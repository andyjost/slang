
  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return static_cast<RET>(a1);
  }

  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return dynamic_cast<RET>(a1);
  }

  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return const_cast<RET>(a1);
  }

  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return reinterpret_cast<RET>(a1);
  }

  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    detail::suppress_unused_variable_warnings(a1);
    return typeid(a1);
  }

  template<class RET, class Arg1>
  static RET apply(Arg1 &a1) {
    return sizeof(a1);
  }


  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::for_each(a, b, c); }


  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::find(a, b, c); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::find_if(a, b, c); }


  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return ::std::find_end(a, b, c, d); }


  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::find_end(a, b, c, d, e); }


  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return ::std::find_first_of(a, b, c, d); }


  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::find_first_of(a, b, c, d, e); }


  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::adjacent_find(a, b); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::adjacent_find(a, b, c); }


  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::equal(a, b, c); }


  template <class A, class C, class D>
  bool
  operator()(A a, A b, C c, D d) const
  { return ::std::equal(a, b, c, d); }


  template <class A, class C>
  A
  operator()(A a, A b, C c, C d) const
  { return std::search(a, b, c, d);}


  template <class A, class C, class E>
  A
  operator()(A a, A b, C c, C d, E e) const
  { return std::search(a, b, c, d, e);}


  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::copy(a, b, c); }


  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::copy_backward(a, b, c); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::swap(a, b); }


  template <class A, class C>
  C
  operator()(A a, A b, C c) const
  { return ::std::swap_ranges(a, b, c); }


  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::iter_swap(a, b); }


  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, D d) const
  { return std::transform(a, b, c, d);}


  template <class A, class C, class D, class E>
  D
  operator()(A a, A b, C c, D d, E e) const
  { return std::transform(a, b, c, d, e);}


  template <class A, class C>
  void
  operator()(A a, A b, const C& c, const C& d) const
  { ::std::replace(a, b, c, d); }


  template <class A, class C, class D>
  void
  operator()(A a, A b, C c, const D& d) const
  { ::std::replace_if(a, b, c, d); }


  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, const D& d, const D& e) const
  { return ::std::replace_copy(a, b, c, d, e); }


  template <class A, class C, class D, class E>
  C
  operator()(A a, A b, C c, D d, const E& e) const
  { return ::std::replace_copy_if(a, b, c, d, e); }


  template <class A, class C>
  void 
  operator()(A a, A b, const C& c) const
  { ::std::fill(a, b, c); }


  template <class A, class B, class C>
  void 
  operator()(A a, B b, const C& c) const
  { ::std::fill_n(a, b, c); }


  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::generate(a, b, c); }


  template <class A, class B, class C>
  void 
  operator()(A a, B b, C c) const
  { ::std::generate_n(a, b, c); }


  template <class A, class C >
  A
  operator()(A a, A b, const C& c) const
  { return ::std::remove(a, b, c); }


  template <class A, class C >
  A
  operator()(A a, A b, C c) const
  { return ::std::remove_if(a, b, c); }


  template <class A, class C, class D >
  C
  operator()(A a, A b, C c, const D& d) const
  { return ::std::remove_copy(a, b, c, d); }


  template <class A, class C, class D >
  C
  operator()(A a, A b, C c, D d) const
  { return ::std::remove_copy_if(a, b, c, d); }


  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::unique(a, b); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::unique(a, b, c); }


  template <class A, class C >
  C
  operator()(A a, A b, C c) const
  { return ::std::unique_copy(a, b, c); }


  template <class A, class C, class D>
  C
  operator()(A a, A b, C c, D d) const
  { return ::std::unique_copy(a, b, c, d); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::reverse(a, b); }


  template <class A, class C >
  C
  operator()(A a, A b, C c) const
  { return ::std::reverse_copy(a, b, c); }


  template <class A>
  void
  operator()(A a, A b, A c) const
  { ::std::rotate(a, b, c); }


  template <class A, class D>
  D
  operator()(A a, A b, A c, D d) const
  { return ::std::rotate_copy(a, b, c, d); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::random_shuffle(a, b); }


  template <class A, class C>
  void
  operator()(A a, A b, const C& c) const
  { ::std::random_shuffle(a, b, c); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::partition(a, b, c); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::stable_partition(a, b, c); }


  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::sort(a, b); }


  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::sort(a, b, c); }


  template <class A>
  void 
  operator()(A a, A b) const
  { ::std::stable_sort(a, b); }


  template <class A, class C>
  void 
  operator()(A a, A b, C c) const
  { ::std::stable_sort(a, b, c); }


  template <class A>
  void 
  operator()(A a, A b, A c) const
  { ::std::partial_sort(a, b, c); }


  template <class A, class D>
  void 
  operator()(A a, A b, A c, D d) const
  { ::std::partial_sort(a, b, c, d); }


  template <class A, class C>
  C
  operator()(A a, A b, C c, C d) const
  { return ::std::partial_sort_copy(a, b, c, d); }


  template <class A, class C, class E >
  C
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::partial_sort_copy(a, b, c, d, e); }


  template <class A>
  void 
  operator()(A a, A b, A c) const
  { ::std::nth_element(a, b, c); }


  template <class A, class D>
  void 
  operator()(A a, A b, A c, D d) const
  { ::std::nth_element(a, b, c, d); }


  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::lower_bound(a, b, c); }


  template <class A, class C, class D>
  A
  operator()(A a, A b, const C& c, D d) const
  { return ::std::lower_bound(a, b, c, d); }


  template <class A, class C>
  A
  operator()(A a, A b, const C& c) const
  { return ::std::upper_bound(a, b, c); }


  template <class A, class C, class D>
  A
  operator()(A a, A b, const C& c, D d) const
  { return ::std::upper_bound(a, b, c, d); }


  template <class A, class C >
  bool
  operator()(A a, A b, const C& c) const
  { return ::std::binary_search(a, b, c); }


  template <class A, class C, class D>
  bool
  operator()(A a, A b, const C& c, D d) const
  { return ::std::binary_search(a, b, c, d); }


  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::merge(a, b, c, d, e);}


  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::merge(a, b, c, d, e, f);}


  template <class A>
  void
  operator()(A a, A b, A c) const
  { ::std::inplace_merge(a, b, c); }


  template <class A, class D>
  void
  operator()(A a, A b, A c, D d) const
  { ::std::inplace_merge(a, b, c, d); }


  template <class A, class C>
  bool
  operator()(A a, A b, C c, C d) const
  { return ::std::includes(a, b, c, d); }


  template <class A, class C, class E>
  bool
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::includes(a, b, c, d, e); }


  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_union(a, b, c, d, e);}


  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_union(a, b, c, d, e, f);}


  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_intersection(a, b, c, d, e);}


  template <class A, class C, class E, class F>
  E
  operator()(A a,  A b, C c, C d, E e, F f) const
  { return std::set_intersection(a, b, c, d, e, f);}


  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_difference(a, b, c, d, e);}


  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_difference(a, b, c, d, e, f);}


  template <class A, class C, class E>
  E
  operator()(A a, A b, C c, C d, E e) const
  { return std::set_symmetric_difference(a, b, c, d, e);}


  template <class A, class C, class E, class F>
  E
  operator()(A a, A b, C c, C d, E e, F f) const
  { return std::set_symmetric_difference(a, b, c, d, e, f);}


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::push_heap(a, b); }


  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::push_heap(a, b, c); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::pop_heap(a, b); }


  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::pop_heap(a, b, c); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::make_heap(a, b); }


  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::make_heap(a, b, c); }


  template <class A>
  void
  operator()(A a, A b) const
  { ::std::sort_heap(a, b); }


  template <class A, class C>
  void
  operator()(A a, A b, C c) const
  { ::std::sort_heap(a, b, c); }


  template <class A>
  A
  operator()(const A& a, const A& b) const
  { return (::std::min)(a, b); }


  template <class A, class C>
  A
  operator()(const A& a, const A& b, C c) const
  { return (::std::min)(a, b, c); }


  template <class A>
  A
  operator()(const A& a, const A& b) const
  { return (::std::max)(a, b); }


  template <class A, class C>
  A
  operator()(const A& a, const A& b, C c) const
  { return (::std::max)(a, b, c); }


  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::min_element(a, b); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::min_element(a, b, c); }


  template <class A>
  A
  operator()(A a, A b) const
  { return ::std::max_element(a, b); }


  template <class A, class C>
  A
  operator()(A a, A b, C c) const
  { return ::std::max_element(a, b, c); }


  template <class A, class C>
  bool
  operator()(A a, A b, C c, C d) const
  { return ::std::lexicographical_compare(a, b, c, d); }


  template <class A, class C, class E>
  bool
  operator()(A a, A b, C c, C d, E e) const
  { return ::std::lexicographical_compare(a, b, c, d, e); }


  template <class A>
  bool
  operator()(A a, A b) const
  { return ::std::next_permutation(a, b); }


  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::next_permutation(a, b, c); }


  template <class A>
  bool
  operator()(A a, A b) const
  { return ::std::prev_permutation(a, b); }


  template <class A, class C >
  bool
  operator()(A a, A b, C c) const
  { return ::std::prev_permutation(a, b, c); }
                                                       \
                                                           \
  template<class T>                                        \
  typename T::const_iterator                               \
  operator()(const T& t) const                             \
  {                                                        \
    return t.X();                                          \
  }                                                        \
};

