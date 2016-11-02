
    
    template< class T >
    inline T* new_clone( const T& r )
    {
        //
        // @remark: if you get a compile-error here,
        //          it is most likely because you did not
        //          define new_clone( const T& ) in the namespace
        //          of T.
        //
        T* res = new T( r );
        BOOST_ASSERT( typeid(r) == typeid(*res) &&
                      "Default new_clone() sliced object!" );
        return res;
    }


    template< class T >
    inline T* new_clone( const T* r )
    {
        return r ? new_clone( *r ) : 0;
    }

    
    template< class T >
    inline void delete_clone( const T* r )
    {
        checked_delete( r );
    }

        template< class U >
        static U* allocate_clone( const U& r )
        {
            return new_clone( r );
        }


        template< class U >
        static void deallocate_clone( const U* r )
        {
            delete_clone( r );
        }

        template< class U >
        static U* allocate_clone( const U& r )
        {
            return const_cast<U*>(&r);
        }


        template< class U >
        static void deallocate_clone( const U* /*r*/ )
        {
            // do nothing
        }
           
       
       template< class Iter >
       static Key* get_pointer( Iter i )
       {
           return static_cast<Key*>( *i.base() );
       }


       template< class Iter >
       static const Key* get_const_pointer( Iter i )
       {
           return static_cast<const Key*>( *i.base() );
       }

        ptr_set_adapter_base() 
        { }

                
        template< class Compare, class Allocator >
        ptr_set_adapter_base( const Compare& comp,
                              const Allocator& a ) 
         : base_type( comp, a ) 
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_set_adapter_base( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }


        template< class InputIterator, class Compare, class Allocator >
        ptr_set_adapter_base( InputIterator first, InputIterator last,
                              const Compare& comp,
                              const Allocator& a ) 
         : base_type( first, last, comp, a ) 
        { }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_set_adapter_base( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }

               
        template< class U, class Set, class CA, bool b >
        ptr_set_adapter_base( const ptr_set_adapter_base<U,Set,CA,b>& r )
          : base_type( r )
        { }


        ptr_set_adapter_base( const ptr_set_adapter_base& r )
          : base_type( r )
        { }

        
        ptr_set_adapter_base& operator=( ptr_set_adapter_base r ) 
        {
            this->swap( r );
            return *this;
        }

        
        size_type erase( const key_type& x ) // nothrow
        {
            key_type* key = const_cast<key_type*>(&x);
            iterator i( this->base().find( key ) );       
            if( i == this->end() )                                  // nothrow
                return 0u;                                          // nothrow
            key = static_cast<key_type*>(*i.base());                // nothrow
            size_type res = this->base().erase( key );              // nothrow 
            this->remove( key );                                    // nothrow
            return res;
        }



        iterator find( const key_type& x )                                                
        {                                                                            
            return iterator( this->base().
                             find( const_cast<key_type*>(&x) ) );            
        }
                                                                            

        size_type count( const key_type& x ) const                                        
        {                                                                            
            return this->base().count( const_cast<key_type*>(&x) );                      
        }
                                                                            
                                                                                     
        iterator lower_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().
                             lower_bound( const_cast<key_type*>(&x) ) );                   
        }
                                                                            
                                                                                     
        iterator upper_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().
                             upper_bound( const_cast<key_type*>(&x) ) );           
        }

        
        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {                                                                     
            while( first != last )                                            
            {           
                if( this->find( *first ) == this->end() )
                    insert( CloneAllocator::allocate_clone( *first ) ); // strong, commit
                ++first;                                                      
            }                                                                 
        }

        ptr_set_adapter()
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_set_adapter( const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
         : base_type( hash, pred, a )
        { }


        template< class InputIterator >
        ptr_set_adapter( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }


        template< class InputIterator, class Compare, class Allocator >
        ptr_set_adapter( InputIterator first, InputIterator last, 
                         const Compare& comp,
                         const Allocator a = Allocator() )
          : base_type( comp, a )
        {
            BOOST_ASSERT( this->empty() );
            set_basic_clone_and_insert( first, last );
        }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_set_adapter( InputIterator first, InputIterator last,
                         const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
          : base_type( first, last, hash, pred, a )
        { }


        explicit ptr_set_adapter( const ptr_set_adapter& r )
          : base_type( r )
        { }


        template< class U, class Set, class CA, bool b >
        explicit ptr_set_adapter( const ptr_set_adapter<U,Set,CA,b>& r )
          : base_type( r )
        { }


        template< class U, class Set, class CA, bool b >
        ptr_set_adapter& operator=( const ptr_set_adapter<U,Set,CA,b>& r ) 
        {
            base_type::operator=( r );
            return *this;
        }

        template< typename II >                                               
        void set_basic_clone_and_insert( II first, II last ) // basic                 
        {               
            while( first != last )                                            
            {           
                insert( CloneAllocator::allocate_clone( *first ) ); // strong, commit                              
                ++first;                                                     
            }                                                                 
        }

        ptr_multiset_adapter()
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_multiset_adapter( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }


        template< class InputIterator >
        ptr_multiset_adapter( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_multiset_adapter( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }

                
        template< class U, class Set, class CA, bool b >
        explicit ptr_multiset_adapter( const ptr_multiset_adapter<U,Set,CA,b>& r )
          : base_type( r )
        { }


        template< class U, class Set, class CA, bool b >
        ptr_multiset_adapter& operator=( const ptr_multiset_adapter<U,Set,CA,b>& r ) 
        {
            base_type::operator=( r );
            return *this;
        }


        iterator insert( iterator before, key_type* x ) // strong  
        {
            return base_type::insert( before, x ); 
        }

    
        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            set_basic_clone_and_insert( first, last );
        }

        indirect_fun() : fun(Fun())
        { }

        
        indirect_fun( Fun f ) : fun(f)
        { }


    template< class Fun >
    inline indirect_fun<Fun> make_indirect_fun( Fun f )
    {
        return indirect_fun<Fun>( f );
    }

        
        void_ptr_indirect_fun() : fun(Fun())
        { }


        void_ptr_indirect_fun( Fun f ) : fun(f)
        { }


    template< class Arg, class Fun >
    inline void_ptr_indirect_fun<Fun,Arg> make_void_ptr_indirect_fun( Fun f )
    {
        return void_ptr_indirect_fun<Fun,Arg>( f );
    }


template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_map<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}
  
       
        template< class Iter >
        static U* get_pointer( Iter i )
        {
            return i->second;
        }


        template< class Iter >
        static const U* get_const_pointer( Iter i )
        {
            return i->second;
        }

        const_mapped_reference lookup( const key_type& key ) const
        {
           const_iterator i = this->find( key );
           if( i != this->end() )
               return *i->second;
           else                                           
               BOOST_PTR_CONTAINER_THROW_EXCEPTION( true, bad_ptr_container_operation,
                                                    "'ptr_map/multimap::at()' could"
                                                    " not find key" );
        }


            eraser( VoidPtrMap* m, const key_type& key ) 
              : released_(false), m_(m), key_(key)
            {}


            ~eraser() 
            {
                if( !released_ )
                    m_->erase(key_);
            }


            void release() { released_ = true; }


        mapped_reference insert_lookup( const key_type& key )
        {
            void*& ref = this->base()[key];
            if( ref )
            {
                return *static_cast<mapped_type>(ref);
            }
            else
            {
                eraser e(&this->base(),key);      // nothrow
                mapped_type res = new T();        // strong 
                ref = res;                        // nothrow
                e.release();                      // nothrow
                return *res;
            }
          }


        ptr_map_adapter_base()
        { }


        template< class Compare, class Allocator >
        ptr_map_adapter_base( const Compare& comp,
                              const Allocator& a ) 
        : base_type( comp, a ) 
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_map_adapter_base( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }

                
        template< class InputIterator >
        ptr_map_adapter_base( InputIterator first, InputIterator last )
         : base_type( first, last )
        { }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_map_adapter_base( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }

        
        template< typename PtrContainer >
        ptr_map_adapter_base& operator=( std::auto_ptr<PtrContainer> clone )    
        {
            base_type::operator=( clone );
            return *this;
        }
        

        iterator find( const key_type& x )                                                
        {                                                                            
            return iterator( this->base().find( x ) );                                
        }
                                                                            

        size_type count( const key_type& x ) const                                        
        {                                                                            
            return this->base().count( x );                                           
        }
                                                                            
                                                                                     
        iterator lower_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().lower_bound( x ) );                         
        }
                                                                            
                                                                                     
        iterator upper_bound( const key_type& x )                                         
        {                                                                            
            return iterator( this->base().upper_bound( x ) );                         
        }


        void safe_insert( const key_type& key, auto_type ptr ) // strong
        {
            std::pair<BOOST_DEDUCED_TYPENAME base_type::ptr_iterator,bool>
                res = 
                this->base().insert( std::make_pair( key, ptr.get() ) ); // strong, commit      
            if( res.second )                                             // nothrow     
                ptr.release();                                           // nothrow
        }


        template< class II >                                               
        void map_basic_clone_and_insert( II first, II last )                  
        {       
            while( first != last )                                            
            {                                            
                if( this->find( first->first ) == this->end() )
                {
                    const_reference p = *first.base();     // nothrow                    
                    auto_type ptr( this->null_policy_allocate_clone( p.second ) ); 
                                                           // strong 
                    this->safe_insert( p.first, 
                                       boost::ptr_container::move( ptr ) );
                                                           // strong, commit 
                }
                ++first;                                                      
            }                                                                 
        }

        ptr_map_adapter( )
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_map_adapter( const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
         : base_type( hash, pred, a )
        { }

                
        template< class InputIterator >
        ptr_map_adapter( InputIterator first, InputIterator last )
        {
            map_basic_clone_and_insert( first, last ); 
        }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_map_adapter( InputIterator first, InputIterator last,
                         const Hash& hash,
                         const Pred& pred,
                         const Allocator& a )
          : base_type( hash, pred, a )
        {
            map_basic_clone_and_insert( first, last ); 
        }

                
        ptr_map_adapter( const ptr_map_adapter& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }

        
        template< class Key, class U, class CA, bool b >
        ptr_map_adapter( const ptr_map_adapter<Key,U,CA,b>& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }


        ptr_map_adapter& operator=( ptr_map_adapter r )
        {
            this->swap( r );
            return *this;
        }


        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            map_basic_clone_and_insert( first, last );
        }


        template< class Range >
        void insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }


        void safe_insert( const key_type& key, auto_type ptr ) // strong
        {
            this->base().insert( 
                           std::make_pair( key, ptr.get() ) ); // strong, commit      
            ptr.release();                                     // nothrow
        }

        
        template< typename II >                                               
        void map_basic_clone_and_insert( II first, II last )                  
        {                                                         
            while( first != last )                                            
            {                                            
                const_reference pair = *first.base();     // nothrow                     
                auto_type ptr( this->null_policy_allocate_clone( pair.second ) );    
                                                          // strong
                safe_insert( pair.first, 
                             boost::ptr_container::move( ptr ) );
                                                          // strong, commit 
                ++first;                                                      
            }                                                                 
        }


        ptr_multimap_adapter()
        { }


        template< class Hash, class Pred, class Allocator >
        ptr_multimap_adapter( const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        { }


        template< class InputIterator >
        ptr_multimap_adapter( InputIterator first, InputIterator last )
        {
            map_basic_clone_and_insert( first, last );
        }


        template< class InputIterator, class Hash, class Pred, class Allocator >
        ptr_multimap_adapter( InputIterator first, InputIterator last,
                              const Hash& hash,
                              const Pred& pred,
                              const Allocator& a )
         : base_type( hash, pred, a )
        {
            map_basic_clone_and_insert( first, last ); 
        }


        ptr_multimap_adapter( const ptr_multimap_adapter& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }

        
        template< class Key, class U, class CA, bool b >
        ptr_multimap_adapter( const ptr_multimap_adapter<Key,U,CA,b>& r )
        {
            map_basic_clone_and_insert( r.begin(), r.end() );      
        }


        ptr_multimap_adapter& operator=( ptr_multimap_adapter r )
        {
            this->swap( r );
            return *this;
        }

        iterator insert_impl( const key_type& key, mapped_type x ) // strong
        {
            this->enforce_null_policy( x, 
                  "Null pointer in 'ptr_multimap_adapter::insert()'" );
            auto_type ptr( x );         // nothrow
            BOOST_DEDUCED_TYPENAME base_type::ptr_iterator
                res = this->base().insert( std::make_pair( key, x ) );
                                        // strong, commit        
            ptr.release();              // notrow
            return iterator( res );           
        }

        template< typename InputIterator >
        void insert( InputIterator first, InputIterator last ) // basic
        {
            map_basic_clone_and_insert( first, last );
        }


        template< class Range >
        void insert( const Range& r )
        {
            insert( boost::begin(r), boost::end(r) );
        }

        
        template< class PtrMapAdapter >
        void transfer( BOOST_DEDUCED_TYPENAME PtrMapAdapter::iterator object, 
                       PtrMapAdapter& from ) // strong
        {
            this->multi_transfer( object, from );
        }


    template< class I, class F, class S >
    inline bool is_null( const ptr_map_iterator<I,F,S>& i )
    {
        return i->second == 0;
    }


template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, unsigned int /*version*/)
{
    typedef ptr_vector<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}


