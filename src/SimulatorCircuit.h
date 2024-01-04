#pragma once
#include <iostream>
#include <set>
#include <queue>
#include <SDL.h>
#include "Componente.h"
#include "UIManager.h"


class SimulatorCircuit
{

	SDL_Color cul_curent = SDL_Color{10,247,255};

	bool reset = false;
	bool pauza = false;

	int interval_pas = 250;
	int timp_pas = 0;

	std::queue<Componenta*> de_vizitat;
	
	
	void Reseteaza();
public:
	void Simuleaza();
	
	void Pauza();

	void Stop();

	void ParcurgePas(float timp_trecut);

	SimulatorCircuit() {
		reset = false;
		pauza = false;
	}

};

inline bool CuloriEgale(SDL_Color col1, SDL_Color col2) {
	return (col1.r == col1.r && col1.g == col2.g && col2.b == col2.b);
}

