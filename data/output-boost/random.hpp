
        explicit param_type(RealType p_arg = RealType(0.5))
          : _p(p_arg)
        {
            BOOST_ASSERT(RealType(0) < _p && _p < RealType(1));
        }

        RealType p() const { return _p; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._p;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            double p_in;
            if(is >> p_in) {
                if(p_in > RealType(0) && p_in < RealType(1)) {
                    parm._p = p_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._p == rhs._p; }

    explicit geometric_distribution(const RealType& p = RealType(0.5))
      : _p(p)
    {
        BOOST_ASSERT(RealType(0) < _p && _p < RealType(1));
        init();
    }

    explicit geometric_distribution(const param_type& parm)
      : _p(parm.p())
    {
        init();
    }

    RealType p() const { return _p; }


    explicit geometric_distribution(RealType p_arg = RealType(0.5))
      : _impl(1 - p_arg) {}


    RealType p() const { return 1 - _impl.p(); }


    void reset() {}


    template<class Engine>
    IntType operator()(Engine& eng) const { return _impl(eng) + IntType(1); }


    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, geometric_distribution, gd)
    {
        os << gd.p();
        return os;
    }


    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, geometric_distribution, gd)
    {
        RealType val;
        if(is >> val) {
            typename impl_type::param_type impl_param(1 - val);
            gd._impl.param(impl_param);
        }
        return is;
    }

    inversive_congruential(IntType x0 = 1) : base_type(x0) {}

    template<class It>
    inversive_congruential(It& first, It last) : base_type(first, last) {}

        explicit param_type(RealType a_arg = 1.0, RealType b_arg = 1.0)
          : _a(a_arg), _b(b_arg)
        {}

        RealType a() const { return _a; }

        RealType b() const { return _b; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._a << ' ' << parm._b; return os; }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._a >> std::ws >> parm._b; return is; }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._a == rhs._a && lhs._b == rhs._b; }

    explicit extreme_value_distribution(RealType a_arg = 1.0, RealType b_arg = 1.0)
      : _a(a_arg), _b(b_arg)
    {}

    explicit extreme_value_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b())
    {}

    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        using std::log;
        return _a - log(-log(uniform_01<RealType>()(urng))) * _b;
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return extreme_value_distribution(parm)(urng);
    }

    RealType a() const { return _a; }

    RealType b() const { return _b; }

    shuffle_output() {}

    template<class T>
    shuffle_output(T& arg) : base_t(arg) {}

    template<class T>
    shuffle_output(const T& arg) : base_t(arg) {}

    template<class It>
    shuffle_output(It& first, It last) : base_t(first, last) {}

        explicit param_type(RealType m_arg = RealType(0.0),
                            RealType s_arg = RealType(1.0))
          : _m(m_arg), _s(s_arg) {}

        RealType m() const { return _m; }

        RealType s() const { return _s; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._m << " " << parm._s;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._m >> std::ws >> parm._s;
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._m == rhs._m && lhs._s == rhs._s; }

    explicit lognormal_distribution(RealType m_arg = RealType(0.0),
                                    RealType s_arg = RealType(1.0))
      : _normal(m_arg, s_arg) {}

    explicit lognormal_distribution(const param_type& parm)
      : _normal(parm.m(), parm.s()) {}

    RealType m() const { return _normal.mean(); }

    RealType s() const { return _normal.sigma(); }


    lognormal_distribution(RealType mean_arg = RealType(1.0),
                           RealType sigma_arg = RealType(1.0))
      : _mean(mean_arg), _sigma(sigma_arg)
    {
        init();
    }

    RealType mean() const { return _mean; }

    RealType sigma() const { return _sigma; }

    void reset() { _normal.reset(); }

    template<class Engine>
    RealType operator()(Engine& eng)
    {
        using std::exp;
        return exp(_normal(eng) * _nsigma + _nmean);
    }

    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, lognormal_distribution, ld)
    {
        os << ld._normal << " " << ld._mean << " " << ld._sigma;
        return os;
    }

    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, lognormal_distribution, ld)
    {
        is >> ld._normal >> std::ws >> ld._mean >> std::ws >> ld._sigma;
        ld.init();
        return is;
    }

    void init()
    {
        using std::log;
        using std::sqrt;
        _nmean = log(_mean*_mean/sqrt(_sigma*_sigma + _mean*_mean));
        _nsigma = sqrt(log(_sigma*_sigma/_mean/_mean+result_type(1)));
    }

    additive_combine() {}

    template<class T>
    additive_combine(T& arg) : base_t(arg) {}

    template<class T>
    additive_combine(const T& arg) : base_t(arg) {}

    template<class It>
    additive_combine(It& first, It last) : base_t(first, last) {}

        explicit param_type(IntType t_arg = 1, RealType p_arg = RealType (0.5))
          : _t(t_arg), _p(p_arg)
        {}

        IntType t() const { return _t; }

        RealType p() const { return _p; }

    explicit binomial_distribution(IntType t_arg = 1,
                                   RealType p_arg = RealType(0.5))
      : _t(t_arg), _p(p_arg)
    {
        init();
    }

    explicit binomial_distribution(const param_type& parm)
      : _t(parm.t()), _p(parm.p())
    {
        init();
    }

    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        if(use_inversion()) {
            if(0.5 < _p) {
                return _t - invert(_t, 1-_p, urng);
            } else {
                return invert(_t, _p, urng);
            }
        } else if(0.5 < _p) {
            return _t - generate(urng);
        } else {
            return generate(urng);
        }
    }

    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return binomial_distribution(parm)(urng);
    }

    IntType t() const { return _t; }

    RealType p() const { return _p; }

        explicit param_type(RealType a_arg = RealType(0.0),
                            RealType b_arg = RealType(0.5),
                            RealType c_arg = RealType(1.0))
          : _a(a_arg), _b(b_arg), _c(c_arg)
        {
            BOOST_ASSERT(_a <= _b && _b <= _c);
        }

        RealType a() const { return _a; }

        RealType b() const { return _b; }

        RealType c() const { return _c; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._a << " " << parm._b << " " << parm._c;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            double a_in, b_in, c_in;
            if(is >> a_in >> std::ws >> b_in >> std::ws >> c_in) {
                if(a_in <= b_in && b_in <= c_in) {
                    parm._a = a_in;
                    parm._b = b_in;
                    parm._c = c_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._a == rhs._a && lhs._b == rhs._b && lhs._c == rhs._c; }

    explicit triangle_distribution(RealType a_arg = RealType(0.0),
                                   RealType b_arg = RealType(0.5),
                                   RealType c_arg = RealType(1.0))
      : _a(a_arg), _b(b_arg), _c(c_arg)
    {
        BOOST_ASSERT(_a <= _b && _b <= _c);
        init();
    }

    explicit triangle_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b()), _c(parm.c())
    {
        init();
    }

    result_type a() const { return _a; }

    result_type b() const { return _b; }

    result_type c() const { return _c; }

        explicit param_type(RealType a_arg = 1.0, RealType b_arg = 1.0)
          : _a(a_arg), _b(b_arg)
        {}

        RealType a() const { return _a; }

        RealType b() const { return _b; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._a << ' ' << parm._b; return os; }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._a >> std::ws >> parm._b; return is; }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._a == rhs._a && lhs._b == rhs._b; }

    explicit weibull_distribution(RealType a_arg = 1.0, RealType b_arg = 1.0)
      : _a(a_arg), _b(b_arg)
    {}

    explicit weibull_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b())
    {}

    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        using std::pow;
        using std::log;
        return _b*pow(-log(1 - uniform_01<RealType>()(urng)), 1/_a);
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return weibull_distribution(parm)(urng);
    }

    RealType a() const { return _a; }

    RealType b() const { return _b; }


