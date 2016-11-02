

    mapping_pair():key(), data(){}


    mapping_pair(const DomainT& key_value, const CodomainT& data_value)
        :key(key_value), data(data_value){}

        static boost::gregorian::date_duration value()
        { 
            return boost::gregorian::date(boost::gregorian::min_date_time) 
                 - boost::gregorian::date(boost::gregorian::min_date_time); 
        }

    inline boost::gregorian::date operator ++(boost::gregorian::date& x)
    {
        return x += boost::gregorian::date::duration_type::unit();
    }


    inline boost::gregorian::date operator --(boost::gregorian::date& x)
    {
        return x -= boost::gregorian::date::duration_type::unit();
    }

    discrete_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    explicit discrete_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }


    domain_type     lower()const { return _lwb; }

    domain_type     upper()const { return _upb; }

    interval_bounds bounds()const{ return _bounds; }


    static discrete_interval open      (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::open());      }

    static discrete_interval right_open(const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::right_open());}

    static discrete_interval left_open (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::left_open()); }

    static discrete_interval closed    (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::closed());    }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };


    static interval_type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds)
    {
        return interval_type(lo, up, bounds, static_cast<interval_type*>(0) );
    }


    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  interval_type
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<interval_type* >(0) 
                );
    }

    static std::string apply()
    { return "dI<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::discrete_interval<DomainT>&) 
    { return 2; }

    continuous_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value)); 
    }

    explicit continuous_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value));
    }


    domain_type     lower()const { return _lwb; }

    domain_type     upper()const { return _upb; }

    interval_bounds bounds()const{ return _bounds; }


    static continuous_interval open     (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::open());      }

    static continuous_interval right_open(const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::right_open());}

    static continuous_interval left_open (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::left_open()); }

    static continuous_interval closed   (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::closed());    }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };


    static interval_type construct(const domain_type lo, const domain_type up, interval_bounds bounds)
    {
        return icl::continuous_interval<DomainT,Compare>(lo, up, bounds,
            static_cast<icl::continuous_interval<DomainT,Compare>* >(0) );
    }


    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  icl::continuous_interval<DomainT,Compare>
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<icl::continuous_interval<DomainT,Compare>* >(0) 
                );
    }

    static std::string apply()
    { return "cI<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::continuous_interval<DomainT>&) 
    { return 2; }

        static inline interval_type right_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::right_open()); }


        static inline interval_type left_open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::left_open()); }


        static inline interval_type open(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::open()); }


        static inline interval_type closed(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up, interval_bounds::closed()); }


        static inline interval_type construct(const DomainT& low, const DomainT& up)
        { return icl::construct<interval_type>(low, up); }


        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            return icl::construct<IntervalT>(
                  shift_lower(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), low)
                , shift_upper(interval_bounds(PretendedBounds), interval_bounds(RepresentedBounds), up )
                ); 
        }


        static inline IntervalT construct(const domain_type& low, const domain_type& up)
        {
            BOOST_STATIC_ASSERT((is_discrete<domain_type>::value || PretendedBounds==RepresentedBounds));
            // For domain_types that are not discrete, e.g. interval<float> 
            // one of the following must hold: If you call
            // interval<T>::right_open(x,y) then interval<T>::type must be static_right_open
            // interval<T>::left_open(x,y)  then interval<T>::type must be static_left_open
            // interval<T>::open(x,y)       then interval<T>::type must be static_open
            // interval<T>::closed(x,y)     then interval<T>::type must be static_closed
            // Conversion between 'PretendedBounds' and 'RepresentedBounds' is only possible
            // for discrete domain_types.
            return icl::construct<IntervalT>(low, up);
        }

    right_open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    explicit right_open_interval(const DomainT& val)
        : _lwb(val), _upb(icl::successor<DomainT,domain_compare>::apply(val))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        // Only for discrete types this ctor creates an interval containing 
        // a single element only.
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    right_open_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }


    domain_type lower()const{ return _lwb; }

    domain_type upper()const{ return _upb; }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };

    static std::string apply()
    { return "[I)<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::right_open_interval<DomainT>&) 
    { return 2; }

    left_open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    explicit left_open_interval(const DomainT& val)
        : _lwb(predecessor<DomainT,domain_compare>::apply(val)), _upb(val)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        // Only for discrete types this ctor creates an interval containing 
        // a single element only.
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
        BOOST_ASSERT((numeric_minimum<DomainT, domain_compare, is_numeric<DomainT>::value >
                                     ::is_less_than(val) )); 
    }

    left_open_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }


    DomainT lower()const{ return _lwb; }

    DomainT upper()const{ return _upb; }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };

    static std::string apply()
    { return "(I]<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::left_open_interval<DomainT>&) 
    { return 2; }

    open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    explicit open_interval(const DomainT& val)
        : _lwb(pred(val)), _upb(succ(val))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        // Only for discrete types this ctor creates an interval containing 
        // a single element only.
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
        BOOST_ASSERT((numeric_minimum<DomainT, domain_compare, is_numeric<DomainT>::value >
                                     ::is_less_than(val) )); 
    }

    open_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }


    DomainT lower()const{ return _lwb; }

    DomainT upper()const{ return _upb; }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };

    static std::string apply()
    { return "(I)<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::open_interval<DomainT>&) 
    { return 2; }

    add_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    add_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = icl::add(*_cont, _iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }


    add_iterator& operator*()    { return *this; }

    add_iterator& operator++()   { return *this; }

    add_iterator& operator++(int){ return *this; }

template<class ContainerT, typename IteratorT>
inline add_iterator<ContainerT> adder(ContainerT& cont, IteratorT iter_)
{
    return add_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

    insert_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    insert_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = _cont->insert(_iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }


    insert_iterator& operator*()    { return *this; }

    insert_iterator& operator++()   { return *this; }

    insert_iterator& operator++(int){ return *this; }

template<class ContainerT, typename IteratorT>
inline insert_iterator<ContainerT> inserter(ContainerT& cont, IteratorT iter_)
{
    return insert_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

    closed_interval() 
        : _lwb(unit_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    explicit closed_interval(const DomainT& val)
        : _lwb(val), _upb(val)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((!icl::is_continuous<DomainT>::value));
    }

    closed_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }


    DomainT lower()const{ return _lwb; }

    DomainT upper()const{ return _upb; }


    DomainT first()const{ return _lwb; }

    DomainT last() const{ return _upb; }


    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }


    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); };

    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); };

    static std::string apply()
    { return "[I]<"+ type_to_string<DomainT>::apply() +">"; }

    static std::size_t apply(const icl::closed_interval<DomainT>&) 
    { return 2; }

    map()
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }


    map(const key_compare& comp): base_type(comp){}


    template <class InputIterator>
    map(InputIterator first, InputIterator past)
        : base_type(first,past){}
 

    template <class InputIterator>
    map(InputIterator first, InputIterator past, const key_compare& comp)
        : base_type(first,past,comp) 
    {}


    map(const map& src)
        : base_type(src)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }


    map& operator = (const map& src) 
    { 
        base_type::operator=(src);
        return *this; 
    }


    map(map&& src)
        : base_type(boost::move(src))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }


    map& operator = (map&& src) 
    { 
        base_type::operator=(src);
        return *this; 
    }


    void swap(map& src) { base_type::swap(src); }


    template<class SubObject>
    bool contains(const SubObject& sub)const 
    { return icl::contains(*this, sub); }


    bool within(const map& super)const 
    { return icl::contains(super, *this); }

    std::size_t iterative_size()const { return base_type::size(); }

    codomain_type operator()(const domain_type& key)const
    {
        const_iterator it = find(key); 
        return it==end() ? identity_element<codomain_type>::value()
                         : it->second;
    }

    map& add(const value_type& value_pair) 
    { 
        return _add<codomain_combine>(value_pair); 
    }

    map& subtract(const element_type& value_pair)
    {
        on_invertible<type, is_total_invertible>
            ::subtract(*this, value_pair);
        return *this;
    }


    map& subtract(const domain_type& key)
    {
        icl::erase(*this, key);
        return *this;
    }


    template<class FragmentT>
    void total_add_intersection(type& section, const FragmentT& fragment)const
    {
        section += *this;
        section.add(fragment);
    }


    void partial_add_intersection(type& section, const element_type& operand)const
    {
        const_iterator it_ = find(operand.first);
        if(it_ != end())
        {
            section.template _add<codomain_combine  >(*it_);
            section.template _add<codomain_intersect>(operand); 
        }
    }


        static void subtract(Type& object, const element_type& operand)
        { object.template _add<inverse_codomain_combine>(operand); }


        static void subtract(Type& object, const element_type& operand)
        { object.template _subtract<inverse_codomain_combine>(operand); }

        static void add_intersection(Type& section, const Type& object, 
                                     const element_type& operand)
        { object.total_add_intersection(section, operand); }

        static void add_intersection(Type& section, const Type& object, 
                                     const element_type& operand)
        { object.partial_add_intersection(section, operand); }

        static void subtract(Type&, typename Type::iterator it_, 
                              const typename Type::codomain_type& )
        { (*it_).second = identity_element<typename Type::codomain_type>::value(); }

        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type&     )
        { object.erase(it_); }

        static void subtract(Type&, typename Type::iterator       it_, 
                              const typename Type::codomain_type& co_value)
        { 
            inverse_codomain_intersect()((*it_).second, co_value); 
        }

        static void subtract(Type& object, typename Type::iterator       it_, 
                                     const typename Type::codomain_type& co_value)
        { 
            inverse_codomain_intersect()((*it_).second, co_value); 
            if((*it_).second == identity_element<codomain_type>::value())
                object.erase(it_);
        }

        static void flip(Type& object, const typename Type::element_type&)
        { icl::clear(object); }


        static void flip(Type& object, const element_type& operand)
        { 
            object.add(operand);
            ICL_FORALL(typename Type, it_, object)
                (*it_).second = identity_element<codomain_type>::value();
        }


        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, true>
                ::subtract(object, insertion.first, operand.second);
        }


        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, false>
                ::subtract(object, insertion.first, operand.second);
        }

        inline static Type identity_element() { return boost::icl::identity_element<Type>::value(); }

        inline static Type identity_element() { return boost::icl::unit_element<Type>::value(); }

        void operator()(Type&, const Type&)const{}


        void operator()(Type& object, const Type& operand)const
        { 
            if(object == operand)
                //identity_element(); //JODO Old gcc-3.4.4 does not compile this
                object = base_type::identity_element(); //<-- but this.
        }


        void operator()(Type& object, const Type& operand)const
        { object += operand; }


        static void version(Type&){}


        void operator()(Type& object, const Type& operand)const
        { object -= operand; }


        void operator()(Type& object, const Type& operand)const
        { object |= operand; }


        static void version(Type&){}


        void operator()(Type& object, const Type& operand)const
        { object &= ~operand; }


        void operator()(Type& object, const Type& operand)const
        { object &= operand; }


        void operator()(Type& object, const Type& operand)const
        { object ^= operand; }


        void operator()(Type& object, const Type& operand)const
        { object &= operand; }


        void operator()(Type& object, const Type& operand)const
        { object ^= operand; }


        void operator()(Type& object, const Type& operand)const
        { insert(object,operand); }


        void operator()(Type& object, const Type& operand)const
        { erase(object,operand); }


        void operator()(Type& object, const Type& operand)const
        { object *= operand; }


        void operator()(Type& object, const Type& operand)const
        { object /= operand; }


        void operator()(Type& object, const Type& operand)const
        {
            if(object < operand)
                object = operand;
        }


        void operator()(Type& object, const Type& operand)const
        {
            if(object > operand)
                object = operand;
        }


        void operator()(Type& object, const Type& operand)const
        { 
            type()(object, operand);
        }


        void operator()(Type& object, const Type& operand)const
        { 
            type()(object, operand);
        }

        static argument_type proversion(const argument_type& value)
        { 
            return value; 
        }

        static argument_type inversion(const argument_type& value)
        {
            argument_type inverse = Combiner::identity_element();
            Combiner()(inverse, value);
            return inverse;
        }


        argument_type operator()(const argument_type& value)
        { return base_type::proversion(value); }
