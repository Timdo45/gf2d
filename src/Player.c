#include "simple_logger.h"
#include "Player.h"
#include "simple_json.h"
#include "gf2d_draw.h"
#include "Level.h"

int Health;
int dashMax;
int _isPlayer;
int Gold;
int Revives;
int Runes;
const char *equippedWeapon;
int attackRank;
int castCount;
int hasSword;
int hasBow;
int hasSpear;
int hasGauntlets;
EntityManager *entityManager;
Entity* ent;
const char* spriteName;
int maxHealth;
int isTouching;
float speedMultiplier =1;
int dashes;
Uint32 lastTime = 0;
Uint32 otherTime = 0;
int tempHealth;
int tempDashes;
int tempRevives;


void player_think(Entity *self)
{
    Vector2D direction;
    int mx,my;
    float angle;
    const Uint8 *keys;
    const Uint8* mouse;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 16)self->frame = 0;
    
    mouse = SDL_GetMouseState(&mx,&my);
    direction.x = mx - self->position.x;
    direction.y = my - self->position.y;
    angle = vector2d_angle(direction) - 90;
    self->rotation.z = angle;
    angle += 90;
    
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    self->faceSide = get_face_direction(angle);
    
    if (keys[SDL_SCANCODE_W])
    {
        self->velocity.y = -2*speedMultiplier;
    }
    if (keys[SDL_SCANCODE_D])
    {
        self->velocity.x = 2 * speedMultiplier;
    }
    if (keys[SDL_SCANCODE_A])
    {
        self->velocity.x = -2* speedMultiplier;
    }
    if (keys[SDL_SCANCODE_S])
    {
        self->velocity.y = 2 *speedMultiplier;
    }
    if (keys[SDL_SCANCODE_F])
    {
        player_activate(self);
    }
    if (keys[SDL_SCANCODE_SPACE])
    {
        player_dash(self);
    }
    if (keys[SDL_SCANCODE_1])
    {
        if (Runes < 50)
        {
            slog("not enough Runes for upgrade");
            return;
        }
        else
        {
            maxHealth += 10;
            Runes -= 50;
        }
    }
    if (keys[SDL_SCANCODE_2])
    {
        if (Runes < 50)
        {
            slog("not enough Runes for upgrade");
            return;
        }
        else
        {
            slog("Bought access to Spear");
            Runes -= 50;
            hasSpear =1;
        }
    }
    if (keys[SDL_SCANCODE_3])
    {
        if (Runes < 50)
        {
            slog("not enough Runes for upgrade");
            return;
        }
        else
        {
            Runes -= 50;
            dashMax++;
        }
    }
    if (keys[SDL_SCANCODE_4])
    {
        if (Runes < 50)
        {
            slog("not enough Runes for upgrade");
            return;
        }
        else
        {
            Runes -= 50;
            Revives++;
        }
    }
    if (keys[SDL_SCANCODE_5])
    {
        if (Runes < 50)
        {
            slog("not enough Runes for upgrade");
            return;
        }
        else
        {

            Runes -= 50;
        }
    }
    if (mouse == SDL_BUTTON_LEFT)
    {
        player_attack(self);

    }
    if (keys[SDL_SCANCODE_T])
    {
        slog("activated death");
        player_die(self,self);
    }
    if (keys[SDL_SCANCODE_LSHIFT])
    {
        player_set_weapon(self);
    }
    {
        vector2d_scale(self->velocity,self->velocity,0.50);
        if (vector2d_magnitude(self->velocity)<0.05)
        {
            vector2d_clear(self->velocity);
        }
    }


}
void player_attack(Entity *self)
{
    Entity* other;
    if (!SDL_strcmp(equippedWeapon, "Sword"))
    {
        sword_attack(self);
    }
    else if(!SDL_strcmp(equippedWeapon, "Bow"))
    {
        slog("has Bow");
    }
    else if (!SDL_strcmp(equippedWeapon, "Gauntlets"))
    {
        gauntlet_attack(self);
    }
    else if (!SDL_strcmp(equippedWeapon, "Spear"))
    {
        spear_attack(self);
    }
}

