#pragma once
#include "Criterion.h"

#include "structures/table/sorted_sequence_table.h"

template<typename O>

class Filter {


public:
	
	virtual bool pass(const O o) = 0;
	virtual ~Filter() = default;

};


