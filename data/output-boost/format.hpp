
    template<class T>
    const T& const_or_not(const T& x) { 
        return x;
    }


    template<class Ch, class Facet> inline
    char wrap_narrow(const Facet& fac, Ch c, char deflt) {
        return const_or_not(fac).narrow(c, deflt);
    }


    template<class Ch, class Facet> inline
    bool wrap_isdigit(const Facet& fac, Ch c) {
#if ! defined( BOOST_NO_LOCALE_ISDIGIT )
        return fac.is(std::ctype<Ch>::digit, c);
# else
        (void) fac;     // remove "unused parameter" warning
        using namespace std;
        return isdigit(c); 
#endif 
    }

 
    template<class Iter, class Facet> 
    Iter wrap_scan_notdigit(const Facet & fac, Iter beg, Iter end) {
        using namespace std;
        for( ; beg!=end && wrap_isdigit(fac, *beg); ++beg) ;
        return beg;
    }

    template<class Res, class Iter, class Facet>
    Iter str2int (const Iter & start, const Iter & last, Res & res, 
                 const Facet& fac) 
    {
        using namespace std;
        Iter it;
        res=0;
        for(it=start; it != last && wrap_isdigit(fac, *it); ++it ) {
            char cur_ch = wrap_narrow(fac, *it, 0); // cant fail.
            res *= 10;
            res += cur_ch - '0'; // 22.2.1.1.2.13 of the C++ standard
        }
        return it;
    }

    template<class Iter, class Facet>
    Iter skip_asterisk(Iter start, Iter last, const Facet& fac) 
    {
        using namespace std;
        ++ start;
        start = wrap_scan_notdigit(fac, start, last);
        if(start!=last && *start== const_or_not(fac).widen( '$') )
            ++start;
        return start;
    }

    inline void maybe_throw_exception(unsigned char exceptions, 
                                      std::size_t pos, std::size_t size)
    {
        if(exceptions & io::bad_format_string_bit)
            boost::throw_exception(io::bad_format_string(pos, size) );
    }

    template<class Ch, class Tr, class Alloc, class Iter, class Facet>
    bool parse_printf_directive(Iter & start, const Iter& last, 
                                detail::format_item<Ch, Tr, Alloc> * fpar,
                                const Facet& fac,
                                std::size_t offset, unsigned char exceptions)
    {
        typedef typename basic_format<Ch, Tr, Alloc>::format_item_t format_item_t;

        fpar->argN_ = format_item_t::argN_no_posit;  // if no positional-directive
        bool precision_set = false;
        bool in_brackets=false;
        Iter start0 = start;
        std::size_t fstring_size = last-start0+offset;

        if(start>= last) { // empty directive : this is a trailing %
                maybe_throw_exception(exceptions, start-start0 + offset, fstring_size);
                return false;
        }          
          
        if(*start== const_or_not(fac).widen( '|')) {
            in_brackets=true;
            if( ++start >= last ) {
                maybe_throw_exception(exceptions, start-start0 + offset, fstring_size);
                return false;
            }
        }

        // the flag '0' would be picked as a digit for argument order, but here it's a flag :
        if(*start== const_or_not(fac).widen( '0')) 
            goto parse_flags;

        // handle argument order (%2$d)  or possibly width specification: %2d
        if(wrap_isdigit(fac, *start)) {
            int n;
            start = str2int(start, last, n, fac);
            if( start >= last ) {
                maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
                return false;
            }
            
            // %N% case : this is already the end of the directive
            if( *start ==  const_or_not(fac).widen( '%') ) {
                fpar->argN_ = n-1;
                ++start;
                if( in_brackets) 
                    maybe_throw_exception(exceptions, start-start0+offset, fstring_size); 
                // but don't return.  maybe "%" was used in lieu of '$', so we go on.
                else
                    return true;
            }

            if ( *start== const_or_not(fac).widen( '$') ) {
                fpar->argN_ = n-1;
                ++start;
            } 
            else {
                // non-positionnal directive
                fpar->fmtstate_.width_ = n;
                fpar->argN_  = format_item_t::argN_no_posit;
                goto parse_precision;
            }
        }
    
      parse_flags: 
        // handle flags
        while ( start != last) { // as long as char is one of + - = _ # 0 l h   or ' '
            // misc switches
            switch ( wrap_narrow(fac, *start, 0)) {
            case '\'' : break; // no effect yet. (painful to implement)
            case 'l':
            case 'h':  // short/long modifier : for printf-comaptibility (no action needed)
                break;
            case '-':
                fpar->fmtstate_.flags_ |= std::ios_base::left;
                break;
            case '=':
                fpar->pad_scheme_ |= format_item_t::centered;
                break;
            case '_':
                fpar->fmtstate_.flags_ |= std::ios_base::internal;
                break;
            case ' ':
                fpar->pad_scheme_ |= format_item_t::spacepad;
                break;
            case '+':
                fpar->fmtstate_.flags_ |= std::ios_base::showpos;
                break;
            case '0':
                fpar->pad_scheme_ |= format_item_t::zeropad;
                // need to know alignment before really setting flags,
                // so just add 'zeropad' flag for now, it will be processed later.
                break;
            case '#':
                fpar->fmtstate_.flags_ |= std::ios_base::showpoint | std::ios_base::showbase;
                break;
            default:
                goto parse_width;
            }
            ++start;
        } // loop on flag.

        if( start>=last) {
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            return true; 
        }
      parse_width:
        // handle width spec
        // first skip 'asterisk fields' :  *, or *N$
        if(*start == const_or_not(fac).widen( '*') )
            start = skip_asterisk(start, last, fac); 
        if(start!=last && wrap_isdigit(fac, *start))
            start = str2int(start, last, fpar->fmtstate_.width_, fac);

      parse_precision:
        if( start>= last) { 
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            return true;
        }
        // handle precision spec
        if (*start== const_or_not(fac).widen( '.')) {
            ++start;
            if(start != last && *start == const_or_not(fac).widen( '*') )
                start = skip_asterisk(start, last, fac); 
            if(start != last && wrap_isdigit(fac, *start)) {
                start = str2int(start, last, fpar->fmtstate_.precision_, fac);
                precision_set = true;
            }
            else
                fpar->fmtstate_.precision_ =0;
        }
    
        // handle  formatting-type flags :
        while( start != last && ( *start== const_or_not(fac).widen( 'l') 
                                  || *start== const_or_not(fac).widen( 'L') 
                                  || *start== const_or_not(fac).widen( 'h')) )
            ++start;
        if( start>=last) {
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            return true;
        }

        if( in_brackets && *start== const_or_not(fac).widen( '|') ) {
            ++start;
            return true;
        }
        switch ( wrap_narrow(fac, *start, 0) ) {
        case 'X':
            fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
        case 'p': // pointer => set hex.
        case 'x':
            fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
            fpar->fmtstate_.flags_ |= std::ios_base::hex;
            break;

        case 'o':
            fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
            fpar->fmtstate_.flags_ |=  std::ios_base::oct;
            break;

        case 'E':
            fpar->fmtstate_.flags_ |=  std::ios_base::uppercase;
        case 'e':
            fpar->fmtstate_.flags_ &= ~std::ios_base::floatfield;
            fpar->fmtstate_.flags_ |=  std::ios_base::scientific;

            fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
            fpar->fmtstate_.flags_ |=  std::ios_base::dec;
            break;
      
        case 'f':
            fpar->fmtstate_.flags_ &= ~std::ios_base::floatfield;
            fpar->fmtstate_.flags_ |=  std::ios_base::fixed;
        case 'u':
        case 'd':
        case 'i':
            fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
            fpar->fmtstate_.flags_ |=  std::ios_base::dec;
            break;

        case 'T':
            ++start;
            if( start >= last)
                maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
            else
                fpar->fmtstate_.fill_ = *start;
            fpar->pad_scheme_ |= format_item_t::tabulation;
            fpar->argN_ = format_item_t::argN_tabulation; 
            break;
        case 't': 
            fpar->fmtstate_.fill_ = const_or_not(fac).widen( ' ');
            fpar->pad_scheme_ |= format_item_t::tabulation;
            fpar->argN_ = format_item_t::argN_tabulation; 
            break;

        case 'G':
            fpar->fmtstate_.flags_ |= std::ios_base::uppercase;
            break;
        case 'g': // 'g' conversion is default for floats.
            fpar->fmtstate_.flags_ &= ~std::ios_base::basefield;
            fpar->fmtstate_.flags_ |=  std::ios_base::dec;

            // CLEAR all floatield flags, so stream will CHOOSE
            fpar->fmtstate_.flags_ &= ~std::ios_base::floatfield; 
            break;

        case 'C':
        case 'c': 
            fpar->truncate_ = 1;
            break;
        case 'S':
        case 's': 
            if(precision_set) // handle truncation manually, with own parameter.
                fpar->truncate_ = fpar->fmtstate_.precision_;
            fpar->fmtstate_.precision_ = 6; // default stream precision.
            break;
        case 'n' :  
            fpar->argN_ = format_item_t::argN_ignored;
            break;
        default: 
            maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
        }
        ++start;

        if( in_brackets ) {
            if( start != last && *start== const_or_not(fac).widen( '|') ) {
                ++start;
                return true;
            }
            else  maybe_throw_exception(exceptions, start-start0+offset, fstring_size);
        }
        return true;
    }


    template<class String, class Facet>
    int upper_bound_from_fstring(const String& buf, 
                                 const typename String::value_type arg_mark,
                                 const Facet& fac, 
                                 unsigned char exceptions) 
    {
        // quick-parsing of the format-string to count arguments mark (arg_mark, '%')
        // returns : upper bound on the number of format items in the format strings
        using namespace boost::io;
        typename String::size_type i1=0;
        int num_items=0;
        while( (i1=buf.find(arg_mark,i1)) != String::npos ) {
            if( i1+1 >= buf.size() ) {
                if(exceptions & bad_format_string_bit)
                    boost::throw_exception(bad_format_string(i1, buf.size() )); // must not end in ".. %"
                else {
                  ++num_items;
                  break;
                }
            }
            if(buf[i1+1] == buf[i1] ) {// escaped "%%"
                i1+=2; continue; 
            }

            ++i1;
            // in case of %N% directives, dont count it double (wastes allocations..) :
            i1 = detail::wrap_scan_notdigit(fac, buf.begin()+i1, buf.end()) - buf.begin();
            if( i1 < buf.size() && buf[i1] == arg_mark )
                ++i1;
            ++num_items;
        }
        return num_items;
    }

    template<class String> inline
    void append_string(String& dst, const String& src, 
                       const typename String::size_type beg, 
                       const typename String::size_type end) {
#if !defined(BOOST_NO_STRING_APPEND)
        dst.append(src.begin()+beg, src.begin()+end);
#else
        dst += src.substr(beg, end-beg);
#endif
    }
  

    template< class Ch, class Tr, class T> inline
    void put_head (BOOST_IO_STD basic_ostream<Ch, Tr> &, const T& ) {
    }


    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        os << x ;
    }



    template< class Ch, class Tr, class Alloc, class T> 
    void put( T x, 
              const format_item<Ch, Tr, Alloc>& specs, 
              typename basic_format<Ch, Tr, Alloc>::string_type& res, 
              typename basic_format<Ch, Tr, Alloc>::internal_streambuf_t & buf,
              io::detail::locale_t *loc_p = NULL)
    {
#ifdef BOOST_MSVC
       // If std::min<unsigned> or std::max<unsigned> are already instantiated
       // at this point then we get a blizzard of warning messages when we call
       // those templates with std::size_t as arguments.  Weird and very annoyning...
#pragma warning(push)
#pragma warning(disable:4267)
#endif
        // does the actual conversion of x, with given params, into a string
        // using the supplied stringbuf.

        typedef typename basic_format<Ch, Tr, Alloc>::string_type   string_type;
        typedef typename basic_format<Ch, Tr, Alloc>::format_item_t format_item_t;
        typedef typename string_type::size_type size_type;

        basic_oaltstringstream<Ch, Tr, Alloc>  oss( &buf);
        specs.fmtstate_.apply_on(oss, loc_p);

        // the stream format state can be modified by manipulators in the argument :
        put_head( oss, x );
        // in case x is a group, apply the manip part of it, 
        // in order to find width

        const std::ios_base::fmtflags fl=oss.flags();
        const bool internal = (fl & std::ios_base::internal) != 0;
        const std::streamsize w = oss.width();
        const bool two_stepped_padding= internal && (w!=0);
      
        res.resize(0);
        if(! two_stepped_padding) {
            if(w>0) // handle padding via mk_str, not natively in stream 
                oss.width(0);
            put_last( oss, x);
            const Ch * res_beg = buf.pbase();
            Ch prefix_space = 0;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = oss.widen(' ');
            size_type res_size = (std::min)(
                static_cast<size_type>(specs.truncate_ - !!prefix_space), 
                buf.pcount() );
            mk_str(res, res_beg, res_size, w, oss.fill(), fl, 
                   prefix_space, (specs.pad_scheme_ & format_item_t::centered) !=0 );
        }
        else  { // 2-stepped padding
            // internal can be implied by zeropad, or user-set.
            // left, right, and centered alignment overrule internal,
            // but spacepad or truncate might be mixed with internal (using manipulator)
            put_last( oss, x); // may pad
            const Ch * res_beg = buf.pbase();
            size_type res_size = buf.pcount();
            bool prefix_space=false;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = true;
            if(res_size == static_cast<size_type>(w) && w<=specs.truncate_ && !prefix_space) {
                // okay, only one thing was printed and padded, so res is fine
                res.assign(res_beg, res_size);
            }
            else { //   length w exceeded
                // either it was multi-output with first output padding up all width..
                // either it was one big arg and we are fine.
                // Note that res_size<w is possible  (in case of bad user-defined formatting)
                res.assign(res_beg, res_size);
                res_beg=NULL;  // invalidate pointers.
                
                // make a new stream, to start re-formatting from scratch :
                buf.clear_buffer();
                basic_oaltstringstream<Ch, Tr, Alloc>  oss2( &buf);
                specs.fmtstate_.apply_on(oss2, loc_p);
                put_head( oss2, x );

                oss2.width(0);
                if(prefix_space)
                    oss2 << ' ';
                put_last(oss2, x );
                if(buf.pcount()==0 && specs.pad_scheme_ & format_item_t::spacepad) {
                    prefix_space =true;
                    oss2 << ' ';
                }
                // we now have the minimal-length output
                const Ch * tmp_beg = buf.pbase();
                size_type tmp_size = (std::min)(static_cast<size_type>(specs.truncate_),
                                                buf.pcount() );
                                                    
                
                if(static_cast<size_type>(w) <= tmp_size) { 
                    // minimal length is already >= w, so no padding (cool!)
                        res.assign(tmp_beg, tmp_size);
                }
                else { // hum..  we need to pad (multi_output, or spacepad present)
                    //find where we should pad
                    size_type sz = (std::min)(res_size + (prefix_space ? 1 : 0), tmp_size);
                    size_type i = prefix_space;
                    for(; i<sz && tmp_beg[i] == res[i - (prefix_space ? 1 : 0)]; ++i) {}
                    if(i>=tmp_size) i=prefix_space;
                    res.assign(tmp_beg, i);
                                        std::streamsize d = w - static_cast<std::streamsize>(tmp_size);
                                        BOOST_ASSERT(d>0);
                    res.append(static_cast<size_type>( d ), oss2.fill());
                    res.append(tmp_beg+i, tmp_size-i);
                    BOOST_ASSERT(i+(tmp_size-i)+(std::max)(d,(std::streamsize)0) 
                                 == static_cast<size_type>(w));
                    BOOST_ASSERT(res.size() == static_cast<size_type>(w));
                }
            }
        }
        buf.clear_buffer();
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    }



            explicit basic_altstringbuf(std::ios_base::openmode mode
                                        = std::ios_base::in | std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                {}

            virtual ~basic_altstringbuf() 
                { dealloc(); }

            Ch * pend() const // the highest position reached by pptr() since creation
                { return ((putend_ < pptr()) ? pptr() : putend_); }

            size_type pcount() const 
                { return static_cast<size_type>( pptr() - pbase()) ;}

            string_type cur_str() const 
                { return string_type(begin(), cur_size()); }
 
                template<class T>
                const T & operator()(const T & arg) { return arg; }

            basic_oaltstringstream() 
                : pbase_type(new stringbuf_t), stream_t(rdbuf()) 
                { }

            basic_oaltstringstream(stringbuf_t * buf) 
                : pbase_type(buf, No_Op() ), stream_t(rdbuf()) 
                { }

            stringbuf_t * rdbuf() const 
                { return pbase_type::member.get(); }

            void clear_buffer() 
                { rdbuf()->clear_buffer(); }

            Ch * begin() const 
                { return rdbuf()->begin(); }

            size_type size() const 
                { return rdbuf()->size(); }

            size_type cur_size() const // stops at current position
                { return rdbuf()->cur_size(); }

            string_type str()     const   // [pbase, epptr[
                { return rdbuf()->str(); }
 
            string_type cur_str() const   // [pbase, pptr[
                { return rdbuf()->cur_str(); }


        stream_format_state(Ch fill)                 { reset(fill); }

        template<class T> 
        void apply_manip(T manipulator)          //- modifies state by applying manipulator
            { apply_manip_body<Ch, Tr, T>( *this, manipulator) ; }


        format_item(Ch fill) :argN_(argN_no_posit), fmtstate_(fill), 
                              truncate_(max_streamsize()), pad_scheme_(0)  {}


        static std::streamsize max_streamsize() { 
            return (std::numeric_limits<std::streamsize>::max)();
        }


    template<class Ch, class Tr>
    void stream_format_state<Ch,Tr>:: set_by_stream(const basic_ios& os) {
        // set our params according to the state of this stream
        flags_ = os.flags();
        width_ = os.width();
        precision_ = os.precision();
        fill_ = os.fill();
        rdstate_ = os.rdstate();
        exceptions_ = os.exceptions();
    }



    template<class Ch, class Tr, class T>
    void apply_manip_body( stream_format_state<Ch, Tr>& self,
                           T manipulator) {
        // modify our params according to the manipulator
        basic_oaltstringstream<Ch, Tr>  ss;
        self.apply_on( ss );
        ss << manipulator;
        self.set_by_stream( ss );
    }


    template<class Ch, class Tr> inline
    void stream_format_state<Ch,Tr>:: reset(Ch fill) {
        // set our params to standard's default state.   cf 27.4.4.1 of the C++ norm
        width_=0; precision_=6; 
        fill_=fill; // default is widen(' '), but we cant compute it without the locale
        flags_ = std::ios_base::dec | std::ios_base::skipws; 
        // the adjust_field part is left equal to 0, which means right.
        exceptions_ = std::ios_base::goodbit;
        rdstate_ = std::ios_base::goodbit;
    }


    template<class Ch, class Tr, class Alloc> 
    void format_item<Ch, Tr, Alloc>:: 
    reset (Ch fill) { 
        argN_=argN_no_posit; truncate_ = max_streamsize(); pad_scheme_ =0; 
        res_.resize(0); appendix_.resize(0);
        fmtstate_.reset(fill);
    }


    template<class Ch, class Tr, class Alloc> 
    void format_item<Ch, Tr, Alloc>:: 
    compute_states() {
        // reflect pad_scheme_   on  fmt_state_
        //   because some pad_schemes has complex consequences on several state params.
        if(pad_scheme_ & zeropad) {
            // ignore zeropad in left alignment :
            if(fmtstate_.flags_ & std::ios_base::left) {
              BOOST_ASSERT(!(fmtstate_.flags_ &(std::ios_base::adjustfield ^std::ios_base::left)));
              // only left bit might be set. (not right, nor internal)
              pad_scheme_ = pad_scheme_ & (~zeropad); 
            }
            else { 
                pad_scheme_ &= ~spacepad; // printf ignores spacepad when zeropadding
                fmtstate_.fill_='0'; 
                fmtstate_.flags_ = (fmtstate_.flags_ & ~std::ios_base::adjustfield) 
                    | std::ios_base::internal;
                // removes all adjustfield bits, and adds internal.
            }
        }
        if(pad_scheme_ & spacepad) {
            if(fmtstate_.flags_ & std::ios_base::showpos)
                pad_scheme_ &= ~spacepad;
        }
    }

    group0()      {}

    group1(T1 a1)
      : a1_(a1)
      {}
&
operator << (BOOST_IO_STD basic_ostream<Ch, Tr>& os,
             const group1<T1>& x)
{ 
   os << x.a1_;  
   return os; 
}

    group2(T1 a1,T2 a2)
      : a1_(a1),a2_(a2)
      {}

    group3(T1 a1,T2 a2,T3 a3)
      : a1_(a1),a2_(a2),a3_(a3)
      {}

    group4(T1 a1,T2 a2,T3 a3,T4 a4)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4)
      {}

    group5(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5)
      {}

    group6(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6)
      {}

    group7(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7)
      {}

    group8(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8)
      {}

    group9(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8),a9_(a9)
      {}

    group10(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9,T10 a10)
      : a1_(a1),a2_(a2),a3_(a3),a4_(a4),a5_(a5),a6_(a6),a7_(a7),a8_(a8),a9_(a9),a10_(a10)
      {}