void player_cast(Entity* self)
{

}
void sword_attack(Entity* self)
{
    SDL_Rect attackHitbox;        
    Entity* other;
    if (self->faceSide == 0)
    {
    self->attackHitbox = collision_box(self->hitbox.x,(self->hitbox.y - self->hitbox.h) ,self->hitbox.w,self->hitbox.h);
    gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
    other=player_touch(self, self->attackHitbox);
    if (!other) {
        
        SDL_Delay(500);
        return;
    }
    other->health -= 5;
    other->position.y -= 100;
    }
    else if (self->faceSide == 1)
    {
        self->attackHitbox = collision_box((self->hitbox.x + self->hitbox.w),self->hitbox.y, self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other=player_touch(self, self->attackHitbox);
        if (!other) {
            
            SDL_Delay(500);
            return;
        }
        other->health -= 5;
        other->position.x += 100;
    }
    else if (self->faceSide == 2)
    {
        self->attackHitbox = collision_box(self->hitbox.x, (self->hitbox.y + self->hitbox.h), self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
       other= player_touch(self, self->attackHitbox);
       if (!other) {
           
           SDL_Delay(500);
           return;
       }
        other->health -= 5;
        other->position.y += 100;
    }
    else if (self->faceSide == 3)
    {
        self->attackHitbox = collision_box((self->hitbox.x - self->hitbox.w), self->hitbox.y, self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
       other = player_touch(self, self->attackHitbox);
       if (!other) {
           
           SDL_Delay(500);
           return;
       }
        other->health -= 5;
        other->position.x -= 100;
    }
    
}
void spear_attack(Entity* self)
{
    SDL_Rect attackHitbox;
    Entity* other;

    if (self->faceSide == 0)
    {
        self->attackHitbox = collision_box((self->hitbox.x*1.07), (self->hitbox.y - self->hitbox.h), self->hitbox.w*0.5, self->hitbox.h*2);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            SDL_Delay(250);
            return;
        }
        other->health -= 2;
    }
    else if (self->faceSide == 1)
    {
        self->attackHitbox = collision_box((self->hitbox.x + self->hitbox.w), self->hitbox.y*1.07, self->hitbox.w*1.5, self->hitbox.h*0.5);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            SDL_Delay(250);
            return;
        }
        other->health -= 2;
    }
    else if (self->faceSide == 2)
    {
        self->attackHitbox = collision_box((self->hitbox.x*1.07), (self->hitbox.y + self->hitbox.h), self->hitbox.w*0.5, self->hitbox.h*1.5);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            SDL_Delay(250);
            return;
        }
        other->health -= 2;
    }
    else if (self->faceSide == 3)
    {
        self->attackHitbox = collision_box((self->hitbox.x - (self->hitbox.w*1.5)), self->hitbox.y*1.07, self->hitbox.w*1.5, self->hitbox.h*0.5);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            SDL_Delay(250);
            return;
        }
        other->health -= 2;
    }

    SDL_Delay(250);
}
void gauntlet_attack(Entity* self)
{
    SDL_Rect attackHitbox;
    Entity* other;
    if (self->faceSide == 0)
    {
        self->attackHitbox = collision_box(self->hitbox.x, (self->hitbox.y - self->hitbox.h), self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            return;
        }
        other->health -= 1;
    }
    else if (self->faceSide == 1)
    {
        self->attackHitbox = collision_box((self->hitbox.x + self->hitbox.w), self->hitbox.y, self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            return;
        }
        other->health -= 1;
    }
    else if (self->faceSide == 2)
    {
        self->attackHitbox = collision_box(self->hitbox.x, (self->hitbox.y + self->hitbox.h), self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            return;
        }
        other->health -= 1;
    }
    else if (self->faceSide == 3)
    {
        self->attackHitbox = collision_box((self->hitbox.x - self->hitbox.w), self->hitbox.y, self->hitbox.w, self->hitbox.h);
        gf2d_draw_rect(self->attackHitbox, vector4d(0, 0, 255, 255));
        other = player_touch(self, self->attackHitbox);
        if (!other) {
            
            return;
        }
        other->health -= 1;
    }

    SDL_Delay(100);
}
void bow_attack(Entity* self)
{

}
void player_activate(Entity* self)
{
    Entity* other;
    other = player_touch(self, self->hitbox);
    slog("checking");
    if (!other)return;
    if (!other->_isInteractable)return;
    if (self == other)return;
    slog("checking2");

    other->onDeath(other,self);
}
void player_dash(Entity* self)
{
    int currentTime;
    currentTime = SDL_GetTicks();
    if (dashes > 0)
    {
       
        if (currentTime > lastTime + 250)
        {


            switch (self->faceSide)
            {
            case 0:
                self->position.y -= 200;
            case 1:
                self->position.x += 200;
            case 2:
                self->position.y += 200;
            case 3:
                self->position.x -= 200;
            }
            slog("dash number (%i)", dashes);
            dashes--;
            slog("dash number (%i)", dashes);
            slog("faceside (%i)", self->faceSide);
            lastTime = currentTime;
        }
    }
}
void player_update(Entity* self)
{
    Uint32 currentTime;
    currentTime = SDL_GetTicks();
    self->hitbox = collision_box((self->position.x + self->draw_offset.x), (self->position.y + self->draw_offset.y), 128, 128);
    gf2d_draw_rect(self->hitbox, vector4d(255, 255, 255, 255));
    player_touch(self, self->hitbox);
    if (self->health <= 0)
    {
        self->health = 0;
        player_die(self,self);
    }

    if (dashes < dashMax   && currentTime > otherTime + 2000)
    {
        dashes = dashMax;
        otherTime = currentTime;
    }

}

