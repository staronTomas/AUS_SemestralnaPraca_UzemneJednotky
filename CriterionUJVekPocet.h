#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekPocet : public CriterionUJ<int> {

private:
	int vek_;
	POHLAVIE pohlavie_;
	
public:

	int evaluate(UzemnaJednotka* object);

	void setVek(int vek);
	void setPohlavie(POHLAVIE pohlavie);

};

inline int CriterionUJVekPocet::evaluate(UzemnaJednotka* object) {
	return object->getVekObyvatelov()->getPocetVek(pohlavie_, vek_);
}

inline void CriterionUJVekPocet::setVek(int vek) {
	vek_ = vek;
}

inline void CriterionUJVekPocet::setPohlavie(POHLAVIE pohlavie) {
	pohlavie_ = pohlavie;
}