#pragma once
#include "UIManager.h"


static Componenta* component_selectat = NULL;
static ElementGrafic* component_preview = NULL;

static int grid_ultim_x;
static int grid_ultim_y;

static bool se_plaseaza;

void SelectareComponenta(Componenta* comp);

void ProcesarePlasare();

void ProcesareClickPlasare();
