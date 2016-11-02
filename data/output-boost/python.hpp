

inline bool type_info::operator<(type_info const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return std::strcmp(m_base_type, rhs.m_base_type) < 0;
#  else
    return m_base_type->before(*rhs.m_base_type);
#  endif 
}


inline bool type_info::operator==(type_info const& rhs) const
{
#  ifdef BOOST_PYTHON_TYPE_ID_NAME
    return !std::strcmp(m_base_type, rhs.m_base_type);
#  else
    return *m_base_type == *rhs.m_base_type;
#  endif 
}

    
inline char const* type_info::name() const
{
    char const* raw_name
        = m_base_type
#  ifndef BOOST_PYTHON_TYPE_ID_NAME
          ->name()
#  endif
        ;
    
#  ifdef BOOST_PYTHON_HAVE_GCC_CP_DEMANGLE
    return detail::gcc_demangle(raw_name);
#  else
    return raw_name;
#  endif 
}

    template <class U>
    inline PyObject*
    operator()(U const& ref) const
    {
        return this->execute(const_cast<U&>(ref), is_pointer<U>());
    }

      template <class T>
      static PyObject* execute(T* p)
      {
          // can't use auto_ptr with Intel 5 and VC6 Dinkum library
          // for some reason. We get link errors against the auto_ptr
          // copy constructor.
# if defined(__ICL) && __ICL < 600 
          typedef boost::shared_ptr<T> smart_pointer;
# else 
          typedef std::auto_ptr<T> smart_pointer;
# endif
          typedef objects::pointer_holder<smart_pointer, T> holder_t;

          smart_pointer ptr(const_cast<T*>(p));
          return objects::make_ptr_instance<T, holder_t>::execute(ptr);
      }

      template <class T>
      static PyObject* execute(T* p)
      {
          typedef objects::pointer_holder<T*, T> holder_t;
          T* q = const_cast<T*>(p);
          return objects::make_ptr_instance<T, holder_t>::execute(q);
      }

    slice() : base(0,0,0) {}

    template<typename Integer1, typename Integer2>
    slice( Integer1 start, Integer2 stop)
        : base( object(start).ptr(), object(stop).ptr(), 0 )
    {}

    
    template<typename Integer1, typename Integer2, typename Integer3>
    slice( Integer1 start, Integer2 stop, Integer3 stride)
        : base( object(start).ptr(), object(stop).ptr(), object(stride).ptr() )
    {}

    
    template<typename RandomAccessIterator>
    slice::range<RandomAccessIterator>
    get_indices( const RandomAccessIterator& begin, 
        const RandomAccessIterator& end) const
    {
        // This is based loosely on PySlice_GetIndicesEx(), but it has been 
        // carefully crafted to ensure that these iterators never fall out of
        // the range of the container.
        slice::range<RandomAccessIterator> ret;
        
        typedef typename iterator_difference<RandomAccessIterator>::type difference_type;
        difference_type max_dist = boost::detail::distance(begin, end);

        object slice_start = this->start();
        object slice_stop = this->stop();
        object slice_step = this->step();
        
        // Extract the step.
        if (slice_step == object()) {
            ret.step = 1;
        }
        else {
            ret.step = extract<long>( slice_step);
            if (ret.step == 0) {
                PyErr_SetString( PyExc_IndexError, "step size cannot be zero.");
                throw_error_already_set();
            }
        }
        
        // Setup the start iterator.
        if (slice_start == object()) {
            if (ret.step < 0) {
                ret.start = end;
                --ret.start;
            }
            else
                ret.start = begin;
        }
        else {
            difference_type i = extract<long>( slice_start);
            if (i >= max_dist && ret.step > 0)
                    throw std::invalid_argument( "Zero-length slice");
            if (i >= 0) {
                ret.start = begin;
                BOOST_USING_STD_MIN();
                std::advance( ret.start, min BOOST_PREVENT_MACRO_SUBSTITUTION(i, max_dist-1));
            }
            else {
                if (i < -max_dist && ret.step < 0)
                    throw std::invalid_argument( "Zero-length slice");
                ret.start = end;
                // Advance start (towards begin) not farther than begin.
                std::advance( ret.start, (-i < max_dist) ? i : -max_dist );
            }
        }
        
        // Set up the stop iterator.  This one is a little trickier since slices
        // define a [) range, and we are returning a [] range.
        if (slice_stop == object()) {
            if (ret.step < 0) {
                ret.stop = begin;
            }
            else {
                ret.stop = end;
                std::advance( ret.stop, -1);
            }
        }
        else {
            difference_type i = extract<long>(slice_stop);
            // First, branch on which direction we are going with this.
            if (ret.step < 0) {
                if (i+1 >= max_dist || i == -1)
                    throw std::invalid_argument( "Zero-length slice");
                
                if (i >= 0) {
                    ret.stop = begin;
                    std::advance( ret.stop, i+1);
                }
                else { // i is negative, but more negative than -1.
                    ret.stop = end;
                    std::advance( ret.stop, (-i < max_dist) ? i : -max_dist);
                }
            }
            else { // stepping forward
                if (i == 0 || -i >= max_dist)
                    throw std::invalid_argument( "Zero-length slice");
                
                if (i > 0) {
                    ret.stop = begin;
                    std::advance( ret.stop, (std::min)( i-1, max_dist-1));
                }
                else { // i is negative, but not more negative than -max_dist
                    ret.stop = end;
                    std::advance( ret.stop, i-1);
                }
            }
        }
        
        // Now the fun part, handling the possibilites surrounding step.
        // At this point, step has been initialized, ret.stop, and ret.step
        // represent the widest possible range that could be traveled
        // (inclusive), and final_dist is the maximum distance covered by the
        // slice.
        typename iterator_difference<RandomAccessIterator>::type final_dist = 
            boost::detail::distance( ret.start, ret.stop);
        
        // First case, if both ret.start and ret.stop are equal, then step
        // is irrelevant and we can return here.
        if (final_dist == 0)
            return ret;
        
        // Second, if there is a sign mismatch, than the resulting range and 
        // step size conflict: std::advance( ret.start, ret.step) goes away from
        // ret.stop.
        if ((final_dist > 0) != (ret.step > 0))
            throw std::invalid_argument( "Zero-length slice.");
        
        // Finally, if the last step puts us past the end, we move ret.stop
        // towards ret.start in the amount of the remainder.
        // I don't remember all of the oolies surrounding negative modulii,
        // so I am handling each of these cases separately.
        if (final_dist < 0) {
            difference_type remainder = -final_dist % -ret.step;
            std::advance( ret.stop, remainder);
        }
        else {
            difference_type remainder = final_dist % ret.step;
            std::advance( ret.stop, -remainder);
        }
        
        return ret;
    }

    template<typename RandomAccessIterator>
    slice::range<RandomAccessIterator>
    get_indicies( const RandomAccessIterator& begin, 
        const RandomAccessIterator& end) const
    {
        return get_indices(begin, end);
    }

  template <class F, class Helper>
  void def_from_helper(
      char const* name, F const& fn, Helper const& helper)
  {
      // Must not try to use default implementations except with method definitions.
      typedef typename error::multiple_functions_passed_to_def<
          Helper::has_default_implementation
          >::type assertion;
      
      detail::scope_setattr_doc(
          name, boost::python::make_function(
              fn
              , helper.policies()
              , helper.keywords())
          , helper.doc()
          );
  }

  template <class Fn, class A1>
  void
  def_maybe_overloads(
      char const* name
      , Fn fn
      , A1 const& a1
      , ...)
  {
      detail::def_from_helper(name, fn, def_helper<A1>(a1));
  }


  template <class T>
  object make_function1(T fn, ...) { return make_function(fn); }


template <class Fn>
void def(char const* name, Fn fn)
{
    detail::scope_setattr_doc(name, detail::make_function1(fn, &fn), 0);
}


template <class Arg1T, class Arg2T>
void def(char const* name, Arg1T arg1, Arg2T const& arg2)
{
    detail::def_maybe_overloads(name, arg1, arg2, &arg2);
}


template <class F, class A1, class A2>
void def(char const* name, F f, A1 const& a1, A2 const& a2)
{
    detail::def_from_helper(name, f, detail::def_helper<A1,A2>(a1,a2));
}


template <class F, class A1, class A2, class A3>
void def(char const* name, F f, A1 const& a1, A2 const& a2, A3 const& a3)
{
    detail::def_from_helper(name, f, detail::def_helper<A1,A2,A3>(a1,a2,a3));
}

      template <class ArgumentPackage>
      static PyObject* execute(ArgumentPackage const& args, PyObject* = 0)
      {
          int const pre_n = static_cast<int>(N) - 1; // separate line is gcc-2.96 workaround
          return detail::get(mpl::int_<pre_n>(), args);
      }

      template <class ArgumentPackage>
      static PyObject* execute(ArgumentPackage const&, PyObject* zeroth)
      {
          return zeroth;
      }


    template <class ArgumentPackage>
    static bool precall(ArgumentPackage const& args_)
    {
        unsigned arity_ = detail::arity(args_);
        if (custodian > arity_ || ward > arity_)
        {
            PyErr_SetString(
                PyExc_IndexError
              , "boost::python::with_custodian_and_ward: argument index out of range"
            );
            return false;
        }

        PyObject* patient = detail::get_prev<ward>::execute(args_);
        PyObject* nurse = detail::get_prev<custodian>::execute(args_);

        PyObject* life_support = python::objects::make_nurse_and_patient(nurse, patient);
        if (life_support == 0)
            return false;
    
        bool result = BasePolicy_::precall(args_);

        if (!result) {
            Py_DECREF(life_support);
        }
    
        return result;
    }

    
    template <class ArgumentPackage>
    static PyObject* postcall(ArgumentPackage const& args_, PyObject* result)
    {
        std::size_t arity_ = detail::arity(args_);
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
        if ( custodian > arity_ || ward > arity_ )
#else
        // check if either custodian or ward exceeds the arity
        // (this weird formulation avoids "always false" warnings
        // for arity_ = 0)
        if ( (std::max)(custodian, ward) > arity_ )
#endif
        {
            PyErr_SetString(
                PyExc_IndexError
              , "boost::python::with_custodian_and_ward_postcall: argument index out of range"
            );
            return 0;
        }
        
        PyObject* patient = detail::get_prev<ward>::execute(args_, result);
        PyObject* nurse = detail::get_prev<custodian>::execute(args_, result);

        if (nurse == 0) return 0;
    
        result = BasePolicy_::postcall(args_, result);
        if (result == 0)
            return 0;
            
        if (python::objects::make_nurse_and_patient(nurse, patient) == 0)
        {
            Py_XDECREF(result);
            return 0;
        }
        return result;
    }

  template <class F, class CallPolicies, class Sig>
  object make_function_aux(
      F f                               // An object that can be invoked by detail::invoke()
      , CallPolicies const& p           // CallPolicies to use in the invocation
      , Sig const&                      // An MPL sequence of argument types expected by F
      )
  {
      return objects::function_object(
          detail::caller<F,CallPolicies,Sig>(f, p)
      );
  }

  template <class F, class CallPolicies, class Keywords>
  object make_function_dispatch(F f, CallPolicies const& policies, Keywords const& kw, mpl::true_)
  {
      return detail::make_function_aux(
          f
        , policies
        , detail::get_signature(f)
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
  }

template <class F>
object make_function(F f)
{
    return detail::make_function_aux(
        f,default_call_policies(), detail::get_signature(f));
}
 

template <class T>
inline T* incref(T* p)
{
    Py_INCREF(python::upcast<PyObject>(p));
    return p;
}


template <class T>
inline T* xincref(T* p)
{
    Py_XINCREF(python::upcast<PyObject>(p));
    return p;
}


template <class T>
inline void decref(T* p)
{
    Py_DECREF(python::upcast<PyObject>(p));
}


template <class T>
inline void xdecref(T* p)
{
    Py_XDECREF(python::upcast<PyObject>(p));
}
 

template <class ExceptionType, class Translate>
void register_exception_translator(Translate translate, boost::type<ExceptionType>* = 0)
{
    detail::register_exception_handler(
        boost::bind<bool>(detail::translate_exception<ExceptionType,Translate>(), _1, _2, translate)
        );
}

    template <class ArgumentPackage>
    static bool precall(ArgumentPackage const&)
    {
        return true;
    }

    template <class ArgumentPackage>
    static PyObject* postcall(ArgumentPackage const&, PyObject* result)
    {
        return result;
    }

    tuple() {}


    template <class T>
    explicit tuple(T const& sequence)
        : base(object(sequence))
    {
    }

inline tuple make_tuple() { return tuple(); }


template <class T>
inline enum_<T>::enum_(char const* name, char const* doc )
    : base(
        name
        , &enum_<T>::to_python
        , &enum_<T>::convertible_from_python
        , &enum_<T>::construct
        , type_id<T>()
        , doc
        )
{
}


template <class T>
inline enum_<T>& enum_<T>::value(char const* name, T x)
{
    this->add_value(name, static_cast<long>(x));
    return *this;
}


template <class T>
inline enum_<T>& enum_<T>::export_values()
{
    this->base::export_values();
    return *this;
}

      explicit method_result(PyObject* x)
        : m_obj(x)
      {}

      template <class T>
      operator T()
      {
          converter::return_from_python<T> converter;
          return converter(m_obj.release());
      }

      
      template <class T>
      operator T&() const
      {
          converter::return_from_python<T&> converter;
          return converter(const_cast<handle<>&>(m_obj).release());
      }
 

      template <class T>
      T as(type<T>* = 0)
      {
          converter::return_from_python<T> converter;
          return converter(m_obj.release());
      }


      template <class T>
      T unchecked(type<T>* = 0)
      {
          return extract<T>(m_obj.get())();
      }

    override(handle<> x)
      : object(x)
    {}

    detail::method_result
    operator()() const
    {
        detail::method_result x(
            PyEval_CallFunction(
                this->ptr()
              , const_cast<char*>("()")
            ));
        return x;
    }


template <class T, class Conversion ,bool has_get_pytype>
to_python_converter<T,Conversion, has_get_pytype>::to_python_converter()
{
    typedef converter::as_to_python_function<
        T, Conversion
        > normalized;
            
    converter::registry::insert(
        &normalized::convert
        , type_id<T>()
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
        , &get_pytype_impl
#endif
        );
}

  
  template <class Source, class Target>
  inline Target* upcast(Source* p, yes_convertible, no_convertible, Target*)
  {
      return p;
  }

      template <class T>
      static inline T* execute(T* x, T*) { return x; }

      template <class Source, class Target>
      static inline Target* execute(Source* x, Target*)
      {
          return detail::upcast(
              x, detail::convertible<Target*>::check(x)
              , detail::convertible<Source*>::check((Target*)0)
              , (Target*)0);
      }



  template <class Target, class Source>
  inline Target* downcast(Source* p, yes_convertible)
  {
      return static_cast<Target*>(p);
  }


  template <class Source, class Target>
  inline Target* upcast_impl(Source* x, Target*)
  {
      typedef typename add_cv<Source>::type src_t;
      typedef typename add_cv<Target>::type target_t;
      bool const same = is_same<src_t,target_t>::value;
      
      return detail::upcaster<same>::execute(x, (Target*)0);
  }


template <class Target, class Source>
inline Target* upcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::upcast_impl(x, (Target*)0);
    
}


