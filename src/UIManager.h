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
static std::list<WindowGrafic*> toate_windowurile;
static std::list<Buton*> toate_butoanele;

typedef void (*PctConexSelectatCallback)(PunctConexiune*);
typedef void (*RefreshUICallback)();

extern PctConexSelectatCallback callback_slectare_pct_conex;
extern list<RefreshUICallback> refresh_ui_listeners;

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

void ActualizeazaGraficaComponenta(Componenta* comp);
void ActualizeazaGraficaConector(Conector* con);

void DeseneazaGrid(int grosime);
Vector2 PozitieGridLaPozitieEcran(Vector2 grid_poz);
Vector2 PozitieEcranLaPozitieGrid(Vector2 ecran_poz);
Vector2 PozitieMouseInGrid();
Vector2 GetCentruEcran();

bool ButonApasat(Buton* btn, Vector2 clickPos);

void InregistrareButon(Buton* buton_new);
void EliminaButon(Buton* buton);

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
