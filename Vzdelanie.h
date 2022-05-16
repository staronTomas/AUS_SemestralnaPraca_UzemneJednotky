#pragma once

#include <iostream>

using namespace std;

class Vzdelanie
{

	enum TYP_VZDELANIA {
		BEZ_UKONCENEHO_VZDELANIA, ZAKLADNE, UCNOVSKE, STREDNE, VYSSIE, VYSOKOSKOLSKE, BEZ_VZDELANIA, NEZISTENE
	};

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


	Vzdelanie() {};
	~Vzdelanie() {

		bezUkoncenehoVzdelaniaDeti_ = 0;
		zakladne_ = 0;
		ucnovske_ = 0;
		stredne_ = 0;
		vyssie_ = 0;
		vysokoskolske_ = 0;
		bezVzdelania_ = 0;
		nezistene_ = 0;
	};



	int getPocetVzdelanie(TYP_VZDELANIA typVzdelania) {
		switch (typVzdelania) {

			case BEZ_UKONCENEHO_VZDELANIA:
				return bezUkoncenehoVzdelaniaDeti_;
			case UCNOVSKE:
				return ucnovske_;
			case STREDNE:
				return stredne_;
			case VYSSIE:
				return vyssie_;
			case VYSOKOSKOLSKE:
				return vysokoskolske_;
			case BEZ_VZDELANIA:
				return bezVzdelania_;
			case NEZISTENE:
				return nezistene_;
		}
	}

	void setPocetVzdelanie(TYP_VZDELANIA typVzdelania, int pocet){
		switch (typVzdelania) {

		case BEZ_UKONCENEHO_VZDELANIA:
			bezUkoncenehoVzdelaniaDeti_ = pocet;
		case UCNOVSKE:
			ucnovske_ = pocet;
		case STREDNE:
			stredne_ = pocet;
		case VYSSIE:
			vyssie_ = pocet;
		case VYSOKOSKOLSKE:
			vysokoskolske_ = pocet;
		case BEZ_VZDELANIA:
			bezVzdelania_ = pocet;
		case NEZISTENE:
			nezistene_ = pocet;
		}
	}
}