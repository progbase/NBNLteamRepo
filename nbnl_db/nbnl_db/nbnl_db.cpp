#include "nbnl_db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct db_con_s {
	sqlite3 * db;
};
db_con_t * db_connect(char * file_name)
{
	db_con_t * self = (db_con_t *)malloc(sizeof(db_con_t));
	int rc = 0;
	rc = sqlite3_open(file_name, &(self->db));
	if (rc != SQLITE_OK)
	{
		free(self);
		return NULL;
	}
	return self;
}

void db_add_entry(db_con_t * self, char * type, time_t actionTime, char * called)
{
	sqlite3_stmt *stmt = NULL;
	int rc = 0;
	char * sql = "INSERT INTO garage_actions (Type, Time, Called) VALUES (?,?,?);";

	rc = sqlite3_prepare_v2(self->db, sql, strlen(sql) + 1, &stmt, NULL);
	if (SQLITE_OK != rc) {
		printf("Error prepare! %i\n", rc);
		return;
	}

	rc = sqlite3_bind_text(stmt, 1, type, strlen(type), SQLITE_STATIC);
	if (SQLITE_OK != rc) {
		printf("Error bind type! %i\n", rc);
		return;
	}

	rc = sqlite3_bind_int(stmt, 2, actionTime);
	if (SQLITE_OK != rc) {
		printf("Error bind actionTime! %i\n", rc);
		return;
	}

	rc = sqlite3_bind_text(stmt, 3, called, strlen(called), SQLITE_STATIC);
	if (SQLITE_OK != rc) {
		printf("Error bind called! %i\n", rc);
		return;
	}
	if (SQLITE_DONE != (rc = sqlite3_step(stmt))) {
		printf("Not inserted! %i\n", rc);
		return;
	}
	printf("Data inserted!\n");
	sqlite3_finalize(stmt);
}


void db_close(db_con_t * self)
{
	int rc = sqlite3_close(self->db);
	free(self);
}
