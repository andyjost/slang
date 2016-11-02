

template<class T> bool ref_compare( T const & a, T const & b, long )
{
    return a == b;
}


template<class R, class F, class L> bool ref_compare( bind_t<R, F, L> const & a, bind_t<R, F, L> const & b, int )
{
    return a.compare( b );
}


    value(T const & t): t_(t) {}


    T & get() { return t_; }

    T const & get() const { return t_; }


    bool operator==(value const & rhs) const
    {
        return t_ == rhs.t_;
    }


template<class T> bool ref_compare( value< weak_ptr<T> > const & a, value< weak_ptr<T> > const & b, int )
{
    return !(a.get() < b.get()) && !(b.get() < a.get());
}

    static inline F & unwrap( F & f, long )
    {
        return f;
    }


    list0() {}


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A &, long)
    {
        return unwrapper<F>::unwrap(f, 0)();
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A &, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)();
    }


    template<class F, class A> void operator()(type<void>, F & f, A &, int)
    {
        unwrapper<F>::unwrap(f, 0)();
    }


    template<class F, class A> void operator()(type<void>, F const & f, A &, int) const
    {
        unwrapper<F const>::unwrap(f, 0)();
    }


    template<class V> void accept(V &) const
    {
    }


    bool operator==(list0 const &) const
    {
        return true;
    }


    explicit list1( A1 a1 ): base_type( a1 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] ( _bi::value<T> & v ) const { return v.get(); }


    template<class T> T const & operator[] ( _bi::value<T> const & v ) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list1 const & rhs) const
    {
        return ref_compare(base_type::a1_, rhs.a1_, 0);
    }


    list2( A1 a1, A2 a2 ): base_type( a1, a2 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_]);
    }


    template<class A> bool operator()( type<bool>, logical_and & /*f*/, A & a, int )
    {
        return a[ base_type::a1_ ] && a[ base_type::a2_ ];
    }


    template<class A> bool operator()( type<bool>, logical_and const & /*f*/, A & a, int ) const
    {
        return a[ base_type::a1_ ] && a[ base_type::a2_ ];
    }


    template<class A> bool operator()( type<bool>, logical_or & /*f*/, A & a, int )
    {
        return a[ base_type::a1_ ] || a[ base_type::a2_ ];
    }


    template<class A> bool operator()( type<bool>, logical_or const & /*f*/, A & a, int ) const
    {
        return a[ base_type::a1_ ] || a[ base_type::a2_ ];
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list2 const & rhs) const
    {
        return ref_compare(base_type::a1_, rhs.a1_, 0) && ref_compare(base_type::a2_, rhs.a2_, 0);
    }


    list3( A1 a1, A2 a2, A3 a3 ): base_type( a1, a2, a3 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list3 const & rhs) const
    {
        return
            
            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 );
    }


    list4( A1 a1, A2 a2, A3 a3, A4 a4 ): base_type( a1, a2, a3, a4 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list4 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 );
    }


    list5( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ): base_type( a1, a2, a3, a4, a5 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list5 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 );
    }


    list6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ): base_type( a1, a2, a3, a4, a5, a6 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list6 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 );
    }


    list7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ): base_type( a1, a2, a3, a4, a5, a6, a7 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list7 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 );
    }


    list8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ): base_type( a1, a2, a3, a4, a5, a6, a7, a8 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list8 const & rhs) const
    {
        return
            
            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 ) &&
            ref_compare( base_type::a8_, rhs.a8_, 0 );
    }


    list9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9 ): base_type( a1, a2, a3, a4, a5, a6, a7, a8, a9 ) {}


    A1 operator[] (boost::arg<1>) const { return base_type::a1_; }


    template<class T> T & operator[] (_bi::value<T> & v) const { return v.get(); }


    template<class T> T const & operator[] (_bi::value<T> const & v) const { return v.get(); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> & b) const { return b.eval(*this); }


    template<class R, class F, class L> typename result_traits<R, F>::type operator[] (bind_t<R, F, L> const & b) const { return b.eval(*this); }


    template<class R, class F, class A> R operator()(type<R>, F & f, A & a, long)
    {
        return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }


    template<class R, class F, class A> R operator()(type<R>, F const & f, A & a, long) const
    {
        return unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }


    template<class F, class A> void operator()(type<void>, F & f, A & a, int)
    {
        unwrapper<F>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }


    template<class F, class A> void operator()(type<void>, F const & f, A & a, int) const
    {
        unwrapper<F const>::unwrap(f, 0)(a[base_type::a1_], a[base_type::a2_], a[base_type::a3_], a[base_type::a4_], a[base_type::a5_], a[base_type::a6_], a[base_type::a7_], a[base_type::a8_], a[base_type::a9_]);
    }


    template<class V> void accept(V & v) const
    {
        base_type::accept(v);
    }


    bool operator==(list9 const & rhs) const
    {
        return

            ref_compare( base_type::a1_, rhs.a1_, 0 ) &&
            ref_compare( base_type::a2_, rhs.a2_, 0 ) &&
            ref_compare( base_type::a3_, rhs.a3_, 0 ) &&
            ref_compare( base_type::a4_, rhs.a4_, 0 ) &&
            ref_compare( base_type::a5_, rhs.a5_, 0 ) &&
            ref_compare( base_type::a6_, rhs.a6_, 0 ) &&
            ref_compare( base_type::a7_, rhs.a7_, 0 ) &&
            ref_compare( base_type::a8_, rhs.a8_, 0 ) &&
            ref_compare( base_type::a9_, rhs.a9_, 0 );
    }


    bind_t(F f, L const & l): f_(f), l_(l) {}


