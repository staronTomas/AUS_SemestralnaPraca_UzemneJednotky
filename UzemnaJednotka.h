#pragma once

#include <iostream>
#include "structures/table/sorted_sequence_table.h"
#include "Vzdelanie.h"
#include "Vek.h"

#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"
#include "structures/heap_monitor.h"


using namespace structures; // nemusim robi? structures::



class UzemnaJednotka
{


private:


	std::string nazov_;
	UZEMNA_JEDNOTKA typUzemnejJednotky_;
	std::string kodUJ_;
	UzemnaJednotka* vyssiaUJRodic_;
	Vzdelanie* vzdelanie_;
	int pocetObyvatelov_;
	Vek* vekObyvatelov_;

	SortedSequenceTable<std::string, UzemnaJednotka*>* uzemneJednotkyChildren_;

public:

	UzemnaJednotka(std::string nazov, UZEMNA_JEDNOTKA typUzemnejJednotky, std::string kodUJ, UzemnaJednotka* rodic) {

		nazov_ = nazov;
		typUzemnejJednotky_ = typUzemnejJednotky;
		kodUJ_ = kodUJ;
		vyssiaUJRodic_ = rodic;
		pocetObyvatelov_ = 0;
		vekObyvatelov_ = new Vek();
		uzemneJednotkyChildren_ = new SortedSequenceTable<std::string, UzemnaJednotka*>();
		vzdelanie_ = new Vzdelanie();
	};

	~UzemnaJednotka() {
		nazov_ = "";
		typUzemnejJednotky_;
		kodUJ_ = "";
		delete vzdelanie_;
		vzdelanie_ = nullptr;
		pocetObyvatelov_ = 0;
		delete vekObyvatelov_;
		vekObyvatelov_ = nullptr;
		vyssiaUJRodic_ = nullptr;

		// samostatne UzemneJednotky deletnem na konci programu
		delete uzemneJednotkyChildren_;
		uzemneJednotkyChildren_ = nullptr;
	}




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

	std::string getStringTypUzemnejJednotky() {
		switch (typUzemnejJednotky_)
		{
		case UZEMNA_JEDNOTKA::STAT:
			return "Stat";
			break;
		case UZEMNA_JEDNOTKA::KRAJ:
			return "Kraj";
			break;
		case UZEMNA_JEDNOTKA::OKRES:
			return "Okres";
			break;
		case UZEMNA_JEDNOTKA::OBEC:
			return "Obec";
			break;
		default:
			return "Neznamy typ UJ";
			break;
		}
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

	Vek* getVekObyvatelov() {
		return vekObyvatelov_;
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

	void setChildren(SortedSequenceTable<std::string, UzemnaJednotka*>* newChildren) {
		uzemneJednotkyChildren_ = newChildren;
	}

	void setPocetObyvatelov(int pocet) {
		pocetObyvatelov_ = pocet;
	}

	void setVzdelanie(Vzdelanie* vzdelanie) {
		vzdelanie_ = vzdelanie;
	}

	void setVekObyvatelov(Vek* vek) {
		vekObyvatelov_ = vek;
	}



	double getPodielVzdelanie(TYP_VZDELANIA vzd) {

		double result = 0;

		double pocetVzdelanych = getVzdelanie()->getPocetVzdelanie(vzd);
		double celkovyPocetObyv = getPocetObyvatelov();

		result = 100.0 / celkovyPocetObyv * static_cast<double>(pocetVzdelanych);

		return result;
	}

};