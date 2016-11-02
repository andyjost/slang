

    explicit scoped_ptr( T * p = 0 ): px( p ) // never throws
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_constructor_hook( px );
#endif
    }

      bool operator()(const T &lhs, const T &rhs) const
      {
        return lhs.owner_before(rhs);
      }

      bool operator()(const T &lhs, const U &rhs) const
      {
        return lhs.owner_before(rhs);
      }

      bool operator()(const U &lhs, const T &rhs) const
      {
        return lhs.owner_before(rhs);
      }


    void destroy()
    {
        if( initialized_ )
        {
#if defined( __GNUC__ )

            // fixes incorrect aliasing warning
            T * p = reinterpret_cast< T* >( storage_.data_ );
            p->~T();

#else

            reinterpret_cast< T* >( storage_.data_ )->~T();

#endif

            initialized_ = false;
        }
    }


template< class T > typename boost::detail::sp_if_not_array< T >::type make_shared()
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ) );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T();
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


template< class T > typename boost::detail::sp_if_not_array< T >::type make_shared_noinit()
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ) );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T;
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


template< class T, class A > typename boost::detail::sp_if_not_array< T >::type allocate_shared( A const & a )
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ), a );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T();
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


template< class T, class A > typename boost::detail::sp_if_not_array< T >::type allocate_shared_noinit( A const & a )
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ), a );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T;
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


template< class T, class Arg1, class... Args > typename boost::detail::sp_if_not_array< T >::type make_shared( Arg1 && arg1, Args && ... args )
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ) );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( boost::detail::sp_forward<Arg1>( arg1 ), boost::detail::sp_forward<Args>( args )... );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


template< class T, class A, class Arg1, class... Args > typename boost::detail::sp_if_not_array< T >::type allocate_shared( A const & a, Arg1 && arg1, Args && ... args )
{
    boost::shared_ptr< T > pt( static_cast< T* >( 0 ), BOOST_SP_MSD( T ), a );

    boost::detail::sp_ms_deleter< T > * pd = static_cast<boost::detail::sp_ms_deleter< T > *>( pt._internal_get_untyped_deleter() );

    void * pv = pd->address();

    ::new( pv ) T( boost::detail::sp_forward<Arg1>( arg1 ), boost::detail::sp_forward<Args>( args )... );
    pd->set_initialized();

    T * pt2 = static_cast< T* >( pv );

    boost::detail::sp_enable_shared_from_this( &pt, pt2, pt2 );
    return boost::shared_ptr< T >( pt, pt2 );
}


    virtual char const * what() const throw()
    {
        return "tr1::bad_weak_ptr";
    }


    enable_shared_from_raw()
    {
    }


    enable_shared_from_raw( enable_shared_from_raw const & )
    {
    }


    enable_shared_from_raw & operator=( enable_shared_from_raw const & )
    {
        return *this;
    }


    ~enable_shared_from_raw()
    {
        BOOST_ASSERT( shared_this_.use_count() <= 1 ); // make sure no dangling shared_ptr objects exist
    }


    void init_weak_once() const
    {
        if( weak_this_.expired() )
        {
            shared_this_.reset( static_cast<void*>(0), detail::esft2_deleter_wrapper() );
            weak_this_ = shared_this_;
        }
    }


template< class X, class Y, class T > inline void sp_enable_shared_from_this( boost::shared_ptr<X> const * ppx, Y const * py, boost::enable_shared_from_this< T > const * pe )
{
    if( pe != 0 )
    {
        pe->_internal_accept_owner( ppx, const_cast< Y* >( py ) );
    }
}


inline void sp_enable_shared_from_this( ... )
{
}


template< class Y, class T > inline void sp_assert_convertible()
{
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    // static_assert( sp_convertible< Y, T >::value );
    typedef char tmp[ sp_convertible< Y, T >::value? 1: -1 ];
    (void)sizeof( tmp );

#else

    T* p = static_cast< Y* >( 0 );
    (void)p;

#endif
}


template< class T, class Y > inline void sp_pointer_construct( boost::shared_ptr< T > * ppx, Y * p, boost::detail::shared_count & pn )
{
    boost::detail::shared_count( p ).swap( pn );
    boost::detail::sp_enable_shared_from_this( ppx, p, p );
}


template< class T, class Y > inline void sp_deleter_construct( boost::shared_ptr< T > * ppx, Y * p )
{
    boost::detail::sp_enable_shared_from_this( ppx, p, p );
}


template< class T, class Y > inline void sp_deleter_construct( boost::shared_ptr< T[] > * /*ppx*/, Y * /*p*/ )
{
    sp_assert_convertible< Y[], T[] >();
}


template< class T, std::size_t N, class Y > inline void sp_deleter_construct( boost::shared_ptr< T[N] > * /*ppx*/, Y * /*p*/ )
{
    sp_assert_convertible< Y[N], T[N] >();
}

    allocate_shared(const A& allocator, std::size_t size, Args&&... args) {
        typedef typename boost::detail::array_inner<T>::type T1;
        typedef typename boost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * boost::detail::array_total<T1>::size;
        boost::detail::allocate_array_helper<A, T2[]> a1(allocator, n1, &p2);
        boost::detail::array_deleter<T2[]> d1(n1);
        boost::shared_ptr<T> s1(p1, d1, a1);
        typedef boost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, boost::detail::sp_forward<Args>(args)...);
        return boost::shared_ptr<T>(s1, p1);
    }

    allocate_shared_noinit(const A& allocator, std::size_t size) {
        typedef typename boost::detail::array_inner<T>::type T1;
        typedef typename boost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * boost::detail::array_total<T1>::size;
        boost::detail::allocate_array_helper<A, T2[]> a1(allocator, n1, &p2);
        boost::detail::array_deleter<T2[]> d1(n1);
        boost::shared_ptr<T> s1(p1, d1, a1);
        typedef boost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->noinit(p2);
        return boost::shared_ptr<T>(s1, p1);
    }

    make_shared(std::size_t size, Args&&... args) {
        typedef typename boost::detail::array_inner<T>::type T1;
        typedef typename boost::detail::array_base<T1>::type T2;
        T1* p1 = 0;
        T2* p2 = 0;
        std::size_t n1 = size * boost::detail::array_total<T1>::size;
        boost::detail::make_array_helper<T2[]> a1(n1, &p2);
        boost::detail::array_deleter<T2[]> d1(n1);
        boost::shared_ptr<T> s1(p1, d1, a1);
        typedef boost::detail::array_deleter<T2[]>* D2;
        p1 = reinterpret_cast<T1*>(p2);
        D2 d2 = static_cast<D2>(s1._internal_get_untyped_deleter());
        d2->init(p2, boost::detail::sp_forward<Args>(args)...);
        return boost::shared_ptr<T>(s1, p1);
    }


