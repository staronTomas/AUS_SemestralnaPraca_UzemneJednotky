#pragma once

#include "CriterionUJ.h"

template<typename T>

class CriterionUJNadradena : public CriterionUJ<T> {

private:


public:

	CriterionUJNadradena() {};
	~CriterionUJNadradena() {};

	UzemnaJednotka* evaluate(UzemnaJednotka* object) {
		return object->getVyssiaUJRodic();
	}

};