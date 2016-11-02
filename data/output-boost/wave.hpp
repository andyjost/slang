
inline bool
need_cpp(language_support language)
{
    return (language & ~support_option_mask) == support_cpp;
}


inline bool
need_cpp0x(language_support language)
{
    return false;
}

inline bool
need_variadics(language_support language)
{
    return false;
}

inline language_support
enable_variadics(language_support language, bool enable = true)
{
    return language;
}

inline bool
need_c99(language_support language)
{
    return false;
}

inline language_support
get_support_options(language_support language)
{
    return static_cast<language_support>(language & support_option_mask);
}

inline language_support
set_support_options(language_support language, language_support option)
{
    return static_cast<language_support>(
        (language & ~support_option_mask) | (option & support_option_mask));
}
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)        // support_option_convert_trigraphs
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
BOOST_WAVE_OPTION(include_guard_detection)  // support_option_include_guard_detection
#endif
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
BOOST_WAVE_OPTION(variadics)                // support_option_variadics
#endif
#if BOOST_WAVE_EMIT_PRAGMA_DIRECTIVES != 0
BOOST_WAVE_OPTION(emit_pragma_directives)   // support_option_emit_pragma_directives
#endif
BOOST_WAVE_OPTION(insert_whitespace)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)        // support_option_convert_trigraphs
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
BOOST_WAVE_OPTION(include_guard_detection)  // support_option_include_guard_detection
#endif
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
BOOST_WAVE_OPTION(variadics)                // support_option_variadics
#endif
#if BOOST_WAVE_EMIT_PRAGMA_DIRECTIVES != 0
BOOST_WAVE_OPTION(emit_pragma_directives)   // support_option_emit_pragma_directives
#endif
BOOST_WAVE_OPTION(insert_whitespace)
                                        \
    inline bool need_ ## option(language_support language)                    \
    {                                                                         \
        return (language & support_option_ ## option) ? true : false;         \
    }                                                                         \
    /**/

#define BOOST_WAVE_ENABLE_OPTION(option)                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)        // support_option_convert_trigraphs
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
BOOST_WAVE_OPTION(include_guard_detection)  // support_option_include_guard_detection
#endif
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
BOOST_WAVE_OPTION(variadics)                // support_option_variadics
#endif
#if BOOST_WAVE_EMIT_PRAGMA_DIRECTIVES != 0
BOOST_WAVE_OPTION(emit_pragma_directives)   // support_option_emit_pragma_directives
#endif
BOOST_WAVE_OPTION(insert_whitespace)        // support_option_insert_whitespace
BOOST_WAVE_OPTION(emit_contnewlines)
                                      \
    inline language_support                                                   \
    enable_ ## option(language_support language, bool enable = true)          \
    {                                                                         \
        if (enable)                                                           \
            return static_cast<language_support>(language | support_option_ ## option); \
        return static_cast<language_support>(language & ~support_option_ ## option);    \
    }                                                                         \
    /**/

#define BOOST_WAVE_OPTION(option)                                             \
    BOOST_WAVE_NEED_OPTION(option)                                            \
    BOOST_WAVE_ENABLE_OPTION(option)                                          \
    /**/

///////////////////////////////////////////////////////////////////////////////
BOOST_WAVE_OPTION(long_long)                // support_option_long_long
BOOST_WAVE_OPTION(no_character_validation)  // support_option_no_character_validation
BOOST_WAVE_OPTION(preserve_comments)        // support_option_preserve_comments
BOOST_WAVE_OPTION(prefer_pp_numbers)        // support_option_prefer_pp_numbers
BOOST_WAVE_OPTION(emit_line_directives)     // support_option_emit_line_directives
BOOST_WAVE_OPTION(single_line)              // support_option_single_line
BOOST_WAVE_OPTION(convert_trigraphs)        // support_option_convert_trigraphs
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
BOOST_WAVE_OPTION(include_guard_detection)  // support_option_include_guard_detection
#endif
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
BOOST_WAVE_OPTION(variadics)                // support_option_variadics
#endif
#if BOOST_WAVE_EMIT_PRAGMA_DIRECTIVES != 0
BOOST_WAVE_OPTION(emit_pragma_directives)   // support_option_emit_pragma_directives
#endif
BOOST_WAVE_OPTION(insert_whitespace)        // support_option_insert_whitespace
BOOST_WAVE_OPTION(emit_contnewlines)

    template <typename TokenT>
    bool ccomment_has_newline(TokenT const& token)
    {
        using namespace boost::wave;

        if (T_CCOMMENT == token_id(token) &&
            TokenT::string_type::npos != token.get_value().find_first_of("\n"))
        {
            return true;
        }
        return false;
    }

    template <typename TokenT>
    int ccomment_count_newlines(TokenT const& token)
    {
        using namespace boost::wave;
        int newlines = 0;
        if (T_CCOMMENT == token_id(token)) {
        typename TokenT::string_type const& value = token.get_value();
        typename TokenT::string_type::size_type p = value.find_first_of("\n");

            while (TokenT::string_type::npos != p) {
                ++newlines;
                p = value.find_first_of("\n", p+1);
            } 
        }
        return newlines;
    }

    bool skip_cppcomment(boost::wave::token_id id)
    {
        return !preserve_comments && T_CPPCOMMENT == id;
    }


template <typename TokenT>
inline 
eat_whitespace<TokenT>::eat_whitespace()
:   state(&eat_whitespace::newline), preserve_comments(false),
    preserve_bol_whitespace(false)
{
}

template <typename ContextT>
inline bool 
eat_whitespace<TokenT>::may_skip_whitespace(ContextT const& ctx, TokenT &token, 
    bool &skipped_newline) 
{
    // re-initialize the preserve comments state
    preserve_comments = boost::wave::need_preserve_comments(ctx.get_language());
    return (this->*state)(token, skipped_newline);
}

template <typename ContextT>
inline bool 
eat_whitespace<TokenT>::may_skip_whitespace(ContextT const& ctx, TokenT &token, 
    bool preserve_comments_, bool preserve_bol_whitespace_,
    bool &skipped_newline) 
{
    // re-initialize the preserve comments state
    preserve_comments = preserve_comments_;
    preserve_bol_whitespace = preserve_bol_whitespace_;
    return (this->*state)(token, skipped_newline);
}


template <typename TokenT>
inline bool 
eat_whitespace<TokenT>::general(TokenT &token, bool &skipped_newline) 
{
    using namespace boost::wave;

    token_id id = token_id(token);
    if (T_NEWLINE == id || T_CPPCOMMENT == id) {
        state = &eat_whitespace::newline;
    }
    else if (T_SPACE == id || T_SPACE2 == id || T_CCOMMENT == id) {
        state = &eat_whitespace::whitespace;

        if (util::ccomment_has_newline(token)) 
            skipped_newline = true;

        if ((!preserve_comments || T_CCOMMENT != id) && 
            token.get_value().size() > 1)
        {
            token.set_value(" ");   // replace with a single space
        }
    }
    else {
        state = &eat_whitespace::general;
    }
    return false;
}


template <typename TokenT>
inline bool 
eat_whitespace<TokenT>::newline(TokenT &token, bool &skipped_newline) 
{
    using namespace boost::wave;

    token_id id = token_id(token);
    if (T_NEWLINE == id || T_CPPCOMMENT == id) {
        skipped_newline = true;
        state = &eat_whitespace::newline_2nd;
        return T_NEWLINE == id || skip_cppcomment(id);
    }

    if (T_SPACE != id && T_SPACE2 != id && T_CCOMMENT != id) 
        return general(token, skipped_newline);

    if (T_CCOMMENT == id) {
        if (util::ccomment_has_newline(token)) {
            skipped_newline = true;
            state = &eat_whitespace::newline_2nd;
        }
        if (preserve_comments) {
            state = &eat_whitespace::general;
            return false;
        }
        return true;
    }

    if (preserve_bol_whitespace) {
        state = &eat_whitespace::bol_whitespace;
        return false;
    }

    return true;
}


template <typename TokenT>
inline bool 
eat_whitespace<TokenT>::newline_2nd(TokenT &token, bool &skipped_newline) 
{
    using namespace boost::wave;

    token_id id = token_id(token);
    if (T_SPACE == id || T_SPACE2 == id) {
        if (preserve_bol_whitespace) {
            state = &eat_whitespace::bol_whitespace;
            return false;
        }
        return true;
    }

    if (T_CCOMMENT == id) {
        if (util::ccomment_has_newline(token))
            skipped_newline = true;

        if (preserve_comments) {
            state = &eat_whitespace::general;
            return false;
        }
        return  true;
    }

    if (T_NEWLINE != id && T_CPPCOMMENT != id) 
        return general(token, skipped_newline);

    skipped_newline = true;
    return T_NEWLINE == id || skip_cppcomment(id);
}


template <typename TokenT>
inline bool 
eat_whitespace<TokenT>::bol_whitespace(TokenT &token, bool &skipped_newline) 
{
    using namespace boost::wave;

    token_id id = token_id(token);
    if (T_SPACE == id || T_SPACE2 == id) 
        return !preserve_bol_whitespace;

    return general(token, skipped_newline);
}


template <typename TokenT>
inline bool 
eat_whitespace<TokenT>::whitespace(TokenT &token, bool &skipped_newline) 
{
    using namespace boost::wave;

    token_id id = token_id(token);
    if (T_SPACE != id && T_SPACE2 != id && 
        T_CCOMMENT != id && T_CPPCOMMENT != id) 
    {
        return general(token, skipped_newline);
    }

    if (T_CCOMMENT == id) {
        if (util::ccomment_has_newline(token))
            skipped_newline = true;
        return !preserve_comments;
    }

    return T_SPACE == id || T_SPACE2 == id || skip_cppcomment(id);
}

inline bool is_pp_token(boost::wave::token_id id)
{
    return (id & boost::wave::PPTokenFlag) ? true : false;
}


template <typename TokenT>
inline bool is_pp_token(TokenT const& tok)
{
    return is_pp_token(boost::wave::token_id(tok));
}


    inline char const *
    get_severity(int level)
    {
        static char const *severity_text[] =
        {
            "remark",               // severity_remark
            "warning",              // severity_warning
            "error",                // severity_error
            "fatal error",          // severity_fatal
            "command line error"    // severity_commandline_error
        };
        BOOST_ASSERT(severity_remark <= level &&
            level <= last_severity_code);
        return severity_text[level];
    }

    template <typename Exception, typename S1, typename Pos>
    void throw_(typename Exception::error_code code, S1 msg, Pos const& pos)
    {
        std::stringstream stream;
        stream << Exception::severity_text(code) << ": "
               << Exception::error_text(code);
        if (msg[0] != 0) 
            stream << ": " << msg;
        stream << std::ends;
        std::string throwmsg = stream.str(); 
        boost::throw_exception(Exception(throwmsg.c_str(), code,
            pos.get_line(), pos.get_column(), pos.get_file().c_str()));
    }


    template <typename Exception, typename Context, typename S1, typename Pos>
    void throw_(Context& ctx, typename Exception::error_code code, 
        S1 msg, Pos const& pos)
    {
        std::stringstream stream;
        stream << Exception::severity_text(code) << ": "
               << Exception::error_text(code);
        if (msg[0] != 0) 
            stream << ": " << msg;
        stream << std::ends;
        std::string throwmsg = stream.str(); 
        ctx.get_hooks().throw_exception(ctx.derived(), 
            Exception(throwmsg.c_str(), code, pos.get_line(), pos.get_column(), 
                pos.get_file().c_str()));
    }


    template <typename Exception, typename S1, typename Pos, typename S2>
    void throw_(typename Exception::error_code code, S1 msg, Pos const& pos, 
        S2 name)
    {
        std::stringstream stream;
        stream << Exception::severity_text(code) << ": "
               << Exception::error_text(code);
        if (msg[0] != 0) 
            stream << ": " << msg;
        stream << std::ends;
        std::string throwmsg = stream.str(); 
        boost::throw_exception(Exception(throwmsg.c_str(), code,
            pos.get_line(), pos.get_column(), pos.get_file().c_str(), name));
    }


    template <typename Exception, typename Context, typename S1, typename Pos1, 
        typename S2>
    void throw_(Context& ctx, typename Exception::error_code code, 
        S1 msg, Pos1 const& pos, S2 name)
    {
        std::stringstream stream;
        stream << Exception::severity_text(code) << ": "
               << Exception::error_text(code);
        if (msg[0] != 0) 
            stream << ": " << msg;
        stream << std::ends;
        std::string throwmsg = stream.str(); 
        ctx.get_hooks().throw_exception(ctx.derived(), 
            Exception(throwmsg.c_str(), code, pos.get_line(), pos.get_column(), 
                pos.get_file().c_str(), name));
    }

            template <typename PositionT>
            static void init_iterators(IterContextT &iter_ctx,
                PositionT const &act_pos, language_support language)
            {
                typedef typename IterContextT::iterator_type iterator_type;

                // read in the file
                std::ifstream instream(iter_ctx.filename.c_str());
                if (!instream.is_open()) {
                    BOOST_WAVE_THROW_CTX(iter_ctx.ctx, preprocess_exception,
                        bad_include_file, iter_ctx.filename.c_str(), act_pos);
                    return;
                }
                instream.unsetf(std::ios::skipws);

                iter_ctx.instring.assign(
                    std::istreambuf_iterator<char>(instream.rdbuf()),
                    std::istreambuf_iterator<char>());

                iter_ctx.first = iterator_type(
                    iter_ctx.instring.begin(), iter_ctx.instring.end(),
                    PositionT(iter_ctx.filename), language);
                iter_ctx.last = iterator_type();
            }


    base_iteration_context(ContextT& ctx_,
            BOOST_WAVE_STRINGTYPE const &fname, std::size_t if_block_depth = 0)
    :   real_filename(fname), real_relative_filename(fname), filename(fname),
        line(1), emitted_lines(0), if_block_depth(if_block_depth), ctx(ctx_),
        type(main_file)
    {}


    iteration_context(ContextT& ctx, BOOST_WAVE_STRINGTYPE const &fname,
            position_type const &act_pos,
            boost::wave::language_support language_,
            typename base_type::file_type type = base_type::main_file)
    :   base_iteration_context<ContextT, IteratorT>(ctx, fname, type)
    {
        InputPolicyT::template inner<self_type>::init_iterators(
            *this, act_pos, language_);
    }

    template <typename ContextT, typename TokenT, typename ContainerT, typename IteratorT>
    bool 
    expanding_function_like_macro(ContextT const& ctx,
        TokenT const& macrodef, std::vector<TokenT> const& formal_args, 
        ContainerT const& definition,
        TokenT const& macrocall, std::vector<ContainerT> const& arguments,
        IteratorT const& seqstart, IteratorT const& seqend) 
    { return false; }

    template <typename ContextT, typename TokenT, typename ContainerT>
    bool 
    expanding_object_like_macro(ContextT const& ctx, TokenT const& macro, 
        ContainerT const& definition, TokenT const& macrocall)
    { return false; }

    template <typename ContextT, typename ContainerT>
    void expanded_macro(ContextT const& ctx, ContainerT const& result)
    {}

    template <typename ContextT, typename ContainerT>
    void rescanned_macro(ContextT const& ctx, ContainerT const& result)
    {}

    template <typename ContextT>
    bool 
    locate_include_file(ContextT& ctx, std::string &file_path, 
        bool is_system, char const *current_name, std::string &dir_path, 
        std::string &native_name) 
    {
        if (!ctx.find_include_file (file_path, dir_path, is_system, current_name))
            return false;   // could not locate file

        namespace fs = boost::filesystem;

        fs::path native_path(wave::util::create_path(file_path));
        if (!fs::exists(native_path)) {
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_include_file, 
                file_path.c_str(), ctx.get_main_pos());
            return false;
        }

        // return the unique full file system path of the located file
        native_name = wave::util::native_file_string(native_path);

        return true;      // include file has been located successfully
    }

    template <typename ContextT>
    bool 
    found_include_directive(ContextT const& ctx, std::string const& filename, 
        bool include_next) 
    {
        return false;    // ok to include this file
    }

    template <typename ContextT>
    void 
    opened_include_file(ContextT const& ctx, std::string const& relname, 
        std::string const& absname, bool is_system_include) 
    {}

    template <typename ContextT>
    void
    returning_from_include_file(ContextT const& ctx) 
    {}

    template <typename ContextT, typename ContainerT>
    bool 
    interpret_pragma(ContextT const& ctx, ContainerT &pending, 
        typename ContextT::token_type const& option, ContainerT const& values, 
        typename ContextT::token_type const& act_token)
    {
        return false;
    }

    template <typename ContextT, typename ContainerT>
    bool 
    emit_line_directive(ContextT const& ctx, ContainerT &pending, 
        typename ContextT::token_type const& act_token)
    {
        return false;
    }

    template <
        typename ContextT, typename TokenT, typename ParametersT, 
        typename DefinitionT
    >
    void
    defined_macro(ContextT const& ctx, TokenT const& macro_name, 
        bool is_functionlike, ParametersT const& parameters, 
        DefinitionT const& definition, bool is_predefined)
    {}

    template <typename ContextT, typename TokenT>
    void
    undefined_macro(ContextT const& ctx, TokenT const& macro_name)
    {}

    template <typename ContextT, typename TokenT>
    bool
    found_directive(ContextT const& ctx, TokenT const& directive)
    { return false; }

    template <typename ContextT, typename ContainerT>
    bool
    found_unknown_directive(ContextT const& ctx, ContainerT const& line, 
        ContainerT& pending)
    { return false; }

    template <typename ContextT, typename TokenT, typename ContainerT>
    bool
    evaluated_conditional_expression(ContextT const& ctx, 
        TokenT const& directive, ContainerT const& expression, 
        bool expression_value)
    { return false; }

    template <typename ContextT, typename TokenT>
    void
    skipped_token(ContextT const& ctx, TokenT const& token)
    {}

    template <typename ContextT, typename TokenT>
    TokenT const&
    generated_token(ContextT const& ctx, TokenT const& t)
    { return t; }

    template <typename ContextT, typename TokenT>
    bool
    may_skip_whitespace(ContextT const& ctx, TokenT& token, bool& skipped_newline)
    { return false; }

    template <typename ContextT, typename ContainerT>
    bool
    found_error_directive(ContextT const& ctx, ContainerT const& message)
    { return false; }

    template <typename ContextT, typename ContainerT>
    void
    found_line_directive(ContextT const& ctx, ContainerT const& arguments,
        unsigned int line, std::string const& filename)
    {}

    template <typename ContextT, typename ExceptionT>
    void
    throw_exception(ContextT const& ctx, ExceptionT const& e)
    {
        boost::throw_exception(e);
    }


        store_found_eof(bool &found_eof_) : found_eof(found_eof_) {}

        
        template <typename TokenT>
        void operator()(TokenT const &/*token*/) const
        {
            found_eof = true;
        }


        store_found_directive(TokenT &found_directive_) 
        :   found_directive(found_directive_) {}

        
        void operator()(TokenT const &token) const
        {
            found_directive = token;
        }


        store_found_eoltokens(ContainerT &found_eoltokens_) 
        :   found_eoltokens(found_eoltokens_) {}

        
        template <typename IteratorT>
        void operator()(IteratorT const &first, IteratorT const& last) const
        {
            std::copy(first, last, 
                std::inserter(found_eoltokens, found_eoltokens.end()));
        }


        definition(cpp_grammar const &self) 
        {
        // import the spirit and cpplexer namespaces here
            using namespace boost::spirit::classic;
            using namespace boost::wave;
            using namespace boost::wave::util;

        // set the rule id's for later use
            pp_statement.set_id(BOOST_WAVE_PP_STATEMENT_ID);
//             include_file.set_id(BOOST_WAVE_INCLUDE_FILE_ID);
//             system_include_file.set_id(BOOST_WAVE_SYSINCLUDE_FILE_ID);
            macro_include_file.set_id(BOOST_WAVE_MACROINCLUDE_FILE_ID);
            plain_define.set_id(BOOST_WAVE_PLAIN_DEFINE_ID);
            macro_parameters.set_id(BOOST_WAVE_MACRO_PARAMETERS_ID);
            macro_definition.set_id(BOOST_WAVE_MACRO_DEFINITION_ID);
            undefine.set_id(BOOST_WAVE_UNDEFINE_ID);
            ppifdef.set_id(BOOST_WAVE_IFDEF_ID);
            ppifndef.set_id(BOOST_WAVE_IFNDEF_ID);
            ppif.set_id(BOOST_WAVE_IF_ID);
            ppelif.set_id(BOOST_WAVE_ELIF_ID);
//             ppelse.set_id(BOOST_WAVE_ELSE_ID);
//             ppendif.set_id(BOOST_WAVE_ENDIF_ID);
            ppline.set_id(BOOST_WAVE_LINE_ID);
            pperror.set_id(BOOST_WAVE_ERROR_ID);
            ppwarning.set_id(BOOST_WAVE_WARNING_ID);
            pppragma.set_id(BOOST_WAVE_PRAGMA_ID);
            illformed.set_id(BOOST_WAVE_ILLFORMED_ID);
            ppsp.set_id(BOOST_WAVE_PPSPACE_ID);
            ppqualifiedname.set_id(BOOST_WAVE_PPQUALIFIEDNAME_ID);
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
            ppregion.set_id(BOOST_WAVE_REGION_ID);
            ppendregion.set_id(BOOST_WAVE_ENDREGION_ID);
#endif

#if BOOST_WAVE_DUMP_PARSE_TREE != 0
            self.map_rule_id_to_name.init_rule_id_to_name_map(self);
#endif 

        // recognizes preprocessor directives only

        // C++ standard 16.1: A preprocessing directive consists of a sequence 
        // of preprocessing tokens. The first token in the sequence is # 
        // preprocessing token that is either the first character in the source 
        // file (optionally after white space containing no new-line 
        // characters) or that follows white space containing at least one 
        // new-line character. The last token in the sequence is the first 
        // new-line character that follows the first token in the sequence.

            pp_statement
                =   (   plain_define
//                     |   include_file
//                     |   system_include_file
                    |   ppif
                    |   ppelif
                    |   ppifndef
                    |   ppifdef
                    |   undefine
//                     |   ppelse
                    |   macro_include_file
                    |   ppline
                    |   pppragma
                    |   pperror
                    |   ppwarning
//                     |   ppendif
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
                    |   ppregion
                    |   ppendregion
#endif
                    |   illformed
                    )
                    >> eol_tokens
                       [ store_found_eoltokens_type(self.found_eoltokens) ]
//  In parser debug mode it is useful not to flush the underlying stream
//  to allow its investigation in the debugger and to see the correct
//  output in the printed debug log..
//  Note: this may break the parser, though.
#if !(defined(BOOST_SPIRIT_DEBUG) && \
      (BOOST_SPIRIT_DEBUG_FLAGS_CPP & BOOST_SPIRIT_DEBUG_FLAGS_CPP_GRAMMAR) \
     )
                   >>  impl::flush_underlying_parser_p
#endif // !(defined(BOOST_SPIRIT_DEBUG) &&
                ;

//         // #include ...
//             include_file            // include "..."
//                 =   ch_p(T_PP_QHEADER) 
//                     [ store_found_directive_type(self.found_directive) ]
// #if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
//                 |   ch_p(T_PP_QHEADER_NEXT)
//                     [ store_found_directive_type(self.found_directive) ]
// #endif 
//                 ;

//             system_include_file     // include <...>
//                 =   ch_p(T_PP_HHEADER) 
//                     [ store_found_directive_type(self.found_directive) ]
// #if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
//                 |   ch_p(T_PP_HHEADER_NEXT)
//                     [ store_found_directive_type(self.found_directive) ]
// #endif 
//                 ;

            macro_include_file      // include ...anything else...
                =   no_node_d
                    [
                        ch_p(T_PP_INCLUDE)
                        [ store_found_directive_type(self.found_directive) ]
#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
                    |   ch_p(T_PP_INCLUDE_NEXT)
                        [ store_found_directive_type(self.found_directive) ]
#endif
                    ]
                    >> *(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

        // #define FOO foo (with optional parameters)
            plain_define
                =   no_node_d
                    [
                        ch_p(T_PP_DEFINE) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> +ppsp
                    ]
                    >>  (   ch_p(T_IDENTIFIER) 
                        |   pattern_p(KeywordTokenType, 
                                TokenTypeMask|PPTokenFlag)
                        |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                        |   pattern_p(BoolLiteralTokenType, 
                                TokenTypeMask|PPTokenFlag)  // true/false
                        )
                    >>  (   (   no_node_d[eps_p(ch_p(T_LEFTPAREN))]
                                >>  macro_parameters
                                >> !macro_definition
                            )
                        |  !(   no_node_d[+ppsp] 
                                >>  macro_definition
                            )
                        )
                ;

        // parameter list
        // normal C++ mode
            macro_parameters
                =   confix_p(
                        no_node_d[ch_p(T_LEFTPAREN) >> *ppsp],
                       !list_p(
                            (   ch_p(T_IDENTIFIER) 
                            |   pattern_p(KeywordTokenType, 
                                    TokenTypeMask|PPTokenFlag)
                            |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                    ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                            |   pattern_p(BoolLiteralTokenType, 
                                    TokenTypeMask|PPTokenFlag)  // true/false
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
                            |   ch_p(T_ELLIPSIS)
#endif
                            ), 
                            no_node_d[*ppsp >> ch_p(T_COMMA) >> *ppsp]
                        ),
                        no_node_d[*ppsp >> ch_p(T_RIGHTPAREN)]
                    )
                ;
            
        // macro body (anything left until eol)
            macro_definition
                =   no_node_d[*ppsp]
                    >> *(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

        // #undef FOO 
            undefine
                =   no_node_d
                    [
                        ch_p(T_PP_UNDEF) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> +ppsp
                    ]
                    >>  (   ch_p(T_IDENTIFIER) 
                        |   pattern_p(KeywordTokenType, 
                                TokenTypeMask|PPTokenFlag)
                        |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                        |   pattern_p(BoolLiteralTokenType, 
                                TokenTypeMask|PPTokenFlag)  // true/false
                        )
                ;

        // #ifdef et.al.
            ppifdef
                =   no_node_d
                    [
                        ch_p(T_PP_IFDEF) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> +ppsp
                    ]
                    >>  ppqualifiedname
                ;

            ppifndef
                =   no_node_d
                    [
                        ch_p(T_PP_IFNDEF) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> +ppsp
                    ]
                    >>  ppqualifiedname
                ;

            ppif
                =   no_node_d
                    [
                        ch_p(T_PP_IF) 
                        [ store_found_directive_type(self.found_directive) ]
//                        >> *ppsp
                    ]
                    >> +(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

//             ppelse
//                 =   no_node_d
//                     [
//                         ch_p(T_PP_ELSE)
//                         [ store_found_directive_type(self.found_directive) ]
//                     ]
//                 ;

            ppelif
                =   no_node_d
                    [
                        ch_p(T_PP_ELIF) 
                        [ store_found_directive_type(self.found_directive) ]
//                        >> *ppsp
                    ]
                    >> +(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

//             ppendif
//                 =   no_node_d
//                     [
//                         ch_p(T_PP_ENDIF)
//                         [ store_found_directive_type(self.found_directive) ]
//                     ]
//                 ;

        // #line ...
            ppline 
                =   no_node_d
                    [
                        ch_p(T_PP_LINE) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> *ppsp
                    ]
                    >> +(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;
                
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
        // #region ...
            ppregion
                =   no_node_d
                    [
                        ch_p(T_MSEXT_PP_REGION) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> +ppsp
                    ]
                    >>  ppqualifiedname
                ;

        // #endregion
            ppendregion
                =   no_node_d
                    [
                        ch_p(T_MSEXT_PP_ENDREGION) 
                        [ store_found_directive_type(self.found_directive) ]
                    ]
                ;
#endif

        // # something else (ill formed preprocessor directive)
            illformed           // for error reporting
                =   no_node_d
                    [
                        pattern_p(T_POUND, MainTokenMask) 
                        >> *ppsp
                    ]
                    >>  (   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                    >>  no_node_d
                        [
                           *(   anychar_p -
                                (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                            )
                        ]
                ;

        // #error
            pperror
                =   no_node_d
                    [
                        ch_p(T_PP_ERROR) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> *ppsp
                    ]
                    >> *(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

        // #warning
            ppwarning
                =   no_node_d
                    [
                        ch_p(T_PP_WARNING) 
                        [ store_found_directive_type(self.found_directive) ]
                        >> *ppsp
                    ]
                    >> *(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

        // #pragma ...
            pppragma
                =   no_node_d
                    [
                        ch_p(T_PP_PRAGMA)
                        [ store_found_directive_type(self.found_directive) ]
                    ] 
                    >> *(   anychar_p -
                            (ch_p(T_NEWLINE) | ch_p(T_CPPCOMMENT) | ch_p(T_EOF)) 
                        )
                ;

            ppqualifiedname
                =   no_node_d[*ppsp]
                    >>  (   ch_p(T_IDENTIFIER) 
                        |   pattern_p(KeywordTokenType, 
                                TokenTypeMask|PPTokenFlag)
                        |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                        |   pattern_p(BoolLiteralTokenType, 
                                TokenTypeMask|PPTokenFlag)  // true/false
                        ) 
                ;

        // auxiliary helper rules
            ppsp     // valid space in a line with a preprocessor directive
                =   ch_p(T_SPACE) | ch_p(T_CCOMMENT)
                ;

        // end of line tokens
            eol_tokens 
                =   no_node_d
                    [
                       *(   ch_p(T_SPACE) 
                        |   ch_p(T_CCOMMENT)
                        )
                    >>  (   ch_p(T_NEWLINE)
                        |   ch_p(T_CPPCOMMENT)
                        |   ch_p(T_EOF)
                            [ store_found_eof_type(self.found_eof) ]
                        )
                    ]
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(pp_statement, TRACE_CPP_GRAMMAR);
//             BOOST_SPIRIT_DEBUG_TRACE_RULE(include_file, TRACE_CPP_GRAMMAR);
//             BOOST_SPIRIT_DEBUG_TRACE_RULE(system_include_file, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(macro_include_file, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(plain_define, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(macro_definition, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(macro_parameters, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(undefine, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppifdef, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppifndef, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppif, TRACE_CPP_GRAMMAR);
//             BOOST_SPIRIT_DEBUG_TRACE_RULE(ppelse, TRACE_CPP_GRAMMAR);
//             BOOST_SPIRIT_DEBUG_TRACE_RULE(ppelif, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppendif, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppline, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(pperror, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppwarning, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(illformed, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppsp, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppqualifiedname, TRACE_CPP_GRAMMAR);
#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppregion, TRACE_CPP_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(ppendregion, TRACE_CPP_GRAMMAR);
#endif
        }

    
    cpp_grammar(bool &found_eof_, TokenT &found_directive_, 
            ContainerT &found_eoltokens_)
    :   found_eof(found_eof_), 
        found_directive(found_directive_),
        found_eoltokens(found_eoltokens_)
    { 
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "cpp_grammar", 
            TRACE_CPP_GRAMMAR); 
    }

    intlit_grammar(bool &is_unsigned_) : is_unsigned(is_unsigned_)
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "intlit_grammar", 
            TRACE_INTLIT_GRAMMAR);
    }


        definition(intlit_grammar const &self)
        {
            using namespace boost::spirit::classic;
            namespace phx = phoenix;
 
            
            int_lit = (
                    sub_int_lit = 
                        (   ch_p('0')[self.val = 0] >> (hex_lit | oct_lit)
                        |   dec_lit
                        )
                        >> !as_lower_d[
                                (ch_p('u')[phx::var(self.is_unsigned) = true] || ch_p('l')) 
                            |   (ch_p('l') || ch_p('u')[phx::var(self.is_unsigned) = true])
                            ]
                    ,

                    hex_lit =
                            (ch_p('X') | ch_p('x'))
                        >>  uint_parser<uint_literal_type, 16>()
                            [
                                self.val = phx::arg1,
                                phx::var(self.is_unsigned) = true
                            ]
                    ,
                        
                    oct_lit =
                       !uint_parser<uint_literal_type, 8>()
                        [
                            self.val = phx::arg1,
                            phx::var(self.is_unsigned) = true
                        ]
                    ,
                        
                    dec_lit =
                        uint_parser<uint_literal_type, 10>()
                        [
                            self.val = phx::arg1
                        ]
                    )
                ;
                
            BOOST_SPIRIT_DEBUG_TRACE_RULE(int_lit, TRACE_INTLIT_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(sub_int_lit, TRACE_INTLIT_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(hex_lit, TRACE_INTLIT_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(oct_lit, TRACE_INTLIT_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(dec_lit, TRACE_INTLIT_GRAMMAR);
        }


        definition(predefined_macros_grammar const &/*self*/) 
        {
        // import the spirit and cpplexer namespaces here
            using namespace boost::spirit::classic;
            using namespace boost::wave;
            using namespace boost::wave::util;
            
        // set the rule id's for later use
            plain_define.set_id(BOOST_WAVE_PLAIN_DEFINE_ID);
            macro_parameters.set_id(BOOST_WAVE_MACRO_PARAMETERS_ID);
            macro_definition.set_id(BOOST_WAVE_MACRO_DEFINITION_ID);

        // recognizes command line defined macro syntax, i.e.
        //  -DMACRO
        //  -DMACRO=
        //  -DMACRO=value
        //  -DMACRO(x)
        //  -DMACRO(x)=
        //  -DMACRO(x)=value

        // This grammar resembles the overall structure of the cpp_grammar to
        // make it possible to reuse the parse tree traversal code
            plain_define
                =   (   ch_p(T_IDENTIFIER)
                    |   pattern_p(KeywordTokenType, 
                            TokenTypeMask|PPTokenFlag)
                    |   pattern_p(OperatorTokenType|AltExtTokenType, 
                            ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                    |   pattern_p(BoolLiteralTokenType, 
                            TokenTypeMask|PPTokenFlag)  // true/false
                    )
                    >>  !macro_parameters
                    >>  !macro_definition
                ;

        // parameter list
            macro_parameters
                =   confix_p(
                        no_node_d[ch_p(T_LEFTPAREN) >> *ch_p(T_SPACE)],
                       !list_p(
                            (   ch_p(T_IDENTIFIER)
                            |   pattern_p(KeywordTokenType, 
                                    TokenTypeMask|PPTokenFlag)
                            |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                    ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                            |   pattern_p(BoolLiteralTokenType, 
                                    TokenTypeMask|PPTokenFlag)  // true/false
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
                            |   ch_p(T_ELLIPSIS)
#endif
                            ), 
                            no_node_d
                            [
                                *ch_p(T_SPACE) >> ch_p(T_COMMA) >> *ch_p(T_SPACE)
                            ]
                        ),
                        no_node_d[*ch_p(T_SPACE) >> ch_p(T_RIGHTPAREN)]
                    )
                ;

        // macro body (anything left until eol)
            macro_definition
                =   no_node_d[ch_p(T_ASSIGN)]
                    >> *anychar_p
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(plain_define, TRACE_PREDEF_MACROS_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(macro_definition, TRACE_PREDEF_MACROS_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(macro_parameters, TRACE_PREDEF_MACROS_GRAMMAR);
        }


    predefined_macros_grammar() 
    { 
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, 
            "predefined_macros_grammar", TRACE_PREDEF_MACROS_GRAMMAR); 
    }


        void 
        operator()(boost::uint32_t& value, bool long_lit, bool& overflow,
            boost::uint32_t character) const
        { 
            // The following assumes that wchar_t is max. 32 Bit
            BOOST_STATIC_ASSERT(sizeof(wchar_t) <= 4);
            
            static boost::uint32_t masks[] = { 
                0x000000ff, 0x0000ffff, 0x00ffffff, 0xffffffff
            };
            static boost::uint32_t overflow_masks[] = { 
                0xff000000, 0xffff0000, 0xffffff00, 0xffffffff
            };
            
            if (long_lit) {
            // make sure no overflow will occur below
                if ((value & overflow_masks[sizeof(wchar_t)-1]) != 0) {
                    overflow |= true;
                }
                else {
                // calculate the new value (avoiding a warning regarding 
                // shifting count >= size of the type)
                    value <<= CHAR_BIT * (sizeof(wchar_t)-1);
                    value <<= CHAR_BIT;  
                    value |= character & masks[sizeof(wchar_t)-1];
                }
            }
            else {
            // make sure no overflow will occur below
                if ((value & overflow_masks[sizeof(char)-1]) != 0) {
                    overflow |= true;
                }
                else {
                // calculate the new value
                    value <<= CHAR_BIT * sizeof(char);
                    value |= character & masks[sizeof(char)-1];
                }
            }
        }

    chlit_grammar()
    :   overflow(false)
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "chlit_grammar", 
            TRACE_CHLIT_GRAMMAR);
    }


        definition(chlit_grammar const &self)
        {
            using namespace boost::spirit::classic;
            namespace phx = phoenix;
            
            // special parsers for '\x..' and L'\x....'
            typedef uint_parser<
                        unsigned int, 16, 1, 2 * sizeof(char)
                    > hex_char_parser_type;
            typedef uint_parser<
                        unsigned int, 16, 1, 2 * sizeof(wchar_t)
                    > hex_wchar_parser_type;

            // the rule for a character literal
            ch_lit
                =   eps_p[self.value = phx::val(0), self.long_lit = phx::val(false)]
                    >> !ch_p('L')[self.long_lit = phx::val(true)]
                    >>  ch_p('\'')
                    >> +(   (
                            ch_p('\\') 
                            >>  (   ch_p('a')    // BEL
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x07))
                                    ]
                                |   ch_p('b')    // BS
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x08))
                                    ]
                                |   ch_p('t')    // HT
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x09))
                                    ]
                                |   ch_p('n')    // NL
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x0a))
                                    ]
                                |   ch_p('v')    // VT
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x0b))
                                    ]
                                |   ch_p('f')    // FF
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x0c))
                                    ]
                                |   ch_p('r')    // CR
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val(0x0d))
                                    ]
                                |   ch_p('?')
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val('?'))
                                    ]
                                |   ch_p('\'')
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val('\''))
                                    ]
                                |   ch_p('\"')
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val('\"'))
                                    ]
                                |   ch_p('\\')
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::val('\\'))
                                    ]
                                |   ch_p('x') 
                                    >>  if_p(self.long_lit) 
                                        [
                                            hex_wchar_parser_type()
                                            [
                                                impl::compose(self.value, self.long_lit, 
                                                    phx::var(self.overflow), phx::arg1)
                                            ]
                                        ]
                                        .else_p
                                        [
                                            hex_char_parser_type()
                                            [
                                                impl::compose(self.value, self.long_lit, 
                                                    phx::var(self.overflow), phx::arg1)
                                            ]
                                        ]
                                |   ch_p('u') 
                                    >>  uint_parser<unsigned int, 16, 4, 4>()
                                        [
                                            impl::compose(self.value, self.long_lit, 
                                                phx::var(self.overflow), phx::arg1)
                                        ]
                                |   ch_p('U')
                                    >>  uint_parser<unsigned int, 16, 8, 8>()
                                        [
                                            impl::compose(self.value, self.long_lit, 
                                                phx::var(self.overflow), phx::arg1)
                                        ]
                                |   uint_parser<unsigned int, 8, 1, 3>()
                                    [
                                        impl::compose(self.value, self.long_lit, 
                                            phx::var(self.overflow), phx::arg1)
                                    ]
                                )
                            )
                        |   ~eps_p(ch_p('\'')) >> anychar_p
                            [
                                impl::compose(self.value, self.long_lit, 
                                    phx::var(self.overflow), phx::arg1)
                            ]
                        )
                    >>  ch_p('\'')
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(ch_lit, TRACE_CHLIT_GRAMMAR);
        }

    defined_grammar(ContainerT &result_seq_)
    :   result_seq(result_seq_)
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "defined_grammar", 
            TRACE_CPP_DEFINED_GRAMMAR);
    }


        definition(defined_grammar const &self)
        {
            using namespace boost::spirit::classic;
            using namespace boost::wave;
            using namespace boost::wave::util;

            defined_op      // parens not required, see C++ standard 16.1.1
                =   ch_p(T_IDENTIFIER)      // token contains 'defined'
                    >>  (
                            (   ch_p(T_LEFTPAREN)
                                >>  identifier
                                >>  ch_p(T_RIGHTPAREN)
                            )
                            |   identifier
                        )
                ;

            identifier
                =   ch_p(T_IDENTIFIER)
                    [
                        spirit_append_actor(self.result_seq)
                    ] 
                |   pattern_p(KeywordTokenType, TokenTypeMask|PPTokenFlag)
                    [
                        spirit_append_actor(self.result_seq)
                    ] 
                |   pattern_p(OperatorTokenType|AltExtTokenType, 
                        ExtTokenTypeMask|PPTokenFlag)
                    [
                        spirit_append_actor(self.result_seq)
                    ] 
                |   pattern_p(BoolLiteralTokenType, TokenTypeMask|PPTokenFlag)
                    [
                        spirit_append_actor(self.result_seq)
                    ] 
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(defined_op, TRACE_CPP_DEFINED_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(identifier, TRACE_CPP_DEFINED_GRAMMAR);
        }


        template <typename TokenT>
        boost::wave::grammars::closures::closure_value 
        operator()(TokenT const &token) const
        { 
            typedef boost::wave::grammars::closures::closure_value return_type;
            bool is_unsigned = false;
            uint_literal_type ul = intlit_grammar_gen<TokenT>::evaluate(token, 
                is_unsigned);

            return is_unsigned ? 
                return_type(ul) : return_type(static_cast<int_literal_type>(ul));
        }


        template <typename TokenT>
        boost::wave::grammars::closures::closure_value 
        operator()(TokenT const &token) const
        { 
            typedef boost::wave::grammars::closures::closure_value return_type;
            value_error status = error_noerror;

            //  If the literal is a wchar_t and wchar_t is represented by a 
            //  signed integral type, then the created value will be signed as 
            //  well, otherwise we assume unsigned values.
#if BOOST_WAVE_WCHAR_T_SIGNEDNESS == BOOST_WAVE_WCHAR_T_AUTOSELECT
            if ('L' == token.get_value()[0] && std::numeric_limits<wchar_t>::is_signed) 
            {
                int value = chlit_grammar_gen<int, TokenT>::evaluate(token, status);
                return return_type(value, status);
            }
#elif BOOST_WAVE_WCHAR_T_SIGNEDNESS == BOOST_WAVE_WCHAR_T_FORCE_SIGNED
            if ('L' == token.get_value()[0]) 
            {
                int value = chlit_grammar_gen<int, TokenT>::evaluate(token, status);
                return return_type(value, status);
            }
#endif

            unsigned int value = chlit_grammar_gen<unsigned int, TokenT>::evaluate(token, status);
            return return_type(value, status);
        }


        template <typename CondT, typename Arg1T, typename Arg2T>
        boost::wave::grammars::closures::closure_value 
        operator()(CondT const &cond, Arg1T &val1, Arg2T const &val2) const
        { 
            return val1.handle_questionmark(cond, val2);
        }


        template <typename ArgT>
        boost::wave::grammars::closures::closure_value 
        operator()(ArgT &val) const
        { 
            typedef boost::wave::grammars::closures::closure_value return_type;
            return return_type(
                boost::wave::grammars::closures::as_bool(val), val.is_valid());
        }


        template <typename ArgT>
        bool
        operator()(ArgT &val) const
        { 
            return boost::wave::grammars::closures::as_bool(val);
        }
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
    BOOST_WAVE_BINARYOP(less, <);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
    BOOST_WAVE_BINARYOP(less, <);
    BOOST_WAVE_BINARYOP(greater, >);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
    BOOST_WAVE_BINARYOP(less, <);
    BOOST_WAVE_BINARYOP(greater, >);
    BOOST_WAVE_BINARYOP(greateq, >=);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
    BOOST_WAVE_BINARYOP(less, <);
    BOOST_WAVE_BINARYOP(greater, >);
    BOOST_WAVE_BINARYOP(greateq, >=);
    BOOST_WAVE_BINARYOP(eq, ==);
                                                                    \
                                                                              \
        template <typename Arg1T, typename Arg2T>                             \
        boost::wave::grammars::closures::closure_value                        \
        operator()(Arg1T &val1, Arg2T &val2) const                            \
        {                                                                     \
            return val1 optok val2;                                           \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_binary_ ## op> const binary_ ## op             \
    /**/

    BOOST_WAVE_BINARYOP(and, &&);
    BOOST_WAVE_BINARYOP(or, ||);
    
    BOOST_WAVE_BINARYOP(bitand, &);
    BOOST_WAVE_BINARYOP(bitor, |);
    BOOST_WAVE_BINARYOP(bitxor, ^);
    
    BOOST_WAVE_BINARYOP(lesseq, <=);
    BOOST_WAVE_BINARYOP(less, <);
    BOOST_WAVE_BINARYOP(greater, >);
    BOOST_WAVE_BINARYOP(greateq, >=);
    BOOST_WAVE_BINARYOP(eq, ==);
    BOOST_WAVE_BINARYOP(ne, !=);
                                                                    \
                                                                              \
        template <typename ArgT>                                              \
        boost::wave::grammars::closures::closure_value                        \
        operator()(ArgT &val) const                                           \
        {                                                                     \
            return optok val;                                                 \
        }                                                                     \
    };                                                                        \
    phoenix::function<operator_unary_ ## op> const unary_ ## op               \
    /**/

    BOOST_WAVE_UNARYOP(neg, !);

    expression_grammar()
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "expression_grammar", 
            TRACE_CPP_EXPR_GRAMMAR);
    }


        definition(expression_grammar const &self)
        {
            using namespace boost::spirit::classic;
            using namespace phoenix;
            using namespace boost::wave;
            using boost::wave::util::pattern_p;
            
            pp_expression
                =   const_exp[self.val = arg1]
                ;
                
            const_exp
                =   logical_or_exp[const_exp.val = arg1]
                    >> !(const_exp_subrule =
                            ch_p(T_QUESTION_MARK)
                            >>  const_exp
                                [
                                    const_exp_subrule.val = arg1
                                ] 
                            >>  ch_p(T_COLON)
                            >>  const_exp
                                [
                                    const_exp_subrule.val = 
                                        impl::questionmark(const_exp.val, 
                                            const_exp_subrule.val, arg1)
                                ]
                        )[const_exp.val = arg1]
                ;

            logical_or_exp 
                =   logical_and_exp[logical_or_exp.val = arg1]
                    >> *(   if_p(impl::as_bool(logical_or_exp.val))
                            [
                                // if one of the || operators is true, no more
                                // evaluation is required
                                pattern_p(T_OROR, MainTokenMask)
                                >>  logical_and_exp_nocalc
                                    [
                                        logical_or_exp.val = 
                                            impl::to_bool(logical_or_exp.val)
                                    ]
                            ]
                            .else_p
                            [
                                pattern_p(T_OROR, MainTokenMask)
                                >>  logical_and_exp
                                    [
                                        logical_or_exp.val = 
                                            impl::binary_or(logical_or_exp.val, arg1)
                                    ]
                            ]
                        )
                ;

            logical_and_exp
                =   inclusive_or_exp[logical_and_exp.val = arg1]
                    >> *(   if_p(impl::as_bool(logical_and_exp.val))
                            [
                                pattern_p(T_ANDAND, MainTokenMask)
                                >>  inclusive_or_exp
                                    [
                                        logical_and_exp.val = 
                                            impl::binary_and(logical_and_exp.val, arg1)
                                    ]
                            ]
                            .else_p
                            [
                                // if one of the && operators is false, no more
                                // evaluation is required
                                pattern_p(T_ANDAND, MainTokenMask)
                                >>  inclusive_or_exp_nocalc
                                    [
                                        logical_and_exp.val =
                                            impl::to_bool(logical_and_exp.val)
                                    ]
                            ]
                        )
                ;

            inclusive_or_exp
                =   exclusive_or_exp[inclusive_or_exp.val = arg1]
                    >> *(   pattern_p(T_OR, MainTokenMask)
                            >>  exclusive_or_exp
                                [
                                    inclusive_or_exp.val = 
                                        impl::binary_bitor(inclusive_or_exp.val, arg1)
                                ]
                        )
                ;

            exclusive_or_exp
                =   and_exp[exclusive_or_exp.val = arg1]
                    >> *(   pattern_p(T_XOR, MainTokenMask)
                            >>  and_exp
                                [
                                    exclusive_or_exp.val = 
                                        impl::binary_bitxor(exclusive_or_exp.val, arg1)
                                ]
                        )
                ;

            and_exp
                =   cmp_equality[and_exp.val = arg1]
                    >> *(   pattern_p(T_AND, MainTokenMask)
                            >>  cmp_equality
                                [
                                    and_exp.val = 
                                        impl::binary_bitand(and_exp.val, arg1)
                                ]
                        )
                ;

            cmp_equality
                =   cmp_relational[cmp_equality.val = arg1]
                    >> *(   ch_p(T_EQUAL)
                            >>  cmp_relational
                                [
                                    cmp_equality.val = 
                                        impl::binary_eq(cmp_equality.val, arg1)
                                ]
                        |   pattern_p(T_NOTEQUAL, MainTokenMask)
                            >>  cmp_relational
                                [
                                    cmp_equality.val = 
                                        impl::binary_ne(cmp_equality.val, arg1)
                                ]
                        )
                ;

            cmp_relational
                =   shift_exp[cmp_relational.val = arg1]
                    >> *(   ch_p(T_LESSEQUAL)
                            >>  shift_exp
                                [
                                    cmp_relational.val = 
                                        impl::binary_lesseq(cmp_relational.val, arg1)
                                ]
                        |   ch_p(T_GREATEREQUAL)
                            >>  shift_exp
                                [
                                    cmp_relational.val = 
                                        impl::binary_greateq(cmp_relational.val, arg1)
                                ]
                        |   ch_p(T_LESS)
                            >>  shift_exp
                                [
                                    cmp_relational.val = 
                                        impl::binary_less(cmp_relational.val, arg1)
                                ]
                        |   ch_p(T_GREATER)
                            >>  shift_exp
                                [
                                    cmp_relational.val = 
                                        impl::binary_greater(cmp_relational.val, arg1)
                                ]
                        )
                ;

            shift_exp
                =   add_exp[shift_exp.val = arg1]
                    >> *(   ch_p(T_SHIFTLEFT)
                            >>  add_exp
                                [
                                    shift_exp.val <<= arg1
                                ]
                        |   ch_p(T_SHIFTRIGHT)
                            >>  add_exp
                                [
                                    shift_exp.val >>= arg1
                                ]
                        )
                ;

            add_exp
                =   multiply_exp[add_exp.val = arg1]
                    >> *(   ch_p(T_PLUS)
                            >>  multiply_exp
                                [
                                    add_exp.val += arg1
                                ]
                        |   ch_p(T_MINUS)
                            >>  multiply_exp
                                [
                                    add_exp.val -= arg1
                                ]
                        )
                ;

            multiply_exp
                =   unary_exp[multiply_exp.val = arg1]
                    >> *(   ch_p(T_STAR)
                            >>  unary_exp
                                [
                                    multiply_exp.val *= arg1
                                ]
                        |   ch_p(T_DIVIDE)
                            >>  unary_exp
                                [
                                    multiply_exp.val /= arg1
                                ]
                        |   ch_p(T_PERCENT)
                            >>  unary_exp
                                [
                                    multiply_exp.val %= arg1
                                ]
                        )
                ;

            unary_exp
                =   primary_exp[unary_exp.val = arg1]
                |   ch_p(T_PLUS) >> unary_exp
                    [
                        unary_exp.val = arg1
                    ]
                |   ch_p(T_MINUS) >> unary_exp
                    [
                        unary_exp.val = -arg1
                    ]
                |   pattern_p(T_COMPL, MainTokenMask) >> unary_exp
                    [
                        unary_exp.val = ~arg1
                    ]
                |   pattern_p(T_NOT, MainTokenMask) >> unary_exp
                    [
                        unary_exp.val = impl::unary_neg(arg1)
                    ]
                ;

            primary_exp
                =   constant[primary_exp.val = arg1]
                |   ch_p(T_LEFTPAREN) 
                    >> const_exp[primary_exp.val = arg1]
                    >> ch_p(T_RIGHTPAREN)
                ;

            constant
                =   ch_p(T_PP_NUMBER) 
                    [
                        constant.val = impl::as_intlit(arg1)
                    ]
                |   ch_p(T_INTLIT) 
                    [
                        constant.val = impl::as_intlit(arg1)
                    ]
                |   ch_p(T_CHARLIT) 
                    [
                        constant.val = impl::as_chlit(arg1)
                    ]
                ;
              
            //  here follows the same grammar, but without any embedded 
            //  calculations
            const_exp_nocalc
                =   logical_or_exp_nocalc
                    >> !(   ch_p(T_QUESTION_MARK)
                            >>  const_exp_nocalc
                            >>  ch_p(T_COLON)
                            >>  const_exp_nocalc
                        )
                ;

            logical_or_exp_nocalc 
                =   logical_and_exp_nocalc
                    >> *(   pattern_p(T_OROR, MainTokenMask)
                            >>  logical_and_exp_nocalc
                        )
                ;

            logical_and_exp_nocalc
                =   inclusive_or_exp_nocalc
                    >> *(   pattern_p(T_ANDAND, MainTokenMask)
                            >>  inclusive_or_exp_nocalc
                        )
                ;

            inclusive_or_exp_nocalc
                =   exclusive_or_exp_nocalc
                    >> *(   pattern_p(T_OR, MainTokenMask)
                            >>  exclusive_or_exp_nocalc
                        )
                ;

            exclusive_or_exp_nocalc
                =   and_exp_nocalc
                    >> *(   pattern_p(T_XOR, MainTokenMask)
                            >>  and_exp_nocalc
                        )
                ;

            and_exp_nocalc
                =   cmp_equality_nocalc
                    >> *(   pattern_p(T_AND, MainTokenMask)
                            >>  cmp_equality_nocalc
                        )
                ;

            cmp_equality_nocalc
                =   cmp_relational_nocalc
                    >> *(   ch_p(T_EQUAL)
                            >>  cmp_relational_nocalc
                        |   pattern_p(T_NOTEQUAL, MainTokenMask)
                            >>  cmp_relational_nocalc
                        )
                ;

            cmp_relational_nocalc
                =   shift_exp_nocalc
                    >> *(   ch_p(T_LESSEQUAL)
                            >>  shift_exp_nocalc
                        |   ch_p(T_GREATEREQUAL)
                            >>  shift_exp_nocalc
                        |   ch_p(T_LESS)
                            >>  shift_exp_nocalc
                        |   ch_p(T_GREATER)
                            >>  shift_exp_nocalc
                        )
                ;

            shift_exp_nocalc
                =   add_exp_nocalc
                    >> *(   ch_p(T_SHIFTLEFT)
                            >>  add_exp_nocalc
                        |   ch_p(T_SHIFTRIGHT)
                            >>  add_exp_nocalc
                        )
                ;

            add_exp_nocalc
                =   multiply_exp_nocalc
                    >> *(   ch_p(T_PLUS)
                            >>  multiply_exp_nocalc
                        |   ch_p(T_MINUS)
                            >>  multiply_exp_nocalc
                        )
                ;

            multiply_exp_nocalc
                =   unary_exp_nocalc
                    >> *(   ch_p(T_STAR)
                            >>  unary_exp_nocalc
                        |   ch_p(T_DIVIDE)
                            >>  unary_exp_nocalc
                        |   ch_p(T_PERCENT)
                            >>  unary_exp_nocalc
                        )
                ;

            unary_exp_nocalc
                =   primary_exp_nocalc
                |   ch_p(T_PLUS) >> unary_exp_nocalc
                |   ch_p(T_MINUS) >> unary_exp_nocalc
                |   pattern_p(T_COMPL, MainTokenMask) >> unary_exp_nocalc
                |   pattern_p(T_NOT, MainTokenMask) >> unary_exp_nocalc
                ;

            primary_exp_nocalc
                =   constant_nocalc
                |   ch_p(T_LEFTPAREN) 
                    >> const_exp_nocalc
                    >> ch_p(T_RIGHTPAREN)
                ;

            constant_nocalc
                =   ch_p(T_PP_NUMBER) 
                |   ch_p(T_INTLIT) 
                |   ch_p(T_CHARLIT) 
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(pp_expression, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(const_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(logical_or_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(logical_and_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(inclusive_or_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(exclusive_or_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(and_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(cmp_equality, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(cmp_relational, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(shift_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(add_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(multiply_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(unary_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(primary_exp, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(constant, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(const_exp_subrule, TRACE_CPP_EXPR_GRAMMAR);

            BOOST_SPIRIT_DEBUG_TRACE_RULE(const_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(logical_or_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(logical_and_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(inclusive_or_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(exclusive_or_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(and_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(cmp_equality_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(cmp_relational_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(shift_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(add_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(multiply_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(unary_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(primary_exp_nocalc, TRACE_CPP_EXPR_GRAMMAR);
            BOOST_SPIRIT_DEBUG_TRACE_RULE(constant_nocalc, TRACE_CPP_EXPR_GRAMMAR);
        }

    
    closure_value(value_error valid_ = error_noerror) 
    : type(is_int), valid(valid_) 
    { value.i = 0; }


    value_type get_type() const { return type; }

    value_error is_valid() const { return valid; }

    closure_value &operator= (closure_value const &rhs)
    {
        switch (rhs.get_type()) {
        case is_int:    
            value.i = as_long(rhs); 
            type = is_int;
            break;
        
        case is_uint:   
            value.ui = as_ulong(rhs); 
            type = is_uint;
            break;
        
        case is_bool:   
            value.b = as_bool(rhs);
            type = is_bool;
            break;
        }
        valid = rhs.valid;
        return *this;
    }

    closure_value &operator= (int rhs)
    {
        type = is_int;
        value.i = rhs;
        valid = error_noerror;
        return *this;
    }

    closure_value &operator= (unsigned int rhs)
    {
        type = is_uint;
        value.ui = rhs;
        valid = error_noerror;
        return *this;
    }

    closure_value &operator= (bool rhs)
    {
        type = is_bool;
        value.b = rhs;
        valid = error_noerror;
        return *this;
    }

    closure_value &operator+= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:
                {
                    int_literal_type result = value.i + as_long(rhs); 
                    if ((rhs.value.i > 0L && value.i > result) || 
                        (rhs.value.i < 0L && value.i < result))
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i = result;
                    }
                }
                break;
                
            case is_int:
                {
                    int_literal_type result = value.i + rhs.value.i;
                    if ((rhs.value.i > 0L && value.i > result) || 
                        (rhs.value.i < 0L && value.i < result))
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i = result;
                    }
                }
                break;
                
            case is_uint:
                {
                    uint_literal_type result = value.ui + rhs.value.ui; 
                    if (result < value.ui) {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                        type = is_uint; 
                    }
                }
                break;
            }
            break;
            
        case is_uint:
            {
                uint_literal_type result = value.ui + as_ulong(rhs); 
                if (result < value.ui) {
                    valid = error_integer_overflow;
                }
                else {
                    value.ui = result;
                }
            }
            break;
            
        case is_bool:   
            value.i = value.b + as_bool(rhs);
            type = is_int;
        }
        valid = (value_error)(valid | rhs.valid);
        return *this;
    }

    closure_value &operator-= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:
            switch(rhs.type) {
            case is_bool:
                {
                    int_literal_type result = value.i - as_long(rhs); 
                    if ((rhs.value.i > 0L && result > value.i) || 
                        (rhs.value.i < 0L && result < value.i))
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i = result;
                    }
                }
                break;

            case is_int:
                {
                    int_literal_type result = value.i - rhs.value.i;
                    if ((rhs.value.i > 0L && result > value.i) || 
                        (rhs.value.i < 0L && result < value.i))
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i = result;
                    }
                }
                break;
                
            case is_uint:
                {
                    uint_literal_type result = value.ui - rhs.value.ui; 
                    if (result > value.ui) {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                        type = is_uint; 
                    }
                }
                break;
            }
            break;
            
        case is_uint:
            switch(rhs.type) {
            case is_bool:
                {
                    uint_literal_type result = value.ui - as_ulong(rhs); 
                    if (result > value.ui)
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                    }
                }
                break;

            case is_int:
                {
                    uint_literal_type result = value.ui - rhs.value.i;
                    if ((rhs.value.i > 0L && result > value.ui) || 
                        (rhs.value.i < 0L && result < value.ui))
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                    }
                }
                break;
                
            case is_uint:
                {
                    uint_literal_type result = value.ui - rhs.value.ui; 
                    if (result > value.ui) {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                    }
                }
                break;
            }
            break;

        case is_bool:   
            value.i = value.b - as_bool(rhs);
            type = is_int;
        }
        valid = (value_error)(valid | rhs.valid);
        return *this;
    }

    closure_value &operator*= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:   value.i *= as_long(rhs); break;
            case is_int:
                {
                    int_literal_type result = value.i * rhs.value.i; 
                    if (0 != value.i && 0 != rhs.value.i &&
                        (result / value.i != rhs.value.i ||
                         result / rhs.value.i != value.i)
                       )
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i = result;
                    }
                }
                break;
                
            case is_uint:
                {
                    uint_literal_type result = value.ui * rhs.value.ui; 
                    if (0 != value.ui && 0 != rhs.value.ui &&
                        (result / value.ui != rhs.value.ui ||
                         result / rhs.value.ui != value.ui)
                       )
                    {
                        valid = error_integer_overflow;
                    }
                    else {
                        value.ui = result;
                        type = is_uint; 
                    }
                }
                break;
            }
            break;
            
        case is_uint:
            {
                uint_literal_type rhs_val = as_ulong(rhs);
                uint_literal_type result = value.ui * rhs_val; 
                if (0 != value.ui && 0 != rhs_val &&
                    (result / value.ui != rhs_val ||
                      result / rhs_val != value.ui)
                    )
                {
                    valid = error_integer_overflow;
                }
                else {
                    value.ui = result;
                    type = is_uint; 
                }
            }
            break;
            
        case is_bool:
            switch (rhs.type) {
            case is_int:
                value.i = (value.b ? 1 : 0) * rhs.value.i; 
                type = is_int; 
                break;
                
            case is_uint:
                value.ui = (value.b ? 1 : 0) * rhs.value.ui; 
                type = is_uint; 
                break;
                
            case is_bool:
                value.b = 0 != ((value.b ? 1 : 0) * (rhs.value.b ? 1 : 0));
                break;
            }
        }
        valid = (value_error)(valid | rhs.valid);
        return *this;
    }

    closure_value &operator/= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:   
            case is_int:
                if (as_long(rhs) != 0) {
                    if (value.i == -value.i && -1 == rhs.value.i) {
                    // LONG_MIN / -1 on two's complement
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i /= as_long(rhs); 
                    }
                }
                else {
                    valid = error_division_by_zero;   // division by zero
                }
                break;
                
            case is_uint:
                if (rhs.value.ui != 0) {
                    value.ui /= rhs.value.ui; 
                    type = is_uint; 
                }
                else {
                    valid = error_division_by_zero;      // division by zero
                }
                break;
            }
            break;
            
        case is_uint: 
            if (as_ulong(rhs) != 0) 
                value.ui /= as_ulong(rhs); 
            else
                valid = error_division_by_zero;         // division by zero
            break;

        case is_bool:  
            if (as_bool(rhs)) {
                switch(rhs.type) {
                case is_int:
                    value.i = (value.b ? 1 : 0) / rhs.value.i;
                    type = is_int;
                    break;
                    
                case is_uint:
                    value.i = (value.b ? 1 : 0) / rhs.value.ui;
                    type = is_int;
                    break;
                    
                case is_bool:
                    break;
                }
            }
            else {
                valid = error_division_by_zero;         // division by zero
            }
        }
        return *this;
    }

    closure_value &operator%= (closure_value const &rhs)
    {
        switch (type) {
        case is_int:    
            switch(rhs.type) {
            case is_bool:   
            case is_int:
                if (as_long(rhs) != 0) {
                    if (value.i == -value.i && -1 == rhs.value.i) {
                    // LONG_MIN % -1 on two's complement
                        valid = error_integer_overflow;
                    }
                    else {
                        value.i %= as_long(rhs); 
                    }
                }
                else {
                    valid = error_division_by_zero;      // division by zero
                }
                break;
                
            case is_uint:
                if (rhs.value.ui != 0) {
                    value.ui %= rhs.value.ui; 
                    type = is_uint; 
                }
                else {
                    valid = error_division_by_zero;      // division by zero
                }
                break;
            }
            break;
            
        case is_uint: 
            if (as_ulong(rhs) != 0) 
                value.ui %= as_ulong(rhs); 
            else
                valid = error_division_by_zero;      // division by zero
            break;

        case is_bool:  
            if (as_bool(rhs)) {
                switch(rhs.type) {
                case is_int:
                    value.i = (value.b ? 1 : 0) % rhs.value.i;
                    type = is_int;
                    break;
                    
                case is_uint:
                    value.i = (value.b ? 1 : 0) % rhs.value.ui;
                    type = is_int;
                    break;
                    
                case is_bool:
                    break;
                }                    
            }
            else {
                valid = error_division_by_zero;      // division by zero
            }
        }
        return *this;
    }


    closure_value &
    operator<<= (closure_value const &rhs)
    {
        switch (type) {
        case is_bool:
        case is_int:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                int_literal_type shift_by = as_long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.i <<= shift_by; 
                }
                break;
                
            case is_uint:
                {
                uint_literal_type shift_by = as_ulong(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui <<= shift_by; 
                
                // Note: The usual arithmetic conversions are not performed on 
                //       bit shift operations.
                }
                break;
            }
            break;

        case is_uint:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                int_literal_type shift_by = as_long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.ui <<= shift_by; 
                }
                break;
                
            case is_uint:
                {
                uint_literal_type shift_by = as_ulong(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui <<= shift_by; 
                }
                break;
            }
        }
        valid = (value_error)(valid | rhs.valid);
        return *this;
    }


    closure_value &
    operator>>= (closure_value const &rhs)
    {
        switch (type) {
        case is_bool:
        case is_int:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                int_literal_type shift_by = as_long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.i >>= shift_by; 
                }
                break;
                
            case is_uint:
                {
                uint_literal_type shift_by = as_ulong(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui >>= shift_by; 
                
                // Note: The usual arithmetic conversions are not performed on 
                //       bit shift operations.
                }
                break;
            }
            break;
            
        case is_uint:
            switch (rhs.type) {
            case is_bool:
            case is_int:
                {
                int_literal_type shift_by = as_long(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    else if (shift_by < -64)
                        shift_by = -64;
                    value.ui >>= shift_by; 
                }
                break;
                
            case is_uint:
                {
                uint_literal_type shift_by = as_ulong(rhs);
                    
                    if (shift_by > 64) 
                        shift_by = 64;
                    value.ui >>= shift_by; 
                }
                break;
            }
            break;
        }
        valid = (value_error)(valid | rhs.valid);
        return *this;
    }

    closure_value &
    handle_questionmark(closure_value const &cond, closure_value const &val2)
    {
        switch (type) {
        case is_int:
            switch (val2.type) {
            case is_bool: value.b = as_bool(cond) ? value.b : as_bool(val2); break;
            case is_int:  value.i = as_bool(cond) ? value.i : as_long(val2); break;
            case is_uint: 
                value.ui = as_bool(cond) ? value.ui : as_ulong(val2); 
                type = is_uint;   // changing type!
                break;
            }
            break;
            
        case is_uint:   value.ui = as_bool(cond) ? value.ui : as_ulong(val2); break;
        case is_bool:   value.b = as_bool(cond) ? value.b : as_bool(val2); break;
        }
        valid = as_bool(cond) ? valid : val2.valid;
        return *this;
    }

    token_data()
    :   id(T_EOI), refcnt(1)
    {}

    explicit token_data(int)
    :   id(T_UNKNOWN), refcnt(1)
    {}


    token_data(token_data const& rhs)
    :   id(rhs.id), value(rhs.value), pos(rhs.pos), refcnt(1)
    {}


    ~token_data()
    {}


    std::size_t addref() { return ++refcnt; }

    std::size_t release() { return --refcnt; }

    std::size_t get_refcnt() const { return refcnt; }


template <typename StringTypeT, typename PositionT>
inline void *
token_data<StringTypeT, PositionT>::operator new(std::size_t size)
{
    BOOST_ASSERT(sizeof(token_data<StringTypeT, PositionT>) == size);
    typedef boost::singleton_pool<
            token_data_tag, sizeof(token_data<StringTypeT, PositionT>)
        > pool_type;

    void *ret = pool_type::malloc();
    if (0 == ret)
        boost::throw_exception(std::bad_alloc());
    return ret;
}

    lex_token()
    :   data(0)
    {}

    explicit lex_token(int)
    :   data(new data_type(0))
    {}


    lex_token(lex_token const& rhs)
    :   data(rhs.data)
    {
        if (0 != data) 
            data->addref();
    }


    ~lex_token()
    {
        if (0 != data && 0 == data->release()) 
            delete data;
        data = 0;
    }


    lex_token& operator=(lex_token const& rhs)
    {
        if (&rhs != this) {
            if (0 != data && 0 == data->release()) 
                delete data;
            
            data = rhs.data;
            if (0 != data) 
                data->addref();
        }
        return *this;
    }

template <typename Position>
inline bool 
token_is_valid(lex_token<Position> const& t)
{
    return t.is_valid();
}

    lex_iterator_functor_shim() 
#if /*0 != __DECCXX_VER || */defined(__PGI)
      : eof()
#endif
    {}


    template <typename MultiPass>
    static result_type& get_next(MultiPass& mp, result_type& result)
    { 
        return mp.shared()->ftor->get(result); 
    }

    template <typename MultiPass>
    static void destroy(MultiPass& mp)
    { 
        delete mp.shared()->ftor; 
    }


    template <typename MultiPass>
    static void set_position(MultiPass& mp, position_type const &pos)
    {
        mp.shared()->ftor->set_position(pos);
    }


    lex_iterator()
    {}


    void set_position(typename TokenT::position_type const &pos)
    {
        typedef typename TokenT::position_type position_type;

    // set the new position in the current token
    token_type const& currtoken = this->base_type::dereference(*this);
    position_type currpos = currtoken.get_position();

        currpos.set_file(pos.get_file());
        currpos.set_line(pos.get_line());
        const_cast<token_type&>(currtoken).set_position(currpos);

    // set the new position for future tokens as well
        if (token_type::string_type::npos != 
            currtoken.get_value().find_first_of('\n'))
        {
            currpos.set_line(pos.get_line() + 1);
        }
        unique_functor_type::set_position(*this, currpos);
    }

inline bool
in_range(unsigned long ch, unsigned long l, unsigned long u)
{
    return (l <= ch && ch <= u);
}

inline universal_char_type
classify_universal_char (unsigned long ch)
{
// test for invalid characters
    if (ch <= 0x0020 || in_range(ch, 0x007f, 0x009f))
        return universal_char_type_invalid;

// test for characters in the range of the base character set
    if (in_range(ch, 0x0021, 0x005f) || in_range(ch, 0x0061, 0x007e))
        return universal_char_type_base_charset;

// test for additional valid character values (see C++ Standard: Annex E)
    if (in_range(ch, 0x00c0, 0x00d6) || in_range(ch, 0x00d8, 0x00f6) ||
        in_range(ch, 0x00f8, 0x01f5) || in_range(ch, 0x01fa, 0x0217) ||
        in_range(ch, 0x0250, 0x02a8) || in_range(ch, 0x1e00, 0x1e9a) ||
        in_range(ch, 0x1ea0, 0x1ef9))
    {
        return universal_char_type_valid;   // Latin
    }

    if (0x0384 == ch || in_range(ch, 0x0388, 0x038a) ||
        0x038c == ch || in_range(ch, 0x038e, 0x03a1) ||
        in_range(ch, 0x03a3, 0x03ce) || in_range(ch, 0x03d0, 0x03d6) ||
        0x03da == ch || 0x03dc == ch || 0x03de == ch || 0x03e0 == ch ||
        in_range(ch, 0x03e2, 0x03f3) || in_range(ch, 0x1f00, 0x1f15) ||
        in_range(ch, 0x1f18, 0x1f1d) || in_range(ch, 0x1f20, 0x1f45) ||
        in_range(ch, 0x1f48, 0x1f4d) || in_range(ch, 0x1f50, 0x1f57) ||
        0x1f59 == ch || 0x1f5b == ch || 0x1f5d == ch ||
        in_range(ch, 0x1f5f, 0x1f7d) || in_range(ch, 0x1f80, 0x1fb4) ||
        in_range(ch, 0x1fb6, 0x1fbc) || in_range(ch, 0x1fc2, 0x1fc4) ||
        in_range(ch, 0x1fc6, 0x1fcc) || in_range(ch, 0x1fd0, 0x1fd3) ||
        in_range(ch, 0x1fd6, 0x1fdb) || in_range(ch, 0x1fe0, 0x1fec) ||
        in_range(ch, 0x1ff2, 0x1ff4) || in_range(ch, 0x1ff6, 0x1ffc))
    {
        return universal_char_type_valid;   // Greek
    }

    if (in_range(ch, 0x0401, 0x040d) || in_range(ch, 0x040f, 0x044f) ||
        in_range(ch, 0x0451, 0x045c) || in_range(ch, 0x045e, 0x0481) ||
        in_range(ch, 0x0490, 0x04c4) || in_range(ch, 0x04c7, 0x04c8) ||
        in_range(ch, 0x04cb, 0x04cc) || in_range(ch, 0x04d0, 0x04eb) ||
        in_range(ch, 0x04ee, 0x04f5) || in_range(ch, 0x04f8, 0x04f9))
    {
        return universal_char_type_valid;   // Cyrillic
    }

    if (in_range(ch, 0x0531, 0x0556) || in_range(ch, 0x0561, 0x0587))
        return universal_char_type_valid;   // Armenian

    if (in_range(ch, 0x05d0, 0x05ea) || in_range(ch, 0x05f0, 0x05f4))
        return universal_char_type_valid;   // Hebrew

    if (in_range(ch, 0x0621, 0x063a) || in_range(ch, 0x0640, 0x0652) ||
        in_range(ch, 0x0670, 0x06b7) || in_range(ch, 0x06ba, 0x06be) ||
        in_range(ch, 0x06c0, 0x06ce) || in_range(ch, 0x06e5, 0x06e7))
    {
        return universal_char_type_valid;   // Arabic
    }

    if (in_range(ch, 0x0905, 0x0939) || in_range(ch, 0x0958, 0x0962))
        return universal_char_type_valid;   // Devanagari

    if (in_range(ch, 0x0985, 0x098c) || in_range(ch, 0x098f, 0x0990) ||
        in_range(ch, 0x0993, 0x09a8) || in_range(ch, 0x09aa, 0x09b0) ||
        0x09b2 == ch || in_range(ch, 0x09b6, 0x09b9) ||
        in_range(ch, 0x09dc, 0x09dd) || in_range(ch, 0x09df, 0x09e1) ||
        in_range(ch, 0x09f0, 0x09f1))
    {
        return universal_char_type_valid;   // Bengali
    }

    if (in_range(ch, 0x0a05, 0x0a0a) || in_range(ch, 0x0a0f, 0x0a10) ||
        in_range(ch, 0x0a13, 0x0a28) || in_range(ch, 0x0a2a, 0x0a30) ||
        in_range(ch, 0x0a32, 0x0a33) || in_range(ch, 0x0a35, 0x0a36) ||
        in_range(ch, 0x0a38, 0x0a39) || in_range(ch, 0x0a59, 0x0a5c) ||
        0x0a5e == ch)
    {
        return universal_char_type_valid;   // Gurmukhi
    }

    if (in_range(ch, 0x0a85, 0x0a8b) || 0x0a8d == ch ||
        in_range(ch, 0x0a8f, 0x0a91) || in_range(ch, 0x0a93, 0x0aa8) ||
        in_range(ch, 0x0aaa, 0x0ab0) || in_range(ch, 0x0ab2, 0x0ab3) ||
        in_range(ch, 0x0ab5, 0x0ab9) || 0x0ae0 == ch)
    {
        return universal_char_type_valid;   // Gujarati
    }

    if (in_range(ch, 0x0b05, 0x0b0c) || in_range(ch, 0x0b0f, 0x0b10) ||
        in_range(ch, 0x0b13, 0x0b28) || in_range(ch, 0x0b2a, 0x0b30) ||
        in_range(ch, 0x0b32, 0x0b33) || in_range(ch, 0x0b36, 0x0b39) ||
        in_range(ch, 0x0b5c, 0x0b5d) || in_range(ch, 0x0b5f, 0x0b61))
    {
        return universal_char_type_valid;   // Oriya
    }

    if (in_range(ch, 0x0b85, 0x0b8a) || in_range(ch, 0x0b8e, 0x0b90) ||
        in_range(ch, 0x0b92, 0x0b95) || in_range(ch, 0x0b99, 0x0b9a) ||
        0x0b9c == ch || in_range(ch, 0x0b9e, 0x0b9f) ||
        in_range(ch, 0x0ba3, 0x0ba4) || in_range(ch, 0x0ba8, 0x0baa) ||
        in_range(ch, 0x0bae, 0x0bb5) || in_range(ch, 0x0bb7, 0x0bb9))
    {
        return universal_char_type_valid;   // Tamil
    }

    if (in_range(ch, 0x0c05, 0x0c0c) || in_range(ch, 0x0c0e, 0x0c10) ||
        in_range(ch, 0x0c12, 0x0c28) || in_range(ch, 0x0c2a, 0x0c33) ||
        in_range(ch, 0x0c35, 0x0c39) || in_range(ch, 0x0c60, 0x0c61))
    {
        return universal_char_type_valid;   // Telugu
    }

    if (in_range(ch, 0x0c85, 0x0c8c) || in_range(ch, 0x0c8e, 0x0c90) ||
        in_range(ch, 0x0c92, 0x0ca8) || in_range(ch, 0x0caa, 0x0cb3) ||
        in_range(ch, 0x0cb5, 0x0cb9) || in_range(ch, 0x0ce0, 0x0ce1))
    {
        return universal_char_type_valid;   // Kannada
    }

    if (in_range(ch, 0x0d05, 0x0d0c) || in_range(ch, 0x0d0e, 0x0d10) ||
        in_range(ch, 0x0d12, 0x0d28) || in_range(ch, 0x0d2a, 0x0d39) ||
        in_range(ch, 0x0d60, 0x0d61))
    {
        return universal_char_type_valid;   // Malayalam
    }

    if (in_range(ch, 0x0e01, 0x0e30) || in_range(ch, 0x0e32, 0x0e33) ||
        in_range(ch, 0x0e40, 0x0e46) || in_range(ch, 0x0e4f, 0x0e5b))
    {
        return universal_char_type_valid;   // Thai
    }

    return universal_char_type_not_allowed_for_identifiers;
}

template <typename StringT>
inline void
validate_identifier_name (StringT const &name, std::size_t line, 
    std::size_t column, StringT const &file_name)
{
    using namespace std;    // some systems have strtoul in namespace std::

typename StringT::size_type pos = name.find_first_of('\\');

    while (StringT::npos != pos) {
    // the identifier name contains a backslash (must be universal char)
        BOOST_ASSERT('u' == name[pos+1] || 'U' == name[pos+1]);

    StringT uchar_val(name.substr(pos+2, ('u' == name[pos+1]) ? 4 : 8));
    universal_char_type type =
        classify_universal_char(strtoul(uchar_val.c_str(), 0, 16));

        if (universal_char_type_valid != type) {
        // an invalid char was found, so throw an exception
        StringT error_uchar(name.substr(pos, ('u' == name[pos+1]) ? 6 : 10));

            if (universal_char_type_invalid == type) {
                BOOST_WAVE_LEXER_THROW(lexing_exception, universal_char_invalid,
                    error_uchar, line, column, file_name.c_str());
            }
            else if (universal_char_type_base_charset == type) {
                BOOST_WAVE_LEXER_THROW(lexing_exception, universal_char_base_charset,
                    error_uchar, line, column, file_name.c_str());
            }
            else {
                BOOST_WAVE_LEXER_THROW(lexing_exception, universal_char_not_allowed,
                    error_uchar, line, column, file_name.c_str());
            }
        }

    // find next universal char (if appropriate)
        pos = name.find_first_of('\\', pos+2);
    }
}

template <typename StringT>
inline void
validate_literal (StringT const &name, std::size_t line, std::size_t column,
    StringT const &file_name)
{
    using namespace std;    // some systems have strtoul in namespace std::

typename StringT::size_type pos = name.find_first_of('\\');

    while (StringT::npos != pos) {
    // the literal contains a backslash (may be universal char)
        if ('u' == name[pos+1] || 'U' == name[pos+1]) {
        StringT uchar_val(name.substr(pos+2, ('u' == name[pos+1]) ? 4 : 8));
        universal_char_type type =
            classify_universal_char(strtoul(uchar_val.c_str(), 0, 16));

            if (universal_char_type_valid != type &&
                universal_char_type_not_allowed_for_identifiers != type)
            {
            // an invalid char was found, so throw an exception
            StringT error_uchar(name.substr(pos, ('u' == name[pos+1]) ? 6 : 10));

                if (universal_char_type_invalid == type) {
                    BOOST_WAVE_LEXER_THROW(lexing_exception, universal_char_invalid,
                        error_uchar, line, column, file_name.c_str());
                }
                else {
                    BOOST_WAVE_LEXER_THROW(lexing_exception, universal_char_base_charset,
                        error_uchar, line, column, file_name.c_str());
                }
            }
        }

    // find next universal char (if appropriate)
        pos = name.find_first_of('\\', pos+2);
    }
}

    include_guards()
    :   state(&include_guards::state_0), detected_guards(false), 
        current_state(true), if_depth(0)
    {}


    Token& detect_guard(Token& t) 
        { return current_state ? (this->*state)(t) : t; }

    bool detected(std::string& guard_name_) const 
    {
        if (detected_guards) {
            guard_name_ = guard_name.c_str();
            return true;
        }
        return false; 
    }


    bool is_skippable(token_id id) const
    {
        return (T_POUND == BASE_TOKEN(id) || 
                IS_CATEGORY(id, WhiteSpaceTokenType) ||
                IS_CATEGORY(id, EOLTokenType));
    }

template <typename Token>
inline Token& 
include_guards<Token>::state_0(Token& t)
{
    token_id id = token_id(t);
    if (T_PP_IFNDEF == id)
        state = &include_guards::state_1;
    else if (T_PP_IF == id)
        state = &include_guards::state_1a;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1(Token& t)
{
    token_id id = token_id(t);
    if (T_IDENTIFIER == id) {
        guard_name = t.get_value();
        state = &include_guards::state_2;
    }
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1a(Token& t)
{
    token_id id = token_id(t);
    if (T_NOT == BASE_TOKEN(id)) 
        state = &include_guards::state_1b;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1b(Token& t)
{
    token_id id = token_id(t);
    if (T_IDENTIFIER == id && t.get_value() == "defined") 
        state = &include_guards::state_1c;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1c(Token& t)
{
    token_id id = token_id(t);
    if (T_LEFTPAREN == id) 
        state = &include_guards::state_1d;
    else if (T_IDENTIFIER == id) {
        guard_name = t.get_value();
        state = &include_guards::state_2;
    }
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1d(Token& t)
{
    token_id id = token_id(t);
    if (T_IDENTIFIER == id) {
        guard_name = t.get_value();
        state = &include_guards::state_1e;
    }
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_1e(Token& t)
{
    token_id id = token_id(t);
    if (T_RIGHTPAREN == id) 
        state = &include_guards::state_2;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_2(Token& t)
{
    token_id id = token_id(t);
    if (T_PP_DEFINE == id) 
        state = &include_guards::state_3;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_3(Token& t)
{
    token_id id = token_id(t);
    if (T_IDENTIFIER == id && t.get_value() == guard_name)
        state = &include_guards::state_4;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_4(Token& t)
{
    token_id id = token_id(t);
    if (T_PP_IF == id || T_PP_IFDEF == id || T_PP_IFNDEF == id)
        ++if_depth;
    else if (T_PP_ENDIF == id) {
        if (if_depth > 0)
            --if_depth;
        else
            state = &include_guards::state_5;
    }
    return t;
}

template <typename Token>
inline Token& 
include_guards<Token>::state_5(Token& t)
{
    token_id id = token_id(t);
    if (T_EOF == id) 
        detected_guards = current_state;
    else if (!is_skippable(id))
        current_state = false;
    return t;
}


    inline char const *
    get_severity(severity level)
    {
        static char const *severity_text[] =
        {
            "remark",           // severity_remark
            "warning",          // severity_warning
            "error",            // severity_error
            "fatal error"       // severity_fatal
        };
        BOOST_ASSERT(severity_remark <= level && level <= severity_fatal);
        return severity_text[level];
    }


    lex_input_interface_generator() {}

    ~lex_input_interface_generator() {}


    lex_input_interface() {}

    virtual ~lex_input_interface() {}

    token_cache()
    :   cache(T_LAST_TOKEN - T_FIRST_TOKEN)
    {
        typename std::vector<StringT>::iterator it = cache.begin();
        for (unsigned int i = T_FIRST_TOKEN; i < T_LAST_TOKEN;  ++i, ++it)
        {
            *it = StringT(boost::wave::get_token_value(token_id(i)));
        }
    }


    StringT const &get_token_value(token_id id) const
    {
        return cache[BASEID_FROM_TOKEN(id) - T_FIRST_TOKEN];
    }

template <typename StringT>
inline bool 
is_trigraph(StringT const& trigraph)
{
    if (trigraph.size() < 3 || '?' != trigraph[0] || '?' != trigraph[1])
        return false;
        
    switch (trigraph[2]) {
    case '\'': case '=': case '/': case '(':
    case ')':  case '<': case '>': case '!':
    case '-':
        break;

    default:
        return false;
    }

    return true;
}

template <typename StringT>
inline StringT
convert_trigraph(StringT const &trigraph)
{
StringT result (trigraph);

    if (is_trigraph(trigraph)) {
        switch (trigraph[2]) {
        case '\'':  result = "^"; break;
        case '=':   result = "#"; break;
        case '/':   result = "\\"; break;
        case '(':   result = "["; break;
        case ')':   result = "]"; break;
        case '<':   result = "{"; break;
        case '>':   result = "}"; break;
        case '!':   result = "|"; break;
        case '-':   result = "~"; break;
        }
    }
    return result;
}

template <typename StringT>
inline StringT
convert_trigraphs(StringT const &value)
{
    StringT result;
    typename StringT::size_type pos = 0;
    typename StringT::size_type pos1 = value.find_first_of ("?", 0);
    if (StringT::npos != pos1) {
        do {
            result += value.substr(pos, pos1-pos);
            StringT trigraph (value.substr(pos1)); 
            if (is_trigraph(trigraph)) {
                result += convert_trigraph(trigraph);
                pos1 = value.find_first_of ("?", pos = pos1+3);
            }
            else {
                result += value[pos1];
                pos1 = value.find_first_of ("?", pos = pos1+1);
            }
        } while (StringT::npos != pos1);
        result += value.substr(pos);
    }
    else {
        result = value;
    }
    return result;
}

        pop_front(ContainerT &list_) : list(list_) {}

        ~pop_front() { list.pop_front(); }

        splice_pop_front(ContainerT &list_, ContainerT &queue) 
        :   list(list_) 
        {
            list.splice(list.end(), queue);
        }

        ~splice_pop_front() { list.pop_front(); }

        reset(TypeT &target_value_, TypeT new_value)
        :   target_value(target_value_), old_value(target_value_)
        {
            target_value_ = new_value;
        }

        ~reset() { target_value = old_value; }

        assign(IteratorT &it_, UnputIteratorT const &uit_) 
        :   it(it_), uit(uit_) {}

        ~assign() { it = uit.base(); }

        assign(IteratorT &it_, IteratorT const &uit_) 
        :   it(it_), uit(uit_) {}

        ~assign() { it = uit; }

template <typename StringT>
inline bool 
is_special_macroname (StringT const &name)
{
    if (name.size() < 7)
        return false;

    if ("defined" == name)
        return true;

    if ('_' == name[0] && '_' == name[1]) {
    StringT str = name.substr(2);

        if (str == "cplusplus"  || str == "STDC__" || 
            str == "TIME__"     || str == "DATE__" ||
            str == "LINE__"     || str == "FILE__" ||
            str == "INCLUDE_LEVEL__")
        {
            return true;
        }
    }
    return false;
}

template <typename TokenT>
inline bool 
token_equals(TokenT const &left, TokenT const &right)
{
    using namespace boost::wave;

    if (IS_CATEGORY(left, ParameterTokenType)) {
    //  if the existing token is of type T_PARAMETERBASE, then the right token 
    //  must be of type T_IDENTIFIER or a keyword
    token_id id = token_id(right);

        return (T_IDENTIFIER == id || 
                IS_CATEGORY(id, KeywordTokenType) ||
                IS_EXTCATEGORY(id, OperatorTokenType|AltExtTokenType) ||
                IS_CATEGORY(id, BoolLiteralTokenType)) && 
            left.get_value() == right.get_value();
    }

    // if the left token has whitespace, the value is irrelevant
    return token_id(left) == token_id(right) && (
            IS_CATEGORY(left, WhiteSpaceTokenType) ||
            left.get_value() == right.get_value()
        );
}

template <typename ContainerT>
inline bool 
definition_equals(ContainerT const &definition, 
    ContainerT const &new_definition)
{
    typedef typename ContainerT::const_iterator const_iterator_type;

const_iterator_type first1 = definition.begin();
const_iterator_type last1 = definition.end();
const_iterator_type first2 = new_definition.begin();
const_iterator_type last2 = new_definition.end();

    while (first1 != last1 && first2 != last2 && token_equals(*first1, *first2)) 
    {
    // skip whitespace, if both sequences have a whitespace next
    token_id id1 = next_token<const_iterator_type>::peek(first1, last1, false);
    token_id id2 = next_token<const_iterator_type>::peek(first2, last2, false);

        if (IS_CATEGORY(id1, WhiteSpaceTokenType) && 
            IS_CATEGORY(id2, WhiteSpaceTokenType)) 
        {
        // all consecutive whitespace tokens count as one whitespace
        // adjust first1 and first2 accordingly
            skip_whitespace(first1, last1);
            skip_whitespace(first2, last2);
        }
        else if (!IS_CATEGORY(id1, WhiteSpaceTokenType) && 
                 !IS_CATEGORY(id2, WhiteSpaceTokenType)) 
        {
            ++first1;
            ++first2;
        }
        else {
        // the sequences differ
            break;
        }
    }
    return (first1 == last1 && first2 == last2) ? true : false;
}

template <typename ContainerT>
inline bool 
parameters_equal(ContainerT const &parameters, ContainerT const &new_parameters)
{
    if (parameters.size() != new_parameters.size())
        return false;   // different parameter count

    typedef typename ContainerT::const_iterator const_iterator_type;

const_iterator_type first1 = parameters.begin();
const_iterator_type last1 = parameters.end();
const_iterator_type first2 = new_parameters.begin();
const_iterator_type last2 = new_parameters.end();

    while (first1 != last1 && first2 != last2) {
    // parameters are different, if the corresponding tokens are different
        using namespace boost::wave;
        if (token_id(*first1) != token_id(*first2) ||
            (*first1).get_value() != (*first2).get_value())
        {
            break;
        }
        ++first1;
        ++first2;
    }
    return (first1 == last1 && first2 == last2) ? true : false;
}

template <typename ContainerT>
inline void
trim_replacement_list (ContainerT &replacement_list)
{
    using namespace boost::wave;

// strip leading whitespace
    if (replacement_list.size() > 0) {
    typename ContainerT::iterator end = replacement_list.end();
    typename ContainerT::iterator it = replacement_list.begin();

        while (it != end && IS_CATEGORY(*it, WhiteSpaceTokenType)) { 
            token_id id(*it);
            if (T_PLACEHOLDER != id && T_PLACEMARKER != id) {
                typename ContainerT::iterator next = it;
                ++next;
                replacement_list.erase(it);
                it = next;
            }
            else {
                ++it;
            }
        }
    }

// strip trailing whitespace
    if (replacement_list.size() > 0) {
    typename ContainerT::reverse_iterator rend = replacement_list.rend();
    typename ContainerT::reverse_iterator rit = replacement_list.rbegin();

        while (rit != rend && IS_CATEGORY(*rit, WhiteSpaceTokenType)) 
            ++rit;

    typename ContainerT::iterator end = replacement_list.end();
    typename ContainerT::iterator it = rit.base();

        while (it != end && IS_CATEGORY(*it, WhiteSpaceTokenType)) { 
            token_id id(*it);
            if (T_PLACEHOLDER != id && T_PLACEMARKER != id) {
                typename ContainerT::iterator next = it;
                ++next;
                replacement_list.erase(it);
                it = next;
            }
            else {
                ++it;
            }
        }
    }
}

template <typename ContainerT>
inline bool
is_whitespace_only (ContainerT const &argument)
{
    typename ContainerT::const_iterator end = argument.end();
    for (typename ContainerT::const_iterator it = argument.begin();
          it != end; ++it)
    {
        if (!IS_CATEGORY(*it, WhiteSpaceTokenType))
            return false;
    }
    return true;
}

template <typename ContainerT>
inline void
remove_placeholders (ContainerT &replacement_list)
{
    using namespace boost::wave;

// strip leading whitespace
    if (replacement_list.size() > 0) {
    typename ContainerT::iterator end = replacement_list.end();
    typename ContainerT::iterator it = replacement_list.begin();

        while (it != end) {
            token_id id(*it);
            if (T_PLACEHOLDER == id || T_PLACEMARKER == id) {
                typename ContainerT::iterator next = it;
                ++next;
                replacement_list.erase(it);
                it = next;
            }
            else {
                ++it;
            }
        }

    // remove all 'new' leading and trailing whitespace 
        if (is_whitespace_only(replacement_list))
            trim_replacement_list(replacement_list);
    }
}

template <typename ContainerT>
inline void
trim_sequence_left (ContainerT &argument)
{
    using namespace boost::wave;

// strip leading whitespace (should be only one token)
    if (argument.size() > 0 &&
        IS_CATEGORY(argument.front(), WhiteSpaceTokenType))
    {
        argument.pop_front();
    }
}

template <typename ContainerT>
inline void
trim_sequence_right (ContainerT &argument)
{
    using namespace boost::wave;

// strip trailing whitespace (should be only one token)
    if (argument.size() > 0 &&
        IS_CATEGORY(argument.back(), WhiteSpaceTokenType))
    {
        argument.pop_back();
    }
}

template <typename ContainerT>
inline void
trim_sequence (ContainerT &argument)
{
    trim_sequence_left(argument);
    trim_sequence_right(argument);
}

template <typename ContextT>
void call_skipped_token_hook(ContextT& ctx, 
    typename ContextT::token_type const& skipped)
{
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    ctx.get_hooks().skipped_token(skipped);     
#else
    ctx.get_hooks().skipped_token(ctx.derived(), skipped);
#endif
}

template <typename ContextT, typename IteratorT>
inline bool 
skip_to_token(ContextT& ctx, IteratorT &it, IteratorT const &end, 
    token_id id, bool& seen_newline)
{
    using namespace boost::wave;
    if (token_id(*it) == id) 
        return true;

//     call_skipped_token_hook(ctx, *it);
    if (++it == end) 
        return false;

    while (IS_CATEGORY(*it, WhiteSpaceTokenType) || 
           T_NEWLINE == token_id(*it)) 
    {
        if (T_NEWLINE == token_id(*it))
            seen_newline = true;

//         call_skipped_token_hook(ctx, *it);
        if (++it == end)
            return false;
    }
    return token_id(*it) == id;
}

template <typename IteratorT>
inline std::string
get_full_name(IteratorT const &begin, IteratorT const &end)
{
    std::string full_name;
    for (IteratorT err_it = begin; err_it != end; ++err_it) 
        full_name += (*err_it).get_value().c_str();

    return full_name;
}

    find_concat_operator(bool &found_) : found_concat(found_) {}


    template <typename TokenT>
    bool operator()(TokenT const &tok)
    {
        using namespace boost::wave;
        if (T_POUND_POUND == BASE_TOKEN(token_id(tok)))
            found_concat = true;
        return false;
    }


    static Target call(Src const& str)
    {
        return Target(str.c_str());
    }


    static Src const& call(Src const& str)
    {
        return str;
    }


    static Target call(char const* str)
    {
        return Target(str);
    }


template <typename Target, typename Src>
inline typename impl::to_string_helper<Target, Src>::type
to_string(Src const& src)
{
    return impl::to_string_helper<Target, Src>::call(src);
}

    template <typename StringT>
    inline StringT
    escape_lit(StringT const &value)
    {
        StringT result;
        typename StringT::size_type pos = 0;
        typename StringT::size_type pos1 = value.find_first_of ("\"\\?", 0);
        if (StringT::npos != pos1) {
            do {
                result += value.substr(pos, pos1-pos) 
                            + StringT("\\") 
                            + StringT(1, value[pos1]);
                pos1 = value.find_first_of ("\"\\?", pos = pos1+1);
            } while (StringT::npos != pos1);
            result += value.substr(pos);
        }
        else {
            result = value;
        }
        return result;
    }

    template <typename StringT>
    inline StringT
    unescape_lit(StringT const &value)
    {
        StringT result;
        typename StringT::size_type pos = 0;
        typename StringT::size_type pos1 = value.find_first_of ("\\", 0);
        if (StringT::npos != pos1) {
            do {
                switch (value[pos1+1]) {
                case '\\':
                case '\"':
                case '?':
                    result = result + value.substr(pos, pos1-pos);
                    pos1 = value.find_first_of ("\\", (pos = pos1+1)+1);
                    break;

                case 'n':
                    result = result + value.substr(pos, pos1-pos) + "\n";
                    pos1 = value.find_first_of ("\\", pos = pos1+1);
                    ++pos;
                    break;

                default:
                    result = result + value.substr(pos, pos1-pos+1);
                    pos1 = value.find_first_of ("\\", pos = pos1+1);
                }

            } while (pos1 != StringT::npos);
            result = result + value.substr(pos);
        }
        else {
        // the string doesn't contain any escaped character sequences
            result = value;
        }
        return result;
    }

    template <typename ContainerT, typename PositionT>
    inline typename ContainerT::value_type::string_type
    as_stringlit (ContainerT const &token_sequence, PositionT const &pos)
    {
        using namespace boost::wave;
        typedef typename ContainerT::value_type::string_type string_type;

        string_type result("\"");
        bool was_whitespace = false;
        typename ContainerT::const_iterator end = token_sequence.end();
        for (typename ContainerT::const_iterator it = token_sequence.begin(); 
             it != end; ++it) 
        {
            token_id id = token_id(*it);

            if (IS_CATEGORY(*it, WhiteSpaceTokenType) || T_NEWLINE == id) {
                if (!was_whitespace) {
                // C++ standard 16.3.2.2 [cpp.stringize]
                // Each occurrence of white space between the argument's 
                // preprocessing tokens becomes a single space character in the 
                // character string literal.
                    result += " ";
                    was_whitespace = true;
                }
            }
            else if (T_STRINGLIT == id || T_CHARLIT == id) {
            // string literals and character literals have to be escaped
                result += impl::escape_lit((*it).get_value());
                was_whitespace = false;
            }
            else 
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
            if (T_PLACEMARKER != id) 
#endif 
            {
            // now append this token to the string
                result += (*it).get_value();
                was_whitespace = false;
            }
        }
        result += "\"";

    // validate the resulting literal to contain no invalid universal character
    // value (throws if invalid chars found)
        boost::wave::cpplexer::impl::validate_literal(result, pos.get_line(), 
            pos.get_column(), pos.get_file()); 
        return result;
    }

    template <typename StringT, typename IteratorT>
    inline StringT
    as_string(IteratorT it, IteratorT const& end)
    {
        StringT result;
        for (/**/; it != end; ++it) 
        {
            result += (*it).get_value();
        }
        return result;
    }

    template <typename ContainerT>
    inline typename ContainerT::value_type::string_type
    as_string (ContainerT const &token_sequence)
    {
        typedef typename ContainerT::value_type::string_type string_type;
        return as_string<string_type>(token_sequence.begin(), 
            token_sequence.end());
    }

    template <typename IteratorT>
    inline boost::wave::token_id 
    skip_whitespace(IteratorT &first, IteratorT const &last)
    {
        token_id id = util::impl::next_token<IteratorT>::peek(first, last, false);
        if (IS_CATEGORY(id, WhiteSpaceTokenType)) {
            do {
                ++first;
                id = util::impl::next_token<IteratorT>::peek(first, last, false);
            } while (IS_CATEGORY(id, WhiteSpaceTokenType));
        }
        ++first;
        return id;
    }

        void reset_datestr()
        {
        static const char *const monthnames[] = {
                "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
            };

        // for some systems sprintf, time_t etc. is in namespace std
            using namespace std;

        time_t tt = time(0);
        struct tm *tb = 0;

            if (tt != (time_t)-1) {
            char buffer[sizeof("\"Oct 11 1347\"")+1];

                tb = localtime (&tt);
                sprintf (buffer, "\"%s %2d %4d\"",
                    monthnames[tb->tm_mon], tb->tm_mday, tb->tm_year + 1900);
                datestr_ = buffer;
            }
            else {
                datestr_ = "\"??? ?? ????\"";
            }
        }


        void reset_timestr()
        {
        // for some systems sprintf, time_t etc. is in namespace std
            using namespace std;

        time_t tt = time(0);
        struct tm *tb = 0;

            if (tt != (time_t)-1) {
            char buffer[sizeof("\"12:34:56\"")+1];

                tb = localtime (&tt);
                sprintf (buffer, "\"%02d:%02d:%02d\"", tb->tm_hour, 
                    tb->tm_min, tb->tm_sec);
                timestr_ = buffer;
            }
            else {
                timestr_ = "\"??:??:??\"";
            }
        }


        void reset_version()
        {
        char buffer[sizeof("0x00000000")+1];

        // for some systems sprintf, time_t etc. is in namespace std
            using namespace std;

        // calculate the number of days since Dec 13 2001 
        // (the day the Wave project was started)
        tm first_day;

            using namespace std;    // for some systems memset is in namespace std
            memset (&first_day, 0, sizeof(tm));
            first_day.tm_mon = 11;           // Dec
            first_day.tm_mday = 13;          // 13
            first_day.tm_year = 101;         // 2001

        long seconds = long(difftime(compilation_time_.get_time(), mktime(&first_day)));

            sprintf(buffer, "0x%02d%1d%1d%04ld", BOOST_WAVE_VERSION_MAJOR,
                 BOOST_WAVE_VERSION_MINOR, BOOST_WAVE_VERSION_SUBMINOR, 
                 seconds/(3600*24));
            version_ = buffer;
        }


        void reset_versionstr()
        {
        char buffer[sizeof("\"00.00.00.0000 \"")+sizeof(BOOST_PLATFORM)+sizeof(BOOST_COMPILER)+4];

        // for some systems sprintf, time_t etc. is in namespace std
            using namespace std;

        // calculate the number of days since Dec 13 2001 
        // (the day the Wave project was started)
        tm first_day;

            memset (&first_day, 0, sizeof(tm));
            first_day.tm_mon = 11;           // Dec
            first_day.tm_mday = 13;          // 13
            first_day.tm_year = 101;         // 2001

        long seconds = long(difftime(compilation_time_.get_time(), mktime(&first_day)));

            sprintf(buffer, "\"%d.%d.%d.%ld [%s/%s]\"", BOOST_WAVE_VERSION_MAJOR,
                 BOOST_WAVE_VERSION_MINOR, BOOST_WAVE_VERSION_SUBMINOR, 
                 seconds/(3600*24), BOOST_PLATFORM, BOOST_COMPILER);
            versionstr_ = buffer;
        }

        string_type get_date() const { return datestr_; }

        string_type get_time() const { return timestr_; }

        string_type get_version() const
        {
            char buffer[sizeof("0x0000")+1];

            using namespace std;    // for some systems sprintf is in namespace std
            sprintf(buffer, "0x%02d%1d%1d", BOOST_WAVE_VERSION_MAJOR, 
                BOOST_WAVE_VERSION_MINOR, BOOST_WAVE_VERSION_SUBMINOR);
            return buffer;
        }

        string_type get_config() const
        {
            char buffer[sizeof("0x00000000")+1];

            using namespace std;     // for some systems sprintf is in namespace std
            sprintf(buffer, "0x%08x", BOOST_WAVE_CONFIG);
            return buffer;
        }

        predefined_macros() 
          : compilation_time_(__DATE__ " " __TIME__)
        { 
            reset(); 
            reset_version();
            reset_versionstr();
        }


        void reset()
        {
            reset_datestr();
            reset_timestr();
        }

        string_type get_fullversion() const { return version_; }

        string_type get_versionstr() const { return versionstr_; }

        static_macros const& static_data_cpp(std::size_t i) const
        {
        static static_macros data[] = {
                { "__STDC__", T_INTLIT, "1" },
                { "__cplusplus", T_INTLIT, "199711L" },
                { 0, T_EOF, 0 }
            }; 
            BOOST_ASSERT(i < sizeof(data)/sizeof(data[0]));
            return data[i];
        }
 

        dynamic_macros const& dynamic_data(std::size_t i) const
        {
        static dynamic_macros data[] = {
                { "__DATE__", T_STRINGLIT, &predefined_macros::get_date },
                { "__TIME__", T_STRINGLIT, &predefined_macros::get_time },
                { "__SPIRIT_PP__", T_INTLIT, &predefined_macros::get_version },
                { "__SPIRIT_PP_VERSION__", T_INTLIT, &predefined_macros::get_fullversion },
                { "__SPIRIT_PP_VERSION_STR__", T_STRINGLIT, &predefined_macros::get_versionstr },
                { "__WAVE__", T_INTLIT, &predefined_macros::get_version },
                { "__WAVE_VERSION__", T_INTLIT, &predefined_macros::get_fullversion },
                { "__WAVE_VERSION_STR__", T_STRINGLIT, &predefined_macros::get_versionstr },
                { "__WAVE_CONFIG__", T_INTLIT, &predefined_macros::get_config },
                { 0, T_EOF, 0 }
            };
            BOOST_ASSERT(i < sizeof(data)/sizeof(data[0]));
            return data[i];
        }

    include_paths()
    :   was_sys_include_path(false),
        current_dir(initial_path()),
        current_rel_dir(initial_path())
    {}

    
    bool add_include_path(char const *path_, bool is_system = false)
    {
        return add_include_path(path_, (is_system || was_sys_include_path) ? 
            system_include_paths : user_include_paths);
    }

    void set_sys_include_delimiter() { was_sys_include_path = true; }

    boost::filesystem::path get_current_directory() const 
        { return current_dir; }

template <typename ContextT, typename IteratorT, typename ContainerT>
inline bool 
interpret_pragma(ContextT &ctx, typename ContextT::token_type const &act_token,
    IteratorT it, IteratorT const &end, ContainerT &pending)
{
    typedef typename ContextT::token_type token_type;
    typedef typename token_type::string_type string_type;

    using namespace cpplexer;
    if (T_IDENTIFIER == token_id(*it)) {
    // check for pragma wave ...
        if ((*it).get_value() == BOOST_WAVE_PRAGMA_KEYWORD) 
        {
        //  this is a wave specific option, it should have the form:
        //
        //      #pragma command option(value)
        //
        //  where 
        //      'command' is the value of the preprocessor constant
        //                BOOST_WAVE_PRAGMA_KEYWORD (defaults to "wave") and
        //      '(value)' is required only for some pragma directives (this is 
        //                optional)
        //
        //  All recognized #pragma operators are forwarded to the supplied 
        //  preprocessing hook.
            using namespace boost::spirit::classic;
            token_type option;
            ContainerT values;
            
            if (!parse (++it, end, 
                            (   ch_p(T_IDENTIFIER)
                                [
                                    spirit_assign_actor(option)
                                ] 
                            |   pattern_p(KeywordTokenType, 
                                    TokenTypeMask|PPTokenFlag)
                                [
                                    spirit_assign_actor(option)
                                ] 
                            |   pattern_p(OperatorTokenType|AltExtTokenType, 
                                    ExtTokenTypeMask|PPTokenFlag)   // and, bit_and etc.
                                [
                                    spirit_assign_actor(option)
                                ] 
                            |   pattern_p(BoolLiteralTokenType, 
                                    TokenTypeMask|PPTokenFlag)
                                [
                                    spirit_assign_actor(option)
                                ] 
                            )
                        >> !comment_nest_p(
                                ch_p(T_LEFTPAREN),
                                ch_p(T_RIGHTPAREN)
                            )[spirit_assign_actor(values)],
                    pattern_p(WhiteSpaceTokenType, TokenTypeMask|PPTokenFlag)).hit)
            {
                typename ContextT::string_type msg(
                    impl::as_string<string_type>(it, end));
                BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, 
                    ill_formed_pragma_option,
                    msg.c_str(), act_token.get_position());
                return false;
            }

        // remove the falsely matched surrounding parenthesis's
            if (values.size() >= 2) {
                BOOST_ASSERT(T_LEFTPAREN == values.front() && T_RIGHTPAREN == values.back());
                values.erase(values.begin());
                typename ContainerT::reverse_iterator rit = values.rbegin();
                values.erase((++rit).base());
            }

        // decode the option (call the context_policy hook)
            if (!ctx.get_hooks().interpret_pragma(
                  ctx.derived(), pending, option, values, act_token)) 
            {
            // unknown #pragma option 
            string_type option_str ((*it).get_value());

                option_str += option.get_value();
                if (values.size() > 0) {
                    option_str += "(";
                    option_str += impl::as_string(values);
                    option_str += ")";
                }
                BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, 
                    ill_formed_pragma_option,
                    option_str.c_str(), act_token.get_position());
                return false;
            }
            return true;
        }
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
        else if ((*it).get_value() == "once") {
        // #pragma once
            return ctx.add_pragma_once_header(act_token, ctx.get_current_filename());
        }
#endif 
#if BOOST_WAVE_SUPPORT_PRAGMA_MESSAGE != 0
        else if ((*it).get_value() == "message") {
        // #pragma message(...) or #pragma message ...
            using namespace boost::spirit::classic;
            ContainerT values;

            if (!parse (++it, end, 
                            (   (   ch_p(T_LEFTPAREN) 
                                >>  lexeme_d[
                                        *(anychar_p[spirit_append_actor(values)] - ch_p(T_RIGHTPAREN))
                                    ]
                                >>  ch_p(T_RIGHTPAREN)
                                )
                            |   lexeme_d[
                                    *(anychar_p[spirit_append_actor(values)] - ch_p(T_NEWLINE))
                                ]
                            ),
                            pattern_p(WhiteSpaceTokenType, TokenTypeMask|PPTokenFlag)
                       ).hit
               )
            {
                typename ContextT::string_type msg(
                    impl::as_string<string_type>(it, end));
                BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, 
                    ill_formed_pragma_message,
                    msg.c_str(), act_token.get_position());
                return false;
            }

        // remove the falsely matched closing parenthesis/newline
            if (values.size() > 0) {
                BOOST_ASSERT(T_RIGHTPAREN == values.back() || T_NEWLINE == values.back());
                typename ContainerT::reverse_iterator rit = values.rbegin();
                values.erase((++rit).base());
            }

        // output the message itself
            typename ContextT::string_type msg(impl::as_string(values));
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, 
                pragma_message_directive, 
                msg.c_str(), act_token.get_position());
            return false;
        }
#endif
    }
    return false;
}


    unput_queue_iterator(IteratorT const &it, ContainerT &queue)
    :   base_type(it), unput_queue(queue)
    {}

    
    ContainerT &get_unput_queue() 
        { return unput_queue; }

    ContainerT const &get_unput_queue() const 
        { return unput_queue; }

    IteratorT &get_base_iterator() 
        { return base_type::base_reference(); }

    IteratorT const &get_base_iterator() const 
        { return base_type::base_reference(); }

    
    unput_queue_iterator &operator= (unput_queue_iterator const &rhs)
    { 
        if (this != &rhs) {
            unput_queue = rhs.unput_queue; 
            base_type::operator=(rhs);
        }
        return *this; 
    }


        static return_type
        generate(iterator_type const &it)
        {
            return return_type(it, last);
        }


        static return_type
        generate(ContainerT &queue, iterator_type const &it)
        {
            return return_type(it, queue);
        }


        static return_type 
        generate(iterator_type &it)
        {
            return return_type(it.base(), last);
        }


        static return_type 
        generate(ContainerT &queue, iterator_type &it)
        {
            return return_type(it.base(), queue);
        }

        static void 
        do_ (IteratorT &dest, IteratorT const &src)
        {
            dest = src;
        }

        static boost::wave::token_id  
        peek(IteratorT it, IteratorT end, bool skip_whitespace = true)
        {
            using namespace boost::wave;
            if (skip_whitespace) {
                for (++it; it != end; ++it) {
                    if (!IS_CATEGORY(*it, WhiteSpaceTokenType) &&
                        T_NEWLINE != token_id(*it))
                    {
                        break;  // stop at the first non-whitespace token
                    }
                }
            }
            else {
                ++it;           // we have at least to look ahead
            }
            if (it != end) 
                return token_id(*it);
            return T_EOI;
        }


        static boost::wave::token_id 
        peek(iterator_type it, iterator_type end, bool skip_whitespace = true)
        {
            using namespace boost::wave;

        typename iterator_type::container_type &queue = it.get_unput_queue();

        // first try to find it in the unput_queue
            if (0 != queue.size()) {
            typename iterator_type::container_type::iterator cit = queue.begin();
            typename iterator_type::container_type::iterator cend = queue.end();

                if (skip_whitespace) {
                    for (++cit; cit != cend; ++cit) {
                        if (!IS_CATEGORY(*cit, WhiteSpaceTokenType) &&
                            T_NEWLINE != token_id(*cit))
                        {
                            break;  // stop at the first non-whitespace token
                        }
                    }
                }
                else {
                    ++cit;          // we have at least to look ahead
                }
                if (cit != cend) 
                    return token_id(*cit);
            }

        // second try to move on into the base iterator stream
        typename iterator_type::iterator_type base_it = it.get_base_iterator();
        typename iterator_type::iterator_type base_end = end.get_base_iterator();

            if (0 == queue.size())
                ++base_it;  // advance, if the unput queue is empty

            if (skip_whitespace) {
                for (/**/; base_it != base_end; ++base_it) {
                    if (!IS_CATEGORY(*base_it, WhiteSpaceTokenType) &&
                        T_NEWLINE != token_id(*base_it))
                    {
                        break;  // stop at the first non-whitespace token
                    }
                }
            }
            if (base_it == base_end)
                return T_EOI;

            return token_id(*base_it);
        }


    iteration_context_stack()
    :   max_include_nesting_depth(BOOST_WAVE_MAX_INCLUDE_LEVEL_DEPTH)
    {}


    void set_max_include_nesting_depth(size_type new_depth)
        {  max_include_nesting_depth = new_depth; }

    size_type get_max_include_nesting_depth() const
        { return max_include_nesting_depth; }


    typename base_type::size_type size() const { return iter_ctx.size(); }

    template <class InIt, class OutIt>
    OutIt copy_n(InIt b, 
        typename std::iterator_traits<InIt>::difference_type n, OutIt d)
    {
        for (/**/; n != 0; --n, ++b, ++d)
        {
            *d = *b;
        }
        return d;
    }


    template <class Pod, class T>
    inline void pod_fill(Pod* b, Pod* e, T c)
    {
        switch ((e - b) & 7)
        {
        case 0:
            while (b != e)
            {
                *b = c; ++b; BOOST_FALLTHROUGH;
        case 7: *b = c; ++b; BOOST_FALLTHROUGH;
        case 6: *b = c; ++b; BOOST_FALLTHROUGH;
        case 5: *b = c; ++b; BOOST_FALLTHROUGH;
        case 4: *b = c; ++b; BOOST_FALLTHROUGH;
        case 3: *b = c; ++b; BOOST_FALLTHROUGH;
        case 2: *b = c; ++b; BOOST_FALLTHROUGH;
        case 1: *b = c; ++b;
            }
        }
    }


    template <class Pod>
    inline void pod_move(const Pod* b, const Pod* e, Pod* d)
    {
        using namespace std;
        memmove(d, b, (e - b) * sizeof(*b));
    }


    template <class Pod>
    inline Pod* pod_copy(const Pod* b, const Pod* e, Pod* d)
    {
        const std::size_t s = e - b;
        using namespace std;
        memcpy(d, b, s * sizeof(*b));
        return d + s;
    }


    mallocator() {}

    mallocator(const mallocator&) {}

    ~mallocator() {}


    pointer address(reference x) const { return &x; }

    const_pointer address(const_reference x) const 
    { 
        return x;
    }


    pointer allocate(size_type n, const_pointer = 0) 
    {
        using namespace std;
        void* p = malloc(n * sizeof(T));
        if (!p) boost::throw_exception(std::bad_alloc());
        return static_cast<pointer>(p);
    }


    void deallocate(pointer p, size_type) 
    { 
        using namespace std;
        free(p); 
    }


    size_type max_size() const 
    { 
        return static_cast<size_type>(-1) / sizeof(T);
    }


    void construct(pointer p, const value_type& x) 
    { 
        new(p) value_type(x); 
    }


    void destroy(pointer p) 
    { 
        p->~value_type(); 
    }


template <class T>
inline bool operator==(const mallocator<T>&, 
                       const mallocator<T>&) {
  return true;
}


template <class T>
inline bool operator!=(const mallocator<T>&, 
                       const mallocator<T>&) {
  return false;
}


template <class Allocator>
typename Allocator::pointer Reallocate(
    Allocator& alloc,
    typename Allocator::pointer p, 
    typename Allocator::size_type oldObjCount,
    typename Allocator::size_type newObjCount,
    void*)
{
    // @@@ not implemented
    return NULL;
}


template <class Allocator>
typename Allocator::pointer Reallocate(
    Allocator& alloc,
    typename Allocator::pointer p, 
    typename Allocator::size_type oldObjCount,
    typename Allocator::size_type newObjCount,
    mallocator<void>*)
{
    // @@@ not implemented
    return NULL;
}


    Storage& GetStorage()
    {
        BOOST_ASSERT(buf_[maxSmallString] == magic);
        Storage* p = reinterpret_cast<Storage*>(&buf_[0]);
        return *p;
    }


    const Storage& GetStorage() const
    {
        BOOST_ASSERT(buf_[maxSmallString] == magic);
        const Storage *p = reinterpret_cast<const Storage*>(&buf_[0]);
        return *p;
    }


    bool Small() const
    {
        return buf_[maxSmallString] != magic;
    }

  SmallStringOpt(const SmallStringOpt& s)
    {
        if (s.Small())
        {
            flex_string_details::pod_copy(
                s.buf_, 
                s.buf_ + s.size(), 
                buf_);
        }
        else
        {
            new(buf_) Storage(s.GetStorage());
        }
        buf_[maxSmallString] = s.buf_[maxSmallString];
    }


    SmallStringOpt(const allocator_type&)
    {
        buf_[maxSmallString] = maxSmallString;
    }


    SmallStringOpt(const value_type* s, size_type len, const allocator_type& a)
    {
        if (len <= maxSmallString)
        {
            flex_string_details::pod_copy(s, s + len, buf_);
            buf_[maxSmallString] = value_type(maxSmallString - len);
        }
        else
        {
            new(buf_) Storage(s, len, a);
            buf_[maxSmallString] = magic;
        }
    }


    SmallStringOpt(size_type len, value_type c, const allocator_type& a)
    {
        if (len <= maxSmallString)
        {
            flex_string_details::pod_fill(buf_, buf_ + len, c);
            buf_[maxSmallString] = value_type(maxSmallString - len);
        }
        else
        {
            new(buf_) Storage(len, c, a);
            buf_[maxSmallString] = magic;
        }
    }


    SmallStringOpt& operator=(const SmallStringOpt& rhs)
    {
        reserve(rhs.size());
        resize(0, 0);
        append(rhs.data(), rhs.size());
        return *this;
    }


    ~SmallStringOpt()
    {
        if (!Small()) GetStorage().~Storage();
    }


    iterator begin()
    {
        if (Small()) return buf_;
        return &*GetStorage().begin(); 
    }


    const_iterator begin() const
    {
        if (Small()) return buf_;
        return &*GetStorage().begin(); 
    }


    iterator end()
    {
        if (Small()) return buf_ + maxSmallString - buf_[maxSmallString];
        return &*GetStorage().end(); 
    }


    const_iterator end() const
    {
        if (Small()) return buf_ + maxSmallString - buf_[maxSmallString];
        return &*GetStorage().end(); 
    }


    size_type size() const
    {
        BOOST_ASSERT(!Small() || maxSmallString >= buf_[maxSmallString]);
        return Small() 
            ? maxSmallString - buf_[maxSmallString] 
            : GetStorage().size();
    }


    size_type max_size() const
    { return get_allocator().max_size(); }


    size_type capacity() const
    { return Small() ? maxSmallString : GetStorage().capacity(); }


    void reserve(size_type res_arg)
    {
        if (Small())
        {
            if (res_arg <= maxSmallString) return;
            SmallStringOpt temp(*this);
            this->~SmallStringOpt();
            new(buf_) Storage(temp.data(), temp.size(), 
                temp.get_allocator());
            buf_[maxSmallString] = magic;
            GetStorage().reserve(res_arg);
        }
        else
        {
            GetStorage().reserve(res_arg);
        }
        BOOST_ASSERT(capacity() >= res_arg);
    }


    void append(const value_type* s, size_type sz)
    {
        if (!Small())
        {
            GetStorage().append(s, sz);
        }
        else
        {
            // append to a small string
            const size_type neededCapacity = 
                maxSmallString - buf_[maxSmallString] + sz;

            if (maxSmallString < neededCapacity)
            {
                // need to change storage strategy
                allocator_type alloc;
                Storage temp(alloc);
                temp.reserve(neededCapacity);
                temp.append(buf_, maxSmallString - buf_[maxSmallString]);
                temp.append(s, sz);
                buf_[maxSmallString] = magic;
                new(buf_) Storage(temp.get_allocator());
                GetStorage().swap(temp);
            }
            else
            {
                flex_string_details::pod_move(s, s + sz, 
                    buf_ + maxSmallString - buf_[maxSmallString]);
                buf_[maxSmallString] -= value_type(sz);
            }
        }
    }


    template <class InputIterator>
    void append(InputIterator b, InputIterator e)
    {
        // @@@ todo: optimize this depending on iterator type
        for (; b != e; ++b)
        {
            *this += *b;
        }
    }


    void resize(size_type n, value_type c)
    {
        if (Small())
        {
            if (n > maxSmallString)
            {
                // Small string resized to big string
                SmallStringOpt temp(*this); // can't throw
                // 11-17-2001: correct exception safety bug
                Storage newString(temp.data(), temp.size(), 
                    temp.get_allocator());
                newString.resize(n, c);
                // We make the reasonable assumption that an empty Storage
                //     constructor won't throw
                this->~SmallStringOpt();
                new(&buf_[0]) Storage(temp.get_allocator());
                buf_[maxSmallString] = value_type(magic);
                GetStorage().swap(newString);
            }
            else
            {
                // Small string resized to small string
                // 11-17-2001: bug fix: terminating zero not copied
                size_type toFill = n > size() ? n - size() : 0;
                flex_string_details::pod_fill(end(), end() + toFill, c);
                buf_[maxSmallString] = value_type(maxSmallString - n);
            }
        }
        else
        {
            if (n > maxSmallString)
            {
                // Big string resized to big string
                GetStorage().resize(n, c);
            }
            else
            {
                // Big string resized to small string
                // 11-17=2001: bug fix in the BOOST_ASSERTion below
                BOOST_ASSERT(capacity() > n);
                SmallStringOpt newObj(data(), n, get_allocator());
                newObj.swap(*this);
            }
        }
    }


    void swap(SmallStringOpt& rhs)
    {
        if (Small())
        {
            if (rhs.Small())
            {
                // Small swapped with small
                std::swap_ranges(buf_, buf_ + maxSmallString + 1, 
                    rhs.buf_);
            }
            else
            {
                // Small swapped with big
                // Make a copy of myself - can't throw
                SmallStringOpt temp(*this);
                // Nuke myself
                this->~SmallStringOpt();
                // Make an empty storage for myself (likely won't throw)
                new(buf_) Storage(0, value_type(), rhs.get_allocator());
                buf_[maxSmallString] = magic;
                // Recurse to this same function
                swap(rhs);
                // Nuke rhs
                rhs.~SmallStringOpt();
                // Build the new small string into rhs
                new(&rhs) SmallStringOpt(temp);
            }
        }
        else
        {
            if (rhs.Small())
            {
                // Big swapped with small
                // Already implemented, recurse with reversed args
                rhs.swap(*this);
            }
            else
            {
                // Big swapped with big
                GetStorage().swap(rhs.GetStorage());
            }
        }
    }


    const value_type* c_str() const
    { 
        if (!Small()) return GetStorage().c_str(); 
        buf_[maxSmallString - buf_[maxSmallString]] = value_type();
        return buf_;
    }


    const value_type* data() const
    { return Small() ? buf_ : GetStorage().data(); }

    
    allocator_type get_allocator() const
    { return allocator_type(); }


    Storage& Data() const
    { 
        Storage* p = reinterpret_cast<Storage*>(&buf_[0]);
        return *p;
    }


    RefCountType GetRefs() const
    {
        const Storage& d = Data();
        BOOST_ASSERT(d.size() > 0);
        BOOST_ASSERT(static_cast<RefCountType>(*d.begin()) != 0);
        return *d.begin();
    }

    
    RefCountType& Refs()
    {
        Storage& d = Data();
        BOOST_ASSERT(d.size() > 0);
        return reinterpret_cast<RefCountType&>(*d.begin());
    }

    
    void MakeUnique() const
    {
        BOOST_ASSERT(GetRefs() >= 1);
        if (GetRefs() == 1) return;

        union
        {
            char buf_[sizeof(Storage)];
            Align align_;
        } temp;

        --(*Data().begin()); // decrement the use count of the remaining object

        Storage* p = reinterpret_cast<Storage*>(&temp.buf_[0]);
        new(buf_) Storage(
            *new(p) Storage(Data()), 
            flex_string_details::Shallow());
        *Data().begin() = 1;
    }

    CowString(const CowString& s)
    {
        if (s.GetRefs() == (std::numeric_limits<RefCountType>::max)())
        {
            // must make a brand new copy
            new(buf_) Storage(s.Data()); // non shallow
            Refs() = 1;
        }
        else
        {
            new(buf_) Storage(s.Data(), flex_string_details::Shallow());
            ++Refs();
        }
        BOOST_ASSERT(Data().size() > 0);
    }

    
    CowString(const allocator_type& a)
    {
        new(buf_) Storage(1, 1, a);
    }

    
    CowString(const E* s, size_type len, const allocator_type& a)
    {
        // Warning - MSVC's debugger has trouble tracing through the code below.
        // It seems to be a const-correctness issue
        //
        new(buf_) Storage(a);
        Data().reserve(len + 1);
        Data().resize(1, 1);
        Data().append(s, s + len);
    }


    CowString(size_type len, E c, const allocator_type& a)
    {
        new(buf_) Storage(len + 1, c, a);
        Refs() = 1;
    }

    
    CowString& operator=(const CowString& rhs)
    {
//        CowString(rhs).swap(*this);
        if (--Refs() == 0) 
            Data().~Storage();
        if (rhs.GetRefs() == (std::numeric_limits<RefCountType>::max)())
        {
            // must make a brand new copy
            new(buf_) Storage(rhs.Data()); // non shallow
            Refs() = 1;
        }
        else
        {
            new(buf_) Storage(rhs.Data(), flex_string_details::Shallow());
            ++Refs();
        }
        BOOST_ASSERT(Data().size() > 0);
        return *this;
    }


    ~CowString()
    {
        BOOST_ASSERT(Data().size() > 0);
        if (--Refs() == 0) 
            Data().~Storage();
    }


    iterator begin()
    {
        BOOST_ASSERT(Data().size() > 0);
        MakeUnique();
        return Data().begin() + 1; 
    }

    
    const_iterator begin() const
    {
        BOOST_ASSERT(Data().size() > 0);
        return Data().begin() + 1; 
    }

    
    iterator end()
    {
        MakeUnique();
        return Data().end(); 
    }

    
    const_iterator end() const
    {
        return Data().end(); 
    }

    
    size_type size() const
    {
        BOOST_ASSERT(Data().size() > 0);
        return Data().size() - 1;
    }


    size_type max_size() const
    { 
        BOOST_ASSERT(Data().max_size() > 0);
        return Data().max_size() - 1;
    }


    size_type capacity() const
    { 
        BOOST_ASSERT(Data().capacity() > 0);
        return Data().capacity() - 1;
    }


    void resize(size_type n, E c)
    {
        BOOST_ASSERT(Data().size() > 0);
        MakeUnique();
        Data().resize(n + 1, c);
    }


    template <class FwdIterator>
    void append(FwdIterator b, FwdIterator e)
    {
        MakeUnique();
        Data().append(b, e);
    }

    
    void reserve(size_type res_arg)
    {
        if (capacity() > res_arg) return;
        MakeUnique();
        Data().reserve(res_arg + 1);
    }

    
    void swap(CowString& rhs)
    {
        Data().swap(rhs.Data());
    }

    
    const E* c_str() const
    { 
        BOOST_ASSERT(Data().size() > 0);
        return Data().c_str() + 1;
    }


    const E* data() const
    { 
        BOOST_ASSERT(Data().size() > 0);
        return Data().data() + 1;
    }

    
    allocator_type get_allocator() const
    { 
        return Data().get_allocator();
    }

        time_conversion_grammar() : fYearIsCorrected(false)
        {
            using namespace std;        // some systems have memset in std
            memset (&time_stamp, 0, sizeof(tm));
            BOOST_SPIRIT_DEBUG_TRACE_RULE_NAME(*this, "time_conversion_grammar",
                TRACE_CPP_TIME_CONVERSION);
        }

        
            definition(time_conversion_grammar const &self)
            {
                using boost::spirit::classic::int_p;
                using boost::spirit::classic::add;
                
            char const *m[] = {
                    "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
                };

                for (int i = 0; i < 12; ++i)
                    add (month, m[i], i);

                time_rule       // expected format is 'Dec 29 2001 11:23:59'
                    =   month[spirit_assign_actor(self.time_stamp.tm_mon)]  
                    >>  int_p[spirit_assign_actor(self.time_stamp.tm_mday)]    
                    >>  int_p[spirit_assign_actor(self.time_stamp.tm_year)]
                    >>  int_p[spirit_assign_actor(self.time_stamp.tm_hour)] >> ':' 
                    >>  int_p[spirit_assign_actor(self.time_stamp.tm_min)] >> ':'
                    >>  int_p[spirit_assign_actor(self.time_stamp.tm_sec)]
                    ;
                    
                BOOST_SPIRIT_DEBUG_TRACE_RULE(time_rule, TRACE_CPP_TIME_CONVERSION);
            }

    
        void correct_year() 
        { 
            if (!fYearIsCorrected) {
                time_stamp.tm_year -= 1900;
                fYearIsCorrected = true;
            }
        }

        time_conversion_helper(char const *act_time) : compile_time(0)
        {
            using namespace boost::spirit::classic;
            
        time_conversion_grammar g;
        parse_info<> pi = parse (act_time, g, space_p);
        
            if (pi.hit) {
                g.correct_year();
                compile_time = mktime(&g.time_stamp);
            }
            BOOST_ASSERT(0 != compile_time);        
        }


        time_t get_time() const { return compile_time; }


    file_position()
    :   file(), line(1), column(1)
    {}

    string_type const &get_file() const { return file; }

    std::size_t get_line() const { return line; }

    std::size_t get_column() const { return column; }


    void set_file(string_type const &file_) 
    { 
        file = file_; 
    }

    void set_line(std::size_t line_) { line = line_; }

    void set_column(std::size_t column_) { column = column_; }


template <typename StringT>
bool operator== (file_position<StringT> const &lhs, 
    file_position<StringT> const &rhs)
{
    return lhs.get_column() == rhs.get_column() && 
        lhs.get_line() == rhs.get_line() && lhs.get_file() == rhs.get_file();
}


template <typename StringT>
inline std::ostream &
operator<< (std::ostream &o, file_position<StringT> const &pos)
{
    o << pos.get_file() << ":" << pos.get_line() << ":"  << pos.get_column();
    return o;
}


    position_iterator()
    {
    }


    position_iterator(IteratorT const &begin, IteratorT const &end,
            PositionT const &pos)
    :   base_type(begin, end, pos)
    {
    }

        position_policy()
            : m_CharsPerTab(4)
        {}


        void next_line(boost::wave::util::file_position_type &pos)
        {
            pos.set_line(pos.get_line() + 1);
            pos.set_column(1);
        }


        void set_tab_chars(unsigned int chars)
        {
            m_CharsPerTab = chars;
        }


        void next_char(boost::wave::util::file_position_type &pos)
        {
            pos.set_column(pos.get_column() + 1);
        }


        void tabulation(boost::wave::util::file_position_type &pos)   
        {
            pos.set_column(pos.get_column() + m_CharsPerTab - 
                (pos.get_column() - 1) % m_CharsPerTab);
        }

    inline boost::filesystem::path initial_path()
    {
        return boost::filesystem::initial_path();
    }


    inline boost::filesystem::path current_path()
    {
        return boost::filesystem::current_path();
    }


    template <typename String>
    inline boost::filesystem::path create_path(String const& p)
    {
#if BOOST_FILESYSTEM_VERSION >= 3
        return boost::filesystem::path(p);
#else
        return boost::filesystem::path(p, boost::filesystem::native);
#endif
    }

            Data(FunctorT const &ftor_) 
            :   ftor(ftor_), was_initialized(false)
            {}

        inner()
        :   data(0)
        {}


        inner(FunctorT const &x)
        :   data(new Data(x))
        {}


        inner(inner const &x)
        :   data(x.data)
        {}


        void destroy()
        {
            delete data;
            data = 0;
        }


        bool same_input(inner const &x) const
        {
            return data == x.data;
        }


        void swap(inner &x)
        {
            boost::spirit::classic::impl::mp_swap(data, x.data);
        }


        void ensure_initialized() const
        {
            if (data && !data->was_initialized) {
                data->curtok = (data->ftor)();    // get the first token
                data->was_initialized = true;
            }
        }

        reference get_input() const
        {
            ensure_initialized();
            return data->curtok;
        }


        void advance_input()
        {
            BOOST_ASSERT(0 != data);
            data->curtok = (data->ftor)();
            data->was_initialized = true;
        }


        bool input_at_eof() const
        {
            ensure_initialized();
            return !data || data->curtok == data->ftor.eof;
        }


        FunctorT& get_functor() const
        {
            BOOST_ASSERT(0 != data);
            return data->ftor;
        }

    macromap(ContextT &ctx_)
    :   current_macros(0), defined_macros(new defined_macros_type(1)),
        main_pos("", 0), ctx(ctx_), macro_uid(1)
    {
        current_macros = defined_macros.get();
    }

    ~macromap() {}


    position_type &get_main_pos() { return main_pos; }

    position_type const& get_main_pos() const { return main_pos; }


    name_iterator begin()
        { return defined_macros_type::make_iterator(current_macros->begin()); }

    name_iterator end()
        { return defined_macros_type::make_iterator(current_macros->end()); }

    const_name_iterator begin() const
        { return defined_macros_type::make_iterator(current_macros->begin()); }

    const_name_iterator end() const
        { return defined_macros_type::make_iterator(current_macros->end()); }

template <typename IteratorT>
inline bool
macromap<ContextT>::is_defined(IteratorT const &begin,
    IteratorT const &end) const
{
// in normal mode the name under inspection should consist of an identifier
// only
token_id id = token_id(*begin);

    if (T_IDENTIFIER != id &&
        !IS_CATEGORY(id, KeywordTokenType) &&
        !IS_EXTCATEGORY(id, OperatorTokenType|AltExtTokenType) &&
        !IS_CATEGORY(id, BoolLiteralTokenType))
    {
        std::string msg(impl::get_full_name(begin, end));
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, invalid_macroname,
            msg.c_str(), main_pos);
        return false;
    }

IteratorT it = begin;
string_type name ((*it).get_value());
typename defined_macros_type::iterator cit;

    if (++it != end) {
    // there should be only one token as the inspected name
        std::string msg(impl::get_full_name(begin, end));
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, invalid_macroname,
            msg.c_str(), main_pos);
        return false;
    }
    return is_defined(name, cit, 0);
}

template <typename ContextT>
inline bool
macromap<ContextT>::is_defined(string_type const &str) const
{
    typename defined_macros_type::iterator cit;
    return is_defined(str, cit, 0);
}

template <typename ContextT>
inline bool
macromap<ContextT>::remove_macro(string_type const &name,
    position_type const& pos, bool even_predefined)
{
    typename defined_macros_type::iterator it = current_macros->find(name);

    if (it != current_macros->end()) {
        if ((*it).second->is_predefined) {
            if (!even_predefined || impl::is_special_macroname(name)) {
                BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                    bad_undefine_statement, name.c_str(), main_pos);
                return false;
            }
        }
        current_macros->erase(it);

    // call the context supplied preprocessing hook function
    token_type tok(T_IDENTIFIER, name, pos);

#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
        ctx.get_hooks().undefined_macro(tok);
#else
        ctx.get_hooks().undefined_macro(ctx.derived(), tok);
#endif
        return true;
    }
    else if (impl::is_special_macroname(name)) {
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_undefine_statement,
            name.c_str(), pos);
    }
    return false;       // macro was not defined
}

template <typename IteratorT, typename ContainerT>
inline typename ContextT::token_type const &
macromap<ContextT>::expand_tokensequence(IteratorT &first,
    IteratorT const &last, ContainerT &pending, ContainerT &expanded,
    bool& seen_newline, bool expand_operator_defined)
{
    typedef impl::gen_unput_queue_iterator<IteratorT, token_type, ContainerT>
        gen_type;
    typedef typename gen_type::return_type iterator_type;

    iterator_type first_it = gen_type::generate(expanded, first);
    iterator_type last_it = gen_type::generate(last);

on_exit::assign<IteratorT, iterator_type> on_exit(first, first_it);

    return expand_tokensequence_worker(pending, first_it, last_it,
        seen_newline, expand_operator_defined);
}

template <typename IteratorT, typename ContainerT>
inline void
macromap<ContextT>::expand_whole_tokensequence(ContainerT &expanded,
    IteratorT &first, IteratorT const &last,
    bool expand_operator_defined)
{
    typedef impl::gen_unput_queue_iterator<IteratorT, token_type, ContainerT>
        gen_type;
    typedef typename gen_type::return_type iterator_type;

    ContainerT empty;
    iterator_type first_it = gen_type::generate(empty, first);
    iterator_type last_it = gen_type::generate(last);

    on_exit::assign<IteratorT, iterator_type> on_exit(first, first_it);
    ContainerT pending_queue;
    bool seen_newline;

    while (!pending_queue.empty() || first_it != last_it) {
        expanded.push_back(
            expand_tokensequence_worker(pending_queue, first_it,
                    last_it, seen_newline, expand_operator_defined)
        );
    }

// should have returned all expanded tokens
    BOOST_ASSERT(pending_queue.empty()/* && unput_queue.empty()*/);
}

template <typename ContainerT>
inline bool
macromap<ContextT>::expand_predefined_macro(token_type const &curr_token,
    ContainerT &expanded)
{
    using namespace boost::wave;

string_type const &value = curr_token.get_value();

    if (value.size() < 8 || '_' != value[0] || '_' != value[1])
        return false;       // quick check failed

    if (value == "__LINE__") {
    // expand the __LINE__ macro
    char buffer[22];    // 21 bytes holds all NUL-terminated unsigned 64-bit numbers

        using namespace std;    // for some systems sprintf is in namespace std
        sprintf(buffer, "%ld", main_pos.get_line());
        expanded.push_back(token_type(T_INTLIT, buffer, curr_token.get_position()));
        return true;
    }
    else if (value == "__FILE__") {
    // expand the __FILE__ macro
        namespace fs = boost::filesystem;

    std::string file("\"");
    fs::path filename(wave::util::create_path(main_pos.get_file().c_str()));

        using boost::wave::util::impl::escape_lit;
        file += escape_lit(wave::util::native_file_string(filename)) + "\"";
        expanded.push_back(token_type(T_STRINGLIT, file.c_str(),
            curr_token.get_position()));
        return true;
    }
    else if (value == "__INCLUDE_LEVEL__") {
    // expand the __INCLUDE_LEVEL__ macro
    char buffer[22];    // 21 bytes holds all NUL-terminated unsigned 64-bit numbers

        using namespace std;    // for some systems sprintf is in namespace std
        sprintf(buffer, "%d", (int)ctx.get_iteration_depth());
        expanded.push_back(token_type(T_INTLIT, buffer, curr_token.get_position()));
        return true;
    }
    return false;   // no predefined token
}

template <typename IteratorT, typename ContainerT>
inline typename ContextT::token_type const &
macromap<ContextT>::resolve_defined(IteratorT &first,
    IteratorT const &last, ContainerT &pending)
{
    using namespace boost::wave;
    using namespace boost::wave::grammars;

ContainerT result;
IteratorT start = first;
boost::spirit::classic::parse_info<IteratorT> hit =
    defined_grammar_gen<typename ContextT::lexer_type>::
        parse_operator_defined(start, last, result);

    if (!hit.hit) {
        string_type msg ("defined(): ");
        msg = msg + util::impl::as_string<string_type>(first, last);
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, ill_formed_expression,
            msg.c_str(), main_pos);

    // insert a dummy token
        pending.push_back(token_type(T_INTLIT, "0", main_pos));
    }
    else {
        impl::assign_iterator<IteratorT>::do_(first, hit.stop);

    // insert a token, which reflects the outcome
        pending.push_back(token_type(T_INTLIT,
            is_defined(result.begin(), result.end()) ? "1" : "0",
            main_pos));
    }

on_exit::pop_front<definition_container_type> pop_front_token(pending);

    return act_token = pending.front();
}

template <typename IteratorT, typename ContainerT>
inline bool
macromap<ContextT>::resolve_operator_pragma(IteratorT &first,
    IteratorT const &last, ContainerT &pending, bool& seen_newline)
{
// isolate the parameter of the operator _Pragma
    token_type pragma_token = *first;

    if (!impl::skip_to_token(ctx, first, last, T_LEFTPAREN, seen_newline)) {
    // illformed operator _Pragma
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, ill_formed_expression,
            "operator _Pragma()", pragma_token.get_position());
        return false;
    }

    std::vector<ContainerT> arguments;
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    typename std::vector<ContainerT>::size_type count_args =
        collect_arguments (pragma_token, arguments, first, last, 1, seen_newline);
#else
    IteratorT endparen = first;
    typename std::vector<ContainerT>::size_type count_args =
        collect_arguments (pragma_token, arguments, first, endparen, last, 1,
            seen_newline);
#endif

// verify the parameter count
    if (pragma_token.get_position().get_file().empty())
        pragma_token.set_position(act_token.get_position());

    if (count_args < 1 || arguments.size() < 1) {
    // too few macro arguments
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, too_few_macroarguments,
            pragma_token.get_value().c_str(), pragma_token.get_position());
        return false;
    }
    if (count_args > 1 || arguments.size() > 1) {
    // too many macro arguments
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, too_many_macroarguments,
            pragma_token.get_value().c_str(), pragma_token.get_position());
        return false;
    }

// preprocess the pragma token body
    typedef typename std::vector<ContainerT>::value_type::iterator
        argument_iterator_type;

    ContainerT expanded;
    argument_iterator_type begin_it = arguments[0].begin();
    argument_iterator_type end_it = arguments[0].end();
    expand_whole_tokensequence(expanded, begin_it, end_it, false);

// un-escape the parameter of the operator _Pragma
    typedef typename token_type::string_type string_type;

    string_type pragma_cmd;
    typename ContainerT::const_iterator end_exp = expanded.end();
    for (typename ContainerT::const_iterator it_exp = expanded.begin();
         it_exp != end_exp; ++it_exp)
    {
        if (T_EOF == token_id(*it_exp))
            break;
        if (IS_CATEGORY(*it_exp, WhiteSpaceTokenType))
            continue;

        if (T_STRINGLIT != token_id(*it_exp)) {
        // ill formed operator _Pragma
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                ill_formed_pragma_option, "_Pragma",
                pragma_token.get_position());
            return false;
        }
        if (pragma_cmd.size() > 0) {
        // there should be exactly one string literal (string literals are to
        // be concatenated at translation phase 6, but _Pragma operators are
        // to be executed at translation phase 4)
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                ill_formed_pragma_option, "_Pragma",
                pragma_token.get_position());
            return false;
        }

    // remove the '\"' and concat all given string literal-values
        string_type token_str = (*it_exp).get_value();
        pragma_cmd += token_str.substr(1, token_str.size() - 2);
    }
    string_type pragma_cmd_unesc = impl::unescape_lit(pragma_cmd);

// tokenize the pragma body
    typedef typename ContextT::lexer_type lexer_type;

    ContainerT pragma;
    std::string pragma_cmd_str(pragma_cmd_unesc.c_str());
    lexer_type it = lexer_type(pragma_cmd_str.begin(), pragma_cmd_str.end(),
        pragma_token.get_position(), ctx.get_language());
    lexer_type end = lexer_type();
    for (/**/; it != end; ++it)
        pragma.push_back(*it);

// analyze the preprocessed token sequence and eventually dispatch to the
// associated action
    if (interpret_pragma(ctx, pragma_token, pragma.begin(), pragma.end(),
        pending))
    {
        return true;    // successfully recognized a wave specific pragma
    }

// unknown pragma token sequence, push it back and return to the caller
    pending.push_front(token_type(T_SPACE, " ", pragma_token.get_position()));
    pending.push_front(token_type(T_RIGHTPAREN, ")", pragma_token.get_position()));
    pending.push_front(token_type(T_STRINGLIT, string_type("\"") + pragma_cmd + "\"",
        pragma_token.get_position()));
    pending.push_front(token_type(T_LEFTPAREN, "(", pragma_token.get_position()));
    pending.push_front(pragma_token);
    return false;
}

template <typename ContainerT>
inline bool
macromap<ContextT>::is_valid_concat(string_type new_value,
    position_type const &pos, ContainerT &rescanned)
{
// re-tokenize the newly generated string
    typedef typename ContextT::lexer_type lexer_type;

    std::string value_to_test(new_value.c_str());

    boost::wave::language_support lang =
        boost::wave::enable_prefer_pp_numbers(ctx.get_language());
    lang = boost::wave::enable_single_line(lang);

    lexer_type it = lexer_type(value_to_test.begin(), value_to_test.end(), pos,
        lang);
    lexer_type end = lexer_type();
    for (/**/; it != end && T_EOF != token_id(*it); ++it)
    {
        // as of Wave V2.0.7 pasting of tokens is valid only if the resulting
        // tokens are pp_tokens (as mandated by C++11)
        if (!is_pp_token(*it))
            return false;
        rescanned.push_back(*it);
    }

#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
    if (boost::wave::need_variadics(ctx.get_language()))
        return true;       // in variadics mode token pasting is well defined
#endif

// test if the newly generated token sequence contains more than 1 token
    return 1 == rescanned.size();
}

template <typename Context>
inline void report_invalid_concatenation(Context& ctx,
    typename Context::token_type const& prev,
    typename Context::token_type const& next,
    typename Context::position_type const& main_pos)
{
typename Context::string_type error_string("\"");

    error_string += prev.get_value();
    error_string += "\" and \"";
    error_string += next.get_value();
    error_string += "\"";
    BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, invalid_concat,
        error_string.c_str(), main_pos);
}

template <typename ContainerT>
inline bool
macromap<ContextT>::concat_tokensequence(ContainerT &expanded)
{
    using namespace boost::wave;
    typedef typename ContainerT::iterator iterator_type;

    iterator_type end = expanded.end();
    iterator_type prev = end;
    for (iterator_type it = expanded.begin(); it != end; /**/)
    {
        if (T_POUND_POUND == BASE_TOKEN(token_id(*it))) {
        iterator_type next = it;

            ++next;
            if (prev == end || next == end) {
            // error, '##' should be in between two tokens
                BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                    ill_formed_operator, "concat ('##')", main_pos);
                return false;
            }

        // replace prev##next with the concatenated value, skip whitespace
        // before and after the '##' operator
            while (IS_CATEGORY(*next, WhiteSpaceTokenType)) {
                ++next;
                if (next == end) {
                // error, '##' should be in between two tokens
                    BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                        ill_formed_operator, "concat ('##')", main_pos);
                    return false;
                }
            }

#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
            if (boost::wave::need_variadics(ctx.get_language())) {
                if (T_PLACEMARKER == token_id(*next)) {
                // remove the '##' and the next tokens from the sequence
                iterator_type first_to_delete = prev;

                    expanded.erase(++first_to_delete, ++next);
                    it = next;
                    continue;
                }
                else if (T_PLACEMARKER == token_id(*prev)) {
                // remove the '##' and the next tokens from the sequence
                iterator_type first_to_delete = prev;

                    *prev = *next;
                    expanded.erase(++first_to_delete, ++next);
                    it = next;
                    continue;
                }
            }
#endif // BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0

        // test if the concat operator has to concatenate two unrelated
        // tokens i.e. the result yields more then one token
        string_type concat_result;
        ContainerT rescanned;

            concat_result = ((*prev).get_value() + (*next).get_value());

        // analyze the validity of the concatenation result
            if (!is_valid_concat(concat_result, (*prev).get_position(),
                    rescanned) &&
                !IS_CATEGORY(*prev, WhiteSpaceTokenType) &&
                !IS_CATEGORY(*next, WhiteSpaceTokenType))
            {
                report_invalid_concatenation(ctx, *prev, *next, main_pos);
                return false;
            }

#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
            if (boost::wave::need_variadics(ctx.get_language())) {
            // remove the prev, '##' and the next tokens from the sequence
                expanded.erase(prev, ++next);       // remove not needed tokens

            // some stl implementations clear() the container if we erased all
            // the elements, which orphans all iterators. we re-initialize these
            // here
                if (expanded.empty())
                    end = next = expanded.end();

            // replace the old token (pointed to by *prev) with the re-tokenized
            // sequence
                expanded.splice(next, rescanned);

            // the last token of the inserted sequence is the new previous
                prev = next;
                if (next != expanded.end())
                    --prev;
            }
            else
#endif // BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
            {
            // we leave the token_id unchanged, but unmark the token as
            // disabled, if appropriate
                (*prev).set_value(concat_result);
                if (T_NONREPLACABLE_IDENTIFIER == token_id(*prev))
                    (*prev).set_token_id(T_IDENTIFIER);

            // remove the '##' and the next tokens from the sequence
            iterator_type first_to_delete = prev;

                expanded.erase(++first_to_delete, ++next);
            }
            it = next;
            continue;
        }

    // save last non-whitespace token position
        if (!IS_CATEGORY(*it, WhiteSpaceTokenType))
            prev = it;

        ++it;           // next token, please
    }
    return true;
}

