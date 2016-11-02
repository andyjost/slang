
    static void duration_put(const time_duration_type& td, 
                             ostream_type& os)
    {
      if(td.is_special()) {
        os << td.get_rep(); 
      }
      else {
        charT fill_char = '0';
        if(td.is_negative()) {
          os << '-';
        }
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.hours()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.minutes()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.seconds());
        fractional_seconds_type frac_sec = 
          absolute_value(td.fractional_seconds());
        if (frac_sec != 0) {
          os  << "." 
              << std::setw(time_duration_type::num_fractional_digits())
              << std::setfill(fill_char)
              << frac_sec;
        }
      } // else
    }

    static void time_put(const time_type& t, 
                         ostream_type& os)
    {
      date_type d = t.date();
      os << d;
      if(!d.is_infinity() && !d.is_not_a_date())
      {
        os << " "; //TODO: fix the separator here.
        duration_formatter::duration_put(t.time_of_day(), os);
      }
      
    }

    static void period_put(const time_period_type& tp, 
                           ostream_type& os)
    {
      os << '['; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.begin(), os);
      os << '/'; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.last(), os);
      os << ']'; 

    }

    special_values_parser()
    {
      sv_strings(string_type(nadt_string),
                 string_type(neg_inf_string),
                 string_type(pos_inf_string),
                 string_type(min_date_time_string),
                 string_type(max_date_time_string));
    }


    special_values_parser(const special_values_parser<date_type,charT>& svp)
    {
      this->m_sv_strings = svp.m_sv_strings;
    }

    void sv_strings(const string_type& nadt_str,
                    const string_type& neg_inf_str,
                    const string_type& pos_inf_str,
                    const string_type& min_dt_str,
                    const string_type& max_dt_str)
    {
      collection_type phrases;
      phrases.push_back(nadt_str);
      phrases.push_back(neg_inf_str);
      phrases.push_back(pos_inf_str);
      phrases.push_back(min_dt_str);
      phrases.push_back(max_dt_str);
      m_sv_strings = parse_tree_type(phrases, static_cast<int>(not_a_date_time));
    }

    bool match(stream_itr_type& sitr, 
                        stream_itr_type& str_end,
                        match_results& mr) const
    {
      unsigned int level = 0;
      m_sv_strings.match(sitr, str_end, mr, level);
      return (mr.current_match != match_results::PARSE_ERROR);
    }

    time_itr(time_type t, time_duration_type d) : current_(t), offset_(d) {}

    time_itr& operator++()
    {
      current_ = current_ + offset_;
      return *this;
    }

    time_itr& operator--()
    {
      current_ = current_ - offset_;
      return *this;
    }

    time_type operator*() {return current_;}

    time_type* operator->() {return &current_;}

    bool operator<  (const time_type& t) {return current_ < t;}

    bool operator<= (const time_type& t) {return current_ <= t;}

    bool operator!=  (const time_type& t) {return current_ != t;}

    bool operator== (const time_type& t) {return current_ == t;}

    bool operator>  (const time_type& t) {return current_ > t;}

    bool operator>= (const time_type& t) {return current_ >= t;}


    static time_rep_type get_time_rep(special_values sv)
    {
      switch (sv) {
      case not_a_date_time:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));
      case pos_infin:
        return time_rep_type(date_type(pos_infin), 
                             time_duration_type(pos_infin));
      case neg_infin:
        return time_rep_type(date_type(neg_infin), 
                             time_duration_type(neg_infin));
      case max_date_time: {
        time_duration_type td = time_duration_type(24,0,0,0) - time_duration_type(0,0,0,1);
        return time_rep_type(date_type(max_date_time), td);
      }
      case min_date_time:
        return time_rep_type(date_type(min_date_time), time_duration_type(0,0,0,0));

      default:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));
        
      }

    }

    static date_type get_date(const time_rep_type& val)
    {
      return date_type(val.day);
    }

    static time_duration_type get_time_of_day(const time_rep_type& val)
    {
      return time_duration_type(val.time_of_day);
    }

    static std::string zone_name(const time_rep_type&)
    {
      return std::string();
    }

    static bool is_equal(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return ((lhs.day == rhs.day) && (lhs.time_of_day == rhs.time_of_day));
    }

    static bool is_less(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      if (lhs.day < rhs.day) return true;
      if (lhs.day > rhs.day) return false;
      return (lhs.time_of_day < rhs.time_of_day);
    }

    static time_rep_type add_days(const time_rep_type& base,
                                  const date_duration_type& dd)
    {
      return time_rep_type(base.day+dd, base.time_of_day);
    }

    static time_rep_type subtract_days(const time_rep_type& base,
                                       const date_duration_type& dd)
    {
      return split_timedate_system::get_time_rep(base.day-dd, base.time_of_day);
    }

    static time_rep_type subtract_time_duration(const time_rep_type& base,
                                                const time_duration_type& td)
    {
      if(base.day.is_special() || td.is_special())
      {
        return split_timedate_system::get_time_rep(base.day, -td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return add_time_duration(base,td1);
      }

      wrap_int_type  day_offset(base.time_of_day.ticks());
      date_duration_type day_overflow(static_cast<typename date_duration_type::duration_rep_type>(day_offset.subtract(td.ticks())));

      return time_rep_type(base.day-day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }

    static time_rep_type add_time_duration(const time_rep_type& base,
                                           time_duration_type td)
    {
      if(base.day.is_special() || td.is_special()) {
        return split_timedate_system::get_time_rep(base.day, td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return subtract_time_duration(base,td1);
      }

      wrap_int_type day_offset(base.time_of_day.ticks());      
      date_duration_type day_overflow(static_cast< typename date_duration_type::duration_rep_type >(day_offset.add(td.ticks())));

      return time_rep_type(base.day+day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }

    static time_duration_type subtract_times(const time_rep_type& lhs,
                                             const time_rep_type& rhs)
    {
      date_duration_type dd = lhs.day - rhs.day;
      time_duration_type td(dd.days()*24,0,0); //days * 24 hours
      time_duration_type td2 = lhs.time_of_day - rhs.time_of_day;
      return td+td2;
      // return time_rep_type(base.day-dd, base.time_of_day);
    }

    weeks_duration(typename duration_config::impl_type w) 
      : date_duration<duration_config>(w * 7) {}

      months_duration(int_rep num) : _m(num) {}

      int_rep number_of_months() const { return _m; }

      duration_type get_neg_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_m.as_number());
        return duration_type(m_adj.get_neg_offset(d));
      }

      duration_type get_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_m.as_number());
        return duration_type(m_adj.get_offset(d));
      }

      bool operator==(const months_type& rhs) const
      {
        return(_m == rhs._m);
      }

      bool operator!=(const months_type& rhs) const
      {
        return(_m != rhs._m);
      }

      months_type operator+(const months_type& rhs)const
      {
        return months_type(_m + rhs._m);
      }

      months_type& operator+=(const months_type& rhs)
      {
        _m = _m + rhs._m;
        return *this;
      }

      months_type operator-(const months_type& rhs)const
      {
        return months_type(_m - rhs._m);
      }

      months_type& operator-=(const months_type& rhs)
      {
        _m = _m - rhs._m;
        return *this;
      }

      months_type operator*(const int_type rhs)const
      {
        return months_type(_m * rhs);
      }

      months_type& operator*=(const int_type rhs)
      {
        _m = _m * rhs;
        return *this;
      }

      months_type operator/(const int_type rhs)const
      {
        return months_type(_m / rhs);
      }

      months_type& operator/=(const int_type rhs)
      {
        _m = _m / rhs;
        return *this;
      }

      months_type operator+(const years_type& y)const
      {
        return months_type(y.number_of_years() * 12 + _m);
      }

      months_type& operator+=(const years_type& y)
      {
        _m = y.number_of_years() * 12 + _m;
        return *this;
      }

      months_type operator-(const years_type& y) const
      {
        return months_type(_m - y.number_of_years() * 12);
      }

      months_type& operator-=(const years_type& y)
      {
        _m = _m - y.number_of_years() * 12;
        return *this;
      }

      years_duration(int_rep num) : _y(num) {}

      int_rep number_of_years() const { return _y; }

      duration_type get_neg_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_y.as_number() * 12);
        return duration_type(m_adj.get_neg_offset(d));
      }

      duration_type get_offset(const date_type& d) const
      {
        month_adjustor_type m_adj(_y.as_number() * 12);
        return duration_type(m_adj.get_offset(d));
      }

      bool operator==(const years_type& rhs) const
      {
        return(_y == rhs._y);
      }

      bool operator!=(const years_type& rhs) const
      {
        return(_y != rhs._y);
      }

      years_type operator+(const years_type& rhs)const
      {
        return years_type(_y + rhs._y);
      }

      years_type& operator+=(const years_type& rhs)
      {
        _y = _y + rhs._y;
        return *this;
      }

      years_type operator-(const years_type& rhs)const
      {
        return years_type(_y - rhs._y);
      }

      years_type& operator-=(const years_type& rhs)
      {
        _y = _y - rhs._y;
        return *this;
      }

      years_type operator*(const int_type rhs)const
      {
        return years_type(_y * rhs);
      }

      years_type& operator*=(const int_type rhs)
      {
        _y = _y * rhs;
        return *this;
      }

      years_type operator/(const int_type rhs)const
      {
        return years_type(_y / rhs);
      }

      years_type& operator/=(const int_type rhs)
      {
        _y = _y / rhs;
        return *this;
      }

      months_type operator+(const months_type& m) const
      {
        return(months_type(_y * 12 + m.number_of_months()));
      }

      months_type operator-(const months_type& m) const
      {
        return(months_type(_y * 12 - m.number_of_months()));
      }

    
    base_time(const date_type& day, 
              const time_duration_type& td, 
              dst_flags dst=not_dst) :
      time_(time_system::get_time_rep(day, td, dst))
    {}

    base_time(const time_rep_type& rhs) :
      time_(rhs)
    {}

    date_type date() const
    {
      return time_system::get_date(time_);
    }

    time_duration_type time_of_day() const
    {
      return time_system::get_time_of_day(time_);
    }

    std::string zone_name(bool /*as_offset*/=false) const
    {
      return time_system::zone_name(time_);
    }

    std::string zone_abbrev(bool /*as_offset*/=false) const
    {
      return time_system::zone_name(time_);
    }

    std::string zone_as_posix_string() const
    {
      return std::string();
    }

    bool is_not_a_date_time()  const
    {
      return time_.is_not_a_date_time();
    }

    bool is_infinity()  const
    {
      return (is_pos_infinity() || is_neg_infinity()); 
    }

    bool is_pos_infinity()  const
    {
      return time_.is_pos_infinity();
    }

    bool is_neg_infinity()  const
    {
      return time_.is_neg_infinity();
    }

    bool is_special() const
    {
      return(is_not_a_date_time() || is_infinity());
    }

    bool operator==(const time_type& rhs) const
    {
      return time_system::is_equal(time_,rhs.time_);
    }

    bool operator<(const time_type& rhs) const
    {
      return time_system::is_less(time_,rhs.time_);
    }

    time_duration_type operator-(const time_type& rhs) const
    {
      return time_system::subtract_times(time_, rhs.time_);
    }

    time_type operator+(const date_duration_type& dd) const
    {
      return time_system::add_days(time_, dd);
    }

    time_type operator+=(const date_duration_type& dd)
    {
      time_ = (time_system::get_time_rep(date() + dd, time_of_day()));
      return time_type(time_);
    }

    time_type operator-(const date_duration_type& dd) const
    {
      return time_system::subtract_days(time_, dd);
    }

    time_type operator-=(const date_duration_type& dd)
    {
      time_ = (time_system::get_time_rep(date() - dd, time_of_day()));
      return time_type(time_);
    }

    time_type operator+(const time_duration_type& td) const
    {
      return time_type(time_system::add_time_duration(time_, td));
    }

    time_type operator+=(const time_duration_type& td)
    {
      time_ = (time_system::get_time_rep(date(), time_of_day() + td));
      return time_type(time_);
    }

    time_type operator-(const time_duration_type& rhs) const
    {
      return time_system::subtract_time_duration(time_, rhs);
    }

    time_type operator-=(const time_duration_type& td) 
    {
      time_ = (time_system::get_time_rep(date(), time_of_day() - td));
      return time_type(time_);
    }

    explicit date_duration(duration_rep day_count) : days_(day_count) {}

    date_duration(const date_duration<duration_rep_traits>& other) :
            days_(other.days_)
    {}

    duration_rep get_rep()const
    {
        return days_;
    }

    bool is_special()const
    {
        return days_.is_special();
    }

    duration_rep_type days() const
    {
        return duration_rep_traits::as_number(days_);
    }

    static date_duration unit()
    {
        return date_duration<duration_rep_traits>(1);
    }

    bool operator==(const date_duration& rhs) const
    {
        return days_ == rhs.days_;
    }

    bool operator<(const date_duration& rhs) const
    {
        return days_ < rhs.days_;
    }

    date_duration& operator-=(const date_duration& rhs)
    {
        //days_ -= rhs.days_;
        days_ = days_ - rhs.days_;
        return *this;
    }

    date_duration& operator+=(const date_duration& rhs)
    {
        days_ = days_ + rhs.days_;
        return *this;
    }

    date_duration operator-() const
    {
        return date_duration<duration_rep_traits>(get_rep() * (-1));
    }

    date_duration& operator/=(int divisor)
    {
        days_ = days_ / divisor;
        return *this;
    }

    bool is_negative() const
    {
        return days_ < 0;
    }

    static int_type as_number(impl_type i) { return i; }

    static int_type as_number(impl_type i) { return i.as_number(); }


    date_itr_base(date_type d) : current_(d) {}

    virtual ~date_itr_base() {}

    date_itr_base& operator++()
    {
      current_ = current_ + get_offset(current_);
      return *this;
    }

    date_itr_base& operator--()
    {
      current_ = current_ + get_neg_offset(current_);
      return *this;
    }

    date_type operator*() {return current_;}

    date_type* operator->() {return &current_;}

    bool operator<  (const date_type& d) {return current_ < d;}

    bool operator<= (const date_type& d) {return current_ <= d;}

    bool operator>  (const date_type& d) {return current_ > d;}

    bool operator>= (const date_type& d) {return current_ >= d;}

    bool operator== (const date_type& d) {return current_ == d;}

    bool operator!= (const date_type& d) {return current_ != d;}

    date_itr(date_type d, int factor=1) :
      date_itr_base<date_type>(d),
      of_(factor)
    {}

    virtual duration_type get_offset(const date_type& current) const
    {
      return of_.get_offset(current);
    }

    virtual duration_type get_neg_offset(const date_type& current) const
    {
      return of_.get_neg_offset(current);
    }

    static std::ostream& format_month(const month_type& month,
                                      std::ostream& os)
    {
      switch (format_type::month_format()) 
      {
        case month_as_short_string: 
        { 
          os << month.as_short_string(); 
          break;
        }
        case month_as_long_string: 
        { 
          os << month.as_long_string(); 
          break;
        }
        case month_as_integer: 
        { 
          os << std::setw(2) << std::setfill('0') << month.as_number();
          break;
        }
     
      }
      return os;
    }
 
    static std::string ymd_to_string(ymd_type ymd)
    {
      typedef typename ymd_type::month_type month_type;
      std::ostringstream ss;
      ss << ymd.year;
      if (format_type::has_date_sep_chars()) {
        ss << format_type::month_sep_char();
      }
      //this name is a bit ugly, oh well....
      month_formatter<month_type,format_type>::format_month(ymd.month, ss);
      if (format_type::has_date_sep_chars()) {
        ss << format_type::day_sep_char();
      }
      ss  << std::setw(2) << std::setfill('0') 
          << ymd.day;
      return ss.str();
    }

    static std::string date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return format_type::not_a_date();
      }
      if (d.is_neg_infinity()) {
        return format_type::neg_infinity();
      }
      if (d.is_pos_infinity()) {
        return format_type::pos_infinity();
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type>::ymd_to_string(ymd);
    }

  static const charT* not_a_date()
  {
    return "not-a-date-time";
  }

  static const charT* pos_infinity()
  {  
    return "+infinity";
  }

  static const charT* neg_infinity()
  {
    return "-infinity";
  }

  static month_format_spec month_format()
  {
    return month_as_short_string;
  }

  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }

  static bool has_date_sep_chars()
  {
    return true;
  }

  static charT year_sep_char()
  {
    return '-';
  }

  static charT month_sep_char()
  {
    return '-';
  }

  static charT day_sep_char()
  {
    return '-';
  }

  static charT hour_sep_char()
  {
    return ' ';
  }

  static charT minute_sep_char()
  {
    return ':';
  }

  static charT second_sep_char()
  {
    return ':';
  }

  static const wchar_t* not_a_date()
  {
    return L"not-a-date-time";
  }

  static const wchar_t* pos_infinity()
  {   
    return L"+infinity";
  }

  static const wchar_t* neg_infinity()
  {
    return L"-infinity";
  }

  static month_format_spec month_format()
  {
    return month_as_short_string;
  }

  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }

  static bool has_date_sep_chars()
  {
    return true;
  }

  static wchar_t year_sep_char()
  {
    return '-';
  }

  static wchar_t month_sep_char()
  {
    return '-';
  }

  static wchar_t day_sep_char()
  {
    return '-';
  }

  static wchar_t hour_sep_char()
  {
    return ' ';
  }

  static wchar_t minute_sep_char()
  {
    return ':';
  }

  static wchar_t second_sep_char()
  {
    return ':';
  }

    static ostream_type& format_month(const month_type& month,
                                      ostream_type &os)
    {
      switch (format_type::month_format()) 
      {
        case month_as_short_string: 
        { 
          os << month.as_short_string(); 
          break;
        }
        case month_as_long_string: 
        { 
          os << month.as_long_string(); 
          break;
        }
        case month_as_integer: 
        { 
          os << std::setw(2) << std::setfill(os.widen('0')) << month.as_number();
          break;
        }
        default:
          break;
          
      }
      return os;
    }

    static string_type date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return string_type(format_type::not_a_date());
      }
      if (d.is_neg_infinity()) {
        return string_type(format_type::neg_infinity());
      }
      if (d.is_pos_infinity()) {
        return string_type(format_type::pos_infinity());
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type, charT>::ymd_to_string(ymd);
    }

    static void format_month(const month_type& month,
                             ostream_type& os,
                             const facet_type& f)
    {

      switch (f.month_format())
      {
        case month_as_short_string:
        {
          std::ostreambuf_iterator<charT> oitr(os);
          f.put_month_short(oitr, month.as_enum());
          break;
        }
        case month_as_long_string:
        {
          std::ostreambuf_iterator<charT> oitr(os);
          f.put_month_long(oitr, month.as_enum());
          break;
        }
        case month_as_integer:
        {
          charT fill_char = '0';
          os << std::setw(2) << std::setfill(fill_char) << month.as_number();
          break;
        }

      }
    }

    static void format_weekday(const weekday_type& wd,
                               ostream_type& os,
                               const facet_type& f,
                               bool  as_long_string)
    {

      std::ostreambuf_iterator<charT> oitr(os);
      if (as_long_string) {
        f.put_weekday_long(oitr, wd.as_enum());
      }
      else {
        f.put_weekday_short(oitr, wd.as_enum());
      }

    }

    static void ymd_put(ymd_type ymd,
                        ostream_type& os,
                        const facet_type& f)
    {
      std::ostreambuf_iterator<charT> oitr(os);
      charT fill_char = '0';
      switch (f.date_order()) {
        case ymd_order_iso: {
          os << ymd.year;
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
            f.day_sep_char(oitr);
          }
          os  << std::setw(2) << std::setfill(fill_char)
              << ymd.day;
          break;
        }
        case ymd_order_us: {
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
          f.day_sep_char(oitr);
          }
          os  << std::setw(2) << std::setfill(fill_char)
            << ymd.day;
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          os << ymd.year;
          break;
        }
        case ymd_order_dmy: {
          os  << std::setw(2) << std::setfill(fill_char)
              << ymd.day;
          if (f.has_date_sep_chars()) {
            f.day_sep_char(oitr);
          }
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          os << ymd.year;
          break;
        }
      }
    }

    static void date_put(const date_type& d,
                         ostream_type& os,
                         const facet_type& f)
    {
      special_values sv = d.as_special();
      if (sv == not_special) {
        ymd_type ymd = d.year_month_day();
        ostream_ymd_formatter<ymd_type, facet_type, charT>::ymd_put(ymd, os, f);
      }
      else { // output a special value
        std::ostreambuf_iterator<charT> coi(os);
        f.put_special_value(coi, sv);
      }
    }

  int_adapter(int_type v) :
    value_(v)
  {}

  static bool has_infinity()
  {
    return  true;
  }

  static const int_adapter  pos_infinity()
  {
    return (::std::numeric_limits<int_type>::max)();
  }

  static const int_adapter  neg_infinity()
  {
    return (::std::numeric_limits<int_type>::min)();
  }

  static const int_adapter  not_a_number()
  {
    return (::std::numeric_limits<int_type>::max)()-1;
  }

  int compare(const int_adapter& rhs)const
  {
    if(this->is_special() || rhs.is_special())
    {
      if(this->is_nan() || rhs.is_nan()) {
        if(this->is_nan() && rhs.is_nan()) {
          return 0; // equal
        }
        else {
          return 2; // nan
        }
      }
      if((is_neg_inf(value_) && !is_neg_inf(rhs.value_)) ||
         (is_pos_inf(rhs.value_) && !is_pos_inf(value_)) )
        {
          return -1; // less than
        }
      if((is_pos_inf(value_) && !is_pos_inf(rhs.value_)) ||
         (is_neg_inf(rhs.value_) && !is_neg_inf(value_)) ) {
        return 1; // greater than
      }
    }
    if(value_ < rhs.value_) return -1;
    if(value_ > rhs.value_) return 1;
    // implied-> if(value_ == rhs.value_) 
    return 0;
  }

  int_adapter mult_div_specials(const int_adapter& rhs)const
  {
    int min_value; 
    // quiets compiler warnings
    bool is_signed = std::numeric_limits<int_type>::is_signed;
    if(is_signed) {
      min_value = 0;
    }
    else {
      min_value = 1;// there is no zero with unsigned
    }
    if(this->is_nan() || rhs.is_nan()) {
      return int_adapter<int_type>(not_a_number());
    }
    if((*this > 0 && rhs > 0) || (*this < min_value && rhs < min_value)) {
        return int_adapter<int_type>(pos_infinity());
    }
    if((*this > 0 && rhs < min_value) || (*this < min_value && rhs > 0)) {
        return int_adapter<int_type>(neg_infinity());
    }
    //implied -> if(this->value_ == 0 || rhs.value_ == 0)
    return int_adapter<int_type>(not_a_number());
  }

  int_adapter mult_div_specials(const int& rhs) const
  {
    int min_value; 
    // quiets compiler warnings
    bool is_signed = std::numeric_limits<int_type>::is_signed;
    if(is_signed) {
      min_value = 0;
    }
    else {
      min_value = 1;// there is no zero with unsigned
    }
    if(this->is_nan()) {
      return int_adapter<int_type>(not_a_number());
    }
    if((*this > 0 && rhs > 0) || (*this < min_value && rhs < 0)) {
        return int_adapter<int_type>(pos_infinity());
    }
    if((*this > 0 && rhs < 0) || (*this < min_value && rhs > 0)) {
        return int_adapter<int_type>(neg_infinity());
    }
    //implied -> if(this->value_ == 0 || rhs.value_ == 0)
    return int_adapter<int_type>(not_a_number());
  }

  template<class int_type>
  inline
  int_type power(int_type base, int_type exponent)
  {
    int_type result = 1;
    for(int i = 0; i < exponent; ++i){
      result *= base;
    }
    return result;
  }

  template<class time_duration, class char_type>
  inline
  time_duration
  str_from_delimited_time_duration(const std::basic_string<char_type>& s)
  {
    unsigned short min=0, sec =0;
    int hour =0; 
    bool is_neg = (s.at(0) == '-');
    boost::int64_t fs=0;
    int pos = 0;
      
    typedef typename std::basic_string<char_type>::traits_type traits_type;
    typedef boost::char_separator<char_type, traits_type> char_separator_type;
    typedef boost::tokenizer<char_separator_type,
                             typename std::basic_string<char_type>::const_iterator,
                             std::basic_string<char_type> > tokenizer;
    typedef typename boost::tokenizer<char_separator_type,
                             typename std::basic_string<char_type>::const_iterator,
                             typename std::basic_string<char_type> >::iterator tokenizer_iterator;
   
    char_type sep_chars[5] = {'-',':',',','.'};
    char_separator_type sep(sep_chars);
    tokenizer tok(s,sep);
    for(tokenizer_iterator beg=tok.begin(); beg!=tok.end();++beg){
      switch(pos) {
      case 0: {
        hour = boost::lexical_cast<int>(*beg);
        break;
      }
      case 1: {
        min = boost::lexical_cast<unsigned short>(*beg);
        break;
      }
      case 2: {
        sec = boost::lexical_cast<unsigned short>(*beg);
        break;
      };
      case 3: {
        int digits = static_cast<int>(beg->length());
        //Works around a bug in MSVC 6 library that does not support
        //operator>> thus meaning lexical_cast will fail to compile.
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
        // msvc wouldn't compile 'time_duration::num_fractional_digits()' 
        // (required template argument list) as a workaround a temp 
        // time_duration object was used
        time_duration td(hour,min,sec,fs);
        int precision = td.num_fractional_digits();
        // _atoi64 is an MS specific function
        if(digits >= precision) {
          // drop excess digits
          fs = _atoi64(beg->substr(0, precision).c_str());
        }
        else {
          fs = _atoi64(beg->c_str());
        }
#else
        int precision = time_duration::num_fractional_digits();
        if(digits >= precision) {
          // drop excess digits
          fs = boost::lexical_cast<boost::int64_t>(beg->substr(0, precision));
        }
        else {
          fs = boost::lexical_cast<boost::int64_t>(*beg);
        }
#endif
        if(digits < precision){
          // trailing zeros get dropped from the string, 
          // "1:01:01.1" would yield .000001 instead of .100000
          // the power() compensates for the missing decimal places
          fs *= power(10, precision - digits); 
        }
        
        break;
      }
      default: break;
      }//switch
      pos++;
    }
    if(is_neg) {
      return -time_duration(hour, min, sec, fs);
    }
    else {
      return time_duration(hour, min, sec, fs);
    }
  }

  template<class time_duration>
  inline
  time_duration
  parse_delimited_time_duration(const std::string& s)
  {
    return str_from_delimited_time_duration<time_duration,char>(s);
  }

  inline
  bool 
  split(const std::string& s,
        char sep,
        std::string& first,
        std::string& second)
  {
    std::string::size_type sep_pos = s.find(sep);
    first = s.substr(0,sep_pos);
    if (sep_pos!=std::string::npos)
        second = s.substr(sep_pos+1);
    return true;
  }



  template<class time_type>
  inline
  time_type
  parse_delimited_time(const std::string& s, char sep)
  {
    typedef typename time_type::time_duration_type time_duration;
    typedef typename time_type::date_type date_type;

    //split date/time on a unique delimiter char such as ' ' or 'T'
    std::string date_string, tod_string;
    split(s, sep, date_string, tod_string);
    //call parse_date with first string
    date_type d = parse_date<date_type>(date_string);
    //call parse_time_duration with remaining string
    time_duration td = parse_delimited_time_duration<time_duration>(tod_string);
    //construct a time
    return time_type(d, td);

  }

  template<class time_duration>
  inline
  time_duration
  parse_undelimited_time_duration(const std::string& s)
  {
    int precision = 0;
    {
      // msvc wouldn't compile 'time_duration::num_fractional_digits()' 
      // (required template argument list) as a workaround, a temp 
      // time_duration object was used
      time_duration tmp(0,0,0,1);
      precision = tmp.num_fractional_digits();
    }
    // 'precision+1' is so we grab all digits, plus the decimal
    int offsets[] = {2,2,2, precision+1};
    int pos = 0, sign = 0;
    int hours = 0;
    short min=0, sec=0;
    boost::int64_t fs=0;
    // increment one position if the string was "signed"
    if(s.at(sign) == '-')
    {
      ++sign;
    }
    // stlport choked when passing s.substr() to tokenizer
    // using a new string fixed the error
    std::string remain = s.substr(sign);
    /* We do not want the offset_separator to wrap the offsets, we 
     * will never want to  process more than: 
     * 2 char, 2 char, 2 char, frac_sec length.
     * We *do* want the offset_separator to give us a partial for the
     * last characters if there were not enough provided in the input string. */
    bool wrap_off = false;
    bool ret_part = true;
    boost::offset_separator osf(offsets, offsets+4, wrap_off, ret_part); 
    typedef boost::tokenizer<boost::offset_separator,
                             std::basic_string<char>::const_iterator,
                             std::basic_string<char> > tokenizer;
    typedef boost::tokenizer<boost::offset_separator,
                             std::basic_string<char>::const_iterator,
                             std::basic_string<char> >::iterator tokenizer_iterator;
    tokenizer tok(remain, osf);
    for(tokenizer_iterator ti=tok.begin(); ti!=tok.end();++ti){
      switch(pos) {
        case 0: 
          {
            hours = boost::lexical_cast<int>(*ti); 
            break;
          }
        case 1: 
          {
            min = boost::lexical_cast<short>(*ti); 
            break;
          }
        case 2: 
          {
            sec = boost::lexical_cast<short>(*ti); 
            break;
          }
        case 3:
          {
            std::string char_digits(ti->substr(1)); // digits w/no decimal
            int digits = static_cast<int>(char_digits.length());
            
            //Works around a bug in MSVC 6 library that does not support
            //operator>> thus meaning lexical_cast will fail to compile.
#if (defined(BOOST_MSVC) && (_MSC_VER <= 1200))  // 1200 == VC++ 6.0
            // _atoi64 is an MS specific function
            if(digits >= precision) {
              // drop excess digits
              fs = _atoi64(char_digits.substr(0, precision).c_str());
            }
            else if(digits == 0) {
              fs = 0; // just in case _atoi64 doesn't like an empty string
            }
            else {
              fs = _atoi64(char_digits.c_str());
            }
#else
            if(digits >= precision) {
              // drop excess digits
              fs = boost::lexical_cast<boost::int64_t>(char_digits.substr(0, precision));
            }
            else if(digits == 0) {
              fs = 0; // lexical_cast doesn't like empty strings
            }
            else {
              fs = boost::lexical_cast<boost::int64_t>(char_digits);
            }
#endif
            if(digits < precision){
              // trailing zeros get dropped from the string, 
              // "1:01:01.1" would yield .000001 instead of .100000
              // the power() compensates for the missing decimal places
              fs *= power(10, precision - digits); 
            }
            
            break;
          }
          default: break;
      };
      pos++;
    }
    if(sign) {
      return -time_duration(hours, min, sec, fs);
    }
    else {
      return time_duration(hours, min, sec, fs);
    }
  }

  template<class time_type>
  inline
  time_type
  parse_iso_time(const std::string& s, char sep)
  {
    typedef typename time_type::time_duration_type time_duration;
    typedef typename time_type::date_type date_type;

    //split date/time on a unique delimiter char such as ' ' or 'T'
    std::string date_string, tod_string;
    split(s, sep, date_string, tod_string);
    //call parse_date with first string
    date_type d = parse_undelimited_date<date_type>(date_string);
    //call parse_time_duration with remaining string
    time_duration td = parse_undelimited_time_duration<time_duration>(tod_string);
    //construct a time
    return time_type(d, td);
  }

  inline
  std::string
  convert_to_lower(std::string inp)
  {
#if !defined(BOOST_DATE_TIME_NO_LOCALE)
    const std::locale loc(std::locale::classic());
#endif
    std::string::size_type i = 0, n = inp.length();
    for (; i < n; ++i) {
      inp[i] =
#if defined(BOOST_DATE_TIME_NO_LOCALE)
        static_cast<char>(std::tolower(inp[i]));
#else
        // tolower and others were brought in to std for borland >= v564
        // in compiler_config.hpp
        std::tolower(inp[i], loc);
#endif
    }
    return inp;
  }

    template<class charT>
    short find_match(const charT* const* short_names,
                     const charT* const* long_names,
                     short size,
                     const std::basic_string<charT>& s) {
      for(short i = 0; i < size; ++i){
        if(short_names[i] == s || long_names[i] == s){
          return i;
        }
      }
      return size; // not-found, return a value out of range
    }

    template<class date_type>
    date_type
    parse_date(const std::string& s, int order_spec = ymd_order_iso) {
      std::string spec_str;
      if(order_spec == ymd_order_iso) {
        spec_str = "ymd";
      }
      else if(order_spec == ymd_order_dmy) {
        spec_str = "dmy";
      }
      else { // (order_spec == ymd_order_us)
        spec_str = "mdy";
      }

      typedef typename date_type::year_type year_type;
      typedef typename date_type::month_type month_type;
      unsigned pos = 0;
      unsigned short year(0), month(0), day(0);
      typedef typename std::basic_string<char>::traits_type traits_type;
      typedef boost::char_separator<char, traits_type> char_separator_type;
      typedef boost::tokenizer<char_separator_type,
                               std::basic_string<char>::const_iterator,
                               std::basic_string<char> > tokenizer;
      typedef boost::tokenizer<char_separator_type,
                               std::basic_string<char>::const_iterator,
                               std::basic_string<char> >::iterator tokenizer_iterator;
      // may need more delimiters, these work for the regression tests
      const char sep_char[] = {',','-','.',' ','/','\0'};
      char_separator_type sep(sep_char);
      tokenizer tok(s,sep);
      for(tokenizer_iterator beg=tok.begin();
          beg!=tok.end() && pos < spec_str.size();
          ++beg, ++pos) {
        switch(spec_str.at(pos)) {
          case 'y':
          {
            year = boost::lexical_cast<unsigned short>(*beg);
            break;
          }
          case 'm':
          {
            month = month_str_to_ushort<month_type>(*beg);
            break;
          }
          case 'd':
          {
            day = boost::lexical_cast<unsigned short>(*beg);
            break;
          }
          default: break;
        } //switch
      }
      return date_type(year, month, day);
    }

    template<class date_type>
    date_type
    parse_undelimited_date(const std::string& s) {
      int offsets[] = {4,2,2};
      int pos = 0;
      typedef typename date_type::year_type year_type;
      //typename date_type::ymd_type ymd((year_type::min)(),1,1);
      unsigned short y = 0, m = 0, d = 0;

      /* The two bool arguments state that parsing will not wrap
       * (only the first 8 characters will be parsed) and partial
       * strings will not be parsed.
       * Ex:
       * "2005121" will parse 2005 & 12, but not the "1" */
      boost::offset_separator osf(offsets, offsets+3, false, false);

      typedef typename boost::tokenizer<boost::offset_separator,
                                        std::basic_string<char>::const_iterator,
                                        std::basic_string<char> > tokenizer_type;
      tokenizer_type tok(s, osf);
      for(typename tokenizer_type::iterator ti=tok.begin(); ti!=tok.end();++ti) {
        unsigned short i = boost::lexical_cast<unsigned short>(*ti);
        switch(pos) {
        case 0: y = i; break;
        case 1: m = i; break;
        case 2: d = i; break;
        default:       break;
        }
        pos++;
      }
      return date_type(y,m,d);
    }

    template<class date_type, class iterator_type>
    inline
    date_type
    from_stream_type(iterator_type& beg,
                     iterator_type const& end,
                     char)
    {
      std::ostringstream ss;
      while(beg != end) {
        ss << *beg++;
      }
      return parse_date<date_type>(ss.str());
    }

    template<class date_type, class iterator_type>
    inline
    date_type from_stream_type(iterator_type& beg,
                               iterator_type const& end,
                               wchar_t)
    {
      std::ostringstream ss;
#if !defined(BOOST_DATE_TIME_NO_LOCALE)
      std::locale loc;
      std::ctype<wchar_t> const& fac = std::use_facet<std::ctype<wchar_t> >(loc);
      while(beg != end) {
        ss << fac.narrow(*beg++, 'X'); // 'X' will cause exception to be thrown
      }
#else
      while(beg != end) {
        char c = 'X'; // 'X' will cause exception to be thrown
        const wchar_t wc = *beg++;
        if (wc >= 0 && wc <= 127)
          c = static_cast< char >(wc);
        ss << c;
      }
#endif
      return parse_date<date_type>(ss.str());
    }

  template<typename YearType, typename MonthType, typename DayType>
  inline
  year_month_day_base<YearType,MonthType,DayType>::year_month_day_base(YearType y, 
                                                                       MonthType m,
                                                                       DayType d) :
    year(y),
    month(m),
    day(d)
  {}

  template<class point_rep, class duration_rep>
  inline
  period<point_rep,duration_rep>::period(point_rep first_point, 
                                         point_rep end_point) : 
    begin_(first_point), 
    last_(end_point - duration_rep::unit())
  {}

  template<class point_rep, class duration_rep>
  inline
  period<point_rep,duration_rep>::period(point_rep first_point, duration_rep len) :
    begin_(first_point), 
    last_(first_point + len-duration_rep::unit())
  { }

  template<class point_rep, class duration_rep>
  inline
  point_rep period<point_rep,duration_rep>::begin() const 
  {
    return begin_;
  }

  template<class point_rep, class duration_rep>
  inline
  point_rep period<point_rep,duration_rep>::end() const 
  {
    return last_ + duration_rep::unit();
  }

  template<class point_rep, class duration_rep>
  inline
  point_rep period<point_rep,duration_rep>::last() const 
  {
    return last_;
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::is_null() const 
  {
    return end() <= begin_;
  }

  template<class point_rep, class duration_rep>
  inline
  duration_rep period<point_rep,duration_rep>::length() const
  {
    if(last_ < begin_){ // invalid period
      return last_+duration_rep::unit() - begin_;
    }
    else{
      return end() - begin_; // normal case
    }
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::operator==(const period& rhs) const 
  {
    return  ((begin_ == rhs.begin_) && 
             (last_ == rhs.last_));
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::operator<(const period& rhs) const 
  {
    return (last_ < rhs.begin_);
  }

  template<class point_rep, class duration_rep>
  inline
  void period<point_rep,duration_rep>::shift(const duration_rep& d)
  {
    begin_ = begin_ + d;
    last_  = last_  + d;
  }

  template<class point_rep, class duration_rep>
  inline
  void period<point_rep,duration_rep>::expand(const duration_rep& d)
  {
    begin_ = begin_ - d;
    last_  = last_  + d;
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::contains(const point_rep& point) const 
  {
    return ((point >= begin_) &&
            (point <= last_));
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::contains(const period<point_rep,duration_rep>& other) const
  {
    return ((begin_ <= other.begin_) && (last_ >= other.last_));
  }

  template<class point_rep, class duration_rep>
  inline
  bool 
  period<point_rep,duration_rep>::is_adjacent(const period<point_rep,duration_rep>& other) const 
  {
    return (other.begin() == end() ||
            begin_ == other.end());
  }

  template<class point_rep, class duration_rep>
  inline
  bool 
  period<point_rep,duration_rep>::is_after(const point_rep& t) const 
  { 
    if (is_null()) 
    {
      return false; //null period isn't after
    }
    
    return t < begin_;
  }

  template<class point_rep, class duration_rep>
  inline
  bool 
  period<point_rep,duration_rep>::is_before(const point_rep& t) const 
  { 
    if (is_null()) 
    {
      return false;  //null period isn't before anything
    }
    
    return last_ < t;
  }

  template<class point_rep, class duration_rep>
  inline
  bool period<point_rep,duration_rep>::intersects(const period<point_rep,duration_rep>& other) const 
  { 
    return ( contains(other.begin_) ||
             other.contains(begin_) ||
             ((other.begin_ < begin_) && (other.last_ >= begin_)));
  }

  template<class point_rep, class duration_rep>
  inline
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::intersection(const period<point_rep,duration_rep>& other) const 
  {
    if (begin_ > other.begin_) {
      if (last_ <= other.last_) { //case2
        return *this;  
      }
      //case 1
      return period<point_rep,duration_rep>(begin_, other.end());
    }
    else {
      if (last_ <= other.last_) { //case3
        return period<point_rep,duration_rep>(other.begin_, this->end());
      }
      //case4
      return other;
    }
    //unreachable
  }

  template<class point_rep, class duration_rep>
  inline
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::merge(const period<point_rep,duration_rep>& other) const 
  {
    if (this->intersects(other)) {      
      if (begin_ < other.begin_) {
        return period<point_rep,duration_rep>(begin_, last_ > other.last_ ? this->end() : other.end());
      }
      
      return period<point_rep,duration_rep>(other.begin_, last_ > other.last_ ? this->end() : other.end());
      
    }
    return period<point_rep,duration_rep>(begin_,begin_); // no intersect return null
  }

  template<class point_rep, class duration_rep>
  inline
  period<point_rep,duration_rep>
  period<point_rep,duration_rep>::span(const period<point_rep,duration_rep>& other) const 
  {
    point_rep start((begin_ < other.begin_) ? begin() : other.begin());
    point_rep newend((last_  < other.last_)  ? other.end() : this->end());
    return period<point_rep,duration_rep>(start, newend);
  }


    time_zone_base() {}

    virtual ~time_zone_base() {}

    dst_adjustment_offsets(const time_duration_type& dst_adjust,
                           const time_duration_type& dst_start_offset,
                           const time_duration_type& dst_end_offset) :
      dst_adjust_(dst_adjust),
      dst_start_offset_(dst_start_offset),
      dst_end_offset_(dst_end_offset)
    {}

    day_functor(int f) : f_(f) {}

    duration_type get_offset(const date_type& d) const 
    {
      // why is 'd' a parameter???
      // fix compiler warnings
      d.year();
      return duration_type(f_);
    }

    duration_type get_neg_offset(const date_type& d) const 
    {
      // fix compiler warnings
      d.year();
      return duration_type(-f_);
    }


    month_functor(int f) : f_(f), origDayOfMonth_(0) {}

    duration_type get_offset(const date_type& d) const 
    {
      ymd_type ymd(d.year_month_day());
      if (origDayOfMonth_ == 0) {
        origDayOfMonth_ = ymd.day;
        day_type endOfMonthDay(cal_type::end_of_month_day(ymd.year,ymd.month));
        if (endOfMonthDay == ymd.day) {
          origDayOfMonth_ = -1; //force the value to the end of month
        }
      }
      typedef date_time::wrapping_int2<short,1,12> wrap_int2;
      typedef typename wrap_int2::int_type int_type;
      wrap_int2 wi(ymd.month);
      //calc the year wrap around, add() returns 0 or 1 if wrapped
      int_type year = wi.add(static_cast<int_type>(f_)); 
      year = static_cast<int_type>(year + ymd.year); //calculate resulting year
//       std::cout << "trace wi: " << wi.as_int() << std::endl;
//       std::cout << "trace year: " << year << std::endl;
      //find the last day for the new month
      day_type resultingEndOfMonthDay(cal_type::end_of_month_day(year, wi.as_int()));
      //original was the end of month -- force to last day of month
      if (origDayOfMonth_ == -1) {
        return date_type(year, wi.as_int(), resultingEndOfMonthDay) - d;
      }
      day_type dayOfMonth = origDayOfMonth_;
      if (dayOfMonth > resultingEndOfMonthDay) {
        dayOfMonth = resultingEndOfMonthDay;
      }
      return date_type(year, wi.as_int(), dayOfMonth) - d;
    }

    duration_type get_neg_offset(const date_type& d) const 
    {
      ymd_type ymd(d.year_month_day());
      if (origDayOfMonth_ == 0) {
        origDayOfMonth_ = ymd.day;
        day_type endOfMonthDay(cal_type::end_of_month_day(ymd.year,ymd.month));
        if (endOfMonthDay == ymd.day) {
          origDayOfMonth_ = -1; //force the value to the end of month
        }
      }
      typedef date_time::wrapping_int2<short,1,12> wrap_int2;
      typedef typename wrap_int2::int_type int_type;
      wrap_int2 wi(ymd.month);
      //calc the year wrap around, add() returns 0 or 1 if wrapped
      int_type year = wi.subtract(static_cast<int_type>(f_)); 
      year = static_cast<int_type>(year + ymd.year); //calculate resulting year
      //find the last day for the new month
      day_type resultingEndOfMonthDay(cal_type::end_of_month_day(year, wi.as_int()));
      //original was the end of month -- force to last day of month
      if (origDayOfMonth_ == -1) {
        return date_type(year, wi.as_int(), resultingEndOfMonthDay) - d;
      }
      day_type dayOfMonth = origDayOfMonth_;
      if (dayOfMonth > resultingEndOfMonthDay) {
        dayOfMonth = resultingEndOfMonthDay;
      }
      return date_type(year, wi.as_int(), dayOfMonth) - d;
    }

    week_functor(int f) : f_(f) {}

    duration_type get_offset(const date_type& d) const 
    {
      // why is 'd' a parameter???
      // fix compiler warnings
      d.year();
      return duration_type(f_*calendar_type::days_in_week());
    }

    duration_type get_neg_offset(const date_type& d) const 
    {
      // fix compiler warnings
      d.year();
      return duration_type(-f_*calendar_type::days_in_week());
    }

    year_functor(int f) : _mf(f * 12) {}

    duration_type get_offset(const date_type& d) const 
    {
      return _mf.get_offset(d);
    }

    duration_type get_neg_offset(const date_type& d) const 
    {
      return _mf.get_neg_offset(d);
    }

  parse_match_result() :
    match_depth(0),
    current_match(-1)// -1 is match_not-found value
  {}

  string_type remaining() const
  {
    if (match_depth == cache.size()) {
      return string_type();
    }
    if (current_match == -1) {
      return cache;
    }
    //some of the cache was used return the rest
    return string_type(cache, match_depth);
  }

  charT last_char() const
  {
    return cache[cache.size()-1];
  }

  bool has_remaining() const
  {
    return (cache.size() > match_depth);
  }

    year_based_generator() {}

    virtual ~year_based_generator() {}

   partial_date(day_type d, month_type m) :
     day_(d),
     month_(m)
   {}

   partial_date(duration_rep days) :
     day_(1), // default values
     month_(1)
   {
     date_type d1(2000,1,1);
     if(days > 1) {
       if(days > 366) // prevents wrapping
       {
         days = 366;
       }
       days = days - 1;
       duration_type dd(days);
       d1 = d1 + dd;
     }
     day_ = d1.day();
     month_ = d1.month();
   }

   date_type get_date(year_type y) const
   {
     if((day_ == 29) && (month_ == 2) && !(calendar_type::is_leap_year(y))) {
       std::ostringstream ss;
       ss << "No Feb 29th in given year of " << y << ".";
       boost::throw_exception(std::invalid_argument(ss.str()));
     }
     return date_type(y, month_, day_);
   }

   date_type operator()(year_type y) const
   {
     return get_date(y);
     //return date_type(y, month_, day_);
   }

   bool operator==(const partial_date& rhs) const
   {
     return (month_ == rhs.month_) && (day_ == rhs.day_);
   }

   bool operator<(const partial_date& rhs) const
   {
     if (month_ < rhs.month_) return true;
     if (month_ > rhs.month_) return false;
     //months are equal
     return (day_ < rhs.day_);
   }

   month_type month() const
   {
     return month_;
   }

   day_type day() const
   {
     return day_;
   }

   virtual std::string to_string() const
   {
     std::ostringstream ss;
     date_type d(2004, month_, day_);
     unsigned short c = d.day_of_year();
     c--; // numbered 0-365 while day_of_year is 1 based...
     ss << c;
     return ss.str();
   }

    nth_kday_of_month(week_num week_no,
                      day_of_week_type dow,
                      month_type m) :
      month_(m),
      wn_(week_no),
      dow_(dow)
    {}

    date_type get_date(year_type y) const
    {
      date_type d(y, month_, 1); //first day of month
      duration_type one_day(1);
      duration_type one_week(7);
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      int week = 1;
      while (week < wn_) {
        d = d + one_week;
        week++;
      }
      // remove wrapping to next month behavior
      if(d.month() != month_) {
        d = d - one_week;
      }
      return d;
    }

    month_type month() const
    {
      return month_;
    }

    week_num nth_week() const
    {
      return wn_;
    }

    day_of_week_type day_of_week() const
    {
      return dow_;
    }

    const char* nth_week_as_str() const
    {
      return nth_as_str(wn_);
    }

    virtual std::string to_string() const
    {
     std::ostringstream ss;
     ss << 'M'
       << static_cast<int>(month_) << '.'
       << static_cast<int>(wn_) << '.'
       << static_cast<int>(dow_);
     return ss.str();
    }

    first_kday_of_month(day_of_week_type dow, month_type m) :
      month_(m),
      dow_(dow)
    {}

    date_type get_date(year_type year) const
    {
      date_type d(year, month_,1);
      duration_type one_day(1);
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      return d;
    }

    month_type month() const
    {
      return month_;
    }

    day_of_week_type day_of_week() const
    {
      return dow_;
    }

    virtual std::string to_string() const
    {
     std::ostringstream ss;
     ss << 'M'
       << static_cast<int>(month_) << '.'
       << 1 << '.'
       << static_cast<int>(dow_);
     return ss.str();
    }

    last_kday_of_month(day_of_week_type dow, month_type m) :
      month_(m),
      dow_(dow)
    {}

    date_type get_date(year_type year) const
    {
      date_type d(year, month_, calendar_type::end_of_month_day(year,month_));
      duration_type one_day(1);
      while (dow_ != d.day_of_week()) {
        d = d - one_day;
      }
      return d;
    }

    month_type month() const
    {
      return month_;
    }

    day_of_week_type day_of_week() const
    {
      return dow_;
    }

    virtual std::string to_string() const
    {
      std::ostringstream ss;
      ss << 'M'
         << static_cast<int>(month_) << '.'
         << 5 << '.'
         << static_cast<int>(dow_);
      return ss.str();
    }

    first_kday_after(day_of_week_type dow) :
      dow_(dow)
    {}

    date_type get_date(date_type start_day) const
    {
      duration_type one_day(1);
      date_type d = start_day + one_day;
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      return d;
    }

    day_of_week_type day_of_week() const
    {
      return dow_;
    }

    first_kday_before(day_of_week_type dow) :
      dow_(dow)
    {}

    date_type get_date(date_type start_day) const
    {
      duration_type one_day(1);
      date_type d = start_day - one_day;
      while (dow_ != d.day_of_week()) {
        d = d - one_day;
      }
      return d;
    }

    day_of_week_type day_of_week() const
    {
      return dow_;
    }

  template<typename date_type, class weekday_type>
  inline
  typename date_type::duration_type days_until_weekday(const date_type& d, const weekday_type& wd)
  {
    typedef typename date_type::duration_type duration_type;
    duration_type wks(0);
    duration_type dd(wd.as_number() - d.day_of_week().as_number());
    if(dd.is_negative()){
      wks = duration_type(7);
    }
    return dd + wks;
  }

  template<typename date_type, class weekday_type>
  inline
  typename date_type::duration_type days_before_weekday(const date_type& d, const weekday_type& wd)
  {
    typedef typename date_type::duration_type duration_type;
    duration_type wks(0);
    duration_type dd(wd.as_number() - d.day_of_week().as_number());
    if(dd.days() > 0){
      wks = duration_type(7);
    }
    // we want a number of days, not an offset. The value returned must
    // be zero or larger.
    return (-dd + wks);
  }

  template<class date_type, class weekday_type>
  inline
  date_type next_weekday(const date_type& d, const weekday_type& wd)
  {
    return d + days_until_weekday(d, wd);
  }

  template<class date_type, class weekday_type>
  inline
  date_type previous_weekday(const date_type& d, const weekday_type& wd)
  {
    return d - days_before_weekday(d, wd);
  }

    static time_type utc_to_local(const time_type& t)
    {
      date_type time_t_start_day(1970,1,1);
      time_type time_t_start_time(time_t_start_day,time_duration_type(0,0,0));
      if (t < time_t_start_time) {
        boost::throw_exception(std::out_of_range("Cannot convert dates prior to Jan 1, 1970"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_t_start_time); // should never reach
      }
      date_duration_type dd = t.date() - time_t_start_day;
      time_duration_type td = t.time_of_day();
      std::time_t t2 = dd.days()*86400 + td.hours()*3600 + td.minutes()*60 + td.seconds();
      std::tm tms, *tms_ptr;
      tms_ptr = c_time::localtime(&t2, &tms);
      date_type d(static_cast<unsigned short>(tms_ptr->tm_year + 1900),
                  static_cast<unsigned short>(tms_ptr->tm_mon + 1),
                  static_cast<unsigned short>(tms_ptr->tm_mday));
      time_duration_type td2(tms_ptr->tm_hour,
                             tms_ptr->tm_min,
                             tms_ptr->tm_sec,
                             t.time_of_day().fractional_seconds());
      
      return time_type(d,td2);
    }

      static time_is_dst_result 
      process_local_dst_start_day(const time_duration_type& time_of_day,
                                  unsigned int dst_start_offset_minutes,
                                  long dst_length_minutes)
      {
        //std::cout << "here" << std::endl;
        if (time_of_day < time_duration_type(0,dst_start_offset_minutes,0)) {
          return is_not_in_dst;
        }
        long offset = dst_start_offset_minutes + dst_length_minutes;
        if (time_of_day >= time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        return invalid_time_label; 
      }

      static time_is_dst_result 
      process_local_dst_end_day(const time_duration_type& time_of_day,
                                unsigned int dst_end_offset_minutes,
                                long dst_length_minutes)
      {
        //in US this will be 60 so offset in day is 1,0,0
        int offset = dst_end_offset_minutes-dst_length_minutes;
        if (time_of_day < time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        if (time_of_day >= time_duration_type(0,dst_end_offset_minutes,0)) {
          return is_not_in_dst;
        }
        return ambiguous;
      }

      static time_is_dst_result 
      local_is_dst(const date_type& current_day,
                   const time_duration_type& time_of_day,
                   const date_type& dst_start_day,
                   const time_duration_type& dst_start_offset,
                   const date_type& dst_end_day,
                   const time_duration_type& dst_end_offset,
                   const time_duration_type& dst_length_minutes)
      {
        unsigned int start_minutes = 
          dst_start_offset.hours() * 60 + dst_start_offset.minutes();
        unsigned int end_minutes = 
          dst_end_offset.hours() * 60 + dst_end_offset.minutes();
        long length_minutes =  
          dst_length_minutes.hours() * 60 + dst_length_minutes.minutes();

        return local_is_dst(current_day, time_of_day,
                            dst_start_day, start_minutes,
                            dst_end_day, end_minutes,
                            length_minutes);
      }

      static time_is_dst_result 
      local_is_dst(const date_type& current_day,
                   const time_duration_type& time_of_day,
                   const date_type& dst_start_day,
                   unsigned int dst_start_offset_minutes,
                   const date_type& dst_end_day,
                   unsigned int dst_end_offset_minutes,
                   long dst_length_minutes)
      {
        //in northern hemisphere dst is in the middle of the year
        if (dst_start_day < dst_end_day) {
          if ((current_day > dst_start_day) && (current_day < dst_end_day)) {
            return is_in_dst;
          }
          if ((current_day < dst_start_day) || (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
        }
        else {//southern hemisphere dst is at begining /end of year
          if ((current_day < dst_start_day) && (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
          if ((current_day > dst_start_day) || (current_day < dst_end_day)) {
            return is_in_dst;
          }
        }

        if (current_day == dst_start_day) {
          return process_local_dst_start_day(time_of_day,
                                             dst_start_offset_minutes,
                                             dst_length_minutes);
        }
      
        if (current_day == dst_end_day) {
          return process_local_dst_end_day(time_of_day,
                                           dst_end_offset_minutes,
                                           dst_length_minutes);
        }
        //you should never reach this statement
        return invalid_time_label;
      }

      static time_is_dst_result local_is_dst(const date_type& d,
                                             const time_duration_type& td) 
      {

        year_type y = d.year();
        date_type dst_start = local_dst_start_day(y);
        date_type dst_end   = local_dst_end_day(y);
        return dstcalc::local_is_dst(d,td,
                                     dst_start,
                                     dst_traits::dst_start_offset_minutes(),
                                     dst_end, 
                                     dst_traits::dst_end_offset_minutes(), 
                                     dst_traits::dst_shift_length_minutes());
      
      }


      static bool is_dst_boundary_day(date_type d)
      {
        year_type y = d.year();
        return ((d == local_dst_start_day(y)) ||
                (d == local_dst_end_day(y)));
      }

      static time_duration_type dst_offset() 
      {
        return time_duration_type(0,dst_traits::dst_shift_length_minutes(),0);
      }


      static date_type local_dst_start_day(year_type year)
      {
        return dst_traits::local_dst_start_day(year);      
      }


      static date_type local_dst_end_day(year_type year)
      {
        return dst_traits::local_dst_end_day(year);
      }

      static time_is_dst_result local_is_dst(const date_type& d,
                                             const time_duration_type& td) 
      {

        year_type y = d.year();
        date_type dst_start = local_dst_start_day(y);
        date_type dst_end   = local_dst_end_day(y);
        return dstcalc::local_is_dst(d,td,
                                     dst_start,dst_start_offset_minutes,
                                     dst_end, dst_start_offset_minutes, 
                                     dst_length_minutes);
      
      }



      static bool is_dst_boundary_day(date_type d)
      {
        year_type y = d.year();
        return ((d == local_dst_start_day(y)) ||
                (d == local_dst_end_day(y)));
      }


      static date_type local_dst_start_day(year_type year)
      {
        if (year >= year_type(2007)) {
          //second sunday in march
          nkday ssim(nkday::second, Sunday, gregorian::Mar);
          return ssim.get_date(year);      
        } else {
          //first sunday in april
          fkday fsia(Sunday, gregorian::Apr);
          return fsia.get_date(year);      
        }
      }


      static date_type local_dst_end_day(year_type year)
      {
        if (year >= year_type(2007)) {
          //first sunday in november
          fkday fsin(Sunday, gregorian::Nov);
          return fsin.get_date(year);      
        } else {
          //last sunday in october
          lkday lsio(Sunday, gregorian::Oct);
          return lsio.get_date(year);
        }
      }


      static time_duration_type dst_offset()
      {
        return time_duration_type(0,dst_length_minutes,0);
      }

      static time_is_dst_result local_is_dst(const date_type&, 
                                             const time_duration_type&) 
      {
        return is_not_in_dst;
      }

      static time_is_dst_result utc_is_dst(const date_type&, 
                                           const time_duration_type&) 
      {
        return is_not_in_dst;
      }


      static bool is_dst_boundary_day(date_type /*d*/)
      {
        return false;
      }


      static time_duration_type dst_offset() 
      {
        return time_duration_type(0,0,0);
      }

      static time_duration_type local_to_utc_base_offset()
      {
        time_duration_type td(hours,minutes,0);
        return td.invert_sign();
      }

      static time_duration_type utc_to_local_base_offset()
      {
        return time_duration_type(hours,minutes,0);
      }


      dynamic_local_time_adjustor(time_duration_type utc_offset) :
        utc_offset_(utc_offset)
      {}

      time_duration_type utc_offset(bool is_dst) 
      { 
        if (is_dst) {
          return utc_offset_ + this->dst_offset();
        }
        else {
          return utc_offset_;
        }

      }

      static time_duration_type utc_to_local_offset(const time_type& t)
      {
        //get initial local time guess by applying utc offset
        time_type initial = t + utc_offset_rules::utc_to_local_base_offset();
        time_is_dst_result dst_flag = 
          dst_rules::local_is_dst(initial.date(), initial.time_of_day());
        switch(dst_flag) {
        case is_in_dst:        return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case is_not_in_dst:    return utc_offset_rules::utc_to_local_base_offset();
        case invalid_time_label:return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
        case ambiguous: {
          time_type retry = initial + dst_rules::dst_offset();
          dst_flag = dst_rules::local_is_dst(retry.date(), retry.time_of_day());
          //if still ambibuous then the utc time still translates to a dst time
          if (dst_flag == ambiguous) {
            return utc_offset_rules::utc_to_local_base_offset() + dst_rules::dst_offset();
          }
          // we are past the dst boundary
          else {
            return utc_offset_rules::utc_to_local_base_offset();
          }
        }
        }//case
        //TODO  better exception type
        boost::throw_exception(std::out_of_range("Unreachable case"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }

      static time_duration_type local_to_utc_offset(const time_type& t, 
                                                    date_time::dst_flags dst=date_time::calculate) 
      {
        switch (dst) {
        case is_dst:
          return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
        case not_dst:
          return utc_offset_rules::local_to_utc_base_offset();
        case calculate:
          time_is_dst_result res = 
            dst_rules::local_is_dst(t.date(), t.time_of_day());
          switch(res) {
          case is_in_dst:      return utc_offset_rules::local_to_utc_base_offset() - dst_rules::dst_offset();
          case is_not_in_dst:      return utc_offset_rules::local_to_utc_base_offset();
          case ambiguous:          return utc_offset_rules::local_to_utc_base_offset();
          case invalid_time_label: break;
          }
        }
        boost::throw_exception(std::out_of_range("Time label invalid"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_duration_type(not_a_date_time)); // should never reach
      }

      static time_type utc_to_local(const time_type& t)
      {
        time_duration_type td = dst_adjustor::utc_to_local_offset(t);
        return t + td;
      }

      static time_type local_to_utc(const time_type& t, 
                                    date_time::dst_flags dst=date_time::calculate)
      {
        time_duration_type td = dst_adjustor::local_to_utc_offset(t, dst);
        return t + td;
      }

      virtual ~dst_day_calc_rule() {}

      day_calc_dst_rule(start_rule dst_start,
                        end_rule dst_end) :
        dst_start_(dst_start),
        dst_end_(dst_end)
      {}

      virtual date_type start_day(year_type y) const
      {
        return dst_start_.get_date(y);
      }

      virtual std::string start_rule_as_string() const
      {
        return dst_start_.to_string();
      }

      virtual date_type end_day(year_type y) const
      {
        return dst_end_.get_date(y);
      }

      virtual std::string end_rule_as_string() const
      {
        return dst_end_.to_string();
      }

       static day_of_week_type start_day(year_type) {return Sunday;}

       static month_type start_month(year_type y) 
       {
         if (y < 2007) return Apr;
         return Mar;
       }

       static day_of_week_type end_day(year_type) {return Sunday;}

       static month_type end_month(year_type y) 
       {
         if (y < 2007) return Oct;
         return Nov;
       }

       static date_type local_dst_start_day(year_type year)
       {
         if (year < 2007) {
           start_rule_functor_pre2007 start1(start_day(year), 
                                             start_month(year));
           return start1.get_date(year);
         }
         start_rule_functor start(start_rule_functor::second,
                                  start_day(year), 
                                  start_month(year));
         return start.get_date(year);
          
       }

       static date_type local_dst_end_day(year_type year)
       {
         if (year < 2007) {
           end_rule_functor_pre2007 end_rule(end_day(year), 
                                             end_month(year));
           return end_rule.get_date(year);
         }
         end_rule_functor end(end_day(year), 
                              end_month(year));
         return end.get_date(year);      
       }

       static int dst_start_offset_minutes() { return 120;}

       static int dst_end_offset_minutes() { return 120; }

       static int dst_shift_length_minutes() { return 60; }

      static day_of_week_type start_day(year_type) {return Sunday;}

      static month_type start_month(year_type) {return Mar;}

      static day_of_week_type end_day(year_type) {return Sunday;}

      static month_type end_month(year_type) {return Oct;}

      static int dst_start_offset_minutes() { return 120;}

      static int dst_end_offset_minutes() { return 180; }

      static int dst_shift_length_minutes() { return 60; }

      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }

      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }

      static int dst_start_offset_minutes() { return 60;}

      static int dst_end_offset_minutes() { return 120; }

      static int dst_shift_length_minutes() { return 60; }

      static day_of_week_type start_day(year_type) {return Sunday;}

      static month_type start_month(year_type) {return Oct;}

      static day_of_week_type end_day(year_type) {return Sunday;}

      static month_type end_month(year_type) {return Mar;}

      static int dst_start_offset_minutes() { return 120;}

      static int dst_end_offset_minutes() { return 180; }

      static int dst_shift_length_minutes() { return 60; }

      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }

      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }

    static date_type local_day() 
    {
      return date_type(local_day_ymd());
    }

    static typename date_type::ymd_type local_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_local_time(result);
      return ymd_type(curr->tm_year + 1900, 
                      curr->tm_mon + 1, 
                      curr->tm_mday);
    }

    static typename date_type::ymd_type universal_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_universal_time(result);
      return ymd_type(curr->tm_year + 1900, 
                      curr->tm_mon + 1, 
                      curr->tm_mday);
    }

    static date_type universal_day() 
    {
      return date_type(universal_day_ymd());
    }

    static ::std::tm* get_local_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::localtime(&t, &result);
    }

    static ::std::tm* get_universal_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::gmtime(&t, &result);
    }

       data_not_accessible() : 
         std::logic_error(std::string("Unable to locate or access the required datafile.")) 
       {}

       bad_field_count(const std::string& s) : 
         std::out_of_range(s) 
      {}

      tz_db_base() {}

      void load_from_stream(std::istream &in)
      {
        std::string  buff;
        while( std::getline(in, buff)) {
          parse_string(buff);
        }
      }

      void load_from_file(const std::string& pathspec)
      {
        string_type in_str;
        std::string  buff;
        
        std::ifstream ifs(pathspec.c_str());
        if(!ifs){
          boost::throw_exception(data_not_accessible(pathspec));
        }
        std::getline(ifs, buff); // first line is column headings
        this->load_from_stream(ifs);
      }

      bool add_record(const string_type& region, 
                      boost::shared_ptr<time_zone_base_type> tz)
      {
        typename map_type::value_type p(region, tz); 
        return (m_zone_map.insert(p)).second;
      }

      rule_type* parse_rules(const string_type& sr, const string_type& er) const
      {
        using namespace gregorian;
        // start and end rule are of the same type, 
        // both are included here for readability
        typedef typename rule_type::start_rule start_rule;
        typedef typename rule_type::end_rule end_rule;
       
        // these are: [start|end] nth, day, month
        int s_nth = 0, s_d = 0, s_m = 0;
        int e_nth = 0, e_d = 0, e_m = 0;
        split_rule_spec(s_nth, s_d, s_m, sr);
        split_rule_spec(e_nth, e_d, e_m, er);
        
        typename start_rule::week_num s_wn, e_wn;
        s_wn = get_week_num(s_nth);
        e_wn = get_week_num(e_nth);
        
        
        return new rule_type(start_rule(s_wn, s_d, s_m),
                             end_rule(e_wn, e_d, e_m));
      }

      week_num get_week_num(int nth) const
      {
        typedef typename rule_type::start_rule start_rule;
        switch(nth){
        case 1:
          return start_rule::first;
        case 2:
          return start_rule::second;
        case 3:
          return start_rule::third;
        case 4:
          return start_rule::fourth;
        case 5:
        case -1:
          return start_rule::fifth;
        default:
          // shouldn't get here - add error handling later
          break;
        }
        return start_rule::fifth; // silence warnings
      }

      void split_rule_spec(int& nth, int& d, int& m, string_type rule) const
      {
        typedef boost::char_separator<char_type, std::char_traits<char_type> > char_separator_type;
        typedef boost::tokenizer<char_separator_type,
                                 std::basic_string<char_type>::const_iterator,
                                 std::basic_string<char_type> > tokenizer;
        typedef boost::tokenizer<char_separator_type,
                                 std::basic_string<char_type>::const_iterator,
                                 std::basic_string<char_type> >::iterator tokenizer_iterator;
        
        const char_type sep_char[] = { ';', '\0'};
        char_separator_type sep(sep_char);
        tokenizer tokens(rule, sep); // 3 fields

        if ( std::distance ( tokens.begin(), tokens.end ()) != 3 ) {
          std::ostringstream msg;
          msg << "Expecting 3 fields, got " 
              << std::distance ( tokens.begin(), tokens.end ()) 
              << " fields in line: " << rule;
          boost::throw_exception(bad_field_count(msg.str()));
        }

        tokenizer_iterator tok_iter = tokens.begin(); 
        nth = std::atoi(tok_iter->c_str()); ++tok_iter;
        d   = std::atoi(tok_iter->c_str()); ++tok_iter;
        m   = std::atoi(tok_iter->c_str());
      }

      bool parse_string(string_type& s)
      {
        std::vector<string_type> result;
        typedef boost::token_iterator_generator<boost::escaped_list_separator<char_type>, string_type::const_iterator, string_type >::type token_iter_type;

        token_iter_type i = boost::make_token_iterator<string_type>(s.begin(), s.end(),boost::escaped_list_separator<char_type>());

        token_iter_type end;
        while (i != end) {
          result.push_back(*i);
          i++;
        }

        enum db_fields { ID, STDABBR, STDNAME, DSTABBR, DSTNAME, GMTOFFSET,
                         DSTADJUST, START_DATE_RULE, START_TIME, END_DATE_RULE,
                         END_TIME, FIELD_COUNT };

        //take a shot at fixing gcc 4.x error
        const unsigned int expected_fields = static_cast<unsigned int>(FIELD_COUNT);
        if (result.size() != expected_fields) { 
          std::ostringstream msg;
          msg << "Expecting " << FIELD_COUNT << " fields, got " 
            << result.size() << " fields in line: " << s;
          boost::throw_exception(bad_field_count(msg.str()));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return false); // should never reach
        }

        // initializations
        bool has_dst = true; 
        if(result[DSTABBR] == std::string()){
          has_dst = false;
        }


        // start building components of a time_zone
        time_zone_names names(result[STDNAME], result[STDABBR],
                              result[DSTNAME], result[DSTABBR]);

        time_duration_type utc_offset = 
          str_from_delimited_time_duration<time_duration_type,char_type>(result[GMTOFFSET]);
        
        dst_adjustment_offsets adjust(time_duration_type(0,0,0),
                                      time_duration_type(0,0,0),
                                      time_duration_type(0,0,0));

        boost::shared_ptr<rule_type> rules;

        if(has_dst){
          adjust = dst_adjustment_offsets(
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[DSTADJUST]),
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[START_TIME]),
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[END_TIME])
                                          );

          rules = 
            boost::shared_ptr<rule_type>(parse_rules(result[START_DATE_RULE],
                                                     result[END_DATE_RULE]));
        }
        string_type id(result[ID]);
        boost::shared_ptr<time_zone_base_type> zone(new time_zone_type(names, utc_offset, adjust, rules));
        return (add_record(id, zone));
        
      }

    time_zone_names_base() :
      std_zone_name_(default_zone_names<CharT>::standard_name),
      std_zone_abbrev_(default_zone_names<CharT>::standard_abbrev),
      dst_zone_name_(default_zone_names<CharT>::non_dst_identifier),
      dst_zone_abbrev_(default_zone_names<CharT>::non_dst_identifier)
    {}

    string_type dst_zone_abbrev() const
    {
      return dst_zone_abbrev_;
    }

    string_type std_zone_abbrev() const
    {
      return std_zone_abbrev_;
    }

    string_type dst_zone_name() const
    {
      return dst_zone_name_;
    }

    string_type std_zone_name() const
    {
      return std_zone_name_;
    }


    time_duration() : ticks_(0) {}

    time_duration(hour_type hours_in,
                  min_type minutes_in,
                  sec_type seconds_in=0,
                  fractional_seconds_type frac_sec_in = 0) :
      ticks_(rep_type::to_tick_count(hours_in,minutes_in,seconds_in,frac_sec_in))
    {}

    time_duration(const time_duration<T, rep_type>& other)
      : ticks_(other.ticks_)
    {}

    static duration_type unit()
    {
      return duration_type(0,0,0,1);
    }

    static tick_type ticks_per_second()
    {
      return rep_type::res_adjust();
    }

    static time_resolutions resolution()
    {
      return rep_type::resolution();
    }

    hour_type hours()   const
    {
      return static_cast<hour_type>(ticks() / (3600*ticks_per_second()));
    }

    min_type minutes() const
    {
      return static_cast<min_type>((ticks() / (60*ticks_per_second())) % 60);
    }

    sec_type seconds() const
    {
      return static_cast<sec_type>((ticks()/ticks_per_second()) % 60);
    }

    sec_type total_seconds() const
    {
      return static_cast<sec_type>(ticks() / ticks_per_second());
    }

    tick_type total_milliseconds() const
    {
      if (ticks_per_second() < 1000) {
        return ticks() * (static_cast<tick_type>(1000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000)) ;
    }

    tick_type total_nanoseconds() const
    {
      if (ticks_per_second() < 1000000000) {
        return ticks() * (static_cast<tick_type>(1000000000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000000000)) ;
    }

    tick_type total_microseconds() const
    {
      if (ticks_per_second() < 1000000) {
        return ticks() * (static_cast<tick_type>(1000000) / ticks_per_second());
      }
      return ticks() / (ticks_per_second() / static_cast<tick_type>(1000000)) ;
    }

    fractional_seconds_type fractional_seconds() const
    {
      return (ticks() % ticks_per_second());
    }

    static unsigned short num_fractional_digits()
    {
      return rep_type::num_fractional_digits();
    }

    duration_type invert_sign() const
    {
      return duration_type(ticks_ * (-1));
    }

    bool is_negative() const
    {
      return ticks_ < 0;
    }

    bool operator<(const time_duration& rhs)  const
    {
      return ticks_ <  rhs.ticks_;
    }

    bool operator==(const time_duration& rhs)  const
    {
      return ticks_ ==  rhs.ticks_;
    }

    duration_type operator-()const
    {
      return duration_type(ticks_ * (-1));
    }

    duration_type operator-(const duration_type& d) const
    {
      return duration_type(ticks_ - d.ticks_);
    }

    duration_type operator+(const duration_type& d) const
    {
      return duration_type(ticks_ + d.ticks_);
    }

    duration_type operator/(int divisor) const
    {
      return duration_type(ticks_ / divisor);
    }

    duration_type operator-=(const duration_type& d)
    {
      ticks_ = ticks_ - d.ticks_;
      return duration_type(ticks_);
    }

    duration_type operator+=(const duration_type& d)
    {
      ticks_ = ticks_ + d.ticks_;
      return duration_type(ticks_);
    }

    duration_type operator/=(int divisor)
    {
      ticks_ = ticks_ / divisor;
      return duration_type(ticks_);
    }

    duration_type operator*(int rhs) const
    {
      return duration_type(ticks_ * rhs);
    }

    duration_type operator*=(int divisor)
    {
      ticks_ = ticks_ * divisor;
      return duration_type(ticks_);
    }

    tick_type ticks() const
    {
      return traits_type::as_number(ticks_);
    }

    bool is_special()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_special();
      }
      else{
        return false;
      }
    }

    bool is_pos_infinity()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_pos_infinity();
      }
      else{
        return false;
      }
    }

    bool is_neg_infinity()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_neg_infinity();
      }
      else{
        return false;
      }
    }

    bool is_not_a_date_time()const
    {
      if(traits_type::is_adapted())
      {
        return ticks_.is_nan();
      }
      else{
        return false;
      }
    }

    impl_type get_rep()const
    {
      return ticks_;
    }

    explicit time_duration(impl_type in) : ticks_(in) {}

    explicit subsecond_duration(boost::int64_t ss) :
      base_duration(impl_type(traits_type::ticks_per_second >= frac_of_second ? ss * adjustment_ratio : ss / adjustment_ratio))
    {
    }


    static time_type local_time()
    {
      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::localtime(&t);
      curr_ptr = c_time::localtime(&t, &curr);
      return create_time(curr_ptr);
    }

    static time_type universal_time()
    {

      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::gmtime(&t);
      curr_ptr = c_time::gmtime(&t, &curr);
      return create_time(curr_ptr);
    }

    static time_type create_time(::std::tm* current)
    {
      date_type d(static_cast<unsigned short>(current->tm_year + 1900),
                  static_cast<unsigned short>(current->tm_mon + 1),
                  static_cast<unsigned short>(current->tm_mday));
      time_duration_type td(current->tm_hour,
                            current->tm_min,
                            current->tm_sec);
      return time_type(d,td);
    }

    
    counted_time_rep(const date_type& d, const time_duration_type& time_of_day) 
      : time_count_(1)
    {
      if(d.is_infinity() || d.is_not_a_date() || time_of_day.is_special()) {
        time_count_ = time_of_day.get_rep() + d.day_count();
        //std::cout << time_count_ << std::endl;
      }
      else {    
        time_count_ = (d.day_number() * frac_sec_per_day()) + time_of_day.ticks();
      }
    }

    explicit counted_time_rep(int_type count) :
      time_count_(count)
    {}

    explicit counted_time_rep(impl_type count) :
      time_count_(count)
    {}

    date_type date() const
    {
      if(time_count_.is_special()) {
        return date_type(time_count_.as_special());
      }
      else {
        typename calendar_type::date_int_type dc = day_count();
        //std::cout << "time_rep here:" << dc << std::endl;
        ymd_type ymd = calendar_type::from_day_number(dc);
        return date_type(ymd);
      }
    }

    unsigned long day_count() const
    {
      /* resolution_traits::as_number returns a boost::int64_t & 
       * frac_sec_per_day is also a boost::int64_t so, naturally, 
       * the division operation returns a boost::int64_t. 
       * The static_cast to an unsigned long is ok (results in no data loss) 
       * because frac_sec_per_day is either the number of 
       * microseconds per day, or the number of nanoseconds per day. 
       * Worst case scenario: resolution_traits::as_number returns the 
       * maximum value an int64_t can hold and frac_sec_per_day 
       * is microseconds per day (lowest possible value). 
       * The division operation will then return a value of 106751991 - 
       * easily fitting in an unsigned long. 
       */
      return static_cast<unsigned long>(resolution_traits::as_number(time_count_) / frac_sec_per_day());
    }

    int_type time_count() const
    {
      return resolution_traits::as_number(time_count_);
    }

    int_type tod() const
    {
      return resolution_traits::as_number(time_count_) % frac_sec_per_day();
    }

    static int_type frac_sec_per_day()
    {
      int_type seconds_per_day = 60*60*24;
      int_type fractional_sec_per_sec(resolution_traits::res_adjust());
      return seconds_per_day*fractional_sec_per_sec;
    }

    bool is_pos_infinity()const
    {
      return impl_type::is_pos_inf(time_count_.as_number());
    }

    bool is_neg_infinity()const
    {
      return impl_type::is_neg_inf(time_count_.as_number());
    }

    bool is_not_a_date_time()const
    {
      return impl_type::is_not_a_number(time_count_.as_number());
    }

    bool is_special()const
    {
      return time_count_.is_special();
    }

    impl_type get_rep()const
    {
      return time_count_;
    }



    template<class T> static void unused_var(const T&) {}


    static time_rep_type get_time_rep(const date_type& day,
                                      const time_duration_type& tod,
                                      date_time::dst_flags dst=not_dst)
    {
      unused_var(dst);
      return time_rep_type(day, tod);
    }


    static date_type get_date(const time_rep_type& val)
    {
      return val.date();
    }

    static time_duration_type get_time_of_day(const time_rep_type& val)
    {
      if(val.is_special()) {
        return time_duration_type(val.get_rep().as_special());
      }
      else{
        return time_duration_type(0,0,0,val.tod()); 
      }
    }

    static std::string zone_name(const time_rep_type&)
    {
      return "";
    }

    static bool is_equal(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return (lhs.time_count() == rhs.time_count());
    }

    static bool is_less(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return (lhs.time_count() < rhs.time_count());
    }

    static time_rep_type add_days(const time_rep_type& base,
                                  const date_duration_type& dd)
    {
      if(base.is_special() || dd.is_special()) {
        return(time_rep_type(base.get_rep() + dd.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() + (dd.days() * time_rep_type::frac_sec_per_day()));
      }
    }

    static time_rep_type subtract_days(const time_rep_type& base,
                                       const date_duration_type& dd)
    {
      if(base.is_special() || dd.is_special()) {
        return(time_rep_type(base.get_rep() - dd.get_rep()));
      }
      else{
        return time_rep_type(base.time_count() - (dd.days() * time_rep_type::frac_sec_per_day()));
      }
    }

    static time_rep_type subtract_time_duration(const time_rep_type& base,
                                                const time_duration_type& td)
    {
      if(base.is_special() || td.is_special()) {
        return(time_rep_type(base.get_rep() - td.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() - td.ticks());
      }
    }

    static time_rep_type add_time_duration(const time_rep_type& base,
                                           time_duration_type td)
    {
      if(base.is_special() || td.is_special()) {
        return(time_rep_type(base.get_rep() + td.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() + td.ticks());
      }
    }

    static time_duration_type subtract_times(const time_rep_type& lhs,
                                             const time_rep_type& rhs)
    {
      if(lhs.is_special() || rhs.is_special()) {
        return(time_duration_type(
          impl_type::to_special((lhs.get_rep() - rhs.get_rep()).as_number())));
      }
      else {
        fractional_seconds_type fs = lhs.time_count() - rhs.time_count();
        return time_duration_type(0,0,0,fs); 
      }
    }

    constrained_value(value_type value) : value_((min)())
    {
      assign(value);
    }

    constrained_value& operator=(value_type v)
    {
      assign(v); 
      return *this;
    }

    void assign(value_type value)
    {
      //adding 1 below gets rid of a compiler warning which occurs when the 
      //min_value is 0 and the type is unsigned....
      if (value+1 < (min)()+1) {
        value_policies::on_error(value_, value, min_violation);
        return;
      }
      if (value > (max)()) {
        value_policies::on_error(value_, value, max_violation);
        return;
      }
      value_ = value;
    }

  template <typename T>
  // JDG [7/6/02 made a template],
  // moved here from time_duration.hpp 2003-Sept-4.
  inline T absolute_value(T x)
  {
    return x < 0 ? -x : x;
  }

    static int_type as_number(impl_type i){ return i;}

    static bool is_adapted() { return false;}

    static int_type as_number(impl_type i){ return i.as_number();}

    static bool is_adapted() { return true;}

    static int_type as_number(impl_type i){ return i;}

    static bool is_adapted() { return false;}

    static int_type as_number(impl_type i){ return i.as_number();}

    static bool is_adapted() { return true;}

    static fractional_seconds_type as_number(impl_type i)
    {
      return frac_sec_type::as_number(i);
    }

    static bool is_adapted()
    {
      return frac_sec_type::is_adapted();
    }


    static time_resolutions resolution()
    {
      return res;
    }

    static unsigned short num_fractional_digits()
    {
      return frac_digits;
    }

    static fractional_seconds_type res_adjust()
    {
      return resolution_adjust;
    }

    static tick_type to_tick_count(hour_type hours,
                                   min_type  minutes,
                                   sec_type  seconds,
                                   fractional_seconds_type  fs)
    {
      if(hours < 0 || minutes < 0 || seconds < 0 || fs < 0)
      {
        hours = absolute_value(hours);
        minutes = absolute_value(minutes);
        seconds = absolute_value(seconds);
        fs = absolute_value(fs);
        return (((((fractional_seconds_type(hours)*3600)
                   + (fractional_seconds_type(minutes)*60)
                   + seconds)*res_adjust()) + fs) * -1);
      }

      return (((fractional_seconds_type(hours)*3600)
               + (fractional_seconds_type(minutes)*60)
               + seconds)*res_adjust()) + fs;
    }

      inline
      static std::tm* localtime(const std::time_t* t, std::tm* result)
      {
        result = std::localtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to local time"));
        return result;
      }

      inline
      static std::tm* gmtime(const std::time_t* t, std::tm* result)
      {
        result = std::gmtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to UTC time"));
        return result;
      }

    date_generator_parser()
    {
      element_strings(string_type(first_string),
                      string_type(second_string),
                      string_type(third_string),
                      string_type(fourth_string),
                      string_type(fifth_string),
                      string_type(last_string),
                      string_type(before_string),
                      string_type(after_string),
                      string_type(of_string));
    }

    void element_strings(const string_type& first_str,
                         const string_type& second_str,
                         const string_type& third_str,
                         const string_type& fourth_str,
                         const string_type& fifth_str,
                         const string_type& last_str,
                         const string_type& before_str,
                         const string_type& after_str,
                         const string_type& of_str)
    {
      collection_type phrases;
      phrases.push_back(first_str);
      phrases.push_back(second_str);
      phrases.push_back(third_str);
      phrases.push_back(fourth_str);
      phrases.push_back(fifth_str);
      phrases.push_back(last_str);
      phrases.push_back(before_str);
      phrases.push_back(after_str);
      phrases.push_back(of_str);
      m_element_strings = parse_tree_type(phrases, this->first); // enum first
    }

    template<class facet_type>
    partial_date_type
    get_partial_date_type(stream_itr_type& sitr,
                          stream_itr_type& stream_end,
                          std::ios_base& a_ios,
                          const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_type d(1);
      month_type m(1);
      facet.get(sitr, stream_end, a_ios, d);
      facet.get(sitr, stream_end, a_ios, m);

      return partial_date_type(d,m);
    }

    template<class facet_type>
    nth_kday_type
    get_nth_kday_type(stream_itr_type& sitr,
                      stream_itr_type& stream_end,
                      std::ios_base& a_ios,
                      const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
 
      typename nth_kday_type::week_num wn;
      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor

      match_results mr = m_element_strings.match(sitr, stream_end);
      switch(mr.current_match) {
        case first  : { wn = nth_kday_type::first; break; }
        case second : { wn = nth_kday_type::second; break; }
        case third  : { wn = nth_kday_type::third; break; }
        case fourth : { wn = nth_kday_type::fourth; break; }
        case fifth  : { wn = nth_kday_type::fifth; break; }
        default:
        {
          boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'"));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(wn = nth_kday_type::first);
        }
      }                                         // week num
      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, of);    // "of" element
      facet.get(sitr, stream_end, a_ios, m);    // month

      return nth_kday_type(wn, wd, m);
    }

    template<class facet_type>
    first_kday_type
    get_first_kday_type(stream_itr_type& sitr,
                        stream_itr_type& stream_end,
                        std::ios_base& a_ios,
                        const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor

      extract_element(sitr, stream_end, first); // "first" element
      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, of);    // "of" element
      facet.get(sitr, stream_end, a_ios, m);    // month


      return first_kday_type(wd, m);
    }

    template<class facet_type>
    last_kday_type
    get_last_kday_type(stream_itr_type& sitr,
                       stream_itr_type& stream_end,
                       std::ios_base& a_ios,
                       const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor
      month_type m(1);        // no default constructor
 
      extract_element(sitr, stream_end, last); // "last" element
      facet.get(sitr, stream_end, a_ios, wd);  // day_of_week
      extract_element(sitr, stream_end, of);   // "of" element
      facet.get(sitr, stream_end, a_ios, m);   // month


      return last_kday_type(wd, m);
    }

    template<class facet_type>
    kday_before_type
    get_kday_before_type(stream_itr_type& sitr,
                         stream_itr_type& stream_end,
                         std::ios_base& a_ios,
                         const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor

      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, before);// "before" element

      return kday_before_type(wd);
    }

    template<class facet_type>
    kday_after_type
    get_kday_after_type(stream_itr_type& sitr,
                        stream_itr_type& stream_end,
                        std::ios_base& a_ios,
                        const facet_type& facet) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

      day_of_week_type wd(0); // no default constructor

      facet.get(sitr, stream_end, a_ios, wd);   // day_of_week
      extract_element(sitr, stream_end, after); // "after" element

      return kday_after_type(wd);
    }

    void extract_element(stream_itr_type& sitr,
                         stream_itr_type& stream_end,
                         typename date_generator_parser::phrase_elements ele) const
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }
      match_results mr = m_element_strings.match(sitr, stream_end);
      if(mr.current_match != ele) {
        boost::throw_exception(std::ios_base::failure("Parse failed. No match found for '" + mr.cache + "'"));
      }
    }

    period_parser(period_range_option range_opt = AS_CLOSED_RANGE,
                  const char_type* const period_separator = default_period_separator,
                  const char_type* const period_start_delimeter = default_period_start_delimeter,
                  const char_type* const period_open_range_end_delimeter = default_period_open_range_end_delimeter,
                  const char_type* const period_closed_range_end_delimeter = default_period_closed_range_end_delimeter)
      : m_range_option(range_opt)
    {
      delimiters.push_back(string_type(period_separator));
      delimiters.push_back(string_type(period_start_delimeter));
      delimiters.push_back(string_type(period_open_range_end_delimeter));
      delimiters.push_back(string_type(period_closed_range_end_delimeter));
    }


    period_parser(const period_parser<date_type,CharT>& p_parser)
    {
      this->delimiters = p_parser.delimiters;
      this->m_range_option = p_parser.m_range_option;
    }


    period_range_option range_option() const
    {
      return m_range_option;
    }

    void range_option(period_range_option option)
    {
      m_range_option = option;
    }

    collection_type delimiter_strings() const
    {
      return delimiters;
    }

    template<class period_type, class duration_type, class facet_type>
    period_type get_period(stream_itr_type& sitr, 
                           stream_itr_type& stream_end,
                           std::ios_base& a_ios, 
                           const period_type& /* p */,
                           const duration_type& dur_unit,
                           const facet_type& facet) const 
    {
      // skip leading whitespace
      while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; } 

      typedef typename period_type::point_type point_type;
      point_type p1(not_a_date_time), p2(not_a_date_time);


      consume_delim(sitr, stream_end, delimiters[START]);       // start delim
      facet.get(sitr, stream_end, a_ios, p1);                   // first point
      consume_delim(sitr, stream_end, delimiters[SEPARATOR]);   // separator
      facet.get(sitr, stream_end, a_ios, p2);                   // second point

      // period construction parameters are always open range [begin, end)
      if (m_range_option == AS_CLOSED_RANGE) {
        consume_delim(sitr, stream_end, delimiters[CLOSED_END]);// end delim
        // add 1 duration unit to p2 to make range open
        p2 += dur_unit;
      }
      else {
        consume_delim(sitr, stream_end, delimiters[OPEN_END]);  // end delim
      }

      return period_type(p1, p2);
    }

    void consume_delim(stream_itr_type& sitr,
                       stream_itr_type& stream_end,
                       const string_type& delim) const
    {
      /* string_parse_tree will not parse a string of punctuation characters 
       * without knowing exactly how many characters to process
       * Ex [2000. Will not parse out the '[' string without knowing 
       * to process only one character. By using length of the delimiter 
       * string we can safely iterate past it. */
      string_type s;
      for(unsigned int i = 0; i < delim.length() && sitr != stream_end; ++i) {
        s += *sitr;
        ++sitr;
      }
      if(s != delim) {
        boost::throw_exception(std::ios_base::failure("Parse failed. Expected '"
          + convert_string_type<char_type,char>(delim) + "' but found '" + convert_string_type<char_type,char>(s) + "'"));
      }
    }

  static int_type wrap_value() {return wrap_val;}

  wrapping_int(int_type v) : value_(v) {}

  int_type as_int()   const   {return value_;}

  operator int_type() const   {return value_;}

  template< typename IntT >
  IntT add(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_val));
    IntT overflow = static_cast<IntT>(v / (wrap_val));
    value_ = static_cast<int_type>(value_ + remainder);
    return calculate_wrap(overflow);
  }

  template< typename IntT >
  IntT subtract(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_val));
    IntT underflow = static_cast<IntT>(-(v / (wrap_val)));
    value_ = static_cast<int_type>(value_ - remainder);
    return calculate_wrap(underflow) * -1;
  }


  template< typename IntT >
  IntT calculate_wrap(IntT wrap)
  {
    if ((value_) >= wrap_val)
    {
      ++wrap;
      value_ -= (wrap_val);
    }
    else if(value_ < 0)
    {
      --wrap;
      value_ += (wrap_val);
    }
    return wrap;
  }

  static int_type wrap_value() {return wrap_max;}

  static int_type min_value()  {return wrap_min;}

  wrapping_int2(int_type v) : value_(v) {
    if(value_ < wrap_min)
    {
      value_ = wrap_min;
    }
    if(value_ > wrap_max)
    {
      value_ = wrap_max;
    }
  }

  int_type as_int()   const   {return value_;}

  operator int_type() const {return value_;}

  template< typename IntT >
  IntT add(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_max - wrap_min + 1));
    IntT overflow = static_cast<IntT>(v / (wrap_max - wrap_min + 1));
    value_ = static_cast<int_type>(value_ + remainder);
    return calculate_wrap(overflow);
  }

  template< typename IntT >
  IntT subtract(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_max - wrap_min + 1));
    IntT underflow = static_cast<IntT>(-(v / (wrap_max - wrap_min + 1)));
    value_ = static_cast<int_type>(value_ - remainder);
    return calculate_wrap(underflow);
  }


  template< typename IntT >
  IntT calculate_wrap(IntT wrap)
  {
    if ((value_) > wrap_max)
    {
      ++wrap;
      value_ -= (wrap_max - wrap_min + 1);
    }
    else if((value_) < wrap_min)
    {
      --wrap;
      value_ += (wrap_max - wrap_min + 1);
    }
    return wrap;
  }

  
  format_date_parser(const string_type& format_str,
                     const input_collection_type& month_short_names,
                     const input_collection_type& month_long_names,
                     const input_collection_type& weekday_short_names,
                     const input_collection_type& weekday_long_names) :
    m_format(format_str),
    m_month_short_names(month_short_names, 1),
    m_month_long_names(month_long_names, 1),
    m_weekday_short_names(weekday_short_names),
    m_weekday_long_names(weekday_long_names)
  {}


  format_date_parser(const format_date_parser<date_type,charT>& fdp)
  {
    this->m_format = fdp.m_format;
    this->m_month_short_names = fdp.m_month_short_names;
    this->m_month_long_names = fdp.m_month_long_names;
    this->m_weekday_short_names = fdp.m_weekday_short_names;
    this->m_weekday_long_names = fdp.m_weekday_long_names;
  }

  
  string_type format() const
  {
    return m_format;
  }


  void short_month_names(const input_collection_type& month_names)
  {
    m_month_short_names = parse_tree_type(month_names, 1);
  }

  void long_month_names(const input_collection_type& month_names)
  {
    m_month_long_names = parse_tree_type(month_names, 1);
  }

  void short_weekday_names(const input_collection_type& weekday_names)
  {
    m_weekday_short_names = parse_tree_type(weekday_names);
  }

  void long_weekday_names(const input_collection_type& weekday_names)
  {
    m_weekday_long_names = parse_tree_type(weekday_names);
  }


  date_type
  parse_date(const string_type& value, 
             const string_type& format_str,
             const special_values_parser<date_type,charT>& sv_parser) const
  {
    stringstream_type ss(value);
    stream_itr_type sitr(ss);
    stream_itr_type stream_end;
    return parse_date(sitr, stream_end, format_str, sv_parser);
  }

  month_type
  parse_month(std::istreambuf_iterator<charT>& sitr, 
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_month(sitr, stream_end, format_str, mr);
  }

  day_type
  parse_var_day_of_month(std::istreambuf_iterator<charT>& sitr, 
                         std::istreambuf_iterator<charT>& stream_end) const
  {
    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; } 

    return day_type(var_string_to_int<short, charT>(sitr, stream_end, 2));
  }

  day_type
  parse_day_of_month(std::istreambuf_iterator<charT>& sitr, 
                     std::istreambuf_iterator<charT>& stream_end) const
  {
    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; } 

    //return day_type(var_string_to_int<short, charT>(sitr, stream_end, 2));
    match_results mr;
    return day_type(fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2));
  }


  day_of_week_type
  parse_weekday(std::istreambuf_iterator<charT>& sitr, 
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_weekday(sitr, stream_end, format_str, mr);
  }

  year_type
  parse_year(std::istreambuf_iterator<charT>& sitr, 
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_year(sitr, stream_end, format_str, mr);
  }

    date(year_type y, month_type m, day_type d)
      : days_(calendar::day_number(ymd_type(y, m, d)))
    {}

    date(const ymd_type& ymd)
      : days_(calendar::day_number(ymd))
    {}

    year_type        year() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.year;
    }

    month_type       month() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.month;
    }

    day_type         day() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.day;
    }

    day_of_week_type day_of_week() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return calendar::day_of_week(ymd);
    }

    ymd_type         year_month_day() const
    {
      return calendar::from_day_number(days_);
    }

    bool operator<(const date_type& rhs)  const
    {
      return days_ < rhs.days_;
    }

    bool operator==(const date_type& rhs) const
    {
      return days_ == rhs.days_;
    }

    bool is_special()const
    {
      return(is_not_a_date() || is_infinity());
    }

    bool is_not_a_date()  const
    {
      return traits_type::is_not_a_number(days_);
    }

    bool is_infinity()  const
    {
      return traits_type::is_inf(days_);
    }

    bool is_pos_infinity()  const
    {
      return traits_type::is_pos_inf(days_);
    }

    bool is_neg_infinity()  const
    {
      return traits_type::is_neg_inf(days_);
    }

    special_values as_special()  const
    {
      return traits_type::to_special(days_);
    }

    duration_type operator-(const date_type& d) const
    {
      if (!this->is_special() && !d.is_special())
      {
        // The duration underlying type may be wider than the date underlying type.
        // Thus we calculate the difference in terms of two durations from some common fixed base date.
        typedef typename duration_type::duration_rep_type duration_rep_type;
        return duration_type(static_cast< duration_rep_type >(days_) - static_cast< duration_rep_type >(d.days_));
      }
      else
      {
        // In this case the difference will be a special value, too
        date_rep_type val = date_rep_type(days_) - date_rep_type(d.days_);
        return duration_type(val.as_special());
      }
    }


    date_type operator-(const duration_type& dd) const
    {
      if(dd.is_special())
      {
        return date_type(date_rep_type(days_) - dd.get_rep());
      }
      return date_type(date_rep_type(days_) - dd.days());
    }

    date_type operator-=(const duration_type& dd)
    {
      *this = *this - dd;
      return date_type(days_);
    }

    date_rep_type day_count() const
    {
      return days_;
    }

    date_type operator+(const duration_type& dd) const
    {
      if(dd.is_special())
      {
        return date_type(date_rep_type(days_) + dd.get_rep());
      }
      return date_type(date_rep_type(days_) + dd.days());
    }

    date_type operator+=(const duration_type& dd)
    {
      *this = *this + dd;
      return date_type(days_);
    }

    explicit date(date_int_type days) : days_(days) {}

    explicit date(date_rep_type days) : days_(days.as_number()) {}

  static month_format_spec month_format()
  {
    return month_as_integer;
  }

  static const charT* not_a_date()
  {     
    return "not-a-date-time";
  }

  static const charT* pos_infinity()
  {
    return "+infinity";
  }

  static const charT* neg_infinity()
  {
    return "-infinity";
  }

  static charT year_sep_char()
  {
    return 'Y';
  }

  static charT month_sep_char()
  {
    return '-';
  }

  static charT day_sep_char()
  {
    return '-';
  }

  static charT hour_sep_char()
  {
    return ':';
  }

  static charT minute_sep_char()
  {
    return ':';
  }

  static charT second_sep_char()
  {
    return ':';
  }

  static charT period_start_char()
  {
    return 'P';
  }

  static charT time_start_char()
  {
    return 'T';
  }

  static charT week_start_char()
  {
    return 'W';
  }

  static charT period_sep_char()
  {
    return '/';
  }

  static charT time_sep_char()
  {
    return ':';
  }

  static charT fractional_time_sep_char()
  {
    return ',';
  }


  static bool is_component_sep(charT sep)
  {
    switch(sep) {
    case 'H':
    case 'M':
    case 'S':
    case 'W':
    case 'T':
    case 'Y':
    case 'D':return true;
    default:
      return false;
    }
  }


  static bool is_fractional_time_sep(charT sep)
  {
    switch(sep) {
    case ',':
    case '.': return true;
    default: return false;
    }
  }

  static bool is_timezone_sep(charT sep)
  {
    switch(sep) {
    case '+':
    case '-': return true;
    default: return false;
    }
  }

  static charT element_sep_char()
  {
    return '-';
  }

  static month_format_spec month_format()
  {
    return month_as_integer;
  }

  static const wchar_t* not_a_date()
  {      
    return L"not-a-date-time";
  }

  static const wchar_t* pos_infinity()
  {
    return L"+infinity";
  }

  static const wchar_t* neg_infinity()
  {
    return L"-infinity";
  }

  static wchar_t year_sep_char()
  {
    return 'Y';
  }

  static wchar_t month_sep_char()
  {
    return '-';
  }

  static wchar_t day_sep_char()
  {
    return '-';
  }

  static wchar_t hour_sep_char()
  {
    return ':';
  }

  static wchar_t minute_sep_char()
  {
    return ':';
  }

  static wchar_t second_sep_char()
  {
    return ':';
  }

  static wchar_t period_start_char()
  {
    return 'P';
  }

  static wchar_t time_start_char()
  {
    return 'T';
  }

  static wchar_t week_start_char()
  {
    return 'W';
  }

  static wchar_t period_sep_char()
  {
    return '/';
  }

  static wchar_t time_sep_char()
  {
    return ':';
  }

  static wchar_t fractional_time_sep_char()
  {
    return ',';
  }


  static bool is_component_sep(wchar_t sep)
  {
    switch(sep) {
    case 'H':
    case 'M':
    case 'S':
    case 'W':
    case 'T':
    case 'Y':
    case 'D':return true;
    default:
      return false;
    }
  }


  static bool is_fractional_time_sep(wchar_t sep)
  {
    switch(sep) {
    case ',':
    case '.': return true;
    default: return false;
    }
  }

  static bool is_timezone_sep(wchar_t sep)
  {
    switch(sep) {
    case '+':
    case '-': return true;
    default: return false;
    }
  }

  static wchar_t element_sep_char()
  {
    return '-';
  }

  static bool has_date_sep_chars()
  {
    return false;
  }

  static bool has_date_sep_chars()
  {
    return true;
  }


    custom_time_zone_base(const time_zone_names& zone_names,
                     const time_duration_type& utc_offset,
                     const dst_adjustment_offsets& dst_shift,
                     boost::shared_ptr<dst_calc_rule> calc_rule) :
      zone_names_(zone_names),
      base_utc_offset_(utc_offset),
      dst_offsets_(dst_shift),
      dst_calc_rules_(calc_rule)
    {}

    virtual ~custom_time_zone_base() {}

    virtual string_type dst_zone_abbrev() const
    {
      return zone_names_.dst_zone_abbrev();
    }

    virtual string_type std_zone_abbrev() const
    {
      return zone_names_.std_zone_abbrev();
    }

    virtual string_type dst_zone_name() const
    {
      return zone_names_.dst_zone_name();
    }

    virtual string_type std_zone_name() const
    {
      return zone_names_.std_zone_name();
    }

    virtual bool has_dst() const
    {
      return (bool) dst_calc_rules_; //if calc_rule is set the tz has dst
    }

    virtual posix_time::ptime dst_local_start_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->start_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_start_offset_);
    }

    virtual posix_time::ptime dst_local_end_time(gregorian::greg_year y) const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if (dst_calc_rules_) {
        d = dst_calc_rules_->end_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_end_offset_);
    }

    virtual time_duration_type base_utc_offset() const
    {
      return base_utc_offset_;
    }

    virtual time_duration_type dst_offset() const
    {
      return dst_offsets_.dst_adjust_;
    }

    virtual string_type to_posix_string() const
    {
      // std offset dst [offset],start[/time],end[/time] - w/o spaces
      stringstream_type ss;
      ss.fill('0');
      boost::shared_ptr<dst_calc_rule> no_rules;
      // std
      ss << std_zone_abbrev();
      // offset
      if(base_utc_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
        ss << '-' << std::setw(2) << base_utc_offset().invert_sign().hours();
      }
      else {
        ss << '+' << std::setw(2) << base_utc_offset().hours();
      }
      if(base_utc_offset().minutes() != 0 || base_utc_offset().seconds() != 0) {
        ss << ':' << std::setw(2) << base_utc_offset().minutes();
        if(base_utc_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << base_utc_offset().seconds();
        }
      }
      if(dst_calc_rules_ != no_rules) {
        // dst
        ss << dst_zone_abbrev();
        // dst offset
        if(dst_offset().is_negative()) {
          // inverting the sign guarantees we get two digits
          ss << '-' << std::setw(2) << dst_offset().invert_sign().hours();
        }
        else {
          ss << '+' << std::setw(2) << dst_offset().hours();
        }
        if(dst_offset().minutes() != 0 || dst_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offset().minutes();
          if(dst_offset().seconds() != 0) {
            ss << ':' << std::setw(2) << dst_offset().seconds();
          }
        }
        // start/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->start_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_start_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_start_offset_.minutes();
        if(dst_offsets_.dst_start_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_start_offset_.seconds();
        }
        // end/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->end_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_end_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_end_offset_.minutes();
        if(dst_offsets_.dst_end_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_end_offset_.seconds();
        }
      }

      return ss.str();
    }

  inline
  local_date_time 
  operator+(const local_date_time& t, const boost::gregorian::months& m)
  {
    return t + m.get_offset(t.utc_time().date());
  }

  inline
  local_date_time 
  operator+=(local_date_time& t, const boost::gregorian::months& m)
  {
    return t += m.get_offset(t.utc_time().date());
  }

  inline
  local_date_time 
  operator-(const local_date_time& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + m.get_neg_offset(t.utc_time().date());
  }

  inline
  local_date_time 
  operator-=(local_date_time& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += m.get_neg_offset(t.utc_time().date());
  }

    ambiguous_result (std::string const& msg = std::string()) :
      std::logic_error(std::string("Daylight Savings Results are ambiguous: " + msg)) {}

    time_label_invalid (std::string const& msg = std::string()) :
      std::logic_error(std::string("Time label given is invalid: " + msg)) {}

    dst_not_valid(std::string const& msg = std::string()) :
      std::logic_error(std::string("is_dst flag does not match resulting dst for time label given: " + msg)) {}