// create call_begin and call_end classes
CALL_MEMBER(begin)
                                                       \
                                                           \
  template<class T>                                        \
  typename T::const_iterator                               \
  operator()(const T& t) const                             \
  {                                                        \
    return t.X();                                          \
  }                                                        \
};

// create call_begin and call_end classes
CALL_MEMBER(begin)
CALL_MEMBER(end)


    closure_frame(ClosureT& clos)
    : ClosureT::tuple_t(), save(clos.frame), frame(clos.frame)
    { clos.frame = this; }


    template <typename TupleT>
    closure_frame(ClosureT& clos, TupleT const& init)
    : ClosureT::tuple_t(init), save(clos.frame), frame(clos.frame)
    { clos.frame = this; }


    ~closure_frame()
    { frame = save; }


    closure_member()
    : frame(ClosureT::closure_frame_ref()) {}


    template <class Ret, class A, class B, class C>
    //    typename detail::tuple_element_as_reference
    //        <N, typename ClosureT::tuple_t>::type
    Ret
    call(A&, B&, C&) const
    {
        assert(frame);
        return boost::tuples::get<N>(*frame);
    }


                            closure()
                            : frame(0)      { closure_frame_ref(&frame); }

    closure_frame_t&        context()       { assert(frame); return frame; }

    closure_frame_t const&  context() const { assert(frame); return frame; }


    static closure_frame_t*&
    closure_frame_ref(closure_frame_t** frame_ = 0)
    {
        static closure_frame_t** frame = 0;
        if (frame_ != 0)
            frame = frame_;
        return *frame;
    }


  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::accumulate(a, b, c); }


  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::accumulate(a, b, c, d); }


  template <class A, class B, class C, class D>
  D
  operator()(A a, B b, C c, D d) const
  { return ::std::inner_product(a, b, c, d); }


  template <class A, class B, class C, class D, class E, class F>
  D
  operator()(A a, B b, C c, D d, E e, F f) const
  { return ::std::inner_product(a, b, c, d, e, f); }


  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::partial_sum(a, b, c); }


  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::partial_sum(a, b, c, d); }


  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::adjacent_difference(a, b, c); }


  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::adjacent_difference(a, b, c, d); }

  explicit lambda_functor_base(const Args& a) : args(a) {}


  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    if (detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)) 
      detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
  }


    if_then_else_composite(
        CondT const& cond_,
        ThenT const& then_,
        ElseT const& else__)
    :   cond(cond_), then(then_), else_(else__) {}


    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        if (cond.internal_call(CALL_ACTUAL_ARGS))
            then.internal_call(CALL_ACTUAL_ARGS);
        else
            else_.internal_call(CALL_ACTUAL_ARGS);
    }


    else_gen(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_) {}


    if_then_composite(CondT const& cond_, ThenT const& then_)
    :   cond(cond_), then(then_), else_(cond, then) {}


    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
      if (cond.internal_call(CALL_ACTUAL_ARGS))
            then.internal_call(CALL_ACTUAL_ARGS);
    }


    if_gen(CondT const& cond_)
    :   cond(cond_) {}

