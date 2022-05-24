#pragma once

#include "CriterionVzdelaniePocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJVzdelaniePocet : public FilterInterval<UzemnaJednotka*, int> {

public:

	FUJVzdelaniePocet(int min, int max) : FilterInterval(new CriterionUJVzdelaniePocet(), min, max) {

	}

	virtual ~FUJVzdelaniePocet() = default;

};


