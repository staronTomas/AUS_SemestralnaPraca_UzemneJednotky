#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
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
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& operator[](int index);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& at(int index);

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception>
		static void copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;
	};

	template<typename T>
	Array<T>::Array(size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(Array<T>& other) :
		vector_(new Vector(*(other.vector_))),
		size_(other.size_)
	{

	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_;
		vector_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	Structure& Array<T>::assign(Structure& other)
	{
		if (this != &other) {
			//pretypuj other na pole
			//maju rovnake velkosti?
			//	ano: prirad do svojho vektora vektor od pola other
			//	nie: vynimka
			Array<T>& otherArray = dynamic_cast<Array<T>&>(other);
			if (size_ != otherArray.size_) {
				throw std::invalid_argument("Array sizes are not the same!");
			}
			vector_->assign(*(otherArray.vector_));
		}

		return *this;
	}

	template<typename T>
	inline bool Array<T>::equals(Structure& other)
	{

		//pretypujte other na ukazovatel na pole
		// ak je to pole, tak vratte vysledok z porovnania vektorov
		// ak to nieje pole, vratte False

		Array<T>* otherArray = dynamic_cast<Array<T>*>(&other);
		if (otherArray != nullptr) {
			return vector_->equals(*otherArray->vector_);
		}
		else {
			return false;
		}
	}

	template<typename T>
	size_t Array<T>::size()
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		return at(index);
	}

	template<typename T>
	inline T& Array<T>::at(int index)
	{
		// 1, pomocou mapovacej funckie ziskaj index vo vektore
		// 2, pomocou getBytePointer ziskaj ukazovatel na byte vo vektore na indexe z kroku 1
		// 3, pretypuj ukazovatel z kroku 2 na T*
		// vrat hodnotu podukazovatelom z kroku 3

		//dynamic cast je vhodny pre objekty
		//reinterpret cast neriesi konverzie

		int vectorIndex = mapFunction(index);
		byte* ptrByte = vector_->getBytePointer(vectorIndex);
		T* ptrT = reinterpret_cast<T*>(ptrByte);

		return *ptrT;

	}

	template<typename T>
	void Array<T>::copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length)
	{
		if (length != 0) {
			Vector::copy(*src.vector_, src.mapFunction(srcStartIndex), *dest.vector_, dest.mapFunction(destStartIndex), length * sizeof(T));
		}
	}

	template<typename T>
	inline int Array<T>::mapFunction(int index) const
	{
		Utils::rangeCheckExcept(index, size_, "INvalid index!");
		return index * sizeof(T);
	}
}


