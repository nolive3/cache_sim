#include "NMRU_FIFO.h"

bool mNMRU_FIFO::access(uint64_t addr)
{
    return false;
}


bool mNMRU_FIFO::contains(uint64_t addr) const
{
    return false;
}
void mNMRU_FIFO::get_victim(uint64_t addr)
{
    if(m_s == 0){ // if direct mapped replace the only option
        m_tags[0] = tag(addr);
    }
    if(m_tags[0] != m_mru){// unless the oldest is not most recently used or is still invalid
        m_tags[0] = m_tags[1];
    }
    for (uint64_t i = 2; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];// move ereryone towards their immenent doom
    }
    m_tags[(1<<m_s)-1] = tag(addr); // store the new thing in the freshly vacated position
}
void mNMRU_FIFO::touch(uint64_t addr)
{
    m_mru = tag(addr); // save which one was most recently used
}
