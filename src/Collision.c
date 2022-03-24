#include "Collision.h"
int collision_rect_test(SDL_Rect A, SDL_Rect B) {
	if (((A.x > B.x + B.w) || (A.x + A.w < B.x)) || ((A.y + A.h < B.y) || (A.y > B.y + B.h)))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

SDL_Rect collision_box (float xc, float yc, float wc, float hc)
{
	SDL_Rect A;
	A.x = xc;
	A.y = yc;
	A.w = wc;
	A.h = hc;
	return A;
}