short       operator()(short       val){return -val;}
int         operator()(int         val){return -val;}
long        operator()(long        val){return -val;}
long long   operator()(long long   val){return -val;}
float       operator()(float       val){return -val;}
double      operator()(double      val){return -val;}
long double operator()(long double val){return -val;}


        Type operator()(const Type& value)
        {
            return base_type::inversion(value);
        }

    inline boost::posix_time::ptime operator ++(boost::posix_time::ptime& x)
    {
        return x += boost::posix_time::ptime::time_duration_type::unit();
    }


    inline boost::posix_time::ptime operator --(boost::posix_time::ptime& x)
    {
        return x -= boost::posix_time::ptime::time_duration_type::unit();
    }

    interval_bounds():_bits(){}

    explicit interval_bounds(bound_type bounds): _bits(bounds){}

    interval_bounds all  ()const { return interval_bounds(_bits & _all  ); }

    interval_bounds left ()const { return interval_bounds(_bits & _left ); }

    interval_bounds right()const { return interval_bounds(_bits & _right); }

    interval_bounds reverse_left ()const { return interval_bounds((~_bits>>1) & _right); }

    interval_bounds reverse_right()const { return interval_bounds((~_bits<<1) & _left ); }


    bound_type bits()const{ return _bits; }


    static interval_bounds open()      { return interval_bounds(_open);     }

    static interval_bounds left_open() { return interval_bounds(_left_open); }

    static interval_bounds right_open(){ return interval_bounds(_right_open);}

    static interval_bounds closed()    { return interval_bounds(_closed);   }

    bounded_value(const domain_type& value, interval_bounds bound)
        : _value(value), _bound(bound) {}


    domain_type     value()const { return _value; }

    interval_bounds bound()const { return _bound; }


