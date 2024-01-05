#pragma once
#include <SDL.h>
#include "UIManager.h"
#include "ElementeGrafice.h"

class Aplicatie;

class EcranPrincipal {
	WindowGrafic* window_ecran;

	SDL_Color culoare_highlight = SDL_Color{255,255,255};
	SDL_Color culoare_normala = SDL_Color{0,100,100 };

public:

	void Initializare(ClickFunct actiune_schimba_ecran, ClickFunct actiune_inchidere);

	void RefreshUI();

	void ProceseazaMouse(SDL_Event* event);


};


