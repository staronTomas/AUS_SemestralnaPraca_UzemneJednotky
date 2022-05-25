#pragma once


template<typename O, typename T>

// T - Navratova hodnota kriteria

// O - UzemnaJednotka*

class Criterion {

public:

	virtual T evaluate(O o) = 0;

};

