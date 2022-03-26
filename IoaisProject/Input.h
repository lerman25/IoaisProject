#pragma once
#define N_SIZES 2 
#include <iostream>
#include <array>
#include <vector>
using std::vector;
using std::array;
using std::ostream;
enum Type {qj,pj};
class Input
{
	int m;
	int j;
	vector<array<int, N_SIZES>> jobs;
public: 
	Input();
	Input(int m, vector<array<int, N_SIZES>> jobs);
	int getM() { return m; };
	int getJ() { return j; };
	vector<array<int, N_SIZES>> getJobs() { return jobs; };
	friend ostream& operator<<(ostream& output, Input input);
	friend bool operator==(Input lhs, Input rhs);
	friend bool operator!=(Input lhs, Input rhs);
};

