#include <stdio.h>
#include "sqlite3.h"
#include <string>

static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

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

	std::string sql = "UPDATE player set databinary = 'yyyy' where charid=1; " \
		"select * from player";

	const char* data = "Callback function called";
	rc = sqlite3_exec(db, sql.c_str(), callback, (void *)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records selected successfully\n");
	}

	sqlite3_close(db);
	return 0;
}
