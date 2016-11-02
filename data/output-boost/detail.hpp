
   template <typename T>
   inline void cp_swap(T& t1, T& t2)
   {
#ifndef __GNUC__
      using std::swap;
#endif
      swap(t1, t2);
   }


      compressed_pair_imp() {}


      first_reference       first()       {return first_;}


      second_reference       second()       {return second_;}


      void swap(::boost::compressed_pair<T1, T2>& y)
      {
         cp_swap(first_, y.first());
         cp_swap(second_, y.second());
      }


      compressed_pair_imp() {}


      first_reference       first()       {return *this;}


      second_reference       second()       {return second_;}


      void swap(::boost::compressed_pair<T1,T2>& y)
      {
         // no need to swap empty base class:
         cp_swap(second_, y.second());
      }


      compressed_pair_imp() {}


      first_reference       first()       {return first_;}


      second_reference       second()       {return *this;}


      void swap(::boost::compressed_pair<T1,T2>& y)
      {
         // no need to swap empty base class:
         cp_swap(first_, y.first());
      }


      compressed_pair_imp() {}


      first_reference       first()       {return *this;}


      second_reference       second()       {return *this;}

      void swap(::boost::compressed_pair<T1,T2>&) {}


      compressed_pair_imp() {}


      first_reference       first()       {return *this;}


      second_reference       second()       {return m_second;}


      void swap(::boost::compressed_pair<T1,T2>&) {}


      compressed_pair_imp() {}


      first_reference       first()       {return first_;}


      second_reference       second()       {return second_;}


      void swap(::boost::compressed_pair<T1, T2>& y)
      {
         cp_swap(first_, y.first());
         cp_swap(second_, y.second());
      }


            compressed_pair() : base() {}


   first_reference       first()       {return base::first();}


   second_reference       second()       {return base::second();}


   void swap(compressed_pair& y) { base::swap(y); }


            compressed_pair() : base() {}


   first_reference       first()       {return base::first();}


   second_reference       second()       {return base::second();}


   void swap(::boost::compressed_pair<T,T>& y) { base::swap(y); }


template <class T1, class T2>
inline
void
swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}


template<typename T> 
struct is_incrementable 
BOOST_TT_AUX_BOOL_C_BASE(::boost::detail::is_incrementable_::impl<T>::value)
{ 
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(::boost::detail::is_incrementable_::impl<T>::value)
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_incrementable,(T))
};


template<typename T> 
struct is_postfix_incrementable 
BOOST_TT_AUX_BOOL_C_BASE(::boost::detail::is_incrementable_::impl<T>::value)
{ 
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(::boost::detail::is_incrementable_::postfix_impl<T>::value)
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_postfix_incrementable,(T))
};


template<class Iterator, class Comp>
inline Iterator is_sorted_until (Iterator first, Iterator last, Comp c) {
  if (first == last)
    return last;

  Iterator it = first; ++it;

  for (; it != last; first = it, ++it)
    if (c(*it, *first))
      return it;

  return it;
}


template<class Iterator>
inline Iterator is_sorted_until (Iterator first, Iterator last) {
  typedef typename boost::detail::iterator_traits<Iterator>::value_type
    value_type;

  typedef std::less<value_type> c; 

  return ::boost::detail::is_sorted_until(first, last, c()); 
}


template<class Iterator, class Comp>
inline bool is_sorted (Iterator first, Iterator last, Comp c) {
  return ::boost::detail::is_sorted_until(first, last, c) == last;
}
 

template<class Iterator>
inline bool is_sorted (Iterator first, Iterator last) {
  return ::boost::detail::is_sorted_until(first, last) == last;
}


            compressed_pair() : _first(), _second() {}


   first_reference       first()       { return _first; }


   second_reference       second()       { return _second; }


   void swap(compressed_pair& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }


template <class T1, class T2>
inline void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}


  template <class Number>
  typename numeric_traits<Number>::difference_type numeric_distance(Number x, Number y)
  {
      typedef typename numeric_traits<Number>::difference_type difference_type;
      return difference_type(y) - difference_type(x);
  }


    ~reference_content()
    {
    }


    reference_content(RefT r)
        : content_( r )
    {
    }


    reference_content(const reference_content& operand)
        : content_( operand.content_ )
    {
    }


    RefT get() const
    {
        return content_;
    }


      const value_type value() const           { return m_value; }

      void  assign( value_type v )             { m_value = v; }


      bool operator==( const D & rhs ) const   { return m_value == rhs.m_value; }

      bool operator!=( const D & rhs ) const   { return m_value != rhs.m_value; }

      bool operator< ( const D & rhs ) const   { return m_value <  rhs.m_value; }

      bool operator<=( const D & rhs ) const   { return m_value <= rhs.m_value; }

      bool operator> ( const D & rhs ) const   { return m_value >  rhs.m_value; }

      bool operator>=( const D & rhs ) const   { return m_value >= rhs.m_value; }

      static void unspecified_bool_true(D){}


      operator unspecified_bool_type() const   { return m_value == value_type() ? 0 : unspecified_bool_true; }

      bool operator!() const                   { return m_value == value_type(); }

      identifier()                             {}

      explicit identifier( value_type v )      : m_value(v) {}


  partial_std_allocator_wrapper(){};


  template<typename Other>
  partial_std_allocator_wrapper(const partial_std_allocator_wrapper<Other>&){}


template<typename Type>
void construct(void* p,const Type& t)
{
  new (p) Type(t);
}


template<typename Type>
void destroy(const Type* p)
{

#if BOOST_WORKAROUND(__SUNPRO_CC,BOOST_TESTED_AT(0x590))
  const_cast<Type*>(p)->~Type();
#else
  p->~Type();
#endif

}


  template <typename InputIterator, typename Predicate>
  bool any_if(InputIterator first, InputIterator last, Predicate p)
  {
    return std::find_if(first, last, p) != last;
  }


  template <typename Container, typename Predicate>
  bool any_if(const Container& c, Predicate p)
  {
    return any_if(boost::begin(c), boost::end(c), p);
  }


  template <typename InputIterator, typename T>
  bool container_contains(InputIterator first, InputIterator last, T value)
  {
    return std::find(first, last, value) != last;
  }

  template <typename Container, typename T>
  bool container_contains(const Container& c, const T& value)
  {
    return container_contains(boost::begin(c), boost::end(c), value);
  }


int main(int argc, char* argv[])
{
  try
  {
    return cpp_main(argc, argv);
  }

  catch (const std::exception& ex)
  {
    std::cout
    << "\nERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR\n"
    << "\n****************************** std::exception *****************************\n"
    << ex.what()
    << "\n***************************************************************************\n"
    << std::endl;
  }
  return 1;

  report_errors_reminder() : called_report_errors_function(false) {}

 ~report_errors_reminder()
  {
    BOOST_ASSERT(called_report_errors_function);  // verify report_errors() was called  
  }


inline report_errors_reminder& report_errors_remind()
{
  static report_errors_reminder r;
  return r;
}


inline int & test_errors()
{
    static int x = 0;
    report_errors_remind();
    return x;
}


inline void test_failed_impl(char const * expr, char const * file, int line, char const * function)
{
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
      << file << "(" << line << "): test '" << expr << "' failed in function '"
      << function << "'" << std::endl;
    ++test_errors();
}


inline void error_impl(char const * msg, char const * file, int line, char const * function)
{
    BOOST_LIGHTWEIGHT_TEST_OSTREAM
      << file << "(" << line << "): " << msg << " in function '"
      << function << "'" << std::endl;
    ++test_errors();
}


inline void throw_failed_impl(char const * excep, char const * file, int line, char const * function)
{
   BOOST_LIGHTWEIGHT_TEST_OSTREAM
    << file << "(" << line << "): Exception '" << excep << "' not thrown in function '"
    << function << "'" << std::endl;
   ++test_errors();
}


template<class T, class U> inline void test_eq_impl( char const * expr1, char const * expr2,
  char const * file, int line, char const * function, T const & t, U const & u )
{
    if( t == u )
    {
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " == " << expr2
            << "' failed in function '" << function << "': "
            << "'" << t << "' != '" << u << "'" << std::endl;
        ++test_errors();
    }
}


template<class T, class U> inline void test_ne_impl( char const * expr1, char const * expr2,
  char const * file, int line, char const * function, T const & t, U const & u )
{
    if( t != u )
    {
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
            << file << "(" << line << "): test '" << expr1 << " != " << expr2
            << "' failed in function '" << function << "': "
            << "'" << t << "' == '" << u << "'" << std::endl;
        ++test_errors();
    }
}


inline int report_errors()
{
    detail::report_errors_remind().called_report_errors_function = true;

    int errors = detail::test_errors();

    if( errors == 0 )
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
          << "No errors detected." << std::endl;
        return 0;
    }
    else
    {
        BOOST_LIGHTWEIGHT_TEST_OSTREAM
          << errors << " error" << (errors == 1? "": "s") << " detected." << std::endl;
        return 1;
    }
}


