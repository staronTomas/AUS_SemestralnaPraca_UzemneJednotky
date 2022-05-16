#pragma once

#include <iostream>
#include "sorted_sequence_table.h"
#include "Vzdelanie.h"

using namespace std;

using namespace structures; // nemusim robiù structures::

class UzemnaJednotka
{

private:


	enum UZEMNA_JEDNOTKA {
		STAT, KRAJ, OKRES, OBEC
	};

	enum TYP_VZDELANIA {
		BEZ_UKONCENEHO_VZDELANIA, ZAKLADNE, UCNOVSKE, STREDNE, VYSSIE, VYSOKOSKOLSKE, BEZ_VZDELANIA, NEZISTENE
	};


	string nazov_;
	UZEMNA_JEDNOTKA typUzemnejJednotky_;
	string kodUJ_;
	UzemnaJednotka* vyssiaUJRodic_;
	bool list_;
	bool koren_;
	Vzdelanie* vzdelanie_;

	
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

	bool jeKoren() {
		return koren_;
	}

	bool jeList() {
		return list_;
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

	void setKoren(bool isRoot) {
		koren_ = isRoot;
	}

	void setList(bool isList) {
		list_ = isList;
	}

};

