ECHO OFF
ECHO Compile
cd Exhaust
g++ -std=c++11 knapsack.cpp -o ..\exhaust.exe
cd ..\GreedyAlgorithms
g++ -std=c++11 knapsack.cpp -o ..\greed.exe
cd ..\Pruning
g++ -std=c++11 recursive.cpp -o ..\prune.exe
cd ..
