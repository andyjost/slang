
        reference(block_type & b, block_type pos)
            :m_block(b),
             m_mask( (assert(pos < bits_per_block),
                      block_type(1) << pos )
                   )
        { }


        operator bool() const { return (m_block & m_mask) != 0; }

        bool operator~() const { return (m_block & m_mask) == 0; }


        reference& flip() { do_flip(); return *this; }


        reference& operator=(bool x)               { do_assign(x);   return *this; }

        reference& operator=(const reference& rhs) { do_assign(rhs); return *this; }


        reference& operator|=(bool x) { if  (x) do_set();   return *this; }

        reference& operator&=(bool x) { if (!x) do_reset(); return *this; }

        reference& operator^=(bool x) { if  (x) do_flip();  return *this; }

        reference& operator-=(bool x) { if  (x) do_reset(); return *this; }


        void do_set() { m_block |= m_mask; }

        void do_reset() { m_block &= ~m_mask; }

        void do_flip() { m_block ^= m_mask; }

        void do_assign(bool x) { x? do_set() : do_reset(); }

    template <typename BlockInputIterator>
    dynamic_bitset(BlockInputIterator first, BlockInputIterator last,
                   const Allocator& alloc = Allocator())

    :m_bits(alloc),
     m_num_bits(0)
    {
        using boost::detail::dynamic_bitset_impl::value_to_type;
        using boost::detail::dynamic_bitset_impl::is_numeric;

        const value_to_type<
            is_numeric<BlockInputIterator>::value> selector;

        dispatch_init(first, last, selector);
    }


    template <typename T>
    void dispatch_init(T num_bits, unsigned long value,
                       detail::dynamic_bitset_impl::value_to_type<true>)
    {
        init_from_unsigned_long(static_cast<size_type>(num_bits), value);
    }


    template <typename BlockIter>
    void init_from_block_range(BlockIter first, BlockIter last)
    {
        assert(m_bits.size() == 0);
        m_bits.insert(m_bits.end(), first, last);
        m_num_bits = m_bits.size() * bits_per_block;
    }


    template <typename BlockInputIterator>
    void m_append(BlockInputIterator first, BlockInputIterator last, std::input_iterator_tag)
    {
        std::vector<Block, Allocator> v(first, last);
        m_append(v.begin(), v.end(), std::random_access_iterator_tag());
    }

    template <typename BlockInputIterator>
    void append(BlockInputIterator first, BlockInputIterator last) // strong guarantee
    {
        if (first != last) {
            typename detail::iterator_traits<BlockInputIterator>::iterator_category cat;
            m_append(first, last, cat);
        }
    }

    reference operator[](size_type pos) {
        return reference(m_bits[block_index(pos)], bit_index(pos));
    }

    bool operator[](size_type pos) const { return test(pos); }


    block_width_type count_extra_bits() const { return bit_index(size()); }

    static size_type block_index(size_type pos) { return pos / bits_per_block; }

    static block_width_type bit_index(size_type pos) { return static_cast<block_width_type>(pos % bits_per_block); }

    static Block bit_mask(size_type pos) { return Block(1) << bit_index(pos); }


    template <typename CharT, typename Traits, typename Alloc>
    void init_from_string(const std::basic_string<CharT, Traits, Alloc>& s,
        typename std::basic_string<CharT, Traits, Alloc>::size_type pos,
        typename std::basic_string<CharT, Traits, Alloc>::size_type n,
        size_type num_bits)
    {
        assert(pos <= s.size());

        typedef typename std::basic_string<CharT, Traits, Alloc> StrT;
        typedef typename StrT::traits_type Tr;

        const typename StrT::size_type rlen = (std::min)(n, s.size() - pos);
        const size_type sz = ( num_bits != npos? num_bits : rlen);
        m_bits.resize(calc_num_blocks(sz));
        m_num_bits = sz;


        BOOST_DYNAMIC_BITSET_CTYPE_FACET(CharT, fac, std::locale());
        const CharT one = BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, '1');

        const size_type m = num_bits < rlen ? num_bits : rlen;
        typename StrT::size_type i = 0;
        for( ; i < m; ++i) {

            const CharT c = s[(pos + m - 1) - i];

            assert( Tr::eq(c, one)
                    || Tr::eq(c, BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, '0')) );

            if (Tr::eq(c, one))
                set(i);

        }

    }


    void init_from_unsigned_long(size_type num_bits,
                                 unsigned long value/*,
                                 const Allocator& alloc*/)
    {

        assert(m_bits.size() == 0);

        m_bits.resize(calc_num_blocks(num_bits));
        m_num_bits = num_bits;

        typedef unsigned long num_type;
        typedef boost::detail::dynamic_bitset_impl
            ::shifter<num_type, bits_per_block, ulong_width> shifter;

        //if (num_bits == 0)
        //    return;

        // zero out all bits at pos >= num_bits, if any;
        // note that: num_bits == 0 implies value == 0
        if (num_bits < static_cast<size_type>(ulong_width)) {
            const num_type mask = (num_type(1) << num_bits) - 1;
            value &= mask;
        }

        typename buffer_type::iterator it = m_bits.begin();
        for( ; value; shifter::left_shift(value), ++it) {
            *it = static_cast<block_type>(value);
        }

    }

        bit_appender(dynamic_bitset & r) : bs(r), n(0), mask(0), current(0) {}

        ~bit_appender() {
            // reverse the order of blocks, shift
            // if needed, and then resize
            //
            std::reverse(bs.m_bits.begin(), bs.m_bits.end());
            const block_width_type offs = bit_index(n);
            if (offs)
                bs >>= (bits_per_block - offs);
            bs.resize(n); // doesn't enlarge, so can't throw
            assert(bs.m_check_invariants());
        }

        inline void do_append(bool value) {

            if (mask == 0) {
                bs.append(Block(0));
                current = &bs.m_highest_block();
                mask = Block(1) << (bits_per_block - 1);
            }

            if(value)
                *current |= mask;

            mask /= 2;
            ++n;
        }

        size_type get_count() const { return n; }