template <class T1,class T2>
inline
group1<T1> 
group_head( group2<T1,T2> const& x)
{
   return group1<T1> (x.a1_); 
}


template <class T1,class T2>
inline
group1<T2> 
group_last( group2<T1,T2> const& x)
{
   return group1<T2> (x.a2_); 
}




template <class T1,class T2,class T3>
inline
group2<T1,T2> 
group_head( group3<T1,T2,T3> const& x)
{
   return group2<T1,T2> (x.a1_,x.a2_); 
}


template <class T1,class T2,class T3>
inline
group1<T3> 
group_last( group3<T1,T2,T3> const& x)
{
   return group1<T3> (x.a3_); 
}




template <class T1,class T2,class T3,class T4>
inline
group3<T1,T2,T3> 
group_head( group4<T1,T2,T3,T4> const& x)
{
   return group3<T1,T2,T3> (x.a1_,x.a2_,x.a3_); 
}


template <class T1,class T2,class T3,class T4>
inline
group1<T4> 
group_last( group4<T1,T2,T3,T4> const& x)
{
   return group1<T4> (x.a4_); 
}




template <class T1,class T2,class T3,class T4,class T5>
inline
group4<T1,T2,T3,T4> 
group_head( group5<T1,T2,T3,T4,T5> const& x)
{
   return group4<T1,T2,T3,T4> (x.a1_,x.a2_,x.a3_,x.a4_); 
}


