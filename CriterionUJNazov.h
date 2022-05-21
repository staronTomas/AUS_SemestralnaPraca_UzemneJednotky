#pragma once

#include "CriterionUJ.h"
#include "UzemnaJednotka.h"


class CriterionUJNazov : public CriterionUJ<std::string> {

public:

	std::string evaluate(UzemnaJednotka* object) override;

};


inline std::string CriterionUJNazov::evaluate(UzemnaJednotka* object) {
	return object->getNazov();
}



