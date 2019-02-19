#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#ifndef SNOWGLOBE_H
#define  SNOWGLOBE_H
#include "snowglobe.h"
#endif
using namespace std;

vector<snowglobe> grabByWeightGreed(int maxWeight, vector<snowglobe> house)
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
    }
    else
    {
      return knapsack;
    }
  }
}

vector<snowglobe> grabByWeightOpt(int maxWeight, vector<snowglobe>& house)
{
  vector<snowglobe> knapsack;
  int currentWeight = 0;

  //Greedy Algorithms are implemented below
  sort(house.begin(), house.end(), sortWeight);
  while (!house.empty())
  {
    if (currentWeight+house[0].weight <= maxWeight)
    {
      knapsack.push_back(house[0]);
      currentWeight += house[0].weight;
      house.erase(house.begin());
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
  int currentWeight = 0;

  //Greedy Algorithms are implemented below
  sort(house.begin(), house.end(), sortValue);
  for( int i = 0; i < house.size(); i++ )
  {
    if (currentWeight+house[i].weight <= maxWeight)
    {
      knapsack.push_back(house[i]);
      currentWeight += house[i].weight;

      //check if we're done
      if (currentWeight == maxWeight)
      {
        return knapsack;
      }
    }
  }

  return knapsack;
}

vector<snowglobe> grabByRatio(int maxWeight, vector<snowglobe> house)
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

void recursivelyExhaustive(vector<snowglobe> house, int houseSize, int place, int maxWeight, vector<snowglobe>& bestKnapsack, int& bestValue, vector<snowglobe> currentKnapsack, int currentWeight, int currentValue)
{
  if (place == houseSize)
  {
    if (currentValue > bestValue && currentWeight <= maxWeight)
    {
      bestKnapsack = currentKnapsack;
      bestValue = currentValue;
    }

    return;
  }

  recursivelyExhaustive(house, houseSize, place+1, maxWeight, bestKnapsack, bestValue, currentKnapsack, currentWeight, currentValue);
  currentKnapsack.push_back(house[place]);
  currentWeight += house[place].weight;
  currentValue += house[place].value;
  recursivelyExhaustive(house, houseSize, place+1, maxWeight, bestKnapsack, bestValue, currentKnapsack, currentWeight, currentValue);
}

void recursivelyExhaustivePruned(vector<snowglobe> house, int houseSize, int place, int maxWeight, vector<snowglobe>& bestKnapsack, int& bestValue, vector<snowglobe> currentKnapsack, int currentWeight, int currentValue)
{
  //extra condition of currentWeight >= maxWeight added for pruning
  if (currentWeight >= maxWeight || place == houseSize)
  {
    if (currentWeight <= maxWeight && currentValue > bestValue)
    {
      bestKnapsack = currentKnapsack;
      bestValue = currentValue;
    }

    return;
  }

  recursivelyExhaustive(house, houseSize, place+1, maxWeight, bestKnapsack, bestValue, currentKnapsack, currentWeight, currentValue);
  currentKnapsack.push_back(house[place]);
  currentWeight += house[place].weight;
  currentValue += house[place].value;
  recursivelyExhaustive(house, houseSize, place+1, maxWeight, bestKnapsack, bestValue, currentKnapsack, currentWeight, currentValue);
}

vector<snowglobe> simulatedAnnealing(vector<snowglobe> knapsack, vector<snowglobe> house, int maxWeight)
{
  if (house.empty())
  {
    return knapsack;
  }
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

  // This is where the magic happens. We will go through and randomly
  // select whether to swap or add and then randomly select the
  // snowglobes we need to do either all to generate the new state
  // space.
  // We didn't randomly select subtraction because that will always
  // make the value worse so we are relying on swapping to do the same
  // function as subtraction just in one iteration rather than 2.
  // Then we will determine whether the new state space is better
  // or if we should take it even though it isn't better.
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
      loc = dist(engine) * houseCount;
      tempSnow1 = newHouseState[loc];
      newHouseState.erase(newHouseState.begin()+loc);
      // Randomly select snowglobe from knapsack
      loc = dist(engine) * (knapsackCount);
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
      loc = dist(engine) * houseCount;
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
      double Delta = newStateValue - currentValue;

      // Determine whether the new state is better and if it isn't whether
      // we should take it anyway.
      if (Delta > 0 || dist(engine) < exp(Delta/temperature))
      {
        house = newHouseState;
        knapsack = newKnapState;
        houseCount = house.size();
        knapsackCount = knapsack.size();
      }
    }

    // Get the current time so that we can run this process for only a specific
    // amount of time.
    currentTime = chrono::high_resolution_clock::now();
    compare = currentTime - startTime;
    temperature = 10000*pow((1-.0015), compare.count());
  }

  return knapsack;
}

int getValue(vector<snowglobe> knapsack)
{
  int totalValue = 0;

  for (int i = 0; i < knapsack.size(); i++)
  {
    totalValue += knapsack[i].value;
  }

  return totalValue;
}

int getWeight(vector<snowglobe> knapsack)
{
  int totalWeight = 0;

  for (int i = 0; i < knapsack.size(); i++)
  {
    totalWeight += knapsack[i].weight;
  }

  return totalWeight;
}
