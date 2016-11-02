
  template<typename T, typename Pred> 
  T const & clamp ( T const& val, 
    typename boost::mpl::identity<T>::type const & lo, 
    typename boost::mpl::identity<T>::type const & hi, Pred p )
  {
//    assert ( !p ( hi, lo ));    // Can't assert p ( lo, hi ) b/c they might be equal
    return p ( val, lo ) ? lo : p ( hi, val ) ? hi : val;
  }

  template<typename InputIterator, typename OutputIterator> 
  OutputIterator clamp_range ( InputIterator first, InputIterator last, OutputIterator out,
    typename std::iterator_traits<InputIterator>::value_type lo, 
    typename std::iterator_traits<InputIterator>::value_type hi )
  {
  // this could also be written with bind and std::transform
    while ( first != last )
        *out++ = clamp ( *first++, lo, hi );
    return out;
  }

      bool operator()(Iterator const& it1,
                      Iterator const& it2) const { return *it1 < *it2; }

      explicit binary_pred_over_iter(BinaryPredicate const& p ) : m_p( p ) {}

      bool operator()(Iterator const& it1,
                      Iterator const& it2) const { return m_p(*it1, *it2); }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_first_min_element(ForwardIter first, ForwardIter last,
                          BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter min_result = first;
    while (++first != last)
      if (comp(first, min_result))
        min_result = first;
    return min_result;
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_last_min_element(ForwardIter first, ForwardIter last,
                         BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter min_result = first;
    while (++first != last)
      if (!comp(min_result, first))
        min_result = first;
    return min_result;
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_first_max_element(ForwardIter first, ForwardIter last,
                          BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter max_result = first;
    while (++first != last)
      if (comp(max_result, first))
        max_result = first;
    return max_result;
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_last_max_element(ForwardIter first, ForwardIter last,
                         BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter max_result = first;
    while (++first != last)
      if (!comp(first, max_result))
        max_result = first;
    return max_result;
  }


  template <typename ForwardIter>
  ForwardIter
  first_min_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_first_min_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  first_min_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_first_min_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }


  template <typename ForwardIter>
  ForwardIter
  last_min_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_min_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  last_min_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_last_min_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }


  template <typename ForwardIter>
  ForwardIter
  first_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_first_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  first_max_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_first_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }


  template <typename ForwardIter>
  ForwardIter
  last_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }


  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  last_max_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_last_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }


    template <typename T, typename OutputIterator>
    OutputIterator encode_one ( T val, OutputIterator out ) {
        const std::size_t num_hex_digits =  2 * sizeof ( T );
        char res [ num_hex_digits ];
        char  *p = res + num_hex_digits;
        for ( std::size_t i = 0; i < num_hex_digits; ++i, val >>= 4 )
            *--p = "0123456789ABCDEF" [ val & 0x0F ];
        return std::copy ( res, res + num_hex_digits, out );
        }


    template <typename T>
    unsigned char hex_char_to_int ( T val ) {
        char c = static_cast<char> ( val );
        unsigned retval = 0;
        if      ( c >= '0' && c <= '9' ) retval = c - '0';
        else if ( c >= 'A' && c <= 'F' ) retval = c - 'A' + 10;
        else if ( c >= 'a' && c <= 'f' ) retval = c - 'a' + 10;
        else BOOST_THROW_EXCEPTION (non_hex_input() << bad_char (c));
        return retval;
        }


    template <typename Iterator> 
    bool iter_end ( Iterator current, Iterator last ) { return current == last; }

  
    template <typename T>
    bool ptr_end ( const T* ptr, const T* /*end*/ ) { return *ptr == '\0'; }

        value_predicate ( Predicate p, Iterator it ) : p_ ( p ), it_ ( it ) {}


        template <typename T1>
        bool operator () ( const T1 &t1 ) const { return p_ ( *it_, t1 ); }

    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
    bool is_permutation_inner ( ForwardIterator1 first1, ForwardIterator1 last1,
                                ForwardIterator2 first2, ForwardIterator2 last2,
                                BinaryPredicate p ) {
        //  for each unique value in the sequence [first1,last1), count how many times
        //  it occurs, and make sure it occurs the same number of times in [first2, last2)
            for ( ForwardIterator1 iter = first1; iter != last1; ++iter ) {
                value_predicate<BinaryPredicate, ForwardIterator1> pred ( p, iter );

            /*  For each value we haven't seen yet... */
                if ( std::find_if ( first1, iter, pred ) == iter ) {
                    std::size_t dest_count = std::count_if ( first2, last2, pred );
                    if ( dest_count == 0 || dest_count != (std::size_t) std::count_if ( iter, last1, pred ))
                        return false;
                    }
                }

        return true;
        }
                      

    template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
    bool is_permutation_tag ( ForwardIterator1 first1, ForwardIterator1 last1, 
                          ForwardIterator2 first2, ForwardIterator2 last2, 
                          BinaryPredicate p,
                          std::forward_iterator_tag, std::forward_iterator_tag ) {

    //  Skip the common prefix (if any)
        while ( first1 != last1 && first2 != last2 && p ( *first1, *first2 )) {
            ++first1;
            ++first2;
            }
        if ( first1 != last1 && first2 != last2 )
            return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
                std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        return first1 == last1 && first2 == last2;
        }

template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, BinaryPredicate p )
{
//  Skip the common prefix (if any)
//  std::tie (first1, first2) = std::mismatch (first1, last1, first2, p);
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2, p);
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2, p );
        }

    return true;
}

template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
//  Skip the common prefix (if any)
    std::pair<ForwardIterator1, ForwardIterator2> eq = std::mismatch (first1, last1, first2 );
    first1 = eq.first;
    first2 = eq.second;
    if ( first1 != last1 ) {
    //  Create last2
        ForwardIterator2 last2 = first2;
        std::advance ( last2, std::distance (first1, last1));
        return boost::algorithm::detail::is_permutation_inner ( first1, last1, first2, last2,
            std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> ());
        }
    return true;
}

template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, 
                      ForwardIterator2 first2, ForwardIterator2 last2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
    return boost::algorithm::detail::is_permutation_tag (
        first1, last1, first2, last2, 
        std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> (),
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, ForwardIterator2 last2, 
                      BinaryPredicate pred )
{
    return boost::algorithm::detail::is_permutation_tag (
        first1, last1, first2, last2, pred, 
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

template <typename Range, typename ForwardIterator>
bool is_permutation ( const Range &r, ForwardIterator first2 )
{
    return boost::algorithm::is_permutation (boost::begin (r), boost::end (r), first2 );
}

template<typename InputIterator, typename Predicate> 
bool none_of ( InputIterator first, InputIterator last, Predicate p )
{
for ( ; first != last; ++first )
    if ( p(*first)) 
        return false;
    return true;
}

template<typename Range, typename Predicate> 
bool none_of ( const Range &r, Predicate p )
{
    return boost::algorithm::none_of (boost::begin (r), boost::end (r), p );
}

template<typename InputIterator, typename V> 
bool none_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return false;
    return true; 
}

template<typename Range, typename V> 
bool none_of_equal ( const Range &r, const V & val ) 
{
    return boost::algorithm::none_of_equal (boost::begin (r), boost::end (r), val);
}

template <typename ForwardIterator, typename Predicate>
ForwardIterator partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
{
    std::size_t dist = std::distance ( first, last );
    while ( first != last ) {
        std::size_t d2 = dist / 2;
        ForwardIterator ret_val = first;
        std::advance (ret_val, d2);
        if (p (*ret_val)) {
            first = ++ret_val;
            dist -= d2 + 1;
            }
        else {
            last = ret_val;
            dist = d2;
            }
        }
    return first;
}

template<typename InputIterator, typename Predicate> 
bool all_of ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( !p(*first)) 
            return false;
    return true; 
}

template<typename Range, typename Predicate> 
bool all_of ( const Range &r, Predicate p )
{
    return boost::algorithm::all_of ( boost::begin (r), boost::end (r), p );
}

template<typename InputIterator, typename T> 
bool all_of_equal ( InputIterator first, InputIterator last, const T &val )
{
    for ( ; first != last; ++first )
    if ( val != *first ) 
        return false;
    return true; 
}

