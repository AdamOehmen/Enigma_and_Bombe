#include "Driver.h"


string plaintext, encrypted_msg;
sqlite3* db;

int msg_order;
int plug_order;
int rotor_order, inotch;
string rotor_usr;
int plug_usr;
string plug_store, rotor_store;

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


static void last_msg(string tbl) {
	string query;
	sqlite3_stmt* stmt;
	string order;
	int exit = 0;
	if (tbl == "Past_Messages") {
		order = "messageOrder";
	}
	if (tbl == "Plugboard_Settings") {
		order = "plugName";
	}
	if (tbl == "Rotor_Settings") {
		order = "rotorName";
	}
	query = "SELECT MAX("+ order +") FROM " + tbl + "; ";
	//cout << "The query is: " << query;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Statement failed" << endl;
	}
	int count = sqlite3_column_int(stmt, 0); // Get the maximum message order from result set
	if (tbl == "Past_Messages") {
		if (count >= 0) {
			sqlite3_finalize(stmt); // Finalize the statement
			msg_order = count + 1;	// set msg_order as max message order + 1
		}
		else {
			cout << "No results!" << endl;
		}
	}
	if (tbl == "Plugboard_Settings") {
		if (count >= 0) {
			sqlite3_finalize(stmt); // Finalize the statement
			plug_order = count + 1;	// set msg_order as max message order + 1
		}
		else {
			cout << "No results!" << endl;
		}
	}
	if (tbl == "Rotor_Settings") {
		if (count >= 0) {
			sqlite3_finalize(stmt); // Finalize the statement
			rotor_order = count + 1;	// set msg_order as max message order + 1
		}
		else {
			cout << "No results!" << endl;
		}
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
		//cout << "open success" << endl;
	}
	if (tbl == "Past_Messages") {
		int rotor_used, plug_used;
		last_msg(tbl);	// grab the last message order
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(msg_order) + ", '" + plaintext + "', '" + encrypted_msg + "', '"
			+ rotor_usr +  "', " + to_string(plug_usr) + "); ";	// construct query using user input, will replace placeholder with actual encrypted msg
	}
	else if (tbl == "Plugboard_Settings") {
		last_msg(tbl);	// grab the last plug order
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(plug_order) + ", '" + plug_store + "');";	// construct query using user input, will replace placeholder with actual setting
	}
	else if (tbl == "Rotor_Settings") {
		last_msg(tbl);	// grab the last rotor order
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(rotor_order) + ", '" + rotor_store + "', " + to_string(inotch) + "); ";	// construct query using user input, will replace placeholder with actual setting and notch
	}
	//cout << query << endl;
	exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);	// execute the query command 
	if (exit != SQLITE_OK)	// check if query has been executed successfully 
	{
		cerr << "Error Insert: " << sqlite3_errmsg(db) << endl;
	}
	else {
		//cout << "Inserted into Database Successfully!" << endl;
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
		//cout << "open success" << endl;
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
		//cout << "open success" << endl;
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
		return "Er";
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

void ask_usr_set(int result[10]) {
	int plugSet;	// Plugboard Setting input
	//int numRotor;   // Number of Rotors input
	//int rotorSet[] = { 0,0,0,0,0,0,0,0 }; // Rotor Settings 
	/*
	Final Result Array Stores Following:
	First number is plug setting
	Second number is number of rotors
	Rest of array stores setting of rotors
	*/
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		//cout << "open success" << endl;
	}
	string query = "SELECT * FROM Plugboard_Settings";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	while (1)
	{
		cout << "Please enter plugName of the setting you want to use: " << endl;
		if (cin >> plugSet)  // Check if the input operation is successful
		{
			
			break;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			cin.clear();  // Clear any error flags from the input stream
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the input line
		}
	}
	
	result[0] = plugSet;
	plug_usr = plugSet;
	/*
	cout << "How many rotors would you like to use?" << endl;
	cin >> numRotor;
	result[1] = numRotor;
	query = "SELECT * FROM Rotor_Settings";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);
	int temp_set;
	for (int i = 0; i < numRotor; i++) {
		cout << "Which Rotor would you like to use for Rotor #" + to_string(i + 1) << endl;
		cin >> temp_set;
		rotorSet[i] = temp_set;
		result[i + 2] = temp_set;
	}
	*/
}
int concat(int a, int b)
{

	// Convert both the integers to string
	string s1 = to_string(a);
	string s2 = to_string(b);

	// Concatenate both strings
	string s = s1 + s2;

	// Convert the concatenated string
	// to integer
	int c = stoi(s);

	// return the formed integer
	return c;
}

