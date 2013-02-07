#include "cachesim.hpp"

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
}

/**
 * Subroutine for cleaning up any outstanding memory operations and calculating overall statistics
 * such as miss rate or average access time.
 * XXX: You're responsible for completing this routine
 *
 * @p_stats Pointer to the statistics structure
 */
void complete_cache(cache_stats_t *p_stats) {
    p_stats->accesses = p_stats->reads+p_stats->writes;
    p_stats->misses = p_stats->read_misses+p_stats->write_misses;
    p_stats->read_hits = p_stats->reads-p_stats->read_misses;
    p_stats->write_hits = p_stats->writes-p_stats->write_misses;
    p_stats->miss_rate = p_stats->misses/(double)p_stats->accesses;
    p_stats->avg_access_time = p_stats->hit_time + p_stats->miss_rate*p_stats->miss_penalty;
}
