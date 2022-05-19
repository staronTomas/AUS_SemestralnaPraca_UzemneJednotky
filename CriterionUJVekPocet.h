#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJVekPocet: public CriterionUJ<T> {

private:


public:

	CriterionUJVekPocet() {};
	~CriterionUJVekPocet() {};

	int evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek) {
		return object->getVekObyvatelov()->getPocetVek(pohlavie, vek);
	}

};