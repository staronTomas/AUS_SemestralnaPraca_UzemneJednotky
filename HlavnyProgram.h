#pragma once

#include <iostream>
#include <string.h>

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
		std::cout << "ahoj, Vitaj v tomto programe" << std::endl << std::endl;

		nacitajVsetkyData();
	}


	void nacitajVsetkyData() {
		
		LinkedList<LinkedList<std::string>*>* obceList = reader_->nacitajObce("../Data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ;KodUJ

		LinkedList<LinkedList<std::string>*>* okresyList = reader_->nacitajOkresy("../Data_bez_diakritiky/okresy.csv");  // okresy mi nacita:   NazovUJ;KodUJ

		LinkedList<LinkedList<std::string>*>* krajeList = reader_->nacitajKraje("../Data_bez_diakritiky/kraje.csv");  // kraje mi nacita:   NazovUJ;KodUJ

		SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieZoSuborov = reader_->nacitajVzdelanie("../Data_bez_diakritiky/vzdelanie.csv");


		for (int i = 0; i < krajeList->size(); i++)
		{
			std::string nazovUjKraj = krajeList->at(i)->at(0);
			std::string kodUjKraj = krajeList->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::KRAJ, kodUjKraj, slovensko_);
			slovensko_->getUzemneJednotkyChildren()->insert(nazovUjKraj, novyKraj);

			for (int j = 0; j < okresyList->size(); j++)
			{
				std::string okresNazovUj = okresyList->at(j)->at(0);
				std::string okresKodUJ = okresyList->at(j)->at(1);

				std::string subKodUjOkres = okresKodUJ.substr(0,5);
				
				int porovnanie = subKodUjOkres.compare(kodUjKraj);

				if (porovnanie == 0)
				{
					// patri okres do tohoto kraja
					// idem okresu priradit jeho OBCE V CYKLE
					UzemnaJednotka* novyOkres = new UzemnaJednotka(okresNazovUj, UZEMNA_JEDNOTKA::OKRES, okresKodUJ, novyKraj);
					novyKraj->getUzemneJednotkyChildren()->insert(okresNazovUj, novyOkres);

					for (int j = 0; j < obceList->size(); j++)
					{
						std::string obecNazovUj = obceList->at(j)->at(0);
						std::string obecKodUJ = obceList->at(j)->at(1);

						std::string subKodUjObec = obecKodUJ.substr(0, 6);

						int porovnanie = subKodUjObec.compare(okresKodUJ);

						if (porovnanie == 0)
						{
							// patri okres do tohoto kraja
							// idem okresu priradit jeho OBCE V CYKLE

							UzemnaJednotka* novaObec = new UzemnaJednotka(obecNazovUj, UZEMNA_JEDNOTKA::OBEC, obecKodUJ, novaObec);
							novyOkres->getUzemneJednotkyChildren()->insert(obecNazovUj, novyOkres);

						}
					}
				}
			}
		}
	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