template<class LeftT, class RightT>
bool is_element_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}


template<class LeftT, class RightT>
bool is_element_less(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::less;
}


template<class LeftT, class RightT>
bool is_element_greater(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::greater;
}


template<class IntervalContainerT>
bool is_joinable(const IntervalContainerT& container, 
                 typename IntervalContainerT::const_iterator first, 
                 typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!icl::touches(key_value<IntervalContainerT>(it_++),
                         key_value<IntervalContainerT>(next_++)))
            return false;

    return true;
}



template<class LeftT, class RightT>
bool is_inclusion_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}


template<class Type>
inline bool joinable(const Type& _Type, typename Type::iterator& some, typename Type::iterator& next)
{
    // assert: next != end && some++ == next
    return touches(key_value<Type>(some), key_value<Type>(next)) 
        && co_equal(some, next, &_Type, &_Type); 
}


template<class Type>
inline void join_nodes(Type& object, typename Type::iterator& left_, 
                                     typename Type::iterator& right_)
{
    typedef typename Type::interval_type interval_type;
    interval_type right_interval = key_value<Type>(right_);
    object.erase(right_);
    const_cast<interval_type&>(key_value<Type>(left_)) 
        = hull(key_value<Type>(left_), right_interval);
}


template<class Type>
inline typename Type::iterator 
    join_on_left(Type& object, typename Type::iterator& left_, 
                               typename Type::iterator& right_)
{
    typedef typename Type::interval_type interval_type;
    // both left and right are in the set and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    return left_;
}


template<class Type>
inline typename Type::iterator 
    join_on_right(Type& object, typename Type::iterator& left_, 
                                typename Type::iterator& right_)
{
    typedef typename Type::interval_type interval_type;
    // both left and right are in the map and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    right_ = left_;
    return right_;
}


template<class Type>
typename Type::iterator join_left(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.begin())
        return it_;

    // there is a predecessor
    iterator pred_ = it_;
    if(joinable(object, --pred_, it_)) 
        return join_on_right(object, pred_, it_); 

    return it_;
}


template<class Type>
typename Type::iterator join_right(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.end())
        return it_;

    // there is a successor
    iterator succ_ = it_;

    if(++succ_ != object.end() && joinable(object, it_, succ_)) 
        return join_on_left(object, it_, succ_);

    return it_;
}


template<class Type>
typename Type::iterator join_neighbours(Type& object, typename Type::iterator& it_)
{
           join_left (object, it_); 
    return join_right(object, it_);
}


template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    std::pair<iterator,iterator> overlap = object.equal_range(addend);
    iterator first_ = overlap.first,
             end_   = overlap.second,
             last_  = end_; --last_;

    iterator second_= first_; ++second_;

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}


template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend,
                                   typename Type::iterator last_)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    iterator first_ = object.lower_bound(addend);
    //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));
    iterator second_= boost::next(first_), end_ = boost::next(last_);

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}



