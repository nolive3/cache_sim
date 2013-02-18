#ifndef LRU_H
#define LRU_H

#include "Tag_Store.h"


class mLRU : public Tag_Store
{
    public:
        mLRU(uint64_t s,uint64_t b,uint64_t c,bool r) : Tag_Store(s,b,c,r){}
        ~mLRU() {}
    protected:
    private:
        void get_victim(uint64_t tag);
        void touch(uint64_t tag);
};

#endif // LRU_H
