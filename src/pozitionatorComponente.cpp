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
		ImagineGrafica* imagine_preview = new ImagineGrafica();
		imagine_preview->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
        component_preview = imagine_preview;
	}
	component_preview->path = ((ImagineGrafica*)component_selectat->grafica)->path;
	
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