int pthread_create( pthread_t * thread, void const *, unsigned (__stdcall * start_routine) (void*), void* arg )
{
    HANDLE h = (HANDLE)_beginthreadex( 0, 0, start_routine, arg, 0, 0 );

    if( h != 0 )
    {
        *thread = h;
        return 0;
    }
    else
    {
        return EAGAIN;
    }
}


int pthread_join( pthread_t thread, void ** /*value_ptr*/ )
{
    ::WaitForSingleObject( thread, INFINITE );
    ::CloseHandle( thread );
    return 0;
}


    virtual ~lw_abstract_thread() {}


unsigned __stdcall lw_thread_routine( void * pv )
{
    std::auto_ptr<lw_abstract_thread> pt( static_cast<lw_abstract_thread *>( pv ) );

    pt->run();

    return 0;
}


    explicit lw_thread_impl( F f ): f_( f )
    {
    }


    void run()
    {
        f_();
    }


template<class F> int lw_thread_create( pthread_t & pt, F f )
{
    std::auto_ptr<lw_abstract_thread> p( new lw_thread_impl<F>( f ) );

    int r = pthread_create( &pt, 0, lw_thread_routine, p.get() );

    if( r == 0 )
    {
        p.release();
    }

    return r;
}


template<class T>
inline std::streamsize lcast_get_precision(T* = 0)
{
#ifndef BOOST_LCAST_NO_COMPILE_TIME_PRECISION
    return lcast_precision<T>::value;
#else // Follow lcast_precision algorithm at run-time:

#ifdef BOOST_NO_IS_ABSTRACT
    typedef std::numeric_limits<T> limits; // No fix for SF:1358600.
#else
    typedef BOOST_DEDUCED_TYPENAME boost::mpl::if_<
        boost::is_abstract<T>
      , std::numeric_limits<lcast_abstract_stub>
      , std::numeric_limits<T>
      >::type limits;
#endif

    bool const use_default_precision =
        !limits::is_specialized || limits::is_exact;

    if(!use_default_precision)
    { // Includes all built-in floating-point types, float, double ...
      // and UDT types for which digits (significand bits) is defined (not zero)

        bool const is_specialized_bin =
            limits::radix == 2 && limits::digits > 0;
        bool const is_specialized_dec =
            limits::radix == 10 && limits::digits10 > 0;
        std::streamsize const streamsize_max =
            (boost::integer_traits<std::streamsize>::max)();

        if(is_specialized_bin)
        { // Floating-point types with
          // limits::digits defined by the specialization.

            unsigned long const digits = limits::digits;
            unsigned long const precision = 2UL + digits * 30103UL / 100000UL;
            // unsigned long is selected because it is at least 32-bits
            // and thus ULONG_MAX / 30103UL is big enough for all types.
            BOOST_ASSERT(
                    digits < ULONG_MAX / 30103UL &&
                    precision > limits::digits10 + 0UL &&
                    precision <= streamsize_max + 0UL
                );
            return precision;
        }
        else if(is_specialized_dec)
        {   // Decimal Floating-point type, most likely a User Defined Type
            // rather than a real floating-point hardware type.
            unsigned int const precision = limits::digits10 + 1U;
            BOOST_ASSERT(precision <= streamsize_max + 0UL);
            return precision;
        }
    }

    // Integral type (for which precision has no effect)
    // or type T for which limits is NOT specialized,
    // so assume stream precision remains the default 6 decimal digits.
    // Warning: if your User-defined Floating-point type T is NOT specialized,
    // then you may lose accuracy by only using 6 decimal digits.
    // To avoid this, you need to specialize T with either
    // radix == 2 and digits == the number of significand bits,
    // OR
    // radix = 10 and digits10 == the number of decimal digits.

    return 6;
#endif
}