template <typename ContextT>
inline void
macromap<ContextT>::reset_macromap()
{
    current_macros->clear();
    predef.reset();
    act_token = token_type();
}

template <
    typename ContextT, typename ParseNodeT, typename TokenT,
    typename PositionT
>
inline bool
retrieve_macroname(ContextT& ctx, ParseNodeT const &node,
    boost::spirit::classic::parser_id id, TokenT &macroname, PositionT& act_pos,
    bool update_position)
{
ParseNodeT const *name_node = 0;

    using boost::spirit::classic::find_node;
    if (!find_node(node, id, &name_node))
    {
        // ill formed define statement (unexpected, should not happen)
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_define_statement,
            "bad parse tree (unexpected)", act_pos);
        return false;
    }

typename ParseNodeT::children_t const &children = name_node->children;

    if (0 == children.size() ||
        children.front().value.begin() == children.front().value.end())
    {
        // ill formed define statement (unexpected, should not happen)
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_define_statement,
            "bad parse tree (unexpected)", act_pos);
        return false;
    }

// retrieve the macro name
    macroname = *children.front().value.begin();
    if (update_position) {
        macroname.set_position(act_pos);
        act_pos.set_column(act_pos.get_column() + macroname.get_value().size());
    }
    return true;
}

template <typename ParseNodeT, typename ContainerT, typename PositionT>
inline bool
retrieve_macrodefinition(
    ParseNodeT const &node, boost::spirit::classic::parser_id id,
    ContainerT &macrodefinition, PositionT& act_pos, bool update_position)
{
    using namespace boost::wave;
    typedef typename ParseNodeT::const_tree_iterator const_tree_iterator;

// find macro parameters/macro definition inside the parse tree
std::pair<const_tree_iterator, const_tree_iterator> nodes;

    using boost::spirit::classic::get_node_range;
    if (get_node_range(node, id, nodes)) {
    // copy all parameters to the supplied container
        typename ContainerT::iterator last_nonwhite = macrodefinition.end();
        const_tree_iterator end = nodes.second;

        for (const_tree_iterator cit = nodes.first; cit != end; ++cit) {
            if ((*cit).value.begin() != (*cit).value.end()) {
            typename ContainerT::iterator inserted = macrodefinition.insert(
                macrodefinition.end(), *(*cit).value.begin());

                if (!IS_CATEGORY(macrodefinition.back(), WhiteSpaceTokenType) &&
                    T_NEWLINE != token_id(macrodefinition.back()) &&
                    T_EOF != token_id(macrodefinition.back()))
                {
                    last_nonwhite = inserted;
                }

                if (update_position) {
                    (*inserted).set_position(act_pos);
                    act_pos.set_column(
                        act_pos.get_column() + (*inserted).get_value().size());
                }
            }
        }

    // trim trailing whitespace (leading whitespace is trimmed by the grammar)
        if (last_nonwhite != macrodefinition.end()) {
            if (update_position) {
                act_pos.set_column((*last_nonwhite).get_position().get_column() +
                    (*last_nonwhite).get_value().size());
            }
            macrodefinition.erase(++last_nonwhite, macrodefinition.end());
        }
        return true;
    }
    return false;
}

    template <typename IteratorT>
    pp_iterator_functor(ContextT &ctx_, IteratorT const &first_,
            IteratorT const &last_, typename ContextT::position_type const &pos_)
    :   ctx(ctx_),
        iter_ctx(new base_iteration_context_type(ctx,
                lexer_type(first_, last_, pos_,
                    boost::wave::enable_prefer_pp_numbers(ctx.get_language())),
                lexer_type(),
                pos_.get_file().c_str()
            )),
        seen_newline(true), skipped_newline(false),
        must_emit_line_directive(false), act_pos(ctx_.get_main_pos()),
        whitespace(boost::wave::need_insert_whitespace(ctx.get_language()))
    {
        act_pos.set_file(pos_.get_file());
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
        ctx_.set_current_filename(pos_.get_file().c_str());
#endif
        iter_ctx->emitted_lines = (unsigned int)(-1);   // force #line directive
    }

    result_type const &current_token() const { return act_token; }

