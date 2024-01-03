#pragma once
#include <iostream>
#include <set>
#include <queue>
#include <SDL.h>
#include "Componente.h"
#include "UIManager.h"


class SimulatorCircuit
{
	std::list<Componenta*> toate_componentele;

	SDL_Color cul_curent = SDL_Color{10,247,255};

	//std::set<Componenta*> vizitate;
	std::queue<Componenta*> de_vizitat;
	void Parcurge(Componenta* comp);
public:
	void Simuleaza(std::list<Componenta*>);
	
	void Reseteaza();

};

