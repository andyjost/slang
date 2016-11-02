
            function_input_iterator() {}

            function_input_iterator(Function & f_, Input state_ = Input()) 
                : f(&f_), state(state_) {}


            void increment() {
                if(value)
                    value = none;
                else
                    (*f)();
                ++state;
            }


            typename Function::result_type const & 
                dereference() const {
                    return (value ? value : value = (*f)()).get();
            }


            bool equal(function_input_iterator const & other) const {
                return f == other.f && state == other.state;
            }

            function_pointer_input_iterator() {}

            function_pointer_input_iterator(Function &f_, Input state_ = Input())
                : f(f_), state(state_) {}


            void increment() {
                if(value)
                    value = none;
                else
                    (*f)();
                ++state;
            }

            function_reference_input_iterator(Function & f_, Input state_ = Input())
                : function_pointer_input_iterator<Function*,Input>(&f_, state_)
            {}


    template <class Function, class Input>
    inline function_input_iterator<Function, Input>
        make_function_input_iterator(Function & f, Input state) {
            typedef function_input_iterator<Function, Input> result_t;
            return result_t(f, state);
    }


    template <class Function, class Input>
    inline function_input_iterator<Function*, Input>
        make_function_input_iterator(Function * f, Input state) {
            typedef function_input_iterator<Function*, Input> result_t;
            return result_t(f, state);
    }

        infinite & operator++() { return *this; }

        infinite & operator++(int) { return *this; }

        bool operator==(infinite &) const { return false; };

        bool operator==(infinite const &) const { return false; };

    template <typename Iterator1, typename Iterator2>
    void interop_single_pass_constraints(Iterator1 const& i1, Iterator2 const& i2)
    {
        bool b;
        b = i1 == i2;
        b = i1 != i2;

        b = i2 == i1;
        b = i2 != i1;
        boost::ignore_unused_variable_warning(b);
    }


    template <typename Iterator1, typename Iterator2>
    void interop_rand_access_constraints(
        Iterator1 const& i1, Iterator2 const& i2,
        boost::random_access_traversal_tag, boost::random_access_traversal_tag)
    {
        bool b;
        typename boost::detail::iterator_traits<Iterator2>::difference_type n;
        b = i1 <  i2;
        b = i1 <= i2;
        b = i1 >  i2;
        b = i1 >= i2;
        n = i1 -  i2;

        b = i2 <  i1;
        b = i2 <= i1;
        b = i2 >  i1;
        b = i2 >= i1;
        n = i2 -  i1;
        boost::ignore_unused_variable_warning(b);
        boost::ignore_unused_variable_warning(n);
    }

      filter_iterator() { }


      filter_iterator(Predicate f, Iterator x, Iterator end_ = Iterator())
          : super_t(x), m_predicate(f), m_end(end_)
      {
          satisfy_predicate();
      }


      filter_iterator(Iterator x, Iterator end_ = Iterator())
        : super_t(x), m_predicate(), m_end(end_)
      {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
          // Don't allow use of this constructor if Predicate is a
          // function pointer type, since it will be 0.
          BOOST_STATIC_ASSERT(is_class<Predicate>::value);
#endif 
          satisfy_predicate();
      }


      Predicate predicate() const { return m_predicate; }


      Iterator end() const { return m_end; }

      void increment()
      {
          ++(this->base_reference());
          satisfy_predicate();
      }


      void decrement()
      {
        while(!this->m_predicate(*--(this->base_reference()))){};
      }


      void satisfy_predicate()
      {
          while (this->base() != this->m_end && !this->m_predicate(*this->base()))
              ++(this->base_reference());
      }


  template <class Predicate, class Iterator>
  filter_iterator<Predicate,Iterator>
  make_filter_iterator(Predicate f, Iterator x, Iterator end = Iterator())
  {
      return filter_iterator<Predicate,Iterator>(f,x,end);
  }

  permutation_iterator() : m_elt_iter() {}


  explicit permutation_iterator(ElementIterator x, IndexIterator y) 
      : super_t(y), m_elt_iter(x) {}



