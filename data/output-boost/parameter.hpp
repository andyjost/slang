

  inline PyObject* unspecified_type()
  {
      static PyTypeObject unspecified = {
          PyObject_HEAD_INIT(NULL)
          0,                                /* ob_size        */
          "Boost.Parameter.Unspecified",    /* tp_name        */
          PyType_Type.tp_basicsize,         /* tp_basicsize   */
          0,                                /* tp_itemsize    */
          0,                                /* tp_dealloc     */
          0,                                /* tp_print       */
          0,                                /* tp_getattr     */
          0,                                /* tp_setattr     */
          0,                                /* tp_compare     */
          0,                                /* tp_repr        */
          0,                                /* tp_as_number   */
          0,                                /* tp_as_sequence */
          0,                                /* tp_as_mapping  */
          0,                                /* tp_hash        */
          0,                                /* tp_call        */
          0,                                /* tp_str         */
          0,                                /* tp_getattro    */
          0,                                /* tp_setattro    */
          0,                                /* tp_as_buffer   */
          Py_TPFLAGS_DEFAULT,               /* tp_flags       */
          0,                                /* tp_doc         */
      };

      if (unspecified.ob_type == 0)
      {
          unspecified.ob_type = &PyType_Type;
          PyType_Ready(&unspecified);
      }

      return (PyObject*)&unspecified;
  }

      static PyObject* convert(empty_tag)
      {
          return python_::xincref(unspecified_type());
      }

      template <class T>
      T const& operator,(T const& x) const
      {
          return x;
      }


  template <class Def, class F, class Iter, class End, class Keywords>
  void def_combination_aux0(
      Def def, F f, Iter, End, Keywords const& keywords, mpl::false_)
  {
      typedef typename mpl::deref<Iter>::type spec;
      typedef typename spec::keyword kw;

      def_combination_aux(
          def, f, typename mpl::next<Iter>::type(), End()
        , (
              keywords, boost::python::arg(kw::keyword_name())
          )
      );
  }


  inline void initialize_converter()
  {
      static python_::to_python_converter<empty_tag, empty_tag_to_python> x;
  }


  template <class Def, class F, class Iter, class End, class Keywords>
  void def_combination_aux(
      Def def, F f, Iter, End, Keywords const& keywords)
  {
      typedef typename mpl::deref<Iter>::type spec;

      typedef typename mpl::and_<
          typename spec::optimized_default
        , mpl::not_<typename spec::required>
      >::type optimized_default;
      
      def_combination_aux0(
          def, f, Iter(), End(), keywords, optimized_default()
      );
  }


  template <class Def, class F, class End, class Keywords>
  void def_combination_aux(
      Def def, F f, End, End, Keywords const& keywords)
  {
      def(f, keywords);
  }
 

  template <class Def, class F, class End>
  void def_combination_aux(
      Def def, F f, End, End, no_keywords const&)
  {
      def(f);
  }


  template <
      class Def, class Specs, class Bits, class Invoker
  >
  void def_combination(
      Def def, Specs*, Bits, Invoker*)
  {
      typedef typename mpl::fold<
          Specs
        , mpl::pair<mpl::vector0<>, Bits>
        , combinations_op<mpl::_2, mpl::_1>
      >::type combination0;

      typedef typename combination0::first combination;

      typedef typename mpl::apply_wrap1<
          Invoker, combination
      >::type invoker;

      def_combination_aux(
          def
        , &invoker::execute
        , typename mpl::begin<combination>::type()
        , typename mpl::end<combination>::type()
        , no_keywords()
      );
  }


  template <
      class Def, class Specs, class Bits, class End, class Invoker
  >
  void def_combinations(
      Def def, Specs*, Bits, End, Invoker*)
  {
      initialize_converter();

      def_combination(def, (Specs*)0, Bits(), (Invoker*)0);

      def_combinations(
          def
        , (Specs*)0
        , mpl::long_<Bits::value + 1>()
        , End()
        , (Invoker*)0
      );
  }


  template <
      class Def, class Specs, class End, class Invoker
  >
  void def_combinations(
      Def, Specs*, End, End, Invoker*)
  {}

      call_policies_as_options(CallPolicies const& call_policies)
        : call_policies(call_policies)
      {}


      CallPolicies const& policies() const
      {
          return call_policies;
      }


      char const* doc() const
      {
          return 0;
      }

      def_class(Class& cl, char const* name, Options options = Options())
        : cl(cl)
        , name(name)
        , options(options)
      {}


      template <class F>
      void def(F f, not_specified const*) const
      {
          cl.def(name, f);
      }


      template <class F>
      void def(F f, void const*) const
      {
          cl.def(name, f, options.doc(), options.policies());
      }

      
      template <class F>
      void operator()(F f) const
      {
          this->def(f, &options);
      }


      template <class F, class Keywords>
      void def(F f, Keywords const& keywords, not_specified const*) const
      {
          cl.def(name, f, keywords);
      }


      template <class F, class Keywords>
      void def(F f, Keywords const& keywords, void const*) const
      {
          cl.def(name, f, keywords, options.doc(), options.policies());
      }


      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          this->def(f, keywords, &options);
      }

      def_init(Class& cl, CallPolicies call_policies = CallPolicies())
        : cl(cl)
        , call_policies(call_policies)
      {}


      template <class F>
      void operator()(F f) const
      {
          cl.def(
              "__init__"
            , boost::python::make_constructor(f, call_policies)
          );
      }


      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          cl.def(
              "__init__"
            , boost::python::make_constructor(f, call_policies, keywords)
          );
      }

      def_function(char const* name)
        : name(name)
      {}

      
      template <class F>
      void operator()(F f) const
      {
          boost::python::def(name, f);
      }


      template <class F, class Keywords>
      void operator()(F f, Keywords const& keywords) const
      {
          boost::python::def(name, f, keywords);
      }


