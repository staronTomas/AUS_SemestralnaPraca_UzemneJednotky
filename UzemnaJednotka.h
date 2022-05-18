#pragma once

#include <iostream>
#include "structures/table/sorted_sequence_table.h"
#include "Vzdelanie.h"

#include "enum_UzemnaJednotka.h"
#include "enum_TypVzdelania.h"


using namespace structures; // nemusim robiù structures::




class UzemnaJednotka
{


private:


	std::string nazov_;
	UZEMNA_JEDNOTKA typUzemnejJednotky_;
	std::string kodUJ_;
	UzemnaJednotka* vyssiaUJRodic_;
	bool list_;
	bool koren_;
	Vzdelanie* vzdelanie_;
	
	SortedSequenceTable<std::string, UzemnaJednotka*>* uzemneJednotkyChildren_;

public:

	UzemnaJednotka(std::string nazov, UZEMNA_JEDNOTKA typUzemnejJednotky, std::string kodUJ, UzemnaJednotka* rodic) {

		nazov_ = nazov;
		typUzemnejJednotky_ = typUzemnejJednotky;
		kodUJ_ = kodUJ;
		vyssiaUJRodic_ = rodic;
		
		if (typUzemnejJednotky_ == UZEMNA_JEDNOTKA::STAT) {
			koren_ = true;
		}
		else {
			koren_ = false;
			if (typUzemnejJednotky_ == UZEMNA_JEDNOTKA::OBEC) {
				list_ = true;
			}
		}

		uzemneJednotkyChildren_ = new SortedSequenceTable<std::string, UzemnaJednotka*>();
	};

	~UzemnaJednotka() {
		nazov_ = "";
		kodUJ_ = "";
		vyssiaUJRodic_ = nullptr;
	};











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

};

