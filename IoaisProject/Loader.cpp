#include "Loader.h"
#include <iostream>
#include <array>

using std::string;
using std::vector;
using std::array;
enum Format{machine_line,jobs_line};
vector<string> split(string str, char splitter)
{
    std::vector<std::string> result;
    std::string current = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == splitter) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.size() != 0)
        result.push_back(current);
    return result;
}
vector<array<int,N_SIZES>> parse_jobs(vector<string> lines)
{
    vector<array<int,N_SIZES>> jobs;
    for (string str : lines)
    {
        if (str[0] == 'j')
        {
            string job =split(str, ':')[1];
            array<int,N_SIZES> time;
            time[pj] = stoi(split(job, ',')[pj]);
            time[qj] = stoi(split(job, ',')[qj]);
            jobs.push_back(time);
        }
    }
    return jobs;

}
Loader::Loader(vector<string> lines)
{
	std::cout << "loading Input"<<std::endl;
    string machines = lines.at(machine_line);
    int nmachines = stoi(split(machines, ':')[1]);
    vector<array<int,N_SIZES>> jobs = parse_jobs(lines);
    this->problem =new  Input(nmachines, jobs);
    std::cout << *problem<<std::endl;
}