template<class T, class U> inline bool operator==(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b)
{
    return a.get() == b.get();
}


template<class T, class U> inline bool operator!=(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b)
{
    return a.get() != b.get();
}


template<class T, class U> inline bool operator==(intrusive_ptr<T> const & a, U * b)
{
    return a.get() == b;
}


template<class T, class U> inline bool operator!=(intrusive_ptr<T> const & a, U * b)
{
    return a.get() != b;
}


template<class T, class U> inline bool operator==(T * a, intrusive_ptr<U> const & b)
{
    return a == b.get();
}


template<class T, class U> inline bool operator!=(T * a, intrusive_ptr<U> const & b)
{
    return a != b.get();
}


template< class T > std::size_t hash_value( boost::intrusive_ptr<T> const & p )
{
    return boost::hash< T* >()( p.get() );
}

        template<typename T>
        inline void array_destroy(T*, std::size_t, boost::true_type) {
        }

        template<typename T>
        inline void array_init(T* memory, std::size_t size, boost::true_type) {
            for (std::size_t i = 0; i < size; i++) {
                memory[i] = T();
            }
        }

        template<typename T>
        inline void array_init_value(T* memory, std::size_t size, T&& value) {
#if !defined(BOOST_NO_EXCEPTIONS)
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(value);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
#else
            for (std::size_t i = 0; i < size; i++) {
                void* p1 = memory + i;
                ::new(p1) T(value);
            }
#endif
        }

        template<typename T, typename... Args>
        inline void array_init_args(T* memory, std::size_t size, Args&&... args) {
#if !defined(BOOST_NO_EXCEPTIONS)
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(args...);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
#else
            for (std::size_t i = 0; i < size; i++) {
                void* p1 = memory + i;
                ::new(p1) T(args...);
            }
#endif
        }

        template<typename T>
        inline void array_init_list(T* memory, std::size_t size, const T* list) {
#if !defined(BOOST_NO_EXCEPTIONS)
            std::size_t i = 0;
            try {
                for (; i < size; i++) {
                    void* p1 = memory + i;
                    ::new(p1) T(list[i]);
                }
            } catch (...) {
                array_destroy(memory, i);
                throw;
            }
#else
            for (std::size_t i = 0; i < size; i++) {
                void* p1 = memory + i;
                ::new(p1) T(list[i]);
            }
#endif
        }

        template<typename T>
        inline void array_noinit(T*, std::size_t, boost::true_type) {
        }


inline void yield( unsigned )
{
}


    bool try_lock()
    {
        long r = BOOST_INTERLOCKED_EXCHANGE( &v_, 1 );

        BOOST_COMPILER_FENCE

        return r == 0;
    }


    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }


    void unlock()
    {
        BOOST_COMPILER_FENCE
        *const_cast< long volatile* >( &v_ ) = 0;
    }


        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


    explicit atomic_count( long v ) : value_( v ) {}


    long operator++()
    {
        return __sync_add_and_fetch( &value_, 1 );
    }


    long operator--()
    {
        return __sync_add_and_fetch( &value_, -1 );
    }


    operator long() const
    {
        return __sync_fetch_and_add( &value_, 0 );
    }


    bool try_lock()
    {
        int r;

#ifdef BOOST_SP_ARM_HAS_LDREX

        __asm__ __volatile__(
            "ldrex %0, [%2]; \n"
            "cmp %0, %1; \n"
            "strexne %0, %1, [%2]; \n"
            BOOST_SP_ARM_BARRIER :
            "=&r"( r ): // outputs
            "r"( 1 ), "r"( &v_ ): // inputs
            "memory", "cc" );

#else

        __asm__ __volatile__(
            "swp %0, %1, [%2];\n"
            BOOST_SP_ARM_BARRIER :
            "=&r"( r ): // outputs
            "r"( 1 ), "r"( &v_ ): // inputs
            "memory", "cc" );

#endif

        return r == 0;
    }


    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }


    void unlock()
    {
        __asm__ __volatile__( BOOST_SP_ARM_BARRIER ::: "memory" );
        *const_cast< int volatile* >( &v_ ) = 0;
    }


        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


    static inline void * alloc()
    {
#ifdef BOOST_HAS_THREADS
        lightweight_mutex::scoped_lock lock( mutex() );
#endif
        if(block * x = free)
        {
            free = x->next;
            return x;
        }
        else
        {
            if(last == items_per_page)
            {
                // "Listen to me carefully: there is no memory leak"
                // -- Scott Meyers, Eff C++ 2nd Ed Item 10
                page = ::new block[items_per_page];
                last = 0;
            }

            return &page[last++];
        }
    }


    static inline void dealloc(void * pv)
    {
        if(pv != 0) // 18.4.1.1/13
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock( mutex() );
#endif
            block * pb = static_cast<block *>(pv);
            pb->next = free;
            free = pb;
        }
    }

            allocate_array_helper(const A& allocator_, std::size_t size_, T** data_)
                : allocator(allocator_),
                  size(sizeof(T) * size_),
                  data(data_) {
            }

            template<class U>
            allocate_array_helper(const allocate_array_helper<A, T[], U>& other) 
                : allocator(other.allocator),
                  size(other.size),
                  data(other.data) {
            }

            pointer address(reference value) const {
                return allocator.address(value);
            }

            const_pointer address(const_reference value) const {
                return allocator.address(value);
            }

            size_type max_size() const {
                return allocator.max_size();
            }

            pointer allocate(size_type count, const void* value = 0) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                char*  p1 = A3(allocator).allocate(n1 + size, value);
                char*  p2 = p1 + n1;
                while (std::size_t(p2) % a1 != 0) {
                    p2--;
                }
                *data = reinterpret_cast<T*>(p2);
                return  reinterpret_cast<Y*>(p1);
            }

            void deallocate(pointer memory, size_type count) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                char*  p1 = reinterpret_cast<char*>(memory);
                A3(allocator).deallocate(p1, n1 + size);
            }

            void construct(pointer memory, const Y& value) {
                allocator.construct(memory, value);
            }

            void destroy(pointer memory) {
                allocator.destroy(memory);
            }

            template<typename U>
            bool operator==(const allocate_array_helper<A, T[], U>& other) const {
                return allocator == other.allocator;
            }

            template<typename U>
            bool operator!=(const allocate_array_helper<A, T[], U>& other) const {
                return !(*this == other); 
            }

            allocate_array_helper(const A& allocator_, T** data_)
                : allocator(allocator_),
                  data(data_) {
            }

            template<class U>
            allocate_array_helper(const allocate_array_helper<A, T[N], U>& other) 
                : allocator(other.allocator),
                  data(other.data) {
            }

            pointer address(reference value) const {
                return allocator.address(value);
            }

            const_pointer address(const_reference value) const {
                return allocator.address(value);
            }

            size_type max_size() const {
                return allocator.max_size();
            }

            pointer allocate(size_type count, const void* value = 0) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                char*  p1 = A3(allocator).allocate(n1 + N1, value);
                char*  p2 = p1 + n1;
                while (std::size_t(p2) % a1 != 0) {
                    p2--;
                }
                *data = reinterpret_cast<T*>(p2);
                return  reinterpret_cast<Y*>(p1);
            }

            void deallocate(pointer memory, size_type count) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                char*  p1 = reinterpret_cast<char*>(memory);
                A3(allocator).deallocate(p1, n1 + N1);
            }

            void construct(pointer memory, const Y& value) {
                allocator.construct(memory, value);
            }

            void destroy(pointer memory) {
                allocator.destroy(memory);
            }

            template<typename U>
            bool operator==(const allocate_array_helper<A, T[N], U>& other) const {
                return allocator == other.allocator;
            }

            template<typename U>
            bool operator!=(const allocate_array_helper<A, T[N], U>& other) const {
                return !(*this == other); 
            }