int get_face_direction(float angle)
{
    if (angle < -45 && angle > -135)
    {
        return 0;
    }
    else if (angle > -45 && angle < 45)
    {
        return 1;
    }
    else if (angle > 45 && angle < 135)
    {
        return 2;
    }
    else
    {     
        return 3;
    }
    
}

Entity* player_new(Vector2D position, char *filename)
{
    SJson* json, *pjson;
    Rect hitbox;
    const char* weapon;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for player");
        return NULL;
    }
    json = sj_load(filename);
    if (!json)
    {
        slog("failed to load json file (%s) for the world data", filename);
        free(ent);
        return NULL;
    }
    pjson = sj_object_get_value(json, "player");
    if (!pjson)
    {
        slog("failed to find player object in %s player config", filename);
        free(ent);
        sj_free(json);
        return NULL;
    }
    spriteName = sj_get_string_value(sj_object_get_value(pjson, "sprite"));
    ent->sprite_name = spriteName;
    if (ent->sprite_name)
    {
        ent->sprite = gf2d_sprite_load_all(ent->sprite_name, 128, 128, 16);
    }
    else
    {
        slog("player data (%s) has no sprite", filename);
    }
    sj_get_integer_value(sj_object_get_value(pjson, "Health"), &Health);
    sj_get_integer_value(sj_object_get_value(pjson, "Gold"), &Gold);
    sj_get_integer_value(sj_object_get_value(pjson, "_isPlayer"), &_isPlayer);
    sj_get_integer_value(sj_object_get_value(pjson, "dashMax"), &dashMax);
    sj_get_integer_value(sj_object_get_value(pjson, "Revives"), &Revives);
    sj_get_integer_value(sj_object_get_value(pjson, "Runes"), &Runes);
    sj_get_integer_value(sj_object_get_value(pjson, "Sword"), &hasSword);
    sj_get_integer_value(sj_object_get_value(pjson, "Spear"), &hasSpear);
    sj_get_integer_value(sj_object_get_value(pjson, "Gauntlets"), &hasGauntlets);
    sj_get_integer_value(sj_object_get_value(pjson, "Bow"), &hasBow);
    sj_get_integer_value(sj_object_get_value(pjson, "castCount"), &castCount);
    sj_get_integer_value(sj_object_get_value(pjson, "attackRank"), &attackRank);
    equippedWeapon=sj_get_string_value(sj_object_get_value(pjson, "equippedWeapon"));
    
    ent->think = player_think;
    ent->update = player_update;
    ent->onDeath = player_die;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->health = Health;
    maxHealth = ent->health;
    dashes = dashMax;
    entityManager = entity_manager_get();
    ent->hitbox = collision_box((ent->position.x + ent->draw_offset.x), (ent->position.y + ent->draw_offset.y), 128, 128);
    gf2d_draw_rect(ent->hitbox, vector4d(255, 255, 255, 255));
    vector2d_copy(ent->position,position);
    slog("Current Health: (%i)", Health);
    slog("Current Gold: (%i)", Gold);
    slog("Sprite Name: (%s)", ent->sprite_name);
    slog("Equipped Weapon: (%s)", equippedWeapon);
    
    return ent;
}

