#ifndef SNOWGLOBE_H
#define  SNOWGLOBE_H
#include "snowglobe.h"
#endif
#include "methods.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

int main() 
{
  string files[] = {"a21.kp","a23.kp","a25.kp","a30.kp", "a31.kp",
                    "b21.kp","b23.kp","b25.kp","b30.kp", "b31.kp",
                    "c21.kp","c23.kp","c25.kp","c30.kp", "c31.kp",
                    "d21.kp","d23.kp","d25.kp","d30.kp", "d31.kp",
                    "e21.kp","e23.kp","e25.kp","e30.kp", "e31.kp",
                    "f21.kp","f23.kp","f25.kp","f30.kp", "f31.kp",
                    "g23.kp","g24.kp","g25.kp","g26.kp"};
  int numFiles = 34;
  string fileOut1 = "runtimeTest_v1.csv";
  string fileOut2 = "runtimeTest_v2.csv";
  string line;
  ifstream fin;
  ifstream fi2;
  ofstream fout(fileOut1, ofstream::out);
  ofstream fo2(fileOut2, ofstream::out);
  fo2 << "File, Approach, Runtime, Value, Weight, Number of Items in Knapsack" << endl;

  for (int i = 0; i < 2; i++)
  {
    string filename = files[i];
    filename.erase(filename.end()-3,filename.end());
    string filename2 = filename +"v2.csv";
    filename += "v1.csv";
    fin.open(filename.c_str());
    while (getline(fin, line))
    {
      fout << line << endl;
    }
    fin.close();
    fi2.open(filename2.c_str());
    while (getline(fi2, line))
    {
      fo2 << line << endl;
    }
  }

  fout.close();
  fo2.close();
}