template <typename BlockIterator, typename B, typename A>
inline void
from_block_range(BlockIterator first, BlockIterator last,
                 dynamic_bitset<B, A>& result)
{
    // PRE: distance(first, last) <= numblocks()
    std::copy (first, last, result.m_bits.begin());
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>::dynamic_bitset(const Allocator& alloc)
  : m_bits(alloc), m_num_bits(0)
{

}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>::
dynamic_bitset(size_type num_bits, unsigned long value, const Allocator& alloc)
    : m_bits(alloc),
      m_num_bits(0)
{
    init_from_unsigned_long(num_bits, value);
}

template <typename Block, typename Allocator>
inline dynamic_bitset<Block, Allocator>::
dynamic_bitset(const dynamic_bitset& b)
  : m_bits(b.m_bits), m_num_bits(b.m_num_bits)
{

}


template <typename Block, typename Allocator>
inline dynamic_bitset<Block, Allocator>::
~dynamic_bitset()
{
    assert(m_check_invariants());
}


template <typename Block, typename Allocator>
inline void dynamic_bitset<Block, Allocator>::
swap(dynamic_bitset<Block, Allocator>& b) // no throw
{
    std::swap(m_bits, b.m_bits);
    std::swap(m_num_bits, b.m_num_bits);
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>& dynamic_bitset<Block, Allocator>::
operator=(const dynamic_bitset<Block, Allocator>& b)
{
    m_bits = b.m_bits;
    m_num_bits = b.m_num_bits;
    return *this;
}


template <typename Block, typename Allocator>
inline typename dynamic_bitset<Block, Allocator>::allocator_type
dynamic_bitset<Block, Allocator>::get_allocator() const
{
    return m_bits.get_allocator();
}


template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
resize(size_type num_bits, bool value) // strong guarantee
{

  const size_type old_num_blocks = num_blocks();
  const size_type required_blocks = calc_num_blocks(num_bits);

  const block_type v = value? ~Block(0) : Block(0);

  if (required_blocks != old_num_blocks) {
    m_bits.resize(required_blocks, v); // s.g. (copy)
  }


  // At this point:
  //
  //  - if the buffer was shrunk, we have nothing more to do,
  //    except a call to m_zero_unused_bits()
  //
  //  - if it was enlarged, all the (used) bits in the new blocks have
  //    the correct value, but we have not yet touched those bits, if
  //    any, that were 'unused bits' before enlarging: if value == true,
  //    they must be set.

  if (value && (num_bits > m_num_bits)) {

    const block_width_type extra_bits = count_extra_bits();
    if (extra_bits) {
        assert(old_num_blocks >= 1 && old_num_blocks <= m_bits.size());

        // Set them.
        m_bits[old_num_blocks - 1] |= (v << extra_bits);
    }

  }

  m_num_bits = num_bits;
  m_zero_unused_bits();

}


template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
clear() // no throw
{
  m_bits.clear();
  m_num_bits = 0;
}



template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
push_back(bool bit)
{
  const size_type sz = size();
  resize(sz + 1);
  set(sz, bit);
}


template <typename Block, typename Allocator>
void dynamic_bitset<Block, Allocator>::
append(Block value) // strong guarantee
{
    const block_width_type r = count_extra_bits();

    if (r == 0) {
        // the buffer is empty, or all blocks are filled
        m_bits.push_back(value);
    }
    else {
        m_bits.push_back(value >> (bits_per_block - r));
        m_bits[m_bits.size() - 2] |= (value << r); // m_bits.size() >= 2
    }

    m_num_bits += bits_per_block;
    assert(m_check_invariants());

}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator&=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < num_blocks(); ++i)
        m_bits[i] &= rhs.m_bits[i];
    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator|=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < num_blocks(); ++i)
        m_bits[i] |= rhs.m_bits[i];
    //m_zero_unused_bits();
    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator^=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < this->num_blocks(); ++i)
        m_bits[i] ^= rhs.m_bits[i];
    //m_zero_unused_bits();
    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator-=(const dynamic_bitset& rhs)
{
    assert(size() == rhs.size());
    for (size_type i = 0; i < num_blocks(); ++i)
        m_bits[i] &= ~rhs.m_bits[i];
    //m_zero_unused_bits();
    return *this;
}

