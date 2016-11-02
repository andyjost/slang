

template<class T> inline T pi_lower() { return 3; }

template<class T> inline T pi_upper() { return 4; }

template<class T> inline T pi_half_lower() { return 1; }

template<class T> inline T pi_half_upper() { return 2; }

template<class T> inline T pi_twice_lower() { return 6; }

template<class T> inline T pi_twice_upper() { return 7; }


template<> inline float pi_lower<float>() { return pi_f_l; }

template<> inline float pi_upper<float>() { return pi_f_u; }

template<> inline float pi_half_lower<float>() { return pi_f_l / 2; }

template<> inline float pi_half_upper<float>() { return pi_f_u / 2; }

template<> inline float pi_twice_lower<float>() { return pi_f_l * 2; }

template<> inline float pi_twice_upper<float>() { return pi_f_u * 2; }


template<> inline double pi_lower<double>() { return pi_d_l; }

template<> inline double pi_upper<double>() { return pi_d_u; }

template<> inline double pi_half_lower<double>() { return pi_d_l / 2; }

template<> inline double pi_half_upper<double>() { return pi_d_u / 2; }

template<> inline double pi_twice_lower<double>() { return pi_d_l * 2; }

template<> inline double pi_twice_upper<double>() { return pi_d_u * 2; }


template<> inline long double pi_lower<long double>() { return pi_d_l; }

template<> inline long double pi_upper<long double>() { return pi_d_u; }

template<> inline long double pi_half_lower<long double>() { return pi_d_l / 2; }

template<> inline long double pi_half_upper<long double>() { return pi_d_u / 2; }

template<> inline long double pi_twice_lower<long double>() { return pi_d_l * 2; }

template<> inline long double pi_twice_upper<long double>() { return pi_d_u * 2; }


template<class I> inline
I pi()
{
  typedef typename I::base_type T;
  return I(constants::pi_lower<T>(),
           constants::pi_upper<T>(), true);
}


template<class I> inline
I pi_half()
{
  typedef typename I::base_type T;
  return I(constants::pi_half_lower<T>(),
           constants::pi_half_upper<T>(), true);
}


template<class I> inline
I pi_twice()
{
  typedef typename I::base_type T;
  return I(constants::pi_twice_lower<T>(),
           constants::pi_twice_upper<T>(), true);
}

  void operator()()
  {
    throw std::runtime_error("boost::interval: empty interval created");
  }

  void operator()()
  {
    throw std::invalid_argument("boost::interval: invalid number");
  }

  static T pos_inf()
  {
    assert(std::numeric_limits<T>::has_infinity);
    return std::numeric_limits<T>::infinity();
  }

  static T neg_inf()
  {
    assert(std::numeric_limits<T>::has_infinity);
    return -std::numeric_limits<T>::infinity();
  }

  static T nan()
  {
    assert(std::numeric_limits<T>::has_quiet_NaN);
    return std::numeric_limits<T>::quiet_NaN();
  }

  static bool is_nan(const T& x)
  {
    return std::numeric_limits<T>::has_quiet_NaN && (x != x);
  }

  static T empty_lower()
  {
    return (std::numeric_limits<T>::has_quiet_NaN ?
            std::numeric_limits<T>::quiet_NaN() : static_cast<T>(1));
  }

  static T empty_upper()
  {
    return (std::numeric_limits<T>::has_quiet_NaN ?
            std::numeric_limits<T>::quiet_NaN() : static_cast<T>(0));
  }

  static bool is_empty(const T& l, const T& u)
  {
    return !(l <= u); // safety for partial orders
  }

  static T nan()
  {
    assert(false);
    return Checking::nan();
  }

  static T empty_lower()
  {
    Exception()();
    return Checking::empty_lower();
  }

  static T empty_upper()
  {
    Exception()();
    return Checking::empty_upper();
  }

  static bool is_empty(const T&, const T&)
  {
    return false;
  }

  static bool is_nan(const T&)
  {
    return false;
  }

  static bool is_nan(const T& x)
  {
    if (Checking::is_nan(x)) Exception()();
    return false;
  }


template<class T, class Policies> inline
const T& lower(const interval<T, Policies>& x)
{
  return x.lower();
}


template<class T, class Policies> inline
const T& upper(const interval<T, Policies>& x)
{
  return x.upper();
}


template<class T, class Policies> inline
T checked_lower(const interval<T, Policies>& x)
{
  if (empty(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  return x.lower();
}


template<class T, class Policies> inline
T checked_upper(const interval<T, Policies>& x)
{
  if (empty(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  return x.upper();
}


template<class T, class Policies> inline
T width(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) return static_cast<T>(0);
  typename Policies::rounding rnd;
  return rnd.sub_up(x.upper(), x.lower());
}


template<class T, class Policies> inline
T median(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  typename Policies::rounding rnd;
  return rnd.median(x.lower(), x.upper());
}

  void init() { }

  template<class U> T conv_down(U const &v) { return v; }

  template<class U> T conv_up  (U const &v) { return v; }

  T add_down (const T& x, const T& y) { return x + y; }

  T add_up   (const T& x, const T& y) { return x + y; }

  T sub_down (const T& x, const T& y) { return x - y; }

  T sub_up   (const T& x, const T& y) { return x - y; }

  T mul_down (const T& x, const T& y) { return x * y; }

  T mul_up   (const T& x, const T& y) { return x * y; }

  T div_down (const T& x, const T& y) { return x / y; }

  T div_up   (const T& x, const T& y) { return x / y; }

  T median   (const T& x, const T& y) { return (x + y) / 2; }

  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }

  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }

  T int_down (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(floor); return floor(x); }

  T int_up   (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(ceil); return ceil(x); }

  void init() { }

  template<class U> T conv_down(U const &v) { BOOST_DN(v); }

  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }

  T add_down(const T& x, const T& y) { BOOST_DN(x + y); }

  T sub_down(const T& x, const T& y) { BOOST_DN(x - y); }

  T mul_down(const T& x, const T& y) { BOOST_DN(x * y); }

  T div_down(const T& x, const T& y) { BOOST_DN(x / y); }

  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }

  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }

  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }

  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }

  T median(const T& x, const T& y) { BOOST_NR((x + y) / 2); }

  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }

  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }

  T int_down(const T& x) { this->downward(); return to_int(x); }

  T int_up  (const T& x) { this->upward();   return to_int(x); }

  void init() { this->upward(); }

  template<class U> T conv_down(U const &v) { BOOST_UP_NEG(-v); }

  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }

  T add_down(const T& x, const T& y) { BOOST_UP_NEG((-x) - y); }

  T sub_down(const T& x, const T& y) { BOOST_UP_NEG(y - x); }

  T mul_down(const T& x, const T& y) { BOOST_UP_NEG(x * (-y)); }

  T div_down(const T& x, const T& y) { BOOST_UP_NEG(x / (-y)); }

  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }

  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }

  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }

  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }

  T median  (const T& x, const T& y) { BOOST_NR((x + y) / 2); }

  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }

  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }

  T int_down(const T& x) { return -to_int(-x); }

  T int_up  (const T& x) { return to_int(x); }


template<class I> inline
I add(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.add_down(x, y), rnd.add_up(x, y), true);
}


template<class I> inline
I sub(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.sub_down(x, y), rnd.sub_up(x, y), true);
}


template<class I> inline
I mul(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.mul_down(x, y), rnd.mul_up(x, y), true);
}


template<class I> inline
I div(const typename I::base_type& x, const typename I::base_type& y)
{
  typedef typename I::traits_type Policies;
  if (detail::test_input<typename I::base_type, Policies>(x, y) || user::is_zero(y))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.div_down(x, y), rnd.div_up(x, y), true);
}

  comparison_error()
    : std::runtime_error("boost::interval: uncertain comparison")
  { }

  interval(const T& l, const T& u, bool): low(l), up(u) {}

    template<class Policies2>
    interval_holder(const interval<T, Policies2>& r)
      : low(r.lower()), up(r.upper())
    {
      typedef typename Policies2::checking checking2;
      if (checking2::is_empty(low, up))
        throw interval_lib::comparison_error();
    }

    number_holder(const T& r) : val(r)
    {
      typedef typename Policies::checking checking;
      if (checking::is_nan(r))
        throw interval_lib::comparison_error();
    }


template<class T, class Policies> inline
interval<T, Policies>::interval():
  low(static_cast<T>(0)), up(static_cast<T>(0))
{}


template<class T, class Policies> inline
interval<T, Policies>::interval(T const &v): low(v), up(v)
{
  if (checking::is_nan(v)) set_empty();
}
 template<class T1> inline
interval<T, Policies>::interval(T1 const &v)
{
  if (checking::is_nan(v)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(v);
    up  = rnd.conv_up  (v);
  }
}
 template<class T1, class T2> inline
interval<T, Policies>::interval(T1 const &l, T2 const &u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(l);
    up  = rnd.conv_up  (u);
  }
}


template<class T, class Policies> inline
interval<T, Policies>::interval(T const &l, T const &u): low(l), up(u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
}



template<class T, class Policies> inline
interval<T, Policies>::interval(interval<T, Policies> const &r): low(r.lower()), up(r.upper())
{}
 template<class Policies1> inline
interval<T, Policies>::interval(interval<T, Policies1> const &r): low(r.lower()), up(r.upper())
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
}
 template<class T1, class Policies1> inline
interval<T, Policies>::interval(interval<T1, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(r.lower());
    up  = rnd.conv_up  (r.upper());
  }
}


template<class T, class Policies> inline
interval<T, Policies> &interval<T, Policies>::operator=(T const &v)
{
  if (checking::is_nan(v)) set_empty();
  else low = up = v;
  return *this;
}
 template<class T1> inline
interval<T, Policies> &interval<T, Policies>::operator=(T1 const &v)
{
  if (checking::is_nan(v)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(v);
    up  = rnd.conv_up  (v);
  }
  return *this;
}


template<class T, class Policies> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T, Policies> const &r)
{
  low = r.lower();
  up  = r.upper();
  return *this;
}
 template<class Policies1> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    low = r.lower();
    up  = r.upper();
  }
  return *this;
}
 template<class T1, class Policies1> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T1, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(r.lower());
    up  = rnd.conv_up  (r.upper());
  }
  return *this;
}


template<class T, class Policies> inline
void interval<T, Policies>::assign(const T& l, const T& u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
  else set(l, u);
}


template<class T, class Policies> inline
void interval<T, Policies>::set(const T& l, const T& u)
{
  low = l;
  up  = u;
}


template<class T, class Policies> inline
void interval<T, Policies>::set_empty()
{
  low = checking::empty_lower();
  up  = checking::empty_upper();
}


template<class T, class Policies> inline
void interval<T, Policies>::set_whole()
{
  low = checking::neg_inf();
  up  = checking::pos_inf();
}


template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::hull(const T& x, const T& y)
{
  bool bad_x = checking::is_nan(x);
  bool bad_y = checking::is_nan(y);
  if (bad_x)
    if (bad_y) return interval::empty();
    else       return interval(y, y, true);
  else
    if (bad_y) return interval(x, x, true);
  if (x <= y) return interval(x, y, true);
  else        return interval(y, x, true);
}


template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::empty()
{
  return interval<T, Policies>(checking::empty_lower(),
                               checking::empty_upper(), true);
}


template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::whole()
{
  return interval<T, Policies>(checking::neg_inf(), checking::pos_inf(), true);
}


template<class T, class Policies> inline
const T& interval<T, Policies>::lower() const
{
  return low;
}


template<class T, class Policies> inline
const T& interval<T, Policies>::upper() const
{
  return up;
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.low) return true;
    else if (low >= r.up) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low > r.up) return true;
    else if (up <= r.low) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up <= r.low) return true;
    else if (low > r.up) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low >= r.up) return true;
    else if (up < r.low) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up == r.low && low == r.up) return true;
    else if (up < r.low || low > r.up) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.low || low > r.up) return true;
    else if (up == r.low && low == r.up) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.val) return true;
    else if (low >= r.val) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low > r.val) return true;
    else if (up <= r.val) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up <= r.val) return true;
    else if (low > r.val) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low >= r.val) return true;
    else if (up < r.val) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up == r.val && low == r.val) return true;
    else if (up < r.val || low > r.val) return false;
  }
  throw interval_lib::comparison_error();
}


template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.val || low > r.val) return true;
    else if (up == r.val && low == r.val) return false;
  }
  throw interval_lib::comparison_error();
}

  static void get_rounding_mode(rounding_mode&) {}

  static void set_rounding_mode(rounding_mode)  {}

  static void upward()     {}

  static void downward()   {}

  static void to_nearest() {}

  static const T& to_int(const T& x)         { return x; }

  static const T& force_rounding(const T& x) { return x; }

  save_state() {
    this->get_rounding_mode(mode);
    this->init();
  }

  ~save_state() { this->set_rounding_mode(mode); }
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
 \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
 \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
 \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(acosh)


    static void set_rounding_mode(const rounding_mode mode)
    { __asm__ __volatile__ ("mt_fpcr %0" : : "f"(mode)); }


    static void get_rounding_mode(rounding_mode& mode)
    { __asm__ __volatile__ ("mf_fpcr %0" : "=f"(mode)); }


    static void downward()    { set_rounding_mode(mode_downward.dmode);    }

    static void upward()      { set_rounding_mode(mode_upward.dmode);      }

    static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }

    static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }

  static float force_rounding(const float r)
  { volatile float _r = r; return _r; }

  static float to_int(const float& x) { return rintf(x); }

  static void to_nearest()  { set_rounding_mode(rnd_mode.to_nearest);  }

  static void downward()    { set_rounding_mode(rnd_mode.downward);    }

  static void upward()      { set_rounding_mode(rnd_mode.upward);      }

  static void toward_zero() { set_rounding_mode(rnd_mode.toward_zero); }

  static float force_rounding(const float& r) 
  { volatile float r_ = r; return r_; }

  static long double force_rounding(long double const &r)
  { volatile long double r_ = r; return r_; }

  static long double const &force_rounding(long double const &r)
  { return r; }

  borland_workaround() { _fm_init(); }


__inline double rint(double)
{ __emit__(0xD9); __emit__(0xFC); /* asm FRNDINT */ }

  static void get_rounding_mode(rounding_mode& mode)
  { mode = _control87(0, 0); }

  static void set_rounding_mode(const rounding_mode mode)
  { _control87(mode, 0xffff); }
 
  static double to_int(const double& x) { return rint(x); }


template<class T> inline
bool is_zero(T const &v) { return v == static_cast<T>(0); }


template<class T> inline
bool is_neg (T const &v) { return v <  static_cast<T>(0); }


template<class T> inline
bool is_pos (T const &v) { return v >  static_cast<T>(0); }


template<class T, class Policies> inline
bool test_input(const interval<T, Policies>& x) {
  typedef typename Policies::checking checking;
  return checking::is_empty(x.lower(), x.upper());
}


template<class T, class Policies> inline
bool test_input(const T& x) {
  typedef typename Policies::checking checking;
  return checking::is_nan(x);
}


template<class T, class Policies> inline
bool test_input(const T& x, const T& y) {
  typedef typename Policies::checking checking;
  return checking::is_nan(x) || checking::is_nan(y);
}


  static void set_rounding_mode(const rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("ld %0, %%fsr" : : "m"(mode));
#   elif defined (__SUNPRO_CC)
    fpsetround(fp_rnd(mode));
#   elif defined(__KCC)
    asm("sethi %hi(mode), %o1");
    asm("ld [%o1+%lo(mode)], %fsr");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }


  static void get_rounding_mode(rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("st %%fsr, %0" : "=m"(mode));
#   elif defined (__SUNPRO_CC)
    mode = fpgetround();
#   elif defined(__KCC)
#     error KCC on Sun SPARC get_round_mode: please fix me
    asm("st %fsr, [mode]");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }

  static void downward()    { set_rounding_mode(0xc0000000); }

  static void upward()      { set_rounding_mode(0x80000000); }

  static void to_nearest()  { set_rounding_mode(0x00000000); }

  static void toward_zero() { set_rounding_mode(0x40000000); }

  static const float& force_rounding(const float& x) { return x; }

  static float to_int(const float& x) { return rintf(x); }


  static void set_rounding_mode(rounding_mode mode)  { fesetround(mode); }

  static void get_rounding_mode(rounding_mode &mode) { mode = fegetround(); }

  static void downward()    { set_rounding_mode(FE_DOWNWARD);   }

  static void upward()      { set_rounding_mode(FE_UPWARD);     }

  static void to_nearest()  { set_rounding_mode(FE_TONEAREST);  }

  static void toward_zero() { set_rounding_mode(FE_TOWARDZERO); }


  template<class T>
  static T to_int(const T& r) { return rint(r); }


  static void set_rounding_mode(const rounding_mode& mode)
  { __asm__ __volatile__ ("fldcw %0" : : "m"(mode)); }


  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("fnstcw %0" : "=m"(mode)); }


  template<class T>
  static T to_int(T r)
  {
    T r_;
    __asm__ ("frndint" : "=&t"(r_) : "0"(r));
    return r_;
  }

  static unsigned int hard2msvc(unsigned short m) {
    unsigned int n = 0;
    if (m & 0x01) n |= _EM_INVALID;
    if (m & 0x02) n |= _EM_DENORMAL;
    if (m & 0x04) n |= _EM_ZERODIVIDE;
    if (m & 0x08) n |= _EM_OVERFLOW;
    if (m & 0x10) n |= _EM_UNDERFLOW;
    if (m & 0x20) n |= _EM_INEXACT;
    switch (m & 0x300) {
    case 0x000: n |= _PC_24; break;
    case 0x200: n |= _PC_53; break;
    case 0x300: n |= _PC_64; break;
    }
    switch (m & 0xC00) {
    case 0x000: n |= _RC_NEAR; break;
    case 0x400: n |= _RC_DOWN; break;
    case 0x800: n |= _RC_UP;   break;
    case 0xC00: n |= _RC_CHOP; break;
    }
    if (m & 0x1000) n |= _IC_AFFINE; // only useful on 287
    return n;
  }


  static unsigned short msvc2hard(unsigned int n) {
    unsigned short m = 0;
    if (n & _EM_INVALID)    m |= 0x01;
    if (n & _EM_DENORMAL)   m |= 0x02;
    if (n & _EM_ZERODIVIDE) m |= 0x04;
    if (n & _EM_OVERFLOW)   m |= 0x08;
    if (n & _EM_UNDERFLOW)  m |= 0x10;
    if (n & _EM_INEXACT)    m |= 0x20;
    switch (n & _MCW_RC) {
    case _RC_NEAR: m |= 0x000; break;
    case _RC_DOWN: m |= 0x400; break;
    case _RC_UP:   m |= 0x800; break;
    case _RC_CHOP: m |= 0xC00; break;
    }
    switch (n & _MCW_PC) {
    case _PC_24: m |= 0x000; break;
    case _PC_53: m |= 0x200; break;
    case _PC_64: m |= 0x300; break;
    }
    if ((n & _MCW_IC) == _IC_AFFINE) m |= 0x1000;
    return m;
  }

  static void get_rounding_mode(rounding_mode& mode)
  { mode = msvc2hard(_control87(0, 0)); }

  static void set_rounding_mode(const rounding_mode mode)
  { _control87(hard2msvc(mode), _MCW_EM | _MCW_RC | _MCW_PC | _MCW_IC); }

  static double to_int(const double& x) { return rint(x); }

  static float force_rounding(float const &r)
  { volatile float r_ = r; return r_; }


  static void set_rounding_mode(const rounding_mode mode)
  { __asm__ __volatile__ ("mtfsf 255,%0" : : "f"(mode)); }


  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("mffs %0" : "=f"(mode)); }


  static void downward()    { set_rounding_mode(mode_downward.dmode);    }

  static void upward()      { set_rounding_mode(mode_upward.dmode);      }

  static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }

  static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }

  static float force_rounding(const float r)
  {
    float tmp;
    __asm__ __volatile__ ("frsp %0, %1" : "=f" (tmp) : "f" (r));
    return tmp;
  }

  static float to_int(const float& x) { return rintf(x); }

  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_f.to_nearest);  }

  static void downward()    { set_rounding_mode(detail::rnd_mode_f.downward);    }

  static void upward()      { set_rounding_mode(detail::rnd_mode_f.upward);      }

  static void toward_zero() { set_rounding_mode(detail::rnd_mode_f.toward_zero); }

  static const float& force_rounding(const float& r) { return r; }

  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_d.to_nearest);  }

  static void downward()    { set_rounding_mode(detail::rnd_mode_d.downward);    }

  static void upward()      { set_rounding_mode(detail::rnd_mode_d.upward);      }

  static void toward_zero() { set_rounding_mode(detail::rnd_mode_d.toward_zero); }

  static const double& force_rounding(const double& r) { return r; }

  static void to_nearest()  { set_rounding_mode(detail::rnd_mode_l.to_nearest);  }

  static void downward()    { set_rounding_mode(detail::rnd_mode_l.downward);    }

  static void upward()      { set_rounding_mode(detail::rnd_mode_l.upward);      }

  static void toward_zero() { set_rounding_mode(detail::rnd_mode_l.toward_zero); }

  static const long double& force_rounding(const long double& r) { return r; }


template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper() && x.upper() >= y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.upper() || x.upper() != y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() == y.lower() && x.lower() == y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower() || x.lower() > y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(x, y);
}


template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(x, y);
}


template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(y, x);
}


template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(y, x);
}


template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return equal(y, x);
}


template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return !equal(y, x);
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower()) return true;
  if (x.lower() >= y.upper()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y.lower()) return true;
  if (x.lower() > y.upper()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y.upper()) return true;
  if (x.upper() <= y.lower()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y.upper()) return true;
  if (x.upper() < y.lower()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y.lower() && x.lower() == y.upper()) return true;
  if (x.upper() < y.lower() || x.lower() > y.upper()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
logic::tribool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower() || x.lower() > y.upper()) return true;
  if (x.upper() == y.lower() && x.lower() == y.upper()) return false;
  return logic::indeterminate;
}


template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() < y.upper());
}


template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() <= y.upper());
}


template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() > y.upper());
}


template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() >= y.upper());
}


template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y.lower() && x.upper() == y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.lower() || x.upper() != y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool cerlt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool cerle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() <= y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool cergt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() > y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool cerge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() >= y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool cereq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() == y.upper() && y.lower() == x.upper();
}


template<class T, class Policies1, class Policies2> inline
bool cerne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower() || y.upper() < x.lower();
}


template<class T, class Policies1, class Policies2> inline
bool poslt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() < y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool posle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() <= y.upper();
}


template<class T, class Policies1, class Policies2> inline
bool posgt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() > y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool posge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower();
}


template<class T, class Policies1, class Policies2> inline
bool poseq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower() && y.upper() >= x.lower();
}


template<class T, class Policies1, class Policies2> inline
bool posne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() != y.lower() || y.upper() != x.lower();
}

	    matrix (size_type size1, size_type size2, const value_type &init):
	        matrix_container<self_type> (),
	        size1_ (size1), size2_ (size2), data_ (layout_type::storage_size (size1, size2), init) {
	    }

        BOOST_UBLAS_INLINE
        ~bounded_matrix () {}

        ublas_expression () {}

        ~ublas_expression () {}


        BOOST_UBLAS_INLINE
        operator value_type () const {
            return t_;
        }
  move_to(T i) {
    return vector_move_to_manip<T>(i);
}
  move(T i) {
    return vector_move_manip<T>(i);
}

inline begin1_manip  begin1() {
    return begin1_manip();
}

inline begin2_manip  begin2() {
    return begin2_manip();
}

inline next_row_manip  next_row() {
    return next_row_manip();
}

