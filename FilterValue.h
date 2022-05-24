#pragma once

#include "FilterWithCriterion.h"

template<typename O, typename ValueType>

class FilterValue : public FilterWithCriterion<O, ValueType> {

private:
	ValueType hodnota_;

public:

	FilterValue(Criterion<O, ValueType>* criterion, ValueType hodnota) : FilterWithCriterion<O, ValueType>(criterion) {
		hodnota_ = hodnota;
	}

	virtual ~FilterValue() = default;

	bool passFilter(ValueType hodnota) {
		if (hodnota == hodnota_)
		{
			return true;
		}
		else {
			return false;
		}
	}


	void setHodnota(ValueType hodnota) {
		hodnota_ = hodnota;
	}



};