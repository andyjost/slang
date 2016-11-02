
   interval_error(const std::string& s) : std::runtime_error(s) {}


inline int mpfi_sgn(mpfi_srcptr p)
{
   if(mpfi_is_zero(p))
      return 0;
   if(mpfi_is_strictly_pos(p))
      return 1;
   if(mpfi_is_strictly_neg(p))
      return -1;
   BOOST_THROW_EXCEPTION(interval_error("Sign of interval is ambiguous."));
}


   mpfi_float_imp()
   {
      mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : get_default_precision()));
   }

   mpfi_float_imp(unsigned prec)
   {
      mpfi_init2(m_data, prec);
   }


   mpfi_float_imp(const mpfi_float_imp& o)
   {
      mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : get_default_precision()));
      if(o.m_data[0].left._mpfr_d)
         mpfi_set(m_data, o.m_data);
   }

   mpfi_float_backend() : detail::mpfi_float_imp<digits10>() {}

   mpfi_float_backend(const mpfi_float_backend& o) : detail::mpfi_float_imp<digits10>(o) {}

   mpfi_float_backend(mpfi_float_backend&& o) : detail::mpfi_float_imp<digits10>(static_cast<detail::mpfi_float_imp<digits10>&&>(o)) {}

   mpfi_float_backend& operator=(const mpfi_float_backend& o)
   {
      *static_cast<detail::mpfi_float_imp<digits10>*>(this) = static_cast<detail::mpfi_float_imp<digits10> const&>(o);
      return *this;
   }

   mpfi_float_backend() : detail::mpfi_float_imp<0>() {}

   mpfi_float_backend(const mpfi_float_backend& o) : detail::mpfi_float_imp<0>(o) {}


template <class Backend, expression_template_option ExpressionTemplates>
inline std::ostream& operator << (std::ostream& os, const number<Backend, ExpressionTemplates>& r)
{
   std::streamsize d = os.precision();
   std::string s = r.str(d, os.flags());
   std::streamsize ss = os.width();
   if(ss > static_cast<std::streamsize>(s.size()))
   {
      char fill = os.fill();
      if((os.flags() & std::ios_base::left) == std::ios_base::left)
         s.append(static_cast<std::string::size_type>(ss - s.size()), fill);
      else
         s.insert(0, static_cast<std::string::size_type>(ss - s.size()), fill);
   }
   return os << s;
}


template <class tag, class A1, class A2, class A3, class A4>
inline std::ostream& operator << (std::ostream& os, const expression<tag, A1, A2, A3, A4>& r)
{
   typedef typename expression<tag, A1, A2, A3, A4>::result_type value_type;
   value_type temp(r);
   return os << temp;
}


template <class Backend, expression_template_option ExpressionTemplates>
inline std::istream& operator >> (std::istream& is, number<Backend, ExpressionTemplates>& r)
{
   std::string s;
   is >> s;
   r.assign(s);
   return is;
}


