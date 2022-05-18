#pragma once

#include "Criterion.h"

template<typename T, typename O>

class CriterionUJ : public Criterion<T, O>{

public:

	virtual T evaluate(O* o) const = 0;
	virtual ~Criterion() {};

};