template <typename CondT>
inline if_gen<CondT>
if_(CondT const& cond)
{
    return if_gen<CondT>(cond);
}

  template<class RET>
  static RET apply() {
    throw;
  }

  template<class RET, class T>
  static RET apply(T& t) {
    throw t;
  }

  template<class RET, class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS) {
    BOOST_STATIC_ASSERT(throws_for_sure<Arg>::value);
    detail::select(arg, CALL_ACTUAL_ARGS); // this line throws
    throw 1; // this line is never performed, hence 1 is just a dummy
             // The line is needed to make compiler happy and not require
             // a matching return type
  }

  template<class RET, class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS) {
    return detail::select(arg, CALL_ACTUAL_ARGS);
  }

  template<class Arg, CALL_TEMPLATE_ARGS>
  static RET call(Arg& arg, CALL_FORMAL_ARGS)
  {        
    //    typedef typename Arg::return_type<ARG, open_args<A&, B&, C&> >::type RT;        
    typedef typename as_lambda_functor<ARG>::type lf_type;
    typedef typename lf_type::inherited::template 
      sig<tuple<CALL_REFERENCE_TYPES> >::type RT;  

    return 
      return_or_throw_phase2<
        ::boost::is_convertible<RT, RET>::value
      >::template call<RET>(arg, CALL_ACTUAL_ARGS);
  }

  template<class Arg, CALL_TEMPLATE_ARGS>
  static void call(Arg& arg, CALL_FORMAL_ARGS) { detail::select(arg, CALL_ACTUAL_ARGS); }

  explicit lambda_functor_base(const Args& a) : args(a) {}


  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    for(detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
        detail::select(boost::tuples::get<2>(args), CALL_ACTUAL_ARGS)) {}
   }


    while_composite(CondT const& cond_, DoT const& do__)
    :   cond(cond_), do_(do__) {}


    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        while (cond.internal_call(CALL_ACTUAL_ARGS))
            do_.internal_call(CALL_ACTUAL_ARGS);
    }


    while_gen(CondT const& cond_)
    :   cond(cond_) {}

