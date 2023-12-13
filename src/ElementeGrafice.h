#pragma once
#include <SDL.h> 
#include <SDL_ttf.h> 
#include <list>
#include "Vector2.h" 
#include "unelteDesenare.h"

#pragma region Elemente Grafice

typedef void(*ClickFunct)();


class ElementGrafic {
public:
	Vector2 pozitie;
	const char* nume = "";
	float marime;
	SDL_Color culoare = SDL_Color{ 255,255,255,255 };

	virtual void Desenare(SDL_Renderer* rend);
};

class DreptunghiGrafic : public ElementGrafic {
public:
	Vector2 dimensiuni;
	SDL_Color culoare;

	void Desenare(SDL_Renderer* rend) override;
};

class ImagineGrafica : public ElementGrafic {
public:
	Vector2 dimensiuni;
	char* path;

	virtual void Desenare(SDL_Renderer* rend)override;
};

class TextGrafic : public ElementGrafic {
public:
	Vector2 dimensiuni;
	char* text;

	virtual void Desenare(SDL_Renderer* rend)override;
};

#pragma endregion

class Buton
{
public:
	Vector2 pozitie;

	float marime;

	Vector2 dimensiuni;

	Buton(const char* _text, SDL_Color _culoare, const char* _nume, Vector2 _pozitie, Vector2 _dimensiuni);
	Buton(const char* _text, SDL_Color _culoare, const char* _nume, Vector2 _pozitie, Vector2 _dimensiuni, ClickFunct actiune);

	ClickFunct actiune_click;

	std::list <ElementGrafic*>ListaElementeGrafice;

	void AdaugaElementGrafic(ElementGrafic* obiect)
	{
		if (obiect == NULL)printf("Elementul Grafic este NULL");
		else ListaElementeGrafice.push_back(obiect);

	}

	void ActionareClick();
};

class Path : public ElementGrafic {

public:
	std::list<Vector2> pozitii;

	void Desenare(SDL_Renderer* rend) override;

};
