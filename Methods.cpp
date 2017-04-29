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