template <typename ContextT>
inline bool
pp_iterator_functor<ContextT>::returned_from_include()
{
    if (iter_ctx->first == iter_ctx->last && ctx.get_iteration_depth() > 0) {
    // call the include policy trace function
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
        ctx.get_hooks().returning_from_include_file();
#else
        ctx.get_hooks().returning_from_include_file(ctx.derived());
#endif

    // restore the previous iteration context after finishing the preprocessing
    // of the included file
        BOOST_WAVE_STRINGTYPE oldfile = iter_ctx->real_filename;
        position_type old_pos (act_pos);

    // if this file has include guards handle it as if it had a #pragma once
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
        if (need_include_guard_detection(ctx.get_language())) {
            std::string guard_name;
            if (iter_ctx->first.has_include_guards(guard_name))
                ctx.add_pragma_once_header(ctx.get_current_filename(), guard_name);
        }
#endif
        iter_ctx = ctx.pop_iteration_context();

        must_emit_line_directive = true;
        iter_ctx->emitted_lines = (unsigned int)(-1);   // force #line directive
        seen_newline = true;

    // restore current file position
        act_pos.set_file(iter_ctx->filename);
        act_pos.set_line(iter_ctx->line);
        act_pos.set_column(0);

    // restore the actual current file and directory
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
        namespace fs = boost::filesystem;
        fs::path rfp(wave::util::create_path(iter_ctx->real_filename.c_str()));
        std::string real_filename(rfp.string());
        ctx.set_current_filename(real_filename.c_str());
#endif
        ctx.set_current_directory(iter_ctx->real_filename.c_str());
        ctx.set_current_relative_filename(iter_ctx->real_relative_filename.c_str());

    // ensure the integrity of the #if/#endif stack
    // report unbalanced #if/#endif now to make it possible to recover properly
        if (iter_ctx->if_block_depth != ctx.get_if_block_depth()) {
            using boost::wave::util::impl::escape_lit;
            BOOST_WAVE_STRINGTYPE msg(escape_lit(oldfile));
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, unbalanced_if_endif,
                msg.c_str(), old_pos);
        }
        return true;
    }
    return false;
}

    template <typename ContextT>
    bool consider_emitting_line_directive(ContextT const& ctx, token_id id)
    {
        if (need_preserve_comments(ctx.get_language()))
        {
            if (!IS_CATEGORY(id, EOLTokenType) && !IS_CATEGORY(id, EOFTokenType))
            {
                return true;
            }
        }
        if (!IS_CATEGORY(id, WhiteSpaceTokenType) &&
            !IS_CATEGORY(id, EOLTokenType) && !IS_CATEGORY(id, EOFTokenType))
        {
            return true;
        }
        return false;
    }


