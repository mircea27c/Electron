#pragma once
#include <SDL.h> 
#include <SDL_ttf.h> 
#include <list>
#include <iostream>
#include <math.h>
#include "Vector2.h" 
#include "unelteDesenare.h"

#pragma region Elemente Grafice

typedef void(*ClickFunct)();

class WindowGrafic;

class ElementGrafic {
public:
	Vector2 pozitie;
	float marime;
	SDL_Color culoare = SDL_Color{ 255,255,255,255 };

	virtual void Desenare(SDL_Renderer* rend);
	inline virtual ElementGrafic* Clonare() {
		ElementGrafic* element = new ElementGrafic();
		element->culoare = culoare;

		return element;
	}
};

class DreptunghiGrafic : public ElementGrafic {
public:
	Vector2 dimensiuni;
	void Desenare(SDL_Renderer* rend) override;
	inline ElementGrafic* Clonare() override {
		DreptunghiGrafic* element = new DreptunghiGrafic(*this);
		element->dimensiuni = dimensiuni;

		return element;
	}
};

class ImagineGrafica : public ElementGrafic {
public:
	Vector2 dimensiuni;
	const char* path;

	virtual void Desenare(SDL_Renderer* rend)override;
	inline ElementGrafic* Clonare() override {
		ImagineGrafica* element = new ImagineGrafica(*this);
		element->dimensiuni = dimensiuni;
		element->path = path;


		return element;
	}
};

class TextGrafic : public ElementGrafic {
public:
	Vector2 dimensiuni;
	const char* text;

	virtual void Desenare(SDL_Renderer* rend)override;
	inline ElementGrafic* Clonare() override {
		TextGrafic* element = new TextGrafic(*this);
		dimensiuni = element->dimensiuni;
		text = element->text;

		return element;
	}
};

#pragma endregion

class Buton
{
public:
	Vector2 pozitie;

	float marime;

	Vector2 dimensiuni;

	Buton(Vector2 _pozitie, Vector2 _dimensiuni);
	Buton(Vector2 _pozitie, Vector2 _dimensiuni, ClickFunct actiune);

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

//clasa asta e un grup de elemente grafice la un loc
class WindowGrafic {
public:
	std::list<ElementGrafic*> elem_grafice;
	std::list<Buton*> butoane;

	WindowGrafic();

	void AdaugaElementGrafic(ElementGrafic* element);

	void AdaugaButon(Buton* btn);
};