template <class T1,class T2,class T3,class T4,class T5>
inline
group1<T5> 
group_last( group5<T1,T2,T3,T4,T5> const& x)
{
   return group1<T5> (x.a5_); 
}




template <class T1,class T2,class T3,class T4,class T5,class T6>
inline
group5<T1,T2,T3,T4,T5> 
group_head( group6<T1,T2,T3,T4,T5,T6> const& x)
{
   return group5<T1,T2,T3,T4,T5> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_); 
}


template <class T1,class T2,class T3,class T4,class T5,class T6>
inline
group1<T6> 
group_last( group6<T1,T2,T3,T4,T5,T6> const& x)
{
   return group1<T6> (x.a6_); 
}




template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
inline
group6<T1,T2,T3,T4,T5,T6> 
group_head( group7<T1,T2,T3,T4,T5,T6,T7> const& x)
{
   return group6<T1,T2,T3,T4,T5,T6> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_); 
}


template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
inline
group1<T7> 
group_last( group7<T1,T2,T3,T4,T5,T6,T7> const& x)
{
   return group1<T7> (x.a7_); 
}




template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
inline
group7<T1,T2,T3,T4,T5,T6,T7> 
group_head( group8<T1,T2,T3,T4,T5,T6,T7,T8> const& x)
{
   return group7<T1,T2,T3,T4,T5,T6,T7> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_); 
}


