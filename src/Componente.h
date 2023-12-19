#pragma once
#include <list>
#include "grid.cpp"
#include "Vector2.h"
#include "ElementeGrafice.h"

enum ORIENTARE {
	STANGA,
	DREAPTA,
	SUS,
	JOS
};

class Componenta;
class PunctConexiune;
class Conector;

class PunctConexiune {
private:
public:
	ORIENTARE orientare;
	
	Componenta* parinte;
	Conector* output = NULL;

	//exprimat in procentaj din latimea si lungimea celulei respective(valori intre 0 si 1)
	Vector2 pozitie_relativa;
	Buton* buton;

	PunctConexiune(Vector2 _poz_rel, Componenta* _parinte, ORIENTARE _orientare);
	PunctConexiune(PunctConexiune* model);
};

class Componenta {
	Vector2 pozitie_in_grid;

public:

	const char* id; //pentru debugging doar

	ElementGrafic* grafica;
	std::list<PunctConexiune*> puncte_conexiune;
	
	inline Componenta() {
		id = "componenta fara nume";
		DreptunghiGrafic* dreptunghi = new DreptunghiGrafic();
		dreptunghi->culoare = SDL_Color{ 255,255,255,255 };
		dreptunghi->dimensiuni = Vector2(50, 50);
		grafica = dreptunghi;

		pozitie_in_grid = Vector2();
	}
	inline Componenta(Componenta* tip) {
		id = "clona fara nume";

		grafica = tip->grafica->Clonare();

		puncte_conexiune.clear();

		for (auto &pct_conex : tip->puncte_conexiune)
		{
			PunctConexiune* pct_nou = new PunctConexiune(pct_conex);
			pct_nou->parinte = this;
			puncte_conexiune.push_back(pct_nou);
		}

		pozitie_in_grid = Vector2();
	}
	
	void SetPozitie(Vector2 pozitie);
	Vector2 GetPozitie();

	virtual void Print();

};

class Conector : public Componenta {
public:
	PunctConexiune* start_conexiune;
	PunctConexiune* final_conexiune;

	std::list<Vector2> pozitii;


};