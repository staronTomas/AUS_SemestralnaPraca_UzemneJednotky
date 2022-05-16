#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
			void sortHelper(UnsortedSequenceTable<K, T>& table, int min, int max);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		sortHelper(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::sortHelper(UnsortedSequenceTable<K, T>&table, int min, int max) {

		K hlavnyKluc = table.getItemAtIndex((min + max) / 2).getKey();

		int lavy = min;
		int pravy = max;

		do
		{
			while (table.getItemAtIndex(lavy).getKey() < hlavnyKluc)
			{
				lavy++;
			}
			while (table.getItemAtIndex(pravy).getKey() > hlavnyKluc)
			{
				pravy--;
			}
			if (lavy <= pravy)
			{
				table.swap(lavy, pravy);
				lavy++;
				pravy--;
			}
		} while (lavy <= pravy);

		if (min < pravy)
		{
			sortHelper(table, min, pravy);
		}
		if (lavy < max)
		{
			sortHelper(table, lavy, max);
		}
	}

}