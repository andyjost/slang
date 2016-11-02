
                                 
        static integer_type numerator()      { return Numerator; }

        static integer_type denominator()    { return Denominator; }

        static_rational() { }

template<class Archive,class System,class Dim>
inline void serialize(Archive& ar,boost::units::unit<Dim,System>&,const unsigned int /*version*/)
{ }

template<class T> std::string to_string(const T& t)
{
    std::stringstream sstr;
    
    sstr << t;
    
    return sstr.str();
}

    xalloc_key_initializer_t() 
    {
        if (!xalloc_key_holder<true>::initialized) 
        {
            xalloc_key_holder<true>::value = std::ios_base::xalloc();
            xalloc_key_holder<true>::initialized = true;
        }
    }

inline long get_flags(std::ios_base& ios, long mask) 
{
    return(ios.iword(detail::xalloc_key_holder<true>::value) & mask);
}

inline void set_flags(std::ios_base& ios, long new_flags, long mask) 
{
    assert((~mask & new_flags) == 0);
    long& flags = ios.iword(detail::xalloc_key_holder<true>::value);
    flags = (flags & ~mask) | new_flags;
}

inline format_mode get_format(std::ios_base& ios) 
{
    return(static_cast<format_mode>((get_flags)(ios, fmt_mask)));
}

inline void set_format(std::ios_base& ios, format_mode new_mode) 
{
    (set_flags)(ios, new_mode, fmt_mask);
}

inline std::ios_base& typename_format(std::ios_base& ios) 
{
    (set_format)(ios, typename_fmt);
    return(ios);
}

inline std::ios_base& raw_format(std::ios_base& ios) 
{
    (set_format)(ios, raw_fmt);
    return(ios);
}

inline std::ios_base& symbol_format(std::ios_base& ios) 
{
    (set_format)(ios, symbol_fmt);
    return(ios);
}

inline std::ios_base& name_format(std::ios_base& ios) 
{
    (set_format)(ios, name_fmt);
    return(ios);
}

inline autoprefix_mode get_autoprefix(std::ios_base& ios)
{
    return static_cast<autoprefix_mode>((get_flags)(ios, autoprefix_mask));
}

inline void set_autoprefix(std::ios_base& ios, autoprefix_mode new_mode)
{
    (set_flags)(ios, new_mode, autoprefix_mask);
}

inline std::ios_base& no_prefix(std::ios_base& ios)
{
    (set_autoprefix)(ios, autoprefix_none);
    return ios;
}

inline std::ios_base& engineering_prefix(std::ios_base& ios)
{
    (set_autoprefix)(ios, autoprefix_engineering);
    return ios;
}

inline std::ios_base& binary_prefix(std::ios_base& ios)
{
    (set_autoprefix)(ios, autoprefix_binary);
    return ios;
}

template<integer_type N, integer_type D>
inline std::string exponent_string(const static_rational<N,D>& r)
{
    return '^' + to_string(r);
}


template<class T>
inline std::string base_unit_symbol_string(const T&)
{
    return base_unit_info<typename T::tag_type>::symbol() + exponent_string(typename T::value_type());
}


template<class T>    
inline std::string base_unit_name_string(const T&)
{
    return base_unit_info<typename T::tag_type>::name() + exponent_string(typename T::value_type());
}

        static void value(std::string& str)
        {
            str += base_unit_symbol_string(typename Begin::item()) + ' ';
            next::value(str);
        }

        static void value(std::string& str)
        {
            str += base_unit_symbol_string(typename Begin::item());
        };

        static void value(std::string& str)
        {
            // better shorthand for dimensionless?
            str += "dimensionless";
        }

        static void value(std::string& str) 
        {
            str += Begin::item::symbol();
            scale_symbol_string_impl<N - 1>::template apply<typename Begin::next>::value(str);
        }

        static void value(std::string&) { }

        static void value(std::string& str)
        {
            str += base_unit_name_string(typename Begin::item()) + ' ';
            next::value(str);
        }

        static void value(std::string& str)
        {
            str += base_unit_name_string(typename Begin::item());
        };

        static void value(std::string& str)
        {
            str += "dimensionless";
        }

        static void value(std::string& str) 
        {
            str += Begin::item::name();
            scale_name_string_impl<N - 1>::template apply<typename Begin::next>::value(str);
        }

        static void value(std::string&) { }

