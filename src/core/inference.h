
#ifndef INFERENCE_H
#define INFERENCE_H

#include "feature.h"
#include "model_manager.h"

typedef enum
{
    CLASS_NORMAL = 0,
    CLASS_WARNING,
    CLASS_CRITICAL
} Classification;

Classification inference_run(
    const FeatureData *features,
    ModelVersion version
);

#endif
