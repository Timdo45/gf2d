#include "monster.h"
#include "Player.h"

Entity* player;
Entity monster_new(Vector2D position)
{
	Entity* ent;
	char* Sprite;

	Sprite = "images/space_bug_top.png";
	ent = entity_new();
	ent->sprite = gf2d_sprite_load_all(Sprite, 128, 128, 16);
	ent->think = monster_think;
	ent->update = monster_update;
	ent->onDeath = monster_die;
	ent->draw_offset.x = -64;
	ent->draw_offset.y = -64;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->health =10;
	player = player_get();
	vector2d_copy(ent->position, position);

	ent->hitbox = collision_box((ent->position.x + ent->draw_offset.x), (ent->position.y + ent->draw_offset.y), 128, 128);
	gf2d_draw_rect(ent->hitbox, vector4d(255, 255, 255, 255));
	slog("enemy isPlayer: (%i)", ent->_isPlayer);
}
void monster_think(Entity *self)
{

}
void monster_update(Entity* self)
{
	self->hitbox = collision_box((self->position.x + self->draw_offset.x), (self->position.y + self->draw_offset.y), 128, 128);
	gf2d_draw_rect(self->hitbox, vector4d(255, 255, 255, 255));
	if (self->health<=0)
	{
		monster_die(self,player);
	}
	monster_move(self);
	monster_attack(self);

}

void monster_die(Entity* self, Entity* player)
{
		slog("monster died");
		self->health = 0;

		player_set_runes(50);
		entity_free(self);
}
void monster_move(Entity* self)
{
	if (self->position.x > player->position.x)
	{
		self->position.x -= 0.2;
	}
	if (self->position.x < player->position.x)
	{
		self->position.x += 0.2;
	}
	if (self->position.y > player->position.y)
	{
		self->position.y -= 0.2;
	}
	if (self->position.y < player->position.y)
	{
		self->position.y += 0.2;
	}
}
void monster_attack(Entity* self)
{
	if (collision_rect_test(self->hitbox, player->hitbox))
	{
		slog("monster attack");
		gf2d_draw_rect(self->hitbox, vector4d(255, 0, 0, 0));
		player->health -= 5;
	}
}