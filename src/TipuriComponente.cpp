#include "TipuriComponente.h"

void CreazaComponenta(const char* path, Vector2 dimensiuni, std::vector<PunctConexiune*> puncteConexiune) {
	static int index_componenta = 0;

	Componenta* componenta = new Componenta();

	ImagineGrafica* img = new ImagineGrafica();
	img->dimensiuni = dimensiuni;
	img->path = path;
	componenta->grafica = img;

	componenta->nr_pct_conexiune = puncteConexiune.size();
	componenta->puncte_conexiune = new PunctConexiune[componenta->nr_pct_conexiune];

	for (int i = 0; i < componenta->nr_pct_conexiune; ++i) {
		componenta->puncte_conexiune[i] = *puncteConexiune[i];
	}

	componenta->id = index_componenta;
	tipuri_componente[index_componenta] = componenta;

	index_componenta++;
}
 

/*void CreazaComponenta(const char* path, Vector2 dimensiuni, Vector2 pct1, Vector2 pct2) {
		
	static int index_componenta = 0;
	
	Componenta* componenta = new Componenta();

	ImagineGrafica* img = new ImagineGrafica();
	img->dimensiuni = dimensiuni;
	img->path = path;
	componenta->grafica = img;

	componenta->puncte_conexiune = new PunctConexiune[2];
	componenta->nr_pct_conexiune = 2;
	componenta->puncte_conexiune[0] = PunctConexiune(pct1, componenta, DREAPTA, PunctConexiune::OUTPUT);
	componenta->puncte_conexiune[1] = PunctConexiune(pct2, componenta, STANGA, PunctConexiune::INPUT);

	componenta->id = index_componenta;
	tipuri_componente[index_componenta] = componenta;

	index_componenta++;
}*/

void InitializareTipuriComponente() {
	std::vector<PunctConexiune*> puncte;
	//rezistor

	auto procesare_tranzistor = [](Componenta* comp, bool* puncte_curent) -> bool* {
		bool* output_valid = new bool[comp->nr_pct_conexiune];
		for (int i = 0; i < comp->nr_pct_conexiune; i++)
		{
			output_valid[i] = false;
		}

		if (puncte_curent[0] && puncte_curent[1]) {
			output_valid[2] = true;
		}
		else {
			output_valid[2] = false;
		}
		return output_valid;
	};


	puncte.push_back(new PunctConexiune(Vector2(0.15f, 0.5), nullptr, SUS, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.85f, 0.5), nullptr, JOS, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/sursavoltaj.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();


	puncte.push_back(new PunctConexiune(Vector2(0.89, 0.50f), nullptr, STANGA, PunctConexiune::OUTPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.11, 0.50f), nullptr, DREAPTA, PunctConexiune::INPUT));
	
	CreazaComponenta("Desenecomponente/rezistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();


	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.50f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.88, 0.50f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/bec.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();

	auto procesare_bec = [](Componenta* comp, bool* puncte_curent) {
		bool* output_valid = new bool[comp->nr_pct_conexiune];
		for (int i = 0; i < comp->nr_pct_conexiune; i++)
		{
			output_valid[i] = false;
		}

		if (puncte_curent[0] == true) {
			printf("seteaza culoare galben \n");
			comp->grafica->culoare = SDL_Color{255,255,0};
			output_valid[1] = true;
		}
		else {
			printf("reseteaza culoare \n");
			comp->grafica->culoare = SDL_Color{255,255,255};
			output_valid[1] = false;
		}

		return output_valid;
	};
	tipuri_componente[2]->functie_procesare = procesare_bec;

	//andgate
	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.43f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.57f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.85, 0.50f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/andgate.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();

	tipuri_componente[3]->functie_procesare = procesare_tranzistor;

	//capacitor

	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.51f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.88, 0.51f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/capacitor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();
	//dioda2linii

	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.51f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.88, 0.51f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/dioda2linii.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();

	//diodacerc

	puncte.push_back(new PunctConexiune(Vector2(0.14, 0.51f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.88, 0.51f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/diodacerc.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();

	//impamantare
	puncte.push_back(new PunctConexiune(Vector2(0.5, 0.2f), nullptr, SUS, PunctConexiune::INPUT));

	CreazaComponenta("Desenecomponente/impamantare.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();


	//tranzistor
	puncte.push_back(new PunctConexiune(Vector2(0.65f,0.88), nullptr, DREAPTA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.15f,0.5), nullptr, SUS, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.65f,0.14), nullptr, STANGA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/tranzistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	puncte.clear();

	tipuri_componente[8]->functie_procesare = procesare_tranzistor;

	puncte.push_back(new PunctConexiune(Vector2(0.5f, 0.8f), nullptr, JOS, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.3f, 0.2f), nullptr, STANGA, PunctConexiune::OUTPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.7f, 0.2f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

	CreazaComponenta("Desenecomponente/2splitter.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);

	auto procesare_splitter = [](Componenta* comp, bool* puncte_curent) -> bool* {
		bool* output_valid = new bool[comp->nr_pct_conexiune];
		for (int i = 0; i < comp->nr_pct_conexiune; i++)
		{
			output_valid[i] = false;
		}

		output_valid[1] = puncte_curent[0];
		output_valid[2] = puncte_curent[0];
		return output_valid;
	};
	tipuri_componente[9]->functie_procesare = procesare_splitter;

}

void SelecteazaComponenta(int index) {
	if (index < 0 || index >= tipuri_componente.size()) { printf("eroare selectare componenta index out of bounds \n");  return; }

	if (tipuri_componente[0] == NULL)printf("rezistor bagat in array e null");

	tip_comp_selectat = tipuri_componente[index];

	if (tip_comp_selectat == NULL) {
		printf("E NUL");
	}
}


Componenta* GetComponentaSelectata() {
	return tip_comp_selectat;
}

int NrTipuriComponente()
{
	return tipuri_componente.size();
}
