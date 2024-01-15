#include "SimulatorCircuit.h"

void SimulatorCircuit::Simuleaza()
{
	Reseteaza();

	pauza = false;
	toate_componentele;

	for (auto& comp : toate_componentele) {
		if (((ImagineGrafica*)comp->grafica)->path == "Desenecomponente/sursavoltaj.bmp") {
			de_vizitat.push(comp);
		}
	}

}

void SimulatorCircuit::Pauza()
{
	pauza = true;
}

void SimulatorCircuit::Stop()
{
	reset = true;
}

void SimulatorCircuit::ParcurgePas(float timp_trecut) {

	if (reset) {
		Reseteaza();
		reset = false;
		return;
	}
	if (pauza) {
		return;
	}

	timp_pas += timp_trecut;
	if (timp_pas < interval_pas) {
		return;
	}
	timp_pas = 0;

	if (de_vizitat.empty() || reset) {
		return;
	}

	Componenta* top = de_vizitat.front();
	if (top == NULL)return;
	//vizitate.insert(top);

	bool* puncte_output = new bool[top->nr_pct_conexiune];
	for (int i = 0; i < top->nr_pct_conexiune; i++)
	{
		puncte_output[i] = false;
	}

	if (top->functie_procesare == NULL) {
		for (int i = 0; i < top->nr_pct_conexiune; i++)
		{
			if (top->puncte_conexiune[i].tip == PunctConexiune::OUTPUT) {
				puncte_output[i] = true;
			}
			else {
				puncte_output[i] = false;
			}

		}
	}
	else {

		bool* puncte_input = new bool[top->nr_pct_conexiune];
		for (int i = 0; i < top->nr_pct_conexiune; i++)
		{
			puncte_input[i] = false;
		}

		for (int i = 0; i < top->nr_pct_conexiune; i++)
		{
			if (top->puncte_conexiune[i].conector != NULL) {
				if (CuloriEgale(top->puncte_conexiune[i].conector->grafica->culoare, cul_curent)) {
					puncte_input[i] = true;
					continue;
				}
			}
			puncte_input[i] = false;
		}

		puncte_output = top->functie_procesare(top, puncte_input);

		delete[] puncte_input;
	}

	for (int i = 0; i < top->nr_pct_conexiune; i++)
	{
		if (puncte_output[i] == false)continue;

		if (top->puncte_conexiune[i].conector != NULL) {

			Conector* con = top->puncte_conexiune[i].conector;

			SDL_Color cul_con = con->grafica->culoare;
			bool are_curent = CuloriEgale(cul_con, cul_curent);

			if (are_curent) {
				continue;
			}

			con->grafica->culoare = cul_curent;
			RefreshUI();

			Componenta* next_comp = NULL;

			PunctConexiune* pct_urmator = NULL;
			if (con->start_conexiune != NULL && con->start_conexiune == &top->puncte_conexiune[i]) {
				if (con->final_conexiune != NULL) {
					next_comp = con->final_conexiune->parinte;
					pct_urmator = con->final_conexiune;
				}
			}
			if (con->final_conexiune != NULL && con->final_conexiune == &top->puncte_conexiune[i]) {
				if (con->start_conexiune != NULL) {
					next_comp = con->start_conexiune->parinte;
					pct_urmator = con->start_conexiune;
				}
			}

			if (next_comp == NULL) { continue; }
			if (pct_urmator->tip == PunctConexiune::INPUT) {
				de_vizitat.push(next_comp);
			}
		}
	}

	delete[] puncte_output;

	//printf("simuleaza...\n");
	de_vizitat.pop();

}

void SimulatorCircuit::CresteViteza()
{
	index_viteza = min(index_viteza + 1, nr_viteze - 1);
	RecalculeazaViteza();
}

void SimulatorCircuit::ScadeViteza()
{
	index_viteza = max(index_viteza - 1, 0);
	RecalculeazaViteza();
}


void SimulatorCircuit::RecalculeazaViteza()
{
	float viteza = viteze[index_viteza];
	interval_pas = interval_normal * 1.0f / viteza;

	text_viteza.clear();
	text_viteza = std::to_string(viteze[index_viteza]);
	text_viteza.erase(4);
	text_viteza += 'x';
}

void SimulatorCircuit::Reseteaza()
{
	if (toate_componentele.empty())return;

	for (auto& comp : toate_componentele) {

		if (Conector* conector = dynamic_cast<Conector*>(comp))
		{
			comp->grafica->culoare = SDL_Color{255,255,255};
		}
		else {
			bool* input_gol = new bool[comp->nr_pct_conexiune];
			for (int i = 0; i < comp->nr_pct_conexiune; i++)
			{
				input_gol[i] = false;
			}

			if (comp->functie_procesare != NULL) {

				comp->functie_procesare(comp, input_gol);
			}
		}
	}

	RefreshUI();
}
