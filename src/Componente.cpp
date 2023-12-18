#include "Componente.h"

Vector2 Componenta::GetPozitie() { return pozitie_in_grid; }
void Componenta::SetPozitie(Vector2 pozitie)
{
	pozitie_in_grid = pozitie;
}
Componenta::Componenta() {
	DreptunghiGrafic* dreptunghi = new DreptunghiGrafic();
	dreptunghi->culoare = SDL_Color{255,255,255,255};
	dreptunghi->dimensiuni = Vector2(50,50);
	grafica = dreptunghi;

	pozitie_in_grid = Vector2();
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

void Componenta::Print() {
	
}
