

        operator T const & () const
        {
            return one::value;
        }


        operator T const & () const
        {
            return zero::value;
        }

    template<typename A0>
    typename result<function1(A0 &)>::type
    operator ()(A0 &a0) const
    {
        typedef typename result<function1(A0 &)>::impl impl;
        typedef typename result<function1(A0 &)>::type type;
        typedef A0 &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }

    template<typename A0>
    typename result<function1(A0 const &)>::type
    operator ()(A0 const &a0) const
    {
        typedef typename result<function1(A0 const &)>::impl impl;
        typedef typename result<function1(A0 const &)>::type type;
        typedef A0 const &arg0;
        BOOST_CONCEPT_ASSERT((UnaryFunction<impl, type, arg0>));
        //boost::function_requires<UnaryFunctionConcept<impl, type, arg0> >();
        return impl()(a0);
    }

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::less(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::greater(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }

            To operator ()(From &arr) const
            {
                typename remove_const<To>::type res(arr.size());
                for(std::size_t i = 0, size = arr.size(); i != size; ++i)
                {
                    res[i] = numeric::promote<typename To::value_type>(arr[i]);
                }
                return res;
            }
                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<typename Left::value_type, Right>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<Left, typename Right::value_type>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<typename Left::value_type, Right>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<Left, typename Right::value_type>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(minus, -)
                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<typename Left::value_type, Right>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<Left, typename Right::value_type>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(minus, -)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(multiplies, *)
                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<typename Left::value_type, Right>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<Left, typename Right::value_type>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(minus, -)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(multiplies, *)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(divides, /)
                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left)          \
                    Op numeric::promote<std::valarray<right_value_type> >(right);       \
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, std_valarray_tag, void>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<typename Left::value_type, Right>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Left::value_type left_value_type;                          \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<left_value_type, Right>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return numeric::promote<std::valarray<left_value_type> >(left) Op right;\
            }                                                                           \
        };                                                                              \
        template<typename Left, typename Right>                                         \
        struct Name<Left, Right, void, std_valarray_tag>                                \
          : std::binary_function<                                                       \
                Left                                                                    \
              , Right                                                                   \
              , std::valarray<                                                          \
                    typename Name<Left, typename Right::value_type>::result_type        \
                >                                                                       \
            >                                                                           \
        {                                                                               \
            typedef typename Right::value_type right_value_type;                        \
            typedef                                                                     \
                std::valarray<                                                          \
                    typename Name<Left, right_value_type>::result_type                  \
                >                                                                       \
            result_type;                                                                \
            result_type                                                                 \
            operator ()(Left &left, Right &right) const                                 \
            {                                                                           \
                return left Op numeric::promote<std::valarray<right_value_type> >(right);\
            }                                                                           \
        };

        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(plus, +)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(minus, -)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(multiplies, *)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(divides, /)
        BOOST_NUMERIC_FUNCTIONAL_DEFINE_VALARRAY_BIN_OP(modulus, %)

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::less(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }

            void operator ()(Left &left, Right &right) const
            {
                BOOST_ASSERT(left.size() == right.size());
                for(std::size_t i = 0, size = left.size(); i != size; ++i)
                {
                    if(numeric::greater(right[i], left[i]))
                    {
                        left[i] = right[i];
                    }
                }
            }

            To operator ()(From &arr) const
            {
                typename remove_const<To>::type res(arr.size());
                for(std::size_t i = 0, size = arr.size(); i != size; ++i)
                {
                    res[i] = numeric::promote<typename To::value_type>(arr[i]);
                }
                return res;
            }

    template<typename Args>
    dont_care(Args const &)
    {
    }

    detail::void_ operator ()(dont_care)
    {
    }


    detail::void_ add_ref(dont_care)
    {
    }


    detail::void_ drop(dont_care)
    {
    }


    detail::void_ on_drop(dont_care)
    {
    }

    void constraints()
    {
        // TODO: define the stat concept
    }

        explicit accumulator_visitor(Args const &a)
          : args(a)
        {
        }


        template<typename Accumulator>
        void operator ()(Accumulator &accumulator) const
        {
            accumulator(this->args);
        }


    template<typename Args>
    inline accumulator_visitor<Args> const make_accumulator_visitor(Args const &args)
    {
        return accumulator_visitor<Args>(args);
    }

    accumulator_set()
      : accumulators(
            detail::make_acc_list(
                accumulators_mpl_vector()
              , detail::accumulator_params()(*this)
            )
        )
    {
        // Add-ref the Features that the user has specified
        this->template visit_if<detail::contains_feature_of_<Features> >(
            detail::make_add_ref_visitor(detail::accumulator_params()(*this))
        );
    }

    template<typename A1>
    explicit accumulator_set(A1 const &a1)
      : accumulators(
            detail::make_acc_list(
                accumulators_mpl_vector()
              , detail::accumulator_params()(*this, a1)
            )
        )
    {
        // Add-ref the Features that the user has specified
        this->template visit_if<detail::contains_feature_of_<Features> >(
            detail::make_add_ref_visitor(detail::accumulator_params()(*this))
        );
    }

    void operator ()()
    {
        this->visit(
            detail::make_accumulator_visitor(
                detail::accumulator_params()(*this)
            )
        );
    }


    template<typename A1>
    void operator ()(A1 const &a1)
    {
        this->visit(
            detail::make_accumulator_visitor(
                detail::accumulator_params()(*this, a1)
            )
        );
    }


            template<typename Args>
            static fusion::nil
            call(Args const &, First const&, Last const&)
            {
                return fusion::nil();
            }


        template<typename Sequence, typename Args>
        typename meta::make_acc_list<Sequence>::type
        make_acc_list(Sequence const &seq, Args const &args)
        {
            return meta::make_acc_list<Sequence>::call(args, fusion::begin(seq), fusion::end(seq));
        }


            accumulator_wrapper(accumulator_wrapper const &that)
              : Accumulator(*static_cast<Accumulator const *>(&that))
            {
            }


            template<typename Args>
            accumulator_wrapper(Args const &args)
              : Accumulator(args)
            {
            }


    template<typename Feature, typename AccumulatorSet>
    typename extractor_result<AccumulatorSet, Feature>::type
    do_extract(AccumulatorSet const &acc, mpl::true_)
    {
        typedef typename as_feature<Feature>::type feature_type;
        return extract_result<feature_type>(acc);
    }

    template<typename Arg1>
    typename detail::extractor_result<Arg1, Feature>::type
    operator ()(Arg1 const &arg1) const
    {
        // Arg1 could be an accumulator_set or an argument pack containing
        // an accumulator_set. Dispatch accordingly.
        return detail::do_extract<Feature>(arg1, detail::is_accumulator_set<Arg1>());
    }

    template<typename AccumulatorSet, typename A1>
    typename detail::extractor_result<AccumulatorSet, Feature>::type
    operator ()(AccumulatorSet const &acc, A1 const &a1) const
    {
        BOOST_MPL_ASSERT((detail::is_accumulator_set<AccumulatorSet>));
        typedef typename as_feature<Feature>::type feature_type;
        return extract_result<feature_type>(acc, a1);
    }

            explicit add_ref_visitor(Args const &args)
              : args_(args)
            {
            }


            template<typename Accumulator>
            void operator ()(Accumulator &acc) const
            {
                typedef typename Accumulator::feature_tag::dependencies dependencies;

                acc.add_ref(this->args_);

                // Also add_ref accumulators that this feature depends on
                this->args_[accumulator].template
                    visit_if<detail::contains_feature_of_<dependencies> >(
                        *this
                );
            }


        template<typename Args>
        add_ref_visitor<Args> make_add_ref_visitor(Args const &args)
        {
            return add_ref_visitor<Args>(args);
        }

            explicit drop_visitor(Args const &args)
              : args_(args)
            {
            }


            template<typename Accumulator>
            void operator ()(Accumulator &acc) const
            {
                if(typename Accumulator::is_droppable())
                {
                    typedef typename Accumulator::feature_tag::dependencies dependencies;

                    acc.drop(this->args_);
                    // Also drop accumulators that this feature depends on
                    this->args_[accumulator].template
                        visit_if<detail::contains_feature_of_<dependencies> >(
                            *this
                    );
                }
            }


        template<typename Args>
        drop_visitor<Args> make_drop_visitor(Args const &args)
        {
            return drop_visitor<Args>(args);
        }


        template<typename Args>
        droppable_accumulator_base(Args const &args)
          : Accumulator(args)
          , ref_count_(0)
        {
        }


        droppable_accumulator_base(droppable_accumulator_base const &that)
          : Accumulator(*static_cast<Accumulator const *>(&that))
          , ref_count_(that.ref_count_)
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            if(!this->is_dropped())
            {
                this->Accumulator::operator ()(args);
            }
        }


        template<typename Args>
        void add_ref(Args const &)
        {
            ++this->ref_count_;
        }


        template<typename Args>
        void drop(Args const &args)
        {
            BOOST_ASSERT(0 < this->ref_count_);
            if(1 == this->ref_count_)
            {
                static_cast<droppable_accumulator<Accumulator> *>(this)->on_drop(args);
            }
            --this->ref_count_;
        }


        bool is_dropped() const
        {
            return 0 == this->ref_count_;
        }

        template<typename Args>
        droppable_accumulator(Args const &args)
          : droppable_accumulator::base(args)
        {
        }


        droppable_accumulator(droppable_accumulator const &that)
          : droppable_accumulator::base(*static_cast<typename droppable_accumulator::base const *>(&that))
        {
        }


        template<typename Args>
        with_cached_result(Args const &args)
          : Accumulator(args)
          , cache()
        {
        }


        with_cached_result(with_cached_result const &that)
          : Accumulator(*static_cast<Accumulator const *>(&that))
          , cache()
        {
            if(that.has_result())
            {
                this->set(that.get());
            }
        }


        ~with_cached_result()
        {
            // Since this is a base class of droppable_accumulator_base,
            // this destructor is called before any of droppable_accumulator_base's
            // members get cleaned up, including is_dropped, so the following
            // call to has_result() is valid.
            if(this->has_result())
            {
                this->get().~result_type();
            }
        }


        template<typename Args>
        void on_drop(Args const &args)
        {
            // cache the result at the point this calculation was dropped
            BOOST_ASSERT(!this->has_result());
            this->set(this->Accumulator::result(args));
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->has_result() ? this->get() : this->Accumulator::result(args);
        }


        void set(result_type const &r)
        {
            ::new(this->cache.address()) result_type(r);
        }


        result_type const &get() const
        {
            return *static_cast<result_type const *>(this->cache.address());
        }


        bool has_result() const
        {
            typedef with_cached_result<Accumulator> this_type;
            typedef droppable_accumulator_base<this_type> derived_type;
            return static_cast<derived_type const *>(this)->is_dropped();
        }


        template<typename Args>
        reference_accumulator_impl(Args const &args)
          : ref(args[parameter::keyword<Tag>::get()])
        {
        }


        result_type result(dont_care) const
        {
            return this->ref;
        }


        template<typename Args>
        value_accumulator_impl(Args const &args)
          : val(args[parameter::keyword<Tag>::get()])
        {
        }


        result_type result(dont_care) const
        {
            return this->val;
        }


        external_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->extract_(args, args[parameter::keyword<Tag>::get() | 0]);
        }


        template<typename Args>
        static result_type extract_(Args const &args, int)
        {
            // No named parameter passed to the extractor. Maybe the external
            // feature is held by reference<>.
            extractor<feature_tag> extract;
            return extract(accumulators::reference_tag<Tag>(args));
        }


        template<typename Args, typename AccumulatorSet>
        static result_type extract_(Args const &, AccumulatorSet const &acc)
        {
            // OK, a named parameter for this external feature was passed to the
            // extractor, so use that.
            extractor<feature_tag> extract;
            return extract(acc);
        }


        error_of_impl(dont_care)
        {
        }


        result_type result(dont_care) const
        {
            return 0;
        }


        template<typename Args>
        weighted_sum_kahan_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()] * numeric::one<Weight>::value),
                compensation(boost::numeric_cast<weighted_sample>(0.0))
        {
        }


        template<typename Args>
        void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
        __attribute__((__optimize__("no-associative-math")))
