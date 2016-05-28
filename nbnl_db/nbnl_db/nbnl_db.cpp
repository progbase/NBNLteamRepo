#include "nbnl_db.h"
#include <sqlite3.h>
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

void db_close(db_con_t * self)
{
	int rc = sqlite3_close(self->db);
	free(self);
}