inline
std::tm to_tm(const local_date_time& lt) {
  std::tm lt_tm = posix_time::to_tm(lt.local_time());
  if(lt.is_dst()){
    lt_tm.tm_isdst = 1;
  }
  else{
    lt_tm.tm_isdst = 0;
  }
  return lt_tm;
}

    bad_offset(std::string const& msg = std::string()) :
      std::out_of_range(std::string("Offset out of range: " + msg)) {}

    bad_adjustment(std::string const& msg = std::string()) :
      std::out_of_range(std::string("Adjustment out of range: " + msg)) {}

    posix_time_zone_base(const string_type& s) :
      //zone_names_("std_name","std_abbrev","no-dst","no-dst"),
      zone_names_(),
      has_dst_(false),
      base_utc_offset_(posix_time::hours(0)),
      dst_offsets_(posix_time::hours(0),posix_time::hours(0),posix_time::hours(0)),
      dst_calc_rules_()
    {
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[2] = {',',0};
#else
      const char_type sep_chars[2] = {','};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type tokens(s, sep);
      tokenizer_iterator_type it = tokens.begin(), end = tokens.end();
      if (it == end)
        BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse time zone name"));
      calc_zone(*it++);
      if(has_dst_)
      {
        if (it == end)
          BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse DST begin time"));
        string_type dst_begin = *it++;

        if (it == end)
          BOOST_THROW_EXCEPTION(std::invalid_argument("Could not parse DST end time"));
        string_type dst_end = *it;
        calc_rules(dst_begin, dst_end);
      }
    }

    virtual ~posix_time_zone_base() {}

    virtual string_type std_zone_abbrev()const
    {
      return zone_names_.std_zone_abbrev();
    }

    virtual string_type dst_zone_abbrev() const
    {
      return zone_names_.dst_zone_abbrev();
    }

    virtual string_type std_zone_name()const
    {
      return zone_names_.std_zone_name();
    }

    virtual string_type dst_zone_name()const
    {
      return zone_names_.dst_zone_name();
    }

    virtual bool has_dst()const
    {
      return has_dst_;
    }

    virtual posix_time::ptime dst_local_start_time(gregorian::greg_year y)const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if(has_dst_)
      {
        d = dst_calc_rules_->start_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_start_offset_);
    }

    virtual posix_time::ptime dst_local_end_time(gregorian::greg_year y)const
    {
      gregorian::date d(gregorian::not_a_date_time);
      if(has_dst_)
      {
        d = dst_calc_rules_->end_day(y);
      }
      return posix_time::ptime(d, dst_offsets_.dst_end_offset_);
    }

    virtual time_duration_type base_utc_offset()const
    {
      return base_utc_offset_;
    }

    virtual time_duration_type dst_offset()const
    {
      return dst_offsets_.dst_adjust_;
    }

    virtual string_type to_posix_string() const
    {
      // std offset dst [offset],start[/time],end[/time] - w/o spaces
      stringstream_type ss;
      ss.fill('0');
      boost::shared_ptr<dst_calc_rule> no_rules;
      // std
      ss << std_zone_abbrev();
      // offset
      if(base_utc_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
        ss << '-' << std::setw(2) << base_utc_offset().invert_sign().hours();
      }
      else {
        ss << '+' << std::setw(2) << base_utc_offset().hours();
      }
      if(base_utc_offset().minutes() != 0 || base_utc_offset().seconds() != 0) {
        ss << ':' << std::setw(2) << base_utc_offset().minutes();
        if(base_utc_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << base_utc_offset().seconds();
        }
      }
      if(dst_calc_rules_ != no_rules) {
        // dst
        ss << dst_zone_abbrev();
        // dst offset
        if(dst_offset().is_negative()) {
        // inverting the sign guarantees we get two digits
          ss << '-' << std::setw(2) << dst_offset().invert_sign().hours();
        }
        else {
          ss << '+' << std::setw(2) << dst_offset().hours();
        }
        if(dst_offset().minutes() != 0 || dst_offset().seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offset().minutes();
          if(dst_offset().seconds() != 0) {
            ss << ':' << std::setw(2) << dst_offset().seconds();
          }
        }
        // start/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->start_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_start_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_start_offset_.minutes();
        if(dst_offsets_.dst_start_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_start_offset_.seconds();
        }
        // end/time
        ss << ',' << date_time::convert_string_type<char, char_type>(dst_calc_rules_->end_rule_as_string()) << '/'
           << std::setw(2) << dst_offsets_.dst_end_offset_.hours() << ':'
           << std::setw(2) << dst_offsets_.dst_end_offset_.minutes();
        if(dst_offsets_.dst_end_offset_.seconds() != 0) {
          ss << ':' << std::setw(2) << dst_offsets_.dst_end_offset_.seconds();
        }
      }

      return ss.str();
    }

    void calc_zone(const string_type& obj){
      const char_type empty_string[2] = {'\0'};
      stringstream_type ss(empty_string);
      typename string_type::const_pointer sit = obj.c_str(), obj_end = sit + obj.size();
      string_type l_std_zone_abbrev, l_dst_zone_abbrev;

      // get 'std' name/abbrev
      while(std::isalpha(*sit)){
        ss << *sit++;
      }
      l_std_zone_abbrev = ss.str();
      ss.str(empty_string);

      // get UTC offset
      if(sit != obj_end){
        // get duration
        while(sit != obj_end && !std::isalpha(*sit)){
          ss << *sit++;
        }
        base_utc_offset_ = date_time::str_from_delimited_time_duration<time_duration_type,char_type>(ss.str());
        ss.str(empty_string);

        // base offset must be within range of -12 hours to +14 hours
        if(base_utc_offset_ < time_duration_type(-12,0,0) ||
          base_utc_offset_ > time_duration_type(14,0,0))
        {
          boost::throw_exception(bad_offset(posix_time::to_simple_string(base_utc_offset_)));
        }
      }

      // get DST data if given
      if(sit != obj_end){
        has_dst_ = true;

        // get 'dst' name/abbrev
        while(sit != obj_end && std::isalpha(*sit)){
          ss << *sit++;
        }
        l_dst_zone_abbrev = ss.str();
        ss.str(empty_string);

        // get DST offset if given
        if(sit != obj_end){
          // get duration
          while(sit != obj_end && !std::isalpha(*sit)){
            ss << *sit++;
          }
          dst_offsets_.dst_adjust_ = date_time::str_from_delimited_time_duration<time_duration_type,char_type>(ss.str());
          ss.str(empty_string);
        }
        else{ // default DST offset
          dst_offsets_.dst_adjust_ = posix_time::hours(1);
        }

        // adjustment must be within +|- 1 day
        if(dst_offsets_.dst_adjust_ <= time_duration_type(-24,0,0) ||
            dst_offsets_.dst_adjust_ >= time_duration_type(24,0,0))
        {
          boost::throw_exception(bad_adjustment(posix_time::to_simple_string(dst_offsets_.dst_adjust_)));
        }
      }
      // full names not extracted so abbrevs used in their place
      zone_names_ = time_zone_names(l_std_zone_abbrev, l_std_zone_abbrev, l_dst_zone_abbrev, l_dst_zone_abbrev);
    }


    void calc_rules(const string_type& start, const string_type& end){
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[2] = {'/',0};
#else
      const char_type sep_chars[2] = {'/'};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type st_tok(start, sep);
      tokenizer_type et_tok(end, sep);
      tokenizer_iterator_type sit = st_tok.begin();
      tokenizer_iterator_type eit = et_tok.begin();

      // generate date spec
      char_type x = string_type(*sit).at(0);
      if(x == 'M'){
        M_func(*sit, *eit);
      }
      else if(x == 'J'){
        julian_no_leap(*sit, *eit);
      }
      else{
        julian_day(*sit, *eit);
      }

      ++sit;
      ++eit;
      // generate durations
      // starting offset
      if(sit != st_tok.end()){
        dst_offsets_.dst_start_offset_ =  date_time::str_from_delimited_time_duration<time_duration_type,char_type>(*sit);
      }
      else{
        // default
        dst_offsets_.dst_start_offset_ = posix_time::hours(2);
      }
      // start/end offsets must fall on given date
      if(dst_offsets_.dst_start_offset_ < time_duration_type(0,0,0) ||
          dst_offsets_.dst_start_offset_ >= time_duration_type(24,0,0))
      {
        boost::throw_exception(bad_offset(posix_time::to_simple_string(dst_offsets_.dst_start_offset_)));
      }

      // ending offset
      if(eit != et_tok.end()){
        dst_offsets_.dst_end_offset_ =  date_time::str_from_delimited_time_duration<time_duration_type,char_type>(*eit);
      }
      else{
        // default
        dst_offsets_.dst_end_offset_ = posix_time::hours(2);
      }
      // start/end offsets must fall on given date
      if(dst_offsets_.dst_end_offset_ < time_duration_type(0,0,0) ||
        dst_offsets_.dst_end_offset_ >= time_duration_type(24,0,0))
      {
        boost::throw_exception(bad_offset(posix_time::to_simple_string(dst_offsets_.dst_end_offset_)));
      }
    }

    void M_func(const string_type& s, const string_type& e){
      typedef gregorian::nth_kday_of_month nkday;
      unsigned short sm=0,sw=0,sd=0,em=0,ew=0,ed=0; // start/end month,week,day
#ifdef __HP_aCC
      // Work around bug in aC++ compiler: see QXCR1000880488 in the
      // HP bug tracking system
      const char_type sep_chars[3] = {'M','.',0};
#else
      const char_type sep_chars[3] = {'M','.'};
#endif
      char_separator_type sep(sep_chars);
      tokenizer_type stok(s, sep), etok(e, sep);

      tokenizer_iterator_type it = stok.begin();
      sm = lexical_cast<unsigned short>(*it++);
      sw = lexical_cast<unsigned short>(*it++);
      sd = lexical_cast<unsigned short>(*it);

      it = etok.begin();
      em = lexical_cast<unsigned short>(*it++);
      ew = lexical_cast<unsigned short>(*it++);
      ed = lexical_cast<unsigned short>(*it);

      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new nth_kday_dst_rule(
          nth_last_dst_rule::start_rule(
            static_cast<nkday::week_num>(sw),sd,sm),
          nth_last_dst_rule::start_rule(
            static_cast<nkday::week_num>(ew),ed,em)
          )
      );
    }

    void julian_no_leap(const string_type& s, const string_type& e){
      typedef gregorian::gregorian_calendar calendar;
      const unsigned short year = 2001; // Non-leap year
      unsigned short sm=1;
      int sd=0;
      sd = lexical_cast<int>(s.substr(1)); // skip 'J'
      while(sd >= calendar::end_of_month_day(year,sm)){
        sd -= calendar::end_of_month_day(year,sm++);
      }
      unsigned short em=1;
      int ed=0;
      ed = lexical_cast<int>(e.substr(1)); // skip 'J'
      while(ed > calendar::end_of_month_day(year,em)){
        ed -= calendar::end_of_month_day(year,em++);
      }

      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new partial_date_dst_rule(
          partial_date_dst_rule::start_rule(
            sd, static_cast<date_time::months_of_year>(sm)),
          partial_date_dst_rule::end_rule(
            ed, static_cast<date_time::months_of_year>(em))
          )
      );
    }

    void julian_day(const string_type& s, const string_type& e){
      int sd=0, ed=0;
      sd = lexical_cast<int>(s);
      ed = lexical_cast<int>(e);
      dst_calc_rules_ = shared_ptr<dst_calc_rule>(
        new partial_date_dst_rule(
          partial_date_dst_rule::start_rule(++sd),// args are 0-365
          partial_date_dst_rule::end_rule(++ed) // pd expects 1-366
          )
      );
    }

    static std::string td_as_string(const time_duration_type& td)
    {
      std::string s;
#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
      s = posix_time::to_simple_string(td);
#else
      std::stringstream ss;
      ss << td;
      s = ss.str();
#endif
      return s;
    }

  inline
  ptime 
  operator+(const ptime& t, const boost::gregorian::months& m)
  {
    return t + m.get_offset(t.date());
  }

  inline
  ptime 
  operator+=(ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += m.get_offset(t.date());
  }

  inline
  ptime 
  operator-(const ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + m.get_neg_offset(t.date());
  }

  inline
  ptime 
  operator-=(ptime& t, const boost::gregorian::months& m)
  {
    return t += m.get_neg_offset(t.date());
  }

  inline time_duration duration_from_string(const std::string& s) {
    return date_time::parse_delimited_time_duration<time_duration>(s);
  }


  inline ptime time_from_string(const std::string& s) {
    return date_time::parse_delimited_time<ptime>(s, ' ');
  }


  inline ptime from_iso_string(const std::string& s) {
    return date_time::parse_iso_time<ptime>(s, 'T');
  }

