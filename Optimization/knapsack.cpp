//snowglobe.h has iostream and cmath
#include "snowglobe.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

vector<snowglobe> simulatedAnnealing(vector<snowglobe> knapsack, vector<snowglobe> house, int maxWeight)
{
  // Generate random seed and other random tools
  random_device rd{};
  mt19937 engine{rd()};
  uniform_real_distribution<double> dist{0.0, 1.0};

  // Generate all timing variables that will be used to change the temperature
  auto startTime = chrono::high_resolution_clock::now();
  auto currentTime = startTime;
  chrono::duration<double, std::milli> compare = currentTime - startTime;

  // Define variables that will be consistently used in while loop
  int houseCount = house.size();
  int knapsackCount = knapsack.size();
  int addCount;
  long swapCount;
  long totalNumOptions;
  double chance;

  double temperature = 10000;

  while ( compare.count() < 5500 )
  {
    // The temporary vectors and snowglobes to check.
    snowglobe tempSnow1;
    snowglobe tempSnow2;
    vector<snowglobe> newKnapState;
    vector<snowglobe> newHouseState;

    // The number of options to choose from for the random options
    addCount = houseCount;
    swapCount = houseCount*knapsackCount;
    totalNumOptions = addCount+swapCount;
    chance = dist(engine) * totalNumOptions;

    // Define the currentWeight and newStateWeight and Delta
    int currentWeight = 0;
    int currentValue = 0;
    int newStateWeight = 0;
    int newStateValue = 0;

    // Randomly select either swap or add (if or else respectively)
    if (chance < swapCount)
    {
      int loc;

      // Set the new states equal to the old states
      newHouseState = house;
      newKnapState = knapsack;

      // Act on the new states
      // Randomly select snowglobe from house
      loc = dist(engine) * houseCount);
      tempSnow1 = newHouseState[loc];
      newHouseState.erase(newHouseState.begin()+loc);

      // Randomly select snowglobe from knapsack
      loc = dist(engine) * (knapsackCount+1);
      tempSnow2 = newKnapState[loc];
      newKnapState.erase(newKnapState.begin()+loc);

      // Add Randomly selected snowglobes to the respective new states.
      newHouseState.push_back(tempSnow2);
      newKnapState.push_back(tempSnow1);
    }
    else
    {
      int loc;

      // Set the new states equal to the old states
      newHouseState = house;
      newKnapState = knapsack;

      // Act on the new states
      // Randomly select snowglobe from house
      loc = dist(engine) * houseCount);
      tempSnow1 = newHouseState[loc];
      newHouseState.erase(newHouseState.begin()+loc);

      // Add Randomly selected snowglobes to the respective new states.
      newKnapState.push_back(tempSnow1);
    }

    for (int i = 0; i < knapsackCount; i++)
    {
      currentWeight += knapsack[i].weight;
      currentValue += knapsack[i].value;
    }

    for (int i = 0; i < newKnapState.size(); i++)
    {
      newStateWeight += newKnapState[i].weight;
      newStateValue += newKnapState[i].value;
    }

    // Check that the new state generated is valid.
    if (newStateWeight <= maxWeight)
    {
      // Calculate Delta
      Delta = newStateValue - currentValue;

      // Determine whether the new state is better and if it isn't whether
      // we should take it anyway.
      if (Delta > 0 || dist(engine) < exp(Delta/temperature)
      {
        house = newHouseState;
        knapsack = newKnapState;
      }
    }
    currentTime = chrono::high_resolution_clock::now();
    compare = currentTime - startTime;
    temperature = 10000*pow((1-.0015), compare.count());
  }
}

vector<snowglobe> grabByWeight(int maxWeight, vector<snowglobe>& house)
{
  vector<snowglobe> knapsack;
  int currentWeight = 0;

  //Greedy Algorithms are implemented below
  sort(house.begin(), house.end(), sortWeight);
  for (int i = 0; i < house.size(); i++)
  {
    if (currentWeight+house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;
      house.erase(house.begin() + i);
    }
    else
    {
      return knapsack;
    }
  }
}

vector<snowglobe> grabByValue(int maxWeight, vector<snowglobe>& house)
{
  vector<snowglobe> knapsack;
  int currentWeight = 0;

  //Greedy Algorithms are implemented below
  sort(house.begin(), house.end(), sortValue);
  for( int i = 0; i < house.size(); i++ )
  {
    if (currentWeight+house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;
      house.erase(house.begin() + i);

      //check if we're done
      if (currentWeight == maxWeight)
      {
        return knapsack;
      }
    }
  }

  return knapsack;
}

vector<snowglobe> grabByRatio(int maxWeight, vector<snowglobe>& house)
{
  vector<snowglobe> knapsack;
  int currentWeight = 0;

  //Greedy Algorithms are implemented below
  sort(house.begin(), house.end(), sortRatio);
  for (int i = 0; i < house.size(); i++)
  {
    if (currentWeight + house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;
      house.erase(house.begin() + i);

      //check if we're done
      if (currentWeight == maxWeight)
      {
        return knapsack;
      }
    }
  }

  return knapsack;
}

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
  auto t1 = chrono::high_resolution_clock::now();
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
  auto t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> fp_ms = t2 - t1;

  cout << endl << "File Input time: " << fp_ms.count() << endl;

  //Greedy Algorithms called here.
  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByWeight(maxWeight, house);
  t2 = chrono::high_resolution_clock::now();
  fp_ms = t2 - t1;
  cout << "By Weight:" << endl;
  outputKnapsack(knapsack);
  cout << endl;
  cout << "Weight time: " << fp_ms.count() << endl;

  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByValue(maxWeight, house);
  t2 = chrono::high_resolution_clock::now();
  fp_ms = t2 - t1;
  cout << "By Value:" << endl;
  outputKnapsack(knapsack);
  cout << endl;
  cout << "Value time: " << fp_ms.count() << endl;

  t1 = chrono::high_resolution_clock::now();
  knapsack = grabByRatio(maxWeight, house);
  t2 = chrono::high_resolution_clock::now();
  fp_ms = t2 - t1;
  cout << "By Value-to-Weight Ratio:" << endl;
  outputKnapsack(knapsack);
  cout << "Value-to-Weight time: " << fp_ms.count() << endl;
}
