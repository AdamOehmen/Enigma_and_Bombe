#pragma once

#include "pch.h"

class Reflector {
public:
	Reflector();
	Reflector(int reflectorNum);
	int reflect(int input);
protected:
	int pairings[13][2] = { 
		{21, 19},
		{3, 13},
		{20, 9},
		{8, 10},
		{18, 5},
		{11, 24},
		{25, 16},
		{15, 14},
		{0, 7},
		{12, 17},
		{22, 2},
		{1, 4},
		{6, 23} 
	};
};

