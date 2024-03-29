#pragma once
#include "UIManager.h"
#include "TipuriComponente.h"

namespace pozitionator_componente {
	static Componenta* component_selectat = NULL;
	static ImagineGrafica* component_preview = NULL;

	static int grid_ultim_x;
	static int grid_ultim_y;

	static bool se_plaseaza;

	void SelectareComponentaPozitionare(int index);

	void SelectareComponentaPozitionare(Componenta* comp);

	void ProcesarePlasare();

	void ProcesareClickPlasare();
}