template <typename CondT>
inline while_gen<CondT>
while_(CondT const& cond)
{
    return while_gen<CondT>(cond);
}


    do_composite(DoT const& do__, CondT const& cond_)
    :   do_(do__), cond(cond_) {}


    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret call(CALL_FORMAL_ARGS) const
    {
        do
            do_.internal_call(CALL_ACTUAL_ARGS);
        while (cond.internal_call(CALL_ACTUAL_ARGS));
    }


    do_gen2(DoT const& do__)
    :   do_(do__) {}


    template <typename DoT>
    do_gen2<DoT>
    operator[](DoT const& do_) const
    {
        return do_gen2<DoT>(do_);
    }


    for_composite(
        InitT const& init_,
        CondT const& cond_,
        StepT const& step_,
        DoT const& do__)
    :   init(init_), cond(cond_), step(step_), do_(do__) {}


    template <class Ret, CALL_TEMPLATE_ARGS>
    Ret
    call(CALL_FORMAL_ARGS) const
    {
        for (init.internal_call(CALL_ACTUAL_ARGS); cond.internal_call(CALL_ACTUAL_ARGS); step.internal_call(CALL_ACTUAL_ARGS))
            do_.internal_call(CALL_ACTUAL_ARGS);
    }


    for_gen(
        InitT const& init_,
        CondT const& cond_,
        StepT const& step_)
    :   init(init_), cond(cond_), step(step_) {}

