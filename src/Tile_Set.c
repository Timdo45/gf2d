#include "Tile_Set.h"


typedef struct {
	TileSet Tile_set_list;
	Uint32 tileset_count;
}TileSetManager;

static TileSetManager tile_set_manager = { 0 };

void tile_set_manager_close() {
	int i;
	for (i = 0; i < tile_set_manager.tileset_count; i++) {
		tile_set_free();
	}
}

void tile_set_manager_init(Uint32 tileset_count) {
	if (tileset_count == 0) {
		slog("cannot init zero tilesets");

	}
}

TileSet tile_set_load(
	char* filename,
	Uint32	tile_width,
	Uint32	tile_height,
	Uint32	tile_count);

TileSet tile_set_new() {
	int i;
	for (i = 0; i < tile_set_manager.tileset_count; i++) {
		if(tile_set_manager.tile_set_list[i]._refcount = i)
	}
}

void tile_set_free(TileSet* tileset) {
	if (!tileset) return;
	if (tileset->_refcount > 0){
		slog("");
		}
		gf2d_sprite_free(&tileset->tileImage);
		memset(tileset, 0, sizeof(TileSet));
}

void tile_set_draw(TileSet* tileset, Uint32 tile, Vector2D position) {
if(tileset->tileImage)
}