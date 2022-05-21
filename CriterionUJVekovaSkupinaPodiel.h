#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekovaSkupinaPodiel : public CriterionUJ<double> {

public:

	double evaluate(UzemnaJednotka* object, EVS evs);

};

inline double CriterionUJVekovaSkupinaPodiel::evaluate(UzemnaJednotka* object, EVS evs) {
	double result = 0;

	int pocetObyvatelov = object->getPocetObyvatelov();
	int pocetEvsVUJ = object->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(evs);

	result = 100.0 / pocetObyvatelov * static_cast<double>(pocetEvsVUJ);

	return result;
}