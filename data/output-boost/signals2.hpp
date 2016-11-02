
        template<typename WeakPtr>
        result_type operator()(const WeakPtr &wp) const
        {
          return wp.lock();
        }

        template<typename WeakPtr>
        bool operator()(const WeakPtr &wp) const
        {
          return wp.expired();
        }


      const tracked_container_type& tracked_objects() const {return _tracked_objects;}

      locked_container_type lock() const
      {
        locked_container_type locked_objects;
        tracked_container_type::const_iterator it;
        for(it = tracked_objects().begin(); it != tracked_objects().end(); ++it)
        {
          locked_objects.push_back(apply_visitor(detail::lock_weak_ptr_visitor(), *it));
          if(apply_visitor(detail::expired_weak_ptr_visitor(), *it))
          {
            boost::throw_exception(expired_slot());
          }
        }
        return locked_objects;
      }

      bool expired() const
      {
        tracked_container_type::const_iterator it;
        for(it = tracked_objects().begin(); it != tracked_objects().end(); ++it)
        {
          if(apply_visitor(detail::expired_weak_ptr_visitor(), *it)) return true;
        }
        return false;
      }


      void track_signal(const signal_base &signal)
      {
        _tracked_objects.push_back(signal.lock_pimpl());
      }

      shared_connection_block(const signals2::connection &conn = signals2::connection(),
        bool initially_blocked = true):
        _weak_connection_body(conn._weak_connection_body)
      {
        if(initially_blocked) block();
      }

      void block()
      {
        if(blocking()) return;
        boost::shared_ptr<detail::connection_body_base> connection_body(_weak_connection_body.lock());
        if(connection_body == 0)
        {
          // Make _blocker non-empty so the blocking() method still returns the correct value
          // after the connection has expired.
          _blocker.reset(static_cast<int*>(0));
          return;
        }
        _blocker = connection_body->get_blocker();
      }

      void unblock()
      {
        _blocker.reset();
      }

      bool blocking() const
      {
        shared_ptr<void> empty;
        return _blocker < empty || empty < _blocker;
      }

      signals2::connection connection() const
      {
        return signals2::connection(_weak_connection_body);
      }

  inline void adl_predestruct(...) {}

    postconstructor_invoker(const shared_ptr<T> & sp):
        _sp(sp), _postconstructed(false)
    {}


    void destroy()
    {
        if( initialized_ )
        {
            T* p = reinterpret_cast< T* >( storage_.data_ );
            using boost::signals2::detail::adl_predestruct;
            adl_predestruct(const_cast<typename boost::remove_const<T>::type *>(p));
            p->~T();
            initialized_ = false;
        }
    }


    deconstruct_deleter(): initialized_( false )
    {
    }

    deconstruct_deleter(const deconstruct_deleter &): initialized_( false )
    {
    }


    ~deconstruct_deleter()
    {
        destroy();
    }


    void operator()( T * )
    {
        destroy();
    }


    void * address()
    {
        return storage_.data_;
    }


    void set_initialized()
    {
        initialized_ = true;
    }


    template< class T >
    static postconstructor_invoker<T> deconstruct()
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T();
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;

    }


    template< class T, class... Args >
    static postconstructor_invoker<T> deconstruct( Args && ... args )
    {
        boost::shared_ptr< T > pt( static_cast< T* >( 0 ), detail::deconstruct_deleter< T >() );

        detail::deconstruct_deleter< T > * pd = boost::get_deleter< detail::deconstruct_deleter< T > >( pt );

        void * pv = pd->address();

        new( pv ) T( std::forward<Args>( args )... );
        pd->set_initialized();

        boost::shared_ptr< T > retval( pt, static_cast< T* >( pv ) );
        boost::detail::sp_enable_shared_from_this(&retval, retval.get(), retval.get());
        return retval;
    }


template< class T > postconstructor_invoker<T> deconstruct()
{
    return deconstruct_access::deconstruct<T>();
}


