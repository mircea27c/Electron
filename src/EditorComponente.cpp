#include "EditorComponente.h"

Componenta* componenta_selectata = NULL;


WindowGrafic* caseta_selectie;
Path* path_caseta_selectie;

WindowGrafic* panou_info;
TextGrafic* panou_info_text;
ImagineGrafica* panou_info_img;


void editor_componente::InitializareEditor() {
	path_caseta_selectie = new Path();
	path_caseta_selectie->culoare = CUL_SELECTIE;

	caseta_selectie = new WindowGrafic();
	caseta_selectie->AdaugaElementGrafic(path_caseta_selectie);

	int latime_caseta_fixa = 300;
	int padding = 25;
	float inaltime_caseta_relativa = 0.5;

	SDL_Color cul_secund = SDL_Color{ 65,61,77 };
	SDL_Color cul_primar = SDL_Color{92,88,107};

	DreptunghiGrafic* bg_panou_info = new DreptunghiGrafic();
	bg_panou_info->culoare = cul_secund;
	bg_panou_info->marime = 1;
	bg_panou_info->dimensiuni = Vector2((float)latime_caseta_fixa, INALTIME * inaltime_caseta_relativa);
	bg_panou_info->pozitie = Vector2((float)(LATIME - latime_caseta_fixa/2), INALTIME * inaltime_caseta_relativa/2);

	DreptunghiGrafic* caseta_nume = new DreptunghiGrafic();
	caseta_nume->culoare = cul_primar;
	caseta_nume->marime = 1;
	caseta_nume->dimensiuni = Vector2(latime_caseta_fixa - padding*2, INALTIME * 0.05);
	caseta_nume->pozitie = Vector2(LATIME - latime_caseta_fixa/2, padding + INALTIME * 0.025);

	panou_info_text = new TextGrafic();
	panou_info_text->culoare = SDL_Color{ 255,255,255,255 };
	panou_info_text->marime = 1;
	panou_info_text->dimensiuni = caseta_nume->dimensiuni;
	panou_info_text->pozitie = caseta_nume->pozitie;


	panou_info_img = new ImagineGrafica();
	panou_info_img->marime = 1;
	panou_info_img->dimensiuni = Vector2((float)latime_caseta_fixa - padding * 2, (float)latime_caseta_fixa - padding * 2);
	panou_info_img->pozitie = Vector2((float)(LATIME - latime_caseta_fixa/2), padding + INALTIME * 0.025 + padding + panou_info_img->dimensiuni.x/2);


	panou_info = new WindowGrafic();
	panou_info->AdaugaElementGrafic(bg_panou_info);
	panou_info->AdaugaElementGrafic(caseta_nume);
	panou_info->AdaugaElementGrafic(panou_info_text);
	panou_info->AdaugaElementGrafic(panou_info_img);

	Buton* buton_stergere = new Buton(Vector2(panou_info_img->pozitie.x, panou_info_img->pozitie.y + padding+ panou_info_img->dimensiuni.y/2), Vector2(panou_info_img->dimensiuni.x, 60.0f), StergeComponentaSelectata);
	DreptunghiGrafic* bg_btn_sters = new DreptunghiGrafic();
	bg_btn_sters->marime = 1;
	bg_btn_sters->dimensiuni = buton_stergere->dimensiuni;
	bg_btn_sters->pozitie = buton_stergere->pozitie;
	bg_btn_sters->culoare = SDL_Color{ 128,41,29 };

	TextGrafic* text_btn_sters = new TextGrafic();
	text_btn_sters->marime = 1;
	text_btn_sters->dimensiuni = buton_stergere->dimensiuni;
	text_btn_sters->pozitie = buton_stergere->pozitie;
	text_btn_sters->text = "Sterge";
	text_btn_sters->culoare = SDL_Color{ 219,121,107};

	buton_stergere->AdaugaElementGrafic(bg_btn_sters);
	buton_stergere->AdaugaElementGrafic(text_btn_sters);
	buton_stergere->marime = 1;

	panou_info->AdaugaButon(buton_stergere);

	refresh_ui_listeners.push_back(RecalculeazaGrafica);
}
void editor_componente::SelectareComponenta(Componenta* comp) {
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

	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x + jum_celula, poz_comp.y - jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x + jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y + jum_celula));
	path_caseta_selectie->pozitii.push_back(Vector2( poz_comp.x - jum_celula, poz_comp.y - jum_celula));
}

void editor_componente::ActualizeazaPanouInformatii() {
	const char* path_componenta = ((ImagineGrafica*)componenta_selectata->grafica)->path;
	panou_info_img->path = path_componenta;

	const char* start_nume = strchr(path_componenta, '/');
	const char* end_nume = strchr(start_nume, '.');

	int lungime = end_nume - start_nume - 1;
	char* text_nume = new char[lungime + 1];
	strncpy(text_nume, start_nume + 1, lungime);
	panou_info_text->text = text_nume;
	text_nume[lungime] = '\0';
}

void editor_componente::RecalculeazaGrafica() {
	ActualizeazaConturCaseta();
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

void editor_componente::StergeComponentaSelectata(){
	if (componenta_selectata == NULL)return;
	EliminaComponenta(componenta_selectata);
	//delete componenta_selectata;
}
