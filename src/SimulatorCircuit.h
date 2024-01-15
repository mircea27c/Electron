#pragma once
#include <iostream>
#include <set>
#include <queue>
#include <SDL.h>
#include <string>
#include "Componente.h"
#include "UIManager.h"


class SimulatorCircuit
{

	SDL_Color cul_curent = SDL_Color{10,247,255};

	bool reset = false;
	bool pauza = false;

	int interval_pas = 250;//0.25 secunde adica 250 milisecunde
	int interval_normal = 250;//cand viteza e 1, interval e 250

	float viteze[7] = {0.2, 0.5, 0.75, 1, 1.5, 2, 5};

	int nr_viteze = 7;
	int index_viteza = 3;


	int timp_pas = 0;

	std::queue<Componenta*> de_vizitat;
	
	void RecalculeazaViteza();
	void Reseteaza();
public:
	void Simuleaza();
	
	void Pauza();

	void Stop();

	void ParcurgePas(float timp_trecut);

	void CresteViteza();
	
	void ScadeViteza();

	string text_viteza;

	SimulatorCircuit() {
		reset = false;
		pauza = false;

	}

};


