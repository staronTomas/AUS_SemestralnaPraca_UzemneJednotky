#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Select sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SelectSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Select sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void SelectSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{

		for (int i = 0; i <= table.size() - 2; i++) {
			int min = i;
			for (int j = i + 1; j <= table.size() - 1; j++) {
				if (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(min).getKey()) {
					min = j;
					
				}
			}
			table.swap(i, min);
		}


		/*
			Pre i od 0 do po�et prvkov - 2, i++
			min := i;
			Pre j od i + 1 do po�et prvkov - 1, j++
			Ak K���[j] < K���[min] tak
			min := j;
			Vyme� (i, min); //vymen� prvky na miestach i a min
		*/
	}

}