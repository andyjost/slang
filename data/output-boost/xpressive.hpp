

    sub_match()
      : std::pair<BidiIter, BidiIter>()
      , matched(false)
    {
    }


    sub_match(BidiIter first, BidiIter second, bool matched_ = false)
      : std::pair<BidiIter, BidiIter>(first, second)
      , matched(matched_)
    {
    }


    string_type str() const
    {
        return this->matched ? string_type(this->first, this->second) : string_type();
    }


    operator string_type() const
    {
        return this->matched ? string_type(this->first, this->second) : string_type();
    }


    difference_type length() const
    {
        return this->matched ? std::distance(this->first, this->second) : 0;
    }


    operator bool_type() const
    {
        return this->matched ? &dummy::i_ : 0;
    }


    bool operator !() const
    {
        return !this->matched;
    }

    int compare(string_type const &str) const
    {
        return this->str().compare(str);
    }

    int compare(sub_match const &sub) const
    {
        return this->str().compare(sub.str());
    }

template<typename BidiIter>
inline BidiIter range_begin(sub_match<BidiIter> &sub)
{
    return sub.first;
}

template<typename BidiIter>
inline BidiIter range_begin(sub_match<BidiIter> const &sub)
{
    return sub.first;
}

template<typename BidiIter>
inline BidiIter range_end(sub_match<BidiIter> &sub)
{
    return sub.second;
}

template<typename BidiIter>
inline BidiIter range_end(sub_match<BidiIter> const &sub)
{
    return sub.second;
}

inline syntax_option_type operator &(syntax_option_type b1, syntax_option_type b2)
{
    return static_cast<syntax_option_type>(
        static_cast<int>(b1) & static_cast<int>(b2));
}

inline syntax_option_type operator |(syntax_option_type b1, syntax_option_type b2)
{
    return static_cast<syntax_option_type>(static_cast<int>(b1) | static_cast<int>(b2));
}

inline syntax_option_type operator ^(syntax_option_type b1, syntax_option_type b2)
{
    return static_cast<syntax_option_type>(static_cast<int>(b1) ^ static_cast<int>(b2));
}

inline syntax_option_type operator ~(syntax_option_type b)
{
    return static_cast<syntax_option_type>(~static_cast<int>(b));
}

inline match_flag_type operator &(match_flag_type b1, match_flag_type b2)
{
    return static_cast<match_flag_type>(static_cast<int>(b1) & static_cast<int>(b2));
}

inline match_flag_type operator |(match_flag_type b1, match_flag_type b2)
{
    return static_cast<match_flag_type>(static_cast<int>(b1) | static_cast<int>(b2));
}

inline match_flag_type operator ^(match_flag_type b1, match_flag_type b2)
{
    return static_cast<match_flag_type>(static_cast<int>(b1) ^ static_cast<int>(b2));
}

inline match_flag_type operator ~(match_flag_type b)
{
    return static_cast<match_flag_type>(~static_cast<int>(b));
}

    bool operator()(std::type_info const *left, std::type_info const *right) const
    {
        return 0 != left->before(*right);
    }

    void operator ()(numeric::range_check_result result) const // throw(regex_error)
    {
        if(numeric::cInRange != result)
        {
            BOOST_THROW_EXCEPTION(
                regex_error(
                    regex_constants::error_escape
                  , "character escape too large to fit in target character type"
                )
            );
        }
    }

    case_converting_iterator(OutputIterator const &out, traits<Char> const *tr)
      : out_(out)
      , traits_(tr)
      , next_(op_none)
      , rest_(op_none)
    {}


    OutputIterator base() const
    {
        return this->out_;
    }


    case_converting_iterator &operator ++()
    {
        ++this->out_;
        this->next_ = op_none;
        return *this;
    }


    case_converting_iterator operator ++(int)
    {
        case_converting_iterator tmp(*this);
        ++*this;
        return tmp;
    }


    case_converting_iterator &operator *()
    {
        return *this;
    }


    case_converting_iterator &operator =(Char ch)
    {
        switch(this->next_ ? this->next_ : this->rest_)
        {
        case op_lower:
            ch = this->traits_->tolower(ch);
            break;

        case op_upper:
            ch = this->traits_->toupper(ch);
            break;

        default:;
        }

        *this->out_ = ch;
        return *this;
    }


template<typename Iterator>
inline bool set_transform(Iterator &, transform_op, transform_scope)
{
    return false;
}

    noop_output_iterator &operator ++()
    {
        return *this;
    }


    noop_output_iterator &operator ++(int)
    {
        return *this;
    }


    noop_output_iterator &operator *()
    {
        return *this;
    }


    noop_output_iterator &operator =(Char const &)
    {
        return *this;
    }

    match_results()
      : regex_id_(0)
      , sub_matches_()
      , base_()
      , prefix_()
      , suffix_()
      , nested_results_()
      , extras_ptr_()
      , traits_()
      , args_()
      , named_marks_()
    {
    }

    match_results(match_results<BidiIter> const &that)
      : regex_id_(that.regex_id_)
      , sub_matches_()
      , base_()
      , prefix_()
      , suffix_()
      , nested_results_()
      , extras_ptr_()
      , traits_()
      , args_(that.args_)
      , named_marks_(that.named_marks_)
    {
        if(that)
        {
            extras_type &extras = this->get_extras_();
            std::size_t size = that.sub_matches_.size();
            detail::sub_match_impl<BidiIter> *sub_matches = extras.sub_match_stack_.push_sequence(size, detail::sub_match_impl<BidiIter>(*that.base_), detail::fill);
            detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, sub_matches, size, that.sub_matches_);

            this->base_ = that.base_;
            this->prefix_ = that.prefix_;
            this->suffix_ = that.suffix_;
            // BUGBUG this doesn't share the extras::sequence_stack
            this->nested_results_ = that.nested_results_;
            this->traits_ = that.traits_;
        }
    }


    ~match_results()
    {
    }

    match_results<BidiIter> &operator =(match_results<BidiIter> const &that)
    {
        match_results<BidiIter>(that).swap(*this);
        return *this;
    }

    size_type size() const
    {
        return this->sub_matches_.size();
    }

    bool empty() const
    {
        return 0 == this->size();
    }

    difference_type length(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].length();
    }

    difference_type position(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].matched ? std::distance(*this->base_, this->sub_matches_[ sub ].first) : -1;
    }

    string_type str(size_type sub = 0) const
    {
        return this->sub_matches_[ sub ].str();
    }

    template<typename Sub>
    const_reference operator [](Sub const &sub) const
    {
        return this->at_(sub);
    }

    const_reference prefix() const
    {
        return this->prefix_ ? *this->prefix_ : this->sub_matches_[this->sub_matches_.size()];
    }

    const_reference suffix() const
    {
        return this->suffix_ ? *this->suffix_ : this->sub_matches_[this->sub_matches_.size()];
    }

    const_iterator begin() const
    {
        return this->sub_matches_.begin();
    }

    const_iterator end() const
    {
        return this->sub_matches_.end();
    }

    operator bool_type() const
    {
        return (!this->empty() && this->sub_matches_[ 0 ].matched) ? &dummy::i_ : 0;
    }

    bool operator !() const
    {
        return this->empty() || !this->sub_matches_[ 0 ].matched;
    }

    regex_id_type regex_id() const
    {
        return this->regex_id_;
    }

    void init_
    (
        regex_id_type regex_id
      , intrusive_ptr<detail::traits<char_type> const> const &tr
      , detail::sub_match_impl<BidiIter> *sub_matches
      , size_type size
      , std::vector<detail::named_mark<char_type> > const &named_marks
    )
    {
        this->traits_ = tr;
        this->regex_id_ = regex_id;
        this->named_marks_ = named_marks;
        detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, sub_matches, size);
    }

    extras_type &get_extras_()
    {
        if(!this->extras_ptr_)
        {
            this->extras_ptr_ = new extras_type;
        }

        return *this->extras_ptr_;
    }

    void set_prefix_suffix_(BidiIter begin, BidiIter end)
    {
        this->base_ = begin;
        this->prefix_ = sub_match<BidiIter>(begin, this->sub_matches_[ 0 ].first, begin != this->sub_matches_[ 0 ].first);
        this->suffix_ = sub_match<BidiIter>(this->sub_matches_[ 0 ].second, end, this->sub_matches_[ 0 ].second != end);

        typename nested_results_type::iterator ibegin = this->nested_results_.begin();
        typename nested_results_type::iterator iend = this->nested_results_.end();
        for( ; ibegin != iend; ++ibegin )
        {
            ibegin->set_prefix_suffix_(begin, end);
        }
    }

    void reset_()
    {
        detail::core_access<BidiIter>::init_sub_match_vector(this->sub_matches_, 0, 0);
    }

    void set_base_(BidiIter base)
    {
        this->base_ = base;

        typename nested_results_type::iterator ibegin = this->nested_results_.begin();
        typename nested_results_type::iterator iend = this->nested_results_.end();
        for( ; ibegin != iend; ++ibegin )
        {
            ibegin->set_base_(base);
        }
    }

    const_reference at_(size_type sub) const
    {
        return this->sub_matches_[ sub ];
    }

    template<typename OutputIterator, typename ForwardRange>
    OutputIterator format2_(OutputIterator out, ForwardRange const &result) const
    {
        return std::copy(boost::begin(result), boost::end(result), out);
    }

    template<typename OutputIterator, typename Char>
    OutputIterator format2_(OutputIterator out, Char const *const &result) const
    {
        Char const *tmp = result;
        BOOST_ASSERT(0 != tmp);
        for(; 0 != *tmp; ++tmp, ++out)
        {
            *out = *tmp;
        }
        return out;
    }

    template<typename OutputIterator, typename ForwardRange>
    OutputIterator format_
    (
        OutputIterator out
      , ForwardRange const &format
      , regex_constants::match_flag_type flags
      , mpl::size_t<0>
    ) const
    {
        typedef typename range_const_iterator<ForwardRange>::type iterator;
        iterator cur = boost::begin(format), end = boost::end(format);

        if(0 != (regex_constants::format_literal & flags))
        {
            return std::copy(cur, end, out);
        }
        else if(0 != (regex_constants::format_perl & flags))
        {
            return this->format_perl_(cur, end, out);
        }
        else if(0 != (regex_constants::format_sed & flags))
        {
            return this->format_sed_(cur, end, out);
        }
        else if(0 != (regex_constants::format_all & flags))
        {
            return this->format_all_(cur, end, out);
        }

        return this->format_ecma_262_(cur, end, out);
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_ecma_262_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                out = this->format_backref_(++cur, end, out);
                break;

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_sed_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '&'):
                ++cur;
                out = std::copy(this->sub_matches_[ 0 ].first, this->sub_matches_[ 0 ].second, out);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                out = this->format_escape_(++cur, end, out);
                break;

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_perl_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        detail::case_converting_iterator<OutputIterator, char_type> iout(out, this->traits_.get());

        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                iout = this->format_backref_(++cur, end, iout);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                if(++cur != end && BOOST_XPR_CHAR_(char_type, 'g') == *cur)
                {
                    iout = this->format_named_backref_(++cur, end, iout);
                }
                else
                {
                    iout = this->format_escape_(cur, end, iout);
                }
                break;

            default:
                *iout++ = *cur++;
                break;
            }
        }

        return iout.base();
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_all_(ForwardIterator cur, ForwardIterator end, OutputIterator out) const
    {
        detail::case_converting_iterator<OutputIterator, char_type> iout(out, this->traits_.get());
        iout = this->format_all_impl_(cur, end, iout);
        BOOST_XPR_ENSURE_(cur == end
          , regex_constants::error_paren, "unbalanced parentheses in format string");
        return iout.base();
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_all_impl_(ForwardIterator &cur, ForwardIterator end, OutputIterator out, bool metacolon = false) const
    {
        int max = 0, sub = 0;
        detail::noop_output_iterator<char_type> noop;

        while(cur != end)
        {
            switch(*cur)
            {
            case BOOST_XPR_CHAR_(char_type, '$'):
                out = this->format_backref_(++cur, end, out);
                break;

            case BOOST_XPR_CHAR_(char_type, '\\'):
                if(++cur != end && BOOST_XPR_CHAR_(char_type, 'g') == *cur)
                {
                    out = this->format_named_backref_(++cur, end, out);
                }
                else
                {
                    out = this->format_escape_(cur, end, out);
                }
                break;

            case BOOST_XPR_CHAR_(char_type, '('):
                out = this->format_all_impl_(++cur, end, out);
                BOOST_XPR_ENSURE_(BOOST_XPR_CHAR_(char_type, ')') == *(cur-1)
                  , regex_constants::error_paren, "unbalanced parentheses in format string");
                break;

            case BOOST_XPR_CHAR_(char_type, '?'):
                BOOST_XPR_ENSURE_(++cur != end
                  , regex_constants::error_subreg, "malformed conditional in format string");
                max = static_cast<int>(this->size() - 1);
                sub = detail::toi(cur, end, *this->traits_, 10, max);
                BOOST_XPR_ENSURE_(0 != sub, regex_constants::error_subreg, "invalid back-reference");
                if(this->sub_matches_[ sub ].matched)
                {
                    out = this->format_all_impl_(cur, end, out, true);
                    if(BOOST_XPR_CHAR_(char_type, ':') == *(cur-1))
                        this->format_all_impl_(cur, end, noop);
                }
                else
                {
                    this->format_all_impl_(cur, end, noop, true);
                    if(BOOST_XPR_CHAR_(char_type, ':') == *(cur-1))
                        out = this->format_all_impl_(cur, end, out);
                }
                return out;

            case BOOST_XPR_CHAR_(char_type, ':'):
                if(metacolon)
                {
            case BOOST_XPR_CHAR_(char_type, ')'):
                    ++cur;
                    return out;
                }
                // else fall-through

            default:
                *out++ = *cur++;
                break;
            }
        }

        return out;
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_backref_
    (
        ForwardIterator &cur
      , ForwardIterator end
      , OutputIterator out
    ) const
    {
        if(cur == end)
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '$');
        }
        else if(BOOST_XPR_CHAR_(char_type, '$') == *cur)
        {
            *out++ = *cur++;
        }
        else if(BOOST_XPR_CHAR_(char_type, '&') == *cur) // whole match
        {
            ++cur;
            out = std::copy(this->sub_matches_[ 0 ].first, this->sub_matches_[ 0 ].second, out);
        }
        else if(BOOST_XPR_CHAR_(char_type, '`') == *cur) // prefix
        {
            ++cur;
            out = std::copy(this->prefix().first, this->prefix().second, out);
        }
        else if(BOOST_XPR_CHAR_(char_type, '\'') == *cur) // suffix
        {
            ++cur;
            out = std::copy(this->suffix().first, this->suffix().second, out);
        }
        else if(-1 != this->traits_->value(*cur, 10)) // a sub-match
        {
            int max = static_cast<int>(this->size() - 1);
            int sub = detail::toi(cur, end, *this->traits_, 10, max);
            BOOST_XPR_ENSURE_(0 != sub, regex_constants::error_subreg, "invalid back-reference");
            if(this->sub_matches_[ sub ].matched)
                out = std::copy(this->sub_matches_[ sub ].first, this->sub_matches_[ sub ].second, out);
        }
        else
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '$');
            *out++ = *cur++;
        }

        return out;
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_escape_
    (
        ForwardIterator &cur
      , ForwardIterator end
      , OutputIterator out
    ) const
    {
        using namespace regex_constants;
        ForwardIterator tmp;
        // define an unsigned type the same size as char_type
        typedef typename boost::uint_t<CHAR_BIT * sizeof(char_type)>::least uchar_t;
        BOOST_MPL_ASSERT_RELATION(sizeof(uchar_t), ==, sizeof(char_type));
        typedef numeric::conversion_traits<uchar_t, int> converstion_traits;
        numeric::converter<int, uchar_t, converstion_traits, detail::char_overflow_handler_> converter;

        if(cur == end)
        {
            *out++ = BOOST_XPR_CHAR_(char_type, '\\');
            return out;
        }

        char_type ch = *cur++;
        switch(ch)
        {
        case BOOST_XPR_CHAR_(char_type, 'a'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\a');
            break;

        case BOOST_XPR_CHAR_(char_type, 'e'):
            *out++ = converter(27);
            break;

        case BOOST_XPR_CHAR_(char_type, 'f'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\f');
            break;

        case BOOST_XPR_CHAR_(char_type, 'n'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\n');
            break;

        case BOOST_XPR_CHAR_(char_type, 'r'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\r');
            break;

        case BOOST_XPR_CHAR_(char_type, 't'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\t');
            break;

        case BOOST_XPR_CHAR_(char_type, 'v'):
            *out++ = BOOST_XPR_CHAR_(char_type, '\v');
            break;

        case BOOST_XPR_CHAR_(char_type, 'x'):
            BOOST_XPR_ENSURE_(cur != end, error_escape, "unexpected end of format found");
            if(BOOST_XPR_CHAR_(char_type, '{') == *cur)
            {
                BOOST_XPR_ENSURE_(++cur != end, error_escape, "unexpected end of format found");
                tmp = cur;
                *out++ = converter(detail::toi(cur, end, *this->traits_, 16, 0xffff));
                BOOST_XPR_ENSURE_(4 == std::distance(tmp, cur) && cur != end && BOOST_XPR_CHAR_(char_type, '}') == *cur++
                  , error_escape, "invalid hex escape : must be \\x { HexDigit HexDigit HexDigit HexDigit }");
            }
            else
            {
                tmp = cur;
                *out++ = converter(detail::toi(cur, end, *this->traits_, 16, 0xff));
                BOOST_XPR_ENSURE_(2 == std::distance(tmp, cur), error_escape
                  , "invalid hex escape : must be \\x HexDigit HexDigit");
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'c'):
            BOOST_XPR_ENSURE_(cur != end, error_escape, "unexpected end of format found");
            BOOST_XPR_ENSURE_
            (
                this->traits_->in_range(BOOST_XPR_CHAR_(char_type, 'a'), BOOST_XPR_CHAR_(char_type, 'z'), *cur)
             || this->traits_->in_range(BOOST_XPR_CHAR_(char_type, 'A'), BOOST_XPR_CHAR_(char_type, 'Z'), *cur)
              , error_escape
              , "invalid escape control letter; must be one of a-z or A-Z"
            );
            // Convert to character according to ECMA-262, section 15.10.2.10:
            *out++ = converter(*cur % 32);
            ++cur;
            break;

        case BOOST_XPR_CHAR_(char_type, 'l'):
            if(!set_transform(out, detail::op_lower, detail::scope_next))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'l');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'L'):
            if(!set_transform(out, detail::op_lower, detail::scope_rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'L');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'u'):
            if(!set_transform(out, detail::op_upper, detail::scope_next))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'u');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'U'):
            if(!set_transform(out, detail::op_upper, detail::scope_rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'U');
            }
            break;

        case BOOST_XPR_CHAR_(char_type, 'E'):
            if(!set_transform(out, detail::op_none, detail::scope_rest))
            {
                *out++ = BOOST_XPR_CHAR_(char_type, 'E');
            }
            break;

        default:
            // BUGBUG what about backreferences like \12 ?
            if(0 < this->traits_->value(ch, 10))
            {
                int sub = this->traits_->value(ch, 10);
                if(this->sub_matches_[ sub ].matched)
                    out = std::copy(this->sub_matches_[ sub ].first, this->sub_matches_[ sub ].second, out);
            }
            else
            {
                *out++ = ch;
            }
            break;
        }

        return out;
    }

    template<typename ForwardIterator, typename OutputIterator>
    OutputIterator format_named_backref_
    (
        ForwardIterator &cur
      , ForwardIterator end
      , OutputIterator out
    ) const
    {
        using namespace regex_constants;
        BOOST_XPR_ENSURE_(cur != end && BOOST_XPR_CHAR_(char_type, '<') == *cur++
            , error_badmark, "invalid named back-reference");
        ForwardIterator begin = cur;
        for(; cur != end && BOOST_XPR_CHAR_(char_type, '>') != *cur; ++cur)
        {}
        BOOST_XPR_ENSURE_(cur != begin && cur != end && BOOST_XPR_CHAR_(char_type, '>') == *cur
            , error_badmark, "invalid named back-reference");

        string_type name(begin, cur++);
        for(std::size_t i = 0; i < this->named_marks_.size(); ++i)
        {
            if(this->named_marks_[i].name_ == name)
            {
                std::size_t sub = this->named_marks_[i].mark_nbr_;
                return std::copy(this->sub_matches_[ sub ].first, this->sub_matches_[ sub ].second, out);
            }
        }

        BOOST_THROW_EXCEPTION(regex_error(error_badmark, "invalid named back-reference"));
        // Should never get here
        return out;
    }

    regex_id_filter_predicate(regex_id_type regex_id)
      : regex_id_(regex_id)
    {
    }


    bool operator ()(match_results<BidiIter> const &res) const
    {
        return this->regex_id_ == res.regex_id();
    }


    regex_iterator_impl
    (
        BidiIter begin
      , BidiIter cur
      , BidiIter end
      , BidiIter next_search
      , basic_regex<BidiIter> const &rex
      , regex_constants::match_flag_type flags
      , bool not_null = false
    )
      : rex_(rex)
      , what_()
      , state_(begin, end, what_, *access::get_regex_impl(rex_), flags)
      , flags_(flags)
      , not_null_(not_null)
    {
        this->state_.cur_ = cur;
        this->state_.next_search_ = next_search;
    }


    bool next()
    {
        this->state_.reset(this->what_, *access::get_regex_impl(this->rex_));
        if(!regex_search_impl(this->state_, this->rex_, this->not_null_))
        {
            return false;
        }

        // Report position() correctly by setting the base different from prefix().first
        access::set_base(this->what_, this->state_.begin_);

        this->state_.cur_ = this->state_.next_search_ = this->what_[0].second;
        this->not_null_ = (0 == this->what_.length());

        return true;
    }


    bool equal_to(regex_iterator_impl<BidiIter> const &that) const
    {
        return this->rex_.regex_id()    == that.rex_.regex_id()
            && this->state_.begin_      == that.state_.begin_
            && this->state_.cur_        == that.state_.cur_
            && this->state_.end_        == that.state_.end_
            && this->flags_             == that.flags_
            ;
    }


    regex_iterator()
      : impl_()
    {
    }


    regex_iterator(regex_iterator<BidiIter> const &that)
      : impl_(that.impl_) // COW
    {
    }


    regex_iterator<BidiIter> &operator =(regex_iterator<BidiIter> const &that)
    {
        this->impl_ = that.impl_; // COW
        return *this;
    }


    regex_token_iterator_impl
    (
        BidiIter begin
      , BidiIter cur
      , BidiIter end
      , BidiIter next_search
      , basic_regex<BidiIter> const &rex
      , regex_constants::match_flag_type flags = regex_constants::match_default
      , std::vector<int> subs = std::vector<int>(1, 0)
      , int n = -2
      , bool not_null = false
    )
      : iter_(begin, cur, end, next_search, rex, flags, not_null)
      , result_()
      , n_((-2 == n) ? (int)subs.size() - 1 : n)
      , subs_()
    {
        BOOST_ASSERT(0 != subs.size());
        this->subs_.swap(subs);
    }


    bool next()
    {
        if(-1 != this->n_)
        {
            BidiIter cur = this->iter_.state_.cur_;
            if(0 != (++this->n_ %= (int)this->subs_.size()) || this->iter_.next())
            {
                this->result_ = (-1 == this->subs_[ this->n_ ])
                    ? this->iter_.what_.prefix()
                    : this->iter_.what_[ this->subs_[ this->n_ ] ];
                return true;
            }
            else if(-1 == this->subs_[ this->n_-- ] && cur != this->iter_.state_.end_)
            {
                this->result_ = value_type(cur, this->iter_.state_.end_, true);
                return true;
            }
        }

        return false;
    }


    bool equal_to(regex_token_iterator_impl<BidiIter> const &that) const
    {
        return this->iter_.equal_to(that.iter_) && this->n_ == that.n_;
    }


inline int get_mark_number(int i)
{
    return i;
}

    regex_token_iterator()
      : impl_()
    {
    }

    regex_token_iterator(regex_token_iterator<BidiIter> const &that)
      : impl_(that.impl_) // COW
    {
    }

    regex_token_iterator<BidiIter> &operator =(regex_token_iterator<BidiIter> const &that)
    {
        this->impl_ = that.impl_; // COW
        return *this;
    }


    explicit regex_compiler(RegexTraits const &traits = RegexTraits())
      : mark_count_(0)
      , hidden_mark_count_(0)
      , traits_(traits)
      , upper_(0)
      , self_()
      , rules_()
    {
        this->upper_ = lookup_classname(this->rxtraits(), "upper");
    }

    locale_type imbue(locale_type loc)
    {
        locale_type oldloc = this->traits_.imbue(loc);
        this->upper_ = lookup_classname(this->rxtraits(), "upper");
        return oldloc;
    }

    locale_type getloc() const
    {
        return this->traits_.getloc();
    }

    template<typename BidiIter>
    inline bool regex_match_impl
    (
        BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) begin
      , BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) end
      , match_results<BidiIter> &what
      , basic_regex<BidiIter> const &re
      , regex_constants::match_flag_type flags = regex_constants::match_default
    )
    {
        typedef detail::core_access<BidiIter> access;
        BOOST_ASSERT(0 != re.regex_id());

        // the state object holds matching state and
        // is passed by reference to all the matchers
        detail::match_state<BidiIter> state(begin, end, what, *access::get_regex_impl(re), flags);
        state.flags_.match_all_ = true;
        state.sub_match(0).begin_ = begin;

        if(access::match(re, state))
        {
            access::set_prefix_suffix(what, begin, end);
            return true;
        }

        // handle partial matches
        else if(state.found_partial_match_ && 0 != (flags & regex_constants::match_partial))
        {
            state.set_partial_match();
            return true;
        }

        access::reset(what);
        return false;
    }

