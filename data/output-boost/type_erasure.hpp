

template<class T>
T make(T*) { return T(); }


template<class T>
fallback make_fallback(const T&, boost::mpl::false_)
{
    return fallback();
}

    any(const ::boost::type_erasure::detail::storage& data_arg, const table_type& table_arg)
      : table(table_arg),
        data(data_arg)
    {}

    any()
    {
        BOOST_MPL_ASSERT((::boost::type_erasure::is_relaxed<Concept>));
        data.data = 0;
    }

    template<class U>
    any(U&& data_arg)
      : table((
            BOOST_TYPE_ERASURE_INSTANTIATE1(Concept, T, typename ::boost::remove_cv<typename ::boost::remove_reference<U>::type>::type),
            ::boost::type_erasure::make_binding<
                ::boost::mpl::map< ::boost::mpl::pair<T, typename ::boost::remove_cv<typename ::boost::remove_reference<U>::type>::type> >
            >()
        )),
        data(std::forward<U>(data_arg))
    {}

    template<class U>
    any(U* data_arg)
      : table((
            BOOST_TYPE_ERASURE_INSTANTIATE1(Concept, T, U*),
            ::boost::type_erasure::make_binding<
                ::boost::mpl::map< ::boost::mpl::pair<T, U*> >
            >()
        )),
        data(data_arg)
    {}

    any(const any& other)
      : table(other.table),
        data(::boost::type_erasure::call(constructible<T(const T&)>(), other))
    {}

    template<class Concept2, class Tag2>
    any(const any<Concept2, Tag2>& other)
      : table(
            ::boost::type_erasure::detail::access::table(other),
            ::boost::mpl::map<
                ::boost::mpl::pair<
                    T,
                    typename ::boost::remove_const<
                        typename ::boost::remove_reference<Tag2>::type
                    >::type
                >
            >()
        ),
        data(::boost::type_erasure::call(
            constructible<
                typename ::boost::remove_const<
                    typename boost::remove_reference<Tag2>::type
                >::type(const typename boost::remove_reference<Tag2>::type&)
            >(), other)
        )
    {}

    any(any&& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(std::move(other)) : 0
            ), std::move(other))
        )
    {}

    any(any& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    template<class Concept2, class Tag2>
    any(any<Concept2, Tag2>& other)
      : table(
            ::boost::type_erasure::detail::access::table(other),
            ::boost::mpl::map<
                ::boost::mpl::pair<
                    T,
                    typename ::boost::remove_const<
                        typename ::boost::remove_reference<Tag2>::type
                    >::type
                >
            >()
        ),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? other._boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    template<class Concept2, class Tag2>
    any(any<Concept2, Tag2>&& other)
      : table(
            ::boost::type_erasure::detail::access::table(other),
            ::boost::mpl::map<
                ::boost::mpl::pair<
                    T,
                    typename ::boost::remove_const<
                        typename ::boost::remove_reference<Tag2>::type
                    >::type
                >
            >()
        ),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? other._boost_type_erasure_deduce_constructor(std::move(other)) : 0
            ), std::move(other))
        )
    {}

    any(const any<Concept, T&>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    any(any<Concept, T&>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    any(any<Concept, T&>&& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    any(const any<Concept, const T&>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    any(any<Concept, const T&>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    any(any<Concept, const T&>&& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    template<class Tag2>
    explicit any(const any<Concept, Tag2>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    template<class Tag2>
    explicit any(any<Concept, Tag2>& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(other) : 0
            ), other)
        )
    {}

    template<class Tag2>
    explicit any(any<Concept, Tag2>&& other)
      : table(::boost::type_erasure::detail::access::table(other)),
        data(::boost::type_erasure::call(
            ::boost::type_erasure::detail::make(
                false? this->_boost_type_erasure_deduce_constructor(std::move(other)) : 0
            ), std::move(other))
        )
    {}


    template<class R, class... A, class... U>
    const table_type& _boost_type_erasure_extract_table(
        ::boost::type_erasure::constructible<R(A...)>*,
        U&&... u)
    {
        return *::boost::type_erasure::detail::extract_table(static_cast<void(*)(A...)>(0), u...);
    }


    template<class U0, class U1, class... U>
    any(U0&& u0, U1&& u1, U&&... u)
      : table(
            _boost_type_erasure_extract_table(
                false? this->_boost_type_erasure_deduce_constructor(std::forward<U0>(u0), std::forward<U1>(u1), std::forward<U>(u)...) : 0,
                std::forward<U0>(u0), std::forward<U1>(u1), std::forward<U>(u)...
            )
        ),
        data(
            ::boost::type_erasure::call(
                ::boost::type_erasure::detail::make(
                    false? this->_boost_type_erasure_deduce_constructor(std::forward<U0>(u0), std::forward<U1>(u1), std::forward<U>(u)...) : 0
                ),
                std::forward<U0>(u0), std::forward<U1>(u1), std::forward<U>(u)...
            )
        )
    {}

    any& operator=(const any& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    template<class U>
    any& operator=(const U& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    ~any()
    {
        table.template find<destructible<T> >()(data);
    }

    any(const ::boost::type_erasure::detail::storage& data_arg,
        const table_type& table_arg)
      : data(data_arg),
        table(table_arg)
    {}

    any(const any& other)
      : data(other.data),
        table(other.table)
    {}

    any(any& other)
      : data(other.data),
        table(other.table)
    {}

    any(any<Concept, T>& other)
      : data(::boost::type_erasure::detail::access::data(other)),
        table(::boost::type_erasure::detail::access::table(other))
    {}

    any& operator=(const any& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    template<class U>
    any& operator=(U& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    template<class U>
    any& operator=(const U& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    any(const ::boost::type_erasure::detail::storage& data_arg,
        const table_type& table_arg)
      : data(data_arg),
        table(table_arg)
    {}

    template<class U>
    any(const U& arg)
      : table((
            BOOST_TYPE_ERASURE_INSTANTIATE1(Concept, T, U),
            ::boost::type_erasure::make_binding<
                ::boost::mpl::map< ::boost::mpl::pair<T, U> >
            >()
        ))
    {
        data.data = const_cast<void*>(static_cast<const void*>(::boost::addressof(arg)));
    }

    any(const any& other)
      : data(other.data),
        table(other.table)
    {}

    any(const any<Concept, T&>& other)
      : data(::boost::type_erasure::detail::access::data(other)),
        table(::boost::type_erasure::detail::access::table(other))
    {}

    any(const any<Concept, T>& other)
      : data(::boost::type_erasure::detail::access::data(other)),
        table(::boost::type_erasure::detail::access::table(other))
    {}

    any(const any<Concept, T&&>& other)
      : data(::boost::type_erasure::detail::access::data(other)),
        table(::boost::type_erasure::detail::access::table(other))
    {}

    any& operator=(const any& other)
    {
        BOOST_MPL_ASSERT((::boost::type_erasure::is_relaxed<Concept>));
        any temp(other);
        _boost_type_erasure_swap(temp);
        return *this;
    }

    template<class U>
    any& operator=(const U& other)
    {
        BOOST_MPL_ASSERT((::boost::type_erasure::is_relaxed<Concept>));
        any temp(other);
        _boost_type_erasure_swap(temp);
        return *this;
    }

    any(const ::boost::type_erasure::detail::storage& data_arg,
        const table_type& table_arg)
      : data(data_arg),
        table(table_arg)
    {}

    any(any&& other)
      : data(other.data),
        table(std::move(other.table))
    {}

    any(const any& other)
      : data(other.data),
        table(other.table)
    {}

    any(any<Concept, T>&& other)
      : data(::boost::type_erasure::detail::access::data(other)),
        table(std::move(::boost::type_erasure::detail::access::table(other)))
    {}

    any& operator=(const any& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    template<class U>
    any& operator=(U& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }

    template<class U>
    any& operator=(const U& other)
    {
        _boost_type_erasure_resolve_assign(other);
        return *this;
    }


template<class T, class Concept, class Tag>
bool check_any_cast(const any<Concept, Tag>&, ::boost::mpl::true_)
{
    return true;
}

template<class Concept, class T>
const std::type_info& typeid_of(const any<Concept, T>& arg)
{
    return ::boost::type_erasure::detail::access::table(arg).template find<
        ::boost::type_erasure::typeid_<
            typename ::boost::remove_cv<
                typename ::boost::remove_reference<T>::type
            >::type
        >
    >()();
}

    static void value(detail::storage& arg)
    {
        delete static_cast<T*>(arg.data);
    }

    static void apply(detail::storage& arg)
    { 
        delete static_cast<T*>(arg.data);
    }

    static void apply(T& dst, const U& src) { dst = src; }

    static const std::type_info& value()
    {
        return typeid(T);
    }

    static const std::type_info& apply()
    {
        return typeid(T);
    }

    static void value(::boost::type_erasure::detail::storage&) {}

    template<class Binding>
    cons(const Binding&) {}

    template<class Binding, class U0, class... U>
    cons(const Binding& b, U0&& u0, U&&... u)
      : value(std::forward<U0>(u0), b),
        rest(b, std::forward<U>(u)...)
    {}

    static const type& call(const Cons& c)
    {
        return cons_advance<N-1, Cons>::call(c).rest;
    }

    static const type& call(const Cons& c)
    {
        return c;
    }

    explicit tuple_iterator(Tuple& t_arg) : t(&t_arg) {}

        static type call(It it)
        {
            return Tuple::template at<Tuple, mpl::int_<N> >::call(*it.t);
        }

        static type call(It it) { return type(*it.t); }

        static type call(It1, It2) { return type(); }

    template<class... U>
    explicit tuple(U&&... args)
      : impl(
            ::boost::type_erasure::make_binding<
                typename ::boost::type_erasure::detail::make_map<
                    ::boost::mpl::pair<
                        typename ::boost::remove_const<
                            typename ::boost::remove_reference<T>::type
                        >::type,
                        typename ::boost::remove_const<
                            typename ::boost::remove_reference<U>::type
                        >::type
                    >...
                >::type
            >(),
            std::forward<U>(args)...)
    {}

        static type call(Seq& seq) { return type(seq); }

        static type call(Seq& seq) { return type(seq); }

        static type call(Seq& seq) { return type(); }

        static type call(Seq& seq) { return type(); }

        static type call(Seq& seq)
        {
            return const_cast<type>(
                ::boost::type_erasure::detail::cons_advance<
                    N::value,
                    ::boost::type_erasure::cons<Concept, T...>
                >::call(seq.impl).value
            );
        }


template<int N, class Concept, class... T>
typename ::boost::type_erasure::detail::cons_advance<
    N,
    ::boost::type_erasure::cons<Concept, T...>
>::type::value_type& get(::boost::type_erasure::tuple<Concept, T...>& t)
{
    return const_cast<
        typename ::boost::type_erasure::detail::cons_advance<
            N,
            ::boost::type_erasure::cons<Concept, T...>
        >::type::value_type&
    >(
        ::boost::type_erasure::detail::cons_advance<N,
            ::boost::type_erasure::cons<Concept, T...>
        >::call(t.impl).value
    );
}


template<int N, class Concept, class... T>
const typename ::boost::type_erasure::detail::cons_advance<
    N,
    ::boost::type_erasure::cons<Concept, T...>
>::type::value_type& get(const ::boost::type_erasure::tuple<Concept, T...>& t)
{
    return ::boost::type_erasure::detail::cons_advance<
        N,
        ::boost::type_erasure::cons<Concept, T...>
    >::call(t.impl).value;
}

    static ::boost::type_erasure::detail::storage
    apply(T... arg)
    {
        ::boost::type_erasure::detail::storage result;
        result.data = new R(::std::forward<T>(arg)...);
        return result;
    }

    static ::boost::type_erasure::detail::storage
    value(T...)
    {
        ::boost::type_erasure::detail::storage result;
        result.data = 0;
        return result;
    }


template<class T, class Table>
int maybe_get_table(const T& arg, const Table*& table, boost::mpl::true_)
{
    if(table == 0) {
        table = &::boost::type_erasure::detail::access::table(arg);
    }
    return 0;
}


template<class... T>
void ignore(const T&...) {}

    template<class F>
    static R apply(const ::boost::type_erasure::binding<Concept>* table, U... arg)
    {
        return table->template find<F>()(
            ::boost::type_erasure::detail::convert_arg(
                ::std::forward<U>(arg),
                ::boost::type_erasure::detail::is_placeholder_arg<T>())...);
    }

    template<class F>
    static type apply(const ::boost::type_erasure::binding<Concept>* table, U... arg)
    {
        return type(table->template find<F>()(
            ::boost::type_erasure::detail::convert_arg(
                ::std::forward<U>(arg),
                ::boost::type_erasure::detail::is_placeholder_arg<T>())...), *table);
    }


template<
    class Concept,
    class Op,
    class... U
>
typename ::boost::type_erasure::detail::call_result<
    Op,
    void(U&&...),
    Concept
>::type
unchecked_call(
    const ::boost::type_erasure::binding<Concept>& table,
    const Op&,
    U&&... arg)
{
    return ::boost::type_erasure::detail::call_impl<
        typename ::boost::type_erasure::detail::get_signature<Op>::type,
        void(U&&...),
        Concept
    >::template apply<
        typename ::boost::type_erasure::detail::adapt_to_vtable<Op>::type
    >(&table, std::forward<U>(arg)...);
}


template<class Concept, class Op, class... U>
typename ::boost::type_erasure::detail::call_result<
    Op,
    void(U&&...),
    Concept
>::type
call(
    const ::boost::type_erasure::binding<Concept>& table,
    const Op& f,
    U&&... arg)
{
    ::boost::type_erasure::require_match(table, f, std::forward<U>(arg)...);
    return ::boost::type_erasure::unchecked_call(table, f, std::forward<U>(arg)...);
}

    static R apply(F& f, T... arg)
    {
        return f(std::forward<T>(arg)...);
    }

    static void apply(F& f, T... arg)
    {
        f(std::forward<T>(arg)...);
    }

template<class T>
bool is_empty(const T& arg) {
    return ::boost::type_erasure::detail::access::data(arg).data == 0;
}
                                                                               \
        static void apply(T& arg) { op arg; }                                       \
    };                                                                              \
                                                                                    \
    template<class T, class Base>                                                   \
    struct concept_interface<name<T>, Base, T,                                      \
        typename ::boost::enable_if<                                                \
            detail::should_be_non_const<T, Base>                                    \
        >::type                                                                     \
    > : Base                                                                        \
    {                                                                               \
        typedef typename ::boost::type_erasure::derived<Base>::type _derived;       \
        _derived& operator op()                                                     \
        {                                                                           \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return static_cast<_derived&>(*this);                                   \
        }                                                                           \
        typename ::boost::type_erasure::rebind_any<Base, T>::type operator op(int)  \
        {                                                                           \
            typename ::boost::type_erasure::rebind_any<Base, T>::type result(       \
                static_cast<_derived&>(*this));                                     \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return result;                                                          \
        }                                                                           \
    };                                                                              \
                                                                                    \
    template<class T, class Base>                                                   \
    struct concept_interface<name<T>, Base, T,                                      \
        typename ::boost::enable_if<                                                \
            detail::should_be_const<T, Base>                                        \
        >::type                                                                     \
    > : Base                                                                        \
    {                                                                               \
        typedef typename ::boost::type_erasure::derived<Base>::type _derived;       \
        const _derived& operator op() const                                         \
        {                                                                           \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return static_cast<const _derived&>(*this);                             \
        }                                                                           \
        typename ::boost::type_erasure::rebind_any<Base, T>::type operator op(int) const \
        {                                                                           \
            typename ::boost::type_erasure::rebind_any<Base, T>::type result(       \
                static_cast<const _derived&>(*this));                               \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return result;                                                          \
        }                                                                           \
    };

/**
 * The @ref incrementable concept allow pre and
 * post increment on an @ref any.  The contained
 * type must provide a pre-increment operator.
 */
BOOST_TYPE_ERASURE_UNARY_INPLACE_OPERATOR(incrementable, ++)
                                                                               \
        static void apply(T& arg) { op arg; }                                       \
    };                                                                              \
                                                                                    \
    template<class T, class Base>                                                   \
    struct concept_interface<name<T>, Base, T,                                      \
        typename ::boost::enable_if<                                                \
            detail::should_be_non_const<T, Base>                                    \
        >::type                                                                     \
    > : Base                                                                        \
    {                                                                               \
        typedef typename ::boost::type_erasure::derived<Base>::type _derived;       \
        _derived& operator op()                                                     \
        {                                                                           \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return static_cast<_derived&>(*this);                                   \
        }                                                                           \
        typename ::boost::type_erasure::rebind_any<Base, T>::type operator op(int)  \
        {                                                                           \
            typename ::boost::type_erasure::rebind_any<Base, T>::type result(       \
                static_cast<_derived&>(*this));                                     \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return result;                                                          \
        }                                                                           \
    };                                                                              \
                                                                                    \
    template<class T, class Base>                                                   \
    struct concept_interface<name<T>, Base, T,                                      \
        typename ::boost::enable_if<                                                \
            detail::should_be_const<T, Base>                                        \
        >::type                                                                     \
    > : Base                                                                        \
    {                                                                               \
        typedef typename ::boost::type_erasure::derived<Base>::type _derived;       \
        const _derived& operator op() const                                         \
        {                                                                           \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return static_cast<const _derived&>(*this);                             \
        }                                                                           \
        typename ::boost::type_erasure::rebind_any<Base, T>::type operator op(int) const \
        {                                                                           \
            typename ::boost::type_erasure::rebind_any<Base, T>::type result(       \
                static_cast<const _derived&>(*this));                               \
            ::boost::type_erasure::call(name<T>(), *this);                          \
            return result;                                                          \
        }                                                                           \
    };

/**
 * The @ref incrementable concept allow pre and
 * post increment on an @ref any.  The contained
 * type must provide a pre-increment operator.
 */
BOOST_TYPE_ERASURE_UNARY_INPLACE_OPERATOR(incrementable, ++)
/**
 * The @ref decrementable concept allow pre and
 * post decrement on an @ref any.  The contained
 * type must provide a pre-decrement operator.
 */
BOOST_TYPE_ERASURE_UNARY_INPLACE_OPERATOR(decrementable, --)
                                                                                   \
        static R apply(const T& arg) { return op arg; }                                 \
    };                                                                                  \
                                                                                        \
    template<class T, class R, class Base>                                              \
    struct concept_interface<name<T, R>, Base, T> : Base                                \
    {                                                                                   \
        typename ::boost::type_erasure::rebind_any<Base, R>::type operator op() const   \
        {                                                                               \
            return ::boost::type_erasure::call(name<T, R>(), *this);                    \
        }                                                                               \
    };

/**
 * The @ref complementable concept allow use of the bitwise
 * complement operator on an @ref any.
 */
BOOST_TYPE_ERASURE_UNARY_OPERATOR(complementable, ~)
                                                                                   \
        static R apply(const T& arg) { return op arg; }                                 \
    };                                                                                  \
                                                                                        \
    template<class T, class R, class Base>                                              \
    struct concept_interface<name<T, R>, Base, T> : Base                                \
    {                                                                                   \
        typename ::boost::type_erasure::rebind_any<Base, R>::type operator op() const   \
        {                                                                               \
            return ::boost::type_erasure::call(name<T, R>(), *this);                    \
        }                                                                               \
    };

/**
 * The @ref complementable concept allow use of the bitwise
 * complement operator on an @ref any.
 */
BOOST_TYPE_ERASURE_UNARY_OPERATOR(complementable, ~)
/**
 * The @ref negatable concept allow use of the unary
 * minus operator on an @ref any.
 */
BOOST_TYPE_ERASURE_UNARY_OPERATOR(negatable, -)

    static R apply(const T& arg) { return *arg; }
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(left_shiftable, <<)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(left_shiftable, <<)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(right_shiftable, >>)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(left_shiftable, <<)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(right_shiftable, >>)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitandable, &)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(left_shiftable, <<)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(right_shiftable, >>)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitandable, &)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitorable, |)
                                                                       \
        static R apply(const T& lhs, const U& rhs) { return lhs op rhs; }   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<name<T, U, R>, Base, T> : Base                 \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const typename derived<Base>::type& lhs,                \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class R, class Base>                         \
    struct concept_interface<                                               \
        name<T, U, R>,                                                      \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend typename rebind_any<Base, R>::type                           \
        operator op(const T& lhs,                                           \
                    const typename derived<Base>::type& rhs)                \
        {                                                                   \
            return ::boost::type_erasure::call(name<T, U, R>(), lhs, rhs);  \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_BINARY_OPERATOR(addable, +)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(subtractable, -)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(multipliable, *)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(dividable, /)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(modable, %)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(left_shiftable, <<)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(right_shiftable, >>)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitandable, &)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitorable, |)
BOOST_TYPE_ERASURE_BINARY_OPERATOR(bitxorable, ^)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(left_shift_assignable, <<=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(left_shift_assignable, <<=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(right_shift_assignable, >>=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(left_shift_assignable, <<=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(right_shift_assignable, >>=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitand_assignable, &=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(left_shift_assignable, <<=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(right_shift_assignable, >>=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitand_assignable, &=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitor_assignable, |=)
                                                                       \
        static void apply(T& lhs, const U& rhs) { lhs op rhs; }             \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<name<T, U>, Base, T,                           \
        typename ::boost::disable_if<                                       \
            ::boost::is_same<                                               \
                typename ::boost::type_erasure::placeholder_of<Base>::type, \
                const T&                                                    \
            >                                                               \
        >::type                                                             \
    > : Base                                                                \
    {                                                                       \
        friend typename detail::non_const_this_param<Base>::type&           \
        operator op(typename detail::non_const_this_param<Base>::type& lhs, \
                    typename as_param<Base, const U&>::type rhs)            \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<class T, class U, class Base>                                  \
    struct concept_interface<                                               \
        name<T, U>,                                                         \
        Base,                                                               \
        U,                                                                  \
        typename ::boost::disable_if<                                       \
            ::boost::type_erasure::is_placeholder<T> >::type                \
    > : Base                                                                \
    {                                                                       \
        friend T&                                                           \
        operator op(T& lhs, const typename derived<Base>::type& rhs)        \
        {                                                                   \
            ::boost::type_erasure::call(name<T, U>(),lhs, rhs);             \
            return lhs;                                                     \
        }                                                                   \
    };

BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(add_assignable, +=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(subtract_assignable, -=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(multiply_assignable, *=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(divide_assignable, /=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(mod_assignable, %=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(left_shift_assignable, <<=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(right_shift_assignable, >>=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitand_assignable, &=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitor_assignable, |=)
BOOST_TYPE_ERASURE_ASSIGNMENT_OPERATOR(bitxor_assignable, ^=)

    static bool apply(const T& lhs, const U& rhs) { return lhs == rhs; }

    static bool apply(const T& lhs, const U& rhs) { return lhs < rhs; }


template<class F, class T, class U>
bool less_impl(const F& f, const T& lhs, const U& rhs, ::boost::mpl::true_)
{
    if(::boost::type_erasure::check_match(f, lhs, rhs)) {
        return ::boost::type_erasure::unchecked_call(f, lhs, rhs);
    } else {
        return ::boost::type_erasure::typeid_of(
            static_cast<const typename derived<T>::type&>(lhs)
        ).before(
            ::boost::type_erasure::typeid_of(
                static_cast<const typename derived<U>::type&>(rhs)
            )
        ) != false;
    }
}

    static R apply(T& arg, const N& index) { return arg[index]; }

    static void apply(Os& out, const T& arg) { out << arg; }

    static void apply(Is& out, T& arg) { out >> arg; }


    template<class U>
    param(any<Concept, U>& a
#ifndef BOOST_TYPE_ERASURE_DOXYGEN
        , typename boost::enable_if<
            ::boost::type_erasure::detail::placeholder_conversion<U, T>
        >::type* = 0
#endif
        )
      : _impl(a)
    {}

    any<Concept, T> get() const { return _impl; }


template<class Concept, class Op, class... U>
void require_match_impl(
    ::boost::mpl::true_,
    const ::boost::type_erasure::binding<Concept>& table,
    const Op& op,
    U&&... arg)
{
    if(!::boost::type_erasure::check_match(table, op, std::forward<U>(arg)...)) {
        BOOST_THROW_EXCEPTION(::boost::type_erasure::bad_function_call());
    }
}


template<class Concept, class Op, class... U>
void require_match(
    const ::boost::type_erasure::binding<Concept>& table,
    const Op& op,
    U&&... arg)
{
    ::boost::type_erasure::is_relaxed<Concept> cond;
    ::boost::type_erasure::detail::require_match_impl(cond, table, op, ::std::forward<U>(arg)...);
}


template<class Op, class... U>
void require_match(
    const Op& op,
    U&&... arg)
{
    ::boost::type_erasure::is_relaxed<
        typename ::boost::type_erasure::detail::extract_concept<
            typename ::boost::type_erasure::detail::get_signature<Op>::type,
            U...>::type
    > cond;
    ::boost::type_erasure::detail::require_match_impl(cond, op, ::std::forward<U>(arg)...);
}

    bad_function_call() : ::std::invalid_argument("bad_function_call") {}


template<class P, class T, class Table>
bool maybe_check_table(const T& arg, const Table*& table, boost::mpl::true_)
{
    if(table == 0) {
        table = &::boost::type_erasure::detail::access::table(arg);
        return true;
    } else {
        return table->template find< ::boost::type_erasure::typeid_<P> >()() ==
            ::boost::type_erasure::detail::access::table(arg).
                template find< ::boost::type_erasure::typeid_<P> >()();
    }
}


template<class Concept>
bool check_table(const ::boost::type_erasure::binding<Concept>* t, void(*)())
{
    return true;
}


template<class Concept, class R, class T0, class... T, class U0, class... U>
bool check_table(
    const ::boost::type_erasure::binding<Concept>* t,
    R(*)(T0, T...),
    const U0& arg0,
    const U&... arg)
{
    typedef typename ::boost::remove_cv<
        typename ::boost::remove_reference<T0>::type
    >::type t0;
    if(!::boost::type_erasure::detail::maybe_check_table<t0>(
        arg0,
        t,
        ::boost::type_erasure::detail::should_check<Concept, t0>()))
        return false;

    return check_table(t, static_cast<void(*)(T...)>(0), arg...);
}


template<class Concept, class Op, class... U>
bool check_match(
    const ::boost::type_erasure::binding<Concept>& table,
    const Op&,
    U&&... arg)
{

    return ::boost::type_erasure::detail::check_table(
        &table,
        static_cast<typename ::boost::type_erasure::detail::get_signature<Op>::type*>(0),
        arg...);
}


template<
    class Op,
    class... U
>
bool check_match(
    const Op&,
    U&&... arg)
{
    const ::boost::type_erasure::binding<
        typename ::boost::type_erasure::detail::extract_concept<
            typename ::boost::type_erasure::detail::get_signature<Op>::type, U...>::type>* p = 0;

    return ::boost::type_erasure::detail::check_table(
        p, static_cast<typename ::boost::type_erasure::detail::get_signature<Op>::type*>(0), arg...);
}

template<class Map>
static_binding<Map> make_binding() { return static_binding<Map>(); }

    binding() { BOOST_MPL_ASSERT((::boost::type_erasure::is_relaxed<Concept>)); }

    template<class Map>
    explicit binding(const Map&)
      : impl((
            BOOST_TYPE_ERASURE_INSTANTIATE(Concept, Map),
            static_binding<Map>()
        ))
    {}

    template<class T>
    typename T::type find() const { return impl.table->lookup((T*)0); }

        impl_type() {
            table = &::boost::type_erasure::detail::make_vtable_init<
                typename ::boost::mpl::transform<
                    actual_concept,
                    ::boost::type_erasure::detail::get_null_vtable_entry<
                        ::boost::mpl::_1
                    >
                >::type,
                table_type
            >::type::value;
        }

        impl_type() {
            table = &::boost::type_erasure::detail::make_vtable_init<
                typename ::boost::mpl::transform<
                    actual_concept,
                    ::boost::type_erasure::detail::get_null_vtable_entry<
                        ::boost::mpl::_1
                    >
                >::type,
                table_type
            >::type::value;
        }

    void* _boost_type_erasure_deduce_constructor(...) { return 0; }

    void* _boost_type_erasure_deduce_assign(...) { return 0; }

    template<class S>
    static bool apply(const S& s1, const S& s2)
    {
        return true;
    }

    template<class S>
    static bool apply(const S& s1, const S& s2)
    {
        return static_cast<const vtable_entry<T0>&>(s1).value ==
            static_cast<const vtable_entry<T0>&>(s2).value &&
            compare_vtable<T...>::apply(s1, s2);
    }


    template<class Bindings, class Src>
    void convert_from(const Src& src)
    {
        *this = vtable_storage(
            src.lookup(
                (typename ::boost::type_erasure::detail::rebind_placeholders<
                T, Bindings
            >::type*)0)...);
    }


    bool operator==(const vtable_storage& other) const
    { return compare_vtable<T...>::apply(*this, other); }


    template<class U>
    typename U::type lookup(U*) const
    {
        return static_cast<const vtable_entry<U>*>(this)->value;
    }


    template<class Bindings, class Src>
    void convert_from(const Src& src) {}


    bool operator==(const vtable_storage& other) const
    { return true; }

    storage() {}

    template<class T>
    storage(const T& arg) : data(new T(arg)) {}


template<class T>
T extract(T arg) { return std::forward<T>(arg); }


template<class T>
T extract(storage& arg)
{
    return *static_cast<typename ::boost::remove_reference<T>::type*>(arg.data);
}


template<class T>
T extract(const storage& arg)
{
    return *static_cast<const typename ::boost::remove_reference<T>::type*>(arg.data);
}


template<class T>
T extract(storage&& arg)
{
    return std::move(*static_cast<typename ::boost::remove_reference<T>::type*>(arg.data));
}

    static R value(T... arg)
    {
        return PrimitiveConcept::apply(
            ::boost::type_erasure::detail::extract<U>(std::forward<T>(arg))...);
    }

    template<class Derived>
    static const typename Derived::table_type&
    table(const ::boost::type_erasure::any_base<Derived>& arg)
    {
        return static_cast<const Derived&>(arg).table;
    }

    template<class Concept, class T>
    static const typename any<Concept, T>::table_type&
    table(const ::boost::type_erasure::param<Concept, T>& arg)
    {
        return arg._impl.table;
    }

    template<class Derived>
    static ::boost::type_erasure::detail::storage&
    data(::boost::type_erasure::any_base<Derived>& arg)
    {
        return static_cast<Derived&>(arg).data;
    }
