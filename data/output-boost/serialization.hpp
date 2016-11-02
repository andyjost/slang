
    static const basic_pointer_iserializer &
    enable_load(mpl::true_){
        return boost::serialization::singleton<
            pointer_iserializer<Archive, Serializable> 
        >::get_const_instance();
    }


    static const basic_pointer_oserializer &
    enable_save(mpl::true_){
        return boost::serialization::singleton<
            pointer_oserializer<Archive, Serializable> 
        >::get_const_instance();
    }


template<class Archive, class T>
void save(
    Archive & ar, 
    const boost::optional< T > & t, 
    const unsigned int /*version*/
){
    const bool tflag = t.is_initialized();
    ar << boost::serialization::make_nvp("initialized", tflag);
    if (tflag){
        const boost::serialization::item_version_type item_version(version< T >::value);
        #if 0
        const boost::archive::library_version_type library_version(
            ar.get_library_version()
        };
        if(boost::archive::library_version_type(3) < library_version){
            ar << BOOST_SERIALIZATION_NVP(item_version);
        }
        #else
            ar << BOOST_SERIALIZATION_NVP(item_version);
        #endif
        ar << boost::serialization::make_nvp("value", *t);
    }
}


template<class Archive, class T>
void load(
    Archive & ar, 
    boost::optional< T > & t, 
    const unsigned int /*version*/
){
    bool tflag;
    ar >> boost::serialization::make_nvp("initialized", tflag);
    if (tflag){
        boost::serialization::item_version_type item_version(0);
        boost::archive::library_version_type library_version(
            ar.get_library_version()
        );
        if(boost::archive::library_version_type(3) < library_version){
            // item_version is handled as an attribute so it doesnt need an NVP
           ar >> BOOST_SERIALIZATION_NVP(item_version);
        }
        detail::stack_construct<Archive, T> aux(ar, item_version);
        ar >> boost::serialization::make_nvp("value", aux.reference());
        t.reset(aux.reference());
    }
    else {
        t.reset();
    }
}


template<class Archive, class T>
void serialize(
    Archive & ar, 
    boost::optional< T > & t, 
    const unsigned int version
){
    boost::serialization::split_free(ar, t, version);
}

    variant_save_visitor(Archive& ar) :
        m_ar(ar)
    {}

    template<class T>
    void operator()(T const & value) const
    {
        m_ar << BOOST_SERIALIZATION_NVP(value);
    }


template<class Archive, BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
void save(
    Archive & ar,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const & v,
    unsigned int /*version*/
){
    int which = v.which();
    ar << BOOST_SERIALIZATION_NVP(which);
    typedef BOOST_DEDUCED_TYPENAME  boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types types;
    variant_save_visitor<Archive> visitor(ar);
    v.apply_visitor(visitor);
}

        template<class Archive, class V>
        static void invoke(
            Archive & /*ar*/,
            int /*which*/,
            V & /*v*/,
            const unsigned int /*version*/
        ){}

        template<class Archive, class V>
        static void invoke(
            Archive & ar,
            int which,
            V & v,
            const unsigned int version
        ){
            if(which == 0){
                // note: A non-intrusive implementation (such as this one)
                // necessary has to copy the value.  This wouldn't be necessary
                // with an implementation that de-serialized to the address of the
                // aligned storage included in the variant.
                typedef BOOST_DEDUCED_TYPENAME mpl::front<S>::type head_type;
                head_type value;
                ar >> BOOST_SERIALIZATION_NVP(value);
                v = value;
                ar.reset_object_address(& boost::get<head_type>(v), & value);
                return;
            }
            typedef BOOST_DEDUCED_TYPENAME mpl::pop_front<S>::type type;
            variant_impl<type>::load(ar, which - 1, v, version);
        }


    template<class Archive, class V>
    static void load(
        Archive & ar,
        int which,
        V & v,
        const unsigned int version
    ){
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<mpl::empty<S>,
            mpl::identity<load_null>,
            mpl::identity<load_impl>
        >::type typex;
        typex::invoke(ar, which, v, version);
    }


template<class Archive, BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
void load(
    Archive & ar, 
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& v,
    const unsigned int version
){
    int which;
    typedef BOOST_DEDUCED_TYPENAME boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types types;
    ar >> BOOST_SERIALIZATION_NVP(which);
    if(which >=  mpl::size<types>::value)
        // this might happen if a type was removed from the list of variant types
        boost::serialization::throw_exception(
            boost::archive::archive_exception(
                boost::archive::archive_exception::unsupported_version
            )
        );
    variant_impl<types>::load(ar, which, v, version);
}


template<class Archive,BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
inline void serialize(
    Archive & ar,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> & v,
    const unsigned int file_version
){
    split_free(ar,v,file_version);
}


template<class T, enum tracking_type L>
inline bool operator>=(tracking_level< T > t, enum tracking_type l)
{
    return t.value >= (int)l;
}


template<class E> inline void throw_exception(E const & e){
    throw e;
}

    
    template<class Archive, class T>
    void save(
        Archive & ar, 
        const boost::scoped_ptr< T > & t, 
        const unsigned int /* version */
    ){
        T* r = t.get();
        ar << boost::serialization::make_nvp("scoped_ptr", r);
    }


    template<class Archive, class T>
    void load(
        Archive & ar, 
        boost::scoped_ptr< T > & t, 
        const unsigned int /* version */
    ){
        T* r;
        ar >> boost::serialization::make_nvp("scoped_ptr", r);
        t.reset(r); 
    }


    template<class Archive, class T>
    void serialize(
        Archive& ar, 
        boost::scoped_ptr< T >& t, 
        const unsigned int version
    ){
        boost::serialization::split_free(ar, t, version);
    }

