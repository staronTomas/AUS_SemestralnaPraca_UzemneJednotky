#pragma once

#include "iostream"

#include "Filter.h"
#include "FilterWithCriterion.h"
#include "FilterInterval.h"
#include "FilterValue.h"
#include "CompositeFilter.h"
#include "FilterAnd.h"
#include "structures/heap_monitor.h"

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
				break;
			case 1:
				if (fujTypAktivovany){fujTypAktivovany = false;} 
				else { fujTypAktivovany = true;}
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
		
		FUJTyp<UzemnaJednotka*, UZEMNA_JEDNOTKA>* fujTyp;
		FUJPrislusnost<UzemnaJednotka*, UzemnaJednotka*>* fujPrislusnost;
		FUJVzdelaniePocet<UzemnaJednotka*, int>* fujVzdelaniePocet;
		FUJVzdelaniePodiel<UzemnaJednotka*, double>* fujVzdelaniePodiel;


		if (fujTypAktivovany)
		{
			std::string vstup = "x";

			while (!isNumber(vstup)) {

				bool breaknut = false;
				

				system("cls");
				std::cout << "#####  FUJTYP  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJTYP" << std::endl;
				std::cout << "# Vysvetlenie filtra: Vyfiltruju sa uzemne jednotky, ktore nebudu zvoleneho typu" << std::endl;
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
					nieJeCisloMessage();
					zapniFiltrovanie(slovensko);
				}
				else {
					int vstupInt = std::stoi(vstup);
					switch (vstupInt)
					{
					case 1:
						fujTYP = UZEMNA_JEDNOTKA::KRAJ;
						breaknut = true;
						break;
					case 2:
						fujTYP = UZEMNA_JEDNOTKA::OKRES;
						breaknut = true;
						break;
					case 3:
						fujTYP = UZEMNA_JEDNOTKA::OBEC;
						breaknut = true;
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
			fujTyp = new FUJTyp<UzemnaJednotka*, UZEMNA_JEDNOTKA>(UZEMNA_JEDNOTKA::OBEC);
		}


		if (fujPrislusnostAktivovany)
		{
			std::string vstup = "x";
			
			int zvolenyKraj = false;
			int zvolenyOkres = false;

			bool breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJPrislusnost  #####" << std::endl;
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
					nieJeCisloMessage();
				}
				else {
					int vstupInt = std::stoi(vstup);
					switch (vstupInt)
					{
					case 1:
						zvolenyKraj = true;
						breaknut = true;
						break;
					case 2:
						zvolenyOkres = true;
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

			vstup = "x";


			breaknut = false;

			while (!isNumber(vstup)) {

				system("cls");
				std::cout << "#####  FUJPrislusnost  #####" << std::endl;
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
					nieJeCisloMessage();
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
						system("cls");
					}

				}

				if (breaknut)
				{
					delete listVyberUJ;
					break;
				}
			}
			fujPrislusnost = new FUJPrislusnost<UzemnaJednotka*, UzemnaJednotka*>(povinnaPrislusnostUJ);
		}
		if (fujVzdelaniePocetAktivovany)
		{
			std::string vstup = "x";

			int zadanyMin = 0;
			int zadanyMax = 0;

			TYP_VZDELANIA zvolenyTypVzdelania;

			bool breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePocet  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePocet - 1. Zvol typ Vzdelania " << std::endl;
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
						zvolenyTypVzdelania = TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI;
						breaknut = true;
						break;
					case 2:
						zvolenyTypVzdelania = TYP_VZDELANIA::ZAKLADNE;
						breaknut = true;
						break;
					case 3:
						zvolenyTypVzdelania = TYP_VZDELANIA::UCNOVSKE;
						breaknut = true;
						break;
					case 4:
						zvolenyTypVzdelania = TYP_VZDELANIA::STREDNE;
						breaknut = true;
						break;
					case 5:
						zvolenyTypVzdelania = TYP_VZDELANIA::VYSSIE;
						breaknut = true;
						break;
					case 6:
						zvolenyTypVzdelania = TYP_VZDELANIA::VYSOKOSKOLSKE;
						breaknut = true;
						break;
					case 7:
						zvolenyTypVzdelania = TYP_VZDELANIA::BEZ_VZDELANIA;
						breaknut = true;
						break;
					case 8:
						zvolenyTypVzdelania = TYP_VZDELANIA::NEZISTENE;
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


			//Zadanie minima a maxima


			breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePocet  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePocet - 2. Zvol MINIMUM poctu zvoleneho Vzdelania " << std::endl;
				std::cout << "#" << std::endl;
				std::cout << std::endl << "VSTUP minimum -> ";
				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					nieJeCisloMessage();
				}
				else {
					zadanyMin = stoi(vstup);
					breaknut = true;
				}
				if (breaknut)
				{
					break;
				}
			}



			breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePocet  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePocet - 3. Zvol MAXIMUM poctu zvoleneho Vzdelania " << std::endl;
				std::cout << "#" << std::endl;
				std::cout << std::endl << "VSTUP maximum -> ";
				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					nieJeCisloMessage();
				}
				else {

					if (zadanyMin <= stoi(vstup))
					{
						zadanyMax = stoi(vstup);
						breaknut = true;
					}
					else {
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Maximum musi byt vacsi alebo rovny minimumu " << std::endl;
						std::cout << "# Minimum -> " << zadanyMin << std::endl;
						std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
						system("pause");
					}

					
				}
				if (breaknut)
				{
					break;
				}
			}

			fujVzdelaniePocet = new FUJVzdelaniePocet<UzemnaJednotka*, int>(zvolenyTypVzdelania, zadanyMin, zadanyMax);
		}
		if (fujVzdelaniePodielAktivovany)
		{
			std::string vstup = "x";

			int zadanyMin = 0;
			int zadanyMax = 0;

			TYP_VZDELANIA zvolenyTypVzdelania;

			bool breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePodiel  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePodiel - 1. Zvol typ Vzdelania " << std::endl;
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
						zvolenyTypVzdelania = TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI;
						breaknut = true;
						break;
					case 2:
						zvolenyTypVzdelania = TYP_VZDELANIA::ZAKLADNE;
						breaknut = true;
						break;
					case 3:
						zvolenyTypVzdelania = TYP_VZDELANIA::UCNOVSKE;
						breaknut = true;
						break;
					case 4:
						zvolenyTypVzdelania = TYP_VZDELANIA::STREDNE;
						breaknut = true;
						break;
					case 5:
						zvolenyTypVzdelania = TYP_VZDELANIA::VYSSIE;
						breaknut = true;
						break;
					case 6:
						zvolenyTypVzdelania = TYP_VZDELANIA::VYSOKOSKOLSKE;
						breaknut = true;
						break;
					case 7:
						zvolenyTypVzdelania = TYP_VZDELANIA::BEZ_VZDELANIA;
						breaknut = true;
						break;
					case 8:
						zvolenyTypVzdelania = TYP_VZDELANIA::NEZISTENE;
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


			//Zadanie minima a maxima


			breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePodiel  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePodiel - 2. Zvol MINIMUM poctu zvoleneho Vzdelania v PERCENTACH 0-100 " << std::endl;
				std::cout << "#" << std::endl;
				std::cout << std::endl << "VSTUP minimum -> ";
				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					nieJeCisloMessage();
				}
				else if (stoi(vstup) < 0 || stoi(vstup) > 100) {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Cislo musi byt v intervale <0, 100> " << std::endl;
					std::cout << "# Minimum -> " << zadanyMin << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
				}
				else {
					zadanyMin = stoi(vstup);
					breaknut = true;
				}
				if (breaknut)
				{
					break;
				}
			}



			breaknut = false;

			while (true) {

				system("cls");
				std::cout << "#####  FUJVzdelaniePodiel  #####" << std::endl;
				std::cout << "# Zvol parameter filtra FUJVzdelaniePodiel - 3. Zvol MAXIMUM poctu zvoleneho Vzdelania v PERCENTACH 0-100 " << std::endl;
				std::cout << "#" << std::endl;
				std::cout << std::endl << "VSTUP maximum -> ";
				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (!isNumber(vstup))
				{
					nieJeCisloMessage();
				}
				else if (stoi(vstup) < 0 || stoi(vstup) > 100) {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Cislo musi byt v intervale <0, 100> " << std::endl;
					std::cout << "# Minimum -> " << zadanyMin << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
				}
				else {

					if (zadanyMin < stoi(vstup))
					{
						zadanyMax = stoi(vstup);
						breaknut = true;
					}
					else {
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Maximum musi byt vacsi než minimum " << std::endl;
						std::cout << "# Minimum -> " << zadanyMin << std::endl;
						std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
						system("pause");
					}


				}
				if (breaknut)
				{
					break;
				}
			}
			fujVzdelaniePodiel = new FUJVzdelaniePodiel<UzemnaJednotka*, double>(zvolenyTypVzdelania, zadanyMin, zadanyMax);
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
	
};