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
class Aplicatie
{public:
	bool middle_btn_apasat=false;

    Vector2 mouse_ultima_poz;

	bool InitializareAplicatie();

	void InchidereAplicatie();

	void InitializareUI();

	void ProcesareClick(SDL_Event* actiune_mouse);

	float ParteFractionara(float nr);

	void Ruleaza();

}; 
