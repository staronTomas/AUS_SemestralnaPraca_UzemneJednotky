#pragma once

#include <iostream>

#include "enum_TypVzdelania.h"


class Vzdelanie {


private:



	int bezUkoncenehoVzdelaniaDeti_;
	int zakladne_;
	int ucnovske_;
	int stredne_;
	int vyssie_;
	int vysokoskolske_;
	int bezVzdelania_;
	int nezistene_;

public:

	Vzdelanie() {
		bezUkoncenehoVzdelaniaDeti_ = 0;
		zakladne_ = 0;
		ucnovske_ = 0;
		stredne_ = 0;
		vyssie_ = 0;
		vysokoskolske_ = 0;
		bezVzdelania_ = 0;
		nezistene_ = 0;
	};

	~Vzdelanie() {};

	int getPocetVzdelanie(TYP_VZDELANIA vzd) {

		switch (vzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			return bezUkoncenehoVzdelaniaDeti_;
		case TYP_VZDELANIA::ZAKLADNE:
			return zakladne_;
		case TYP_VZDELANIA::UCNOVSKE:
			return ucnovske_;
		case TYP_VZDELANIA::STREDNE:
			return stredne_;
		case TYP_VZDELANIA::VYSSIE:
			return vyssie_;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			return vysokoskolske_;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			return bezVzdelania_;
		case TYP_VZDELANIA::NEZISTENE:
			return nezistene_;
		default:
			return -1;
		}
	}




	void setPocetVzdelanie(TYP_VZDELANIA vzd, int pocet) {

		switch (vzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			bezUkoncenehoVzdelaniaDeti_ = pocet;
		case TYP_VZDELANIA::ZAKLADNE:
			zakladne_ = pocet;
		case TYP_VZDELANIA::UCNOVSKE:
			ucnovske_ = pocet;
		case TYP_VZDELANIA::STREDNE:
			stredne_ = pocet;
		case TYP_VZDELANIA::VYSSIE:
			vyssie_ = pocet;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			vysokoskolske_ = pocet;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			bezVzdelania_ = pocet;
		case TYP_VZDELANIA::NEZISTENE:
			nezistene_ = pocet;

		default:
			;
		}
	}



	void navysPocetVzdelanie(TYP_VZDELANIA vzd, int pocet) {

		switch (vzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			bezUkoncenehoVzdelaniaDeti_ += pocet;
		case TYP_VZDELANIA::ZAKLADNE:
			zakladne_ += pocet;
		case TYP_VZDELANIA::UCNOVSKE:
			ucnovske_ += pocet;
		case TYP_VZDELANIA::STREDNE:
			stredne_ += pocet;
		case TYP_VZDELANIA::VYSSIE:
			vyssie_ += pocet;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			vysokoskolske_ += pocet;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			bezVzdelania_ += pocet;
		case TYP_VZDELANIA::NEZISTENE:
			nezistene_ += pocet;

		default:
			;
		}
	}
};