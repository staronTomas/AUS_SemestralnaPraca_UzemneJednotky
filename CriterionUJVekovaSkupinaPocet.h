#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVekovaSkupinaPocet: public CriterionUJ<T> {

private:


public:

	CriterionUJVekovaSkupinaPocet() {};
	~CriterionUJVekovaSkupinaPocet() {};

	int evaluate(UzemnaJednotka* object, EVS evs) {
		return object->getVekObyvatelov()->getPocetEkoVekSkupinu(evs);
	}

};