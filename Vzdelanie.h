#pragma once

#include <iostream>

#include "enum_TypVzdelania.h"
#include "structures/heap_monitor.h"


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
			break;
		case TYP_VZDELANIA::ZAKLADNE:
			return zakladne_;
			break;
		case TYP_VZDELANIA::UCNOVSKE:
			return ucnovske_;
			break;
		case TYP_VZDELANIA::STREDNE:
			return stredne_;
			break;
		case TYP_VZDELANIA::VYSSIE:
			return vyssie_;
			break;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			return vysokoskolske_;
			break;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			return bezVzdelania_;
			break;
		case TYP_VZDELANIA::NEZISTENE:
			return nezistene_;
			break;
		default:
			return -1;
			break;
		}
	}

	void navysCelkovyPocetVzdelania(Vzdelanie* vzd) {

		bezUkoncenehoVzdelaniaDeti_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI);
		zakladne_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::ZAKLADNE);
		ucnovske_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::UCNOVSKE);
		stredne_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::STREDNE);
		vyssie_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::VYSSIE);
		vysokoskolske_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::VYSOKOSKOLSKE);
		bezVzdelania_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::BEZ_VZDELANIA);
		nezistene_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::NEZISTENE);
	}



	void setPocetVzdelanie(TYP_VZDELANIA vzd, int pocet) {

		switch (vzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			bezUkoncenehoVzdelaniaDeti_ = pocet;
			break;
		case TYP_VZDELANIA::ZAKLADNE:
			zakladne_ = pocet;
			break;
		case TYP_VZDELANIA::UCNOVSKE:
			ucnovske_ = pocet;
			break;
		case TYP_VZDELANIA::STREDNE:
			stredne_ = pocet;
			break;
		case TYP_VZDELANIA::VYSSIE:
			vyssie_ = pocet;
			break;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			vysokoskolske_ = pocet;
			break;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			bezVzdelania_ = pocet;
			break;
		case TYP_VZDELANIA::NEZISTENE:
			nezistene_ = pocet;
			break;
		default:
			break;;
		}
	}



	void navysPocetVzdelanie(TYP_VZDELANIA vzd, int pocet) {

		switch (vzd) {

		case TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI:
			bezUkoncenehoVzdelaniaDeti_ += pocet;
			break;
		case TYP_VZDELANIA::ZAKLADNE:
			zakladne_ += pocet;
			break;
		case TYP_VZDELANIA::UCNOVSKE:
			ucnovske_ += pocet;
			break;
		case TYP_VZDELANIA::STREDNE:
			stredne_ += pocet;
			break;
		case TYP_VZDELANIA::VYSSIE:
			vyssie_ += pocet;
			break;
		case TYP_VZDELANIA::VYSOKOSKOLSKE:
			vysokoskolske_ += pocet;
			break;
		case TYP_VZDELANIA::BEZ_VZDELANIA:
			bezVzdelania_ += pocet;
			break;
		case TYP_VZDELANIA::NEZISTENE:
			nezistene_ += pocet;
			break;

		default:
			break;
		}
	}



	int vratCelkovyPocetVzdelaniaVsetkych() {
		return bezUkoncenehoVzdelaniaDeti_ + zakladne_ + ucnovske_ + stredne_ + vyssie_ + vysokoskolske_ + bezVzdelania_ + nezistene_;
	}
};