template <typename InitT, typename CondT, typename StepT>
inline for_gen<InitT, CondT, StepT>
for_(InitT const& init, CondT const& cond, StepT const& step)
{
    return for_gen<InitT, CondT, StepT>(init, cond, step);
}


  T operator()() const {
    return T();
  }


  template<class A1>
  T operator()(A1& a1) const {
    return T(a1);
  }


  template<class A1, class A2>
  T operator()(A1& a1, A2& a2) const {
    return T(a1, a2);
  }


  template<class A1, class A2, class A3>
  T operator()(A1& a1, A2& a2, A3& a3) const {
    return T(a1, a2, a3);
  }


  template<class A1, class A2, class A3, class A4>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return T(a1, a2, a3, a4);
  }


  template<class A1, class A2, class A3, class A4, class A5>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return T(a1, a2, a3, a4, a5);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return T(a1, a2, a3, a4, a5, a6);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return T(a1, a2, a3, a4, a5, a6, a7);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }


  template<class A1>
  static void exec(A1& a1) {
    // remove all the qualifiers, not sure whether it is necessary
    typedef typename boost::remove_cv<A1>::type plainA1;
     a1.~plainA1();
  }


  template<class A1>
  static void exec(A1* a1) {
    typedef typename boost::remove_cv<A1>::type plainA1;
    (*a1).~plainA1();
  }
  

  template<class A1>
  void operator()(A1& a1) const {
    typedef typename boost::remove_cv<A1>::type plainA1;
    detail::destructor_helper<boost::is_pointer<plainA1>::value>::exec(a1);
  }
  

  T* operator()() const {
    return new T();
  }


  template<class A1>
  T* operator()(A1& a1) const {
    return new T(a1);
  }


  template<class A1, class A2>
  T* operator()(A1& a1, A2& a2) const {
    return new T(a1, a2);
  }


  template<class A1, class A2, class A3>
  T* operator()(A1& a1, A2& a2, A3& a3) const {
    return new T(a1, a2, a3);
  }


  template<class A1, class A2, class A3, class A4>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4) const {
    return new T(a1, a2, a3, a4);
  }


  template<class A1, class A2, class A3, class A4, class A5>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) const {
    return new T(a1, a2, a3, a4, a5);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) const {
    return new T(a1, a2, a3, a4, a5, a6);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) const {
    return new T(a1, a2, a3, a4, a5, a6, a7);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }


  template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
  T* operator()(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9, A10& a10) const {
    return new T(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }
  

  template <class A1>
  void operator()(A1& a1) const {
    delete a1;
  }
  

  T* operator()(int size) const {
    return new T[size];
  }
  

  template <class A1>
  void operator()(A1& a1) const {
    delete[] a1;
  }

  template<class RET, class A1>
  static RET apply(A1& a1) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1);
  }

  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2);
  }

  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3);
  }

  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5,  
           class A6, class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, 
           class A6, class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, 
                   A8& a8, A9& a9, A10& a10) {
    return function_adaptor<typename boost::remove_cv<A1>::type>::
      template apply<RET>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }


  lambda_functor() {}

  lambda_functor(const lambda_functor& l) : inherited(l) {}


  lambda_functor(const T& t) : inherited(t) {}


  nullary_return_type operator()() const { 
    return inherited::template 
      call<nullary_return_type>
        (cnull_type(), cnull_type(), cnull_type(), cnull_type()); 
  }

   
template <class T> inline const T&  make_const(const T& t) { return t; }


