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
#include "structures/list/double_linked_list.h"
#include "structures/heap_monitor.h"

#include "UzemnaJednotka.h"
#include "Vzdelanie.h"
#include "Vek.h"
#include "CsvReader.h"
#include "Filter.h"
#include "Filtrovanie.h"
#include "BodoveVyhladavanie.h"
#include "Triedenie.h"

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

	BodoveVyhladavanie* bodoveVyhladavanie_;
	Filtrovanie* filter_;
	Triedenie* triedenie_;


public:

	HlavnyProgam() {
		slovensko_ = new UzemnaJednotka("Slovensko", UZEMNA_JEDNOTKA::STAT, "SK", nullptr);
		reader_ = new CsvReader();
		filter_ = new Filtrovanie();
		bodoveVyhladavanie_ = new BodoveVyhladavanie();
		triedenie_ = new Triedenie();
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

		delete filter_;

		delete bodoveVyhladavanie_;

		delete triedenie_;
	}


	void spustiProgram() {
		std::cout << "### Ahoj, Vitaj v tomto programe ###" << std::endl << std::endl;
		Sleep(1500);
		system("CLS");
		nacitajVsetkyData();
		zvolCinnost();



	}



	void zvolCinnost() {
		system("cls");
		std::cout << "# Zvol cislo cinnosti, ktoru chces vykonat # " << std::endl;
		std::cout << "# 1 # Bodove Vyhladavanie " << std::endl;
		std::cout << "# 2 # Filtorvanie " << std::endl;
		std::cout << "# 3 # Triedenie " << std::endl;
		std::cout << "# 4 # Zobrazit vsetky Uzemne Jednotky hierarchicky (Slovensko > kraje > okresy > obce) " << std::endl;
		std::cout << "# 5 # Ukoncit program " << std::endl;
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
				bodoveVyhladavanie_->bodoveVyhladavnie(slovensko_);
				zvolCinnost();
				break;

			case 2:
				filter_->zapniFiltrovanie(slovensko_);
				zvolCinnost();
				break;
			case 3:
				triedenie_->spustiTriedenie(slovensko_);
				zvolCinnost();
				break;

			case 4:
				vypisVsetkyUzemneJednotky();
				system("pause");
				system("cls");
				zvolCinnost();
				break;

			case 5:
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



	void nacitajVsetkyData() {

		system("cls");
		std::cout << "# Parsujem data z CSV suborov." << std::endl;
		std::cout << "# Citany subor: obce.csv" << std::endl;
		std::cout << "# Hotovo -> 0%" << std::endl;
		DoubleLinkedList<LinkedList<std::string>*>* zoznamObci = reader_->nacitajObce("data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ;KodUJ

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

		system("cls");
		std::cout << "# Parsovanie bolo dokoncene." << std::endl;
		std::cout << std::endl;
		std::cout << "# Hotovo -> 100%" << std::endl;
		Sleep(1000);


		int pocetSpracovanychOkresov = 0;
		double percentoDokoncene = 0.0;

		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			std::string nazovUjKraj = zoznamKrajov->at(i)->at(0);
			std::string kodUjKraj = zoznamKrajov->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::KRAJ, kodUjKraj, slovensko_);

			slovensko_->getUzemneJednotkyChildren()->insert(nazovUjKraj, novyKraj);


			for (int j = 0; j < zoznamOkresov->size(); j++)
			{
				
				
				std::string okresNazovUj = zoznamOkresov->at(j)->at(0);
				std::string okresKodUJ = zoznamOkresov->at(j)->at(1);

				std::string subKodUjOkres = okresKodUJ.substr(0, 5);


				// informacny vypis na konzolu
				double xPodiel = 100.0 / zoznamOkresov->size() * pocetSpracovanychOkresov;
				if (xPodiel > percentoDokoncene) {
					system("CLS");
					percentoDokoncene = xPodiel;
					std::cout << "# Prebieha vkladanie dat do uzemnych jednotiek." << std::endl;
					std::cout << "#" << std::endl;
					std::cout << "# Kraj -> " << nazovUjKraj << std::endl;
					std::cout << "# Okres -> " << okresNazovUj << std::endl;
					std::cout << "#" << std::endl;
					std::cout << "# Podiel spracovanych Uzemnych Jednotiek: " << percentoDokoncene << "%" << std::endl;
				}// informacny vypis na konzolu




				int porovnanie = subKodUjOkres.compare(kodUjKraj);

				if (porovnanie == 0)
				{
					pocetSpracovanychOkresov++;
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



		// kontrola duplicitnych obci -> ak existuje duplicita, pridelim 
		SortedSequenceTable<std::string, UzemnaJednotka*>* tabulkaDupl = new SortedSequenceTable<std::string, UzemnaJednotka*>();

		int counter = 0;
		for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko_->getUzemneJednotkyChildren())
		{

			system("CLS");
			std::cout << "# Prehladavanie duplicitnych nazvov a odlišovanie." << std::endl;
			std::cout << "#" << std::endl;
			int hotovo = 50 / slovensko_->getUzemneJednotkyChildren()->size() * counter;
			std::cout << "# Hotovo -> " << hotovo <<  " % " << std::endl;

			for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
			{
				for (TableItem<std::string, UzemnaJednotka*>* obec : *okres->accessData()->getUzemneJednotkyChildren())
				{
					if (tabulkaDupl->containsKey(obec->accessData()->getNazov())) {

						std::string novyNazovVTabulkeUJ = obec->accessData()->getNazov() + " (Okres " + tabulkaDupl->find(obec->accessData()->getNazov())->getVyssiaUJRodic()->getNazov() + ")";
						std::string novyNazovVCykleUJ = obec->accessData()->getNazov() + " (Okres " + obec->accessData()->getVyssiaUJRodic()->getNazov() + ")";

						tabulkaDupl->find(obec->accessData()->getNazov())->setNazov(novyNazovVTabulkeUJ);
						obec->accessData()->setNazov(novyNazovVCykleUJ);
						
						tabulkaDupl->insert(novyNazovVCykleUJ, obec->accessData());
					}
					else {
						tabulkaDupl->insert(obec->accessData()->getNazov(), obec->accessData());
					}
				}
			}
			counter++;
		}

		delete tabulkaDupl;
		
		
		system("CLS");
		std::cout << "# Nacitavanie dat bolo uspesne dokoncene." << std::endl;
		std::cout << "#" << std::endl;
		std::cout << "# Pri obsluhe programe nepouzivaj diakritiku." << std::endl;
		std::cout << "# Pre pokracovanie stlac lubovolnu klavesu." << std::endl;
		system("pause");



		for (TableItem<std::string, Vek*>* item : *vekZoSuborov)
		{
			delete item->accessData();
			item->accessData() = nullptr;

		}
		delete vekZoSuborov;
		vekZoSuborov = nullptr;





		
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

	}


	void vypisVsetkyUzemneJednotky() {

		std::cout << "### ZOZNAM VSETKYCH UZEMNYCH JEDNOTIEK HIERARCHICKY ###" << std::endl << std::endl;
		std::cout << "### SLOVENSKO ###" << std::endl;

		for (TableItem<std::string, UzemnaJednotka*>* kraj : *slovensko_->getUzemneJednotkyChildren())
		{
			std::cout << "   ## " << kraj->accessData()->getNazov() << std::endl;

			for (TableItem<std::string, UzemnaJednotka*>* okres : *kraj->accessData()->getUzemneJednotkyChildren())
			{
				std::cout << "      # " << okres->accessData()->getNazov() << std::endl;

				for (TableItem<std::string, UzemnaJednotka*>* obec : *okres->accessData()->getUzemneJednotkyChildren())
				{
					std::cout << "         - " << obec->accessData()->getNazov() << std::endl;

				}
			}
			std::cout << std::endl;
		}
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
};