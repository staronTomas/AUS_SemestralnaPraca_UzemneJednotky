#pragma once

#include "CriterionUJ.h"
#include "enum_UzemnaJednotka.h"


class CriterionUJVekPodiel : public CriterionUJ<double> {

private:
	int vek_;
	POHLAVIE pohlavie_;

public:

	double evaluate(UzemnaJednotka* object);

	void setVek(int vek);
	void setPohlavie(POHLAVIE pohlavie);

};

inline double CriterionUJVekPodiel::evaluate(UzemnaJednotka* object) {
	int pocetLudiVPozadovanomVeku = object->getVekObyvatelov()->getPocetVek(pohlavie_, vek_);
	int pocetObyvatelov = object->getPocetObyvatelov();

	double result = 100.0 / pocetObyvatelov * static_cast<double>(pocetLudiVPozadovanomVeku);

	return result;
}



inline void CriterionUJVekPodiel::setVek(int vek) {
	vek_ = vek;
}

inline void CriterionUJVekPodiel::setPohlavie(POHLAVIE pohlavie) {
	pohlavie_ = pohlavie
}