template<typename BidiIter>
inline bool regex_match
(
    BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) begin
  , BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) end
  , match_results<BidiIter> &what
  , basic_regex<BidiIter> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    typedef detail::core_access<BidiIter> access;

    if(0 == re.regex_id())
    {
        access::reset(what);
        return false;
    }

    return detail::regex_match_impl(begin, end, what, re, flags);
}

template<typename BidiIter>
inline bool regex_search
(
    BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) begin
  , BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) end
  , match_results<BidiIter> &what
  , basic_regex<BidiIter> const &re
  , regex_constants::match_flag_type flags = regex_constants::match_default
)
{
    typedef detail::core_access<BidiIter> access;

    // a default-constructed regex matches nothing
    if(0 == re.regex_id())
    {
        access::reset(what);
        return false;
    }

    // the state object holds matching state and
    // is passed by reference to all the matchers
    detail::match_state<BidiIter> state(begin, end, what, *access::get_regex_impl(re), flags);
    return detail::regex_search_impl(state, re);
}

    template<typename OutIter, typename BidiIter, typename Formatter>
    inline OutIter regex_replace_impl
    (
        OutIter out
      , BidiIter begin
      , BidiIter end
      , basic_regex<BidiIter> const &re
      , Formatter const &format
      , regex_constants::match_flag_type flags = regex_constants::match_default
    )
    {
        using namespace regex_constants;
        typedef detail::core_access<BidiIter> access;
        BOOST_ASSERT(0 != re.regex_id());

        BidiIter cur = begin;
        match_results<BidiIter> what;
        detail::match_state<BidiIter> state(begin, end, what, *access::get_regex_impl(re), flags);
        bool const yes_copy = (0 == (flags & format_no_copy));

        if(detail::regex_search_impl(state, re))
        {
            if(yes_copy)
            {
                out = std::copy(cur, what[0].first, out);
            }

            out = what.format(out, format, flags);
            cur = state.cur_ = state.next_search_ = what[0].second;

            if(0 == (flags & format_first_only))
            {
                bool not_null = (0 == what.length());
                state.reset(what, *access::get_regex_impl(re));
                while(detail::regex_search_impl(state, re, not_null))
                {
                    if(yes_copy)
                    {
                        out = std::copy(cur, what[0].first, out);
                    }

                    access::set_prefix_suffix(what, begin, end);
                    out = what.format(out, format, flags);
                    cur = state.cur_ = state.next_search_ = what[0].second;
                    not_null = (0 == what.length());
                    state.reset(what, *access::get_regex_impl(re));
                }
            }
        }

        if(yes_copy)
        {
            out = std::copy(cur, end, out);
        }

        return out;
    }

template<typename OutIter, typename BidiIter, typename Formatter>
inline OutIter regex_replace
(
    OutIter out
  , BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) begin
  , BOOST_XPR_NONDEDUCED_TYPE_(BidiIter) end
  , basic_regex<BidiIter> const &re
  , Formatter const &format
  , regex_constants::match_flag_type flags = regex_constants::match_default
  , typename disable_if<detail::is_char_ptr<Formatter> >::type * = 0
)
{
    // Default-constructed regexes match nothing
    if(0 == re.regex_id())
    {
        if((0 == (flags & regex_constants::format_no_copy)))
        {
            out = std::copy(begin, end, out);
        }

        return out;
    }

    return detail::regex_replace_impl(out, begin, end, re, format, flags);
}

    explicit regex_error(regex_constants::error_type code, char const *str = "")
      : std::runtime_error(str)
      , boost::exception()
      , code_(code)
    {
    }

    regex_constants::error_type code() const
    {
        return this->code_;
    }

    virtual ~regex_error() throw()
    {}

    inline bool ensure_(
        bool cond
      , regex_constants::error_type code
      , char const *msg
      , char const *fun
      , char const *file
      , unsigned long line
    )
    {
        if(!cond)
        {
            #ifndef BOOST_EXCEPTION_DISABLE
            boost::throw_exception(
                boost::xpressive::regex_error(code, msg)
                    << boost::throw_function(fun)
                    << boost::throw_file(file)
                    << boost::throw_line((int)line)
            );
            #else
            boost::throw_exception(boost::xpressive::regex_error(code, msg));
            #endif
        }
        return true;
    }

    inline void throw_on_stack_error(bool stack_error)
    {
        BOOST_XPR_ENSURE_(!stack_error, regex_constants::error_stack, "Regex stack space exhausted");
    }

    basic_regex()
      : base_type()
    {
    }

    basic_regex(basic_regex<BidiIter> const &that)
      : base_type(that)
    {
    }

    basic_regex<BidiIter> &operator =(basic_regex<BidiIter> const &that)
    {
        proto::value(*this) = proto::value(that);
        return *this;
    }

    template<typename Expr>
    basic_regex(Expr const &expr)
      : base_type()
    {
        BOOST_XPRESSIVE_CHECK_REGEX(Expr, char_type);
        this->compile_(expr, is_valid_regex<Expr, char_type>());
    }

    template<typename Expr>
    basic_regex<BidiIter> &operator =(Expr const &expr)
    {
        BOOST_XPRESSIVE_CHECK_REGEX(Expr, char_type);
        this->compile_(expr, is_valid_regex<Expr, char_type>());
        return *this;
    }

    std::size_t mark_count() const
    {
        return proto::value(*this) ? proto::value(*this)->mark_count_ : 0;
    }

    regex_id_type regex_id() const
    {
        return proto::value(*this) ? proto::value(*this)->xpr_.get() : 0;
    }

    void swap(basic_regex<BidiIter> &that) // throw()
    {
        proto::value(*this).swap(proto::value(that));
    }

    template<typename InputIter>
    static basic_regex<BidiIter> compile(InputIter begin, InputIter end, flag_type flags = regex_constants::ECMAScript)
    {
        return regex_compiler<BidiIter>().compile(begin, end, flags);
    }

    template<typename InputRange>
    static basic_regex<BidiIter> compile(InputRange const &pat, flag_type flags = regex_constants::ECMAScript)
    {
        return regex_compiler<BidiIter>().compile(pat, flags);
    }

    bool match_(detail::match_state<BidiIter> &state) const
    {
        #if BOOST_XPRESSIVE_HAS_MS_STACK_GUARD
        bool success = false, stack_error = false;
        __try
        {
            success = proto::value(*this)->xpr_->match(state);
        }
        __except(_exception_code() == 0xC00000FDUL)
        {
            stack_error = true;
            _resetstkoflw();
        }
        detail::throw_on_stack_error(stack_error);
        return success;
        #else
        return proto::value(*this)->xpr_->match(state);
        #endif
    }

    template<typename Expr>
    void compile_(Expr const &expr, mpl::true_)
    {
        detail::static_compile(expr, proto::value(*this).get());
    }

template<typename BidiIter>
inline void swap(basic_regex<BidiIter> &left, basic_regex<BidiIter> &right) // throw()
{
    left.swap(right);
}


        template<typename Subs>
        int operator ()(Subs &subs, int i) const
        {
            subs.push_back(i);
            return i;
        }


        template<typename Expr>
        int operator ()(Expr const &expr) const
        {
            return expr.mark_number_;
        }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param
            ) const
            {
                result_type that = {{{state}}, expr};
                return that;
            }


        skip_directive(Skip const &skip)
          : skip_(proto::as_expr(skip))
        {}


        template<typename Expr>
        typename result<skip_directive(Expr)>::type
        operator ()(Expr const &expr) const
        {
            mpl::void_ ignore;
            typedef result<skip_directive(Expr)> result_fun;
            typename result_fun::type that = {
                typename result_fun::skip_transform()(proto::as_expr(expr), this->skip_, ignore)
              , {skip_}
            };
            return that;
        }


    static detail::basic_mark_tag make_tag(int mark_nbr)
    {
        detail::basic_mark_tag mark = {{mark_nbr}};
        return mark;
    }

    mark_tag(int mark_nbr)
      : base_type(mark_tag::make_tag(mark_nbr))
    {
        // Marks numbers must be integers greater than 0.
        BOOST_ASSERT(mark_nbr > 0);
    }

template<typename Skip>
detail::skip_directive<Skip> skip(Skip const &skip)
{
    return detail::skip_directive<Skip>(skip);
}

    inline void ignore_unused_regex_primitives()
    {
        detail::ignore_unused(repeat_max);
        detail::ignore_unused(inf);
        detail::ignore_unused(epsilon);
        detail::ignore_unused(nil);
        detail::ignore_unused(alnum);
        detail::ignore_unused(bos);
        detail::ignore_unused(eos);
        detail::ignore_unused(bol);
        detail::ignore_unused(eol);
        detail::ignore_unused(bow);
        detail::ignore_unused(eow);
        detail::ignore_unused(_b);
        detail::ignore_unused(_w);
        detail::ignore_unused(_d);
        detail::ignore_unused(_s);
        detail::ignore_unused(_n);
        detail::ignore_unused(_ln);
        detail::ignore_unused(_);
        detail::ignore_unused(self);
        detail::ignore_unused(set);
        detail::ignore_unused(s0);
        detail::ignore_unused(s1);
        detail::ignore_unused(s2);
        detail::ignore_unused(s3);
        detail::ignore_unused(s4);
        detail::ignore_unused(s5);
        detail::ignore_unused(s6);
        detail::ignore_unused(s7);
        detail::ignore_unused(s8);
        detail::ignore_unused(s9);
        detail::ignore_unused(a1);
        detail::ignore_unused(a2);
        detail::ignore_unused(a3);
        detail::ignore_unused(a4);
        detail::ignore_unused(a5);
        detail::ignore_unused(a6);
        detail::ignore_unused(a7);
        detail::ignore_unused(a8);
        detail::ignore_unused(a9);
        detail::ignore_unused(as_xpr);
    }


    regex_traits()
      : Impl()
    {
    }


    explicit regex_traits(locale_type const &loc)
      : Impl(loc)
    {
    }

template<typename Traits, std::size_t N>
inline typename Traits::char_class_type
lookup_classname(Traits const &traits, char const (&cname)[N], bool icase)
{
    typename Traits::char_type name[N] = {0};
    for(std::size_t j = 0; j < N-1; ++j)
    {
        name[j] = traits.widen(cname[j]);
    }
    return traits.lookup_classname(name, name + N - 1, icase);
}


            reference cast(void *pv) const
            {
                return *static_cast<UNREF(T) *>(pv);
            }

            value_wrapper()
              : value()
            {}


            value_wrapper(T const &t)
              : value(t)
            {}


            template<typename MatchResults, typename Expr>
            Expr const & operator ()(MatchResults &what, Expr const &expr) const
            {
                what.let(expr);
                return expr;
            }


        template<typename Args, typename BidiIter>
        void bind_args(let_<Args> const &args, match_results<BidiIter> &what)
        {
            BindArgs()(args, 0, what);
        }


            template<typename Cont, typename Idx>
            typename Cont::reference operator()(Cont &c, Idx idx BOOST_PROTO_DISABLE_IF_IS_CONST(Cont)) const
            {
                return c[idx];
            }


            template<typename Cont, typename Idx>
            typename Cont::const_reference operator()(Cont const &c, Idx idx) const
            {
                return c[idx];
            }


            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                seq.push(val);
            }


            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                seq.push_back(val);
            }


            template<typename Sequence, typename Value>
            void operator()(Sequence &seq, Value const &val) const
            {
                seq.push_front(val);
            }


            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                seq.pop();
            }


            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                seq.pop_back();
            }


            template<typename Sequence>
            void operator()(Sequence &seq) const
            {
                seq.pop_front();
            }


            template<typename Pair>
            typename Pair::first_type operator()(Pair const &p) const
            {
                return p.first;
            }


            template<typename Pair>
            typename Pair::second_type operator()(Pair const &p) const
            {
                return p.second;
            }


            template<typename Sub>
            bool operator()(Sub const &sub) const
            {
                return sub.matched;
            }


            template<typename Sub>
            typename Sub::difference_type operator()(Sub const &sub) const
            {
                return sub.length();
            }


            template<typename Sub>
            typename Sub::string_type operator()(Sub const &sub) const
            {
                return sub.str();
            }


            template<typename Value>
            T operator()(Value const &val) const
            {
                return boost::lexical_cast<T>(val);
            }

            template<typename RandIter>
            T impl(sub_match<RandIter> const &val, mpl::true_) const
            {
                return val.matched
                  ? boost::lexical_cast<T>(boost::make_iterator_range(&*val.first, &*val.first + (val.second - val.first)))
                  : boost::lexical_cast<T>("");
            }


            template<typename Value>
            T operator()(Value const &val) const
            {
                return static_cast<T>(val);
            }


            template<typename Value>
            T operator()(Value const &val) const
            {
                return dynamic_cast<T>(val);
            }


            template<typename Value>
            T operator()(Value const &val) const
            {
                return const_cast<T>(val);
            }


            T operator()() const
            {
                return T();
            }


            template<typename A0>
            T operator()(A0 const &a0) const
            {
                return T(a0);
            }


            template<typename A0, typename A1>
            T operator()(A0 const &a0, A1 const &a1) const
            {
                return T(a0, a1);
            }


            template<typename A0, typename A1, typename A2>
            T operator()(A0 const &a0, A1 const &a1, A2 const &a2) const
            {
                return T(a0, a1, a2);
            }


            void operator()() const
            {
                BOOST_THROW_EXCEPTION(Except());
            }


            template<typename A0>
            void operator()(A0 const &a0) const
            {
                BOOST_THROW_EXCEPTION(Except(a0));
            }


            template<typename A0, typename A1>
            void operator()(A0 const &a0, A1 const &a1) const
            {
                BOOST_THROW_EXCEPTION(Except(a0, a1));
            }


            template<typename A0, typename A1, typename A2>
            void operator()(A0 const &a0, A1 const &a1, A2 const &a2) const
            {
                BOOST_THROW_EXCEPTION(Except(a0, a1, a2));
            }


            template<typename T>
            T &operator()(boost::reference_wrapper<T> r) const
            {
                return static_cast<T &>(r);
            }


        value()
          : base_type()
        {}


        explicit value(T const &t)
          : base_type(base_type::proto_base_expr::make(t))
        {}


        T &get()
        {
            return proto::value(*this);
        }


        T const &get() const
        {
            return proto::value(*this);
        }


        explicit reference(T &t)
          : base_type(base_type::proto_base_expr::make(boost::ref(t)))
        {}


        T &get() const
        {
            return proto::value(*this).get();
        }


        local()
          : detail::value_wrapper<T>()
          , base_type(base_type::make(boost::ref(detail::value_wrapper<T>::value)))
        {}


        explicit local(T const &t)
          : detail::value_wrapper<T>(t)
          , base_type(base_type::make(boost::ref(detail::value_wrapper<T>::value)))
        {}


        T &get()
        {
            return proto::value(*this);
        }


        T const &get() const
        {
            return proto::value(*this);
        }

        inline void ignore_unused_regex_actions()
        {
            detail::ignore_unused(xpressive::at);
            detail::ignore_unused(xpressive::push);
            detail::ignore_unused(xpressive::push_back);
            detail::ignore_unused(xpressive::push_front);
            detail::ignore_unused(xpressive::pop);
            detail::ignore_unused(xpressive::pop_back);
            detail::ignore_unused(xpressive::pop_front);
            detail::ignore_unused(xpressive::top);
            detail::ignore_unused(xpressive::back);
            detail::ignore_unused(xpressive::front);
            detail::ignore_unused(xpressive::first);
            detail::ignore_unused(xpressive::second);
            detail::ignore_unused(xpressive::matched);
            detail::ignore_unused(xpressive::length);
            detail::ignore_unused(xpressive::str);
            detail::ignore_unused(xpressive::insert);
            detail::ignore_unused(xpressive::make_pair);
            detail::ignore_unused(xpressive::unwrap_reference);
            detail::ignore_unused(xpressive::check);
            detail::ignore_unused(xpressive::let);
        }


            int operator()(mark_placeholder m) const
            {
                return m.mark_number_;
            }

        explicit xpression_visitor_base(shared_ptr<regex_impl<BidiIter> > const &self)
          : self_(self)
        {
        }


        void swap(xpression_visitor_base<BidiIter> &that)
        {
            this->self_.swap(that.self_);
        }


        int get_hidden_mark()
        {
            return -(int)(++this->self_->hidden_mark_count_);
        }


        void mark_number(int mark_nbr)
        {
            if(0 < mark_nbr)
            {
                this->self_->mark_count_ =
                    (std::max)(this->self_->mark_count_, (std::size_t)mark_nbr);
            }
        }


        explicit xpression_visitor(Traits const &tr, shared_ptr<regex_impl<BidiIter> > const &self)
          : xpression_visitor_base<BidiIter>(self)
          , traits_(tr)
        {
        }


        template<typename Matcher>
        typename apply<Matcher>::type
        call(Matcher const &matcher)
        {
            this->visit_(matcher);
            return transmogrify<BidiIter, ICase, Traits, Matcher>::call(matcher, *this);
        }


        Traits const &traits() const
        {
            return this->traits_;
        }


        template<typename Expr>
        typename apply<Expr>::type const
        operator ()(Expr const &expr) const
        {
            typename apply<Expr>::type that = {{this->mod_}, proto::as_child(expr)};
            return that;
        }


        operator opt_type() const
        {
            return this->opt_;
        }

    template<typename Xpr, typename BidiIter, typename Traits>
    void static_compile_impl2(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl, Traits const &tr)
    {
        typedef typename iterator_value<BidiIter>::type char_type;
        impl->tracking_clear();
        impl->traits_ = new traits_holder<Traits>(tr);

        // "compile" the regex and wrap it in an xpression_adaptor.
        typedef xpression_visitor<BidiIter, mpl::false_, Traits> visitor_type;
        visitor_type visitor(tr, impl);
        intrusive_ptr<matchable_ex<BidiIter> const> adxpr = make_adaptor<matchable_ex<BidiIter> >(
            typename Grammar<char_type>::template impl<Xpr const &, end_xpression, visitor_type &>()(
                xpr
              , end_xpression()
              , visitor
            )
        );

        // Link and optimize the regex
        common_compile(adxpr, *impl, visitor.traits());

        // References changed, update dependencies.
        impl->tracking_update();
    }

    template<typename Xpr, typename BidiIter>
    void static_compile(Xpr const &xpr, shared_ptr<regex_impl<BidiIter> > const &impl)
    {
        static_compile_impl1(xpr, impl);
    }

    template<typename BidiIter>
    bool match(match_state<BidiIter> &state) const
    {
        return static_cast<Next const *>(this)->
            BOOST_NESTED_TEMPLATE push_match<Top>(state);
    }

    template<typename BidiIter>
    static bool top_match(match_state<BidiIter> &state, void const *top)
    {
        return static_cast<Top const *>(top)->
            BOOST_NESTED_TEMPLATE push_match<Top>(state);
    }

    template<typename BidiIter>
    static bool pop_match(match_state<BidiIter> &state, void const *top)
    {
        return static_cast<Top const *>(top)->match(state);
    }

    template<typename BidiIter>
    bool skip_match(match_state<BidiIter> &state) const
    {
        // could be static_xpression::skip_impl or stacked_xpression::skip_impl
        // depending on if there is 1 or more than 1 xpression on the
        // xpression stack
        return Top::skip_impl(*static_cast<Next const *>(this), state);
    }

    template<typename That, typename BidiIter>
    static bool skip_impl(That const &that, match_state<BidiIter> &state)
    {
        return that.BOOST_NESTED_TEMPLATE push_match<Top>(state);
    }

