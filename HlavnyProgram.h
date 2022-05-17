#pragma once

#include <iostream>

#include "enum_UzemnaJednotka.h"
#include "enum_VyssiCelok.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"
#include "enum_EVS.h"

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
		reader_->readFromCsv("../Data/kraje.csv");
		std::cout << "ahoj";
	}


	void nacitajVsetkyData() {

	}




	UzemnaJednotka* getSlovensko() {
		return slovensko_;
	}

};
