#pragma once

#include <iostream>

using namespace std;


class Vzdelanie {


private:

	enum class TYP_VZDELANIA {
		BEZ_UKONCENEHO_VZDELANIA_DETI, ZAKLADNE, UCNOVSKE, STREDNE, VYSSIE, VYSOKOSKOLSKE, BEZ_VZDELANIA, NEZISTENE
	};

	int bezUkoncenehoVzdelaniaDeti_;
	int zakladne_;
	int ucnovske_;
	int stredne_;
	int vyssie_;
	int vysokoskolske_;
	int bezVzdelania_;
	int nezistene_;

public:

	Vzdelanie() {};
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
};