template<class Dimension,class System, class SubFormatter>
inline std::string
to_string_impl(const unit<Dimension,System>&, SubFormatter f)
{
    return f(typename reduce_unit<unit<Dimension, System> >::type());
}

    template<class Units>
    void append_units_to(std::string& str) {
        detail::symbol_string_impl<Units::size::value>::template apply<Units>::value(str);
    }

    template<class Scale>
    void append_scale_to(std::string& str) {
        detail::scale_symbol_string_impl<Scale::size::value>::template apply<Scale>::value(str);
    }

    template<class Unit>
    std::string operator()(const Unit& u) {
        return(to_string_impl(u, *this));
    }

    template<class Unit>
    bool is_default_string(const std::string&, const Unit&) {
        return(true);
    }

    template<class Unit>
    std::string operator()(const Unit& u) {
        return(symbol_string(u));
    }

    template<class Unit>
    bool is_default_string(const std::string& str, const Unit& u) {
        return(str == to_string_impl(u, format_raw_symbol_impl()));
    }

    template<class Units>
    void append_units_to(std::string& str) {
        detail::name_string_impl<(Units::size::value)>::template apply<Units>::value(str);
    }

    template<class Scale>
    void append_scale_to(std::string& str) {
        detail::scale_name_string_impl<Scale::size::value>::template apply<Scale>::value(str);
    }

    template<class Unit>
    std::string operator()(const Unit& u) {
        return(to_string_impl(u, *this));
    }

    template<class Unit>
    bool is_default_string(const std::string&, const Unit&) {
        return(true);
    }

    template<class Unit>
    std::string operator()(const Unit& u) {
        return(name_string(u));
    }

    template<class Unit>
    bool is_default_string(const std::string& str, const Unit& u) {
        return(str == to_string_impl(u, format_raw_name_impl()));
    }

    static double call(const T& arg) { return std::abs(arg); }


template<class T>
typename autoprefix_norm_impl<T>::type autoprefix_norm(const T& arg)
{
    return autoprefix_norm_impl<T>::call(arg);
}


template<class End, class Prev, class T, class F>
bool find_matching_scale_impl(End, End, Prev, T, double, F)
{
    return false;
}


template<class Begin, class End, class Prev, class T, class F>
bool find_matching_scale_impl(Begin, End end, Prev prev, T t, double x, F f)
{
    if(Begin::item::value() > x) {
        f(prev, t);
        return true;
    } else {
        return detail::find_matching_scale_impl(
            typename Begin::next(),
            end,
            typename Begin::item(),
            t,
            x,
            f
        );
    }
}


template<class End, class T, class F>
bool find_matching_scale_i(End, End, T, double, F)
{
    return false;
}


template<class Begin, class End, class T, class F>
bool find_matching_scale_i(Begin, End end, T t, double x, F f)
{
    if(Begin::item::value() > x) {
        return false;
    } else {
        return detail::find_matching_scale_impl(typename Begin::next(), end, typename Begin::item(), t, x, f);
    }
}


template<class Scales, class T, class F>
bool find_matching_scale(T t, double x, F f)
{
    return detail::find_matching_scale_i(Scales(), dimensionless_type(), t, x, f);
}

    void operator()() const
    {
        *os << q->value() << ' ' << typename Quantity::unit_type();
    }


template<class Os, class Quantity>
print_default_t<Os, Quantity> print_default(Os& os, const Quantity& q)
{
    print_default_t<Os, Quantity> result = { &os, &q };
    return result;
}

    template<class Prefix, class T>
    void operator()(Prefix, const T& t) const
    {
        *prefixed = true;
        *os << t / Prefix::value() << ' ';
        switch(units::get_format(*os)) {
            case name_fmt: do_print(*os, Prefix::name()); break;
            case raw_fmt:
            case symbol_fmt: do_print(*os, Prefix::symbol()); break;
            case typename_fmt: do_print(*os, units::simplify_typename(Prefix())); *os << ' '; break;
        }
    }


template<class Os>
print_scale_t<Os> print_scale(Os& os, bool& prefixed)
{
    print_scale_t<Os> result = { &os, &prefixed };
    return result;
}

template<class Dimension,class Units,class Scale, class Subformatter>
inline std::string
maybe_parenthesize(const unit<Dimension, heterogeneous_system<heterogeneous_system_impl<Units, Dimension, Scale> > >&, Subformatter f)
{
    std::string str;

    std::string without_scale = f(unit<Dimension, heterogeneous_system<heterogeneous_system_impl<Units, Dimension, dimensionless_type> > >());

    if (f.is_default_string(without_scale, unit<Dimension, heterogeneous_system<heterogeneous_system_impl<Units, Dimension, dimensionless_type> > >()))
    {
        str += "(";
        str += without_scale;
        str += ")";
    }
    else
    {
        str += without_scale;
    }

    return(str);
}


