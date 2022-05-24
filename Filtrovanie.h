#pragma once

#include "iostream"

#include "Filter.h"
#include "FilterWithCriterion.h"
#include "FilterInterval.h"
#include "FilterValue.h"
#include "CompositeFilter.h"
#include "FilterAnd.h"

#include "FUJPrislusnost.h"
#include "FUJTyp.h"
#include "FUJVzdelaniePocet.h"
#include "FUJVzdelaniePodiel.h"

class Filtrovanie {

private:

	bool fujPrislusnostAktivovany = false;
	bool fujTypAktivovany = false;
	bool fujVzdelaniePocetAktivovany = false;
	bool fujVzdelaniePodielAktivovany = false;

public:

	Filtrovanie() {};
	~Filtrovanie() {};


	void zapniFiltrovanie(UzemnaJednotka* slovensko) {
		int pocetAplikovanychFiltrov = 0;

		SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<std::string, UzemnaJednotka*>*>* tabulkaUJ = new SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<std::string, UzemnaJednotka*>*>();


		system("cls");
		std::cout << "### FILTROVANIE ###" << std::endl;
		std::cout << "# POPIS:" << std::endl;
		std::cout << "# Vo filtrovani si mozes vyfiltrovat uzemne jednotky podla vlastnych filtrov." << std::endl;
		std::cout << "# " << std::endl;
		std::cout << "# Postupne pis cisla filtrov, ktore chces uplatnit, pokial si s vyberom spokojny, potvrd vybrate filtre a pokracuj dalej." << std::endl;
		std::cout << "# 999 # Ukoncit filtrovanie" << std::endl << std::endl;
		std::cout << "# 0 # POTVRDIT VYBER FILTROV" << std::endl << std::endl;

		if (fujTypAktivovany)
		{
			std::cout << "# 1 # ZAPNUTY # Filter UJ TYP" << std::endl;
		}
		else {
			std::cout << "# 1 # VYPNUTY # Filter UJ TYP" << std::endl;
		}
		if (fujPrislusnostAktivovany)
		{
			std::cout << "# 2 # ZAPNUTY # Filter UJ Prislusnost" << std::endl;
		}
		else {
			std::cout << "# 2 # VYPNUTY # Filter Uj Prislusnost" << std::endl;
		}
		if (fujVzdelaniePocetAktivovany)
		{
			std::cout << "# 3 # ZAPNUTY # Filter UJ Vzdelanie Pocet" << std::endl;
		}
		else {
			std::cout << "# 3 # VYPNUTY # Filter UJ Vzdelanie Pocet" << std::endl;
		}
		if (fujVzdelaniePodielAktivovany)
		{
			std::cout << "# 4 # ZAPNUTY # Filter UJ Vzdelanie Podiel" << std::endl;
		}
		else {
			std::cout << "# 4 # VYPNUTY # Filter UJ Vzdelanie Podiel" << std::endl;
		}
		std::cout << std::endl << "VSTUP -> ";

		std::string vstup = "";

		std::cin >> vstup;
		system("cls");

		if (!isNumber(vstup))
		{
			system("cls");
			std::cout << "# ERROR # " << std::endl;
			std::cout << "# Musis Napisat CISLO " << std::endl;
			std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
			system("pause");
			zapniFiltrovanie(slovensko);
		}
		else {
			int vstupInt = std::stoi(vstup);

			switch (vstupInt)
			{
			case 999:
				break;
			case 0:
				system("cls");
				std::cout << "Filtre potvrdene..." << std::endl;
				Sleep(1000);
				vlozParametreFiltrov(slovensko);
				system("pause");
				break;
			case 1:
				if (fujTypAktivovany){fujTypAktivovany = false;} 
				else { fujTypAktivovany = true;}
				fujTypAktivovany = true;
				zapniFiltrovanie(slovensko);
				break;

			case 2:
				if (fujPrislusnostAktivovany) { fujPrislusnostAktivovany = false; }
				else { fujPrislusnostAktivovany = true; }
				zapniFiltrovanie(slovensko);
				break;
			case 3:
				if (fujVzdelaniePocetAktivovany) { fujVzdelaniePocetAktivovany = false; }
				else { fujVzdelaniePocetAktivovany = true; }
				zapniFiltrovanie(slovensko);
				break;
			case 4:
				if (fujVzdelaniePodielAktivovany) { fujVzdelaniePodielAktivovany = false; }
				else { fujVzdelaniePodielAktivovany = true; }
				zapniFiltrovanie(slovensko);
				break;

			default:
				system("cls");
				std::cout << "# ERROR # " << std::endl;
				std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
				std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
				system("pause");
				zapniFiltrovanie(slovensko);
				break;
			}
		}

		
	}


