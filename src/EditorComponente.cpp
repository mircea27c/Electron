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


	//CREAREA BUTOANELOR DE EDITARE

	int nr_btn = 3;//3 butoane
	float latime_btn = (latime_caseta_fixa - 2 * padding - (nr_btn - 1) * padding) / (float)nr_btn;
	float inaltime_btn = 60;

	float poz_x_1 = LATIME - latime_caseta_fixa + padding*1 + latime_btn / 2 + latime_btn * 0;
	float poz_x_2 = LATIME - latime_caseta_fixa + padding*2 + latime_btn / 2 + latime_btn * 1;
	float poz_x_3 = LATIME - latime_caseta_fixa + padding*3 + latime_btn / 2 + latime_btn * 2;

	float poz_y = panou_info_img->pozitie.y + padding + panou_info_img->dimensiuni.y / 2;

	Buton* btn_stergere = CreazaButon(Vector2(poz_x_1, poz_y), Vector2(latime_btn, inaltime_btn), "Sterge", SDL_Color{ 128,41,29 }, SDL_Color{ 228,141,129 }, StergeComponentaSelectata);
	Buton* btn_rotatie = CreazaButon(Vector2(poz_x_2, poz_y), Vector2(latime_btn, inaltime_btn), "Roteste", SDL_Color{ 150,150,200 }, SDL_Color{ 255,255,255 }, RotesteComponentaSelectata);


	panou_info->AdaugaButon(btn_stergere);
	panou_info->AdaugaButon(btn_rotatie);

	refresh_ui_listeners.push_back(RecalculeazaGrafica);
}
Buton* editor_componente::CreazaButon(Vector2 pozitie, Vector2 dimensiuni, const char* text, SDL_Color culoare,SDL_Color culoare_text, ClickFunct actiune)
{
	Buton* buton_nou = new Buton(pozitie, dimensiuni, actiune);
	DreptunghiGrafic* bg_btn_sters = new DreptunghiGrafic();
	bg_btn_sters->marime = 1;
	bg_btn_sters->dimensiuni = dimensiuni;
	bg_btn_sters->pozitie = pozitie;
	bg_btn_sters->culoare = culoare;

	TextGrafic* text_btn_sters = new TextGrafic();
	text_btn_sters->marime = 1;
	text_btn_sters->dimensiuni = dimensiuni;
	text_btn_sters->pozitie = pozitie;
	text_btn_sters->text = text;
	text_btn_sters->culoare = culoare_text;

	buton_nou->AdaugaElementGrafic(bg_btn_sters);
	buton_nou->AdaugaElementGrafic(text_btn_sters);
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

	if (Conector* conector = dynamic_cast<Conector*>(componenta_apasata)) {
		DeselectareComponenta();
		return;
	}
	if (componenta_apasata != NULL) {
		SelectareComponenta(componenta_apasata);
	}
}

void editor_componente::StergeComponentaSelectata(){
	if (componenta_selectata == NULL)return;
	EliminaComponenta(componenta_selectata);
		
	//elimina toti conectorii componentei
	for (int i = 0; i < componenta_selectata->nr_pct_conexiune; i++)
	{
		if (componenta_selectata->puncte_conexiune[i].conector != NULL) {
			EliminaComponenta(componenta_selectata->puncte_conexiune[i].conector);
		}
	}

	delete componenta_selectata;
	DeselectareComponenta();
}

void editor_componente::RotesteComponentaSelectata() {
	if (componenta_selectata == NULL)return;
	componenta_selectata->rotatie=(ORIENTARE)((componenta_selectata->rotatie + 1)% 4);
	RefreshUI();
}