inline mpl::true_ test_norm(double) { return mpl::true_(); }


template<class Dimension,class System>
inline std::string
typename_string(const unit<Dimension, System>&)
{
    return simplify_typename(typename reduce_unit< unit<Dimension,System> >::type());
}


template<class Dimension,class System>
inline std::string
symbol_string(const unit<Dimension, System>&)
{
    return detail::to_string_impl(unit<Dimension,System>(), detail::format_symbol_impl());
}


template<class Dimension,class System>
inline std::string
name_string(const unit<Dimension, System>&)
{
    return detail::to_string_impl(unit<Dimension,System>(), detail::format_name_impl());
}

 
        quantity() : val_() 
        { 
            BOOST_UNITS_CHECK_LAYOUT_COMPATIBILITY(this_type, Y);
        }


        quantity(unspecified_null_pointer_constant_type) : val_() 
        { 
            BOOST_UNITS_CHECK_LAYOUT_COMPATIBILITY(this_type, Y);
        }

        
        quantity(const this_type& source) : val_(source.val_) 
        {
            BOOST_UNITS_CHECK_LAYOUT_COMPATIBILITY(this_type, Y);
        }

        
        this_type& operator=(const this_type& source) 
        { 
             val_ = source.val_; 
             
             return *this; 
        }

        template<class YY>
        this_type& operator=(const quantity<Unit,YY>& source)
        {
            BOOST_STATIC_ASSERT((boost::is_convertible<YY, Y>::value == true));

            *this = this_type(source);
            
            return *this;
        }

        template<class Unit2,class YY>
        this_type& operator=(const quantity<Unit2,YY>& source)
        {
            
            BOOST_STATIC_ASSERT((is_implicitly_convertible<Unit2,unit_type>::value == true));
            BOOST_STATIC_ASSERT((boost::is_convertible<YY,Y>::value == true));
            
            *this = this_type(source);
            
            return *this;
        }


        const value_type& value() const                     { return val_; }

        template<class Unit2, class YY>
        this_type& operator+=(const quantity<Unit2, YY>& source)
        {
            BOOST_STATIC_ASSERT((boost::is_same<typename add_typeof_helper<Unit, Unit2>::type, Unit>::value));
            val_ += source.value();
            return *this;
        }

        template<class Unit2, class YY>
        this_type& operator-=(const quantity<Unit2, YY>& source)
        {
            BOOST_STATIC_ASSERT((boost::is_same<typename subtract_typeof_helper<Unit, Unit2>::type, Unit>::value));
            val_ -= source.value();
            return *this;
        }
  

        template<class Unit2, class YY>
        this_type& operator*=(const quantity<Unit2, YY>& source)
        {
            BOOST_STATIC_ASSERT((boost::is_same<typename multiply_typeof_helper<Unit, Unit2>::type, Unit>::value));
            val_ *= source.value();
            return *this;
        }
  
        
        template<class Unit2, class YY>
        this_type& operator/=(const quantity<Unit2, YY>& source)
        {
            BOOST_STATIC_ASSERT((boost::is_same<typename divide_typeof_helper<Unit, Unit2>::type, Unit>::value));
            val_ /= source.value();
            return *this;
        }

        this_type& operator*=(const value_type& source) { val_ *= source; return *this; }

        this_type& operator/=(const value_type& source) { val_ /= source; return *this; }

        static this_type from_value(const value_type& val)  { return this_type(val, 0); }

        explicit quantity(const value_type& val, int) : val_(val) { }

    
    type operator()(quantity<Unit,X>& source)           { return const_cast<X&>(source.value()); }

    
    type operator()(const quantity<Unit,X>& source)     { return source.value(); }

template<class X,class Y>
inline 
X
quantity_cast(Y& source)
{
    detail::quantity_cast_helper<X,Y>   qch;
    
    return qch(source);
}


template<class X,class Y>
inline 
X
quantity_cast(const Y& source)
{
    detail::quantity_cast_helper<X,const Y>   qch;
    
    return qch(source);
}

