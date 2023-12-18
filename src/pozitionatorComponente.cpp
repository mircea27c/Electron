#include "pozitionatorComponente.h"

void SelectareComponenta(Componenta* comp) {
	component_selectat = comp;
	if (component_preview == NULL) {
		DreptunghiGrafic* dreptunghi_preview = new DreptunghiGrafic();
		dreptunghi_preview->culoare = SDL_Color{ 180,180,180,255 };
		dreptunghi_preview->dimensiuni = Vector2(50,50);

		component_preview = dreptunghi_preview;
	}
	se_plaseaza = true;
}

void ProcesarePlasare() {
	if (!se_plaseaza)return;
	if (component_selectat == NULL || component_preview == NULL)return;

	Vector2 gridPos = PozitieMouseInGrid();
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
	Vector2 gridPos = PozitieMouseInGrid();
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
