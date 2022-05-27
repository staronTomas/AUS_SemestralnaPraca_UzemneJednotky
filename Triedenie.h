#pragma once

#include <iostream>

#include "Filtrovanie.h"
#include "UzemnaJednotka.h"

#include "structures/table/unsorted_sequence_table.h";

#include "enum_EVS.h"


class Triedenie {


private:

	Filtrovanie* filter_;

	bool triedPodlaNazvu;
	bool triedVzdelaniePocet;
	bool triedVzdelaniePodiel;

	bool triedVekSkupinaPocet;
	bool triedVekSkupinaPodiel;

	bool triedVzostupne;
	bool triedZostupne;

public:
	
	Triedenie() {
		filter_ = new Filtrovanie();

		triedPodlaNazvu = false;
		triedVzdelaniePocet = false;
		triedVzdelaniePodiel = false;

		triedVekSkupinaPocet = false;
		triedVekSkupinaPodiel = false;

		triedVzostupne = false;
		triedZostupne = false;

	};

	~Triedenie() {
		delete filter_;


	};


	void spustiTriedenie(UzemnaJednotka* slovensko) {

		triedPodlaNazvu = false;
		triedVzdelaniePocet = false;
		triedVzdelaniePodiel = false;

		triedVekSkupinaPocet = false;
		triedVekSkupinaPodiel = false;

		triedVzostupne = false;

		// Kluc tu je KodUJ, vsade inde je klucom nazovUJ
		SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneTabulky = filter_->zapniFiltrovanieSTriedenim(slovensko);

		Array<bool>* aktFiltre = filter_->vratZoznamAktivovanychFiltrov();
		std::string vstup = "";

		while (true)
		{

			system("cls");
			std::cout << "### TRIEDENIE ###" << std::endl;
			std::cout << "# POPIS:" << std::endl;
			std::cout << "# Vyber si podla ktorého kriteria chces utriedit Uzemne Jednotky" << std::endl;
			std::cout << "# " << std::endl;
			std::cout << "# 1 # KriteriumUJ Nazov" << std::endl;
			int x = 2;
			if (aktFiltre->at(2))
			{
				std::cout << "# " << x << " # KriteriumUJ Vzdelanie Pocet" << std::endl;
				x++;
			}
			else {
				std::cout << "# " << x << " # KriteriumUJ Vzdelanie Pocet - NIE JE MOZNE AKTIVOVAT" << std::endl;
				x++;
			}
			if (aktFiltre->at(3))
			{
				std::cout << "# " << x << " # KriteriumUJ Vzdelanie Podiel" << std::endl;
				x++;
			}
			else {
				std::cout << "# " << x << " # KriteriumUJ Vzdelanie Podiel - NIE JE MOZNE AKTIVOVAT" << std::endl;
				x++;
			}
			if (aktFiltre->at(4))
			{
				std::cout << "# " << x << " # KriteriumUJ Vekova Skupina Pocet" << std::endl;
				x++;
			}
			else {
				std::cout << "# " << x << " # KriteriumUJ Vekova Skupina Pocet - NIE JE MOZNE AKTIVOVAT" << std::endl;
				x++;
			}
			if (aktFiltre->at(5))
			{
				std::cout << "# " << x << " # KriteriumUJ Vekova Skupina Podiel" << std::endl;
				x++;
			}
			else {
				std::cout << "# " << x << " # KriteriumUJ Vekova Skupina - NIE JE MOZNE AKTIVOVAT" << std::endl;
				x++;
			}
			std::cout << "VSTUP -> ";
			vstup = "";
			std::cin >> vstup;

			bool spravnyVyber = false;

			if (!isNumber(vstup))
			{
				nieJeCisloMessage();
			}
			else {
				int vstupInt = stoi(vstup);

				switch (vstupInt)
				{
				case 1:
					spravnyVyber = true;
					triedPodlaNazvu = true;
					break;
				case 2:
					if (aktFiltre->at(2)) {
						spravnyVyber = true;
						triedVzdelaniePocet = true;
					}
					break;
				case 3:
					if (aktFiltre->at(3)) {
						spravnyVyber = true;
						triedVzdelaniePodiel = true;
					}
					break;
				case 4:
					if (aktFiltre->at(4)) {
						spravnyVyber = true;
						triedVekSkupinaPocet = true;
					}
					break;
				case 5:
					if (aktFiltre->at(5)) {
						spravnyVyber = true;
						triedVekSkupinaPodiel = true;
					}
					break;
				default:
					break;
				}

				if (spravnyVyber)
				{
					break;
				}
				else {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO ktore je v ponuke" << std::endl;
					system("pause");
				}
			}
		}

		system("cls");


		UnsortedSequenceTable<std::string, UzemnaJednotka*>* utriedenaTabulka = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
		for (TableItem<std::string, UzemnaJednotka*>* item : *vyfiltrovaneTabulky) {
			utriedenaTabulka->insert(item->getKey(), item->accessData());
		}

		std::cout << "Triedim Uzemne Jednotky...";

		TYP_VZDELANIA typVzd;
		EVS typEvs;

		if (triedVzdelaniePocet || triedVzdelaniePodiel)
		{
			typVzd = pouzivatelVyberTypVzdelania();
		}
		else {
			// len nastavim lebo mi treba do metody na triedenie... neovyplivni to nic ked to tu bude
			typVzd = TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI;
		}

		if (triedVekSkupinaPocet || triedVekSkupinaPodiel) {
			typEvs = pouzivatelVyberTypEVS();
		}
		else {
			// len nastavim lebo mi treba do metody na triedenie... neovyplivni to nic ked to tu bude
			typEvs = EVS::PREDPRODUKTIVNI;
		}



		system("cls");
		std::cout << "### TRIEDENIE ###" << std::endl;
		std::cout << "# Triedit Vzostupne alebo Zostupne?" << std::endl;
		std::cout << "# " << std::endl;
		std::cout << "# 1 # Vzostupne - od najmensej hodnoty po najvacsiu" << std::endl;
		std::cout << "# 2 # Zostupne - od najvacsej hodnoty po najmensiu" << std::endl;
		std::cout << "VSTUP -> ";
		vstup = "";
		std::cin >> vstup;

		if (!isNumber(vstup))
		{
			nieJeCisloMessage();
		}
		else {
			int vstupInt = stoi(vstup);

			if (vstupInt == 1) {
				triedVzostupne = true;
			}
			else if (vstupInt == 2) {
				triedVzostupne = false;
			}
			else {
				system("cls");
				std::cout << "# ERROR # " << std::endl;
				std::cout << "# Musis Napisat CISLO ktore je v ponuke" << std::endl;
				system("pause");
			}
		}
		

		sort(*utriedenaTabulka, triedVzostupne, triedPodlaNazvu, triedVzdelaniePocet, triedVzdelaniePodiel, triedVekSkupinaPocet, triedVekSkupinaPodiel, typVzd, typEvs);

		system("cls");
		std::cout << "### Vypis utriedenych uzemnych jednotiek ###" << std::endl;

		for (TableItem<std::string, UzemnaJednotka*>* item : *utriedenaTabulka)
		{
			std::cout << "# Nazov - " << item->accessData()->getNazov() << std::endl;
			if (triedVzdelaniePocet)
			{
				std::cout << "# Vzdelanie pocet " << vratTextTypuVzdelania(typVzd) << item->accessData()->getVzdelanie()->getPocetVzdelanie(typVzd) << std::endl;
			}
			if (triedVzdelaniePodiel)
			{
				std::cout << "# Vzdelanie podiel " << vratTextTypuVzdelania(typVzd) << item->accessData()->getPodielVzdelanie(typVzd) << " %" << std::endl;
			}
			if (triedVekSkupinaPocet)
			{
				std::cout << "# Vekova Skupina pocet " << vratTextTypuEvs(typEvs) << item->accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) << std::endl; // chyba tu jeee rozmyslaj este
			}
			if (triedVekSkupinaPodiel)
			{
				std::cout << "# Vekova Skupina podiel " << vratTextTypuEvs(typEvs) << item->accessData()->getVekObyvatelov()->getPodielEvs(typEvs) << " %" << std::endl;
			}
			std::cout << std::endl;
		}
		system("pause");
		delete aktFiltre;
		delete utriedenaTabulka;
	}



	void sort(UnsortedSequenceTable<std::string, UzemnaJednotka*>& table, bool vzostupne, bool triedPodlaNazvu, bool triedPodlaVzdelaniePocet, bool triedPodlaVzdelaniePodiel, bool triedPodlaVekSkupinaPocet, bool triedPodlaVekSkupinaPodiel, TYP_VZDELANIA typVzd, EVS typEvs)
	{
		sortHelper(table, 0, table.size() - 1, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
	}

	
	void sortHelper(UnsortedSequenceTable<std::string, UzemnaJednotka*>& table, int min, int max, bool vzostupne, bool triedPodlaNazvu, bool triedPodlaVzdelaniePocet, bool triedPodlaVzdelaniePodiel, bool triedPodlaVekSkupinaPocet, bool triedPodlaVekSkupinaPodiel, TYP_VZDELANIA typVzd, EVS typEvs) {


		if (triedPodlaNazvu)
		{
			std::string hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getNazov();

			int lavy = min;
			int pravy = max;

			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getNazov() < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getNazov() > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getNazov() > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getNazov() < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}


		if (triedPodlaVzdelaniePocet)
		{
			int hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getVzdelanie()->getPocetVzdelanie(typVzd);

			int lavy = min;
			int pravy = max;


			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getVzdelanie()->getPocetVzdelanie(typVzd) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVzdelanie()->getPocetVzdelanie(typVzd) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getVzdelanie()->getPocetVzdelanie(typVzd) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVzdelanie()->getPocetVzdelanie(typVzd) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}



		if (triedPodlaVzdelaniePodiel)
		{
			double hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getPodielVzdelanie(typVzd);

			double lavy = min;
			double pravy = max;

			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getPodielVzdelanie(typVzd) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getPodielVzdelanie(typVzd) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getPodielVzdelanie(typVzd) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getPodielVzdelanie(typVzd) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}


		if (triedPodlaVekSkupinaPocet)
		{
			int hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs);

			int lavy = min;
			int pravy = max;


			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}



		if (triedPodlaVekSkupinaPodiel)
		{
			int hlavnyKluc = table.getItemAtIndex((min + max) / 2).accessData()->getVekObyvatelov()->getPodielEvs(typEvs);

			int lavy = min;
			int pravy = max;


			do
			{
				if (vzostupne)
				{
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) < hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) > hlavnyKluc)
					{
						pravy--;
					}
				}
				else { // zostupne
					while (table.getItemAtIndex(lavy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) > hlavnyKluc)
					{
						lavy++;
					}
					while (table.getItemAtIndex(pravy).accessData()->getVekObyvatelov()->getPodielEvs(typEvs) < hlavnyKluc)
					{
						pravy--;
					}
				}

				if (lavy <= pravy)
				{
					table.swap(lavy, pravy);
					lavy++;
					pravy--;
				}
			} while (lavy <= pravy);

			if (min < pravy)
			{
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, triedPodlaVekSkupinaPocet, triedPodlaVekSkupinaPodiel, typVzd, typEvs);
			}
		}
	}


	bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}


	void nieJeCisloMessage() {
		system("cls");
		std::cout << "# ERROR # " << std::endl;
		std::cout << "# Musis Napisat CISLO " << std::endl;
		std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
		system("pause");
	}



	TYP_VZDELANIA pouzivatelVyberTypVzdelania() {

		bool breaknut = false;

		while (true) {

			system("cls");
			std::cout << "# Zvol Typ Vzdelania podla ktoreho chces utriedit tabulku" << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# 1 # Bez Vzdelanie DETI " << std::endl;
			std::cout << "# 2 # Zakladne Vzdelanie " << std::endl;
			std::cout << "# 3 # Ucnovske Vzdelanie " << std::endl;
			std::cout << "# 4 # Stredoskolske Vzdelanie  " << std::endl;
			std::cout << "# 5 # Vyssie Vzdelanie  " << std::endl;
			std::cout << "# 6 # Vysokoskolske Vzdelanie  " << std::endl;
			std::cout << "# 7 # Bez Vzdelanie " << std::endl;
			std::cout << "# 8 # Nezistene Vzdelanie" << std::endl;
			std::cout << std::endl << "VSTUP -> ";

			std::string vstup = "";

			std::cin >> vstup;
			system("cls");

			if (!isNumber(vstup))
			{
				nieJeCisloMessage();
			}
			else {
				int vstupInt = std::stoi(vstup);
				switch (vstupInt)
				{
				case 1:
					return TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI;
					breaknut = true;
					break;
				case 2:
					return TYP_VZDELANIA::ZAKLADNE;
					breaknut = true;
					break;
				case 3:
					return TYP_VZDELANIA::UCNOVSKE;
					breaknut = true;
					break;
				case 4:
					return TYP_VZDELANIA::STREDNE;
					breaknut = true;
					break;
				case 5:
					return TYP_VZDELANIA::VYSSIE;
					breaknut = true;
					break;
				case 6:
					return TYP_VZDELANIA::VYSOKOSKOLSKE;
					breaknut = true;
					break;
				case 7:
					return TYP_VZDELANIA::BEZ_VZDELANIA;
					breaknut = true;
					break;
				case 8:
					return TYP_VZDELANIA::NEZISTENE;
					breaknut = true;
					break;
				default:

					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
					system("cls");
					break;
				}

			}

			if (breaknut)
			{
				break;
			}
		}
	}




	EVS pouzivatelVyberTypEVS() {

		bool breaknut = false;

		while (true) {

			system("cls");
			std::cout << "# Zvol Typ Vekovej Skupiny podla ktoreho chces utriedit tabulku" << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# 1 # PredProduktivni " << std::endl;
			std::cout << "# 2 # Produktivni " << std::endl;
			std::cout << "# 3 # PoProduktivni " << std::endl;
			std::cout << std::endl << "VSTUP -> ";

			std::string vstup = "";

			std::cin >> vstup;
			system("cls");

			if (!isNumber(vstup))
			{
				nieJeCisloMessage();
			}
			else {
				int vstupInt = std::stoi(vstup);
				switch (vstupInt)
				{
				case 1:
					return EVS::PREDPRODUKTIVNI;
					breaknut = true;
					break;
				case 2:
					return EVS::PRODUKTIVNI;
					breaknut = true;
					break;
				case 3:
					return EVS::POPRODUKTIVNY;
					breaknut = true;
					break;
				default:

					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
					system("cls");
					break;
				}

			}

			if (breaknut)
			{
				break;
			}
		}
	}



	std::string vratTextTypuVzdelania(TYP_VZDELANIA typVzd) {
		switch (typVzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			return "Bez ukonceneho vzdelania DETI : ";
			break;
		case TYP_VZDELANIA::ZAKLADNE:
			return "Zakladne vzdelanie : ";
			break;
		case TYP_VZDELANIA::UCNOVSKE:
			return "Ucnovske vzdelania : ";
			break;
		case TYP_VZDELANIA::STREDNE:
			return "Stredne vzdelania : ";
			break;
		case TYP_VZDELANIA::VYSSIE:
			return "Vyssie vzdelania : ";
			break;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			return "Vysokoskolske vzdelanie : ";
			break;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			return "Bez vzdelania : ";
			break;
		case TYP_VZDELANIA::NEZISTENE:
			return "Nezistene vzdelanie : ";
			break;

		default:
			break;
		}
	}


	std::string vratTextTypuEvs(EVS typEvs) {
		switch (typEvs) {

		case EVS::PREDPRODUKTIVNI:
			return "PredProduktivni : ";
			break;
		case EVS::PRODUKTIVNI:
			return "Produktivni : ";
			break;
		case EVS::POPRODUKTIVNY:
			return "PoProduktivni : ";
			break;

		default:
			break;
		}
	}
};