template <class M, class Signature>
void def(char const* name, Signature)
{
    typedef mpl::iterator_range<
        typename mpl::next<
            typename mpl::begin<Signature>::type
        >::type
      , typename mpl::end<Signature>::type
    > arg_types;

    typedef typename mpl::transform<
        typename M::keywords
      , arg_types
      , aux::make_arg_spec<mpl::_1, mpl::_2>
      , mpl::back_inserter<mpl::vector0<> >
    >::type arg_specs;

    typedef typename mpl::count_if<
        arg_specs
      , aux::is_optional<mpl::_1>
    >::type optional_arity;
    
    typedef typename mpl::front<Signature>::type result_type;
    typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

    aux::def_combinations(
        aux::def_function(name)
      , (arg_specs*)0
      , mpl::long_<0>()
      , mpl::long_<upper::value>()
      , (aux::make_invoker<M, result_type>*)0
    );
}


template <class M, class Class, class Signature>
void def(Class& cl, char const* name, Signature)
{
    typedef mpl::iterator_range<
        typename mpl::next<
            typename mpl::begin<Signature>::type
        >::type
      , typename mpl::end<Signature>::type
    > arg_types;

    typedef typename mpl::transform<
        typename M::keywords
      , arg_types
      , aux::make_arg_spec<mpl::_1, mpl::_2>
      , mpl::back_inserter<mpl::vector0<> >
    >::type arg_specs;

    typedef typename mpl::count_if<
        arg_specs
      , aux::is_optional<mpl::_1>
    >::type optional_arity;
    
    typedef typename mpl::front<Signature>::type result_type;
    typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

    aux::def_combinations(
        aux::def_class<Class>(cl, name)
      , (arg_specs*)0
      , mpl::long_<0>()
      , mpl::long_<upper::value>()
      , (aux::make_invoker<M, result_type>*)0
    );
}

    init(CallPolicies call_policies = CallPolicies())
      : call_policies(call_policies)
    {}


    template <class CallPolicies1>
    init<ParameterSpecs, CallPolicies1> 
    operator[](CallPolicies1 const& call_policies) const
    {
        return init<ParameterSpecs, CallPolicies1>(call_policies);
    }


    template <class Class>
    void visit_aux(Class& cl, mpl::true_) const
    {
        cl.def(boost::python::init<>()[call_policies]);
    }


    template <class Class>
    void visit(Class& cl) const
    {
        visit_aux(cl, mpl::empty<ParameterSpecs>());
    }

    call(CallPolicies const& call_policies = CallPolicies())
      : call_policies(call_policies)
    {}


    template <class CallPolicies1>
    call<ParameterSpecs, CallPolicies1>
    operator[](CallPolicies1 const& call_policies) const
    {
        return call<ParameterSpecs, CallPolicies1>(call_policies);
    }


    template <class Class>
    void visit(Class& cl) const
    {
        typedef mpl::iterator_range<
            typename mpl::next<
                typename mpl::begin<ParameterSpecs>::type
            >::type
          , typename mpl::end<ParameterSpecs>::type
        > arg_types;

        typedef typename mpl::front<ParameterSpecs>::type result_type;

        typedef typename mpl::transform<
            arg_types
          , aux::make_kw_spec<mpl::_>
          , mpl::back_inserter<mpl::vector0<> >
        >::type arg_specs;

        typedef typename mpl::count_if<
            arg_specs
          , aux::is_optional<mpl::_>
        >::type optional_arity;

        typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

        typedef aux::call_policies_as_options<CallPolicies> options;

        aux::def_combinations(
            aux::def_class<Class, options>(cl, "__call__", options(call_policies))
          , (arg_specs*)0
          , mpl::long_<0>()
          , mpl::long_<upper::value>()
          , (aux::make_call_invoker<typename Class::wrapped_type, result_type>*)0
        );
    }

    template <class Class, class Options>
    void visit(Class& cl, char const* name, Options const& options) const
    {
        typedef mpl::iterator_range<
            typename mpl::next<
                typename mpl::begin<ParameterSpecs>::type
            >::type
          , typename mpl::end<ParameterSpecs>::type
        > arg_types;

        typedef typename mpl::front<ParameterSpecs>::type result_type;

        typedef typename mpl::transform<
            arg_types
          , aux::make_kw_spec<mpl::_>
          , mpl::back_inserter<mpl::vector0<> >
        >::type arg_specs;

        typedef typename mpl::count_if<
            arg_specs
          , aux::is_optional<mpl::_>
        >::type optional_arity;

        typedef typename mpl::shift_left<mpl::long_<1>, optional_arity>::type upper;

        aux::def_combinations(
            aux::def_class<Class, Options>(cl, name, options)
          , (arg_specs*)0
          , mpl::long_<0>()
          , mpl::long_<upper::value>()
          , (aux::make_member_invoker<
                Fwd, result_type, typename Class::wrapped_type
            >*)0
        );
    }

