#pragma once

#include "CriterionVzdelaniePocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"


template<typename O, typename ValueType>

class FUJVzdelaniePocet : public FilterInterval<UzemnaJednotka*, int> {

private:
	TYP_VZDELANIA typVzd_;
	int min_;
	int max_;

public:

	FUJVzdelaniePocet(TYP_VZDELANIA typVzd, int min, int max) : FilterInterval(new CriterionUJVzdelaniePocet(typVzd), min, max) {
		typVzd_ = typVzd;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVzdelaniePocet() = default;



	TYP_VZDELANIA getTypVzdelania() {
		return typVzd_;
	}

};