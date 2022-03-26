#pragma once
#include <iostream>
#include "Input.h"
#include <functional>
#include "Partition.h"
#include <algorithm>
#include "TargetFunction.h"
using std::function;
class LocalSearch
{
	Input* problem;
	Partition current;
	vector<double>(*target_func)(Partition);
public:
	LocalSearch(Input* input, vector<double>(*target_func)(Partition));
	Partition runSearch();
	Partition getCurrent() const { return current; };
};