template<typename Top, typename Next>
inline stacked_xpression<Top, Next> const &stacked_xpression_cast(Next const &next)
{
    // NOTE: this is a little white lie. The "next" object doesn't really have
    // the type to which we're casting it. It is harmless, though. We are only using
    // the cast to decorate the next object with type information. It is done
    // this way to save stack space.
    BOOST_MPL_ASSERT_RELATION(sizeof(stacked_xpression<Top, Next>), ==, sizeof(Next));
    return *static_cast<stacked_xpression<Top, Next> const *>(&next);
}


    static_xpression(Matcher const &matcher = Matcher(), Next const &next = Next())
      : Matcher(matcher)
      , next_(next)
    {
    }

    template<typename BidiIter>
    bool match(match_state<BidiIter> &state) const
    {
        return this->Matcher::match(state, this->next_);
    }

    template<typename Top, typename BidiIter>
    bool push_match(match_state<BidiIter> &state) const
    {
        return this->Matcher::match(state, stacked_xpression_cast<Top>(this->next_));
    }

    template<typename That, typename BidiIter>
    static bool skip_impl(That const &that, match_state<BidiIter> &state)
    {
        return that.match(state);
    }

    template<typename Char>
    void link(xpression_linker<Char> &linker) const
    {
        linker.accept(*static_cast<Matcher const *>(this), &this->next_);
        this->next_.link(linker);
    }

    template<typename Char>
    void peek(xpression_peeker<Char> &peeker) const
    {
        this->peek_next_(peeker.accept(*static_cast<Matcher const *>(this)), peeker);
    }

    detail::width get_width() const
    {
        return this->get_width_(mpl::size_t<width>());
    }


    template<typename Char>
    void peek_next_(mpl::true_, xpression_peeker<Char> &peeker) const
    {
        this->next_.peek(peeker);
    }


    template<std::size_t Width>
    detail::width get_width_(mpl::size_t<Width>) const
    {
        return Width;
    }

template<typename Matcher>
inline static_xpression<Matcher> const
make_static(Matcher const &matcher)
{
    return static_xpression<Matcher>(matcher);
}


template<typename Matcher, typename Next>
inline static_xpression<Matcher, Next> const
make_static(Matcher const &matcher, Next const &next)
{
    return static_xpression<Matcher, Next>(matcher, next);
}


    template<typename Char>
    void link(xpression_linker<Char> &) const
    {
    }


    template<typename Char>
    void peek(xpression_peeker<Char> &peeker) const
    {
        peeker.fail();
    }


    detail::width get_width() const
    {
        return 0;
    }

    static Nbr nbr() { return Nbr(); }


        template<typename Matcher2, typename Visitor>
        static type call(Matcher2 const &m, Visitor &visitor)
        {
            return default_transmogrify::call_(m, visitor, is_char_literal<Matcher2, char_type>());
        }


        template<typename Matcher2, typename Visitor>
        static type call_(Matcher2 const &m, Visitor &visitor, mpl::true_)
        {
            char_type ch = char_cast<char_type>(m, visitor.traits());
            return type(ch, visitor.traits());
        }


        template<typename Matcher2>
        static Matcher2 const &call(Matcher2 const &m, dont_care)
        {
            return m;
        }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                int i = 0;
                return result_type(
                    typename Grammar::template impl<arg_type, end_xpr_type, Data>()(
                        proto::child(expr)
                      , IndependentEndXpression::impl<arg_type, int, int>()(proto::child(expr), i, i)
                      , data
                    )
                  , false
                );
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                int i = 0;
                xpr_type expr2 = typename Grammar::template impl<arg_type, end_xpr_type, Data>()(
                    proto::child(expr)
                  , IndependentEndXpression::impl<arg_type, int, int>()(proto::child(expr), i, i)
                  , data
                );
                std::size_t width = expr2.get_width().value();
                return result_type(expr2, width, false);
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                int i = 0;
                return result_type(
                    typename Grammar::template impl<arg_type, end_xpr_type, Data>()(
                        proto::child(expr)
                      , IndependentEndXpression::impl<arg_type, int, int>()(proto::child(expr), i, i)
                      , data
                    )
                );
            }

        static Nbr nbr() { return Nbr(); }


            result_type operator ()(proto::ignore, proto::ignore, proto::ignore) const
            {
                result_type that = {{}};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                return result_type(
                    proto::value(proto::left(expr)).nbr()
                  , proto::value(proto::right(expr))
                  , data.traits()
                );
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                begin_type begin;
                detail::attr_end_matcher end;
                result_type that = {{begin}, {expr, {end}}};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                int dummy = 0;
                marked_expr_type marked_expr =
                    InsertMark::impl<expr_type, State, Data>()(proto::left(expr), state, data);

                no_attr_type that = {
                    marked_expr
                  , {
                        matcher_type(
                            DeepCopy::impl<action_type, expr_type, int>()(
                                proto::right(expr)
                              , proto::left(expr)
                              , dummy
                            )
                          , proto::value(proto::left(marked_expr)).mark_number_
                        )
                    }
                };
                return InsertAttrs::impl<no_attr_type, State, Data>()(that, state, data);
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                visitor_type new_visitor(proto::value(proto::left(expr)).call(data));
                return typename Grammar::template impl<expr_type, State, visitor_type &>()(
                    proto::right(expr)
                  , state
                  , new_visitor
                );
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return result_type(
                    typename Grammar::template impl<Expr, State, Data>()(expr, state, data)
                  , state
                );
            }

        static T call(T t)
        {
            t.inverse();
            return t;
        }


        template<typename Matcher>
        typename inverter<Matcher>::type operator ()(Matcher const &matcher) const
        {
            return inverter<Matcher>::call(matcher);
        }


            alternates_list(Head const &head, Tail const &tail)
              : fusion::cons<Head, Tail>(head, tail)
            {
            }


                result_type operator ()(
                    typename impl::expr_param expr
                  , typename impl::state_param state
                  , typename impl::data_param data
                ) const
                {
                    return result_type(
                        typename Grammar::template impl<Expr, detail::alternate_end_xpression, Data>()(
                            expr
                          , detail::alternate_end_xpression()
                          , data
                        )
                      , state
                    );
                }


                result_type operator ()(
                    typename impl::expr_param expr
                  , typename impl::state_param state
                  , typename impl::data_param data
                ) const
                {
                    return result_type(
                        typename Grammar::template impl<Expr, State, Data>()(expr, state, data)
                    );
                }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                return data.call(proto::value(expr));
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                int mark_nbr = detail::get_mark_number(proto::left(expr));
                detail::mark_begin_matcher begin(mark_nbr);
                detail::mark_end_matcher end(mark_nbr);

                result_type that = {{begin}, {proto::right(expr), {end}}};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                xpr_type xpr = typename Grammar::template impl<arg_type, detail::true_xpression, Data>()(
                    proto::child(expr)
                  , detail::true_xpression()
                  , data
                );

                typedef typename impl::expr expr_type;
                matcher_type matcher(
                    xpr
                  , (uint_t)min_type<typename expr_type::proto_tag>::value
                  , (uint_t)max_type<typename expr_type::proto_tag>::value
                  , xpr.get_width().value()
                );

                return result_type::make(matcher);
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                // we're inserting a hidden mark ... so grab the next hidden mark number.
                int mark_nbr = data.get_hidden_mark();
                detail::mark_begin_matcher begin(mark_nbr);
                detail::mark_end_matcher end(mark_nbr);

                result_type that = {{begin}, {expr, {end}}};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                // Ensure this sub-expression is book-ended with mark matchers
                marked_sub_type marked_sub =
                    InsertMark::impl<xpr_type, State, Data>()(proto::child(expr), state, data);

                // Get the mark_number from the begin_mark_matcher
                int mark_number = proto::value(proto::left(marked_sub)).mark_number_;
                BOOST_ASSERT(0 != mark_number);

                typedef typename impl::expr expr_type;
                uint_t min_ = (uint_t)min_type<typename expr_type::proto_tag>();
                uint_t max_ = (uint_t)max_type<typename expr_type::proto_tag>();

                detail::repeat_begin_matcher begin(mark_number);
                detail::repeat_end_matcher<Greedy> end(mark_number, min_, max_);

                result_type that = {{begin}, {marked_sub, {end}}};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                return result_type(
                    typename Grammar::template impl<Expr, end_xpr, Data>()(expr, end_xpr(), data)
                );
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                int mark_number = proto::value(proto::left(expr)).mark_number_;

                return result_type(
                    typename Grammar::template impl<Expr, end_xpr, Data>()(expr, end_xpr(), data)
                  , mark_number
                );
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                result_type that = {expr};
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return typename other::template impl<Expr, State, Data>()(expr, state, data);
            }


    template<typename Char, typename Traits>
    void fill_list_set(Char *&, detail::set_initializer_type, Traits const &)
    {}


    template<typename Char, typename Expr, typename Traits>
    void fill_list_set(Char *&buffer, Expr const &expr, Traits const &traits)
    {
        fill_list_set(buffer, proto::left(expr), traits);
        *buffer++ = traits.translate(detail::char_cast<Char>(proto::value(proto::right(expr)), traits));
    }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                result_type set;
                typedef typename impl::data data_type;
                typename data_type::char_type *buffer = set.set_;
                fill_list_set(buffer, expr, data.traits());
                return set;
            }


        merge_charset(CharSet &charset, Data &data)
          : charset_(charset)
          , visitor_(data)
        {}


        template<typename Expr>
        void operator ()(Expr const &expr) const
        {
            this->call_(expr, typename Expr::proto_tag());
        }


        template<typename Expr, typename Tag>
        void call_(Expr const &expr, Tag) const
        {
            this->set_(
                typename Grammar::template impl<Expr const &, detail::end_xpression, Data &>()(
                    expr
                  , detail::end_xpression()
                  , this->visitor_
                )
            );
        }


        template<typename Not>
        void set_(detail::literal_matcher<traits_type, icase_type, Not> const &ch) const
        {
            // BUGBUG fixme!
            BOOST_MPL_ASSERT_NOT((Not));
            set_char(this->charset_.charset_, ch.ch_, this->visitor_.traits(), icase_type());
        }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param data
            ) const
            {
                result_type matcher;
                merge_charset<Grammar, result_type, typename impl::data> merge(matcher, data);
                merge(expr); // Walks the tree and fills in the charset
                return matcher;
            }

        virtual ~actionable() {}

        virtual void execute(action_args_type *) const {}


        actionable()
          : next(0)
        {}

    virtual ~finder() {}

    virtual bool ok_for_partial_matches() const { return true; }

    virtual ~traits() {}


    named_mark(string_type name, std::size_t mark_nbr)
      : name_(name)
      , mark_nbr_(mark_nbr)
    {}


    explicit traits_holder(Traits const &tr)
      : traits_(tr)
    {
    }


    Traits const &traits() const
    {
        return this->traits_;
    }


    char_type tolower(char_type ch) const
    {
        return this->tolower_(ch, typename Traits::version_tag());
    }


    char_type toupper(char_type ch) const
    {
        return this->toupper_(ch, typename Traits::version_tag());
    }


    int value(char_type ch, int radix) const
    {
        return this->traits_.value(ch, radix);
    }


    bool in_range(char_type from, char_type to, char_type ch) const
    {
        return this->traits_.in_range(from, to, ch);
    }

    char_type tolower_(char_type ch, regex_traits_version_1_tag) const
    {
        return ch;
    }


    char_type toupper_(char_type ch, regex_traits_version_1_tag) const
    {
        return ch;
    }


    regex_impl()
      : enable_reference_tracking<regex_impl<BidiIter> >()
      , xpr_()
      , traits_()
      , finder_()
      , named_marks_()
      , mark_count_(0)
      , hidden_mark_count_(0)
    {
        #ifdef BOOST_XPRESSIVE_DEBUG_CYCLE_TEST
        ++instances;
        #endif
    }


    regex_impl(regex_impl<BidiIter> const &that)
      : enable_reference_tracking<regex_impl<BidiIter> >(that)
      , xpr_(that.xpr_)
      , traits_(that.traits_)
      , finder_(that.finder_)
      , named_marks_(that.named_marks_)
      , mark_count_(that.mark_count_)
      , hidden_mark_count_(that.hidden_mark_count_)
    {
        #ifdef BOOST_XPRESSIVE_DEBUG_CYCLE_TEST
        ++instances;
        #endif
    }


    ~regex_impl()
    {
        #ifdef BOOST_XPRESSIVE_DEBUG_CYCLE_TEST
        --instances;
        #endif
    }


    void swap(regex_impl<BidiIter> &that)
    {
        enable_reference_tracking<regex_impl<BidiIter> >::swap(that);
        this->xpr_.swap(that.xpr_);
        this->traits_.swap(that.traits_);
        this->finder_.swap(that.finder_);
        this->named_marks_.swap(that.named_marks_);
        std::swap(this->mark_count_, that.mark_count_);
        std::swap(this->hidden_mark_count_, that.hidden_mark_count_);
    }


