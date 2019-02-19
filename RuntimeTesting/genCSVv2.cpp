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
  string files[] = {"g25.kp"};
  int numFiles = 1;
  string fileOut1 = "runtimeTest_v1start.csv";
  string fileOut2 = "runtimeTest_v2start.csv";
  ofstream fout(fileOut1, ofstream::out);
  ofstream fo2(fileOut2, ofstream::out);
  fo2 << "File, Approach, Runtime, Value, Weight, Number of Items in Knapsack" << endl;
  for (int i = 0; i < numFiles; i++)
  {
    cout << 1 << endl;
    fout << ",,,"+files[i]+",,," << endl;
    fout << ", Greedy (by weight), Greedy (by value), Greedy (by ratio), Exhaustive Search, Pruned Exhaustive Search, Optimized Greedy by Weight" << endl;
    // Declare all variables needed.
    vector<snowglobe> house;
    vector<snowglobe> knapsack;
    vector<snowglobe> temp;
    string line;
    ifstream fin;

    cout << 2 << endl;

    int numItems = 0;
    int maxWeight = 0;
    int tempValue = 0;

    string snowglobeID;
    int snowglobeWeight = 0;
    int snowglobeValue = 0;


    cout << 3 << endl;
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

    cout << 4 << endl;
    // Variables to store each time, value, weight, and number
    // of items
    chrono::duration<double, std::milli> time[6];
    int value[6];
    int weight[6];
    int number[6];

    // Get the time, value, weight, number of items in knapsack
    // at end for each method.
    cout << 5 << endl;
    auto t1 = chrono::high_resolution_clock::now();
    knapsack = grabByWeightGreed(maxWeight, house);
    auto t2 = chrono::high_resolution_clock::now();
    time[0] = t2 - t1;
    value[0] = getValue(knapsack);
    weight[0] = getWeight(knapsack);
    number[0] = knapsack.size();

    cout << 6 << endl;
    t1 = chrono::high_resolution_clock::now();
    knapsack = grabByValue(maxWeight, house);
    t2 = chrono::high_resolution_clock::now();
    time[1] = t2 - t1;
    value[1] = getValue(knapsack);
    weight[1] = getWeight(knapsack);
    number[1] = knapsack.size();

    cout << 7 << endl;
    t1 = chrono::high_resolution_clock::now();
    knapsack = grabByRatio(maxWeight, house);
    t2 = chrono::high_resolution_clock::now();
    time[2] = t2 - t1;
    value[2] = getValue(knapsack);
    weight[2] = getWeight(knapsack);
    number[2] = knapsack.size();

    cout << 8 << endl;
    t1 = chrono::high_resolution_clock::now();
    t2 = t1;
    time[3] = t2-t1;
    value[3] = 0;
    weight[3] = 0;
    number[3] = 0;

    time[4] = t2-t1;
    value[4] = 0;
    weight[4] = 0;
    number[4] = 0;

    cout << 9 << endl;
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
      fo2 << files[i] << ", " << approaches[j] << ", " << time[j].count() << ", ";
      fo2 << value[j] << ", " << weight[j] << ", " << number[j] << endl;
    }
  }

  fout.close();
  fo2.close();
}
