#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"
#include "enum_EVS.h"


class CriterionUJVekovaSkupinaPocet : public CriterionUJ<int> {

private:
	EVS typEvs_;

public:

	CriterionUJVekovaSkupinaPocet(EVS typEvs) {
		typEvs_ = typEvs;
	};

	int evaluate(UzemnaJednotka* object);

	void setTypEvs(EVS evs);

};

inline int CriterionUJVekovaSkupinaPocet::evaluate(UzemnaJednotka* object) {
	return object->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs_);
}

inline void CriterionUJVekovaSkupinaPocet::setTypEvs(EVS evs) {
	typEvs_ = evs;
}