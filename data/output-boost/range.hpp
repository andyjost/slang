
        inline std::size_t length( const char* s )
        {
            return strlen( s );
        }


        inline bool is_char_ptr( char* )
        {
            return true;
        }


        inline bool is_char_ptr( const char* )
        {
            return true;
        }

        inline bool is_char_ptr( wchar_t* )
        {
            return true;
        }


        inline bool is_char_ptr( const wchar_t* )
        {
            return true;
        }


        template< class T >
        inline long is_char_ptr( const T& /* r */ )
        {
            return 0L;
        }


        template< typename Iterator >
        inline Iterator range_end( const std::pair<Iterator,Iterator>& p )
        {
            return p.second;
        }


        template< typename T, std::size_t sz >
        inline const T* range_end( const T (&a)[sz] )
        {
            return range_detail::array_end<T,sz>( a );
        }


        template< typename T, std::size_t sz >
        inline T* range_end( T (&a)[sz] )
        {
            return range_detail::array_end<T,sz>( a );
        }

            template< class ForwardRange >
            static IteratorT adl_begin( ForwardRange& r )
            {
                return static_cast<IteratorT>( boost::begin( r ) );
            }


            template< class ForwardRange >
            static IteratorT adl_end( ForwardRange& r )
            {
                return static_cast<IteratorT>( boost::end( r ) );
            }


        template< class Left, class Right >
        inline bool less_than( const Left& l, const Right& r )
        {
            return std::lexicographical_compare( boost::begin(l),
                                                 boost::end(l),
                                                 boost::begin(r),
                                                 boost::end(r) );
        }

        
        template< class Left, class Right >
        inline bool greater_than( const Left& l, const Right& r )
        {
            return less_than(r,l);
        }

        
        template< class Left, class Right >
        inline bool less_or_equal_than( const Left& l, const Right& r )
        {
            return !iterator_range_detail::less_than(r,l);
        }

        
        template< class Left, class Right >
        inline bool greater_or_equal_than( const Left& l, const Right& r )
        {
            return !iterator_range_detail::less_than(l,r);
        }

        template< class Left, class Right >
        inline bool equal(const Left& l, const Right& r)
        {
            return boost::equal(l, r);
        }

            iterator_range() : m_Begin( iterator() ), m_End( iterator() )
            { }

            template< class Iterator >
            iterator_range( Iterator Begin, Iterator End ) :
                m_Begin(Begin), m_End(End)
            {}

            template< class Range >
            iterator_range( const Range& r ) :
                m_Begin( impl::adl_begin( r ) ), m_End( impl::adl_end( r ) )
            {}

            template< class Range >
            iterator_range( Range& r ) :
                m_Begin( impl::adl_begin( r ) ), m_End( impl::adl_end( r ) )
            {}

            template< class Range >
            iterator_range( const Range& r, iterator_range_detail::const_range_tag ) :
                m_Begin( impl::adl_begin( r ) ), m_End( impl::adl_end( r ) )
            {}

            template< class Range >
            iterator_range( Range& r, iterator_range_detail::range_tag ) :
                m_Begin( impl::adl_begin( r ) ), m_End( impl::adl_end( r ) )
            {}


            template< class Iterator >
            iterator_range& operator=( const iterator_range<Iterator>& r )
            {
                m_Begin  = r.begin();
                m_End    = r.end();
                return *this;
            }


            template< class ForwardRange >
            iterator_range& operator=( ForwardRange& r )
            {
                m_Begin  = impl::adl_begin( r );
                m_End    = impl::adl_end( r );
                return *this;
            }


            template< class ForwardRange >
            iterator_range& operator=( const ForwardRange& r )
            {
                m_Begin  = impl::adl_begin( r );
                m_End    = impl::adl_end( r );
                return *this;
            }


            IteratorT begin() const
            {
                return m_Begin;
            }


            IteratorT end() const
            {
                return m_End;
            }


            difference_type size() const
            {
                return m_End - m_Begin;
            }


            bool empty() const
            {
                return m_Begin == m_End;
            }


        template< class IteratorT, class ForwardRange >
        inline bool operator==( const ForwardRange& l,
                                const iterator_range<IteratorT>& r )
        {
            return boost::equal( l, r );
        }


        template< class IteratorT, class ForwardRange >
        inline bool operator!=( const ForwardRange& l,
                                const iterator_range<IteratorT>& r )
        {
            return !boost::equal( l, r );
        }


        template< class IteratorT, class ForwardRange >
        inline bool operator<( const ForwardRange& l,
                               const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::less_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator<=( const ForwardRange& l,
                                const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator>( const ForwardRange& l,
                               const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator>=( const ForwardRange& l,
                                const iterator_range<IteratorT>& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }

        template< class Iterator1T, class Iterator2T >
        inline bool operator==( const iterator_range<Iterator1T>& l,
                                const iterator_range<Iterator2T>& r )
        {
            return boost::equal( l, r );
        }


        template< class IteratorT, class ForwardRange >
        inline bool operator==( const iterator_range<IteratorT>& l,
                                const ForwardRange& r )
        {
            return boost::equal( l, r );
        }



        template< class Iterator1T, class Iterator2T >
        inline bool operator!=( const iterator_range<Iterator1T>& l,
                                const iterator_range<Iterator2T>& r )
        {
            return !boost::equal( l, r );
        }


        template< class IteratorT, class ForwardRange >
        inline bool operator!=( const iterator_range<IteratorT>& l,
                                const ForwardRange& r )
        {
            return !boost::equal( l, r );
        }



        template< class Iterator1T, class Iterator2T >
        inline bool operator<( const iterator_range<Iterator1T>& l,
                               const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::less_than( l, r );
        }


        template< class IteratorT, class ForwardRange >
        inline bool operator<( const iterator_range<IteratorT>& l,
                               const ForwardRange& r )
        {
            return iterator_range_detail::less_than( l, r );
        }

        
        template< class Iterator1T, class Iterator2T >
        inline bool operator<=( const iterator_range<Iterator1T>& l,
                                const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator<=( const iterator_range<IteratorT>& l,
                                const ForwardRange& r )
        {
            return iterator_range_detail::less_or_equal_than( l, r );
        }

        
        template< class Iterator1T, class Iterator2T >
        inline bool operator>( const iterator_range<Iterator1T>& l,
                               const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator>( const iterator_range<IteratorT>& l,
                               const ForwardRange& r )
        {
            return iterator_range_detail::greater_than( l, r );
        }

        
        template< class Iterator1T, class Iterator2T >
        inline bool operator>=( const iterator_range<Iterator1T>& l,
                                const iterator_range<Iterator2T>& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }

        
        template< class IteratorT, class ForwardRange >
        inline bool operator>=( const iterator_range<IteratorT>& l,
                                const ForwardRange& r )
        {
            return iterator_range_detail::greater_or_equal_than( l, r );
        }

        template< typename IteratorT >
        inline iterator_range< IteratorT >
        make_iterator_range( IteratorT Begin, IteratorT End )
        {
            return iterator_range<IteratorT>( Begin, End );
        }

        template< typename SeqT, typename Range >
        inline SeqT copy_range( const Range& r )
        {
            return SeqT( boost::begin( r ), boost::end( r ) );
        }


    template< typename Iterator >
    inline Iterator range_begin( const std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    template< typename T, std::size_t sz >
    inline const T* range_begin( const T (&a)[sz] )
    {
        return a;
    }


    template< typename T, std::size_t sz >
    inline T* range_begin( T (&a)[sz] )
    {
        return a;
    }

    joined_range(SinglePassRange1& rng1, SinglePassRange2& rng2)
        : base_t(
            iterator_t(rng1, rng2, range_detail::join_iterator_begin_tag()),
            iterator_t(rng1, rng2, range_detail::join_iterator_end_tag())
        )
    {
    }


template<class SinglePassRange1, class SinglePassRange2>
joined_range<const SinglePassRange1, const SinglePassRange2>
join(const SinglePassRange1& r1, const SinglePassRange2& r2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return joined_range<const SinglePassRange1, const SinglePassRange2>(r1, r2);
}


template<class SinglePassRange1, class SinglePassRange2>
joined_range<SinglePassRange1, SinglePassRange2>
join(SinglePassRange1& r1, SinglePassRange2& r2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    return joined_range<SinglePassRange1, SinglePassRange2>(r1, r2);
}

        explicit mfc_ptr_array_iterator()
        { }

        template< class ArrayT_, class PtrType_ >
        mfc_ptr_array_iterator(mfc_ptr_array_iterator<ArrayT_, PtrType_> const& other) :
            super_t(other.base()), m_parr(other.m_parr)
        { }

        ref_t dereference() const
        {
            BOOST_ASSERT(0 <= this->base() && this->base() < m_parr->GetSize() && "out of range");
            return *( m_parr->GetData() + this->base() );
        }


        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_parr == other.m_parr && "iterators incompatible");
            return this->base() == other.base();
        }

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, 0);
        }


        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x, x.GetSize());
        }

        explicit mfc_map_iterator()
        { }


        explicit mfc_map_iterator(MapT const& map) :
            m_pmap(&map), m_pos(0) // end iterator
        { }

        template< class MapT_, class KeyT_, class MappedT_>
        mfc_map_iterator(mfc_map_iterator<MapT_, KeyT_, MappedT_> const& other) :
            m_pmap(other.m_pmap),
            m_pos(other.m_pos), m_posNext(other.m_posNext),
            m_key(other.m_key), m_mapped(other.m_mapped)
        { }

        ref_t dereference() const
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            return std::make_pair(m_key, m_mapped);
        }


        void increment()
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");

            if (m_posNext == 0) {
                m_pos = 0;
                return;
            }

            m_pos = m_posNext;
            m_pmap->GetNextAssoc(m_posNext, m_key, m_mapped);
        }


        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_pmap == other.m_pmap && "iterators incompatible");
            return m_pos == other.m_pos;
        }

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, x.GetStartPosition());
        }


        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x);
        }

        inline ::boost::tuples::null_type range_begin( ::boost::range_detail::void_& )
        { return ::boost::tuples::null_type(); }


        inline ::boost::tuples::null_type range_end( ::boost::range_detail::void_& )
        { return ::boost::tuples::null_type(); }


            static type begin( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            {
                return ::boost::tuples::make_tuple( ::boost::begin(r1),
                                                    ::boost::begin(r2),
                                                    ::boost::begin(r3),
                                                    ::boost::begin(r4),
                                                    ::boost::begin(r5),
                                                    ::boost::begin(r6) );
            }


            static type end( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            {
                return ::boost::tuples::make_tuple( ::boost::end(r1),
                                                    ::boost::end(r2),
                                                    ::boost::end(r3),
                                                    ::boost::end(r4),
                                                    ::boost::end(r5),
                                                    ::boost::end(r6) );
            }

            zip_rng( R1& r1, R2& r2, R3& r3, R4& r4, R5& r5, R6& r6 )
            : base_t( zip_iter_t( generator_t::begin(r1,r2,r3,r4,r5,r6) ),
                      zip_iter_t( generator_t::end(r1,r2,r3,r4,r5,r6) ) )
            {
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r2));
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r3));
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r4));
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r5));
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r6));
            }


            template< class Zip, class Rng >
            zip_rng( Zip& z, Rng& r )
            : base_t( zip_iter_t( generator_t::begin( z, r ) ),
                      zip_iter_t( generator_t::end( z, r ) ) )
            {

                // @todo: tuple::begin( should be overloaded for this situation
            }

            zip_range( Rng1& r1, Rng2& r2 )
            : base_t( zip_iter_t( ::boost::tuples::make_tuple(::boost::begin(r1),
                                                              ::boost::begin(r2)) ),
                      zip_iter_t( ::boost::tuples::make_tuple(::boost::end(r1),
                                                              ::boost::end(r2)) ) )
            {
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r2));
            }

            zip_range3( Rng1& r1, Rng2& r2, Rng3& r3 )
            : base_t( zip_iter_t( ::boost::tuples::make_tuple(::boost::begin(r1),
                                                              ::boost::begin(r2),
                                                              ::boost::begin(r3)) ),
                      zip_iter_t( ::boost::tuples::make_tuple(::boost::end(r1),
                                                              ::boost::end(r2),
                                                              ::boost::end(r3)) )
                    )
            {
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r2));
                BOOST_ASSERT(::boost::distance(r1) <= ::boost::distance(r3));
            }


        template< class Rng >
        inline zip_rng<Rng>
        operator&( combine_tag, Rng& r )
        {
            return zip_rng<Rng>(r);
        }


    template< class Rng1, class Rng2 >
    inline ::boost::range_detail::zip_range<Rng1, Rng2> combine( Rng1& r1, Rng2& r2 )
    {
        return ::boost::range_detail::zip_range<Rng1, Rng2>(r1, r2);
    }


    template< class Rng1, class Rng2 >
    inline ::boost::range_detail::zip_range<const Rng1, Rng2> combine( const Rng1& r1, Rng2& r2 )
    {
        return ::boost::range_detail::zip_range<const Rng1, Rng2>(r1, r2);
    }


    template< class Rng1, class Rng2 >
    inline ::boost::range_detail::zip_range<Rng1, const Rng2> combine( Rng1& r1, const Rng2& r2 )
    {
        return ::boost::range_detail::zip_range<Rng1, const Rng2>(r1, r2);
    }


    template< class Rng1, class Rng2 >
    inline ::boost::range_detail::zip_range<const Rng1, const Rng2> combine( const Rng1& r1, const Rng2& r2 )
    {
        return ::boost::range_detail::zip_range<const Rng1, const Rng2>(r1, r2);
    }


        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.operator BSTR();
        }


        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.Length();
        }

            any_range()
            {
            }


            any_range(const any_range& other)
                : base_type(other)
            {
            }


            template<class WrappedRange>
            any_range(WrappedRange& wrapped_range)
            : base_type(boost::begin(wrapped_range),
                        boost::end(wrapped_range))
            {
            }


            template<class WrappedRange>
            any_range(const WrappedRange& wrapped_range)
            : base_type(boost::begin(wrapped_range),
                        boost::end(wrapped_range))
            {
            }


            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
            >
            any_range(const any_range<
                                OtherValue
                              , OtherTraversal
                              , OtherReference
                              , OtherDifference
                              , Buffer
                            >& other)
            : base_type(boost::begin(other), boost::end(other))
            {
            }


            template<class Iterator>
            any_range(Iterator first, Iterator last)
                : base_type(first, last)
            {
            }

    template< class SinglePassRange, class Value >
    inline Value accumulate( const SinglePassRange& rng, Value init )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::accumulate( boost::begin(rng), boost::end(rng), init );
    }


    template< class SinglePassRange, class Value, class BinaryOperation >
    inline Value accumulate( const SinglePassRange& rng, Value init, BinaryOperation op )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::accumulate( boost::begin(rng), boost::end(rng), init, op );
    }



    template< class SinglePassRange1, class SinglePassRange2, class Value >
    inline Value inner_product( const SinglePassRange1& rng1, const SinglePassRange2& rng2, Value init )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
        BOOST_ASSERT( boost::distance(rng2) >= boost::distance(rng1) );
        return std::inner_product( boost::begin(rng1), boost::end(rng1),
            boost::begin(rng2), init );
    }


    template< class SinglePassRange1,
              class SinglePassRange2,
              class Value,
              class BinaryOperation1, class BinaryOperation2 >
    inline Value inner_product( const SinglePassRange1& rng1, const SinglePassRange2& rng2,
                                Value init,
                                BinaryOperation1 op1, BinaryOperation2 op2 )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
        BOOST_ASSERT( boost::distance(rng2) >= boost::distance(rng1) );

        return std::inner_product( boost::begin(rng1), boost::end(rng1),
                                   boost::begin(rng2), init, op1, op2 );
    }


    template< class SinglePassRange, class OutputIterator >
    inline OutputIterator partial_sum ( const SinglePassRange& rng,
                                        OutputIterator result )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::partial_sum( boost::begin(rng), boost::end(rng), result );
    }


    template< class SinglePassRange, class OutputIterator, class BinaryOperation >
    inline OutputIterator partial_sum ( const SinglePassRange& rng, OutputIterator result,
                                        BinaryOperation op )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::partial_sum( boost::begin(rng), boost::end(rng), result, op );
    }


    template< class SinglePassRange, class OutputIterator >
    inline OutputIterator adjacent_difference ( const SinglePassRange& rng,
                                                OutputIterator result )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::adjacent_difference( boost::begin(rng), boost::end(rng),
                                         result );
    }


    template< class SinglePassRange, class OutputIterator, class BinaryOperation >
    inline OutputIterator adjacent_difference ( const SinglePassRange& rng,
                                                OutputIterator result,
                                                BinaryOperation op )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
        return std::adjacent_difference( boost::begin(rng), boost::end(rng),
                                         result, op );
    }


            integer_iterator() : m_value() {}

            explicit integer_iterator(value_type x) : m_value(x) {}

            void increment()
            {
                ++m_value;
            }


            void decrement()
            {
                --m_value;
            }


            void advance(difference_type offset)
            {
                m_value += offset;
            }


            difference_type distance_to(const integer_iterator& other) const
            {
                return other.m_value - m_value;
            }


            bool equal(const integer_iterator& other) const
            {
                return m_value == other.m_value;
            }


            reference dereference() const
            {
                return m_value;
            }


            integer_iterator_with_step(value_type first, difference_type step, value_type step_size)
                : m_first(first)
                , m_step(step)
                , m_step_size(step_size)
            {
            }

            void increment()
            {
                ++m_step;
            }


            void decrement()
            {
                --m_step;
            }


            void advance(difference_type offset)
            {
                m_step += offset;
            }


            difference_type distance_to(const integer_iterator_with_step& other) const
            {
                return other.m_step - m_step;
            }


            bool equal(const integer_iterator_with_step& other) const
            {
                return m_step == other.m_step;
            }


            reference dereference() const
            {
                return m_first + (m_step * m_step_size);
            }

        integer_range(Integer first, Integer last)
            : base_t(iterator_t(first), iterator_t(last))
        {
        }

        template<typename Iterator>
        strided_integer_range(Iterator first, Iterator last)
            : base_t(first, last)
        {
        }


    template<typename Integer>
    integer_range<Integer>
    irange(Integer first, Integer last)
    {
        BOOST_ASSERT( first <= last );
        return integer_range<Integer>(first, last);
    }


    template<typename Integer, typename StepSize>
    strided_integer_range<Integer>
        irange(Integer first, Integer last, StepSize step_size)
    {
        BOOST_ASSERT( step_size != 0 );
        BOOST_ASSERT( (step_size > 0) ? (last >= first) : (last <= first) );
        
        typedef typename range_detail::integer_iterator_with_step<Integer> iterator_t;

        const std::ptrdiff_t sz = static_cast<std::ptrdiff_t>(step_size >= 0 ? step_size : -step_size);
        const Integer l = step_size >= 0 ? last : first;
        const Integer f = step_size >= 0 ? first : last;
        const std::ptrdiff_t num_steps = (l - f) / sz + ((l - f) % sz ? 1 : 0);
        BOOST_ASSERT(num_steps >= 0);
       
        return strided_integer_range<Integer>(
            iterator_t(first, 0, step_size),
            iterator_t(first, num_steps, step_size));
    }

        sub_range() : base() 
        { }


        template< class ForwardRange2 >
        sub_range( ForwardRange2& r ) : 
            
