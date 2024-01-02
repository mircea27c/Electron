#include "Aplicatie.h"

bool Aplicatie::InitializareAplicatie() {
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    InitializareTipuriComponente();

    return true;
}

void Aplicatie::InchidereAplicatie() {
    InchidereUIManager();
    SDL_Quit();
}

/* Buton* creare_buton(Vector2 pozitie, Vector2 dimensiune, const char* path_imagine, std::function<void()> actiune_click) {
    Buton* buton = new Buton(pozitie, dimensiune);
    ImagineGrafica* imagine = new ImagineGrafica();
    imagine->path = path_imagine;
    imagine->culoare = SDL_Color{ 150,150,150,255 };
    imagine->dimensiuni = dimensiune;
    imagine->pozitie = pozitie;
    imagine->marime = 1;
    DreptunghiGrafic* fundal = new DreptunghiGrafic();
    fundal->culoare = SDL_Color{ 80,80,80,80 };
    fundal->dimensiuni = dimensiune;
    fundal->pozitie = pozitie;
    fundal->marime = 1;
    buton->AdaugaElementGrafic(fundal);
    buton->AdaugaElementGrafic(imagine);
   buton->actiune_click = actiune_click;
    InregistrareButon(buton);
    return buton;
}*/


void Aplicatie::InitializareUI() {
    //register buttons

    InititalizareUIManager();
    desenator_conectori::InitializareDesenatorConectori();
    editor_componente::InitializareEditor();

   // Buton* intrerupator = creare_buton(Vector2(335, INALTIME - 60), Vector2(50, 50), "Desenecomponente/intrerupator.bmp", {
   // SelectareComponentaPozitionare(1);
     //   });


    Buton* zoomInBtn = new Buton(Vector2(40, INALTIME - 60), Vector2(60, 30), ZoomIn);
    
    DreptunghiGrafic* bg_btn = new DreptunghiGrafic();
    bg_btn->culoare = SDL_Color{ 80,80,80,255 };
    bg_btn->dimensiuni = Vector2(60, 30);
    bg_btn->pozitie = Vector2(40, INALTIME - 60);
    bg_btn->marime = 1;

    TextGrafic* text_btn1 = new TextGrafic();
    text_btn1->culoare = SDL_Color{ 255,255,255,255 };
    text_btn1->dimensiuni = Vector2(50, 20);
    text_btn1->pozitie = Vector2(40, INALTIME - 60);
    text_btn1->marime = 1;
    text_btn1->text = "+";

    zoomInBtn->AdaugaElementGrafic(bg_btn);
    zoomInBtn->AdaugaElementGrafic(text_btn1);

    Buton* zoomOutBtn = new Buton( Vector2(120, INALTIME - 60), Vector2(60, 30), ZoomOut);

    DreptunghiGrafic* bg_btn2 = new DreptunghiGrafic();
    bg_btn2->culoare = SDL_Color{ 80,80,80,80 };
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

    Buton* rezistor = new Buton(Vector2(225, INALTIME - 60), Vector2(50, 50));//vect2 100 30

    auto fct_select_rezistor = []() {
        SelectareComponentaPozitionare(0);
    };
    rezistor->actiune_click = fct_select_rezistor;

    DreptunghiGrafic* bg_btn3 = new DreptunghiGrafic();
    bg_btn3->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn3->dimensiuni = Vector2(50, 50);
    bg_btn3->pozitie = Vector2(225, INALTIME - 60);
    bg_btn3->marime = 1;


    ImagineGrafica* bg_btn4 = new ImagineGrafica();
    bg_btn4->path = "Desenecomponente/rezistor.bmp";
    bg_btn4->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn4->dimensiuni = Vector2(50, 50);
    bg_btn4->pozitie = Vector2(225, INALTIME - 60);
    bg_btn4->marime = 1;
    //placeButton->AdaugaElementGrafic(bg_btn4);
    zoomOutBtn->AdaugaElementGrafic(bg_btn3);
    rezistor->AdaugaElementGrafic(bg_btn3);
    rezistor->AdaugaElementGrafic(bg_btn4);

    Buton* intrerupator = new Buton(Vector2(335, INALTIME - 60), Vector2(50, 50));

    auto fct_select_intrerupator = []() {
        SelectareComponentaPozitionare(1);
        };

    intrerupator->actiune_click = fct_select_intrerupator;

    DreptunghiGrafic* bg_btn5 = new DreptunghiGrafic();

    bg_btn5->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn5->dimensiuni = Vector2(50, 50);
    bg_btn5->pozitie = Vector2(335, INALTIME - 60);
    bg_btn5->marime = 1;

    ImagineGrafica* bg_btn6 = new ImagineGrafica();

    bg_btn6->path = "Desenecomponente/intrerupator.bmp";
    bg_btn6->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn6->dimensiuni = Vector2(50, 50);
    bg_btn6->pozitie = Vector2(335, INALTIME - 60);
    bg_btn6->marime = 1;

    intrerupator->AdaugaElementGrafic(bg_btn5);
    intrerupator->AdaugaElementGrafic(bg_btn6); 
   

    Buton* andGate = new Buton(Vector2(445, INALTIME - 60), Vector2(50, 50));

   auto fct_select_andGate = []() {
       SelectareComponentaPozitionare(2);
       };

   andGate->actiune_click = fct_select_andGate;

    DreptunghiGrafic* bg_btn7 = new DreptunghiGrafic();

    bg_btn7->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn7->dimensiuni = Vector2(50, 50);
    bg_btn7->pozitie = Vector2(445, INALTIME - 60);
    bg_btn7->marime = 1;

    ImagineGrafica* bg_btn8 = new ImagineGrafica();

    bg_btn8->path = "Desenecomponente/andgate.bmp";
    bg_btn8->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn8->dimensiuni = Vector2(50, 50);
    bg_btn8->pozitie = Vector2(445, INALTIME - 60);
    bg_btn8->marime = 1;

    andGate->AdaugaElementGrafic(bg_btn7);
    andGate->AdaugaElementGrafic(bg_btn8);

    Buton* capacitor = new Buton(Vector2(555, INALTIME - 60), Vector2(50, 50));

    auto fct_select_capacitor = []() {
        SelectareComponentaPozitionare(3);
        };

    capacitor->actiune_click = fct_select_capacitor;

    DreptunghiGrafic* bg_btn9 = new DreptunghiGrafic();

    bg_btn9->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn9->dimensiuni = Vector2(50, 50);
    bg_btn9->pozitie = Vector2(555, INALTIME - 60);
    bg_btn9->marime = 1;

    ImagineGrafica* bg_btn10 = new ImagineGrafica();

    bg_btn10->path = "Desenecomponente/capacitor.bmp";
    bg_btn10->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn10->dimensiuni = Vector2(50, 50);
    bg_btn10->pozitie = Vector2(555, INALTIME - 60);
    bg_btn10->marime = 1;

    capacitor->AdaugaElementGrafic(bg_btn9);
    capacitor->AdaugaElementGrafic(bg_btn10);

    Buton* dioda2linii = new Buton(Vector2(665, INALTIME - 60), Vector2(50, 50));

    auto fct_select_dioda2linii = []() {
        SelectareComponentaPozitionare(4);
        };

    dioda2linii->actiune_click = fct_select_dioda2linii;

    DreptunghiGrafic* bg_btn11 = new DreptunghiGrafic();

    bg_btn11->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn11->dimensiuni = Vector2(50, 50);
    bg_btn11->pozitie = Vector2(665, INALTIME - 60);
    bg_btn11->marime = 1;

    ImagineGrafica* bg_btn12 = new ImagineGrafica();

    bg_btn12->path = "Desenecomponente/dioda2linii.bmp";
    bg_btn12->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn12->dimensiuni = Vector2(50, 50);
    bg_btn12->pozitie = Vector2(665, INALTIME - 60);
    bg_btn12->marime = 1;

    dioda2linii->AdaugaElementGrafic(bg_btn11);
    dioda2linii->AdaugaElementGrafic(bg_btn12);

    Buton* diodacerc = new Buton(Vector2(775, INALTIME - 60), Vector2(50, 50));

    auto fct_select_diodacerc = []() {
        SelectareComponentaPozitionare(5);
        };

    diodacerc->actiune_click = fct_select_diodacerc;

    DreptunghiGrafic* bg_btn13 = new DreptunghiGrafic();

    bg_btn13->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn13->dimensiuni = Vector2(50, 50);
    bg_btn13->pozitie = Vector2(775, INALTIME - 60);
    bg_btn13->marime = 1;

    ImagineGrafica* bg_btn14 = new ImagineGrafica();

    bg_btn14->path = "Desenecomponente/diodacerc.bmp";
    bg_btn14->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn14->dimensiuni = Vector2(50, 50);
    bg_btn14->pozitie = Vector2(775, INALTIME - 60);
    bg_btn14->marime = 1;

    diodacerc->AdaugaElementGrafic(bg_btn13);
    diodacerc->AdaugaElementGrafic(bg_btn14);

    Buton* impamantare = new Buton(Vector2(885, INALTIME - 60), Vector2(50, 50));

    auto fct_select_impamantare = []() {
        SelectareComponentaPozitionare(6);
        };

    impamantare->actiune_click = fct_select_impamantare;

    DreptunghiGrafic* bg_btn15 = new DreptunghiGrafic();

    bg_btn15->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn15->dimensiuni = Vector2(50, 50);
    bg_btn15->pozitie = Vector2(885, INALTIME - 60);
    bg_btn15->marime = 1;

    ImagineGrafica* bg_btn16 = new ImagineGrafica();

    bg_btn16->path = "Desenecomponente/impamantare.bmp";
    bg_btn16->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn16->dimensiuni = Vector2(50, 50);
    bg_btn16->pozitie = Vector2(885, INALTIME - 60);
    bg_btn16->marime = 1;

    impamantare->AdaugaElementGrafic(bg_btn15);
    impamantare->AdaugaElementGrafic(bg_btn16);

    Buton* sursavoltaj = new Buton(Vector2(995, INALTIME - 60), Vector2(50, 50));

    auto fct_select_sursavoltaj = []() {
        SelectareComponentaPozitionare(7);
        };

    sursavoltaj->actiune_click = fct_select_sursavoltaj;

    DreptunghiGrafic* bg_btn17 = new DreptunghiGrafic();

    bg_btn17->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn17->dimensiuni = Vector2(50, 50);
    bg_btn17->pozitie = Vector2(995, INALTIME - 60);
    bg_btn17->marime = 1;

    ImagineGrafica* bg_btn18 = new ImagineGrafica();

    bg_btn18->path = "Desenecomponente/sursavoltaj.bmp";
    bg_btn18->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn18->dimensiuni = Vector2(50, 50);
    bg_btn18->pozitie = Vector2(995, INALTIME - 60);
    bg_btn18->marime = 1;

    sursavoltaj->AdaugaElementGrafic(bg_btn17);
    sursavoltaj->AdaugaElementGrafic(bg_btn18);

    Buton* tranzistor = new Buton(Vector2(1105, INALTIME - 60), Vector2(50, 50));

    auto fct_select_tranzistor = []() {
        SelectareComponentaPozitionare(8);
        };

    tranzistor->actiune_click = fct_select_tranzistor;

    DreptunghiGrafic* bg_btn19 = new DreptunghiGrafic();

    bg_btn19->culoare = SDL_Color{ 80,80,80,80 };
    bg_btn19->dimensiuni = Vector2(50, 50);
    bg_btn19->pozitie = Vector2(1105, INALTIME - 60);
    bg_btn19->marime = 1;

    ImagineGrafica* bg_btn20 = new ImagineGrafica();

    bg_btn20->path = "Desenecomponente/tranzistor.bmp";
    bg_btn20->culoare = SDL_Color{ 150,150,150,255 };
    bg_btn20->dimensiuni = Vector2(50, 50);
    bg_btn20->pozitie = Vector2(1105, INALTIME - 60);
    bg_btn20->marime = 1;

    tranzistor->AdaugaElementGrafic(bg_btn19);
    tranzistor->AdaugaElementGrafic(bg_btn20);

    InregistrareButon(zoomInBtn);
    InregistrareButon(zoomOutBtn);
    InregistrareButon(rezistor);
    InregistrareButon(intrerupator);
    InregistrareButon(andGate);
    InregistrareButon(capacitor);
    InregistrareButon(dioda2linii);
    InregistrareButon(diodacerc);
    InregistrareButon(impamantare);
    InregistrareButon(sursavoltaj);
    InregistrareButon(tranzistor);
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