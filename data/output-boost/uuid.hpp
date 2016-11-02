
    
    uuid operator()() const {
        // initialize to all zeros
        uuid u = {{0}};
        return u;
    }


inline uuid nil_uuid() {
    return nil_generator()();
}


    explicit name_generator(uuid const& namespace_uuid)
        : namespace_uuid(namespace_uuid)
    {}


    uuid operator()(const char* name) {
        reset();
        process_characters(name, std::strlen(name));
        return sha_to_uuid();
    }

    template <typename char_type>
    void process_characters(char_type const*const characters, size_t count) {
        BOOST_ASSERT(sizeof(uint32_t) >= sizeof(char_type));

        for (size_t i=0; i<count; i++) {
            uint32_t c = characters[i];
            sha.process_byte( (c >>  0) & 0xFF );
            sha.process_byte( (c >>  8) & 0xFF );
            sha.process_byte( (c >> 16) & 0xFF );
            sha.process_byte( (c >> 24) & 0xFF );
        }
    }


    void reset()
    {
        sha.reset();
        sha.process_bytes(namespace_uuid.begin(), namespace_uuid.size());
    }

    
    uuid sha_to_uuid()
    {
        unsigned int digest[5];

        sha.get_digest(digest);

        uuid u;
        for (int i=0; i<4; ++i) {
            *(u.begin() + i*4+0) = ((digest[i] >> 24) & 0xFF);
            *(u.begin() + i*4+1) = ((digest[i] >> 16) & 0xFF);
            *(u.begin() + i*4+2) = ((digest[i] >> 8) & 0xFF);
            *(u.begin() + i*4+3) = ((digest[i] >> 0) & 0xFF);
        }

        // set variant
        // must be 0b10xxxxxx
        *(u.begin()+8) &= 0xBF;
        *(u.begin()+8) |= 0x80;

        // set version
        // must be 0b0101xxxx
        *(u.begin()+6) &= 0x5F; //0b01011111
        *(u.begin()+6) |= 0x50; //0b01010000

        return u;
    }


inline unsigned int left_rotate(unsigned int x, std::size_t n)
{
    return (x<<n) ^ (x>> (32-n));
}


inline sha1::sha1()
{
    reset();
}


inline void sha1::reset()
{
    h_[0] = 0x67452301;
    h_[1] = 0xEFCDAB89;
    h_[2] = 0x98BADCFE;
    h_[3] = 0x10325476;
    h_[4] = 0xC3D2E1F0;

    block_byte_index_ = 0;
    bit_count_low = 0;
    bit_count_high = 0;
}


inline void sha1::process_byte(unsigned char byte)
{
    process_byte_impl(byte);

    // size_t max value = 0xFFFFFFFF
    //if (bit_count_low + 8 >= 0x100000000) { // would overflow
    //if (bit_count_low >= 0x100000000-8) {
    if (bit_count_low < 0xFFFFFFF8) {
        bit_count_low += 8;
    } else {
        bit_count_low = 0;

        if (bit_count_high <= 0xFFFFFFFE) {
            ++bit_count_high;
        } else {
            BOOST_THROW_EXCEPTION(std::runtime_error("sha1 too many bytes"));
        }
    }
}


inline void sha1::process_byte_impl(unsigned char byte)
{
    block_[block_byte_index_++] = byte;

    if (block_byte_index_ == 64) {
        block_byte_index_ = 0;
        process_block();
    }
}


inline void sha1::process_block(void const* bytes_begin, void const* bytes_end)
{
    unsigned char const* begin = static_cast<unsigned char const*>(bytes_begin);
    unsigned char const* end = static_cast<unsigned char const*>(bytes_end);
    for(; begin != end; ++begin) {
        process_byte(*begin);
    }
}