inline next_column_manip next_column() {
    return next_column_manip();
}


    inline by_row_policy<DEFAULT_WRAP_POLICY> by_row() {
    return by_row_policy<DEFAULT_WRAP_POLICY>();
    }


    inline by_row_policy<wrap> by_row_wrap() {
        return by_row_policy<wrap>();
    }


    inline by_row_policy<no_wrap> by_row_no_wrap() {
        return by_row_policy<no_wrap>();
    }


    inline by_column_policy<DEFAULT_WRAP_POLICY> by_column() {
        return by_column_policy<DEFAULT_WRAP_POLICY>();
    }


    inline by_column_policy<wrap> by_column_wrap() {
        return by_column_policy<wrap>();
    }


    inline by_column_policy<no_wrap> by_column_no_wrap() {
        return by_column_policy<no_wrap>();
    }

        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            const_subiterator_type it (data ().lower_bound (layout_type::address (i, size1_, j, size2_)));
            const_subiterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
            size_type index2 = size_type (-1);
            while (rank == 1 && it != it_end) {
                index1 = layout_type::index_i ((*it).first, size1_, size2_);
                index2 = layout_type::index_j ((*it).first, size1_, size2_);
                if (direction > 0) {
                    if ((index1 >= i && index2 == j) || (i >= size1_))
                        break;
                    ++ i;
                } else /* if (direction < 0) */ {
                    if ((index1 <= i && index2 == j) || (i == 0))
                        break;
                    -- i;
                }
                it = data ().lower_bound (layout_type::address (i, size1_, j, size2_));
            }
            if (rank == 1 && index2 != j) {
                if (direction > 0)
                    i = size1_;
                else /* if (direction < 0) */
                    i = 0;
                rank = 0;
            }
            return const_iterator1 (*this, rank, i, j, it);
        }

        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            subiterator_type it (data ().lower_bound (layout_type::address (i, size1_, j, size2_)));
            subiterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
            size_type index2 = size_type (-1);
            while (rank == 1 && it != it_end) {
                index1 = layout_type::index_i ((*it).first, size1_, size2_);
                index2 = layout_type::index_j ((*it).first, size1_, size2_);
                if (direction > 0) {
                    if ((index1 >= i && index2 == j) || (i >= size1_))
                        break;
                    ++ i;
                } else /* if (direction < 0) */ {
                    if ((index1 <= i && index2 == j) || (i == 0))
                        break;
                    -- i;
                }
                it = data ().lower_bound (layout_type::address (i, size1_, j, size2_));
            }
            if (rank == 1 && index2 != j) {
                if (direction > 0)
                    i = size1_;
                else /* if (direction < 0) */
                    i = 0;
                rank = 0;
            }
            return iterator1 (*this, rank, i, j, it);
        }

        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            const_subiterator_type it (data ().lower_bound (layout_type::address (i, size1_, j, size2_)));
            const_subiterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
            size_type index2 = size_type (-1);
            while (rank == 1 && it != it_end) {
                index1 = layout_type::index_i ((*it).first, size1_, size2_);
                index2 = layout_type::index_j ((*it).first, size1_, size2_);
                if (direction > 0) {
                    if ((index2 >= j && index1 == i) || (j >= size2_))
                        break;
                    ++ j;
                } else /* if (direction < 0) */ {
                    if ((index2 <= j && index1 == i) || (j == 0))
                        break;
                    -- j;
                }
                it = data ().lower_bound (layout_type::address (i, size1_, j, size2_));
            }
            if (rank == 1 && index1 != i) {
                if (direction > 0)
                    j = size2_;
                else /* if (direction < 0) */
                    j = 0;
                rank = 0;
            }
            return const_iterator2 (*this, rank, i, j, it);
        }

        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            subiterator_type it (data ().lower_bound (layout_type::address (i, size1_, j, size2_)));
            subiterator_type it_end (data ().end ());
            size_type index1 = size_type (-1);
            size_type index2 = size_type (-1);
            while (rank == 1 && it != it_end) {
                index1 = layout_type::index_i ((*it).first, size1_, size2_);
                index2 = layout_type::index_j ((*it).first, size1_, size2_);
                if (direction > 0) {
                    if ((index2 >= j && index1 == i) || (j >= size2_))
                        break;
                    ++ j;
                } else /* if (direction < 0) */ {
                    if ((index2 <= j && index1 == i) || (j == 0))
                        break;
                    -- j;
                }
                it = data ().lower_bound (layout_type::address (i, size1_, j, size2_));
            }
            if (rank == 1 && index1 != i) {
                if (direction > 0)
                    j = size2_;
                else /* if (direction < 0) */
                    j = 0;
                rank = 0;
            }
            return iterator2 (*this, rank, i, j, it);
        }

        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_const_subiterator_type itv (data ().lower_bound (layout_type::index_M (i, j)));
                vector_const_subiterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());

                const_subiterator_type it ((*itv).second.lower_bound (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).second.end ());
                if (rank == 0) {
                    // advance to the first available major index
                    size_type M = itv->first;
                    size_type m;
                    if (it != it_end) { 
                        m = it->first; 
                    } else {
                        m = layout_type::size_m(size1_, size2_);
                    }
                    size_type first_i = layout_type::index_M(M,m);
                    return const_iterator1 (*this, rank, first_i, j, itv, it);
                }
                if (it != it_end && (*it).first == layout_type::index_m (i, j))
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = (*it).first;
                    } else {
                        if (i >= size1_)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).second.begin ())
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- it;
                        i = (*it).first;
                    } else {
                        if (i == 0)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_subiterator_type itv (data ().lower_bound (layout_type::index_M (i, j)));
                vector_subiterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());

                subiterator_type it ((*itv).second.lower_bound (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).second.end ());
                if (rank == 0) {
                    // advance to the first available major index
                    size_type M = itv->first;
                    size_type m;
                    if (it != it_end) { 
                        m = it->first; 
                    } else {
                        m = layout_type::size_m(size1_, size2_);
                    }
                    size_type first_i = layout_type::index_M(M,m);
                    return iterator1 (*this, rank, first_i, j, itv, it);
                }
                if (it != it_end && (*it).first == layout_type::index_m (i, j))
                    return iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = (*it).first;
                    } else {
                        if (i >= size1_)
                            return iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).second.begin ())
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- it;
                        i = (*it).first;
                    } else {
                        if (i == 0)
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_const_subiterator_type itv (data ().lower_bound (layout_type::index_M (i, j)));
                vector_const_subiterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());

                const_subiterator_type it ((*itv).second.lower_bound (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).second.end ());
                if (rank == 0) {
                    // advance to the first available major index
                    size_type M = itv->first;
                    size_type m;
                    if (it != it_end) { 
                        m = it->first; 
                    } else {
                        m = layout_type::size_m(size1_, size2_);
                    }
                    size_type first_j = layout_type::index_m(M,m);
                    return const_iterator2 (*this, rank, i, first_j, itv, it);
                }
                if (it != it_end && (*it).first == layout_type::index_m (i, j))
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = (*it).first;
                    } else {
                        if (j >= size2_)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).second.begin ())
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- it;
                        j = (*it).first;
                    } else {
                        if (j == 0)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());
            for (;;) {
                vector_subiterator_type itv (data ().lower_bound (layout_type::index_M (i, j)));
                vector_subiterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).second.end ());

                subiterator_type it ((*itv).second.lower_bound (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).second.end ());
                if (rank == 0) {
                    // advance to the first available major index
                    size_type M = itv->first;
                    size_type m;
                    if (it != it_end) { 
                        m = it->first; 
                    } else {
                        m = layout_type::size_m(size1_, size2_);
                    }
                    size_type first_j = layout_type::index_m(M,m);
                    return iterator2 (*this, rank, i, first_j, itv, it);
                }
                if (it != it_end && (*it).first == layout_type::index_m (i, j))
                    return iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = (*it).first;
                    } else {
                        if (j >= size2_)
                            return iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).second.begin ())
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- it;
                        j = (*it).first;
                    } else {
                        if (j == 0)
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                array_size_type address1 (layout_type::index_M (i, j));
                array_size_type address2 (layout_type::index_m (i, j));
                vector_const_subiterator_type itv (index1_data_.begin () + (std::min) (filled1_ - 1, address1));
                if (filled1_ <= address1 + 1)
                    return const_iterator1 (*this, rank, i, j, itv, index2_data_.begin () + filled2_);

                const_subiterator_type it_begin (index2_data_.begin () + zero_based (*itv));
                const_subiterator_type it_end (index2_data_.begin () + zero_based (*(itv + 1)));

                const_subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                if (rank == 0)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*it);
                    } else {
                        if (i >= size1_)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == index2_data_.begin () + zero_based (*itv))
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*(it - 1));
                    } else {
                        if (i == 0)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                array_size_type address1 (layout_type::index_M (i, j));
                array_size_type address2 (layout_type::index_m (i, j));
                vector_subiterator_type itv (index1_data_.begin () + (std::min) (filled1_ - 1, address1));
                if (filled1_ <= address1 + 1)
                    return iterator1 (*this, rank, i, j, itv, index2_data_.begin () + filled2_);

                subiterator_type it_begin (index2_data_.begin () + zero_based (*itv));
                subiterator_type it_end (index2_data_.begin () + zero_based (*(itv + 1)));

                subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                if (rank == 0)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*it);
                    } else {
                        if (i >= size1_)
                            return iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == index2_data_.begin () + zero_based (*itv))
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*(it - 1));
                    } else {
                        if (i == 0)
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                array_size_type address1 (layout_type::index_M (i, j));
                array_size_type address2 (layout_type::index_m (i, j));
                vector_const_subiterator_type itv (index1_data_.begin () + (std::min) (filled1_ - 1, address1));
                if (filled1_ <= address1 + 1)
                    return const_iterator2 (*this, rank, i, j, itv, index2_data_.begin () + filled2_);

                const_subiterator_type it_begin (index2_data_.begin () + zero_based (*itv));
                const_subiterator_type it_end (index2_data_.begin () + zero_based (*(itv + 1)));

                const_subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                if (rank == 0)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*it);
                    } else {
                        if (j >= size2_)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == index2_data_.begin () + zero_based (*itv))
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*(it - 1));
                    } else {
                        if (j == 0)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                array_size_type address1 (layout_type::index_M (i, j));
                array_size_type address2 (layout_type::index_m (i, j));
                vector_subiterator_type itv (index1_data_.begin () + (std::min) (filled1_ - 1, address1));
                if (filled1_ <= address1 + 1)
                    return iterator2 (*this, rank, i, j, itv, index2_data_.begin () + filled2_);

                subiterator_type it_begin (index2_data_.begin () + zero_based (*itv));
                subiterator_type it_end (index2_data_.begin () + zero_based (*(itv + 1)));

                subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                if (rank == 0)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*it);
                    } else {
                        if (j >= size2_)
                            return iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == index2_data_.begin () + zero_based (*itv))
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*(it - 1));
                    } else {
                        if (j == 0)
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            sort ();
            for (;;) {
                size_type address1 (layout_type::index_M (i, j));
                size_type address2 (layout_type::index_m (i, j));
                vector_const_subiterator_type itv_begin (detail::lower_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));
                vector_const_subiterator_type itv_end (detail::upper_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));

                const_subiterator_type it_begin (index2_data_.begin () + (itv_begin - index1_data_.begin ()));
                const_subiterator_type it_end (index2_data_.begin () + (itv_end - index1_data_.begin ()));

                const_subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                vector_const_subiterator_type itv (index1_data_.begin () + (it - index2_data_.begin ()));
                if (rank == 0)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*it);
                    } else {
                        if (i >= size1_)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == index2_data_.begin () + array_size_type (zero_based (*itv)))
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*(it - 1));
                    } else {
                        if (i == 0)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            sort ();
            for (;;) {
                size_type address1 (layout_type::index_M (i, j));
                size_type address2 (layout_type::index_m (i, j));
                vector_subiterator_type itv_begin (detail::lower_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));
                vector_subiterator_type itv_end (detail::upper_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));

                subiterator_type it_begin (index2_data_.begin () + (itv_begin - index1_data_.begin ()));
                subiterator_type it_end (index2_data_.begin () + (itv_end - index1_data_.begin ()));

                subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                vector_subiterator_type itv (index1_data_.begin () + (it - index2_data_.begin ()));
                if (rank == 0)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*it);
                    } else {
                        if (i >= size1_)
                            return iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == index2_data_.begin () + array_size_type (zero_based (*itv)))
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = zero_based (*(it - 1));
                    } else {
                        if (i == 0)
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            sort ();
            for (;;) {
                size_type address1 (layout_type::index_M (i, j));
                size_type address2 (layout_type::index_m (i, j));
                vector_const_subiterator_type itv_begin (detail::lower_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));
                vector_const_subiterator_type itv_end (detail::upper_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));

                const_subiterator_type it_begin (index2_data_.begin () + (itv_begin - index1_data_.begin ()));
                const_subiterator_type it_end (index2_data_.begin () + (itv_end - index1_data_.begin ()));

                const_subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                vector_const_subiterator_type itv (index1_data_.begin () + (it - index2_data_.begin ()));
                if (rank == 0)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*it);
                    } else {
                        if (j >= size2_)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == index2_data_.begin () + array_size_type (zero_based (*itv)))
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*(it - 1));
                    } else {
                        if (j == 0)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            sort ();
            for (;;) {
                size_type address1 (layout_type::index_M (i, j));
                size_type address2 (layout_type::index_m (i, j));
                vector_subiterator_type itv_begin (detail::lower_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));
                vector_subiterator_type itv_end (detail::upper_bound (index1_data_.begin (), index1_data_.begin () + filled_, k_based (address1), std::less<size_type> ()));

                subiterator_type it_begin (index2_data_.begin () + (itv_begin - index1_data_.begin ()));
                subiterator_type it_end (index2_data_.begin () + (itv_end - index1_data_.begin ()));

                subiterator_type it (detail::lower_bound (it_begin, it_end, k_based (address2), std::less<size_type> ()));
                vector_subiterator_type itv (index1_data_.begin () + (it - index2_data_.begin ()));
                if (rank == 0)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && zero_based (*it) == address2)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*it);
                    } else {
                        if (j >= size2_)
                            return iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == index2_data_.begin () + array_size_type (zero_based (*itv)))
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = zero_based (*(it - 1));
                    } else {
                        if (j == 0)
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }


    template<class M>
    bool is_hermitian (const M &m) {
        typedef typename M::size_type size_type;

        if (m.size1 () != m.size2 ())
            return false;
        size_type size = BOOST_UBLAS_SAME (m.size1 (), m.size2 ());
        for (size_type i = 0; i < size; ++ i) {
            for (size_type j = i; j < size; ++ j) {
                if (m (i, j) != conj (m (j, i)))
                    return false;
            }
        }
        return true;
    }

  template<class T> T boost_numeric_ublas_sqrt (const T& t) {
    using namespace std;
    // we'll find either std::sqrt or else another version via ADL:
    return sqrt (t);
  }

  template<class T> T boost_numeric_ublas_abs (const T& t) {
    using namespace std;
    // we'll find either std::abs or else another version via ADL:
    return abs (t);
  }

        static
        const_iterator begin(const VECTOR & v) {
            return v.begin();
        }

        static
        const_iterator end(const VECTOR & v) {
            return v.end();
        }

        static
        iterator begin(VECTOR & v) {
            return v.begin();
        }

        static
        iterator end(VECTOR & v) {
            return v.end();
        }

        BOOST_UBLAS_INLINE
        ~unbounded_array () {
            if (size_) {
                if (! detail::has_trivial_destructor<T>::value) {
                    // std::_Destroy (begin(), end(), alloc_);
                    const iterator i_end = end();
                    for (iterator i = begin (); i != i_end; ++i) {
                        iterator_destroy (i); 
                    }
                }
                alloc_.deallocate (data_, size_);
            }
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        { 
            serialization::collection_size_type s(size_);
            ar & serialization::make_nvp("size",s);
            if ( Archive::is_loading::value ) {
                resize(s);
            }
            ar & serialization::make_array(data_, s);
        }


        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            serialization::collection_size_type s(size_);
            ar & serialization::make_nvp("size", s);
            if ( Archive::is_loading::value ) {
                if (s > N) bad_size("too large size in bounded_array::load()\n").raise();
                resize(s);
            }
            ar & serialization::make_array(data_, s);
        }

        BOOST_UBLAS_INLINE
        ~array_adaptor () {
            if (own_) {
                delete [] data_;
            }
        }

         BOOST_UBLAS_INLINE
        ~index_pair() {
            if (dirty_ && (!is_copy_) ) {
                (*this)().data1_[i_] = v1_;
                (*this)().data2_[i_] = v2_;
            }
        }

        BOOST_UBLAS_INLINE
        ~index_triple() {
            if (dirty_ && (!is_copy_) ) {
                (*this)().data1_[i_] = v1_;
                (*this)().data2_[i_] = v2_;
                (*this)().data3_[i_] = v3_;
            }
        }

        const_iterator find (size_type i) const {
            return const_iterator (*this, data ().lower_bound (i));
        }

        iterator find (size_type i) {
            return iterator (*this, data ().lower_bound (i));
        }

        const_iterator find (size_type i) const {
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }

        iterator find (size_type i) {
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }

        const_iterator find (size_type i) const {
            sort ();
            return const_iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }

        iterator find (size_type i) {
            sort ();
            return iterator (*this, detail::lower_bound (index_data_.begin (), index_data_.begin () + filled_, k_based (i), std::less<size_type> ()));
        }

        BOOST_UBLAS_INLINE
        ~diagonal_matrix () {}

        BOOST_UBLAS_INLINE
        ~diagonal_adaptor () {}
 &
    axpy_prod (const compressed_matrix<T1, L1, 0, IA1, TA1> &e1,
               const vector_expression<E2> &e2,
               V &v, row_major_tag) {
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;

        for (size_type i = 0; i < e1.filled1 () -1; ++ i) {
            size_type begin = e1.index1_data () [i];
            size_type end = e1.index1_data () [i + 1];
            value_type t (v (i));
            for (size_type j = begin; j < end; ++ j)
                t += e1.value_data () [j] * e2 () (e1.index2_data () [j]);
            v (i) = t;
        }
        return v;
    }
 &
    opb_prod (const matrix_expression<E1> &e1,
              const matrix_expression<E2> &e2,
              M &m,
              dense_proxy_tag, row_major_tag) {
        typedef M matrix_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

#if BOOST_UBLAS_TYPE_CHECK
        matrix<value_type, row_major> cm (m);
        typedef typename type_traits<value_type>::real_type real_type;
        real_type merrorbound (norm_1 (m) + norm_1 (e1) * norm_1 (e2));
        indexing_matrix_assign<scalar_plus_assign> (cm, prod (e1, e2), row_major_tag ());
#endif
        size_type size (BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size1 ()));
        for (size_type k = 0; k < size; ++ k) {
            vector<value_type> ce1 (column (e1 (), k));
            vector<value_type> re2 (row (e2 (), k));
            m.plus_assign (outer_prod (ce1, re2));
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (m - cm) <= 2 * std::numeric_limits<real_type>::epsilon () * merrorbound, internal_logic ());
#endif
        return m;
    }

        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                const_vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                const_vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                const_subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = it.index ();
                    } else {
                        if (i >= size1_)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).begin ())
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        --it;
                        i = it.index ();
                    } else {
                        if (i == 0)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = it.index ();
                    } else {
                        if (i >= size1_)
                            return iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).begin ())
                            return iterator1 (*this, rank, i, j, itv, it);
                        --it;
                        i = it.index ();
                    } else {
                        if (i == 0)
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }

        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                const_vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                const_vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                const_subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = it.index ();
                    } else {
                        if (j >= size2_)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).begin ())
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        --it;
                        j = it.index ();
                    } else {
                        if (j == 0)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = it.index ();
                    } else {
                        if (j >= size2_)
                            return iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).begin ())
                            return iterator2 (*this, rank, i, j, itv, it);
                        --it;
                        j = it.index ();
                    } else {
                        if (j == 0)
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }

	     BOOST_UBLAS_INLINE
	     ~bounded_vector () {}
 &
    sparse_prod (const matrix_expression<E1> &e1,
                 const matrix_expression<E2> &e2,
                 M &m, TRI,
                 row_major_tag) {
        typedef M matrix_type;
        typedef TRI triangular_restriction;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename M::size_type size_type;
        typedef typename M::value_type value_type;

        // ISSUE why is there a dense vector here?
        vector<value_type> temporary (e2 ().size2 ());
        temporary.clear ();
        typename expression1_type::const_iterator1 it1 (e1 ().begin1 ());
        typename expression1_type::const_iterator1 it1_end (e1 ().end1 ());
        while (it1 != it1_end) {
            size_type jb (temporary.size ());
            size_type je (0);
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename expression1_type::const_iterator2 it2 (it1.begin ());
            typename expression1_type::const_iterator2 it2_end (it1.end ());
#else
            typename expression1_type::const_iterator2 it2 (boost::numeric::ublas::begin (it1, iterator1_tag ()));
            typename expression1_type::const_iterator2 it2_end (boost::numeric::ublas::end (it1, iterator1_tag ()));
#endif
            while (it2 != it2_end) {
                // temporary.plus_assign (*it2 * row (e2 (), it2.index2 ()));
                matrix_row<expression2_type> mr (e2 (), it2.index2 ());
                typename matrix_row<expression2_type>::const_iterator itr (mr.begin ());
                typename matrix_row<expression2_type>::const_iterator itr_end (mr.end ());
                while (itr != itr_end) {
                    size_type j (itr.index ());
                    temporary (j) += *it2 * *itr;
                    jb = (std::min) (jb, j);
                    je = (std::max) (je, j);
                    ++ itr;
                }
                ++ it2;
            }
            for (size_type j = jb; j < je + 1; ++ j) {
                if (temporary (j) != value_type/*zero*/()) {
                    // FIXME we'll need to extend the container interface!
                    // m.push_back (it1.index1 (), j, temporary (j));
                    // FIXME What to do with adaptors?
                    // m.insert (it1.index1 (), j, temporary (j));
                    if (triangular_restriction::other (it1.index1 (), j))
                        m (it1.index1 (), j) = temporary (j);
                    temporary (j) = value_type/*zero*/();
                }
            }
            ++ it1;
        }
        return m;
    }

    block_prod (const matrix_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef V vector_type;
        typedef const E1 expression1_type;
        typedef const E2 expression2_type;
        typedef typename V::size_type size_type;
        typedef typename V::value_type value_type;
        const size_type block_size = BS;

        V v (e1 ().size1 ());
#if BOOST_UBLAS_TYPE_CHECK
        vector<value_type> cv (v.size ());
        typedef typename type_traits<value_type>::real_type real_type;
        real_type verrorbound (norm_1 (v) + norm_1 (e1) * norm_1 (e2));
        indexing_vector_assign<scalar_assign> (cv, prod (e1, e2));
#endif
        size_type i_size = e1 ().size1 ();
        size_type j_size = BOOST_UBLAS_SAME (e1 ().size2 (), e2 ().size ());
        for (size_type i_begin = 0; i_begin < i_size; i_begin += block_size) {
            size_type i_end = i_begin + (std::min) (i_size - i_begin, block_size);
            // FIX: never ignore Martin Weiser's advice ;-(
#ifdef BOOST_UBLAS_NO_CACHE
            vector_range<vector_type> v_range (v, range (i_begin, i_end));
#else
            // vector<value_type, bounded_array<value_type, block_size> > v_range (i_end - i_begin);
            vector<value_type> v_range (i_end - i_begin);
#endif
            v_range.assign (zero_vector<value_type> (i_end - i_begin));
            for (size_type j_begin = 0; j_begin < j_size; j_begin += block_size) {
                size_type j_end = j_begin + (std::min) (j_size - j_begin, block_size);
#ifdef BOOST_UBLAS_NO_CACHE
                const matrix_range<expression1_type> e1_range (e1 (), range (i_begin, i_end), range (j_begin, j_end));
                const vector_range<expression2_type> e2_range (e2 (), range (j_begin, j_end));
                v_range.plus_assign (prod (e1_range, e2_range));
#else
                // const matrix<value_type, row_major, bounded_array<value_type, block_size * block_size> > e1_range (project (e1 (), range (i_begin, i_end), range (j_begin, j_end)));
                // const vector<value_type, bounded_array<value_type, block_size> > e2_range (project (e2 (), range (j_begin, j_end)));
                const matrix<value_type, row_major> e1_range (project (e1 (), range (i_begin, i_end), range (j_begin, j_end)));
                const vector<value_type> e2_range (project (e2 (), range (j_begin, j_end)));
                v_range.plus_assign (prod (e1_range, e2_range));
#endif
            }
#ifndef BOOST_UBLAS_NO_CACHE
            project (v, range (i_begin, i_end)).assign (v_range);
#endif
        }
#if BOOST_UBLAS_TYPE_CHECK
        BOOST_UBLAS_CHECK (norm_1 (v - cv) <= 2 * std::numeric_limits<real_type>::epsilon () * verrorbound, internal_logic ());
#endif
        return v;
    }


    template<class M>
    bool is_symmetric (const M &m) {
        typedef typename M::size_type size_type;

        if (m.size1 () != m.size2 ())
            return false;
        size_type size = BOOST_UBLAS_SAME (m.size1 (), m.size2 ());
        for (size_type i = 0; i < size; ++ i) {
            for (size_type j = i; j < size; ++ j) {
                if (m (i, j) != m (j, i))
                    return false;
            }
        }
        return true;
    }

        explicit divide_by_zero (const char *s = "divide by zero") :
            std::runtime_error (s) {}

        void raise () {
            throw *this;
        }

        explicit internal_logic (const char *s = "internal logic") :
            std::logic_error (s) {}

        void raise () {
            throw *this;
        }

        explicit external_logic (const char *s = "external logic") :
            std::logic_error (s) {}

        void raise () {
            throw *this;
        }

        explicit bad_argument (const char *s = "bad argument") :
            std::invalid_argument (s) {}

        void raise () {
            throw *this;
        }

        explicit bad_size (const char *s = "bad size") :
            std::domain_error (s) {}

        void raise () {
            throw *this;
        }

        explicit bad_index (const char *s = "bad index") :
            std::out_of_range (s) {}

        void raise () {
            throw *this;
        }

        explicit singular (const char *s = "singular") :
            std::runtime_error (s) {}

        void raise () {
            throw *this;
        }

        explicit non_real (const char *s = "exception: non real") :
            std::domain_error (s) {}

        void raise () {
            throw *this;
        }
 same_impl_ex (const T1 &size1, const T2 &size2, const char *file, int line) {
        BOOST_UBLAS_CHECK_EX (size1 == size2, file, line, bad_argument ());
        return (size1 < size2)?(size1):(size2);
    }
 lower_bound (const I &begin, const I &end, const T &t, C compare) {
            // t <= *begin <=> ! (*begin < t)
            if (begin == end || ! compare (*begin, t))
                return begin;
            if (compare (*(end - 1), t))
                return end;
            return std::lower_bound (begin, end, t, compare);
        }
 upper_bound (const I &begin, const I &end, const T &t, C compare) {
            if (begin == end || compare (t, *begin))
                return begin;
            // (*end - 1) <= t <=> ! (t < *end)
            if (! compare (t, *(end - 1)))
                return end;
            return std::upper_bound (begin, end, t, compare);
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            ar & serialization::make_nvp("base", boost::serialization::base_object< std::map<I, T /*, ALLOC */> >(*this));
        }

        BOOST_UBLAS_INLINE
        ~map_array () {
            if (capacity_) {
                std::for_each (data_, data_ + capacity_, static_destroy);
                alloc_.deallocate (data_, capacity_);
            }
        }

            type operator() ( map_array<I, T, ALLOC> const& m ) const {
               return m.capacity ();
            }
 row (M &data, typename M::size_type i) {
        return matrix_row<M> (data, i);
    }
 column (M &data, typename M::size_type j) {
        return matrix_column<M> (data, j);
    }
 subrange (M &data, typename M::size_type start1, typename M::size_type stop1, typename M::size_type start2, typename M::size_type stop2) {
        typedef basic_range<typename M::size_type, typename M::difference_type> range_type;
        return matrix_range<M> (data, range_type (start1, stop1), range_type (start2, stop2));
    }
 project (M &data, const typename matrix_range<M>::range_type &r1, const typename matrix_range<M>::range_type &r2) {
        return matrix_range<M> (data, r1, r2);
    }
 subslice (M &data, typename M::size_type start1, typename M::difference_type stride1, typename M::size_type size1, typename M::size_type start2, typename M::difference_type stride2, typename M::size_type size2) {
        typedef basic_slice<typename M::size_type, typename M::difference_type> slice_type;
        return matrix_slice<M> (data, slice_type (start1, stride1, size1), slice_type (start2, stride2, size2));
    }
 subrange (V &data, typename V::size_type start, typename V::size_type stop) {
        typedef basic_range<typename V::size_type, typename V::difference_type> range_type;
        return vector_range<V> (data, range_type (start, stop));
    }
 project (V &data, typename vector_range<V>::range_type const &r) {
        return vector_range<V> (data, r);
    }
 subslice (V &data, typename V::size_type start, typename V::difference_type stride, typename V::size_type size) {
        typedef basic_slice<typename V::size_type, typename V::difference_type> slice_type;
        return vector_slice<V> (data, slice_type (start, stride, size));
    }

        nrm2 (const V &v) {
            return norm_2 (v);
        }

        amax (const V &v) {
            return norm_inf (v);
        }

        template<class V1, class V2>
        V1 & copy (V1 &v1, const V2 &v2) 
    {
            return v1.assign (v2);
        }

    template<class V1, class V2>
        void swap (V1 &v1, V2 &v2) 
    {
            v1.swap (v2);
        }

        template<class V, class T>
        V & scal (V &v, const T &t) 
    {
            return v *= t;
        }

        template<class V1, class T, class V2>
        V1 & axpy (V1 &v1, const T &t, const V2 &v2) 
    {
            return v1.plus_assign (t * v2);
        }

        template<class T1, class V1, class T2, class V2>
        void rot (const T1 &t1, V1 &v1, const T2 &t2, V2 &v2) 
    {
            typedef typename promote_traits<typename V1::value_type, typename V2::value_type>::promote_type promote_type;
            vector<promote_type> vt (t1 * v1 + t2 * v2);
            v2.assign (- t2 * v1 + t1 * v2);
            v1.assign (vt);
        }
                 
        template<class V, class M>
        V & tmv (V &v, const M &m) 
    {
            return v = prod (m, v);
        }
                 
        template<class V, class M, class C>
        V & tsv (V &v, const M &m, C) 
    {
            return v = solve (m, v, C ());
        }
                 
        template<class V1, class T1, class T2, class M, class V2>
        V1 & gmv (V1 &v1, const T1 &t1, const T2 &t2, const M &m, const V2 &v2) 
    {
            return v1 = t1 * v1 + t2 * prod (m, v2);
        }

        template<class M, class T, class V1, class V2>
        M & gr (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v1, v2);
