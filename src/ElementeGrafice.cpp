#include "ElementeGrafice.h"

Buton::Buton(Vector2 _pozitie, Vector2 _dimensiuni)
{
	pozitie = _pozitie;
	dimensiuni = _dimensiuni;
	marime = 1;
}
Buton::Buton(Vector2 _pozitie, Vector2 _dimensiuni, ClickFunct actiune)
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
	printf("Desenand element grafic gol ");
}

void DreptunghiGrafic::Desenare(SDL_Renderer* rend) {
	Vector2 marime_reala = dimensiuni * marime;
	SDL_Rect rect = SDL_Rect{ (int)(pozitie.x - marime_reala.x / 2),(int)(pozitie.y - marime_reala.y / 2), (int)marime_reala.x, (int)marime_reala.y };
	SDL_SetRenderDrawColor(rend, culoare.r,culoare.g,culoare.b,culoare.a);

	SDL_RenderFillRect(rend,&rect);
}

void ImagineGrafica::Desenare(SDL_Renderer* rend) {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();

	SDL_Surface* imagine_surface = SDL_LoadBMP(path);

	if (imagine_surface == nullptr) {
		printf("Loading image error");
		printf(SDL_GetError());
		printf("\n");
		return;
	}

	SDL_Texture* image_textura = SDL_CreateTextureFromSurface(rend, imagine_surface);
	textures.push_back(image_textura);

	SDL_FreeSurface(imagine_surface);
	if (image_textura == nullptr) {
		printf("SDL_CreateTextureFromSurface Error: ");
	}

	SDL_SetTextureColorMod(image_textura, culoare.r, culoare.g, culoare.b);

	Vector2 dimensiuni_reale = dimensiuni * marime;

	SDL_Rect dest_rect = SDL_Rect{ (int)(pozitie.x - dimensiuni_reale.x / 2),
								  (int)(pozitie.y - dimensiuni_reale.y / 2),
								  (int)dimensiuni_reale.x, (int)dimensiuni_reale.y };

	SDL_Point center = { dest_rect.w / 2, dest_rect.h / 2 };
	SDL_RenderCopyEx(rend, image_textura, nullptr, &dest_rect, rotatie, &center, SDL_FLIP_NONE);
}

void TextGrafic::Desenare(SDL_Renderer* rend) {
	if (text == "" || text == NULL) {
		
		printf("text null \n");
		return;
	}

	if (font == nullptr) {
		font = TTF_OpenFont("Fonts/ShareTech.ttf", 24);
		if (font == nullptr) {
			font = TTF_OpenFont("Fonts/arial.ttf", 24);
			if (font == nullptr) {
				printf("NULL font error\n");
				return;
			}
		}
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, culoare);
	if (textSurface == nullptr) {
		printf("eroare surface text: %s\n", TTF_GetError());
		return;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rend, textSurface);
	if (textTexture == nullptr) {
		printf("eroare textura text : %s \n", SDL_GetError());
		SDL_FreeSurface(textSurface);
		return;
	}

	Vector2 dimensiuni_reale = dimensiuni * marime;

	SDL_Rect textRect = {};
	float textRatio = static_cast<float>(textSurface->w) / static_cast<float>(textSurface->h);

	if (dimensiuni_reale.y < dimensiuni_reale.x) {
		textRect.h = dimensiuni_reale.y;
		textRect.w = static_cast<int>(textRatio * dimensiuni_reale.y);

		if (textRect.w > dimensiuni_reale.x) {
			textRect.w = dimensiuni_reale.x;
			textRect.h = static_cast<int>(dimensiuni_reale.x / textRatio);
		}
	}
	else {
		textRect.w = dimensiuni_reale.x;
		textRect.h = static_cast<int>(dimensiuni_reale.x / textRatio);

		if (textRect.h > dimensiuni_reale.y) {
			textRect.h = dimensiuni_reale.y;
			textRect.w = static_cast<int>(dimensiuni_reale.y * textRatio);
		}
	}

	SDL_FreeSurface(textSurface);
	SDL_Rect finalTextRect = { pozitie.x - textRect.w / 2, pozitie.y - textRect.h / 2, textRect.w, textRect.h };

	SDL_RenderCopy(rend, textTexture, nullptr, &finalTextRect);

	SDL_DestroyTexture(textTexture);
}



void Path::Desenare(SDL_Renderer* rend){

	Vector2 pozAnterior;
	bool prima = true;
	for (auto poz : pozitii) {
		if (prima) {
			prima = false;
		}
		else {
			DeseneazaLinie(rend, pozAnterior, poz, (int)(5*marime) > 1 ? (int)(5*marime):1, culoare);
		}
		pozAnterior = poz;
	}
}

void WindowGrafic::AdaugaElementGrafic(ElementGrafic* element) {
	elem_grafice.push_back(element);
}

void WindowGrafic::AdaugaButon(Buton* btn) {
	butoane.push_back(btn);
}

WindowGrafic::WindowGrafic() {
	
}