template<class Type>
void add_front(Type& object, const typename Type::interval_type& inter_val, 
                                   typename Type::iterator&      first_)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    // If the collision sequence has a left residual 'left_resid' it will
    // be split, to provide a standardized start of algorithms:
    // The addend interval 'inter_val' covers the beginning of the collision sequence.

    // only for the first there can be a left_resid: a part of *first_ left of inter_val
    interval_type left_resid = right_subtract(key_value<Type>(first_), inter_val);

    if(!icl::is_empty(left_resid))
    {   //            [------------ . . .
        // [left_resid---first_ --- . . .
        iterator prior_ = cyclic_prior(object, first_);
        const_cast<interval_type&>(key_value<Type>(first_)) 
            = left_subtract(key_value<Type>(first_), left_resid);
        //NOTE: Only splitting
        object._insert(prior_, icl::make_value<Type>(left_resid, co_value<Type>(first_)));
    }

    //POST:
    // [----- inter_val ---- . . .
    // ...[-- first_ --...
}



template<class Type>
void add_segment(Type& object, const typename Type::interval_type& inter_val, 
                                     typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    interval_type lead_gap = right_subtract(inter_val, *it_);
    if(!icl::is_empty(lead_gap))
        //           [lead_gap--- . . .
        // [prior_)           [-- it_ ...
        object._insert(prior(it_), lead_gap);

    // . . . --------- . . . addend interval
    //      [-- it_ --)      has a common part with the first overval
    ++it_;
}



template<class Type>
void add_main(Type& object, typename Type::interval_type& rest_interval, 
                            typename Type::iterator&      it_,
                      const typename Type::iterator&      last_)
{
    typedef typename Type::interval_type interval_type;
    interval_type cur_interval;
    while(it_ != last_)
    {
        cur_interval = *it_ ;
        add_segment(object, rest_interval, it_);
        // shrink interval
        rest_interval = left_subtract(rest_interval, cur_interval);
    }
}



template<class Type>
void add_rear(Type& object, const typename Type::interval_type& inter_val, 
                                  typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    iterator prior_ = cyclic_prior(object, it_);
    interval_type cur_itv = *it_;

    interval_type lead_gap = right_subtract(inter_val, cur_itv);
    if(!icl::is_empty(lead_gap))
        //          [lead_gap--- . . .
        // [prior_)          [-- it_ ...
        object._insert(prior_, lead_gap);
    
    interval_type end_gap = left_subtract(inter_val, cur_itv);
    if(!icl::is_empty(end_gap))
        // [---------------end_gap)
        //      [-- it_ --)
        it_ = object._insert(it_, end_gap);
    else
    {
        // only for the last there can be a right_resid: a part of *it_ right of addend
        interval_type right_resid = left_subtract(cur_itv, inter_val);

        if(!icl::is_empty(right_resid))
        {
            // [--------------)
            //      [-- it_ --right_resid)
            const_cast<interval_type&>(*it_) = right_subtract(*it_, right_resid);
            it_ = object._insert(it_, right_resid);
        }
    }
}

template<class Type>
typename Type::iterator 
    add(Type& object, const typename Type::value_type& addend)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return object.end();

    std::pair<iterator,bool> insertion = object._insert(addend);

    if(insertion.second)
        return on_style_::handle_inserted(object, insertion.first);
    else
        return on_style_::add_over(object, addend, insertion.first);
}



template<class Type>
typename Type::iterator 
    add(Type& object, typename Type::iterator    prior_, 
                const typename Type::value_type& addend)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return prior_;

    iterator insertion = object._insert(prior_, addend);

    if(*insertion == addend)
        return on_style_::handle_inserted(object, insertion);
    else
        return on_style_::add_over(object, addend);
}

