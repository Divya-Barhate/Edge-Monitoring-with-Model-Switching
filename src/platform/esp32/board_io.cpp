
#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "board_io.h"

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDRESS 0x3C

static DHT dht(DHT_PIN, DHT_TYPE);

static Adafruit_SSD1306 display(
    OLED_WIDTH, OLED_HEIGHT, &Wire, -1
);

bool platform_begin(void)
{
    Serial.begin(115200);

    dht.begin();
    Wire.begin(21, 22);

    if (!display.begin(
            SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("OLED initialization failed");
        return false;
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("HotSwap Edge AI");
    display.println("Initializing...");
    display.display();

    return true;
}

bool platform_read(PlatformReadings *readings)
{
    if (readings == nullptr) {
        return false;
    }

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        return false;
    }

    readings->temperature = temperature;
    readings->humidity = humidity;

    return true;
}

void platform_show(
    float temperature,
    float humidity,
    int model_version,
    const char *status)
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("HotSwap Edge AI");
    display.println("----------------");

    display.print("Temp: ");
    display.print(temperature, 1);
    display.println(" C");

    display.print("Humidity: ");
    display.print(humidity, 1);
    display.println(" %");

    display.print("Model: V");
    display.println(model_version);

    display.print("Status: ");
    display.println(status);

    display.display();
}

void platform_log_sample(
    int sample,
    float temperature,
    float humidity,
    int model_version,
    const char *status)
{
    Serial.printf(
        "Sample: %d | Temp: %.1f C | Humidity: %.1f%%"
        " | Model: V%d | Status: %s\n",
        sample,
        temperature,
        humidity,
        model_version,
        status
    );
}