template<class UIntType, int w, unsigned int p, unsigned int q>
void lagged_fibonacci_engine<UIntType, w, p, q>::fill()
{
    // two loops to avoid costly modulo operations
    {  // extra scope for MSVC brokenness w.r.t. for scope
    for(unsigned int j = 0; j < short_lag; ++j)
        x[j] = (x[j] + x[j+(long_lag-short_lag)]) & low_bits_mask_t<w>::sig_bits;
    }
    for(unsigned int j = short_lag; j < long_lag; ++j)
        x[j] = (x[j] + x[j-short_lag]) & low_bits_mask_t<w>::sig_bits;
    i = 0;
}

    lagged_fibonacci() {}

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci, UIntType, val)
    { this->seed(val); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci, SeedSeq, seq)
    { this->seed(seq); }

    template<class It>
    lagged_fibonacci(It& first, It last) : base_type(first, last) {}

    lagged_fibonacci_01_engine() { seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci_01_engine, uint32_t, value)
    { seed(value); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci_01_engine, SeedSeq, seq)
    { seed(seq); }

    template<class It> lagged_fibonacci_01_engine(It& first, It last)
    { seed(first, last); }

    void seed() { seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(lagged_fibonacci_01_engine, boost::uint32_t, value)
    {
        minstd_rand0 intgen(value);
        detail::generator_seed_seq<minstd_rand0> gen(intgen);
        seed(gen);
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(lagged_fibonacci_01_engine, SeedSeq, seq)
    {
        detail::seed_array_real<w>(seq, x);
        i = long_lag;
    }

    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_real<w>(first, last, x);
        i = long_lag;
    }

    static RealType modulus()
    {
        using std::pow;
        return pow(RealType(2), word_size);
    }

template<class RealType, int w, unsigned int p, unsigned int q>
void lagged_fibonacci_01_engine<RealType, w, p, q>::fill()
{
    // two loops to avoid costly modulo operations
    {  // extra scope for MSVC brokenness w.r.t. for scope
    for(unsigned int j = 0; j < short_lag; ++j) {
        RealType t = x[j] + x[j+(long_lag-short_lag)];
        if(t >= RealType(1))
            t -= RealType(1);
        x[j] = t;
    }
    }
    for(unsigned int j = short_lag; j < long_lag; ++j) {
        RealType t = x[j] + x[j-short_lag];
        if(t >= RealType(1))
            t -= RealType(1);
        x[j] = t;
    }
    i = 0;
}

    lagged_fibonacci_01() {}

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci_01, boost::uint32_t, val)
    { this->seed(val); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci_01, SeedSeq, seq)
    { this->seed(seq); }

    template<class It>
    lagged_fibonacci_01(It& first, It last) : base_type(first, last) {}

    static std::size_t value() { return w; }

    static std::size_t value() { return w; }


    void calc_params(
        std::size_t n, base_unsigned range,
        std::size_t& w0, std::size_t& n0,
        base_unsigned& y0, base_unsigned& y1,
        base_unsigned& y0_mask, base_unsigned& y1_mask)
    {
        BOOST_ASSERT(w >= n);
        w0 = w/n;
        n0 = n - w % n;
        y0_mask = (base_unsigned(2) << (w0 - 1)) - 1;
        y1_mask = (y0_mask << 1) | 1;
        y0 = (range + 1) & ~y0_mask;
        y1 = (range + 1) & ~y1_mask;
        BOOST_ASSERT(y0 != 0 || base_unsigned(range + 1) == 0);
    }

        explicit param_type(RealType n_arg = RealType(1.0))
          : _n(n_arg)
        {}

        RealType n() const { return _n; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._n; return os; }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._n; return is; }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._n == rhs._n; }

    explicit student_t_distribution(RealType n_arg = RealType(1.0))
      : _normal(), _chi_squared(n_arg)
    {}

    explicit student_t_distribution(const param_type& parm)
      : _normal(), _chi_squared(parm.n())
    {}

    template<class URNG>
    RealType operator()(URNG& urng)
    {
        using std::sqrt;
        return _normal(urng) / sqrt(_chi_squared(urng) / n());
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return student_t_distribution(parm)(urng);
    }

    RealType n() const { return _chi_squared.n(); }

        explicit param_type(IntType k_arg = 1, RealType p_arg = RealType (0.5))
          : _k(k_arg), _p(p_arg)
        {}

        IntType k() const { return _k; }

        RealType p() const { return _p; }

    explicit negative_binomial_distribution(IntType k_arg = 1,
                                            RealType p_arg = RealType(0.5))
      : _k(k_arg), _p(p_arg)
    {}

    explicit negative_binomial_distribution(const param_type& parm)
      : _k(parm.k()), _p(parm.p())
    {}

    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        gamma_distribution<RealType> gamma(_k, (1-_p)/_p);
        poisson_distribution<IntType, RealType> poisson(gamma(urng));
        return poisson(urng);
    }

    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return negative_binomial_distribution(parm)(urng);
    }

    IntType k() const { return _k; }

    RealType p() const { return _p; }

    xor_combine_engine() : _rng1(), _rng2() { }

    xor_combine_engine(const base1_type & rng1, const base2_type & rng2)
      : _rng1(rng1), _rng2(rng2) { }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(xor_combine_engine,
        result_type, v)
    { seed(v); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(xor_combine_engine,
        SeedSeq, seq)
    { seed(seq); }

    template<class It> xor_combine_engine(It& first, It last)
      : _rng1(first, last), _rng2( /* advanced by other call */ first, last) { }

    void seed() { _rng1.seed(); _rng2.seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(xor_combine_engine, result_type, v)
    { _rng1.seed(v); _rng2.seed(v); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(xor_combine_engine, SeedSeq, seq)
    { _rng1.seed(seq); _rng2.seed(seq); }

    template<class It> void seed(It& first, It last)
    {
        _rng1.seed(first, last);
        _rng2.seed(first, last);
    }

    const base1_type& base1() const { return _rng1; }

    const base2_type& base2() const { return _rng2; }

    result_type operator()()
    {
        return (_rng1() << s1) ^ (_rng2() << s2);
    }

    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    void discard(boost::uintmax_t z)
    {
        _rng1.discard(z);
        _rng2.discard(z);
    }

    xor_combine() {}

    xor_combine(result_type val) : base_type(val) {}

    template<class It>
    xor_combine(It& first, It last) : base_type(first, last) {}

    xor_combine(const URNG1 & rng1, const URNG2 & rng2)
      : base_type(rng1, rng2) { }

        explicit param_type(RealType mean_arg = RealType(1))
          : _mean(mean_arg)
        {
            BOOST_ASSERT(_mean > 0);
        }

        RealType mean() const { return _mean; }

    explicit poisson_distribution(RealType mean_arg = RealType(1))
      : _mean(mean_arg)
    {
        BOOST_ASSERT(_mean > 0);
        init();
    }

    explicit poisson_distribution(const param_type& parm)
      : _mean(parm.mean())
    {
        init();
    }

    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        if(use_inversion()) {
            return invert(urng);
        } else {
            return generate(urng);
        }
    }

    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return poisson_distribution(parm)(urng);
    }

    RealType mean() const { return _mean; }

        explicit param_type(RealType median_arg = RealType(0.0),
                            RealType sigma_arg = RealType(1.0))
          : _median(median_arg), _sigma(sigma_arg) {}

        RealType median() const { return _median; }

        RealType sigma() const { return _sigma; }

        RealType a() const { return _median; }

        RealType b() const { return _sigma; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._median << " " << parm._sigma;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._median >> std::ws >> parm._sigma;
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._median == rhs._median && lhs._sigma == rhs._sigma; }

    explicit cauchy_distribution(RealType median_arg = RealType(0.0), 
                                 RealType sigma_arg = RealType(1.0))
      : _median(median_arg), _sigma(sigma_arg) { }

    explicit cauchy_distribution(const param_type& parm)
      : _median(parm.median()), _sigma(parm.sigma()) { }

    RealType median() const { return _median; }

    RealType sigma() const { return _sigma; }

    RealType a() const { return _median; }

    RealType b() const { return _sigma; }

    seed_seq() {}

    template<class Iter>
    seed_seq(Iter first, Iter last) : v(first, last) {}

    template<class Range>
    explicit seed_seq(const Range& range)
      : v(boost::begin(range), boost::end(range)) {}

    template<class Iter>
    void generate(Iter first, Iter last) const
    {
        typedef typename std::iterator_traits<Iter>::value_type value_type;
        std::fill(first, last, static_cast<value_type>(0x8b8b8b8bu));
        std::size_t s = v.size();
        std::size_t n = last - first;
        std::size_t t =
            (n >= 623) ? 11 :
            (n >=  68) ?  7 :
            (n >=  39) ?  5 :
            (n >=   7) ?  3 :
            (n - 1)/2;
        std::size_t p = (n - t) / 2;
        std::size_t q = p + t;
        std::size_t m = (std::max)(s+1, n);
        value_type mask = 0xffffffffu;
        for(std::size_t k = 0; k < m; ++k) {
            value_type r1 =
                *(first + k%n) ^ *(first + (k+p)%n) ^ *(first + (k+n-1)%n);
            r1 = r1 ^ (r1 >> 27);
            r1 = (r1 * 1664525u) & mask;
            value_type r2 = r1 +
                ((k == 0) ? s :
                 (k <= s) ? k % n + v[k - 1] :
                 (k % n));
            *(first + (k+p)%n) = (*(first + (k+p)%n) + r1) & mask;
            *(first + (k+q)%n) = (*(first + (k+q)%n) + r2) & mask;
            *(first + k%n) = r2;
        }
        for(std::size_t k = m; k < m + n; ++k) {
            value_type r3 =
                (*(first + k%n) + *(first + (k+p)%n) + *(first + (k+n-1)%n))
                & mask;
            r3 = r3 ^ (r3 >> 27);
            r3 = (r3 * 1566083941u) & mask;
            value_type r4 = r3 - k%m;
            *(first + (k+p)%n) ^= r3;
            *(first + (k+q)%n) ^= r4;
            *(first + k%n) = r4;
        }
    }

    std::size_t size() const { return v.size(); }

    template<class Iter>
    void param(Iter out) { std::copy(v.begin(), v.end(), out); }

    template<class Iter>
    void generate(Iter begin, Iter end)
    {
        for(; begin != end; ++begin) {
            *begin = (*this)();
        }
    }

        param_type(IntType min_arg = 0, IntType max_arg = 9)
          : _min(min_arg), _max(max_arg)
        {
            BOOST_ASSERT(_min <= _max);
        }

        IntType a() const { return _min; }

        IntType b() const { return _max; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._min << " " << parm._max;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._min >> std::ws >> parm._max;
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._min == rhs._min && lhs._max == rhs._max; }

    explicit uniform_smallint(IntType min_arg = 0, IntType max_arg = 9)
      : _min(min_arg), _max(max_arg) {}

    explicit uniform_smallint(const param_type& parm)
      : _min(parm.a()), _max(parm.b()) {}

    result_type a() const { return _min; }

    result_type b() const { return _max; }

        explicit param_type(RealType min_arg = RealType(0.0),
                            RealType max_arg = RealType(1.0))
          : base_type::param_type(min_arg, max_arg)
        {}

    explicit uniform_real(RealType min_arg = RealType(0.0),
                          RealType max_arg = RealType(1.0))
      : base_type(min_arg, max_arg)
    {
        BOOST_ASSERT(min_arg <= max_arg);
    }

    explicit uniform_real(const param_type& parm)
      : base_type(parm)
    {}

    param_type param() const { return param_type(this->a(), this->b()); }

    void param(const param_type& parm) { this->base_type::param(parm); }


template<class Engine, class T>
T generate_uniform_real(
    Engine& eng, T min_value, T max_value,
    boost::mpl::false_  /** is_integral<Engine::result_type> */)
{
    for(;;) {
        typedef T result_type;
        typedef typename Engine::result_type base_result;
        result_type numerator = static_cast<T>(eng() - (eng.min)());
        result_type divisor = static_cast<T>((eng.max)() - (eng.min)());
        BOOST_ASSERT(divisor > 0);
        BOOST_ASSERT(numerator >= 0 && numerator <= divisor);
        T result = numerator / divisor * (max_value - min_value) + min_value;
        if(result < max_value) return result;
    }
}


template<class Engine, class T>
inline T generate_uniform_real(Engine& eng, T min_value, T max_value)
{
    typedef typename Engine::result_type base_result;
    return generate_uniform_real(eng, min_value, max_value,
        boost::is_integral<base_result>());
}

        explicit param_type(RealType min_arg = RealType(0.0),
                            RealType max_arg = RealType(1.0))
          : _min(min_arg), _max(max_arg)
        {
            BOOST_ASSERT(_min <= _max);
        }

        RealType a() const { return _min; }

        RealType b() const { return _max; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._min << " " << parm._max;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            RealType min_in, max_in;
            if(is >> min_in >> std::ws >> max_in) {
                if(min_in <= max_in) {
                    parm._min = min_in;
                    parm._max = max_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._min == rhs._min && lhs._max == rhs._max; }

    explicit uniform_real_distribution(
        RealType min_arg = RealType(0.0),
        RealType max_arg = RealType(1.0))
      : _min(min_arg), _max(max_arg)
    {
        BOOST_ASSERT(min_arg <= max_arg);
    }

    explicit uniform_real_distribution(const param_type& parm)
      : _min(parm.a()), _max(parm.b()) {}


template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical_impl(URNG& g, boost::mpl::true_ /*is_integral*/)
{
    using std::pow;
    typedef typename URNG::result_type base_result;
    std::size_t digits = std::numeric_limits<RealType>::digits;
    RealType R = RealType((g.max)()) - RealType((g.min)()) + 1;
    RealType mult = R;
    RealType limit =
        pow(RealType(2),
            RealType((std::min)(static_cast<std::size_t>(bits), digits)));
    RealType S = RealType(detail::subtract<base_result>()(g(), (g.min)()));
    while(mult < limit) {
        RealType inc = RealType(detail::subtract<base_result>()(g(), (g.min)()));
        S += inc * mult;
        mult *= R;
    }
    return S / mult;
}

template<class RealType, std::size_t bits, class URNG>
RealType generate_canonical(URNG& g)
{
    RealType result = detail::generate_canonical_impl<RealType, bits>(
        g, boost::is_integral<typename URNG::result_type>());
    BOOST_ASSERT(result >= 0);
    BOOST_ASSERT(result <= 1);
    if(result == 1) {
        result -= std::numeric_limits<RealType>::epsilon() / 2;
        BOOST_ASSERT(result != 1);
    }
    return result;
}

    linear_congruential_engine() { seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(linear_congruential_engine,
                                               IntType, x0)
    { seed(x0); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(linear_congruential_engine,
                                             SeedSeq, seq)
    { seed(seq); }

    template<class It>
    linear_congruential_engine(It& first, It last)
    {
        seed(first, last);
    }

    void seed() { seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(linear_congruential_engine, IntType, x0)
    {
        // wrap _x if it doesn't fit in the destination
        if(modulus == 0) {
            _x = x0;
        } else {
            _x = x0 % modulus;
        }
        // handle negative seeds
        if(_x <= 0 && _x != 0) {
            _x += modulus;
        }
        // adjust to the correct range
        if(increment == 0 && _x == 0) {
            _x = 1;
        }
        BOOST_ASSERT(_x >= (min)());
        BOOST_ASSERT(_x <= (max)());
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(linear_congruential_engine, SeedSeq, seq)
    { seed(detail::seed_one_int<IntType, m>(seq)); }

    template<class It>
    void seed(It& first, It last)
    { seed(detail::get_one_int<IntType, m>(first, last)); }

    linear_congruential(IntType x0 = 1) : base_type(x0) {}

    template<class It>
    linear_congruential(It& first, It last) : base_type(first, last) {}


    static boost::uint64_t cnv(boost::uint32_t x)
    { return (static_cast<uint64_t>(x) << 16) | 0x330e; }

    template<class Engine>
    static void apply(Engine& eng, boost::uintmax_t z)
    {
        typedef typename Engine::result_type IntType;
        const std::size_t short_lag = Engine::short_lag;
        const std::size_t long_lag = Engine::long_lag;
        std::size_t k = eng.k;
        IntType carry = eng.carry;
        if(k != 0) {
            // increment k until it becomes 0.
            if(k < short_lag) {
                std::size_t limit = (short_lag - k) < z?
                    short_lag : (k + static_cast<std::size_t>(z));
                for(std::size_t j = k; j < limit; ++j) {
                    carry = eng.do_update(j, j + long_lag - short_lag, carry);
                }
            }
            std::size_t limit = (long_lag - k) < z?
                long_lag : (k + static_cast<std::size_t>(z));
            std::size_t start = (k < short_lag ? short_lag : k);
            for(std::size_t j = start; j < limit; ++j) {
                carry = eng.do_update(j, j - short_lag, carry);
            }
        }

        k = ((z % long_lag) + k) % long_lag;

        if(k < z) {
            // main loop: update full blocks from k = 0 to long_lag
            for(std::size_t i = 0; i < (z - k) / long_lag; ++i) {
                for(std::size_t j = 0; j < short_lag; ++j) {
                    carry = eng.do_update(j, j + long_lag - short_lag, carry);
                }
                for(std::size_t j = short_lag; j < long_lag; ++j) {
                    carry = eng.do_update(j, j - short_lag, carry);
                }
            }

            // Update the last partial block
            std::size_t limit = short_lag < k? short_lag : k; 
            for(std::size_t j = 0; j < limit; ++j) {
                carry = eng.do_update(j, j + long_lag - short_lag, carry);
            }
            for(std::size_t j = short_lag; j < k; ++j) {
                carry = eng.do_update(j, j - short_lag, carry);
            }
        }
        eng.carry = carry;
        eng.k = k;
    }

    subtract_with_carry_engine() { seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_engine,
                                               IntType, value)
    { seed(value); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_engine,
                                             SeedSeq, seq)
    { seed(seq); }

    template<class It> subtract_with_carry_engine(It& first, It last)
    { seed(first,last); }

    void seed() { seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_engine,
                                        IntType, value)
    {
        typedef linear_congruential_engine<uint32_t,40014,0,2147483563> gen_t;
        gen_t intgen(static_cast<boost::uint32_t>(value == 0 ? default_seed : value));
        detail::generator_seed_seq<gen_t> gen(intgen);
        seed(gen);
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry, SeedSeq, seq)
    {
        detail::seed_array_int<w>(seq, x);
        carry = (x[long_lag-1] == 0);
        k = 0;
    }

    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_int<w>(first, last, x);
        carry = (x[long_lag-1] == 0);
        k = 0;
    }


    IntType do_update(std::size_t current, std::size_t short_index, IntType carry)
    {
        IntType delta;
        IntType temp = x[current] + carry;
        if (x[short_index] >= temp) {
            // x(n) >= 0
            delta =  x[short_index] - temp;
            carry = 0;
        } else {
            // x(n) < 0
            delta = modulus - temp + x[short_index];
            carry = 1;
        }
        x[current] = delta;
        return carry;
    }

    subtract_with_carry_01_engine() { init_modulus(); seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01_engine,
                                               boost::uint32_t, value)
    { init_modulus(); seed(value); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_01_engine,
                                             SeedSeq, seq)
    { init_modulus(); seed(seq); }

    template<class It> subtract_with_carry_01_engine(It& first, It last)
    { init_modulus(); seed(first,last); }

    void init_modulus()
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::pow;
#endif
        _modulus = pow(RealType(2), RealType(word_size));
    }

    void seed() { seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01_engine,
                                        boost::uint32_t, value)
    {
        typedef linear_congruential_engine<uint32_t, 40014, 0, 2147483563> gen_t;
        gen_t intgen(value == 0 ? default_seed : value);
        detail::generator_seed_seq<gen_t> gen(intgen);
        seed(gen);
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry_01_engine,
                                      SeedSeq, seq)
    {
        detail::seed_array_real<w>(seq, x);
        carry = (x[long_lag-1] ? 0 : 1 / _modulus);
        k = 0;
    }

    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_real<w>(first, last, x);
        carry = (x[long_lag-1] ? 0 : 1 / _modulus);
        k = 0;
    }


    RealType do_update(std::size_t current, std::size_t short_index, RealType carry)
    {
        RealType delta = x[short_index] - x[current] - carry;
        if(delta < 0) {
            delta += RealType(1);
            carry = RealType(1)/_modulus;
        } else {
            carry = 0;
        }
        x[current] = delta;
        return carry;
    }

    subtract_with_carry() {}

    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry, Gen, gen)
    { seed(gen); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry,
                                               IntType, val)
    { seed(val); }

    template<class It>
    subtract_with_carry(It& first, It last) : base_type(first, last) {}

    void seed() { base_type::seed(); }

    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry, IntType, val)
    { base_type::seed(val); }

    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }

    subtract_with_carry_01() {}

    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry_01, Gen, gen)
    { seed(gen); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01,
                                               uint32_t, val)
    { seed(val); }

    template<class It>
    subtract_with_carry_01(It& first, It last) : base_type(first, last) {}

    void seed() { base_type::seed(); }

    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry_01, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01, uint32_t, val)
    { base_type::seed(val); }

    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }

    static std::size_t value() { return w; }

    static std::size_t value() { return w; }

        param_type()
        {
            _weights.push_back(RealType(1));
            _weights.push_back(RealType(1));
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }

        template<class IntervalIter, class WeightIter>
        param_type(IntervalIter intervals_first, IntervalIter intervals_last,
                   WeightIter weight_first)
          : _intervals(intervals_first, intervals_last)
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _weights.push_back(RealType(1));
                _weights.push_back(RealType(1));
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
            } else {
                _weights.reserve(_intervals.size());
                for(std::size_t i = 0; i < _intervals.size(); ++i) {
                    _weights.push_back(*weight_first++);
                }
            }
        }

        template<class IntervalRange, class WeightRange>
        param_type(const IntervalRange& intervals_arg,
                   const WeightRange& weights_arg)
          : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
            _weights(boost::begin(weights_arg), boost::end(weights_arg))
        {
            if(_intervals.size() < 2) {
                _weights.clear();
                _weights.push_back(RealType(1));
                _weights.push_back(RealType(1));
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
            }
        }

    piecewise_linear_distribution()
    {
        default_init();
    }

    template<class IntervalIter, class WeightIter>
    piecewise_linear_distribution(IntervalIter first_interval,
                                  IntervalIter last_interval,
                                  WeightIter first_weight)
      : _intervals(first_interval, last_interval)
    {
        if(_intervals.size() < 2) {
            default_init();
        } else {
            _weights.reserve(_intervals.size());
            for(std::size_t i = 0; i < _intervals.size(); ++i) {
                _weights.push_back(*first_weight++);
            }
            init();
        }
    }

    template<class IntervalsRange, class WeightsRange>
    piecewise_linear_distribution(const IntervalsRange& intervals_arg,
                                  const WeightsRange& weights_arg)
      : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
        _weights(boost::begin(weights_arg), boost::end(weights_arg))
    {
        if(_intervals.size() < 2) {
            default_init();
        } else {
            init();
        }
    }

    explicit piecewise_linear_distribution(const param_type& parm)
      : _intervals(parm._intervals),
        _weights(parm._weights)
    {
        init();
    }

    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        std::size_t i = _bins(urng);
        bool is_in_rectangle = (i % 2 == 0);
        i = i / 2;
        uniform_real<RealType> dist(_intervals[i], _intervals[i+1]);
        if(is_in_rectangle) {
            return dist(urng);
        } else if(_weights[i] < _weights[i+1]) {
            return (std::max)(dist(urng), dist(urng));
        } else {
            return (std::min)(dist(urng), dist(urng));
        }
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return piecewise_linear_distribution(parm)(urng);
    }

        explicit param_type(IntType min_arg = 0, IntType max_arg = 9)
          : base_type::param_type(min_arg, max_arg)
        {}

    explicit uniform_int(IntType min_arg = 0, IntType max_arg = 9)
      : base_type(min_arg, max_arg)
    {}

    explicit uniform_int(const param_type& parm)
      : base_type(parm)
    {}

    param_type param() const { return param_type(this->a(), this->b()); }

    void param(const param_type& parm) { this->base_type::param(parm); }


    template<class Engine>
    IntType operator()(Engine& eng) const
    {
        return static_cast<const base_type&>(*this)(eng);
    }


    template<class Engine>
    IntType operator()(Engine& eng, const param_type& parm) const
    {
        return static_cast<const base_type&>(*this)(eng, parm);
    }


    template<class Engine>
    IntType operator()(Engine& eng, IntType n) const
    {
        BOOST_ASSERT(n > 0);
        return static_cast<const base_type&>(*this)(eng, param_type(0, n - 1));
    }

        explicit param_type(RealType m_arg = RealType(1.0),
                            RealType n_arg = RealType(1.0))
          : _m(m_arg), _n(n_arg)
        {}

        RealType m() const { return _m; }

        RealType n() const { return _n; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._m << ' ' << parm._n; return os; }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._m >> std::ws >> parm._n; return is; }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._m == rhs._m && lhs._n == rhs._n; }

    explicit fisher_f_distribution(RealType m_arg = RealType(1.0),
                                   RealType n_arg = RealType(1.0))
      : _impl_m(m_arg), _impl_n(n_arg)
    {}

    explicit fisher_f_distribution(const param_type& parm)
      : _impl_m(parm.m()), _impl_n(parm.n())
    {}

    template<class URNG>
    RealType operator()(URNG& urng)
    {
        return (_impl_m(urng) * n()) / (_impl_n(urng) * m());
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return fisher_f_distribution(parm)(urng);
    }

    RealType m() const { return _impl_m.n(); }

    RealType n() const { return _impl_n.n(); }

    variate_generator(Engine e, Distribution d)
      : _eng(e), _dist(d) { }

    result_type operator()() { return _dist(engine()); }

    template<class T>
    result_type operator()(const T& value) { return _dist(engine(), value); }

    engine_value_type& engine() { return helper_type::ref(_eng); }

    distribution_type& distribution() { return _dist; }

    const distribution_type& distribution() const { return _dist; }

    random_number_generator(base_type& rng) : _rng(rng) {}

    result_type operator()(argument_type n)
    {
        BOOST_ASSERT(n > 0);
        return uniform_int_distribution<IntType>(0, n-1)(_rng);
    }

        param_type() : _probabilities(1, static_cast<WeightType>(1)) {}

        template<class Iter>
        param_type(Iter first, Iter last) : _probabilities(first, last)
        {
            normalize();
        }

        template<class Range>
        explicit param_type(const Range& range)
          : _probabilities(boost::begin(range), boost::end(range))
        {
            normalize();
        }

        explicit param_type(const discrete_distribution& dist)
          : _probabilities(dist.probabilities())
        {}

        void normalize()
        {
            WeightType sum =
                std::accumulate(_probabilities.begin(), _probabilities.end(),
                                static_cast<WeightType>(0));
            for(typename std::vector<WeightType>::iterator
                    iter = _probabilities.begin(),
                    end = _probabilities.end();
                    iter != end; ++iter)
            {
                *iter /= sum;
            }
        }

    discrete_distribution()
    {
        _alias_table.push_back(std::make_pair(static_cast<WeightType>(1),
                                              static_cast<IntType>(0)));
    }

    template<class Iter>
    discrete_distribution(Iter first, Iter last)
    {
        init(first, last);
    }

    template<class Range>
    explicit discrete_distribution(const Range& range)
    {
        init(boost::begin(range), boost::end(range));
    }

    explicit discrete_distribution(const param_type& parm)
    {
        param(parm);
    }

    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        BOOST_ASSERT(!_alias_table.empty());
        WeightType test = uniform_01<WeightType>()(urng);
        IntType result = uniform_int<IntType>((min)(), (max)())(urng);
        if(test < _alias_table[result].first) {
            return result;
        } else {
            return(_alias_table[result].second);
        }
    }

    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        while(true) {
            WeightType val = uniform_01<WeightType>()(urng);
            WeightType sum = 0;
            std::size_t result = 0;
            for(typename std::vector<WeightType>::const_iterator
                iter = parm._probabilities.begin(),
                end = parm._probabilities.end();
                iter != end; ++iter, ++result)
            {
                sum += *iter;
                if(sum > val) {
                    return result;
                }
            }
        }
    }

        explicit param_type(RealType p_arg = RealType(0.5))
          : _p(p_arg)
        {
            BOOST_ASSERT(_p >= 0);
            BOOST_ASSERT(_p <= 1);
        }

        RealType p() const { return _p; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._p;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._p;
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._p == rhs._p; }

    explicit bernoulli_distribution(const RealType& p_arg = RealType(0.5)) 
      : _p(p_arg)
    {
        BOOST_ASSERT(_p >= 0);
        BOOST_ASSERT(_p <= 1);
    }

    explicit bernoulli_distribution(const param_type& parm)
      : _p(parm.p()) {}

    RealType p() const { return _p; }


