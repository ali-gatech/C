#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include "types.h"

///////////////////////////////////////////////////////////////////////////////////
/// Define the necessary data structures here (Look at Appendix A for more details)
///////////////////////////////////////////////////////////////////////////////////


struct Cache_Line
{
    bool valid;
    bool dirty;
    uint32_t tag;
    uint8_t coreID;
    uint32_t freq;
    unsigned long long int LAT;
    #if CacheTiempo
        uint32_t counter;
    #endif
};

struct Cache_Set
{
    uint8_t ways;
    Cache_Line* cache_ways;
};


struct Cache
{
    uint64_t replace_policy;
    uint64_t num_sets;
    Cache_Line evict_line;
    Cache_Set* cache_sets;
    uint64_t stat_read_access;
    uint64_t stat_write_access;
    uint64_t stat_read_miss;
    uint64_t stat_write_miss;
    uint64_t stat_dirty_evicts;
    uint64_t stat_set_conflicts;
    uint64_t stat_place_invalid;
};

//////////////////////////////////////////////////////////////////////////////////////
// Mandatory variables required for generating the desired final reports as necessary
// Used by cache_print_stats()
//////////////////////////////////////////////////////////////////////////////////////

// stat_read_access : Number of read (lookup accesses do not count as READ accesses) accesses made to the cache
// stat_write_access : Number of write accesses made to the cache
// stat_read_miss : Number of READ requests that lead to a MISS at the respective cache.
// stat_write_miss : Number of WRITE requests that lead to a MISS at the respective cache
// stat_dirty_evicts : Count of requests to evict DIRTY lines.

/////////////////////////////////////////////////////////////////////////////////////////
// Functions to be implemented
//////////////////////////////////////////////////////////////////////////////////////////////

Cache* cache_new(uint64_t size, uint64_t assocs, uint64_t linesize, uint64_t repl_policy);
bool cache_access(Cache* c, Addr lineaddr, uint32_t is_write, uint32_t core_id);
void cache_install(Cache* c, Addr lineaddr, uint32_t is_write, uint32_t core_id);
uint32_t cache_find_victim(Cache *c, uint32_t set_index, uint32_t core_id);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void cache_print_stats(Cache* c, char* header);

#endif // CACHE_H
