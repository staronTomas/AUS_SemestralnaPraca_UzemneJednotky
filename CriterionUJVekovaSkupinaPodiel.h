#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekovaSkupinaPodiel : public CriterionUJ<double> {

private:
	EVS typEvs_;

public:

	CriterionUJVekovaSkupinaPodiel(EVS typEvs) {
		typEvs_ = typEvs;
	};

	double evaluate(UzemnaJednotka* object);

	void setTypEvs(EVS evs);
};

inline double CriterionUJVekovaSkupinaPodiel::evaluate(UzemnaJednotka* object) {
	double result = 0;

	int pocetObyvatelov = object->getPocetObyvatelov();
	int pocetEvsVUJ = object->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs_);

	result = 100.0 / pocetObyvatelov * static_cast<double>(pocetEvsVUJ);

	return result;
}


inline void CriterionUJVekovaSkupinaPodiel::setTypEvs(EVS evs) {
	typEvs_ = evs;
}