template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}


template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_set<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

        template< class Iter >
        static U* get_pointer( void_ptr_iterator<Iter,U> i )
        {
            return static_cast<U*>( *i.base() );
        }

        template< class Iter >
        static const U* get_const_pointer( void_ptr_iterator<Iter,const U> i )
        {
            return static_cast<const U*>( *i.base() );
        }

                
        ptr_sequence_adapter()
        { }


        template< class Allocator >
        explicit ptr_sequence_adapter( const Allocator& a )
          : base_type( a )
        { }


        template< class InputIterator >
        ptr_sequence_adapter( InputIterator first, InputIterator last )
          : base_type( first, last )
        { }


        template< class InputIterator, class Allocator >
        ptr_sequence_adapter( InputIterator first, InputIterator last,
                              const Allocator& a )
          : base_type( first, last, a )
        { }


        ptr_sequence_adapter( const ptr_sequence_adapter& r )
          : base_type( r )
        { }

        
        template< class U >
        ptr_sequence_adapter( const ptr_sequence_adapter<U,VoidPtrSeq,CloneAllocator>& r )
          : base_type( r )
        { }


        ptr_sequence_adapter& operator=( const ptr_sequence_adapter r )
        {
            this->swap( r );
            return *this; 
        }


        void push_back( value_type x )  // strong               
        {
            this->enforce_null_policy( x, "Null pointer in 'push_back()'" );

            auto_type ptr( x );           // notrow
            this->base().push_back( x );  // strong, commit
            ptr.release();                // nothrow
        }

        
        void push_front( value_type x )                
        {
            this->enforce_null_policy( x, "Null pointer in 'push_front()'" );

            auto_type ptr( x );           // nothrow
            this->base().push_front( x ); // strong, commit
            ptr.release();                // nothrow
        }


        auto_type pop_back()
        {
            BOOST_ASSERT( !this->empty() && 
                          "'pop_back()' on empty container" );
            auto_type ptr( static_cast<value_type>( this->base().back() ) );      
                                                       // nothrow
            this->base().pop_back();                   // nothrow
            return ptr_container_detail::move( ptr );  // nothrow
        }


        auto_type pop_front()
        {
            BOOST_ASSERT( !this->empty() &&
                          "'pop_front()' on empty container" ); 
            auto_type ptr( static_cast<value_type>( this->base().front() ) ); 
                                         // nothrow 
            this->base().pop_front();    // nothrow
            return ptr_container_detail::move( ptr ); 
        }

        
        reference front()        
        { 
            BOOST_ASSERT( !this->empty() &&
                          "accessing 'front()' on empty container" );

            BOOST_ASSERT( !::boost::is_null( this->begin() ) );
            return *this->begin(); 
        }


        reference back()
        {
            BOOST_ASSERT( !this->empty() &&
                          "accessing 'back()' on empty container" );
            BOOST_ASSERT( !::boost::is_null( --this->end() ) );
            return *--this->end(); 
        }

        
        reference operator[]( size_type n ) // nothrow 
        {
            BOOST_ASSERT( n < this->size() );
            BOOST_ASSERT( !this->is_null( n ) );
            return *static_cast<value_type>( this->base()[n] ); 
        }

        
        reference at( size_type n )
        {
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( n >= this->size(), bad_index, 
                                                 "'at()' out of bounds" );
            BOOST_ASSERT( !this->is_null( n ) );
            return (*this)[n];
        }

        
        size_type capacity() const
        {
            return this->base().capacity();
        }

        
        void reserve( size_type n )
        {
            this->base().reserve( n ); 
        }


        void reverse()
        {
            this->base().reverse(); 
        }

        template< class InputIterator >
        void assign( InputIterator first, InputIterator last ) // strong
        { 
            base_type temp( first, last );
            this->swap( temp );
        }


        template< class Range >
        void assign( const Range& r ) // strong
        {
            assign( boost::begin(r), boost::end(r ) );
        }

        template< class I >
        void insert_impl( iterator before, I first, I last, std::input_iterator_tag ) // strong
        {
            ptr_sequence_adapter temp(first,last);  // strong
            transfer( before, temp );               // strong, commit
        }

        
        template< class InputIterator >
        void insert( iterator before, InputIterator first, InputIterator last ) // strong
        {
            insert_impl( before, first, last, BOOST_DEDUCED_TYPENAME
                         iterator_category<InputIterator>::type() );
        }

        
            void_ptr_delete_if() : fun(Fun())
            { }

        
            void_ptr_delete_if( Fun f ) : fun(f)
            { }

        
            bool operator()( void* r ) const
            {
               BOOST_ASSERT( r != 0 );
               Arg1 arg1 = static_cast<Arg1>(r);
               if( fun( *arg1 ) )
               { 
                   clone_allocator_type::deallocate_clone( arg1 );
                   return true;
               }
               return false;
            }

        void compact_and_erase_nulls( iterator first, iterator last ) // nothrow
        {
            typename base_type::ptr_iterator p = std::stable_partition( 
                                                    first.base(), 
                                                    last.base(), 
                                                    is_not_zero_ptr() );
            this->base().erase( p, this->end().base() );
            
        }


        void range_check_impl( iterator first, iterator last, 
                               std::bidirectional_iterator_tag )
        { /* do nothing */ }

        
        void range_check( iterator first, iterator last )
        {
            range_check_impl( first, last, 
                              BOOST_DEDUCED_TYPENAME iterator_category<iterator>::type() );
        }

        
        template< class Compare >
        void unique( iterator first, iterator last, Compare comp )
        {
            range_check(first,last);
            
            iterator prev = first;
            iterator next = first;
            ++next;
            for( ; next != last; ++next )
            {
                BOOST_ASSERT( !::boost::is_null(prev) );
                BOOST_ASSERT( !::boost::is_null(next) );
                if( comp( *prev, *next ) )
                {
                    this->remove( next ); // delete object
                    *next.base() = 0;     // mark pointer as deleted
                }
                else
                {
                    prev = next;
                }
                // ++next
            }

            compact_and_erase_nulls( first, last );
        }

        
        template< class Compare >
        void unique( Compare comp )
        {
            unique( this->begin(), this->end(), comp );
        }


        template< class Pred >
        void erase_if( iterator first, iterator last, Pred pred )
        {
            range_check(first,last);
            this->base().erase( std::remove_if( first.base(), last.base(), 
                                                void_ptr_delete_if<Pred,value_type>(pred) ),
                                last.base() );  
        }

        
        template< class Pred >
        void erase_if( Pred pred )
        {
            erase_if( this->begin(), this->end(), pred );
        }



        void merge( iterator first, iterator last, 
                    ptr_sequence_adapter& from )
        {
             merge( first, last, from, std::less<T>() );
        }

        
        void merge( ptr_sequence_adapter& r )
        {
            merge( r, std::less<T>() );
            BOOST_ASSERT( r.empty() );
        }

        
        template< class BinPred >
        void merge( ptr_sequence_adapter& r, BinPred pred )
        {
            merge( r.begin(), r.end(), r, pred );
            BOOST_ASSERT( r.empty() );    
        }


