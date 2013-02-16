#include "NMRU_FIFO.h"
#include <iostream>
#include <iomanip>



void mNMRU_FIFO::get_victim(uint64_t addr)
{
    bool * valids = m_valid[0]; // save the space from the evicted valid bits
    if(m_s>0){ // if not direct mapped
        if(m_mru != m_tags[0]){
            m_valid[0] = m_valid[1]; // if mru is not first evict him
            m_tags[0] = m_tags[1];
        } else {
            valids = m_valid[1]; // else evict second guy
        }
        for (uint64_t i = 2; i < (uint64_t)1<<m_s; i++){
            m_tags[i-1] = m_tags[i];// move everyone foward
            m_valid[i-1] = m_valid[i];
        }
    }
    m_mru = tag(addr); // just added so most recently used
    m_valid[(1<<m_s)-1] = valids; // set the new valid bits
    for(uint64_t i = 0; i < (uint64_t)1<<m_b; i++){
        if(i>=offset(addr) || m_r) // if it is blocking of this is after the requested byte the it gets fetched
            valids[i] = true;
        else
            valids[i] = false; // otherwise it does not
    }
    m_tags[(1<<m_s)-1] = tag(addr); // store the new guy at the end as the most recently in
}

void mNMRU_FIFO::touch(uint64_t addr)
{
    uint64_t i;
    bool* valids;
    m_mru = tag(addr); // save which one was most recently used

    for (i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_tags[i] == tag(addr)) // find the tag in the set
            break;
    }
    valids = m_valid[i];

    for(i = 0; i < (uint64_t)1<<m_b; i++){
        if(i>=offset(addr) || m_r) // if it is after requested byte then it gets fetched (for use with fetching th erst of the block in EAGER
            valids[i] = true; // but in this case dont invalidate ones before
    }
}
