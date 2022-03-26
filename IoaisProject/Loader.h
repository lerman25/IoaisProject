#pragma once
#include <fstream>
#include "Input.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::ofstream;
class Loader
{
	Input* problem;
public:
	Loader(vector<string> lines);
	Input* getProblem() { return problem; };
	~Loader() {delete problem;};
};

