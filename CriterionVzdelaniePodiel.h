#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVzdelaniePodiel : public CriterionUJ<double> {

public:

	double evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania);

};

inline double CriterionUJVzdelaniePodiel::evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania) {
	double result = 0;

	int pocetVzdelanych = object->getVzdelanie()->getPocetVzdelanie(typVzdelania);
	int celkovyPocetObyv = object->getPocetObyvatelov();

	result = 100.0 / celkovyPocetObyv * static_cast<double>(pocetVzdelanych);

	return result;
}