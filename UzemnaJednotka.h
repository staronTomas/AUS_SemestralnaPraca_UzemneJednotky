#pragma once

#include <iostream>
#include "sorted_sequence_table.h"

using namespace std;

using namespace structures; // nemusim robiù structures::

class UzemnaJednotka
{
private:

	enum UZEMNA_JEDNOTKA {
		STAT, KRAJ, OKRES, OBEC
	};

	string nazov_;
	UZEMNA_JEDNOTKA typUzemnejJednotky_;
	string kodUJ_;
	UzemnaJednotka* vyssiaUJRodic_;
	bool list_;
	bool koren_;
	
	SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<string, UzemnaJednotka*>*>* uzemneJednotkyChilder_;

public:
	UzemnaJednotka(string nazov, UZEMNA_JEDNOTKA typUzemnejJednotky, string kodUJ, UzemnaJednotka* rodic) {
		nazov_ = nazov;
		typUzemnejJednotky_ = typUzemnejJednotky;
		kodUJ_ = kodUJ;
		vyssiaUJRodic_ = rodic;
		
		if (typUzemnejJednotky_ = STAT) {
			koren_ = true;
		}
		else {
			koren_ = false;
			if (typUzemnejJednotky_ = OBEC) {
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


	string getNazov() {
		return nazov_;
	}

	UZEMNA_JEDNOTKA getTypUzemnejJednotky() {
		return typUzemnejJednotky_;
	}

	string getKodUJ() {
		return kodUJ_;
	}

	UzemnaJednotka* getVyssiaUJRodic() {
		return vyssiaUJRodic_;
	}

	SortedSequenceTable<UZEMNA_JEDNOTKA, SortedSequenceTable<string, UzemnaJednotka*>*>* getUzemneJednotkyChildren() {
		return uzemneJednotkyChilder_;
	}


	// Settery

	void setNazov(string nazov) {
		nazov_ = nazov;
	}

	void setTypUzemnejJednotky(UZEMNA_JEDNOTKA typUJ) {
		typUzemnejJednotky_ = typUJ;
	}

	void setKodUJ(string kodUj) {
		kodUJ_ = kodUj;
	}

	void setVyssiaUJRodic(UzemnaJednotka* vyssiaUJRodic) {
		vyssiaUJRodic_ = vyssiaUJRodic;
	}


};

