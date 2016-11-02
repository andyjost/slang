
    template< class T >
    static void delete_object( const T * pObject )
    {
      delete pObject;
    }

    event_base( detail::rtti_policy::id_provider_type idProvider ) :
      base_type( idProvider )
    {
    }


    virtual ~event_base() {}




inline void intrusive_ptr_add_ref( const ::boost::statechart::event_base * pBase )
{
  pBase->add_ref();
}


inline void intrusive_ptr_release( const ::boost::statechart::event_base * pBase )
{
  if ( pBase->release() )
  {
    ::boost::statechart::detail::delete_helper::delete_object( pBase );
  }
}

    template< class Action, class ExceptionEventHandler >
    result operator()( Action action, ExceptionEventHandler eventHandler )
    {
      try
      {
        return action();
      }
      catch ( ... )
      {
        return eventHandler( ExceptionEvent() );
      }
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase & evt, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        return detail::result_utility::get_result( 
          stt.react( *polymorphic_downcast< const Event * >( &evt ) ) );
      }
      else
      {
        return detail::no_reaction;
      }
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase & evt, const IdType & )
    {
      return detail::result_utility::get_result( stt.react( evt ) );
    }

    virtual ~event_processor() {}


    Scheduler & my_scheduler() const
    {
      return myScheduler_;
    }


    processor_handle my_handle() const
    {
      return myHandle_;
    }


    void initiate()
    {
      initiate_impl();
    }


    void process_event( const event_base & evt )
    {
      process_event_impl( evt );
    }


    void terminate()
    {
      terminate_impl();
    }


    event_processor( my_context ctx ) :
      myScheduler_( ctx.my_scheduler() ),
      myHandle_( ctx.my_handle() )
    {
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase &, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        return detail::result_utility::get_result( stt.defer_event() );
      }
      else
      {
        return detail::no_reaction;
      }
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase &, const IdType & )
    {
      return detail::result_utility::get_result( stt.defer_event() );
    }

    send_function(
      StateBaseType & toState,
      const EventBaseType & evt,
      IdType eventType
    ) :
      toState_( toState ), evt_( evt ), eventType_( eventType )
    {
    }


    result operator()()
    {
      return detail::result_utility::make_result(
        toState_.react_impl( evt_, eventType_ ) );
    }

    template< class StateBaseType >
    static const StateBaseType * deref_if_necessary(
      const StateBaseType * pState )
    {
      return pState;
    }


    template< class Target, class IdType >
    static IdType type_id()
    {
      Target p = 0;
      return type_id_impl< IdType >( p );
    }


    static bool found( const void * pFound )
    {
      return pFound != 0;
    }


    template< class Target >
    static Target not_found()
    {
      return 0;
    }

    template< class IdType, class Type >
    static IdType type_id_impl( const Type * )
    {
      return Type::static_type();
    }

  template< class StateBaseType >
  static const StateBaseType & deref_if_necessary(
    const StateBaseType * pState )
  {
    return *pState;
  }


  template< class Target, class IdType >
  static IdType type_id()
  {
    return remove_reference< Target >::type::static_type();
  }


  template< class Dummy >
  static bool found( const Dummy & )
  {
    return true;
  }


  template< class Target >
  static Target not_found()
  {
    throw std::bad_cast();
  }

    template< class HistorizedState >
    static history_key make_history_key()
    {
      return history_key(
        HistorizedState::context_type::static_type(),
        HistorizedState::orthogonal_position::value );
    }


    typename RttiPolicy::id_type history_context_type() const
    {
      return historyContextType_;
    }

    history_key(
      typename RttiPolicy::id_type historyContextType, 
      orthogonal_position_type historizedOrthogonalRegion
    ) :
      historyContextType_( historyContextType ),
      historizedOrthogonalRegion_( historizedOrthogonalRegion )
    {
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase &, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        return detail::result_utility::get_result( stt.terminate() );
      }
      else
      {
        return detail::no_reaction;
      }
    }

    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase &, const IdType & )
    {
      return detail::result_utility::get_result( stt.terminate() );
    }


    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_base_type & outermostContextBase )
    {
      outermostContextBase.template construct_with_shallow_history<
        DefaultState >( pContext );
    }

    template< class Action, class ExceptionEventHandler >
    result operator()( Action action, ExceptionEventHandler )
    {
      return action();
    }


    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_base_type & outermostContextBase )
    {
      outermostContextBase.template construct_with_deep_history<
        DefaultState >( pContext );
    }

  template< class CommonContext >
  void operator()( CommonContext & ) const {}

    transition_function(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & evt
    ) :
      pTransitionAction_( pTransitionAction ),
      evt_( evt )
    {
    }


    template< class CommonContext >
    void operator()( CommonContext & commonContext ) const
    {
      ( commonContext.template context< TransitionContext >()
        .*pTransitionAction_ )( evt_ );
    }

  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ) {}

  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ctx )
  {
    ctx.template store_deep_history_impl< LeafState >();
  }

  template< class HistorizedState, class LeafState, class Context >
  static void store_deep_history( Context & ctx )
  {
    ctx.outermost_context_base().template store_deep_history<
      HistorizedState, LeafState >();
    ctx.template store_deep_history_impl< LeafState >();
  }




