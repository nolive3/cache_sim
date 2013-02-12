#ifndef TAG_STORE_H
#define TAG_STORE_H
#include <cstdint>


class Tag_Store
{
    public:
        Tag_Store(uint64_t s, uint64_t b, uint64_t c, bool is_blocking);
        virtual ~Tag_Store();
        Tag_Store(const Tag_Store& other) = delete;
        Tag_Store& operator=(const Tag_Store& other) = delete;
        virtual bool access(uint64_t addr) = 0;
    protected:
        uint64_t tag(uint64_t addr) const;
        uint64_t offset(uint64_t addr) const;
        uint64_t m_s;
        uint64_t m_b;
        uint64_t m_c;
        bool m_r;
        bool** m_valid;
        uint64_t m_last;
        uint64_t* m_tags;
    private:
};

#endif // TAG_STORE_H
