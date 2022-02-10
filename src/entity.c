#include "entity.h"
#include <simple_json.h>

void entity_manager_close()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)continue;
        entity_free(&entity_manager.entity_list[i]);
    }
    free(entity_manager.entity_list);
    memset(&entity_manager, 0, sizeof(EntityManager));
    slog("entity_system closed");
}

void entity_manager_init(Uint32 maxEntities)
{
    entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), maxEntities);
    if (entity_manager.entity_list == NULL)
    {
        slog("failed to allocate entity list, cannot allocate ZERO entities");
        return;
    }
    entity_manager.entity_count = maxEntities;
    atexit(entity_manager_close);
    slog("entity_system initialized");
}

Entity* entity_new()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet, so we can!
        {
            entity_manager.entity_list[i]._inuse = 1;
            entity_manager.entity_list[i].scale.x = 1;
            entity_manager.entity_list[i].scale.y = 1;
            return &entity_manager.entity_list[i];
        }
    }
    slog("entity_new: no free space in the entity list");
    return NULL;
}

void entity_free(Entity* entity) {
    if (entity == NULL) {
        slog("null pointer provided. nothing to do!");
        return;
    }
    if (entity->sprite != NULL) {
        gf2d_sprite_free(entity->sprite);
        memset(entity, 0, sizeof(Entity));
    }
}

void entity_draw(Entity* entity) {
    if (!entity) {
        return;
    }
}

