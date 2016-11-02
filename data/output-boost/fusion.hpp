

        iterator_range(First const& in_first, Last const& in_last)
            : first(convert_iterator<First>::call(in_first))
            , last(convert_iterator<Last>::call(in_last)) {}


                static type
                call(Seq& s)
                {
                    return * fusion::advance<N>(s.first);
                }


                static type
                call(Sequence& s)
                {
                    return s.first;
                }


                static type call(Sequence & seq)
                {
                    return fusion::segments(impl::call(seq.first, seq.last));
                }


                static type
                call(Sequence& s)
                {
                    return s.last;
                }


        static type call(Stack const& stack)
        {
            //return segment_sequence(
            //  push_front(
            //    iterator_range(next(begin(car(cdr(stack_begin)))), end(segments(front(car(stack_begin))))),
            //    make_segment_sequence_front(cdr(stack_begin))));
            return type(
                fusion::push_front(
                    rest_type(fusion::next(stack.cdr.car.first), fusion::end(fusion::segments(*stack.car.first)))
                  , recurse::call(stack.cdr)));
        }


        static type call(Stack const& stack)
        {
            // return iterator_range(begin(car(cdr(stack_begin))), end(front(car(stack_begin))));
            return type(stack.cdr.car.first, fusion::end(*stack.car.first));
        }


        static type call(Stack const &stack)
        {
            return stack.cdr;
        }


        static type call(Stack const& stack)
        {
            //  return segment_sequence(
            //    push_back(
            //      iterator_range(begin(segments(front(car(stack_end)))), begin(car(cdr(stack_end)))),
            //      make_segment_sequence_back(cdr(stack_end))));
            return type(
                fusion::push_back(
                    rest_type(fusion::begin(fusion::segments(*stack.car.first)), stack.cdr.car.first)
                  , recurse::call(stack.cdr)));
        }


        static type call(Stack const& stack)
        {
            // return iterator_range(begin(front(car(stack_end))), begin(car(cdr(stack_end))));
            return type(fusion::begin(*stack.car.first), stack.cdr.car.first);
        }


        static type call(Stack const& stack)
        {
            return stack.cdr;
        }


        static type call(StackBegin stack_begin, StackEnd stack_end)
        {
            return impl::call(stack_begin.cdr, stack_end.cdr);
        }


        static type call(StackBegin stack_begin, StackEnd stack_end)
        {
            //return segment_sequence(
            //  single_view(
            //    iterator_range(begin(car(stack_begin)), begin(car(stack_end)))));
            return type(segment_type(range_type(stack_begin.car.first, stack_end.car.first)));
        }


        static type call(Begin const& begin, End const& end)
        {
            return impl::call(
                reverse_begin_cons::call(begin.context)
              , reverse_end_cons::call(end.context));
        }


        repetitive_view(Sequence& in_seq)
            : seq(in_seq) {}


                static type call(Iterator const& i)
                {
                    return *i.pos;
                }


                static type call(View const& v)
                {
                    return type(v.seq);
                }


                static type call(View const& v)
                {
                    return type(v.seq,end(v.seq));
                }


                static type call(Iterator const& i)
                {
                    return type(i.seq);
                }


                static type call(Iterator const& i)
                {
                    return type(i);
                }

            template <typename T>
            typename result<addref(T)>::type
            operator()(T&& x) const
            {
                return x;
            }


        explicit nview(Sequence& val)
          : seq(sequence_type(transform_view_type(val, transform_type()))) 
        {}


        explicit nview_iterator(Sequence& in_seq)
          : seq(in_seq) {}


                static type call(Iterator const& i)
                {
                    return at<index>(i.seq.seq);
                }


                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }


                static type 
                call(Sequence& seq)
                {
                    return fusion::at<index>(seq.seq);
                }


                static type call(Sequence& s)
                {
                    return type(s);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }


                static type call(Sequence& s)
                {
                    return type(s);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }


        template<typename InitSeq>
        zip_view_iterator(
            const InitSeq& iterator_seq)
            : iterators_(iterator_seq)
        {}


        zip_view(
            const Sequences& seqs)
            : sequences_(seqs)
        {};


            template<typename It>
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
            }


                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }

                static typename detail::zip_view_iterator_distance<It1, It2>::type
                call(It1 const& /*it1*/, It2 const& /*it2*/)
                {
                    return typename detail::zip_view_iterator_distance<It1, It2>::type();
                }


            template<typename Seq>
            typename result<poly_at(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::at<N>(seq);
            }


            template<typename Seq>
            typename result<poly_at(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::at<N>(seq);
            }


                static type
                call(Seq& seq)
                {
                    return type(
                        fusion::transform(seq.sequences_, detail::poly_at<N>()));
                }


            template<typename Seq>
            typename result<poly_begin(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::begin(seq);
            }


            template<typename Seq>
            typename result<poly_begin(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::begin(seq);
            }


                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::poly_begin()));
                }


            template<typename It>
            typename result<poly_advance(It)>::type
            operator()(const It& it) const
            {
                return fusion::advance<N>(it);
            }


                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_advance<N>()));
                }


            template<typename Seq>
            typename result<endpoints(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::advance<M>(fusion::begin(seq));
            }


            template<typename Seq>
            typename result<endpoints(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::advance<M>(fusion::begin(seq));
            }


                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::endpoints<typename Sequence::size>()));
                }


            template<typename It>
            typename result<poly_prior(It)>::type
            operator()(const It& it) const
            {
                return fusion::prior(it);
            }


                static type
                call(Iterator const& it)

                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_prior()));
                }


            template<typename It>
            typename result<poly_next(It)>::type
            operator()(const It& it) const
            {
                return fusion::next(it);
            }


                static type
                call(Iterator const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_next()));
                }


        filter_view(Sequence& in_seq)
            : seq(in_seq)
        {}


        first_type first() const { return fusion::begin(seq); }

        last_type last() const { return fusion::end(seq); }


        filter_iterator(First const& in_first)
            : first(filter::iter_call(first_converter::call(in_first))) {}


                static type
                call(Sequence& s)
                {
                    return type(s.first());
                }


                static type
                call(Sequence& s)
                {
                    return type(s.last());
                }


                static type
                call(Iterator const& i)
                {
                    return type(filter::iter_call(i.first));
                }


        joint_view_iterator(First const& in_first, Concat const& in_concat)
            : first(first_converter::call(in_first))
            , concat(concat_converter::call(in_concat))
        {}


        joint_view(Sequence1& in_seq1, Sequence2& in_seq2)
            : seq1(in_seq1)
            , seq2(in_seq2)
        {}


        first_type first() const { return fusion::begin(seq1); }

        concat_type concat() const { return fusion::begin(seq2); }

        concat_last_type concat_last() const { return fusion::end(seq2); }


                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }


                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }


                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }


        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}


        first_type first() const { return fusion::begin(seq); }

        last_type last() const { return fusion::end(seq); }


        reverse_view_iterator(First const& in_first)
            : first(converter::call(in_first)) {}

    
                static type
                call(Iterator const& i)
                {
                    return *fusion::prior(i.first);
                }


                static type
                call(First const& first, Last const& last)
                {
                    return boost::fusion::distance(last.first, first.first);
                }

    
                static type
                call(Sequence const& s)
                {
                    return type(s.last());
                }


                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }

    
                static type
                call(Sequence const& s)
                {
                    return type(s.first());
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


        transform_view(Sequence1& in_seq1, Sequence2& in_seq2, F const& binop)
            : f(binop)
            , seq1(in_seq1)
            , seq2(in_seq2)
        {}


        first1_type first1() const { return fusion::begin(seq1); }

        first2_type first2() const { return fusion::begin(seq2); }

        last1_type last1() const { return fusion::end(seq1); }

        last2_type last2() const { return fusion::end(seq2); }


        transform_view_iterator(First const& in_first, F const& in_f)
            : first(converter::call(in_first)), f(in_f) {}


        transform_view_iterator2(First1 const& in_first1, First2 const& in_first2, F const& in_f)
            : first1(converter1::call(in_first1)), first2(converter2::call(in_first2)), f(in_f) {}


                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }


                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }


                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq));
                }


                static type call(Seq& seq)
                {
                    return seq.f(boost::fusion::at<N>(seq.seq1), boost::fusion::at<N>(seq.seq2));
                }


                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<Dist>(i.first), i.f);
                }


                static type
                call(Iterator const& i)
                {
                    return type(
                        boost::fusion::advance<Dist>(i.first1)
                      , boost::fusion::advance<Dist>(i.first2), i.f);
                }


                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first), i.f);
                }


                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first1), fusion::prior(i.first2), i.f);
                }


                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first), i.f);
                }


                static type
                call(Iterator const& i)
                {
                    return type(fusion::next(i.first1), fusion::next(i.first2), i.f);
                }


        single_view()
            : val() {}


        explicit single_view_iterator(single_view_type& in_view)
            : view(in_view) {}

    
                static type
                call(Iterator const& i)
                {
                    return i.view.val;
                }


                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }


                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }

    
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }

    
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }


                static type
                call(Iterator const& i)
                {
                    BOOST_STATIC_ASSERT((type::position::value < 2));
                    return type(i.view);
                }


        nil() {}


        template <typename Iterator>
        void assign_from_iter(Iterator const& /*iter*/)
        {
        }


        cons()
            : car(), cdr() {}

        
        template <typename Car2, typename Cdr2>
        cons(cons<Car2, Cdr2> const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}


        cons(cons const& rhs)
            : car(rhs.car), cdr(rhs.cdr) {}


        template <typename Car2, typename Cdr2>
        cons& operator=(cons<Car2, Cdr2> const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }


        cons& operator=(cons const& rhs)
        {
            car = rhs.car;
            cdr = rhs.cdr;
            return *this;
        }


            static type
            call(Sequence& seq)
            {
                return build_cons::call(fusion::begin(seq), fusion::end(seq));
            }


    template <typename Sequence>
    inline typename result_of::as_list<Sequence>::type
    as_list(Sequence& seq)
    {
        return result_of::as_list<Sequence>::call(seq);
    }


    template <typename Sequence>
    inline typename result_of::as_list<Sequence const>::type
    as_list(Sequence const& seq)
    {
        return result_of::as_list<Sequence const>::call(seq);
    }


        explicit cons_iterator(cons_type& in_cons)
            : cons(in_cons) {}

        nil_iterator() {}

        explicit nil_iterator(nil const&) {}

        cons_iterator() {}

        explicit cons_iterator(nil const&) {}

        cons_iterator() {}

        explicit cons_iterator(nil const&) {}


                static type
                call(Sequence& seq)
                {
                    return build_cons::call(fusion::begin(seq), fusion::end(seq));
                }

        
        static nil
        call(First const&, Last const&)
        {
            return nil();
        }

    
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }


                template <typename Cons, int N2>
                static type
                call(Cons& s, mpl::int_<N2>)
                {
                    return call(s.cdr, mpl::int_<N2-1>());
                }

    
                static type
                call(Sequence& t)
                {
                    return type(t);
                }

    
                static type
                call(Sequence&)
                {
                    return type();
                }

    
                static type
                call(Iterator const& i)
                {
                    return type(i.cons.cdr);
                }

        list()
            : inherited_type() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename T>
        list&
        operator=(T const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        list()
            : inherited_type() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename T>
        list&
        operator=(T const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

    static type
    call(typename detail::call_param<T0 >::type _0)
    {
        return type(_0 
            );
    }

    static type
    call(typename detail::call_param<T0 >::type _0)
    {
        return type(_0 
            );
    }

    static type
    call(typename detail::call_param<T0 >::type _0)
    {
        return type(_0 
            );
    }

        list()
            : inherited_type() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename T>
        list&
        operator=(T const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

    static type
    call(typename detail::call_param<T0 >::type _0)
    {
        return type(_0 
            );
    }

    static type
    call(typename detail::call_param<T0 >::type _0)
    {
        return type(_0 
            );
    }

        list()
            : inherited_type() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename T>
        list&
        operator=(T const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        list()
            : inherited_type() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        list(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        list&
        operator=(list<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }

        template <typename T>
        list&
        operator=(T const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }


    template<typename Key, typename T>
    typename result_of::pair_tie<Key, T const>::type
    pair_tie(T const& t)
    {
        return typename result_of::pair_tie<Key, T const>::type(t);
    }

            template<typename T>
            swallow_assign const&
            operator=(const T&) const
            {
                return *this;
            }


    template <typename Sequence>
    inline typename result_of::as_set<Sequence>::type
    as_set(Sequence& seq)
    {
        typedef typename result_of::as_set<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }


    template <typename Sequence>
    inline typename result_of::as_set<Sequence const>::type
    as_set(Sequence const& seq)
    {
        typedef typename result_of::as_set<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }


                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }


        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return set<>();
        }

        set()
            : data() {}

        template <typename Sequence>
        set(Sequence const& rhs)
            : data(rhs) {}

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        set()
            : data() {}

        template <typename Sequence>
        set(Sequence const& rhs)
            : data(rhs) {}

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        set()
            : data() {}

        template <typename Sequence>
        set(Sequence const& rhs)
            : data(rhs) {}

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        set()
            : data() {}

        template <typename Sequence>
        set(Sequence const& rhs)
            : data(rhs) {}

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        set()
            : data() {}

        template <typename Sequence>
        set(Sequence const& rhs)
            : data(rhs) {}

        template <typename T>
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }


    template <typename Sequence>
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef typename result_of::as_map<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }


    template <typename Sequence>
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef typename result_of::as_map<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }


                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }

    
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }

    
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }


        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return map<>();
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        map()
            : data() {}

        template <typename Sequence>
        map(Sequence const& rhs)
            : data(rhs) {}

    explicit
    map(T0 const& _0)
        : data(_0) {}

    map(T0 const& _0 , T1 const& _1)
        : data(_0 , _1) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2)
        : data(_0 , _1 , _2) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3)
        : data(_0 , _1 , _2 , _3) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4)
        : data(_0 , _1 , _2 , _3 , _4) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5)
        : data(_0 , _1 , _2 , _3 , _4 , _5) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9) {}

        template <typename T>
        map&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        map()
            : data() {}

        template <typename Sequence>
        map(Sequence const& rhs)
            : data(rhs) {}

    explicit
    map(T0 const& _0)
        : data(_0) {}

    map(T0 const& _0 , T1 const& _1)
        : data(_0 , _1) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2)
        : data(_0 , _1 , _2) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3)
        : data(_0 , _1 , _2 , _3) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4)
        : data(_0 , _1 , _2 , _3 , _4) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5)
        : data(_0 , _1 , _2 , _3 , _4 , _5) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39) {}

        template <typename T>
        map&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        map()
            : data() {}

        template <typename Sequence>
        map(Sequence const& rhs)
            : data(rhs) {}

    explicit
    map(T0 const& _0)
        : data(_0) {}

    map(T0 const& _0 , T1 const& _1)
        : data(_0 , _1) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2)
        : data(_0 , _1 , _2) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3)
        : data(_0 , _1 , _2 , _3) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4)
        : data(_0 , _1 , _2 , _3 , _4) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5)
        : data(_0 , _1 , _2 , _3 , _4 , _5) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29) {}

        template <typename T>
        map&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        map()
            : data() {}

        template <typename Sequence>
        map(Sequence const& rhs)
            : data(rhs) {}

    explicit
    map(T0 const& _0)
        : data(_0) {}

    map(T0 const& _0 , T1 const& _1)
        : data(_0 , _1) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2)
        : data(_0 , _1 , _2) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3)
        : data(_0 , _1 , _2 , _3) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4)
        : data(_0 , _1 , _2 , _3 , _4) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5)
        : data(_0 , _1 , _2 , _3 , _4 , _5) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44 , T45 const& _45)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44 , _45) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44 , T45 const& _45 , T46 const& _46)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44 , _45 , _46) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44 , T45 const& _45 , T46 const& _46 , T47 const& _47)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44 , _45 , _46 , _47) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44 , T45 const& _45 , T46 const& _46 , T47 const& _47 , T48 const& _48)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44 , _45 , _46 , _47 , _48) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19 , T20 const& _20 , T21 const& _21 , T22 const& _22 , T23 const& _23 , T24 const& _24 , T25 const& _25 , T26 const& _26 , T27 const& _27 , T28 const& _28 , T29 const& _29 , T30 const& _30 , T31 const& _31 , T32 const& _32 , T33 const& _33 , T34 const& _34 , T35 const& _35 , T36 const& _36 , T37 const& _37 , T38 const& _38 , T39 const& _39 , T40 const& _40 , T41 const& _41 , T42 const& _42 , T43 const& _43 , T44 const& _44 , T45 const& _45 , T46 const& _46 , T47 const& _47 , T48 const& _48 , T49 const& _49)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19 , _20 , _21 , _22 , _23 , _24 , _25 , _26 , _27 , _28 , _29 , _30 , _31 , _32 , _33 , _34 , _35 , _36 , _37 , _38 , _39 , _40 , _41 , _42 , _43 , _44 , _45 , _46 , _47 , _48 , _49) {}

        template <typename T>
        map&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        map()
            : data() {}

        template <typename Sequence>
        map(Sequence const& rhs)
            : data(rhs) {}

    explicit
    map(T0 const& _0)
        : data(_0) {}

    map(T0 const& _0 , T1 const& _1)
        : data(_0 , _1) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2)
        : data(_0 , _1 , _2) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3)
        : data(_0 , _1 , _2 , _3) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4)
        : data(_0 , _1 , _2 , _3 , _4) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5)
        : data(_0 , _1 , _2 , _3 , _4 , _5) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18) {}

    map(T0 const& _0 , T1 const& _1 , T2 const& _2 , T3 const& _3 , T4 const& _4 , T5 const& _5 , T6 const& _6 , T7 const& _7 , T8 const& _8 , T9 const& _9 , T10 const& _10 , T11 const& _11 , T12 const& _12 , T13 const& _13 , T14 const& _14 , T15 const& _15 , T16 const& _16 , T17 const& _17 , T18 const& _18 , T19 const& _19)
        : data(_0 , _1 , _2 , _3 , _4 , _5 , _6 , _7 , _8 , _9 , _10 , _11 , _12 , _13 , _14 , _15 , _16 , _17 , _18 , _19) {}

        template <typename T>
        map&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        storage_type& get_data() { return data; }


        template <typename Sequence>
        deque(Sequence const&,
            typename enable_if<
                mpl::and_<
                    traits::is_sequence<Sequence>
                  , result_of::empty<Sequence>>>::type* /*dummy*/ = 0)
        {}


        deque() {}


        deque()
        {}


        template <typename ...Elements>
        deque(deque<Elements...> const& seq)
          : base(seq)
        {}


        template <typename ...Elements>
        deque(deque<Elements...>& seq)
          : base(seq)
        {}

        template <typename ...Elements>
        deque(deque<Elements...>&& seq)
          : base(std::forward<deque<Elements...>>(seq))
        {}


        deque(deque const& seq)
          : base(seq)
        {}

        deque(deque&& seq)
          : base(std::forward<deque>(seq))
        {}


        explicit deque(Head const& head, Tail const&... tail)
          : base(detail::deque_keyed_values<Head, Tail...>::construct(head, tail...))
        {}


        template <typename Head_, typename ...Tail_>
        explicit deque(Head_ const& head, Tail_ const&... tail)
          : base(detail::deque_keyed_values<Head_, Tail_...>::construct(head, tail...))
        {}

        template <typename Head_, typename ...Tail_>
        explicit deque(Head_&& head, Tail_&&... tail)
          : base(detail::deque_keyed_values<Head, Tail...>
                ::forward_(std::forward<Head_>(head), std::forward<Tail_>(tail)...))
        {}


        template <typename ...Elements>
        deque& operator=(deque<Elements...> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }


        template <typename T>
        deque& operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque& operator=(T&& rhs)
        {
            base::operator=(std::forward<T>(rhs));
            return *this;
        }


        template <typename Arg>
        back_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

        template <typename Arg>
        back_extended_deque(Deque const& deque, Arg&& val)
          : base(std::forward<Arg>(val), deque)
        {}


        deque_iterator(Seq& seq)
            : seq_(seq)
        {}


            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }


            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }


            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }


    template <typename Sequence>
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }


    template <typename Sequence>
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }


        template <typename Arg>
        front_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

        template <typename Arg>
        front_extended_deque(Deque const& deque, Arg&& val)
          : base(std::forward<Arg>(val), deque)
        {}


                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }


        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return deque<>();
        }


                static type call(Sequence& seq)
                {
                    return seq.get(adjusted_index());
                }


                static type call(Sequence& seq)
                {
                    return type(seq);
                }


                static type call(Sequence& seq)
                {
                    return type(seq);
                }


        template<typename It>
        static nil_keyed_element
        from_iterator(It const&)
        {
            return nil_keyed_element();
        }


        template <typename It>
        static keyed_element
        from_iterator(It const& it)
        {
            return keyed_element(
                *it, base::from_iterator(fusion::next(it)));
        }


        keyed_element(keyed_element const& rhs)
          : Rest(rhs.get_base()), value_(rhs.value_)
        {}

        keyed_element(keyed_element&& rhs)
          : Rest(std::forward<Rest>(rhs.forward_base()))
          , value_(std::forward<Value>(rhs.value_))
        {}


        template <typename U, typename Rst>
        keyed_element(keyed_element<Key, U, Rst> const& rhs)
          : Rest(rhs.get_base()), value_(rhs.value_)
        {}


        Rest& get_base()
        {
            return *this;
        }


        Rest const& get_base() const
        {
            return *this;
        }

        Rest&& forward_base()
        {
            return std::forward<Rest>(*static_cast<Rest*>(this));
        }


        static type construct(
          typename detail::call_param<Head>::type head
        , typename detail::call_param<Tail>::type... tail)
        {
            return type(
                head
              , deque_keyed_values_impl<next_index, Tail...>::construct(tail...)
            );
        }


        template <typename Head_, typename ...Tail_>
        static type forward_(Head_&& head, Tail_&&... tail)
        {
            return type(
                std::forward<Head_>(head)
              , deque_keyed_values_impl<next_index, Tail_...>::
                  forward_(std::forward<Tail_>(tail)...)
            );
        }

        static type construct() { return type(); }

        static type forward_() { return type(); }

        static type call(typename add_reference<typename add_const<T0 >::type>::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::call());
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

