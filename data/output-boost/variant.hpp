

    template <typename T>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    internal_visit(T& operand, int) const
    {
        operand.~T();

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x0551)) || \
    BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
        operand; // suppresses warnings
#endif

        BOOST_VARIANT_AUX_RETURN_VOID;
    }


    T& execute(T& operand, mpl::true_) const
    {
        return operand;
    }


    template <typename U>
    T& operator()(U& operand) const
    {
        typedef typename is_same< U,T >::type
            U_is_T;

        return execute(operand, U_is_T());
    }


    template<class RhsT>
    backup_assigner(Variant& lhs, int rhs_which, const RhsT& rhs_content)
        : lhs_(lhs)
        , rhs_which_(rhs_which)
        , rhs_content_(&rhs_content)
        , copy_rhs_content_(&construct_impl<RhsT>)
    {
    }


    template<class RhsT>
    static void construct_impl(void* addr, const void* obj)
    {
        new(addr) RhsT(*static_cast<const RhsT*>(obj));
    }


    template <typename LhsT>
    void backup_assign_impl(
          LhsT& lhs_content
        , mpl::true_ // is_nothrow_move_constructible
        )
    {
        // Move lhs content to backup...
        LhsT backup_lhs_content(
              ::boost::detail::variant::move(lhs_content)
            ); // nothrow

        // ...destroy lhs content...
        lhs_content.~LhsT(); // nothrow

        try
        {
            // ...and attempt to copy rhs content into lhs storage:
            copy_rhs_content_(lhs_.storage_.address(), rhs_content_);
        }
        catch (...)
        {
            // In case of failure, restore backup content to lhs storage...
            new(lhs_.storage_.address())
                LhsT(
                      ::boost::detail::variant::move(backup_lhs_content)
                    ); // nothrow

            // ...and rethrow:
            throw;
        }

        // In case of success, indicate new content type:
        lhs_.indicate_which(rhs_which_); // nothrow
    }


    template <typename LhsT>
        BOOST_VARIANT_AUX_RETURN_VOID_TYPE
    internal_visit(LhsT& lhs_content, int)
    {
        typedef typename is_nothrow_move_constructible<LhsT>::type
            nothrow_move;

        backup_assign_impl( lhs_content, nothrow_move() );

        BOOST_VARIANT_AUX_RETURN_VOID;
    }


    explicit swap_with(Variant& toswap)
        : toswap_(toswap)
    {
    }


    template <typename T>
    void operator()(T& operand) const
    {
        // Since the precondition ensures types are same, get T...
        known_get<T> getter;
        T& other = toswap_.apply_visitor(getter);

        // ...and swap:
        ::boost::detail::variant::move_swap( operand, other );
    }

    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs == rhs;
    }

    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }


    void destroy_content()
    {
        detail::variant::destroyer visitor;
        this->internal_apply_visitor(visitor);
    }


    ~variant()
    {
        destroy_content();
    }


    variant()
    {
        // NOTE TO USER :
        // Compile error from here indicates that the first bound
        // type is not default-constructible, and so variant cannot
        // support its own default-construction.
        //
        new( storage_.address() ) internal_T0();
        indicate_which(0); // zero is the index of the first bounded type
    }


    template <typename T>
    void convert_construct(
          T& operand
        , int
        , mpl::false_ = mpl::false_() // is_foreign_variant
        )
    {
        // NOTE TO USER :
        // Compile error here indicates that the given type is not 
        // unambiguously convertible to one of the variant's types
        // (or that no conversion exists).
        //
        indicate_which(
              initializer::initialize(
                  storage_.address()
                , operand
                )
            );
    }


    void variant_assign(const variant& rhs)
    {
        // If the contained types are EXACTLY the same...
        if (which_ == rhs.which_)
        {
            // ...then assign rhs's storage to lhs's content:
            detail::variant::assign_storage visitor(rhs.storage_.address());
            this->internal_apply_visitor(visitor);
        }
        else
        {
            // Otherwise, perform general (copy-based) variant assignment:
            assigner visitor(*this, rhs.which());
            rhs.internal_apply_visitor(visitor); 
        }
    }

    void variant_assign(variant&& rhs)
    {
        // If the contained types are EXACTLY the same...
        if (which_ == rhs.which_)
        {
            // ...then move rhs's storage to lhs's content:
            detail::variant::move_storage visitor(rhs.storage_.address());
            this->internal_apply_visitor(visitor);
        }
        else
        {
            // Otherwise, perform general (move-based) variant assignment:
            move_assigner visitor(*this, rhs.which());
            rhs.internal_apply_visitor(visitor); 
        }
    }


    template <typename T>
    void assign(const T& rhs)
    {
        // If direct T-to-T assignment is not possible...
        detail::variant::direct_assigner<T> direct_assign(rhs);
        if (this->apply_visitor(direct_assign) == false)
        {
            // ...then convert rhs to variant and assign:
            //
            // While potentially inefficient, the following construction of a
            // variant allows T as any type convertible to one of the bounded
            // types without excessive code redundancy.
            //
            variant temp(rhs);
            variant_assign( detail::variant::move(temp) );
        }
    }

    template <typename T>
    void move_assign(T&& rhs)
    {
        // If direct T-to-T move assignment is not possible...
        detail::variant::direct_mover<T> direct_move(rhs);
        if (this->apply_visitor(direct_move) == false)
        {
            // ...then convert rhs to variant and assign:
            //
            // While potentially inefficient, the following construction of a
            // variant allows T as any type convertible to one of the bounded
            // types without excessive code redundancy.
            //
            variant temp( detail::variant::move(rhs) );
            variant_assign( detail::variant::move(temp) );
        }
    }

