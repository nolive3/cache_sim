#include "NMRU_FIFO.h"
uint64_t mNMRU_FIFO::get(uint64_t index) const
{
    for (uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_indexes[i] == index)
            return m_tags[i];
    }
    return -1;
}
uint64_t mNMRU_FIFO::get_victim(uint64_t tag)
{
    uint64_t v = m_indexes[1];
    if(m_tags[0] != m_mru){
        v = m_indexes[0];
        m_tags[0] = m_tags[1];
        m_indexes[0] = m_indexes[1];
    }
    for (uint64_t i = 2; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];
        m_indexes[i-1] = m_indexes[i];
    }
    m_tags[(1<<m_s)-1] = tag;
    m_indexes[(1<<m_s)-1] = v;
    return v;
}
void mNMRU_FIFO::touch(uint64_t tag)
{
    m_mru = tag;
}