inline uint32_t compare_and_swap( uint32_t * dest_, uint32_t compare_, uint32_t swap_ )
{
    return __builtin_cellAtomicCompareAndSwap32(dest_,compare_,swap_);
}


inline uint32_t atomic_fetch_and_add( uint32_t * pw, uint32_t dv )
{
    // long r = *pw;
    // *pw += dv;
    // return r;

    for( ;; )
    {
        uint32_t r = *pw;

        if( __builtin_expect((compare_and_swap(pw, r, r + dv) == r), 1) )
        {
            return r;
        }
    }
}


inline void atomic_increment( uint32_t * pw )
{
    (void) __builtin_cellAtomicIncr32( pw );
}


inline uint32_t atomic_decrement( uint32_t * pw )
{
    return __builtin_cellAtomicDecr32( pw );
}


inline uint32_t atomic_conditional_increment( uint32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    for( ;; )
    {
        uint32_t r = *pw;

        if( r == 0 )
        {
            return r;
        }

        if( __builtin_expect( ( compare_and_swap( pw, r, r + 1 ) == r ), 1 ) )
        {
            return r;
        }
    }    
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return const_cast< uint32_t const volatile & >( use_count_ );
    }


inline void atomic_increment( register long * pw )
{
    register int a;

    asm
    {
loop:

    lwarx   a, 0, pw
    addi    a, a, 1
    stwcx.  a, 0, pw
    bne-    loop
    }
}


inline long atomic_decrement( register long * pw )
{
    register int a;

    asm
    {
    sync

loop:

    lwarx   a, 0, pw
    addi    a, a, -1
    stwcx.  a, 0, pw
    bne-    loop

    isync
    }

    return a;
}


inline long atomic_conditional_increment( register long * pw )
{
    register int a;

    asm
    {
loop:

    lwarx   a, 0, pw
    cmpwi   a, 0
    beq     store

    addi    a, a, 1

store:

    stwcx.  a, 0, pw
    bne-    loop
    }

    return a;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<long const volatile &>( use_count_ );
    }


inline void atomic_increment( int * pw )
{
    // ++*pw;

    int tmp;

    __asm__
    (
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "addi %1, %1, 1\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b":

        "=m"( *pw ), "=&b"( tmp ):
        "r"( pw ), "m"( *pw ):
        "cc"
    );
}


inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv;

    __asm__ __volatile__
    (
        "sync\n\t"
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "addi %1, %1, -1\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b\n\t"
        "isync":

        "=m"( *pw ), "=&b"( rv ):
        "r"( pw ), "m"( *pw ):
        "memory", "cc"
    );

    return rv;
}


inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv;

    __asm__
    (
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "cmpwi %1, 0\n\t"
        "beq 1f\n\t"
        "addi %1, %1, 1\n\t"
        "1:\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b":

        "=m"( *pw ), "=&b"( rv ):
        "r"( pw ), "m"( *pw ):
        "cc"
    );

    return rv;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ );
    }

            array_deleter(std::size_t size_)
                : size(size_),
                  object(0) {
            }

            ~array_deleter() {
                if (object) {
                    array_destroy(object, size);
                }
            }

            void init(T* memory) {
                array_init(memory, size);
                object = memory;
            }

            void init(T* memory, T&& value) {
                array_init_value(memory, size, sp_forward<T>(value));
                object = memory;                
            }

            template<typename... Args>
            void init(T* memory, Args&&... args) {
                array_init_args(memory, size, sp_forward<Args>(args)...);
                object = memory;
            }

            void init_list(T* memory, const T* list) {
                array_init_list(memory, size, list);
                object = memory;
            }

            template<std::size_t M>
            void init_list(T* memory, const T* list) {
                array_init_list<T, M>(memory, size, list);
                object = memory;
            }

            void noinit(T* memory) {
                array_noinit(memory, size);
                object = memory;
            }

            void operator()(const void*) {
                if (object) {
                    array_destroy(object, size);
                    object = 0;
                }
            }

            array_deleter()
                : object(0) {
            }

            ~array_deleter() {
                if (object) {
                    array_destroy(object, N);
                }
            }

            void init(T* memory) {
                array_init(memory, N);
                object = memory;
            }

            void init(T* memory, T&& value) {
                array_init_value(memory, N, sp_forward<T>(value));
                object = memory;                
            }

            template<typename... Args>
            void init(T* memory, Args&&... args) {
                array_init_args(memory, N, sp_forward<Args>(args)...);
                object = memory;
            }

            void init_list(T* memory, const T* list) {
                array_init_list(memory, N, list);
                object = memory;
            }

            template<std::size_t M>
            void init_list(T* memory, const T* list) {
                array_init_list<T, M>(memory, N, list);
                object = memory;
            }

            void noinit(T* memory) {
                array_noinit(memory, N);
                object = memory;
            }

            void operator()(const void*) {
                if (object) {
                    array_destroy(object, N);
                    object = 0;
                }
            }


    lightweight_mutex()
    {
        InitializeCriticalSection(&cs_);
    }


    ~lightweight_mutex()
    {
        DeleteCriticalSection(&cs_);
    }


        explicit scoped_lock(lightweight_mutex & m): m_(m)
        {
            EnterCriticalSection(&m_.cs_);
        }


        ~scoped_lock()
        {
            LeaveCriticalSection(&m_.cs_);
        }


    lightweight_mutex()
    {

// HPUX 10.20 / DCE has a nonstandard pthread_mutex_init

#if defined(__hpux) && defined(_DECTHREADS_)
        BOOST_VERIFY( pthread_mutex_init( &m_, pthread_mutexattr_default ) == 0 );
#else
        BOOST_VERIFY( pthread_mutex_init( &m_, 0 ) == 0 );
#endif
    }


    ~lightweight_mutex()
    {
        BOOST_VERIFY( pthread_mutex_destroy( &m_ ) == 0 );
    }


        scoped_lock(lightweight_mutex & m): m_(m.m_)
        {
            BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        }


        ~scoped_lock()
        {
            BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
        }

            make_array_helper(std::size_t size_, T** data_)
                : size(sizeof(T) * size_),
                  data(data_) {
            }

            template<class U>
            make_array_helper(const make_array_helper<T[], U>& other) 
                : size(other.size),
                  data(other.data) {
            }

            pointer address(reference value) const {
                return &value;
            }

            const_pointer address(const_reference value) const {
                return &value;
            }

            size_type max_size() const {
                return static_cast<std::size_t>(-1) / sizeof(Y);
            }

            pointer allocate(size_type count, const void* = 0) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                void*  p1 = ::operator new(n1 + size);
                char*  p2 = static_cast<char*>(p1) + n1;
                while (std::size_t(p2) % a1 != 0) {
                    p2--;
                }
                *data = reinterpret_cast<T*>(p2);
                return  reinterpret_cast<Y*>(p1);
            }

            void deallocate(pointer memory, size_type) {
                void* p1 = memory;
                ::operator delete(p1);
            }

            void construct(pointer memory, const Y& value) {
                void* p1 = memory;
                ::new(p1) Y(value);
            }

            void destroy(pointer memory) {
                memory->~Y();
            }

            template<typename U>
            bool operator==(const make_array_helper<T[], U>&) const {
                return true;
            }

            template<typename U>
            bool operator!=(const make_array_helper<T[], U>& other) const {
                return !(*this == other); 
            }

            make_array_helper(T** data_)
                : data(data_) {
            }

            template<class U>
            make_array_helper(const make_array_helper<T[N], U>& other) 
                : data(other.data) {
            }

            pointer address(reference value) const {
                return &value;
            }

            const_pointer address(const_reference value) const {
                return &value;
            }

            size_type max_size() const {
                return static_cast<std::size_t>(-1) / sizeof(Y);
            }

            pointer allocate(size_type count, const void* = 0) {
                std::size_t a1 = boost::alignment_of<T>::value;
                std::size_t n1 = count * sizeof(Y) + a1 - 1;
                void*  p1 = ::operator new(n1 + N1);
                char*  p2 = static_cast<char*>(p1) + n1;
                while (std::size_t(p2) % a1 != 0) {
                    p2--;
                }
                *data = reinterpret_cast<T*>(p2);
                return  reinterpret_cast<Y*>(p1);
            }

            void deallocate(pointer memory, size_type) {
                void* p1 = memory;
                ::operator delete(p1);
            }

            void construct(pointer memory, const Y& value) {
                void* p1 = memory;
                ::new(p1) Y(value);
            }

            void destroy(pointer memory) {
                memory->~Y();
            }

            template<typename U>
            bool operator==(const make_array_helper<T[N], U>&) const {
                return true;
            }

            template<typename U>
            bool operator!=(const make_array_helper<T[N], U>& other) const {
                return !(*this == other); 
            }


inline int32_t compare_and_swap( int32_t * dest_, int32_t compare_, int32_t swap_ )
{
    __asm__ __volatile__( "cas [%1], %2, %0"
                        : "+r" (swap_)
                        : "r" (dest_), "r" (compare_)
                        : "memory" );

    return swap_;
}


inline int32_t atomic_fetch_and_add( int32_t * pw, int32_t dv )
{
    // long r = *pw;
    // *pw += dv;
    // return r;

    for( ;; )
    {
        int32_t r = *pw;

        if( __builtin_expect((compare_and_swap(pw, r, r + dv) == r), 1) )
        {
            return r;
        }
    }
}


inline void atomic_increment( int32_t * pw )
{
    atomic_fetch_and_add( pw, 1 );
}


inline int32_t atomic_decrement( int32_t * pw )
{
    return atomic_fetch_and_add( pw, -1 );
}


inline int32_t atomic_conditional_increment( int32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    for( ;; )
    {
        int32_t r = *pw;

        if( r == 0 )
        {
            return r;
        }

        if( __builtin_expect( ( compare_and_swap( pw, r, r + 1 ) == r ), 1 ) )
        {
            return r;
        }
    }    
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return const_cast< int32_t const volatile & >( use_count_ );
    }


inline int atomic_exchange_and_add( int * pw, int dv )
{
    // int r = *pw;
    // *pw += dv;
    // return r;

    asm
    {
        mov esi, [pw]
        mov eax, dv
        lock xadd dword ptr [esi], eax
    }
}


inline void atomic_increment( int * pw )
{
    //atomic_exchange_and_add( pw, 1 );

    asm
    {
        mov esi, [pw]
        lock inc dword ptr [esi]
    }
}


