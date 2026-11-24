
#ifndef BOARD_IO_H
#define BOARD_IO_H

#include <stdbool.h>

typedef struct
{
    float temperature;
    float humidity;
} PlatformReadings;

bool platform_begin(void);

bool platform_read(PlatformReadings *readings);

void platform_show(
    float temperature,
    float humidity,
    int model_version,
    const char *status
);

void platform_log_sample(
    int sample,
    float temperature,
    float humidity,
    int model_version,
    const char *status
);

#endif
