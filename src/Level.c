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
    SJson* json, * wjson;
    Level* level = NULL;
    level = level_new();
    level->levelLayout = tilemap_load(filename);
	json = sj_load(filename);
	wjson = sj_object_get_value(json, "world");
    slog("loading level");
    return level;
}


void level_spawn_boon(Vector2D position)
{

}

void level_clear(Level* self)
{
    if (self == NULL)
    {
        slog("null pointer provided, nothing to do!");
        return;
    }
    if (self->levelLayout != NULL)
    {
        tilemap_free(self->levelLayout);
    }
    memset(self, 0, sizeof(Level));
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

Level* level_transition(Level* currentLevel)
{
    if (currentLevel) {

        level_clear(currentLevel);
    }
    Level* nextLevel;
    nextLevel = level_load("levels/testlevel.json");
    monster_new(vector2d(600, 100));
    monster_new(vector2d(700, 200));
    monster_new(vector2d(250, 250));
    Boons_new(vector2d(500, 500), 0);
    Boons_new(vector2d(600, 500), 1);
    Boons_new(vector2d(400, 500), 2);
    Boons_new(vector2d(700, 500), 3);
    Boons_new(vector2d(300, 500), 4);
    level_draw(nextLevel);
  
    return nextLevel;


}