template <class ElementIterator, class IndexIterator>
permutation_iterator<ElementIterator, IndexIterator> 
make_permutation_iterator( ElementIterator e, IndexIterator i )
{
    return permutation_iterator<ElementIterator, IndexIterator>( e, i );
}

      advance_iterator(DiffType step) : m_step(step) {}

      
      template<typename Iterator>
      void operator()(Iterator& it) const
      { it += m_step; }

      template<typename Iterator>
      void operator()(Iterator& it)
      { ++it; }

      template<typename Iterator>
      void operator()(Iterator& it)
      { --it; }


      template<typename Iterator>
        typename apply<Iterator>::type operator()(Iterator const& it)
      { return *it; }

      template<typename Fun>
      Fun BOOST_TUPLE_ALGO(tuple_for_each)(
          tuples::null_type
        , Fun f BOOST_TUPLE_ALGO_TERMINATOR
      )
      { return f; }


      
      template<typename Tuple, typename Fun>
      Fun BOOST_TUPLE_ALGO(tuple_for_each)(
          Tuple& t
        , Fun f BOOST_TUPLE_ALGO_RECURSE)
      { 
          f( t.get_head() );
          return tuple_for_each(t.get_tail(), f);
      }

      inline bool tuple_equal(tuples::null_type, tuples::null_type)
      { return true; }


      template<typename Tuple1, typename Tuple2>
        bool tuple_equal(
            Tuple1 const& t1, 
            Tuple2 const& t2
        )
      { 
          return t1.get_head() == t2.get_head() && 
          tuple_equal(t1.get_tail(), t2.get_tail());
      }

    zip_iterator() { }

    zip_iterator(IteratorTuple iterator_tuple) 
      : m_iterator_tuple(iterator_tuple) 
    { }

    const IteratorTuple& get_iterator_tuple() const
    { return m_iterator_tuple; }

    typename super_t::reference dereference() const
    { 
      return detail::tuple_impl_specific::tuple_transform( 
        get_iterator_tuple(),
        detail::dereference_iterator()
       );
    }

    template<typename OtherIteratorTuple>   
    bool equal(const zip_iterator<OtherIteratorTuple>& other) const
    {
      return detail::tuple_impl_specific::tuple_equal(
        get_iterator_tuple(),
        other.get_iterator_tuple()
        );
    }

    void advance(typename super_t::difference_type n)
    { 
      detail::tuple_impl_specific::tuple_for_each(
          m_iterator_tuple,
          detail::advance_iterator<BOOST_DEDUCED_TYPENAME super_t::difference_type>(n)
          );
    }

    void increment()
    { 
      detail::tuple_impl_specific::tuple_for_each(
        m_iterator_tuple,
        detail::increment_iterator()
        );
    }

    void decrement()
    { 
      detail::tuple_impl_specific::tuple_for_each(
        m_iterator_tuple,
        detail::decrement_iterator()
        );
    }

    template<typename OtherIteratorTuple>
      typename super_t::difference_type distance_to(
        const zip_iterator<OtherIteratorTuple>& other
        ) const
    { 
        return boost::tuples::get<0>(other.get_iterator_tuple()) - 
            boost::tuples::get<0>(this->get_iterator_tuple());
    }

  template<typename IteratorTuple> 
  zip_iterator<IteratorTuple> 
  make_zip_iterator(IteratorTuple t)
  { return zip_iterator<IteratorTuple>(t); }

      reverse_iterator() {}


      explicit reverse_iterator(Iterator x) 
          : super_t(x) {}


  template <class BidirectionalIterator>
  reverse_iterator<BidirectionalIterator> make_reverse_iterator(BidirectionalIterator x)
  {
      return reverse_iterator<BidirectionalIterator>(x);
  }

      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return y - x;
      }

      static Difference distance(Incrementable1 x, Incrementable2 y)
      {
          return numeric_distance(x, y);
      }


    counting_iterator() { }

    
    counting_iterator(counting_iterator const& rhs) : super_t(rhs.base()) {}


    counting_iterator(Incrementable x)
      : super_t(x)
    {
    }

    
    typename super_t::reference dereference() const
    {
        return this->base_reference();
    }


    template <class OtherIncrementable>
    difference_type
    distance_to(counting_iterator<OtherIncrementable, CategoryOrTraversal, Difference> const& y) const
    {
      typedef typename mpl::if_<
          detail::is_numeric<Incrementable>
        , detail::number_distance<difference_type, Incrementable, OtherIncrementable>
        , detail::iterator_distance<difference_type, Incrementable, OtherIncrementable>
      >::type d;

      return d::distance(this->base(), y.base());
    }

