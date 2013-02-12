#ifndef NMRU_FIFO_H
#define NMRU_FIFO_H

#include "Tag_Store.h"
#include <cstdint>


class mNMRU_FIFO : public Tag_Store
{
    public:
        mNMRU_FIFO(uint64_t s) : Tag_Store(s), m_mru(0) {}
        virtual ~mNMRU_FIFO() = default;
        virtual uint64_t get(uint64_t index) const;
        virtual uint64_t get_victim(uint64_t tag);
        virtual void touch(uint64_t tag);
    protected:
    private:
        uint64_t m_mru;
};

#endif // NMRU_FIFO_H