template <typename ContextT>
inline typename pp_iterator_functor<ContextT>::result_type const &
pp_iterator_functor<ContextT>::operator()()
{
    using namespace boost::wave;

    // make sure the cwd has been initialized
    ctx.init_context();

    // loop over skip able whitespace until something significant is found
    bool was_seen_newline = seen_newline;
    bool was_skipped_newline = skipped_newline;
    token_id id = T_UNKNOWN;

    try {   // catch lexer exceptions
        do {
            if (skipped_newline) {
                was_skipped_newline = true;
                skipped_newline = false;
            }

        // get_next_token assigns result to act_token member
            get_next_token();

        // if comments shouldn't be preserved replace them with newlines
            id = token_id(act_token);
            if (!need_preserve_comments(ctx.get_language()) &&
                (T_CPPCOMMENT == id || context_policies::util::ccomment_has_newline(act_token)))
            {
                act_token.set_token_id(id = T_NEWLINE);
                act_token.set_value("\n");
            }

            if (IS_CATEGORY(id, EOLTokenType))
                seen_newline = true;

        } while (ctx.get_hooks().may_skip_whitespace(ctx.derived(), act_token, skipped_newline));
    }
    catch (boost::wave::cpplexer::lexing_exception const& e) {
    // dispatch any lexer exceptions to the context hook function
        ctx.get_hooks().throw_exception(ctx.derived(), e);
        return act_token;
    }

// restore the accumulated skipped_newline state for next invocation
    if (was_skipped_newline)
        skipped_newline = true;

// if there were skipped any newlines, we must emit a #line directive
    if ((must_emit_line_directive || (was_seen_newline && skipped_newline)) &&
        impl::consider_emitting_line_directive(ctx, id))
    {
    // must emit a #line directive
        if (need_emit_line_directives(ctx.get_language()) && emit_line_directive())
        {
            skipped_newline = false;
            ctx.get_hooks().may_skip_whitespace(ctx.derived(), act_token, skipped_newline);     // feed ws eater FSM
            id = token_id(act_token);
        }
    }

// cleanup of certain tokens required
    seen_newline = false;
    switch (static_cast<unsigned int>(id)) {
    case T_NONREPLACABLE_IDENTIFIER:
        act_token.set_token_id(id = T_IDENTIFIER);
        break;

    case T_GENERATEDNEWLINE:  // was generated by emit_line_directive()
        act_token.set_token_id(id = T_NEWLINE);
        ++iter_ctx->emitted_lines;
        seen_newline = true;
        break;

    case T_NEWLINE:
    case T_CPPCOMMENT:
        seen_newline = true;
        ++iter_ctx->emitted_lines;
        break;

#if BOOST_WAVE_SUPPORT_CPP0X != 0
    case T_RAWSTRINGLIT:
        iter_ctx->emitted_lines +=
            context_policies::util::rawstring_count_newlines(act_token);
        break;
#endif

    case T_CCOMMENT:          // will come here only if whitespace is preserved
        iter_ctx->emitted_lines +=
            context_policies::util::ccomment_count_newlines(act_token);
        break;

    case T_PP_NUMBER:        // re-tokenize the pp-number
        {
            token_sequence_type rescanned;

            std::string pp_number(
                util::to_string<std::string>(act_token.get_value()));

            lexer_type it = lexer_type(pp_number.begin(),
                pp_number.end(), act_token.get_position(),
                ctx.get_language());
            lexer_type end = lexer_type();

            for (/**/; it != end && T_EOF != token_id(*it); ++it)
                rescanned.push_back(*it);

            pending_queue.splice(pending_queue.begin(), rescanned);
            act_token = pending_queue.front();
            id = token_id(act_token);
            pending_queue.pop_front();
        }
        break;

    case T_EOF:
        seen_newline = true;
        break;

    default:    // make sure whitespace at line begin keeps seen_newline status
        if (IS_CATEGORY(id, WhiteSpaceTokenType))
            seen_newline = was_seen_newline;
        break;
    }

    if (whitespace.must_insert(id, act_token.get_value())) {
    // must insert some whitespace into the output stream to avoid adjacent
    // tokens, which would form different (and wrong) tokens
        whitespace.shift_tokens(T_SPACE);
        pending_queue.push_front(act_token);        // push this token back
        return act_token = result_type(T_SPACE,
            typename result_type::string_type(" "),
            act_token.get_position());
    }
    whitespace.shift_tokens(id);
    return ctx.get_hooks().generated_token(ctx.derived(), act_token);
}

