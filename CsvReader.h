#pragma once

typedef std::basic_string<wchar_t> wstring;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<clocale>
#include<string>


#include "structures/array/array.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/list/linked_list.h"
#include "structures/heap_monitor.h"

#include "Vzdelanie.h"
#include "enum_TypVzdelania.h"



class CsvReader {


private:

	std::string nazovSuboru;


public:

	CsvReader() {};
	~CsvReader() {};


	structures::LinkedList<LinkedList<std::string>*>* nacitajObce(std::string nazovSuboru) {

		std::vector<std::vector<std::string>> content;
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(nazovSuboru, std::ios::in);
		if (file.is_open())
		{
			bool firstTime = true;
			while (getline(file, line))
			{
				if (firstTime) {
					firstTime = false;
					continue;
				}
				row.clear();

				std::stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			std::cout << "Could not open the file\n";
		}

		structures::LinkedList<std::string>* texty = new structures::LinkedList<std::string>();
		structures::LinkedList<LinkedList<std::string>*>* result = new structures::LinkedList<LinkedList<std::string>*>();

		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			if (riadok == ";;;;;") {
				break;
			}

			texty->add(riadok);
		}

		
		for (std::string item : *texty) {
			std::string kodUJ = "";
			std::string nazovUJ = "";
			int i = 0;
			// najprv prejdem po prvu ";" v obciach, vyfiltrujem poradove cislo, netreba mi ho, potom sa dostanem na meno obce
			while (item.at(i) != ';') {
				i++;
			}
			i++;
			while (item.at(i) != ';') {
				kodUJ += item.at(i);
				i++;
			}
			i++;
			while (item.at(i) != ';') {
				nazovUJ += item.at(i);
				i++;
			}		


			LinkedList<std::string>* list = new LinkedList<std::string>;
			list->add(nazovUJ);
			list->add(kodUJ);

			result->add(list);
		}
		return result;
	}







	structures::LinkedList<LinkedList<std::string>*>* nacitajOkresy(std::string nazovSuboru) {

		std::vector<std::vector<std::string>> content;
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(nazovSuboru, std::ios::in);
		if (file.is_open())
		{
			bool firstTime = true;
			while (getline(file, line))
			{
				if (firstTime) {
					firstTime = false;
					continue;
				}
				row.clear();

				std::stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			std::cout << "Could not open the file\n";
		}

		structures::LinkedList<std::string>* texty = new structures::LinkedList<std::string>;
		structures::LinkedList<LinkedList<std::string>*>* result = new structures::LinkedList<LinkedList<std::string>*>;

		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			if (riadok == ";;;;;") {
				break;
			}

			texty->add(riadok);
		}


		for (std::string item : *texty) {
			std::string kodUJ = "";
			std::string nazovUJ = "";
			int i = 0;
			// najprv prejdem po prvu ";" v obciach, vyfiltrujem poradove cislo, netreba mi ho, potom sa dostanem na meno obce
			while (item.at(i) != ';') {
				i++;
			}
			i++;
			while (item.at(i) != ';') {
				kodUJ += item.at(i);
				i++;
			}
			i++;

			while (item.at(i) != ';') {
				nazovUJ += item.at(i);
				i++;
			}

			nazovUJ = nazovUJ.substr(6, nazovUJ.size()); // Odstraním prvých 6 znakov z nazvov okresov "Okres "

			LinkedList<std::string>* list = new LinkedList<std::string>();
			list->add(nazovUJ);
			list->add(kodUJ);

			result->add(list);

		}

		delete texty;



		return result;
	}









	structures::LinkedList<LinkedList<std::string>*>* nacitajKraje(std::string nazovSuboru) {

		std::vector<std::vector<std::string>> content;
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(nazovSuboru, std::ios::in);
		if (file.is_open())
		{
			bool firstTime = true;
			while (getline(file, line))
			{
				if (firstTime) {
					firstTime = false;
					continue;
				}
				row.clear();

				std::stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			std::cout << "Could not open the file\n";
		}

		structures::LinkedList<std::string>* texty = new structures::LinkedList<std::string>;
		structures::LinkedList<LinkedList<std::string>*>* result = new structures::LinkedList<LinkedList<std::string>*>;

		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			if (riadok == ";;;;;") {
				break;
			}

			texty->add(riadok);
		}


		for (std::string item : *texty) {
			std::string kodUJ = "";
			std::string nazovUJ = "";
			int i = 0;
			// najprv prejdem po prvu ";" v obciach, vyfiltrujem poradove cislo, netreba mi ho, potom sa dostanem na meno obce
			while (item.at(i) != ';') {
				i++;
			}
			i++;
			while (item.at(i) != ';') {
				kodUJ += item.at(i);
				i++;
			}
			i++;

			while (item.at(i) != ';') {
				nazovUJ += item.at(i);
				i++;
			}

			kodUJ = "SK0" + kodUJ;

			LinkedList<std::string>* list = new LinkedList<std::string>;
			list->add(nazovUJ);
			list->add(kodUJ);

			result->add(list);

		}

		delete texty;



		return result;
	}



		structures::SortedSequenceTable<std::string, Vzdelanie*>* nacitajVzdelanie(std::string nazovSuboru) {

		std::vector<std::vector<std::string>> content;
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(nazovSuboru, std::ios::in);
		if (file.is_open())
		{
			bool firstTime = true;
			while (getline(file, line))
			{
				if (firstTime) {
					firstTime = false;
					continue;
				}
				row.clear();

				std::stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			std::cout << "Could not open the file\n";
		}

		structures::LinkedList<std::string>* texty = new structures::LinkedList<std::string>;
		structures::SortedSequenceTable<std::string, Vzdelanie*>* vzdelanieTable = new SortedSequenceTable<std::string, Vzdelanie*>();


		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			std::string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			riadok += ";"; // pre zistovanie ukoncenia neskor

			texty->add(riadok);

		}


		for (std::string item : *texty) {
			std::string kodUJ = "";
			structures::Array<int>* vzdelanie = new Array<int>(8);

			Vzdelanie* noveVzdelanie = new Vzdelanie();

			int i = 0;
			while (item.at(i) != ';') {
				kodUJ += item.at(i);
				i++;
			}
			i++;

			while (item.at(i) != ';') {
				i++;
			}
			i++;
			
			//tu nacitavam pocet vzdelanych ludi v konkretnom..
			for (int j = 0; j < 8; j++)
			{
				std::string vzdelaniePocetStr = "";
				while (item.at(i) != ';') {
					vzdelaniePocetStr += item.at(i);
					i++;
				}
				vzdelanie->at(j) = stoi(vzdelaniePocetStr);
				
				i++;
			}


			Vzdelanie* vzdelanieObjekt = new Vzdelanie();
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::BEZ_UKONCENEHO_VZDELANIA_DETI, vzdelanie->at(0));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::ZAKLADNE, vzdelanie->at(1));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::UCNOVSKE, vzdelanie->at(2));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::STREDNE, vzdelanie->at(3));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::VYSSIE, vzdelanie->at(4));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::VYSOKOSKOLSKE, vzdelanie->at(5));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::BEZ_VZDELANIA, vzdelanie->at(6));
			vzdelanieObjekt->navysPocetVzdelanie(TYP_VZDELANIA::NEZISTENE, vzdelanie->at(7));




			vzdelanieTable->insert(kodUJ, vzdelanieObjekt);

		}
		delete texty;



		return vzdelanieTable;
	}




};