template<class R, class F, class L> bool function_equal( bind_t<R, F, L> const & a, bind_t<R, F, L> const & b )
{
    return a.compare(b);
}

    template<class V> bool operator()(V const & v) const { return !v; }


template<class R, class F, class L>
    bind_t< bool, logical_not, list1< bind_t<R, F, L> > >
    operator! (bind_t<R, F, L> const & f)
{
    typedef list1< bind_t<R, F, L> > list_type;
    return bind_t<bool, logical_not, list_type> ( logical_not(), list_type(f) );
}
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

BOOST_BIND_OPERATOR( &&, logical_and )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

BOOST_BIND_OPERATOR( &&, logical_and )
 \
    template<class V, class W> bool operator()(V const & v, W const & w) const { return v op w; } \
}; \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

BOOST_BIND_OPERATOR( &&, logical_and )
BOOST_BIND_OPERATOR( ||, logical_or )
 \
 template<class R, class F, class L, class A2> \
    bind_t< bool, name, list2< bind_t<R, F, L>, typename add_value<A2>::type > > \
    operator op (bind_t<R, F, L> const & f, A2 a2) \
{ \
    typedef typename add_value<A2>::type B2; \
    typedef list2< bind_t<R, F, L>, B2> list_type; \
    return bind_t<bool, name, list_type> ( name(), list_type(f, a2) ); \
}

BOOST_BIND_OPERATOR( ==, equal )
BOOST_BIND_OPERATOR( !=, not_equal )

BOOST_BIND_OPERATOR( <, less )
BOOST_BIND_OPERATOR( <=, less_equal )

BOOST_BIND_OPERATOR( >, greater )
BOOST_BIND_OPERATOR( >=, greater_equal )

BOOST_BIND_OPERATOR( &&, logical_and )
BOOST_BIND_OPERATOR( ||, logical_or )


template<class V, class T> void visit_each( V & v, value<T> const & t, int )
{
    using boost::visit_each;
    BOOST_BIND_VISIT_EACH( v, t.get(), 0 );
}


template<class V, class R, class F, class L> void visit_each( V & v, bind_t<R, F, L> const & t, int )
{
    t.accept( v );
}


template<class R, class F>
    _bi::bind_t<R, F, _bi::list0>
    BOOST_BIND(F f)
{
    typedef _bi::list0 list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type());
}


template<class R, class F, class A1>
    _bi::bind_t<R, F, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(F f, A1 a1)
{
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1));
}


template<class R, class F, class A1, class A2>
    _bi::bind_t<R, F, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(F f, A1 a1, A2 a2)
{
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1, a2));
}


