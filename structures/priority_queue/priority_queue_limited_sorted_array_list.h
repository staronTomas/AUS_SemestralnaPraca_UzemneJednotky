#pragma once

#include "priority_queue_sorted_array_list.h"
#include <stdexcept>

namespace structures
{
    /// <summary> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        PriorityQueueLimitedSortedArrayList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou, z ktoreho sa prevezmu vlastnosti. </param>
        PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other);

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou. </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front plny. </exception>
        void push(int priority, const T& data) override;

        /// <summary>
        ///  Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou.
        ///  V pripade, ze je prioritny front plny, odstrani polozku s najmensou prioritou z prioritneho frontu a vrati smernik na nu.
        ///  V opacnom pripade vrati nullptr.
        /// </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <returns> Smernik na odstranenu polozku alebo nullptr. </returns>
        PriorityQueueItem<T>* pushAndRemove(int priority, T data);

        /// <summary> Vrati najmensiu prioritu nachadzajucu sa v prioritnom fronte. </summary>
        /// <returns> Najmensiu priorita nachadzajuca sa v prioritnom fronte. </returns>
        int minPriority();

        /// <summary>
        ///  Pokusi sa zmenit kapacitu prioritneho frontu.
        ///  Kapacitu je mozne zmensit len ak nova kapacita nie je mensia ako aktualny pocet poloziek v prioritnom fronte.
        ///  V opacnom pripade nedojde k zmene kapacity.
        /// </summary>
        /// <param name = "capacity"> Nova kapacita. </param>
        /// <returns> true, ak sa kapacitu podarilo zmenit, false inak. </returns>
        bool trySetCapacity(size_t capacity);

        size_t getCapacity();

    private:
        /// <summary> Kapacita prioritneho frontu. </summary>
        size_t capacity_;
    };

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList() :
        PriorityQueueSortedArrayList<T>(),
        capacity_(2)
    {
    }

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other) :
        PriorityQueueSortedArrayList<T>(other),
        capacity_(other.capacity_)
    {
    }

    template<typename T>
    inline Structure& PriorityQueueLimitedSortedArrayList<T>::assign(Structure& other)
    {
        
        auto otherCasted = dynamic_cast<PriorityQueueLimitedSortedArrayList<T>&>(other);
        capacity_ = otherCasted.capacity_;

        return PriorityQueueSortedArrayList<T>::assign(dynamic_cast<PriorityQueueSortedArrayList<T>&>(other));
    }

    template<typename T>
    void PriorityQueueLimitedSortedArrayList<T>::push(int priority, const T& data)
    {

        if (PriorityQueueList<T>::list_->size() >= capacity_) {
            throw std::logic_error("Kapacita prio que lim sort arrListu bola naplnena... prvok sa nevlozil");
        }

        PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);

        int leftIndex = 0;
        int rightIndex = static_cast<int>(PriorityQueueList<T>::list_->size());

        while (leftIndex < rightIndex)
        {
            int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
            if (priority < PriorityQueueList<T>::list_->at(middleIndex)->getPriority())
            {
                leftIndex = middleIndex + 1;
            }
            else
            {
                rightIndex = middleIndex;
            }
        }
        PriorityQueueList<T>::list_->insert(item, leftIndex);

    }

    template<typename T>
    inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(int priority, T data)
    {

        PriorityQueueItem<T>* deletedItem = nullptr;

        if (PriorityQueueList<T>::list_->size() == capacity_)
        {
            if (PriorityQueueList<T>::list_->at(0)->getPriority() > priority)
            {
                deletedItem = PriorityQueueList<T>::list_->removeAt(0);
                this->push(priority, data);
            }
            else
            {
                deletedItem = new PriorityQueueItem<T>(priority, data);
            }
        }
        else
        {
            this->push(priority, data);
        }
        return deletedItem;
    }

    template<typename T>
    inline int PriorityQueueLimitedSortedArrayList<T>::minPriority()
    {
        if (PriorityQueueList<T>::list_->size() == 0) {
            throw std::logic_error("Prio que lim sort arrListu ma 0 prvkov...");
        }
        return PriorityQueueList<T>::list_->at(0)->getPriority();
    }

    template<typename T>
    inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity)
    {

        if (capacity >= PriorityQueueList<T>::list_->size()) {
            capacity_ = capacity;
            return true;
        }
        else {
            return false;
        }
    }

    template<typename T>
    inline size_t PriorityQueueLimitedSortedArrayList<T>::getCapacity()
    {
        return capacity_;
    }
}