template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, unsigned int version)
{
    typedef ptr_circular_buffer<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}


template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_circular_buffer<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

        explicit ptr_back_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }


        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            container->push_back( obj );
            return *this;
        }


        ptr_back_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_back( container_type::clone_allocator_type::
                                  allocate_clone(r) );
            return *this;
        }


        ptr_back_insert_iterator& operator*()
        { 
            return *this;
        }


        ptr_back_insert_iterator& operator++()
        { 
            return *this;
        }


        ptr_back_insert_iterator operator++(int)
        { 
            return *this;
        }

        explicit ptr_front_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }


        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            container->push_front( obj );
            return *this;
        }

        
        ptr_front_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_front( container_type::clone_allocator_type::
                                   allocate_clone(r) );
            return *this;
        }


        ptr_front_insert_iterator& operator*()
        { 
            return *this;
        }


        ptr_front_insert_iterator& operator++()
        { 
            return *this;
        }


        ptr_front_insert_iterator operator++(int)
        { 
            return *this;
        }

        ptr_insert_iterator( PtrContainer& cont,
                               typename PtrContainer::iterator before )
        : container(&cont), iter(before)
        { }


        ptr_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            iter = container->insert( iter, obj );
            return *this;
        }

        
        ptr_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            iter = container->insert( iter, container_type::clone_allocator_type::
                                            allocate_clone(r) );
            return *this;
        }


        ptr_insert_iterator& operator*()
        { 
            return *this;
        }


        ptr_insert_iterator& operator++()
        { 
            return *this;
        }


        ptr_insert_iterator operator++(int)
        { 
            return *this;
        }


    template< class PtrContainer >
    inline ptr_back_insert_iterator<PtrContainer> 
    ptr_back_inserter( PtrContainer& cont )
    {
        return ptr_back_insert_iterator<PtrContainer>( cont );
    }


    template< class PtrContainer >
    inline ptr_front_insert_iterator<PtrContainer> 
    ptr_front_inserter( PtrContainer& cont )
    {
        return ptr_front_insert_iterator<PtrContainer>( cont );
    }


    template< class PtrContainer >
    inline ptr_insert_iterator<PtrContainer> 
    ptr_inserter( PtrContainer& cont, 
                    typename PtrContainer::iterator before )
    {
        return ptr_insert_iterator<PtrContainer>( cont, before );
    }


