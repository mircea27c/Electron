#include "Aplicatie.h"

class EcranPrincipal;

bool Aplicatie::InitializareAplicatie() {
    int initResult = SDL_Init(SDL_INIT_VIDEO);
    if (initResult < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    InitializareTipuriComponente();

    simulator = new SimulatorCircuit();

    return true;
}

void Aplicatie::InchidereAplicatie() {

    InchidereUIManager();
    SDL_Quit();
}

 Buton* Aplicatie::CreareButon(Vector2 pozitie, Vector2 dimensiune,SDL_Color culoare_buton, SDL_Color culoare_componenta, const char* path_imagine,int index_btn, const char* nume) {
    Buton* buton = new Buton(pozitie, dimensiune);
    
    buton->tooltip = nume;

    int latura_img = min(dimensiune.x, dimensiune.y);
    
    ImagineGrafica* imagine = new ImagineGrafica();
    imagine->path = path_imagine;
    imagine->culoare = culoare_componenta;
    imagine->dimensiuni = Vector2(latura_img, latura_img);
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

    ecran_principal = new EcranPrincipal();
    ecran_principal->Initializare([this]() {SchimbaEcranActiv(EDITOR); }, [this]() {running = false;});

    tooltip::Initializare();

    SDL_Color culoare_btn = {60,60,60};
    SDL_Color culoare_comp = {150,150,150 };
    SDL_Color culoare_bg = SDL_Color{ 30,30,30 };

#pragma region header_navigare

    int h_nav_nr_el = 3;

    int pad_h_nav = 8;

    int centru_x = 60;

    int spatiu_btn_miscare = 75;
    int marime_btn_miscare = 25;
    WindowGrafic* header_navigare = new WindowGrafic();

    DreptunghiGrafic* bg_h_nav = new DreptunghiGrafic();
    bg_h_nav->dimensiuni = Vector2(centru_x + spatiu_btn_miscare / 2 + marime_btn_miscare, 45);
    bg_h_nav->marime = 1;
    bg_h_nav->pozitie = Vector2(bg_h_nav->dimensiuni.x / 2, bg_h_nav->dimensiuni.y / 2);
    bg_h_nav->culoare = culoare_bg;

    int centru_y = bg_h_nav->dimensiuni.y + 60;
    header_navigare->AdaugaElementGrafic(bg_h_nav);


    int latime_btn_nav = (bg_h_nav->dimensiuni.x - pad_h_nav * (h_nav_nr_el + 1)) /h_nav_nr_el;
    int inaltime_btn_nav = (bg_h_nav->dimensiuni.y - pad_h_nav * 2);

    Buton* zoomInBtn = CreeazaButonCuText(Vector2(pad_h_nav + latime_btn_nav/2.0f, bg_h_nav->pozitie.y), Vector2(latime_btn_nav, inaltime_btn_nav),1.5f,culoare_btn, culoare_comp, "+");
    zoomInBtn->tooltip = "zoom in";
    zoomInBtn->actiune_click = ZoomIn;

    Buton* zoomOutBtn = CreeazaButonCuText(Vector2(pad_h_nav * 2 + latime_btn_nav * 1.5f, bg_h_nav->pozitie.y), Vector2(latime_btn_nav, inaltime_btn_nav), 1.5f, culoare_btn, culoare_comp, "-");
    zoomOutBtn->actiune_click = ZoomOut;
    zoomOutBtn->tooltip = "zoom out";

    ImagineGrafica* icon_zoom = new ImagineGrafica();
    icon_zoom->pozitie = Vector2(pad_h_nav * 3 + latime_btn_nav * 2.5f, bg_h_nav->pozitie.y);
    icon_zoom->marime = 1;
    icon_zoom->dimensiuni = Vector2(latime_btn_nav, inaltime_btn_nav) * 0.8f;
    icon_zoom->culoare = culoare_comp;
    icon_zoom->path = "Iconite/zoom.bmp";
    

    Vector2 dim_btn_miscare = Vector2(marime_btn_miscare, marime_btn_miscare);

    DreptunghiGrafic* bg_miscare = new DreptunghiGrafic();
    bg_miscare->dimensiuni = Vector2(centru_x + spatiu_btn_miscare/2 + marime_btn_miscare + 1, centru_x + spatiu_btn_miscare / 2 + marime_btn_miscare);
    bg_miscare->marime = 1;
    bg_miscare->pozitie = Vector2(centru_x, centru_y);
    bg_miscare->culoare = SDL_Color{30,30,30};

    header_navigare->AdaugaElementGrafic(bg_miscare);

    Buton* moveUpBtn = CreeazaButonCuImagine(Vector2(centru_x, centru_y - spatiu_btn_miscare / 2), dim_btn_miscare, .8f, culoare_btn, culoare_comp, "Iconite/run.bmp");
    moveUpBtn->ListaElementeGrafice.back()->rotatie = 270;
    moveUpBtn->actiune_click = []() {pozitie_grid.y += factor_zoom * 100; RefreshUI(); };


    Buton* moveDownBtn = CreeazaButonCuImagine(Vector2(centru_x, centru_y + spatiu_btn_miscare / 2), dim_btn_miscare, .8f, culoare_btn, culoare_comp, "Iconite/run.bmp");
    moveDownBtn->ListaElementeGrafice.back()->rotatie = 90;
    moveDownBtn->actiune_click = []() {pozitie_grid.y -= factor_zoom * 100; RefreshUI(); };

    Buton* moveLeftBtn = CreeazaButonCuImagine(Vector2(centru_x - spatiu_btn_miscare/2, centru_y), dim_btn_miscare, .8f, culoare_btn, culoare_comp, "Iconite/run.bmp");
    moveLeftBtn->ListaElementeGrafice.back()->rotatie = 180;
    moveLeftBtn->actiune_click = []() {pozitie_grid.x += factor_zoom * 100; RefreshUI(); };

    Buton* moveRightBtn = CreeazaButonCuImagine(Vector2(centru_x + spatiu_btn_miscare / 2, centru_y), dim_btn_miscare, .8f, culoare_btn, culoare_comp, "Iconite/run.bmp");
    moveRightBtn->actiune_click = []() {pozitie_grid.x -= factor_zoom * 100; RefreshUI(); };
      
    Buton* centerBtn = CreeazaButonCuImagine(Vector2(centru_x , centru_y), dim_btn_miscare, 1.1f, culoare_btn, culoare_comp, "Iconite/center.bmp");
    centerBtn->actiune_click = []() {pozitie_grid = Vector2(0, 0); RefreshUI(); };


    moveUpBtn->tooltip = "move up";
    moveDownBtn->tooltip = "move down";
    moveLeftBtn->tooltip = "move left";
    moveRightBtn->tooltip = "move right";
    centerBtn->tooltip = "center screen";

    header_navigare->AdaugaButon(moveUpBtn);
    header_navigare->AdaugaButon(moveDownBtn);
    header_navigare->AdaugaButon(moveLeftBtn);
    header_navigare->AdaugaButon(moveRightBtn);
    header_navigare->AdaugaButon(centerBtn);

    header_navigare->AdaugaElementGrafic(icon_zoom);
    header_navigare->AdaugaButon(zoomInBtn);
    header_navigare->AdaugaButon(zoomOutBtn);


#pragma endregion

#pragma region footer_butoane
    WindowGrafic* footer_butoane = new WindowGrafic();

    int nr_componente = NrTipuriComponente();
    int padding_btn_comp = 20;
    int inaltime_buton = 50;
    int latime_buton = (LATIME - padding_btn_comp * (nr_componente + 1) )/ nr_componente;


    DreptunghiGrafic* bg_footer = new DreptunghiGrafic();
    bg_footer->dimensiuni = Vector2((float)LATIME, inaltime_buton + padding_btn_comp*2.0f);
    bg_footer->marime = 1;
    bg_footer->pozitie = Vector2(LATIME / 2.0f, INALTIME - bg_footer->dimensiuni.y / 2);
    bg_footer->culoare = culoare_bg;

    footer_butoane->AdaugaElementGrafic(bg_footer);


    Buton* sursavoltaj = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/sursavoltaj.bmp", 0, "voltage source");
    Buton* rezistor = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/rezistor.bmp", 1, "rezistor");
    Buton* intrerupator = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/bec.bmp", 2, "light bulb");
    Buton* andGate = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/andgate.bmp", 3,"and gate");
    Buton* capacitor = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/capacitor.bmp",4 ,"capacitor");
    Buton* dioda2linii = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/dioda2linii.bmp", 5, "varicap diode");
    Buton* diodacerc = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/diodacerc.bmp", 6, "diode");
    Buton* impamantare = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/impamantare.bmp",7, "ground");
    Buton* tranzistor = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/tranzistor.bmp", 8,  "tranzistor");
    Buton* splitter = CreareButon(Vector2(0, 0), Vector2(latime_buton, inaltime_buton), culoare_btn, culoare_comp, "Desenecomponente/2splitter.bmp", 9, "2 way splitter");
    
    footer_butoane->AdaugaButon(rezistor);
    footer_butoane->AdaugaButon(intrerupator);
    footer_butoane->AdaugaButon(andGate);
    footer_butoane->AdaugaButon(capacitor);
    footer_butoane->AdaugaButon(dioda2linii);
    footer_butoane->AdaugaButon(diodacerc);
    footer_butoane->AdaugaButon(impamantare);
    footer_butoane->AdaugaButon(sursavoltaj);
    footer_butoane->AdaugaButon(tranzistor);
    footer_butoane->AdaugaButon(splitter);
    
    int index = 0;

    //aici se calculeaza automat pozitia butoanelor

    for (auto &btn: footer_butoane->butoane)
    {
        btn->pozitie = Vector2(padding_btn_comp * (index + 1) + latime_buton * index + latime_buton / 2, INALTIME - inaltime_buton / 2 - padding_btn_comp);
        for (auto& el :btn->ListaElementeGrafice)
        {
            el->pozitie = btn->pozitie;
        }
        index++;
    }

#pragma endregion

#pragma region header_simulare

    WindowGrafic* header_simulare = new WindowGrafic();

    DreptunghiGrafic* bg = new DreptunghiGrafic();
    
    int padding = 15;
    bg->dimensiuni = Vector2((65.0f - padding * 2) * 3.0f + padding*4,65.0f);
    bg->marime = 1;
    bg->pozitie = Vector2(LATIME/2.0f,bg->dimensiuni.y/2.0f);
    bg->culoare = culoare_bg;

    int latime_btn_head = (bg->dimensiuni.x - 4 * padding)/3;
    int inaltime_btn_head = bg->dimensiuni.y - 2*padding;

    cout << latime_btn_head << " " << inaltime_btn_head << endl;

    Buton* btn_run = CreeazaButonCuImagine(Vector2(LATIME / 2.0f - latime_btn_head - padding, bg->pozitie.y), Vector2(latime_btn_head, inaltime_btn_head), 0.7f, culoare_btn, SDL_Color{150,200,150}, "Iconite/run.bmp"); 

    auto fct_simulare = [this]() {simulator->Simuleaza(); RefreshUI(); };
    btn_run->actiune_click = fct_simulare;


    Buton* btn_pause = CreeazaButonCuImagine(Vector2(LATIME / 2.0f, bg->pozitie.y), Vector2(latime_btn_head, inaltime_btn_head), 0.7f, culoare_btn, SDL_Color{ 150,150,150 }, "Iconite/pause.bmp");
    
    auto fct_pauza = [this]() {simulator->Pauza(); RefreshUI(); };
    btn_pause->actiune_click = fct_pauza;
    
    Buton* btn_stop = CreeazaButonCuImagine(Vector2(LATIME / 2.0f + latime_btn_head + padding, bg->pozitie.y), Vector2(latime_btn_head, inaltime_btn_head), 0.7f, culoare_btn, SDL_Color{ 200,150,150 }, "Iconite/stop.bmp");

    auto fct_stop = [this]() {simulator->Stop(); RefreshUI(); };
    btn_stop->actiune_click = fct_stop;

    btn_run->tooltip = "start simulation";
    btn_pause->tooltip = "pause simulation";
    btn_stop->tooltip = "reset simulation";

    header_simulare->AdaugaElementGrafic(bg);
    header_simulare->AdaugaButon(btn_run);
    header_simulare->AdaugaButon(btn_pause);
    header_simulare->AdaugaButon(btn_stop);

#pragma endregion

#pragma region sidebar_optiuni

    WindowGrafic* sidebar_optiuni = new WindowGrafic();

    DreptunghiGrafic* bg_optiuni = new DreptunghiGrafic();

    int pad_optiuni = 15;
    int nr_btn_optiuni = 3;

    int latura_btn_optiuni = 45;

    bg_optiuni->dimensiuni = Vector2(pad_optiuni * 2.0f + latura_btn_optiuni, pad_optiuni * (nr_btn_optiuni + 1.0f) + latura_btn_optiuni * nr_btn_optiuni);
    bg_optiuni->pozitie = Vector2(LATIME - bg_optiuni->dimensiuni.x/2, bg_optiuni->dimensiuni.y / 2);
    bg_optiuni->marime = 1;
    bg_optiuni->culoare = culoare_bg;

    sidebar_optiuni->AdaugaElementGrafic(bg_optiuni);

    Buton* btn_delete_all = CreeazaButonCuImagine(Vector2(bg_optiuni->pozitie.x, latura_btn_optiuni / 2.0f + padding), Vector2(latura_btn_optiuni, latura_btn_optiuni), 0.9f, SDL_Color{ 100,50,50 } , culoare_comp, "Iconite/delete_tot.bmp");
    Buton* btn_ss = CreeazaButonCuImagine(Vector2(bg_optiuni->pozitie.x, latura_btn_optiuni *1.5f + padding * 2), Vector2(latura_btn_optiuni, latura_btn_optiuni), 0.9f, culoare_btn, culoare_comp , "Iconite/camera.bmp");
    Buton* btn_meniu = CreeazaButonCuImagine(Vector2(bg_optiuni->pozitie.x, latura_btn_optiuni *2.5f + padding * 3), Vector2(latura_btn_optiuni, latura_btn_optiuni), 0.9f, culoare_btn, culoare_comp , "Iconite/meniu.bmp");

    auto fct_screenshot = []() {

        float factor_scalare = (float)Grid::GRID_CELULE_LATIME * (float)Grid::MARIME_CELULA/ (float)INALTIME;

        float factor_zoom_inainte = factor_zoom;
        Vector2 offset_inainte = pozitie_grid;

        factor_zoom = 1/factor_scalare;
        pozitie_grid = Vector2(0,0);
        AscundeGUI();

        RefreshUI();

        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);

        std::string path_save = "Screenshots/Circuit_";

        std::string timp = std::ctime(&currentTime_t);
        timp.pop_back();
        for (char& c : timp) {
            if (c == ' ' || c == ':') {
                c = '_';
            }
        }
        path_save += timp;

        path_save += ".bmp";

        printf("%s", path_save.c_str());
        CapturaScreenshot(path_save.c_str(), window, renderer, (float)Grid::GRID_CELULE_LATIME* (float)Grid::MARIME_CELULA* factor_zoom, INALTIME);

        AfiseazaGUI();
        factor_zoom = factor_zoom_inainte;
        pozitie_grid = offset_inainte;

        RefreshUI();
    };
    btn_ss->actiune_click = fct_screenshot;

    auto fct_delete = []() {
        while (!toate_componentele.empty()) {
            editor_componente::StergeComponenta(toate_componentele.front());
        }
    };

    auto fct_meniu = [this]() {
        SchimbaEcranActiv(START);
    };

    btn_delete_all->actiune_click = fct_delete;

    btn_meniu->actiune_click = fct_meniu;

    btn_delete_all->tooltip = "reset board";
    btn_ss->tooltip = "export board as image";
    btn_meniu->tooltip = "main menu";

    sidebar_optiuni->AdaugaButon(btn_delete_all);
    sidebar_optiuni->AdaugaButon(btn_ss);
    sidebar_optiuni->AdaugaButon(btn_meniu);

#pragma endregion

    InregistreazaWindowGrafic(header_navigare);
    InregistreazaWindowGrafic(header_simulare);
    InregistreazaWindowGrafic(sidebar_optiuni);

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
        else {
            tooltip::ProcesarePozitieMouse(Vector2(x,y));
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
    running = true;
    SDL_Event actiune_input;

    ecran_activ = Aplicatie::EDITOR;
    SchimbaEcranActiv(Aplicatie::START);

    while (running) {

        if (ecran_activ == Aplicatie::START) {
            RuleazaEcranPrincipal(actiune_input);
        }
        else if (ecran_activ == Aplicatie::EDITOR) {
            RuleazaEditor(actiune_input);
        }

        SDL_Delay(5);
    }
    InchidereAplicatie();

    return;

}

void Aplicatie::RuleazaEditor(SDL_Event& actiune_input) {
    if (refreshUI_urm_frame) {
        RefreshUI();
        refreshUI_urm_frame = false;
    }
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
    simulator->ParcurgePas(5);
}

void Aplicatie::RuleazaEcranPrincipal(SDL_Event& actiune_input) {
    if (refreshUI_urm_frame) {
        ecran_principal->RefreshUI();
        refreshUI_urm_frame = false;
    }
    while (SDL_PollEvent(&actiune_input) != 0) {
        if (actiune_input.type == SDL_QUIT) {
            running = false;
        }
        else {

            ecran_principal->ProceseazaMouse(&actiune_input);
        }
    }

}

void Aplicatie::SchimbaEcranActiv(Aplicatie::ECRAN ecran_nou) {
    if (ecran_activ != ecran_nou) {
        ecran_activ = ecran_nou;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        refreshUI_urm_frame = true;
        
    }
}