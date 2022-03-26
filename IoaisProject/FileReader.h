#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using std::ifstream;
using std::vector;
using std::string;
class FileReader
{
public:
	static vector<string> readFile(string file);
	static vector<string> split(string str, char splitter);
};