int main() //This is the main
{
	sqlite3_stmt* st;
	string sql3;
	string plugset;
	int settings[10];	// Settings are stored as follows: #1: Plug Setting ID #2: Number of Rotors #3-10: Rotor ID's 
	// If Rotor ID is 0, then it doesn't exist

	cout << "Welcome to Enigma!" << endl << endl;
	
	
	// Ask User whether they would like to use predefined settings or create 
	// settings for Plugboard and Rotors
	char usr;
	Plugboard plug{};
	while (1)
	{
		cout << "Would you like to create your own settings for the Plugboard? (Y/N): ";
		cin >> usr;
		cin.ignore();
		
		if (usr == 'N') {
			// Extract settings from DB and store into object
			// Extracting Plugboard Settings and creating plugboard
			// Start of Plugboard Creation
			while (1)
			{
				ask_usr_set(settings);
				plugset = pull_plug_set(settings[0]);
				if (plugset.compare("Error") == 0)
				{
					cout << "Please enter a valid Plugboard" << endl << endl;
				}
				else
				{
					break;
				}

			}

			plug.DB_Extract(plugset);
			plug.setPlugPos();
			plug_store = plug.returnPlugLet();
			// End of Plugboard Creation
			// Start of Rotor Creation

			// End of Rotor Creation
			break;
		}
		else if (usr == 'Y') {
			/*
			Create Plugboard and Rotor Settings
			*/
			// Create plugboard with user inputs
			plug.createPlugboard();
			plug.setPlugPos();
			plug_store = plug.returnPlugLet();
			db_store("Plugboard_Settings");
			// Create Rotors with user inputs 
			// Reuse Below code
			break;
		}
		else
		{
			cout << "Please enter Y or N" << endl;
		}
		cout << endl;
	}
	// Place breakpoint here if you want to test above	
	// When testing Plugboard ensure you have a setting plugSetting entry with 20 characters such as 'ABCDEFGHIJKLMNOPQRSY' 

	// Create reflector with hard-coded values
	Reflector reflector;

	//Set number of rotors being used
	int numRotors = 10;
	while (numRotors > 8) {
		while (1) {
			cout << endl << "How many rotors would you like to use? (Max is 8): ";
			cin >> numRotors;

			if (cin.fail()) {
				cout << "Invalid input. Please enter an integer value." << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			}
			else {
				if (numRotors <= 8 && numRotors >= 1) {
					break; // Exit the loop as we have a valid number of rotors
				}
				else {
					cout << "Invalid input. Please enter a number between 1 and 8." << endl;
				}
			}
		}
	}
	settings[1] = numRotors; // add to settings
	
	// Create a vector with all of the rotors so we can iterate through it
	// Each has hard-coded values for now
	vector<Rotor> rotors;
	for (int i = 0; i < numRotors; i++) {
		rotors.push_back(Rotor());
		int chkYN = rotors[i].getYN();
		settings[i + 2] = rotors[i].getName();
		if (chkYN == 1)
		{
			rotor_store = rotors[i].getScramble();
			inotch = rotors[i].getNotch();
			last_msg("Rotor_Settings");
			//cout << "The previous rotor is: " << rotor_order << endl;
			db_store("Rotor_Settings");
			rotor_order = rotor_order + 1;	// grab the last rotor order
			//cout << "The lastest rotor is: " << rotor_order << endl;
			if (i == 0)
			{
				rotor_usr = to_string(rotor_order);
			}
			else
			{
				rotor_usr = rotor_usr + ", " + to_string(rotor_order);
			}

		}
		else
		{
			if (i == 0)
			{
				rotor_usr = to_string(rotors[i].getName());
			}
			else
			{
				rotor_usr = rotor_usr + ", " + to_string(rotors[i].getName());
			}
		}
	}

	cin.clear();
	while (1)
	{
		cout << "What is the message you want to send: ";
		getline(cin, plaintext);

		// Check if the input contains any special characters
		bool containsSpecialCharacters = false;
		for (char c : plaintext) {
			if (!isalpha(c)) { // Check if the character is an alphabet letter
				containsSpecialCharacters = true;
				break;
			}
		}

		if (containsSpecialCharacters) {
			cout << "Invalid input. Please enter letters or words only." << endl << endl;
		}
		else {
			// No special characters found, we can proceed
			break;
		}
	}
	// put input string into array
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}

	
	for (int i = 0; i < messageSize; i++)
	{
		cout << "Starting letter: " << numToLetter(plainNum[i]) << endl;

		// Send input through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);

		// Send plugboard output through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
		}
		
		// Send output of rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);

		// Send reflector output back through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
		}

		cout << "Encrypted letter: " << numToLetter(plainNum[i]) << endl << endl;

		// Rotate rotor #1 after every encrypted input letter
		rotors[0].rotate();
		//cout << "ROTATE ROTOR 1" << endl << endl;

		bool lastRotated = true;
		for (int k = 1; k < numRotors; k++) {
			// Rotate the next rotor IF the notch of the previous matches the current position, AND the previous just rotated
			if ((rotors[k - 1].getNotch() == rotors[k - 1].getPos()) && lastRotated) {
				rotors[k].rotate();
				//cout << "ROTATE ROTOR " << (k + 1) << endl;
				lastRotated = true;
			}
			// Otherwise, update value of lastRotated
			else {
				lastRotated = false;
			}
		}
	}

	// Print the final encrypted message
	cout << "Final encrypted message: ";
	for (int i = 0; i < plainNum.size(); i++) {
		encrypted_msg = encrypted_msg + numToLetter(plainNum[i]);
	}

	cout << encrypted_msg << endl << endl;
	
	// call last_msg so program knows where to store the encrypted message
	db_store("Past_Messages");

	return 0;

}
