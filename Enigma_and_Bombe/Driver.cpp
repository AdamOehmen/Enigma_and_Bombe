#include "Driver.h"


string plaintext;
sqlite3* db;

int msg_order;
int plug_name = 1;
int rotor_name = 1;
int rotor_usr, plug_usr;

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


static void last_msg() {
	string query;
	sqlite3_stmt* stmt;
	int exit = 0;
	query = "SELECT MAX(messageOrder) FROM Past_Messages;";
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Statement failed" << endl;
	}
	int count = sqlite3_column_int(stmt, 0); // Get the maximum message order from result set
	if (count >= 0) {
		sqlite3_finalize(stmt); // Finalize the statement
		msg_order = count + 1;	// set msg_order as max message order + 1
	}
	else {
		cout << "No results!" << endl;
	}
}
static void db_store(string tbl) {
	int exit = 0;
	string query;
	exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	if (tbl == "Past_Messages") {
		int rotor_used, plug_used;
		last_msg();	// grab the last message order
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(msg_order) + ", '" + plaintext + "', 'placeholder', "
			+ to_string(rotor_usr) + ", " + to_string(plug_usr) + "); ";	// construct query using user input, will replace placeholder with actual encrypted msg
	}
	else if (tbl == "Plugboard_Settings") {
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(plug_name) + ", 'ABCD'); ";	// construct query using user input, will replace placeholder with actual setting
		plug_name++; // update plug name
	}
	else if (tbl == "Rotor_Settings") {
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(rotor_name) + ", 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 1); ";	// construct query using user input, will replace placeholder with actual setting and notch
		rotor_name++; // update rotor name 
	}
	cout << query << endl;
	exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);	// execute the query command 
	if (exit != SQLITE_OK)	// check if query has been executed successfully 
	{
		cerr << "Error Insert: " << sqlite3_errmsg(db) << endl;
	}
	else {
		cout << "Inserted into Database Successfully!" << endl;
		sqlite3_close(db);	// close database after writing 
	}
}
int* pull_msg_settings(string encrypt) {
	int arr[2];
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	string query = "SELECT plugUsed, rotorUsed FROM Past_Messages WHERE encryptedMsg = '" + encrypt + "';";	// SQL statement selecting the rotorUsed element for the encrypted msg
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement

	int count = sqlite3_column_int(stmt, 0); // Get the plugUsed setting and add to resulting array
	if (count > 0) {
		arr[0] = count;
		count = sqlite3_column_int(stmt, 1); // Get the rotorUsed setting and add to resulting array
		arr[1] = count;
		sqlite3_finalize(stmt); // Finalize the statement
		return arr;				// Return pointer to resulting array
	}
	else {
		cout << sqlite3_errmsg(db);
		return 0;
	}

}
string pull_plug_set(int plug) {
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	string query = "SELECT plugSettings FROM Plugboard_Settings WHERE plugName = " + to_string(plug) + ";";	// SQL statement selecting plugboard setting
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Plugboard Doesn't exist" << endl;	// Check if plugboard exists
	}
	size_t length = strlen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));  // calculate the length using reinterpret_cast since strlen expects a string
	int size = length * sizeof(unsigned char);  // calculate the total size

	string result = "";
	for (int i = 0; i < size; i++) {
		char temp = sqlite3_column_text(stmt, 0)[i];	// temp char set to each index of char array
		result = result + temp;	// append temp to resulting string
	}
	sqlite3_finalize(stmt); // Finalize the statement
	sqlite3_close(db);	// close db
	return result;

}
string pull_rotor_set(int rotor) {
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	string query = "SELECT rotorSetting FROM Rotor_Settings WHERE rotorName = " + to_string(rotor) + ";";	// SQL statement selecting rotor setting
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;	// Check if statement is prepared correctly
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
	sqlite3_close(db);	// close db
	return result;
}
int pull_rotor_notch(int rotor) {
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	string query = "SELECT notch FROM Rotor_Settings WHERE rotorName = " + to_string(rotor) + ";";	// SQL statement selecting rotor setting
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;	// Check if statement is prepared correctly
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Rotor Doesn't exist" << endl;	// Check if plugboard exists
	}

	int result = sqlite3_column_int(stmt, 0);	// save notch value into result
	sqlite3_finalize(stmt); // Finalize the statement
	sqlite3_close(db);	// close db
	return result;
}

int main() //This is the main
{
	sqlite3_stmt* st;
	string sql3;
	string usr_username;
	string usr_password;
	cout << "Welcome to Enigma!" << endl;
	// Create plugboard with user inputs
	Plugboard plug{};
	plug.createPlugboard();
	plug.setPlugPos();

	cout << "What is the message you want to send\n"; //get the message we want to encode
	getline(cin,plaintext);
	plaintext = delSpaces(plaintext);

	// put input string into array
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}


	// Create reflector with hard-coded values
	Reflector reflector;

	int numRotors = 3;
	// Create a vector with all of the rotors so we can iterate through it
	// Each has hard-coded values for now
	vector<Rotor> rotors;
	for (int i = 0; i < numRotors; i++) {
		rotors.push_back(Rotor());
	}
	for (int i = 0; i < messageSize; i++)
	{
		// Send input through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
		cout << "After plugboard: " << plainNum[i] << endl;;

		// Send plugboard output through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
			cout << "After rotor " << j+1 << ": " << plainNum[i] << endl;
		}
		
		// Send output of rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);
		cout << "After reflector: " << plainNum[i] << endl;

		// Send reflector back through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
			cout << "After rotor " << j + 1 << ": " << plainNum[i] << endl;
		}

		// Rotate rotor #1 after every encrypted input
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
		// Print final letter to screen
		cout << numToLetter(plainNum[i]) << endl;
	}

	return 0;

}