inline int atomic_conditional_increment( int * pw )
{
    // int rv = *pw;
    // if( rv != 0 ) ++*pw;
    // return rv;

    asm
    {
        mov esi, [pw]
        mov eax, dword ptr [esi]
    L0:
        test eax, eax
        je L1
        mov ebx, eax
        inc ebx
        lock cmpxchg dword ptr [esi], ebx
        jne L0
    L1:
    }
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_exchange_and_add( &use_count_, -1 ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_exchange_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ );
    }


    explicit sp_counted_impl_p( X * px ): px_( px )
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_constructor_hook( px, sizeof(X), this );
#endif
    }


    virtual void dispose() // nothrow
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_destructor_hook( px_, sizeof(X), this );
#endif
        boost::checked_delete( px_ );
    }


    virtual void * get_deleter( detail::sp_typeinfo const & )
    {
        return 0;
    }


    virtual void * get_untyped_deleter()
    {
        return 0;
    }


    sp_counted_impl_pd( P p, D & d ): ptr( p ), del( d )
    {
    }


    sp_counted_impl_pd( P p ): ptr( p ), del()
    {
    }


    virtual void dispose() // nothrow
    {
        del( ptr );
    }


    virtual void * get_deleter( detail::sp_typeinfo const & ti )
    {
        return ti == BOOST_SP_TYPEID(D)? &reinterpret_cast<char&>( del ): 0;
    }


    virtual void * get_untyped_deleter()
    {
        return &reinterpret_cast<char&>( del );
    }


    sp_counted_impl_pda( P p, D & d, A a ): p_( p ), d_( d ), a_( a )
    {
    }


    sp_counted_impl_pda( P p, A a ): p_( p ), d_(), a_( a )
    {
    }


    virtual void dispose() // nothrow
    {
        d_( p_ );
    }


    virtual void destroy() // nothrow
    {
        typedef typename A::template rebind< this_type >::other A2;

        A2 a2( a_ );

        this->~this_type();
        a2.deallocate( this, 1 );
    }


    virtual void * get_deleter( detail::sp_typeinfo const & ti )
    {
        return ti == BOOST_SP_TYPEID( D )? &reinterpret_cast<char&>( d_ ): 0;
    }


    virtual void * get_untyped_deleter()
    {
        return &reinterpret_cast<char&>( d_ );
    }


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_inc_32( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            uint32_t tmp = static_cast< uint32_t const volatile& >( use_count_ );
            if( tmp == 0 ) return false;
            if( atomic_cas_32( &use_count_, tmp, tmp + 1 ) == tmp ) return true;
        }
    }


    void release() // nothrow
    {
        if( atomic_dec_32_nv( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_inc_32( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_dec_32_nv( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<long const volatile &>( use_count_ );
    }


inline void atomic_increment( int * pw )
{
    // ++*pw;

    int tmp;

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
        ".set mips2\n\t"
        "ll %0, %1\n\t"
        "addiu %0, 1\n\t"
        "sc %0, %1\n\t"
        ".set pop\n\t"
        "beqz %0, 0b":
        "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw )
    );
}


inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv, tmp;

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
        ".set mips2\n\t"
        "ll %1, %2\n\t"
        "addiu %0, %1, -1\n\t"
        "sc %0, %2\n\t"
        ".set pop\n\t"
        "beqz %0, 0b\n\t"
        "addiu %0, %1, -1":
        "=&r"( rv ), "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw ):
        "memory"
    );

    return rv;
}


inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv, tmp;

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
        ".set mips2\n\t"
        "ll %0, %2\n\t"
        "beqz %0, 1f\n\t"
        "addiu %1, %0, 1\n\t"
        "sc %1, %2\n\t"
        ".set pop\n\t"
        "beqz %1, 0b\n\t"
        "addiu %0, %0, 1\n\t"
        "1:":
        "=&r"( rv ), "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw ):
        "memory"
    );

    return rv;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ );
    }


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
// HPUX 10.20 / DCE has a nonstandard pthread_mutex_init

#if defined(__hpux) && defined(_DECTHREADS_)
        pthread_mutex_init( &m_, pthread_mutexattr_default );
#else
        pthread_mutex_init( &m_, 0 );
#endif
    }


    virtual ~sp_counted_base() // nothrow
    {
        pthread_mutex_destroy( &m_ );
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        pthread_mutex_lock( &m_ );
        ++use_count_;
        pthread_mutex_unlock( &m_ );
    }


    bool add_ref_lock() // true on success
    {
        pthread_mutex_lock( &m_ );
        bool r = use_count_ == 0? false: ( ++use_count_, true );
        pthread_mutex_unlock( &m_ );
        return r;
    }


    void release() // nothrow
    {
        pthread_mutex_lock( &m_ );
        long new_use_count = --use_count_;
        pthread_mutex_unlock( &m_ );

        if( new_use_count == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        pthread_mutex_lock( &m_ );
        ++weak_count_;
        pthread_mutex_unlock( &m_ );
    }


    void weak_release() // nothrow
    {
        pthread_mutex_lock( &m_ );
        long new_weak_count = --weak_count_;
        pthread_mutex_unlock( &m_ );

        if( new_weak_count == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        pthread_mutex_lock( &m_ );
        long r = use_count_;
        pthread_mutex_unlock( &m_ );

        return r;
    }


    explicit atomic_count( long v ): value_( v )
    {
    }


    long operator++()
    {
        return BOOST_INTERLOCKED_INCREMENT( &value_ );
    }


    long operator--()
    {
        return BOOST_INTERLOCKED_DECREMENT( &value_ );
    }


    operator long() const
    {
        return static_cast<long const volatile &>( value_ );
    }


    inline bool try_lock()
    {
        if( locked_ )
        {
            return false;
        }
        else
        {
            locked_ = true;
            return true;
        }
    }


    inline void lock()
    {
        BOOST_ASSERT( !locked_ );
        locked_ = true;
    }


    inline void unlock()
    {
        BOOST_ASSERT( locked_ );
        locked_ = false;
    }


        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


inline void atomic_increment( int32_t* pw )
{
    // ++*pw;

    fetch_and_add( pw, 1 );
}


inline int32_t atomic_decrement( int32_t * pw )
{
    // return --*pw;

    int32_t originalValue;

    __lwsync();
    originalValue = fetch_and_add( pw, -1 );
    __isync();

    return (originalValue - 1);
}


inline int32_t atomic_conditional_increment( int32_t * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int32_t tmp = fetch_and_add( pw, 0 );
    for( ;; )
    {
        if( tmp == 0 ) return 0;
        if( compare_and_swap( pw, &tmp, tmp + 1 ) ) return (tmp + 1);
    }
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return fetch_and_add( const_cast<int32_t*>(&use_count_), 0 );
    }


inline void atomic_increment( int * pw )
{
    // ++*pw;

    int tmp;

    // No barrier is required here but fetchadd always has an acquire or
    // release barrier associated with it.  We choose release as it should be
    // cheaper.
    __asm__ ("fetchadd4.rel %0=%1,1" :
         "=r"(tmp), "=m"(*pw) :
         "m"( *pw ));
}


inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv;

    __asm__ ("     fetchadd4.rel %0=%1,-1 ;; \n"
             "     cmp.eq        p7,p0=1,%0 ;; \n"
             "(p7) ld4.acq       %0=%1    " :
             "=&r"(rv), "=m"(*pw) :
             "m"( *pw ) :
             "p7");

    return rv;
}


inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv, tmp, tmp2;

    __asm__ ("0:   ld4          %0=%3           ;; \n"
         "     cmp.eq       p7,p0=0,%0        ;; \n"
         "(p7) br.cond.spnt 1f                \n"
         "     mov          ar.ccv=%0         \n"
         "     add          %1=1,%0           ;; \n"
         "     cmpxchg4.acq %2=%3,%1,ar.ccv ;; \n"
         "     cmp.ne       p7,p0=%0,%2       ;; \n"
         "(p7) br.cond.spnt 0b                \n"
         "     mov          %0=%1             ;; \n"
         "1:" : 
         "=&r"(rv), "=&r"(tmp), "=&r"(tmp2), "=m"(*pw) :
         "m"( *pw ) :
         "ar.ccv", "p7");

    return rv;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ ); // TODO use ld.acq here
    }


        scoped_lock(pthread_mutex_t & m): m_(m)
        {
            pthread_mutex_lock(&m_);
        }


        ~scoped_lock()
        {
            pthread_mutex_unlock(&m_);
        }


    explicit atomic_count(long v): value_(v)
    {
        pthread_mutex_init(&mutex_, 0);
    }


    ~atomic_count()
    {
        pthread_mutex_destroy(&mutex_);
    }


    long operator++()
    {
        scoped_lock lock(mutex_);
        return ++value_;
    }


    long operator--()
    {
        scoped_lock lock(mutex_);
        return --value_;
    }


    operator long() const
    {
        scoped_lock lock(mutex_);
        return value_;
    }


