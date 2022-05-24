#pragma once

#include "CompositeFilter.h"

template<typename O>

class FilterAnd : public CompositeFilter<O> {

bool pass(O& object) override;



};

template<typename O>
inline bool FilterAnd<O>::pass(O& object) {


	for (Filter<O>* filter : *filters_)
	{
		if (!filter->pass(object)) {
			return false;
		}
	}
	return true;
}