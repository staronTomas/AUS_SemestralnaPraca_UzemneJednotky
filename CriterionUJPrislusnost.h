#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJPrislusnost : public CriterionUJ<T> {

private:


public:

	CriterionUJPrislusnost() {};
	~CriterionUJPrislusnost() {};

	UZEMNA_JEDNOTKA evaluate(UzemnaJednotka* object, UzemnaJednotka* vyssiCelok) {
		if (object->getVyssiaUJRodic == vyssiCelok) {
			return true;
		}
		else {
			return false;
		}
	}

};