#endif
        operator ()(Args const &args)
        {
            const weighted_sample myTmp1 = args[parameter::keyword<Tag>::get()] * args[weight] - this->compensation;
            const weighted_sample myTmp2 = this->weighted_sum_ + myTmp1;
            this->compensation = (myTmp2 - this->weighted_sum_) - myTmp1;
            this->weighted_sum_ = myTmp2;

        }


        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }


            result_type
            operator ()(Left & left, Right & right) const
            {
                std::size_t left_size = left.size();
                std::size_t right_size = right.size();
                result_type result(left_size, right_size);
                for (std::size_t i = 0; i < left_size; ++i)
                    for (std::size_t j = 0; j < right_size; ++j)
                        result(i,j) = numeric::multiplies(left[i], right[j]);
                return result;
            }


        template<typename Args>
        covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::average(args[sample | Sample()], (std::size_t)1)
                  , numeric::average(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                )
            )
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::mean_of_variates<VariateType, VariateTag> > const some_mean_of_variates = {};

                this->cov_ = this->cov_*(cnt-1.)/cnt
                           + numeric::outer_product(
                                 some_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , mean(args) - args[sample]
                             ) / (cnt-1.);
            }
        }


        result_type result(dont_care) const
        {
            return this->cov_;
        }


        template<typename Args>
        rolling_sum_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {}


        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= rolling_window_plus1(args).front();
            }
            this->sum_ += args[sample];
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->sum_;
        }


        pot_tail_mean_impl(dont_care)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
        {
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_peaks_over_threshold<LeftRight>
                  , tag::peaks_over_threshold<LeftRight>
                >::type
            peaks_over_threshold_tag;

            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_pot_quantile<LeftRight>
                  , tag::pot_quantile<LeftRight>
                >::type
            pot_quantile_tag;

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};
            extractor<pot_quantile_tag> const some_pot_quantile = {};

            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return some_pot_quantile(args) - this->sign_ * beta_bar/( xi_hat - 1. ) * std::pow(
                is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
              , -xi_hat);
        }


        template<typename Args>
        weighted_sum_impl(Args const &args)
          : weighted_sum_(
                args[parameter::keyword<Tag>::get() | Sample()]
                  * numeric::one<Weight>::value
            )
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->weighted_sum_ += args[parameter::keyword<Tag>::get()] * args[weight];
        }


        result_type result(dont_care) const
        {
            return this->weighted_sum_;
        }


        template<typename Args>
        min_impl(Args const &args)
          : min_(numeric::as_max(args[sample | Sample()]))
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::min_assign(this->min_, args[sample]);
        }


        result_type result(dont_care) const
        {
            return this->min_;
        }


        pot_quantile_impl(dont_care)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
        {
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl, weighted>
                  , tag::weighted_peaks_over_threshold<LeftRight>
                  , tag::peaks_over_threshold<LeftRight>
                >::type
            peaks_over_threshold_tag;

            extractor<peaks_over_threshold_tag> const some_peaks_over_threshold = {};

            float_type u_bar    = some_peaks_over_threshold(args).template get<0>();
            float_type beta_bar = some_peaks_over_threshold(args).template get<1>();
            float_type xi_hat   = some_peaks_over_threshold(args).template get<2>();

            return this->sign_ * (u_bar + beta_bar/xi_hat * ( std::pow(
                    is_same<LeftRight, left>::value ? args[quantile_probability] : 1. - args[quantile_probability]
                , -xi_hat
              ) - 1.));
        }


        error_of_mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            using namespace std;
            extractor<Variance> const variance = {};
            return sqrt(numeric::average(variance(args), count(args) - 1));
        }


        rolling_count_impl(dont_care)
        {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return static_cast<std::size_t>(rolling_window_plus1(args).size()) - is_rolling_window_plus1_full(args);
        }

    template<typename Args>
    sum_kahan_impl(Args const & args)
      : sum(args[parameter::keyword<Tag>::get() | Sample()]),
        compensation(boost::numeric_cast<Sample>(0.0))
    {
    }


    template<typename Args>
    void 
