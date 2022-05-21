#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekPodiel : public CriterionUJ<double> {

public:

	double evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek);

};

inline double CriterionUJVekPodiel::evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek) {
	int pocetLudiVPozadovanomVeku = object->getVekObyvatelov()->getPocetVek(pohlavie, vek);
	int pocetObyvatelov = object->getPocetObyvatelov();

	double result = 100.0 / pocetObyvatelov * static_cast<double>(pocetLudiVPozadovanomVeku);

	return result;
}
