#pragma once

#include "iostream"

#include "Filter.h"
#include "FilterWithCriterion.h"
#include "FilterInterval.h"
#include "FilterValue.h"
#include "CompositeFilter.h"
#include "FilterAnd.h"
#include "structures/heap_monitor.h"

#include "structures/array/array.h"
#include "structures/table/unsorted_sequence_table.h"

#include "FUJPrislusnost.h"
#include "FUJTyp.h"
#include "FUJVzdelaniePocet.h"
#include "FUJVzdelaniePodiel.h"

#include "CriterionUJTyp.h"
#include "CriterionUJPrislusnost.h"
#include "CriterionUJVekPocet.h"
#include "CriterionUJVekPodiel.h"

class Filtrovanie {

private:

	bool fujPrislusnostAktivovany = false;
	bool fujTypAktivovany = false;
	bool fujVzdelaniePocetAktivovany = false;
	bool fujVzdelaniePodielAktivovany = false;

	bool ajTriedenie_ = false;



	FUJTyp<UzemnaJednotka*, UZEMNA_JEDNOTKA>* fujTyp;
	FUJPrislusnost<UzemnaJednotka*, UzemnaJednotka*>* fujPrislusnost;
	FUJVzdelaniePocet<UzemnaJednotka*, int>* fujVzdelaniePocet;
	FUJVzdelaniePodiel<UzemnaJednotka*, double>* fujVzdelaniePodiel;

	CriterionUJPrislusnost* kritPrislusnost = nullptr;
	CriterionUJVzdelaniePocet* kritVzdelaniePocet = nullptr;
	CriterionUJVzdelaniePodiel* kritVzdelaniePodiel = nullptr;
	

	//pre triedenie tabulka na return
	structures::LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>* vyfiltrovanaTabulkaNaTriedenie = nullptr;



public:

	Filtrovanie() {
		fujTyp = nullptr;
		fujPrislusnost = nullptr;
		fujVzdelaniePocet = nullptr;
		fujVzdelaniePodiel = nullptr;


		vyfiltrovanaTabulkaNaTriedenie = nullptr;
	};

	~Filtrovanie() {
		delete fujTyp;
		delete fujPrislusnost;
		delete fujVzdelaniePocet;
		delete fujVzdelaniePodiel;


		delete kritPrislusnost;
		delete kritVzdelaniePocet;
		delete kritVzdelaniePodiel;


		if (vyfiltrovanaTabulkaNaTriedenie != nullptr)
		{
			for (int i = 0; i < vyfiltrovanaTabulkaNaTriedenie->size(); i++)
			{
				delete vyfiltrovanaTabulkaNaTriedenie->at(i);
			}
			delete vyfiltrovanaTabulkaNaTriedenie;
		}
		
		
	};


	structures::LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>* zapniFiltrovanieSTriedenim(UzemnaJednotka* slovensko) {

		ajTriedenie_ = true;

		if (vyfiltrovanaTabulkaNaTriedenie != nullptr)
		{
			for (int i = 0; i < vyfiltrovanaTabulkaNaTriedenie->size(); i++) {
				delete vyfiltrovanaTabulkaNaTriedenie->at(i);
			}

			delete vyfiltrovanaTabulkaNaTriedenie;
		}
		

		fujPrislusnostAktivovany = false;
		fujTypAktivovany = false;
		fujVzdelaniePocetAktivovany = false;
		fujVzdelaniePodielAktivovany = false;

		kritPrislusnost = nullptr;
		CriterionUJVzdelaniePocet* kritVzdelaniePocet = nullptr;
		CriterionUJVzdelaniePodiel* kritVzdelaniePodiel = nullptr;

		delete fujTyp;
		delete fujPrislusnost;
		delete fujVzdelaniePocet;
		delete fujVzdelaniePodiel;

		fujTyp = nullptr;
		fujPrislusnost = nullptr;
		fujVzdelaniePocet = nullptr;
		fujVzdelaniePodiel = nullptr;

		zacniFiltrovanie(slovensko);

		return vyfiltrovanaTabulkaNaTriedenie;
	}

