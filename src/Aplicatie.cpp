#include "Aplicatie.h"

bool Aplicatie::InitializareAplicatie() {
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    InitializareTipuriComponente();

    simulator = SimulatorCircuit();

    return true;
}

void Aplicatie::InchidereAplicatie() {
    InchidereUIManager();
    SDL_Quit();
}

 Buton* Aplicatie::CreareButon(Vector2 pozitie, Vector2 dimensiune,SDL_Color culoare_buton, SDL_Color culoare_componenta, const char* path_imagine,int index_btn) {
    Buton* buton = new Buton(pozitie, dimensiune);
    ImagineGrafica* imagine = new ImagineGrafica();
    imagine->path = path_imagine;
    imagine->culoare = culoare_componenta;
    imagine->dimensiuni = dimensiune;
    imagine->pozitie = pozitie;
    imagine->marime = 1;
    DreptunghiGrafic* fundal = new DreptunghiGrafic();
    fundal->culoare = culoare_buton;
    fundal->dimensiuni = dimensiune;
    fundal->pozitie = pozitie;
    fundal->marime = 1;
    buton->AdaugaElementGrafic(fundal);
    buton->AdaugaElementGrafic(imagine);


    auto actiune_click = [=]() {
        pozitionator_componente::SelectareComponentaPozitionare(index_btn);
    };

    buton->actiune_click = actiune_click;
    InregistrareButon(buton);
    return buton;
}


void Aplicatie::InitializareUI() {
    //register buttons

    InititalizareUIManager();
    desenator_conectori::InitializareDesenatorConectori();
    editor_componente::InitializareEditor();

    SDL_Color culoare_btn = {60,60,60};
    SDL_Color culoare_comp = {150,150,150 };

    WindowGrafic* footer_butoane = new WindowGrafic();

    DreptunghiGrafic* bg_footer = new DreptunghiGrafic();
    bg_footer->dimensiuni = Vector2((float)LATIME, (float)(60 + MARIME_COMPONENTE/2 + (60 - MARIME_COMPONENTE/2)));
    bg_footer->marime = 1;
    bg_footer->pozitie = Vector2(LATIME / 2.0f, INALTIME - bg_footer->dimensiuni.y / 2);
    bg_footer->culoare = SDL_Color{30,30,30};

    footer_butoane->AdaugaElementGrafic(bg_footer);

    auto fct_simulare = [this]() {simulator.Simuleaza(GetToateComponentele()); RefreshUI(); };

    Buton* zoomInBtn = new Buton(Vector2(40, INALTIME - 60), Vector2(60, 30), fct_simulare);
    
    DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
    bg_btn->culoare = culoare_btn;
    bg_btn->dimensiuni = Vector2(60, 30);
    bg_btn->pozitie = Vector2(40, INALTIME - 60);
    bg_btn->marime = 1;

    TextGrafic* text_btn1 = new TextGrafic();
    text_btn1->culoare = SDL_Color{ 255,255,255,255 };
    text_btn1->dimensiuni = Vector2(50, 20);
    text_btn1->pozitie = Vector2(40, INALTIME - 60);
    text_btn1->marime = 1;
    text_btn1->text = "Simuleaza";

    zoomInBtn->AdaugaElementGrafic(bg_btn);
    zoomInBtn->AdaugaElementGrafic(text_btn1);

    Buton* zoomOutBtn = new Buton( Vector2(120, INALTIME - 60), Vector2(60, 30), ZoomOut);

    DreptunghiGrafic* bg_btn2 = new DreptunghiGrafic();
    bg_btn2->culoare = culoare_btn;
    bg_btn2->dimensiuni = Vector2(60, 30);
    bg_btn2->pozitie = Vector2(120, INALTIME - 60);
    bg_btn2->marime = 1;

    TextGrafic* text_btn2 = new TextGrafic();
    text_btn2->culoare = SDL_Color{ 255,255,255,255 };
    text_btn2->dimensiuni = Vector2(50, 20);
    text_btn2->pozitie = Vector2(120, INALTIME - 60);
    text_btn2->marime = 1;
    text_btn2->text = "-";

    zoomOutBtn->AdaugaElementGrafic(bg_btn2);
    zoomOutBtn->AdaugaElementGrafic(text_btn2);

    DreptunghiGrafic* bg_btn3 = new DreptunghiGrafic();
    bg_btn3->culoare = culoare_btn;
    bg_btn3->dimensiuni = zoomOutBtn->dimensiuni;
    bg_btn3->pozitie = Vector2(225, INALTIME - 60);
    bg_btn3->marime = 1;

    zoomOutBtn->AdaugaElementGrafic(bg_btn3);

    int marime_buton = 80;


    Buton* rezistor = CreareButon(Vector2(225, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/rezistor.bmp", 0);
    Buton* intrerupator = CreareButon(Vector2(335, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/intrerupator.bmp", 1);
    Buton* andGate = CreareButon(Vector2(445, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/andgate.bmp", 2);
    Buton* capacitor = CreareButon(Vector2(555, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/capacitor.bmp", 3);
    Buton* dioda2linii = CreareButon(Vector2(665, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/dioda2linii.bmp", 4);
    Buton* diodacerc = CreareButon(Vector2(775, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/diodacerc.bmp", 5);
    Buton* impamantare = CreareButon(Vector2(885, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/impamantare.bmp", 6);
    Buton* sursavoltaj = CreareButon(Vector2(995, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/sursavoltaj.bmp", 7);
    Buton* tranzistor = CreareButon(Vector2(1105, INALTIME - 60), Vector2(marime_buton, marime_buton), culoare_btn, culoare_comp, "Desenecomponente/tranzistor.bmp", 8);
    
    InregistrareButon(zoomInBtn);
    footer_butoane->AdaugaButon(zoomOutBtn);
    footer_butoane->AdaugaButon(rezistor);
    footer_butoane->AdaugaButon(intrerupator);
    footer_butoane->AdaugaButon(andGate);
    footer_butoane->AdaugaButon(capacitor);
    footer_butoane->AdaugaButon(dioda2linii);
    footer_butoane->AdaugaButon(diodacerc);
    footer_butoane->AdaugaButon(impamantare);
    footer_butoane->AdaugaButon(sursavoltaj);
    footer_butoane->AdaugaButon(tranzistor);
    
    InregistreazaWindowGrafic(footer_butoane);

    RefreshUI();
}

void Aplicatie::ProcesareClick(SDL_Event* actiune_mouse) {

    int x, y;
    SDL_GetMouseState(&x, &y);
    switch (actiune_mouse->type) {
    case SDL_MOUSEBUTTONDOWN:
        if (actiune_mouse->button.button == SDL_BUTTON_LEFT) {
            pozitionator_componente::ProcesareClickPlasare();
            ProceseazaClickPuncteConexiune(Vector2(x,y));
            ProcesareButoane(Vector2(x, y));
            editor_componente::ProcesareClick(x,y);
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

        ProcesareActiuniListaButoane();

        while (SDL_PollEvent(&actiune_input) != 0) {
            if (actiune_input.type == SDL_QUIT) {
                running = false;
            }
            else {
                ProcesareClick(&actiune_input);
            }
        }

        pozitionator_componente::ProcesarePlasare();
        desenator_conectori::ProcesareConectare();

        SDL_Delay(5);
    }
    InchidereAplicatie();

    return;

}