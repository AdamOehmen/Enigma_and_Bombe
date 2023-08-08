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

void Plugboard::DB_Extract(string db_setting) {
	int temp = 0;
	// Extracts DB settings and stores into PlugLet
	// Essentially createPlugboard() but pulls data from DB
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0) {
				PlugLet[j][i] = db_setting[temp];
				temp = temp + 2;
			}
			else if (i == 1) {
				PlugLet[j][i] = db_setting[temp + 1];
				temp = temp + 2;
			}
		}
		temp = 0;
	}
	// Converts Letters to Num
	for (int i = 0; i < 10; i++){
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
		bool containsSpecialCharacters = false;
		for (char c : temp) {
			if (!isalpha(c)) { // Check if the character is an alphabet letter
				containsSpecialCharacters = true;
				break;
			}
		}
		
		if (containsSpecialCharacters) {
			cout << "Invalid input. Please enter letters only." << endl << endl;
			i--;
		}
		else {
			// No special characters found, we can proceed

			PlugLet[i][0] = temp[0];
			cout << "To where: ";
			getline(cin, temp);
			for (char c : temp) {
				if (!isalpha(c)) { // Check if the character is an alphabet letter
					containsSpecialCharacters = true;
					break;
				}
			}

			if (containsSpecialCharacters) {
				cout << "Invalid input. Please enter letters or words only." << endl << endl;
				i--;
			}
			else {
				// No special characters found, we can proceed
				temp[0] = toupper(temp[0]);
				PlugLet[i][1] = temp[0];
			}
		}
		if (i == 0 && (PlugLet[0][0] == PlugLet[0][1]))
		{
			cout << "Plugs must go to different positions." << endl;
			i--;
		}
		for (int k = 0; k <= i; k++)
		{
			for (int n = 0; n <= i; n++) {
				if (PlugLet[n][0] == PlugLet[k][1] || k != n && (PlugLet[n][0] == PlugLet[k][0] || PlugLet[n][1] == PlugLet[k][1])) {
					cout << "Plugs must go to different positions." << endl;
					i--;
					k = i;
					break;
				}
			}
		}
		
	}
	
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k <= 25; k++) {
				if (PlugLet[i][j] == let[k]) {
					PlugPos[i][j] = k;
				}
			}
		}
	}
}

string Plugboard::returnPlugLet() {
	string result = "";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 2; j++) {
			result = result + PlugLet[i][j];
		}
	}
	return result;
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