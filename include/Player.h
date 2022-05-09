#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "entity.h"
/**
 * @brief creates an instance of a bug entity
 * @param position the location in the world to spawn the bug at
 * @returns NULL on error, or a pointer to the bug
 */
Entity *player_new(Vector2D position, char *filename);

void player_hitbox(Entity* self);

void player_save(Entity* self, char* filename);

void player_attack(Entity* self);

void player_die(Entity* self, Entity* other);

Entity* player_touch(Entity* self, SDL_Rect hitbox);

void player_collide_level(Entity* self);

void sword_attack(Entity* self);

void spear_attack(Entity* self);

void gauntlet_attack(Entity* self);

void bow_attack(Entity* self);
int get_face_direction(float angle);

void player_move(Entity* self);

void player_activate(Entity* self);

Entity* player_get();

void player_set_runes(int amount);

void player_set_maxHealth(int amount);

void player_set_speedMultiplier(float amount);

void player_set_attackRank(int amount);

void player_dash(Entity* self);

void player_set_weapon(Entity* self);

void player_gain_dash();

void player_gain_revives();

#endif