template <typename ContextT>
inline typename pp_iterator_functor<ContextT>::result_type const &
pp_iterator_functor<ContextT>::get_next_token()
{
    using namespace boost::wave;

// if there is something in the unput_queue, then return the next token from
// there (all tokens in the queue are preprocessed already)
    if (!pending_queue.empty() || !unput_queue.empty())
        return pp_token();      // return next token

// test for EOF, if there is a pending input context, pop it back and continue
// parsing with it
bool returned_from_include_file = returned_from_include();

// try to generate the next token
    if (iter_ctx->first != iter_ctx->last) {
        do {
        // If there are pending tokens in the queue, we'll have to return
        // these. This may happen from a #pragma directive, which got replaced
        // by some token sequence.
            if (!pending_queue.empty()) {
            util::on_exit::pop_front<token_sequence_type>
                pop_front_token(pending_queue);

                return act_token = pending_queue.front();
            }

        // adjust the current position (line and column)
        bool was_seen_newline = seen_newline || returned_from_include_file;

        // fetch the current token
            act_token = *iter_ctx->first;
            act_pos = act_token.get_position();

        // act accordingly on the current token
        token_id id = token_id(act_token);

            if (T_EOF == id) {
            // returned from an include file, continue with the next token
                whitespace.shift_tokens(T_EOF);
                ++iter_ctx->first;

            // now make sure this line has a newline
                if ((!seen_newline || act_pos.get_column() > 1) &&
                    !need_single_line(ctx.get_language()))
                {
                // warn, if this file does not end with a newline
                    BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                        last_line_not_terminated, "", act_pos);
                }
                continue;   // if this is the main file, the while loop breaks
            }
            else if (T_NEWLINE == id || T_CPPCOMMENT == id) {
            // a newline is to be returned ASAP, a C++ comment too
            // (the C++ comment token includes the trailing newline)
                seen_newline = true;
                ++iter_ctx->first;

                if (!ctx.get_if_block_status()) {
                // skip this token because of the disabled #if block
                    whitespace.shift_tokens(id);  // whitespace controller
                    util::impl::call_skipped_token_hook(ctx, act_token);
                    continue;
                }
                return act_token;
            }
            seen_newline = false;

            if (was_seen_newline && pp_directive()) {
            // a pp directive was found
//                 pending_queue.push_back(result_type(T_NEWLINE, "\n", act_pos));
//                 seen_newline = true;
//                 must_emit_line_directive = true;

            // loop to the next token to analyze
            // simply fall through, since the iterator was already adjusted
            // correctly
            }
            else if (ctx.get_if_block_status()) {
            // preprocess this token, eat up more, if appropriate, return
            // the next preprocessed token
                return pp_token();
            }
            else {
            // compilation condition is false: if the current token is a
            // newline, account for it, otherwise discard the actual token and
            // try the next one
                if (T_NEWLINE == token_id(act_token)) {
                    seen_newline = true;
                    must_emit_line_directive = true;
                }

            // next token
                util::impl::call_skipped_token_hook(ctx, act_token);
                ++iter_ctx->first;
            }

        } while ((iter_ctx->first != iter_ctx->last) ||
                 (returned_from_include_file = returned_from_include()));

    // overall eof reached
        if (ctx.get_if_block_depth() > 0 && !need_single_line(ctx.get_language()))
        {
        // missing endif directive(s)
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                missing_matching_endif, "", act_pos);
        }
    }
    else {
        act_token = eof;            // this is the last token
    }

