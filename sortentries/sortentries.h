#ifndef SORTENTRIES_H_INCLUDED
#define SORTENTRIES_H_INCLUDED

#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

#define BUFFER_LEN 256

typedef struct db_con_s db_con_t;
typedef struct garage_stats_entry {
	size_t id;
	char type[BUFFER_LEN];
	time_t actionTime;
	char called[BUFFER_LEN];
} garage_stats_entry;

void sortEntries (vector<garage_stats_entry> entries);

#endif // SORTENTRIES_H_INCLUDED