#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 800 )
            base( impl::adl_begin( r ), impl::adl_end( r ) )
#else
            base( r )
#endif        
        { }

        
        template< class ForwardRange2 >
        sub_range( const ForwardRange2& r ) : 

#if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 800 )
            base( impl::adl_begin( r ), impl::adl_end( r ) )
#else
            base( r )
#endif                
        { }


        template< class Iter >
        sub_range( Iter first, Iter last ) :
            base( first, last )
        { }

        
        template< class ForwardRange2 >
        sub_range& operator=( ForwardRange2& r )
        {
            base::operator=( r );
            return *this;
        }


        template< class ForwardRange2 >
        sub_range& operator=( const ForwardRange2& r )
        {
            base::operator=( r );
            return *this;
        }
   

        sub_range& operator=( const sub_range& r )
        {
            base::operator=( static_cast<const base&>(r) );
            return *this;            
        }

        
        iterator        begin()          { return base::begin(); }

        iterator        end()            { return base::end();   }

        difference_type size() const     { return base::size();  }

        reference front()
        {
            return base::front();
        }


        reference back()
        {
            return base::back();
        }


        reference operator[]( difference_type sz )
        {
            return base::operator[](sz);
        }


    template< class ForwardRange, class ForwardRange2 >
    inline bool operator==( const sub_range<ForwardRange>& l,
                            const sub_range<ForwardRange2>& r )
    {
        return boost::equal( l, r );
    }


    template< class ForwardRange, class ForwardRange2 >
    inline bool operator!=( const sub_range<ForwardRange>& l,
                            const sub_range<ForwardRange2>& r )
    {
        return !boost::equal( l, r );
    }


    template< class ForwardRange, class ForwardRange2 >
    inline bool operator<( const sub_range<ForwardRange>& l,
                           const sub_range<ForwardRange2>& r )
    {
        return iterator_range_detail::less_than( l, r );
    }
 

    template< class T >
    inline bool empty( const T& r )
    {
        return boost::begin( r ) == boost::end( r );
    }


            explicit postfix_increment_proxy(any_iterator_type const& x)
                : stored_value(*x)
            {}


            value_type&
            operator*() const
            {
                return this->stored_value;
            }


            explicit writable_postfix_increment_proxy(any_iterator_type const& x)
              : stored_value(*x)
              , stored_iterator(x)
            {}

            writable_postfix_increment_proxy const&
            operator*() const
            {
                return *this;
            }

            operator value_type&() const
            {
                return stored_value;
            }

            template <class T>
            T const& operator=(T const& x) const
            {
                *this->stored_iterator = x;
                return x;
            }

            template <class T>
            T& operator=(T& x) const
            {
                *this->stored_iterator = x;
                return x;
            }

            operator any_iterator_type const&() const
            {
                return stored_iterator;
            }

            any_iterator()
                : m_impl(0) {}

            any_iterator(const any_iterator& other)
                : base_type(other)
                , m_impl(other.m_impl
                            ? other.m_impl->clone(m_buffer)
                            : 0)
            {
            }

            any_iterator& operator=(const any_iterator& other)
            {
                if (this != &other)
                {
                    if (m_impl)
                        m_impl->~abstract_base_type();
                    m_buffer.deallocate();
                    m_impl = 0;
                    if (other.m_impl)
                        m_impl = other.m_impl->clone(m_buffer);
                }
                return *this;
            }


            any_iterator clone() const
            {
                any_iterator result;
                if (m_impl)
                    result.m_impl = m_impl->clone(result.m_buffer);
                return result;
            }

            clone_const_ref() const
            {
                typedef any_iterator<
                    Value
                  , Traversal
                  , typename abstract_base_type::const_reference
                  , Difference
                  , Buffer
                > result_type;

                result_type result;

                if (m_impl)
                    result.m_impl = m_impl->clone_const_ref(result.m_buffer);

                return result;
            }


            ~any_iterator()
            {
                // manually run the destructor, the deallocation is automatically
                // handled by the any_iterator_small_buffer base class.
                if (m_impl)
                    m_impl->~abstract_base_type();
            }


            Reference dereference() const
            {
                BOOST_ASSERT( m_impl );
                return m_impl->dereference();
            }


            bool equal(const any_iterator& other) const
            {
                return (m_impl == other.m_impl)
                    || (m_impl && other.m_impl && m_impl->equal(*other.m_impl));
            }


            void increment()
            {
                BOOST_ASSERT( m_impl );
                m_impl->increment();
            }


            void decrement()
            {
                BOOST_ASSERT( m_impl );
                m_impl->decrement();
            }


            Difference distance_to(const any_iterator& other) const
            {
                return m_impl && other.m_impl
                    ? m_impl->distance_to(*other.m_impl)
                    : 0;
            }


            void advance(Difference offset)
            {
                BOOST_ASSERT( m_impl );
                m_impl->advance(offset);
            }


            any_iterator& swap(any_iterator& other)
            {
                BOOST_ASSERT( this != &other );
                // grab a temporary copy of the other iterator
                any_iterator tmp(other);

                // deallocate the other iterator, taking care to obey the
                // class-invariants in-case of exceptions later
                if (other.m_impl)
                {
                    other.m_impl->~abstract_base_type();
                    other.m_buffer.deallocate();
                    other.m_impl = 0;
                }

                // If this is a non-null iterator then we need to put
                // a clone of this iterators implementation into the other
                // iterator.
                // We can't just swap because of the small buffer optimization.
                if (m_impl)
                {
                    other.m_impl = m_impl->clone(other.m_buffer);
                    m_impl->~abstract_base_type();
                    m_buffer.deallocate();
                    m_impl = 0;
                }

                // assign to this instance a clone of the temporarily held
                // tmp which represents the input other parameter at the
                // start of execution of this function.
                if (tmp.m_impl)
                    m_impl = tmp.m_impl->clone(m_buffer);

                return *this;
            }

    static unspecified_bool_type to_unspecified_bool(const bool x, DataMemberPtr p)
    {
        return x ? p : 0;
    }

        template <typename T>
        inline void boost_range_silence_warning( const T& ) { }


        inline const char* str_end( const char* s, const char* )
        {
            return s + strlen( s );
        }

        inline const wchar_t* str_end( const wchar_t* s, const wchar_t* )
        {
            return s + wcslen( s );
        }


        template< class Char >
        inline Char* str_end( Char* s )
        {
            return const_cast<Char*>( str_end( s, s ) );
        }


        template< class T, std::size_t sz >
        inline T* array_end( T BOOST_RANGE_ARRAY_REF()[sz] )
        {
            return boost_range_array + sz;
        }


        template< class Char >
        inline std::size_t str_size( const Char* const& s )
        {
            return str_end( s ) - s;
        }


        template< class T, std::size_t sz >
        inline std::size_t array_size( T BOOST_RANGE_ARRAY_REF()[sz] )
        {
            boost_range_silence_warning( boost_range_array );
            return sz;
        }

    join_iterator_link(Iterator1 last1, Iterator2 first2)
        :    last1(last1)
        ,    first2(first2)
    {
    }


    join_iterator_union() {}

    join_iterator_union(unsigned int /*selected*/, const iterator1_t& it1, const iterator2_t& it2) : m_it1(it1), m_it2(it2) {}


    iterator1_t& it1() { return m_it1; }

    const iterator1_t& it1() const { return m_it1; }


    iterator2_t& it2() { return m_it2; }

    const iterator2_t& it2() const { return m_it2; }


    Reference dereference(unsigned int selected) const
    {
        return selected ? *m_it2 : *m_it1;
    }


    bool equal(const join_iterator_union& other, unsigned int selected) const
    {
        return selected
            ? m_it2 == other.m_it2
            : m_it1 == other.m_it1;
    }


    join_iterator_union() {}


    join_iterator_union(unsigned int selected, const iterator1_t& it1, const iterator2_t& it2)
        : m_it(selected ? it2 : it1)
    {
    }


    iterator1_t& it1() { return m_it; }

    const iterator1_t& it1() const { return m_it; }


    iterator2_t& it2() { return m_it; }

    const iterator2_t& it2() const { return m_it; }


    Reference dereference(unsigned int) const
    {
        return *m_it;
    }


    bool equal(const join_iterator_union& other, unsigned int selected) const
    {
        return m_it == other.m_it;
    }

                template< typename C >
                static size_type size( const C& c )
                {
                    return c.size();
                }


                template< typename C >
                static bool empty( const C& c )
                {
                    return c.empty();
                }


                template< typename C >
                static iterator begin( C& c )
                {
                    return c.begin();
                }


                template< typename C >
                static iterator end( C& c )
                {
                    return c.end();
                }

                template< typename P >
                static size_type size( const P& p )
                {
                    difference_type diff = std::distance( p.first, p.second );
                    if ( diff < 0 ) 
                        return 0;
                    else
                        return diff;
                }


                template< typename P >
                static bool empty( const P& p )
                {
                    return p.first==p.second;
                }


                template< typename P > 
                static const_iterator begin( const P& p )
                {
                    return p.first;
                }


                template< typename P >
                static const_iterator end( const P& p )
                {
                    return p.second;
                }


                    template< typename A >
                    static size_type length( const A& )
                    {
                        return array_size;
                    }


                    template< typename A >
                    static bool empty( const A& )
                    {
                        return array_size==0;
                    }


                    template< typename A >
                    static size_type length( const A& a )
                    {
                        if ( a==0 ) 
                            return 0;
                        else
                            return std::char_traits<char>::length(a);
                    }

                    
                    template< typename A >
                    static bool empty( const A& a )
                    {
                        return a==0 || a[0]==0;
                    }


                    template< typename A >
                    static size_type length( const A& a )
                    {
                        if ( a==0 ) 
                            return 0;
                        else
                            return std::char_traits<wchar_t>::length(a);
                    }


                    template< typename A >
                    static bool empty( const A& a )
                    {
                        return a==0 || a[0]==0;
                    }

                template< typename A >
                static size_type size( const A& a )
                {
                    return array_length_type::length(a);
                }


                template< typename A >
                static bool empty( const A& a )
                {
                    return array_length_type::empty(a);
                }


                template< typename A >
                static iterator begin( A& a )
                {
                    return a;
                }


                template< typename A >
                static iterator end( A& a )
                {
                    return a+array_length_type::length(a);
                }

                template< typename P >
                static size_type size( const P& p )
                {
                    if ( p==0 ) 
                        return 0;
                    else
                        return char_traits::length(p);
                }


                template< typename P >
                static bool empty( const P& p )
                {
                    return p==0 || p[0]==0;
                }


                template< typename P >
                static iterator begin( P& p )
                {
                    return p;
                }


                template< typename P >
                static const_iterator begin( const P& p )
                {
                    return p;
                }


                template< typename P >
                static iterator end( P& p )
                {
                    if ( p==0 )
                        return p;
                    else
                        return p+char_traits::length(p);
                }


                template< typename P >
                static const_iterator end( const P& p )
                {
                    if ( p==0 )
                        return p;
                    else
                        return p+char_traits::length(p);
                }

        any_iterator_buffer()
            : m_ptr()
        {
        }


        ~any_iterator_buffer()
        {
            delete [] m_ptr;
        }


        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( !m_ptr );
            if (bytes <= StackBufferSize)
                return m_buffer.data();

            m_ptr = new char[bytes];
            return m_ptr;
        }


        void deallocate()
        {
            delete [] m_ptr;
            m_ptr = 0;
        }

        any_iterator_heap_only_buffer()
            : m_ptr()
        {
        }


        ~any_iterator_heap_only_buffer()
        {
            delete [] m_ptr;
        }


        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( !m_ptr );
            m_ptr = new char[bytes];
            return m_ptr;
        }


        void deallocate()
        {
            delete [] m_ptr;
            m_ptr = 0;
        }

        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( bytes <= m_buffer.size() );
            return m_buffer.data();
        }


        void deallocate()
        {
        }

        size( const C& c )
        {
            return collection_traits<C>::function_type::size( c ); 
        }

        template< typename C >
        inline bool empty( const C& c )
        {
            return collection_traits<C>::function_type::empty( c );
        }

        begin( C& c )
        {
            return collection_traits<C>::function_type::begin( c ); 
        }

        end( C& c )
        {
            return collection_traits<C>::function_type::end( c );
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }


        static type pack(type found, SinglePassRange&)
        {
            return found;
        }


        static type pack(type found, SinglePassRange& rng)
        {
            return found == boost::end(rng)
                ? found
                : boost::next(found);
        }


        static type pack(type found, BidirectionalRange& rng)
        {
            return found == boost::begin(rng)
                ? found
                : boost::prior(found);
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), found);
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( boost::begin(rng), 
                         found == boost::end(rng) ? found : boost::next(found) );
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( boost::begin(rng),
                         found == boost::begin(rng) ? found : boost::prior(found) );
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(found, boost::end(rng));
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type( found == boost::end(rng) ? found : boost::next(found),
                         boost::end(rng) );
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type found,
                         BidirectionalRange& rng)
        {
            return type( found == boost::begin(rng) ? found : boost::prior(found),
                         boost::end(rng) );
        }


        static type pack(BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type found,
                         SinglePassRange& rng)
        {
            return type(boost::begin(rng), boost::end(rng));
        }


            virtual ~any_incrementable_iterator_interface() {}

            template<typename T> void same_type(T,T) {}



    template< class T > inline
    typename mutable_iterator_of<T>::type
    begin_of(T& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template begin<typename mutable_iterator_of<T>::type>(x);
    }



    template< class T > inline
    typename const_iterator_of<T>::type
    begin_of(T const& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template begin<typename const_iterator_of<T>::type>(x);
    }



    template< class T > inline
    typename mutable_iterator_of<T>::type
    end_of(T& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template end<typename mutable_iterator_of<T>::type>(x);
    }



    template< class T > inline
    typename const_iterator_of<T>::type
    end_of(T const& x)
    {
        typedef typename customization_of<T>::type cust_t;
        return cust_t().template end<typename const_iterator_of<T>::type>(x);
    }


    template< class T > inline
    typename size_type_of<T>::type
    size_of(T const& x)
    {
        return std::distance(boost::begin(x), boost::end(x));
    }

        explicit list_iterator()
        { }


        explicit list_iterator(ListT& lst, POSITION pos) :
            m_plst(boost::addressof(lst)), m_pos(pos)
        { }

        template< class ListT_, class Value_, class Reference_, class Traversal_>
        list_iterator(list_iterator<ListT_, Value_, Reference_, Traversal_> const& other) :
            m_plst(other.m_plst), m_pos(other.m_pos)
        { }

        ref_t dereference() const
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            return m_plst->GetAt(m_pos);
        }

        void increment()
        {
            BOOST_ASSERT(m_pos != 0 && "out of range");
            m_plst->GetNext(m_pos);
        }


        void decrement()
        {
            if (m_pos == 0) {
                m_pos = m_plst->GetTailPosition();
                return;
            }

            m_plst->GetPrev(m_pos);
        }


        bool equal(self_t const& other) const
        {
            BOOST_ASSERT(m_plst == other.m_plst && "iterators incompatible");
            return m_pos == other.m_pos;
        }

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.GetData();
        }


        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return begin<Iterator>(x) + x.GetSize();
        }

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return Iterator(x, x.GetHeadPosition());
        }


        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return Iterator(x, POSITION(0));
        }

    
        
    template< typename C >
    inline bool 
    empty( const C& c )
    {
        return range_detail::range_empty<  BOOST_RANGE_DEDUCED_TYPENAME range_detail::range<C>::type >::fun( c );
    }

            static char* fun( char* s )
            {
                return s;
            }

            template< typename T, std::size_t sz >
            static T* fun( T BOOST_RANGE_ARRAY_REF()[sz] )
            {
                return boost::range_detail::array_end( boost_range_array );
            }


            any_incrementable_iterator_wrapper()
                : m_it()
            {}


            explicit any_incrementable_iterator_wrapper(wrapped_type it)
                : m_it(it)
            {}

            virtual any_incrementable_iterator_wrapper* clone(
                typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_incrementable_iterator_wrapper(m_it);
            }


            virtual any_incrementable_iterator_wrapper<
                        WrappedIterator
                      , typename any_incrementable_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                        typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_incrementable_iterator_wrapper<
                            WrappedIterator
                          , typename any_incrementable_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual any_incrementable_iterator_wrapper<
                        WrappedIterator
                      , typename any_incrementable_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                        typename any_incrementable_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_incrementable_iterator_wrapper<
                            WrappedIterator
                          , typename any_incrementable_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual void increment()
            {
                ++m_it;
            }


            any_single_pass_iterator_wrapper()
                : m_it()
            {}


            explicit any_single_pass_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {}

            virtual any_single_pass_iterator_wrapper* clone(
                typename any_single_pass_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                            any_single_pass_iterator_wrapper(m_it);
            }


            virtual any_single_pass_iterator_wrapper<
                WrappedIterator
              , typename any_single_pass_iterator_wrapper::const_reference
              , Buffer
            >* clone_const_ref(
                   typename any_single_pass_iterator_wrapper::buffer_type& buffer
                   ) const
            {
                typedef any_single_pass_iterator_wrapper<
                            WrappedIterator
                          , typename any_single_pass_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual any_single_pass_iterator_wrapper<
                WrappedIterator
              , typename any_single_pass_iterator_wrapper::reference_as_value_type
              , Buffer
            >* clone_reference_as_value(
                typename any_single_pass_iterator_wrapper::buffer_type& buffer
                ) const
            {
                typedef any_single_pass_iterator_wrapper<
                            WrappedIterator
                          , typename any_single_pass_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual void increment()
            {
                ++m_it;
            }


            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == boost::polymorphic_downcast<const any_single_pass_iterator_wrapper*>(&other)->m_it;
            }


            virtual Reference dereference() const
            {
                return *m_it;
            }

            any_forward_iterator_wrapper()
                : m_it()
            {}


            explicit any_forward_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {}

            virtual any_forward_iterator_wrapper* clone(
                typename any_forward_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_forward_iterator_wrapper(m_it);
            }


            virtual any_forward_iterator_wrapper<
                        WrappedIterator
                      , typename any_forward_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                            typename any_forward_iterator_wrapper::buffer_type& buffer
                        ) const
            {
                typedef any_forward_iterator_wrapper<
                            WrappedIterator
                          , typename any_forward_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual any_forward_iterator_wrapper<
                        WrappedIterator
                      , typename any_forward_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                            typename any_forward_iterator_wrapper::buffer_type& buffer
                    ) const
            {
                typedef any_forward_iterator_wrapper<
                            WrappedIterator
                          , typename any_forward_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual void increment()
            {
                ++m_it;
            }


            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == boost::polymorphic_downcast<const any_forward_iterator_wrapper*>(&other)->m_it;
            }


            virtual Reference dereference() const
            {
                return *m_it;
            }

            any_bidirectional_iterator_wrapper()
                : m_it()
            {
            }


            explicit any_bidirectional_iterator_wrapper(const WrappedIterator& it)
                : m_it(it)
            {
            }


            virtual any_bidirectional_iterator_wrapper* clone(
                typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                            any_bidirectional_iterator_wrapper(*this);
            }


            virtual any_bidirectional_iterator_wrapper<
                        WrappedIterator
                      , typename any_bidirectional_iterator_wrapper::const_reference
                      , Buffer
                    >* clone_const_ref(
                           typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                       ) const
            {
                typedef any_bidirectional_iterator_wrapper<
                            WrappedIterator
                          , typename any_bidirectional_iterator_wrapper::const_reference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual any_bidirectional_iterator_wrapper<
                        WrappedIterator
                      , typename any_bidirectional_iterator_wrapper::reference_as_value_type
                      , Buffer
                    >* clone_reference_as_value(
                           typename any_bidirectional_iterator_wrapper::buffer_type& buffer
                       ) const
            {
                typedef any_bidirectional_iterator_wrapper<
                            WrappedIterator
                          , typename any_bidirectional_iterator_wrapper::reference_as_value_type
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual void increment()
            {
                ++m_it;
            }


            virtual void decrement()
            {
                --m_it;
            }


            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == boost::polymorphic_downcast<const any_bidirectional_iterator_wrapper*>(&other)->m_it;
            }


            virtual Reference dereference() const
            {
                return *m_it;
            }


            any_random_access_iterator_wrapper()
                : m_it()
            {
            }


            explicit any_random_access_iterator_wrapper(const WrappedIterator& other)
                : m_it(other)
            {
            }


            virtual any_random_access_iterator_wrapper* clone(
                    typename any_random_access_iterator_wrapper::buffer_type& buffer
                ) const
            {
                return new (buffer.allocate(sizeof(*this)))
                                any_random_access_iterator_wrapper(*this);
            }


            virtual any_random_access_iterator_wrapper<
                        WrappedIterator
                      , typename any_random_access_iterator_wrapper::const_reference
                      , Difference
                      , Buffer
                    >* clone_const_ref(
                           typename any_random_access_iterator_wrapper::buffer_type& buffer
                           ) const
            {
                typedef any_random_access_iterator_wrapper<
                            WrappedIterator
                          , typename any_random_access_iterator_wrapper::const_reference
                          , Difference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual any_random_access_iterator_wrapper<
                        WrappedIterator
                      , typename any_random_access_iterator_wrapper::reference_as_value_type
                      , Difference
                      , Buffer
                    >* clone_reference_as_value(
                           typename any_random_access_iterator_wrapper::buffer_type& buffer
                           ) const
            {
                typedef any_random_access_iterator_wrapper<
                            WrappedIterator
                          , typename any_random_access_iterator_wrapper::reference_as_value_type
                          , Difference
                          , Buffer
                        > result_type;

                return new (buffer.allocate(sizeof(result_type)))
                            result_type(m_it);
            }


            virtual void increment()
            {
                ++m_it;
            }


            virtual bool equal(const any_single_pass_iterator_interface<Reference, Buffer>& other) const
            {
                return m_it == boost::polymorphic_downcast<const any_random_access_iterator_wrapper*>(&other)->m_it;
            }


            virtual void decrement()
            {
                --m_it;
            }


            virtual void advance(Difference offset)
            {
                m_it += offset;
            }


            virtual Reference dereference() const
            {
                return *m_it;
            }


            virtual Difference distance_to(const any_random_access_iterator_interface<Reference, Difference, Buffer>& other) const
            {
                return boost::polymorphic_downcast<const any_random_access_iterator_wrapper*>(&other)->m_it - m_it;
            }

            sliced(std::size_t t_, std::size_t u_)
                : t(t_), u(u_) {}

            template<typename Rng, typename T, typename U>
            sliced_range(Rng& rng, T t, U u)
                : base_t(boost::make_iterator_range(rng, t, u - boost::size(rng)))
            {
            }


        template< class RandomAccessRange >
        inline sliced_range<RandomAccessRange>
        slice( RandomAccessRange& rng, std::size_t t, std::size_t u )
        {
            BOOST_ASSERT( t <= u && "error in slice indices" );
            BOOST_ASSERT( static_cast<std::size_t>(boost::size(rng)) >= u &&
                          "second slice index out of bounds" );

            return sliced_range<RandomAccessRange>(rng, t, u);
        }


            replace_value_if(const Pred& pred, const Value& to)
                :   m_pred(pred), m_to(to)
            {
            }


            const Value& operator()(const Value& x) const
            {
                return m_pred(x) ? m_to : x;
            }


            replaced_if_range( R& r, const Pred& pred, value_type to )
                : base_t( make_transform_iterator( boost::begin(r), Fn(pred, to) ),
                          make_transform_iterator( boost::end(r), Fn(pred, to) ) )
            { }

            replace_if_holder( const Pred& pred, const T& to )
                : m_pred(pred), m_to(to)
            { }


            const Pred& pred() const { return m_pred; }

            const T& to() const { return m_to; }


        template< class Pred, class InputRng >
        inline replaced_if_range<Pred, InputRng>
        operator|( InputRng& r,
                   const replace_if_holder<Pred, BOOST_DEDUCED_TYPENAME range_value<InputRng>::type>& f )
        {
            return replaced_if_range<Pred, InputRng>(r, f.pred(), f.to());
        }

        
        template<class Pred, class InputRange>
        inline replaced_if_range<Pred, InputRange>
        replace_if(InputRange& rng, Pred pred,
                   BOOST_DEDUCED_TYPENAME range_value<InputRange>::type to)
        {
            return range_detail::replaced_if_range<Pred, InputRange>(rng, pred, to);
        }


            explicit reversed_range( R& r ) 
                : base( iterator(boost::end(r)), iterator(boost::begin(r)) )
            { }

        
        template< class BidirectionalRng >
        inline reversed_range<BidirectionalRng> 
        operator|( BidirectionalRng& r, reverse_forwarder )
        {
            return reversed_range<BidirectionalRng>( r );   
        }

    
        template< class BidirectionalRng >
        inline reversed_range<const BidirectionalRng> 
        operator|( const BidirectionalRng& r, reverse_forwarder )
        {
            return reversed_range<const BidirectionalRng>( r );   
        }

        
        template<class BidirectionalRange>
        inline reversed_range<BidirectionalRange>
        reverse(BidirectionalRange& rng)
        {
            return reversed_range<BidirectionalRange>(rng);
        }

        
        template<class BidirectionalRange>
        inline reversed_range<const BidirectionalRange>
        reverse(const BidirectionalRange& rng)
        {
            return reversed_range<const BidirectionalRange>(rng);
        }

            filtered_range( P p, R& r )
            : base( make_filter_iterator( p, boost::begin(r), boost::end(r) ),
                    make_filter_iterator( p, boost::end(r), boost::end(r) ) )
            { }

            filter_holder( T r ) : holder<T>(r)
            { }


        template< class InputRng, class Predicate >
        inline filtered_range<Predicate, InputRng>
        operator|( InputRng& r,
                   const filter_holder<Predicate>& f )
        {
            return filtered_range<Predicate, InputRng>( f.val, r );
        }


        template< class InputRng, class Predicate >
        inline filtered_range<Predicate, const InputRng>
        operator|( const InputRng& r,
                   const filter_holder<Predicate>& f )
        {
            return filtered_range<Predicate, const InputRng>( f.val, r );
        }


        template<class InputRange, class Predicate>
        inline filtered_range<Predicate, InputRange>
        filter(InputRange& rng, Predicate filter_pred)
        {
            return range_detail::filtered_range<Predicate, InputRange>( filter_pred, rng );
        }


        template<class InputRange, class Predicate>
        inline filtered_range<Predicate, const InputRange>
        filter(const InputRange& rng, Predicate filter_pred)
        {
            return range_detail::filtered_range<Predicate, const InputRange>( filter_pred, rng );
        }


            template< class T >
            bool operator()( const T& l, const T& r ) const
            {
                return !(l == r);
            }

            explicit uniqued_range(ForwardRng& rng)
                : base(unique_not_equal_to(), rng)
            {
            }


        template< class ForwardRng >
        inline uniqued_range<ForwardRng>
        operator|( ForwardRng& r,
                   unique_forwarder )
        {
            return uniqued_range<ForwardRng>(r);
        }


        template< class ForwardRng >
        inline uniqued_range<const ForwardRng>
        operator|( const ForwardRng& r,
                   unique_forwarder )
        {
            return uniqued_range<const ForwardRng>(r);
        }


        template<class ForwardRange>
        inline uniqued_range<ForwardRange>
        unique(ForwardRange& rng)
        {
            return uniqued_range<ForwardRange>(rng);
        }


        template<class ForwardRange>
        inline uniqued_range<const ForwardRange>
        unique(const ForwardRange& rng)
        {
            return uniqued_range<const ForwardRange>(rng);
        }

        operator|(const SinglePassRange& rng,
                  type_erased<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , Buffer
                    >)
        {
            typedef typename any_range_type_generator<
                const SinglePassRange
              , Value
              , Traversal
              , Reference
              , Difference
              , Buffer
            >::type range_type;
            return range_type(boost::begin(rng), boost::end(rng));
        }

        type_erase(SinglePassRange& rng
                 , type_erased<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , Buffer
                    > = type_erased<>()
                )
        {
            typedef typename any_range_type_generator<
                SinglePassRange
              , Value
              , Traversal
              , Reference
              , Difference
              , Buffer
            >::type range_type;

            return range_type(boost::begin(rng), boost::end(rng));
        }

            holder( T t ) : val(t)
            { }

            holder2( T t, T u ) : val1(t), val2(u)
            { }

            template< class T >
            Holder<T> operator()( T t ) const
            {
                return Holder<T>(t);
            }

            template< class T >
            Holder<T> operator()( T t, T u ) const
            {
                return Holder<T>(t,u);
            }

            template< class T, class U >
            Holder<T, U> operator()( T t, U u ) const
            {
                return Holder<T, U>(t, u);
            }


            result_type operator()( argument_type r ) const
            {
                return r.first;
            }


            result_type operator()( argument_type r ) const
            {
                return r.second;
            }


            result_type operator()( argument_type r ) const
            {
                return r.second;
            }


            select_first_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }


            select_second_mutable_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }


            select_second_const_range(transform_fn_type fn, source_range_type& rng)
                : base(fn, rng)
            {
            }


        template< class StdPairRng >
        inline select_first_range<StdPairRng>
        operator|( const StdPairRng& r, map_keys_forwarder )
        {
            return operator|( r,
                boost::adaptors::transformed( select_first<StdPairRng>() ) );
        }


        template< class StdPairRng >
        inline select_second_mutable_range<StdPairRng>
        operator|( StdPairRng& r, map_values_forwarder )
        {
            return operator|( r,
                boost::adaptors::transformed( select_second_mutable<StdPairRng>() ) );
        }


        template< class StdPairRng >
        inline select_second_const_range<StdPairRng>
        operator|( const StdPairRng& r, map_values_forwarder )
        {
            return operator|( r,
                boost::adaptors::transformed( select_second_const<StdPairRng>() ) );
        }


        template<class StdPairRange>
        inline select_first_range<StdPairRange>
        keys(const StdPairRange& rng)
        {
            return select_first_range<StdPairRange>(
                range_detail::select_first<StdPairRange>(), rng );
        }


        template<class StdPairRange>
        inline select_second_const_range<StdPairRange>
        values(const StdPairRange& rng)
        {
            return select_second_const_range<StdPairRange>(
                range_detail::select_second_const<StdPairRange>(), rng );
        }


        template<class StdPairRange>
        inline select_second_mutable_range<StdPairRange>
        values(StdPairRange& rng)
        {
            return select_second_mutable_range<StdPairRange>(
                range_detail::select_second_mutable<StdPairRange>(), rng );
        }


            transformed_range( F f, R& r )
                : base( boost::make_transform_iterator( boost::begin(r), f ),
                        boost::make_transform_iterator( boost::end(r), f ) )

            { }

            transform_holder( T r ) : holder<T>(r)
            { }


        template< class InputRng, class UnaryFunction >
        inline transformed_range<UnaryFunction,InputRng>
        operator|( InputRng& r,
                   const transform_holder<UnaryFunction>& f )
        {
            return transformed_range<UnaryFunction,InputRng>( f.val, r );
        }


        template< class InputRng, class UnaryFunction >
        inline transformed_range<UnaryFunction, const InputRng>
        operator|( const InputRng& r,
                   const transform_holder<UnaryFunction>& f )
        {
           return transformed_range<UnaryFunction, const InputRng>( f.val, r );
        }


        template<class UnaryFunction, class InputRange>
        inline transformed_range<UnaryFunction, InputRange>
        transform(InputRange& rng, UnaryFunction fn)
        {
            return transformed_range<UnaryFunction, InputRange>(fn, rng);
        }


        template<class UnaryFunction, class InputRange>
        inline transformed_range<UnaryFunction, const InputRange>
        transform(const InputRange& rng, UnaryFunction fn)
        {
            return transformed_range<UnaryFunction, const InputRange>(fn, rng);
        }

            explicit indirected_range( R& r )
                : base( r )
            { }


        template< class InputRng >
        inline indirected_range<InputRng>
        operator|( InputRng& r, indirect_forwarder )
        {
            return indirected_range<InputRng>( r );
        }


        template< class InputRng >
        inline indirected_range<const InputRng>
        operator|( const InputRng& r, indirect_forwarder )
        {
            return indirected_range<const InputRng>( r );
        }


        template<class InputRange>
        inline indirected_range<InputRange>
        indirect(InputRange& rng)
        {
            return indirected_range<InputRange>(rng);
        }


        template<class InputRange>
        inline indirected_range<const InputRange>
        indirect(const InputRange& rng)
        {
            return indirected_range<const InputRange>(rng);
        }


            replace_value(const Value& from, const Value& to)
                :   m_from(from), m_to(to)
            {
            }


            const Value& operator()(const Value& x) const
            {
                return (x == m_from) ? m_to : x;
            }


            replaced_range( R& r, value_type from, value_type to )
                : base_t( make_transform_iterator( boost::begin(r), Fn(from, to) ),
                          make_transform_iterator( boost::end(r), Fn(from, to) ) )
            { }

            replace_holder( const T& from, const T& to )
                : holder2<T>(from, to)
            { }


        template< class InputRng >
        inline replaced_range<InputRng>
        operator|( InputRng& r,
                   const replace_holder<BOOST_DEDUCED_TYPENAME range_value<InputRng>::type>& f )
        {
            return replaced_range<InputRng>(r, f.val1, f.val2);
        }


        template<class InputRange>
        inline replaced_range<InputRange>
        replace(InputRange& rng,
                BOOST_DEDUCED_TYPENAME range_value<InputRange>::type from,
                BOOST_DEDUCED_TYPENAME range_value<InputRange>::type to)
        {
            return replaced_range<InputRange>(rng, from, to);
        }


            strided_iterator()
                : m_last()
                , m_stride()
            {
            }


            base_iterator base_end() const { return m_last; }

            difference_type get_stride() const { return m_stride; }

            void increment()
            {
                base_iterator& it = this->base_reference();
                for (difference_type i = 0; (it != m_last) && (i < m_stride); ++i)
                    ++it;
            }

            explicit strided_holder(Difference value) : holder<Difference>(value) {}


            skip_iterator() : m_last() {}


            skip_iterator(iter_t it, iter_t last, const Pred& pred)
                : base_t(it)
                , pred_t(pred)
                , m_last(last)
            {
                move_to_next_valid();
            }


            template<class OtherIter>
            skip_iterator( const skip_iterator<OtherIter, pred_t, default_pass>& other )
            : base_t(other.base())
            , pred_t(other)
            , m_last(other.m_last) {}


            void move_to_next_valid()
            {
                iter_t& it = this->base_reference();
                pred_t& bi_pred = *this;
                if (it != m_last)
                {
                    if (default_pass)
                    {
                        iter_t nxt = ::boost::next(it);
                        while (nxt != m_last && !bi_pred(*it, *nxt))
                        {
                            ++it;
                            ++nxt;
                        }
                    }
                    else
                    {
                        iter_t nxt = ::boost::next(it);
                        for(; nxt != m_last; ++it, ++nxt)
                        {
                            if (bi_pred(*it, *nxt))
                            {
                                break;
                            }
                        }
                        if (nxt == m_last)
                        {
                            it = m_last;
                        }
                    }
                }
            }


            void increment()
            {
                iter_t& it = this->base_reference();
                BOOST_ASSERT( it != m_last );
                ++it;
                move_to_next_valid();
            }

            adjacent_filtered_range( const P& p, R& r )
            : base_range(skip_iter(boost::begin(r), boost::end(r), p),
                         skip_iter(boost::end(r), boost::end(r), p))
            {
            }

            adjacent_holder( T r ) : holder<T>(r)
            { }

            adjacent_excl_holder( T r ) : holder<T>(r)
            { }


        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, ForwardRng, true>
        operator|( ForwardRng& r,
                   const adjacent_holder<BinPredicate>& f )
        {
            return adjacent_filtered_range<BinPredicate, ForwardRng, true>( f.val, r );
        }


        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, const ForwardRng, true>
        operator|( const ForwardRng& r,
                   const adjacent_holder<BinPredicate>& f )
        {
            return adjacent_filtered_range<BinPredicate,
                                           const ForwardRng, true>( f.val, r );
        }


        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, ForwardRng, false>
        operator|( ForwardRng& r,
                   const adjacent_excl_holder<BinPredicate>& f )
        {
            return adjacent_filtered_range<BinPredicate, ForwardRng, false>( f.val, r );
        }


        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, ForwardRng, false>
        operator|( const ForwardRng& r,
                   const adjacent_excl_holder<BinPredicate>& f )
        {
            return adjacent_filtered_range<BinPredicate,
                                           const ForwardRng, false>( f.val, r );
        }


        template<class ForwardRng, class BinPredicate>
        inline adjacent_filtered_range<BinPredicate, ForwardRng, true>
        adjacent_filter(ForwardRng& rng, BinPredicate filter_pred)
        {
            return adjacent_filtered_range<BinPredicate, ForwardRng, true>(filter_pred, rng);
        }


        template<class ForwardRng, class BinPredicate>
        inline adjacent_filtered_range<BinPredicate, const ForwardRng, true>
        adjacent_filter(const ForwardRng& rng, BinPredicate filter_pred)
        {
            return adjacent_filtered_range<BinPredicate, const ForwardRng, true>(filter_pred, rng);
        }

            template< class Regex, class Submatch, class Flag >
            tokenized_range( R& r, const Regex& re, const Submatch& sub, Flag f )
              : base( regex_iter( boost::begin(r), boost::end(r), 
                                  regex_type(re), sub, f ),
                      regex_iter() )
            { }


            regex_holder( const T& rex, const U& subm, V flag ) :
                re(rex), sub(subm), f(flag)
            { }
           
            template< class Regex >
            regex_holder<Regex,int,regex_constants::match_flag_type>
            operator()( const Regex& re, 
                        int submatch = 0,    
                        regex_constants::match_flag_type f = 
                            regex_constants::match_default ) const
            {
                return regex_holder<Regex,int,
                           regex_constants::match_flag_type>( re, submatch, f );
            }

        
        template< class BidirectionalRng, class R, class S, class F >
        inline tokenized_range<BidirectionalRng> 
        operator|( BidirectionalRng& r, 
                   const regex_holder<R,S,F>& f )
        {
            return tokenized_range<BidirectionalRng>( r, f.re, f.sub, f.f );   
        }


        template< class BidirectionalRng, class R, class S, class F  >
        inline tokenized_range<const BidirectionalRng> 
        operator|( const BidirectionalRng& r, 
                   const regex_holder<R,S,F>& f )
        {
            return tokenized_range<const BidirectionalRng>( r, f.re, f.sub, f.f );
        }

        
        template<class BidirectionalRange, class Regex, class Submatch, class Flag>
        inline tokenized_range<BidirectionalRange>
        tokenize(BidirectionalRange& rng, const Regex& reg, const Submatch& sub, Flag f)
        {
            return tokenized_range<BidirectionalRange>(rng, reg, sub, f);
        }

        
        template<class BidirectionalRange, class Regex, class Submatch, class Flag>
        inline tokenized_range<const BidirectionalRange>
        tokenize(const BidirectionalRange& rng, const Regex& reg, const Submatch& sub, Flag f)
        {
            return tokenized_range<const BidirectionalRange>(rng, reg, sub, f);
        }

            copied(std::size_t t_, std::size_t u_)
                : t(t_), u(u_) {}


        template< class CopyableRandomAccessRng >
        inline CopyableRandomAccessRng
        operator|( const CopyableRandomAccessRng& r, const copied& f )
        {
            iterator_range<
                BOOST_DEDUCED_TYPENAME range_iterator<const
                                               CopyableRandomAccessRng>::type >
            temp( adaptors::slice( r, f.t, f.u ) );
            return CopyableRandomAccessRng( temp.begin(), temp.end() );
        }


        template<class CopyableRandomAccessRange>
        inline CopyableRandomAccessRange
        copy(const CopyableRandomAccessRange& rng, std::size_t t, std::size_t u)
        {
            iterator_range<
                BOOST_DEDUCED_TYPENAME range_iterator<const
                    CopyableRandomAccessRange>::type> temp(
                        adaptors::slice(rng, t, u));

            return CopyableRandomAccessRange( temp.begin(), temp.end() );
        }

            explicit indexed(std::size_t x) : val(x) {}

            indexed_iterator()
            : m_index(index_type()) {}


            index_type index() const
            {
                return m_index;
            }


            void increment()
            {
                ++m_index;
                ++(this->base_reference());
            }



            void decrement()
            {
                BOOST_ASSERT( m_index > 0 && "Indexed Iterator out of bounds" );
                --m_index;
                --(this->base_reference());
            }


            void advance( index_type n )
            {
                m_index += n;
                BOOST_ASSERT( m_index >= 0 && "Indexed Iterator out of bounds" );
                this->base_reference() += n;
            }

            template< class Index >
            indexed_range( Index i, Rng& r )
              : base( iter_type(boost::begin(r), i), iter_type(boost::end(r),i) )
            { }

        template< class SinglePassRange >
        inline indexed_range<SinglePassRange>
        operator|( SinglePassRange& r,
                   const indexed& f )
        {
            return indexed_range<SinglePassRange>( f.val, r );
        }


        template< class SinglePassRange >
        inline indexed_range<const SinglePassRange>
        operator|( const SinglePassRange& r,
                   const indexed& f )
        {
            return indexed_range<const SinglePassRange>( f.val, r );
        }


        template<class SinglePassRange, class Index>
        inline indexed_range<SinglePassRange>
        index(SinglePassRange& rng, Index index_value)
        {
            return indexed_range<SinglePassRange>(index_value, rng);
        }


        template<class SinglePassRange, class Index>
        inline indexed_range<const SinglePassRange>
        index(const SinglePassRange& rng, Index index_value)
        {
            return indexed_range<const SinglePassRange>(index_value, rng);
        }