template<typename BidiIter>
void swap(regex_impl<BidiIter> &left, regex_impl<BidiIter> &right)
{
    left.swap(right);
}


    xpression_adaptor(Xpr const &xpr)
    #if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))                          \
      && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
        // Ugh, gcc has an optimizer bug which elides this c'tor call
        // resulting in pure virtual function calls.
        __attribute__((__noinline__))
    #endif
      : xpr_(xpr)
    {
    }


    virtual bool match(match_state<iterator_type> &state) const
    {
        typedef typename boost::unwrap_reference<Xpr const>::type xpr_type;
        return implicit_cast<xpr_type &>(this->xpr_).match(state);
    }


    void link(xpression_linker<char_type> &linker) const
    {
        this->xpr_.link(linker);
    }


    void peek(xpression_peeker<char_type> &peeker) const
    {
        this->xpr_.peek(peeker);
    }


    boyer_moore_finder(char_type const *begin, char_type const *end, Traits const &tr, bool icase)
      : bm_(begin, end, tr, icase)
    {
    }


    bool ok_for_partial_matches() const
    {
        return false;
    }


    bool operator ()(match_state<BidiIter> &state) const
    {
        Traits const &tr = traits_cast<Traits>(state);
        state.cur_ = this->bm_.find(state.cur_, state.end_, tr);
        return state.cur_ != state.end_;
    }


    hash_peek_finder(hash_peek_bitset<char_type> const &bset)
      : bset_(bset)
    {
    }


    bool operator ()(match_state<BidiIter> &state) const
    {
        Traits const &tr = traits_cast<Traits>(state);
        state.cur_ = (this->bset_.icase()
            ? this->find_(state.cur_, state.end_, tr, mpl::true_())
            : this->find_(state.cur_, state.end_, tr, mpl::false_()));
        return state.cur_ != state.end_;
    }


    template<typename ICase>
    BidiIter find_(BidiIter begin, BidiIter end, Traits const &tr, ICase) const
    {
        for(; begin != end && !this->bset_.test(*begin, tr, ICase()); ++begin)
            ;
        return begin;
    }


    line_start_finder(Traits const &tr)
      : newline_(lookup_classname(tr, "newline"))
    {
    }


    bool operator ()(match_state<BidiIter> &state) const
    {
        if(state.bos() && state.flags_.match_bol_)
        {
            return true;
        }

        Traits const &tr = traits_cast<Traits>(state);
        BidiIter cur = state.cur_;
        BidiIter const end = state.end_;
        std::advance(cur, static_cast<diff_type>(-!state.bos()));

        for(; cur != end; ++cur)
        {
            if(tr.isctype(*cur, this->newline_))
            {
                state.cur_ = ++cur;
                return true;
            }
        }

        return false;
    }


    line_start_finder(Traits const &tr)
    {
        char_class_type newline = lookup_classname(tr, "newline");
        for(int j = 0; j < 256; ++j)
        {
            this->bits_[j] = tr.isctype(static_cast<char_type>(static_cast<unsigned char>(j)), newline);
        }
    }


    bool operator ()(match_state<BidiIter> &state) const
    {
        if(state.bos() && state.flags_.match_bol_)
        {
            return true;
        }

        BidiIter cur = state.cur_;
        BidiIter const end = state.end_;
        std::advance(cur, static_cast<diff_type>(-!state.bos()));

        for(; cur != end; ++cur)
        {
            if(this->bits_[static_cast<unsigned char>(*cur)])
            {
                state.cur_ = ++cur;
                return true;
            }
        }

        return false;
    }

    leading_simple_repeat_finder()
      : finder<BidiIter>()
    {}


    bool operator ()(match_state<BidiIter> &state) const
    {
        state.cur_ = state.next_search_;
        return true;
    }


    template<typename Visitor>
    static typename apply<Visitor>::type
    call(Visitor &visitor)
    {
        return typename apply<Visitor>::type(visitor.traits(), visitor.self());
    }


    locale_modifier(Locale const &loc)
      : loc_(loc)
    {
    }


    template<typename Visitor>
    typename apply<Visitor>::type
    call(Visitor &visitor) const
    {
        return typename apply<Visitor>::type(this->loc_, visitor.self());
    }


    Locale getloc() const
    {
        return this->loc_;
    }

    template<typename Traits>
    explicit xpression_linker(Traits const &tr)
      : back_stack_()
      , traits_(&tr)
      , traits_type_(&typeid(Traits))
      , has_backrefs_(false)
    {
    }


    template<typename Matcher>
    void accept(Matcher const &, void const *)
    {
        // no-op
    }

    bool has_backrefs() const
    {
        return this->has_backrefs_;
    }

    template<typename Xpr>
    void alt_branch_link(Xpr const &xpr, void const *next, xpression_peeker<Char> *peeker)
    {
        this->back_stack_.push(next);
        xpr.link(*this);
        xpr.peek(*peeker);
    }


        alt_link_pred
        (
            xpression_linker<Char> *linker
          , xpression_peeker<Char> *peeker
          , void const *next
        )
          : linker_(linker)
          , peeker_(peeker)
          , next_(next)
        {
        }


        template<typename Xpr>
        void operator ()(Xpr const &xpr) const
        {
            this->linker_->alt_branch_link(xpr, this->next_, this->peeker_);
        }


    template<typename BidiIter>
    void alt_link
    (
        alternates_vector<BidiIter> const &alternates
      , void const *next
      , xpression_peeker<Char> *peeker
    )
    {
        std::for_each(alternates.begin(), alternates.end(), alt_link_pred(this, peeker, next));
    }


    template<typename Traits>
    Traits const &get_traits() const
    {
        BOOST_ASSERT(*this->traits_type_ == typeid(Traits));
        return *static_cast<Traits const *>(this->traits_);
    }


    static std::size_t get_hidden_mark_count(basic_regex<BidiIter> const &rex)
    {
        return proto::value(rex)->hidden_mark_count_;
    }


    static bool match(basic_regex<BidiIter> const &rex, match_state<BidiIter> &state)
    {
        return rex.match_(state);
    }


    sub_match_impl(BidiIter const &begin)
      : sub_match<BidiIter>(begin, begin)
      , repeat_count_(0)
      , begin_(begin)
      , zero_width_(false)
    {
    }

            explicit node(T const &value)
              : _value(value)
            {}

            list_iterator(list_iterator<> const &it) : _node(it._node) {}

            explicit list_iterator(node_base *n = 0) : _node(n) {}

            Ref dereference() const { return static_cast<node *>(_node)->_value; }

            void increment() { _node = _node->_next; }

            void decrement() { _node = _node->_prev; }

            bool equal(list_iterator const &it) const { return _node == it._node; }


        list()
        {
            _sentry._next = _sentry._prev = &_sentry;
        }


        list(list const &that)
        {
            _sentry._next = _sentry._prev = &_sentry;
            const_iterator it = that.begin(), e = that.end();
            for( ; it != e; ++it)
                push_back(*it);
        }


        list &operator =(list const &that)
        {
            list(that).swap(*this);
            return *this;
        }


        ~list()
        {
            clear();
        }


        void clear()
        {
            while(!empty())
                pop_front();
        }


        void swap(list &that) // throw()
        {
            list temp;
            temp.splice(temp.begin(), that);  // move that to temp
            that.splice(that.begin(), *this); // move this to that
            splice(begin(), temp);            // move temp to this
        }


        void push_front(T const &t)
        {
            node *new_node = new node(t);

            new_node->_next = _sentry._next;
            new_node->_prev = &_sentry;

            _sentry._next->_prev = new_node;
            _sentry._next = new_node;
        }


        void push_back(T const &t)
        {
            node *new_node = new node(t);

            new_node->_next = &_sentry;
            new_node->_prev = _sentry._prev;

            _sentry._prev->_next = new_node;
            _sentry._prev = new_node;
        }


        void pop_front()
        {
            BOOST_ASSERT(!empty());
            node *old_node = static_cast<node *>(_sentry._next);
            _sentry._next = old_node->_next;
            _sentry._next->_prev = &_sentry;
            delete old_node;
        }


        void pop_back()
        {
            BOOST_ASSERT(!empty());
            node *old_node = static_cast<node *>(_sentry._prev);
            _sentry._prev = old_node->_prev;
            _sentry._prev->_next = &_sentry;
            delete old_node;
        }


        bool empty() const
        {
            return _sentry._next == &_sentry;
        }


        void splice(iterator it, list &x)
        {
            if(x.empty())
                return;

            x._sentry._prev->_next = it._node;
            x._sentry._next->_prev = it._node->_prev;

            it._node->_prev->_next = x._sentry._next;
            it._node->_prev = x._sentry._prev;

            x._sentry._prev = x._sentry._next = &x._sentry;
        }


        void splice(iterator it, list &, iterator xit)
        {
            xit._node->_prev->_next = xit._node->_next;
            xit._node->_next->_prev = xit._node->_prev;

            xit._node->_next = it._node;
            xit._node->_prev = it._node->_prev;

            it._node->_prev = it._node->_prev->_next = xit._node;
        }


        reference front()
        {
            BOOST_ASSERT(!empty());
            return static_cast<node *>(_sentry._next)->_value;
        }


        const_reference front() const
        {
            BOOST_ASSERT(!empty());
            return static_cast<node *>(_sentry._next)->_value;
        }


        reference back()
        {
            BOOST_ASSERT(!empty());
            return static_cast<node *>(_sentry._prev)->_value;
        }


        const_reference back() const
        {
            BOOST_ASSERT(!empty());
            return static_cast<node *>(_sentry._prev)->_value;
        }


        iterator begin()
        {
            return iterator(_sentry._next);
        }


        const_iterator begin() const
        {
            return const_iterator(_sentry._next);
        }


        iterator end()
        {
            return iterator(&_sentry);
        }


        const_iterator end() const
        {
            return const_iterator(const_cast<node_base *>(&_sentry));
        }


        size_type size() const
        {
            return static_cast<size_type>(std::distance(begin(), end()));
        }


    template<typename T>
    void swap(list<T> &lhs, list<T> &rhs)
    {
        lhs.swap(rhs);
    }


    match_context()
      : results_ptr_(0)
      , prev_context_(0)
      , next_ptr_(0)
      , traits_(0)
    {
    }


    explicit match_flags(regex_constants::match_flag_type flags)
      : match_all_(false)
      , match_prev_avail_(0 != (flags & regex_constants::match_prev_avail))
      , match_bol_(match_prev_avail_ || 0 == (flags & regex_constants::match_not_bol))
      , match_eol_(0 == (flags & regex_constants::match_not_eol))
      , match_not_bow_(!match_prev_avail_ && 0 != (flags & regex_constants::match_not_bow))
      , match_not_eow_(0 != (flags & regex_constants::match_not_eow))
      , match_not_null_(0 != (flags & regex_constants::match_not_null))
      , match_continuous_(0 != (flags & regex_constants::match_continuous))
      , match_partial_(0 != (flags & regex_constants::match_partial))
    {
    }

    match_state
    (
        BidiIter begin
      , BidiIter end
      , match_results &what
      , regex_impl const &impl
      , regex_constants::match_flag_type flags
    )
      : cur_(begin)
      , sub_matches_(0)
      , mark_count_(0)
      , begin_(begin)
      , end_(end)
      , flags_(flags)
      , found_partial_match_(false)
      , context_() // zero-initializes the fields of context_
      , extras_(&core_access<BidiIter>::get_extras(what))
      , action_list_()
      , action_list_tail_(&action_list_.next)
      , action_args_(&core_access<BidiIter>::get_action_args(what))
      , attr_context_() // zero-initializes the fields of attr_context_
      , next_search_(begin)
    {
        // reclaim any cached memory in the match_results struct
        this->extras_->sub_match_stack_.unwind();

        // initialize the context_ struct
        this->init_(impl, what);

        // move all the nested match_results structs into the match_results cache
        this->extras_->results_cache_.reclaim_all(access::get_nested_results(what));
    }

    void reset(match_results &what, regex_impl const &impl)
    {
        this->extras_ = &core_access<BidiIter>::get_extras(what);
        this->action_list_.next = 0;
        this->action_list_tail_ = &action_list_.next;
        this->action_args_ = &core_access<BidiIter>::get_action_args(what);
        this->attr_context_ = attr_context();
        this->context_.prev_context_ = 0;
        this->found_partial_match_ = false;
        this->extras_->sub_match_stack_.unwind();
        this->init_(impl, what);
        this->extras_->results_cache_.reclaim_all(access::get_nested_results(what));
    }

    match_context push_context(regex_impl const &impl, matchable const &next, match_context &prev)
    {
        // save state
        match_context context = this->context_;

        // create a new nested match_results for this regex
        nested_results<BidiIter> &nested = access::get_nested_results(*context.results_ptr_);
        match_results &what = this->extras_->results_cache_.append_new(nested);

        // (re)initialize the match context
        this->init_(impl, what);

        // create a linked list of match_context structs
        this->context_.prev_context_ = &prev;
        this->context_.next_ptr_ = &next;

        // record the start of the zero-th sub-match
        this->sub_matches_[0].begin_ = this->cur_;

        return context;
    }

    bool pop_context(regex_impl const &impl, bool success)
    {
        match_context &context = *this->context_.prev_context_;
        if(!success)
        {
            match_results &what = *context.results_ptr_;
            this->uninit_(impl, what);

            // send the match_results struct back to the cache
            nested_results<BidiIter> &nested = access::get_nested_results(what);
            this->extras_->results_cache_.reclaim_last(nested);
        }

        // restore the state
        this->context_ = context;
        match_results &results = *this->context_.results_ptr_;
        this->sub_matches_ = access::get_sub_matches(access::get_sub_match_vector(results));
        this->mark_count_ = results.size();
        return success;
    }

    void swap_context(match_context &context)
    {
        std::swap(this->context_, context);
        match_results &results = *this->context_.results_ptr_;
        this->sub_matches_ = access::get_sub_matches(access::get_sub_match_vector(results));
        this->mark_count_ = results.size();
    }

    bool bos() const
    {
        return this->cur_ == this->begin_;
    }

    bool eos()
    {
        return this->cur_ == this->end_ && this->found_partial_match();
    }

    bool is_active_regex(regex_impl const &impl) const
    {
        return impl.xpr_.get() == this->context_.results_ptr_->regex_id();
    }

    sub_match_impl &sub_match(int n)
    {
        return this->sub_matches_[n];
    }

    void set_partial_match()
    {
        sub_match_impl &sub0 = this->sub_match(0);
        sub0.first = sub0.begin_;
        sub0.second = this->end_;
        sub0.matched = false;
    }


    template<typename Traits>
    Traits const &get_traits() const
    {
        return static_cast<traits_holder<Traits> const *>(this->context_.traits_)->traits();
    }


    void init_(regex_impl const &impl, match_results &what)
    {
        regex_id_type const id = impl.xpr_.get();
        std::size_t const total_mark_count = impl.mark_count_ + impl.hidden_mark_count_ + 1;

        // initialize the context and the sub_match vector
        this->context_.results_ptr_ = &what;
        this->context_.traits_ = impl.traits_.get();
        this->mark_count_ = impl.mark_count_ + 1;
        this->sub_matches_ = this->extras_->sub_match_stack_.push_sequence(total_mark_count, sub_match_impl(begin_), detail::fill);
        this->sub_matches_ += impl.hidden_mark_count_;

        // initialize the match_results struct
        access::init_match_results(what, id, impl.traits_, this->sub_matches_, this->mark_count_, impl.named_marks_);
    }


    void uninit_(regex_impl const &impl, match_results &)
    {
        extras_->sub_match_stack_.unwind_to(this->sub_matches_ - impl.hidden_mark_count_);
    }


    bool found_partial_match()
    {
        this->found_partial_match_ = true;
        return true;
    }

template<typename BidiIter>
inline memento<BidiIter> save_sub_matches(match_state<BidiIter> &state)
{
    memento<BidiIter> mem =
    {
        state.extras_->sub_match_stack_.push_sequence(state.mark_count_, sub_match_impl<BidiIter>(state.begin_))
      , state.context_.results_ptr_->nested_results().size()
      , state.action_list_.next
      , state.action_list_tail_
      , state.attr_context_
    };
    state.action_list_.next = 0;
    state.action_list_tail_ = &state.action_list_.next;
    std::copy(state.sub_matches_, state.sub_matches_ + state.mark_count_, mem.old_sub_matches_);
    return mem;
}

template<typename BidiIter>
inline void restore_action_queue(memento<BidiIter> const &mem, match_state<BidiIter> &state)
{
    state.action_list_.next = mem.action_list_head_;
    state.action_list_tail_ = mem.action_list_tail_;
    *state.action_list_tail_ = 0;
}

template<typename BidiIter>
inline void restore_sub_matches(memento<BidiIter> const &mem, match_state<BidiIter> &state)
{
    typedef core_access<BidiIter> access;
    nested_results<BidiIter> &nested = access::get_nested_results(*state.context_.results_ptr_);
    std::size_t count = nested.size() - mem.nested_results_count_;
    state.extras_->results_cache_.reclaim_last_n(nested, count);
    std::copy(mem.old_sub_matches_, mem.old_sub_matches_ + state.mark_count_, state.sub_matches_);
    state.extras_->sub_match_stack_.unwind_to(mem.old_sub_matches_);
    state.attr_context_ = mem.attr_context_;
}

template<typename BidiIter>
inline void reclaim_sub_matches(memento<BidiIter> const &mem, match_state<BidiIter> &state, bool success)
{
    std::size_t count = state.context_.results_ptr_->nested_results().size() - mem.nested_results_count_;
    if(count == 0)
    {
        state.extras_->sub_match_stack_.unwind_to(mem.old_sub_matches_);
    }
    // else we have we must orphan this block of backrefs because we are using the stack
    // space above it.

    if(!success)
    {
        state.attr_context_ = mem.attr_context_;
    }
}