template<class T>
inline void lcast_set_precision(std::ios_base& stream, T*)
{
    stream.precision(lcast_get_precision<T>());
}

    template <typename T>
    inline const unsigned char * object_representation (T* p)
    {
        return static_cast<const unsigned char *>(static_cast<const void *>(p));
    }

        static void left_shift(T & v) {
            amount >= width ? (v = 0)
                : (v >>= BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(amount));
        }

        value_to_type() {}


     template <typename Iterator>
     inline std::size_t do_count(Iterator first, std::size_t length,
                                 int /*dummy param*/,
                                 value_to_type<access_by_bytes>* )
     {
         std::size_t num = 0;
         if (length)
         {
             const byte_type * p = object_representation(&*first);
             length *= sizeof(*first);

              do {
                 num += count_table<>::table[*p];
                 ++p;
                 --length;

             } while (length);
         }

         return num;
     }

    template <typename T>
    typename T::size_type vector_max_size_workaround(const T & v) {

      typedef typename T::allocator_type allocator_type;

      const typename allocator_type::size_type alloc_max =
                                                  v.get_allocator().max_size();
      const typename T::size_type container_max = v.max_size();

      return alloc_max < container_max?
                    alloc_max :
                    container_max;
    }


  static __number epsilon() throw()     { return __number(); }

  static __number round_error() throw() { return __number(); }


  static __number infinity() throw()      { return __number(); }

  static __number quiet_NaN() throw()     { return __number(); }

  static __number signaling_NaN() throw() { return __number(); }

  static __number denorm_min() throw()    { return __number(); }

  static Number get_word() throw() {
    // sizeof(long double) == 12, but only 10 bytes significant
    const unsigned int _S_word[4] = { 0, 0, 0, Word };
    return *reinterpret_cast<const Number*>(
        reinterpret_cast<const char *>(&_S_word)+16-
                (sizeof(Number) == 12 ? 10 : sizeof(Number)));
  }


 
  static __number infinity() throw() {
    return float_helper<__number, __InfinityWord>::get_word();
  }

  static __number quiet_NaN() throw() {
    return float_helper<__number,__QNaNWord>::get_word();
  }

  static __number signaling_NaN() throw() {
    return float_helper<__number,__SNaNWord>::get_word();
  }

    inline void report_exception( std::ostream & os, 
                                  const char * name, const char * info )
      { os << "\n** uncaught exception: " << name << " " << info << std::endl; }


  template< class Generator >  // Generator is function object returning int
  int catch_exceptions( Generator function_object,
                        std::ostream & out, std::ostream & err )
  {
    int result = 0;               // quiet compiler warnings
    bool exception_thrown = true; // avoid setting result for each excptn type

#ifndef BOOST_NO_EXCEPTIONS
    try
    {
#endif
      result = function_object();
      exception_thrown = false;
#ifndef BOOST_NO_EXCEPTIONS
    }

    //  As a result of hard experience with strangely interleaved output
    //  under some compilers, there is a lot of use of endl in the code below
    //  where a simple '\n' might appear to do.

    //  The rules for catch & arguments are a bit different from function 
    //  arguments (ISO 15.3 paragraphs 18 & 19). Apparently const isn't
    //  required, but it doesn't hurt and some programmers ask for it.

    catch ( const char * ex )
      { detail::report_exception( out, "", ex ); }
    catch ( const std::string & ex )
      { detail::report_exception( out, "", ex.c_str() ); }

    //  std:: exceptions
    catch ( const std::bad_alloc & ex )
      { detail::report_exception( out, "std::bad_alloc:", ex.what() ); }

# ifndef BOOST_BUILT_IN_EXCEPTIONS_MISSING_WHAT
    catch ( const std::bad_cast & ex )
      { detail::report_exception( out, "std::bad_cast:", ex.what() ); }
    catch ( const std::bad_typeid & ex )
      { detail::report_exception( out, "std::bad_typeid:", ex.what() ); }
# else
    catch ( const std::bad_cast & )
      { detail::report_exception( out, "std::bad_cast", "" ); }
    catch ( const std::bad_typeid & )
      { detail::report_exception( out, "std::bad_typeid", "" ); }
# endif

    catch ( const std::bad_exception & ex )
      { detail::report_exception( out, "std::bad_exception:", ex.what() ); }
    catch ( const std::domain_error & ex )
      { detail::report_exception( out, "std::domain_error:", ex.what() ); }
    catch ( const std::invalid_argument & ex )
      { detail::report_exception( out, "std::invalid_argument:", ex.what() ); }
    catch ( const std::length_error & ex )
      { detail::report_exception( out, "std::length_error:", ex.what() ); }
    catch ( const std::out_of_range & ex )
      { detail::report_exception( out, "std::out_of_range:", ex.what() ); }
    catch ( const std::range_error & ex )
      { detail::report_exception( out, "std::range_error:", ex.what() ); }
    catch ( const std::overflow_error & ex )
      { detail::report_exception( out, "std::overflow_error:", ex.what() ); }
    catch ( const std::underflow_error & ex )
      { detail::report_exception( out, "std::underflow_error:", ex.what() ); }
    catch ( const std::logic_error & ex )
      { detail::report_exception( out, "std::logic_error:", ex.what() ); }
    catch ( const std::runtime_error & ex )
      { detail::report_exception( out, "std::runtime_error:", ex.what() ); }
    catch ( const std::exception & ex )
      { detail::report_exception( out, "std::exception:", ex.what() ); }

    catch ( ... )
      { detail::report_exception( out, "unknown exception", "" ); }
#endif // BOOST_NO_EXCEPTIONS

    if ( exception_thrown ) result = boost::exit_exception_failure;

    if ( result != 0 && result != exit_success )
    {
      out << std::endl << "**** returning with error code "
                << result << std::endl;
      err
        << "**********  errors detected; see stdout for details  ***********"
        << std::endl;
    }
#if !defined(BOOST_NO_CPP_MAIN_SUCCESS_MESSAGE)
    else { out << std::flush << "no errors detected" << std::endl; }
#endif
    return result;
  }


