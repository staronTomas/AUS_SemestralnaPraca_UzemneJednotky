#pragma once

#include "CriterionVzdelaniePocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"


template<typename O, typename ValueType>

class FUJVzdelaniePocet : public FilterInterval<UzemnaJednotka*, int> {

public:

	FUJVzdelaniePocet(TYP_VZDELANIA vzd, int min, int max) : FilterInterval(new CriterionUJVzdelaniePocet(vzd), min, max) {

	}

	virtual ~FUJVzdelaniePocet() = default;

};