template < BOOST_VARIANT_ENUM_PARAMS(typename T) >
inline void swap(
      variant< BOOST_VARIANT_ENUM_PARAMS(T) >& lhs
    , variant< BOOST_VARIANT_ENUM_PARAMS(T) >& rhs
    )
{
    lhs.swap(rhs);
}


    explicit visitor_ptr_t(visitor_t visitor)
      : visitor_(visitor)
    {
    }


    template <typename U>
    result_type operator()(const U&) const
    {
        throw bad_visit();
    }


template <typename R, typename T>
inline visitor_ptr_t<T,R> visitor_ptr(R (*visitor)(T))
{
    return visitor_ptr_t<T,R>(visitor);
}


    virtual const char * what() const throw()
    {
        return "boost::bad_visit: "
               "failed visitation using boost::apply_visitor";
    }


    recursive_wrapper& operator=(const recursive_wrapper& rhs)
    {
        assign( rhs.get() );
        return *this;
    }


    recursive_wrapper& operator=(const T& rhs)
    {
        assign( rhs );
        return *this;
    }


template <typename T>
recursive_wrapper<T>::~recursive_wrapper()
{
    boost::checked_delete(p_);
}


template <typename T>
recursive_wrapper<T>::recursive_wrapper()
    : p_(new T)
{
}


template <typename T>
recursive_wrapper<T>::recursive_wrapper(const recursive_wrapper& operand)
    : p_(new T( operand.get() ))
{
}


template <typename T>
recursive_wrapper<T>::recursive_wrapper(const T& operand)
    : p_(new T(operand))
{
}
 
template <typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper&& operand)
    : p_(new T( detail::variant::move(operand.get()) ))
{
}


template <typename T>
recursive_wrapper<T>::recursive_wrapper(T&& operand)
    : p_(new T( detail::variant::move(operand) ))
{
}