deque(typename add_reference<typename add_const<T0 >::type>::type t0 , typename add_reference<typename add_const<T1 >::type>::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::call(t0 , t1))
{}

        deque()
            {}

        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
            deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& seq)
            : base(seq)
            {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        deque&
        operator=(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

deque(typename add_reference<typename add_const<T0 >::type>::type t0 , typename add_reference<typename add_const<T1 >::type>::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::call(t0 , t1))
{}

        deque()
            {}

        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
            deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& seq)
            : base(seq)
            {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        deque&
        operator=(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        static type call(typename add_reference<typename add_const<T0 >::type>::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::call());
        }

deque(typename add_reference<typename add_const<T0 >::type>::type t0 , typename add_reference<typename add_const<T1 >::type>::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::call(t0 , t1))
{}

        deque()
            {}

        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
            deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& seq)
            : base(seq)
            {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        deque&
        operator=(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

deque(typename add_reference<typename add_const<T0 >::type>::type t0 , typename add_reference<typename add_const<T1 >::type>::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::call(t0 , t1))
{}

        deque()
            {}

        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
            deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& seq)
            : base(seq)
            {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        deque&
        operator=(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        static type call(typename add_reference<typename add_const<T0 >::type>::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::call());
        }

        static type call(typename add_reference<typename add_const<T0 >::type>::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::call());
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

deque(typename add_reference<typename add_const<T0 >::type>::type t0 , typename add_reference<typename add_const<T1 >::type>::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::call(t0 , t1))
{}

        deque()
            {}

        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
            deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& seq)
            : base(seq)
            {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        deque&
        operator=(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        template <typename T>
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }

        static type call(typename add_reference<typename add_const<T0 >::type>::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::call());
        }


        vector0() {}


        template<typename Sequence>
        vector0(Sequence const& /*seq*/)
        {}


    template <typename Sequence>
    inline typename result_of::as_vector<Sequence>::type
    as_vector(Sequence& seq)
    {
        typedef typename result_of::as_vector<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }


    template <typename Sequence>
    inline typename result_of::as_vector<Sequence const>::type
    as_vector(Sequence const& seq)
    {
        typedef typename result_of::as_vector<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }


        vector_iterator(Vector& in_vec)
            : vec(in_vec) {}


                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }


                static type
                call(Iterator const& i)
                {
                    return i.vec.at_impl(index());
                }


        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return vector0<>();
        }

    
                static type
                call(Sequence& v)
                {
                    return v.at_impl(N());
                }

    
                static type
                call(Sequence const& v)
                {
                    return v.at_impl(N());
                }

    
                static type
                call(Sequence& v)
                {
                    return type(v);
                }

    
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }

    
                static type
                call(Sequence& v)
                {
                    return type(v);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }


                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }

        vector_data41()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() {}

        vector_data41(
            vector_data41 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) {}

        vector_data41&
        operator=(vector_data41 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40;
            return *this;
        }

        template <typename Sequence>
        static vector_data41
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39);
            return vector_data41(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40);
        }

        template <typename Sequence>
        static vector_data41
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39);
            return vector_data41(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40);
        }

        vector41() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40>
        vector41(
            vector41<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40) {}

        template <typename Sequence>
        vector41(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector41(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40>
        vector41&
        operator=(vector41<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40;
            return *this;
        }

        vector_data42()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() {}

        vector_data42(
            vector_data42 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) {}

        vector_data42&
        operator=(vector_data42 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41;
            return *this;
        }

        template <typename Sequence>
        static vector_data42
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40);
            return vector_data42(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41);
        }

        template <typename Sequence>
        static vector_data42
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40);
            return vector_data42(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41);
        }

        vector42() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41>
        vector42(
            vector42<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41) {}

        template <typename Sequence>
        vector42(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector42(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41>
        vector42&
        operator=(vector42<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41;
            return *this;
        }

        vector_data43()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() {}

        vector_data43(
            vector_data43 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) {}

        vector_data43&
        operator=(vector_data43 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42;
            return *this;
        }

        template <typename Sequence>
        static vector_data43
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41);
            return vector_data43(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42);
        }

        template <typename Sequence>
        static vector_data43
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41);
            return vector_data43(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42);
        }

        vector43() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42>
        vector43(
            vector43<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42) {}

        template <typename Sequence>
        vector43(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector43(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42>
        vector43&
        operator=(vector43<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42;
            return *this;
        }

        vector_data44()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() {}

        vector_data44(
            vector_data44 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) {}

        vector_data44&
        operator=(vector_data44 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43;
            return *this;
        }

        template <typename Sequence>
        static vector_data44
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42);
            return vector_data44(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43);
        }

        template <typename Sequence>
        static vector_data44
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42);
            return vector_data44(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43);
        }

        vector44() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43>
        vector44(
            vector44<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43) {}

        template <typename Sequence>
        vector44(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector44(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43>
        vector44&
        operator=(vector44<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43;
            return *this;
        }

        vector_data45()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() {}

        vector_data45(
            vector_data45 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) {}

        vector_data45&
        operator=(vector_data45 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44;
            return *this;
        }

        template <typename Sequence>
        static vector_data45
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43);
            return vector_data45(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44);
        }

        template <typename Sequence>
        static vector_data45
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43);
            return vector_data45(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44);
        }

        vector45() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44>
        vector45(
            vector45<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44) {}

        template <typename Sequence>
        vector45(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector45(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44>
        vector45&
        operator=(vector45<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44;
            return *this;
        }

        vector_data46()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() , m45() {}

        vector_data46(
            vector_data46 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) , m45(other.m45) {}

        vector_data46&
        operator=(vector_data46 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45;
            return *this;
        }

        template <typename Sequence>
        static vector_data46
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44);
            return vector_data46(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45);
        }

        template <typename Sequence>
        static vector_data46
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44);
            return vector_data46(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45);
        }

        vector46() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45>
        vector46(
            vector46<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44 , vec.m45) {}

        template <typename Sequence>
        vector46(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector46(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45>
        vector46&
        operator=(vector46<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45;
            return *this;
        }

        vector_data47()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() , m45() , m46() {}

        vector_data47(
            vector_data47 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) , m45(other.m45) , m46(other.m46) {}

        vector_data47&
        operator=(vector_data47 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46;
            return *this;
        }

        template <typename Sequence>
        static vector_data47
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45);
            return vector_data47(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46);
        }

        template <typename Sequence>
        static vector_data47
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45);
            return vector_data47(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46);
        }

        vector47() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46>
        vector47(
            vector47<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44 , vec.m45 , vec.m46) {}

        template <typename Sequence>
        vector47(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector47(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46>
        vector47&
        operator=(vector47<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46;
            return *this;
        }

        vector_data48()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() , m45() , m46() , m47() {}

        vector_data48(
            vector_data48 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) , m45(other.m45) , m46(other.m46) , m47(other.m47) {}

        vector_data48&
        operator=(vector_data48 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47;
            return *this;
        }

        template <typename Sequence>
        static vector_data48
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46);
            return vector_data48(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47);
        }

        template <typename Sequence>
        static vector_data48
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46);
            return vector_data48(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47);
        }

        vector48() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47>
        vector48(
            vector48<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44 , vec.m45 , vec.m46 , vec.m47) {}

        template <typename Sequence>
        vector48(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector48(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47>
        vector48&
        operator=(vector48<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47;
            return *this;
        }

        vector_data49()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() , m45() , m46() , m47() , m48() {}

        vector_data49(
            vector_data49 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) , m45(other.m45) , m46(other.m46) , m47(other.m47) , m48(other.m48) {}

        vector_data49&
        operator=(vector_data49 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47; this->m48 = vec.m48;
            return *this;
        }

        template <typename Sequence>
        static vector_data49
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46); typedef typename result_of::next< I47>::type I48; I48 i48 = fusion::next(i47);
            return vector_data49(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47 , *i48);
        }

        template <typename Sequence>
        static vector_data49
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46); typedef typename result_of::next< I47>::type I48; I48 i48 = fusion::next(i47);
            return vector_data49(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47 , *i48);
        }

        vector49() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48>
        vector49(
            vector49<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44 , vec.m45 , vec.m46 , vec.m47 , vec.m48) {}

        template <typename Sequence>
        vector49(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector49(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48>
        vector49&
        operator=(vector49<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47; this->m48 = vec.m48;
            return *this;
        }

        vector_data50()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() , m40() , m41() , m42() , m43() , m44() , m45() , m46() , m47() , m48() , m49() {}

        vector_data50(
            vector_data50 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) , m40(other.m40) , m41(other.m41) , m42(other.m42) , m43(other.m43) , m44(other.m44) , m45(other.m45) , m46(other.m46) , m47(other.m47) , m48(other.m48) , m49(other.m49) {}

        vector_data50&
        operator=(vector_data50 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47; this->m48 = vec.m48; this->m49 = vec.m49;
            return *this;
        }

        template <typename Sequence>
        static vector_data50
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46); typedef typename result_of::next< I47>::type I48; I48 i48 = fusion::next(i47); typedef typename result_of::next< I48>::type I49; I49 i49 = fusion::next(i48);
            return vector_data50(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47 , *i48 , *i49);
        }

        template <typename Sequence>
        static vector_data50
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38); typedef typename result_of::next< I39>::type I40; I40 i40 = fusion::next(i39); typedef typename result_of::next< I40>::type I41; I41 i41 = fusion::next(i40); typedef typename result_of::next< I41>::type I42; I42 i42 = fusion::next(i41); typedef typename result_of::next< I42>::type I43; I43 i43 = fusion::next(i42); typedef typename result_of::next< I43>::type I44; I44 i44 = fusion::next(i43); typedef typename result_of::next< I44>::type I45; I45 i45 = fusion::next(i44); typedef typename result_of::next< I45>::type I46; I46 i46 = fusion::next(i45); typedef typename result_of::next< I46>::type I47; I47 i47 = fusion::next(i46); typedef typename result_of::next< I47>::type I48; I48 i48 = fusion::next(i47); typedef typename result_of::next< I48>::type I49; I49 i49 = fusion::next(i48);
            return vector_data50(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39 , *i40 , *i41 , *i42 , *i43 , *i44 , *i45 , *i46 , *i47 , *i48 , *i49);
        }

        vector50() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        vector50(
            vector50<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39 , vec.m40 , vec.m41 , vec.m42 , vec.m43 , vec.m44 , vec.m45 , vec.m46 , vec.m47 , vec.m48 , vec.m49) {}

        template <typename Sequence>
        vector50(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector50(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        vector50&
        operator=(vector50<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39; this->m40 = vec.m40; this->m41 = vec.m41; this->m42 = vec.m42; this->m43 = vec.m43; this->m44 = vec.m44; this->m45 = vec.m45; this->m46 = vec.m46; this->m47 = vec.m47; this->m48 = vec.m48; this->m49 = vec.m49;
            return *this;
        }

        vector_data21()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() {}

        vector_data21(
            vector_data21 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) {}

        vector_data21&
        operator=(vector_data21 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20;
            return *this;
        }

        template <typename Sequence>
        static vector_data21
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19);
            return vector_data21(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20);
        }

        template <typename Sequence>
        static vector_data21
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19);
            return vector_data21(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20);
        }

        vector21() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20>
        vector21(
            vector21<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20) {}

        template <typename Sequence>
        vector21(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector21(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20>
        vector21&
        operator=(vector21<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20;
            return *this;
        }

        vector_data22()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() {}

        vector_data22(
            vector_data22 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) {}

        vector_data22&
        operator=(vector_data22 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21;
            return *this;
        }

        template <typename Sequence>
        static vector_data22
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20);
            return vector_data22(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21);
        }

        template <typename Sequence>
        static vector_data22
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20);
            return vector_data22(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21);
        }

        vector22() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21>
        vector22(
            vector22<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21) {}

        template <typename Sequence>
        vector22(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector22(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21>
        vector22&
        operator=(vector22<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21;
            return *this;
        }

        vector_data23()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() {}

        vector_data23(
            vector_data23 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) {}

        vector_data23&
        operator=(vector_data23 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22;
            return *this;
        }

        template <typename Sequence>
        static vector_data23
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21);
            return vector_data23(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22);
        }

        template <typename Sequence>
        static vector_data23
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21);
            return vector_data23(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22);
        }

        vector23() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22>
        vector23(
            vector23<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22) {}

        template <typename Sequence>
        vector23(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector23(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22>
        vector23&
        operator=(vector23<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22;
            return *this;
        }

        vector_data24()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() {}

        vector_data24(
            vector_data24 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) {}

        vector_data24&
        operator=(vector_data24 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23;
            return *this;
        }

        template <typename Sequence>
        static vector_data24
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22);
            return vector_data24(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23);
        }

        template <typename Sequence>
        static vector_data24
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22);
            return vector_data24(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23);
        }

        vector24() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23>
        vector24(
            vector24<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23) {}

        template <typename Sequence>
        vector24(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector24(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23>
        vector24&
        operator=(vector24<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23;
            return *this;
        }

        vector_data25()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() {}

        vector_data25(
            vector_data25 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) {}

        vector_data25&
        operator=(vector_data25 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24;
            return *this;
        }

        template <typename Sequence>
        static vector_data25
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23);
            return vector_data25(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24);
        }

        template <typename Sequence>
        static vector_data25
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23);
            return vector_data25(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24);
        }

        vector25() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24>
        vector25(
            vector25<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24) {}

        template <typename Sequence>
        vector25(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector25(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24>
        vector25&
        operator=(vector25<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24;
            return *this;
        }

        vector_data26()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() {}

        vector_data26(
            vector_data26 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) {}

        vector_data26&
        operator=(vector_data26 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25;
            return *this;
        }

        template <typename Sequence>
        static vector_data26
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24);
            return vector_data26(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25);
        }

        template <typename Sequence>
        static vector_data26
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24);
            return vector_data26(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25);
        }

        vector26() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25>
        vector26(
            vector26<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25) {}

        template <typename Sequence>
        vector26(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector26(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25>
        vector26&
        operator=(vector26<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25;
            return *this;
        }

        vector_data27()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() {}

        vector_data27(
            vector_data27 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) {}

        vector_data27&
        operator=(vector_data27 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26;
            return *this;
        }

        template <typename Sequence>
        static vector_data27
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25);
            return vector_data27(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26);
        }

        template <typename Sequence>
        static vector_data27
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25);
            return vector_data27(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26);
        }

        vector27() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26>
        vector27(
            vector27<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26) {}

        template <typename Sequence>
        vector27(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector27(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26>
        vector27&
        operator=(vector27<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26;
            return *this;
        }

        vector_data28()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() {}

        vector_data28(
            vector_data28 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) {}

        vector_data28&
        operator=(vector_data28 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27;
            return *this;
        }

        template <typename Sequence>
        static vector_data28
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26);
            return vector_data28(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27);
        }

        template <typename Sequence>
        static vector_data28
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26);
            return vector_data28(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27);
        }

        vector28() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27>
        vector28(
            vector28<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27) {}

        template <typename Sequence>
        vector28(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector28(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27>
        vector28&
        operator=(vector28<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27;
            return *this;
        }

        vector_data29()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() {}

        vector_data29(
            vector_data29 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) {}

        vector_data29&
        operator=(vector_data29 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28;
            return *this;
        }

        template <typename Sequence>
        static vector_data29
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27);
            return vector_data29(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28);
        }

        template <typename Sequence>
        static vector_data29
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27);
            return vector_data29(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28);
        }

        vector29() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28>
        vector29(
            vector29<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28) {}

        template <typename Sequence>
        vector29(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector29(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28>
        vector29&
        operator=(vector29<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28;
            return *this;
        }

        vector_data30()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() {}

        vector_data30(
            vector_data30 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) {}

        vector_data30&
        operator=(vector_data30 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29;
            return *this;
        }

        template <typename Sequence>
        static vector_data30
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28);
            return vector_data30(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29);
        }

        template <typename Sequence>
        static vector_data30
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28);
            return vector_data30(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29);
        }

        vector30() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        vector30(
            vector30<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29) {}

        template <typename Sequence>
        vector30(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector30(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        vector30&
        operator=(vector30<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29;
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        vector_data11()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() {}

        vector_data11(
            vector_data11 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) {}

        vector_data11&
        operator=(vector_data11 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10;
            return *this;
        }

        template <typename Sequence>
        static vector_data11
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9);
            return vector_data11(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10);
        }

        template <typename Sequence>
        static vector_data11
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9);
            return vector_data11(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10);
        }

        vector11() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
        vector11(
            vector11<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10) {}

        template <typename Sequence>
        vector11(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector11(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
        vector11&
        operator=(vector11<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10;
            return *this;
        }

        vector_data12()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() {}

        vector_data12(
            vector_data12 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) {}

        vector_data12&
        operator=(vector_data12 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11;
            return *this;
        }

        template <typename Sequence>
        static vector_data12
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10);
            return vector_data12(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11);
        }

        template <typename Sequence>
        static vector_data12
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10);
            return vector_data12(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11);
        }

        vector12() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
        vector12(
            vector12<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11) {}

        template <typename Sequence>
        vector12(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector12(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
        vector12&
        operator=(vector12<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11;
            return *this;
        }

        vector_data13()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() {}

        vector_data13(
            vector_data13 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) {}

        vector_data13&
        operator=(vector_data13 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12;
            return *this;
        }

        template <typename Sequence>
        static vector_data13
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11);
            return vector_data13(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12);
        }

        template <typename Sequence>
        static vector_data13
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11);
            return vector_data13(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12);
        }

        vector13() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
        vector13(
            vector13<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12) {}

        template <typename Sequence>
        vector13(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector13(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
        vector13&
        operator=(vector13<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12;
            return *this;
        }

        vector_data14()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() {}

        vector_data14(
            vector_data14 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) {}

        vector_data14&
        operator=(vector_data14 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13;
            return *this;
        }

        template <typename Sequence>
        static vector_data14
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12);
            return vector_data14(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13);
        }

        template <typename Sequence>
        static vector_data14
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12);
            return vector_data14(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13);
        }

        vector14() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
        vector14(
            vector14<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13) {}

        template <typename Sequence>
        vector14(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector14(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
        vector14&
        operator=(vector14<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13;
            return *this;
        }

        vector_data15()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() {}

        vector_data15(
            vector_data15 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) {}

        vector_data15&
        operator=(vector_data15 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14;
            return *this;
        }

        template <typename Sequence>
        static vector_data15
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13);
            return vector_data15(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14);
        }

        template <typename Sequence>
        static vector_data15
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13);
            return vector_data15(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14);
        }

        vector15() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
        vector15(
            vector15<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14) {}

        template <typename Sequence>
        vector15(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector15(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
        vector15&
        operator=(vector15<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14;
            return *this;
        }

        vector_data16()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() {}

        vector_data16(
            vector_data16 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) {}

        vector_data16&
        operator=(vector_data16 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15;
            return *this;
        }

        template <typename Sequence>
        static vector_data16
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14);
            return vector_data16(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15);
        }

        template <typename Sequence>
        static vector_data16
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14);
            return vector_data16(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15);
        }

        vector16() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
        vector16(
            vector16<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15) {}

        template <typename Sequence>
        vector16(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector16(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
        vector16&
        operator=(vector16<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15;
            return *this;
        }

        vector_data17()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() {}

        vector_data17(
            vector_data17 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) {}

        vector_data17&
        operator=(vector_data17 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16;
            return *this;
        }

        template <typename Sequence>
        static vector_data17
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15);
            return vector_data17(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16);
        }

        template <typename Sequence>
        static vector_data17
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15);
            return vector_data17(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16);
        }

        vector17() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
        vector17(
            vector17<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16) {}

        template <typename Sequence>
        vector17(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector17(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
        vector17&
        operator=(vector17<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16;
            return *this;
        }

        vector_data18()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() {}

        vector_data18(
            vector_data18 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) {}

        vector_data18&
        operator=(vector_data18 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17;
            return *this;
        }

        template <typename Sequence>
        static vector_data18
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16);
            return vector_data18(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17);
        }

        template <typename Sequence>
        static vector_data18
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16);
            return vector_data18(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17);
        }

        vector18() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
        vector18(
            vector18<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17) {}

        template <typename Sequence>
        vector18(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector18(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
        vector18&
        operator=(vector18<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17;
            return *this;
        }

        vector_data19()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() {}

        vector_data19(
            vector_data19 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) {}

        vector_data19&
        operator=(vector_data19 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18;
            return *this;
        }

        template <typename Sequence>
        static vector_data19
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17);
            return vector_data19(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18);
        }

        template <typename Sequence>
        static vector_data19
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17);
            return vector_data19(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18);
        }

        vector19() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
        vector19(
            vector19<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18) {}

        template <typename Sequence>
        vector19(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector19(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
        vector19&
        operator=(vector19<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18;
            return *this;
        }

        vector_data20()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() {}

        vector_data20(
            vector_data20 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) {}

        vector_data20&
        operator=(vector_data20 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19;
            return *this;
        }

        template <typename Sequence>
        static vector_data20
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18);
            return vector_data20(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19);
        }

        template <typename Sequence>
        static vector_data20
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18);
            return vector_data20(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19);
        }

        vector20() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        vector20(
            vector20<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19) {}

        template <typename Sequence>
        vector20(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector20(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        vector20&
        operator=(vector20<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19;
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        vector()
            : vec() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
            : vec(rhs.vec) {}

        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        vector(Sequence const& rhs)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        vector_data1()
            : m0() {}

        vector_data1(
            vector_data1 const& other)
            : m0(other.m0) {}

        vector_data1&
        operator=(vector_data1 const& vec)
        {
            this->m0 = vec.m0;
            return *this;
        }

        template <typename Sequence>
        static vector_data1
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            
            return vector_data1(*i0);
        }

        template <typename Sequence>
        static vector_data1
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            
            return vector_data1(*i0);
        }

        vector1() {}

        template <typename U0>
        vector1(
            vector1<U0> const& vec)
            : base_type(vec.m0) {}

        template <typename U0>
        vector1&
        operator=(vector1<U0> const& vec)
        {
            this->m0 = vec.m0;
            return *this;
        }

        vector_data2()
            : m0() , m1() {}

        vector_data2(
            vector_data2 const& other)
            : m0(other.m0) , m1(other.m1) {}

        vector_data2&
        operator=(vector_data2 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1;
            return *this;
        }

        template <typename Sequence>
        static vector_data2
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0);
            return vector_data2(*i0 , *i1);
        }

        template <typename Sequence>
        static vector_data2
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0);
            return vector_data2(*i0 , *i1);
        }

        vector2() {}

        template <typename U0 , typename U1>
        vector2(
            vector2<U0 , U1> const& vec)
            : base_type(vec.m0 , vec.m1) {}

        template <typename Sequence>
        vector2(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector2(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1>
        vector2&
        operator=(vector2<U0 , U1> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1;
            return *this;
        }

        vector_data3()
            : m0() , m1() , m2() {}

        vector_data3(
            vector_data3 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) {}

        vector_data3&
        operator=(vector_data3 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2;
            return *this;
        }

        template <typename Sequence>
        static vector_data3
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1);
            return vector_data3(*i0 , *i1 , *i2);
        }

        template <typename Sequence>
        static vector_data3
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1);
            return vector_data3(*i0 , *i1 , *i2);
        }

        vector3() {}

        template <typename U0 , typename U1 , typename U2>
        vector3(
            vector3<U0 , U1 , U2> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2) {}

        template <typename Sequence>
        vector3(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector3(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2>
        vector3&
        operator=(vector3<U0 , U1 , U2> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2;
            return *this;
        }

        vector_data4()
            : m0() , m1() , m2() , m3() {}

        vector_data4(
            vector_data4 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) {}

        vector_data4&
        operator=(vector_data4 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3;
            return *this;
        }

        template <typename Sequence>
        static vector_data4
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2);
            return vector_data4(*i0 , *i1 , *i2 , *i3);
        }

        template <typename Sequence>
        static vector_data4
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2);
            return vector_data4(*i0 , *i1 , *i2 , *i3);
        }

        vector4() {}

        template <typename U0 , typename U1 , typename U2 , typename U3>
        vector4(
            vector4<U0 , U1 , U2 , U3> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3) {}

        template <typename Sequence>
        vector4(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector4(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3>
        vector4&
        operator=(vector4<U0 , U1 , U2 , U3> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3;
            return *this;
        }

        vector_data5()
            : m0() , m1() , m2() , m3() , m4() {}

        vector_data5(
            vector_data5 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) {}

        vector_data5&
        operator=(vector_data5 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4;
            return *this;
        }

        template <typename Sequence>
        static vector_data5
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3);
            return vector_data5(*i0 , *i1 , *i2 , *i3 , *i4);
        }

        template <typename Sequence>
        static vector_data5
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3);
            return vector_data5(*i0 , *i1 , *i2 , *i3 , *i4);
        }

        vector5() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
        vector5(
            vector5<U0 , U1 , U2 , U3 , U4> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4) {}

        template <typename Sequence>
        vector5(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector5(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
        vector5&
        operator=(vector5<U0 , U1 , U2 , U3 , U4> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4;
            return *this;
        }

        vector_data6()
            : m0() , m1() , m2() , m3() , m4() , m5() {}

        vector_data6(
            vector_data6 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) {}

        vector_data6&
        operator=(vector_data6 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5;
            return *this;
        }

        template <typename Sequence>
        static vector_data6
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4);
            return vector_data6(*i0 , *i1 , *i2 , *i3 , *i4 , *i5);
        }

        template <typename Sequence>
        static vector_data6
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4);
            return vector_data6(*i0 , *i1 , *i2 , *i3 , *i4 , *i5);
        }

        vector6() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
        vector6(
            vector6<U0 , U1 , U2 , U3 , U4 , U5> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5) {}

        template <typename Sequence>
        vector6(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector6(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
        vector6&
        operator=(vector6<U0 , U1 , U2 , U3 , U4 , U5> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5;
            return *this;
        }

        vector_data7()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() {}

        vector_data7(
            vector_data7 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) {}

        vector_data7&
        operator=(vector_data7 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6;
            return *this;
        }

        template <typename Sequence>
        static vector_data7
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5);
            return vector_data7(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6);
        }

        template <typename Sequence>
        static vector_data7
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5);
            return vector_data7(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6);
        }

        vector7() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
        vector7(
            vector7<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6) {}

        template <typename Sequence>
        vector7(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector7(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
        vector7&
        operator=(vector7<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6;
            return *this;
        }

        vector_data8()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() {}

        vector_data8(
            vector_data8 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) {}

        vector_data8&
        operator=(vector_data8 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7;
            return *this;
        }

        template <typename Sequence>
        static vector_data8
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6);
            return vector_data8(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7);
        }

        template <typename Sequence>
        static vector_data8
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6);
            return vector_data8(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7);
        }

        vector8() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
        vector8(
            vector8<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7) {}

        template <typename Sequence>
        vector8(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector8(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
        vector8&
        operator=(vector8<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7;
            return *this;
        }

        vector_data9()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() {}

        vector_data9(
            vector_data9 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) {}

        vector_data9&
        operator=(vector_data9 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8;
            return *this;
        }

        template <typename Sequence>
        static vector_data9
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7);
            return vector_data9(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8);
        }

        template <typename Sequence>
        static vector_data9
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7);
            return vector_data9(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8);
        }

        vector9() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
        vector9(
            vector9<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8) {}

        template <typename Sequence>
        vector9(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector9(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
        vector9&
        operator=(vector9<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8;
            return *this;
        }

        vector_data10()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() {}

        vector_data10(
            vector_data10 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) {}

        vector_data10&
        operator=(vector_data10 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9;
            return *this;
        }

        template <typename Sequence>
        static vector_data10
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8);
            return vector_data10(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9);
        }

        template <typename Sequence>
        static vector_data10
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8);
            return vector_data10(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9);
        }

        vector10() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        vector10(
            vector10<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9) {}

        template <typename Sequence>
        vector10(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector10(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        vector10&
        operator=(vector10<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9;
            return *this;
        }

        vector_data31()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() {}

        vector_data31(
            vector_data31 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) {}

        vector_data31&
        operator=(vector_data31 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30;
            return *this;
        }

        template <typename Sequence>
        static vector_data31
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29);
            return vector_data31(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30);
        }

        template <typename Sequence>
        static vector_data31
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29);
            return vector_data31(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30);
        }

        vector31() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30>
        vector31(
            vector31<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30) {}

        template <typename Sequence>
        vector31(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector31(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30>
        vector31&
        operator=(vector31<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30;
            return *this;
        }

        vector_data32()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() {}

        vector_data32(
            vector_data32 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) {}

        vector_data32&
        operator=(vector_data32 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31;
            return *this;
        }

        template <typename Sequence>
        static vector_data32
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30);
            return vector_data32(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31);
        }

        template <typename Sequence>
        static vector_data32
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30);
            return vector_data32(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31);
        }

        vector32() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31>
        vector32(
            vector32<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31) {}

        template <typename Sequence>
        vector32(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector32(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31>
        vector32&
        operator=(vector32<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31;
            return *this;
        }

        vector_data33()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() {}

        vector_data33(
            vector_data33 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) {}

        vector_data33&
        operator=(vector_data33 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32;
            return *this;
        }

        template <typename Sequence>
        static vector_data33
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31);
            return vector_data33(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32);
        }

        template <typename Sequence>
        static vector_data33
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31);
            return vector_data33(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32);
        }

        vector33() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32>
        vector33(
            vector33<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32) {}

        template <typename Sequence>
        vector33(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector33(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32>
        vector33&
        operator=(vector33<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32;
            return *this;
        }

        vector_data34()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() {}

        vector_data34(
            vector_data34 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) {}

        vector_data34&
        operator=(vector_data34 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33;
            return *this;
        }

        template <typename Sequence>
        static vector_data34
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32);
            return vector_data34(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33);
        }

        template <typename Sequence>
        static vector_data34
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32);
            return vector_data34(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33);
        }

        vector34() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33>
        vector34(
            vector34<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33) {}

        template <typename Sequence>
        vector34(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector34(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33>
        vector34&
        operator=(vector34<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33;
            return *this;
        }

        vector_data35()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() {}

        vector_data35(
            vector_data35 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) {}

        vector_data35&
        operator=(vector_data35 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34;
            return *this;
        }

        template <typename Sequence>
        static vector_data35
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33);
            return vector_data35(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34);
        }

        template <typename Sequence>
        static vector_data35
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33);
            return vector_data35(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34);
        }

        vector35() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34>
        vector35(
            vector35<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34) {}

        template <typename Sequence>
        vector35(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector35(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34>
        vector35&
        operator=(vector35<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34;
            return *this;
        }

        vector_data36()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() {}

        vector_data36(
            vector_data36 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) {}

        vector_data36&
        operator=(vector_data36 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35;
            return *this;
        }

        template <typename Sequence>
        static vector_data36
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34);
            return vector_data36(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35);
        }

        template <typename Sequence>
        static vector_data36
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34);
            return vector_data36(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35);
        }

        vector36() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35>
        vector36(
            vector36<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35) {}

        template <typename Sequence>
        vector36(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector36(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35>
        vector36&
        operator=(vector36<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35;
            return *this;
        }

        vector_data37()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() {}

        vector_data37(
            vector_data37 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) {}

        vector_data37&
        operator=(vector_data37 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36;
            return *this;
        }

        template <typename Sequence>
        static vector_data37
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35);
            return vector_data37(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36);
        }

        template <typename Sequence>
        static vector_data37
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35);
            return vector_data37(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36);
        }

        vector37() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36>
        vector37(
            vector37<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36) {}

        template <typename Sequence>
        vector37(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector37(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36>
        vector37&
        operator=(vector37<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36;
            return *this;
        }

        vector_data38()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() {}

        vector_data38(
            vector_data38 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) {}

        vector_data38&
        operator=(vector_data38 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37;
            return *this;
        }

        template <typename Sequence>
        static vector_data38
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36);
            return vector_data38(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37);
        }

        template <typename Sequence>
        static vector_data38
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36);
            return vector_data38(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37);
        }

        vector38() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37>
        vector38(
            vector38<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37) {}

        template <typename Sequence>
        vector38(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector38(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37>
        vector38&
        operator=(vector38<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37;
            return *this;
        }

        vector_data39()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() {}

        vector_data39(
            vector_data39 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) {}

        vector_data39&
        operator=(vector_data39 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38;
            return *this;
        }

        template <typename Sequence>
        static vector_data39
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37);
            return vector_data39(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38);
        }

        template <typename Sequence>
        static vector_data39
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37);
            return vector_data39(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38);
        }

        vector39() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38>
        vector39(
            vector39<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38) {}

        template <typename Sequence>
        vector39(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector39(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38>
        vector39&
        operator=(vector39<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38;
            return *this;
        }

        vector_data40()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() , m20() , m21() , m22() , m23() , m24() , m25() , m26() , m27() , m28() , m29() , m30() , m31() , m32() , m33() , m34() , m35() , m36() , m37() , m38() , m39() {}

        vector_data40(
            vector_data40 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) , m20(other.m20) , m21(other.m21) , m22(other.m22) , m23(other.m23) , m24(other.m24) , m25(other.m25) , m26(other.m26) , m27(other.m27) , m28(other.m28) , m29(other.m29) , m30(other.m30) , m31(other.m31) , m32(other.m32) , m33(other.m33) , m34(other.m34) , m35(other.m35) , m36(other.m36) , m37(other.m37) , m38(other.m38) , m39(other.m39) {}

        vector_data40&
        operator=(vector_data40 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39;
            return *this;
        }

        template <typename Sequence>
        static vector_data40
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38);
            return vector_data40(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39);
        }

        template <typename Sequence>
        static vector_data40
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18); typedef typename result_of::next< I19>::type I20; I20 i20 = fusion::next(i19); typedef typename result_of::next< I20>::type I21; I21 i21 = fusion::next(i20); typedef typename result_of::next< I21>::type I22; I22 i22 = fusion::next(i21); typedef typename result_of::next< I22>::type I23; I23 i23 = fusion::next(i22); typedef typename result_of::next< I23>::type I24; I24 i24 = fusion::next(i23); typedef typename result_of::next< I24>::type I25; I25 i25 = fusion::next(i24); typedef typename result_of::next< I25>::type I26; I26 i26 = fusion::next(i25); typedef typename result_of::next< I26>::type I27; I27 i27 = fusion::next(i26); typedef typename result_of::next< I27>::type I28; I28 i28 = fusion::next(i27); typedef typename result_of::next< I28>::type I29; I29 i29 = fusion::next(i28); typedef typename result_of::next< I29>::type I30; I30 i30 = fusion::next(i29); typedef typename result_of::next< I30>::type I31; I31 i31 = fusion::next(i30); typedef typename result_of::next< I31>::type I32; I32 i32 = fusion::next(i31); typedef typename result_of::next< I32>::type I33; I33 i33 = fusion::next(i32); typedef typename result_of::next< I33>::type I34; I34 i34 = fusion::next(i33); typedef typename result_of::next< I34>::type I35; I35 i35 = fusion::next(i34); typedef typename result_of::next< I35>::type I36; I36 i36 = fusion::next(i35); typedef typename result_of::next< I36>::type I37; I37 i37 = fusion::next(i36); typedef typename result_of::next< I37>::type I38; I38 i38 = fusion::next(i37); typedef typename result_of::next< I38>::type I39; I39 i39 = fusion::next(i38);
            return vector_data40(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39);
        }

        vector40() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        vector40(
            vector40<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19 , vec.m20 , vec.m21 , vec.m22 , vec.m23 , vec.m24 , vec.m25 , vec.m26 , vec.m27 , vec.m28 , vec.m29 , vec.m30 , vec.m31 , vec.m32 , vec.m33 , vec.m34 , vec.m35 , vec.m36 , vec.m37 , vec.m38 , vec.m39) {}

        template <typename Sequence>
        vector40(
            Sequence const& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
        vector40(
            Sequence& seq
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        vector40&
        operator=(vector40<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19; this->m20 = vec.m20; this->m21 = vec.m21; this->m22 = vec.m22; this->m23 = vec.m23; this->m24 = vec.m24; this->m25 = vec.m25; this->m26 = vec.m26; this->m27 = vec.m27; this->m28 = vec.m28; this->m29 = vec.m29; this->m30 = vec.m30; this->m31 = vec.m31; this->m32 = vec.m32; this->m33 = vec.m33; this->m34 = vec.m34; this->m35 = vec.m35; this->m36 = vec.m36; this->m37 = vec.m37; this->m38 = vec.m38; this->m39 = vec.m39;
            return *this;
        }

        template <typename Iterator>
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }

        vector()
            : vec() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
            : vec(rhs.vec) {}

        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        vector(Sequence const& rhs)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }

        vector()
            : vec() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
            : vec(rhs.vec) {}

        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        vector(Sequence const& rhs)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }

        vector()
            : vec() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
            : vec(rhs.vec) {}

        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        vector(Sequence const& rhs)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }

        vector()
            : vec() {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        vector(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
            : vec(rhs.vec) {}

        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        vector(Sequence const& rhs)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        vector&
        operator=(vector<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }


        inline explicit fused_function_object(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }


        inline explicit unfused_typed(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }


        inline explicit unfused(func_const_fwd_t f = function())
            : unfused<Function,false>(f)
        { }


        inline explicit unfused(func_const_fwd_t f = function())
            : fnc_transformed(f)
        { }


        inline explicit fused_procedure(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }


        template <class Seq> 
        inline void operator()(Seq const & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }


        template <class Seq> 
        inline void operator()(Seq const & s) 
        {
            fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }


        template <class Seq> 
        inline void operator()(Seq & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }


        template <class Seq> 
        inline void operator()(Seq & s) 
        {
            return fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }


        inline explicit fused(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }


    template <typename Function, class Sequence>
    inline void invoke_procedure(Function f, Sequence & s)
    {
        detail::invoke_procedure_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }


    template <typename Function, class Sequence>
    inline void invoke_procedure(Function f, Sequence const & s)
    {
        detail::invoke_procedure_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }


    template <class Function, class Sequence>
    inline typename result_of::invoke_function_object<Function,Sequence>::type
    invoke_function_object(Function f, Sequence & s)
    {
        return detail::invoke_function_object_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }


    template <class Function, class Sequence>
    inline typename result_of::invoke_function_object<Function,Sequence const>::type
    invoke_function_object(Function f, Sequence const & s)
    {
        return detail::invoke_function_object_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }


            static inline result_type call(T C::* f, Sequence & s)
            {
                typename result_of::front<Sequence>::type c = fusion::front(s);
                return that_ptr<qualified_class>::get(c)->*f;
            }


    template <typename Function, class Sequence>
    inline typename result_of::invoke<Function,Sequence>::type
    invoke(Function f, Sequence & s)
    {
        return detail::invoke_impl<
                typename boost::remove_reference<Function>::type,Sequence
            >::call(f,s);
    }


    template <typename Function, class Sequence>
    inline typename result_of::invoke<Function,Sequence const>::type
    invoke(Function f, Sequence const & s)
    {
        return detail::invoke_impl<
                typename boost::remove_reference<Function>::type,Sequence const
            >::call(f,s);
    }


        template <typename T> 
        static inline pointee * do_get_pointer(T &, pointee * x) 
        {
            return x;
        }


        static inline pointee * get(pointee * x)
        {
            return x; 
        }


        array_iterator(Array& a)
            : array(a) {}


            static type
            call(Iterator const & it)
            {
                return it.array[Iterator::index::value];
            }


            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }


            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }


                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }

    
                static type
                call(Sequence& v)
                {
                    return type(v);
                }

    
                static type
                call(Sequence& v)
                {
                    return type(v);
                }


            static type
            call(Iterator)
            {
                return type();
            }


            static type
            call(Iterator)
            {
                return type();
            }


            static type
            call(Iterator)
            {
                return type();
            }


            static type
            call(Iterator const& /*i*/)
            {
                return type();
            }

            
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }

                
                static type
                call(Sequence)
                {
                    return type();
                }

                
                static type
                call(Sequence)
                {
                    return type();
                }

                
                static type
                call(Sequence)
                {
                    return type();
                }


        explicit std_tuple_iterator(Tuple& tuple)
          : tuple(tuple) {}


            static type
            call(Iterator const& iter)
            {
                return std::get<Index>(iter.tuple);
            }


            static type
            call(Iterator const& i)
            {
                return type(i.tuple);
            }


            static type
            call(First const&, Last const&)
            {
                return type();
            }


                static type
                call(Sequence& seq)
                {
                    return std::get<N::value>(seq);
                }


                static type
                call(Sequence& v)
                {
                    return type(v);
                }


                static type
                call(Sequence& v)
                {
                    return type(v);
                }


        explicit boost_tuple_iterator(Cons& in_cons)
            : cons(in_cons) {}


            static type
            call(Iterator const& iter)
            {
                return iter.cons.get_head();
            }


            static type
            call(Iterator const& iter)
            {
                return type(iter.cons.get_tail());
            }

            
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }

    
                static type
                call(Sequence& seq)
                {
                    return tuples::get<N::value>(seq);
                }

    
                static type
                call(Sequence& v)
                {
                    return type(v);
                }


                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }


    template<typename Seq, typename State, typename F>
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq& seq, State const& state, F f)
    {
        return result_of::BOOST_FUSION_FOLD_NAME<Seq,State const,F>::call(
            state,
            seq,
            f);
    }


    template<typename Seq, typename State, typename F>
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq const
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq const& seq, State const& state, F f)
    {
        return result_of::BOOST_FUSION_FOLD_NAME<Seq const,State const,F>::call(
            state,
            seq,
            f);
    }


    template<typename Seq, typename State, typename F>
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq& seq, State& state, F f)
    {
        return result_of::BOOST_FUSION_FOLD_NAME<Seq,State,F>::call(
            state,
            seq,
            f);
    }


    template<typename Seq, typename State, typename F>
    inline typename result_of::BOOST_FUSION_FOLD_NAME<
        Seq const
      , State const
      , F
    >::type
    BOOST_FUSION_FOLD_NAME(Seq const& seq, State& state, F f)
    {
        return result_of::BOOST_FUSION_FOLD_NAME<Seq const,State,F>::call(
            state,
            seq,
            f);
    }

    template <typename First, typename Last, typename F>
    inline void
    for_each_linear(First const&, Last const&, F const&, mpl::true_)
    {
    }



    template <typename Sequence, typename F, typename Tag>
    inline void
    for_each_dispatch(Sequence& seq, F const& f, Tag)
    {
        detail::for_each_linear(
                                fusion::begin(seq)
                                , fusion::end(seq)
                                , f
                                , result_of::equal_to<
                                typename result_of::begin<Sequence>::type
                                , typename result_of::end<Sequence>::type>());
    }

        template<typename I0, typename F>
        static void call(I0 const& i0, F const& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
            typedef typename result_of::next<I2>::type I3;
            I3 i3(fusion::next(i2));
            f(*i3);
            for_each_unrolled<N-4>::call(fusion::next(i3), f);
        }

        template<typename I0, typename F>
        static void call(I0 const& i0, F const& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            f(*i2);
        }

        template<typename I0, typename F>
        static void call(I0 const& i0, F const& f)
        {
            f(*i0);
            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            f(*i1);
        }

        template<typename I0, typename F>
        static void call(I0 const& i0, F const& f)
        {
            f(*i0);
        }

        template<typename It, typename F>
        static void call(It const&, F const&)
        {
        }


    template <typename Sequence, typename F>
    inline void
    for_each(Sequence& seq, F const& f, mpl::false_) // unsegmented implementation
    {
        detail::for_each_dispatch(seq, f, typename traits::category_of<Sequence>::type());
    }

        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}


            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }


        static type call(State& state, Sequence& seq, Fun fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<Fun>(fun));
        }

        explicit segmented_for_each_fun(Fun const& f)
          : fun(f)
        {}


            static type call(Sequence& seq, State const&, Context const&, segmented_for_each_fun const& fun)
            {
                fusion::for_each(seq, fun.fun);
                return void_();
            }


    template <typename Sequence, typename F>
    inline void
    for_each(Sequence& seq, F const& f, mpl::true_) // segmented implementation
    {
        fusion::segmented_fold_until(seq, void_(), segmented_for_each_fun<F>(f));
    }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::next<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::next(it0);
                typedef typename
                    result_of::next<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::next(it1);
                typedef typename
                    result_of::next<
                        It2
                    >::type
                It3;
                It3 it3 = fusion::next(it2);
                typedef typename fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                typedef typename fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,fusion::deref(it1));
                typedef typename fold_lvalue_state<State2,It2,F>::type State3;
                State3 const state3=f(state2,fusion::deref(it2));
                return unrolled_fold<
                    Result
                  , N-4
                >::call(
                    f(state3,fusion::deref(it3)),
                    fusion::next(it3),
                    f);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::next<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::next(it0);
                typedef typename
                    result_of::next<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::next(it1);
                typedef typename fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                typedef typename fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,fusion::deref(it1));
                return f(state2,fusion::deref(it2));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                return f(
                    state1,
                    fusion::deref( fusion::next(it0)));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                return f(state,
                    fusion::deref(it0));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const&, F)
            {
                return static_cast<Result>(state);
            }

            static type
            call(StateRef state, Seq& seq, F f)
            {
                typedef
                    unrolled_fold<
                        type
                      , SeqSize
                    >
                unrolled_impl;
                return unrolled_impl::call(
                    state,
                    fusion::begin(seq),
                    f);
            }

            static StateRef
            call(StateRef state, Seq&, F)
            {
                return static_cast<StateRef>(state);
            }

    template<typename Seq, typename State, typename F>
    inline typename result_of::fold<
        Seq
      , State const
      , F
    >::type
    fold(Seq& seq, State const& state, F f)
    {
        return result_of::fold<Seq,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::fold<
        Seq const
      , State const
      , F
    >::type
    fold(Seq const& seq, State const& state, F f)
    {
        return result_of::fold<Seq const,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::fold<
        Seq
      , State const
      , F
    >::type
    fold(Seq& seq, State& state, F f)
    {
        return result_of::fold<Seq,State,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::fold<
        Seq const
      , State const
      , F
    >::type
    fold(Seq const& seq, State& state, F f)
    {
        return result_of::fold<Seq const,State,F>::call(
            state,
            seq,
            f);
    }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::next<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::next(it0);
                typedef typename
                    result_of::next<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::next(it1);
                typedef typename
                    result_of::next<
                        It2
                    >::type
                It3;
                It3 it3 = fusion::next(it2);
                typedef typename iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                typedef typename iter_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,it1);
                typedef typename iter_fold_lvalue_state<State2,It2,F>::type State3;
                State3 const state3=f(state2,it2);
                return unrolled_iter_fold<
                    Result
                  , N-4
                >::call(
                    f(state3,it3),
                    fusion::next(it3),
                    f);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::next<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::next(it0);
                typedef typename
                    result_of::next<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::next(it1);
                typedef typename iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                typedef typename iter_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,it1);
                return f(state2,it2);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                return f(
                    state1,
                    fusion::next(it0));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                return f(state,
                    it0);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0, F)
            {
                return static_cast<Result>(state);
            }

            static type
            call(StateRef state, Seq& seq, F f)
            {
                typedef
                    unrolled_iter_fold<
                        type
                      , SeqSize
                    >
                unrolled_impl;
                return unrolled_impl::call(
                    state,
                    fusion::begin(seq),
                    f);
            }

            static StateRef
            call(StateRef state, Seq&, F)
            {
                return static_cast<StateRef>(state);
            }

    template<typename Seq, typename State, typename F>
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State const& state, F f)
    {
        return result_of::iter_fold<Seq,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State const& state, F f)
    {
        return result_of::iter_fold<Seq const,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::iter_fold<
        Seq
      , State const
      , F
    >::type
    iter_fold(Seq& seq, State& state, F f)
    {
        return result_of::iter_fold<Seq,State,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::iter_fold<
        Seq const
      , State const
      , F
    >::type
    iter_fold(Seq const& seq, State& state, F f)
    {
        return result_of::iter_fold<Seq const,State,F>::call(
            state,
            seq,
            f);
    }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::prior<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::prior(it0);
                typedef typename
                    result_of::prior<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::prior(it1);
                typedef typename
                    result_of::prior<
                        It2
                    >::type
                It3;
                It3 it3 = fusion::prior(it2);
                typedef typename reverse_iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                typedef typename reverse_iter_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,it1);
                typedef typename reverse_iter_fold_lvalue_state<State2,It2,F>::type State3;
                State3 const state3=f(state2,it2);
                return unrolled_reverse_iter_fold<
                    Result
                  , N-4
                >::call(
                    f(state3,it3),
                    fusion::prior(it3),
                    f);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::prior<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::prior(it0);
                typedef typename
                    result_of::prior<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::prior(it1);
                typedef typename reverse_iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                typedef typename reverse_iter_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,it1);
                return f(state2,it2);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename reverse_iter_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,it0);
                return f(
                    state1,
                    fusion::prior(it0));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                return f(state,
                    it0);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0, F)
            {
                return static_cast<Result>(state);
            }

            static type
            call(StateRef state, Seq& seq, F f)
            {
                typedef
                    unrolled_reverse_iter_fold<
                        type
                      , SeqSize
                    >
                unrolled_impl;
                return unrolled_impl::call(
                    state,
                    fusion::prior( fusion::end(seq)),
                    f);
            }

            static StateRef
            call(StateRef state, Seq&, F)
            {
                return static_cast<StateRef>(state);
            }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State const& state, F f)
    {
        return result_of::reverse_iter_fold<Seq,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State const& state, F f)
    {
        return result_of::reverse_iter_fold<Seq const,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State& state, F f)
    {
        return result_of::reverse_iter_fold<Seq,State,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State& state, F f)
    {
        return result_of::reverse_iter_fold<Seq const,State,F>::call(
            state,
            seq,
            f);
    }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::prior<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::prior(it0);
                typedef typename
                    result_of::prior<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::prior(it1);
                typedef typename
                    result_of::prior<
                        It2
                    >::type
                It3;
                It3 it3 = fusion::prior(it2);
                typedef typename reverse_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                typedef typename reverse_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,fusion::deref(it1));
                typedef typename reverse_fold_lvalue_state<State2,It2,F>::type State3;
                State3 const state3=f(state2,fusion::deref(it2));
                return unrolled_reverse_fold<
                    Result
                  , N-4
                >::call(
                    f(state3,fusion::deref(it3)),
                    fusion::prior(it3),
                    f);
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename
                    result_of::prior<
                        It0 const
                    >::type
                It1;
                It1 it1 = fusion::prior(it0);
                typedef typename
                    result_of::prior<
                        It1
                    >::type
                It2;
                It2 it2 = fusion::prior(it1);
                typedef typename reverse_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                typedef typename reverse_fold_lvalue_state<State1,It1,F>::type State2;
                State2 const state2=f(state1,fusion::deref(it1));
                return f(state2,fusion::deref(it2));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                typedef typename reverse_fold_lvalue_state<State,It0,F>::type State1;
                State1 const state1=f(state,fusion::deref(it0));
                return f(
                    state1,
                    fusion::deref( fusion::prior(it0)));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const& it0,F f)
            {
                return f(state,
                    fusion::deref(it0));
            }

            template<typename State, typename It0, typename F>
            static Result
            call(State const& state,It0 const&, F)
            {
                return static_cast<Result>(state);
            }

            static type
            call(StateRef state, Seq& seq, F f)
            {
                typedef
                    unrolled_reverse_fold<
                        type
                      , SeqSize
                    >
                unrolled_impl;
                return unrolled_impl::call(
                    state,
                    fusion::prior( fusion::end(seq)),
                    f);
            }

            static StateRef
            call(StateRef state, Seq&, F)
            {
                return static_cast<StateRef>(state);
            }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f)
    {
        return result_of::reverse_fold<Seq,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f)
    {
        return result_of::reverse_fold<Seq const,State const,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f)
    {
        return result_of::reverse_fold<Seq,State,F>::call(
            state,
            seq,
            f);
    }

    template<typename Seq, typename State, typename F>
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f)
    {
        return result_of::reverse_fold<Seq const,State,F>::call(
            state,
            seq,
            f);
    }


            static type
            call(First const& first, mpl::false_)
            {
                return fusion::next(convert_iterator<First>::call(first));
            }


    template <typename Sequence, typename First, typename Last>
    typename result_of::erase<Sequence const, First, Last>::type
    erase(Sequence const& seq, First const& first, Last const& last)
    {
        typedef result_of::erase<Sequence const, First, Last> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::type result_type;

        left_type left(fusion::begin(seq), first);
        right_type right(last, fusion::end(seq));
        return result_type(left, right);
    }

    
    template <typename T, typename Sequence>
    inline typename result_of::filter<Sequence const, T>::type
    filter(Sequence const& seq)
    {
        return filter_view<const Sequence, is_same<mpl::_, T> >(seq);
    }


    template<typename LhSequence, typename RhSequence>
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }


    template <typename Sequence>
    inline typename result_of::clear<Sequence const>::type
    clear(Sequence const& /*seq*/)
    {
        return vector0<>();
    }

    
    template <typename Pred, typename Sequence>
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }


    template <typename Sequence, typename Position, typename Range>
    inline typename result_of::insert_range<Sequence const, Position, Range const>::type
    insert_range(Sequence const& seq, Position const& pos, Range const& range)
    {
        typedef result_of::insert_range<Sequence const, Position, Range const> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::left_insert_type left_insert_type;
        typedef typename result_of::type result;

        left_type left(fusion::begin(seq), convert_iterator<Position>::call(pos));
        right_type right(convert_iterator<Position>::call(pos), fusion::end(seq));
        left_insert_type left_insert(left, range);
        return result(left_insert, right);
    }


    template <typename Sequence>
    inline typename result_of::pop_front<Sequence const>::type
    pop_front(Sequence const& seq)
    {
        typedef typename result_of::pop_front<Sequence const>::type result;
        return result(fusion::next(fusion::begin(seq)), fusion::end(seq));
    }


        pop_back_iterator(Iterator_ const& iterator_base)
            : base_type(iterator_base) {}


            static type
            call(BaseIterator const& i)
            {
                return type(i);
            }


            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(i.iterator_base));
            }


            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(
                    fusion::prior(i.iterator_base)));
            }


    template <typename Sequence>
    inline typename result_of::pop_back<Sequence const>::type
    pop_back(Sequence const& seq)
    {
        typedef result_of::pop_back<Sequence const> comp;
        typedef typename comp::begin_type begin_type;
        typedef typename comp::end_type end_type;
        typedef typename comp::type result;

        return result(
            begin_type(fusion::begin(seq))
          , end_type(fusion::end(seq))
        );
    }


    template <typename T, typename Sequence>
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }


    template <typename Pred, typename Sequence>
    inline typename result_of::remove_if<Sequence const, Pred>::type
    remove_if(Sequence const& seq)
    {
        typedef typename result_of::remove_if<Sequence const, Pred>::type result_type;
        return result_type(seq);
    }


    template <typename Key, typename Sequence>
    inline typename result_of::erase_key<Sequence const, Key>::type
    erase_key(Sequence const& seq)
    {
        return erase(seq, find<Key>(seq));
    }

        template <typename U, typename T>
        static U&
        call(U& x, T const&, T const&)
        {
            return x;
        }

        template <typename U, typename T>
        static U
        call(U& x, T const& old_value, T const& new_value)
        {
            return (x == old_value) ? new_value : x;
        }

        replacer(T const& in_old_value, T const& in_new_value)
            : old_value(in_old_value), new_value(in_new_value) {}

    
        template <typename U>
        typename result<replacer(U)>::type
        operator()(U const& x) const
        {
            return replacer_helper<is_convertible<T, U>::value>::
                call(x, old_value, new_value);
        }

        template <typename U, typename F, typename T>
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }

        template <typename U, typename F, typename T>
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }

        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

    
        template <typename U>
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

    template<typename T0 , typename T1>
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }

    template<typename T0 , typename T1 , typename T2>
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }

    template<typename T0 , typename T1>
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }

    template<typename T0 , typename T1 , typename T2>
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }

    template<typename T0 , typename T1>
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }

    template<typename T0 , typename T1 , typename T2>
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }

    template<typename T0 , typename T1>
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }

    template<typename T0 , typename T1 , typename T2>
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }

    template<typename T0 , typename T1>
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }

    template<typename T0 , typename T1 , typename T2>
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }


    template <typename Sequence, typename F>
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }


    template <typename Sequence, typename F>
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }


    template <typename T, typename Sequence>
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq)
    {
        typedef typename result_of::find<Sequence const, T>::filter filter;
        return filter::call(seq);
    }


    template <typename Sequence, typename F>
    inline bool
    none(Sequence const& seq, F f)
    {
        return !fusion::any(seq, f);
    }


    template <typename Pred, typename Sequence>
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq)
    {
        typedef typename result_of::find_if<Sequence const, Pred>::filter filter;
        return filter::call(seq);
    }

    template <typename First, typename Last, typename F>
    inline bool
    linear_any(First const&, Last const&, F const&, mpl::true_)
    {
        return false;
    }


    template <typename Sequence, typename F, typename Tag>
    inline bool
    any(Sequence const& seq, F f, Tag)
    {
        return detail::linear_any(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) || 
                f(*fusion::advance_c<1>(it))||
                f(*fusion::advance_c<2>(it)) ||
                f(*fusion::advance_c<3>(it)) ||
                detail::unrolled_any<N-4>::call(fusion::advance_c<4>(it), f);
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) || 
                f(*fusion::advance_c<1>(it)) ||
                f(*fusion::advance_c<2>(it));
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) || 
                f(*fusion::advance_c<1>(it));
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return f(*it);
        }

        template <typename It, typename F>
        static bool call(It const&, F)
        {
            return false;
        }


    template <typename Sequence, typename F>
    inline bool
    any(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_any<result_of::distance<begin, end>::type::value>::call(
            fusion::begin(seq), f);
    }

    template <typename First, typename Last, typename F>
    inline int
    linear_count_if(First const&, Last const&, F const&, mpl::true_)
    {
        return 0;
    }


    template <typename Sequence, typename F, typename Tag>
    inline int
    count_if(Sequence const& seq, F f, Tag)
    {
        return detail::linear_count_if(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

        template<typename I0, typename F>
        static int call(I0 const& i0, F f)
        {
            int ct = unrolled_count_if<n-4>::
                call(fusion::advance_c<4>(i0), f);
            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            if(f(*i2))
                ++ct;

            typedef typename result_of::next<I2>::type I3;
            I3 i3(fusion::next(i2));
            if(f(*i3))
                ++ct;

            return ct;
        }

        template<typename I0, typename F>
        static int call(I0 const& i0, F f)
        {
            int ct = 0;
            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            typedef typename result_of::next<I1>::type I2;
            I2 i2(fusion::next(i1));
            if(f(*i2))
                ++ct;

            return ct;
        }

        template<typename I0, typename F>
        static int call(I0 const& i0, F f)
        {
            int ct = 0;

            if(f(*i0))
                ++ct;

            typedef typename result_of::next<I0>::type I1;
            I1 i1(fusion::next(i0));
            if(f(*i1))
                ++ct;

            return ct;
        }

        template<typename I0, typename F>
        static int call(I0 const& i0, F f)
        {
            int ct = 0;
            if(f(*i0))
                ++ct;
            return ct;
        }

        template<typename I0, typename F>
        static int call(I0 const&, F)
        {
            return 0;
        }


    template <typename Sequence, typename F>
    inline int
    count_if(Sequence const& seq, F f, random_access_traversal_tag)
    {
        typedef typename result_of::begin<Sequence>::type begin;
        typedef typename result_of::end<Sequence>::type end;
        return detail::unrolled_count_if<result_of::distance<begin, end>::type::value>::
            call(fusion::begin(seq), f);
    }

    template <typename First, typename Last, typename F>
    inline bool
    linear_all(First const&, Last const&, F const&, mpl::true_)
    {
        return true;
    }


    template <typename Sequence, typename F, typename Tag>
    inline bool
    all(Sequence const& seq, F f, Tag)
    {
        return detail::linear_all(
                fusion::begin(seq)
              , fusion::end(seq)
              , f
              , result_of::equal_to<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>());
    }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) && 
                f(*fusion::advance_c<1>(it))&&
                f(*fusion::advance_c<2>(it)) &&
                f(*fusion::advance_c<3>(it)) &&
                detail::unrolled_all<N-4>::call(fusion::advance_c<4>(it), f);
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) && 
                f(*fusion::advance_c<1>(it)) &&
                f(*fusion::advance_c<2>(it));
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return 
                f(*it) && 
                f(*fusion::advance_c<1>(it));
        }

        template <typename It, typename F>
        static bool call(It const& it, F f)
        {
            return f(*it);
        }

        template <typename It, typename F>
        static bool call(It const& /*it*/, F /*f*/)
        {
            return true;
        }

        template <typename T1, typename T2>
        static bool
        call(T1 const& x, T2 const& y)
        {
            return x == y;
        }

        template <typename T1, typename T2>
        static bool
        call(T1 const&, T2 const&)
        {
            return false;
        }

        count_compare(param in_x)
            : x(in_x) {}


        template <typename T2>
        bool
        operator()(T2 const& y)
        {
            return 
                compare_convertible<
                    mpl::or_<
                        is_convertible<T1, T2>
                      , is_convertible<T2, T1> 
                    >::value
                >::call(x, y);
        }


        template <typename Iterator>
        static type
        recursive_call(Iterator const& iter, mpl::true_)
        {
            return iter;
        }


        template <typename Iterator>
        static type
        recursive_call(Iterator const& iter)
        {
            typedef result_of::equal_to<Iterator, type> found;
            return recursive_call(iter, found());
        }


        template <typename Iterator, typename Tag>
        static type
        choose_call(Iterator const& iter, Tag)
        {
            return recursive_call(iter);
        }


        template <typename Iterator>
        static type
        choose_call(Iterator const& iter, random_access_traversal_tag)
        {
            typedef typename result_of::distance<Iterator, type>::type N;
            return fusion::advance<N>(iter);
        }


        template <typename Iterator>
        static type
        iter_call(Iterator const& iter)
        {
            return choose_call(iter, typename traits::category_of<Iterator>::type());
        }


        template <typename Sequence>
        static type
        call(Sequence& seq)
        {
            return iter_call(fusion::begin(seq));
        }


            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_if_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }


            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }


            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , segmented_find_if_fun<Pred>());
            }


            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }


            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }


            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , detail::segmented_find_fun<T>());
            }


            template <typename I1, typename I2>
            static void
            call(I1 const&, I2 const&, mpl::true_)
            {
            }


            template <typename I1, typename I2>
            static void
            call(I1 const& src, I2 const& dest)
            {
                typename result_of::equal_to<I1, end1_type>::type eq;
                return call(src, dest, eq);
            }


    template <typename Tag, typename Sequence>
    inline typename result_of::convert<Tag, Sequence>::type
    convert(Sequence& seq)
    {
        typedef typename result_of::convert<Tag, Sequence>::gen gen;
        return gen::call(seq);
    }


    template <typename Tag, typename Sequence>
    inline typename result_of::convert<Tag, Sequence const>::type
    convert(Sequence const& seq)
    {
        typedef typename result_of::convert<Tag, Sequence const>::gen gen;
        return gen::call(seq);
    }

    template <typename Sequence>
    inline std::ostream&
    out(std::ostream& os, Sequence& seq)
    {
        detail::print_sequence(os, seq);
        return os;
    }

    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

        template <typename Tag>
        int get_xalloc_index(Tag* = 0)
        {
            // each Tag will have a unique index
            static int index = std::ios::xalloc();
            return index;
        }

                ~arena()
                {
                    for (
                        typename std::vector<T*>::iterator i = data.begin()
                      ; i != data.end()
                      ; ++i)
                    {
                        delete *i;
                    }
                }


            static void attach(Stream& stream, T const& data)
            {
                static arena ar; // our arena
                ar.data.push_back(new T(data));
                stream.pword(get_xalloc_index<Tag>()) = ar.data.back();
            }


            static T const* get(Stream& stream)
            {
                return (T const*)stream.pword(get_xalloc_index<Tag>());
            }


            string_ios_manip(Stream& str_)
                : stream(str_)
            {}


            void
            set(string_type const& s)
            {
                stream_data_t::attach(stream, s);
            }


            void
            print(char const* default_) const
            {
                // print a delimiter
                string_type const* p = stream_data_t::get(stream);
                if (p)
                    stream << *p;
                else
                    stream << default_;
            }


            void
            read(char const* default_) const
            {
                // read a delimiter
                string_type const* p = stream_data_t::get(stream);
                using namespace std;
                ws(stream);

                if (p)
                {
                    typedef typename string_type::const_iterator iterator;
                    for (iterator i = p->begin(); i != p->end(); ++i)
                        check_delim(*i);
                }
                else
                {
                    while (*default_)
                        check_delim(*default_++);
                }
            }


            template <typename Char>
            void
            check_delim(Char c) const
            {
                if (!isspace(c))
                {
                    if (stream.get() != c)
                    {
                        stream.unget();
                        stream.setstate(std::ios::failbit);
                    }
                }
            }
                                                                      \
                                                                                \
        template <typename Stream, typename Char, typename Traits>              \
        Stream& operator>>(Stream& s, const name##_type<Char,Traits>& m)        \
        {                                                                       \
            string_ios_manip<name##_tag, Stream>(s).set(m.data);                \
            return s;                                                           \
        }                                                                       \
                                                                                \
        template <typename Stream, typename Char, typename Traits>              \
        Stream& operator<<(Stream& s, const name##_type<Char,Traits>& m)        \
        {                                                                       \
            string_ios_manip<name##_tag, Stream>(s).set(m.data);                \
            return s;                                                           \
        }                                                                       \
    }                                                                           \

#endif // defined(BOOST_NO_TEMPLATED_STREAMS)

    STD_TUPLE_DEFINE_MANIPULATOR(tuple_open)
                                                                       \
                                                                                \
        template <typename Stream, typename Char, typename Traits>              \
        Stream& operator<<(Stream& s, const name##_type<Char,Traits>& m)        \
        {                                                                       \
            string_ios_manip<name##_tag, Stream>(s).set(m.data);                \
            return s;                                                           \
        }                                                                       \
    }                                                                           \

#endif // defined(BOOST_NO_TEMPLATED_STREAMS)

    STD_TUPLE_DEFINE_MANIPULATOR(tuple_open)

        template <typename OS>
        static void
        print(OS& os, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, OS> manip(os);
            manip.print(delim);
        }

        template <typename OS, typename First, typename Last>
        static void
        call(OS&, First const&, Last const&, mpl::true_)
        {
        }


        template <typename OS, typename First, typename Last>
        static void
        call(OS& os, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(os, first, last, eq);
        }


    template <typename OS, typename Sequence>
    inline void
    print_sequence(OS& os, Sequence const& seq)
    {
        delimiter_out<tuple_open_tag>::print(os, "(");
        print_sequence_loop::call(os, fusion::begin(seq), fusion::end(seq));
        delimiter_out<tuple_close_tag>::print(os, ")");
    }

        template <typename IS>
        static void
        read(IS& is, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, IS> manip(is);
            manip.read(delim);
        }

        template <typename IS, typename First, typename Last>
        static void
        call(IS&, First const&, Last const&, mpl::true_)
        {
        }


        template <typename IS, typename First, typename Last>
        static void
        call(IS& is, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(is, first, last, eq);
        }


    template <typename IS, typename Sequence>
    inline void
    read_sequence(IS& is, Sequence& seq)
    {
        delimiter_in<tuple_open_tag>::read(is, "(");
        read_sequence_loop::call(is, fusion::begin(seq), fusion::end(seq));
        delimiter_in<tuple_close_tag>::read(is, ")");
    }

    template <typename Seq1, typename Seq2>
    inline bool
    not_equal_to(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return result_of::size<Seq1>::value != result_of::size<Seq2>::value
            || detail::sequence_not_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a == b);
#endif
    }

    template <typename Seq1, typename Seq2>
    inline bool
    equal_to(Seq1 const& a, Seq2 const& b)
    {
        return result_of::size<Seq1>::value == result_of::size<Seq2>::value
            && detail::sequence_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
    }

    template <typename Seq1, typename Seq2>
    inline bool
    greater_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a < b);
