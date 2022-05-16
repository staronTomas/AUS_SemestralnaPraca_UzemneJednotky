#pragma once

#include <iostream>
#include "sorted_sequence_table.h"

using namespace std;

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
	
	structures::SortedSequenceTable<UZEMNA_JEDNOTKA, structures::SortedSequenceTable<string, UzemnaJednotka*>*>* uzemneJednotkyChilder_;

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



};

