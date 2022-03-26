#include "LocalSearch.h"
using std::function;
using std::vector;
ostream& operator<<(ostream& output, Partition p)
{
	int nJobs = p.getProblem()->getJ();
	bool print_flag = true; // when false - print ',' 
	for (int i = 0; i <p.getProblem()->getM(); i++)
	{
		output << "Machine " << (i+1) << ": ";
		print_flag = true;
		for (int j = 0; j < p.getProblem()->getJ(); j++)
		{
			if (p.getAssigment()[j] == (i+1))
			{
				if (!print_flag)
				{
					output << " ,";
				}
				output << j+1 << "(" << p.getProblem()->getJobs()[j][qj]<<",";
				output << p.getProblem()->getJobs()[j][pj] << ")";
				print_flag = false;
			}
		}
		output << std::endl;
	}
	string space = "";
	output << "Total sizes: ";
	for (int m = 0; m < p.getEndTimes().size(); m++)
	{
		output <<space+"m" << (m+1) << ":" << p.getEndTimes()[m];
		space = " ";
	}
	if (p.lmax != -1)
	{
		output << std::endl<< "Target Function value: " << p.lmax << std::endl;
	}
	return output;
}
LocalSearch::LocalSearch(Input* input, vector<double>(*target_func)(Partition))
{
	this->problem = input;
	this->target_func = target_func;
	Partition newp(problem);
	this->current = newp;
}

Partition LocalSearch::runSearch()
{
	vector<Partition> ss = this->current.getSearchSpace();
	int nJobs = problem->getJ();
	double min = DBL_MAX;
	Partition maxp(Partition(this->current));
	for (Partition p : ss)
	{
		p.setEndTime(this->target_func(p));
		double tValue = TargetFunction::returnMax(p.getEndTimes(),p.getEndTimes().size());
		p.setLmax(tValue);
		if (tValue < min)
		{
			min = tValue;
			maxp = p;
		}
	}
	this->current = maxp;
	return this->current;
}
