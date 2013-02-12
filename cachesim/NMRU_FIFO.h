#ifndef NMRU_FIFO_H
#define NMRU_FIFO_H

#include "Tag_Store.h"
#include <cstdint>


class mNMRU_FIFO : public Tag_Store
{
    public:
        mNMRU_FIFO(uint64_t s,uint64_t b,uint64_t c,bool r) : Tag_Store(s,b,c,r), m_mru(0) {}
        virtual ~mNMRU_FIFO() = default;
        virtual bool access(uint64_t addr);
    protected:
    private:
         bool contains(uint64_t addr) const;
         void get_victim(uint64_t tag);
         void touch(uint64_t tag);
        uint64_t m_mru;
};

#endif // NMRU_FIFO_H
