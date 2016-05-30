#pragma once
#include <stdlib.h>
#include <time.h>
#include "html_gen.h"
#include <string.h>
#include <Windows.h>
#include "nbnl_db.h"
int main(int argc, char ** argv )
{
	garage_stats_entry entry = { 1,"OPEN",time(NULL) , "MANUALLY", };
	db_con_t * con = db_connect("nbnl_garage.db");
	db_add_entry(con, "OPEN", 12, "MANUALLY");
	db_close(con);
	return EXIT_SUCCESS;
}