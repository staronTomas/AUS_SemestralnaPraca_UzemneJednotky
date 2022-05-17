#pragma once

#include <iostream>

#include "UzemnaJednotka.h"



enum class UZEMNA_JEDNOTKA {
	STAT, KRAJ, OKRES, OBEC
};

enum class TYP_VZDELANIA {
	BEZ_UKONCENEHO_VZDELANIA, ZAKLADNE, UCNOVSKE, STREDNE, VYSSIE, VYSOKOSKOLSKE, BEZ_VZDELANIA, NEZISTENE
};

class HlavnyProgam {
	
	

	

private:

	UzemnaJednotka* slovensko_;


public:

	HlavnyProgam() {
		slovensko_ = new UzemnaJednotka("Slovensko", UZEMNA_JEDNOTKA::STAT, "SK", nullptr);
	}

	~HlavnyProgam() {

	}


	void spustiProgram() {

	}


	void nacitajVsetkyData() {

	}

};
