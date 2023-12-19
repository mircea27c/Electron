#pragma once

#include <SDL.h>
#include "vector2.h"

inline void DeseneazaLinie(SDL_Renderer* renderer, Vector2 poz1, Vector2 poz2, int thickness, SDL_Color culoare) {

    SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);

	if (thickness / 2 == 0) {
		SDL_RenderDrawLine(renderer, poz1.x, poz1.y, poz2.x, poz2.y);
		return;
	}
	for (int i = -thickness/2; i < thickness / 2; i++)
	{
		SDL_RenderDrawLine(renderer, poz1.x + i, poz1.y + i, poz2.x + i, poz2.y + i);
	}
}
