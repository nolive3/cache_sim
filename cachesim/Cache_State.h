#ifndef CACHE_STATE_H
#define CACHE_STATE_H


class Cache_State
{
    public:
        /** Default constructor */
        Cache_State(uint64_t c, uint64_t b, uint64_t s, bool is_blocking, bool is_lru);
        /** Default destructor */
        virtual ~Cache_State();
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
        char[][] m_valid; //!< Member variable "m_valid"
        uint64_t m_c; //!< Member variable "m_c"
        uint64_t m_b; //!< Member variable "m_b"
        uint64_t m_s; //!< Member variable "m_s"
        bool m_f; //!< Member variable "m_f"
        bool m_r; //!< Member variable "m_r"
};

#endif // CACHE_STATE_H