template <class T>
T& as_lvalue(T& value, long)
{
    return value;
}


template <class T>
T const& as_lvalue(T const& value, int)
{
    return value;
}

    static keyword<Tag>& get()
    {
        return const_cast<keyword<Tag>&>(instance);
    }


    explicit maybe(T value_)
      : value(value_)
      , constructed(false)
    {}


    maybe()
      : constructed(false)
    {}


    ~maybe()
    {
        if (constructed)
            this->destroy();
    }


    reference construct(reference value_) const
    {
        return value_;
    }


    template <class U>
    reference construct2(U const& value_) const
    {
        new (m_storage.address()) non_cv_value(value_);
        constructed = true;
        return *(non_cv_value*)m_storage.address();
    }


    void destroy()
    {
        ((non_cv_value*)m_storage.address())->~non_cv_value();
    }


    operator safe_bool() const
    {
        return value ? &maybe<T>::get : 0 ;
    }


    reference get() const
    {
        return value.get();
    }


  inline void_& void_reference()
  {
      static void_ instance;
      return instance;
  }

    static use_default_tag execute(use_default_tag)
    {
        return use_default_tag();
    }


    static use_default_tag remove_const(use_default_tag)
    {
        return use_default_tag();
    }


    template <class U>
    static U& execute(U& value)
    {
        return value;
    }


    template <class U>
    static U& remove_const(U& x)
    {
        return x;
    }


    static use_default_tag execute(use_default_tag)
    {
        return use_default_tag();
    }


    static use_default_tag remove_const(use_default_tag)
    {
        return use_default_tag();
    }

    empty_arg_list() {}

    empty_arg_list(
        BOOST_PP_ENUM_PARAMS(
            BOOST_PARAMETER_MAX_ARITY, void_ BOOST_PP_INTERCEPT
        ))
    {}

    template <class K, class Default>
    Default& operator[](default_<K, Default> x) const
    {
        return x.value;
    }

    arg_list(TaggedArg head, Next const& tail)
      : Next(tail)
      , arg(head)
    {}

    template <class D>
    reference get_default(D const&, mpl::false_) const
    {
        return arg.value;
    }


    reference operator[](keyword<key_type> const&) const
    {
        BOOST_MPL_ASSERT_NOT((holds_maybe));
        return arg.value;
    }

    template <class KW, class T2>
    arg_list<tagged_argument<KW, T2>, self>
    operator,(tagged_argument<KW,T2> x) const
    {
        return arg_list<tagged_argument<KW,T2>, self>(x, *this);
    }


    tagged_argument(reference x) : value(x) {}

    default_(Value& x)
      : value(x)
    {}

    lazy_default(const DefaultComputer& x)
      : compute_default(x)
    {}

    static R execute()
    {
        return M()(boost::type<R>());
    }

    static R execute(T& self)
    {
        return M()(boost::type<R>(), self);
    }

    static R execute(T& self)
    {
        return self();
    }

    static T* execute(T& self)
    {
        return new T;
    }