template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::operator<<=(size_type n)
{
    if (n >= m_num_bits)
        return reset();
    //else
    if (n > 0) {

        size_type    const last = num_blocks() - 1;  // num_blocks() is >= 1
        size_type    const div  = n / bits_per_block; // div is <= last
        block_width_type const r = bit_index(n);
        block_type * const b    = &m_bits[0];

        if (r != 0) {

            block_width_type const rs = bits_per_block - r;

            for (size_type i = last-div; i>0; --i) {
                b[i+div] = (b[i] << r) | (b[i-1] >> rs);
            }
            b[div] = b[0] << r;

        }
        else {
            for (size_type i = last-div; i>0; --i) {
                b[i+div] = b[i];
            }
            b[div] = b[0];
        }

        // zero out div blocks at the less significant end
        std::fill_n(b, div, static_cast<block_type>(0));

        // zero out any 1 bit that flowed into the unused part
        m_zero_unused_bits(); // thanks to Lester Gong

    }

    return *this;


}

template <typename B, typename A>
dynamic_bitset<B, A> & dynamic_bitset<B, A>::operator>>=(size_type n) {
    if (n >= m_num_bits) {
        return reset();
    }
    //else
    if (n>0) {

        size_type  const last  = num_blocks() - 1; // num_blocks() is >= 1
        size_type  const div   = n / bits_per_block;   // div is <= last
        block_width_type const r     = bit_index(n);
        block_type * const b   = &m_bits[0];


        if (r != 0) {

            block_width_type const ls = bits_per_block - r;

            for (size_type i = div; i < last; ++i) {
                b[i-div] = (b[i] >> r) | (b[i+1]  << ls);
            }
            // r bits go to zero
            b[last-div] = b[last] >> r;
        }

        else {
            for (size_type i = div; i <= last; ++i) {
                b[i-div] = b[i];
            }
            // note the '<=': the last iteration 'absorbs'
            // b[last-div] = b[last] >> 0;
        }



        // div blocks are zero filled at the most significant end
        std::fill_n(b + (num_blocks()-div), div, static_cast<block_type>(0));
    }

    return *this;
}



