#ifndef LRU_H
#define LRU_H

#include "Tag_Store.h"


class mLRU : public Tag_Store
{
    public:
        mLRU(uint64_t s) : Tag_Store(s){}
        virtual ~mLRU() = default;
        virtual uint64_t get(uint64_t index) const;
        virtual uint64_t get_victim(uint64_t tag);
        virtual void touch(uint64_t tag);
    protected:
    private:
};

#endif // LRU_H
