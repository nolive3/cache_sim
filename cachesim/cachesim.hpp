#ifndef CACHESIM_HPP
#define CACHESIM_HPP

#include <cstdint>

struct cache_stats_t {
    uint64_t accesses;                //Calculated during cleanup as reads+writes
    uint64_t reads;                   //Calculated during runtime incremented for each read
    uint64_t read_hits;               //Calculated during cleanup as reads-read_misses
    uint64_t read_misses;             //Calculated during runtime incremented for each read miss
    uint64_t writes;                  //Calculated during runtime incremented for each write
    uint64_t write_hits;              //Calculated during cleanup as writes-write_misses
    uint64_t write_misses;            //Calculated during runtime incremented for each write miss
    uint64_t misses;                  //Calculated during cleanup as read_misses+write_misses
    uint64_t hit_time;                //Calculated during setup as (2<<S + 5) / 10 The +5 is to do an integer division ceil (cant take part of a cycle)
    uint64_t miss_penalty;            //Calculated during setup as hit_time + 50 + BLOCKING&&B>2?1<<(B-2):1
    double   miss_rate;;
    double   avg_access_time;;
    uint64_t storage_overhead;
    double   storage_overhead_ratio;
};

void cache_access(char rw, uint64_t address, cache_stats_t* p_stats);
void setup_cache(uint64_t c, uint64_t b, uint64_t s, char f, char r);
void complete_cache(cache_stats_t *p_stats);

static const uint64_t DEFAULT_C = 15;   /* 32KB Cache */
static const uint64_t DEFAULT_B = 5;    /* 32-byte blocks */
static const uint64_t DEFAULT_S = 3;    /* 8 blocks per set */

static const char     BLOCKING = 'B';
static const char     EAGER = 'E';
static const char     DEFAULT_F = BLOCKING;

static const char     LRU = 'L';
static const char     NMRU_FIFO = 'N';
static const char     DEFAULT_R = LRU;

/** Argument to cache_access rw. Indicates a load */
static const char     READ = 'r';
/** Argument to cache_access rw. Indicates a store */
static const char     WRITE = 'w';

#endif /* CACHESIM_HPP */
