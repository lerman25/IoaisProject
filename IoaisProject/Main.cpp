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
enum ARGUMENTS { exe_arg,file_arg,num_arg};
void createInputFiles();
vector<Input> createInputs(int num);
void mainGen(int argc, char* argv[]);
#define PROJECTPATH "C:\\Users\\user\\source\\repos\\IoaisProject\\IoaisProject\\"
int main(int argc, char* argv[])
{
	//freopen("myOutput.txt", "w", stdout); // saving the output to a file named "myOutput.txt" in the project directory;

	if (argc == 1)
	{
		cout << "Missing argument, GEN for generated output, file for output from file" <<endl;
		return 0;
	};
	if (string(argv[1]) == string("GEN"))
	{
		mainGen(argc,argv);
		return 0;
	}
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
#define IFILES 10
void createInputFiles()
{
	string input = "inputs/input";
	for (int i = 1; i <= IFILES; i++)
	{
		ofstream ifile;
		ifile.open(input + std::to_string(i)+".txt");
		ifile << Input::generateRandom();
		ifile.close();
	}
	return;
}
vector<Input> createInputs(int num)
{
	vector<Input> inputs;
	for (int i = 0; i < num; i++)
		inputs.push_back(Input::generateRandom());
	return inputs;
}
void mainGen(int argc, char* argv[])
{
	int num = 10;
	if (argc == 3)
	{
		num = stoi(string(argv[num_arg]));
	}
	cout << "Creating "<<num<<" generated Input and Outputs..." << endl;
	vector<Input> inputs = createInputs(num);
	for (int in = 0; in < inputs.size(); in++)
	{
		string input = "examples/input";
		ofstream ifile;
		ifile.open(input + std::to_string(in) + ".txt");
		ifile << inputs[in];
		ifile.close();
		//Loader load(FileReader::readFile(argv[file_arg]));
		LocalSearch ls(&inputs[in], &TargetFunction::Lmax);
		Partition initial = ls.getCurrent();
		Partition last = initial;
		Partition next = initial;
		ofstream ofile;
		ofile.open("examples/output" + std::to_string(in) + ".txt");
		ofile << inputs[in] << std::endl;
		ofile << "Initial Soultion (solution 0): " << endl << initial << endl;
		int i = 0;
		do
		{
			i++;
			last = next;
			next = ls.runSearch();
			ofile << next.getMove() << endl;
			ofile << "Solution: " << i << std::endl << next << std::endl;
		} while (next != last);
	}
}