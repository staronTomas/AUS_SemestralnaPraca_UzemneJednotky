#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekovaSkupinaPocet : public CriterionUJ<int> {

public:

	int evaluate(UzemnaJednotka* object, EVS evs);

};

inline int CriterionUJVekovaSkupinaPocet::evaluate(UzemnaJednotka* object, EVS evs) {
	return object->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(evs);
}