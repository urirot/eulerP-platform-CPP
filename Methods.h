#include <ostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class Methods
{
public:
	static bool containsPermDigits(vector<string>); 
	static int nChooseK(int, int);
	static int fact(int);
	static vector<string> readFromFile(string);
	static void createPlayerHand(multiset<int> &, string &, int);
	static int whatsTheHand(multiset<int>, string, int);
	static bool isStraight(multiset<int>);
	static int thereIsAlwaysAwinner(multiset<int>, multiset<int>, int, int);
	static int checkHighCard(multiset<int>, multiset<int>, int, int);
};