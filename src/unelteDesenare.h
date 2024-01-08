#pragma once

#include <SDL.h>
#include "vector2.h"
#include "math.h"

/*
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
*/
inline void DeseneazaLinie(SDL_Renderer* renderer, Vector2 poz1, Vector2 poz2, int thickness, SDL_Color culoare) {
    // linia principală
    SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
    SDL_RenderDrawLine(renderer, poz1.x, poz1.y, poz2.x, poz2.y);

    if (thickness > 1) {
        float lungime = sqrt(pow(poz2.x - poz1.x, 2) + pow(poz2.y - poz1.y, 2));
        float unghi = atan2(poz2.y - poz1.y, poz2.x - poz1.x);
        float offsetX = (thickness / 2) * sin(unghi);
        float offsetY = (thickness / 2) * cos(unghi);

        //  linii suplimentare pentru grosime
        for (int i = 1; i <= thickness / 2; ++i) {
            float factor = i * 2;
            SDL_RenderDrawLine(renderer,
                poz1.x - (offsetX * factor), poz1.y + (offsetY * factor),
                poz2.x - (offsetX * factor), poz2.y + (offsetY * factor));
            SDL_RenderDrawLine(renderer,
                poz1.x + (offsetX * factor), poz1.y - (offsetY * factor),
                poz2.x + (offsetX * factor), poz2.y - (offsetY * factor));
        }
    }
}
