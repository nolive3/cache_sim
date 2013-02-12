#include "Tag_Store.h"

Tag_Store::Tag_Store(uint64_t s) : m_s(s), m_tags(new uint64_t[1<<s]), m_indexes(new uint64_t[1<<s])
{
    for (uint64_t i = 0; i < (uint64_t)1<<m_s; i++){
        m_indexes[i] = -1;
    }
}

Tag_Store::~Tag_Store()
{
    delete [] m_tags;
    delete [] m_indexes;
}
