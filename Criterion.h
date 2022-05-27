#pragma once


template<typename O, typename T>

// T - Navratova hodnota kriteria - ResultType

// O - UzemnaJednotka* - ObjectType

class Criterion {

public:

	virtual T evaluate(O o) = 0;

};

