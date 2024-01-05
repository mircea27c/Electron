#pragma once
#include "UIManager.h"

namespace tooltip {

    static WindowGrafic* tooltip;
    static DreptunghiGrafic* tooltip_bg;
    static TextGrafic* tooltip_text;
    static int inaltime = 24;
    static int char_latime = 8;
    static Vector2 marime_cursor = Vector2(15,10);

    static bool tooltip_activ;

    void Initializare();

    void ProcesarePozitieMouse(Vector2 poz);

    void AfiseazaTooltip(Buton* buton, Vector2 pozMouse);
    void AscundeTooltip();

    void ProceseazaUITooltip();


}


