#pragma once

#include <iostream>
#include <string>

#include "Criterion.h"

#include "UzemnaJednotka.h"


#include "UzemnaJednotka.h"
#include "Vzdelanie.h"
#include "enum_EVS.h"
#include "enum_Pohlavie.h"
#include "enum_TypVzdelania.h"
#include "enum_UzemnaJednotka.h"
#include "enum_VyssiCelok.h"

template<typename T>

class CriterionUJ : public Criterion<UzemnaJednotka*, T> {

};