template< class ForwardRange, class Value >
inline ForwardRange& fill(ForwardRange& rng, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    std::fill(boost::begin(rng), boost::end(rng), val);
    return rng;
}

template< class ForwardRange, class Value >
inline const ForwardRange& fill(const ForwardRange& rng, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    std::fill(boost::begin(rng), boost::end(rng), val);
    return rng;
}

template< class SinglePassRange, class OutputIterator, class Value >
inline OutputIterator
remove_copy(const SinglePassRange& rng, OutputIterator out_it, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    return std::remove_copy(boost::begin(rng), boost::end(rng), out_it, val);
}

template< class ForwardRange, class OutputIterator, class Predicate, class Value >
inline OutputIterator
replace_copy_if(const ForwardRange& rng, OutputIterator out_it, Predicate pred,
        const Value& with_what)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::replace_copy_if(boost::begin(rng), boost::end(rng), out_it,
        pred, with_what);
}

template< class SinglePassRange, class UnaryFunction >
inline UnaryFunction for_each(SinglePassRange & rng, UnaryFunction fun)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange> ));
    
#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        return for_each_detail::for_each_impl<
                typename range_iterator<SinglePassRange>::type,
                UnaryFunction
        >(boost::begin(rng), boost::end(rng), fun);
#else
    return std::for_each<
        BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange>::type,
        UnaryFunction
    >(boost::begin(rng),boost::end(rng),fun);
