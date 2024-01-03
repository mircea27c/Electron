#pragma once
#include <SDL.h>

class Grid {
public:
	static const int MARIME_CELULA = 120;
	static const int GRID_CELULE_LATIME = 20;
	static const int GRID_CELULE_INALTIME = 20;

	static const int MARIME_PCT_CONEX_LIBER = 15;
	static const int MARIME_PCT_CONEX_OCUPAT = 10;
	#define CUL_PCT_CONEX_INPUT SDL_Color{ 0, 110, 220};
	#define CUL_PCT_CONEX_OUTPUT SDL_Color{ 255,165,0 };
	#define CUL_PCT_CONEX_OCUPAT SDL_Color{ 50,50,200,255};

	#define CUL_SELECTIE SDL_Color{ 230,230,150,255};

};