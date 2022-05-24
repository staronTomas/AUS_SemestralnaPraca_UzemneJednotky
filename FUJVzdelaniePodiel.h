#pragma once

#include "CriterionVzdelaniePodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka*, double> {

public:

	FUJVzdelaniePodiel(double min, double max) : FilterInterval(new CriterionUJVzdelaniePodiel(), min, max) {

	}

	virtual ~FUJVzdelaniePodiel() = default;

};