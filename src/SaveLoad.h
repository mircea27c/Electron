#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "UIManager.h"
#include "TipuriComponente.h"
#include "EditorComponente.h"
using namespace std;
#pragma once

void SaveCircuit(const char* nume);

void LoadCircuit(const char* nume);

Vector2 ParseazaPozitie(string text);

Componenta* GasesteComponentaDupaID(list<Componenta*>* lista, int id);

void SaveCircuitFileBrowser();

void LoadCircuitFileBrowser();