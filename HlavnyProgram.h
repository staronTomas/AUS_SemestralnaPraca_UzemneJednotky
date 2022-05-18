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


		
		//Najprv si ich vsetky vlozim do tychto SequenceTable postupne

		SortedSequenceTable<std::string, UzemnaJednotka*>* obce = new SortedSequenceTable<std::string, UzemnaJednotka*>();
		SortedSequenceTable<std::string, UzemnaJednotka*>* okresy = new SortedSequenceTable<std::string, UzemnaJednotka*>();
		SortedSequenceTable<std::string, UzemnaJednotka*>* kraje = new SortedSequenceTable<std::string, UzemnaJednotka*>();


		for (int i = 0; i < krajeList->size(); i++)
		{
			std::string nazovUjKraj = krajeList->at(i)->at(0);
			std::string kodUjKraj = krajeList->at(i)->at(1);

			UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovUjKraj, UZEMNA_JEDNOTKA::OBEC, kodUjKraj, slovensko_);

			for (int j = 0; j < okresyList->size(); j++)
			{
				std::string subKodUjOkres = okresyList->at(j)->at(1).substr(0,5);
				
				int porovnanie = subKodUjOkres.compare(kodUjKraj);

				std::cout << subKodUjOkres << "    -     " << kodUjKraj << std::endl;
				if (porovnanie == 0)
				{
					std::cout << "anoo" << std::endl;
				}
				else {
					std::cout << "nieee" << std::endl;
				}

			}


			kraje->insert(kodUjKraj, novyKraj);
		}

		// Teraz popriradujem kazdej uzemnej jednotke jej nizzsie uzemne jednotky "children"
		
	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
