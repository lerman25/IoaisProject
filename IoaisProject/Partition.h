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
	double targetVal;
	double scnTargetVal;
	vector<double> endtimes;
	string move;
public:
	Partition() { assigment = NULL; targetVal = -1; scnTargetVal = -1; problem = NULL; move = ""; };
	Partition(Input* problem);
	Partition(const Partition &other);
	void operator=(const Partition& other);
	bool operator<(Partition& other);
	bool operator>(Partition& other);
	friend bool operator==(Partition& lhs, Partition& rhs);
	friend bool operator!=(Partition& lhs, Partition& rhs);
	friend ostream& operator<<(ostream& output, Partition p);
	int* getAssigment() const { return assigment; };
	Input* getProblem() const { return problem; };
	void setTargetVal(double targetVal) { this->targetVal = targetVal; };
	void setScnTargetVal(double targetVal) { this->scnTargetVal = targetVal; };
	vector<double> getEndTimes() { return endtimes; };
	void setEndTime(vector<double> endTimes) { this->endtimes = endTimes; };
	vector<Partition> getSearchSpace();
	string getMove() { return move; };
	void setMove(string move) { this->move = move; };
	~Partition();
};

