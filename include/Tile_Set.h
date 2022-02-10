#ifndef __TILE_SET_H__
#define __TILE_SET_H__#pragma once

#include "gf2d_sprite.h"
#include "gfc_text.h"
#include "gfc_vector.h"

typedef struct {
	TextLine tilename;
	Sprite tileImage; //image used for tile
	Uint8  _refcount;
	Uint32 tile_width;
	Uint32 tile_height;
	Uint32 tile_count; //hw many tiles are in the set
}TileSet;


void tile_set_manager_init(Uint32 tileset_count);

TileSet tile_set_load(char* filename);

void tile_set_free(TileSet* tileset);

void tile_set_draw(TileSet* tileset, Uint32 tile, Vector2D position);
#endif
