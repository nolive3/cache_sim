#ifndef LRU_H
#define LRU_H

#include "Tag_Store.h"


class mLRU : public Tag_Store
{
    public:
        mLRU(uint64_t s,uint64_t b,uint64_t c,bool r) : Tag_Store(s,b,c,r){}
        virtual ~mLRU() = default;
        virtual bool access(uint64_t addr);
    protected:
    private:
         bool contains(uint64_t addr) const;
         bool contains_but_not_valid(uint64_t addr) const;
         void get_victim(uint64_t tag);
         void touch(uint64_t tag);
};

#endif // LRU_H
