#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVekovaSkupinaPodiel : public CriterionUJ<T> {

private:


public:

	CriterionUJVekovaSkupinaPodiel() {};
	~CriterionUJVekovaSkupinaPodiel() {};

	double evaluate(UzemnaJednotka* object, EVS evs) {
		double result = 0;

		int pocetObyvatelov = object->getPocetObyvatelov();
		int pocetEvsVUJ = object->getVekObyvatelov()->getPocetEkoVekSkupinu(evs);

		result = 100 / pocetObyvatelov * pocetEvsVUJ;

		return result;
	}

};