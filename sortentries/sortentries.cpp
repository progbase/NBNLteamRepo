#include "sortentries.h"

bool sortFunction (garage_stats_entry g1, garage_stats_entry g2)
{
    return g1.actionTime < g2.actionTime;
}

void sortEntries (garage_stats_entry entries [], int size)
{
    sort (entries, entries + size, sortFunction);
}
