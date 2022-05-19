#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVzdelaniePodiel : public CriterionUJ<T> {

private:


public:

	CriterionUJVzdelaniePodiel() {};
	~CriterionUJVzdelaniePodiel() {};

	double evaluate(UzemnaJednotka* UJ, TYP_VZDELANIA typVzdelania) {
		double result = 0;

		int pocetVzdelanych = UJ->getVzdelanie()->getPocetVzdelanie(typVzdelania);
		int celkovyPocetObyv = UJ->getPocetObyvatelov();

		result = 100 / celkovyPocetObyv * pocetVzdelanych;

		return result;
	}

};