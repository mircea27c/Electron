#pragma once
#include <SDL.h>
#include <iostream>

void CapturaScreenshot(const char* filename, SDL_Window* window, SDL_Renderer* renderer, int w, int h);