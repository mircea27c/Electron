#pragma once
#include <SDL.h>
#include "vector2.h"
#include "ElementeGrafice.h"
#include "Componente.h"
#include "UIManager.h"


namespace desenator_conectori {

	static Conector* conector_desenat;
	static bool se_deseneaza_conector = false;
	static int grid_ultim_x;
	static int grid_ultim_y;


	void StartConectare(PunctConexiune* pct_start);
	void StopConectare();

	void InitializareDesenatorConectori();
	void ProcesareFinalizareConectare(int mouse_x, int mouse_y);
	void ProcesareConectare();
	void ProcesareStopClickDesenare();

}