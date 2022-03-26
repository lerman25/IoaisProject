#include "TargetFunction.h"
using std::vector;
 vector<double> TargetFunction::Lmax(Partition p)
{
    Input* input = p.getProblem();
    vector<double> endtimes;
    for (int i = 0; i < input->getM(); i++)
        endtimes.push_back(0);
    int  i = 0;
    for ( i = 0; i < input->getJ(); i++)
    {
        // in arrary that the index is a machine
        // the index start from 0, in arrays that the index holds
        // a machine, the machine start from 1.
        int machine = p.getAssigment()[i];
        int time = input->getJobs()[i][machine % 2];
        if (machine == 0)
        {
            std::cout << "Error with indexing" << std::endl;
            exit(1);
        }
        endtimes[machine-1] = endtimes[machine-1]+time ;
    }
    return endtimes;
}
 double TargetFunction::sumSqrd(vector<double> array, int length)
 {
     double sum = 0;
     for (int i = 0; i < length; i++)
     {
         sum += array[i];
     }
     return -(sum * sum);
 }
 double TargetFunction::returnMax(double* array, int length)
 {
     double max = -1;
     int max_index = -1;
     for (int m = 0; m < length; m++)
     {
         if (array[m] > max)
         {
             max = double(array[m]);
             max_index = m;
         }
     }
     return max;
 }

 double TargetFunction::returnMax(vector<double> array, int length)
 {
         double max = -1;
     int max_index = -1;
     for (int m = 0; m < length; m++)
     {
         if (array[m] > max)
         {
             max = double(array[m]);
             max_index = m;
         }
     }
     return max;
 }
