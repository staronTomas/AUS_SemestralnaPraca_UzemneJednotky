#pragma once

typedef basic_string<wchar_t> wstring;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<clocale>
#include<string>

#include "structures/list/array_list.h"
#include "structures/heap_monitor.h"

using namespace std;




class CsvReader {


private:

	std::string nazovSuboru;


public:

	CsvReader() {};
	~CsvReader() {};


	structures::ArrayList<string>* nacitajObce(std::string nazovSuboru) {

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		fstream file(nazovSuboru, ios::in);
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

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Could not open the file\n";
		}

		structures::ArrayList<string>* texty = new structures::ArrayList<string>;
		structures::ArrayList<string>* result = new structures::ArrayList<string>;

		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			if (riadok == ";;;;;") {
				break;
			}

			texty->add(riadok);
		}

		
		for (string item : *texty) {
			string kodUJ = "";
			string nazovUJ = "";
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







	structures::ArrayList<string>* nacitajOkresy(std::string nazovSuboru) {

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		fstream file(nazovSuboru, ios::in);
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

				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else {
			cout << "Could not open the file\n";
		}

		structures::ArrayList<string>* texty = new structures::ArrayList<string>;
		structures::ArrayList<string>* result = new structures::ArrayList<string>;

		// nacitam vsetky texty z csv file
		for (int i = 0; i < content.size(); i++)
		{
			string riadok = "";
			for (int j = 0; j < content[i].size(); j++)
			{
				riadok += content[i][j];
			}

			if (riadok == ";;;;;") {
				break;
			}

			texty->add(riadok);
		}


		for (string item : *texty) {
			string kodUJ = "";
			string nazovUJ = "";
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

			string text = nazovUJ + ";" + kodUJ;

			cout << text << endl;
			result->add(text);
			
		}

		delete texty;

		cout << endl << endl << endl << endl << endl << "KONIEEEEEEEEEEEEC" << endl << endl << endl << endl << endl;

		return result;
	}




};