Entity* player_touch(Entity *self, SDL_Rect hitbox)
{
    Entity *other;
    int isTouching=0;
    if (!self)return 0;
    for (int i = 0; i<entityManager->max_entities; i++)
    {
        other = &entityManager->entity_list[i];
        if (!other) {
            slog("no other");
            return;
        }
        if (!other->_inuse)
        {
            continue;
        }

        if (self != other)
        {
            if (collision_rect_test(hitbox, other->hitbox))
            {
                gf2d_draw_rect(hitbox, vector4d(255, 0, 0, 255));
                
                isTouching = 1;
                return other;
            }
            else if(!isTouching)
            {
                gf2d_draw_rect(hitbox, vector4d(255, 255, 255, 255));
                continue;
            }
            else
            {
            }

        }
        
    }
        player_collide_level(self);
        return NULL;

    //slog("number of entities in use: (%i)", entityCount);
}
void player_collide_level(Entity *self)
{
    Level* level = level_get();
    if (self->hitbox.x <= level->levelBounds.x)
    {
        if (self->velocity.x < 0)
        {
            self->position.x = level->levelBounds.x + (self->hitbox.w * 0.5);
        }
    }
    if (self->hitbox.x + self->hitbox.w >= level->levelBounds.x + level->levelBounds.w)
    {
        if (self->velocity.x > 0)
        {
            self->position.x = (level->levelBounds.x + level->levelBounds.w) - (self->hitbox.w * 0.5);
        }
    }
    if (self->hitbox.y <= level->levelBounds.y)
    {
        if (self->velocity.y < 0)
        {
            self->position.y = level->levelBounds.y + (self->hitbox.h * 0.5);
        }
    }
    if (self->hitbox.y + self->hitbox.h >= level->levelBounds.y + level->levelBounds.h)
    {
        if (self->velocity.y > 0)
        {
            self->position.y = (level->levelBounds.y + level->levelBounds.h) - (self->hitbox.h * 0.5);
        }
    }

}

void player_move(Entity *self)
{
    Vector2D direction;
    int mx, my;
    float angle;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 16)self->frame = 0;

    SDL_GetMouseState(&mx, &my);
    direction.x = mx - self->position.x;
    direction.y = my - self->position.y;
    angle = vector2d_angle(direction) - 90;
    self->rotation.z = angle;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    if (keys[SDL_SCANCODE_W])
    {
        // move forward
        vector2d_set_magnitude(&direction, 3);
        vector2d_copy(self->velocity, direction);
    }
    else
    {
        vector2d_scale(self->velocity, self->velocity, 0.5);
        if (vector2d_magnitude(self->velocity) < 0.05)
        {
            vector2d_clear(self->velocity);
        }
    }

}