template<class Archive, class F, class S>
inline void serialize(
    Archive & ar,
    std::pair<F, S> & p,
    const unsigned int /* file_version */
){
    // note: we remove any const-ness on the first argument.  The reason is that 
    // for stl maps, the type saved is pair<const key, T).  We remove
    // the const-ness in order to be able to load it.
    typedef BOOST_DEDUCED_TYPENAME boost::remove_const<F>::type typef;
    ar & boost::serialization::make_nvp("first", const_cast<typef &>(p.first));
    ar & boost::serialization::make_nvp("second", p.second);
}

            static void const * invoke(){
                Base const * const b = 0;
                Derived const * const d = 0;
                return & void_cast_register(d, b);
            }

            static void const * invoke(){
                return 0;
            }

        static void const * invoke(){
            typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
                is_polymorphic<Base>,
                mpl::identity<polymorphic>,
                mpl::identity<non_polymorphic>
            >::type type;
            return type::invoke();
        }
 & 
base_object(Derived &d)
{
    BOOST_STATIC_ASSERT(( is_base_and_derived<Base,Derived>::value));
    BOOST_STATIC_ASSERT(! is_pointer<Derived>::value);
    typedef BOOST_DEDUCED_TYPENAME detail::base_cast<Base, Derived>::type type;
    detail::base_register<type, Derived>::invoke();
    return access::cast_reference<type, Derived>(d);
}

    explicit ephemeral_object(T& t) :
        val(t)
    {}


    T & value() const {
        return val;
    }


    const T & const_value() const {
        return val;
    }


    template<class Archive>
    void serialize(Archive &ar, const unsigned int) const
    {
       ar & val;
    }


template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
ephemeral_object<T> ephemeral(const char * name, T & t){
    return ephemeral_object<T>(name, t);
}

    void operator()(void const *) const {}


template<class Archive, class P, class D>
inline void serialize(
    Archive & /* ar */,
    boost_132::detail::sp_counted_base_impl<P, D> & /* t */,
    const unsigned int /*file_version*/
){
    // register the relationship between each derived class
    // its polymorphic base
    boost::serialization::void_cast_register<
        boost_132::detail::sp_counted_base_impl<P, D>,
        boost_132::detail::sp_counted_base 
    >(
        static_cast<boost_132::detail::sp_counted_base_impl<P, D> *>(NULL),
        static_cast<boost_132::detail::sp_counted_base *>(NULL)
    );
}


template<class Archive, class P, class D>
inline void save_construct_data(
    Archive & ar,
    const 
    boost_132::detail::sp_counted_base_impl<P, D> *t, 
    const BOOST_PFTO unsigned int /* file_version */
){
    // variables used for construction
    ar << boost::serialization::make_nvp("ptr", t->ptr);
}


template<class Archive, class P, class D>
inline void load_construct_data(
    Archive & ar,
    boost_132::detail::sp_counted_base_impl<P, D> * t, 
    const unsigned int /* file_version */
){
    P ptr_;
    ar >> boost::serialization::make_nvp("ptr", ptr_);
    // ::new(t)boost_132::detail::sp_counted_base_impl<P, D>(ptr_,  D()); 
    // placement
    // note: the original ::new... above is replaced by the one here.  This one
    // creates all new objects with a null_deleter so that after the archive
    // is finished loading and the shared_ptrs are destroyed - the underlying
    // raw pointers are NOT deleted.  This is necessary as they are used by the 
    // new system as well.
    ::new(t)boost_132::detail::sp_counted_base_impl<
        P, 
        boost_132::serialization::detail::null_deleter
    >(
        ptr_,  boost_132::serialization::detail::null_deleter()
    ); // placement new
    // compensate for that fact that a new shared count always is 
    // initialized with one. the add_ref_copy below will increment it
    // every time its serialized so without this adjustment
    // the use and weak counts will be off by one.
    t->use_count_ = 0;
}


template<class Archive>
inline void save(
    Archive & ar,
    const boost_132::detail::shared_count &t,
    const unsigned int /* file_version */
){
    ar << boost::serialization::make_nvp("pi", t.pi_);
}


template<class Archive>
inline void load(
    Archive & ar,
    boost_132::detail::shared_count &t,
    const unsigned int /* file_version */
){
    ar >> boost::serialization::make_nvp("pi", t.pi_);
    if(NULL != t.pi_)
        t.pi_->add_ref_copy();
}

template<class T, int N>
T * factory(std::va_list){
    BOOST_ASSERT(false);
    // throw exception here?
    return NULL;
}


template<class Archive, class Container>
inline void save_hash_collection(Archive & ar, const Container &s)
{
    collection_size_type count(s.size());
    const collection_size_type bucket_count(s.bucket_count());
    const item_version_type item_version(
        version<BOOST_DEDUCED_TYPENAME Container::value_type>::value
    );

    #if 0
    /* should only be necessary to create archives of previous versions
     * which is not currently supported.  So for now comment this out
     */
    boost::archive::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    if(boost::archive::library_version_type(6) != library_version){
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << BOOST_SERIALIZATION_NVP(bucket_count);
    }
    else{
        // note: fixup for error in version 6.  collection size was
        // changed to size_t BUT for hashed collections it was implemented
        // as an unsigned int.  This should be a problem only on win64 machines
        // but I'll leave it for everyone just in case.
        const unsigned int c = count;
        const unsigned int bc = bucket_count;
        ar << BOOST_SERIALIZATION_NVP(c);
        ar << BOOST_SERIALIZATION_NVP(bc);
    }
    if(boost::archive::library_version_type(3) < library_version){
        // record number of elements
        // make sure the target type is registered so we can retrieve
        // the version when we load
        ar << BOOST_SERIALIZATION_NVP(item_version);
    }
    #else
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << BOOST_SERIALIZATION_NVP(bucket_count);
        ar << BOOST_SERIALIZATION_NVP(item_version);
    #endif

    BOOST_DEDUCED_TYPENAME Container::const_iterator it = s.begin();
    while(count-- > 0){
        // note borland emits a no-op without the explicit namespace
        boost::serialization::save_construct_data_adl(
            ar, 
            &(*it), 
            boost::serialization::version<
                BOOST_DEDUCED_TYPENAME Container::value_type
            >::value
        );
        ar << boost::serialization::make_nvp("item", *it++);
    }
}


template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::deque<U, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, std::deque<U, Allocator> 
    >(ar, t);
}


