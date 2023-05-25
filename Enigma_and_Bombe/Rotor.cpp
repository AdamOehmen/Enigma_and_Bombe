#include <vector>

#include "Rotor.h"

using namespace std;

Rotor::Rotor()
{
	this->position = 0;
	this->notch = 0;
}

Rotor::Rotor(int position, int notch)
{
	this->position = position;
	this->notch = notch;
}

void Rotor::rotate()
{
}

int Rotor::getPos(int input)
{

}