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
#include <cstdlib>
#include <ctime>
using std::rand;
using std::srand;
using std::time;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::ostream;
using namespace std::chrono;
enum ARGUMENTS { exe_arg,file_arg,num_arg};
void createInputFiles();
vector<Input> createInputs(int num, int argc=0, int* argv=NULL,bool incFlag=false);
void mainGen(int argc, char* argv[]);
void mainInc(int argc, char* argv[]);
#define PROJECTPATH "C:\\Users\\user\\source\\repos\\IoaisProject\\IoaisProject\\"
int main(int argc, char* argv[])
{
	std::srand(std::time(nullptr));
	//freopen("myOutput.txt", "w", stdout); // saving the output to a file named "myOutput.txt" in the project directory;

	if (argc == 1)
	{
		cout << "Missing argument, GEN for generated output, file for output from file" <<endl;
		return 0;
	};
	if (string(argv[1]) == string("RAND"))
	{
		mainGen(argc,argv);
		return 0;
	}
	if (string(argv[1]) == string("INC"))
	{
		mainInc(argc, argv);
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
vector<Input> createInputs(int num,int argc,int* argv,bool incFlag)
{
	vector<Input> inputs;
	cout << "generating with "<<argc << " args"<<endl;
	for (int i = 0; i < num; i++)
	switch (argc)
	{
		case 0:
			if(incFlag)
				inputs.push_back(Input::generateInc());
			else
				inputs.push_back(Input::generateRandom());
			break;
		case 1:
			if (incFlag)
				inputs.push_back(Input::generateInc(argv[0]));
			else
				inputs.push_back(Input::generateRandom(argv[0]));
			break;
		case 2:
			if (incFlag)
				inputs.push_back(Input::generateInc(argv[0], argv[1]));
			else
				inputs.push_back(Input::generateRandom(argv[0], argv[1]));
			break;
		case 3:
			if (incFlag)
				inputs.push_back(Input::generateInc(argv[0], argv[1]));
			inputs.push_back(Input::generateRandom(argv[0], argv[1], argv[2]));
			break;
		case 4:
			if (incFlag)
				inputs.push_back(Input::generateInc(argv[0], argv[1]));
			inputs.push_back(Input::generateRandom(argv[0], argv[1], argv[2],bool(argv[3]),bool(argv[4])));
			break;
		default:
			cout << "Error with Input generation arguments" << endl;
			exit(1);
	}
	return inputs;
}
void mainGen(int argc, char* argv[])
{
	int num = 10;
	if (argc >= 3)
	{
		num = stoi(string(argv[num_arg]));
	}
	cout << "Creating "<<num<<" generated random Input and Outputs..." << endl;
	int* argvi = new int[argc];
	int j = 0;
	for(int i = num_arg+1; i < argc; i++)
	{
		argvi[j] = std::stoi(argv[i]);
		j++;
	}
	vector<Input> inputs = createInputs(num,j,argvi);
	delete[] argvi;
	auto start = high_resolution_clock::now();
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
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Execution time: " << duration.count() << "ms" << endl;
	cout << "Avg time: " << duration.count() / num << "ms" << endl;
}
void mainInc(int argc, char* argv[])
{
	int num = 10;
	if (argc >= 3)
	{
		num = stoi(string(argv[num_arg]));
	}
	cout << "Creating " << num << " generated incremented Input and Outputs..." << endl;
	int* argvi = new int[argc];
	int j = 0;
	for (int i = num_arg + 1; i < argc; i++)
	{
		argvi[j] = std::stoi(argv[i]);
		j++;
	}
	vector<Input> inputs = createInputs(num, j, argvi,true);
	delete[] argvi;
	auto start = high_resolution_clock::now();
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
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Execution time: " << duration.count() << "ms" << endl;
	cout << "Avg time: " << duration.count()/num << "ms" << endl;

}