#include "Plugboard.h"
int PlugPos[10][2] = { {16, 3}, {9, 4}, {11, 15}, {17, 2}, {5, 24 }, { 8, 20}, {7, 22}, {6, 1}, {14, 23}, {18, 25 } };
char PlugLet[10][2];
string temp;
char let[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
// Initializes connection vector 0-25
Plugboard::Plugboard()
{
	for (int i = 0; i < 26; i++)
	{
		connections[i] = i;
	}
}

void Plugboard::createPlugboard()
{
	for (int i = 0; i < 10; i++)
	{
		temp.clear();
		printf("Plug %d goes from: ", i+1);
		getline(cin, temp);
		if (temp[0] == '-')
		{
			break;
		}
		PlugLet[i][0] = temp[0];
		cout << "To where: ";
		getline(cin, temp);
		PlugLet[i][1] = temp[0];
		PlugLet[i][0] = toupper(PlugLet[i][0]);
		PlugLet[i][1] = toupper(PlugLet[i][1]);
		for (int k = 0; k <= 25; k++) {
			if (PlugLet[i][0] == let[k]) {
				 //return correct num for the input letter
				PlugPos[i][0] = k;
			}
			if (PlugLet[i][1] == let[k]) {
				 //return correct num for the input letter
				PlugPos[i][1] = k;
			}
		}
	}
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			cout << PlugLet[j][i] << " ";
		}
		cout << endl;
	}
	*/
	cout << "test0";
}

int Plugboard::test_createPlugboard(int test_pos[10][2], char test_let[10][2])
{
	// Use test array instead of user input (only testing if correct pos is correctly extracted)
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 10; y++) {
			PlugLet[y][x] = toupper(test_let[y][x]);
		}
	}
	
	for (int i = 0; i < 10; i++)
	{
		/*
		temp.clear();
		printf("Plug %d goes from: ", i + 1);
		getline(cin, temp);
		if (temp[0] == '-')
		{
			break;
		}
		PlugLet[i][0] = temp[0];
		cout << "To where: ";
		getline(cin, temp);
		PlugLet[i][1] = temp[0];
		PlugLet[i][0] = toupper(PlugLet[i][0]);
		PlugLet[i][1] = toupper(PlugLet[i][1]);
		*/
		for (int k = 0; k < 25; k++) {
			if (PlugLet[i][0] == let[k]) {
				//return correct num for the input letter
				PlugPos[i][0] = k;
				// test case
				if (PlugPos[i][0] != test_pos[i][0]) {
					return 0;
				}
			}
			if (PlugLet[i][1] == let[k]) {
				//return correct num for the input letter
				PlugPos[i][1] = k;
				// test case
				if (PlugPos[i][1] != test_pos[i][1]) {
					return 0;
				}
			}
		}
		return 1;
	}
	/*
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			cout << PlugLet[j][i] << " ";
		}
		cout << endl;
	}
	*/
	cout << "test0";
}

// Sets the plugboard configuration and rewrites connections vector
void Plugboard::setPlugPos()
{
	for (int i = 0; i < 10; i++)
	{
		int tempi = PlugPos[i][0];
		int temp = PlugPos[i][1];
		connections[tempi] = PlugPos[i][1];
		connections[temp] = PlugPos[i][0];
	}
}

int Plugboard::test_setPlugPos(int test_swap[26])
{
	int PlugPos[10][2] = { {16, 3}, {9, 4}, {11, 15}, {17, 2}, {5, 24 }, { 8, 20}, {7, 22}, {6, 1}, {14, 23}, {18, 25 } };
	for (int i = 0; i < 10; i++)
	{
		int tempi = PlugPos[i][0];
		int temp = PlugPos[i][1];
		connections[tempi] = PlugPos[i][1];
		connections[temp] = PlugPos[i][0];
	}
	for (int i = 0; i < 26; i++) {
		if (connections[i] != test_swap[i]) {
			return 0;
		}
	}
	return 1;
}


int Plugboard::PlugSwitch(int letter)
{
	return(connections[letter]);
}

Plugboard::~Plugboard()
{

}