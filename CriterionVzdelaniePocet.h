#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVzdelaniePocet : public CriterionUJ<int> {

public:

	int evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania);

};

inline int CriterionUJVzdelaniePocet::evaluate(UzemnaJednotka* object, TYP_VZDELANIA typVzdelania) {
	return object->getVzdelanie()->getPocetVzdelanie(typVzdelania);
}