#endif
    }

    template <typename Seq1, typename Seq2>
    inline bool
    greater(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return (b < a);
#endif
    }

    template <typename Seq1, typename Seq2>
    inline bool
    less_equal(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_less_equal<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(b < a);
#endif
    }

    template <typename Seq1, typename Seq2>
    inline bool
    less(Seq1 const& a, Seq2 const& b)
    {
        return detail::sequence_less<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
    }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }

        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            return true;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }

        template <typename I1, typename I2>
        static bool
        call(I1 const& /*a*/, I2 const& /*b*/)
        {
            return false;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }


        template <typename I1, typename I2>
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }


    template <typename N, typename Sequence>
    inline typename result_of::at<Sequence const, N>::type
    at(Sequence const& seq)
    {
        return result_of::at<Sequence const, N>::call(seq);
    }

    
    template <typename Sequence>
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }


    template <typename Sequence>
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }


    template <typename Sequence>
    inline typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq)
    {
        typedef typename traits::tag_of<Sequence const>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence const>::call(seq);
    }


    template <typename Sequence>
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        typedef typename result_of::size<Sequence>::type result;
        return result();
    }


                static type
                call(Seq& seq)
                {
                    return fusion::deref_data(fusion::find<Key>(seq));
                }


    template <typename Key, typename Sequence>
    inline typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq)
    {
        return result_of::at_key<Sequence const, Key>::call(seq);
    }


    template <typename Key, typename Sequence>
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const&)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }

    
    template <typename Sequence>
    inline typename result_of::back<Sequence>::type
    back(Sequence& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }


    template <typename Sequence>
    inline typename result_of::back<Sequence const>::type
    back(Sequence const& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }


            template<typename Elem>
            void operator()(Elem const& e) const
            {
                using std::swap;
                swap(front(e), back(e));
            }


    template <typename Sequence>
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        typedef typename result_of::empty<Sequence>::type result;
        return result();
    }


            static type call(Sequence& seq, State const&, Context const& context, segmented_begin_fun)
            {
                return type(range_type(fusion::begin(seq), fusion::end(seq)), context);
            }


        static type call(Sequence& seq, Stack stack)
        {
            return type(pair_type(fusion::begin(seq), fusion::end(seq)), stack);
        }


        static type call(Sequence & seq, Stack stack)
        {
            end_type end = fusion::end(fusion::segments(seq));
            return type(pair_type(end, end), stack);
        }


        static type call(Sequence & seq)
        {
            return type(
                segmented_end_impl<Sequence, Nil>::call(seq, Nil()));
        }


        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil>::call(seq, Nil()));
        }


    template <typename Iterator>
    typename result_of::prior<Iterator>::type const
    prior(Iterator const& i)
    {
        return result_of::prior<Iterator>::call(i);
    }


    template <typename It>
    typename result_of::deref_data<It>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }


    template <typename Iterator>
    typename result_of::next<Iterator>::type const
    next(Iterator const& i)
    {
        return result_of::next<Iterator>::call(i);
    }

        
    template <typename First, typename Last>
    inline typename result_of::distance<First, Last>::type
    distance(First const& a, Last const& b)
    {
        return result_of::distance<First, Last>::call(a,b);
    }


        iterator_adapter(iterator_base_type const& iterator_base_)
            : iterator_base(iterator_base_) {}


            static type
            call(Iterator const& it)
            {
                return type(fusion::advance<N>(it.iterator_base));
            }


            static type
            call(Iterator const& it)
            {
                return fusion::deref(it.iterator_base);
            }


            static type
            call(Iterator const& i)
            {
                return type(fusion::next(i.iterator_base));
            }


            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(i.iterator_base));
            }


            static type
            call(It const& it)
            {
                return type(*it.seq,0);
            }


            static
            type
            call(It1 const&, It2 const&)
            {
                return type();
            }


        template<typename OtherSeq>
        basic_iterator(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
          : seq(it.seq)
        {}


        basic_iterator(Seq& in_seq, int)
          : seq(&in_seq)
        {}


        template<typename OtherSeq>
        basic_iterator&
        operator=(basic_iterator<Tag,Category,OtherSeq,Index> const& it)
        {
            seq=it.seq;
            return *this;
        }


    template <typename Iterator>
    typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        return deref_meta::call(i);
    }


    template <typename Iterator>
    typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }


    template <int N, typename Iterator>
    inline typename result_of::advance_c<Iterator, N>::type const
    advance_c(Iterator const& i)
    {
        return result_of::advance_c<Iterator, N>::call(i);
    }


    template<typename N, typename Iterator>
    inline typename result_of::advance<Iterator, N>::type const
    advance(Iterator const& i)
    {
        return result_of::advance<Iterator, N>::call(i);
    }

        explicit segmented_iterator(Context const& ctx)
          : context(ctx)
        {}


            static type call(It const& it)
            {
                return *it.context.car.first;
            }


            static type call(It const& it)
            {
                return fusion::deref_data(it.context.car.first);
            }


            static type call(It const& it)
            {
                return type(impl::call(it.context));
            }


            static type call(Stack const & stack)
            {
                return type(
                    car_type(fusion::next(stack.car.first), stack.car.last),
                    stack.cdr);
            }


            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }


            static type call(Stack const & stack)
            {
                return type(range_type(stack.car.last, stack.car.last));
            }


            static type call(Stack const & stack)
            {
                return segmented_begin_impl<Sequence, Stack>::call(*stack.car.first, stack);
            }


            static type call(Stack const& stack)
            {
                return segmented_next_impl_recurse<typename Stack::cdr_type>::call(stack.cdr);
            }


            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }


            static type call(Stack const & stack)
            {
                return impl::call(pop_front_car<Stack>::call(stack));
            }


            static type call(Stack const & stack)
            {
                return impl::call(stack.cdr);
            }


            static type call(Stack const & stack)
            {
                return pop_front_car<Stack>::call(stack);
            }


            static type
            call(Iterator const& i)
            {
                return *i.first;
            }


        explicit segment_sequence(Sequence const & seq)
            : sequence(seq)
        {}


            static type call(Sequence & seq)
            {
                return seq.sequence;
            }


        static T const&
        call(T const& x, mpl::true_)
        {
            return x;
        }

        unused_type()
        {
        }


        template <typename T>
        unused_type(T const&)
        {
        }


        template <typename T>
        unused_type const&
        operator=(T const&) const
        {
            return *this;
        }


        template <typename T>
        unused_type&
        operator=(T const&)
        {
            return *this;
        }


        unused_type const&
        operator=(unused_type const&) const
        {
            return *this;
        }


        unused_type&
        operator=(unused_type const&)
        {
            return *this;
        }

            unused_only(unused_type const&) {}


    inline std::ostream& operator<<(std::ostream& out, detail::unused_only const&)
    {
        return out;
    }


    inline std::istream& operator>>(std::istream& in, unused_type&)
    {
        return in;
    }

        Sequence const&
        derived() const
        {
            return static_cast<Sequence const&>(*this);
        }


        Sequence&
        derived()
        {
            return static_cast<Sequence&>(*this);
        }


        operator detail::from_sequence_convertible_type()const
        {
            return detail::from_sequence_convertible_type();
        }


    template <typename Sequence, typename State, typename Fun>
    typename result_of::segmented_fold_until<Sequence const, State, Fun>::type
    segmented_fold_until(Sequence const& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence const, State, Fun>::filter
        filter;
        
        return filter::call(seq, state, fusion::nil(), fun);
    }

        pair()
            : second() {}


        template <typename Second2>
        pair(pair<First, Second2> const& rhs)
            : second(rhs.second) {}


        template <typename Second2>
        pair& operator=(pair<First, Second2> const& rhs)
        {
            second = rhs.second;
            return *this;
        }


    template <typename First, typename Second>
    inline typename result_of::make_pair<First,Second>::type
    make_pair(Second const& val)
    {
        return pair<First, typename detail::as_fusion_element<Second>::type>(val);
    }


    template <typename First, typename Second>
    inline std::ostream&
    operator<<(std::ostream& os, pair<First, Second> const& p)
    {
        os << p.second;
        return os;
    }


    template <typename First, typename Second>
    inline std::istream&
    operator>>(std::istream& is, pair<First, Second>& p)
    {
        is >> p.second;
        return is;
    }


    template <typename First, typename SecondL, typename SecondR>
    inline bool
    operator==(pair<First, SecondL> const& l, pair<First, SecondR> const& r)
    {
        return l.second == r.second;
    }


    template <typename First, typename SecondL, typename SecondR>
    inline bool
    operator!=(pair<First, SecondL> const& l, pair<First, SecondR> const& r)
    {
        return l.second != r.second;
    }

    template <typename T>
    const T& as_const(const T& obj)
    {
        return obj;
    }

        Iterator const&
        cast() const
        {
            return static_cast<Iterator const&>(*this);
        }


        Iterator&
        cast()
        {
            return static_cast<Iterator&>(*this);
        }


    template <typename Cur, typename Context>
    typename result_of::make_segmented_iterator<Cur, Context>::type
    make_segmented_iterator(Cur const& cur, Context const& context)
    {
        typedef result_of::make_segmented_iterator<Cur, Context> impl_type;
        typedef typename impl_type::type type;
        typedef typename impl_type::range_type range_type;
        return type(cons<range_type, Context>(range_type(cur, fusion::end(*context.car.first)), context));
    }


            static type call(Cur const& cur, End const& end, Context const& context)
            {
                return cons<range_type, Context>(range_type(cur, end), context);
            }


            static type call(Sequence& seq, State const& state, Context const& context, Fun const& fun)
            {
                return impl::call(fusion::segments(seq), state, context, fun);
            }


            static type call(Sequence& seq, State const& state, Context const& context, Fun const& fun)
            {
                return apply_type::call(seq, state, context, fun);
            }


            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return call(beg, end, state, context, fun, typename fold_recurse_impl::continue_type());
            }


            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return impl::call(fusion::next(beg), end, state, context, fun);
            }


            static type call(Begin const& beg, End const& end, State const& state
                           , Context const& context, Fun const& fun)
            {
                return impl::call(beg, end, state, context, fun);
            }


            static type call(Begin const&, End const&, State const& state
                           , Context const&, Fun const&)
            {
                return state;
            }


            static type call(Segments& segs, State const& state, Context const& context, Fun const& fun)
            {
                return impl::call(fusion::begin(segs), fusion::end(segs), state, context, fun);
            }

        tuple()
            : base_type() {}

        tuple(tuple const& rhs)
            : base_type(rhs) {}

    template <typename U0>
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        : base_type(rhs) {}

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

        template <typename T>
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple()
            : base_type() {}

        tuple(tuple const& rhs)
            : base_type(rhs) {}

    template <typename U0>
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
        : base_type(rhs) {}

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

        template <typename T>
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple()
            : base_type() {}

        tuple(tuple const& rhs)
            : base_type(rhs) {}

    template <typename U0>
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
        : base_type(rhs) {}

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

        template <typename T>
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple()
            : base_type() {}

        tuple(tuple const& rhs)
            : base_type(rhs) {}

    template <typename U0>
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        : base_type(rhs) {}

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

        template <typename T>
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple()
            : base_type() {}

        tuple(tuple const& rhs)
            : base_type(rhs) {}

    template <typename U0>
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
        : base_type(rhs) {}

    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39 , typename U40 , typename U41 , typename U42 , typename U43 , typename U44 , typename U45 , typename U46 , typename U47 , typename U48 , typename U49>
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39 , U40 , U41 , U42 , U43 , U44 , U45 , U46 , U47 , U48 , U49> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

        template <typename T>
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
