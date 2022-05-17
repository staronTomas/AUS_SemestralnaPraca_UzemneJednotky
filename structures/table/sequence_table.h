#pragma once

#include "table.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SequenceTable : public Table<K, T>
	{
	public:
		/// <summary> Destruktor. </sumary>
		~SequenceTable();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky tabulky. </param>
		/// <remarks>
		/// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
		/// List dealokuje tento objekt.
		/// </remarks>
		SequenceTable(List<TableItem<K, T>*>* list);

		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		virtual TableItem<K, T>* findTableItem(const K& key);

		/// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		/// <summary>
		SequenceTable<K, T>& assignSequenceTable(SequenceTable<K, T>& other);

	protected:
		List<TableItem<K, T>*>* list_;
	};

	template<typename K, typename T>
	inline SequenceTable<K, T>::~SequenceTable()
	{
		clear();
		delete list_;
		list_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t SequenceTable<K, T>::size()
	{
		return list_->size();
	}

	template<typename K, typename T>
	inline T& SequenceTable<K, T>::find(const K& key)
	{
		TableItem<K, T>* tableItem = findTableItem(key);
		if (tableItem != nullptr)
		{
			return tableItem->accessData();
		}
		else
		{
			throw std::out_of_range("Unable to find item");
		}
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::insert(const K& key, const T& data)
	{
		if (!containsKey(key))
		{
			TableItem<K, T>* tableItem = new TableItem<K, T>(key, data);
			list_->add(tableItem);
		}
		else
		{
			throw std::logic_error("SequenceTable<K, T>::insert: Key already present in the table!");
		}
	}

	template<typename K, typename T>
	inline T SequenceTable<K, T>::remove(const K& key)
	{
		TableItem<K, T>* tableItem = findTableItem(key);
		if (tableItem != nullptr)
		{
			list_->tryRemove(tableItem);
			T result = tableItem->accessData();
			delete tableItem;
			return result;
		}
		else
		{
			throw std::logic_error("Unable to remove item!");
		}

	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::tryFind(const K& key, T& data)
	{
		TableItem<K, T>* tableItem = findTableItem(key);
		if (tableItem != nullptr)
		{
			data = tableItem->accessData();
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::containsKey(const K& key)
	{
		T data;
		return tryFind(key, data);
		for (auto tableItem : *this)
		{
			if (tableItem->getKey() == key)
			{
				return true;
			}
		}
		
		return false;
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::clear()
	{
		for (auto tableItem : *this)
		{
			delete tableItem;
		}
		list_->clear();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getBeginIterator()
	{
		return list_->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getEndIterator()
	{
		return list_->getEndIterator();
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>::SequenceTable(List<TableItem<K, T>*>* list) :
		Table<K, T>(),
		list_(list)
	{
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SequenceTable<K, T>::findTableItem(const K& key)
	{
		for (auto tableItem : *this)
		{
			if (tableItem->getKey() == key)
			{
				return tableItem;
			}
		}

		return nullptr;
	}
	
	template<typename K, typename T>
	inline SequenceTable<K, T>& SequenceTable<K, T>::assignSequenceTable(SequenceTable<K, T>& other)
	{
		if (this != &other)
		{
			clear();
			for (auto item : *other.list_)
			{
				list_->add(new TableItem<K, T>(*item));
			}
		}
		return *this;
	}
}