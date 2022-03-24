#pragma once
#include "entity.h"

Entity monster_new(Vector2D position);

void monster_think(Entity *self);

void monster_update(Entity *self);

void monster_die(Entity* self, Entity* player);

void monster_move(Entity* self);

void monster_attack(Entity* self);
