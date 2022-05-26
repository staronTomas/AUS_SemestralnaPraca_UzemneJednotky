#pragma once

#include <iostream>

#include "Filtrovanie.h"
#include "UzemnaJednotka.h"

#include "structures/table/unsorted_sequence_table.h";

class Triedenie {


private:

	Filtrovanie* filter_;

public:
	
	Triedenie() {
		filter_ = new Filtrovanie();
	};

	~Triedenie() {
		delete filter_;
	};


	void spustiTriedenie(UzemnaJednotka* slovensko) {

		structures::LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>* vyfiltrovaneTabulky = filter_->zapniFiltrovanieSTriedenim(slovensko);

		UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneKraje = vyfiltrovaneTabulky->at(0);
		UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneOkresy = vyfiltrovaneTabulky->at(1);
		UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneObce = vyfiltrovaneTabulky->at(2);



		for (TableItem<std::string, UzemnaJednotka*>* kraj : *vyfiltrovaneKraje) {

			std::cout << std::endl << std::endl << "## Nazov Uzemnej Jednotky -> " << kraj->accessData()->getNazov();
		}
		std::cout << "# Vypisane OKRESY: " << std::endl;
		for (TableItem<std::string, UzemnaJednotka*>* okres : *vyfiltrovaneOkresy) {
			std::cout << std::endl << "## Nazov Uzemnej Jednotky -> " << okres->accessData()->getNazov();
		}
		std::cout << "# Vypisane OBCE: " << std::endl;
		for (TableItem<std::string, UzemnaJednotka*>* obec : *vyfiltrovaneObce) {
			std::cout << std::endl << "## Nazov Uzemnej Jednotky -> " << obec->accessData()->getNazov() << std::endl;

		}



		std::cout << "som tuuuuuu";
		system("pause");

		



	}

};