

template <class traits>
void raise_error(const traits& t, regex_constants::error_type code)
{
   (void)t;  // warning suppression
   std::runtime_error e(t.error_string(code));
   ::boost::re_detail::raise_runtime_error(e);
}

template <class InputIterator>
inline u32regex do_make_u32regex(InputIterator i, 
                              InputIterator j, 
                              boost::regex_constants::syntax_option_type opt, 
                              const boost::mpl::int_<1>*)
{
   typedef boost::u8_to_u32_iterator<InputIterator, UChar32> conv_type;
   return u32regex(conv_type(i, i, j), conv_type(j, i, j), opt);
}

template <class InputIterator>
inline u32regex make_u32regex(InputIterator i, 
                              InputIterator j, 
                              boost::regex_constants::syntax_option_type opt)
{
   return re_detail::do_make_u32regex(i, j, opt, static_cast<boost::mpl::int_<sizeof(*i)> const*>(0));
}

template<class MR1, class MR2>
void copy_results(MR1& out, MR2 const& in)
{
   // copy results from an adapted MR2 match_results:
   out.set_size(in.size(), in.prefix().first.base(), in.suffix().second.base());
   out.set_base(in.base().base());
   for(int i = 0; i < (int)in.size(); ++i)
   {
      if(in[i].matched)
      {
         out.set_first(in[i].first.base(), i);
         out.set_second(in[i].second.base(), i);
      }
   }
}


template <class BidiIterator, class Allocator>
inline bool do_regex_match(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const u32regex& e, 
                 match_flag_type flags,
                 boost::mpl::int_<4> const*)
{
   return ::boost::regex_match(first, last, m, e, flags);
}


template <class BidiIterator, class Allocator>
inline bool u32regex_match(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const u32regex& e, 
                 match_flag_type flags = match_default)
{
   return re_detail::do_regex_match(first, last, m, e, flags, static_cast<mpl::int_<sizeof(*first)> const*>(0));
}

template <class BidiIterator, class Allocator>
inline bool do_regex_search(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const u32regex& e, 
                 match_flag_type flags,
                 BidiIterator base,
                 boost::mpl::int_<4> const*)
{
   return ::boost::regex_search(first, last, m, e, flags, base);
}


template <class BidiIterator, class Allocator>
inline bool u32regex_search(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const u32regex& e, 
                 match_flag_type flags = match_default)
{
   return re_detail::do_regex_search(first, last, m, e, flags, first, static_cast<mpl::int_<sizeof(*first)> const*>(0));
}


template <class OutputIterator, class BidirectionalIterator, class charT>
inline OutputIterator u32regex_replace(OutputIterator out,
                         BidirectionalIterator first,
                         BidirectionalIterator last,
                         const u32regex& e, 
                         const charT* fmt, 
                         match_flag_type flags = match_default)
{
   return re_detail::extract_output_base
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
   <OutputIterator>
#endif
    (
      re_detail::do_regex_replace(
         re_detail::make_utf32_out(out, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
         re_detail::make_utf32_seq(first, last, static_cast<mpl::int_<sizeof(*first)> const*>(0)),
         e,
         re_detail::make_utf32_seq(fmt, static_cast<mpl::int_<sizeof(*fmt)> const*>(0)),
         flags)
      );
}

inline long hash_value(char_architype val)
{  return val;  }


   static std::size_t length(const char_type* ) { return 0; }


   charT translate(charT ) const { return charT(); }

   charT translate_nocase(charT ) const { return static_object<charT>::get(); }


   template <class ForwardIterator>
   string_type transform(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }

   template <class ForwardIterator>
   string_type transform_primary(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }


   template <class ForwardIterator>
   char_class_type lookup_classname(ForwardIterator , ForwardIterator ) const
   { return static_object<char_class_type>::get(); }

   template <class ForwardIterator>
   string_type lookup_collatename(ForwardIterator , ForwardIterator ) const
   { return static_object<string_type>::get(); }


   bool isctype(charT, char_class_type) const
   { return false; }

   int value(charT, int) const
   { return 0; }


   locale_type imbue(locale_type l)
   { return l; }

   locale_type getloc()const
   { return static_object<locale_type>::get(); }

   void constraints() 
   {
      function_requires<CopyConstructibleConcept<Bitmask> >();
      function_requires<AssignableConcept<Bitmask> >();

      m_mask1 = m_mask2 | m_mask3;
      m_mask1 = m_mask2 & m_mask3;
      m_mask1 = m_mask2 ^ m_mask3;

      m_mask1 = ~m_mask2;

      m_mask1 |= m_mask2;
      m_mask1 &= m_mask2;
      m_mask1 ^= m_mask2;
   }


   void constraints() 
   {
      //function_requires<UnsignedIntegerConcept<size_type> >();
      function_requires<RandomAccessContainerConcept<string_type> >();
      function_requires<DefaultConstructibleConcept<locale_type> >();
      function_requires<CopyConstructibleConcept<locale_type> >();
      function_requires<AssignableConcept<locale_type> >();
      function_requires<BitmaskConcept<char_class_type> >();

      std::size_t n = traits::length(m_pointer);
      ignore_unused_variable_warning(n);

      char_type c = m_ctraits.translate(m_char);
      ignore_unused_variable_warning(c);
      c = m_ctraits.translate_nocase(m_char);
      
      //string_type::foobar bar;
      string_type s1 = m_ctraits.transform(m_pointer, m_pointer);
      ignore_unused_variable_warning(s1);

      string_type s2 = m_ctraits.transform_primary(m_pointer, m_pointer);
      ignore_unused_variable_warning(s2);

      char_class_type cc = m_ctraits.lookup_classname(m_pointer, m_pointer);
      ignore_unused_variable_warning(cc);

      string_type s3 = m_ctraits.lookup_collatename(m_pointer, m_pointer);
      ignore_unused_variable_warning(s3);

      bool b = m_ctraits.isctype(m_char, cc);
      ignore_unused_variable_warning(b);

      int v = m_ctraits.value(m_char, 16);
      ignore_unused_variable_warning(v);

      locale_type l(m_ctraits.getloc());
      m_traits.imbue(l);
      ignore_unused_variable_warning(l);
   }


   void global_constraints()
   {
      //
      // test non-template components:
      //
      function_requires<BitmaskConcept<global_regex_namespace::regex_constants::syntax_option_type> >();
      global_regex_namespace::regex_constants::syntax_option_type opts
         = global_regex_namespace::regex_constants::icase
         | global_regex_namespace::regex_constants::nosubs
         | global_regex_namespace::regex_constants::optimize
         | global_regex_namespace::regex_constants::collate
         | global_regex_namespace::regex_constants::ECMAScript
         | global_regex_namespace::regex_constants::basic
         | global_regex_namespace::regex_constants::extended
         | global_regex_namespace::regex_constants::awk
         | global_regex_namespace::regex_constants::grep
         | global_regex_namespace::regex_constants::egrep;
      ignore_unused_variable_warning(opts);

      function_requires<BitmaskConcept<global_regex_namespace::regex_constants::match_flag_type> >();
      global_regex_namespace::regex_constants::match_flag_type mopts
         = global_regex_namespace::regex_constants::match_default
         | global_regex_namespace::regex_constants::match_not_bol
         | global_regex_namespace::regex_constants::match_not_eol
         | global_regex_namespace::regex_constants::match_not_bow
         | global_regex_namespace::regex_constants::match_not_eow
         | global_regex_namespace::regex_constants::match_any
         | global_regex_namespace::regex_constants::match_not_null
         | global_regex_namespace::regex_constants::match_continuous
         | global_regex_namespace::regex_constants::match_prev_avail
         | global_regex_namespace::regex_constants::format_default
         | global_regex_namespace::regex_constants::format_sed
         | global_regex_namespace::regex_constants::format_no_copy
         | global_regex_namespace::regex_constants::format_first_only;
      ignore_unused_variable_warning(mopts);

      BOOST_STATIC_ASSERT((::boost::is_enum<global_regex_namespace::regex_constants::error_type>::value));
      global_regex_namespace::regex_constants::error_type e1 = global_regex_namespace::regex_constants::error_collate;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_ctype;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_escape;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_backref;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_brack;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_paren;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_brace;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_badbrace;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_range;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_space;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_badrepeat;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_complexity;
      ignore_unused_variable_warning(e1);
      e1 = global_regex_namespace::regex_constants::error_stack;
      ignore_unused_variable_warning(e1);

      BOOST_STATIC_ASSERT((::boost::is_base_and_derived<std::runtime_error, global_regex_namespace::regex_error>::value  ));
      const global_regex_namespace::regex_error except(e1);
      e1 = except.code();

      typedef typename Regex::value_type regex_value_type;
      function_requires< RegexTraitsConcept<global_regex_namespace::regex_traits<char> > >();
      function_requires< BaseRegexConcept<global_regex_namespace::basic_regex<char> > >();
   }

   void constraints() 
   {
      global_constraints();

      BOOST_STATIC_ASSERT((::boost::is_same< flag_type, global_regex_namespace::regex_constants::syntax_option_type>::value));
      flag_type opts
         = Regex::icase
         | Regex::nosubs
         | Regex::optimize
         | Regex::collate
         | Regex::ECMAScript
         | Regex::basic
         | Regex::extended
         | Regex::awk
         | Regex::grep
         | Regex::egrep;
      ignore_unused_variable_warning(opts);

      function_requires<DefaultConstructibleConcept<Regex> >();
      function_requires<CopyConstructibleConcept<Regex> >();

      // Regex constructors:
      Regex e1(m_pointer);
      ignore_unused_variable_warning(e1);
      Regex e2(m_pointer, m_flags);
      ignore_unused_variable_warning(e2);
      Regex e3(m_pointer, m_size, m_flags);
      ignore_unused_variable_warning(e3);
      Regex e4(in1, in2);
      ignore_unused_variable_warning(e4);
      Regex e5(in1, in2, m_flags);
      ignore_unused_variable_warning(e5);

      // assign etc:
      Regex e;
      e = m_pointer;
      e = e1;
      e.assign(e1);
      e.assign(m_pointer);
      e.assign(m_pointer, m_flags);
      e.assign(m_pointer, m_size, m_flags);
      e.assign(in1, in2);
      e.assign(in1, in2, m_flags);

      // access:
      const Regex ce;
      typename Regex::size_type i = ce.mark_count();
      ignore_unused_variable_warning(i);
      m_flags = ce.flags();
      e.imbue(ce.getloc());
      e.swap(e1);
      
      global_regex_namespace::swap(e, e1);

      // sub_match:
      BOOST_STATIC_ASSERT((::boost::is_base_and_derived<std::pair<BidiIterator, BidiIterator>, sub_match_type>::value));
      typedef typename sub_match_type::value_type sub_value_type;
      typedef typename sub_match_type::difference_type sub_diff_type;
      typedef typename sub_match_type::iterator sub_iter_type;
      BOOST_STATIC_ASSERT((::boost::is_same<sub_value_type, value_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<sub_iter_type, BidiIterator>::value));
      bool b = m_sub.matched;
      ignore_unused_variable_warning(b);
      BidiIterator bi = m_sub.first;
      ignore_unused_variable_warning(bi);
      bi = m_sub.second;
      ignore_unused_variable_warning(bi);
      sub_diff_type diff = m_sub.length();
      ignore_unused_variable_warning(diff);
      // match_results tests:
      typedef typename match_results_type::value_type mr_value_type;
      typedef typename match_results_type::const_reference mr_const_reference;
      typedef typename match_results_type::reference mr_reference;
      typedef typename match_results_type::const_iterator mr_const_iterator;
      typedef typename match_results_type::iterator mr_iterator;
      typedef typename match_results_type::difference_type mr_difference_type;
      typedef typename match_results_type::size_type mr_size_type;
      typedef typename match_results_type::allocator_type mr_allocator_type;
      typedef typename match_results_type::char_type mr_char_type;
      typedef typename match_results_type::string_type mr_string_type;

      match_results_type m1;
      mr_allocator_type at;
      match_results_type m2(at);
      match_results_type m3(m1);
      m1 = m2;

      int ival = 0;

      mr_size_type mrs = m_cresults.size();
      ignore_unused_variable_warning(mrs);
      mrs = m_cresults.max_size();
      ignore_unused_variable_warning(mrs);
      b = m_cresults.empty();
      ignore_unused_variable_warning(b);
      mr_difference_type mrd = m_cresults.length();
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.length(ival);
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.position();
      ignore_unused_variable_warning(mrd);
      mrd = m_cresults.position(mrs);
      ignore_unused_variable_warning(mrd);

      mr_const_reference mrcr = m_cresults[ival];
      ignore_unused_variable_warning(mrcr);
      mr_const_reference mrcr2 = m_cresults.prefix();
      ignore_unused_variable_warning(mrcr2);
      mr_const_reference mrcr3 = m_cresults.suffix();
      ignore_unused_variable_warning(mrcr3);
      mr_const_iterator mrci = m_cresults.begin();
      ignore_unused_variable_warning(mrci);
      mrci = m_cresults.end();
      ignore_unused_variable_warning(mrci);

      mr_allocator_type at2 = m_cresults.get_allocator();
      m_results.swap(m_results);
      global_regex_namespace::swap(m_results, m_results);

      // regex_match:
      b = global_regex_namespace::regex_match(m_in, m_in, m_results, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, m_results, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, m_pmatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, m_pmatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_pointer, e, m_mft);
      ignore_unused_variable_warning(b);
      // regex_search:
      b = global_regex_namespace::regex_search(m_in, m_in, m_results, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, m_results, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, m_pmatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, m_pmatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_pointer, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_iterator:
      typedef typename regex_iterator_type::regex_type rit_regex_type;
      typedef typename regex_iterator_type::value_type rit_value_type;
      typedef typename regex_iterator_type::difference_type rit_difference_type;
      typedef typename regex_iterator_type::pointer rit_pointer;
      typedef typename regex_iterator_type::reference rit_reference;
      typedef typename regex_iterator_type::iterator_category rit_iterator_category;
      BOOST_STATIC_ASSERT((::boost::is_same<rit_regex_type, Regex>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_value_type, match_results_default_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_difference_type, std::ptrdiff_t>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_pointer, const match_results_default_type*>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rit_reference, const match_results_default_type&>::value));
      BOOST_STATIC_ASSERT((::boost::is_convertible<rit_iterator_category*, std::forward_iterator_tag*>::value));
      // this takes care of most of the checks needed:
      function_requires<ForwardIteratorConcept<regex_iterator_type> >();
      regex_iterator_type iter1(m_in, m_in, e);
      ignore_unused_variable_warning(iter1);
      regex_iterator_type iter2(m_in, m_in, e, m_mft);
      ignore_unused_variable_warning(iter2);

      // regex_token_iterator:
      typedef typename regex_token_iterator_type::regex_type rtit_regex_type;
      typedef typename regex_token_iterator_type::value_type rtit_value_type;
      typedef typename regex_token_iterator_type::difference_type rtit_difference_type;
      typedef typename regex_token_iterator_type::pointer rtit_pointer;
      typedef typename regex_token_iterator_type::reference rtit_reference;
      typedef typename regex_token_iterator_type::iterator_category rtit_iterator_category;
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_regex_type, Regex>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_value_type, sub_match_type>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_difference_type, std::ptrdiff_t>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_pointer, const sub_match_type*>::value));
      BOOST_STATIC_ASSERT((::boost::is_same<rtit_reference, const sub_match_type&>::value));
      BOOST_STATIC_ASSERT((::boost::is_convertible<rtit_iterator_category*, std::forward_iterator_tag*>::value));
      // this takes care of most of the checks needed:
      function_requires<ForwardIteratorConcept<regex_token_iterator_type> >();
      regex_token_iterator_type ti1(m_in, m_in, e);
      ignore_unused_variable_warning(ti1);
      regex_token_iterator_type ti2(m_in, m_in, e, 0);
      ignore_unused_variable_warning(ti2);
      regex_token_iterator_type ti3(m_in, m_in, e, 0, m_mft);
      ignore_unused_variable_warning(ti3);
      std::vector<int> subs;
      regex_token_iterator_type ti4(m_in, m_in, e, subs);
      ignore_unused_variable_warning(ti4);
      regex_token_iterator_type ti5(m_in, m_in, e, subs, m_mft);
      ignore_unused_variable_warning(ti5);
      static const int i_array[3] = { 1, 2, 3, };
      regex_token_iterator_type ti6(m_in, m_in, e, i_array);
      ignore_unused_variable_warning(ti6);
      regex_token_iterator_type ti7(m_in, m_in, e, i_array, m_mft);
      ignore_unused_variable_warning(ti7);
   }



   void constraints() 
   {
      function_requires<BaseRegexConcept<Regex> >();
      // string based construct:
      Regex e1(m_string);
      ignore_unused_variable_warning(e1);
      Regex e2(m_string, m_flags);
      ignore_unused_variable_warning(e2);

      // assign etc:
      Regex e;
      e = m_string;
      e.assign(m_string);
      e.assign(m_string, m_flags);

      // sub_match:
      string_type s(m_sub);
      ignore_unused_variable_warning(s);
      s = m_sub.str();
      ignore_unused_variable_warning(s);
      int i = m_sub.compare(m_string);
      ignore_unused_variable_warning(i);

      int i2 = m_sub.compare(m_sub);
      ignore_unused_variable_warning(i2);
      i2 = m_sub.compare(m_pointer);
      ignore_unused_variable_warning(i2);

      bool b = m_sub == m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub != m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub > m_sub;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub != m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub > m_pointer;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_pointer;
      ignore_unused_variable_warning(b);

      b = m_pointer == m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer != m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer > m_sub;
      ignore_unused_variable_warning(b);
      b = m_pointer >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_char;
      ignore_unused_variable_warning(b);
      b = m_sub != m_char;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_char;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_char;
      ignore_unused_variable_warning(b);
      b = m_sub > m_char;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_char;
      ignore_unused_variable_warning(b);

      b = m_char == m_sub;
      ignore_unused_variable_warning(b);
      b = m_char != m_sub;
      ignore_unused_variable_warning(b);
      b = m_char <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_char <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_char > m_sub;
      ignore_unused_variable_warning(b);
      b = m_char >= m_sub;
      ignore_unused_variable_warning(b);

      b = m_sub == m_string;
      ignore_unused_variable_warning(b);
      b = m_sub != m_string;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_string;
      ignore_unused_variable_warning(b);
      b = m_sub <= m_string;
      ignore_unused_variable_warning(b);
      b = m_sub > m_string;
      ignore_unused_variable_warning(b);
      b = m_sub >= m_string;
      ignore_unused_variable_warning(b);

      b = m_string == m_sub;
      ignore_unused_variable_warning(b);
      b = m_string != m_sub;
      ignore_unused_variable_warning(b);
      b = m_string <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_string <= m_sub;
      ignore_unused_variable_warning(b);
      b = m_string > m_sub;
      ignore_unused_variable_warning(b);
      b = m_string >= m_sub;
      ignore_unused_variable_warning(b);

      // match results:
      m_string = m_results.str();
      ignore_unused_variable_warning(m_string);
      m_string = m_results.str(0);
      ignore_unused_variable_warning(m_string);
      m_out = m_cresults.format(m_out, m_string);
      m_out = m_cresults.format(m_out, m_string, m_mft);
      m_string = m_cresults.format(m_string);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.format(m_string, m_mft);
      ignore_unused_variable_warning(m_string);

      // regex_match:
      b = global_regex_namespace::regex_match(m_string, m_smatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, m_smatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_match(m_string, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_search:
      b = global_regex_namespace::regex_search(m_string, m_smatch, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, m_smatch, e, m_mft);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, e);
      ignore_unused_variable_warning(b);
      b = global_regex_namespace::regex_search(m_string, e, m_mft);
      ignore_unused_variable_warning(b);

      // regex_replace:
      m_out = global_regex_namespace::regex_replace(m_out, m_in, m_in, e, m_string, m_mft);
      m_out = global_regex_namespace::regex_replace(m_out, m_in, m_in, e, m_string);
      m_string = global_regex_namespace::regex_replace(m_string, e, m_string, m_mft);
      ignore_unused_variable_warning(m_string);
      m_string = global_regex_namespace::regex_replace(m_string, e, m_string);
      ignore_unused_variable_warning(m_string);

   }

   const char_type* operator()(const M&)const
   {
      static const char_type c = static_cast<char_type>(0);
      return &c;
   }

   template <class O>
   O operator()(const M& /*m*/, O i)const
   {
      return i;
   }

   template <class O>
   O operator()(const M& /*m*/, O i, regex_constants::match_flag_type)const
   {
      return i;
   }


   void constraints() 
   {
      global_regex_namespace::regex_constants::match_flag_type mopts
         = global_regex_namespace::regex_constants::match_default
         | global_regex_namespace::regex_constants::match_not_bol
         | global_regex_namespace::regex_constants::match_not_eol
         | global_regex_namespace::regex_constants::match_not_bow
         | global_regex_namespace::regex_constants::match_not_eow
         | global_regex_namespace::regex_constants::match_any
         | global_regex_namespace::regex_constants::match_not_null
         | global_regex_namespace::regex_constants::match_continuous
         | global_regex_namespace::regex_constants::match_partial
         | global_regex_namespace::regex_constants::match_prev_avail
         | global_regex_namespace::regex_constants::format_default
         | global_regex_namespace::regex_constants::format_sed
         | global_regex_namespace::regex_constants::format_perl
         | global_regex_namespace::regex_constants::format_no_copy
         | global_regex_namespace::regex_constants::format_first_only;

      (void)mopts;

      function_requires<RegexConcept<Regex> >();
      const global_regex_namespace::regex_error except(global_regex_namespace::regex_constants::error_collate);
      std::ptrdiff_t pt = except.position();
      ignore_unused_variable_warning(pt);
      const Regex ce, ce2;
#ifndef BOOST_NO_STD_LOCALE
      m_stream << ce;
#endif
      unsigned i = ce.error_code();
      ignore_unused_variable_warning(i);
      pointer_type p = ce.expression();
      ignore_unused_variable_warning(p);
      int i2 = ce.compare(ce2);
      ignore_unused_variable_warning(i2);
      bool b = ce == ce2;
      ignore_unused_variable_warning(b);
      b = ce.empty();
      ignore_unused_variable_warning(b);
      b = ce != ce2;
      ignore_unused_variable_warning(b);
      b = ce < ce2;
      ignore_unused_variable_warning(b);
      b = ce > ce2;
      ignore_unused_variable_warning(b);
      b = ce <= ce2;
      ignore_unused_variable_warning(b);
      b = ce >= ce2;
      ignore_unused_variable_warning(b);
      i = ce.status();
      ignore_unused_variable_warning(i);
      size_type s = ce.max_size();
      ignore_unused_variable_warning(s);
      s = ce.size();
      ignore_unused_variable_warning(s);
      const_iterator pi = ce.begin();
      ignore_unused_variable_warning(pi);
      pi = ce.end();
      ignore_unused_variable_warning(pi);
      string_type s2 = ce.str();
      ignore_unused_variable_warning(s2);

      m_string = m_sub + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_pointer;
      ignore_unused_variable_warning(m_string);
      m_string = m_pointer + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_string;
      ignore_unused_variable_warning(m_string);
      m_string = m_string + m_sub;
      ignore_unused_variable_warning(m_string);
      m_string = m_sub + m_char;
      ignore_unused_variable_warning(m_string);
      m_string = m_char + m_sub;
      ignore_unused_variable_warning(m_string);

      // Named sub-expressions:
      m_sub = m_cresults[&m_char];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[m_string];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[""];
      ignore_unused_variable_warning(m_sub);
      m_sub = m_cresults[std::string("")];
      ignore_unused_variable_warning(m_sub);
      m_string = m_cresults.str(&m_char);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str(m_string);
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str("");
      ignore_unused_variable_warning(m_string);
      m_string = m_cresults.str(std::string(""));
      ignore_unused_variable_warning(m_string);

      typename match_results_type::difference_type diff;
      diff = m_cresults.length(&m_char);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length(m_string);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length("");
      ignore_unused_variable_warning(diff);
      diff = m_cresults.length(std::string(""));
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(&m_char);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(m_string);
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position("");
      ignore_unused_variable_warning(diff);
      diff = m_cresults.position(std::string(""));
      ignore_unused_variable_warning(diff);

#ifndef BOOST_NO_STD_LOCALE
      m_stream << m_sub;
      m_stream << m_cresults;
#endif
      //
      // Extended formatting with a functor:
      //
      regex_constants::match_flag_type f = regex_constants::match_default;
      OutputIterator out = static_object<OutputIterator>::get();
      
      functor3<match_results_default_type> func3;
      functor2<match_results_default_type> func2;
      functor1<match_results_default_type> func1;
      
      functor3<match_results_type> func3b;
      functor2<match_results_type> func2b;
      functor1<match_results_type> func1b;

      out = regex_format(out, m_cresults, func3b, f);
      out = regex_format(out, m_cresults, func3b);
      out = regex_format(out, m_cresults, func2b, f);
      out = regex_format(out, m_cresults, func2b);
      out = regex_format(out, m_cresults, func1b, f);
      out = regex_format(out, m_cresults, func1b);
      out = regex_format(out, m_cresults, boost::ref(func3b), f);
      out = regex_format(out, m_cresults, boost::ref(func3b));
      out = regex_format(out, m_cresults, boost::ref(func2b), f);
      out = regex_format(out, m_cresults, boost::ref(func2b));
      out = regex_format(out, m_cresults, boost::ref(func1b), f);
      out = regex_format(out, m_cresults, boost::ref(func1b));
      out = regex_format(out, m_cresults, boost::cref(func3b), f);
      out = regex_format(out, m_cresults, boost::cref(func3b));
      out = regex_format(out, m_cresults, boost::cref(func2b), f);
      out = regex_format(out, m_cresults, boost::cref(func2b));
      out = regex_format(out, m_cresults, boost::cref(func1b), f);
      out = regex_format(out, m_cresults, boost::cref(func1b));

      m_string += regex_format(m_cresults, func3b, f);
      m_string += regex_format(m_cresults, func3b);
      m_string += regex_format(m_cresults, func2b, f);
      m_string += regex_format(m_cresults, func2b);
      m_string += regex_format(m_cresults, func1b, f);
      m_string += regex_format(m_cresults, func1b);
      m_string += regex_format(m_cresults, boost::ref(func3b), f);
      m_string += regex_format(m_cresults, boost::ref(func3b));
      m_string += regex_format(m_cresults, boost::ref(func2b), f);
      m_string += regex_format(m_cresults, boost::ref(func2b));
      m_string += regex_format(m_cresults, boost::ref(func1b), f);
      m_string += regex_format(m_cresults, boost::ref(func1b));
      m_string += regex_format(m_cresults, boost::cref(func3b), f);
      m_string += regex_format(m_cresults, boost::cref(func3b));
      m_string += regex_format(m_cresults, boost::cref(func2b), f);
      m_string += regex_format(m_cresults, boost::cref(func2b));
      m_string += regex_format(m_cresults, boost::cref(func1b), f);
      m_string += regex_format(m_cresults, boost::cref(func1b));

      out = m_cresults.format(out, func3b, f);
      out = m_cresults.format(out, func3b);
      out = m_cresults.format(out, func2b, f);
      out = m_cresults.format(out, func2b);
      out = m_cresults.format(out, func1b, f);
      out = m_cresults.format(out, func1b);
      out = m_cresults.format(out, boost::ref(func3b), f);
      out = m_cresults.format(out, boost::ref(func3b));
      out = m_cresults.format(out, boost::ref(func2b), f);
      out = m_cresults.format(out, boost::ref(func2b));
      out = m_cresults.format(out, boost::ref(func1b), f);
      out = m_cresults.format(out, boost::ref(func1b));
      out = m_cresults.format(out, boost::cref(func3b), f);
      out = m_cresults.format(out, boost::cref(func3b));
      out = m_cresults.format(out, boost::cref(func2b), f);
      out = m_cresults.format(out, boost::cref(func2b));
      out = m_cresults.format(out, boost::cref(func1b), f);
      out = m_cresults.format(out, boost::cref(func1b));

      m_string += m_cresults.format(func3b, f);
      m_string += m_cresults.format(func3b);
      m_string += m_cresults.format(func2b, f);
      m_string += m_cresults.format(func2b);
      m_string += m_cresults.format(func1b, f);
      m_string += m_cresults.format(func1b);
      m_string += m_cresults.format(boost::ref(func3b), f);
      m_string += m_cresults.format(boost::ref(func3b));
      m_string += m_cresults.format(boost::ref(func2b), f);
      m_string += m_cresults.format(boost::ref(func2b));
      m_string += m_cresults.format(boost::ref(func1b), f);
      m_string += m_cresults.format(boost::ref(func1b));
      m_string += m_cresults.format(boost::cref(func3b), f);
      m_string += m_cresults.format(boost::cref(func3b));
      m_string += m_cresults.format(boost::cref(func2b), f);
      m_string += m_cresults.format(boost::cref(func2b));
      m_string += m_cresults.format(boost::cref(func1b), f);
      m_string += m_cresults.format(boost::cref(func1b));

      out = regex_replace(out, m_in, m_in, ce, func3, f);
      out = regex_replace(out, m_in, m_in, ce, func3);
      out = regex_replace(out, m_in, m_in, ce, func2, f);
      out = regex_replace(out, m_in, m_in, ce, func2);
      out = regex_replace(out, m_in, m_in, ce, func1, f);
      out = regex_replace(out, m_in, m_in, ce, func1);
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func3), f);
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func3));
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func2), f);
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func2));
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func1), f);
      out = regex_replace(out, m_in, m_in, ce, boost::ref(func1));
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func3), f);
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func3));
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func2), f);
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func2));
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func1), f);
      out = regex_replace(out, m_in, m_in, ce, boost::cref(func1));

      functor3<match_results<typename string_type::const_iterator> > func3s;
      functor2<match_results<typename string_type::const_iterator> > func2s;
      functor1<match_results<typename string_type::const_iterator> > func1s;
      m_string += regex_replace(m_string, ce, func3s, f);
      m_string += regex_replace(m_string, ce, func3s);
      m_string += regex_replace(m_string, ce, func2s, f);
      m_string += regex_replace(m_string, ce, func2s);
      m_string += regex_replace(m_string, ce, func1s, f);
      m_string += regex_replace(m_string, ce, func1s);
      m_string += regex_replace(m_string, ce, boost::ref(func3s), f);
      m_string += regex_replace(m_string, ce, boost::ref(func3s));
      m_string += regex_replace(m_string, ce, boost::ref(func2s), f);
      m_string += regex_replace(m_string, ce, boost::ref(func2s));
      m_string += regex_replace(m_string, ce, boost::ref(func1s), f);
      m_string += regex_replace(m_string, ce, boost::ref(func1s));
      m_string += regex_replace(m_string, ce, boost::cref(func3s), f);
      m_string += regex_replace(m_string, ce, boost::cref(func3s));
      m_string += regex_replace(m_string, ce, boost::cref(func2s), f);
      m_string += regex_replace(m_string, ce, boost::cref(func2s));
      m_string += regex_replace(m_string, ce, boost::cref(func1s), f);
      m_string += regex_replace(m_string, ce, boost::cref(func1s));
   }

   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), re(*p), flags(f){ subs.push_back(sub); }


   bool init(BidirectionalIterator first)
   {
      base = first;
      N = 0;
      if(u32regex_search(first, end, what, re, flags, base) == true)
      {
         N = 0;
         result = ((subs[N] == -1) ? what.prefix() : what[(int)subs[N]]);
         return true;
      }
      else if((subs[N] == -1) && (first != end))
      {
         result.first = first;
         result.second = end;
         result.matched = (first != end);
         N = -1;
         return true;
      }
      return false;
   }

   bool compare(const u32regex_token_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) 
         && (end == that.end) 
         && (flags == that.flags) 
         && (N == that.N) 
         && (what[0].first == that.what[0].first) 
         && (what[0].second == that.what[0].second);
   }

   const value_type& get()
   { return result; }

   bool next()
   {
      if(N == -1)
         return false;
      if(N+1 < (int)subs.size())
      {
         ++N;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      //if(what.prefix().first != what[0].second)
      //   flags |= match_prev_avail | regex_constants::match_not_bob;
      BidirectionalIterator last_end(what[0].second);
      if(u32regex_search(last_end, end, what, re, ((what[0].first == what[0].second) ? flags | regex_constants::match_not_initial_null : flags), base))
      {
         N =0;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      else if((last_end != end) && (subs[0] == -1))
      {
         N =-1;
         result.first = last_end;
         result.second = end;
         result.matched = (last_end != end);
         return true;
      }
      return false;
   }

   
   u32regex_token_iterator(){}

   u32regex_token_iterator(const u32regex_token_iterator& that)
      : pdata(that.pdata) {}

   u32regex_token_iterator& operator=(const u32regex_token_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }

   bool operator==(const u32regex_token_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }

   bool operator!=(const u32regex_token_iterator& that)const
   { return !(*this == that); }

   const value_type& operator*()const
   { return pdata->get(); }

   const value_type* operator->()const
   { return &(pdata->get()); }

   u32regex_token_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }

   u32regex_token_iterator operator++(int)
   {
      u32regex_token_iterator result(*this);
      ++(*this);
      return result;
   }


   void cow()
   {
      // copy-on-write
      if(pdata.get() && !pdata.unique())
      {
         pdata.reset(new impl(*(pdata.get())));
      }
   }

inline u32regex_token_iterator<const char*> make_u32regex_token_iterator(const char* p, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const char*>(p, p+std::strlen(p), e, submatch, m);
}


   sub_match() : std::pair<BidiIterator, BidiIterator>(), matched(false) {}

   sub_match(BidiIterator i) : std::pair<BidiIterator, BidiIterator>(i, i), matched(false) {}

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator == (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) == 0; }

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator != (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) != 0; }

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator < (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) < 0; }

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator <= (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) <= 0; }

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator >= (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) >= 0; }

