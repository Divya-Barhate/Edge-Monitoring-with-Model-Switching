

#include "model_manager.h"

static int is_valid_version(ModelVersion version)
{
    return version == MODEL_V1 || version == MODEL_V2;
}

void model_manager_init(ModelManager *manager)
{
    if (manager == 0)
    {
        return;
    }

    manager->active_version = MODEL_V1;
    manager->previous_version = MODEL_V1;
    manager->successful_switches = 0;
}

int model_manager_update(
    ModelManager *manager,
    ModelVersion new_version,
    int integrity_ok)
{
    if (manager == 0)
    {
        return 0;
    }

    if (!is_valid_version(new_version) || integrity_ok != 1)
    {
        return 0;
    }

    if (manager->active_version == new_version)
    {
        return 1;
    }

    manager->previous_version = manager->active_version;
    manager->active_version = new_version;
    manager->successful_switches++;

    return 1;
}

int model_manager_switch(
    ModelManager *manager,
    ModelVersion new_version)
{
    return model_manager_update(manager, new_version, 1);
}

int model_manager_rollback(ModelManager *manager)
{
    if (manager == 0)
    {
        return 0;
    }

    if (!is_valid_version(manager->previous_version))
    {
        return 0;
    }

    if (manager->active_version == manager->previous_version)
    {
        return 0;
    }

    ModelVersion failed_version = manager->active_version;

    manager->active_version = manager->previous_version;
    manager->previous_version = failed_version;

    return 1;
}

ModelVersion model_manager_get_version(
    const ModelManager *manager)
{
    if (manager == 0)
    {
        return (ModelVersion)0;
    }

    return manager->active_version;
}