	void vlozParametreFiltrov(UzemnaJednotka* slovensko) {

		UZEMNA_JEDNOTKA fujTYP;
		UzemnaJednotka* povinnaPrislusnostUJ;


		if (fujTypAktivovany)
		{
			std::string vstup = "x";

			while (!isNumber(vstup)) {

				bool breaknut = false;
				

				system("cls");
				std::cout << "# Zvol parameter filtra FUJTYP" << std::endl;
				std::cout << "#" << std::endl;
				std::cout << "# 1 # " << "Kraj" << std::endl;
				std::cout << "# 2 # " << "Okres" << std::endl;
				std::cout << "# 3 # " << "Obec" << std::endl;


				std::cout << std::endl << "VSTUP -> ";

				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO " << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
					zapniFiltrovanie(slovensko);
				}
				else {
					int vstupInt = std::stoi(vstup);
					switch (vstupInt)
					{
					case 1:
						std::cout << "zvoleny kraj" << std::endl;
						fujTYP = UZEMNA_JEDNOTKA::KRAJ;
						breaknut = true;
						system("pause");
						break;
					case 2:
						std::cout << "zvoleny okres" << std::endl;
						fujTYP = UZEMNA_JEDNOTKA::OKRES;
						system("pause");
						break;
					case 3:
						std::cout << "zvolena obec" << std::endl;
						fujTYP = UZEMNA_JEDNOTKA::OBEC;
						breaknut = true;
						system("pause");
						break;

					default:
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
						std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
						system("pause");
						break;
					}
				}
				if (breaknut)
				{
					break;
				}
			}
		}
		if (fujPrislusnostAktivovany)
		{
			std::string vstup = "x";
			
			int zvolenyKraj = false;
			int zvolenyOkres = false;

			bool breaknut = false;

			while (!isNumber(vstup)) {

				system("cls");
				std::cout << "# Zvol parameter filtra FUJPrislusnost -  1. TYP UzemnejJednotky, ktora je paramterom prislusnosti" << std::endl;
				std::cout << "#" << std::endl;
				std::cout << "# 1 # " << "Kraj" << std::endl;
				std::cout << "# 2 # " << "Okres" << std::endl;


				std::cout << std::endl << "VSTUP -> ";

				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO " << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
					zapniFiltrovanie(slovensko);
				}
				else {
					int vstupInt = std::stoi(vstup);
					switch (vstupInt)
					{
					case 1:
						zvolenyKraj = true;
						breaknut = true;
						system("pause");
						break;
					case 2:
						zvolenyOkres = true;
						breaknut = true;
						system("pause");
						break;
					default:
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
						std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
						system("pause");
						break;
					}

				}

				if (breaknut)
				{
					break;
				}
			}

			vstup = "x";


			breaknut = false;

			while (!isNumber(vstup)) {

				system("cls");
				std::cout << "# Zvol parameter filtra FUJPrislusnost - 2. Názov UzemnejJednotky, ktora je paramterom prislusnosti" << std::endl;
				std::cout << "#" << std::endl;

				ArrayList<UzemnaJednotka*>* listVyberUJ = new ArrayList<UzemnaJednotka*>();
				listVyberUJ->add(nullptr);
				
				if (zvolenyKraj) {

					int i = 1;
					for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko->getUzemneJednotkyChildren())
					{
						std::cout << "# " << i << "  # " << kraj->accessData()->getNazov() << std::endl;
						listVyberUJ->add(kraj->accessData());
						i++;
					}
				}
				else if (zvolenyOkres) {
					int i = 1;
					for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko->getUzemneJednotkyChildren())
					{	
						for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
						{
							std::cout << "# " << i << "  # " << okres->accessData()->getNazov() << std::endl;
							listVyberUJ->add(okres->accessData());
							i++;
						}
						
					}
				}


				std::cout << std::endl << "VSTUP -> ";

				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO " << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
				}
				else {
					int vstupInt = std::stoi(vstup);
					if (vstupInt >= 1 && vstupInt < listVyberUJ->size())
					{
						breaknut = true;
						povinnaPrislusnostUJ = listVyberUJ->at(vstupInt);
					}else {
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
						std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
						system("pause");
					}

				}

				if (breaknut)
				{
					break;
				}
			}


		}
		if (fujVzdelaniePocetAktivovany)
		{

		}
		if (fujVzdelaniePodielAktivovany)
		{

		}
	}

	bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}

	
};