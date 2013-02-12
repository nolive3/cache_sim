#include "Tag_Store.h"

Tag_Store::Tag_Store(uint64_t s, uint64_t b, uint64_t c, bool r) : m_s(s), m_b(b), m_c(c), m_r(r), m_valid(new bool*[1<<s]), m_last(0), m_tags(new uint64_t[1<<s])
{

    for (uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        m_valid[i] = new bool[1<<b];
    }
}

Tag_Store::~Tag_Store()
{
    delete [] m_tags;
    for (uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        delete [] m_valid[i];
    }
    delete [] m_valid;
}

uint64_t Tag_Store::offset(uint64_t addr) const
{
    uint64_t mask = (1<<(m_b))-1; // B 1's
    return (addr) & mask; // just clear all but the bottom B bits to get the offset
}

uint64_t Tag_Store::tag(uint64_t addr) const
{
    return addr >> (m_c-m_s);// shift by C-S to get just the tag
}