#else
            return m = m + t * outer_prod (v1, v2);
#endif
        }

        template<class M, class T, class V>
        M & sr (M &m, const T &t, const V &v) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v, v);
#else
            return m = m + t * outer_prod (v, v);
#endif
        }

        template<class M, class T, class V>
        M & hr (M &m, const T &t, const V &v) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v, conj (v));
#else
            return m = m + t * outer_prod (v, conj (v));
#endif
        }
                 
        template<class M, class T, class V1, class V2>
        M & sr2 (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * (outer_prod (v1, v2) + outer_prod (v2, v1));
#else
            return m = m + t * (outer_prod (v1, v2) + outer_prod (v2, v1));
#endif
        }
                 
        template<class M, class T, class V1, class V2>
        M & hr2 (M &m, const T &t, const V1 &v1, const V2 &v2) 
    {
#ifndef BOOST_UBLAS_SIMPLE_ET_DEBUG
            return m += t * outer_prod (v1, conj (v2)) + type_traits<T>::conj (t) * outer_prod (v2, conj (v1));
#else
            return m = m + t * outer_prod (v1, conj (v2)) + type_traits<T>::conj (t) * outer_prod (v2, conj (v1));
#endif
        }
                 
        template<class M1, class T, class M2, class M3>
        M1 & tmm (M1 &m1, const T &t, const M2 &m2, const M3 &m3) 
    {
            return m1 = t * prod (m2, m3);
        }
                 
        template<class M1, class T, class M2, class C>
        M1 & tsm (M1 &m1, const T &t, const M2 &m2, C) 
    {
            return m1 = solve (m2, t * m1, C ());
        }
                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & gmm (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, m3);
        }
                 
        template<class M1, class T1, class T2, class M2>
        M1 & srk (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, trans (m2));
        }
                 
        template<class M1, class T1, class T2, class M2>
        M1 & hrk (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2) 
    {
            return m1 = t1 * m1 + t2 * prod (m2, herm (m2));
        }
                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & sr2k (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = t1 * m1 + t2 * (prod (m2, trans (m3)) + prod (m3, trans (m2)));
        }
                 
        template<class M1, class T1, class T2, class M2, class M3>
        M1 & hr2k (M1 &m1, const T1 &t1, const T2 &t2, const M2 &m2, const M3 &m3) 
    {
            return m1 = 
              t1 * m1 
            + t2 * prod (m2, herm (m3)) 
            + type_traits<T2>::conj (t2) * prod (m3, herm (m2));
        }

    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_vector_assign_scalar (V &v, const T &t) {
        typedef F<typename V::iterator::reference, T> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (v.size ());
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type::apply (*it, t), ++ it;
#else
        DD (size, 4, r, (functor_type::apply (*it, t), ++ it));
#endif
    }

    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_vector_assign_scalar (V &v, const T &t) {
        typedef F<typename V::reference, T> functor_type;
        typedef typename V::size_type size_type;
        size_type size (v.size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (size_type i = 0; i < size; ++ i)
            functor_type::apply (v (i), t);
#else
        size_type i (0);
        DD (size, 4, r, (functor_type::apply (v (i), t), ++ i));
#endif
    }

    template<template <class T1, class T2> class F, class V, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign_scalar (V &v, const T &t, dense_proxy_tag) {
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_vector_assign_scalar<F> (v, t);
#elif BOOST_UBLAS_USE_ITERATING
        iterating_vector_assign_scalar<F> (v, t);
#else
        typedef typename V::size_type size_type;
        size_type size (v.size ());
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign_scalar<F> (v, t);
        else
            indexing_vector_assign_scalar<F> (v, t);
#endif
    }

    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_vector_assign (V &v, const vector_expression<E> &e) {
        typedef F<typename V::iterator::reference, typename E::value_type> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        typename V::iterator it (v.begin ());
        BOOST_UBLAS_CHECK (v.end () - it == size, bad_size ());
        typename E::const_iterator ite (e ().begin ());
        BOOST_UBLAS_CHECK (e ().end () - ite == size, bad_size ());
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
#else
        DD (size, 2, r, (functor_type::apply (*it, *ite), ++ it, ++ ite));
#endif
    }

    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_vector_assign (V &v, const vector_expression<E> &e) {
        typedef F<typename V::reference, typename E::value_type> functor_type;
        typedef typename V::size_type size_type;
        size_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
        for (size_type i = 0; i < size; ++ i)
            functor_type::apply (v (i), e () (i));
#else
        size_type i (0);
        DD (size, 2, r, (functor_type::apply (v (i), e () (i)), ++ i));
#endif
    }

    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_assign (V &v, const vector_expression<E> &e, dense_proxy_tag) {
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_vector_assign<F> (v, e);
#elif BOOST_UBLAS_USE_ITERATING
        iterating_vector_assign<F> (v, e);
#else
        typedef typename V::size_type size_type;
        size_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        if (size >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_vector_assign<F> (v, e);
        else
            indexing_vector_assign<F> (v, e);
#endif
    }

    template<template <class T1, class T2> class F, class V, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void vector_swap (V &v, vector_expression<E> &e, dense_proxy_tag) {
        typedef F<typename V::iterator::reference, typename E::iterator::reference> functor_type;
        typedef typename V::difference_type difference_type;
        difference_type size (BOOST_UBLAS_SAME (v.size (), e ().size ()));
        typename V::iterator it (v.begin ());
        typename E::iterator ite (e ().begin ());
        while (-- size >= 0)
            functor_type::apply (*it, *ite), ++ it, ++ ite;
    }

        template <class T> inline
        void ignore_unused_variable_warning(const T&) {}

            nonassignable () {}

            ~nonassignable () {}
 noalias (C& lvalue) {
        return noalias_proxy<C> (lvalue);
    }
& safe (C& lvalue) {
        return lvalue;
    }

    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign_scalar (M &m, const T &t, row_major_tag) {
        typedef F<typename M::iterator2::reference, T> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size1 (m.size1 ());
        difference_type size2 (m.size2 ());
        typename M::iterator1 it1 (m.begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || m.end1 () - it1 == size1, bad_size ());
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
#endif
            BOOST_UBLAS_CHECK (it1.end () - it2 == size2, bad_size ());
            difference_type temp_size2 (size2);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size2 >= 0)
                functor_type::apply (*it2, t), ++ it2;
#else
            DD (temp_size2, 4, r, (functor_type::apply (*it2, t), ++ it2));
#endif
            ++ it1;
        }
    }

    template<template <class T1, class T2> class F, class M, class T>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign_scalar (M &m, const T &t, row_major_tag) {
        typedef F<typename M::reference, T> functor_type;
        typedef typename M::size_type size_type;
        size_type size1 (m.size1 ());
        size_type size2 (m.size2 ());
        for (size_type i = 0; i < size1; ++ i) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size2; ++ j)
                functor_type::apply (m (i, j), t);
#else
            size_type j (0);
            DD (size2, 4, r, (functor_type::apply (m (i, j), t), ++ j));
#endif
        }
    }

    template<template <class T1, class T2> class F, class M, class T, class C>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign_scalar (M &m, const T &t, dense_proxy_tag, C) {
        typedef C orientation_category;
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_matrix_assign_scalar<F> (m, t, orientation_category ());
#elif BOOST_UBLAS_USE_ITERATING
        iterating_matrix_assign_scalar<F> (m, t, orientation_category ());
#else
        typedef typename M::size_type size_type;
        size_type size1 (m.size1 ());
        size_type size2 (m.size2 ());
        if (size1 >= BOOST_UBLAS_ITERATOR_THRESHOLD &&
            size2 >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_matrix_assign_scalar<F> (m, t, orientation_category ());
        else
            indexing_matrix_assign_scalar<F> (m, t, orientation_category ());
#endif
    }

    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void iterating_matrix_assign (M &m, const matrix_expression<E> &e, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::value_type> functor_type;
        typedef typename M::difference_type difference_type;
        difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        typename M::iterator1 it1 (m.begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || m.end1 () - it1 == size1, bad_size ());
        typename E::const_iterator1 it1e (e ().begin1 ());
        BOOST_UBLAS_CHECK (size2 == 0 || e ().end1 () - it1e == size1, bad_size ());
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename E::const_iterator2 it2e (it1e.begin ());
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename E::const_iterator2 it2e (begin (it1e, iterator1_tag ()));
#endif
            BOOST_UBLAS_CHECK (it1.end () - it2 == size2, bad_size ());
            BOOST_UBLAS_CHECK (it1e.end () - it2e == size2, bad_size ());
            difference_type temp_size2 (size2);
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            while (-- temp_size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
#else
            DD (temp_size2, 2, r, (functor_type::apply (*it2, *it2e), ++ it2, ++ it2e));
#endif
            ++ it1, ++ it1e;
        }
    }

    template<template <class T1, class T2> class F, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void indexing_matrix_assign (M &m, const matrix_expression<E> &e, row_major_tag) {
        typedef F<typename M::reference, typename E::value_type> functor_type;
        typedef typename M::size_type size_type;
        size_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        size_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        for (size_type i = 0; i < size1; ++ i) {
#ifndef BOOST_UBLAS_USE_DUFF_DEVICE
            for (size_type j = 0; j < size2; ++ j)
                functor_type::apply (m (i, j), e () (i, j));
#else
            size_type j (0);
            DD (size2, 2, r, (functor_type::apply (m (i, j), e () (i, j)), ++ j));
#endif
        }
    }

    template<template <class T1, class T2> class F, class R, class M, class E, class C>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_assign (M &m, const matrix_expression<E> &e, dense_proxy_tag, C) {
        // R unnecessary, make_conformant not required
        typedef C orientation_category;
#ifdef BOOST_UBLAS_USE_INDEXING
        indexing_matrix_assign<F> (m, e, orientation_category ());
#elif BOOST_UBLAS_USE_ITERATING
        iterating_matrix_assign<F> (m, e, orientation_category ());
#else
        typedef typename M::difference_type difference_type;
        size_type size1 (BOOST_UBLAS_SAME (m.size1 (), e ().size1 ()));
        size_type size2 (BOOST_UBLAS_SAME (m.size2 (), e ().size2 ()));
        if (size1 >= BOOST_UBLAS_ITERATOR_THRESHOLD &&
            size2 >= BOOST_UBLAS_ITERATOR_THRESHOLD)
            iterating_matrix_assign<F> (m, e, orientation_category ());
        else
            indexing_matrix_assign<F> (m, e, orientation_category ());
#endif
    }

    template<template <class T1, class T2> class F, class R, class M, class E>
    // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.
    void matrix_swap (M &m, matrix_expression<E> &e, dense_proxy_tag, row_major_tag) {
        typedef F<typename M::iterator2::reference, typename E::reference> functor_type;
        // R unnecessary, make_conformant not required
        typedef typename M::size_type size_type;
        typedef typename M::difference_type difference_type;
        typename M::iterator1 it1 (m.begin1 ());
        typename E::iterator1 it1e (e ().begin1 ());
        difference_type size1 (BOOST_UBLAS_SAME (m.size1 (), size_type (e ().end1 () - it1e)));
        while (-- size1 >= 0) {
#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            typename M::iterator2 it2 (it1.begin ());
            typename E::iterator2 it2e (it1e.begin ());
            difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), size_type (it1e.end () - it2e)));
#else
            typename M::iterator2 it2 (begin (it1, iterator1_tag ()));
            typename E::iterator2 it2e (begin (it1e, iterator1_tag ()));
            difference_type size2 (BOOST_UBLAS_SAME (m.size2 (), size_type (end (it1e, iterator1_tag ()) - it2e)));
