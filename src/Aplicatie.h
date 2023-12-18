#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <functional>
#include "vector2.h"
#include "UIManager.h"
#include "pozitionatorComponente.h"
#include "desenatorConectori.h"
class Aplicatie
{public:
	bool middle_btn_apasat=false;

    Vector2 mouse_ultima_poz;

	static void StartPlasare();

	bool InitializareAplicatie();

	void InchidereAplicatie();



	void InitializareUI();

	void ProcesareClick(SDL_Event* actiune_mouse);

	float ParteFractionara(float nr);

	void Ruleaza();

	void SelecteazaComponenta(int index);
}; 