template <class Target, class Source>
inline Target* downcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::downcast<Target>(x, detail::convertible<Source*>::check((Target*)0));
}

  template <class C, class S>
  typename replace_front2<S,void,C&>::type
  error_signature(S BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(C))
  {
      typedef typename replace_front2<S,void,C&>::type r;
      return r();
  }

      pure_virtual_visitor(PointerToMemberFunction pmf)
        : m_pmf(pmf)
      {}

      
      template <class C_, class Options>
      void visit(C_& c, char const* name, Options& options) const
      {
          // This should probably be a nicer error message
          BOOST_STATIC_ASSERT(!Options::has_default_implementation);

          // Add the virtual function dispatcher
          c.def(
              name
            , m_pmf
            , options.doc()
            , options.keywords()
            , options.policies()
          );

          typedef BOOST_DEDUCED_TYPENAME C_::metadata::held_type held_type;
          
          // Add the default implementation which raises the exception
          c.def(
              name
            , make_function(
                  detail::nullary_function_adaptor<void(*)()>(pure_virtual_called)
                , default_call_policies()
                , detail::error_signature<held_type>(detail::get_signature(m_pmf))
              )
          );
      }

template <class PointerToMemberFunction>
detail::pure_virtual_visitor<PointerToMemberFunction>
pure_virtual(PointerToMemberFunction pmf)
{
    return detail::pure_virtual_visitor<PointerToMemberFunction>(pmf);
}


template <class T>
typename back_reference<T>::source_t const& back_reference<T>::source() const
{
    return m_source;
}


template <class T>
T back_reference<T>::get() const
{
    return m_value;
}

  template <class Target, class Accessor1, class Accessor2, class NextPolicies>
  inline object make_iterator(
      Accessor1 get_start
    , Accessor2 get_finish
    , NextPolicies next_policies
    , Target&(*)()
  )
  {
      return objects::make_iterator_function<Target>(
          boost::protect(boost::bind(get_start, _1))
        , boost::protect(boost::bind(get_finish, _1))
        , next_policies
      );
  }

          static iterator begin(T& x) { return x.begin(); }

          static iterator end(T& x) { return x.end(); }

          static iterator begin(T& x) { return x.begin(); }

          static iterator end(T& x) { return x.end(); }

template <class Accessor1, class Accessor2>
object range(Accessor1 start, Accessor2 finish)
{
    return detail::make_iterator(
        start, finish
      , objects::default_iterator_call_policies()
      , detail::target(start)
    );
}

    iterator()
        : object(
            python::range<NextPolicies>(
                &iterators<Container>::begin, &iterators<Container>::end
                ))
    {
    }

    template <class V, class classT>
    static void visit(V const& v, classT& c)
    {
        v.derived_visitor().visit(c);
    }

    template <class V, class classT, class OptionalArgs>
    static void visit(
        V const& v
      , classT& c
      , char const* name
      , OptionalArgs const& options
    ) 
    {
        v.derived_visitor().visit(c, name, options);
    }

    template <class classT>
    void visit(classT& c) const
    {
        def_visitor_access::visit(*this, c);
    }

    template <class classT, class OptionalArgs>
    void visit(classT& c, char const* name, OptionalArgs const& options) const
    {
        def_visitor_access::visit(*this, c, name, options);
    }

    DerivedVisitor const& derived_visitor() const
    {
        return static_cast<DerivedVisitor const&>(*this);
    }

    str() {}

    
    str(const char* s) : base(s) {}

    
    str(char const* start, char const* finish) // new str
      : base(start, finish)
    {}

    
    template <class T>
    explicit str(T const& other)
        : base(object(other))
    {
    }


    template <class T>
    str center(T const& width) const
    {
        return base::center(object(width));
    }


    template<class T>
    long count(T const& sub) const
    {
        return base::count(object(sub));
    }


    template<class T1, class T2>
    long count(T1 const& sub,T2 const& start) const
    {
        return base::count(object(sub), object(start));
    }


    template<class T1, class T2, class T3>
    long count(T1 const& sub,T2 const& start, T3 const& end) const
    {
        return base::count(object(sub), object(start));
    }

    object decode() const { return base::decode(); }


    object encode() const { return base::encode(); }


    template <class T>
    bool endswith(T const& suffix) const
    {
        return base::endswith(object(suffix));
    }


    template <class T1, class T2>
    bool endswith(T1 const& suffix, T2 const& start) const
    {
        return base::endswith(object(suffix), object(start));
    }


    template <class T1, class T2, class T3>
    bool endswith(T1 const& suffix, T2 const& start, T3 const& end) const
    {
        return base::endswith(object(suffix), object(start), object(end));
    }

    
    str expandtabs() const { return base::expandtabs(); }


    template <class T>
    str expandtabs(T const& tabsize) const
    {
        return base::expandtabs(object(tabsize));
    }

    
    template <class T>
    long find(T const& sub) const
    {
        return base::find(object(sub));
    }


    template <class T1, class T2>
    long find(T1 const& sub, T2 const& start) const
    {
        return base::find(object(sub), object(start));
    }


    template <class T1, class T2, class T3>
    long find(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::find(object(sub), object(start), object(end));
    }

    
    template <class T>
    long index(T const& sub) const
    {
        return base::index(object(sub));
    }

    
    template <class T1, class T2>
    long index(T1 const& sub, T2 const& start) const
    {
        return base::index(object(sub), object(start));
    }


    template <class T1, class T2, class T3>
    long index(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::index(object(sub), object(start), object(end));
    }


    template <class T>
    str join(T const& sequence) const
    {
        return base::join(object(sequence));
    }

    
    template <class T>
    str ljust(T const& width) const
    {
        return base::ljust(object(width));
    }


    template <class T1, class T2>
    str replace(T1 const& old, T2 const& new_) const 
    {
        return base::replace(object(old),object(new_));
    }


    template <class T1, class T2, class T3>
    str replace(T1 const& old, T2 const& new_, T3 const& maxsplit) const 
    {
        return base::replace(object(old),object(new_), object(maxsplit));
    }

    
    template <class T>
    long rfind(T const& sub) const
    {
        return base::rfind(object(sub));
    }


    template <class T1, class T2>
    long rfind(T1 const& sub, T2 const& start) const
    {
        return base::rfind(object(sub), object(start));
    }

    
    template <class T1, class T2, class T3>
    long rfind(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::rfind(object(sub), object(start), object(end));
    }

    
    template <class T>
    long rindex(T const& sub) const
    {
        return base::rindex(object(sub));
    }


    template <class T1, class T2>
    long rindex(T1 const& sub, T2 const& start) const
    {
        return base::rindex(object(sub), object(start));
    }


    template <class T1, class T2, class T3>
    long rindex(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::rindex(object(sub), object(start), object(end));
    }


    template <class T>
    str rjust(T const& width) const
    {
        return base::rjust(object(width));
    }

    
    list split() const { return base::split(); }


    list splitlines() const { return base::splitlines(); }


    template <class T>
    bool startswith(T const& prefix) const
    {
        return base::startswith(object(prefix));
    }


    template <class T1, class T2>
    bool startswith(T1 const& prefix, T2 const& start) const
    {
        return base::startswith(object(prefix), object(start));
    }

     
    template <class T1, class T2, class T3>
    bool startswith(T1 const& prefix, T2 const& start, T3 const& end) const
    {
        return base::startswith(object(prefix), object(start), object(end));
    }


    template <class T>
    str translate(T const& table) const
    {
        return base::translate(object(table));
    }


    template <class T1, class T2>
    str translate(T1 const& table, T2 const& deletechars) const
    {
        return base::translate(object(table), object(deletechars));
    }

      keyword(char const* name_=0)
       : name(name_)
      {}

      static keyword_range range() { return keyword_range(); }
      
      member(Data Class::*which) : m_which(which) {}

      
      Data& operator()(Class& c) const
      {
          return c.*m_which;
      }
      
      datum(Data *which) : m_which(which) {}

      
      Data& operator()() const
      {
          return *m_which;
      }

  template <class D, class Policies>
  inline object make_getter(D* d, Policies const& policies, mpl::false_, int)
  {
      return python::make_function(
          detail::datum<D>(d), policies, mpl::vector1<D&>()
      );
  }

  template <class D, class Policies>
  inline object make_setter(D* p, Policies const& policies, mpl::false_, int)
  {
      return python::make_function(
          detail::datum<D>(p), policies, mpl::vector2<void,D const&>()
      );
  }

template <class D, class Policies>
inline object make_getter(D& d, Policies const& policies)
{
    return detail::make_getter(d, policies, is_member_pointer<D>(), 0L);
}

