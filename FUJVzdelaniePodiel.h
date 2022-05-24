#pragma once

#include "CriterionVzdelaniePodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"

template<typename O, typename ValueType>

class FUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka*, double> {

public:

	FUJVzdelaniePodiel(TYP_VZDELANIA typVzd, double min, double max) : FilterInterval(new CriterionUJVzdelaniePodiel(typVzd), min, max) {

	}

	virtual ~FUJVzdelaniePodiel() = default;

};