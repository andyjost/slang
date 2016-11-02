

    stack_context() :
        size( 0), sp( 0)
    {}


    explicit holder( coroutine_context * ctx_) :
        ctx( ctx_), data(), force_unwind( false)
    { BOOST_ASSERT( ctx); }


    holder( holder const& other) :
        ctx( other.ctx), data( other.data),
        force_unwind( other.force_unwind)
    {}


    holder & operator=( holder const& other)
    {
        if ( this == & other) return * this;
        ctx = other.ctx;
        data = other.data;
        force_unwind = other.force_unwind;
        return * this;
    }


    explicit holder( coroutine_context * ctx_, bool force_unwind_ = false) :
        ctx( ctx_), force_unwind( force_unwind_)
    { BOOST_ASSERT( ctx); }


    holder( holder const& other) :
        ctx( other.ctx), force_unwind( other.force_unwind)
    {}


    holder & operator=( holder const& other)
    {
        if ( this == & other) return * this;
        ctx = other.ctx;
        force_unwind = other.force_unwind;
        return * this;
    }
 void nonnull() {}

    bool has_result() const
    { return static_cast< D const* >( this)->impl_->result_; }

    coroutine_base( coroutine_context::ctx_fn fn, stack_context * stack_ctx,
                    bool unwind, bool preserve_fpu) :
        coroutine_base_resume<
            Signature,
            coroutine_base< Signature >,
            typename function_traits< Signature >::result_type,
            function_traits< Signature >::arity
        >(),
        use_count_( 0),
        caller_(),
        callee_( fn, stack_ctx),
        flags_( 0),
        except_()
    {
        if ( unwind) flags_ |= flag_force_unwind;
        if ( preserve_fpu) flags_ |= flag_preserve_fpu;
    }


    virtual ~coroutine_base()
    {}


    static void destroy_( allocator_t & alloc, coroutine_caller * p)
    {
        alloc.destroy( p);
        alloc.deallocate( p, 1);
    }


template< typename Coroutine >
void trampoline1( intptr_t vp)
{
    BOOST_ASSERT( vp);

    reinterpret_cast< Coroutine * >( vp)->run();
}


