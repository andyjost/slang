
    template <class To, class Rep, class Period>
    To round(const duration<Rep, Period>& d)
    {
        To t0 = duration_cast<To>(d);
        To t1 = t0;
        ++t1;
#if 0
        // Avoid the user of BOOST_AUTO to make the library portable to Sun, PGI, ..
        BOOST_AUTO(diff0, d - t0);
        BOOST_AUTO(diff1, t1 - d);
#else
        typedef typename common_type<To, duration<Rep, Period> >::type  result_type;
        result_type diff0 = d - t0;
        result_type diff1 = t1 - d;
#endif
        if (diff0 == diff1)
        {
            if (t0.count() & 1)
                return t1;
            return t0;
        }
        else if (diff0 < diff1)
            return t0;
        return t1;
    }

    template <class To, class Rep, class Period>
    To floor(const duration<Rep, Period>& d)
    {
        return duration_cast<To>(d);
    }

    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }


inline void free_aux(void* ptr) { free(ptr); }


template <class InputIterator, class ForwardIterator>
ForwardIterator
scan_keyword(InputIterator& b, InputIterator e,
               ForwardIterator kb, ForwardIterator ke,
               std::ios_base::iostate& err
               )
{
    typedef typename std::iterator_traits<InputIterator>::value_type CharT;
    size_t nkw = std::distance(kb, ke);
    const unsigned char doesnt_match = '\0';
    const unsigned char might_match = '\1';
    const unsigned char does_match = '\2';
    unsigned char statbuf[100];
    unsigned char* status = statbuf;
    //  Change free by free_aux to avoid
    // Error: Could not find a match for boost::interprocess::unique_ptr<unsigned char, void(*)(void*)>::unique_ptr(int, extern "C" void(void*))
    unique_ptr<unsigned char, void(*)(void*)> stat_hold(0, free_aux);
    if (nkw > sizeof(statbuf))
    {
        status = (unsigned char*)malloc(nkw);
        if (status == 0)
          throw_exception(std::bad_alloc());
        stat_hold.reset(status);
    }
    size_t n_might_match = nkw;  // At this point, any keyword might match
    size_t n_does_match = 0;       // but none of them definitely do
    // Initialize all statuses to might_match, except for "" keywords are does_match
    unsigned char* st = status;
    for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
    {
        if (!ky->empty())
            *st = might_match;
        else
        {
            *st = does_match;
            --n_might_match;
            ++n_does_match;
        }
    }
    // While there might be a match, test keywords against the next CharT
    for (size_t indx = 0; b != e && n_might_match > 0; ++indx)
    {
        // Peek at the next CharT but don't consume it
        CharT c = *b;
        bool consume = false;
        // For each keyword which might match, see if the indx character is c
        // If a match if found, consume c
        // If a match is found, and that is the last character in the keyword,
        //    then that keyword matches.
        // If the keyword doesn't match this character, then change the keyword
        //    to doesn't match
        st = status;
        for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
        {
            if (*st == might_match)
            {
                CharT kc = (*ky)[indx];
                if (c == kc)
                {
                    consume = true;
                    if (ky->size() == indx+1)
                    {
                        *st = does_match;
                        --n_might_match;
                        ++n_does_match;
                    }
                }
                else
                {
                    *st = doesnt_match;
                    --n_might_match;
                }
            }
        }
        // consume if we matched a character
        if (consume)
        {
            ++b;
            // If we consumed a character and there might be a matched keyword that
            //   was marked matched on a previous iteration, then such keywords
            //   which are now marked as not matching.
            if (n_might_match + n_does_match > 1)
            {
                st = status;
                for (ForwardIterator ky = kb; ky != ke; ++ky, ++st)
                {
                    if (*st == does_match && ky->size() != indx+1)
                    {
                        *st = doesnt_match;
                        --n_does_match;
                    }
                }
            }
        }
    }
    // We've exited the loop because we hit eof and/or we have no more "might matches".
    if (b == e)
        err |= std::ios_base::eofbit;
    // Return the first matching result
    for (st = status; kb != ke; ++kb, ++st)
        if (*st == does_match)
            break;
    if (kb == ke)
        err |= std::ios_base::failbit;
    return kb;
}


      inline long tick_factor() // multiplier to convert ticks
      //  to nanoseconds; -1 if unknown
      {
        static long factor = 0;
        if (!factor)
        {
          if ((factor = ::sysconf(_SC_CLK_TCK)) <= 0)
            factor = -1;
          else
          {
            BOOST_ASSERT(factor <= 1000000000l); // doesn't handle large ticks
            factor = 1000000000l / factor; // compute factor
            if (!factor)
              factor = -1;
          }
        }
        return factor;
      }

  inline long tick_factor()        // multiplier to convert ticks
                            //  to nanoseconds; -1 if unknown
  {
    static long factor = 0;
    if ( !factor )
    {
      if ( (factor = ::sysconf( _SC_CLK_TCK )) <= 0 )
        factor = -1;
      else
      {
        BOOST_ASSERT( factor <= 1000000000l ); // doesn't handle large ticks
        factor = 1000000000l / factor;  // compute factor
        if ( !factor ) factor = -1;
      }
    }
    return factor;
  }


  template <class T, class U>
  bool lt(T t, U u)
  {
    return t < u;
  }


  template <class T, class U>
  bool gt(T t, U u)
  {
    return t > u;
  }


    template <class Period>
        string_type short_name(Period) const
            {return ::boost::ratio_string<Period, CharT>::short_name() + short_seconds_;}


    template <class Period>
        string_type long_name(Period) const
            {return ::boost::ratio_string<Period, CharT>::long_name() + long_seconds_;}


    explicit duration_punct(int use = use_long)
        : use_short_(use==use_short) {init_C();}


    template <class Period>
        string_type plural() const
            {return long_name(typename Period::type());}


    template <class Period>
        string_type singular() const
    {
      return string_type(long_name(typename Period::type()), 0, long_name(typename Period::type()).size()-1);
    }


    template <class Period>
        string_type name() const
    {
      if (use_short_) return short_name<Period>();
      else {
        return long_name<Period>();
      }
    }


    bool is_short_name() const {return use_short_;}

    bool is_long_name() const {return !use_short_;}


