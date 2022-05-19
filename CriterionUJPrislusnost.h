#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJPrislusnost : public CriterionUJ<T> {

private:


public:

	CriterionUJPrislusnost() {};
	~CriterionUJPrislusnost() {};

	UZEMNA_JEDNOTKA evaluate(UzemnaJednotka* UJ, UzemnaJednotka* vyssiCelok) {
		if (UJ->getVyssiaUJRodic == vyssiCelok) {
			return true;
		}
		else {
			return false;
		}
	}

};