template< class MostDerived, class Context,
          class InnerInitial, history_mode historyMode >
inline void intrusive_ptr_release( const ::boost::statechart::simple_state<
  MostDerived, Context, InnerInitial, historyMode > * pBase )
{
  if ( pBase->release() )
  {
    // The cast is necessary because the simple_state destructor is non-
    // virtual (and inaccessible from this context)
    delete polymorphic_downcast< const MostDerived * >( pBase );
  }
}

    safe_reaction_result( const safe_reaction_result & other ) :
      reactionResult_( other.reactionResult_ )
    {
      // This assert fails when an attempt is made to make multiple copies of
      // a result value. This makes little sense, given the requirement that
      // an obtained result value must be returned out of the react function.
      BOOST_ASSERT( reactionResult_ != consumed );
      other.reactionResult_ = consumed;
    }


    ~safe_reaction_result()
    {
      // This assert fails when an obtained result value is not returned out
      // of the react() function. This can happen if the user accidentally
      // makes more than one call to reaction functions inside react() or
      // accidentally makes one or more calls to reaction functions outside
      // react()
      BOOST_ASSERT( reactionResult_ == consumed );
    }

    safe_reaction_result( reaction_result reactionResult ) :
      reactionResult_( reactionResult )
    {
    }


    operator reaction_result() const
    {
      const reaction_result val = reactionResult_;
      reactionResult_ = consumed;
      return val;
    }

  static ::boost::statechart::result make_result( reaction_result value )
  {
    return value;
  }


  static reaction_result get_result( ::boost::statechart::result value )
  {
    return value;
  }


      id_type dynamic_type() const
      {
        #ifdef BOOST_STATECHART_USE_NATIVE_RTTI
        return id_type( typeid( *this ) );
        #else
        return idProvider_;
        #endif
      }

      template< typename CustomId >
      const CustomId * custom_dynamic_type_ptr() const
      {
        BOOST_ASSERT(
          ( idProvider_->pCustomId_ == 0 ) ||
          ( *idProvider_->pCustomIdType_ == typeid( CustomId ) ) );
        return static_cast< const CustomId * >( idProvider_->pCustomId_ );
      }

      rtti_base_type(
        id_provider_type idProvider
      ) :
        idProvider_( idProvider )
      {
      }


      ~rtti_base_type() {}

      static id_type static_type()
      {
        #ifdef BOOST_STATECHART_USE_NATIVE_RTTI
        return id_type( typeid( const MostDerived ) );
        #else
        return &id_holder< MostDerived >::idProvider_;
        #endif
      }

      template< class CustomId >
      static const CustomId * custom_static_type_ptr()
      {
        BOOST_ASSERT(
          ( id_holder< MostDerived >::idProvider_.pCustomId_ == 0 ) ||
          ( *id_holder< MostDerived >::idProvider_.pCustomIdType_ ==
            typeid( CustomId ) ) );
        return static_cast< const CustomId * >(
          id_holder< MostDerived >::idProvider_.pCustomId_ );
      }


      template< class CustomId >
      static void custom_static_type_ptr( const CustomId * pCustomId )
      {
        #if defined( BOOST_ENABLE_ASSERT_HANDLER ) || !defined( NDEBUG )
        id_holder< MostDerived >::idProvider_.pCustomIdType_ =
          &typeid( CustomId );
        #endif
        id_holder< MostDerived >::idProvider_.pCustomId_ = pCustomId;
      }

      ~rtti_derived_type() {}

      rtti_derived_type() : Base( &id_holder< MostDerived >::idProvider_ ) {}

  count_base() : count_( 0 ) {}

  count_base() : count_( 0 ) {}

    bool ref_counted() const
    {
      return base_type::count_ != 0;
    }


    long ref_count() const
    {
      return base_type::count_;
    }

    counted_base() {}

    ~counted_base() {}

    counted_base( const counted_base & ) : base_type() {}

    counted_base & operator=( const counted_base & ) { return *this; }

    void add_ref() const
    {
      ++base_type::count_;
    }


    bool release() const
    {
      BOOST_ASSERT( base_type::count_ > 0 );
      return --base_type::count_ == 0;
    }


  static void construct(
    const context_ptr_type & pContext,
    OutermostContextBase & outermostContextBase )
  {
    const inner_context_ptr_type pInnerContext =
      to_construct::shallow_construct( pContext, outermostContextBase );
    to_construct::template deep_construct_inner<
      first_inner_initial_list >( pInnerContext, outermostContextBase );
    constructor< inner_context_list, OutermostContextBase >::construct(
      pInnerContext, outermostContextBase );
    to_construct::template deep_construct_inner<
      last_inner_initial_list >( pInnerContext, outermostContextBase );
  }


  static void construct(
    const context_ptr_type & pContext,
    OutermostContextBase & outermostContextBase )
  {
    to_construct::deep_construct( pContext, outermostContextBase );
  }




