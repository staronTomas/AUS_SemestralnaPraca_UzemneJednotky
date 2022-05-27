#pragma once

#include <iostream>
#include "UzemnaJednotka.h"



#include "Criterion.h"
#include "CriterionUJ.h"
#include "CriterionUJNazov.h"
#include "CriterionUJTyp.h"
#include "CriterionVzdelaniePocet.h"
#include "CriterionUJVekovaSkupinaPocet.h"
#include "CriterionVzdelaniePodiel.h"


class BodoveVyhladavanie {


private:


public:

	BodoveVyhladavanie() {};
	~BodoveVyhladavanie() {};


	void bodoveVyhladavnie(UzemnaJednotka* slovensko_) {
		system("CLS");
		std::cout << "### BODOVE VYHLADAVANIE ###" << std::endl;
		std::cout << "# POPIS:" << std::endl;
		std::cout << "# V bodovom vyhladavani si mozes zvolit uzemnu jednotku o ktorej chces ziskat informacie o vzdelani pre nu a pre jej nadradene Uzemne Jednotky." << std::endl;
		std::cout << "#" << std::endl;
		std::cout << "# Moznosti volby Uzemnej jednotky: " << std::endl;
		std::cout << "#" << std::endl;
		std::cout << "# Zvol CISLO Uzemnej jednotky" << std::endl;
		std::cout << "# 999 # " << "Zrusit vyhladavanie" << std::endl;
		std::cout << "# " << 0 << " # " << "Vyhodnot pre cele Slovensko" << std::endl;
		volbaUzemnejJednotkyKraj(slovensko_);
	}


	void vypisBodovehoVyhladavania(UzemnaJednotka* uzemnaJednotka) {
		UzemnaJednotka* zvolenaUJ = uzemnaJednotka;

		CriterionUJNazov* kritNazov = new CriterionUJNazov();
		CriterionUJTyp* kritTyp = new CriterionUJTyp();
		CriterionUJVzdelaniePocet* kritVzdPocet = new CriterionUJVzdelaniePocet(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI);
		CriterionUJVekovaSkupinaPocet* kritVekSkupPocet = new CriterionUJVekovaSkupinaPocet(EVS::PREDPRODUKTIVNI);

		system("cls");
		std::cout << "### Vysledny vypis o hladanej Uzemnej jednotke a jej vyssie jednotky do ktorých patrí" << std::endl << std::endl;
		int i = 1;

		std::cout << "### " << i << ".    # " << kritNazov->evaluate(zvolenaUJ) << std::endl;;
		std::cout << "# Typ  UJ # " << getStringTypUJ(kritTyp->evaluate(zvolenaUJ)) << std::endl << std::endl;

		std::cout << "# VZDELANIE    #" << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI);
		std::cout << "# Bez Vzdelanie DETI    # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::ZAKLADNE);
		std::cout << "# Zakladne Vzdelanie    # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::UCNOVSKE);
		std::cout << "# Ucnovske              # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::STREDNE);
		std::cout << "# Stredoskolske         # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::VYSSIE);
		std::cout << "# Vyssie Vzdelanie      # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::VYSOKOSKOLSKE);
		std::cout << "# Vysokoskolske         # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::BEZ_VZDELANIA);
		std::cout << "# Bez Vzdelania Dospely # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		kritVzdPocet->setTypVzdelania(TYP_VZDELANIA::NEZISTENE);
		std::cout << "# Nezistene Vzdelanie   # " << kritVzdPocet->evaluate(zvolenaUJ) << std::endl;
		std::cout << std::endl;

		std::cout << "# Ekonomicke vekove skupiny  #" << std::endl;
		kritVekSkupPocet->setTypEvs(EVS::PREDPRODUKTIVNI);
		std::cout << "# Pocet Predproduktivnych    # " << kritVekSkupPocet->evaluate(zvolenaUJ) << std::endl;
		kritVekSkupPocet->setTypEvs(EVS::PRODUKTIVNI);
		std::cout << "# Pocet Produktivnych        # " << kritVekSkupPocet->evaluate(zvolenaUJ) << std::endl;
		kritVekSkupPocet->setTypEvs(EVS::POPRODUKTIVNY);
		std::cout << "# Pocet Poproduktivnyc       # " << kritVekSkupPocet->evaluate(zvolenaUJ) << std::endl;

