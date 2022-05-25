#pragma once

#include "CriterionVzdelaniePodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"

template<typename O, typename ValueType>

class FUJVzdelaniePodiel : public FilterInterval<UzemnaJednotka*, double> {

private:
	TYP_VZDELANIA typVzd_;
	int min_;
	int max_;


public:

	FUJVzdelaniePodiel(TYP_VZDELANIA typVzd, double min, double max) : FilterInterval(new CriterionUJVzdelaniePodiel(typVzd), min, max) {
		typVzd_ = typVzd;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVzdelaniePodiel() = default;


	TYP_VZDELANIA getTypVzdelania() {
		return typVzd_;
	}

};