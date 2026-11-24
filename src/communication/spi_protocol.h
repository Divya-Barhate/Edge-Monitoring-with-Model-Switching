
#ifndef SPI_PROTOCOL_H
#define SPI_PROTOCOL_H

#include <stdint.h>
#include "../sensor/sensor.h"
#include "inference.h"

#define SPI_PACKET_SIZE 7

typedef struct
{
    float temperature;
    float humidity;
    uint8_t model_version;
    uint8_t classification;
} TelemetryPacket;

uint8_t spi_crc8(const uint8_t *data, uint8_t length);

void spi_packet_encode(
    const SensorData *sensor,
    uint8_t model_version,
    uint8_t classification,
    uint8_t packet[SPI_PACKET_SIZE]
);

int spi_packet_decode(
    const uint8_t packet[SPI_PACKET_SIZE],
    TelemetryPacket *result
);

#endif