//  whitespace.shift_tokens(T_EOF);     // whitespace controller
    return act_token;                   // return eof token
}

template <typename ContextT>
inline bool
pp_iterator_functor<ContextT>::emit_line_directive()
{
    using namespace boost::wave;

typename ContextT::position_type pos = act_token.get_position();

//     if (must_emit_line_directive &&
//         iter_ctx->emitted_lines+1 == act_pos.get_line() &&
//         iter_ctx->filename == act_pos.get_file())
//     {
//         must_emit_line_directive = false;
//         return false;
//     }

    if (must_emit_line_directive ||
        iter_ctx->emitted_lines+1 != act_pos.get_line())
    {
    // unput the current token
        pending_queue.push_front(act_token);
        pos.set_line(act_pos.get_line());

        if (iter_ctx->emitted_lines+2 == act_pos.get_line() && act_pos.get_line() != 1) {
        // prefer to output a single newline instead of the #line directive
//             whitespace.shift_tokens(T_NEWLINE);
            act_token = result_type(T_NEWLINE, "\n", pos);
        }
        else {
        // account for the newline emitted here
            act_pos.set_line(act_pos.get_line()-1);
            iter_ctx->emitted_lines = act_pos.get_line()-1;

        token_sequence_type pending;

            if (!ctx.get_hooks().emit_line_directive(ctx, pending, act_token))
            {
            unsigned int column = 6;

                // the hook did not generate anything, emit default #line
                pos.set_column(1);
                pending.push_back(result_type(T_PP_LINE, "#line", pos));

                pos.set_column(column);      // account for '#line'
                pending.push_back(result_type(T_SPACE, " ", pos));

            // 21 is the max required size for a 64 bit integer represented as a
            // string
            char buffer[22];

                using namespace std;    // for some systems sprintf is in namespace std
                sprintf (buffer, "%ld", pos.get_line());

                pos.set_column(++column);                 // account for ' '
                pending.push_back(result_type(T_INTLIT, buffer, pos));
                pos.set_column(column += (unsigned int)strlen(buffer)); // account for <number>
                pending.push_back(result_type(T_SPACE, " ", pos));
                pos.set_column(++column);                 // account for ' '

            std::string file("\"");
            boost::filesystem::path filename(
                wave::util::create_path(act_pos.get_file().c_str()));

                using wave::util::impl::escape_lit;
                file += escape_lit(wave::util::native_file_string(filename)) + "\"";

                pending.push_back(result_type(T_STRINGLIT, file.c_str(), pos));
                pos.set_column(column += (unsigned int)file.size());    // account for filename
                pending.push_back(result_type(T_GENERATEDNEWLINE, "\n", pos));
            }

        // if there is some replacement text, insert it into the pending queue
            if (!pending.empty()) {
                pending_queue.splice(pending_queue.begin(), pending);
                act_token = pending_queue.front();
                pending_queue.pop_front();
            }
        }

        must_emit_line_directive = false;     // we are now in sync
        return true;
    }

    must_emit_line_directive = false;         // we are now in sync
    return false;
}

