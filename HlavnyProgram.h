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
#include "ZoznamUzemnychJednotiek.h"



class HlavnyProgam {
	


private:

	UzemnaJednotka* slovensko_;
	CsvReader* reader_;
	ZoznamUzemnychJednotiek* zoznamUJ_;

public:

	HlavnyProgam() {
		slovensko_ = new UzemnaJednotka("Slovensko", UZEMNA_JEDNOTKA::STAT, "SK", nullptr);
		reader_ = new CsvReader();
		zoznamUJ_ = new ZoznamUzemnychJednotiek();

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

		// Utriedenie duplicitnych zoznamov OBCI, priadnie na koniec nazov okresu v ktorom je

		zoznamUJ_->setZoznamObci(zoznamObci);
		zoznamUJ_->setZoznamOkresov(zoznamOkresov);
		zoznamUJ_->setZoznamKrajov(zoznamKrajov);


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


							if (vzdelanieZoSuborov->containsKey(obecKodUJ)) {
								Vzdelanie* vzd = vzdelanieZoSuborov->find(obecKodUJ);
								novaObec->setVzdelanie(vzd);
								novaObec->navysPocetObyvatelovZoVzdelania(vzd);

								novyOkres->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyOkres->navysPocetObyvatelovZoVzdelania(vzd);

								novyKraj->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								novyKraj->navysPocetObyvatelovZoVzdelania(vzd);

								slovensko_->getVzdelanie()->navysCelkovyPocetVzdelania(vzd);
								slovensko_->navysPocetObyvatelovZoVzdelania(vzd);
							}	
						}
					}
				}
			}	
		}

		system("CLS");
		std::cout << "Nacitavanie dat bolo uspesne dokoncene." << std::endl;
	
	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
