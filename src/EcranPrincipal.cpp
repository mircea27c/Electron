#include "EcranPrincipal.h"

void EcranPrincipal::Initializare(ClickFunct actiune_schimba_ecran, ClickFunct actiune_inchidere)
{
	window_ecran = new WindowGrafic();
	ImagineGrafica* bg = new ImagineGrafica();
	bg->pozitie = Vector2(LATIME / 2, INALTIME / 2);
	bg->dimensiuni = Vector2(LATIME + 1, INALTIME + 1);
	bg->path = "EcranPrincipal/bg.bmp";
	bg->marime = 1;


	Buton* btnStart = new Buton(Vector2(0.7f * LATIME, 0.5f * INALTIME), Vector2(0.21f * LATIME, 0.16f * INALTIME));
	ImagineGrafica* start_img = new ImagineGrafica();
	start_img->pozitie = btnStart->pozitie;
	start_img->dimensiuni = btnStart->dimensiuni;
	start_img->path = "EcranPrincipal/btn_start.bmp";
	start_img->marime = 1;
	start_img->culoare = culoare_normala;
	btnStart->AdaugaElementGrafic(start_img);

	btnStart->actiune_click = actiune_schimba_ecran;

	window_ecran->AdaugaButon(btnStart);

	Vector2 dim_quit = btnStart->dimensiuni * 0.6f;

	Buton* btnQuit = new Buton(Vector2(btnStart->pozitie.x + btnStart->dimensiuni.x/2 - btnStart->dimensiuni.x * 0.6f/2 , btnStart->pozitie.y + btnStart->dimensiuni.y/2 + INALTIME * 0.02f + dim_quit.y/2), dim_quit);
	ImagineGrafica* quit_img = new ImagineGrafica();
	quit_img->pozitie = btnQuit->pozitie;
	quit_img->dimensiuni = btnQuit->dimensiuni;
	quit_img->path = "EcranPrincipal/btn_quit.bmp";
	quit_img->marime = 1;
	quit_img->culoare = culoare_normala;
	btnQuit->AdaugaElementGrafic(quit_img);
	btnQuit->actiune_click = actiune_inchidere;

	window_ecran->AdaugaButon(btnQuit);

	window_ecran->AdaugaElementGrafic(bg);
}


void EcranPrincipal::RefreshUI() {

	SDL_RenderClear(renderer);

	DeseneazaWindowGrafic(window_ecran);

	for (auto &btn:window_ecran->butoane)
	{
		DeseneazaButon(btn);
	}

	SDL_RenderPresent(renderer);
}

void EcranPrincipal::ProceseazaMouse(SDL_Event* event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    switch (event->type) {
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button == SDL_BUTTON_LEFT) {
			for (auto& btn : window_ecran->butoane)
			{
				if (ButonApasat(btn, Vector2(x, y))) {
					btn->ActionareClick();
				}
			}
        }
        if (event->button.button == SDL_BUTTON_RIGHT) {
        }
        if (event->button.button == SDL_BUTTON_MIDDLE) {
        }

        break;
    case SDL_MOUSEBUTTONUP:
        if (event->button.button == SDL_BUTTON_LEFT) {
        }
        if (event->button.button == SDL_BUTTON_RIGHT) {
        }
        if (event->button.button == SDL_BUTTON_MIDDLE) {
        }
        break;
    case SDL_MOUSEMOTION:


		for (auto& btn : window_ecran->butoane)
		{
			SDL_Color cul_inainte = btn->ListaElementeGrafice.front()->culoare;
			if (ButonApasat(btn, Vector2(x, y))) {
				btn->ListaElementeGrafice.front()->culoare = culoare_highlight;
			}
			else {
				btn->ListaElementeGrafice.front()->culoare = culoare_normala;
			}
			if (!CuloriEgale(btn->ListaElementeGrafice.front()->culoare, cul_inainte)) {
				this->RefreshUI();
			}
		}

        break;
    case SDL_MOUSEWHEEL:
        break;
    }

}