#endif
            while (-- size2 >= 0)
                functor_type::apply (*it2, *it2e), ++ it2, ++ it2e;
            ++ it1, ++ it1e;
        }
    }


        void constraints () {
            iterator_type it = iterator_type ();
            // Index
            it.index ();
        }


        void constraints () {
            function_requires< BidirectionalIteratorConcept<iterator_type> >();
            function_requires< Indexed1DIteratorConcept<iterator_type> >();
        }


        void constraints () {
            function_requires< Mutable_BidirectionalIteratorConcept<iterator_type> >();
            function_requires< Indexed1DIteratorConcept<iterator_type> >();
        }


        void constraints () {
            function_requires< RandomAccessIteratorConcept<iterator_type> >();
            function_requires< Indexed1DIteratorConcept<iterator_type> >();
        }


        void constraints () {
            function_requires< Mutable_RandomAccessIteratorConcept<iterator_type> >();
            function_requires< Indexed1DIteratorConcept<iterator_type> >();
        }


        void constraints () {
            iterator_type it = iterator_type ();
            // Indices
            it.index1 ();
            it.index2 ();
            // Iterator begin/end
            dual_iterator_type it_begin (it.begin ());
            dual_iterator_type it_end (it.end ());
            // Reverse iterator begin/end
            dual_reverse_iterator_type it_rbegin (it.rbegin ());
            dual_reverse_iterator_type it_rend (it.rend ());
            ignore_unused_variable_warning (it_begin);
            ignore_unused_variable_warning (it_end);
            ignore_unused_variable_warning (it_rbegin);
            ignore_unused_variable_warning (it_rend);
        }


        void constraints () {
            function_requires< BidirectionalIteratorConcept<subiterator1_type> >();
            function_requires< BidirectionalIteratorConcept<subiterator2_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator1_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator2_type> >();
        }


        void constraints () {
            function_requires< Mutable_BidirectionalIteratorConcept<subiterator1_type> >();
            function_requires< Mutable_BidirectionalIteratorConcept<subiterator2_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator1_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator2_type> >();
        }


        void constraints () {
            function_requires< RandomAccessIteratorConcept<subiterator1_type> >();
            function_requires< RandomAccessIteratorConcept<subiterator2_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator1_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator2_type> >();
        }


        void constraints () {
            function_requires< Mutable_RandomAccessIteratorConcept<subiterator1_type> >();
            function_requires< Mutable_RandomAccessIteratorConcept<subiterator2_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator1_type> >();
            function_requires< Indexed2DIteratorConcept<subiterator2_type> >();
        }


        void constraints () {
            function_requires< RandomAccessContainerConcept<container_type> >();
            size_type n (0);
            // Sizing constructor
            container_type c = container_type (n);
            // Initialised sizing constructor
            container_type (n, value_type (5));
            ignore_unused_variable_warning (c);
        }


        void constraints () {
            function_requires< Mutable_RandomAccessContainerConcept<container_type> > ();
            size_type n (0);
            // Sizing constructor
            container_type c = container_type (n);
            // Initialised sizing constructor
            c = container_type (n, value_type (3));
            // Resize
            c.resize (n, value_type (5));
            // Resize - none preserving
            c.resize (n);
        }


        void constraints () {
            function_requires< ReversibleContainerConcept<container_type> > ();
        }


        void constraints () {
            // NOTE - Not Mutable_ReversibleContainerConcept
            function_requires< ReversibleContainerConcept<container_type> >();
            container_type c = container_type ();
            value_type t = value_type ();
            iterator_type it = iterator_type (), it1 = iterator_type (), it2 = iterator_type ();
            // Insert
            c.insert (it, t);
            // Erase
            c.erase (it);
            // Range erase
            c.erase (it1, it2);
            // Clear
            c.clear ();
        }


        void constraints () {
            function_requires< AssignableConcept<generator_type> >();
            function_requires< ReversibleContainerConcept<generator_type> >();
            generator_type g = generator_type ();
            size_type n (0);
            value_type t;
            // Element access
            t = g (n);
            ignore_unused_variable_warning (t);
        }


        void constraints () {
            scalar_expression_type *sp;
            scalar_expression_type s = *sp;
            value_type t;
            // Conversion
            t = s;
            ignore_unused_variable_warning (t);
        }


        void constraints () {
            vector_expression_type *vp;
            const vector_expression_type *cvp;
            vector_expression_type v = *vp;
            const vector_expression_type cv = *cvp;
            size_type n (0), i (0);
            value_type t;
            // Find (internal?)
            const_iterator_type cit (v.find (i));
            // Beginning of range
            const_iterator_type cit_begin (v.begin ());
            // End of range
            const_iterator_type cit_end (v.end ());
            // Size
            n = v.size ();
            // Beginning of reverse range
            const_reverse_iterator_type crit_begin (cv.rbegin ());
            // End of reverse range
            const_reverse_iterator_type crit_end (cv.rend ());
            // Element access
            t = v (i);
            ignore_unused_variable_warning (n);
            ignore_unused_variable_warning (cit);
            ignore_unused_variable_warning (cit_begin);
            ignore_unused_variable_warning (cit_end);
            ignore_unused_variable_warning (crit_begin);
            ignore_unused_variable_warning (crit_end);
            ignore_unused_variable_warning (t);
        }


        void constraints () {
            function_requires< AssignableConcept<vector_expression_type> >();
            function_requires< VectorExpressionConcept<vector_expression_type> >();
            vector_expression_type *vp;
            vector_expression_type v = *vp, v1 = *vp, v2 = *vp;
            size_type i (0);
            value_type t = value_type ();
            // Find (internal?)
            iterator_type it (v.find (i));
            // Beginning of range
            iterator_type it_begin (v.begin ());
            // End of range
            iterator_type it_end (v.end ());
            // Swap
            v1.swap (v2);
            // Beginning of reverse range
            reverse_iterator_type rit_begin (v.rbegin ());
            // End of reverse range
            reverse_iterator_type rit_end (v.rend ());
            // Assignments
            v2 = v1;
            v2.assign (v1);
            v2 += v1;
            v2.plus_assign (v1);
            v2 -= v1;
            v2.minus_assign (v1);
            v *= t;
            ignore_unused_variable_warning (it);
            ignore_unused_variable_warning (it_begin);
            ignore_unused_variable_warning (it_end);
            ignore_unused_variable_warning (rit_begin);
            ignore_unused_variable_warning (rit_end);
        }


        void constraints () {
            matrix_expression_type *mp;
            const matrix_expression_type *cmp;
            matrix_expression_type m = *mp;
            const matrix_expression_type cm = *cmp;
            size_type n (0), i (0), j (0);
            value_type t;
            // Find (internal?)
            const_subiterator1_type cit1 (m.find1 (0, i, j));
            const_subiterator2_type cit2 (m.find2 (0, i, j));
            // Beginning of range
            const_subiterator1_type cit1_begin (m.begin1 ());
            const_subiterator2_type cit2_begin (m.begin2 ());
            // End of range
            const_subiterator1_type cit1_end (m.end1 ());
            const_subiterator2_type cit2_end (m.end2 ());
            // Size
            n = m.size1 ();
            n = m.size2 ();
            // Beginning of reverse range
            const_reverse_subiterator1_type crit1_begin (cm.rbegin1 ());
            const_reverse_subiterator2_type crit2_begin (cm.rbegin2 ());
            // End of reverse range
            const_reverse_subiterator1_type crit1_end (cm.rend1 ());
            const_reverse_subiterator2_type crit2_end (cm.rend2 ());
            // Element access
            t = m (i, j);
            ignore_unused_variable_warning (n);
            ignore_unused_variable_warning (cit1);
            ignore_unused_variable_warning (cit2);
            ignore_unused_variable_warning (cit1_begin);
            ignore_unused_variable_warning (cit2_begin);
            ignore_unused_variable_warning (cit1_end);
            ignore_unused_variable_warning (cit2_end);
            ignore_unused_variable_warning (crit1_begin);
            ignore_unused_variable_warning (crit2_begin);
            ignore_unused_variable_warning (crit1_end);
            ignore_unused_variable_warning (crit2_end);
            ignore_unused_variable_warning (t);
        }


        void constraints () {
            function_requires< AssignableConcept<matrix_expression_type> >();
            function_requires< MatrixExpressionConcept<matrix_expression_type> >();
            matrix_expression_type *mp;
            matrix_expression_type m = *mp, m1 = *mp, m2 = *mp;
            size_type i (0), j (0);
            value_type t = value_type ();
            // Find (internal?)
            subiterator1_type it1 (m.find1 (0, i, j));
            subiterator2_type it2 (m.find2 (0, i, j));
            // Beginning of range
            subiterator1_type it1_begin (m.begin1 ());
            subiterator2_type it2_begin (m.begin2 ());
            // End of range
            subiterator1_type it1_end (m.end1 ());
            subiterator2_type it2_end (m.end2 ());
            // Swap
            m1.swap (m2);
            // Beginning of reverse range
            reverse_subiterator1_type rit1_begin (m.rbegin1 ());
            reverse_subiterator2_type rit2_begin (m.rbegin2 ());
            // End of reverse range
            reverse_subiterator1_type rit1_end (m.rend1 ());
            reverse_subiterator2_type rit2_end (m.rend2 ());
            // Assignments
            m2 = m1;
            m2.assign (m1);
            m2 += m1;
            m2.plus_assign (m1);
            m2 -= m1;
            m2.minus_assign (m1);
            m *= t;
            ignore_unused_variable_warning (it1);
            ignore_unused_variable_warning (it2);
            ignore_unused_variable_warning (it1_begin);
            ignore_unused_variable_warning (it2_begin);
            ignore_unused_variable_warning (it1_end);
            ignore_unused_variable_warning (it2_end);
            ignore_unused_variable_warning (rit1_begin);
            ignore_unused_variable_warning (rit2_begin);
            ignore_unused_variable_warning (rit1_end);
            ignore_unused_variable_warning (rit2_end);
        }


        void constraints () {
            function_requires< VectorExpressionConcept<vector_type> >();
            size_type n (0);
            size_type i (0);
            // Sizing constructor
            vector_type v (n);
            // Element support
            const_pointer p = v.find_element (i);

            ignore_unused_variable_warning (p);
        }


        void constraints () {
            function_requires< VectorConcept<vector_type> >();
            function_requires< DefaultConstructible<vector_type> >();
            function_requires< Mutable_VectorExpressionConcept<vector_type> >();
            size_type n (0);
            value_type t = value_type ();
            size_type i (0);
            vector_type v;
            // Element support
            pointer p = v.find_element (i);
            // Element assignment
            value_type r = v.insert_element (i, t);
            v.insert_element (i, t) = r;
            // Zeroing
            v.clear ();
            // Resize
            v.resize (n);

            ignore_unused_variable_warning (p);
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< VectorConcept<vector_type> >();
        }


        void constraints () {
            function_requires< SparseVectorConcept<vector_type> >();
            function_requires< Mutable_VectorConcept<vector_type> >();
            size_type i (0);
            vector_type v;
            // Element erasure
            v.erase_element (i);
        }


        void constraints () {
            function_requires< MatrixExpressionConcept<matrix_type> >();
            size_type n (0);
            size_type i (0), j (0);
            // Sizing constructor
            matrix_type m (n, n);
            // Element support
#ifndef SKIP_BAD
            const_pointer p = m.find_element (i, j);
#else
            const_pointer p;
            ignore_unused_variable_warning (i);
            ignore_unused_variable_warning (j);
#endif
            ignore_unused_variable_warning (p);
        }


        void constraints () {
            function_requires< MatrixConcept<matrix_type> >();
            function_requires< DefaultConstructible<matrix_type> >();
            function_requires< Mutable_MatrixExpressionConcept<matrix_type> >();
            size_type n (0);
            value_type t = value_type ();
            size_type i (0), j (0);
            matrix_type m;
            // Element support
#ifndef SKIP_BAD
            pointer p = m.find_element (i, j);
            ignore_unused_variable_warning (i);
            ignore_unused_variable_warning (j);
#else
            pointer p;
#endif
            // Element assigment
            value_type r = m.insert_element (i, j, t);
            m.insert_element (i, j, t) = r;
            // Zeroing
            m.clear ();
            // Resize
            m.resize (n, n);
            m.resize (n, n, false);

            ignore_unused_variable_warning (p);
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< MatrixConcept<matrix_type> >();
        }


        void constraints () {
            function_requires< SparseMatrixConcept<matrix_type> >();
            function_requires< Mutable_MatrixConcept<matrix_type> >();
            size_type i (0), j (0);
            matrix_type m;
            // Elemnent erasure
            m.erase_element (i, j);
        }

    template<>
    float
    OneElement (float) {
        return 1.f;
    }


        void constraints () {
            bool r;
            value_type a = value_type (), b = value_type (), c = value_type ();
            r = (a * b) * c == a * (b * c);
            r = OneElement (value_type ()) * a == a;
            r = a * OneElement (value_type ()) == a;
            r = a * (OneElement (value_type ()) / a) == a;
            r = (OneElement (value_type ()) / a) * a == a;
            r = a * b == b * a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< AdditiveAbelianGroupConcept<value_type> >();
            bool r;
            value_type a = value_type (), b = value_type (), c = value_type ();
            r = (a * b) * c == a * (b * c);
            r = (a + b) * c == a * c + b * c;
            r = OneElement (value_type ()) * a == a;
            r = a * OneElement (value_type ()) == a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< AdditiveAbelianGroupConcept<value_type> >();
            bool r;
            value_type a = value_type (), b = value_type (), c = value_type ();
            r = prod (T (prod (a, b)), c) == prod (a, T (prod (b, c)));
            r = prod (a + b, c) == prod (a, c) + prod (b, c);
            r = prod (OneElement (value_type ()), a) == a;
            r = prod (a, OneElement (value_type ())) == a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< RingWithIdentityConcept<value_type> >();
            bool r;
            value_type a = value_type (), b = value_type ();
            r = a * b == b * a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< CommutativeRingWithIdentityConcept<value_type> >();
            bool r;
            value_type a = value_type ();
            r = a == ZeroElement (value_type ()) || a * (OneElement (value_type ()) / a) == a;
            r = a == ZeroElement (value_type ()) || (OneElement (value_type ()) / a) * a == a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< FieldConcept<value_type> >();
            function_requires< AdditiveAbelianGroupConcept<vector_type> >();
            bool r;
            value_type alpha = value_type (), beta = value_type ();
            vector_type a = vector_type (), b = vector_type ();
            r = alpha * (a + b) == alpha * a + alpha * b;
            r = (alpha + beta) * a == alpha * a + beta * a;
            r = (alpha * beta) * a == alpha * (beta * a);
            r = OneElement (value_type ()) * a == a;
            ignore_unused_variable_warning (r);
        }


        void constraints () {
            function_requires< VectorSpaceConcept<value_type, vector_type> >();
            bool r;
            value_type alpha = value_type (), beta = value_type ();
            vector_type a = vector_type (), b = vector_type ();
            matrix_type A = matrix_type ();
            r = prod (A, alpha * a + beta * b) == alpha * prod (A, a) + beta * prod (A, b);
            ignore_unused_variable_warning (r);
        }


    void concept_checks () {

        // Allow tests to be group to keep down compiler storage requirement
#ifdef INTERAL
#define INTERNAL_STORAGE
#define INTERNAL_VECTOR
#define INTERNAL_MATRIX
#define INTERNAL_SPECIAL
#define INTERNAL_SPARSE
#define INTERNAL_EXPRESSION
#endif

        // TODO enable this for development
        // #define VIEW_CONCEPTS

        // Element value type for tests
        typedef float T;

        // Storage Array
#if defined (INTERNAL_STORAGE) || defined (INTERNAL_STORAGE_DENSE)
        {
            typedef std::vector<T> container_model;
            function_requires< Mutable_StorageArrayConcept<container_model> >();
            function_requires< RandomAccessIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_RandomAccessIteratorConcept<container_model::iterator> >();
        }

        {
            typedef bounded_array<T, 1> container_model;
            function_requires< Mutable_StorageArrayConcept<container_model> >();
            function_requires< RandomAccessIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_RandomAccessIteratorConcept<container_model::iterator> >();
        }

        {
            typedef unbounded_array<T> container_model;
            function_requires< Mutable_StorageArrayConcept<container_model> >();
            function_requires< RandomAccessIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_RandomAccessIteratorConcept<container_model::iterator> >();
        }

/* FIXME array_adaptors are in progress
        {
            typedef array_adaptor<T> container_model;
            function_requires< Mutable_StorageArrayConcept<container_model> >();
            function_requires< RandomAccessIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_RandomAccessIteratorConcept<container_model::iterator> >();
        }
*/

        {
            typedef range container_model;
            function_requires< IndexSetConcept<range> >();
            function_requires< RandomAccessIteratorConcept<range::const_iterator> >();
        }

        {
            typedef slice container_model;
            function_requires< IndexSetConcept<range> >();
            function_requires< RandomAccessIteratorConcept<range::const_iterator> >();
        }

        {
            typedef indirect_array<> container_model;
            function_requires< IndexSetConcept<range> >();
            function_requires< RandomAccessIteratorConcept<range::const_iterator> >();
        }
#endif

        // Storage Sparse
#if defined (INTERNAL_STORAGE) || defined (INTERNAL_STORAGE_SPARSE)
        {
           typedef map_array<std::size_t, T> container_model;
           function_requires< Mutable_StorageSparseConcept<container_model> >();
           function_requires< RandomAccessIteratorConcept<container_model::const_iterator> >();
           function_requires< RandomAccessIteratorConcept<container_model::iterator> >();
        }

        {
           typedef std::map<std::size_t, T> container_model;
           function_requires< Mutable_StorageSparseConcept<container_model > >();
           function_requires< BidirectionalIteratorConcept<container_model::const_iterator> >();
           function_requires< BidirectionalIteratorConcept<container_model::iterator> >();
        }
#endif

#ifdef VIEW_CONCEPTS
        // read only vectors
        {
           typedef vector_view<T> container_model;
           function_requires< RandomAccessContainerConcept<container_model> >();
           function_requires< VectorConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
        }
#endif

        // Vector
#if defined (INTERNAL_VECTOR) || defined (INTERNAL_VECTOR_DENSE)
        {
           typedef vector<T> container_model;
           function_requires< RandomAccessContainerConcept<container_model> >();
           function_requires< Mutable_VectorConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
           typedef zero_vector<T> container_model;
           function_requires< VectorConcept<container_model> >();
           function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_iterator> >();
           function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_reverse_iterator> >();
        }

        {
           typedef unit_vector<T> container_model;
           function_requires< VectorConcept<container_model> >();
           function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_iterator> >();
           function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_reverse_iterator> >();
        }

        {
           typedef scalar_vector<T> container_model;
           function_requires< VectorConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
        }

        {
           typedef c_vector<T, 1> container_model;
           function_requires< Mutable_VectorConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }
#endif

        // Vector Proxies
#if defined (INTERNAL_VECTOR) || defined (INTERNAL_VECTOR_PROXY)
        {
           typedef vector_range<vector<T> > container_model;
           function_requires< Mutable_VectorExpressionConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
           typedef vector_slice<vector<T> > container_model;
           function_requires< Mutable_VectorExpressionConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
           typedef vector_indirect<vector<T> > container_model;
           function_requires< Mutable_VectorExpressionConcept<container_model> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
           function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
           function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }
#endif

        // Sparse Vector
#if defined (INTERNAL_SPARSE) || defined (INTERNAL_VECTOR_SPARSE)
        {
            typedef mapped_vector<T> container_model;
            function_requires< Mutable_SparseVectorConcept<container_model> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef compressed_vector<T> container_model;
            function_requires< Mutable_SparseVectorConcept<container_model> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef coordinate_vector<T> container_model;
            function_requires< Mutable_SparseVectorConcept<container_model> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedBidirectional1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedBidirectional1DIteratorConcept<container_model::reverse_iterator> >();
        }
#endif

        // Matrix
#if defined (INTERNAL_MATRIX) || defined (INTERNAL_MATRIX_DENSE)
        {
            typedef matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef vector_of_vector<T> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef zero_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
        }

        {
            typedef identity_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
        }

        {
            typedef scalar_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
        }

        {
            typedef c_matrix<T, 1, 1> container_model;
            function_requires< Mutable_MatrixConcept<matrix<T> > >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Matrix Proxies
#if defined (INTERNAL_MATRIX) || defined (INTERNAL_MATRIX_PROXY)
        {
            typedef matrix_row<matrix<T> > container_model;
            function_requires< Mutable_VectorExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef matrix_column<matrix<T> > container_model;
            function_requires< Mutable_VectorExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef matrix_vector_range<matrix<T> > container_model;
            function_requires< Mutable_VectorExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef matrix_vector_slice<matrix<T> > container_model;
            function_requires< Mutable_VectorExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef matrix_vector_indirect<matrix<T> > container_model;
            function_requires< Mutable_VectorExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<container_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<container_model::reverse_iterator> >();
        }

        {
            typedef matrix_range<matrix<T> > container_model;
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef matrix_slice<matrix<T> > container_model;
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef matrix_indirect<matrix<T> > container_model;
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Banded Matrix
#if defined (INTERNAL_SPECIAL) || defined (INTERNAL_BANDED)
        {
            typedef banded_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef banded_adaptor<matrix<T> > container_model;
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Triangular Matrix
#if defined (INTERNAL_SPECIAL) || defined (INTERNAL_TRIANGULAR)
        {
            typedef triangular_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef triangular_adaptor<matrix<T> > container_model;
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Symmetric Matrix
#if defined (INTERNA_SPECIAL) || defined (INTERNAL_SYMMETRIC)
        {
            typedef symmetric_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

        {
            typedef banded_adaptor<matrix<T> > container_model;
#ifndef SKIP_BAD
           // const_iterator (iterator) constructor is bad
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
#endif
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Hermitian Matrix
#if defined (INTERNAL_SPECIAL) || defined (INTERNAL_HERMITIAN)
        {
            typedef hermitian_matrix<T> container_model;
            function_requires< Mutable_MatrixConcept<container_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
        
        {
            typedef hermitian_adaptor<matrix<T> > container_model;
#ifndef SKIP_BAD
           // const_iterator (iterator) constructor is bad
            function_requires< Mutable_MatrixExpressionConcept<container_model> >();
#endif
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
#endif

        // Sparse Matrix
#if defined (INTERNAL_SPARSE) || defined (INTERNAL_MATRIX_SPARSE)
        {
            typedef mapped_matrix<T> container_model;
            function_requires< Mutable_SparseMatrixConcept<container_model> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
        {
            typedef mapped_vector_of_mapped_vector<T> container_model;
            function_requires< Mutable_SparseMatrixConcept<container_model> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
        {
            typedef compressed_matrix<T> container_model;
            function_requires< Mutable_SparseMatrixConcept<container_model> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
        {
            typedef coordinate_matrix<T> container_model;
            function_requires< Mutable_SparseMatrixConcept<container_model> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }
        {
            typedef generalized_vector_of_vector<T, row_major, vector< coordinate_vector<T> > > container_model;
            function_requires< Mutable_SparseMatrixConcept<container_model> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_iterator1, container_model::const_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::iterator1, container_model::iterator2> >();
            function_requires< IndexedBidirectional2DIteratorConcept<container_model::const_reverse_iterator1, container_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedBidirectional2DIteratorConcept<container_model::reverse_iterator1, container_model::reverse_iterator2> >();
        }

#endif

        // Scalar Expressions
#if defined (INTERNAL_EXPRESSION) || defined (INTERNAL_VECTOR_EXPRESSION)
        function_requires< ScalarExpressionConcept<scalar_value<T> > >();
        function_requires< ScalarExpressionConcept<scalar_reference<T> > >();

        // Vector Expressions
        {
            typedef vector_reference<vector<T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< Mutable_VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<expression_model::iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
            function_requires< Mutable_IndexedRandomAccess1DIteratorConcept<expression_model::reverse_iterator> >();
        }

        {
            typedef vector_unary<vector<T>, scalar_identity<T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef vector_binary<vector<T>, vector<T>, scalar_plus<T, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef vector_binary_scalar1<T, vector<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef vector_binary_scalar2<vector<T>, scalar_value<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef vector_binary_scalar1<scalar_value<T>, vector<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef vector_binary_scalar2<vector<T>, scalar_value<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        function_requires< ScalarExpressionConcept<vector_scalar_unary<vector<T>, vector_sum<vector<T> > > > >();
        function_requires< ScalarExpressionConcept<vector_scalar_unary<vector<T>, vector_norm_1<vector<T> > > > >();
        function_requires< ScalarExpressionConcept<vector_scalar_unary<vector<T>, vector_norm_2<vector<T> > > > >();
        function_requires< ScalarExpressionConcept<vector_scalar_unary<vector<T>, vector_norm_inf<vector<T> > > > >();

        function_requires< ScalarExpressionConcept<vector_scalar_binary<vector<T>, vector<T>, vector_inner_prod<vector<T>, vector<T>, T> > > >();
#endif

        // Matrix Expressions
#if defined (INTERNAL_EXPRESSION) || defined (INTERNAL_MATRIX_EXPRESSION)
        {
            typedef matrix_reference<matrix<T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< Mutable_MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<expression_model::iterator1, expression_model::iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
            function_requires< Mutable_IndexedRandomAccess2DIteratorConcept<expression_model::reverse_iterator1, expression_model::reverse_iterator2> >();
        }

        {
            typedef vector_matrix_binary<vector<T>, vector<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_unary1<matrix<T>, scalar_identity<T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_unary2<matrix<T>, scalar_identity<T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_binary<matrix<T>, matrix<T>, scalar_plus<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_binary_scalar1<T, matrix<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_binary_scalar2<matrix<T>, T, scalar_multiplies<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_binary_scalar1<scalar_value<T>, matrix<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_binary_scalar2<matrix<T>, scalar_value<T>, scalar_multiplies<T, T> > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        {
            typedef matrix_vector_binary1<matrix<T>, vector<T>, matrix_vector_prod1<matrix<T>, vector<T>, T> > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef matrix_vector_binary2<vector<T>, matrix<T>, matrix_vector_prod2<matrix<T>, vector<T>, T > > expression_model;
            function_requires< VectorExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_iterator> >();
            function_requires< IndexedRandomAccess1DIteratorConcept<expression_model::const_reverse_iterator> >();
        }

        {
            typedef matrix_matrix_binary<matrix<T>, matrix<T>, matrix_matrix_prod<matrix<T>, matrix<T>, T > > expression_model;
            function_requires< MatrixExpressionConcept<expression_model> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_iterator1, expression_model::const_iterator2> >();
            function_requires< IndexedRandomAccess2DIteratorConcept<expression_model::const_reverse_iterator1, expression_model::const_reverse_iterator2> >();
        }

        function_requires< ScalarExpressionConcept<matrix_scalar_unary<matrix<T>, matrix_norm_1<vector<T> > > > >();
        function_requires< ScalarExpressionConcept<matrix_scalar_unary<matrix<T>, matrix_norm_frobenius<vector<T> > > > >();
        function_requires< ScalarExpressionConcept<matrix_scalar_unary<matrix<T>, matrix_norm_inf<vector<T> > > > >();
#endif

#ifdef EXTERNAL
        function_requires< AdditiveAbelianGroupConcept<float> >();
        function_requires< CommutativeRingWithIdentityConcept<float> >();
        function_requires< FieldConcept<float> >();
        function_requires< VectorSpaceConcept<float, vector<float> > >();
        function_requires< Prod_RingWithIdentityConcept<matrix<float> > >();
        function_requires< VectorSpaceConcept<float, matrix<float> > >();
        function_requires< LinearOperatorConcept<float, vector<float>, matrix<float> > >();

        function_requires< AdditiveAbelianGroupConcept<std::complex<float> > >();
        function_requires< CommutativeRingWithIdentityConcept<std::complex<float> > >();
        function_requires< FieldConcept<std::complex<float> > >();
        function_requires< VectorSpaceConcept<std::complex<float>, vector<std::complex<float> > > >();
        function_requires< Prod_RingWithIdentityConcept<matrix<std::complex<float> > > >();
        function_requires< VectorSpaceConcept<std::complex<float>, matrix<std::complex<float> > > >();
        function_requires< LinearOperatorConcept<std::complex<float>, vector<std::complex<float> >, matrix<std::complex<float> > > >();
#endif
    }

        static
        const_iterator begin(const vector_type & v) {
            return & (v[0]);
        }

        static
        const_iterator end(const vector_type & v) {
            return & (v[N]);
        }


        c_array_view(size_type size, array_type data) :
            size_(size), data_(data)
        {}


        ~c_array_view()
        {}

        index_type size1() const {
            return size1_;
        }

        index_type size2() const {
            return size2_;
        }

        value_type operator()(index_type i, index_type j) const {
            const_pointer p = find_element(i,j);
            if (!p) {
                return zero_;
            } else {
                return *p;
            }
        }


        const_pointer find_element (index_type i, index_type j) const {
            index_type element1 (layout_type::index_M (i, j));
            index_type element2 (layout_type::index_m (i, j));

            const array_size_type itv      = zero_based( index1_data_[element1] );
            const array_size_type itv_next = zero_based( index1_data_[element1+1] );

            const_subiterator_type it_start = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv);
            const_subiterator_type it_end = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv_next);
            const_subiterator_type it = find_index_in_row(it_start, it_end, element2) ;
            
            if (it == it_end || *it != k_based (element2))
                return 0;
            return &value_data_ [it - vector_view_traits<index_array_type>::begin(index2_data_)];
        }


        const_subiterator_type find_index_in_row(const_subiterator_type it_start
                                                 , const_subiterator_type it_end
                                                 , index_type index) const {
            return std::lower_bound( it_start
                                     , it_end
                                     , k_based (index) );
        }

        void storage_invariants () const {
            BOOST_UBLAS_CHECK (index1_data_ [layout_type::size_M (size1_, size2_)] == k_based (nnz_), external_logic ());
        }



    template<class L, std::size_t IB, class IA, class JA, class TA  >
    compressed_matrix_view<L,IB,IA,JA,TA>
    make_compressed_matrix_view(typename vector_view_traits<JA>::value_type n_rows
                                , typename vector_view_traits<JA>::value_type n_cols
                                , typename vector_view_traits<JA>::size_type nnz
                                , const IA & ia
                                , const JA & ja
                                , const TA & ta) {

        return compressed_matrix_view<L,IB,IA,JA,TA>(n_rows, n_cols, nnz, ia, ja, ta);

    }


inline std::string get_version_string( void )
{
    std::ostringstream str;
    str << "v" << version::major << "." << version::minor;
    if( version::patch_level != 0 ) str << "_" << version::patch_level;
    return str.str();
}


    implicit_euler( value_type epsilon = 1E-6 )
    : m_epsilon( epsilon ) 
    { }



    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<state_type> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i<x.size() ; ++i )
            m_pm.m_v[i] = i;

        t += dt;

        // apply first Newton step
        deriv_func( x , m_dxdt.m_v , t );

        m_b.m_v = dt * m_dxdt.m_v;

        jacobi_func( x , m_jacobi.m_v  , t );
        m_jacobi.m_v *= dt;
        m_jacobi.m_v -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

        solve( m_b.m_v , m_jacobi.m_v );

        m_x.m_v = x - m_b.m_v;

        // iterate Newton until some precision is reached
        // ToDo: maybe we should apply only one Newton step -> linear implicit one-step scheme
        while( boost::numeric::ublas::norm_2( m_b.m_v ) > m_epsilon )
        {
            deriv_func( m_x.m_v , m_dxdt.m_v , t );
            m_b.m_v = x - m_x.m_v + dt*m_dxdt.m_v;

            // simplified version, only the first Jacobian is used
            //            jacobi( m_x , m_jacobi , t );
            //            m_jacobi *= dt;
            //            m_jacobi -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

            solve( m_b.m_v , m_jacobi.m_v );

            m_x.m_v -= m_b.m_v;
        }
        x = m_x.m_v;
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_x , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_b , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_jacobi , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_pm , x , typename is_resizeable<pmatrix_type>::type() );
        return resized;
    }



    void solve( state_type &x , matrix_type &m )
    {
        int res = boost::numeric::ublas::lu_factorize( m , m_pm.m_v );
        if( res != 0 ) exit(0);
        boost::numeric::ublas::lu_substitute( m , m_pm.m_v , x );
    }

    adams_bashforth_moulton( void )
    : m_adams_bashforth() , m_adams_moulton( m_adams_bashforth.algebra() )
    { }


    adams_bashforth_moulton( const algebra_type &algebra )
    : m_adams_bashforth( algebra ) , m_adams_moulton( m_adams_bashforth.algebra() )
    { }


    order_type order( void ) const { return order_value; }


    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        m_adams_bashforth.do_step( system , x , t , dt );
        m_adams_moulton.do_step( system , x , t , dt , m_adams_bashforth.step_storage() );
    }

    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        m_adams_bashforth.do_step( system , x , t , dt );
        m_adams_moulton.do_step( system , x , t , dt , m_adams_bashforth.step_storage() );
    }


    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , const StateOut &out , time_type dt )
    {
        m_adams_bashforth.do_step( system , in , t , out , dt );
        m_adams_moulton.do_step( system , out , t , dt , m_adams_bashforth.step_storage() );
    }

    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        m_adams_bashforth.do_step( system , in , t , out , dt );
        m_adams_moulton.do_step( system , out , t , dt , m_adams_bashforth.step_storage() );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        m_adams_bashforth.adjust_size( x );
        m_adams_moulton.adjust_size( x );
    }



    template< class ExplicitStepper , class System , class StateIn >
    void initialize( ExplicitStepper explicit_stepper , System system , StateIn &x , time_type &t , time_type dt )
    {
        m_adams_bashforth.initialize( explicit_stepper , system , x , t , dt );
    }



    template< class System , class StateIn >
    void initialize( System system , StateIn &x , time_type &t , time_type dt )
    {
        m_adams_bashforth.initialize( system , x , t , dt );
    }



    rosenbrock4_controller( value_type atol = 1.0e-6 , value_type rtol = 1.0e-6 , const stepper_type &stepper = stepper_type() )
    : m_stepper( stepper ) , m_atol( atol ) , m_rtol( rtol ) ,
      m_first_step( true ) , m_err_old( 0.0 ) , m_dt_old( 0.0 ) ,
      m_last_rejected( false )
    { }



    value_type error( const state_type &x , const state_type &xold , const state_type &xerr )
    {
        BOOST_USING_STD_MAX();
        using std::abs;
        
        const size_t n = x.size();
        value_type err = 0.0 , sk = 0.0;
        for( size_t i=0 ; i<n ; ++i )
        {
            sk = m_atol + m_rtol * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( xold[i] ) , abs( x[i] ) );
            err += xerr[i] * xerr[i] / sk / sk;
        }
        return sqrt( err / value_type( n ) );
    }


    value_type last_error( void ) const
    {
        return m_err_old;
    }





    template< class System >
    boost::numeric::odeint::controlled_step_result
    try_step( System sys , state_type &x , time_type &t , time_type &dt )
    {
        m_xnew_resizer.adjust_size( x , detail::bind( &controller_type::template resize_m_xnew< state_type > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::controlled_step_result res = try_step( sys , x , t , m_xnew.m_v , dt );
        if( res == success )
        {
            boost::numeric::odeint::copy( m_xnew.m_v , x );
        }
        return res;
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_m_xerr( x );
        resize_m_xnew( x );
    }




    stepper_type& stepper( void )
    {
        return m_stepper;
    }


    const stepper_type& stepper( void ) const
    {
        return m_stepper;
    }


    template< class StateIn >
    bool resize_m_xerr( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xerr , x , typename is_resizeable<state_type>::type() );
    }


    template< class StateIn >
    bool resize_m_xnew( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xnew , x , typename is_resizeable<state_type>::type() );
    }


    default_rosenbrock_coefficients( void )
    : gamma ( static_cast< value_type >( 0.25 ) ) ,
      d1 ( static_cast< value_type >( 0.25 ) ) ,
      d2 ( static_cast< value_type >( -0.1043 ) ) ,
      d3 ( static_cast< value_type >( 0.1035 ) ) ,
      d4 ( static_cast< value_type >( 0.3620000000000023e-01 ) ) ,
      c2 ( static_cast< value_type >( 0.386 ) ) ,
      c3 ( static_cast< value_type >( 0.21 ) ) ,
      c4 ( static_cast< value_type >( 0.63 ) ) ,
      c21 ( static_cast< value_type >( -0.5668800000000000e+01 ) ) ,
      a21 ( static_cast< value_type >( 0.1544000000000000e+01 ) ) ,
      c31 ( static_cast< value_type >( -0.2430093356833875e+01 ) ) ,
      c32 ( static_cast< value_type >( -0.2063599157091915e+00 ) ) ,
      a31 ( static_cast< value_type >( 0.9466785280815826e+00 ) ) ,
      a32 ( static_cast< value_type >( 0.2557011698983284e+00 ) ) ,
      c41 ( static_cast< value_type >( -0.1073529058151375e+00 ) ) ,
      c42 ( static_cast< value_type >( -0.9594562251023355e+01 ) ) ,
      c43 ( static_cast< value_type >( -0.2047028614809616e+02 ) ) ,
      a41 ( static_cast< value_type >( 0.3314825187068521e+01 ) ) ,
      a42 ( static_cast< value_type >( 0.2896124015972201e+01 ) ) ,
      a43 ( static_cast< value_type >( 0.9986419139977817e+00 ) ) ,
      c51 ( static_cast< value_type >( 0.7496443313967647e+01 ) ) ,
      c52 ( static_cast< value_type >( -0.1024680431464352e+02 ) ) ,
      c53 ( static_cast< value_type >( -0.3399990352819905e+02 ) ) ,
      c54 ( static_cast< value_type >(  0.1170890893206160e+02 ) ) ,
      a51 ( static_cast< value_type >( 0.1221224509226641e+01 ) ) ,
      a52 ( static_cast< value_type >( 0.6019134481288629e+01 ) ) ,
      a53 ( static_cast< value_type >( 0.1253708332932087e+02 ) ) ,
      a54 ( static_cast< value_type >( -0.6878860361058950e+00 ) ) ,
      c61 ( static_cast< value_type >( 0.8083246795921522e+01 ) ) ,
      c62 ( static_cast< value_type >( -0.7981132988064893e+01 ) ) ,
      c63 ( static_cast< value_type >( -0.3152159432874371e+02 ) ) ,
      c64 ( static_cast< value_type >( 0.1631930543123136e+02 ) ) ,
      c65 ( static_cast< value_type >( -0.6058818238834054e+01 ) ) ,
      d21 ( static_cast< value_type >( 0.1012623508344586e+02 ) ) ,
      d22 ( static_cast< value_type >( -0.7487995877610167e+01 ) ) ,
      d23 ( static_cast< value_type >( -0.3480091861555747e+02 ) ) ,
      d24 ( static_cast< value_type >( -0.7992771707568823e+01 ) ) ,
      d25 ( static_cast< value_type >( 0.1025137723295662e+01 ) ) ,
      d31 ( static_cast< value_type >( -0.6762803392801253e+00 ) ) ,
      d32 ( static_cast< value_type >( 0.6087714651680015e+01 ) ) ,
      d33 ( static_cast< value_type >( 0.1643084320892478e+02 ) ) ,
      d34 ( static_cast< value_type >( 0.2476722511418386e+02 ) ) ,
      d35 ( static_cast< value_type >( -0.6594389125716872e+01 ) )
    {}


    rosenbrock4( void )
    : m_resizer() , m_x_err_resizer() ,
      m_jac() , m_pm() ,
      m_dfdt() , m_dxdt() , m_dxdtnew() ,
      m_g1() , m_g2() , m_g3() , m_g4() , m_g5() ,
      m_cont3() , m_cont4() , m_xtmp() , m_x_err() ,
      m_coef()
    { }



    order_type order() const { return stepper_order; }
 

    template< class System >
    void do_step( System system , const state_type &x , time_type t , state_type &xout , time_type dt , state_type &xerr )
    {
        // get the system and jacobi function
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        const size_t n = x.size();

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<state_type> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i<n ; ++i )
            m_pm.m_v( i ) = i;

        deriv_func( x , m_dxdt.m_v , t );
        jacobi_func( x , m_jac.m_v , t , m_dfdt.m_v );

        m_jac.m_v *= -1.0;
        m_jac.m_v += 1.0 / m_coef.gamma / dt * boost::numeric::ublas::identity_matrix< value_type >( n );
        boost::numeric::ublas::lu_factorize( m_jac.m_v , m_pm.m_v );

        for( size_t i=0 ; i<n ; ++i )
            m_g1.m_v[i] = m_dxdt.m_v[i] + dt * m_coef.d1 * m_dfdt.m_v[i];
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g1.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a21 * m_g1.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c2 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g2.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d2 * m_dfdt.m_v[i] + m_coef.c21 * m_g1.m_v[i] / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g2.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a31 * m_g1.m_v[i] + m_coef.a32 * m_g2.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c3 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g3.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d3 * m_dfdt.m_v[i] + ( m_coef.c31 * m_g1.m_v[i] + m_coef.c32 * m_g2.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g3.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a41 * m_g1.m_v[i] + m_coef.a42 * m_g2.m_v[i] + m_coef.a43 * m_g3.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c4 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g4.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d4 * m_dfdt.m_v[i] + ( m_coef.c41 * m_g1.m_v[i] + m_coef.c42 * m_g2.m_v[i] + m_coef.c43 * m_g3.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g4.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a51 * m_g1.m_v[i] + m_coef.a52 * m_g2.m_v[i] + m_coef.a53 * m_g3.m_v[i] + m_coef.a54 * m_g4.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g5.m_v[i] = m_dxdtnew.m_v[i] + ( m_coef.c51 * m_g1.m_v[i] + m_coef.c52 * m_g2.m_v[i] + m_coef.c53 * m_g3.m_v[i] + m_coef.c54 * m_g4.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g5.m_v );

        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] += m_g5.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + dt );
        for( size_t i=0 ; i<n ; ++i )
            xerr[i] = m_dxdtnew.m_v[i] + ( m_coef.c61 * m_g1.m_v[i] + m_coef.c62 * m_g2.m_v[i] + m_coef.c63 * m_g3.m_v[i] + m_coef.c64 * m_g4.m_v[i] + m_coef.c65 * m_g5.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , xerr );

        for( size_t i=0 ; i<n ; ++i )
            xout[i] = m_xtmp.m_v[i] + xerr[i];
    }


    void prepare_dense_output()
    {
        const size_t n = m_g1.m_v.size();
        for( size_t i=0 ; i<n ; ++i )
        {
            m_cont3.m_v[i] = m_coef.d21 * m_g1.m_v[i] + m_coef.d22 * m_g2.m_v[i] + m_coef.d23 * m_g3.m_v[i] + m_coef.d24 * m_g4.m_v[i] + m_coef.d25 * m_g5.m_v[i];
            m_cont4.m_v[i] = m_coef.d31 * m_g1.m_v[i] + m_coef.d32 * m_g2.m_v[i] + m_coef.d33 * m_g3.m_v[i] + m_coef.d34 * m_g4.m_v[i] + m_coef.d35 * m_g5.m_v[i];
        }
    }



    void calc_state( time_type t , state_type &x ,
            const state_type &x_old , time_type t_old ,
            const state_type &x_new , time_type t_new )
    {
        const size_t n = m_g1.m_v.size();
        time_type dt = t_new - t_old;
        time_type s = ( t - t_old ) / dt;
        time_type s1 = 1.0 - s;
        for( size_t i=0 ; i<n ; ++i )
            x[i] = x_old[i] * s1 + s * ( x_new[i] + s1 * ( m_cont3.m_v[i] + s * m_cont4.m_v[i] ) );
    }




    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
        resize_x_err( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dfdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdtnew , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_xtmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g2 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g3 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g4 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g5 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_cont3 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_cont4 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_jac , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_pm , x , typename is_resizeable<pmatrix_type>::type() );
        return resized;
    }


    template< class StateIn >
    bool resize_x_err( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_x_err , x , typename is_resizeable<state_type>::type() );
    }


    explicit_generic_rk( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c ,
            const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_rk_algorithm( a , b , c )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt )
    {
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        // actual calculation done in generic_rk.hpp
        m_rk_algorithm.do_step( stepper_base_type::m_algebra , system , in , dxdt , t , out , dt , m_x_tmp.m_v , m_F );
    }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < StageCount-1 ; ++i )
        {
            resized |= adjust_size_by_resizeability( m_F[i] , x , typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    }

    rk78_coefficients_a1( void )
            {
        (*this)[0] = static_cast< Value >( 2 )/static_cast< Value >( 27 );
            }

    rk78_coefficients_a2( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 36 );
        (*this)[1] = static_cast< Value >( 1 )/static_cast< Value >( 12 );
            }

    rk78_coefficients_a3( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 24 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 1 )/static_cast< Value >( 8 );
            }

    rk78_coefficients_a4( void )
            {
        (*this)[0] = static_cast< Value >( 5 )/static_cast< Value >( 12 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( -25 )/static_cast< Value >( 16 );
        (*this)[3] = static_cast< Value >( 25 )/static_cast< Value >( 16 );
            }

    rk78_coefficients_a5( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 20 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 1 )/static_cast< Value >( 4 );
        (*this)[4] = static_cast< Value >( 1 )/static_cast< Value >( 5 );
            }

    rk78_coefficients_a6( void )
            {
        (*this)[0] = static_cast< Value >( -25 )/static_cast< Value >( 108 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 125 )/static_cast< Value >( 108 );
        (*this)[4] = static_cast< Value >( -65 )/static_cast< Value >( 27 );
        (*this)[5] = static_cast< Value >( 125 )/static_cast< Value >( 54 );
            }

    rk78_coefficients_a7( void )
            {
        (*this)[0] = static_cast< Value >( 31 )/static_cast< Value >( 300 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 61 )/static_cast< Value >( 225 );
        (*this)[5] = static_cast< Value >( -2 )/static_cast< Value >( 9 );
        (*this)[6] = static_cast< Value >( 13 )/static_cast< Value >( 900 );
            }

    rk78_coefficients_a8( void )
            {
        (*this)[0] = static_cast< Value >( 2 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -53 )/static_cast< Value >( 6 );
        (*this)[4] = static_cast< Value >( 704 )/static_cast< Value >( 45 );
        (*this)[5] = static_cast< Value >( -107 )/static_cast< Value >( 9 );
        (*this)[6] = static_cast< Value >( 67 )/static_cast< Value >( 90 );
        (*this)[7] = static_cast< Value >( 3 );
            }

    rk78_coefficients_a9( void )
            {
        (*this)[0] = static_cast< Value >( -91 )/static_cast< Value >( 108 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 23 )/static_cast< Value >( 108 );
        (*this)[4] = static_cast< Value >( -976 )/static_cast< Value >( 135 );
        (*this)[5] = static_cast< Value >( 311 )/static_cast< Value >( 54 );
        (*this)[6] = static_cast< Value >( -19 )/static_cast< Value >( 60 );
        (*this)[7] = static_cast< Value >( 17 )/static_cast< Value >( 6 );
        (*this)[8] = static_cast< Value >( -1 )/static_cast< Value >( 12 );
            }

    rk78_coefficients_a10( void )
            {
        (*this)[0] = static_cast< Value >( 2383 )/static_cast< Value >( 4100 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -341 )/static_cast< Value >( 164 );
        (*this)[4] = static_cast< Value >( 4496 )/static_cast< Value >( 1025 );
        (*this)[5] = static_cast< Value >( -301 )/static_cast< Value >( 82 );
        (*this)[6] = static_cast< Value >( 2133 )/static_cast< Value >( 4100 );
        (*this)[7] = static_cast< Value >( 45 )/static_cast< Value >( 82 );
        (*this)[8] = static_cast< Value >( 45 )/static_cast< Value >( 164 );
        (*this)[9] = static_cast< Value >( 18 )/static_cast< Value >( 41 );
            }

    rk78_coefficients_a11( void )
            {
        (*this)[0] = static_cast< Value >( 3 )/static_cast< Value >( 205 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( -6 )/static_cast< Value >( 41 );
        (*this)[6] = static_cast< Value >( -3 )/static_cast< Value >( 205 );
        (*this)[7] = static_cast< Value >( -3 )/static_cast< Value >( 41 );
        (*this)[8] = static_cast< Value >( 3 )/static_cast< Value >( 41 );
        (*this)[9] = static_cast< Value >( 6 )/static_cast< Value >( 41 );
        (*this)[10] = static_cast< Value >( 0 );
            }

    rk78_coefficients_a12( void )
            {
        (*this)[0] = static_cast< Value >( -1777 )/static_cast< Value >( 4100 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -341 )/static_cast< Value >( 164 );
        (*this)[4] = static_cast< Value >( 4496 )/static_cast< Value >( 1025 );
        (*this)[5] = static_cast< Value >( -289 )/static_cast< Value >( 82 );
        (*this)[6] = static_cast< Value >( 2193 )/static_cast< Value >( 4100 );
        (*this)[7] = static_cast< Value >( 51 )/static_cast< Value >( 82 );
        (*this)[8] = static_cast< Value >( 33 )/static_cast< Value >( 164 );
        (*this)[9] = static_cast< Value >( 12 )/static_cast< Value >( 41 );
        (*this)[10] = static_cast< Value >( 0 );
        (*this)[11] = static_cast< Value >( 1 );
            }

    rk78_coefficients_b( void )
            {
        (*this)[0] = static_cast< Value >( 0 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( 34 )/static_cast<Value>( 105 );
        (*this)[6] = static_cast< Value >( 9 )/static_cast<Value>( 35 );
        (*this)[7] = static_cast< Value >( 9 )/static_cast<Value>( 35 );
        (*this)[8] = static_cast< Value >( 9 )/static_cast<Value>( 280 );
        (*this)[9] = static_cast< Value >( 9 )/static_cast<Value>( 280 );
        (*this)[10] = static_cast< Value >( 0 );
        (*this)[11] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[12] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
            }

    rk78_coefficients_db( void )
            {
        (*this)[0] = static_cast< Value >( 0 ) - static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( 0 );
        (*this)[6] = static_cast< Value >( 0 );
        (*this)[7] = static_cast< Value >( 0 );
        (*this)[8] = static_cast< Value >( 0 );
        (*this)[9] = static_cast< Value >( 0 );
        (*this)[10] = static_cast< Value >( 0 ) - static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[11] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[12] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
            }

    rk78_coefficients_c( void )
            {
        (*this)[0] = static_cast< Value >( 0 );
        (*this)[1] = static_cast< Value >( 2 )/static_cast< Value >( 27 );
        (*this)[2] = static_cast< Value >( 1 )/static_cast< Value >( 9 );
        (*this)[3] = static_cast< Value >( 1 )/static_cast<Value>( 6 );
        (*this)[4] = static_cast< Value >( 5 )/static_cast<Value>( 12 );
        (*this)[5] = static_cast< Value >( 1 )/static_cast<Value>( 2 );
        (*this)[6] = static_cast< Value >( 5 )/static_cast<Value>( 6 );
        (*this)[7] = static_cast< Value >( 1 )/static_cast<Value>( 6 );
        (*this)[8] = static_cast< Value >( 2 )/static_cast<Value>( 3 );
        (*this)[9] = static_cast< Value >( 1 )/static_cast<Value>( 3 );
        (*this)[10] = static_cast< Value >( 1 );
        (*this)[11] = static_cast< Value >( 0 );
        (*this)[12] = static_cast< Value >( 1 );
            }



    runge_kutta_fehlberg78( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
            boost::fusion::make_vector( rk78_coefficients_a1<Value>() , rk78_coefficients_a2<Value>() , rk78_coefficients_a3<Value>() ,
                    rk78_coefficients_a4<Value>() , rk78_coefficients_a5<Value>() , rk78_coefficients_a6<Value>() ,
                    rk78_coefficients_a7<Value>() , rk78_coefficients_a8<Value>() , rk78_coefficients_a9<Value>() ,
                    rk78_coefficients_a10<Value>() , rk78_coefficients_a11<Value>() , rk78_coefficients_a12<Value>() ) ,
            rk78_coefficients_b<Value>() , rk78_coefficients_db<Value>() , rk78_coefficients_c<Value>() , algebra )
    { }


    bulirsch_stoer(
        value_type eps_abs = 1E-6 , value_type eps_rel = 1E-6 ,
        value_type factor_x = 1.0 , value_type factor_dxdt = 1.0 )
        : m_error_checker( eps_abs , eps_rel , factor_x, factor_dxdt ) , m_midpoint() ,
          m_last_step_rejected( false ) , m_first( true ) ,
          m_interval_sequence( m_k_max+1 ) ,
          m_coeff( m_k_max+1 ) ,
          m_cost( m_k_max+1 ) ,
          m_table( m_k_max ) ,
          STEPFAC1( 0.65 ) , STEPFAC2( 0.94 ) , STEPFAC3( 0.02 ) , STEPFAC4( 4.0 ) , KFAC1( 0.8 ) , KFAC2( 0.9 )
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        /* initialize sequence of stage numbers and work */
        for( unsigned short i = 0; i < m_k_max+1; i++ )
        {
            m_interval_sequence[i] = 2 * (i+1);
            if( i == 0 )
                m_cost[i] = m_interval_sequence[i];
            else
                m_cost[i] = m_cost[i-1] + m_interval_sequence[i];
            m_coeff[i].resize(i);
            for( size_t k = 0 ; k < i ; ++k  )
            {
                const value_type r = static_cast< value_type >( m_interval_sequence[i] ) / static_cast< value_type >( m_interval_sequence[k] );
                m_coeff[i][k] = 1.0 / ( r*r - static_cast< value_type >( 1.0 ) ); // coefficients for extrapolation
            }

            // crude estimate of optimal order

            m_current_k_opt = 4;
            /* no calculation because log10 might not exist for value_type!
            const value_type logfact( -log10( max BOOST_PREVENT_MACRO_SUBSTITUTION( eps_rel , static_cast< value_type >(1.0E-12) ) ) * 0.6 + 0.5 );
            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>( 1 ) , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>( m_k_max-1 ) , logfact ));
            */
        }

    }

    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t, dt );
    }

    rk4_coefficients_a1( void )
    {
        (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
    }

    rk4_coefficients_a2( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
    }

    rk4_coefficients_a3( void )
            {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast<Value>(0);
        (*this)[2] = static_cast<Value>(1);
            }

    rk4_coefficients_b( void )
    {
        (*this)[0] = static_cast<Value>(1)/static_cast<Value>(6);
        (*this)[1] = static_cast<Value>(1)/static_cast<Value>(3);
        (*this)[2] = static_cast<Value>(1)/static_cast<Value>(3);
        (*this)[3] = static_cast<Value>(1)/static_cast<Value>(6);
    }

    rk4_coefficients_c( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[2] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[3] = static_cast<Value>(1);
    }


    runge_kutta4( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
            boost::fusion::make_vector( rk4_coefficients_a1<Value>() , rk4_coefficients_a2<Value>() , rk4_coefficients_a3<Value>() ) ,
            rk4_coefficients_b<Value>() , rk4_coefficients_c<Value>() , algebra )
    { }

    coef_a_type( void )
    {
        (*this)[0] = static_cast< Value >( 1 );
    }

    coef_b_type( void )
    {
        (*this)[0] = static_cast< Value >( 1 );
    }



    symplectic_euler( const algebra_type &algebra = algebra_type() )
    : stepper_base_type( detail::symplectic_euler_coef::coef_a_type< value_type >() ,
            detail::symplectic_euler_coef::coef_b_type< value_type >() ,
            algebra )
    { }



    modified_midpoint( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_steps( steps )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt /  static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>(2) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        stepper_base_type::m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        sys( m_x1.m_v , m_dxdt.m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            stepper_base_type::m_algebra.for_each3( m_x1.m_v , m_x0.m_v , m_dxdt.m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            th += h;
            sys( m_x1.m_v , m_dxdt.m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        stepper_base_type::m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , m_dxdt.m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }



    void set_steps( unsigned short steps )
    {   m_steps = steps; }



    unsigned short steps( void ) const
    {   return m_steps; }



    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    modified_midpoint_dense_out( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra ) , m_steps( steps )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt ,
            state_type &x_mp , deriv_table_type &derivs )
    {

        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt / static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>( 2 ) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        if( m_steps == 2 )
            // result of first step already gives approximation at the center of the interval
            boost::numeric::odeint::copy( m_x1.m_v , x_mp );

        sys( m_x1.m_v , derivs[0].m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            m_algebra.for_each3( m_x1.m_v , m_x0.m_v , derivs[i-1].m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            if( i == m_steps/2-1 )
                // save approximation at the center of the interval
                boost::numeric::odeint::copy( m_x1.m_v , x_mp );

            th += h;
            sys( m_x1.m_v , derivs[i].m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , derivs[m_steps-1].m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }



    void set_steps( unsigned short steps )
    {   m_steps = steps; }



    unsigned short steps( void ) const
    {   return m_steps; }



    template< class StateIn >
    bool resize( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        return resized;
    }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize( x );
    }
 


    euler( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        stepper_base_type::m_algebra.for_each3( out , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt ) );

    }


    template< class StateOut , class StateIn1 , class StateIn2 >
    void calc_state( StateOut &x , time_type t ,  const StateIn1 &old_state , time_type t_old , const StateIn2 &current_state , time_type t_new ) const
    {
        const time_type delta = t - t_old;
        stepper_base_type::m_algebra.for_each3( x , old_state , stepper_base_type::m_dxdt.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , delta ) );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        stepper_base_type::adjust_size( x );
    }


    adams_moulton( )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( m_algebra_instance )
    { }


    adams_moulton( algebra_type &algebra )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( algebra )
    { }


    adams_moulton& operator=( const adams_moulton &stepper )
    {
        m_dxdt = stepper.m_dxdt;
        m_resizer = stepper.m_resizer;
        m_algebra = stepper.m_algebra;
        return *this;
    }


    order_type order( void ) const { return order_value; }

    template< class System , class StateInOut , class ABBuf >
    void do_step( System system , StateInOut &in , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , in , t , in , dt , buf );
    }


    template< class System , class StateInOut , class ABBuf >
    void do_step( System system , const StateInOut &in , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , in , t , in , dt , buf );
    }

    template< class System , class StateIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v , t );
        detail::adams_moulton_call_algebra< steps , algebra_type , operations_type >()( m_algebra , in , out , m_dxdt.m_v , buf , m_coefficients , dt );
    }


    template< class System , class StateIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , time_type t , const StateOut &out , time_type dt , const ABBuf &buf )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v , t );
        detail::adams_moulton_call_algebra< steps , algebra_type , operations_type >()( m_algebra , in , out , m_dxdt.m_v , buf , m_coefficients , dt );
    }




    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }


    algebra_type& algebra()
    {   return m_algebra; }


    const algebra_type& algebra() const
    {   return m_algebra; }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }




    runge_kutta4_classic( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        // ToDo : check if size of in,dxdt,out are equal?

        static const value_type val1 = static_cast< value_type >( 1 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        typename odeint::unwrap_reference< System >::type &sys = system;

        const time_type dh = dt / static_cast< value_type >( 2 );
        const time_type th = t + dh;

        // dt * dxdt = k1
        // m_x_tmp = x + dh*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dh ) );


        // dt * m_dxt = k2
        sys( m_x_tmp.m_v , m_dxt.m_v , th );

        // m_x_tmp = x + dh*m_dxt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , m_dxt.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dh ) );


        // dt * m_dxm = k3
        sys( m_x_tmp.m_v , m_dxm.m_v , th );
        //m_x_tmp = x + dt*m_dxm
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , m_dxm.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dt ) );


        // dt * m_dxh = k4
        sys( m_x_tmp.m_v , m_dxh.m_v , t + dt );
        //x += dt/6 * ( m_dxdt + m_dxt + val2*m_dxm )
        time_type dt6 = dt / static_cast< value_type >( 6 );
        time_type dt3 = dt / static_cast< value_type >( 3 );
        stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_dxt.m_v , m_dxm.m_v , m_dxh.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt6 , dt3 , dt3 , dt6 ) );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxm , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxh , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }

    rk54_ck_coefficients_a1( void )
    {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 5 );
    }

    rk54_ck_coefficients_a2( void )
    {
        (*this)[0] = static_cast<Value>( 3 )/static_cast<Value>( 40 );
        (*this)[1] = static_cast<Value>( 9 )/static_cast<Value>( 40 );
    }

    rk54_ck_coefficients_a3( void )
    {
        (*this)[0] = static_cast<Value>( 3 )/static_cast<Value>( 10 );
        (*this)[1] = static_cast<Value>( -9 )/static_cast<Value>( 10 );
        (*this)[2] = static_cast<Value>( 6 )/static_cast<Value>( 5 );
    }

    rk54_ck_coefficients_a4( void )
    {
        (*this)[0] = static_cast<Value>( -11 )/static_cast<Value>( 54 );
        (*this)[1] = static_cast<Value>( 5 )/static_cast<Value>( 2 );
        (*this)[2] = static_cast<Value>( -70 )/static_cast<Value>( 27 );
        (*this)[3] = static_cast<Value>( 35 )/static_cast<Value>( 27 );
    }

    rk54_ck_coefficients_a5( void )
    {
        (*this)[0] = static_cast<Value>( 1631 )/static_cast<Value>( 55296 );
        (*this)[1] = static_cast<Value>( 175 )/static_cast<Value>( 512 );
        (*this)[2] = static_cast<Value>( 575 )/static_cast<Value>( 13824 );
        (*this)[3] = static_cast<Value>( 44275 )/static_cast<Value>( 110592 );
        (*this)[4] = static_cast<Value>( 253 )/static_cast<Value>( 4096 );
    }

    rk54_ck_coefficients_b( void )
    {
        (*this)[0] = static_cast<Value>( 37 )/static_cast<Value>( 378 );
        (*this)[1] = static_cast<Value>( 0 );
        (*this)[2] = static_cast<Value>( 250 )/static_cast<Value>( 621 );
        (*this)[3] = static_cast<Value>( 125 )/static_cast<Value>( 594 );
        (*this)[4] = static_cast<Value>( 0 );
        (*this)[5] = static_cast<Value>( 512 )/static_cast<Value>( 1771 );
    }

    rk54_ck_coefficients_db( void )
    {
        (*this)[0] = static_cast<Value>( 37 )/static_cast<Value>( 378 ) - static_cast<Value>( 2825 )/static_cast<Value>( 27648 );
        (*this)[1] = static_cast<Value>( 0 );
        (*this)[2] = static_cast<Value>( 250 )/static_cast<Value>( 621 ) - static_cast<Value>( 18575 )/static_cast<Value>( 48384 );
        (*this)[3] = static_cast<Value>( 125 )/static_cast<Value>( 594 ) - static_cast<Value>( 13525 )/static_cast<Value>( 55296 );
        (*this)[4] = static_cast<Value>( -277 )/static_cast<Value>( 14336 );
        (*this)[5] = static_cast<Value>( 512 )/static_cast<Value>( 1771 ) - static_cast<Value>( 1 )/static_cast<Value>( 4 );
    }

    rk54_ck_coefficients_c( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast<Value>( 1 )/static_cast<Value>( 5 );
        (*this)[2] = static_cast<Value>( 3 )/static_cast<Value>( 10 );
        (*this)[3] = static_cast<Value>( 3 )/static_cast<Value>( 5 );
        (*this)[4] = static_cast<Value>( 1 );
        (*this)[5] = static_cast<Value>( 7 )/static_cast<Value>( 8 );
    }



    runge_kutta_cash_karp54( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
        boost::fusion::make_vector( rk54_ck_coefficients_a1<Value>() ,
                                 rk54_ck_coefficients_a2<Value>() ,
                                 rk54_ck_coefficients_a3<Value>() ,
                                 rk54_ck_coefficients_a4<Value>() ,
                                 rk54_ck_coefficients_a5<Value>() ) ,
            rk54_ck_coefficients_b<Value>() , rk54_ck_coefficients_db<Value>() , rk54_ck_coefficients_c<Value>() ,
            algebra )
    { }




    bulirsch_stoer_dense_out(
        value_type eps_abs = 1E-6 , value_type eps_rel = 1E-6 ,
        value_type factor_x = 1.0 , value_type factor_dxdt = 1.0 ,
        bool control_interpolation = false )
        : m_error_checker( eps_abs , eps_rel , factor_x, factor_dxdt ) , 
          m_control_interpolation( control_interpolation) ,
          m_last_step_rejected( false ) , m_first( true ) ,
          m_current_state_x1( true ) ,
          m_error( m_k_max ) ,
          m_interval_sequence( m_k_max+1 ) ,
          m_coeff( m_k_max+1 ) ,
          m_cost( m_k_max+1 ) ,
          m_table( m_k_max ) ,
          m_mp_states( m_k_max+1 ) ,
          m_derivs( m_k_max+1 ) ,
          m_diffs( 2*m_k_max+1 ) ,
          STEPFAC1( 0.65 ) , STEPFAC2( 0.94 ) , STEPFAC3( 0.02 ) , STEPFAC4( 4.0 ) , KFAC1( 0.8 ) , KFAC2( 0.9 )
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();

        for( unsigned short i = 0; i < m_k_max+1; i++ )
        {
            /* only this specific sequence allows for dense output */
            m_interval_sequence[i] = 2 + 4*i;  // 2 6 10 14 ...
            m_derivs[i].resize( m_interval_sequence[i] );
            if( i == 0 )
                m_cost[i] = m_interval_sequence[i];
            else
                m_cost[i] = m_cost[i-1] + m_interval_sequence[i];
            m_coeff[i].resize(i);
            for( size_t k = 0 ; k < i ; ++k  )
            {
                const value_type r = static_cast< value_type >( m_interval_sequence[i] ) / static_cast< value_type >( m_interval_sequence[k] );
                m_coeff[i][k] = 1.0 / ( r*r - static_cast< value_type >( 1.0 ) ); // coefficients for extrapolation
            }
            // crude estimate of optimal order

            m_current_k_opt = 4;
            /* no calculation because log10 might not exist for value_type!
            const value_type logfact( -log10( max BOOST_PREVENT_MACRO_SUBSTITUTION( eps_rel , static_cast< value_type >( 1.0E-12 ) ) ) * 0.6 + 0.5 );
            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 1 , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>( m_k_max-1 ) , static_cast<int>( logfact ) ));
            */
        }
        int num = 1;
        for( int i = 2*(m_k_max) ; i >=0  ; i-- )
        {
            m_diffs[i].resize( num );
            num += (i+1)%2;
        }
    }


    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut >
    controlled_step_result try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , DerivOut &dxdt_new , time_type &dt )
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;
        
        static const value_type val1( 1.0 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        bool reject( true );

        time_vector h_opt( m_k_max+1 );
        inv_time_vector work( m_k_max+1 );

        m_k_final = 0;
        time_type new_h = dt;

        //std::cout << "t=" << t <<", dt=" << dt << ", k_opt=" << m_current_k_opt << ", first: " << m_first << std::endl;

        for( size_t k = 0 ; k <= m_current_k_opt+1 ; k++ )
        {
            m_midpoint.set_steps( m_interval_sequence[k] );
            if( k == 0 )
            {
                m_midpoint.do_step( sys , in , dxdt , t , out , dt , m_mp_states[k].m_v , m_derivs[k]);
            }
            else
            {
                m_midpoint.do_step( sys , in , dxdt , t , m_table[k-1].m_v , dt , m_mp_states[k].m_v , m_derivs[k] );
                extrapolate( k , m_table , m_coeff , out );
                // get error estimate
                m_algebra.for_each3( m_err.m_v , out , m_table[0].m_v ,
                                     typename operations_type::template scale_sum2< value_type , value_type >( val1 , -val1 ) );
                const value_type error = m_error_checker.error( m_algebra , in , dxdt , m_err.m_v , dt );
                h_opt[k] = calc_h_opt( dt , error , k );
                work[k] = static_cast<value_type>( m_cost[k] ) / h_opt[k];

                m_k_final = k;

                if( (k == m_current_k_opt-1) || m_first )
                { // convergence before k_opt ?
                    if( error < 1.0 )
                    {
                        //convergence
                        reject = false;
                        if( (work[k] < KFAC2*work[k-1]) || (m_current_k_opt <= 2) )
                        {
                            // leave order as is (except we were in first round)
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(k)+1 ) );
                            new_h = h_opt[k] * static_cast<value_type>( m_cost[k+1] ) / static_cast<value_type>( m_cost[k] );
                        } else {
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(k) ) );
                            new_h = h_opt[k];
                        }
                        break;
                    }
                    else if( should_reject( error , k ) && !m_first )
                    {
                        reject = true;
                        new_h = h_opt[k];
                        break;
                    }
                }
                if( k == m_current_k_opt )
                { // convergence at k_opt ?
                    if( error < 1.0 )
                    {
                        //convergence
                        reject = false;
                        if( (work[k-1] < KFAC2*work[k]) )
                        {
                            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(m_current_k_opt)-1 );
                            new_h = h_opt[m_current_k_opt];
                        }
                        else if( (work[k] < KFAC2*work[k-1]) && !m_last_step_rejected )
                        {
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , static_cast<int>(m_current_k_opt)+1 );
                            new_h = h_opt[k]*static_cast<value_type>( m_cost[m_current_k_opt] ) / static_cast<value_type>( m_cost[k] );
                        } else
                            new_h = h_opt[m_current_k_opt];
                        break;
                    }
                    else if( should_reject( error , k ) )
                    {
                        reject = true;
                        new_h = h_opt[m_current_k_opt];
                        break;
                    }
                }
                if( k == m_current_k_opt+1 )
                { // convergence at k_opt+1 ?
                    if( error < 1.0 )
                    {   //convergence
                        reject = false;
                        if( work[k-2] < KFAC2*work[k-1] )
                            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(m_current_k_opt)-1 );
                        if( (work[k] < KFAC2*work[m_current_k_opt]) && !m_last_step_rejected )
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , static_cast<int>(k) );
                        new_h = h_opt[m_current_k_opt];
                    } else
                    {
                        reject = true;
                        new_h = h_opt[m_current_k_opt];
                    }
                    break;
                }
            }
        }

        if( !reject )
        {

            //calculate dxdt for next step and dense output
            sys( out , dxdt_new , t+dt );

            //prepare dense output
            value_type error = prepare_dense_output( m_k_final , in , dxdt , out , dxdt_new , dt );

            if( error > static_cast<value_type>(10) ) // we are not as accurate for interpolation as for the steps
            {
                reject = true;
                new_h = dt * pow BOOST_PREVENT_MACRO_SUBSTITUTION( error , static_cast<value_type>(-1)/(2*m_k_final+2) );
            } else {
                t += dt;
            }
        }
        //set next stepsize
        if( !m_last_step_rejected || (new_h < dt) )
            dt = new_h;

        m_last_step_rejected = reject;
        if( reject )
            return fail;
        else
            return success;
    }


    template< class StateType >
    void initialize( const StateType &x0 , const time_type &t0 , const time_type &dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &controlled_error_bs_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::copy( x0 , get_current_state() );
        m_t = t0;
        m_dt = dt0;
        reset();
    }

        coef_a_type( void )
        {
            (*this)[0] = static_cast< Value >( 0.40518861839525227722 );
            (*this)[1] = static_cast< Value >( -0.28714404081652408900 );
            (*this)[2] = static_cast< Value >( 1 ) / static_cast< Value >( 2 ) - ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[2];
            (*this)[4] = (*this)[1];
            (*this)[5] = (*this)[0];

        }

        coef_b_type( void )
        {
            (*this)[0] = static_cast< Value >( -3 ) / static_cast< Value >( 73 );
            (*this)[1] = static_cast< Value >( 17 ) / static_cast< Value >( 59 );
            (*this)[2] = static_cast< Value >( 1 ) - static_cast< Value >( 2 ) * ( (*this)[0] + (*this)[1] );
            (*this)[3] = (*this)[1];
            (*this)[4] = (*this)[0];
            (*this)[5] = static_cast< Value >( 0 );
        }



    symplectic_rkn_sb3a_mclachlan( const algebra_type &algebra = algebra_type() )
        : stepper_base_type(
            detail::symplectic_rkn_sb3a_mclachlan::coef_a_type< value_type >() ,
            detail::symplectic_rkn_sb3a_mclachlan::coef_b_type< value_type >() ,
            algebra )
    { }



    runge_kutta_cash_karp54_classic( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }




    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        const value_type dc1 = c1 - static_cast<value_type> ( 2825 ) / static_cast<value_type>( 27648 );
        const value_type dc3 = c3 - static_cast<value_type> ( 18575 ) / static_cast<value_type>( 48384 );
        const value_type dc4 = c4 - static_cast<value_type> ( 13525 ) / static_cast<value_type>( 55296 );
        const value_type dc5 = static_cast<value_type> ( -277 ) / static_cast<value_type>( 14336 );
        const value_type dc6 = c6 - static_cast<value_type> ( 1 ) / static_cast<value_type> ( 4 );

        do_step_impl( system , in , dxdt , t , out , dt );

        //error estimate
        stepper_base_type::m_algebra.for_each6( xerr , dxdt , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 ));

    }




    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        const value_type a2 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type a3 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type a4 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 5 );
        const value_type a5 = static_cast<value_type> ( 1 );
        const value_type a6 = static_cast<value_type> ( 7 ) / static_cast<value_type> ( 8 );

        const value_type b21 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type b31 = static_cast<value_type> ( 3 ) / static_cast<value_type>( 40 );
        const value_type b32 = static_cast<value_type> ( 9 ) / static_cast<value_type>( 40 );
        const value_type b41 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type b42 = static_cast<value_type> ( -9 ) / static_cast<value_type> ( 10 );
        const value_type b43 = static_cast<value_type> ( 6 ) / static_cast<value_type> ( 5 );
        const value_type b51 = static_cast<value_type> ( -11 ) / static_cast<value_type>( 54 );
        const value_type b52 = static_cast<value_type> ( 5 ) / static_cast<value_type> ( 2 );
        const value_type b53 = static_cast<value_type> ( -70 ) / static_cast<value_type>( 27 );
        const value_type b54 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 27 );
        const value_type b61 = static_cast<value_type> ( 1631 ) / static_cast<value_type>( 55296 );
        const value_type b62 = static_cast<value_type> ( 175 ) / static_cast<value_type>( 512 );
        const value_type b63 = static_cast<value_type> ( 575 ) / static_cast<value_type>( 13824 );
        const value_type b64 = static_cast<value_type> ( 44275 ) / static_cast<value_type>( 110592 );
        const value_type b65 = static_cast<value_type> ( 253 ) / static_cast<value_type>( 4096 );

        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        //m_x1 = x + dt*b21*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

        sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
        // m_x_tmp = x + dt*b31*dxdt + dt*b32*m_x2
        stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt , m_k2.m_v ,
                typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

        sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
        // m_x_tmp = x + dt * (b41*dxdt + b42*m_x2 + b43*m_x3)
        stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v ,
                typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

        sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
        stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

        sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
        stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

        sys( m_x_tmp.m_v , m_k6.m_v , t + dt*a6 );
        stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_k3.m_v , m_k4.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c6 ));

    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_k2 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k3 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k4 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k5 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k6 , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    default_error_checker(
            value_type eps_abs = static_cast< value_type >( 1.0e-6 ) ,
            value_type eps_rel = static_cast< value_type >( 1.0e-6 ) ,
            value_type a_x = static_cast< value_type >( 1 ) ,
            value_type a_dxdt = static_cast< value_type >( 1 ) )
    : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
    { }



    template< class State , class Deriv , class Err , class Time >
    value_type error( const State &x_old , const Deriv &dxdt_old , Err &x_err , Time dt ) const
    {
        return error( algebra_type() , x_old , dxdt_old , x_err , dt );
    }


    template< class State , class Deriv , class Err , class Time >
    value_type error( algebra_type &algebra , const State &x_old , const Deriv &dxdt_old , Err &x_err , Time dt ) const
    {
        // this overwrites x_err !
        algebra.for_each3( x_err , x_old , dxdt_old ,
                typename operations_type::template rel_error< value_type >( m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt * get_unit_value( dt ) ) );

        value_type res = algebra.reduce( x_err ,
                typename operations_type::template maximum< value_type >() , static_cast< value_type >( 0 ) );
        return res;
    }


    rosenbrock4_dense_output( const controlled_stepper_type &stepper = controlled_stepper_type() )
    : m_stepper( stepper ) ,
      m_x1() , m_x2() , 
      m_current_state_x1( true ) ,
      m_t() , m_t_old() , m_dt()
    {
    }




    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &dense_output_stepper_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        get_current_state() = x0;
        m_t = t0;
        m_dt = dt0;
    }

    explicit_error_generic_rk( const coef_a_type &a ,
            const coef_b_type &b ,
            const coef_b_type &b2 ,
            const coef_c_type &c ,
            const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_rk_algorithm( a , b , c ) , m_b2( b2 )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        // normal step
        do_step_impl( system , in , dxdt , t , out , dt );

        // additionally, perform the error calculation
        detail::template generic_rk_call_algebra< StageCount , algebra_type >()( stepper_base_type::m_algebra ,
                xerr , dxdt , m_F , detail::generic_rk_scale_sum_err< StageCount , operations_type , value_type , time_type >( m_b2 , dt) );
    }



    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt )
    {
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        // actual calculation done in generic_rk.hpp
        m_rk_algorithm.do_step( stepper_base_type::m_algebra , system , in , dxdt , t , out , dt , m_x_tmp.m_v , m_F );
    }



    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < StageCount-1 ; ++i )
        {
            resized |= adjust_size_by_resizeability( m_F[i] , x , typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    }

        coef_a_type( void )
        {
            using std::sqrt;

            Value z = sqrt( static_cast< Value >( 7 ) / static_cast< Value >( 8 ) ) / static_cast< Value >( 3 );
            (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 ) - z ;
            (*this)[1] = static_cast< Value >( -1 ) / static_cast< Value >( 3 ) + z ;
            (*this)[2] = static_cast< Value >( 2 ) / static_cast< Value >( 3 );
            (*this)[3] = (*this)[1];
            (*this)[4] = (*this)[0];
        }

        coef_b_type( void )
        {
            (*this)[0] = static_cast< Value >( 1 );
            (*this)[1] = static_cast< Value >( -1 ) / static_cast< Value >( 2 );
            (*this)[2] = (*this)[1];
            (*this)[3] = (*this)[0];
            (*this)[4] = static_cast< Value >( 0 );
        }



    symplectic_rkn_sb3a_m4_mclachlan( const algebra_type &algebra = algebra_type() )
        : stepper_base_type(
            detail::symplectic_rkn_sb3a_m4_mclachlan::coef_a_type< value_type >() ,
            detail::symplectic_rkn_sb3a_m4_mclachlan::coef_b_type< value_type >() ,
            algebra )
    { }



    runge_kutta_dopri5( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t ,
            StateOut &out , DerivOut &dxdt_out , time_type dt )
    {
        const value_type a2 = static_cast<value_type> ( 1 ) / static_cast<value_type>( 5 );
        const value_type a3 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type a4 = static_cast<value_type> ( 4 ) / static_cast<value_type> ( 5 );
        const value_type a5 = static_cast<value_type> ( 8 )/static_cast<value_type> ( 9 );

        const value_type b21 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );

        const value_type b31 = static_cast<value_type> ( 3 ) / static_cast<value_type>( 40 );
        const value_type b32 = static_cast<value_type> ( 9 ) / static_cast<value_type>( 40 );

        const value_type b41 = static_cast<value_type> ( 44 ) / static_cast<value_type> ( 45 );
        const value_type b42 = static_cast<value_type> ( -56 ) / static_cast<value_type> ( 15 );
        const value_type b43 = static_cast<value_type> ( 32 ) / static_cast<value_type> ( 9 );

        const value_type b51 = static_cast<value_type> ( 19372 ) / static_cast<value_type>( 6561 );
        const value_type b52 = static_cast<value_type> ( -25360 ) / static_cast<value_type> ( 2187 );
        const value_type b53 = static_cast<value_type> ( 64448 ) / static_cast<value_type>( 6561 );
        const value_type b54 = static_cast<value_type> ( -212 ) / static_cast<value_type>( 729 );

        const value_type b61 = static_cast<value_type> ( 9017 ) / static_cast<value_type>( 3168 );
        const value_type b62 = static_cast<value_type> ( -355 ) / static_cast<value_type>( 33 );
        const value_type b63 = static_cast<value_type> ( 46732 ) / static_cast<value_type>( 5247 );
        const value_type b64 = static_cast<value_type> ( 49 ) / static_cast<value_type>( 176 );
        const value_type b65 = static_cast<value_type> ( -5103 ) / static_cast<value_type>( 18656 );

        const value_type c1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type c3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type c5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type c6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        m_k_x_tmp_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_k_x_tmp_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        //m_x_tmp = x + dt*b21*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt_in ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

        sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
        // m_x_tmp = x + dt*b31*dxdt + dt*b32*m_k2
        stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v ,
                typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

        sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
        // m_x_tmp = x + dt * (b41*dxdt + b42*m_k2 + b43*m_k3)
        stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v ,
                typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

        sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
        stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

        sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
        stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

        sys( m_x_tmp.m_v , m_k6.m_v , t + dt );
        stepper_base_type::m_algebra.for_each7( out , in , dxdt_in , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c5 , dt*c6 ));

        // the new derivative
        sys( out , dxdt_out , t + dt );
    }




    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t ,
            StateOut &out , DerivOut &dxdt_out , time_type dt , Err &xerr )
    {
        const value_type c1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type c3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type c5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type c6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        const value_type dc1 = c1 - static_cast<value_type> ( 5179 ) / static_cast<value_type>( 57600 );
        const value_type dc3 = c3 - static_cast<value_type> ( 7571 ) / static_cast<value_type>( 16695 );
        const value_type dc4 = c4 - static_cast<value_type> ( 393 ) / static_cast<value_type>( 640 );
        const value_type dc5 = c5 - static_cast<value_type> ( -92097 ) / static_cast<value_type>( 339200 );
        const value_type dc6 = c6 - static_cast<value_type> ( 187 ) / static_cast<value_type>( 2100 );
        const value_type dc7 = static_cast<value_type>( -1 ) / static_cast<value_type> ( 40 );

        /* ToDo: copy only if &dxdt_in == &dxdt_out ? */
        if( same_instance( dxdt_in , dxdt_out ) )
        {
            m_dxdt_tmp_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_dxdt_tmp_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
            boost::numeric::odeint::copy( dxdt_in , m_dxdt_tmp.m_v );
            do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt );
            //error estimate
            stepper_base_type::m_algebra.for_each7( xerr , m_dxdt_tmp.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , dxdt_out ,
                                                    typename operations_type::template scale_sum6< time_type , time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 , dt*dc7 ) );

        }
        else
        {
            do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt );
            //error estimate
            stepper_base_type::m_algebra.for_each7( xerr , dxdt_in , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , dxdt_out ,
                                                    typename operations_type::template scale_sum6< time_type , time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 , dt*dc7 ) );
        
        }

    }

    template< class StateOut , class StateIn1 , class DerivIn1 , class StateIn2 , class DerivIn2 >
    void calc_state( time_type t , StateOut &x ,
                     const StateIn1 &x_old , const DerivIn1 &deriv_old , time_type t_old ,
                     const StateIn2 & /* x_new */ , const DerivIn2 &deriv_new , time_type t_new ) const
    {
        const value_type b1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type b3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type b4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type b5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type b6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        const time_type dt = ( t_new - t_old );
        const value_type theta = ( t - t_old ) / dt;
        const value_type X1 = static_cast< value_type >( 5 ) * ( static_cast< value_type >( 2558722523LL ) - static_cast< value_type >( 31403016 ) * theta ) / static_cast< value_type >( 11282082432LL );
        const value_type X3 = static_cast< value_type >( 100 ) * ( static_cast< value_type >( 882725551 ) - static_cast< value_type >( 15701508 ) * theta ) / static_cast< value_type >( 32700410799LL );
        const value_type X4 = static_cast< value_type >( 25 ) * ( static_cast< value_type >( 443332067 ) - static_cast< value_type >( 31403016 ) * theta ) / static_cast< value_type >( 1880347072LL ) ;
        const value_type X5 = static_cast< value_type >( 32805 ) * ( static_cast< value_type >( 23143187 ) - static_cast< value_type >( 3489224 ) * theta ) / static_cast< value_type >( 199316789632LL );
        const value_type X6 = static_cast< value_type >( 55 ) * ( static_cast< value_type >( 29972135 ) - static_cast< value_type >( 7076736 ) * theta ) / static_cast< value_type >( 822651844 );
        const value_type X7 = static_cast< value_type >( 10 ) * ( static_cast< value_type >( 7414447 ) - static_cast< value_type >( 829305 ) * theta ) / static_cast< value_type >( 29380423 );

        const value_type theta_m_1 = theta - static_cast< value_type >( 1 );
        const value_type theta_sq = theta * theta;
        const value_type A = theta_sq * ( static_cast< value_type >( 3 ) - static_cast< value_type >( 2 ) * theta );
        const value_type B = theta_sq * theta_m_1;
        const value_type C = theta_sq * theta_m_1 * theta_m_1;
        const value_type D = theta * theta_m_1 * theta_m_1;

        const value_type b1_theta = A * b1 - C * X1 + D;
        const value_type b3_theta = A * b3 + C * X3;
        const value_type b4_theta = A * b4 - C * X4;
        const value_type b5_theta = A * b5 + C * X5;
        const value_type b6_theta = A * b6 - C * X6;
        const value_type b7_theta = B + C * X7;

        // const state_type &k1 = *m_old_deriv;
        // const state_type &k3 = dopri5().m_k3;
        // const state_type &k4 = dopri5().m_k4;
        // const state_type &k5 = dopri5().m_k5;
        // const state_type &k6 = dopri5().m_k6;
        // const state_type &k7 = *m_current_deriv;

        stepper_base_type::m_algebra.for_each8( x , x_old , deriv_old , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , deriv_new ,
                typename operations_type::template scale_sum7< value_type , time_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt * b1_theta , dt * b3_theta , dt * b4_theta , dt * b5_theta , dt * b6_theta , dt * b7_theta ) );
    }



    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_k_x_tmp_impl( x );
        resize_dxdt_tmp_impl( x );
        stepper_base_type::adjust_size( x );
    }


    template< class StateIn >
    bool resize_k_x_tmp_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_k2 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k3 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k4 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k5 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k6 , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    template< class StateIn >
    bool resize_dxdt_tmp_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt_tmp , x , typename is_resizeable<deriv_type>::type() );
    }


            do_insertion( stage_vector_base &base , const coef_a_type &a , const coef_c_type &c )
            : m_base( base ) , m_a( a ) , m_c( c ) { }


            template< class Index >
            void operator()( Index ) const
            {
                //boost::fusion::at< Index >( m_base ) = stage< double , Index::value+1 , intermediate_stage >( m_c[ Index::value ] , boost::fusion::at< Index >( m_a ) );
                boost::fusion::at< Index >( m_base ).c  = m_c[ Index::value ];
                boost::fusion::at< Index >( m_base ).a = boost::fusion::at< Index >( m_a );
            }


            print_butcher( const stage_vector_base &base , std::ostream &os )
            : m_base( base ) , m_os( os )
            { }


            template<class Index>
            void operator()(Index) const {
                m_os << boost::fusion::at<Index>(m_base).c << " | ";
                for( size_t i=0 ; i<Index::value ; ++i )
                    m_os << boost::fusion::at<Index>(m_base).a[i] << " ";
                m_os << std::endl;
            }



        stage_vector( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c )
        {
            typedef boost::mpl::range_c< size_t , 0 , StageCount-1 > indices;
            boost::mpl::for_each< indices >( do_insertion( *this , a , c ) );
            boost::fusion::at_c< StageCount - 1 >( *this ).c = c[ StageCount - 1 ];
            boost::fusion::at_c< StageCount - 1 >( *this ).a = b;
        }


        void print( std::ostream &os ) const
        {
            typedef boost::mpl::range_c< size_t , 0 , StageCount > indices;
            boost::mpl::for_each< indices >( print_butcher( *this , os ) );
        }


        calculate_stage( Algebra &_algebra , System &_system , const StateIn &_x , const DerivIn &_dxdt , StateOut &_out ,
                StateTemp &_x_tmp , Deriv *_F , Time _t , Time _dt )
        : algebra( _algebra ) , system( _system ) , x( _x ) , x_tmp( _x_tmp ) , x_out( _out) , dxdt( _dxdt ) , F( _F ) , t( _t ) , dt( _dt )
        {}



        template< typename T , size_t stage_number >
        void inline operator()( stage< T , stage_number > const &stage ) const
        //typename stage_fusion_wrapper< T , mpl::size_t< stage_number > , intermediate_stage >::type const &stage ) const
        {
            if( stage_number > 1 )
            {
#ifdef BOOST_MSVC
#pragma warning( disable : 4307 34 )
#endif
                system( x_tmp , F[stage_number-2].m_v , t + stage.c * dt );
#ifdef BOOST_MSVC
#pragma warning( default : 4307 34 )
#endif
            }
            //std::cout << stage_number-2 << ", t': " << t + stage.c * dt << std::endl;

            if( stage_number < StageCount )
                detail::template generic_rk_call_algebra< stage_number , Algebra >()( algebra , x_tmp , x , dxdt , F ,
                        detail::generic_rk_scale_sum< stage_number , Operations , Value , Time >( stage.a , dt) );
            //                  algebra_type::template for_eachn<stage_number>( x_tmp , x , dxdt , F ,
            //                          typename operations_type::template scale_sumn< stage_number , time_type >( stage.a , dt ) );
            else
                detail::template generic_rk_call_algebra< stage_number , Algebra >()( algebra , x_out , x , dxdt , F ,
                        detail::generic_rk_scale_sum< stage_number , Operations , Value , Time >( stage.a , dt ) );
            //                algebra_type::template for_eachn<stage_number>( x_out , x , dxdt , F ,
            //                            typename operations_type::template scale_sumn< stage_number , time_type >( stage.a , dt ) );
        }


    generic_rk_algorithm( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c )
    : m_stages( a , b , c )
    { }


    template< class System , class StateIn , class DerivIn , class Time , class StateOut , class StateTemp , class Deriv >
    void inline do_step( Algebra &algebra , System system , const StateIn &in , const DerivIn &dxdt ,
            Time t , StateOut &out , Time dt ,
            StateTemp &x_tmp , Deriv F[StageCount-1] ) const
    {
        typedef typename odeint::unwrap_reference< System >::type unwrapped_system_type;
        unwrapped_system_type &sys = system;
        boost::fusion::for_each( m_stages , calculate_stage<
                unwrapped_system_type , StateIn , StateTemp , DerivIn , Deriv , StateOut , Time >
        ( algebra , sys , in , dxdt , out , x_tmp , F , t , dt ) );
    }

    generic_rk_scale_sum( const boost::array<Fac,1> &a , Time dt ) : Operations::template scale_sum2< Fac , Time >( 1.0 , a[0]*dt )
                { }

    generic_rk_scale_sum( const boost::array<Fac,2> &a , Time dt )
                    : Operations::template scale_sum3< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,3> &a , Time dt )
                    : Operations::template scale_sum4< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,4> &a , Time dt )
                    : Operations::template scale_sum5< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,5> &a , Time dt )
                    : Operations::template scale_sum6< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,6> &a , Time dt )
                    : Operations::template scale_sum7< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,7> &a , Time dt )
                    : Operations::template scale_sum8< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt , a[6]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,8> &a , Time dt )
                    : Operations::template scale_sum9< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,9> &a , Time dt )
                    : Operations::template scale_sum10< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,10> &a , Time dt )
                    : Operations::template scale_sum11< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,11> &a , Time dt )
                    : Operations::template scale_sum12< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,12> &a , Time dt )
                    : Operations::template scale_sum13< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt )
                      { }

    generic_rk_scale_sum( const boost::array<Fac,13> &a , Time dt )
                    : Operations::template scale_sum14< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt , a[12]*dt  )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,1> &a , Time dt ) : Operations::template scale_sum1< Time >( a[0]*dt )
                { }

    generic_rk_scale_sum_err( const boost::array<Fac,2> &a , Time dt )
                    : Operations::template scale_sum2< Time >( a[0]*dt , a[1]*dt )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,3> &a , Time dt )
                    : Operations::template scale_sum3< Time >( a[0]*dt , a[1]*dt , a[2]*dt )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,4> &a , Time dt )
                    : Operations::template scale_sum4< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,5> &a , Time dt )
                    : Operations::template scale_sum5< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,6> &a , Time dt )
                    : Operations::template scale_sum6< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt )
                      { }

    generic_rk_scale_sum_err( const boost::array<Fac,13> &a , Time dt )
                    : Operations::template scale_sum13< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt ,
                        a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt , a[12]*dt )
                      { }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each3( out , in , steps[0].m_v , typename Operations::template scale_sum2< value_type , Time >( 1.0 , dt * coef[0] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each4( out , in , steps[0].m_v , steps[1].m_v ,
                typename Operations::template scale_sum3< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each5( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v ,
                typename Operations::template scale_sum4< value_type , Time , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each6( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v ,
                typename Operations::template scale_sum5< value_type , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each7( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v ,
                typename Operations::template scale_sum6< value_type , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each8( out , in , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v ,
                typename Operations::template scale_sum7< value_type , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        BOOST_ASSERT( false ); // not implemented
        // typedef typename Coefficients::value_type value_type;
        // Algebra::for_each9( out , in , steps[0] , steps[1] , steps[2] , steps[3] , steps[4] , steps[5] , steps[6]
        //                     typename Operations::template scale_sum8< value_type , Time , Time , Time , Time , Time , Time >(
        //                         1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] ) );
    }

    template< class StateIn , class StateOut , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        BOOST_ASSERT( false ); // not implemented
        // typedef typename Coefficients::value_type value_type;
        // Algebra::for_each10( out , in , steps[0] , steps[1] , steps[2] , steps[3] , steps[4] , steps[5] , steps[6] , steps[7] ,
        //                      typename Operations::template scale_sum9< value_type , Time , Time , Time , Time , Time , Time , Time >(
        //                          1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] , dt * coef[7] ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( algebra_type &algebra , S1 &s1 , S2 &s2 ,  S3 &s3 , S4 * /* s4_array */ , Op op ) const
    {
        algebra.for_each3( s1 , s2 , s3 , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( algebra_type &algebra , S1 &s1 , S2 &s2 , S4 * /* s4_array */ , Op op ) const
    {
        algebra.for_each2( s1 , s2 , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 ,  S3 &s3 , S4 s4_array[1] , Op op ) const
    {
        algebra.for_each4( s1 , s2 , s3 , s4_array[0].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[1] , Op op ) const
    {
        algebra.for_each3( s1 , s2 , s4_array[0].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[2] , Op op ) const
    {
        algebra.for_each5( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[2] , Op op ) const
    {
        algebra.for_each4( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[3] , Op op ) const
    {
        algebra.for_each6( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[3] , Op op ) const
    {
        algebra.for_each5( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[4] , Op op ) const
    {
        algebra.for_each7( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[4] , Op op ) const
    {
        algebra.for_each6( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[5] , Op op ) const
    {
        algebra.for_each8( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[5] , Op op ) const
    {
        algebra.for_each7( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[6] , Op op ) const
    {
        algebra.for_each9( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[6] , Op op ) const
    {
        algebra.for_each8( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[7] , Op op ) const
    {
        algebra.for_each10( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[7] , Op op ) const
    {
        algebra.for_each9( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[8] , Op op ) const
    {
        algebra.for_each11( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[8] , Op op ) const
    {
        algebra.for_each10( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[9] , Op op ) const
    {
        algebra.for_each12( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[9] , Op op ) const
    {
        algebra.for_each11( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[10] , Op op ) const
    {
        algebra.for_each13( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[10] , Op op ) const
    {
        algebra.for_each12( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[11] , Op op ) const
    {
        algebra.for_each14( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[11] , Op op ) const
    {
        algebra.for_each13( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[12] , Op op ) const
    {
        algebra.for_each15( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , s4_array[11].m_v , op );
    }


    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[12] , Op op ) const
    {
        algebra.for_each14( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , s4_array[11].m_v , op );
    }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 1 >()
      {
        (*this)[0] = static_cast< Value >( 1 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 2 >()
      {
        (*this)[0] = static_cast< Value >( 3 ) / static_cast< Value >( 2 );
        (*this)[1] = -static_cast< Value >( 1 ) / static_cast< Value >( 2 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 3 >()
      {
        (*this)[0] = static_cast< Value >( 23 ) / static_cast< Value >( 12 );
        (*this)[1] = -static_cast< Value >( 4 ) / static_cast< Value >( 3 );
        (*this)[2] = static_cast< Value >( 5 ) / static_cast< Value >( 12 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 4 >()
      {
        (*this)[0] = static_cast< Value >( 55 ) / static_cast< Value >( 24 );
        (*this)[1] = -static_cast< Value >( 59 ) / static_cast< Value >( 24 );
        (*this)[2] = static_cast< Value >( 37 ) / static_cast< Value >( 24 );
        (*this)[3] = -static_cast< Value >( 3 ) / static_cast< Value >( 8 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 5 >()
      {
        (*this)[0] = static_cast< Value >( 1901 ) / static_cast< Value >( 720 );
        (*this)[1] = -static_cast< Value >( 1387 ) / static_cast< Value >( 360 );
        (*this)[2] = static_cast< Value >( 109 ) / static_cast< Value >( 30 );
        (*this)[3] = -static_cast< Value >( 637 ) / static_cast< Value >( 360 );
        (*this)[4] = static_cast< Value >( 251 ) / static_cast< Value >( 720 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 6 >()
      {
        (*this)[0] = static_cast< Value >( 4277 ) / static_cast< Value >( 1440 );
        (*this)[1] = -static_cast< Value >( 2641 ) / static_cast< Value >( 480 );
        (*this)[2] = static_cast< Value >( 4991 ) / static_cast< Value >( 720 );
        (*this)[3] = -static_cast< Value >( 3649 ) / static_cast< Value >( 720 );
        (*this)[4] = static_cast< Value >( 959 ) / static_cast< Value >( 480 );
        (*this)[5] = -static_cast< Value >( 95 ) / static_cast< Value >( 288 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 7 >()
      {
        (*this)[0] = static_cast< Value >( 198721 ) / static_cast< Value >( 60480 );
        (*this)[1] = -static_cast< Value >( 18637 ) / static_cast< Value >( 2520 );
        (*this)[2] = static_cast< Value >( 235183 ) / static_cast< Value >( 20160 );
        (*this)[3] = -static_cast< Value >( 10754 ) / static_cast< Value >( 945 );
        (*this)[4] = static_cast< Value >( 135713 ) / static_cast< Value >( 20160 );
        (*this)[5] = -static_cast< Value >( 5603 ) / static_cast< Value >( 2520 );
        (*this)[6] = static_cast< Value >( 19087 ) / static_cast< Value >( 60480 );
      }

    adams_bashforth_coefficients( void )
    : boost::array< Value , 8 >()
      {
        (*this)[0] = static_cast< Value >( 16083 ) / static_cast< Value >( 4480 );
        (*this)[1] = -static_cast< Value >( 1152169 ) / static_cast< Value >( 120960 );
        (*this)[2] = static_cast< Value >( 242653 ) / static_cast< Value >( 13440 );
        (*this)[3] = -static_cast< Value >( 296053 ) / static_cast< Value >( 13440 );
        (*this)[4] = static_cast< Value >( 2102243 ) / static_cast< Value >( 120960 );
        (*this)[5] = -static_cast< Value >( 115747 ) / static_cast< Value >( 13440 );
        (*this)[6] = static_cast< Value >( 32863 ) / static_cast< Value >( 13440 );
        (*this)[7] = -static_cast< Value >( 5257 ) / static_cast< Value >( 17280 );
      }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each3( out , in , dxdt , typename Operations::template scale_sum2< value_type , Time >( 1.0 , dt * coef[0] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each4( out , in , dxdt , steps[0].m_v ,
                typename Operations::template scale_sum3< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each5( out , in , dxdt , steps[0].m_v , steps[1].m_v ,
                typename Operations::template scale_sum4< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each6( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v ,
                typename Operations::template scale_sum5< value_type , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each7( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v ,
                typename Operations::template scale_sum6< value_type , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each8( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v ,
                typename Operations::template scale_sum7< value_type , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] ) );
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        BOOST_ASSERT( false ); // not implemented
    }

    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        BOOST_ASSERT( false ); // not implemented
    }

    adams_moulton_coefficients( void )
    : boost::array< Value , 1 >()
      {
        (*this)[0] = static_cast< Value >( 1 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 2 >()
      {
        (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 3 >()
      {
        (*this)[0] = static_cast< Value >( 5 ) / static_cast< Value >( 12 );
        (*this)[1] = static_cast< Value >( 2 ) / static_cast< Value >( 3 );
        (*this)[2] = -static_cast< Value >( 1 ) / static_cast< Value >( 12 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 4 >()
      {
        (*this)[0] = static_cast< Value >( 3 ) / static_cast< Value >( 8 );
        (*this)[1] = static_cast< Value >( 19 ) / static_cast< Value >( 24 );
        (*this)[2] = -static_cast< Value >( 5 ) / static_cast< Value >( 24 );
        (*this)[3] = static_cast< Value >( 1 ) / static_cast< Value >( 24 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 5 >()
      {
        (*this)[0] = static_cast< Value >( 251 ) / static_cast< Value >( 720 );
        (*this)[1] = static_cast< Value >( 323 ) / static_cast< Value >( 360 );
        (*this)[2] = -static_cast< Value >( 11 ) / static_cast< Value >( 30 );
        (*this)[3] = static_cast< Value >( 53 ) / static_cast< Value >( 360 );
        (*this)[4] = -static_cast< Value >( 19 ) / static_cast< Value >( 720 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 6 >()
      {
        (*this)[0] = static_cast< Value >( 95 ) / static_cast< Value >( 288 );
        (*this)[1] = static_cast< Value >( 1427 ) / static_cast< Value >( 1440 );
        (*this)[2] = -static_cast< Value >( 133 ) / static_cast< Value >( 240 );
        (*this)[3] = static_cast< Value >( 241 ) / static_cast< Value >( 720 );
        (*this)[4] = -static_cast< Value >( 173 ) / static_cast< Value >( 1440 );
        (*this)[5] = static_cast< Value >( 3 ) / static_cast< Value >( 160 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 7 >()
      {
        (*this)[0] = static_cast< Value >( 19087 ) / static_cast< Value >( 60480 );
        (*this)[1] = static_cast< Value >( 2713 ) / static_cast< Value >( 2520 );
        (*this)[2] = -static_cast< Value >( 15487 ) / static_cast< Value >( 20160 );
        (*this)[3] = static_cast< Value >( 586 ) / static_cast< Value >( 945 );
        (*this)[4] = -static_cast< Value >( 6737 ) / static_cast< Value >( 20160 );
        (*this)[5] = static_cast< Value >( 263 ) / static_cast< Value >( 2520 );
        (*this)[6] = -static_cast< Value >( 863 ) / static_cast< Value >( 60480 );
      }

    adams_moulton_coefficients( void )
    : boost::array< Value , 8 >()
      {
        (*this)[0] = static_cast< Value >( 5257 ) / static_cast< Value >( 17280 );
        (*this)[1] = static_cast< Value >( 139849 ) / static_cast< Value >( 120960 );
        (*this)[2] = -static_cast< Value >( 4511 ) / static_cast< Value >( 4480 );
        (*this)[3] = static_cast< Value >( 123133 ) / static_cast< Value >( 120960 );
        (*this)[4] = -static_cast< Value >( 88547 ) / static_cast< Value >( 120960 );
        (*this)[5] = static_cast< Value >( 1537 ) / static_cast< Value >( 4480 );
        (*this)[6] = -static_cast< Value >( 11351 ) / static_cast< Value >( 120960 );
        (*this)[7] = static_cast< Value >( 275 ) / static_cast< Value >( 24192 );
      }


    rotating_buffer( void ) : m_first( 0 )
    { }


    size_t size( void ) const
    {
        return dim;
    }


    value_type& operator[]( size_t i )
    {
        return m_data[ get_index( i ) ];
    }


    void rotate( void )
    {
        if( m_first == 0 )
            m_first = dim-1;
        else
            --m_first;
    }


    size_t get_index( size_t i ) const
    {
        return ( ( i + m_first ) % dim );
    }

    Controller operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            const Stepper &stepper )
    {
        return Controller( abs_error , rel_error , stepper );
    }



template< class Stepper >
typename result_of::make_controlled< Stepper >::type make_controlled(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        const Stepper & stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_controlled< stepper_type >::type controller_type;
    typedef controller_factory< stepper_type , controller_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , stepper );
}

    DenseOutput operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            const Stepper &stepper )
    {
        return DenseOutput( abs_error , rel_error , stepper );
    }




template< class Stepper >
typename result_of::make_dense_output< Stepper >::type make_dense_output(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        const Stepper &stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_dense_output< stepper_type >::type dense_output_type;
    typedef dense_output_factory< stepper_type , dense_output_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , stepper );
}


    algebra_stepper_base( const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra ) { }


    algebra_type& algebra()
    {
        return m_algebra;
    }


    const algebra_type& algebra() const
    {
        return m_algebra;
    }



    explicit_error_stepper_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra )
    { }


    order_type order( void ) const
    {
        return order_value;
    }


    order_type stepper_order( void ) const
    {
        return stepper_order_value;
    }


    order_type error_order( void ) const
    {
        return error_order_value;
    }

    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }



    explicit_stepper_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra )
    { }

    order_type order( void ) const
    {
        return order_value;
    }

    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }


    symplectic_nystroem_stepper_base( const coef_type &coef_a , const coef_type &coef_b , const algebra_type &algebra = algebra_type() )
        : algebra_stepper_base_type( algebra ) , m_coef_a( coef_a ) , m_coef_b( coef_b ) ,
          m_dqdt_resizer() , m_dpdt_resizer() , m_dqdt() , m_dpdt() 
    { }



    order_type order( void ) const
    {
        return order_value;
    }

    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &state , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , state , t , state , dt , typename is_pair< system_type >::type() );
    }

    template< class System , class StateInOut >
    void do_step( System system , StateInOut &state , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , state , t , state , dt , typename is_pair< system_type >::type() );
    }

    template< class System , class CoorInOut , class MomentumInOut >
    void do_step( System system , CoorInOut &q , MomentumInOut &p , time_type t , time_type dt )
    {
        do_step( system , std::make_pair( detail::ref( q ) , detail::ref( p ) ) , t , dt );
    }

    template< class System , class CoorInOut , class MomentumInOut >
    void do_step( System system , const CoorInOut &q , const MomentumInOut &p , time_type t , time_type dt )
    {
        do_step( system , std::make_pair( detail::ref( q ) , detail::ref( p ) ) , t , dt );
    }

    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        do_step_impl( system , in , t , out , dt , typename is_pair< system_type >::type() );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_dqdt( x );
        resize_dpdt( x );
    }

    const coef_type& coef_a( void ) const { return m_coef_a; }

    const coef_type& coef_b( void ) const { return m_coef_b; }

    template< class System , class StateIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , boost::mpl::true_ )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type coor_deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type momentum_deriv_func_type;
        system_type &sys = system;
        coor_deriv_func_type &coor_func = sys.first;
        momentum_deriv_func_type &momentum_func = sys.second;

        typedef typename odeint::unwrap_reference< StateIn >::type state_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::first_type >::type coor_in_type;
        typedef typename odeint::unwrap_reference< typename state_in_type::second_type >::type momentum_in_type;
        const state_in_type &state_in = in;
        const coor_in_type &coor_in = state_in.first;
        const momentum_in_type &momentum_in = state_in.second;

        typedef typename odeint::unwrap_reference< StateOut >::type state_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::first_type >::type coor_out_type;
        typedef typename odeint::unwrap_reference< typename state_out_type::second_type >::type momentum_out_type;
        state_out_type &state_out = out;
        coor_out_type &coor_out = state_out.first;
        momentum_out_type &momentum_out = state_out.second;

        m_dqdt_resizer.adjust_size( coor_in , detail::bind( &internal_stepper_base_type::template resize_dqdt< coor_in_type > , detail::ref( *this ) , detail::_1 ) );
        m_dpdt_resizer.adjust_size( momentum_in , detail::bind( &internal_stepper_base_type::template resize_dpdt< momentum_in_type > , detail::ref( *this ) , detail::_1 ) );

        // ToDo: check sizes?

        for( size_t l=0 ; l<num_of_stages ; ++l )
        {
            if( l == 0 )
            {
                coor_func( momentum_in , m_dqdt.m_v );
                this->m_algebra.for_each3( coor_out , coor_in , m_dqdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[l] * dt ) );
                momentum_func( coor_out , m_dpdt.m_v );
                this->m_algebra.for_each3( momentum_out , momentum_in , m_dpdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[l] * dt ) );
            }
            else
            {
                coor_func( momentum_out , m_dqdt.m_v );
                this->m_algebra.for_each3( coor_out , coor_out , m_dqdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_a[l] * dt ) );
                momentum_func( coor_out , m_dpdt.m_v );
                this->m_algebra.for_each3( momentum_out , momentum_out , m_dpdt.m_v ,
                        typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , m_coef_b[l] * dt ) );
            }
        }
    }


    template< class StateIn >
    bool resize_dqdt( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dqdt , x , typename is_resizeable<coor_deriv_type>::type() );
    }


    template< class StateIn >
    bool resize_dpdt( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dpdt , x , typename is_resizeable<momentum_deriv_type>::type() );
    }


    explicit_error_stepper_fsal_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra ) , m_first_call( true )
    { }


    order_type order( void ) const
    {
        return order_value;
    }


    order_type stepper_order( void ) const
    {
        return stepper_order_value;
    }


    order_type error_order( void ) const
    {
        return error_order_value;
    }

    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }


    gsl_vector_iterator( void ): m_p(0) , m_stride( 0 ) { }


    void increment( void ) { m_p += m_stride; }

    void decrement( void ) { m_p -= m_stride; }

    void advance( ptrdiff_t n ) { m_p += n*m_stride; }

    bool equal( const gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }

    double& dereference( void ) const { return *m_p; }


    const_gsl_vector_iterator( void ): m_p(0) , m_stride( 0 ) { }

    const_gsl_vector_iterator( const gsl_vector_iterator &p ) : m_p( p.m_p ) , m_stride( p.m_stride ) { }


    void increment( void ) { m_p += m_stride; }

    void decrement( void ) { m_p -= m_stride; }

    void advance( ptrdiff_t n ) { m_p += n*m_stride; }

    bool equal( const const_gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }

    bool equal( const gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }

    const double& dereference( void ) const { return *m_p; }



bool gsl_vector_iterator::equal( const const_gsl_vector_iterator &other ) const { return this->m_p == other.m_p; }

inline gsl_vector_iterator range_begin( gsl_vector *x )
{
    return gsl_vector_iterator( x );
}

inline gsl_vector_iterator range_end( gsl_vector *x )
{
    return end_iterator( x );
}

    static bool same_size( const gsl_vector* x , const gsl_vector* y )
    {
        return x->size == y->size;
    }

    static void resize( gsl_vector* x , const gsl_vector* y )
    {
        gsl_vector_free( x );
        x = gsl_vector_alloc( y->size );
    }


    state_wrapper( )
    {
        m_v = gsl_vector_alloc( 1 );
    }



    ~state_wrapper()
    {
        gsl_vector_free( m_v );
    }


        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }


        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }
            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
        }


        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }


        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }
            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
        }


        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }

            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha4 , &(t5[0]) , 1 , &(t1[0]) , 1 );
        }


        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 , const Fac5 alpha5 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6   >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            //boost::numeric::odeint::copy( t1 , t3 );
            if( &(t2[0]) != &(t1[0]) )
            {
                cblas_dcopy( n , &(t2[0]) , 1 , &(t1[0]) , 1 );
            }

            cblas_dscal( n , m_alpha1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha2 , &(t3[0]) , 1 , &(t1[0]) , 1 );
            //daxpby( &n , &m_alpha2 , &(t3[0]) , &one , &m_alpha1 , &(t1[0]) , &one );
            cblas_daxpy( n , m_alpha3 , &(t4[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha4 , &(t5[0]) , 1 , &(t1[0]) , 1 );
            cblas_daxpy( n , m_alpha5 , &(t6[0]) , 1 , &(t1[0]) , 1 );
        }


        scale_sum2( Fac1 alpha1 , Fac2 alpha2 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 )
        { }


        template< class T1 , class T2 , class T3 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::cpu_symbolic_scalar<3, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<4, Fac2> sym_a2;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                    );

            ocl::enqueue( op(v1,
                        const_cast< viennacl::vector<T2>& >(v2),
                        const_cast< viennacl::vector<T3>& >(v3),
                        const_cast< Fac1& >(m_alpha1),
                        const_cast< Fac2& >(m_alpha2)
                        ) );
        }


        scale_sum3( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 )
        { }


        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::symbolic_vector    <3, T4>   sym_v4;
            static generator::cpu_symbolic_scalar<4, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<5, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar<6, Fac3> sym_a3;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4
                    );

            ocl::enqueue( op(v1,
                        const_cast< viennacl::vector<T2>& >(v2),
                        const_cast< viennacl::vector<T3>& >(v3),
                        const_cast< viennacl::vector<T4>& >(v4),
                        const_cast< Fac1& >(m_alpha1),
                        const_cast< Fac2& >(m_alpha2),
                        const_cast< Fac3& >(m_alpha3)
                        ) );
        }


        scale_sum4( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4 ,
                const viennacl::vector<T5> &v5
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    <0, T1>   sym_v1;
            static generator::symbolic_vector    <1, T2>   sym_v2;
            static generator::symbolic_vector    <2, T3>   sym_v3;
            static generator::symbolic_vector    <3, T4>   sym_v4;
            static generator::symbolic_vector    <4, T5>   sym_v5;
            static generator::cpu_symbolic_scalar<5, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar<6, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar<7, Fac3> sym_a3;
            static generator::cpu_symbolic_scalar<8, Fac4> sym_a4;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4
                           + sym_a4 * sym_v5
                    );

            ocl::enqueue( op(v1,
                        const_cast< viennacl::vector<T2>& >(v2),
                        const_cast< viennacl::vector<T3>& >(v3),
                        const_cast< viennacl::vector<T4>& >(v4),
                        const_cast< viennacl::vector<T5>& >(v5),
                        const_cast< Fac1& >(m_alpha1),
                        const_cast< Fac2& >(m_alpha2),
                        const_cast< Fac3& >(m_alpha3),
                        const_cast< Fac4& >(m_alpha4)
                        ) );
        }


        scale_sum5( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
        void operator()( viennacl::vector<T1> &v1 ,
                const viennacl::vector<T2> &v2 ,
                const viennacl::vector<T3> &v3 ,
                const viennacl::vector<T4> &v4 ,
                const viennacl::vector<T5> &v5 ,
                const viennacl::vector<T6> &v6
                ) const
        {
            using namespace viennacl;

            static generator::symbolic_vector    < 0, T1>   sym_v1;
            static generator::symbolic_vector    < 1, T2>   sym_v2;
            static generator::symbolic_vector    < 2, T3>   sym_v3;
            static generator::symbolic_vector    < 3, T4>   sym_v4;
            static generator::symbolic_vector    < 4, T5>   sym_v5;
            static generator::symbolic_vector    < 5, T6>   sym_v6;
            static generator::cpu_symbolic_scalar< 6, Fac1> sym_a1;
            static generator::cpu_symbolic_scalar< 7, Fac2> sym_a2;
            static generator::cpu_symbolic_scalar< 8, Fac3> sym_a3;
            static generator::cpu_symbolic_scalar< 9, Fac4> sym_a4;
            static generator::cpu_symbolic_scalar<10, Fac5> sym_a5;

            static generator::custom_operation op(
                    sym_v1 = sym_a1 * sym_v2
                           + sym_a2 * sym_v3
                           + sym_a3 * sym_v4
                           + sym_a4 * sym_v5
                           + sym_a5 * sym_v6
                    );

            ocl::enqueue( op(v1,
                        const_cast< viennacl::vector<T2>& >(v2),
                        const_cast< viennacl::vector<T3>& >(v3),
                        const_cast< viennacl::vector<T4>& >(v4),
                        const_cast< viennacl::vector<T5>& >(v5),
                        const_cast< viennacl::vector<T6>& >(v6),
                        const_cast< Fac1& >(m_alpha1),
                        const_cast< Fac2& >(m_alpha2),
                        const_cast< Fac3& >(m_alpha3),
                        const_cast< Fac4& >(m_alpha4),
                        const_cast< Fac5& >(m_alpha5)
                        ) );
        }


        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }


        scale_sum_swap2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }


        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }


        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ){ }


        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }


        scale_sum6( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) { }


        scale_sum7( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 , const Fac7 alpha7 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }


        rel_error( const Fac1 eps_abs , const Fac1 eps_rel , const Fac1 a_x , const Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }

    template< class StateType , class Operation >
    static void for_each1( StateType &s , Operation op )
    {
        thrust::for_each( boost::begin(s) , boost::begin(s) , op );
    }


    template< class StateType1 , class StateType2 , class Operation >
    static void for_each2( StateType1 &s1 , StateType2 &s2 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 , class Operation >
    static void for_each3( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class Operation >
    static void for_each4( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 ,class Operation >
    static void for_each5( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 , class StateType6 , class Operation >
    static void for_each6( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class Operation >
    static void for_each7( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ,
                                boost::end(s7) ) ) ,
                                op);
    }


    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class StateType8 , class Operation >
    static void for_each8( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , StateType8 &s8 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ,
                        boost::begin(s8) ) ) ,
                thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                        boost::end(s2) ,
                        boost::end(s3) ,
                        boost::end(s4) ,
                        boost::end(s5) ,
                        boost::end(s6) ,
                        boost::end(s7) ,
                        boost::end(s8) ) ) ,
                op);
    }



    template< class Value , class S , class Red >
    Value reduce( const S &s , Red red , Value init)
    {
        return thrust::reduce( boost::begin( s ) , boost::end( s ) , init , red );
    }



    implicit_euler_mtl4( const value_type epsilon = 1E-6 )
        : m_epsilon( epsilon ) , m_resizer() ,
          m_dxdt() , m_x() ,
          m_identity() , m_jacobi()
    { }



    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        m_resizer.adjust_size( x , detail::bind(
                                   &stepper_type::template resize_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        m_identity.m_v = 1;

        t += dt;
        m_x.m_v = x;

        deriv_func( x , m_dxdt.m_v , t );
        jacobi_func( x , m_jacobi.m_v , t );


        m_dxdt.m_v *= -dt;

        m_jacobi.m_v *= dt;
        m_jacobi.m_v -= m_identity.m_v ;



        // using ilu_0 preconditioning -incomplete LU factorisation
        // itl::pc::diagonal<matrix_type,double> L(m_jacobi.m_v);
        itl::pc::ilu_0<matrix_type> L( m_jacobi.m_v );

        solve( m_jacobi.m_v , m_x.m_v , m_dxdt.m_v , L );
        x+= m_x.m_v;


    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }

    template < class LinearOperator, class HilbertSpaceX, class HilbertSpaceB, class Preconditioner>
    void solve(const LinearOperator& A, HilbertSpaceX& x, const HilbertSpaceB& b,
               const Preconditioner& L, int max_iteractions =500)
    {
        // Termination criterion: r < 1e-6 * b or N iterations
        itl::basic_iteration< double > iter( b , max_iteractions , 1e-6 );
        itl::bicgstab( A , x , b , L , iter );

    }



    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_x , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_identity , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_jacobi , x , typename is_resizeable<matrix_type>::type() );
        return resized;
    }

    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        detail::for_each1( boost::begin( s1 ) , boost::end( s1 ) ,
                op );
    }


    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        detail::for_each2( boost::begin( s1 ) , boost::end( s1 ) ,
                boost::begin( s2 ) , op );
    }


    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        detail::for_each3( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        detail::for_each4( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        detail::for_each5( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        detail::for_each6( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        detail::for_each7( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        detail::for_each8( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        detail::for_each9( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        detail::for_each10( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        detail::for_each11( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        detail::for_each12( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        detail::for_each13( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        detail::for_each14( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , op );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        detail::for_each15( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , boost::begin( s15 ) , op );
    }


    template< class Value , class S , class Red >
    static Value reduce( const S &s , Red red , Value init)
    {
        return detail::reduce( boost::begin( s ) , boost::end( s ) , red , init );
    }


    template< class Value , class S1 , class S2 , class Red >
    static Value reduce2( const S1 &s1 , const S2 &s2 , Red red , Value init )
    {
        return detail::reduce2( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , red , init );
    }


    template< class Value , class S1 , class S2 , class S3 , class Red >
    static Value reduce3( const S1 &s1 , const S2 &s2 , const S3 &s3 , Red red , Value init )
    {
        return detail::reduce3( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , red , init );
    }


    template< class Value , class S1 , class S2 , class S3 , class S4 , class Red >
    static Value reduce4( const S1 &s1 , const S2 &s2 , const S3 &s3 , const S4 &s4 , Red red , Value init )
    {
        return detail::reduce4( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , red , init );
    }

  template< class Op >
  double operator()( double x , Op op , double init ) const
  {
      init = op( init , x );
      return init;
  }

    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        // ToDo : build checks, that the +-*/ operators are well defined
        op( s1 );
    }


    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        op( s1 , s2 );
    }


    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        op( s1 , s2 , s3 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        op( s1 , s2 , s3 , s4 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
    }


    template< class Value , class S , class Red >
    static Value reduce( const S &s , Red red , Value init )
    {
        boost::numeric::odeint::vector_space_reduce< S > r;
        return r( s , red , init );
    }


        scale( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }


        template< class T1 >
        void operator()( T1 &t1 ) const
        {
            t1 *= m_alpha1;
        }


        scale_sum1( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }


        template< class T1 , class T2 >
        void operator()( T1 &t1 , const T2 &t2 ) const
        {
            t1 = m_alpha1 * t2;
        }


        scale_sum2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }


        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3;
        }


        scale_sum3( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }


        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
        }


        scale_sum4( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
        }


        scale_sum5( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
        }


        scale_sum6( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 , Fac6 alpha6 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ){ }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ,const T7 &t7) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7;
        }


        scale_sum7( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8;
        }


        scale_sum8( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9;
        }


        scale_sum9( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10;
        }


        scale_sum10( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 , Fac10 alpha10 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11;
        }


        scale_sum11( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12;
        }


        scale_sum12( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13;
        }


        scale_sum13( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14;
        }


        scale_sum14( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
                Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
                Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 , Fac14 alpha14 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) , m_alpha14( alpha14 ) { }


        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 , const T15 &t15 ) const
        {
            t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14 + m_alpha14 * t15;
        }


        scale_sum_swap2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }


        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , T2 &t2 , const T3 &t3) const
        {
            const T1 tmp( t1 );
            t1 = m_alpha1 * t2 + m_alpha2 * t3;
            t2 = tmp;
        }


        rel_error( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }



        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            using std::abs;
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( t1 ) ) + m_a_dxdt * abs( get_unit_value( t2 ) ) ) ) );
        }


        default_rel_error( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Fac1 x1 = abs( get_unit_value( t1 ) ) , x2 = abs( get_unit_value( t2 ) );
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( x1 , x2 ) ) );
        }

        template< class Fac1 , class Fac2 >
        Value operator()( Fac1 t1 , const Fac2 t2 ) const
        {
            using std::abs;
            Value a1 = abs( get_unit_value( t1 ) ) , a2 = abs( get_unit_value( t2 ) );
            return ( a1 < a2 ) ? a2 : a1 ;
        }


        rel_error_max( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }


        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }


        rel_error_max2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }


        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &dxdt_old , const T4 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }


        rel_error_l2( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }


        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return r + tmp * tmp;
        }


        rel_error_l2_2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }


        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &dxdt_old , const T4 &x_err )
        {
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return r + tmp * tmp;
        }

    template< typename T , size_t dim , class Op >
    static void for_each1( boost::array< T , dim > &s1 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] );
    }



    template< typename T1 , typename T2 , size_t dim , class Op >
    static void for_each2( boost::array< T1 , dim > &s1 ,
            const boost::array< T2 , dim > &s2 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each3( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each4( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each5( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each6( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each7( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each8( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each9( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each10( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each11( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 ,
            const boost::array< T , dim > &s11 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each12( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 ,
            const boost::array< T , dim > &s11 ,
            const boost::array< T , dim > &s12 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each13( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 ,
            const boost::array< T , dim > &s11 ,
            const boost::array< T , dim > &s12 ,
            const boost::array< T , dim > &s13 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each14( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 ,
            const boost::array< T , dim > &s11 ,
            const boost::array< T , dim > &s12 ,
            const boost::array< T , dim > &s13 ,
            const boost::array< T , dim > &s14 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] , s14[i] );
    }


    template< typename T , size_t dim , class Op >
    static void for_each15( boost::array< T , dim > &s1 ,
            const boost::array< T , dim > &s2 ,
            const boost::array< T , dim > &s3 ,
            const boost::array< T , dim > &s4 ,
            const boost::array< T , dim > &s5 ,
            const boost::array< T , dim > &s6 ,
            const boost::array< T , dim > &s7 ,
            const boost::array< T , dim > &s8 ,
            const boost::array< T , dim > &s9 ,
            const boost::array< T , dim > &s10 ,
            const boost::array< T , dim > &s11 ,
            const boost::array< T , dim > &s12 ,
            const boost::array< T , dim > &s13 ,
            const boost::array< T , dim > &s14 ,
            const boost::array< T , dim > &s15 , Op op )
    {
        for( size_t i=0 ; i<dim ; ++i )
            op( s1[i] , s2[i] , s3[i] , s4[i] , s5[i] , s6[i] , s7[i] , s8[i] , s9[i] , s10[i] , s11[i] , s12[i] , s13[i] , s14[i] , s15[i] );
    }



    template< class Value , class T , size_t dim , class Red >
    static Value reduce( const boost::array< T , dim > &s , Red red , Value init)
    {
        for( size_t i=0 ; i<dim ; ++i )
            init = red( init , s[i] );
        return init;
    }

    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        boost::fusion::for_each( s1 , op );
    };



    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& > Sequences;
        Sequences sequences( s1 , s2 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }



    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& > Sequences;
        Sequences sequences( s1 , s2 , s3 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }



    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }



    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }



    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }



    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 8 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 9 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 10 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 11 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 11 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 12 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 12 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 13 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 13 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 14 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 14 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& , S14& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 15 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 15 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& , S14& , S15& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class Value , class S , class Reduction >
    static Value reduce( const S &s , Reduction red , Value init)
    {
        return boost::fusion::accumulate( s , init , red );
    }



    template< class Iterator1 , class Operation >
    inline void for_each1( Iterator1 first1 , Iterator1 last1 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ );
    }



    template< class Iterator1 , class Iterator2 , class Operation >
    inline void for_each2( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ );
    }



    template< class Iterator1 , class Iterator2 , class Iterator3 , class Operation >
    inline void for_each3( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ );
    }



    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Operation >
    inline void for_each4( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3, Iterator4 first4, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ );
    }



    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Operation >
    inline void for_each5( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ );
    }



    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Operation >
    inline void for_each6( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ );
    }



    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Operation >
    inline void for_each7( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Operation >
    inline void for_each8( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Operation >
    inline void for_each9( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                           Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                           Iterator9 first9 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Operation >
    inline void for_each10( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Operation >
    inline void for_each11( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Operation >
    inline void for_each12( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Operation >
    inline void for_each13( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Operation >
    inline void for_each14( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ );
    }


    template< class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Iterator5 , class Iterator6 , class Iterator7 , class Iterator8 , class Iterator9 , class Iterator10 , class Iterator11 , class Iterator12 , class Iterator13 , class Iterator14 , class Iterator15 , class Operation >
    inline void for_each15( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3,
                            Iterator4 first4, Iterator5 first5, Iterator6 first6 , Iterator7 first7 , Iterator8 first8 ,
                            Iterator9 first9 , Iterator10 first10 , Iterator11 first11 , Iterator12 first12 , Iterator13 first13 ,
                            Iterator14 first14 , Iterator15 first15 , Operation op )
    {
        for( ; first1 != last1 ; )
            op( *first1++ , *first2++ , *first3++ , *first4++ , *first5++ , *first6++ , *first7++ , *first8++ , *first9++ , *first10++ , *first11++ , *first12++ , *first13++ , *first14++ , *first15++ );
    }


template< class ValueType , class Iterator1 , class Reduction >
inline ValueType reduce( Iterator1 first1 , Iterator1 last1 , Reduction red, ValueType init)
{
    for( ; first1 != last1 ; )
        init = red( init , *first1++ );
    return init;
}



template< class ValueType , class Iterator1 , class Iterator2 , class Reduction >
inline ValueType reduce2( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Reduction red, ValueType init)
{
    for( ; first1 != last1 ; )
        init = red( init , *first1++ , *first2++ );
    return init;
}


template< class ValueType , class Iterator1 , class Iterator2 , class Iterator3 , class Reduction >
inline ValueType reduce3( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3 , Reduction red, ValueType init)
{
    for( ; first1 != last1 ; )
        init = red( init , *first1++ , *first2++ , *first3++ );
    return init;
}


template< class ValueType , class Iterator1 , class Iterator2 , class Iterator3 , class Iterator4 , class Reduction >
inline ValueType reduce4( Iterator1 first1 , Iterator1 last1 , Iterator2 first2 , Iterator3 first3 , Iterator4 first4 , Reduction red, ValueType init)
{
    for( ; first1 != last1 ; )
        init = red( init , *first1++ , *first2++ , *first3++ , *first4++ );
    return init;
}

range_begin( const matrix< T , L , A > &x )
{
    return x.data().begin();
}


    template< class Container1 , class Container2 >
    void do_copying( const Container1 &from , Container2 &to , boost::mpl::true_ )
    {
        boost::range::copy( from , boost::begin( to ) );
    }

    static void copy( const Container1 &from , Container2 &to )
    {
        typedef typename boost::numeric::odeint::detail::is_range< Container1 >::type is_range_type;
        detail::do_copying( from , to , is_range_type() );
    }


template< class Container1 , class Container2 >
void copy( const Container1 &from , Container2 &to )
{
    copy_impl< Container1 , Container2 >::copy( from , to );
}

    static void resize( StateOut &x1 , const StateIn &x2 )
    {
        x1.resize( boost::size( x2 ) );
    }

template< class StateOut , class StateIn >
void resize( StateOut &x1 , const StateIn &x2 )
{
    resize_impl< StateOut , StateIn >::resize( x1 , x2 );
}


        template< class StateOut , class StateIn >
        void operator()( StateOut &x1 , const StateIn &x2 ) const
        {
            resize_op( x1 , x2 , typename is_resizeable< StateOut >::type() );
        }


        template< class StateOut , class StateIn >
        void resize_op( StateOut &x1 , const StateIn &x2 , boost::true_type ) const
        {
            resize( x1 , x2 );
        }

        static T value(const T &t)
        {
            return t;
        }

        static void set_value(T &t , const V &v)
        {
            t = v;
        }
 get_unit_value(const T &t)
    {
        return detail::get_unit_value_impl<T>::value(t);
    }



    template<class T , class V>

    void set_unit_value(T &t , const V &v)
    {
        return detail::set_unit_value_impl<T , V>::set_value(t , v);
    }


template< class ResizeWrappedState , class State >
bool adjust_size_by_resizeability( ResizeWrappedState &x , const State &y , boost::true_type )
{
    if ( !same_size( x.m_v , y ) )
    {
        resize( x.m_v , y );
        return true;
    }
    else
        return false;
}

    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        return f( x );
    }


    initially_resizer() : m_initialized( false )
    { }


    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        if( !m_initialized )
        {
            m_initialized = true;
            return f( x );
        } else
            return false;
    }

    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        return false;
    }
 
    static bool same_instance( const T1 &x1 , const T2 &x2 )
    {
        return false;
    }
 
    static bool same_instance( const T &x1 , const T &x2 )
    {
        // check pointers
        return (&x1 == &x2);
    }



template< class T1 , class T2 >
bool same_instance( const T1 &x1 , const T2 &x2 )
{
    return same_instance_impl< T1 , T2 >::same_instance( x1 , x2 );
}

    static bool same_size( const State1 &x1 , const State2 &x2 )
    {
        return ( boost::size( x1 ) == boost::size( x2 ) );
    }

template< class State1 , class State2 >
bool same_size( const State1 &x1 , const State2 &x2 )
{
    return same_size_impl< State1 , State2 >::same_size( x1 , x2 );
}


    template< class S1 , class S2 >
    bool operator()( const S1 &x1 , const S2 &x2 ) const
    {
        return same_size_op( x1 , x2 , typename is_resizeable< S1 >::type() );
    }


    template< class S1 , class S2 >
    bool same_size_op( const S1 &x1 , const S2 &x2 , boost::true_type ) const
    {
        return same_size( x1 , x2 );
    }

template< typename T1 , typename T2 , typename T3 >
bool less_with_sign( T1 t1 , T2 t2 , T3 dt )
{
    if( get_unit_value(dt) > 0 )
        return t1 < t2;
    else
        return t1 > t2;
}

template< typename T1 , typename T2 , typename T3>
bool less_eq_with_sign( T1 t1 , T2 t2 , T3 dt )
{
    if( get_unit_value(dt) > 0 )
        return t1 <= t2;
    else
        return t1 >= t2;
}

template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , typename Stepper::stepper_category() );
}

template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer
)
{
    // we want to get as fast as possible to the end
    if( boost::is_same< null_observer , Observer >::value )
    {
        return detail::integrate_adaptive(
                stepper , system , start_state ,
                start_time , end_time  , dt ,
                observer , typename Stepper::stepper_category() );
    }
    else
    {
        return detail::integrate_const( stepper , system , start_state , 
                                        start_time , end_time , dt ,
                                        observer , typename Stepper::stepper_category() );
      }
}