template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::deque<U, Allocator> &t,
    const unsigned int /*file_version*/
){
    boost::serialization::stl::load_collection<
        Archive,
        std::deque<U, Allocator>,
        boost::serialization::stl::archive_input_seq<
        Archive, std::deque<U, Allocator> 
        >,
        boost::serialization::stl::no_reserve_imp<std::deque<U, Allocator> >
    >(ar, t);
}

template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::deque<U, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

    static void invoke(
        Archive & ar, 
        const  T & t, 
        const unsigned int file_version
    ){
        // use function overload (version_type) to workaround
        // two-phase lookup issue
        const version_type v(file_version);
        save(ar, t, v);
    }

    static void invoke(
        Archive & ar, 
        T & t, 
        const unsigned int file_version
    ){
        // use function overload (version_type) to workaround
        // two-phase lookup issue
        const version_type v(file_version);
        load(ar, t, v);
    }


template<class Archive, class T>
inline void split_free(
    Archive & ar, 
    T & t, 
    const unsigned int file_version
){
    typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
        BOOST_DEDUCED_TYPENAME Archive::is_saving,
        mpl::identity</* detail:: */ free_saver<Archive, T> >, 
        mpl::identity</* detail:: */ free_loader<Archive, T> >
    >::type typex;
    typex::invoke(ar, t, file_version);
}


template<class Archive, class T>
inline void serialize(
    Archive & ar,
    std::complex< T > & t,
    const unsigned int file_version 
){
    boost::serialization::split_free(ar, t, file_version);
}


template<class Archive, class T>
inline void save(
    Archive & ar,
    std::complex< T > const & t,
    const unsigned int /* file_version */
){
    const T re = t.real();
    const T im = t.imag();
    ar << boost::serialization::make_nvp("real", re);
    ar << boost::serialization::make_nvp("imag", im);
}


template<class Archive, class T>
inline void load(
    Archive & ar,
    std::complex< T >& t,
    const unsigned int /* file_version */ 
){
    T re;
    T im;
    ar >> boost::serialization::make_nvp("real", re);
    ar >> boost::serialization::make_nvp("imag", im);
    t = std::complex< T >(re,im);
}

    item_version_type(): t(0) {};

    explicit item_version_type(const unsigned int t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }

    item_version_type(const item_version_type & t_) : 
        t(t_.t)
    {}

    item_version_type & operator=(item_version_type rhs){
        t = rhs.t; 
        return *this;
    }

    operator base_type () const {
        return t;
    }

    operator base_type & () {
        return t;
    }

    bool operator==(const item_version_type & rhs) const {
        return t == rhs.t;
    }
 
    bool operator<(const item_version_type & rhs) const {
        return t < rhs.t;
    }


template<class T, BOOST_MPL_AUX_NTTP_DECL(int, L) >
inline bool operator>=(implementation_level< T > t, enum level_type l)
{
    return t.value >= (int)l;
}

        static inline const char * call()
        {
            return NULL;
        }


template<class T>
inline const char * guid(){
    return ext::guid_impl<T>::call();
}


inline void *
void_upcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void * const t 
){
    return const_cast<void*>(void_upcast(
        derived, 
        base, 
        const_cast<void const *>(t)
    ));
}


inline void *
void_downcast(
    extended_type_info const & derived,
    extended_type_info const & base,
    void * const t 
){
    return const_cast<void*>(void_downcast(
        derived, 
        base, 
        const_cast<void const *>(t)
    ));
}

    virtual void const * downcast(void const * const t) const {
        const Derived * d = 
            boost::serialization::smart_cast<const Derived *, const Base *>(
                static_cast<const Base *>(t)
            );
        return d;
    }

    virtual void const * upcast(void const * const t) const {
        const Base * b = 
            boost::serialization::smart_cast<const Base *, const Derived *>(
                static_cast<const Derived *>(t)
            );
        return b;
    }

    virtual bool has_virtual_base() const {
        return false;
    }


template <class Derived, class Base>
void_caster_primitive<Derived, Base>::void_caster_primitive() :
    void_caster( 
        & type_info_implementation<Derived>::type::get_const_instance(), 
        & type_info_implementation<Base>::type::get_const_instance(),
        // note:I wanted to display from 0 here, but at least one compiler
        // treated 0 by not shifting it at all.
        reinterpret_cast<std::ptrdiff_t>(
            static_cast<Derived *>(
                reinterpret_cast<Base *>(1)
            )
        ) - 1
    )
{
    recursive_register();
}


template <class Derived, class Base>
void_caster_primitive<Derived, Base>::~void_caster_primitive(){
    recursive_unregister();
}

    virtual bool has_virtual_base() const {
        return true;
    }

    virtual void const * downcast(void const * const t) const {
        const Derived * d = 
            dynamic_cast<const Derived *>(
                static_cast<const Base *>(t)
            );
        return d;
    }

    virtual void const * upcast(void const * const t) const {
        const Base * b = 
            dynamic_cast<const Base *>(
                static_cast<const Derived *>(t)
            );
        return b;
    }


template <class Derived, class Base>
void_caster_virtual_base<Derived,Base>::void_caster_virtual_base() :
    void_caster( 
        & (type_info_implementation<Derived>::type::get_const_instance()), 
        & (type_info_implementation<Base>::type::get_const_instance())
    )
{
    recursive_register(true);
}


template <class Derived, class Base>
void_caster_virtual_base<Derived,Base>::~void_caster_virtual_base(){
    recursive_unregister();
}

    template<class Archive, class T>
    static void member_save(
        Archive & ar, 
        //const T & t,
        T & t,
        const unsigned int file_version
    ){
        t.save(ar, file_version);
    }

    template<class Archive, class T>
    static void member_load(
        Archive & ar, 
        T & t,
        const unsigned int file_version
    ){
        t.load(ar, file_version);
    }

    template<class Archive, class T>
    static void serialize(
        Archive & ar, 
        T & t, 
        const unsigned int file_version
    ){
        // note: if you get a compile time error here with a
        // message something like:
        // cannot convert parameter 1 from <file type 1> to <file type 2 &>
        // a likely possible cause is that the class T contains a 
        // serialize function - but that serialize function isn't 
        // a template and corresponds to a file type different than
        // the class Archive.  To resolve this, don't include an
        // archive type other than that for which the serialization
        // function is defined!!!
        t.serialize(ar, file_version);
    }

    template<class T>
    static void destroy( const T * t) // const appropriate here?
    {
        // the const business is an MSVC 6.0 hack that should be
        // benign on everything else
        delete const_cast<T *>(t);
    }

    template<class T>
    static void construct(T * t){
        // default is inplace invocation of default constructor
        // Note the :: before the placement new. Required if the
        // class doesn't have a class-specific placement new defined.
        ::new(t)T;
    }

    template<class T, class U>
    static T & cast_reference(U & u){
        return static_cast<T &>(u);
    }

    template<class T, class U>
    static T * cast_pointer(U * u){
        return static_cast<T *>(u);
    }

