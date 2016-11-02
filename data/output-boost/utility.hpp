

    base_from_member()
        : member()
        {}


    inline addr_impl_ref( T & v ): v_( v ) {}

    inline operator T& () const { return v_; }

    static inline T * f( T & v, long )
    {
        return reinterpret_cast<T*>(
            &const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
    }


    static inline T * f( T * v, int )
    {
        return v;
    }


template<class T> T * addressof( T & v )
{
#if (defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT( 0x610 ) ) ) || defined( __SUNPRO_CC )

    return boost::detail::addressof_impl<T>::f( v, 0 );

#else

    return boost::detail::addressof_impl<T>::f( boost::detail::addr_impl_ref<T>( v ), 0 );

#endif
}


      wrapper()
      :
      data()
      {
      }


      wrapper(T const & arg)
      :
      data(arg)
      {
      }


    wrapper * wrapper_address() const
    {
      return static_cast<wrapper *>( static_cast<void*>(&x));
    }


    initialized()
    {
#if BOOST_DETAIL_VALUE_INIT_WORKAROUND
      std::memset(&x, 0, sizeof(x));
#endif
      new (wrapper_address()) wrapper();
    }


    initialized(initialized const & arg)
    {
      new (wrapper_address()) wrapper( static_cast<wrapper const &>(*(arg.wrapper_address())));
    }


    explicit initialized(T const & arg)
    {
      new (wrapper_address()) wrapper(arg);
    }


    initialized & operator=(initialized const & arg)
    {
      // Assignment is only allowed when T is non-const.
      BOOST_STATIC_ASSERT( ! is_const<T>::value );
      *wrapper_address() = static_cast<wrapper const &>(*(arg.wrapper_address()));
      return *this;
    }


    ~initialized()
    {
      wrapper_address()->wrapper::~wrapper();
    }


    T const & data() const
    {
      return wrapper_address()->data;
    }


    T& data()
    {
      return wrapper_address()->data;
    }


    void swap(initialized & arg)
    {
      ::boost::swap( this->data(), arg.data() );
    }


    operator T const &() const
    {
      return wrapper_address()->data;
    }


    operator T&()
    {
      return wrapper_address()->data;
    }


template<class T>
T const& get ( initialized<T> const& x )
{
  return x.data() ;
}


template<class T>
T& get ( initialized<T>& x )
{
  return x.data() ;
}


template<class T>
void swap ( initialized<T> & lhs, initialized<T> & rhs )
{
  lhs.swap(rhs) ;
}

    
    value_initialized()
    :
    m_data()
    { }

    
    T const & data() const
    {
      return m_data.data();
    }


    T& data()
    {
      return m_data.data();
    }


    void swap(value_initialized & arg)
    {
      m_data.swap(arg.m_data);
    }


    operator T const &() const
    {
      return m_data;
    }


    operator T&()
    {
      return m_data;
    }



template<class T>
T const& get ( value_initialized<T> const& x )
{
  return x.data() ;
}


template<class T>
T& get ( value_initialized<T>& x )
{
  return x.data() ;
}


template<class T>
void swap ( value_initialized<T> & lhs, value_initialized<T> & rhs )
{
  lhs.swap(rhs) ;
}

    
    template <class T> operator T() const
    {
      return initialized<T>().data();
    }

template<class OptionalPointee>
inline
bool equal_pointees ( OptionalPointee const& x, OptionalPointee const& y )
{
  return (!x) != (!y) ? false : ( !x ? true : (*x) == (*y) ) ;
}

  bool operator() ( OptionalPointee const& x, OptionalPointee const& y ) const
    { return equal_pointees(x,y) ; }

template<class OptionalPointee>
inline
bool less_pointees ( OptionalPointee const& x, OptionalPointee const& y )
{
  return !y ? false : ( !x ? true : (*x) < (*y) ) ;
}

  bool operator() ( OptionalPointee const& x, OptionalPointee const& y ) const
    { return less_pointees(x,y) ; }

            string_ref_traits_eq ( charT ch ) : ch_(ch) {}

            bool operator () ( charT val ) const { return traits::eq ( ch_, val ); }


        basic_string_ref& operator=(const basic_string_ref &rhs) {
            ptr_ = rhs.ptr_;
            len_ = rhs.len_;
            return *this;
            }


        basic_string_ref(const charT* str)
            : ptr_(str), len_(traits::length(str)) {}

    template<typename charT, typename traits>
    inline bool operator==(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        if ( x.size () != y.size ()) return false;
        return x.compare(y) == 0;
        }


    template<typename charT, typename traits>
    inline bool operator==(basic_string_ref<charT, traits> x, const charT * y) {
        return x == basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator==(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) == y;
        }

    template<typename charT, typename traits>
    inline bool operator!=(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        if ( x.size () != y.size ()) return true;
        return x.compare(y) != 0;
        }


    template<typename charT, typename traits>
    inline bool operator!=(basic_string_ref<charT, traits> x, const charT * y) {
        return x != basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator!=(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) != y;
        }

    template<typename charT, typename traits>
    inline bool operator<(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        return x.compare(y) < 0;
        }


    template<typename charT, typename traits>
    inline bool operator<(basic_string_ref<charT, traits> x, const charT * y) {
        return x < basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator<(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) < y;
        }

    template<typename charT, typename traits>
    inline bool operator>(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        return x.compare(y) > 0;
        }


    template<typename charT, typename traits>
    inline bool operator>(basic_string_ref<charT, traits> x, const charT * y) {
        return x > basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator>(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) > y;
        }

    template<typename charT, typename traits>
    inline bool operator<=(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        return x.compare(y) <= 0;
        }


    template<typename charT, typename traits>
    inline bool operator<=(basic_string_ref<charT, traits> x, const charT * y) {
        return x <= basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator<=(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) <= y;
        }

    template<typename charT, typename traits>
    inline bool operator>=(basic_string_ref<charT, traits> x, basic_string_ref<charT, traits> y) {
        return x.compare(y) >= 0;
        }


    template<typename charT, typename traits>
    inline bool operator>=(basic_string_ref<charT, traits> x, const charT * y) {
        return x >= basic_string_ref<charT, traits>(y);
        }


    template<typename charT, typename traits>
    inline bool operator>=(const charT * x, basic_string_ref<charT, traits> y) {
        return basic_string_ref<charT, traits>(x) >= y;
        }

  template<class T>
  void swap_impl(T& left, T& right)
  {
    using namespace std;//use std::swap if argument dependent lookup fails
    swap(left,right);
  }


  template<class T, std::size_t N>
  void swap_impl(T (& left)[N], T (& right)[N])
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      ::boost_swap_impl::swap_impl(left[i], right[i]);
    }
  }

  template<class T1, class T2>
  void swap(T1& left, T2& right)
  {
    ::boost_swap_impl::swap_impl(left, right);
  }