template<class T>
inline void suppress_unused_variable_warnings(const T&) {}


  template<class RET, class A1>
  static RET apply(A1& a1) {
    return a1();
  }

  template<class RET, class A1, class A2>
  static RET apply(A1& a1, A2& a2) {
    return a1(a2);
  }

  template<class RET, class A1, class A2, class A3>
  static RET apply(A1& a1, A2& a2, A3& a3) {
    return a1(a2, a3);
  }

  template<class RET, class A1, class A2, class A3, class A4>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4) {
    return a1(a2, a3, a4);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return a1(a2, a3, a4, a5);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return a1(a2, a3, a4, a5, a6);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7) {
    return a1(a2, a3, a4, a5, a6, a7);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8) {
    return a1(a2, a3, a4, a5, a6, a7, a8);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8, A9& a9) {
    return a1(a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template<class RET, class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9, class A10>
  static RET apply(A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, 
                           A7& a7, A8& a8, A9& a9, A10& a10) {
    return a1(a2, a3, a4, a5, a6, a7, a8, a9, a10);
  }


  template <class RET>
  static RET apply( T Object::*data, Object& o) {
    return o.*data;
  }

  template <class RET>
  static RET apply( T Object::*data, const Object& o) {
    return o.*data;
  }

  template <class RET>
  static RET apply( T Object::*data, volatile Object& o) {
    return o.*data;
  }

  template <class RET>
  static RET apply( T Object::*data, const volatile Object& o) {
    return o.*data;
  }

  template <class RET>
  static RET apply( T Object::*data, Object* o) {
    return o->*data;
  }

  template <class RET>
  static RET apply( T Object::*data, const Object* o) {
    return o->*data;
  }

  template <class RET>
  static RET apply( T Object::*data, volatile Object* o) {
    return o->*data;
  }

  template <class RET>
  static RET apply( T Object::*data, const volatile Object* o) {
    return o->*data;
  }

  template <class RET>
  static Result apply(Result (*func)()) {
    return func();
  }

  template <class RET>
  static Result apply(Result (*func)()) {
    return func();
  }

  template <class RET>
  static Result apply( Result (Object::*func)() const, const Object* o) {
    return (o->*func)();
  }

  template <class RET>
  static Result apply( Result (Object::*func)() const, const Object& o) {
    return (o.*func)();
  }

  template <class RET>
  static Result apply( Result (Object::*func)(), Object* o) {
    return (o->*func)();
  }

  template <class RET>
  static Result apply( Result (Object::*func)(), Object& o) {
    return (o.*func)();
  }

  template <class RET, class A1>
  static Result apply(Result (*func)(Arg1), A1& a1) {
    return func(a1);
  }

  template <class RET, class A1>
  static Result apply(Result (*func)(Arg1), A1& a1) {
    return func(a1);
  }

  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1) const, const Object* o, 
    A1& a1) {
    return (o->*func)(a1);
  }

  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1) const, const Object& o, 
    A1& a1) {
    return (o.*func)(a1);
  }

  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1), Object* o, A1& a1) {
    return (o->*func)(a1);
  }

  template <class RET, class A1>
  static Result apply( Result (Object::*func)(Arg1), Object& o, A1& a1) {
    return (o.*func)(a1);
  }

  template <class RET, class A1, class A2>
  static Result apply(Result (*func)(Arg1, Arg2), A1& a1, A2& a2) {
    return func(a1, a2);
  }

  template <class RET, class A1, class A2>
  static Result apply(Result (*func)(Arg1, Arg2), A1& a1, A2& a2) {
    return func(a1, a2);
  }

  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2) const, const Object* o, A1& a1, A2& a2) {
    return (o->*func)(a1, a2);
  }

  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2) const, const Object& o, A1& a1, A2& a2) {
    return (o.*func)(a1, a2);
  }

  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2), Object* o, A1& a1, A2& a2) {
    return (o->*func)(a1, a2);
  }

  template <class RET, class A1, class A2>
  static Result apply( Result (Object::*func)(Arg1, Arg2), Object& o, A1& a1, A2& a2) {
    return (o.*func)(a1, a2);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3), A1& a1, A2& a2, A3& a3) {
    return func(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3), A1& a1, A2& a2, A3& a3) {
    return func(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3) const, const Object* o, A1& a1, A2& a2, A3& a3) {
    return (o->*func)(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3) const, const Object& o, A1& a1, A2& a2, A3& a3) {
    return (o.*func)(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3), Object* o, A1& a1, A2& a2, A3& a3) {
    return (o->*func)(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3), Object& o, A1& a1, A2& a2, A3& a3) {
    return (o.*func)(a1, a2, a3);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4), A1& a1, A2& a2, A3& a3, A4& a4) {
    return func(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4), A1& a1, A2& a2, A3& a3, A4& a4) {
    return func(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o->*func)(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o.*func)(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4), Object* o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o->*func)(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4), Object& o, A1& a1, A2& a2, A3& a3, A4& a4) {
    return (o.*func)(a1, a2, a3, a4);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return func(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return func(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o->*func)(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o.*func)(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o->*func)(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5) {
    return (o.*func)(a1, a2, a3, a4, a5);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return func(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return func(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o->*func)(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o.*func)(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o->*func)(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6) {
    return (o.*func)(a1, a2, a3, a4, a5, a6);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return func(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return func(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const, const Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) const, const Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), Object* o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o->*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
  static Result apply( Result (Object::*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8), Object& o, A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8) {
    return (o.*func)(a1, a2, a3, a4, a5, a6, a7, a8);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  template <class RET, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
  static Result apply(Result (*func)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9), A1& a1, A2& a2, A3& a3, A4& a4, A5& a5, A6& a6, A7& a7, A8& a8, A9& a9) {
    return func(a1, a2, a3, a4, a5, a6, a7, a8, a9);
  }

  member_pointer_caller(const A& aa, const B& bb) : a(aa), b(bb) {}


  RET operator()() const { return (a->*b)(); }
 

  template<class A1>
  RET operator()(const A1& a1) const { return (a->*b)(a1); }
 

  template<class A1, class A2>
  RET operator()(const A1& a1, const A2& a2) const { return (a->*b)(a1, a2); }
 

  template<class A1, class A2, class A3>
  RET operator()(const A1& a1, const A2& a2, const A3& a3) const { 
    return (a->*b)(a1, a2, a3); 
  }
 

  template<class A1, class A2, class A3, class A4>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, 
                 const A4& a4) const { 
    return (a->*b)(a1, a2, a3, a4); 
  }
 

  template<class A1, class A2, class A3, class A4, class A5>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5) const { 
    return (a->*b)(a1, a2, a3, a4, a5); 
  }
 

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6); 
  }
 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7); 
  }
 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7,
                 const A8& a8) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7, a8); 
  }
 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7,
                 const A8& a8, const A9& a9) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
  }


  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
    return a->*b; 
  }

  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