template<class Archive, class Container, class InputFunction>
inline void load_hash_collection(Archive & ar, Container &s)
{
    s.clear();
    collection_size_type count;
    collection_size_type bucket_count;
    boost::serialization::item_version_type item_version(0);
    boost::archive::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    if(boost::archive::library_version_type(6) != library_version){
        ar >> BOOST_SERIALIZATION_NVP(count);
        ar >> BOOST_SERIALIZATION_NVP(bucket_count);
    }
    else{
        // note: fixup for error in version 6.  collection size was
        // changed to size_t BUT for hashed collections it was implemented
        // as an unsigned int.  This should be a problem only on win64 machines
        // but I'll leave it for everyone just in case.
        unsigned int c;
        unsigned int bc;
        ar >> BOOST_SERIALIZATION_NVP(c);
        count = c;
        ar >> BOOST_SERIALIZATION_NVP(bc);
        bucket_count = bc;
    }
    if(boost::archive::library_version_type(3) < library_version){
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    #if ! defined(__MWERKS__)
    s.resize(bucket_count);
    #endif
    InputFunction ifunc;
    while(count-- > 0){
        ifunc(ar, s, item_version);
    }
}


template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::list<U, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, 
        std::list<U, Allocator> 
    >(ar, t);
}


template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::list<U, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::load_collection<
        Archive,
        std::list<U, Allocator>,
        boost::serialization::stl::archive_input_seq<
            Archive, 
            std::list<U, Allocator> 
        >,
        boost::serialization::stl::no_reserve_imp<std::list<U, Allocator> >
    >(ar, t);
}

template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::list<U, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

    template<class Archive>
    void save(Archive & ar, const unsigned int /* file_version */) const {
        ar.save_binary(m_t, m_size);
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int /* file_version */) const {
        ar.load_binary(const_cast<void *>(m_t), m_size);
    }

inline 
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
binary_object 
make_binary_object(/* const */ void * t, std::size_t size){
    return binary_object(t, size);
}

    
    array(value_type* t, std::size_t s) :
        m_t(t),
        m_element_count(s)
    {}

    array(const array & rhs) :
        m_t(rhs.m_t),
        m_element_count(rhs.m_element_count)
    {}

    array & operator=(const array & rhs){
        m_t = rhs.m_t;
        m_element_count = rhs.m_element_count;
    }

    template<class Archive>
    void serialize_optimized(Archive &ar, const unsigned int, mpl::false_ ) const
    {
      // default implemention does the loop
      std::size_t c = count();
      value_type * t = address();
      while(0 < c--)
            ar & boost::serialization::make_nvp("item", *t++);
    }

    template<class Archive>
    void save(Archive &ar, const unsigned int version) const
    {
      ar.save_array(*this,version);
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version)
    {
      ar.load_array(*this,version);
    }

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      typedef BOOST_DEDUCED_TYPENAME 
          boost::serialization::use_array_optimization<Archive>::template apply<
                    BOOST_DEDUCED_TYPENAME remove_const< T >::type 
                >::type use_optimized;
      serialize_optimized(ar,version,use_optimized());
    }

    
    value_type* address() const
    {
      return m_t;
    }


    std::size_t count() const
    {
      return m_element_count;
    }


template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
array< T > make_array( T* t, std::size_t s){
    return array< T >(t, s);
}


template <class Archive, class T, std::size_t N>
void serialize(Archive& ar, boost::array<T,N>& a, const unsigned int /* version */)
{
  ar & boost::serialization::make_nvp("elems",a.elems);
}

    static bool & get_lock(){
        static bool lock = false;
        return lock;
    }

    static void lock(){
        get_lock() = true;
    }

    static void unlock(){
        get_lock() = false;
    }

    static bool is_locked() {
        return get_lock();
    }

    ~singleton_wrapper(){
        m_is_destroyed = true;
    }

    static void use(T const &) {}


template<class Archive, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::set<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, std::set<Key, Compare, Allocator> 
    >(ar, t);
}


template<class Archive, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::set<Key, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::load_collection<
        Archive,
        std::set<Key, Compare, Allocator>,
        boost::serialization::stl::archive_input_set<
            Archive, std::set<Key, Compare, Allocator> 
        >,
        boost::serialization::stl::no_reserve_imp<std::set<
            Key, Compare, Allocator> 
        >
    >(ar, t);
}

template<class Archive, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::set<Key, Compare, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}


template <class Archive, std::size_t size>
inline void save(
    Archive & ar,
    std::bitset<size> const & t,
    const unsigned int /* version */
){
    const std::string bits = t.template to_string<
        std::string::value_type,
        std::string::traits_type,
        std::string::allocator_type
    >();
    ar << BOOST_SERIALIZATION_NVP( bits );
}


template <class Archive, std::size_t size>
inline void load(
    Archive & ar,
    std::bitset<size> & t,
    const unsigned int /* version */
){
    std::string bits;
    ar >> BOOST_SERIALIZATION_NVP( bits );
    t = std::bitset<size>(bits);
}


template <class Archive, std::size_t size>
inline void serialize(
    Archive & ar,
    std::bitset<size> & t,
    const unsigned int version
){
    boost::serialization::split_free( ar, t, version );
}

    void operator()(void const *) const {}


template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost::shared_ptr< T > &t,
    const unsigned int /* file_version */
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    const T * t_ptr = t.get();
    ar << boost::serialization::make_nvp("px", t_ptr);
}

