#include "SaveLoad.h"


void SaveCircuit(const char* nume) {
	string path_save = "Saves/";
	path_save += nume;
	path_save += ".txt";
	
	ofstream output;
	
	output.open(path_save);

	string date_componente = "";
	string date_conectori = "";

	for (auto &comp : toate_componentele) {
		if (Conector* conector = dynamic_cast<Conector*>(comp)) {
			//salveaza id
			date_conectori += to_string(conector->id) + "\n";

			//salveaza punct start
			date_conectori += "(";
			date_conectori += to_string((int)conector->start_conexiune->parinte->id);
			date_conectori += ",";
			for (int i = 0; i < conector->start_conexiune->parinte->nr_pct_conexiune; i++)
			{
				if (&conector->start_conexiune->parinte->puncte_conexiune[i] == conector->start_conexiune) {
					date_conectori += to_string(i);
					break;
				}
			}
			date_conectori += ")\n";

			//salveaza punct final
			date_conectori += "(";
			date_conectori += to_string((int)conector->final_conexiune->parinte->id);
			date_conectori += ",";
			for (int i = 0; i < conector->final_conexiune->parinte->nr_pct_conexiune; i++)
			{
				if (&conector->final_conexiune->parinte->puncte_conexiune[i] == conector->final_conexiune) {
					date_conectori += to_string(i);
					break;
				}
			}
			date_conectori += ")\n";

			if (conector->pozitii.empty()) {
				date_conectori += "-1";
			}
			for (auto &poz: conector->pozitii)
			{
				date_conectori += "(";
				date_conectori += to_string((int)poz.x);
				date_conectori += ",";
				date_conectori += to_string((int)poz.y);
				date_conectori += ") ";
			}

			date_conectori += "\n";
		}
		else {
			//salveaza tip
			date_componente += to_string(comp->id_tip) + "\n";
			//salveaza id
			date_componente += to_string(comp->id) + "\n";
			
			//salveaza pozitie
			date_componente += "(";
			date_componente += to_string((int)comp->GetPozitie().x);
			date_componente += ",";
			date_componente += to_string((int)comp->GetPozitie().y);
			date_componente += ")\n";

			//salveaza rotatie
			date_componente += to_string((int)comp->rotatie);
			date_componente += "\n";
			
			for (int i = 0; i < comp->nr_pct_conexiune; i++)
			{
				if (comp->puncte_conexiune[i].conector == NULL) {
					date_componente += "-1";
				}
				else {
					date_componente += to_string(comp->puncte_conexiune[i].conector->id);
				}
				if (i <= comp->nr_pct_conexiune - 1) {
					date_componente += " ";
				}
			}			

			date_componente += "\n";
		}
	}

	output << "<id>\n";
	output << GetIdActualComponente();
	output << "\n";

	output << "<componente>\n";
	output << date_componente;

	output << "<conectori>\n";
	output << date_conectori;

	output.close();

	cout << "Salvare circuit\n";

}

