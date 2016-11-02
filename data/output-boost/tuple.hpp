
   
   static int get_stream_index (int m)
   {
     static const int stream_index[number_of_manipulators]
        = { std::ios::xalloc(), std::ios::xalloc(), std::ios::xalloc() };

     return stream_index[m];
   }

   template<class CharType, class CharTrait>
   static CharType get_manipulator(std::basic_ios<CharType, CharTrait>& i, 
                                   manipulator_type m) {
     // The manipulators are stored as long.
     // A valid instanitation of basic_stream allows CharType to be any POD,
     // hence, the static_cast may fail (it fails if long is not convertible 
     // to CharType
     CharType c = static_cast<CharType>(i.iword(get_stream_index(m)) ); 
     // parentheses and space are the default manipulators
     if (!c) {
       switch(m) {
         case detail::format_info::open :  c = i.widen('('); break;
         case detail::format_info::close : c = i.widen(')'); break;
         case detail::format_info::delimiter : c = i.widen(' '); break;
       }
     }
     return c;
   }



   template<class CharType, class CharTrait>
   static void set_manipulator(std::basic_ios<CharType, CharTrait>& i, 
                               manipulator_type m, CharType c) {
     // The manipulators are stored as long.
     // A valid instanitation of basic_stream allows CharType to be any POD,
     // hence, the static_cast may fail (it fails if CharType is not 
     // convertible long.
      i.iword(get_stream_index(m)) = static_cast<long>(c);
   }

  explicit tuple_manipulator(detail::format_info::manipulator_type m, 
                             const char c = 0)
     : mt(m), f_c(c) {}

   template<class CharTrait>
  void set(std::basic_ios<CharType, CharTrait> &io) const {
     detail::format_info::set_manipulator(io, mt, f_c);
  }


inline bool operator==(const null_type&, const null_type&) { return true; }

inline bool operator>=(const null_type&, const null_type&) { return true; }

inline bool operator<=(const null_type&, const null_type&) { return true; }

inline bool operator!=(const null_type&, const null_type&) { return false; }

inline bool operator<(const null_type&, const null_type&) { return false; }

inline bool operator>(const null_type&, const null_type&) { return false; }



template<class T1, class T2>
inline bool eq(const T1& lhs, const T2& rhs) {
  return lhs.get_head() == rhs.get_head() &&
         eq(lhs.get_tail(), rhs.get_tail());
}

      null_type() {}

      null_type(const null_type&, const null_type&) {}

    inline const null_type cnull_type() { return null_type(); }

        explicit assign_to_pointee(T* p) : ptr(p) {}


        template<typename Other>
        assign_to_pointee& operator=(const Other& other)
        {
          *ptr = other;
          return *this;
        }

        template<typename T>
        swallow_assign const& operator=(const T&) const
        {
          return *this;
        }

        template <class H, class T>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
        static typename add_reference<typename add_const<T>::type>::type
#else
        static typename add_const_reference<T>::type
