#pragma once

#include <iostream>
#include <string>

#include "structures/list/linked_list.h"

#include "enum_Pohlavie.h"
#include "enum_EVS.h"


class Vek {


private:

	structures::ArrayList<int>* pocetVekMuzi_;
	structures::ArrayList<int>* pocetVekZeny_;
	structures::ArrayList<int>* ekoVekSkupinyMuzi_;
	structures::ArrayList<int>* ekoVekSkupinyZeny_;


public:

	Vek() {
		pocetVekMuzi_ = new structures::ArrayList<int>;
		pocetVekZeny_ = new structures::ArrayList<int>;
		for (int i = 0; i < 101; i++)
		{
			pocetVekMuzi_->add(0);
			pocetVekZeny_->add(0);
		}
		ekoVekSkupinyMuzi_ = new structures::ArrayList<int>;
		ekoVekSkupinyZeny_ = new structures::ArrayList<int>;
		for (int i = 0; i < 3; i++)
		{
			ekoVekSkupinyMuzi_->add(0);
			ekoVekSkupinyZeny_->add(0);
		}
	}

	~Vek() {
		delete pocetVekMuzi_;
		delete pocetVekZeny_;
		delete ekoVekSkupinyMuzi_;
		delete ekoVekSkupinyZeny_;
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


	void navysPocetVekCelkovo(Vek* vek) {
		for (int i = 0; i < 101; i++)
		{
			pocetVekMuzi_->at(i) += vek->getArrayVekMuzi()->at(i);
			pocetVekZeny_->at(i) += vek->getArrayVekZeny()->at(i);
		}
	}

	void navysPocetEvsSkupin(Vek* vek) {

		//PredProduktivni
		for (int i = 0; i < 15; i++)
		{
			ekoVekSkupinyMuzi_->at(0) += vek->getArrayVekMuzi()->at(i);
			ekoVekSkupinyZeny_->at(0) += vek->getArrayVekZeny()->at(i);
		}

		//Produktivni
		for (int i = 15; i < 65; i++)
		{
			ekoVekSkupinyMuzi_->at(1) += vek->getArrayVekMuzi()->at(i);
			ekoVekSkupinyZeny_->at(1) += vek->getArrayVekZeny()->at(i);
		}

		//Poproduktivni
		for (int i = 65; i < 101; i++)
		{
			ekoVekSkupinyMuzi_->at(2) += vek->getArrayVekMuzi()->at(i);
			ekoVekSkupinyZeny_->at(2) += vek->getArrayVekZeny()->at(i);
		}
	}




	void navysEkoVekSkupinuZeny(EVS evs, int pocet) {
		switch (evs) {

		case EVS::PREDPRODUKTIVNI:
			ekoVekSkupinyZeny_->at(0) += pocet;
			break;
		case EVS::PRODUKTIVNI:
			ekoVekSkupinyZeny_->at(1) += pocet;
			break;
		case EVS::POPRODUKTIVNY:
			ekoVekSkupinyZeny_->at(2) += pocet;
			break;
		default:
			break;
		}
	}

	void navysEkoVekSkupinuMuzi(EVS evs, int pocet) {
		switch (evs) {

		case EVS::PREDPRODUKTIVNI:
			ekoVekSkupinyMuzi_->at(0) += pocet;
			break;
		case EVS::PRODUKTIVNI:
			ekoVekSkupinyMuzi_->at(1) += pocet;
			break;
		case EVS::POPRODUKTIVNY:
			ekoVekSkupinyMuzi_->at(2) += pocet;
			break;
		default:
			break;
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
	
	structures::ArrayList<int>* getArrayVekMuzi() {
		return pocetVekMuzi_;
	}

	structures::ArrayList<int>* getArrayVekZeny() {
		return pocetVekZeny_;
	}


	int getPocetEkoVekSkupinuZeny(EVS evs) {
		switch (evs) {

		case EVS::PREDPRODUKTIVNI:
			return ekoVekSkupinyZeny_->at(0);
			break;
		case EVS::PRODUKTIVNI:
			return ekoVekSkupinyZeny_->at(1);
			break;
		case EVS::POPRODUKTIVNY:
			return ekoVekSkupinyZeny_->at(2);
			break;
		default:
			break;
		}
	}

	int getPocetEkoVekSkupinuMuzi(EVS evs) {
		switch (evs) {

		case EVS::PREDPRODUKTIVNI:
			return ekoVekSkupinyMuzi_->at(0);
			break;
		case EVS::PRODUKTIVNI:
			return ekoVekSkupinyMuzi_->at(1);
			break;
		case EVS::POPRODUKTIVNY:
			return ekoVekSkupinyMuzi_->at(2);
			break;
		default:
			break;
		}
	}


	int getPocetEkoVekSkupinuCelkovo(EVS evs) {
		switch (evs) {

		case EVS::PREDPRODUKTIVNI:
			return ekoVekSkupinyMuzi_->at(0) + ekoVekSkupinyZeny_->at(0);
			break;
		case EVS::PRODUKTIVNI:
			return ekoVekSkupinyMuzi_->at(1) + ekoVekSkupinyZeny_->at(1);
			break;
		case EVS::POPRODUKTIVNY:
			return ekoVekSkupinyMuzi_->at(2) + ekoVekSkupinyZeny_->at(2);
			break;
		default:
			break;
		}
	}


	//settery

	void setArrayVekMuzi(structures::ArrayList<int>* arrayVeky) {
		pocetVekMuzi_ = arrayVeky;
	}

	void setArrayVekZeny(structures::ArrayList<int>* arrayVeky) {
		pocetVekZeny_ = arrayVeky;
	}



	
};