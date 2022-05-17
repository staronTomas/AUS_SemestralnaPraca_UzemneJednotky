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


		for (const std::string& item : *obceArrayList) {

			std::cout << item << std::endl;
		}

		for (const std::string& item : *okresyArrayList) {

			std::cout << item << std::endl;
		}

	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
