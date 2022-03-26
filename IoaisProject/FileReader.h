#pragma once
#include <vector>
#include <fstream>
#include <string>
using std::ifstream;
using std::vector;
using std::string;
class FileReader
{
public:
	static vector<string> readFile(string file);
};