template <class CharT>
void
duration_punct<CharT>::init_C()
{
    short_seconds_ = CharT('s');
    short_minutes_ = CharT('m');
    short_hours_ = CharT('h');
    const CharT s[] = {'s', 'e', 'c', 'o', 'n', 'd', 's'};
    const CharT m[] = {'m', 'i', 'n', 'u', 't', 'e', 's'};
    const CharT h[] = {'h', 'o', 'u', 'r', 's'};
    long_seconds_.assign(s, s + sizeof(s)/sizeof(s[0]));
    long_minutes_.assign(m, m + sizeof(m)/sizeof(m[0]));
    long_hours_.assign(h, h + sizeof(h)/sizeof(h[0]));
}


template <class CharT>
duration_punct<CharT>::duration_punct(int use, const duration_punct& d)
    : use_short_(use==use_short),
      long_seconds_(d.long_seconds_),
      long_minutes_(d.long_minutes_),
      long_hours_(d.long_hours_),
      short_seconds_(d.short_seconds_),
      short_minutes_(d.short_minutes_),
      short_hours_(d.short_hours_)
{}

      explicit time_point_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      template <typename Clock>
      string_type get_epoch() const
      {
        return do_get_epoch(Clock());
      }

      virtual ~time_point_units() {}


      explicit time_point_units_default(size_t refs = 0) :
        time_point_units<CharT> (refs)
      {
      }

      ~time_point_units_default() {}

      string_type get_pattern() const
      {
        static const CharT t[] =
        { '%', 'd', '%', 'e' };
        static const string_type pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

      string_type do_get_epoch(system_clock ) const
      {
        return clock_string<system_clock,CharT>::since();
      }


        time_manip(timezone tz, std::basic_string<CharT> fmt)
        // todo move semantics
        :
          fmt_(fmt), tz_(tz)
        {
        }

        void operator()(std::ios_base &ios) const
        {
          set_time_fmt<CharT> (ios, fmt_);
          set_timezone(ios, tz_);
        }


        time_man(timezone tz)
        // todo move semantics
        :
          tz_(tz)
        {
        }

        void operator()(std::ios_base &ios) const
        {
          //set_time_fmt<typename out_stream::char_type>(ios, "");
          set_timezone(ios, tz_);
        }


    template <class CharT>
    inline detail::time_manip<CharT> time_fmt(timezone tz, const CharT* fmt)
    {
      return detail::time_manip<CharT>(tz, fmt);
    }

      explicit timezone_io_saver(state_type &s) :
        s_save_(s), a_save_(get_timezone(s_save_))
      {
      }

      timezone_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(new_value)
      {
      }

      ~timezone_io_saver()
      {
        this->restore();
      }

      void restore()
      {
        set_timezone(s_save_, a_save_);
      }

      explicit duration_style_io_saver(state_type &s) :
        s_save_(s)
      {
        a_save_ = get_duration_style(s_save_);
      }

      duration_style_io_saver(state_type &s, aspect_type new_value) :
        s_save_(s), a_save_(new_value)
      {
      }

      ~duration_style_io_saver()
      {
        this->restore();
      }

      void restore()
      {
        set_duration_style(s_save_, a_save_);
      }

      fmt_masks(std::ios_base& ios): base_type(ios) {}


      inline duration_style get_duration_style()
      {
        return (flags() & uses_symbol) ? duration_style::symbol : duration_style::prefix;
      }

      inline void set_duration_style(duration_style style)
      {
        if (style == duration_style::symbol)
          setf(uses_symbol);
        else
          unsetf(uses_symbol);
      }


      inline timezone get_timezone()
      {
        return (flags() & uses_local) ? timezone::local : timezone::utc;
      }

      inline void set_timezone(timezone tz)
      {
        if (tz == timezone::local)
          setf(uses_local);
        else
          unsetf(uses_local);
      }


    inline duration_style get_duration_style(std::ios_base & ios)
    {
      return fmt_masks(ios).get_duration_style();
    }

    inline void set_duration_style(std::ios_base& ios, duration_style style)
    {
      fmt_masks(ios).set_duration_style(style);
    }

    inline std::ios_base&  symbol_format(std::ios_base& ios)
    {
      fmt_masks(ios).setf(fmt_masks::uses_symbol);
      return ios;
    }

    inline std::ios_base&  name_format(std::ios_base& ios)
    {
      fmt_masks(ios).unsetf(fmt_masks::uses_symbol);
      return ios;
    }


    inline timezone get_timezone(std::ios_base & ios)
    {
      return fmt_masks(ios).get_timezone();
    }

    inline void set_timezone(std::ios_base& ios, timezone tz)
    {
      fmt_masks(ios).set_timezone(tz);
    }

    inline std::ios_base& local_timezone(std::ios_base& ios)
    {
      fmt_masks(ios).setf(fmt_masks::uses_local);
      return ios;
    }


    inline std::ios_base& utc_timezone(std::ios_base& ios)
    {
      fmt_masks(ios).unsetf(fmt_masks::uses_local);
      return ios;
    }


        ios_base_data_aux() :
          time_fmt(""),
          duration_fmt("")
        {
        }

      template <typename Period>
      rt_ratio(Period const&) :
        num(Period::type::num), den(Period::type::den)
      {
      }

      explicit duration_units(size_t refs = 0) :
        std::locale::facet(refs)
      {
      }

      template <typename Rep, typename Period>
      string_type get_unit(duration_style style, duration<Rep, Period> const& d) const
      {
        return do_get_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }

      template <typename Rep, typename Period>
      string_type get_n_d_unit(duration_style style, duration<Rep, Period> const& d) const
      {
        return do_get_n_d_unit(style, rt_ratio(Period()), static_cast<intmax_t>(d.count()));
      }

      template <typename Period>
      bool is_named_unit() const
      {
        return do_is_named_unit(rt_ratio(Period()));
      }

      virtual ~duration_units()
      {
      }

      explicit duration_units_default(size_t refs = 0) :
        duration_units<CharT> (refs)
      {
      }

      ~duration_units_default()
      {
      }

      bool match_n_d_valid_unit(const string_type* k) const
      {
        std::size_t index = (k - get_n_d_valid_units_start()) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          break;
        default:
          return false;
        }
        return true;
      }

      bool match_valid_unit(const string_type* k, rt_ratio& rt) const
      {
        std::size_t index = (k - get_valid_units_start()) / (pfs_ + 1);
        switch (index)
        {
        case 0:
          rt = rt_ratio(atto());
          break;
        case 1:
          rt = rt_ratio(femto());
          break;
        case 2:
          rt = rt_ratio(pico());
          break;
        case 3:
          rt = rt_ratio(nano());
          break;
        case 4:
          rt = rt_ratio(micro());
          break;
        case 5:
          rt = rt_ratio(milli());
          break;
        case 6:
          rt = rt_ratio(centi());
          break;
        case 7:
          rt = rt_ratio(deci());
          break;
        case 8:
          rt = rt_ratio(deca());
          break;
        case 9:
          rt = rt_ratio(hecto());
          break;
        case 10:
          rt = rt_ratio(kilo());
          break;
        case 11:
          rt = rt_ratio(mega());
          break;
        case 12:
          rt = rt_ratio(giga());
          break;
        case 13:
          rt = rt_ratio(tera());
          break;
        case 14:
          rt = rt_ratio(peta());
          break;
        case 15:
          rt = rt_ratio(exa());
          break;
        case 16:
          rt = rt_ratio(ratio<1> ());
          break;
        case 17:
          rt = rt_ratio(ratio<60> ());
          break;
        case 18:
          rt = rt_ratio(ratio<3600> ());
          break;
        default:
          return false;
        }
        return true;
      }

      virtual const string_type* get_n_d_valid_units_start()const
      {
        return  detail::duration_units_default_holder<CharT>::n_d_valid_units_;
      }

      virtual const string_type* get_n_d_valid_units_end()const
      {
        return detail::duration_units_default_holder<CharT>::n_d_valid_units_ + (pfs_ + 1);
      }

      virtual const string_type* get_valid_units_start() const
      {
        return detail::duration_units_default_holder<CharT>::valid_units_;
      }

      virtual const string_type* get_valid_units_end() const
      {
        return detail::duration_units_default_holder<CharT>::valid_units_ + 19 * (pfs_ + 1);
      }


      string_type get_pattern() const
      {
        static const CharT t[] =
        { '%', 'v', ' ', '%', 'u' };
        static const string_type pattern(t, t + sizeof (t) / sizeof (t[0]));

        return pattern;
      }

      bool do_is_named_unit(rt_ratio rt) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
          case BOOST_RATIO_INTMAX_C(60):
          case BOOST_RATIO_INTMAX_C(100):
          case BOOST_RATIO_INTMAX_C(1000):
          case BOOST_RATIO_INTMAX_C(3600):
          case BOOST_RATIO_INTMAX_C(1000000):
          case BOOST_RATIO_INTMAX_C(1000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000):
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return true;
          default:
            return false;
          }
        }
        return false;

      }

      string_type do_get_n_d_unit(duration_style style, rt_ratio, intmax_t v) const
      {
        return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
      }

      string_type do_get_unit(duration_style style, rt_ratio rt, intmax_t v) const
      {
        if (rt.num==1) {
          switch (rt.den)
          {
          case BOOST_RATIO_INTMAX_C(1):
            return do_get_unit(style, ratio<1>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(10):
            return do_get_unit(style, deci(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
            return do_get_unit(style, centi(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000):
            return do_get_unit(style, milli(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000):
            return do_get_unit(style, micro(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000):
            return do_get_unit(style, nano(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000):
            return do_get_unit(style, pico(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000):
            return do_get_unit(style, femto(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(1000000000000000000):
            return do_get_unit(style, atto(), do_get_plural_form(v));
          default:
            ;
          }
        } else if (rt.den==1) {
          switch (rt.num)
          {
          case BOOST_RATIO_INTMAX_C(10):
             return do_get_unit(style, deca(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(60):
            return do_get_unit(style, ratio<60>(), do_get_plural_form(v));
          case BOOST_RATIO_INTMAX_C(100):
             return do_get_unit(style, hecto(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000):
             return do_get_unit(style, kilo(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(3600):
             return do_get_unit(style, ratio<3600>(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000):
             return do_get_unit(style, mega(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000):
             return do_get_unit(style, giga(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000):
             return do_get_unit(style, tera(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000):
             return do_get_unit(style, peta(), do_get_plural_form(v));
           case BOOST_RATIO_INTMAX_C(1000000000000000000):
             return do_get_unit(style, exa(), do_get_plural_form(v));
           default:
             ;
           }
        }
        BOOST_ASSERT(false&&"ratio parameter can not be translated");
        //throw "exception";
        return string_type();
      }

      virtual std::size_t do_get_plural_forms() const
      {
        return static_get_plural_forms();
      }

      static std::size_t static_get_plural_forms()
      {
        return pfs_;
      }

      virtual std::size_t do_get_plural_form(int_least64_t value) const
      {
        return static_get_plural_form(value);
      }

      static std::size_t static_get_plural_form(int_least64_t value)
      {
        return (value == -1 || value == 1) ? 0 : 1;
      }

      static string_type static_get_unit(duration_style style, ratio<1> , std::size_t pf)
      {
        static const CharT t[] =
        { 's' };
        static const string_type symbol(t, t + sizeof (t) / sizeof (t[0]));
        static const CharT u[] =
        { 's', 'e', 'c', 'o', 'n', 'd' };
        static const string_type singular(u, u + sizeof (u) / sizeof (u[0]));
        static const CharT v[] =
        { 's', 'e', 'c', 'o', 'n', 'd', 's' };
        static const string_type plural(v, v + sizeof (v) / sizeof (v[0]));

        if (style == duration_style::symbol)
        {
          return symbol;
        }
        if (pf == 0)
        {
          return singular;
        }
        if (pf == 1)
        {
          return plural;
        }
        BOOST_ASSERT(false&&"style/pf parameters not valid");
        //throw "exception";
        return string_type();
      }

      virtual string_type do_get_ratio_prefix(duration_style style, atto u) const
      {
        return static_get_ratio_prefix(style, u);
      }

      static string_type static_get_ratio_prefix(duration_style style, atto)
      {
        if (style == duration_style::symbol) return ratio_string<atto, CharT>::symbol();
        return ratio_string<atto, CharT>::prefix();
      }

      template <typename Period>
      string_type* fill_units(string_type* it, Period) const
      {
        std::size_t pfs = do_get_plural_forms();
        for (std::size_t pf = 0; pf < pfs; ++pf)
        {
          *it++ = do_get_unit(duration_style::prefix, Period(), pf);
        }
        *it++ = do_get_unit(duration_style::symbol, Period(), 0);
        return it;
      }

      template <typename Period>
      static string_type* static_fill_units(string_type* it, Period)
      {
        std::size_t pfs = static_get_plural_forms();
        for (std::size_t pf = 0; pf < pfs; ++pf)
        {
          *it++ = static_get_unit(duration_style::prefix, Period(), pf);
        }
        *it++ = static_get_unit(duration_style::symbol, Period(), 0);
        return it;
      }

      static string_type* static_init_valid_units(string_type* it)
      {
        it = static_fill_units(it, atto());
        it = static_fill_units(it, femto());
        it = static_fill_units(it, pico());
        it = static_fill_units(it, nano());
        it = static_fill_units(it, micro());
        it = static_fill_units(it, milli());
        it = static_fill_units(it, centi());
        it = static_fill_units(it, deci());
        it = static_fill_units(it, deca());
        it = static_fill_units(it, hecto());
        it = static_fill_units(it, kilo());
        it = static_fill_units(it, mega());
        it = static_fill_units(it, giga());
        it = static_fill_units(it, tera());
        it = static_fill_units(it, peta());
        it = static_fill_units(it, exa());
        it = static_fill_units(it, ratio<1> ());
        it = static_fill_units(it, ratio<60> ());
        it = static_fill_units(it, ratio<3600> ());
        return it;
      }

        duration_units_default_initializer_t()
          {
              if (!duration_units_default_holder<CharT>::initialized_)
              {
                typedef typename duration_units_default_holder<CharT>::string_type string_type;
                duration_units_default_holder<CharT>::n_d_valid_units_ = new string_type[3];
                duration_units_default_holder<CharT>::valid_units_ = new string_type[19 * 3];

                string_type* it = duration_units_default_holder<CharT>::n_d_valid_units_;
                it = duration_units_default<CharT>::static_fill_units(it, ratio<1> ());
                it = duration_units_default<CharT>::static_init_valid_units(duration_units_default_holder<CharT>::valid_units_);

                duration_units_default_holder<CharT>::initialized_ = true;
              }
          }

        ~duration_units_default_initializer_t()
          {
            if (duration_units_default_holder<CharT>::initialized_)
            {
              delete[] duration_units_default_holder<CharT>::n_d_valid_units_;
              duration_units_default_holder<CharT>::n_d_valid_units_ = 0;
              delete[] duration_units_default_holder<CharT>::valid_units_;
              duration_units_default_holder<CharT>::valid_units_ = 0;
              duration_units_default_holder<CharT>::initialized_ = false;
            }
        }

      xalloc_key_initializer()
      {
        if (!detail::xalloc_key_holder<T>::initialized)
        {
          detail::xalloc_key_holder<T>::value = std::ios_base::xalloc();
          detail::xalloc_key_holder<T>::initialized = true;
        }
      }

      explicit ios_state_ptr(std::ios_base& ios) :
        ios_(ios)
      {
      }

      ~ios_state_ptr()
      {
      }

      explicit ios_state_not_null_ptr(std::ios_base& ios) :
      base_type(ios)
      {
        if (this->get() == 0)
        {
          this->base_type::reset(new T());
        }
      }

      ~ios_state_not_null_ptr()
      {
      }

      explicit ios_flags(std::ios_base& ios) :
        ios_(ios)
      {
      }

      ~ios_flags()
      {
      }

      void operator()(std::ios_base &ios) const
      {
        (*static_cast<const Final *> (this))(ios);
      }

    template <typename out_stream, typename manip_type>
    out_stream &operator<<(out_stream &out, const manip<manip_type> &op)
    {
      if (out.good())
        op(out);
      return out;
    }

    template <typename in_stream, typename manip_type>
    in_stream &operator>>(in_stream &in, const manip<manip_type> &op)
    {
      if (in.good())
        op(in);
      return in;
    }