template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator > (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) > 0; }

   concrete_protected_call(T* o, proc_type p)
      : obj(o), proc(p) {}


template <class T>
bool concrete_protected_call<T>::call()const
{
   return (obj->*proc)();
}


template <class T>
inline void pointer_destroy(T* p)
{ p->~T(); (void)p; }


template <class T>
inline void pointer_construct(T* p, const T& t)
{ new (p) T(t); }

   inline std::size_t strcpy_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
      if(std::strlen(strSource)+1 > sizeInBytes)
         return 1;
      std::strcpy(strDestination, strSource);
      return 0;
   }

   inline std::size_t strcat_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
      if(std::strlen(strSource) + std::strlen(strDestination) + 1 > sizeInBytes)
         return 1;
      std::strcat(strDestination, strSource);
      return 0;
   }


   inline void overflow_error_if_not_zero(std::size_t i)
   {
      if(i)
      {
         std::overflow_error e("String buffer too small");
         boost::throw_exception(e);
      }
   }


template <class T>
inline void inplace_destroy(T* p)
{
   (void)p;  // warning suppression
   p->~T();
}

   saved_state(unsigned i) : state_id(i) {}

   saved_matched_paren(int i, const sub_match<BidiIterator>& s) : saved_state(1), index(i), sub(s){};

   saved_position(const re_syntax_base* ps, BidiIterator pos, int i) : saved_state(i), pstate(ps), position(pos){};

   saved_assertion(bool p, const re_syntax_base* ps, BidiIterator pos) 
      : saved_position<BidiIterator>(ps, pos, saved_type_assertion), positive(p){};

   saved_repeater(int i, repeater_count<BidiIterator>** s, BidiIterator start) 
      : saved_state(saved_state_repeater_count), count(i,s,start){}

   saved_extra_block(saved_state* b, saved_state* e) 
      : saved_state(saved_state_extra_block), base(b), end(e) {}

   save_state_init(saved_state** base, saved_state** end)
      : stack(base)
   {
      *base = static_cast<saved_state*>(get_mem_block());
      *end = reinterpret_cast<saved_state*>(reinterpret_cast<char*>(*base)+BOOST_REGEX_BLOCKSIZE);
      --(*end);
      (void) new (*end)saved_state(0);
      BOOST_ASSERT(*end > *base);
   }

   ~save_state_init()
   {
      put_mem_block(*stack);
      *stack = 0;
   }

   saved_single_repeat(std::size_t c, const re_repeat* r, BidiIterator lp, int arg_id) 
      : saved_state(arg_id), count(c), rep(r), last_position(lp){}

   saved_recursion(int idx, const re_syntax_base* p, Results* pr) 
      : saved_state(14), recursion_id(idx), preturn_address(p), results(*pr)
   {}

template <class charT>
inline bool is_extended(charT c)
{ return c > 256; }

inline bool is_extended(char)
{ return false; }


template <class charT>
inline bool is_combining(charT c)
{
   return (c <= static_cast<charT>(0)) ? false : ((c >= static_cast<charT>((std::numeric_limits<uint_least16_t>::max)())) ? false : is_combining_implementation(static_cast<unsigned short>(c)));
}

template <class charT>
inline bool is_separator(charT c)
{
   return BOOST_REGEX_MAKE_BOOL(
      (c == static_cast<charT>('\n'))
      || (c == static_cast<charT>('\r'))
      || (c == static_cast<charT>('\f'))
      || (static_cast<boost::uint16_t>(c) == 0x2028u)
      || (static_cast<boost::uint16_t>(c) == 0x2029u)
      || (static_cast<boost::uint16_t>(c) == 0x85u));
}


   bool operator < (const character_pointer_range& r)const
   {
      return std::lexicographical_compare(p1, p2, r.p1, r.p2);
   }

   bool operator == (const character_pointer_range& r)const
   {
      // Not only do we check that the ranges are of equal size before
      // calling std::equal, but there is no other algorithm available:
      // not even a non-standard MS one.  So forward to unchecked_equal
      // in the MS case.
      return ((p2 - p1) == (r.p2 - r.p1)) && re_detail::equal(p1, p2, r.p1);
   }