template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_list<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}


template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_set<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}


template<class Archive, class Key, class T, class Compare, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_map<Key, T, Compare, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

        bad_ptr_container_operation( const char* what ) : what_( what )
        { }

        
        virtual const char* what() const throw()
        {
            return what_;
        }

        bad_index( const char* what ) : bad_ptr_container_operation( what )
        { }

        bad_pointer() : bad_ptr_container_operation( "Null pointer not allowed in a pointer container!" )
        { }

        
        bad_pointer( const char* text ) : bad_ptr_container_operation( text )
        { }


template<class Archive, class T, std::size_t N, class CloneAllocator>
void save(Archive& ar, const ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    ptr_container_detail::save_helper(ar, c);
}


template<class Archive, class T, std::size_t N, class CloneAllocator>
void load(Archive& ar, ptr_array<T, N, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_array<T, N, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    for(size_type i = 0u; i != N; ++i)
    {
        T* p;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), p );
        c.replace(i, p);
    }
}


template<class Archive, class T, std::size_t N, class CloneAllocator>
void serialize(Archive& ar, ptr_array<T, N, CloneAllocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}


template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_deque<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}


            ptr_array_impl( Allocator /*a*/ = Allocator() )
            {
                this->assign( 0 );
            }

        ptr_array() : base_class()
        { }


        ptr_array( const ptr_array& r )
        {
            size_t i = 0;
            for( ; i != N; ++i )
                this->base()[i] = this->null_policy_allocate_clone( 
                                        static_cast<const T*>( &r[i] ) ); 
        }


        ptr_array& operator=( ptr_array r )
        {
            this->swap( r );
            return *this;            
        }


        template< size_t idx >
        auto_type replace( U* r ) // strong
        {
            BOOST_STATIC_ASSERT( idx < N );

            this->enforce_null_policy( r, "Null pointer in 'ptr_array::replace()'" );

            auto_type res( static_cast<U*>( this->base()[idx] ) ); // nothrow
            this->base()[idx] = r;                                 // nothrow
            return boost::ptr_container::move(res);                // nothrow 
        }


        template< size_t idx >
        T& at()
        {
            BOOST_STATIC_ASSERT( idx < N );
            return (*this)[idx];
        }


        template< size_t idx >
        const T& at() const
        {
            BOOST_STATIC_ASSERT( idx < N );
            return (*this)[idx];
        }


        bool is_null( size_t idx ) const
        {
            return base_class::is_null(idx);
        }


        template< size_t idx >
        bool is_null() const
        {
            BOOST_STATIC_ASSERT( idx < N );
            return this->base()[idx] == 0;
        }


    template< typename T, size_t size, typename CA >
    inline ptr_array<T,size,CA>* new_clone( const ptr_array<T,size,CA>& r )
    {
        return r.clone().release();
    }


    template< typename T, size_t size, typename CA >
    inline void swap( ptr_array<T,size,CA>& l, ptr_array<T,size,CA>& r )
    {
        l.swap(r);
    }


            template< class F2, class S2 >
            ref_pair( const std::pair<F2,S2>& p )
            : first(p.first), second(static_cast<S>(p.second))
            { }


            template< class RP >
            ref_pair( const RP* rp )
            : first(rp->first), second(rp->second)
            { }

            
            const ref_pair* const operator->() const
            {
                return this;
            }

        ptr_map_iterator() : base_type()                                 
        { }

        
        explicit ptr_map_iterator( const I& i ) : base_type(i)
        { }


        template< class I2, class F2, class S2 >
            ptr_map_iterator( const ptr_map_iterator<I2,F2,S2>& r ) 
         : base_type(r.base())
        { }

            scoped_deleter( T** a, size_type size ) 
                : ptrs_( a ), stored_( size ), released_( false )
            { 
                BOOST_ASSERT( a );
            }

            
            scoped_deleter( size_type size ) 
                : ptrs_( new T*[size] ), stored_( 0 ), 
                 released_( false )
            {
                BOOST_ASSERT( size > 0 );
            }



            
            scoped_deleter( size_type n, const T& x ) // strong
                : ptrs_( new T*[n] ), stored_(0),
                  released_( false )
            {
                for( size_type i = 0; i != n; i++ )
                    add( CloneAllocator::allocate_clone( &x ) );
                BOOST_ASSERT( stored_ > 0 );
            }



            
            template< class InputIterator >
            scoped_deleter ( InputIterator first, InputIterator last  ) // strong
                : ptrs_( new T*[ std::distance(first,last) ] ),
                  stored_(0),
                  released_( false )
            {
                for( ; first != last; ++first )
                    add( CloneAllocator::allocate_clone_from_iterator( first ) );
                BOOST_ASSERT( stored_ > 0 );
            }


            
            
            ~scoped_deleter()
            {
                if ( !released_ )
                {
                    for( size_type i = 0u; i != stored_; ++i )
                        CloneAllocator::deallocate_clone( ptrs_[i] ); 
                }
            }

            
            
            
            void add( T* t )
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                ptrs_[stored_] = t;
                ++stored_;
            }

            
            
            
            void release()
            {
                released_ = true;
            }

            
            
            
            T** begin()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[0];
            }

            
            
            
            T** end()
            {
                BOOST_ASSERT( ptrs_.get() != 0 );
                return &ptrs_[stored_];
            }


