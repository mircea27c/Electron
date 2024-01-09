#pragma once 
#include <list>
#include <iostream>
#include <array>
#include "Grid.cpp"
#include "Componente.h"


#define MARIME_COMPONENTE Grid::MARIME_CELULA * 0.9f

static std::array<Componenta*,11> tipuri_componente;
static Componenta* tip_comp_selectat = NULL;


void InitializareTipuriComponente();

void SelecteazaComponenta(int index);
Componenta* GetComponentaSelectata(); 

int NrTipuriComponente();