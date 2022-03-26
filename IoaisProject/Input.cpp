#include "Input.h"
Input::Input():m(0),j(0){}
using std::rand;
using std::srand;
using std::time;
Input::Input(int m, vector<array<int, N_SIZES>> jobs) : m(m), jobs(jobs) { j = jobs.size(); }
Input Input::generateRandom()
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	// machine number [2,10]
	int m = 11;
	while(m>10)
		m=2 + std::rand() / ((RAND_MAX + 1u) / 10);  // Note: 1+rand()%6 is biased
	// jobs number [10,25]
	int j = 26;
	while (j>25)
		j = 10 + std::rand() / ((RAND_MAX + 1u) / 25);

	vector<array<int, N_SIZES>> jobs;
	for (int i = 0; i < j; i++)
	{
		//pq value [1,15]
		int pt = 16;
		int qt = 16;
		array<int, N_SIZES> time;
		while(pt>15)
			pt = 1 + std::rand() / ((RAND_MAX + 1u) / 15);
		while(qt>15)
			qt = 1 + std::rand() / ((RAND_MAX + 1u) / 15);
		time[pj] = pt;
		time[qj] = qt;
		jobs.push_back(time);
	}
	Input randInput(m, jobs);
	
	
	return randInput;
}
bool operator==(Input lhs, Input rhs)
{
	if (lhs.m != rhs.m)
		return false;
	int lnJobs = lhs.jobs.size();
	if (lnJobs != rhs.jobs.size())
		return false;
	for (int i = 0; i < lnJobs; i++)
	{
		if (lhs.jobs[i] != rhs.jobs[i])
			return false;
	}
	return true;
}
bool operator!=(Input lhs, Input rhs)
{
	return !(lhs == rhs);
}