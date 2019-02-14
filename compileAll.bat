ECHO OFF
ECHO Compile
g++ -std=c++11 .\Exhaust\knapsack.cpp -o exhaust.exe
g++ -std=c++11 .\GreedyAlgorithms\knapsack.cpp -o greed.exe
g++ -std=c++11 .\Pruning\recursive.cpp -o prune.exe
g++ -std=c++11 .\Optimization\knapsack.cpp -o optimized.exe