void LoadCircuit(const char* nume) {
	string path_load = "Saves/";
	path_load += nume;
	path_load += ".txt";

	ifstream input;

	input.open(path_load);

	bool eroare_citire = false;

	int categorie_date = 0; //1 - date componente, 2 - date conectori, 3 - date contor id

	string date_componente = "";
	string date_conectori = "";

	string linie_citita;

	string conexiuni_componente = "";
	string conexiuni_conectori = "";
	//obtine datele componentelor is a conectorilor separat

	int ultim_id = -1;

	while (!input.eof()) {
		getline(input, linie_citita);
		if (linie_citita == "<componente>") {
			categorie_date = 1;
			continue;
		}
		else if (linie_citita == "<conectori>") {
			categorie_date = 2;
			continue;
		}
		else if (linie_citita == "<id>") {
			categorie_date = 3;
			continue;
		}
		if (categorie_date == 1) {
			date_componente += linie_citita + "\n";
		}
		else if (categorie_date == 2) {
			date_conectori += linie_citita + "\n";
		}
		else if (categorie_date == 3) {
			ultim_id = stoi(linie_citita);
			categorie_date = 0;
		}
	}

	if (ultim_id == -1) {
		eroare_citire = true;
	}

	list<Componenta*> componente_citite;
	list<Componenta*> conectori_cititi;

	int camp_citit = 0;
	//- 0 id_tip
	//- 1 id
	//- 2 poz
	//- 3 rotatie
	//- 4 id-uri pct conexiune

	if (date_componente != "" && !eroare_citire) {
		istringstream stream_linie(date_componente);
		string linie_comp;

		Componenta* componenta_curenta = NULL;

		getline(stream_linie, linie_comp);

		while (!stream_linie.eof()) {
			
			istringstream stream_elemente(linie_comp);

			string pozitie;
			switch (camp_citit)
			{
			case 0:
				int tip_id;
				stream_elemente >> tip_id;
				if (tip_id < 0 || tip_id > tipuri_componente.size()) {
					eroare_citire = true;
					break;
				}
				componenta_curenta = new Componenta(tipuri_componente[tip_id]);

				break;
			case 1:
				int id;
				stream_elemente >> id;
				if (tip_id < 0) {
					eroare_citire = true;
					break;
					id = 0;
				}
				componenta_curenta->id = id;
				break;
			case 2:
				stream_elemente >> pozitie;
				componenta_curenta->SetPozitie(ParseazaPozitie(pozitie));
				break;
			case 3:
				int rotatie;
				stream_elemente >> rotatie;
				componenta_curenta->rotatie = (ORIENTARE)rotatie;
				if (rotatie > 3) {
					eroare_citire = true;
					break;
				}
				break;
			case 4:
				//nimic momentan
				conexiuni_componente += linie_comp + '\n';

				//reseteaza campul pentru urmatoarea componenta. adauga componenta curenta in lista
				camp_citit = -1;
				componente_citite.push_back(componenta_curenta);
				componenta_curenta = NULL;
				break;
			default:
				break;
			}

			camp_citit++;
			getline(stream_linie, linie_comp);
		}
	}

	camp_citit = 0;
	//0 - id
	//1 - start conexiune
	//2 - final conexiune
	//3 - pozitii
	if (date_conectori != "" && !eroare_citire) {
		istringstream stream_linie(date_conectori);
		string linie_con;

		Conector* conector_curent = new Conector();

		getline(stream_linie, linie_con);

		while (!stream_linie.eof()) {

			istringstream stream_elemente(linie_con);

			string pozitie;
			switch (camp_citit)
			{
			case 0:
				int id;
				stream_elemente >> id;
				if (id < 0) {
					//eroare
					eroare_citire = true;
					break;
				}
				conector_curent->id = id;
				break;
			case 1:
				conexiuni_conectori += linie_con + '\n';
				break;
			case 2:
				conexiuni_conectori += linie_con + '\n';
				break;
			case 3:
				if (linie_con.length() < 2) {
					eroare_citire = true;
					break;
				}
				if (linie_con[0] == '-' && linie_con[1] == '1') {
					//conectorul nu are pozitii desenate	
				}
				else {
					while (!stream_elemente.eof()) {
						stream_elemente >> pozitie;

						Vector2 poz_parsata = ParseazaPozitie(pozitie);
						if (poz_parsata.x == -1) {
							eroare_citire = true;
							break;
						}
						conector_curent->pozitii.push_back(poz_parsata);
					}
				}

				//trecem la urmatorul conector citit
				camp_citit = -1;
				conectori_cititi.push_back(conector_curent);

				conector_curent = new Conector();
				break;
			default:
				break;
			}

			camp_citit++;
			getline(stream_linie, linie_con);
		}
	}

	if (conexiuni_componente != "" && !eroare_citire) {
		istringstream stream_linie(conexiuni_componente);
		istringstream stream_elemente;
		string linie;
		for (auto &comp:componente_citite)
		{
			getline(stream_linie, linie);
			stream_elemente = istringstream(linie);
			for (int i = 0; i < comp->nr_pct_conexiune; i++)
			{
				int id_conector;
				stream_elemente >> id_conector;
				if (id_conector == -1) {
					comp->puncte_conexiune[i].conector = NULL;
				}
				else {
					if (id_conector > ultim_id) {
						eroare_citire = true;
						break;
					}
					comp->puncte_conexiune[i].conector = (Conector*)GasesteComponentaDupaID(&conectori_cititi, id_conector);
				}
			}
		}
	}
	if (conexiuni_conectori != "" && !eroare_citire) {
		istringstream stream_linie(conexiuni_conectori);
		string linie;
		for (auto& con : conectori_cititi)
		{
			stream_linie>>linie;
			Vector2 date_pct_start = ParseazaPozitie(linie);
			Componenta* parinte_pct = GasesteComponentaDupaID(&componente_citite,(int)date_pct_start.x);
			if (parinte_pct == NULL) {
				eroare_citire;
				break;
			}
			if (date_pct_start.y >= parinte_pct->nr_pct_conexiune) {
				eroare_citire;
				break;
			}
			((Conector*)con)->start_conexiune = &parinte_pct->puncte_conexiune[(int)date_pct_start.y];
			
			stream_linie>>linie;
			Vector2 date_pct_final = ParseazaPozitie(linie);
			parinte_pct = GasesteComponentaDupaID(&componente_citite, (int)date_pct_final.x);
			if (parinte_pct == NULL) {
				eroare_citire;
				break;
			}
			if (date_pct_final.y >= parinte_pct->nr_pct_conexiune) {
				eroare_citire;
				break;
			}
			((Conector*)con)->final_conexiune = &parinte_pct->puncte_conexiune[(int)date_pct_final.y];
		}
	}

	if (!eroare_citire) {
		while (!toate_componentele.empty()) {
			editor_componente::StergeComponenta(toate_componentele.front());
		}
		for (auto& comp : componente_citite)
		{
			toate_componentele.push_back(comp);
		}
		for (auto& comp : conectori_cititi)
		{
			toate_componentele.push_back(comp);
		}

		SetIdActualComponente(ultim_id);

		printf("Incarcare circuit\n");
		RefreshUI();
	}
	else {
		printf("Eroare Load: Fisierul nu este un save file valid sau formatarea a fost corupta.");
	}
}

Vector2 ParseazaPozitie(string text) {
	int start_poz = text.find('(');
	int virgula_poz = text.find(',');
	int final_poz = text.find(')');

	if (start_poz != string::npos && virgula_poz != string::npos && final_poz != string::npos) {
		return Vector2(stoi(text.substr(start_poz + 1, virgula_poz - start_poz - 1)), stoi(text.substr(virgula_poz + 1, final_poz - virgula_poz - 1)));
	}
	return Vector2(-1,-1);
}

Componenta* GasesteComponentaDupaID(list<Componenta*>* lista,int id) {
	for (auto& comp : *lista)
	{
		if (comp->id == id) {
			return comp;
		}
	}
	return NULL;
}


void SaveCircuitFileBrowser() {
	
}

void LoadCircuitFileBrowser() {
	
}