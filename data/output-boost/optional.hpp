
  template <class T, class Factory>
  inline void construct(Factory const& factory, void* address)
  {
    factory.BOOST_NESTED_TEMPLATE apply<T>(address);
  }

    void const* address() const { return &dummy_; }

    void      * address()       { return &dummy_; }

    optional_base()
      :
      m_initialized(false) {}

    optional_base ( optional_base const& rhs )
      :
      m_initialized(false)
    {
      if ( rhs.is_initialized() )
        construct(rhs.get_impl());
    }

    template<class Expr>
    explicit optional_base ( Expr const& expr, Expr const* tag )
      :
      m_initialized(false)
    {
      construct(expr,tag);
    }

    ~optional_base() { destroy() ; }

    void assign ( optional_base const& rhs )
    {
      if (is_initialized())
      {
        if ( rhs.is_initialized() )
             assign_value(rhs.get_impl(), is_reference_predicate() );
        else destroy();
      }
      else
      {
        if ( rhs.is_initialized() )
          construct(rhs.get_impl());
      }
    }

    template<class Expr>
    void assign_expr ( Expr const& expr, Expr const* tag )
      {
        if (is_initialized())
             assign_expr_to_initialized(expr,tag);
        else construct(expr,tag);
      }

    void reset() { destroy(); }

    pointer_const_type get_ptr() const { return m_initialized ? get_ptr_impl() : 0 ; }


    bool is_initialized() const { return m_initialized ; }


    void construct ( argument_type val )
     {
       new (m_storage.address()) internal_type(val) ;
       m_initialized = true ;
     }

    template<class Expr>
    void construct ( Expr const& factory, in_place_factory_base const* )
     {
       BOOST_STATIC_ASSERT ( ::boost::mpl::not_<is_reference_predicate>::value ) ;
       boost_optional_detail::construct<value_type>(factory, m_storage.address());
       m_initialized = true ;
     }

    template<class Expr>
    void construct ( Expr const& factory, typed_in_place_factory_base const* )
     {
       BOOST_STATIC_ASSERT ( ::boost::mpl::not_<is_reference_predicate>::value ) ;
       factory.apply(m_storage.address()) ;
       m_initialized = true ;
     }


    template<class Expr>
    void assign_expr_to_initialized ( Expr const& factory, in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }

    template<class Expr>
    void assign_expr_to_initialized ( Expr const& factory, typed_in_place_factory_base const* tag )
     {
       destroy();
       construct(factory,tag);
     }

    template<class Expr>
    void construct ( Expr const& expr, void const* )
     {
       new (m_storage.address()) internal_type(expr) ;
       m_initialized = true ;
     }

    template<class Expr>
    void assign_expr_to_initialized ( Expr const& expr, void const* )
     {
       assign_value(expr, is_reference_predicate());
     }


    void assign_value ( argument_type val, is_not_reference_tag ) { get_impl() = val; }


    void destroy()
    {
      if ( m_initialized )
        destroy_impl(is_reference_predicate()) ;
    }


    unspecified_bool_type safe_bool() const { return m_initialized ? &this_type::is_initialized : 0 ; }


    reference_const_type get_impl() const { return dereference(get_object(), is_reference_predicate() ) ; }


    pointer_const_type get_ptr_impl() const { return cast_ptr(get_object(), is_reference_predicate() ) ; }

    optional() : base() {}

    template<class U>
    explicit optional ( optional<U> const& rhs )
      :
      base()
    {
      if ( rhs.is_initialized() )
        this->construct(rhs.get());
    }

    template<class Expr>
    explicit optional ( Expr const& expr ) : base(expr,boost::addressof(expr)) {}

    optional ( optional const& rhs ) : base( static_cast<base const&>(rhs) ) {}

    ~optional() {}

    template<class Expr>
    optional& operator= ( Expr const& expr )
      {
        this->assign_expr(expr,boost::addressof(expr));
        return *this ;
      }

    template<class U>
    optional& operator= ( optional<U> const& rhs )
      {
        this->assign(rhs);
        return *this ;
      }

    optional& operator= ( optional const& rhs )
      {
        this->assign( static_cast<base const&>(rhs) ) ;
        return *this ;
      }


    void swap( optional & arg )
      {
        // allow for Koenig lookup
        using boost::swap;
        swap(*this, arg);
      }

    reference_const_type get() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_impl(); }

    reference_const_type get_value_or ( reference_const_type v ) const { return this->is_initialized() ? get() : v ; }

    pointer_const_type operator->() const { BOOST_ASSERT(this->is_initialized()) ; return this->get_ptr_impl() ; }

    reference_const_type operator *() const { return this->get() ; }

template<class T>
inline
optional<T> make_optional ( T const& v  )
{
  return optional<T>(v);
}

template<class T>
inline
optional<T> make_optional ( bool cond, T const& v )
{
  return optional<T>(cond,v);
}
