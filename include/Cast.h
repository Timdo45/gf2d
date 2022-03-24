#include "entity.h"


Entity cast_new(Vector2D position);

void cast_think(Entity* self);

void cast_update(Entity* self);

void cast_die(Entity* self);

void cast_damage(Entity* self);
