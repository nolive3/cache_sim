#include "LRU.h"





void mLRU::get_victim(uint64_t addr)
{
    bool * valids = m_valid[0]; // save the space from the evicted valid bits
    for (uint64_t i = 1; i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];// move everyone foward
        m_valid[i-1] = m_valid[i];
    }
    m_valid[(1<<m_s)-1] = valids; // set the new valid bits
    for(uint64_t i = 0; i < (uint64_t)1<<m_b; i++){
        if(i>=offset(addr) || m_r) // if it is blocking of this is after the requested byte the it gets fetched
            valids[i] = true;
        else
            valids[i] = false; // otherwise it does not
    }
    m_tags[(1<<m_s)-1] = tag(addr); // store the new guy at the end as the most recently used
}


void mLRU::touch(uint64_t addr)
{
    uint64_t i;
    bool* valids;

    for (i = 0; i < (uint64_t)1<<m_s; i++){
        if(m_tags[i] == tag(addr)) // find the tag in the set
            break;
    }
    valids = m_valid[i];
    for (i = i+1;i < (uint64_t)1<<m_s; i++){
        m_tags[i-1] = m_tags[i];
        m_valid[i-1] = m_valid[i];//move everyone who had been used more recently foward
    }
    m_tags[(1<<m_s)-1] = tag(addr); // store the guy who just got used at the end
    m_valid[(1<<m_s)-1] = valids;
    for(i = 0; i < (uint64_t)1<<m_b; i++){
        if(i>=offset(addr) || m_r) // if it is after requested byte then it gets fetched (for use with fetching th erst of the block in EAGER
            valids[i] = true; // but in this case dnt invalidate ones before
    }
}
