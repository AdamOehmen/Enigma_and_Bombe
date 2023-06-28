#include "Driver.h"
#include "sqlite3.h"

string plaintext;
int msg_order = 1;
int plug_name = 1;
int rotor_name = 1;

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
static void db_store(string tbl) {
	sqlite3* db;
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
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(msg_order) + ", '" + plaintext + "', 'placeholder'); ";	// construct query using user input, will replace placeholder with actual encrypted msg
		msg_order++; // update msg order 
	}
	else if (tbl == "Plugboard_Settings") {
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(plug_name) + ", 'placeholder plug setting'); ";	// construct query using user input, will replace placeholder with actual setting
		plug_name++; // update plug name
	}
	else if (tbl == "Rotor_Settings") {
		query = "INSERT INTO " + tbl + " VALUES(" + to_string(rotor_name) + ", 'placeholder rotor setting', 1); ";	// construct query using user input, will replace placeholder with actual setting and notch
		rotor_name++; // update rotor name 
	}
	cout << query << endl;
	exit = sqlite3_exec(db, query.c_str(), callback, NULL, NULL);	// execute the query command 
	if (exit != SQLITE_OK)	// check if query has been executed successfully 
	{
		cerr << "Error Insert" << endl;
	}
	else
		cout << "Inserted into Database Successfully!" << endl;
	sqlite3_close(db);	// close database after writing 
}
int main() //This is the main
{
	sqlite3_stmt* st;
	string sql3;

	cout << "What is the message you want to send\n"; //get the message we want to encode
	getline(cin,plaintext);  // get msg
	plaintext = delSpaces(plaintext);  // delete spaces of msg
	int messageSize = plaintext.size();  // get size of msg
	vector<int> plainNum(messageSize);  // create vector to hold msg
	// insert msg into database of past messages
	db_store("Past_Messages");
	// insert plugboard setting into database of plugboard settings
	db_store("Plugboard_Settings");
	// insert plugboard setting into database of rotor settings
	db_store("Rotor_Settings");
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