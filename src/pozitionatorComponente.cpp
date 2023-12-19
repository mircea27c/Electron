#include "pozitionatorComponente.h"

void SelectareComponentaPozitionare(int index) {
	printf("indexul este %d si se selecteaza componenta\n ", index);
	SelecteazaComponenta(index);

	Componenta* comp = GetComponentaSelectata();

	if (comp == NULL) {
		printf("comp e nula pula");
		return;
	}

	component_selectat = new Componenta(GetComponentaSelectata());
	component_selectat->id = "componenta valida \n";

	if (component_preview == NULL) {
		ImagineGrafica* rezistor = new ImagineGrafica();
		rezistor->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		rezistor->path="Desenecomponente/rezistor.bmp";
        component_preview = rezistor;
		/*/DreptunghiGrafic* dreptunghi_preview = new DreptunghiGrafic();
		dreptunghi_preview->culoare = SDL_Color{ 180,180,180,255 };
		dreptunghi_preview->dimensiuni = Vector2(50,50);

		component_preview = dreptunghi_preview;*/
	}
	se_plaseaza = true;
}

void ProcesarePlasare() {
	if (!se_plaseaza)return;
	if (component_selectat == NULL || component_preview == NULL)return;


	int x = 0, y = 0;


	SDL_GetMouseState(&x, &y);
	printf("pozitie mouse %f %f\n", x, y);

	Vector2 gridPos = PozitieMouseInGrid(x,y);
	if (grid_ultim_x != gridPos.x || grid_ultim_y != gridPos.y) {
		RefreshUI();
	}
	//in functie de pozitia mouseului, determina celula din tabel in care se afla Componenta

	if (gridPos.x != -1) {
			
			component_preview->pozitie = PozitieGridLaPozitieEcran(gridPos);
			component_preview->marime = factor_zoom;

			if (VerificaColiziune(gridPos)) {
				component_preview->culoare = SDL_Color{ 200,0,0,255 };
			}
			else {
				component_preview->culoare = SDL_Color{ 180,180,180,255 };
			}
			component_preview->Desenare(GetCurrentRenderer());
			SDL_RenderPresent(GetCurrentRenderer());
	}


	grid_ultim_x = gridPos.x;
	grid_ultim_y = gridPos.y;

}

void ProcesareClickPlasare() {
	
	if (!se_plaseaza)return;

	int x = 0, y = 0;

	SDL_GetMouseState(&x, &y);
	Vector2 gridPos = PozitieMouseInGrid(x,y);
	if (gridPos.x == -1)return;
	if (VerificaColiziune(gridPos)) {
		return;
	}
	component_selectat->SetPozitie(gridPos);

	InregistreazaComponenta(component_selectat);
	component_selectat = NULL;
	se_plaseaza = false;

	RefreshUI();
}
