﻿#include "TipuriComponente.h"

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
	
	puncte.push_back(new PunctConexiune(Vector2(0.89, 0.50f), nullptr, STANGA, PunctConexiune::INPUT));
	puncte.push_back(new PunctConexiune(Vector2(0.11, 0.50f), nullptr, DREAPTA, PunctConexiune::OUTPUT));
	
CreazaComponenta("Desenecomponente/rezistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
puncte.clear();


   puncte.push_back(new PunctConexiune(Vector2(0.14, 0.50f), nullptr, STANGA, PunctConexiune::INPUT));
   puncte.push_back(new PunctConexiune(Vector2(0.88, 0.50f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

CreazaComponenta("Desenecomponente/intrerupator.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
puncte.clear();

//andgate
puncte.push_back(new PunctConexiune(Vector2(0.14, 0.43f), nullptr, STANGA, PunctConexiune::INPUT));
puncte.push_back(new PunctConexiune(Vector2(0.14, 0.57f), nullptr, STANGA, PunctConexiune::INPUT));
puncte.push_back(new PunctConexiune(Vector2(0.85, 0.50f), nullptr, DREAPTA, PunctConexiune::OUTPUT));

CreazaComponenta("Desenecomponente/andgate.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
puncte.clear();

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

//sursavoltaj
puncte.push_back(new PunctConexiune(Vector2(0.5, 0.15f), nullptr, SUS, PunctConexiune::INPUT));
puncte.push_back(new PunctConexiune(Vector2(0.5, 0.85f), nullptr, JOS, PunctConexiune::OUTPUT));

CreazaComponenta("Desenecomponente/sursavoltaj.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
puncte.clear();

//tranzistor
puncte.push_back(new PunctConexiune(Vector2(0.5, 0.2f), nullptr, SUS, PunctConexiune::OUTPUT));
puncte.push_back(new PunctConexiune(Vector2(0.14, 0.53f), nullptr, STANGA, PunctConexiune::INPUT));
puncte.push_back(new PunctConexiune(Vector2(0.88, 0.53f), nullptr, DREAPTA, PunctConexiune::INPUT));

CreazaComponenta("Desenecomponente/tranzistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
puncte.clear();

	/* CreazaComponenta("Desenecomponente/intrerupator.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/andgate.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/capacitor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/dioda2linii.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/diodacerc.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/impamantare.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/sursavoltaj.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	CreazaComponenta("Desenecomponente/tranzistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), puncte);
	*/

 /*CreazaComponenta("Desenecomponente/rezistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.89, 0.47f), Vector2(0.11, 0.47f));
	CreazaComponenta("Desenecomponente/intrerupator.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.88, 0.53f), Vector2(0.14, 0.53f));
	CreazaComponenta("Desenecomponente/andgate.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.85, 0.50f), Vector2(0.20, 0.50f));
	CreazaComponenta("Desenecomponente/capacitor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.85, 0.50f), Vector2(0.12, 0.50f));
	CreazaComponenta("Desenecomponente/dioda2linii.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.90, 0.50f), Vector2(0.12, 0.50f));
	CreazaComponenta("Desenecomponente/diodacerc.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.89, 0.50f), Vector2(0.11, 0.50f));
	CreazaComponenta("Desenecomponente/impamantare.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.89, 0.55f), Vector2(0.12, 0.55f));
	
	CreazaComponenta("Desenecomponente/sursavoltaj.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.80, 0.50f), Vector2(0.20, 0.50f));
	tipuri_componente[7]->generator_curent = true;
	
	CreazaComponenta("Desenecomponente/tranzistor.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.80, 0.50f), Vector2(0.20, 0.50f));
	
	tipuri_componente[8]->nr_pct_conexiune = 3;
	tipuri_componente[8]->puncte_conexiune = new PunctConexiune[3];
	tipuri_componente[8]->puncte_conexiune[2] = PunctConexiune(Vector2(0.72f, 0.22f), tipuri_componente[8], DREAPTA, PunctConexiune::OUTPUT);
	tipuri_componente[8]->puncte_conexiune[1] = PunctConexiune(Vector2(0.72f, 0.78f), tipuri_componente[8], DREAPTA, PunctConexiune::INPUT);
	tipuri_componente[8]->puncte_conexiune[0] = PunctConexiune(Vector2(0.3f, 0.5f), tipuri_componente[8], STANGA, PunctConexiune::INPUT);
	auto procesare_tranzistor = [](Componenta* comp,bool* puncte_curent) -> bool* {
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
	tipuri_componente[8]->functie_procesare = procesare_tranzistor;

	CreazaComponenta("Desenecomponente/2splitter.bmp", Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE), Vector2(0.80, 0.50f), Vector2(0.20, 0.50f));

	tipuri_componente[9]->nr_pct_conexiune = 3;
	tipuri_componente[9]->puncte_conexiune = new PunctConexiune[3];
	tipuri_componente[9]->puncte_conexiune[0] = PunctConexiune(Vector2(0.5f, 0.8f), tipuri_componente[8], JOS, PunctConexiune::INPUT);
	tipuri_componente[9]->puncte_conexiune[1] = PunctConexiune(Vector2(0.3f, 0.2f), tipuri_componente[8], STANGA, PunctConexiune::OUTPUT);
	tipuri_componente[9]->puncte_conexiune[2] = PunctConexiune(Vector2(0.7f, 0.2f), tipuri_componente[8], DREAPTA, PunctConexiune::OUTPUT);
	auto procesare_splitter = [](Componenta* comp, bool* puncte_curent) -> bool* {
		bool* output_valid = new bool[comp->nr_pct_conexiune];
		for (int i = 0; i < comp->nr_pct_conexiune; i++)
		{
			output_valid[i] = false;
		}

		output_valid[1]= puncte_curent[0];
		output_valid[2]= puncte_curent[0];
		return output_valid;
	};
	tipuri_componente[9]->functie_procesare = procesare_splitter;

	*/
	/*Componenta* rezistor = new Componenta();

		ImagineGrafica* img_rezistor = new ImagineGrafica();
		img_rezistor->dimensiuni = Vector2(MARIME_COMPONENTE , MARIME_COMPONENTE);
		img_rezistor->path = "Desenecomponente/rezistor.bmp";
		rezistor->grafica = img_rezistor;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		rezistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.89, 0.47f), rezistor, DREAPTA));
		rezistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.11, 0.47f), rezistor, STANGA));


		//comp2 
		Componenta* intrerupator = new Componenta();

		ImagineGrafica* img_intrerupator = new ImagineGrafica();
		img_intrerupator->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		img_intrerupator->path = "Desenecomponente/intrerupator.bmp";
		intrerupator->grafica = img_intrerupator;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		intrerupator->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.88, 0.53f), intrerupator, DREAPTA));
		intrerupator->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.14, 0.53f), intrerupator, STANGA));


		//comp3
		 Componenta* andGate = new Componenta();

		ImagineGrafica* img_andGate = new ImagineGrafica();
		img_andGate->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		img_andGate->path = "Desenecomponente/andgate.bmp";
		andGate->grafica = img_andGate;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		andGate->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.85, 0.5f), andGate, DREAPTA));
		andGate->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), andGate, STANGA));

		//comp4
		Componenta* capacitor = new Componenta();

		ImagineGrafica* img_capacitor = new ImagineGrafica();
		img_capacitor->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		img_capacitor->path = "Desenecomponente/capacitor.bmp";
		capacitor->grafica = img_capacitor;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		capacitor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.85, 0.5f), capacitor, DREAPTA));
		capacitor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.12, 0.5f), capacitor, STANGA));

		//comp5
		Componenta* dioda2linii = new Componenta();

		ImagineGrafica* img_dioda2linii = new ImagineGrafica();
		img_dioda2linii->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		img_dioda2linii->path = "Desenecomponente/dioda2linii.bmp";
		dioda2linii->grafica = img_dioda2linii;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		dioda2linii->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.9, 0.5f), dioda2linii, DREAPTA));
		dioda2linii->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.12, 0.5f), dioda2linii, STANGA));

		//comp6
		Componenta* diodacerc = new Componenta();

		ImagineGrafica* img_diodacerc = new ImagineGrafica();
		img_diodacerc->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		img_diodacerc->path = "Desenecomponente/diodacerc.bmp";
		diodacerc->grafica = img_diodacerc;
		//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
		diodacerc->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.89, 0.5f), diodacerc, DREAPTA));
		diodacerc->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.11, 0.5f), diodacerc, STANGA));

		//comp7
	 Componenta* impamantare = new Componenta();

	ImagineGrafica* img_impamantare = new ImagineGrafica();
	img_impamantare->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_impamantare->path = "Desenecomponente/impamantare.bmp";
	impamantare->grafica = img_impamantare;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	impamantare->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.89, 0.55f), impamantare, DREAPTA));
	impamantare->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.12, 0.55f), impamantare, STANGA));


	//comp8
	Componenta* sursavoltaj = new Componenta();

	ImagineGrafica* img_sursavoltaj = new ImagineGrafica();
	img_sursavoltaj->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_sursavoltaj->path = "Desenecomponente/sursavoltaj.bmp";
	sursavoltaj->grafica = img_sursavoltaj;

	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	sursavoltaj->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), sursavoltaj, DREAPTA));
	sursavoltaj->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), sursavoltaj, STANGA));

	//comp9
	Componenta* tranzistor = new Componenta();

	ImagineGrafica* img_tranzistor = new ImagineGrafica();
	img_tranzistor->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_tranzistor->path = "Desenecomponente/tranzistor.bmp";
	tranzistor->grafica = img_tranzistor;

	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	tranzistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), tranzistor, DREAPTA));
	tranzistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), tranzistor, STANGA));
	*/

	
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