template<class Unit,class Y>
inline void swap(quantity<Unit,Y>& lhs, quantity<Unit,Y>& rhs)
{
    using std::swap;
    swap(quantity_cast<Y&>(lhs),quantity_cast<Y&>(rhs));
}

        
        absolute() : val_() { }

        absolute(const value_type& val) : val_(val) { }

        absolute(const this_type& source) : val_(source.val_) { }

   
        this_type& operator=(const this_type& source)           { val_ = source.val_; return *this; }

        
        const value_type& value() const                         { return val_; }

        
        const this_type& operator+=(const value_type& val)      { val_ += val; return *this; }

        const this_type& operator-=(const value_type& val)      { val_ -= val; return *this; }

template<class Y>
absolute<Y> operator+(const absolute<Y>& aval,const Y& rval)
{
    return absolute<Y>(aval.value()+rval);
}

template<class Y>
absolute<Y> operator+(const Y& rval,const absolute<Y>& aval)
{
    return absolute<Y>(aval.value()+rval);
}

template<class Y>
absolute<Y> operator-(const absolute<Y>& aval,const Y& rval)
{
    return absolute<Y>(aval.value()-rval);
}

template<class Y>
Y operator-(const absolute<Y>& aval1,const absolute<Y>& aval2)
{
    return Y(aval1.value()-aval2.value());
}

    static value_type value() { return(detail::static_rational_power<Exponent>(static_cast<double>(base))); }


template<long Base,class Exponent>
std::string symbol_string(const scale<Base,Exponent>&)
{
    return scale<Base,Exponent>::symbol();
}


template<long Base,class Exponent>
std::string name_string(const scale<Base,Exponent>&)
{
    return scale<Base,Exponent>::name();
}
 BOOST_PREVENT_MACRO_SUBSTITUTION (const quantity<Unit,Y>& q)
{ 
    using boost::math::isfinite;
    return isfinite BOOST_PREVENT_MACRO_SUBSTITUTION (q.value());
}
 
sin(const quantity<si::plane_angle,Y>& theta)
{
    using std::sin;
    return sin(theta.value());
}
 
tan(const quantity<si::plane_angle,Y>& theta)
{
    using std::tan;
    return tan(theta.value());
}
 
cos(const quantity<unit<plane_angle_dimension,System>,Y>& theta)
{
    return cos(quantity<si::plane_angle,Y>(theta));
}

        
        unit() { }

        unit(const this_type&) { }

       
        this_type& operator=(const this_type&) { return *this; }

operator+(const unit<Dim,System>&)
{ 
    typedef typename unary_plus_typeof_helper< unit<Dim,System> >::type type;
    
    return type();
}

operator-(const unit<Dim,System>&)
{ 
    typedef typename unary_minus_typeof_helper< unit<Dim,System> >::type    type;
    
    return type();
}


    static std::string symbol()
    {
        return(Scale::symbol() + base_unit_info<S>::symbol());
    }

    static std::string name()
    {
        return(Scale::name() + base_unit_info<S>::name());
    }


inline
std::string
demangle(const char* name)
{
    return name;
}


template<class L>
std::string simplify_typename(const L& /*source*/)
{
    return std::string(typeid(L).name());
}

        static type value()
        {
            return(next_iteration::value() * Begin::item::value());
        }

        static one value()
        {
            one result;
            return(result);
        }

        static T1 value(const T0& t0)
        {
            return(
                t0 * 
                conversion_factor(Unit1(), Unit2()) +
                affine_conversion_helper<typename reduce_unit<Unit1>::type, typename reduce_unit<Unit2>::type>::value());
        }

        static T1 value(const T0& t0)
        {
            return(
                (t0 - affine_conversion_helper<typename reduce_unit<Unit2>::type, typename reduce_unit<Unit1>::type>::value()) * 
                conversion_factor(Unit1(), Unit2()));
        }
 BOOST_PREVENT_MACRO_SUBSTITUTION(const Y& v1,const Y& v2)
{
    if((boost::math::isnan)(v1) || (boost::math::isnan)(v2)) return false;
    else return v1 > v2;
}

    static type value()
    {
        return(converter::value() * eval_factor::value());
    }

        static type value() {
            one numerator;
            return(numerator / converter::value());
        }

        static type value() {
            return(start::value() * conversion::value() / end::value());
        }

        static type value() {
            return(static_rational_power<exponent>(conversion::value()) * next_iteration::value());
        }

        static one value() {
            one result;
            return(result);
        }

        static type value() {
            return(start::value() * conversion::value() / impl::value());
        }

        static type value() { return(static_rational_power<typename unit_pair::value_type>(converter::value()) * next_iteration::value()); }

        static type value() { one result; return(result); }
 one() {}

