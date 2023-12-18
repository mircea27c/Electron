#pragma once
#include "UIManager.h"
#include<math.h>
const int LATIME = 1200;
const int INALTIME = 800;
float factor_zoom = 1;
float rata_zoom = 1.2f;


Vector2 pozitie_grid;

TTF_Font* font;

PunctConexiune* pct_conex_selectat;
PctConexSelectatCallback callback_slectare_pct_conex;


SDL_Renderer* GetCurrentRenderer() {
    return renderer;
}

//Componente si grid-------------------------------------------

void ZoomIn() {
    factor_zoom *= rata_zoom;
    if (factor_zoom > 10) {
        factor_zoom = 10;
        return;
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    pozitie_grid = pozitie_grid * rata_zoom;
    RefreshUI();
}

void ZoomOut() {

    factor_zoom /= rata_zoom;
    if (factor_zoom < 0.1f) {
        factor_zoom = 0.1f;
        return;
    }


    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    pozitie_grid = pozitie_grid / rata_zoom;
    RefreshUI();
}


void InititalizareUIManager() {

    window = SDL_CreateWindow("Electron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LATIME, INALTIME, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) return;


    if (TTF_Init() < 0) {
        //Eroare
        cout << "ttf initialization error";
    }

    font = TTF_OpenFont("Fonts/ShareTech.ttf", 24);
    if (font == NULL) {
        font = TTF_OpenFont("Fonts/aril.ttf", 24);

    }
    if (font == NULL) {
        printf("NULL font error");
    }

}

void InchidereUIManager() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void InregistreazaComponenta(Componenta* comp) {
    toate_componentele.push_back(comp);
}
void ShowTabelDetalii(Componenta* comp) {
    
}

void RefreshUI() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    DeseneazaGrid(2);
    DeseneazaComponente();
    DeseneazaToateButoanele();

    SDL_RenderPresent(renderer);
    //ShowTabelDetalii(comp);
}

void DeseneazaComponente() {
    for (auto comp : toate_componentele)
    {
        DeseneazaComponenta(comp);
    }
}
void DeseneazaComponenta(Componenta* comp) {

    float zoomedCellSize = Grid::MARIME_CELULA * factor_zoom;

    Vector2 gridSize = Vector2(Grid::GRID_CELULE_LATIME * zoomedCellSize, Grid::GRID_CELULE_INALTIME * zoomedCellSize);
    Vector2 gridCenter = Vector2(gridSize.x / 2, gridSize.y / 2);
    Vector2 screenCenter = Vector2(LATIME / 2 + pozitie_grid.x, INALTIME / 2 + pozitie_grid.y);

    //convertim din pozitia pe grid in pozitia pe ecran
    comp->grafica->pozitie = PozitieGridLaPozitieEcran(comp->GetPozitie());

    //Ajustam pozitia punctelor de conexiune
    if (comp) {
        
        ActualizeazaGraficaComponenta(comp);
        comp->grafica->Desenare(renderer);
        
        for (auto& pct : comp->puncte_conexiune)
        {

            DeseneazaButon(pct->buton);

        }
    }

}

void ActualizeazaGraficaComponenta(Componenta* comp) {
    comp->grafica->marime = factor_zoom;
    comp->grafica->pozitie = PozitieGridLaPozitieEcran(comp->GetPozitie());

    if (Conector* conector = dynamic_cast<Conector*>(comp)) {
        ActualizeazaGraficaConector(conector);
    }

    for (auto& pct : comp->puncte_conexiune)
    {
        //recalculeaza pozitia punctului de conexiune
        Vector2 v = (pct->pozitie_relativa * Grid::MARIME_CELULA * factor_zoom);
        Vector2 pozGrafica = comp->grafica->pozitie;
        Vector2 m = Vector2(Grid::MARIME_CELULA * factor_zoom, Grid::MARIME_CELULA * factor_zoom) / 2 - v;
        pct->buton->ListaElementeGrafice.front()->pozitie = pozGrafica - m;
        pct->buton->pozitie = pozGrafica - m;
        pct->buton->ListaElementeGrafice.front()->marime = factor_zoom;
    }
}

void ActualizeazaGraficaConector(Conector* con) {
    Path* path_conector = (Path*)con->grafica;
    path_conector->pozitii.clear();

    //Obtine al doilea element din lista de pozitii

    Vector2 pozCelula2;
    if (con->pozitii.size() >= 2) {
        int i = 0;
        for (auto poz : con->pozitii) {
            if (i == 1) {
                pozCelula2 = poz;
                break;
            }
            i++;
        }
    }
    else {
        return;
    }
    //printf("\n pozitie con: %f %f \n pozitie grid con %f %f \n", PozitieGridLaPozitieEcran(PozitieEcranLaPozitieGrid(con->GetPozitie())).x, PozitieGridLaPozitieEcran(PozitieEcranLaPozitieGrid(con->GetPozitie())).y, pozCelula2.x, pozCelula2.y, dirLaUrmatorulPunct.x, dirLaUrmatorulPunct.y);
    Vector2 dirLaUrmatorulPunct = con->pozitii.front() - pozCelula2;

    float distanta = sqrt(dirLaUrmatorulPunct.x * dirLaUrmatorulPunct.x + dirLaUrmatorulPunct.y * dirLaUrmatorulPunct.y);

    dirLaUrmatorulPunct = dirLaUrmatorulPunct / distanta;
    dirLaUrmatorulPunct.x *= -1;
    dirLaUrmatorulPunct.y *= -1;

    Vector2 dirLaPunctIntermediar = dirLaUrmatorulPunct * Grid::MARIME_CELULA * 0.4f * factor_zoom;


    Vector2 testVector = Vector2((float)0, Grid::MARIME_CELULA/2 * factor_zoom);

    path_conector->pozitii.push_back(con->start_conexiune->buton->pozitie);
    path_conector->pozitii.push_back(con->start_conexiune->buton->pozitie + dirLaPunctIntermediar);

    Vector2 dirIntermediar2 = dirLaUrmatorulPunct * Grid::MARIME_CELULA/2 * factor_zoom;

    path_conector->pozitii.push_back(PozitieGridLaPozitieEcran(con->pozitii.front()) + dirIntermediar2);


    for (auto pozitie : con->pozitii) {
        if (pozitie == con->pozitii.front())continue;
        path_conector->pozitii.push_back(PozitieGridLaPozitieEcran(pozitie));
    }
}
void DeseneazaGrid(int grosime) {

    SDL_SetRenderDrawColor(renderer, 15,15,15,255);
    SDL_Rect fundal = {0,0,  LATIME,INALTIME };

    SDL_RenderFillRect(renderer,&fundal);


    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

    float zoomedCellSize = Grid::MARIME_CELULA * factor_zoom;

    Vector2 gridSize = Vector2(Grid::GRID_CELULE_LATIME * zoomedCellSize, Grid::GRID_CELULE_INALTIME * zoomedCellSize);
    Vector2 gridCenter = Vector2(gridSize.x / 2, gridSize.y / 2);
    Vector2 screenCenter = Vector2(LATIME / 2 + pozitie_grid.x, INALTIME / 2 + pozitie_grid.y);



    Vector2 offset = Vector2(gridCenter.x - screenCenter.x, gridCenter.y - screenCenter.y);

    //deseneaza tabelul
    for (int x = 0; x < Grid::GRID_CELULE_LATIME + 1; x++)
    {
        int xPosition = x * zoomedCellSize - offset.x;

        SDL_Rect linie = { xPosition , gridCenter.y - offset.y - gridSize.y/2,grosime,gridSize.y };
        SDL_RenderFillRect(renderer,&linie);
        //bar(xPosition - grosime / 2, screenCenter.y - gridSize.y / 2, xPosition + grosime / 2, screenCenter.y + gridSize.y / 2);
    }
    for (int y = 0; y < Grid::GRID_CELULE_INALTIME + 1; y++)
    {
        int yPosition = y * zoomedCellSize - offset.y;

        SDL_Rect linie = { gridCenter.x -offset.x - gridSize.x/2, yPosition, gridSize.x,grosime };
        SDL_RenderFillRect(renderer, &linie);
        //bar(screenCenter.x - gridSize.x / 2, yPosition - grosime / 2, screenCenter.x + gridSize.x / 2, yPosition + grosime / 2);
    }

    SDL_SetRenderDrawColor(renderer,40,40,40,255);
    //Deseneaza punctuletele
    for (int x = 0; x < Grid::GRID_CELULE_LATIME + 1; x += 2)
    {
        for (int y = 0; y < Grid::GRID_CELULE_INALTIME + 1; y += 2)
        {
            int xPosition = x * zoomedCellSize - offset.x;
            int yPosition = y * zoomedCellSize - offset.y;

            float marime_punct = grosime * 4 * factor_zoom;

            SDL_Rect punct_decor = { xPosition - marime_punct /2 , yPosition - marime_punct/2,marime_punct,marime_punct };
            SDL_RenderFillRect(renderer, &punct_decor);
        }
    }


    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    SDL_RenderDrawLine(renderer,screenCenter.x - gridSize.x / 2, screenCenter.y - gridSize.y / 2, screenCenter.x + gridSize.x / 2, screenCenter.y - gridSize.y / 2);
    SDL_RenderDrawLine(renderer,screenCenter.x - gridSize.x / 2, screenCenter.y + gridSize.y / 2, screenCenter.x + gridSize.x / 2, screenCenter.y + gridSize.y / 2);
    SDL_RenderDrawLine(renderer,screenCenter.x - gridSize.x / 2, screenCenter.y - gridSize.y / 2, screenCenter.x - gridSize.x / 2, screenCenter.y + gridSize.y / 2);
    SDL_RenderDrawLine(renderer,screenCenter.x + gridSize.x / 2, screenCenter.y - gridSize.y / 2, screenCenter.x + gridSize.x / 2, screenCenter.y + gridSize.y / 2);
}

Vector2 PozitieGridLaPozitieEcran(Vector2 grid_poz) {

    float zoomedCellSize = Grid::MARIME_CELULA * factor_zoom;

    Vector2 gridSize = Vector2(Grid::GRID_CELULE_LATIME * zoomedCellSize, Grid::GRID_CELULE_INALTIME * zoomedCellSize);
    Vector2 gridCenter = Vector2(gridSize.x / 2, gridSize.y / 2);
    Vector2 screenCenter = Vector2(LATIME / 2 + pozitie_grid.x, INALTIME / 2 + pozitie_grid.y);

    //convertim din pozitia pe grid in pozitia pe ecran   
    Vector2 jum_gs = gridSize / 2;
    Vector2 grid_poz_vizual = (Vector2(0.5f, 0.5f) + grid_poz) * zoomedCellSize;
    return screenCenter - jum_gs + grid_poz_vizual;

}

Vector2 PozitieEcranLaPozitieGrid(Vector2 ecran_poz) {

    float marime_grid = Grid::MARIME_CELULA * factor_zoom;

    Vector2 screenCenter = Vector2(LATIME / 2 + pozitie_grid.x, INALTIME / 2 + pozitie_grid.y);

    Vector2 poz_ajustata = { ecran_poz.x - screenCenter.x - pozitie_grid.x, ecran_poz.y - screenCenter.y - pozitie_grid.y };

    Vector2 jum_celula = Vector2(marime_grid / 2, marime_grid / 2);

    // Calculate the closest cell position
    Vector2 cell = { std::floor((poz_ajustata.x + jum_celula.x) / marime_grid), std::floor((poz_ajustata.y + jum_celula.y) / marime_grid) };

    // Snap to the nearest cell
    return cell;
}

Vector2 PozitieMouseInGrid() {

    float zoomedCellSize = Grid::MARIME_CELULA * factor_zoom;
    Vector2 gridSize = Vector2(Grid::GRID_CELULE_LATIME * zoomedCellSize, Grid::GRID_CELULE_INALTIME * zoomedCellSize);
    Vector2 gridCenter = Vector2(gridSize.x / 2, gridSize.y / 2);
    Vector2 screenCenter = GetCentruEcran();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);

    Vector2 offset_grid = gridSize / 2 - screenCenter;
    //aici am calculat matematic inversa functiei din drawcomponent care converteste din pozitie in grid, in pozitie pe ecran
    Vector2 positionInGrid = (Vector2(mouseX, mouseY) + offset_grid) / zoomedCellSize;

    if (positionInGrid.x < 0 || positionInGrid.x > Grid::GRID_CELULE_LATIME - 1  || positionInGrid.y < 0 || positionInGrid.y > Grid::GRID_CELULE_INALTIME - 1) {
        positionInGrid.x = -1;
        positionInGrid.y = -1;
    }

     positionInGrid.x = (int)positionInGrid.x;
     positionInGrid.y = (int)positionInGrid.y;
    return positionInGrid;

}
Vector2 GetCentruEcran() {
    return Vector2(LATIME / 2 + pozitie_grid.x, INALTIME / 2 + pozitie_grid.y);
}

