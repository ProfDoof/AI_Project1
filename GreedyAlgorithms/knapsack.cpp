//snowglobe.h has iostream and cmath
#include "snowglobe.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  //create the vector to hold all the snowglobes (and the other variables)
  vector<snowglobe> house;
  string filename;
  string line;
  ifstream fin;

  //get the input file
  cout << "Enter filename: ";
  cin >> filename;

  //open the file and read in the snowglobes
  fin.open(filename.c_str());

  if (fin.is_open())
  {
    //the first line has num items and max weight, so do that separately
    getline(fin, line);
    cout << "before: " << line << endl;
    //replace the commas with spaces
    replace(line.begin(), line.end(), ',', ' ');
    cout << "after: " << line << endl;
  }
  else
  {
    cout << "Could not open file." << endl;
  }

  fin.close();
}
