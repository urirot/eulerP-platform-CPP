#include "solveEuler.h"

SolveEuler::SolveEuler()
{
	func_map["52"] = &SolveEuler::prob52;
}

// call them via an invoking function
int SolveEuler::solver(const std::string& which)
{
	if (func_map.find(which) != func_map.end()) // indeed the function was added
		return func_map[which]();
	else
	{
		std::cerr << "Function \"" << which << "\" is not in the map!\n";
		return -1; // or throw
	}
}

/*It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
answer - 142857, computation time:slow*/
int SolveEuler::prob52()
{
	int ans = 0;
	int i = 2; 
	bool found = false;
	vector<string> nums(6);

	while (!found)
	{
		nums.at(0) = to_string(i);
		nums.at(1) = to_string(i*2);
		nums.at(2) = to_string(i*3);
		nums.at(3) = to_string(i*4);
		nums.at(4) = to_string(i*5);
		nums.at(5) = to_string(i*6);

		if (Methods::containsPermDigits(nums))
		{
			found = true;
			ans = i;
		}
		i++;
	}

	return ans;
}

int SolveEuler::prob53()
{
	return 0;
}

