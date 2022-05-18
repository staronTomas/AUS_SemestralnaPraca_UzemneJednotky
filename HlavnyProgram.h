#pragma once

#include <iostream>

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
		
		LinkedList<std::string>* obceArrayList = reader_->nacitajObce("../Data_bez_diakritiky/obce.csv");  // Obce mi nacita:   NazovUJ-KodUJ

		LinkedList<std::string>* okresyArrayList = reader_->nacitajOkresy("../Data_bez_diakritiky/okresy.csv");  // Obce mi nacita:   NazovUJ-KodUJ

		LinkedList<std::string>* krajeArrayList = reader_->nacitajKraje("../Data_bez_diakritiky/kraje.csv");  // Obce mi nacita:   NazovUJ-KodUJ

		SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieZoSuborov = reader_->nacitajVzdelanie("../Data_bez_diakritiky/vzdelanie.csv");

		for (const std::string& item : *krajeArrayList) {

			std::cout << item << std::endl;
		}


		Vzdelanie* x = vzdelanieZoSuborov->find("SK0102529320");

		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::ZAKLADNE) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::UCNOVSKE) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::STREDNE) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::VYSOKOSKOLSKE) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::VYSOKOSKOLSKE) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::BEZ_VZDELANIA) << std::endl;
		std::cout << x->getPocetVzdelanie(TYP_VZDELANIA::NEZISTENE) << std::endl;

	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