inline void atomic_increment( sp_int32_t * pw )
{
    __sync_fetch_and_add( pw, 1 );
}


inline sp_int32_t atomic_decrement( sp_int32_t * pw )
{
    return __sync_fetch_and_add( pw, -1 );
}


inline sp_int32_t atomic_conditional_increment( sp_int32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    sp_int32_t r = *pw;

    for( ;; )
    {
        if( r == 0 )
        {
            return r;
        }

        sp_int32_t r2 = __sync_val_compare_and_swap( pw, r, r + 1 );

        if( r2 == r )
        {
            return r;
        }
        else
        {
            r = r2;
        }
    }    
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return const_cast< sp_int32_t const volatile & >( use_count_ );
    }


inline void atomic_increment( int *pw )
{
   // ++*pw;
   __lwsync();
   __fetch_and_add(pw, 1);
   __isync();
}
 

inline int atomic_decrement( int *pw )
{
   // return --*pw;
   __lwsync();
   int originalValue = __fetch_and_add(pw, -1);
   __isync();

   return (originalValue - 1);
}


inline int atomic_conditional_increment( int *pw )
{
   // if( *pw != 0 ) ++*pw;
   // return *pw;

   __lwsync();
   int v = *const_cast<volatile int*>(pw);
   for (;;)
   // loop until state is known
   {
      if (v == 0) return 0;
      if (__compare_and_swap(pw, &v, v + 1))
      {
         __isync(); return (v + 1);
      }
   }
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return *const_cast<volatile int*>(&use_count_); 
    }


    bool try_lock()
    {
        int r = __sync_lock_test_and_set( &v_, 1 );
        return r == 0;
    }


    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }


    void unlock()
    {
        __sync_lock_release( &v_ );
    }


        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


    explicit atomic_count( uint32_t v ): value_( v )
    {
    }


    long operator++()
    {
        return atomic_inc_32_nv( &value_ );
    }


    long operator--()
    {
        return atomic_dec_32_nv( &value_ );
    }


    explicit atomic_count( long v ) : value_( v ) {}


    long operator++()
    {
        return __exchange_and_add( &value_, +1 ) + 1;
    }


    long operator--()
    {
        return __exchange_and_add( &value_, -1 ) - 1;
    }


    operator long() const
    {
        return __exchange_and_add( &value_, 0 );
    }


    bool try_lock()
    {
        return pthread_mutex_trylock( &v_ ) == 0;
    }


    void lock()
    {
        pthread_mutex_lock( &v_ );
    }


    void unlock()
    {
        pthread_mutex_unlock( &v_ );
    }


        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


    explicit sp_reference_wrapper( T & t): t_( boost::addressof( t ) )
    {
    }


    template< class Y > void operator()( Y * p ) const
    {
        (*t_)( p );
    }


    shared_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }


    template<class Y> explicit shared_count( Y * p ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_p<Y>( p );
        }
        catch(...)
        {
            boost::checked_delete( p );
            throw;
        }

#else

        pi_ = new sp_counted_impl_p<Y>( p );

        if( pi_ == 0 )
        {
            boost::checked_delete( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif
    }

    template<class P, class D> shared_count( P p, D d ): pi_(0)
#endif
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1200 )
        typedef Y* P;
#endif
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_pd<P, D>(p, d);
        }
        catch(...)
        {
            d(p); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_impl_pd<P, D>(p, d);

        if(pi_ == 0)
        {
            d(p); // delete p
            boost::throw_exception(std::bad_alloc());
        }

#endif
    }


    template< class P, class D > shared_count( P p, sp_inplace_tag<D> ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_pd< P, D >( p );
        }
        catch( ... )
        {
            D::operator_fn( p ); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_impl_pd< P, D >( p );

        if( pi_ == 0 )
        {
            D::operator_fn( p ); // delete p
            boost::throw_exception( std::bad_alloc() );
        }

#endif // #ifndef BOOST_NO_EXCEPTIONS
    }


    template<class P, class D, class A> shared_count( P p, D d, A a ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef sp_counted_impl_pda<P, D, A> impl_type;
        typedef typename A::template rebind< impl_type >::other A2;

        A2 a2( a );

#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = a2.allocate( 1, static_cast< impl_type* >( 0 ) );
            new( static_cast< void* >( pi_ ) ) impl_type( p, d, a );
        }
        catch(...)
        {
            d( p );

            if( pi_ != 0 )
            {
                a2.deallocate( static_cast< impl_type* >( pi_ ), 1 );
            }

            throw;
        }

