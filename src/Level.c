#include "Level.h"
#include "simple_json.h"
#include "simple_logger.h"

Level* level = NULL;
Level* level_new()
{
    level = (Level*)malloc(sizeof(Level));
    if (!level)
    {
        slog("failed to allocate memory for a new level");
        return NULL;
    }
    memset(level, 0, sizeof(Level));
    return level;
}


Level *level_load(char* filename)
{
    //SJson* json, * wjson;
    Level* level = NULL;
    level = level_new();
    level->levelLayout = tilemap_load(filename);
	//json = sj_load(filename);
	//wjson = sj_object_get_value(json, "world");
    slog("loading level");
    return level;
}


void level_spawn_boon(Vector2D position)
{

}

void level_clear()
{

}

void level_spawn_entities()
{

}
void level_draw(Level* level)
{
    int i;
    int walls;
    tilemap_draw(level->levelLayout);
    for (i = 0; i < level->levelLayout->tilemap_count; i++)
    {
        if (!level->levelLayout->tilemap[i])
        { 
            continue;
        }
        if (level->levelLayout->tilemap[i] != 1)
        {
            continue;
        }
        else
        {
            level->levelBounds = collision_box(
                level->levelLayout->tileset->tile_width,
                level->levelLayout->tileset->tile_height,
                ((level->levelLayout->tilemap_width - 2) * level->levelLayout->tileset->tile_width),
                (((level->levelLayout->tilemap_height - 2) * level->levelLayout->tileset->tile_height)));
            gf2d_draw_rect(level->levelBounds, vector4d(255, 0, 255, 255));
        }
    }
}


Level* level_get()
{
    return level;
}