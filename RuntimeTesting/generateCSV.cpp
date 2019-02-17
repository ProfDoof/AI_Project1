#ifndef SNOWGLOBE_H
#define  SNOWGLOBE_H
#include "snowglobe.h"
#endif
#include "methods.h"
#include <fstream>
#include <sstream>

using namespace std;

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
  string fileOut = "runtimeTest.csv";
  ofstream fout(fileOut, ofstream::out);
  for (int i = 0; i < 1; i++)
  {
    fout << ",,,"+files[i]+",,," << endl;
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
    fin.open(files[i].c_str());

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
    cout << knapsack.size();

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
    cout << knapsack.size();

    t1 = chrono::high_resolution_clock::now();
    knapsack = grabByWeightOpt(maxWeight, house);
    knapsack = simulatedAnnealing(knapsack, house, maxWeight);
    t2 = chrono::high_resolution_clock::now();
    time[5] = t2 - t1;
    value[5] = getValue(knapsack);
    weight[5] = getWeight(knapsack);
    number[5] = knapsack.size();

    fout << "runtime";
    for (int i = 0; i < 6; i++)
    {
      fout << "," << time[i].count();
    }
    fout << endl;

    fout << "value";
    for (int i = 0; i < 6; i++)
    {
      fout << "," << value[i];
    }
    fout << endl;

    fout << "weight";
    for (int i = 0; i < 6; i++)
    {
      fout << "," << weight[i];
    }
    fout << endl;

    fout << "numItemsInKnapsack";
    for (int i = 0; i < 6; i++)
    {
      fout << "," << number[i];
    }
    fout << endl;
    fout << ",,,,,," << endl;
  }
}
