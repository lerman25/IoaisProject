#include "Partition.h"
using std::to_string;
Partition::Partition(Input* input):problem(input)
{
	targetVal = -1;
	move = "";
	assigment = new int[problem->getJ()];
	if (!assigment)
	{
		std::cout << "can't allocate memory" << std::endl;
		exit(1);
	}
	for (int i = 0; i < problem->getJ(); i++)
	{
		//Every job is initilized to be at machine 1
		assigment[i] = 1;
	}
}
Partition::Partition(const Partition& other)
{
	problem = other.getProblem();
	targetVal = other.targetVal;
	endtimes = other.endtimes;
	move = other.move;
	int* new_assigment = new int[problem->getJ()];
	if (!new_assigment)
	{
		std::cout << "can't allocate memory" << std::endl;
		exit(1);
	}
	for (int i = 0; i < problem->getJ(); i++)
	{
		new_assigment[i] = other.getAssigment()[i];
	}
	assigment = new_assigment;
}
void Partition::operator=(const Partition& other)
{
	problem = other.getProblem();
	targetVal = other.targetVal;
	endtimes = other.endtimes;
	move = other.move;
	int* new_assigment = new int[problem->getJ()];
	if (!new_assigment)
	{
		std::cout << "can't allocate memory" << std::endl;
		exit(1);
	}
	for (int i = 0; i < problem->getJ(); i++)
	{
		new_assigment[i] = other.getAssigment()[i];
	}
	delete[] assigment;
	assigment = new_assigment;
}
vector<Partition> Partition::getSearchSpace()
{
	vector<Partition> ss;
	int nJobs = this->getProblem()->getJ();
	int nM = this->getProblem()->getM();
	ss.push_back(*this);
	for (int i = 0; i < nJobs; i++)
	{
		for (int j = 0; j < nM; j++)
		{
			Partition newP(*this);
			if (newP.getAssigment()[i] != (j+1))
			{
				newP.setMove("Moving job "+ to_string(i+1) +" from machine " + to_string(newP.getAssigment()[i]) + " to machine "+ to_string(j+1));
				newP.getAssigment()[i] = (j+1);
				ss.push_back(newP);
			}
		}
	}
	return ss;
}
Partition::~Partition()
{
	delete[] assigment;
}
using std::ostream;

bool operator==(Partition& lhs, Partition& rhs)
{
	if (lhs.problem != rhs.problem)
		return false;
	int nJobs = lhs.problem->getJ();
	for (int i = 0; i < nJobs; i++)
	{
		if (lhs.assigment[i] != rhs.assigment[i])
			return false;
	}
	return true;
}
bool operator!=(Partition& lhs, Partition& rhs)
{
	return !(lhs == rhs);
}
