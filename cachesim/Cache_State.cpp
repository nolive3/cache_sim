#include "Cache_State.h"
//number of sets is ((48<<13)/((8<<B)+((f?1:(1<<b))+r?8:4)));
Cache_State::Cache_State(uint64_t nc, uint64_t nb, uint64_t ns, bool is_blocking, bool is_lru) : m_valid(new bool**[((48<<13)/((8<<nb)+((is_blocking?1:(1<<nb))+is_lru?8:4)))]), m_tagstore(new uint64_t*[((48<<13)/((8<<nb)+((is_blocking?1:(1<<nb))+is_lru?8:4)))]), m_c(nc), m_b(nb), m_s(ns), m_f(is_blocking), m_r(is_lru)
{
    for (uint64_t i = 0; i< (uint64_t)((48<<13)/((8<<m_b)+((m_f?1:(1<<m_b))+m_r?8:4))); i++){
        m_valid[i] = new bool*[1<<ns];
        for (uint64_t j = 0; j < (uint64_t)1<<m_s; j++){
            m_valid[i][j] = new bool[1<<nb];
        }
    }
    for (uint64_t i = 0; i< (uint64_t)((48<<13)/((8<<m_b)+((m_f?1:(1<<m_b))+m_r?8:4))); i++){
        m_tagstore[i] = new uint64_t[1<<ns];
    }
}

Cache_State::~Cache_State()
{
    for (uint64_t i = 0; i< (uint64_t)((48<<13)/((8<<m_b)+((m_f?1:(1<<m_b))+m_r?8:4))); i++){
        for (uint64_t j = 0; j < (uint64_t)1<<m_s; j++){
            delete [] m_valid[i][j];
        }
        delete [] m_valid[i];
    }
    delete [] m_valid;
    for (uint64_t i = 0; i< (uint64_t)((48<<13)/((8<<m_b)+((m_f?1:(1<<m_b))+m_r?8:4))); i++){
        delete [] m_tagstore[i];
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
        if(m_valid[index(addr)][i][offset(addr)] && m_tagstore[index(addr)][i] == tag(addr)){
            return true;
        }
    }
    return false;
}
void Cache_State::get(uint64_t addr)
{
    for(uint64_t i = 0; i < (uint64_t)1<<m_b; i++){
        if(m_f || i>=offset(addr))
            m_valid[index(addr)][0][i] = true;
    }
    m_tagstore[index(addr)][0] = tag(addr);
}

void Cache_State::read(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->reads++;
    if(!valid(addr)){
        p_stats->read_misses++;
        get(addr);
    }
}
void Cache_State::write(uint64_t addr, cache_stats_t* p_stats)
{
    p_stats->writes++;
    if(!valid(addr)){
        p_stats->write_misses++;
        get(addr);
    }
}
