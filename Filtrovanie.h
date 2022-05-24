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
				zapniFiltrovanie(slovensko);
				break;
			case 1:

				break;

			case 2:

				break;
			case 3:

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



	bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
};