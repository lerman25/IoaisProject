#pragma once
#include "Input.h"
#include <functional>
#include <array>
#include <vector>
#include <string>
using std::array;
using std::vector;
using std::function;
using std::ostream;
using std::string;
class Partition
{
	Input* problem;
	int* assigment;
	double lmax;
	vector<double> endtimes;
	string move;
public:
	Partition() { assigment = NULL; lmax = -1; problem = NULL; move = ""; };
	Partition(Input* problem);
	Partition(const Partition &other);
	void operator=(const Partition& other);
	friend bool operator==(Partition& lhs, Partition& rhs);
	friend bool operator!=(Partition& lhs, Partition& rhs);
	friend ostream& operator<<(ostream& output, Partition p);
	int* getAssigment() const { return assigment; };
	Input* getProblem() const { return problem; };
	void setLmax(double lmax) { this->lmax = lmax; };
	vector<double> getEndTimes() { return endtimes; };
	void setEndTime(vector<double> endTimes) { this->endtimes = endTimes; };
	vector<Partition> getSearchSpace();
	string getMove() { return move; };
	void setMove(string move) { this->move = move; };
	~Partition();
};

