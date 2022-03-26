#pragma once
#include "FileReader.h"
#include <windows.h>
using std::ifstream;
using std::vector;
using std::string;

vector<string> FileReader::readFile(string file)
{
	ifstream input_file;
	input_file.open(file);
	vector<string> lines;
	string read = "";
	while (getline(input_file, read))
	{
		lines.push_back(read);
	}
	return lines;
}
