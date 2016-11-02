

   bimap(const allocator_type& al = allocator_type()) :

       base_::relation_set(
           ::boost::multi_index::get<
               logic_relation_set_tag
           >(core)
       ),

       core(al),

       left (
           ::boost::multi_index::get<
               logic_left_tag
           >(core)
       ),
       right (
           ::boost::multi_index::get<
               logic_right_tag
           >(core)
       )

   {}


   template< class InputIterator >
   bimap(InputIterator first,InputIterator last,
         const allocator_type& al = allocator_type()) :

       base_::relation_set(
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(core)
       ),

       core(first,last,ctor_args_list(),al),

       left (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(core)
       ),
       right (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(core)
       )

   {}


   bimap(const bimap& x) :

       base_::relation_set(
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(core)
       ),

       core(x.core),

       left (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(core)
       ),
       right (
           ::boost::multi_index::get<
               BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(core)
       )

   {}


    bimap& operator=(const bimap& x)
    {
        core = x.core;
        return *this;
    }


    template< class IteratorType >
    left_iterator project_left(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(iter.base());
    }


    template< class IteratorType >
    left_const_iterator project_left(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_left_tag>(iter.base());
    }


    template< class IteratorType >
    right_iterator project_right(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(iter.base());
    }


    template< class IteratorType >
    right_const_iterator project_right(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_right_tag>(iter.base());
    }


    template< class IteratorType >
    BOOST_DEDUCED_TYPENAME base_::relation_set::iterator
        project_up(IteratorType iter)
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(iter.base());
    }


    template< class IteratorType >
    BOOST_DEDUCED_TYPENAME base_::relation_set::const_iterator
        project_up(IteratorType iter) const
    {
        return core.template project<
            BOOST_DEDUCED_TYPENAME base_::logic_relation_set_tag>(iter.base());
    }


    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & serialization::make_nvp("mi_core",core);
    }



    relation_modifier_adaptor( const Modifier & m ) : Modifier(m) {}

    relation_modifier_adaptor( const Modifier & m,
                               const FirstExtractor & fe,
                               const SecondExtractor & se ) :
        Modifier(m), FirstExtractor(fe), SecondExtractor(se) {}


    void operator()( NewArgument & x ) const
    {
        Modifier::operator()(
            FirstExtractor ::operator()( x ),
            SecondExtractor::operator()( x )
        );
    }

    unary_modifier_adaptor( const Modifier & m ) : Modifier(m) {}

    unary_modifier_adaptor( const Modifier & m,
                            const Extractor & fe) :
        Modifier(m), Extractor(fe) {}


    void operator()( NewArgument & x ) const
    {
        Modifier::operator()( Extractor::operator()( x ) );
    }

    const Key operator()( const Value & v ) const
    {
        return keyToBase( v );
    }

    const MutantRelationStorage & operator()( const non_mutable_storage & k ) const
    {
        return ::boost::bimaps::relation::detail::mutate<MutantRelationStorage>(k);
    }

    const MutantRelationStorage & operator()( const MutantRelationStorage & k ) const
    {
        return k;
    }


    bool replace(iterator_ position,
                 const value_type_ & x)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),x
        );
    }


    template< class CompatibleLeftType >
    bool replace_left(iterator_ position,
                      const CompatibleLeftType & l)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            ::boost::bimaps::relation::detail::copy_with_left_replaced(*position,l)
        );
    }


    template< class CompatibleRightType >
    bool replace_right(iterator_ position,
                       const CompatibleRightType & r)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            ::boost::bimaps::relation::detail::copy_with_right_replaced(*position,r)
        );
    }


    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }


    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }


    set_view_iterator() {}


    set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}


    set_view_iterator(set_view_iterator const & iter)
      : base_(iter.base()) {}


    typename base_::reference dereference() const
    {
        return const_cast<
            BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )->get_view();
    }



    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }


    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }


    const_set_view_iterator() {}


    const_set_view_iterator(CoreIterator const& iter)
      : base_(iter) {}


    const_set_view_iterator(const_set_view_iterator const & iter)
      : base_(iter.base()) {}


    const_set_view_iterator(set_view_iterator<CoreIterator> i)
      : base_(i.base()) {}




    template< class Archive >
    void save(Archive & ar, const unsigned int) const
    {
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());
    }


    template< class Archive >
    void load(Archive & ar, const unsigned int)
    {
        CoreIterator iter;
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);
        this->base_reference() = iter;
    }


    bool replace(iterator_ position, const value_type_ & x)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(x)
        );
    }


    template< class CompatibleKey >
    bool replace_key(iterator_ position, const CompatibleKey & k)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(
                ::boost::bimaps::relation::detail::
                    copy_with_first_replaced(*position,k)
            )
        );
    }


    template< class CompatibleData >
    bool replace_data(iterator_ position, const CompatibleData & d)
    {
        return derived().base().replace(
            derived().template functor<iterator_to_base_>()(position),
            derived().template functor<value_to_base_>()(
                ::boost::bimaps::relation::detail::
                    copy_with_second_replaced(*position,d)
            )
        );
    }


    template< class Modifier >
    bool modify_key(iterator_ position, Modifier mod)
    {
        return derived().base().modify_key(
            derived().template functor<iterator_to_base_>()(position), mod
        );
    }


    template< class Modifier >
    bool modify_data(iterator_ position, Modifier mod)
    {
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        data_extractor
        <
            BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                        opossite_tag<Tag,BimapType>::type,
            BOOST_DEDUCED_TYPENAME BimapType::relation

        >::type data_extractor_;

        return derived().base().modify(

            derived().template functor<iterator_to_base_>()(position),

            // this may be replaced later by
            // ::boost::bind( mod, ::boost::bind(data_extractor_(),_1) )

            ::boost::bimaps::detail::unary_modifier_adaptor
            <
                Modifier,
                BOOST_DEDUCED_TYPENAME BimapType::relation,
                data_extractor_

            >(mod)
        );
    }


    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }


    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }


    template< class CompatibleKey >
    data_type_ & at(const CompatibleKey& k)
    {
        typedef ::boost::bimaps::detail::
            map_view_iterator<Tag,BimapType> iterator;

        iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->second;
    }


    template< class CompatibleKey >
    data_type_ & operator[](const CompatibleKey& k)
    {
        typedef ::boost::bimaps::detail::
                      map_view_iterator<Tag,BimapType>          iterator;

        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::support::
                         value_type_by<Tag,BimapType>::type     value_type;

        iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            iter = derived().insert( value_type(k,data_type_()) ).first;
        }
        return iter->second;
    }


    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }


    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }


    template< class CompatibleKey >
    const data_type_ & at(const CompatibleKey& k) const
    {
        typedef ::boost::bimaps::detail::
                const_map_view_iterator<Tag,BimapType> const_iterator;

        const_iterator iter = derived().find(k);
        if( iter == derived().end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->second;
    }


    template< class CompatibleKey >
    data_type_ & operator[](const CompatibleKey&)
    {
        BOOST_BIMAP_STATIC_ERROR( OPERATOR_BRACKET_IS_NOT_SUPPORTED, (Derived));
    }




    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }


    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }


template <class T> inline const T&  make_const(const T& t) { return t; }








    map_view_iterator() {}

    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    const_map_view_iterator() {}

    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}

	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    reverse_map_view_iterator() {}

    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    const_reverse_map_view_iterator() {}

    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    local_map_view_iterator() {}

    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// local_map_view_iterator

template< class Tag, class BimapCore >
struct local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct local_map_view_iterator :
    public local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    local_map_view_iterator() {}
    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// local_map_view_iterator

template< class Tag, class BimapCore >
struct local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct local_map_view_iterator :
    public local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    local_map_view_iterator() {}
    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    const_local_map_view_iterator() {}

    const_local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}

    const_local_map_view_iterator(const_local_map_view_iterator const & iter)
      : base_(iter.base()) {}

	const_local_map_view_iterator(local_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}


template< class Archive >                                                 \
    void save(Archive & ar, const unsigned int) const                         \
    {                                                                         \
        ar << ::boost::serialization::make_nvp("mi_iterator",this->base());   \
    }                                                                         \
                                                                              \
    template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// local_map_view_iterator

template< class Tag, class BimapCore >
struct local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct local_map_view_iterator :
    public local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    local_map_view_iterator() {}
    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_local_map_view_iterator :
    public const_local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_local_map_view_iterator() {}
    const_local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_local_map_view_iterator(const_local_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_local_map_view_iterator(local_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
template< class Archive >                                                 \
    void load(Archive & ar, const unsigned int)                               \
    {                                                                         \
        BOOST_DEDUCED_TYPENAME base_::base_type iter;                         \
        ar >> ::boost::serialization::make_nvp("mi_iterator",iter);           \
        this->base_reference() = iter;                                        \
    }
/*===========================================================================*/
#else
#define BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT // None
#endif // BOOST_BIMAP_DISABLE_SERIALIZATION

/*===========================================================================*/
#define BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( METANAME, ITERATOR )       BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER( METANAME, BimapCore,             \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::left_tag>                     \
            ::type::ITERATOR type,                                            \
    typedef BOOST_DEDUCED_TYPENAME BimapCore::core_type::BOOST_NESTED_TEMPLATE\
        index<BOOST_DEDUCED_TYPENAME BimapCore::right_tag>                    \
            ::type::ITERATOR type                                             \
)
/*===========================================================================*/


BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( core_iterator_type_by
                                         , iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( reverse_core_iterator_type_by
                                         , reverse_iterator )

BOOST_BIMAP_CORE_ITERATOR_TYPE_BY_BUILDER( local_core_iterator_type_by
                                         , local_iterator )


// map_view_iterator

template< class Tag, class BimapCore >
struct map_view_iterator_adaptor {
    typedef iterator_adaptor<
        map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct map_view_iterator : 
    public map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    map_view_iterator() {}
    map_view_iterator(BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    map_view_iterator(map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


template< class Tag, class BimapCore >
struct const_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_map_view_iterator : 
    public const_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_map_view_iterator() {}
    const_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_map_view_iterator(const_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_map_view_iterator(map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// reverse_map_view_iterator

template< class Tag, class BimapCore >
struct reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct reverse_map_view_iterator :
    public reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    reverse_map_view_iterator() {}
    reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    reverse_map_view_iterator(reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_reverse_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            reverse_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_reverse_map_view_iterator :
    public const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_reverse_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    
    public:

    const_reverse_map_view_iterator() {}
    const_reverse_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_reverse_map_view_iterator(const_reverse_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_reverse_map_view_iterator(reverse_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};


// local_map_view_iterator

template< class Tag, class BimapCore >
struct local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct local_map_view_iterator :
    public local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    local_map_view_iterator() {}
    local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    local_map_view_iterator(local_map_view_iterator const & iter)
      : base_(iter.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(
            *const_cast<BOOST_DEDUCED_TYPENAME base_::base_type::value_type*>(
                &(*this->base())
            )
        );
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT
};

template< class Tag, class BimapCore >
struct const_local_map_view_iterator_adaptor {
    typedef iterator_adaptor<
        const_local_map_view_iterator<Tag,BimapCore>,
        BOOST_DEDUCED_TYPENAME 
            local_core_iterator_type_by<Tag,BimapCore>::type,
        const BOOST_DEDUCED_TYPENAME 
            ::boost::bimaps::support::value_type_by<Tag,BimapCore>::type
    > type;
};
template< class Tag, class BimapCore >
struct const_local_map_view_iterator :
    public const_local_map_view_iterator_adaptor<Tag,BimapCore>::type
{
    typedef BOOST_DEDUCED_TYPENAME 
        const_local_map_view_iterator_adaptor<Tag,BimapCore>::type base_;
    public:

    const_local_map_view_iterator() {}
    const_local_map_view_iterator(
            BOOST_DEDUCED_TYPENAME base_::base_type const& iter)
      : base_(iter) {}
    const_local_map_view_iterator(const_local_map_view_iterator const & iter)
      : base_(iter.base()) {}
	const_local_map_view_iterator(local_map_view_iterator<Tag,BimapCore> i)
      : base_(i.base()) {}

    BOOST_DEDUCED_TYPENAME base_::reference dereference() const
    {
        return ::boost::bimaps::relation::support::pair_by<Tag>(*this->base());
    }
    private:
    friend class iterator_core_access;
    BOOST_BIMAP_MAP_VIEW_ITERATOR_SERIALIZATION_SUPPORT


    explicit list_adaptor(Base & c) :
        base_(c) {}


    void splice(Iterator position, list_adaptor & x)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base()
        );
    }


    void splice(Iterator position, list_adaptor & x, Iterator i)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }


    void splice(Iterator position, list_adaptor & x, 
                Iterator first, Iterator last)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }


    void remove(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type
        >::param_type value
    )
    {
        this->base().remove(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(value)
        );
    }


    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( pred, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }


    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }


    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( binary_pred,
               this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }


    void merge(list_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }


    template< class Compare >
    void merge(list_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }


    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }


    template< class Compare >
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }


    void reverse()
    {
        this->base().reverse();
    }


    explicit multiset_adaptor(Base & c) :
        base_(c) {}





    vector_map_adaptor() {}


    explicit vector_map_adaptor(Base & c) :
        base_(c) {}


    explicit sequence_container_adaptor(Base & c)
        : base_(c) {}


    reverse_iterator rbegin()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );

    }


    reverse_iterator rend()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }


    const_reverse_iterator rbegin() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );
    }


    const_reverse_iterator rend() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }


    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }






    void push_front(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_front(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }


    void pop_front()
    {
        this->base().pop_front();
    }


    void push_back(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_back(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }


    void pop_back()
    {
        this->base().pop_back();
    }


    explicit unordered_multiset_adaptor(Base & c) :
        base_(c) {}





    explicit ordered_associative_container_adaptor(Base & c)
        : base_(c) {}


    reverse_iterator rbegin()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );

    }


    reverse_iterator rend()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }


    const_reverse_iterator rbegin() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );
    }


    const_reverse_iterator rend() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }


    key_compare key_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base_;

        return key_compare(
            this->base().key_comp(),
            this->template functor<key_to_base_>()
        );
    }


    value_compare value_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::value_to_base value_to_base_;

        return value_compare(
            this->base().value_comp(),
            this->template functor<value_to_base_>()
        );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator lower_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator lower_bound(const CompatibleKey & k) const
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator upper_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator upper_bound(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }


    bool operator==(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() == c.base() );
    }


    bool operator<(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() < c.base() );
    }


    explicit unordered_multimap_adaptor(Base & c) :
        base_(c) {}





    explicit set_adaptor(Base & c) :
        base_(c) {}


    explicit unordered_associative_container_adaptor(Base & c)
        : base_(c) {}





    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type bucket(
        const CompatibleKey & k) const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base;
        return this->base().bucket(
            this->template functor<key_to_base>()(k)
        );
    }


    local_iterator       begin(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }


    const_local_iterator begin(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }


    local_iterator       end(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }


    const_local_iterator end(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }


    float load_factor() const
    {
        return this->base().load_factor();
    }


    float max_load_factor() const
    {
        return this->base().max_load_factor();
    }


    void max_load_factor(float z)
    {
        return this->base().max_load_factor(z);
    }


    void rehash(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->base().rehash(n);
    }






    explicit unordered_set_adaptor(Base & c) :
        base_(c) {}


    explicit multimap_adaptor(Base & c) :
        base_(c) {}





    explicit unordered_map_adaptor(Base & c) :
        base_(c) {}


    template< class CompatibleKey >
    data_type& operator[](const CompatibleKey & k)
    {
        return this->base()
            [this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)];
    }


    template< class CompatibleKey >
    data_type& at(const CompatibleKey & k)
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }


    template< class CompatibleKey >
    const data_type& at(const CompatibleKey & k) const
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }


    explicit container_adaptor(Base & c) : dwfb(c) {}


    const Base & base() const { return dwfb.data; }

          Base & base()       { return dwfb.data; }


    size_type size() const                    { return base().size();         }

    size_type max_size() const                { return base().max_size();     }

    bool empty() const                        { return base().empty();        }


    iterator begin()
    {
        return this->template functor<iterator_from_base>()( base().begin() );
    }


    iterator end()
    {
        return this->template functor<iterator_from_base>()( base().end() );
    }


    const_iterator begin() const
    {
        return this->template functor<iterator_from_base>()( base().begin() );
    }


    const_iterator end() const
    {
        return this->template functor<iterator_from_base>()( base().end() );
    }



    iterator erase(iterator pos)
    {
        return this->template functor<iterator_from_base>()(
            base().erase(this->template functor<iterator_to_base>()(pos))
        );
    }


    iterator erase(iterator first, iterator last)
    {
        return this->template functor<iterator_from_base>()(
            base().erase(
                this->template functor<iterator_to_base>()(first),
                this->template functor<iterator_to_base>()(last)
            )
        );
    }


    void clear()
    {
        base().clear();
    }


    template< class InputIterator >
    void insert(InputIterator iterBegin, InputIterator iterEnd)
    {
        for( ; iterBegin != iterEnd ; ++iterBegin )
        {
            base().insert( this->template
                functor<value_to_base>()( *iterBegin )
            );
        }
    }


    explicit associative_container_adaptor(Base & c)
        : base_(c) {}


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type erase(const CompatibleKey & k)
    {
        return this->base().erase
        (
            this->template functor<key_to_base>()(k)
        );
    }




    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type count(const CompatibleKey & k) const
    {
        return this->base().count(
            this->template functor<key_to_base>()(k)
        );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator find(const CompatibleKey & k)
    {
        return this->template functor<typename base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }


    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator
        find(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }


    vector_adaptor() {}


    explicit vector_adaptor(Base & c) :
        base_(c) {}



    void reserve(BOOST_DEDUCED_TYPENAME base_::size_type m)
    {
        this->base().resize(m);
    }


    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }






    explicit map_adaptor(Base & c) :
        base_(c) {}


    template< class CompatibleKey >
    data_type& operator[](const CompatibleKey & k)
    {
        return this->base()
            [this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)];
    }


    template< class CompatibleKey >
    data_type& at(const CompatibleKey & k)
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }


    template< class CompatibleKey >
    const data_type& at(const CompatibleKey & k) const
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }


    explicit list_map_adaptor(Base & c) :
        base_(c) {}


    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( pred, this->template functor<key_from_base_value>() )
        );
    }


    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::equal_to<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }


    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( binary_pred, this->template functor<key_from_base_value>() )
        );
    }


    void merge(list_map_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }


    template< class Compare >
    void merge(list_map_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }


    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }


    template< class Compare >
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

    comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}


    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x,
                     BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type y) const
    {
        return compare( converter(x), converter(y) );
    }

    compatible_comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}


    template< class CompatibleTypeLeft, class CompatibleTypeRight >
    bool operator()( const CompatibleTypeLeft  & x,
                     const CompatibleTypeRight & y) const
    {
        return compare( converter(x), converter(y) );
    }

    unary_check_adaptor( const Compare & comp, const Converter & conv ) :
        compare(comp), converter(conv) {}


    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x) const
    {
        return compare( converter(x) );
    }

    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }


    BaseConstIterator operator()(ConstIterator iter) const
    {
        return BaseConstIterator(iter);
    }

    BaseIterator operator()(Iterator iter) const
    {
        return BaseIterator(iter);
    }

    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }

    ConstIterator operator()(BaseConstIterator iter) const
    {
        return ConstIterator(iter);
    }

    Iterator operator()(BaseIterator iter) const
    {
        return Iterator(iter);
    }

    BaseValue operator()(const Value & val) const
    {
        return BaseValue(val);
    }

    const Value & operator()(const Value & val) const
    {
        return val;
    }

    Value operator()(const BaseValue & val) const
    {
        return Value(val);
    }

    Value & operator()(Value & val) const
    {
        return val;
    }


    const Value & operator()(const Value & val) const
    {
        return val;
    }

    BaseKey operator()(const Key & k) const
    {
        return BaseKey(k);
    }


    template< class CompatibleKey >
    const CompatibleKey & operator()(const CompatibleKey & k) const
    {
        return k;
    }


    data_with_functor_bag() {}


    data_with_functor_bag(BOOST_DEDUCED_TYPENAME add_reference<Data>::type d)
        : data(d) {}


    template< class Functor >
    Functor& functor()
    {
        return *(static_cast<Functor*>(this));
    }


    template< class Functor >
    const Functor& functor() const
    {
        return *(static_cast<Functor const *>(this));
    }

    bool operator()( const T & p ) { return p.first; }





    map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}



    map_view & operator=(const map_view & v) 
    {
        this->base() = v.base();
        return *this;
    }


    template< class CompatibleKey >
    const info_type & info_at(const CompatibleKey& k) const
    {
        BOOST_DEDUCED_TYPENAME base_::const_iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }


    template< class CompatibleKey >
    info_type & info_at(const CompatibleKey& k)
    {
        BOOST_DEDUCED_TYPENAME base_::iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }


    list_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}


    list_set_view & operator=(const list_set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }



    list_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}


    list_map_view & operator=(const list_map_view & v)
    {
        this->base() = v.base(); 
        return *this;
    }








    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator i)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }


    void relocate(BOOST_DEDUCED_TYPENAME base_::iterator position,
                  BOOST_DEDUCED_TYPENAME base_::iterator first,
                  BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        this->base().relocate(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }


    vector_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}


    vector_map_view & operator=(const vector_map_view & v)
    {
        this->base() = v.base();
        return *this;
    }


    unordered_map_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}


    unordered_map_view & operator=(const unordered_map_view & v) 
    {
        this->base() = v.base();
        return *this;
    }


    template< class CompatibleKey >
    const info_type & info_at(const CompatibleKey& k) const
    {
        BOOST_DEDUCED_TYPENAME base_::const_iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }


    template< class CompatibleKey >
    info_type & info_at(const CompatibleKey& k)
    {
        BOOST_DEDUCED_TYPENAME base_::iterator iter = this->find(k);
        if( iter == this->end() )
        {
            ::boost::throw_exception(
                std::out_of_range("bimap<>: invalid key")
            );
        }
        return iter->info;
    }

    template< class T >
    unconstrained_map_view(const T &) {}

    template< class T >
    unconstrained_set_view(const T &) {}


    vector_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) :
        base_(c) {}


    vector_set_view & operator=(const vector_set_view & v)
    {
        this->base() = v.base();
        return *this;
    }


    multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}


    multiset_view & operator=(const multiset_view & v) 
    {
        this->base() = v.base(); return *this;
    }



    multimap_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}



    multimap_view & operator=(const multimap_view & v) 
    {
        this->base() = v.base();
        return *this;
    }



    unordered_multiset_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}



    set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c) : base_(c) {}


    set_view & operator=(const set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }


    unordered_set_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}


    unordered_set_view & operator=(const unordered_set_view & v) 
    {
        this->base() = v.base();
        return *this;
    }


    unordered_multimap_view(BOOST_DEDUCED_TYPENAME base_::base_type & c)
        : base_(c) {}


























    normal_storage() {}


    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return first;  }


    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return second; }


    mirror_storage() {}


    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return second; }


    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return first;  }


    pair_info_hook() {}


    pair_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type
                    >::param_type f,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type
                    >::param_type s,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        info_type
                    >::param_type i = info_type() )
        : base_(f,s), info(i) {}


    template< class Pair >
    pair_info_hook( const Pair & p) :
        base_(p.first,p.second),
        info(p.info) {}


    template< class Pair >
    void change_to( const Pair & p )
    {
        base_::first  = p.first ;
        base_::second = p.second;
        info          = p.info  ;
    }


    void clear_info()
    {
        info = info_type();
    };


    pair_info_hook() {}


    pair_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type
                    >::param_type f,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type
                    >::param_type s)

        : base_(f,s) {}


    template< class Pair >
    pair_info_hook( const Pair & p ) :
        base_(p.first,p.second) {}


    template< class Pair >
    void change_to( const Pair & p )
    {
        base_::first  = p.first ;
        base_::second = p.second;
    }


    void clear_info() {};


    structured_pair() {}


    structured_pair(BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type  >::param_type f,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type >::param_type s)
        : base_(f,s) {}


    structured_pair(BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::first_type  >::param_type f,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::second_type >::param_type s,
                    BOOST_DEDUCED_TYPENAME boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::info_type   >::param_type i)
        : base_(f,s,i) {}


    template< class OtherLayout >
    structured_pair(
        const structured_pair<FirstType,SecondType,Info,OtherLayout> & p)
        : base_(p) {}


    template< class OtherLayout >
    structured_pair& operator=(
        const structured_pair<FirstType,SecondType,OtherLayout> & p)
    {
        base_::change_to(p);
        return *this;
    }


    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const structured_pair>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }


    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,structured_pair>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator==(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  == b.first  ) &&
             ( a.second == b.second ) );
}


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator!=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ! ( a == b );
}


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator<(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
               const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second < b.second )));
}


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator<=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return (  ( a.first  <  b.first  ) ||
             (( a.first == b.first ) && ( a.second <= b.second )));
}


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator>(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
               const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second > b.second )));
}