// not a built in member pointer operator, just call ->*
    return a->*b; 
  }


  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
    typedef typename ::boost::remove_cv<B>::type plainB;
    typedef typename detail::member_pointer<plainB>::type ret_t; 
    typedef typename ::boost::remove_cv<A>::type plainA;

    // we always strip cv:s to 
    // make the two routes (calling and type deduction)
    // to give the same results (and the const does not make any functional
    // difference)
    return detail::member_pointer_caller<ret_t, plainA, plainB>(a, b); 
  }

  template<class RET, class A, class B>
  static RET apply(A& a, B& b) {
    typedef typename 
      ::boost::remove_cv<B>::type plainB;

    return detail::member_pointer_action_helper<
        boost::is_pointer<A>::value && 
          detail::member_pointer<plainB>::is_data_member,
        boost::is_pointer<A>::value && 
          detail::member_pointer<plainB>::is_function_member
      >::template apply<RET>(a, b); 
    }

template<class Any, CALL_TEMPLATE_ARGS>
inline Any& select(Any& any, CALL_FORMAL_ARGS) { CALL_USE_ARGS; return any; }


template<class A1, class A2, class A3, class A4>
void do_nothing(A1&, A2&, A3&, A4&) {}


  explicit identity(par_t t) : elem(t) {}


  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const { CALL_USE_ARGS; return elem; }


  explicit lambda_functor_base(const Args& a) : args(a) {}



  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const 
  {
     CALL_USE_ARGS;
     return boost::tuples::get<0>(args);
  }


template <class Arg>
inline const Arg& unlambda(const Arg& a) { return a; }


  explicit const_parameter_lambda_functor(const LambdaFunctor& a) : lf(a) {}
