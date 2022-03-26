#include "Input.h"
Input::Input():m(0),j(0){}
using std::rand;
using std::srand;
using std::time;
Input::Input(int m, vector<array<int, N_SIZES>> jobs) : m(m), jobs(jobs) { j = jobs.size(); }
Input Input::generateRandom(int nm,int nj,int mj,bool mflag,bool jflag)
{
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	int m = nm;
	// machine number [2,nm]
	if (!mflag)
	{ 
		m += 1;
		while(m>nm)
			m=2 + std::rand() / ((RAND_MAX + 1u) / nm);  // Note: 1+rand()%6 is biased
	}
	int j = nj;
	// jobs number [10,nj]
	if (!jflag)
	{
		j += 1;
		while (j>nj)
			j = 10 + std::rand() / ((RAND_MAX + 1u) / nj);
	}
	vector<array<int, N_SIZES>> jobs;
	for (int i = 0; i < j; i++)
	{
		//pq value [1,mj]
		int pt = mj+1;
		int qt = mj+1;
		array<int, N_SIZES> time;
		while(pt>mj)
			pt = 1 + std::rand() / ((RAND_MAX + 1u) / mj);
		while(qt>mj)
			qt = 1 + std::rand() / ((RAND_MAX + 1u) / mj);
		time[pj] = pt;
		time[qj] = qt;
		jobs.push_back(time);
	}
	Input randInput(m, jobs);
	
	
	return randInput;
}
Input Input::generateInc(int nm, int nj)
{
	int m = nm;
	int j = nj;
	vector<array<int, N_SIZES>> jobs;
	for (int i = 1; i <= j; i++)
	{
		//pq value (i,i+1)
		int pt = i;
		int qt = i + 1;
		array<int, N_SIZES> time;
		time[pj] = pt;
		time[qj] = qt;
		jobs.push_back(time);
	}
	Input incInput(m, jobs);
	return incInput;
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