#pragma once

#include <iostream>
#include "structures/table/sorted_sequence_table.h"
#include "Vzdelanie.h"

#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"
#include "structures/heap_monitor.h"


using namespace structures; // nemusim robiù structures::




class UzemnaJednotka
{


private:


	std::string nazov_;
	UZEMNA_JEDNOTKA typUzemnejJednotky_;
	std::string kodUJ_;
	UzemnaJednotka* vyssiaUJRodic_;
	Vzdelanie* vzdelanie_;
	int pocetObyvatelov_;
	
	SortedSequenceTable<std::string, UzemnaJednotka*>* uzemneJednotkyChildren_;

public:

	UzemnaJednotka(std::string nazov, UZEMNA_JEDNOTKA typUzemnejJednotky, std::string kodUJ, UzemnaJednotka* rodic) {

		nazov_ = nazov;
		typUzemnejJednotky_ = typUzemnejJednotky;
		kodUJ_ = kodUJ;
		vyssiaUJRodic_ = rodic;
		pocetObyvatelov_ = 0;
		uzemneJednotkyChildren_ = new SortedSequenceTable<std::string, UzemnaJednotka*>();
		vzdelanie_ = new Vzdelanie();
	};

	~UzemnaJednotka() {
		nazov_ = "";
		kodUJ_ = "";
		vyssiaUJRodic_ = nullptr;
	};



	void navysPocetObyvatelov(int pocet) {
		pocetObyvatelov_ += pocet;
	}

	void navysPocetObyvatelovZoVzdelania(Vzdelanie* vzd) {
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::ZAKLADNE);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::UCNOVSKE);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::STREDNE);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::VYSSIE);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::VYSOKOSKOLSKE);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::BEZ_VZDELANIA);
		 pocetObyvatelov_ += vzd->getPocetVzdelanie(TYP_VZDELANIA::NEZISTENE);
	}


	//Gettery


	std::string getNazov() {
		return nazov_;
	}

	UZEMNA_JEDNOTKA getTypUzemnejJednotky() {
		return typUzemnejJednotky_;
	}

	std::string getKodUJ() {
		return kodUJ_;
	}

	UzemnaJednotka* getVyssiaUJRodic() {
		return vyssiaUJRodic_;
	}

	SortedSequenceTable<std::string, UzemnaJednotka*>* getUzemneJednotkyChildren() {
		return uzemneJednotkyChildren_;
	}

	int getPocetObyvatelov() {
		return pocetObyvatelov_;
	}

	Vzdelanie* getVzdelanie() {
		return vzdelanie_;
	}



	// Settery

	void setNazov(std::string nazov) {
		nazov_ = nazov;
	}

	void setTypUzemnejJednotky(UZEMNA_JEDNOTKA typUJ) {
		typUzemnejJednotky_ = typUJ;
	}

	void setKodUJ(std::string kodUj) {
		kodUJ_ = kodUj;
	}

	void setVyssiaUJRodic(UzemnaJednotka* vyssiaUJRodic) {
		vyssiaUJRodic_ = vyssiaUJRodic;
	}

	void setChildren(SortedSequenceTable<std::string, UzemnaJednotka*>*  newChildren) {
		uzemneJednotkyChildren_ = newChildren;
	}

	void setPocetObyvatelov(int pocet) {
		pocetObyvatelov_ = pocet;
	}

	void setVzdelanie(Vzdelanie* vzdelanie) {
		vzdelanie_ = vzdelanie;
	}

};