template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::shared_ptr< T > &t,
    const unsigned int /*file_version*/
){
    // The most common cause of trapping here would be serializing
    // something like shared_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    T* r;
    ar >> boost::serialization::make_nvp("px", r);
    ar.reset(t,r);
}


template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost::shared_ptr< T > &t,
    const unsigned int file_version
){
    // correct shared_ptr serialization depends upon object tracking
    // being used.
    BOOST_STATIC_ASSERT(
        boost::serialization::tracking_level< T >::value
        != boost::serialization::track_never
    );
    boost::serialization::split_free(ar, t, file_version);
}


template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void save(
    Archive & ar,
    const std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::save_collection<
        Archive, 
        std::map<Key, Type, Compare, Allocator> 
    >(ar, t);
}


template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void load(
    Archive & ar,
    std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int /* file_version */
){
    boost::serialization::stl::load_collection<
        Archive,
        std::map<Key, Type, Compare, Allocator>,
        boost::serialization::stl::archive_input_map<
            Archive, std::map<Key, Type, Compare, Allocator> >,
            boost::serialization::stl::no_reserve_imp<std::map<
                Key, Type, Compare, Allocator
            >
        >
    >(ar, t);
}

template<class Archive, class Type, class Key, class Compare, class Allocator >
inline void serialize(
    Archive & ar,
    std::map<Key, Type, Compare, Allocator> &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}


template<class Archive, class U, class Allocator>
inline void save(
    Archive & ar,
    const std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::save_collection<Archive, STD::vector<U, Allocator> >(
        ar, t
    );
}


template<class Archive, class U, class Allocator>
inline void load(
    Archive & ar,
    std::vector<U, Allocator> &t,
    const unsigned int /* file_version */,
    mpl::false_
){
    boost::serialization::stl::load_collection<
        Archive,
        std::vector<U, Allocator>,
        boost::serialization::stl::archive_input_seq<
            Archive, STD::vector<U, Allocator> 
        >,
        boost::serialization::stl::reserve_imp<STD::vector<U, Allocator> >
    >(ar, t);
}

