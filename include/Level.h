#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Collision.h"
#include "Tile_Map.h"
#include "gfc_list.h"
#include "simple_json.h"


typedef struct
{
    TileMap* levelLayout;
    List* spawnList;        //entities to spawn
    List* entityList;
    char* levelFile;
    SDL_Rect levelBounds;
}Level;
typedef struct
{
    Uint32 max_levels;            /**<how many entities exist*/
    Level* entity_list;           /**<a big ole list of entities*/
}LevelManager;

Level *level_load(char* filename);


void level_spawn_boon(Vector2D position);

void level_clear();

void level_spawn_entities();

void level_draw();

Level* level_transition(Level* currentLevel);

#endif