template<class Type>
void subtract(Type& object, const typename Type::value_type& minuend)
{
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    if(icl::is_empty(minuend)) return;

    std::pair<iterator, iterator> exterior = object.equal_range(minuend);
    if(exterior.first == exterior.second) return;

    iterator first_ = exterior.first;
    iterator end_   = exterior.second;
    iterator last_  = end_; --last_;

    interval_type leftResid = right_subtract(*first_, minuend);
    interval_type rightResid; 
    if(first_ != end_  )
        rightResid = left_subtract(*last_ , minuend);

    object.erase(first_, end_);

    if(!icl::is_empty(leftResid))
        object._insert(leftResid);

    if(!icl::is_empty(rightResid))
        object._insert(rightResid);
}

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        return inclusion_compare( icl::co_value<LeftT>(left_), 
                                 icl::co_value<RightT>(right_));
    }

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        if(icl::co_value<LeftT>(left_) == icl::co_value<RightT>(right_))
            return inclusion::equal;
        else
            return inclusion::unrelated;
    }

    static int apply(typename LeftT::const_iterator&, typename RightT::const_iterator)
    {
        return inclusion::equal;
    }

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        using namespace boost::mpl;
        typedef typename LeftT::codomain_type  LeftCodomainT;
        typedef typename RightT::codomain_type RightCodomainT;

        return
            if_<
                bool_<is_concept_equivalent<is_set,LeftCodomainT,
                                                   RightCodomainT>::value>,
                settic_codomain_compare<LeftT,RightT>,
                atomic_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left_, right_);
    }
 


    subset_comparer(const LeftT&      left,
                    const RightT&     right,
                    const LeftIterT&  left_end,
                    const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), _result(equal)
    {}


    int result()const{ return _result; }



    int co_compare(LeftIterT& left, RightIterT& right)
    {
        using namespace boost::mpl;

        return  
            if_<
                bool_<is_concept_equivalent<is_interval_map,LeftT,RightT>::value>,
                map_codomain_compare<LeftT,RightT>,
                empty_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left,right);
    }


    int restrict_result(int state) { return _result &= state; }


    int proceed(LeftIterT& left, RightIterT& right)
    {
        if(upper_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left  ..)  
            // right .....)
            _prior_left = left;
            ++left;
            return nextleft;
        }
        else if(upper_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left  .....)
            // right ..)
            _prior_right = right;
            ++right;
            return nextright;
        }
        else//key_value<LeftT>(left).upper_equal(key_value<RightT>(right))
        {   // left  ..)
            // right ..)
            ++left; 
            ++right;    
            return nextboth;
        }
    }


    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end && right == _right_end)
            return stop;
        else if(left == _left_end)
        {   // left: ....end    left could be subset
            // right:....[..
            restrict_result(subset);
            return stop;
        }
        else if(right == _right_end)
        {   // left: ....[..    left could be superset
            // right:....end
            restrict_result(superset);
            return stop;
        }
        else if(exclusive_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: [..) . . .[---)      left could be superset
            // right:           [..)....  if [---) exists
            restrict_result(superset);
            if(unrelated == _result)
                return stop;
            else
            {
                LeftIterT joint_ = _left.lower_bound(key_value<RightT>(right));
                if(joint_ == _left.end())
                {
                    _result = unrelated;
                    return stop;
                }
                else
                {
                    left = joint_;
                    return nextboth;
                }
            }
        }
        else if(exclusive_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left:             [..  left could be subset
            // right:....) . . .[---) if [---) exists 
            restrict_result(subset);
            if(unrelated == _result)
                return stop;
            else
            {
                RightIterT joint_ = _right.lower_bound(key_value<LeftT>(left));
                if(joint_ == _right.end())
                {
                    _result = unrelated;
                    return stop;
                }
                else
                {
                    right = joint_;
                    return nextboth;
                }
            }
        }

        // left and right have intervals with nonempty intersection:
        if(_compare_codomain)
            if(unrelated == restrict_result(co_compare(left,right)))
                return stop;

        // examine left borders only. Right borders are checked in proceed
        if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: ....[...     left could be superset
            // right:....   [..
            if(unrelated == restrict_result(superset))
                return stop;
        }
        else if(lower_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left: ....   [..   left can be subset
            // right:....[...
            if(unrelated == restrict_result(subset))
                return stop;
        }
        //else key_value<LeftT>(right).lower_equal(key_value<RightT>(left))
            // left: ....[..   both can be equal
            // right:....[..
            // nothing to do: proceed

        return proceed(left, right);
    }


    int next_left(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {   // left: ..)end    left could be subset
            // right:......)
            restrict_result(subset);
            return stop;            
        }
        else if(!touches(key_value<LeftT>(_prior_left), key_value<LeftT>(left)))
        {   // left: ..)   [..
            // right:.........)
            if(lower_less(key_value<RightT>(right), key_value<LeftT>(left)))
            {   //   ..)   [..   left could be subset
                //   ..........)
                if(unrelated == restrict_result(subset))
                    return stop;            
            }
            //else   ..)   [...
            //          [..
            if(_compare_codomain && intersects(key_value<LeftT>(left),key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }
        else
        {   // left: ..)[..  left could be subset
            // right:.......)
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }

        return proceed(left, right);
    }



    int next_right(LeftIterT& left, RightIterT& right)
    {
        if(right == _right_end)
        {   // left: ......)    left could be superset
            // right:..)end
            restrict_result(superset);
            return stop;            
        }
        else if(!touches(key_value<RightT>(_prior_right), key_value<RightT>(right)))
        {   // left: .........)
            // right:..)   [..
            if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
            {   //       [....)  left could be superset
                //   ..)   [..
                if(unrelated == restrict_result(superset))
                    return stop;            
            }
            //else       [....)
            //   ..)   [..
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }
        else
        {
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }

        return proceed(left, right);
    }

template<class LeftT, class RightT>
int subset_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef subset_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
    {
        switch(state){
        case Step::nextboth:    state = step.next_both(left_, right_);  break;
        case Step::nextleft:    state = step.next_left(left_, right_);  break;
        case Step::nextright:   state = step.next_right(left_, right_); break;
        }
    }
    return step.result();
}

    element_iterator()
        : _saltator(identity_element<segment_iterator>::value())
        , _reptator(identity_element<domain_difference_type>::value()){}


    explicit element_iterator(segment_iterator jumper)
        : _saltator(jumper), _reptator(identity_element<domain_difference_type>::value()) {}


    template <class SaltatorT>
    bool equal(element_iterator<SaltatorT> const& other) const
    {
        return this->_saltator == other._saltator
            && this->_reptator == other._reptator;
    }


    void increment()
    { 
        if(_reptator < icl::pred(adapt::length(_saltator)))
            ++_reptator; 
        else
        {
            ++_saltator;
            _reptator = identity_element<domain_difference_type>::value();
        }
    }


    void decrement()
    { 
        if(identity_element<domain_difference_type>::value() < _reptator)
            --_reptator; 
        else
        {
            --_saltator;
            _reptator = adapt::length(_saltator);
            --_reptator;
        }
    }


    value_type dereference()const
    {
        return adapt::transient_element(_inter_pos, _saltator, _reptator);
    }

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        return inclusion_compare( co_value<LeftT>(left_), 
                                 co_value<RightT>(right_));
    }

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        if(co_value<LeftT>(left_) == co_value<RightT>(right_))
            return inclusion::equal;
        else
            return inclusion::unrelated;
    }

    static int apply(typename LeftT::const_iterator&, typename RightT::const_iterator&)
    {
        return inclusion::equal;
    }

    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        using namespace boost::mpl;
        typedef typename LeftT::codomain_type  LeftCodomainT;
        typedef typename RightT::codomain_type RightCodomainT;

        return
            if_<
                bool_<is_concept_equivalent<is_set,LeftCodomainT,
                                                   RightCodomainT>::value>,
                settic_codomain_compare<LeftT,RightT>,
                atomic_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left_, right_);
    }
 

    subset_comparer(const LeftT&      left,
                    const RightT&     right,
                    const LeftIterT&  left_end,
                    const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), _result(equal)
    {}


    int result()const{ return _result; }


    int co_compare(LeftIterT& left, RightIterT& right)
    {
        using namespace boost::mpl;
        typedef typename codomain_type_of<LeftT>::type  LeftCodomainT;
        typedef typename codomain_type_of<RightT>::type RightCodomainT;

        return  
            if_<
                bool_<is_concept_equivalent<is_element_map,LeftT,RightT>::value>,
                map_codomain_compare<LeftT,RightT>,
                empty_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left,right);
    }


    int restrict_result(int state) { return _result &= state; }


    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end && right == _right_end)
            return stop;
        else if(left == _left_end)
        {
            restrict_result(subset);
            return stop;
        }
        else if(right == _right_end)
        {
            restrict_result(superset);
            return stop;
        }
        else if(typename LeftT::key_compare()(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left:  *left . . *joint_     left could be superset
            // right:           *right ...  if joint_ exists
            restrict_result(superset);
            if(unrelated == _result)
                return stop;
            else
            {
                LeftIterT joint_ = _left.lower_bound(key_value<RightT>(right));
                if(    joint_ == _left.end() 
                    || typename LeftT::key_compare()(key_value<RightT>(right), key_value<LeftT>(joint_)))
                {
                    _result = unrelated;
                    return stop;
                }
                else
                    left = joint_;
            }
        }
        else if(typename LeftT::key_compare()(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left:             *left   left could be subset
            // right:*right . . .*joint_ if *joint_ exists 
            restrict_result(subset);
            if(unrelated == _result)
                return stop;
            else
            {
                RightIterT joint_ = _right.lower_bound(key_value<LeftT>(left));
                if(    joint_ == _right.end()
                    || typename LeftT::key_compare()(key_value<LeftT>(left), key_value<RightT>(joint_)))
                {
                    _result = unrelated;
                    return stop;
                }
                else
                    right = joint_;
            }
        }

        // left =key= right 
        if(_compare_codomain)
            if(unrelated == restrict_result(co_compare(left,right)))
                return stop;

        ++left;
        ++right;
        return nextboth;
    }

template<class LeftT, class RightT>
int subset_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef subset_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
        state = step.next_both(left_, right_);

    return step.result();
}


