#pragma once

#include "CriterionUJ.h"


class CriterionUJNadradena : public CriterionUJ<UzemnaJednotka*> {
public:

	UzemnaJednotka* evaluate(UzemnaJednotka* object) override;

};

inline UzemnaJednotka* CriterionUJNadradena::evaluate(UzemnaJednotka* object) {
	return object->getVyssiaUJRodic();
}


