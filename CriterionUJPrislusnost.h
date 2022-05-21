#pragma once

#include "CriterionUJ.h"


class CriterionUJPrislusnost : public CriterionUJ<bool> {

public:

	bool evaluate(UzemnaJednotka* object, UzemnaJednotka* vyssiCelok);

};


inline bool CriterionUJPrislusnost::evaluate(UzemnaJednotka* object, UzemnaJednotka* vyssiCelok) {
	if (object->getVyssiaUJRodic() == vyssiCelok) {
		return true;
	}
	else {
		return false;
	}
}