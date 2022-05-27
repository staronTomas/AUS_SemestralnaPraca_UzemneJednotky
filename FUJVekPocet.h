#pragma once

#include "CriterionVzdelaniePocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"


template<typename O, typename ValueType>

class FUJVekPocet : public FilterInterval<UzemnaJednotka*, int> {

private:
	POHLAVIE typPohlavia_;
	int min_;
	int max_;

public:

	FUJVekPocet(POHLAVIE typPohlavia,  int min, int max) : FilterInterval(new CriterionUJVekPocet(typPohlavia), min, max) {
		typPohlavia_ = typPohlavia;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVekPocet() = default;



	POHLAVIE getTypPohlavia() {
		return typPohlavia_;
	}

};