template<class Archive, class Config, class CloneAllocator>
void save_helper(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::const_iterator const_iterator;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    const_iterator i = c.begin(), e = c.end();
    for(; i != e; ++i)
        ar << boost::serialization::make_nvp( ptr_container_detail::item(), 
                ptr_container_detail::serialize_as_const(static_cast<value_type>(*i.base()))); 
    }


template<class Archive, class Config, class CloneAllocator>
void load_helper(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c,
                 BOOST_DEDUCED_TYPENAME ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>::size_type n)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::value_type value_type;

    //
    // Called after an appropriate reserve on c.
    //

    c.clear();            
    for(size_type i = 0u; i != n; ++i)
    {
        //
        // Remark: pointers are not tracked,
        // so we need not call ar.reset_object_address(v, u)
        //
        value_type ptr;
        ar >> boost::serialization::make_nvp( ptr_container_detail::item(), ptr ); 
        c.insert(c.end(), ptr);
    }
}


template<class Archive, class Config, class CloneAllocator>
void save(Archive& ar, const ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{   
    ar << boost::serialization::make_nvp( ptr_container_detail::count(), 
                                          ptr_container_detail::serialize_as_const(c.size()) );
    ptr_container_detail::save_helper(ar, c);
}


template<class Archive, class Config, class CloneAllocator>
void load(Archive& ar, ptr_container_detail::reversible_ptr_container<Config, CloneAllocator>& c, unsigned int /*version*/)
{
    typedef ptr_container_detail::reversible_ptr_container<Config, CloneAllocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    ptr_container_detail::load_helper(ar, c, n);
    
}

    move_source(Ptr& ptr) : ptr_(ptr) {}

    Ptr& ptr() const { return ptr_; }



template<typename T>
move_ptrs::move_source<T> move(T& x) 
{ return move_ptrs::move_source<T>(x); }


template<class Archive, class T, class VoidPtrMap, class CloneAllocator, bool Ordered>
void save(Archive& ar, const ptr_container_detail::ptr_map_adapter_base<T, VoidPtrMap, CloneAllocator,Ordered>& c, unsigned int /*version*/)
{
    typedef ptr_container_detail::ptr_map_adapter_base<T, VoidPtrMap, CloneAllocator,Ordered> container;
    typedef BOOST_DEDUCED_TYPENAME container::const_iterator const_iterator;

    ar << boost::serialization::make_nvp( ptr_container_detail::count(), 
                                          ptr_container_detail::serialize_as_const(c.size()) );

    const_iterator i = c.begin(), e = c.end();
    for(; i != e; ++i)
    {
        ar << boost::serialization::make_nvp( ptr_container_detail::first(), i->first );
        ar << boost::serialization::make_nvp( ptr_container_detail::second(),
                                              ptr_container_detail::serialize_as_const(i->second) );
    }
}


template<class Archive, class T, class VoidPtrMap, class CloneAllocator, bool Ordered>
void load(Archive& ar, ptr_map_adapter<T, VoidPtrMap, CloneAllocator,Ordered>& c, unsigned int /*version*/)
{
    typedef ptr_map_adapter<T, VoidPtrMap, CloneAllocator,Ordered> container;
    typedef BOOST_DEDUCED_TYPENAME container::key_type key_type;
    typedef BOOST_DEDUCED_TYPENAME container::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME container::iterator iterator;

    c.clear();
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );

    for(size_type i = 0u; i != n; ++i)
    {
        key_type key;
        T* value;
        ar >> boost::serialization::make_nvp( ptr_container_detail::first(), key );
        ar >> boost::serialization::make_nvp( ptr_container_detail::second(), value );
        std::pair<iterator, bool> p = c.insert(key, value);
        ar.reset_object_address(&p.first->first, &key); 
    }
}

    deleter_base(deleter d) { delete_ = d; }

    void operator() (T* t) const { delete_(t); }

    scalar_deleter() : base(do_delete) { }

    static void do_delete(T* t) { checked_delete(t); }

    array_deleter() : base(do_delete) { }

    static void do_delete(element_type* t) { checked_array_delete(t); }

        template< class T >
        void operator()( const T* p ) const
        {
            CloneAllocator::deallocate_clone( p );
        }

            template< class Iter >
            static Ty_* allocate_clone_from_iterator( Iter i )
            { 
                return allocate_clone( Config::get_const_pointer( i ) );
            }

            
            static Ty_* allocate_clone( const Ty_* x )
            {
                if( allow_null_values )
                {
                    if( x == 0 )
                        return 0;
                }
                else
                {
                    BOOST_ASSERT( x != 0 && "Cannot insert clone of null!" );
                }

                Ty_* res = CloneAllocator::allocate_clone( *x );
                BOOST_ASSERT( typeid(*res) == typeid(*x) &&
                              "CloneAllocator::allocate_clone() does not clone the "
                              "object properly. Check that new_clone() is implemented"
                              " correctly" );
                return res;
            }

            
            static void deallocate_clone( const Ty_* x )
            {
                if( allow_null_values )
                {
                    if( x == 0 )
                        return;
                }

                CloneAllocator::deallocate_clone( x );
            }

        Cont&       base()               { return c_; }


        template< class InputIterator >  
        void copy( InputIterator first, InputIterator last ) 
        {
            std::copy( first, last, begin() );
        }

        
        void copy( const reversible_ptr_container& r )
        { 
            copy( r.begin(), r.end() );
        }

        
        void copy_clones_and_release( scoped_deleter& sd ) // nothrow
        {
            BOOST_ASSERT( size_type( std::distance( sd.begin(), sd.end() ) ) == c_.size() );
            std::copy( sd.begin(), sd.end(), c_.begin() );
            sd.release(); 
        }

        
        template< class ForwardIterator >
        void clone_assign( ForwardIterator first, 
                           ForwardIterator last ) // strong 
        {
            BOOST_ASSERT( first != last );
            scoped_deleter sd( first, last );      // strong
            copy_clones_and_release( sd );         // nothrow
        }


        template< class ForwardIterator >
        void clone_back_insert( ForwardIterator first,
                                ForwardIterator last )
        {
            BOOST_ASSERT( first != last );
            scoped_deleter sd( first, last );
            insert_clones_and_release( sd, end() );
        }

        
        void remove_all() 
        {
            remove( begin(), end() ); 
        }


        void insert_clones_and_release( scoped_deleter& sd, 
                                        iterator where ) // strong
        {
            //
            // 'c_.insert' always provides the strong guarantee for T* elements
            // since a copy constructor of a pointer cannot throw
            //
            c_.insert( where.base(), 
                       sd.begin(), sd.end() ); 
            sd.release();
        }


        template< class U >
        void remove( U* ptr )
        {
            null_policy_deallocate_clone( ptr );
        }

        
        template< class I >
        void remove( I i )
        { 
            null_policy_deallocate_clone( Config::get_const_pointer(i) );
        }


        template< class I >
        void remove( I first, I last ) 
        {
            for( ; first != last; ++first )
                remove( first );
        }


        static void enforce_null_policy( const Ty_* x, const char* msg )
        {
            if( !allow_null )
            {
                BOOST_PTR_CONTAINER_THROW_EXCEPTION( 0 == x && "null not allowed", 
                                                     bad_pointer, msg );
            }
        }


        static Ty_* null_policy_allocate_clone( const Ty_* x )
        {
            return null_cloner_type::allocate_clone( x );
        }


        static void null_policy_deallocate_clone( const Ty_* x )
        {
            null_cloner_type::deallocate_clone( x );
        }

        template< class ForwardIterator >
        ForwardIterator advance( ForwardIterator begin, size_type n ) 
        {
            ForwardIterator iter = begin;
            std::advance( iter, n );
            return iter;
        }
        

        template< class I >
        void constructor_impl( I first, I last, std::input_iterator_tag ) // basic
        {
            while( first != last )
            {
                insert( end(), null_cloner_type::allocate_clone_from_iterator(first) );
                ++first;
            }
        }


        template< class I >
        void associative_constructor_impl( I first, I last ) // strong
        {
            if( first == last )
                return;

            scoped_deleter sd( first, last );
            insert_clones_and_release( sd );             
        }

        reversible_ptr_container()
        { }


        template< class SizeType >
        reversible_ptr_container( SizeType n, unordered_associative_container_tag )
          : c_( n )
        { }


        template< class SizeType >
        reversible_ptr_container( SizeType n, fixed_length_sequence_tag )
          : c_( n )
        { }


        reversible_ptr_container( const reversible_ptr_container& r ) 
        {
            constructor_impl( r.begin(), r.end(), std::forward_iterator_tag() ); 
        }


        template< class C, class V >
        reversible_ptr_container( const reversible_ptr_container<C,V>& r ) 
        {
            constructor_impl( r.begin(), r.end(), std::forward_iterator_tag() ); 
        }


        template< class PtrContainer >
        reversible_ptr_container& operator=( std::auto_ptr<PtrContainer> clone ) // nothrow
        {
            swap( *clone );
            return *this;
        }


        reversible_ptr_container& operator=( reversible_ptr_container r ) // strong 
        {
            swap( r );
            return *this;
        }


        template< class ForwardIterator >
        reversible_ptr_container( ForwardIterator first,
                                  ForwardIterator last,
                                  fixed_length_sequence_tag )
          : c_( std::distance(first,last) )
        {
            constructor_impl( first, last, 
                              std::forward_iterator_tag() );
        }


        template< class SizeType, class InputIterator >
        reversible_ptr_container( SizeType n,
                                  InputIterator first,
                                  InputIterator last,
                                  fixed_length_sequence_tag )
          : c_( n )
        {
            constructor_impl( first, last, 
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#else
                              BOOST_DEDUCED_TYPENAME
#endif                              
                              iterator_category<InputIterator>::type() );
        }

                
        template< class InputIterator >
        reversible_ptr_container( InputIterator first,
                                  InputIterator last,
                                  associative_container_tag )
        {
            associative_constructor_impl( first, last );
        }
        
        ~reversible_ptr_container()
        { 
            remove_all();
        }

        
        allocator_type get_allocator() const                   
        {
            return c_.get_allocator(); 
        }

        iterator begin()            
            { return iterator( c_.begin() ); }

        iterator end()              
            { return iterator( c_.end() ); }

        
        reverse_iterator rbegin()           
            { return reverse_iterator( this->end() ); }
 
        reverse_iterator rend()             
            { return reverse_iterator( this->begin() ); }
 

        const_iterator cbegin() const      
            { return const_iterator( c_.begin() ); }

        const_iterator cend() const             
            { return const_iterator( c_.end() ); }


        const_reverse_iterator crbegin() const      
            { return const_reverse_iterator( this->end() ); }

        const_reverse_iterator crend() const             
            { return const_reverse_iterator( this->begin() ); }


        void swap( reversible_ptr_container& r ) // nothrow
        { 
            c_.swap( r.c_ );
        }

          
        size_type size() const // nothrow
        {
            return c_.size();
        }


        size_type max_size() const // nothrow
        {
            return c_.max_size(); 
        }

        
        bool empty() const // nothrow
        {
            return c_.empty();
        }


        bool operator==( const reversible_ptr_container& r ) const // nothrow
        { 
            if( size() != r.size() )
                return false;
            else
                return std::equal( begin(), end(), r.begin() );
        }


        bool operator!=( const reversible_ptr_container& r ) const // nothrow
        {
            return !(*this == r);
        }

        
        bool operator<( const reversible_ptr_container& r ) const // nothrow 
        {
             return std::lexicographical_compare( begin(), end(), r.begin(), r.end() );
        }


        bool operator<=( const reversible_ptr_container& r ) const // nothrow 
        {
            return !(r < *this);
        }


        bool operator>( const reversible_ptr_container& r ) const // nothrow 
        {
            return r < *this;
        }


        bool operator>=( const reversible_ptr_container& r ) const // nothrow 
        {
            return !(*this < r);
        }


        iterator insert( iterator before, Ty_* x )
        {
            enforce_null_policy( x, "Null pointer in 'insert()'" );

            auto_type ptr( x );                            // nothrow
            iterator res( c_.insert( before.base(), x ) ); // strong, commit
            ptr.release();                                 // nothrow
            return res;
        }


        iterator erase( iterator x ) // nothrow
        {
            BOOST_ASSERT( !empty() );
            BOOST_ASSERT( x != end() );

            remove( x );
            return iterator( c_.erase( x.base() ) );
        }


        void clear()
        {
            remove_all();
            c_.clear();
        }

        
        auto_type release( iterator where )
        { 
            BOOST_ASSERT( where != end() );
            
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( empty(), bad_ptr_container_operation,
                                                 "'release()' on empty container" ); 
            
            auto_type ptr( Config::get_pointer( where ) );  // nothrow
            c_.erase( where.base() );                       // nothrow
            return boost::ptr_container_detail::move( ptr ); 
        }


        auto_type replace( iterator where, Ty_* x ) // strong  
        { 
            BOOST_ASSERT( where != end() );

            enforce_null_policy( x, "Null pointer in 'replace()'" );
            
            auto_type ptr( x );
            
            BOOST_PTR_CONTAINER_THROW_EXCEPTION( empty(), bad_ptr_container_operation,
                                                 "'replace()' on empty container" );

            auto_type old( Config::get_pointer( where ) );  // nothrow            
            const_cast<void*&>(*where.base()) = ptr.release();                
            return boost::ptr_container_detail::move( old );
        }

            void_ptr_iterator() : iter_()
            { }


            void_ptr_iterator( VoidIter r ) : iter_(r)
            { }

            template< class MutableIterator, class MutableT >
            void_ptr_iterator( const void_ptr_iterator<MutableIterator,MutableT>& r )
