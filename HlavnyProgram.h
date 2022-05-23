#pragma once


#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "structures/array/array.h"
#include "structures/list/linked_list.h"
#include "structures/heap_monitor.h"

#include "UzemnaJednotka.h"
#include "Vzdelanie.h"
#include "Vek.h"
#include "CsvReader.h"
#include "Filter.h"


#include "enum_UzemnaJednotka.h"
#include "enum_VyssiCelok.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"
#include "enum_EVS.h"

#include "Criterion.h"
#include "CriterionUJ.h"
#include "CriterionUJNazov.h"
#include "CriterionUJTyp.h"
#include "CriterionVzdelaniePocet.h"
#include "CriterionUJVekovaSkupinaPocet.h"
#include "CriterionVzdelaniePodiel.h"


class HlavnyProgam {



private:

	UzemnaJednotka* slovensko_;
	CsvReader* reader_;

public:

	HlavnyProgam() {
		slovensko_ = new UzemnaJednotka("Slovensko", UZEMNA_JEDNOTKA::STAT, "SK", nullptr);
		reader_ = new CsvReader();

	}

	~HlavnyProgam() {

		delete reader_;

		for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko_->getUzemneJednotkyChildren())
		{
			for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
			{
				for (TableItem<std::string, UzemnaJednotka*>* obec : *okres->accessData()->getUzemneJednotkyChildren())
				{
					delete obec->accessData();
				}
				delete okres->accessData();
			}
			delete kraj->accessData();
		}
		delete slovensko_;
	}


	void spustiProgram() {
		std::cout << "### Ahoj, Vitaj v tomto programe ###" << std::endl << std::endl;
		Sleep(1500);
		system("CLS");
		nacitajVsetkyData();
		//zvolCinnost();




	}



	void zvolCinnost() {
		system("cls");
		std::cout << "# Zvol cislo cinnosti, ktoru chces vykonat # " << std::endl;
		std::cout << "# 1 # Bodove Vyhladavanie " << std::endl;
		std::cout << "# 2 # Filtorvanie " << std::endl;
		std::cout << "# 3 # Zobrazit vsetky Uzemne Jednotky hierarchicky (Slovensko > kraje > okresy > obce) " << std::endl;
		std::cout << "# 4 # Ukoncit program " << std::endl;
		std::cout << "# VSTUP:  ";
		std::string vstup = "";
		std::cin >> vstup;

		if (!isNumber(vstup))
		{
			system("cls");
			std::cout << "# ERROR # " << std::endl;
			std::cout << "# Musis Napisat CISLO " << std::endl;
			std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
			system("pause");
			zvolCinnost();
		}
		else {
			int vstupInt = std::stoi(vstup);

			switch (vstupInt)
			{
			case 1:
				bodoveVyhladavnie();
				zvolCinnost();
				break;

			case 2:
				zvolCinnost();
				break;

			case 3:
				zvolCinnost();
				break;

			case 4:
				system("cls");
				std::cout << "# Aplikacia bola ukoncena. " << std::endl;
				break;

			default:
				system("cls");
				std::cout << "# ERROR # " << std::endl;
				std::cout << "# Zvolene cislo neponuka ziadnu akciu. " << std::endl;
				std::cout << "# Pre pokracovanie stlac lubovolne tlacidlo. " << std::endl;
				system("pause");
				zvolCinnost();
				break;
			}
		}

	}


	void bodoveVyhladavnie() {
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
		volbaUzemnejJednotkyKraj();
	}


	void vypisBodovehoVyhladavania(UzemnaJednotka* uzemnaJednotka) {
		UzemnaJednotka* zvolenaUJ = uzemnaJednotka;

		CriterionUJNazov* kritNazov = new CriterionUJNazov();
		CriterionUJTyp* kritTyp = new CriterionUJTyp();
		CriterionUJVzdelaniePocet* kritVzdPocet = new CriterionUJVzdelaniePocet();
		CriterionUJVekovaSkupinaPocet* kritVekSkupPocet = new CriterionUJVekovaSkupinaPocet();

		system("cls");
		std::cout << "### Vysledny vypis o hladanej Uzemnej jednotke a jej vyssie jednotky do ktorých patrí" << std::endl << std::endl;
		int i = 1;
		while (zvolenaUJ != nullptr) {
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
			i++;
		}
		delete kritNazov;
		delete kritTyp;
		delete kritVzdPocet;
		delete kritVekSkupPocet;
		system("pause");
	}

	void volbaUzemnejJednotkyKraj() {
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
				if (vstupInt >= 0 && vstupInt <= slovensko_->getUzemneJednotkyChildren()->size() || vstupInt == 999)
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
			zvolCinnost();
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
			zvolCinnost();
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
			zvolCinnost();
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


	void nacitajVsetkyData() {

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: obce.csv" << std::endl;
		std::cout << "# Hotovo -> 0%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamObci = reader_->nacitajObce("data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: okresy.csv" << std::endl;
		std::cout << "# Hotovo -> 20%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamOkresov = reader_->nacitajOkresy("data_bez_diakritiky/okresy.csv");  // okresy mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: kraje.csv" << std::endl;
		std::cout << "# Hotovo -> 40%" << std::endl;
		LinkedList<LinkedList<std::string>*>* zoznamKrajov = reader_->nacitajKraje("data_bez_diakritiky/kraje.csv");  // kraje mi nacita:   NazovUJ;KodUJ

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: vzdelanie.csv" << std::endl;
		std::cout << "# Hotovo -> 60%" << std::endl;
		SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieZoSuborov = reader_->nacitajVzdelanie("data_bez_diakritiky/vzdelanie.csv");

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: vek.csv" << std::endl;
		std::cout << "# Hotovo -> 80%" << std::endl;
		SortedSequenceTable<std::string, Vek*>* vekZoSuborov = reader_->nacitajVek("data_bez_diakritiky/vek.csv");
		
		// Utriedenie duplicitnych zoznamov OBCI, priadnie na koniec nazov okresu v ktorom je

		system("cls");
		std::cout << "# Parsovanie bolo dokoncene." << std::endl;
		std::cout << std::endl;
		std::cout << "# Hotovo -> 100%" << std::endl;
		Sleep(1000);

		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			std::string nazovUjKraj = zoznamKrajov->at(i)->at(0);
			std::string kodUjKraj = zoznamKrajov->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::KRAJ, kodUjKraj, slovensko_);

			slovensko_->getUzemneJednotkyChildren()->insert(nazovUjKraj, novyKraj);

			system("CLS");
			int percentoDokoncene = 100 / zoznamKrajov->size() * i;
			std::cout << "# Prebieha vkladanie dat do uzemnych jednotiek." << std::endl;
			std::cout << "#" << std::endl;
			std::cout << "# Prebieha ukladanie dat v Uzemnej jednotke -> " << nazovUjKraj << " a jeho okresoch a obciach." << std::endl;
			std::cout << "# Dokoncene: " << percentoDokoncene << "%" << std::endl;

			for (int j = 0; j < zoznamOkresov->size(); j++)
			{
				std::string okresNazovUj = zoznamOkresov->at(j)->at(0);
				std::string okresKodUJ = zoznamOkresov->at(j)->at(1);

				std::string subKodUjOkres = okresKodUJ.substr(0, 5);

				int porovnanie = subKodUjOkres.compare(kodUjKraj);

				if (porovnanie == 0)
				{
					// patri okres do tohoto kraja
					// idem okresu priradit jeho OBCE V CYKLE
					UzemnaJednotka* novyOkres = new UzemnaJednotka(okresNazovUj, UZEMNA_JEDNOTKA::OKRES, okresKodUJ, novyKraj);
					novyKraj->getUzemneJednotkyChildren()->insert(okresNazovUj, novyOkres);

					for (int j = 0; j < zoznamObci->size(); j++)
					{
						std::string obecNazovUj = zoznamObci->at(j)->at(0);
						std::string obecKodUJ = zoznamObci->at(j)->at(1);

						std::string subKodUjObec = obecKodUJ.substr(0, 6);

						int porovnanie = subKodUjObec.compare(okresKodUJ);

						if (porovnanie == 0)
						{
							// patri okres do tohoto kraja
							// idem okresu priradit jeho OBCE V CYKLE
							UzemnaJednotka* novaObec = new UzemnaJednotka(obecNazovUj, UZEMNA_JEDNOTKA::OBEC, obecKodUJ, novyOkres);
							novyOkres->getUzemneJednotkyChildren()->insert(obecNazovUj, novaObec);


							// pokial sa dana obec nachadzala v CSV Vek tak jej priradim jej udaje a takisto jej vyssim uzemnym jednotkam.
							// Chybala tam jedna obec tak preto overujem ete aj cez containsKey()
							if (vzdelanieZoSuborov->containsKey(obecKodUJ)) {
								Vzdelanie* vzd = vzdelanieZoSuborov->find(obecKodUJ);
								novaObec->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novaObec->navysPocetObyvatelovZoVzdelania(vzd);

								novyOkres->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyOkres->navysPocetObyvatelovZoVzdelania(vzd);

								novyKraj->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyKraj->navysPocetObyvatelovZoVzdelania(vzd);

								slovensko_->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								slovensko_->navysPocetObyvatelovZoVzdelania(vzd);
							}

							// pokial sa dana obec nachadzala v CSV Vek tak jej priradim jej udaje a takisto jej vyssim uzemnym jednotkam.
							// Chybala tam jedna obec tak preto overujem ete aj cez containsKey()
							if (vekZoSuborov->containsKey(obecKodUJ)) {
								Vek* vek = vekZoSuborov->find(obecKodUJ);
								novaObec->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								novaObec->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								novyOkres->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								novyOkres->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								novyKraj->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								novyKraj->getVekObyvatelov()->navysPocetEvsSkupin(vek);

								slovensko_->getVekObyvatelov()->navysPocetVekCelkovo(vek);
								slovensko_->getVekObyvatelov()->navysPocetEvsSkupin(vek);
							}
						}
					}
				}
			}
		}
		
		
		system("CLS");
		std::cout << "# Nacitavanie dat bolo uspesne dokoncene." << std::endl;
		std::cout << "#" << std::endl;
		std::cout << "# Pri obsluhe programe nepouzivaj diakritiku." << std::endl;
		Sleep(1000);
		std::cout << "# Pre pokracovanie stlac lubovolnu klavesu." << std::endl;
		system("pause");

		
		for (int i = 0; i < zoznamObci->size(); i++)
		{
			delete zoznamObci->at(i);
		}
		delete zoznamObci;

		for (int i = 0; i < zoznamOkresov->size(); i++)
		{
			delete zoznamOkresov->at(i);
		}
		delete zoznamOkresov;
		
		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			delete zoznamKrajov->at(i);
		}
		delete zoznamKrajov;


		for (TableItem<std::string, Vzdelanie*>* item : *vzdelanieZoSuborov)
		{
			delete item->accessData();
		}
		delete vzdelanieZoSuborov;

		
		for (TableItem<std::string, Vek*>* item : *vekZoSuborov)
		{
			delete item->accessData();
		}
		delete vekZoSuborov;
		
	}


	UzemnaJednotka* getSlovensko() {
		return slovensko_;
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