template <class D, class Policies>
inline object make_setter(D& x, Policies const& policies)
{
    return detail::make_setter(x, policies, is_member_pointer<D>(), 0);
}
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
BOOST_PYTHON_BINARY_OPERATOR(>>)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
BOOST_PYTHON_BINARY_OPERATOR(>>)
BOOST_PYTHON_BINARY_OPERATOR(&)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
BOOST_PYTHON_BINARY_OPERATOR(>>)
BOOST_PYTHON_BINARY_OPERATOR(&)
BOOST_PYTHON_BINARY_OPERATOR(^)
 operator op(L const& l, R const& r)  \
{                                                                       \
    return object(l) op object(r);                                      \
}
BOOST_PYTHON_BINARY_OPERATOR(>)
BOOST_PYTHON_BINARY_OPERATOR(>=)
BOOST_PYTHON_BINARY_OPERATOR(<)
BOOST_PYTHON_BINARY_OPERATOR(<=)
BOOST_PYTHON_BINARY_OPERATOR(==)
BOOST_PYTHON_BINARY_OPERATOR(!=)
BOOST_PYTHON_BINARY_OPERATOR(+)
BOOST_PYTHON_BINARY_OPERATOR(-)
BOOST_PYTHON_BINARY_OPERATOR(*)
BOOST_PYTHON_BINARY_OPERATOR(/)
BOOST_PYTHON_BINARY_OPERATOR(%)
BOOST_PYTHON_BINARY_OPERATOR(<<)
BOOST_PYTHON_BINARY_OPERATOR(>>)
BOOST_PYTHON_BINARY_OPERATOR(&)
BOOST_PYTHON_BINARY_OPERATOR(^)
BOOST_PYTHON_BINARY_OPERATOR(|)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
BOOST_PYTHON_INPLACE_OPERATOR(>>=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
BOOST_PYTHON_INPLACE_OPERATOR(>>=)
BOOST_PYTHON_INPLACE_OPERATOR(&=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
BOOST_PYTHON_INPLACE_OPERATOR(>>=)
BOOST_PYTHON_INPLACE_OPERATOR(&=)
BOOST_PYTHON_INPLACE_OPERATOR(^=)
      template <class R>                                                      object& operator op(object& l, R const& r)                              \
{                                                                       \
    return l op object(r);                                              \
}
BOOST_PYTHON_INPLACE_OPERATOR(+=)
BOOST_PYTHON_INPLACE_OPERATOR(-=)
BOOST_PYTHON_INPLACE_OPERATOR(*=)
BOOST_PYTHON_INPLACE_OPERATOR(/=)
BOOST_PYTHON_INPLACE_OPERATOR(%=)
BOOST_PYTHON_INPLACE_OPERATOR(<<=)
BOOST_PYTHON_INPLACE_OPERATOR(>>=)
BOOST_PYTHON_INPLACE_OPERATOR(&=)
BOOST_PYTHON_INPLACE_OPERATOR(^=)
BOOST_PYTHON_INPLACE_OPERATOR(|=)

    list() {}


    template <class T>
    explicit list(T const& sequence)
        : base(object(sequence))
    {
    }


    template <class T>
    void append(T const& x)
    {
        base::append(object(x));
    }


    template <class T>
    long count(T const& value) const
    {
        return base::count(object(value));
    }

    
    template <class T>
    void extend(T const& x)
    {
        base::extend(object(x));
    }


    template <class T>
    long index(T const& x) const
    {
        return base::index(object(x));
    }

    
    template <class T>
    void insert(ssize_t index, T const& x) // insert object before index
    {
        base::insert(index, object(x));
    }


    object pop() { return base::pop(); }


    template <class T>
    void remove(T const& value)
    {
        base::remove(object(value));
    }

    void sort() { base::sort(); }


    template <class T>
    void sort(T const& value)
    {
        base::sort(object(value));
    }

    stl_input_iterator()
      : impl_()
    {
    }


    void increment()
    {
        this->impl_.increment();
    }


    ValueT dereference() const
    {
        return extract<ValueT>(this->impl_.current().get())();
    }


    bool equal(stl_input_iterator<ValueT> const &that) const
    {
        return this->impl_.equal(that.impl_);
    }

    dict() {}


    template <class T>
    explicit dict(T const& data)
        : base(object(data))
    {
    }


    template<class T>
    object get(T const& k) const 
    {
        return base::get(object(k));
    }

    
    template<class T>
    bool has_key(T const& k) const
    {
        return base::has_key(object(k));
    }

    
    template<class T>
    object setdefault(T const& k)
    {
        return base::setdefault(object(k));
    }


    template<class T>
    void update(T const& E)
    {
        base::update(object(E));
    }

      raw_dispatcher(F f) : f(f) {}

      
      PyObject* operator()(PyObject* args, PyObject* keywords)
      {
          return incref(
              object(
                  f(
                      tuple(borrowed_reference(args))
                    , keywords ? dict(borrowed_reference(keywords)) : dict()
                  )
              ).ptr()
          );
      }


template <class F>
object raw_function(F f, std::size_t min_args = 0)
{
    return detail::make_raw_function(
        objects::py_function(
            detail::raw_dispatcher<F>(f)
          , mpl::vector1<PyObject*>()
          , min_args
          , (std::numeric_limits<unsigned>::max)()
        )
    );
}

    override get_override(char const* name) const
    {
        typedef detail::wrapper_base base;
        converter::registration const& r
            = converter::registered<T>::converters;
        PyTypeObject* type = r.get_class_object();
        
        return this->base::get_override(name, type);
    }


template <class T, class U>
inline slice_policies::key_type slice_key(T x, U y)
{
    return slice_policies::key_type(handle<>(x), handle<>(y));
}


inline scope::scope()
    : object(detail::borrowed_reference(
                 detail::current_scope ? detail::current_scope : Py_None
                 ))
    , m_previous_scope(python::xincref(detail::current_scope))
{
}


inline scope::~scope()
{
    python::xdecref(detail::current_scope);
    detail::current_scope = m_previous_scope;
}

inline scope::scope(scope const& new_scope)
    : object(new_scope)
    , m_previous_scope(detail::current_scope)
{
    detail::current_scope = python::incref(new_scope.ptr());
}

      install_holder(PyObject* args_)
        : m_self(PyTuple_GetItem(args_, 0)) {}


      PyObject* operator()(T x) const
      {
          dispatch(x, is_pointer<T>());
          return none();
      }

      template <class U>
      void dispatch(U* x, mpl::true_) const
      {
          std::auto_ptr<U> owner(x);
          dispatch(owner, mpl::false_());
      }

      offset_args(BaseArgs base_) : base(base_) {}

  
  template <class BaseArgs, class Offset>
  inline unsigned arity(offset_args<BaseArgs,Offset> const& args_)
  {
      return arity(args_.base) - Offset::value;
  }

      constructor_policy(BasePolicy_ base) : BasePolicy_(base) {}

  template <class F, class CallPolicies, class Sig>
  object make_constructor_aux(
      F f                             // An object that can be invoked by detail::invoke()
    , CallPolicies const& p           // CallPolicies to use in the invocation
    , Sig const&                      // An MPL sequence of argument types expected by F
  )
  {
      typedef typename outer_constructor_signature<Sig>::type outer_signature;

      typedef constructor_policy<CallPolicies> inner_policy;
      
      return objects::function_object(
          objects::py_function(
              detail::caller<F,inner_policy,Sig>(f, inner_policy(p))
            , outer_signature()
          )
      );
  }

  template <class F, class CallPolicies, class Keywords>
  object make_constructor_dispatch(F f, CallPolicies const& policies, Keywords const& kw, mpl::true_)
  {
      return detail::make_constructor_aux(
          f
        , policies
        , detail::get_signature(f)
        , kw.range()
        , mpl::int_<Keywords::size>()
      );
  }

template <class F>
object make_constructor(F f)
{
    return detail::make_constructor_aux(
        f,default_call_policies(), detail::get_signature(f));
}

  template <class T>
  PyObject* convert_result(T const& x)
  {
      return converter::arg_to_python<T>(x).release();
  }

      template <class ClassT>
      void visit(ClassT& cl) const
      {
          typedef typename mpl::eval_if<
              is_same<L,self_t>
            , mpl::if_<
                  is_same<R,self_t>
                , binary_op<id>
                , binary_op_l<
                      id
                    , BOOST_DEDUCED_TYPENAME unwrap_other<R>::type
                  >
              >
            , mpl::if_<
                  is_same<L,not_specified>
                , unary_op<id>
                , binary_op_r<
                      id
                    , BOOST_DEDUCED_TYPENAME unwrap_other<L>::type
                  >
              >
          >::type generator;
      
          cl.def(
              generator::name()
            , &generator::template apply<
                 BOOST_DEDUCED_TYPENAME ClassT::wrapped_type
              >::execute
          );
      }
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
BOOST_PYTHON_BINARY_OPERATOR(lt, gt, <)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
BOOST_PYTHON_BINARY_OPERATOR(lt, gt, <)
BOOST_PYTHON_BINARY_OPERATOR(le, ge, <=)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
BOOST_PYTHON_BINARY_OPERATOR(lt, gt, <)
BOOST_PYTHON_BINARY_OPERATOR(le, ge, <=)
BOOST_PYTHON_BINARY_OPERATOR(eq, eq, ==)
                                                       \
  template <class L, class R>                           \
  inline detail::operator_<detail::op_##id,L,R>         \
  operator op(L const&, R const&)                       \
  {                                                     \
      return detail::operator_<detail::op_##id,L,R>();  \
  }                                                     \
}
  
BOOST_PYTHON_BINARY_OPERATOR(add, radd, +)
BOOST_PYTHON_BINARY_OPERATOR(sub, rsub, -)
BOOST_PYTHON_BINARY_OPERATOR(mul, rmul, *)
#if PY_VERSION_HEX >= 0x03000000
    BOOST_PYTHON_BINARY_OPERATOR(truediv, rtruediv, /)
#else
    BOOST_PYTHON_BINARY_OPERATOR(div, rdiv, /)
#endif
BOOST_PYTHON_BINARY_OPERATOR(mod, rmod, %)
BOOST_PYTHON_BINARY_OPERATOR(lshift, rlshift, <<)
BOOST_PYTHON_BINARY_OPERATOR(rshift, rrshift, >>)
BOOST_PYTHON_BINARY_OPERATOR(and, rand, &)
BOOST_PYTHON_BINARY_OPERATOR(xor, rxor, ^)
BOOST_PYTHON_BINARY_OPERATOR(or, ror, |)
BOOST_PYTHON_BINARY_OPERATOR(gt, lt, >)
BOOST_PYTHON_BINARY_OPERATOR(ge, le, >=)
BOOST_PYTHON_BINARY_OPERATOR(lt, gt, <)
BOOST_PYTHON_BINARY_OPERATOR(le, ge, <=)
BOOST_PYTHON_BINARY_OPERATOR(eq, eq, ==)
BOOST_PYTHON_BINARY_OPERATOR(ne, ne, !=)

  template <class L, class R>
  inline detail::operator_<detail::op_pow,L,R>
  pow(L const&, R const&)
  {
      return detail::operator_<detail::op_pow,L,R>();
  }
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
BOOST_PYTHON_INPLACE_OPERATOR(irshift,>>=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
BOOST_PYTHON_INPLACE_OPERATOR(irshift,>>=)
BOOST_PYTHON_INPLACE_OPERATOR(iand,&=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
BOOST_PYTHON_INPLACE_OPERATOR(irshift,>>=)
BOOST_PYTHON_INPLACE_OPERATOR(iand,&=)
BOOST_PYTHON_INPLACE_OPERATOR(ixor,^=)
                                                               \
  template <class R>                                            \
  inline detail::operator_<detail::op_##id,self_t,R>            \
  operator op(self_t const&, R const&)                          \
  {                                                             \
      return detail::operator_<detail::op_##id,self_t,R>();     \
  }                                                             \
}

BOOST_PYTHON_INPLACE_OPERATOR(iadd,+=)
BOOST_PYTHON_INPLACE_OPERATOR(isub,-=)
BOOST_PYTHON_INPLACE_OPERATOR(imul,*=)
BOOST_PYTHON_INPLACE_OPERATOR(idiv,/=)
BOOST_PYTHON_INPLACE_OPERATOR(imod,%=)
BOOST_PYTHON_INPLACE_OPERATOR(ilshift,<<=)
BOOST_PYTHON_INPLACE_OPERATOR(irshift,>>=)
BOOST_PYTHON_INPLACE_OPERATOR(iand,&=)
BOOST_PYTHON_INPLACE_OPERATOR(ixor,^=)
BOOST_PYTHON_INPLACE_OPERATOR(ior,|=)
                                                               \
  inline detail::operator_<detail::op_##id>                     \
  func_name(self_t const&)                                      \
  {                                                             \
      return detail::operator_<detail::op_##id>();              \
  }                                                             \
}
# undef BOOST_PYTHON_INPLACE_OPERATOR

BOOST_PYTHON_UNARY_OPERATOR(neg, -, operator-)
BOOST_PYTHON_UNARY_OPERATOR(pos, +, operator+)
BOOST_PYTHON_UNARY_OPERATOR(abs, abs, abs)
BOOST_PYTHON_UNARY_OPERATOR(invert, ~, operator~)
                                                               \
  inline detail::operator_<detail::op_##id>                     \
  func_name(self_t const&)                                      \
  {                                                             \
      return detail::operator_<detail::op_##id>();              \
  }                                                             \
}
# undef BOOST_PYTHON_INPLACE_OPERATOR

BOOST_PYTHON_UNARY_OPERATOR(neg, -, operator-)
BOOST_PYTHON_UNARY_OPERATOR(pos, +, operator+)
BOOST_PYTHON_UNARY_OPERATOR(abs, abs, abs)
BOOST_PYTHON_UNARY_OPERATOR(invert, ~, operator~)
#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_UNARY_OPERATOR(bool, !!, operator!)
#else
BOOST_PYTHON_UNARY_OPERATOR(nonzero, !!, operator!)


    object astype() { return base::astype(); }


    template <class Type>
    array new_(Type const& type_) const
    {
        return base::new_(object(type_));
    }


    template <class Sequence>
    void resize(Sequence const& x)
    {
        base::resize(object(x));
    }


    template <class Sequence>
    void setshape(Sequence const& x)
    {
        base::setshape(object(x));
    }


    template <class Indices, class Values>
    void put(Indices const& indices, Values const& values)
    {
        base::put(object(indices), object(values));
    }

    
    template <class Sequence>
    object take(Sequence const& sequence, long axis = 0)
    {
        return base::take(object(sequence), axis);
    }


    template <class File>
    void tofile(File const& f) const
    {
        base::tofile(object(f));
    }


    object factory()
    {
        return base::factory();
    }

      
      template <class ClassT, class DocStringT>
      void visit(ClassT& cl, char const* name, python::detail::def_helper<DocStringT> const& helper) const
      {
          // It's too late to specify anything other than docstrings if
          // the callable object is already wrapped.
          BOOST_STATIC_ASSERT(
              (is_same<char const*,DocStringT>::value
               || detail::is_string_literal<DocStringT const>::value));
        
          objects::add_to_namespace(cl, name, this->derived_visitor(), helper.doc());
      }

  
  template <class T>
  PyObject* object_base_initializer(T const& x)
  {
      typedef typename is_derived<
          BOOST_DEDUCED_TYPENAME objects::unforward_cref<T>::type
        , object
      >::type is_obj;

      return object_initializer<
          BOOST_DEDUCED_TYPENAME unwrap_reference<T>::type
      >::get(
            x
          , is_obj()
      );
  }

      template <class T>
      explicit object(
          T const& x
# if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          // use some SFINAE to un-confuse MSVC about its
          // copy-initialization ambiguity claim.
        , typename mpl::if_<is_proxy<T>,int&,int>::type* = 0
# endif 
      )
        : object_base(object_base_initializer(x))
      {
      }

      static PyObject*
      get(object const& x, mpl::true_)
      {
          return python::incref(x.ptr());
      }

      template <class Policies>
      static PyObject* 
      get(proxy<Policies> const& x, mpl::false_)
      {
          return python::incref(x.operator object().ptr());
      }

      template <class T, class U>
      static PyObject*
      get(T const& x, U)
      {
          return python::incref(get_managed_object(x, boost::python::tag));
      }
 
  call_proxy(object target) : m_target(target) {}
 
  operator object() const { return m_target;}
 
  kwds_proxy(object o = object()) : call_proxy(o) {}
 
  args_proxy(object o) : call_proxy(o) {}
 
  kwds_proxy operator* () const { return kwds_proxy(*this);}
 
 
template <typename U> 
detail::args_proxy api::object_operators<U>::operator* () const 
{ 
  object_cref2 x = *static_cast<U const*>(this); 
  return boost::python::detail::args_proxy(x); 
}
 
 
template <typename U> 
object api::object_operators<U>::operator()(detail::args_proxy const &args) const 
{ 
  U const& self = *static_cast<U const*>(this); 
  PyObject *result = PyObject_Call(get_managed_object(self, boost::python::tag), 
                                   args.operator object().ptr(), 
                                   0); 
  return object(boost::python::detail::new_reference(result)); 
 
}
 
 
template <typename U> 
object api::object_operators<U>::operator()(detail::args_proxy const &args, 
                                            detail::kwds_proxy const &kwds) const 
{ 
  U const& self = *static_cast<U const*>(this); 
  PyObject *result = PyObject_Call(get_managed_object(self, boost::python::tag), 
                                   args.operator object().ptr(), 
                                   kwds.operator object().ptr()); 
  return object(boost::python::detail::new_reference(result)); 
 
}

template <class T>
object api::object_operators<U>::contains(T const& key) const
{
    return this->attr("__contains__")(object(key));
}



inline object::object()
    : object_base(python::incref(Py_None))
{}

inline api::object_base::object_base(object_base const& rhs)
    : m_ptr(python::incref(rhs.m_ptr))
{}


inline api::object_base& api::object_base::operator=(api::object_base const& rhs)
{
    Py_INCREF(rhs.m_ptr);
    Py_DECREF(this->m_ptr);
    this->m_ptr = rhs.m_ptr;
    return *this;
}


inline api::object_base::~object_base()
{
    Py_DECREF(m_ptr);
}


inline bool api::object_base::is_none() const
{
    return (m_ptr == Py_None);
}

      static bool check(PyObject*) { return true; }

      
      static python::detail::new_non_null_reference adopt(PyObject* x)
      {
          return python::detail::new_non_null_reference(x);
      }


