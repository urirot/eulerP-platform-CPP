#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Methods.h"

using namespace std;
typedef int(*FUNCPTR)(); // our typedef


class SolveEuler {

public:
	SolveEuler();
	// some functions
	int solver(const string& which);

private: 
	map<string, FUNCPTR> func_map;
	static int prob52();
	static int prob53();
};