template <typename T>
void recursive_wrapper<T>::assign(const T& rhs)
{
    this->get() = rhs;
}


    static_visitor() { }

    ~static_visitor() { }


    virtual const char * what() const throw()
    {
        return "boost::bad_get: "
               "failed value get using boost::get";
    }


    pointer execute_impl(reference operand, mpl::true_) const
    {
        return boost::addressof(operand);
    }


    template <typename U>
    pointer operator()(U& operand) const
    {
        // MSVC6 finds normal implementation (above) ambiguous,
        // so we must explicitly disambiguate

        typedef typename mpl::or_<
              is_same<U, T>
            , is_same<const U, T>
            >::type U_is_T;

        return execute_impl(operand, U_is_T());
    }

get(
      const boost::variant< BOOST_VARIANT_ENUM_PARAMS(T) >* operand
      BOOST_VARIANT_AUX_GET_EXPLICIT_TEMPLATE_TYPE(U)
    )
{
    typedef typename add_pointer<const U>::type U_ptr;
    if (!operand) return static_cast<U_ptr>(0);

    detail::variant::get_visitor<const U> v;
    return operand->apply_visitor(v);
}

visitation_impl_invoke_impl(
      int, Visitor& visitor, VoidPtrCV storage, T*
    , mpl::true_// never_uses_backup
    )
{
    return visitor.internal_visit(
          cast_storage<T>(storage), 1L
        );
}

visitation_impl_invoke(
      int internal_which, Visitor& visitor, VoidPtrCV storage, T* t
    , NoBackupFlag
    , int
    )
{
    typedef typename mpl::or_<
          NoBackupFlag
        , is_nothrow_move_constructible<T>
        , has_nothrow_copy<T>
        >::type never_uses_backup;

    return (visitation_impl_invoke_impl)(
          internal_which, visitor, storage, t
        , never_uses_backup()
        );
}

visitation_impl(
      int, int, Visitor&, VPCV
    , mpl::true_ // is_apply_visitor_unrolled
    , NBF, W* = 0, S* = 0
    )
{
    // should never be here at runtime:
    BOOST_ASSERT(false);
    typedef typename Visitor::result_type result_type;
    return ::boost::detail::variant::forced_return< result_type >();
}


template <typename T>
inline T& cast_storage(
      void* storage
      BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(T)
    )
{
    return *static_cast<T*>(storage);
}


template <typename T>
inline const T& cast_storage(
      const void* storage
      BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(T)
    )
{
    return *static_cast<const T*>(storage);
}


template <typename T>
inline void swap(T& lhs, T& rhs)
{
    T tmp( boost::detail::variant::move(lhs) );
    lhs = boost::detail::variant::move(rhs);
    rhs = boost::detail::variant::move(tmp);
}


template <typename T>
inline void move_swap(T& lhs, T& rhs)
{
    using detail::move_swap::swap;

    swap(lhs, rhs);
}


    explicit apply_visitor_delayed_t(Visitor& visitor)
      : visitor_(visitor)
    {
    }


template <typename Visitor>
inline apply_visitor_delayed_t<Visitor> apply_visitor(Visitor& visitor)
{
    return apply_visitor_delayed_t<Visitor>(visitor);
}


    explicit printer(OStream& out)
        : out_( out )
    {
    }


    template <typename T>
    void operator()(const T& operand) const
    {
        out_ << operand;
    }

            template <class T>
            std::size_t operator()(T const& val) const {
                boost::hash<T> hasher;
                return hasher(val);
            }


    ~backup_holder()
    {
        delete backup_;
    }


    backup_holder& operator=(const backup_holder& rhs)
    {
        *backup_ = rhs.get();
        return *this;
    }


    backup_holder& operator=(const T& rhs)
    {
        *backup_ = rhs;
        return *this;
    }


template <typename T>
backup_holder<T>::backup_holder(const backup_holder&)
    : backup_(0)
{
    // not intended for copy, but do not want to prohibit syntactically
    BOOST_ASSERT(false);
}


    apply_visitor_binary_invoke(Visitor& visitor, Value1& value1)
        : visitor_(visitor)
        , value1_(value1)
    {
    }


    apply_visitor_binary_unwrap(Visitor& visitor, Visitable2& visitable2)
        : visitor_(visitor)
        , visitable2_(visitable2)
    {
    }
