#include "Driver.h"
#include "sqlite3.h"

string plaintext;

int main() //This is the main
{
	sqlite3* db;
	sqlite3_stmt* st;
	string sql3;

	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,plaintext);  // get msg
	plaintext = delSpaces(plaintext);  // delete spaces of msg
	int messageSize = plaintext.size();  // get size of msg
	vector<int> plainNum(messageSize);  // create vector to hold msg
	// insert msg into database of past messages
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