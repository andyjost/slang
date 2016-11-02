
    static int after_guard(int current_state,int){return current_state;}

    static int after_exit(int current_state,int){return current_state;}

    static int after_action(int current_state,int){return current_state;}

    static int after_entry(int,int next_state){return next_state;}

    static int after_guard(int,int next_state){return next_state;}

    static int after_exit(int,int next_state){return next_state;}

    static int after_action(int,int next_state){return next_state;}

    static int after_entry(int,int next_state){return next_state;}

    static int after_guard(int current_state,int){return current_state;}

    static int after_exit(int,int next_state){return next_state;}

    static int after_action(int,int next_state){return next_state;}

    static int after_entry(int,int next_state){return next_state;}

    static int after_guard(int current_state,int){return current_state;}

    static int after_exit(int current_state,int){return current_state;}

    static int after_action(int,int next_state){return next_state;}

    static int after_entry(int,int next_state){return next_state;}

    msm_terminal(Expr const &e = Expr())
        : base_type(e)
    {}

    euml_terminal(Expr const &e = Expr())
        : base_type(e)
    {}

    process_any_event_helper(msm::back::HandledEnum& res_,Fsm* self_,::boost::any any_event_):
    res(res_),self(self_),any_event(any_event_),finished(false){}

    template <class Event>
    void operator()(boost::msm::wrap<Event> const&)
    {
        if ( ! finished && ::boost::any_cast<Event>(&any_event)!=0)
        {
            finished = true;
            res = self->process_event_internal(::boost::any_cast<Event>(any_event),false);
 
        }
    }

        HandledEnum operator()(Fsm& fsm, int region,int state,Event const& evt) const
        {
            HandledEnum res = HANDLED_FALSE;
            typename std::deque<cell>::const_iterator it = one_state.begin();
            while (it != one_state.end() && (res != HANDLED_TRUE && res != HANDLED_DEFERRED ))
            {
                HandledEnum handled = (*it)(fsm,region,state,evt);
                // reject is considered as erasing an error (HANDLED_FALSE)
                if ((HANDLED_FALSE==handled) && (HANDLED_GUARD_REJECT==res) )
                    res = HANDLED_GUARD_REJECT;
                else
                    res = handled;
                ++it;
            }
            return res;
        }

    template <class TransitionState>
    static HandledEnum call_submachine(Fsm& fsm, int , int , Event const& evt)
    {
        return (fsm.template get_state<TransitionState&>()).process_any_event( ::boost::any(evt));
    }

        init_cell(dispatch_table* self_)
          : self(self_)
        {}

        default_init_cell(dispatch_table* self_,chain_row* tofill_entries_)
            : self(self_),tofill_entries(tofill_entries_)
        {}

            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt; 
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::defer_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }

            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt; 
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::defer_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }

            template <class State>
            static void execute(boost::msm::wrap<State> const&,chain_row* tofill)
            {
                typedef typename create_stt<Fsm>::type stt; 
                BOOST_STATIC_CONSTANT(int, state_id = (get_state_id<stt,State>::value));
                cell call_no_transition = &Fsm::call_no_transition;
                tofill[state_id+1].one_state.push_back(call_no_transition);
            }

        template <class State>
        void operator()(boost::msm::wrap<State> const& s)
        {
            helper<has_state_delayed_event<State,Event>::type::value,
                   is_composite_state<State>::type::value>::execute(s,tofill_entries);
        }

    dispatch_table()
    {
        // Initialize cells for no transition
        ::boost::mpl::for_each<
            ::boost::mpl::filter_view<
                    Stt, ::boost::is_base_of<transition_event< ::boost::mpl::placeholders::_>, Event> > >
        (init_cell(this));

        ::boost::mpl::for_each<
            typename generate_state_set<Stt>::type, 
            boost::msm::wrap< ::boost::mpl::placeholders::_1> >
         (default_init_cell<Event>(this,entries));

    }
 dummy(int) {}

    NoHistoryImpl(){}

    ~NoHistoryImpl(){}

    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }

    void history_exit(int* const )
    {
        // ignore
    }

    template <class Event>
    const int* history_entry(Event const& )
    {
        // always come back to the original state
        return m_initialStates;
    }

    NoHistoryImpl<NumberOfRegions>& operator=(NoHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }

    AlwaysHistoryImpl(){}

    ~AlwaysHistoryImpl(){}

    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = initial_states[i];
    }

    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_initialStates[i] = current_states[i];
    }

    template <class Event>
    const int* history_entry(Event const& )
    {
        // always load back the last active state
        return m_initialStates;
    }

    AlwaysHistoryImpl<NumberOfRegions>& operator=(AlwaysHistoryImpl<NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
         }
         return *this;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
    }

    ShallowHistoryImpl(){}

    ~ShallowHistoryImpl(){}

    void set_initial_states(int* const initial_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
        {
            m_currentStates[i] = initial_states[i];
            m_initialStates[i] = initial_states[i];
        }
    }

    void history_exit(int* const current_states)
    {
        for (int i=0;i<NumberOfRegions;++i)
            m_currentStates[i] = current_states[i];
    }

    template <class Event>
    const int* history_entry(Event const&)
    {
        if ( ::boost::mpl::contains<Events,Event>::value)
        {
            return m_currentStates;
        }
        // not one of our events, no history
        return m_initialStates;
    }

    ShallowHistoryImpl<Events,NumberOfRegions>& operator=(ShallowHistoryImpl<Events,NumberOfRegions> const& rhs)
    {
         for (int i=0; i<NumberOfRegions;++i)
         {
             m_initialStates[i] = rhs.m_initialStates[i];
             m_currentStates[i] = rhs.m_currentStates[i];
         }
         return *this;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & m_initialStates;
        ar & m_currentStates;
    }

        template <class Fsm>
        static void check_orthogonality()
        {
        }

        template <class Fsm>
        static void check_unreachable_states()
        {
        }

        template <class Fsm>
        static void check_orthogonality()
        {
            BOOST_MPL_ASSERT_RELATION( ::boost::msm::back::check_regions_orthogonality<Fsm>::states_in_regions_raw,
                                       ==, 
                                       ::boost::msm::back::check_regions_orthogonality<Fsm>::cumulated_states_in_regions_raw );

        }

        template <class Fsm>
        static void check_unreachable_states()
        {
            BOOST_MPL_ASSERT_RELATION( ::boost::msm::back::check_no_unreachable_state<Fsm>::states_in_fsm,
                                       ==, 
                                       ::boost::msm::back::check_no_unreachable_state<Fsm>::cumulated_states_in_regions );

        }

        _Ty operator()( _Ty _Left, _Tz _Right) const
        {
            // apply operator+ to operands
            return (_Left + _Right);
        }

        T& operator()(T*  f) const
        {
            return *f;
        }

    fill_state_names(char const** names):m_names(names){}

    template <class StateType>
    void operator()(boost::msm::wrap<StateType> const&)
    {
        m_names[get_state_id<stt,StateType>::value]= typeid(StateType).name();
    }

    get_state_name(std::string& name_to_fill, int state_id):m_name(name_to_fill),m_state_id(state_id){}

    template <class StateType>
    void operator()(boost::msm::wrap<StateType> const&)
    {
        if (get_state_id<stt,StateType>::value == m_state_id)
        {
            m_name = typeid(StateType).name();
        }
    }

    template <class Type>
    void operator()(boost::msm::wrap<Type> const&)
    {
        std::cout << typeid(Type).name() << std::endl;
    }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&, AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState, class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            (fsm.*action)(evt);
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState&,TargetState&,AllStates&)
        {
            // in this front-end, we don't need to know source and target states
            return (fsm.*guard)(evt);
        }

    template <class FSM,class Event>
    void no_transition(Event const& ,FSM&, int )
    {
        BOOST_ASSERT(false);
    }

    template <class FSM,class Event>
    void exception_caught (Event const&,FSM&,std::exception& )
    {
        BOOST_ASSERT(false);
    }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

        none(){}

        template <class Event>
        none(Event const&){}

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::template call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState, class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static ::boost::msm::back::HandledEnum action_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt, 
                                AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            ::boost::msm::front::detail::row2_action_helper<CalledForAction,Event,action>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForAction,FSM>::type::value>());
            return ::boost::msm::back::HANDLED_TRUE;
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

        template <class FSM,class SourceState,class TargetState,class AllStates>
        static bool guard_call(FSM& fsm,Event const& evt,SourceState& src,TargetState& tgt,
                               AllStates& all_states)
        {
            // in this front-end, we don't need to know source and target states
            return ::boost::msm::front::detail::row2_guard_helper<CalledForGuard,Event,guard>::call_helper
                (fsm,evt,src,tgt,all_states,
                ::boost::mpl::bool_< ::boost::is_base_of<CalledForGuard,FSM>::type::value>());
        }

    ~default_base_state(){}

    virtual ~polymorphic_state() {}

            template <class FSM,class Evt,class SourceState,class TargetState, class AllStates>
            static void call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states,::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                ( ::boost::fusion::at_key<CalledForAction>(all_states).*action)(evt);
            }

            template <class FSM,class Evt,class SourceState,class TargetState,class AllStates>
            static bool call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states, ::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                return ( ::boost::fusion::at_key<CalledForGuard>(all_states).*guard)(evt);
            }

    BackInserter_Helper(){}

    FrontInserter_Helper(){}

    Inserter_Helper(){}

    Transform_Helper(){}
