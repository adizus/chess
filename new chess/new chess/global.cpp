#include "stdafx.h"



#ifndef GLOBAL
#define GLOBAL

#include <string>
using namespace std;

string trim(string input) {//can it be added to string itself?
	int inputLength = input.size();
	int begin = input.find_first_not_of(" ");
	int end = input.find_last_not_of(" ");
	string newInput = input.substr(begin, end - begin - 1);
	return input;//maybe use reference
}


#endif // !GLOBAL

