#pragma once

#include <iostream>

#include "Filtrovanie.h"
#include "UzemnaJednotka.h"

#include "structures/table/unsorted_sequence_table.h";


class Triedenie {


private:

	Filtrovanie* filter_;

	bool triedPodlaNazvu;
	bool triedVzdelaniePocet;
	bool triedVzdelaniePodiel;

	bool triedVzostupne;
	bool triedZostupne;

public:
	
	Triedenie() {
		filter_ = new Filtrovanie();

		triedPodlaNazvu = false;
		triedVzdelaniePocet = false;
		triedVzdelaniePodiel = false;

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
			}
			else {
				std::cout << "# " << x << " # KriteriumUJ Vzdelanie Podiel - NIE JE MOZNE AKTIVOVAT" << std::endl;
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

		system("cls");


		UnsortedSequenceTable<std::string, UzemnaJednotka*>* utriedenaTabulka = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
		for (TableItem<std::string, UzemnaJednotka*>* item : *vyfiltrovaneTabulky) {
			utriedenaTabulka->insert(item->getKey(), item->accessData());
		}

		std::cout << "Triedim Uzemne Jednotky...";

		TYP_VZDELANIA typVzd;

		if (!triedPodlaNazvu)
		{
			typVzd = pouzivatelVyberTypVzdelania();
		}
		else {
			// len nastavim lebo mi treba do metody na triedenie... neovyplivni to nic ked to tu bude
			typVzd = TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI;
		}
		

		sort(*utriedenaTabulka, triedVzostupne, triedPodlaNazvu, triedVzdelaniePocet, triedVzdelaniePodiel, typVzd);

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
			std::cout << std::endl;
		}
		system("pause");
		delete aktFiltre;
		delete utriedenaTabulka;
	}



	void sort(UnsortedSequenceTable<std::string, UzemnaJednotka*>& table, bool vzostupne, bool triedPodlaNazvu, bool triedPodlaVzdelaniePocet, bool triedPodlaVzdelaniePodiel, TYP_VZDELANIA typVzd)
	{
		sortHelper(table, 0, table.size() - 1, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
	}

	
	void sortHelper(UnsortedSequenceTable<std::string, UzemnaJednotka*>& table, int min, int max, bool vzostupne, bool triedPodlaNazvu, bool triedPodlaVzdelaniePocet, bool triedPodlaVzdelaniePodiel, TYP_VZDELANIA typVzd) {


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
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
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
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
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
				sortHelper(table, min, pravy, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
			}
			if (lavy < max)
			{
				sortHelper(table, lavy, max, vzostupne, triedPodlaNazvu, triedPodlaVzdelaniePocet, triedPodlaVzdelaniePodiel, typVzd);
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
};