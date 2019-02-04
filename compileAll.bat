ECHO OFF
ECHO Compile
cd Exhaust
g++ -std=c++11 knapsack.cpp -o ..\exhaust.exe
cd ..\GreedyAlgorithms
g++ -std=c++11 knapsack.cpp -o ..\greed.exe
cd ..\Pruning
g++ -std=c++11 recursive.cpp -o ..\prune.exe
cd ..
echo.
echo.
echo Run Datasets with exe
echo.
echo -----------------------------------MarWitData1---------------------------
echo.
echo DataSets\MarWitData1.kp | exhaust.exe
echo.
echo DataSets\MarWitData1.kp | greed.exe
echo.
echo DataSets\MarWitData1.kp | prune.exe
echo.

echo -----------------------------------MarWitData2---------------------------
echo.
echo DataSets\MarWitData2.kp | exhaust.exe
echo.
echo DataSets\MarWitData2.kp | greed.exe
echo.
echo DataSets\MarWitData2.kp | prune.exe
echo.

echo -----------------------------------MarWitData3---------------------------
echo.
echo DataSets\MarWitData3.kp | exhaust.exe
echo.
echo DataSets\MarWitData3.kp | greed.exe
echo.
echo DataSets\MarWitData3.kp | prune.exe
echo.

echo -----------------------------------MarWitData4---------------------------
echo.
echo DataSets\MarWitData4.kp | greed.exe
echo.
echo DataSets\MarWitData4.kp | prune.exe
echo.

echo -----------------------------------MarWitData5---------------------------
echo.
echo DataSets\MarWitData5.kp | greed.exe
echo.
echo DataSets\MarWitData5.kp | prune.exe
echo.
