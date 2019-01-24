#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
	vector <int> weight;
	vector <int> value;
	int items;
	int maxWeight;
	int dummy;

	cout << "Enter # of items: ";
	cin >> items;
	cout << "Enter max weight: ";
	cin >> maxWeight;

	cout << "Enter list of weights: ";
	for( int i = 0; i < items; i++ )
	{
		cin >> dummy;
		weight.push_back(dummy);
	}

	cout << "Enter list of values: ";
	for( int i = 0; i < items; i++ )
	{
		cin >> dummy;
		value.push_back(dummy);
	}

	cout << endl << endl;
	cout << "Output:\n----------------" << endl;
	cout << items << ", " << maxWeight << endl;

	string id = "";
	int idNum = 1;
	for( int i = 0; i < items; i++ )
	{
		cout << i+1 << ", " << weight[i] << ", " << value[i] << endl;
	}
}