template<class LeftT, class RightT>
int subset_compare(const LeftT& left, const RightT& right)
{
    return subset_compare
        (
            left, right,
            left.begin(), left.end(),
            right.begin(), right.end()
        );
}

    bool operator()(const IntervalT& left, const IntervalT& right)const
    { 
        return icl::non_empty::exclusive_less(left, right); 
    }


    mapped_reference(const FirstT& fst, second_reference_type snd) : first(fst), second(snd){}


    template<class FstT, class SndT>
    mapped_reference(const mapped_reference<FstT, SndT>& source):
        first(source.first), second(source.second){}

operator != (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(right == left); 
}

operator < (                         const StdPairT& left, 
            const mapped_reference<FirstT, SecondT>& right)
{ 
    return right > left; 
}

operator > (                         const StdPairT& left, 
            const mapped_reference<FirstT, SecondT>& right)
{ 
    return right < left; 
}

operator <= (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(right < left); 
}

operator >= (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(left < right); 
}

template<class FirstT, class SecondT>
inline mapped_reference<FirstT, SecondT> make_mapped_reference(const FirstT& left, SecondT& right)
{ return mapped_reference<FirstT, SecondT>(left, right); }


template<class ObjectT, class ConstObjectT, class IteratorT>
bool common_range(IteratorT& lwb, IteratorT& upb, ObjectT& x1, const ConstObjectT& x2)
{
    // lwb and upb are iterators of x1 marking the lower and upper bound of
    // the common range of x1 and x2.
    typedef typename ConstObjectT::const_iterator ConstObject_iterator;
    // ObjectT may be const or non const. 
    typedef typename remove_const<ObjectT>::type  PureObjectT;

    lwb = x1.end();
    upb = x1.end();

    if(icl::is_empty(x1) || icl::is_empty(x2)) 
        return false;

    IteratorT x1_fst_ = x1.begin();
    IteratorT x1_lst_ = x1.end(); x1_lst_--;

    ConstObject_iterator x2_fst_ = x2.begin();
    ConstObject_iterator x2_lst_ = x2.end(); x2_lst_--;

    typename ObjectT::key_compare key_less;
    if(key_less(icl::key_value< PureObjectT>(x1_lst_), 
                icl::key_value<ConstObjectT>(x2_fst_))) // {x1}   {x2}
        return false;
    if(key_less(icl::key_value<ConstObjectT>(x2_lst_), 
                icl::key_value< PureObjectT>(x1_fst_))) // {x2}   {x1} 
        return false;

    // We do have a common range
    lwb = x1.lower_bound(icl::key_value<ConstObjectT>(x2_fst_));
    upb = x1.upper_bound(icl::key_value<ConstObjectT>(x2_lst_));

    return true;
}

template<class SetType>
inline bool within(const SetType& sub, const SetType& super)
{
    if(&super == &sub)                   return true;
    if(icl::is_empty(sub))               return true;
    if(icl::is_empty(super))             return false;

    typename SetType::const_iterator common_lwb_, common_upb_;
    if(!common_range(common_lwb_, common_upb_, sub, super))
        return false;

    typename SetType::const_iterator sub_ = common_lwb_, super_;
    while(sub_ != common_upb_)
    {
        super_ = super.find(*sub_++);
        if(super_ == super.end()) 
            return false;
    }
    return true;
}


template<class SetType>
bool intersects(const SetType& left, const SetType& right)
{
    typename SetType::const_iterator common_lwb_right_, common_upb_right_;
    if(!common_range(common_lwb_right_, common_upb_right_, right, left))
        return false;

    typename SetType::const_iterator right_ = common_lwb_right_, found_;
    while(right_ != common_upb_right_)
    {
        found_ = left.find(*right_++);
        if(found_ != left.end()) 
            return true; // found a common element
    }
    // found no common element
    return false;    
}

