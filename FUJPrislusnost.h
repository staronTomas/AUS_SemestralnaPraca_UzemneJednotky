#pragma once

#include "CriterionUJPrislusnost.h"

#include "FilterValue.h"
#include "UzemnaJednotka.h"
#include "enum_UzemnaJednotka.h"


template<typename O, typename ValueType>

class FUJPrislusnost : public FilterValue<UzemnaJednotka*, UzemnaJednotka*> {

public:

	FUJPrislusnost(UzemnaJednotka* prislusnost) : FilterValue(new CriterionUJPrislusnost(), prislusnost) {

	}

	virtual ~FUJPrislusnost() = default;

};