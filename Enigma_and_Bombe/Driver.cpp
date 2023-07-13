#define _CRT_SECURE_NO_WARNINGS
#include "Driver.h"
#include "sqlite3.h"


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

static int login(string usr, string pwd) {
	int exit = sqlite3_open("enigma_bombe.db", &db); // open database
	if (exit != SQLITE_OK) {	// check if database is opened
		cout << "error" << endl;
	}
	else {
		cout << "open success" << endl;
	}
	string query = "SELECT 1 FROM Login WHERE Username = '" + usr + "';";	// SQL statement selecting 1 and inserting into result set if username is found else select 0
	sqlite3_stmt* stmt;
	int result;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

	int count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		sqlite3_finalize(stmt); // Finalize the statement
	}
	else {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

	query = ("SELECT 1 FROM Login WHERE Password = '" + pwd + "';");	// SQL statement selecting 1 and inserting into result set if password is found else select 0

	rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr); // Prepare the statement
	if (rc != SQLITE_OK) {
		cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
		return 0;
	}
	rc = sqlite3_step(stmt); // Execute the statement
	if (rc != SQLITE_ROW) {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

	count = sqlite3_column_int(stmt, 0); // Get the count from the result set
	if (count > 0) {
		cout << "Welcome to Enigma!" << endl;
		sqlite3_finalize(stmt); // Finalize the statement
		sqlite3_close(db);	// close database 
		return 1;
	}
	else {
		cout << "Incorrect Username or Password" << endl;
		return 0;
	}

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
		+ to_string(rotor_usr) + ", " + to_string(plug_usr)+ "); ";	// construct query using user input, will replace placeholder with actual encrypted msg
	}
	else if (tbl == "Plugboard_Settings") {
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(plug_name) + ", 'a'); ";	// construct query using user input, will replace placeholder with actual setting
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
		cerr << "Error Insert: " << sqlite3_errmsg(db)<<endl;
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
	// Login into Enigma
	cout << "-------------Please login to Enigma-------------" << endl;
	cout << "Username: ";	cin >> usr_username;
	cout << "Password: ";	cin >> usr_password;
	cin.ignore();	// clear queue
	if (login(usr_username, usr_password) == 0) {
		return 0;
	}
	
	cout << "What is the message you want to send\n"; //get the message we want to encode
	getline(cin,plaintext);  // get msg
	plaintext = delSpaces(plaintext);  // delete spaces of msg
	int messageSize = plaintext.size();  // get size of msg
	vector<int> plainNum(messageSize);  // create vector to hold msg
	cout << "What Rotor Setting would you like to use?" << endl;
	cin >> rotor_usr;
	cout << "What Plugboard Setting would you like to use?" << endl;
	cin >> plug_usr;
	// insert msg into database of past messages
	db_store("Past_Messages");
	// insert plugboard setting into database of plugboard settings
	db_store("Plugboard_Settings");
	// insert plugboard setting into database of rotor settings
	db_store("Rotor_Settings");
	int* arr = pull_msg_settings("ABCD");
	int plugSet = arr[0];	// dereference ptr
	int rotorSet = arr[1];	// dereference ptr
	cout << "Plug Setting is " << plugSet << endl;
	cout << "Rotor Setting is " << rotorSet << endl;
	cout << "The Current Plugboard is Set to " << pull_plug_set(plugSet) << endl;
	cout << "The Current Rotor is Set to " << pull_rotor_set(rotorSet) << endl;
	cout << "The Current Rotor Notch is Set to " << to_string(pull_rotor_notch(rotorSet)) << endl;
	/*
	if (sqlite3_open("enigma_bombe.db", &db) == SQLITE_OK)
	{
		string sql = "INSERT INTO PastMessages (originalMsg) VALUES ('" + plaintext + "'); ";
		int rc = sqlite3_prepare(db, sql.c_str(), -1, &st, NULL);
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(st, 1, plaintext.c_str(), plaintext.length(), SQLITE_TRANSIENT);
			sqlite3_step(st);
			if (rc != SQLITE_DONE) {
				cout << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
			}
			sqlite3_finalize(st);
			cout << "Uploaded to the database." << endl;
		} else {
			cout << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
		}
		sqlite3_close(db);
	} else {
		cout << "Error opening database." << endl;
	}
	*/

	
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);  // translate letter to number
	}

	int arry[10] = { 2, 7, 10, 5, 16, 20, 22, 12, 6, 23};
	Plugboard plug{};
	plug.setPlugPos(arry);
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
	}

	return 0;

}