template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer )
{
    return detail::integrate_adaptive(
            stepper , system , start_state ,
            start_time , end_time , dt ,
            observer , typename Stepper::stepper_category() );

    /*
     * Suggestion for a new extendable version:
     *
     * integrator_adaptive< Stepper , System, State , Time , Observer , typename Stepper::stepper_category > integrator;
     * return integrator.run( stepper , system , start_state , start_time , end_time , dt , observer );
     */
}

template< class System , class State , class Time , class Observer >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
{
    return integrate_adaptive( controlled_runge_kutta< runge_kutta_dopri5< State > >() , system , start_state , start_time , end_time , dt , observer );
}

template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer )
{

    return detail::integrate_n_steps(
                stepper , system , start_state ,
                start_time , dt , num_of_steps ,
                observer , typename Stepper::stepper_category() );
}

    template< class State , class Time >
    void operator()( const State& /* x */ , Time /* t */ ) const
    {

    }


    void operator()( const State& x , Time t )
    {
        for( size_t i=0 ; i<m_observers.size() ; ++i )
            m_observers[i]( x , t );
    }


    collection_type& observers( void ) { return m_observers; }

template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    BOOST_USING_STD_MIN();

    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    size_t steps = 0;
    Time current_dt = dt;
    while( true )
    {
        Time current_time = *start_time++;
        obs( start_state , current_time );
        if( start_time == end_time )
            break;
        while( less_with_sign( current_time , *start_time , current_dt ) )
        {
            current_dt = min BOOST_PREVENT_MACRO_SUBSTITUTION ( dt , *start_time - current_time );
            stepper.do_step( system , start_state , current_time , current_dt );
            current_time += current_dt;
            steps++;
        }
    }
    return steps;
}