template <class Backend, multiprecision::expression_template_option ExpressionTemplates>
inline std::istream& operator >> (std::istream& is, rational<multiprecision::number<Backend, ExpressionTemplates> >& r)
{
   std::string s1;
   multiprecision::number<Backend, ExpressionTemplates> v1, v2;
   char c;
   bool have_hex = false;

   while((EOF != (c = static_cast<char>(is.peek()))) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
   {
      if(c == 'x' || c == 'X')
         have_hex = true;
      s1.append(1, c);
      is.get();
   }
   v1.assign(s1);
   s1.erase();
   if(c == '/')
   {
      is.get();
      while((EOF != (c = static_cast<char>(is.peek()))) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
      {
         if(c == 'x' || c == 'X')
            have_hex = true;
         s1.append(1, c);
         is.get();
      }
      v2.assign(s1);
   }
   else
      v2 = 1;
   r.assign(v1, v2);
   return is;
}


   rational_adaptor(){}

   rational_adaptor(const rational_adaptor& o)
   {
      m_value = o.m_value;
   }

   rational_adaptor(const IntBackend& o) : m_value(o) {}


template <class IntBackend>
inline void eval_add(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() += o.data();
}

template <class IntBackend>
inline void eval_subtract(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() -= o.data();
}

template <class IntBackend>
inline void eval_multiply(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() *= o.data();
}

template <class IntBackend>
inline void eval_divide(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   using default_ops::eval_is_zero;
   if(eval_is_zero(o))
   {
      BOOST_THROW_EXCEPTION(std::overflow_error("Divide by zero."));
   }
   result.data() /= o.data();
}


template <class R, class IntBackend>
inline void eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   *result = backend.data().numerator().template convert_to<R>();
   *result /= backend.data().denominator().template convert_to<R>();
}


template <class IntBackend>
inline bool eval_is_zero(const rational_adaptor<IntBackend>& val)
{
   return eval_is_zero(val.data().numerator().backend());
}

template <class IntBackend>
inline int eval_get_sign(const rational_adaptor<IntBackend>& val)
{
   return eval_get_sign(val.data().numerator().backend());
}


template<class IntBackend, class V>
inline void assign_components(rational_adaptor<IntBackend>& result, const V& v1, const V& v2)
{
   result.data().assign(v1, v2);
}

   cpp_dec_float(fpclass_type c)   : 
      data(),
      exp      (static_cast<ExponentType>(0)),
      neg      (false),
      fpclass  (c),
      prec_elem(cpp_dec_float_elem_number) { }

         initializer()
         {
            cpp_dec_float<Digits10, ExponentType, Allocator>::nan();
            cpp_dec_float<Digits10, ExponentType, Allocator>::inf();
            (cpp_dec_float<Digits10, ExponentType, Allocator>::min)();
            (cpp_dec_float<Digits10, ExponentType, Allocator>::max)();
            cpp_dec_float<Digits10, ExponentType, Allocator>::zero();
            cpp_dec_float<Digits10, ExponentType, Allocator>::one();
            cpp_dec_float<Digits10, ExponentType, Allocator>::two();
            cpp_dec_float<Digits10, ExponentType, Allocator>::half();
            cpp_dec_float<Digits10, ExponentType, Allocator>::double_min();
            cpp_dec_float<Digits10, ExponentType, Allocator>::double_max();
            cpp_dec_float<Digits10, ExponentType, Allocator>::long_double_max();
            cpp_dec_float<Digits10, ExponentType, Allocator>::long_double_min();
            cpp_dec_float<Digits10, ExponentType, Allocator>::long_long_max();
            cpp_dec_float<Digits10, ExponentType, Allocator>::long_long_min();
            cpp_dec_float<Digits10, ExponentType, Allocator>::ulong_long_max();
            cpp_dec_float<Digits10, ExponentType, Allocator>::eps();
            cpp_dec_float<Digits10, ExponentType, Allocator>::pow2(0);
         }

         void do_nothing(){}

   cpp_dec_float()   : 
      data(),
      exp      (static_cast<ExponentType>(0)),
      neg      (false),
      fpclass  (cpp_dec_float_finite),
      prec_elem(cpp_dec_float_elem_number) { }


   cpp_dec_float(const char* s) : 
      data(),
      exp      (static_cast<ExponentType>(0)),
      neg      (false),
      fpclass  (cpp_dec_float_finite),
      prec_elem(cpp_dec_float_elem_number) 
      {
         *this = s;
      }


   cpp_dec_float(const cpp_dec_float& f)   : 
      data     (f.data),
      exp      (f.exp),
      neg      (f.neg),
      fpclass  (f.fpclass),
      prec_elem(f.prec_elem) { }

   static const cpp_dec_float& nan()  
   {
      static const cpp_dec_float val(cpp_dec_float_NaN);
      init.do_nothing();
      return val;
   }

   static const cpp_dec_float& inf()  
   {
      static const cpp_dec_float val(cpp_dec_float_inf);
      init.do_nothing();
      return val;
   }

   static const cpp_dec_float& (max)()
   {
      init.do_nothing();
      static bool init = false;
      static const std::string str_max =   std::string("9." + std::string(static_cast<std::size_t>(cpp_dec_float_total_digits10), static_cast<char>('9')))
         + std::string("e+" + boost::lexical_cast<std::string>(cpp_dec_float_max_exp10));
      static cpp_dec_float val_max;
      if(!init)
      {
         init = true;
         val_max = str_max.c_str();
      }
      return val_max;
   }


   static const cpp_dec_float& (min)()
   {
      init.do_nothing();
      static bool init = false;
      static cpp_dec_float val_min;
      if(!init)
      {
         init = true;
         val_min = std::string("1.0e" + boost::lexical_cast<std::string>(cpp_dec_float_min_exp10)).c_str();
      }
      return val_min;
   }

   static const cpp_dec_float& zero()  
   {
      init.do_nothing();
      static cpp_dec_float val(static_cast<unsigned long long>(0u));
      return val;
   }

   static const cpp_dec_float& one()  
   {
      init.do_nothing();
      static cpp_dec_float val(static_cast<unsigned long long>(1u));
      return val;
   }

   static const cpp_dec_float& two()  
   {
      init.do_nothing();
      static cpp_dec_float val(static_cast<unsigned long long>(2u));
      return val;
   }

   static const cpp_dec_float& half()  
   {
      init.do_nothing();
      static cpp_dec_float val(0.5L);
      return val;
   }

   static const cpp_dec_float& double_min()  
   {
      init.do_nothing();
      static cpp_dec_float val(static_cast<long double>((std::numeric_limits<double>::min)()));
      return val;
   }

   static const cpp_dec_float& double_max()  
   {
      init.do_nothing();
      static cpp_dec_float val(static_cast<long double>((std::numeric_limits<double>::max)()));
      return val;
   }

   static const cpp_dec_float& long_double_min()  
   {
      init.do_nothing();
      static cpp_dec_float val((std::numeric_limits<long double>::min)());
      return val;
   }

   static const cpp_dec_float& long_double_max()  
   {
      init.do_nothing();
      static cpp_dec_float val((std::numeric_limits<long double>::max)());
      return val;
   }

   static const cpp_dec_float& long_long_max()  
   {
      init.do_nothing();
      static cpp_dec_float val((std::numeric_limits<long long>::max)());
      return val;
   }

   static const cpp_dec_float& long_long_min()  
   {
      init.do_nothing();
      static cpp_dec_float val((std::numeric_limits<long long>::min)());
      return val;
   }

   static const cpp_dec_float& ulong_long_max()  
   {
      init.do_nothing();
      static cpp_dec_float val((std::numeric_limits<unsigned long long>::max)());
      return val;
   }

   static const cpp_dec_float& eps()  
   {
      init.do_nothing();
      static cpp_dec_float val(1.0, 1 - (int)Digits10);
      return val;
   }

   cpp_dec_float& operator= (const cpp_dec_float& v)  
   {
      data = v.data;
      exp = v.exp;
      neg = v.neg;
      fpclass = v.fpclass;
      prec_elem = v.prec_elem;
      return *this;
   }

   cpp_dec_float& operator= (long long v)  
   {
      if(v < 0)
      {
         from_unsigned_long_long(-v);
         negate();
      }
      else
         from_unsigned_long_long(v);
      return *this;
   }

   cpp_dec_float& operator= (unsigned long long v)  
   {
      from_unsigned_long_long(v);
      return *this;
   }

   cpp_dec_float& operator= (const char* v)
   {
      rd_string(v);
      return *this;
   }

   
   cpp_dec_float& add_unsigned_long_long(const unsigned long long n)  
   {
      cpp_dec_float t;
      t.from_unsigned_long_long(n);
      return *this += t;
   }

   cpp_dec_float& sub_unsigned_long_long(const unsigned long long n)  
   {
      cpp_dec_float t;
      t.from_unsigned_long_long(n);
      return *this -= t;
   }

   void negate()   
   { 
      if(!iszero())
         neg = !neg;
   }

   bool isnan   (void) const  { return (fpclass == cpp_dec_float_NaN); }

   bool isinf   (void) const  { return (fpclass == cpp_dec_float_inf); }

   bool isfinite(void) const  { return (fpclass == cpp_dec_float_finite); }


   bool iszero (void) const 
   {
      return ((fpclass == cpp_dec_float_finite) && (data[0u] == 0u));
   }

   bool isneg  (void) const  { return neg; }

   cpp_dec_float& operator++(void)  
   {
      return *this += one();
   }

   cpp_dec_float& operator--(void)  
   {
      return *this -= one();
   }

   template <class V>
   int compare(const V& v)const 
   {
      cpp_dec_float<Digits10, ExponentType, Allocator> t;
      t = v;
      return compare(t);
   }


   void swap(cpp_dec_float& v) 
   {
      data.swap(v.data);
      std::swap(exp, v.exp);
      std::swap(neg, v.neg);
      std::swap(fpclass, v.fpclass);
      std::swap(prec_elem, v.prec_elem);
   }

   void precision(const boost::int32_t prec_digits) 
   {
      if(prec_digits >= cpp_dec_float_total_digits10)
      {
         prec_elem = cpp_dec_float_elem_number;
      }
      else
      {
         const boost::int32_t elems = static_cast<boost::int32_t>(  static_cast<boost::int32_t>( (prec_digits + (cpp_dec_float_elem_digits10 / 2)) / cpp_dec_float_elem_digits10)
            + static_cast<boost::int32_t>(((prec_digits %  cpp_dec_float_elem_digits10) != 0) ? 1 : 0));

         prec_elem = (std::min)(cpp_dec_float_elem_number, (std::max)(elems, static_cast<boost::int32_t>(2)));
      }
   }

   ExponentType order()const 
   {
      const bool bo_order_is_zero = ((!isfinite()) || (data[0] == static_cast<boost::uint32_t>(0u)));
      //
      // Binary search to find the order of the leading term:
      //
      ExponentType prefix = 0;

      if(data[0] >= 100000UL)
      {
         if(data[0] >= 10000000UL)
         {
            if(data[0] >= 100000000UL)
            {
               if(data[0] >= 1000000000UL)
                  prefix = 9;
               else
                  prefix = 8;
            }
            else
               prefix = 7;
         }
         else
         {
            if(data[0] >= 1000000UL)
               prefix = 6;
            else
               prefix = 5;
         }
      }
      else
      {
         if(data[0] >= 1000UL)
         {
            if(data[0] >= 10000UL)
               prefix = 4;
            else
               prefix = 3;
         }
         else
         {
            if(data[0] >= 100)
               prefix = 2;
            else if(data[0] >= 10)
               prefix = 1;
         }
      }

      return (bo_order_is_zero ? static_cast<ExponentType>(0) : static_cast<ExponentType>(exp + prefix));
   }

   static bool data_elem_is_non_zero_predicate(const boost::uint32_t& d)  { return (d != static_cast<boost::uint32_t>(0u)); }

   static bool data_elem_is_non_nine_predicate(const boost::uint32_t& d)  { return (d != static_cast<boost::uint32_t>(cpp_dec_float::cpp_dec_float_elem_mask - 1)); }

   static bool char_is_nonzero_predicate(const char& c)  { return (c != static_cast<char>('0')); }



template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::operator+=(const cpp_dec_float<Digits10, ExponentType, Allocator>& v)
{
   if(isnan())
   {
      return *this;
   }

   if(isinf())
   {
      if(v.isinf() && (isneg() != v.isneg()))
      {
         *this = nan();
      }
      return *this;
   }

   if(iszero())
   {
      return operator=(v);
   }

   // Get the offset for the add/sub operation.
   static const ExponentType max_delta_exp = static_cast<ExponentType>((cpp_dec_float_elem_number - 1) * cpp_dec_float_elem_digits10);

   const ExponentType ofs_exp = static_cast<ExponentType>(exp - v.exp);

   // Check if the operation is out of range, requiring special handling.
   if(v.iszero() || (ofs_exp > max_delta_exp))
   {
      // Result is *this unchanged since v is negligible compared to *this.
      return *this;
   }
   else if(ofs_exp < -max_delta_exp)
   {
      // Result is *this = v since *this is negligible compared to v.
      return operator=(v);
   }

   // Do the add/sub operation.

   typename array_type::iterator       p_u    =   data.begin();
   typename array_type::const_iterator p_v    = v.data.begin();
   bool                       b_copy = false;
   const boost::int32_t       ofs    = static_cast<boost::int32_t>(static_cast<boost::int32_t>(ofs_exp) / cpp_dec_float_elem_digits10);
   array_type                 n_data;

   if(neg == v.neg)
   {
      // Add v to *this, where the data array of either *this or v
      // might have to be treated with a positive, negative or zero offset.
      // The result is stored in *this. The data are added one element
      // at a time, each element with carry.
      if(ofs >= static_cast<boost::int32_t>(0))
      {
         std::copy(v.data.begin(), v.data.end() - static_cast<size_t>(ofs), n_data.begin() + static_cast<size_t>(ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(ofs), static_cast<boost::uint32_t>(0u));
         p_v = n_data.begin();
      }
      else
      {
         std::copy(data.begin(), data.end() - static_cast<size_t>(-ofs), n_data.begin() + static_cast<size_t>(-ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(-ofs), static_cast<boost::uint32_t>(0u));
         p_u = n_data.begin();
         b_copy = true;
      }

      // Addition algorithm
      boost::uint32_t carry = static_cast<boost::uint32_t>(0u);

      for(boost::int32_t j = static_cast<boost::int32_t>(cpp_dec_float_elem_number - static_cast<boost::int32_t>(1)); j >= static_cast<boost::int32_t>(0); j--)
      {
         boost::uint32_t t = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(p_u[j] + p_v[j]) + carry);
         carry    = t / static_cast<boost::uint32_t>(cpp_dec_float_elem_mask);
         p_u[j]   = static_cast<boost::uint32_t>(t - static_cast<boost::uint32_t>(carry * static_cast<boost::uint32_t>(cpp_dec_float_elem_mask)));
      }

      if(b_copy)
      {
         data = n_data;
         exp  = v.exp;
      }

      // There needs to be a carry into the element -1 of the array data
      if(carry != static_cast<boost::uint32_t>(0u))
      {
         std::copy_backward(data.begin(), data.end() - static_cast<std::size_t>(1u), data.end());
         data[0] = carry;
         exp += static_cast<ExponentType>(cpp_dec_float_elem_digits10);
      }
   }
   else
   {
      // Subtract v from *this, where the data array of either *this or v
      // might have to be treated with a positive, negative or zero offset.
      if((ofs > static_cast<boost::int32_t>(0))
         || (   (ofs == static_cast<boost::int32_t>(0))
         && (cmp_data(v.data) > static_cast<boost::int32_t>(0)))
         )
      {
         // In this case, |u| > |v| and ofs is positive.
         // Copy the data of v, shifted down to a lower value
         // into the data array m_n. Set the operand pointer p_v
         // to point to the copied, shifted data m_n.
         std::copy(v.data.begin(), v.data.end() - static_cast<size_t>(ofs), n_data.begin() + static_cast<size_t>(ofs));
         std::fill(n_data.begin(), n_data.begin() + static_cast<size_t>(ofs), static_cast<boost::uint32_t>(0u));
         p_v = n_data.begin();
      }
      else
      {
         if(ofs != static_cast<boost::int32_t>(0))
         {
            // In this case, |u| < |v| and ofs is negative.
            // Shift the data of u down to a lower value.
            std::copy_backward(data.begin(), data.end() - static_cast<size_t>(-ofs), data.end());
            std::fill(data.begin(), data.begin() + static_cast<size_t>(-ofs), static_cast<boost::uint32_t>(0u));
         }

         // Copy the data of v into the data array n_data.
         // Set the u-pointer p_u to point to m_n and the
         // operand pointer p_v to point to the shifted
         // data m_data.
         n_data = v.data;
         p_u    = n_data.begin();
         p_v    = data.begin();
         b_copy = true;
      }

      boost::int32_t j;

      // Subtraction algorithm
      boost::int32_t borrow = static_cast<boost::int32_t>(0);

      for(j = static_cast<boost::int32_t>(cpp_dec_float_elem_number - static_cast<boost::int32_t>(1)); j >= static_cast<boost::int32_t>(0); j--)
      {
         boost::int32_t t = static_cast<boost::int32_t>(static_cast<boost::int32_t>(  static_cast<boost::int32_t>(p_u[j])
            - static_cast<boost::int32_t>(p_v[j])) - borrow);

         // Underflow? Borrow?
         if(t < static_cast<boost::int32_t>(0))
         {
            // Yes, underflow and borrow
            t     += static_cast<boost::int32_t>(cpp_dec_float_elem_mask);
            borrow = static_cast<boost::int32_t>(1);
         }
         else
         {
            borrow = static_cast<boost::int32_t>(0);
         }

         p_u[j] = static_cast<boost::uint32_t>(static_cast<boost::uint32_t>(t) % static_cast<boost::uint32_t>(cpp_dec_float_elem_mask));
      }

      if(b_copy)
      {
         data = n_data;
         exp  = v.exp;
         neg  = v.neg;
      }

      // Is it necessary to justify the data?
      const typename array_type::const_iterator first_nonzero_elem = std::find_if(data.begin(), data.end(), data_elem_is_non_zero_predicate);

      if(first_nonzero_elem != data.begin())
      {
         if(first_nonzero_elem == data.end())
         {
            // This result of the subtraction is exactly zero.
            // Reset the sign and the exponent.
            neg = false;
            exp = static_cast<ExponentType>(0);
         }
         else
         {
            // Justify the data
            const std::size_t sj = static_cast<std::size_t>(std::distance<typename array_type::const_iterator>(data.begin(), first_nonzero_elem));

            std::copy(data.begin() + static_cast<std::size_t>(sj), data.end(), data.begin());
            std::fill(data.end() - sj, data.end(), static_cast<boost::uint32_t>(0u));

            exp -= static_cast<ExponentType>(sj * static_cast<std::size_t>(cpp_dec_float_elem_digits10));
         }
      }
   }

   // Check for underflow.
   if(iszero()) 
   { 
      return *this = zero();
   }

   bool overflow = exp >= cpp_dec_float_max_exp10;
   if(exp == cpp_dec_float_max_exp10)
   {
      // Check to see if we really truly have an overflow or not...
      if(isneg())
      {
         cpp_dec_float t(*this);
         t.negate();
         overflow = t.compare((max)()) > 0;
      }
      else
      {
         overflow = compare((max)()) > 0;
      }
   }

   // Check for overflow.
   if(overflow)
   {
      const bool b_result_is_neg = neg;

      *this = inf();
      if(b_result_is_neg)
         negate();
   }

   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::operator-=(const cpp_dec_float<Digits10, ExponentType, Allocator>& v)  
{
   // Use *this - v = -(-*this + v).
   negate();
   *this += v;
   negate();
   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::operator*=(const cpp_dec_float<Digits10, ExponentType, Allocator>& v)  
{
   // Evaluate the sign of the result.
   const bool b_result_is_neg = (neg != v.neg);

   // Artificially set the sign of the result to be positive.
   neg = false;

   // Handle special cases like zero, inf and NaN.
   const bool b_u_is_inf  =   isinf();
   const bool b_v_is_inf  = v.isinf();
   const bool b_u_is_zero =   iszero();
   const bool b_v_is_zero = v.iszero();

   if(   (isnan() || v.isnan())
      || (b_u_is_inf && b_v_is_zero)
      || (b_v_is_inf && b_u_is_zero)
      )
   {
      *this = nan();
      return *this;
   }

   if(b_u_is_inf || b_v_is_inf)
   {
      *this = inf();
      if(b_result_is_neg)
         negate();
      return *this;
   }

   if(b_u_is_zero || b_v_is_zero)
   {
      return *this = zero();
   }

   // Check for overflow or underflow.
   const bool u_exp_is_neg =   (exp < static_cast<ExponentType>(0));
   const bool v_exp_is_neg = (v.exp < static_cast<ExponentType>(0));

   if(u_exp_is_neg == v_exp_is_neg)
   {
      // Get the unsigned base-10 exponents of *this and v and...
      const ExponentType u_exp = ((!u_exp_is_neg) ?   exp : static_cast<ExponentType>(  -exp));
      const ExponentType v_exp = ((!v_exp_is_neg) ? v.exp : static_cast<ExponentType>(-v.exp));

      // Check the range of the upcoming multiplication.
      const bool b_result_is_out_of_range = (v_exp >= static_cast<ExponentType>(cpp_dec_float_max_exp10 - u_exp));

      if(b_result_is_out_of_range)
      {
         if(u_exp_is_neg)
         {
            *this = zero();
         }
         else
         {
            *this = inf();
            if(b_result_is_neg)
               negate();
         }
         return *this;
      }
   }

   // Set the exponent of the result.
   exp += v.exp;

   const boost::int32_t prec_mul = (std::min)(prec_elem, v.prec_elem);

   const boost::uint32_t carry = mul_loop_uv(data.data(), v.data.data(), prec_mul);

   // Handle a potential carry.
   if(carry != static_cast<boost::uint32_t>(0u))
   {
      exp += cpp_dec_float_elem_digits10;

      // Shift the result of the multiplication one element to the right...
      std::copy_backward(data.begin(),
                         data.begin() + static_cast<std::size_t>(prec_elem - static_cast<boost::int32_t>(1)),
                         data.begin() + static_cast<std::size_t>(prec_elem));

      // ... And insert the carry.
      data.front() = carry;
   }

   // Set the sign of the result.
   neg = b_result_is_neg;

   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::operator/=(const cpp_dec_float<Digits10, ExponentType, Allocator>& v)  
{
   const bool u_and_v_are_finite_and_identical = (   isfinite()
      && (fpclass == v.fpclass)
      && (exp     == v.exp)
      && (cmp_data(v.data) == static_cast<boost::int32_t>(0)));

   if(u_and_v_are_finite_and_identical)
   {
      if(neg != v.neg)
      {
         *this = one();
         negate();
      }
      else
         *this = one();
      return *this;
   }
   else
   {
      if(iszero())
      {
         if(v.isnan() || v.iszero())
         {
            return *this = v;
         }
         return *this;
      }
      cpp_dec_float t(v);
      t.calculate_inv();
      return operator*=(t);
   }
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::mul_unsigned_long_long(const unsigned long long n)  
{
   // Multiply *this with a constant unsigned long long.

   // Evaluate the sign of the result.
   const bool b_neg = neg;

   // Artificially set the sign of the result to be positive.
   neg = false;

   // Handle special cases like zero, inf and NaN.
   const bool b_u_is_inf  = isinf();
   const bool b_n_is_zero = (n == static_cast<boost::int32_t>(0));

   if(isnan() || (b_u_is_inf && b_n_is_zero))
   {
      return (*this = nan());
   }

   if(b_u_is_inf)
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(iszero() || b_n_is_zero)
   {
      // Multiplication by zero.
      return *this = zero();
   }

   if(n >= static_cast<unsigned long long>(cpp_dec_float_elem_mask))
   {
      neg = b_neg;
      cpp_dec_float t;
      t = n;
      return operator*=(t);
   }

   if(n == static_cast<unsigned long long>(1u))
   {
      neg = b_neg;
      return *this;
   }

   // Set up the multiplication loop.
   const boost::uint32_t nn = static_cast<boost::uint32_t>(n);
   const boost::uint32_t carry = mul_loop_n(data.data(), nn, prec_elem);

   // Handle the carry and adjust the exponent.
   if(carry != static_cast<boost::uint32_t>(0u))
   {
      exp += static_cast<ExponentType>(cpp_dec_float_elem_digits10);

      // Shift the result of the multiplication one element to the right.
      std::copy_backward(data.begin(),
         data.begin() + static_cast<std::size_t>(prec_elem - static_cast<boost::int32_t>(1)),
         data.begin() + static_cast<std::size_t>(prec_elem));

      data.front() = static_cast<boost::uint32_t>(carry);
   }

   bool overflow = exp >= cpp_dec_float_max_exp10;
   if(exp == cpp_dec_float_max_exp10)
   {
      // Check to see if we really truly have an overflow or not...
      if(isneg())
      {
         cpp_dec_float t(*this);
         t.negate();
         overflow = t.compare((max)()) > 0;
      }
      else
      {
         overflow = compare((max)()) > 0;
      }
   }

   if(overflow)
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   // Set the sign.
   neg = b_neg;

   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::div_unsigned_long_long(const unsigned long long n)  
{
   // Divide *this by a constant unsigned long long.

   // Evaluate the sign of the result.
   const bool b_neg = neg;

   // Artificially set the sign of the result to be positive.
   neg = false;

   // Handle special cases like zero, inf and NaN.
   if(isnan())
   {
      return *this;
   }

   if(isinf())
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(n == static_cast<unsigned long long>(0u))
   {
      // Divide by 0.
      if(iszero())
      {
         *this = nan();
         return *this;
      }
      else
      {
         *this = inf();
         if(isneg())
            negate();
         return *this;
      }
   }

   if(iszero())
   {
      return *this;
   }

   if(n >= static_cast<unsigned long long>(cpp_dec_float_elem_mask))
   {
      neg = b_neg;
      cpp_dec_float t;
      t = n;
      return operator/=(t);
   }

   const boost::uint32_t nn = static_cast<boost::uint32_t>(n);

   if(nn > static_cast<boost::uint32_t>(1u))
   {
      // Do the division loop.
      const boost::uint32_t prev = div_loop_n(data.data(), nn, prec_elem);

      // Determine if one leading zero is in the result data.
      if(data[0] == static_cast<boost::uint32_t>(0u))
      {
         // Adjust the exponent
         exp -= static_cast<ExponentType>(cpp_dec_float_elem_digits10);

         // Shift result of the division one element to the left.
         std::copy(data.begin() + static_cast<std::size_t>(1u),
            data.begin() + static_cast<std::size_t>(prec_elem - static_cast<boost::int32_t>(1)),
            data.begin());

         data[prec_elem - static_cast<boost::int32_t>(1)] = static_cast<boost::uint32_t>(static_cast<boost::uint64_t>(prev * static_cast<boost::uint64_t>(cpp_dec_float_elem_mask)) / nn);
      }
   }

   // Check for underflow.
   if(iszero()) 
   {
      return *this = zero();
   }

   // Set the sign of the result.
   neg = b_neg;

   return *this; 
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::calculate_inv()  
{
   // Compute the inverse of *this.
   const bool b_neg = neg;

   neg = false;

   // Handle special cases like zero, inf and NaN.
   if(iszero())
   {
      *this = inf();
      if(b_neg)
         negate();
      return *this;
   }

   if(isnan())
   {
      return *this;
   }

   if(isinf())
   {
      return *this = zero();
   }

   if(isone())
   {
      if(b_neg)
         negate();
      return *this;
   }

   // Save the original *this.
   cpp_dec_float<Digits10, ExponentType, Allocator> x(*this);

   // Generate the initial estimate using division.
   // Extract the mantissa and exponent for a "manual"
   // computation of the estimate.
   double dd;
   ExponentType  ne;
   x.extract_parts(dd, ne);

   // Do the inverse estimate using double precision estimates of mantissa and exponent.
   operator=(cpp_dec_float<Digits10, ExponentType, Allocator>(1.0 / dd, -ne));

   // Compute the inverse of *this. Quadratically convergent Newton-Raphson iteration
   // is used. During the iterative steps, the precision of the calculation is limited
   // to the minimum required in order to minimize the run-time.

   static const boost::int32_t double_digits10_minus_a_few = std::numeric_limits<double>::digits10 - 3;

   for(boost::int32_t digits = double_digits10_minus_a_few; digits <= cpp_dec_float_total_digits10; digits *= static_cast<boost::int32_t>(2))
   {
      // Adjust precision of the terms.
      precision(static_cast<boost::int32_t>((digits + 10) * static_cast<boost::int32_t>(2)));
      x.precision(static_cast<boost::int32_t>((digits + 10) * static_cast<boost::int32_t>(2)));

      // Next iteration.
      cpp_dec_float t(*this);
      t *= x;
      t -= two();
      t.negate();
      *this *= t;
   }

   neg = b_neg;

   prec_elem = cpp_dec_float_elem_number;

   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::calculate_sqrt(void)  
{
   // Compute the square root of *this.

   if(isneg() || (!isfinite()))
   {
      *this = nan();
      return *this;
   }

   if(iszero() || isone())
   {
      return *this;
   }

   // Save the original *this.
   cpp_dec_float<Digits10, ExponentType, Allocator> x(*this);

   // Generate the initial estimate using division.
   // Extract the mantissa and exponent for a "manual"
   // computation of the estimate.
   double dd;
   ExponentType  ne;
   extract_parts(dd, ne);

   // Force the exponent to be an even multiple of two.
   if((ne % static_cast<ExponentType>(2)) != static_cast<ExponentType>(0))
   {
      ++ne;
      dd /= 10.0;
   }

   // Setup the iteration.
   // Estimate the square root using simple manipulations.
   const double sqd = std::sqrt(dd);

   *this = cpp_dec_float<Digits10, ExponentType, Allocator>(sqd, static_cast<ExponentType>(ne / static_cast<ExponentType>(2)));

   // Estimate 1.0 / (2.0 * x0) using simple manipulations.
   cpp_dec_float<Digits10, ExponentType, Allocator> vi(0.5 / sqd, static_cast<ExponentType>(-ne / static_cast<ExponentType>(2)));

   // Compute the square root of x. Coupled Newton iteration
   // as described in "Pi Unleashed" is used. During the
   // iterative steps, the precision of the calculation is
   // limited to the minimum required in order to minimize
   // the run-time.
   //
   // Book references:
   // http://www.jjj.de/pibook/pibook.html
   // http://www.amazon.com/exec/obidos/tg/detail/-/3540665722/qid=1035535482/sr=8-7/ref=sr_8_7/104-3357872-6059916?v=glance&n=507846

   static const boost::uint32_t double_digits10_minus_a_few = std::numeric_limits<double>::digits10 - 3;

   for(boost::int32_t digits = double_digits10_minus_a_few; digits <= cpp_dec_float_total_digits10; digits *= 2u)
   {
      // Adjust precision of the terms.
      precision((digits + 10) * 2);
      vi.precision((digits + 10) * 2);

      // Next iteration of vi
      cpp_dec_float t(*this);
      t *= vi;
      t.negate();
      t.mul_unsigned_long_long(2u);
      t += one();
      t *= vi;
      vi += t;

      // Next iteration of *this
      t = *this;
      t *= *this;
      t.negate();
      t += x;
      t *= vi;
      *this += t;
   }

   prec_elem = cpp_dec_float_elem_number;

   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
int cpp_dec_float<Digits10, ExponentType, Allocator>::compare(const cpp_dec_float& v) const 
{
   // Compare v with *this.
   //         Return +1 for *this > v
   //                 0 for *this = v
   //                -1 for *this < v

   // Handle all non-finite cases.
   if((!isfinite()) || (!v.isfinite()))
   {
      // NaN can never equal NaN. Return an implementation-dependent
      // signed result. Also note that comparison of NaN with NaN
      // using operators greater-than or less-than is undefined.
      if(isnan() || v.isnan()) { return (isnan() ? 1 : -1); }

      if(isinf() && v.isinf())
      {
         // Both *this and v are infinite. They are equal if they have the same sign.
         // Otherwise, *this is less than v if and only if *this is negative.
         return ((neg == v.neg) ? 0 : (neg ? -1 : 1));
      }

      if(isinf())
      {
         // *this is infinite, but v is finite.
         // So negative infinite *this is less than any finite v.
         // Whereas positive infinite *this is greater than any finite v.
         return (isneg() ? -1 : 1);
      }
      else
      {
         // *this is finite, and v is infinite.
         // So any finite *this is greater than negative infinite v.
         // Whereas any finite *this is less than positive infinite v.
         return (v.neg ? 1 : -1);
      }
   }

   // And now handle all *finite* cases.
   if(iszero())
   {
      // The value of *this is zero and v is either zero or non-zero.
      return (v.iszero() ? 0
         : (v.neg ? 1 : -1));
   }
   else if(v.iszero())
   {
      // The value of v is zero and *this is non-zero.
      return (neg ? -1 : 1);
   }
   else
   {
      // Both *this and v are non-zero.

      if(neg != v.neg)
      {
         // The signs are different.
         return (neg ? -1 : 1);
      }
      else if(exp != v.exp)
      {
         // The signs are the same and the exponents are different.
         const int val_cexpression = ((exp < v.exp) ? 1 : -1);

         return (neg ? val_cexpression : -val_cexpression);
      }
      else
      {
         // The signs are the same and the exponents are the same.
         // Compare the data.
         const int val_cmp_data = cmp_data(v.data);

         return ((!neg) ? val_cmp_data : -val_cmp_data);
      }
   }
}


template <unsigned Digits10, class ExponentType, class Allocator>
bool cpp_dec_float<Digits10, ExponentType, Allocator>::isone() const 
{
   // Check if the value of *this is identically 1 or very close to 1.

   const bool not_negative_and_is_finite = ((!neg) && isfinite());

   if(not_negative_and_is_finite)
   {
      if((data[0u] == static_cast<boost::uint32_t>(1u)) && (exp == static_cast<ExponentType>(0)))
      {
         const typename array_type::const_iterator it_non_zero = std::find_if(data.begin(), data.end(), data_elem_is_non_zero_predicate);
         return (it_non_zero == data.end());
      }
      else if((data[0u] == static_cast<boost::uint32_t>(cpp_dec_float_elem_mask - 1)) && (exp == static_cast<ExponentType>(-cpp_dec_float_elem_digits10)))
      {
         const typename array_type::const_iterator it_non_nine = std::find_if(data.begin(), data.end(), data_elem_is_non_nine_predicate);
         return (it_non_nine == data.end());
      }
   }

   return false;
}


template <unsigned Digits10, class ExponentType, class Allocator>
bool cpp_dec_float<Digits10, ExponentType, Allocator>::isint() const 
{
   if(fpclass != cpp_dec_float_finite) { return false; }

   if(iszero()) { return true; }

   if(exp < static_cast<ExponentType>(0)) { return false; } // |*this| < 1.

   const typename array_type::size_type offset_decimal_part = static_cast<typename array_type::size_type>(exp / cpp_dec_float_elem_digits10) + 1u;

   if(offset_decimal_part >= static_cast<typename array_type::size_type>(cpp_dec_float_elem_number))
   {
      // The number is too large to resolve the integer part.
      // It considered to be a pure integer.
      return true;
   }

   typename array_type::const_iterator it_non_zero = std::find_if(data.begin() + offset_decimal_part, data.end(), data_elem_is_non_zero_predicate);

   return (it_non_zero == data.end());
}


template <unsigned Digits10, class ExponentType, class Allocator>
void cpp_dec_float<Digits10, ExponentType, Allocator>::extract_parts(double& mantissa, ExponentType& exponent) const 
{
   // Extract the approximate parts mantissa and base-10 exponent from the input cpp_dec_float<Digits10, ExponentType, Allocator> value x.

   // Extracts the mantissa and exponent.
   exponent = exp;

   boost::uint32_t p10  = static_cast<boost::uint32_t>(1u);
   boost::uint32_t test = data[0u];

   for(;;)
   {
      test /= static_cast<boost::uint32_t>(10u);

      if(test == static_cast<boost::uint32_t>(0u))
      {
         break;
      }

      p10 *= static_cast<boost::uint32_t>(10u);
      ++exponent;
   }

   // Establish the upper bound of limbs for extracting the double.
   const int max_elem_in_double_count =     static_cast<int>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) / cpp_dec_float_elem_digits10)
                                         + (static_cast<int>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) % cpp_dec_float_elem_digits10) != 0 ? 1 : 0)
                                         + 1;

   // And make sure this upper bound stays within bounds of the elems.
   const std::size_t max_elem_extract_count = static_cast<std::size_t>((std::min)(static_cast<boost::int32_t>(max_elem_in_double_count), cpp_dec_float_elem_number));

   // Extract into the mantissa the first limb, extracted as a double.
   mantissa = static_cast<double>(data[0]);
   double scale = 1.0;

   // Extract the rest of the mantissa piecewise from the limbs.
   for(std::size_t i = 1u; i < max_elem_extract_count; i++)
   {
     scale /= static_cast<double>(cpp_dec_float_elem_mask);
     mantissa += (static_cast<double>(data[i]) * scale);
   }

   mantissa /= static_cast<double>(p10);

   if(neg) { mantissa = -mantissa; }
}


template <unsigned Digits10, class ExponentType, class Allocator>
double cpp_dec_float<Digits10, ExponentType, Allocator>::extract_double(void) const
{
   // Returns the double conversion of a cpp_dec_float<Digits10, ExponentType, Allocator>.

   // Check for non-normal cpp_dec_float<Digits10, ExponentType, Allocator>.
   if(!isfinite())
   {
      if(isnan())
      {
         return std::numeric_limits<double>::quiet_NaN();
      }
      else
      {
         return ((!neg) ?  std::numeric_limits<double>::infinity()
            : -std::numeric_limits<double>::infinity());
      }
   }

   cpp_dec_float<Digits10, ExponentType, Allocator> xx(*this);
   if(xx.isneg())
      xx.negate();

   // Check if *this cpp_dec_float<Digits10, ExponentType, Allocator> is zero.
   if(iszero() || (xx.compare(double_min()) < 0))
   {
      return 0.0;
   }

   // Check if *this cpp_dec_float<Digits10, ExponentType, Allocator> exceeds the maximum of double.
   if(xx.compare(double_max()) > 0)
   {
      return ((!neg) ?  std::numeric_limits<double>::infinity()
         : -std::numeric_limits<double>::infinity());
   }

   std::stringstream ss;

   ss << str(std::numeric_limits<double>::digits10 + (2 + 1), std::ios_base::scientific);

   double d;
   ss >> d;

   return d;
}


template <unsigned Digits10, class ExponentType, class Allocator>
long double cpp_dec_float<Digits10, ExponentType, Allocator>::extract_long_double(void) const
{
   // Returns the long double conversion of a cpp_dec_float<Digits10, ExponentType, Allocator>.

   // Check if *this cpp_dec_float<Digits10, ExponentType, Allocator> is subnormal.
   if(!isfinite())
   {
      if(isnan())
      {
         return std::numeric_limits<long double>::quiet_NaN();
      }
      else
      {
         return ((!neg) ?  std::numeric_limits<long double>::infinity()
            : -std::numeric_limits<long double>::infinity());
      }
   }

   cpp_dec_float<Digits10, ExponentType, Allocator> xx(*this);
   if(xx.isneg())
      xx.negate();

   // Check if *this cpp_dec_float<Digits10, ExponentType, Allocator> is zero.
   if(iszero() || (xx.compare(long_double_min()) < 0))
   {
      return static_cast<long double>(0.0);
   }

   // Check if *this cpp_dec_float<Digits10, ExponentType, Allocator> exceeds the maximum of double.
   if(xx.compare(long_double_max()) > 0)
   {
      return ((!neg) ?  std::numeric_limits<long double>::infinity()
         : -std::numeric_limits<long double>::infinity());
   }

   std::stringstream ss;

   ss << str(std::numeric_limits<long double>::digits10 + (2 + 1), std::ios_base::scientific);

   long double ld;
   ss >> ld;

   return ld;
}


template <unsigned Digits10, class ExponentType, class Allocator>
signed long long cpp_dec_float<Digits10, ExponentType, Allocator>::extract_signed_long_long(void) const  
{
   // Extracts a signed long long from *this.
   // If (x > maximum of signed long long) or (x < minimum of signed long long),
   // then the maximum or minimum of signed long long is returned accordingly.

   if(exp < static_cast<ExponentType>(0))
   {
      return static_cast<signed long long>(0);
   }

   const bool b_neg = isneg();

   unsigned long long val;

   if((!b_neg) && (compare(long_long_max()) > 0))
   {
      return (std::numeric_limits<signed long long>::max)();
   }
   else if(b_neg &&  (compare(long_long_min()) < 0))
   {
      return (std::numeric_limits<signed long long>::min)();
   }
   else
   {
      // Extract the data into an unsigned long long value.
      cpp_dec_float<Digits10, ExponentType, Allocator> xn(extract_integer_part());
      if(xn.isneg())
         xn.negate();

      val = static_cast<unsigned long long>(xn.data[0]);

      const boost::int32_t imax = (std::min)(static_cast<boost::int32_t>(static_cast<boost::int32_t>(xn.exp) / cpp_dec_float_elem_digits10), static_cast<boost::int32_t>(cpp_dec_float_elem_number - static_cast<boost::int32_t>(1)));

      for(boost::int32_t i = static_cast<boost::int32_t>(1); i <= imax; i++)
      {
         val *= static_cast<unsigned long long>(cpp_dec_float_elem_mask);
         val += static_cast<unsigned long long>(xn.data[i]);
      }
   }

   return ((!b_neg) ? static_cast<signed long long>(val) : static_cast<signed long long>(-static_cast<signed long long>(val)));
}


template <unsigned Digits10, class ExponentType, class Allocator>
unsigned long long cpp_dec_float<Digits10, ExponentType, Allocator>::extract_unsigned_long_long(void) const  
{
   // Extracts an unsigned long long from *this.
   // If x exceeds the maximum of unsigned long long,
   // then the maximum of unsigned long long is returned.
   // If x is negative, then the unsigned long long cast of
   // the signed long long extracted value is returned.

   if(isneg())
   {
      return static_cast<unsigned long long>(extract_signed_long_long());
   }

   if(exp < static_cast<ExponentType>(0))
   {
      return static_cast<unsigned long long>(0u);
   }

   const cpp_dec_float<Digits10, ExponentType, Allocator> xn(extract_integer_part());

   unsigned long long val;

   if(xn.compare(ulong_long_max()) > 0)
   {
      return (std::numeric_limits<unsigned long long>::max)();
   }
   else
   {
      // Extract the data into an unsigned long long value.
      val = static_cast<unsigned long long>(xn.data[0]);

      const boost::int32_t imax = (std::min)(static_cast<boost::int32_t>(static_cast<boost::int32_t>(xn.exp) / cpp_dec_float_elem_digits10), static_cast<boost::int32_t>(cpp_dec_float_elem_number - static_cast<boost::int32_t>(1)));

      for(boost::int32_t i = static_cast<boost::int32_t>(1); i <= imax; i++)
      {
         val *= static_cast<unsigned long long>(cpp_dec_float_elem_mask);
         val += static_cast<unsigned long long>(xn.data[i]);
      }
   }

   return val;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator> cpp_dec_float<Digits10, ExponentType, Allocator>::extract_integer_part(void) const  
{
   // Compute the signed integer part of x.

   if(!isfinite())
   {
      return *this;
   }

   if(exp < static_cast<ExponentType>(0))
   {
      // The absolute value of the number is smaller than 1.
      // Thus the integer part is zero.
      return zero();
   }

   // Truncate the digits from the decimal part, including guard digits
   // that do not belong to the integer part.

   // Make a local copy.
   cpp_dec_float<Digits10, ExponentType, Allocator> x = *this;

   // Clear out the decimal portion
   const size_t first_clear = (static_cast<size_t>(x.exp) / static_cast<size_t>(cpp_dec_float_elem_digits10)) + 1u;
   const size_t last_clear  =  static_cast<size_t>(cpp_dec_float_elem_number);

   std::fill(x.data.begin() + first_clear, x.data.begin() + last_clear, static_cast<boost::uint32_t>(0u));

   return x;
}


template <unsigned Digits10, class ExponentType, class Allocator>
bool cpp_dec_float<Digits10, ExponentType, Allocator>::rd_string(const char* const s)
{
   try{

   std::string str(s);

   // TBD: Using several regular expressions may significantly reduce
   // the code complexity (and perhaps the run-time) of rd_string().

   // Get a possible exponent and remove it.
   exp = static_cast<ExponentType>(0);

   std::size_t pos;

   if(   ((pos = str.find('e')) != std::string::npos)
      || ((pos = str.find('E')) != std::string::npos)
      )
   {
      // Remove the exponent part from the string.
      exp = boost::lexical_cast<ExponentType>(static_cast<const char*>(str.c_str() + (pos + 1u)));
      str = str.substr(static_cast<std::size_t>(0u), pos);
   }

   // Get a possible +/- sign and remove it.
   neg = false;

   if(str.size())
   {
      if(str[0] == '-')
      {
         neg = true;
         str.erase(0, 1);
      }
      else if(str[0] == '+')
      {
         str.erase(0, 1);
      }
   }
   //
   // Special cases for infinities and NaN's:
   //
   if((str == "inf") || (str == "INF") || (str == "infinity") || (str == "INFINITY"))
   {
      if(neg)
      {
         *this = this->inf();
         this->negate();
      }
      else
         *this = this->inf();
      return true;
   }
   if((str.size() >= 3) && ((str.substr(0, 3) == "nan") || (str.substr(0, 3) == "NAN") || (str.substr(0, 3) == "NaN")))
   {
      *this = this->nan();
      return true;
   }

   // Remove the leading zeros for all input types.
   const std::string::iterator fwd_it_leading_zero = std::find_if(str.begin(), str.end(), char_is_nonzero_predicate);

   if(fwd_it_leading_zero != str.begin())
   {
      if(fwd_it_leading_zero == str.end())
      {
         // The string contains nothing but leading zeros.
         // This string represents zero.
         operator=(zero());
         return true;
      }
      else
      {
         str.erase(str.begin(), fwd_it_leading_zero);
      }
   }

   // Put the input string into the standard cpp_dec_float<Digits10, ExponentType, Allocator> input form
   // aaa.bbbbE+/-n, where aaa has 1...cpp_dec_float_elem_digits10, bbbb has an
   // even multiple of cpp_dec_float_elem_digits10 which are possibly zero padded
   // on the right-end, and n is a signed 64-bit integer which is an
   // even multiple of cpp_dec_float_elem_digits10.

   // Find a possible decimal point.
   pos = str.find(static_cast<char>('.'));

   if(pos != std::string::npos)
   {
      // Remove all trailing insignificant zeros.
      const std::string::const_reverse_iterator rit_non_zero = std::find_if(str.rbegin(), str.rend(), char_is_nonzero_predicate);

      if(rit_non_zero != str.rbegin())
      {
         const std::string::size_type ofs = str.length() - std::distance<std::string::const_reverse_iterator>(str.rbegin(), rit_non_zero);
         str.erase(str.begin() + ofs, str.end());
      }

      // Check if the input is identically zero.
      if(str == std::string("."))
      {
         operator=(zero());
         return true;
      }

      // Remove leading significant zeros just after the decimal point
      // and adjust the exponent accordingly.
      // Note that the while-loop operates only on strings of the form ".000abcd..."
      // and peels away the zeros just after the decimal point.
      if(str.at(static_cast<std::size_t>(0u)) == static_cast<char>('.'))
      {
         const std::string::iterator it_non_zero = std::find_if(str.begin() + 1u, str.end(), char_is_nonzero_predicate);

         std::size_t delta_exp = static_cast<std::size_t>(0u);

         if(str.at(static_cast<std::size_t>(1u)) == static_cast<char>('0'))
         {
            delta_exp = std::distance<std::string::const_iterator>(str.begin() + 1u, it_non_zero);
         }

         // Bring one single digit into the mantissa and adjust the exponent accordingly.
         str.erase(str.begin(), it_non_zero);
         str.insert(static_cast<std::size_t>(1u), ".");
         exp -= static_cast<ExponentType>(delta_exp + 1u);
      }
   }
   else
   {
      // Input string has no decimal point: Append decimal point.
      str.append(".");
   }

   // Shift the decimal point such that the exponent is an even multiple of cpp_dec_float_elem_digits10.
   std::size_t n_shift   = static_cast<std::size_t>(0u);
   const std::size_t n_exp_rem = static_cast<std::size_t>(exp % static_cast<ExponentType>(cpp_dec_float_elem_digits10));

   if((exp % static_cast<ExponentType>(cpp_dec_float_elem_digits10)) != static_cast<ExponentType>(0))
   {
      n_shift = ((exp < static_cast<ExponentType>(0))
         ? static_cast<std::size_t>(n_exp_rem + static_cast<std::size_t>(cpp_dec_float_elem_digits10))
         : static_cast<std::size_t>(n_exp_rem));
   }

   // Make sure that there are enough digits for the decimal point shift.
   pos = str.find(static_cast<char>('.'));

   std::size_t pos_plus_one = static_cast<std::size_t>(pos + 1u);

   if((str.length() - pos_plus_one) < n_shift)
   {
      const std::size_t sz = static_cast<std::size_t>(n_shift - (str.length() - pos_plus_one));

      str.append(std::string(sz, static_cast<char>('0')));
   }

   // Do the decimal point shift.
   if(n_shift != static_cast<std::size_t>(0u))
   {
      str.insert(static_cast<std::size_t>(pos_plus_one + n_shift), ".");

      str.erase(pos, static_cast<std::size_t>(1u));

      exp -= static_cast<ExponentType>(n_shift);
   }

   // Cut the size of the mantissa to <= cpp_dec_float_elem_digits10.
   pos          = str.find(static_cast<char>('.'));
   pos_plus_one = static_cast<std::size_t>(pos + 1u);

   if(pos > static_cast<std::size_t>(cpp_dec_float_elem_digits10))
   {
      const boost::int32_t n_pos         = static_cast<boost::int32_t>(pos);
      const boost::int32_t n_rem_is_zero = ((static_cast<boost::int32_t>(n_pos % cpp_dec_float_elem_digits10) == static_cast<boost::int32_t>(0)) ? static_cast<boost::int32_t>(1) : static_cast<boost::int32_t>(0));
      const boost::int32_t n             = static_cast<boost::int32_t>(static_cast<boost::int32_t>(n_pos / cpp_dec_float_elem_digits10) - n_rem_is_zero);

      str.insert(static_cast<std::size_t>(static_cast<boost::int32_t>(n_pos - static_cast<boost::int32_t>(n * cpp_dec_float_elem_digits10))), ".");

      str.erase(pos_plus_one, static_cast<std::size_t>(1u));

      exp += static_cast<ExponentType>(static_cast<ExponentType>(n) * static_cast<ExponentType>(cpp_dec_float_elem_digits10));
   }

   // Pad the decimal part such that its value is an even
   // multiple of cpp_dec_float_elem_digits10.
   pos          = str.find(static_cast<char>('.'));
   pos_plus_one = static_cast<std::size_t>(pos + 1u);

   const boost::int32_t n_dec = static_cast<boost::int32_t>(static_cast<boost::int32_t>(str.length() - 1u) - static_cast<boost::int32_t>(pos));
   const boost::int32_t n_rem = static_cast<boost::int32_t>(n_dec % cpp_dec_float_elem_digits10);
   boost::int32_t n_cnt = ((n_rem != static_cast<boost::int32_t>(0)) ? static_cast<boost::int32_t>(cpp_dec_float_elem_digits10 - n_rem)
      : static_cast<boost::int32_t>(0));

   if(n_cnt != static_cast<boost::int32_t>(0))
   {
      str.append(static_cast<std::size_t>(n_cnt), static_cast<char>('0'));
   }

   // Truncate decimal part if it is too long.
   const std::size_t max_dec = static_cast<std::size_t>((cpp_dec_float_elem_number - 1) * cpp_dec_float_elem_digits10);

   if(static_cast<std::size_t>(str.length() - pos) > max_dec)
   {
      str = str.substr(static_cast<std::size_t>(0u),
         static_cast<std::size_t>(pos_plus_one + max_dec));
   }

   // Now the input string has the standard cpp_dec_float<Digits10, ExponentType, Allocator> input form.
   // (See the comment above.)

   // Set all the data elements to 0.
   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   // Extract the data.

   // First get the digits to the left of the decimal point...
   data[0u] = boost::lexical_cast<boost::uint32_t>(str.substr(static_cast<std::size_t>(0u), pos));

   // ...then get the remaining digits to the right of the decimal point.
   const std::string::size_type i_end = ((str.length() - pos_plus_one) / static_cast<std::string::size_type>(cpp_dec_float_elem_digits10));

   for(std::string::size_type i = static_cast<std::string::size_type>(0u); i < i_end; i++)
   {
      const std::string::const_iterator it =   str.begin()
         + pos_plus_one
         + (i * static_cast<std::string::size_type>(cpp_dec_float_elem_digits10));

      data[i + 1u] = boost::lexical_cast<boost::uint32_t>(std::string(it, it + static_cast<std::string::size_type>(cpp_dec_float_elem_digits10)));
   }

   // Check for overflow...
   if(exp > cpp_dec_float_max_exp10)
   {
      const bool b_result_is_neg = neg;

      *this = inf();
      if(b_result_is_neg)
         negate();
   }

   // ...and check for underflow.
   if(exp <= cpp_dec_float_min_exp10)
   {
      if(exp == cpp_dec_float_min_exp10)
      {
         // Check for identity with the minimum value.
         cpp_dec_float<Digits10, ExponentType, Allocator> test = *this;

         test.exp = static_cast<ExponentType>(0);

         if(test.isone())
         {
            *this = zero();
         }
      }
      else
      {
         *this = zero();
      }
   }

   }
   catch(const bad_lexical_cast&)
   {
      // Rethrow with better error message:
      std::string msg = "Unable to parse the string \"";
      msg += s;
      msg += "\" as a floating point value.";
      throw std::runtime_error(msg);
   }

   return true;
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>::cpp_dec_float(const double mantissa, const ExponentType exponent)   
 : data     (),
   exp      (static_cast<ExponentType>(0)),
   neg      (false),
   fpclass  (cpp_dec_float_finite),
   prec_elem(cpp_dec_float_elem_number)
{
   // Create *this cpp_dec_float<Digits10, ExponentType, Allocator> from a given mantissa and exponent.
   // Note: This constructor does not maintain the full precision of double.

   const bool mantissa_is_iszero = (::fabs(mantissa) < ((std::numeric_limits<double>::min)() * (1.0 + std::numeric_limits<double>::epsilon())));

   if(mantissa_is_iszero)
   {
      std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));
      return;
   }

   const bool b_neg = (mantissa < 0.0);

   double d = ((!b_neg) ? mantissa : -mantissa);
   ExponentType  e = exponent;

   while(d > 10.0) { d /= 10.0; ++e; }
   while(d <  1.0) { d *= 10.0; --e; }

   boost::int32_t shift = static_cast<boost::int32_t>(e % static_cast<boost::int32_t>(cpp_dec_float_elem_digits10));

   while(static_cast<boost::int32_t>(shift-- % cpp_dec_float_elem_digits10) != static_cast<boost::int32_t>(0))
   {
      d *= 10.0;
      --e;
   }

   exp = e;
   neg = b_neg;

   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   static const boost::int32_t digit_ratio = static_cast<boost::int32_t>(static_cast<boost::int32_t>(std::numeric_limits<double>::digits10) / static_cast<boost::int32_t>(cpp_dec_float_elem_digits10));
   static const boost::int32_t digit_loops = static_cast<boost::int32_t>(digit_ratio + static_cast<boost::int32_t>(2));

   for(boost::int32_t i = static_cast<boost::int32_t>(0); i < digit_loops; i++)
   {
      boost::uint32_t n = static_cast<boost::uint32_t>(static_cast<boost::uint64_t>(d));
      data[i]  = static_cast<boost::uint32_t>(n);
      d       -= static_cast<double>(n);
      d       *= static_cast<double>(cpp_dec_float_elem_mask);
   }
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator>& cpp_dec_float<Digits10, ExponentType, Allocator>::operator= (long double a)
{
   // Christopher Kormanyos's original code used a cast to long long here, but that fails
   // when long double has more digits than a long long.
   using std::frexp;
   using std::ldexp;
   using std::floor;

   if (a == 0) {
      return *this = zero();
   }

   if (a == 1) {
      return *this = one();
   }

   if((boost::math::isinf)(a))
   {
      return *this = inf();
   }
   if((boost::math::isnan)(a))
      return *this = nan();

   int e;
   long double f, term;
   *this = zero();

   f = frexp(a, &e);

   static const int shift = std::numeric_limits<int>::digits - 1;

   while(f)
   {
      // extract int sized bits from f:
      f = ldexp(f, shift);
      term = floor(f);
      e -= shift;
      *this *= pow2(shift);
      if(term > 0)
         add_unsigned_long_long(static_cast<unsigned>(term));
      else
         sub_unsigned_long_long(static_cast<unsigned>(-term));
      f -= term;
   }
   if(e != 0)
      *this *= pow2(e);
   return *this;
}


template <unsigned Digits10, class ExponentType, class Allocator>
void cpp_dec_float<Digits10, ExponentType, Allocator>::from_unsigned_long_long(const unsigned long long u) 
{
   std::fill(data.begin(), data.end(), static_cast<boost::uint32_t>(0u));

   exp = static_cast<ExponentType>(0);
   neg = false;
   fpclass = cpp_dec_float_finite;
   prec_elem = cpp_dec_float_elem_number;

   std::size_t i =static_cast<std::size_t>(0u);

   unsigned long long uu = u;

   boost::uint32_t temp[(std::numeric_limits<unsigned long long>::digits10 / static_cast<int>(cpp_dec_float_elem_digits10)) + 3] = { static_cast<boost::uint32_t>(0u) };

   while(uu != static_cast<unsigned long long>(0u))
   {
      temp[i] = static_cast<boost::uint32_t>(uu % static_cast<unsigned long long>(cpp_dec_float_elem_mask));
      uu = static_cast<unsigned long long>(uu / static_cast<unsigned long long>(cpp_dec_float_elem_mask));
      ++i;
   }

   if(i > static_cast<std::size_t>(1u))
   {
      exp += static_cast<ExponentType>((i - 1u) * static_cast<std::size_t>(cpp_dec_float_elem_digits10));
   }

   std::reverse(temp, temp + i);
   std::copy(temp, temp + (std::min)(i, static_cast<std::size_t>(cpp_dec_float_elem_number)), data.begin());
}


template <unsigned Digits10, class ExponentType, class Allocator>
cpp_dec_float<Digits10, ExponentType, Allocator> cpp_dec_float<Digits10, ExponentType, Allocator>::pow2(const long long p)
{
   // Create a static const table of p^2 for -128 < p < +128.
   // Note: The size of this table must be odd-numbered and
   // symmetric about 0.
   init.do_nothing();
   static const boost::array<cpp_dec_float<Digits10, ExponentType, Allocator>, 255u> p2_data =
   {{
       cpp_dec_float("5.877471754111437539843682686111228389093327783860437607543758531392086297273635864257812500000000000e-39"),
       cpp_dec_float("1.175494350822287507968736537222245677818665556772087521508751706278417259454727172851562500000000000e-38"),
       cpp_dec_float("2.350988701644575015937473074444491355637331113544175043017503412556834518909454345703125000000000000e-38"),
       cpp_dec_float("4.701977403289150031874946148888982711274662227088350086035006825113669037818908691406250000000000000e-38"),
       cpp_dec_float("9.403954806578300063749892297777965422549324454176700172070013650227338075637817382812500000000000000e-38"),
       cpp_dec_float("1.880790961315660012749978459555593084509864890835340034414002730045467615127563476562500000000000000e-37"),
       cpp_dec_float("3.761581922631320025499956919111186169019729781670680068828005460090935230255126953125000000000000000e-37"),
       cpp_dec_float("7.523163845262640050999913838222372338039459563341360137656010920181870460510253906250000000000000000e-37"),
       cpp_dec_float("1.504632769052528010199982767644474467607891912668272027531202184036374092102050781250000000000000000e-36"),
       cpp_dec_float("3.009265538105056020399965535288948935215783825336544055062404368072748184204101562500000000000000000e-36"),
       cpp_dec_float("6.018531076210112040799931070577897870431567650673088110124808736145496368408203125000000000000000000e-36"),
       cpp_dec_float("1.203706215242022408159986214115579574086313530134617622024961747229099273681640625000000000000000000e-35"),
       cpp_dec_float("2.407412430484044816319972428231159148172627060269235244049923494458198547363281250000000000000000000e-35"),
       cpp_dec_float("4.814824860968089632639944856462318296345254120538470488099846988916397094726562500000000000000000000e-35"),
       cpp_dec_float("9.629649721936179265279889712924636592690508241076940976199693977832794189453125000000000000000000000e-35"),
       cpp_dec_float("1.925929944387235853055977942584927318538101648215388195239938795566558837890625000000000000000000000e-34"),
       cpp_dec_float("3.851859888774471706111955885169854637076203296430776390479877591133117675781250000000000000000000000e-34"),
       cpp_dec_float("7.703719777548943412223911770339709274152406592861552780959755182266235351562500000000000000000000000e-34"),
       cpp_dec_float("1.540743955509788682444782354067941854830481318572310556191951036453247070312500000000000000000000000e-33"),
       cpp_dec_float("3.081487911019577364889564708135883709660962637144621112383902072906494140625000000000000000000000000e-33"),
       cpp_dec_float("6.162975822039154729779129416271767419321925274289242224767804145812988281250000000000000000000000000e-33"),
       cpp_dec_float("1.232595164407830945955825883254353483864385054857848444953560829162597656250000000000000000000000000e-32"),
       cpp_dec_float("2.465190328815661891911651766508706967728770109715696889907121658325195312500000000000000000000000000e-32"),
       cpp_dec_float("4.930380657631323783823303533017413935457540219431393779814243316650390625000000000000000000000000000e-32"),
       cpp_dec_float("9.860761315262647567646607066034827870915080438862787559628486633300781250000000000000000000000000000e-32"),
       cpp_dec_float("1.972152263052529513529321413206965574183016087772557511925697326660156250000000000000000000000000000e-31"),
       cpp_dec_float("3.944304526105059027058642826413931148366032175545115023851394653320312500000000000000000000000000000e-31"),
       cpp_dec_float("7.888609052210118054117285652827862296732064351090230047702789306640625000000000000000000000000000000e-31"),
       cpp_dec_float("1.577721810442023610823457130565572459346412870218046009540557861328125000000000000000000000000000000e-30"),
       cpp_dec_float("3.155443620884047221646914261131144918692825740436092019081115722656250000000000000000000000000000000e-30"),
       cpp_dec_float("6.310887241768094443293828522262289837385651480872184038162231445312500000000000000000000000000000000e-30"),
       cpp_dec_float("1.262177448353618888658765704452457967477130296174436807632446289062500000000000000000000000000000000e-29"),
       cpp_dec_float("2.524354896707237777317531408904915934954260592348873615264892578125000000000000000000000000000000000e-29"),
       cpp_dec_float("5.048709793414475554635062817809831869908521184697747230529785156250000000000000000000000000000000000e-29"),
       cpp_dec_float("1.009741958682895110927012563561966373981704236939549446105957031250000000000000000000000000000000000e-28"),
       cpp_dec_float("2.019483917365790221854025127123932747963408473879098892211914062500000000000000000000000000000000000e-28"),
       cpp_dec_float("4.038967834731580443708050254247865495926816947758197784423828125000000000000000000000000000000000000e-28"),
       cpp_dec_float("8.077935669463160887416100508495730991853633895516395568847656250000000000000000000000000000000000000e-28"),
       cpp_dec_float("1.615587133892632177483220101699146198370726779103279113769531250000000000000000000000000000000000000e-27"),
       cpp_dec_float("3.231174267785264354966440203398292396741453558206558227539062500000000000000000000000000000000000000e-27"),
       cpp_dec_float("6.462348535570528709932880406796584793482907116413116455078125000000000000000000000000000000000000000e-27"),
       cpp_dec_float("1.292469707114105741986576081359316958696581423282623291015625000000000000000000000000000000000000000e-26"),
       cpp_dec_float("2.584939414228211483973152162718633917393162846565246582031250000000000000000000000000000000000000000e-26"),
       cpp_dec_float("5.169878828456422967946304325437267834786325693130493164062500000000000000000000000000000000000000000e-26"),
       cpp_dec_float("1.033975765691284593589260865087453566957265138626098632812500000000000000000000000000000000000000000e-25"),
       cpp_dec_float("2.067951531382569187178521730174907133914530277252197265625000000000000000000000000000000000000000000e-25"),
       cpp_dec_float("4.135903062765138374357043460349814267829060554504394531250000000000000000000000000000000000000000000e-25"),
       cpp_dec_float("8.271806125530276748714086920699628535658121109008789062500000000000000000000000000000000000000000000e-25"),
       cpp_dec_float("1.654361225106055349742817384139925707131624221801757812500000000000000000000000000000000000000000000e-24"),
       cpp_dec_float("3.308722450212110699485634768279851414263248443603515625000000000000000000000000000000000000000000000e-24"),
       cpp_dec_float("6.617444900424221398971269536559702828526496887207031250000000000000000000000000000000000000000000000e-24"),
       cpp_dec_float("1.323488980084844279794253907311940565705299377441406250000000000000000000000000000000000000000000000e-23"),
       cpp_dec_float("2.646977960169688559588507814623881131410598754882812500000000000000000000000000000000000000000000000e-23"),
       cpp_dec_float("5.293955920339377119177015629247762262821197509765625000000000000000000000000000000000000000000000000e-23"),
       cpp_dec_float("1.058791184067875423835403125849552452564239501953125000000000000000000000000000000000000000000000000e-22"),
       cpp_dec_float("2.117582368135750847670806251699104905128479003906250000000000000000000000000000000000000000000000000e-22"),
       cpp_dec_float("4.235164736271501695341612503398209810256958007812500000000000000000000000000000000000000000000000000e-22"),
       cpp_dec_float("8.470329472543003390683225006796419620513916015625000000000000000000000000000000000000000000000000000e-22"),
       cpp_dec_float("1.694065894508600678136645001359283924102783203125000000000000000000000000000000000000000000000000000e-21"),
       cpp_dec_float("3.388131789017201356273290002718567848205566406250000000000000000000000000000000000000000000000000000e-21"),
       cpp_dec_float("6.776263578034402712546580005437135696411132812500000000000000000000000000000000000000000000000000000e-21"),
       cpp_dec_float("1.355252715606880542509316001087427139282226562500000000000000000000000000000000000000000000000000000e-20"),
       cpp_dec_float("2.710505431213761085018632002174854278564453125000000000000000000000000000000000000000000000000000000e-20"),
       cpp_dec_float("5.421010862427522170037264004349708557128906250000000000000000000000000000000000000000000000000000000e-20"),
       cpp_dec_float("1.084202172485504434007452800869941711425781250000000000000000000000000000000000000000000000000000000e-19"),
       cpp_dec_float("2.168404344971008868014905601739883422851562500000000000000000000000000000000000000000000000000000000e-19"),
       cpp_dec_float("4.336808689942017736029811203479766845703125000000000000000000000000000000000000000000000000000000000e-19"),
       cpp_dec_float("8.673617379884035472059622406959533691406250000000000000000000000000000000000000000000000000000000000e-19"),
       cpp_dec_float("1.734723475976807094411924481391906738281250000000000000000000000000000000000000000000000000000000000e-18"),
       cpp_dec_float("3.469446951953614188823848962783813476562500000000000000000000000000000000000000000000000000000000000e-18"),
       cpp_dec_float("6.938893903907228377647697925567626953125000000000000000000000000000000000000000000000000000000000000e-18"),
       cpp_dec_float("1.387778780781445675529539585113525390625000000000000000000000000000000000000000000000000000000000000e-17"),
       cpp_dec_float("2.775557561562891351059079170227050781250000000000000000000000000000000000000000000000000000000000000e-17"),
       cpp_dec_float("5.551115123125782702118158340454101562500000000000000000000000000000000000000000000000000000000000000e-17"),
       cpp_dec_float("1.110223024625156540423631668090820312500000000000000000000000000000000000000000000000000000000000000e-16"),
       cpp_dec_float("2.220446049250313080847263336181640625000000000000000000000000000000000000000000000000000000000000000e-16"),
       cpp_dec_float("4.440892098500626161694526672363281250000000000000000000000000000000000000000000000000000000000000000e-16"),
       cpp_dec_float("8.881784197001252323389053344726562500000000000000000000000000000000000000000000000000000000000000000e-16"),
       cpp_dec_float("1.776356839400250464677810668945312500000000000000000000000000000000000000000000000000000000000000000e-15"),
       cpp_dec_float("3.552713678800500929355621337890625000000000000000000000000000000000000000000000000000000000000000000e-15"),
       cpp_dec_float("7.105427357601001858711242675781250000000000000000000000000000000000000000000000000000000000000000000e-15"),
       cpp_dec_float("1.421085471520200371742248535156250000000000000000000000000000000000000000000000000000000000000000000e-14"),
       cpp_dec_float("2.842170943040400743484497070312500000000000000000000000000000000000000000000000000000000000000000000e-14"),
       cpp_dec_float("5.684341886080801486968994140625000000000000000000000000000000000000000000000000000000000000000000000e-14"),
       cpp_dec_float("1.136868377216160297393798828125000000000000000000000000000000000000000000000000000000000000000000000e-13"),
       cpp_dec_float("2.273736754432320594787597656250000000000000000000000000000000000000000000000000000000000000000000000e-13"),
       cpp_dec_float("4.547473508864641189575195312500000000000000000000000000000000000000000000000000000000000000000000000e-13"),
       cpp_dec_float("9.094947017729282379150390625000000000000000000000000000000000000000000000000000000000000000000000000e-13"),
       cpp_dec_float("1.818989403545856475830078125000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
       cpp_dec_float("3.637978807091712951660156250000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
       cpp_dec_float("7.275957614183425903320312500000000000000000000000000000000000000000000000000000000000000000000000000e-12"),
       cpp_dec_float("1.455191522836685180664062500000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
       cpp_dec_float("2.910383045673370361328125000000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
       cpp_dec_float("5.820766091346740722656250000000000000000000000000000000000000000000000000000000000000000000000000000e-11"),
       cpp_dec_float("1.164153218269348144531250000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
       cpp_dec_float("2.328306436538696289062500000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
       cpp_dec_float("4.656612873077392578125000000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
       cpp_dec_float("9.313225746154785156250000000000000000000000000000000000000000000000000000000000000000000000000000000e-10"),
       cpp_dec_float("1.862645149230957031250000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
       cpp_dec_float("3.725290298461914062500000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
       cpp_dec_float("7.450580596923828125000000000000000000000000000000000000000000000000000000000000000000000000000000000e-9"),
       cpp_dec_float("1.490116119384765625000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
       cpp_dec_float("2.980232238769531250000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
       cpp_dec_float("5.960464477539062500000000000000000000000000000000000000000000000000000000000000000000000000000000000e-8"),
       cpp_dec_float("1.192092895507812500000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
       cpp_dec_float("2.384185791015625000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
       cpp_dec_float("4.768371582031250000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
       cpp_dec_float("9.536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-7"),
       cpp_dec_float("1.907348632812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
       cpp_dec_float("3.814697265625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
       cpp_dec_float("7.629394531250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-6"),
       cpp_dec_float("0.000015258789062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000030517578125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000061035156250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000122070312500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000244140625000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000488281250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.000976562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.001953125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.003906250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.007812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.01562500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.03125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.06250000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
       cpp_dec_float("0.125"),
       cpp_dec_float("0.25"),
       cpp_dec_float("0.5"),
       one(),
       two(),
       cpp_dec_float(static_cast<unsigned long long>(4)),
       cpp_dec_float(static_cast<unsigned long long>(8)),
       cpp_dec_float(static_cast<unsigned long long>(16)),
       cpp_dec_float(static_cast<unsigned long long>(32)),
       cpp_dec_float(static_cast<unsigned long long>(64)),
       cpp_dec_float(static_cast<unsigned long long>(128)),
       cpp_dec_float(static_cast<unsigned long long>(256)),
       cpp_dec_float(static_cast<unsigned long long>(512)),
       cpp_dec_float(static_cast<unsigned long long>(1024)),
       cpp_dec_float(static_cast<unsigned long long>(2048)),
       cpp_dec_float(static_cast<unsigned long long>(4096)),
       cpp_dec_float(static_cast<unsigned long long>(8192)),
       cpp_dec_float(static_cast<unsigned long long>(16384)),
       cpp_dec_float(static_cast<unsigned long long>(32768)),
       cpp_dec_float(static_cast<unsigned long long>(65536)),
       cpp_dec_float(static_cast<unsigned long long>(131072)),
       cpp_dec_float(static_cast<unsigned long long>(262144)),
       cpp_dec_float(static_cast<unsigned long long>(524288)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 20u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 21u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 22u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 23u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 24u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 25u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 26u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 27u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 28u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 29u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 30u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uL << 31u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 32u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 33u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 34u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 35u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 36u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 37u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 38u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 39u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 40u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 41u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 42u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 43u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 44u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 45u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 46u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 47u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 48u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 49u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 50u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 51u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 52u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 53u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 54u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 55u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 56u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 57u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 58u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 59u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 60u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 61u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 62u)),
       cpp_dec_float(static_cast<boost::uint64_t>(1uLL << 63u)),
       cpp_dec_float("1.844674407370955161600000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
       cpp_dec_float("3.689348814741910323200000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
       cpp_dec_float("7.378697629483820646400000000000000000000000000000000000000000000000000000000000000000000000000000000e19"),
       cpp_dec_float("1.475739525896764129280000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
       cpp_dec_float("2.951479051793528258560000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
       cpp_dec_float("5.902958103587056517120000000000000000000000000000000000000000000000000000000000000000000000000000000e20"),
       cpp_dec_float("1.180591620717411303424000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
       cpp_dec_float("2.361183241434822606848000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
       cpp_dec_float("4.722366482869645213696000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
       cpp_dec_float("9.444732965739290427392000000000000000000000000000000000000000000000000000000000000000000000000000000e21"),
       cpp_dec_float("1.888946593147858085478400000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
       cpp_dec_float("3.777893186295716170956800000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
       cpp_dec_float("7.555786372591432341913600000000000000000000000000000000000000000000000000000000000000000000000000000e22"),
       cpp_dec_float("1.511157274518286468382720000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
       cpp_dec_float("3.022314549036572936765440000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
       cpp_dec_float("6.044629098073145873530880000000000000000000000000000000000000000000000000000000000000000000000000000e23"),
       cpp_dec_float("1.208925819614629174706176000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
       cpp_dec_float("2.417851639229258349412352000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
       cpp_dec_float("4.835703278458516698824704000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
       cpp_dec_float("9.671406556917033397649408000000000000000000000000000000000000000000000000000000000000000000000000000e24"),
       cpp_dec_float("1.934281311383406679529881600000000000000000000000000000000000000000000000000000000000000000000000000e25"),
       cpp_dec_float("3.868562622766813359059763200000000000000000000000000000000000000000000000000000000000000000000000000e25"),
       cpp_dec_float("7.737125245533626718119526400000000000000000000000000000000000000000000000000000000000000000000000000e25"),
       cpp_dec_float("1.547425049106725343623905280000000000000000000000000000000000000000000000000000000000000000000000000e26"),
       cpp_dec_float("3.094850098213450687247810560000000000000000000000000000000000000000000000000000000000000000000000000e26"),
       cpp_dec_float("6.189700196426901374495621120000000000000000000000000000000000000000000000000000000000000000000000000e26"),
       cpp_dec_float("1.237940039285380274899124224000000000000000000000000000000000000000000000000000000000000000000000000e27"),
       cpp_dec_float("2.475880078570760549798248448000000000000000000000000000000000000000000000000000000000000000000000000e27"),
       cpp_dec_float("4.951760157141521099596496896000000000000000000000000000000000000000000000000000000000000000000000000e27"),
       cpp_dec_float("9.903520314283042199192993792000000000000000000000000000000000000000000000000000000000000000000000000e27"),
       cpp_dec_float("1.980704062856608439838598758400000000000000000000000000000000000000000000000000000000000000000000000e28"),
       cpp_dec_float("3.961408125713216879677197516800000000000000000000000000000000000000000000000000000000000000000000000e28"),
       cpp_dec_float("7.922816251426433759354395033600000000000000000000000000000000000000000000000000000000000000000000000e28"),
       cpp_dec_float("1.584563250285286751870879006720000000000000000000000000000000000000000000000000000000000000000000000e29"),
       cpp_dec_float("3.169126500570573503741758013440000000000000000000000000000000000000000000000000000000000000000000000e29"),
       cpp_dec_float("6.338253001141147007483516026880000000000000000000000000000000000000000000000000000000000000000000000e29"),
       cpp_dec_float("1.267650600228229401496703205376000000000000000000000000000000000000000000000000000000000000000000000e30"),
       cpp_dec_float("2.535301200456458802993406410752000000000000000000000000000000000000000000000000000000000000000000000e30"),
       cpp_dec_float("5.070602400912917605986812821504000000000000000000000000000000000000000000000000000000000000000000000e30"),
       cpp_dec_float("1.014120480182583521197362564300800000000000000000000000000000000000000000000000000000000000000000000e31"),
       cpp_dec_float("2.028240960365167042394725128601600000000000000000000000000000000000000000000000000000000000000000000e31"),
       cpp_dec_float("4.056481920730334084789450257203200000000000000000000000000000000000000000000000000000000000000000000e31"),
       cpp_dec_float("8.112963841460668169578900514406400000000000000000000000000000000000000000000000000000000000000000000e31"),
       cpp_dec_float("1.622592768292133633915780102881280000000000000000000000000000000000000000000000000000000000000000000e32"),
       cpp_dec_float("3.245185536584267267831560205762560000000000000000000000000000000000000000000000000000000000000000000e32"),
       cpp_dec_float("6.490371073168534535663120411525120000000000000000000000000000000000000000000000000000000000000000000e32"),
       cpp_dec_float("1.298074214633706907132624082305024000000000000000000000000000000000000000000000000000000000000000000e33"),
       cpp_dec_float("2.596148429267413814265248164610048000000000000000000000000000000000000000000000000000000000000000000e33"),
       cpp_dec_float("5.192296858534827628530496329220096000000000000000000000000000000000000000000000000000000000000000000e33"),
       cpp_dec_float("1.038459371706965525706099265844019200000000000000000000000000000000000000000000000000000000000000000e34"),
       cpp_dec_float("2.076918743413931051412198531688038400000000000000000000000000000000000000000000000000000000000000000e34"),
       cpp_dec_float("4.153837486827862102824397063376076800000000000000000000000000000000000000000000000000000000000000000e34"),
       cpp_dec_float("8.307674973655724205648794126752153600000000000000000000000000000000000000000000000000000000000000000e34"),
       cpp_dec_float("1.661534994731144841129758825350430720000000000000000000000000000000000000000000000000000000000000000e35"),
       cpp_dec_float("3.323069989462289682259517650700861440000000000000000000000000000000000000000000000000000000000000000e35"),
       cpp_dec_float("6.646139978924579364519035301401722880000000000000000000000000000000000000000000000000000000000000000e35"),
       cpp_dec_float("1.329227995784915872903807060280344576000000000000000000000000000000000000000000000000000000000000000e36"),
       cpp_dec_float("2.658455991569831745807614120560689152000000000000000000000000000000000000000000000000000000000000000e36"),
       cpp_dec_float("5.316911983139663491615228241121378304000000000000000000000000000000000000000000000000000000000000000e36"),
       cpp_dec_float("1.063382396627932698323045648224275660800000000000000000000000000000000000000000000000000000000000000e37"),
       cpp_dec_float("2.126764793255865396646091296448551321600000000000000000000000000000000000000000000000000000000000000e37"),
       cpp_dec_float("4.253529586511730793292182592897102643200000000000000000000000000000000000000000000000000000000000000e37"),
       cpp_dec_float("8.507059173023461586584365185794205286400000000000000000000000000000000000000000000000000000000000000e37"),
       cpp_dec_float("1.701411834604692317316873037158841057280000000000000000000000000000000000000000000000000000000000000e38")
   }};

   if((p > static_cast<long long>(-128)) && (p < static_cast<long long>(+128)))
   {
      return p2_data[static_cast<std::size_t>(p + ((p2_data.size() - 1u) / 2u))];
   }
   else
   {
      // Compute and return 2^p.
      if(p < static_cast<long long>(0))
      {
         return pow2(static_cast<long long>(-p)).calculate_inv();
      }
      else
      {
         cpp_dec_float<Digits10, ExponentType, Allocator> t;
         default_ops::detail::pow_imp(t, two(), p, mpl::true_());
         return t;
      }
   }
}



template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_add(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& o)  
{
   result += o;
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_subtract(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& o)  
{
   result -= o;
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_multiply(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& o)  
{
   result *= o;
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_divide(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& o)  
{
   result /= o;
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_add(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const unsigned long long& o)  
{
   result.add_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_subtract(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const unsigned long long& o)  
{
   result.sub_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_multiply(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const unsigned long long& o)  
{
   result.mul_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_divide(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const unsigned long long& o)  
{
   result.div_unsigned_long_long(o);
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_add(cpp_dec_float<Digits10, ExponentType, Allocator>& result, long long o)  
{
   if(o < 0)
      result.sub_unsigned_long_long(-o);
   else
      result.add_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_subtract(cpp_dec_float<Digits10, ExponentType, Allocator>& result, long long o)  
{
   if(o < 0)
      result.add_unsigned_long_long(-o);
   else
      result.sub_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_multiply(cpp_dec_float<Digits10, ExponentType, Allocator>& result, long long o)  
{
   if(o < 0)
   {
      result.mul_unsigned_long_long(-o);
      result.negate();
   }
   else
      result.mul_unsigned_long_long(o);
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_divide(cpp_dec_float<Digits10, ExponentType, Allocator>& result, long long o)  
{
   if(o < 0)
   {
      result.div_unsigned_long_long(-o);
      result.negate();
   }
   else
      result.div_unsigned_long_long(o);
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_convert_to(unsigned long long* result, const cpp_dec_float<Digits10, ExponentType, Allocator>& val)  
{
   *result = val.extract_unsigned_long_long();
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_convert_to(long long* result, const cpp_dec_float<Digits10, ExponentType, Allocator>& val)  
{
   *result = val.extract_signed_long_long();
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_convert_to(long double* result, cpp_dec_float<Digits10, ExponentType, Allocator>& val)
{
   *result = val.extract_long_double();
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline int eval_fpclassify(const cpp_dec_float<Digits10, ExponentType, Allocator>& x) 
{
   if(x.isinf())
      return FP_INFINITE;
   if(x.isnan())
      return FP_NAN;
   if(x.iszero())
      return FP_ZERO;
   return FP_NORMAL;
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_abs(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x) 
{
   result = x;
   if(x.isneg())
      result.negate();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_fabs(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x) 
{
   result = x;
   if(x.isneg())
      result.negate();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_sqrt(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x)  
{
   result = x;
   result.calculate_sqrt();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_floor(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x)  
{
   result = x;
   if(!x.isfinite() || x.isint()) 
   { 
      return; 
   }

   if(x.isneg())
      result -= cpp_dec_float<Digits10, ExponentType, Allocator>::one();
   result = result.extract_integer_part();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_ceil(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x)  
{
   result = x;
   if(!x.isfinite() || x.isint()) 
   { 
      return; 
   }

   if(!x.isneg())
      result += cpp_dec_float<Digits10, ExponentType, Allocator>::one();
   result = result.extract_integer_part();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_trunc(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x)
{
   if(!x.isfinite()) 
   { 
      result = boost::math::policies::raise_rounding_error("boost::multiprecision::trunc<%1%>(%1%)", 0, number<cpp_dec_float<Digits10, ExponentType, Allocator> >(x), number<cpp_dec_float<Digits10, ExponentType, Allocator> >(x), boost::math::policies::policy<>()).backend();
      return;
   }
   else if(x.isint())
   {
      result = x;
      return;
   }
   result = x.extract_integer_part();
}


template <unsigned Digits10, class ExponentType, class Allocator, class ArgType>
inline void eval_ldexp(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x, ArgType e)  
{
   const long long the_exp = static_cast<long long>(e);

   if((the_exp > (std::numeric_limits<ExponentType>::max)()) || (the_exp < (std::numeric_limits<ExponentType>::min)()))
      BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Exponent value is out of range.")));

   result = x;

   if     ((the_exp > static_cast<long long>(-std::numeric_limits<long long>::digits)) && (the_exp < static_cast<long long>(0)))
      result.div_unsigned_long_long(1ULL << static_cast<long long>(-the_exp));
   else if((the_exp < static_cast<long long>( std::numeric_limits<long long>::digits)) && (the_exp > static_cast<long long>(0)))
      result.mul_unsigned_long_long(1ULL << the_exp);
   else if(the_exp != static_cast<long long>(0))
      result *= cpp_dec_float<Digits10, ExponentType, Allocator>::pow2(e);
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline void eval_frexp(cpp_dec_float<Digits10, ExponentType, Allocator>& result, const cpp_dec_float<Digits10, ExponentType, Allocator>& x, ExponentType* e)
{
   result = x;
   if(result.isneg())
      result.negate();

   if(result.iszero())
   {
      *e = 0;
      return;
   }

   ExponentType t = result.order();
   BOOST_MP_USING_ABS
   if(abs(t) < ((std::numeric_limits<ExponentType>::max)() / 1000))
   {
      t *= 1000;
      t /= 301;
   }
   else
   {
      t /= 301;
      t *= 1000;
   }

   result *= cpp_dec_float<Digits10, ExponentType, Allocator>::pow2(-t);

   if(result.iszero() || result.isinf() || result.isnan())
   {
      // pow2 overflowed, slip the calculation up:
      result = x;
      if(result.isneg())
         result.negate();
      t /= 2;
      result *= cpp_dec_float<Digits10, ExponentType, Allocator>::pow2(-t);
   }
   BOOST_MP_USING_ABS
   if(abs(result.order()) > 5)
   {
      // If our first estimate doesn't get close enough then try recursion until we do:
      ExponentType e2;
      cpp_dec_float<Digits10, ExponentType, Allocator> r2;
      eval_frexp(r2, result, &e2);
      // overflow protection:
      if((t > 0) && (e2 > 0) && (t > (std::numeric_limits<ExponentType>::max)() - e2))
         BOOST_THROW_EXCEPTION(std::runtime_error("Exponent is too large to be represented as a power of 2."));
      if((t < 0) && (e2 < 0) && (t < (std::numeric_limits<ExponentType>::min)() - e2))
         BOOST_THROW_EXCEPTION(std::runtime_error("Exponent is too large to be represented as a power of 2."));
      t += e2;
      result = r2;
   }

   while(result.compare(cpp_dec_float<Digits10, ExponentType, Allocator>::one()) >= 0)
   {
      result /= cpp_dec_float<Digits10, ExponentType, Allocator>::two();
      ++t;
   }
   while(result.compare(cpp_dec_float<Digits10, ExponentType, Allocator>::half()) < 0)
   {
      result *= cpp_dec_float<Digits10, ExponentType, Allocator>::two();
      --t;
   }
   *e = t;
   if(x.isneg())
      result.negate();
}


template <unsigned Digits10, class ExponentType, class Allocator>
inline bool eval_is_zero(const cpp_dec_float<Digits10, ExponentType, Allocator>& val) 
{
   return val.iszero();
}

template <unsigned Digits10, class ExponentType, class Allocator>
inline int eval_get_sign(const cpp_dec_float<Digits10, ExponentType, Allocator>& val) 
{
   return val.iszero() ? 0 : val.isneg() ? -1 : 1;
}

   gmp_float()
   {
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
   }

   gmp_float(const gmp_float& o) : detail::gmp_float_imp<digits10>(o) {}

   template <class V>
   gmp_float& operator=(const V& v)
   {
      *static_cast<detail::gmp_float_imp<digits10>*>(this) = v;
      return *this;
   }

   gmp_float()
   {
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
   }

   gmp_float(const gmp_float& o) : detail::gmp_float_imp<0>(o) {}

   template <unsigned D>
   gmp_float(const gmp_float<D>& o)
   {
      mpf_init2(this->m_data, mpf_get_prec(o.data()));
      mpf_set(this->m_data, o.data());
   }

   gmp_float(const gmp_float& o, unsigned digits10)
   {
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpf_set(this->m_data, o.data());
   }


   gmp_float& operator=(const gmp_float& o)
   {
      *static_cast<detail::gmp_float_imp<0>*>(this) = static_cast<detail::gmp_float_imp<0> const&>(o);
      return *this;
   }

   template <class V>
   gmp_float& operator=(const V& v)
   {
      *static_cast<detail::gmp_float_imp<0>*>(this) = v;
      return *this;
   }


   gmp_rational()
   {
      mpq_init(this->m_data);
   }

   gmp_rational(const gmp_rational& o)
   {
      mpq_init(m_data);
      if(o.m_data[0]._mp_num._mp_d)
         mpq_set(m_data, o.m_data);
   }

   gmp_rational(const gmp_int& o)
   {
      mpq_init(m_data);
      mpq_set_z(m_data, o.data());
   }


inline bool eval_is_zero(const gmp_rational& val)
{
   return mpq_sgn(val.data()) == 0;
}

template <class T>
inline bool eval_eq(gmp_rational& a, const T& b)
{
   return a.compare(b) == 0;
}

template <class T>
inline bool eval_lt(gmp_rational& a, const T& b)
{
   return a.compare(b) < 0;
}

template <class T>
inline bool eval_gt(gmp_rational& a, const T& b)
{
   return a.compare(b) > 0;
}


inline void eval_add(gmp_rational& t, const gmp_rational& o)
{
   mpq_add(t.data(), t.data(), o.data());
}

inline void eval_subtract(gmp_rational& t, const gmp_rational& o)
{
   mpq_sub(t.data(), t.data(), o.data());
}

inline void eval_multiply(gmp_rational& t, const gmp_rational& o)
{
   mpq_mul(t.data(), t.data(), o.data());
}

inline void eval_divide(gmp_rational& t, const gmp_rational& o)
{
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   mpq_div(t.data(), t.data(), o.data());
}

inline void eval_add(gmp_rational& t, const gmp_rational& p, const gmp_rational& o)
{
   mpq_add(t.data(), p.data(), o.data());
}

inline void eval_subtract(gmp_rational& t, const gmp_rational& p, const gmp_rational& o)
{
   mpq_sub(t.data(), p.data(), o.data());
}

inline void eval_multiply(gmp_rational& t, const gmp_rational& p, const gmp_rational& o)
{
   mpq_mul(t.data(), p.data(), o.data());
}

inline void eval_divide(gmp_rational& t, const gmp_rational& p, const gmp_rational& o)
{
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Division by zero."));
   mpq_div(t.data(), p.data(), o.data());
}


inline int eval_get_sign(const gmp_rational& val)
{
   return mpq_sgn(val.data());
}

inline void eval_convert_to(double* result, const gmp_rational& val)
{
   *result = mpq_get_d(val.data());
}


inline void eval_convert_to(long* result, const gmp_rational& val)
{
   double r;
   eval_convert_to(&r, val);
   *result = static_cast<long>(r);
}


inline void eval_convert_to(unsigned long* result, const gmp_rational& val)
{
   double r;
   eval_convert_to(&r, val);
   *result = static_cast<long>(r);
}


inline void eval_abs(gmp_rational& result, const gmp_rational& val)
{
   mpq_abs(result.data(), val.data());
}


inline void assign_components(gmp_rational& result, unsigned long v1, unsigned long v2)
{
   mpq_set_ui(result.data(), v1, v2);
   mpq_canonicalize(result.data());
}

inline void assign_components(gmp_rational& result, long v1, long v2)
{
   mpq_set_si(result.data(), v1, v2);
   mpq_canonicalize(result.data());
}

inline void assign_components(gmp_rational& result, gmp_int const& v1, gmp_int const& v2)
{
   mpz_set(mpq_numref(result.data()), v1.data());
   mpz_set(mpq_denref(result.data()), v2.data());
   mpq_canonicalize(result.data());
}

template <unsigned Digits10>
inline gmp_float<Digits10>::gmp_float(const gmp_int& o)
{
   mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(Digits10 ? Digits10 : this->get_default_precision()));
   mpf_set_z(this->data(), o.data());
}

template <unsigned Digits10>
inline gmp_float<Digits10>::gmp_float(const gmp_rational& o)
{
   mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(Digits10 ? Digits10 : this->get_default_precision()));
   mpf_set_q(this->data(), o.data());
}

template <unsigned D>
inline gmp_float<Digits10>& gmp_float<Digits10>::operator=(const gmp_float<D>& o)
{
   if(this->m_data[0]._mp_d == 0)
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(Digits10 ? Digits10 : this->get_default_precision()));
   mpf_set(this->m_data, o.data());
   return *this;
}

template <unsigned Digits10>
inline gmp_float<Digits10>& gmp_float<Digits10>::operator=(const gmp_int& o)
{
   if(this->m_data[0]._mp_d == 0)
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(Digits10 ? Digits10 : this->get_default_precision()));
   mpf_set_z(this->data(), o.data());
   return *this;
}

template <unsigned Digits10>
inline gmp_float<Digits10>& gmp_float<Digits10>::operator=(const gmp_rational& o)
{
   if(this->m_data[0]._mp_d == 0)
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(Digits10 ? Digits10 : this->get_default_precision()));
   mpf_set_q(this->data(), o.data());
   return *this;
}

inline gmp_float<0>::gmp_float(const gmp_int& o)
{
   mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
   mpf_set_z(this->data(), o.data());
}

inline gmp_float<0>::gmp_float(const gmp_rational& o)
{
   mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
   mpf_set_q(this->data(), o.data());
}

inline gmp_float<0>& gmp_float<0>::operator=(const gmp_int& o)
{
   if(this->m_data[0]._mp_d == 0)
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(this->get_default_precision()));
   mpf_set_z(this->data(), o.data());
   return *this;
}

inline gmp_float<0>& gmp_float<0>::operator=(const gmp_rational& o)
{
   if(this->m_data[0]._mp_d == 0)
      mpf_init2(this->m_data, multiprecision::detail::digits10_2_2(this->get_default_precision()));
   mpf_set_q(this->data(), o.data());
   return *this;
}

   void update_view()
   {
      try
      {
         debug_value = m_value.str(0, static_cast<std::ios_base::fmtflags>(0));
      }
      catch(const std::exception& e)
      {
         debug_value = "String conversion failed with message: \"";
         debug_value += e.what();
         debug_value += "\"";
      }
   }

   debug_adaptor()
   {
      update_view();
   }

   debug_adaptor(const debug_adaptor& o) : debug_value(o.debug_value), m_value(o.m_value)
   {
   }

   debug_adaptor& operator = (const debug_adaptor& o)
   {
      debug_value = o.debug_value;
      m_value = o.m_value;
      return *this;
   }

   template <class T>
   debug_adaptor(const T& i, const T& j)
      : m_value(i, j)
   {
      update_view();
   }


template <class Backend>
inline Backend const& unwrap_debug_type(debug_adaptor<Backend> const& val)
{
   return val.value();
}

template <class T>
inline const T& unwrap_debug_type(const T& val)
{
   return val;
}
 \
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const T& a)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a));\
      result.update_view();\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a));\
      result.update_view();\
   }

#define NON_MEMBER_OP3(name, str) \
   template <class Backend, class T, class U>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const T& a, const U& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b));\
      result.update_view();\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const T& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b));\
      result.update_view();\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const T& a, const debug_adaptor<Backend>& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b));\
      result.update_view();\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b));\
      result.update_view();\
   }

#define NON_MEMBER_OP4(name, str) \
   template <class Backend, class T, class U, class V>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const T& a, const U& b, const V& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b, const T& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const T& b, const debug_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const T& a, const debug_adaptor<Backend>& b, const debug_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b, const debug_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\
   template <class Backend, class T, class U>\
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& a, const T& b, const U& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));\
      result.update_view();\
   }\

NON_MEMBER_OP2(add, "+=");


template <class Backend, class R>
inline void eval_convert_to(R* result, const debug_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(result, val.value());
}


template <class Backend, class Exp>
inline void eval_frexp(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& arg, Exp* exp)
{
   eval_frexp(result.value(), arg.value(), exp);
   result.update_view();\
}


template <class Backend, class Exp>
inline void eval_ldexp(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& arg, Exp exp)
{
   eval_ldexp(result.value(), arg.value(), exp);
   result.update_view();\
}


template <class Backend>
inline int eval_fpclassify(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_fpclassify;
   return eval_fpclassify(arg.value());
}


template <class Backend>
inline void eval_left_shift(debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_left_shift;
   eval_left_shift(arg.value(), a);
   arg.update_view();\
}

template <class Backend>
inline void eval_left_shift(debug_adaptor<Backend>& arg, const debug_adaptor<Backend>& a, unsigned b)
{
   using default_ops::eval_left_shift;
   eval_left_shift(arg.value(), a.value(), b);
   arg.update_view();\
}

template <class Backend>
inline void eval_right_shift(debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_right_shift;
   eval_right_shift(arg.value(), a);
   arg.update_view();\
}

template <class Backend>
inline void eval_right_shift(debug_adaptor<Backend>& arg, const debug_adaptor<Backend>& a, unsigned b)
{
   using default_ops::eval_right_shift;
   eval_right_shift(arg.value(), a.value(), b);
   arg.update_view();\
}


template <class Backend, class T>
inline unsigned eval_integer_modulus(const debug_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   return eval_integer_modulus(arg.value(), a);
}


template <class Backend>
inline unsigned eval_lsb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   return eval_lsb(arg.value());
}


template <class Backend>
inline bool eval_bit_test(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_test;
   return eval_bit_test(arg.value(), a);
}


template <class Backend>
inline void eval_bit_set(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_set;
   eval_bit_set(arg.value(), a);
   arg.update_view();\
}

template <class Backend>
inline void eval_bit_unset(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_unset;
   eval_bit_unset(arg.value(), a);
   arg.update_view();\
}

template <class Backend>
inline void eval_bit_flip(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_flip;
   eval_bit_flip(arg.value(), a);
   arg.update_view();\
}

   float128_backend& operator = (const float128_backend& o) 
   {
      m_value = o.m_value;
      return *this;
   }


inline void eval_add(float128_backend& result, const float128_backend& a)
{
   result.value() += a.value();
}

template <class A>
inline void eval_add(float128_backend& result, const A& a)
{
   result.value() += a;
}

inline void eval_subtract(float128_backend& result, const float128_backend& a)
{
   result.value() -= a.value();
}

template <class A>
inline void eval_subtract(float128_backend& result, const A& a)
{
   result.value() -= a;
}

inline void eval_multiply(float128_backend& result, const float128_backend& a)
{
   result.value() *= a.value();
}

template <class A>
inline void eval_multiply(float128_backend& result, const A& a)
{
   result.value() *= a;
}

inline void eval_divide(float128_backend& result, const float128_backend& a)
{
   result.value() /= a.value();
}

template <class A>
inline void eval_divide(float128_backend& result, const A& a)
{
   result.value() /= a;
}


inline void eval_add(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() + b.value();
}

template <class A>
inline void eval_add(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() + b;
}

inline void eval_subtract(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() - b.value();
}

template <class A>
inline void eval_subtract(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() - b;
}

template <class A>
inline void eval_subtract(float128_backend& result, const A& a, const float128_backend& b)
{
   result.value() = a - b.value();
}

inline void eval_multiply(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() * b.value();
}

template <class A>
inline void eval_multiply(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() * b;
}

inline void eval_divide(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() / b.value();
}


template <class R>
inline void eval_convert_to(R* result, const float128_backend& val)
{
   *result = static_cast<R>(val.value());
}


inline void eval_frexp(float128_backend& result, const float128_backend& arg, int* exp)
{
   result.value() = frexpq(arg.value(), exp);
}


inline void eval_ldexp(float128_backend& result, const float128_backend& arg, int exp)
{
   result.value() = ldexpq(arg.value(), exp);
}


inline void eval_floor(float128_backend& result, const float128_backend& arg)
{
   result.value() = floorq(arg.value());
}

inline void eval_ceil(float128_backend& result, const float128_backend& arg)
{
   result.value() = ceilq(arg.value());
}

inline void eval_sqrt(float128_backend& result, const float128_backend& arg)
{
   result.value() = sqrtq(arg.value());
}

inline int eval_fpclassify(const float128_backend& arg)
{
   return isnanq(arg.value()) ? FP_NAN : isinfq(arg.value()) ? FP_INFINITE : arg.value() == 0 ? FP_ZERO : FP_NORMAL;
}


inline void eval_increment(float128_backend& arg)
{
   ++arg.value();
}

inline void eval_decrement(float128_backend& arg)
{
   --arg.value();
}


inline void eval_abs(float128_backend& result, const float128_backend& arg)
{
   result.value() = fabsq(arg.value());
}

inline void eval_fabs(float128_backend& result, const float128_backend& arg)
{
   result.value() = fabsq(arg.value());
}


inline void eval_trunc(float128_backend& result, const float128_backend& arg)
{
   if(isnanq(arg.value()) || isinfq(arg.value()))
   {
      result = boost::math::policies::raise_rounding_error(
            "boost::multiprecision::trunc<%1%>(%1%)", 0, 
            number<float128_backend, et_off>(arg), 
            number<float128_backend, et_off>(arg), 
            boost::math::policies::policy<>()).backend();
      return;
   }
   result.value() = truncq(arg.value());
}


inline void eval_exp(float128_backend& result, const float128_backend& arg)
{
   result.value() = expq(arg.value());
}

inline void eval_log(float128_backend& result, const float128_backend& arg)
{
   result.value() = logq(arg.value());
}

inline void eval_log10(float128_backend& result, const float128_backend& arg)
{
   result.value() = log10q(arg.value());
}

inline void eval_sin(float128_backend& result, const float128_backend& arg)
{
   result.value() = sinq(arg.value());
}

inline void eval_cos(float128_backend& result, const float128_backend& arg)
{
   result.value() = cosq(arg.value());
}

inline void eval_tan(float128_backend& result, const float128_backend& arg)
{
   result.value() = tanq(arg.value());
}

inline void eval_asin(float128_backend& result, const float128_backend& arg)
{
   result.value() = asinq(arg.value());
}

inline void eval_acos(float128_backend& result, const float128_backend& arg)
{
   result.value() = acosq(arg.value());
}

inline void eval_atan(float128_backend& result, const float128_backend& arg)
{
   result.value() = atanq(arg.value());
}

inline void eval_sinh(float128_backend& result, const float128_backend& arg)
{
   result.value() = sinhq(arg.value());
}

inline void eval_cosh(float128_backend& result, const float128_backend& arg)
{
   result.value() = coshq(arg.value());
}

inline void eval_tanh(float128_backend& result, const float128_backend& arg)
{
   result.value() = tanhq(arg.value());
}

inline void eval_fmod(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = fmodq(a.value(), b.value());
}

inline void eval_pow(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = powq(a.value(), b.value());
}

inline void eval_atan2(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = atan2q(a.value(), b.value());
}


inline void check_tommath_result(unsigned v)
{
   if(v != MP_OKAY)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error(mp_error_to_string(v)));
   }
}


   tommath_int()
   {
      detail::check_tommath_result(mp_init(&m_data));
   }

   tommath_int(const tommath_int& o)
   {
      detail::check_tommath_result(mp_init_copy(&m_data, const_cast< ::mp_int*>(&o.m_data)));
   }


inline void eval_add(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_subtract(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_multiply(tommath_int& t, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_divide(tommath_int& t, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   tommath_int temp;
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   detail::check_tommath_result(mp_div(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data(), &temp.data()));
}

inline void eval_modulus(tommath_int& t, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   bool neg = eval_get_sign(t) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if(neg && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}

template <class UI>
inline void eval_left_shift(tommath_int& t, UI i)
{
   detail::check_tommath_result(mp_mul_2d(&t.data(), static_cast<unsigned>(i), &t.data()));
}

template <class UI>
inline void eval_right_shift(tommath_int& t, UI i)
{
   tommath_int d;
   detail::check_tommath_result(mp_div_2d(&t.data(), static_cast<unsigned>(i), &t.data(), &d.data()));
}

template <class UI>
inline void eval_left_shift(tommath_int& t, const tommath_int& v, UI i)
{
   detail::check_tommath_result(mp_mul_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned>(i), &t.data()));
}

template <class UI>
inline void eval_right_shift(tommath_int& t, const tommath_int& v, UI i)
{
   tommath_int d;
   detail::check_tommath_result(mp_div_2d(const_cast< ::mp_int*>(&v.data()), static_cast<unsigned long>(i), &t.data(), &d.data()));
}


inline void eval_bitwise_and(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}


inline void eval_bitwise_or(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}


inline void eval_bitwise_xor(tommath_int& result, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(result);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(&result.data(), const_cast< ::mp_int*>(&v.data()), &result.data()));
}


inline void eval_add(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_add(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_subtract(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_sub(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_multiply(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   detail::check_tommath_result(mp_mul(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
}

inline void eval_divide(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   tommath_int d;
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data(), &d.data()));
}

inline void eval_modulus(tommath_int& t, const tommath_int& p, const tommath_int& o)
{
   using default_ops::eval_is_zero;
   if(eval_is_zero(o))
      BOOST_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
   bool neg = eval_get_sign(p) < 0;
   bool neg2 = eval_get_sign(o) < 0;
   detail::check_tommath_result(mp_mod(const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&o.data()), &t.data()));
   if((neg != neg2) && (eval_get_sign(t) != 0))
   {
      t.negate();
      detail::check_tommath_result(mp_add(&t.data(), const_cast< ::mp_int*>(&o.data()), &t.data()));
      t.negate();
   }
   else if(neg  && (t.compare(o) == 0))
   {
      mp_zero(&t.data());
   }
}


inline void eval_bitwise_and(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_and(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}


inline void eval_bitwise_or(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_or(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}


inline void eval_bitwise_xor(tommath_int& result, const tommath_int& u, const tommath_int& v)
{
   BOOST_MP_TOMMATH_BIT_OP_CHECK(u);
   BOOST_MP_TOMMATH_BIT_OP_CHECK(v);
   detail::check_tommath_result(mp_xor(const_cast< ::mp_int*>(&u.data()), const_cast< ::mp_int*>(&v.data()), &result.data()));
}

inline bool eval_is_zero(const tommath_int& val)
{
   return mp_iszero(&val.data());
}

inline int eval_get_sign(const tommath_int& val)
{
   return mp_iszero(&val.data()) ? 0 : SIGN(&val.data()) ? -1 : 1;
}

template <class A>
inline void eval_convert_to(A* result, const tommath_int& val)
{
   *result = boost::lexical_cast<A>(val.str(0, std::ios_base::fmtflags(0)));
}

inline void eval_convert_to(char* result, const tommath_int& val)
{
   *result = static_cast<char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}

inline void eval_convert_to(unsigned char* result, const tommath_int& val)
{
   *result = static_cast<unsigned char>(boost::lexical_cast<unsigned>(val.str(0, std::ios_base::fmtflags(0))));
}

inline void eval_convert_to(signed char* result, const tommath_int& val)
{
   *result = static_cast<signed char>(boost::lexical_cast<int>(val.str(0, std::ios_base::fmtflags(0))));
}

inline void eval_abs(tommath_int& result, const tommath_int& val)
{
   detail::check_tommath_result(mp_abs(const_cast< ::mp_int*>(&val.data()), &result.data()));
}

inline void eval_gcd(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_gcd(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}

inline void eval_lcm(tommath_int& result, const tommath_int& a, const tommath_int& b)
{
   detail::check_tommath_result(mp_lcm(const_cast< ::mp_int*>(&a.data()), const_cast< ::mp_int*>(&b.data()), const_cast< ::mp_int*>(&result.data())));
}

inline void eval_powm(tommath_int& result, const tommath_int& base, const tommath_int& p, const tommath_int& m)
{
   if(eval_get_sign(p) < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   detail::check_tommath_result(mp_exptmod(const_cast< ::mp_int*>(&base.data()), const_cast< ::mp_int*>(&p.data()), const_cast< ::mp_int*>(&m.data()), &result.data()));
}



inline void eval_qr(const tommath_int& x, const tommath_int& y, 
   tommath_int& q, tommath_int& r)
{
   detail::check_tommath_result(mp_div(const_cast< ::mp_int*>(&x.data()), const_cast< ::mp_int*>(&y.data()), &q.data(), &r.data()));
}


inline unsigned eval_lsb(const tommath_int& val)
{
   int c = eval_get_sign(val);
   if(c == 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("No bits were set in the operand."));
   }
   if(c < 0)
   {
      BOOST_THROW_EXCEPTION(std::range_error("Testing individual bits in negative values is not supported - results are undefined."));
   }
   return mp_cnt_lsb(const_cast< ::mp_int*>(&val.data()));
}


inline void verify_new_size(unsigned new_size, unsigned min_size, const mpl::int_<checked>&)
{
   if(new_size < min_size)
      BOOST_THROW_EXCEPTION(std::overflow_error("Unable to allocate sufficient storage for the value of the result: value overflows the maximum allowable magnitude."));
}


template <class U>
inline void verify_limb_mask(bool b, U limb, U mask, const mpl::int_<checked>&)
{
   // When we mask out "limb" with "mask", do we loose bits?  If so it's an overflow error:
   if(b && (limb & ~mask))
      BOOST_THROW_EXCEPTION(std::overflow_error("Overflow in cpp_int arithmetic: there is insufficient precision in the target type to hold all of the bits of the result."));
}

      initializer() {}

      ~initializer(){ mpfr_free_cache(); }

      void force_instantiate()const {}

   static void force_instantiate() { init.force_instantiate(); }


inline long get_default_precision() { return 50; }


   mpfr_float_imp()
   {
      mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : get_default_precision()));
   }

   mpfr_float_imp(unsigned prec)
   {
      mpfr_init2(m_data, prec);
   }


   mpfr_float_imp(const mpfr_float_imp& o)
   {
      mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : get_default_precision()));
      if(o.m_data[0]._mpfr_d)
         mpfr_set(m_data, o.m_data, GMP_RNDN);
   }

   mpfr_float_backend() : detail::mpfr_float_imp<digits10, AllocationType>() {}

   mpfr_float_backend(const mpfr_float_backend& o) : detail::mpfr_float_imp<digits10, AllocationType>(o) {}

   mpfr_float_backend(mpfr_float_backend&& o) : detail::mpfr_float_imp<digits10, AllocationType>(static_cast<detail::mpfr_float_imp<digits10, AllocationType>&&>(o)) {}

   mpfr_float_backend& operator=(const mpfr_float_backend& o)
   {
      *static_cast<detail::mpfr_float_imp<digits10, AllocationType>*>(this) = static_cast<detail::mpfr_float_imp<digits10, AllocationType> const&>(o);
      return *this;
   }

   mpfr_float_backend() : detail::mpfr_float_imp<0, allocate_dynamic>() {}

   mpfr_float_backend(const mpfr_float_backend& o) : detail::mpfr_float_imp<0, allocate_dynamic>(o) {}

      static void force_instantiate()
      {
         init.force_instantiate();
      }

         initializer()
         {
            T::get(mpl::int_<N>());
         }

         void force_instantiate()const{}


template <class Backend>
inline void log_postfix_event(const Backend&, const char* /*event_description*/)
{
}

template <class Backend, class T>
inline void log_postfix_event(const Backend&, const T&, const char* /*event_description*/)
{
}

template <class Backend>
inline void log_prefix_event(const Backend&, const char* /*event_description*/)
{
}

template <class Backend, class T>
inline void log_prefix_event(const Backend&, const T&, const char* /*event_description*/)
{
}

template <class Backend, class T, class U>
inline void log_prefix_event(const Backend&, const T&, const U&, const char* /*event_description*/)
{
}

template <class Backend, class T, class U, class V>
inline void log_prefix_event(const Backend&, const T&, const U&, const V&, const char* /*event_description*/)
{
}

   logged_adaptor()
   {
      log_postfix_event(m_value, "Default construct");
   }

   logged_adaptor(const logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "Copy construct");
      m_value = o.m_value;
      log_postfix_event(m_value, "Copy construct");
   }

   logged_adaptor& operator = (const logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "Assignment");
      m_value = o.m_value;
      log_postfix_event(m_value, "Copy construct");
      return *this;
   }


template <class T>
inline const T& unwrap_logged_type(const T& a) { return a; }

template <class Backend>
inline const Backend& unwrap_logged_type(const logged_adaptor<Backend>& a) { return a.value(); }
 \
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const T& a)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a));\
      log_postfix_event(result.value(), str);\
   }

#define NON_MEMBER_OP3(name, str) \
   template <class Backend, class T, class U>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const T& a, const U& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const T& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const T& a, const logged_adaptor<Backend>& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b));\
      log_postfix_event(result.value(), str);\
   }

#define NON_MEMBER_OP4(name, str) \
   template <class Backend, class T, class U, class V>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const T& a, const U& b, const V& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b, const T& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const T& b, const logged_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const T& a, const logged_adaptor<Backend>& b, const logged_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b, const logged_adaptor<Backend>& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\
   template <class Backend, class T, class U>\
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& a, const T& b, const U& c)\
   {\
      using default_ops::BOOST_JOIN(eval_, name);\
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);\
      BOOST_JOIN(eval_, name)(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));\
      log_postfix_event(result.value(), str);\
   }\

NON_MEMBER_OP2(add, "+=");


template <class Backend, class R>
inline void eval_convert_to(R* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(result, val.value());
   log_postfix_event(val.value(), *result, "convert_to");
}


template <class Backend, class Exp>
inline void eval_frexp(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& arg, Exp* exp)
{
   log_prefix_event(arg.value(), "frexp");
   eval_frexp(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), *exp, "frexp");
}


template <class Backend, class Exp>
inline void eval_ldexp(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& arg, Exp exp)
{
   log_prefix_event(arg.value(), "ldexp");
   eval_ldexp(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), exp, "ldexp");
}


template <class Backend>
inline int eval_fpclassify(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_fpclassify;
   log_prefix_event(arg.value(), "fpclassify");
   int r = eval_fpclassify(arg.value());
   log_postfix_event(arg.value(), r, "fpclassify");
   return r;
}


template <class Backend>
inline void eval_left_shift(logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_left_shift;
   log_prefix_event(arg.value(), a, "<<=");
   eval_left_shift(arg.value(), a);
   log_postfix_event(arg.value(), "<<=");
}

template <class Backend>
inline void eval_left_shift(logged_adaptor<Backend>& arg, const logged_adaptor<Backend>& a, unsigned b)
{
   using default_ops::eval_left_shift;
   log_prefix_event(arg.value(), a, b, "<<");
   eval_left_shift(arg.value(), a.value(), b);
   log_postfix_event(arg.value(), "<<");
}

template <class Backend>
inline void eval_right_shift(logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_right_shift;
   log_prefix_event(arg.value(), a, ">>=");
   eval_right_shift(arg.value(), a);
   log_postfix_event(arg.value(), ">>=");
}

template <class Backend>
inline void eval_right_shift(logged_adaptor<Backend>& arg, const logged_adaptor<Backend>& a, unsigned b)
{
   using default_ops::eval_right_shift;
   log_prefix_event(arg.value(), a, b, ">>");
   eval_right_shift(arg.value(), a.value(), b);
   log_postfix_event(arg.value(), ">>");
}


template <class Backend, class T>
inline unsigned eval_integer_modulus(const logged_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   log_prefix_event(arg.value(), a, "integer-modulus");
   unsigned r = eval_integer_modulus(arg.value(), a);
   log_postfix_event(arg.value(), r, "integer-modulus");
   return r;
}


template <class Backend>
inline unsigned eval_lsb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   log_prefix_event(arg.value(), "least-significant-bit");
   unsigned r = eval_lsb(arg.value());
   log_postfix_event(arg.value(), r, "least-significant-bit");
   return r;
}


template <class Backend>
inline bool eval_bit_test(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_test;
   log_prefix_event(arg.value(), a, "bit-test");
   bool r = eval_bit_test(arg.value(), a);
   log_postfix_event(arg.value(), r, "bit-test");
   return r;
}


template <class Backend>
inline void eval_bit_set(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_set;
   log_prefix_event(arg.value(), a, "bit-set");
   eval_bit_set(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-set");
}

template <class Backend>
inline void eval_bit_unset(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_unset;
   log_prefix_event(arg.value(), a, "bit-unset");
   eval_bit_unset(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-unset");
}

template <class Backend>
inline void eval_bit_flip(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_flip;
   log_prefix_event(arg.value(), a, "bit-flip");
   eval_bit_flip(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-flip");
}


template <class I>
bool check_small_factors(const I& n)
{
   static const boost::uint32_t small_factors1[] = {
      3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u };
   static const boost::uint32_t pp1 = 223092870u;

   boost::uint32_t m1 = integer_modulus(n, pp1);

   for(unsigned i = 0; i < sizeof(small_factors1) / sizeof(small_factors1[0]); ++i)
   {
      BOOST_ASSERT(pp1 % small_factors1[i] == 0);
      if(m1 % small_factors1[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors2[] = {
      29u, 31u, 37u, 41u, 43u, 47u };
   static const boost::uint32_t pp2 = 2756205443u;

   m1 = integer_modulus(n, pp2);

   for(unsigned i = 0; i < sizeof(small_factors2) / sizeof(small_factors2[0]); ++i)
   {
      BOOST_ASSERT(pp2 % small_factors2[i] == 0);
      if(m1 % small_factors2[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors3[] = {
      53u, 59u, 61u, 67u, 71u };
   static const boost::uint32_t pp3 = 907383479u;

   m1 = integer_modulus(n, pp3);

   for(unsigned i = 0; i < sizeof(small_factors3) / sizeof(small_factors3[0]); ++i)
   {
      BOOST_ASSERT(pp3 % small_factors3[i] == 0);
      if(m1 % small_factors3[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors4[] = {
      73u, 79u, 83u, 89u, 97u };
   static const boost::uint32_t pp4 = 4132280413u;

   m1 = integer_modulus(n, pp4);

   for(unsigned i = 0; i < sizeof(small_factors4) / sizeof(small_factors4[0]); ++i)
   {
      BOOST_ASSERT(pp4 % small_factors4[i] == 0);
      if(m1 % small_factors4[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors5[6][4] = {
      { 101u, 103u, 107u, 109u },
      { 113u, 127u, 131u, 137u },
      { 139u, 149u, 151u, 157u },
      { 163u, 167u, 173u, 179u },
      { 181u, 191u, 193u, 197u },
      { 199u, 211u, 223u, 227u }
   };
   static const boost::uint32_t pp5[6] = 
   { 
      121330189u, 
      113u * 127u * 131u * 137u, 
      139u * 149u * 151u * 157u,
      163u * 167u * 173u * 179u,
      181u * 191u * 193u * 197u,
      199u * 211u * 223u * 227u
   };

   for(unsigned k = 0; k < sizeof(pp5) / sizeof(*pp5); ++k)
   {
      m1 = integer_modulus(n, pp5[k]);

      for(unsigned i = 0; i < 4; ++i)
      {
         BOOST_ASSERT(pp5[k] % small_factors5[k][i] == 0);
         if(m1 % small_factors5[k][i] == 0)
            return false;
      }
   }
   return true;
}


inline bool is_small_prime(unsigned n)
{
   static const unsigned char p[] = 
   {
      3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u, 
      37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u, 
      79u, 83u, 89u, 97u, 101u, 103u, 107u, 109u, 113u, 
      127u, 131u, 137u, 139u, 149u, 151u, 157u, 163u, 
      167u, 173u, 179u, 181u, 191u, 193u, 197u, 199u, 
      211u, 223u, 227u
   };
   for(unsigned i = 0; i < sizeof(p) / sizeof(*p); ++i)
   {
      if(n == p[i])
         return true;
   }
   return false;
}


template <class B>
inline bool eval_eq(const B& a, const B& b)
{
   return a.compare(b) == 0;
}

template <class B, class A>
inline bool eval_eq(const B& a, const A& b)
{
   typedef typename mpl::if_c<
      is_convertible<A, number<B, et_on> >::value,
      number<B, et_on>,
      number<B, et_off> >::type mp_type;
   mp_type t(b);
   return eval_eq(a, t.backend());
}


template <class B>
inline bool eval_lt(const B& a, const B& b)
{
   return a.compare(b) < 0;
}

template <class B, class A>
inline bool eval_lt(const B& a, const A& b)
{
   typedef typename mpl::if_c<
      is_convertible<A, number<B, et_on> >::value,
      number<B, et_on>,
      number<B, et_off> >::type mp_type;
   mp_type t(b);
   return eval_lt(a, t.backend());
}


template <class B>
inline bool eval_gt(const B& a, const B& b)
{
   return a.compare(b) > 0;
}

template <class B, class A>
inline bool eval_gt(const B& a, const A& b)
{
   typedef typename mpl::if_c<
      is_convertible<A, number<B, et_on> >::value,
      number<B, et_on>,
      number<B, et_off> >::type mp_type;
   mp_type t(b);
   return eval_gt(a, t.backend());
}


template <class Backend, expression_template_option ExpressionTemplates>
inline bool operator == (const number<Backend, ExpressionTemplates>& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_eq;
   return eval_eq(a.backend(), b.backend());
}


template <class To, class From>
void generic_interconvert(To& to, const From& from, const mpl::int_<number_kind_floating_point>& /*to_type*/, const mpl::int_<number_kind_integer>& /*from_type*/)
{
   using default_ops::eval_get_sign;
   using default_ops::eval_bitwise_and;
   using default_ops::eval_convert_to;
   using default_ops::eval_right_shift;
   using default_ops::eval_ldexp;
   using default_ops::eval_add;
   // smallest unsigned type handled natively by "From" is likely to be it's limb_type:
   typedef typename canonical<unsigned char, From>::type   limb_type;
   // get the corresponding type that we can assign to "To":
   typedef typename canonical<limb_type, To>::type         to_type;
   From t(from);
   bool is_neg = eval_get_sign(t) < 0;
   if(is_neg)
      t.negate();
   // Pick off the first limb:
   limb_type limb;
   limb_type mask = ~static_cast<limb_type>(0);
   From fl;
   eval_bitwise_and(fl, t, mask);
   eval_convert_to(&limb, fl);
   to = static_cast<to_type>(limb);
   eval_right_shift(t, std::numeric_limits<limb_type>::digits);
   //
   // Then keep picking off more limbs until "t" is zero:
   //
   To l;
   unsigned shift = std::numeric_limits<limb_type>::digits;
   while(!eval_is_zero(t))
   {
      eval_bitwise_and(fl, t, mask);
      eval_convert_to(&limb, fl);
      l = static_cast<to_type>(limb);
      eval_right_shift(t, std::numeric_limits<limb_type>::digits);
      eval_ldexp(l, l, shift);
      eval_add(to, l);
      shift += std::numeric_limits<limb_type>::digits;
   }
   //
   // Finish off by setting the sign:
   //
   if(is_neg)
      to.negate();
}


template <class V, class Backend, multiprecision::expression_template_option ExpressionTemplates>
inline bool operator == (const sparse_vector_element<V>& a, const ::boost::multiprecision::number<Backend, ExpressionTemplates>& b)
{
   typedef typename sparse_vector_element<V>::const_reference ref_type;
   return static_cast<ref_type>(a) == b;
}


template <class T>
inline void eval_add_default(T& t, const T& u, const T& v)
{
   if(&t == &v)
   {
      eval_add(t, u);
   }
   else if(&t == &u)
   {
      eval_add(t, v);
   }
   else
   {
      t = u;
      eval_add(t, v);
   }
}


template <class T>
inline void eval_subtract_default(T& t, const T& u, const T& v)
{
   if((&t == &v) && is_signed_number<T>::value)
   {
      eval_subtract(t, u);
      t.negate();
   }
   else if(&t == &u)
   {
      eval_subtract(t, v);
   }
   else
   {
      t = u;
      eval_subtract(t, v);
   }
}


template <class T>
inline void eval_divide_default(T& t, const T& u, const T& v)
{
   if(&t == &u)
      eval_divide(t, v);
   else if(&t == &v)
   {
      T temp;
      eval_divide(temp, u, v);
      temp.swap(t);
   }
   else
   {
      t = u;
      eval_divide(t, v);
   }
}


template <class T>
inline void eval_modulus_default(T& t, const T& u, const T& v)
{
   if(&t == &u)
      eval_modulus(t, v);
   else if(&t == &v)
   {
      T temp;
      eval_modulus(temp, u, v);
      temp.swap(t);
   }
   else
   {
      t = u;
      eval_modulus(t, v);
   }
}


template <class T>
inline void eval_bitwise_and_default(T& t, const T& u, const T& v)
{
   if(&t == &v)
   {
      eval_bitwise_and(t, u);
   }
   else if(&t == &u)
   {
      eval_bitwise_and(t, v);
   }
   else
   {
      t = u;
      eval_bitwise_and(t, v);
   }
}


template <class T>
inline void eval_bitwise_or_default(T& t, const T& u, const T& v)
{
   if(&t == &v)
   {
      eval_bitwise_or(t, u);
   }
   else if(&t == &u)
   {
      eval_bitwise_or(t, v);
   }
   else
   {
      t = u;
      eval_bitwise_or(t, v);
   }
}


template <class T>
inline void eval_bitwise_xor_default(T& t, const T& u, const T& v)
{
   if(&t == &v)
   {
      eval_bitwise_xor(t, u);
   }
   else if(&t == &u)
   {
      eval_bitwise_xor(t, v);
   }
   else
   {
      t = u;
      eval_bitwise_xor(t, v);
   }
}

   terminal(const R& v) : value(v){}

   terminal(){}

   terminal& operator = (R val) {  value = val;  }

   operator R()const {  return value;  }


template <class R, class T>
inline bool check_in_range(const T& t)
{
   // Can t fit in an R?
   if(std::numeric_limits<R>::is_specialized && std::numeric_limits<R>::is_bounded && (t > (std::numeric_limits<R>::max)()))
      return true;
   return false;
}


template <class R, class T>
inline bool check_in_range(const terminal<T>&)
{
   return false;
}


template <class R, class B>
inline void eval_convert_to(R* result, const B& backend)
{
   typedef typename calculate_next_larger_type<R, B>::type next_type;
   next_type n;
   eval_convert_to(&n, backend);
   if(check_in_range<R>(n))
   {
      *result = (std::numeric_limits<R>::max)();
   }
   else
      *result = static_cast<R>(n);
}


template <class R, class B>
inline void eval_convert_to(terminal<R>* result, const B& backend)
{
   //
   // We ran out of types to try for the conversion, try
   // a lexical_cast and hope for the best:
   //
   result->value = boost::lexical_cast<R>(backend.str(0, std::ios_base::fmtflags(0)));
}

template <class T>
void eval_abs(T& result, const T& arg)
{
   typedef typename T::signed_types type_list;
   typedef typename mpl::front<type_list>::type front;
   result = arg;
   if(arg.compare(front(0)) < 0)
      result.negate();
}

template <class T>
void eval_fabs(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The fabs function is only valid for floating point types.");
   typedef typename T::signed_types type_list;
   typedef typename mpl::front<type_list>::type front;
   result = arg;
   if(arg.compare(front(0)) < 0)
      result.negate();
}


template <class Backend>
inline int eval_fpclassify(const Backend& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_floating_point, "The fpclassify function is only valid for floating point types.");
   return eval_is_zero(arg) ? FP_ZERO : FP_NORMAL;
}


template <class T>
inline void eval_fmod(T& result, const T& a, const T& b)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The fmod function is only valid for floating point types.");
   if((&result == &a) || (&result == &b))
   {
      T temp;
      eval_fmod(temp, a, b);
      result = temp;
      return;
   }
   T n;
   eval_divide(result, a, b);
   if(eval_get_sign(a) < 0)
      eval_ceil(n, result);
   else
      eval_floor(n, result);
   eval_multiply(n, b);
   eval_subtract(result, a, n);
}
 BOOST_PREVENT_MACRO_SUBSTITUTION(const multiprecision::number<Backend, ExpressionTemplates>& arg)
{
   using multiprecision::default_ops::eval_fpclassify;
   return eval_fpclassify(arg.backend());
}


template <class Backend>
inline void eval_qr(const Backend& x, const Backend& y, Backend& q, Backend& r)
{
   eval_divide(q, x, y);
   eval_modulus(r, x, y);
}


template <class Backend, class Integer>
inline Integer eval_integer_modulus(const Backend& x, Integer val)
{
   BOOST_MP_USING_ABS
   using default_ops::eval_modulus;
   using default_ops::eval_convert_to;
   typedef typename boost::multiprecision::detail::canonical<Integer, Backend>::type int_type;
   Backend t;
   eval_modulus(t, x, static_cast<int_type>(val));
   Integer result;
   eval_convert_to(&result, t);
   return abs(result);
}


template <class B>
inline void eval_gcd(B& result, const B& a, const B& b)
{
   using default_ops::eval_lsb;
   using default_ops::eval_is_zero;
   using default_ops::eval_get_sign;

   int shift;

   B u(a), v(b);

   int s = eval_get_sign(u);

   /* GCD(0,x) := x */
   if(s < 0)
   {
      u.negate();
   }
   else if(s == 0)
   {
      result = v;
      return;
   }
   s = eval_get_sign(v);
   if(s < 0)
   {
      v.negate();
   }
   else if(s == 0)
   {
      result = u;
      return;
   }

   /* Let shift := lg K, where K is the greatest power of 2
   dividing both u and v. */

   unsigned us = eval_lsb(u);
   unsigned vs = eval_lsb(v);
   shift = (std::min)(us, vs);
   eval_right_shift(u, us);
   eval_right_shift(v, vs);

   do 
   {
      /* Now u and v are both odd, so diff(u, v) is even.
      Let u = min(u, v), v = diff(u, v)/2. */
      s = u.compare(v);
      if(s > 0)
         u.swap(v);
      if(s == 0)
         break;
      eval_subtract(v, u);
      vs = eval_lsb(v);
      eval_right_shift(v, vs);
   } 
   while(true);

   result = u;
   eval_left_shift(result, shift);
}


template <class B>
inline void eval_lcm(B& result, const B& a, const B& b)
{
   typedef typename mpl::front<typename B::unsigned_types>::type ui_type;
   B t;
   eval_gcd(t, a, b);

   if(eval_is_zero(t))
   {
      result = static_cast<ui_type>(0);
   }
   else
   {
      eval_divide(result, a, t);
      eval_multiply(result, b);
   }
   if(eval_get_sign(result) < 0)
      result.negate();
}

template <class B>
BOOST_MP_FORCEINLINE number<B, et_off> operator ~ (const number<B, et_off>& v)
{
   number<B, et_off> result;
   eval_complement(result.backend(), v.backend());
   return BOOST_MP_MOVE(result);
}

template <class B>
BOOST_MP_FORCEINLINE number<B, et_off> operator + (const number<B, et_off>& a, const number<B, et_off>& b)
{
   number<B, et_off> result;
   using default_ops::eval_add;
   eval_add(result.backend(), a.backend(), b.backend());
   return BOOST_MP_MOVE(result);
}

       dynamic_array() :
         std::vector<value_type, typename rebind<value_type, my_allocator>::type>(static_cast<typename std::vector<value_type, typename rebind<value_type, my_allocator>::type>::size_type>(elem_number), static_cast<value_type>(0))
       {
       }


             value_type* data()       { return &(*(this->begin())); }

       const value_type* data() const { return &(*(this->begin())); }


  template<class unsigned_type>
  int utype_prior(unsigned_type ui)
  {
    // TBD: Implement a templated binary search for this.
    int priority_bit;

    unsigned_type priority_mask = unsigned_type(unsigned_type(1U) << (std::numeric_limits<unsigned_type>::digits - 1));

    for(priority_bit = std::numeric_limits<unsigned_type>::digits - 1; priority_bit >= 0; --priority_bit)
    {
      if(unsigned_type(priority_mask & ui) != unsigned_type(0U))
      {
        break;
      }

      priority_mask >>= 1;
    }

    return priority_bit;
  }

   unmentionable* proc(){ return 0; }


   explicit expression(const Arg1& a) : arg(a) {}


   left_type left()const { return left_type(arg); }

   explicit operator bool()const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }


   explicit expression(const Arg1& a) : arg(a) {}

   explicit operator bool()const
   {
      return static_cast<bool>(arg);
   }


   expression(const Arg1& a1, const Arg2& a2) : arg1(a1), arg2(a2) {}


   left_type left()const { return left_type(arg1); }

   right_type right()const { return right_type(arg2); }


   expression(const Arg1& a1, const Arg2& a2, const Arg3& a3) : arg1(a1), arg2(a2), arg3(a3) {}


   left_type left()const { return left_type(arg1); }

   middle_type middle()const { return middle_type(arg2); }

   right_type right()const { return right_type(arg3); }


   expression(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) : arg1(a1), arg2(a2), arg3(a3), arg4(a4) {}


   left_type left()const { return left_type(arg1); }

   left_middle_type left_middle()const { return left_middle_type(arg2); }

   right_middle_type right_middle()const { return right_middle_type(arg3); }

   right_type right()const { return right_type(arg4); }


template <class S>
void format_float_string(S& str, boost::intmax_t my_exp, boost::intmax_t digits, std::ios_base::fmtflags f, bool iszero)
{
   typedef typename S::size_type size_type;
   bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
   bool fixed      = (f & std::ios_base::fixed) == std::ios_base::fixed;
   bool showpoint  = (f & std::ios_base::showpoint) == std::ios_base::showpoint;
   bool showpos     = (f & std::ios_base::showpos) == std::ios_base::showpos;

   bool neg = str.size() && (str[0] == '-');

   if(neg)
      str.erase(0, 1);

   if(digits == 0)
   {
      digits = (std::max)(str.size(), size_type(16));
   }

   if(iszero || str.empty() || (str.find_first_not_of('0') == S::npos))
   {
      // We will be printing zero, even though the value might not
      // actually be zero (it just may have been rounded to zero).
      str = "0";
      if(scientific || fixed)
      {
         str.append(1, '.');
         str.append(size_type(digits), '0');
         if(scientific)
            str.append("e+00");
      }
      else
      {
         if(showpoint)
         {
            str.append(1, '.');
            if(digits > 1)
               str.append(size_type(digits - 1), '0');
         }
      }
      if(neg)
         str.insert(0, 1, '-');
      else if(showpos)
         str.insert(0, 1, '+');
      return;
   }

   if(!fixed && !scientific && !showpoint)
   {
      //
      // Suppress trailing zeros:
      //
      std::string::iterator pos = str.end();
      while(pos != str.begin() && *--pos == '0'){}
      if(pos != str.end())
         ++pos;
      str.erase(pos, str.end());
      if(str.empty())
         str = '0';
   }
   else if(!fixed || (my_exp >= 0))
   {
      //
      // Pad out the end with zero's if we need to:
      //
      boost::intmax_t chars = str.size();
      chars = digits - chars;
      if(scientific)
         ++chars;
      if(chars > 0)
      {
         str.append(static_cast<std::string::size_type>(chars), '0');
      }
   }

   if(fixed || (!scientific && (my_exp >= -4) && (my_exp < digits)))
   {
      if(1 + my_exp > static_cast<boost::intmax_t>(str.size()))
      {
         // Just pad out the end with zeros:
         str.append(static_cast<std::string::size_type>(1 + my_exp - str.size()), '0');
         if(showpoint || fixed)
            str.append(".");
      }
      else if(my_exp + 1 < static_cast<boost::intmax_t>(str.size()))
      {
         if(my_exp < 0)
         {
            str.insert(0, static_cast<std::string::size_type>(-1 - my_exp), '0');
            str.insert(0, "0.");
         }
         else
         {
            // Insert the decimal point:
            str.insert(static_cast<std::string::size_type>(my_exp + 1), 1, '.');
         }
      }
      else if(showpoint || fixed) // we have exactly the digits we require to left of the point
         str += ".";

      if(fixed)
      {
         // We may need to add trailing zeros:
         boost::intmax_t l = str.find('.') + 1;
         l = digits - (str.size() - l);
         if(l > 0)
            str.append(size_type(l), '0');
      }
   }
   else
   {
      BOOST_MP_USING_ABS
      // Scientific format:
      if(showpoint || (str.size() > 1))
         str.insert(1, 1, '.');
      str.append(1, 'e');
      S e = boost::lexical_cast<S>(abs(my_exp));
      if(e.size() < BOOST_MP_MIN_EXPONENT_DIGITS)
         e.insert(0, BOOST_MP_MIN_EXPONENT_DIGITS-e.size(), '0');
      if(my_exp < 0)
         e.insert(0, 1, '-');
      else
         e.insert(0, 1, '+');
      str.append(e);
   }
   if(neg)
      str.insert(0, 1, '-');
   else if(showpos)
      str.insert(0, 1, '+');
}


template <class V>
void check_shift_range(V val, const mpl::true_&, const mpl::true_&)
{
   if(val > (std::numeric_limits<std::size_t>::max)())
      BOOST_THROW_EXCEPTION(std::out_of_range("Can not shift by a value greater than std::numeric_limits<std::size_t>::max()."));
   if(val < 0)
      BOOST_THROW_EXCEPTION(std::out_of_range("Can not shift by a negative value."));
}


template <class R, class B, boost::multiprecision::expression_template_option ET>
inline R real_cast(const boost::multiprecision::number<B, ET>& val)
{
   return val.template convert_to<R>();
}


template <class R, class tag, class A1, class A2, class A3, class A4>
inline R real_cast(const boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>& val)
{
   typedef typename boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type val_type;
   return val_type(val).template convert_to<R>();
}


inline void round_string_up_at(std::string& s, int pos)
{
   //
   // Rounds up a string representation of a number at pos:
   //
   if(pos < 0)
   {
      s.insert(0, 1, '1');
   }
   else if(s[pos] == '9')
   {
      s[pos] = '0';
      round_string_up_at(s, pos - 1);
   }
   else
   {
      ++s[pos];
   }
}


template <class Backend>
std::string convert_to_string(Backend b, std::streamsize digits, std::ios_base::fmtflags f)
{
   using default_ops::eval_log10;
   using default_ops::eval_floor;
   using default_ops::eval_pow;
   using default_ops::eval_convert_to;
   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_subtract;
   using default_ops::eval_fpclassify;

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   typedef typename Backend::exponent_type exponent_type;

   std::string result;
   bool iszero = false;
   bool isneg = false;
   exponent_type expon;
   std::streamsize org_digits = digits;
   BOOST_ASSERT(digits > 0);

   int fpt = eval_fpclassify(b);

   if(fpt == FP_ZERO)
   {
      result = "0";
      iszero = true;
   }
   else if(fpt == FP_INFINITE)
   {
      if(b.compare(ui_type(0)) < 0)
         return "-inf";
      else
         return ((f & std::ios_base::showpos) == std::ios_base::showpos) ? "+inf" : "inf";
   }
   else if(fpt == FP_NAN)
   {
      return "nan";
   }
   else
   {
      //
      // Start by figuring out the exponent:
      //
      isneg = b.compare(ui_type(0)) < 0;
      if(isneg)
         b.negate();
      Backend t;
      Backend ten;
      ten = ui_type(10);

      eval_log10(t, b);
      eval_floor(t, t);
      eval_convert_to(&expon, t);
      eval_pow(t, ten, -expon);
      eval_multiply(t, b);
      //
      // Make sure we're between [1,10) and adjust if not:
      //
      if(t.compare(ui_type(1)) < 0)
      {
         eval_multiply(t, ui_type(10));
         --expon;
      }
      else if(t.compare(ui_type(10)) >= 0)
      {
         eval_divide(t, ui_type(10));
         ++expon;
      }
      Backend digit;
      ui_type cdigit;
      //
      // Adjust the number of digits required based on formatting options:
      //
      if(((f & std::ios_base::fixed) == std::ios_base::fixed) && (expon != -1))
         digits += expon + 1;
      if((f & std::ios_base::scientific) == std::ios_base::scientific)
         ++digits;
      //
      // Extract the digits one at a time:
      //
      for(unsigned i = 0; i < digits; ++i)
      {
         eval_floor(digit, t);
         eval_convert_to(&cdigit, digit);
         result += static_cast<char>('0' + cdigit);
         eval_subtract(t, digit);
         eval_multiply(t, ten);
      }
      //
      // Possibly round result:
      //
      if(digits >= 0)
      {
         eval_floor(digit, t);
         eval_convert_to(&cdigit, digit);
         eval_subtract(t, digit);
         if((cdigit == 5) && (t.compare(ui_type(0)) == 0))
         {
            // Bankers rounding:
            if((*result.rend() - '0') & 1)
            {
               round_string_up_at(result, result.size() - 1);
            }
         }
         else if(cdigit >= 5)
         {
            round_string_up_at(result, result.size() - 1);
         }
      }
   }
   while((result.size() > digits) && result.size())
   {
      // We may get here as a result of rounding...
      if(result.size() > 1)
         result.erase(result.size() - 1);
      else
      {
         if(expon > 0)
            --expon; // so we put less padding in the result.
         else
            ++expon;
         ++digits;
      }
   }
   BOOST_ASSERT(org_digits >= 0);
   if(isneg)
      result.insert(0, 1, '-');
   format_float_string(result, expon, org_digits, f, iszero);

   return result;
}


template <class Backend>
void convert_from_string(Backend& b, const char* p)
{
   using default_ops::eval_multiply;
   using default_ops::eval_add;
   using default_ops::eval_pow;
   using default_ops::eval_divide;

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   b = ui_type(0);
   if(!p || (*p == 0))
      return;

   bool is_neg = false;
   bool is_neg_expon = false;
   static const ui_type ten = ui_type(10);
   typename Backend::exponent_type expon = 0;
   int digits_seen = 0;
   typedef std::numeric_limits<number<Backend, et_off> > limits;
   static const int max_digits = limits::is_specialized ? limits::max_digits10 + 1 : INT_MAX;

   if(*p == '+') ++p;
   else if(*p == '-')
   {
      is_neg = true;
      ++p;
   }
   if((std::strcmp(p, "nan") == 0) || (std::strcmp(p, "NaN") == 0) || (std::strcmp(p, "NAN") == 0))
   {
      eval_divide(b, ui_type(0));
      if(is_neg)
         b.negate();
      return;
   }
   if((std::strcmp(p, "inf") == 0) || (std::strcmp(p, "Inf") == 0) || (std::strcmp(p, "INF") == 0))
   {
      b = ui_type(1);
      eval_divide(b, ui_type(0));
      if(is_neg)
         b.negate();
      return;
   }
   //
   // Grab all the leading digits before the decimal point:
   //
   while(std::isdigit(*p))
   {
      eval_multiply(b, ten);
      eval_add(b, ui_type(*p - '0'));
      ++p;
      ++digits_seen;
   }
   if(*p == '.')
   {
      //
      // Grab everything after the point, stop when we've seen
      // enough digits, even if there are actually more available:
      //
      ++p;
      while(std::isdigit(*p))
      {
         eval_multiply(b, ten);
         eval_add(b, ui_type(*p - '0'));
         ++p;
         --expon;
         if(++digits_seen > max_digits)
            break;
      }
      while(std::isdigit(*p))
         ++p;
   }
   //
   // Parse the exponent:
   //
   if((*p == 'e') || (*p == 'E'))
   {
      ++p;
      if(*p == '+') ++p;
      else if(*p == '-')
      {
         is_neg_expon = true;
         ++p;
      }
      typename Backend::exponent_type e2 = 0;
      while(std::isdigit(*p))
      {
         e2 *= 10;
         e2 += (*p - '0');
         ++p;
      }
      if(is_neg_expon)
         e2 = -e2;
      expon += e2;
   }
   if(expon)
   {
      // Scale by 10^expon, note that 10^expon can be
      // outside the range of our number type, even though the
      // result is within range, if that looks likely, then split
      // the calculation in two:
      Backend t;
      t = ten;
      if(expon > limits::min_exponent10 + 2)
      {
         eval_pow(t, t, expon);
         eval_multiply(b, t);
      }
      else
      {
         eval_pow(t, t, expon + digits_seen + 1);
         eval_multiply(b, t);
         t = ten;
         eval_pow(t, t, -digits_seen - 1);
         eval_multiply(b, t);
      }
   }
   if(is_neg)
      b.negate();
   if(*p)
   {
      // Unexpected input in string:
      BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected characters in string being interpreted as a float128."));
   }
}


inline unsigned long digits10_2_2(unsigned long d10)
{
   return (d10 * 1000uL) / 301uL + ((d10 * 1000uL) % 301 ? 2u : 1u);
}


inline unsigned long digits2_2_10(unsigned long d2)
{
   return (d2 * 301uL) / 1000uL;
}


template <class T>
void calc_log2(T& num, unsigned digits)
{
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename mpl::front<typename T::signed_types>::type si_type;

   //
   // String value with 1100 digits:
   //
   static const char* string_val = "0."
        "6931471805599453094172321214581765680755001343602552541206800094933936219696947156058633269964186875"
        "4200148102057068573368552023575813055703267075163507596193072757082837143519030703862389167347112335"
        "0115364497955239120475172681574932065155524734139525882950453007095326366642654104239157814952043740"
        "4303855008019441706416715186447128399681717845469570262716310645461502572074024816377733896385506952"
        "6066834113727387372292895649354702576265209885969320196505855476470330679365443254763274495125040606"
        "9438147104689946506220167720424524529612687946546193165174681392672504103802546259656869144192871608"
        "2938031727143677826548775664850856740776484514644399404614226031930967354025744460703080960850474866"
        "3852313818167675143866747664789088143714198549423151997354880375165861275352916610007105355824987941"
        "4729509293113897155998205654392871700072180857610252368892132449713893203784393530887748259701715591"
        "0708823683627589842589185353024363421436706118923678919237231467232172053401649256872747782344535347"
        "6481149418642386776774406069562657379600867076257199184734022651462837904883062033061144630073719489";
   //
   // Check if we can just construct from string:
   //
   if(digits  < 3640)  // 3640 binary digits ~ 1100 decimal digits
   {
      num = string_val;
      return;
   }
   //
   // We calculate log2 from using the formula:
   //
   // ln(2) = 3/4 SUM[n>=0] ((-1)^n * N!^2 / (2^n(2n+1)!))
   //
   // Numerator and denominator are calculated separately and then 
   // divided at the end, we also precalculate the terms up to n = 5
   // since these fit in a 32-bit integer anyway.
   //
   // See Gourdon, X., and Sebah, P. The logarithmic constant: log 2, Jan. 2004.
   // Also http://www.mpfr.org/algorithms.pdf.
   //
   num = static_cast<ui_type>(1180509120uL);
   T denom, next_term, temp;
   denom = static_cast<ui_type>(1277337600uL);
   next_term = static_cast<ui_type>(120uL);
   si_type sign = -1;

   ui_type limit = digits / 3 + 1;

   for(ui_type n = 6; n < limit; ++n)
   {
      temp = static_cast<ui_type>(2);
      eval_multiply(temp, ui_type(2 * n));
      eval_multiply(temp, ui_type(2 * n + 1));
      eval_multiply(num, temp);
      eval_multiply(denom, temp);
      sign = -sign;
      eval_multiply(next_term, n);
      eval_multiply(temp, next_term, next_term);
      if(sign < 0)
         temp.negate();
      eval_add(num, temp);
   }
   eval_multiply(denom, ui_type(4));
   eval_multiply(num, ui_type(3));
   INSTRUMENT_BACKEND(denom);
   INSTRUMENT_BACKEND(num);
   eval_divide(num, denom);
   INSTRUMENT_BACKEND(num);
}


template <class T>
void calc_e(T& result, unsigned digits)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type real_type;
   //
   // 1100 digits in string form:
   //
   const char* string_val = "2."
         "7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274"
         "2746639193200305992181741359662904357290033429526059563073813232862794349076323382988075319525101901"
         "1573834187930702154089149934884167509244761460668082264800168477411853742345442437107539077744992069"
         "5517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416"
         "9283681902551510865746377211125238978442505695369677078544996996794686445490598793163688923009879312"
         "7736178215424999229576351482208269895193668033182528869398496465105820939239829488793320362509443117"
         "3012381970684161403970198376793206832823764648042953118023287825098194558153017567173613320698112509"
         "9618188159304169035159888851934580727386673858942287922849989208680582574927961048419844436346324496"
         "8487560233624827041978623209002160990235304369941849146314093431738143640546253152096183690888707016"
         "7683964243781405927145635490613031072085103837505101157477041718986106873969655212671546889570350354"
         "0212340784981933432106817012100562788023519303322474501585390473041995777709350366041699732972508869";
   //
   // Check if we can just construct from string:
   //
   if(digits  < 3640) // 3640 binary digits ~ 1100 decimal digits
   {
      result = string_val;
      return;
   }

   T lim;
   lim = ui_type(1);
   eval_ldexp(lim, lim, digits);

   //
   // Standard evaluation from the definition of e: http://functions.wolfram.com/Constants/E/02/
   //
   result = ui_type(2);
   T denom;
   denom = ui_type(1);
   ui_type i = 2;
   do{
      eval_multiply(denom, i);
      eval_multiply(result, i);
      eval_add(result, ui_type(1));
      ++i;
   }while(denom.compare(lim) <= 0);
   eval_divide(result, denom);
}


template <class T>
void calc_pi(T& result, unsigned digits)
{
   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;
   typedef typename mpl::front<typename T::float_types>::type real_type;
   //
   // 1100 digits in string form:
   //
   const char* string_val = "3."
         "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
         "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
         "4428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273"
         "7245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094"
         "3305727036575959195309218611738193261179310511854807446237996274956735188575272489122793818301194912"
         "9833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132"
         "0005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235"
         "4201995611212902196086403441815981362977477130996051870721134999999837297804995105973173281609631859"
         "5024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303"
         "5982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989"
         "3809525720106548586327886593615338182796823030195203530185296899577362259941389124972177528347913152";
   //
   // Check if we can just construct from string:
   //
   if(digits  < 3640) // 3640 binary digits ~ 1100 decimal digits
   {
      result = string_val;
      return;
   }

   T a;
   a = ui_type(1);
   T b;
   T A(a);
   T B;
   B = real_type(0.5f);
   T D;
   D = real_type(0.25f);

   T lim;
   lim = ui_type(1);
   eval_ldexp(lim, lim, -(int)digits);

   //
   // This algorithm is from:
   // Schonhage, A., Grotefeld, A. F. W., and Vetter, E. Fast Algorithms: A Multitape Turing
   // Machine Implementation. BI Wissenschaftverlag, 1994.
   // Also described in MPFR's algorithm guide: http://www.mpfr.org/algorithms.pdf.
   //
   // Let:
   // a[0] = A[0] = 1
   // B[0] = 1/2
   // D[0] = 1/4
   // Then:
   // S[k+1] = (A[k]+B[k]) / 4
   // b[k] = sqrt(B[k])
   // a[k+1] = a[k]^2
   // B[k+1] = 2(A[k+1]-S[k+1])
   // D[k+1] = D[k] - 2^k(A[k+1]-B[k+1])
   // Stop when |A[k]-B[k]| <= 2^(k-p)
   // and PI = B[k]/D[k]

   unsigned k = 1;

   do
   {
      eval_add(result, A, B);
      eval_ldexp(result, result, -2);
      eval_sqrt(b, B);
      eval_add(a, b);
      eval_ldexp(a, a, -1);
      eval_multiply(A, a, a);
      eval_subtract(B, A, result);
      eval_ldexp(B, B, 1);
      eval_subtract(result, A, B);
      bool neg = eval_get_sign(result) < 0;
      if(neg)
         result.negate();
      if(result.compare(lim) <= 0)
         break;
      if(neg)
         result.negate();
      eval_ldexp(result, result, k - 1);
      eval_subtract(D, result);
      ++k;
      eval_ldexp(lim, lim, 1);
   }
   while(true);

   eval_divide(result, B, D);
}

   static void do_nothing()
   {
      init.do_nothing();
   }

      initializer()
      {
         F();
      }

      void do_nothing()const{}


template <class T>
const T& get_constant_ln2()
{
   static T result;
   static bool b = false;
   if(!b)
   {
      calc_log2(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value);
      b = true;
   }

   constant_initializer<T, &get_constant_ln2<T> >::do_nothing();

   return result;
}


template <class T>
const T& get_constant_e()
{
   static T result;
   static bool b = false;
   if(!b)
   {
      calc_e(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value);
      b = true;
   }

   constant_initializer<T, &get_constant_e<T> >::do_nothing();

   return result;
}


template <class T>
const T& get_constant_pi()
{
   static T result;
   static bool b = false;
   if(!b)
   {
      calc_pi(result, boost::multiprecision::detail::digits2<number<T, et_on> >::value);
      b = true;
   }

   constant_initializer<T, &get_constant_pi<T> >::do_nothing();

   return result;


template <class T>
void hyp0F1(T& result, const T& b, const T& x)
{
   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   // Compute the series representation of Hypergeometric0F1 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F1/06/01/01/
   // There are no checks on input range or parameter boundaries.

   T x_pow_n_div_n_fact(x);
   T pochham_b         (b);
   T bp                (b);

   eval_divide(result, x_pow_n_div_n_fact, pochham_b);
   eval_add(result, ui_type(1));

   si_type n;

   T tol;
   tol = ui_type(1);
   eval_ldexp(tol, tol, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value);
   eval_multiply(tol, result);
   if(eval_get_sign(tol) < 0)
      tol.negate();
   T term;

   static const unsigned series_limit = 
      boost::multiprecision::detail::digits2<number<T, et_on> >::value < 100
      ? 100 : boost::multiprecision::detail::digits2<number<T, et_on> >::value;
   // Series expansion of hyperg_0f1(; b; x).
   for(n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_increment(bp);
      eval_multiply(pochham_b, bp);

      eval_divide(term, x_pow_n_div_n_fact, pochham_b);
      eval_add(result, term);

      bool neg_term = eval_get_sign(term) < 0;
      if(neg_term)
         term.negate();
      if(term.compare(tol) <= 0)
         break;
   }

   if(n >= series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H0F1 Failed to Converge"));
}



template <class T>
void eval_sin(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The sin function is only valid for floating point types.");
   if(&result == &x)
   {
      T temp;
      eval_sin(temp, x);
      result = temp;
      return;
   }

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   switch(eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   case FP_ZERO:
      result = ui_type(0);
      return;
   default: ;
   }

   // Local copy of the argument
   T xx = x;

   // Analyze and prepare the phase of the argument.
   // Make a local, positive copy of the argument, xx.
   // The argument xx will be reduced to 0 <= xx <= pi/2.
   bool b_negate_sin = false;

   if(eval_get_sign(x) < 0)
   {
      xx.negate();
      b_negate_sin = !b_negate_sin;
   }

   T n_pi, t;
   // Remove even multiples of pi.
   if(xx.compare(get_constant_pi<T>()) > 0)
   {
      eval_divide(n_pi, xx, get_constant_pi<T>());
      eval_trunc(n_pi, n_pi);
      t = ui_type(2);
      eval_fmod(t, n_pi, t);
      const bool b_n_pi_is_even = eval_get_sign(t) == 0;
      eval_multiply(n_pi, get_constant_pi<T>());
      eval_subtract(xx, n_pi);

      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));

      // Adjust signs if the multiple of pi is not even.
      if(!b_n_pi_is_even)
      {
         b_negate_sin = !b_negate_sin;
      }
   }

   // Reduce the argument to 0 <= xx <= pi/2.
   eval_ldexp(t, get_constant_pi<T>(), -1);
   if(xx.compare(t) > 0)
   {
      eval_subtract(xx, get_constant_pi<T>(), xx);
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
   }

   eval_subtract(t, xx);
   const bool b_zero    = eval_get_sign(xx) == 0;
   const bool b_pi_half = eval_get_sign(t) == 0;

   // Check if the reduced argument is very close to 0 or pi/2.
   const bool    b_near_zero    = xx.compare(fp_type(1e-1)) < 0;
   const bool    b_near_pi_half = t.compare(fp_type(1e-1)) < 0;;

   if(b_zero)
   {
      result = ui_type(0);
   }
   else if(b_pi_half)
   {
      result = ui_type(1);
   }
   else if(b_near_zero)
   {
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(1.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
      eval_multiply(result, xx);
   }
   else if(b_near_pi_half)
   {
      eval_multiply(t, t);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(0.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
   }
   else
   {
      // Scale to a small argument for an efficient Taylor series,
      // implemented as a hypergeometric function. Use a standard
      // divide by three identity a certain number of times.
      // Here we use division by 3^9 --> (19683 = 3^9).

      static const si_type n_scale = 9;
      static const si_type n_three_pow_scale = static_cast<si_type>(19683L);

      eval_divide(xx, n_three_pow_scale);

      // Now with small arguments, we are ready for a series expansion.
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      T t2;
      t2 = fp_type(1.5);
      hyp0F1(result, t2, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
      eval_multiply(result, xx);

      // Convert back using multiple angle identity.
      for(boost::int32_t k = static_cast<boost::int32_t>(0); k < n_scale; k++)
      {
         // Rescale the cosine value using the multiple angle identity.
         eval_multiply(t2, result, ui_type(3));
         eval_multiply(t, result, result);
         eval_multiply(t, result);
         eval_multiply(t, ui_type(4));
         eval_subtract(result, t2, t);
      }
   }

   if(b_negate_sin)
      result.negate();
}


template <class T>
void eval_cos(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The cos function is only valid for floating point types.");
   if(&result == &x)
   {
      T temp;
      eval_cos(temp, x);
      result = temp;
      return;
   }

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   switch(eval_fpclassify(x))
   {
   case FP_INFINITE:
   case FP_NAN:
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   case FP_ZERO:
      result = ui_type(1);
      return;
   default: ;
   }

   // Local copy of the argument
   T xx = x;

   // Analyze and prepare the phase of the argument.
   // Make a local, positive copy of the argument, xx.
   // The argument xx will be reduced to 0 <= xx <= pi/2.
   bool b_negate_cos = false;

   if(eval_get_sign(x) < 0)
   {
      xx.negate();
   }

   T n_pi, t;
   // Remove even multiples of pi.
   if(xx.compare(get_constant_pi<T>()) > 0)
   {
      eval_divide(t, xx, get_constant_pi<T>());
      eval_trunc(n_pi, t);
      BOOST_MATH_INSTRUMENT_CODE(n_pi.str(0, std::ios_base::scientific));
      eval_multiply(t, n_pi, get_constant_pi<T>());
      BOOST_MATH_INSTRUMENT_CODE(t.str(0, std::ios_base::scientific));
      eval_subtract(xx, t);
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));

      // Adjust signs if the multiple of pi is not even.
      t = ui_type(2);
      eval_fmod(t, n_pi, t);
      const bool b_n_pi_is_even = eval_get_sign(t) == 0;

      if(!b_n_pi_is_even)
      {
         b_negate_cos = !b_negate_cos;
      }
   }

   // Reduce the argument to 0 <= xx <= pi/2.
   eval_ldexp(t, get_constant_pi<T>(), -1);
   int com = xx.compare(t);
   if(com > 0)
   {
      eval_subtract(xx, get_constant_pi<T>(), xx);
      b_negate_cos = !b_negate_cos;
      BOOST_MATH_INSTRUMENT_CODE(xx.str(0, std::ios_base::scientific));
   }

   const bool b_zero    = eval_get_sign(xx) == 0;
   const bool b_pi_half = com == 0;

   // Check if the reduced argument is very close to 0 or pi/2.
   const bool    b_near_zero    = xx.compare(fp_type(1e-4)) < 0;
   eval_subtract(t, xx);
   const bool    b_near_pi_half = t.compare(fp_type(1e-4)) < 0;

   if(b_zero)
   {
      result = si_type(1);
   }
   else if(b_pi_half)
   {
      result = si_type(0);
   }
   else if(b_near_zero)
   {
      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      n_pi = fp_type(0.5f);
      hyp0F1(result, n_pi, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
   }
   else if(b_near_pi_half)
   {
      T t2(t);
      eval_multiply(t, t);
      eval_divide(t, si_type(-4));
      n_pi = fp_type(1.5f);
      hyp0F1(result, n_pi, t);
      eval_multiply(result, t2);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));
   }
   else
   {
      // Scale to a small argument for an efficient Taylor series,
      // implemented as a hypergeometric function. Use a standard
      // divide by three identity a certain number of times.
      // Here we use division by 3^9 --> (19683 = 3^9).

      static const ui_type n_scale           = 9;
      static const ui_type n_three_pow_scale = 19683;
      eval_divide(xx, n_three_pow_scale);

      eval_multiply(t, xx, xx);
      eval_divide(t, si_type(-4));
      n_pi = fp_type(0.5f);

      // Now with small arguments, we are ready for a series expansion.
      hyp0F1(result, n_pi, t);
      BOOST_MATH_INSTRUMENT_CODE(result.str(0, std::ios_base::scientific));

      // Convert back using multiple angle identity.
      for(ui_type k = 0; k < n_scale; k++)
      {
         eval_multiply(t, result, result);
         eval_multiply(t, result);
         eval_multiply(t, ui_type(4));
         eval_multiply(result, si_type(-3));
         eval_add(result, t);
      }
   }
   if(b_negate_cos)
      result.negate();
}


template <class T>
void eval_tan(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The tan function is only valid for floating point types.");
   if(&result == &x)
   {
      T temp;
      eval_tan(temp, x);
      result = temp;
      return;
   }
   T t;
   eval_sin(result, x);
   eval_cos(t, x);
   eval_divide(result, t);
}


template <class T>
void hyp2F1(T& result, const T& a, const T& b, const T& c, const T& x)
{
  // Compute the series representation of hyperg_2f1 taken from
  // Abramowitz and Stegun 15.1.1.
  // There are no checks on input range or parameter boundaries.

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   T x_pow_n_div_n_fact(x);
   T pochham_a         (a);
   T pochham_b         (b);
   T pochham_c         (c);
   T ap                (a);
   T bp                (b);
   T cp                (c);

   eval_multiply(result, pochham_a, pochham_b);
   eval_divide(result, pochham_c);
   eval_multiply(result, x_pow_n_div_n_fact);
   eval_add(result, ui_type(1));

   T lim;
   eval_ldexp(lim, result, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value);

   if(eval_get_sign(lim) < 0)
      lim.negate();

   ui_type n;
   T term;

   static const unsigned series_limit = 
      boost::multiprecision::detail::digits2<number<T, et_on> >::value < 100
      ? 100 : boost::multiprecision::detail::digits2<number<T, et_on> >::value;
   // Series expansion of hyperg_2f1(a, b; c; x).
   for(n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);

      eval_increment(ap);
      eval_multiply(pochham_a, ap);
      eval_increment(bp);
      eval_multiply(pochham_b, bp);
      eval_increment(cp);
      eval_multiply(pochham_c, cp);

      eval_multiply(term, pochham_a, pochham_b);
      eval_divide(term, pochham_c);
      eval_multiply(term, x_pow_n_div_n_fact);
      eval_add(result, term);

      if(eval_get_sign(term) < 0)
         term.negate();
      if(lim.compare(term) >= 0)
         break;
   }
   if(n > series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H2F1 failed to converge."));
}


template <class T>
void eval_asin(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The asin function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   if(&result == &x)
   {
      T t(x);
      eval_asin(result, t);
      return;
   }

   switch(eval_fpclassify(x))
   {
   case FP_NAN:
   case FP_INFINITE:
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   case FP_ZERO:
      result = ui_type(0);
      return;
   default: ;
   }

   const bool b_neg = eval_get_sign(x) < 0;

   T xx(x);
   if(b_neg)
      xx.negate();

   int c = xx.compare(ui_type(1));
   if(c > 0)
   {
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   }
   else if(c == 0)
   {
      result = get_constant_pi<T>();
      eval_ldexp(result, result, -1);
      if(b_neg)
         result.negate();
      return;
   }

   if(xx.compare(fp_type(1e-4)) < 0)
   {
      // http://functions.wolfram.com/ElementaryFunctions/ArcSin/26/01/01/
      eval_multiply(xx, xx);
      T t1, t2;
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      hyp2F1(result, t1, t1, t2, xx);
      eval_multiply(result, x);
      return;
   }
   else if(xx.compare(fp_type(1 - 1e-4f)) > 0)
   {
      T dx1;
      T t1, t2;
      eval_subtract(dx1, ui_type(1), xx);
      t1 = fp_type(0.5f);
      t2 = fp_type(1.5f);
      eval_ldexp(dx1, dx1, -1);
      hyp2F1(result, t1, t1, t2, dx1);
      eval_ldexp(dx1, dx1, 2);
      eval_sqrt(t1, dx1);
      eval_multiply(result, t1);
      eval_ldexp(t1, get_constant_pi<T>(), -1);
      result.negate();
      eval_add(result, t1);
      if(b_neg)
         result.negate();
      return;
   }

   // Get initial estimate using standard math function asin.
   double dd;
   eval_convert_to(&dd, xx);

   result = fp_type(std::asin(dd));

   // Newton-Raphson iteration
   while(true)
   {
      T s, c;
      eval_sin(s, result);
      eval_cos(c, result);
      eval_subtract(s, xx);
      eval_divide(s, c);
      eval_subtract(result, s);

      T lim;
      eval_ldexp(lim, result, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value);
      if(eval_get_sign(s) < 0)
         s.negate();
      if(eval_get_sign(lim) < 0)
         lim.negate();
      if(lim.compare(s) >= 0)
         break;
   }
   if(b_neg)
      result.negate();
}


template <class T>
inline void eval_acos(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The acos function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;

   switch(eval_fpclassify(x))
   {
   case FP_NAN:
   case FP_INFINITE:
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   case FP_ZERO:
      result = get_constant_pi<T>();
      eval_ldexp(result, result, -1); // divide by two.
      return;
   }

   eval_abs(result, x);
   int c = result.compare(ui_type(1));

   if(c > 0)
   {
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   }
   else if(c == 0)
   {
      if(eval_get_sign(x) < 0)
         result = get_constant_pi<T>();
      else
         result = ui_type(0);
      return;
   }

   eval_asin(result, x);
   T t;
   eval_ldexp(t, get_constant_pi<T>(), -1);
   eval_subtract(result, t);
   result.negate();
}


template <class T>
void eval_atan(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The atan function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   switch(eval_fpclassify(x))
   {
   case FP_NAN:
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   case FP_ZERO:
      result = ui_type(0);
      return;
   case FP_INFINITE:
      if(eval_get_sign(x) < 0)
      {
         eval_ldexp(result, get_constant_pi<T>(), -1);
         result.negate();
      }
      else
         eval_ldexp(result, get_constant_pi<T>(), -1);
      return;
   default: ;
   }

   const bool b_neg = eval_get_sign(x) < 0;

   T xx(x);
   if(b_neg)
      xx.negate();

   if(xx.compare(fp_type(0.1)) < 0)
   {
      T t1, t2, t3;
      t1 = ui_type(1);
      t2 = fp_type(0.5f);
      t3 = fp_type(1.5f);
      eval_multiply(xx, xx);
      xx.negate();
      hyp2F1(result, t1, t2, t3, xx);
      eval_multiply(result, x);
      return;
   }

   if(xx.compare(fp_type(10)) > 0)
   {
      T t1, t2, t3;
      t1 = fp_type(0.5f);
      t2 = ui_type(1u);
      t3 = fp_type(1.5f);
      eval_multiply(xx, xx);
      eval_divide(xx, si_type(-1), xx);
      hyp2F1(result, t1, t2, t3, xx);
      eval_divide(result, x);
      if(!b_neg)
         result.negate();
      eval_ldexp(t1, get_constant_pi<T>(), -1);
      eval_add(result, t1);
      if(b_neg)
         result.negate();
      return;
   }


   // Get initial estimate using standard math function atan.
   fp_type d;
   eval_convert_to(&d, xx);
   result = fp_type(std::atan(d));

   // Newton-Raphson iteration
   static const boost::int32_t double_digits10_minus_a_few = std::numeric_limits<double>::digits10 - 3;

   T s, c, t;
   for(boost::int32_t digits = double_digits10_minus_a_few; digits <= std::numeric_limits<number<T, et_on> >::digits10; digits *= 2)
   {
      eval_sin(s, result);
      eval_cos(c, result);
      eval_multiply(t, xx, c);
      eval_subtract(t, s);
      eval_multiply(s, t, c);
      eval_add(result, s);
   }
   if(b_neg)
      result.negate();
}


template <class T>
void eval_atan2(T& result, const T& y, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The atan2 function is only valid for floating point types.");
   if(&result == &y)
   {
      T temp(y);
      eval_atan2(result, temp, x);
      return;
   }
   else if(&result == &x)
   {
      T temp(x);
      eval_atan2(result, y, temp);
      return;
   }

   typedef typename boost::multiprecision::detail::canonical<boost::int32_t, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<boost::uint32_t, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   switch(eval_fpclassify(y))
   {
   case FP_NAN:
      result = y;
      return;
   case FP_ZERO:
      {
         int c = eval_get_sign(x);
         if(c < 0)
            result = get_constant_pi<T>();
         else if(c >= 0)
            result = ui_type(0); // Note we allow atan2(0,0) to be zero, even though it's mathematically undefined
         return;
      }
   case FP_INFINITE:
      {
         if(eval_fpclassify(x) == FP_INFINITE)
         {
            result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
         }
         else
         {
            eval_ldexp(result, get_constant_pi<T>(), -1);
            if(eval_get_sign(y) < 0)
               result.negate();
         }
         return;
      }
   }

   switch(eval_fpclassify(x))
   {
   case FP_NAN:
      result = x;
      return;
   case FP_ZERO:
      {
         eval_ldexp(result, get_constant_pi<T>(), -1);
         if(eval_get_sign(y) < 0)
            result.negate();
         return;
      }
   case FP_INFINITE:
      if(eval_get_sign(x) > 0)
         result = ui_type(0);
      else
         result = get_constant_pi<T>();
      if(eval_get_sign(y) < 0)
         result.negate();
      return;
   }

   T xx;
   eval_divide(xx, y, x);
   if(eval_get_sign(xx) < 0)
      xx.negate();

   eval_atan(result, xx);

   // Determine quadrant (sign) based on signs of x, y
   const bool y_neg = eval_get_sign(y) < 0;
   const bool x_neg = eval_get_sign(x) < 0;

   if(y_neg != x_neg)
      result.negate();

   if(x_neg)
   {
      if(y_neg)
         eval_subtract(result, get_constant_pi<T>());
      else
         eval_add(result, get_constant_pi<T>());
   }
}


template<typename T, typename U> 
inline void pow_imp(T& result, const T& t, const U& p, const mpl::false_&)
{
   // Compute the pure power of typename T t^p.
   // Use the S-and-X binary method, as described in
   // D. E. Knuth, "The Art of Computer Programming", Vol. 2,
   // Section 4.6.3 . The resulting computational complexity
   // is order log2[abs(p)].

   typedef typename boost::multiprecision::detail::canonical<U, T>::type int_type;

   if(&result == &t)
   {
      T temp;
      pow_imp(temp, t, p, mpl::false_());
      result = temp;
      return;
   }

   // This will store the result.
   if(U(p % U(2)) != U(0))
   {
      result = t;
   }
   else
      result = int_type(1);

   U p2(p);

   // The variable x stores the binary powers of t.
   T x(t);

   while(U(p2 /= 2) != U(0))
   {
      // Square x for each binary power.
      eval_multiply(x, x);

      const bool has_binary_power = (U(p2 % U(2)) != U(0));

      if(has_binary_power)
      {
         // Multiply the result with each binary power contained in the exponent.
         eval_multiply(result, x);
      }
   }
}


template <class T>
void hyp0F0(T& H0F0, const T& x)
{
   // Compute the series representation of Hypergeometric0F0 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric0F0/06/01/
   // There are no checks on input range or parameter boundaries.

   typedef typename mpl::front<typename T::unsigned_types>::type ui_type;

   BOOST_ASSERT(&H0F0 != &x);
   long tol = boost::multiprecision::detail::digits2<number<T, et_on> >::value;
   T t;

   T x_pow_n_div_n_fact(x);

   eval_add(H0F0, x_pow_n_div_n_fact, ui_type(1));

   T lim;
   eval_ldexp(lim, H0F0, 1 - tol);
   if(eval_get_sign(lim) < 0)
      lim.negate();

   ui_type n;

   static const unsigned series_limit = 
      boost::multiprecision::detail::digits2<number<T, et_on> >::value < 100
      ? 100 : boost::multiprecision::detail::digits2<number<T, et_on> >::value;
   // Series expansion of hyperg_0f0(; ; x).
   for(n = 2; n < series_limit; ++n)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_add(H0F0, x_pow_n_div_n_fact);
      bool neg = eval_get_sign(x_pow_n_div_n_fact) < 0;
      if(neg)
         x_pow_n_div_n_fact.negate();
      if(lim.compare(x_pow_n_div_n_fact) > 0)
         break;
      if(neg)
         x_pow_n_div_n_fact.negate();
   }
   if(n >= series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H0F0 failed to converge"));
}


template <class T>
void hyp1F0(T& H1F0, const T& a, const T& x)
{
   // Compute the series representation of Hypergeometric1F0 taken from
   // http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F0/06/01/01/
   // and also see the corresponding section for the power function (i.e. x^a).
   // There are no checks on input range or parameter boundaries.

   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   BOOST_ASSERT(&H1F0 != &x);
   BOOST_ASSERT(&H1F0 != &a);

   T x_pow_n_div_n_fact(x);
   T pochham_a         (a);
   T ap                (a);

   eval_multiply(H1F0, pochham_a, x_pow_n_div_n_fact);
   eval_add(H1F0, si_type(1));
   T lim;
   eval_ldexp(lim, H1F0, 1 - boost::multiprecision::detail::digits2<number<T, et_on> >::value);
   if(eval_get_sign(lim) < 0)
      lim.negate();

   si_type n;
   T term, part;

   static const unsigned series_limit = 
      boost::multiprecision::detail::digits2<number<T, et_on> >::value < 100
      ? 100 : boost::multiprecision::detail::digits2<number<T, et_on> >::value;
   // Series expansion of hyperg_1f0(a; ; x).
   for(n = 2; n < series_limit; n++)
   {
      eval_multiply(x_pow_n_div_n_fact, x);
      eval_divide(x_pow_n_div_n_fact, n);
      eval_increment(ap);
      eval_multiply(pochham_a, ap);
      eval_multiply(term, pochham_a, x_pow_n_div_n_fact);
      eval_add(H1F0, term);
      if(eval_get_sign(term) < 0)
         term.negate();
      if(lim.compare(term) >= 0)
         break;
   }
   if(n >= series_limit)
      BOOST_THROW_EXCEPTION(std::runtime_error("H1F0 failed to converge"));
}


template <class T>
void eval_exp(T& result, const T& x)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The exp function is only valid for floating point types.");
   if(&x == &result)
   {
      T temp;
      eval_exp(temp, x);
      result = temp;
      return;
   }
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename boost::multiprecision::detail::canonical<float, T>::type float_type;

   // Handle special arguments.
   int type = eval_fpclassify(x);
   bool isneg = eval_get_sign(x) < 0;
   if(type == FP_NAN)
   {
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
      return;
   }
   else if(type == FP_INFINITE)
   {
      result = x;
      if(isneg)
         result = ui_type(0u);
      else 
         result = x;
      return;
   }
   else if(type == FP_ZERO)
   {
      result = ui_type(1);
      return;
   }

   // Get local copy of argument and force it to be positive.
   T xx = x;
   T exp_series;
   if(isneg)
      xx.negate();

   // Check the range of the argument.
   static const canonical_exp_type maximum_arg_for_exp = std::numeric_limits<number<T, et_on> >::max_exponent == 0 ? (std::numeric_limits<long>::max)() : std::numeric_limits<number<T, et_on> >::max_exponent;

   if(xx.compare(maximum_arg_for_exp) >= 0)
   {
      // Overflow / underflow
      if(isneg)
         result = ui_type(0);
      else
         result = std::numeric_limits<number<T, et_on> >::has_infinity ? std::numeric_limits<number<T, et_on> >::infinity().backend() : (std::numeric_limits<number<T, et_on> >::max)().backend();
      return;
   }
   if(xx.compare(si_type(1)) <= 0)
   {
      //
      // Use series for exp(x) - 1:
      //
      T lim = std::numeric_limits<number<T, et_on> >::epsilon().backend();
      unsigned k = 2;
      exp_series = xx;
      result = si_type(1);
      if(isneg)
         eval_subtract(result, exp_series);
      else
         eval_add(result, exp_series);
      eval_multiply(exp_series, xx);
      eval_divide(exp_series, ui_type(k));
      eval_add(result, exp_series);
      while(exp_series.compare(lim) > 0)
      {
         ++k;
         eval_multiply(exp_series, xx);
         eval_divide(exp_series, ui_type(k));
         if(isneg && (k&1))
            eval_subtract(result, exp_series);
         else
            eval_add(result, exp_series);
      }
      return;
   }

   // Check for pure-integer arguments which can be either signed or unsigned.
   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type ll;
   eval_trunc(exp_series, x);
   eval_convert_to(&ll, exp_series);
   if(x.compare(ll) == 0)
   {
      detail::pow_imp(result, get_constant_e<T>(), ll, mpl::true_());
      return;
   }

   // The algorithm for exp has been taken from MPFUN.
   // exp(t) = [ (1 + r + r^2/2! + r^3/3! + r^4/4! ...)^p2 ] * 2^n
   // where p2 is a power of 2 such as 2048, r = t_prime / p2, and
   // t_prime = t - n*ln2, with n chosen to minimize the absolute
   // value of t_prime. In the resulting Taylor series, which is
   // implemented as a hypergeometric function, |r| is bounded by
   // ln2 / p2. For small arguments, no scaling is done.

   // Compute the exponential series of the (possibly) scaled argument.

   eval_divide(result, xx, get_constant_ln2<T>());
   exp_type n;
   eval_convert_to(&n, result);

   // The scaling is 2^11 = 2048.
   static const si_type p2 = static_cast<si_type>(si_type(1) << 11);

   eval_multiply(exp_series, get_constant_ln2<T>(), static_cast<canonical_exp_type>(n));
   eval_subtract(exp_series, xx);
   eval_divide(exp_series, p2);
   exp_series.negate();
   hyp0F0(result, exp_series);

   detail::pow_imp(exp_series, result, p2, mpl::true_());
   result = ui_type(1);
   eval_ldexp(result, result, n);
   eval_multiply(exp_series, result);

   if(isneg)
      eval_divide(result, ui_type(1), exp_series);
   else
      result = exp_series;
}


template <class T>
void eval_log(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The log function is only valid for floating point types.");
   //
   // We use a variation of http://dlmf.nist.gov/4.45#i
   // using frexp to reduce the argument to x * 2^n,
   // then let y = x - 1 and compute:
   // log(x) = log(2) * n + log1p(1 + y)
   //
   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   exp_type e;
   T t;
   eval_frexp(t, arg, &e);
   bool alternate = false;

   if(t.compare(fp_type(2) / fp_type(3)) <= 0)
   {
      alternate = true;
      eval_ldexp(t, t, 1);
      --e;
   }
   
   eval_multiply(result, get_constant_ln2<T>(), canonical_exp_type(e));
   INSTRUMENT_BACKEND(result);
   eval_subtract(t, ui_type(1)); /* -0.3 <= t <= 0.3 */
   if(!alternate)
      t.negate(); /* 0 <= t <= 0.33333 */
   T pow = t;
   T lim;
   T t2;

   if(alternate)
      eval_add(result, t);
   else
      eval_subtract(result, t);

   eval_multiply(lim, result, std::numeric_limits<number<T, et_on> >::epsilon().backend());
   if(eval_get_sign(lim) < 0)
      lim.negate();
   INSTRUMENT_BACKEND(lim);

   ui_type k = 1;
   do
   {
      ++k;
      eval_multiply(pow, t);
      eval_divide(t2, pow, k);
      INSTRUMENT_BACKEND(t2);
      if(alternate && ((k & 1) != 0))
         eval_add(result, t2);
      else
         eval_subtract(result, t2);
      INSTRUMENT_BACKEND(result);
   }while(lim.compare(t2) < 0);
}


template <class T>
const T& get_constant_log10()
{
   static T result;
   static bool b = false;
   if(!b)
   {
      typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
      T ten;
      ten = ui_type(10u);
      eval_log(result, ten);
   }

   constant_initializer<T, &get_constant_log10<T> >::do_nothing();

   return result;
}


template <class T>
void eval_log10(T& result, const T& arg)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The log10 function is only valid for floating point types.");
   eval_log(result, arg);
   eval_divide(result, get_constant_log10<T>());
}


template<typename T> 
inline void eval_pow(T& result, const T& x, const T& a)
{
   BOOST_STATIC_ASSERT_MSG(number_category<T>::value == number_kind_floating_point, "The pow function is only valid for floating point types.");
   typedef typename boost::multiprecision::detail::canonical<int, T>::type si_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned, T>::type ui_type;
   typedef typename T::exponent_type exp_type;
   typedef typename boost::multiprecision::detail::canonical<exp_type, T>::type canonical_exp_type;
   typedef typename mpl::front<typename T::float_types>::type fp_type;

   if((&result == &x) || (&result == &a))
   {
      T t;
      eval_pow(t, x, a);
      result = t;
      return;
   }

   if(a.compare(si_type(1)) == 0)
   {
      result = x;
      return;
   }

   int type = eval_fpclassify(x);

   switch(type)
   {
   case FP_INFINITE:
      result = x;
      return;
   case FP_ZERO:
      result = si_type(1);
      return;
   case FP_NAN:
      result = x;
      return;
   default: ;
   }

   if(eval_get_sign(a) == 0)
   {
      result = si_type(1);
      return;
   }

   if(a.compare(si_type(-1)) < 0)
   {
      T t, da;
      t = a;
      t.negate();
      eval_pow(da, x, t);
      eval_divide(result, si_type(1), da);
      return;
   }
   
   bool bo_a_isint = false;
   typename boost::multiprecision::detail::canonical<boost::intmax_t, T>::type an;
   T fa;
   try
   {
      eval_convert_to(&an, a);
      if(a.compare(an) == 0)
      {
         detail::pow_imp(result, x, an, mpl::true_());
         return;
      }
   }
   catch(const std::exception&)
   {
      // conversion failed, just fall through, value is not an integer.
      an = (std::numeric_limits<boost::intmax_t>::max)();
   }

   if((eval_get_sign(x) < 0) && !bo_a_isint)
   {
      result = std::numeric_limits<number<T, et_on> >::quiet_NaN().backend();
   }

   T t, da;

   eval_subtract(da, a, an);

   if((x.compare(fp_type(0.5)) >= 0) && (x.compare(fp_type(0.9)) < 0))
   {
      if(a.compare(fp_type(1e-5f)) <= 0)
      {
         // Series expansion for small a.
         eval_log(t, x);
         eval_multiply(t, a);
         hyp0F0(result, t);
         return;
      }
      else
      {
         // Series expansion for moderately sized x. Note that for large power of a,
         // the power of the integer part of a is calculated using the pown function.
         if(an)
         {
            da.negate();
            t = si_type(1);
            eval_subtract(t, x);
            hyp1F0(result, da, t);
            detail::pow_imp(t, x, an, mpl::true_());
            eval_multiply(result, t);
         }
         else
         {
            da = a;
            da.negate();
            t = si_type(1);
            eval_subtract(t, x);
            hyp1F0(result, da, t);
         }
      }
   }
   else
   {
      // Series expansion for pow(x, a). Note that for large power of a, the power
      // of the integer part of a is calculated using the pown function.
      if(an)
      {
         eval_log(t, x);
         eval_multiply(t, da);
         eval_exp(result, t);
         detail::pow_imp(t, x, an, mpl::true_());
         eval_multiply(result, t);
      }
      else
      {
         eval_log(t, x);
         eval_multiply(t, a);
         eval_exp(result, t);
      }
   }
}


inline limb_type block_multiplier(unsigned count)
{
   static const limb_type values[digits_per_block_10]
      = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
   BOOST_ASSERT(count < digits_per_block_10);
   return values[count];
}


template <class T>
inline void minmax(const T& a, const T& b, T& aa, T& bb)
{
   if(a < b)
   {
      aa = a;
      bb = b;
   }
   else
   {
      aa = b;
      bb = a;
   }
}


inline void raise_overflow(std::string op)
{
   BOOST_THROW_EXCEPTION(std::overflow_error("overflow in " + op));
}

inline void raise_add_overflow()
{
   raise_overflow("addition");
}

inline void raise_subtract_overflow()
{
   BOOST_THROW_EXCEPTION(std::range_error("Subtraction resulted in a negative value, but the type is unsigned"));
}

inline void raise_mul_overflow()
{
   raise_overflow("multiplication");
}

inline void raise_div_overflow()
{
   raise_overflow("division");
}


template <class A>
inline A checked_add_imp(A a, A b, const mpl::true_&)
{
   if(a > 0)
   {
      if((b > 0) && ((integer_traits<A>::const_max - b) < a))
         raise_add_overflow();
   }
   else
   {
      if((b < 0) && ((integer_traits<A>::const_min - b) > a))
         raise_add_overflow();
   }
   return a + b;
}

template <class A>
inline A checked_add(A a, A b, const mpl::int_<checked>&)
{
   return checked_add_imp(a, b, boost::is_signed<A>());
}


template <class A>
inline A checked_subtract_imp(A a, A b, const mpl::true_&)
{
   if(a > 0)
   {
      if((b < 0) && ((integer_traits<A>::const_max + b) < a))
         raise_subtract_overflow();
   }
   else
   {
      if((b > 0) && ((integer_traits<A>::const_min + b) > a))
         raise_subtract_overflow();
   }
   return a - b;
}

template <class A>
inline A checked_subtract(A a, A b, const mpl::int_<checked>&)
{
   return checked_subtract_imp(a, b, boost::is_signed<A>());
}


template <class A>
inline A checked_multiply(A a, A b, const mpl::int_<checked>&)
{
   BOOST_MP_USING_ABS
   if(a && (integer_traits<A>::const_max / abs(a) < abs(b)))
      raise_mul_overflow();
   return a * b;
}


template <class A>
inline A checked_divide(A a, A b, const mpl::int_<checked>&)
{
   if(b == 0)
      raise_div_overflow();
   return a / b;
}


template <class A>
inline A checked_left_shift(A a, unsigned long long shift, const mpl::int_<checked>&)
{
   if(a && shift)
   {
      if((shift > sizeof(A) * CHAR_BIT) || (a >> (sizeof(A) * CHAR_BIT - shift)))
         BOOST_THROW_EXCEPTION(std::overflow_error("Shift out of range"));
   }
   return a << shift;
}


template <class R, class CppInt>
void check_in_range(const CppInt& val, const mpl::int_<checked>&)
{
   typedef typename boost::multiprecision::detail::canonical<R, CppInt>::type cast_type;
   if(val.sign())
   {
      if(val.compare(static_cast<cast_type>((std::numeric_limits<R>::min)())) < 0)
         BOOST_THROW_EXCEPTION(std::overflow_error("Could not convert to the target type - -value is out of range."));
   }
   else
   {
      if(val.compare(static_cast<cast_type>((std::numeric_limits<R>::max)())) > 0)
         BOOST_THROW_EXCEPTION(std::overflow_error("Could not convert to the target type - -value is out of range."));
   }
}


template <class CppInt1, class CppInt2, class CppInt3>
void divide_unsigned_helper(
   CppInt1* result, 
   const CppInt2& x, 
   const CppInt3& y, 
   CppInt1& r)
{
   if(((void*)result == (void*)&x) || ((void*)&r == (void*)&x))
   {
      CppInt2 t(x);
      divide_unsigned_helper(result, t, y, r);
      return;
   }
   if(((void*)result == (void*)&y) || ((void*)&r == (void*)&y))
   {
      CppInt3 t(y);
      divide_unsigned_helper(result, x, t, r);
      return;
   }

   /*
    Very simple, fairly braindead long division.
    Start by setting the remainder equal to x, and the
    result equal to 0.  Then in each loop we calculate our
    "best guess" for how many times y divides into r,
    add our guess to the result, and subtract guess*y
    from the remainder r.  One wrinkle is that the remainder
    may go negative, in which case we subtract the current guess
    from the result rather than adding.  The value of the guess
    is determined by dividing the most-significant-limb of the
    current remainder by the most-significant-limb of y.

    Note that there are more efficient algorithms than this
    available, in particular see Knuth Vol 2.  However for small
    numbers of limbs this generally outperforms the alternatives
    and avoids the normalisation step which would require extra storage.
    */


   using default_ops::eval_subtract;

   if(result == &r)
   {
      CppInt1 rem;
      divide_unsigned_helper(result, x, y, rem);
      r = rem;
      return;
   }

   //
   // Find the most significant words of numerator and denominator.
   //
   limb_type y_order = y.size() - 1;

   if(y_order == 0)
   {
      //
      // Only a single non-zero limb in the denominator, in this case
      // we can use a specialized divide-by-single-limb routine which is
      // much faster.  This also handles division by zero:
      //
      divide_unsigned_helper(result, x, y.limbs()[y_order], r);
      return;
   }

   typename CppInt2::const_limb_pointer px = x.limbs();
   typename CppInt3::const_limb_pointer py = y.limbs();

   limb_type r_order = x.size() - 1;
   if((r_order == 0) && (*px == 0))
   {
      // x is zero, so is the result:
      r = x;
      if(result)
         *result = x;
      return;
   }

   r = x;
   r.sign(false);
   if(result)
      *result = static_cast<limb_type>(0u);
   //
   // Check if the remainder is already less than the divisor, if so
   // we already have the result.  Note we try and avoid a full compare
   // if we can:
   //
   if(r_order <= y_order)
   {
      if((r_order < y_order) || (r.compare_unsigned(y) < 0))
      {
         return;
      }
   }

   CppInt1 t;
   bool r_neg = false;

   //
   // See if we can short-circuit long division, and use basic arithmetic instead:
   //
   if(r_order == 0)
   {
      if(result)
      {
         *result = px[0] / py[0];
      }
      r = px[0] % py[0];
      return;
   }
   else if(r_order == 1)
   {
      double_limb_type a, b;
      a = (static_cast<double_limb_type>(px[1]) << CppInt1::limb_bits) | px[0];
      b = y_order ? 
         (static_cast<double_limb_type>(py[1]) << CppInt1::limb_bits) | py[0] 
         : py[0];
      if(result)
      {
         *result = a / b;
      }
      r = a % b;
      return;
   }
   //
   // prepare result:
   //
   if(result)
      result->resize(1 + r_order - y_order, 1 + r_order - y_order);
   typename CppInt1::const_limb_pointer prem = r.limbs();
   // This is initialised just to keep the compiler from emitting useless warnings later on:
   typename CppInt1::limb_pointer pr 
      = typename CppInt1::limb_pointer();
   if(result)
   {
      pr = result->limbs();
      for(unsigned i = 1; i < 1 + r_order - y_order; ++i)
         pr[i] = 0;
   }
   bool first_pass = true;

   do
   {
      //
      // Calculate our best guess for how many times y divides into r:
      //
      limb_type guess;
      if((prem[r_order] <= py[y_order]) && (r_order > 0))
      {
         double_limb_type a, b, v;
         a = (static_cast<double_limb_type>(prem[r_order]) << CppInt1::limb_bits) | prem[r_order - 1];
         b = py[y_order];
         v = a / b;
         if(v > CppInt1::max_limb_value)
            guess = 1;
         else
         {
            guess = static_cast<limb_type>(v);
            --r_order;
         }
      }
      else if(r_order == 0)
      {
         guess = prem[0] / py[y_order];
      }
      else
      {
         double_limb_type a, b, v;
         a = (static_cast<double_limb_type>(prem[r_order]) << CppInt1::limb_bits) | prem[r_order - 1];
         b = (y_order > 0) ? (static_cast<double_limb_type>(py[y_order]) << CppInt1::limb_bits) | py[y_order - 1] : (static_cast<double_limb_type>(py[y_order])  << CppInt1::limb_bits);
         v = a / b;
         guess = static_cast<limb_type>(v);
      }
      BOOST_ASSERT(guess); // If the guess ever gets to zero we go on forever....
      //
      // Update result:
      //
      limb_type shift = r_order - y_order;
      if(result)
      {
         if(r_neg)
         {
            if(pr[shift] > guess)
               pr[shift] -= guess;
            else
            {
               t.resize(shift + 1, shift + 1);
               t.limbs()[shift] = guess;
               for(unsigned i = 0; i < shift; ++i)
                  t.limbs()[i] = 0;
               eval_subtract(*result, t);
            }
         }
         else if(CppInt1::max_limb_value - pr[shift] > guess)
            pr[shift] += guess;
         else
         {
            t.resize(shift + 1, shift + 1);
            t.limbs()[shift] = guess;
            for(unsigned i = 0; i < shift; ++i)
               t.limbs()[i] = 0;
            eval_add(*result, t);
         }
      }
      //
      // Calculate guess * y, we use a fused mutiply-shift O(N) for this
      // rather than a full O(N^2) multiply:
      //
      double_limb_type carry = 0;
      t.resize(y.size() + shift + 1, y.size() + shift);
      bool truncated_t = !CppInt1::variable && (t.size() != y.size() + shift + 1);
      typename CppInt1::limb_pointer pt = t.limbs();
      for(unsigned i = 0; i < shift; ++i)
         pt[i] = 0;
      for(unsigned i = 0; i < y.size(); ++i)
      {
         carry += static_cast<double_limb_type>(py[i]) * static_cast<double_limb_type>(guess);
         pt[i + shift] = static_cast<limb_type>(carry);
         carry >>= CppInt1::limb_bits;
      }
      if(carry && !truncated_t)
      {
         pt[t.size() - 1] = static_cast<limb_type>(carry);
      }
      else if(!truncated_t)
      {
         t.resize(t.size() - 1, t.size() - 1);
      }
      //
      // Update r in a way that won't actually produce a negative result
      // in case the argument types are unsigned:
      //
      if(r.compare(t) > 0)
      {
         eval_subtract(r, t);
      }
      else
      {
         r.swap(t);
         eval_subtract(r, t);
         prem = r.limbs();
         r_neg = !r_neg;
      }
      //
      // First time through we need to strip any leading zero, otherwise
      // the termination condition goes belly-up:
      //
      if(result && first_pass)
      {
         first_pass = false;
         while(pr[result->size() - 1] == 0)
            result->resize(result->size() - 1, result->size() - 1);
      }
      //
      // Update r_order:
      //
      r_order = r.size() - 1;
      if(r_order < y_order)
         break;
   }
   // Termination condition is really just a check that r > y, but with a common
   // short-circuit case handled first:
   while((r_order > y_order) || (r.compare_unsigned(y) >= 0));

   //
   // We now just have to normalise the result:
   //
   if(r_neg && eval_get_sign(r))
   {
      // We have one too many in the result:
      if(result)
         eval_decrement(*result);
      if(y.sign())
      {
         r.negate();
         eval_subtract(r, y);
      }
      else
         eval_subtract(r, y, r);
   }

   BOOST_ASSERT(r.compare_unsigned(y) < 0); // remainder must be less than the divisor or our code has failed
}


   number_backend_float_architype()
   {
      std::cout << "Default construct" << std::endl;
   }

   number_backend_float_architype(const number_backend_float_architype& o)
   {
      std::cout << "Copy construct" << std::endl;
      m_value = o.m_value;
   }

   number_backend_float_architype& operator = (const number_backend_float_architype& o)
   {
      m_value = o.m_value;
      std::cout << "Assignment (" << m_value << ")" << std::endl;
      return *this;
   }

   number_backend_float_architype& operator = (unsigned long long i)
   {
      m_value = i;
      std::cout << "UInt Assignment (" << i << ")" << std::endl;
      return *this;
   }

   number_backend_float_architype& operator = (long long i)
   {
      m_value = i;
      std::cout << "Int Assignment (" << i << ")" << std::endl;
      return *this;
   }

   number_backend_float_architype& operator = (long double d)
   {
      m_value = d;
      std::cout << "long double Assignment (" << d << ")" << std::endl;
      return *this;
   }

   number_backend_float_architype& operator = (const char* s)
   {
      try
      {
         m_value = boost::lexical_cast<long double>(s);
      }
      catch(const std::exception&)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse input string: \"") + s + std::string("\" as a valid floating point number.")));
      }
      std::cout << "const char* Assignment (" << s << ")" << std::endl;
      return *this;
   }

   void swap(number_backend_float_architype& o)
   {
      std::cout << "Swapping (" << m_value << " with " << o.m_value << ")" << std::endl;
      std::swap(m_value, o.m_value);
   }

   std::string str(std::streamsize digits, std::ios_base::fmtflags f)const
   {
      std::stringstream ss;
      ss.flags(f);
      if(digits)
         ss.precision(digits);
      else
         ss.precision(std::numeric_limits<long double>::digits10 + 2);
      boost::intmax_t i = m_value;
      boost::uintmax_t u = m_value;
      if(!(f & std::ios_base::scientific) && m_value == i)
         ss << i;
      else if(!(f & std::ios_base::scientific) && m_value == u)
         ss << u;
      else
         ss << m_value;
      std::string s = ss.str();
      std::cout << "Converting to string (" << s << ")" << std::endl;
      return s;
   }

   void negate()
   {
      std::cout << "Negating (" << m_value << ")" << std::endl;
      m_value = -m_value;
   }

   int compare(const number_backend_float_architype& o)const
   {
      std::cout << "Comparison" << std::endl;
      return m_value > o.m_value ? 1 : (m_value < o.m_value ? -1 : 0);
   }

   int compare(long long i)const
   {
      std::cout << "Comparison with int" << std::endl;
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }

   int compare(unsigned long long i)const
   {
      std::cout << "Comparison with unsigned" << std::endl;
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }

   int compare(long double d)const
   {
      std::cout << "Comparison with long double" << std::endl;
      return m_value > d ? 1 : (m_value < d ? -1 : 0);
   }


inline void eval_add(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Addition (" << result.m_value << " += " << o.m_value << ")" << std::endl;
   result.m_value += o.m_value;
}

inline void eval_subtract(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Subtraction (" << result.m_value << " -= " << o.m_value << ")" << std::endl;
   result.m_value -= o.m_value;
}

inline void eval_multiply(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Multiplication (" << result.m_value << " *= " << o.m_value << ")" << std::endl;
   result.m_value *= o.m_value;
}

inline void eval_divide(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Division (" << result.m_value << " /= " << o.m_value << ")" << std::endl;
   result.m_value /= o.m_value;
}


inline void eval_convert_to(unsigned long long* result, const number_backend_float_architype& val)
{
   *result = static_cast<unsigned long long>(val.m_value);
}

inline void eval_convert_to(long long* result, const number_backend_float_architype& val)
{
   *result = static_cast<long long>(val.m_value);
}

inline void eval_convert_to(long double* result, number_backend_float_architype& val)
{
   *result = val.m_value;
}


inline void eval_frexp(number_backend_float_architype& result, const number_backend_float_architype& arg, int* exp)
{
   result = std::frexp(arg.m_value, exp);
}


inline void eval_ldexp(number_backend_float_architype& result, const number_backend_float_architype& arg, int exp)
{
   result = std::ldexp(arg.m_value, exp);
}


inline void eval_floor(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::floor(arg.m_value);
}


inline void eval_ceil(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::ceil(arg.m_value);
}


inline void eval_sqrt(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::sqrt(arg.m_value);
}


inline int eval_fpclassify(const number_backend_float_architype& arg)
{
   return (boost::math::fpclassify)(arg.m_value);
}
