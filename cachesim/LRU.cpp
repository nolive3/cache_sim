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
    uint64_t v = m_indexes[0];
    for (uint64_t i = 1; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];
        m_indexes[i-1] = m_indexes[i];
    }
    if(v == (uint64_t)-1){
        v = m_last++;
    }
    m_tags[(1<<m_s)-1] = tag;
    m_indexes[(1<<m_s)-1] = v;
    return v;
}
void mLRU::touch(uint64_t tag)
{
    uint64_t i;
    uint64_t index;

    for (i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_tags[i] == tag)
            break;
    }
    index = m_indexes[i];
    for (i = i+1;i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];
        m_indexes[i-1] = m_indexes[i];
    }
    m_tags[(1<<m_s)-1] = tag;
    m_indexes[(1<<m_s)-1] = index;
}