inline void sha1::process_block()
{
    unsigned int w[80];
    for (std::size_t i=0; i<16; ++i) {
        w[i]  = (block_[i*4 + 0] << 24);
        w[i] |= (block_[i*4 + 1] << 16);
        w[i] |= (block_[i*4 + 2] << 8);
        w[i] |= (block_[i*4 + 3]);
    }
    for (std::size_t i=16; i<80; ++i) {
        w[i] = left_rotate((w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]), 1);
    }

    unsigned int a = h_[0];
    unsigned int b = h_[1];
    unsigned int c = h_[2];
    unsigned int d = h_[3];
    unsigned int e = h_[4];

    for (std::size_t i=0; i<80; ++i) {
        unsigned int f;
        unsigned int k;

        if (i<20) {
            f = (b & c) | (~b & d);
            k = 0x5A827999;
        } else if (i<40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if (i<60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        unsigned temp = left_rotate(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = left_rotate(b, 30);
        b = a;
        a = temp;
    }

    h_[0] += a;
    h_[1] += b;
    h_[2] += c;
    h_[3] += d;
    h_[4] += e;
}


inline void sha1::get_digest(digest_type digest)
{
    // append the bit '1' to the message
    process_byte_impl(0x80);

    // append k bits '0', where k is the minimum number >= 0
    // such that the resulting message length is congruent to 56 (mod 64)
    // check if there is enough space for padding and bit_count
    if (block_byte_index_ > 56) {
        // finish this block
        while (block_byte_index_ != 0) {
            process_byte_impl(0);
        }

        // one more block
        while (block_byte_index_ < 56) {
            process_byte_impl(0);
        }
    } else {
        while (block_byte_index_ < 56) {
            process_byte_impl(0);
        }
    }

    // append length of message (before pre-processing) 
    // as a 64-bit big-endian integer
    process_byte_impl( static_cast<unsigned char>((bit_count_high>>24) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_high>>16) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_high>>8 ) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_high)     & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_low>>24) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_low>>16) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_low>>8 ) & 0xFF) );
    process_byte_impl( static_cast<unsigned char>((bit_count_low)     & 0xFF) );

    // get final digest
    digest[0] = h_[0];
    digest[1] = h_[1];
    digest[2] = h_[2];
    digest[3] = h_[3];
    digest[4] = h_[4];
}

    
    template <typename ch, typename char_traits, typename alloc>
    uuid operator()(std::basic_string<ch, char_traits, alloc> const& s) const {
        return operator()(s.begin(), s.end());
    }

    seed_rng()
        : rd_index_(5)
        , random_(std::fopen( "/dev/urandom", "rb" ))
    {}


    ~seed_rng()
    {
        if (random_) {
            std::fclose(random_);
        }
    }

    generator_iterator() : m_g(NULL), m_value(0) {}

    generator_iterator(Generator* g) : m_g(g), m_value((*m_g)()) {}


    void increment()
    {
        m_value = (*m_g)();
    }


    const typename Generator::result_type&
    dereference() const
    {
        return m_value;
    }


    bool equal(generator_iterator const& y) const
    {
        return this->m_g == y.m_g && this->m_value == y.m_value;
    }