template <class charT>
int get_default_class_id(const charT* p1, const charT* p2)
{
   static const charT data[73] = {
      'a', 'l', 'n', 'u', 'm',
      'a', 'l', 'p', 'h', 'a',
      'b', 'l', 'a', 'n', 'k',
      'c', 'n', 't', 'r', 'l',
      'd', 'i', 'g', 'i', 't',
      'g', 'r', 'a', 'p', 'h',
      'l', 'o', 'w', 'e', 'r',
      'p', 'r', 'i', 'n', 't',
      'p', 'u', 'n', 'c', 't',
      's', 'p', 'a', 'c', 'e',
      'u', 'n', 'i', 'c', 'o', 'd', 'e',
      'u', 'p', 'p', 'e', 'r',
      'v',
      'w', 'o', 'r', 'd',
      'x', 'd', 'i', 'g', 'i', 't',
   };

   static const character_pointer_range<charT> ranges[21] =
   {
      {data+0, data+5,}, // alnum
      {data+5, data+10,}, // alpha
      {data+10, data+15,}, // blank
      {data+15, data+20,}, // cntrl
      {data+20, data+21,}, // d
      {data+20, data+25,}, // digit
      {data+25, data+30,}, // graph
      {data+29, data+30,}, // h
      {data+30, data+31,}, // l
      {data+30, data+35,}, // lower
      {data+35, data+40,}, // print
      {data+40, data+45,}, // punct
      {data+45, data+46,}, // s
      {data+45, data+50,}, // space
      {data+57, data+58,}, // u
      {data+50, data+57,}, // unicode
      {data+57, data+62,}, // upper
      {data+62, data+63,}, // v
      {data+63, data+64,}, // w
      {data+63, data+67,}, // word
      {data+67, data+73,}, // xdigit
   };
   static const character_pointer_range<charT>* ranges_begin = ranges;
   static const character_pointer_range<charT>* ranges_end = ranges + (sizeof(ranges)/sizeof(ranges[0]));

   character_pointer_range<charT> t = { p1, p2, };
   const character_pointer_range<charT>* p = std::lower_bound(ranges_begin, ranges_end, t);
   if((p != ranges_end) && (t == *p))
      return static_cast<int>(p - ranges);
   return -1;
}

template <class charT>
std::ptrdiff_t global_length(const charT* p)
{
   std::ptrdiff_t n = 0;
   while(*p)
   {
      ++p;
      ++n;
   }
   return n;
}
 global_lower(charT c)
{
   return c;
}
 global_upper(charT c)
{
   return c;
}


template <class charT>
int global_value(charT c)
{
   static const charT zero = '0';
   static const charT nine = '9';
   static const charT a = 'a';
   static const charT f = 'f';
   static const charT A = 'A';
   static const charT F = 'F';

   if(c > f) return -1;
   if(c >= a) return 10 + (c - a);
   if(c > F) return -1;
   if(c >= A) return 10 + (c - A);
   if(c > nine) return -1;
   if(c >= zero) return c - zero;
   return -1;
}

template <class charT, class traits>
int global_toi(const charT*& p1, const charT* p2, int radix, const traits& t)
{
   (void)t; // warning suppression
   int next_value = t.value(*p1, radix);
   if((p1 == p2) || (next_value < 0) || (next_value >= radix))
      return -1;
   int result = 0;
   while(p1 != p2)
   {
      next_value = t.value(*p1, radix);
      if((next_value < 0) || (next_value >= radix))
         break;
      result *= radix;
      result += next_value;
      ++p1;
   }
   return result;
}


template <class charT>
inline const charT* get_escape_R_string()
{
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4309 4245)
#endif
   static const charT e1[] = { '(', '?', '>', '\x0D', '\x0A', '?',
      '|', '[', '\x0A', '\x0B', '\x0C', static_cast<unsigned char>('\x85'), '\\', 'x', '{', '2', '0', '2', '8', '}',
                '\\', 'x', '{', '2', '0', '2', '9', '}', ']', ')', '\0' };
   static const charT e2[] = { '(', '?', '>', '\x0D', '\x0A', '?',
      '|', '[', '\x0A', '\x0B', '\x0C', static_cast<unsigned char>('\x85'), ']', ')', '\0' };

   charT c = static_cast<charT>(0x2029u);
   bool b = (static_cast<unsigned>(c) == 0x2029u);

   return (b ? e1 : e2);
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
}

   explicit match_results(const Allocator& a = Allocator())
#ifndef BOOST_NO_STD_ALLOCATOR
      : m_subs(a), m_base(), m_last_closed_paren(0), m_is_singular(true) {}

   match_results(const match_results& m)
      : m_subs(m.m_subs), m_named_subs(m.m_named_subs), m_last_closed_paren(m.m_last_closed_paren), m_is_singular(m.m_is_singular) 
   {
      if(!m_is_singular)
      {
         m_base = m.m_base;
         m_null = m.m_null;
      }
   }

   match_results& operator=(const match_results& m)
   {
      m_subs = m.m_subs;
      m_named_subs = m.m_named_subs;
      m_last_closed_paren = m.m_last_closed_paren;
      m_is_singular = m.m_is_singular;
      if(!m_is_singular)
      {
         m_base = m.m_base;
         m_null = m.m_null;
      }
      return *this;
   }

   ~match_results(){}

   size_type size() const
   { return empty() ? 0 : m_subs.size() - 2; }

   size_type max_size() const
   { return m_subs.max_size(); }

   bool empty() const
   { return m_subs.size() < 2; }

   difference_type length(int sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      if((sub < (int)m_subs.size()) && (sub > 0))
         return m_subs[sub].length();
      return 0;
   }

   difference_type position(size_type sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      if(sub < m_subs.size())
      {
         const sub_match<BidiIterator>& s = m_subs[sub];
         if(s.matched || (sub == 2))
         {
            return ::boost::re_detail::distance((BidiIterator)(m_base), (BidiIterator)(s.first));
         }
      }
      return ~static_cast<difference_type>(0);
   }

   string_type str(int sub = 0) const
   {
      if(m_is_singular)
         raise_logic_error();
      sub += 2;
      string_type result;
      if(sub < (int)m_subs.size() && (sub > 0))
      {
         const sub_match<BidiIterator>& s = m_subs[sub];
         if(s.matched)
         {
            result = s.str();
         }
      }
      return result;
   }

   const_reference operator[](int sub) const
   {
      if(m_is_singular && m_subs.empty())
         raise_logic_error();
      sub += 2;
      if(sub < (int)m_subs.size() && (sub >= 0))
      {
         return m_subs[sub];
      }
      return m_null;
   }

   const_reference named_subexpression(const char_type* i, const char_type* j) const
   {
      //
      // Scan for the leftmost *matched* subexpression with the specified named:
      //
      if(m_is_singular)
         raise_logic_error();
      re_detail::named_subexpressions::range_type r = m_named_subs->equal_range(i, j);
      while((r.first != r.second) && ((*this)[r.first->index].matched == false))
         ++r.first;
      return r.first != r.second ? (*this)[r.first->index] : m_null;
   }

   template <class charT>
   const_reference named_subexpression(const charT* i, const charT* j) const
   {
      BOOST_STATIC_ASSERT(sizeof(charT) <= sizeof(char_type));
      if(i == j)
         return m_null;
      std::vector<char_type> s;
      while(i != j)
         s.insert(s.end(), *i++);
      return named_subexpression(&*s.begin(), &*s.begin() + s.size());
   }

   int named_subexpression_index(const char_type* i, const char_type* j) const
   {
      //
      // Scan for the leftmost *matched* subexpression with the specified named.
      // If none found then return the leftmost expression with that name,
      // otherwise an invalid index:
      //
      if(m_is_singular)
         raise_logic_error();
      re_detail::named_subexpressions::range_type s, r;
      s = r = m_named_subs->equal_range(i, j);
      while((r.first != r.second) && ((*this)[r.first->index].matched == false))
         ++r.first;
      if(r.first == r.second)
         r = s;
      return r.first != r.second ? r.first->index : -20;
   }

   template <class charT>
   int named_subexpression_index(const charT* i, const charT* j) const
   {
      BOOST_STATIC_ASSERT(sizeof(charT) <= sizeof(char_type));
      if(i == j)
         return -20;
      std::vector<char_type> s;
      while(i != j)
         s.insert(s.end(), *i++);
      return named_subexpression_index(&*s.begin(), &*s.begin() + s.size());
   }


   template <class charT>
   const_reference operator[](const charT* p) const
   {
      BOOST_STATIC_ASSERT(sizeof(charT) <= sizeof(char_type));
      if(*p == 0)
         return m_null;
      std::vector<char_type> s;
      while(*p)
         s.insert(s.end(), *p++);
      return named_subexpression(&*s.begin(), &*s.begin() + s.size());
   }


   const_reference prefix() const
   {
      if(m_is_singular)
         raise_logic_error();
      return (*this)[-1];
   }


   const_reference suffix() const
   {
      if(m_is_singular)
         raise_logic_error();
      return (*this)[-2];
   }

   const_iterator begin() const
   {
      return (m_subs.size() > 2) ? (m_subs.begin() + 2) : m_subs.end();
   }

   const_iterator end() const
   {
      return m_subs.end();
   }

   template <class OutputIterator, class Functor>
   OutputIterator format(OutputIterator out,
                         Functor fmt,
                         match_flag_type flags = format_default) const
   {
      if(m_is_singular)
         raise_logic_error();
      typedef typename re_detail::compute_functor_type<Functor, match_results<BidiIterator, Allocator>, OutputIterator>::type F;
      F func(fmt);
      return func(*this, out, flags);
   }


   const_reference get_last_closed_paren()const
   {
      if(m_is_singular)
         raise_logic_error();
      return m_last_closed_paren == 0 ? m_null : (*this)[m_last_closed_paren];
   }


   allocator_type get_allocator() const
   {
#ifndef BOOST_NO_STD_ALLOCATOR
      return m_subs.get_allocator();
#else
     return allocator_type();
#endif
   }

   void swap(match_results& that)
   {
      std::swap(m_subs, that.m_subs);
      std::swap(m_named_subs, that.m_named_subs);
      std::swap(m_last_closed_paren, that.m_last_closed_paren);
      if(m_is_singular)
      {
         if(!that.m_is_singular)
         {
            m_base = that.m_base;
            m_null = that.m_null;
         }
      }
      else if(that.m_is_singular)
      {
         that.m_base = m_base;
         that.m_null = m_null;
      }
      else
      {
         std::swap(m_base, that.m_base);
         std::swap(m_null, that.m_null);
      }
      std::swap(m_is_singular, that.m_is_singular);
   }

   bool operator==(const match_results& that)const
   {
      if(m_is_singular)
      {
         return that.m_is_singular;
      }
      else if(that.m_is_singular)
      {
         return false;
      }
      return (m_subs == that.m_subs) && (m_base == that.m_base) && (m_last_closed_paren == that.m_last_closed_paren);
   }

   bool operator!=(const match_results& that)const
   { return !(*this == that); }
 match_results<BidiIterator, Allocator>::maybe_assign(const match_results<BidiIterator, Allocator>& m)
{
   if(m_is_singular)
   {
      *this = m;
      return;
   }
   const_iterator p1, p2;
   p1 = begin();
   p2 = m.begin();
   //
   // Distances are measured from the start of *this* match, unless this isn't
   // a valid match in which case we use the start of the whole sequence.  Note that
   // no subsequent match-candidate can ever be to the left of the first match found.
   // This ensures that when we are using bidirectional iterators, that distances 
   // measured are as short as possible, and therefore as efficient as possible
   // to compute.  Finally note that we don't use the "matched" data member to test
   // whether a sub-expression is a valid match, because partial matches set this
   // to false for sub-expression 0.
   //
   BidiIterator l_end = this->suffix().second;
   BidiIterator l_base = (p1->first == l_end) ? this->prefix().first : (*this)[0].first;
   difference_type len1 = 0;
   difference_type len2 = 0;
   difference_type base1 = 0;
   difference_type base2 = 0;
   std::size_t i;
   for(i = 0; i < size(); ++i, ++p1, ++p2)
   {
      //
      // Leftmost takes priority over longest; handle special cases
      // where distances need not be computed first (an optimisation
      // for bidirectional iterators: ensure that we don't accidently
      // compute the length of the whole sequence, as this can be really
      // expensive).
      //
      if(p1->first == l_end)
      {
         if(p2->first != l_end)
         {
            // p2 must be better than p1, and no need to calculate
            // actual distances:
            base1 = 1;
            base2 = 0;
            break;
         }
         else
         {
            // *p1 and *p2 are either unmatched or match end-of sequence,
            // either way no need to calculate distances:
            if((p1->matched == false) && (p2->matched == true))
               break;
            if((p1->matched == true) && (p2->matched == false))
               return;
            continue;
         }
      }
      else if(p2->first == l_end)
      {
         // p1 better than p2, and no need to calculate distances:
         return;
      }
      base1 = ::boost::re_detail::distance(l_base, p1->first);
      base2 = ::boost::re_detail::distance(l_base, p2->first);
      BOOST_ASSERT(base1 >= 0);
      BOOST_ASSERT(base2 >= 0);
      if(base1 < base2) return;
      if(base2 < base1) break;

      len1 = ::boost::re_detail::distance((BidiIterator)p1->first, (BidiIterator)p1->second);
      len2 = ::boost::re_detail::distance((BidiIterator)p2->first, (BidiIterator)p2->second);
      BOOST_ASSERT(len1 >= 0);
      BOOST_ASSERT(len2 >= 0);
      if((len1 != len2) || ((p1->matched == false) && (p2->matched == true)))
         break;
      if((p1->matched == true) && (p2->matched == false))
         return;
   }
   if(i == size())
      return;
   if(base2 < base1)
      *this = m;
   else if((len2 > len1) || ((p1->matched == false) && (p2->matched == true)) )
      *this = m;
}


template <class BidiIterator, class Allocator>
void swap(match_results<BidiIterator, Allocator>& a, match_results<BidiIterator, Allocator>& b)
{
   a.swap(b);
}


template <class OutputIterator, class charT, class Traits1, class Alloc1, class Traits2>
std::size_t regex_split(OutputIterator out,
                   std::basic_string<charT, Traits1, Alloc1>& s, 
                   const basic_regex<charT, Traits2>& e,
                   match_flag_type flags,
                   std::size_t max_split)
{
   typedef typename std::basic_string<charT, Traits1, Alloc1>::const_iterator  ci_t;
   //typedef typename match_results<ci_t>::allocator_type                        match_allocator;
   ci_t last = s.begin();
   std::size_t init_size = max_split;
   re_detail::split_pred<OutputIterator, charT, Traits1, Alloc1> pred(&last, &out, &max_split);
   ci_t i, j;
   i = s.begin();
   j = s.end();
   regex_grep(pred, i, j, e, flags);
   //
   // if there is still input left, do a final push as long as max_split
   // is not exhausted, and we're not splitting sub-expressions rather 
   // than whitespace:
   if(max_split && (last != s.end()) && (e.mark_count() == 1))
   {
      *out = std::basic_string<charT, Traits1, Alloc1>((ci_t)last, (ci_t)s.end());
      ++out;
      last = s.end();
      --max_split;
   }
   //
   // delete from the string everything that has been processed so far:
   s.erase(0, last - s.begin());
   //
   // return the number of new records pushed:
   return init_size - max_split;
}


template <class OutputIterator, class BidirectionalIterator, class traits, class charT, class Formatter>
OutputIterator regex_replace(OutputIterator out,
                         BidirectionalIterator first,
                         BidirectionalIterator last,
                         const basic_regex<charT, traits>& e, 
                         Formatter fmt, 
                         match_flag_type flags = match_default)
{
   regex_iterator<BidirectionalIterator, charT, traits> i(first, last, e, flags);
   regex_iterator<BidirectionalIterator, charT, traits> j;
   if(i == j)
   {
      if(!(flags & regex_constants::format_no_copy))
         out = re_detail::copy(first, last, out);
   }
   else
   {
      BidirectionalIterator last_m(first);
      while(i != j)
      {
         if(!(flags & regex_constants::format_no_copy))
            out = re_detail::copy(i->prefix().first, i->prefix().second, out); 
         out = i->format(out, fmt, flags, e);
         last_m = (*i)[0].second;
         if(flags & regex_constants::format_first_only)
            break;
         ++i;
      }
      if(!(flags & regex_constants::format_no_copy))
         out = re_detail::copy(last_m, last, out);
   }
   return out;
}

   template <class A>
   backup_subex(const match_results<BidiIterator, A>& w, int i)
      : index(i), sub(w[i], false) {}

   template <class A>
   void restore(match_results<BidiIterator, A>& w)
   {
      w.set_first(sub.first, index, index == 0);
      w.set_second(sub.second, index, sub.matched, index == 0);
   }


template <class OutputIterator, class Iterator, class traits, class charT>
inline OutputIterator regex_merge(OutputIterator out,
                         Iterator first,
                         Iterator last,
                         const basic_regex<charT, traits>& e, 
                         const charT* fmt, 
                         match_flag_type flags = match_default)
{
   return regex_replace(out, first, last, e, fmt, flags);
}

   w32_regex_traits_base(lcid_type l)
   { imbue(l); }


template <class charT>
inline lcid_type w32_regex_traits_base<charT>::imbue(lcid_type l)
{
   lcid_type result(m_locale);
   m_locale = l;
   return result;
}


   regex_constants::syntax_type syntax_type(charT c)const
   {
      map_iterator_type i = m_char_map.find(c);
      return ((i == m_char_map.end()) ? 0 : i->second);
   }

   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      map_iterator_type i = m_char_map.find(c);
      if(i == m_char_map.end())
      {
         if(::boost::re_detail::w32_is_lower(c, this->m_locale)) return regex_constants::escape_type_class;
         if(::boost::re_detail::w32_is_upper(c, this->m_locale)) return regex_constants::escape_type_not_class;
         return 0;
      }
      return i->second;
   }

   charT tolower(charT c)const
   {
      return ::boost::re_detail::w32_tolower(c, this->m_locale);
   }

   bool isctype(boost::uint32_t mask, charT c)const
   {
      return ::boost::re_detail::w32_is(this->m_locale, mask, c);
   }

   std::string error_string(regex_constants::error_type n) const
   {
      if(!m_error_strings.empty())
      {
         std::map<int, std::string>::const_iterator p = m_error_strings.find(n);
         return (p == m_error_strings.end()) ? std::string(get_default_error_string(n)) : p->second;
      }
      return get_default_error_string(n);
   }

   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      char_class_type result = lookup_classname_imp(p1, p2);
      if(result == 0)
      {
         typedef typename string_type::size_type size_type;
         string_type temp(p1, p2);
         for(size_type i = 0; i < temp.size(); ++i)
            temp[i] = this->tolower(temp[i]);
         result = lookup_classname_imp(&*temp.begin(), &*temp.begin() + temp.size());
      }
      return result;
   }

   string_type transform(const charT* p1, const charT* p2) const
   {
      return ::boost::re_detail::w32_transform(this->m_locale, p1, p2);
   }


