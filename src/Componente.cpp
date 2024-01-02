#include "Componente.h"

Vector2 Componenta::GetPozitie() { return pozitie_in_grid; }
void Componenta::SetPozitie(Vector2 pozitie)
{
	pozitie_in_grid = pozitie;
}

PunctConexiune::PunctConexiune(Vector2 _poz_rel, Componenta* _parinte, ORIENTARE _orientare)
{

	parinte = _parinte;
	pozitie_relativa = _poz_rel;
	buton = new Buton(Vector2(0,0), Vector2(15, 15));

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

void Componenta::Print() {
	
}