	void zapniFiltrovanie(UzemnaJednotka* slovensko) {

		bool ajTriedenie_ = false;

		fujPrislusnostAktivovany = false;
		fujTypAktivovany = false;
		fujVzdelaniePocetAktivovany = false;
		fujVzdelaniePodielAktivovany = false;

		kritPrislusnost = nullptr;
		CriterionUJVzdelaniePocet* kritVzdelaniePocet = nullptr;
		CriterionUJVzdelaniePodiel* kritVzdelaniePodiel = nullptr;

		delete fujTyp;
		delete fujPrislusnost;
		delete fujVzdelaniePocet;
		delete fujVzdelaniePodiel;

		fujTyp = nullptr;
		fujPrislusnost = nullptr;
		fujVzdelaniePocet = nullptr;
		fujVzdelaniePodiel = nullptr;

		zacniFiltrovanie(slovensko);
	}



	void zacniFiltrovanie(UzemnaJednotka* slovensko) {

	

		int pocetAplikovanychFiltrov = 0;


		system("cls");
		if (ajTriedenie_)
		{
			std::cout << "### FILTROVANIE S TRIEDENIM ###" << std::endl;
			std::cout << "# POPIS:" << std::endl;
			std::cout << "# Vyfiltruj si pod¾a vlastných filtrov uzemne jednotky a potom utriet." << std::endl;
		}
		else {
			std::cout << "### FILTROVANIE ###" << std::endl;
			std::cout << "# POPIS:" << std::endl;
			std::cout << "# Vo filtrovani si mozes vyfiltrovat uzemne jednotky podla vlastnych filtrov." << std::endl;
		}
		
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
			zacniFiltrovanie(slovensko);
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
				zacniFiltrovanie(slovensko);
				break;

			case 2:
				if (fujPrislusnostAktivovany) { fujPrislusnostAktivovany = false; }
				else { fujPrislusnostAktivovany = true; }
				zacniFiltrovanie(slovensko);
				break;
			case 3:
				if (fujVzdelaniePocetAktivovany) { fujVzdelaniePocetAktivovany = false; }
				else { fujVzdelaniePocetAktivovany = true; }
				zacniFiltrovanie(slovensko);
				break;
			case 4:
				if (fujVzdelaniePodielAktivovany) { fujVzdelaniePodielAktivovany = false; }
				else { fujVzdelaniePodielAktivovany = true; }
				zacniFiltrovanie(slovensko);
				break;

			default:
				system("cls");
				std::cout << "# ERROR # " << std::endl;
				std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
				std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
				system("pause");
				zacniFiltrovanie(slovensko);
				break;
			}
		}

		
	}


	void vlozParametreFiltrov(UzemnaJednotka* slovensko) {

		UZEMNA_JEDNOTKA fujTYP;
		UzemnaJednotka* povinnaPrislusnostUJ = nullptr;
		
		


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
					zacniFiltrovanie(slovensko);
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

			fujTyp = new FUJTyp<UzemnaJednotka*, UZEMNA_JEDNOTKA>(fujTYP);
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

			kritPrislusnost = new CriterionUJPrislusnost(povinnaPrislusnostUJ);
			fujPrislusnost = new FUJPrislusnost<UzemnaJednotka*, UzemnaJednotka*>(povinnaPrislusnostUJ, true);
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
				std::cout << "# Pokial chces bez limitu, napis slovo -> maximum" << std::endl;
				std::cout << std::endl << "VSTUP maximum -> ";
				std::string vstup = "";

				std::cin >> vstup;
				system("cls");

				if (vstup.compare("maximum") == 0)
				{
					zadanyMax = INT_MAX;
					break;
				}
				else {

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
			}
			kritVzdelaniePocet = new CriterionUJVzdelaniePocet(zvolenyTypVzdelania);
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

					if (zadanyMin <= stoi(vstup))
					{
						zadanyMax = stoi(vstup);
						breaknut = true;
					}
					else {
						system("cls");
						std::cout << "# ERROR # " << std::endl;
						std::cout << "# Maximum musi byt vacsi alebo rovny ako minimum " << std::endl;
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

			kritVzdelaniePodiel = new CriterionUJVzdelaniePodiel(zvolenyTypVzdelania);

			fujVzdelaniePodiel = new FUJVzdelaniePodiel<UzemnaJednotka*, double>(zvolenyTypVzdelania, zadanyMin, zadanyMax);
		}

		aplikujFiltre(slovensko);


	}

	void aplikujFiltre(UzemnaJednotka* slovensko) {

		if (!ajTriedenie_)
		{
			SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneKraje = new SortedSequenceTable<std::string, UzemnaJednotka*>();
			SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneOkresy = new SortedSequenceTable<std::string, UzemnaJednotka*>();
			SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneObce = new SortedSequenceTable<std::string, UzemnaJednotka*>();

			for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko->getUzemneJednotkyChildren())
			{
				for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
				{
					for (TableItem<std::string, UzemnaJednotka*>* obec : *okres->accessData()->getUzemneJednotkyChildren())
					{
						if (vyfiltrujUJ(obec->accessData()))
						{
							vyfiltrovaneObce->insert(obec->accessData()->getNazov(), obec->accessData());
						}
					}
					if (vyfiltrujUJ(okres->accessData()))
					{
						vyfiltrovaneOkresy->insert(okres->accessData()->getNazov(), okres->accessData());
					}
				}
				if (vyfiltrujUJ(kraj->accessData()))
				{
					vyfiltrovaneKraje->insert(kraj->accessData()->getNazov(), kraj->accessData());
				}
			}

			vypisVyslednehoVyfiltrovania(vyfiltrovaneKraje, vyfiltrovaneOkresy, vyfiltrovaneObce);

			delete vyfiltrovaneKraje;
			delete vyfiltrovaneOkresy;
			delete vyfiltrovaneObce;
		}
		else {

			UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneKraje = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
			UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneOkresy = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
			UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneObce = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();

			for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko->getUzemneJednotkyChildren())
			{
				for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
				{
					for (TableItem<std::string, UzemnaJednotka*>* obec : *okres->accessData()->getUzemneJednotkyChildren())
					{
						if (vyfiltrujUJ(obec->accessData()))
						{
							vyfiltrovaneObce->insert(obec->accessData()->getNazov(), obec->accessData());
						}
					}
					if (vyfiltrujUJ(okres->accessData()))
					{
						vyfiltrovaneOkresy->insert(okres->accessData()->getNazov(), okres->accessData());
					}
				}
				if (vyfiltrujUJ(kraj->accessData()))
				{
					vyfiltrovaneKraje->insert(kraj->accessData()->getNazov(), kraj->accessData());
				}
			}

			vyfiltrovanaTabulkaNaTriedenie = new LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>();

			vyfiltrovanaTabulkaNaTriedenie->add(vyfiltrovaneKraje);
			vyfiltrovanaTabulkaNaTriedenie->add(vyfiltrovaneOkresy);
			vyfiltrovanaTabulkaNaTriedenie->add(vyfiltrovaneObce);

		}		
	}

	void vypisVyslednehoVyfiltrovania(SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneKraje, SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneOkresy, SortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneObce) {
		system("cls");

		std::cout << "### VYSLEDNY VYPIS PO FILTROVANI ###" << std::endl;
		std::cout << "#" << std::endl;
		std::cout << "# Vypisane KRAJE: " << std::endl;

		for (TableItem<std::string, UzemnaJednotka*>* kraj : *vyfiltrovaneKraje) {

			std::cout << std::endl << std::endl << "## Nazov Uzemnej Jednotky -> " << kraj->accessData()->getNazov();

			if (fujTyp != nullptr)
			{
				std::cout << "# Typ Uzemnej Jednotky -> " << kraj->accessData()->getStringTypUzemnejJednotky() << std::endl;
			}
			if (fujVzdelaniePocet != nullptr)
			{
				std::cout << "# Vzdelanie POCET -> " << vratTextTypuVzdelania(fujVzdelaniePocet->getTypVzdelania()) << " : " << kraj->accessData()->getVzdelanie()->getPocetVzdelanie(fujVzdelaniePocet->getTypVzdelania()) << std::endl;
			}
			if (fujVzdelaniePodiel != nullptr)
			{
				std::cout << "# Vzdelanie PODIEL -> " << vratTextTypuVzdelania(fujVzdelaniePodiel->getTypVzdelania()) << " : " << kritVzdelaniePodiel->evaluate(kraj->accessData()) << std::endl;
			}
			std::cout <<  "### Vyssie Uzemne Jednotky:" << std::endl;
			std::cout << "1. Nazov -> " << kraj->accessData()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << kraj->accessData()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
		}
		std::cout << "# Vypisane OKRESY: " << std::endl;
		for (TableItem<std::string, UzemnaJednotka*>* okres : *vyfiltrovaneOkresy) {
			std::cout << std::endl << "## Nazov Uzemnej Jednotky -> " << okres->accessData()->getNazov();

			if (fujTyp != nullptr)
			{
				std::cout << "# Typ Uzemnej Jednotky -> " << okres->accessData()->getStringTypUzemnejJednotky() << std::endl;
			}
			if (fujVzdelaniePocet != nullptr)
			{
				std::cout << "# Vzdelanie POCET -> " << vratTextTypuVzdelania(fujVzdelaniePocet->getTypVzdelania()) << " : " << okres->accessData()->getVzdelanie()->getPocetVzdelanie(fujVzdelaniePocet->getTypVzdelania()) << std::endl;
			}
			if (fujVzdelaniePodiel != nullptr)
			{
				std::cout << "# Vzdelanie PODIEL -> " << vratTextTypuVzdelania(fujVzdelaniePodiel->getTypVzdelania()) << " : " << kritVzdelaniePodiel->evaluate(okres->accessData()) << std::endl;
			}
			std::cout  << "### Vyssie Uzemne Jednotky:" << std::endl;
			std::cout << "1. Nazov -> " << okres->accessData()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << okres->accessData()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
			std::cout << "2. Nazov -> " << okres->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << okres->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
		}
		std::cout << "# Vypisane OBCE: " << std::endl;
		for (TableItem<std::string, UzemnaJednotka*>* obec : *vyfiltrovaneObce) {
			std::cout << std::endl << "## Nazov Uzemnej Jednotky -> " << obec->accessData()->getNazov() << std::endl;

			if (fujTyp != nullptr)
			{
				std::cout << "# Typ Uzemnej Jednotky -> " << obec->accessData()->getStringTypUzemnejJednotky() << std::endl;
			}
			if (fujVzdelaniePocet != nullptr)
			{
				std::cout << "# Vzdelanie POCET -> " << vratTextTypuVzdelania(fujVzdelaniePocet->getTypVzdelania()) << " : " << obec->accessData()->getVzdelanie()->getPocetVzdelanie(fujVzdelaniePocet->getTypVzdelania()) << std::endl;
			}
			if (fujVzdelaniePodiel != nullptr)
			{
				std::cout << "# Vzdelanie PODIEL -> " << vratTextTypuVzdelania(fujVzdelaniePodiel->getTypVzdelania()) << " : " << kritVzdelaniePodiel->evaluate(obec->accessData()) << std::endl;
			}
			std::cout << "### Vyssie Uzemne Jednotky:" << std::endl;
			std::cout << "1. Nazov -> " << obec->accessData()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << obec->accessData()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
			std::cout << "2. Nazov -> " << obec->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << obec->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
			std::cout << "3. Nazov -> " << obec->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getVyssiaUJRodic()->getNazov() << "  # TYP -> " << obec->accessData()->getVyssiaUJRodic()->getVyssiaUJRodic()->getVyssiaUJRodic()->getStringTypUzemnejJednotky() << std::endl;
		}
		system("pause");
		system("cls");
	}

	


	bool vyfiltrujUJ(UzemnaJednotka* uzemnaJednotka) {

		bool jeDobra = false;

		if (fujTyp!=nullptr)
		{
			if (!fujTyp->pass(uzemnaJednotka))
			{
				return false;
			}
		}
		if (fujPrislusnost != nullptr)
		{
			if (!fujPrislusnost->pass(uzemnaJednotka) && !fujPrislusnost->pass(uzemnaJednotka->getVyssiaUJRodic()))
			{
				return false;
			}
		}
		if (fujVzdelaniePocet != nullptr)
		{
			if (!fujVzdelaniePocet->pass(uzemnaJednotka))
			{
				return false;
			}
		}
		if (fujVzdelaniePodiel != nullptr)
		{
			if (!fujVzdelaniePodiel->pass(uzemnaJednotka))
			{
				return false;
			}
		}

		return true;
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



	structures::Array<bool>* vratZoznamAktivovanychFiltrov() {
		Array<bool>* aktFiltre = new Array<bool>(4);
		aktFiltre->at(0) = fujTypAktivovany;
		aktFiltre->at(1) = fujPrislusnostAktivovany;

		aktFiltre->at(2) = fujVzdelaniePocetAktivovany;
		aktFiltre->at(3) = fujVzdelaniePodielAktivovany;

		return aktFiltre;
	}
};