template< typename T >
inline void avoid_unused_warning( const T & ) {}

      static result react( State & stt, const EventBase & )
      {
        return Reactions::react_without_action( stt );
      }

      static result react( State & stt, const EventBase & evt )
      {
        return Reactions::react_with_action( stt, evt );
      }

      static result react(
        State & stt, const EventBase & evt, const IdType & )
      {
        typedef typename mpl::if_<
          is_same< ActionContext, detail::no_context< Event > >,
          without_action, base_with_action
        >::type reaction;
        return reaction::react( stt, evt );
      }

      static result react( State & stt, const EventBase & evt )
      {
        return Reactions::react_with_action(
          stt, *polymorphic_downcast< const Event * >( &evt ) );
      }

      static result react(
        State & stt, const EventBase & evt, const IdType & eventType )
      {
        if ( eventType == Event::static_type() )
        {
          typedef typename mpl::if_<
            is_same< ActionContext, detail::no_context< Event > >,
            without_action, derived_with_action
          >::type reaction;
          return reaction::react( stt, evt );
        }
        else
        {
          return detail::result_utility::make_result( detail::no_reaction );
        }
      }

    static reaction_result react(
      State & stt, const EventBase & evt, const IdType & eventType )
    {
      typedef typename mpl::if_<
        is_same< Event, EventBase >, base, derived
      >::type reaction;
      return result_utility::get_result(
        reaction::react( stt, evt, eventType ) );
    }




template< class MostDerived, class Allocator >
void * allocate( std::size_t size )
{
  avoid_unused_warning( size );
  // The assert below fails when memory is allocated for an event<>,
  // simple_state<> or state<> subtype object, *and* the first template
  // parameter passed to one of these templates is not equal to the most-
  // derived object being constructed.
  // The following examples apply to all these subtypes:
  // // Example 1
  // struct A {};
  // struct B : sc::simple_state< A, /* ... */ >
  // // Above, the first template parameter must be equal to the most-
  // // derived type
  // 
  // // Example 2
  // struct A : sc::event< A >
  // struct B : A { /* ... */ };
  // void f() { delete new B(); }
  // // Above the most-derived type being constructed is B, but A was passed
  // // as the most-derived type to event<>.
  BOOST_ASSERT( size == sizeof( MostDerived ) );
  return typename boost::detail::allocator::rebind_to<
    Allocator, MostDerived
  >::type().allocate( 1, static_cast< MostDerived * >( 0 ) );
}