#endif    
}

template< class SinglePassRange, class UnaryFunction >
inline UnaryFunction for_each(const SinglePassRange& rng, UnaryFunction fun)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    
#if BOOST_WORKAROUND(BOOST_MSVC, == 1600)
        return for_each_detail::for_each_impl<
                typename range_iterator<const SinglePassRange>::type,
                UnaryFunction
        >(boost::begin(rng), boost::end(rng), fun);
#else    
    return std::for_each<
        BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange>::type,
        UnaryFunction
    >(boost::begin(rng), boost::end(rng), fun);
#endif    
}

        template< class SinglePassRange1,
                  class OutputIterator,
                  class UnaryOperation >
        inline OutputIterator
        transform(const SinglePassRange1& rng,
                  OutputIterator          out,
                  UnaryOperation          fun)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            return std::transform(boost::begin(rng),boost::end(rng),out,fun);
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class OutputIterator,
                  class BinaryFunction >
        inline OutputIterator
        transform_impl(SinglePassTraversalReadableIterator1 first1,
                       SinglePassTraversalReadableIterator1 last1,
                       SinglePassTraversalReadableIterator2 first2,
                       SinglePassTraversalReadableIterator2 last2,
                       OutputIterator                       out,
                       BinaryFunction                       fn)
        {
            for (; first1 != last1; ++first1, ++first2)
            {
                BOOST_ASSERT( first2 != last2 );
                *out = fn(*first1, *first2);
                ++out;
            }
            return out;
        }

        template< class SinglePassRange1,
                  class SinglePassRange2,
                  class OutputIterator,
                  class BinaryOperation >
        inline OutputIterator
        transform(const SinglePassRange1& rng1,
                  const SinglePassRange2& rng2,
                  OutputIterator          out,
                  BinaryOperation         fun)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
            return boost::range_detail::transform_impl(
                        boost::begin(rng1), boost::end(rng1),
                        boost::begin(rng2), boost::end(rng2),
                        out, fun);
        }

        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class IteratorCategoryTag1,
                  class IteratorCategoryTag2 >
        inline bool equal_impl( SinglePassTraversalReadableIterator1 first1,
                                SinglePassTraversalReadableIterator1 last1,
                                SinglePassTraversalReadableIterator2 first2,
                                SinglePassTraversalReadableIterator2 last2,
                                IteratorCategoryTag1,
                                IteratorCategoryTag2 )
        {
            while (true)
            {
                // If we have reached the end of the left range then this is
                // the end of the loop. They are equal if and only if we have
                // simultaneously reached the end of the right range.
                if (first1 == last1)
                    return first2 == last2;

                // If we have reached the end of the right range at this line
                // it indicates that the right range is shorter than the left
                // and hence the result is false.
                if (first2 == last2)
                    return false;

                // continue looping if and only if the values are equal
                if (*first1 != *first2)
                    break;

                ++first1;
                ++first2;
            }

            // Reaching this line in the algorithm indicates that a value
            // inequality has been detected.
            return false;
        }


        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class IteratorCategoryTag1,
                  class IteratorCategoryTag2,
                  class BinaryPredicate >
        inline bool equal_impl( SinglePassTraversalReadableIterator1 first1,
                                SinglePassTraversalReadableIterator1 last1,
                                SinglePassTraversalReadableIterator2 first2,
                                SinglePassTraversalReadableIterator2 last2,
                                BinaryPredicate                      pred,
                                IteratorCategoryTag1,
                                IteratorCategoryTag2 )
        {
            while (true)
            {
                // If we have reached the end of the left range then this is
                // the end of the loop. They are equal if and only if we have
                // simultaneously reached the end of the right range.
                if (first1 == last1)
                    return first2 == last2;

                // If we have reached the end of the right range at this line
                // it indicates that the right range is shorter than the left
                // and hence the result is false.
                if (first2 == last2)
                    return false;

                // continue looping if and only if the values are equal
                if (!pred(*first1, *first2))
                    break;

                ++first1;
                ++first2;
            }

            // Reaching this line in the algorithm indicates that a value
            // inequality has been detected.
            return false;
        }


        template< class RandomAccessTraversalReadableIterator1,
                  class RandomAccessTraversalReadableIterator2,
                  class BinaryPredicate >
        inline bool equal_impl( RandomAccessTraversalReadableIterator1 first1,
                                RandomAccessTraversalReadableIterator1 last1,
                                RandomAccessTraversalReadableIterator2 first2,
                                RandomAccessTraversalReadableIterator2 last2,
                                BinaryPredicate                        pred )
        {
            return ((last1 - first1) == (last2 - first2))
                && std::equal(first1, last1, first2, pred);
        }


        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2 >
        inline bool equal( SinglePassTraversalReadableIterator1 first1,
                           SinglePassTraversalReadableIterator1 last1,
                           SinglePassTraversalReadableIterator2 first2,
                           SinglePassTraversalReadableIterator2 last2 )
        {
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

            return equal_impl(first1, last1, first2, last2, tag1, tag2);
        }


        template< class SinglePassTraversalReadableIterator1,
                  class SinglePassTraversalReadableIterator2,
                  class BinaryPredicate >
        inline bool equal( SinglePassTraversalReadableIterator1 first1,
                           SinglePassTraversalReadableIterator1 last1,
                           SinglePassTraversalReadableIterator2 first2,
                           SinglePassTraversalReadableIterator2 last2,
                           BinaryPredicate                      pred )
        {
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator1 >::iterator_category tag1;
            BOOST_DEDUCED_TYPENAME std::iterator_traits< SinglePassTraversalReadableIterator2 >::iterator_category tag2;

            return equal_impl(first1, last1, first2, last2, pred, tag1, tag2);
        }

        template< class SinglePassRange1, class SinglePassRange2 >
        inline bool equal( const SinglePassRange1& rng1, const SinglePassRange2& rng2 )
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::equal(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2) );
        }

        template< class SinglePassRange1, class SinglePassRange2, class BinaryPredicate >
        inline bool equal( const SinglePassRange1& rng1, const SinglePassRange2& rng2,
                           BinaryPredicate pred )
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::equal(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2),
                pred);
        }

