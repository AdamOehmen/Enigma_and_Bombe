#include "../Enigma/pch.h"
#include "../Enigma/Reflector.h"
#include "../Enigma/Plugboard.h"
#include "../Enigma/Rotor.h"
#include "../Enigma/functions.h"
#include "../Enigma/sqlite3.h"

// return the rotors used for the given message number, as a string of format "#,#,#," where # is the rotor number in that slot
string getRotorsUsed(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getMessageRotorSettings" << endl;
		exit(0);
	}

	string query = "SELECT rotorUsed FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}
	
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No rotor setting found for msg #" << msgNum << endl;
		exit(0);
	}

	// iterate through each character of rotorUsed and store into a string
	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char rotor = sqlite3_column_text(stmt, 0)[i];
		result = result + rotor;
	}

	// delete unused spaces and add a comma at the end (so that # of commas = # of rotors)
	return delSpaces(result) + ",";
}

// returns the total number of rotors used in encrypting the given message number
int getNumRotorsUsed(int msgNum) {
	// get the string of rotors used for the msg
	string rotorStr = getRotorsUsed(msgNum);

	// count # of commas in the string, which is equal to the number of rotors
	int count = 0;
	for (int i = 0; i < rotorStr.length(); i++) {
		if (rotorStr[i] == ',') {
			count++;
		}
	}

	return count;
}

// returns the plugboard number used in encrypting the given message number
string getPlugboardUsed(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getMessagePlugboardUsed" << endl;
		exit(0);
	}

	string query = "SELECT plugUsed FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No plugboard setting found for msg #" << msgNum << endl;
		exit(0);
	}

	int plug = sqlite3_column_int(stmt, 0);
	query = "SELECT plugSettings FROM Plugboard_Settings WHERE plugName = '" + to_string(plug) + "'";

	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No plugboard setting found for msg #" << msgNum << endl;
		exit(0);
	}

	// iterate through each character of plugSettings and store into a string
	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char plug = sqlite3_column_text(stmt, 0)[i];
		result = result + plug;
	}

	return result;
}

// gets the rotor scramble of the given rotor number from the Rotors table
string getRotorScramble(int rotorNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);

	string query = "SELECT rotorSetting FROM Rotor_Settings WHERE rotorName = '" + to_string(rotorNum) + "'";

	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No rotor setting found for rotor #" << rotorNum << endl;
		exit(0);
	}

	// iterate through each character of rotorSetting and store into string
	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char let = sqlite3_column_text(stmt, 0)[i];
		result = result + let;
	}
	
	return result;
}

int getRotorNotch(int rotorNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);

	string query = "SELECT notch FROM Rotor_Settings WHERE rotorName = '" + to_string(rotorNum) + "'";

	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No rotor setting found for rotor #" << rotorNum << endl;
		exit(0);
	}

	int result = sqlite3_column_int(stmt, 0);

	return result;
}

string getEncryptedMessage(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getEncryptedMessage" << endl;
		exit(0);
	}

	string query = "SELECT encryptedMsg FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No message #" << msgNum << " found." << endl;
		exit(0);
	}
	
	// iterate through each character of encryptedMsg and store in result string
	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char nextLetter = sqlite3_column_text(stmt, 0)[i];
		result = result + nextLetter;
	}

	return result;
}

