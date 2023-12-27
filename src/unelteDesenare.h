#pragma once

#include <SDL.h>
#include "vector2.h"
#include "math.h"


inline void DeseneazaLinie(SDL_Renderer* renderer, Vector2 poz1, Vector2 poz2, int thickness, SDL_Color culoare) {

    //SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);

	SDL_Color culoare_umbra = SDL_Color{(unsigned char)std::max(0,culoare.r - 50), (unsigned char)std::max(0,culoare.g - 50) ,(unsigned char)std::max(0,culoare.b - 50) ,255};

	if (thickness / 2 == 0) {

		SDL_SetRenderDrawColor(renderer, culoare_umbra.r, culoare_umbra.g, culoare_umbra.b, culoare_umbra.a);
		SDL_RenderDrawLine(renderer, poz1.x + 1, poz1.y + 1, poz2.x + 1, poz2.y + 1);
		SDL_RenderDrawLine(renderer, poz1.x - 1, poz1.y - 1, poz2.x - 1, poz2.y - 1);
		SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
		SDL_RenderDrawLine(renderer, poz1.x, poz1.y, poz2.x, poz2.y);
		return;
	}

	SDL_SetRenderDrawColor(renderer, culoare_umbra.r, culoare_umbra.g, culoare_umbra.b, culoare_umbra.a);
	SDL_RenderDrawLine(renderer, poz1.x - thickness/2 - 1, poz1.y - thickness / 2 - 1, poz2.x - thickness / 2 - 1, poz2.y - thickness / 2 - 1);
	SDL_RenderDrawLine(renderer, poz1.x + thickness / 2, poz1.y + thickness / 2, poz2.x + thickness / 2, poz2.y + thickness / 2);

	SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
	for (int i = -thickness/2; i < thickness / 2; i++)
	{
		SDL_RenderDrawLine(renderer, poz1.x + i, poz1.y + i, poz2.x + i, poz2.y + i);
	}
}