inline one make_one() {
    one result;
    return(result);
}


template<class T>
inline T operator*(const one&, const T& t)
{
    return(t);
}


template<class T>
inline T operator*(const T& t, const one&)
{
    return(t);
}


inline one operator*(const one&, const one&)
{
    one result;
    return(result);
}


template<class T>
inline T operator/(const T& t, const one&)
{
    return(t);
}


template<class T>
inline T operator/(const one&, const T& t)
{
    return(1/t);
}


inline one operator/(const one&, const one&)
{
    one result;
    return(result);
}


template<class T>
inline bool operator>(const boost::units::one&, const T& t) {
    return(1 > t);
}


template<class T>
T one_to_double(const T& t) { return t; }


inline double one_to_double(const one&) { return 1.0; }

    static type call(const Y& y)
    {
        using std::pow;
        return(pow(y, static_cast<double>(R::Numerator) / static_cast<double>(R::Denominator)));
    }

        static type call(const Y& y, const R& r)
        {
            const square_type square = y * y;
            return(next::call(square, r));
        }

        static type call(const Y& y, const R& r)
        {
            const Y square = y * y;
            return(next::call(square, y * r));
        }

        static type call(const Y& y, const R& r)
        {
            return(y * r);
        }

        static R call(const Y&, const R& r)
        {
            return(r);
        }

        static type call(const Y& y)
        {
            one result;
            return(impl::call(y, result));
        }

        static type call(const Y& y)
        {
            one result;
            return(result/impl::call(y, result));
        }

    static type call(const Y& y)
    {
        return(impl::call(y));
    }


template<class R, class Y>
typename detail::static_rational_power_impl<R, Y>::type static_rational_power(const Y& y)
{
    return(detail::static_rational_power_impl<R, Y>::call(y));
}
 no() {}

template<class T>
detail::no 
boost_units_is_registered(const T&) 
{ detail::no result; return(result); }

