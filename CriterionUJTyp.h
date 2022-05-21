#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJTyp : public CriterionUJ<UZEMNA_JEDNOTKA> {

public:

	UZEMNA_JEDNOTKA evaluate(UzemnaJednotka* object);

};

inline UZEMNA_JEDNOTKA CriterionUJTyp::evaluate(UzemnaJednotka* object) {
	return object->getTypUzemnejJednotky();
}