template <class Incrementable>
inline counting_iterator<Incrementable>
make_counting_iterator(Incrementable x)
{
  typedef counting_iterator<Incrementable> result_t;
  return result_t(x);
}

    template <class Tr1, class Tr2>
    inline void iterator_adaptor_assert_traversal ()
    {
      BOOST_STATIC_ASSERT((is_convertible<Tr1, Tr2>::value));
    }

      iterator_adaptor() {}


      explicit iterator_adaptor(Base const &iter)
          : m_iterator(iter)
      {
      }


      Base const& base() const
        { return m_iterator; }

      Base const& base_reference() const
        { return m_iterator; }


      Base& base_reference()
        { return m_iterator; }

      typename super_t::reference dereference() const
        { return *m_iterator; }


      template <
      class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >   
      bool equal(iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& x) const
      {
        // Maybe readd with same_distance
        //           BOOST_STATIC_ASSERT(
        //               (detail::same_category_and_difference<Derived,OtherDerived>::value)
        //               );
          return m_iterator == x.base();
      }


      void advance(typename super_t::difference_type n)
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(random_access_traversal_tag)
          m_iterator += n;
      }

  
      void increment() { ++m_iterator; }


      void decrement() 
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(bidirectional_traversal_tag)
           --m_iterator;
      }


      template <
          class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >   
      typename super_t::difference_type distance_to(
          iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& y) const
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(random_access_traversal_tag)
          // Maybe readd with same_distance
          //           BOOST_STATIC_ASSERT(
          //               (detail::same_category_and_difference<Derived,OtherDerived>::value)
          //               );
          return y.base() - m_iterator;
      }

      indirect_iterator() {}


      indirect_iterator(Iterator iter)
        : super_t(iter) {}
    
      typename super_t::reference dereference() const
      {
# if BOOST_WORKAROUND(__BORLANDC__, < 0x5A0 )
          return const_cast<super_t::reference>(**this->base());
# else
          return **this->base();
# endif 
      }


  template <class Iter>
  inline
  indirect_iterator<Iter> make_indirect_iterator(Iter x)
  {
    return indirect_iterator<Iter>(x);
  }

      assign_proxy& operator=(T) { return *this; }

      operator T() { return static_object<T>::get(); }

      read_write_proxy& operator=(T) { return *this; }

      T const* operator->() const { return 0; }

      read_proxy<ValueType> operator[](std::ptrdiff_t n) const { return read_proxy<ValueType>(); }

      read_write_proxy<ValueType> operator[](std::ptrdiff_t n) const { return read_write_proxy<ValueType>(); }

      
      traversal_archetype_() {}


      traversal_archetype_(ctor_arg arg)
        : base(arg) 
      {}


  template <class Derived, class Value>
  bool operator==(traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&,
                  traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&) { return true; }


  template <class Derived, class Value>
  Derived& operator+(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                     std::ptrdiff_t) { return static_object<Derived>::get(); }


  template <class Derived, class Value>
  Derived& operator-(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                     std::ptrdiff_t)
      { return static_object<Derived>::get(); }


  template <class Derived, class Value>
  bool operator<(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }


  template <class Derived, class Value>
  bool operator>(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }


  template <class Derived, class Value>
  bool operator<=(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }


  template <class Derived, class Value>
  bool operator>=(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }


    iterator_archetype() { }

    iterator_archetype(iterator_archetype const& x)
      : detail::iterator_archetype_base<
            Value
          , AccessCategory
          , TraversalCategory
        >(x)
    {}


    iterator_archetype& operator=(iterator_archetype const&)
        { return *this; }

        explicit postfix_increment_proxy(Iterator const& x)
          : stored_value(*x)
        {}

        value_type&
        operator*() const
        {
            return this->stored_value;
        }

        explicit writable_postfix_increment_proxy(Iterator const& x)
          : stored_value(*x)
          , stored_iterator(x)
        {}

        writable_postfix_increment_proxy const&
        operator*() const
        {
            return *this;
        }

            explicit proxy(Reference const & x) : m_ref(x) {}

            Reference* operator->() { return boost::addressof(m_ref); }

            operator Reference*() { return boost::addressof(m_ref); }

        static result_type apply(Reference const & x)
        {
            return result_type(x);
        }

        static result_type apply(T& x)
        {
            return boost::addressof(x);
        }

        operator_brackets_proxy(Iterator const& iter)
          : m_iter(iter)
        {}


        operator reference() const
        {
            return *m_iter;
        }


        operator_brackets_proxy& operator=(value_type const& val)
        {
            *m_iter = val;
            return *this;
        }


    template <class Iterator>
    operator_brackets_proxy<Iterator> make_operator_brackets_result(Iterator const& iter, mpl::true_)
    {
        return operator_brackets_proxy<Iterator>(iter);
    }


      template <class Facade>
      static typename Facade::reference dereference(Facade const& f)
      {
          return f.dereference();
      }


      template <class Facade>
      static void increment(Facade& f)
      {
          f.increment();
      }


      template <class Facade>
      static void decrement(Facade& f)
      {
          f.decrement();
      }


      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return f1.equal(f2);
      }


      template <class Facade>
      static void advance(Facade& f, typename Facade::difference_type n)
      {
          f.advance(n);
      }


      template <class Facade1, class Facade2>
      static typename Facade1::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return -f1.distance_to(f2);
      }

      template <class I, class V, class TC, class R, class D>
      static I& derived(iterator_facade<I,V,TC,R,D>& facade)
      {
          return *static_cast<I*>(&facade);
      }


      template <class I, class V, class TC, class R, class D>
      static I const& derived(iterator_facade<I,V,TC,R,D> const& facade)
      {
          return *static_cast<I const*>(&facade);
      }

      Derived& derived()
      {
          return *static_cast<Derived*>(this);
      }


      Derived const& derived() const
      {
          return *static_cast<Derived const*>(this);
      }


      reference operator*() const
      {
          return iterator_core_access::dereference(this->derived());
      }


      pointer operator->() const
      {
          return operator_arrow_dispatch_::apply(*this->derived());
      }

        
      typename boost::detail::operator_brackets_result<Derived,Value,reference>::type
      operator[](difference_type n) const
      {
          typedef boost::detail::use_operator_brackets_proxy<Value,Reference> use_proxy;
          
          return boost::detail::make_operator_brackets_result<Derived>(
              this->derived() + n
            , use_proxy()
          );
      }


      Derived& operator++()
      {
          iterator_core_access::increment(this->derived());
          return this->derived();
      }

      
      Derived& operator--()
      {
          iterator_core_access::decrement(this->derived());
          return this->derived();
      }


      Derived operator--(int)
      {
          Derived tmp(this->derived());
          --*this;
          return tmp;
      }


      Derived& operator+=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), n);
          return this->derived();
      }


      Derived& operator-=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), -n);
          return this->derived();
      }


      Derived operator-(difference_type x) const
      {
          Derived result(this->derived());
          return result -= x;
      }
              \
    template <class Derived, class V, class TC, class R, class D>   \
    prefix Derived operator+ args

  //
  // Helper class for granting access to the iterator core interface.
  //
  // The simple core interface is used by iterator_facade. The core
  // interface of a user/library defined iterator type should not be made public
  // so that it does not clutter the public interface. Instead iterator_core_access
  // should be made friend so that iterator_facade can access the core
  // interface through iterator_core_access.
  //
  class iterator_core_access
  {
# if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)                  
      // Tasteless as this may seem, making all members public allows member templates
      // to work in the absence of member template friends.
   public:
# else
      
      template <class I, class V, class TC, class R, class D> friend class iterator_facade;

#  define BOOST_ITERATOR_FACADE_RELATION(op)                                \
      BOOST_ITERATOR_FACADE_INTEROP_HEAD(friend,op, boost::detail::always_bool2);

      BOOST_ITERATOR_FACADE_RELATION(==)
      BOOST_ITERATOR_FACADE_RELATION(!=)

      BOOST_ITERATOR_FACADE_RELATION(<)
      BOOST_ITERATOR_FACADE_RELATION(>)
      BOOST_ITERATOR_FACADE_RELATION(<=)
      BOOST_ITERATOR_FACADE_RELATION(>=)
#  undef BOOST_ITERATOR_FACADE_RELATION

      BOOST_ITERATOR_FACADE_INTEROP_HEAD(
          friend, -, boost::detail::choose_difference_type)
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
          , (iterator_facade<Derived, V, TC, R, D> const&
           , typename Derived::difference_type)
      )
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
        , (typename Derived::difference_type
           , iterator_facade<Derived, V, TC, R, D> const&)
      )
      ;

