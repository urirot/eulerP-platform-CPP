#include "Methods.h"


//check if all numbers are permutations
bool Methods::containsPermDigits(vector<string> nums)
{
	bool sameDigits = true;
	sort(nums.at(0).begin(), nums.at(0).end());
	string curStr = nums.at(0);
	for (vector<string>::iterator it = next(nums.begin()); it != nums.end() && sameDigits; ++it)
	{
		string toCompare = *it;
		sort(toCompare.begin(), toCompare.end());
		if (toCompare.compare(curStr))
		{
			sameDigits = false;
		}
		else
		{
			curStr = toCompare;
		}
	}
	return sameDigits;
}

int Methods::nChooseK(int n, int k)
{
	if (k > 0 && (n - k > 0))
	{
		return fact(n) / (fact(k) * fact(n - k));
	}
	return 1;
}

int Methods::fact(int n)
{
	return (n == 1 || n == 0) ? 1 : fact(n - 1) * n;
}

//reads a file to a vector of strings by lines
vector<string> Methods::readFromFile(string file)
{
	string line;
	vector<string> result;
	ifstream myfile;
	myfile.open(file);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			result.push_back(line);
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	return result;
}

//methods for poker
void Methods::createPlayerHand(multiset<int> & playerNums, string & curHands, int startValue)
{
	int counter = 0;
	int tempStartValue = startValue;
	for (tempStartValue; counter < 5; tempStartValue += 3)
	{
		switch (curHands[tempStartValue])
		{
			case 'T':
				playerNums.insert(10);
				break;
			case 'J':
				playerNums.insert(11);
				break;
			case 'Q':
				playerNums.insert(12);
				break;
			case 'K':
				playerNums.insert(13);
				break;
			case 'A':
				playerNums.insert(14);
				break;
			default:
				playerNums.insert((int)curHands[tempStartValue] - 48);
		}
		counter++;
	}
	//there is a straight of ace 2 3 4 5
	if (playerNums.find(2) != playerNums.end() && playerNums.find(3) != playerNums.end() && playerNums.find(4) != playerNums.end() && playerNums.find(5) != playerNums.end() && playerNums.find(14) != playerNums.end())
	{
		playerNums.erase(14);
		playerNums.insert(1);
	}
}
bool Methods::isStraight(multiset<int> playerNums)
{
	multiset<int>::const_iterator iter = playerNums.begin();
	int curNum = *iter;
	++iter;
	while (iter != playerNums.end())
	{
		if (*iter - 1 != curNum) break;
		iter++;
		curNum++;
	}
	if (iter == playerNums.end())
	{
		return true;
	}
	return false;
}
int Methods::whatsTheHand(multiset<int> playerNums, string curHands, int flushIndex)
{
	// 0=nothing, 1=pair, 2=two pairs, 3=three of a kind, 4=straight, 5=flush, 6=full house, 7=four of a kind, 8=straight flush
	string theHand;
	int ans = 0; 

	// check for flush
	char shape = curHands[flushIndex];
	if (shape == curHands[flushIndex + 3] && shape == curHands[flushIndex + 6] && shape == curHands[flushIndex + 9] && shape == curHands[flushIndex + 12])
	{
		ans = 5;
	}
	//check for straight
	if (isStraight(playerNums))
	{
		if (ans == 5 ? ans = 8 : ans = 4);
	
	}
	for (int i = 2; i < 15; i++)
	{
		if (playerNums.count(i) == 4)
		{
			ans = 7;
		}
		if (playerNums.count(i) == 3)
		{
			theHand += "3";
		}
		if (playerNums.count(i) == 2)
		{
			theHand += "2";
		}
	}
	if (theHand == "23" || theHand == "32")
	{
		ans = 6;
	}
	if (theHand == "22")
	{
		ans = 2;
	}
	if (theHand == "2")
	{
		ans = 1;
	}
	if (theHand == "3")
	{
		ans = 3;
	}
	return ans;
}
int Methods::checkHighCard(multiset<int> player1Nums, multiset<int> player2Nums, int player1State, int player2State)
{
	for (multiset<int>::reverse_iterator i = player1Nums.rbegin(), j = player2Nums.rbegin(); i != player1Nums.rend(); ++i, ++j)
	{
		if (*i > *j)
		{
			return 1;
		}
		if (*i < *j)
		{
			return 2;
		}
	}
	return -1;
}
int Methods::thereIsAlwaysAwinner(multiset<int> player1Nums, multiset<int> player2Nums, int player1State, int player2State)
{
	int ans = -1;
	int player1Group = 0, player2Group = 0, player1Group2 = 0, player2Group2 = 0;
	//pair, three of a kind and 4 of a kind
	if (player1State == 1 || player1State == 3 || player1State == 7)
	{
		for (multiset<int>::reverse_iterator i = player1Nums.rbegin(), j = player2Nums.rbegin(); i != player1Nums.rend(); ++i, ++j)
		{
			if (player1Nums.count(*i) > 1)
			{
				player1Group = *i;
			}
			if (player2Nums.count(*j) > 1)
			{
				player2Group = *j;
			}
		}

		if (player1Group > player2Group)
		{
			return 1;
		}
		if (player1Group < player2Group)
		{
			return 2;
		}
		else
		{
			return Methods::checkHighCard(player1Nums, player2Nums, player1State, player2State);
		}
	}

	//full house
	if (player1State == 6)
	{
		for (multiset<int>::reverse_iterator i = player1Nums.rbegin(), j = player2Nums.rbegin(); i != player1Nums.rend(); ++i, ++j)
		{
			if (player1Nums.count(*i) == 3)
			{
				player1Group = *i;
			}
			if (player2Nums.count(*j) == 3)
			{
				player2Group = *j;
			}
			if (player1Nums.count(*i) == 2)
			{
				player1Group2 = *i;
			}
			if (player2Nums.count(*j) == 2)
			{
				player2Group2 = *j;
			}
		}
		if (player1Group > player2Group)
		{
			return 1;
		}
		if (player1Group < player2Group)
		{
			return 2;
		}
		if (player1Group2 > player2Group2)
		{
			return 1;
		}
		if (player1Group2 < player2Group2)
		{
			return 2;
		}
		else
		{
			return Methods::checkHighCard(player1Nums, player2Nums, player1State, player2State);
		}
	}

	if (player1State == 2)
	{

		for (multiset<int>::const_iterator i = player1Nums.begin(), j = player2Nums.begin(); i != player1Nums.end(); ++i, ++j)
		{
			if (player1Nums.count(*i) == 2)
			{
				player1Group = *i;
			}
			if (player2Nums.count(*j) == 2)
			{
				player2Group = *j;
			}
		}

		for (multiset<int>::reverse_iterator i = player1Nums.rbegin(), j = player2Nums.rbegin(); i != player1Nums.rend(); ++i, ++j)
		{
			if (player1Nums.count(*i) == 2)
			{
				player1Group2 = *i;
			}
			if (player2Nums.count(*j) == 2)
			{
				player2Group2 = *j;
			}
		}
		
		if (player1Group > player2Group)
		{
			return 1;
		}
		if (player1Group < player2Group)
		{
			return 2;
		}
		if (player1Group2 > player2Group2)
		{
			return 1;
		}
		if (player1Group2 < player2Group2)
		{
			return 2;
		}
		else
		{
			return Methods::checkHighCard(player1Nums, player2Nums, player1State, player2State);
		}		
	}
	return Methods::checkHighCard(player1Nums, player2Nums, player1State, player2State);
}