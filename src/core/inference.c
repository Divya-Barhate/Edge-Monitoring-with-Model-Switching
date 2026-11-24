
#include "inference.h"

Classification inference_run(
    const FeatureData *features,
    ModelVersion version)
{
    if (features == 0)
    {
        return CLASS_CRITICAL;
    }

    if (version == MODEL_V1)
    {
        if (features->temperature >= 35.0f ||
            features->humidity >= 80.0f)
        {
            return CLASS_CRITICAL;
        }

        if (features->temperature >= 30.0f ||
            features->humidity >= 65.0f)
        {
            return CLASS_WARNING;
        }

        return CLASS_NORMAL;
    }

    if (version == MODEL_V2)
    {
        if (features->temperature >= 33.0f ||
            features->humidity >= 75.0f)
        {
            return CLASS_CRITICAL;
        }

        if (features->temperature >= 28.0f ||
            features->humidity >= 60.0f ||
            features->temperature_rate >= 2.0f)
        {
            return CLASS_WARNING;
        }

        return CLASS_NORMAL;
    }

    return CLASS_CRITICAL;
}

