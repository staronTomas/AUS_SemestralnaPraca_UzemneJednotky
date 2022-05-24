#pragma once
#include "Criterion.h"

#include "Filter.h"

template<typename O, typename ValueType>

class FilterWithCriterion : Filter<O>{

private:

	Criterion<O, ValueType>* kriterium_;

public:

	FilterWithCriterion(Criterion<O, ValueType> kriterium) {
		kriterium_ = kriterium;
	}

	~FilterWithCriterion() {
		delete kriterium_;
	}


	bool pass(const O object) override {
		return passFilter(kriterium_->evaluate(object));
	}

protected:
	virtual bool passFilter(ValueType) = 0;

};