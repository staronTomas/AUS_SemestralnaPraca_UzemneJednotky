#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJNazov : public CriterionUJ<T> {

private:



public:

	CriterionUJNazov() {};
	~CriterionUJNazov() {};

	std::string evaluate(UzemnaJednotka* UJ) {
		return UJ->getNazov();
	}



};