
    log_entry_data()
    {
        m_file_name.reserve( 200 );
    }


    void clear()
    {
        m_file_name.erase();
        m_line_num      = 0;
        m_level     = log_nothing;
    }


    void clear()
    {
        m_file_name.clear();
        m_line_num    = 0;
        m_message = std::string();
    }

    virtual             ~unit_test_log_formatter() {}


    virtual void        log_exception( std::ostream& os, log_checkpoint_data const& cd, execution_exception const& ex )
    {
        // for backward compatibility
        log_exception( os, cd, ex.what() );
    }

    void    test_finish() {}


    void    test_unit_start( test_unit const& ) {}

    void    test_unit_aborted( test_unit const& ) {}


    void    assertion_result( bool ) {}

    void    exception_caught( execution_exception const& ) {}
 progress_monitor_t );

    mock_object_base() {}


    template<typename T1>
    mock_object_base( T1 const& ) {}


    template<typename T1, typename T2>
    mock_object_base( T1 const&, T2 const& ) {}


    template<typename T1, typename T2, typename T3>
    mock_object_base( T1 const&, T2 const&, T3 const& ) {}


    template<typename T1, typename T2, typename T3, typename T4>
    mock_object_base( T1 const&, T2 const&, T3 const&, T4 const& ) {}


    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object_base( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) {}
 void nonnull() {};

    mock_object( dummy* ) {}

    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }


    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }


    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }


    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }


    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }


    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }


    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }


    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }
bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
self_type const& operator op() const                        \
{                                                           \
    MO_OP_IMPL( op, descr, prototype() );                   \
}                                                           \
/**/

#define MO_UNARY_BOOL_OP( op, descr )                       bool operator op() const                                    \
{                                                           \
    MO_OP_IMPL( op, descr, (!!BOOST_ITEST_DPOINT()) );      \
}                                                           \
/**/