inline PyObject* get_managed_object(object const& x, tag_t)
{
    return x.ptr();
}

    init_base(char const* doc_, detail::keyword_range const& keywords_)
        : m_doc(doc_), m_keywords(keywords_)
    {}

        
    init_base(char const* doc_)
        : m_doc(doc_)
    {}


    DerivedT const& derived() const
    {
        return *static_cast<DerivedT const*>(this);
    }

    
    char const* doc_string() const
    {
        return m_doc;
    }


    init_with_call_policies(
        CallPoliciesT const& policies_
        , char const* doc_
        , detail::keyword_range const& keywords
        )
        : base(doc_, keywords)
        , m_policies(policies_)
    {}


    CallPoliciesT const& call_policies() const
    {
        return this->m_policies;
    }

  template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
  inline void def_init_aux(
      ClassT& cl
      , Signature const&
      , NArgs
      , CallPoliciesT const& policies
      , char const* doc
      , detail::keyword_range const& keywords_
      )
  {
      cl.def(
          "__init__"
        , detail::make_keyword_range_constructor<Signature,NArgs>(
              policies
            , keywords_
            , (typename ClassT::metadata::holder*)0
          )
        , doc
      );
  }


      template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
      static void apply(
          ClassT& cl
          , CallPoliciesT const& policies
          , Signature const& args
          , NArgs
          , char const* doc
          , detail::keyword_range keywords)
      {
          detail::def_init_aux(cl, args, NArgs(), policies, doc, keywords);

          if (keywords.second > keywords.first)
              --keywords.second;

          typedef typename mpl::prior<NArgs>::type next_nargs;
          define_class_init_helper<NDefaults-1>::apply(
              cl, policies, Signature(), next_nargs(), doc, keywords);
      }


      template <class ClassT, class CallPoliciesT, class Signature, class NArgs>
      static void apply(
          ClassT& cl
        , CallPoliciesT const& policies
        , Signature const& args
        , NArgs
        , char const* doc
        , detail::keyword_range const& keywords)
      {
          detail::def_init_aux(cl, args, NArgs(), policies, doc, keywords);
      }

    opaque()
    {
        if (type_object.tp_name == 0)
        {
            type_object.tp_name = const_cast<char*>(type_id<Pointee*>().name());
            if (PyType_Ready (&type_object) < 0)
            {
                throw error_already_set();
            }

            this->register_self();
        }
    }

    
    static void* extract(PyObject* op)
    {
        return PyObject_TypeCheck(op, &type_object)
            ? static_cast<python_instance*>(implicit_cast<void*>(op))->x
            : 0
            ;
    }


    static PyObject* wrap(void const* px)
    {
        Pointee* x = *static_cast<Pointee*const*>(px);
        
        if (x == 0)
            return detail::none();

        if ( python_instance *o = PyObject_New(python_instance, &type_object) )
        {
            o->x = x;
            return static_cast<PyObject*>(implicit_cast<void*>(o));
        }
        else
        {
            throw error_already_set();
        }
    }


    void register_self()
    {
        converter::registration const *existing =
            converter::registry::query (type_id<Pointee*>());

        if ((existing == 0) || (existing->m_to_python == 0))
        {
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
            converter::registry::insert(&extract, type_id<Pointee>(), &get_pytype);
            converter::registry::insert(&wrap, type_id<Pointee*>(), &get_pytype);
#else
            converter::registry::insert(&extract, type_id<Pointee>());
            converter::registry::insert(&wrap, type_id<Pointee*>());
#endif
        }
    }

    
    template <class T>
    inline proxy const& operator=(T const& rhs) const
    {
        Policies::set(m_target, m_key, object(rhs));
        return *this;
    }



template <class T>
inline void del(proxy<T> const& x)
{
    x.del();
}

  template <class Pointee>
  static void opaque_pointee(Pointee const volatile*)
  {
      force_instantiate(opaque<Pointee>::instance);
  }

            type() { detail::opaque_pointee(R()); }


template <class T>
bool handle_exception(T f)
{
    return handle_exception_impl(function0<void>(boost::ref(f)));
}
 inline void rethrow() { throw; }


inline void handle_exception()
{
    handle_exception(detail::rethrow);
}


template <class T>
inline T* expect_non_null(T* x)
{
    if (x == 0)
        throw_error_already_set();
    return x;
}


template <class Target, class Key>
object getattr(Target const& target, Key const& key BOOST_PYTHON_NO_ARRAY_ARG(Key))
{
    return getattr(object(target), object(key));
}


template <class Target, class Key>
object getitem(Target const& target, Key const& key BOOST_PYTHON_NO_ARRAY_ARG(Key))
{
    return getitem(object(target), object(key));
}


template <class Target, class Begin, class End>
object getslice(Target const& target, Begin const& begin, End const& end)
{
    return getslice(object(target), object(begin), object(end));
}


template <class T>
inline null_ok<T>* allow_null(T* p)
{
    return (null_ok<T>*)p;
}


    template <class Y>
    explicit handle(Y* p)
        : m_p(
            python::upcast<T>(
                detail::manage_ptr(p, 0)
                )
            )
    {
    }


    handle& operator=(handle const& r)
    {
        python::xdecref(m_p);
        m_p = python::xincref(r.m_p);
        return *this;
    }


    template<typename Y>
    handle& operator=(handle<Y> const & r) // never throws
    {
        python::xdecref(m_p);
        m_p = python::xincref(python::upcast<T>(r.get()));
        return *this;
    }


    template <typename Y>
    handle(handle<Y> const& r)
        : m_p(python::xincref(python::upcast<T>(r.get())))
    {
    }

    
    handle(handle const& r)
        : m_p(python::xincref(r.m_p))
    {
    }

    
    operator bool_type() const // never throws
    {
        return m_p ? &handle<T>::get : 0;
    }


template<class T> inline T * get_pointer(python::handle<T> const & p)
{
    return p.get();
}

template <class T>
inline handle<T>::handle()
    : m_p(0)
{
}


template <class T>
inline handle<T>::~handle()
{
    python::xdecref(m_p);
}


template <class T>
inline T* handle<T>::operator->() const
{
    return m_p;
}


template <class T>
inline T& handle<T>::operator*() const
{
    return *m_p;
}


template <class T>
inline T* handle<T>::get() const
{
    return m_p;
}

    
template <class T>
inline bool handle<T>::operator!() const
{
    return m_p == 0;
}


template <class T>
inline T* handle<T>::release()
{
    T* result = m_p;
    m_p = 0;
    return result;
}


template <class T>
inline void handle<T>::reset()
{
    python::xdecref(m_p);
    m_p = 0;
}

template <class T>
inline PyObject* get_managed_object(handle<T> const& h, tag_t)
{
    return h.get() ? python::upcast<PyObject>(h.get()) : Py_None;
}

    long_() {}


    template <class T>
    explicit long_(T const& rhs)
        : detail::long_base(object(rhs))
    {
    }


    template <class T, class U>
    explicit long_(T const& rhs, U const& base)
        : detail::long_base(object(rhs), object(base))
    {
    }

      write_type_id(type_info**p) : p(p) {}

      template <class T>
      void operator()(T*) const
      {
          *(*p)++ = type_id<T>();
      }

    
    template <class Default>
    void not_a_derived_class_member(Default) {}

        template <class Default>
        static void
        must_be_derived_class_member(Default const&)
        {
            // https://svn.boost.org/trac/boost/ticket/5803
            //typedef typename assertion<mpl::not_<is_same<Default,Fn> > >::failed test0;
# if !BOOST_WORKAROUND(__MWERKS__, <= 0x2407)
            typedef typename assertion<is_polymorphic<T> >::failed test1;
# endif 
            typedef typename assertion<is_member_function_pointer<Fn> >::failed test2;
            not_a_derived_class_member<Default>(Fn());
        }

        
        id_vector()
        {
            // Stick the derived class id into the first element of the array
            ids[0] = detail::unwrap_type_id((W*)0, (W*)0);

            // Write the rest of the elements into succeeding positions.
            type_info* p = ids + 1;
            mpl::for_each(detail::write_type_id(&p), (bases*)0, (add_pointer<mpl::_>*)0);
        }

    template <class Derived>
    self& def(def_visitor<Derived> const& visitor)
    {
        visitor.visit(*this);
        return *this;
    }

    template <class F>
    self& def(char const* name, F f)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, f, detail::def_helper<char const*>(0), &f);
        return *this;
    }


    template <class A1, class A2>
    self& def(char const* name, A1 a1, A2 const& a2)
    {
        this->def_maybe_overloads(name, a1, a2, &a2);
        return *this;
    }


    template <class Fn, class A1, class A2>
    self& def(char const* name, Fn fn, A1 const& a1, A2 const& a2)
    {
        //  The arguments are definitely:
        //      def(name, function, policy, doc_string)
        //      def(name, function, doc_string, policy)

        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, fn
          , detail::def_helper<A1,A2>(a1,a2)
          , &fn);

        return *this;
    }


    template <class Fn, class A1, class A2, class A3>
    self& def(char const* name, Fn fn, A1 const& a1, A2 const& a2, A3 const& a3)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name, fn
          , detail::def_helper<A1,A2,A3>(a1,a2,a3)
          , &fn);

        return *this;
    }

    template <class D>
    self& def_readonly(char const* name, D const& d, char const* doc=0)
    {
        return this->def_readonly_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }


    template <class D>
    self& def_readwrite(char const* name, D const& d, char const* doc=0)
    {
        return this->def_readwrite_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }

    
    template <class D>
    self& def_readonly(char const* name, D& d, char const* doc=0)
    {
        return this->def_readonly_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }


    template <class D>
    self& def_readwrite(char const* name, D& d, char const* doc=0)
    {
        return this->def_readwrite_impl(name, d, doc BOOST_PYTHON_DATA_MEMBER_HELPER(D));
    }

    template <class Get>
    self& add_property_impl(char const* name, Get fget, char const* docstr, int)
    {
        base::add_property(name, this->make_getter(fget), docstr);
        return *this;
    }


    template <class Get, class Set>
    self& add_property_impl(char const* name, Get fget, Set fset, ...)
    {
        base::add_property(
            name, this->make_getter(fget), this->make_setter(fset), 0);
        return *this;
    }
    
    template <class Get>
    self& add_property(char const* name, Get fget)
    {
        base::add_property(name, this->make_getter(fget), 0);
        return *this;
    }


    template <class Get, class DocStrOrSet>
    self& add_property(char const* name, Get fget, DocStrOrSet docstr_or_set)
    {
        this->add_property_impl(name, this->make_getter(fget), docstr_or_set, 0);
        return *this;
    }


    template <class Get, class Set>
    self&
    add_property(char const* name, Get fget, Set fset, char const* docstr)
    {
        base::add_property(
            name, this->make_getter(fget), this->make_setter(fset), docstr);
        return *this;
    }

        
    template <class Get>
    self& add_static_property(char const* name, Get fget)
    {
        base::add_static_property(name, object(fget));
        return *this;
    }


    template <class Get, class Set>
    self& add_static_property(char const* name, Get fget, Set fset)
    {
        base::add_static_property(name, object(fget), object(fset));
        return *this;
    }

        
    template <class U>
    self& setattr(char const* name, U const& x)
    {
        this->base::setattr(name, object(x));
        return *this;
    }

    template <typename PickleSuiteType>
    self& def_pickle(PickleSuiteType const& x)
    {
      error_messages::must_be_derived_from_pickle_suite(x);
      detail::pickle_suite_finalize<PickleSuiteType>::register_(
        *this,
        &PickleSuiteType::getinitargs,
        &PickleSuiteType::getstate,
        &PickleSuiteType::setstate,
        PickleSuiteType::getstate_manages_dict());
      return *this;
    }


    self& enable_pickling()
    {
        this->base::enable_pickling_(false);
        return *this;
    }


    self& staticmethod(char const* name)
    {
        this->make_method_static(name);
        return *this;
    }

    template <class F>
    object make_getter(F f)
    {
        typedef typename api::is_object_operators<F>::type is_obj_or_proxy;
        
        return this->make_fn_impl(
            detail::unwrap_wrapper((W*)0)
          , f, is_obj_or_proxy(), (char*)0, detail::is_data_member_pointer<F>()
        );
    }

    
    template <class F>
    object make_setter(F f)
    {
        typedef typename api::is_object_operators<F>::type is_obj_or_proxy;
        
        return this->make_fn_impl(
            detail::unwrap_wrapper((W*)0)
          , f, is_obj_or_proxy(), (int*)0, detail::is_data_member_pointer<F>()
        );
    }

    
    template <class T, class F>
    object make_fn_impl(T*, F const& f, mpl::false_, void*, mpl::false_)
    {
        return python::make_function(f, default_call_policies(), detail::get_signature(f, (T*)0));
    }

    
    template <class D, class B>
    self& def_readonly_impl(
        char const* name, D B::*pm_, char const* doc BOOST_PYTHON_YES_DATA_MEMBER)
    {
        return this->add_property(name, pm_, doc);
    }


    template <class D, class B>
    self& def_readwrite_impl(
        char const* name, D B::*pm_, char const* doc BOOST_PYTHON_YES_DATA_MEMBER)
    {
        return this->add_property(name, pm_, pm_, doc);
    }


    template <class D>
    self& def_readonly_impl(
        char const* name, D& d, char const* BOOST_PYTHON_NO_DATA_MEMBER)
    {
        return this->add_static_property(name, python::make_getter(d));
    }


    template <class D>
    self& def_readwrite_impl(
        char const* name, D& d, char const* BOOST_PYTHON_NO_DATA_MEMBER)
    {
        return this->add_static_property(name, python::make_getter(d), python::make_setter(d));
    }


    template <class DefVisitor>
    inline void initialize(DefVisitor const& i)
    {
        metadata::register_(); // set up runtime metadata/conversions
        
        typedef typename metadata::holder holder;
        this->set_instance_size( objects::additional_instance_size<holder>::value );
        
        this->def(i);
    }

    
    inline void initialize(no_init_t)
    {
        metadata::register_(); // set up runtime metadata/conversions
        this->def_no_init();
    }

    template <class T, class Helper, class LeafVisitor, class Visitor>
    inline void def_impl(
        T*
      , char const* name
      , LeafVisitor
      , Helper const& helper
      , def_visitor<Visitor> const* v
    )
    {
        v->visit(*this, name,  helper);
    }


    template <class T, class Fn, class Helper>
    inline void def_impl(
        T*
      , char const* name
      , Fn fn
      , Helper const& helper
      , ...
    )
    {
        objects::add_to_namespace(
            *this
          , name
          , make_function(
                fn
              , helper.policies()
              , helper.keywords()
              , detail::get_signature(fn, (T*)0)
            )
          , helper.doc()
        );

        this->def_default(name, fn, helper, mpl::bool_<Helper::has_default_implementation>());
    }

    template <class Fn, class Helper>
    inline void def_default(
        char const* name
        , Fn
        , Helper const& helper
        , mpl::bool_<true>)
    {
        detail::error::virtual_function_default<W,Fn>::must_be_derived_class_member(
            helper.default_implementation());
            
        objects::add_to_namespace(
            *this, name,
            make_function(
                helper.default_implementation(), helper.policies(), helper.keywords())
            );
    }

    template <class OverloadsT, class SigT>
    void def_maybe_overloads(
        char const* name
        , SigT sig
        , OverloadsT const& overloads
        , detail::overloads_base const*)

    {
        //  convert sig to a type_list (see detail::get_signature in signature.hpp)
        //  before calling detail::define_with_defaults.
        detail::define_with_defaults(
            name, overloads, *this, detail::get_signature(sig));
    }


    template <class Fn, class A1>
    void def_maybe_overloads(
        char const* name
        , Fn fn
        , A1 const& a1
        , ...)
    {
        this->def_impl(
            detail::unwrap_wrapper((W*)0)
          , name
          , fn
          , detail::def_helper<A1>(a1)
          , &fn
        );

    }