template <typename ContextT>
inline typename pp_iterator_functor<ContextT>::result_type const &
pp_iterator_functor<ContextT>::pp_token()
{
    using namespace boost::wave;

token_id id = token_id(*iter_ctx->first);

    // eat all T_PLACEHOLDER tokens, eventually slipped through out of the
    // macro engine
    do {
        if (!pending_queue.empty()) {
        // if there are pending tokens in the queue, return the first one
            act_token = pending_queue.front();
            pending_queue.pop_front();
            act_pos = act_token.get_position();
        }
        else if (!unput_queue.empty()
              || T_IDENTIFIER == id
              || IS_CATEGORY(id, KeywordTokenType)
              || IS_EXTCATEGORY(id, OperatorTokenType|AltExtTokenType)
              || IS_CATEGORY(id, BoolLiteralTokenType))
        {
        //  call the lexer, preprocess the required number of tokens, put them
        //  into the unput queue
            act_token = ctx.expand_tokensequence(iter_ctx->first,
                iter_ctx->last, pending_queue, unput_queue, skipped_newline);
        }
        else {
        // simply return the next token
            act_token = *iter_ctx->first;
            ++iter_ctx->first;
        }
        id = token_id(act_token);

    } while (T_PLACEHOLDER == id);
    return act_token;
}

    template <typename ContextT>
    bool call_found_directive_hook(ContextT& ctx,
        typename ContextT::token_type const& found_directive)
    {
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
        ctx.get_hooks().found_directive(found_directive);
#else
        if (ctx.get_hooks().found_directive(ctx.derived(), found_directive))
            return true;    // skip this directive and return newline only
#endif
        return false;
    }


    template <typename ContextT, typename IteratorT>
    bool next_token_is_pp_directive(ContextT &ctx, IteratorT &it, IteratorT const &end)
    {
        using namespace boost::wave;

        token_id id = T_UNKNOWN;
        for (/**/; it != end; ++it) {
            id = token_id(*it);
            if (!IS_CATEGORY(id, WhiteSpaceTokenType))
                break;          // skip leading whitespace
            if (IS_CATEGORY(id, EOLTokenType) || IS_CATEGORY(id, EOFTokenType))
                break;          // do not enter a new line
            if (T_CPPCOMMENT == id ||
                context_policies::util::ccomment_has_newline(*it))
            {
                break;
            }

            // this token gets skipped
            util::impl::call_skipped_token_hook(ctx, *it);
        }
        BOOST_ASSERT(it == end || id != T_UNKNOWN);
        return it != end && IS_CATEGORY(id, PPTokenType);
    }

    template <typename ContextT, typename IteratorT>
    bool pp_is_last_on_line(ContextT &ctx, IteratorT &it, IteratorT const &end,
        bool call_hook = true)
    {
        using namespace boost::wave;

        // this token gets skipped
        if (call_hook)
            util::impl::call_skipped_token_hook(ctx, *it);

        for (++it; it != end; ++it) {
        token_id id = token_id(*it);

            if (T_CPPCOMMENT == id || T_NEWLINE == id ||
                context_policies::util::ccomment_has_newline(*it))
            {
                if (call_hook)
                    util::impl::call_skipped_token_hook(ctx, *it);
                ++it;           // skip eol/C/C++ comment
                return true;    // no more significant tokens on this line
            }

            if (!IS_CATEGORY(id, WhiteSpaceTokenType))
                break;

            // this token gets skipped
            if (call_hook)
                util::impl::call_skipped_token_hook(ctx, *it);
        }
        return false;
    }

    template <typename ContextT, typename IteratorT>
    bool skip_to_eol(ContextT &ctx, IteratorT &it, IteratorT const &end,
        bool call_hook = true)
    {
        using namespace boost::wave;

        for (/**/; it != end; ++it) {
        token_id id = token_id(*it);

            if (T_CPPCOMMENT == id || T_NEWLINE == id ||
                context_policies::util::ccomment_has_newline(*it))
            {
                // always call hook for eol
                util::impl::call_skipped_token_hook(ctx, *it);
                ++it;           // skip eol/C/C++ comment
                return true;    // found eol
            }

            if (call_hook)
                util::impl::call_skipped_token_hook(ctx, *it);
        }
        return false;
    }

    template <typename ContextT, typename ContainerT>
    inline void
    remove_leading_whitespace(ContextT &ctx, ContainerT& c, bool call_hook = true)
    {
        typename ContainerT::iterator it = c.begin();
        while (IS_CATEGORY(*it, WhiteSpaceTokenType)) {
            typename ContainerT::iterator save = it++;
            if (call_hook)
                util::impl::call_skipped_token_hook(ctx, *save);
            c.erase(save);
        }
    }

template <typename IteratorT>
inline bool
pp_iterator_functor<ContextT>::extract_identifier(IteratorT &it)
{
    token_id id = util::impl::skip_whitespace(it, iter_ctx->last);
    if (T_IDENTIFIER == id || IS_CATEGORY(id, KeywordTokenType) ||
        IS_EXTCATEGORY(id, OperatorTokenType|AltExtTokenType) ||
        IS_CATEGORY(id, BoolLiteralTokenType))
    {
        IteratorT save = it;
        if (impl::pp_is_last_on_line(ctx, save, iter_ctx->last, false))
            return true;
    }

    // report the ill formed directive
    impl::skip_to_eol(ctx, it, iter_ctx->last);

string_type str(util::impl::as_string<string_type>(iter_ctx->first, it));

    seen_newline = true;
    iter_ctx->first = it;
    on_illformed(str);
    return false;
}

template <typename IteratorT>
inline bool
pp_iterator_functor<ContextT>::ensure_is_last_on_line(IteratorT& it, bool call_hook)
{
    if (!impl::pp_is_last_on_line(ctx, it, iter_ctx->last, call_hook))
    {
    // enable error recovery (start over with the next line)
        impl::skip_to_eol(ctx, it, iter_ctx->last);

    string_type str(util::impl::as_string<string_type>(
        iter_ctx->first, it));

        seen_newline = true;
        iter_ctx->first = it;

    // report an invalid directive
        on_illformed(str);
        return false;
    }

    if (it == iter_ctx->last && !need_single_line(ctx.get_language()))
    {
    // The line doesn't end with an eol but eof token.
        seen_newline = true;    // allow to resume after warning
        iter_ctx->first = it;

    // Trigger a warning that the last line was not terminated with a
    // newline.
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
            last_line_not_terminated, "", act_pos);

        return false;
    }
    return true;
}

template <typename IteratorT>
inline bool
pp_iterator_functor<ContextT>::skip_to_eol_with_check(IteratorT &it, bool call_hook)
{
    typename ContextT::string_type value ((*it).get_value());
    if (!impl::skip_to_eol(ctx, it, iter_ctx->last, call_hook) &&
        !need_single_line(ctx.get_language()))
    {
    // The line doesn't end with an eol but eof token.
        seen_newline = true;    // allow to resume after warning
        iter_ctx->first = it;

    // Trigger a warning, that the last line was not terminated with a
    // newline.
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
            last_line_not_terminated, "", act_pos);
        return false;
    }

// normal line ending reached, adjust iterator and flag
    seen_newline = true;
    iter_ctx->first = it;
    return true;
}

template <typename IteratorT>
inline bool
pp_iterator_functor<ContextT>::handle_pp_directive(IteratorT &it)
{
    token_id id = token_id(*it);
    bool can_exit = true;
    bool call_hook_in_skip = true;
    if (!ctx.get_if_block_status()) {
        if (IS_EXTCATEGORY(*it, PPConditionalTokenType)) {
        // simulate the if block hierarchy
            switch (static_cast<unsigned int>(id)) {
            case T_PP_IFDEF:        // #ifdef
            case T_PP_IFNDEF:       // #ifndef
            case T_PP_IF:           // #if
                ctx.enter_if_block(false);
                break;

            case T_PP_ELIF:         // #elif
                if (!ctx.get_enclosing_if_block_status()) {
                    if (!ctx.enter_elif_block(false)) {
                    // #else without matching #if
                        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                            missing_matching_if, "#elif", act_pos);
                        return true;  // do not analyze this directive any further
                    }
                }
                else {
                    can_exit = false;   // #elif is not always safe to skip
                }
                break;

            case T_PP_ELSE:         // #else
            case T_PP_ENDIF:        // #endif
                {
                // handle this directive
                    if (T_PP_ELSE == token_id(*it))
                        on_else();
                    else
                        on_endif();

                // make sure, there are no (non-whitespace) tokens left on
                // this line
                    ensure_is_last_on_line(it);

                // we skipped to the end of this line already
                    seen_newline = true;
                    iter_ctx->first = it;
                }
                return true;

            default:                // #something else
                on_illformed((*it).get_value());
                break;
            }
        }
        else {
            util::impl::call_skipped_token_hook(ctx, *it);
            ++it;
        }
    }
    else {
    // try to handle the simple pp directives without parsing
        result_type directive = *it;
        bool include_next = false;
        switch (static_cast<unsigned int>(id)) {
        case T_PP_QHEADER:        // #include "..."
#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
        case T_PP_QHEADER_NEXT:
#endif
            include_next = (T_PP_QHEADER_NEXT == id) ? true : false;
            if (!impl::call_found_directive_hook(ctx, *it))
            {
                string_type dir((*it).get_value());

            // make sure, there are no (non-whitespace) tokens left on
            // this line
                if (ensure_is_last_on_line(it))
                {
                    seen_newline = true;
                    iter_ctx->first = it;
                    on_include (dir, false, include_next);
                }
                return true;
            }
            break;

        case T_PP_HHEADER:        // #include <...>
#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
        case T_PP_HHEADER_NEXT:
#endif
            include_next = (T_PP_HHEADER_NEXT == id) ? true : false;
            if (!impl::call_found_directive_hook(ctx, *it))
            {
                string_type dir((*it).get_value());

            // make sure, there are no (non-whitespace) tokens left on
            // this line
                if (ensure_is_last_on_line(it))
                {
                    seen_newline = true;
                    iter_ctx->first = it;
                    on_include (dir, true, include_next);
                }
                return true;
            }
            break;

        case T_PP_ELSE:         // #else
        case T_PP_ENDIF:        // #endif
            if (!impl::call_found_directive_hook(ctx, *it))
            {
                // handle this directive
                if (T_PP_ELSE == token_id(*it))
                    on_else();
                else
                    on_endif();

            // make sure, there are no (non-whitespace) tokens left on
            // this line
                ensure_is_last_on_line(it);

            // we skipped to the end of this line already
                seen_newline = true;
                iter_ctx->first = it;
                return true;
            }
            break;

        // extract everything on this line as arguments
//         case T_PP_IF:                   // #if
//         case T_PP_ELIF:                 // #elif
//         case T_PP_ERROR:                // #error
//         case T_PP_WARNING:              // #warning
//         case T_PP_PRAGMA:               // #pragma
//         case T_PP_LINE:                 // #line
//             break;

        // extract first non-whitespace token as argument
        case T_PP_UNDEF:                // #undef
            if (!impl::call_found_directive_hook(ctx, *it) &&
                extract_identifier(it))
            {
                on_undefine(it);
            }
            call_hook_in_skip = false;
            break;

        case T_PP_IFDEF:                // #ifdef
            if (!impl::call_found_directive_hook(ctx, *it) &&
                extract_identifier(it))
            {
                on_ifdef(directive, it);
            }
            call_hook_in_skip = false;
            break;

        case T_PP_IFNDEF:               // #ifndef
            if (!impl::call_found_directive_hook(ctx, *it) &&
                extract_identifier(it))
            {
                on_ifndef(directive, it);
            }
            call_hook_in_skip = false;
            break;

#if BOOST_WAVE_SUPPORT_MS_EXTENSIONS != 0
//         case T_MSEXT_PP_REGION:         // #region ...
//             break;
//
//         case T_MSEXT_PP_ENDREGION:      // #endregion
//             break;
#endif

        default:
            can_exit = false;
            break;
        }
    }

// start over with the next line, if only possible
    if (can_exit) {
        skip_to_eol_with_check(it, call_hook_in_skip);
        return true;    // may be safely ignored
    }
    return false;   // do not ignore this pp directive
}

template <typename ContextT>
inline bool
pp_iterator_functor<ContextT>::pp_directive()
{
    using namespace cpplexer;

// test, if the next non-whitespace token is a pp directive
lexer_type it = iter_ctx->first;

    if (!impl::next_token_is_pp_directive(ctx, it, iter_ctx->last)) {
    // skip null pp directive (no need to do it via the parser)
        if (it != iter_ctx->last && T_POUND == BASE_TOKEN(token_id(*it))) {
            if (impl::pp_is_last_on_line(ctx, it, iter_ctx->last)) {
            // start over with the next line
                seen_newline = true;
                iter_ctx->first = it;
                return true;
            }
            else if (ctx.get_if_block_status()) {
            // report invalid pp directive
                impl::skip_to_eol(ctx, it, iter_ctx->last);
                seen_newline = true;

                string_type str(boost::wave::util::impl::as_string<string_type>(
                    iter_ctx->first, it));

            token_sequence_type faulty_line;

                for (/**/; iter_ctx->first != it; ++iter_ctx->first)
                    faulty_line.push_back(*iter_ctx->first);

                token_sequence_type pending;
                if (ctx.get_hooks().found_unknown_directive(ctx, faulty_line, pending))
                {
                // if there is some replacement text, insert it into the pending queue
                    if (!pending.empty())
                        pending_queue.splice(pending_queue.begin(), pending);
                    return true;
                }

                // default behavior is to throw an exception
                on_illformed(str);
            }
        }

    // this line does not contain a pp directive, so simply return
        return false;
    }

// found eof
    if (it == iter_ctx->last)
        return false;

// ignore/handle all pp directives not related to conditional compilation while
// if block status is false
    if (handle_pp_directive(it)) {
        // we may skip pp directives only if the current if block status is
        // false or if it was a #include directive we could handle directly
        return true;    //  the pp directive has been handled/skipped
    }

// found a pp directive, so try to identify it, start with the pp_token
bool found_eof = false;
result_type found_directive;
token_sequence_type found_eoltokens;

tree_parse_info_type hit = cpp_grammar_type::parse_cpp_grammar(
    it, iter_ctx->last, act_pos, found_eof, found_directive, found_eoltokens);

    if (hit.match) {
    // position the iterator past the matched sequence to allow
    // resynchronization, if an error occurs
        iter_ctx->first = hit.stop;
        seen_newline = true;
        must_emit_line_directive = true;

    // found a valid pp directive, dispatch to the correct function to handle
    // the found pp directive
    bool result = dispatch_directive (hit, found_directive, found_eoltokens);

        if (found_eof && !need_single_line(ctx.get_language())) {
        // The line was terminated with an end of file token.
        // So trigger a warning, that the last line was not terminated with a
        // newline.
            BOOST_WAVE_THROW_CTX(ctx, preprocess_exception,
                last_line_not_terminated, "", act_pos);
        }
        return result;
    }
    else if (token_id(found_directive) != T_EOF) {
    // recognized invalid directive
        impl::skip_to_eol(ctx, it, iter_ctx->last);
        seen_newline = true;

        string_type str(boost::wave::util::impl::as_string<string_type>(
            iter_ctx->first, it));
        iter_ctx->first = it;

    // report the ill formed directive
        on_illformed(str);
    }
    return false;
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_include (string_type const &s,
    bool is_system, bool include_next)
{
    BOOST_ASSERT(ctx.get_if_block_status());

// strip quotes first, extract filename
typename string_type::size_type pos_end = s.find_last_of(is_system ? '>' : '\"');

    if (string_type::npos == pos_end) {
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_include_statement,
            s.c_str(), act_pos);
        return;
    }

typename string_type::size_type pos_begin =
    s.find_last_of(is_system ? '<' : '\"', pos_end-1);

    if (string_type::npos == pos_begin) {
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_include_statement,
            s.c_str(), act_pos);
        return;
    }

std::string file_token(s.substr(pos_begin, pos_end-pos_begin+1).c_str());
std::string file_path(s.substr(pos_begin+1, pos_end-pos_begin-1).c_str());

// finally include the file
    on_include_helper(file_token.c_str(), file_path.c_str(), is_system,
        include_next);
}


template <typename ContextT>
inline bool
pp_iterator_functor<ContextT>::on_include_helper (char const *f, char const *s,
    bool is_system, bool include_next)
{
    namespace fs = boost::filesystem;

// try to locate the given file, searching through the include path lists
std::string file_path(s);
std::string dir_path;
#if BOOST_WAVE_SUPPORT_INCLUDE_NEXT != 0
char const *current_name = include_next ? iter_ctx->real_filename.c_str() : 0;
#else
char const *current_name = 0;   // never try to match current file name
#endif

// call the 'found_include_directive' hook function
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    ctx.get_hooks().found_include_directive(f, include_next);
#else
    if (ctx.get_hooks().found_include_directive(ctx.derived(), f, include_next))
        return true;    // client returned false: skip file to include
#endif

    file_path = util::impl::unescape_lit(file_path);
    std::string native_path_str;

    if (!ctx.get_hooks().locate_include_file(ctx, file_path, is_system,
            current_name, dir_path, native_path_str))
    {
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, bad_include_file,
            file_path.c_str(), act_pos);
        return false;
    }

// test, if this file is known through a #pragma once directive
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
    if (!ctx.has_pragma_once(native_path_str))