template<class Engine, class T>
T generate_uniform_int(
    Engine& eng, T min_value, T max_value,
    boost::mpl::true_ /** is_integral<Engine::result_type> */)
{
    typedef T result_type;
    typedef typename make_unsigned<T>::type range_type;
    typedef typename Engine::result_type base_result;
    // ranges are always unsigned
    typedef typename make_unsigned<base_result>::type base_unsigned;
    const range_type range = random::detail::subtract<result_type>()(max_value, min_value);
    const base_result bmin = (eng.min)();
    const base_unsigned brange =
      random::detail::subtract<base_result>()((eng.max)(), (eng.min)());

    if(range == 0) {
      return min_value;    
    } else if(brange == range) {
      // this will probably never happen in real life
      // basically nothing to do; just take care we don't overflow / underflow
      base_unsigned v = random::detail::subtract<base_result>()(eng(), bmin);
      return random::detail::add<base_unsigned, result_type>()(v, min_value);
    } else if(brange < range) {
      // use rejection method to handle things like 0..3 --> 0..4
      for(;;) {
        // concatenate several invocations of the base RNG
        // take extra care to avoid overflows

        //  limit == floor((range+1)/(brange+1))
        //  Therefore limit*(brange+1) <= range+1
        range_type limit;
        if(range == (std::numeric_limits<range_type>::max)()) {
          limit = range/(range_type(brange)+1);
          if(range % (range_type(brange)+1) == range_type(brange))
            ++limit;
        } else {
          limit = (range+1)/(range_type(brange)+1);
        }

        // We consider "result" as expressed to base (brange+1):
        // For every power of (brange+1), we determine a random factor
        range_type result = range_type(0);
        range_type mult = range_type(1);

        // loop invariants:
        //  result < mult
        //  mult <= range
        while(mult <= limit) {
          // Postcondition: result <= range, thus no overflow
          //
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // and mult<=limit.                            loop condition      (3)
          // Therefore mult*(eng()-bmin+1)<=range+1      by (1),(2),(3)      (4)
          // Therefore mult*(eng()-bmin)+mult<=range+1   rearranging (4)     (5)
          // result<mult                                 loop invariant      (6)
          // Therefore result+mult*(eng()-bmin)<range+1  by (5), (6)         (7)
          //
          // Postcondition: result < mult*(brange+1)
          //
          // result<mult                                 loop invariant      (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // Therefore result+mult*(eng()-bmin) <
          //           mult+mult*(eng()-bmin)            by (1)              (3)
          // Therefore result+(eng()-bmin)*mult <
          //           mult+mult*brange                  by (2), (3)         (4)
          // Therefore result+(eng()-bmin)*mult <
          //           mult*(brange+1)                   by (4)
          result += static_cast<range_type>(random::detail::subtract<base_result>()(eng(), bmin) * mult);

          // equivalent to (mult * (brange+1)) == range+1, but avoids overflow.
          if(mult * range_type(brange) == range - mult + 1) {
              // The destination range is an integer power of
              // the generator's range.
              return(result);
          }

          // Postcondition: mult <= range
          // 
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // mult<=limit                                 loop condition      (2)
          // Therefore mult*(brange+1)<=range+1          by (1), (2)         (3)
          // mult*(brange+1)!=range+1                    preceding if        (4)
          // Therefore mult*(brange+1)<range+1           by (3), (4)         (5)
          // 
          // Postcondition: result < mult
          //
          // See the second postcondition on the change to result. 
          mult *= range_type(brange)+range_type(1);
        }
        // loop postcondition: range/mult < brange+1
        //
        // mult > limit                                  loop condition      (1)
        // Suppose range/mult >= brange+1                Assumption          (2)
        // range >= mult*(brange+1)                      by (2)              (3)
        // range+1 > mult*(brange+1)                     by (3)              (4)
        // range+1 > (limit+1)*(brange+1)                by (1), (4)         (5)
        // (range+1)/(brange+1) > limit+1                by (5)              (6)
        // limit < floor((range+1)/(brange+1))           by (6)              (7)
        // limit==floor((range+1)/(brange+1))            def. of limit       (8)
        // not (2)                                       reductio            (9)
        //
        // loop postcondition: (range/mult)*mult+(mult-1) >= range
        //
        // (range/mult)*mult + range%mult == range       identity            (1)
        // range%mult < mult                             def. of %           (2)
        // (range/mult)*mult+mult > range                by (1), (2)         (3)
        // (range/mult)*mult+(mult-1) >= range           by (3)              (4)
        //
        // Note that the maximum value of result at this point is (mult-1),
        // so after this final step, we generate numbers that can be
        // at least as large as range.  We have to really careful to avoid
        // overflow in this final addition and in the rejection.  Anything
        // that overflows is larger than range and can thus be rejected.

        // range/mult < brange+1  -> no endless loop
        range_type result_increment =
            generate_uniform_int(
                eng,
                static_cast<range_type>(0),
                static_cast<range_type>(range/mult),
                boost::mpl::true_());
        if((std::numeric_limits<range_type>::max)() / mult < result_increment) {
          // The multiplcation would overflow.  Reject immediately.
          continue;
        }
        result_increment *= mult;
        // unsigned integers are guaranteed to wrap on overflow.
        result += result_increment;
        if(result < result_increment) {
          // The addition overflowed.  Reject.
          continue;
        }
        if(result > range) {
          // Too big.  Reject.
          continue;
        }
        return random::detail::add<range_type, result_type>()(result, min_value);
      }
    } else {                   // brange > range
      base_unsigned bucket_size;
      // it's safe to add 1 to range, as long as we cast it first,
      // because we know that it is less than brange.  However,
      // we do need to be careful not to cause overflow by adding 1
      // to brange.
      if(brange == (std::numeric_limits<base_unsigned>::max)()) {
        bucket_size = brange / (static_cast<base_unsigned>(range)+1);
        if(brange % (static_cast<base_unsigned>(range)+1) == static_cast<base_unsigned>(range)) {
          ++bucket_size;
        }
      } else {
        bucket_size = (brange+1) / (static_cast<base_unsigned>(range)+1);
      }
      for(;;) {
        base_unsigned result =
          random::detail::subtract<base_result>()(eng(), bmin);
        result /= bucket_size;
        // result and range are non-negative, and result is possibly larger
        // than range, so the cast is safe
        if(result <= static_cast<base_unsigned>(range))
          return random::detail::add<base_unsigned, result_type>()(result, min_value);
      }
    }
}