template <class charT>
typename w32_regex_traits_implementation<charT>::char_class_type 
   w32_regex_traits_implementation<charT>::lookup_classname_imp(const charT* p1, const charT* p2) const
{
   static const char_class_type masks[22] = 
   {
      0,
      0x0104u, // C1_ALPHA | C1_DIGIT
      0x0100u, // C1_ALPHA
      0x0040u, // C1_BLANK
      0x0020u, // C1_CNTRL
      0x0004u, // C1_DIGIT
      0x0004u, // C1_DIGIT
      (~(0x0020u|0x0008u|0x0040) & 0x01ffu) | 0x0400u, // not C1_CNTRL or C1_SPACE or C1_BLANK
      w32_regex_traits_implementation<charT>::mask_horizontal, 
      0x0002u, // C1_LOWER
      0x0002u, // C1_LOWER
      (~0x0020u & 0x01ffu) | 0x0400, // not C1_CNTRL
      0x0010u, // C1_PUNCT
      0x0008u, // C1_SPACE
      0x0008u, // C1_SPACE
      0x0001u, // C1_UPPER
      w32_regex_traits_implementation<charT>::mask_unicode,
      0x0001u, // C1_UPPER
      w32_regex_traits_implementation<charT>::mask_vertical, 
      0x0104u | w32_regex_traits_implementation<charT>::mask_word, 
      0x0104u | w32_regex_traits_implementation<charT>::mask_word, 
      0x0080u, // C1_XDIGIT
   };
   if(m_custom_class_names.size())
   {
      typedef typename std::map<std::basic_string<charT>, char_class_type>::const_iterator map_iter;
      map_iter pos = m_custom_class_names.find(string_type(p1, p2));
      if(pos != m_custom_class_names.end())
         return pos->second;
   }
   std::size_t state_id = 1 + re_detail::get_default_class_id(p1, p2);
   if(state_id < sizeof(masks) / sizeof(masks[0]))
      return masks[state_id];
   return masks[0];
}


   w32_regex_traits()
      : m_pimpl(re_detail::create_w32_regex_traits<charT>(::boost::re_detail::w32_get_default_locale()))
   { }

   static size_type length(const char_type* p)
   {
      return std::char_traits<charT>::length(p);
   }

   regex_constants::syntax_type syntax_type(charT c)const
   {
      return m_pimpl->syntax_type(c);
   }

   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      return m_pimpl->escape_syntax_type(c);
   }

   charT translate(charT c) const
   {
      return c;
   }

   charT translate_nocase(charT c) const
   {
      return this->m_pimpl->tolower(c);
   }

   charT translate(charT c, bool icase) const
   {
      return icase ? this->m_pimpl->tolower(c) : c;
   }

   charT tolower(charT c) const
   {
      return this->m_pimpl->tolower(c);
   }

   charT toupper(charT c) const
   {
      return ::boost::re_detail::w32_toupper(c, this->m_pimpl->m_locale);
   }

   string_type transform(const charT* p1, const charT* p2) const
   {
      return ::boost::re_detail::w32_transform(this->m_pimpl->m_locale, p1, p2);
   }

   string_type transform_primary(const charT* p1, const charT* p2) const
   {
      return m_pimpl->transform_primary(p1, p2);
   }

   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_classname(p1, p2);
   }

   string_type lookup_collatename(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_collatename(p1, p2);
   }

   bool isctype(charT c, char_class_type f) const
   {
      if((f & re_detail::w32_regex_traits_implementation<charT>::mask_base) 
         && (this->m_pimpl->isctype(f & re_detail::w32_regex_traits_implementation<charT>::mask_base, c)))
         return true;
      else if((f & re_detail::w32_regex_traits_implementation<charT>::mask_unicode) && re_detail::is_extended(c))
         return true;
      else if((f & re_detail::w32_regex_traits_implementation<charT>::mask_word) && (c == '_'))
         return true;
      else if((f & re_detail::w32_regex_traits_implementation<charT>::mask_vertical)
         && (::boost::re_detail::is_separator(c) || (c == '\v')))
         return true;
      else if((f & re_detail::w32_regex_traits_implementation<charT>::mask_horizontal) 
         && this->isctype(c, 0x0008u) && !this->isctype(c, re_detail::w32_regex_traits_implementation<charT>::mask_vertical))
         return true;
      return false;
   }

   int toi(const charT*& p1, const charT* p2, int radix)const
   {
      return ::boost::re_detail::global_toi(p1, p2, radix, *this);
   }

   int value(charT c, int radix)const
   {
      int result = ::boost::re_detail::global_value(c);
      return result < radix ? result : -1;
   }

   locale_type imbue(locale_type l)
   {
      ::boost::re_detail::lcid_type result(getloc());
      m_pimpl = re_detail::create_w32_regex_traits<charT>(l);
      return result;
   }

   locale_type getloc()const
   {
      return m_pimpl->m_locale;
   }

   std::string error_string(regex_constants::error_type n) const
   {
      return m_pimpl->error_string(n);
   }

   regex_iterator_implementation(const regex_type* p, BidirectionalIterator last, match_flag_type f)
      : base(), end(last), re(*p), flags(f){}

   bool init(BidirectionalIterator first)
   {
      base = first;
      return regex_search(first, end, what, re, flags);
   }

   bool compare(const regex_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) && (end == that.end) && (flags == that.flags) && (what[0].first == that.what[0].first) && (what[0].second == that.what[0].second);
   }

   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), re(*p), flags(f){ subs.push_back(sub); }

   bool init(BidirectionalIterator first)
   {
      N = 0;
      base = first;
      if(regex_search(first, end, what, re, flags, base) == true)
      {
         N = 0;
         result = ((subs[N] == -1) ? what.prefix() : what[(int)subs[N]]);
         return true;
      }
      else if((subs[N] == -1) && (first != end))
      {
         result.first = first;
         result.second = end;
         result.matched = (first != end);
         N = -1;
         return true;
      }
      return false;
   }

   bool compare(const regex_token_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) 
         && (end == that.end) 
         && (flags == that.flags) 
         && (N == that.N) 
         && (what[0].first == that.what[0].first) 
         && (what[0].second == that.what[0].second);
   }

   const value_type& get()
   { return result; }

   bool next()
   {
      if(N == -1)
         return false;
      if(N+1 < (int)subs.size())
      {
         ++N;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      //if(what.prefix().first != what[0].second)
      //   flags |= /*match_prev_avail |*/ regex_constants::match_not_bob;
      BidirectionalIterator last_end(what[0].second);
      if(regex_search(last_end, end, what, re, ((what[0].first == what[0].second) ? flags | regex_constants::match_not_initial_null : flags), base))
      {
         N =0;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      else if((last_end != end) && (subs[0] == -1))
      {
         N =-1;
         result.first = last_end;
         result.second = end;
         result.matched = (last_end != end);
         return true;
      }
      return false;
   }


template <class S, class charT>
unsigned count_chars(const S& s, charT c)
{
   //
   // Count how many occurances of character c occur
   // in string s: if c is a delimeter between collation
   // fields, then this should be the same value for all
   // sort keys:
   //
   unsigned int count = 0;
   for(unsigned pos = 0; pos < s.size(); ++pos)
   {
      if(s[pos] == c) ++count;
   }
   return count;
}



template <class traits, class charT>
unsigned find_sort_syntax(const traits* pt, charT* delim)
{
   //
   // compare 'a' with 'A' to see how similar they are,
   // should really use a-accute but we can't portably do that,
   //
   typedef typename traits::string_type string_type;
   typedef typename traits::char_type char_type;

   // Suppress incorrect warning for MSVC
   (void)pt;

   char_type a[2] = {'a', '\0', };
   string_type sa(pt->transform(a, a+1));
   if(sa == a)
   {
      *delim = 0;
      return sort_C;
   }
   char_type A[2] = { 'A', '\0', };
   string_type sA(pt->transform(A, A+1));
   char_type c[2] = { ';', '\0', };
   string_type sc(pt->transform(c, c+1));

   int pos = 0;
   while((pos <= static_cast<int>(sa.size())) && (pos <= static_cast<int>(sA.size())) && (sa[pos] == sA[pos])) ++pos;
   --pos;
   if(pos < 0)
   {
      *delim = 0;
      return sort_unknown;
   }
   //
   // at this point sa[pos] is either the end of a fixed width field
   // or the character that acts as a delimiter:
   //
   charT maybe_delim = sa[pos];
   if((pos != 0) && (count_chars(sa, maybe_delim) == count_chars(sA, maybe_delim)) && (count_chars(sa, maybe_delim) == count_chars(sc, maybe_delim)))
   {
      *delim = maybe_delim;
      return sort_delim;
   }
   //
   // OK doen't look like a delimiter, try for fixed width field:
   //
   if((sa.size() == sA.size()) && (sa.size() == sc.size()))
   {
      // note assumes that the fixed width field is less than
      // (numeric_limits<charT>::max)(), should be true for all types
      // I can't imagine 127 character fields...
      *delim = static_cast<charT>(++pos);
      return sort_fixed;
   }
   //
   // don't know what it is:
   //
   *delim = 0;
   return sort_unknown;
}

   digraph() : std::pair<charT, charT>(0, 0){}

   digraph(charT c1) : std::pair<charT, charT>(c1, 0){}

   digraph(charT c1, charT c2) : std::pair<charT, charT>(c1, c2)
   {}

   template <class Seq>
   digraph(const Seq& s) : std::pair<charT, charT>()
   {
      BOOST_ASSERT(s.size() <= 2);
      BOOST_ASSERT(s.size());
      this->first = s[0];
      this->second = (s.size() > 1) ? s[1] : 0;
   }


   basic_char_set()
   {
      m_negate = false;
      m_has_digraphs = false;
      m_classes = 0;
      m_negated_classes = 0;
      m_empty = true;
   }


   void add_single(const digraph_type& s)
   {
      m_singles.insert(m_singles.end(), s);
      if(s.second)
         m_has_digraphs = true;
      m_empty = false;
   }

   void add_range(const digraph_type& first, const digraph_type& end)
   {
      m_ranges.insert(m_ranges.end(), first);
      m_ranges.insert(m_ranges.end(), end);
      if(first.second)
      {
         m_has_digraphs = true;
         add_single(first);
      }
      if(end.second)
      {
         m_has_digraphs = true;
         add_single(end);
      }
      m_empty = false;
   }

   void add_class(m_type m)
   {
      m_classes |= m;
      m_empty = false;
   }

   void add_negated_class(m_type m)
   {
      m_negated_classes |= m;
      m_empty = false;
   }

   void add_equivalent(const digraph_type& s)
   {
      m_equivalents.insert(m_equivalents.end(), s);
      if(s.second)
      {
         m_has_digraphs = true;
         add_single(s);
      }
      m_empty = false;
   }

   void negate()
   { 
      m_negate = true;
      //m_empty = false;
   }

   bool has_digraphs()const
   {
      return m_has_digraphs;
   }

   bool is_negated()const
   {
      return m_negate;
   }

   list_iterator singles_begin()const
   {
      return m_singles.begin();
   }

   list_iterator singles_end()const
   {
      return m_singles.end();
   }

   list_iterator ranges_begin()const
   {
      return m_ranges.begin();
   }

   list_iterator ranges_end()const
   {
      return m_ranges.end();
   }

   list_iterator equivalents_begin()const
   {
      return m_equivalents.begin();
   }

   list_iterator equivalents_end()const
   {
      return m_equivalents.end();
   }

   m_type classes()const
   {
      return m_classes;
   }

   m_type negated_classes()const
   {
      return m_negated_classes;
   }

   bool empty()const
   {
      return m_empty;
   }

   std::ptrdiff_t getoffset(void* addr)
   {
      return getoffset(addr, m_pdata->m_data.data());
   }

   re_syntax_base* getaddress(std::ptrdiff_t off)
   {
      return getaddress(off, m_pdata->m_data.data());
   }

   void init(unsigned l_flags)
   {
      m_pdata->m_flags = l_flags;
      m_icase = l_flags & regex_constants::icase;
   }

   regbase::flag_type flags()
   {
      return m_pdata->m_flags;
   }


template<class T>
inline bool char_less(T t1, T t2)
{
   return t1 < t2;
}

inline bool char_less(char t1, char t2)
{
   return static_cast<unsigned char>(t1) < static_cast<unsigned char>(t2);
}

inline bool char_less(signed char t1, signed char t2)
{
   return static_cast<unsigned char>(t1) < static_cast<unsigned char>(t2);
}


template <class charT, class traits>
void basic_regex_creator<charT, traits>::finalize(const charT* p1, const charT* p2)
{
   if(this->m_pdata->m_status)
      return;
   // we've added all the states we need, now finish things off.
   // start by adding a terminating state:
   append_state(syntax_element_match);
   // extend storage to store original expression:
   std::ptrdiff_t len = p2 - p1;
   m_pdata->m_expression_len = len;
   charT* ps = static_cast<charT*>(m_pdata->m_data.extend(sizeof(charT) * (1 + (p2 - p1))));
   m_pdata->m_expression = ps;
   re_detail::copy(p1, p2, ps);
   ps[p2 - p1] = 0;
   // fill in our other data...
   // successful parsing implies a zero status:
   m_pdata->m_status = 0;
   // get the first state of the machine:
   m_pdata->m_first_state = static_cast<re_syntax_base*>(m_pdata->m_data.data());
   // fixup pointers in the machine:
   fixup_pointers(m_pdata->m_first_state);
   if(m_has_recursions)
   {
      m_pdata->m_has_recursions = true;
      fixup_recursions(m_pdata->m_first_state);
      if(this->m_pdata->m_status)
         return;
   }
   else
      m_pdata->m_has_recursions = false;
   // create nested startmaps:
   create_startmaps(m_pdata->m_first_state);
   // create main startmap:
   std::memset(m_pdata->m_startmap, 0, sizeof(m_pdata->m_startmap));
   m_pdata->m_can_be_null = 0;

   m_bad_repeats = 0;
   if(m_has_recursions)
      m_recursion_checks.assign(1 + m_pdata->m_mark_count, false);
   create_startmap(m_pdata->m_first_state, m_pdata->m_startmap, &(m_pdata->m_can_be_null), mask_all);
   // get the restart type:
   m_pdata->m_restart_type = get_restart_type(m_pdata->m_first_state);
   // optimise a leading repeat if there is one:
   probe_leading_repeat(m_pdata->m_first_state);
}


template <class charT, class traits>
void basic_regex_creator<charT, traits>::set_all_masks(unsigned char* bits, unsigned char mask)
{
   //
   // set mask in all of bits elements, 
   // if bits[0] has mask_init not set then we can 
   // optimise this to a call to memset:
   //
   if(bits)
   {
      if(bits[0] == 0)
         (std::memset)(bits, mask, 1u << CHAR_BIT);
      else
      {
         for(unsigned i = 0; i < (1u << CHAR_BIT); ++i)
            bits[i] |= mask;
      }
      bits[0] |= mask_init;
   }
}

inline match_flags operator&(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) & static_cast<boost::int32_t>(m2)); }

inline match_flags operator|(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) | static_cast<boost::int32_t>(m2)); }

inline match_flags operator^(match_flags m1, match_flags m2)
{ return static_cast<match_flags>(static_cast<boost::int32_t>(m1) ^ static_cast<boost::int32_t>(m2)); }

inline match_flags operator~(match_flags m1)
{ return static_cast<match_flags>(~static_cast<boost::int32_t>(m1)); }

inline match_flags& operator&=(match_flags& m1, match_flags m2)
{ m1 = m1&m2; return m1; }

inline match_flags& operator|=(match_flags& m1, match_flags m2)
{ m1 = m1|m2; return m1; }

inline match_flags& operator^=(match_flags& m1, match_flags m2)
{ m1 = m1^m2; return m1; }


