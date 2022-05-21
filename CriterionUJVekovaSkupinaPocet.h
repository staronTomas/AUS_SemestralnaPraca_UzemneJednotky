#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"

class CriterionUJVekovaSkupinaPocet : public CriterionUJ<int> {

private:
	EVS typEvs_;

public:

	int evaluate(UzemnaJednotka* object);

	void setTypEvs(EVS evs);

};

inline int CriterionUJVekovaSkupinaPocet::evaluate(UzemnaJednotka* object) {
	return object->getVekObyvatelov()->getPocetEkoVekSkupinuCelkovo(typEvs_);
}

inline void CriterionUJVekovaSkupinaPocet::setTypEvs(EVS evs) {
	typEvs_ = evs;
}