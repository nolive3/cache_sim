#ifndef TAG_STORE_H
#define TAG_STORE_H
#include <cstdint>


class Tag_Store
{
    public:
        Tag_Store(uint64_t s);
        virtual ~Tag_Store();
        Tag_Store(const Tag_Store& other) = delete;
        Tag_Store& operator=(const Tag_Store& other) = delete;
        virtual bool contains(uint64_t index, uint64_t tag) const = 0;
        virtual uint64_t get_victim(uint64_t tag) = 0;
        virtual void touch(uint64_t tag) = 0;

    protected:
        uint64_t m_s;
        uint64_t m_last;
        uint64_t* m_tags;
        uint64_t* m_indexes;
    private:
};

#endif // TAG_STORE_H
