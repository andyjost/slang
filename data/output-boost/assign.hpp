
        generic_ptr_list() : values_( 32u )
        { }


        release_type release()
        {
            return values_.release();
        }

        iterator begin() const       { return values_.begin(); }

        iterator end() const         { return values_.end(); }

        bool empty() const           { return values_.empty(); }

        size_type size() const       { return values_.size(); }

    template< class T >
    inline assign_detail::generic_ptr_list<T>
    ptr_list_of()
    {
        return assign_detail::generic_ptr_list<T>()();
    }

    
    template< class T, class U >
    inline assign_detail::generic_ptr_list<T> 
    ptr_list_of( const U& t )
    {
        return assign_detail::generic_ptr_list<T>()( t );
    }

            assignment_exception( const char* _what ) 
            : what_( _what )
            { }

        
            virtual const char* what() const throw()
            {
                return what_;
            }

        
        iterator begin() const 
        {
            return static_cast<const DerivedTAssign*>(this)->begin();
        }


        iterator end() const
        {
            return static_cast<const DerivedTAssign*>(this)->end();
        }


        template< class Container >
        Container convert_to_container() const
        {
            static Container* c = 0;
            BOOST_STATIC_CONSTANT( bool, is_array_flag = sizeof( assign_detail::assign_is_array( c ) ) 
                                   == sizeof( type_traits::yes_type ) );

            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< is_array_flag,
                                                      array_type_tag,
                                             default_type_tag >::type tag_type;

            return convert<Container>( c, tag_type() );
        }

        
        template< class Container >
        Container convert( const Container*, default_type_tag ) const
        {

#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
// old Dinkumware doesn't support iterator type as template
            Container result;
            iterator it  = begin(), 
                     e   = end();
            while( it != e )
            {
                result.insert( result.end(), *it );
                ++it;
            }
            return result;
#else
            return Container( begin(), end() );
#endif
        }


        template< class Array >
        Array convert( const Array*, array_type_tag ) const
        {
            typedef BOOST_DEDUCED_TYPENAME Array::value_type value_type;

#if BOOST_WORKAROUND(BOOST_INTEL, <= 910 ) || BOOST_WORKAROUND(__SUNPRO_CC, <= 0x580 )
            BOOST_DEDUCED_TYPENAME remove_const<Array>::type ar;
#else
            Array ar;
#endif            
            const std::size_t sz = ar.size();
            if( sz < static_cast<const DerivedTAssign*>(this)->size() )
                throw assign::assignment_exception( "array initialized with too many elements" );
            std::size_t n = 0; 
            iterator i   = begin(), 
                     e   = end();
            for( ; i != e; ++i, ++n )
                ar[n] = *i;
            for( ; n < sz; ++n )
                ar[n] = value_type();
            return ar; 
        }


        template< class Adapter >
        Adapter convert_to_adapter( const Adapter* = 0 ) const
        {
            Adapter a;
            iterator i   = begin(), 
                     e   = end();
            for( ; i != e; ++i )
                a.push( *i );
            return a;
        }

            adapter_converter( const converter& this_ ) : gl( this_ )
            {}


            adapter_converter( const adapter_converter& r ) 
            : gl( r.gl )
            { }


            template< class Adapter >
            operator Adapter() const
            {
                return gl.convert_to_adapter<Adapter>();
            }
 
        template< class Container >
        Container to_container( Container& c ) const
        {
            return convert( &c, default_type_tag() ); 
        }


        adapter_converter to_adapter() const
        {
            return adapter_converter( *this );
        }


        template< class Adapter >
        Adapter to_adapter( Adapter& a ) const
        {
            return this->convert_to_adapter( &a ); 
        }


        template< class Array >
        Array to_array( Array& a ) const
        {
            return convert( &a, array_type_tag() );
        }


    template< class T, class I, class Range >
    inline bool operator==( const converter<T,I>& l, const Range& r )
    {
        return ::boost::iterator_range_detail::equal( l, r );
    }


    template< class T, class I, class Range >
    inline bool operator==( const Range& l, const converter<T,I>& r )
    {
        return r == l;
    }


    template< class T, class I, class Range >
    inline bool operator!=( const converter<T,I>& l, const Range& r )
    {
        return !( l == r );
    }

    
    template< class T, class I, class Range >
    inline bool operator!=( const Range& l, const converter<T,I>& r )
    {
        return !( l == r );
    }


    template< class T, class I, class Range >
    inline bool operator<( const converter<T,I>& l, const Range& r )
    {
        return ::boost::iterator_range_detail::less_than( l, r );
    }


    template< class T, class I, class Range >
    inline bool operator<( const Range& l, const converter<T,I>& r )
    {
        return ::boost::iterator_range_detail::less_than( l, r );
    }


    template< class T, class I, class Range >
    inline bool operator>( const converter<T,I>& l, const Range& r )
    {
        return r < l;
    }


    template< class T, class I, class Range >
    inline bool operator>( const Range& l, const converter<T,I>& r )
    {
        return r < l;
    }


    template< class T, class I, class Range >
    inline bool operator<=( const converter<T,I>& l, const Range& r )
    {
        return !( l > r );
    }


    template< class T, class I, class Range >
    inline bool operator<=( const Range& l, const converter<T,I>& r )
    {
        return !( l > r );
    }

    
    template< class T, class I, class Range >
    inline bool operator>=( const converter<T,I>& l, const Range& r )
    {
        return !( l < r );
    }


    template< class T, class I, class Range >
    inline bool operator>=( const Range& l, const converter<T,I>& r )
    {
        return !( l < r );
    }

        assign_reference()
        { /* intentionally empty */ }


        assign_reference( T& r ) : ref_(&r)
        { }


        void operator=( T& r )
        {
            ref_ = &r;
        }


        operator T&() const
        {
            return *ref_;
        }


        void swap( assign_reference& r )
        {
            std::swap( *ref_, *r.ref_ );
        }


        T& get_ref() const
        {
            return *ref_;
        }


    template< class T >
    inline bool operator<( const assign_reference<T>& l, 
                           const assign_reference<T>& r )
    {
        return l.get_ref() < r.get_ref();
    }


    template< class T >
    inline bool operator>( const assign_reference<T>& l,
                           const assign_reference<T>& r )
    {
        return l.get_ref() > r.get_ref();
    }


    template< class T >
    inline void swap( assign_reference<T>& l, 
                      assign_reference<T>& r )
    {
        l.swap( r );
    }


    
        static_generic_list( T& r ) :
            current_(1)
        {
            refs_[0] = r;
        }


        static_generic_list& operator()( T& r )
        {
            insert( r );
            return *this;
        }


        iterator begin() const 
        {
            return &refs_[0];
        }


        iterator end() const
        {
            return &refs_[current_];
        }


        size_type size() const
        {
            return static_cast<size_type>( current_ ); 
        }


        bool empty() const
        {
            return false;
        }


        template< class ForwardIterator >
        static_generic_list& range( ForwardIterator first, 
                                    ForwardIterator last )
        {
            for( ; first != last; ++first )
                this->insert( *first );
            return *this;
        }


        template< class ForwardRange >
        static_generic_list& range( ForwardRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }


        template< class ForwardRange >
        static_generic_list& range( const ForwardRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }


        template< class Container >
        operator Container() const
        {
            return this-> BOOST_NESTED_TEMPLATE convert_to_container<Container>();
        }

        void insert( T& r )
        {
            refs_[current_] = r;
            ++current_;
        }


        repeater( std::size_t sz_, T r ) : sz( sz_ ), val( r )
        { }

        
        fun_repeater( std::size_t sz_, Fun r ) : sz( sz_ ), val( r )
        { }

        call_push_back( C& c ) : c_( c )
        { }

        
        template< class T >
        void operator()( T r ) 
        {
            c_.push_back( r );
        }

        call_push_front( C& c ) : c_( c )
        { }

        
        template< class T >
        void operator()( T r ) 
        {
            c_.push_front( r );
        }

        call_push( C& c ) : c_( c )
        { }

    
        template< class T >
        void operator()( T r ) 
        {
            c_.push( r );
        }

        call_insert( C& c ) : c_( c )
        { }

    
        template< class T >
        void operator()( T r ) 
        {
            c_.insert( r );
        }

        call_add_edge( C& c ) : c_(c)
        { }


        template< class T >
        void operator()( T l, T r )
        {
            add_edge( l, r, c_ );
        }


        template< class T, class EP >
        void operator()( T l, T r, const EP& ep )
        {
            add_edge( l, r, ep, c_ );
        }


    template< class T >
    inline assign_detail::repeater<T>
    repeat( std::size_t sz, T r )
    {
        return assign_detail::repeater<T>( sz, r );
    }

    
    template< class Function >
    inline assign_detail::fun_repeater<Function>
    repeat_fun( std::size_t sz, Function r )
    {
        return assign_detail::fun_repeater<Function>( sz, r );
    }

        
        list_inserter( Function fun ) : insert_( fun )
        {}

        
        template< class Function2, class Arg >
        list_inserter( const list_inserter<Function2,Arg>& r ) 
        : insert_( r.fun_private() ) 
        {}


        list_inserter( const list_inserter& r ) : insert_( r.insert_ )
        {}


        list_inserter& operator()()
        {
            insert_( Argument() );
            return *this;
        }

        
        template< class T >
        list_inserter& operator=( const T& r )
        {
            insert_( r );
            return *this;
        }

        
        template< class T >
        list_inserter& operator=( assign_detail::repeater<T> r )
        {
            return operator,( r );
        }

        
        template< class Nullary_function >
        list_inserter& operator=( const assign_detail::fun_repeater<Nullary_function>& r )
        {
            return operator,( r );
        }

        
        template< class T >
        list_inserter& operator,( const T& r )
        {
            insert_( r  );
            return *this;
        }

        template< class T >
        list_inserter& operator,( assign_detail::repeater<T> r )
        {
            return repeat( r.sz, r.val ); 
        }

        
        template< class Nullary_function >
        list_inserter& operator,( const assign_detail::fun_repeater<Nullary_function>& r )
        {
            return repeat_fun( r.sz, r.val ); 
        }


        template< class T >
        list_inserter& repeat( std::size_t sz, T r )
        {
            std::size_t i = 0;
            while( i++ != sz )
                insert_( r );
            return *this;
        }

        
        template< class Nullary_function >
        list_inserter& repeat_fun( std::size_t sz, Nullary_function fun )
        {
            std::size_t i = 0;
            while( i++ != sz )
                insert_( fun() );
            return *this;
        }


        template< class SinglePassIterator >
        list_inserter& range( SinglePassIterator first, 
                              SinglePassIterator last )
        {
            for( ; first != last; ++first )
                insert_( *first );
            return *this;
        }

        
        template< class SinglePassRange >
        list_inserter& range( const SinglePassRange& r )
        {
            return range( boost::begin(r), boost::end(r) );
        }

        
        template< class T >
        list_inserter& operator()( const T& t )
        {
            insert_( t );
            return *this;
        }


        
        Function fun_private() const
        {
            return insert_;
        }

    
    template< class Function >
    inline list_inserter< Function >
    make_list_inserter( Function fun )
    {
        return list_inserter< Function >( fun );
    }

    
    template< class Function, class Argument >
    inline list_inserter<Function,Argument>
    make_list_inserter( Function fun, Argument* )
    {
        return list_inserter<Function,Argument>( fun );
    }


    template< class C >
    inline list_inserter< assign_detail::call_push_back<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push_back( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push_back<C>( c ), 
                                   p );
    }

    
    template< class C >
    inline list_inserter< assign_detail::call_push_front<C>,
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push_front( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push_front<C>( c ),
                                   p );
    }


    template< class C >
    inline list_inserter< assign_detail::call_insert<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    insert( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_insert<C>( c ),
                                   p );
    }


    template< class C >
    inline list_inserter< assign_detail::call_push<C>, 
                          BOOST_DEDUCED_TYPENAME C::value_type >
    push( C& c )
    {
        static BOOST_DEDUCED_TYPENAME C::value_type* p = 0;
        return make_list_inserter( assign_detail::call_push<C>( c ),
                                   p );
    }


    template< class C >
    inline list_inserter< assign_detail::call_add_edge<C> >
    add_edge( C& c )   
    {
        return make_list_inserter( assign_detail::call_add_edge<C>( c ) );
    }

        
        ptr_map_inserter( PtrMap& m ) : m_( m )
        {}

        
        template< class Key >
        ptr_map_inserter& operator()( const Key& t )
        {
            key_type k(t);
            m_.insert( k, new obj_type );
            return *this;
        }

    
    template< class PtrMap >
    inline ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, typename PtrMap::mapped_reference >( m );
    }


    template< class T, class PtrMap >
    inline ptr_map_inserter< PtrMap, T >
    ptr_map_insert( PtrMap& m )
    {
        return ptr_map_inserter< PtrMap, T >( m );
    }

        
        ptr_list_inserter( Function fun ) : insert_( fun )
        {}

        
        template< class Function2, class Obj2 >
        ptr_list_inserter( const ptr_list_inserter<Function2,Obj2>& r ) 
        : insert_( r.fun_private() ) 
        {}


        ptr_list_inserter( const ptr_list_inserter& r ) : insert_( r.insert_ )
        {}


        ptr_list_inserter& operator()()
        {
            insert_( new obj_type() );
            return *this;
        }

        
        template< class T >
        ptr_list_inserter& operator()( const T& t )
        {
            insert_( new obj_type(t) );
            return *this;
        }

    
    template< class Obj, class Function >
    inline ptr_list_inserter< Function, Obj >
    make_ptr_list_inserter( Function fun )
    {
        return ptr_list_inserter< Function, Obj >( fun );
    }