template<class SetType>
inline bool lexicographical_equal(const SetType& left, const SetType& right)
{
    if(&left == &right)
        return true;
    else return left.iterative_size() == right.iterative_size()
             && std::equal(left.begin(), left.end(), right.begin()); 
}


template<class IntervalMapT>
bool is_joinable(const IntervalMapT& container, 
                 typename IntervalMapT::const_iterator first, 
                 typename IntervalMapT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalMapT::const_iterator it_ = first, next_ = first;
    ++next_;

    const typename IntervalMapT::codomain_type& co_value 
        = icl::co_value<IntervalMapT>(first);
    while(it_ != past)
    {
        if(icl::co_value<IntervalMapT>(next_) != co_value)
            return false;
        if(!icl::touches(key_value<IntervalMapT>(it_++),
                         key_value<IntervalMapT>(next_++)))
            return false;
    }

    return true;
}


    static bool is_absorbable(const codomain_type&){ return false; }


    static bool is_absorbable(const codomain_type& co_value)
    {
        return co_value == Combiner::identity_element();
    }

        template <typename ElementContainerT, typename IntervalContainerT>
        void atomize(ElementContainerT& result, const IntervalContainerT& src)
        {
            ICL_const_FORALL(typename IntervalContainerT, itv_, src)
            {
                const typename IntervalContainerT::key_type& itv   = icl::key_value<IntervalContainerT>(itv_);
                typename IntervalContainerT::codomain_type   coval = icl::co_value<IntervalContainerT>(itv_);

                for(typename IntervalContainerT::domain_type element = first(itv); element <= last(itv); ++element)
                    icl::insert(result, icl::make_value<ElementContainerT>(element, coval));
            }
        }


        template <typename IntervalContainerT, typename ElementContainerT>
        void cluster(IntervalContainerT& result, const ElementContainerT& src)
        {
            typedef typename IntervalContainerT::key_type key_type;
            ICL_const_FORALL(typename ElementContainerT, element_, src)
            {
                const typename ElementContainerT::key_type&  key  
                    = key_value<ElementContainerT>(element_);
                const typename codomain_type_of<ElementContainerT>::type& coval 
                    = co_value<ElementContainerT>(element_);

                result += icl::make_value<IntervalContainerT>(key_type(key), coval);
            }
        }

            void operator()(AtomizedType& atomized, const ClusteredType& clustered)
            {
                segmental::atomize(atomized, clustered);
            }

            void operator()(ClusteredType& clustered, const AtomizedType& atomized)
            {
                segmental::cluster(clustered, atomized);
            }

            void operator()(JointType& joint, SplitType& split)
            {
                icl::join(split);
                ICL_FORALL(typename SplitType, split_, split)
                    joint.insert(*split_);
            }

            void operator()(AbsorberType& absorber, EnricherType& enricher)
            {
                icl::absorb_identities(enricher);
                ICL_FORALL(typename EnricherType, enricher_, enricher)
                    absorber.insert(*enricher_);
            }
 

    element_comparer(const LeftT&      left,
                     const RightT&     right,
                     const LeftIterT&  left_end,
                     const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), _result(equal)
    {}


    int result()const{ return _result; }


    bool covalues_are_equal(LeftIterT& left, RightIterT& right)
    {
        if(co_value<LeftT>(left) < co_value<RightT>(right))
            _result = less;
        if(co_value<RightT>(right) < co_value<LeftT>(left))
            _result = greater;
        return _result == equal;
    }


    int proceed(LeftIterT& left, RightIterT& right)
    {
        if(upper_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {
            _prior_left = left;
            ++left;
            return nextleft;
        }
        else if(upper_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {
            _prior_right = right;
            ++right;
            return nextright;
        }
        else
        {
            ++left; 
            ++right;    
            return nextboth;
        }
    }


    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {
            _result = (right == _right_end) ? equal : less;
            return stop;
        }

        // left != _left_end
        if(right == _right_end)
        {
            _result = greater;
            return stop;
        }

        // The starting intervals have to begin equally
        if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: same A... = sameA...
            // right:same  B.. = sameB...
            _result = less;
            return stop;
        }

        if(lower_less(key_value<LeftT>(right), key_value<RightT>(left)))
        {   // left: same  B.. = sameB...
            // right:same A... = sameA...
            _result = greater;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }


    int next_left(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {   // left: same
            // right:sameA...
            _result = less;
            return stop;
        }

        if(!key_value<LeftT>(_prior_left).touches(key_value<LeftT>(left)))
        {   // left: same B = sameB...
            // right:sameA  = sameA...
            _result = greater;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }


    int next_right(LeftIterT& left, RightIterT& right)
    {
        if(right == _right_end)
        {   // left: sameA...
            // right:same
            _result = greater;
            return stop;
        }

        if(!key_value<RightT>(_prior_right).touches(key_value<RightT>(right)))
        {
            // left: sameA... = sameA...
            // right:same B.. = sameB...
            _result = less;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }




template<class LeftT, class RightT>
int element_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef element_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
    {
        switch(state){
        case Step::nextboth:  state = step.next_both (left_, right_); break;
        case Step::nextleft:  state = step.next_left (left_, right_); break;
        case Step::nextright: state = step.next_right(left_, right_); break;
        }
    }
    return step.result();
}


template <class ObjectT, class CoObjectT>
bool intersects(const ObjectT& left, const CoObjectT& right)
{
    typedef typename CoObjectT::const_iterator co_iterator;
    co_iterator right_common_lower_, right_common_upper_;
    if(!Set::common_range(right_common_lower_, right_common_upper_, right, left))
        return false;

    co_iterator right_ = right_common_lower_;
    while(right_ != right_common_upper_)
        if(!(left.find(key_value<CoObjectT>(right_++))==left.end()))
            return true;

    return false;
}



template<class MapT>
typename MapT::const_iterator next_proton(typename MapT::const_iterator& iter_, const MapT& object)
{
    while(   iter_ != object.end() 
          && (*iter_).second == identity_element<typename MapT::codomain_type>::value())
        ++iter_;

    return iter_;
}

template<class MapT>
bool lexicographical_distinct_equal(const MapT& left, const MapT& right)
{
    if(&left == &right)        
        return true;

    typename MapT::const_iterator left_  = left.begin();
    typename MapT::const_iterator right_ = right.begin();

    left_  = next_proton(left_,  left);
    right_ = next_proton(right_, right);

    while(left_ != left.end() && right_ != right.end())
    {
        if(!(left_->first == right_->first && left_->second == right_->second))
            return false;

        ++left_;
        ++right_;
        left_  = next_proton(left_,  left);
        right_ = next_proton(right_, right);
    }

    return left_ == left.end() && right_ == right.end();
}

        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_element_equal(lhs, rhs);
        }

        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_distinct_equal(lhs, rhs);
        }

        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }

        bool operator()(const Type& sub, const Type& super)const
        {
            return contains(super, sub);
        }

        bool operator()(const Type& super, const Type& sub)const
        {
            return contains(super, sub);
        }


