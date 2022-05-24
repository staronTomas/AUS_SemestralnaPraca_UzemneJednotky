#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVzdelaniePodiel : public CriterionUJ<double> {


private:
	TYP_VZDELANIA typVzdelania_;

public:

	CriterionUJVzdelaniePodiel (TYP_VZDELANIA vzdelanie) {
		typVzdelania_ = vzdelanie;
	};

	double evaluate(UzemnaJednotka* object);

	void setTypVzdelania(TYP_VZDELANIA typVzdelania);

};

inline double CriterionUJVzdelaniePodiel::evaluate(UzemnaJednotka* object) {
	double result = 0;

	int pocetVzdelanych = object->getVzdelanie()->getPocetVzdelanie(typVzdelania_);
	int celkovyPocetObyv = object->getPocetObyvatelov();

	result = 100.0 / celkovyPocetObyv * static_cast<double>(pocetVzdelanych);

	return result;
}

inline void CriterionUJVzdelaniePodiel::setTypVzdelania(TYP_VZDELANIA typVzdelania) {
	typVzdelania_ = typVzdelania;
}