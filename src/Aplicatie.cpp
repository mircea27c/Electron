#include "Aplicatie.h"
void Aplicatie::StartPlasare() {
    ImagineGrafica* bg_btn4 = new ImagineGrafica();
    bg_btn4->path = "Desenecomponente/rezistor.bmp";
    bg_btn4->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn4->dimensiuni = Vector2(50, 50);
    bg_btn4->pozitie = Vector2(300, INALTIME - 60);
    bg_btn4->marime = 1;

    Componenta* comp = new Componenta();
    SelectareComponenta(comp);
    comp->grafica = bg_btn4;
}

bool Aplicatie::InitializareAplicatie() {
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Aplicatie::InchidereAplicatie() {
    InchidereUIManager();
    SDL_Quit();
}

void Aplicatie::InitializareUI() {
    //register buttons

    InititalizareUIManager();
    desenator_conectori::InitializareDesenatorConectori();

    for (int i = 0; i < 10; i++)
    {
        auto functie_selectare_comp = [i]() -> void {

            return;
        };
        //arrayTest[i] = functie_selectare_comp;

    }

    Buton* zoomInBtn = new Buton(Vector2(80, INALTIME - 60), Vector2(60, 30), ZoomIn);
    
    DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
    bg_btn->culoare = SDL_Color{ 80,80,80,255 };
    bg_btn->dimensiuni = Vector2(60, 30);
    bg_btn->pozitie = Vector2(80, INALTIME - 60);
    bg_btn->marime = 1;

    TextGrafic* text_btn1 = new TextGrafic();
    text_btn1->culoare = SDL_Color{ 255,255,255,255 };
    text_btn1->dimensiuni = Vector2(50, 20);
    text_btn1->pozitie = Vector2(80, INALTIME - 60);
    text_btn1->marime = 1;
    text_btn1->text = "+";

    zoomInBtn->AdaugaElementGrafic(bg_btn);
    zoomInBtn->AdaugaElementGrafic(text_btn1);

    Buton* zoomOutBtn = new Buton( Vector2(160, INALTIME - 60), Vector2(60, 30), ZoomOut);

    DreptunghiGrafic* bg_btn2 = new DreptunghiGrafic();
    bg_btn2->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn2->dimensiuni = Vector2(60, 30);
    bg_btn2->pozitie = Vector2(160, INALTIME - 60);
    bg_btn2->marime = 1;

    TextGrafic* text_btn2 = new TextGrafic();
    text_btn2->culoare = SDL_Color{ 255,255,255,255 };
    text_btn2->dimensiuni = Vector2(50, 20);
    text_btn2->pozitie = Vector2(160, INALTIME - 60);
    text_btn2->marime = 1;
    text_btn2->text = "-";

    zoomOutBtn->AdaugaElementGrafic(bg_btn2);
    zoomOutBtn->AdaugaElementGrafic(text_btn2);

    Buton* placeButton = new Buton(Vector2(300, INALTIME - 60), Vector2(100, 30), StartPlasare);

    DreptunghiGrafic* bg_btn3 = new DreptunghiGrafic();
    bg_btn3->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn3->dimensiuni = Vector2(100, 30);
    bg_btn3->pozitie = Vector2(300, INALTIME - 60);
    bg_btn3->marime = 1;


    ImagineGrafica* bg_btn4 = new ImagineGrafica();
    bg_btn4->path = "Desenecomponente/rezistor.bmp";
    bg_btn4->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn4->dimensiuni = Vector2(100, 30);
    bg_btn4->pozitie = Vector2(300, INALTIME - 60);
    bg_btn4->marime = 1;
    
    placeButton->AdaugaElementGrafic(bg_btn4);
    zoomOutBtn->AdaugaElementGrafic(bg_btn3);

   


    InregistrareButon(zoomInBtn);
    InregistrareButon(zoomOutBtn);
    InregistrareButon(placeButton);
    DeseneazaToateButoanele();

    RefreshUI();
}

void Aplicatie::ProcesareClick(SDL_Event* actiune_mouse) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    switch (actiune_mouse->type) {
    case SDL_MOUSEBUTTONDOWN:
        if (actiune_mouse->button.button == SDL_BUTTON_LEFT) {
            ProcesareClickPlasare();
            ProceseazaClickPuncteConexiune(Vector2(x,y));
            ProcesareButoane(Vector2(x, y));
        }
        if (actiune_mouse->button.button == SDL_BUTTON_RIGHT) {
            Vector2 mouseInGrid = PozitieMouseInGrid();
            cout << mouseInGrid.x << " " << mouseInGrid.y << endl;
        }
        if (actiune_mouse->button.button == SDL_BUTTON_MIDDLE) {
            middle_btn_apasat = true;
        }

        break;
    case SDL_MOUSEBUTTONUP:
        if (actiune_mouse->button.button == SDL_BUTTON_LEFT) {
            desenator_conectori::ProcesareStopClickDesenare();
        }
        if (actiune_mouse->button.button == SDL_BUTTON_RIGHT) {
        }
        if (actiune_mouse->button.button == SDL_BUTTON_MIDDLE) {
            middle_btn_apasat = false;
        }
        break;
    case SDL_MOUSEMOTION:
        if (middle_btn_apasat) {
            pozitie_grid.x += (x - mouse_ultima_poz.x);
            pozitie_grid.y += (y - mouse_ultima_poz.y);

            RefreshUI();
        }
        break;
    case SDL_MOUSEWHEEL:
        if (actiune_mouse->wheel.y > 0) {
            ZoomIn();
        }
        else if (actiune_mouse->wheel.y < 0) {
            ZoomOut();
        }
        break;
    }

    mouse_ultima_poz.x = x;
    mouse_ultima_poz.y = y;
}

float Aplicatie::ParteFractionara(float nr) {
    return nr - (int)nr;
}

void Aplicatie::Ruleaza()
{
    InitializareAplicatie();
    InitializareUI();
 
    bool running = true;
    SDL_Event actiune_input;

    while (running) {

        while (SDL_PollEvent(&actiune_input) != 0) {
            if (actiune_input.type == SDL_QUIT) {
                running = false;
            }
            else {
                ProcesareClick(&actiune_input);
            }
        }

        ProcesarePlasare();
        desenator_conectori::ProcesareConectare();

        SDL_Delay(5);
    }
    InchidereAplicatie();

    return;

}