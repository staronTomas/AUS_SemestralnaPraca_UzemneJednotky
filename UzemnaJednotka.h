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
	
	SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<std::string, UzemnaJednotka*>*>* uzemneJednotkyChilder_;

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

	SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<std::string, UzemnaJednotka*>*>* getUzemneJednotkyChildren() {
		return uzemneJednotkyChilder_;
	}

	bool jeKoren() {
		return koren_;
	}

	bool jeList() {
		return list_;
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

	void setKoren(bool isRoot) {
		koren_ = isRoot;
	}

	void setList(bool isList) {
		list_ = isList;
	}

};