#ifdef BOOST_NO_SFINAE
                         : iter_( VoidIter(const_cast<void**>(&*r.base())) )
#else

             : iter_(r.base())
#endif
            { }


            T& operator*() const
            {
                return *static_cast<T*>( *iter_ );
            }


            T* operator->() const
            {
                return static_cast<T*>( *iter_ );
            }

            
            void_ptr_iterator& operator++()
            {
                ++iter_;
                return *this;
            }


            void_ptr_iterator operator++(int)
            {
                void_ptr_iterator res = *this;
                ++iter_;
                return res;
            }


            void_ptr_iterator& operator--()
            {
                --iter_;
                return *this;
            }


            void_ptr_iterator operator--(int)
            {
                void_ptr_iterator res = *this;
                --iter_;
                return res;
            }


            void_ptr_iterator& operator+=( difference_type n )
            {
                iter_ += n;
                return *this;
            }


            void_ptr_iterator& operator-=( difference_type n )
            {
                iter_ -= n;
                return *this;
            }


            T& operator[]( difference_type n ) const
            {
                return *static_cast<T*>( *(iter_ + n) );
            }


            VoidIter base() const
            {
                return iter_;
            }


        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator+( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l += n;
            return l;
        }


        template< class VoidIter, class T >
        inline void_ptr_iterator<VoidIter,T> 
        operator-( void_ptr_iterator<VoidIter,T> l, 
                   BOOST_DEDUCED_TYPENAME void_ptr_iterator<VoidIter,T>::difference_type n )
        {
            l -= n;
            return l;
        }




        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator==( const void_ptr_iterator<VoidIterT,T>& l,
                                const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() == r.base();
        }



        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator!=( const void_ptr_iterator<VoidIterT,T>& l,
                                const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() != r.base();
        }




        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator<( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() < r.base();
        }



        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator<=( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() <= r.base();
        }



        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator>( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() > r.base();
        }



        
        template< class VoidIterT, class T, class VoidIterU, class U >
        inline bool operator>=( const void_ptr_iterator<VoidIterT,T>& l,
                               const void_ptr_iterator<VoidIterU,U>& r )
        {
            return l.base() >= r.base();
        }

        inline const char* count()  { return "count"; }

        inline const char* item()   { return "item"; }

        inline const char* first()  { return "first"; }

        inline const char* second() { return "second"; }


        template<class T>
        inline T const& serialize_as_const(T const& r)
        {
            return r;
        }

        associative_ptr_container()
        { }


        template< class Compare, class Allocator >
        associative_ptr_container( const Compare& comp,
                                   const Allocator& a )
         : base_type( comp, a, container_type() )
        { }

        
        template< class Hash, class Pred, class Allocator >
        associative_ptr_container( const Hash& hash,
                                   const Pred& pred,
                                   const Allocator& a )
         : base_type( hash, pred, a )
        { }


        template< class InputIterator, class Compare, class Allocator >
        associative_ptr_container( InputIterator first, InputIterator last,
                                   const Compare& comp,
                                   const Allocator& a )
         : base_type( first, last, comp, a, container_type() )
        { }

        
        template< class InputIterator, class Hash, class Pred, class Allocator >
        associative_ptr_container( InputIterator first, InputIterator last,
                                   const Hash& hash,
                                   const Pred& pred,
                                   const Allocator& a )
         : base_type( first, last, hash, pred, a )
        { }


        associative_ptr_container( const associative_ptr_container& r )
         : base_type( r.begin(), r.end(), container_type() )
        { }

        
        template< class C, class V >
        associative_ptr_container( const associative_ptr_container<C,V>& r )
         : base_type( r.begin(), r.end(), container_type() )
        { }

        
        template< class PtrContainer >
        associative_ptr_container& operator=( std::auto_ptr<PtrContainer> r ) // nothrow
        {
           base_type::operator=( r );
           return *this;
        }

        
        associative_ptr_container& operator=( associative_ptr_container r ) // strong
        {
           this->swap( r );
           return *this;   
        }

        key_compare key_comp() const
        {
            return this->base().key_comp();
        }


        value_compare value_comp() const
        {
            return this->base().value_comp();
        }


        iterator erase( iterator before ) // nothrow
        {
            BOOST_ASSERT( !this->empty() );
            BOOST_ASSERT( before != this->end() );

            this->remove( before );                      // nothrow
            iterator res( before );                      // nothrow
            ++res;                                       // nothrow
            this->base().erase( before.base() );         // nothrow
            return res;                                  // nothrow
        }

        local_iterator begin( size_type n )
        {
            return local_iterator( this->base().begin( n ) );
        }

        
        local_iterator end( size_type n )
        {
            return local_iterator( this->base().end( n ) );
        }

        
        const_local_iterator cbegin( size_type n ) const
        {
            return const_local_iterator( this->base().cbegin( n ) );
        }

        
        const_local_iterator cend( size_type n )
        {
            return const_local_iterator( this->base().cend( n ) );
        }
