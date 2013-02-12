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
    if(m_s == 0){ // if direct mapped replace the only option
        m_tags[0] = tag;
        uint64_t v = m_indexes[0];
        if(v == (uint64_t)-1){
            v = m_last++;
        }
        m_indexes[0] = v;
        return v;
    }
    uint64_t v = m_indexes[1]; // replace the second oldest
    if(m_tags[0] != m_mru || m_indexes[0]==(uint64_t)-1){
        v = m_indexes[0]; // unless the oldest is not most recently used or is still invalid
        m_tags[0] = m_tags[1];
        m_indexes[0] = m_indexes[1];
    }
    for (uint64_t i = 2; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];// move ereryone towards their immenent doom
        m_indexes[i-1] = m_indexes[i];
    }
    if(v == (uint64_t)-1){ // if the one we just kicked out is invalid set the index to something useful
        v = m_last++;
    }
    m_tags[(1<<m_s)-1] = tag; // store the new thing in the freshly vacated position
    m_indexes[(1<<m_s)-1] = v;
    return v; // return the index it is stored at
}
void mNMRU_FIFO::touch(uint64_t tag)
{
    m_mru = tag; // save which one was most recently used
}
