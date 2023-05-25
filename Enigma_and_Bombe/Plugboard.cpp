#include "Plugboard.h"
Plugboard::Plugboard()
{
	for (int i = 0; i < 24; i++)
	{
		connections[i] = i + 1;
	}
}

string Plugboard::encodeMessage(string input_message)
{
	// TODO: everything
	return "";
}

void Plugboard::setPlugPos(int PlugPos[])
{
	for (int i = 0; i < 2; i++)
	{
		int tempi = PlugPos[i];
		int temp = connections[tempi];
		connections[tempi] = PlugPos[i + 1];
		connections[temp] = PlugPos[i];
	}
}


void Plugboard::getPlugPos()
{

}

Plugboard::~Plugboard()
{

}