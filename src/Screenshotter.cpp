#include "Screenshotter.h"

void CapturaScreenshot(const char* filename, SDL_Window* window, SDL_Renderer* renderer, int width, int height)
{
    width--;

    SDL_Rect captureArea;
    SDL_RenderGetViewport(renderer, &captureArea);

    //zona de captura de pe ecran
    captureArea.x = (captureArea.w - width) / 2 + 1;
    captureArea.y = (captureArea.h - height) / 2 + 1;
    captureArea.w = width;
    captureArea.h = height;


    //surfaceul screenshotului
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    //se transfera imaginea de pe ecran pe screenshot
    SDL_RenderReadPixels(renderer, &captureArea, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

    SDL_SaveBMP(surface, filename);


    SDL_FreeSurface(surface);
}