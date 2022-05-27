#pragma once

#include "CriterionUJVekovaSkupinaPodiel.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_EVS.h"

template<typename O, typename ValueType>

class FUJVekovaSkupinaPodiel : public FilterInterval<UzemnaJednotka*, double> {

private:
	EVS typEvs_;
	int min_;
	int max_;


public:

	FUJVekovaSkupinaPodiel(EVS typEvs, double min, double max) : FilterInterval(new CriterionUJVekovaSkupinaPodiel(typEvs), min, max) {
		typEvs_ = typEvs;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVekovaSkupinaPodiel() = default;


	EVS getTypEvs() {
		return typEvs_;
	}

};