#pragma once
#include "UIManager.h"
#include<math.h>
const int LATIME = 1200;
const int INALTIME = 800;
float factor_zoom = 1;
float rata_zoom = 1.2f;


Vector2 pozitie_grid;


PunctConexiune* pct_conex_selectat;
PctConexSelectatCallback callback_slectare_pct_conex;

list<RefreshUICallback> refresh_ui_listeners;


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

void EliminaComponenta(Componenta* comp) {
    toate_componentele.remove(comp);
}


void ShowTabelDetalii(Componenta* comp) {
    
}

void RefreshUI() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    DeseneazaGrid(2);

    DeseneazaComponente();

    ////facem callback pentru UI-ul refreshuit
    for (auto& callback : refresh_ui_listeners) {
        callback();
    }
    DeseneazaWindowuriGrafice();

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
        
        for (int i = 0; i < comp->nr_pct_conexiune; i++)
        {
            DeseneazaButon(comp->puncte_conexiune[i].buton);
        }

    }

}

void ActualizeazaGraficaComponenta(Componenta* comp) {
    comp->grafica->marime = factor_zoom;
    comp->grafica->pozitie = PozitieGridLaPozitieEcran(comp->GetPozitie());
    switch (comp->rotatie)
    {
    case DREAPTA:
        comp->grafica->rotatie = 0;
        break;
    case JOS:
        comp->grafica->rotatie = 90;
        break;
    case STANGA:
        comp->grafica->rotatie = 180;
        break;
    case SUS:
        comp->grafica->rotatie = 270;
        break;
    default:
        comp->grafica->rotatie = 0;
        break;
    }

    if (Conector* conector = dynamic_cast<Conector*>(comp)) {
        ActualizeazaGraficaConector(conector);
    }

    for (int i = 0; i < comp->nr_pct_conexiune; i++)
    {
        ActualizeazaGraficaPctConex(comp, &comp->puncte_conexiune[i]);
    }
}

void ActualizeazaGraficaPctConex(Componenta* comp, PunctConexiune* pct)
{
    Vector2 poz_rotita;

    switch (comp->rotatie)
    {
    case DREAPTA:
        poz_rotita = pct->pozitie_relativa;
        break;
    case STANGA:
        poz_rotita = Vector2(1 - pct->pozitie_relativa.x, 1 - pct->pozitie_relativa.y);
        break;
    case SUS:
        poz_rotita = Vector2(pct->pozitie_relativa.y, 1 - pct->pozitie_relativa.x);
        break;
    case JOS:
        poz_rotita = Vector2(1- pct->pozitie_relativa.y, pct->pozitie_relativa.x);
        break; 
    default:
        pct->pozitie_relativa;
        break;
    }

    Vector2 v = (poz_rotita * Grid::MARIME_CELULA * factor_zoom);


    Vector2 pozGrafica = comp->grafica->pozitie;
    Vector2 m = Vector2(Grid::MARIME_CELULA * factor_zoom, Grid::MARIME_CELULA * factor_zoom) / 2 - v;
    pct->buton->ListaElementeGrafice.front()->pozitie = pozGrafica - m;
    pct->buton->pozitie = pozGrafica - m;
    pct->buton->ListaElementeGrafice.front()->marime = factor_zoom;

    if (pct->conector != NULL) {
        pct->buton->ListaElementeGrafice.front()->culoare = CUL_PCT_CONEX_OCUPAT;
        ((DreptunghiGrafic*)pct->buton->ListaElementeGrafice.front())->dimensiuni = Vector2(Grid::MARIME_PCT_CONEX_OCUPAT, Grid::MARIME_PCT_CONEX_OCUPAT);
    }
    else {
        pct->buton->ListaElementeGrafice.front()->culoare = CUL_PCT_CONEX_LIBER;
        ((DreptunghiGrafic*)pct->buton->ListaElementeGrafice.front())->dimensiuni = Vector2(Grid::MARIME_PCT_CONEX_LIBER, Grid::MARIME_PCT_CONEX_LIBER);
    }
}

