#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

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

		/// <summary> Pole s datami. </summary>
		Array<Array<T>*>* array_;
		/// <summary> Pocet prvkov v matici. </summary>
		size_t size_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount)
	{

		size_ = rowCount * columnCount;
		rowNum = rowCount;
		colNum = columnCount;

		array_ = new Array<Array<T>*>(rowCount);
		for (size_t i = 0; i < rowCount; i++) {
			array_->at(i) = new Array<T>(columnCount);
		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other)
	{
		
		rowNum = other.getRowCount();
		colNum = other.getColumnCount();
		size_ = rowNum * colNum;

		array_ = new Array<Array<T>*>(rowNum);
		for (size_t i = 0; i < rowNum; i++) {
			array_->at(i) = new Array<T>(colNum);
		}

		for (size_t i = 0; i < rowNum; i++) {

			for (size_t j = 0; j < colNum; j++) {
				this->at(i, j) = other.at(i, j);
			}
		}

	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		
		for (size_t i = 0; i < rowNum; i++) {
			delete array_->at(i);
			array_->at(i) = nullptr;
		}


		size_ = 0;
		rowNum = 0;
		colNum = 0;

		delete array_;
		array_ = nullptr;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{

		if (this != &other) {



			IncoherentMatrix<T>& otherMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);



			if (rowNum == otherMatrix.getRowCount() && colNum == otherMatrix.getColumnCount()) {
				for (int i = 0; i < rowNum; i++) {
					// assignovat pomocou array.assign()
					//najprv vytiahnem daný Array<T>
								
					array_->at(i)->assign(*otherMatrix.array_->at(i));
				}
			}
		}
		return *this;

	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{

		IncoherentMatrix<T>& otherMatrix = dynamic_cast<IncoherentMatrix<T>&>(other);
	
		if (this == &other) {
			return true;
		}


		

		if (rowNum == otherMatrix.getRowCount() && colNum == otherMatrix.getColumnCount()) {
			for (size_t i = 0; i < rowNum; i++) {
				for (size_t j = 0; j < colNum; j++) {
					if (this->at(i, j) != otherMatrix.at(i, j)) {
						return false;
					}
				}
			}
		}
		else {
			return false;
		}
		return true;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return size_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return rowNum;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return colNum;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, rowNum, "Invalid row index!");
		Utils::rangeCheckExcept(columnIndex, colNum, "Invalid column index!");

		size_t newColIndex = static_cast<size_t>(columnIndex);

		return (*array_->at(rowIndex)).at(newColIndex);
	}
}


