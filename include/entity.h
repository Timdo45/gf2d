#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL.h>
#include "gf2d_sprite.h"
typedef struct ENTITY_S
{
	void       (*think)(struct Entity_S* self); /**<pointer to the think function*/
	void       (*update)(struct Entity_S* self); /**<pointer to the update function*/
	void       (*damage)(struct Entity_S* self, float damage, struct Entity_S* inflictor); /**<pointer to the think function*/
	void       (*onDeath)(struct Entity_S* self, struct Entity_S* inflictor); /**<pointer to an funciton to call when the entity dies*/
	Uint8 _inuse;  /**<this flag keeps track if this entity is active or free to reassign*/
	Sprite *sprite; /**<sprite used to draw the sprite */
	Vector2D position; /**<where our entity lives*/
	Vector2D draw_offset;/**<draw position relative to the entity position*/
	Vector2D velocity; /**<how fast enitty moves*/
	Vector2D mins, maxs; /**<describe the bounding box around the entity*/
	Vector2D scale;
	float frame; /**<current frame to draw*/

}Entity;

typedef struct
{
	Entity* entity_list;
	Uint32  entity_count;

}EntityManager;

static EntityManager entity_manager = { 0 };

/**
 * @brief initializes the entity subsystem
 * @param maxEntities the limit on number of entities that can exist at the same time
 */
void entity_system_init(Uint32 maxEntities);

/**
 * @brief provide a pointer to a new empty entity
 * @return NULL on error or a valid entity pointer otherwise
 */
Entity* entity_new();

/**
 * @brief free a previously created entity from memory
 * @param self the entity in question
 */
void entity_free(Entity* self);


/**
 * @brief Draw an entity in the current frame
 * @param self the entity in question
 */
void entity_draw(Entity* self);

/**
 * @brief draw ALL active entities
 */
void entity_draw_all();

/**
 * @brief Call an entity's think function if it exists
 * @param self the entity in question
 */
void entity_think(Entity* self);

/**
 * @brief run the think functions for ALL active entities
 */
void entity_think_all();

/**
 * @brief run the update functions for ALL active entities
 */
void entity_update_all();




#endif