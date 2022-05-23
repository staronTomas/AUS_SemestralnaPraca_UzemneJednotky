#pragma once
#include "Criterion.h"
template<typename T, typename O>

class Filter {

protected:


	Criterion<T, O>* criterion_ = nullptr;
	virtual bool pass(O* objekt) const = 0;
	SortedSequenceTable<std::string, UzemnaJednotka*>* resultTable_ = nullptr;
public:

	SortedSequenceTable<std::string, UzemnaJednotka*>* getResultTable() {
		return this->vystupnaTabulka;
	}

	SortedSequenceTable<std::string, UzemnaJednotka*>* passFilter(SortedSequenceTable<std::string, UzemnaJednotka*>* inputTable) {
		LinkedList<UzemnaJednotka*>* link;

		for (TableItem<std::string, UzemnaJednotka*>* objekt : *inputTable)
		{


			for (int i = 0; i < objekt->accessData()->size(); i++)
			{
				if (passFilter(objekt->accessData()->operator[](i))) {

					std::string nazov = objekt->accessData()->operator[](i)->getNazov();


					if (!this->resultTable_->containsKey(nazov))
					{
						link = new LinkedList<UzemnaJednotka*>;
						this->resultTable_->insert(objekt->accessData()->operator[](i)->getNazov(), link);
						UzemnaJednotka* pridavanyObjekt = objekt->accessData()->operator[](i);
						link->add(pridavanyObjekt);
					}
					else {
						link = this->resultTable_->operator[](objekt->accessData()->operator[](i)->getNazov());
						link->add(objekt->accessData()->operator[](i));
					}

				}
			}
		}

		return this->resultTable_;
	};

	Filter() {
		this->resultTable_ = new SortedSequenceTable<std::string, UzemnaJednotka*>();
	}

	virtual ~Filter()
	{

		for (TableItem<std::string, UzemnaJednotka*>* item : *resultTable_)
		{
			std::string key = item->getKey();
			delete resultTable_->operator[](key);
		}
		delete resultTable_;

		resultTable_ = nullptr;

	}




};