template<class RandomAccessRange>
inline RandomAccessRange& random_shuffle(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::random_shuffle(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& random_shuffle(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::random_shuffle(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class Generator>
inline RandomAccessRange& random_shuffle(RandomAccessRange& rng, Generator& gen)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::random_shuffle(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

template<class RandomAccessRange, class Generator>
inline const RandomAccessRange& random_shuffle(const RandomAccessRange& rng, Generator& gen)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::random_shuffle(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

template< class ForwardRange, class Value >
inline ForwardRange&
replace(ForwardRange& rng, const Value& what,
        const Value& with_what)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    std::replace(boost::begin(rng), boost::end(rng), what, with_what);
    return rng;
}

template< class ForwardRange, class Value >
inline const ForwardRange&
replace(const ForwardRange& rng, const Value& what,
        const Value& with_what)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    std::replace(boost::begin(rng), boost::end(rng), what, with_what);
    return rng;
}

template<class BidirectionalRange>
inline BidirectionalRange& inplace_merge(BidirectionalRange& rng,
    BOOST_DEDUCED_TYPENAME range_iterator<BidirectionalRange>::type middle)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    std::inplace_merge(boost::begin(rng), middle, boost::end(rng));
    return rng;
}

template< class SinglePassRange, class OutputIterator >
inline OutputIterator copy(const SinglePassRange& rng, OutputIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    return std::copy(boost::begin(rng),boost::end(rng),out);
}

        template<class Iterator1, class Iterator2>
        void swap_ranges_impl(Iterator1 it1, Iterator1 last1,
                              Iterator2 it2, Iterator2 last2,
                              single_pass_traversal_tag,
                              single_pass_traversal_tag)
        {
            ignore_unused_variable_warning(last2);
            for (; it1 != last1; ++it1, ++it2)
            {
                BOOST_ASSERT( it2 != last2 );
                std::iter_swap(it1, it2);
            }
        }


        template<class Iterator1, class Iterator2>
        void swap_ranges_impl(Iterator1 first1, Iterator1 last1,
                              Iterator2 first2, Iterator2 last2)
        {
            swap_ranges_impl(first1, last1, first2, last2,
                BOOST_DEDUCED_TYPENAME iterator_traversal<Iterator1>::type(),
                BOOST_DEDUCED_TYPENAME iterator_traversal<Iterator2>::type());
        }

template< class SinglePassRange1, class SinglePassRange2 >
inline SinglePassRange2&
swap_ranges(SinglePassRange1& range1, SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

template< class SinglePassRange1, class SinglePassRange2 >
inline SinglePassRange2&
swap_ranges(const SinglePassRange1& range1, SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

template< class SinglePassRange1, class SinglePassRange2 >
inline const SinglePassRange2&
swap_ranges(SinglePassRange1& range1, const SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

template< class SinglePassRange1, class SinglePassRange2 >
inline const SinglePassRange2&
swap_ranges(const SinglePassRange1& range1, const SinglePassRange2& range2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange1>));
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange2>));

    boost::range_detail::swap_ranges_impl(
        boost::begin(range1), boost::end(range1),
        boost::begin(range2), boost::end(range2));

    return range2;
}

template<class BidirectionalRange, class OutputIterator>
inline OutputIterator reverse_copy(const BidirectionalRange& rng, OutputIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::reverse_copy(boost::begin(rng), boost::end(rng), out);
}

template< class ForwardRange, class OutputIterator, class Value >
inline OutputIterator
replace_copy(const ForwardRange& rng, OutputIterator out_it, const Value& what,
        const Value& with_what)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::replace_copy(boost::begin(rng), boost::end(rng), out_it,
        what, with_what);
}

    template<typename ForwardRange, typename OutputIterator>
    inline OutputIterator rotate_copy(
        const ForwardRange&                                             rng,
        BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type middle,
        OutputIterator                                                  target
        )
    {
        BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
        return std::rotate_copy(boost::begin(rng), middle, boost::end(rng), target);
    }

template<class RandomAccessRange>
inline RandomAccessRange& sort(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& sort(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class BinaryPredicate>
inline RandomAccessRange& sort(RandomAccessRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort(boost::begin(rng), boost::end(rng), pred);
    return rng;
}

template<class RandomAccessRange, class BinaryPredicate>
inline const RandomAccessRange& sort(const RandomAccessRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort(boost::begin(rng), boost::end(rng), pred);
    return rng;
}

template<class BidirectionalRange>
inline BidirectionalRange& reverse(BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    std::reverse(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class BidirectionalRange>
inline const BidirectionalRange& reverse(const BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    std::reverse(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class BidirectionalRange>
inline bool next_permutation(BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng));
}

template<class BidirectionalRange>
inline bool next_permutation(const BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng));
}

template<class BidirectionalRange, class Compare>
inline bool next_permutation(BidirectionalRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

template<class BidirectionalRange, class Compare>
inline bool next_permutation(const BidirectionalRange& rng,
                             Compare                   comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::next_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

template<class BidirectionalRange>
inline bool prev_permutation(BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng));
}

template<class BidirectionalRange>
inline bool prev_permutation(const BidirectionalRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng));
}

template<class BidirectionalRange, class Compare>
inline bool prev_permutation(BidirectionalRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

template<class BidirectionalRange, class Compare>
inline bool prev_permutation(const BidirectionalRange& rng,
                             Compare                   comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::prev_permutation(boost::begin(rng), boost::end(rng),
                                 comp_pred);
}

template< class ForwardRange, class Size, class Value >
inline ForwardRange& fill_n(ForwardRange& rng, Size n, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    BOOST_ASSERT( static_cast<Size>(std::distance(boost::begin(rng), boost::end(rng))) >= n );
    std::fill_n(boost::begin(rng), n, val);
    return rng;
}

template< class ForwardRange, class Size, class Value >
inline const ForwardRange& fill_n(const ForwardRange& rng, Size n, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    BOOST_ASSERT( static_cast<Size>(std::distance(boost::begin(rng), boost::end(rng))) >= n );
    std::fill_n(boost::begin(rng), n, val);
    return rng;
}

template< class ForwardRange, class UnaryPredicate, class Value >
inline ForwardRange&
    replace_if(ForwardRange& rng, UnaryPredicate pred,
               const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    std::replace_if(boost::begin(rng), boost::end(rng), pred, val);
    return rng;
}

template< class ForwardRange, class UnaryPredicate, class Value >
inline const ForwardRange&
    replace_if(const ForwardRange& rng, UnaryPredicate pred,
               const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    std::replace_if(boost::begin(rng), boost::end(rng), pred, val);
    return rng;
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator merge(const SinglePassRange1& rng1,
                            const SinglePassRange2& rng2,
                            OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::merge(boost::begin(rng1), boost::end(rng1),
                      boost::begin(rng2), boost::end(rng2), out);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator merge(const SinglePassRange1& rng1,
                            const SinglePassRange2& rng2,
                            OutputIterator          out,
                            BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::merge(boost::begin(rng1), boost::end(rng1),
                      boost::begin(rng2), boost::end(rng2), out, pred);
}

template<class RandomAccessRange>
inline RandomAccessRange& push_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& push_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class Compare>
inline RandomAccessRange& push_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& push_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::push_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange>
inline RandomAccessRange& pop_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& pop_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class Compare>
inline RandomAccessRange& pop_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& pop_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::pop_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange>
inline RandomAccessRange& make_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& make_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class Compare>
inline RandomAccessRange& make_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& make_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::make_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange>
inline RandomAccessRange& sort_heap(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& sort_heap(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class Compare>
inline RandomAccessRange& sort_heap(RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class RandomAccessRange, class Compare>
inline const RandomAccessRange& sort_heap(const RandomAccessRange& rng, Compare comp_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::sort_heap(boost::begin(rng), boost::end(rng), comp_pred);
    return rng;
}

template<class ForwardRange>
inline ForwardRange& rotate(ForwardRange& rng,
    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type middle)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    std::rotate(boost::begin(rng), middle, boost::end(rng));
    return rng;
}

template<class SinglePassRange1, class SinglePassRange2>
inline bool includes(const SinglePassRange1& rng1,
                     const SinglePassRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::includes(boost::begin(rng1),boost::end(rng1),
                         boost::begin(rng2),boost::end(rng2));
}

template<class SinglePassRange1, class SinglePassRange2,
         class BinaryPredicate>
inline bool includes(const SinglePassRange1& rng1,
                     const SinglePassRange2& rng2,
                     BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::includes(boost::begin(rng1), boost::end(rng1),
                         boost::begin(rng2), boost::end(rng2), pred);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_union(const SinglePassRange1& rng1,
                                const SinglePassRange2& rng2,
                                OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_union(boost::begin(rng1), boost::end(rng1),
                          boost::begin(rng2), boost::end(rng2), out);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_union(const SinglePassRange1& rng1,
                                const SinglePassRange2& rng2,
                                OutputIterator          out,
                                BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_union(boost::begin(rng1), boost::end(rng1),
                          boost::begin(rng2), boost::end(rng2), out, pred);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_intersection(const SinglePassRange1& rng1,
                                       const SinglePassRange2& rng2,
                                       OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_intersection(boost::begin(rng1), boost::end(rng1),
                                 boost::begin(rng2), boost::end(rng2), out);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_intersection(const SinglePassRange1& rng1,
                                       const SinglePassRange2& rng2,
                                       OutputIterator          out,
                                       BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_intersection(boost::begin(rng1), boost::end(rng1),
                                 boost::begin(rng2), boost::end(rng2),
                                 out, pred);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator set_difference(const SinglePassRange1& rng1,
                                     const SinglePassRange2& rng2,
                                     OutputIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_difference(boost::begin(rng1), boost::end(rng1),
                               boost::begin(rng2), boost::end(rng2), out);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator set_difference(const SinglePassRange1& rng1,
                                     const SinglePassRange2& rng2,
                                     OutputIterator          out,
                                     BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_difference(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), out, pred);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator>
inline OutputIterator
set_symmetric_difference(const SinglePassRange1& rng1,
                         const SinglePassRange2& rng2,
                         OutputIterator          out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_symmetric_difference(boost::begin(rng1), boost::end(rng1),
                                         boost::begin(rng2), boost::end(rng2), out);
}

template<class SinglePassRange1, class SinglePassRange2,
         class OutputIterator, class BinaryPredicate>
inline OutputIterator
set_symmetric_difference(const SinglePassRange1& rng1,
                         const SinglePassRange2& rng2,
                         OutputIterator          out,
                         BinaryPredicate         pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::set_symmetric_difference(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), out, pred);
}

template<class RandomAccessRange>
inline RandomAccessRange& partial_sort(RandomAccessRange& rng,
    BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type middle)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::partial_sort(boost::begin(rng), middle, boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline RandomAccessRange& nth_element(RandomAccessRange& rng,
    BOOST_DEDUCED_TYPENAME range_iterator<RandomAccessRange>::type nth)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::nth_element(boost::begin(rng), nth, boost::end(rng));
    return rng;
}

template< class ForwardRange, class Generator >
inline ForwardRange& generate( ForwardRange& rng, Generator gen )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    std::generate(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

template< class ForwardRange, class Generator >
inline const ForwardRange& generate( const ForwardRange& rng, Generator gen )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    std::generate(boost::begin(rng), boost::end(rng), gen);
    return rng;
}

adjacent_find(const ForwardRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return std::adjacent_find(boost::begin(rng),boost::end(rng));
}

template<class SinglePassRange1, class SinglePassRange2>
inline bool lexicographical_compare(const SinglePassRange1& rng1,
                                    const SinglePassRange2& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::lexicographical_compare(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2));
}

template<class SinglePassRange1, class SinglePassRange2,
         class BinaryPredicate>
inline bool lexicographical_compare(const SinglePassRange1& rng1,
                                    const SinglePassRange2& rng2,
                                    BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));
    return std::lexicographical_compare(
        boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), pred);
}

template<class RandomAccessRange>
inline RandomAccessRange& stable_sort(RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::stable_sort(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange>
inline const RandomAccessRange& stable_sort(const RandomAccessRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::stable_sort(boost::begin(rng), boost::end(rng));
    return rng;
}

template<class RandomAccessRange, class BinaryPredicate>
inline RandomAccessRange& stable_sort(RandomAccessRange& rng, BinaryPredicate sort_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<RandomAccessRange> ));
    std::stable_sort(boost::begin(rng), boost::end(rng), sort_pred);
    return rng;
}

template<class RandomAccessRange, class BinaryPredicate>
inline const RandomAccessRange& stable_sort(const RandomAccessRange& rng, BinaryPredicate sort_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( RandomAccessRangeConcept<const RandomAccessRange> ));
    std::stable_sort(boost::begin(rng), boost::end(rng), sort_pred);
    return rng;
}

    template<typename ForwardIterator, typename Integer, typename Value>
    inline ForwardIterator
    search_n_impl(ForwardIterator first, ForwardIterator last, Integer count,
                  const Value& value, std::forward_iterator_tag)
    {
        first = std::find(first, last, value);
        while (first != last)
        {
            typename std::iterator_traits<ForwardIterator>::difference_type n = count;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 1 && *i==value)
            {
                ++i;
                --n;
            }
            if (n == 1)
                return first;
            if (i == last)
                return last;
            first = std::find(++i, last, value);
        }
        return last;
    }

    template<typename ForwardIterator, typename Integer, typename Value,
             typename BinaryPredicate>
    inline ForwardIterator
    search_n_pred_impl(ForwardIterator first, ForwardIterator last,
                       Integer count, const Value& value,
                       BinaryPredicate pred, std::forward_iterator_tag)
    {
        typedef typename std::iterator_traits<ForwardIterator>::difference_type difference_t;

        while (first != last && !static_cast<bool>(pred(*first, value)))
            ++first;

        while (first != last)
        {
            difference_t n = count;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 1 && static_cast<bool>(pred(*i, value)))
            {
                ++i;
                --n;
            }
            if (n == 1)
                return first;
            if (i == last)
                return last;
            first = ++i;
            while (first != last && !static_cast<bool>(pred(*first, value)))
                ++first;
        }
        return last;
    }


    template<typename ForwardIterator, typename Integer, typename Value>
    inline ForwardIterator
    search_n_impl(ForwardIterator first, ForwardIterator last,
                  Integer count, const Value& value)
    {
        BOOST_RANGE_CONCEPT_ASSERT((ForwardIteratorConcept<ForwardIterator>));
        BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept<Value>));
        BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept<typename std::iterator_traits<ForwardIterator>::value_type>));
        //BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept2<typename std::iterator_traits<ForwardIterator>::value_type, Value>));

        typedef typename std::iterator_traits<ForwardIterator>::iterator_category cat_t;

        if (count <= 0)
            return first;
        if (count == 1)
            return std::find(first, last, value);
        return range_detail::search_n_impl(first, last, count, value, cat_t());
    }


    template<typename ForwardIterator, typename Integer, typename Value,
             typename BinaryPredicate>
    inline ForwardIterator
    search_n_pred_impl(ForwardIterator first, ForwardIterator last,
                       Integer count, const Value& value,
                       BinaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT((ForwardIteratorConcept<ForwardIterator>));
        BOOST_RANGE_CONCEPT_ASSERT((
            BinaryPredicateConcept<
                BinaryPredicate,
                typename std::iterator_traits<ForwardIterator>::value_type,
                Value>
            ));

        typedef typename std::iterator_traits<ForwardIterator>::iterator_category cat_t;

        if (count <= 0)
            return first;
        if (count == 1)
        {
            while (first != last && !static_cast<bool>(pred(*first, value)))
                ++first;
            return first;
        }
        return range_detail::search_n_pred_impl(first, last, count,
                                                value, pred, cat_t());
    }

