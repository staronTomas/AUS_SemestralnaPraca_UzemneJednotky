#pragma once

#include "CriterionUJ.h"


class CriterionUJPrislusnost : public CriterionUJ<bool> {


private: 
	UzemnaJednotka* vyssiCelok_;

public:

	CriterionUJPrislusnost(UzemnaJednotka* prislusnostVyssi) {
		vyssiCelok_ = prislusnostVyssi;
	}

	bool evaluate(UzemnaJednotka* object);

	void setVyssiCelok(UzemnaJednotka* vyssiCelok);

};


inline bool CriterionUJPrislusnost::evaluate(UzemnaJednotka* object) {
	if (object->getVyssiaUJRodic() == vyssiCelok_) {
		return true;
	}
	else {
		return false;
	}
}

inline void CriterionUJPrislusnost::setVyssiCelok(UzemnaJednotka* uj) {
	vyssiCelok_ = uj;
}