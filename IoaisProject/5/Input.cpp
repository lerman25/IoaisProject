#include "Input.h"
Input::Input():m(0),j(0){}
Input::Input(int m, vector<array<int, N_SIZES>> jobs) : m(m), jobs(jobs) { j = jobs.size(); }
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