template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, char const* doc)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->initialize(init<>());
//  select_holder::assert_default_constructible();
}


template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, no_init_t)
    : base(name, id_vector::size, id_vector().ids)
{
    this->initialize(no_init);
}


template <class W, class X1, class X2, class X3>
inline class_<W,X1,X2,X3>::class_(char const* name, char const* doc, no_init_t)
    : base(name, id_vector::size, id_vector().ids, doc)
{
    this->initialize(no_init);
}

  template <class T, class U>
  inline type_info extractor_type_id(T&(*)(U))
  {
      return type_id<T>();
  }

      static inline void* execute(PyObject* op)
      {
          typedef typename boost::add_reference<U>::type param;
          return &Extractor::execute(
              boost::python::detail::void_ptr_to_reference(
                  op, (param(*)())0 )
              );
      }

  template <class Extractor, class T, class U>
  inline normalized_extractor<Extractor,U>
  normalize(T(*)(U), Extractor* = 0)
  {
      return normalized_extractor<Extractor, U>();
  }

    static MemberType& execute(InstanceType& c)
    {
        (void)Py_TYPE(&c); // static assertion
        return c.*member;
    }

    static InstanceType& execute(InstanceType& c)
    {
        (void)Py_TYPE(&c); // static assertion
        return c;
    }

    lvalue_from_pytype()
    {
        converter::registry::insert
            ( &extract
            , detail::extractor_type_id(&Extractor::execute)
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
            , &get_pytype
#endif
            );
    }

    static void* extract(PyObject* op)
    {
        return PyObject_TypeCheck(op, const_cast<PyTypeObject*>(python_type))
            ? const_cast<void*>(
                static_cast<void const volatile*>(
                    detail::normalize<Extractor>(&Extractor::execute).execute(op)))
            : 0
            ;
    }

    
    operator result_type() const
    {
        return (*this)();
    }


template <class T>
inline extract<T>::extract(api::object const& o)
    : base(o.ptr())
{
}

  
  template <class T>
  inline bool
  extract_rvalue<T>::check() const
  {
      return m_data.stage1.convertible;
  }


  template <class Ref>
  inline bool extract_reference<Ref>::check() const
  {
      return m_result != 0;
  }


  template <class Ref>
  inline Ref extract_reference<Ref>::operator()() const
  {
      if (m_result == 0)
          (throw_no_reference_from_python)(m_source, registered<Ref>::converters);
      
      return python::detail::void_ptr_to_reference(m_result, (Ref(*)())0);
  }


  template <class Ptr>
  inline bool extract_pointer<Ptr>::check() const
  {
      return m_source == Py_None || m_result != 0;
  }


  template <class Ptr>
  inline Ptr extract_pointer<Ptr>::operator()() const
  {
      if (m_result == 0 && m_source != Py_None)
          (throw_no_pointer_from_python)(m_source, registered_pointee<Ptr>::converters);
      
      return Ptr(m_result);
  }


  template <class T>
  inline bool extract_object_manager<T>::check() const
  {
      return object_manager_traits<T>::check(m_source);
  }


  template <class T>
  inline T extract_object_manager<T>::operator()() const
  {
      return T(
          object_manager_traits<T>::adopt(python::incref(m_source))
          );
  }

              static bool convertible()
              {
                  return true;
              }

              
              PyObject *operator()( typename value_arg<T>::type ) const
              {
                  return none();
              }


    template <class ArgumentPackage>
    static PyObject* postcall(ArgumentPackage const& args, PyObject* result)
    {
        // In case of arg_pos == 0 we could simply return Base::postcall,
        // but this is redundant
        BOOST_STATIC_ASSERT(arg_pos > 0);

        result = Base::postcall(args,result);
        if (!result)
            return 0;
        Py_DECREF(result);
        return incref( detail::get(mpl::int_<arg_pos-1>(),args) );
    }

    slice_nil() : object() {}

    
    explicit pointer_wrapper(Ptr x): p_(x) {}

    operator Ptr() const { return p_; }

    Ptr get() const { return p_; }


template<class T>
inline pointer_wrapper<T> ptr(T t)
{ 
    return pointer_wrapper<T>(t);
}

      
      keyword_range range() const
      {
          return keyword_range(elements, elements + nkeywords);
      }

      explicit keywords(char const *name)
      {
          elements[0].name = name;
      }

    
      template <class T>
      python::arg& operator=(T const& value)
      {
          object z(value);
          elements[0].default_value = handle<>(python::borrowed(object(value).ptr()));
          return *this;
      }


  template <std::size_t nkeywords>
  inline
  keywords<nkeywords+1>
  keywords_base<nkeywords>::operator,(python::arg const &k) const
  {
      keywords<nkeywords> const& l = *static_cast<keywords<nkeywords> const*>(this);
      python::detail::keywords<nkeywords+1> res;
      std::copy(l.elements, l.elements+nkeywords, res.elements);
      res.elements[nkeywords] = k.elements[0];
      return res;
  }


  template <std::size_t nkeywords>
  inline
  keywords<nkeywords + 1>
  keywords_base<nkeywords>::operator,(char const *name) const
  {
      return this->operator,(python::arg(name));
  }


inline detail::keywords<1> args(char const* name)
{ 
    return detail::keywords<1>(name);
}


inline bool decorated_type_info::operator<(decorated_type_info const& rhs) const
{
    return m_decoration < rhs.m_decoration
      || (m_decoration == rhs.m_decoration
          && m_base_type < rhs.m_base_type);
}


inline bool decorated_type_info::operator==(decorated_type_info const& rhs) const
{
    return m_decoration == rhs.m_decoration && m_base_type == rhs.m_base_type;
}

    nullary_function_adaptor(NullaryFunction fn)
      : m_fn(fn)
    {}


    void operator()() const { m_fn(); }


    inline PyObject*
    owner_impl(void const volatile* /*x*/, mpl::false_)
    {
        return 0;
    }

    
    template <class T>
    inline PyObject*
    owner(T const volatile* x)
    {
        return wrapper_base_::owner_impl(x,is_polymorphic<T>());
    }


inline unsigned arity(PyObject* const& args_)
{
    return PyTuple_GET_SIZE(args_);
}


template <class ArgPackage, class ResultConverter>
inline ResultConverter create_result_converter(
    ArgPackage const& args_
  , ResultConverter*
  , converter::context_result_converter*
)
{
    return ResultConverter(args_);
}

    
template <class ArgPackage, class ResultConverter>
inline ResultConverter create_result_converter(
    ArgPackage const&
  , ResultConverter*
  , ...
)
{
    return ResultConverter();
}

    
    caller(F f, CallPolicies p) : base(f,p) {}


template <class T>
inline void force_instantiate(T const&) {}
 

template <class T>
inline type_info unwrap_type_id(T*, ...)
{
    return type_id<T>();
}


    static void *converter (PyObject *p){
        return p;
    }


    static void register_()
    {
        static bool first_time = true;

        if ( !first_time ) return;

        first_time = false;
        converter::registry::insert(&converter, boost::python::type_id<this_type>(), &converter::registered_pytype_direct<T>::get_pytype);
    }

    void_return() {}

      overloads_base(char const* doc_)
          : m_doc(doc_) {}


      char const* doc_string() const
      {
          return m_doc;
      }


      overloads_proxy(
          CallPoliciesT const& policies_
          , char const* doc
          , keyword_range const& kw
          )
          : overloads_base(doc, kw)
            , policies(policies_)
      {}


      CallPoliciesT
      call_policies() const
      {
          return policies;
      }

      overloads_common(char const* doc)
          : overloads_base(doc) {}


      default_call_policies
      call_policies() const
      {
          return default_call_policies();
      }


      template <class CallPoliciesT>
      overloads_proxy<CallPoliciesT, DerivedT>
      operator[](CallPoliciesT const& policies) const
      {
          return overloads_proxy<CallPoliciesT, DerivedT>(
              policies, this->doc_string(), this->keywords());
      }

    map_entry() {}

    map_entry(Key k) : key(k), value() {}

    map_entry(Key k, Value v) : key(k), value(v) {}

    
    bool operator<(map_entry const& rhs) const
    {
        return this->key < rhs.key;
    }


template <class Key, class Value>
bool operator<(map_entry<Key,Value> const& e, Key const& k)
{
    return e.key < k;
}


template <class Key, class Value>
bool operator<(Key const& k, map_entry<Key,Value> const& e)
{
    return k < e.key;
}


template <class R, class T>
T& (* target(R (T::*)) )() { return 0; }

template <class F, class Policies>
object make_keyword_range_function(
    F f
  , Policies const& policies
  , keyword_range const& kw)
{
    return detail::make_function_aux(
        f, policies, detail::get_signature(f), kw, mpl::int_<0>());
}

template <class ArgList, class Arity, class Holder, class CallPolicies>
object make_keyword_range_constructor(
    CallPolicies const& policies        // The CallPolicies with which to invoke the Holder's constructor
    , detail::keyword_range const& kw   // The (possibly empty) set of associated argument keywords
    , Holder* = 0                       
    , ArgList* = 0, Arity* = 0)
{
#if !defined( BOOST_PYTHON_NO_PY_SIGNATURES) && defined( BOOST_PYTHON_PY_SIGNATURES_PROPER_INIT_SELF_TYPE)
    python_class<BOOST_DEDUCED_TYPENAME Holder::value_type>::register_();
#endif
    return detail::make_keyword_range_function(
        objects::make_holder<Arity::value>
            ::template apply<Holder,ArgList>::execute
        , policies
        , kw);
}

          
          static typename Tuple::head_type extract(Tuple const& x)
          {
              return x.get_head();
          }

          
          static result_type extract(Tuple const& x)
          {
              return next::extract(x.get_tail());
          }

      def_helper(T1 const& a1) : m_all(a1,m_nil,m_nil,m_nil) {}

      def_helper(T1 const& a1, T2 const& a2) : m_all(a1,a2,m_nil,m_nil) {}

      def_helper(T1 const& a1, T2 const& a2, T3 const& a3) : m_all(a1,a2,a3,m_nil) {}

      def_helper(T1 const& a1, T2 const& a2, T3 const& a3, T4 const& a4) : m_all(a1,a2,a3,a4) {}

      char const* doc() const
      {
          return doc_extract<all_t>::extract(m_all);
      }


template <class T>
inline T* get_managed_object(detail::borrowed<T> const volatile* p, tag_t)
{
    return (T*)p;
}


template <class Generator, class U>
inline typename Generator::result_type
unwind_type_cv(U* p, cv_unqualified, Generator* = 0)
{
    return Generator::execute(p);
}


template <class Generator, class U>
inline typename Generator::result_type
unwind_ptr_type(U* p, Generator* = 0)
{
    typedef typename cv_category<U>::type tag;
    return unwind_type_cv<Generator>(p, tag());
}

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U p, Generator* = 0)
    {
        return unwind_ptr_type(p, (Generator*)0);
    }

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U& p, Generator* = 0)
    {
        return unwind_ptr_type(&p, (Generator*)0);
    }


template <class Generator, class U>
inline typename Generator::result_type
#ifndef _MSC_VER
unwind_type(U const& p, Generator*)
#else
unwind_type(U const& p, Generator* = 0)
#endif
{
    return unwind_helper<is_pointer<U>::value>::execute(p, (Generator*)0);
}

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U*(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U&(*)(), Generator* = 0)
    {
        return unwind_ptr_type((U*)0, (Generator*)0);
    }

    template <class Generator, class U>
    static typename Generator::result_type
    execute(U&(*)(), Generator* = 0)
    {
        return unwind_ptr_type(U(0), (Generator*)0);
    }
 

template <class U>
inline U& void_ptr_to_reference(void const volatile* p, U&(*)())
{
    return *(U*)p;
}


template <class T>
inline void write_void_ptr(void const volatile* storage, void* ptr, T*)
{
    *(T**)storage = (T*)ptr;
}

template <class U>
inline void write_void_ptr_reference(void const volatile* storage, void* ptr, U&(*)())
{
    // stripping CV qualification suppresses warnings on older EDGs
    typedef typename remove_cv<U>::type u_stripped; 
    write_void_ptr(storage, ptr, u_stripped(0));
}

    template <class T>
    static void execute(T const volatile* p)
    {
        p->~T();
    }

    template <class A, class T>
    static void execute(A*, T const volatile* const first)
    {
        for (T const volatile* p = first; p != first + sizeof(A)/sizeof(T); ++p)
        {
            value_destroyer<
                boost::is_array<T>::value
# if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
              , boost::is_enum<T>::value
# endif 
            >::execute(p);
        }
    }

    
    template <class T>
    static void execute(T const volatile* p)
    {
        execute(p, *p);
    }
 
template <class T>
inline void destroy_referent_impl(void* p, T& (*)())
{
    // note: cv-qualification needed for MSVC6
    // must come *before* T for metrowerks
    value_destroyer<
         (boost::is_array<T>::value)
# if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
       , (boost::is_enum<T>::value)
# endif 
    >::execute((const volatile T*)p);
}


template <class T>
inline void destroy_referent(void* p, T(*)() = 0)
{
    destroy_referent_impl(p, (T(*)())0);
}