template<class Archive>
void save(Archive & ar, 
          const posix_time::time_duration& td, 
          unsigned int /*version*/)
{
  // serialize a bool so we know how to read this back in later
  bool is_special = td.is_special();
  ar & make_nvp("is_special", is_special);
  if(is_special) {
    std::string s = to_simple_string(td);
    ar & make_nvp("sv_time_duration", s);
  }
  else {
    posix_time::time_duration::hour_type h = td.hours();
    posix_time::time_duration::min_type m = td.minutes();
    posix_time::time_duration::sec_type s = td.seconds();
    posix_time::time_duration::fractional_seconds_type fs = td.fractional_seconds();
    ar & make_nvp("time_duration_hours", h);
    ar & make_nvp("time_duration_minutes", m);
    ar & make_nvp("time_duration_seconds", s);
    ar & make_nvp("time_duration_fractional_seconds", fs);
  }
}

template<class Archive>
void load(Archive & ar, 
          posix_time::time_duration & td, 
          unsigned int /*version*/)
{
  bool is_special = false;
  ar & make_nvp("is_special", is_special);
  if(is_special) {
    std::string s;
    ar & make_nvp("sv_time_duration", s);
    posix_time::special_values sv = gregorian::special_value_from_string(s);
    td = posix_time::time_duration(sv);
  }
  else {
    posix_time::time_duration::hour_type h(0);
    posix_time::time_duration::min_type m(0);
    posix_time::time_duration::sec_type s(0);
    posix_time::time_duration::fractional_seconds_type fs(0);
    ar & make_nvp("time_duration_hours", h);
    ar & make_nvp("time_duration_minutes", m);
    ar & make_nvp("time_duration_seconds", s);
    ar & make_nvp("time_duration_fractional_seconds", fs);
    td = posix_time::time_duration(h,m,s,fs);
  }
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                posix_time::ptime* pt, 
                                const unsigned int /*file_version*/)
{
  // retrieve data from archive required to construct new 
  // invoke inplace constructor to initialize instance of date
  new(pt) boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

  inline std::string to_simple_string(time_duration td) {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special())
      {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  inline
  std::string
  to_iso_string(time_duration td)
  {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special()) {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  inline
  std::string
  to_iso_extended_string(ptime t)
  {
    std::string ts = gregorian::to_iso_extended_string(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      return ts + "T" + to_simple_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }

    explicit hours(long h) :
      time_duration(h,0,0)
    {}

    explicit minutes(long m) :
      time_duration(0,m,0)
    {}

    explicit seconds(long s) :
      time_duration(0,0,s)
    {}

  inline
  ptime from_time_t(std::time_t t)
  {
    ptime start(gregorian::date(1970,1,1));
    return start + seconds(static_cast<long>(t));
  }

  inline
  std::tm to_tm(const boost::posix_time::ptime& t) {
    std::tm timetm = boost::gregorian::to_tm(t.date());
    boost::posix_time::time_duration td = t.time_of_day();
    timetm.tm_hour = td.hours();
    timetm.tm_min = td.minutes();
    timetm.tm_sec = td.seconds();
    timetm.tm_isdst = -1; // -1 used when dst info is unknown
    return timetm;
  }

  inline
  ptime ptime_from_tm(const std::tm& timetm) {
    boost::gregorian::date d = boost::gregorian::date_from_tm(timetm);
    return ptime(d, time_duration(timetm.tm_hour, timetm.tm_min, timetm.tm_sec));
  }

    ptime(gregorian::date d,time_duration_type td) : date_time::base_time<time_type,time_system_type>(d,td)
    {}

    ptime(const time_rep_type& rhs):
      date_time::base_time<time_type,time_system_type>(rhs)
    {}

    ptime() : date_time::base_time<time_type,time_system_type>(gregorian::date(not_a_date_time), time_duration_type(not_a_date_time))
    {}

    time_duration(hour_type hour,
                  min_type min,
                  sec_type sec,
                  fractional_seconds_type fs=0) :
      date_time::time_duration<time_duration, time_res_traits>(hour,min,sec,fs)
    {}

    time_duration() :
      date_time::time_duration<time_duration, time_res_traits>(0,0,0)
    {}

    explicit time_duration(impl_type tick_count) :
      date_time::time_duration<time_duration, time_res_traits>(tick_count)
    {}

    bad_month() : std::out_of_range(std::string("Month number is out of range 1..12")) {}

  inline std::string to_simple_string(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d);
  }

  inline std::string to_iso_string(const date_period& d) {
    std::string s(date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.begin()));
    return s + "/" + date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.last());
  }

  inline std::string to_iso_extended_string(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<char> >::date_to_string(d);
  }

  
  

  inline std::string to_sql_string(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::ostringstream ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.day;
    return ss.str();
  }

    bad_day_of_year() : 
      std::out_of_range(std::string("Day of year value is out of range 1..366")) 
    {}

    bad_weekday() : std::out_of_range(std::string("Weekday is out of range 0..6")) {}

  inline
  std::tm to_tm(const date& d)
  {
    if (d.is_special())
    {
        std::string s = "tm unable to handle ";
        switch (d.as_special())
        {
        case date_time::not_a_date_time:
            s += "not-a-date-time value"; break;
        case date_time::neg_infin:
            s += "-infinity date value"; break;
        case date_time::pos_infin:
            s += "+infinity date value"; break;
        default:
            s += "a special date value"; break;
        }
        boost::throw_exception(std::out_of_range(s));
    }

    std::tm datetm;
    std::memset(&datetm, 0, sizeof(datetm));
    boost::gregorian::date::ymd_type ymd = d.year_month_day();
    datetm.tm_year = ymd.year - 1900;
    datetm.tm_mon = ymd.month - 1;
    datetm.tm_mday = ymd.day;
    datetm.tm_wday = d.day_of_week();
    datetm.tm_yday = d.day_of_year() - 1;
    datetm.tm_isdst = -1; // negative because not enough info to set tm_isdst
    return datetm;
  }

  inline
  date date_from_tm(const std::tm& datetm)
  {
    return date(static_cast<unsigned short>(datetm.tm_year+1900),
                static_cast<unsigned short>(datetm.tm_mon+1),
                static_cast<unsigned short>(datetm.tm_mday));
  }

    explicit date_duration(duration_rep day_count = 0) : base_type(day_count) {}

    date_duration(const date_duration& other) : base_type(static_cast< base_type const& >(other))
    {}

    bool operator== (const date_duration& rhs) const
    {
      return base_type::operator== (rhs);
    }

    bool operator!= (const date_duration& rhs) const
    {
      return !operator== (rhs);
    }

    bool operator< (const date_duration& rhs) const
    {
      return base_type::operator< (rhs);
    }

    bool operator> (const date_duration& rhs) const
    {
      return !(base_type::operator< (rhs) || base_type::operator== (rhs));
    }

    bool operator<= (const date_duration& rhs) const
    {
      return (base_type::operator< (rhs) || base_type::operator== (rhs));
    }

    bool operator>= (const date_duration& rhs) const
    {
      return !base_type::operator< (rhs);
    }

    date_duration& operator-= (const date_duration& rhs)
    {
      base_type::operator-= (rhs);
      return *this;
    }

    date_duration& operator+= (const date_duration& rhs)
    {
      base_type::operator+= (rhs);
      return *this;
    }

    date_duration operator- ()const
    {
      return date_duration(get_rep() * (-1));
    }

    date_duration& operator/= (int divisor)
    {
      base_type::operator/= (divisor);
      return *this;
    }

    static date_duration unit()
    {
      return date_duration(base_type::unit().get_rep());
    }

    date():
      date_time::date<date, gregorian_calendar, date_duration>(date_rep_type::from_special(not_a_date_time))
    {}

    date(year_type y, month_type m, day_type d)
      : date_time::date<date, gregorian_calendar, date_duration>(y, m, d)
    {
      if (gregorian_calendar::end_of_month_day(y, m) < d) {
        boost::throw_exception(bad_day_of_month(std::string("Day of month is not valid for year")));
      }
    }

    explicit date(const ymd_type& ymd)
      : date_time::date<date, gregorian_calendar, date_duration>(ymd)
    {}

    explicit date(date_rep_type rhs):
      date_time::date<date,gregorian_calendar, date_duration>(rhs)
    {}

    date_int_type julian_day() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::julian_day_number(ymd);
    }

    day_of_year_type day_of_year() const
    {
      date start_of_year(year(), 1, 1);
      unsigned short doy = static_cast<unsigned short>((*this-start_of_year).days() + 1);
      return day_of_year_type(doy);
    }

    date_int_type modjulian_day() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::modjulian_day_number(ymd);
    }

    int week_number() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::week_number(ymd);
    }

    date_int_type day_number() const
    {
      return days_;
    }

    date end_of_month() const
    {
      ymd_type ymd = year_month_day();
      short eom_day =  gregorian_calendar::end_of_month_day(ymd.year, ymd.month);
      return date(ymd.year, ymd.month, eom_day);
    }

  inline date from_string(std::string s) {
    return date_time::parse_date<date>(s);
  }

  inline date from_simple_string(std::string s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_iso);
  }

  inline date from_us_string(std::string s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_us);
  }

  inline date from_uk_string(std::string s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_dmy);
  }

  inline date from_undelimited_string(std::string s) {
    return date_time::parse_undelimited_date<date>(s);
  }

  inline date date_from_iso_string(const std::string& s) {
    return date_time::parse_undelimited_date<date>(s);
  }

  template<class iterator_type>
  inline date from_stream(iterator_type beg, iterator_type end) {
    if(beg == end)
    {
      return date(not_a_date_time);
    }
    typedef typename std::iterator_traits<iterator_type>::value_type value_type;
    return  date_time::from_stream_type<date>(beg, end, value_type());
  }

  inline date_period date_period_from_string(const std::string& s){
    return date_time::from_simple_string_type<date,char>(s);
  }

  inline date_period date_period_from_wstring(const std::wstring& s){
    return date_time::from_simple_string_type<date,wchar_t>(s);
  }

