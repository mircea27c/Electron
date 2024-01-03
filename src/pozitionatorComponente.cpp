#include "pozitionatorComponente.h"

void pozitionator_componente::SelectareComponentaPozitionare(int index) {
	SelecteazaComponenta(index);

	Componenta* comp = GetComponentaSelectata();

	if (comp == NULL) {
		printf("comp e nula");
		return;
	}

	component_selectat = new Componenta(GetComponentaSelectata());

	if (component_preview == NULL) {
		ImagineGrafica* imagine_preview = new ImagineGrafica();
		imagine_preview->dimensiuni = Vector2(MARIME_COMPONENTE, MARIME_COMPONENTE);
		component_preview = imagine_preview;
	}
	component_preview->path = ((ImagineGrafica*)component_selectat->grafica)->path;

	se_plaseaza = true;
}

void pozitionator_componente::SelectareComponentaPozitionare(Componenta* comp) {
	SelectareComponentaPozitionare(comp->id);
	component_selectat->rotatie = comp->rotatie;
	switch (comp->rotatie)
	{
	case DREAPTA:
		component_preview->rotatie = 0;
		break;
	case JOS:
		component_preview->rotatie = 90;
		break;
	case STANGA:
		component_preview->rotatie = 180;
		break;
	case SUS:
		component_preview->rotatie = 270;
		break;
	default:
		component_preview->rotatie = 0;
		break;
	}
}


void pozitionator_componente::ProcesarePlasare() {
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

void pozitionator_componente::ProcesareClickPlasare() {

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

