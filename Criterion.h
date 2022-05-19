#pragma once

template<typename O, typename T>

class Criterion {

public:

	virtual T evaluate(O* o) const = 0;
	virtual ~Criterion() {};

};