template< typename Coroutine, typename Arg >
void trampoline2( intptr_t vp)
{
    BOOST_ASSERT( vp);

    tuple< Coroutine *, Arg > * tpl(
        reinterpret_cast< tuple< Coroutine *, Arg > * >( vp) );
    Coroutine * coro( get< 0 >( * tpl) );
    Arg arg( get< 1 >( * tpl) );

    coro->run( arg);
}


    stack_tuple( StackAllocator const& stack_alloc_, std::size_t size) :
        stack_ctx(),
        stack_alloc( stack_alloc_)
    {
        stack_alloc.allocate( stack_ctx, size);
    }


    ~stack_tuple()
    {
        stack_alloc.deallocate( stack_ctx);
    }

    D & operator()()
    {
        BOOST_ASSERT( static_cast< D * >( this)->impl_);
        BOOST_ASSERT( ! static_cast< D * >( this)->impl_->is_complete() );

        static_cast< D * >( this)->impl_->resume();

        return * static_cast< D * >( this);
    }


        void fetch_()
        {
            BOOST_ASSERT( dp_);

            if ( ! dp_->has_result() )
            {
                dp_ = 0;
                val_ = none;
                return;
            }
            val_ = dp_->get();
        }


        void increment_()
        {
            BOOST_ASSERT( dp_);
            BOOST_ASSERT( * dp_);

            ( * dp_)();
            fetch_();
        }


        iterator() :
            dp_( 0), val_()
        {}


        explicit iterator( D * dp) :
            dp_( dp), val_()
        { fetch_(); }


        iterator( iterator const& other) :
            dp_( other.dp_), val_( other.val_)
        {}


        iterator & operator=( iterator const& other)
        {
            if ( this == & other) return * this;
            dp_ = other.dp_;
            val_ = other.val_;
            return * this;
        }


        bool operator==( iterator const& other)
        { return other.dp_ == dp_ && other.val_ == val_; }


        bool operator!=( iterator const& other)
        { return other.dp_ != dp_ || other.val_ != val_; }


        iterator & operator++()
        {
            increment_();
            return * this;
        }


        iterator operator++( int)
        {
            iterator tmp( * this);
            ++*this;
            return tmp;
        }


        reference_t operator*() const
        { return const_cast< optional< Result > & >( val_).get(); }


        pointer_t operator->() const
        { return const_cast< optional< Result > & >( val_).get_ptr(); }


        void fetch_()
        {
            BOOST_ASSERT( dp_);

            if ( ! dp_->has_result() )
            {
                dp_ = 0;
                val_ = none;
                return;
            }
            val_ = dp_->get();
        }


        void increment_()
        {
            BOOST_ASSERT( dp_);
            BOOST_ASSERT( * dp_);

            ( * dp_)();
            fetch_();
        }


        const_iterator() :
            dp_( 0), val_()
        {}


        explicit const_iterator( D const* dp) :
            dp_( const_cast< D * >( dp) ), val_()
        { fetch_(); }


        const_iterator( const_iterator const& other) :
            dp_( other.dp_), val_( other.val_)
        {}


        const_iterator & operator=( const_iterator const& other)
        {
            if ( this == & other) return * this;
            dp_ = other.dp_;
            val_ = other.val_;
            return * this;
        }


        bool operator==( const_iterator const& other)
        { return other.dp_ == dp_ && other.val_ == val_; }


        bool operator!=( const_iterator const& other)
        { return other.dp_ != dp_ || other.val_ != val_; }


        const_iterator & operator++()
        {
            increment_();
            return * this;
        }


        const_iterator operator++( int)
        {
            const_iterator tmp( * this);
            ++*this;
            return tmp;
        }


        reference_t operator*() const
        { return val_.get(); }


        pointer_t operator->() const
        { return val_.get_ptr(); }


    D & operator()()
    {
        BOOST_ASSERT( static_cast< D * >( this)->impl_);
        BOOST_ASSERT( ! static_cast< D * >( this)->impl_->is_complete() );

        static_cast< D * >( this)->impl_->resume();

        return * static_cast< D * >( this);
    }

        iterator() :
           dp_( 0)
        {}


        explicit iterator( D * dp) :
            dp_( dp)
        {}


        iterator & operator=( arg_type a1)
        {
            BOOST_ASSERT( dp_);
            if ( ! ( * dp_)( a1) ) dp_ = 0;
            return * this;
        }


        bool operator==( iterator const& other)
        { return other.dp_ == dp_; }


        bool operator!=( iterator const& other)
        { return other.dp_ != dp_; }


        iterator & operator*()
        { return * this; }


        iterator & operator++()
        { return * this; }


    D & operator()( arg_type a1)
    {
        BOOST_ASSERT( static_cast< D * >( this)->impl_);
        BOOST_ASSERT( ! static_cast< D * >( this)->impl_->is_complete() );

        static_cast< D * >( this)->impl_->resume( a1);

        return * static_cast< D * >( this);
    }


    D & operator()( arg_type a1)
    {
        BOOST_ASSERT( static_cast< D * >( this)->impl_);
        BOOST_ASSERT( ! static_cast< D * >( this)->impl_->is_complete() );

        static_cast< D * >( this)->impl_->resume( a1);

        return * static_cast< D * >( this);
    }

    void resume()
    {
        holder< void > hldr_to( & static_cast< D * >( this)->caller_);
        holder< void > * hldr_from(
            reinterpret_cast< holder< void > * >(
                hldr_to.ctx->jump(
                    static_cast< D * >( this)->callee_,
                    reinterpret_cast< intptr_t >( & hldr_to),
                    static_cast< D * >( this)->preserve_fpu() ) ) );
        BOOST_ASSERT( hldr_from->ctx);
        static_cast< D * >( this)->callee_ = * hldr_from->ctx;
        if ( hldr_from->force_unwind) throw forced_unwind();
        if ( static_cast< D * >( this)->except_)
            rethrow_exception( static_cast< D * >( this)->except_);
    }

    void resume()
    {
        BOOST_ASSERT( static_cast< D * >( this));
        BOOST_ASSERT( ! static_cast< D * >( this)->is_complete() );

        holder< void > hldr_to( & static_cast< D * >( this)->caller_);
        holder< Result > * hldr_from(
            reinterpret_cast< holder< Result > * >(
                hldr_to.ctx->jump(
                    static_cast< D * >( this)->callee_,
                    reinterpret_cast< intptr_t >( & hldr_to),
                    static_cast< D * >( this)->preserve_fpu() ) ) );
        BOOST_ASSERT( hldr_from->ctx);
        static_cast< D * >( this)->callee_ = * hldr_from->ctx;
        result_ = hldr_from->data;
        if ( hldr_from->force_unwind) throw forced_unwind();
        if ( static_cast< D * >( this)->except_)
            rethrow_exception( static_cast< D * >( this)->except_);
    }


    void resume( arg_type a1)
    {
        BOOST_ASSERT( static_cast< D * >( this));
        BOOST_ASSERT( ! static_cast< D * >( this)->is_complete() );

        holder< arg_type > hldr_to( & static_cast< D * >( this)->caller_, a1);
        holder< void > * hldr_from(
            reinterpret_cast< holder< void > * >(
                hldr_to.ctx->jump(
                    static_cast< D * >( this)->callee_,
                    reinterpret_cast< intptr_t >( & hldr_to),
                    static_cast< D * >( this)->preserve_fpu() ) ) );
        BOOST_ASSERT( hldr_from->ctx);
        static_cast< D * >( this)->callee_ = * hldr_from->ctx;
        if ( hldr_from->force_unwind) throw forced_unwind();
        if ( static_cast< D * >( this)->except_)
            rethrow_exception( static_cast< D * >( this)->except_);
    }


    void resume( arg_type a1)
    {
        BOOST_ASSERT( static_cast< D * >( this));
        BOOST_ASSERT( ! static_cast< D * >( this)->is_complete() );

        coroutine_context caller;
        holder< arg_type > hldr_to( & static_cast< D * >( this)->caller_, a1);
        holder< Result > * hldr_from(
            reinterpret_cast< holder< Result > * >(
                hldr_to.ctx->jump(
                    static_cast< D * >( this)->callee_,
                    reinterpret_cast< intptr_t >( & hldr_to),
                    static_cast< D * >( this)->preserve_fpu() ) ) );
        BOOST_ASSERT( hldr_from->ctx);
        static_cast< D * >( this)->callee_ = * hldr_from->ctx;
        result_ = hldr_from->data;
        if ( hldr_from->force_unwind) throw forced_unwind();
        if ( static_cast< D * >( this)->except_)
            rethrow_exception( static_cast< D * >( this)->except_);
    }
 void nonnull() {}
 void nonnull() {}


    static void destroy_( allocator_t & alloc, coroutine_object * p)
    {
        alloc.destroy( p);
        alloc.deallocate( p, 1);
    }


    void enter_()
    {
        holder< void > * hldr_from(
            reinterpret_cast< holder< void > * >(
                this->caller_.jump(
                    this->callee_,
                    reinterpret_cast< intptr_t >( this),
                    this->preserve_fpu() ) ) );
        this->callee_ = * hldr_from->ctx;
        this->result_ = hldr_from->data;
        if ( this->except_) rethrow_exception( this->except_);
    }


    void run_( Caller & c)
    {
        coroutine_context callee;
        coroutine_context caller;
        try
        {
            fn_( c);
            this->flags_ |= flag_complete;
            callee = c.impl_->callee_;
            holder< void > hldr_to( & caller);
            caller.jump(
                callee,
                reinterpret_cast< intptr_t >( & hldr_to),
                this->preserve_fpu() );
            BOOST_ASSERT_MSG( false, "coroutine is complete");
        }
        catch ( forced_unwind const&)
        {}
        catch (...)
        { this->except_ = current_exception(); }

        this->flags_ |= flag_complete;
        callee = c.impl_->callee_;
        holder< void > hldr_to( & caller);
        caller.jump(
            callee,
            reinterpret_cast< intptr_t >( & hldr_to),
            this->preserve_fpu() );
        BOOST_ASSERT_MSG( false, "coroutine is complete");
    }