# endif

      template <class Facade>
      static typename Facade::reference dereference(Facade const& f)
      {
          return f.dereference();
      }

      template <class Facade>
      static void increment(Facade& f)
      {
          f.increment();
      }

      template <class Facade>
      static void decrement(Facade& f)
      {
          f.decrement();
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return f1.equal(f2);
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.equal(f1);
      }

      template <class Facade>
      static void advance(Facade& f, typename Facade::difference_type n)
      {
          f.advance(n);
      }

      template <class Facade1, class Facade2>
      static typename Facade1::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return -f1.distance_to(f2);
      }

      template <class Facade1, class Facade2>
      static typename Facade2::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.distance_to(f1);
      }

      //
      // Curiously Recurring Template interface.
      //
      template <class I, class V, class TC, class R, class D>
      static I& derived(iterator_facade<I,V,TC,R,D>& facade)
      {
          return *static_cast<I*>(&facade);
      }

      template <class I, class V, class TC, class R, class D>
      static I const& derived(iterator_facade<I,V,TC,R,D> const& facade)
      {
          return *static_cast<I const*>(&facade);
      }

   private:
      // objects of this class are useless
      iterator_core_access(); //undefined
  };

  //
  // iterator_facade - use as a public base class for defining new
  // standard-conforming iterators.
  //
  template <
      class Derived             // The derived iterator type being constructed
    , class Value
    , class CategoryOrTraversal
    , class Reference   = Value&
    , class Difference  = std::ptrdiff_t
  >
  class iterator_facade
# ifdef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
    : public boost::detail::iterator_facade_types<
         Value, CategoryOrTraversal, Reference, Difference
      >::base
#  undef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
# endif
  {
   private:
      //
      // Curiously Recurring Template interface.
      //
      Derived& derived()
      {
          return *static_cast<Derived*>(this);
      }

      Derived const& derived() const
      {
          return *static_cast<Derived const*>(this);
      }

      typedef boost::detail::iterator_facade_types<
         Value, CategoryOrTraversal, Reference, Difference
      > associated_types;

      typedef boost::detail::operator_arrow_dispatch<
          Reference
        , typename associated_types::pointer
      > operator_arrow_dispatch_;

   protected:
      // For use by derived classes
      typedef iterator_facade<Derived,Value,CategoryOrTraversal,Reference,Difference> iterator_facade_;
      
   public:

      typedef typename associated_types::value_type value_type;
      typedef Reference reference;
      typedef Difference difference_type;

      typedef typename operator_arrow_dispatch_::result_type pointer;

      typedef typename associated_types::iterator_category iterator_category;

      reference operator*() const
      {
          return iterator_core_access::dereference(this->derived());
      }

      pointer operator->() const
      {
          return operator_arrow_dispatch_::apply(*this->derived());
      }
        
      typename boost::detail::operator_brackets_result<Derived,Value,reference>::type
      operator[](difference_type n) const
      {
          typedef boost::detail::use_operator_brackets_proxy<Value,Reference> use_proxy;
          
          return boost::detail::make_operator_brackets_result<Derived>(
              this->derived() + n
            , use_proxy()
          );
      }

      Derived& operator++()
      {
          iterator_core_access::increment(this->derived());
          return this->derived();
      }

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      typename boost::detail::postfix_increment_result<Derived,Value,Reference,CategoryOrTraversal>::type
      operator++(int)
      {
          typename boost::detail::postfix_increment_result<Derived,Value,Reference,CategoryOrTraversal>::type
          tmp(this->derived());
          ++*this;
          return tmp;
      }
# endif
      
      Derived& operator--()
      {
          iterator_core_access::decrement(this->derived());
          return this->derived();
      }

      Derived operator--(int)
      {
          Derived tmp(this->derived());
          --*this;
          return tmp;
      }

      Derived& operator+=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), n);
          return this->derived();
      }

      Derived& operator-=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), -n);
          return this->derived();
      }

      Derived operator-(difference_type x) const
      {
          Derived result(this->derived());
          return result -= x;
      }

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      // There appears to be a bug which trashes the data of classes
      // derived from iterator_facade when they are assigned unless we
      // define this assignment operator.  This bug is only revealed
      // (so far) in STLPort debug mode, but it's clearly a codegen
      // problem so we apply the workaround for all MSVC6.
      iterator_facade& operator=(iterator_facade const&)
      {
          return *this;
      }
# endif
  };

# if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
  template <class I, class V, class TC, class R, class D>
  inline typename boost::detail::postfix_increment_result<I,V,R,TC>::type
  operator++(
      iterator_facade<I,V,TC,R,D>& i
    , int
  )
  {
      typename boost::detail::postfix_increment_result<I,V,R,TC>::type
          tmp(*static_cast<I*>(&i));
      
      ++i;
      
      return tmp;
  }