template<class Archive>                         
inline void serialize(Archive & ar,                               
                      ::boost::gregorian::date & d,
                      const unsigned int file_version)
{
  split_free(ar, d, file_version);              
}

template<class Archive>
void save(Archive & ar, 
          const ::boost::gregorian::date & d, 
          unsigned int /* version */)
{
  std::string ds = to_iso_string(d);
  ar & make_nvp("date", ds);
}

template<class Archive>
void load(Archive & ar, 
          ::boost::gregorian::date & d, 
          unsigned int /*version*/)
{
  std::string ds;
  ar & make_nvp("date", ds);
  try{
    d = ::boost::gregorian::from_undelimited_string(ds);
  }catch(bad_lexical_cast&) {
    gregorian::special_values sv = gregorian::special_value_from_string(ds);
    if(sv == gregorian::not_special) {
      throw; // no match found, rethrow original exception
    }
    else {
      d = gregorian::date(sv);
    }
  }
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                ::boost::gregorian::date* dp, 
                                const unsigned int /*file_version*/)
{
  // retrieve data from archive required to construct new 
  // invoke inplace constructor to initialize instance of date
  ::new(dp) ::boost::gregorian::date(::boost::gregorian::not_a_date_time);
}

    bad_year() : 
      std::out_of_range(std::string("Year is out of valid range: 1400..10000")) 
    {}

    greg_year(unsigned short year) : greg_year_rep(year) {}

    operator unsigned short()  const {return value_;}

    bad_day_of_month() : 
      std::out_of_range(std::string("Day of month value is out of range 1..31")) 
    {}

    greg_day(unsigned short day_of_month) : greg_day_rep(day_of_month) {}

    unsigned short as_number() const {return value_;}

    operator unsigned short()  const {return value_;}

    weeks_duration(duration_rep w) 
      : date_duration(w * 7) {}
