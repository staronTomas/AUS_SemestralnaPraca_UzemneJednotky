#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJTyp : public CriterionUJ<T> {

private:



public:

	CriterionUJTyp() {};
	~CriterionUJTyp() {};

	UZEMNA_JEDNOTKA evaluate(UzemnaJednotka* object) {
		return object->getTypUzemnejJednotky();
	}



};