template< class BidirectionalRange, class BidirectionalTraversalWriteableIterator >
inline BidirectionalTraversalWriteableIterator
copy_backward(const BidirectionalRange& rng,
              BidirectionalTraversalWriteableIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( BidirectionalRangeConcept<const BidirectionalRange> ));
    return std::copy_backward(boost::begin(rng), boost::end(rng), out);
}

template<class ForwardRange, class Value>
inline bool binary_search(const ForwardRange& rng, const Value& val)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::binary_search(boost::begin(rng), boost::end(rng), val);
}

template<class ForwardRange, class Value, class BinaryPredicate>
inline bool binary_search(const ForwardRange& rng, const Value& val,
                          BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    return std::binary_search(boost::begin(rng), boost::end(rng), val, pred);
}

template< class SinglePassRange, class OutputIterator >
inline OutputIterator
unique_copy( const SinglePassRange& rng, OutputIterator out_it )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    return std::unique_copy(boost::begin(rng), boost::end(rng), out_it);
}

template< class SinglePassRange, class OutputIterator, class BinaryPredicate >
inline OutputIterator
unique_copy( const SinglePassRange& rng, OutputIterator out_it,
             BinaryPredicate pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    return std::unique_copy(boost::begin(rng), boost::end(rng), out_it, pred);
}

    template< class SinglePassRange, class OutputIterator, class Predicate >
    inline OutputIterator
    remove_copy_if(const SinglePassRange& rng, OutputIterator out_it, Predicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
        return std::remove_copy_if(boost::begin(rng), boost::end(rng), out_it, pred);
    }


