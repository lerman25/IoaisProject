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
	if (p.targetVal != -1)
	{
		output << std::endl<< "Target Function value: " << p.targetVal << std::endl;
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
	this->current.setEndTime(this->target_func(this->current));
	double tValue = TargetFunction::returnMax(this->current.getEndTimes(), this->current.getEndTimes().size());
	this->current.setTargetVal(tValue);
	this->current.setScnTargetVal(TargetFunction::sumSqrd(this->current.getEndTimes(), this->current.getEndTimes().size()));
	Partition minp(Partition(this->current));
	for (Partition p : ss)
	{
		p.setEndTime(this->target_func(p));
		double tValue = TargetFunction::returnMax(p.getEndTimes(),p.getEndTimes().size());
		p.setTargetVal(tValue);
		p.setScnTargetVal(TargetFunction::sumSqrd(p.getEndTimes(), p.getEndTimes().size()));
		if (p < minp)
		{
			minp = p;
		}
		
	}
	this->current = minp;
	return this->current;
}
