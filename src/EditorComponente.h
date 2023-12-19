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

	void SelectareComponenta(Componenta* comp);

	void ActualizeazaConturCaseta();

	void ActualizeazaPanouInformatii();

	void DeselectareComponenta();

	void RecalculeazaGrafica();

	void ProcesareClick(int x, int y);

	void StergeComponentaSelectata();

}