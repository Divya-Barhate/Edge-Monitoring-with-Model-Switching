
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "platform/esp32/board_io.h"

extern "C" {
#include "inference.h"
#include "model_manager.h"
#include "feature.h"
}

static ModelManager manager;
static float previousTemperature = 0.0f;
static float previousHumidity = 0.0f;
static int sampleCount = 0;
static bool modelSwitched = false;


static const char *WIFI_SSID = "Wokwi-GUEST";
static const char *WIFI_PASSWORD = "";

static const char *NODE_RED_URL =
    "http://host.wokwi.internal:1880/api/sensor";

static void connectWiFi()
{
    Serial.println("Connecting to Wokwi WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);

    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - startTime < 15000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi connection failed");
    }
}

static void sendToNodeRed(float temperature,
                          float humidity,
                          int modelVersion,
                          const char *status)
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Node-RED send skipped: WiFi disconnected");
        return;
    }

    HTTPClient http;

    if (!http.begin(NODE_RED_URL)) {
        Serial.println("HTTP initialization failed");
        return;
    }

    http.addHeader("Content-Type", "application/json");

    String payload = "{";
    payload += "\"temperature\":" + String(temperature, 2) + ",";
    payload += "\"humidity\":" + String(humidity, 2) + ",";
    payload += "\"modelVersion\":" + String(modelVersion) + ",";
    payload += "\"edgeStatus\":\"" + String(status) + "\"";
    payload += "}";

    int responseCode = http.POST(payload);

    Serial.print("Node-RED HTTP response: ");
    Serial.println(responseCode);

    if (responseCode > 0) {
        Serial.println(http.getString());
    }

    http.end();
}


static const char *getStatusName(Classification status)
{
    switch (status) {
        case CLASS_NORMAL:   return "NORMAL";
        case CLASS_WARNING:  return "WARNING";
        case CLASS_CRITICAL: return "CRITICAL";
        default:             return "UNKNOWN";
    }
}

void setup()
{
    if (!platform_begin()) {
        Serial.println("Display initialization failed");
    }

    model_manager_init(&manager);
    connectWiFi();

    Serial.println("HotSwap Edge AI Monitoring");
}

void loop()
{
    PlatformReadings readings;

    if (!platform_read(&readings)) {
        Serial.println("Sensor reading failed");
        delay(2500);
        return;
    }

    sampleCount++;

    float temperatureRate =
        sampleCount == 1 ? 0.0f :
        readings.temperature - previousTemperature;

    float humidityRate =
        sampleCount == 1 ? 0.0f :
        readings.humidity - previousHumidity;

    FeatureData features = {
        readings.temperature,
        readings.humidity,
        temperatureRate,
        humidityRate,
        readings.temperature
    };

    previousTemperature = readings.temperature;
    previousHumidity = readings.humidity;

    if (sampleCount >= 4 && !modelSwitched) {
        if (model_manager_update(&manager, MODEL_V2, 1)) {
            Serial.println("Model updated to V2");
        } else {
            Serial.println("Model update failed");
        }

        modelSwitched = true;
    }

    ModelVersion active = model_manager_get_version(&manager);

    Classification result =
        inference_run(&features, active);

    const char *status = getStatusName(result);

    platform_show(
        readings.temperature,
        readings.humidity,
        (int)active,
        status
    );

    platform_log_sample(
        sampleCount,
        readings.temperature,
        readings.humidity,
        (int)active,
        status
    );

    sendToNodeRed(
    readings.temperature,
    readings.humidity,
    (int)active,
    status
    );

    delay(2500);
}
 

