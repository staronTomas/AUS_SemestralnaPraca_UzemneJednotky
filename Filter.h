#pragma once
#include "Criterion.h"
#include "structures/table/sorted_sequence_table.h"
#include "UzemnaJednotka.h"

template<typename T, typename O, typename P>

class Filter {

protected:

	Criterion<T, O>* kriterium = nullptr;
	virtual bool pass(O* object) const = 0;
	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* resultTable = nullptr;
public:

	
	/*
	Filter() {
		resultTable = new SortedSequenceTable<std::string, LinkedList<UzemnaJednotka*>*>();
	}

	virtual ~Filter()
	{

		for (structures::TableItem<std::string, structures::LinkedList<UzemnaJednotka*>*>* item : *resultTable)
		{
			std::string kluc = item->getKey();
			delete resultTable->operator[](kluc);
		}
		delete resultTable;

		resultTable = nullptr;

	}


	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* pass(structures::SortedSequenceTable<std::string, UzemnaJednotka*>* paramTable) {
		LinkedList<UzemnaJednotka*>* link;

		for (TableItem<std::string, UzemnaJednotka*>* objekt : *paramTable)
		{


			for (int i = 0; i < objekt->accessData()->size(); i++)
			{
				if (splnaFilter(objekt->accessData()->operator[](i))) {

					std::string nazov = objekt->accessData()->operator[](i)->getNazov();


					if (!this->vystupnaTabulka->containsKey(nazov))
					{
						link = new LinkedList<UzemnaJednotka*>;
						this->vystupnaTabulka->insert(objekt->accessData()->operator[](i)->getNazov(), link);
						UzemnaJednotka* pridavanyObjekt = objekt->accessData()->operator[](i);
						link->add(pridavanyObjekt);
					}
					else {
						link = this->vystupnaTabulka->operator[](objekt->accessData()->operator[](i)->getNazov());
						link->add(objekt->accessData()->operator[](i));
					}

				}
			}
		}

		return this->vystupnaTabulka;
	};


	structures::SortedSequenceTable<std::string, UzemnaJednotka*>* getResultTable() {
		return this->resultTable;
	}

	*/

};