template<typename Traits, typename BidiIter>
inline Traits const &traits_cast(match_state<BidiIter> const &state)
{
    return state.template get_traits<Traits>();
}

    inline void ignore_unused_icase()
    {
        detail::ignore_unused(icase);
    }


    sub_match_vector()
      : size_(0)
      , sub_matches_(0)
    {
    }


    const_reference operator [](size_type index) const
    {
        static value_type const s_null;
        return (index >= this->size_)
            ? s_null
            : *static_cast<value_type const *>(&this->sub_matches_[ index ]);
    }


    size_type size() const
    {
        return this->size_;
    }


    bool empty() const
    {
        return 0 == this->size();
    }


    const_iterator begin() const
    {
        return const_iterator(this->sub_matches_);
    }


    const_iterator end() const
    {
        return const_iterator(this->sub_matches_ + this->size_);
    }


    operator bool_type() const
    {
        return (!this->empty() && (*this)[0].matched) ? &dummy::i_ : 0;
    }


    bool operator !() const
    {
        return this->empty() || !(*this)[0].matched;
    }


    void swap(sub_match_vector<BidiIter> &that)
    {
        std::swap(this->size_, that.size_);
        std::swap(this->sub_matches_, that.sub_matches_);
    }


    void init_(sub_match_impl<BidiIter> *sub_matches, size_type size)
    {
        this->size_ = size;
        this->sub_matches_ = sub_matches;
    }


    char_sink(hash_peek_bitset<char_type> &bset, Traits const &tr)
      : bset_(bset)
      , traits_(tr)
    {}


    void operator()(char_type ch) const
    {
        this->bset_.set_char(ch, ICase, this->traits_);
    }

    template<typename Traits>
    xpression_peeker(hash_peek_bitset<Char> &bset, Traits const &tr, bool has_backrefs = false)
      : bset_(bset)
      , str_()
      , line_start_(false)
      , traits_(0)
      , traits_type_(0)
      , leading_simple_repeat_(0)
      , has_backrefs_(has_backrefs)
    {
        this->set_traits(tr);
    }

    peeker_string<Char> const &get_string() const
    {
        return this->str_;
    }


    bool line_start() const
    {
        return this->line_start_;
    }


    bool leading_simple_repeat() const
    {
        return 0 < this->leading_simple_repeat_;
    }


    template<typename Traits>
    Traits const &get_traits_() const
    {
        BOOST_ASSERT(!!(*this->traits_type_ == typeid(Traits)));
        return *static_cast<Traits const *>(this->traits_);
    }


    static detail::width get_width()
    {
        return width;
    }


        explicit char_translate(Traits const &tr)
          : traits_(tr)
        {}


        char_type operator ()(char_type ch1) const
        {
            return this->traits_.translate(ch1);
        }


        explicit char_translate(Traits const &tr)
          : traits_(tr)
        {}


        char_type operator ()(char_type ch1) const
        {
            return this->traits_.translate_nocase(ch1);
        }


        attr_matcher(int slot, Matcher const &matcher, Traits const& tr)
          : slot_(slot-1)
        {
            char_translate<Traits, ICase::value> trans(tr);
            this->sym_.load(matcher, trans);
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BidiIter tmp = state.cur_;
            char_translate<Traits, ICase::value> trans(traits_cast<Traits>(state));
            result_type const &result = this->sym_(state.cur_, state.end_, trans);
            if(result)
            {
                void const *old_slot = state.attr_context_.attr_slots_[this->slot_];
                state.attr_context_.attr_slots_[this->slot_] = &*result;
                if(next.match(state))
                {
                    return true;
                }
                state.attr_context_.attr_slots_[this->slot_] = old_slot;
            }
            state.cur_ = tmp;
            return false;
        }


        mark_begin_matcher(int mark_number)
          : mark_number_(mark_number)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            sub_match_impl<BidiIter> &br = state.sub_match(this->mark_number_);

            BidiIter old_begin = br.begin_;
            br.begin_ = state.cur_;

            if(next.match(state))
            {
                return true;
            }

            br.begin_ = old_begin;
            return false;
        }

        explicit action_context(action_args_type *action_args)
          : action_args_(action_args)
        {}

            result_type operator()(Expr &expr, action_context const &) const
            {
                return proto::value(expr);
            }


            result_type operator ()(Expr const &expr, action_context const &ctx) const
            {
                return proto::value(proto::left(proto::child(expr))).t_
                    ? *proto::value(proto::left(proto::child(expr))).t_
                    :  proto::eval(proto::right(proto::child(expr)), ctx);
            }

        action(Actor const &actor)
          : actionable()
          , actor_(actor)
        {
        }


        virtual void execute(action_args_type *action_args) const
        {
            action_context const ctx(action_args);
            proto::eval(this->actor_, ctx);
        }


            result_type operator ()(
                typename impl::expr_param
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return result_type::make(state.sub_matches_[ data ]);
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param
            ) const
            {
                return result_type::make(state.sub_matches_[ proto::value(expr).mark_number_ ]);
            }


        opt(T const *t)
          : t_(t)
        {}


        operator reference() const
        {
            BOOST_XPR_ENSURE_(0 != this->t_, regex_constants::error_badattr, "Use of uninitialized regex attribute");
            return *this->t_;
        }


            result_type operator ()(
                typename impl::expr_param
              , typename impl::state_param state
              , typename impl::data_param
            ) const
            {
                int slot = typename expr_type::proto_child0::nbr_type();
                attr_type const *attr = static_cast<attr_type const *>(state.attr_context_.attr_slots_[slot-1]);
                return result_type::make(opt<attr_type>(attr));
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                result_type that = {
                    typename Grammar::template impl<Expr, State, Data>()(expr, state, data)
                };
                return that;
            }


            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param
              , typename impl::data_param
            ) const
            {
                return result_type::make(proto::value(expr));
            }


        action_matcher(Actor const &actor, int sub)
          : sub_(sub)
          , actor_(actor)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            // Bind the arguments
            typedef
                typename boost::result_of<BindActionArgs(
                    Actor const &
                  , match_state<BidiIter> &
                  , int const &
                )>::type
            action_type;

            action<action_type> actor(BindActionArgs()(this->actor_, state, this->sub_));

            // Put the action in the action list
            actionable const **action_list_tail = state.action_list_tail_;
            *state.action_list_tail_ = &actor;
            state.action_list_tail_ = &actor.next;

            // Match the rest of the pattern
            if(next.match(state))
            {
                return true;
            }

            BOOST_ASSERT(0 == actor.next);
            // remove action from list
            *action_list_tail = 0;
            state.action_list_tail_ = action_list_tail;
            return false;
        }

        keeper_matcher(Xpr const &xpr, bool pure = Xpr::pure)
          : xpr_(xpr)
          , pure_(pure)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return Xpr::pure || this->pure_
              ? this->match_(state, next, mpl::true_())
              : this->match_(state, next, mpl::false_());
        }


        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const
        {
            BidiIter const tmp = state.cur_;

            // matching xpr is guaranteed to not produce side-effects, don't bother saving state
            if(!this->xpr_.match(state))
            {
                return false;
            }
            else if(next.match(state))
            {
                return true;
            }

            state.cur_ = tmp;
            return false;
        }


        posix_charset_matcher(char_class_type m, bool no)
          : not_(no)
          , mask_(m)
        {
            BOOST_ASSERT(0 != this->mask_);
        }


        void inverse()
        {
            this->not_ = !this->not_;
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos() || this->not_ == traits_cast<Traits>(state).isctype(
                *state.cur_, this->mask_))
            {
                return false;
            }

            ++state.cur_;
            if(next.match(state))
            {
                return true;
            }

            --state.cur_;
            return false;
        }

        alt_match_pred(match_state<BidiIter> &state)
          : state_(&state)
        {
        }


        template<typename Xpr>
        bool operator ()(Xpr const &xpr) const
        {
            return xpr.BOOST_NESTED_TEMPLATE push_match<Next>(*this->state_);
        }


        explicit alternate_matcher(Alternates const &alternates = Alternates())
          : alternates_(alternates)
          , bset_()
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(!state.eos() && !this->can_match_(*state.cur_, traits_cast<Traits>(state)))
            {
                return false;
            }

            return detail::alt_match(this->alternates_, state, next);
        }


        detail::width get_width() const
        {
            // Only called when constructing static regexes, and this is a
            // set of same-width alternates where the widths are known at compile
            // time, as in: sregex rx = +(_ | 'a' | _n);
            BOOST_MPL_ASSERT_RELATION(unknown_width::value, !=, Alternates::width);
            return Alternates::width;
        }


        bool can_match_(char_type ch, Traits const &tr) const
        {
            return this->bset_.test(ch, tr);
        }


        assert_bol_matcher(Traits const &tr)
          : assert_line_base<Traits>(tr)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.bos())
            {
                if(!state.flags_.match_bol_)
                {
                    return false;
                }
            }
            else
            {
                char_type ch = *boost::prior(state.cur_);

                // If the previous character is not a newline, we're not at the start of a line
                if(!traits_cast<Traits>(state).isctype(ch, this->newline_))
                {
                    return false;
                }
                // There is no line-break between \r and \n
                else if(ch == this->cr_ && !state.eos() && *state.cur_ == this->nl_)
                {
                    return false;
                }
            }

            return next.match(state);
        }


        mark_matcher(int mark_number, Traits const &)
          : mark_number_(mark_number)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BOOST_ASSERT(this->mark_number_ < static_cast<int>(state.mark_count_));
            sub_match_impl<BidiIter> const &br = state.sub_match(this->mark_number_);

            if(!br.matched)
            {
                return false;
            }

            BidiIter const tmp = state.cur_;
            for(BidiIter begin = br.first, end = br.second; begin != end; ++begin, ++state.cur_)
            {
                if(state.eos()
                    || detail::translate(*state.cur_, traits_cast<Traits>(state), icase_type())
                    != detail::translate(*begin, traits_cast<Traits>(state), icase_type()))
                {
                    state.cur_ = tmp;
                    return false;
                }
            }

            if(next.match(state))
            {
                return true;
            }

            state.cur_ = tmp;
            return false;
        }


        range_matcher(char_type ch_min, char_type ch_max, bool no, Traits const &)
          : ch_min_(ch_min)
          , ch_max_(ch_max)
          , not_(no)
        {
        }


        void inverse()
        {
            this->not_ = !this->not_;
        }


        bool in_range(Traits const &tr, char_type ch, mpl::false_) const // case-sensitive
        {
            return tr.in_range(this->ch_min_, this->ch_max_, ch);
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos() || this->not_ ==
                this->in_range(traits_cast<Traits>(state), *state.cur_, icase_type()))
            {
                return false;
            }

            ++state.cur_;
            if(next.match(state))
            {
                return true;
            }

            --state.cur_;
            return false;
        }


        logical_newline_matcher(Traits const &tr)
          : newline_(lookup_classname(tr, "newline"))
          , nl_(tr.widen('\n'))
          , cr_(tr.widen('\r'))
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos())
            {
                return false;
            }

            char_type ch = *state.cur_;
            if(traits_cast<Traits>(state).isctype(ch, this->newline_))
            {
                ++state.cur_;
                if(this->cr_ == ch && !state.eos() && this->nl_ == *state.cur_)
                {
                    ++state.cur_;
                    if(next.match(state))
                    {
                        return true;
                    }
                    --state.cur_;
                }
                else if(next.match(state))
                {
                    return true;
                }

                --state.cur_;
            }
            return false;
        }


        char_class_type newline() const
        {
            return this->newline_;
        }

        assert_line_base(Traits const &tr)
            : newline_(lookup_classname(tr, "newline"))
            , nl_(tr.widen('\n'))
            , cr_(tr.widen('\r'))
        {
        }

        template<typename BidiIter>
        static bool eval(bool prevword, bool thisword, match_state<BidiIter> &state)
        {
            if((state.flags_.match_not_bow_ && state.bos()) || (state.flags_.match_not_eow_ && state.eos()))
            {
                return !IsBoundary::value;
            }

            return IsBoundary::value == (prevword != thisword);
        }

        template<typename BidiIter>
        static bool eval(bool prevword, bool thisword, match_state<BidiIter> &state)
        {
            if(state.flags_.match_not_bow_ && state.bos())
            {
                return false;
            }

            return !prevword && thisword;
        }

        template<typename BidiIter>
        static bool eval(bool prevword, bool thisword, match_state<BidiIter> &state)
        {
            if(state.flags_.match_not_eow_ && state.eos())
            {
                return false;
            }

            return prevword && !thisword;
        }


        assert_word_matcher(Traits const &tr)
          : word_(lookup_classname(tr, "w"))
        {
            BOOST_ASSERT(0 != this->word_);
        }


        assert_word_matcher(char_class_type word)
          : word_(word)
        {}


        bool is_word(Traits const &tr, char_type ch) const
        {
            detail::ignore_unused(tr);
            return tr.isctype(tr.translate(ch), this->word_);
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BidiIter cur = state.cur_;
            bool const thisword = !state.eos() && this->is_word(traits_cast<Traits>(state), *cur);
            bool const prevword = (!state.bos() || state.flags_.match_prev_avail_)
                && this->is_word(traits_cast<Traits>(state), *--cur);

            return Cond::eval(prevword, thisword, state) && next.match(state);
        }


        char_class_type word() const
        {
            return this->word_;
        }

        template<typename BidiIter, typename Next>
        static bool match(match_state<BidiIter> &state, Next const &next)
        {
            void const *attr_slots[Nbr::value] = {};
            attr_context old_attr_context = state.attr_context_;
            state.attr_context_.attr_slots_ = attr_slots;
            state.attr_context_.prev_attr_context_ = &old_attr_context;

            if(next.match(state))
            {
                return true;
            }

            state.attr_context_ = old_attr_context;
            return false;
        }

        template<typename BidiIter, typename Next>
        static bool match(match_state<BidiIter> &state, Next const &next)
        {
            attr_context old_attr_context = state.attr_context_;
            state.attr_context_ = *old_attr_context.prev_attr_context_;

            if(next.match(state))
            {
                return true;
            }

            state.attr_context_ = old_attr_context;
            return false;
        }


        simple_repeat_matcher(Xpr const &xpr, unsigned int min, unsigned int max, std::size_t width)
          : xpr_(xpr)
          , min_(min)
          , max_(max)
          , width_(width)
          , leading_(false)
        {
            // it is the job of the parser to make sure this never happens
            BOOST_ASSERT(min <= max);
            BOOST_ASSERT(0 != max);
            BOOST_ASSERT(0 != width && unknown_width() != width);
            BOOST_ASSERT(Xpr::width == unknown_width() || Xpr::width == width);
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            typedef mpl::bool_<is_random<BidiIter>::value> is_rand;
            typedef typename simple_repeat_traits<Xpr, greedy_type, is_rand>::tag_type tag_type;
            return this->match_(state, next, tag_type());
        }

        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, greedy_slow_tag) const
        {
            int const diff = -static_cast<int>(Xpr::width == unknown_width::value ? this->width_ : Xpr::width);
            unsigned int matches = 0;
            BidiIter const tmp = state.cur_;

            // greedily match as much as we can
            while(matches < this->max_ && this->xpr_.match(state))
            {
                ++matches;
            }

            // If this repeater is at the front of the pattern, note
            // how much of the input we consumed so that a repeated search
            // doesn't have to cover the same ground again.
            if(this->leading_)
            {
                state.next_search_ = (matches && matches < this->max_)
                                   ? state.cur_
                                   : (tmp == state.end_) ? tmp : boost::next(tmp);
            }

            if(this->min_ > matches)
            {
                state.cur_ = tmp;
                return false;
            }

            // try matching the rest of the pattern, and back off if necessary
            for(; ; --matches, std::advance(state.cur_, diff))
            {
                if(next.match(state))
                {
                    return true;
                }
                else if(this->min_ == matches)
                {
                    state.cur_ = tmp;
                    return false;
                }
            }
        }


        detail::width get_width() const
        {
            if(this->min_ != this->max_)
            {
                return unknown_width::value;
            }
            return this->min_ * this->width_;
        }


    set_matcher()
      : set_()
      , not_(false)
      , icase_(false)
    {
    }


    void inverse()
    {
        this->not_ = !this->not_;
    }


    void nocase(Traits const &tr)
    {
        this->icase_ = true;

        for(int i = 0; i < Size::value; ++i)
        {
            this->set_[i] = tr.translate_nocase(this->set_[i]);
        }
    }


    bool in_set(Traits const &tr, char_type ch) const
    {
        char_type const *begin = &this->set_[0], *end = begin + Size::value;
        ch = this->icase_ ? tr.translate_nocase(ch) : tr.translate(ch);
        return end != std::find(begin, end, ch);
    }


    template<typename BidiIter, typename Next>
    bool match(match_state<BidiIter> &state, Next const &next) const
    {
        if(state.eos() || this->not_ == this->in_set(traits_cast<Traits>(state), *state.cur_))
        {
            return false;
        }

        if(++state.cur_, next.match(state))
        {
            return true;
        }

        return --state.cur_, false;
    }

        lookahead_matcher(Xpr const &xpr, bool no, bool pure = Xpr::pure)
          : xpr_(xpr)
          , not_(no)
          , pure_(pure)
        {
        }


        void inverse()
        {
            this->not_ = !this->not_;
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return Xpr::pure || this->pure_
              ? this->match_(state, next, mpl::true_())
              : this->match_(state, next, mpl::false_());
        }


        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const
        {
            BidiIter const tmp = state.cur_;

            if(this->not_)
            {
                // negative look-ahead assertions do not trigger partial matches.
                save_restore<bool> partial_match(state.found_partial_match_);
                detail::ignore_unused(partial_match);

                if(this->xpr_.match(state))
                {
                    state.cur_ = tmp;
                    return false;
                }
                else if(next.match(state))
                {
                    return true;
                }
            }
            else
            {
                if(!this->xpr_.match(state))
                {
                    return false;
                }
                state.cur_ = tmp;
                if(next.match(state))
                {
                    return true;
                }
            }

            BOOST_ASSERT(state.cur_ == tmp);
            return false;
        }

        lookbehind_matcher(Xpr const &xpr, std::size_t wid, bool no, bool pure = Xpr::pure)
          : xpr_(xpr)
          , not_(no)
          , pure_(pure)
          , width_(wid)
        {
            BOOST_XPR_ENSURE_(!is_unknown(this->width_), regex_constants::error_badlookbehind,
                "Variable-width look-behind assertions are not supported");
        }


        void inverse()
        {
            this->not_ = !this->not_;
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return Xpr::pure || this->pure_
              ? this->match_(state, next, mpl::true_())
              : this->match_(state, next, mpl::false_());
        }


        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const
        {
            typedef typename iterator_difference<BidiIter>::type difference_type;
            BidiIter const tmp = state.cur_;
            if(!detail::advance_to(state.cur_, -static_cast<difference_type>(this->width_), state.begin_))
            {
                state.cur_ = tmp;
                return this->not_ ? next.match(state) : false;
            }

            if(this->not_)
            {
                if(this->xpr_.match(state))
                {
                    BOOST_ASSERT(state.cur_ == tmp);
                    return false;
                }
                state.cur_ = tmp;
                if(next.match(state))
                {
                    return true;
                }
            }
            else
            {
                if(!this->xpr_.match(state))
                {
                    state.cur_ = tmp;
                    return false;
                }
                BOOST_ASSERT(state.cur_ == tmp);
                if(next.match(state))
                {
                    return true;
                }
            }

            BOOST_ASSERT(state.cur_ == tmp);
            return false;
        }


        explicit literal_matcher(char_type ch)
          : ch_(ch)
        {}


        literal_matcher(char_type ch, Traits const &tr)
          : ch_(detail::translate(ch, tr, icase_type()))
        {}


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos() || Not::value ==
                (detail::translate(*state.cur_, traits_cast<Traits>(state), icase_type()) == this->ch_))
            {
                return false;
            }

            ++state.cur_;
            if(next.match(state))
            {
                return true;
            }

            --state.cur_;
            return false;
        }


        regex_matcher(shared_ptr<regex_impl<BidiIter> > const &impl)
          : impl_()
        {
            this->impl_.xpr_ = impl->xpr_;
            this->impl_.traits_ = impl->traits_;
            this->impl_.mark_count_ = impl->mark_count_;
            this->impl_.hidden_mark_count_ = impl->hidden_mark_count_;

            BOOST_XPR_ENSURE_(this->impl_.xpr_, regex_constants::error_badref, "bad regex reference");
        }


        template<typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            // regex_matcher is used for embeding a dynamic regex in a static regex. As such,
            // Next will always point to a static regex.
            BOOST_MPL_ASSERT((is_static_xpression<Next>));

            // wrap the static xpression in a matchable interface
            xpression_adaptor<reference_wrapper<Next const>, matchable<BidiIter> > adaptor(boost::cref(next));
            return push_context_match(this->impl_, state, adaptor);
        }


        repeat_begin_matcher(int mark_number)
          : mark_number_(mark_number)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            sub_match_impl<BidiIter> &br = state.sub_match(this->mark_number_);

            unsigned int old_repeat_count = br.repeat_count_;
            bool old_zero_width = br.zero_width_;

            br.repeat_count_ = 1;
            br.zero_width_ = false;

            // "push" next onto the stack, so it can be "popped" in
            // repeat_end_matcher and used to loop back.
            if(next.BOOST_NESTED_TEMPLATE push_match<Next>(state))
            {
                return true;
            }

            br.repeat_count_ = old_repeat_count;
            br.zero_width_ = old_zero_width;

            return false;
        }


        repeat_end_matcher(int mark_nbr, unsigned int min, unsigned int max)
          : mark_number_(mark_nbr)
          , min_(min)
          , max_(max)
          , back_(0)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            // prevent repeated zero-width sub-matches from causing infinite recursion
            sub_match_impl<BidiIter> &br = state.sub_match(this->mark_number_);

            if(br.zero_width_ && br.begin_ == state.cur_)
            {
                return next.skip_match(state);
            }

            bool old_zero_width = br.zero_width_;
            br.zero_width_ = (br.begin_ == state.cur_);

            if(this->match_(state, next, greedy_type()))
            {
                return true;
            }

            br.zero_width_ = old_zero_width;
            return false;
        }

        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const
        {
            sub_match_impl<BidiIter> &br = state.sub_match(this->mark_number_);

            if(this->max_ > br.repeat_count_)
            {
                ++br.repeat_count_;
                // loop back to the expression "pushed" in repeat_begin_matcher::match
                if(next.top_match(state, this->back_))
                {
                    return true;
                }
                else if(--br.repeat_count_ < this->min_)
                {
                    return false;
                }
            }

            // looping finished, continue matching the rest of the pattern
            return next.skip_match(state);
        }

        template<typename BidiIter, typename Next>
        static bool match(match_state<BidiIter> &, Next const &)
        {
            return true;
        }


        charset_matcher(CharSet const &charset = CharSet())
          : charset_(charset)
        {
        }


        void inverse()
        {
            this->charset_.inverse();
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos() || !this->charset_.test(*state.cur_, traits_cast<Traits>(state), icase_type()))
            {
                return false;
            }

            ++state.cur_;
            if(next.match(state))
            {
                return true;
            }

            --state.cur_;
            return false;
        }

        template<typename BidiIter, typename Next>
        static bool match(match_state<BidiIter> &state, Next const &)
        {
            BidiIter const tmp = state.cur_;
            sub_match_impl<BidiIter> &s0 = state.sub_match(0);
            BOOST_ASSERT(!s0.matched);

            // SPECIAL: if there is a match context on the context stack, then
            // this pattern has been nested within another. pop that context and
            // continue executing.
            if(0 != state.context_.prev_context_)
            {
                if(!pop_context_match(state))
                {
                    return false;
                }

                // record the end of sub-match zero
                s0.first = s0.begin_;
                s0.second = tmp;
                s0.matched = true;

                return true;
            }
            else if((state.flags_.match_all_ && !state.eos()) ||
                    (state.flags_.match_not_null_ && state.cur_ == s0.begin_))
            {
                return false;
            }

            // record the end of sub-match zero
            s0.first = s0.begin_;
            s0.second = tmp;
            s0.matched = true;

            // Now execute any actions that have been queued
            for(actionable const *actor = state.action_list_.next; 0 != actor; actor = actor->next)
            {
                actor->execute(state.action_args_);
            }

            return true;
        }

        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &) const
        {
            // Now execute any actions that have been queued
            for(actionable const *actor = state.action_list_.next; 0 != actor; actor = actor->next)
            {
                actor->execute(state.action_args_);
            }

            return true;
        }


        alternate_end_matcher()
          : back_(0)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return next.pop_match(state, this->back_);
        }


        mark_end_matcher(int mark_number)
          : mark_number_(mark_number)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            sub_match_impl<BidiIter> &br = state.sub_match(this->mark_number_);

            BidiIter old_first = br.first;
            BidiIter old_second = br.second;
            bool old_matched = br.matched;

            br.first = br.begin_;
            br.second = state.cur_;
            br.matched = true;

            if(next.match(state))
            {
                return true;
            }

            br.first = old_first;
            br.second = old_second;
            br.matched = old_matched;

            return false;
        }


        string_matcher(string_type const &str, Traits const &tr)
          : str_(str)
          , end_()
        {
            typename range_iterator<string_type>::type cur = boost::begin(this->str_);
            typename range_iterator<string_type>::type end = boost::end(this->str_);
            for(; cur != end; ++cur)
            {
                *cur = detail::translate(*cur, tr, icase_type());
            }
            this->end_ = detail::data_end(str_);
        }


        string_matcher(string_matcher<Traits, ICase> const &that)
          : str_(that.str_)
          , end_(detail::data_end(str_))
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BidiIter const tmp = state.cur_;
            char_type const *begin = detail::data_begin(this->str_);
            for(; begin != this->end_; ++begin, ++state.cur_)
            {
                if(state.eos() ||
                    (detail::translate(*state.cur_, traits_cast<Traits>(state), icase_type()) != *begin))
                {
                    state.cur_ = tmp;
                    return false;
                }
            }

            if(next.match(state))
            {
                return true;
            }

            state.cur_ = tmp;
            return false;
        }


        detail::width get_width() const
        {
            return boost::size(this->str_);
        }


        explicit optional_matcher(Xpr const &xpr)
          : xpr_(xpr)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return this->match_(state, next, Greedy());
        }

        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const // Greedy
        {
            return this->xpr_.BOOST_NESTED_TEMPLATE push_match<Next>(state)
                || next.match(state);
        }


        explicit optional_mark_matcher(Xpr const &xpr, int mark_number)
          : xpr_(xpr)
          , mark_number_(mark_number)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            return this->match_(state, next, Greedy());
        }

        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const // Greedy
        {
            return this->xpr_.BOOST_NESTED_TEMPLATE push_match<Next>(state)
                || match_next(state, next, this->mark_number_);
        }

        explicit predicate_context(int sub, sub_match_impl<BidiIter> const *sub_matches, action_args_type *action_args)
          : sub_(sub)
          , sub_matches_(sub_matches)
          , action_args_(action_args)
        {}

            result_type operator()(Expr &, predicate_context const &ctx) const
            {
                return ctx.sub_matches_[ctx.sub_];
            }


        predicate_matcher(Predicate const &pred, int sub)
          : sub_(sub)
          , predicate_(pred)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            // Predicate is check(assertion), where assertion can be
            // a lambda or a function object.
            return this->match_(state, next, proto::matches<Predicate, AssertionFunctor>());
        }

        template<typename BidiIter, typename Next>
        bool match_(match_state<BidiIter> &state, Next const &next, mpl::true_) const
        {
            sub_match<BidiIter> const &sub = state.sub_match(this->sub_);
            return proto::value(proto::child_c<1>(this->predicate_))(sub) && next.match(state);
        }

        
        assert_eol_matcher(Traits const &tr)
          : assert_line_base<Traits>(tr)
        {
        }


        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            if(state.eos())
            {
                if(!state.flags_.match_eol_)
                {
                    return false;
                }
            }
            else
            {
                char_type ch = *state.cur_;

                // If the current character is not a newline, we're not at the end of a line
                if(!traits_cast<Traits>(state).isctype(ch, this->newline_))
                {
                    return false;
                }
                // There is no line-break between \r and \n
                else if(ch == this->nl_ && (!state.bos() || state.flags_.match_prev_avail_) && *boost::prior(state.cur_) == this->cr_)
                {
                    return false;
                }
            }

            return next.match(state);
        }


        regex_byref_matcher(shared_ptr<regex_impl<BidiIter> > const &impl)
          : wimpl_(impl)
          , pimpl_(impl.get())
        {
            BOOST_ASSERT(this->pimpl_);
        }


        template<typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            BOOST_ASSERT(this->pimpl_ == this->wimpl_.lock().get());
            BOOST_XPR_ENSURE_(this->pimpl_->xpr_, regex_constants::error_badref, "bad regex reference");

            return push_context_match(*this->pimpl_, state, this->wrap_(next, is_static_xpression<Next>()));
        }

    virtual ~matchable() {}


    virtual void link(xpression_linker<char_type> &) const
    {
    }


    virtual void peek(xpression_peeker<char_type> &peeker) const
    {
        peeker.fail();
    }


    virtual void repeat(quant_spec const &, sequence<BidiIter> &) const
    {
        BOOST_THROW_EXCEPTION(
            regex_error(regex_constants::error_badrepeat, "expression cannot be quantified")
        );
    }


    template<typename Top>
    bool push_match(match_state<BidiIter> &state) const
    {
        BOOST_MPL_ASSERT((is_same<Top, matchable_ex<BidiIter> >));
        return this->match(state);
    }


    static bool top_match(match_state<BidiIter> &state, void const *top)
    {
        return static_cast<matchable_ex<BidiIter> const *>(top)->match(state);
    }


    static bool pop_match(match_state<BidiIter> &state, void const *top)
    {
        return static_cast<matchable_ex<BidiIter> const *>(top)->match(state);
    }


    bool skip_match(match_state<BidiIter> &state) const
    {
        return this->match(state);
    }


    shared_matchable(matchable_ptr const &xpr = matchable_ptr())
      : xpr_(xpr)
    {
    }


    bool operator !() const
    {
        return !this->xpr_;
    }

    void operator ()(numeric::range_check_result result) const // throw(regex_error)
    {
        if(numeric::cInRange != result)
        {
            BOOST_THROW_EXCEPTION(
                regex_error(
                    regex_constants::error_escape
                  , "character escape too large to fit in target character type"
                )
            );
        }
    }

    sequence()
      : pure_(true)
      , width_(0)
      , quant_(quant_none)
      , head_()
      , tail_(0)
      , alt_end_xpr_()
      , alternates_(0)
    {
    }


    bool empty() const
    {
        return !this->head_;
    }


    sequence<BidiIter> &operator +=(sequence<BidiIter> const &that)
    {
        if(this->empty())
        {
            *this = that;
        }
        else if(!that.empty())
        {
            *this->tail_ = that.head_;
            this->tail_ = that.tail_;
            // keep track of sequence width and purity
            this->width_ += that.width_;
            this->pure_ = this->pure_ && that.pure_;
            this->set_quant_();
        }
        return *this;
    }


    sequence<BidiIter> &operator |=(sequence<BidiIter> that)
    {
        BOOST_ASSERT(!this->empty());
        BOOST_ASSERT(0 != this->alternates_);

        // Keep track of width and purity
        if(this->alternates_->empty())
        {
            this->width_ = that.width_;
            this->pure_ = that.pure_;
        }
        else
        {
            this->width_ |= that.width_;
            this->pure_ = this->pure_ && that.pure_;
        }

        // through the wonders of reference counting, all alternates_ can share an end_alternate
        if(!this->alt_end_xpr_)
        {
            this->alt_end_xpr_ = new alt_end_xpr_type;
        }

        // terminate each alternate with an alternate_end_matcher
        that += sequence(this->alt_end_xpr_);
        this->alternates_->push_back(that.head_);
        this->set_quant_();
        return *this;
    }


    void repeat(quant_spec const &spec)
    {
        this->xpr().matchable()->repeat(spec, *this);
    }


    void set_quant_()
    {
        this->quant_ = (!is_unknown(this->width_) && this->pure_)
          ? (!this->width_ ? quant_none : quant_fixed_width)
          : quant_variable_width;
    }


