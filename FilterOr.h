#pragma once

#include "CompositeFilter.h"

template<typename O>

class FilterOr : public CompositeFilter<O> {

	bool pass(O& object) override;



};

template<typename O>
inline bool FilterOr<O>::pass(O& object) {


	bool vysledok = false;

	for (Filter<O>* filter : *filters_)
	{
		if (filter->pass(object)) {
			vysledok = true;
		}
	}
	return vysledok;
}