template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator<<(size_type n) const
{
    dynamic_bitset r(*this);
    return r <<= n;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator>>(size_type n) const
{
    dynamic_bitset r(*this);
    return r >>= n;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::set(size_type pos, bool val)
{
    assert(pos < m_num_bits);

    if (val)
        m_bits[block_index(pos)] |= bit_mask(pos);
    else
        reset(pos);

    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::set()
{
  std::fill(m_bits.begin(), m_bits.end(), ~Block(0));
  m_zero_unused_bits();
  return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::reset(size_type pos)
{
    assert(pos < m_num_bits);
#if defined __MWERKS__ && BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
    // CodeWarrior 8 generates incorrect code when the &=~ is compiled,
    // use the |^ variation instead.. <grafik>
    m_bits[block_index(pos)] |= bit_mask(pos);
    m_bits[block_index(pos)] ^= bit_mask(pos);
#else
    m_bits[block_index(pos)] &= ~bit_mask(pos);
#endif
    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::reset()
{
  std::fill(m_bits.begin(), m_bits.end(), Block(0));
  return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::flip(size_type pos)
{
    assert(pos < m_num_bits);
    m_bits[block_index(pos)] ^= bit_mask(pos);
    return *this;
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>&
dynamic_bitset<Block, Allocator>::flip()
{
    for (size_type i = 0; i < num_blocks(); ++i)
        m_bits[i] = ~m_bits[i];
    m_zero_unused_bits();
    return *this;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::m_unchecked_test(size_type pos) const
{
    return (m_bits[block_index(pos)] & bit_mask(pos)) != 0;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::test(size_type pos) const
{
    assert(pos < m_num_bits);
    return m_unchecked_test(pos);
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::any() const
{
    for (size_type i = 0; i < num_blocks(); ++i)
        if (m_bits[i])
            return true;
    return false;
}


template <typename Block, typename Allocator>
inline bool dynamic_bitset<Block, Allocator>::none() const
{
    return !any();
}


template <typename Block, typename Allocator>
dynamic_bitset<Block, Allocator>
dynamic_bitset<Block, Allocator>::operator~() const
{
    dynamic_bitset b(*this);
    b.flip();
    return b;
}


template <typename Block, typename Allocator>
typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::count() const
{
    using detail::dynamic_bitset_impl::table_width;
    using detail::dynamic_bitset_impl::access_by_bytes;
    using detail::dynamic_bitset_impl::access_by_blocks;
    using detail::dynamic_bitset_impl::value_to_type;

#if BOOST_WORKAROUND(__GNUC__, == 4) && (__GNUC_MINOR__ == 3) && (__GNUC_PATCHLEVEL__ == 3)
    // NOTE: Explicit qualification of "bits_per_block"
    //       breaks compilation on gcc 4.3.3
    enum { no_padding = bits_per_block == CHAR_BIT * sizeof(Block) };
#else
    // NOTE: Explicitly qualifying "bits_per_block" to workaround
    //       regressions of gcc 3.4.x
    enum { no_padding =
        dynamic_bitset<Block, Allocator>::bits_per_block
        == CHAR_BIT * sizeof(Block) };
#endif

    enum { enough_table_width = table_width >= CHAR_BIT };

    enum { mode = (no_padding && enough_table_width)
                          ? access_by_bytes
                          : access_by_blocks };

    return do_count(m_bits.begin(), num_blocks(), Block(0),
                    static_cast<value_to_type<(bool)mode> *>(0));
}



template <typename B, typename A, typename stringT>
void to_string_helper(const dynamic_bitset<B, A> & b, stringT & s,
                      bool dump_all)
{
    typedef typename stringT::traits_type Tr;
    typedef typename stringT::value_type  Ch;

    BOOST_DYNAMIC_BITSET_CTYPE_FACET(Ch, fac, std::locale());
    const Ch zero = BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, '0');
    const Ch one  = BOOST_DYNAMIC_BITSET_WIDEN_CHAR(fac, '1');

    // Note that this function may access (when
    // dump_all == true) bits beyond position size() - 1

    typedef typename dynamic_bitset<B, A>::size_type size_type;

    const size_type len = dump_all?
         dynamic_bitset<B, A>::bits_per_block * b.num_blocks():
         b.size();
    s.assign (len, zero);

    for (size_type i = 0; i < len; ++i) {
        if (b.m_unchecked_test(i))
            Tr::assign(s[len - 1 - i], one);

    }

}

template <typename Block, typename Allocator, typename stringT>
inline void
to_string(const dynamic_bitset<Block, Allocator>& b, stringT& s)
{
    to_string_helper(b, s, false);
}

template <typename B, typename A, typename stringT>
inline void
dump_to_string(const dynamic_bitset<B, A>& b, stringT& s)
{
    to_string_helper(b, s, true /* =dump_all*/);
}


template <typename Block, typename Allocator, typename BlockOutputIterator>
inline void
to_block_range(const dynamic_bitset<Block, Allocator>& b,
               BlockOutputIterator result)
{
    // note how this copies *all* bits, including the
    // unused ones in the last block (which are zero)
    std::copy(b.m_bits.begin(), b.m_bits.end(), result);
}


template <typename Block, typename Allocator>
unsigned long dynamic_bitset<Block, Allocator>::
to_ulong() const
{

  if (m_num_bits == 0)
      return 0; // convention

  // Check for overflows. This may be a performance burden on very
  // large bitsets but is required by the specification, sorry
  if (find_next(ulong_width - 1) != npos)
    throw std::overflow_error("boost::dynamic_bitset::to_ulong overflow");


  // Ok, from now on we can be sure there's no "on" bit
  // beyond the "allowed" positions
  typedef unsigned long result_type;

  const size_type maximum_size =
            (std::min)(m_num_bits, static_cast<size_type>(ulong_width));

  const size_type last_block = block_index( maximum_size - 1 );

  assert((last_block * bits_per_block) < static_cast<size_type>(ulong_width));

  result_type result = 0;
  for (size_type i = 0; i <= last_block; ++i) {
    const size_type offset = i * bits_per_block;
    result |= (static_cast<result_type>(m_bits[i]) << offset);
  }

  return result;
}


template <typename Block, typename Allocator>
inline typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::size() const
{
    return m_num_bits;
}


template <typename Block, typename Allocator>
inline typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::num_blocks() const
{
    return m_bits.size();
}


template <typename Block, typename Allocator>
inline typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::max_size() const
{
    // Semantics of vector<>::max_size() aren't very clear
    // (see lib issue 197) and many library implementations
    // simply return dummy values, _unrelated_ to the underlying
    // allocator.
    //
    // Given these problems, I was tempted to not provide this
    // function at all but the user could need it if he provides
    // his own allocator.
    //

    const size_type m = detail::dynamic_bitset_impl::
                        vector_max_size_workaround(m_bits);

    return m <= (size_type(-1)/bits_per_block) ?
        m * bits_per_block :
        size_type(-1);
}


template <typename Block, typename Allocator>
inline bool dynamic_bitset<Block, Allocator>::empty() const
{
  return size() == 0;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::
is_subset_of(const dynamic_bitset<Block, Allocator>& a) const
{
    assert(size() == a.size());
    for (size_type i = 0; i < num_blocks(); ++i)
        if (m_bits[i] & ~a.m_bits[i])
            return false;
    return true;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::
is_proper_subset_of(const dynamic_bitset<Block, Allocator>& a) const
{
    assert(size() == a.size());
    assert(num_blocks() == a.num_blocks());

    bool proper = false;
    for (size_type i = 0; i < num_blocks(); ++i) {
        const Block & bt =   m_bits[i];
        const Block & ba = a.m_bits[i];

        if (bt & ~ba)
            return false; // not a subset at all
        if (ba & ~bt)
            proper = true;
    }
    return proper;
}


template <typename Block, typename Allocator>
bool dynamic_bitset<Block, Allocator>::intersects(const dynamic_bitset & b) const
{
    size_type common_blocks = num_blocks() < b.num_blocks()
                              ? num_blocks() : b.num_blocks();

    for(size_type i = 0; i < common_blocks; ++i) {
        if(m_bits[i] & b.m_bits[i])
            return true;
    }
    return false;
}

template <typename Block, typename Allocator>
typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::m_do_find_from(size_type first_block) const
{
    size_type i = first_block;

    // skip null blocks
    while (i < num_blocks() && m_bits[i] == 0)
        ++i;

    if (i >= num_blocks())
        return npos; // not found

    return i * bits_per_block + boost::lowest_bit(m_bits[i]);

}



template <typename Block, typename Allocator>
typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::find_first() const
{
    return m_do_find_from(0);
}



template <typename Block, typename Allocator>
typename dynamic_bitset<Block, Allocator>::size_type
dynamic_bitset<Block, Allocator>::find_next(size_type pos) const
{

    const size_type sz = size();
    if (pos >= (sz-1) || sz == 0)
        return npos;

    ++pos;

    const size_type blk = block_index(pos);
    const block_width_type ind = bit_index(pos);

    // mask out bits before pos
    const Block fore = m_bits[blk] & ( ~Block(0) << ind );

    return fore?
        blk * bits_per_block + lowest_bit(fore)
        :
        m_do_find_from(blk + 1);

}


template <typename Block, typename Allocator>
bool operator==(const dynamic_bitset<Block, Allocator>& a,
                const dynamic_bitset<Block, Allocator>& b)
{
    return (a.m_num_bits == b.m_num_bits)
           && (a.m_bits == b.m_bits);
}


template <typename Block, typename Allocator>
inline bool operator!=(const dynamic_bitset<Block, Allocator>& a,
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a == b);
}


template <typename Block, typename Allocator>
bool operator<(const dynamic_bitset<Block, Allocator>& a,
               const dynamic_bitset<Block, Allocator>& b)
{
    assert(a.size() == b.size());
    typedef typename dynamic_bitset<Block, Allocator>::size_type size_type;

    //if (a.size() == 0)
    //  return false;

    // Since we are storing the most significant bit
    // at pos == size() - 1, we need to do the comparisons in reverse.
    //
    for (size_type ii = a.num_blocks(); ii > 0; --ii) {
      size_type i = ii-1;
      if (a.m_bits[i] < b.m_bits[i])
        return true;
      else if (a.m_bits[i] > b.m_bits[i])
        return false;
    }
    return false;
}


template <typename Block, typename Allocator>
inline bool operator<=(const dynamic_bitset<Block, Allocator>& a,
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a > b);
}


template <typename Block, typename Allocator>
inline bool operator>(const dynamic_bitset<Block, Allocator>& a,
                      const dynamic_bitset<Block, Allocator>& b)
{
    return b < a;
}


template <typename Block, typename Allocator>
inline bool operator>=(const dynamic_bitset<Block, Allocator>& a,
                       const dynamic_bitset<Block, Allocator>& b)
{
    return !(a < b);
}

    template <typename T> T make_non_const(T t) { return t; }
