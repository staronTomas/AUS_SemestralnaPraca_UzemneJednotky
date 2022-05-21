#pragma once

#include "CriterionUJ.h"

class CriterionUJNazov : public CriterionUJ<std::string> {

public:

	std::string evaluate(UzemnaJednotka* object);

};


inline std::string CriterionUJNazov::evaluate(UzemnaJednotka* object) {
	return object->getNazov();
}