# endif 

  
  //
  // Comparison operator implementation. The library supplied operators
  // enables the user to provide fully interoperable constant/mutable
  // iterator types. I.e. the library provides all operators
  // for all mutable/constant iterator combinations.
  //
  // Note though that this kind of interoperability for constant/mutable
  // iterators is not required by the standard for container iterators.
  // All the standard asks for is a conversion mutable -> constant.
  // Most standard library implementations nowadays provide fully interoperable
  // iterator implementations, but there are still heavily used implementations
  // that do not provide them. (Actually it's even worse, they do not provide
  // them for only a few iterators.)
  //
  // ?? Maybe a BOOST_ITERATOR_NO_FULL_INTEROPERABILITY macro should
  //    enable the user to turn off mixed type operators
  //
  // The library takes care to provide only the right operator overloads.
  // I.e.
  //
  // bool operator==(Iterator,      Iterator);
  // bool operator==(ConstIterator, Iterator);
  // bool operator==(Iterator,      ConstIterator);
  // bool operator==(ConstIterator, ConstIterator);
  //
  //   ...
  //
  // In order to do so it uses c++ idioms that are not yet widely supported
  // by current compiler releases. The library is designed to degrade gracefully
  // in the face of compiler deficiencies. In general compiler
  // deficiencies result in less strict error checking and more obscure
  // error messages, functionality is not affected.
  //
  // For full operation compiler support for "Substitution Failure Is Not An Error"
  // (aka. enable_if) and boost::is_convertible is required.
  //
  // The following problems occur if support is lacking.
  //
  // Pseudo code
  //
  // ---------------
  // AdaptorA<Iterator1> a1;
  // AdaptorA<Iterator2> a2;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if or is_convertible is not supported
  // // The instantiation will fail with an error hopefully indicating that
  // // there is no operator== for Iterator1, Iterator2
  // // The same will happen if no enable_if is used to remove
  // // false overloads from the templated conversion constructor
  // // of AdaptorA.
  //
  // a1 == a2;
  // ----------------
  //
  // AdaptorA<Iterator> a;
  // AdaptorB<Iterator> b;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if is not supported the static assert used
  // // in the operator implementation will fail.
  // // This will accidently work if is_convertible is not supported.
  //
  // a == b;
  // ----------------
  //

# ifdef BOOST_NO_ONE_WAY_ITERATOR_INTEROP
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) mpl::true_()
# else
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) is_convertible<a,b>()
# endif

# define BOOST_ITERATOR_FACADE_INTEROP(op, result_type, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP_HEAD(inline, op, result_type)                   \
  {                                                                             \
      /* For those compilers that do not support enable_if */                   \
      BOOST_STATIC_ASSERT((                                                     \
          is_interoperable< Derived1, Derived2 >::value                         \
      ));                                                                       \
      return_prefix iterator_core_access::base_op(                              \
          *static_cast<Derived1 const*>(&lhs)                                   \
        , *static_cast<Derived2 const*>(&rhs)                                   \
        , BOOST_ITERATOR_CONVERTIBLE(Derived2,Derived1)                         \
      );                                                                        \
  }

