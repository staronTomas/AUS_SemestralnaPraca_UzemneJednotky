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

#include "enum_UzemnaJednotka.h"
#include "enum_VyssiCelok.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"
#include "enum_EVS.h"
#include "structures/list/linked_list.h"


#include "structures/heap_monitor.h"

#include "UzemnaJednotka.h"
#include "CsvReader.h"



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

	}


	void spustiProgram() {
		std::cout << "Ahoj, Vitaj v tomto programe" << std::endl << std::endl;
		Sleep(1000);
		system("CLS");
		nacitajVsetkyData();
	}


	void nacitajVsetkyData() {
		
		LinkedList<LinkedList<std::string>*>* zoznamObci = reader_->nacitajObce("data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ;KodUJ

		LinkedList<LinkedList<std::string>*>* zoznamOkresov = reader_->nacitajOkresy("data_bez_diakritiky/okresy.csv");  // okresy mi nacita:   NazovUJ;KodUJ

		LinkedList<LinkedList<std::string>*>* zoznamKrajov = reader_->nacitajKraje("data_bez_diakritiky/kraje.csv");  // kraje mi nacita:   NazovUJ;KodUJ

		SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieZoSuborov = reader_->nacitajVzdelanie("data_bez_diakritiky/vzdelanie.csv");



		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			std::string nazovUjKraj = zoznamKrajov->at(i)->at(0);
			std::string kodUjKraj = zoznamKrajov->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::KRAJ, kodUjKraj, slovensko_);

			slovensko_->getUzemneJednotkyChildren()->insert(nazovUjKraj, novyKraj);

			system("CLS");
			int percentoDokoncene = 100 / zoznamKrajov->size() * i;
			std::cout << "Prebieha nacitavanie dat do uzemnych jednotiek." << std::endl << "Dokoncene: " << percentoDokoncene << "%" << std::endl;
			

			for (int j = 0; j < zoznamOkresov->size(); j++)
			{
				std::string okresNazovUj = zoznamOkresov->at(j)->at(0);
				std::string okresKodUJ = zoznamOkresov->at(j)->at(1);

				std::string subKodUjOkres = okresKodUJ.substr(0,5);
				
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
						}
					}
				}
			}
		}

		system("CLS");
		std::cout << "Nacitvanie dat bolo uspesne dokoncene." << std::endl;

		SortedSequenceTable<std::string, UzemnaJednotka*>*  kraje = slovensko_->getUzemneJednotkyChildren();

		int x = 0;
		
		for (int i = 0; i < zoznamKrajov->size(); i++)
		{
			int pocetOkresovVKraji = 0;
			int pocetObciVKraji = 0;


			std::string nazovKraja = zoznamKrajov->at(i)->at(0);

			for (int j = 0; j < zoznamOkresov->size(); j++)
			{

				std::string nazovOkresu = zoznamOkresov->at(j)->at(0);

				if (!slovensko_->getUzemneJednotkyChildren()->find(nazovKraja)->getUzemneJednotkyChildren()->containsKey(nazovOkresu)) {
					continue;
				}
				pocetOkresovVKraji++;

				for (int k = 0; k < zoznamObci->size(); k++)
				{
					std::string nazovObce = zoznamObci->at(k)->at(0);


					if (!slovensko_->getUzemneJednotkyChildren()->find(nazovKraja)->getUzemneJednotkyChildren()->find(nazovOkresu)->getUzemneJednotkyChildren()->containsKey(nazovObce)) {
						continue;
					}

					x++;
					/*
					std::cout << x << std::endl;
					std::cout << slovensko_->getUzemneJednotkyChildren()->find(nazovKraja)->getUzemneJednotkyChildren()->find(nazovOkresu)->getUzemneJednotkyChildren()->find(nazovObce)->getNazov() << std::endl;
					*/

					pocetObciVKraji++;

				}
			}
			std::cout << "V kraji " << nazovKraja << " je: " << pocetObciVKraji << " obci." << std::endl;
		}

		std::cout << "Celkovy pocet obci: " << x << std::endl;
		std::cout << "Koniec nacitavania a ukladania dat.";
	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
