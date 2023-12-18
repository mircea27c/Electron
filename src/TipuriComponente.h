#pragma once 
#include <list>
#include <iostream>
#include <array>
#include "Componente.h"

#define MARIME_COMPONENTE 50

static std::array<Componenta*,1> tipuri_componente;
static Componenta* tip_comp_selectat = NULL;

void InitializareTipuriComponente();

void SelecteazaComponenta(int index);
Componenta* GetComponentaSelectata();
