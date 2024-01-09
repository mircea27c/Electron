#pragma once

#include <SDL.h>
#include "vector2.h"
#include "math.h"


 inline void DeseneazaLinie(SDL_Renderer* renderer, Vector2 poz1, Vector2 poz2, int thickness, SDL_Color culoare) {

    //SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);

	//SDL_Color culoare_umbra = SDL_Color{(unsigned char)std::max(0,culoare.r - 50), (unsigned char)std::max(0,culoare.g - 50) ,(unsigned char)std::max(0,culoare.b - 50) ,255};

	if (thickness / 2 == 0) {

		//SDL_SetRenderDrawColor(renderer, culoare_umbra.r, culoare_umbra.g, culoare_umbra.b, culoare_umbra.a);
		//SDL_RenderDrawLine(renderer, poz1.x + 1, poz1.y + 1, poz2.x + 1, poz2.y + 1);
		//SDL_RenderDrawLine(renderer, poz1.x - 1, poz1.y - 1, poz2.x - 1, poz2.y - 1);
		SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
		SDL_RenderDrawLine(renderer, poz1.x, poz1.y, poz2.x, poz2.y);
		return;
	}

	Vector2 dir_linie = poz2 - poz1;
	float lungime_linie = sqrt(dir_linie.x*dir_linie.x + dir_linie.y * dir_linie.y);
	Vector2 dir_linie_normalizat = dir_linie / lungime_linie;

	Vector2 perp_linie = Vector2(dir_linie_normalizat.y, -dir_linie_normalizat.x);

	//SDL_SetRenderDrawColor(renderer, culoare_umbra.r, culoare_umbra.g, culoare_umbra.b, culoare_umbra.a);
	//SDL_RenderDrawLine(renderer, poz1.x - thickness/2 - 1, poz1.y - thickness / 2 - 1, poz2.x - thickness / 2 - 1, poz2.y - thickness / 2 - 1);
	//SDL_RenderDrawLine(renderer, poz1.x + thickness / 2, poz1.y + thickness / 2, poz2.x + thickness / 2, poz2.y + thickness / 2);

	SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
	for (int i = -thickness/2; i < thickness / 2; i++)
	{
		Vector2 offset = perp_linie * i;
		SDL_RenderDrawLine(renderer, poz1.x + offset.x, poz1.y + offset.y, poz2.x + offset.x, poz2.y + offset.y);
	}
}
//
//inline void DeseneazaLinie(SDL_Renderer* renderer, Vector2 poz1, Vector2 poz2, int thickness, SDL_Color culoare) {
//    // linia principală
//    SDL_SetRenderDrawColor(renderer, culoare.r, culoare.g, culoare.b, culoare.a);
//    SDL_RenderDrawLine(renderer, poz1.x, poz1.y, poz2.x, poz2.y);
//
//    if (thickness > 1) {
//        float lungime = sqrt(pow(poz2.x - poz1.x, 2) + pow(poz2.y - poz1.y, 2));
//        float unghi = atan2(poz2.y - poz1.y, poz2.x - poz1.x);
//        float offsetX = (thickness / 2) * sin(unghi);
//        float offsetY = (thickness / 2) * cos(unghi);
//
//        offsetX /= lungime;
//        offsetY /= lungime;
//
//        //  linii suplimentare pentru grosime
//        for (int i = 1; i <= thickness / 2; ++i) {
//            float factor = i;
//            SDL_RenderDrawLine(renderer,
//                poz1.x - (offsetX * factor), poz1.y + (offsetY * factor),
//                poz2.x - (offsetX * factor), poz2.y + (offsetY * factor));
//            SDL_RenderDrawLine(renderer,
//                poz1.x + (offsetX * factor), poz1.y - (offsetY * factor),
//                poz2.x + (offsetX * factor), poz2.y - (offsetY * factor));
//        }
//    }
//    else {
//        
//    }
//}
