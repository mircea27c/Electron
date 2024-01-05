#include "Tooltip.h"

void tooltip::Initializare()
{
    tooltip = new WindowGrafic();
    tooltip_bg = new DreptunghiGrafic();
    tooltip_text = new TextGrafic();

    tooltip_bg->dimensiuni = Vector2(inaltime, inaltime);

    tooltip_bg->culoare = SDL_Color{ 0,0,0,255 };
    tooltip_text->culoare = SDL_Color{ 230,230,230, 255 };

    tooltip->AdaugaElementGrafic(tooltip_bg);
    tooltip->AdaugaElementGrafic(tooltip_text);

    post_refresh_ui_listeners.push_back(ProceseazaUITooltip);
}

void tooltip::ProcesarePozitieMouse(Vector2 poz)
{
    Vector2 poz_inainte = tooltip_bg->pozitie;

    Buton* btn_hover = NULL;
    for (auto& btn : toate_butoanele) {

        if (ButonApasat(btn, poz)) {
            btn_hover = btn;
        }

    }
    if (btn_hover == NULL) {
        AscundeTooltip();
    }
    else {
        AfiseazaTooltip(btn_hover, poz);
    }
    
    if (!(tooltip_bg->pozitie == poz_inainte))RefreshUI();
}

void tooltip::AfiseazaTooltip(Buton* buton, Vector2 pozMouse)
{
    if (buton->tooltip == NULL || buton->tooltip == "")return;

    float latime = strlen(buton->tooltip) * char_latime;
    tooltip_bg->marime = 1;
    tooltip_bg->dimensiuni = Vector2(latime, (float)inaltime);
    tooltip_bg->pozitie = pozMouse + tooltip_bg->dimensiuni/2 + marime_cursor;

    tooltip_text->pozitie = tooltip_bg->pozitie;
    tooltip_text->dimensiuni = tooltip_bg->dimensiuni;
    tooltip_text->text = buton->tooltip;
    tooltip_text->marime = 1;

    tooltip_activ = true;
}

void tooltip::AscundeTooltip()
{
    tooltip_activ = false;
    tooltip_bg->pozitie = Vector2(-10,-10);

}

void tooltip::ProceseazaUITooltip()
{
    if (tooltip_activ) {
        DeseneazaWindowGrafic(tooltip);
    }
}