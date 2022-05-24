#pragma once

#include "Filter.h"

#include "structures/list/array_list.h"

template<typename O>

class CompositeFilter : public Filter<O> {

protected:
	structures::ArrayList<Filter<O>*>* filters_; 

public:
	CompositeFilter() {
		filters_ = new structures::ArrayList<Filter<O>*>();
	}

	~CompositeFilter() {
		delete filters_;
	}

	void registerFilter(Filter<O>* filter) {
		filters_->add(filter);
	}


	


};