template <class charT, class traits>
void basic_regex_parser<charT, traits>::parse(const charT* p1, const charT* p2, unsigned l_flags)
{
   // pass l_flags on to base class:
   this->init(l_flags);
   // set up pointers:
   m_position = m_base = p1;
   m_end = p2;
   // empty strings are errors:
   if((p1 == p2) && 
      (
         ((l_flags & regbase::main_option_type) != regbase::perl_syntax_group)
         || (l_flags & regbase::no_empty_expressions)
      )
     )
   {
      fail(regex_constants::error_empty, 0);
      return;
   }
   // select which parser to use:
   switch(l_flags & regbase::main_option_type)
   {
   case regbase::perl_syntax_group:
      {
         m_parser_proc = &basic_regex_parser<charT, traits>::parse_extended;
         //
         // Add a leading paren with index zero to give recursions a target:
         //
         re_brace* br = static_cast<re_brace*>(this->append_state(syntax_element_startmark, sizeof(re_brace)));
         br->index = 0;
         br->icase = this->flags() & regbase::icase;
         break;
      }
   case regbase::basic_syntax_group:
      m_parser_proc = &basic_regex_parser<charT, traits>::parse_basic;
      break;
   case regbase::literal:
      m_parser_proc = &basic_regex_parser<charT, traits>::parse_literal;
      break;
   default:
      // Ooops, someone has managed to set more than one of the main option flags, 
      // so this must be an error:
      fail(regex_constants::error_unknown, 0, "An invalid combination of regular expression syntax flags was used.");
      return;
   }

   // parse all our characters:
   bool result = parse_all();
   //
   // Unwind our alternatives:
   //
   unwind_alts(-1);
   // reset l_flags as a global scope (?imsx) may have altered them:
   this->flags(l_flags);
   // if we haven't gobbled up all the characters then we must
   // have had an unexpected ')' :
   if(!result)
   {
      fail(regex_constants::error_paren, ::boost::re_detail::distance(m_base, m_position), "Found a closing ) with no corresponding openening parenthesis.");
      return;
   }
   // if an error has been set then give up now:
   if(this->m_pdata->m_status)
      return;
   // fill in our sub-expression count:
   this->m_pdata->m_mark_count = 1 + m_mark_count;
   this->finalize(p1, p2);
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_all()
{
   bool result = true;
   while(result && (m_position != m_end))
   {
      result = (this->*m_parser_proc)();
   }
   return result;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_basic()
{
   switch(this->m_traits.syntax_type(*m_position))
   {
   case regex_constants::syntax_escape:
      return parse_basic_escape();
   case regex_constants::syntax_dot:
      return parse_match_any();
   case regex_constants::syntax_caret:
      ++m_position;
      this->append_state(syntax_element_start_line);
      break;
   case regex_constants::syntax_dollar:
      ++m_position;
      this->append_state(syntax_element_end_line);
      break;
   case regex_constants::syntax_star:
      if(!(this->m_last_state) || (this->m_last_state->type == syntax_element_start_line))
         return parse_literal();
      else
      {
         ++m_position;
         return parse_repeat();
      }
   case regex_constants::syntax_plus:
      if(!(this->m_last_state) || (this->m_last_state->type == syntax_element_start_line) || !(this->flags() & regbase::emacs_ex))
         return parse_literal();
      else
      {
         ++m_position;
         return parse_repeat(1);
      }
   case regex_constants::syntax_question:
      if(!(this->m_last_state) || (this->m_last_state->type == syntax_element_start_line) || !(this->flags() & regbase::emacs_ex))
         return parse_literal();
      else
      {
         ++m_position;
         return parse_repeat(0, 1);
      }
   case regex_constants::syntax_open_set:
      return parse_set();
   case regex_constants::syntax_newline:
      if(this->flags() & regbase::newline_alt)
         return parse_alt();
      else
         return parse_literal();
   default:
      return parse_literal();
   }
   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_extended()
{
   bool result = true;
   switch(this->m_traits.syntax_type(*m_position))
   {
   case regex_constants::syntax_open_mark:
      return parse_open_paren();
   case regex_constants::syntax_close_mark:
      return false;
   case regex_constants::syntax_escape:
      return parse_extended_escape();
   case regex_constants::syntax_dot:
      return parse_match_any();
   case regex_constants::syntax_caret:
      ++m_position;
      this->append_state(
         (this->flags() & regex_constants::no_mod_m ? syntax_element_buffer_start : syntax_element_start_line));
      break;
   case regex_constants::syntax_dollar:
      ++m_position;
      this->append_state(
         (this->flags() & regex_constants::no_mod_m ? syntax_element_buffer_end : syntax_element_end_line));
      break;
   case regex_constants::syntax_star:
      if(m_position == this->m_base)
      {
         fail(regex_constants::error_badrepeat, 0, "The repeat operator \"*\" cannot start a regular expression.");
         return false;
      }
      ++m_position;
      return parse_repeat();
   case regex_constants::syntax_question:
      if(m_position == this->m_base)
      {
         fail(regex_constants::error_badrepeat, 0, "The repeat operator \"?\" cannot start a regular expression.");
         return false;
      }
      ++m_position;
      return parse_repeat(0,1);
   case regex_constants::syntax_plus:
      if(m_position == this->m_base)
      {
         fail(regex_constants::error_badrepeat, 0, "The repeat operator \"+\" cannot start a regular expression.");
         return false;
      }
      ++m_position;
      return parse_repeat(1);
   case regex_constants::syntax_open_brace:
      ++m_position;
      return parse_repeat_range(false);
   case regex_constants::syntax_close_brace:
      fail(regex_constants::error_brace, this->m_position - this->m_base, "Found a closing repetition operator } with no corresponding {.");
      return false;
   case regex_constants::syntax_or:
      return parse_alt();
   case regex_constants::syntax_open_set:
      return parse_set();
   case regex_constants::syntax_newline:
      if(this->flags() & regbase::newline_alt)
         return parse_alt();
      else
         return parse_literal();
   case regex_constants::syntax_hash:
      //
      // If we have a mod_x flag set, then skip until
      // we get to a newline character:
      //
      if((this->flags() 
         & (regbase::no_perl_ex|regbase::mod_x))
         == regbase::mod_x)
      {
         while((m_position != m_end) && !is_separator(*m_position++)){}
         return true;
      }
      BOOST_FALLTHROUGH;
   default:
      result = parse_literal();
      break;
   }
   return result;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_literal()
{
   // append this as a literal provided it's not a space character
   // or the perl option regbase::mod_x is not set:
   if(
      ((this->flags() 
         & (regbase::main_option_type|regbase::mod_x|regbase::no_perl_ex)) 
            != regbase::mod_x)
      || !this->m_traits.isctype(*m_position, this->m_mask_space))
         this->append_literal(*m_position);
   ++m_position;
   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_open_paren()
{
   //
   // skip the '(' and error check:
   //
   if(++m_position == m_end)
   {
      fail(regex_constants::error_paren, m_position - m_base);
      return false;
   }
   //
   // begin by checking for a perl-style (?...) extension:
   //
   if(
         ((this->flags() & (regbase::main_option_type | regbase::no_perl_ex)) == 0)
         || ((this->flags() & (regbase::main_option_type | regbase::emacs_ex)) == (regbase::basic_syntax_group|regbase::emacs_ex))
     )
   {
      if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_question)
         return parse_perl_extension();
   }
   //
   // update our mark count, and append the required state:
   //
   unsigned markid = 0;
   if(0 == (this->flags() & regbase::nosubs))
   {
      markid = ++m_mark_count;
#ifndef BOOST_NO_STD_DISTANCE
      if(this->flags() & regbase::save_subexpression_location)
         this->m_pdata->m_subs.push_back(std::pair<std::size_t, std::size_t>(std::distance(m_base, m_position) - 1, 0));
#else
      if(this->flags() & regbase::save_subexpression_location)
         this->m_pdata->m_subs.push_back(std::pair<std::size_t, std::size_t>((m_position - m_base) - 1, 0));
#endif
   }
   re_brace* pb = static_cast<re_brace*>(this->append_state(syntax_element_startmark, sizeof(re_brace)));
   pb->index = markid;
   pb->icase = this->flags() & regbase::icase;
   std::ptrdiff_t last_paren_start = this->getoffset(pb);
   // back up insertion point for alternations, and set new point:
   std::ptrdiff_t last_alt_point = m_alt_insert_point;
   this->m_pdata->m_data.align();
   m_alt_insert_point = this->m_pdata->m_data.size();
   //
   // back up the current flags in case we have a nested (?imsx) group:
   //
   regex_constants::syntax_option_type opts = this->flags();
   bool old_case_change = m_has_case_change;
   m_has_case_change = false; // no changes to this scope as yet...
   //
   // Back up branch reset data in case we have a nested (?|...)
   //
   int mark_reset = m_mark_reset;
   m_mark_reset = -1;
   //
   // now recursively add more states, this will terminate when we get to a
   // matching ')' :
   //
   parse_all();
   //
   // Unwind pushed alternatives:
   //
   if(0 == unwind_alts(last_paren_start))
      return false;
   //
   // restore flags:
   //
   if(m_has_case_change)
   {
      // the case has changed in one or more of the alternatives
      // within the scoped (...) block: we have to add a state
      // to reset the case sensitivity:
      static_cast<re_case*>(
         this->append_state(syntax_element_toggle_case, sizeof(re_case))
         )->icase = opts & regbase::icase;
   }
   this->flags(opts);
   m_has_case_change = old_case_change;
   //
   // restore branch reset:
   //
   m_mark_reset = mark_reset;
   //
   // we either have a ')' or we have run out of characters prematurely:
   //
   if(m_position == m_end)
   {
      this->fail(regex_constants::error_paren, ::boost::re_detail::distance(m_base, m_end));
      return false;
   }
   BOOST_ASSERT(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_close_mark);
#ifndef BOOST_NO_STD_DISTANCE
   if(markid && (this->flags() & regbase::save_subexpression_location))
      this->m_pdata->m_subs.at(markid - 1).second = std::distance(m_base, m_position);
#else
   if(markid && (this->flags() & regbase::save_subexpression_location))
      this->m_pdata->m_subs.at(markid - 1).second = (m_position - m_base);
#endif
   ++m_position;
   //
   // append closing parenthesis state:
   //
   pb = static_cast<re_brace*>(this->append_state(syntax_element_endmark, sizeof(re_brace)));
   pb->index = markid;
   pb->icase = this->flags() & regbase::icase;
   this->m_paren_start = last_paren_start;
   //
   // restore the alternate insertion point:
   //
   this->m_alt_insert_point = last_alt_point;
   //
   // allow backrefs to this mark:
   //
   if((markid > 0) && (markid < sizeof(unsigned) * CHAR_BIT))
      this->m_backrefs |= 1u << (markid - 1);

   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_basic_escape()
{
   ++m_position;
   bool result = true;
   switch(this->m_traits.escape_syntax_type(*m_position))
   {
   case regex_constants::syntax_open_mark:
      return parse_open_paren();
   case regex_constants::syntax_close_mark:
      return false;
   case regex_constants::syntax_plus:
      if(this->flags() & regex_constants::bk_plus_qm)
      {
         ++m_position;
         return parse_repeat(1);
      }
      else
         return parse_literal();
   case regex_constants::syntax_question:
      if(this->flags() & regex_constants::bk_plus_qm)
      {
         ++m_position;
         return parse_repeat(0, 1);
      }
      else
         return parse_literal();
   case regex_constants::syntax_open_brace:
      if(this->flags() & regbase::no_intervals)
         return parse_literal();
      ++m_position;
      return parse_repeat_range(true);
   case regex_constants::syntax_close_brace:
      if(this->flags() & regbase::no_intervals)
         return parse_literal();
      fail(regex_constants::error_brace, this->m_position - this->m_base, "Found a closing repetition operator } with no corresponding {.");
      return false;
   case regex_constants::syntax_or:
      if(this->flags() & regbase::bk_vbar)
         return parse_alt();
      else
         result = parse_literal();
      break;
   case regex_constants::syntax_digit:
      return parse_backref();
   case regex_constants::escape_type_start_buffer:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_buffer_start);
      }
      else
         result = parse_literal();
      break;
   case regex_constants::escape_type_end_buffer:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_buffer_end);
      }
      else
         result = parse_literal();
      break;
   case regex_constants::escape_type_word_assert:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_word_boundary);
      }
      else
         result = parse_literal();
      break;
   case regex_constants::escape_type_not_word_assert:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_within_word);
      }
      else
         result = parse_literal();
      break;
   case regex_constants::escape_type_left_word:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_word_start);
      }
      else
         result = parse_literal();
      break;
   case regex_constants::escape_type_right_word:
      if(this->flags() & regbase::emacs_ex)
      {
         ++m_position;
         this->append_state(syntax_element_word_end);
      }
      else
         result = parse_literal();
      break;
   default:
      if(this->flags() & regbase::emacs_ex)
      {
         bool negate = true;
         switch(*m_position)
         {
         case 'w':
            negate = false;
            BOOST_FALLTHROUGH;
         case 'W':
            {
            basic_char_set<charT, traits> char_set;
            if(negate)
               char_set.negate();
            char_set.add_class(this->m_word_mask);
            if(0 == this->append_set(char_set))
            {
               fail(regex_constants::error_ctype, m_position - m_base);
               return false;
            }
            ++m_position;
            return true;
            }
         case 's':
            negate = false;
            BOOST_FALLTHROUGH;
         case 'S':
            return add_emacs_code(negate);
         case 'c':
         case 'C':
            // not supported yet:
            fail(regex_constants::error_escape, m_position - m_base, "The \\c and \\C escape sequences are not supported by POSIX basic regular expressions: try the Perl syntax instead.");
            return false;
         default:
            break;
         }
      }
      result = parse_literal();
      break;
   }
   return result;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_extended_escape()
{
   ++m_position;
   if(m_position == m_end)
   {
      fail(regex_constants::error_escape, m_position - m_base, "Incomplete escape sequence found.");
      return false;
   }
   bool negate = false; // in case this is a character class escape: \w \d etc
   switch(this->m_traits.escape_syntax_type(*m_position))
   {
   case regex_constants::escape_type_not_class:
      negate = true;
      BOOST_FALLTHROUGH;
   case regex_constants::escape_type_class:
      {
escape_type_class_jump:
         typedef typename traits::char_class_type m_type;
         m_type m = this->m_traits.lookup_classname(m_position, m_position+1);
         if(m != 0)
         {
            basic_char_set<charT, traits> char_set;
            if(negate)
               char_set.negate();
            char_set.add_class(m);
            if(0 == this->append_set(char_set))
            {
               fail(regex_constants::error_ctype, m_position - m_base);
               return false;
            }
            ++m_position;
            return true;
         }
         //
         // not a class, just a regular unknown escape:
         //
         this->append_literal(unescape_character());
         break;
      }
   case regex_constants::syntax_digit:
      return parse_backref();
   case regex_constants::escape_type_left_word:
      ++m_position;
      this->append_state(syntax_element_word_start);
      break;
   case regex_constants::escape_type_right_word:
      ++m_position;
      this->append_state(syntax_element_word_end);
      break;
   case regex_constants::escape_type_start_buffer:
      ++m_position;
      this->append_state(syntax_element_buffer_start);
      break;
   case regex_constants::escape_type_end_buffer:
      ++m_position;
      this->append_state(syntax_element_buffer_end);
      break;
   case regex_constants::escape_type_word_assert:
      ++m_position;
      this->append_state(syntax_element_word_boundary);
      break;
   case regex_constants::escape_type_not_word_assert:
      ++m_position;
      this->append_state(syntax_element_within_word);
      break;
   case regex_constants::escape_type_Z:
      ++m_position;
      this->append_state(syntax_element_soft_buffer_end);
      break;
   case regex_constants::escape_type_Q:
      return parse_QE();
   case regex_constants::escape_type_C:
      return parse_match_any();
   case regex_constants::escape_type_X:
      ++m_position;
      this->append_state(syntax_element_combining);
      break;
   case regex_constants::escape_type_G:
      ++m_position;
      this->append_state(syntax_element_restart_continue);
      break;
   case regex_constants::escape_type_not_property:
      negate = true;
      BOOST_FALLTHROUGH;
   case regex_constants::escape_type_property:
      {
         ++m_position;
         char_class_type m;
         if(m_position == m_end)
         {
            fail(regex_constants::error_escape, m_position - m_base, "Incomplete property escape found.");
            return false;
         }
         // maybe have \p{ddd}
         if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_open_brace)
         {
            const charT* base = m_position;
            // skip forward until we find enclosing brace:
            while((m_position != m_end) && (this->m_traits.syntax_type(*m_position) != regex_constants::syntax_close_brace))
               ++m_position;
            if(m_position == m_end)
            {
               fail(regex_constants::error_escape, m_position - m_base, "Closing } missing from property escape sequence.");
               return false;
            }
            m = this->m_traits.lookup_classname(++base, m_position++);
         }
         else
         {
            m = this->m_traits.lookup_classname(m_position, m_position+1);
            ++m_position;
         }
         if(m != 0)
         {
            basic_char_set<charT, traits> char_set;
            if(negate)
               char_set.negate();
            char_set.add_class(m);
            if(0 == this->append_set(char_set))
            {
               fail(regex_constants::error_ctype, m_position - m_base);
               return false;
            }
            return true;
         }
         fail(regex_constants::error_ctype, m_position - m_base, "Escape sequence was neither a valid property nor a valid character class name.");
         return false;
      }
   case regex_constants::escape_type_reset_start_mark:
      if(0 == (this->flags() & (regbase::main_option_type | regbase::no_perl_ex)))
      {
         re_brace* pb = static_cast<re_brace*>(this->append_state(syntax_element_startmark, sizeof(re_brace)));
         pb->index = -5;
         pb->icase = this->flags() & regbase::icase;
         this->m_pdata->m_data.align();
         ++m_position;
         return true;
      }
      goto escape_type_class_jump;
   case regex_constants::escape_type_line_ending:
      if(0 == (this->flags() & (regbase::main_option_type | regbase::no_perl_ex)))
      {
         const charT* e = get_escape_R_string<charT>();
         const charT* old_position = m_position;
         const charT* old_end = m_end;
         const charT* old_base = m_base;
         m_position = e;
         m_base = e;
         m_end = e + traits::length(e);
         bool r = parse_all();
         m_position = ++old_position;
         m_end = old_end;
         m_base = old_base;
         return r;
      }
      goto escape_type_class_jump;
   case regex_constants::escape_type_extended_backref:
      if(0 == (this->flags() & (regbase::main_option_type | regbase::no_perl_ex)))
      {
         bool have_brace = false;
         bool negative = false;
         static const char* incomplete_message = "Incomplete \\g escape found.";
         if(++m_position == m_end)
         {
            fail(regex_constants::error_escape, m_position - m_base, incomplete_message);
            return false;
         }
         // maybe have \g{ddd}
         regex_constants::syntax_type syn = this->m_traits.syntax_type(*m_position);
         regex_constants::syntax_type syn_end = 0;
         if((syn == regex_constants::syntax_open_brace) 
            || (syn == regex_constants::escape_type_left_word)
            || (syn == regex_constants::escape_type_end_buffer))
         {
            if(++m_position == m_end)
            {
               fail(regex_constants::error_escape, m_position - m_base, incomplete_message);
               return false;
            }
            have_brace = true;
            switch(syn)
            {
            case regex_constants::syntax_open_brace:
               syn_end = regex_constants::syntax_close_brace;
               break;
            case regex_constants::escape_type_left_word:
               syn_end = regex_constants::escape_type_right_word;
               break;
            default:
               syn_end = regex_constants::escape_type_end_buffer;
               break;
            }
         }
         negative = (*m_position == static_cast<charT>('-'));
         if((negative) && (++m_position == m_end))
         {
            fail(regex_constants::error_escape, m_position - m_base, incomplete_message);
            return false;
         }
         const charT* pc = m_position;
         int i = this->m_traits.toi(pc, m_end, 10);
         if((i < 0) && syn_end)
         {
            // Check for a named capture, get the leftmost one if there is more than one:
            const charT* base = m_position;
            while((m_position != m_end) && (this->m_traits.syntax_type(*m_position) != syn_end))
            {
               ++m_position;
            }
            i = hash_value_from_capture_name(base, m_position);
            pc = m_position;
         }
         if(negative)
            i = 1 + m_mark_count - i;
         if(((i > 0) && (this->m_backrefs & (1u << (i-1)))) || ((i > 10000) && (this->m_pdata->get_id(i) > 0) && (this->m_backrefs & (1u << (this->m_pdata->get_id(i)-1)))))
         {
            m_position = pc;
            re_brace* pb = static_cast<re_brace*>(this->append_state(syntax_element_backref, sizeof(re_brace)));
            pb->index = i;
            pb->icase = this->flags() & regbase::icase;
         }
         else
         {
            fail(regex_constants::error_backref, m_position - m_base);
            return false;
         }
         m_position = pc;
         if(have_brace)
         {
            if((m_position == m_end) || (this->m_traits.syntax_type(*m_position) != syn_end))
            {
               fail(regex_constants::error_escape, m_position - m_base, incomplete_message);
               return false;
            }
            ++m_position;
         }
         return true;
      }
      goto escape_type_class_jump;
   case regex_constants::escape_type_control_v:
      if(0 == (this->flags() & (regbase::main_option_type | regbase::no_perl_ex)))
         goto escape_type_class_jump;
      BOOST_FALLTHROUGH;
   default:
      this->append_literal(unescape_character());
      break;
   }
   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_match_any()
{
   //
   // we have a '.' that can match any character:
   //
   ++m_position;
   static_cast<re_dot*>(
      this->append_state(syntax_element_wild, sizeof(re_dot))
      )->mask = static_cast<unsigned char>(this->flags() & regbase::no_mod_s 
      ? re_detail::force_not_newline 
         : this->flags() & regbase::mod_s ?
            re_detail::force_newline : re_detail::dont_care);
   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_repeat_range(bool isbasic)
{
   static const char* incomplete_message = "Missing } in quantified repetition.";
   //
   // parse a repeat-range:
   //
   std::size_t min, max;
   int v;
   // skip whitespace:
   while((m_position != m_end) && this->m_traits.isctype(*m_position, this->m_mask_space))
      ++m_position;
   if(this->m_position == this->m_end)
   {
      if(this->flags() & (regbase::main_option_type | regbase::no_perl_ex))
      {
         fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
         return false;
      }
      // Treat the opening '{' as a literal character, rewind to start of error:
      --m_position;
      while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
      return parse_literal();
   }
   // get min:
   v = this->m_traits.toi(m_position, m_end, 10);
   // skip whitespace:
   if(v < 0)
   {
      if(this->flags() & (regbase::main_option_type | regbase::no_perl_ex))
      {
         fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
         return false;
      }
      // Treat the opening '{' as a literal character, rewind to start of error:
      --m_position;
      while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
      return parse_literal();
   }
   while((m_position != m_end) && this->m_traits.isctype(*m_position, this->m_mask_space))
      ++m_position;
   if(this->m_position == this->m_end)
   {
      if(this->flags() & (regbase::main_option_type | regbase::no_perl_ex))
      {
         fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
         return false;
      }
      // Treat the opening '{' as a literal character, rewind to start of error:
      --m_position;
      while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
      return parse_literal();
   }
   min = v;
   // see if we have a comma:
   if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_comma)
   {
      // move on and error check:
      ++m_position;
      // skip whitespace:
      while((m_position != m_end) && this->m_traits.isctype(*m_position, this->m_mask_space))
         ++m_position;
      if(this->m_position == this->m_end)
      {
         if(this->flags() & (regbase::main_option_type | regbase::no_perl_ex))
         {
            fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
            return false;
         }
         // Treat the opening '{' as a literal character, rewind to start of error:
         --m_position;
         while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
         return parse_literal();
      }
      // get the value if any:
      v = this->m_traits.toi(m_position, m_end, 10);
      max = (v >= 0) ? (std::size_t)v : (std::numeric_limits<std::size_t>::max)();
   }
   else
   {
      // no comma, max = min:
      max = min;
   }
   // skip whitespace:
   while((m_position != m_end) && this->m_traits.isctype(*m_position, this->m_mask_space))
      ++m_position;
   // OK now check trailing }:
   if(this->m_position == this->m_end)
   {
      if(this->flags() & (regbase::main_option_type | regbase::no_perl_ex))
      {
         fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
         return false;
      }
      // Treat the opening '{' as a literal character, rewind to start of error:
      --m_position;
      while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
      return parse_literal();
   }
   if(isbasic)
   {
      if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_escape)
      {
         ++m_position;
         if(this->m_position == this->m_end)
         {
            fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
            return false;
         }
      }
      else
      {
         fail(regex_constants::error_brace, this->m_position - this->m_base, incomplete_message);
         return false;
      }
   }
   if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_close_brace)
      ++m_position;
   else
   {
      // Treat the opening '{' as a literal character, rewind to start of error:
      --m_position;
      while(this->m_traits.syntax_type(*m_position) != regex_constants::syntax_open_brace) --m_position;
      return parse_literal();
   }
   //
   // finally go and add the repeat, unless error:
   //
   if(min > max)
   {
      // Backtrack to error location:
      m_position -= 2;
      while(this->m_traits.isctype(*m_position, this->m_word_mask)) --m_position;
         ++m_position;
      fail(regex_constants::error_badbrace, m_position - m_base);
      return false;
   }
   return parse_repeat(min, max);
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_alt()
{
   //
   // error check: if there have been no previous states,
   // or if the last state was a '(' then error:
   //
   if(
      ((this->m_last_state == 0) || (this->m_last_state->type == syntax_element_startmark))
      &&
      !(
         ((this->flags() & regbase::main_option_type) == regbase::perl_syntax_group)
           &&
         ((this->flags() & regbase::no_empty_expressions) == 0)
        )
      )
   {
      fail(regex_constants::error_empty, this->m_position - this->m_base, "A regular expression can start with the alternation operator |.");
      return false;
   }
   //
   // Reset mark count if required:
   //
   if(m_max_mark < m_mark_count)
      m_max_mark = m_mark_count;
   if(m_mark_reset >= 0)
      m_mark_count = m_mark_reset;

   ++m_position;
   //
   // we need to append a trailing jump: 
   //
   re_syntax_base* pj = this->append_state(re_detail::syntax_element_jump, sizeof(re_jump));
   std::ptrdiff_t jump_offset = this->getoffset(pj);
   //
   // now insert the alternative:
   //
   re_alt* palt = static_cast<re_alt*>(this->insert_state(this->m_alt_insert_point, syntax_element_alt, re_alt_size));
   jump_offset += re_alt_size;
   this->m_pdata->m_data.align();
   palt->alt.i = this->m_pdata->m_data.size() - this->getoffset(palt);
   //
   // update m_alt_insert_point so that the next alternate gets
   // inserted at the start of the second of the two we've just created:
   //
   this->m_alt_insert_point = this->m_pdata->m_data.size();
   //
   // the start of this alternative must have a case changes state
   // if the current block has messed around with case changes:
   //
   if(m_has_case_change)
   {
      static_cast<re_case*>(
         this->append_state(syntax_element_toggle_case, sizeof(re_case))
         )->icase = this->m_icase;
   }
   //
   // push the alternative onto our stack, a recursive
   // implementation here is easier to understand (and faster
   // as it happens), but causes all kinds of stack overflow problems
   // on programs with small stacks (COM+).
   //
   m_alt_jumps.push_back(jump_offset);
   return true;
}


