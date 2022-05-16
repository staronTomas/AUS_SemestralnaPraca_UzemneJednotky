#pragma once

#include "list.h"

#include <iostream>

namespace structures
{
    // implementacne tipy: 
    //  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
    //    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
    //    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
    //    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
    //    zvysok nechat na predka.
    //  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
    //    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
    //  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
    //    takze ich nebudete musiet implementovat.



     /// <summary> Prvok dvojstranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class DoubleLinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getNext();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(DoubleLinkedListItem<T>* next);

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getPrev();

        /// <summary> Setter predchadzajuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy predchadzajuceho prvok zretazeneho zoznamu. </param>
        void setPrev(DoubleLinkedListItem<T>* prev);


    private:
        /// <summary> Predchadzajuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* prev_;

        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* next_;

    };






    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class DoubleLinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;


        // pomocna metoda pre mna, ktora mi zisti ci obsahuje list ma dane data
        bool hasData(const T& data);

    private:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        DoubleLinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        DoubleLinkedListItem<T>* last_;




    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        DoubleLinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class DoubleLinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~DoubleLinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            DoubleLinkedListItem<T>* position_;
        };
    };




    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr),
        prev_(nullptr)
    {

    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_),
        prev_(other.prev_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        next_ = nullptr;
        prev_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrev()
    {
        return prev_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrev(DoubleLinkedListItem<T>* prev)
    {
        prev_ = prev;
    }





















    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {

    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
    {
        assign(other);
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        if (this != &other) {
            DoubleLinkedList<T>& otherLinkedList = dynamic_cast<DoubleLinkedList<T>&>(other);
            clear();
            DoubleLinkedListItem<T>* otherItem = otherLinkedList.first_;
            while (otherItem != nullptr) {
                add(otherItem->accessData());
                otherItem = otherItem->getNext();
            }
        }

        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        if (this == &other) {
            return true;
        }

        if (size_ != other.size()) {
            return false;
        }

        DoubleLinkedList<T>* otherDoubleLinkedList = dynamic_cast<DoubleLinkedList<T>*>(&other);
        if (otherDoubleLinkedList == nullptr) {
            return false;
        }

        DoubleLinkedListItem<T>* item = first_;
        DoubleLinkedListItem<T>* otherItem = otherDoubleLinkedList->first_;

        while (item != nullptr) {
            if (item->accessData() != otherItem->accessData()) {
                return false;
            }
            item = item->getNext();
            otherItem = otherItem->getNext();
        }

        return true;
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {

        Utils::rangeCheckExcept(index, size_, "Invalid index!");

        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        DoubleLinkedListItem<T>* newItem = new DoubleLinkedListItem<T>(data);
        if (size_ == 0) {
            first_ = newItem;
            last_ = newItem;

        }
        else {
            newItem->setPrev(last_);
            last_->setNext(newItem);
            last_ = newItem;
        }
        size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {


        if (size_ == index) {
            add(data);
        }
        else {
            Utils::rangeCheckExcept(index, size_, "Invalid index!");

            DoubleLinkedListItem<T>* newLinkedListItem = new DoubleLinkedListItem<T>(data);

            if (index == 0) {
                newLinkedListItem->setNext(first_);
                first_->setPrev(newLinkedListItem);
                first_ = newLinkedListItem;
            }
            else {
                DoubleLinkedListItem<T>* previousLinkedListItem = getItemAtIndex(index - 1);
                newLinkedListItem->setNext(previousLinkedListItem->getNext());
                newLinkedListItem->setPrev(previousLinkedListItem);
                previousLinkedListItem->getNext()->setPrev(newLinkedListItem);
                previousLinkedListItem->setNext(newLinkedListItem);

            }
            size_++;

        }
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        int index = getIndexOf(data);
        if (index == -1) {
            return false;
        }
        else {
            removeAt(index);
            return true;
        }
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {


        Utils::rangeCheckExcept(index, size_, "Invalid index!");
        DoubleLinkedListItem<T>* itemToDelete;

        if (index != 0) {
            DoubleLinkedListItem<T>* previousItem = getItemAtIndex(index - 1);
            itemToDelete = previousItem->getNext();


            previousItem->setNext(itemToDelete->getNext());
            if (itemToDelete == last_) {
                last_ = previousItem;
            }
            else {
                itemToDelete->getNext()->setPrev(previousItem);
            }
        }
        else {
            itemToDelete = first_;
            first_ = first_->getNext();
            if (itemToDelete == last_) {
                last_ = nullptr;
                first_ = nullptr;
            }
        }

        T result = itemToDelete->accessData();
        delete itemToDelete;
        size_--;

        return result;

    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {

        int i = 0;
        DoubleLinkedListItem<T>* currentDoubleLinkedListItem = first_;
        if (currentDoubleLinkedListItem != nullptr) {
            do
            {
                if (currentDoubleLinkedListItem->accessData() == data) {
                    return i;
                }
                currentDoubleLinkedListItem = currentDoubleLinkedListItem->getNext();
                i++;
            } while (currentDoubleLinkedListItem != first_);
        }
        return -1;

    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        if (size_ != 0) {
            DoubleLinkedListItem<T>* itemToDelete = first_;

            while (itemToDelete != nullptr) {
                DoubleLinkedListItem<T>* nextItem = itemToDelete->getNext();
                delete itemToDelete;
                itemToDelete = nextItem;
            }

            size_ = 0;
            first_ = nullptr;
            last_ = nullptr;
        }
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        return new DoubleLinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        return new DoubleLinkedListIterator(last_);
    }





    template<typename T>
    inline bool DoubleLinkedList<T>::hasData(const T& data)
    {
        DoubleLinkedListItem<T>* currentItem = first_;

        while (currentItem != last_) {
            if (currentItem->accessData() = data) {
                return true;
            }
            currentItem = currentItem->getNext();
        }

        return false;
    }










    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {


        int velkostListu = static_cast<int>(size_);

        if (velkostListu / 2 > index) { // IF TRUE >> idem normalne cez next... else idem cez prev

            DoubleLinkedListItem<T>* currentLinkedListItem = first_;
            for (int i = 0; i < index; i++) {
                currentLinkedListItem = currentLinkedListItem->getNext();
            }

            return currentLinkedListItem;
        }
        else {
            DoubleLinkedListItem<T>* currentLinkedListItem = last_;
            for (int i = velkostListu - 1; i > index; i--) {
                currentLinkedListItem = currentLinkedListItem->getPrev();
            }

            return currentLinkedListItem;
        }



    }







    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
    {
        delete position_;
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
    {
        position_ = dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
    {
        return position_ != dynamic_cast<const DoubleLinkedListIterator&>(other).position_;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    }

}