template<class T>
detail::no 
boost_units_unit_is_registered(const T&) 
{ detail::no result; return(result); }

    static const char* name()   { return("gallon (U.S.)"); }

    static const char* symbol() { return("gal"); }

    static const char* name()   { return("fluid ounce (U.S.)"); }

    static const char* symbol() { return("fl oz"); }

    static const char* name()   { return("quart (U.S.)"); }

    static const char* symbol() { return("qt"); }

    static const char* name()   { return("hundredweight (U.S.)"); }

    static const char* symbol() { return("cwt"); }

    static const char* name()   { return("gill (U.S.)"); }

    static const char* symbol() { return("gi"); }

    static const char* name()   { return("fluid dram (U.S.)"); }

    static const char* symbol() { return("fl dr"); }

    static const char* name()   { return("mile"); }

    static const char* symbol() { return("mi"); }

    static const char* name()   { return("short ton"); }

    static const char* symbol() { return("t"); }

    static const char* name()   { return("minim (U.S.)"); }

    static const char* symbol() { return("minim"); }

    static const char* name()   { return("inch"); }

    static const char* symbol() { return("in"); }

    static const char* name()   { return("cup"); }

    static const char* symbol() { return("c"); }

    static const char* name()   { return("grain"); }

    static const char* symbol() { return("gr"); }

    static const char* name()   { return("mil"); }

    static const char* symbol() { return("mil"); }

    static const char* name()   { return("teaspoon"); }

    static const char* symbol() { return("tsp"); }

    static const char* name()   { return("dram (U.S.)"); }

    static const char* symbol() { return("dr"); }

    static const char* name()   { return("tablespoon"); }

    static const char* symbol() { return("tbsp"); }

    static const char* name()   { return("foot"); }

    static const char* symbol() { return("ft"); }

    static const char* name()   { return("ounce"); }

    static const char* symbol() { return("oz"); }

    static const char* name()   { return("stone"); }

    static const char* symbol() { return("st"); }

    static const char* name()   { return("gallon (imp.)"); }

    static const char* symbol() { return("gal"); }

    static const char* name()   { return("fluid ounce (imp.)"); }

    static const char* symbol() { return("fl oz"); }

    static const char* name()   { return("thou"); }

    static const char* symbol() { return("thou"); }

    static const char* name()   { return("quart (imp.)"); }

    static const char* symbol() { return("qt"); }

    static const char* name()   { return("hundredweight"); }

    static const char* symbol() { return("cwt"); }

    static const char* name()   { return("drachm"); }

    static const char* symbol() { return("drachm"); }

    static const char* name()   { return("league"); }

    static const char* symbol() { return("league"); }

    static const char* name()   { return("gill (imp.)"); }

    static const char* symbol() { return("gill"); }

    static const char* name()   { return("mile"); }

    static const char* symbol() { return("mi"); }

    static const char* name()   { return("quarter"); }

    static const char* symbol() { return("quarter"); }

    static const char* name()   { return("long ton"); }

    static const char* symbol() { return("t"); }

    static const char* name()   { return("inch"); }

    static const char* symbol() { return("in"); }

    static const char* name()   { return("grain"); }

    static const char* symbol() { return("grain"); }

    static const char* name()   { return("foot"); }

    static const char* symbol() { return("ft"); }

    static const char* name()   { return("furlong"); }

    static const char* symbol() { return("furlong"); }

    static const char* name()   { return("ounce"); }

    static const char* symbol() { return("oz"); }

    static std::string name()    { return("gram"); }

    static std::string symbol() { return("g"); }

    static std::string name()   { return("steradian"); }

    static std::string symbol() { return("sr"); }

    static std::string name()   { return("radian"); }

    static std::string symbol() { return("rad"); }

    static const char* name()   { return("arcminute"); }

    static const char* symbol() { return("'"); }

    static const char* name()   { return("revolution"); }

    static const char* symbol() { return("rev"); }

    static const char* name()   { return("arcsecond"); }

    static const char* symbol() { return("\""); }

    static const char* name()   { return("fermi"); }

    static const char* symbol() { return("fm"); }

    static const char* name()   { return("micron"); }

    static const char* symbol() { return("u"); }

    static const char* name()   { return("day"); }

    static const char* symbol() { return("d"); }

    static const char* name()   { return("angstrom"); }

    static const char* symbol() { return("A"); }

    static const char* name()   { return("metric ton"); }

    static const char* symbol() { return("t"); }

    static const char* name()   { return("minute"); }

    static const char* symbol() { return("min"); }

    static const char* name()   { return("hour"); }

    static const char* symbol() { return("h"); }

    static const char* name()   { return("Julian year"); }

    static const char* symbol() { return("yr"); }

    static const char* name()   { return("nautical mile"); }

    static const char* symbol() { return("nmi"); }

    static const char* name()   { return("light day"); }

    static const char* symbol() { return("ldy"); }

    static const char* name()   { return("light hour"); }

    static const char* symbol() { return("lhr"); }

    static const char* name()   { return("light year"); }

    static const char* symbol() { return("ly"); }

    static const char* name()   { return("light minute"); }

    static const char* symbol() { return("lmn"); }

    static std::string name()   { return("fahrenheit"); }

    static std::string symbol() { return("F"); }

    static std::string name()   { return("celsius"); }

    static std::string symbol() { return("C"); }

    static std::string name()   { return("kelvin"); }

    static std::string symbol() { return("K"); }

    static std::string name()   { return("mole"); }

    static std::string symbol() { return("mol"); }

    static std::string name()   { return("candela"); }

    static std::string symbol() { return("cd"); }

    static std::string name()   { return("second"); }

    static std::string symbol() { return("s"); }

    static std::string name()   { return("meter"); }

    static std::string symbol() { return("m"); }

    static std::string name()   { return("ampere"); }

    static std::string symbol() { return("A"); }
 
    static std::string name()       { return "[Length]"; }

    static std::string symbol()     { return "[L]"; }
 
    operator value_type() const    { return Base().value(); }
 
    value_type value() const       { return Base().value(); }
 
    value_type uncertainty() const { return Base().uncertainty(); }
 
    value_type lower_bound() const { return Base().lower_bound(); }
 
    value_type upper_bound() const { return Base().upper_bound(); }
 
    operator value_type() const    { return Base().value(); }
 
    value_type value() const       { return Base().value(); }
 
    value_type uncertainty() const { return Base().uncertainty(); }
 
    value_type lower_bound() const { return Base().lower_bound(); }
 
    value_type upper_bound() const { return Base().upper_bound(); }
 

inline std::string name_string(const reduce_unit<cgs::acceleration>::type&) { return "galileo"; }

inline std::string symbol_string(const reduce_unit<cgs::acceleration>::type&) { return "Gal"; }

inline std::string name_string(const reduce_unit<si::absorbed_dose>::type&) { return "gray"; }

inline std::string symbol_string(const reduce_unit<si::absorbed_dose>::type&) { return "Gy"; }
