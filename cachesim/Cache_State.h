#ifndef CACHE_STATE_H
#define CACHE_STATE_H
#include <stdint.h>
#include "Tag_Store.h"
#include "cachesim.hpp"
class Cache_State
{
    public:
        /** Default constructor */
        Cache_State(uint64_t c, uint64_t b, uint64_t s, bool is_blocking, bool is_lru);
        /** Default destructor */
        virtual ~Cache_State();
        void read(uint64_t addr, cache_stats_t* p_stats);
        void write(uint64_t addr, cache_stats_t* p_stats);
        /** Access m_valid
         * \return The current value of m_valid
         */
        uint64_t c() { return m_c; }
        /** Access m_b
         * \return The current value of m_b
         */
        uint64_t b() { return m_b; }
        /** Access m_s
         * \return The current value of m_s
         */
        uint64_t s() { return m_s; }
        /** Access m_f
         * \return The current value of m_f
         */
        bool f() { return m_f; }
        /** Access m_r
         * \return The current value of m_r
         */
        bool r() { return m_r; }
    protected:
    private:
        Cache_State(const Cache_State&);
        const Cache_State& operator=(const Cache_State&);
        uint64_t index(uint64_t addr) const;
        Tag_Store** m_tagstore; // the tag store [SET] each set manages its self
        uint64_t m_c; // C
        uint64_t m_b; // B
        uint64_t m_s; // S
        bool m_f; // true for blocking false for critical word first
        bool m_r; // true for LRU false for NMRU_FIFO
};

#endif // CACHE_STATE_H