template<typename BidiIter>
inline sequence<BidiIter> operator +(sequence<BidiIter> left, sequence<BidiIter> const &right)
{
    return left += right;
}


template<typename BidiIter>
inline sequence<BidiIter> operator |(sequence<BidiIter> left, sequence<BidiIter> const &right)
{
    return left |= right;
}

    explicit compiler_traits(RegexTraits const &traits = RegexTraits())
      : traits_(traits)
      , flags_(regex_constants::ECMAScript)
      , space_(lookup_classname(traits_, "space"))
      , alnum_(lookup_classname(traits_, "alnum"))
    {
    }

    regex_constants::syntax_option_type flags() const
    {
        return this->flags_;
    }

    regex_traits &traits()
    {
        return this->traits_;
    }


    regex_traits const &traits() const
    {
        return this->traits_;
    }

    locale_type imbue(locale_type const &loc)
    {
        locale_type oldloc = this->traits().imbue(loc);
        this->space_ = lookup_classname(this->traits(), "space");
        this->alnum_ = lookup_classname(this->traits(), "alnum");
        return oldloc;
    }

    locale_type getloc() const
    {
        return this->traits().getloc();
    }

    template<typename FwdIter>
    regex_constants::compiler_token_type get_token(FwdIter &begin, FwdIter end)
    {
        using namespace regex_constants;
        if(this->eat_ws_(begin, end) == end)
        {
            return regex_constants::token_end_of_pattern;
        }

        switch(*begin)
        {
        case BOOST_XPR_CHAR_(char_type, '\\'): return this->get_escape_token(++begin, end);
        case BOOST_XPR_CHAR_(char_type, '.'): ++begin; return token_any;
        case BOOST_XPR_CHAR_(char_type, '^'): ++begin; return token_assert_begin_line;
        case BOOST_XPR_CHAR_(char_type, '$'): ++begin; return token_assert_end_line;
        case BOOST_XPR_CHAR_(char_type, '('): ++begin; return token_group_begin;
        case BOOST_XPR_CHAR_(char_type, ')'): ++begin; return token_group_end;
        case BOOST_XPR_CHAR_(char_type, '|'): ++begin; return token_alternate;
        case BOOST_XPR_CHAR_(char_type, '['): ++begin; return token_charset_begin;

        case BOOST_XPR_CHAR_(char_type, '*'):
        case BOOST_XPR_CHAR_(char_type, '+'):
        case BOOST_XPR_CHAR_(char_type, '?'):
            return token_invalid_quantifier;

        case BOOST_XPR_CHAR_(char_type, ']'):
        case BOOST_XPR_CHAR_(char_type, '{'):
        default:
            return token_literal;
        }
    }

    template<typename FwdIter>
    bool get_quant_spec(FwdIter &begin, FwdIter end, detail::quant_spec &spec)
    {
        using namespace regex_constants;
        FwdIter old_begin;

        if(this->eat_ws_(begin, end) == end)
        {
            return false;
        }

        switch(*begin)
        {
        case BOOST_XPR_CHAR_(char_type, '*'):
            spec.min_ = 0;
            spec.max_ = (std::numeric_limits<unsigned int>::max)();
            break;

        case BOOST_XPR_CHAR_(char_type, '+'):
            spec.min_ = 1;
            spec.max_ = (std::numeric_limits<unsigned int>::max)();
            break;

        case BOOST_XPR_CHAR_(char_type, '?'):
            spec.min_ = 0;
            spec.max_ = 1;
            break;

        case BOOST_XPR_CHAR_(char_type, '{'):
            old_begin = this->eat_ws_(++begin, end);
            spec.min_ = spec.max_ = detail::toi(begin, end, this->traits());
            BOOST_XPR_ENSURE_
            (
                begin != old_begin && begin != end, error_brace, "invalid quantifier"
            );

            if(*begin == BOOST_XPR_CHAR_(char_type, ','))
            {
                old_begin = this->eat_ws_(++begin, end);
                spec.max_ = detail::toi(begin, end, this->traits());
                BOOST_XPR_ENSURE_
                (
                    begin != end && BOOST_XPR_CHAR_(char_type, '}') == *begin
                  , error_brace, "invalid quantifier"
                );

                if(begin == old_begin)
                {
                    spec.max_ = (std::numeric_limits<unsigned int>::max)();
                }
                else
                {
                    BOOST_XPR_ENSURE_
                    (
                        spec.min_ <= spec.max_, error_badbrace, "invalid quantification range"
                    );
                }
            }
            else
            {
                BOOST_XPR_ENSURE_
                (
                    BOOST_XPR_CHAR_(char_type, '}') == *begin, error_brace, "invalid quantifier"
                );
            }
            break;

        default:
            return false;
        }

        spec.greedy_ = true;
        if(this->eat_ws_(++begin, end) != end && BOOST_XPR_CHAR_(char_type, '?') == *begin)
        {
            ++begin;
            spec.greedy_ = false;
        }

        return true;
    }

    template<typename FwdIter>
    regex_constants::compiler_token_type get_group_type(FwdIter &begin, FwdIter end, string_type &name)
    {
        using namespace regex_constants;
        if(this->eat_ws_(begin, end) != end && BOOST_XPR_CHAR_(char_type, '?') == *begin)
        {
            this->eat_ws_(++begin, end);
            BOOST_XPR_ENSURE_(begin != end, error_paren, "incomplete extension");

            switch(*begin)
            {
            case BOOST_XPR_CHAR_(char_type, ':'): ++begin; return token_no_mark;
            case BOOST_XPR_CHAR_(char_type, '>'): ++begin; return token_independent_sub_expression;
            case BOOST_XPR_CHAR_(char_type, '#'): ++begin; return token_comment;
            case BOOST_XPR_CHAR_(char_type, '='): ++begin; return token_positive_lookahead;
            case BOOST_XPR_CHAR_(char_type, '!'): ++begin; return token_negative_lookahead;
            case BOOST_XPR_CHAR_(char_type, 'R'): ++begin; return token_recurse;
            case BOOST_XPR_CHAR_(char_type, '$'):
                this->get_name_(++begin, end, name);
                BOOST_XPR_ENSURE_(begin != end, error_paren, "incomplete extension");
                if(BOOST_XPR_CHAR_(char_type, '=') == *begin)
                {
                    ++begin;
                    return token_rule_assign;
                }
                return token_rule_ref;

            case BOOST_XPR_CHAR_(char_type, '<'):
                this->eat_ws_(++begin, end);
                BOOST_XPR_ENSURE_(begin != end, error_paren, "incomplete extension");
                switch(*begin)
                {
                case BOOST_XPR_CHAR_(char_type, '='): ++begin; return token_positive_lookbehind;
                case BOOST_XPR_CHAR_(char_type, '!'): ++begin; return token_negative_lookbehind;
                default:
                    BOOST_THROW_EXCEPTION(regex_error(error_badbrace, "unrecognized extension"));
                }

            case BOOST_XPR_CHAR_(char_type, 'P'):
                this->eat_ws_(++begin, end);
                BOOST_XPR_ENSURE_(begin != end, error_paren, "incomplete extension");
                switch(*begin)
                {
                case BOOST_XPR_CHAR_(char_type, '<'):
                    this->get_name_(++begin, end, name);
                    BOOST_XPR_ENSURE_(begin != end && BOOST_XPR_CHAR_(char_type, '>') == *begin++, error_paren, "incomplete extension");
                    return token_named_mark;
                case BOOST_XPR_CHAR_(char_type, '='):
                    this->get_name_(++begin, end, name);
                    BOOST_XPR_ENSURE_(begin != end, error_paren, "incomplete extension");
                    return token_named_mark_ref;
                default:
                    BOOST_THROW_EXCEPTION(regex_error(error_badbrace, "unrecognized extension"));
                }

            case BOOST_XPR_CHAR_(char_type, 'i'):
            case BOOST_XPR_CHAR_(char_type, 'm'):
            case BOOST_XPR_CHAR_(char_type, 's'):
            case BOOST_XPR_CHAR_(char_type, 'x'):
            case BOOST_XPR_CHAR_(char_type, '-'):
                return this->parse_mods_(begin, end);

            default:
                BOOST_THROW_EXCEPTION(regex_error(error_badbrace, "unrecognized extension"));
            }
        }

        return token_literal;
    }

    template<typename FwdIter>
    regex_constants::compiler_token_type get_charset_token(FwdIter &begin, FwdIter end)
    {
        using namespace regex_constants;
        BOOST_ASSERT(begin != end);
        switch(*begin)
        {
        case BOOST_XPR_CHAR_(char_type, '^'): ++begin; return token_charset_invert;
        case BOOST_XPR_CHAR_(char_type, '-'): ++begin; return token_charset_hyphen;
        case BOOST_XPR_CHAR_(char_type, ']'): ++begin; return token_charset_end;
        case BOOST_XPR_CHAR_(char_type, '['):
            {
                FwdIter next = begin; ++next;
                if(next != end)
                {
                    BOOST_XPR_ENSURE_(
                        *next != BOOST_XPR_CHAR_(char_type, '=')
                      , error_collate
                      , "equivalence classes are not yet supported"
                    );

                    BOOST_XPR_ENSURE_(
                        *next != BOOST_XPR_CHAR_(char_type, '.')
                      , error_collate
                      , "collation sequences are not yet supported"
                    );

                    if(*next == BOOST_XPR_CHAR_(char_type, ':'))
                    {
                        begin = ++next;
                        return token_posix_charset_begin;
                    }
                }
            }
            break;
        case BOOST_XPR_CHAR_(char_type, ':'):
            {
                FwdIter next = begin; ++next;
                if(next != end && *next == BOOST_XPR_CHAR_(char_type, ']'))
                {
                    begin = ++next;
                    return token_posix_charset_end;
                }
            }
            break;
        case BOOST_XPR_CHAR_(char_type, '\\'):
            if(++begin != end)
            {
                switch(*begin)
                {
                case BOOST_XPR_CHAR_(char_type, 'b'): ++begin; return token_charset_backspace;
                default:;
                }
            }
            return token_escape;
        default:;
        }
        return token_literal;
    }

    template<typename FwdIter>
    regex_constants::compiler_token_type get_escape_token(FwdIter &begin, FwdIter end)
    {
        using namespace regex_constants;
        if(begin != end)
        {
            switch(*begin)
            {
            //case BOOST_XPR_CHAR_(char_type, 'a'): ++begin; return token_escape_bell;
            //case BOOST_XPR_CHAR_(char_type, 'c'): ++begin; return token_escape_control;
            //case BOOST_XPR_CHAR_(char_type, 'e'): ++begin; return token_escape_escape;
            //case BOOST_XPR_CHAR_(char_type, 'f'): ++begin; return token_escape_formfeed;
            //case BOOST_XPR_CHAR_(char_type, 'n'): ++begin; return token_escape_newline;
            //case BOOST_XPR_CHAR_(char_type, 't'): ++begin; return token_escape_horizontal_tab;
            //case BOOST_XPR_CHAR_(char_type, 'v'): ++begin; return token_escape_vertical_tab;
            case BOOST_XPR_CHAR_(char_type, 'A'): ++begin; return token_assert_begin_sequence;
            case BOOST_XPR_CHAR_(char_type, 'b'): ++begin; return token_assert_word_boundary;
            case BOOST_XPR_CHAR_(char_type, 'B'): ++begin; return token_assert_not_word_boundary;
            case BOOST_XPR_CHAR_(char_type, 'E'): ++begin; return token_quote_meta_end;
            case BOOST_XPR_CHAR_(char_type, 'Q'): ++begin; return token_quote_meta_begin;
            case BOOST_XPR_CHAR_(char_type, 'Z'): ++begin; return token_assert_end_sequence;
            // Non-standard extension to ECMAScript syntax
            case BOOST_XPR_CHAR_(char_type, '<'): ++begin; return token_assert_word_begin;
            case BOOST_XPR_CHAR_(char_type, '>'): ++begin; return token_assert_word_end;
            default:; // fall-through
            }
        }

        return token_escape;
    }

    template<typename FwdIter>
    regex_constants::compiler_token_type parse_mods_(FwdIter &begin, FwdIter end)
    {
        using namespace regex_constants;
        bool set = true;
        do switch(*begin)
        {
        case BOOST_XPR_CHAR_(char_type, 'i'): this->flag_(set, icase_); break;
        case BOOST_XPR_CHAR_(char_type, 'm'): this->flag_(!set, single_line); break;
        case BOOST_XPR_CHAR_(char_type, 's'): this->flag_(!set, not_dot_newline); break;
        case BOOST_XPR_CHAR_(char_type, 'x'): this->flag_(set, ignore_white_space); break;
        case BOOST_XPR_CHAR_(char_type, ':'): ++begin; // fall-through
        case BOOST_XPR_CHAR_(char_type, ')'): return token_no_mark;
        case BOOST_XPR_CHAR_(char_type, '-'): if(false == (set = !set)) break; // else fall-through
        default: BOOST_THROW_EXCEPTION(regex_error(error_paren, "unknown pattern modifier"));
        }
        while(BOOST_XPR_ENSURE_(++begin != end, error_paren, "incomplete extension"));
        // this return is technically unreachable, but this must
        // be here to work around a bug in gcc 4.0
        return token_no_mark;
    }

    void flag_(bool set, regex_constants::syntax_option_type flag)
    {
        this->flags_ = set ? (this->flags_ | flag) : (this->flags_ & ~flag);
    }

    bool is_space_(char_type ch) const
    {
        return 0 != this->space_ && this->traits().isctype(ch, this->space_);
    }

    bool is_alnum_(char_type ch) const
    {
        return 0 != this->alnum_ && this->traits().isctype(ch, this->alnum_);
    }

    template<typename FwdIter>
    void get_name_(FwdIter &begin, FwdIter end, string_type &name)
    {
        this->eat_ws_(begin, end);
        for(name.clear(); begin != end && this->is_alnum_(*begin); ++begin)
        {
            name.push_back(*begin);
        }
        this->eat_ws_(begin, end);
        BOOST_XPR_ENSURE_(!name.empty(), regex_constants::error_paren, "incomplete extension");
    }

    template<typename FwdIter>
    FwdIter &eat_ws_(FwdIter &begin, FwdIter end)
    {
        if(0 != (regex_constants::ignore_white_space & this->flags()))
        {
            while(end != begin && (BOOST_XPR_CHAR_(char_type, '#') == *begin || this->is_space_(*begin)))
            {
                if(BOOST_XPR_CHAR_(char_type, '#') == *begin++)
                {
                    while(end != begin && BOOST_XPR_CHAR_(char_type, '\n') != *begin++) {}
                }
                else
                {
                    for(; end != begin && this->is_space_(*begin); ++begin) {}
                }
            }
        }

        return begin;
    }

    invalid_xpression()
      : matchable_ex<BidiIter>()
    {
        intrusive_ptr_add_ref(this); // keep alive forever
    }


    bool match(match_state<BidiIter> &) const
    {
        BOOST_ASSERT(false);
        return false;
    }

    matcher_wrapper(Matcher const &matcher = Matcher())
      : Matcher(matcher)
    {
    }


    template<typename BidiIter>
    bool match(match_state<BidiIter> &state) const
    {
        return this->Matcher::match(state, matcher_wrapper<true_matcher>());
    }


    template<typename Char>
    void link(xpression_linker<Char> &linker) const
    {
        linker.accept(*static_cast<Matcher const *>(this), 0);
    }


    template<typename Char>
    void peek(xpression_peeker<Char> &peeker) const
    {
        peeker.accept(*static_cast<Matcher const *>(this));
    }

        template <typename First, typename Last, typename F>
        inline bool
        any(First const&, Last const&, F const&, mpl::true_)
        {
            return false;
        }


            template <typename Sequence, typename F>
            inline bool
            operator()(Sequence const& seq, F const& f) const
            {
                return detail::any(
                        fusion::begin(seq)
                      , fusion::end(seq)
                      , f
                      , meta::equal_to<
                            BOOST_DEDUCED_TYPENAME meta::begin<Sequence>::type
                          , BOOST_DEDUCED_TYPENAME meta::end<Sequence>::type>());
            }


            template <typename Sequence, typename F>
            inline bool
            operator()(Sequence& seq, F const& f) const
            {
                return detail::any(
                        fusion::begin(seq)
                      , fusion::end(seq)
                      , f
                      , meta::equal_to<
                            BOOST_DEDUCED_TYPENAME meta::begin<Sequence>::type
                          , BOOST_DEDUCED_TYPENAME meta::end<Sequence>::type>());
            }

        explicit save_restore(T &t)
          : ref(t)
          , val(t)
        {
        }


        save_restore(T &t, T const &n)
          : ref(t)
          , val(t)
        {
            this->ref = n;
        }


        ~save_restore()
        {
            this->ref = this->val;
        }


        void restore()
        {
            this->ref = this->val;
        }

        long use_count() const
        {
            return this->count_;
        }

        counted_base()
          : count_(0)
        {
        }


        counted_base(counted_base<Derived> const &)
          : count_(0)
        {
        }


        counted_base &operator =(counted_base<Derived> const &)
        {
            return *this;
        }

        static void add_ref(counted_base<Derived> const *that)
        {
            ++that->count_;
        }


        static void release(counted_base<Derived> const *that)
        {
            BOOST_ASSERT(0 < that->count_);
            if(0 == --that->count_)
            {
                boost::checked_delete(static_cast<Derived const *>(that));
            }
        }


    template<typename Derived>
    inline void intrusive_ptr_add_ref(counted_base<Derived> const *that)
    {
        counted_base_access<Derived>::add_ref(that);
    }


    template<typename Derived>
    inline void intrusive_ptr_release(counted_base<Derived> const *that)
    {
        counted_base_access<Derived>::release(that);
    }

template<typename InIter, typename Pred>
inline bool any(InIter begin, InIter end, Pred pred)
{
    return end != std::find_if(begin, end, pred);
}

template<typename FwdIter, typename Diff, typename Pred>
FwdIter find_nth_if(FwdIter begin, FwdIter end, Diff count, Pred pred)
{
    for(; begin != end; ++begin)
    {
        if(pred(*begin) && 0 == count--)
        {
            return begin;
        }
    }

    return end;
}

template<typename InIter, typename Traits>
int toi(InIter &begin, InIter end, Traits const &tr, int radix = 10, int max = INT_MAX)
{
    detail::ignore_unused(tr);
    int i = 0, c = 0;
    for(; begin != end && -1 != (c = tr.value(*begin, radix)); ++begin)
    {
        if(max < ((i *= radix) += c))
            return i / radix;
    }
    return i;
}

template<typename BidiIter, typename Diff>
inline bool advance_to_impl(BidiIter & iter, Diff diff, BidiIter end, std::bidirectional_iterator_tag)
{
    for(; 0 < diff && iter != end; --diff)
        ++iter;
    for(; 0 > diff && iter != end; ++diff)
        --iter;
    return 0 == diff;
}


template<typename Iter, typename Diff>
inline bool advance_to(Iter & iter, Diff diff, Iter end)
{
    return detail::advance_to_impl(iter, diff, end, typename iterator_category<Iter>::type());
}


template<typename T> std::ptrdiff_t is_null_terminated(T const &) { return 0; }

template<typename Cont>
typename range_data<Cont>::type const *data_begin(Cont const &cont)
{
    return &*boost::begin(cont);
}


template<typename Cont>
typename range_data<Cont>::type const *data_end(Cont const &cont)
{
    return &*boost::begin(cont) + boost::size(cont) - is_null_terminated(cont);
}


template<typename Char>
Char const *data_begin(Char const *const &sz)
{
    return sz;
}


