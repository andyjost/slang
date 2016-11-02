

    explicit  ios_flags_saver( state_type &s )
        : s_save_( s ), a_save_( s.flags() )
        {}

    ios_flags_saver( state_type &s, aspect_type const &a )
        : s_save_( s ), a_save_( s.flags(a) )
        {}

    ~ios_flags_saver()
        { this->restore(); }


    void  restore()
        { s_save_.flags( a_save_ ); }


    explicit  ios_precision_saver( state_type &s )
        : s_save_( s ), a_save_( s.precision() )
        {}

    ios_precision_saver( state_type &s, aspect_type const &a )
        : s_save_( s ), a_save_( s.precision(a) )
        {}

    ~ios_precision_saver()
        { this->restore(); }


    void  restore()
        { s_save_.precision( a_save_ ); }


    explicit  ios_width_saver( state_type &s )
        : s_save_( s ), a_save_( s.width() )
        {}

    ios_width_saver( state_type &s, aspect_type const &a )
        : s_save_( s ), a_save_( s.width(a) )
        {}

    ~ios_width_saver()
        { this->restore(); }


    void  restore()
        { s_save_.width( a_save_ ); }


    explicit  basic_ios_iostate_saver( state_type &s )
        : s_save_( s ), a_save_( s.rdstate() )
        {}

    ~basic_ios_iostate_saver()
        { this->restore(); }


    void  restore()
        { s_save_.clear( a_save_ ); }


    explicit  basic_ios_exception_saver( state_type &s )
        : s_save_( s ), a_save_( s.exceptions() )
        {}

    ~basic_ios_exception_saver()
        { this->restore(); }


    void  restore()
        { s_save_.exceptions( a_save_ ); }


    explicit  basic_ios_tie_saver( state_type &s )
        : s_save_( s ), a_save_( s.tie() )
        {}

    ~basic_ios_tie_saver()
        { this->restore(); }


    void  restore()
        { s_save_.tie( a_save_ ); }


    explicit  basic_ios_rdbuf_saver( state_type &s )
        : s_save_( s ), a_save_( s.rdbuf() )
        {}

    ~basic_ios_rdbuf_saver()
        { this->restore(); }


    void  restore()
        { s_save_.rdbuf( a_save_ ); }


    explicit  basic_ios_fill_saver( state_type &s )
        : s_save_( s ), a_save_( s.fill() )
        {}

    ~basic_ios_fill_saver()
        { this->restore(); }


    void  restore()
        { s_save_.fill( a_save_ ); }


    explicit basic_ios_locale_saver( state_type &s )
        : s_save_( s ), a_save_( s.getloc() )
        {}

    ~basic_ios_locale_saver()
        { this->restore(); }


    void  restore()
        { s_save_.imbue( a_save_ ); }


    explicit ios_iword_saver( state_type &s, index_type i )
        : s_save_( s ), a_save_( s.iword(i) ), i_save_( i )
        {}

    ios_iword_saver( state_type &s, index_type i, aspect_type const &a )
        : s_save_( s ), a_save_( s.iword(i) ), i_save_( i )
        { s.iword(i) = a; }

    ~ios_iword_saver()
        { this->restore(); }


    void  restore()
        { s_save_.iword( i_save_ ) = a_save_; }


    explicit  ios_pword_saver( state_type &s, index_type i )
        : s_save_( s ), a_save_( s.pword(i) ), i_save_( i )
        {}

    ios_pword_saver( state_type &s, index_type i, aspect_type const &a )
        : s_save_( s ), a_save_( s.pword(i) ), i_save_( i )
        { s.pword(i) = a; }

    ~ios_pword_saver()
        { this->restore(); }


    void  restore()
        { s_save_.pword( i_save_ ) = a_save_; }


    explicit  ios_base_all_saver( state_type &s )
        : s_save_( s ), a1_save_( s.flags() ), a2_save_( s.precision() )
        , a3_save_( s.width() )
        {}


    ~ios_base_all_saver()
        { this->restore(); }


    void  restore()
    {
        s_save_.width( a3_save_ );
        s_save_.precision( a2_save_ );
        s_save_.flags( a1_save_ );
    }


    explicit  basic_ios_all_saver( state_type &s )
        : s_save_( s ), a1_save_( s.flags() ), a2_save_( s.precision() )
        , a3_save_( s.width() ), a4_save_( s.rdstate() )
        , a5_save_( s.exceptions() ), a6_save_( s.tie() )
        , a7_save_( s.rdbuf() ), a8_save_( s.fill() )
        #ifndef BOOST_NO_STD_LOCALE
        , a9_save_( s.getloc() )
        #endif
        {}


    ~basic_ios_all_saver()
        { this->restore(); }


    void  restore()
    {
        #ifndef BOOST_NO_STD_LOCALE
        s_save_.imbue( a9_save_ );
        #endif
        s_save_.fill( a8_save_ );
        s_save_.rdbuf( a7_save_ );
        s_save_.tie( a6_save_ );
        s_save_.exceptions( a5_save_ );
        s_save_.clear( a4_save_ );
        s_save_.width( a3_save_ );
        s_save_.precision( a2_save_ );
        s_save_.flags( a1_save_ );
    }


    ios_all_word_saver( state_type &s, index_type i )
        : s_save_( s ), i_save_( i ), a1_save_( s.iword(i) )
        , a2_save_( s.pword(i) )
        {}


    ~ios_all_word_saver()
        { this->restore(); }


    void  restore()
    {
        s_save_.pword( i_save_ ) = a2_save_;
        s_save_.iword( i_save_ ) = a1_save_;
    }


        quoted_proxy(String s_, Char escape_, Char delim_)
          : string(s_), escape(escape_), delim(delim_) {}