#if BOOST_ACCUMULATORS_GCC_VERSION > 40305
    __attribute__((__optimize__("no-associative-math")))
#endif
    operator ()(Args const & args)
    {
        const Sample myTmp1 = args[parameter::keyword<Tag>::get()] - this->compensation;
        const Sample myTmp2 = this->sum + myTmp1;
        this->compensation = (myTmp2 - this->sum) - myTmp1;
        this->sum = myTmp2;
    }


    result_type result(dont_care) const
    {
      return this->sum;
    }


        lazy_weighted_variance_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> const some_mean = {};
            result_type tmp = some_mean(args);
            return accumulators::weighted_moment<2>(args) - tmp * tmp;
        }


        template<typename Args>
        weighted_variance_impl(Args const &args)
          : weighted_variance(numeric::average(args[sample | Sample()], numeric::one<Weight>::value))
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> const some_mean = {};

                result_type tmp = args[parameter::keyword<Tag>::get()] - some_mean(args);

                this->weighted_variance =
                    numeric::average(this->weighted_variance * (sum_of_weights(args) - args[weight]), sum_of_weights(args))
                  + numeric::average(tmp * tmp * args[weight], sum_of_weights(args) - args[weight] );
            }
        }


        result_type result(dont_care) const
        {
            return this->weighted_variance;
        }


        rolling_mean_impl(dont_care)
        {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(rolling_sum(args), rolling_count(args));
        }


        coherent_tail_mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            extractor<tag::non_coherent_tail_mean<LeftRight> > const some_non_coherent_tail_mean = {};

            return some_non_coherent_tail_mean(args)
                 + numeric::average(quantile(args), n)
                 * (
                     ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability]
                     - numeric::average(n, count(args))
                   );
        }


        non_coherent_tail_mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if (n <= static_cast<std::size_t>(tail(args).size()))
                return numeric::average(
                    std::accumulate(
                        tail(args).begin()
                      , tail(args).begin() + n
                      , Sample(0)
                    )
                  , n
                );
            else
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }
            }
        }


        weighted_mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Tag, tag::sample>
                  , tag::weighted_sum
                  , tag::weighted_sum_of_variates<Sample, Tag>
                >::type
            weighted_sum_tag;

            extractor<weighted_sum_tag> const some_weighted_sum = {};

            return numeric::average(some_weighted_sum(args), sum_of_weights(args));
        }


        template<typename Args>
        immediate_weighted_mean_impl(Args const &args)
          : mean(
                numeric::average(
                    args[parameter::keyword<Tag>::get() | Sample()]
                      * numeric::one<Weight>::value
                  , numeric::one<Weight>::value
                )
            )
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            // Matthias:
            //  need to pass the argument pack since the weight might be an external
            //  accumulator set passed as a named parameter
            Weight w_sum = sum_of_weights(args);
            Weight w = args[weight];
            weighted_sample const &s = args[parameter::keyword<Tag>::get()] * w;
            this->mean = numeric::average(this->mean * (w_sum - w) + s, w_sum);
        }


        result_type result(dont_care) const
        {
            return this->mean;
        }


        template<typename Args>
        weighted_peaks_over_threshold_impl(Args const &args)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
          , mu_(sign_ * numeric::average(args[sample | Sample()], (std::size_t)1))
          , sigma2_(numeric::average(args[sample | Sample()], (std::size_t)1))
          , w_sum_(numeric::average(args[weight | Weight()], (std::size_t)1))
          , threshold_(sign_ * args[pot_threshold_value])
          , fit_parameters_(boost::make_tuple(0., 0., 0.))
          , is_dirty_(true)
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty_ = true;

            if (this->sign_ * args[sample] > this->threshold_)
            {
                this->mu_ += args[weight] * args[sample];
                this->sigma2_ += args[weight] * args[sample] * args[sample];
                this->w_sum_ += args[weight];
            }
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty_)
            {
                this->is_dirty_ = false;

                this->mu_ = this->sign_ * numeric::average(this->mu_, this->w_sum_);
                this->sigma2_ = numeric::average(this->sigma2_, this->w_sum_);
                this->sigma2_ -= this->mu_ * this->mu_;

                float_type threshold_probability = numeric::average(sum_of_weights(args) - this->w_sum_, sum_of_weights(args));

                float_type tmp = numeric::average(( this->mu_ - this->threshold_ )*( this->mu_ - this->threshold_ ), this->sigma2_);
                float_type xi_hat = 0.5 * ( 1. - tmp );
                float_type beta_hat = 0.5 * ( this->mu_ - this->threshold_ ) * ( 1. + tmp );
                float_type beta_bar = beta_hat * std::pow(1. - threshold_probability, xi_hat);
                float_type u_bar = this->threshold_ - beta_bar * ( std::pow(1. - threshold_probability, -xi_hat) - 1.)/xi_hat;
                this->fit_parameters_ = boost::make_tuple(u_bar, beta_bar, xi_hat);
            }

            return this->fit_parameters_;
        }


        template<typename Args>
        weighted_peaks_over_threshold_prob_impl(Args const &args)
          : sign_((is_same<LeftRight, left>::value) ? -1 : 1)
          , mu_(sign_ * numeric::average(args[sample | Sample()], (std::size_t)1))
          , sigma2_(numeric::average(args[sample | Sample()], (std::size_t)1))
          , threshold_probability_(args[pot_threshold_probability])
          , fit_parameters_(boost::make_tuple(0., 0., 0.))
          , is_dirty_(true)
        {
        }


        void operator ()(dont_care)
        {
            this->is_dirty_ = true;
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty_)
            {
                this->is_dirty_ = false;

                float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? this->threshold_probability_ : 1. - this->threshold_probability_ );

                std::size_t n = 0;
                Weight sum = Weight(0);

                while (sum < threshold)
                {
                    if (n < static_cast<std::size_t>(tail_weights(args).size()))
                    {
                        mu_ += *(tail_weights(args).begin() + n) * *(tail(args).begin() + n);
                        sigma2_ += *(tail_weights(args).begin() + n) * *(tail(args).begin() + n) * (*(tail(args).begin() + n));
                        sum += *(tail_weights(args).begin() + n);
                        n++;
                    }
                    else
                    {
                        if (std::numeric_limits<float_type>::has_quiet_NaN)
                        {
                            return boost::make_tuple(
                                std::numeric_limits<float_type>::quiet_NaN()
                              , std::numeric_limits<float_type>::quiet_NaN()
                              , std::numeric_limits<float_type>::quiet_NaN()
                            );
                        }
                        else
                        {
                            std::ostringstream msg;
                            msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                            boost::throw_exception(std::runtime_error(msg.str()));
                            return boost::make_tuple(Sample(0), Sample(0), Sample(0));
                        }
                    }
                }

                float_type u = *(tail(args).begin() + n - 1) * this->sign_;


                this->mu_ = this->sign_ * numeric::average(this->mu_, sum);
                this->sigma2_ = numeric::average(this->sigma2_, sum);
                this->sigma2_ -= this->mu_ * this->mu_;

                if (is_same<LeftRight, left>::value)
                    this->threshold_probability_ = 1. - this->threshold_probability_;

                float_type tmp = numeric::average(( this->mu_ - u )*( this->mu_ - u ), this->sigma2_);
                float_type xi_hat = 0.5 * ( 1. - tmp );
                float_type beta_hat = 0.5 * ( this->mu_ - u ) * ( 1. + tmp );
                float_type beta_bar = beta_hat * std::pow(1. - threshold_probability_, xi_hat);
                float_type u_bar = u - beta_bar * ( std::pow(1. - threshold_probability_, -xi_hat) - 1.)/xi_hat;
                this->fit_parameters_ = boost::make_tuple(u_bar, beta_bar, xi_hat);

            }

            return this->fit_parameters_;
        }


        non_coherent_weighted_tail_mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
                }
                else
                {
                    if (std::numeric_limits<result_type>::has_quiet_NaN)
                    {
                        return std::numeric_limits<result_type>::quiet_NaN();
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                        return result_type(0);
                    }
                }
            }

            return numeric::average(
                std::inner_product(
                    tail(args).begin()
                  , tail(args).begin() + n
                  , tail_weights(args).begin()
                  , weighted_sample(0)
                )
              , sum
            );
        }


        weighted_tail_variate_means_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
                }
                else
                {
                    if (std::numeric_limits<float_type>::has_quiet_NaN)
                    {
                        std::fill(
                            this->tail_means_.begin()
                          , this->tail_means_.end()
                          , std::numeric_limits<float_type>::quiet_NaN()
                        );
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                    }
                }
            }

            std::size_t num_variates = tail_variate(args).begin()->size();

            this->tail_means_.clear();
            this->tail_means_.resize(num_variates, Sample(0));

            this->tail_means_ = std::inner_product(
                tail_variate(args).begin()
              , tail_variate(args).begin() + n
              , tail_weights(args).begin()
              , this->tail_means_
              , numeric::functional::plus<array_type const, array_type const>()
              , numeric::functional::multiply_and_promote_to_double<VariateType const, Weight const>()
            );

            float_type factor = sum * ( (is_same<Impl, relative>::value) ? non_coherent_weighted_tail_mean(args) : 1. );

            std::transform(
                this->tail_means_.begin()
              , this->tail_means_.end()
              , this->tail_means_.begin()
              , std::bind2nd(numeric::functional::divides<typename array_type::value_type const, float_type const>(), factor)
            );

            return make_iterator_range(this->tail_means_);
        }


        template<typename Args>
        max_impl(Args const &args)
          : max_(numeric::as_min(args[sample | Sample()]))
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            numeric::max_assign(this->max_, args[sample]);
        }


        result_type result(dont_care) const
        {
            return this->max_;
        }


        skewness_impl(dont_care)
        {
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(
                        accumulators::moment<3>(args)
                        - 3. * accumulators::moment<2>(args) * mean(args)
                        + 2. * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * std::sqrt( accumulators::moment<2>(args) - mean(args) * mean(args) )
                   );
        }


        template<typename Args>
        weighted_moment_impl(Args const &args)
          : sum(args[sample | Sample()] * numeric::one<Weight>::value)
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            this->sum += args[weight] * numeric::pow(args[sample], N());
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(this->sum, sum_of_weights(args));
        }


        weighted_kurtosis_impl(dont_care)
        {
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(
                        accumulators::weighted_moment<4>(args)
                        - 4. * accumulators::weighted_moment<3>(args) * weighted_mean(args)
                        + 6. * accumulators::weighted_moment<2>(args) * weighted_mean(args) * weighted_mean(args)
                        - 3. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                        * ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   ) - 3.;
        }


        kurtosis_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(
                        accumulators::moment<4>(args)
                        - 4. * accumulators::moment<3>(args) * mean(args)
                        + 6. * accumulators::moment<2>(args) * mean(args) * mean(args)
                        - 3. * mean(args) * mean(args) * mean(args) * mean(args)
                      , ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                        * ( accumulators::moment<2>(args) - mean(args) * mean(args) )
                    ) - 3.;
        }


        template<typename Args>
        weighted_covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::average(args[sample | Sample()], (std::size_t)1)
                      * numeric::one<Weight>::value
                  , numeric::average(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                      * numeric::one<Weight>::value
                )
            )
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::weighted_mean_of_variates<VariateType, VariateTag> > const some_weighted_mean_of_variates = {};

                this->cov_ = this->cov_ * (sum_of_weights(args) - args[weight]) / sum_of_weights(args)
                           + numeric::outer_product(
                                 some_weighted_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , weighted_mean(args) - args[sample]
                             ) * args[weight] / (sum_of_weights(args) - args[weight]);
            }
        }


        result_type result(dont_care) const
        {
            return this->cov_;
        }


        template<typename Args>
        weighted_p_square_quantile_impl(Args const &args)
          : p(is_same<Impl, for_median>::value ? 0.5 : args[quantile_probability | 0.5])
          , heights()
          , actual_positions()
          , desired_positions()
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            // accumulate 5 first samples
            if (cnt <= 5)
            {
                this->heights[cnt - 1] = args[sample];

                // In this initialization phase, actual_positions stores the weights of the
                // initial samples that are needed at the end of the initialization phase to
                // compute the correct initial positions of the markers.
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights and actual_positions by sorting
                if (cnt == 5)
                {
                    // TODO: we need to sort the initial samples (in heights) in ascending order and
                    // sort their weights (in actual_positions) the same way. The following lines do
                    // it, but there must be a better and more efficient way of doing this.
                    typename array_type::iterator it_begin, it_end, it_min;

                    it_begin = this->heights.begin();
                    it_end   = this->heights.end();

                    std::size_t pos = 0;

                    while (it_begin != it_end)
                    {
                        it_min = std::min_element(it_begin, it_end);
                        std::size_t d = std::distance(it_begin, it_min);
                        std::swap(*it_begin, *it_min);
                        std::swap(this->actual_positions[pos], this->actual_positions[pos + d]);
                        ++it_begin;
                        ++pos;
                    }

                    // calculate correct initial actual positions
                    for (std::size_t i = 1; i < 5; ++i)
                    {
                        this->actual_positions[i] += this->actual_positions[i - 1];
                    }
                }
            }
            else
            {
                std::size_t sample_cell = 1; // k

                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if (this->heights[4] <= args[sample])
                {
                    this->heights[4] = args[sample];
                    sample_cell = 4;
                }
                else
                {
                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // increment positions of markers above sample_cell
                for (std::size_t i = sample_cell; i < 5; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // update desired positions for all markers
                this->desired_positions[0] = this->actual_positions[0];
                this->desired_positions[1] = (sum_of_weights(args) - this->actual_positions[0])
                                           * this->p/2. + this->actual_positions[0];
                this->desired_positions[2] = (sum_of_weights(args) - this->actual_positions[0])
                                           * this->p + this->actual_positions[0];
                this->desired_positions[3] = (sum_of_weights(args) - this->actual_positions[0])
                                           * (1. + this->p)/2. + this->actual_positions[0];
                this->desired_positions[4] = sum_of_weights(args);

                // adjust height and actual positions of markers 1 to 3 if necessary
                for (std::size_t i = 1; i <= 3; ++i)
                {
                    // offset to desired positions
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if ( ( d >= 1. && dp > 1. ) || ( d <= -1. && dm < -1. ) )
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ( (sign_d - dm) * hp + (dp - sign_d) * hm );

                        if ( this->heights[i - 1] < h && h < this->heights[i + 1] )
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if (d>0)
                            {
                                this->heights[i] += hp;
                            }
                            if (d<0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }


        result_type result(dont_care) const
        {
            return this->heights[2];
        }

    template<typename T>
    T const &pow(T const &x, mpl::int_<1>)
    {
        return x;
    }


        template<typename Args>
        moment_impl(Args const &args)
          : sum(args[sample | Sample()])
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            this->sum += numeric::pow(args[sample], N());
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(this->sum, count(args));
        }


        mean_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<SumFeature> sum;
            return numeric::average(sum(args), count(args));
        }


        template<typename Args>
        immediate_mean_impl(Args const &args)
          : mean(numeric::average(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            this->mean = numeric::average(
                (this->mean * (cnt - 1)) + args[parameter::keyword<Tag>::get()]
              , cnt
            );
        }


        result_type result(dont_care) const
        {
            return this->mean;
        }


        template<typename Args>
        weighted_density_impl(Args const &args)
            : cache_size(args[density_cache_size])
            , cache(cache_size)
            , num_bins(args[density_num_bins])
            , samples_in_bin(num_bins + 2, 0.)
            , bin_positions(num_bins + 2)
            , histogram(
                num_bins + 2
              , std::make_pair(
                    numeric::average(args[sample | Sample()],(std::size_t)1)
                  , numeric::average(args[sample | Sample()],(std::size_t)1)
                )
              )
            , is_dirty(true)
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);

            // Fill up cache with cache_size first samples
            if (cnt <= this->cache_size)
            {
                this->cache[cnt - 1] = std::make_pair(args[sample], args[weight]);
            }

            // Once cache_size samples have been accumulated, create num_bins bins of same size between
            // the minimum and maximum of the cached samples as well as an under- and an overflow bin.
            // Store their lower bounds (bin_positions) and fill the bins with the cached samples (samples_in_bin).
            if (cnt == this->cache_size)
            {
                float_type minimum = numeric::average((min)(args),(std::size_t)1);
                float_type maximum = numeric::average((max)(args),(std::size_t)1);
                float_type bin_size = numeric::average(maximum - minimum, this->num_bins);

                // determine bin positions (their lower bounds)
                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->bin_positions[i] = minimum + (i - 1.) * bin_size;
                }

                for (typename histogram_type::const_iterator iter = this->cache.begin(); iter != this->cache.end(); ++iter)
                {
                    if (iter->first < this->bin_positions[1])
                    {
                        this->samples_in_bin[0] += iter->second;
                    }
                    else if (iter->first >= this->bin_positions[this->num_bins + 1])
                    {
                        this->samples_in_bin[this->num_bins + 1] += iter->second;
                    }
                    else
                    {
                        typename array_type::iterator it = std::upper_bound(
                            this->bin_positions.begin()
                          , this->bin_positions.end()
                          , iter->first
                        );

                        std::size_t d = std::distance(this->bin_positions.begin(), it);
                        this->samples_in_bin[d - 1] += iter->second;
                    }
                }
            }
            // Add each subsequent sample to the correct bin
            else if (cnt > this->cache_size)
            {
                if (args[sample] < this->bin_positions[1])
                {
                    this->samples_in_bin[0] += args[weight];
                }
                else if (args[sample] >= this->bin_positions[this->num_bins + 1])
                {
                    this->samples_in_bin[this->num_bins + 1] += args[weight];
                }
                else
                {
                    typename array_type::iterator it = std::upper_bound(
                        this->bin_positions.begin()
                      , this->bin_positions.end()
                      , args[sample]
                    );

                    std::size_t d = std::distance(this->bin_positions.begin(), it);
                    this->samples_in_bin[d - 1] += args[weight];
                }
            }
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                // creates a vector of std::pair where each pair i holds
                // the values bin_positions[i] (x-axis of histogram) and
                // samples_in_bin[i] / cnt (y-axis of histogram).

                for (std::size_t i = 0; i < this->num_bins + 2; ++i)
                {
                    this->histogram[i] = std::make_pair(this->bin_positions[i], numeric::average(this->samples_in_bin[i], sum_of_weights(args)));
                }
            }

            // returns a range of pairs
            return make_iterator_range(this->histogram);
        }


        template<typename Args>
        sum_impl(Args const &args)
          : sum(args[parameter::keyword<Tag>::get() | Sample()])
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            // what about overflow?
            this->sum += args[parameter::keyword<Tag>::get()];
        }


        result_type result(dont_care) const
        {
            return this->sum;
        }


    inline times2_iterator make_times2_iterator(std::size_t i)
    {
        return make_transform_iterator(
            make_counting_iterator(i)
          , std::bind1st(std::multiplies<std::size_t>(), 2)
        );
    }

        lvalue_index_iterator(Base base)
          : Base(base)
        {
        }


        typename Base::reference operator [](typename Base::difference_type n) const
        {
            return *(*this + n);
        }


        lazy_variance_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            extractor<MeanFeature> mean;
            result_type tmp = mean(args);
            return accumulators::moment<2>(args) - tmp * tmp;
        }


        template<typename Args>
        variance_impl(Args const &args)
          : variance(numeric::average(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if(cnt > 1)
            {
                extractor<MeanFeature> mean;
                result_type tmp = args[parameter::keyword<Tag>::get()] - mean(args);
                this->variance =
                    numeric::average(this->variance * (cnt - 1), cnt)
                  + numeric::average(tmp * tmp, cnt - 1);
            }
        }


        result_type result(dont_care) const
        {
            return this->variance;
        }


        template<typename Args>
        weighted_extended_p_square_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
          , heights(2 * probabilities.size() + 3)
          , actual_positions(heights.size())
          , desired_positions(heights.size())
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t num_quantiles = this->probabilities.size();

            // m+2 principal markers and m+1 middle markers
            std::size_t num_markers = 2 * num_quantiles + 3;

            // first accumulate num_markers samples
            if(cnt <= num_markers)
            {
                this->heights[cnt - 1] = args[sample];
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights (and actual_positions) by sorting
                if(cnt == num_markers)
                {
                    // TODO: we need to sort the initial samples (in heights) in ascending order and
                    // sort their weights (in actual_positions) the same way. The following lines do
                    // it, but there must be a better and more efficient way of doing this.
                    typename array_type::iterator it_begin, it_end, it_min;

                    it_begin = this->heights.begin();
                    it_end   = this->heights.end();

                    std::size_t pos = 0;

                    while (it_begin != it_end)
                    {
                        it_min = std::min_element(it_begin, it_end);
                        std::size_t d = std::distance(it_begin, it_min);
                        std::swap(*it_begin, *it_min);
                        std::swap(this->actual_positions[pos], this->actual_positions[pos + d]);
                        ++it_begin;
                        ++pos;
                    }

                    // calculate correct initial actual positions
                    for (std::size_t i = 1; i < num_markers; ++i)
                    {
                        actual_positions[i] += actual_positions[i - 1];
                    }
                }
            }
            else
            {
                if(args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if(args[sample] >= this->heights[num_markers - 1])
                {
                    this->heights[num_markers - 1] = args[sample];
                    sample_cell = num_markers - 1;
                }
                else
                {
                    // find cell k = sample_cell such that heights[k-1] <= sample < heights[k]

                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // update actual position of all markers above sample_cell
                for(std::size_t i = sample_cell; i < num_markers; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // compute desired positions
                {
                    this->desired_positions[0] = this->actual_positions[0];
                    this->desired_positions[num_markers - 1] = sum_of_weights(args);
                    this->desired_positions[1] = (sum_of_weights(args) - this->actual_positions[0]) * probabilities[0]
                                              / 2. + this->actual_positions[0];
                    this->desired_positions[num_markers - 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                            * (probabilities[num_quantiles - 1] + 1.)
                                                            / 2. + this->actual_positions[0];

                    for (std::size_t i = 0; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 2] = (sum_of_weights(args) - this->actual_positions[0])
                                                          * probabilities[i] + this->actual_positions[0];
                    }

                    for (std::size_t i = 1; i < num_quantiles; ++i)
                    {
                        this->desired_positions[2 * i + 1] = (sum_of_weights(args) - this->actual_positions[0])
                                                      * (probabilities[i - 1] + probabilities[i])
                                                      / 2. + this->actual_positions[0];
                    }
                }

                // adjust heights and actual_positions of markers 1 to num_markers - 2 if necessary
                for (std::size_t i = 1; i <= num_markers - 2; ++i)
                {
                    // offset to desired position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if((d >= 1 && dp > 1) || (d <= -1 && dm < -1))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm)*hp + (dp - sign_d) * hm);

                        // try adjusting heights[i] using p-squared formula
                        if(this->heights[i - 1] < h && h < this->heights[i + 1])
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if(d > 0)
                            {
                                this->heights[i] += hp;
                            }
                            if(d < 0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }


        result_type result(dont_care) const
        {
            // for i in [1,probabilities.size()], return heights[i * 2]
            detail::times2_iterator idx_begin = detail::make_times2_iterator(1);
            detail::times2_iterator idx_end = detail::make_times2_iterator(this->probabilities.size() + 1);

            return result_type(
                make_permutation_iterator(this->heights.begin(), idx_begin)
              , make_permutation_iterator(this->heights.begin(), idx_end)
            );
        }


        template<typename Args>
        extended_p_square_quantile_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
        {
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl1, weighted>
                  , tag::weighted_extended_p_square
                  , tag::extended_p_square
                >::type
            extended_p_square_tag;

            extractor<extended_p_square_tag> const some_extended_p_square = {};

            array_type heights(some_extended_p_square(args).size());
            std::copy(some_extended_p_square(args).begin(), some_extended_p_square(args).end(), heights.begin());

            this->probability = args[quantile_probability];

            typename array_type::const_iterator iter_probs = std::lower_bound(this->probabilities.begin(), this->probabilities.end(), this->probability);
            std::size_t dist = std::distance(this->probabilities.begin(), iter_probs);
            typename array_type::const_iterator iter_heights = heights.begin() + dist;

            // If this->probability is not in a valid range return NaN or throw exception
            if (this->probability < *this->probabilities.begin() || this->probability > *(this->probabilities.end() - 1))
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "probability = " << this->probability << " is not in valid range (";
                    msg << *this->probabilities.begin() << ", " << *(this->probabilities.end() - 1) << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }

            }

            if (*iter_probs == this->probability)
            {
                return heights[dist];
            }
            else
            {
                result_type res;

                if (is_same<Impl2, linear>::value)
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // LINEAR INTERPOLATION
                    //
                    float_type p1 = *iter_probs;
                    float_type p0 = *(iter_probs - 1);
                    float_type h1 = *iter_heights;
                    float_type h0 = *(iter_heights - 1);

                    float_type a = numeric::average(h1 - h0, p1 - p0);
                    float_type b = h1 - p1 * a;

                    res = a * this->probability + b;
                }
                else
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // QUADRATIC INTERPOLATION
                    //
                    float_type p0, p1, p2;
                    float_type h0, h1, h2;

                    if ( (dist == 1 || *iter_probs - this->probability <= this->probability - *(iter_probs - 1) ) && dist != this->probabilities.size() - 1 )
                    {
                        p0 = *(iter_probs - 1);
                        p1 = *iter_probs;
                        p2 = *(iter_probs + 1);
                        h0 = *(iter_heights - 1);
                        h1 = *iter_heights;
                        h2 = *(iter_heights + 1);
                    }
                    else
                    {
                        p0 = *(iter_probs - 2);
                        p1 = *(iter_probs - 1);
                        p2 = *iter_probs;
                        h0 = *(iter_heights - 2);
                        h1 = *(iter_heights - 1);
                        h2 = *iter_heights;
                    }

                    float_type hp21 = numeric::average(h2 - h1, p2 - p1);
                    float_type hp10 = numeric::average(h1 - h0, p1 - p0);
                    float_type p21  = numeric::average(p2 * p2 - p1 * p1, p2 - p1);
                    float_type p10  = numeric::average(p1 * p1 - p0 * p0, p1 - p0);

                    float_type a = numeric::average(hp21 - hp10, p21 - p10);
                    float_type b = hp21 - a * p21;
                    float_type c = h2 - a * p2 * p2 - b * p2;

                    res = a * this->probability * this-> probability + b * this->probability + c;
                }

                return res;
            }

        }


        tail_quantile_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if ( n < static_cast<std::size_t>(tail(args).size()))
            {
               // Note that the cached samples of the left are sorted in ascending order,
               // whereas the samples of the right tail are sorted in descending order
               return *(boost::begin(tail(args)) + n - 1);
            }
            else
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }
            }
        }


        count_impl(dont_care)
          : cnt(0)
        {
        }


        void operator ()(dont_care)
        {
            ++this->cnt;
        }


        result_type result(dont_care) const
        {
            return this->cnt;
        }


        weighted_median_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return weighted_p_square_quantile_for_median(args);
        }


        template<typename Args>
        with_density_weighted_median_impl(Args const &args)
          : sum(numeric::average(args[sample | Sample()], (std::size_t)1))
          , is_dirty(true)
        {
        }


        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                std::size_t cnt = count(args);
                range_type histogram = weighted_density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::average(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }


        with_p_square_cumulative_distribution_weighted_median_impl(dont_care)
          : is_dirty(true)
        {
        }


        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                range_type histogram = weighted_p_square_cumulative_distribution(args);
                typename range_type::iterator it = histogram.begin();
                while (it->second < 0.5)
                {
                    ++it;
                }
                float_type over = numeric::average(it->second - 0.5, it->second - (it - 1)->second);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }


        template<typename Args>
        weighted_p_square_cumulative_distribution_impl(Args const &args)
          : num_cells(args[p_square_cumulative_distribution_num_cells])
          , heights(num_cells + 1)
          , actual_positions(num_cells + 1)
          , desired_positions(num_cells + 1)
          , histogram(num_cells + 1)
          , is_dirty(true)
        {
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            this->is_dirty = true;

            std::size_t cnt = count(args);
            std::size_t sample_cell = 1; // k
            std::size_t b = this->num_cells;

            // accumulate num_cells + 1 first samples
            if (cnt <= b + 1)
            {
                this->heights[cnt - 1] = args[sample];
                this->actual_positions[cnt - 1] = args[weight];

                // complete the initialization of heights by sorting
                if (cnt == b + 1)
                {
                    //std::sort(this->heights.begin(), this->heights.end());

                    // TODO: we need to sort the initial samples (in heights) in ascending order and
                    // sort their weights (in actual_positions) the same way. The following lines do
                    // it, but there must be a better and more efficient way of doing this.
                    typename array_type::iterator it_begin, it_end, it_min;

                    it_begin = this->heights.begin();
                    it_end   = this->heights.end();

                    std::size_t pos = 0;

                    while (it_begin != it_end)
                    {
                        it_min = std::min_element(it_begin, it_end);
                        std::size_t d = std::distance(it_begin, it_min);
                        std::swap(*it_begin, *it_min);
                        std::swap(this->actual_positions[pos], this->actual_positions[pos + d]);
                        ++it_begin;
                        ++pos;
                    }

                    // calculate correct initial actual positions
                    for (std::size_t i = 1; i < b; ++i)
                    {
                        this->actual_positions[i] += this->actual_positions[i - 1];
                    }
                }
            }
            else
            {
                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    this->actual_positions[0] = args[weight];
                    sample_cell = 1;
                }
                else if (this->heights[b] <= args[sample])
                {
                    this->heights[b] = args[sample];
                    sample_cell = b;
                }
                else
                {
                    typename array_type::iterator it;
                    it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // increment positions of markers above sample_cell
                for (std::size_t i = sample_cell; i < b + 1; ++i)
                {
                    this->actual_positions[i] += args[weight];
                }

                // determine desired marker positions
                for (std::size_t i = 1; i < b + 1; ++i)
                {
                    this->desired_positions[i] = this->actual_positions[0]
                                               + numeric::average((i-1) * (sum_of_weights(args) - this->actual_positions[0]), b);
                }

                // adjust heights of markers 2 to num_cells if necessary
                for (std::size_t i = 1; i < b; ++i)
                {
                    // offset to desire position
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if ( ( d >= 1. && dp > 1. ) || ( d <= -1. && dm < -1. ) )
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ( (sign_d - dm) * hp + (dp - sign_d) * hm );

                        if ( this->heights[i - 1] < h && h < this->heights[i + 1] )
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if (d>0)
                            {
                                this->heights[i] += hp;
                            }
                            if (d<0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                // creates a vector of std::pair where each pair i holds
                // the values heights[i] (x-axis of histogram) and
                // actual_positions[i] / sum_of_weights (y-axis of histogram)

                for (std::size_t i = 0; i < this->histogram.size(); ++i)
                {
                    this->histogram[i] = std::make_pair(this->heights[i], numeric::average(this->actual_positions[i], sum_of_weights(args)));
                }
            }

            return make_iterator_range(this->histogram);
        }


        weighted_tail_quantile_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
                }
                else
                {
                    if (std::numeric_limits<result_type>::has_quiet_NaN)
                    {
                        return std::numeric_limits<result_type>::quiet_NaN();
                    }
                    else
                    {
                        std::ostringstream msg;
                        msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                        boost::throw_exception(std::runtime_error(msg.str()));
                        return Sample(0);
                    }
                }
            }

            // Note that the cached samples of the left are sorted in ascending order,
            // whereas the samples of the right tail are sorted in descending order
            return *(boost::begin(tail(args)) + n - 1);
        }


        tail_variate_means_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            std::size_t num_variates = tail_variate(args).begin()->size();

            this->tail_means_.clear();
            this->tail_means_.resize(num_variates, Sample(0));

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if (n < static_cast<std::size_t>(tail(args).size()))
            {
                this->tail_means_ = std::accumulate(
                    tail_variate(args).begin()
                  , tail_variate(args).begin() + n
                  , this->tail_means_
                  , numeric::plus
                );

                float_type factor = n * ( (is_same<Impl, relative>::value) ? non_coherent_tail_mean(args) : 1. );

                std::transform(
                    this->tail_means_.begin()
                  , this->tail_means_.end()
                  , this->tail_means_.begin()
                  , std::bind2nd(std::divides<float_type>(), factor)
                );
            }
            else
            {
                if (std::numeric_limits<float_type>::has_quiet_NaN)
                {
                    std::fill(
                        this->tail_means_.begin()
                      , this->tail_means_.end()
                      , std::numeric_limits<float_type>::quiet_NaN()
                    );
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                }
            }
            return make_iterator_range(this->tail_means_);
        }


        template<typename Args>
        tail_variate_impl(Args const &args)
          : variates(args[tag::tail<LeftRight>::cache_size], args[parameter::keyword<VariateTag>::get() | VariateType()])
        {
        }


        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            this->variates[index] = args[parameter::keyword<VariateTag>::get()];
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            // getting the order result causes the indices vector to be sorted.
            extractor<tag::tail<LeftRight> > const some_tail = {};
            return this->do_result(some_tail(args));
        }

        template<typename TailRng>
        result_type do_result(TailRng const &rng) const
        {
            return detail::make_tail_range(
                this->variates.begin()
              , rng.end().base().base()   // the index iterator
              , rng.begin().base().base() // (begin and end reversed because these are reverse iterators)
            );
        }


        template<typename Args>
        p_square_quantile_impl(Args const &args)
          : p(is_same<Impl, for_median>::value ? 0.5 : args[quantile_probability | 0.5])
          , heights()
          , actual_positions()
          , desired_positions()
          , positions_increments()
        {
            for(std::size_t i = 0; i < 5; ++i)
            {
                this->actual_positions[i] = i + 1;
            }

            this->desired_positions[0] = 1.;
            this->desired_positions[1] = 1. + 2. * this->p;
            this->desired_positions[2] = 1. + 4. * this->p;
            this->desired_positions[3] = 3. + 2. * this->p;
            this->desired_positions[4] = 5.;

            this->positions_increments[0] = 0.;
            this->positions_increments[1] = this->p / 2.;
            this->positions_increments[2] = this->p;
            this->positions_increments[3] = (1. + this->p) / 2.;
            this->positions_increments[4] = 1.;
        }


        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            // accumulate 5 first samples
            if(cnt <= 5)
            {
                this->heights[cnt - 1] = args[sample];

                // complete the initialization of heights by sorting
                if(cnt == 5)
                {
                    std::sort(this->heights.begin(), this->heights.end());
                }
            }
            else
            {
                std::size_t sample_cell = 1; // k

                // find cell k such that heights[k-1] <= args[sample] < heights[k] and adjust extreme values
                if (args[sample] < this->heights[0])
                {
                    this->heights[0] = args[sample];
                    sample_cell = 1;
                }
                else if (this->heights[4] <= args[sample])
                {
                    this->heights[4] = args[sample];
                    sample_cell = 4;
                }
                else
                {
                    typedef typename array_type::iterator iterator;
                    iterator it = std::upper_bound(
                        this->heights.begin()
                      , this->heights.end()
                      , args[sample]
                    );

                    sample_cell = std::distance(this->heights.begin(), it);
                }

                // update positions of markers above sample_cell
                for(std::size_t i = sample_cell; i < 5; ++i)
                {
                    ++this->actual_positions[i];
                }

                // update desired positions of all markers
                for(std::size_t i = 0; i < 5; ++i)
                {
                    this->desired_positions[i] += this->positions_increments[i];
                }

                // adjust heights and actual positions of markers 1 to 3 if necessary
                for(std::size_t i = 1; i <= 3; ++i)
                {
                    // offset to desired positions
                    float_type d = this->desired_positions[i] - this->actual_positions[i];

                    // offset to next position
                    float_type dp = this->actual_positions[i + 1] - this->actual_positions[i];

                    // offset to previous position
                    float_type dm = this->actual_positions[i - 1] - this->actual_positions[i];

                    // height ds
                    float_type hp = (this->heights[i + 1] - this->heights[i]) / dp;
                    float_type hm = (this->heights[i - 1] - this->heights[i]) / dm;

                    if((d >= 1. && dp > 1.) || (d <= -1. && dm < -1.))
                    {
                        short sign_d = static_cast<short>(d / std::abs(d));

                        // try adjusting heights[i] using p-squared formula
                        float_type h = this->heights[i] + sign_d / (dp - dm) * ((sign_d - dm) * hp
                                     + (dp - sign_d) * hm);

                        if(this->heights[i - 1] < h && h < this->heights[i + 1])
                        {
                            this->heights[i] = h;
                        }
                        else
                        {
                            // use linear formula
                            if(d > 0)
                            {
                                this->heights[i] += hp;
                            }
                            if(d < 0)
                            {
                                this->heights[i] -= hm;
                            }
                        }
                        this->actual_positions[i] += sign_d;
                    }
                }
            }
        }


        result_type result(dont_care) const
        {
            return this->heights[2];
        }


        weighted_skewness_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::average(
                        accumulators::weighted_moment<3>(args)
                        - 3. * accumulators::weighted_moment<2>(args) * weighted_mean(args)
                        + 2. * weighted_mean(args) * weighted_mean(args) * weighted_mean(args)
                      , ( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                      * std::sqrt( accumulators::weighted_moment<2>(args) - weighted_mean(args) * weighted_mean(args) )
                   );
        }


        median_impl(dont_care) {}


        template<typename Args>
        result_type result(Args const &args) const
        {
            return p_square_quantile_for_median(args);
        }


        template<typename Args>
        with_density_median_impl(Args const &args)
          : sum(numeric::average(args[sample | Sample()], (std::size_t)1))
          , is_dirty(true)
        {
        }


        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }



        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                std::size_t cnt = count(args);
                range_type histogram = density(args);
                typename range_type::iterator it = histogram.begin();
                while (this->sum < 0.5 * cnt)
                {
                    this->sum += it->second * cnt;
                    ++it;
                }
                --it;
                float_type over = numeric::average(this->sum - 0.5 * cnt, it->second * cnt);
                this->median = it->first * over + (it + 1)->first * (1. - over);
            }

            return this->median;
        }


        with_p_square_cumulative_distribution_median_impl(dont_care)
          : is_dirty(true)
        {
        }


        void operator ()(dont_care)
        {
            this->is_dirty = true;
        }


        template<typename Args>
        result_type result(Args const &args) const
        {
            if (this->is_dirty)
            {
                this->is_dirty = false;

                range_type histogram = p_square_cumulative_distribution(args);
                typename range_type::iterator it = histogram.begin();
                while (it->second < 0.5)
                {
                    ++it;
                }
                float_type over = numeric::average(it->second - 0.5, it->second - (it - 1)->second);
                this->median = it->first * over + (it + 1)->first * ( 1. - over );
            }

            return this->median;
        }
