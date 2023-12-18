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

	//comp3

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
