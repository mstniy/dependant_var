#include "dependant_var.h"
#include <iostream>

using namespace std;

int calc(int x, int y)
{
	cout << "Calculating..." << endl;
	return x+y;
}

int main()
{
	int x, y;
	dependant_var<int(int, int)> res(calc, x, y);
	x = 3;
	y = 6;
	cout << res << endl;
	cout << res << endl;
	x = 4;
	cout << res << endl;
	return 0;
}
