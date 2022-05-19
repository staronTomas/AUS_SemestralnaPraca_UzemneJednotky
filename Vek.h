#pragma once

#include <iostream>
#include <string>

#include "structures/array/array.h"

#include "enum_Pohlavie.h"


class Vek {


private:

	structures::Array<int>* pocetVekMuzi_;
	structures::Array<int>* pocetVekZeny_;


public:

	Vek() {
		pocetVekMuzi_ = new structures::Array<int>(101);
		pocetVekZeny_ = new structures::Array<int>(101);
	}


	

	void navysPocetVek(POHLAVIE pohlavie, int pocetRokov, int pocet) {
		if (pohlavie == POHLAVIE::MUZ)
		{
			if (pocetRokov < 100) {
				pocetVekMuzi_->at(pocetRokov) += pocet;
			}
			else {
				pocetVekMuzi_->at(100) += pocet;
			}

		}
		else {
			if (pocetRokov < 100) {
				pocetVekZeny_->at(pocetRokov) += pocet;
			}
			else {
				pocetVekZeny_->at(100) += pocet;
			}
		}
	}


	
	//gettery

	int getPocetVek(POHLAVIE pohlavie, int pocetRokov) {
		if (pohlavie == POHLAVIE::MUZ)
		{
			if (pocetRokov < 100) {
				return pocetVekMuzi_->at(pocetRokov);
			}
			else {
				return pocetVekMuzi_->at(100);
			}

		}
		else {
			if (pocetRokov < 100) {
				return pocetVekZeny_->at(pocetRokov);
			}
			else {
				return pocetVekZeny_->at(100);
			}
		}
	}
	
	structures::Array<int>* getArrayVekMuzi() {
		return pocetVekMuzi_;
	}

	structures::Array<int>* getArrayVekZeny() {
		return pocetVekZeny_;
	}

	//settery

	void setArrayVekMuzi(structures::Array<int>* arrayVeky) {
		pocetVekMuzi_ = arrayVeky;
	}

	void setArrayVekZeny(structures::Array<int>* arrayVeky) {
		pocetVekZeny_ = arrayVeky;
	}

	
};