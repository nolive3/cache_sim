#include "Cache_State.h"

Cache_State::Cache_State(uint64_t c, uint64_t b, uint64_t s, bool is_blocking, bool is_lru) : m_c(c), m_b(b), m_s(s), m_f(is_blocking), m_r(is_lru)
{
    //ctor
}

Cache_State::~Cache_State()
{
    //dtor
}
