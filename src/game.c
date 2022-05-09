#include <SDL.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gfc_text.h"
#include "gfc_input.h"
#include "gfc_audio.h"
#include "windows.h"

#include "entity.h"
#include "Player.h"
#include "tile_map.h"
#include "monster.h"
#include "Level.h"
#include "Boons.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
    
    int mx,my;
    float mf = 0;
    Uint8 inMainMenu = 1;
    Uint8 inrestArea = 1;
    Uint8 inSaveMenu = 0;
    Uint8 changeLevel = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
    TileMap *tilemap;
    Level* level,*rest;
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1210,
        720,
        1210,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    tile_set_manager_init(16);
    entity_manager_init(1024);
    gfc_text_init("config/font.cfg");
    windows_manager_init(100);
    gfc_audio_init(10, 2, 2, 3, 1, 1);
    gfc_sound_play(gfc_sound_load("music/01 No Escape.mp3", 0.1, -1), -1, 0.1, -1, -1);
    
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    //tilemap = tilemap_load("levels/testlevel.json");
    level = level_load("levels/testlevel.json");
    rest = level_load("levels/rest_area.json");
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    windows* mainMenu = windows_load("config/main menu.json");
    
    
    player_new(vector2d(500,300), "config/player.json");
    monster_new(vector2d(600, 100));
    monster_new(vector2d(700, 200));
    monster_new(vector2d(250, 250));
    Boons_new(vector2d(500, 500), 0);
    Boons_new(vector2d(600, 500),1);
    Boons_new(vector2d(400, 500),2);
    Boons_new(vector2d(700, 500),3);
    Boons_new(vector2d(300, 500),4);
    
    Color color;
    color = gfc_color(1, 0, 0, 255);
   
    
    
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
            // draw other game elements
            //tilemap_draw(tilemap);
            if (!inMainMenu && !inSaveMenu)
            {
                if (!changeLevel)
                {
                    level_draw(rest);
                }
                else
                {
                    level_clear(rest);
                    level_draw(level);
                }
            entity_manager_think_all();
            entity_update_all();
            entity_manager_draw_all();
            windows_free(mainMenu);

            }
            //UI elements last
            windows_manager_draw_all();
            windows_update_all();
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
            //gfc_text_draw_line("hello there, things", FT_H1, color, vector2d(100, 500));
            
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        if (keys[SDL_SCANCODE_KP_ENTER])inMainMenu = 0;
        if (keys[SDL_SCANCODE_Z])changeLevel = 1;
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
       // slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
