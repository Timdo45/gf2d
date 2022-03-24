#include "Boons.h"
#include "Player.h"


int boonType;
EntityManager *entityManager;
Entity Boons_new(Vector2D position, int boon)
{
	Entity* ent;
	
	ent = entity_new();
	vector2d_copy(ent->position, position);
	ent->_isInteractable = 1;
	ent->think = Boons_think;
	ent->update = Boons_update;
	ent->onDeath = Boons_die;
	ent->hitbox = collision_box(ent->position.x-50, ent->position.y, 100 , 100);
	ent->boonType = boon;
}

void Boons_think(Entity* self)
{

}

void Boons_update(Entity* self)
{
	self->hitbox = collision_box(self->position.x, self->position.y, 100, 100);
	if (self->boonType == 0)
	{
		gf2d_draw_rect(self->hitbox, vector4d(0, 255, 255, 255));
	}
	else if (self->boonType == 1)
	{
		gf2d_draw_rect(self->hitbox, vector4d(255, 0, 255, 255));
	}
	else if (self->boonType == 2)
	{
		gf2d_draw_rect(self->hitbox, vector4d(255, 255, 0, 255));
	}
	else if (self->boonType == 3)
	{
		gf2d_draw_rect(self->hitbox, vector4d(100, 255, 100, 255));
	}
	else if (self->boonType == 4)
	{
		gf2d_draw_rect(self->hitbox, vector4d(0, 0, 0, 255));
	}

}

void Boons_die(Entity* self, Entity* player)
{
	if (self->boonType == 0)
	{
		slog("Runes");
		Boons_Runes(self,player);
	}
	else if (self->boonType == 1)
	{
		slog("speed");
		Boons_speed(self, player);
	}
	else if (self->boonType == 2)
	{
		slog("health");
		Boons_health(self, player);
	}
	else if (self->boonType == 3)
	{
		slog("dash");
		Boons_dash(self, player);
	}
	else if (self->boonType == 4)
	{
		slog("revive");
		Boons_revive(self, player);
	}
	entity_free(self);
	
}
void Boons_Runes(Entity* self, Entity* player)
{
	player_set_runes(100);
}

void Boons_speed(Entity* self, Entity* player)
{
	player_set_speedMultiplier(2);
	slog("player gained 25% spped boost");
}

void Boons_health(Entity* self, Entity* player)
{
	int healthGain;
	healthGain = 50;
	player_set_maxHealth(healthGain);
	player->health += healthGain;
	slog("player gained (%i) maximum health", healthGain);

}
void Boons_dash(Entity* self, Entity* player)
{
	player_gain_dash();
}
void Boons_revive(Entity* self, Entity* player)
{
	player_gain_revives();
}