inline interval_bounds left(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_left); }


inline interval_bounds right(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_right); }


inline interval_bounds all(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_all); }


inline bool operator == (const interval_bounds x1, const interval_bounds x2)
{ return x1._bits == x2._bits; }


inline bool operator != (const interval_bounds x1, const interval_bounds x2)
{ return x1._bits != x2._bits; }


inline interval_bounds operator & (interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1._bits & x2._bits); }


inline interval_bounds operator | (interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1._bits | x2._bits); }

inline interval_bounds operator << (interval_bounds bounds, unsigned int shift)
{ return interval_bounds(bounds._bits << shift); }

inline interval_bounds operator >> (interval_bounds bounds, unsigned int shift)
{ return interval_bounds(bounds._bits >> shift); }


inline interval_bounds operator ~ (interval_bounds x1)
{ return all(interval_bounds(~(x1._bits))); }


inline interval_bounds outer_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | right(x2); }


inline interval_bounds inner_bounds(interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1.reverse_right() | x2.reverse_left()); }


inline interval_bounds left_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | (left(x2) >> 1); }


inline interval_bounds right_bounds(interval_bounds x1, interval_bounds x2)
{ return (right(x1) <<1 ) | right(x2); }


inline interval_bounds left_subtract_bounds(interval_bounds x1, interval_bounds x2)
{ return right(x1) | ~(right(x2) << 1); }


inline interval_bounds right_subtract_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | ~(left(x2) >> 1); }


inline bool is_complementary(interval_bounds x1)
{ return x1 == interval_bounds::right_open() || x1 == interval_bounds::left_open(); }


inline bool is_left_closed(interval_bounds bounds)
{ return bounds.left().bits()==2; }


inline bool is_right_closed(interval_bounds bounds)
{ return bounds.right().bits()==1; }


inline std::string left_bracket(interval_bounds bounds)
{ return is_left_closed(bounds) ? "[" : "("; }


inline std::string right_bracket(interval_bounds bounds)
{ return is_right_closed(bounds) ? "]" : ")"; }

template <class IncrementableT>
inline static IncrementableT succ(IncrementableT x) { return ++x; }


template <class DecrementableT>
inline static DecrementableT pred(DecrementableT x) { return --x; }

        inline static DomainT apply(DomainT value){ return ++value; }

        inline static DomainT apply(DomainT value){ return --value; }

        inline static DomainT apply(DomainT value){ return --value; }

        inline static DomainT apply(DomainT value){ return ++value; }

    inline static DomainT apply(DomainT value)
    {
        return detail::successor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }

    inline static DomainT apply(DomainT value)
    {
        return detail::predecessor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }

    static std::string apply(const Type& value)
    {
        std::stringstream repr;
        repr << value;
        return repr.str();
    }

        member_property( bool(Type::* pred)()const ): property<Type>(), m_pred(pred){}

        bool operator()(const Type& x)const { return (x.*m_pred)(); }

    static bool is_less_than(Type){ return true; }

    static bool is_less_than_or(Type, bool){ return true; }

        static std::string to_string()
        { 
            return unary_template_to_string<Unary>::apply()+"<"+type_to_string<Type>::apply()+">"; 
        }

        static std::string apply()
        { 
            return binary_template_to_string<Binary>::apply()+
                "<"+type_to_string<Type1>::apply()+","+type_to_string<Type2>::apply()+">"; 
        }
    

template <typename Type>
Type abs(Type val) { return val < 0 ? -val : val; }
 
        Type operator()()const { return value(); }


    template <class Type>
    inline Type identity_element<Type>::value()
    { 
        return Type(); 
    }

    static Type value()
    {
        return (std::numeric_limits<Type>::infinity)();
    }

    static Type value()
    {
        return (std::numeric_limits<Type>::max)();
    }

    static Type value()
    {
        return Type();
    }

    static Type value()
    {
        return get_numeric_infinity< Type
                                   , has_std_infinity<Type>::value
                                   , has_max_infinity<Type>::value >::value();
    }


    static Type value()
    {
        return  numeric_infinity<Type>::value();
    }


    static Type value()
    {
        return Type(numeric_infinity<typename Type::rep>::value());
    }


    static Type value()
    {
        return Type(numeric_infinity<size_type>::value());
    }


    static Type value()
    {
        return identity_element<difference_type>::value();
    }


    static Type value()
    {
        return identity_element<Type>::value();
    }


    static Type value()
    {
        return
            get_infinity< Type
                        , is_numeric<Type>::value
                        , has_rep_type<Type>::value
                        , has_size_type<Type>::value
                        , has_difference_type<Type>::value
                        >::value();
    }
