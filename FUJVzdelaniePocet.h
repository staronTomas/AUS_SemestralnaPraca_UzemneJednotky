#pragma once

#include "CriterionVzdelaniePocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJVzdelaniePocet : public FilterInterval<UzemnaJednotka*, int, int> {

public:

	FUJVzdelaniePocet(int min, int max) : FilterInterval(new CriterionVzdelaniePocet(), min, max) {

	}

	virtual ~FUJVzdelaniePocet() = default;

};