void player_save(Entity *self, char* filename)
{
    SJson* json, *player, *sprite, *health, *gold, *runes, *maxDashes, *isPlayer,
        *revives, *Sword, *Bow, *Spear, *Gauntlets, *CastCount, *AttackRank, *EquippedWeapon;
    char* thing;

    dashMax -= tempDashes;
    maxHealth -= tempHealth;
    Revives -= 1;

    thing = equippedWeapon;
    json = sj_object_new();
    player = sj_object_new();
    health = sj_new_int(maxHealth);
    sprite = sj_new_str(self->sprite_name);
    gold = sj_new_int(0);
    runes = sj_new_int(Runes);
    maxDashes = sj_new_int(dashMax);
    isPlayer = sj_new_int(_isPlayer);
    revives = sj_new_int(Revives);
    Sword = sj_new_int(hasSword);
    Bow = sj_new_int(hasBow);
    Spear = sj_new_int(hasSpear);
    Gauntlets = sj_new_int(hasGauntlets);
    CastCount = sj_new_int(castCount);
    AttackRank = sj_new_int(attackRank);
    EquippedWeapon = sj_new_str(thing);
    
    slog("Sprite Name: (%s)", self->sprite_name);

    sj_object_insert(json, "player", player);
    sj_object_insert(player,"sprite",sprite);
    sj_object_insert(player,"Health",health);
    sj_object_insert(player,"Gold",gold);
    sj_object_insert(player,"_isPlayer",isPlayer);
    sj_object_insert(player, "dashMax", maxDashes);
    sj_object_insert(player, "Revives", revives);
    sj_object_insert(player, "Runes", runes);
    sj_object_insert(player, "Sword", Sword);
    sj_object_insert(player, "Bow", Bow);
    sj_object_insert(player, "Spear", Spear);
    sj_object_insert(player,"Gauntlets",Gauntlets);
    sj_object_insert(player, "castCount", CastCount);
    sj_object_insert(player, "attackRank", AttackRank);
    sj_object_insert(player, "equippedWeapon", EquippedWeapon);

    sj_save(json, filename);

    slog("saved game to (%s)", filename);
    slog("Equipped Weapon: (%s)", thing);

    sj_free(json);



}
void player_set_weapon(Entity *self)
{
    if (SDL_strcmp(equippedWeapon, "Sword") && hasSpear == 1)
    {
        equippedWeapon = "Spear";
        slog("switched to spear");
        return;
    }
    if (SDL_strcmp(equippedWeapon, "Spear") && hasGauntlets == 1)
    {
        equippedWeapon = "Gauntlets";
        slog("switched to Gauntlets");
        return;
    }
    if (SDL_strcmp(equippedWeapon, "Gauntlets") && hasSword == 1)
    {
        equippedWeapon = "Sword";
        slog("switched to Sword");
        return;
    }
}

void player_die(Entity* self, Entity* other)
{
    if (Revives <= 0)
    {
        player_save(self, "config/player1.json");
        slog("player has died");
        slog("respawning at rest point");
        entity_free(self);
        self = player_new(vector2d(100, 100), "config/player1.json");
    }
    else
    {
        slog("player has died, reviving");
        self->health = maxHealth;
        SDL_Delay(1000);
        
        Revives--;
    }
}

Entity* player_get()
{
    return ent;
}

void player_set_runes(int amount)
{
    Runes += amount;
    slog("gained (%i) runes", amount);
    slog("Total Runes: (%i)", Runes);
}

void player_set_maxHealth(int amount)
{
    maxHealth += amount;
    tempHealth += amount;
}
void player_set_attackRank(int amount)
{
    attackRank += amount;
}
void player_set_speedMultiplier(float amount)
{
    speedMultiplier = amount;
}
void player_gain_dash()
{
    dashMax += 1;
    tempDashes += 1;
}
void player_gain_revives()
{
    Revives+= 1;
    tempRevives += 1;
}


//eof