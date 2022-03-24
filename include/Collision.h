#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "gfc_vector.h"
#include "simple_logger.h"

typedef struct {
	float x,y;
	float w, h;

}Rect;

/**
* @brief test if rect collides with other rect
* @param 
*/
int collision_rect_test(SDL_Rect A, SDL_Rect B);

SDL_Rect collision_box(float xc, float yc, float wc, float hc);
#endif // !__COLLISION_H__