template<typename Range, typename T> 
bool all_of_equal ( const Range &r, const T &val ) 
{
    return boost::algorithm::all_of_equal ( boost::begin (r), boost::end (r), val );
}

    template <typename ForwardIterator, typename Pred>
    ForwardIterator is_sorted_until ( ForwardIterator first, ForwardIterator last, Pred p )
    {
        if ( first == last ) return last;  // the empty sequence is ordered
        ForwardIterator next = first;
        while ( ++next != last )
        {
            if ( p ( *next, *first ))
                return next;
            first = next;
        }
        return last;    
    }

    template <typename ForwardIterator>
    ForwardIterator is_sorted_until ( ForwardIterator first, ForwardIterator last )
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
        return boost::algorithm::is_sorted_until ( first, last, std::less<value_type>());
    }

    template <typename ForwardIterator, typename Pred>
    bool is_sorted ( ForwardIterator first, ForwardIterator last, Pred p )
    {
        return boost::algorithm::is_sorted_until (first, last, p) == last;
    }

    template <typename ForwardIterator>
    bool is_sorted ( ForwardIterator first, ForwardIterator last )
    {
        return boost::algorithm::is_sorted_until (first, last) == last;
    }

template<typename InputIterator, typename OutputIterator, typename Predicate> 
OutputIterator copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last; ++first )
        if (p(*first))
            *result++ = *first;
    return result;
}

template<typename Range, typename OutputIterator, typename Predicate>
OutputIterator copy_if ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_if (boost::begin (r), boost::end(r), result, p);
}

template <typename InputIterator, typename UnaryPredicate>
bool is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return false;
    return true;
}

template <typename Range, typename UnaryPredicate>
bool is_partitioned ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned (boost::begin(r), boost::end(r), p);
}

template<typename InputIterator, typename Predicate> 
bool any_of ( InputIterator first, InputIterator last, Predicate p ) 
{
    for ( ; first != last; ++first )
        if ( p(*first)) 
            return true;
    return false; 
}

template<typename Range, typename Predicate> 
bool any_of ( const Range &r, Predicate p )
{
    return boost::algorithm::any_of (boost::begin (r), boost::end (r), p);
}

template<typename InputIterator, typename V> 
bool any_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return true;
    return false; 
}

template<typename Range, typename V> 
bool any_of_equal ( const Range &r, const V &val ) 
{
    return boost::algorithm::any_of_equal (boost::begin (r), boost::end (r), val);
}

template<typename InputIterator, typename Predicate> 
bool one_of ( InputIterator first, InputIterator last, Predicate p )
{
    InputIterator i = std::find_if (first, last, p);
    if (i == last)
        return false;    // Didn't occur at all
    return boost::algorithm::none_of (++i, last, p);
}

template<typename Range, typename Predicate> 
bool one_of ( const Range &r, Predicate p ) 
{
    return boost::algorithm::one_of ( boost::begin (r), boost::end (r), p );
}

template<typename InputIterator, typename V> 
bool one_of_equal ( InputIterator first, InputIterator last, const V &val )
{
    InputIterator i = std::find (first, last, val); // find first occurrence of 'val'
    if (i == last)
        return false;                    // Didn't occur at all
    return boost::algorithm::none_of_equal (++i, last, val);
}

template<typename Range, typename V> 
bool one_of_equal ( const Range &r, const V &val )
{
    return boost::algorithm::one_of_equal ( boost::begin (r), boost::end (r), val );
}

template<typename InputIterator, typename Predicate> 
InputIterator find_if_not ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( !p(*first))
            break;
    return first;
}

template <typename ForwardIterator, typename T>
void iota ( ForwardIterator first, ForwardIterator last, T value )
{
    for ( ; first != last; ++first, ++value )
        *first = value;
}

template <typename Range, typename T>
void iota ( Range &r, T value )
{
    boost::algorithm::iota (boost::begin(r), boost::end(r), value);
}

template <typename OutputIterator, typename T>
OutputIterator iota_n ( OutputIterator out, T value, std::size_t n )
{
    while ( n-- > 0 )
        *out++ = value++;

    return out;
}

