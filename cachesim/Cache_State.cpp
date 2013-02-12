#include "Cache_State.h"
#include "LRU.h"
#include "NMRU_FIFO.h"
#include <iostream>
 // booring setup stuff
Cache_State::Cache_State(uint64_t nc, uint64_t nb, uint64_t ns, bool is_blocking, bool is_lru) : m_valid(new bool**[1<<(nc-nb-ns)]), m_tagstore(new Tag_Store*[1<<(nc-nb-ns)]), m_c(nc), m_b(nb), m_s(ns), m_f(is_blocking), m_r(is_lru)
{
    for (uint64_t i = 0; i< (uint64_t)1<<(nc-nb-ns); i++){
        m_valid[i] = new bool*[1<<ns];
        for (uint64_t j = 0; j < (uint64_t)1<<m_s; j++){
            m_valid[i][j] = new bool[1<<nb];
        }
    }
    for (uint64_t i = 0; i< (uint64_t)1<<(nc-nb-ns); i++){
        if(is_lru) {
            m_tagstore[i] = new mLRU(m_s);
        }else{
            m_tagstore[i] = new mNMRU_FIFO(m_s);
        }
    }
}
//booring tear down stuff
Cache_State::~Cache_State()
{
    for (uint64_t i = 0; i< (uint64_t)1<<(m_c-m_b-m_s); i++){
        for (uint64_t j = 0; j < (uint64_t)1<<m_s; j++){
            delete [] m_valid[i][j];
        }
        delete [] m_valid[i];
    }
    delete [] m_valid;
    for (uint64_t i = 0; i< (uint64_t)1<<(m_c-m_b-m_s); i++){
        delete m_tagstore[i];
    }
    delete [] m_tagstore;
}


uint64_t Cache_State::tag(uint64_t addr) const
{
    return addr >> (m_c-m_s);// shift by C-S to get just the tag
}
uint64_t Cache_State::index(uint64_t addr) const
{
    uint64_t mask = (1<<(m_c-m_b-m_s))-1; // this is C-B-S 1's
    return (addr >> m_b) & mask; // shift by B and clear all but the bottom C-B-S gets the index
}
uint64_t Cache_State::offset(uint64_t addr) const
{
    uint64_t mask = (1<<(m_b))-1; // B 1's
    return (addr) & mask; // just clear all but the bottom B bits to get the offset
}
uint64_t Cache_State::valid(uint64_t addr) const
{
    for(uint64_t i = 0; i < (uint64_t)1<<m_s; i++){ // look through the appropriate set for a block that has a matching tag AND the proper byte is valid
        if(m_valid[index(addr)][i][offset(addr)] && m_tagstore[index(addr)]->contains(i, tag(addr))){ // if found it is a hit
            return true;
        }
    }
    return false; // if no such block exists then it is a miss
}
void Cache_State::get(uint64_t addr)
{
    int victim = m_tagstore[index(addr)]->get_victim(tag(addr)); // evict a person and get the evicted index in the set
    for(uint64_t i = 0; i < (uint64_t)1<<m_b; i++){ // then set all of the valid bits
        if(m_f || i>=offset(addr))  // either using BLOCKING so everything is fetched or this is after the requested byte
            m_valid[index(addr)][victim][i] = true; // so it is valid now
        if(!m_f && i<offset(addr)) // we are using EAGER and the byte is earlier than the requested byte
            m_valid[index(addr)][victim][i] = false; // so this is not fecthed
    }
}
void Cache_State::touch(uint64_t addr)
{
    m_tagstore[index(addr)]->touch(tag(addr)); // just tell the cache set store to update that block
}

void Cache_State::read(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->reads++; // increment reads
    if(!valid(addr)){ // check if the block exists
        p_stats->read_misses++; // if not make add a miss
        get(addr); // and get it
    }else{
        touch(addr); // otherwise update its eviction since it was accessed
    }
}
void Cache_State::write(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->writes++; // inc writes
    if(!valid(addr)){ // check block
        p_stats->write_misses++; // oh noes!! it's not there
        get(addr); // so get it
    }else{
        touch(addr); // or maybe it was there so protect it from eviction
    }
}