template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag 
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    
    Time time = start_time;
    int step = 0;
    
    while( less_eq_with_sign( time+dt , end_time , dt ) )
    {
        obs( start_state , time );
        stepper.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        ++step;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * dt;
    }
    obs( start_state , time );

    return step;
}

template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    size_t steps = static_cast< size_t >( (end_time-start_time)/dt );
    Time end = detail::integrate_n_steps( stepper , system , start_state , start_time ,
                                          dt , steps , observer , stepper_tag() );
    if( less_with_sign( end , end_time , dt ) )
    {   //make a last step to end exactly at end_time
        stepper.do_step( system , start_state , end , end_time - end );
        steps++;
        typename odeint::unwrap_reference< Observer >::type &obs = observer;
        obs( start_state , end_time );
    }
    return steps;
}

template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    Time time = start_time;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        stepper.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >( step+1 ) * dt;
    }
    obs( start_state , time );

    return time;
}

    template <typename Target, typename Source> 
    inline Target numeric_cast( Source arg )
    {
        typedef numeric::conversion_traits<Target, Source>   conv_traits;
        typedef numeric::numeric_cast_traits<Target, Source> cast_traits;
        typedef boost::numeric::converter
            <
                Target,
                Source, 
                conv_traits,
                typename cast_traits::overflow_policy, 
                typename cast_traits::rounding_policy, 
                boost::numeric::raw_converter< conv_traits >,
                typename cast_traits::range_checking_policy
            > converter;
        return converter::convert(arg);
    }


  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    return s < static_cast<S>(0) ? ceil(s) : floor(s) ;
  }


  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