template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_set()
{
   static const char* incomplete_message = "Character set declaration starting with [ terminated prematurely - either no ] was found or the set had no content.";
   ++m_position;
   if(m_position == m_end)
   {
      fail(regex_constants::error_brack, m_position - m_base, incomplete_message);
      return false;
   }
   basic_char_set<charT, traits> char_set;

   const charT* base = m_position;  // where the '[' was
   const charT* item_base = m_position;  // where the '[' or '^' was

   while(m_position != m_end)
   {
      switch(this->m_traits.syntax_type(*m_position))
      {
      case regex_constants::syntax_caret:
         if(m_position == base)
         {
            char_set.negate();
            ++m_position;
            item_base = m_position;
         }
         else
            parse_set_literal(char_set);
         break;
      case regex_constants::syntax_close_set:
         if(m_position == item_base)
         {
            parse_set_literal(char_set);
            break;
         }
         else
         {
            ++m_position;
            if(0 == this->append_set(char_set))
            {
               fail(regex_constants::error_ctype, m_position - m_base);
               return false;
            }
         }
         return true;
      case regex_constants::syntax_open_set:
         if(parse_inner_set(char_set))
            break;
         return true;
      case regex_constants::syntax_escape:
         {
            // 
            // look ahead and see if this is a character class shortcut
            // \d \w \s etc...
            //
            ++m_position;
            if(this->m_traits.escape_syntax_type(*m_position)
               == regex_constants::escape_type_class)
            {
               char_class_type m = this->m_traits.lookup_classname(m_position, m_position+1);
               if(m != 0)
               {
                  char_set.add_class(m);
                  ++m_position;
                  break;
               }
            }
            else if(this->m_traits.escape_syntax_type(*m_position)
               == regex_constants::escape_type_not_class)
            {
               // negated character class:
               char_class_type m = this->m_traits.lookup_classname(m_position, m_position+1);
               if(m != 0)
               {
                  char_set.add_negated_class(m);
                  ++m_position;
                  break;
               }
            }
            // not a character class, just a regular escape:
            --m_position;
            parse_set_literal(char_set);
            break;
         }
      default:
         parse_set_literal(char_set);
         break;
      }
   }
   return m_position != m_end;
}


template <class BidiIterator, class Allocator, class charT, class traits>
bool regex_search(BidiIterator first, BidiIterator last, 
                  match_results<BidiIterator, Allocator>& m, 
                  const basic_regex<charT, traits>& e, 
                  match_flag_type flags = match_default)
{
   return regex_search(first, last, m, e, flags, first);
}

inline bool operator < (const file_iterator&, const file_iterator&)
{
   return false;
}

template <class Predicate, class BidiIterator, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, 
                               BidiIterator first, 
                               BidiIterator last, 
                               const basic_regex<charT, traits>& e, 
                               match_flag_type flags = match_default)
{
   if(e.flags() & regex_constants::failbit)
      return false;

   typedef typename match_results<BidiIterator>::allocator_type match_allocator_type;

   match_results<BidiIterator> m;
   re_detail::perl_matcher<BidiIterator, match_allocator_type, traits> matcher(first, last, m, e, flags, first);
   unsigned int count = 0;
   while(matcher.find())
   {
      ++count;
      if(0 == foo(m))
         return count; // caller doesn't want to go on
      if(m[0].second == last)
         return count; // we've reached the end, don't try and find an extra null match.
      if(m.length() == 0)
      {
         if(m[0].second == last)
            return count;
         // we found a NULL-match, now try to find
         // a non-NULL one at the same position:
         match_results<BidiIterator, match_allocator_type> m2(m);
         matcher.setf(match_not_null | match_continuous);
         if(matcher.find())
         {
            ++count;
            if(0 == foo(m))
               return count;
         }
         else
         {
            // reset match back to where it was:
            m = m2;
         }
         matcher.unsetf((match_not_null | match_continuous) & ~flags);
      }
   }
   return count;
}

template <class BidiIterator, class Allocator, class charT, class traits>
bool regex_match(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   re_detail::perl_matcher<BidiIterator, Allocator, traits> matcher(first, last, m, e, flags, first);
   return matcher.match();
}

template <class charT>
inline bool can_start(charT c, const unsigned char* map, unsigned char mask)
{
   return ((c < static_cast<charT>(0)) ? true : ((c >= static_cast<charT>(1 << CHAR_BIT)) ? true : map[c] & mask));
}

inline bool can_start(char c, const unsigned char* map, unsigned char mask)
{
   return map[(unsigned char)c] & mask;
}

inline bool can_start(signed char c, const unsigned char* map, unsigned char mask)
{
   return map[(unsigned char)c] & mask;
}

inline bool can_start(unsigned char c, const unsigned char* map, unsigned char mask)
{
   return map[c] & mask;
}

inline bool can_start(unsigned short c, const unsigned char* map, unsigned char mask)
{
   return ((c >= (1 << CHAR_BIT)) ? true : map[c] & mask);
}

inline bool can_start(unsigned int c, const unsigned char* map, unsigned char mask)
{
   return (((c >= static_cast<unsigned int>(1u << CHAR_BIT)) ? true : map[c] & mask));
}

template <class Seq, class C>
inline int string_compare(const Seq& s, const C* p)
{
   std::size_t i = 0;
   while((i < s.size()) && (p[i] == s[i]))
   {
      ++i;
   }
   return (i == s.size()) ? -p[i] : s[i] - p[i];
}


template<class charT>
inline const charT* re_skip_past_null(const charT* p)
{
  while (*p != static_cast<charT>(0)) ++p;
  return ++p;
}
 re_is_set_member(iterator next, 
                          iterator last, 
                          const re_set_long<char_classT>* set_, 
                          const regex_data<charT, traits_type>& e, bool icase)
{   
   const charT* p = reinterpret_cast<const charT*>(set_+1);
   iterator ptr;
   unsigned int i;
   //bool icase = e.m_flags & regex_constants::icase;

   if(next == last) return next;

   typedef typename traits_type::string_type traits_string_type;
   const ::boost::regex_traits_wrapper<traits_type>& traits_inst = *(e.m_ptraits);
   
   // dwa 9/13/00 suppress incorrect MSVC warning - it claims this is never
   // referenced
   (void)traits_inst;

   // try and match a single character, could be a multi-character
   // collating element...
   for(i = 0; i < set_->csingles; ++i)
   {
      ptr = next;
      if(*p == static_cast<charT>(0))
      {
         // treat null string as special case:
         if(traits_inst.translate(*ptr, icase) != *p)
         {
            while(*p == static_cast<charT>(0))++p;
            continue;
         }
         return set_->isnot ? next : (ptr == next) ? ++next : ptr;
      }
      else
      {
         while(*p && (ptr != last))
         {
            if(traits_inst.translate(*ptr, icase) != *p)
               break;
            ++p;
            ++ptr;
         }

         if(*p == static_cast<charT>(0)) // if null we've matched
            return set_->isnot ? next : (ptr == next) ? ++next : ptr;

         p = re_skip_past_null(p);     // skip null
      }
   }

   charT col = traits_inst.translate(*next, icase);


   if(set_->cranges || set_->cequivalents)
   {
      traits_string_type s1;
      //
      // try and match a range, NB only a single character can match
      if(set_->cranges)
      {
         if((e.m_flags & regex_constants::collate) == 0)
            s1.assign(1, col);
         else
         {
            charT a[2] = { col, charT(0), };
            s1 = traits_inst.transform(a, a + 1);
         }
         for(i = 0; i < set_->cranges; ++i)
         {
            if(STR_COMP(s1, p) >= 0)
            {
               do{ ++p; }while(*p);
               ++p;
               if(STR_COMP(s1, p) <= 0)
                  return set_->isnot ? next : ++next;
            }
            else
            {
               // skip first string
               do{ ++p; }while(*p);
               ++p;
            }
            // skip second string
            do{ ++p; }while(*p);
            ++p;
         }
      }
      //
      // try and match an equivalence class, NB only a single character can match
      if(set_->cequivalents)
      {
         charT a[2] = { col, charT(0), };
         s1 = traits_inst.transform_primary(a, a +1);
         for(i = 0; i < set_->cequivalents; ++i)
         {
            if(STR_COMP(s1, p) == 0)
               return set_->isnot ? next : ++next;
            // skip string
            do{ ++p; }while(*p);
            ++p;
         }
      }
   }
   if(traits_inst.isctype(col, set_->cclasses) == true)
      return set_->isnot ? next : ++next;
   if((set_->cnclasses != 0) && (traits_inst.isctype(col, set_->cnclasses) == false))
      return set_->isnot ? next : ++next;
   return set_->isnot ? ++next : next;
}

   repeater_count(repeater_count** s)
   {
      stack = s;
      next = 0;
      state_id = -1;
      count = 0;
   }

   repeater_count(int i, repeater_count** s, BidiIterator start)
      : start_pos(start)
   {
      state_id = i;
      stack = s;
      next = *stack;
      *stack = this;
      if(state_id > next->state_id)
         count = 0;
      else
      {
         repeater_count* p = next;
         while(p && (p->state_id != state_id))
            p = p->next;
         if(p)
         {
            count = p->count;
            start_pos = p->start_pos;
         }
         else
            count = 0;
      }
   }

   ~repeater_count()
   {
      if(next)
         *stack = next;
   }

   std::size_t get_count() { return count; }

   int get_id() { return state_id; }

   std::size_t operator++() { return ++count; }

   bool check_null_repeat(const BidiIterator& pos, std::size_t max)
   {
      // this is called when we are about to start a new repeat,
      // if the last one was NULL move our count to max,
      // otherwise save the current position.
      bool result = (count == 0) ? false : (pos == start_pos);
      if(result)
         count = max;
      else
         start_pos = pos;
      return result;
   }


   perl_matcher(BidiIterator first, BidiIterator end, 
      match_results<BidiIterator, Allocator>& what, 
      const basic_regex<char_type, traits>& e,
      match_flag_type f,
      BidiIterator l_base)
      :  m_result(what), base(first), last(end), 
         position(first), backstop(l_base), re(e), traits_inst(e.get_traits()), 
         m_independent(false), next_count(&rep_obj), rep_obj(&next_count)
   {
      construct_init(e, f);
   }


   void setf(match_flag_type f)
   { m_match_flags |= f; }

   void unsetf(match_flag_type f)
   { m_match_flags &= ~f; }

   bool match_dot_repeat_dispatch()
   {
      return ::boost::is_random_access_iterator<BidiIterator>::value ? match_dot_repeat_fast() : match_dot_repeat_slow();
   }

   perl_matcher& operator=(const perl_matcher&)
   {
      return *this;
   }

   perl_matcher(const perl_matcher& that)
      : m_result(that.m_result), re(that.re), traits_inst(that.traits_inst), rep_obj(0) {}


template <class I>
void bubble_down_one(I first, I last)
{
   if(first != last)
   {
      I next = last - 1;
      while((next != first) && (*next < *(next-1)))
      {
         (next-1)->swap(*next);
         --next;
      }
   }
}


template <class Iterator>
inline int hash_value_from_capture_name(Iterator i, Iterator j)
{
   std::size_t r = boost::hash_range(i, j);
   r %= ((std::numeric_limits<int>::max)() - 10001);
   r += 10000;
   return static_cast<int>(r);
}

      template <class charT>
      name(const charT* i, const charT* j, int idx)
         : index(idx) 
      { 
         hash = hash_value_from_capture_name(i, j); 
      }

      name(int h, int idx)
         : index(idx), hash(h)
      { 
      }

      bool operator < (const name& other)const
      {
         return hash < other.hash;
      }

      bool operator == (const name& other)const
      {
         return hash == other.hash; 
      }

      void swap(name& other)
      {
         std::swap(index, other.index);
         std::swap(hash, other.hash);
      }


   named_subexpressions(){}


   template <class charT>
   void set_name(const charT* i, const charT* j, int index)
   {
      m_sub_names.push_back(name(i, j, index));
      bubble_down_one(m_sub_names.begin(), m_sub_names.end());
   }

   template <class charT>
   int get_id(const charT* i, const charT* j)const
   {
      name t(i, j, 0);
      typename std::vector<name>::const_iterator pos = std::lower_bound(m_sub_names.begin(), m_sub_names.end(), t);
      if((pos != m_sub_names.end()) && (*pos == t))
      {
         return pos->index;
      }
      return -1;
   }

   template <class charT>
   range_type equal_range(const charT* i, const charT* j)const
   {
      name t(i, j, 0);
      return std::equal_range(m_sub_names.begin(), m_sub_names.end(), t);
   }

   int get_id(int h)const
   {
      name t(h, 0);
      std::vector<name>::const_iterator pos = std::lower_bound(m_sub_names.begin(), m_sub_names.end(), t);
      if((pos != m_sub_names.end()) && (*pos == t))
      {
         return pos->index;
      }
      return -1;
   }
  

   regex_data(const ::boost::shared_ptr<
      ::boost::regex_traits_wrapper<traits> >& t) 
      : m_ptraits(t), m_expression(0), m_expression_len(0) {}

   regex_data() 
      : m_ptraits(new ::boost::regex_traits_wrapper<traits>()), m_expression(0), m_expression_len(0) {}


   basic_regex_implementation(){}

   void assign(const charT* arg_first,
                          const charT* arg_last,
                          flag_type f)
   {
      regex_data<charT, traits>* pdat = this;
      basic_regex_parser<charT, traits> parser(pdat);
      parser.parse(arg_first, arg_last, f);
   }

   explicit basic_regex(){}

   explicit basic_regex(const charT* p, flag_type f = regex_constants::normal)
   {
      assign(p, f);
   }

   basic_regex(const charT* p1, const charT* p2, flag_type f = regex_constants::normal)
   {
      assign(p1, p2, f);
   }

   basic_regex(const charT* p, size_type len, flag_type f)
   {
      assign(p, len, f);
   }

   basic_regex(const basic_regex& that)
      : m_pimpl(that.m_pimpl) {}

   ~basic_regex(){}

   basic_regex& assign(const charT* p1,
                          const charT* p2,
                          flag_type f = regex_constants::normal)
   {
      return do_assign(p1, p2, f);
   }

template <class charT, class traits>
basic_regex<charT, traits>& basic_regex<charT, traits>::do_assign(const charT* p1,
                        const charT* p2,
                        flag_type f)
{
   shared_ptr<re_detail::basic_regex_implementation<charT, traits> > temp;
   if(!m_pimpl.get())
   {
      temp = shared_ptr<re_detail::basic_regex_implementation<charT, traits> >(new re_detail::basic_regex_implementation<charT, traits>());
   }
   else
   {
      temp = shared_ptr<re_detail::basic_regex_implementation<charT, traits> >(new re_detail::basic_regex_implementation<charT, traits>(m_pimpl->m_ptraits));
   }
   temp->assign(p1, p2, f);
   temp.swap(m_pimpl);
   return *this;
}
 basic_regex<charT, traits>::imbue(locale_type l)
{ 
   shared_ptr<re_detail::basic_regex_implementation<charT, traits> > temp(new re_detail::basic_regex_implementation<charT, traits>());
   locale_type result = temp->imbue(l);
   temp.swap(m_pimpl);
   return result;
}

