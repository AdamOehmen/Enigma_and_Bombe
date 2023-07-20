#include "../Enigma_and_Bombe/pch.h"
#include "../Enigma_and_Bombe/Reflector.h"
#include "../Enigma_and_Bombe/Plugboard.h"
#include "../Enigma_and_Bombe/Rotor.h"
#include "../Enigma_and_Bombe/functions.h"
#include "../Enigma_and_Bombe/sqlite3.h"

string getRotorsUsed(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma_and_Bombe/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getMessageRotorSettings" << endl;
	}

	string query = "SELECT rotorUsed FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
	}
	
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No rotor setting found for msg #" << msgNum << endl;
	}

	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char rotor = sqlite3_column_text(stmt, 0)[i];
		result = result + rotor;
	}

	return result;
}

int getNumRotorsUsed(int msgNum) {
	string rotorStr = getRotorsUsed(msgNum);

	int count = 0;
	for (int i = 0; i < rotorStr.length(); i++) {
		if (rotorStr[i] == ',') {
			count++;
		}
	}

	return count;
}

int getPlugboardUsed(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma_and_Bombe/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getMessagePlugboardUsed" << endl;
	}

	string query = "SELECT plugUsed FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No plugboard setting found for msg #" << msgNum << endl;
	}

	int plug = sqlite3_column_int(stmt, 0);
	query = "SELECT plugSettings FROM Plugboard_Settings WHERE plugName = '" + to_string(plug) + "'";

	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No plugboard setting found for msg #" << msgNum << endl;
	}

	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char plug = sqlite3_column_text(stmt, 0)[i];
		result = result + plug;
	}

	cout << result;

	return 0;
}

string getEncryptedMessage(int msgNum) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma_and_Bombe/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in getEncryptedMessage" << endl;
	}

	string query = "SELECT encryptedMsg FROM Past_Messages WHERE messageOrder = " + to_string(msgNum);
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No message #" << msgNum << " found." << endl;
	}

	string result = "";
	int length = sqlite3_column_bytes(stmt, 0);
	for (int i = 0; i < length; i++) {
		char nextLetter = sqlite3_column_text(stmt, 0)[i];
		result = result + nextLetter;
	}

	return result;
}

int selectMessage() {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	rc = sqlite3_open("../Enigma_and_Bombe/enigma_bombe.db", &db);
	if (rc != SQLITE_OK) {
		cout << "Error opening db in selectMessage" << endl;
	}

	string query = "SELECT messageOrder, encryptedMsg FROM Past_Messages";
	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << query << endl;
	}

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
		cout << "No past messages found. Run the Enigma program and enter some messages to get started!" << endl;
		exit(0);
	}

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

	getPlugboardUsed(1);

	// Create plugboard with user inputs
	Plugboard plug{};
	

	// Map encoded message string to a vector
	int messageSize = encodedMessage.size();
	vector <int> plainNum(messageSize);

	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(encodedMessage[i]);
	}
	
	// Create reflector with hardcoded values
	Reflector reflector;

	int numRotors = getNumRotorsUsed(selectedMessage);
	// Create a vector with all of the rotors so we can iterate through it
	// Each has hard-coded values for now
	vector<Rotor> rotors;

	int scramble[26] = { 20, 13, 21, 18, 23, 1, 12, 14, 7, 10, 11, 25, 19,
						 4, 9, 2, 0, 17, 16, 15, 6, 22, 5, 24, 3, 8 }; // The order of the scrambled numbers on the rotor

	for (int i = 0; i < numRotors; i++) {
		rotors.push_back(Rotor(scramble, 0));
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

	cout << "Final decrypted message: ";
	for (int i = 0; i < plainNum.size(); i++) {
		cout << numToLetter(plainNum[i]);
	}

	return 0;
}