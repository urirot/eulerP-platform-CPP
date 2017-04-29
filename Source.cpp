#include <iostream>
#include <string>
#include "solveEuler.h"
#include <ctime>

void main()
{
	SolveEuler solve = SolveEuler();
	string input = "";
	cout << "which euler do you want to solve?" << endl;
	cin >> input; 

	clock_t begin = clock();

	cout << "answer is: " << solve.solver(input) << endl;

	clock_t end = clock();

	cout << "the elapsed time in secs: " << double(end - begin)/1000 << endl;

	system("PAUSE");
}