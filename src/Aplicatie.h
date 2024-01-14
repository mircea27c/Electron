#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <functional>
#include <chrono>
#include "vector2.h"
#include "UIManager.h"
#include "desenatorConectori.h"
#include "TipuriComponente.h" 
#include "EditorComponente.h" 
#include "SimulatorCircuit.h" 
#include "Screenshotter.h"
#include "EcranPrincipal.h"
#include "Tooltip.h"
#include "SaveLoad.h"
class Aplicatie{

	bool refreshUI_urm_frame = false;
public:
	bool running;
	enum ECRAN {START, EDITOR};
	ECRAN ecran_activ;
	SimulatorCircuit* simulator = NULL;

	EcranPrincipal* ecran_principal = NULL;

	Buton* CreareButon(Vector2 pozitie, Vector2 dimensiune, SDL_Color culoare_buton, SDL_Color culoare_componenta, const char* path_imagine, int index_btn, const char* nume);
	bool middle_btn_apasat=false;

    Vector2 mouse_ultima_poz;

	bool InitializareAplicatie();

	void InchidereAplicatie();

	void InitializareUI();

	void SaveLoadUI();

	void ProcesareClick(SDL_Event* actiune_mouse);

	float ParteFractionara(float nr);

	void Ruleaza();

	void RuleazaEditor(SDL_Event& actiune_input);
	void RuleazaEcranPrincipal(SDL_Event& actiune_input);

	void SchimbaEcranActiv(Aplicatie::ECRAN ecran_nou);

}; 

