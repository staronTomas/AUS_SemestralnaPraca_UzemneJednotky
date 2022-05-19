#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVzdelaniePodiel : public CriterionUJ<T> {

private:


public:

	CriterionUJVzdelaniePodiel() {};
	~CriterionUJVzdelaniePodiel() {};

	double evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania) {
		double result = 0;

		int pocetVzdelanych = object->getVzdelanie()->getPocetVzdelanie(typVzdelania);
		int celkovyPocetObyv = object->getPocetObyvatelov();

		result = 100 / celkovyPocetObyv * pocetVzdelanych;

		return result;
	}

};