#define MO_BINARY_OP( op, descr )                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )

    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }

    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }

    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }

    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }

    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
                           template<int i1, typename Base1,int i2, typename Base2>     inline mock_object<i1,Base1> const&                         operator op( mock_object<i1,Base1> const& mo,               \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
MO_BINARY_OP( >>, "Right shift" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( mock_object<i,Base> const& mo, T const& )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
MO_BINARY_OP( >>, "Right shift" )
                                                           \
                                                            template<int i, typename Base, typename T>                  inline mock_object<i,Base> const&                           operator op( T const&, mock_object<i,Base> const& mo )      \
{                                                           \
    MO_OP_IMPL( op, descr, mo );                            \
}                                                           \
/**/

#define MO_BINARY_BOOL_OP( op, descr )                      template<int i1, typename Base1,int i2, typename Base2>     inline bool                                                 operator op( mock_object<i1,Base1> const&,                  \
             mock_object<i2,Base2> const& )                 \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( mock_object<i,Base> const&, T const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
                                                            template<int i, typename Base, typename T>                  inline bool                                                 operator op( T const&, mock_object<i,Base> const& )         \
{                                                           \
    MO_OP_IMPL( op, descr, BOOST_ITEST_DPOINT() );          \
}                                                           \
/**/

// ************************************************************************** //
// **************                  mock_object                 ************** //
// ************************************************************************** //

template<int i = 0, typename Base=mock_object_base>
class mock_object;

template<int i, typename Base>
class mock_object : public Base {
    // Private typeefs
    typedef mock_object<i,Base> self_type;
    struct dummy { void nonnull() {}; };
    typedef void (dummy::*safe_bool)();

    // prototype constructor
    mock_object( dummy* ) {}

public:
    static mock_object& prototype()
    {
        static mock_object p( reinterpret_cast<dummy*>(0) ); 
        return p;
    }

    // Constructors
    mock_object()
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object default constructor" );
    }

    template<typename T1>
    mock_object( T1 const& arg1 )
    : mock_object_base( arg1 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2>
    mock_object( T1 const& arg1, T2 const& arg2 )
    : mock_object_base( arg1, arg2 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3 )
    : mock_object_base( arg1, arg2, arg3 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4 )
    : mock_object_base( arg1, arg2, arg3, arg4 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    mock_object( T1 const& arg1, T2 const& arg2, T3 const& arg3, T4 const& arg4, T5 const& arg5 )
    : mock_object_base( arg1, arg2, arg3, arg4, arg5 )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object constructor" );
    }

    mock_object( mock_object const& )
    {
        BOOST_ITEST_SCOPE( mock_object::mock_object );
        BOOST_ITEST_EPOINT( "Mock object copy constructor" );
    }

    // assignment
    self_type const&    operator =( mock_object const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    template <typename T>
    self_type const&    operator =( T const& ) const
    {
        MO_OP_IMPL( =, "Copy assignment", prototype() );
    }

    // Unary operators
    MO_UNARY_BOOL_OP( !, "Logical NOT operator" )
    MO_UNARY_OP( &, "Address-of operator" )
    MO_UNARY_OP( ~, "One's complement operator" )
    MO_UNARY_OP( *, "Pointer dereference" )
    MO_UNARY_OP( +, "Unary plus" )

    // Increment and Decrement
    MO_UNARY_OP( ++, "Prefix increment" )
    MO_UNARY_OP( --, "Prefix decrement" )
    self_type const&    operator ++(int) const
    {
        MO_OP_IMPL( ++, "Postfix increment", prototype() );
    }
    self_type const&    operator --(int) const
    {
        MO_OP_IMPL( --, "Postfix decrement", prototype() );
    }

    // Bool context convertion
    operator safe_bool() const
    {
        MO_OP_IMPL( safe_bool, "Bool context conversion",
                    (BOOST_ITEST_DPOINT() ? 0 : &dummy::nonnull) );
    }

    // Function-call operators
    self_type const&    operator ()() const
    {
        MO_OP_IMPL( (), "0-arity function-call", prototype() );
    }
    template<typename T1>
    self_type const&    operator ()( T1 const& arg1 ) const
    {
        MO_OP_IMPL( (), "1-arity function-call", prototype() );
    }
    template<typename T1, typename T2>
    self_type const&    operator ()( T1 const&, T2 const& ) const
    {
        MO_OP_IMPL( (), "2-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const& ) const
    {
        MO_OP_IMPL( (), "3-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const& ) const
    {
        MO_OP_IMPL( (), "4-arity function-call", prototype() );
    }
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    self_type const&    operator ()( T1 const&, T2 const&, T3 const&, T4 const&, T5 const& ) const
    {
        MO_OP_IMPL( (), "5-arity function-call", prototype() );
    }

    // Substripting
    template<typename T>
    self_type const&    operator []( T const& ) const
    {
        MO_OP_IMPL( [], "Substripting", prototype() );
    }

    // Class member access
    self_type const*    operator->() const
    {
        MO_OP_IMPL( ->, "Class member access", this );
    }
};

// !! MO_BINARY_OP( BOOST_PP_COMMA(), "Comma operator" )

MO_BINARY_BOOL_OP( !=, "Inequality" )
MO_BINARY_OP( %, "Modulus" )
MO_BINARY_OP( %=, "Modulus/assignment" )
MO_BINARY_OP( &, "Bitwise AND" )
MO_BINARY_BOOL_OP( &&, "Logical AND" )
MO_BINARY_OP( &=, "Bitwise AND/assignment" )
MO_BINARY_OP( *, "Multiplication" )
MO_BINARY_OP( *=, "Multiplication/assignment" )
MO_BINARY_OP( +, "Addition" )
MO_BINARY_OP( +=, "Addition/assignment" )
//MO_BINARY_OP( -, "Subtraction" )
MO_BINARY_OP( -=, "Subtraction/assignment" )
MO_BINARY_OP( ->*, "Pointer-to-member selection" )
MO_BINARY_OP( /, "Division" )
MO_BINARY_OP( /=, "Division/assignment" )
MO_BINARY_BOOL_OP( <, "Less than" )
MO_BINARY_OP( <<=, "Left shift/assignment" )
MO_BINARY_BOOL_OP( <=, "Less than or equal to" )
MO_BINARY_BOOL_OP( ==, "Equality" )
MO_BINARY_BOOL_OP( >, "Greater than" )
MO_BINARY_BOOL_OP( >=, "Greater than or equal to" )
MO_BINARY_OP( >>=, "Right shift/assignment" )
MO_BINARY_OP( ^, "Exclusive OR" )
MO_BINARY_OP( ^=, "Exclusive OR/assignment" )
MO_BINARY_OP( |, "Bitwise inclusive OR" )
MO_BINARY_OP( |=, "Bitwise inclusive OR/assignment" )
MO_BINARY_BOOL_OP( ||, "Logical OR" )

MO_BINARY_OP( <<, "Left shift" )
MO_BINARY_OP( >>, "Right shift" )

    explicit    translate_exception_base( boost::scoped_ptr<translate_exception_base>& next )
    {
        next.swap( m_next );
    }

    virtual     ~translate_exception_base() {}

    error_code      code() const    { return m_error_code; }

    const_string    what() const    { return m_what; }

    location const& where() const   { return m_location; }

    execution_monitor()
    : p_catch_system_errors( true )
    , p_auto_start_dbg( false )
    , p_timeout( 0 )
    , p_use_alt_stack( true )
    , p_detect_fp_exceptions( false )
    {}

    explicit    translate_exception( ExceptionTranslator const& tr, base_ptr& next )
    : translate_exception_base( next ), m_translator( tr ) {}


    int operator()( unit_test::callback0<int> const& F )
    {
        try {
            return m_next ? (*m_next)( F ) : F();
        } catch( Exception const& e ) {
            m_translator( e );
            return boost::exit_exception_failure;
        }
    }


template<typename Exception, typename ExceptionTranslator>
void
execution_monitor::register_exception_translator( ExceptionTranslator const& tr, boost::type<Exception>* )
{
    m_custom_translators.reset( 
        new detail::translate_exception<Exception,ExceptionTranslator>( tr,m_custom_translators ) );
}

    begin( const_string fn, std::size_t ln )
    : m_file_name( fn )
    , m_line_num( ln )
    {}

    entry_value_collector() : m_last( true ) {}

    entry_value_collector( entry_value_collector const& rhs ) : m_last( true ) { rhs.m_last = false; }


    virtual int         priority() { return 1; }
 unit_test_log_t );

    static manager&     instance() { return *instance_ptr(); }

    virtual void        exception_point( const_string /*file*/, 
                                         std::size_t /*line_num*/, 
                                         const_string /*descr*/ ){}

    virtual bool        decision_point( const_string /*file*/, 
                                        std::size_t /*line_num*/ )          { return true; }

    virtual unsigned    enter_scope( const_string /*file*/, 
                                     std::size_t /*line_num*/,
                                     const_string /*scope_name*/){ return 0; }

    virtual void        leave_scope( unsigned )                             {}

    virtual void        allocated( const_string /*file*/, 
                                   std::size_t /*line_num*/, 
                                   void* /*p*/, std::size_t /*s*/ )         {}

    virtual void        freed( void* /*p*/ )                                {}

    virtual void        data_flow( const_string /*d*/ )                     {}

    virtual std::string return_value( const_string /*default_value */ )     { return ""; }


    template<typename T>
    void                generic_data_flow( T const& t )
    {
        wrap_stringstream ws;

        data_flow( (ws << t).str() );
    }

    template<typename T, typename DefaultValueType>
    T                   generic_return( DefaultValueType const& dv )
    {
        wrap_stringstream ws;

        std::string const& res = return_value( (ws << dv).str() );

        if( res.empty() )
            return dv;

        return lexical_cast<T>( res );
    }

    explicit manager( dummy_constr* ) {}

    scope_guard( const_string file, std::size_t line_num, const_string scope_name )
    {
        m_scope_index = manager::instance().enter_scope( file, line_num, scope_name );
    }

    ~scope_guard()
    {
        manager::instance().leave_scope( m_scope_index );
    }

    location( const_string file, std::size_t line ) 
    : m_file_name( file )
    , m_line_num( line )
    {}


inline void
operator delete( void* p, ::boost::itest::location const& )
{
    ::boost::itest::manager::instance().freed( p );

    std::free( p );
}


inline void
operator delete[]( void* p, ::boost::itest::location const& )
{
    ::boost::itest::manager::instance().freed( p );

    std::free( p );
}


inline void
operator delete( void* p ) throw()
{
    ::boost::itest::manager::instance().freed( p );

    std::free( p );
}


inline void
operator delete[]( void* p ) throw()
{
    ::boost::itest::manager::instance().freed( p );

    std::free( p );
}

template<typename FPT>
inline FPT
fpt_abs( FPT fpv ) 
{
    return fpv < static_cast<FPT>(0) ? -fpv : fpv;
}

    static FPT    min_value()
    {
        return std::numeric_limits<FPT>::is_specialized
                    ? (std::numeric_limits<FPT>::min)()
                    : 0;
    }

    static FPT    max_value()
    {
        return std::numeric_limits<FPT>::is_specialized
                    ? (std::numeric_limits<FPT>::max)()
                    : static_cast<FPT>(1000000); // for the our purpuses it doesn't really matter what value is returned here
    }

template<typename FPT>
inline FPT
safe_fpt_division( FPT f1, FPT f2 )
{
    // Avoid overflow.
    if( (f2 < static_cast<FPT>(1))  && (f1 > f2*fpt_limits<FPT>::max_value()) )
        return fpt_limits<FPT>::max_value();

    // Avoid underflow.
    if( (f1 == static_cast<FPT>(0)) ||
        ((f2 > static_cast<FPT>(1)) && (f1 < f2*fpt_limits<FPT>::min_value())) )
        return static_cast<FPT>(0);

    return f1/f2;
}

    explicit    percent_tolerance_t( FPT v ) : m_value( v ) {}


template<typename Out,typename FPT>
Out& operator<<( Out& out, percent_tolerance_t<FPT> t )
{
    return out << t.m_value;
}


template<typename FPT>
inline percent_tolerance_t<FPT>
percent_tolerance( FPT v )
{
    return percent_tolerance_t<FPT>( v );
}

    explicit fraction_tolerance_t( FPT v ) : m_value( v ) {}


template<typename Out,typename FPT>
Out& operator<<( Out& out, fraction_tolerance_t<FPT> t )
{
    return out << t.m_value;
}


template<typename FPT>
inline fraction_tolerance_t<FPT>
fraction_tolerance( FPT v )
{
    return fraction_tolerance_t<FPT>( v );
}

    template<typename ToleranceBaseType>
    explicit    close_at_tolerance( percent_tolerance_t<ToleranceBaseType>  tolerance, 
                                    floating_point_comparison_type          fpc_type = FPC_STRONG ) 
    : p_fraction_tolerance( tt_detail::fpt_abs( static_cast<FPT>(0.01)*tolerance.m_value ) )
    , p_strong_or_weak( fpc_type ==  FPC_STRONG )
    , m_report_modifier( 100. )
    {}

    template<typename ToleranceBaseType>
    explicit    close_at_tolerance( fraction_tolerance_t<ToleranceBaseType> tolerance, 
                                    floating_point_comparison_type          fpc_type = FPC_STRONG ) 
    : p_fraction_tolerance( tt_detail::fpt_abs( tolerance.m_value ) )
    , p_strong_or_weak( fpc_type ==  FPC_STRONG )
    , m_report_modifier( 1. )
    {}


    predicate_result        operator()( FPT left, FPT right ) const
    {
        FPT diff = tt_detail::fpt_abs( left - right );
        FPT d1   = tt_detail::safe_fpt_division( diff, tt_detail::fpt_abs( right ) );
        FPT d2   = tt_detail::safe_fpt_division( diff, tt_detail::fpt_abs( left ) );
        
        predicate_result res( p_strong_or_weak 
            ? (d1 <= p_fraction_tolerance.get() && d2 <= p_fraction_tolerance.get()) 
            : (d1 <= p_fraction_tolerance.get() || d2 <= p_fraction_tolerance.get()) );

        if( !res )
            res.message() << (( d1 <= p_fraction_tolerance.get() ? d2 : d1 ) * m_report_modifier);

        return res;
    }


    template<typename FPT1, typename FPT2, typename ToleranceBaseType>
    predicate_result
    operator()( FPT1 left, FPT2 right, percent_tolerance_t<ToleranceBaseType> tolerance, 
                floating_point_comparison_type fpc_type = FPC_STRONG ) const
    {
        // deduce "better" type from types of arguments being compared
        // if one type is floating and the second integral we use floating type and 
        // value of integral type is promoted to the floating. The same for float and double
        // But we don't want to compare two values of integral types using this tool.
        typedef typename numeric::conversion_traits<FPT1,FPT2>::supertype FPT;
        BOOST_STATIC_ASSERT( !is_integral<FPT>::value );

        close_at_tolerance<FPT> pred( tolerance, fpc_type );

        return pred( left, right );
    }

    template<typename FPT1, typename FPT2, typename ToleranceBaseType>
    predicate_result
    operator()( FPT1 left, FPT2 right, fraction_tolerance_t<ToleranceBaseType> tolerance, 
                floating_point_comparison_type fpc_type = FPC_STRONG ) const
    {
        // same as in a comment above
        typedef typename numeric::conversion_traits<FPT1,FPT2>::supertype FPT;
        BOOST_STATIC_ASSERT( !is_integral<FPT>::value );

        close_at_tolerance<FPT> pred( tolerance, fpc_type );

        return pred( left, right );
    }


    template<typename FPT>
    bool
    operator()( FPT fpv, FPT tolerance ) const
    {
        return tt_detail::fpt_abs( fpv ) < tt_detail::fpt_abs( tolerance );
    }

    virtual ~format() {}

inline void             confirmation_report( test_unit_id id = INV_TEST_UNIT_ID )   
{ make_report( CONFIRMATION_REPORT, id ); }

inline void             short_report( test_unit_id id = INV_TEST_UNIT_ID )
{ make_report( SHORT_REPORT, id ); }

inline void             detailed_report( test_unit_id id = INV_TEST_UNIT_ID )
{ make_report( DETAILED_REPORT, id ); }

inline void first_failed_assertion() {}








 results_collector_t );

    void    operator()( std::ostream& ostr, T const& t )
    {
        // avoid warning: 'boost::test_tools::<unnamed>::dummy_cond' defined but not used 
        if (::boost::test_tools::dummy_cond) {}

        typedef typename mpl::or_<is_array<T>,is_function<T>,is_abstract<T> >::type cant_use_nl;

        set_precision( ostr, cant_use_nl() );

        ostr << t; // by default print the value
    }


    void set_precision( std::ostream& ostr, mpl::false_ )
    {
        if( std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::radix == 2 )
            ostr.precision( 2 + std::numeric_limits<T>::digits * 301/1000 ); 
    }

    void    operator()( std::ostream& ostr, bool t )
    {
         ostr << std::boolalpha << t;
    }

    explicit    print_helper_t( T const& t ) : m_t( t ) {}


template<typename T>
inline print_helper_t<T> print_helper( T const& t )
{
    return print_helper_t<T>( t );
}


template<typename T>
inline std::ostream& 
operator<<( std::ostream& ostr, print_helper_t<T> const& ph )
{
    print_log_value<T>()( ostr, ph.m_t );

    return ostr;
}
                                                    template<typename Pred                                                              \
         BOOST_PP_REPEAT_ ## z( BOOST_PP_ADD( n, 1 ), TEMPL_PARAMS, _ )>            inline bool                                                                         check_frwd( Pred P, unit_test::lazy_ostream const& check_descr,                     \
            const_string file_name, std::size_t line_num,                           \
            tool_level tl, check_type ct                                            \
            BOOST_PP_REPEAT_ ## z( BOOST_PP_ADD( n, 1 ), FUNC_PARAMS, _ )           \
)                                                                                   \
{                                                                                   \
    return                                                                          \
    check_impl( P( BOOST_PP_REPEAT_ ## z( BOOST_PP_ADD( n, 1 ), PRED_PARAMS, _ ) ), \
                check_descr, file_name, line_num, tl, ct,                           \
                BOOST_PP_ADD( n, 1 )                                                \
                BOOST_PP_REPEAT_ ## z( BOOST_PP_ADD( n, 1 ), ARG_INFO, _ )          \
    );                                                                              \
}                                                                                   \
/**/

#ifndef BOOST_TEST_MAX_PREDICATE_ARITY
#define BOOST_TEST_MAX_PREDICATE_ARITY 5
#endif

BOOST_PP_REPEAT( BOOST_TEST_MAX_PREDICATE_ARITY, IMPL_FRWD, _ )


template <class Left, class Right>
predicate_result equal_impl( Left const& left, Right const& right )
{
    return left == right;
}

inline predicate_result equal_impl( char* left, char const* right ) { return equal_impl( static_cast<char const*>(left), static_cast<char const*>(right) ); }

inline predicate_result equal_impl( char const* left, char* right ) { return equal_impl( static_cast<char const*>(left), static_cast<char const*>(right) ); }

inline predicate_result equal_impl( char* left, char* right )       { return equal_impl( static_cast<char const*>(left), static_cast<char const*>(right) ); }

inline predicate_result equal_impl( wchar_t* left, wchar_t const* right ) { return equal_impl( static_cast<wchar_t const*>(left), static_cast<wchar_t const*>(right) ); }

inline predicate_result equal_impl( wchar_t const* left, wchar_t* right ) { return equal_impl( static_cast<wchar_t const*>(left), static_cast<wchar_t const*>(right) ); }

inline predicate_result equal_impl( wchar_t* left, wchar_t* right )       { return equal_impl( static_cast<wchar_t const*>(left), static_cast<wchar_t const*>(right) ); }

    template <typename Left, typename Right>
    inline predicate_result
    call_impl( Left const& left, Right const& right, mpl::false_ ) const
    {
        return equal_impl( left, right );
    }


    template <typename Left, typename Right>
    inline predicate_result
    call_impl( Left const& left, Right const& right, mpl::true_ ) const
    {
        return (*this)( right, &left[0] );
    }


    template <typename Left, typename Right>
    inline predicate_result
    operator()( Left const& left, Right const& right ) const
    {
        typedef typename is_array<Left>::type left_is_array;
        return call_impl( left, right, left_is_array() );
    }

    template <class Left, class Right>
    predicate_result operator()( Left const& left, Right const& right )
    {
        return !equal_impl_frwd()( left, right );
    }

    template <class Left, class Right>
    predicate_result operator()( Left const& left, Right const& right )
    {
        return left < right;
    }

    template <class Left, class Right>
    predicate_result operator()( Left const& left, Right const& right )
    {
        return left <= right;
    }

    template <class Left, class Right>
    predicate_result operator()( Left const& left, Right const& right )
    {
        return left > right;
    }

    template <class Left, class Right>
    predicate_result operator()( Left const& left, Right const& right )
    {
        return left >= right;
    }


template <typename Left, typename Right>
inline predicate_result
equal_coll_impl( Left left_begin, Left left_end, Right right_begin, Right right_end )
{
    predicate_result    res( true );
    std::size_t         pos = 0;

    for( ; left_begin != left_end && right_begin != right_end; ++left_begin, ++right_begin, ++pos ) {
        if( *left_begin != *right_begin ) {
            res = false;
            res.message() << "\nMismatch in a position " << pos << ": "  << *left_begin << " != " << *right_begin;
        }
    }

    if( left_begin != left_end ) {
        std::size_t r_size = pos;
        while( left_begin != left_end ) {
            ++pos;
            ++left_begin;
        }

        res = false;
        res.message() << "\nCollections size mismatch: " << pos << " != " << r_size;
    }

    if( right_begin != right_end ) {
        std::size_t l_size = pos;
        while( right_begin != right_end ) {
            ++pos;
            ++right_begin;
        }

        res = false;
        res.message() << "\nCollections size mismatch: " << l_size << " != " << pos;
    }

    return res;
}


template <class Left, class Right>
inline predicate_result
bitwise_equal_impl( Left const& left, Right const& right )
{
    predicate_result    res( true );

    std::size_t left_bit_size  = sizeof(Left)*CHAR_BIT;
    std::size_t right_bit_size = sizeof(Right)*CHAR_BIT;

    static Left const leftOne( 1 );
    static Right const rightOne( 1 );

    std::size_t total_bits = left_bit_size < right_bit_size ? left_bit_size : right_bit_size;

    for( std::size_t counter = 0; counter < total_bits; ++counter ) {
        if( ( left & ( leftOne << counter ) ) != ( right & ( rightOne << counter ) ) ) {
            res = false;
            res.message() << "\nMismatch in a position " << counter;
        }
    }

    if( left_bit_size != right_bit_size ) {
        res = false;
        res.message() << "\nOperands bit sizes mismatch: " << left_bit_size << " != " << right_bit_size;
    }

    return res;
}


inline unit_test::counter_t& errors_counter() { static unit_test::counter_t ec = 0; return ec; }


inline void
report_error( const char* msg, const char* file, int line, const_string func_name, bool is_msg = false )
{
    ++errors_counter();
    std::cerr << file << "(" << line << "): ";

    if( is_msg )
        std::cerr << msg;
    else
        std::cerr << "test " << msg << " failed";

    if( func_name != "(unknown)" )
        std::cerr << " in function: '" << func_name << "'";

    std::cerr << std::endl;
}


inline void
report_critical_error( const char* msg, const char* file, int line, const_string func_name, bool is_msg = false )
{
    report_error( msg, file, line, func_name, is_msg );

    throw boost::execution_aborted();
}

    caller( int argc, char** argv )
    : m_argc( argc ), m_argv( argv ) {}

    int operator()() { return test_main( m_argc, m_argv ); }


int BOOST_TEST_CALL_DECL main( int argc, char* argv[] )
{
    using namespace boost::minimal_test;

    try {
        ::boost::execution_monitor ex_mon;
        int run_result = ex_mon.execute( caller( argc, argv ) );

        BOOST_CHECK( run_result == 0 || run_result == boost::exit_success );
    }
    catch( boost::execution_exception const& exex ) {
        if( exex.code() != boost::execution_exception::no_error )
            BOOST_ERROR( (std::string( "exception \"" ).
                            append( exex.what().begin(), exex.what().end() ).
                            append( "\" caught" ) ).c_str() );
        std::cerr << "\n**** Testing aborted.";
    }

    if( boost::minimal_test::errors_counter() != 0 ) {
        std::cerr << "\n**** " << errors_counter()
                  << " error" << (errors_counter() > 1 ? "s" : "" ) << " detected\n";

        return boost::exit_test_failure;
    }

    std::cout << "\n**** no errors detected\n";
    
    return boost::exit_success;
}


    static bool is_critical_error( error_level e ) { return e <= fatal_error; }
 unit_test_monitor_t );










    callback0<> const&  test_func() const { return m_test_func; }

    ~test_case() {}

    std::size_t     size() const { return m_members.size(); }

    virtual     ~test_suite() {}

    master_test_suite_t() : test_suite( "Master Test Suite" )
    , argc( 0 )
    , argv( 0 )
    {}

    virtual void    visit( test_case const& )               {}

    virtual bool    test_suite_start( test_suite const& )   { return true; }

    virtual void    test_suite_finish( test_suite const& )  {}



inline void
traverse_test_tree( test_unit const& tu, test_tree_visitor& V )
{
    if( tu.p_type == tut_case )
        traverse_test_tree( static_cast<test_case const&>( tu ), V );
    else
        traverse_test_tree( static_cast<test_suite const&>( tu ), V );
}

    test_case_counter() : p_count( 0 ) {}





    virtual bool    test_suite_start( test_suite const& ts )    { return ts.p_enabled; }


    user_tc_method_invoker( shared_ptr<InstanceType> inst, TestMethod test_method )
    : m_inst( inst ), m_test_method( test_method ) {}


    void operator()() { ((*m_inst).*m_test_method)(); }


inline test_case*
make_test_case( callback0<> const& test_func, const_string tc_name )
{
    return new test_case( ut_detail::normalize_test_case_name( tc_name ), test_func );
}


template<typename UserTestCase, typename InstanceType>
inline test_case*
make_test_case( void (UserTestCase::*           test_method )(),
                const_string                    tc_name,
                boost::shared_ptr<InstanceType> user_test_case )
{
    return new test_case( ut_detail::normalize_test_case_name( tc_name ), 
                          ut_detail::user_tc_method_invoker<InstanceType,UserTestCase>( user_test_case, test_method ) );
}

    auto_tc_exp_fail() : m_value( 0 ) {}


    explicit    auto_tc_exp_fail( unsigned v )
    : m_value( v )
    {
        instance() = this;
    }


    static auto_tc_exp_fail*& instance() 
    {
        static auto_tc_exp_fail     inst; 
        static auto_tc_exp_fail*    inst_ptr = &inst; 

        return inst_ptr;
    }


    unsigned    value() const { return m_value; }

    global_fixture_impl(): m_fixure( 0 )    {}

    virtual void    test_start( counter_t ) { m_fixure = new F; }

    virtual void    test_finish()           { delete m_fixure; m_fixure = 0; }
 
    virtual void    test_aborted()          { delete m_fixure; m_fixure = 0; }

    void    operator()()    { TestCaseTemplate::run( (boost::type<TestType>*)0 ); }

    explicit    generate_test_case_4_type( const_string tc_name, Generator& G )
    : m_test_case_name( tc_name )
    , m_holder( G )
    {}


    template<typename TestType>
    void        operator()( mpl::identity<TestType> )
    {
        std::string full_name;
        assign_op( full_name, m_test_case_name, 0 );
        full_name += '<';
        full_name += typeid(TestType).name();
        if( boost::is_const<TestType>::value )
            full_name += " const";
        full_name += '>';

        m_holder.m_test_cases.push_back( 
            new test_case( full_name, test_case_template_invoker<TestCaseTemplate,TestType>() ) );
    }

    template_test_case_gen( const_string tc_name )
    {
        typedef generate_test_case_4_type<template_test_case_gen<TestCaseTemplate,TestTypesList>,
                                          TestCaseTemplate
        > single_test_gen;
        mpl::for_each<TestTypesList,mpl::make_identity<mpl::_> >( single_test_gen( tc_name, *this ) );
    }


    virtual test_unit* next() const
    {
        if( m_test_cases.empty() )
            return 0;
    
        test_unit* res = m_test_cases.front();
        m_test_cases.pop_front();

        return res;
    }

template<typename UnitType>
UnitType&               get( test_unit_id id )
{
    return static_cast<UnitType&>( get( id, static_cast<test_unit_type>(UnitType::type) ) );
}

    internal_error( const_string m ) : std::runtime_error( std::string( m.begin(), m.size() ) ) {}

    setup_error( const_string m ) : std::runtime_error( std::string( m.begin(), m.size() ) ) {}

    virtual void    test_start( counter_t /* test_cases_amount */ ) {}

    virtual void    test_finish() {}

    virtual void    test_aborted() {}


    virtual void    test_unit_start( test_unit const& ) {}

    virtual void    test_unit_finish( test_unit const&, unsigned long /* elapsed */ ) {}

    virtual void    test_unit_skipped( test_unit const& ) {}

    virtual void    test_unit_aborted( test_unit const& ) {}


    virtual void    assertion_result( bool /* passed */ ) {}

    virtual void    exception_caught( execution_exception const& ) {}


    virtual int     priority() { return 0; }

 void nonnull() {};

    predicate_result( bool pv_ ) 
    : p_predicate_value( pv_ )
    {}


    template<typename BoolConvertable>
    predicate_result( BoolConvertable const& pv_ ) : p_predicate_value( !!pv_ ) {}

    bool                operator!() const           { return !p_predicate_value; }

    void                operator=( bool pv_ )       { p_predicate_value.value = pv_; }

    operator            safe_bool() const           { return !!p_predicate_value ? &dummy::nonnull : 0; }





    bool                has_empty_message() const   { return !m_message; }

    wrap_stringstream&  message()
    {
        if( !m_message )
            m_message.reset( new wrap_stringstream );

        return *m_message;
    }

    const_string        message() const                   { return !m_message ? const_string() : const_string( m_message->str() ); }

    template<typename T>
    test_func_with_bound_param( callback1<ParamType> test_func, T const& param )
    : m_test_func( test_func )
    , m_param( param )
    {}


    void operator()() { m_test_func( m_param ); }

    param_test_case_generator( callback1<ParamType> const&  test_func,
                               const_string                 tc_name, 
                               ParamIter                    par_begin,
                               ParamIter                    par_end )
    : m_test_func( test_func )
    , m_tc_name( ut_detail::normalize_test_case_name( tc_name ) )
    , m_par_begin( par_begin )
    , m_par_end( par_end )
    {}


    virtual test_unit* next() const
    {
        if( m_par_begin == m_par_end )
            return (test_unit*)0;

        test_func_with_bound_param<ParamType> bound_test_func( m_test_func, *m_par_begin );
        test_unit* res = new test_case( m_tc_name, bound_test_func );

        ++m_par_begin;

        return res;
    }

    user_param_tc_method_invoker( shared_ptr<UserTestCase> inst, test_method test_method )
    : m_inst( inst ), m_test_method( test_method ) {}


    void operator()( ParamType p ) { ((*m_inst).*m_test_method)( p ); }


template<typename ParamType, typename ParamIter>
inline ut_detail::param_test_case_generator<
    BOOST_DEDUCED_TYPENAME remove_const<BOOST_DEDUCED_TYPENAME remove_reference<ParamType>::type>::type,ParamIter>
make_test_case( void (*test_func)( ParamType ),
                const_string  tc_name, 
                ParamIter     par_begin,
                ParamIter     par_end )
{
    typedef BOOST_DEDUCED_TYPENAME remove_const<BOOST_DEDUCED_TYPENAME remove_reference<ParamType>::type>::type param_value_type;
    return ut_detail::param_test_case_generator<param_value_type,ParamIter>( test_func, tc_name, par_begin, par_end );
}


template<typename UserTestCase,typename ParamType, typename ParamIter>
inline ut_detail::param_test_case_generator<
    BOOST_DEDUCED_TYPENAME remove_const<BOOST_DEDUCED_TYPENAME remove_reference<ParamType>::type>::type,ParamIter>
make_test_case( void (UserTestCase::*test_method )( ParamType ),
                const_string                           tc_name,
                boost::shared_ptr<UserTestCase> const& user_test_case,
                ParamIter                              par_begin,
                ParamIter                              par_end )
{
    typedef BOOST_DEDUCED_TYPENAME remove_const<BOOST_DEDUCED_TYPENAME remove_reference<ParamType>::type>::type param_value_type;
    return ut_detail::param_test_case_generator<param_value_type,ParamIter>( 
               ut_detail::user_param_tc_method_invoker<UserTestCase,ParamType>( user_test_case, test_method ), 
               tc_name,
               par_begin,
               par_end );
}


inline test_unit_type
test_id_2_unit_type( test_unit_id id )
{
    return (id & 0xFFFF0000) != 0 ? tut_case : tut_suite;
}


template <class T> inline void ignore_unused_variable_warning(const T&) {}


template <typename CharT, typename T>
inline basic_wrap_stringstream<CharT>&
operator<<( basic_wrap_stringstream<CharT>& targ, T const& t )
{
    targ.stream() << t;
    return targ;
}


template <typename CharT>
inline basic_wrap_stringstream<CharT>&
basic_wrap_stringstream<CharT>::ref()
{ 
    return *this;
}

                    class_property() : value( PropertyType() ) {}

    explicit        class_property( write_param_t init_value )
    : value( init_value ) {}

    operator        read_access_t() const   { return value; }

    read_access_t   get() const             { return value; }

    bool            operator!() const       { return !value; }

    address_res_t   operator&() const       { return &value; }

                    readwrite_property() : base_prop() {}

    explicit        readwrite_property( write_param_t init_value ) : base_prop( init_value ) {}

    void            set( write_param_t v )  { base_prop::value = v; }

    arrow_res_t     operator->()            { return boost::addressof( base_prop::value ); }

    const_arrow_res_t operator->() const    { return boost::addressof( base_prop::value ); }

    static id_t id() { return reinterpret_cast<id_t>( &inst() ); }


    static rttid const& inst() { static rttid s_inst;  return s_inst; }


template<typename T>   
inline id_t
type_id()
{
    return rtti_detail::rttid_holder<T>::id();
}

template<typename T,typename S>
inline void
assign_op( T& t, S const& s, long )
{
    t = s;
}

    template<typename Functor>
    R       invoke( Functor& f )                        { return f(); }

    template<typename Functor, typename T1>
    R       invoke( Functor& f, T1 t1 )                 { return f( t1 ); }

    template<typename Functor, typename T1, typename T2>
    R       invoke( Functor& f, T1 t1, T2 t2 )          { return f( t1, t2 ); }

    template<typename Functor, typename T1, typename T2, typename T3>
    R       invoke( Functor& f, T1 t1, T2 t2, T3 t3 )   { return f( t1, t2, t3 ); }

    template<typename Functor>
    unused  invoke( Functor& f )                        { f(); return unused(); }

    template<typename Functor, typename T1>
    unused  invoke( Functor& f, T1 t1 )                 { f( t1 ); return unused(); }

    template<typename Functor, typename T1, typename T2>
    unused  invoke( Functor& f, T1 t1, T2 t2 )          { f( t1, t2 ); return unused(); }

    template<typename Functor, typename T1, typename T2, typename T3>
    unused  invoke( Functor& f, T1 t1, T2 t2, T3 t3 )   { f( t1, t2, t3 ); return unused(); }

    virtual ~callback0_impl() {}

    explicit callback0_impl_t( Functor f ) : m_f( f ) {}


    virtual R invoke() { return invoker<R>().invoke( m_f ); }

    callback0() {}


    template<typename Functor>
    callback0( Functor f )
    : m_impl( new ut_detail::callback0_impl_t<R,Functor>( f ) ) {}

    
    void        operator=( callback0 const& rhs ) { m_impl = rhs.m_impl; }


    template<typename Functor>
    void        operator=( Functor f ) { m_impl.reset( new ut_detail::callback0_impl_t<R,Functor>( f ) );  }


    R           operator()() const { return m_impl->invoke(); }


    bool        operator!() const { return !m_impl; }

    virtual ~callback1_impl() {}

    explicit callback1_impl_t( Functor f ) : m_f( f ) {}


    virtual R invoke( T1 t1 ) { return invoker<R>().invoke( m_f, t1 ); }

    callback1() {}


    template<typename Functor>
    callback1( Functor f )
    : m_impl( new ut_detail::callback1_impl_t<R,T1,Functor>( f ) ) {}


    void        operator=( callback1 const& rhs ) { m_impl = rhs.m_impl; }


    template<typename Functor>
    void        operator=( Functor f ) { m_impl.reset( new ut_detail::callback1_impl_t<R,T1,Functor>( f ) );  }


    R           operator()( T1 t1 ) const { return m_impl->invoke( t1 ); }


    bool        operator!() const { return !m_impl; }

    virtual ~callback2_impl() {}

    explicit callback2_impl_t( Functor f ) : m_f( f ) {}


    virtual R invoke( T1 t1, T2 t2 ) { return invoker<R>().template invoke<Functor,T1,T2>( m_f, t1, t2 ); }

    callback2() {}


    template<typename Functor>
                callback2( Functor f ) : m_impl( new ut_detail::callback2_impl_t<R,T1,T2,Functor>( f ) ) {}


    void        operator=( callback2 const& rhs ) { m_impl = rhs.m_impl; }


    template<typename Functor>
    void        operator=( Functor f ) { m_impl.reset( new ut_detail::callback2_impl_t<R,T1,T2,Functor>( f ) );  }


    R           operator()( T1 t1, T2 t2 ) const { return m_impl->invoke( t1, t2 ); }


    bool        operator!() const { return !m_impl; }

    virtual ~callback3_impl() {}

    explicit callback3_impl_t( Functor f ) : m_f( f ) {}


    virtual R invoke( T1 t1, T2 t2, T3 t3 ) { return invoker<R>().invoke( m_f, t1, t2, t3 ); }

    callback3() {}


    template<typename Functor>
    callback3( Functor f )
    : m_impl( new ut_detail::callback3_impl_t<R,T1,T2,T3,Functor>( f ) ) {}


    void        operator=( callback3 const& rhs ) { m_impl = rhs.m_impl; }


    template<typename Functor>
    void        operator=( Functor f ) { m_impl.reset( new ut_detail::callback3_impl_t<R,T1,T2,T3,Functor>( f ) );  }


    R           operator()( T1 t1, T2 t2, T3 t3 ) const { return m_impl->invoke( t1, t2, t3 ); }


    bool        operator!() const { return !m_impl; }

    static Derived& instance() { static Derived the_inst; return the_inst; }

    singleton()  {}

    ~singleton() {}


inline void 
report_access_to_invalid_parameter()
{
    throw access_to_invalid_parameter();
}

    template<typename T>
#if defined(__GNUC__) || defined(__HP_aCC) || defined(__EDG__) || defined(__SUNPRO_CC)
    operator T() const
#else
    operator T const&() const
#endif
    { report_access_to_invalid_parameter(); static T* v = 0; return *v; }


    template<typename T>
    T any_cast() const
    { report_access_to_invalid_parameter(); static typename remove_reference<T>::type* v = 0; return *v; }


    template<typename Arg1>
    nil operator()( Arg1 const& )
    { report_access_to_invalid_parameter(); return nil(); }


    template<typename Arg1,typename Arg2>
    nil operator()( Arg1 const&, Arg2 const& )
    { report_access_to_invalid_parameter(); return nil(); }


    template<typename Arg1,typename Arg2,typename Arg3>
    nil operator()( Arg1 const&, Arg2 const&, Arg3 const& )
    { report_access_to_invalid_parameter(); return nil(); }

    template<typename Visitor>
    void            apply_to( Visitor& V ) const {}


    static nil&     inst() { static nil s_inst; return s_inst; }

    nil() {}

    template<typename NP>
    named_parameter_combine<NP,Derived>
    operator,( NP const& np ) const { return named_parameter_combine<NP,Derived>( np, *static_cast<Derived const*>(this) ); }

    named_parameter_combine( NP const& np, Rest const& r )
    : Rest( r )
    , m_param( np )
    {}

    res_type    operator[]( keyword<typename NP::id,true> kw ) const    { return m_param[kw]; }

    res_type    operator[]( keyword<typename NP::id,false> kw ) const   { return m_param[kw]; }


    bool        has( keyword<typename NP::id,false> kw ) const          { return m_param.has( kw ); }


    void        erase( keyword<typename NP::id,false> kw ) const        { m_param.erase( kw ); }

    template<typename Visitor>
    void            apply_to( Visitor& V ) const
    {
        m_param.apply_to( V );

        Rest::apply_to( V );
    }

    explicit        named_parameter( ref_type v ) 
    : m_value( v )
    , m_erased( false )
    {}

    named_parameter( named_parameter const& np )
    : m_value( np.m_value )
    , m_erased( np.m_erased )
    {}

    ref_type        operator[]( keyword<unique_id,true> ) const     { return m_erased ? nil_t::inst().template any_cast<ref_type>() :  m_value; }

    ref_type        operator[]( keyword<unique_id,false> ) const    { return m_erased ? nil_t::inst().template any_cast<ref_type>() :  m_value; }

    template<typename UnknownId>
    nil_t           operator[]( keyword<UnknownId,false> ) const    { return nil_t::inst(); }


    bool            has( keyword<unique_id,false> ) const           { return !m_erased; }

    template<typename UnknownId>
    bool            has( keyword<UnknownId,false> ) const           { return false; }


    void            erase( keyword<unique_id,false> ) const         { m_erased = true; }

    template<typename UnknownId>
    void            erase( keyword<UnknownId,false> ) const         {}

    template<typename Visitor>
    void            apply_to( Visitor& V ) const
    {
        V.set_parameter( rtti::type_id<unique_id>(), m_value );
    }


    template<typename T>
    named_parameter<T const,unique_id>
    operator=( T const& t ) const       { return named_parameter<T const,unique_id>( t ); }


    named_parameter<char const*,unique_id,char const*>
    operator=( char const* t ) const   { return named_parameter<char const*,unique_id,char const*>( t ); }

    named_parameter<T const,unique_id>
    operator=( T const& t ) const       { return named_parameter<T const,unique_id>( t ); }


    typed_keyword() : named_parameter<bool,unique_id,bool>( true ) {}


    named_parameter<bool,unique_id,bool>
    operator!() const           { return named_parameter<bool,unique_id,bool>( false ); }


template<typename T>
inline void
optionally_assign( T&, nfp_detail::nil )
{
    nfp_detail::report_access_to_invalid_parameter();
}


template<typename T, typename Source>
inline void
#if BOOST_WORKAROUND( __MWERKS__, BOOST_TESTED_AT( 0x3003 ) ) \
    || BOOST_WORKAROUND( __DECCXX_VER, BOOST_TESTED_AT(60590042) )
optionally_assign( T& target, Source src )
#else
optionally_assign( T& target, Source const& src )
#endif
{
    using namespace unit_test;

    assign_op( target, src, static_cast<int>(0) );
}


template<typename T, typename Params, typename Keyword>
inline void
optionally_assign( T& target, Params const& p, Keyword k )
{
    if( p.has(k) )
        optionally_assign( target, p[k] );
}


inline void
print_escaped( std::ostream& where_to, const_string value )
{
    static fixed_mapping<char,char const*> char_type(
        '<' , "lt",
        '>' , "gt",
        '&' , "amp",
        '\'', "apos" ,
        '"' , "quot",

        0
    );

    BOOST_TEST_FOREACH( char, c, value ) {
        char const* ref = char_type[c];

        if( ref )
            where_to << '&' << ref << ';';
        else
            where_to << c;
    }
}

    static lazy_ostream&    instance()                                              { static lazy_ostream inst; return inst; }

    bool                    empty() const                                           { return m_empty; }

    virtual std::ostream&   operator()( std::ostream& ostr ) const                  { return ostr; }

    explicit                lazy_ostream( bool empty = true ) : m_empty( empty )    {}


    lazy_ostream_impl( lazy_ostream const& prev, T value )
    : lazy_ostream( false )
    , m_prev( prev )
    , m_value( value )
    {}

    virtual std::ostream&   operator()( std::ostream& ostr ) const
    {
        return m_prev(ostr) << m_value;
    }


template<typename T>
inline lazy_ostream_impl<T const&>
operator<<( lazy_ostream const& prev, T const& v )
{
    return lazy_ostream_impl<T const&>( prev, v );
}


template<typename R,typename S>
inline lazy_ostream_impl<R& (BOOST_TEST_CALL_DECL *)(S&)>
operator<<( lazy_ostream const& prev, R& (BOOST_TEST_CALL_DECL *man)(S&) )
{
    return lazy_ostream_impl<R& (BOOST_TEST_CALL_DECL *)(S&)>( prev, man );
}

    explicit custom_printer( std::ostream& ostr ) : m_ostr( &ostr ) {}


    std::ostream& operator*() const { return *m_ostr; }


template<typename Uniq>
inline custom_printer<custom_manip<Uniq> >
operator<<( std::ostream& ostr, custom_manip<Uniq> const& ) { return custom_printer<custom_manip<Uniq> >( ostr ); }

    operator bool() const { return false; }

    static_any( Iter const& t ) : m_it( t ) {}


template<typename Iter>
inline Iter&
static_any_cast( static_any_t a, Iter* = 0 )
{
    return static_cast<Iter&>( static_cast<static_any<Iter> const&>( a ).m_it );
}


template<typename C>
inline is_const<C>
is_const_coll( C& )
{
    return is_const<C>();
}


template<typename C>
inline static_any<BOOST_DEDUCED_TYPENAME C::iterator>
begin( C& t, mpl::false_ )
{
    return static_any<BOOST_DEDUCED_TYPENAME C::iterator>( t.begin() );
}


template<typename C>
inline static_any<BOOST_DEDUCED_TYPENAME C::const_iterator>
begin( C const& t, mpl::true_ )
{
    return static_any<BOOST_DEDUCED_TYPENAME C::const_iterator>( t.begin() );
}


template<typename C>
inline static_any<BOOST_DEDUCED_TYPENAME C::iterator>
end( C& t, mpl::false_ )
{
    return static_any<BOOST_DEDUCED_TYPENAME C::iterator>( t.end() );
}


template<typename C>
inline static_any<BOOST_DEDUCED_TYPENAME C::const_iterator>
end( C const& t, mpl::true_ )
{
    return static_any<BOOST_DEDUCED_TYPENAME C::const_iterator>( t.end() );
}


template<typename C>
inline bool
done( static_any_t cur, static_any_t end, C&, mpl::false_ )
{
    return  static_any_cast<BOOST_DEDUCED_TYPENAME C::iterator>( cur ) ==
            static_any_cast<BOOST_DEDUCED_TYPENAME C::iterator>( end );
}


template<typename C>
inline bool
done( static_any_t cur, static_any_t end, C const&, mpl::true_ )
{
    return  static_any_cast<BOOST_DEDUCED_TYPENAME C::const_iterator>( cur ) ==
            static_any_cast<BOOST_DEDUCED_TYPENAME C::const_iterator>( end );
}


template<typename C>
inline void
next( static_any_t cur, C&, mpl::false_ )
{
    ++static_any_cast<BOOST_DEDUCED_TYPENAME C::iterator>( cur );
}


template<typename C>
inline void
next( static_any_t cur, C const&, mpl::true_ )
{
    ++static_any_cast<BOOST_DEDUCED_TYPENAME C::const_iterator>( cur );
}


template<class RefType,typename C>
inline RefType
deref( static_any_t cur, C&, ::boost::type<RefType>, mpl::false_ )
{
    return *static_any_cast<BOOST_DEDUCED_TYPENAME C::iterator>( cur );
}


template<class RefType,typename C>
inline RefType
deref( static_any_t cur, C const&, ::boost::type<RefType>, mpl::true_ )
{
    return *static_any_cast<BOOST_DEDUCED_TYPENAME C::const_iterator>( cur );
}

    argument( parameter const& p, rtti::id_t value_type )
    : p_formal_parameter( p )
    , p_value_type( value_type )
    {}

    virtual     ~argument()  {}

    explicit typed_argument( parameter const& p )
    : argument( p, rtti::type_id<T>() )
    {}

    typed_argument( parameter const& p, T const& t )
    : argument( p, rtti::type_id<T>() )
    , p_value( t )
    {}


template<typename T>
inline T const&
arg_value( argument const& arg_ )
{
    assert( arg_.p_value_type == rtti::type_id<T>() ); // detect logic error

    return static_cast<typed_argument<T> const&>( arg_ ).p_value.value;
}


template<typename T>
inline T&
arg_value( argument& arg_ )
{
    assert( arg_.p_value_type == rtti::type_id<T>() ); // detect logic error

    return static_cast<typed_argument<T>&>( arg_ ).p_value.value;
}

    config_source()     {}

    ~config_source()    {}


    void    use( config_source const& )
    {

    }

    explicit    logic_error( cstring msg ) : m_msg( new dstring( msg.begin(), msg.size() ) ) {}

    ~logic_error() throw()                          {}


    dstring const&   msg() const                    { return *m_msg; }

    virtual char_type const* what() const throw()   { return m_msg->c_str(); }


inline void
report_logic_error( format_stream& msg )
{
    throw BOOST_RT_PARAM_NAMESPACE::logic_error( msg.str() );
}

    virtual ~parameter() {}

inline void
putenv_impl( cstring name, cstring value )
{
    format_stream fs;

    fs << name << '=' << value;

    // !! this may actually fail. What should we do?
    // const_cast is used to satisfy putenv interface
    using namespace std;
    putenv( const_cast<char*>( fs.str().c_str() ) );
}

    static bool _( cstring source, boost::optional<T>& res )
    {
        BOOST_RT_PARAM_TRACE( "In interpret_argument_value_impl<" << typeid(T).name() << ">" );

        res = lexical_cast<T>( source );

        BOOST_RT_PARAM_TRACE( "String " << source << " is interpreted as " << *res );
        return true;
    }

    static bool _( cstring source, boost::optional<dstring>& res )
    {
        BOOST_RT_PARAM_TRACE( "In interpret_argument_value_impl<dstring>" );

        res = dstring();
        assign_op( *res, source, 0 );

        return true;
    }

    static bool _( cstring source, boost::optional<cstring>& res )
    {
        BOOST_RT_PARAM_TRACE( "In interpret_argument_value_impl<cstring>" );

        res = source;

        return true;
    }

    static bool _( cstring source, boost::optional<bool>& res )
    {
        BOOST_RT_PARAM_TRACE( "In interpret_argument_value_impl<bool>" );

        static literal_cstring YES( BOOST_RT_PARAM_CSTRING_LITERAL( "YES" ) );
        static literal_cstring Y( BOOST_RT_PARAM_CSTRING_LITERAL( "Y" ) );
        static literal_cstring NO( BOOST_RT_PARAM_CSTRING_LITERAL( "NO" ) );
        static literal_cstring N( BOOST_RT_PARAM_CSTRING_LITERAL( "N" ) );
        static literal_cstring one( BOOST_RT_PARAM_CSTRING_LITERAL( "1" ) );
        static literal_cstring zero( BOOST_RT_PARAM_CSTRING_LITERAL( "0" ) );

        source.trim();

        if( case_ins_eq( source, YES ) || case_ins_eq( source, Y ) || case_ins_eq( source, one ) ) {
            res = true;
            return true;
        }
        else if( case_ins_eq( source, NO ) || case_ins_eq( source, N ) || case_ins_eq( source, zero ) ) {
            res = false;
            return true;
        }
        else {
            res = true;
            return false;
        }
    }


template<typename T>
inline bool
interpret_argument_value( cstring source, boost::optional<T>& res, long )
{
    return interpret_argument_value_impl<T>::_( source, res );
}

    trivial_id_policy()
    : identification_policy( rtti::type_id<trivial_id_policy>() )
    {}



    virtual bool    responds_to( cstring name ) const                       { return m_name == name; }

    virtual bool    conflict_with( identification_policy const& ) const     { return false; }

    virtual cstring id_2_report() const                                     { return m_name; }

    virtual void    usage_info( format_stream& fs ) const
    { 
        if( !m_name.empty() )
            fs << BOOST_RT_PARAM_LITERAL( '<' ) << m_name << BOOST_RT_PARAM_LITERAL( '>' );
        else
            fs << BOOST_RT_PARAM_CSTRING_LITERAL( "<value>" );
    }


    virtual bool    matching( parameter const& p, argv_traverser&, bool primary ) const
    {
        return primary && ( !p.has_argument() || p.p_multiplicable );
    }


    template<typename Modifier>
    void            accept_modifier( Modifier const& m )
    {
        nfp::optionally_assign( m_name, m, name );
    }

    explicit    positional_parameter_t( cstring name )
    : base( name )
    {}


    explicit typed_parameter( identification_policy& ID ) 
    : cla::parameter( ID, m_arg_factory, rtti::type_id<T>() == rtti::type_id<bool>() ) 
    {}

    template<typename Modifier>
    void    accept_modifier( Modifier const& m )
    {
        cla::parameter::accept_modifier( m );

        m_arg_factory.accept_modifier( m );

        BOOST_RT_PARAM_VALIDATE_LOGIC( !p_optional || !m_arg_factory.m_value_generator,
            BOOST_RT_PARAM_LITERAL( "can't define a value generator for optional parameter " ) << id_2_report() );
    }

    template<typename T>
    void operator()( argv_traverser& tr, boost::optional<T>& value )
    {
        if( interpret_argument_value( tr.token(), value, 0 ) )
            tr.next_token();
    }

    typed_argument_factory()
    : m_value_interpreter( rt_cla_detail::default_value_interpreter() )
    {}


    template<typename Modifier>
    void                accept_modifier( Modifier const& m )
    {
        optionally_assign( m_value_handler, m, handler );
        optionally_assign( m_value_interpreter, m, interpreter );

        if( m.has( default_value ) ) {
            BOOST_RT_PARAM_VALIDATE_LOGIC( !m_value_generator, 
                BOOST_RT_PARAM_LITERAL( "multiple value generators for parameter" ) );

            T const& dv_ref = m[default_value];
            m_value_generator = rt_cla_detail::const_generator<T>( dv_ref );
        }

        if( m.has( default_refer_to ) ) {
            BOOST_RT_PARAM_VALIDATE_LOGIC( !m_value_generator, 
                BOOST_RT_PARAM_LITERAL( "multiple value generators for parameter" ) );

            cstring ref_id = m[default_refer_to];
            m_value_generator = rt_cla_detail::ref_generator<T>( ref_id );
        }

        if( m.has( assign_to ) ) {
            BOOST_RT_PARAM_VALIDATE_LOGIC( !m_value_handler, 
                BOOST_RT_PARAM_LITERAL( "multiple value handlers for parameter" ) );

            m_value_handler = rt_cla_detail::assigner<T>( m[assign_to] );
        }
    }


template<typename T>
inline argument_ptr
typed_argument_factory<T>::produce_using( parameter& p, argv_traverser& tr )
{
    boost::optional<T> value;

    try {
        m_value_interpreter( tr, value );
    }
    catch( ... ) { // !! should we do that?
        BOOST_RT_PARAM_TRACE( "Fail to parse argument value" );

        if( !p.p_optional_value )
            throw;
    }

    argument_ptr actual_arg = p.actual_argument();

    BOOST_RT_CLA_VALIDATE_INPUT( !!value || p.p_optional_value, tr, 
        BOOST_RT_PARAM_LITERAL( "Argument value missing for parameter " ) << p.id_2_report() );

    BOOST_RT_CLA_VALIDATE_INPUT( !actual_arg || p.p_multiplicable, tr, 
        BOOST_RT_PARAM_LITERAL( "Unexpected repetition of the parameter " ) << p.id_2_report() );

    if( !!value && !!m_value_handler )
        m_value_handler( p, *value );

    if( !p.p_multiplicable )
        actual_arg.reset( p.p_optional_value && (rtti::type_id<T>() != rtti::type_id<bool>())
            ? static_cast<argument*>(new typed_argument<boost::optional<T> >( p, value ))
            : static_cast<argument*>(new typed_argument<T>( p, *value )) );
    else {
        typedef std::list<boost::optional<T> > optional_list;

        if( !actual_arg )
            actual_arg.reset( p.p_optional_value 
                ? static_cast<argument*>(new typed_argument<optional_list>( p ))
                : static_cast<argument*>(new typed_argument<std::list<T> >( p )) );

        if( p.p_optional_value ) {
            optional_list& values = arg_value<optional_list>( *actual_arg );

            values.push_back( value );
        }
        else {
            std::list<T>& values = arg_value<std::list<T> >( *actual_arg );
            
            values.push_back( *value );
        }
    }

    return actual_arg;
}


template<typename T>
inline argument_ptr 
typed_argument_factory<T>::produce_using( parameter& p, parser const& pa )
{
    argument_ptr actual_arg;

    if( !m_value_generator )
        return actual_arg;

    boost::optional<T> value;
    m_value_generator( pa, value );

    if( !value )
        return actual_arg;

    if( !!m_value_handler )
        m_value_handler( p, *value );

    actual_arg.reset( new typed_argument<T>( p, *value ) );

    return actual_arg;
}


template<typename T>
inline void
typed_argument_factory<T>::argument_usage_info( format_stream& fs )
{
    rt_cla_detail::argument_value_usage( fs, 0, reinterpret_cast<T*>(0) );
}

    explicit    basic_parameter( cstring n ) 
    : base_from_member<IdPolicy>()
    , typed_parameter<T>( base_from_member<IdPolicy>::member )
    {
        this->accept_modifier( name = n );
    }

    template<typename Modifier>
    void        accept_modifier( Modifier const& m )
    {
        typed_parameter<T>::accept_modifier( m );

        base_from_member<IdPolicy>::member.accept_modifier( m );
    }

    explicit    assigner( T& loc ) : m_target( loc )    {}

    void        operator()( parameter const&, T& t )  { m_target = t; }

    parameter( identification_policy& ID, argument_factory& F, bool optional_value = false )
    : p_optional( false )
    , p_multiplicable( false )
    , p_optional_value( optional_value )
    , m_id_policy( ID )
    , m_arg_factory( F )
    {}

    virtual         ~parameter()                                {}

    template<typename Modifier>
    void            accept_modifier( Modifier const& m )
    {
        if( m.has( optional_m ) )
            p_optional.value = true;

        if( m.has( required_m ) )
            p_optional.value = false;

        if( m.has( multiplicable_m ) )
            p_multiplicable.value = true;

        if( m.has( optional_value_m ) )
            p_optional_value.value = true;

        nfp::optionally_assign( p_description.value, m, description );
    }

    bool            has_argument() const                        { return m_actual_argument!=0; }

    argument const& actual_argument() const                     { return *m_actual_argument; }

    argument_ptr    actual_argument()                           { return m_actual_argument; }

    bool            responds_to( cstring name ) const           { return m_id_policy.responds_to( name ); }

    bool            conflict_with( parameter const& p ) const
    {
        return (id_2_report() == p.id_2_report() && !id_2_report().is_empty())  ||
               m_id_policy.conflict_with( p.m_id_policy )                       || 
               ((m_id_policy.p_type_id != p.m_id_policy.p_type_id) && p.m_id_policy.conflict_with( m_id_policy ));
    }

    cstring         id_2_report() const                         { return m_id_policy.id_2_report(); }

    void            usage_info( format_stream& fs ) const
    { 
        m_id_policy.usage_info( fs );
        if( p_optional_value )
            fs << BOOST_RT_PARAM_LITERAL( '[' );

        m_arg_factory.argument_usage_info( fs );

        if( p_optional_value )
            fs << BOOST_RT_PARAM_LITERAL( ']' );
    }

    bool            matching( argv_traverser& tr, bool primary ) const
    {
        return m_id_policy.matching( *this, tr, primary );
    }

    void            produce_argument( argv_traverser& tr )
    {
        m_id_policy.matching( *this, tr, true ); // !! can we save this position somehow
        m_actual_argument = m_arg_factory.produce_using( *this, tr );
    }

    void            produce_argument( parser const& p )
    {
        m_actual_argument = m_arg_factory.produce_using( *this, p );
    }


template<typename Parameter,typename Modifier>
inline shared_ptr<Parameter>
operator-( shared_ptr<Parameter> p, Modifier const& m )
{
    p->accept_modifier( m );

    return p;
}

    explicit    const_generator( T const& t ) : m_const_value( t ) {}

    void        operator()( parser const&, boost::optional<T>& t ) const   { t = m_const_value; }

    explicit    ref_generator( cstring ref_id ) : m_ref_id( ref_id ) {}

    void        operator()( parser const& p, boost::optional<T>& t ) const
    {
        p.get( m_ref_id, t );
    }

template<typename T>
inline void
argument_value_usage( format_stream& fs, long, T* = 0 )
{
    fs << BOOST_RT_PARAM_CSTRING_LITERAL( "<value>" );
}

inline void
argument_value_usage( format_stream& fs,  int, bool* = 0 )
{
    fs << BOOST_RT_PARAM_CSTRING_LITERAL( "yes|y|no|n" );
}


    explicit        identification_policy( rtti::id_t dyn_type )
    : p_type_id( dyn_type )
    {}


                    config_file_iterator() {}

    explicit        config_file_iterator( cstring file_name )
    {
        construct();
        load( file_name );
    }

    template<typename Modifiers>
                    config_file_iterator( cstring file_name, Modifiers const& m )
    {
        construct();
        m.apply_to( *this );
        load( file_name );
    }

    config_file_iterator( config_file_iterator const& rhs )
    : base( rhs )
    , m_pimpl( rhs.m_pimpl )
    {
        rhs.m_valid = false;
    }


    void operator=( config_file_iterator const& rhs )
    {
        if( this == &rhs )
            return;

        (base&)(*this)  = rhs;
        m_pimpl         = rhs.m_pimpl;
        rhs.m_valid     = false;
    }














    void                    load( config_file_iterator cf_it ) { load( cf_it, nfp::no_params );  }

    template<typename Modifier>
    void                    load( config_file_iterator cf_it, Modifier const& m )
    {
        cstring vm = m.has( value_marker )        ? m[value_marker]        : BOOST_RT_PARAM_CSTRING_LITERAL( "\"" );
        cstring vd = m.has( value_delimeter )     ? m[value_delimeter]     : BOOST_RT_PARAM_CSTRING_LITERAL( "= \t\n\r" );
        cstring nd = m.has( namespace_delimeter ) ? m[namespace_delimeter] : BOOST_RT_PARAM_CSTRING_LITERAL( "::" );

        load_impl( cf_it, vm, vd, nd );
    }

    void                    load( cstring file_name )
    {
        load( file_name, nfp::no_params );
    }

    template<typename Modifier>
    void                    load( cstring file_name, Modifier const& m )
    {
        config_file_iterator cfi( file_name, m );

        load( cfi, m );
    }


    iterator                begin()                 { return m_parameters.begin(); }


    iterator                end()                   { return m_parameters.end(); }


    sub_ns_iterator         sub_ns_begin()          { return m_subnamespaces.begin(); }


    sub_ns_iterator         sub_ns_end()            { return m_subnamespaces.end(); }

    explicit    ifstream_holder( basic_cstring<CharT const> file_name )
    {
        if( file_name.is_empty() )
            return;

        m_stream.open( file_name.begin(), std::ios::in );
    }


    bool is_valid()
    {
        return m_stream.is_open();
    }

    basic_ifstream_line_iterator( basic_cstring<CharT const> file_name, CharT delimeter )
    : ut_detail::ifstream_holder<CharT>( file_name ), basic_istream_line_iterator<CharT>( this->m_stream, delimeter ) {}


    explicit basic_ifstream_line_iterator( basic_cstring<CharT const> file_name = basic_cstring<CharT const>() )
    : ut_detail::ifstream_holder<CharT>( file_name ), basic_istream_line_iterator<CharT>( this->m_stream ) {}


    template <class Facade>
    static bool get( Facade& f )
    {
        return f.get();
    }

    input_iterator_facade() : m_valid( false ), m_value() {}

    void                init()
    {
        m_valid = true;
        increment();
    }

    void                increment()
    {
        // we make post-end incrementation indefinetly safe 
        if( m_valid )
            m_valid = input_iterator_core_access::get( *static_cast<Derived*>(this) );
    }

    Reference           dereference() const
    {
        return m_value;
    }

    bool                equal( input_iterator_facade const& rhs ) const
    {
        // two invalid iterator equals, inequal otherwise
        return !m_valid && !rhs.m_valid;
    }

    bool operator()( CharT c1, CharT c2 )
    {
#ifdef BOOST_CLASSIC_IOSTREAMS
        return std::string_char_traits<CharT>::eq( c1, c2 );
#else
        return std::char_traits<CharT>::eq( c1, c2 );
#endif
    }

    explicit    delim_policy( ti_delimeter_type t = dt_char, cstring d = cstring() )
    : m_type( t )
    {
        set_delimeters( d );
    }


    void        set_delimeters( ti_delimeter_type t ) { m_type = t; }

    template<typename Src>
    void        set_delimeters( Src d )
    {
        nfp::optionally_assign( m_delimeters, d );
        
        if( !m_delimeters.is_empty() )
            m_type = dt_char;
    }


    bool        operator()( CharT c )
    {
        switch( m_type ) {
        case dt_char: {
            BOOST_TEST_FOREACH( CharT, delim, m_delimeters )
                if( CharCompare()( delim, c ) )
                    return true;

            return false;
        }
        case dt_ispunct:
            return (std::ispunct)( c ) != 0;
        case dt_isspace:
            return (std::isspace)( c ) != 0;
        case dt_none:
            return false;
        }

        return false;
    }

    template<typename Iterator, typename Token>
    static void assign( Iterator b, Iterator e, Token& t )  { t.assign( b, e ); }

    template<typename Iterator, typename Token>
    static void append_move( Iterator& b, Token& )          { ++b; }

    template<typename Iterator, typename Token>
    static void assign( Iterator b, Iterator e, Token& t )  {}


    template<typename Iterator, typename Token>
    static void append_move( Iterator& b, Token& t )        { t += *b; ++b; }

    explicit    token_iterator_base()
    : m_is_dropped( dt_isspace )
    , m_is_kept( dt_ispunct )
    , m_keep_empty_tokens( false )
    , m_tokens_left( static_cast<std::size_t>(-1) )
    , m_token_produced( false )
    {
    }


    template<typename Modifier>
    void
    apply_modifier( Modifier const& m )
    {
        if( m.has( dropped_delimeters ) )
            m_is_dropped.set_delimeters( m[dropped_delimeters] );

        if( m.has( kept_delimeters ) )
            m_is_kept.set_delimeters( m[kept_delimeters] );

        if( m.has( keep_empty_tokens ) )
            m_keep_empty_tokens = true;

        nfp::optionally_assign( m_tokens_left, m, max_tokens );
    }


    template<typename Iter> 
    bool                    get( Iter& begin, Iter end )
    {
        typedef ut_detail::token_assigner<BOOST_DEDUCED_TYPENAME iterator_traversal<Iter>::type> Assigner;
        Iter check_point;

        this->m_value.clear();

        if( !m_keep_empty_tokens ) {
            while( begin != end && m_is_dropped( *begin ) )
                ++begin;

            if( begin == end )
                return false;

            check_point = begin;

            if( m_tokens_left == 1 )
                while( begin != end )
                    Assigner::append_move( begin, this->m_value );
            else if( m_is_kept( *begin ) )
                Assigner::append_move( begin, this->m_value );
            else
                while( begin != end && !m_is_dropped( *begin ) && !m_is_kept( *begin ) )
                    Assigner::append_move( begin, this->m_value );

            --m_tokens_left;
        } 
        else { // m_keep_empty_tokens is true
            check_point = begin;

            if( begin == end ) {
                if( m_token_produced ) 
                    return false;

                m_token_produced = true;
            }
            if( m_is_kept( *begin ) ) {
                if( m_token_produced ) 
                    Assigner::append_move( begin, this->m_value );

                m_token_produced = !m_token_produced;
            } 
            else if( !m_token_produced && m_is_dropped( *begin ) )
                m_token_produced = true;
            else {
                if( m_is_dropped( *begin ) )
                    check_point = ++begin;

                while( begin != end && !m_is_dropped( *begin ) && !m_is_kept( *begin ) )
                    Assigner::append_move( begin, this->m_value );

                m_token_produced = true;
            }
        }

        Assigner::assign( check_point, begin, this->m_value );

        return true;
    }

    explicit    basic_string_token_iterator() {}

    explicit    basic_string_token_iterator( cstring src )
    : m_src( src )
    {
        this->init();
    }


    template<typename Src, typename Modifier>
    basic_string_token_iterator( Src src, Modifier const& m )
    : m_src( src )
    {
        this->apply_modifier( m );

        this->init();
    }

    bool        get()
    {
        typename cstring::iterator begin = m_src.begin();
        bool res = base::get( begin, m_src.end() );

        m_src.assign( begin, m_src.end() );

        return res;
    }

    static bool eq( CharT c1, CharT c2 )
    {
        return c1 == c2;
    }

    static bool lt( CharT c1, CharT c2 )
    {
        return c1 < c2;
    }


    static int compare( const_char* cstr1, const_char* cstr2, std::size_t n )
    {
        while( n > 0 ) {
            if( !eq( *cstr1, *cstr2 ) )
                return lt( *cstr1, *cstr2 ) ? -1 : 1;
            ++cstr1;
            ++cstr2;
            --n;
        }

        return 0;
    }


    static std::size_t length( const_char* cstr )
    {
        const_char null_char = CharT();

        const_char* ptr = cstr;
        while( !eq( *ptr, null_char ) )
            ++ptr;

        return ptr - cstr;
    }


    static const_char* find( const_char* s, std::size_t n, CharT c )
    {
        while( n > 0 ) {
            if( eq( *s, c ) )
                return s;

            ++s;
            --n;
        }
        return 0;
    }

    static bool         eq( CharT c1, CharT c2 ) { return (std::toupper)( c1 ) == (std::toupper)( c2 ); }

    static bool         lt( CharT c1, CharT c2 ) { return (std::toupper)( c1 ) <  (std::toupper)( c2 ); }


    static int          compare( CharT const* s1, CharT const* s2, std::size_t n )
    {
        for( std::size_t i = 0; i < n; ++i ) {
            if( !eq( s1[i], s2[i] ) )
                return lt( s1[i], s2[i] ) ? -1 : 1;
        }
        return 0;
    }


template<class CharT>
inline bool
case_ins_eq( basic_cstring<CharT> x, basic_cstring<CharT> y )
{
    return x.size() == y.size() && ut_detail::case_ins<CharT>::compare( x.begin(), y.begin(), x.size() ) == 0;
}

    bool operator()( basic_cstring<CharT> x, basic_cstring<CharT> y ) const
    {
        return x.size() != y.size() 
                ? x.size() < y.size() 
                : ut_detail::case_ins<CharT>::compare( x.begin(), y.begin(), x.size() ) < 0;
    }


template<class CharT>
inline bool
operator <( boost::unit_test::basic_cstring<CharT> const& x,
            boost::unit_test::basic_cstring<CharT> const& y )
{
    typedef typename boost::unit_test::basic_cstring<CharT>::traits_type traits_type;
    return x.size() != y.size() 
            ? x.size() < y.size() 
            : traits_type::compare( x.begin(), y.begin(), x.size() ) < 0;
}


    template<typename CharT2>
    basic_cstring&  assign( basic_cstring<CharT2> const& s ) { *this = basic_cstring<CharT>( s.begin(), s.end() ); return *this; }


template<typename CharT>
inline typename basic_cstring<CharT>::pointer
basic_cstring<CharT>::null_str()
{
    static CharT null = 0;
    return &null;
}


template<typename CharT>
inline
basic_cstring<CharT>::basic_cstring()
: m_begin( null_str() )
, m_end( m_begin )
{
}


template<typename CharT>
inline
basic_cstring<CharT>::basic_cstring( std_string const& s )
: m_begin( s.c_str() )
, m_end( m_begin + s.size() )
{
}


template<typename CharT>
inline
basic_cstring<CharT>::basic_cstring( pointer s )
: m_begin( s ? s : null_str() )
, m_end  ( m_begin + (s ? traits_type::length( s ) : 0 ) )
{
}


template<typename CharT>
inline
basic_cstring<CharT>::basic_cstring( pointer s, size_type arg_size )
: m_begin( s ), m_end( m_begin + arg_size )
{
}


template<typename CharT>
inline
basic_cstring<CharT>::basic_cstring( pointer first, pointer last )
: m_begin( first )
, m_end( last )
{
}


template<typename CharT>
inline typename basic_cstring<CharT>::value_type
basic_cstring<CharT>::operator[]( size_type index ) const
{
    return m_begin[index];
}


template<typename CharT>
inline typename basic_cstring<CharT>::value_type
basic_cstring<CharT>::at( size_type index ) const
{
    if( m_begin + index >= m_end )
        return static_cast<value_type>(0);

    return m_begin[index];
}


template<typename CharT>
inline typename basic_cstring<CharT>::size_type
basic_cstring<CharT>::size() const
{
    return m_end - m_begin;
}


template<typename CharT>
inline bool
basic_cstring<CharT>::is_empty() const
{
    return m_end == m_begin;
}


template<typename CharT>
inline bool
basic_cstring<CharT>::empty() const
{
    return is_empty();
}


template<typename CharT>
inline void
basic_cstring<CharT>::clear()
{
    m_begin = m_end;
}


template<typename CharT>
inline void
basic_cstring<CharT>::resize( size_type new_len )
{
    if( m_begin + new_len < m_end )
        m_end = m_begin + new_len;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_left( size_type trim_size )
{
    m_begin += trim_size;
    if( m_end <= m_begin )
        clear();

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_left( iterator it )
{
    m_begin = it;
    if( m_end <= m_begin )
        clear();

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_left( basic_cstring exclusions )
{
    if( exclusions.is_empty() )
        exclusions = default_trim_ex();

    iterator it;
    for( it = begin(); it != end(); ++it ) {
        if( traits_type::find( exclusions.begin(), exclusions.size(), *it ) == reinterpret_cast<pointer>(0) )
            break;
    }
    
    return trim_left( it );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_right( size_type trim_size )
{
    m_end  -= trim_size;
    if( m_end <= m_begin )
        clear();

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_right( iterator it )
{
    m_end = it;
    if( m_end <= m_begin )
        clear();

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim_right( basic_cstring exclusions )
{
    if( exclusions.is_empty() )
        exclusions = default_trim_ex();

    iterator it;

    for( it = end()-1; it != begin()-1; --it ) {
        if( self_type::traits_type::find( exclusions.begin(),  exclusions.size(), *it ) == reinterpret_cast<pointer>(0) )
            break;
    }
    
    return trim_right( it+1 );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::trim( basic_cstring exclusions )
{
    trim_left( exclusions );
    trim_right( exclusions );

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::operator=( basic_cstring<CharT> const& s )
{
    m_begin = s.m_begin;
    m_end   = s.m_end;

    return *this;
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::operator=( std_string const& s )
{
    return *this = self_type( s );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::operator=( pointer s )
{
    return *this = self_type( s );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( basic_cstring<CharT> const& s, size_type pos, size_type len )
{
    return *this = self_type( s.m_begin + pos, len );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( std_string const& s )
{
    return *this = self_type( s );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( std_string const& s, size_type pos, size_type len )
{
    return *this = self_type( s.c_str() + pos, len );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( pointer s )
{
    return *this = self_type( s );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( pointer s, size_type len )
{
    return *this = self_type( s, len );
}


template<typename CharT>
inline basic_cstring<CharT>&
basic_cstring<CharT>::assign( pointer f, pointer l )
{
    return *this = self_type( f, l );
}


template<typename CharT>
inline void
basic_cstring<CharT>::swap( basic_cstring<CharT>& s )
{
    // do not want to include alogrithm
    pointer tmp1    = m_begin;
    pointer tmp2    = m_end;

    m_begin         = s.m_begin;
    m_end           = s.m_end;

    s.m_begin       = tmp1;
    s.m_end         = tmp2;
}


template<typename CharT>
inline typename basic_cstring<CharT>::iterator
basic_cstring<CharT>::begin()
{
    return m_begin;
}


template<typename CharT>
inline typename basic_cstring<CharT>::const_iterator
basic_cstring<CharT>::begin() const
{
    return m_begin;
}


template<typename CharT>
inline typename basic_cstring<CharT>::iterator
basic_cstring<CharT>::end()
{
    return m_end;
}


template<typename CharT>
inline typename basic_cstring<CharT>::const_iterator
basic_cstring<CharT>::end() const
{
    return m_end;
}


template<typename CharT>
inline typename basic_cstring<CharT>::size_type
basic_cstring<CharT>::find( basic_cstring<CharT> str ) const
{
    if( str.is_empty() || str.size() > size() )
        return static_cast<size_type>(npos);

    const_iterator it   = begin();
    const_iterator last = end() - str.size() + 1;

    while( it != last ) {
        if( traits_type::compare( it, str.begin(), str.size() ) == 0 )
            break;

        ++it;
    }

    return it == last ? static_cast<size_type>(npos) : it - begin();
}


template<typename CharT>
inline typename basic_cstring<CharT>::size_type
basic_cstring<CharT>::rfind( basic_cstring<CharT> str ) const
{
    if( str.is_empty() || str.size() > size() )
        return static_cast<size_type>(npos);

    const_iterator it   = end() - str.size();
    const_iterator last = begin()-1;

    while( it != last ) {
        if( traits_type::compare( it, str.begin(), str.size() ) == 0 )
            break;

        --it;
    }

    return it == last ? static_cast<size_type>(npos) : static_cast<size_type>(it - begin());
}


template<typename CharT>
inline basic_cstring<CharT>
basic_cstring<CharT>::substr( size_type beg_index, size_type end_index ) const
{
    return beg_index > size()
            ?       self_type()
            : end_index > size()
                ?   self_type( m_begin + beg_index, m_end )
                :   self_type( m_begin + beg_index, m_begin + end_index );
}


template<typename CharT>
inline basic_cstring<CharT>
basic_cstring<CharT>::default_trim_ex()
{
    static CharT ws[3] = { CharT(' '), CharT('\t'), CharT('\n') }; // !! wide case

    return self_type( ws, 3 );
}


template<typename CharT1,typename CharT2>
inline bool
operator==( basic_cstring<CharT1> const& s1, basic_cstring<CharT2> const& s2 )
{
    typedef typename basic_cstring<CharT1>::traits_type traits_type;
    return s1.size() == s2.size() && 
               traits_type::compare( s1.begin(), s2.begin(), s1.size() ) == 0;
}


template<typename CharT1,typename CharT2>
inline bool
operator==( basic_cstring<CharT1> const& s1, CharT2* s2 )
{
#if !defined(__DMC__)
    return s1 == basic_cstring<CharT2>( s2 );
#else
    return s1 == basic_cstring<CharT2 const>( s2 );
#endif
}


template<typename CharT>
inline bool
operator==( basic_cstring<CharT> const& s1, typename basic_cstring<CharT>::std_string const& s2 )
{
    return s1 == basic_cstring<CharT>( s2 );
}


template<typename CharT1,typename CharT2>
inline bool
operator==( CharT1* s2, basic_cstring<CharT2> const& s1 )
{
    return s1 == s2;
}


template<typename CharT>
inline bool
operator==( typename basic_cstring<CharT>::std_string const& s2, basic_cstring<CharT> const& s1 )
{
    return s1 == s2;
}


template<typename CharT>
inline bool
operator!=( basic_cstring<CharT> const& s1, CharT* s2 )
{
    return !(s1 == s2);
}


template<typename CharT>
inline bool
operator!=( CharT* s2, basic_cstring<CharT> const& s1 )
{
    return !(s1 == s2);
}


template<typename CharT>
inline bool
operator!=( basic_cstring<CharT> const& s1, basic_cstring<CharT> const& s2 )
{
    return !(s1 == s2);
}


template<typename CharT>
inline bool
operator!=( basic_cstring<CharT> const& s1, typename basic_cstring<CharT>::std_string const& s2 )
{
    return !(s1 == s2);
}


template<typename CharT>
inline bool
operator!=( typename basic_cstring<CharT>::std_string const& s2, basic_cstring<CharT> const& s1 )
{
    return !(s1 == s2);
}


template<typename CharT>
inline typename basic_cstring<CharT>::value_type
first_char( basic_cstring<CharT> source )
{
    typedef typename basic_cstring<CharT>::value_type string_value_type;

    return source.is_empty() ? static_cast<string_value_type>(0) : *source.begin();
}


template<typename CharT>
inline typename basic_cstring<CharT>::value_type
last_char( basic_cstring<CharT> source )
{
    typedef typename basic_cstring<CharT>::value_type string_value_type;

    return source.is_empty() ? static_cast<string_value_type>(0) : *(source.end()-1);
}
