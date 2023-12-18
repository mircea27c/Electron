#include "ElementeGrafice.h"


Buton::Buton(const char* _text, SDL_Color _culoare, const char* _nume, Vector2 _pozitie, Vector2 _dimensiuni)
{
	pozitie = _pozitie;
	dimensiuni = _dimensiuni;
	marime = 1;
}
Buton::Buton(const char* _text, SDL_Color _culoare, const char* _nume, Vector2 _pozitie, Vector2 _dimensiuni, ClickFunct actiune)
{
	pozitie = _pozitie;
	dimensiuni = _dimensiuni;
	marime = 1;
	actiune_click = actiune;
}
void Buton::ActionareClick()
{
	actiune_click();
}

void ElementGrafic::Desenare(SDL_Renderer* rend) {
	
}

void DreptunghiGrafic::Desenare(SDL_Renderer* rend) {
	Vector2 marime_reala = dimensiuni * marime;
	SDL_Rect rect = SDL_Rect{ (int)(pozitie.x - marime_reala.x / 2),(int)(pozitie.y - marime_reala.y / 2), (int)marime_reala.x, (int)marime_reala.y };
	SDL_SetRenderDrawColor(rend, culoare.r,culoare.g,culoare.b,culoare.a);

	SDL_RenderFillRect(rend,&rect);
}

void ImagineGrafica::Desenare(SDL_Renderer* rend) {
	SDL_Surface* imagine_surface = SDL_LoadBMP(path);

	if (imagine_surface == nullptr) {
		printf("Loading image error");
		printf(SDL_GetError());
		printf("\n");
		return;
	}

	SDL_Texture* image_textura = SDL_CreateTextureFromSurface(rend, imagine_surface);
	SDL_FreeSurface(imagine_surface); // Free the surface, as it's no longer needed
	if (image_textura == nullptr) {
		printf("SDL_CreateTextureFromSurface Error: ");
		// Error handling code...
	}    

	SDL_Rect dest_rect = SDL_Rect{(int)(pozitie.x - dimensiuni.x/2), (int)(pozitie.y - dimensiuni.y/2), (int)dimensiuni.x,(int)dimensiuni.y};

	SDL_RenderCopy(rend, image_textura, NULL, &dest_rect);

}

void TextGrafic::Desenare(SDL_Renderer* rend) {
	if (text != NULL && text != "") {

		TTF_Font* font = TTF_OpenFont("Fonts/ShareTech.ttf", 24);
		if (font == NULL) {
			font = TTF_OpenFont("Fonts/aril.ttf", 24);
		}
		if (font == NULL) {
			printf("NULL font error");
		}

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, SDL_Color{ 255, 255, 255, 255 });
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend, textSurface);

		SDL_FreeSurface(textSurface);

		SDL_Rect textRect;

		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_RenderCopy(rend, textTexture, NULL, &textRect);
	}
}

void Path::Desenare(SDL_Renderer* rend){
	SDL_SetRenderDrawColor(rend, 230,230,230,255);


	Vector2 pozAnterior;

	bool prima = true;
	for (auto poz : pozitii) {
		if (prima) {
			prima = false;
		}
		else {
			SDL_RenderDrawLine(rend, pozAnterior.x, pozAnterior.y, poz.x, poz.y );
			//DeseneazaLinie(rend, pozAnterior, poz, 5);
		}
		pozAnterior = poz;
	}
}