#else

        pi_ = a2.allocate( 1, static_cast< impl_type* >( 0 ) );

        if( pi_ != 0 )
        {
            new( static_cast< void* >( pi_ ) ) impl_type( p, d, a );
        }
        else
        {
            d( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif
    }


    template< class P, class D, class A > shared_count( P p, sp_inplace_tag< D >, A a ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef sp_counted_impl_pda< P, D, A > impl_type;
        typedef typename A::template rebind< impl_type >::other A2;

        A2 a2( a );

#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = a2.allocate( 1, static_cast< impl_type* >( 0 ) );
            new( static_cast< void* >( pi_ ) ) impl_type( p, a );
        }
        catch(...)
        {
            D::operator_fn( p );

            if( pi_ != 0 )
            {
                a2.deallocate( static_cast< impl_type* >( pi_ ), 1 );
            }

            throw;
        }

#else

        pi_ = a2.allocate( 1, static_cast< impl_type* >( 0 ) );

        if( pi_ != 0 )
        {
            new( static_cast< void* >( pi_ ) ) impl_type( p, a );
        }
        else
        {
            D::operator_fn( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif // #ifndef BOOST_NO_EXCEPTIONS
    }


    ~shared_count() // nothrow
    {
        if( pi_ != 0 ) pi_->release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }


    shared_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if( pi_ != 0 ) pi_->add_ref_copy();
    }


    shared_count(shared_count && r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        r.pi_ = 0;
    }


    shared_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if( tmp != 0 ) tmp->add_ref_copy();
            if( pi_ != 0 ) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }


    void swap(shared_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }


    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }


    bool unique() const // nothrow
    {
        return use_count() == 1;
    }


    bool empty() const // nothrow
    {
        return pi_ == 0;
    }


    void * get_deleter( sp_typeinfo const & ti ) const
    {
        return pi_? pi_->get_deleter( ti ): 0;
    }


    void * get_untyped_deleter() const
    {
        return pi_? pi_->get_untyped_deleter(): 0;
    }


    weak_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
    }


    weak_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }


    weak_count(weak_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }


    weak_count(weak_count && r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        r.pi_ = 0;
    }


    ~weak_count() // nothrow
    {
        if(pi_ != 0) pi_->weak_release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }


    weak_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if(tmp != 0) tmp->weak_add_ref();
            if(pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }


    weak_count & operator= (weak_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if(tmp != 0) tmp->weak_add_ref();
            if(pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }


    void swap(weak_count & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }


    long use_count() const // nothrow
    {
        return pi_ != 0? pi_->use_count(): 0;
    }


    bool empty() const // nothrow
    {
        return pi_ == 0;
    }


inline shared_count::shared_count( weak_count const & r ): pi_( r.pi_ )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if( pi_ == 0 || !pi_->add_ref_lock() )
    {
        boost::throw_exception( boost::bad_weak_ptr() );
    }
}


inline shared_count::shared_count( weak_count const & r, sp_nothrow_tag ): pi_( r.pi_ )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if( pi_ != 0 && !pi_->add_ref_lock() )
    {
        pi_ = 0;
    }
}


    static spinlock & spinlock_for( void const * pv )
    {
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64  
        std::size_t i = reinterpret_cast< unsigned long long >( pv ) % 41;
#else  
        std::size_t i = reinterpret_cast< std::size_t >( pv ) % 41;
#endif  
        return pool_[ i ];
    }


        explicit scoped_lock( void const * pv ): sp_( spinlock_for( pv ) )
        {
            sp_.lock();
        }


        ~scoped_lock()
        {
            sp_.unlock();
        }


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        ++use_count_;
    }


    bool add_ref_lock() // true on success
    {
        if( use_count_ == 0 ) return false;
        ++use_count_;
        return true;
    }


    void release() // nothrow
    {
        if( --use_count_ == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        ++weak_count_;
    }


    void weak_release() // nothrow
    {
        if( --weak_count_ == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return use_count_;
    }


inline void atomic_increment( int * pw )
{
    // ++*pw;

    _Asm_fetchadd(_FASZ_W, _SEM_REL, pw, +1, _LDHINT_NONE);
}
 

inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int r = static_cast<int>(_Asm_fetchadd(_FASZ_W, _SEM_REL, pw, -1, _LDHINT_NONE));
    if (1 == r)
    {
        _Asm_mf();
    }
    
    return r - 1;
}


inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int v = *pw;
    
    for (;;)
    {
        if (0 == v)
        {
            return 0;
        }
        
        _Asm_mov_to_ar(_AREG_CCV,
                       v,
                       (_UP_CALL_FENCE | _UP_SYS_FENCE | _DOWN_CALL_FENCE | _DOWN_SYS_FENCE));
        int r = static_cast<int>(_Asm_cmpxchg(_SZ_W, _SEM_ACQ, pw, v + 1, _LDHINT_NONE));
        if (r == v)
        {
            return r + 1;
        }
        
        v = r;
    }
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ ); // TODO use ld.acq here
    }


    explicit shared_ptr(T * p = 0): px(p)
    {
#ifndef BOOST_NO_EXCEPTIONS

        try  // prevent leak if new throws
        {
            pn = new count_type(1);
        }
        catch(...)
        {
            boost::checked_delete(p);
            throw;
        }

#else

        pn = new count_type(1);

        if(pn == 0)
        {
            boost::checked_delete(p);
            boost::throw_exception(std::bad_alloc());
        }

#endif
    }


    ~shared_ptr()
    {
        if(--*pn == 0)
        {
            boost::checked_delete(px);
            delete pn;
        }
    }


    shared_ptr(shared_ptr const & r): px(r.px)  // never throws
    {
        pn = r.pn;
        ++*pn;
    }


    shared_ptr & operator=(shared_ptr const & r)
    {
        shared_ptr(r).swap(*this);
        return *this;
    }


    void reset(T * p = 0)
    {
        BOOST_ASSERT(p == 0 || p != px);
        shared_ptr(p).swap(*this);
    }


    T & operator*() const  // never throws
    {
        BOOST_ASSERT(px != 0);
        return *px;
    }


    T * operator->() const  // never throws
    {
        BOOST_ASSERT(px != 0);
        return px;
    }


    T * get() const  // never throws
    {
        return px;
    }


    long use_count() const  // never throws
    {
        return *pn;
    }


    bool unique() const  // never throws
    {
        return *pn == 1;
    }

    
    void swap(shared_ptr<T> & other)  // never throws
    {
        std::swap(px, other.px);
        std::swap(pn, other.pn);
    }


template<class T, class U> inline bool operator==(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}


template<class T, class U> inline bool operator!=(shared_ptr<T> const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}


template<class T> inline bool operator<(shared_ptr<T> const & a, shared_ptr<T> const & b)
{
    return std::less<T*>()(a.get(), b.get());
}


