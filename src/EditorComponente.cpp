#include "EditorComponente.h"

Componenta* componenta_selectata = NULL;


WindowGrafic* caseta_selectie;
Path* path_caseta_selectie;
WindowGrafic* panou_informatii;


void editor_componente::InitializareEditor() {
	path_caseta_selectie = new Path();
	path_caseta_selectie->culoare = CUL_SELECTIE;

	caseta_selectie = new WindowGrafic();
	caseta_selectie->AdaugaElementGrafic(path_caseta_selectie);

	int latime_caseta_fixa = 300;
	int padding = 25;
	//int inaltime_caseta_relativa = 0.5;

	SDL_Color cul_secund = SDL_Color{ 65,61,77 };
	SDL_Color cul_primar = SDL_Color{92,88,107};

	DreptunghiGrafic* bg_panou_info = new DreptunghiGrafic();
	bg_panou_info->culoare = cul_secund;
	bg_panou_info->marime = 1;
	bg_panou_info->dimensiuni = Vector2(latime_caseta_fixa, INALTIME * 0.7);
	bg_panou_info->pozitie = Vector2(LATIME - latime_caseta_fixa/2, INALTIME * 0.35);

	DreptunghiGrafic* caseta_nume = new DreptunghiGrafic();
	caseta_nume->culoare = cul_primar;
	caseta_nume->marime = 1;
	caseta_nume->dimensiuni = Vector2(latime_caseta_fixa - padding*2, INALTIME * 0.05);
	caseta_nume->pozitie = Vector2(LATIME - latime_caseta_fixa/2, padding + INALTIME * 0.025);

	panou_informatii = new WindowGrafic();
	panou_informatii->AdaugaElementGrafic(bg_panou_info);
	panou_informatii->AdaugaElementGrafic(caseta_nume);


	refresh_ui_listeners.push_back(RecalculeazaGrafica);
}
void editor_componente:: SelectareComponenta(Componenta* comp) {
	componenta_selectata = comp;
	ActualizeazaConturCaseta();

	InregistreazaWindowGrafic(caseta_selectie);
	InregistreazaWindowGrafic(panou_informatii);

	RefreshUI();
}
void editor_componente::DeselectareComponenta() {
	componenta_selectata = NULL;

	EliminaWindowGrafic(caseta_selectie);
	EliminaWindowGrafic(panou_informatii);

	RefreshUI();
}


void editor_componente::ActualizeazaConturCaseta() {
	if (componenta_selectata == NULL)return;
	path_caseta_selectie->pozitii.clear();

	Vector2 poz_comp = componenta_selectata->grafica->pozitie;

	float jum_celula = Grid::MARIME_CELULA * factor_zoom / 2;

	path_caseta_selectie->marime = factor_zoom;

	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x + jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x + jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y - jum_celula));
}


void editor_componente::RecalculeazaGrafica() {
	ActualizeazaConturCaseta();
}

void editor_componente::ProcesareClick(int x, int y) {

	Vector2 poz_mouse = PozitieMouseInGrid();

	Componenta* componenta_apasata = VerificaColiziuneComponenta(poz_mouse);

	if (componenta_apasata != NULL) {
		SelectareComponenta(componenta_apasata);
	}
	else {
		if (componenta_selectata != NULL) {
			DeselectareComponenta();
		}
	}
}