void ActualizeazaGraficaConector(Conector* con) {
    //incerc sa adaug conectorul de start daca exista
    Path* grafica = (Path*)con->grafica;
    grafica->pozitii.clear();

    if (con->start_conexiune != NULL) {
        Vector2 poz_ecran_pct = con->start_conexiune->buton->pozitie;
        grafica->pozitii.push_back(poz_ecran_pct);

        if (!con->pozitii.empty()) {
            DeseneazaLegaturaPctLaConector(con->start_conexiune, con->pozitii.front(), grafica);
        }
    }

    //adaug restul pozitiilor
    for (auto &poz: con->pozitii)
    {
        grafica->pozitii.push_back(PozitieGridLaPozitieEcran(poz));
    }


    //incer sa adaug conector final daca exista
    if (con->final_conexiune != NULL) {
        Vector2 poz_ecran_pct = con->final_conexiune->buton->pozitie;
        grafica->pozitii.push_back(poz_ecran_pct);

        if (!con->pozitii.empty()) {
            DeseneazaLegaturaPctLaConector(con->start_conexiune, con->pozitii.back(), grafica);
        }
    }
}

void DeseneazaLegaturaPctLaConector(PunctConexiune* pct, Vector2 g_poz_conector /* g_ = pozitie in grid*/, Path* grafica) {
    Vector2 g_poz_pct = pct->parinte->GetPozitie();
    Vector2 e_poz_pct = PozitieGridLaPozitieEcran(g_poz_pct);
    
    Vector2 dir_fwd = g_poz_conector - g_poz_pct;
    Vector2 dir_dreapta = Vector2(dir_fwd.y, -dir_fwd.x);

    ORIENTARE orientare_rotita_pct = (ORIENTARE)(((int)pct->orientare + (int)pct->parinte->rotatie)%4);

    ORIENTARE orientare_spre_dest = DREAPTA;

    Vector2 mij_margine_pct = e_poz_pct;

    float marime_cel_scalata = Grid::MARIME_CELULA * factor_zoom;

    switch (orientare_rotita_pct)
    {
    case DREAPTA:
        mij_margine_pct.x += 0.4 * marime_cel_scalata;
        break;
    case JOS:
        mij_margine_pct.y += 0.4 * marime_cel_scalata;
        break;
    case STANGA:
        mij_margine_pct.x -= 0.4 * marime_cel_scalata;
        break;
    case SUS:
        mij_margine_pct.y -= 0.4 * marime_cel_scalata;
        break;
    default:
        break;
    }

    if (g_poz_conector.x > g_poz_pct.x) {
        orientare_spre_dest = DREAPTA;
    }
    else if(g_poz_conector.x < g_poz_pct.x){
        orientare_spre_dest = STANGA;
    }else  if (g_poz_conector.y> g_poz_pct.y) {
        orientare_spre_dest = JOS;
    }
    else if (g_poz_conector.y < g_poz_pct.y) {
        orientare_spre_dest = SUS;
    }
    
    int abs_dif = std::abs((int)orientare_spre_dest - (int)orientare_rotita_pct);
    int semn_dif = (int)orientare_spre_dest - (int)orientare_rotita_pct;

    printf("orientare punct %d, orientare componenta  %d, directia la urmator %d", (int)pct->orientare,(int)pct->parinte->rotatie, (int)orientare_spre_dest );

    switch (abs_dif) {
    case 0:
        //aceeasi directie
        return;
        break;
    case 2:
        //directie opusa
        grafica->pozitii.push_back(mij_margine_pct + (dir_fwd * 0.1f * marime_cel_scalata + (dir_dreapta * 0.4f * marime_cel_scalata)));
        grafica->pozitii.push_back(mij_margine_pct + (dir_fwd * 0.9f * marime_cel_scalata + (dir_dreapta * 0.4f * marime_cel_scalata)));
        break;
    case 1:
        //stanga sau dreapta
        grafica->pozitii.push_back(mij_margine_pct + (dir_fwd * 0.1f * marime_cel_scalata + (dir_dreapta * 0.4f * marime_cel_scalata * semn_dif)));
        grafica->pozitii.push_back(mij_margine_pct + (dir_fwd * 0.5f * marime_cel_scalata + (dir_dreapta * 0.4f * marime_cel_scalata * semn_dif)));
        break;
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

    Vector2 offset_grid = gridSize / 2 - screenCenter;
    //aici am calculat matematic inversa functiei din drawcomponent care converteste din pozitie in grid, in pozitie pe ecran
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

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

Componenta* VerificaColiziuneComponenta(Vector2 pozitie_in_grid) {
    for (auto comp : toate_componentele)
    {
        if (comp->GetPozitie().x == pozitie_in_grid.x && comp->GetPozitie().y == pozitie_in_grid.y) {
            return comp;
        }
    }
    return NULL;
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
    coada_actiuni_lista_butoane.push(ActiuneListaButoane{ADAUGA ,buton_new});
}

void EliminaButon(Buton* buton) {
    coada_actiuni_lista_butoane.push(ActiuneListaButoane{ELIMINA ,buton});
}

void ProcesareActiuniListaButoane() {
    if (coada_actiuni_lista_butoane.empty())return;
    
    while (!coada_actiuni_lista_butoane.empty()) {
        ActiuneListaButoane temp = coada_actiuni_lista_butoane.front();

        if (temp.tip_actiune == ADAUGA) {
            toate_butoanele.push_back(temp.buton);
        }
        else {
            toate_butoanele.remove(temp.buton);
        }

        coada_actiuni_lista_butoane.pop();
    }

    RefreshUI();
}

void ProcesareButoane(Vector2 poz_click) {

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
            for (int i = 0; i < comp->nr_pct_conexiune;i++)
            {
                if (ButonApasat(comp->puncte_conexiune[i].buton, poz_click)) {
                    SelecteazaPunctConexiune(&comp->puncte_conexiune[i]);
                }
            }
        }
        
    }

}
bool SuntCeluleAdiacente(Vector2 poz1, Vector2 poz2) {

    return (abs(poz1.x - poz2.x) + abs(poz1.y - poz2.y) == 1);
}
Vector2 CelulaAdiacentaInDir(Vector2 poz, ORIENTARE dir) {
    switch (dir)
    {
    case STANGA:
        return Vector2(poz.x - 1, poz.y);
        break;
    case DREAPTA:
        return Vector2(poz.x + 1, poz.y);
        break;
    case SUS:
        return Vector2(poz.x, poz.y + 1);
        break;
    case JOS:
        return Vector2(poz.x, poz.y - 1);
        break;
    default:
        break;
    }
}

PunctConexiune* MousePestePuctConexiune(Vector2 poz_mouse) {

    for (auto& comp : toate_componentele)
    {
        if (comp) {
            for (int i = 0; i < comp->nr_pct_conexiune; i++)
            {
                if (comp->puncte_conexiune[i].conector == NULL) {
                    if (ButonApasat(comp->puncte_conexiune[i].buton, poz_mouse)) {
                        return &comp->puncte_conexiune[i];
                    }
                }
            }
        }

    }
    return NULL;
}

void DeseneazaWindowuriGrafice() {
    for (auto& window : toate_windowurile) {
        DeseneazaWindowGrafic(window);
    }
}

void DeseneazaWindowGrafic(WindowGrafic* window) {
    for (auto& element : window->elem_grafice) {
        element->Desenare(renderer);
    }
}

void InregistreazaWindowGrafic(WindowGrafic* window) {
    toate_windowurile.push_back(window);
    for (auto& btn : window->butoane) {
        InregistrareButon(btn);
    }
}
void EliminaWindowGrafic(WindowGrafic* window) {
    toate_windowurile.remove(window);
    if (window->butoane.empty())return;
    for (auto& btn : window->butoane) {
        EliminaButon(btn);
    }
}
