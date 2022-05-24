#pragma once

#include "CriterionUJTyp.h"

#include "FilterValue.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJTyp : public FilterValue<UzemnaJednotka*, UZEMNA_JEDNOTKA> {

public:

	FUJTyp(UZEMNA_JEDNOTKA typUJ) : FilterValue(new CriterionUJTyp(), typUJ) {

	}

	virtual ~FUJTyp() = default;

};