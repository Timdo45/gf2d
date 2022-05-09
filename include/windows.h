#ifndef __WINDOWS_H__
#define __WINDOWS_H__

#include "label.h"
typedef struct WINDOWS_S
{
    Uint8       _inuse;     /**<this flag keeps track if this windows is active or free to reassign*/
    Uint8       isActive;
    Sprite*     sprite;     /**<sprite used to draw the sprite*/
    float       frame;      /**<current frame to draw*/
    Vector2D    draw_offset;/**<draw position relative to the windows position*/
    Vector2D    position;   /**<where our windows lives*/
    Vector2D    draw_scale;  /**<the scale factor for drawing the sprite*/
    SDL_Rect    hitbox;  /**<describe the bounding box around this window*/
    void (*think)(struct WINDOWS_S* self); /**<a pointer to a think function for this windows*/
    void (*update)(struct WINDOWS_S* self);
    Uint8       labelCount;
    Label*      labelList;
    char* spritename;
     

}windows;
typedef struct
{
    Uint32 max_windows;            /**<how many entities exist*/
    windows* windows_list;           /**<a big ole list of entities*/
}windowsManager;

/**
 * @brief initialize the internal windows windows_manager_init
 * @note must be called before other windows functions
 * @param max_entities how many concurrent entities will be supported
 */
void windows_manager_init(Uint32 max_entities);

/**
 * @brief draws all active entities to the screen
 */
void windows_manager_draw_all();

/**
 * @brief runs any think function for all active entities
 */
void windows_manager_think_all();


/**
 * @brief free all active entities
 * @note for use in level transitions.
 */
void windows_manager_clear();

/**
 * @brief get a new empty windows
 * @returns NULL on error, or a pointer to a blank windows
 */
windows* windows_new();

/**
 * @brief draws the given windows
 * @param windows the windows to draw
 */
void windows_draw(windows* windows);

/**
 * @brief free the memory of an windows
 * @param windows the windows to free
 */
void windows_free(windows* windows);

void windows_update(windows* ent);

void windows_update_all();
windows* windows_load(char* filename);
windowsManager* windows_manager_get();

#endif
