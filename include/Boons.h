#include "entity.h"


Entity Boons_new(Vector2D position, int boon);

void Boons_think(Entity* self);

void Boons_update(Entity* self);

void Boons_die(Entity* self, Entity* player);

void Boons_Runes(Entity* self, Entity* player);

void Boons_speed(Entity* self, Entity* player);

void Boons_health(Entity* self, Entity* player);

void Boons_dash(Entity* self, Entity* player);

void Boons_revive(Entity* self, Entity* player);