inline PyObject* none() { Py_INCREF(Py_None); return Py_None; }

        inline void dealloc(PyObject* self)
        {
          PyObject_Del(self);
        }

    decref_guard(PyObject* o) : obj(o) {}

    ~decref_guard() { Py_XDECREF(obj); }

    void cancel() { obj = 0; }

  template <class Func, class CallPolicies, class NameSpaceT>
  static void name_space_def(
      NameSpaceT& name_space
      , char const* name
      , Func f
      , keyword_range const& kw
      , CallPolicies const& policies
      , char const* doc
      , objects::class_base*
      )
  {
      typedef typename NameSpaceT::wrapped_type wrapped_type;
      
      objects::add_to_namespace(
          name_space, name,
          detail::make_keyword_range_function(
              f, policies, kw, get_signature(f, (wrapped_type*)0))
        , doc
      );
  }


      template <class StubsT, class CallPolicies, class NameSpaceT>
      static void
      def(
          char const* name,
          StubsT stubs,
          keyword_range kw,
          CallPolicies const& policies,
          NameSpaceT& name_space,
          char const* doc)
      {
          //  define the NTH stub function of stubs
          define_stub_function<N>::define(name, stubs, kw, policies, name_space, doc);

          if (kw.second > kw.first)
              --kw.second;

          //  call the next define_with_defaults_helper
          define_with_defaults_helper<N-1>::def(name, stubs, kw, policies, name_space, doc);
      }


      template <class StubsT, class CallPolicies, class NameSpaceT>
      static void
      def(
          char const* name,
          StubsT stubs,
          keyword_range const& kw,
          CallPolicies const& policies,
          NameSpaceT& name_space,
          char const* doc)
      {
          //  define the Oth stub function of stubs
          define_stub_function<0>::define(name, stubs, kw, policies, name_space, doc);
          //  return
      }

  template <class OverloadsT, class NameSpaceT, class SigT>
  inline void
  define_with_defaults(
      char const* name,
      OverloadsT const& overloads,
      NameSpaceT& name_space,
      SigT const&)
  {
      typedef typename mpl::front<SigT>::type return_type;
      typedef typename OverloadsT::void_return_type void_return_type;
      typedef typename OverloadsT::non_void_return_type non_void_return_type;

      typedef typename mpl::if_c<
          boost::is_same<void, return_type>::value
          , void_return_type
          , non_void_return_type
      >::type stubs_type;

      BOOST_STATIC_ASSERT(
          (stubs_type::max_args) <= mpl::size<SigT>::value);

      typedef typename stubs_type::template gen<SigT> gen_type;
      define_with_defaults_helper<stubs_type::n_funcs-1>::def(
          name
          , gen_type()
          , overloads.keywords()
          , overloads.call_policies()
          , name_space
          , overloads.doc_string());
  }
 

template <class T, class Arg>
void construct_pointee(void* storage, Arg& x
# if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
                       , T const volatile*
# else 
                       , T const*
# endif 
    )
{
    new (storage) T(x);
}


template <class T, class Arg>
void construct_referent_impl(void* storage, Arg& x, T&(*)())
{
    construct_pointee(storage, x, (T*)0);
}


template <class T, class Arg>
void construct_referent(void* storage, Arg const& x, T(*tag)() = 0)
{
    construct_referent_impl(storage, x, tag);
}


template <class T, class Arg>
void construct_referent(void* storage, Arg& x, T(*tag)() = 0)
{
    construct_referent_impl(storage, x, tag);
}

    
    inline bool operator()(
        exception_handler const& handler
      , function0<void> const& f
      , typename call_traits<Translate>::param_type translate) const
    {
        try
        {
            return handler(f);
        }
// workaround for broken gcc that ships with SuSE 9.0 and SuSE 9.1
# if defined(__linux__) && defined(__GNUC__) \
    && BOOST_WORKAROUND(__GNUC__, == 3) \
    && BOOST_WORKAROUND(__GNUC_MINOR__, == 3) \
    && (BOOST_WORKAROUND(__GNUC_PATCHLEVEL__, == 1) \
        || BOOST_WORKAROUND(__GNUC_PATCHLEVEL__, == 3))
        catch(exception_non_ref& e)
# else
        catch(exception_cref e)
# endif
        {
            translate(e);
            return true;
        }
    }


template <class T>
typename unwrap_wrapper_<T>::type*
unwrap_wrapper(T*)
{
    return 0;
}

    static inline no_convertible check(...) { return 0; }

    static inline yes_convertible check(Target) { return 0; }

        
        template <class Class>
        static void 
        extension_def(Class& cl)
        {
            cl
                .def("append", &base_append)
                .def("extend", &base_extend)
            ;
        }

        
    template <typename Container>
    void
    extend_container(Container& container, object l)
    {
        typedef typename Container::value_type data_type;
        
        //  l must be iterable
        BOOST_FOREACH(object elem,
            std::make_pair(
              boost::python::stl_input_iterator<object>(l),
              boost::python::stl_input_iterator<object>()
              ))
        {
            extract<data_type const&> x(elem);
            //  try if elem is an exact data_type type
            if (x.check())
            {
                container.push_back(x());
            }
            else
            {
                //  try to convert elem to data_type type
                extract<data_type> x(elem);
                if (x.check())
                {
                    container.push_back(x());
                }
                else
                {
                    PyErr_SetString(PyExc_TypeError, "Incompatible Data Type");
                    throw_error_already_set();
                }
            }
        }          
    }


        template <class Class>
        static void
        extension_def(Class& cl)
        {
            //  Wrap the map's element (value_type)
            std::string elem_name = "map_indexing_suite_";
            object class_name(cl.attr("__name__"));
            extract<std::string> class_name_extractor(class_name);
            elem_name += class_name_extractor();
            elem_name += "_entry";

            typedef typename mpl::if_<
                mpl::and_<is_class<data_type>, mpl::bool_<!NoProxy> >
              , return_internal_reference<>
              , default_call_policies
            >::type get_data_return_policy;

            class_<value_type>(elem_name.c_str())
                .def("__repr__", &DerivedPolicies::print_elem)
                .def("data", &DerivedPolicies::get_data, get_data_return_policy())
                .def("key", &DerivedPolicies::get_key)
            ;
        }


        static object
        print_elem(typename Container::value_type const& e)
        {
            return "(%s, %s)" % python::make_tuple(e.first, e.second);
        }


        template <class Class>
        void visit(Class& cl) const
        {
            // Hook into the class_ generic visitation .def function
            proxy_handler::register_container_element();

            cl
                .def("__len__", base_size)
                .def("__setitem__", &base_set_item)
                .def("__delitem__", &base_delete_item)
                .def("__getitem__", &base_get_item)
                .def("__contains__", &base_contains)
                .def("__iter__", def_iterator())
            ;

            DerivedPolicies::extension_def(cl);
        }


        template <class Class>
        static void
        extension_def(Class& cl)
        {
            // default.
            // no more extensions
        }


        static object
        base_get_item(back_reference<Container&> container, PyObject* i)
        {
            if (PySlice_Check(i))
                return slice_handler::base_get_slice(
                    container.get(), static_cast<PySliceObject*>(static_cast<void*>(i)));

            return proxy_handler::base_get_item_(container, i);
        }


        static void
        base_set_item(Container& container, PyObject* i, PyObject* v)
        {
            if (PySlice_Check(i))
            {
                 slice_handler::base_set_slice(container,
                     static_cast<PySliceObject*>(static_cast<void*>(i)), v);
            }
            else
            {
                extract<Data&> elem(v);
                // try if elem is an exact Data
                if (elem.check())
                {
                    DerivedPolicies::
                        set_item(container,
                            DerivedPolicies::
                                convert_index(container, i), elem());
                }
                else
                {
                    //  try to convert elem to Data
                    extract<Data> elem(v);
                    if (elem.check())
                    {
                        DerivedPolicies::
                            set_item(container,
                                DerivedPolicies::
                                    convert_index(container, i), elem());
                    }
                    else
                    {
                        PyErr_SetString(PyExc_TypeError, "Invalid assignment");
                        throw_error_already_set();
                    }
                }
            }
        }


        static void
        base_delete_item(Container& container, PyObject* i)
        {
            if (PySlice_Check(i))
            {
                slice_handler::base_delete_slice(
                    container, static_cast<PySliceObject*>(static_cast<void*>(i)));
                return;
            }

            Index index = DerivedPolicies::convert_index(container, i);
            proxy_handler::base_erase_index(container, index, mpl::bool_<NoSlice>());
            DerivedPolicies::delete_item(container, index);
        }


        static size_t
        base_size(Container& container)
        {
            return DerivedPolicies::size(container);
        }


        static bool
        base_contains(Container& container, PyObject* key)
        {
            extract<Key const&> x(key);
            //  try if key is an exact Key type
            if (x.check())
            {
                return DerivedPolicies::contains(container, x());
            }
            else
            {
                //  try to convert key to Key type
                extract<Key> x(key);
                if (x.check())
                    return DerivedPolicies::contains(container, x());
                else
                    return false;
            }
        }

                
        template <class Index>
        bool operator()(PyObject* prox, Index i) const
        {
            typedef typename Proxy::policies_type policies_type;
            Proxy& proxy = extract<Proxy&>(prox)();
            return policies_type::
                compare_index(proxy.get_container(), proxy.get_index(), i);
        }

        
        iterator
        first_proxy(index_type i)
        {
            // Return the first proxy with index <= i
            return boost::detail::lower_bound(
                proxies.begin(), proxies.end(), 
                i, compare_proxy_index<Proxy>());
        }


        void
        remove(Proxy& proxy)
        {
            // Remove a proxy
            for (iterator iter = first_proxy(proxy.get_index());
                iter != proxies.end(); ++iter)
            {
                if (&extract<Proxy&>(*iter)() == &proxy)
                {
                    proxies.erase(iter);
                    break;
                }
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }


        void
        add(PyObject* prox)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Add a proxy
            proxies.insert(
                first_proxy(extract<Proxy&>(prox)().get_index()), prox);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }


        void
        erase(index_type i, mpl::false_)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase the proxy with index i 
            replace(i, i+1, 0);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }


        void
        erase(index_type from, index_type to)
        {
            // note: this cannot be called when container is not sliceable
            
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase all proxies with indexes from..to 
            replace(from, to, 0);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }


        void
        replace(
            index_type from, 
            index_type to, 
            typename std::vector<PyObject*>::size_type len)
        {
            // note: this cannot be called when container is not sliceable

            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase all proxies with indexes from..to.
            // Adjust the displaced indexes such that the
            // final effect is that we have inserted *len*
            // number of proxies in the vacated region. This
            // procedure involves adjusting the indexes of 
            // the proxies.
            
            iterator left = first_proxy(from);
            iterator right = proxies.end(); // we'll adjust this later
            
            for (iterator iter = left; iter != right; ++iter)
            {
                if (extract<Proxy&>(*iter)().get_index() > to)
                {
                    right = iter; // adjust right
                    break;
                }
                extract<Proxy&> p(*iter);
                p().detach();
            }
            
            typename std::vector<PyObject*>::size_type 
                offset = left-proxies.begin();
            proxies.erase(left, right);
            right = proxies.begin()+offset;

            while (right != proxies.end())
            {
                typedef typename Proxy::container_type::difference_type difference_type;
                extract<Proxy&> p(*right);
                p().set_index(
                    extract<Proxy&>(*right)().get_index() 
                    - (difference_type(to) - from - len)
                );
                    
                ++right;
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        
        PyObject*
        find(index_type i)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Find the proxy with *exact* index i.
            // Return 0 (null) if no proxy with the 
            // given index is found.
            iterator iter = first_proxy(i);
            if (iter != proxies.end()
                && extract<Proxy&>(*iter)().get_index() == i)
            {
                BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
                return *iter;
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            return 0;
        }


        void
        remove(Proxy& proxy)
        {
            // Remove a proxy.
            typename links_t::iterator r = links.find(&proxy.get_container());
            if (r != links.end())
            {
                r->second.remove(proxy);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }

        
        void
        add(PyObject* prox, Container& container)
        {
            // Add a proxy
            links[&container].add(prox);
        }

        
        template <class NoSlice>
        void erase(Container& container, index_type i, NoSlice no_slice)
        {
            // Erase the proxy with index i 
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.erase(i, no_slice);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }

        
        void
        erase(Container& container, index_type from, index_type to)
        {
            // Erase all proxies with indexes from..to 
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.erase(from, to);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }


        void
        replace(
            Container& container, 
            index_type from, index_type to, index_type len)
        {
            // Erase all proxies with indexes from..to.
            // Adjust the displaced indexes such that the
            // final effect is that we have inserted *len*
            // number of proxies in the vacated region. This
            // procedure involves adjusting the indexes of 
            // the proxies.

            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.replace(from, to, len);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }

        
        PyObject*
        find(Container& container, index_type i)
        {
            // Find the proxy with *exact* index i.
            // Return 0 (null) if no proxy with the given 
            // index is found.
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
                return r->second.find(i);
            return 0;
        }

        
        container_element(object container, Index index)
            : ptr()
            , container(container)
            , index(index)
        {
        }

            
        container_element(container_element const& ce)
          : ptr(ce.ptr.get() == 0 ? 0 : new element_type(*ce.ptr.get()))
          , container(ce.container)
          , index(ce.index)
        {
        }


        ~container_element()
        {
            if (!is_detached())
                get_links().remove(*this);
        }

                      
        element_type& operator*() const
        {
            if (is_detached())
                return *get_pointer(ptr);
            return Policies::get_item(get_container(), index);
        }

        
        element_type* get() const
        {
            if (is_detached())
                return get_pointer(ptr);
            return &Policies::get_item(get_container(), index);
        }

        
        void
        detach()
        {
            if (!is_detached())
            {
                ptr.reset(
                    new element_type(
                        Policies::get_item(get_container(), index)));
                container = object(); // free container. reset it to None
            }
        }

        
        bool
        is_detached() const
        {
            return get_pointer(ptr) != 0;
        }


        Container& 
        get_container() const
        {
            return extract<Container&>(container)();
        }

        
        Index 
        get_index() const
        {
            return index;
        }


        void 
        set_index(Index i)
        {
            index = i;
        }

 
        static proxy_links<self_t, Container>&
        get_links()
        {
            // All container_element(s) maintain links to
            // its container in a global map (see proxy_links).
            // This global "links" map is a singleton.
            
            static proxy_links<self_t, Container> links;
            return links; // singleton
        }
                
        static void
        register_container_element()
        { 
        }


        template <class DataType> 
        static object
        base_get_item_helper(DataType const& p, mpl::true_)
        { 
            return object(ptr(p));
        }


        static object
        base_get_item_(back_reference<Container&> const& container, PyObject* i)
        { 
            return base_get_item_helper(
                DerivedPolicies::get_item(
                    container.get(), DerivedPolicies::
                        convert_index(container.get(), i))
              , is_pointer<BOOST_DEDUCED_TYPENAME Container::value_type>()
            );
        }


        static void
        base_replace_indexes(
            Container& /*container*/, Index /*from*/, 
            Index /*to*/, Index /*n*/)
        {
        }


        template <class NoSlice>
        static void
        base_erase_index(
            Container& /*container*/, Index /*i*/, NoSlice /*no_slice*/)
        {
        }

        
        static void
        base_erase_indexes(Container& /*container*/, Index /*from*/, Index /*to*/)
        {
        }
        
        static void
        register_container_element()
        { 
            register_ptr_to_python<ContainerElement>();
        }


        static object
        base_get_item_(back_reference<Container&> const& container, PyObject* i)
        { 
            // Proxy
            Index idx = DerivedPolicies::convert_index(container.get(), i);

            if (PyObject* shared = 
                ContainerElement::get_links().find(container.get(), idx))
            {
                handle<> h(python::borrowed(shared));
                return object(h);
            }
            else
            {
                object prox(ContainerElement(container.source(), idx));
                ContainerElement::
                    get_links().add(prox.ptr(), container.get());
                return prox;
            }
        }


        static void
        base_replace_indexes(
            Container& container, Index from, 
            Index to, Index n)
        {
            ContainerElement::get_links().replace(container, from, to, n);
        }

        
        template <class NoSlice>
        static void
        base_erase_index(
            Container& container, Index i, NoSlice no_slice)
        {
            ContainerElement::get_links().erase(container, i, no_slice);
        }

        
        static void
        base_erase_indexes(
            Container& container, Index from, Index to)
        {
            ContainerElement::get_links().erase(container, from, to);
        }
        
        static object 
        base_get_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            return DerivedPolicies::get_slice(container, from, to);
        }


        static void
        base_get_slice_data(
            Container& container, PySliceObject* slice, Index& from_, Index& to_)
        {
            if (Py_None != slice->step) {
                PyErr_SetString( PyExc_IndexError, "slice step size not supported.");
                throw_error_already_set();
            }

            Index min_index = DerivedPolicies::get_min_index(container);
            Index max_index = DerivedPolicies::get_max_index(container);
            
            if (Py_None == slice->start) {
                from_ = min_index;
            }
            else {
                long from = extract<long>( slice->start);
                if (from < 0) // Negative slice index
                    from += max_index;
                if (from < 0) // Clip lower bounds to zero
                    from = 0;
                from_ = boost::numeric_cast<Index>(from);
                if (from_ > max_index) // Clip upper bounds to max_index.
                    from_ = max_index;
            }

            if (Py_None == slice->stop) {
                to_ = max_index;
            }
            else {
                long to = extract<long>( slice->stop);
                if (to < 0)
                    to += max_index;
                if (to < 0)
                    to = 0;
                to_ = boost::numeric_cast<Index>(to);
                if (to_ > max_index)
                    to_ = max_index;
            }
        }
        
   
        static void 
        base_set_slice(Container& container, PySliceObject* slice, PyObject* v)
        {
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            
            extract<Data&> elem(v);
            // try if elem is an exact Data
            if (elem.check())
            {
                ProxyHandler::base_replace_indexes(container, from, to, 1);
                DerivedPolicies::set_slice(container, from, to, elem());
            }
            else
            {
                //  try to convert elem to Data
                extract<Data> elem(v);
                if (elem.check())
                {
                    ProxyHandler::base_replace_indexes(container, from, to, 1);
                    DerivedPolicies::set_slice(container, from, to, elem());
                }
                else
                {
                    //  Otherwise, it must be a list or some container
                    handle<> l_(python::borrowed(v));
                    object l(l_);
    
                    std::vector<Data> temp;
                    for (int i = 0; i < l.attr("__len__")(); i++)
                    {
                        object elem(l[i]);
                        extract<Data const&> x(elem);
                        //  try if elem is an exact Data type
                        if (x.check())
                        {
                            temp.push_back(x());
                        }
                        else
                        {
                            //  try to convert elem to Data type
                            extract<Data> x(elem);
                            if (x.check())
                            {
                                temp.push_back(x());
                            }
                            else
                            {
                                PyErr_SetString(PyExc_TypeError, 
                                    "Invalid sequence element");
                                throw_error_already_set();
                            }
                        }
                    }          
                  
                    ProxyHandler::base_replace_indexes(container, from, to, 
                        temp.end()-temp.begin());
                    DerivedPolicies::set_slice(container, from, to, 
                        temp.begin(), temp.end());
                }
            }            
        }

        
        static void 
        base_delete_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            ProxyHandler::base_erase_indexes(container, from, to);
            DerivedPolicies::delete_slice(container, from, to);
        }
        
        static void
        slicing_not_suported()
        {
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
        }

        
        static object 
        base_get_slice(Container& /*container*/, PySliceObject* /*slice*/)
        { 
            slicing_not_suported();
            return object();
        }

   
        static void 
        base_set_slice(Container& /*container*/, PySliceObject* /*slice*/, PyObject* /*v*/)
        {
            slicing_not_suported();
        }

        
        static void 
        base_delete_slice(Container& /*container*/, PySliceObject* /*slice*/)
        { 
            slicing_not_suported();
        }


    template <class Container, class Index, class Policies>
    inline typename Policies::data_type* 
    get_pointer(
        python::detail::container_element<Container, Index, Policies> const& p)
    {
        // Get the pointer of a container_element smart pointer
        return p.get();
    }

template <class T>
inline rvalue_from_python_data<T>::rvalue_from_python_data(rvalue_from_python_stage1_data const& _stage1)
{
    this->stage1 = _stage1;
}


template <class T>
inline rvalue_from_python_data<T>::rvalue_from_python_data(void* convertible)
{
    this->stage1.convertible = convertible;
}


template <class T>
inline rvalue_from_python_data<T>::~rvalue_from_python_data()
{
    if (this->stage1.convertible == this->storage.bytes)
        python::detail::destroy_referent<ref_type>(this->storage.bytes);
}

      object_manager_arg_to_python(T const& x) : m_src(x) {}

      
      PyObject* get() const
      {
          return python::upcast<PyObject>(get_managed_object(m_src, tag));
      }

      static void error(Convertibility)
      {
          cannot_convert_raw_PyObject<T*>::to_python_use_handle_instead();
      }

      static void error(...) {}

  
  template <class T>
  inline void reject_raw_object_ptr(T*)
  {
      reject_raw_object_helper<T,yes_convertible>::error(
          python::detail::convertible<PyObject const volatile*>::check((T*)0));
      
      typedef typename remove_cv<T>::type value_type;
      
      reject_raw_object_helper<T,no_convertible>::error(
          python::detail::convertible<unspecialized*>::check(
              (base_type_traits<value_type>*)0
              ));
  }

      
  template <class T>
  inline function_arg_to_python<T>::function_arg_to_python(T const& x)
      : handle<>(python::objects::make_function_handle(x))
  {
  }


  template <class T>
  inline value_arg_to_python<T>::value_arg_to_python(T const& x)
      : arg_to_python_base(&x, registered<T>::converters)
  {
  }


  template <class Ptr>
  inline pointer_deep_arg_to_python<Ptr>::pointer_deep_arg_to_python(Ptr x)
      : arg_to_python_base(x, registered_pointee<Ptr>::converters)
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }


  template <class T>
  inline reference_arg_to_python<T>::reference_arg_to_python(T& x)
      : handle<>(reference_arg_to_python<T>::get_object(x))
  {
  }


  template <class T>
  inline shared_ptr_arg_to_python<T>::shared_ptr_arg_to_python(T const& x)
      : handle<>(shared_ptr_to_python(x))
  {
  }


  template <class Ptr>
  inline pointer_shallow_arg_to_python<Ptr>::pointer_shallow_arg_to_python(Ptr x)
      : handle<>(pointer_shallow_arg_to_python<Ptr>::get_object(x))
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }


template <class T>
inline arg_to_python<T>::arg_to_python(T const& x)
    : base(x)
{}


inline bool operator<(registration const& lhs, registration const& rhs)
{
    return lhs.target_type < rhs.target_type;
}

    template <class U>
    static result_type execute(U* ){
        return python::type_id<U>();
    }

    shared_ptr_from_python()
    {
        converter::registry::insert(&convertible, &construct, type_id<shared_ptr<T> >()
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
                      , &converter::expected_from_python_type_direct<T>::get_pytype
#endif
                      );
    }

    static void* convertible(PyObject* p)
    {
        if (p == Py_None)
            return p;
        
        return converter::get_lvalue_from_python(p, registered<T>::converters);
    }

    
    static void construct(PyObject* source, rvalue_from_python_stage1_data* data)
    {
        void* const storage = ((converter::rvalue_from_python_storage<shared_ptr<T> >*)data)->storage.bytes;
        // Deal with the "None" case.
        if (data->convertible == source)
            new (storage) shared_ptr<T>();
        else
        {
            boost::shared_ptr<void> hold_convertible_ref_count(
              (void*)0, shared_ptr_deleter(handle<>(borrowed(source))) );
            // use aliasing constructor
            new (storage) shared_ptr<T>(
                hold_convertible_ref_count,
                static_cast<T*>(data->convertible));
        }
        
        data->convertible = storage;
    }

    static void* convertible(PyObject* obj)
    {
        // Find a converter which can produce a Source instance from
        // obj. The user has told us that Source can be converted to
        // Target, and instantiating construct() below, ensures that
        // at compile-time.
        return implicit_rvalue_convertible_from_python(obj, registered<Source>::converters)
            ? obj : 0;
    }

      
    static void construct(PyObject* obj, rvalue_from_python_stage1_data* data)
    {
        void* storage = ((rvalue_from_python_storage<Target>*)data)->storage.bytes;

        arg_from_python<Source> get_source(obj);
        bool convertible = get_source.convertible();
        BOOST_VERIFY(convertible);
        
        new (storage) Target(get_source());
        
        // record successful construction
        data->convertible = storage;
    }

    
    result_type operator()(PyObject* x) const
    {
        (void_result_from_python)(x);
# ifdef BOOST_NO_VOID_RETURNS
        return result_type();
# endif 
    }

  template <class T>
  inline return_rvalue_from_python<T>::return_rvalue_from_python()
      : m_data(
          const_cast<registration*>(&registered<T>::converters)
          )
  {
  }
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(long double, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(long double, ::PyFloat_FromDouble(x), &PyFloat_Type)
                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(long double, ::PyFloat_FromDouble(x), &PyFloat_Type)

  inline void
  register_shared_ptr0(...)
  {
  }

  
  template <class T>
  inline void
  register_shared_ptr0(shared_ptr<T>*)
  {
      registry::lookup_shared_ptr(type_id<shared_ptr<T> >());
  }

  
  template <class T>
  inline void
  register_shared_ptr1(T const volatile*)
  {
      detail::register_shared_ptr0((T*)0);
  }

  
  template <class T>
  inline registration const& 
  registry_lookup2(T&(*)())
  {
      detail::register_shared_ptr1((T*)0);
      return registry::lookup(type_id<T&>());
  }

inline arg_lvalue_from_python_base::arg_lvalue_from_python_base(void* result)
    : m_result(result)
{
}


inline bool arg_lvalue_from_python_base::convertible() const
{
    return m_result != 0;
}


inline void*const& arg_lvalue_from_python_base::result() const
{
    return m_result;
}

  
  template <class U>
  inline U& null_ptr_reference(U&(*)())
  {
      return null_ptr_owner<U>::value;
  }


template <class T>
inline bool pointer_cref_arg_from_python<T>::convertible() const
{
    return python::detail::void_ptr_to_reference(m_result.bytes, (T(*)())0) != 0;
}

template <class T>
inline T pointer_cref_arg_from_python<T>::operator()() const
{
    return (*(void**)m_result.bytes == Py_None)  // None ==> 0
        ? detail::null_ptr_reference((T(*)())0)
        // Otherwise, return a U*const& to the m_result storage.
        : python::detail::void_ptr_to_reference(m_result.bytes, (T(*)())0);
}


template <class T>
inline T pointer_arg_from_python<T>::operator()() const
{
    return (result() == Py_None) ? 0 : T(result());
}


template <class T>
inline T reference_arg_from_python<T>::operator()() const
{
    return python::detail::void_ptr_to_reference(result(), (T(*)())0);
}


template <class T>
inline bool arg_rvalue_from_python<T>::convertible() const
{
    return m_data.stage1.convertible != 0;
}


template <class T>
inline T
back_reference_arg_from_python<T>::operator()()
{
    return T(m_source, base::operator()());
}

    
template <class T>
inline bool object_manager_value_arg_from_python<T>::convertible() const
{
    return object_manager_traits<T>::check(m_source);
}


template <class T>
inline T object_manager_value_arg_from_python<T>::operator()() const
{
    return T(python::detail::borrowed_reference(m_source));
}


template <class Ref>
inline object_manager_ref_arg_from_python<Ref>::~object_manager_ref_arg_from_python()
{
    python::detail::destroy_referent<Ref>(this->m_result.bytes);
}

  template <class T>
  inline bool object_manager_ref_check(T const& x)
  {
      return object_manager_traits<T>::check(get_managed_object(x, tag));
  }


template <class Ref>
inline bool object_manager_ref_arg_from_python<Ref>::convertible() const
{
    return detail::object_manager_ref_check(
        python::detail::void_ptr_to_reference(this->m_result.bytes, (Ref(*)())0));
}


template <class Ref>
inline Ref object_manager_ref_arg_from_python<Ref>::operator()() const
{
    return python::detail::void_ptr_to_reference(
        this->m_result.bytes, (Ref(*)())0);
}

    template <class U>
    static void convert_function_must_take_value_or_const_reference(U(*)(T), int, T* = 0) {}

    template <class U>
    static void convert_function_must_take_value_or_const_reference(U(*)(T const&), long ...) {}

        
    static PyObject* convert(void const* x)
    {
        convert_function_must_take_value_or_const_reference(&ToPython::convert, 1L);
        
        // Yes, the const_cast below opens a hole in const-correctness,
        // but it's needed to convert auto_ptr<U> to python.
        //
        // How big a hole is it?  It allows ToPython::convert() to be
        // a function which modifies its argument. The upshot is that
        // client converters applied to const objects may invoke
        // undefined behavior. The damage, however, is limited by the
        // use of the assertion function. Thus, the only way this can
        // modify its argument is if T is an auto_ptr-like type. There
        // is still a const-correctness hole w.r.t. auto_ptr<U> const,
        // but c'est la vie.
        return ToPython::convert(*const_cast<T*>(static_cast<T const*>(x)));
    }

    static bool check(PyObject* x)
    {
        return ::PyObject_IsInstance(x, (PyObject*)pytype);
    }


    static Object* checked_downcast(PyObject* x)
    {
        return python::downcast<Object>(
            (checked_downcast_impl)(x, pytype)
            );
    }

      template <class T>
      static inline type_info execute(T*(*)() = 0)
      {
          return type_id<T>();
      }

      template <class T>
      static inline type_info execute(T* const volatile&(*)() = 0)
      {
          return type_id<T>();
      }

template <class T>
type_info pointer_type_id(T(*)() = 0)
{
    return detail::pointer_typeid_select<
          is_reference<T>::value
        >::execute((T(*)())0);
}

    static dynamic_id_t execute(void* p_)
    {
        T* p = static_cast<T*>(p_);
        return std::make_pair(dynamic_cast<void*>(p), class_id(typeid(*p)));
    }

    static dynamic_id_t execute(void* p_)
    {
        return std::make_pair(p_, python::type_id<T>());
    }

template <class T>
void register_dynamic_id(T* = 0)
{
    typedef typename dynamic_id_generator<T>::type generator;
    register_dynamic_id_aux(
        python::type_id<T>(), &generator::execute);
}

    static void* execute(void* source)
    {
        return dynamic_cast<Target*>(
            static_cast<Source*>(source));
    }

    static void* execute(void* source)
    {
        Target* result = static_cast<Source*>(source);
        return result;
    }


template <class Source, class Target>
inline void register_conversion(
    bool is_downcast = ::boost::is_base_and_derived<Source,Target>::value
    // These parameters shouldn't be used; they're an MSVC bug workaround
    , Source* = 0, Target* = 0)
{
    typedef typename cast_generator<Source,Target>::type generator;

    add_cast(
        python::type_id<Source>()
      , python::type_id<Target>()
      , &generator::execute
      , is_downcast
    );
}

    template <class Base>
    inline void operator()(Base*) const
    {
# if !BOOST_WORKAROUND(BOOST_MSVC, == 1200)
        BOOST_MPL_ASSERT_NOT((is_same<Base,Derived>));
# else
        BOOST_STATIC_ASSERT(!(is_same<Base,Derived>::value));
# endif 
        
        // Register the Base class
        register_dynamic_id<Base>();

        // Register the up-cast
        register_conversion<Derived,Base>(false);

        // Register the down-cast, if appropriate.
        this->register_downcast((Base*)0, is_polymorphic<Base>());
    }

    static inline void register_downcast(void*, mpl::false_) {}

template <class T, class Bases>
inline void register_shared_ptr_from_python_and_casts(T*, Bases)
{
    // Constructor performs registration
    python::detail::force_instantiate(converter::shared_ptr_from_python<T>());

    //
    // register all up/downcasts here.  We're using the alternate
    // interface to mpl::for_each to avoid an MSVC 6 bug.
    //
    register_dynamic_id<T>();
    mpl::for_each(register_base_of<T>(), (Bases*)0, (add_pointer<mpl::_>*)0);
}

    
    inline static void register_() // Register the runtime metadata.
    {
        class_metadata::register_aux((T*)0);
    }

    template <class T2>
    inline static void register_aux(python::wrapper<T2>*) 
    {
        typedef typename mpl::not_<is_same<T2,wrapped> >::type use_callback;
        class_metadata::register_aux2((T2*)0, use_callback());
    }


    inline static void register_aux(void*) 
    {
        typedef typename is_base_and_derived<T,wrapped>::type use_callback;
        class_metadata::register_aux2((T*)0, use_callback());
    }


    template <class T2, class Callback>
    inline static void register_aux2(T2*, Callback) 
    {
        objects::register_shared_ptr_from_python_and_casts((T2*)0, bases());
        
        class_metadata::maybe_register_callback_class((T2*)0, Callback());

        class_metadata::maybe_register_class_to_python((T2*)0, is_noncopyable());
        
        class_metadata::maybe_register_pointer_to_python(
            (T2*)0, (use_value_holder*)0, (use_back_reference*)0);
    }

    inline static void maybe_register_pointer_to_python(...) {}

    inline static void maybe_register_class_to_python(void*, mpl::true_) {}

    inline static void maybe_register_callback_class(void*, mpl::false_) {}

    caller_py_function_impl(Caller const& caller)
        : m_caller(caller)
    {}

    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }

    
    virtual unsigned min_arity() const
    {
        return m_caller.min_arity();
    }

    
    virtual python::detail::py_func_sig_info signature() const
    {
        return m_caller.signature();
    }

    signature_py_function_impl(Caller const& caller)
        : m_caller(caller)
    {}

    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }

    
    virtual unsigned min_arity() const
    {
        return mpl::size<Sig>::value - 1;
    }

    
    virtual python::detail::py_func_sig_info signature() const
    {
        python::detail::signature_element const* sig = python::detail::signature<Sig>::elements();
        python::detail::py_func_sig_info res = {sig, sig};
        return  res;
    }

    full_py_function_impl(Caller const& caller, unsigned min_arity, unsigned max_arity)
      : m_caller(caller)
      , m_min_arity(min_arity)
      , m_max_arity(max_arity > min_arity ? max_arity : min_arity)
    {}

    
    PyObject* operator()(PyObject* args, PyObject* kw)
    {
        return m_caller(args, kw);
    }

    
    virtual unsigned min_arity() const
    {
        return m_min_arity;
    }

    
    virtual unsigned max_arity() const
    {
        return m_max_arity;
    }

    
    virtual python::detail::py_func_sig_info signature() const
    {
        python::detail::signature_element const* sig = python::detail::signature<Sig>::elements();
        python::detail::py_func_sig_info res = {sig, sig};
        return  res;
    }

    template <class Caller>
    py_function(Caller const& caller)
        : m_impl(new caller_py_function_impl<Caller>(caller))
    {}


    template <class Caller, class Sig>
    py_function(Caller const& caller, Sig)
      : m_impl(new signature_py_function_impl<Caller, Sig>(caller))
    {}


    template <class Caller, class Sig>
    py_function(Caller const& caller, Sig, int min_arity, int max_arity = 0)
      : m_impl(new full_py_function_impl<Caller, Sig>(caller, min_arity, max_arity))
    {}


    py_function(py_function const& rhs)
        : m_impl(rhs.m_impl)
    {}


    PyObject* operator()(PyObject* args, PyObject* kw) const
    {
        return (*m_impl)(args, kw);
    }


    unsigned min_arity() const
    {
        return m_impl->min_arity();
    }

    
    unsigned max_arity() const
    {
        return m_impl->max_arity();
    }

    
    template <class T>
    inline void* holds_wrapped(type_info dst_t, wrapper<T>*,T* p)
    {
        return python::type_id<T>() == dst_t ? p : 0;
    }

    template <class Arg>
    static inline Holder* construct(void* storage, PyObject*, Arg& x)
    {
        return new (storage) Holder(x);
    }

    
    template <class Ptr>
    static inline PyTypeObject* get_class_object(Ptr const& x)
    {
        return get_class_object_impl(get_pointer(x));
    }

    static PyObject* convert(Src const& x)
    {
        return MakeInstance::execute(boost::ref(x));
    }

    static PyObject* convert(Src x)
    {
        return MakeInstance::execute(x);
    }

        
        result_type
        operator()(iterator_range<NextPolicies,Iterator>& self)
        {
            if (self.m_start == self.m_finish)
                stop_iteration_error();
            return *self.m_start++;
        }

  template <class Iterator, class NextPolicies>
  object demand_iterator_class(char const* name, Iterator* = 0, NextPolicies const& policies = NextPolicies())
  {
      typedef iterator_range<NextPolicies,Iterator> range_;

      // Check the registry. If one is already registered, return it.
      handle<> class_obj(
          objects::registered_class_object(python::type_id<range_>()));
        
      if (class_obj.get() != 0)
          return object(class_obj);

      typedef typename range_::next_fn next_fn;
      typedef typename next_fn::result_type result_type;
      
      return class_<range_>(name, no_init)
          .def("__iter__", identity_function())
          .def(
#if PY_VERSION_HEX >= 0x03000000
              "__next__"
#else
              "next"
#endif
            , make_function(
                next_fn()
              , policies
              , mpl::vector2<result_type,range_&>()
            ));
  }

      py_iter_(Accessor1 const& get_start, Accessor2 const& get_finish)
        : m_get_start(get_start)
        , m_get_finish(get_finish)
      {}

      iterator_range<NextPolicies,Iterator>
      operator()(back_reference<Target&> x) const
      {
          // Make sure the Python class is instantiated.
          detail::demand_iterator_class("iterator", (Iterator*)0, NextPolicies());
          
          return iterator_range<NextPolicies,Iterator>(
              x.source()
            , m_get_start(x.get())
            , m_get_finish(x.get())
          );
      }


  template <class Target, class Iterator, class NextPolicies, class Accessor1, class Accessor2>
  inline object make_iterator_function(
      Accessor1 const& get_start
    , Accessor2 const& get_finish
    , NextPolicies const& /*next_policies*/
    , Iterator const& (*)()
    , boost::type<Target>*
    , int
  )
  {
      return make_function(
          py_iter_<Target,Iterator,Accessor1,Accessor2,NextPolicies>(get_start, get_finish)
        , default_call_policies()
        , mpl::vector2<iterator_range<NextPolicies,Iterator>, back_reference<Target&> >()
      );
  }