template <class ForwardIter, class Tp>
ForwardIter lower_bound(ForwardIter first, ForwardIter last,
                             const Tp& val) 
{
    typedef detail::iterator_traits<ForwardIter> traits;
    
    typename traits::difference_type len = boost::detail::distance(first, last);
    typename traits::difference_type half;
    ForwardIter middle;

    while (len > 0) {
      half = len >> 1;
      middle = first;
      std::advance(middle, half);
      if (*middle < val) {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else
        len = half;
    }
    return first;
}


template <class ForwardIter, class Tp, class Compare>
ForwardIter lower_bound(ForwardIter first, ForwardIter last,
                              const Tp& val, Compare comp)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (comp(*middle, val)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}


template <class ForwardIter, class Tp>
ForwardIter upper_bound(ForwardIter first, ForwardIter last,
                           const Tp& val)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (val < *middle)
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}


template <class ForwardIter, class Tp, class Compare>
ForwardIter upper_bound(ForwardIter first, ForwardIter last,
                           const Tp& val, Compare comp)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (comp(val, *middle))
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}


  template <typename UnderlyingType, typename EnumType>
  UnderlyingType underlying_cast(EnumType v)
  {
    return static_cast<UnderlyingType>(v);
  }


  template <typename EnumType>
  inline
  EnumType native_value(EnumType e)
  {
    return e;
 }

    inline WORD_ MAKELANGID_(WORD_ p, WORD_ s) {
        return ((((WORD_  )(s)) << 10) | (WORD_  )(p));
    }