template< class Container >
inline Container& erase( Container& on,
      iterator_range<BOOST_DEDUCED_TYPENAME Container::iterator> to_erase )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<Container> ));
    on.erase( boost::begin(to_erase), boost::end(to_erase) );
    return on;
}


template< class Container, class T >
inline Container& remove_erase( Container& on, const T& val )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<Container> ));
    on.erase(
        std::remove(boost::begin(on), boost::end(on), val),
        boost::end(on));
    return on;
}


template< class Container, class Pred >
inline Container& remove_erase_if( Container& on, Pred pred )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<Container> ));
    on.erase(
        std::remove_if(boost::begin(on), boost::end(on), pred),
        boost::end(on));
    return on;
}

        template<class InputIterator1, class InputIterator2, class Fn2>
        inline Fn2 for_each_impl(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Fn2 fn)
        {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            {
                fn(*first1, *first2);
            }
            return fn;
        }

        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(const SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }


        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(const SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }


        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(SinglePassRange1& rng1, const SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }


        template<class SinglePassRange1, class SinglePassRange2, class Fn2>
        inline Fn2 for_each(SinglePassRange1& rng1, SinglePassRange2& rng2, Fn2 fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange1> ));
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

            return ::boost::range_detail::for_each_impl(
                ::boost::begin(rng1), ::boost::end(rng1),
                ::boost::begin(rng2), ::boost::end(rng2), fn);
        }