template< class MostDerived, class Allocator >
void deallocate( void * pObject )
{
  return typename boost::detail::allocator::rebind_to<
    Allocator, MostDerived
  >::type().deallocate( static_cast< MostDerived * >( pObject ), 1 );
}

    node_state_base( typename RttiPolicy::id_provider_type idProvider ) :
      base_type( idProvider )
    {
    }


    ~node_state_base() {}

    node_state( typename RttiPolicy::id_provider_type idProvider ) :
      base_type( idProvider )
    {
      for ( orthogonal_position_type pos = 0; 
            pos < OrthogonalRegionCount::value; ++pos )
      {
        pInnerStates[ pos ] = 0;
      }
    }


    ~node_state() {}


    void add_inner_state( orthogonal_position_type position,
                          state_base_type * pInnerState )
    {
      BOOST_ASSERT( ( position < OrthogonalRegionCount::value ) &&
                    ( pInnerStates[ position ] == 0 ) );
      pInnerStates[ position ] = pInnerState;
    }


    void remove_inner_state( orthogonal_position_type position )
    {
      BOOST_ASSERT( position < OrthogonalRegionCount::value );
      pInnerStates[ position ] = 0;
    }


    virtual void remove_from_state_list(
      typename state_base_type::state_list_type::iterator & statesEnd,
      typename state_base_type::node_state_base_ptr_type &
        pOutermostUnstableState,
      bool performFullExit )
    {
      state_base_type ** const pPastEnd =
        &pInnerStates[ OrthogonalRegionCount::value ];
      // We must not iterate past the last inner state because *this* state
      // will no longer exist when the last inner state has been removed
      state_base_type ** const pFirstNonNull = std::find_if(
        &pInnerStates[ 0 ], pPastEnd, &node_state::is_not_null );

      if ( pFirstNonNull == pPastEnd )
      {
        // The state does not have inner states but is still alive, this must
        // be the outermost unstable state then.
        BOOST_ASSERT( get_pointer( pOutermostUnstableState ) == this );
        typename state_base_type::node_state_base_ptr_type pSelf =
          pOutermostUnstableState;
        pSelf->exit_impl( pSelf, pOutermostUnstableState, performFullExit );
      }
      else
      {
        // Destroy inner states in the reverse order of construction
        for ( state_base_type ** pState = pPastEnd; pState != pFirstNonNull; )
        {
          --pState;

          // An inner orthogonal state might have been terminated long before,
          // that's why we have to check for 0 pointers
          if ( *pState != 0 )
          {
            ( *pState )->remove_from_state_list(
              statesEnd, pOutermostUnstableState, performFullExit );
          }
        }
      }
    }

    static bool is_not_null( const state_base_type * pInner )
    {
      return pInner != 0;
    }

    leaf_state( typename RttiPolicy::id_provider_type idProvider ) :
      base_type( idProvider )
    {
    }


    ~leaf_state() {}

    void set_list_position(
      typename base_type::state_list_type::iterator listPosition )
    {
      listPosition_ = listPosition;
    }


    virtual void remove_from_state_list(
      typename base_type::state_list_type::iterator & statesEnd,
      typename base_type::node_state_base_ptr_type & pOutermostUnstableState,
      bool performFullExit )
    {
      --statesEnd;
      swap( *listPosition_, *statesEnd );
      ( *listPosition_ )->set_list_position( listPosition_ );
      direct_state_base_ptr_type & pState = *statesEnd;
      // Because the list owns the leaf_state, this leads to the immediate
      // termination of this state.
      pState->exit_impl( pState, pOutermostUnstableState, performFullExit );
    }

    void exit() {}

    state_base( typename RttiPolicy::id_provider_type idProvider ) :
      base_type( idProvider ),
      deferredEvents_( false )
    {
    }

    ~state_base() {}

    void defer_event()
    {
      deferredEvents_ = true;
    }


    bool deferred_events() const
    {
      return deferredEvents_;
    }


    template< class Context >
    void set_context( orthogonal_position_type position, Context * pContext )
    {
      pContext->add_inner_state( position, this );
    }




template< class Allocator, class RttiPolicy >
inline void intrusive_ptr_add_ref(
  const ::boost::statechart::detail::state_base< Allocator, RttiPolicy > * pBase )
{
  pBase->add_ref();
}


template< class Allocator, class RttiPolicy >
inline void intrusive_ptr_release( 
  const ::boost::statechart::detail::state_base< Allocator, RttiPolicy > * pBase )
{
  if ( pBase->release() )
  {
    // The state_base destructor is *not* virtual for performance reasons
    // but intrusive_ptr< state_base > objects are nevertheless used to point
    // to states. This assert ensures that such a pointer is never the last
    // one referencing a state object.
    BOOST_ASSERT( false );
  }
}