template<class T> void swap(shared_ptr<T> & a, shared_ptr<T> & b)
{
    a.swap(b);
}


template<class T> inline T * get_pointer(shared_ptr<T> const & p)
{
    return p.get();
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        BOOST_INTERLOCKED_INCREMENT( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            long tmp = static_cast< long const volatile& >( use_count_ );
            if( tmp == 0 ) return false;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1200 )

            // work around a code generation bug

            long tmp2 = tmp + 1;
            if( BOOST_INTERLOCKED_COMPARE_EXCHANGE( &use_count_, tmp2, tmp ) == tmp2 - 1 ) return true;

#else

            if( BOOST_INTERLOCKED_COMPARE_EXCHANGE( &use_count_, tmp + 1, tmp ) == tmp ) return true;

#endif
        }
    }


    void release() // nothrow
    {
        if( BOOST_INTERLOCKED_DECREMENT( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        BOOST_INTERLOCKED_INCREMENT( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( BOOST_INTERLOCKED_DECREMENT( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<long const volatile &>( use_count_ );
    }


    explicit atomic_count( long v ) : value_( static_cast< int >( v ) ) {}


    long operator++()
    {
        return atomic_exchange_and_add( &value_, +1 ) + 1;
    }


    long operator--()
    {
        return atomic_exchange_and_add( &value_, -1 ) - 1;
    }


    operator long() const
    {
        return atomic_exchange_and_add( &value_, 0 );
    }


    static int atomic_exchange_and_add( int * pw, int dv )
    {
        // int r = *pw;
        // *pw += dv;
        // return r;

        int r;

        __asm__ __volatile__
        (
            "lock\n\t"
            "xadd %1, %0":
            "+m"( *pw ), "=r"( r ): // outputs (%0, %1)
            "1"( dv ): // inputs (%2 == %1)
            "memory", "cc" // clobbers
        );

        return r;
    }


inline int atomic_exchange_and_add( int * pw, int dv )
{
    spinlock_pool<1>::scoped_lock lock( pw );

    int r = *pw;
    *pw += dv;
    return r;
}


inline void atomic_increment( int * pw )
{
    spinlock_pool<1>::scoped_lock lock( pw );
    ++*pw;
}


inline int atomic_conditional_increment( int * pw )
{
    spinlock_pool<1>::scoped_lock lock( pw );

    int rv = *pw;
    if( rv != 0 ) ++*pw;
    return rv;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_exchange_and_add( &use_count_, -1 ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_exchange_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        spinlock_pool<1>::scoped_lock lock( &use_count_ );
        return use_count_;
    }


inline int atomic_exchange_and_add( int * pw, int dv )
{
    // int r = *pw;
    // *pw += dv;
    // return r;

    int r;

    __asm__ __volatile__
    (
        "lock\n\t"
        "xadd %1, %0":
        "=m"( *pw ), "=r"( r ): // outputs (%0, %1)
        "m"( *pw ), "1"( dv ): // inputs (%2, %3 == %1)
        "memory", "cc" // clobbers
    );

    return r;
}


inline void atomic_increment( int * pw )
{
    //atomic_exchange_and_add( pw, 1 );

    __asm__
    (
        "lock\n\t"
        "incl %0":
        "=m"( *pw ): // output (%0)
        "m"( *pw ): // input (%1)
        "cc" // clobbers
    );
}


inline int atomic_conditional_increment( int * pw )
{
    // int rv = *pw;
    // if( rv != 0 ) ++*pw;
    // return rv;

    int rv, tmp;

    __asm__
    (
        "movl %0, %%eax\n\t"
        "0:\n\t"
        "test %%eax, %%eax\n\t"
        "je 1f\n\t"
        "movl %%eax, %2\n\t"
        "incl %2\n\t"
        "lock\n\t"
        "cmpxchgl %2, %0\n\t"
        "jne 0b\n\t"
        "1:":
        "=m"( *pw ), "=&a"( rv ), "=&r"( tmp ): // outputs (%0, %1, %2)
        "m"( *pw ): // input (%3)
        "cc" // clobbers
    );

    return rv;
}


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destroy() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }


    void release() // nothrow
    {
        if( atomic_exchange_and_add( &use_count_, -1 ) == 1 )
        {
            dispose();
            weak_release();
        }
    }


    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }


    void weak_release() // nothrow
    {
        if( atomic_exchange_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }


    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ );
    }

      
    explicit shared_array(T * p = 0): px(p)
    {
#ifndef BOOST_NO_EXCEPTIONS

        try  // prevent leak if new throws
        {
            pn = new count_type(1);
        }
        catch(...)
        {
            boost::checked_array_delete(p);
            throw;
        }

#else

        pn = new count_type(1);

        if(pn == 0)
        {
            boost::checked_array_delete(p);
            boost::throw_exception(std::bad_alloc());
        }

#endif
    }


    ~shared_array()
    {
        if(--*pn == 0)
        {
            boost::checked_array_delete(px);
            delete pn;
        }
    }


    shared_array(shared_array const & r) : px(r.px)  // never throws
    {
        pn = r.pn;
        ++*pn;
    }


    shared_array & operator=(shared_array const & r)
    {
        shared_array(r).swap(*this);
        return *this;
    }


    void reset(T * p = 0)
    {
        BOOST_ASSERT(p == 0 || p != px);
        shared_array(p).swap(*this);
    }


    T * get() const  // never throws
    {
        return px;
    }


    T & operator[](std::ptrdiff_t i) const  // never throws
    {
        BOOST_ASSERT(px != 0);
        BOOST_ASSERT(i >= 0);
        return px[i];
    }


    long use_count() const  // never throws
    {
        return *pn;
    }


    bool unique() const  // never throws
    {
        return *pn == 1;
    }


    void swap(shared_array<T> & other)  // never throws
    {
        std::swap(px, other.px);
        std::swap(pn, other.pn);
    }


template<class T, class U> inline bool operator==(shared_array<T> const & a, shared_array<U> const & b)
{
    return a.get() == b.get();
}


template<class T, class U> inline bool operator!=(shared_array<T> const & a, shared_array<U> const & b)
{
    return a.get() != b.get();
}


template<class T> inline bool operator<(shared_array<T> const & a, shared_array<T> const & b)
{
    return std::less<T*>()(a.get(), b.get());
}


template<class T> void swap(shared_array<T> & a, shared_array<T> & b)
{
    a.swap(b);
}
