
#include "spi_protocol.h"

uint8_t spi_crc8(const uint8_t *data, uint8_t length)
{
    uint8_t crc = 0;

    if (data == 0)
    {
        return 0;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80)
            {
                crc = (uint8_t)((crc << 1) ^ 0x07);
            }
            else
            {
                crc = (uint8_t)(crc << 1);
            }
        }
    }

    return crc;
}

void spi_packet_encode(
    const SensorData *sensor,
    uint8_t model_version,
    uint8_t classification,
    uint8_t packet[SPI_PACKET_SIZE])
{
    if (sensor == 0 || packet == 0)
    {
        return;
    }

    int16_t temperature =
        (int16_t)(sensor->temperature * 100.0f);

    uint16_t humidity =
        (uint16_t)(sensor->humidity * 100.0f);

    /* Temperature: signed 16-bit, big-endian. */
    packet[0] = (uint8_t)((uint16_t)temperature >> 8);
    packet[1] = (uint8_t)temperature;

    /* Humidity: unsigned 16-bit, big-endian. */
    packet[2] = (uint8_t)(humidity >> 8);
    packet[3] = (uint8_t)humidity;

    packet[4] = model_version;
    packet[5] = classification;

    /* CRC covers the first six bytes. */
    packet[6] = spi_crc8(packet, 6);
}

int spi_packet_decode(
    const uint8_t packet[SPI_PACKET_SIZE],
    TelemetryPacket *result)
{
    if (packet == 0 || result == 0)
    {
        return 0;
    }

    if (spi_crc8(packet, 6) != packet[6])
    {
        return 0;
    }

    if ((packet[4] != 1 && packet[4] != 2) ||
        packet[5] > 2)
    {
        return 0;
    }

    uint16_t temp_bits =
        ((uint16_t)packet[0] << 8) | packet[1];

    int16_t temperature = (int16_t)temp_bits;

    uint16_t humidity =
        ((uint16_t)packet[2] << 8) | packet[3];

    result->temperature = (float)temperature / 100.0f;
    result->humidity = (float)humidity / 100.0f;
    result->model_version = packet[4];
    result->classification = packet[5];

    return 1;
}