template<typename Char>
Char const *data_end(Char const *const &sz)
{
    Char const *tmp = sz;
    for(; *tmp; ++tmp)
        ;
    return tmp;
}

    static T *allocate(std::size_t size, T const &t)
    {
        std::size_t i = 0;
        T *p = (T *)::operator new(size * sizeof(T));
        try
        {
            for(; i < size; ++i)
                ::new((void *)(p+i)) T(t);
        }
        catch(...)
        {
            deallocate(p, i);
            throw;
        }
        return p;
    }


    static void deallocate(T *p, std::size_t i)
    {
        while(i-- > 0)
            (p+i)->~T();
        ::operator delete(p);
    }

        chunk(std::size_t size, T const &t, std::size_t count, chunk *back, chunk *next)
          : begin_(allocate(size, t))
          , curr_(begin_ + count)
          , end_(begin_ + size)
          , back_(back)
          , next_(next)
        {
            if(this->back_)
                this->back_->next_ = this;
            if(this->next_)
                this->next_->back_ = this;
        }


        ~chunk()
        {
            deallocate(this->begin_, this->size());
        }


        std::size_t size() const
        {
            return static_cast<std::size_t>(this->end_ - this->begin_);
        }


    T *grow_(std::size_t count, T const &t)
    {
        if(this->current_chunk_)
        {
            // write the cached value of current into the expr.
            // OK to do this even if later statements throw.
            this->current_chunk_->curr_ = this->curr_;

            // Do we have a expr with enough available memory already?
            if(this->current_chunk_->next_ && count <= this->current_chunk_->next_->size())
            {
                this->current_chunk_ = this->current_chunk_->next_;
                this->curr_ = this->current_chunk_->curr_ = this->current_chunk_->begin_ + count;
                this->end_ = this->current_chunk_->end_;
                this->begin_ = this->current_chunk_->begin_;
                std::fill_n(this->begin_, count, t);
                return this->begin_;
            }

            // grow exponentially
            std::size_t new_size = (std::max)(
                count
              , static_cast<std::size_t>(static_cast<double>(this->current_chunk_->size()) * 1.5)
            );

            // Create a new expr and insert it into the list
            this->current_chunk_ = new chunk(new_size, t, count, this->current_chunk_, this->current_chunk_->next_);
        }
        else
        {
            // first chunk is 256
            std::size_t new_size = (std::max)(count, static_cast<std::size_t>(256U));

            // Create a new expr and insert it into the list
            this->current_chunk_ = new chunk(new_size, t, count, 0, 0);
        }

        this->begin_ = this->current_chunk_->begin_;
        this->curr_ = this->current_chunk_->curr_;
        this->end_ = this->current_chunk_->end_;
        return this->begin_;
    }


    void unwind_chunk_()
    {
        // write the cached value of curr_ into current_chunk_
        this->current_chunk_->curr_ = this->begin_;
        // make the previous chunk the current
        this->current_chunk_ = this->current_chunk_->back_;

        // update the cache
        this->begin_ = this->current_chunk_->begin_;
        this->curr_ = this->current_chunk_->curr_;
        this->end_ = this->current_chunk_->end_;
    }


    bool in_current_chunk(T *ptr) const
    {
        return !std::less<void*>()(ptr, this->begin_) && std::less<void*>()(ptr, this->end_);
    }

    sequence_stack()
      : current_chunk_(0)
      , begin_(0)
      , curr_(0)
      , end_(0)
    {
    }


    ~sequence_stack()
    {
        this->clear();
    }

    void unwind()
    {
        if(this->current_chunk_)
        {
            while(this->current_chunk_->back_)
            {
                this->current_chunk_->curr_ = this->current_chunk_->begin_;
                this->current_chunk_ = this->current_chunk_->back_;
            }

            this->begin_ = this->curr_ = this->current_chunk_->curr_ = this->current_chunk_->begin_;
            this->end_ = this->current_chunk_->end_;
        }
    }


    void clear()
    {
        // walk to the front of the list
        this->unwind();

        // delete the list
        for(chunk *next; this->current_chunk_; this->current_chunk_ = next)
        {
            next = this->current_chunk_->next_;
            delete this->current_chunk_;
        }

        this->begin_ = this->curr_ = this->end_ = 0;
    }


    T *push_sequence(std::size_t count, T const &t)
    {
        // This is the ptr to return
        T *ptr = this->curr_;

        // Advance the high-water mark
        this->curr_ += count;

        // Check to see if we have overflowed this buffer
        if(std::less<void*>()(this->end_, this->curr_))
        {
            // oops, back this out.
            this->curr_ = ptr;

            // allocate a new block and return a ptr to the new memory
            return this->grow_(count, t);
        }

        return ptr;
    }


    void unwind_to(T *ptr)
    {
        while(!this->in_current_chunk(ptr))
        {
            // completely unwind the current chunk, move to the previous chunk
            this->unwind_chunk_();
        }
        this->current_chunk_->curr_ = this->curr_ = ptr;
    }

    void conserve()
    {
        if(this->current_chunk_)
        {
            for(chunk *next; this->current_chunk_->next_; this->current_chunk_->next_ = next)
            {
                next = this->current_chunk_->next_->next_;
                delete this->current_chunk_->next_;
            }
        }
    }

    boyer_moore(char_type const *begin, char_type const *end, Traits const &tr, bool icase)
      : begin_(begin)
      , last_(begin)
      , fold_()
      , find_fun_(
              icase
            ? (case_fold() ? &boyer_moore::find_nocase_fold_ : &boyer_moore::find_nocase_)
            : &boyer_moore::find_
        )
    {
        std::ptrdiff_t const uchar_max = UCHAR_MAX;
        std::ptrdiff_t diff = std::distance(begin, end);
        this->length_  = static_cast<unsigned char>((std::min)(diff, uchar_max));
        std::fill_n(static_cast<unsigned char *>(this->offsets_), uchar_max + 1, this->length_);
        --this->length_;

        icase ? this->init_(tr, case_fold()) : this->init_(tr, mpl::false_());
    }


    BidiIter find(BidiIter begin, BidiIter end, Traits const &tr) const
    {
        return (this->*this->find_fun_)(begin, end, tr);
    }


    void init_(Traits const &tr, mpl::false_)
    {
        for(unsigned char offset = this->length_; offset; --offset, ++this->last_)
        {
            this->offsets_[tr.hash(*this->last_)] = offset;
        }
    }

    BidiIter find_(BidiIter begin, BidiIter end, Traits const &tr) const
    {
        typedef typename boost::iterator_difference<BidiIter>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            char_type const *pat_tmp = this->last_;
            BidiIter str_tmp = begin;

            for(; tr.translate(*str_tmp) == *pat_tmp; --pat_tmp, --str_tmp)
            {
                if(pat_tmp == this->begin_)
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[tr.hash(tr.translate(*begin))];
        }

        return end;
    }

    BidiIter find_nocase_(BidiIter begin, BidiIter end, Traits const &tr) const
    {
        typedef typename boost::iterator_difference<BidiIter>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            char_type const *pat_tmp = this->last_;
            BidiIter str_tmp = begin;

            for(; tr.translate_nocase(*str_tmp) == *pat_tmp; --pat_tmp, --str_tmp)
            {
                if(pat_tmp == this->begin_)
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[tr.hash(tr.translate_nocase(*begin))];
        }

        return end;
    }

    BidiIter find_nocase_fold_(BidiIter begin, BidiIter end, Traits const &tr) const
    {
        typedef typename boost::iterator_difference<BidiIter>::type diff_type;
        diff_type const endpos = std::distance(begin, end);
        diff_type offset = static_cast<diff_type>(this->length_);

        for(diff_type curpos = offset; curpos < endpos; curpos += offset)
        {
            std::advance(begin, offset);

            string_type const *pat_tmp = &this->fold_.back();
            BidiIter str_tmp = begin;

            for(; pat_tmp->end() != std::find(pat_tmp->begin(), pat_tmp->end(), *str_tmp);
                --pat_tmp, --str_tmp)
            {
                if(pat_tmp == &this->fold_.front())
                {
                    return str_tmp;
                }
            }

            offset = this->offsets_[tr.hash(*begin)];
        }

        return end;
    }


            static type
            call(Iterator const& i)
            {
                return detail::ref(i.cons.car);
            }


            static type
            call(Iterator const& i)
            {
                return type(detail::ref(i.cons.cdr));
            }


            static type
            call(Cons& t)
            {
                return type(t);
            }


            static type
            call(Cons& t)
            {
                FUSION_RETURN_DEFAULT_CONSTRUCTED;
            }


        explicit cons_iterator(cons_type& cons_)
            : cons(cons_) {}

        cons_iterator() {}

        explicit cons_iterator(nil const&) {}

        cons_iterator() {}

        explicit cons_iterator(nil const&) {}


        cons()
          : car(), cdr() {}


    template <typename Car>
    inline cons<Car>
    make_cons(Car const& car)
    {
        return cons<Car>(car);
    }


    template <typename Car, typename Cdr>
    inline cons<Car, Cdr>
    make_cons(Car const& car, Cdr const& cdr)
    {
        return cons<Car, Cdr>(car, cdr);
    }

    template<typename ToChar, typename FromChar, typename Traits>
    inline ToChar
    char_cast(FromChar from, Traits const &, typename enable_if<is_same<ToChar, FromChar> >::type * = 0)
    {
        return from;
    }

        explicit widen_fun(Traits const &tr)
          : traits_(tr)
        {}


        result_type operator()(char ch) const
        {
            return this->traits_.widen(ch);
        }

        template<typename Traits>
        result_type operator()(From const &from, Traits const &) const
        {
            To to(detail::data_begin(from), detail::data_end(from));
            return to;
        }

        dont_care() {}


        template<typename T>
        dont_care(T const &) {}


    weak_iterator()
      : cur_()
      , iter_()
      , set_(0)
    {
    }

    filter_self(enable_reference_tracking<Derived> *self)
      : self_(self)
    {
    }


    bool operator ()(shared_ptr<Derived> const &that) const
    {
        return this->self_ != that.get();
    }

template<typename T>
void adl_swap(T &t1, T &t2)
{
    swap(t1, t2);
}


    void tracking_copy(Derived const &that)
    {
        if(&this->derived_() != &that)
        {
            this->raw_copy_(that);
            this->tracking_update();
        }
    }


    void tracking_clear()
    {
        this->raw_copy_(Derived());
    }

    void tracking_update()
    {
        // add "this" as a dependency to all the references
        this->update_references_();
        // notify our dependencies that we have new references
        this->update_dependents_();
    }


    void track_reference(enable_reference_tracking<Derived> &that)
    {
        // avoid some unbounded memory growth in certain circumstances by
        // opportunistically removing stale dependencies from "that"
        that.purge_stale_deps_();
        // add "that" as a reference
        this->refs_.insert(that.self_);
        // also inherit that's references
        this->refs_.insert(that.refs_.begin(), that.refs_.end());
    }


    long use_count() const
    {
        return this->cnt_;
    }


    void add_ref()
    {
        ++this->cnt_;
    }


    void release()
    {
        BOOST_ASSERT(0 < this->cnt_);
        if(0 == --this->cnt_)
        {
            this->refs_.clear();
            this->self_.reset();
        }
    }


    enable_reference_tracking()
      : refs_()
      , deps_()
      , self_()
      , cnt_(0)
    {
    }


    enable_reference_tracking(enable_reference_tracking<Derived> const &that)
      : refs_()
      , deps_()
      , self_()
      , cnt_(0)
    {
        this->operator =(that);
    }


    enable_reference_tracking<Derived> &operator =(enable_reference_tracking<Derived> const &that)
    {
        references_type(that.refs_).swap(this->refs_);
        return *this;
    }


    void swap(enable_reference_tracking<Derived> &that)
    {
        this->refs_.swap(that.refs_);
    }


    Derived &derived_()
    {
        return *static_cast<Derived *>(this);
    }


    void raw_copy_(Derived that)
    {
        detail::adl_swap(this->derived_(), that);
    }


    bool has_deps_() const
    {
        return !this->deps_.empty();
    }


    void update_references_()
    {
        typename references_type::iterator cur = this->refs_.begin();
        typename references_type::iterator end = this->refs_.end();
        for(; cur != end; ++cur)
        {
            // for each reference, add this as a dependency
            (*cur)->track_dependency_(*this);
        }
    }


    void update_dependents_()
    {
        // called whenever this regex object changes (i.e., is assigned to). it walks
        // the list of dependent regexes and updates *their* lists of references,
        // thereby spreading out the reference counting responsibility evenly.
        weak_iterator<Derived> cur(this->deps_.begin(), &this->deps_);
        weak_iterator<Derived> end(this->deps_.end(), &this->deps_);

        for(; cur != end; ++cur)
        {
            (*cur)->track_reference(*this);
        }
    }


    void track_dependency_(enable_reference_tracking<Derived> &dep)
    {
        if(this == &dep) // never add ourself as a dependency
            return;

        // add dep as a dependency
        this->deps_.insert(dep.self_);

        filter_self<Derived> not_self(this);
        weak_iterator<Derived> begin(dep.deps_.begin(), &dep.deps_);
        weak_iterator<Derived> end(dep.deps_.end(), &dep.deps_);

        // also inherit dep's dependencies
        this->deps_.insert(
            make_filter_iterator(not_self, begin, end)
          , make_filter_iterator(not_self, end, end)
        );
    }


    void purge_stale_deps_()
    {
        weak_iterator<Derived> cur(this->deps_.begin(), &this->deps_);
        weak_iterator<Derived> end(this->deps_.end(), &this->deps_);

        for(; cur != end; ++cur)
            ;
    }


template<typename Derived>
inline void intrusive_ptr_add_ref(enable_reference_tracking<Derived> *p)
{
    p->add_ref();
}


template<typename Derived>
inline void intrusive_ptr_release(enable_reference_tracking<Derived> *p)
{
    p->release();
}


    tracking_ptr()
      : impl_()
    {
    }


    tracking_ptr(tracking_ptr<element_type> const &that)
      : impl_()
    {
        this->operator =(that);
    }


    tracking_ptr<element_type> &operator =(tracking_ptr<element_type> const &that)
    {
        // Note: the copy-and-swap idiom doesn't work here if has_deps_()==true
        // because it invalidates references to the element_type object.
        if(this != &that)
        {
            if(that)
            {
                if(that.has_deps_() || this->has_deps_())
                {
                    this->fork_(); // deep copy, forks data if necessary
                    this->impl_->tracking_copy(*that);
                }
                else
                {
                    this->impl_ = that.impl_; // shallow, copy-on-write
                }
            }
            else if(*this)
            {
                this->impl_->tracking_clear();
            }
        }
        return *this;
    }

    void swap(tracking_ptr<element_type> &that) // throw()
    {
        this->impl_.swap(that.impl_);
    }


    hash_peek_bitset()
      : icase_(false)
      , bset_()
    {
    }


    std::size_t count() const
    {
        return this->bset_.count();
    }


    void set_all()
    {
        this->icase_ = false;
        this->bset_.set();
    }


    template<typename Traits>
    void set_char(char_type ch, bool icase, Traits const &tr)
    {
        if(this->test_icase_(icase))
        {
            ch = icase ? tr.translate_nocase(ch) : tr.translate(ch);
            this->bset_.set(tr.hash(ch));
        }
    }


    template<typename Traits>
    void set_range(char_type from, char_type to, bool no, bool icase, Traits const &tr)
    {
        int_type ifrom = std::char_traits<char_type>::to_int_type(from);
        int_type ito = std::char_traits<char_type>::to_int_type(to);
        BOOST_ASSERT(ifrom <= ito);
        // bound the computational complexity. BUGBUG could set the inverse range
        if(no || 256 < (ito - ifrom))
        {
            this->set_all();
        }
        else if(this->test_icase_(icase))
        {
            for(int_type i = ifrom; i <= ito; ++i)
            {
                char_type ch = std::char_traits<char_type>::to_char_type(i);
                ch = icase ? tr.translate_nocase(ch) : tr.translate(ch);
                this->bset_.set(tr.hash(ch));
            }
        }
    }


    template<typename Traits>
    void set_class(typename Traits::char_class_type char_class, bool no, Traits const &tr)
    {
        if(1 != sizeof(char_type))
        {
            // wide character set, no efficient way of filling in the bitset, so set them all to 1
            this->set_all();
        }
        else
        {
            for(std::size_t i = 0; i <= UCHAR_MAX; ++i)
            {
                char_type ch = std::char_traits<char_type>::to_char_type(static_cast<int_type>(i));
                if(no != tr.isctype(ch, char_class))
                {
                    this->bset_.set(i);
                }
            }
        }
    }


    void set_bitset(hash_peek_bitset<Char> const &that)
    {
        if(this->test_icase_(that.icase()))
        {
            this->bset_ |= that.bset_;
        }
    }


    void set_charset(basic_chset_8bit<Char> const &that, bool icase)
    {
        if(this->test_icase_(icase))
        {
            this->bset_ |= that.base();
        }
    }


    bool icase() const
    {
        return this->icase_;
    }


    template<typename Traits>
    bool test(char_type ch, Traits const &tr) const
    {
        ch = this->icase_ ? tr.translate_nocase(ch) : tr.translate(ch);
        return this->bset_.test(tr.hash(ch));
    }

    bool test_icase_(bool icase)
    {
        std::size_t count = this->bset_.count();

        if(256 == count)
        {
            return false; // all set already, nothing to do
        }
        else if(0 != count && this->icase_ != icase)
        {
            this->set_all(); // icase mismatch! set all and bail
            return false;
        }

        this->icase_ = icase;
        return true;
    }

    width(std::size_t val = 0)
      : value_(val)
    {
    }


    bool operator !() const
    {
        return !this->value_;
    }


    width &operator +=(width const &that)
    {
        this->value_ =
            !is_unknown(*this) && !is_unknown(that)
          ? this->value_ + that.value_
          : unknown_width();
        return *this;
    }


    width &operator |=(width const &that)
    {
        this->value_ =
            this->value_ == that.value_
          ? this->value_
          : unknown_width();
        return *this;
    }


    std::size_t value() const
    {
        return this->value_;
    }


inline bool is_unknown(width const &that)
{
    return unknown_width::value == that.value();
}


inline bool operator ==(width const &left, width const &right)
{
    return left.value() == right.value();
}


inline bool operator !=(width const &left, width const &right)
{
    return left.value() != right.value();
}


inline width operator +(width left, width const &right)
{
    return left += right;
}


inline width operator |(width left, width const &right)
{
    return left |= right;
}


        template<typename Trans>
        void load(Map const &map, Trans trans)
        {
            iterator begin = boost::begin(map);
            iterator end = boost::end(map);
            node* root_p = this->root.get();
            for(; begin != end; ++begin)
            {
                key_iterator kbegin = boost::begin(begin->first);
                key_iterator kend = boost::end(begin->first);
                root_p = this->insert(root_p, kbegin, kend, &begin->second, trans);
            }
            this->root.reset(root_p);
        }


        template<typename BidiIter, typename Trans>
        result_type operator ()(BidiIter &begin, BidiIter end, Trans trans) const
        {
            return this->search(begin, end, trans, this->root.get());
        }


        template<typename Sink>
        void peek(Sink const &sink) const
        {
            this->peek_(this->root.get(), sink);
        }

            node(char_type c)
              : ch(c)
              , lo(0)
              , eq(0)
              , hi(0)
              #ifdef BOOST_DISABLE_THREADS
              , tau(0)
              #endif
            {}


            ~node()
            {
                delete lo;
                if (ch)
                    delete eq;
                delete hi;
            }


            void swap(node& that)
            {
                std::swap(ch, that.ch);
                std::swap(lo, that.lo);
                std::swap(eq, that.eq);
                std::swap(hi, that.hi);
                #ifdef BOOST_DISABLE_THREADS
                std::swap(tau, that.tau);
                #endif
            }

        template<typename Trans>
        node* insert(node* p, key_iterator &begin, key_iterator end, result_type r, Trans trans) const
        {
            char_type c1 = 0;

            if(begin != end)
            {
                c1 = trans(*begin);
            }

            if(!p)
            {
                p = new node(c1);
            }

            if(c1 < p->ch)
            {
                p->lo = this->insert(p->lo, begin, end, r, trans);
            }
            else if(c1 == p->ch)
            {
                if(0 == c1)
                {
                    p->result = r;
                }
                else
                {
                    p->eq = this->insert(p->eq, ++begin, end, r, trans);
                }
            }
            else
            {
                p->hi = this->insert(p->hi, begin, end, r, trans);
            }

            return p;
        }

        template<typename BidiIter, typename Trans>
        result_type search(BidiIter &begin, BidiIter end, Trans trans, node* p) const
        {
            result_type r = 0;
            #ifdef BOOST_DISABLE_THREADS
            node* p2 = p;
            bool left = false;
            #endif
            char_type c1 = (begin != end ? trans(*begin) : 0);
            while(p)
            {
                #ifdef BOOST_DISABLE_THREADS
                ++p->tau;
                #endif
                if(c1 == p->ch)
                {
                    // conditional rotation test
                    #ifdef BOOST_DISABLE_THREADS
                    if (this->cond_rotation(left, p, p2))
                        p = p2;
                    #endif
                    if (0 == p->ch)
                    {
                        // it's a match!
                        r = p->result;
                    }
                    if(begin == end)
                        break;
                    ++begin;
                    p = p->eq;
                    // search for the longest match first
                    r = search(begin,end,trans,p);
                    if (0 == r)
                    {
                        // search for a match ending here
                        r = search(end,end,trans,p);
                        if (0 == r)
                        {
                            --begin;
                        }
                    }
                    break;
                }
                else if(c1 < p->ch)
                {
                    #ifdef BOOST_DISABLE_THREADS
                    left = true;
                    p2 = p;
                    #endif
                    p = p->lo;
                }
                else // (c1 > p->ch)
                {
                    #ifdef BOOST_DISABLE_THREADS
                    left = false;
                    p2 = p;
                    #endif
                    p = p->hi;
                }
            }
            return r;
        }


        template<typename Sink>
        void peek_(node const *const &p, Sink const &sink) const
        {
            if(p)
            {
                sink(p->ch);
                this->peek_(p->lo, sink);
                this->peek_(p->hi, sink);
            }
        }

    bool operator()(range<Char> const &x, range<Char> const &y) const
    {
        return x.first_ < y.first_;
    }


    compound_charset()
      : base_type()
      , complement_(false)
      , has_posix_(false)
      , posix_yes_()
      , posix_no_()
    {
    }

    bool test_posix(char_type ch, Traits const &tr) const
    {
        not_posix_pred const pred = {ch, &tr};
        return tr.isctype(ch, this->posix_yes_)
            || any(this->posix_no_.begin(), this->posix_no_.end(), pred);
    }