template <class charT, class traits>
void swap(basic_regex<charT, traits>& e1, basic_regex<charT, traits>& e2)
{
   e1.swap(e2);
}


   static std::ptrdiff_t length(const charT* p)
   {
      return global_length(p);
   }

   static charT tolower(charT c)
   {
      return ::boost::re_detail::global_lower(c);
   }

   static charT toupper(charT c)
   {
      return ::boost::re_detail::global_upper(c);
   }

   static int value(const charT c, int radix)
   {
      int result = global_value(c);
      return result >= radix ? -1 : result;
   }

   int toi(const charT*& p1, const charT* p2, int radix)const
   {
      return global_toi(p1, p2, radix, *this);
   }

   basic_regex_formatter(OutputIterator o, const Results& r, const traits& t)
      : m_traits(t), m_results(r), m_out(o), m_state(output_copy), m_restore_state(output_copy), m_have_conditional(false) {}


   inline typename Results::value_type const& get_named_sub(ForwardIter i, ForwardIter j, const mpl::false_&)
   {
      std::vector<char_type> v(i, j);
      return (i != j) ? this->m_results.named_subexpression(&v[0], &v[0] + v.size())
         : this->m_results.named_subexpression(static_cast<const char_type*>(0), static_cast<const char_type*>(0));
   }

   inline typename Results::value_type const& get_named_sub(ForwardIter i, ForwardIter j)
   {
      typedef typename boost::is_convertible<ForwardIter, const char_type*>::type tag_type;
      return get_named_sub(i, j, tag_type());
   }

   inline int get_named_sub_index(ForwardIter i, ForwardIter j, const mpl::false_&)
   {
      std::vector<char_type> v(i, j);
      return (i != j) ? this->m_results.named_subexpression_index(&v[0], &v[0] + v.size())
         : this->m_results.named_subexpression_index(static_cast<const char_type*>(0), static_cast<const char_type*>(0));
   }

   inline int get_named_sub_index(ForwardIter i, ForwardIter j)
   {
      typedef typename boost::is_convertible<ForwardIter, const char_type*>::type tag_type;
      return get_named_sub_index(i, j, tag_type());
   }

   inline int toi(ForwardIter& i, ForwardIter j, int base, const boost::mpl::false_&)
   {
      if(i != j)
      {
         std::vector<char_type> v(i, j);
         const char_type* start = &v[0];
         const char_type* pos = start;
         int r = m_traits.toi(pos, &v[0] + v.size(), base);
         std::advance(i, pos - start);
         return r;
      }
      return -1;
   }

   inline int toi(ForwardIter& i, ForwardIter j, int base)
   {
#if defined(_MSC_VER) && defined(__INTEL_COMPILER) && ((__INTEL_COMPILER == 9999) || (__INTEL_COMPILER == 1210))
      // Workaround for Intel support issue #656654.
      // See also https://svn.boost.org/trac/boost/ticket/6359
      return toi(i, j, base, mpl::false_());
#else
      typedef typename boost::is_convertible<ForwardIter, const char_type*&>::type tag_type;
      return toi(i, j, base, tag_type());
#endif
   }


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_all()
{
   // over and over:
   while(m_position != m_end)
   {
      switch(*m_position)
      {
      case '&':
         if(m_flags & ::boost::regex_constants::format_sed)
         {
            ++m_position;
            put(m_results[0]);
            break;
         }
         put(*m_position++);
         break;
      case '\\':
         format_escape();
         break;
      case '(':
         if(m_flags & boost::regex_constants::format_all)
         {
            ++m_position;
            bool have_conditional = m_have_conditional;
            m_have_conditional = false;
            format_until_scope_end();
            m_have_conditional = have_conditional;
            if(m_position == m_end)
               return;
            BOOST_ASSERT(*m_position == static_cast<char_type>(')'));
            ++m_position;  // skip the closing ')'
            break;
         }
         put(*m_position);
         ++m_position;
         break;
      case ')':
         if(m_flags & boost::regex_constants::format_all)
         {
            return;
         }
         put(*m_position);
         ++m_position;
         break;
      case ':':
         if((m_flags & boost::regex_constants::format_all) && m_have_conditional)
         {
            return;
         }
         put(*m_position);
         ++m_position;
         break;
      case '?':
         if(m_flags & boost::regex_constants::format_all)
         {
            ++m_position;
            format_conditional();
            break;
         }
         put(*m_position);
         ++m_position;
         break;
      case '$':
         if((m_flags & format_sed) == 0)
         {
            format_perl();
            break;
         }
         // not a special character:
         BOOST_FALLTHROUGH;
      default:
         put(*m_position);
         ++m_position;
         break;
      }
   }
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_perl()
{
   //
   // On entry *m_position points to a '$' character
   // output the information that goes with it:
   //
   BOOST_ASSERT(*m_position == '$');
   //
   // see if this is a trailing '$':
   //
   if(++m_position == m_end)
   {
      --m_position;
      put(*m_position);
      ++m_position;
      return;
   }
   //
   // OK find out what kind it is:
   //
   bool have_brace = false;
   ForwardIter save_position = m_position;
   switch(*m_position)
   {
   case '&':
      ++m_position;
      put(this->m_results[0]);
      break;
   case '`':
      ++m_position;
      put(this->m_results.prefix());
      break;
   case '\'':
      ++m_position;
      put(this->m_results.suffix());
      break;
   case '$':
      put(*m_position++);
      break;
   case '+':
      if((++m_position != m_end) && (*m_position == '{'))
      {
         ForwardIter base = ++m_position;
         while((m_position != m_end) && (*m_position != '}')) ++m_position;
         if(m_position != m_end)
         {
            // Named sub-expression:
            put(get_named_sub(base, m_position));
            ++m_position;
            break;
         }
         else
         {
            m_position = --base;
         }
      }
      put((this->m_results)[this->m_results.size() > 1 ? static_cast<int>(this->m_results.size() - 1) : 1]);
      break;
   case '{':
      have_brace = true;
      ++m_position;
      BOOST_FALLTHROUGH;
   default:
      // see if we have a number:
      {
         std::ptrdiff_t len = ::boost::re_detail::distance(m_position, m_end);
         //len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
         int v = this->toi(m_position, m_position + len, 10);
         if((v < 0) || (have_brace && ((m_position == m_end) || (*m_position != '}'))))
         {
            // Look for a Perl-5.10 verb:
            if(!handle_perl_verb(have_brace))
            {
               // leave the $ as is, and carry on:
               m_position = --save_position;
               put(*m_position);
               ++m_position;
            }
            break;
         }
         // otherwise output sub v:
         put(this->m_results[v]);
         if(have_brace)
            ++m_position;
      }
   }
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
bool basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::handle_perl_verb(bool have_brace)
{
   // 
   // We may have a capitalised string containing a Perl action:
   //
   static const char_type MATCH[] = { 'M', 'A', 'T', 'C', 'H' };
   static const char_type PREMATCH[] = { 'P', 'R', 'E', 'M', 'A', 'T', 'C', 'H' };
   static const char_type POSTMATCH[] = { 'P', 'O', 'S', 'T', 'M', 'A', 'T', 'C', 'H' };
   static const char_type LAST_PAREN_MATCH[] = { 'L', 'A', 'S', 'T', '_', 'P', 'A', 'R', 'E', 'N', '_', 'M', 'A', 'T', 'C', 'H' };
   static const char_type LAST_SUBMATCH_RESULT[] = { 'L', 'A', 'S', 'T', '_', 'S', 'U', 'B', 'M', 'A', 'T', 'C', 'H', '_', 'R', 'E', 'S', 'U', 'L', 'T' };
   static const char_type LAST_SUBMATCH_RESULT_ALT[] = { '^', 'N' };

   if(m_position == m_end)
      return false;
   if(have_brace && (*m_position == '^'))
      ++m_position;

   std::ptrdiff_t max_len = m_end - m_position;

   if((max_len >= 5) && std::equal(m_position, m_position + 5, MATCH))
   {
      m_position += 5;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 5;
            return false;
         }
      }
      put(this->m_results[0]);
      return true;
   }
   if((max_len >= 8) && std::equal(m_position, m_position + 8, PREMATCH))
   {
      m_position += 8;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 8;
            return false;
         }
      }
      put(this->m_results.prefix());
      return true;
   }
   if((max_len >= 9) && std::equal(m_position, m_position + 9, POSTMATCH))
   {
      m_position += 9;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 9;
            return false;
         }
      }
      put(this->m_results.suffix());
      return true;
   }
   if((max_len >= 16) && std::equal(m_position, m_position + 16, LAST_PAREN_MATCH))
   {
      m_position += 16;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 16;
            return false;
         }
      }
      put((this->m_results)[this->m_results.size() > 1 ? static_cast<int>(this->m_results.size() - 1) : 1]);
      return true;
   }
   if((max_len >= 20) && std::equal(m_position, m_position + 20, LAST_SUBMATCH_RESULT))
   {
      m_position += 20;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 20;
            return false;
         }
      }
      put(this->m_results.get_last_closed_paren());
      return true;
   }
   if((max_len >= 2) && std::equal(m_position, m_position + 2, LAST_SUBMATCH_RESULT_ALT))
   {
      m_position += 2;
      if(have_brace)
      {
         if((m_position != m_end) && (*m_position == '}'))
            ++m_position;
         else
         {
            m_position -= 2;
            return false;
         }
      }
      put(this->m_results.get_last_closed_paren());
      return true;
   }
   return false;
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_escape()
{
   // skip the escape and check for trailing escape:
   if(++m_position == m_end)
   {
      put(static_cast<char_type>('\\'));
      return;
   }
   // now switch on the escape type:
   switch(*m_position)
   {
   case 'a':
      put(static_cast<char_type>('\a'));
      ++m_position;
      break;
   case 'f':
      put(static_cast<char_type>('\f'));
      ++m_position;
      break;
   case 'n':
      put(static_cast<char_type>('\n'));
      ++m_position;
      break;
   case 'r':
      put(static_cast<char_type>('\r'));
      ++m_position;
      break;
   case 't':
      put(static_cast<char_type>('\t'));
      ++m_position;
      break;
   case 'v':
      put(static_cast<char_type>('\v'));
      ++m_position;
      break;
   case 'x':
      if(++m_position == m_end)
      {
         put(static_cast<char_type>('x'));
         return;
      }
      // maybe have \x{ddd}
      if(*m_position == static_cast<char_type>('{'))
      {
         ++m_position;
         int val = this->toi(m_position, m_end, 16);
         if(val < 0)
         {
            // invalid value treat everything as literals:
            put(static_cast<char_type>('x'));
            put(static_cast<char_type>('{'));
            return;
         }
         if((m_position == m_end) || (*m_position != static_cast<char_type>('}')))
         {
            --m_position;
            while(*m_position != static_cast<char_type>('\\'))
               --m_position;
            ++m_position;
            put(*m_position++);
            return;
         }
         ++m_position;
         put(static_cast<char_type>(val));
         return;
      }
      else
      {
         std::ptrdiff_t len = ::boost::re_detail::distance(m_position, m_end);
         len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
         int val = this->toi(m_position, m_position + len, 16);
         if(val < 0)
         {
            --m_position;
            put(*m_position++);
            return;
         }
         put(static_cast<char_type>(val));
      }
      break;
   case 'c':
      if(++m_position == m_end)
      {
         --m_position;
         put(*m_position++);
         return;
      }
      put(static_cast<char_type>(*m_position++ % 32));
      break;
   case 'e':
      put(static_cast<char_type>(27));
      ++m_position;
      break;
   default:
      // see if we have a perl specific escape:
      if((m_flags & boost::regex_constants::format_sed) == 0)
      {
         bool breakout = false;
         switch(*m_position)
         {
         case 'l':
            ++m_position;
            m_restore_state = m_state;
            m_state = output_next_lower;
            breakout = true;
            break;
         case 'L':
            ++m_position;
            m_state = output_lower;
            breakout = true;
            break;
         case 'u':
            ++m_position;
            m_restore_state = m_state;
            m_state = output_next_upper;
            breakout = true;
            break;
         case 'U':
            ++m_position;
            m_state = output_upper;
            breakout = true;
            break;
         case 'E':
            ++m_position;
            m_state = output_copy;
            breakout = true;
            break;
         }
         if(breakout)
            break;
      }
      // see if we have a \n sed style backreference:
      std::ptrdiff_t len = ::boost::re_detail::distance(m_position, m_end);
      len = (std::min)(static_cast<std::ptrdiff_t>(1), len);
      int v = this->toi(m_position, m_position+len, 10);
      if((v > 0) || ((v == 0) && (m_flags & ::boost::regex_constants::format_sed)))
      {
         put(m_results[v]);
         break;
      }
      else if(v == 0)
      {
         // octal ecape sequence:
         --m_position;
         len = ::boost::re_detail::distance(m_position, m_end);
         len = (std::min)(static_cast<std::ptrdiff_t>(4), len);
         v = this->toi(m_position, m_position + len, 8);
         BOOST_ASSERT(v >= 0);
         put(static_cast<char_type>(v));
         break;
      }
      // Otherwise output the character "as is":
      put(*m_position++);
      break;
   }
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_conditional()
{
   if(m_position == m_end)
   {
      // oops trailing '?':
      put(static_cast<char_type>('?'));
      return;
   }
   int v;
   if(*m_position == '{')
   {
      ForwardIter base = m_position;
      ++m_position;
      v = this->toi(m_position, m_end, 10);
      if(v < 0)
      {
         // Try a named subexpression:
         while((m_position != m_end) && (*m_position != '}'))
            ++m_position;
         v = this->get_named_sub_index(base + 1, m_position);
      }
      if((v < 0) || (*m_position != '}'))
      {
         m_position = base;
         // oops trailing '?':
         put(static_cast<char_type>('?'));
         return;
      }
      // Skip trailing '}':
      ++m_position;
   }
   else
   {
      std::ptrdiff_t len = ::boost::re_detail::distance(m_position, m_end);
      len = (std::min)(static_cast<std::ptrdiff_t>(2), len);
      v = this->toi(m_position, m_position + len, 10);
   }
   if(v < 0)
   {
      // oops not a number:
      put(static_cast<char_type>('?'));
      return;
   }

   // output varies depending upon whether sub-expression v matched or not:
   if(m_results[v].matched)
   {
      m_have_conditional = true;
      format_all();
      m_have_conditional = false;
      if((m_position != m_end) && (*m_position == static_cast<char_type>(':')))
      {
         // skip the ':':
         ++m_position;
         // save output state, then turn it off:
         output_state saved_state = m_state;
         m_state = output_none;
         // format the rest of this scope:
         format_until_scope_end();
         // restore output state:
         m_state = saved_state;
      }
   }
   else
   {
      // save output state, then turn it off:
      output_state saved_state = m_state;
      m_state = output_none;
      // format until ':' or ')':
      m_have_conditional = true;
      format_all();
      m_have_conditional = false;
      // restore state:
      m_state = saved_state;
      if((m_position != m_end) && (*m_position == static_cast<char_type>(':')))
      {
         // skip the ':':
         ++m_position;
         // format the rest of this scope:
         format_until_scope_end();
      }
   }
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::format_until_scope_end()
{
   do
   {
      format_all();
      if((m_position == m_end) || (*m_position == static_cast<char_type>(')')))
         return;
      put(*m_position++);
   }while(m_position != m_end);
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::put(char_type c)
{
   // write a single character to output
   // according to which case translation mode we are in:
   switch(this->m_state)
   {
   case output_none:
      return;
   case output_next_lower:
      c = m_traits.tolower(c);
      this->m_state = m_restore_state;
      break;
   case output_next_upper:
      c = m_traits.toupper(c);
      this->m_state = m_restore_state;
      break;
   case output_lower:
      c = m_traits.tolower(c);
      break;
   case output_upper:
      c = m_traits.toupper(c);
      break;
   default:
      break;
   }
   *m_out = c;
   ++m_out;
}


template <class OutputIterator, class Results, class traits, class ForwardIter>
void basic_regex_formatter<OutputIterator, Results, traits, ForwardIter>::put(const sub_match_type& sub)
{
   typedef typename sub_match_type::iterator iterator_type;
   iterator_type i = sub.first;
   while(i != sub.second)
   {
      put(*i);
      ++i;
   }
}

   string_out_iterator(S& s) : out(&s) {}

   string_out_iterator& operator++() { return *this; }

   string_out_iterator& operator++(int) { return *this; }

   string_out_iterator& operator*() { return *this; }

   string_out_iterator& operator=(typename S::value_type v) 
   { 
      out->append(1, v); 
      return *this; 
   }


template <class OutputIterator, class Iterator, class Alloc, class ForwardIter, class traits>
OutputIterator regex_format_imp(OutputIterator out,
                          const match_results<Iterator, Alloc>& m,
                          ForwardIter p1, ForwardIter p2,
                          match_flag_type flags,
                          const traits& t
                         )
{
   if(flags & regex_constants::format_literal)
   {
      return re_detail::copy(p1, p2, out);
   }

   re_detail::basic_regex_formatter<
      OutputIterator, 
      match_results<Iterator, Alloc>, 
      traits, ForwardIter> f(out, m, t);
   return f.format(p1, p2, flags);
}

   format_functor3(Base b) : func(b) {}

   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f)
   {
      return boost::unwrap_ref(func)(m, i, f);
   }

   format_functor2(Base b) : func(b) {}

   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type /*f*/)
   {
      return boost::unwrap_ref(func)(m, i);
   }

   format_functor1(Base b) : func(b) {}


   template <class S, class OutputIter>
   OutputIter do_format_string(const S& s, OutputIter i)
   {
      return re_detail::copy(s.begin(), s.end(), i);
   }

   template <class S, class OutputIter>
   inline OutputIter do_format_string(const S* s, OutputIter i)
   {
      while(s && *s)
      {
         *i = *s;
         ++i;
         ++s;
      }
      return i;
   }

   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type /*f*/)
   {
      return do_format_string(boost::unwrap_ref(func)(m), i);
   }

   format_functor_c_string(const charT* ps) : func(ps) {}


   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits& t = Traits())
   {
      //typedef typename Match::char_type char_type;
      const charT* end = func;
      while(*end) ++end;
      return regex_format_imp(i, m, func, end, f, t);
   }

   format_functor_container(const Container& c) : func(c) {}


   template <class OutputIter>
   OutputIter operator()(const Match& m, OutputIter i, boost::regex_constants::match_flag_type f, const Traits& t = Traits())
   {
      //typedef typename Match::char_type char_type;
      return re_detail::regex_format_imp(i, m, func.begin(), func.end(), f, t);
   }


template <class OutputIterator, class Iterator, class Allocator, class Functor>
inline OutputIterator regex_format(OutputIterator out,
                          const match_results<Iterator, Allocator>& m,
                          Functor fmt,
                          match_flag_type flags = format_all
                         )
{
   return m.format(out, fmt, flags);
}

   cpp_regex_traits_char_layer(const std::locale& l)
      : cpp_regex_traits_base<charT>(l)
   {
      init();
   }


   regex_constants::syntax_type syntax_type(charT c)const
   {
      map_iterator_type i = m_char_map.find(c);
      return ((i == m_char_map.end()) ? 0 : i->second);
   }

   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      map_iterator_type i = m_char_map.find(c);
      if(i == m_char_map.end())
      {
         if(this->m_pctype->is(std::ctype_base::lower, c)) return regex_constants::escape_type_class;
         if(this->m_pctype->is(std::ctype_base::upper, c)) return regex_constants::escape_type_not_class;
         return 0;
      }
      return i->second;
   }