# define BOOST_ITERATOR_FACADE_RELATION(op, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP(                                    \
      op                                                            \
    , boost::detail::always_bool2                                   \
    , return_prefix                                                 \
    , base_op                                                       \
  )

  BOOST_ITERATOR_FACADE_RELATION(==, return, equal)
  BOOST_ITERATOR_FACADE_RELATION(!=, return !, equal)

  BOOST_ITERATOR_FACADE_RELATION(<, return 0 >, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(>, return 0 <, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(<=, return 0 >=, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(>=, return 0 <=, distance_from)
# undef BOOST_ITERATOR_FACADE_RELATION

  // operator- requires an additional part in the static assertion
  BOOST_ITERATOR_FACADE_INTEROP(
      -
    , boost::detail::choose_difference_type
    , return
    , distance_from
  )
# undef BOOST_ITERATOR_FACADE_INTEROP
# undef BOOST_ITERATOR_FACADE_INTEROP_HEAD

# define BOOST_ITERATOR_FACADE_PLUS(args)           \
  BOOST_ITERATOR_FACADE_PLUS_HEAD(inline, args)     \
  {                                                 \
      Derived tmp(static_cast<Derived const&>(i));  \
      return tmp += n;                              \
  }

BOOST_ITERATOR_FACADE_PLUS((
  iterator_facade<Derived, V, TC, R, D> const& i
  , typename Derived::difference_type n
))
              \
    template <class Derived, class V, class TC, class R, class D>   \
    prefix Derived operator+ args

  //
  // Helper class for granting access to the iterator core interface.
  //
  // The simple core interface is used by iterator_facade. The core
  // interface of a user/library defined iterator type should not be made public
  // so that it does not clutter the public interface. Instead iterator_core_access
  // should be made friend so that iterator_facade can access the core
  // interface through iterator_core_access.
  //
  class iterator_core_access
  {
# if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)                  
      // Tasteless as this may seem, making all members public allows member templates
      // to work in the absence of member template friends.
   public:
# else
      
      template <class I, class V, class TC, class R, class D> friend class iterator_facade;

#  define BOOST_ITERATOR_FACADE_RELATION(op)                                \
      BOOST_ITERATOR_FACADE_INTEROP_HEAD(friend,op, boost::detail::always_bool2);

      BOOST_ITERATOR_FACADE_RELATION(==)
      BOOST_ITERATOR_FACADE_RELATION(!=)

      BOOST_ITERATOR_FACADE_RELATION(<)
      BOOST_ITERATOR_FACADE_RELATION(>)
      BOOST_ITERATOR_FACADE_RELATION(<=)
      BOOST_ITERATOR_FACADE_RELATION(>=)
#  undef BOOST_ITERATOR_FACADE_RELATION

      BOOST_ITERATOR_FACADE_INTEROP_HEAD(
          friend, -, boost::detail::choose_difference_type)
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
          , (iterator_facade<Derived, V, TC, R, D> const&
           , typename Derived::difference_type)
      )
      ;

      BOOST_ITERATOR_FACADE_PLUS_HEAD(
          friend inline
        , (typename Derived::difference_type
           , iterator_facade<Derived, V, TC, R, D> const&)
      )
      ;

# endif

      template <class Facade>
      static typename Facade::reference dereference(Facade const& f)
      {
          return f.dereference();
      }

      template <class Facade>
      static void increment(Facade& f)
      {
          f.increment();
      }

      template <class Facade>
      static void decrement(Facade& f)
      {
          f.decrement();
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return f1.equal(f2);
      }

      template <class Facade1, class Facade2>
      static bool equal(Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.equal(f1);
      }

      template <class Facade>
      static void advance(Facade& f, typename Facade::difference_type n)
      {
          f.advance(n);
      }

      template <class Facade1, class Facade2>
      static typename Facade1::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::true_)
      {
          return -f1.distance_to(f2);
      }

      template <class Facade1, class Facade2>
      static typename Facade2::difference_type distance_from(
          Facade1 const& f1, Facade2 const& f2, mpl::false_)
      {
          return f2.distance_to(f1);
      }

      //
      // Curiously Recurring Template interface.
      //
      template <class I, class V, class TC, class R, class D>
      static I& derived(iterator_facade<I,V,TC,R,D>& facade)
      {
          return *static_cast<I*>(&facade);
      }

      template <class I, class V, class TC, class R, class D>
      static I const& derived(iterator_facade<I,V,TC,R,D> const& facade)
      {
          return *static_cast<I const*>(&facade);
      }

   private:
      // objects of this class are useless
      iterator_core_access(); //undefined
  };

  //
  // iterator_facade - use as a public base class for defining new
  // standard-conforming iterators.
  //
  template <
      class Derived             // The derived iterator type being constructed
    , class Value
    , class CategoryOrTraversal
    , class Reference   = Value&
    , class Difference  = std::ptrdiff_t
  >
  class iterator_facade
# ifdef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
    : public boost::detail::iterator_facade_types<
         Value, CategoryOrTraversal, Reference, Difference
      >::base
#  undef BOOST_ITERATOR_FACADE_NEEDS_ITERATOR_BASE
# endif
  {
   private:
      //
      // Curiously Recurring Template interface.
      //
      Derived& derived()
      {
          return *static_cast<Derived*>(this);
      }

      Derived const& derived() const
      {
          return *static_cast<Derived const*>(this);
      }

      typedef boost::detail::iterator_facade_types<
         Value, CategoryOrTraversal, Reference, Difference
      > associated_types;

      typedef boost::detail::operator_arrow_dispatch<
          Reference
        , typename associated_types::pointer
      > operator_arrow_dispatch_;

   protected:
      // For use by derived classes
      typedef iterator_facade<Derived,Value,CategoryOrTraversal,Reference,Difference> iterator_facade_;
      
   public:

      typedef typename associated_types::value_type value_type;
      typedef Reference reference;
      typedef Difference difference_type;

      typedef typename operator_arrow_dispatch_::result_type pointer;

      typedef typename associated_types::iterator_category iterator_category;

      reference operator*() const
      {
          return iterator_core_access::dereference(this->derived());
      }

      pointer operator->() const
      {
          return operator_arrow_dispatch_::apply(*this->derived());
      }
        
      typename boost::detail::operator_brackets_result<Derived,Value,reference>::type
      operator[](difference_type n) const
      {
          typedef boost::detail::use_operator_brackets_proxy<Value,Reference> use_proxy;
          
          return boost::detail::make_operator_brackets_result<Derived>(
              this->derived() + n
            , use_proxy()
          );
      }

      Derived& operator++()
      {
          iterator_core_access::increment(this->derived());
          return this->derived();
      }

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      typename boost::detail::postfix_increment_result<Derived,Value,Reference,CategoryOrTraversal>::type
      operator++(int)
      {
          typename boost::detail::postfix_increment_result<Derived,Value,Reference,CategoryOrTraversal>::type
          tmp(this->derived());
          ++*this;
          return tmp;
      }
# endif
      
      Derived& operator--()
      {
          iterator_core_access::decrement(this->derived());
          return this->derived();
      }

      Derived operator--(int)
      {
          Derived tmp(this->derived());
          --*this;
          return tmp;
      }

      Derived& operator+=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), n);
          return this->derived();
      }

      Derived& operator-=(difference_type n)
      {
          iterator_core_access::advance(this->derived(), -n);
          return this->derived();
      }

      Derived operator-(difference_type x) const
      {
          Derived result(this->derived());
          return result -= x;
      }

# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      // There appears to be a bug which trashes the data of classes
      // derived from iterator_facade when they are assigned unless we
      // define this assignment operator.  This bug is only revealed
      // (so far) in STLPort debug mode, but it's clearly a codegen
      // problem so we apply the workaround for all MSVC6.
      iterator_facade& operator=(iterator_facade const&)
      {
          return *this;
      }
# endif
  };

# if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
  template <class I, class V, class TC, class R, class D>
  inline typename boost::detail::postfix_increment_result<I,V,R,TC>::type
  operator++(
      iterator_facade<I,V,TC,R,D>& i
    , int
  )
  {
      typename boost::detail::postfix_increment_result<I,V,R,TC>::type
          tmp(*static_cast<I*>(&i));
      
      ++i;
      
      return tmp;
  }
