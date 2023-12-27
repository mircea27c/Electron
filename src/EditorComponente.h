#pragma once
#include <SDL.h>
#include "UIManager.h"
#include "vector2.h"

namespace editor_componente {
	static Componenta* componenta_selectata;

	static WindowGrafic* caseta_selectie;
	static Path* path_caseta_selectie;

	static WindowGrafic* panou_info;
	static TextGrafic* panou_info_text;
	static ImagineGrafica* panou_info_img;

	void InitializareEditor();

	Buton* CreazaButon(Vector2 pozitie, Vector2 dimensiuni, const char* text, SDL_Color culoare, SDL_Color culoare_text, ClickFunct actiune);

	void SelectareComponenta(Componenta* comp);

	void ActualizeazaConturCaseta();

	void ActualizeazaPanouInformatii();

	void DeselectareComponenta();

	void RecalculeazaGrafica();

	void ProcesareClick(int x, int y);

	void StergeComponentaSelectata();
	void RotesteComponentaSelectata();
}