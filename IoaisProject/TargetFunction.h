#pragma once
#include "Input.h"
#include "Partition.h"
using std::vector;
class TargetFunction
{
public:
	static vector<double> Lmax(Partition p);
	static double returnMax(double* array, int length);
	static double returnMax(vector<double> array, int length);
};

