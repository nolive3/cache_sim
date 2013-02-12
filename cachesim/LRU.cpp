#include "LRU.h"
uint64_t mLRU::get(uint64_t index) const
{
    for (uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_indexes[i] == index)
            return m_tags[i];
    }
    return -1;
}
uint64_t mLRU::get_victim(uint64_t tag)
{
    uint64_t v = m_indexes[0]; // kick out the least recently used
    for (uint64_t i = 1; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];// move everyone foward
        m_indexes[i-1] = m_indexes[i];
    }
    if(v == (uint64_t)-1){
        v = m_last++; // if we kicked out an invalid make the index something useful
    }
    m_tags[(1<<m_s)-1] = tag;
    m_indexes[(1<<m_s)-1] = v; // store the new guy at the end as the most recently used
    return v;
}
void mLRU::touch(uint64_t tag)
{
    uint64_t i;
    uint64_t index;

    for (i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_tags[i] == tag) // find the tag in the set
            break;
    }
    index = m_indexes[i];
    for (i = i+1;i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];
        m_indexes[i-1] = m_indexes[i];//move everyone who had been used more recently foward
    }
    m_tags[(1<<m_s)-1] = tag; // store the guy who just got used at the end
    m_indexes[(1<<m_s)-1] = index;
}