template <typename UniformRandomNumberGenerator>
inline void seed(UniformRandomNumberGenerator& rng)
{
    seed_rng seed_gen;
    generator_iterator<seed_rng> begin(&seed_gen);
    generator_iterator<seed_rng> end;
    rng.seed(begin, end);
}

    static size_type static_size() { return 16; }

    iterator begin() { return data; }

    iterator end() { return data+size(); }


    size_type size() const { return static_size(); }


    bool is_nil() const /* throw() */
    {
        for(size_t i=0; i<static_size(); i++) {
            if (data[i] != 0U) {
                return false;
            }
        }
        return true;
    }

    variant_type variant() const /* throw() */
    {
        // variant is stored in octet 7
        // which is index 8, since indexes count backwards
        unsigned char octet7 = data[8]; // octet 7 is array index 8
        if ( (octet7 & 0x80) == 0x00 ) { // 0b0xxxxxxx
            return variant_ncs;
        } else if ( (octet7 & 0xC0) == 0x80 ) { // 0b10xxxxxx
            return variant_rfc_4122;
        } else if ( (octet7 & 0xE0) == 0xC0 ) { // 0b110xxxxx
            return variant_microsoft;
        } else {
            //assert( (octet7 & 0xE0) == 0xE0 ) // 0b111xxxx
            return variant_future;
        }
    }

    version_type version() const /* throw() */
    {
        //version is stored in octet 9
        // which is index 6, since indexes count backwards
        unsigned char octet9 = data[6];
        if ( (octet9 & 0xF0) == 0x10 ) {
            return version_time_based;
        } else if ( (octet9 & 0xF0) == 0x20 ) {
            return version_dce_security;
        } else if ( (octet9 & 0xF0) == 0x30 ) {
            return version_name_based_md5;
        } else if ( (octet9 & 0xF0) == 0x40 ) {
            return version_random_number_based;
        } else if ( (octet9 & 0xF0) == 0x50 ) {
            return version_name_based_sha1;
        } else {
            return version_unknown;
        }
    }

    void swap(uuid& rhs) /* throw() */
    {
        std::swap_ranges(begin(), end(), rhs.begin());
    }


inline bool operator==(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}


inline bool operator!=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(lhs == rhs);
}


inline bool operator<(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


inline bool operator>(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return rhs < lhs;
}

inline bool operator<=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(rhs < lhs);
}


inline bool operator>=(uuid const& lhs, uuid const& rhs) /* throw() */
{
    return !(lhs < rhs);
}


inline void swap(uuid& lhs, uuid& rhs) /* throw() */
{
    lhs.swap(rhs);
}

inline std::size_t hash_value(uuid const& u) /* throw() */
{
    std::size_t seed = 0;
    for(uuid::const_iterator i=u.begin(); i != u.end(); ++i)
    {
        seed ^= static_cast<std::size_t>(*i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    return seed;
}

        void operator()(void const *) const {}

    basic_random_generator()
        : pURNG(new UniformRandomNumberGenerator)
        , generator
          ( pURNG.get()
          , distribution_type
            ( (std::numeric_limits<unsigned long>::min)()
            , (std::numeric_limits<unsigned long>::max)()
            )
          )
    {
        // seed the random number generator
        detail::seed(*pURNG);
    }

    explicit basic_random_generator(UniformRandomNumberGenerator& gen)
        : pURNG(&gen, null_deleter())
        , generator
          ( pURNG.get()
          , distribution_type
            ( (std::numeric_limits<unsigned long>::min)()
            , (std::numeric_limits<unsigned long>::max)()
            )
          )
    {}

    explicit basic_random_generator(UniformRandomNumberGenerator* pGen)
        : pURNG(pGen, null_deleter())
        , generator
          ( pURNG.get()
          , distribution_type
            ( (std::numeric_limits<unsigned long>::min)()
            , (std::numeric_limits<unsigned long>::max)()
            )
          )
    {
        BOOST_ASSERT(pURNG);
    }

    
    uuid operator()()
    {
        uuid u;
        
        int i=0;
        unsigned long random_value = generator();
        for (uuid::iterator it=u.begin(); it!=u.end(); ++it, ++i) {
            if (i==sizeof(unsigned long)) {
                random_value = generator();
                i = 0;
            }

			// static_cast gets rid of warnings of converting unsigned long to boost::uint8_t
            *it = static_cast<uuid::value_type>((random_value >> (i*8)) & 0xFF);
        }

        // set variant
        // must be 0b10xxxxxx
        *(u.begin()+8) &= 0xBF;
        *(u.begin()+8) |= 0x80;

        // set version
        // must be 0b0100xxxx
        *(u.begin()+6) &= 0x4F; //0b01001111
        *(u.begin()+6) |= 0x40; //0b01000000

        return u;
    }
