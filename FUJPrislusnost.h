#pragma once

#include "CriterionUJPrislusnost.h"

#include "FilterValue.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"

template<typename O, typename ValueType>

class FUJPrislusnost : public FilterValue<UzemnaJednotka*, bool> {

public:

	FUJPrislusnost(UzemnaJednotka* prislusnost, bool prislucha) : FilterValue(new CriterionUJPrislusnost(prislusnost), prislucha) {

	}

	virtual ~FUJPrislusnost() = default;

};