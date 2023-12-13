#pragma once

#include <SDL.h>
#include "vector2.h"

inline void DeseneazaLinie(SDL_Renderer* rend, Vector2 poz1, Vector2 poz2, int grosime) {


    Vector2 dirLinie = poz2 - poz1;
    Vector2 perpendicular = Vector2{ dirLinie.x * grosime, -dirLinie.y * grosime };

    SDL_RenderDrawLine(rend, (poz1 + perpendicular).x, (poz1 + perpendicular).y, (poz2 + perpendicular).x, (poz2 + perpendicular).y);
    SDL_RenderDrawLine(rend, (poz1 - perpendicular).x, (poz1 - perpendicular).y, (poz2 - perpendicular).x, (poz2 - perpendicular).y);
}
