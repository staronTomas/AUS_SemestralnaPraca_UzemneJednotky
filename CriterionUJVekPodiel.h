#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVekPodiel : public CriterionUJ<T> {

private:


public:

	CriterionUJVekPodiel() {};
	~CriterionUJVekPodiel() {};

	double evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek) {
		int pocetLudiVPozadovanomVeku = object->getVekObyvatelov()->getPocetVek(pohlavie, vek);
		int pocetObyvatelov = object->getPocetObyvatelov();

		int result = 100 / pocetObyvatelov * pocetLudiVPozadovanomVeku;

		return result;	
	}

};