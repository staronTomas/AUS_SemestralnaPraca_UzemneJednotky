#pragma once

#include <iostream>

using namespace std;

class CsvReader
{

private:
	string nazovSuboru;


public:

	CsvReader();
	~CsvReader();

	void readFromCsv(string nazovSuboru);
};