#endif

    return floor(s) ;
  }


  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::ceil ;
#endif

    return ceil(s) ;
  }


  static source_type nearbyint ( argument_type s )
  {
    // Algorithm contributed by Guillaume Melquiond

#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    // only works inside the range not at the boundaries
    S prev = floor(s);
    S next = ceil(s);

    S rt = (s - prev) - (next - s); // remainder type

    S const zero(0.0);
    S const two(2.0);

    if ( rt < zero )
      return prev;
    else if ( rt > zero )
      return next;
    else
    {
      bool is_prev_even = two * floor(prev / two) == prev ;
      return ( is_prev_even ? prev : next ) ;
    }
  }


    virtual const char * what() const throw()
      {  return "bad numeric conversion: overflow"; }


    virtual const char * what() const throw()
      {  return "bad numeric conversion: negative overflow"; }


    virtual const char * what() const throw()
      { return "bad numeric conversion: positive overflow"; }

  void operator() ( range_check_result r ) // throw(negative_overflow,positive_overflow)
  {
#ifndef BOOST_NO_EXCEPTIONS
    if ( r == cNegOverflow )
      throw negative_overflow() ;
    else if ( r == cPosOverflow )
           throw positive_overflow() ;
#else
    if ( r == cNegOverflow )
      ::boost::throw_exception(negative_overflow()) ;
    else if ( r == cPosOverflow )
           ::boost::throw_exception(positive_overflow()) ;
#endif
  }

  void operator() ( range_check_result ) {}


  static result_type low_level_convert ( argument_type s ) { return static_cast<result_type>(s) ; }

    
      static N lowest  () { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }

      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }

      static N smallest() { return static_cast<N>(1); }

    
      static N lowest  () { return static_cast<N>(-limits::max BOOST_PREVENT_MACRO_SUBSTITUTION ()) ; }

      static N highest () { return limits::max BOOST_PREVENT_MACRO_SUBSTITUTION (); }

      static N smallest() { return limits::min BOOST_PREVENT_MACRO_SUBSTITUTION (); }

        template <class X, class Y>
        static bool check(X x, Y y_min)
            { return x < y_min; }

        template <class X, class Y>
        static bool check(X, Y)
            { return false; }

        template <class X, class Y>
        static bool check(X x, Y)
            { return x < 0; }

        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }

        template <class X, class Y>
        static inline bool check(X x, Y)
            { return x >= 0 && static_cast<X>(static_cast<Y>(x)) != x; }

        template <class X, class Y>
        static inline bool check(X x, Y y_max)
            { return x > y_max; }

        template <class X, class Y>
        static inline bool check(X x, Y)
            { return static_cast<X>(static_cast<Y>(x)) != x; }


    template<typename Target, typename Source>
    inline Target numeric_cast(Source arg BOOST_EXPLICIT_DEFAULT_TARGET)
    {
        // typedefs abbreviating respective trait classes
        typedef detail::fixed_numeric_limits<Source> arg_traits;
        typedef detail::fixed_numeric_limits<Target> result_traits;

#if defined(BOOST_STRICT_CONFIG) \
    || (!defined(__HP_aCC) || __HP_aCC > 33900) \
         && (!defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS) \
             || defined(BOOST_SGI_CPP_LIMITS))
        // typedefs that act as compile time assertions
        // (to be replaced by boost compile time assertions
        // as and when they become available and are stable)
        typedef bool argument_must_be_numeric[arg_traits::is_specialized];
        typedef bool result_must_be_numeric[result_traits::is_specialized];

        const bool arg_is_signed = arg_traits::is_signed;
        const bool result_is_signed = result_traits::is_signed;
        const bool same_sign = arg_is_signed == result_is_signed;

        if (less_than_type_min<arg_is_signed, result_is_signed>::check(arg, (result_traits::min)())
            || greater_than_type_max<same_sign, arg_is_signed>::check(arg, (result_traits::max)())
            )

