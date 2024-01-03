#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <functional>
#include "vector2.h"
#include "UIManager.h"
#include "desenatorConectori.h"
#include "TipuriComponente.h" 
#include "EditorComponente.h" 
#include "SimulatorCircuit.h" 
class Aplicatie
{public:
	SimulatorCircuit simulator;

	Buton* CreareButon(Vector2 pozitie, Vector2 dimensiune, SDL_Color culoare_buton, SDL_Color culoare_componenta, const char* path_imagine, int index_btn);
	void Simuleaza();
	bool middle_btn_apasat=false;

    Vector2 mouse_ultima_poz;

	bool InitializareAplicatie();

	void InchidereAplicatie();

	void InitializareUI();

	void ProcesareClick(SDL_Event* actiune_mouse);

	float ParteFractionara(float nr);

	void Ruleaza();

}; 

