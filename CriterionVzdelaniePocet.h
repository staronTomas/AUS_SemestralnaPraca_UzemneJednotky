#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVzdelaniePocet: public CriterionUJ<T> {

private:


public:

	CriterionUJVzdelaniePocet() {};
	~CriterionUJVzdelaniePocet() {};

	int evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania) {
		return object->getVzdelanie()->getPocetVzdelanie(typVzdelania);
	}

};