template<class Engine, class T>
inline T generate_uniform_int(Engine& eng, T min_value, T max_value)
{
    typedef typename Engine::result_type base_result;
    return generate_uniform_int(eng, min_value, max_value,
        boost::is_integral<base_result>());
}

        explicit param_type(
            IntType min_arg = 0,
            IntType max_arg = (std::numeric_limits<IntType>::max)())
          : _min(min_arg), _max(max_arg)
        {
            BOOST_ASSERT(_min <= _max);
        }

        IntType a() const { return _min; }

        IntType b() const { return _max; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._min << " " << parm._max;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            IntType min_in, max_in;
            if(is >> min_in >> std::ws >> max_in) {
                if(min_in <= max_in) {
                    parm._min = min_in;
                    parm._max = max_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._min == rhs._min && lhs._max == rhs._max; }

    explicit uniform_int_distribution(
        IntType min_arg = 0,
        IntType max_arg = (std::numeric_limits<IntType>::max)())
      : _min(min_arg), _max(max_arg)
    {
        BOOST_ASSERT(min_arg <= max_arg);
    }

    explicit uniform_int_distribution(const param_type& parm)
      : _min(parm.a()), _max(parm.b()) {}

    mersenne_twister_engine() { seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister_engine,
                                               UIntType, value)
    { seed(value); }

    template<class It> mersenne_twister_engine(It& first, It last)
    { seed(first,last); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(mersenne_twister_engine,
                                             SeedSeq, seq)
    { seed(seq); }

    void seed() { seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(mersenne_twister_engine, UIntType, value)
    {
        // New seeding algorithm from 
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
        // In the previous versions, MSBs of the seed affected only MSBs of the
        // state x[].
        const UIntType mask = (max)();
        x[0] = value & mask;
        for (i = 1; i < n; i++) {
            // See Knuth "The Art of Computer Programming"
            // Vol. 2, 3rd ed., page 106
            x[i] = (f * (x[i-1] ^ (x[i-1] >> (w-2))) + i) & mask;
        }
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(mersenne_twister_engine, SeeqSeq, seq)
    {
        detail::seed_array_int<w>(seq, x);
        i = n;

        // fix up the state if it's all zeroes.
        if((x[0] & (~static_cast<UIntType>(0) << r)) == 0) {
            for(std::size_t j = 1; j < n; ++j) {
                if(x[j] != 0) return;
            }
            x[0] = static_cast<UIntType>(1) << (w-1);
        }
    }

    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_int<w>(first, last, x);
        i = n;

        // fix up the state if it's all zeroes.
        if((x[0] & (~static_cast<UIntType>(0) << r)) == 0) {
            for(std::size_t j = 1; j < n; ++j) {
                if(x[j] != 0) return;
            }
            x[0] = static_cast<UIntType>(1) << (w-1);
        }
    }

    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    bool equal_imp(const mersenne_twister_engine& other) const
    {
        UIntType back[n];
        std::size_t offset = other.i - i;
        for(std::size_t j = 0; j + offset < n; ++j)
            if(x[j] != other.x[j+offset])
                return false;
        rewind(&back[n-1], offset);
        for(std::size_t j = 0; j < offset; ++j)
            if(back[j + n - offset] != other.x[j])
                return false;
        return true;
    }

    template<class CharT, class Traits>
    void print(std::basic_ostream<CharT, Traits>& os) const
    {
        UIntType data[n];
        for(std::size_t j = 0; j < i; ++j) {
            data[j + n - i] = x[j];
        }
        if(i != n) {
            rewind(&data[n - i - 1], n - i);
        }
        os << data[0];
        for(std::size_t j = 1; j < n; ++j) {
            os << ' ' << data[j];
        }
    }

    void rewind(UIntType* last, std::size_t z) const
    {
        const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
        const UIntType lower_mask = ~upper_mask;
        UIntType y0 = x[m-1] ^ x[n-1];
        if(y0 & (static_cast<UIntType>(1) << (w-1))) {
            y0 = ((y0 ^ a) << 1) | 1;
        } else {
            y0 = y0 << 1;
        }
        for(std::size_t sz = 0; sz < z; ++sz) {
            UIntType y1 =
                rewind_find(last, sz, m-1) ^ rewind_find(last, sz, n-1);
            if(y1 & (static_cast<UIntType>(1) << (w-1))) {
                y1 = ((y1 ^ a) << 1) | 1;
            } else {
                y1 = y1 << 1;
            }
            *(last - sz) = (y0 & upper_mask) | (y1 & lower_mask);
            y0 = y1;
        }
    }

    UIntType
    rewind_find(UIntType* last, std::size_t size, std::size_t j) const
    {
        std::size_t index = (j + n - size + n - 1) % n;
        if(index < n - size) {
            return x[index];
        } else {
            return *(last - (n - 1 - index));
        }
    }

    mersenne_twister() {}

    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(mersenne_twister, Gen, gen)
    { seed(gen); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister, UIntType, val)
    { seed(val); }

    template<class It>
    mersenne_twister(It& first, It last) : base_type(first, last) {}

    void seed() { base_type::seed(); }

    BOOST_RANDOM_DETAIL_GENERATOR_SEED(mersenne_twister, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(mersenne_twister, UIntType, val)
    { base_type::seed(val); }

    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }

    linear_feedback_shift_engine() { seed(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(linear_feedback_shift_engine,
        UIntType, s0)
    { seed(s0); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(linear_feedback_shift_engine,
        SeedSeq, seq)
    { seed(seq); }

    template<class It> linear_feedback_shift_engine(It& first, It last)
    { seed(first, last); }

    void seed() {  seed(default_seed); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(linear_feedback_shift_engine,
        UIntType, s0)
    {
        value = s0 & wordmask();
        if(value < (1 << (w-k))) {
            value += 1 << (w-k);
        }
    }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(linear_feedback_shift_engine,
        SeedSeq, seq)
    { seed(detail::seed_one_int<UIntType, (UIntType(2) << (w - 1))>(seq)); }

    template<class It> void seed(It& first, It last)
    {
        seed(detail::get_one_int<UIntType, (UIntType(2) << (w - 1))>(first, last));
    }

    result_type operator()()
    {
        const UIntType b = (((value << q) ^ value) & wordmask()) >> (k-s);
        const UIntType mask = (wordmask() << (w-k)) & wordmask();
        value = ((value & mask) << s) ^ b;
        return value;
    }

    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, linear_feedback_shift_engine, x)
    {
        os << x.value;
        return os;
    }

    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, linear_feedback_shift_engine, x)
    {
        is >> x.value;
        return is;
    }

    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(linear_feedback_shift_engine, x, y)
    { return x.value == y.value; }

    linear_feedback_shift() {}

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(linear_feedback_shift,
        SeedSeq, seq)
    { seed(seq); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(linear_feedback_shift,
        UIntType, val)
    { seed(val); }

    template<class It>
    linear_feedback_shift(It& first, It last) : base_type(first, last) {}

    shuffle_order_engine() : _rng() { init(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(shuffle_order_engine,
                                               result_type, s)
    { _rng.seed(s); init(); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(shuffle_order_engine, SeedSeq, seq)
    { _rng.seed(seq); init(); }

    explicit shuffle_order_engine(const base_type & rng) : _rng(rng) { init(); }

    explicit shuffle_order_engine(base_type&& rng) : _rng(rng) { init(); }


    template<class It> shuffle_order_engine(It& first, It last)
      : _rng(first, last) { init(); }

    void seed() { _rng.seed(); init(); }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(shuffle_order_engine,
        result_type, seed_arg)
    { _rng.seed(seed_arg); init(); }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(shuffle_order_engine, SeedSeq, seq)
    { _rng.seed(seq); init(); }

    template<class It> void seed(It& first, It last)
    { _rng.seed(first, last); init(); }


    const base_type& base() const { return _rng; }


    result_type operator()() {
        // calculating the range every time may seem wasteful.  However, this
        // makes the information locally available for the optimizer.
        typedef typename make_unsigned<result_type>::type base_unsigned;
        const base_unsigned brange =
            detail::subtract<result_type>()((max)(), (min)());
        const base_unsigned off =
            detail::subtract<result_type>()(y, (min)());

        base_unsigned j;
        if(k == 1) {
            j = 0;
        } else if(brange < (std::numeric_limits<base_unsigned>::max)() / k) {
            // try to do it in the native type if we know that it won't
            // overflow
            j = k * off / (brange + 1);
        } else if(brange < (std::numeric_limits<uintmax_t>::max)() / k) {
            // Otherwise try to use uint64_t
            j = static_cast<base_unsigned>(
                static_cast<uintmax_t>(off) * k /
                (static_cast<uintmax_t>(brange) + 1));
        } else {
            boost::uintmax_t divisor =
                static_cast<boost::uintmax_t>(brange) + 1;
            j = static_cast<base_unsigned>(detail::muldiv(off, k, divisor));
        }
        // assert(0 <= j && j < k);
        y = v[j];
        v[j] = _rng();
        return y;
    }

    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    discard_block_engine() : _rng(), _n(0) { }

    explicit discard_block_engine(const base_type & rng) : _rng(rng), _n(0) { }

    explicit discard_block_engine(base_type && rng) : _rng(rng), _n(0) { }

    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(discard_block_engine,
                                               seed_type, value)
    { _rng.seed(value); _n = 0; }

    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(discard_block_engine, SeedSeq, seq)
    { _rng.seed(seq); _n = 0; }

    template<class It> discard_block_engine(It& first, It last)
      : _rng(first, last), _n(0) { }

    void seed() { _rng.seed(); _n = 0; }

    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(discard_block_engine, seed_type, s)
    { _rng.seed(s); _n = 0; }

    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(discard_block_engine, SeedSeq, seq)
    { _rng.seed(seq); _n = 0; }

    template<class It> void seed(It& first, It last)
    { _rng.seed(first, last); _n = 0; }

    const base_type& base() const { return _rng; }

    result_type operator()()
    {
        if(_n >= returned_block) {
            // discard values of random number generator
            // Don't use discard, since we still need to
            // be somewhat compatible with TR1.
            // _rng.discard(total_block - _n);
            for(std::size_t i = 0; i < total_block - _n; ++i) {
                _rng();
            }
            _n = 0;
        }
        ++_n;
        return _rng();
    }


    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }


    template<class It>
    void generate(It first, It last)
    { detail::generate(*this, first, last); }

    discard_block() {}

    template<class T>
    discard_block(T& arg) : base_t(arg) {}

    template<class T>
    discard_block(const T& arg) : base_t(arg) {}

    template<class It>
    discard_block(It& first, It last) : base_t(first, last) {}

        static std::size_t value() { return generator_bits<URNG>::value(); }

        static std::size_t value() { return generator_bits<URNG>::value(); }

        param_type()
        {
            _weights.push_back(WeightType(1));
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }

        template<class IntervalIter, class WeightIter>
        param_type(IntervalIter intervals_first, IntervalIter intervals_last,
                   WeightIter weight_first)
          : _intervals(intervals_first, intervals_last)
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
                _weights.push_back(WeightType(1));
            } else {
                _weights.reserve(_intervals.size() - 1);
                for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                    _weights.push_back(*weight_first++);
                }
            }
        }

        template<class IntervalRange, class WeightRange>
        param_type(const IntervalRange& intervals_arg,
                   const WeightRange& weights_arg)
          : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
            _weights(boost::begin(weights_arg), boost::end(weights_arg))
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
                _weights.push_back(WeightType(1));
            }
        }

    piecewise_constant_distribution()
    {
        _intervals.push_back(RealType(0));
        _intervals.push_back(RealType(1));
    }

    template<class IntervalIter, class WeightIter>
    piecewise_constant_distribution(IntervalIter first_interval,
                                    IntervalIter last_interval,
                                    WeightIter first_weight)
      : _intervals(first_interval, last_interval)
    {
        if(_intervals.size() < 2) {
            _intervals.clear();
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        } else {
            std::vector<WeightType> actual_weights;
            actual_weights.reserve(_intervals.size() - 1);
            for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                actual_weights.push_back(*first_weight++);
            }
            typedef discrete_distribution<std::size_t, WeightType> bins_type;
            typename bins_type::param_type bins_param(actual_weights);
            _bins.param(bins_param);
        }
    }

    template<class IntervalsRange, class WeightsRange>
    piecewise_constant_distribution(const IntervalsRange& intervals_arg,
                                    const WeightsRange& weights_arg)
      : _bins(weights_arg),
        _intervals(boost::begin(intervals_arg), boost::end(intervals_arg))
    {
        if(_intervals.size() < 2) {
            _intervals.clear();
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }
    }

    explicit piecewise_constant_distribution(const param_type& parm)
      : _bins(parm._weights),
        _intervals(parm._intervals)
    {
    }

    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        std::size_t i = _bins(urng);
        return uniform_real<RealType>(_intervals[i], _intervals[i+1])(urng);
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return piecewise_constant_distribution(parm)(urng);
    }


  explicit backward_compatible_uniform_01(typename traits::rvalue_type rng)
    : _rng(rng),
      _factor(result_type(1) /
              (result_type((base().max)()-(base().min)()) +
               result_type(std::numeric_limits<base_result>::is_integer ? 1 : 0)))
  {
  }

        param_type(const RealType& alpha_arg = RealType(1.0),
                   const RealType& beta_arg = RealType(1.0))
          : _alpha(alpha_arg), _beta(beta_arg)
        {
        }

        RealType alpha() const { return _alpha; }

        RealType beta() const { return _beta; }

    explicit gamma_distribution(const result_type& alpha_arg = result_type(1.0),
                                const result_type& beta_arg = result_type(1.0))
      : _exp(result_type(1)), _alpha(alpha_arg), _beta(beta_arg)
    {
        BOOST_ASSERT(_alpha > result_type(0));
        BOOST_ASSERT(_beta > result_type(0));
        init();
    }

    explicit gamma_distribution(const param_type& parm)
      : _exp(result_type(1)), _alpha(parm.alpha()), _beta(parm.beta())
    {
        init();
    }

    RealType alpha() const { return _alpha; }

    RealType beta() const { return _beta; }

        explicit param_type(RealType mean_arg = RealType(0.0),
                            RealType sigma_arg = RealType(1.0))
          : _mean(mean_arg),
            _sigma(sigma_arg)
        {}

        RealType mean() const { return _mean; }

        RealType sigma() const { return _sigma; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._mean << " " << parm._sigma ; return os; }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._mean >> std::ws >> parm._sigma; return is; }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._mean == rhs._mean && lhs._sigma == rhs._sigma; }

    explicit normal_distribution(const RealType& mean_arg = RealType(0.0),
                                 const RealType& sigma_arg = RealType(1.0))
      : _mean(mean_arg), _sigma(sigma_arg),
        _r1(0), _r2(0), _cached_rho(0), _valid(false)
    {
        BOOST_ASSERT(_sigma >= RealType(0));
    }

    explicit normal_distribution(const param_type& parm)
      : _mean(parm.mean()), _sigma(parm.sigma()),
        _r1(0), _r2(0), _cached_rho(0), _valid(false)
    {}

    RealType mean() const { return _mean; }

    RealType sigma() const { return _sigma; }

        explicit param_type(RealType n_arg = RealType(1))
          : _n(n_arg)
        {}

        RealType n() const { return _n; }

    explicit chi_squared_distribution(RealType n_arg = RealType(1))
      : _impl(n_arg / 2)
    {
    }

    explicit chi_squared_distribution(const param_type& parm)
      : _impl(parm.n() / 2)
    {
    }

    template<class URNG>
    RealType operator()(URNG& urng)
    {
        return 2 * _impl(urng);
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return chi_squared_distribution(parm)(urng);
    }

    RealType n() const { return 2 * _impl.alpha(); }

        param_type(RealType lambda_arg = RealType(1.0))
          : _lambda(lambda_arg) { BOOST_ASSERT(_lambda > RealType(0)); }

        RealType lambda() const { return _lambda; }

        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._lambda;
            return os;
        }

        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._lambda;
            return is;
        }

        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._lambda == rhs._lambda; }

    explicit exponential_distribution(RealType lambda_arg = RealType(1.0))
      : _lambda(lambda_arg) { BOOST_ASSERT(_lambda > RealType(0)); }

    explicit exponential_distribution(const param_type& parm)
      : _lambda(parm.lambda()) {}

    RealType lambda() const { return _lambda; }

  result_type operator()(T x, T y) { return x - y; }

  result_type operator()(T1 x, T2 y) { return T2(x) + y; }

  static IntType apply(IntType x)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(x)) & (unsigned_m() - 1);
    else {
      IntType supress_warnings = (m == 0);
      BOOST_ASSERT(supress_warnings == 0);
      return x % (m + supress_warnings);
    }
  }


  static IntType add(IntType x, IntType c)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1);
    else if(c == 0)
      return x;
    else if(x < m - c)
      return x + c;
    else
      return x - (m - c);
  }


  static IntType mult(IntType a, IntType x)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return unsigned_type(a) * unsigned_type(x) & (unsigned_m() - 1);
    else if(a == 0)
      return 0;
    else if(a == 1)
      return x;
    else if(m <= traits::const_max/a)      // i.e. a*m <= max
      return mult_small(a, x);
    else if(traits::is_signed && (m%a < m/a))
      return mult_schrage(a, x);
    else
      return mult_general(a, x);
  }


  static IntType mult_add(IntType a, IntType x, IntType c)
  {
    if(((unsigned_m() - 1) & unsigned_m()) == 0)
      return (unsigned_type(a) * unsigned_type(x) + unsigned_type(c)) & (unsigned_m() - 1);
    else if(a == 0)
      return c;
    else if(m <= (traits::const_max-c)/a) {  // i.e. a*m+c <= max
      IntType supress_warnings = (m == 0);
      BOOST_ASSERT(supress_warnings == 0);
      return (a*x+c) % (m + supress_warnings);
    } else
      return add(mult(a, x), c);
  }


  static IntType pow(IntType a, boost::uintmax_t exponent)
  {
      IntType result = 1;
      while(exponent != 0) {
          if(exponent % 2 == 1) {
              result = mult(result, a);
          }
          a = mult(a, a);
          exponent /= 2;
      }
      return result;
  }


  static IntType invert(IntType x)
  { return x == 0 ? 0 : (m == 0? invert_euclidian0(x) : invert_euclidian(x)); }


  static IntType mult_small(IntType a, IntType x)
  {
    IntType supress_warnings = (m == 0);
    BOOST_ASSERT(supress_warnings == 0);
    return a*x % (m + supress_warnings);
  }


  static IntType mult_schrage(IntType a, IntType value)
  {
    const IntType q = m / a;
    const IntType r = m % a;

    BOOST_ASSERT(r < q);        // check that overflow cannot happen

    return sub(a*(value%q), r*(value/q));
  }


  static IntType mult_general(IntType a, IntType b)
  {
    IntType suppress_warnings = (m == 0);
    BOOST_ASSERT(suppress_warnings == 0);
    IntType modulus = m + suppress_warnings;
    BOOST_ASSERT(modulus == m);
    if(::boost::uintmax_t(modulus) <=
        (::std::numeric_limits< ::boost::uintmax_t>::max)() / modulus)
    {
      return static_cast<IntType>(boost::uintmax_t(a) * b % modulus);
    } else {
      return static_cast<IntType>(detail::mulmod(a, b, modulus));
    }
  }


  static IntType sub(IntType a, IntType b)
  {
    if(a < b)
      return m - (b - a);
    else
      return a - b;
  }


  static unsigned_type unsigned_m()
  {
      if(m == 0) {
          return unsigned_type((std::numeric_limits<IntType>::max)()) + 1;
      } else {
          return unsigned_type(m);
      }
  }

  static IntType invert_euclidian(IntType c)
  {
    // we are interested in the gcd factor for c, because this is our inverse
    BOOST_ASSERT(c > 0);
    IntType l1 = 0;
    IntType l2 = 1;
    IntType n = c;
    IntType p = m;
    for(;;) {
      IntType q = p / n;
      l1 += q * l2;
      p -= q * n;
      if(p == 0)
        return l2;
      IntType q2 = n / p;
      l2 += q2 * l1;
      n -= q2 * p;
      if(n == 0)
        return m - l1;
    }
  }

  static IntType invert_euclidian0(IntType c)
  {
    // we are interested in the gcd factor for c, because this is our inverse
    BOOST_ASSERT(c > 0);
    if(c == 1) return 1;
    IntType l1 = 0;
    IntType l2 = 1;
    IntType n = c;
    IntType p = m;
    IntType max = (std::numeric_limits<IntType>::max)();
    IntType q = max / n;
    BOOST_ASSERT(max % n != n - 1 && "c must be relatively prime to m.");
    l1 += q * l2;
    p = max - q * n + 1;
    for(;;) {
      if(p == 0)
        return l2;
      IntType q2 = n / p;
      l2 += q2 * l1;
      n -= q2 * p;
      if(n == 0)
        return m - l1;
      q = p / n;
      l1 += q * l2;
      p -= q * n;
    }
  }

  Generator& operator++() { v = cast()(); return cast(); }

  const value_type& operator*() const { return v; }

  generator_iterator_mixin_adapter() { }

  void iterator_init() { operator++(); }

  Generator & cast() { return static_cast<Generator&>(*this); }

    template<class T>
    static T call(T arg, int n, T result)
    {
        return const_pow_impl<N / 2>::call(arg * arg, n / 2,
            n%2 == 0? result : result * arg);
    }

    template<class T>
    static T call(T, int, T result)
    {
        return result;
    }

