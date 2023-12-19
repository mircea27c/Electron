#include "TipuriComponente.h"

#define MARIME_COMPONENTE 50


void InitializareTipuriComponente() {
	printf("Initializare succes \n");
	Componenta* rezistor = new Componenta();

	ImagineGrafica* img_rezistor = new ImagineGrafica();
	img_rezistor->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_rezistor->path = "Desenecomponente/rezistor.bmp";
	rezistor->grafica = img_rezistor;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	rezistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), rezistor, DREAPTA));
	rezistor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), rezistor, STANGA));


	//comp2 
	Componenta* intrerupator = new Componenta();

	ImagineGrafica* img_intrerupator = new ImagineGrafica();
	img_intrerupator->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_intrerupator->path = "Desenecomponente/intrerupator.bmp";
	intrerupator->grafica = img_intrerupator;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	intrerupator->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), intrerupator, DREAPTA));
	intrerupator->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), intrerupator, STANGA));


	//comp3
	Componenta* andGate = new Componenta();

	ImagineGrafica* img_andGate = new ImagineGrafica();
	img_andGate->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_andGate->path = "Desenecomponente/andgate.bmp";
	andGate->grafica = img_andGate;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	andGate->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), andGate, DREAPTA));
	andGate->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), andGate, STANGA));

	//comp4
	Componenta* capacitor = new Componenta();

	ImagineGrafica* img_capacitor = new ImagineGrafica();
	img_capacitor->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_capacitor->path = "Desenecomponente/capacitor.bmp";
	capacitor->grafica = img_capacitor;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	capacitor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), capacitor, DREAPTA));
	capacitor->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), capacitor, STANGA));

	//comp5
	Componenta* dioda2linii = new Componenta();

	ImagineGrafica* img_dioda2linii = new ImagineGrafica();
	img_dioda2linii->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_dioda2linii->path = "Desenecomponente/dioda2linii.bmp";
	dioda2linii->grafica = img_dioda2linii;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	dioda2linii->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), dioda2linii, DREAPTA));
	dioda2linii->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), dioda2linii, STANGA));

	//comp6
	Componenta* diodacerc = new Componenta();

	ImagineGrafica* img_diodacerc = new ImagineGrafica();
	img_diodacerc->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_diodacerc->path = "Desenecomponente/diodacerc.bmp";
	diodacerc->grafica = img_diodacerc;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	diodacerc->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), diodacerc, DREAPTA));
	diodacerc->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), diodacerc, STANGA));

	//comp7
	Componenta* impamantare = new Componenta();

	ImagineGrafica* img_impamantare = new ImagineGrafica();
	img_impamantare->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
	img_impamantare->path = "Desenecomponente/impamantare.bmp";
	impamantare->grafica = img_impamantare;
	//adauga un pct conexiune la 0.8 (80%) din marimea celulei (de la stanga la dreapta) si 0.5 (50%) adica mijloc de sus in jos (sau invers)
	impamantare->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.8, 0.5f), impamantare, DREAPTA));
	impamantare->puncte_conexiune.push_back(new PunctConexiune(Vector2(0.2, 0.5f), impamantare, STANGA));

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

	
	if (rezistor == NULL)printf("rezistor e null");

	tipuri_componente[0] = rezistor;
	if (tipuri_componente[0] == NULL)printf("rezistor bagat in array e null");

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
