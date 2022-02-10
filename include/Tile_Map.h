#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include "gf2d_sprite.h"
#include "gfc_text.h"
#include "gfc_vector.h"
#include "Tile_Set.h"
typedef struct {
	TextLine  tilename;
	TileSet *tileset;

}TileMap;

TileMap tile_map_new();
#endif
