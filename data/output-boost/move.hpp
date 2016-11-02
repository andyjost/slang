

         template <class T, class U>
         inline T&& forward(U&& t
             , typename ::boost::move_detail::enable_if_c<
               move_detail::is_lvalue_reference<T>::value ? move_detail::is_lvalue_reference<U>::value : true>::type * = 0/*
             , typename ::boost::move_detail::enable_if_c<
               move_detail::is_convertible
                  <typename remove_reference<U>::type*, typename remove_reference<T>::type*>::value>::type * = 0*/)
         { return static_cast<T&&>(t);   }


   move_iterator()
   {}


   explicit move_iterator(It i)
      :  m_it(i)
   {}


   template <class U>
   move_iterator(const move_iterator<U>& u)
      :  m_it(u.base())
   {}


   iterator_type base() const
   {  return m_it;   }


   reference operator*() const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return *m_it;
      #else
      return ::boost::move(*m_it);
      #endif
   }


   pointer   operator->() const
   {  return m_it;   }


   move_iterator& operator++()
   {  ++m_it; return *this;   }


   move_iterator<iterator_type>  operator++(int)
   {  move_iterator<iterator_type> tmp(*this); ++(*this); return tmp;   }


   move_iterator& operator--()
   {  --m_it; return *this;   }


   move_iterator<iterator_type>  operator--(int)
   {  move_iterator<iterator_type> tmp(*this); --(*this); return tmp;   }


   move_iterator<iterator_type>  operator+ (difference_type n) const
   {  return move_iterator<iterator_type>(m_it + n);  }


   move_iterator& operator+=(difference_type n)
   {  m_it += n; return *this;   }


   move_iterator<iterator_type>  operator- (difference_type n) const
   {  return move_iterator<iterator_type>(m_it - n);  }


   move_iterator& operator-=(difference_type n)
   {  m_it -= n; return *this;   }


   reference operator[](difference_type n) const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return m_it[n];
      #else
      return ::boost::move(m_it[n]);
      #endif
   }

template<class It>
inline move_iterator<It> make_move_iterator(const It &it)
{  return move_iterator<It>(it); }


   explicit back_move_insert_iterator(C& x) : container_m(&x) { }


   back_move_insert_iterator& operator=(reference x)
   { container_m->push_back(boost::move(x)); return *this; }


   back_move_insert_iterator& operator*()     { return *this; }

   back_move_insert_iterator& operator++()    { return *this; }

   back_move_insert_iterator& operator++(int) { return *this; }

template <typename C> // C models Container
inline back_move_insert_iterator<C> back_move_inserter(C& x)
{
   return back_move_insert_iterator<C>(x);
}


   explicit front_move_insert_iterator(C& x) : container_m(&x) { }


   front_move_insert_iterator& operator=(reference x)
   { container_m->push_front(boost::move(x)); return *this; }


   front_move_insert_iterator& operator*()     { return *this; }

   front_move_insert_iterator& operator++()    { return *this; }

   front_move_insert_iterator& operator++(int) { return *this; }

template <typename C> // C models Container
inline front_move_insert_iterator<C> front_move_inserter(C& x)
{
   return front_move_insert_iterator<C>(x);
}


   explicit move_insert_iterator(C& x, typename C::iterator pos)
      : container_m(&x), pos_(pos)
   {}


   move_insert_iterator& operator=(reference x)
   {
      pos_ = container_m->insert(pos_, ::boost::move(x));
      ++pos_;
      return *this;
   }


   move_insert_iterator& operator*()     { return *this; }

   move_insert_iterator& operator++()    { return *this; }

   move_insert_iterator& operator++(int) { return *this; }

template <typename C> // C models Container
inline move_insert_iterator<C> move_inserter(C& x, typename C::iterator it)
{
   return move_insert_iterator<C>(x, it);
}

   template <typename I, // I models InputIterator
            typename O> // O models OutputIterator
   O move(I f, I l, O result)
   {
      while (f != l) {
         *result = ::boost::move(*f);
         ++f; ++result;
      }
      return result;
   }

   template <typename I, // I models BidirectionalIterator
   typename O> // O models BidirectionalIterator
   O move_backward(I f, I l, O result)
   {
      while (f != l) {
         --l; --result;
         *result = ::boost::move(*l);
      }
      return result;
   }

template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
F uninitialized_move(I f, I l, F r
   /// @cond
//   ,typename ::boost::move_detail::enable_if<has_move_emulation_enabled<typename std::iterator_traits<I>::value_type> >::type* = 0
   /// @endcond
   )
{
   typedef typename std::iterator_traits<I>::value_type input_value_type;

   F back = r;
   BOOST_TRY{
      while (f != l) {
         void * const addr = static_cast<void*>(::boost::move_detail::addressof(*r));
         ::new(addr) input_value_type(::boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
	   for (; back != r; ++back){
         back->~input_value_type();
      }
	   BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}


template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::uninitialized_move(f, l, r);
}


template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::uninitialized_move_move_iterator(f, l, r);
}


template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::move(f, l, r);
}


template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::move_move_iterator(f, l, r);
}

   inline addr_impl_ref( T & v ): v_( v ) {}

   inline operator T& () const { return v_; }

   static inline T * f( T & v, long )
   {
      return reinterpret_cast<T*>(
         &const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
   }


   static inline T * f( T * v, int )
   {  return v;  }


template<class T>
inline T * addressof( T & v )
{
   return ::boost::move_detail::addressof_impl<T>::f
      ( ::boost::move_detail::addr_impl_ref<T>( v ), 0 );
}
