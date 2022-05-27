#pragma once

#include "CriterionUJVekPodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"
#include "enum_Pohlavie.h"

template<typename O, typename ValueType>

class FUJVekPodiel : public FilterInterval<UzemnaJednotka*, double> {

private:
	POHLAVIE typPohlavia_;
	int min_;
	int max_;


public:

	FUJVekPodiel(POHLAVIE typPohlavia, double min, double max) : FilterInterval(new CriterionUJVekPodiel(typPohlavia), min, max) {
		typPohlavia_ = typPohlavia;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVekPodiel() = default;


	POHLAVIE getTypPohlavia() {
		return typPohlavia_;
	}

};