		std::cout << "########################################" << std::endl << std::endl;
		zvolenaUJ = zvolenaUJ->getVyssiaUJRodic();

		while (zvolenaUJ != nullptr) {
			i++;
			std::cout << "### " << i << ".    # " << kritNazov->evaluate(zvolenaUJ) << std::endl;;
			std::cout << "# Typ  UJ # " << getStringTypUJ(kritTyp->evaluate(zvolenaUJ)) << std::endl << std::endl;
			zvolenaUJ = zvolenaUJ->getVyssiaUJRodic();
		}
		delete kritNazov;
		delete kritTyp;
		delete kritVzdPocet;
		delete kritVekSkupPocet;
		system("pause");
	}

	void volbaUzemnejJednotkyKraj(UzemnaJednotka* slovensko_) {
		UzemnaJednotka* zvolenyKraj;

		structures::Array<UzemnaJednotka*>* ciselnyZoznamUJKraje = new structures::Array<UzemnaJednotka*>(slovensko_->getUzemneJednotkyChildren()->size());
		std::string vstup = "x";
		int vstupInt = -1;


		while (true)
		{
			int i = 0;
			for (TableItem<std::string, UzemnaJednotka*>* item : *slovensko_->getUzemneJednotkyChildren())
			{
				i++;

				std::cout << "# " << i << " # " << item->accessData()->getNazov() << std::endl;
				ciselnyZoznamUJKraje->at(i - 1) = item->accessData();
			}

			std::cout << "# UJ Kraj zvol napisanim cisla " << std::endl;
			std::cout << "# VSTUP: ";
			std::cin >> vstup;

			if (isNumber(vstup)) {
				vstupInt = std::stoi(vstup);
				if (vstupInt >= 0 && unsigned(vstupInt) <= slovensko_->getUzemneJednotkyChildren()->size() || vstupInt == 999)
				{
					break;
				}
				else {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO zo zoznamu, ktory ti bol vypisany" << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
					system("cls");
				}
			}
		}

		if (vstupInt == 999)
		{
			return;
		}

		if (vstupInt == 0)
		{
			system("cls");
			vypisBodovehoVyhladavania(slovensko_);
		}
		else {
			zvolenyKraj = ciselnyZoznamUJKraje->at(vstupInt - 1);

			system("cls");
			volbaUzemnejJednotkyOkres(zvolenyKraj);
		}

		delete ciselnyZoznamUJKraje;
	}


	void volbaUzemnejJednotkyOkres(UzemnaJednotka* zvolenyKraj) {
		UzemnaJednotka* zvolenyOkres;


		structures::Array<UzemnaJednotka*>* ciselnyZoznamUJOkresy = new structures::Array<UzemnaJednotka*>(zvolenyKraj->getUzemneJednotkyChildren()->size());
		std::string vstup = "x";
		int vstupInt = -1;


		while (true)
		{




			std::cout << "# Moznosti volby Uzemnej jednotky: " << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# Zvol CISLO Uzemnej jednotky" << std::endl;
			std::cout << "# 999 # " << "Zrusit vyhladavanie" << std::endl;
			std::cout << "# " << 0 << " # " << "Vyhodnot pre cely " << zvolenyKraj->getNazov() << std::endl;

			int i = 0;
			for (TableItem<std::string, UzemnaJednotka*>* item : *zvolenyKraj->getUzemneJednotkyChildren())
			{
				i++;
				std::cout << "# " << i << " # " << item->accessData()->getNazov() << std::endl;
				ciselnyZoznamUJOkresy->at(i - 1) = item->accessData();
			}

			std::cout << "# UJ Okres zvol napisanim daneho nazvu " << std::endl;
			std::cout << "# VSTUP: ";
			std::cin >> vstup;

			if (isNumber(vstup)) {
				vstupInt = std::stoi(vstup);
				if (vstupInt >= 0 && vstupInt <= zvolenyKraj->getUzemneJednotkyChildren()->size() || vstupInt == 999)
				{
					break;
				}
				else {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO zo zoznamu, ktory ti bol vypisany" << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
				}
			}

			system("cls");
			std::cout << "# ERROR # " << std::endl;
			std::cout << "# Musis Napisat CISLO" << std::endl;
			std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
			system("pause");
		}

		if (vstupInt == 999)
		{
			return;
		}

		if (vstupInt == 0)
		{
			system("cls");
			vypisBodovehoVyhladavania(zvolenyKraj);
		}
		else {
			zvolenyOkres = ciselnyZoznamUJOkresy->at(vstupInt - 1);
			system("cls");
			volbaUzemnejJednotkyObec(zvolenyOkres);
		}

		delete ciselnyZoznamUJOkresy;
	}




	void volbaUzemnejJednotkyObec(UzemnaJednotka* zvolenyOkres) {
		UzemnaJednotka* zvolenaObec;


		structures::Array<UzemnaJednotka*>* ciselnyZoznamUJObce = new structures::Array<UzemnaJednotka*>(zvolenyOkres->getUzemneJednotkyChildren()->size());
		std::string vstup = "x";
		int vstupInt = -1;


		while (true)
		{




			std::cout << "# Moznosti volby Uzemnej jednotky: " << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# Zvol CISLO Uzemnej jednotky" << std::endl;
			std::cout << "# 999 # " << "Zrusit vyhladavanie" << std::endl;
			std::cout << "# " << 0 << " # " << "Vyhodnot pre cely Okres" << zvolenyOkres->getNazov() << std::endl;

			int i = 0;
			for (TableItem<std::string, UzemnaJednotka*>* item : *zvolenyOkres->getUzemneJednotkyChildren())
			{
				i++;
				std::cout << "# " << i << " # " << item->accessData()->getNazov() << std::endl;
				ciselnyZoznamUJObce->at(i - 1) = item->accessData();
			}

			std::cout << "# UJ Obec zvol napisanim daneho nazvu " << std::endl;
			std::cout << "# VSTUP: ";
			std::cin >> vstup;

			if (isNumber(vstup)) {
				vstupInt = std::stoi(vstup);
				if (vstupInt >= 0 && vstupInt <= zvolenyOkres->getUzemneJednotkyChildren()->size() || vstupInt == 999)
				{
					break;
				}
				else {
					system("cls");
					std::cout << "# ERROR # " << std::endl;
					std::cout << "# Musis Napisat CISLO zo zoznamu, ktory ti bol vypisany" << std::endl;
					std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
					system("pause");
				}
			}

			system("cls");
			std::cout << "# ERROR # " << std::endl;
			std::cout << "# Musis Napisat CISLO" << std::endl;
			std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
			system("pause");
		}

		if (vstupInt == 999)
		{
			return;
		}

		if (vstupInt == 0)
		{
			system("cls");
			vypisBodovehoVyhladavania(zvolenyOkres);

		}
		else {
			zvolenaObec = ciselnyZoznamUJObce->at(vstupInt - 1);
			system("cls");
			vypisBodovehoVyhladavania(zvolenaObec);
		}

		delete ciselnyZoznamUJObce;

	}


	bool isNumber(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}


	std::string getStringTypUJ(UZEMNA_JEDNOTKA typ) {
		switch (typ)
		{
		case UZEMNA_JEDNOTKA::STAT:
			return "Stat";
			break;
		case UZEMNA_JEDNOTKA::KRAJ:
			return "Kraj";
			break;
		case UZEMNA_JEDNOTKA::OKRES:
			return "Okres";
			break;
		case UZEMNA_JEDNOTKA::OBEC:
			return "Obec";
			break;
		default:
			return "Neznamy typ UJ";
			break;
		}
	}
};