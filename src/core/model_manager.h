
#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

typedef enum
{
    MODEL_V1 = 1,
    MODEL_V2 = 2
} ModelVersion;

typedef struct
{
    ModelVersion active_version;
    ModelVersion previous_version;
    unsigned int successful_switches;
} ModelManager;

void model_manager_init(ModelManager *manager);

int model_manager_switch(
    ModelManager *manager,
    ModelVersion new_version
);

int model_manager_update(
    ModelManager *manager,
    ModelVersion new_version,
    int integrity_ok
);

int model_manager_rollback(ModelManager *manager);

ModelVersion model_manager_get_version(
    const ModelManager *manager
);

#endif