template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8>
inline
group1<T8> 
group_last( group8<T1,T2,T3,T4,T5,T6,T7,T8> const& x)
{
   return group1<T8> (x.a8_); 
}




template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
inline
group8<T1,T2,T3,T4,T5,T6,T7,T8> 
group_head( group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> const& x)
{
   return group8<T1,T2,T3,T4,T5,T6,T7,T8> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_,x.a8_); 
}


template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9>
inline
group1<T9> 
group_last( group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> const& x)
{
   return group1<T9> (x.a9_); 
}




template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
inline
group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> 
group_head( group10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> const& x)
{
   return group9<T1,T2,T3,T4,T5,T6,T7,T8,T9> (x.a1_,x.a2_,x.a3_,x.a4_,x.a5_,x.a6_,x.a7_,x.a8_,x.a9_); 
}


template <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9,class T10>
inline
group1<T10> 
group_last( group10<T1,T2,T3,T4,T5,T6,T7,T8,T9,T10> const& x)
{
   return group1<T10> (x.a10_); 
}



inline detail::group1< detail::group0 >  
group() { return detail::group1< detail::group0 > ( detail::group0() ); }


template  <class T1, class Var> 
inline
detail::group1< detail::group2<T1, Var const&> >
  group(T1 a1, Var const& var)
{ 
   return detail::group1< detail::group2<T1, Var const&> >
                   ( detail::group2<T1, Var const&> 
                        (a1, var) 
                  );
}


