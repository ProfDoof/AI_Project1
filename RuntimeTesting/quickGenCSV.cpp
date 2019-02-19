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

using namespace std;

void individualProcess(string filename)
{
  string trueFile = filename;
  trueFile.erase(trueFile.end()-3,trueFile.end());
  string fileOut1 = trueFile+"v1.csv";
  string fileOut2 = trueFile+"v2.csv";
  ofstream fout(fileOut1, ofstream::out);
  ofstream fo2(fileOut2, ofstream::out);
  fout << ",,,"+filename+",,," << endl;
  fout << ", Greedy (by weight), Greedy (by value), Greedy (by ratio), Exhaustive Search, Pruned Exhaustive Search, Optimized Greedy by Weight" << endl;
  // Declare all variables needed.
  vector<snowglobe> house;
  vector<snowglobe> knapsack;
  vector<snowglobe> temp;
  string line;
  ifstream fin;

  int numItems = 0;
  int maxWeight = 0;
  int tempValue = 0;

  string snowglobeID;
  int snowglobeWeight = 0;
  int snowglobeValue = 0;

  //open the file and read in the snowglobes
  fin.open(filename.c_str());

  if (fin.is_open())
  {
    //the first line has num items and max weight, so do that separately
    getline(fin, line);

    //replace the commas with spaces
    replace(line.begin(), line.end(), ',', ' ');

    //now we get the two numbers
    stringstream ss(line);
    ss >> numItems >> maxWeight;

    //loop through the rest of the file to get the snowglobes
    for (int i = 0; i < numItems; i++)
    {
      //read in the line and replace the commas
      getline(fin, line);
      replace(line.begin(), line.end(), ',', ' ');
      stringstream ssSnowglobe(line);

      //get the individual components and put them into a struct
      ssSnowglobe >> snowglobeID >> snowglobeWeight >> snowglobeValue;
      snowglobe current;
      current.id = snowglobeID;
      current.weight = snowglobeWeight;
      current.value = snowglobeValue;
      current.ratio = (double)(snowglobeValue) / snowglobeWeight;

      //put the snowglobe into the house
      house.push_back(current);
    }
  }
  else
  {
    cout << "Could not open file." << endl;
  }

  fin.close();
  // Variables to store each time, value, weight, and number
  // of items
  chrono::duration<double, std::milli> time[6];
  int value[6];
  int weight[6];
  int number[6];

  // Get the time, value, weight, number of items in knapsack
  // at end for each method.
  auto t1 = chrono::high_resolution_clock::now();
  knapsack = grabByWeightGreed(maxWeight, house);
  auto t2 = chrono::high_resolution_clock::now();
  time[0] = t2 - t1;
  value[0] = getValue(knapsack);
  weight[0] = getWeight(knapsack);
  number[0] = knapsack.size();

  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByValue(maxWeight, house);
  t2 = chrono::high_resolution_clock::now();
  time[1] = t2 - t1;
  value[1] = getValue(knapsack);
  weight[1] = getWeight(knapsack);
  number[1] = knapsack.size();

  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByRatio(maxWeight, house);
  t2 = chrono::high_resolution_clock::now();
  time[2] = t2 - t1;
  value[2] = getValue(knapsack);
  weight[2] = getWeight(knapsack);
  number[2] = knapsack.size();


  t1 = chrono::high_resolution_clock::now();
  recursivelyExhaustive(house, numItems, 0, maxWeight, knapsack, tempValue, temp, 0, 0);
  t2 = chrono::high_resolution_clock::now();
  time[3] = t2 - t1;
  value[3] = getValue(knapsack);
  weight[3] = getWeight(knapsack);
  number[3] = knapsack.size();

  // Because of the way that the pruned exhaustive search is implemented
  // we need to reset the knapsack before we use it.
  knapsack.erase(knapsack.begin(), knapsack.end());
  temp.erase(temp.begin(), temp.end());
  tempValue = 0;

  t1 = chrono::high_resolution_clock::now();
  recursivelyExhaustivePruned(house, numItems, 0, maxWeight, knapsack, tempValue, temp, 0, 0);
  t2 = chrono::high_resolution_clock::now();
  time[4] = t2 - t1;
  value[4] = getValue(knapsack);
  weight[4] = getWeight(knapsack);
  number[4] = knapsack.size();

  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByWeightOpt(maxWeight, house);
  knapsack = simulatedAnnealing(knapsack, house, maxWeight);
  t2 = chrono::high_resolution_clock::now();
  time[5] = t2 - t1;
  value[5] = getValue(knapsack);
  weight[5] = getWeight(knapsack);
  number[5] = knapsack.size();

  fout << "runtime";
  for (int j = 0; j < 6; j++)
  {
    fout << "," << time[j].count();
  }
  fout << endl;

  fout << "value";
  for (int j = 0; j < 6; j++)
  {
    fout << "," << value[j];
  }
  fout << endl;

  fout << "weight";
  for (int j = 0; j < 6; j++)
  {
    fout << "," << weight[j];
  }
  fout << endl;

  fout << "numItemsInKnapsack";
  for (int j = 0; j < 6; j++)
  {
    fout << "," << number[j];
  }
  fout << endl;
  fout << ",,,,,," << endl;
  string approaches[] = {"Greedy By Weight", "Greedy By Value",
                         "Greedy By Ratio", "Exhaustive Search",
                         "Pruned Exhaustive Search",
                         "Optimized Greedy by Weight"};

  for (int j = 0; j < 6; j++)
  {
    fo2 << filename << ", " << approaches[j] << ", " << time[j].count() << ", ";
    fo2 << value[j] << ", " << weight[j] << ", " << number[j] << endl;
  }

  fout.close();
  fo2.close();
  cout << "Completed fork for " << filename << endl;
}

int main()
{
  // A list of all files so that we can pick and choose which ones we
  // want or can just run all of them.
  string files[] = {"a21.kp","a23.kp","a25.kp","a30.kp", "a31.kp",
                    "b21.kp","b23.kp","b25.kp","b30.kp", "b31.kp",
                    "c21.kp","c23.kp","c25.kp","c30.kp", "c31.kp",
                    "d21.kp","d23.kp","d25.kp","d30.kp", "d31.kp",
                    "e21.kp","e23.kp","e25.kp","e30.kp", "e31.kp",
                    "f21.kp","f23.kp","f25.kp","f30.kp", "f31.kp",
                    "g23.kp","g24.kp","g25.kp","g26.kp"};
  int numFiles = 34;
  for (int i = 0; i < numFiles; i++)
  {
    pid_t pid = fork();
    if (pid > 0)
    {
      individualProcess(files[i]);
      i = numFiles;
    }
    else if (pid == 0)
    {
      cout << "fork succeeded for " << files[i] << endl;
    }
    else
    {
      cout << "fork failed for " << files[i] << endl;
    }
  }

  while (true)
  {
    int status;
    pid_t done = wait(&status);
    if (done == -1)
    {
        if (errno == ECHILD) break; // no more child processes
    }
    else
    {
      if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
      {
          cerr << "pid " << done << " failed" << endl;
          exit(1);
      }
    }
  }
}