template <typename InputIterator, typename Size, typename OutputIterator>
OutputIterator copy_n ( InputIterator first, Size n, OutputIterator result )
{
    for ( ; n > 0; --n, ++first, ++result )
        *result = *first;
    return result;
}

        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT erase_range_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<RangeT>::type>& SearchRange )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT>
        inline void erase_range( 
            SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_iterator<SequenceT>::type>& SearchRange )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_first_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void erase_first( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void ierase_first( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_last_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void erase_last( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void ierase_last( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_nth_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            int Nth )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void erase_nth( 
            SequenceT& Input,
            const RangeT& Search,
            int Nth )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void ierase_nth( 
            SequenceT& Input,
            const RangeT& Search,
            int Nth,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }
  
        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_all_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void erase_all( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<typename SequenceT, typename RangeT>
        inline void ierase_all( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        template<
            typename OutputIteratorT,
            typename RangeT>
        inline OutputIteratorT erase_head_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<typename SequenceT>
        inline SequenceT erase_head_copy( 
            const SequenceT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<typename SequenceT>
        inline void erase_head( 
            SequenceT& Input,
            int N )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<
            typename OutputIteratorT,
            typename RangeT>
        inline OutputIteratorT erase_tail_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<typename SequenceT>
        inline SequenceT erase_tail_copy( 
            const SequenceT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<typename SequenceT>
        inline void erase_tail( 
            SequenceT& Input,
            int N )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_left_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));

            std::copy( 
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace ),
                ::boost::end(lit_range),
                Output);

            return Output;
        }

        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_left_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return SequenceT( 
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace ),
                ::boost::end(Input));
        }

        template<typename SequenceT>
        inline SequenceT trim_left_copy(const SequenceT& Input, const std::locale& Loc=std::locale())
        {
            return            
                ::boost::algorithm::trim_left_copy_if(
                    Input, 
                    is_space(Loc));
        }

        template<typename SequenceT, typename PredicateT>
        inline void trim_left_if(SequenceT& Input, PredicateT IsSpace)
        {
            Input.erase( 
                ::boost::begin(Input),
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace));
        }

        template<typename SequenceT>
        inline void trim_left(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_left_if( 
                Input, 
                is_space(Loc));
        }

        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_right_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace )
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));
         
            std::copy( 
                ::boost::begin(lit_range),
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace ),
                Output );

            return Output;
        }

        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_right_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return SequenceT( 
                ::boost::begin(Input),
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace)
                );
        }

        template<typename SequenceT>
        inline SequenceT trim_right_copy(const SequenceT& Input, const std::locale& Loc=std::locale())
        {
            return 
                ::boost::algorithm::trim_right_copy_if( 
                    Input, 
                    is_space(Loc));
        }

        template<typename SequenceT, typename PredicateT>
        inline void trim_right_if(SequenceT& Input, PredicateT IsSpace)
        {
            Input.erase(
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace ),
                ::boost::end(Input)
                );
        }

        template<typename SequenceT>
        inline void trim_right(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_right_if(
                Input, 
                is_space(Loc) );
        }

        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));

            BOOST_STRING_TYPENAME 
                range_const_iterator<RangeT>::type TrimEnd=
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace);

            std::copy( 
                detail::trim_begin( 
                    ::boost::begin(lit_range), TrimEnd, IsSpace),
                TrimEnd,
                Output
                );

            return Output;
        }

        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            BOOST_STRING_TYPENAME 
                range_const_iterator<SequenceT>::type TrimEnd=
                    ::boost::algorithm::detail::trim_end( 
                        ::boost::begin(Input), 
                        ::boost::end(Input), 
                        IsSpace);

            return SequenceT( 
                detail::trim_begin( 
                    ::boost::begin(Input), 
                    TrimEnd, 
                    IsSpace),
                TrimEnd
                );
        }

        template<typename SequenceT>
        inline SequenceT trim_copy( const SequenceT& Input, const std::locale& Loc=std::locale() )
        {
            return
                ::boost::algorithm::trim_copy_if(
                    Input, 
                    is_space(Loc) );
        }

        template<typename SequenceT, typename PredicateT>
        inline void trim_if(SequenceT& Input, PredicateT IsSpace)
        {
            ::boost::algorithm::trim_right_if( Input, IsSpace );
            ::boost::algorithm::trim_left_if( Input, IsSpace );
        }

        template<typename SequenceT>
        inline void trim(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_if(
                Input, 
                is_space( Loc ) );
        }

            void constraints()
            {
                // Operation
                r=(*pF)(i,i);
            }

            void constraints()
            {
                // Operation
                ::boost::begin((*pFo)( (*pF)(i,i) ));
                ::boost::end((*pFo)( (*pF)(i,i) ));
            }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_range_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<Range1T>::type>& SearchRange,
            const Range2T& Format)
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::const_formatter(Format));
        }

        template<typename SequenceT, typename RangeT>
        inline void replace_range( 
            SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_iterator<SequenceT>::type>& SearchRange,
            const RangeT& Format)
        {
            ::boost::algorithm::find_format(
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::const_formatter(Format));
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format)
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_first_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_first( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_first( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_last_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_last( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_last( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_nth_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_nth( 
            SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc) ),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_nth( 
            SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_all_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_all( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_all( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_head_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            int N,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT replace_head_copy( 
            const SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename RangeT>
        inline void replace_head( 
            SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_tail_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            int N,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT replace_tail_copy( 
            const SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        template<typename SequenceT, typename RangeT>
        inline void replace_tail( 
            SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }
 
        join_if(
            const SequenceSequenceT& Input,
            const Range1T& Separator,
            PredicateT Pred)
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;

            // Roll to the first element that will be added
            while(itBegin!=itEnd && !Pred(*itBegin)) ++itBegin;
            // Add this element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                if(Pred(*itBegin))
                {
                    // Add separator
                    detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                    // Add element
                    detail::insert(Result, ::boost::end(Result), *itBegin);
                }
            }

            return Result;
        }

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1==Arg2;
            }

            is_iequal( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)==std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)==std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1<Arg2;
            }

            is_iless( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)<std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)<std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                return Arg1<=Arg2;
            }

            is_not_igreater( const std::locale& Loc=std::locale() ) :
                m_Loc( Loc ) {}

            template< typename T1, typename T2 >
                bool operator()( const T1& Arg1, const T2& Arg2 ) const
            {
                #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                    return std::toupper(Arg1)<=std::toupper(Arg2);
                #else
                    return std::toupper<T1>(Arg1,m_Loc)<=std::toupper<T2>(Arg2,m_Loc);
                #endif
            }

        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
            Range1T& Input,
            const Range2T& Search)
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search) );        
        }

        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
            Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc) ) );        
        }

        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
            RangeT& Input,
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::token_finder( Pred, eCompress ) );         
        }

        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_copy_impl(
                Output,
                lit_input,
                Formatter,
                Finder( ::boost::begin(lit_input), ::boost::end(lit_input) ) );
        }

        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT>
        inline SequenceT find_format_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_copy_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }

        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT>
        inline void find_format( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }

        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_all_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT(( 
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_all_copy_impl(
                Output,
                lit_input,
                Finder,
                Formatter,
                Finder(::boost::begin(lit_input), ::boost::end(lit_input)));
        }

        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT >
        inline SequenceT find_format_all_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_all_copy_impl(
                Input,
                Finder,
                Formatter,
                Finder( ::boost::begin(Input), ::boost::end(Input) ) );
        }

        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT >
        inline void find_format_all( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_all_impl(
                Input,
                Finder,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));

        }

        template<typename Range1T, typename Range2T, typename PredicateT>
            inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range2T>::type Iterator2T;

            Iterator1T InputEnd=::boost::end(lit_input);
            Iterator2T TestEnd=::boost::end(lit_test);

            Iterator1T it=::boost::begin(lit_input);
            Iterator2T pit=::boost::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return pit==TestEnd;
        }

        template<typename Range1T, typename Range2T>
        inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::starts_with(Input, Test, is_equal());
        }

        template<typename Range1T, typename Range2T>
        inline bool istarts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::starts_with(Input, Test, is_iequal(Loc));
        }

        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME boost::detail::
                iterator_traits<Iterator1T>::iterator_category category;

            return detail::
                ends_with_iter_select( 
                    ::boost::begin(lit_input), 
                    ::boost::end(lit_input), 
                    ::boost::begin(lit_test), 
                    ::boost::end(lit_test), 
                    Comp,
                    category());
        }

        template<typename Range1T, typename Range2T>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::ends_with(Input, Test, is_equal());
        }

        template<typename Range1T, typename Range2T>
        inline bool iends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::ends_with(Input, Test, is_iequal(Loc));
        }

        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            if (::boost::empty(lit_test))
            {
                // Empty range is contained always
                return true;
            }
            
            // Use the temporary variable to make VACPP happy
            bool bResult=(::boost::algorithm::first_finder(lit_test,Comp)(::boost::begin(lit_input), ::boost::end(lit_input)));
            return bResult;
        }

        template<typename Range1T, typename Range2T>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::contains(Input, Test, is_equal());
        }

        template<typename Range1T, typename Range2T>
        inline bool icontains( 
            const Range1T& Input, 
            const Range2T& Test, 
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::contains(Input, Test, is_iequal(Loc));
        }

        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range2T>::type Iterator2T;
                
            Iterator1T InputEnd=::boost::end(lit_input);
            Iterator2T TestEnd=::boost::end(lit_test);

            Iterator1T it=::boost::begin(lit_input);
            Iterator2T pit=::boost::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return  (pit==TestEnd) && (it==InputEnd);
        }

        template<typename Range1T, typename Range2T>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::equals(Input, Test, is_equal());
        }

        template<typename Range1T, typename Range2T>
        inline bool iequals( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::equals(Input, Test, is_iequal(Loc));
        }

        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            PredicateT Pred)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_arg1(::boost::as_literal(Arg1));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_arg2(::boost::as_literal(Arg2));

            return std::lexicographical_compare(
                ::boost::begin(lit_arg1),
                ::boost::end(lit_arg1),
                ::boost::begin(lit_arg2),
                ::boost::end(lit_arg2),
                Pred);
        }

        template<typename Range1T, typename Range2T>
            inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2)
        {
            return ::boost::algorithm::lexicographical_compare(Arg1, Arg2, is_less());
        }

        template<typename Range1T, typename Range2T>
        inline bool ilexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::lexicographical_compare(Arg1, Arg2, is_iless(Loc));
        }

        template<typename RangeT, typename PredicateT>
        inline bool all( 
            const RangeT& Input, 
            PredicateT Pred)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<RangeT>::type Iterator1T;

            Iterator1T InputEnd=::boost::end(lit_input);
            for( Iterator1T It=::boost::begin(lit_input); It!=InputEnd; ++It)
            {
                if (!Pred(*It))
                    return false;
            }
            
            return true;
        }

            find_iterator() {}

            find_iterator( const find_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_End(Other.m_End) {}

            template<typename FinderT>
            find_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_End(End)
            {
                increment();
            }

            template<typename FinderT, typename RangeT>
            find_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0)
            {
                iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_col(::boost::as_literal(Col));
                m_Match=::boost::make_iterator_range(::boost::begin(lit_col), ::boost::begin(lit_col));
                m_End=::boost::end(lit_col);

                increment();
            }

            const match_type& dereference() const
            {
                return m_Match;
            }

            void increment()
            {
                if(m_Match.begin() == m_Match.end())
                    m_Match=this->do_find(m_Match.end(),m_End);
                else {
                    input_iterator_type last = m_Match.begin();
                    m_Match=this->do_find(++last,m_End);
                    }
            }

            bool equal( const find_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_End==Other.m_End 
                    );
            }

            bool eof() const
            {
                return 
                    this->is_null() || 
                    ( 
                        m_Match.begin() == m_End &&
                        m_Match.end() == m_End
                    );
            }

            split_iterator() {}

            split_iterator( const split_iterator& Other ) :
                base_type(Other),
                m_Match(Other.m_Match),
                m_Next(Other.m_Next),
                m_End(Other.m_End),
                m_bEof(Other.m_bEof)
            {}

            template<typename FinderT>
            split_iterator(
                    IteratorT Begin,
                    IteratorT End,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_Match(Begin,Begin),
                m_Next(Begin),
                m_End(End),
                m_bEof(false)
            {
                // force the correct behavior for empty sequences and yield at least one token
                if(Begin!=End)
                {
                    increment();
                }
            }

            template<typename FinderT, typename RangeT>
            split_iterator(
                    RangeT& Col,
                    FinderT Finder ) :
                detail::find_iterator_base<IteratorT>(Finder,0),
                m_bEof(false)
            {
                iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_col(::boost::as_literal(Col));
                m_Match=make_iterator_range(::boost::begin(lit_col), ::boost::begin(lit_col));
                m_Next=::boost::begin(lit_col);
                m_End=::boost::end(lit_col);

                // force the correct behavior for empty sequences and yield at least one token
                if(m_Next!=m_End)
                {
                    increment();
                }
            }

            const match_type& dereference() const
            {
                return m_Match;
            }

            void increment()
            {
                match_type FindMatch=this->do_find( m_Next, m_End );

                if(FindMatch.begin()==m_End && FindMatch.end()==m_End)
                {
                    if(m_Match.end()==m_End)
                    {
                        // Mark iterator as eof
                        m_bEof=true;
                    }
                }

                m_Match=match_type( m_Next, FindMatch.begin() );
                m_Next=FindMatch.end();
            }

            bool equal( const split_iterator& Other ) const
            {
                bool bEof=eof();
                bool bOtherEof=Other.eof();

                return bEof || bOtherEof ? bEof==bOtherEof :
                    (
                        m_Match==Other.m_Match &&
                        m_Next==Other.m_Next &&
                        m_End==Other.m_End
                    );
            }

            bool eof() const
            {
                return this->is_null() || m_bEof;
            }

        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_find(
            SequenceSequenceT& Result,
            RangeT& Input,
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef find_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type());
            
            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type());

            SequenceSequenceT Tmp(itBegin, itEnd);
                        
            Result.swap(Tmp);
            return Result;
        }

        template< 
            typename SequenceSequenceT,
            typename RangeT,
            typename FinderT >
        inline SequenceSequenceT&
        iter_split(
            SequenceSequenceT& Result,
            RangeT& Input,
            FinderT Finder )
        {
            BOOST_CONCEPT_ASSERT((
                FinderConcept<FinderT,
                BOOST_STRING_TYPENAME range_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_iterator<RangeT>::type input_iterator_type;
            typedef split_iterator<input_iterator_type> find_iterator_type;
            typedef detail::copy_iterator_rangeF<
                BOOST_STRING_TYPENAME 
                    range_value<SequenceSequenceT>::type,
                input_iterator_type> copy_range_type;
            
            input_iterator_type InputEnd=::boost::end(lit_input);

            typedef transform_iterator<copy_range_type, find_iterator_type>
                transform_iter_type;
    
            transform_iter_type itBegin=
                ::boost::make_transform_iterator( 
                    find_iterator_type( ::boost::begin(lit_input), InputEnd, Finder ),
                    copy_range_type() );

            transform_iter_type itEnd=
                ::boost::make_transform_iterator( 
                    find_iterator_type(),
                    copy_range_type() );
            
            SequenceSequenceT Tmp(itBegin, itEnd);

            Result.swap(Tmp);
            return Result;
        }

        inline detail::is_classifiedF
        is_classified(std::ctype_base::mask Type, const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(Type, Loc);
        }

        inline detail::is_classifiedF 
        is_space(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::space, Loc);
        }

        inline detail::is_classifiedF 
        is_alnum(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::alnum, Loc);
        }

        inline detail::is_classifiedF 
        is_alpha(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::alpha, Loc);
        }

        inline detail::is_classifiedF 
        is_cntrl(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::cntrl, Loc);
        }

        inline detail::is_classifiedF 
        is_digit(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::digit, Loc);
        }

        inline detail::is_classifiedF
        is_graph(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::graph, Loc);
        }

        inline detail::is_classifiedF 
        is_lower(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::lower, Loc);
        }

        inline detail::is_classifiedF 
        is_print(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::print, Loc);
        }

        inline detail::is_classifiedF 
        is_punct(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::punct, Loc);
        }

        inline detail::is_classifiedF 
        is_upper(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::upper, Loc);
        }

        inline detail::is_classifiedF 
        is_xdigit(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::xdigit, Loc);
        }

        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT 
        to_lower_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy( 
               Output,
               ::boost::as_literal(Input),
               ::boost::algorithm::detail::to_lowerF<
                    typename range_value<RangeT>::type >(Loc));
        }

        template<typename WritableRangeT>
        inline void to_lower( 
            WritableRangeT& Input, 
            const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::detail::transform_range(
                ::boost::as_literal(Input),
                ::boost::algorithm::detail::to_lowerF<
                    typename range_value<WritableRangeT>::type >(Loc));
        }

        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT 
        to_upper_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy( 
               Output,
               ::boost::as_literal(Input),
               ::boost::algorithm::detail::to_upperF<
                    typename range_value<RangeT>::type >(Loc));
        }

        template<typename WritableRangeT>
        inline void to_upper( 
            WritableRangeT& Input, 
            const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::detail::transform_range(
                ::boost::as_literal(Input),
                ::boost::algorithm::detail::to_upperF<
                    typename range_value<WritableRangeT>::type >(Loc));
        }

        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_all_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return 
                ::boost::find_format_all_copy(      
                    ::boost::trim_copy_if(Input, IsSpace),
                    ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                    ::boost::dissect_formatter(::boost::head_finder(1)));
        }

        template<typename SequenceT, typename PredicateT>
        inline void trim_all_if(SequenceT& Input, PredicateT IsSpace)
        {
            ::boost::trim_if(Input, IsSpace);
            ::boost::find_format_all(       
                Input,          
                ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                ::boost::dissect_formatter(::boost::head_finder(1)));
        }

        template<typename SequenceT>
        inline SequenceT trim_all_copy(const SequenceT& Input, const std::locale& Loc =std::locale())
        {
            return trim_all_copy_if(Input, ::boost::is_space(Loc));
        }

        template<typename SequenceT>
        inline void trim_all(SequenceT& Input, const std::locale& Loc =std::locale())
        {
            trim_all_if(Input, ::boost::is_space(Loc));
        }

        template<typename SequenceT, typename RangeT, typename PredicateT>
        inline SequenceT trim_fill_copy_if(const SequenceT& Input, const RangeT& Fill, PredicateT IsSpace)
        {
            return 
                ::boost::find_format_all_copy(      
                    ::boost::trim_copy_if(Input, IsSpace),
                    ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                    ::boost::const_formatter(::boost::as_literal(Fill)));
        }

        template<typename SequenceT, typename RangeT, typename PredicateT>
        inline void trim_fill_if(SequenceT& Input, const RangeT& Fill, PredicateT IsSpace)
        {
            ::boost::trim_if(Input, IsSpace);
            ::boost::find_format_all(       
                Input,          
                ::boost::token_finder(IsSpace, ::boost::token_compress_on),
                ::boost::const_formatter(::boost::as_literal(Fill)));
        }

        template<typename SequenceT, typename RangeT>
        inline SequenceT trim_fill_copy(const SequenceT& Input, const RangeT& Fill, const std::locale& Loc =std::locale())
        {
            return trim_fill_copy_if(Input, Fill, ::boost::is_space(Loc));
        }

        template<typename SequenceT, typename RangeT>
        inline void trim_fill(SequenceT& Input, const RangeT& Fill, const std::locale& Loc =std::locale())
        {
            trim_fill_if(Input, Fill, ::boost::is_space(Loc));
        }


           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_all_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    Output = std::copy( LastMatch, M.begin(), Output );
                    // Copy formatted result
                    Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                Output = std::copy( LastMatch, ::boost::end(Input), Output );

                return Output;
            }


            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_all_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2( 
                        Output,
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }


           template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_all_copy_impl2(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Output temporary
                InputT Output;

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, M.begin() );
                    // Copy formatted result
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                ::boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, ::boost::end(Input) );

                return Output;
            }


            template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_all_copy_impl(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

        
            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_all_impl2( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult,
                FormatResultT FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_iterator<InputT>::type input_iterator_type; 
                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );
          
                // Instantiate replacement storage
                std::deque<
                    BOOST_STRING_TYPENAME range_value<InputT>::type> Storage;

                // Initialize replacement iterators
                input_iterator_type InsertIt=::boost::begin(Input);
                input_iterator_type SearchIt=::boost::begin(Input);
                
                while( M )
                {
                    // process the segment
                    InsertIt=process_segment( 
                        Storage,
                        Input,
                        InsertIt,
                        SearchIt,
                        M.begin() );
                    
                    // Adjust search iterator
                    SearchIt=M.end();

                    // Copy formatted replace to the storage
                    ::boost::algorithm::detail::copy_to_storage( Storage, M.format_result() );

                    // Find range for a next match
                    M=Finder( SearchIt, ::boost::end(Input) );
                }

                // process the last segment
                InsertIt=::boost::algorithm::detail::process_segment( 
                    Storage,
                    Input,
                    InsertIt,
                    SearchIt,
                    ::boost::end(Input) );
                
                if ( Storage.empty() )
                {
                    // Truncate input
                    ::boost::algorithm::detail::erase( Input, InsertIt, ::boost::end(Input) );
                }
                else
                {
                    // Copy remaining data to the end of input
                    ::boost::algorithm::detail::insert( Input, ::boost::end(Input), Storage.begin(), Storage.end() );
                }
            }


            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_all_impl( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_all_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }


            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end_iter_select( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace,
                std::forward_iterator_tag )
            {
                ForwardIteratorT TrimIt=InBegin;

                for( ForwardIteratorT It=InBegin; It!=InEnd; ++It )
                {
                    if ( !IsSpace(*It) ) 
                    {
                        TrimIt=It;
                        ++TrimIt;
                    }
                }

                return TrimIt;
            }

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_begin( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                ForwardIteratorT It=InBegin;
                for(; It!=InEnd; ++It )
                {
                    if (!IsSpace(*It))
                        return It;
                }

                return It;
            }

            template< typename ForwardIteratorT, typename PredicateT >
            inline ForwardIteratorT trim_end( 
                ForwardIteratorT InBegin, 
                ForwardIteratorT InEnd, 
                PredicateT IsSpace )
            {
                typedef BOOST_STRING_TYPENAME boost::detail::
                    iterator_traits<ForwardIteratorT>::iterator_category category;

                return ::boost::algorithm::detail::trim_end_iter_select( InBegin, InEnd, IsSpace, category() );
            }

        
            template< typename InputT, typename ForwardIteratorT >
            inline void insert(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator At,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                Input.insert( At, Begin, End );
            }

            template< typename InputT >
            inline typename InputT::iterator erase(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator From,
                BOOST_STRING_TYPENAME InputT::iterator To )
            {
                return Input.erase( From, To );
            }

                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    // Copy data to the container ( as much as possible )
                    ForwardIteratorT InsertIt=Begin;
                    BOOST_STRING_TYPENAME InputT::iterator InputIt=From;
                    for(; InsertIt!=End && InputIt!=To; InsertIt++, InputIt++ )
                    {
                        *InputIt=*InsertIt;
                    }

                    if ( InsertIt!=End )
                    {
                        // Replace sequence is longer, insert it
                        Input.insert( InputIt, InsertIt, End );
                    }
                    else
                    {
                        if ( InputIt!=To )
                        {
                            // Replace sequence is shorter, erase the rest
                            Input.erase( InputIt, To );
                        }
                    }
                }

                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    BOOST_STRING_TYPENAME InputT::iterator At=Input.erase( From, To );
                    if ( Begin!=End )
                    {
                        if(!Input.empty())
                        {
                            Input.insert( At, Begin, End );
                        }
                        else
                        {
                            Input.insert( Input.begin(), Begin, End );
                        }
                    }
                }

                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End ) 
                {
                    replace_const_time_helper< 
                        boost::mpl::and_<
                            has_const_time_insert<InputT>,
                            has_const_time_erase<InputT> >::value >()(
                        Input, From, To, Begin, End );
                }

                template< typename InputT, typename ForwardIteratorT >
                void operator()(
                    InputT& Input,
                    BOOST_STRING_TYPENAME InputT::iterator From,
                    BOOST_STRING_TYPENAME InputT::iterator To,
                    ForwardIteratorT Begin,
                    ForwardIteratorT End )
                {
                    Input.replace( From, To, Begin, End );
                }

        
            template< typename InputT, typename ForwardIteratorT >
            inline void replace(
                InputT& Input,
                BOOST_STRING_TYPENAME InputT::iterator From,
                BOOST_STRING_TYPENAME InputT::iterator To,
                ForwardIteratorT Begin,
                ForwardIteratorT End )
            {
                replace_native_helper< has_native_replace<InputT>::value >()(
                    Input, From, To, Begin, End );
            }

                template< typename SearchT >
                first_finderF( const SearchT& Search, PredicateT Comp ) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)), m_Comp(Comp) {}

                first_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        PredicateT Comp ) :
                    m_Search(SearchBegin, SearchEnd), m_Comp(Comp) {}

                template< typename SearchT >
                last_finderF( const SearchT& Search, PredicateT Comp ) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)), m_Comp(Comp) {}

                last_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        PredicateT Comp ) :
                    m_Search(SearchBegin, SearchEnd), m_Comp(Comp) {}

                template< typename SearchT >
                nth_finderF(
                        const SearchT& Search,
                        int Nth,
                        PredicateT Comp) :
                    m_Search(::boost::begin(Search), ::boost::end(Search)),
                    m_Nth(Nth),
                    m_Comp(Comp) {}

                nth_finderF(
                        search_iterator_type SearchBegin,
                        search_iterator_type SearchEnd,
                        int Nth,
                        PredicateT Comp) :
                    m_Search(SearchBegin, SearchEnd),
                    m_Nth(Nth),
                    m_Comp(Comp) {}

                tail_finderF( int N ) : m_N(N) {}

                token_finderF(
                    PredicateT Pred,
                    token_compress_mode_type eCompress=token_compress_off ) :
                        m_Pred(Pred), m_eCompress(eCompress) {}

                range_finderF(
                    input_iterator_type Begin,
                    input_iterator_type End ) : m_Range(Begin, End) {}

                const_formatF(const RangeT& Format) :
                    m_Format(::boost::begin(Format), ::boost::end(Format)) {}


                template<typename Range2T>
                const result_type& operator()(const Range2T&) const
                {
                    return m_Format;
                }

                template< typename Range2T >
                const RangeT& operator()(const Range2T& Replace) const
                {
                    return RangeT(::boost::begin(Replace), ::boost::end(Replace));
                }

                dissect_formatF(FinderT Finder) :
                  m_Finder(Finder) {}


           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    Output = std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                    return Output;
                }

                // Copy the beginning of the sequence
                Output = std::copy( ::boost::begin(Input), ::boost::begin(M), Output );
                // Format find result
                // Copy formatted result
                Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );
                // Copy the rest of the sequence
                Output = std::copy( M.end(), ::boost::end(Input), Output );

                return Output;
            }


            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2( 
                        Output,
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }


           template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_copy_impl2(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_const_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Match not found - return original sequence
                    return InputT( Input );
                }

                InputT Output;
                // Copy the beginning of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), ::boost::begin(Input), M.begin() );
                // Copy formatted result
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );
                // Copy the rest of the sequence
                boost::algorithm::detail::insert( Output, ::boost::end(Output), M.end(), ::boost::end(Input) );

                return Output;
            }


            template< 
                typename InputT, 
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_copy_impl(
                const InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_copy_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

        
            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_impl2( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef find_format_store<
                    BOOST_STRING_TYPENAME 
                        range_iterator<InputT>::type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                if ( !M )
                {
                    // Search not found - return original sequence
                    return;
                }

                // Replace match
                ::boost::algorithm::detail::replace( Input, M.begin(), M.end(), M.format_result() );
            }


            template<
                typename InputT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_impl( 
                InputT& Input,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_impl2(
                        Input,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }


            template< 
                typename ForwardIterator1T, 
                typename ForwardIterator2T,
                typename PredicateT>
            inline bool ends_with_iter_select( 
                ForwardIterator1T Begin, 
                ForwardIterator1T End, 
                ForwardIterator2T SubBegin,
                ForwardIterator2T SubEnd,
                PredicateT Comp,
                std::bidirectional_iterator_tag)
            {
                ForwardIterator1T it=End;
                ForwardIterator2T pit=SubEnd;
                for(;it!=Begin && pit!=SubBegin;)
                {
                    if( !(Comp(*(--it),*(--pit))) )
                        return false;
                }

                return pit==SubBegin;
            }

                regex_search_result( const match_results_type& MatchResults ) :
                    base_type( MatchResults[0].first, MatchResults[0].second ),
                    m_MatchResults( MatchResults ) {}

                regex_search_result( IteratorT End ) :
                    base_type( End, End ) {}


                regex_search_result( const regex_search_result& Other ) :
                    base_type( Other.begin(), Other.end() ),
                    m_MatchResults( Other.m_MatchResults ) {}

                regex_search_result& operator=( const regex_search_result& Other )
                {
                    base_type::operator=( Other );
                    m_MatchResults=Other.m_MatchResults;
                    return *this;
                }

                const match_results_type& match_results() const
                {
                    return m_MatchResults;
                }

                find_regexF( regex_reference_type Rx, match_flag_type MatchFlags = match_default ) : 
                    m_Rx(Rx), m_MatchFlags(MatchFlags) {}

                template< typename ForwardIteratorT >
                regex_search_result<ForwardIteratorT>
                operator()( 
                    ForwardIteratorT Begin, 
                    ForwardIteratorT End ) const
                {
                    typedef ForwardIteratorT input_iterator_type;
                    typedef regex_search_result<ForwardIteratorT> result_type;

                    // instantiate match result
                    match_results<input_iterator_type> result;
                    // search for a match
                    if ( ::boost::regex_search( Begin, End, result, m_Rx, m_MatchFlags ) )
                    {
                        // construct a result
                        return result_type( result );
                    }
                    else
                    {
                        // empty result
                        return result_type( End );
                    }
                }

            
            template< typename StorageT, typename OutputIteratorT >
            inline OutputIteratorT move_from_storage(
                StorageT& Storage,
                OutputIteratorT DestBegin,
                OutputIteratorT DestEnd )
            {
                OutputIteratorT OutputIt=DestBegin;
                
                while( !Storage.empty() && OutputIt!=DestEnd )
                {
                    *OutputIt=Storage.front();
                    Storage.pop_front();
                    ++OutputIt;
                }

                return OutputIt;
            }


            template< typename StorageT, typename WhatT >
            inline void copy_to_storage(
                StorageT& Storage,
                const WhatT& What )
            {
                Storage.insert( Storage.end(), ::boost::begin(What), ::boost::end(What) );
            }

                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& /*Input*/,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )
                {
                    // Copy data from the storage until the beginning of the segment
                    ForwardIteratorT It=::boost::algorithm::detail::move_from_storage( Storage, InsertIt, SegmentBegin );

                    // 3 cases are possible :
                    //   a) Storage is empty, It==SegmentBegin
                    //   b) Storage is empty, It!=SegmentBegin
                    //   c) Storage is not empty

                    if( Storage.empty() )
                    {
                        if( It==SegmentBegin )
                        {
                            // Case a) everything is grand, just return end of segment
                            return SegmentEnd;
                        }
                        else
                        {
                            // Case b) move the segment backwards
                            return std::copy( SegmentBegin, SegmentEnd, It );
                        }
                    }
                    else
                    {
                        // Case c) -> shift the segment to the left and keep the overlap in the storage
                        while( It!=SegmentEnd )
                        {
                            // Store value into storage
                            Storage.push_back( *It );
                            // Get the top from the storage and put it here
                            *It=Storage.front();
                            Storage.pop_front();

                            // Advance
                            ++It;
                        }

                        return It;
                    }
                }

                template< 
                    typename StorageT,
                    typename InputT,
                    typename ForwardIteratorT >
                ForwardIteratorT operator()(
                    StorageT& Storage,
                    InputT& Input,
                    ForwardIteratorT InsertIt,
                    ForwardIteratorT SegmentBegin,
                    ForwardIteratorT SegmentEnd )

                {
                    // Call replace to do the job
                    ::boost::algorithm::detail::replace( Input, InsertIt, SegmentBegin, Storage );
                    // Empty the storage
                    Storage.clear();
                    // Iterators were not changed, simply return the end of segment
                    return SegmentEnd;
                }

            template< 
                typename StorageT,
                typename InputT,
                typename ForwardIteratorT >
            inline ForwardIteratorT process_segment(
                StorageT& Storage,
                InputT& Input,
                ForwardIteratorT InsertIt,
                ForwardIteratorT SegmentBegin,
                ForwardIteratorT SegmentEnd )
            {
                return 
                    process_segment_helper< 
                        has_stable_iterators<InputT>::value>()(
                                Storage, Input, InsertIt, SegmentBegin, SegmentEnd );
            }

                find_iterator_base() {};

                find_iterator_base( const find_iterator_base& Other ) :
                    m_Finder(Other.m_Finder) {}

                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_Finder(Finder) {}

                ~find_iterator_base() {}

                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (!m_Finder.empty())
                    {
                        return m_Finder(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                bool is_null() const
                {
                    return m_Finder.empty();
                }

                is_classifiedF(std::ctype_base::mask Type, std::locale const & Loc = std::locale()) :
                    m_Type(Type), m_Locale(Loc) {}

                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return std::use_facet< std::ctype<CharT> >(m_Locale).is( m_Type, Ch );
                }

                template<typename RangeT>
                is_any_ofF( const RangeT& Range ) : m_Size(0)
                {
                    // Prepare storage
                    m_Storage.m_dynSet=0;

                    std::size_t Size=::boost::distance(Range);
                    m_Size=Size;
                    set_value_type* Storage=0;

                    if(use_fixed_storage(m_Size))
                    {
                        // Use fixed storage
                        Storage=&m_Storage.m_fixSet[0];
                    }
                    else
                    {
                        // Use dynamic storage
                        m_Storage.m_dynSet=new set_value_type[m_Size];
                        Storage=m_Storage.m_dynSet;
                    }

                    // Use fixed storage
                    ::std::copy(::boost::begin(Range), ::boost::end(Range), Storage);
                    ::std::sort(Storage, Storage+m_Size);
                }

                is_any_ofF(const is_any_ofF& Other) : m_Size(Other.m_Size)
                {
                    // Prepare storage
                    m_Storage.m_dynSet=0;               
                    const set_value_type* SrcStorage=0;
                    set_value_type* DestStorage=0;

                    if(use_fixed_storage(m_Size))
                    {
                        // Use fixed storage
                        DestStorage=&m_Storage.m_fixSet[0];
                        SrcStorage=&Other.m_Storage.m_fixSet[0];
                    }
                    else
                    {
                        // Use dynamic storage
                        m_Storage.m_dynSet=new set_value_type[m_Size];
                        DestStorage=m_Storage.m_dynSet;
                        SrcStorage=Other.m_Storage.m_dynSet;
                    }

                    // Use fixed storage
                    ::std::memcpy(DestStorage, SrcStorage, sizeof(set_value_type)*m_Size);
                }

                ~is_any_ofF()
                {
                    if(!use_fixed_storage(m_Size) && m_Storage.m_dynSet!=0)
                    {
                        delete [] m_Storage.m_dynSet;
                    }
                }

                is_any_ofF& operator=(const is_any_ofF& Other)
                {
                    // Handle self assignment
                    if(this==&Other) return *this;

                    // Prepare storage             
                    const set_value_type* SrcStorage;
                    set_value_type* DestStorage;

                    if(use_fixed_storage(Other.m_Size))
                    {
                        // Use fixed storage
                        DestStorage=&m_Storage.m_fixSet[0];
                        SrcStorage=&Other.m_Storage.m_fixSet[0];

                        // Delete old storage if was present
                        if(!use_fixed_storage(m_Size) && m_Storage.m_dynSet!=0)
                        {
                            delete [] m_Storage.m_dynSet;
                        }

                        // Set new size
                        m_Size=Other.m_Size;
                    }
                    else
                    {
                        // Other uses dynamic storage
                        SrcStorage=Other.m_Storage.m_dynSet;

                        // Check what kind of storage are we using right now
                        if(use_fixed_storage(m_Size))
                        {
                            // Using fixed storage, allocate new
                            set_value_type* pTemp=new set_value_type[Other.m_Size];
                            DestStorage=pTemp;
                            m_Storage.m_dynSet=pTemp;
                            m_Size=Other.m_Size;
                        }
                        else
                        {
                            // Using dynamic storage, check if can reuse
                            if(m_Storage.m_dynSet!=0 && m_Size>=Other.m_Size && m_Size<Other.m_Size*2)
                            {
                                // Reuse the current storage
                                DestStorage=m_Storage.m_dynSet;
                                m_Size=Other.m_Size;
                            }
                            else
                            {
                                // Allocate the new one
                                set_value_type* pTemp=new set_value_type[Other.m_Size];
                                DestStorage=pTemp;
                        
                                // Delete old storage if necessary
                                if(m_Storage.m_dynSet!=0)
                                {
                                    delete [] m_Storage.m_dynSet;
                                }
                                // Store the new storage
                                m_Storage.m_dynSet=pTemp;
                                // Set new size
                                m_Size=Other.m_Size;
                            }
                        }
                    }

                    // Copy the data
                    ::std::memcpy(DestStorage, SrcStorage, sizeof(set_value_type)*m_Size);

                    return *this;
                }

                template<typename Char2T>
                bool operator()( Char2T Ch ) const
                {
                    const set_value_type* Storage=
                        (use_fixed_storage(m_Size))
                        ? &m_Storage.m_fixSet[0]
                        : m_Storage.m_dynSet;

                    return ::std::binary_search(Storage, Storage+m_Size, Ch);
                }

                static bool use_fixed_storage(std::size_t size)
                {
                    return size<=sizeof(set_value_type*)*2;
                }

                is_from_rangeF( CharT From, CharT To ) : m_From(From), m_To(To) {}

                template<typename Char2T>
                bool operator()( Char2T Ch ) const
                {
                    return ( m_From <= Ch ) && ( Ch <= m_To );
                }

                pred_andF( Pred1T Pred1, Pred2T Pred2 ) :
                    m_Pred1(Pred1), m_Pred2(Pred2) {}

                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return m_Pred1(Ch) && m_Pred2(Ch);
                }

                pred_orF( Pred1T Pred1, Pred2T Pred2 ) :
                    m_Pred1(Pred1), m_Pred2(Pred2) {}

                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return m_Pred1(Ch) || m_Pred2(Ch);
                }

                pred_notF( PredT Pred ) : m_Pred(Pred) {}

                template<typename CharT>
                bool operator()( CharT Ch ) const
                {
                    return !m_Pred(Ch);
                }

                find_format_store( 
                        const base_type& FindResult,
                        const format_result_type& FormatResult,
                        const formatter_type& Formatter ) :
                    base_type(FindResult),
                    m_FormatResult(FormatResult),
                    m_Formatter(Formatter) {}

                template< typename FindResultT >
                find_format_store& operator=( FindResultT FindResult )
                {
                    iterator_range<ForwardIteratorT>::operator=(FindResult);
                    if( !this->empty() ) {
                        m_FormatResult=m_Formatter(FindResult);
                    }
                    
                    return *this;
                }

                const format_result_type& format_result()
                {   
                    return m_FormatResult;
                }


            template<typename InputT, typename FindResultT>
            bool check_find_result(InputT&, FindResultT& FindResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 
                iterator_range<input_iterator_type> ResultRange(FindResult);
                return !ResultRange.empty();
            }

                to_lowerF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                CharT operator ()( CharT Ch ) const
                {
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::tolower( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::tolower<CharT>( Ch, *m_Loc );
                    #endif
                }

                to_upperF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                CharT operator ()( CharT Ch ) const
                {
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::toupper( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::toupper<CharT>( Ch, *m_Loc );
                    #endif
                }

            template<typename OutputIteratorT, typename RangeT, typename FunctorT>
            OutputIteratorT transform_range_copy(
                OutputIteratorT Output,
                const RangeT& Input,
                FunctorT Functor)
            {
                return std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    Output,
                    Functor);
            }

            template<typename RangeT, typename FunctorT>
            void transform_range(
                const RangeT& Input,
                FunctorT Functor)
            {
                std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    ::boost::begin(Input),
                    Functor);
            }


            template<typename SequenceT, typename RangeT, typename FunctorT>
            inline SequenceT transform_range_copy( 
                const RangeT& Input, 
                FunctorT Functor)
            {
                return SequenceT(
                    ::boost::make_transform_iterator(
                        ::boost::begin(Input),
                        Functor),
                    ::boost::make_transform_iterator(
                        ::boost::end(Input), 
                        Functor));
            }

                regex_formatF( const StringT& Fmt, match_flag_type Flags=format_default ) :
                    m_Fmt(Fmt), m_Flags( Flags ) {}


                template<typename InputIteratorT>
                result_type operator()( 
                    const regex_search_result<InputIteratorT>& Replace ) const
                {
                    if ( Replace.empty() )
                    {
                        return result_type();
                    }
                    else
                    {
                        return Replace.match_results().format( m_Fmt, m_Flags );                      
                    }
                }

                const_iterator begin() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }


                const_iterator end() const
                {
                    return reinterpret_cast<const_iterator>(0);
                }


                bool empty() const
                {
                    return false;
                }


                size_type size() const
                {
                    return 0;
                }

            template<typename InputIteratorT, typename OutputIteratorT>
            inline OutputIteratorT bounded_copy(
                InputIteratorT First, 
                InputIteratorT Last, 
                OutputIteratorT DestFirst,
                OutputIteratorT DestLast )
            {
                InputIteratorT InputIt=First;
                OutputIteratorT OutputIt=DestFirst;
                for(; InputIt!=Last && OutputIt!=DestLast; InputIt++, OutputIt++ )
                {
                    *OutputIt=*InputIt;
                }

                return OutputIt;
            }

		bool operator () ( const T1& v1, const T2& v2 ) const { return v1 == v2 ;}

	

	template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
	bool is_permutation ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
				 RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
				 std::random_access_iterator_tag, std::random_access_iterator_tag )
	{
	//	Random-access iterators let is check the sizes in constant time
		if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
			return false;
	// If we know that the sequences are the same size, the original version is fine
		return std::is_permutation ( first1, last1, first2, pred );
	}



