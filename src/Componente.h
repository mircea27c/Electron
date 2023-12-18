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

class PunctConexiune {
private:
public:
	ORIENTARE orientare;
	
	Componenta* parinte;

	//exprimat in procentaj din latimea si lungimea celulei respective(valori intre 0 si 1)
	Vector2 pozitie_relativa;
	Buton* buton;

	PunctConexiune(Vector2 _poz_rel, Componenta* _parinte, ORIENTARE _orientare);
};

class Componenta {
	Vector2 pozitie_in_grid;

public:

	ElementGrafic* grafica;
	std::list<PunctConexiune*> puncte_conexiune;
	
	Componenta();
	inline Componenta(Componenta* tip) {
		grafica = tip->grafica->Clonare();

		puncte_conexiune.clear();
		std::copy(tip->puncte_conexiune.begin(), tip->puncte_conexiune.end(), std::back_inserter(puncte_conexiune));

		pozitie_in_grid = Vector2();
	}
	
	void SetPozitie(Vector2 pozitie);
	Vector2 GetPozitie();

	virtual void Print();

};

class Conector : public Componenta {
public:
	PunctConexiune* start_conexiune;

	std::list<Vector2> pozitii;


};