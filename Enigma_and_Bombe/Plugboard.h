#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class Plugboard 
{
protected:
	std::vector<char> connections;
public:
	string encodeMessage(string input_message);
};

