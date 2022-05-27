#pragma once

#include "CriterionUJVekovaSkupinaPocet.h"

#include "FilterInterval.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"
#include "enum_EVS.h"


template<typename O, typename ValueType>

class FUJVekovaSkupinaPocet : public FilterInterval<UzemnaJednotka*, int> {

private:
	EVS typEvs_;
	int min_;
	int max_;

public:

	FUJVekovaSkupinaPocet(EVS typEvs, int min, int max) : FilterInterval(new CriterionUJVekovaSkupinaPocet(typEvs), min, max) {
		typEvs_ = typEvs;
		min_ = min;
		max_ = max;
	}

	virtual ~FUJVekovaSkupinaPocet() = default;



	EVS getTypEvs() {
		return typEvs_;
	}

};