# endif 

  
  //
  // Comparison operator implementation. The library supplied operators
  // enables the user to provide fully interoperable constant/mutable
  // iterator types. I.e. the library provides all operators
  // for all mutable/constant iterator combinations.
  //
  // Note though that this kind of interoperability for constant/mutable
  // iterators is not required by the standard for container iterators.
  // All the standard asks for is a conversion mutable -> constant.
  // Most standard library implementations nowadays provide fully interoperable
  // iterator implementations, but there are still heavily used implementations
  // that do not provide them. (Actually it's even worse, they do not provide
  // them for only a few iterators.)
  //
  // ?? Maybe a BOOST_ITERATOR_NO_FULL_INTEROPERABILITY macro should
  //    enable the user to turn off mixed type operators
  //
  // The library takes care to provide only the right operator overloads.
  // I.e.
  //
  // bool operator==(Iterator,      Iterator);
  // bool operator==(ConstIterator, Iterator);
  // bool operator==(Iterator,      ConstIterator);
  // bool operator==(ConstIterator, ConstIterator);
  //
  //   ...
  //
  // In order to do so it uses c++ idioms that are not yet widely supported
  // by current compiler releases. The library is designed to degrade gracefully
  // in the face of compiler deficiencies. In general compiler
  // deficiencies result in less strict error checking and more obscure
  // error messages, functionality is not affected.
  //
  // For full operation compiler support for "Substitution Failure Is Not An Error"
  // (aka. enable_if) and boost::is_convertible is required.
  //
  // The following problems occur if support is lacking.
  //
  // Pseudo code
  //
  // ---------------
  // AdaptorA<Iterator1> a1;
  // AdaptorA<Iterator2> a2;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if or is_convertible is not supported
  // // The instantiation will fail with an error hopefully indicating that
  // // there is no operator== for Iterator1, Iterator2
  // // The same will happen if no enable_if is used to remove
  // // false overloads from the templated conversion constructor
  // // of AdaptorA.
  //
  // a1 == a2;
  // ----------------
  //
  // AdaptorA<Iterator> a;
  // AdaptorB<Iterator> b;
  //
  // // This will result in a no such overload error in full operation
  // // If enable_if is not supported the static assert used
  // // in the operator implementation will fail.
  // // This will accidently work if is_convertible is not supported.
  //
  // a == b;
  // ----------------
  //

# ifdef BOOST_NO_ONE_WAY_ITERATOR_INTEROP
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) mpl::true_()
# else
#  define BOOST_ITERATOR_CONVERTIBLE(a,b) is_convertible<a,b>()
# endif

# define BOOST_ITERATOR_FACADE_INTEROP(op, result_type, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP_HEAD(inline, op, result_type)                   \
  {                                                                             \
      /* For those compilers that do not support enable_if */                   \
      BOOST_STATIC_ASSERT((                                                     \
          is_interoperable< Derived1, Derived2 >::value                         \
      ));                                                                       \
      return_prefix iterator_core_access::base_op(                              \
          *static_cast<Derived1 const*>(&lhs)                                   \
        , *static_cast<Derived2 const*>(&rhs)                                   \
        , BOOST_ITERATOR_CONVERTIBLE(Derived2,Derived1)                         \
      );                                                                        \
  }