#endif
    {
    // the new include file determines the actual current directory
        ctx.set_current_directory(native_path_str.c_str());

    // preprocess the opened file
    boost::shared_ptr<base_iteration_context_type> new_iter_ctx (
        new iteration_context_type(ctx, native_path_str.c_str(), act_pos,
            boost::wave::enable_prefer_pp_numbers(ctx.get_language()),
            is_system ? base_iteration_context_type::system_header :
                base_iteration_context_type::user_header));

    // call the include policy trace function
#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
        ctx.get_hooks().opened_include_file(dir_path, file_path,
            ctx.get_iteration_depth(), is_system);
#else
        ctx.get_hooks().opened_include_file(ctx.derived(), dir_path, file_path,
            is_system);
#endif

    // store current file position
        iter_ctx->real_relative_filename = ctx.get_current_relative_filename().c_str();
        iter_ctx->filename = act_pos.get_file();
        iter_ctx->line = act_pos.get_line();
        iter_ctx->if_block_depth = ctx.get_if_block_depth();
        iter_ctx->emitted_lines = (unsigned int)(-1);   // force #line directive

    // push the old iteration context onto the stack and continue with the new
        ctx.push_iteration_context(act_pos, iter_ctx);
        iter_ctx = new_iter_ctx;
        seen_newline = true;        // fake a newline to trigger pp_directive
        must_emit_line_directive = true;

        act_pos.set_file(iter_ctx->filename);  // initialize file position
#if BOOST_WAVE_SUPPORT_PRAGMA_ONCE != 0
        fs::path rfp(wave::util::create_path(iter_ctx->real_filename.c_str()));
        std::string real_filename(rfp.string());
        ctx.set_current_filename(real_filename.c_str());
#endif

        ctx.set_current_relative_filename(dir_path.c_str());
        iter_ctx->real_relative_filename = dir_path.c_str();

        act_pos.set_line(iter_ctx->line);
        act_pos.set_column(0);
    }
    return true;
}

    template <typename StringT>
    inline StringT
    trim_whitespace(StringT const &s)
    {
        typedef typename StringT::size_type size_type;

        size_type first = s.find_first_not_of(" \t\v\f");
        if (StringT::npos == first)
            return StringT();
        size_type last = s.find_last_not_of(" \t\v\f");
        return s.substr(first, last-first+1);
    }

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_undefine (lexer_type const &it)
{
    BOOST_ASSERT(ctx.get_if_block_status());

// retrieve the macro name to undefine from the parse tree
    ctx.remove_macro_definition((*it).get_value()); // throws for predefined macros
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_ifdef(
    result_type const& found_directive, lexer_type const &it)
//     typename parse_tree_type::const_iterator const &it)
//     typename parse_tree_type::const_iterator const &end)
{
// get_token_value<result_type, parse_node_type> get_value;
// token_sequence_type toexpand;
//
//     std::copy(make_ref_transform_iterator((*begin).children.begin(), get_value),
//         make_ref_transform_iterator((*begin).children.end(), get_value),
//         std::inserter(toexpand, toexpand.end()));

bool is_defined = false;
token_sequence_type directive;

    directive.insert(directive.end(), *it);

#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    is_defined = ctx.is_defined_macro((*it).get_value()); // toexpand.begin(), toexpand.end());
    ctx.get_hooks().evaluated_conditional_expression(directive, is_defined);
#else
    do {
        is_defined = ctx.is_defined_macro((*it).get_value()); // toexpand.begin(), toexpand.end());
    } while (ctx.get_hooks().evaluated_conditional_expression(ctx.derived(),
             found_directive, directive, is_defined));
#endif
    ctx.enter_if_block(is_defined);
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_ifndef(
    result_type const& found_directive, lexer_type const &it)
//     typename parse_tree_type::const_iterator const &it)
//     typename parse_tree_type::const_iterator const &end)
{
// get_token_value<result_type, parse_node_type> get_value;
// token_sequence_type toexpand;
//
//     std::copy(make_ref_transform_iterator((*begin).children.begin(), get_value),
//         make_ref_transform_iterator((*begin).children.end(), get_value),
//         std::inserter(toexpand, toexpand.end()));

bool is_defined = false;
token_sequence_type directive;

    directive.insert(directive.end(), *it);

#if BOOST_WAVE_USE_DEPRECIATED_PREPROCESSING_HOOKS != 0
    is_defined = ctx.is_defined_macro((*it).get_value()); // toexpand.begin(), toexpand.end());
    ctx.get_hooks().evaluated_conditional_expression(directive, is_defined);
#else
    do {
        is_defined = ctx.is_defined_macro((*it).get_value()); // toexpand.begin(), toexpand.end());
    } while (ctx.get_hooks().evaluated_conditional_expression(ctx.derived(),
             found_directive, directive, is_defined));
#endif
    ctx.enter_if_block(!is_defined);
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_else()
{
    if (!ctx.enter_else_block()) {
    // #else without matching #if
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, missing_matching_if,
            "#else", act_pos);
    }
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_endif()
{
    if (!ctx.exit_if_block()) {
    // #endif without matching #if
        BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, missing_matching_if,
            "#endif", act_pos);
    }
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::replace_undefined_identifiers(
    token_sequence_type &expanded)
{
    typename token_sequence_type::iterator exp_end = expanded.end();
    for (typename token_sequence_type::iterator exp_it = expanded.begin();
         exp_it != exp_end; ++exp_it)
    {
        using namespace boost::wave;

        token_id id = token_id(*exp_it);
        if (IS_CATEGORY(id, IdentifierTokenType) ||
            IS_CATEGORY(id, KeywordTokenType))
        {
            (*exp_it).set_token_id(T_INTLIT);
            (*exp_it).set_value("0");
        }
    }
}

template <typename ContextT>
inline void
pp_iterator_functor<ContextT>::on_illformed(
    typename result_type::string_type s)
{
    BOOST_ASSERT(ctx.get_if_block_status());

    // some messages have more than one newline at the end
    typename string_type::size_type p = s.find_last_not_of('\n');
    if (string_type::npos != p)
        s = s.substr(0, p+1);

    // throw the exception
    BOOST_WAVE_THROW_CTX(ctx, preprocess_exception, ill_formed_directive,
        s.c_str(), act_pos);
}


    template <typename IteratorT, typename StringT>
    bool retrieve_line_info (IteratorT first, IteratorT const &last,
        unsigned int &line, StringT &file,
        boost::wave::preprocess_exception::error_code& error)
    {
        using namespace boost::wave;
        token_id id = token_id(*first);
        if (T_PP_NUMBER == id || T_INTLIT == id) {
        // extract line number
            using namespace std;    // some systems have atoi in namespace std
            line = (unsigned int)atoi((*first).get_value().c_str());
            if (0 == line)
                error = preprocess_exception::bad_line_number;

        // re-extract line number with spirit to diagnose overflow
            using namespace boost::spirit::classic;
            if (!parse((*first).get_value().c_str(), int_p).full)
                error = preprocess_exception::bad_line_number;

        // extract file name (if it is given)
            while (++first != last && IS_CATEGORY(*first, WhiteSpaceTokenType))
                /**/;   // skip whitespace

            if (first != last) {
                if (T_STRINGLIT != token_id(*first)) {
                    error = preprocess_exception::bad_line_filename;
                    return false;
                }

            StringT const &file_lit = (*first).get_value();

                if ('L' == file_lit[0]) {
                    error = preprocess_exception::bad_line_filename;
                    return false;       // shouldn't be a wide character string
                }

                file = file_lit.substr(1, file_lit.size()-2);

            // test if there is other junk on this line
                while (++first != last && IS_CATEGORY(*first, WhiteSpaceTokenType))
                    /**/;   // skip whitespace
            }
            return first == last;
        }
        error = preprocess_exception::bad_line_statement;
        return false;
    }


template <typename ContextT>
inline bool
pp_iterator_functor<ContextT>::interpret_pragma(
    token_sequence_type const &pragma_body, token_sequence_type &result)
{
    using namespace cpplexer;

    typename token_sequence_type::const_iterator end = pragma_body.end();
    typename token_sequence_type::const_iterator it = pragma_body.begin();
    for (++it; it != end && IS_CATEGORY(*it, WhiteSpaceTokenType); ++it)
        /**/;   // skip whitespace

    if (it == end)      // eof reached
        return false;

    return boost::wave::util::interpret_pragma(
        ctx.derived(), act_token, it, end, result);
}

    pp_iterator()
    {}


    template <typename IteratorT>
    pp_iterator(ContextT &ctx, IteratorT const &first, IteratorT const &last,
        typename ContextT::position_type const &pos)
    :   base_type(input_policy_type(ctx, first, last, pos))
    {}


    bool force_include(char const *path_, bool is_last)
    {
        bool result = this->get_functor().on_include_helper(path_, path_,
            false, false);
        if (is_last) {
            this->functor_input_type::
                template inner<input_policy_type>::advance_input();
        }
        return result;
    }

    template <typename StringT>
    inline bool
    would_form_universal_char (StringT const &value)
    {
        if ('u' != value[0] && 'U' != value[0])
            return false;
        if ('u' == value[0] && value.size() < 5)
            return false;
        if ('U' == value[0] && value.size() < 9)
            return false;
    
    typename StringT::size_type pos = 
        value.find_first_not_of("0123456789abcdefABCDEF", 1);
        
        if (StringT::npos == pos || 
            ('u' == value[0] && pos > 5) ||
            ('U' == value[0] && pos > 9))
        {
            return true;        // would form an universal char
        }
        return false;
    }

    template <typename StringT>
    inline bool 
    handle_identifier(boost::wave::token_id prev, 
        boost::wave::token_id before, StringT const &value)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_IDENTIFIER:
        case T_NONREPLACABLE_IDENTIFIER:
        case T_COMPL_ALT:
        case T_OR_ALT:
        case T_AND_ALT:
        case T_NOT_ALT:
        case T_XOR_ALT:
        case T_ANDASSIGN_ALT:
        case T_ORASSIGN_ALT:
        case T_XORASSIGN_ALT:
        case T_NOTEQUAL_ALT:
        case T_FIXEDPOINTLIT:
            return true;

        case T_FLOATLIT:
        case T_INTLIT:
        case T_PP_NUMBER:
            return (value.size() > 1 || (value[0] != 'e' && value[0] != 'E'));
            
         // avoid constructing universal characters (\u1234)
        case TOKEN_FROM_ID('\\', UnknownTokenType):
            return would_form_universal_char(value);
        }
        return false;
    }

    inline bool 
    handle_intlit(boost::wave::token_id prev, boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_IDENTIFIER:
        case T_NONREPLACABLE_IDENTIFIER:
        case T_INTLIT:
        case T_FLOATLIT:
        case T_FIXEDPOINTLIT:
        case T_PP_NUMBER:
            return true;
        }
        return false;
    }

    inline bool 
    handle_floatlit(boost::wave::token_id prev, 
        boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_IDENTIFIER:
        case T_NONREPLACABLE_IDENTIFIER:
        case T_INTLIT:
        case T_FLOATLIT:
        case T_FIXEDPOINTLIT:
        case T_PP_NUMBER:
            return true;
        }
        return false;
    }

    inline bool 
    handle_alt_leftbrace(boost::wave::token_id prev, 
        boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_LESS:        // <<%
        case T_SHIFTLEFT:   // <<<%
            return true;
        }
        return false;
    }

    inline bool 
    handle_alt_leftbracket(boost::wave::token_id prev, 
        boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_LESS:        // <<:
        case T_SHIFTLEFT:   // <<<:
            return true;
        }
        return false;
    }

    inline bool 
    handle_fixedpointlit(boost::wave::token_id prev, 
        boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_IDENTIFIER:
        case T_NONREPLACABLE_IDENTIFIER:
        case T_INTLIT:
        case T_FLOATLIT:
        case T_FIXEDPOINTLIT:
        case T_PP_NUMBER:
            return true;
        }
        return false;
    }

    inline bool 
    handle_dot(boost::wave::token_id prev, boost::wave::token_id before)
    {
        using namespace boost::wave;
        switch (static_cast<unsigned int>(prev)) {
        case T_DOT:
            if (T_DOT == before)
                return true;    // ...
            break;
        }
        return false;
    }

    inline bool 
    handle_questionmark(boost::wave::token_id prev, 
        boost::wave::token_id /*before*/)
    {
        using namespace boost::wave;
        switch(static_cast<unsigned int>(prev)) {
        case TOKEN_FROM_ID('\\', UnknownTokenType):     // \?
        case T_QUESTION_MARK:   // ??
            return true;
        }
        return false;
    }

    inline bool
    handle_newline(boost::wave::token_id prev, 
        boost::wave::token_id before)
    {
        using namespace boost::wave;
        switch(static_cast<unsigned int>(prev)) {
        case TOKEN_FROM_ID('\\', UnknownTokenType): // \ \n
        case T_DIVIDE:
            if (T_QUESTION_MARK == before)
                return true;    // ?/\n     // may be \\n
            break;
        }
        return false;
    }


    inline bool 
    handle_parens(boost::wave::token_id prev)
    {
        switch (static_cast<unsigned int>(prev)) {
        case T_LEFTPAREN:
        case T_RIGHTPAREN:
        case T_LEFTBRACKET:
        case T_RIGHTBRACKET:
        case T_LEFTBRACE:
        case T_RIGHTBRACE:
        case T_SEMICOLON:
        case T_COMMA:
        case T_COLON:
            // no insertion between parens/brackets/braces and operators
            return false;   

        default:
            break;
        }
        return true;
    }

    insert_whitespace_detection(bool insert_whitespace_ = true) 
    :   insert_whitespace(insert_whitespace_),
        prev(boost::wave::T_EOF), beforeprev(boost::wave::T_EOF) 
    {}

    
    template <typename StringT>
    bool must_insert(boost::wave::token_id current, StringT const &value)
    {
        if (!insert_whitespace)
            return false;       // skip whitespace insertion alltogether
            
        using namespace boost::wave;
        switch (static_cast<unsigned int>(current)) {
        case T_NONREPLACABLE_IDENTIFIER:
        case T_IDENTIFIER: 
            return impl::handle_identifier(prev, beforeprev, value); 
        case T_PP_NUMBER:
        case T_INTLIT:
            return impl::handle_intlit(prev, beforeprev); 
        case T_FLOATLIT:
            return impl::handle_floatlit(prev, beforeprev); 
        case T_STRINGLIT:
            if (TOKEN_FROM_ID('L', IdentifierTokenType) == prev)       // 'L'
                return true;
            break;
        case T_LEFTBRACE_ALT:
            return impl::handle_alt_leftbrace(prev, beforeprev); 
        case T_LEFTBRACKET_ALT:
            return impl::handle_alt_leftbracket(prev, beforeprev); 
        case T_FIXEDPOINTLIT:
            return impl::handle_fixedpointlit(prev, beforeprev); 
        case T_DOT:
            return impl::handle_dot(prev, beforeprev); 
        case T_QUESTION_MARK:
            return impl::handle_questionmark(prev, beforeprev); 
        case T_NEWLINE:
            return impl::handle_newline(prev, beforeprev); 

        case T_LEFTPAREN:
        case T_RIGHTPAREN:
        case T_LEFTBRACKET:
        case T_RIGHTBRACKET:
        case T_SEMICOLON:
        case T_COMMA:
        case T_COLON:
            switch (static_cast<unsigned int>(prev)) {
            case T_LEFTPAREN:
            case T_RIGHTPAREN:
            case T_LEFTBRACKET:
            case T_RIGHTBRACKET:
            case T_LEFTBRACE:
            case T_RIGHTBRACE:
                return false;   // no insertion between parens/brackets/braces

            default:
                if (IS_CATEGORY(prev, OperatorTokenType))
                    return false;
                break;
            }        
            break;
            
        case T_LEFTBRACE:
        case T_RIGHTBRACE:
            switch (static_cast<unsigned int>(prev)) {
            case T_LEFTPAREN:
            case T_RIGHTPAREN:
            case T_LEFTBRACKET:
            case T_RIGHTBRACKET:
            case T_LEFTBRACE:
            case T_RIGHTBRACE:
            case T_SEMICOLON:
            case T_COMMA:
            case T_COLON:
                return false;   // no insertion between parens/brackets/braces

            case T_QUESTION_MARK:
                if (T_QUESTION_MARK == beforeprev)
                    return true;
                if (IS_CATEGORY(prev, OperatorTokenType))
                    return false;
                break;
                
            default:
                break;
            }
            break;
                            
        case T_MINUS:
        case T_MINUSMINUS:
        case T_MINUSASSIGN:
            if (T_MINUS == prev || T_MINUSMINUS == prev)
                return true;
            if (!impl::handle_parens(prev))
                return false;
            if (T_QUESTION_MARK == prev && T_QUESTION_MARK == beforeprev)
                return true;
            break;
            
        case T_PLUS:
        case T_PLUSPLUS:
        case T_PLUSASSIGN:
            if (T_PLUS == prev || T_PLUSPLUS == prev)
                return true;
            if (!impl::handle_parens(prev))
                return false;
            if (T_QUESTION_MARK == prev && T_QUESTION_MARK == beforeprev)
                return true;
            break;
            
        case T_DIVIDE:
        case T_DIVIDEASSIGN:
            if (T_DIVIDE == prev)
                return true;
            if (!impl::handle_parens(prev))
                return false;
            if (T_QUESTION_MARK == prev && T_QUESTION_MARK == beforeprev)
                return true;
            break;
        
        case T_EQUAL:
        case T_ASSIGN:
            switch (static_cast<unsigned int>(prev)) {
            case T_PLUSASSIGN:
            case T_MINUSASSIGN:
            case T_DIVIDEASSIGN:
            case T_STARASSIGN:
            case T_SHIFTRIGHTASSIGN:
            case T_SHIFTLEFTASSIGN:
            case T_EQUAL:
            case T_NOTEQUAL:
            case T_LESSEQUAL:
            case T_GREATEREQUAL:
            case T_LESS:
            case T_GREATER:
            case T_PLUS:
            case T_MINUS:
            case T_STAR:
            case T_DIVIDE:
            case T_ORASSIGN:
            case T_ANDASSIGN:
            case T_XORASSIGN:
            case T_OR:
            case T_AND:
            case T_XOR:
            case T_OROR:
            case T_ANDAND:
                return true;

            case T_QUESTION_MARK:
                if (T_QUESTION_MARK == beforeprev)
                    return true;
                break;
                
            default:
                if (!impl::handle_parens(prev))
                    return false;
                break;
            }
            break;

        case T_GREATER:
            if (T_MINUS == prev || T_GREATER == prev)
                return true;    // prevent -> or >>
            if (!impl::handle_parens(prev))
                return false;
            if (T_QUESTION_MARK == prev && T_QUESTION_MARK == beforeprev)
                return true;
            break;

        case T_LESS:
            if (T_LESS == prev)
                return true;    // prevent <<
            // fall through
        case T_CHARLIT:
        case T_NOT:
        case T_NOTEQUAL:
            if (!impl::handle_parens(prev))
                return false;
            if (T_QUESTION_MARK == prev && T_QUESTION_MARK == beforeprev)
                return true;
            break;

        case T_AND:
        case T_ANDAND:
            if (!impl::handle_parens(prev))
                return false;
            if (T_AND == prev || T_ANDAND == prev)
                return true;
            break;
            
        case T_OR:
            if (!impl::handle_parens(prev))
                return false;
            if (T_OR == prev)
                return true;
            break;
            
        case T_XOR:
            if (!impl::handle_parens(prev))
                return false;
            if (T_XOR == prev)
                return true;
            break;
            
        case T_COMPL_ALT:
        case T_OR_ALT:
        case T_AND_ALT:
        case T_NOT_ALT:
        case T_XOR_ALT:
        case T_ANDASSIGN_ALT:
        case T_ORASSIGN_ALT:
        case T_XORASSIGN_ALT:
        case T_NOTEQUAL_ALT:
            switch (static_cast<unsigned int>(prev)) {
            case T_LEFTPAREN:
            case T_RIGHTPAREN:
            case T_LEFTBRACKET:
            case T_RIGHTBRACKET:
            case T_LEFTBRACE:
            case T_RIGHTBRACE:
            case T_SEMICOLON:
            case T_COMMA:
            case T_COLON:
                // no insertion between parens/brackets/braces and operators
                return false;   

            case T_IDENTIFIER:
                if (T_NONREPLACABLE_IDENTIFIER == prev ||
                    IS_CATEGORY(prev, KeywordTokenType))
                {
                    return true;
                }
                break;
                
            default:
                break;
            }
            break;
            
        case T_STAR:
            if (T_STAR == prev)
                return false;     // '*****' do not need to be separated
            if (T_GREATER== prev && 
                (T_MINUS == beforeprev || T_MINUSMINUS == beforeprev)
               )
            {
                return true;    // prevent ->*
            }
            break;

        case T_POUND:
            if (T_POUND == prev)
                return true;
            break;
        }

    // FIXME: else, handle operators separately (will catch to many cases)
//         if (IS_CATEGORY(current, OperatorTokenType) && 
//             IS_CATEGORY(prev, OperatorTokenType))
//         {
//             return true;    // operators must be delimited always
//         }
        return false;
    }

    void shift_tokens (boost::wave::token_id next_id)
    {
        if (insert_whitespace) {
            beforeprev = prev;
            prev = next_id;
        }
    }

    if_block() :
        status(true), some_part_status(true), 
        enclosing_status(true), is_in_else(false)
    {
    }

    if_block(bool status_, bool enclosing_status_) : 
        status(status_), 
        some_part_status(status_),
        enclosing_status(enclosing_status_),
        is_in_else(false)
    {
    }


    void set_status(bool status_) 
    { 
        status = status_; 
        if (status_) 
            some_part_status = true; 
    }

    bool get_status() const { return status; }

    bool get_some_part_status() const { return some_part_status; }

    bool get_enclosing_status() const { return enclosing_status; }

    bool get_in_else() const { return is_in_else; }

    void set_in_else() { is_in_else = true; }


    void enter_if_block(bool new_status)
    {
    // If enclosing block is false, then this block is also false
        bool enclosing_status = get_status();
        this->push (value_type (new_status && enclosing_status, enclosing_status));
    }

    bool enter_elif_block(bool new_status)
    {
        if (!is_inside_ifpart())
            return false;       // #elif without matching #if

        if (get_enclosing_status()) {
            if (get_status()) {
            // entered a (false) #elif block from a true block
                this->top().set_status(false);
            } 
            else if (new_status && !this->top().get_some_part_status()) {
            // Entered true #elif block and no previous block was true
                this->top().set_status(new_status);
            }
        }
        return true;
    }

    bool enter_else_block()
    {
        if (!is_inside_ifpart())
            return false;       // #else without matching #if

        if (get_enclosing_status()) {
            if (!this->top().get_some_part_status()) {
            // Entered (true) #else block and no previous block was true
                this->top().set_status(true);
            } 
            else if (get_status()) {
            // Entered (false) #else block from true block
                this->top().set_status(false);
            }

        // Set else flag
            this->top().set_in_else();
        }
        return true;
    }

    bool exit_if_block()
    {
        if (0 == this->size())
            return false;   // #endif without matching #if

        this->pop();
        return true;
    }

    bool get_status() const
    { 
        return 0 == this->size() || this->top().get_status(); 
    }

    bool get_some_part_status() const
    { 
        return 0 == this->size() || this->top().get_some_part_status(); 
    }

    bool get_enclosing_status() const
    {
        return 0 == this->size() || this->top().get_enclosing_status();
    }


    size_type get_if_block_depth() const { return this->size(); }

    bool is_inside_ifpart() const
    {
        return 0 != this->size() && !this->top().get_in_else();
    }

    bool is_inside_elsepart() const
    {
        return 0 != this->size() && this->top().get_in_else();
    }

        pattern_and(CharT pattern_, unsigned long pattern_mask_ = 0UL)
        :   pattern(pattern_), 
            pattern_mask((0UL != pattern_mask_) ? 
                pattern_mask_ : (unsigned long)pattern_)
        {}


        template <typename T>
        bool test(T pattern_) const
        { return ((unsigned long)pattern_ & pattern_mask) == (unsigned long)pattern; }


    template <typename CharT>
    inline pattern_and<CharT>
    pattern_p(CharT pattern, unsigned long pattern_mask = 0UL)
    { return pattern_and<CharT>(pattern, pattern_mask); }


    macro_definition(TokenT const &token_, bool has_parameters, 
            bool is_predefined_, long uid_)
    :   macroname(token_), uid(uid_), is_functionlike(has_parameters), 
        replaced_parameters(false), is_available_for_replacement(true),
        is_predefined(is_predefined_)
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
        , has_ellipsis(false)
#endif
        , use_count(0)
    {
    }

    void replace_parameters()
    {
        using namespace boost::wave;

        if (!replaced_parameters) {
        typename definition_container_type::iterator end = macrodefinition.end();
        typename definition_container_type::iterator it = macrodefinition.begin(); 

            for (/**/; it != end; ++it) {
            token_id id = *it;

                if (T_IDENTIFIER == id || 
                    IS_CATEGORY(id, KeywordTokenType) ||
                    IS_EXTCATEGORY(id, OperatorTokenType|AltExtTokenType) ||
                    IS_CATEGORY(id, OperatorTokenType)) 
                {
                // may be a parameter to replace
                    const_parameter_iterator_t cend = macroparameters.end();
                    const_parameter_iterator_t cit = macroparameters.begin();
                    for (typename parameter_container_type::size_type i = 0; 
                        cit != cend; ++cit, ++i) 
                    {
                        if ((*it).get_value() == (*cit).get_value()) {
                            (*it).set_token_id(token_id(T_PARAMETERBASE+i));
                            break;
                        }
#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0
                        else if (T_ELLIPSIS == token_id(*cit) && 
                            "__VA_ARGS__" == (*it).get_value()) 
                        {
                        // __VA_ARGS__ requires special handling
                            (*it).set_token_id(token_id(T_EXTPARAMETERBASE+i));
                            break;
                        }
#endif
                    }
                }
            }

#if BOOST_WAVE_SUPPORT_VARIADICS_PLACEMARKERS != 0 
        // we need to know, if the last of the formal arguments is an ellipsis
            if (macroparameters.size() > 0 &&
                T_ELLIPSIS == token_id(macroparameters.back())) 
            {
                has_ellipsis = true;
            }
#endif 
            replaced_parameters = true;     // do it only once
        }
    }

template <typename TokenT, typename ContainerT>
inline void
intrusive_ptr_add_ref(macro_definition<TokenT, ContainerT>* p)
{
    ++p->use_count;
}


template <typename TokenT, typename ContainerT>
inline void
intrusive_ptr_release(macro_definition<TokenT, ContainerT>* p)
{
    if (--p->use_count == 0)
        delete p;
}


    template <class AdaptableUnaryFunctionT, class IteratorT>
    inline 
    typename ref_transform_iterator_generator<
        AdaptableUnaryFunctionT, IteratorT>::type
    make_ref_transform_iterator(
        IteratorT base, AdaptableUnaryFunctionT const &f)
    {
        typedef typename ref_transform_iterator_generator<
                AdaptableUnaryFunctionT, IteratorT>::type
            iterator_type;
        return iterator_type(base, f.transform);
    }


        static result_type
        transform (argument_type node) 
        {
            BOOST_ASSERT(1 == std::distance(node.value.begin(), 
                node.value.end()));
            return *node.value.begin();
        }


    symbol_table(long uid_ = 0) 
    {}


        template <typename First, typename Second>
        StringT1 const& operator() (std::pair<First, Second> const& p) const
        {
            return p.first;
        }