template  <class T1,class T2, class Var> 
inline
detail::group1< detail::group3<T1,T2, Var const&> >
  group(T1 a1,T2 a2, Var const& var)
{ 
   return detail::group1< detail::group3<T1,T2, Var const&> >
                   ( detail::group3<T1,T2, Var const&> 
                        (a1,a2, var) 
                  );
}


template  <class T1,class T2,class T3, class Var> 
inline
detail::group1< detail::group4<T1,T2,T3, Var const&> >
  group(T1 a1,T2 a2,T3 a3, Var const& var)
{ 
   return detail::group1< detail::group4<T1,T2,T3, Var const&> >
                   ( detail::group4<T1,T2,T3, Var const&> 
                        (a1,a2,a3, var) 
                  );
}


template  <class T1,class T2,class T3,class T4, class Var> 
inline
detail::group1< detail::group5<T1,T2,T3,T4, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4, Var const& var)
{ 
   return detail::group1< detail::group5<T1,T2,T3,T4, Var const&> >
                   ( detail::group5<T1,T2,T3,T4, Var const&> 
                        (a1,a2,a3,a4, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5, class Var> 
inline
detail::group1< detail::group6<T1,T2,T3,T4,T5, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5, Var const& var)
{ 
   return detail::group1< detail::group6<T1,T2,T3,T4,T5, Var const&> >
                   ( detail::group6<T1,T2,T3,T4,T5, Var const&> 
                        (a1,a2,a3,a4,a5, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6, class Var> 
inline
detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6, Var const& var)
{ 
   return detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var const&> >
                   ( detail::group7<T1,T2,T3,T4,T5,T6, Var const&> 
                        (a1,a2,a3,a4,a5,a6, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7, class Var> 
inline
detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7, Var const& var)
{ 
   return detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> >
                   ( detail::group8<T1,T2,T3,T4,T5,T6,T7, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8, class Var> 
inline
detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8, Var const& var)
{ 
   return detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> >
                   ( detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9, class Var> 
inline
detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9, Var const& var)
{ 
   return detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> >
                   ( detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var const&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8,a9, var) 
                  );
}


template  <class T1, class Var> 
inline
detail::group1< detail::group2<T1, Var&> >
  group(T1 a1, Var& var)
{ 
   return detail::group1< detail::group2<T1, Var&> >
                   ( detail::group2<T1, Var&> 
                        (a1, var) 
                  );
}


template  <class T1,class T2, class Var> 
inline
detail::group1< detail::group3<T1,T2, Var&> >
  group(T1 a1,T2 a2, Var& var)
{ 
   return detail::group1< detail::group3<T1,T2, Var&> >
                   ( detail::group3<T1,T2, Var&> 
                        (a1,a2, var) 
                  );
}


template  <class T1,class T2,class T3, class Var> 
inline
detail::group1< detail::group4<T1,T2,T3, Var&> >
  group(T1 a1,T2 a2,T3 a3, Var& var)
{ 
   return detail::group1< detail::group4<T1,T2,T3, Var&> >
                   ( detail::group4<T1,T2,T3, Var&> 
                        (a1,a2,a3, var) 
                  );
}


template  <class T1,class T2,class T3,class T4, class Var> 
inline
detail::group1< detail::group5<T1,T2,T3,T4, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4, Var& var)
{ 
   return detail::group1< detail::group5<T1,T2,T3,T4, Var&> >
                   ( detail::group5<T1,T2,T3,T4, Var&> 
                        (a1,a2,a3,a4, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5, class Var> 
inline
detail::group1< detail::group6<T1,T2,T3,T4,T5, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5, Var& var)
{ 
   return detail::group1< detail::group6<T1,T2,T3,T4,T5, Var&> >
                   ( detail::group6<T1,T2,T3,T4,T5, Var&> 
                        (a1,a2,a3,a4,a5, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6, class Var> 
inline
detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6, Var& var)
{ 
   return detail::group1< detail::group7<T1,T2,T3,T4,T5,T6, Var&> >
                   ( detail::group7<T1,T2,T3,T4,T5,T6, Var&> 
                        (a1,a2,a3,a4,a5,a6, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7, class Var> 
inline
detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7, Var& var)
{ 
   return detail::group1< detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> >
                   ( detail::group8<T1,T2,T3,T4,T5,T6,T7, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8, class Var> 
inline
detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8, Var& var)
{ 
   return detail::group1< detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> >
                   ( detail::group9<T1,T2,T3,T4,T5,T6,T7,T8, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8, var) 
                  );
}


template  <class T1,class T2,class T3,class T4,class T5,class T6,class T7,class T8,class T9, class Var> 
inline
detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> >
  group(T1 a1,T2 a2,T3 a3,T4 a4,T5 a5,T6 a6,T7 a7,T8 a8,T9 a9, Var& var)
{ 
   return detail::group1< detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> >
                   ( detail::group10<T1,T2,T3,T4,T5,T6,T7,T8,T9, Var&> 
                        (a1,a2,a3,a4,a5,a6,a7,a8,a9, var) 
                  );
}

        template<class T>  
        basic_format&   operator%(const T& x)
            { return io::detail::feed<CharT, Tr, Alloc, const T&>(*this,x); }

        template<class T>  basic_format&   operator%(T& x) 
            { return io::detail::feed<CharT, Tr, Alloc, T&>(*this,x); }

        basic_format&   operator%(const int& x)
            { return io::detail::feed<CharT, Tr, Alloc, const int&>(*this,x); }

        basic_format&   operator%(int& x)
            { return io::detail::feed<CharT, Tr, Alloc, int&>(*this,x); }

        int expected_args() const
            { return num_args_; }

        template<class T>
        basic_format&  bind_arg(int argN, const T& val) 
            { return io::detail::bind_arg_body(*this, argN, val); }

        template<class T> 
        basic_format&  modify_item(int itemN, T manipulator) 
            { return io::detail::modify_item_body<Ch,Tr, Alloc, T> (*this, itemN, manipulator);}

            format_error()  {}

            virtual const char *what() const throw() {
                return "boost::format_error: "
                    "format generic failure";
            }

            bad_format_string(std::size_t pos, std::size_t size) 
                : pos_(pos), next_(size) {}

            std::size_t get_pos() const { return pos_; }

            std::size_t get_next() const { return next_; }

            virtual const char *what() const throw() {
                return "boost::bad_format_string: format-string is ill-formed";
            }

            too_few_args(std::size_t cur, std::size_t expected) 
                : cur_(cur), expected_(expected) {}

            std::size_t get_cur() const { return cur_; }

            std::size_t get_expected() const { return expected_; }

            virtual const char *what() const throw() {
                return "boost::too_few_args: "
                    "format-string referred to more arguments than were passed";
            }

            too_many_args(std::size_t cur, std::size_t expected) 
                : cur_(cur), expected_(expected) {}

            std::size_t get_cur() const { return cur_; }

            std::size_t get_expected() const { return expected_; }

            virtual const char *what() const throw() {
                return "boost::too_many_args: "
                    "format-string referred to less arguments than were passed";
            }

            out_of_range(int index, int beg, int end) 
                : index_(index), beg_(beg), end_(end) {}

            int get_index() const { return index_; }

            int get_beg() const { return beg_; }

            int get_end() const { return end_; }

            virtual const char *what() const throw() {
                return "boost::out_of_range: "
                    "tried to refer to an argument (or item) number which"
                    " is out of range, according to the format string";
            }