template<class SinglePassRange>
inline bool is_sorted(const SinglePassRange& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange>));
    BOOST_RANGE_CONCEPT_ASSERT((LessThanComparableConcept<BOOST_DEDUCED_TYPENAME
      range_value<const SinglePassRange>::type>));
    return ::boost::detail::is_sorted(boost::begin(rng), boost::end(rng));
}

template<class SinglePassRange, class BinaryPredicate>
inline bool is_sorted(const SinglePassRange& rng, BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<const SinglePassRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
      BOOST_DEDUCED_TYPENAME range_value<const SinglePassRange>::type,
      BOOST_DEDUCED_TYPENAME range_value<const SinglePassRange>::type>));
    return ::boost::detail::is_sorted(boost::begin(rng), boost::end(rng), pred);
}


template< class Container, class Range >
inline Container& push_front( Container& on, const Range& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Container> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const Range> ));
    BOOST_ASSERT( (void*)&on != (void*)&from &&
                  "cannot copy from a container to itself" );
    on.insert( on.begin(), boost::begin(from), boost::end(from) );
    return on;
}


template< class Container, class Range >
inline Container& push_back( Container& on, const Range& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Container> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const Range> ));
    BOOST_ASSERT( (void*)&on != (void*)&from &&
                  "cannot copy from a container to itself" );
    on.insert( on.end(), boost::begin(from), boost::end(from) );
    return on;
}


template< class SinglePassRange1, class SinglePassRange2 >
inline void overwrite( const SinglePassRange1& from, SinglePassRange2& to )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<SinglePassRange2> ));

    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type
        i = boost::begin(from), e = boost::end(from);

    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type
        out = boost::begin(to);

#ifndef NDEBUG
    BOOST_DEDUCED_TYPENAME range_iterator<SinglePassRange2>::type
        last_out = boost::end(to);
#endif

    for( ; i != e; ++out, ++i )
    {
#ifndef NDEBUG
        BOOST_ASSERT( out != last_out
            && "out of bounds in boost::overwrite()" );
#endif
        *out = *i;
    }
}


template< class SinglePassRange1, class SinglePassRange2 >
inline void overwrite( const SinglePassRange1& from, const SinglePassRange2& to )
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange1> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange2> ));

    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange1>::type
        i = boost::begin(from), e = boost::end(from);

    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type
        out = boost::begin(to);

#ifndef NDEBUG
    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange2>::type
        last_out = boost::end(to);
#endif

    for( ; i != e; ++out, ++i )
    {
#ifndef NDEBUG
        BOOST_ASSERT( out != last_out
            && "out of bounds in boost::overwrite()" );
#endif
        *out = *i;
    }
}


template< class ForwardRange, class Value >
inline ForwardRange& iota( ForwardRange& rng, Value x )
{
    BOOST_CONCEPT_ASSERT(( ForwardRangeConcept<ForwardRange> ));
    typedef BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type iterator_t;

    iterator_t last_target = ::boost::end(rng);
    for (iterator_t target = ::boost::begin(rng); target != last_target; ++target, ++x)
        *target = x;

    return rng;
}


template< class ForwardRange, class Value >
inline const ForwardRange& iota( const ForwardRange& rng, Value x )
{
    BOOST_CONCEPT_ASSERT(( ForwardRangeConcept<const ForwardRange> ));
    typedef BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type iterator_t;
    
    iterator_t last_target = ::boost::end(rng);
    for (iterator_t target = ::boost::begin(rng); target != last_target; ++target, ++x)
        *target = x;
    
    return rng;
}


template< class Container, class Range >
inline Container& insert( Container& on,
                          BOOST_DEDUCED_TYPENAME Container::iterator before,
                          const Range& from )
{
    BOOST_RANGE_CONCEPT_ASSERT(( ForwardRangeConcept<Container> ));
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<Range> ));
    BOOST_ASSERT( (void*)&on != (void*)&from &&
                  "cannot copy from a container to itself" );
    on.insert( before, boost::begin(from), boost::end(from) );
    return on;
}

template< class SinglePassRange, class Size, class OutputIterator >
inline OutputIterator copy_n(const SinglePassRange& rng, Size n, OutputIterator out)
{
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<const SinglePassRange> ));
    BOOST_ASSERT( n <= static_cast<Size>(::boost::distance(rng)) );
    BOOST_ASSERT( n >= static_cast<Size>(0) );

    BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange>::type source = ::boost::begin(rng);

    for (Size i = 0; i < n; ++i, ++out, ++source)
        *out = *source;

    return out;
}
