#pragma once

typedef std::basic_string<wchar_t> wstring;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<clocale>
#include<string>

#include "structures/list/array_list.h"
#include "structures/heap_monitor.h"



class CsvReader {


private:

	std::string nazovSuboru;


public:

	CsvReader() {};
	~CsvReader() {};


	structures::ArrayList<std::string>* nacitajObce(std::string nazovSuboru) {

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

		structures::ArrayList<std::string>* texty = new structures::ArrayList<std::string>();
		structures::ArrayList<std::string>* result = new structures::ArrayList<std::string>();

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
			result->add(nazovUJ + ";" + kodUJ);
		}
		return result;
	}







	structures::ArrayList<std::string>* nacitajOkresy(std::string nazovSuboru) {

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

		structures::ArrayList<std::string>* texty = new structures::ArrayList<std::string>;
		structures::ArrayList<std::string>* result = new structures::ArrayList<std::string>;

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

			std::string text = nazovUJ + ";" + kodUJ;

			std::cout << text << std::endl;
			result->add(text);
			
		}

		delete texty;

		

		return result;
	}




};