template<class R, class F, class A1, class A2, class A3>
    _bi::bind_t<R, F, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
}


template<class R, class F, class A1, class A2, class A3, class A4>
    _bi::bind_t<R, F, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
}


template<class R, class F, class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, F, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}


template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, F, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}


template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, F, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}


template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, F, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}


template<class R, class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, F, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}


template<class F>
    _bi::bind_t<_bi::unspecified, F, _bi::list0>
    BOOST_BIND(F f)
{
    typedef _bi::list0 list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type());
}


template<class F, class A1>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(F f, A1 a1)
{
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type(a1));
}


template<class F, class A1, class A2>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(F f, A1 a1, A2 a2)
{
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type> (f, list_type(a1, a2));
}


template<class F, class A1, class A2, class A3>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3)
{
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3));
}


template<class F, class A1, class A2, class A3, class A4>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4));
}


template<class F, class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}


template<class F, class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}


template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<_bi::unspecified, F, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(F f, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<_bi::unspecified, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}


    template<class U> R const & call(U & u, T const *) const
    {
        return (u.*f_);
    }


    template<class U> R const & call(U & u, void const *) const
    {
        return (get_pointer(u)->*f_);
    }

    
    explicit dm(F f): f_(f) {}


    R & operator()(T * p) const
    {
        return (p->*f_);
    }


    R const & operator()(T const * p) const
    {
        return (p->*f_);
    }


    template<class U> R const & operator()(U const & u) const
    {
        return call(u, &u);
    }


    bool operator==(dm const & rhs) const
    {
        return f_ == rhs.f_;
    }


    bool operator!=(dm const & rhs) const
    {
        return f_ != rhs.f_;
    }


template<class R, class T> _mfi::dm<R, T> mem_fn(R T::*f)
{
    return _mfi::dm<R, T>(f);
}

    explicit storage1( A1 a1 ): a1_( a1 ) {}


    template<class V> void accept(V & v) const
    {
        BOOST_BIND_VISIT_EACH(v, a1_, 0);
    }


    storage2( A1 a1, A2 a2 ): storage1<A1>( a1 ), a2_( a2 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a2_, 0);
    }


    storage3( A1 a1, A2 a2, A3 a3 ): storage2<A1, A2>( a1, a2 ), a3_( a3 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a3_, 0);
    }


    storage4( A1 a1, A2 a2, A3 a3, A4 a4 ): storage3<A1, A2, A3>( a1, a2, a3 ), a4_( a4 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a4_, 0);
    }


    storage5( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ): storage4<A1, A2, A3, A4>( a1, a2, a3, a4 ), a5_( a5 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a5_, 0);
    }


    storage6( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ): storage5<A1, A2, A3, A4, A5>( a1, a2, a3, a4, a5 ), a6_( a6 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a6_, 0);
    }


    storage7( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ): storage6<A1, A2, A3, A4, A5, A6>( a1, a2, a3, a4, a5, a6 ), a7_( a7 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a7_, 0);
    }


    storage8( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ): storage7<A1, A2, A3, A4, A5, A6, A7>( a1, a2, a3, a4, a5, a6, a7 ), a8_( a8 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a8_, 0);
    }


    storage9( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9 ): storage8<A1, A2, A3, A4, A5, A6, A7, A8>( a1, a2, a3, a4, a5, a6, a7, a8 ), a9_( a9 ) {}


    template<class V> void accept(V & v) const
    {
        inherited::accept(v);
        BOOST_BIND_VISIT_EACH(v, a9_, 0);
    }


    explicit protected_bind_t(F f): f_(f)
    {
    }


    result_type operator()()
    {
        return f_();
    }


    result_type operator()() const
    {
        return f_();
    }


    template<class A1> result_type operator()(A1 & a1)
    {
        return f_(a1);
    }


    template<class A1> result_type operator()(A1 & a1) const
    {
        return f_(a1);
    }


    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2)
    {
        return f_(a1, a2);
    }


    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2) const
    {
        return f_(a1, a2);
    }


    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3)
    {
        return f_(a1, a2, a3);
    }


    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3) const
    {
        return f_(a1, a2, a3);
    }


    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4)
    {
        return f_(a1, a2, a3, a4);
    }


    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f_(a1, a2, a3, a4);
    }


    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5)
    {
        return f_(a1, a2, a3, a4, a5);
    }


    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f_(a1, a2, a3, a4, a5);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6)
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f_(a1, a2, a3, a4, a5, a6);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9)
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }


    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f_(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }


