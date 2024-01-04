#pragma once
#include <list>
#include "grid.cpp"
#include "Vector2.h"
#include "ElementeGrafice.h"

enum ORIENTARE {
	DREAPTA = 0,
	JOS = 1,
	STANGA = 2,
	SUS = 3
};

class Conector;
class Componenta;
class PunctConexiune;

class PunctConexiune {
private:
public: 
	enum PCT_CONEX_TIP {
		INPUT, OUTPUT
	};

	PCT_CONEX_TIP tip;
	ORIENTARE orientare;

	Componenta* parinte;
	Conector* conector = NULL;

	//exprimat in procentaj din latimea si lungimea celulei respective(valori intre 0 si 1)
	Vector2 pozitie_relativa;
	Buton* buton;

	PunctConexiune(Vector2 _poz_rel, Componenta* _parinte, ORIENTARE _orientare, PCT_CONEX_TIP _tip);
	PunctConexiune(PunctConexiune* model);
	PunctConexiune(); 
	void Clonare(PunctConexiune* copie);
};


class Componenta {
	Vector2 pozitie_in_grid;

public:

	int id; //pentru debugging doar

	ORIENTARE rotatie;

	ElementGrafic* grafica;
	PunctConexiune* puncte_conexiune;
	int nr_pct_conexiune;

	Componenta();
	Componenta(Componenta* tip);
	~Componenta();

	void StergeLegaturi();

	void SetPozitie(Vector2 pozitie);
	Vector2 GetPozitie();

	virtual void Print();

};

class Conector : public Componenta {
public:

	PunctConexiune* start_conexiune;
	PunctConexiune* final_conexiune;

	std::list<Vector2> pozitii;
	// Other members and functions...
	Conector();
	~Conector();
};

