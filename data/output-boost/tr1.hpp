
   explicit linear_congruential(unsigned long x0 = 1)
      : m_gen(x0){}

   linear_congruential(const linear_congruential& that)
      : m_gen(that.m_gen){}

   template<class Gen> linear_congruential(Gen& g)
   {
      init1(g, ::boost::is_same<Gen,linear_congruential>());
   }

   void seed(unsigned long x0 = 1)
   { m_gen.seed(x0); }

   template<class Gen> void seed(Gen& g)
   { 
      init2(g, ::boost::is_fundamental<Gen>());
   }

   mersenne_twister(){}

   explicit mersenne_twister(unsigned long value)
      : m_gen(value == 0 ? 5489UL : value){}

   template<class Gen> mersenne_twister(Gen& g)
   {
      init1(g, ::boost::is_same<mersenne_twister,Gen>());
   }

   void seed()
   { m_gen.seed(); }

   void seed(unsigned long value)
   { m_gen.seed(value == 0 ? 5489UL : value); }

   template<class Gen> void seed(Gen& g)
   { init2(g, ::boost::is_fundamental<Gen>()); }

   subtract_with_carry(){}

   explicit subtract_with_carry(unsigned long value)
      : m_gen(value == 0 ? 19780503UL : value){}

   template<class Gen> subtract_with_carry(Gen& g)
   { init1(g, ::boost::is_same<Gen, subtract_with_carry<IntType, m, s, r> >()); }

   void seed(unsigned long value = 19780503ul)
   { m_gen.seed(value == 0 ? 19780503UL : value); }

   template<class Gen> void seed(Gen& g)
   { init2(g, ::boost::is_fundamental<Gen>()); }

   subtract_with_carry_01(){}

   explicit subtract_with_carry_01(unsigned long value)
      : m_gen(value == 0 ? 19780503UL : value){}

   template<class Gen> subtract_with_carry_01(Gen& g)
   { init1(g, ::boost::is_same<Gen, subtract_with_carry_01<RealType, w, s, r> >()); }

   void seed(unsigned long value = 19780503UL)
   { m_gen.seed(value == 0 ? 19780503UL : value); }

   template<class Gen> void seed(Gen& g)
   { init2(g, ::boost::is_fundamental<Gen>()); }

   xor_combine(){ init_minmax(); }

   xor_combine(const base1_type & rng1, const base2_type & rng2)
      : m_b1(rng1), m_b2(rng2) { init_minmax(); }

   xor_combine(unsigned long s)
      : m_b1(s), m_b2(s+1) { init_minmax(); }

   template<class Gen> xor_combine(Gen& g)
   { 
      init_minmax(); 
      init1(g, ::boost::is_same<Gen, xor_combine<UniformRandomNumberGenerator1, s1, UniformRandomNumberGenerator2, s2> >());
   }

   void seed()
   {
      m_b1.seed();
      m_b2.seed();
   }

   void seed(unsigned long s)
   {
      m_b1.seed(s);
      m_b2.seed(s+1);
   }

   template<class Gen> void seed(Gen& g)
   {
      init2(g, ::boost::is_fundamental<Gen>());
   }


   const base1_type& base1() const
   { return m_b1; }

   const base2_type& base2() const
   { return m_b2; }


   template <class Gen>
   void init1(Gen& g, const ::boost::true_type&)
   {
      m_b1 = g.m_b1;
      m_b2 = g.m_b2;
   }

   template <class Gen>
   void init2(Gen& g, const ::boost::true_type&)
   {
      m_b1.seed(static_cast<unsigned long>(g));
      m_b2.seed(static_cast<unsigned long>(g));
   }


template<class UniformRandomNumberGenerator1, int s1, class UniformRandomNumberGenerator2, int s2>
void xor_combine<UniformRandomNumberGenerator1, s1, UniformRandomNumberGenerator2, s2>::init_minmax()
{
   //
   // The following code is based on that given in "Hacker's Delight"
   // by Henry S. Warren, (Addison-Wesley, 2003), and at 
   // http://www.hackersdelight.org/index.htm.
   // Used here by permission.
   //
   // calculation of minimum value:
   //
   result_type a = (m_b1.min)() << s1;
   result_type b = (m_b1.max)() << s1;
   result_type c = (m_b2.min)() << s2;
   result_type d = (m_b2.max)() << s2;
   result_type m, temp;

   m = 0x1uL << ((sizeof(result_type) * CHAR_BIT) - 1);
   while (m != 0) {
      if (~a & c & m) {
         temp = (a | m) & (static_cast<result_type>(0u) - m);
         if (temp <= b) a = temp;
      }
      else if (a & ~c & m) {
         temp = (c | m) & (static_cast<result_type>(0u) - m);
         if (temp <= d) c = temp;
      }
      m >>= 1;
   }
   m_min = a ^ c;

   //
   // calculation of maximum value:
   //
   if((((std::numeric_limits<result_type>::max)() >> s1) < (m_b1.max)())
      || ((((std::numeric_limits<result_type>::max)()) >> s2) < (m_b2.max)()))
   {
      m_max = (std::numeric_limits<result_type>::max)();
      return;
   }
   a = (m_b1.min)() << s1;
   b = (m_b1.max)() << s1;
   c = (m_b2.min)() << s2;
   d = (m_b2.max)() << s2;

   m = 0x1uL << ((sizeof(result_type) * CHAR_BIT) - 1);

   while (m != 0) {
      if (b & d & m) {
         temp = (b - m) | (m - 1);
         if (temp >= a) b = temp;
         else {
            temp = (d - m) | (m - 1);
            if (temp >= c) d = temp;
         }
      }
      m = m >> 1;
   }
   m_max = b ^ d;
}

   explicit bernoulli_distribution(double p = 0.5)
      : m_dist(p){}

   double p() const
   { return m_dist.p(); }

   void reset()
   { m_dist.reset(); }

   template<class UniformRandomNumberGenerator>
   result_type operator()(UniformRandomNumberGenerator& urng)
   {
      return m_dist(urng);
   }
 arg(const T& t)
{
   return ::std::atan2(0.0, static_cast<double>(t));
}

inline long double arg(const long double& t)
{
   return ::std::atan2(0.0L, static_cast<long double>(t));
}

inline float arg(const float& t)
{
   return ::std::atan2(0.0F, static_cast<float>(t));
}
 norm(const T& t)
{
   double r = static_cast<double>(t);
   return r*r;
}

inline long double norm(const long double& t)
{
   long double l = t;
   return l*l;
}

inline float norm(const float& t)
{
   float f = t;
   return f*f;
}
 conj(const T& t)
{
   return ::std::conj(std::complex<double>(static_cast<double>(t)));
}
 imag(const T& )
{
   return 0;
}

inline long double imag(const long double& )
{
   return 0;
}

inline float imag(const float& )
{
   return 0;
}
 real(const T& t)
{
   return static_cast<double>(t);
}

inline long double real(const long double& t)
{
   return t;
}

inline float real(const float& t)
{
   return t;
}

   functor2iterator() : m_func(0){}

   functor2iterator(Func& f)
      : m_func(&f)
   {
      m_val = (*m_func)();
   }

   const R& dereference()const
   { return m_val; }

   void increment(){ m_val = (*m_func)(); }

   bool equal(const functor2iterator&)const
   { return false; }
