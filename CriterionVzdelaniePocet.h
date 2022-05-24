#pragma once

#include "CriterionUJ.h"


class CriterionUJVzdelaniePocet : public CriterionUJ<int> {

private:
	TYP_VZDELANIA typVzdelania_;

public:

	CriterionUJVzdelaniePocet(TYP_VZDELANIA vzdelanie) {
		typVzdelania_ = vzdelanie;
	};

	int evaluate(UzemnaJednotka* object);

	void setTypVzdelania(TYP_VZDELANIA typVzdelania);
};

inline int CriterionUJVzdelaniePocet::evaluate(UzemnaJednotka* object) {
	return object->getVzdelanie()->getPocetVzdelanie(typVzdelania_);
}

inline void CriterionUJVzdelaniePocet::setTypVzdelania(TYP_VZDELANIA typVzdelania) {
	typVzdelania_ = typVzdelania;
}
