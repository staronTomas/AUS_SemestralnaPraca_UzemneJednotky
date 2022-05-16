#pragma once

#include "matrix.h"
#include <stdexcept>
#include "../vector/vector.h"
#include "../utils.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	private:
		size_t rowNum;
		size_t colNum;

		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;


	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount):
		vector_(new Vector(rowCount * columnCount * sizeof(T))),
		size_(rowCount* columnCount)
	{
		rowNum = rowCount;
		colNum = columnCount;
	}


	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		Matrix<T>(),
		vector_(new Vector(*other.vector_)),
		rowNum(other.rowNum),
		colNum(other.colNum)
	{
	}



	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete vector_;
		vector_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			
			CoherentMatrix<T>& otherMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
			if (rowNum != otherMatrix.getRowCount() || colNum != otherMatrix.getColumnCount()) {
				throw std::invalid_argument("Array sizes are not the same!");
			}
			vector_->assign(*(otherMatrix.vector_));
		}

		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}

		CoherentMatrix<T>* otherMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (otherMatrix != nullptr) {
			return vector_->equals(*otherMatrix->vector_);
		}
		else {
			return false;
		}
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return rowNum;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return colNum;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		int index;

		index = rowIndex * colNum + columnIndex;

		int vectorIndex = mapFunction(index);
		byte* ptrByte = vector_->getBytePointer(vectorIndex);
		T* ptrT = reinterpret_cast<T*>(ptrByte);

		return *ptrT;
	}

	template<typename T>
	inline int CoherentMatrix<T>::mapFunction(int index) const
	{
		Utils::rangeCheckExcept(index, size_, "INvalid index!");
		return index * sizeof(T);
	}

}