// ask the user to pick a message from the database to decrypt
int selectMessage() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in selectMessage" << endl;
		exit(0);
	}

	string query = "SELECT messageOrder, encryptedMsg FROM Past_Messages";
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
		exit(0);
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No past messages found. Run the Enigma program and enter some messages to get started!" << endl;
		exit(0);
	}

	// print messages table and store message #s into a vector
	cout << "#\tMessage" << endl << "---------------" << endl;
	vector<int> messages;
	bool exit = false;
	do {
		string message = "";
		int length = sqlite3_column_bytes(stmt, 1);
		for (int i = 0; i < length; i++) {
			char nextChar = sqlite3_column_text(stmt, 1)[i];
			message = message + nextChar;
		}
		messages.push_back(sqlite3_column_int(stmt, 0));

		cout << sqlite3_column_int(stmt, 0) << "\t" << message << endl;

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_ROW) {
			exit = true;
		}
	} while (exit == false);

	int result;
	exit = false;
	// get input from user
	do {
		cout << "Enter the # of the message you'd like to decode: ";
		cin >> result;
		if (result < 1) {
			cout << "Unrecognized input, try again." << endl;
			cin.clear();
			cin.ignore(1);
			result = 0;
			continue;
		}
		// make sure user input is in the message # vector
		if (find(messages.begin(), messages.end(), result) != messages.end()) {
			exit = true;
		}
		else {
			cout << "Unrecognized message number, please try again." << endl;
			result = 0;
		}
	} while (exit == false);

	cin.clear();
	cin.ignore(1);

	return result;
}

int main() {
	cout << "Welcome to Bombe." << endl;

	int selectedMessage = selectMessage();
	cout << "Selected message #" << selectedMessage << endl;
	string encodedMessage = getEncryptedMessage(selectedMessage);
	encodedMessage = delSpaces(encodedMessage);

	// Map encoded message string to a vector
	int messageSize = encodedMessage.size();
	vector <int> plainNum(messageSize);

	// Create plugboard
	Plugboard plug{};
	string plugboardUsed = getPlugboardUsed(selectedMessage);
	cout << "Using plugboard: " << plugboardUsed << endl;
	plug.DB_Extract(plugboardUsed);
	plug.setPlugPos();

	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(encodedMessage[i]);
	}
	
	// Create reflector with hardcoded values
	Reflector reflector;

	int numRotors = getNumRotorsUsed(selectedMessage);
	string rotorsStr = getRotorsUsed(selectedMessage);
	vector<int> rotorNums;
	string currentRotor = "";
	for (int i = 0; i < rotorsStr.length(); i++) {
		if (rotorsStr[i] == ',') {
			rotorNums.push_back(stoi(currentRotor));
			currentRotor = "";
		} else {
			currentRotor = currentRotor + string(1, rotorsStr[i]);
		}
	}

	// Create a vector with all of the rotors so we can iterate through it
	vector<Rotor> rotors;
	for (int i = 0; i < numRotors; i++) {
		int scramble[26];
		string scrambleStr = getRotorScramble(rotorNums[i]);
		cout << "Using rotor #" << rotorNums[i] << ": " << scrambleStr << endl;
		for (int j = 0; j < 26; j++) {
			scramble[j] = letterToNum(scrambleStr[j]);
		}
		int notch = getRotorNotch(rotorNums[i]);
		rotors.push_back(Rotor(scramble, notch));
	}

	for (int i = 0; i < messageSize; i++)
	{
		cout << "Encrypted letter: " << numToLetter(plainNum[i]) << endl;

		// Send input through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
		}

		// Send output of first pass thru rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);

		// Send reflector output through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
		}

		// Send through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);

		// Print final letter to screen
		cout << "Unencrypted letter: " << numToLetter(plainNum[i]) << endl << endl;

		// Rotate rotor #1 after every decrypted input letter
		rotors[0].rotate();
		cout << "ROTATE ROTOR 1" << endl;

		bool lastRotated = true;
		for (int k = 1; k < numRotors; k++) {
			// Rotate the next rotor IF the notch of the previous matches the current position, AND the previous just rotated
			if ((rotors[k - 1].getNotch() == rotors[k - 1].getPos()) && lastRotated) {
				rotors[k].rotate();
				cout << "ROTATE ROTOR " << (k + 1) << endl;
				lastRotated = true;
			}
			// Otherwise, update value of lastRotated
			else {
				lastRotated = false;
			}
		}
		cout << endl;
	}

	// print out final decrypted message
	cout << "Final decrypted message: ";
	for (int i = 0; i < plainNum.size(); i++) {
		cout << numToLetter(plainNum[i]);
	}

	return 0;
}