template<class Archive, class U, class Allocator>
inline void serialize(
    Archive & ar,
    std::vector<U, Allocator> & t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

        static void invoke(T & previous_ref, const T & previous_value){
            previous_ref = previous_value; // won't throw
        }

        static void invoke(T & previous_ref, const T & previous_value){
            BOOST_TRY{
                previous_ref = previous_value;
            } 
            BOOST_CATCH(::std::exception &) { 
                // we must ignore it - we are in destructor
            }
            BOOST_CATCH_END
        }

    state_saver(
        T & object
    ) : 
        previous_value(object),
        previous_ref(object) 
    {}

    
    ~state_saver() {
        #ifndef BOOST_NO_EXCEPTIONS
            typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
                has_nothrow_copy< T >,
                mpl::identity<restore>,
                mpl::identity<restore_with_exception>
            >::type typex;
            typex::invoke(previous_ref, previous_value);
        #else
            previous_ref = previous_value;
        #endif
    }


template<class Archive, class U>
void save( Archive & ar, const STD::valarray<U> &t, const unsigned int /*file_version*/ )
{
  const collection_size_type count(t.size());
  ar << BOOST_SERIALIZATION_NVP(count);
  if (t.size())
    ar << make_array(detail::get_data(t), t.size());
}


template<class Archive, class U>
void load( Archive & ar, STD::valarray<U> &t,  const unsigned int /*file_version*/ )
{
  collection_size_type count;
  ar >> BOOST_SERIALIZATION_NVP(count);
  t.resize(count);
  if (t.size())
    ar >> make_array(detail::get_data(t), t.size());
}

template<class Archive, class U>
inline void serialize( Archive & ar, STD::valarray<U> & t, const unsigned int file_version)
{
    boost::serialization::split_free(ar, t, file_version);
}


template<class Archive, class Container>
inline void save_collection(Archive & ar, const Container &s)
{
    // record number of elements
    collection_size_type count(s.size());
    const item_version_type item_version(
        version<BOOST_DEDUCED_TYPENAME Container::value_type>::value
    );
    ar << BOOST_SERIALIZATION_NVP(count);
    #if 0
        boost::archive::library_version_type library_version(
            ar.get_library_version()
        );
        if(boost::archive::library_version_type(3) < library_version){
            ar << BOOST_SERIALIZATION_NVP(item_version);
        }
    #else
        ar << BOOST_SERIALIZATION_NVP(item_version);
    #endif

    BOOST_DEDUCED_TYPENAME Container::const_iterator it = s.begin();
    while(count-- > 0){
        // note borland emits a no-op without the explicit namespace
        boost::serialization::save_construct_data_adl(
            ar, 
            &(*it), 
            item_version
        );
        ar << boost::serialization::make_nvp("item", *it++);
    }
}

    explicit nvp(const char * name_, T & t) :
        // note: redundant cast works around borland issue
        // note: added _ to suppress useless gcc warning
        std::pair<const char *, T *>(name_, (T*)(& t))
    {}

    nvp(const nvp & rhs) : 
        // note: redundant cast works around borland issue
        std::pair<const char *, T *>(rhs.first, (T*)rhs.second)
    {}


    const char * name() const {
        return this->first;
    }

    T & value() const {
        return *(this->second);
    }


    const T & const_value() const {
        return *(this->second);
    }

    template<class Archivex>
    void save(
        Archivex & ar, 
        const unsigned int /* file_version */
    ) const {
        // CodeWarrior 8.x can't seem to resolve the << op for a rhs of "const T *"
        ar.operator<<(const_value());
    }

    template<class Archivex>
    void load(
        Archivex & ar, 
        const unsigned int /* file_version */
    ){
        // CodeWarrior 8.x can't seem to resolve the >> op for a rhs of "const T *"
        ar.operator>>(value());
    }


template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
nvp< T > make_nvp(const char * name, T & t){
    return nvp< T >(name, t);
}

    extended_type_info_typeid() :
        typeid_system::extended_type_info_typeid_0(get_key())
    {
        type_register(typeid(T));
        key_register();
    }

    ~extended_type_info_typeid(){
        key_unregister();
        type_unregister();
    }

    const extended_type_info *
    get_derived_extended_type_info(const T & t) const {
        // note: this implementation - based on usage of typeid (rtti)
        // only does something if the class has at least one virtual function.
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        return 
            typeid_system::extended_type_info_typeid_0::get_extended_type_info(
                typeid(t)
            );
    }

    const char * get_key() const {
        return boost::serialization::guid< T >();
    }

    virtual void * construct(unsigned int count, ...) const{
        // count up the arguments
        std::va_list ap;
        va_start(ap, count);
        switch(count){
        case 0:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 0>(ap);
        case 1:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 1>(ap);
        case 2:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 2>(ap);
        case 3:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 3>(ap);
        case 4:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 4>(ap);
        default:
            BOOST_ASSERT(false); // too many arguments
            // throw exception here?
            return NULL;
        }
    }

    virtual void destroy(void const * const p) const {
        boost::serialization::access::destroy(
            static_cast<T const *>(p)
        );
        //delete static_cast<T const * const>(p);
    }

    collection_size_type(): t(0) {};

    collection_size_type(const collection_size_type & t_) : 
        t(t_.t)
    {}

    collection_size_type & operator=(const collection_size_type & rhs){
        t = rhs.t; 
        return *this;
    }

    collection_size_type & operator=(const unsigned int & rhs){
        t = rhs; 
        return *this;
    }

    operator base_type () const {
        return t;
    }

    operator base_type & () {
        return t;
    }
                
    bool operator==(const collection_size_type & rhs) const {
        return t == rhs.t;
    }
 
    bool operator<(const collection_size_type & rhs) const {
        return t < rhs.t;
    }


template<class Archive, class T>
inline void save(
    Archive & ar,
    const boost::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    const boost::shared_ptr< T > sp = t.lock();
    ar << boost::serialization::make_nvp("weak_ptr", sp);
}


template<class Archive, class T>
inline void load(
    Archive & ar,
    boost::weak_ptr< T > &t,
    const unsigned int /* file_version */
){
    boost::shared_ptr< T > sp;
    ar >> boost::serialization::make_nvp("weak_ptr", sp);
    t = sp;
}


template<class Archive, class T>
inline void serialize(
    Archive & ar,
    boost::weak_ptr< T > &t,
    const unsigned int file_version
){
    boost::serialization::split_free(ar, t, file_version);
}

            static const char * invoke(){
                return guid< T >();
            }

        static const char * invoke(){
            typedef 
                BOOST_DEDUCED_TYPENAME boost::mpl::if_c<
                    tf,
                    defined,
                    undefined
                >::type type;
            return type::invoke();
        }

    extended_type_info_no_rtti() :
        no_rtti_system::extended_type_info_no_rtti_0(get_key())
    {
        key_register();
    }

    ~extended_type_info_no_rtti(){
        key_unregister();
    }

    const extended_type_info *
    get_derived_extended_type_info(const T & t) const {
        // find the type that corresponds to the most derived type.
        // this implementation doesn't depend on typeid() but assumes
        // that the specified type has a function of the following signature.
        // A common implemention of such a function is to define as a virtual
        // function. So if the is not a polymporphic type it's likely an error
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        const char * derived_key = t.get_key();
        BOOST_ASSERT(NULL != derived_key);
        return boost::serialization::extended_type_info::find(derived_key);
    }

    const char * get_key() const{
        return action<guid_defined< T >::value >::invoke();
    }

    virtual const char * get_debug_info() const{
        return action<guid_defined< T >::value >::invoke();
    }

    virtual void * construct(unsigned int count, ...) const{
        // count up the arguments
        std::va_list ap;
        va_start(ap, count);
        switch(count){
        case 0:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 0>(ap);
        case 1:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 1>(ap);
        case 2:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 2>(ap);
        case 3:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 3>(ap);
        case 4:
            return factory<BOOST_DEDUCED_TYPENAME boost::remove_const< T >::type, 4>(ap);
        default:
            BOOST_ASSERT(false); // too many arguments
            // throw exception here?
            return NULL;
        }
    }

    virtual void destroy(void const * const p) const{
        boost::serialization::access::destroy(
            static_cast<T const *>(p)
        );
        //delete static_cast<T const * const>(p) ;
    }

    operator const T & (){
        return t;
    }

    pfto_wrapper (const T & rhs) : t(rhs) {}


template<class T>
pfto_wrapper< T > make_pfto_wrapper(const T & t, BOOST_PFTO int){
    return pfto_wrapper< T >(t);
}


template<class T>
pfto_wrapper< T > make_pfto_wrapper(const pfto_wrapper< T > & t, int){
    return t;
}

    void operator()(Container &s, std::size_t count) const {
        s.reserve(count);
    }

    void operator()(Container & /* s */, std::size_t /* count */) const{}


template<class Archive, class Container, class InputFunction, class R>
inline void load_collection(Archive & ar, Container &s)
{
    s.clear();
    collection_size_type count;
    const boost::archive::library_version_type library_version(
        ar.get_library_version()
    );
    // retrieve number of elements
    item_version_type item_version(0);
    ar >> BOOST_SERIALIZATION_NVP(count);
    if(boost::archive::library_version_type(3) < library_version){
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }

    R rx;
    rx(s, count);
    InputFunction ifunc;
    BOOST_DEDUCED_TYPENAME Container::iterator hint;
    hint = s.begin();
    while(count-- > 0){
        hint = ifunc(ar, s, item_version, hint);
    }
}

                template<class U>
                 static T cast(U & u){
                    return static_cast< T >(u);
                }

                 template<class U>
                static T cast(U & u){
                    return dynamic_cast< T >(u);
                }


            template<class U>
            static T cast(U & u){
                // if we're in debug mode
                #if ! defined(NDEBUG)                               \
                || defined(__BORLANDC__) && (__BORLANDC__ <= 0x560) \
                || defined(__MWERKS__)
                    // do a checked dynamic cast
                    return cross::cast(u);
                #else
                    // borland 5.51 chokes here so we can't use it
                    // note: if remove_reference isn't function for these types
                    // cross casting will be selected this will work but will
                    // not be the most efficient method. This will conflict with
                    // the original smart_cast motivation.
                    typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
                            BOOST_DEDUCED_TYPENAME mpl::and_<
                                mpl::not_<is_base_and_derived<
                                    BOOST_DEDUCED_TYPENAME remove_reference< T >::type,
                                    U
                                > >,
                                mpl::not_<is_base_and_derived<
                                    U,
                                    BOOST_DEDUCED_TYPENAME remove_reference< T >::type
                                > >
                            >,
                            // borland chokes w/o full qualification here
                            mpl::identity<cross>,
                            mpl::identity<linear>
                    >::type typex;
                    // typex works around gcc 2.95 issue
                    return typex::cast(u);
                #endif
            }

            template<class U>
             static T cast(U & u){
                return static_cast< T >(u);
            }

        template<class U>
        static T cast(U & u){
            #if defined(__BORLANDC__)
                return mpl::eval_if<
                    boost::is_polymorphic<U>,
                    mpl::identity<polymorphic>,
                    mpl::identity<non_polymorphic>
                >::type::cast(u);
            #else
                typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
                    boost::is_polymorphic<U>,
                    mpl::identity<polymorphic>,
                    mpl::identity<non_polymorphic>
                >::type typex;
                return typex::cast(u);
            #endif
        }

            template<class U>
            static T cast(U * u){
                T tmp = dynamic_cast< T >(u);
                #ifndef NDEBUG
                    if ( tmp == 0 ) throw_exception(std::bad_cast());
                #endif
                return tmp;
            }

            template<class U>
             static T cast(U * u){
                return static_cast< T >(u);
            }


        template<class U>
        static T cast(U * u){
            #if defined(__BORLANDC__)
                return mpl::eval_if<
                    boost::is_polymorphic<U>,
                    mpl::identity<polymorphic>,
                    mpl::identity<non_polymorphic>
                >::type::cast(u);
            #else
                typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
                    boost::is_polymorphic<U>,
                    mpl::identity<polymorphic>,
                    mpl::identity<non_polymorphic>
                >::type typex;
                return typex::cast(u);
            #endif
        }

        template<class UPtr>
        static TPtr cast(UPtr uptr){
            return static_cast<TPtr>(uptr);
        }

        template<class U>
        static T cast(U u){
            BOOST_STATIC_ASSERT(sizeof(T)==0);
            return * static_cast<T *>(NULL);
        }

template<class T, class U>
T smart_cast(U u) {
    typedef
        BOOST_DEDUCED_TYPENAME mpl::eval_if<
            BOOST_DEDUCED_TYPENAME mpl::or_<
                boost::is_same<void *, U>,
                boost::is_same<void *, T>,
                boost::is_same<const void *, U>,
                boost::is_same<const void *, T>
            >,
            mpl::identity<smart_cast_impl::void_pointer< T > >,
        // else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<boost::is_pointer<U>,
            mpl::identity<smart_cast_impl::pointer< T > >,
        // else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<boost::is_reference<U>,
            mpl::identity<smart_cast_impl::reference< T > >,
        // else
            mpl::identity<smart_cast_impl::error< T >
        >
        >
        >
        >::type typex;
    return typex::cast(u);
}

template<class T, class U>
T smart_cast_reference(U & u) {
    return smart_cast_impl::reference< T >::cast(u);
}

        static void invoke(
            Archive & ar, 
            const T & t,
            const unsigned int file_version
        ){
            access::member_save(ar, t, file_version);
        }

        static void invoke(
            Archive & ar, 
            T & t,
            const unsigned int file_version
        ){
            access::member_load(ar, t, file_version);
        }


template<class Archive, class T>
inline void split_member(
    Archive & ar, T & t, const unsigned int file_version
){
    typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
        BOOST_DEDUCED_TYPENAME Archive::is_saving,
        mpl::identity<detail::member_saver<Archive, T> >, 
        mpl::identity<detail::member_loader<Archive, T> >
    >::type typex;
    typex::invoke(ar, t, file_version);
}


    shared_ptr(): px(0), pn() // never throws in 1.30+
    {
    }

    template<class Y>
    explicit shared_ptr(Y * p): px(p), pn(p, boost::checked_deleter<Y>()) // Y must be complete
#endif
    {
        detail::sp_enable_shared_from_this( pn, p, p );
    }


    template<class Y, class D> shared_ptr(Y * p, D d): px(p), pn(p, d)
    {
        detail::sp_enable_shared_from_this( pn, p, p );
    }


    shared_ptr & operator=(shared_ptr const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }


    template<class Y>
    explicit shared_ptr(weak_ptr<Y> const & r): pn(r.pn) // may throw
    {
        // it is now safe to copy r.px, as pn(r.pn) did not throw
        px = r.px;
    }


    template<class Y>
    shared_ptr(shared_ptr<Y> const & r): px(r.px), pn(r.pn) // never throws
    {
    }


    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::static_cast_tag): px(static_cast<element_type *>(r.px)), pn(r.pn)
    {
    }


    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::const_cast_tag): px(const_cast<element_type *>(r.px)), pn(r.pn)
    {
    }


    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::dynamic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if(px == 0) // need to allocate new counter -- the cast failed
        {
            pn = detail::shared_count();
        }
    }


    template<class Y>
    shared_ptr(shared_ptr<Y> const & r, detail::polymorphic_cast_tag): px(dynamic_cast<element_type *>(r.px)), pn(r.pn)
    {
        if(px == 0)
        {
            boost::serialization::throw_exception(std::bad_cast());
        }
    }


    template<class Y>
    shared_ptr & operator=(shared_ptr<Y> const & r) // never throws
    {
        px = r.px;
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }


    void reset() // never throws in 1.30+
    {
        this_type().swap(*this);
    }


    template<class Y> void reset(Y * p) // Y must be complete
    {
        BOOST_ASSERT(p == 0 || p != px); // catch self-reset errors
        this_type(p).swap(*this);
    }


    template<class Y, class D> void reset(Y * p, D d)
    {
        this_type(p, d).swap(*this);
    }


    reference operator* () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return *px;
    }


    T * operator-> () const // never throws
    {
        BOOST_ASSERT(px != 0);
        return px;
    }

    
    T * get() const // never throws
    {
        return px;
    }


    operator unspecified_bool_type() const // never throws
    {
        return px == 0? 0: &this_type::px;
    }


    bool operator! () const // never throws
    {
        return px == 0;
    }


    bool unique() const // never throws
    {
        return pn.unique();
    }


    long use_count() const // never throws
    {
        return pn.use_count();
    }


    void swap(shared_ptr< T > & other) // never throws
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }


    template<class Y> bool _internal_less(shared_ptr<Y> const & rhs) const
    {
        return pn < rhs.pn;
    }


    void * _internal_get_deleter(std::type_info const & ti) const
    {
        return pn.get_deleter(ti);
    }


