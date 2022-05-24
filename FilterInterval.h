#pragma once

#include "FilterWithCriterion.h"

template<typename O, typename ValueType>

class FilterInterval : public FilterWithCriterion<O, ValueType> {

private:
	ValueType min_;
	ValueType max_;

public:

	FilterInterval(Criterion<O, ValueType>* criterion, ValueType min, ValueType max) : FilterWithCriterion<O, ValueType>(criterion) {
		min_ = min;
		max_ = max;
	}

	virtual ~FilterInterval() = default;

	bool passFilter(ValueType hodnota) {
		if (hodnota >= min_ && hodnota <= max_)
		{
			return true;
		}
		else {
			return false;
		}
	}


	void setMin(ValueType min) {
		min_ = min;
	}


	void setMax(ValueType max) {
		max_ = max;
	}

};