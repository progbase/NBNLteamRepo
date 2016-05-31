#ifndef SORTENTRIES_H_INCLUDED
#define SORTENTRIES_H_INCLUDED

#include <algorithm>
#include <ctime>

using namespace std;

#define BUFFER_LEN 256

typedef struct db_con_s db_con_t;
typedef struct garage_stats_entry {
	size_t id;
	char type[BUFFER_LEN];
	time_t actionTime;
	char called[BUFFER_LEN];
} garage_stats_entry;

void sortEntries (garage_stats_entry entries [], int size);

#endif // SORTENTRIES_H_INCLUDED