template<class T, class U> inline bool operator==(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}


template<class T, class U> inline bool operator!=(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}


template<class T, class U> inline bool operator<(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a._internal_less(b);
}


template<class T> inline void swap(shared_ptr< T > & a, shared_ptr< T > & b)
{
    a.swap(b);
}


template<class T, class U> shared_ptr< T > static_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::static_cast_tag());
}


template<class T, class U> shared_ptr< T > const_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::const_cast_tag());
}


template<class T, class U> shared_ptr< T > dynamic_pointer_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::dynamic_cast_tag());
}


template<class T, class U> shared_ptr< T > shared_static_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::static_cast_tag());
}


template<class T, class U> shared_ptr< T > shared_dynamic_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::dynamic_cast_tag());
}


template<class T, class U> shared_ptr< T > shared_polymorphic_cast(shared_ptr<U> const & r)
{
    return shared_ptr< T >(r, detail::polymorphic_cast_tag());
}


template<class T, class U> shared_ptr< T > shared_polymorphic_downcast(shared_ptr<U> const & r)
{
    BOOST_ASSERT(dynamic_cast<T *>(r.get()) == r.get());
    return shared_static_cast< T >(r);
}


template<class T> inline T * get_pointer(shared_ptr< T > const & p)
{
    return p.get();
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
            boost::serialization::throw_exception(std::bad_alloc());
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

    
    void swap(shared_ptr< T > & other)  // never throws
    {
        std::swap(px, other.px);
        std::swap(pn, other.pn);
    }


template<class T, class U> inline bool operator==(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() == b.get();
}


template<class T, class U> inline bool operator!=(shared_ptr< T > const & a, shared_ptr<U> const & b)
{
    return a.get() != b.get();
}


template<class T> inline bool operator<(shared_ptr< T > const & a, shared_ptr< T > const & b)
{
    return std::less<T*>()(a.get(), b.get());
}


template<class T> void swap(shared_ptr< T > & a, shared_ptr< T > & b)
{
    a.swap(b);
}


template<class T> inline T * get_pointer(shared_ptr< T > const & p)
{
    return p.get();
}


    virtual char const * what() const throw()
    {
        return "boost::bad_weak_ptr";
    }


    sp_counted_base(): use_count_(1), weak_count_(1)
    {
    }


    virtual ~sp_counted_base() // nothrow
    {
    }


    virtual void destruct() // nothrow
    {
        delete this;
    }


    void add_ref_copy()
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++use_count_;
    }


    void add_ref_lock()
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        if(use_count_ == 0) boost::serialization::throw_exception(bad_weak_ptr());
        ++use_count_;
    }


    void release() // nothrow
    {
        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            long new_use_count = --use_count_;

            if(new_use_count != 0) return;
        }

        dispose();
        weak_release();
    }


    void weak_add_ref() // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++weak_count_;
    }


    void weak_release() // nothrow
    {
        long new_weak_count;

        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            new_weak_count = --weak_count_;
        }

        if(new_weak_count == 0)
        {
            destruct();
        }
    }


    long use_count() const // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        return use_count_;
    }


    sp_counted_base_impl(P p, D d): ptr(p), del(d)
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_constructor_hook(this, p, d, 0);
#endif
    }


    virtual void dispose() // nothrow
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        detail::cbi_call_destructor_hook(this, ptr, del, 0);
#endif
        del(ptr);
    }


    virtual void * get_deleter(std::type_info const & ti)
    {
        return ti == typeid(D)? &del: 0;
    }


    shared_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }


    template<class P, class D> shared_count(P p, D d): pi_(0)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_base_impl<P, D>(p, d);
        }
        catch(...)
        {
            d(p); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_base_impl<P, D>(p, d);

        if(pi_ == 0)
        {
            d(p); // delete p
            boost::serialization::throw_exception(std::bad_alloc());
        }

#endif
    }
 

    ~shared_count() // nothrow
    {
        if(pi_ != 0) pi_->release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }


    shared_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->add_ref_copy();
    }


    shared_count & operator= (shared_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;

        if(tmp != pi_)
        {
            if(tmp != 0) tmp->add_ref_copy();
            if(pi_ != 0) pi_->release();
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


    void * get_deleter(std::type_info const & ti) const
    {
        return pi_? pi_->get_deleter(ti): 0;
    }


    weak_count(): pi_(0) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
    }


    weak_count(shared_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }


    weak_count(weak_count const & r): pi_(r.pi_) // nothrow
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
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
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

        return *this;
    }


    weak_count & operator= (weak_count const & r) // nothrow
    {
        sp_counted_base * tmp = r.pi_;
        if(tmp != 0) tmp->weak_add_ref();
        if(pi_ != 0) pi_->weak_release();
        pi_ = tmp;

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


inline shared_count::shared_count(weak_count const & r): pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if(pi_ != 0)
    {
        pi_->add_ref_lock();
    }
    else
    {
        boost::serialization::throw_exception(bad_weak_ptr());
    }
}

    T * address() {
        return static_cast<T*>(storage_.address()); 
    }

    T & reference() {
        return * address();
    }

    stack_construct(Archive & ar, const unsigned int version){
        // note borland emits a no-op without the explicit namespace
        boost::serialization::load_construct_data_adl(
            ar, 
            this->address(), 
            version
        );
    }

    ~stack_construct(){
        this->address()->~T(); // undo load_construct_data above
    }