template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
bool is_permutation (
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2, 
			BinaryPredicate pred )
{
	return boost::algorithm::detail::is_permutation ( 
		first1, last1, first2, last2, pred,
		typename std::iterator_traits<ForwardIterator1>::iterator_category (),
		typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}


template<class ForwardIterator1, class ForwardIterator2>
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
					  ForwardIterator2 first2, ForwardIterator2 last2 )
{
    typedef typename iterator_traits<_ForwardIterator1>::value_type value1_t;
    typedef typename iterator_traits<_ForwardIterator2>::value_type value2_t;
    return boost::algorithm::detail::is_permutation ( 
    		first1, last1, first2, last2, 
      		boost::algorithm::detail::is_perm_eq<
				typename std::iterator_traits<InputIterator1>::value_type,
				typename std::iterator_traits<InputIterator2>::value_type> (),
			typename std::iterator_traits<ForwardIterator1>::iterator_category (),
			typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

		bool operator () ( const T1& v1, const T2& v2 ) const { return v1 == v2 ;}

	
	template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
	bool equal ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
				 RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
				 std::random_access_iterator_tag, std::random_access_iterator_tag )
	{
	//	Random-access iterators let is check the sizes in constant time
		if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
			return false;
	// If we know that the sequences are the same size, the original version is fine
		return std::equal ( first1, last1, first2, pred );
	}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred )
{
	return boost::algorithm::detail::equal ( 
		first1, last1, first2, last2, pred,
		typename std::iterator_traits<InputIterator1>::iterator_category (),
		typename std::iterator_traits<InputIterator2>::iterator_category ());
}

