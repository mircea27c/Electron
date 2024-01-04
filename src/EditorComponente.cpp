#include "EditorComponente.h"

Componenta* componenta_selectata = NULL;


WindowGrafic* caseta_selectie;
Path* path_caseta_selectie;

WindowGrafic* panou_info;


void editor_componente::InitializareEditor() {

	//CREAREA BUTOANELOR DE EDITARE
	inaltime_caseta_info = 80;
	latime_caseta_info = 280;
	padding = 10;
	
	
	path_caseta_selectie = new Path();
	path_caseta_selectie->culoare = CUL_SELECTIE;

	caseta_selectie = new WindowGrafic();
	caseta_selectie->AdaugaElementGrafic(path_caseta_selectie);


	SDL_Color cul_primar = SDL_Color{ 25,25,25,25 };

	DreptunghiGrafic* bg_panou_info = new DreptunghiGrafic();
	bg_panou_info->culoare = cul_primar;
	bg_panou_info->marime = 1;
	bg_panou_info->dimensiuni = Vector2((float)latime_caseta_info, (float)inaltime_caseta_info);

	panou_info = new WindowGrafic();
	panou_info->AdaugaElementGrafic(bg_panou_info);


	nr_btn = 4;
	latime_btn = (latime_caseta_info - (nr_btn + 1) * padding )/ nr_btn;
	inaltime_btn = inaltime_caseta_info - 2 * padding;

	Buton* btn_stergere = CreazaButon(Vector2(0, 0), Vector2(latime_btn, inaltime_btn), "Iconite/delete_icon.bmp", SDL_Color{ 70,49,49,255 }, SDL_Color{ 178,178,178 ,255 }, StergeComponentaSelectata);
	Buton* btn_rotatie = CreazaButon(Vector2(0, 0), Vector2(latime_btn, inaltime_btn), "Iconite/rotate_icon.bmp", SDL_Color{ 49,49,49,255 }, SDL_Color{ 178,178,178,255 }, RotesteComponentaSelectata);
	Buton* btn_mutare = CreazaButon(Vector2(0, 0), Vector2(latime_btn, inaltime_btn), "Iconite/move_icon.bmp", SDL_Color{ 49,49,49,255 }, SDL_Color{ 178,178,178,255 }, MutaComponentaSelectata);
	Buton* btn_sterge_legaturi = CreazaButon(Vector2(0, 0), Vector2(latime_btn, inaltime_btn), "Iconite/cut.bmp", SDL_Color{ 49,49,49,255 }, SDL_Color{ 178,178,178,255 }, StergeLegaturiComponentaSelectata);

	panou_info->AdaugaButon(btn_mutare);
	panou_info->AdaugaButon(btn_rotatie);
	panou_info->AdaugaButon(btn_sterge_legaturi);
	panou_info->AdaugaButon(btn_stergere);

	refresh_ui_listeners.push_back(RecalculeazaGrafica);
}
Buton* editor_componente::CreazaButon(Vector2 pozitie, Vector2 dimensiuni, const char* path, SDL_Color culoare, SDL_Color culoare_text, ClickFunct actiune)
{
	Buton* buton_nou = new Buton(pozitie, dimensiuni, actiune);
	DreptunghiGrafic* bg_btn_sters = new DreptunghiGrafic();
	bg_btn_sters->marime = 1;
	bg_btn_sters->dimensiuni = dimensiuni;
	bg_btn_sters->pozitie = pozitie;
	bg_btn_sters->culoare = culoare;

	ImagineGrafica* img_btn = new ImagineGrafica();
	img_btn->marime = 1;
	img_btn->dimensiuni = dimensiuni + Vector2(-10,-10);
	img_btn->pozitie = pozitie;
	img_btn->path = path;
	img_btn->culoare = culoare_text;

	buton_nou->AdaugaElementGrafic(bg_btn_sters);
	buton_nou->AdaugaElementGrafic(img_btn);
	buton_nou->marime = 1;

	return buton_nou;
}
void editor_componente::SelectareComponenta(Componenta* comp) {
	if (componenta_selectata != NULL)DeselectareComponenta();

	componenta_selectata = comp;
	ActualizeazaConturCaseta();
	ActualizeazaPanouInformatii();


	InregistreazaWindowGrafic(caseta_selectie);
	InregistreazaWindowGrafic(panou_info);

	RefreshUI();
}
void editor_componente::DeselectareComponenta() {
	componenta_selectata = NULL;

	EliminaWindowGrafic(caseta_selectie);
	EliminaWindowGrafic(panou_info);

	RefreshUI();
}