# define BOOST_ITERATOR_FACADE_RELATION(op, return_prefix, base_op) \
  BOOST_ITERATOR_FACADE_INTEROP(                                    \
      op                                                            \
    , boost::detail::always_bool2                                   \
    , return_prefix                                                 \
    , base_op                                                       \
  )

  BOOST_ITERATOR_FACADE_RELATION(==, return, equal)
  BOOST_ITERATOR_FACADE_RELATION(!=, return !, equal)

  BOOST_ITERATOR_FACADE_RELATION(<, return 0 >, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(>, return 0 <, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(<=, return 0 >=, distance_from)
  BOOST_ITERATOR_FACADE_RELATION(>=, return 0 <=, distance_from)
# undef BOOST_ITERATOR_FACADE_RELATION

  // operator- requires an additional part in the static assertion
  BOOST_ITERATOR_FACADE_INTEROP(
      -
    , boost::detail::choose_difference_type
    , return
    , distance_from
  )
# undef BOOST_ITERATOR_FACADE_INTEROP
# undef BOOST_ITERATOR_FACADE_INTEROP_HEAD

# define BOOST_ITERATOR_FACADE_PLUS(args)           \
  BOOST_ITERATOR_FACADE_PLUS_HEAD(inline, args)     \
  {                                                 \
      Derived tmp(static_cast<Derived const&>(i));  \
      return tmp += n;                              \
  }

BOOST_ITERATOR_FACADE_PLUS((
  iterator_facade<Derived, V, TC, R, D> const& i
  , typename Derived::difference_type n
))

BOOST_ITERATOR_FACADE_PLUS((
    typename Derived::difference_type n
    , iterator_facade<Derived, V, TC, R, D> const& i
))

template <class Iterator, class T>
void readable_iterator_traversal_test(Iterator i1, T v, mpl::true_)
{
    T v2(*i1++);
    BOOST_TEST(v == v2);
}


template <class Iterator, class T>
void writable_iterator_traversal_test(Iterator i1, T v, mpl::true_)
{
    ++i1;  // we just wrote into that position
    *i1++ = v;
    Iterator x(i1++);
    (void)x;
}

template <class Iterator, class T>
void readable_iterator_test(const Iterator i1, T v)
{
  Iterator i2(i1); // Copy Constructible
  typedef typename detail::iterator_traits<Iterator>::reference ref_t;
  ref_t r1 = *i1;
  ref_t r2 = *i2;
  T v1 = r1;
  T v2 = r2;
  BOOST_TEST(v1 == v);
  BOOST_TEST(v2 == v);

# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
  readable_iterator_traversal_test(i1, v, detail::is_postfix_incrementable<Iterator>());
      
  // I think we don't really need this as it checks the same things as
  // the above code.
  BOOST_STATIC_ASSERT(is_readable_iterator<Iterator>::value);
# endif 
}


template <class Iterator, class T>
void writable_iterator_test(Iterator i, T v, T v2)
{
  Iterator i2(i); // Copy Constructible
  *i2 = v;

# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
  writable_iterator_traversal_test(
      i, v2, mpl::and_<
          detail::is_incrementable<Iterator>
        , detail::is_postfix_incrementable<Iterator>
      >());
# endif 
}


template <class Iterator>
void swappable_iterator_test(Iterator i, Iterator j)
{
  Iterator i2(i), j2(j);
  typename detail::iterator_traits<Iterator>::value_type bi = *i, bj = *j;
  iter_swap(i2, j2);
  typename detail::iterator_traits<Iterator>::value_type ai = *i, aj = *j;
  BOOST_TEST(bi == aj && bj == ai);
}


template <class Iterator, class T>
void constant_lvalue_iterator_test(Iterator i, T v1)
{
  Iterator i2(i);
  typedef typename detail::iterator_traits<Iterator>::value_type value_type;
  typedef typename detail::iterator_traits<Iterator>::reference reference;
  BOOST_STATIC_ASSERT((is_same<const value_type&, reference>::value));
  const T& v2 = *i2;
  BOOST_TEST(v1 == v2);
# ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  BOOST_STATIC_ASSERT(is_lvalue_iterator<Iterator>::value);
  BOOST_STATIC_ASSERT(!is_non_const_lvalue_iterator<Iterator>::value);
# endif 
}


template <class Iterator, class T>
void non_const_lvalue_iterator_test(Iterator i, T v1, T v2)
{
  Iterator i2(i);
  typedef typename detail::iterator_traits<Iterator>::value_type value_type;
  typedef typename detail::iterator_traits<Iterator>::reference reference;
  BOOST_STATIC_ASSERT((is_same<value_type&, reference>::value));
  T& v3 = *i2;
  BOOST_TEST(v1 == v3);
  
  // A non-const lvalue iterator is not neccessarily writable, but we
  // are assuming the value_type is assignable here
  *i = v2;
  
  T& v4 = *i2;
  BOOST_TEST(v2 == v4);
# ifndef BOOST_NO_LVALUE_RETURN_DETECTION
  BOOST_STATIC_ASSERT(is_lvalue_iterator<Iterator>::value);
  BOOST_STATIC_ASSERT(is_non_const_lvalue_iterator<Iterator>::value);
# endif 
}


template <class Iterator, class T>
void forward_readable_iterator_test(Iterator i, Iterator j, T val1, T val2)
{
  Iterator i2;
  Iterator i3(i);
  i2 = i;
  BOOST_TEST(i2 == i3);
  BOOST_TEST(i != j);
  BOOST_TEST(i2 != j);
  readable_iterator_test(i, val1);
  readable_iterator_test(i2, val1);
  readable_iterator_test(i3, val1);

  BOOST_TEST(i == i2++);
  BOOST_TEST(i != ++i3);

  readable_iterator_test(i2, val2);
  readable_iterator_test(i3, val2);

  readable_iterator_test(i, val1);
}


template <class Iterator, class T>
void forward_swappable_iterator_test(Iterator i, Iterator j, T val1, T val2)
{
  forward_readable_iterator_test(i, j, val1, val2);
  Iterator i2 = i;
  ++i2;
  swappable_iterator_test(i, i2);
}

template <class Iterator, class T>
void bidirectional_readable_iterator_test(Iterator i, T v1, T v2)
{
  Iterator j(i);
  ++j;
  forward_readable_iterator_test(i, j, v1, v2);
  ++i;

  Iterator i1 = i, i2 = i;

  BOOST_TEST(i == i1--);
  BOOST_TEST(i != --i2);

  readable_iterator_test(i, v2);
  readable_iterator_test(i1, v1);
  readable_iterator_test(i2, v1);

  --i;
  BOOST_TEST(i == i1);
  BOOST_TEST(i == i2);
  ++i1;
  ++i2;

  readable_iterator_test(i, v1);
  readable_iterator_test(i1, v2);
  readable_iterator_test(i2, v2);
}

template <class Iterator, class TrueVals>
void random_access_readable_iterator_test(Iterator i, int N, TrueVals vals)
{
  bidirectional_readable_iterator_test(i, vals[0], vals[1]);
  const Iterator j = i;
  int c;

  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == j + c);
    BOOST_TEST(*i == vals[c]);
    typename detail::iterator_traits<Iterator>::value_type x = j[c];
    BOOST_TEST(*i == x);
    BOOST_TEST(*i == *(j + c));
    BOOST_TEST(*i == *(c + j));
    ++i;
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
  }

  Iterator k = j + N - 1;
  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == k - c);
    BOOST_TEST(*i == vals[N - 1 - c]);
    typename detail::iterator_traits<Iterator>::value_type x = j[N - 1 - c];
    BOOST_TEST(*i == x);
    Iterator q = k - c; 
    BOOST_TEST(*i == *q);
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
    --i;
  }
}

    transform_iterator() { }


    transform_iterator(Iterator const& x, UnaryFunc f)
      : super_t(x), m_f(f) { }


    explicit transform_iterator(Iterator const& x)
      : super_t(x)
    {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
        // don't provide this constructor if UnaryFunc is a
        // function pointer type, since it will be 0.  Too dangerous.
        BOOST_STATIC_ASSERT(is_class<UnaryFunc>::value);
#endif 
    }


    UnaryFunc functor() const
      { return m_f; }

    typename super_t::reference dereference() const
    { return m_f(*this->base()); }


  template <class UnaryFunc, class Iterator>
  transform_iterator<UnaryFunc, Iterator>
  make_transform_iterator(Iterator it, UnaryFunc fun)
  {
      return transform_iterator<UnaryFunc, Iterator>(it, fun);
  }
