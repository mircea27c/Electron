#include "SimulatorCircuit.h"

void SimulatorCircuit::Simuleaza(std::list<Componenta*> componente)
{
	toate_componentele = componente;

	for (auto& comp : toate_componentele) {
		if (((ImagineGrafica*)comp->grafica)->path == "Desenecomponente/sursavoltaj.bmp") {
			Parcurge(comp);
		}
	}

}

void SimulatorCircuit::Parcurge(Componenta* comp)
{
	de_vizitat.push(comp);

	while (!de_vizitat.empty()) {
		Componenta* top = de_vizitat.front();
		if (top == NULL)break;
		//vizitate.insert(top);
		for (int i = 0; i < top->nr_pct_conexiune; i++)
		{
			if (top->puncte_conexiune[i].conector != NULL) {

				SDL_Delay(500);
				top->puncte_conexiune[i].conector->grafica->culoare = cul_curent;
				RefreshUI();

				Conector* con = top->puncte_conexiune[i].conector;
				Componenta* next_comp = NULL;

				SDL_Color cul_con = con->grafica->culoare;
				bool are_curent = (cul_con.r == cul_curent.r && cul_con.g == cul_curent.g && cul_con.b == cul_curent.b);

				if (are_curent) {
					continue;
				}


				if (con->start_conexiune != NULL && con->start_conexiune == &top->puncte_conexiune[i]) {
					if (con->final_conexiune != NULL) {
						next_comp = con->final_conexiune->parinte;
					}
				}
				if (con->final_conexiune != NULL && con->final_conexiune == &top->puncte_conexiune[i]) {
					if (con->start_conexiune != NULL)
					next_comp = con->start_conexiune->parinte;
				}

				//if ()

				de_vizitat.push(next_comp);
			}
		}
		de_vizitat.pop();
	}
}

void SimulatorCircuit::Reseteaza()
{
}
