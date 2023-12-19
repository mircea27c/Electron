#pragma once
#include <SDL.h>
#include "UIManager.h"
#include "vector2.h"

namespace editor_componente {
	static Componenta* componenta_selectata;

	static WindowGrafic* caseta_selectie;
	static WindowGrafic* panou_informatii;
	static Path* path_caseta_selectie;

	void InitializareEditor();

	void SelectareComponenta(Componenta* comp);

	void ActualizeazaConturCaseta();

	void DeselectareComponenta();

	void RecalculeazaGrafica();

	void ProcesareClick(int x, int y);

}