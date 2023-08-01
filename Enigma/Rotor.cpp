#include <vector>
#include <iostream>
#include <sstream>
#include "Rotor.h"
int lettersToNum(char letter);
char Alp[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
string query;
sqlite3* dab;
int YN = 0;
string str_scramble = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

// Default Constructor, sets start position and notch to '0' 
// and reference rotor to NULL if no values are given
static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

string pull_rotor_set(int rotor) {
	int exit = sqlite3_open("enigma_bombe.db", &dab); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		//cout << "open success" << endl;
	}
	string query = "SELECT rotorSetting FROM Rotor_Settings WHERE rotorName = " + to_string(rotor) + ";";	// SQL statement selecting rotor setting
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(dab, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(dab) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Rotor Doesn't exist" << endl;	// Check if plugboard exists
	}

	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size

	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	sqlite3_finalize(stmt); // Finalize the statement
	sqlite3_close(dab);	// close dab
	return result;
}
int pull_rotor_notch(int rotor) {
	int exit = sqlite3_open("enigma_bombe.db", &dab); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		//cout << "open success" << endl;
	}
	string query = "SELECT notch FROM Rotor_Settings WHERE rotorName = " + to_string(rotor) + ";";	// SQL statement selecting rotor setting
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(dab, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(dab) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Rotor Doesn't exist" << endl;	// Check if plugboard exists
	}

	int result = sqlite3_column_int(stmt, 0);	// save notch value into result
	sqlite3_finalize(stmt); // Finalize the statement
	sqlite3_close(dab);	// close dab
	return result;
}

Rotor::Rotor()
{
	int exit = 0;
	char temp;
	sqlite3_stmt* stmt;
	query = "SELECT * FROM Rotor_Settings;";
	int pullm = sqlite3_open("enigma_bombe.db", &dab); // open database
	if (pullm != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else
	{
		sqlite3_exec(dab, query.c_str(), callback, NULL, NULL);
	}


	while (1) {
		cout << "These are the current rotors" << endl;
		cout << "Would you like to create a new one? (Y/N): ";
		string ClearWhenAddingDataBase;
		cin >> ClearWhenAddingDataBase;
		cin.ignore();

		if (ClearWhenAddingDataBase == "N")
		{
			cout << "Which rotors would you like to use: ";
			cin >> this->rtrName;
			cin.ignore();
			this->scramble = pull_rotor_set(this->rtrName);
			cout << "Setting is " << this->scramble << endl;
			for (int i = 0; i < this->scramble.length(); i++)
			{
				this->scramble[i] = lettersToNum(this->scramble[i]);
			}
			this->notch = pull_rotor_notch(this->rtrName);
			YN = 0;
			break;
		}
		else if (ClearWhenAddingDataBase == "Y")
		{
			UI_Scramble();
			UI_Notch();
			YN = 1;
			break;
		}
		else
		{
			cout << "Please Enter Y or N" << endl;
		}

	}

}

int Rotor::getName()
{
	return this->rtrName;
}

// Returns notch position
int Rotor::getNotch()
{
	return this->notch;
}

string Rotor::getStrScramble()
{
	return this->StrScm;
}

string Rotor::getScramble()
{
	
	return this->scramble;
}

// Simulates a rotation of the Rotor by incrementing its position 
// value and wrapping around to 0 when the position hits 25
void Rotor::rotate()
{
	if (this->position == 25)
	{
		this->position = 0;
	}
	else
	{
		position++;
	}
}

// Returns the Rotors new value based on the previous Rotor's output
// param input: the position outputted by the previous output
// returns output: the new scrambled position value
int Rotor::getScramblePos(int input)
{
	if (input >= 0 && input < 26)
	{
		// simulate rotation
		int newInput = (input + position) % 26;
		return this->scramble[newInput];
	}
	else
	{
		cout << "Invalid position argument for Rotor::getScramblePos" << endl;
		return -1;
	}
}

// Find the position of a value, to work through the rotor backwards
int Rotor::getReversePos(int input)
{
	int result;
	if (input >= 0 && input < 26)
	{
		// Check all positions on the rotor
		for (int i = 0; i <= 25; i++) {
			if (this->scramble[i] == input) {
				// calculate rotations by subtracting it from the result, then doing a mod (and if the result of mod is negative, make it positive by cycling back around)
				int result = (i - position) % 26;
				if (result < 0) {
					result += 26;
				}
				return result;
			}
		}
	}
	else {
		cout << "Invalid input value for Rotor::getReversePos" << endl;
		return -1;
	}
}

int Rotor::getPos() {
	return this->position;
}

void Rotor::UI_Notch()
{
	string temp;
	while (1)
	{
		cout << "What letter is the notch at: ";
		getline(cin, temp);
		char notch_Let = temp[0];
		notch = lettersToNum(notch_Let);
		if (notch >= 0 && notch < 26)
		{
			this->notch = notch;
			break;
		}
		else
		{
			cout << "Invalid notch value" << endl;
			this->notch = 0;
		}
	}
}

void Rotor::UI_Scramble()
{
	char ctemp;
	string sttemp;
	for (int i = 0; i < 26; i++)
	{
		while (1)
		{

			cout << Alp[i] << " is link to: ";
			getline(cin, sttemp);
			ctemp = sttemp[0];
			ctemp = toupper(ctemp);
			sttemp = ctemp;
			try {
				int value = stoi(sttemp);
				cout << "Invalid input. Please enter a Letter." << endl;
				continue;
			}
			catch (const std::invalid_argument& e) {
				cout << "You entered: " << sttemp << endl;
				break;
			}
		}
		for (int j = 0; j < 26; j++)
		{
			if (lettersToNum(ctemp) == this->scramble[j])
			{
				cout << sttemp << " is already attached" << endl;
				i--;
				break;
			}
			else if (j == 25)
			{
				this->StrScm = this->StrScm + ctemp;
				this->scramble[i] = lettersToNum(ctemp);
			}
		}
		//Add stuff for dab
	}
}

int Rotor::getYN()
{
	return YN;
}


Rotor::~Rotor()
{
}


int lettersToNum(char letter) {
	// convert input letter to uppercase
	letter = toupper(letter);

	try {
		// iterate thru letters array
		for (int i = 0; i <= 25; i++) {
			if (letter == Alp[i]) {
				// return correct num for the input letter
				return i;
			}
		}
		// throw error if input letter isn't between A-Z
		throw(letter);
	}
	// print error message, return 99 (code for a blank space)
	catch (char wrongChar) {
		cout << "Error in function letterToNum: Input char (" << wrongChar << ") not in alphabet\n";
		return 99;
	}
}

Rotor::Rotor(int newScramble[], int newNotch) {
	for (int i = 0; i <= 25; i++) {
		this->scramble[i] = newScramble[i];
	}
	this->notch = newNotch;
}
