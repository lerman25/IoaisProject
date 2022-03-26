#pragma once
#include "FileReader.h"
#include <windows.h>
using std::ifstream;
using std::vector;
using std::string;
vector<string> FileReader::split(string str, char splitter)
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
using std::cout;
using std::endl;
vector<string> FileReader::readFile(string file)
{
    vector<string> splits = FileReader::split(file, '.');
    if (splits.size() == 1)
    {
        cout << "Problem with file arguemt! not a file..." << endl;
        exit(1);
    }
    if (splits[1] != "txt")
    {
        cout << "Problem with file arguemt! not a file..." << endl;
        exit(1);
    }
	ifstream input_file;
	input_file.open(file);
    if (input_file.bad())
    {
        cout << "Problem with file arguemt! not a file..." << endl;
        exit(1);
    }
	vector<string> lines;
	string read = "";
	while (getline(input_file, read))
	{
		lines.push_back(read);
	}
	return lines;
}
