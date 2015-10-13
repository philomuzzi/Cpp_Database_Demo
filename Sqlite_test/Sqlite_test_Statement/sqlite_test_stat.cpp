#include <stdio.h>
#include "sqlite3.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	rc = sqlite3_open(R"(F:\Sqlite3\test.db)", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
	else {
		fprintf(stdout, "Database opened successfully\n");
	}

	sqlite3_stmt * stmt;
	string sql_i = "insert into player (accid, name, account, databinary) "
		"VALUES ('Paul5', 'Paul5', 'Paul5', 'xxxx5'); ";

	if (sqlite3_prepare(db, sql_i.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
		int res = sqlite3_step(stmt); // 返回的是操作是否成功，而不是递增的id
		cout << res << endl;
		sqlite3_finalize(stmt);
	}

	sqlite3_stmt * statement;

	std::string sql = "select * from player";

	if (sqlite3_prepare(db, sql.c_str(), -1, &statement, NULL) == SQLITE_OK ) {
		int ctotal = sqlite3_column_count(statement);
		int res = 0;
		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				string s0 = (char*)sqlite3_column_text(statement, 0);
				int i1 = sqlite3_column_int(statement, 1);
				string s2 = (char*)sqlite3_column_text(statement, 2);
				string s3 = (char*)sqlite3_column_text(statement, 3);
				string s4 = (char*)sqlite3_column_text(statement, 4);

				cout << s0 << " " << i1 << " " << s2 << " " << s3 << " " << s4;
				cout << endl;
			}

			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				cout << "done " << endl;
				break;
			}
		}
	}
	

	sqlite3_finalize(statement);
	sqlite3_close(db);

	getchar();
	return 0;
}