void editor_componente::ActualizeazaConturCaseta() {
	if (componenta_selectata == NULL)return;
	path_caseta_selectie->pozitii.clear();

	Vector2 poz_comp = componenta_selectata->grafica->pozitie;

	float jum_celula = Grid::MARIME_CELULA * factor_zoom / 2;

	path_caseta_selectie->marime = factor_zoom;

	path_caseta_selectie->pozitii.push_back(Vector2(poz_comp.x - jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2(poz_comp.x + jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2(poz_comp.x + jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2(poz_comp.x - jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2(poz_comp.x - jum_celula, poz_comp.y - jum_celula));
}

void editor_componente::ActualizeazaPanouInformatii() {

	if (componenta_selectata == NULL)return;

	int y_poz = componenta_selectata->grafica->pozitie.y + Grid::MARIME_CELULA * factor_zoom * 0.5f + inaltime_caseta_info / 2;
	int x_poz = componenta_selectata->grafica->pozitie.x;

	int start_x = x_poz - latime_caseta_info / 2;

	for (auto& el : panou_info->elem_grafice)
	{
		el->pozitie.x = x_poz;
		el->pozitie.y = y_poz;
	}

	int i = 0;
	for (auto &btn: panou_info->butoane)
	{
		
		btn->pozitie.x = start_x +  (i + 1) * padding + latime_btn / 2 + i * latime_btn;
		btn->pozitie.y = y_poz;
	
		for (auto &el: btn->ListaElementeGrafice)
		{
			el->pozitie.x = btn->pozitie.x;
			el->pozitie.y = btn->pozitie.y;
		}

		i++;
	}


}

void editor_componente::RecalculeazaGrafica() {
	ActualizeazaConturCaseta();
	ActualizeazaPanouInformatii();
}

void editor_componente::ProcesareClick(int x, int y) {

	Vector2 poz_mouse = PozitieMouseInGrid();

	Componenta* componenta_apasata = VerificaColiziuneComponenta(poz_mouse);

	if (Conector* conector = dynamic_cast<Conector*>(componenta_apasata)) {
		DeselectareComponenta();
		return;
	}
	if (componenta_apasata != NULL) {
		SelectareComponenta(componenta_apasata);
	}
	else {
		DreptunghiGrafic* bg = (DreptunghiGrafic*)panou_info->elem_grafice.front();
		if(x >= bg->pozitie.x - (int)(bg->dimensiuni.x * bg->marime) / 2 && x <= bg->pozitie.x + (int)(bg->dimensiuni.x * bg->marime) / 2 && y >= bg->pozitie.y - (int)(bg->dimensiuni.y * bg->marime) / 2 && y <= bg->pozitie.y + (int)(bg->dimensiuni.y * bg->marime) / 2){		
		}
		else {	
			DeselectareComponenta();
		}
	}
}

void editor_componente::StergeComponentaSelectata() {
	if (componenta_selectata == NULL)return;
	EliminaComponenta(componenta_selectata);

	StergeLegaturiComponenta(componenta_selectata);

	delete componenta_selectata;
	DeselectareComponenta();
}

void editor_componente::StergeLegaturiComponenta(Componenta* comp) {
	//elimina toti conectorii componentei
	for (int i = 0; i < comp->nr_pct_conexiune; i++)
	{
		if (comp->puncte_conexiune[i].conector != NULL) {
			EliminaComponenta(comp->puncte_conexiune[i].conector);
		}
	}
	comp->StergeLegaturi();
}

void editor_componente::RotesteComponentaSelectata() {
	if (componenta_selectata == NULL)return;
	componenta_selectata->rotatie = (ORIENTARE)((componenta_selectata->rotatie + 1) % 4);
	RefreshUI();

}

void editor_componente::MutaComponentaSelectata() {
	if (componenta_selectata == NULL)return;
	pozitionator_componente::SelectareComponentaPozitionare(componenta_selectata);
	StergeComponentaSelectata();
}

void editor_componente::StergeLegaturiComponentaSelectata() {
	if (componenta_selectata == NULL)return;
	StergeLegaturiComponenta(componenta_selectata);
	RefreshUI();
}