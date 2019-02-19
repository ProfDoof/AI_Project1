Project 1 ReadMe

The code implementing the three greedy algorithms is in the folder "GreedyAlgorithms." snowglobe.h contains the definition of the snowglobe struct used in the program, and knapsack.cpp contains the implementations of the greedy algorithms.

The code implementing the exhaustive search is in the folder "Exhaust." snowglobe.h contains the definition of the snowglobe struct used in the program, knapsack.cpp contains a binary array implementation of an exhaustive search, and recursice.cpp contains a recursive implementation of an exhaustive search.

The code implementing the pruned search is in the folder "Pruning." snowglobe.h contains the definition of the snowglobe struct used in the program, and recursive.cpp contains the pruned recursive implementation.

The code implementing the simulated annealing optimization is in the folder "Optimization." snowglobe.h contains the definition of the snowglobe struct used in the program, and knapsack.cpp contains the implementations of the optimization.

Compile the programs using the c++11 standard. Then, run the program(s) and enter the path to the file (including the name) containing the test data when prompted. The code will output the resulting knapsack.

In the folder "RuntimeTesting" there is code for two methods of generating the data for the runtime assignment. generateCSV.cpp sequentially runs every file throwing their data into two different csv's. One which implements a crosstab format and one which simply does many lines of data. quickGenCSV.cpp runs every single file at the same time leveraging fork and generates a csv for every file. Their is then a formatCSV.cpp that takes all of those csv's and combines them into the same kind of csv's seen in the generateCSV.cpp.

All batch files were generated merely for own convenience and need no explanation. The Data Sets folder contains testing data used in class and generated for the data sets assignment.