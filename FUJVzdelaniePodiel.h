#pragma once

#include "CriterionVzdelaniePodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka*, int, int> {

public:

	FUJVzdelaniePodiel(int min, int max) : FilterInterval(new CriterionVzdelaniePodiel(), min, max) {

	}

	virtual ~FUJVzdelaniePodiel() = default;

};