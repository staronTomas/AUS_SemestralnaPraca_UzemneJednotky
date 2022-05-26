#pragma once

#include <iostream>

#include "Filtrovanie.h"
#include "UzemnaJednotka.h"

#include "structures/table/unsorted_sequence_table.h";

class Triedenie {


private:

	Filtrovanie* filter_;

	UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovaneUJ_;

public:
	
	Triedenie() {
		filter_ = new Filtrovanie();
		vyfiltrovaneUJ_ = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
	};

	~Triedenie() {
		delete filter_;

		delete vyfiltrovaneUJ_;
	};


	void spustiTriedenie(UzemnaJednotka* slovensko) {


		// toto sa mi pomaly strasne moc nacita
		structures::LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>* vyfiltrovaneTabulky = filter_->zapniFiltrovanieSTriedenim(slovensko);

		
		spojTabulky(vyfiltrovaneTabulky);

		Array<bool>* aktFiltre = filter_->vratZoznamAktivovanychFiltrov();
		



		delete aktFiltre;
	}


	void spojTabulky(structures::LinkedList<UnsortedSequenceTable<std::string, UzemnaJednotka*>*>* tab) {

		std::cout << "kebaaab" << std::endl;

		for (int i = 0; i < tab->size(); i++)
		{
			if (tab->at(i) != nullptr)
			{
				for (TableItem<std::string, UzemnaJednotka*>* item : *tab->at(i))
				{
					vyfiltrovaneUJ_->insert(item->getKey(), item->accessData());
				}
			}
		}

		
	}

};