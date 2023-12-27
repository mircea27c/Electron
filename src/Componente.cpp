#include "Componente.h"

Vector2 Componenta::GetPozitie() { return pozitie_in_grid; }

Componenta::Componenta(Componenta* tip) {
	id = "clona fara nume";

	grafica = tip->grafica->Clonare();

	puncte_conexiune = new PunctConexiune[tip->nr_pct_conexiune];
	
	nr_pct_conexiune = tip->nr_pct_conexiune;
	
	for (int i = 0; i < nr_pct_conexiune; i++)
	{
		tip->puncte_conexiune[i].Clonare(&puncte_conexiune[i]);
		puncte_conexiune[i].parinte = this;
	}
	
	rotatie = DREAPTA;

	pozitie_in_grid = Vector2();
}
Componenta::Componenta() {
	id = "componenta fara nume";
	DreptunghiGrafic* dreptunghi = new DreptunghiGrafic();
	dreptunghi->culoare = SDL_Color{ 255,255,255,255 };
	dreptunghi->dimensiuni = Vector2(50, 50);
	grafica = dreptunghi;
	rotatie = DREAPTA;

	pozitie_in_grid = Vector2();
}

Componenta::~Componenta() {
	for (int i = 0; i < nr_pct_conexiune; i++)
	{

		if (puncte_conexiune[i].conector != NULL) {			
			delete puncte_conexiune[i].conector;
			puncte_conexiune[i].conector = NULL;
		}
		printf("successfully disconnectat pct conex de la conector \n");
	}
	//smth smth
}

void Componenta::SetPozitie(Vector2 pozitie)
{
	pozitie_in_grid = pozitie;
}

PunctConexiune::PunctConexiune(Vector2 _poz_rel, Componenta* _parinte, ORIENTARE _orientare)
{

	parinte = _parinte;
	pozitie_relativa = _poz_rel;
	buton = new Buton(Vector2(0, 0), Vector2(15, 15));

	DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
	bg_btn->culoare = SDL_Color{ 100,100,255,255 };
	bg_btn->dimensiuni = buton->dimensiuni;
	bg_btn->pozitie = Vector2(25, 15);
	bg_btn->marime = 1;


	buton->AdaugaElementGrafic(bg_btn);

	orientare = _orientare;
}
PunctConexiune::PunctConexiune(PunctConexiune* model)
{

	parinte = model->parinte;
	pozitie_relativa = model->pozitie_relativa;
	buton = new Buton(Vector2(0, 0), Vector2(Grid::MARIME_PCT_CONEX_LIBER, Grid::MARIME_PCT_CONEX_LIBER));

	DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
	bg_btn->culoare = CUL_PCT_CONEX_LIBER;
	bg_btn->dimensiuni = buton->dimensiuni;
	bg_btn->pozitie = Vector2(25, 15);
	bg_btn->marime = 1;

	buton->AdaugaElementGrafic(bg_btn);

	orientare = model->orientare;
}
PunctConexiune::PunctConexiune() {
}	
void PunctConexiune::Clonare(PunctConexiune* copie) {

	copie->parinte = parinte;
	copie->pozitie_relativa = pozitie_relativa;
	buton = new Buton(Vector2(0, 0), Vector2(Grid::MARIME_PCT_CONEX_LIBER, Grid::MARIME_PCT_CONEX_LIBER));
	copie->buton = buton;

	DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
	bg_btn->culoare = CUL_PCT_CONEX_LIBER;
	bg_btn->dimensiuni = buton->dimensiuni;
	bg_btn->pozitie = Vector2(25, 15);
	bg_btn->marime = 1;

	copie->buton->AdaugaElementGrafic(bg_btn);

	copie->orientare = orientare;
}

void Componenta::Print() {
	
}

Conector::Conector() {
	start_conexiune = NULL;
	final_conexiune= NULL;
}

Conector::~Conector() {
	if (start_conexiune != NULL) {
		start_conexiune->conector= NULL;
		start_conexiune = NULL;
	}
	if (final_conexiune != NULL) {
		final_conexiune->conector = NULL;
		final_conexiune = NULL;
	}
}