template <class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2 )
{
	return boost::algorithm::detail::equal (
		first1, last1, first2, last2,
		boost::algorithm::detail::eq<
			typename std::iterator_traits<InputIterator1>::value_type,
			typename std::iterator_traits<InputIterator2>::value_type> (),
		typename std::iterator_traits<InputIterator1>::iterator_category (),
		typename std::iterator_traits<InputIterator2>::iterator_category ());
}

    template <typename patIter, typename corpusIter>
    corpusIter boyer_moore_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        boyer_moore<patIter> bm ( pat_first, pat_last );
        return bm ( corpus_first, corpus_last );
    }


    template <typename PatternRange, typename corpusIter>
    corpusIter boyer_moore_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore<pattern_iterator> bm ( boost::begin(pattern), boost::end (pattern));
        return bm ( corpus_first, corpus_last );
    }

    template <typename patIter, typename corpusIter>
    corpusIter boyer_moore_horspool_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        boyer_moore_horspool<patIter> bmh ( pat_first, pat_last );
        return bmh ( corpus_first, corpus_last );
    }


    template <typename PatternRange, typename corpusIter>
    corpusIter boyer_moore_horspool_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        boyer_moore_horspool<pattern_iterator> bmh ( boost::begin(pattern), boost::end (pattern));
        return bmh ( corpus_first, corpus_last );
    }

        knuth_morris_pratt ( patIter first, patIter last ) 
                : pat_first ( first ), pat_last ( last ), 
                  k_pattern_length ( std::distance ( pat_first, pat_last )),
                  skip_ ( k_pattern_length + 1 ) {
#ifdef NEW_KMP
            preKmp ( pat_first, pat_last );
#else
            init_skip_table ( pat_first, pat_last );
#endif
#ifdef BOOST_ALGORITHM_KNUTH_MORRIS_PRATT_DEBUG
            detail::PrintTable ( skip_.begin (), skip_.end ());
#endif
            }

            
        ~knuth_morris_pratt () {}

        template <typename corpusIter>
        corpusIter operator () ( corpusIter corpus_first, corpusIter corpus_last ) const {
            BOOST_STATIC_ASSERT (( boost::is_same<
                typename std::iterator_traits<patIter>::value_type, 
                typename std::iterator_traits<corpusIter>::value_type>::value ));
            if ( corpus_first == corpus_last ) return corpus_last;  // if nothing to search, we didn't find it!
            if ( pat_first == pat_last )       return corpus_first; // empty pattern matches at start

            const difference_type k_corpus_length = std::distance ( corpus_first, corpus_last );
        //  If the pattern is larger than the corpus, we can't find it!
            if ( k_corpus_length < k_pattern_length ) 
                return corpus_last;

            return do_search   ( corpus_first, corpus_last, k_corpus_length );
            }

        template <typename corpusIter>
        corpusIter do_search ( corpusIter corpus_first, corpusIter corpus_last, 
                                                difference_type k_corpus_length ) const {
            difference_type match_start = 0;  // position in the corpus that we're matching
            
#ifdef NEW_KMP
            int patternIdx = 0;
            while ( match_start < k_corpus_length ) {
                while ( patternIdx > -1 && pat_first[patternIdx] != corpus_first [match_start] )
                    patternIdx = skip_ [patternIdx]; //<--- Shifting the pattern on mismatch

                patternIdx++;
                match_start++; //<--- corpus is always increased by 1

                if ( patternIdx >= (int) k_pattern_length )
                    return corpus_first + match_start - patternIdx;
                }
            
#else
//  At this point, we know:
//          k_pattern_length <= k_corpus_length
//          for all elements of skip, it holds -1 .. k_pattern_length
//      
//          In the loop, we have the following invariants
//              idx is in the range 0 .. k_pattern_length
//              match_start is in the range 0 .. k_corpus_length - k_pattern_length + 1

            const difference_type last_match = k_corpus_length - k_pattern_length;
            difference_type idx = 0;          // position in the pattern we're comparing

            while ( match_start <= last_match ) {
                while ( pat_first [ idx ] == corpus_first [ match_start + idx ] ) {
                    if ( ++idx == k_pattern_length )
                        return corpus_first + match_start;
                    }
            //  Figure out where to start searching again
           //   assert ( idx - skip_ [ idx ] > 0 ); // we're always moving forward
                match_start += idx - skip_ [ idx ];
                idx = skip_ [ idx ] >= 0 ? skip_ [ idx ] : 0;
           //   assert ( idx >= 0 && idx < k_pattern_length );
                }
#endif
                
        //  We didn't find anything
            return corpus_last;
            }

    

        void preKmp ( patIter first, patIter last ) {
           const /*std::size_t*/ int count = std::distance ( first, last );
        
           int i, j;
        
           i = 0;
           j = skip_[0] = -1;
           while (i < count) {
              while (j > -1 && first[i] != first[j])
                 j = skip_[j];
              i++;
              j++;
              if (first[i] == first[j])
                 skip_[i] = skip_[j];
              else
                 skip_[i] = j;
           }
        }



        void init_skip_table ( patIter first, patIter last ) {
            const difference_type count = std::distance ( first, last );
    
            int j;
            skip_ [ 0 ] = -1;
            for ( int i = 1; i <= count; ++i ) {
                j = skip_ [ i - 1 ];
                while ( j >= 0 ) {
                    if ( first [ j ] == first [ i - 1 ] )
                        break;
                    j = skip_ [ j ];
                    }
                skip_ [ i ] = j + 1;
                }
            }

    template <typename patIter, typename corpusIter>
    corpusIter knuth_morris_pratt_search ( 
                  corpusIter corpus_first, corpusIter corpus_last, 
                  patIter pat_first, patIter pat_last )
    {
        knuth_morris_pratt<patIter> kmp ( pat_first, pat_last );
        return kmp ( corpus_first, corpus_last );
    }


    template <typename PatternRange, typename corpusIter>
    corpusIter knuth_morris_pratt_search ( 
        corpusIter corpus_first, corpusIter corpus_last, const PatternRange &pattern )
    {
        typedef typename boost::range_iterator<const PatternRange>::type pattern_iterator;
        knuth_morris_pratt<pattern_iterator> kmp ( boost::begin(pattern), boost::end (pattern));
        return kmp ( corpus_first, corpus_last );
    }

    template <typename Iter>
    void PrintTable ( Iter first, Iter last ) {
        std::cout << std::distance ( first, last ) << ": { ";
        for ( Iter iter = first; iter != last; ++iter )
            std::cout << *iter << " ";
        std::cout << "}" << std::endl;
        }

        skip_table ( std::size_t patSize, value_type default_value ) 
            : k_default_value ( default_value ), skip_ ( patSize ) {}

        
        void insert ( key_type key, value_type val ) {
            skip_ [ key ] = val;    // Would skip_.insert (val) be better here?
            }


        value_type operator [] ( key_type key ) const {
            typename skip_map::const_iterator it = skip_.find ( key );
            return it == skip_.end () ? k_default_value : it->second;
            }

            
        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <unordered_map>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( it->second != k_default_value )
                    std::cout << "  " << it->first << ": " << it->second << std::endl;
            std::cout << std::endl;
            }

        skip_table ( std::size_t patSize, value_type default_value ) : k_default_value ( default_value ) {
            std::fill_n ( skip_.begin(), skip_.size(), default_value );
            }

        
        void insert ( key_type key, value_type val ) {
            skip_ [ static_cast<unsigned_key_type> ( key ) ] = val;
            }


        value_type operator [] ( key_type key ) const {
            return skip_ [ static_cast<unsigned_key_type> ( key ) ];
            }


        void PrintSkipTable () const {
            std::cout << "BM(H) Skip Table <boost:array>:" << std::endl;
            for ( typename skip_map::const_iterator it = skip_.begin (); it != skip_.end (); ++it )
                if ( *it != k_default_value )
                    std::cout << "  " << std::distance (skip_.begin (), it) << ": " << *it << std::endl;
            std::cout << std::endl;
            }