#else // We need to use #pragma hacks if available

# if BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4018)
#elif defined(__BORLANDC__)
#pragma option push -w-8012
# endif
        if ((arg < 0 && !result_traits::is_signed)  // loss of negative range
             || (arg_traits::is_signed && arg < (result_traits::min)())  // underflow
             || arg > (result_traits::max)())            // overflow
# if BOOST_MSVC
#  pragma warning(pop)
#elif defined(__BORLANDC__)
#pragma option pop
# endif
#endif
        {
            throw bad_numeric_cast();
        }
        return static_cast<Target>(arg);
    }


      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(bounds<T>::lowest()) ? cNegOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(0) ? cNegOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s <= static_cast<S>(bounds<T>::lowest()) - static_cast<S>(1.0)
                 ? cNegOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(bounds<T>::lowest()) - static_cast<S>(0.5)
                 ? cNegOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s > static_cast<S>(bounds<T>::highest())
                 ? cPosOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s >= static_cast<S>(bounds<T>::highest()) + static_cast<S>(1.0)
                 ? cPosOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        return s >= static_cast<S>(bounds<T>::highest()) + static_cast<S>(0.5)
                 ? cPosOverflow : cInRange ;
      }


      static range_check_result apply ( argument_type s )
      {
        range_check_result r = PredA::apply(s) ;
        if ( r == cInRange )
          r = PredB::apply(s);
        return r ;
      }


    static range_check_result out_of_range ( argument_type ) { return cInRange ; }

    static void validate_range ( argument_type ) {}


    static range_check_result out_of_range ( argument_type s )
    {
      typedef typename combine<IsNegOverflow,IsPosOverflow>::type Predicate ;

      return Predicate::apply(s);
    }


    static void validate_range ( argument_type s )
      { OverflowHandler()( out_of_range(s) ) ; }


    static result_type low_level_convert ( argument_type s ) { return s ; }

    static source_type nearbyint         ( argument_type s ) { return s ; }

    static result_type convert           ( argument_type s ) { return s ; }


    static result_type convert ( argument_type s )
    {
      RangeCheckerBase::validate_range(s);
      source_type s1 = Float2IntRounderBase::nearbyint(s);
      return RawConverterBase::low_level_convert(s1);
    }


    static source_type nearbyint ( argument_type s ) { return s ; }


    static result_type convert ( argument_type s )
    {
      RangeCheckerBase::validate_range(s);
      return RawConverterBase::low_level_convert(s);
    }
