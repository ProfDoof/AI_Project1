//snowglobe.h has iostream and cmath
#include "snowglobe.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void outputKnapsack(vector<snowglobe> knapsack)
{
  int totalValue = 0;
  int totalWeight = 0;

  cout << "Take snowglobes ";

  for (int i = 0; i < knapsack.size(); i++)
  {
    if (totalValue == 0)
    {
      cout << knapsack[i].id;
    }
    else
    {
      cout << ", " << knapsack[i].id;
    }

    totalWeight += knapsack[i].weight;
    totalValue += knapsack[i].value;
  }

  cout << " for a total weight of " << totalWeight << " and a value of " << totalValue << "." << endl;
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

  //Exhaustive Search implemented here.
  
}
