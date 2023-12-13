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


	inline void StartConectare(PunctConexiune* pct_start) {
		conector_desenat = new Conector();
		conector_desenat->start_conexiune = pct_start;

		Path* path = new Path();
		conector_desenat->grafica = path;

		se_deseneaza_conector = true;

		cout << "start conectare";
	}
	inline void StopConectare() {



		se_deseneaza_conector = false;
		InregistreazaComponenta(conector_desenat);
		conector_desenat = NULL;
	}

	inline void InitializareDesenatorConectori() {
		callback_slectare_pct_conex = StartConectare;
	}

	inline void ProcesareConectare() {
		if (!se_deseneaza_conector)return;
		if (conector_desenat == NULL)return;

		Vector2 gridPos = PozitieMouseInGrid();
		if (grid_ultim_x != gridPos.x || grid_ultim_y != gridPos.y) {

		}
		else {
			return;
		}
		//in functie de pozitia mouseului, determina celula din tabel in care se afla Componenta

		if (gridPos.x != -1) {
			RefreshUI();	
			conector_desenat->pozitii.push_back(gridPos);
			ActualizeazaGraficaComponenta(conector_desenat);

			conector_desenat->grafica->Desenare(GetCurrentRenderer());
			SDL_RenderPresent(GetCurrentRenderer());
		}
		grid_ultim_x = gridPos.x;
		grid_ultim_y = gridPos.y;
	}

	inline void ProcesareStopClickDesenare() {
		if (!se_deseneaza_conector || conector_desenat == NULL)return;
		StopConectare();
	}

}