#endif
        execute( cons<H,T> const& u, long )
        {
            return u.get_tail();
        }

        template <class H>
        static null_type execute( cons<H,null_type> const& u, long )
        {
            return null_type();
        }


        template <class U>
        static null_type execute(U const&, ...)
        {
            return null_type();
        }


    template <class Other>
    Other const&
    init_head( Other const& u, ... )
    {
        return u;
    }


     head_ref get_head() { return head; }

     tail_ref get_tail() { return tail; }


     head_cref get_head() const { return head; }

     tail_cref get_tail() const { return tail; }


     cons() : head(), tail() {}

      template<typename T>
      explicit cons(head_cref h, const T& t) :
        head(h), tail(t.head, t.tail)
      {
      }


      explicit cons(head_cref h = head_type(),
                    tail_cref t = tail_type()) :
        head(h), tail(t)
      {
      }


      template <class U>
      cons( const U& u )
        : head(detail::init_head(u, 0))
        , tail(detail::init_tail<Tail>::execute(u, 0L))
       {
       }


      template<typename Other>
      cons& operator=(const Other& other)
      {
        head = other.head;
        tail = other.tail;
        return *this;
      }

      template<typename Head, typename Tail>
      static inline
      typename detail::element_ref<N, cons<Head, Tail> >::RET
      get(cons<Head, Tail>& t)
      {
        return get_class<N-1>::get(t.tail);
      }


      template<typename Head, typename Tail>
      static inline
      typename detail::element_const_ref<N, cons<Head, Tail> >::RET
      get(const cons<Head, Tail>& t)
      {
        return get_class<N-1>::get(t.tail);
      }


      tuple() : cons1(T1(), cons2(T2(), cons3(T3(), cons4(T4(), cons5(T5(), cons6(T6(),cons7(T7(),cons8(T8(),cons9(T9(),cons10(T10()))))))))))
        {}


      tuple(
          t1_cref t1,
          t2_cref t2,
          t3_cref t3 = T3(),
          t4_cref t4 = T4(),
          t5_cref t5 = T5(),
          t6_cref t6 = T6(),
          t7_cref t7 = T7(),
          t8_cref t8 = T8(),
          t9_cref t9 = T9(),
          t10_cref t10 = T10()
      ) :
        cons1(t1, cons2(t2, cons3(t3, cons4(t4, cons5(t5, cons6(t6,cons7(t7,cons8(t8,cons9(t9,cons10(t10))))))))))
      {
      }


      explicit tuple(t1_cref t1)
        : cons1(t1, cons2(T2(), cons3(T3(), cons4(T4(), cons5(T5(), cons6(T6(),cons7(T7(),cons8(T8(),cons9(T9(),cons10(T10()))))))))))
      {}


      template<typename Head, typename Tail>
      tuple(const cons<Head, Tail>& other) :
        cons1(other.head, other.tail)
      {
      }


      template<typename First, typename Second>
      self_type& operator=(const std::pair<First, Second>& other)
      {
        this->head = other.first;
        this->tail.head = other.second;
        return *this;
      }


      template<typename Head, typename Tail>
      self_type& operator=(const cons<Head, Tail>& other)
      {
        this->head = other.head;
        this->tail = other.tail;

        return *this;
      }


    template<int N, typename Head, typename Tail>
    typename detail::element_ref<N, cons<Head, Tail> >::RET
    get(cons<Head, Tail>& t, detail::workaround_holder<N>* = 0)
    {
      return detail::get_class<N>::get(t);
    }


    template<int N, typename Head, typename Tail>
    typename detail::element_const_ref<N, cons<Head, Tail> >::RET
    get(const cons<Head, Tail>& t, detail::workaround_holder<N>* = 0)
    {
      return detail::get_class<N>::get(t);
    }

    template<typename T1>
    inline
    tuple<T1>
    make_tuple(const T1& t1)
    {
      return tuple<T1>(t1);
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    inline
    tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
    make_tuple(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6, const T7& t7, const T8& t8, const T9& t9, const T10& t10)
    {
      return tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
    }

    template<typename T1>
    inline
    tuple<detail::assign_to_pointee<T1> >
    tie(T1& t1)
    {
      return make_tuple(detail::assign_to_pointee<T1>(&t1));
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    inline
    tuple<detail::assign_to_pointee<T1>,
      detail::assign_to_pointee<T2>,
      detail::assign_to_pointee<T3>,
      detail::assign_to_pointee<T4>,
      detail::assign_to_pointee<T5>,
      detail::assign_to_pointee<T6>,
      detail::assign_to_pointee<T7>,
      detail::assign_to_pointee<T8>,
      detail::assign_to_pointee<T9>,
      detail::assign_to_pointee<T10> >
    tie(T1& t1, T2& t2, T3& t3, T4& t4, T5 &t5, T6 &t6, T7 &t7, T8 &t8, T9 &t9, T10 &t10)
    {
      return make_tuple(detail::assign_to_pointee<T1>(&t1),
                        detail::assign_to_pointee<T2>(&t2),
                        detail::assign_to_pointee<T3>(&t3),
                        detail::assign_to_pointee<T4>(&t4),
                        detail::assign_to_pointee<T5>(&t5),
                        detail::assign_to_pointee<T6>(&t6),
                        detail::assign_to_pointee<T7>(&t7),
                        detail::assign_to_pointee<T8>(&t8),
                        detail::assign_to_pointee<T9>(&t9),
                        detail::assign_to_pointee<T10>(&t10));
    }

inline void swap(null_type&, null_type&) {}

template<class HH>
inline void swap(cons<HH, null_type>& lhs, cons<HH, null_type>& rhs) {
  ::boost::swap(lhs.head, rhs.head);
}

template<class HH, class TT>
inline void swap(cons<HH, TT>& lhs, cons<HH, TT>& rhs) {
  ::boost::swap(lhs.head, rhs.head);
  ::boost::tuples::swap(lhs.tail, rhs.tail);
}

template <class T0, class T1, class T2, class T3, class T4,
          class T5, class T6, class T7, class T8, class T9>
inline void swap(tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& lhs,
          tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& rhs) {
  typedef tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tuple_type;
  typedef typename tuple_type::inherited base;
  ::boost::tuples::swap(static_cast<base&>(lhs), static_cast<base&>(rhs));
}

  inline const null_type cnull() { return null_type(); }

        static const type& call(const Tuple& tup) {
            return next::call(tup).tail;
        }

        static const type& call(const Tuple& tup) {
            return tup;
        }


template<int N, class HT, class TT>
inline typename access_traits<
                  typename element<N, cons<HT, TT> >::type
                >::non_const_type
get(cons<HT, TT>& c BOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(int, N)) {
  typedef BOOST_DEDUCED_TYPENAME detail::drop_front<N>::BOOST_NESTED_TEMPLATE
      apply<cons<HT, TT> > impl;
  typedef BOOST_DEDUCED_TYPENAME impl::type cons_element;
  return const_cast<cons_element&>(impl::call(c)).head;
}

template<int N, class HT, class TT>
inline typename access_traits<
                  typename element<N, cons<HT, TT> >::type
                >::const_type
get(const cons<HT, TT>& c BOOST_APPEND_EXPLICIT_TEMPLATE_NON_TYPE(int, N)) {
  typedef BOOST_DEDUCED_TYPENAME detail::drop_front<N>::BOOST_NESTED_TEMPLATE
      apply<cons<HT, TT> > impl;
  typedef BOOST_DEDUCED_TYPENAME impl::type cons_element;
  return impl::call(c).head;
}


  typename access_traits<stored_head_type>::non_const_type
  get_head() { return head; }


  typename access_traits<tail_type>::non_const_type
  get_tail() { return tail; }


  typename access_traits<stored_head_type>::const_type
  get_head() const { return head; }


  typename access_traits<tail_type>::const_type
  get_tail() const { return tail; }


  cons() : head(), tail() {}


  cons(typename access_traits<stored_head_type>::parameter_type h,
       const tail_type& t)
    : head (h), tail(t) {}


  template <class T1, class T2, class T3, class T4, class T5,
            class T6, class T7, class T8, class T9, class T10>
  cons( T1& t1, T2& t2, T3& t3, T4& t4, T5& t5,
        T6& t6, T7& t7, T8& t8, T9& t9, T10& t10 )
    : head (t1),
      tail (t2, t3, t4, t5, t6, t7, t8, t9, t10, detail::cnull())
      {}


  template <class T2, class T3, class T4, class T5,
            class T6, class T7, class T8, class T9, class T10>
  cons( const null_type& /*t1*/, T2& t2, T3& t3, T4& t4, T5& t5,
        T6& t6, T7& t7, T8& t8, T9& t9, T10& t10 )
    : head (),
      tail (t2, t3, t4, t5, t6, t7, t8, t9, t10, detail::cnull())
      {}



  template <class HT2, class TT2>
  cons( const cons<HT2, TT2>& u ) : head(u.head), tail(u.tail) {}


  template <class HT2, class TT2>
  cons& operator=( const cons<HT2, TT2>& u ) {
    head=u.head; tail=u.tail; return *this;
  }

  cons& operator=(const cons& u) {
    head = u.head; tail = u.tail;  return *this;
  }

  template <int N>
  typename access_traits<
             typename element<N, cons<HT, TT> >::type
           >::non_const_type
  get() {
    return boost::tuples::get<N>(*this); // delegate to non-member get
  }


  template <int N>
  typename access_traits<
             typename element<N, cons<HT, TT> >::type
           >::const_type
  get() const {
    return boost::tuples::get<N>(*this); // delegate to non-member get
  }


  typename access_traits<stored_head_type>::non_const_type
  get_head() { return head; }


  null_type get_tail() { return null_type(); }


  typename access_traits<stored_head_type>::const_type
  get_head() const { return head; }


  const null_type get_tail() const { return null_type(); }

  cons() : head() {}


  cons(typename access_traits<stored_head_type>::parameter_type h,
       const null_type& = null_type())
    : head (h) {}


  template<class T1>
  cons(T1& t1, const null_type&, const null_type&, const null_type&,
       const null_type&, const null_type&, const null_type&,
       const null_type&, const null_type&, const null_type&)
  : head (t1) {}


  cons(const null_type&,
       const null_type&, const null_type&, const null_type&,
       const null_type&, const null_type&, const null_type&,
       const null_type&, const null_type&, const null_type&)
  : head () {}


  template <class HT2>
  cons( const cons<HT2, null_type>& u ) : head(u.head) {}


  template <class HT2>
  cons& operator=(const cons<HT2, null_type>& u )
  { head = u.head; return *this; }

  cons& operator=(const cons& u) { head = u.head; return *this; }


  template <int N>
  typename access_traits<
             typename element<N, self_type>::type
            >::non_const_type
  get(BOOST_EXPLICIT_TEMPLATE_NON_TYPE(int, N)) {
    return boost::tuples::get<N>(*this);
  }

  tuple() {}


  tuple(typename access_traits<T0>::parameter_type t0)
    : inherited(t0, detail::cnull(), detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1)
    : inherited(t0, t1, detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2)
    : inherited(t0, t1, t2, detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3)
    : inherited(t0, t1, t2, t3, detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull(),
                detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4)
    : inherited(t0, t1, t2, t3, t4, detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4,
        typename access_traits<T5>::parameter_type t5)
    : inherited(t0, t1, t2, t3, t4, t5, detail::cnull(), detail::cnull(),
                detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4,
        typename access_traits<T5>::parameter_type t5,
        typename access_traits<T6>::parameter_type t6)
    : inherited(t0, t1, t2, t3, t4, t5, t6, detail::cnull(),
                detail::cnull(), detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4,
        typename access_traits<T5>::parameter_type t5,
        typename access_traits<T6>::parameter_type t6,
        typename access_traits<T7>::parameter_type t7)
    : inherited(t0, t1, t2, t3, t4, t5, t6, t7, detail::cnull(),
                detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4,
        typename access_traits<T5>::parameter_type t5,
        typename access_traits<T6>::parameter_type t6,
        typename access_traits<T7>::parameter_type t7,
        typename access_traits<T8>::parameter_type t8)
    : inherited(t0, t1, t2, t3, t4, t5, t6, t7, t8, detail::cnull()) {}


  tuple(typename access_traits<T0>::parameter_type t0,
        typename access_traits<T1>::parameter_type t1,
        typename access_traits<T2>::parameter_type t2,
        typename access_traits<T3>::parameter_type t3,
        typename access_traits<T4>::parameter_type t4,
        typename access_traits<T5>::parameter_type t5,
        typename access_traits<T6>::parameter_type t6,
        typename access_traits<T7>::parameter_type t7,
        typename access_traits<T8>::parameter_type t8,
        typename access_traits<T9>::parameter_type t9)
    : inherited(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9) {}



  template<class U1, class U2>
  tuple(const cons<U1, U2>& p) : inherited(p) {}


  template <class U1, class U2>
  tuple& operator=(const cons<U1, U2>& k) {
    inherited::operator=(k);
    return *this;
  }

  swallow_assign(ignore_t(*)(ignore_t)) {}

  template<typename T>
  swallow_assign const& operator=(const T&) const {
    return *this;
  }

inline detail::ignore_t ignore(detail::ignore_t) { return 0; }

inline tuple<> make_tuple() {
  return tuple<>();
}


template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
         class T7, class T8, class T9>
inline typename detail::make_tuple_mapper
  <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
make_tuple(const T0& t0, const T1& t1, const T2& t2, const T3& t3,
                  const T4& t4, const T5& t5, const T6& t6, const T7& t7,
                  const T8& t8, const T9& t9) {
  typedef typename detail::make_tuple_mapper
           <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type t;
  return t(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

tie(T0& t0) {
  typedef typename detail::tie_mapper<T0>::type t;
  return t(t0);
}


template<class T0, class T1, class T2, class T3, class T4, class T5, class T6,
         class T7, class T8, class T9>
inline typename detail::tie_mapper
  <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type
tie(T0& t0, T1& t1, T2& t2, T3& t3,
                  T4& t4, T5& t5, T6& t6, T7& t7,
                  T8& t8, T9& t9) {
  typedef typename detail::tie_mapper
           <T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>::type t;
  return t(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

inline void swap(null_type&, null_type&) {}

template<class HH>
inline void swap(cons<HH, null_type>& lhs, cons<HH, null_type>& rhs) {
  ::boost::swap(lhs.head, rhs.head);
}

template<class HH, class TT>
inline void swap(cons<HH, TT>& lhs, cons<HH, TT>& rhs) {
  ::boost::swap(lhs.head, rhs.head);
  ::boost::tuples::swap(lhs.tail, rhs.tail);
}

template <class T0, class T1, class T2, class T3, class T4,
          class T5, class T6, class T7, class T8, class T9>
inline void swap(tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& lhs,
          tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& rhs) {
  typedef tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> tuple_type;
  typedef typename tuple_type::inherited base;
  ::boost::tuples::swap(static_cast<base&>(lhs), static_cast<base&>(rhs));
}
