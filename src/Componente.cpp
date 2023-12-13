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
	puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), DREAPTA));
	puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), STANGA));
}

PunctConexiune::PunctConexiune(Vector2 _poz_rel, ORIENTARE _orientare) {
	pozitie_relativa = _poz_rel;
	buton = new Buton("", SDL_Color{ 50,50,230,255 }, "", Vector2(0, 0), Vector2(15, 15));
	orientare = _orientare;
}

void Componenta::Print() {
	
}