template< class FirstType, class SecondType, class Info, class Layout1, class Layout2 >
bool operator>=(const structured_pair<FirstType,SecondType,Info,Layout1> & a,
                const structured_pair<FirstType,SecondType,Info,Layout2> & b)
{
    return ( ( a.first  >  b.first  ) ||
             (( a.first == b.first ) && ( a.second >= b.second )));
}


template< class FirstType, class SecondType, class Info, class Layout>
structured_pair<FirstType,SecondType,Info,Layout> 
    copy_with_first_replaced(structured_pair<FirstType,SecondType,Info,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,Info,Layout>::first_type>
                ::param_type f)
{
    return structured_pair<FirstType,SecondType,Info,Layout>(f,p.second,p.info);
}

    
template< class FirstType, class SecondType, class Layout>
structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> 
    copy_with_first_replaced(structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>::first_type>
                ::param_type f)
{
    return structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>(f,p.second);
}

    
template< class FirstType, class SecondType, class Info, class Layout>
structured_pair<FirstType,SecondType,Info,Layout> 
    copy_with_second_replaced(structured_pair<FirstType,SecondType,Info,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,Info,Layout>::second_type>
                ::param_type s)
{
    return structured_pair<FirstType,SecondType,Info,Layout>(p.first,s,p.info);
}

    
template< class FirstType, class SecondType, class Layout>
structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> 
    copy_with_second_replaced(structured_pair<FirstType,SecondType,::boost::mpl::na,Layout> const& p,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>::second_type>
                ::param_type s)
{
    return structured_pair<FirstType,SecondType,::boost::mpl::na,Layout>(p.first,s);
}


    relation_storage() {}


    relation_storage(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                         BOOST_DEDUCED_TYPENAME base_::left_value_type
                     >::param_type l,
                     BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                     >::param_type r)

        : left(l), right(r) {}


    const BOOST_DEDUCED_TYPENAME base_:: left_value_type &  get_left()const { return left;  }


    const BOOST_DEDUCED_TYPENAME base_::right_value_type & get_right()const { return right; }


    relation_info_hook() {}


    relation_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                           BOOST_DEDUCED_TYPENAME base_::left_value_type
                        >::param_type l,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            BOOST_DEDUCED_TYPENAME base_::right_value_type
                        >::param_type r,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            info_type
                        >::param_type i = info_type() )

        : base_(l,r), info(i) {}


    template< class Relation >
    relation_info_hook( const Relation & rel ) :
        base_(rel.left,rel.right),
        info(rel.info) {}


    template< class Relation >
    void change_to( const Relation & rel )
    {
        base_::left  = rel.left ;
        base_::right = rel.right;
        info         = rel.info ;
    }

    template< class Archive >
    void serialize(Archive & ar, const unsigned int)
    {
        ar & ::boost::serialization::make_nvp("left" , base_::left );
        ar & ::boost::serialization::make_nvp("right", base_::right);
        ar & ::boost::serialization::make_nvp("info" , info        );
    }


    relation_info_hook() {}


    relation_info_hook( BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                           BOOST_DEDUCED_TYPENAME base_::left_value_type
                        >::param_type l,
                        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                            BOOST_DEDUCED_TYPENAME base_::right_value_type
                        >::param_type r)

        : base_(l,r) {}


    template< class Relation >
    relation_info_hook( const Relation & rel ) :
        base_(rel.left,rel.right) {}


    template< class Relation >
    void change_to( const Relation & rel )
    {
        base_::left  = rel.left ;
        base_::right = rel.right;
    }

    template< class Archive >
    void serialize(Archive & ar, const unsigned int)
    {
        ar & ::boost::serialization::make_nvp("left" , base_::left );
        ar & ::boost::serialization::make_nvp("right", base_::right);
    }


    mutant_relation() {}


    mutant_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_:: left_value_type
                    >::param_type l,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                    >::param_type r) :
        base_(l,r) {}


    mutant_relation(BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_:: left_value_type
                    >::param_type l,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::right_value_type
                    >::param_type r,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                        BOOST_DEDUCED_TYPENAME base_::info_type
                    >::param_type i) :
        base_(l,r,i) {}


    mutant_relation(const mutant_relation<TA,TB,Info,false> & rel) :
        base_(rel) {}


    mutant_relation(const mutant_relation<TA,TB,Info,true> & rel) :
        base_(rel) {}


    template< bool FM >
    mutant_relation& operator=(const mutant_relation<TA,TB,Info,FM> & rel)
    {
        base_::change_to(rel);
        return *this;
    }


    left_pair & get_left_pair()
    {
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }


    const left_pair & get_left_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<left_pair>(*this);
    }


    right_pair & get_right_pair()
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }


    const right_pair & get_right_pair() const
    {
        return ::boost::bimaps::relation::detail::mutate<right_pair>(*this);
    }


    above_view & get_view()
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }


    const above_view & get_view() const
    {
        return ::boost::bimaps::relation::detail::mutate<above_view>(*this);
    }


    template< class Tag >
    const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,const mutant_relation>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag)) const
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }


    template< class Tag >
    BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
        result_of::get<Tag,mutant_relation>::type
    get(BOOST_EXPLICIT_TEMPLATE_TYPE(Tag))
    {
        return ::boost::bimaps::relation::support::get<Tag>(*this);
    }


    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        base_::serialize(ar,version);
    }


