#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekPocet : public CriterionUJ<int> {

public:

	int evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek);

};

inline int CriterionUJVekPocet::evaluate(UzemnaJednotka* object, POHLAVIE pohlavie, int vek) {
	return object->getVekObyvatelov()->getPocetVek(pohlavie, vek);
}