#pragma once

template<typename T, typename O>

class Criterion {

public:

	virtual T evaluate(O* o) const = 0;
	virtual ~Criterion() {};

};