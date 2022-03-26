#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Loader.h"
#include "FileReader.h"
#include "LocalSearch.h"
#include "TargetFunction.h"
#include <chrono>
#include <math.h>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::ostream;
using namespace std::chrono;
enum ARGUMENTS { exe_arg,file_arg };

#define PROJECTPATH "C:\\Users\\user\\source\\repos\\IoaisProject\\IoaisProject\\"
int main(int argc, char* argv[])
{
	//freopen("myOutput.txt", "w", stdout); // saving the output to a file named "myOutput.txt" in the project directory;

	if (argc == 1)
	{
		cout << "No file in main arguemts" <<endl;
		return 0;
	};
	auto start = high_resolution_clock::now();
	Loader load(FileReader::readFile(argv[file_arg]));
	LocalSearch ls(load.getProblem(), &TargetFunction::Lmax);
	Partition initial = ls.getCurrent();
	Partition last = initial;
	Partition next = initial;
	cout<<"Initial Soultion (solution 0): " << endl << initial<<endl;
	int i = 0;
	do 
	{
		i++;
		last = next;
		next = ls.runSearch();
		std::cout << next.getMove() << endl;
		std::cout << "Solution: " << i << std::endl<<next << std::endl;
	} while (next != last);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout <<"Execution time: "<< duration.count()<<"ms"<< endl;
}

ostream& operator<<(ostream& output, Input input)
{
	output << "numMachine:" << input.m << endl;
	for (int i = 0; i < input.j; i++)
	{
		output << "j" << (i + 1) << ":" << input.jobs[i][qj] << "," << input.jobs[i][pj] << endl;
	}
	int tSum = 0;
	int qSum = 0;
	int pSum = 0; 
	for (int i = 0; i < input.j; i++)
	{
		qSum += input.jobs[i][qj];
		pSum += input.jobs[i][pj]; 
		(input.jobs[i][qj] < input.jobs[i][pj]) ? tSum += input.jobs[i][qj] : tSum += input.jobs[i][pj];
	}
	output << "total size: " << tSum <<", qj sum: "<<qSum<<", pj sum: "<<pSum<< endl;
	double tAvg = double(tSum) / double(input.m);
	double qAvg = double(qSum) / double(input.m);
	double pAVg = double(pSum) / double(input.m);
	output << "total average: " << ceil(tAvg) << endl;
	return output;
}