bool VerificaColiziune(Vector2 pozitie_in_grid) {
    for (auto comp: toate_componentele)
    {
        if (Conector* conector = dynamic_cast<Conector*>(comp)) {
            for (auto poz : conector->pozitii) {
                if (poz == pozitie_in_grid) {
                    return true;
                }
            }
        }
        if (comp->GetPozitie().x == pozitie_in_grid.x && comp->GetPozitie().y == pozitie_in_grid.y) {
            return true;
        }
    }
    return false;
}

void SelecteazaPunctConexiune(PunctConexiune* pct) {

    if (pct_conex_selectat != NULL)pct_conex_selectat->buton->dimensiuni = Vector2(15, 15);
    
    pct_conex_selectat = pct;
    pct_conex_selectat->buton->dimensiuni = Vector2(25,25);

    RefreshUI();
    
    
    if (callback_slectare_pct_conex != NULL) {
        callback_slectare_pct_conex(pct);
    }

}

//Butoane-----------------------------------------------------

bool ButonApasat(Buton* btn, Vector2 clickPos) {
    Vector2 dimScalat = btn->dimensiuni * btn->marime;
    if (clickPos.x > btn->pozitie.x - dimScalat.x / 2 && clickPos.x < btn->pozitie.x + dimScalat.x / 2)
        if (clickPos.y > btn->pozitie.y - dimScalat.y / 2 && clickPos.y < btn->pozitie.y + dimScalat.y / 2)
            return true;
    return false;
}

void InregistrareButon(Buton* buton_new) {
    toate_butoanele.push_back(buton_new);
}

void ProcesareButoane(Vector2 poz_click) {
    //functia asta va fi apelata doar cand se apasa click

    for (auto& btn : toate_butoanele) {
        //verificam daca clickul este pe vreunul dintre butoane
        //daca e, il consideram apasat

        if (ButonApasat(btn, poz_click)) {
            btn->ActionareClick();
        }

    }
}

void DeseneazaButon(Buton* btn) {
    for (auto& el_grafic : btn->ListaElementeGrafice) {
        el_grafic->Desenare(renderer);
    }
}


void DeseneazaToateButoanele() {
    for (auto& btn : toate_butoanele) {
        DeseneazaButon(btn);
    }
}

//Puncte conexiune------------------------------------

void ProceseazaClickPuncteConexiune(Vector2 poz_click) {
    for (auto& comp : toate_componentele)
    {   
        
        if (comp) { // Check if comp is not null
            for (auto& pct : comp->puncte_conexiune)
            {
                if (pct && ButonApasat(pct->buton, poz_click)) {
                    SelecteazaPunctConexiune(pct);
                }
            }
        }
        
    }

}

//Procesare grafica------------------
