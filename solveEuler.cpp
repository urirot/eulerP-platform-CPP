#include "solveEuler.h"

SolveEuler::SolveEuler()
{
	func_map["52"] = &SolveEuler::prob52;
	func_map["53"] = &SolveEuler::prob53;
	func_map["54"] = &SolveEuler::prob54;
}

// call an euler function via an invoking function
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

/*-----------------------------------------euler problems-----------------------------------------------*/
/*------------------------------------------------------------------------------------------------------*/

/*It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
answer - 142857, computation time:3.896*/
int SolveEuler::prob52()
{
	int ans = 0;
	int i = 2; 
	bool found = false;
	vector<string> nums(6);

	while (!found)
	{
		if (to_string(i)[0] == '1' && to_string(i)[to_string(i).length()] != '0')
		{
			nums.at(0) = to_string(i);
			nums.at(1) = to_string(i * 2);
			nums.at(2) = to_string(i * 3);
			nums.at(3) = to_string(i * 4);
			nums.at(4) = to_string(i * 5);
			nums.at(5) = to_string(i * 6);

			if (Methods::containsPermDigits(nums))
			{
				found = true;
				ans = i;
			}
		}
		i++;
	}

	return ans;
}

/*There are exactly ten ways of selecting three from five, 12345:
123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
In combinatorics, we use the notation, 5C3 = 10.
In general,nCr =	n! -> r!(n−r)! ,where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one-million?*/
int SolveEuler::prob53()
{
	int ans = 0;
	int pascalTriangle[101][101];
	for (int n = 0; n < 100; n++)
	{
		for (int k = 0; k < 100; k++)
		{
			pascalTriangle[n][k] = 1;
		}
	}
	for (int n = 1; n <= 100; n++)
	{
		for (int k = 1; k < n; k++)
		{
			pascalTriangle[n][k] = pascalTriangle[n - 1][k] + pascalTriangle[n - 1][k - 1];
			if (pascalTriangle[n][k] > 999999)
			{
				pascalTriangle[n][k] = 1000000;
				ans++;
			}
		}
	}
	return ans;
}

/*The file, poker.txt, contains one-thousand random hands dealt to two players.
Each line of the file contains ten cards (separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards.
You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.
How many hands does Player 1 win?*/
int SolveEuler::prob54()
{	
	int player1Wins = 0, player2Wins = 0;
	vector<string> hands = Methods::readFromFile(string("resources/p054_poker.txt")); 

	//go over a line (two hands)
	for (vector<string>::const_iterator i = hands.begin(); i != hands.end(); ++i)
	{
		string curHands = *i;
		int player1State, player2State;
		multiset<int> player1Nums, player2Nums;
		
		//create a multi set of one hand for each player
		Methods::createPlayerHand(player1Nums, curHands, 0);
		Methods::createPlayerHand(player2Nums, curHands, 15);

		//check which hand each player has
		player1State = Methods::whatsTheHand(player1Nums, curHands, 1);
		player2State = Methods::whatsTheHand(player2Nums, curHands, 16);

		if (player1State > player2State)
		{
			player1Wins++;
		}
		if (player1State < player2State)
		{
			player2Wins++;
		}
		if (player1State == player2State)
		{
			if (Methods::thereIsAlwaysAwinner(player1Nums, player2Nums, player1State, player2State) == 1 ? player1Wins++ : player2Wins++);
		}
	}
	
	return player1Wins;
}