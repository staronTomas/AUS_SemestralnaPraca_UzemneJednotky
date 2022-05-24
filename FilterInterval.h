#pragma once

#include "Filter.h"

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
		if (value >= min_ && value <= max_)
		{
			return true;
		}
		else {
			return false;
		}
	}


	void setMin(T min) {
		min_ = max_;
	}


	void setMax(T max) {
		max_ = max;
	}

};