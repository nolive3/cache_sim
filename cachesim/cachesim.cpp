#include "cachesim.hpp"
#include "Cache_State.h"
#include <iostream>

Cache_State * current;

/**
 * Subroutine for initializing the cache. You many add and initialize any global or heap
 * variables as needed.
 * XXX: You're responsible for completing this routine
 *
 * @c The total number of bytes for data storage is 2^C
 * @b The size of a single cache line in bytes is 2^B
 * @s The number of blocks in each set is 2^S
 * @f The fetch policy, BLOCKING or EAGER (refer to project description for details)
 * @r The replacement policy, LRU or NMRU_FIFO (refer to project description for details)
 */
void setup_cache(uint64_t c, uint64_t b, uint64_t s, char f, char r) {
    current = new Cache_State(c,b,s,f==BLOCKING,r==LRU);
}
/**
 * Subroutine that simulates the cache one trace event at a time.
 * XXX: You're responsible for completing this routine
 *
 * @rw The type of event. Either READ or WRITE
 * @address  The target memory address
 * @p_stats Pointer to the statistics structure
 */
void cache_access(char rw, uint64_t address, cache_stats_t* p_stats) {
    switch (rw){
    case READ:
        current->read(address, p_stats);
        return;
    case WRITE:
        current->write(address, p_stats);
        return;
    default:
        std::cerr<<"Invalid cache access type "<<rw<<" at address "<<address<<std::endl;
    }
}

/**
 * Subroutine for cleaning up any outstanding memory operations and calculating overall statistics
 * such as miss rate or average access time.
 * XXX: You're responsible for completing this routine
 *
 * @p_stats Pointer to the statistics structure
 */
void complete_cache(cache_stats_t *p_stats) {
    p_stats->hit_time = ((2<<current->s()) + 9) / 10;
    p_stats->miss_penalty = p_stats->hit_time + 50 + ((current->f()&&(current->b()>2))?(1<<(current->b()-2)):1);
    p_stats->accesses = p_stats->reads+p_stats->writes;
    p_stats->misses = p_stats->read_misses+p_stats->write_misses;
    p_stats->read_hits = p_stats->reads-p_stats->read_misses;
    p_stats->write_hits = p_stats->writes-p_stats->write_misses;
    p_stats->miss_rate = p_stats->misses/(double)p_stats->accesses;
    p_stats->avg_access_time = p_stats->hit_time + p_stats->miss_rate*p_stats->miss_penalty;
    uint64_t per_block = (current->f()?1:1<<current->b())+current->r()?8:4;
    p_stats->storage_overhead = per_block * ((48<<13)/((8<<current->b())+per_block));
    p_stats->storage_overhead_ratio = p_stats->storage_overhead/((double)(48<<13));
    delete current;
}
