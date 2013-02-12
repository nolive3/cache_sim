#include "Cache_State.h"
#include "LRU.h"
#include "NMRU_FIFO.h"
#include <iostream>
 // booring setup stuff
Cache_State::Cache_State(uint64_t nc, uint64_t nb, uint64_t ns, bool is_blocking, bool is_lru) :m_tagstore(new Tag_Store*[1<<(nc-nb-ns)]), m_c(nc), m_b(nb), m_s(ns), m_f(is_blocking), m_r(is_lru)
{
    for (uint64_t i = 0; i< (uint64_t)1<<(nc-nb-ns); i++){
        if(is_lru) {
            m_tagstore[i] = new mLRU(m_s, m_b, m_c, is_blocking);
        }else{
            m_tagstore[i] = new mNMRU_FIFO(m_s, m_b, m_c, is_blocking);
        }
    }
}
//booring tear down stuff
Cache_State::~Cache_State()
{
    for (uint64_t i = 0; i< (uint64_t)1<<(m_c-m_b-m_s); i++){
        delete m_tagstore[i];
    }
    delete [] m_tagstore;
}


uint64_t Cache_State::index(uint64_t addr) const
{
    uint64_t mask = (1<<(m_c-m_b-m_s))-1; // this is C-B-S 1's
    return (addr >> m_b) & mask; // shift by B and clear all but the bottom C-B-S gets the index
}


void Cache_State::read(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->reads++; // increment reads
    if(!m_tagstore[index(addr)]->access(addr)){ // check if the block exists and if not get it
        p_stats->read_misses++; // if it did not add a miss
    }
}
void Cache_State::write(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->writes++; // increment reads
    if(!m_tagstore[index(addr)]->access(addr)){ // check if the block exists and if not get it
        p_stats->write_misses++; // if it did not add a miss
    }
}
