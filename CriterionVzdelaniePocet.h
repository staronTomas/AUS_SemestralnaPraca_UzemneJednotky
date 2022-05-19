#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVzdelaniePocet: public CriterionUJ<T> {

private:


public:

	CriterionUJVzdelaniePocet() {};
	~CriterionUJVzdelaniePocet() {};

	int evaluate(UzemnaJednotka* UJ, TYP_VZDELANIA typVzdelania) {
		return UJ->getVzdelanie()->getPocetVzdelanie(typVzdelania);
	}

};