template<int N, class T>
inline T const_pow(T arg, int n) { return const_pow_impl<N>::call(arg, n, T(1)); }


template<class T>
inline T pow2(int n)
{
    typedef unsigned int_type;
    const int max_bits = std::numeric_limits<int_type>::digits;
    T multiplier = T(int_type(1) << (max_bits - 1)) * 2;
    return (int_type(1) << (n % max_bits)) *
        const_pow<std::numeric_limits<T>::digits / max_bits>(multiplier, n / max_bits);
}


template<class Engine, class Iter>
void generate_from_real(Engine& eng, Iter begin, Iter end)
{
    using std::fmod;
    typedef typename Engine::result_type RealType;
    const int Bits = detail::generator_bits<Engine>::value();
    int remaining_bits = 0;
    boost::uint_least32_t saved_bits = 0;
    RealType multiplier = pow2<RealType>( Bits);
    RealType mult32 = RealType(4294967296.0); // 2^32
    while(true) {
        RealType val = eng() * multiplier;
        int available_bits = Bits;
        // Make sure the compiler can optimize this out
        // if it isn't possible.
        if(Bits < 32 && available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint_least32_t(val) << remaining_bits;
            remaining_bits += Bits;
        } else {
            // If Bits < 32, then remaining_bits != 0, since
            // if remaining_bits == 0, available_bits < 32 - 0,
            // and we won't get here to begin with.
            if(Bits < 32 || remaining_bits != 0) {
                boost::uint_least32_t divisor =
                    (boost::uint_least32_t(1) << (32 - remaining_bits));
                boost::uint_least32_t extra_bits = boost::uint_least32_t(fmod(val, mult32)) & (divisor - 1);
                val = val / divisor;
                *begin++ = saved_bits | (extra_bits << remaining_bits);
                if(begin == end) return;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            // If Bits < 32 we should never enter this loop
            if(Bits >= 32) {
                for(; available_bits >= 32; available_bits -= 32) {
                    boost::uint_least32_t word = boost::uint_least32_t(fmod(val, mult32));
                    val /= mult32;
                    *begin++ = word;
                    if(begin == end) return;
                }
            }
            remaining_bits = available_bits;
            saved_bits = static_cast<boost::uint_least32_t>(val);
        }
    }
}


template<class Engine, class Iter>
void generate_from_int(Engine& eng, Iter begin, Iter end)
{
    typedef typename Engine::result_type IntType;
    typedef typename boost::make_unsigned<IntType>::type unsigned_type;
    int remaining_bits = 0;
    boost::uint_least32_t saved_bits = 0;
    unsigned_type range = boost::random::detail::subtract<IntType>()((eng.max)(), (eng.min)());

    int bits =
        (range == (std::numeric_limits<unsigned_type>::max)()) ?
            std::numeric_limits<unsigned_type>::digits :
            detail::integer_log2(range + 1);

    {
        int discarded_bits = detail::integer_log2(bits);
        unsigned_type excess = (range + 1) >> (bits - discarded_bits);
        if(excess != 0) {
            int extra_bits = detail::integer_log2((excess - 1) ^ excess);
            bits = bits - discarded_bits + extra_bits;
        }
    }

    unsigned_type mask = (static_cast<unsigned_type>(2) << (bits - 1)) - 1;
    unsigned_type limit = ((range + 1) & ~mask) - 1;

    while(true) {
        unsigned_type val;
        do {
            val = boost::random::detail::subtract<IntType>()(eng(), (eng.min)());
        } while(limit != range && val > limit);
        val &= mask;
        int available_bits = bits;
        if(available_bits == 32) {
            *begin++ = static_cast<boost::uint_least32_t>(val) & 0xFFFFFFFFu;
            if(begin == end) return;
        } else if(available_bits % 32 == 0) {
            for(int i = 0; i < available_bits / 32; ++i) {
                boost::uint_least32_t word = boost::uint_least32_t(val) & 0xFFFFFFFFu;
                int supress_warning = (bits >= 32);
                BOOST_ASSERT(supress_warning == 1);
                val >>= (32 * supress_warning);
                *begin++ = word;
                if(begin == end) return;
            }
        } else if(bits < 32 && available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint_least32_t(val) << remaining_bits;
            remaining_bits += bits;
        } else {
            if(bits < 32 || remaining_bits != 0) {
                boost::uint_least32_t extra_bits = boost::uint_least32_t(val) & ((boost::uint_least32_t(1) << (32 - remaining_bits)) - 1);
                val >>= 32 - remaining_bits;
                *begin++ = saved_bits | (extra_bits << remaining_bits);
                if(begin == end) return;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            if(bits >= 32) {
                for(; available_bits >= 32; available_bits -= 32) {
                    boost::uint_least32_t word = boost::uint_least32_t(val) & 0xFFFFFFFFu;
                    int supress_warning = (bits >= 32);
                    BOOST_ASSERT(supress_warning == 1);
                    val >>= (32 * supress_warning);
                    *begin++ = word;
                    if(begin == end) return;
                }
            }
            remaining_bits = available_bits;
            saved_bits = static_cast<boost::uint_least32_t>(val);
        }
    }
}


template<class Engine, class Iter>
void generate_impl(Engine& eng, Iter first, Iter last, boost::mpl::true_)
{
    return detail::generate_from_int(eng, first, last);
}


template<class Engine, class Iter>
void generate(Engine& eng, Iter first, Iter last)
{
    return detail::generate_impl(eng, first, last, boost::is_integral<typename Engine::result_type>());
}




template<class IntType, IntType m, class SeedSeq>
IntType seed_one_int(SeedSeq& seq)
{
    static const int log = ::boost::mpl::if_c<(m == 0),
        ::boost::mpl::int_<(::std::numeric_limits<IntType>::digits)>,
        ::boost::static_log2<m> >::type::value;
    static const int k =
        (log + ((~(static_cast<IntType>(2) << (log - 1)) & m)? 32 : 31)) / 32;
    ::boost::uint_least32_t array[log / 32 + 4];
    seq.generate(&array[0], &array[0] + k + 3);
    IntType s = 0;
    for(int j = 0; j < k; ++j) {
        IntType digit = const_mod<IntType, m>::apply(IntType(array[j+3]));
        IntType mult = IntType(1) << 32*j;
        s = const_mod<IntType, m>::mult_add(mult, digit, s);
    }
    return s;
}


template<class IntType, IntType m, class Iter>
IntType get_one_int(Iter& first, Iter last)
{
    static const int log = ::boost::mpl::if_c<(m == 0),
        ::boost::mpl::int_<(::std::numeric_limits<IntType>::digits)>,
        ::boost::static_log2<m> >::type::value;
    static const int k =
        (log + ((~(static_cast<IntType>(2) << (log - 1)) & m)? 32 : 31)) / 32;
    IntType s = 0;
    for(int j = 0; j < k; ++j) {
        if(first == last) {
            throw ::std::invalid_argument("Not enough elements in call to seed.");
        }
        IntType digit = const_mod<IntType, m>::apply(IntType(*first++));
        IntType mult = IntType(1) << 32*j;
        s = const_mod<IntType, m>::mult_add(mult, digit, s);
    }
    return s;
}

template<int w, std::size_t n, class SeedSeq, class UIntType>
void seed_array_int_impl(SeedSeq& seq, UIntType (&x)[n])
{
    boost::uint_least32_t storage[((w+31)/32) * n];
    seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
    for(std::size_t j = 0; j < n; j++) {
        UIntType val = 0;
        for(std::size_t k = 0; k < (w+31)/32; ++k) {
            val += static_cast<UIntType>(storage[(w+31)/32*j + k]) << 32*k;
        }
        x[j] = val & ::boost::low_bits_mask_t<w>::sig_bits;
    }
}


template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int(SeedSeq& seq, IntType (&x)[n])
{
    seed_array_int_impl<w>(seq, x, boost::is_signed<IntType>());
}


template<int w, std::size_t n, class Iter, class UIntType>
void fill_array_int_impl(Iter& first, Iter last, UIntType (&x)[n])
{
    for(std::size_t j = 0; j < n; j++) {
        UIntType val = 0;
        for(std::size_t k = 0; k < (w+31)/32; ++k) {
            if(first == last) {
                throw std::invalid_argument("Not enough elements in call to seed.");
            }
            val += static_cast<UIntType>(*first++) << 32*k;
        }
        x[j] = val & ::boost::low_bits_mask_t<w>::sig_bits;
    }
}


template<int w, std::size_t n, class Iter, class IntType>
inline void fill_array_int(Iter& first, Iter last, IntType (&x)[n])
{
    fill_array_int_impl<w>(first, last, x, boost::is_signed<IntType>());
}


template<int w, std::size_t n, class RealType>
void seed_array_real_impl(const boost::uint_least32_t* storage, RealType (&x)[n])
{
    boost::uint_least32_t mask = ~((~boost::uint_least32_t(0)) << (w%32));
    RealType two32 = 4294967296.0;
    const RealType divisor = RealType(1)/detail::pow2<RealType>(w);
    unsigned int j;
    for(j = 0; j < n; ++j) {
        RealType val = RealType(0);
        RealType mult = divisor;
        for(int k = 0; k < w/32; ++k) {
            val += *storage++ * mult;
            mult *= two32;
        }
        if(mask != 0) {
            val += (*storage++ & mask) * mult;
        }
        BOOST_ASSERT(val >= 0);
        BOOST_ASSERT(val < 1);
        x[j] = val;
    }
}


template<int w, std::size_t n, class SeedSeq, class RealType>
void seed_array_real(SeedSeq& seq, RealType (&x)[n])
{
    using std::pow;
    boost::uint_least32_t storage[((w+31)/32) * n];
    seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
    seed_array_real_impl<w>(storage, x);
}


template<int w, std::size_t n, class Iter, class RealType>
void fill_array_real(Iter& first, Iter last, RealType (&x)[n])
{
    boost::uint_least32_t mask = ~((~boost::uint_least32_t(0)) << (w%32));
    RealType two32 = 4294967296.0;
    const RealType divisor = RealType(1)/detail::pow2<RealType>(w);
    unsigned int j;
    for(j = 0; j < n; ++j) {
        RealType val = RealType(0);
        RealType mult = divisor;
        for(int k = 0; k < w/32; ++k, ++first) {
            if(first == last) throw std::invalid_argument("Not enough elements in call to seed.");
            val += *first * mult;
            mult *= two32;
        }
        if(mask != 0) {
            if(first == last) throw std::invalid_argument("Not enough elements in call to seed.");
            val += (*first & mask) * mult;
            ++first;
        }
        BOOST_ASSERT(val >= 0);
        BOOST_ASSERT(val < 1);
        x[j] = val;
    }
}

    generator_seed_seq(Generator& g) : gen(&g) {}

    template<class It>
    void generate(It first, It last) {
        for(; first != last; ++first) {
            *first = (*gen)();
        }
    }


inline div_t muldivmod(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{
    static const int bits =
        ::std::numeric_limits< ::boost::uintmax_t>::digits / 2;
    static const ::boost::uintmax_t mask = (::boost::uintmax_t(1) << bits) - 1;
    typedef ::boost::uint_t<bits>::fast digit_t;

    int shift = std::numeric_limits< ::boost::uintmax_t>::digits - 1
        - detail::integer_log2(m);

    a <<= shift;
    m <<= shift;

    digit_t product[4] = { 0, 0, 0, 0 };
    digit_t a_[2] = { digit_t(a & mask), digit_t((a >> bits) & mask) };
    digit_t b_[2] = { digit_t(b & mask), digit_t((b >> bits) & mask) };
    digit_t m_[2] = { digit_t(m & mask), digit_t((m >> bits) & mask) };

    // multiply a * b
    for(int i = 0; i < 2; ++i) {
        digit_t carry = 0;
        for(int j = 0; j < 2; ++j) {
            ::boost::uint64_t temp = ::boost::uintmax_t(a_[i]) * b_[j] +
                carry + product[i + j];
            product[i + j] = digit_t(temp & mask);
            carry = digit_t(temp >> bits);
        }
        if(carry != 0) {
            product[i + 2] += carry;
        }
    }

    digit_t quotient[2];

    if(m == 0) {
        div_t result = {
            ((::boost::uintmax_t(product[3]) << bits) | product[2]),
            ((::boost::uintmax_t(product[1]) << bits) | product[0]) >> shift,
        };
        return result;
    }

    // divide product / m
    for(int i = 3; i >= 2; --i) {
        ::boost::uintmax_t temp =
            ::boost::uintmax_t(product[i]) << bits | product[i - 1];

        digit_t q = digit_t((product[i] == m_[1]) ? mask : temp / m_[1]);

        ::boost::uintmax_t rem =
            ((temp - ::boost::uintmax_t(q) * m_[1]) << bits) + product[i - 2];

        ::boost::uintmax_t diff = m_[0] * ::boost::uintmax_t(q);

        int error = 0;
        if(diff > rem) {
            if(diff - rem > m) {
                error = 2;
            } else {
                error = 1;
            }
        }
        q -= error;
        rem = rem + error * m - diff;

        quotient[i - 2] = q;
        product[i] = 0;
        product[i-1] = (rem >> bits) & mask;
        product[i-2] = rem & mask;
    }

    div_t result = {
        ((::boost::uintmax_t(quotient[1]) << bits) | quotient[0]),
        ((::boost::uintmax_t(product[1]) << bits) | product[0]) >> shift,
    };
    return result;
}


inline boost::uintmax_t muldiv(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{ return detail::muldivmod(a, b, m).quotient; }


inline boost::uintmax_t mulmod(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{ return detail::muldivmod(a, b, m).remainder; }

  static reference_type ref(T& r) { return r; }

  static const T& ref(const T& r) { return r; }

  static reference_type ref(T& r) { return r; }

  static const T& ref(const T& r) { return r; }

  static reference_type ref(T * p) { return *p; }

  static const T& ref(const T * p) { return *p; }

    static std::size_t value() {
        return std::numeric_limits<typename URNG::result_type>::digits;
    }


    uniform_int_float(base_type& rng)
      : _rng(rng) {}
