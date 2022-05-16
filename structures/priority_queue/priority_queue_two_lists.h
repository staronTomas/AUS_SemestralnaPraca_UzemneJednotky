#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

#include <iostream>
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{

		if (this == &other) {
			return *this;
		}

		PriorityQueueTwoLists& paramQueue = dynamic_cast<PriorityQueueTwoLists&>(other);
		shortList_->clear();
		shortList_->assign(*paramQueue.shortList_);

		longList_->clear();
		for (auto item : *paramQueue.longList_) {
			longList_->add(new PriorityQueueItem<T>(*item));
		}

		return *this;

	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return longList_->size() + shortList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		delete shortList_;
		shortList_ = nullptr;

		for (auto item : *longList_) {
			delete item;
		}

		delete longList_;
		longList_ = nullptr;
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
		if (shortList_->getCapacity() != shortList_->size()) {
			shortList_->push(priority, data);
		}
		else if (longList_->size() == 0 || priority < shortList_->minPriority()) {

			PriorityQueueItem<T>* removedItem = shortList_->pushAndRemove(priority, data);
			longList_->add(removedItem);

		}
		else {
			PriorityQueueItem<T>* removedItem = new PriorityQueueItem<T>(priority, data);
			longList_->add(removedItem);

		}

	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{

		T delItem = shortList_->pop();


		if (shortList_->isEmpty() && longList_->size() != 0) {

			if (sqrt(longList_->size()) > 2) {
				shortList_->trySetCapacity(sqrt(longList_->size()));
			}
			else {
				shortList_->trySetCapacity(2); // toto je defaultna hodnota pre moj shortList ktora sa nastavi v pripade ze longList je moc maly...
			}

			LinkedList<PriorityQueueItem<T>*>* pomocnyList = new LinkedList<PriorityQueueItem<T>*>();

			while (!longList_->isEmpty()) {

				PriorityQueueItem<T>* removedItem = longList_->removeAt(0);
				
				if (removedItem == nullptr) {
					continue;
				}

				PriorityQueueItem<T>* tempVar = shortList_->pushAndRemove(removedItem->getPriority(), removedItem->accessData());

				delete removedItem;

				if (tempVar != nullptr) {
					pomocnyList->add(tempVar);
				}
			}
			
			longList_->clear();
			longList_->assign(*pomocnyList);

			delete pomocnyList;
		}
		return delItem;
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}
}