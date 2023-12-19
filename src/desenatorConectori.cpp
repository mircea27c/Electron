#include "desenatorConectori.h"
void desenator_conectori::StartConectare(PunctConexiune* pct_start) {
	if (pct_start->output != NULL) {
		//momentan return 
		printf("pct de conex pe care ai apasat are deja un cablu atasat. daca nu-l vezi e o problema la randare \n");
		return;
	}

	conector_desenat = new Conector();
	conector_desenat->start_conexiune = pct_start;

	Path* path = new Path();
	conector_desenat->grafica = path;
	pct_start->output = conector_desenat;

	se_deseneaza_conector = true;

	InregistreazaComponenta(conector_desenat);
}
void desenator_conectori::StopConectare() {

	se_deseneaza_conector = false;
	conector_desenat = NULL;

}

void desenator_conectori::InitializareDesenatorConectori() {
	callback_slectare_pct_conex = StartConectare;
}

void desenator_conectori::ProcesareFinalizareConectare(int mouse_x, int mouse_y) {
	PunctConexiune* pct_sub_mouse = MousePestePuctConexiune(Vector2(mouse_x, mouse_y));
	printf("coordonate mouse %f %f \n", mouse_x, mouse_y);
	if (pct_sub_mouse != NULL) {
		printf("punct sub mouse NU este null \n");
		conector_desenat->final_conexiune = pct_sub_mouse;
		pct_sub_mouse->output = conector_desenat;
		StopConectare();

		RefreshUI();
	}
	else {
		printf("punct sub mouse este NULL \n");
	}
}


void desenator_conectori::ProcesareConectare() {
	if (!se_deseneaza_conector)return;
	if (conector_desenat == NULL)return;

	int x = 0, y = 0;

	SDL_GetMouseState(&x,&y);

	Vector2 gridPos = PozitieMouseInGrid(x,y);
	if (grid_ultim_x == gridPos.x && grid_ultim_y == gridPos.y) {
		//daca suntem in aceeasi celula nu mai procesam nimic legat de schimbarea celulei, dar verificam daca mouseul este peste vreun pct conexiune

		if (gridPos.x != -1) {
			if (conector_desenat->pozitii.empty()) {
				Vector2 poz_start = conector_desenat->start_conexiune->parinte->GetPozitie();
				Vector2 adiacenta_blocata = CelulaAdiacentaInDir(poz_start, conector_desenat->start_conexiune->orientare);

				//nu uita sa decomentezi verificarea celului adiancente blocate si sa o faci sa mearga
				if (SuntCeluleAdiacente(poz_start, gridPos) /*&& !(gridPos == adiacenta_blocata)*/ && VerificaColiziune(gridPos)) {
					ProcesareFinalizareConectare(x, y);
				}
			}
			else {
				if (SuntCeluleAdiacente(conector_desenat->pozitii.back(), gridPos)) {

					if (VerificaColiziune(gridPos)) {
						ProcesareFinalizareConectare(x, y);
					}
				}
			}
		}


		return;
	}

	//in functie de pozitia mouseului, determina celula din tabel in care se afla Componenta

	if (gridPos.x != -1) {
		if (conector_desenat->pozitii.empty()) {
			Vector2 poz_start = conector_desenat->start_conexiune->parinte->GetPozitie();
			Vector2 adiacenta_blocata = CelulaAdiacentaInDir(poz_start, conector_desenat->start_conexiune->orientare);

			//nu uita sa decomentezi verificarea celului adiancente blocate si sa o faci sa mearga
			if (SuntCeluleAdiacente(poz_start, gridPos) /*&& !(gridPos == adiacenta_blocata)*/ && !VerificaColiziune(gridPos)) {

				conector_desenat->pozitii.push_back(gridPos);

				RefreshUI();

			}
		}
		else {
			if (SuntCeluleAdiacente(conector_desenat->pozitii.back(), gridPos)) {

				if (!VerificaColiziune(gridPos)) {
					conector_desenat->pozitii.push_back(gridPos);
				}

				RefreshUI();
			}
		}
	}
	grid_ultim_x = gridPos.x;
	grid_ultim_y = gridPos.y;
}

void desenator_conectori::ProcesareStopClickDesenare() {
	if (!se_deseneaza_conector || conector_desenat == NULL)return;
	StopConectare();
}