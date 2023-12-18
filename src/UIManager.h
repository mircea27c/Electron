#pragma once
#include <SDL.h>
#undef main
#include <SDL_ttf.h>
#include <iostream>
#include <list>
#include "grid.cpp"
#include "vector2.h"
#include "Componente.h"
#include "ElementeGrafice.h"

using namespace std;

extern const int LATIME;
extern const int INALTIME;
extern float factor_zoom;
extern float rata_zoom;

extern Vector2 pozitie_grid;

static SDL_Window* window;
static SDL_Renderer* renderer;

static std::list<Componenta*> toate_componentele;
static std::list<Buton*> toate_butoanele;

typedef void (*PctConexSelectatCallback)(PunctConexiune*);
extern PctConexSelectatCallback callback_slectare_pct_conex;

void ZoomIn();
void ZoomOut();

SDL_Renderer* GetCurrentRenderer();
void InititalizareUIManager();
void InchidereUIManager();
void InregistreazaComponenta(Componenta* comp);
void RefreshUI();
void DeseneazaComponente();
void DeseneazaComponenta(Componenta* comp);

void ActualizeazaGraficaComponenta(Componenta* comp);
void ActualizeazaGraficaConector(Conector* con);

void DeseneazaGrid(int grosime);
Vector2 PozitieGridLaPozitieEcran(Vector2 grid_poz);
Vector2 PozitieEcranLaPozitieGrid(Vector2 ecran_poz);
Vector2 PozitieMouseInGrid();
Vector2 GetCentruEcran();
Vector2 GetCentruGrid();

bool ButonApasat(Buton* btn, Vector2 clickPos);

void InregistrareButon(Buton* buton_new);

void ProcesareButoane(Vector2 poz_click);

void DeseneazaButon(Buton* btn);
void DeseneazaToateButoanele();

bool VerificaColiziune(Vector2 pozitie_in_grid);

void SelecteazaPunctConexiune(PunctConexiune* pct);
void ProceseazaClickPuncteConexiune(Vector2 poz_click);

inline bool SuntCeluleAdiacente(Vector2 poz1, Vector2 poz2) {
	
	return (abs(poz1.x - poz2.x) + abs(poz1.y - poz2.y) == 1);
}
inline Vector2 CelulaAdiacentaInDir(Vector2 poz, ORIENTARE dir) {
	switch (dir)
	{
	case STANGA:
		return Vector2(poz.x - 1, poz.y);
		break;
	case DREAPTA:
		return Vector2(poz.x + 1, poz.y);
		break;
	case SUS:
		return Vector2(poz.x, poz.y + 1);
		break;
	case JOS:
		return Vector2(poz.x, poz.y - 1);
		break;
	default:
		break;
	}
}