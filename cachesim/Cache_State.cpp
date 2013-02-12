#include "Cache_State.h"
#include "LRU.h"
#include "NMRU_FIFO.h"
#include <iostream>

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
    return addr >> (m_c-m_s);
}
uint64_t Cache_State::index(uint64_t addr) const
{
    uint64_t mask = (1<<(m_c-m_b-m_s))-1;
    return (addr >> m_b) & mask;
}
uint64_t Cache_State::offset(uint64_t addr) const
{
    uint64_t mask = (1<<(m_b))-1;
    return (addr) & mask;
}
uint64_t Cache_State::valid(uint64_t addr) const
{
    for(uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_valid[index(addr)][i][offset(addr)] && m_tagstore[index(addr)]->get(i) == tag(addr)){
            return true;
        }
    }
    return false;
}
void Cache_State::get(uint64_t addr)
{
    int victim = m_tagstore[index(addr)]->get_victim(tag(addr));
    for(uint64_t i = 0; i < (uint64_t)1<<m_b; i++){
        if(m_f || i>=offset(addr))
            m_valid[index(addr)][victim][i] = true;
    }
}
void Cache_State::touch(uint64_t addr)
{
    m_tagstore[index(addr)]->touch(tag(addr));
}

void Cache_State::read(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->reads++;
    if(!valid(addr)){
        p_stats->read_misses++;
        get(addr);
    }else{
        touch(addr);
    }
}
void Cache_State::write(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->writes++;
    if(!valid(addr)){
        p_stats->write_misses++;
        get(addr);
    }else{
        touch(addr);
    }
}