template< class T, class... Args > postconstructor_invoker< T > deconstruct( Args && ... args )
{
    return deconstruct_access::deconstruct<T>( std::forward<Args>( args )... );
}

      template<typename InputIterator>
        result_type operator()(InputIterator first, InputIterator last) const
      {
        while (first != last)
        {
          try
          {
            *first;
          }
          catch(const expired_slot &) {}
          ++first;
        }
        return;
      }

      virtual char const * what() const throw()
      {
        return "boost::signals2::expired_slot";
      }

    extern inline void null_deleter(const void*) {}

        connection_body_base():
          _connected(true)
        {
        }

        virtual ~connection_body_base() {}

        void disconnect()
        {
          unique_lock<connection_body_base> local_lock(*this);
          nolock_disconnect();
        }

        void nolock_disconnect()
        {
          _connected = false;
        }

        connection_body(const SlotType &slot_in):
          slot(slot_in)
        {
        }

        virtual ~connection_body() {}

        virtual bool connected() const
        {
          unique_lock<mutex_type> local_lock(_mutex);
          nolock_grab_tracked_objects(detail::null_output_iterator());
          return nolock_nograb_connected();
        }

        const GroupKey& group_key() const {return _group_key;}

        void set_group_key(const GroupKey &key) {_group_key = key;}

        bool nolock_slot_expired() const
        {
          bool expired = slot.expired();
          if(expired == true)
          {
            _connected = false;
          }
          return expired;
        }

        template<typename OutputIterator>
          void nolock_grab_tracked_objects(OutputIterator inserter) const
        {
          slot_base::tracked_container_type::const_iterator it;
          for(it = slot.tracked_objects().begin();
            it != slot.tracked_objects().end();
            ++it)
          {
            void_shared_ptr_variant locked_object
            (
              apply_visitor
              (
                detail::lock_weak_ptr_visitor(),
                *it
              )
            );
            if(apply_visitor(detail::expired_weak_ptr_visitor(), *it))
            {
              _connected = false;
              return;
            }
            *inserter++ = locked_object;
          }
        }

        virtual void lock()
        {
          _mutex.lock();
        }

        virtual void unlock()
        {
          _mutex.unlock();
        }


      connection() {}

      connection(const connection &other): _weak_connection_body(other._weak_connection_body)
      {}

      ~connection() {}

      void disconnect() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return;
        connectionBody->disconnect();
      }

      bool connected() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return false;
        return connectionBody->connected();
      }

      bool blocked() const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        if(connectionBody == 0) return true;
        return connectionBody->blocked();
      }

      bool operator==(const connection& other) const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        boost::shared_ptr<detail::connection_body_base> otherConnectionBody(other._weak_connection_body.lock());
        return connectionBody == otherConnectionBody;
      }

      bool operator!=(const connection& other) const
      {
        return !(*this == other);
      }

      bool operator<(const connection& other) const
      {
        boost::shared_ptr<detail::connection_body_base> connectionBody(_weak_connection_body.lock());
        boost::shared_ptr<detail::connection_body_base> otherConnectionBody(other._weak_connection_body.lock());
        return connectionBody < otherConnectionBody;
      }

      void swap(connection &other)
      {
        using std::swap;
        swap(_weak_connection_body, other._weak_connection_body);
      }

    inline void swap(connection &conn1, connection &conn2)
    {
      conn1.swap(conn2);
    }

      scoped_connection() {}

      scoped_connection(const connection &other):
        connection(other)
      {}

      ~scoped_connection()
      {
        disconnect();
      }

      scoped_connection& operator=(const connection &rhs)
      {
        disconnect();
        connection::operator=(rhs);
        return *this;
      }

      connection release()
      {
        connection conn(_weak_connection_body);
        _weak_connection_body.reset();
        return conn;
      }

    inline void swap(scoped_connection &conn1, scoped_connection &conn2)
    {
      conn1.swap(conn2);
    }

        postconstructible() {}

        virtual ~postconstructible() {}


      virtual ~signal_base() {}

      trackable(): _tracked_ptr(static_cast<int*>(0)) {}

      trackable(const trackable &): _tracked_ptr(static_cast<int*>(0)) {}

      trackable& operator=(const trackable &)
      {
          return *this;
      }

      ~trackable() {}

        predestructible() {}

        virtual ~predestructible() {}

      extern inline void do_postconstruct(const postconstructible *ptr)
      {
        postconstructible *nonconst_ptr = const_cast<postconstructible*>(ptr);
        nonconst_ptr->postconstruct();
      }

      extern inline void do_postconstruct(...)
      {
      }

      extern inline void do_predestruct(...)
      {
      }

      void operator()(const T *ptr) const
      {
        detail::do_predestruct(ptr);
        checked_delete(ptr);
      }

      virtual const char* what() const throw() {return "boost::signals2::no_slots_error";}


      template<typename InputIterator>
      T operator()(InputIterator first, InputIterator last) const
      {
        if(first == last)
        {
          boost::throw_exception(no_slots_error());
        }
        optional<T> value;
        while (first != last)
        {
          try
          {
            value = *first;
          }
          catch(const expired_slot &) {}
          ++first;
        }
        if(value) return value.get();
        boost::throw_exception(no_slots_error());
      }

      template<typename InputIterator>
        result_type operator()(InputIterator first, InputIterator last) const
      {
        while (first != last)
        {
          try
          {
            *first;
          }
          catch(const expired_slot &) {}
          ++first;
        }
        return;
      }

      void lock() {}

      bool try_lock() {return true;}

      void unlock() {}


    mutex()
    {
        InitializeCriticalSection(&cs_);
    }


    ~mutex()
    {
        DeleteCriticalSection(&cs_);
    }


    void lock()
    {
        EnterCriticalSection(&cs_);
    }

    bool try_lock()
    {
        BOOST_ASSERT(false);
        return false;
    }

    void unlock()
    {
        LeaveCriticalSection(&cs_);
    }


        template<typename Func, typename ... Args, std::size_t N>
        R operator()(Func &func, BOOST_SIGNALS2_TUPLE<Args...> args, mpl::size_t<N>) const
        {
          typedef typename make_unsigned_meta_array<N>::type indices_type;
          typename Func::result_type *resolver = 0;
          return m_invoke(resolver, func, indices_type(), args);
        }

        template<typename T, typename Func, unsigned ... indices, typename ... Args>
          R m_invoke(T *, Func &func, unsigned_meta_array<indices...>, BOOST_SIGNALS2_TUPLE<Args...> args) const
        {
          return func(BOOST_SIGNALS2_GET<indices>(args)...);
        }


        variadic_slot_invoker(Args & ... args): _args(args...)
        {}

        template<typename ConnectionBodyType>
          result_type operator ()(const ConnectionBodyType &connectionBody) const
        {
          result_type *resolver = 0;
          return m_invoke(connectionBody,
            resolver);
        }

        template<typename ConnectionBodyType>
        result_type m_invoke(const ConnectionBodyType &connectionBody,
          const void_type *) const
        {
          return call_with_tuple_args<result_type>()(connectionBody->slot.slot_function(), _args, mpl::size_t<sizeof...(Args)>());
          return void_type();
        }

        template<typename ConnectionBodyType>
          result_type m_invoke(const ConnectionBodyType &connectionBody, ...) const
        {
          return call_with_tuple_args<result_type>()(connectionBody->slot.slot_function(), _args, mpl::size_t<sizeof...(Args)>());
        }


    mutex()
    {

// HPUX 10.20 / DCE has a nonstandard pthread_mutex_init

#if defined(__hpux) && defined(_DECTHREADS_)
        pthread_mutex_init(&m_, pthread_mutexattr_default);
#else
        pthread_mutex_init(&m_, 0);
#endif
    }


    ~mutex()
    {
        pthread_mutex_destroy(&m_);
    }


    void lock()
    {
        pthread_mutex_lock(&m_);
    }


    bool try_lock()
    {
        return pthread_mutex_trylock(&m_) == 0;
    }


    void unlock()
    {
        pthread_mutex_unlock(&m_);
    }

      template<typename F>
      typename F::weak_signal_type
      get_invocable_slot(const F &signal, signal_tag)
      { return typename F::weak_signal_type(signal); }


      template<typename F>
      const F&
      get_invocable_slot(const F& f, reference_tag)
      { return f; }


      template<typename F>
      const F&
      get_invocable_slot(const F& f, value_tag)
      { return f; }

      template<typename F>
      typename get_slot_tag<F>::type
      tag_type(const F&)
      {
        typedef typename get_slot_tag<F>::type
          the_tag_type;
        the_tag_type tag = the_tag_type();
        return tag;
      }

        template< class SizeType >
        static SizeType new_capacity( SizeType capacity )
        {
            //
            // @remark: we grow the capacity quite agressively.
            //          this is justified since we aim to minimize
            //          heap-allocations, and because we mostly use
            //          the buffer locally.
            return capacity * 4u;
        }


        template< class SizeType >
        static bool should_shrink( SizeType size, SizeType capacity )
        {
            //
            // @remark: when defining a new grow policy, one might
            //          choose that if the waated space is less
            //          than a certain percentage, then it is of
            //          little use to shrink.
            //
            return true;
        }


        pointer allocate( size_type capacity_arg )
        {
            if( capacity_arg > N )
                return &*get_allocator().allocate( capacity_arg );
            else
                return static_cast<T*>( members_.address() );
        }


        void deallocate( pointer where, size_type capacity_arg )
        {
            if( capacity_arg <= N )
                return;
            get_allocator().deallocate( allocator_pointer(where), capacity_arg );
        }


        template< class I >
        static void copy_impl( I begin, I end, pointer where, std::random_access_iterator_tag )
        {
            copy_rai( begin, end, where, boost::has_trivial_assign<T>() );
        }


        static void copy_rai( const T* begin, const T* end,
                              pointer where, const boost::true_type& )
        {
            std::memcpy( where, begin, sizeof(T) * std::distance(begin,end) );
        }


        template< class I >
        static void copy_impl( I begin, I end, pointer where )
        {
            copy_impl( begin, end, where,
                       typename std::iterator_traits<I>::iterator_category() );
        }


        template< class I, class I2 >
        static void assign_impl( I begin, I end, I2 where )
        {
            assign_impl( begin, end, where, boost::has_trivial_assign<T>() );
        }


        void unchecked_push_back_n( size_type n, const boost::true_type& )
        {
            std::uninitialized_fill( end(), end() + n, T() );
            size_ += n;
        }


        void auto_buffer_destroy( pointer where, const boost::false_type& )
        {
            (*where).~T();
        }


        void auto_buffer_destroy( pointer where )
        {
            auto_buffer_destroy( where, boost::has_trivial_destructor<T>() );
        }


        void destroy_back_n( size_type n, const boost::false_type& )
        {
            BOOST_ASSERT( n > 0 );
            pointer buffer  = buffer_ + size_ - 1u;
            pointer new_end = buffer - n;
            for( ; buffer > new_end; --buffer )
                auto_buffer_destroy( buffer );
        }


        void destroy_back_n( size_type n )
        {
            destroy_back_n( n, boost::has_trivial_destructor<T>() );
        }


        pointer move_to_new_buffer( size_type new_capacity, const boost::false_type& )
        {
            pointer new_buffer = allocate( new_capacity ); // strong
            boost::multi_index::detail::scope_guard guard =
                boost::multi_index::detail::make_obj_guard( *this,
                                                            &auto_buffer::deallocate,
                                                            new_buffer,
                                                            new_capacity );
            copy_impl( begin(), end(), new_buffer ); // strong
            guard.dismiss();                         // nothrow
            return new_buffer;
        }


        void reserve_impl( size_type new_capacity )
        {
            pointer new_buffer = move_to_new_buffer( new_capacity,
                                                 boost::has_nothrow_copy<T>() );
            (*this).~auto_buffer();
            buffer_   = new_buffer;
            members_.capacity_ = new_capacity;
            BOOST_ASSERT( size_ <= members_.capacity_ );
        }


        size_type new_capacity_impl( size_type n )
        {
            BOOST_ASSERT( n > members_.capacity_ );
            size_type new_capacity = GrowPolicy::new_capacity( members_.capacity_ );
            // @todo: consider to check for allocator.max_size()
            return (std::max)(new_capacity,n);
        }


        static void swap_helper( auto_buffer& l, auto_buffer& r,
                                 const boost::true_type& )
        {
            BOOST_ASSERT( l.is_on_stack() && r.is_on_stack() );

            auto_buffer temp( l.begin(), l.end() );
            assign_impl( r.begin(), r.end(), l.begin() );
            assign_impl( temp.begin(), temp.end(), r.begin() );
            boost::swap( l.size_, r.size_ );
            boost::swap( l.members_.capacity_, r.members_.capacity_ );
        }


        void one_sided_swap( auto_buffer& temp ) // nothrow
        {
            BOOST_ASSERT( !temp.is_on_stack() );
            this->~auto_buffer();
            // @remark: must be nothrow
            get_allocator()    = temp.get_allocator();
            members_.capacity_ = temp.members_.capacity_;
            buffer_            = temp.buffer_;
            BOOST_ASSERT( temp.size_ >= size_ + 1u );
            size_              = temp.size_;
            temp.buffer_       = 0;
            BOOST_ASSERT( temp.is_valid() );
        }


        template< class I >
        void insert_impl( const_iterator before, I begin_arg, I end_arg,
                          std::input_iterator_tag )
        {
            for( ; begin_arg != end_arg; ++begin_arg )
            {
                before = insert( before, *begin_arg );
                ++before;
            }
        }


        void grow_back( size_type n, const boost::true_type& )
        {
            BOOST_ASSERT( size_ + n <= members_.capacity_ );
            size_ += n;
        }


        void grow_back( size_type n )
        {
            grow_back( n, boost::has_trivial_constructor<T>() );
        }


        void grow_back_one( const boost::true_type& )
        {
            BOOST_ASSERT( size_ + 1 <= members_.capacity_ );
            size_ += 1;
        }


        void grow_back_one()
        {
            grow_back_one( boost::has_trivial_constructor<T>() );
        }

        bool is_valid() const // invariant
        {
            // @remark: allowed for N==0 and when
            //          using a locally instance
            //          in insert()/one_sided_swap()
            if( buffer_ == 0 )
                return true;

            if( members_.capacity_ < N )
                return false;

            if( !is_on_stack() && members_.capacity_ <= N )
                return false;

            if( buffer_ == members_.address() )
                if( members_.capacity_ > N )
                    return false;

            if( size_ > members_.capacity_ )
                return false;

            return true;
        }


        auto_buffer()
            : members_( N ),
              buffer_( static_cast<T*>(members_.address()) ),
              size_( 0u )
        {
            BOOST_ASSERT( is_valid() );
        }


        auto_buffer( const auto_buffer& r )
            : members_( (std::max)(r.size_,size_type(N)) ),
              buffer_( allocate( members_.capacity_ ) ),
              size_( 0 )
        {
            copy_impl( r.begin(), r.end(), buffer_ );
            size_ = r.size_;
            BOOST_ASSERT( is_valid() );
        }


        auto_buffer& operator=( const auto_buffer& r ) // basic
        {
            if( this == &r )
                return *this;

            difference_type diff = size_ - r.size_;
            if( diff >= 0 )
            {
                pop_back_n( static_cast<size_type>(diff) );
                assign_impl( r.begin(), r.end(), begin() );
            }
            else
            {
                if( members_.capacity_ >= r.size() )
                {
                    unchecked_push_back_n( static_cast<size_type>(-diff) );
                    assign_impl( r.begin(), r.end(), begin() );
                }
                else
                {
                    // @remark: we release memory as early as possible
                    //          since we only give the basic guarantee
                    (*this).~auto_buffer();
                    buffer_ = 0;
                    pointer new_buffer = allocate( r.size() );
                    boost::multi_index::detail::scope_guard guard =
                        boost::multi_index::detail::make_obj_guard( *this,
                                                                    &auto_buffer::deallocate,
                                                                    new_buffer,
                                                                    r.size() );
                    copy_impl( r.begin(), r.end(), new_buffer );
                    guard.dismiss();
                    buffer_            = new_buffer;
                    members_.capacity_ = r.size();
                    size_              = members_.capacity_;
                }
            }

            BOOST_ASSERT( size() == r.size() );
            BOOST_ASSERT( is_valid() );
            return *this;
        }


        explicit auto_buffer( size_type capacity_arg )
            : members_( (std::max)(capacity_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            BOOST_ASSERT( is_valid() );
        }


        auto_buffer( size_type capacity_arg, const allocator_type& a )
            : allocator_type( a ),
              members_( (std::max)(capacity_arg, size_type(N)) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            BOOST_ASSERT( is_valid() );
        }


        template< class ForwardIterator >
        auto_buffer( ForwardIterator begin_arg, ForwardIterator end_arg )
            :
              members_( std::distance(begin_arg, end_arg) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            copy_impl( begin_arg, end_arg, buffer_ );
            size_ = members_.capacity_;
            if( members_.capacity_ < N )
                members_.capacity_ = N;
            BOOST_ASSERT( is_valid() );
        }


        template< class ForwardIterator >
        auto_buffer( ForwardIterator begin_arg, ForwardIterator end_arg,
                     const allocator_type& a )
            : allocator_type( a ),
              members_( std::distance(begin_arg, end_arg) ),
              buffer_( allocate(members_.capacity_) ),
              size_( 0 )
        {
            copy_impl( begin_arg, end_arg, buffer_ );
            size_ = members_.capacity_;
            if( members_.capacity_ < N )
                members_.capacity_ = N;
            BOOST_ASSERT( is_valid() );
        }


        ~auto_buffer()
        {
            BOOST_ASSERT( is_valid() );
            if( buffer_ ) // do we need this check? Yes, but only
                // for N = 0u + local instances in one_sided_swap()
                auto_buffer_destroy( boost::has_trivial_destructor<T>() );
        }

        bool empty() const
        {
            return size_ == 0;
        }


        bool full() const
        {
            return size_ == members_.capacity_;
        }


        bool is_on_stack() const
        {
            return members_.capacity_ <= N;
        }


        size_type size() const
        {
            return size_;
        }


        size_type capacity() const
        {
            return members_.capacity_;
        }

        pointer data()
        {
            return buffer_;
        }


        const_pointer data() const
        {
            return buffer_;
        }


        allocator_type& get_allocator()
        {
            return static_cast<allocator_type&>(*this);
        }


        const allocator_type& get_allocator() const
        {
            return static_cast<const allocator_type&>(*this);
        }

        iterator begin()
        {
            return buffer_;
        }


        const_iterator begin() const
        {
            return buffer_;
        }


        iterator end()
        {
            return buffer_ + size_;
        }


        const_iterator end() const
        {
            return buffer_ + size_;
        }


        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }


        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }


        const_iterator cbegin() const
        {
            return const_cast<const auto_buffer*>(this)->begin();
        }


        const_iterator cend() const
        {
            return const_cast<const auto_buffer*>(this)->end();
        }


        const_reverse_iterator crbegin() const
        {
            return const_cast<const auto_buffer*>(this)->rbegin();
        }


        const_reverse_iterator crend() const
        {
            return const_cast<const auto_buffer*>(this)->rend();
        }

        reference front()
        {
            return buffer_[0];
        }


        reference back()
        {
            return buffer_[size_-1];
        }


        reference operator[]( size_type n )
        {
            BOOST_ASSERT( n < size_ );
            return buffer_[n];
        }


        void unchecked_push_back()
        {
            BOOST_ASSERT( !full() );
            new (buffer_ + size_) T;
            ++size_;
        }


        void unchecked_push_back_n( size_type n )
        {
            BOOST_ASSERT( size_ + n <= members_.capacity_ );
            unchecked_push_back_n( n, boost::has_trivial_assign<T>() );
        }


        template< class ForwardIterator >
        void unchecked_push_back( ForwardIterator begin_arg,
                                  ForwardIterator end_arg ) // non-growing
        {
            BOOST_ASSERT( size_ + std::distance(begin_arg, end_arg) <= members_.capacity_ );
            copy_impl( begin_arg, end_arg, buffer_ + size_ );
            size_ += std::distance(begin_arg, end_arg);
        }


        void reserve_precisely( size_type n )
        {
            BOOST_ASSERT( members_.capacity_  >= N );

            if( n <= members_.capacity_ )
                return;
            reserve_impl( n );
            BOOST_ASSERT( members_.capacity_ == n );
        }


        void reserve( size_type n ) // strong
        {
            BOOST_ASSERT( members_.capacity_  >= N );

            if( n <= members_.capacity_ )
                return;

            reserve_impl( new_capacity_impl( n ) );
            BOOST_ASSERT( members_.capacity_ >= n );
        }


        void push_back()
        {
            if( size_ != members_.capacity_ )
            {
                unchecked_push_back();
            }
            else
            {
                reserve( size_ + 1u );
                unchecked_push_back();
            }
        }


        template< class ForwardIterator >
        void push_back( ForwardIterator begin_arg, ForwardIterator end_arg )
        {
            difference_type diff = std::distance(begin_arg, end_arg);
            if( size_ + diff > members_.capacity_ )
                reserve( size_ + diff );
            unchecked_push_back( begin_arg, end_arg );
        }


        iterator insert( const_iterator before, optimized_const_reference x ) // basic
        {
            // @todo: consider if we want to support x in 'this'
            if( size_ < members_.capacity_ )
            {
                bool is_back_insertion = before == cend();
                iterator where = const_cast<T*>(before);

                if( !is_back_insertion )
                {
                    grow_back_one();
                    std::copy( before, cend() - 1u, where + 1u );
                    *where = x;
                    BOOST_ASSERT( is_valid() );
                 }
                else
                {
                    unchecked_push_back( x );
                }
                return where;
            }

            auto_buffer temp( new_capacity_impl( size_ + 1u ) );
            temp.unchecked_push_back( cbegin(), before );
            iterator result = temp.end();
            temp.unchecked_push_back( x );
            temp.unchecked_push_back( before, cend() );
            one_sided_swap( temp );
            BOOST_ASSERT( is_valid() );
            return result;
        }


        template< class ForwardIterator >
        void insert( const_iterator before,
                     ForwardIterator begin_arg, ForwardIterator end_arg ) // basic
        {
            typedef typename std::iterator_traits<ForwardIterator>
                ::iterator_category category;
            insert_impl( before, begin_arg, end_arg, category() );
        }


        void pop_back()
        {
            BOOST_ASSERT( !empty() );
            auto_buffer_destroy( buffer_ + size_ - 1, boost::has_trivial_destructor<T>() );
            --size_;
        }


        void pop_back_n( size_type n )
        {
            BOOST_ASSERT( n <= size_ );
            if( n )
            {
                destroy_back_n( n );
                size_ -= n;
            }
        }


        void clear()
        {
            pop_back_n( size_ );
        }


        iterator erase( const_iterator where )
        {
            BOOST_ASSERT( !empty() );
            BOOST_ASSERT( cbegin() <= where );
            BOOST_ASSERT( cend() > where );

            unsigned elements = cend() - where - 1u;

            if( elements > 0u )
            {
                const_iterator start = where + 1u;
                std::copy( start, start + elements,
                           const_cast<T*>(where) );
            }
            pop_back();
            BOOST_ASSERT( !full() );
            iterator result = const_cast<T*>( where );
            BOOST_ASSERT( result <= end() );
            return result;
        }


        iterator erase( const_iterator from, const_iterator to )
        {
            BOOST_ASSERT( !(std::distance(from,to)>0) ||
                          !empty() );
            BOOST_ASSERT( cbegin() <= from );
            BOOST_ASSERT( cend() >= to );

            unsigned elements = std::distance(to,cend());

            if( elements > 0u )
            {
                BOOST_ASSERT( elements > 0u );
                std::copy( to, to + elements,
                           const_cast<T*>(from) );
            }
            pop_back_n( std::distance(from,to) );
            BOOST_ASSERT( !full() );
            iterator result = const_cast<T*>( from );
            BOOST_ASSERT( result <= end() );
            return result;
        }


        void shrink_to_fit()
        {
            if( is_on_stack() || !GrowPolicy::should_shrink(size_,members_.capacity_) )
                return;

            reserve_impl( size_ );
            members_.capacity_ = (std::max)(size_type(N),members_.capacity_);
            BOOST_ASSERT( is_on_stack() || size_ == members_.capacity_ );
            BOOST_ASSERT( !is_on_stack() || size_ <= members_.capacity_ );
        }


        pointer uninitialized_grow( size_type n ) // strong
        {
            if( size_ + n <= members_.capacity_ )
                reserve( size_ + n );

            pointer res = end();
            size_ += n;
            return res;
        }


        void uninitialized_shrink( size_type n ) // nothrow
        {
            // @remark: test for wrap-around
            BOOST_ASSERT( size_ - n <= members_.capacity_ );
            size_ -= n;
        }


        void uninitialized_resize( size_type n )
        {
            if( n > size() )
                uninitialized_grow( n - size() );
            else if( n < size() )
                uninitialized_shrink( size() - n );

           BOOST_ASSERT( size() == n );
        }

        void swap( auto_buffer& r )
        {
            bool on_stack      = is_on_stack();
            bool r_on_stack    = r.is_on_stack();
            bool both_on_heap  = !on_stack && !r_on_stack;
            if( both_on_heap )
            {
                boost::swap( get_allocator(), r.get_allocator() );
                boost::swap( members_.capacity_, r.members_.capacity_ );
                boost::swap( buffer_, r.buffer_ );
                boost::swap( size_, r.size_ );
                BOOST_ASSERT( is_valid() );
                BOOST_ASSERT( r.is_valid() );
                return;
            }

            BOOST_ASSERT( on_stack || r_on_stack );
            bool exactly_one_on_stack = (on_stack && !r_on_stack) ||
                                        (!on_stack && r_on_stack);

            //
            // Remark: we now know that we can copy into
            //         the unused stack buffer.
            //
            if( exactly_one_on_stack )
            {
                auto_buffer* one_on_stack = on_stack ? this : &r;
                auto_buffer* other        = on_stack ? &r : this;
                pointer new_buffer = static_cast<T*>(other->members_.address());
                copy_impl( one_on_stack->begin(), one_on_stack->end(),
                           new_buffer );                            // strong
                one_on_stack->~auto_buffer();                       // nothrow
                boost::swap( get_allocator(), r.get_allocator() );  // assume nothrow
                boost::swap( members_.capacity_, r.members_.capacity_ );
                boost::swap( size_, r.size_ );
                one_on_stack->buffer_ = other->buffer_;
                other->buffer_        = new_buffer;
                BOOST_ASSERT( other->is_on_stack() );
                BOOST_ASSERT( !one_on_stack->is_on_stack() );
                BOOST_ASSERT( is_valid() );
                BOOST_ASSERT( r.is_valid() );
                return;
            }

            BOOST_ASSERT( on_stack && r_on_stack );
            swap_helper( *this, r, boost::has_trivial_assign<T>() );
            BOOST_ASSERT( is_valid() );
            BOOST_ASSERT( r.is_valid() );
        }


            members_type( size_type capacity )
               : capacity_(capacity)
            { }


            void* address() const
            { return const_cast<storage&>(static_cast<const storage&>(*this)).address(); }


    template< class T, class SBP, class GP, class A >
    inline void swap( auto_buffer<T,SBP,GP,A>& l, auto_buffer<T,SBP,GP,A>& r )
    {
        l.swap( r );
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator==( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        if( l.size() != r.size() )
            return false;
        return std::equal( l.begin(), l.end(), r.begin() );
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator!=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(l == r);
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator<( const auto_buffer<T,SBP,GP,A>& l,
                           const auto_buffer<T,SBP,GP,A>& r )
    {
        return std::lexicographical_compare( l.begin(), l.end(),
                                             r.begin(), r.end() );
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator>( const auto_buffer<T,SBP,GP,A>& l,
                           const auto_buffer<T,SBP,GP,A>& r )
    {
        return (r < l);
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator<=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(r > l);
    }


    template< class T, class SBP, class GP, class A >
    inline bool operator>=( const auto_buffer<T,SBP,GP,A>& l,
                            const auto_buffer<T,SBP,GP,A>& r )
    {
        return !(l < r);
    }

        template<typename Combiner, typename InputIterator>
          result_type operator()(Combiner &combiner,
          InputIterator first, InputIterator last) const
        {
          return combiner(first, last);
        }

        template<typename Combiner, typename InputIterator>
          result_type operator()(Combiner &combiner,
          InputIterator first, InputIterator last) const
        {
          combiner(first, last);
          return result_type();
        }

        slot_call_iterator_cache(const Function &f_arg):
          f(f_arg),
          connected_slot_count(0),
          disconnected_slot_count(0)
        {}

        slot_call_iterator_t(Iterator iter_in, Iterator end_in,
          slot_call_iterator_cache<result_type, Function> &c):
          iter(iter_in), end(end_in),
          cache(&c), callable_iter(end_in)
        {
          lock_next_callable();
        }


        void lock_next_callable() const
        {
          if(iter == callable_iter)
          {
            return;
          }
          for(;iter != end; ++iter)
          {
            lock_type lock(**iter);
            cache->tracked_ptrs.clear();
            (*iter)->nolock_grab_tracked_objects(std::back_inserter(cache->tracked_ptrs));
            if((*iter)->nolock_nograb_connected())
            {
              ++cache->connected_slot_count;
            }else
            {
              ++cache->disconnected_slot_count;
            }
            if((*iter)->nolock_nograb_blocked() == false)
            {
              callable_iter = iter;
              break;
            }
          }
          if(iter == end)
          {
            callable_iter = end;
          }
        }

        template<typename T>
          void operator()(const T&) const
          {}

        tracked_objects_visitor(slot_base *slot) : slot_(slot)
        {}

        template<typename T>
        void operator()(const T& t) const
        {
            m_visit_reference_wrapper(t, mpl::bool_<is_reference_wrapper<T>::value>());
        }

        template<typename T>
        void m_visit_reference_wrapper(const reference_wrapper<T> &t, const mpl::bool_<true> &) const
        {
            m_visit_pointer(t.get_pointer(), mpl::bool_<true>());
        }

        template<typename T>
        void m_visit_pointer(const T &t, const mpl::bool_<true> &) const
        {
            m_visit_not_function_pointer(t, mpl::bool_<!is_function<typename remove_pointer<T>::type>::value>());
        }

        template<typename T>
        void m_visit_not_function_pointer(const T *t, const mpl::bool_<true> &) const
        {
            m_visit_signal(t, mpl::bool_<is_signal<T>::value>());
        }

        template<typename T>
        void m_visit_signal(const T *signal, const mpl::bool_<true> &) const
        {
          if(signal)
            slot_->track_signal(*signal);
        }

        void add_if_trackable(const trackable *trackable) const
        {
          if(trackable)
            slot_->_tracked_objects.push_back(trackable->get_shared_ptr());
        }

        void add_if_trackable(const void *) const {}

        unique_lock(Mutex &m): _mutex(m)
        {
          _mutex.lock();
        }

        ~unique_lock()
        {
          _mutex.unlock();
        }

      template<typename ResultSlot, typename SlotIn, typename SlotFunction>
        ResultSlot replace_slot_function(const SlotIn &slot_in, const SlotFunction &fun)
      {
        ResultSlot slot(fun);
        slot.track(slot_in);
        return slot;
      }

        virtual ~foreign_shared_ptr_impl_base() {}

        foreign_shared_ptr_impl(const FSP &p): _p(p)
        {}

        virtual void * get() const
        {
          return _p.get();
        }

        virtual foreign_shared_ptr_impl * clone() const
        {
          return new foreign_shared_ptr_impl(*this);
        }

        foreign_void_shared_ptr():
          _p(0)
        {}

        foreign_void_shared_ptr(const foreign_void_shared_ptr &other):
          _p(other._p->clone())
        {}

        template<typename FSP>
        explicit foreign_void_shared_ptr(const FSP &fsp):
          _p(new foreign_shared_ptr_impl<FSP>(fsp))
        {}

        ~foreign_void_shared_ptr()
        {
          delete _p;
        }

        foreign_void_shared_ptr & operator=(const foreign_void_shared_ptr &other)
        {
          if(&other == this) return *this;
          foreign_void_shared_ptr(other).swap(*this);
          return *this;
        }

        void swap(foreign_void_shared_ptr &other)
        {
          boost::swap(_p, other._p);
        }

        virtual ~foreign_weak_ptr_impl_base() {}

        foreign_weak_ptr_impl(const FWP &p): _p(p)
        {}

        virtual foreign_void_shared_ptr lock() const
        {
          return foreign_void_shared_ptr(_p.lock());
        }

        virtual bool expired() const
        {
          return _p.expired();
        }

        virtual foreign_weak_ptr_impl * clone() const
        {
          return new foreign_weak_ptr_impl(*this);
        }

        foreign_void_weak_ptr()
        {}

        foreign_void_weak_ptr(const foreign_void_weak_ptr &other):
          _p(other._p->clone())
        {}

        template<typename FWP>
        explicit foreign_void_weak_ptr(const FWP &fwp):
          _p(new foreign_weak_ptr_impl<FWP>(fwp))
        {}

        foreign_void_weak_ptr & operator=(const foreign_void_weak_ptr &other)
        {
          if(&other == this) return *this;
          foreign_void_weak_ptr(other).swap(*this);
          return *this;
        }

        void swap(foreign_void_weak_ptr &other)
        {
          boost::swap(_p, other._p);
        }

        foreign_void_shared_ptr lock() const
        {
          return _p->lock();
        }

        bool expired() const
        {
          return _p->expired();
        }

        group_key_less()
        {}

        group_key_less(const GroupCompare &group_compare): _group_compare(group_compare)
        {}

        bool operator ()(const typename group_key<Group>::type &key1, const typename group_key<Group>::type &key2) const
        {
          if(key1.first != key2.first) return key1.first < key2.first;
          if(key1.first != grouped_slots) return false;
          return _group_compare(key1.second.get(), key2.second.get());
        }


        grouped_list(const group_key_compare_type &group_key_compare):
          _group_key_compare(group_key_compare)
        {}

        grouped_list(const grouped_list &other): _list(other._list),
          _group_map(other._group_map), _group_key_compare(other._group_key_compare)
        {
          // fix up _group_map
          typename map_type::const_iterator other_map_it;
          typename list_type::iterator this_list_it = _list.begin();
          typename map_type::iterator this_map_it = _group_map.begin();
          for(other_map_it = other._group_map.begin();
            other_map_it != other._group_map.end();
            ++other_map_it, ++this_map_it)
          {
            BOOST_ASSERT(this_map_it != _group_map.end());
            this_map_it->second = this_list_it;
            typename list_type::const_iterator other_list_it = other.get_list_iterator(other_map_it);
            typename map_type::const_iterator other_next_map_it = other_map_it;
            ++other_next_map_it;
            typename list_type::const_iterator other_next_list_it = other.get_list_iterator(other_next_map_it);
            while(other_list_it != other_next_list_it)
            {
              ++other_list_it;
              ++this_list_it;
            }
          }
        }

        iterator begin()
        {
          return _list.begin();
        }

        iterator end()
        {
          return _list.end();
        }

        iterator lower_bound(const group_key_type &key)
        {
          map_iterator map_it = _group_map.lower_bound(key);
          return get_list_iterator(map_it);
        }

        iterator upper_bound(const group_key_type &key)
        {
          map_iterator map_it = _group_map.upper_bound(key);
          return get_list_iterator(map_it);
        }

        void push_front(const group_key_type &key, const ValueType &value)
        {
          map_iterator map_it;
          if(key.first == front_ungrouped_slots)
          {// optimization
            map_it = _group_map.begin();
          }else
          {
            map_it = _group_map.lower_bound(key);
          }
          m_insert(map_it, key, value);
        }

        void push_back(const group_key_type &key, const ValueType &value)
        {
          map_iterator map_it;
          if(key.first == back_ungrouped_slots)
          {// optimization
            map_it = _group_map.end();
          }else
          {
            map_it = _group_map.upper_bound(key);
          }
          m_insert(map_it, key, value);
        }

        void erase(const group_key_type &key)
        {
          map_iterator map_it = _group_map.lower_bound(key);
          iterator begin_list_it = get_list_iterator(map_it);
          iterator end_list_it = upper_bound(key);
          if(begin_list_it != end_list_it)
          {
            _list.erase(begin_list_it, end_list_it);
            _group_map.erase(map_it);
          }
        }

        iterator erase(const group_key_type &key, const iterator &it)
        {
          BOOST_ASSERT(it != _list.end());
          map_iterator map_it = _group_map.lower_bound(key);
          BOOST_ASSERT(map_it != _group_map.end());
          BOOST_ASSERT(weakly_equivalent(map_it->first, key));
          if(map_it->second == it)
          {
            iterator next = it;
            ++next;
            // if next is in same group
            if(next != upper_bound(key))
            {
              _group_map[key] = next;
            }else
            {
              _group_map.erase(map_it);
            }
          }
          return _list.erase(it);
        }

        void clear()
        {
          _list.clear();
          _group_map.clear();
        }


        bool weakly_equivalent(const group_key_type &arg1, const group_key_type &arg2)
        {
          if(_group_key_compare(arg1, arg2)) return false;
          if(_group_key_compare(arg2, arg1)) return false;
          return true;
        }

        void m_insert(const map_iterator &map_it, const group_key_type &key, const ValueType &value)
        {
          iterator list_it = get_list_iterator(map_it);
          iterator new_it = _list.insert(list_it, value);
          if(map_it != _group_map.end() && weakly_equivalent(key, map_it->first))
          {
            _group_map.erase(map_it);
          }
          map_iterator lower_bound_it = _group_map.lower_bound(key);
          if(lower_bound_it == _group_map.end() ||
            weakly_equivalent(lower_bound_it->first, key) == false)
          {
            /* doing the following instead of just
              _group_map[key] = new_it;
              to avoid bogus error when enabling checked iterators with g++ */
            _group_map.insert(typename map_type::value_type(key, new_it));
          }
        }

        iterator get_list_iterator(const const_map_iterator &map_it)
        {
          iterator list_it;
          if(map_it == _group_map.end())
          {
            list_it = _list.end();
          }else
          {
            list_it = map_it->second;
          }
          return list_it;
        }