template< class FirstType, class SecondType, bool FM >
std::size_t hash_value(const detail::relation_storage<FirstType,SecondType,FM> & r)
{
    std::size_t seed = 0;
    ::boost::hash_combine(seed, r. left );
    ::boost::hash_combine(seed, r.right );

    return seed;
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator==(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  == b.left  ) &&
             ( a.right == b.right ) );
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator!=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ! ( a == b );
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<(const detail::relation_storage<FirstType,SecondType,FM1> & a,
               const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right < b.right )));
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator<=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return (  ( a.left  <  b.left  ) ||
             (( a.left == b.left ) && ( a.right <= b.right )));
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>(const detail::relation_storage<FirstType,SecondType,FM1> & a,
               const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right > b.right )));
}


template< class FirstType, class SecondType, bool FM1, bool FM2 >
bool operator>=(const detail::relation_storage<FirstType,SecondType,FM1> & a,
                const detail::relation_storage<FirstType,SecondType,FM2> & b)
{
    return ( ( a.left  >  b.left  ) ||
             (( a.left == b.left ) && ( a.right >= b.right )));
}


template< class TA, class TB, class Info, bool force_mutable>
mutant_relation<TA,TB,Info,force_mutable> 
    copy_with_left_replaced(mutant_relation<TA,TB,Info,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,Info,force_mutable>::left_value_type>
                ::param_type l)
{
    return mutant_relation<TA,TB,Info,force_mutable>(l,rel.right,rel.info);
}

    
template< class TA, class TB, bool force_mutable>
mutant_relation<TA,TB,::boost::mpl::na,force_mutable>
    copy_with_left_replaced(mutant_relation<TA,TB,::boost::mpl::na,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,::boost::mpl::na,force_mutable>::left_value_type>
                ::param_type l)
{
    return mutant_relation<TA,TB,::boost::mpl::na,force_mutable>(l,rel.right);  
}

    
template< class TA, class TB, class Info, bool force_mutable>
mutant_relation<TA,TB,Info,force_mutable> 
    copy_with_right_replaced(mutant_relation<TA,TB,Info,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,Info,force_mutable>::right_value_type>
                ::param_type r)
{
    return mutant_relation<TA,TB,Info,force_mutable>(rel.left,r,rel.info);
}

    
template< class TA, class TB, bool force_mutable>
mutant_relation<TA,TB,::boost::mpl::na,force_mutable>
    copy_with_right_replaced(mutant_relation<TA,TB,::boost::mpl::na,force_mutable> const& rel,
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< BOOST_DEDUCED_TYPENAME 
            mutant_relation<TA,TB,::boost::mpl::na,force_mutable>::right_value_type>
                ::param_type r)
{
    return mutant_relation<TA,TB,::boost::mpl::na,force_mutable>(rel.left,r);  
}



template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< mpl::not_< is_const< Type > >,

View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View>
    ));
    return *reinterpret_cast< View* >(boost::addressof(m));
}


template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< is_const< Type >,

const View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View> 
    ));
    return *reinterpret_cast< const View* >(boost::addressof(m));
}

    const Relation
        operator()(const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                            pair_type_by<Tag,Relation>::type & p) const
    {
        return Relation(p);
    }


    Relation &
        operator()( BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
            pair_type_by<Tag,Relation>::type & p ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(p);
    }

    const Relation
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return Relation(r);
    }


    Relation &
    operator()( BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }


    const Relation &
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }













template< class SymmetricType >
BOOST_DEDUCED_TYPENAME result_of::get<
    ::boost::bimaps::relation::member_at::info, SymmetricType >::type
get(::boost::bimaps::relation::member_at::info, SymmetricType & rel)
{
    return rel.info;
}









     const result_type & operator()(const Relation & rel) const
    {
        return rel;
    }


    result_type & operator()( Relation & rel) const
    {
        return rel;
    }





    const BOOST_DEDUCED_TYPENAME Relation::above_view &
    operator()( const Relation & r ) const
    {
        return r.get_view();
    }