template<class F> _bi::protected_bind_t<F> protect(F f)
{
    return _bi::protected_bind_t<F>(f);
}


    result_type operator()()
    {
        list0 a;
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }


    template<class A> result_type eval(A & a)
    {
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }


    template<class V> void accept(V & v) const
    {
#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) && !defined( __BORLANDC__ )

        using boost::visit_each;

#endif
        BOOST_BIND_VISIT_EACH(v, f_, 0);
        l_.accept(v);
    }


    explicit af0(F f): f_(f)
    {
    }


    result_type operator()()
    {
        return f_();
    }


    result_type operator()() const
    {
        return f_();
    }


    explicit af1(F f): f_(f)
    {
    }


    result_type operator()(A1 a1)
    {
        return f_(a1);
    }


    result_type operator()(A1 a1) const
    {
        return f_(a1);
    }


    explicit af2(F f): f_(f)
    {
    }


    result_type operator()(A1 a1, A2 a2)
    {
        return f_(a1, a2);
    }


    result_type operator()(A1 a1, A2 a2) const
    {
        return f_(a1, a2);
    }


    explicit af3(F f): f_(f)
    {
    }


    result_type operator()(A1 a1, A2 a2, A3 a3)
    {
        return f_(a1, a2, a3);
    }


    result_type operator()(A1 a1, A2 a2, A3 a3) const
    {
        return f_(a1, a2, a3);
    }


    explicit af4(F f): f_(f)
    {
    }


    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4)
    {
        return f_(a1, a2, a3, a4);
    }


    result_type operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
    {
        return f_(a1, a2, a3, a4);
    }


template<class R, class F> _bi::af0<R, F> make_adaptable(F f)
{
    return _bi::af0<R, F>(f);
}


template<class R, class A1, class F> _bi::af1<R, A1, F> make_adaptable(F f)
{
    return _bi::af1<R, A1, F>(f);
}


template<class R, class A1, class A2, class F> _bi::af2<R, A1, A2, F> make_adaptable(F f)
{
    return _bi::af2<R, A1, A2, F>(f);
}


template<class R, class A1, class A2, class A3, class F> _bi::af3<R, A1, A2, A3, F> make_adaptable(F f)
{
    return _bi::af3<R, A1, A2, A3, F>(f);
}


template<class R, class A1, class A2, class A3, class A4, class F> _bi::af4<R, A1, A2, A3, A4, F> make_adaptable(F f)
{
    return _bi::af4<R, A1, A2, A3, A4, F>(f);
}


    template<class F> result_type operator()(F & f) const
    {
        return f();
    }


    template<class F, class A1> result_type operator()(F & f, A1 & a1) const
    {
        return f(a1);
    }


    template<class F, class A1, class A2> result_type operator()(F & f, A1 & a1, A2 & a2) const
    {
        return f(a1, a2);
    }


    template<class F, class A1, class A2, class A3> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3) const
    {
        return f(a1, a2, a3);
    }


    template<class F, class A1, class A2, class A3, class A4> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f(a1, a2, a3, a4);
    }


    template<class F, class A1, class A2, class A3, class A4, class A5> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f(a1, a2, a3, a4, a5);
    }


    template<class F, class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f(a1, a2, a3, a4, a5, a6);
    }


    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7);
    }


    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8);
    }


    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    arg()
    {
    }


    template< class T > arg( T const & /* t */ )
    {
        // static assert I == is_placeholder<T>::value
        typedef char T_must_be_placeholder[ I == is_placeholder<T>::value? 1: -1 ];
    }


template< int I > bool operator==( arg<I> const &, arg<I> const & )
{
    return true;
}
