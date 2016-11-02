
            not_a_valid_type()
            {}
 make_terminal(T &t, Expr *, proto::term<Arg0> *)
        {
            Expr that = {t};
            return that;
        }

            ignore()
            {}


            template<typename T>
            ignore(T const &)
            {}

            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr, Context>::type
            operator ()(Expr &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr>()(e, ctx);
            }

            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }

            template<typename Expr, typename Context>
            typename proto::result_of::eval<Expr const, Context>::type
            operator ()(Expr const &e, Context const &ctx) const
            {
                return typename Context::template eval<Expr const>()(e, ctx);
            }

    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr, Context>::type
    eval(Expr &e, Context const &ctx)
    {
        return typename Context::template eval<Expr>()(e, ctx);
    }

    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }

    template<typename Expr, typename Context>
    typename proto::result_of::eval<Expr const, Context>::type
    eval(Expr const &e, Context const &ctx)
    {
        return typename Context::template eval<Expr const>()(e, ctx);
    }
                                             \
        inline std::ostream &operator <<(std::ostream &sout, Tag const &)       \
        {                                                                       \
            return sout << BOOST_PP_STRINGIZE(Tag);                             \
        }                                                                       \
        /**/

        BOOST_PROTO_DEFINE_TAG_INSERTION(terminal)

            ostream_wrapper(std::ostream &sout)
              : sout_(sout)
            {}

            template<typename T>
            named_any(T const &)
              : name_(BOOST_SP_TYPEID(T).name())
            {}


        inline std::ostream &operator <<(ostream_wrapper sout_wrap, named_any t)
        {
            return sout_wrap.sout_ << t.name_;
        }

            explicit display_expr_impl(std::ostream &sout, int depth = 0)
              : depth_(depth)
              , first_(true)
              , sout_(sout)
            {}


            template<typename Expr>
            void operator()(Expr const &expr) const
            {
                this->impl(expr, mpl::long_<arity_of<Expr>::value>());
            }


            template<typename Expr>
            void impl(Expr const &expr, mpl::long_<0>) const
            {
                using namespace hidden_detail_;
                typedef typename tag_of<Expr>::type tag;
                this->sout_.width(this->depth_);
                this->sout_ << (this->first_? "" : ", ");
                this->sout_ << tag() << "(" << proto::value(expr) << ")\n";
                this->first_ = false;
            }


            template<typename Expr, typename Arity>
            void impl(Expr const &expr, Arity) const
            {
                using namespace hidden_detail_;
                typedef typename tag_of<Expr>::type tag;
                this->sout_.width(this->depth_);
                this->sout_ << (this->first_? "" : ", ");
                this->sout_ << tag() << "(\n";
                display_expr_impl display(this->sout_, this->depth_ + 4);
                fusion::for_each(expr, display);
                this->sout_.width(this->depth_);
                this->sout_ << "" << ")\n";
                this->first_ = false;
            }

            explicit display_expr(std::ostream &sout = std::cout, int depth = 0)
              : depth_(depth)
              , sout_(sout)
            {}

            template<typename Expr>
            void operator()(Expr const &expr) const
            {
                detail::display_expr_impl(this->sout_, this->depth_)(expr);
            }

    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
        functional::display_expr(sout, 0)(expr);
    }

    template<typename Expr>
    void display_expr(Expr const &expr)
    {
        functional::display_expr()(expr);
    }

    template<typename Grammar, typename Expr>
    void assert_matches(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, Grammar>));
    }

    template<typename Grammar, typename Expr>
    void assert_matches_not(Expr const & /*expr*/)
    {
        BOOST_MPL_ASSERT_NOT((proto::matches<Expr, Grammar>));
    }


            explicit expr_iterator(Expr &e)
              : expr(e)
            {}


            template<typename Expr>
            typename result<as_element(Expr &)>::type const
            operator ()(Expr &e) const
            {
                return typename result<as_element(Expr &)>::type(e);
            }


            template<typename Expr>
            typename result<as_element(Expr const &)>::type const
            operator ()(Expr const &e) const
            {
                return typename result<as_element(Expr const &)>::type(e);
            }


            explicit flat_view(Expr &e)
              : segs_(fusion::as_list(fusion::transform(e, as_element<typename Expr::proto_tag>())))
            {}


            template<typename Expr>
            proto::detail::flat_view<Expr> const
            operator ()(Expr &e) const
            {
                return proto::detail::flat_view<Expr>(e);
            }


            template<typename Expr>
            proto::detail::flat_view<Expr const> const
            operator ()(Expr const &e) const
            {
                return proto::detail::flat_view<Expr const>(e);
            }

    template<typename Expr>
    proto::detail::flat_view<Expr> const
    flatten(Expr &e)
    {
        return proto::detail::flat_view<Expr>(e);
    }

    template<typename Expr>
    proto::detail::flat_view<Expr const> const
    flatten(Expr const &e)
    {
        return proto::detail::flat_view<Expr const>(e);
    }

        explicit eval_fun(Context &ctx)
          : ctx_(ctx)
        {}


            template<typename Expr2, typename S, typename D>
            result_type operator()(Expr2 const &e, S const &, D const &) const
            {
                return proto_generator()(expr_type::make(e.proto_base().child0));
            }

            template<typename Expr>
            typename result_of::deep_copy<Expr>::type
            operator()(Expr const &e) const
            {
                return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
            }

    template<typename Expr>
    typename proto::result_of::deep_copy<Expr>::type
    deep_copy(Expr const &e)
    {
        return proto::detail::deep_copy_impl<Expr>()(e, 0, 0);
    }

            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return typename which::template impl<Expr, State, Data>()(e, s, d);
            }

                template<typename T> any(T const &) {}


        arg(type t)
          : value(t)
        {}


        operator type() const
        {
            return this->value;
        }


        type operator()() const
        {
            return this->value;
        }


        arg(type t)
          : value(t)
        {}


        operator type() const
        {
            return this->value;
        }


        type operator()() const
        {
            return this->value;
        }


        NullaryResult operator()() const
        {
            result<Derived const()> impl;
            return impl();
        }


        reverse_view_iterator(First const& first)
            : first(converter::convert(first)) {}


        reverse_view(Sequence& seq)
          : first(fusion::begin(seq))
          , last(fusion::end(seq))
        {}


                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }


                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }


                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }


                static type
                call(Sequence const& s)
                {
                    return type(s.last);
                }


                static type
                call(Sequence const& s)
                {
                    return type(s.first);
                }


    template <typename Sequence>
    inline reverse_view<Sequence const>
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
 &as_lvalue(T &t)
        {
            return t;
        }


    template <typename Sequence>
    inline typename meta::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename meta::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }

        template<typename T>
        T &lvalue(T &t)
        {
            return t;
        }


        template<typename T>
        T const &lvalue(T const &t)
        {
            return t;
        }

        template<typename U, typename V, typename T>
        U *proto_get_pointer(T &t, V *, U *)
        {
            return boost::addressof(t);
        }


        template<typename U, typename V, typename T>
        U const *proto_get_pointer(T &t, V *, U const *)
        {
            return boost::addressof(t);
        }


        template<typename U, typename V, typename T>
        V *proto_get_pointer(T &t, V *, ...)
        {
            return get_pointer(t);
        }


                result_type operator()(
                    typename add_reference<typename add_const<T>::type>::type t
                  , U u
                ) const
                {
                    return BOOST_PROTO_GET_POINTER(V, t) ->* u;
                }


            memfun(T t, pmf_type p)
              : obj(t)
              , pmf(p)
            {}


            result_type operator()() const
            {
                BOOST_PROTO_USE_GET_POINTER();
                return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)();
            }
 operator()(A0 const &a0) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0);
    }

    operator ()(A0 const &a0) const
    {
        result<
            Derived const(
                A0 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0));
    }

        template<typename Expr2, typename S, typename D>
        result_type operator()(Expr2 const &e, S const &, D const &) const
        {
            expr_type const that = {
                proto::deep_copy(e.proto_base().child0)
            };
            return proto_generator()(that);
        }

            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(typename Expr::proto_tag(), proto::value(expr));
            }

            result_type operator ()(Expr &expr, Context &ctx) const
            {
                return detail::mem_ptr_fun<r0, r1>()(
                    proto::eval(proto::child_c<0>(expr), ctx)
                  , proto::eval(proto::child_c<1>(expr), ctx)
                );
            }

        void operator()(Expr &, Context &) const
        {}

        result_type operator ()(Expr &expr, Context &context) const
        {
            return this->invoke(expr, context, is_member_function_pointer<function_type>());
        }

        result_type invoke(Expr &expr, Context &context, mpl::false_) const
        {
            return proto::eval(proto::child_c< 0>( expr), context)(
                proto::eval(proto::child_c< 1>( expr), context) , proto::eval(proto::child_c< 2>( expr), context)
            );
        }

        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx);
        }

            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr)
                );
            }


        template<typename Pair>
        typename Pair::first_type &operator()(Pair &pair) const
        {
            return pair.first;
        }


        template<typename Pair>
        typename Pair::first_type const &operator()(Pair const &pair) const
        {
            return pair.first;
        }


        template<typename Pair>
        typename Pair::second_type &operator()(Pair &pair) const
        {
            return pair.second;
        }


        template<typename Pair>
        typename Pair::second_type const &operator()(Pair const &pair) const
        {
            return pair.second;
        }


        template<typename InputIterator, typename Distance>
        void operator()(InputIterator &x, Distance n) const
        {
            std::advance(x, n);
        }


        template<typename ForwardIterator>
        ForwardIterator operator()(ForwardIterator x) const
        {
            return std::advance(
                x
              , static_cast<typename std::iterator_traits<ForwardIterator>::difference_type>(1)
            );
        }


        template<typename BidirectionalIterator>
        BidirectionalIterator operator()(BidirectionalIterator x) const
        {
            return std::advance(
                x
              , -static_cast<typename std::iterator_traits<BidirectionalIterator>::difference_type>(1)
            );
        }


        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }

            as_callable(Data d)
              : d_(d)
            {}

            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                typename when<_, Sequence>::template impl<Expr, State, Data> seq;
                detail::as_callable<Fun, Data> f(d);
                return fusion::fold(
                    seq(e, s, d)
                  , typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d)
                  , f
                );
            }

            result_type operator ()(
                typename impl::expr_param   e
              , typename impl::state_param  s
              , typename impl::data_param   d
            ) const
            {
                typename when<_, Sequence>::template impl<Expr, State, Data> seq;
                detail::as_callable<Fun, Data> f(d);
                return fusion::reverse_fold(
                    seq(e, s, d)
                  , typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d)
                  , f
                );
            }


                explicit env(const_reference value, Base const &base = Base())
                  : Base(base)
                  , value_(value)
                {}


                    result_type operator()(detail::arg<Env>) const
                    {
                        return result_type();
                    }

        template<typename T>
        typename proto::result_of::as_env<T &>::type const as_env(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T))
        {
            return proto::functional::as_env()(t);
        }


        template<typename T>
        typename proto::result_of::as_env<T const &>::type const as_env(T const &t)
        {
            return proto::functional::as_env()(t);
        }

        template<typename Key, typename Env>
        typename proto::result_of::has_env_var<Env &, Key>::type has_env_var(Env &e BOOST_PROTO_DISABLE_IF_IS_CONST(Env))
        {
            return functional::has_env_var<Key>()(e);
        }


        template<typename Key, typename Env>
        typename proto::result_of::has_env_var<Env const &, Key>::type has_env_var(Env const &e)
        {
            return functional::has_env_var<Key>()(e);
        }

        template<typename Key, typename Env>
        typename proto::result_of::env_var<Env &, Key>::type env_var(Env &e BOOST_PROTO_DISABLE_IF_IS_CONST(Env))
        {
            return functional::env_var<Key>()(e);
        }


        template<typename Key, typename Env>
        typename proto::result_of::env_var<Env const &, Key>::type env_var(Env const &e)
        {
            return functional::env_var<Key>()(e);
        }

            T operator()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return I;
            }


            key_not_found operator[](detail::any) const
            {
                return key_not_found();
            }


            template<typename T>
            T const &at(detail::any, T const &t) const
            {
                return t;
            }

            result_type operator ()(
                typename default_mem_ptr_impl::expr_param e
              , typename default_mem_ptr_impl::state_param s
              , typename default_mem_ptr_impl::data_param d
            ) const
            {
                typename Grammar::template impl<e0, State, Data> t0;
                typename Grammar::template impl<e1, State, Data> t1;
                return detail::mem_ptr_fun<r0, r1>()(
                    t0(proto::child_c<0>(e), s, d)
                  , t1(proto::child_c<1>(e), s, d)
                );
            }

            result_type const operator ()(
                typename default_mem_ptr_impl::expr_param e
              , typename default_mem_ptr_impl::state_param s
              , typename default_mem_ptr_impl::data_param d
            ) const
            {
                typename Grammar::template impl<e0, State, Data> t0;
                typename Grammar::template impl<e1, State, Data> t1;
                return detail::memfun<r0, r1>(
                    t0(proto::child_c<0>(e), s, d)
                  , t1(proto::child_c<1>(e), s, d)
                );
            }

                result_type operator ()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    typename Grammar::template impl<e0, State, Data> t0;
                    typename Grammar::template impl<e1, State, Data> t1;
                    return t0(proto::child_c<0>(e), s, d)
                          , t1(proto::child_c<1>(e), s, d);
                }


            result_type operator ()(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
            ) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)();
            }


            result_type operator ()(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
            ) const
            {
                return this->invoke(
                    e
                  , s
                  , d
                  , is_member_function_pointer<function_type>()
                  , is_member_object_pointer<function_type>()
                );
            }

            result_type invoke(
                typename default_function_impl::expr_param e
              , typename default_function_impl::state_param s
              , typename default_function_impl::data_param d
              , mpl::false_
              , mpl::false_
            ) const
            {
                return BOOST_PROTO_DEFAULT_EVAL(~, 0, e)(BOOST_PROTO_DEFAULT_EVAL(~, 1, e));
            }

            void operator ()(
                typename impl::expr_param
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {}

        template<typename T>
        T operator ()(T const &t) const
        {
            return t;
        }
 operator ()(A0 &a0) const
    {
        return Type(a0);
    }
 operator ()(A0 &a0) const
    {
        Type that = {a0};
        return that;
    }
 construct()
        {
            return construct_<Type>()();
        }

        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }

        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d )
            );
        }

        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d );
            return s1;
        }

        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state1 s1 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