template <class Target, class NextPolicies, class Accessor1, class Accessor2>
inline object make_iterator_function(
    Accessor1 const& get_start
  , Accessor2 const& get_finish
  , NextPolicies const& next_policies
  , boost::type<Target>* = 0
)
{
    typedef typename Accessor1::result_type iterator;
    typedef typename add_const<iterator>::type iterator_const;
    typedef typename add_reference<iterator_const>::type iterator_cref;
      
    return detail::make_iterator_function(
        get_start
      , get_finish
      , next_policies
      , (iterator_cref(*)())0
      , (boost::type<Target>*)0
      , 0
    );
}

    
    template <class T>
    inline void* holds_wrapped(type_info dst_t, wrapper<T>*,T* p)
    {
        return python::type_id<T>() == dst_t ? p : 0;
    }


template <class Pointer, class Value>
inline pointer_holder<Pointer,Value>::pointer_holder(Pointer p)
    : m_p(p)
{
}


template <class Pointer, class Value>
inline pointer_holder_back_reference<Pointer,Value>::pointer_holder_back_reference(Pointer p)
    : m_p(p)
{
}

    
    reference_to_value(reference x) : m_value(x) {}

    reference get() const { return m_value; }


template <class T>
typename reference_to_value<T>::reference
do_unforward(reference_to_value<T> const& x, int)
{
    return x.get();
}


template <class T>
T const& do_unforward(T const& x, ...)
{
    return x;
}

        
    template <class Arg>
    static inline PyObject* execute(Arg& x)
    {
        BOOST_MPL_ASSERT((mpl::or_<is_class<T>, is_union<T> >));

        PyTypeObject* type = Derived::get_class_object(x);

        if (type == 0)
            return python::detail::none();

        PyObject* raw_result = type->tp_alloc(
            type, objects::additional_instance_size<Holder>::value);
          
        if (raw_result != 0)
        {
            python::detail::decref_guard protect(raw_result);
            
            instance_t* instance = (instance_t*)raw_result;
            
            // construct the new C++ object and install the pointer
            // in the Python object.
            Derived::construct(&instance->storage, (PyObject*)instance, x)->install(raw_result);
              
            // Note the position of the internally-stored Holder,
            // for the sake of destruction
            Py_SIZE(instance) = offsetof(instance_t, storage);

            // Release ownership of the python object
            protect.cancel();
        }
        return raw_result;
    }

    template <class U>
    static inline PyTypeObject* get_class_object(U&)
    {
        return converter::registered<T>::converters.get_class_object();
    }

    
    static inline Holder* construct(void* storage, PyObject* instance, reference_wrapper<T const> x)
    {
        return new (storage) Holder(instance, x);
    }


  inline void must_be_derived_from_pickle_suite(pickle_suite const&) {}

    static inaccessible* getinitargs() { return 0; }

    static inaccessible* getstate() { return 0; }

    static inaccessible* setstate() { return 0; }

    static bool getstate_manages_dict() { return false; }


    template <class Class_, class Tgetinitargs>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      inaccessible* (* /*getstate_fn*/)(),
      inaccessible* (* /*setstate_fn*/)(),
      bool)
    {
      cl.enable_pickling_(false);
      cl.def("__getinitargs__", getinitargs_fn);
    }


    template <class Class_,
              class Rgetstate, class Tgetstate,
              class Tsetstate, class Ttuple>
    static
    void
    register_(
      Class_& cl,
      inaccessible* (* /*getinitargs_fn*/)(),
      Rgetstate (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, Ttuple),
      bool getstate_manages_dict)
    {
      cl.enable_pickling_(getstate_manages_dict);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }


    template <class Class_,
              class Tgetinitargs,
              class Rgetstate, class Tgetstate,
              class Tsetstate, class Ttuple>
    static
    void
    register_(
      Class_& cl,
      tuple (*getinitargs_fn)(Tgetinitargs),
      Rgetstate (*getstate_fn)(Tgetstate),
      void (*setstate_fn)(Tsetstate, Ttuple),
      bool getstate_manages_dict)
    {
      cl.enable_pickling_(getstate_manages_dict);
      cl.def("__getinitargs__", getinitargs_fn);
      cl.def("__getstate__", getstate_fn);
      cl.def("__setstate__", setstate_fn);
    }


    template <class Class_>
    static
    void
    register_(
      Class_&,
      ...)
    {
      typedef typename
        error_messages::missing_pickle_suite_function_or_incorrect_signature<
          Class_>::error_type error_type;
    }
