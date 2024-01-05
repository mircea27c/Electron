#pragma once
#include <SDL.h>
#undef main
#include <SDL_ttf.h>
#include <iostream>
#include <list>
#include <queue>
#include "grid.cpp"
#include "vector2.h"
#include "Componente.h"
#include "ElementeGrafice.h"

class EcranPrincipal;

using namespace std;

static bool afiseaza_GUI = true;

extern int LATIME;
extern int INALTIME;
extern float factor_zoom;
extern float rata_zoom;

extern Vector2 pozitie_grid;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern std::list<Componenta*> toate_componentele;
static std::list<WindowGrafic*> toate_windowurile;

enum ActiuneLista
{
	ADAUGA,
	ELIMINA
};
struct ActiuneListaButoane{
	ActiuneLista tip_actiune;
	Buton* buton;
};

static std::queue<ActiuneListaButoane> coada_actiuni_lista_butoane;
extern std::list<Buton*> toate_butoanele;

typedef void (*PctConexSelectatCallback)(PunctConexiune*);
typedef void (*RefreshUICallback)();

extern PctConexSelectatCallback callback_slectare_pct_conex;
extern list<RefreshUICallback> refresh_ui_listeners;
extern list<RefreshUICallback> post_refresh_ui_listeners;

void ZoomIn();
void ZoomOut();

SDL_Renderer* GetCurrentRenderer();
void InititalizareUIManager();
void InchidereUIManager();
void InregistreazaComponenta(Componenta* comp);
void EliminaComponenta(Componenta* comp);
void RefreshUI();
void DeseneazaComponente();
void DeseneazaComponenta(Componenta* comp);

void DeseneazaWindowGrafic(WindowGrafic* window);
void DeseneazaWindowuriGrafice();
void InregistreazaWindowGrafic(WindowGrafic* window);
void EliminaWindowGrafic(WindowGrafic* window);

Buton* CreeazaButonCuImagine(Vector2 pozitie, Vector2 dimensiuni,float procentaj, SDL_Color culoare_btn, SDL_Color culoare_img, const char* path_img);

Buton* CreeazaButonCuText(Vector2 pozitie, Vector2 dimensiuni, float procentaj_marime_imagine, SDL_Color culoare_btn, SDL_Color culoare_img, const char* text);

void ActualizeazaGraficaComponenta(Componenta* comp);
void ActualizeazaGraficaPctConex(Componenta* comp, PunctConexiune* pct);
void ActualizeazaGraficaConector(Conector* con);

void DeseneazaGrid(int grosime);

void AfiseazaGUI();
void AscundeGUI();

Vector2 PozitieGridLaPozitieEcran(Vector2 grid_poz);
Vector2 PozitieEcranLaPozitieGrid(Vector2 ecran_poz);
Vector2 PozitieMouseInGrid();
Vector2 GetCentruEcran();

bool ButonApasat(Buton* btn, Vector2 clickPos);

void InregistrareButon(Buton* buton_new);
void EliminaButon(Buton* buton);
void ProcesareActiuniListaButoane();

void ProcesareButoane(Vector2 poz_click);

void DeseneazaButon(Buton* btn);
void DeseneazaToateButoanele();

bool VerificaColiziune(Vector2 pozitie_in_grid);
Componenta* VerificaColiziuneComponenta(Vector2 pozitie_in_grid);

void SelecteazaPunctConexiune(PunctConexiune* pct);
void ProceseazaClickPuncteConexiune(Vector2 poz_click);

bool SuntCeluleAdiacente(Vector2 poz1, Vector2 poz2);
Vector2 CelulaAdiacentaInDir(Vector2 poz, ORIENTARE dir);

PunctConexiune* MousePestePuctConexiune(Vector2 poz_mouse);

void DeseneazaLegaturaPctLaConector(PunctConexiune* pct, Vector2 g_poz_conector, Path* grafica, bool primul);
float GasestePctIntermediar(float num);
std::list<Componenta*> GetToateComponentele();


inline bool CuloriEgale(SDL_Color col1, SDL_Color col2) {
	return (col1.r == col1.r && col1.g == col2.g && col2.b == col2.b);
}