template <class charT>
void cpp_regex_traits_char_layer<charT>::init()
{
   // we need to start by initialising our syntax map so we know which
   // character is used for which purpose:
#ifndef BOOST_NO_STD_MESSAGES
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if(cat_name.size() && (this->m_pmessages != 0))
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::re_detail::raise_runtime_error(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
#ifndef BOOST_NO_EXCEPTIONS
      try{
#endif
         for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
         {
            string_type mss = this->m_pmessages->get(cat, 0, i, get_default_message(i));
            for(typename string_type::size_type j = 0; j < mss.size(); ++j)
            {
               m_char_map[mss[j]] = i;
            }
         }
         this->m_pmessages->close(cat);
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
         if(this->m_pmessages)
            this->m_pmessages->close(cat);
         throw;
      }
#endif
   }
   else
   {
#endif
      for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
      {
         const char* ptr = get_default_syntax(i);
         while(ptr && *ptr)
         {
            m_char_map[this->m_pctype->widen(*ptr)] = i;
            ++ptr;
         }
      }
#ifndef BOOST_NO_STD_MESSAGES
   }
#endif
}

   cpp_regex_traits_implementation(const std::locale& l)
      : cpp_regex_traits_char_layer<charT>(l)
   {
      init();
   }

   std::string error_string(regex_constants::error_type n) const
   {
      if(!m_error_strings.empty())
      {
         std::map<int, std::string>::const_iterator p = m_error_strings.find(n);
         return (p == m_error_strings.end()) ? std::string(get_default_error_string(n)) : p->second;
      }
      return get_default_error_string(n);
   }

   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      char_class_type result = lookup_classname_imp(p1, p2);
      if(result == 0)
      {
         string_type temp(p1, p2);
         this->m_pctype->tolower(&*temp.begin(), &*temp.begin() + temp.size());
         result = lookup_classname_imp(&*temp.begin(), &*temp.begin() + temp.size());
      }
      return result;
   }


template <class charT>
void cpp_regex_traits_implementation<charT>::init()
{
#ifndef BOOST_NO_STD_MESSAGES
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if(cat_name.size() && (this->m_pmessages != 0))
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::re_detail::raise_runtime_error(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
      //
      // Error messages:
      //
      for(boost::regex_constants::error_type i = static_cast<boost::regex_constants::error_type>(0); 
         i <= boost::regex_constants::error_unknown; 
         i = static_cast<boost::regex_constants::error_type>(i + 1))
      {
         const char* p = get_default_error_string(i);
         string_type default_message;
         while(*p)
         {
            default_message.append(1, this->m_pctype->widen(*p));
            ++p;
         }
         string_type s = this->m_pmessages->get(cat, 0, i+200, default_message);
         std::string result;
         for(std::string::size_type j = 0; j < s.size(); ++j)
         {
            result.append(1, this->m_pctype->narrow(s[j], 0));
         }
         m_error_strings[i] = result;
      }
      //
      // Custom class names:
      //
#ifndef BOOST_REGEX_BUGGY_CTYPE_FACET
      static const char_class_type masks[16] = 
      {
         std::ctype<charT>::alnum,
         std::ctype<charT>::alpha,
         std::ctype<charT>::cntrl,
         std::ctype<charT>::digit,
         std::ctype<charT>::graph,
         cpp_regex_traits_implementation<charT>::mask_horizontal,
         std::ctype<charT>::lower,
         std::ctype<charT>::print,
         std::ctype<charT>::punct,
         std::ctype<charT>::space,
         std::ctype<charT>::upper,
         cpp_regex_traits_implementation<charT>::mask_vertical,
         std::ctype<charT>::xdigit,
         cpp_regex_traits_implementation<charT>::mask_blank,
         cpp_regex_traits_implementation<charT>::mask_word,
         cpp_regex_traits_implementation<charT>::mask_unicode,
      };
#else
      static const char_class_type masks[16] = 
      {
         ::boost::re_detail::char_class_alnum,
         ::boost::re_detail::char_class_alpha,
         ::boost::re_detail::char_class_cntrl,
         ::boost::re_detail::char_class_digit,
         ::boost::re_detail::char_class_graph,
         ::boost::re_detail::char_class_horizontal_space,
         ::boost::re_detail::char_class_lower,
         ::boost::re_detail::char_class_print,
         ::boost::re_detail::char_class_punct,
         ::boost::re_detail::char_class_space,
         ::boost::re_detail::char_class_upper,
         ::boost::re_detail::char_class_vertical_space,
         ::boost::re_detail::char_class_xdigit,
         ::boost::re_detail::char_class_blank,
         ::boost::re_detail::char_class_word,
         ::boost::re_detail::char_class_unicode,
      };
#endif
      static const string_type null_string;
      for(unsigned int j = 0; j <= 13; ++j)
      {
         string_type s(this->m_pmessages->get(cat, 0, j+300, null_string));
         if(s.size())
            this->m_custom_class_names[s] = masks[j];
      }
   }
#endif
   //
   // get the collation format used by m_pcollate:
   //
   m_collate_type = re_detail::find_sort_syntax(this, &m_collate_delim);
}


template <class charT>
typename cpp_regex_traits_implementation<charT>::char_class_type 
   cpp_regex_traits_implementation<charT>::lookup_classname_imp(const charT* p1, const charT* p2) const
{
#ifndef BOOST_REGEX_BUGGY_CTYPE_FACET
   static const char_class_type masks[22] = 
   {
      0,
      std::ctype<char>::alnum, 
      std::ctype<char>::alpha,
      cpp_regex_traits_implementation<charT>::mask_blank,
      std::ctype<char>::cntrl,
      std::ctype<char>::digit,
      std::ctype<char>::digit,
      std::ctype<char>::graph,
      cpp_regex_traits_implementation<charT>::mask_horizontal,
      std::ctype<char>::lower,
      std::ctype<char>::lower,
      std::ctype<char>::print,
      std::ctype<char>::punct,
      std::ctype<char>::space,
      std::ctype<char>::space,
      std::ctype<char>::upper,
      cpp_regex_traits_implementation<charT>::mask_unicode,
      std::ctype<char>::upper,
      cpp_regex_traits_implementation<charT>::mask_vertical,
      std::ctype<char>::alnum | cpp_regex_traits_implementation<charT>::mask_word, 
      std::ctype<char>::alnum | cpp_regex_traits_implementation<charT>::mask_word, 
      std::ctype<char>::xdigit,
   };
#else
   static const char_class_type masks[22] = 
   {
      0,
      ::boost::re_detail::char_class_alnum, 
      ::boost::re_detail::char_class_alpha,
      ::boost::re_detail::char_class_blank,
      ::boost::re_detail::char_class_cntrl,
      ::boost::re_detail::char_class_digit,
      ::boost::re_detail::char_class_digit,
      ::boost::re_detail::char_class_graph,
      ::boost::re_detail::char_class_horizontal_space,
      ::boost::re_detail::char_class_lower,
      ::boost::re_detail::char_class_lower,
      ::boost::re_detail::char_class_print,
      ::boost::re_detail::char_class_punct,
      ::boost::re_detail::char_class_space,
      ::boost::re_detail::char_class_space,
      ::boost::re_detail::char_class_upper,
      ::boost::re_detail::char_class_unicode,
      ::boost::re_detail::char_class_upper,
      ::boost::re_detail::char_class_vertical_space,
      ::boost::re_detail::char_class_alnum | ::boost::re_detail::char_class_word, 
      ::boost::re_detail::char_class_alnum | ::boost::re_detail::char_class_word, 
      ::boost::re_detail::char_class_xdigit,
   };
#endif
   if(m_custom_class_names.size())
   {
      typedef typename std::map<std::basic_string<charT>, char_class_type>::const_iterator map_iter;
      map_iter pos = m_custom_class_names.find(string_type(p1, p2));
      if(pos != m_custom_class_names.end())
         return pos->second;
   }
   std::size_t state_id = 1 + re_detail::get_default_class_id(p1, p2);
   BOOST_ASSERT(state_id < sizeof(masks) / sizeof(masks[0]));
   return masks[state_id];
}


   cpp_regex_traits()
      : m_pimpl(re_detail::create_cpp_regex_traits<charT>(std::locale()))
   { }

   static size_type length(const char_type* p)
   {
      return std::char_traits<charT>::length(p);
   }

   regex_constants::syntax_type syntax_type(charT c)const
   {
      return m_pimpl->syntax_type(c);
   }

   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      return m_pimpl->escape_syntax_type(c);
   }

   charT translate(charT c) const
   {
      return c;
   }

   charT translate_nocase(charT c) const
   {
      return m_pimpl->m_pctype->tolower(c);
   }

   charT translate(charT c, bool icase) const
   {
      return icase ? m_pimpl->m_pctype->tolower(c) : c;
   }

   charT tolower(charT c) const
   {
      return m_pimpl->m_pctype->tolower(c);
   }

   charT toupper(charT c) const
   {
      return m_pimpl->m_pctype->toupper(c);
   }

   string_type transform(const charT* p1, const charT* p2) const
   {
      return m_pimpl->transform(p1, p2);
   }

   string_type transform_primary(const charT* p1, const charT* p2) const
   {
      return m_pimpl->transform_primary(p1, p2);
   }

   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_classname(p1, p2);
   }

   string_type lookup_collatename(const charT* p1, const charT* p2) const
   {
      return m_pimpl->lookup_collatename(p1, p2);
   }

   bool isctype(charT c, char_class_type f) const
   {
#ifndef BOOST_REGEX_BUGGY_CTYPE_FACET
      typedef typename std::ctype<charT>::mask ctype_mask;

      static const ctype_mask mask_base = 
         static_cast<ctype_mask>(
            std::ctype<charT>::alnum 
            | std::ctype<charT>::alpha
            | std::ctype<charT>::cntrl
            | std::ctype<charT>::digit
            | std::ctype<charT>::graph
            | std::ctype<charT>::lower
            | std::ctype<charT>::print
            | std::ctype<charT>::punct
            | std::ctype<charT>::space
            | std::ctype<charT>::upper
            | std::ctype<charT>::xdigit);

      if((f & mask_base) 
         && (m_pimpl->m_pctype->is(
            static_cast<ctype_mask>(f & mask_base), c)))
         return true;
      else if((f & re_detail::cpp_regex_traits_implementation<charT>::mask_unicode) && re_detail::is_extended(c))
         return true;
      else if((f & re_detail::cpp_regex_traits_implementation<charT>::mask_word) && (c == '_'))
         return true;
      else if((f & re_detail::cpp_regex_traits_implementation<charT>::mask_blank) 
         && m_pimpl->m_pctype->is(std::ctype<charT>::space, c)
         && !re_detail::is_separator(c))
         return true;
      else if((f & re_detail::cpp_regex_traits_implementation<charT>::mask_vertical) 
         && (::boost::re_detail::is_separator(c) || (c == '\v')))
         return true;
      else if((f & re_detail::cpp_regex_traits_implementation<charT>::mask_horizontal) 
         && this->isctype(c, std::ctype<charT>::space) && !this->isctype(c, re_detail::cpp_regex_traits_implementation<charT>::mask_vertical))
         return true;
      return false;
#else
      return m_pimpl->isctype(c, f);
#endif
   }

   int value(charT c, int radix)const
   {
      const charT* pc = &c;
      return toi(pc, pc + 1, radix);
   }

   locale_type imbue(locale_type l)
   {
      std::locale result(getloc());
      m_pimpl = re_detail::create_cpp_regex_traits<charT>(l);
      return result;
   }

   locale_type getloc()const
   {
      return m_pimpl->m_locale;
   }

   std::string error_string(regex_constants::error_type n) const
   {
      return m_pimpl->error_string(n);
   }



template <class charT>
int cpp_regex_traits<charT>::toi(const charT*& first, const charT* last, int radix)const
{
   re_detail::parser_buf<charT>   sbuf;            // buffer for parsing numbers.
   std::basic_istream<charT>      is(&sbuf);       // stream for parsing numbers.

   // we do NOT want to parse any thousands separators inside the stream:
   last = std::find(first, last, BOOST_USE_FACET(std::numpunct<charT>, is.getloc()).thousands_sep());

   sbuf.pubsetbuf(const_cast<charT*>(static_cast<const charT*>(first)), static_cast<std::streamsize>(last-first));
   is.clear();
   if(std::abs(radix) == 16) is >> std::hex;
   else if(std::abs(radix) == 8) is >> std::oct;
   else is >> std::dec;
   int val;
   if(is >> val)
   {
      first = first + ((last - first) - sbuf.in_avail());
      return val;
   }
   else
      return -1;
}

   regex_traits() : implementationT() {}

   std::string error_string(::boost::regex_constants::error_type e)const
   {
      return ::boost::re_detail::get_default_error_string(e);
   }

   ::boost::regex_constants::syntax_type syntax_type(char_type c)const
   {
      return ((c & 0x7f) == c) ? get_default_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::syntax_char;
   }

   ::boost::regex_constants::escape_syntax_type escape_syntax_type(char_type c)const
   {
      return ((c & 0x7f) == c) ? get_default_escape_syntax_type(static_cast<char>(c)) : ::boost::regex_constants::escape_type_identity;
   }

   int toi(const char_type*& p1, const char_type* p2, int radix)const
   {
      return ::boost::re_detail::global_toi(p1, p2, radix, *this);
   }

   char_type translate(char_type c, bool icase)const
   {
      return (icase ? this->translate_nocase(c) : this->translate(c));
   }

   char_type translate(char_type c)const
   {
      return BaseT::translate(c);
   }

   char_type tolower(char_type c)const
   {
      return ::boost::re_detail::global_lower(c);
   }

   char_type toupper(char_type c)const
   {
      return ::boost::re_detail::global_upper(c);
   }

   regex_traits_wrapper(){}


   ~mem_block_cache()
   {
      while(next)
      {
         mem_block_node* old = next;
         next = next->next;
         ::operator delete(old);
      }
   }

   void* get()
   {
#ifdef BOOST_HAS_THREADS
      boost::static_mutex::scoped_lock g(mut);
#endif
     if(next)
      {
         mem_block_node* result = next;
         next = next->next;
         --cached_blocks;
         return result;
      }
      return ::operator new(BOOST_REGEX_BLOCKSIZE);
   }

   void put(void* p)
   {
#ifdef BOOST_HAS_THREADS
      boost::static_mutex::scoped_lock g(mut);
#endif
      if(cached_blocks >= BOOST_REGEX_MAX_CACHE_BLOCKS)
      {
         ::operator delete(p);
      }
      else
      {
         mem_block_node* old = static_cast<mem_block_node*>(p);
         old->next = next;
         next = old;
         ++cached_blocks;
      }
   }

   u32regex_iterator_implementation(const regex_type* p, BidirectionalIterator last, match_flag_type f)
      : base(), end(last), re(*p), flags(f){}

   bool init(BidirectionalIterator first)
   {
      base = first;
      return u32regex_search(first, end, what, re, flags, base);
   }

   bool compare(const u32regex_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) && (end == that.end) && (flags == that.flags) && (what[0].first == that.what[0].first) && (what[0].second == that.what[0].second);
   }

   
   u32regex_iterator(){}

   u32regex_iterator(const u32regex_iterator& that)
      : pdata(that.pdata) {}

   u32regex_iterator& operator=(const u32regex_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }

   bool operator==(const u32regex_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }

   bool operator!=(const u32regex_iterator& that)const
   { return !(*this == that); }

   const value_type& operator*()const
   { return pdata->get(); }

   const value_type* operator->()const
   { return &(pdata->get()); }

   u32regex_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }

   u32regex_iterator operator++(int)
   {
      u32regex_iterator result(*this);
      ++(*this);
      return result;
   }


   void cow()
   {
      // copy-on-write
      if(pdata.get() && !pdata.unique())
      {
         pdata.reset(new impl(*(pdata.get())));
      }
   }


inline u32regex_iterator<const char*> make_u32regex_iterator(const char* p, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_iterator<const char*>(p, p+std::strlen(p), e, m);
}


inline bool is_high_surrogate(::boost::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xd800u;
}

inline bool is_low_surrogate(::boost::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xdc00u;
}

template <class T>
inline bool is_surrogate(T v)
{
   return (v & 0xFFFFF800u) == 0xd800;
}


inline unsigned utf8_byte_count(boost::uint8_t c)
{
   // if the most significant bit with a zero in it is in position
   // 8-N then there are N bytes in this UTF-8 sequence:
   boost::uint8_t mask = 0x80u;
   unsigned result = 0;
   while(c & mask)
   {
      ++result;
      mask >>= 1;
   }
   return (result == 0) ? 1 : ((result > 4) ? 4 : result);
}


inline unsigned utf8_trailing_byte_count(boost::uint8_t c)
{
   return utf8_byte_count(c) - 1;
}

inline void invalid_utf32_code_point(::boost::uint32_t val)
{
#ifndef BOOST_NO_STD_LOCALE
   std::stringstream ss;
   ss << "Invalid UTF-32 code point U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-16 sequence";
   std::out_of_range e(ss.str());
#else
   std::out_of_range e("Invalid UTF-32 code point encountered while trying to encode UTF-16 sequence");
#endif
   boost::throw_exception(e);
}


   utf16_output_iterator(const BaseIterator& b)
      : m_position(b){}

   utf16_output_iterator(const utf16_output_iterator& that)
      : m_position(that.m_position){}

   utf16_output_iterator& operator=(const utf16_output_iterator& that)
   {
      m_position = that.m_position;
      return *this;
   }

   const utf16_output_iterator& operator*()const
   {
      return *this;
   }

   utf16_output_iterator& operator++()
   {
      return *this;
   }

   utf16_output_iterator& operator++(int)
   {
      return *this;
   }

   BaseIterator base()const
   {
      return m_position;
   }

   void push(boost::uint32_t v)const
   {
      if(v >= 0x10000u)
      {
         // begin by checking for a code point out of range:
         if(v > 0x10FFFFu)
            detail::invalid_utf32_code_point(v);
         // split into two surrogates:
         *m_position++ = static_cast<boost::uint16_t>(v >> 10) + detail::high_surrogate_base;
         *m_position++ = static_cast<boost::uint16_t>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
      }
      else
      {
         // 16-bit code point:
         // value must not be a surrogate:
         if(detail::is_surrogate(v))
            detail::invalid_utf32_code_point(v);
         *m_position++ = static_cast<boost::uint16_t>(v);
      }
   }


   utf8_output_iterator(const BaseIterator& b)
      : m_position(b){}

   utf8_output_iterator(const utf8_output_iterator& that)
      : m_position(that.m_position){}

   utf8_output_iterator& operator=(const utf8_output_iterator& that)
   {
      m_position = that.m_position;
      return *this;
   }

   const utf8_output_iterator& operator*()const
   {
      return *this;
   }

   utf8_output_iterator& operator++()
   {
      return *this;
   }

   utf8_output_iterator& operator++(int)
   {
      return *this;
   }

   BaseIterator base()const
   {
      return m_position;
   }

   void push(boost::uint32_t c)const
   {
      if(c > 0x10FFFFu)
         detail::invalid_utf32_code_point(c);
      if(c < 0x80u)
      {
         *m_position++ = static_cast<unsigned char>(c);
      }
      else if(c < 0x800u)
      {
         *m_position++ = static_cast<unsigned char>(0xC0u + (c >> 6));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
      else if(c < 0x10000u)
      {
         *m_position++ = static_cast<unsigned char>(0xE0u + (c >> 12));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
      else
      {
         *m_position++ = static_cast<unsigned char>(0xF0u + (c >> 18));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 12) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
   }