template<typename Char, typename Traits>
inline void set_char(compound_charset<Traits> &chset, Char ch, Traits const &tr, bool icase)
{
    chset.set_char(ch, tr, icase);
}


template<typename Char, typename Traits>
inline void set_range(compound_charset<Traits> &chset, Char from, Char to, Traits const &tr, bool icase)
{
    chset.set_range(from, to, tr, icase);
}


template<typename Traits>
inline void set_class(compound_charset<Traits> &chset, typename Traits::char_class_type char_class, bool no, Traits const &)
{
    chset.set_class(char_class, no);
}

        template<typename Traits>
        void imbue(Traits const &tr)
        {
        }

        template<typename Traits>
        static void imbue(Traits const &)
        {
        }

        template<typename Traits>
        static void imbue(Traits const &)
        {
        }

    c_regex_traits(locale_type const &loc = locale_type())
      : base_type()
    {
        this->imbue(loc);
    }

    bool operator ==(c_regex_traits<char_type> const &) const
    {
        return true;
    }

    bool operator !=(c_regex_traits<char_type> const &) const
    {
        return false;
    }

    static unsigned char hash(char_type ch)
    {
        return static_cast<unsigned char>(std::char_traits<Char>::to_int_type(ch));
    }

    static char_type translate(char_type ch)
    {
        return ch;
    }

    static char_type translate_nocase(char_type ch)
    {
        return detail::c_tolower(ch);
    }

    static char_type tolower(char_type ch)
    {
        return detail::c_tolower(ch);
    }

    static char_type toupper(char_type ch)
    {
        return detail::c_toupper(ch);
    }

    string_type fold_case(char_type ch) const
    {
        BOOST_MPL_ASSERT((is_same<char_type, char>));
        char_type ntcs[] = {
            detail::c_tolower(ch)
          , detail::c_toupper(ch)
          , 0
        };
        if(ntcs[1] == ntcs[0])
            ntcs[1] = 0;
        return string_type(ntcs);
    }

    static bool in_range(char_type first, char_type last, char_type ch)
    {
        return first <= ch && ch <= last;
    }

    static bool in_range_nocase(char_type first, char_type last, char_type ch)
    {
        return c_regex_traits::in_range(first, last, ch)
            || c_regex_traits::in_range(first, last, detail::c_tolower(ch))
            || c_regex_traits::in_range(first, last, detail::c_toupper(ch));
    }

    template<typename FwdIter>
    static string_type transform(FwdIter begin, FwdIter end)
    {
        BOOST_ASSERT(false); // BUGBUG implement me
    }

    template<typename FwdIter>
    static string_type transform_primary(FwdIter begin, FwdIter end)
    {
        BOOST_ASSERT(false); // BUGBUG implement me
    }

    template<typename FwdIter>
    static string_type lookup_collatename(FwdIter begin, FwdIter end)
    {
        BOOST_ASSERT(false); // BUGBUG implement me
    }

    template<typename FwdIter>
    static char_class_type lookup_classname(FwdIter begin, FwdIter end, bool icase)
    {
        return detail::char_class_impl<char_type>::lookup_classname(begin, end, icase);
    }

    static bool isctype(char_type ch, char_class_type mask)
    {
        return detail::char_class_impl<char_type>::isctype(ch, mask);
    }

    locale_type imbue(locale_type loc)
    {
        this->base_type::imbue(*this);
        return loc;
    }

    static locale_type getloc()
    {
        locale_type loc;
        return loc;
    }

    null_regex_traits(locale_type = locale_type())
    {
    }

    bool operator ==(null_regex_traits<char_type> const &that) const
    {
        detail::ignore_unused(that);
        return true;
    }

    bool operator !=(null_regex_traits<char_type> const &that) const
    {
        detail::ignore_unused(that);
        return false;
    }

    char_type widen(char ch) const
    {
        return char_type(ch);
    }

    static unsigned char hash(char_type ch)
    {
        return static_cast<unsigned char>(ch);
    }

    static char_type translate(char_type ch)
    {
        return ch;
    }

    static char_type translate_nocase(char_type ch)
    {
        return ch;
    }

    static bool in_range(char_type first, char_type last, char_type ch)
    {
        return first <= ch && ch <= last;
    }

    static bool in_range_nocase(char_type first, char_type last, char_type ch)
    {
        return first <= ch && ch <= last;
    }

    template<typename FwdIter>
    static string_type transform(FwdIter begin, FwdIter end)
    {
        return string_type(begin, end);
    }

    template<typename FwdIter>
    static string_type transform_primary(FwdIter begin, FwdIter end)
    {
        return string_type(begin, end);
    }

    template<typename FwdIter>
    static string_type lookup_collatename(FwdIter begin, FwdIter end)
    {
        detail::ignore_unused(begin);
        detail::ignore_unused(end);
        return string_type();
    }

    template<typename FwdIter>
    static char_class_type lookup_classname(FwdIter begin, FwdIter end, bool icase)
    {
        detail::ignore_unused(begin);
        detail::ignore_unused(end);
        detail::ignore_unused(icase);
        return 0;
    }

    static bool isctype(char_type ch, char_class_type mask)
    {
        detail::ignore_unused(ch);
        detail::ignore_unused(mask);
        return false;
    }

    static int value(char_type ch, int radix)
    {
        detail::ignore_unused(ch);
        detail::ignore_unused(radix);
        return -1;
    }

    static locale_type imbue(locale_type loc)
    {
        return loc;
    }

    static locale_type getloc()
    {
        return locale_type();
    }

        void imbue(std::locale const &)
        {
        }


        static bool is(std::ctype<Char> const &ct, Char ch, umaskex_t mask)
        {
            #ifndef BOOST_XPRESSIVE_BUGGY_CTYPE_FACET

            if(ct.is((std::ctype_base::mask)(umask_t)mask, ch))
            {
                return true;
            }

            // HACKHACK Cygwin and mingw have buggy ctype facets for wchar_t
            #if defined(__CYGWIN__) || defined(__MINGW32_VERSION)
            if (std::ctype_base::xdigit == ((std::ctype_base::mask)(umask_t)mask & std::ctype_base::xdigit))
            {
                typename std::char_traits<Char>::int_type i = std::char_traits<Char>::to_int_type(ch);
                if(UCHAR_MAX >= i && std::isxdigit(static_cast<int>(i)))
                    return true;
            }
            #endif

            #else

            umaskex_t tmp = mask & ~non_std_ctype_masks;
            for(umaskex_t i; 0 != (i = (tmp & (~tmp+1))); tmp &= ~i)
            {
                std::ctype_base::mask m = (std::ctype_base::mask)(umask_t)std_masks[mylog2(i)];
                if(ct.is(m, ch))
                {
                    return true;
                }
            }

            #endif

            return ((mask & non_std_ctype_blank) && cpp_regex_traits_base::is_blank(ch))
                || ((mask & non_std_ctype_underscore) && cpp_regex_traits_base::is_underscore(ch))
                || ((mask & non_std_ctype_newline) && cpp_regex_traits_base::is_newline(ch));
        }

        static bool is_blank(Char ch)
        {
            BOOST_MPL_ASSERT_RELATION('\t', ==, L'\t');
            BOOST_MPL_ASSERT_RELATION(' ', ==, L' ');
            return L' ' == ch || L'\t' == ch;
        }


        static bool is_underscore(Char ch)
        {
            BOOST_MPL_ASSERT_RELATION('_', ==, L'_');
            return L'_' == ch;
        }


        static bool is_newline(Char ch)
        {
            BOOST_MPL_ASSERT_RELATION('\r', ==, L'\r');
            BOOST_MPL_ASSERT_RELATION('\n', ==, L'\n');
            BOOST_MPL_ASSERT_RELATION('\f', ==, L'\f');
            return L'\r' == ch || L'\n' == ch || L'\f' == ch
                || (1 < SizeOfChar && (0x2028u == ch || 0x2029u == ch || 0x85u == ch));
        }

        void imbue(std::locale const &loc)
        {
            int i = 0;
            Char allchars[UCHAR_MAX + 1];
            for(i = 0; i <= static_cast<int>(UCHAR_MAX); ++i)
            {
                allchars[i] = static_cast<Char>(i);
            }

            std::ctype<Char> const &ct = BOOST_USE_FACET(std::ctype<Char>, loc);
            std::ctype_base::mask tmp[UCHAR_MAX + 1];
            ct.is(allchars, allchars + UCHAR_MAX + 1, tmp);
            for(i = 0; i <= static_cast<int>(UCHAR_MAX); ++i)
            {
                this->masks_[i] = static_cast<umask_t>(tmp[i]);
                BOOST_ASSERT(0 == (this->masks_[i] & non_std_ctype_masks));
            }

            this->masks_[static_cast<unsigned char>('_')] |= non_std_ctype_underscore;
            this->masks_[static_cast<unsigned char>(' ')] |= non_std_ctype_blank;
            this->masks_[static_cast<unsigned char>('\t')] |= non_std_ctype_blank;
            this->masks_[static_cast<unsigned char>('\n')] |= non_std_ctype_newline;
            this->masks_[static_cast<unsigned char>('\r')] |= non_std_ctype_newline;
            this->masks_[static_cast<unsigned char>('\f')] |= non_std_ctype_newline;
        }


        bool is(std::ctype<Char> const &, Char ch, umaskex_t mask) const
        {
            return 0 != (this->masks_[static_cast<unsigned char>(ch)] & mask);
        }

    cpp_regex_traits(locale_type const &loc = locale_type())
      : base_type()
      , loc_()
    {
        this->imbue(loc);
    }

    bool operator ==(cpp_regex_traits<char_type> const &that) const
    {
        return this->loc_ == that.loc_;
    }

    bool operator !=(cpp_regex_traits<char_type> const &that) const
    {
        return this->loc_ != that.loc_;
    }

    char_type widen(char ch) const
    {
        return this->ctype_->widen(ch);
    }

    static unsigned char hash(char_type ch)
    {
        return static_cast<unsigned char>(std::char_traits<Char>::to_int_type(ch));
    }

    static char_type translate(char_type ch)
    {
        return ch;
    }

    char_type translate_nocase(char_type ch) const
    {
        return this->ctype_->tolower(ch);
    }

    char_type tolower(char_type ch) const
    {
        return this->ctype_->tolower(ch);
    }

    char_type toupper(char_type ch) const
    {
        return this->ctype_->toupper(ch);
    }

    string_type fold_case(char_type ch) const
    {
        BOOST_MPL_ASSERT((is_same<char_type, char>));
        char_type ntcs[] = {
            this->ctype_->tolower(ch)
          , this->ctype_->toupper(ch)
          , 0
        };
        if(ntcs[1] == ntcs[0])
            ntcs[1] = 0;
        return string_type(ntcs);
    }

    static bool in_range(char_type first, char_type last, char_type ch)
    {
        return first <= ch && ch <= last;
    }

    bool in_range_nocase(char_type first, char_type last, char_type ch) const
    {
        // NOTE: this default implementation doesn't do proper Unicode
        // case folding, but this is the best we can do with the standard
        // std::ctype facet.
        return this->in_range(first, last, ch)
            || this->in_range(first, last, this->ctype_->toupper(ch))
            || this->in_range(first, last, this->ctype_->tolower(ch));
    }

    template<typename FwdIter>
    string_type transform(FwdIter, FwdIter) const
    {
        //string_type str(begin, end);
        //return this->transform(str.data(), str.data() + str.size());

        BOOST_ASSERT(false);
        return string_type();
    }

    template<typename FwdIter>
    string_type transform_primary(FwdIter, FwdIter ) const
    {
        BOOST_ASSERT(false); // TODO implement me
        return string_type();
    }

    template<typename FwdIter>
    string_type lookup_collatename(FwdIter, FwdIter) const
    {
        BOOST_ASSERT(false); // TODO implement me
        return string_type();
    }

    template<typename FwdIter>
    char_class_type lookup_classname(FwdIter begin, FwdIter end, bool icase) const
    {
        static detail::umaskex_t const icase_masks =
            detail::std_ctype_lower | detail::std_ctype_upper;

        BOOST_ASSERT(begin != end);
        char_class_type char_class = this->lookup_classname_impl_(begin, end);
        if(0 == char_class)
        {
            // convert the string to lowercase
            string_type classname(begin, end);
            for(typename string_type::size_type i = 0, len = classname.size(); i < len; ++i)
            {
                classname[i] = this->translate_nocase(classname[i]);
            }
            char_class = this->lookup_classname_impl_(classname.begin(), classname.end());
        }
        // erase case-sensitivity if icase==true
        if(icase && 0 != (char_class & icase_masks))
        {
            char_class |= icase_masks;
        }
        return char_class;
    }

    bool isctype(char_type ch, char_class_type mask) const
    {
        return this->base_type::is(*this->ctype_, ch, mask);
    }

    int value(char_type ch, int radix) const
    {
        BOOST_ASSERT(8 == radix || 10 == radix || 16 == radix);
        int val = -1;
        std::basic_stringstream<char_type> str;
        str.imbue(this->getloc());
        str << (8 == radix ? std::oct : (16 == radix ? std::hex : std::dec));
        str.put(ch);
        str >> val;
        return str.fail() ? -1 : val;
    }

    locale_type imbue(locale_type loc)
    {
        locale_type old_loc = this->loc_;
        this->loc_ = loc;
        this->ctype_ = &BOOST_USE_FACET(std::ctype<char_type>, this->loc_);
        //this->collate_ = &BOOST_USE_FACET(std::collate<char_type>, this->loc_);
        this->base_type::imbue(this->loc_);
        return old_loc;
    }

    locale_type getloc() const
    {
        return this->loc_;
    }

    static char_class_pair const &char_class(std::size_t j)
    {
        static BOOST_CONSTEXPR_OR_CONST char_class_pair s_char_class_map[] =
        {
            { BOOST_XPR_CSTR_(char_type, "alnum"),  detail::std_ctype_alnum }
          , { BOOST_XPR_CSTR_(char_type, "alpha"),  detail::std_ctype_alpha }
          , { BOOST_XPR_CSTR_(char_type, "blank"),  detail::non_std_ctype_blank }
          , { BOOST_XPR_CSTR_(char_type, "cntrl"),  detail::std_ctype_cntrl }
          , { BOOST_XPR_CSTR_(char_type, "d"),      detail::std_ctype_digit }
          , { BOOST_XPR_CSTR_(char_type, "digit"),  detail::std_ctype_digit }
          , { BOOST_XPR_CSTR_(char_type, "graph"),  detail::std_ctype_graph }
          , { BOOST_XPR_CSTR_(char_type, "lower"),  detail::std_ctype_lower }
          , { BOOST_XPR_CSTR_(char_type, "newline"),detail::non_std_ctype_newline }
          , { BOOST_XPR_CSTR_(char_type, "print"),  detail::std_ctype_print }
          , { BOOST_XPR_CSTR_(char_type, "punct"),  detail::std_ctype_punct }
          , { BOOST_XPR_CSTR_(char_type, "s"),      detail::std_ctype_space }
          , { BOOST_XPR_CSTR_(char_type, "space"),  detail::std_ctype_space }
          , { BOOST_XPR_CSTR_(char_type, "upper"),  detail::std_ctype_upper }
          , { BOOST_XPR_CSTR_(char_type, "w"),      detail::std_ctype_alnum | detail::non_std_ctype_underscore }
          , { BOOST_XPR_CSTR_(char_type, "xdigit"), detail::std_ctype_xdigit }
          , { 0, 0 }
        };
        return s_char_class_map[j];
    }

    template<typename FwdIter>
    static char_class_type lookup_classname_impl_(FwdIter begin, FwdIter end)
    {
        // find the classname
        typedef cpp_regex_traits<Char> this_t;
        for(std::size_t j = 0; 0 != this_t::char_class(j).class_name_; ++j)
        {
            if(this_t::compare_(this_t::char_class(j).class_name_, begin, end))
            {
                return this_t::char_class(j).class_type_;
            }
        }
        return 0;
    }

    template<typename FwdIter>
    static bool compare_(char_type const *name, FwdIter begin, FwdIter end)
    {
        for(; *name && begin != end; ++name, ++begin)
        {
            if(*name != *begin)
            {
                return false;
            }
        }
        return !*name && begin == end;
    }

inline bool isnewline(char ch)
{
    switch(ch)
    {
    case L'\n': case L'\r': case L'\f':
        return true;
    default:
        return false;
    }
}

inline bool iswnewline(wchar_t ch)
{
    switch(ch)
    {
    case L'\n': case L'\r': case L'\f': case 0x2028u: case 0x2029u: case 0x85u:
        return true;
    default:
        return false;
    }
}

template<typename FwdIter>
inline std::string classname_a(FwdIter begin, FwdIter end)
{
    std::string name(begin, end);
    for(std::size_t i = 0; i < name.size(); ++i)
    {
        using namespace std;
        name[i] = static_cast<char>(tolower(static_cast<unsigned char>(name[i])));
    }
    return name;
}

template<typename FwdIter>
inline std::wstring classname_w(FwdIter begin, FwdIter end)
{
    std::wstring name(begin, end);
    for(std::size_t i = 0; i < name.size(); ++i)
    {
        using namespace std;
        name[i] = towlower(name[i]);
    }
    return name;
}


    template<typename FwdIter>
    static char_class_type lookup_classname(FwdIter begin, FwdIter end, bool icase)
    {
        using namespace std;
        string const name = classname_a(begin, end);
        if(name == "alnum")     return char_class_alpha|char_class_digit;
        if(name == "alpha")     return char_class_alpha;
        if(name == "blank")     return char_class_blank;
        if(name == "cntrl")     return char_class_cntrl;
        if(name == "d")         return char_class_digit;
        if(name == "digit")     return char_class_digit;
        if(name == "graph")     return char_class_punct|char_class_alpha|char_class_digit;
        if(name == "lower")     return icase ? (char_class_lower|char_class_upper) : char_class_lower;
        if(name == "newline")   return char_class_newline;
        if(name == "print")     return char_class_blank|char_class_punct|char_class_alpha|char_class_digit;
        if(name == "punct")     return char_class_punct;
        if(name == "s")         return char_class_space;
        if(name == "space")     return char_class_space;
        if(name == "upper")     return icase ? (char_class_upper|char_class_lower) : char_class_upper;
        if(name == "w")         return char_class_alpha|char_class_digit|char_class_underscore;
        if(name == "xdigit")    return char_class_xdigit;
        return 0;
    }


    static bool isctype(char ch, char_class_type mask)
    {
        using namespace std;
        unsigned char uch = static_cast<unsigned char>(ch);
        return ((char_class_alpha & mask) && isalpha(uch))
            || ((char_class_blank & mask) && (' ' == ch || '\t' == ch)) // BUGBUG
            || ((char_class_cntrl & mask) && iscntrl(uch))
            || ((char_class_digit & mask) && isdigit(uch))
            || ((char_class_lower & mask) && islower(uch))
            || ((char_class_newline & mask) && detail::isnewline(ch))
            || ((char_class_punct & mask) && ispunct(uch))
            || ((char_class_space & mask) && isspace(uch))
            || ((char_class_upper & mask) && isupper(uch))
            || ((char_class_underscore & mask) && '_' == ch)
            || ((char_class_xdigit & mask) && isxdigit(uch))
            ;
    }


    template<typename FwdIter>
    static char_class_type lookup_classname(FwdIter begin, FwdIter end, bool icase)
    {
        using namespace std;
        wstring const name = classname_w(begin, end);
        if(name == L"alnum")    return char_class_alpha|char_class_digit;
        if(name == L"alpha")    return char_class_alpha;
        if(name == L"blank")    return char_class_blank;
        if(name == L"cntrl")    return char_class_cntrl;
        if(name == L"d")        return char_class_digit;
        if(name == L"digit")    return char_class_digit;
        if(name == L"graph")    return char_class_punct|char_class_alpha|char_class_digit;
        if(name == L"newline")  return char_class_newline;
        if(name == L"lower")    return icase ? (char_class_lower|char_class_upper) : char_class_lower;
        if(name == L"print")    return char_class_blank|char_class_punct|char_class_alpha|char_class_digit;
        if(name == L"punct")    return char_class_punct;
        if(name == L"s")        return char_class_space;
        if(name == L"space")    return char_class_space;
        if(name == L"upper")    return icase ? (char_class_upper|char_class_lower) : char_class_upper;
        if(name == L"w")        return char_class_alpha|char_class_digit|char_class_underscore;
        if(name == L"xdigit")   return char_class_xdigit;
        return 0;
    }


    static bool isctype(wchar_t ch, char_class_type mask)
    {
        using namespace std;
        return ((char_class_alpha & mask) && iswalpha(ch))
            || ((char_class_blank & mask) && (L' ' == ch || L'\t' == ch)) // BUGBUG
            || ((char_class_cntrl & mask) && iswcntrl(ch))
            || ((char_class_digit & mask) && iswdigit(ch))
            || ((char_class_lower & mask) && iswlower(ch))
            || ((char_class_newline & mask) && detail::iswnewline(ch))
            || ((char_class_punct & mask) && iswpunct(ch))
            || ((char_class_space & mask) && iswspace(ch))
            || ((char_class_upper & mask) && iswupper(ch))
            || ((char_class_underscore & mask) && L'_' == ch)
            || ((char_class_xdigit & mask) && iswxdigit(ch))
            ;
    }
