//snowglobe.h has iostream and cmath
#include "snowglobe.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<snowglobe> grabByWeight(int maxWeight, vector<snowglobe> house)
{
  vector<snowglobe> knapsack;
  int currentWeight;

  //Greedy Algorithms are implemented below
  currentWeight = 0;
  sort(house.begin(), house.end(), sortWeight);
  for (int i = 0; i < house.size(); i++)
  {
    if (currentWeight+house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;
    }
    else
    {
      return knapsack;
    }
  }
}

vector<snowglobe> grabByValue(int maxWeight, vector<snowglobe> house)
{
  vector<snowglobe> knapsack;
  int currentWeight;

  //Greedy Algorithms are implemented below
  currentWeight = 0;
  sort(house.begin(), house.end(), sortValue);
  for( int i = 0; i < house.size(); i++ )
  {
    if (currentWeight+house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;
    }
  }

  return knapsack;
}

vector<snowglobe> grabByRatio(int maxWeight, vector<snowglobe> house)
{
  vector<snowglobe> knapsack;
  int currentWeight;

  //Greedy Algorithms are implemented below
  currentWeight = 0;
  sort(house.begin(), house.end(), sortRatio);

  return knapsack;
}

void outputKnapsack(string sortedBy, vector<snowglobe> knapsack)
{
  int totalValue = 0;
  cout << "Sorted by "+sortedBy+"\n-------------------" << endl;
  for (int i = 0; i < knapsack.size(); i++)
  {
    cout << knapsack[i].id << " " << knapsack[i].weight << " " << knapsack[i].value << " " << knapsack[i].ratio << endl;
    totalValue += knapsack[i].value;
  }
  cout << endl;
  cout << "Total Value of Snowglobes stolen from Dr. Pettit/Reeves via this method is $" << totalValue << endl << endl;
}

int main()
{
  //create the vector to hold all the snowglobes (and the other variables)
  vector<snowglobe> house;
  vector<snowglobe> knapsack;
  string filename;
  string line;
  ifstream fin;

  int numItems = 0;
  int maxWeight = 0;

  string snowglobeID;
  int snowglobeWeight = 0;
  int snowglobeValue = 0;

  //get the input file
  cout << "Enter filename: ";
  cin >> filename;

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

  //Greedy Algorithms called here. totalValue is passed by reference so that you can have the changed version.
  knapsack = grabByWeight(maxWeight, house);
  outputKnapsack("Weight",knapsack);

  knapsack = grabByValue(maxWeight, house);
  outputKnapsack("Value",knapsack);

  knapsack = grabByRatio(maxWeight, house);

  outputKnapsack("Ratio of Value to Weight",knapsack);


}
