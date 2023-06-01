#include "Plugboard.h"
Plugboard::Plugboard()
{
	for (int i = 0; i < 26; i++)
	{
		connections[i] = i;
	}
}

void Plugboard::setPlugPos(int PlugPos[])
{
	for (int i = 0; i < 10; i+=2)
	{
		int tempi = PlugPos[i];
		int temp = PlugPos[i+1];
		connections[tempi] = PlugPos[i + 1];
		connections[temp] = PlugPos[i];
	}
}


int Plugboard::PlugSwitch(int letter)
{
	return(connections[letter]);
}

Plugboard::~Plugboard()
{

}