

    template<class T>
    void load(T & t)
    {
        if(! is.fail()){
            is >> t;
            return;
        }
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    }


    void load(char & t)
    {
        short int i;
        load(i);
        t = i;
    }

    void load(signed char & t)
    {
        short int i;
        load(i);
        t = i;
    }

    void load(unsigned char & t)
    {
        unsigned short int i;
        load(i);
        t = i;
    }

    void load(wchar_t & t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        int i;
        load(i);
        t = i;
    }

    std::wistream & get_is(){
        return is;
    }

    template<class T>
    void 
    load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        basic_xml_iarchive<Archive>::load_override(t, 0);
    }

    naked_xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        xml_wiarchive_impl<naked_xml_wiarchive>(is, flags)
    {}

    ~naked_xml_wiarchive(){}

    xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        xml_wiarchive_impl<xml_wiarchive>(is, flags)
    {}

    ~xml_wiarchive(){}

    template<class T>
    void save_override(const T & t, BOOST_PFTO int version){
      this->detail_common_oarchive::save_override(t, static_cast<int>(version));
    }


    basic_binary_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags)
    {}

    template<class T>
    void 
    save(const T & t){
        basic_text_oprimitive<std::wostream>::save(t);
    }

    ~xml_woarchive_impl(){}

    void 
    save_binary(const void *address, std::size_t count){
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::wostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address, 
            count
        );
        this->indent_next = true;
    }

    xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        xml_woarchive_impl<xml_woarchive>(os, flags)
    {}

    ~xml_woarchive(){}

    polymorphic_binary_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_binary_iarchive>(is, flags)
    {}

    ~polymorphic_binary_iarchive(){}

    template<class T>
    void load_override(T & t,  BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t, 0);
    }

    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::wistream>::load(t);
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        basic_text_iarchive<Archive>::load_override(t, 0);
    }

    ~text_wiarchive_impl(){};

    naked_text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        text_wiarchive_impl<naked_text_wiarchive>(is, flags)
    {}

    ~naked_text_wiarchive(){}

    text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        text_wiarchive_impl<text_wiarchive>(is, flags)
    {}

    ~text_wiarchive(){}

    polymorphic_text_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_text_wiarchive>(is, flags)
    {}

    ~polymorphic_text_wiarchive(){}

    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        basic_text_iarchive<Archive>::load_override(t, 0);
    }

    ~text_iarchive_impl(){};

    naked_text_iarchive(std::istream & is_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_iarchive_impl<naked_text_iarchive>(is_, flags)
    {}

    ~naked_text_iarchive(){}

    text_iarchive(std::istream & is_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_iarchive_impl<text_iarchive>(is_, flags)
    {}

    ~text_iarchive(){}

    template<class T>
    void save_override(T & t, BOOST_PFTO int)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_oarchive::save_override(t, 0);
    }

    polymorphic_text_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_text_iarchive>(is, flags)
    {}

    ~polymorphic_text_iarchive(){}


template<class Facet>
inline std::locale * 
add_facet(const std::locale &l, Facet * f){
    return
        #if defined BOOST_ARCHIVE_OLD_DINKUMWARE_BENEATH_STLPORT 
            // std namespace used for native locale
            new std::locale(std::_Addfac(l, f));
        #elif BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) // old Dinkumwar
            // std namespace used for native locale
            new std::locale(std::_Addfac(l, f));
        #else
            // standard compatible
            new std::locale(l, f);
        #endif
}

    naked_binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            naked_binary_wiarchive, 
            std::wistream::char_type, 
            std::wistream::traits_type
        >(is, flags)
    {}

    binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(is, flags)
    {}

    virtual bool do_always_noconv() const throw() {
        return true;
    }

    explicit codecvt_null(std::size_t no_locale_manage = 0) :
        std::codecvt<char, char, std::mbstate_t>(no_locale_manage)
    {}

    virtual int do_encoding( ) const throw( ){
        return sizeof(wchar_t) / sizeof(char);
    }

    virtual int do_max_length( ) const throw( ){
        return do_encoding();
    }

    explicit basic_streambuf_locale_saver( state_type &s )
        : s_save_( s ), a_save_( s.getloc() )
        {}

    ~basic_streambuf_locale_saver()
        { this->restore(); }

    void  restore()
        { s_save_.pubimbue( a_save_ ); }

    binary_woarchive(std::wostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_woarchive, std::wostream::char_type, std::wostream::traits_type
        >(os, flags)
    {}

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        this->detail_common_iarchive::load_override(t, 0);
    }


    basic_text_iarchive(unsigned int flags) : 
        detail::common_iarchive<Archive>(flags)
    {}

    ~basic_text_iarchive(){}

    template<class T>
    void save_override(T & t, BOOST_PFTO int)
    {
        archive::save(* this->This(), t);
    }

    virtual ~polymorphic_oarchive_impl(){};

    virtual ~polymorphic_oarchive(){};

    template<class T>
    void save(const T &t){
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << t;
    }

    void save(const bool t){
        // trap usage of invalid uninitialized boolean which would
        // otherwise crash on load.
        BOOST_ASSERT(0 == static_cast<int>(t) || 1 == static_cast<int>(t));
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << t;
    }

    void save(const signed char t)
    {
        save(static_cast<short int>(t));
    }

    void save(const unsigned char t)
    {
        save(static_cast<short unsigned int>(t));
    }

    void save(const char t)
    {
        save(static_cast<short int>(t));
    }

    void save(const wchar_t t)
    {
        BOOST_STATIC_ASSERT(sizeof(wchar_t) <= sizeof(int));
        save(static_cast<int>(t));
    }

    void save(const float t)
    {
        // must be a user mistake - can't serialize un-initialized data
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << std::setprecision(std::numeric_limits<float>::digits10 + 2);
        os << t;
    }

    void save(const double t)
    {
        // must be a user mistake - can't serialize un-initialized data
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os << std::setprecision(std::numeric_limits<double>::digits10 + 2);
        os << t;
    }

    void put(BOOST_DEDUCED_TYPENAME OStream::char_type c){
        if(os.fail())
            boost::serialization::throw_exception(
                archive_exception(archive_exception::output_stream_error)
            );
        os.put(c);
    }

    void put(const char * s){
        while('\0' != *s)
            os.put(*s++);
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int version){
      this->detail_common_iarchive::load_override(t, static_cast<int>(version));
    }

   
    basic_binary_iarchive(unsigned int flags) :
        detail::common_iarchive<Archive>(flags)
    {}

    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::ostream>::save(t);
    }

    ~text_oarchive_impl(){};

    text_oarchive(std::ostream & os_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_oarchive_impl<text_oarchive>(os_, flags)
    {}

    ~text_oarchive(){}

    polymorphic_xml_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_xml_iarchive>(is, flags)
    {}

    ~polymorphic_xml_iarchive(){}

    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    void save(const T & t)
    {
        save_binary(& t, sizeof(T));
    }

    void save(const bool t){
        BOOST_ASSERT(0 == static_cast<int>(t) || 1 == static_cast<int>(t));
        save_binary(& t, sizeof(t));
    }

    template <class ValueType>
    void save_array(boost::serialization::array<ValueType> const& a, unsigned int)
    {
      save_binary(a.address(),a.count()*sizeof(ValueType));
    }

    template<class T>
    void save_override(T & t, BOOST_PFTO int){
        this->basic_binary_oarchive<Archive>::save_override(t, 0L);
    }

    void init(unsigned int flags) {
        if(0 != (flags & no_header))
            return;
        #if ! defined(__MWERKS__)
            this->basic_binary_oarchive<Archive>::init();
            this->basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_oarchive<Archive>::init();
            basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #endif
    }

    binary_oarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb, 
        unsigned int flags
    ) :
        basic_binary_oprimitive<Archive, Elem, Tr>(
            bsb, 
            0 != (flags & no_codecvt)
        ),
        basic_binary_oarchive<Archive>(flags)
    {
        init(flags);
    }


inline const char * tmpdir(){
    const char *dirname;
    dirname = std::getenv("TMP");
    if(NULL == dirname)
        dirname = std::getenv("TMPDIR");
    if(NULL == dirname)
        dirname = std::getenv("TEMP");
    if(NULL == dirname){
        //BOOST_ASSERT(false); // no temp directory found
        dirname = ".";
    }
    return dirname;
}


    std::istream & get_is(){
        return is;
    }

    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        basic_xml_iarchive<Archive>::load_override(t, 0);
    }

    naked_xml_iarchive(std::istream & is, unsigned int flags = 0) :
        xml_iarchive_impl<naked_xml_iarchive>(is, flags)
    {}

    ~naked_xml_iarchive(){}

    xml_iarchive(std::istream & is, unsigned int flags = 0) :
        xml_iarchive_impl<xml_iarchive>(is, flags)
    {}

    ~xml_iarchive(){};

    library_version_type(): t(0) {};

    explicit library_version_type(const unsigned int & t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }

    library_version_type(const library_version_type & t_) : 
        t(t_.t)
    {}

    library_version_type & operator=(const library_version_type & rhs){
        t = rhs.t; 
        return *this;
    }

    operator base_type () const {
        return t;
    }

    operator base_type & (){
        return t;
    }
                
    bool operator==(const library_version_type & rhs) const {
        return t == rhs.t;
    }
 
    bool operator<(const library_version_type & rhs) const {
        return t < rhs.t;
    }

    version_type(): t(0) {};

    explicit version_type(const unsigned int & t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }

    version_type(const version_type & t_) : 
        t(t_.t)
    {}

    version_type & operator=(const version_type & rhs){
        t = rhs.t; 
        return *this;
    }

    operator base_type () const {
        return t;
    }

    operator base_type  & (){
        return t;
    }
                
    bool operator==(const version_type & rhs) const {
        return t == rhs.t;
    }
 
    bool operator<(const version_type & rhs) const {
        return t < rhs.t;
    }

    class_id_type() : t(0) {};

    explicit class_id_type(const int t_) : t(t_){
        BOOST_ASSERT(t_ <= boost::integer_traits<base_type>::const_max);
    }

    class_id_type(const class_id_type & t_) : 
        t(t_.t)
    {}

    class_id_type & operator=(const class_id_type & rhs){
        t = rhs.t; 
        return *this;
    }

    operator int () const {
        return t;
    }

    object_id_type(): t(0) {};

    object_id_type(const object_id_type & t_) : 
        t(t_.t)
    {}

    object_id_type & operator=(const object_id_type & rhs){
        t = rhs.t; 
        return *this;
    }

    explicit tracking_type(const bool t_ = false)
        : t(t_)
    {};

    tracking_type(const tracking_type & t_)
        : t(t_.t)
    {}

    operator bool () const {
        return t;
    };

    operator bool & () {
        return t;
    };

    tracking_type & operator=(const bool t_){
        t = t_;
        return *this;
    }

    bool operator==(const tracking_type & rhs) const {
        return t == rhs.t;
    }

    bool operator==(const bool & rhs) const {
        return t == rhs;
    }

    tracking_type & operator=(const tracking_type & rhs){
        t = rhs.t;
        return *this;
    }

    operator const char * & () const {
        return const_cast<const char * &>(t);
    }

    operator char * () {
        return t;
    }

    explicit class_name_type(const char *key_) 
    : t(const_cast<char *>(key_)){}

    explicit class_name_type(char *key_) 
    : t(key_){}

    class_name_type & operator=(const class_name_type & rhs){
        t = rhs.t;
        return *this;
    }
                                        \
        explicit D(const T tt) : T(tt){}           \
    };                                             \
/**/

BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_reference_type)
                                        \
        explicit D(const T tt) : T(tt){}           \
    };                                             \
/**/

BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_reference_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_optional_type)
                                        \
        explicit D(const T tt) : T(tt){}           \
    };                                             \
/**/

BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_reference_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(class_id_type, class_id_optional_type)
BOOST_ARCHIVE_STRONG_TYPEDEF(object_id_type, object_reference_type)

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        this->basic_binary_iarchive<Archive>::load_override(t, 0L);
    }

    void init(unsigned int flags){
        if(0 != (flags & no_header))
            return;
        #if ! defined(__MWERKS__)
            this->basic_binary_iarchive<Archive>::init();
            this->basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_iarchive<Archive>::init();
            basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #endif
    }

    binary_iarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb, 
        unsigned int flags
    ) :
        basic_binary_iprimitive<Archive, Elem, Tr>(
            bsb, 
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>(flags)
    {
        init(flags);
    }

    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::wostream>::save(t);
    }

    text_woarchive_impl(std::wostream & os, unsigned int flags) :
        basic_text_oprimitive<std::wostream>(
            os, 
            0 != (flags & no_codecvt)
        ),
        basic_text_oarchive<Archive>(flags)
    {
        if(0 == (flags & no_header))
            basic_text_oarchive<Archive>::init();
    }

    void save_binary(const void *address, std::size_t count){
        put(static_cast<wchar_t>('\n'));
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::wostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address, 
            count
        );
        put(static_cast<wchar_t>('\n'));
        this->delimiter = this->none;
    }

    text_woarchive(std::wostream & os, unsigned int flags = 0) :
        text_woarchive_impl<text_woarchive>(os, flags)
    {}

    ~text_woarchive(){}

    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    void load(T & t){
        load_binary(& t, sizeof(T));
    }

    void load(bool & t){
        load_binary(& t, sizeof(t));
        int i = t;
        BOOST_ASSERT(0 == i || 1 == i);
        (void)i; // warning suppression for release builds.
    }

    template <class ValueType>
    void load_array(serialization::array<ValueType>& a, unsigned int)
    {
      load_binary(a.address(),a.count()*sizeof(ValueType));
    }

    polymorphic_xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<naked_xml_wiarchive>(is, flags)
    {}

    ~polymorphic_xml_wiarchive(){}

        bool operator()(
            const shared_ptr<const void> &lhs,
            const shared_ptr<const void> &rhs
        )const{
            return lhs.get() < rhs.get();
        }

        void operator()(void const *) const {}

        void_deleter(const boost::serialization::extended_type_info *eti) :
            m_eti(eti)
        {}

        void operator()(void *vp) const {
            m_eti->destroy(vp);
        }

        static const boost::serialization::extended_type_info * 
        get_object_identifier(T &){
            return & boost::serialization::singleton<
                BOOST_DEDUCED_TYPENAME 
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance();
        }

        static const boost::serialization::extended_type_info * 
        get_object_identifier(T & t){
            return boost::serialization::singleton<
                BOOST_DEDUCED_TYPENAME 
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance().get_derived_extended_type_info(t);
        }

    template<class T>
    void reset(shared_ptr< T > & s, T * t){
        if(NULL == t){
            s.reset();
            return;
        }
        const boost::serialization::extended_type_info * this_type
            = & boost::serialization::type_info_implementation< T >::type
                    ::get_const_instance();

        // get pointer to the most derived object.  This is effectively
        // the object identifern
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
            is_polymorphic< T >,
            mpl::identity<polymorphic< T > >,
            mpl::identity<non_polymorphic< T > >
        >::type type;

        const boost::serialization::extended_type_info * true_type
            = type::get_object_identifier(*t);

        // note:if this exception is thrown, be sure that derived pointern
        // is either registered or exported.
        if(NULL == true_type)
            boost::serialization::throw_exception(
                archive_exception(
                    archive_exception::unregistered_class,
                    this_type->get_debug_info()
                )
            );
        shared_ptr<void> r =
            get_od(
                static_cast<const void *>(t), 
                true_type,
                this_type
            );
        if(!r){
            s.reset(t);
            const void * od = void_downcast(
                *true_type,
                *this_type,
                static_cast<const void *>(t)
            );
            shared_ptr<const void> sp(s, od);
            append(sp);
        }
        else{
            s = shared_ptr< T >(
                r,
                static_cast<T *>(r.get())
            );
        }
    }

    binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_oarchive, std::ostream::char_type, std::ostream::traits_type
        >(os, flags)
    {}

    template<class T>
    void load_override(T & t, BOOST_PFTO int)
    {
        archive::load(* this->This(), t);
    }

    virtual ~polymorphic_iarchive_impl(){};

    virtual ~polymorphic_iarchive(){};


    void newline(){
        delimiter = eol;
    }

    template<class T>
    void save_override(T & t, BOOST_PFTO int){
        this->detail_common_oarchive::save_override(t, 0);
    }


    basic_text_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags),
        delimiter(none)
    {}

    ~basic_text_oarchive(){}

    naked_binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            naked_binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(is, flags)
    {}

    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(is, flags)
    {}

    template<class T>
    void save(const T & t){
        basic_text_oprimitive<std::ostream>::save(t);
    }

    ~xml_oarchive_impl(){}

    void save_binary(const void *address, std::size_t count){
        this->end_preamble();
        #if ! defined(__MWERKS__)
        this->basic_text_oprimitive<std::ostream>::save_binary(
        #else
        this->basic_text_oprimitive::save_binary(
        #endif
            address, 
            count
        );
        this->indent_next = true;
    }

    xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        xml_oarchive_impl<xml_oarchive>(os, flags)
    {}

    ~xml_oarchive(){}

    template<class Archive, class T>
    static void load_primitive(Archive &ar, T &t){
        ar.load(t);
    }

    virtual void destroy(/*const*/ void *address) const {
        boost::serialization::access::destroy(static_cast<T *>(address));
    }

    explicit iserializer() :
        basic_iserializer(
            boost::serialization::singleton<
                BOOST_DEDUCED_TYPENAME 
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance()
        )
    {}

    virtual bool class_info() const {
        return boost::serialization::implementation_level< T >::value 
            >= boost::serialization::object_class_info;
    }

    virtual bool tracking(const unsigned int /* flags */) const {
        return boost::serialization::tracking_level< T >::value 
                == boost::serialization::track_always
            || ( boost::serialization::tracking_level< T >::value 
                == boost::serialization::track_selectively
                && serialized_as_pointer());
    }

    virtual version_type version() const {
        return version_type(::boost::serialization::version< T >::value);
    }

    virtual bool is_polymorphic() const {
        return boost::is_polymorphic< T >::value;
    }

    virtual ~iserializer(){};

            static T* invoke() {
                return static_cast<T *>((T::operator new)(sizeof(T)));
            }

            static T* invoke() {
                return static_cast<T *>(operator new(sizeof(T)));
            }

        static T * invoke() {
            typedef BOOST_DEDUCED_TYPENAME
                mpl::eval_if<
                    boost::has_new_operator< T >,
                    mpl::identity<has_new_operator >,
                    mpl::identity<doesnt_have_new_operator >    
                >::type typex;
            return typex::invoke();
        }

    explicit auto_ptr_with_deleter(T* p) :
        m_p(p)
    {}

    ~auto_ptr_with_deleter(){
        if (m_p)
            boost::serialization::access::destroy(m_p);
    }

    T* get() const {
        return m_p;
    }


    T* release() {
        T* p = m_p;
        m_p = NULL;
        return p;
    }

        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return static_cast<basic_pointer_iserializer *>(NULL);
         }

        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }


    template<class T>
    static const basic_pointer_iserializer * register_type(Archive &ar, const T & /*t*/){
        // there should never be any need to load an abstract polymorphic 
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef BOOST_DEDUCED_TYPENAME
            mpl::eval_if<
                boost::serialization::is_abstract<const T>,
                boost::mpl::identity<abstract>,
                boost::mpl::identity<non_abstract>  
            >::type typex;
        return typex::template register_type< T >(ar);
    }


    template<class T>
    static T * pointer_tweak(
        const boost::serialization::extended_type_info & eti,
        void const * const t,
        const T &
    ) {
        // tweak the pointer back to the base class
        return static_cast<T *>(
            const_cast<void *>(
                boost::serialization::void_upcast(
                    eti,
                    boost::serialization::singleton<
                        BOOST_DEDUCED_TYPENAME 
                        boost::serialization::type_info_implementation< T >::type
                    >::get_const_instance(),
                    t
                )
            )
        );
    }


    template<class T>
    static void check_load(T & /* t */){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
    }


    static const basic_pointer_iserializer *
    find(const boost::serialization::extended_type_info & type){
        return static_cast<const basic_pointer_iserializer *>(
            archive_serializer_map<Archive>::find(type)
        );
    }


    template<class Tptr>
    static void invoke(Archive & ar, Tptr & t){
        check_load(*t);
        const basic_pointer_iserializer * bpis_ptr = register_type(ar, *t);
        const basic_pointer_iserializer * newbpis_ptr = ar.load_pointer(
            // note major hack here !!!
            // I tried every way to convert Tptr &t (where Tptr might
            // include const) to void * &.  This is the only way
            // I could make it work. RR
            (void * & )t,
            bpis_ptr,
            find
        );
        // if the pointer isn't that of the base class
        if(newbpis_ptr != bpis_ptr){
            t = pointer_tweak(newbpis_ptr->get_eti(), t, *t);
        }
    }

    template<class T>
    static void invoke(Archive &ar, T &t){
        // convert integers to correct enum to load
        int i;
        ar >> boost::serialization::make_nvp(NULL, i);
        t = static_cast< T >(i);
    }

    template<class T>
    static void invoke(Archive &ar, T &t){
        typedef BOOST_DEDUCED_TYPENAME remove_extent< T >::type value_type;
        
        // convert integers to correct enum to load
        // determine number of elements in the array. Consider the
        // fact that some machines will align elements on boundries
        // other than characters.
        std::size_t current_count = sizeof(t) / (
            static_cast<char *>(static_cast<void *>(&t[1])) 
            - static_cast<char *>(static_cast<void *>(&t[0]))
        );
        boost::serialization::collection_size_type count;
        ar >> BOOST_SERIALIZATION_NVP(count);
        if(static_cast<std::size_t>(count) > current_count)
            boost::serialization::throw_exception(
                archive::archive_exception(
                    boost::archive::archive_exception::array_size_too_short
                )
            );
        ar >> serialization::make_array(static_cast<value_type*>(&t[0]),count);
    }


template<class Archive, class T>
inline void load(Archive & ar, T &t){
    // if this assertion trips. It means we're trying to load a
    // const object with a compiler that doesn't have correct
    // funtion template ordering.  On other compilers, this is
    // handled below.
    detail::check_const_loading< T >();
    typedef
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::load_pointer_type<Archive> >
        ,//else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_array< T >,
            mpl::identity<detail::load_array_type<Archive> >
        ,//else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_enum< T >,
            mpl::identity<detail::load_enum_type<Archive> >
        ,//else
            mpl::identity<detail::load_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

    virtual void vload(version_type & t){
        * this->This() >> t; 
    }

    template<class T>
    void load_override(T & t, BOOST_PFTO int){
        archive::load(* this->This(), t);
    }

    void load_start(const char * /*name*/){}

    void load_end(const char * /*name*/){}

    common_iarchive(unsigned int flags = 0) : 
        basic_iarchive(flags),
        interface_iarchive<Archive>()
    {}

template <class Serializable>
void instantiate_ptr_serialization(Serializable*, int, adl_tag ) {}

    interface_iarchive(){};

    Archive * This(){
        return static_cast<Archive *>(this);
    }


    template<class T>
    const basic_pointer_iserializer * 
    register_type(T * = NULL){
        const basic_pointer_iserializer & bpis =
            boost::serialization::singleton<
                pointer_iserializer<Archive, T> 
            >::get_const_instance();
        this->This()->register_basic_serializer(bpis.get_basic_serializer());
        return & bpis;
    }

    template<class T>
    Archive & operator>>(T & t){
        this->This()->load_override(t, 0);
        return * this->This();
    }

    template<class T>
    Archive & operator&(T & t){
        return *(this->This()) >> t;
    }

    template<class Archive>
    static void end_preamble(Archive & ar){
        ar.end_preamble();
    }

    template<class Archive, class T>
    static void save_primitive(Archive & ar, const  T & t){
        ar.end_preamble();
        ar.save(t);
    }

    virtual bool class_info() const {
        return boost::serialization::implementation_level< T >::value 
            >= boost::serialization::object_class_info;
    }

    virtual bool tracking(const unsigned int /* flags */) const {
        return boost::serialization::tracking_level< T >::value == boost::serialization::track_always
            || (boost::serialization::tracking_level< T >::value == boost::serialization::track_selectively
                && serialized_as_pointer());
    }

    virtual version_type version() const {
        return version_type(::boost::serialization::version< T >::value);
    }

    virtual bool is_polymorphic() const {
        return boost::is_polymorphic< T >::value;
    }

    virtual ~oserializer(){}

        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return NULL;
        }

        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }


    template<class T>
    static const basic_pointer_oserializer * register_type(Archive &ar, T & /*t*/){
        // there should never be any need to save an abstract polymorphic 
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef 
            BOOST_DEDUCED_TYPENAME mpl::eval_if<
                boost::serialization::is_abstract< T >,
                mpl::identity<abstract>,
                mpl::identity<non_abstract>       
            >::type typex;
        return typex::template register_type< T >(ar);
    }

        template<class T>
        static void save(
            Archive &ar, 
            T & t
        ){
            const basic_pointer_oserializer & bpos = 
                boost::serialization::singleton<
                    pointer_oserializer<Archive, T>
                >::get_const_instance();
            // save the requested pointer type
            ar.save_pointer(& t, & bpos);
        }

        template<class T>
        static void save(
            Archive &ar, 
            T & t
        ){
            BOOST_DEDUCED_TYPENAME 
            boost::serialization::type_info_implementation< T >::type const
            & i = boost::serialization::singleton<
                BOOST_DEDUCED_TYPENAME 
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance();

            boost::serialization::extended_type_info const * const this_type = & i;

            // retrieve the true type of the object pointed to
            // if this assertion fails its an error in this library
            BOOST_ASSERT(NULL != this_type);

            const boost::serialization::extended_type_info * true_type =
                i.get_derived_extended_type_info(t);

            // note:if this exception is thrown, be sure that derived pointer
            // is either registered or exported.
            if(NULL == true_type){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            }

            // if its not a pointer to a more derived type
            const void *vp = static_cast<const void *>(&t);
            if(*this_type == *true_type){
                const basic_pointer_oserializer * bpos = register_type(ar, t);
                ar.save_pointer(vp, bpos);
                return;
            }
            // convert pointer to more derived type. if this is thrown
            // it means that the base/derived relationship hasn't be registered
            vp = serialization::void_downcast(
                *true_type, 
                *this_type, 
                static_cast<const void *>(&t)
            );
            if(NULL == vp){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_cast,
                        true_type->get_debug_info(),
                        this_type->get_debug_info()
                    )
                );
            }

            // since true_type is valid, and this only gets made if the 
            // pointer oserializer object has been created, this should never
            // fail
            const basic_pointer_oserializer * bpos
                = static_cast<const basic_pointer_oserializer *>(
                    boost::serialization::singleton<
                        archive_serializer_map<Archive>
                    >::get_const_instance().find(*true_type)
                );
            BOOST_ASSERT(NULL != bpos);
            if(NULL == bpos)
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            ar.save_pointer(vp, bpos);
        }


    template<class T>
    static void save(
        Archive & ar, 
        const T & t
    ){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
        typedef BOOST_DEDUCED_TYPENAME mpl::eval_if<
            is_polymorphic< T >,
            mpl::identity<polymorphic>,
            mpl::identity<non_polymorphic>
        >::type type;
        type::save(ar, const_cast<T &>(t));
    }


    template<class TPtr>
    static void invoke(Archive &ar, const TPtr t){
        register_type(ar, * t);
        if(NULL == t){
            basic_oarchive & boa 
                = boost::serialization::smart_cast_reference<basic_oarchive &>(ar);
            boa.save_null_pointer();
            save_access::end_preamble(ar);
            return;
        }
        save(ar, * t);
    }

    template<class T>
    static void invoke(Archive &ar, const T &t){
        // convert enum to integers on save
        const int i = static_cast<int>(t);
        ar << boost::serialization::make_nvp(NULL, i);
    }

    template<class T>
    static void invoke(Archive &ar, const T &t){
        typedef BOOST_DEDUCED_TYPENAME boost::remove_extent< T >::type value_type;
        
        save_access::end_preamble(ar);
        // consider alignment
        std::size_t c = sizeof(t) / (
            static_cast<const char *>(static_cast<const void *>(&t[1])) 
            - static_cast<const char *>(static_cast<const void *>(&t[0]))
        );
        boost::serialization::collection_size_type count(c);
        ar << BOOST_SERIALIZATION_NVP(count);
        ar << serialization::make_array(static_cast<value_type const*>(&t[0]),count);
    }


template<class Archive, class T>
inline void save(Archive & ar, /*const*/ T &t){
    typedef 
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::save_pointer_type<Archive> >,
        //else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_enum< T >,
            mpl::identity<detail::save_enum_type<Archive> >,
        //else
        BOOST_DEDUCED_TYPENAME mpl::eval_if<is_array< T >,
            mpl::identity<detail::save_array_type<Archive> >,
        //else
            mpl::identity<detail::save_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

    explicit basic_serializer(
        const boost::serialization::extended_type_info & eti
    ) : 
        m_eti(& eti)
    {
        BOOST_ASSERT(NULL != & eti);
    }

    inline bool 
    operator<(const basic_serializer & rhs) const {
        // can't compare address since there can be multiple eti records
        // for the same type in different execution modules (that is, DLLS)
        // leave this here as a reminder not to do this!
        // return & lhs.get_eti() < & rhs.get_eti();
        return get_eti() < rhs.get_eti();
    }

    const char * get_debug_info() const {
        return m_eti->get_debug_info();
    }

    const boost::serialization::extended_type_info & get_eti() const {
        return * m_eti;
    }

    basic_serializer_arg(const serialization::extended_type_info & eti) :
        basic_serializer(eti)
    {}

    virtual void save_object(
        const void *x,
        const detail::basic_oserializer & bos
    ){
        ArchiveImplementation::save_object(x, bos);
    }

    virtual void save_pointer(
        const void * t,
        const detail::basic_pointer_oserializer * bpos_ptr
    ){
        ArchiveImplementation::save_pointer(t, bpos_ptr);
    }

    virtual void save_null_pointer(){
        ArchiveImplementation::save_null_pointer();
    }

    virtual void save(const bool t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const char t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const signed char t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const unsigned char t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const wchar_t t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const short t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const unsigned short t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const int t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const unsigned int t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const long t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const unsigned long t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const float t){
        ArchiveImplementation::save(t);
    }

    virtual void save(const double t){
        ArchiveImplementation::save(t);
    }

    virtual library_version_type get_library_version() const{
        return ArchiveImplementation::get_library_version();
    }

    virtual unsigned int get_flags() const {
        return ArchiveImplementation::get_flags();
    }

    virtual void save_binary(const void * t, std::size_t size){
        ArchiveImplementation::save_binary(t, size);
    }

    virtual void save_start(const char * name){
        ArchiveImplementation::save_start(name);
    }

    virtual void save_end(const char * name){
        ArchiveImplementation::save_end(name);
    }

    virtual void end_preamble(){
        ArchiveImplementation::end_preamble();
    }

    virtual void register_basic_serializer(const detail::basic_oserializer & bos){
        ArchiveImplementation::register_basic_serializer(bos);
    }

    template<class T>
    polymorphic_oarchive & operator<<(T & t){
        return polymorphic_oarchive::operator<<(t);
    }

    template<class T>
    polymorphic_oarchive & operator&(T & t){
        return polymorphic_oarchive::operator&(t);
    }

    template<class T>
    const basic_pointer_oserializer * 
    register_type(T * t = NULL){
        return ArchiveImplementation::register_type(t);
    }

    template <class _Elem, class _Tr>
    polymorphic_oarchive_route(
        std::basic_ostream<_Elem, _Tr> & os,
        unsigned int flags = 0
    ) :
        ArchiveImplementation(os, flags)
    {}

    virtual ~polymorphic_oarchive_route(){};

    interface_oarchive(){};

    Archive * This(){
        return static_cast<Archive *>(this);
    }


    template<class T>
    const basic_pointer_oserializer * 
    register_type(const T * = NULL){
        const basic_pointer_oserializer & bpos =
            boost::serialization::singleton<
                pointer_oserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpos.get_basic_serializer());
        return & bpos;
    }


    template<class T>
    Archive & operator<<(T & t){
        this->This()->save_override(t, 0);
        return * this->This();
    }

    template<class T>
    Archive & operator&(T & t){
        #ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
            return * this->This() << const_cast<const T &>(t);
        #else
            return * this->This() << t;
        #endif
    }


template<class T>
inline void check_object_level(){
    typedef 
        BOOST_DEDUCED_TYPENAME mpl::greater_equal<
            serialization::implementation_level< T >,
            mpl::int_<serialization::primitive_type>
        >::type typex;

    // trap attempts to serialize objects marked
    // not_serializable
    BOOST_STATIC_ASSERT(typex::value);
}


template<class T>
inline void check_object_versioning(){
    typedef 
        BOOST_DEDUCED_TYPENAME mpl::or_<
            BOOST_DEDUCED_TYPENAME mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            BOOST_DEDUCED_TYPENAME mpl::equal_to<
                serialization::version< T >,
                mpl::int_<0>
            >
        > typex;
    // trap attempts to serialize with objects that don't
    // save class information in the archive with versioning.
    BOOST_STATIC_ASSERT(typex::value);
}


template<class T>
inline void check_object_tracking(){
    // presume it has already been determined that
    // T is not a const
    BOOST_STATIC_ASSERT(! boost::is_const< T >::value);
    typedef BOOST_DEDUCED_TYPENAME mpl::equal_to<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // saving an non-const object of a type not marked "track_never)

    // may be an indicator of an error usage of the
    // serialization library and should be double checked.  
    // See documentation on object tracking.  Also, see the 
    // "rationale" section of the documenation
    // for motivation for this checking.

    BOOST_STATIC_WARNING(typex::value);
}


template<class T>
inline void check_pointer_level(){
    // we should only invoke this once we KNOW that T
    // has been used as a pointer!!
    typedef 
        BOOST_DEDUCED_TYPENAME mpl::or_<
            BOOST_DEDUCED_TYPENAME mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            BOOST_DEDUCED_TYPENAME mpl::not_<
                BOOST_DEDUCED_TYPENAME mpl::equal_to<
                    serialization::tracking_level< T >,
                    mpl::int_<serialization::track_selectively>
                >
            >
        > typex;
    // Address the following when serializing to a pointer:

    // a) This type doesn't save class information in the
    // archive. That is, the serialization trait implementation
    // level <= object_serializable.
    // b) Tracking for this type is set to "track selectively"

    // in this case, indication that an object is tracked is
    // not stored in the archive itself - see level == object_serializable
    // but rather the existence of the operation ar >> T * is used to 
    // infer that an object of this type should be tracked.  So, if
    // you save via a pointer but don't load via a pointer the operation
    // will fail on load without given any valid reason for the failure.

    // So if your program traps here, consider changing the 
    // tracking or implementation level traits - or not
    // serializing via a pointer.
    BOOST_STATIC_WARNING(typex::value);
}


template<class T>
void inline check_pointer_tracking(){
    typedef BOOST_DEDUCED_TYPENAME mpl::greater<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // serializing an object of a type marked "track_never" through a pointer
    // could result in creating more objects than were saved!
    BOOST_STATIC_WARNING(typex::value);
}


template<class T>
inline void check_const_loading(){
    typedef
        BOOST_DEDUCED_TYPENAME mpl::or_<
            BOOST_DEDUCED_TYPENAME boost::serialization::is_wrapper< T >,
            BOOST_DEDUCED_TYPENAME mpl::not_<
                BOOST_DEDUCED_TYPENAME boost::is_const< T >
            >
        >::type typex;
    // cannot load data into a "const" object unless it's a
    // wrapper around some other non-const object.
    BOOST_STATIC_ASSERT(typex::value);
}

    virtual void vsave(const version_type t){
        * this->This() << t;
    }

    template<class T>
    void save_override(T & t, BOOST_PFTO int){
        archive::save(* this->This(), t);
    }

    void save_start(const char * /*name*/){}

    void save_end(const char * /*name*/){}

    common_oarchive(unsigned int flags = 0) : 
        basic_oarchive(flags),
        interface_oarchive<Archive>()
    {}

    virtual void load_object(
        void *t,
        const basic_iserializer & bis
    ){
        ArchiveImplementation::load_object(t, bis);
    }

    virtual const basic_pointer_iserializer * load_pointer(
        void * & t,
        const basic_pointer_iserializer * bpis_ptr,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & type
        )
    ){
        return ArchiveImplementation::load_pointer(t, bpis_ptr, finder);
    }

    virtual void set_library_version(library_version_type archive_library_version){
        ArchiveImplementation::set_library_version(archive_library_version);
    }

    virtual library_version_type get_library_version() const{
        return ArchiveImplementation::get_library_version();
    }

    virtual unsigned int get_flags() const {
        return ArchiveImplementation::get_flags();
    }

    virtual void delete_created_pointers(){
        ArchiveImplementation::delete_created_pointers();
    }

    virtual void reset_object_address(
        const void * new_address,
        const void * old_address
    ){
        ArchiveImplementation::reset_object_address(new_address, old_address);
    }

    virtual void load_binary(void * t, std::size_t size){
        ArchiveImplementation::load_binary(t, size);
    }

    virtual void load(bool & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(char & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(signed char & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(unsigned char & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(wchar_t & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(short & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(unsigned short & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(int & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(unsigned int & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(long & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(unsigned long & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(float & t){
        ArchiveImplementation::load(t);
    }

    virtual void load(double & t){
        ArchiveImplementation::load(t);
    }

    virtual void load_start(const char * name){
        ArchiveImplementation::load_start(name);
    }

    virtual void load_end(const char * name){
        ArchiveImplementation::load_end(name);
    }


    virtual void register_basic_serializer(const basic_iserializer & bis){
        ArchiveImplementation::register_basic_serializer(bis);
    }

    template<class T>
    polymorphic_iarchive & operator>>(T & t){
        return polymorphic_iarchive::operator>>(t);
    }

    template<class T>
    polymorphic_iarchive & operator&(T & t){
        return polymorphic_iarchive::operator&(t);
    }

    template<class T>
    const basic_pointer_iserializer * 
    register_type(T * t = NULL){
        return ArchiveImplementation::register_type(t);
    }

    template <class _Elem, class _Tr>
    polymorphic_iarchive_route(
        std::basic_istream<_Elem, _Tr> & is,
        unsigned int flags = 0
    ) :
        ArchiveImplementation(is, flags)
    {}

    virtual ~polymorphic_iarchive_route(){};

        return_values() :
            version(0),
            tracking_level(false)
        {}

        return_values() :
            version(0),
            tracking_level(false)
        {}


    reference_type dereference() const {
        return unescape<xml_unescape<Base>, Base>::dereference();
    }


    template<class T>
    xml_unescape(BOOST_PFTO_WRAPPER(T) start) : 
        super_t(Base(BOOST_MAKE_PFTO_WRAPPER(static_cast< T >(start))))
    {}

    xml_unescape(const xml_unescape & rhs) : 
        super_t(rhs.base_reference())
    {}


template<class Base>
void xml_unescape<Base>::drain_residue(const char * literal){
    do{
        if(* literal != * ++(this->base_reference()))
            boost::serialization::throw_exception(
                dataflow_exception(
                    dataflow_exception::invalid_xml_escape_sequence
                )
            );
    }
    while('\0' != * ++literal);
}

xml_unescape<Base>::drain(){
    value_type retval = * this->base_reference();
    if('&' != retval){
        return retval;
    }
    retval = * ++(this->base_reference());
    switch(retval){
    case 'l': // &lt;
        drain_residue("t;");
        retval = '<';
        break;
    case 'g': // &gt;
        drain_residue("t;");
        retval = '>';
        break;
    case 'a':
        retval = * ++(this->base_reference());
        switch(retval){
        case 'p': // &apos;
            drain_residue("os;");
            retval = '\'';
            break;
        case 'm': // &amp;
            drain_residue("p;");
            retval = '&';
            break;
        }
        break;
    case 'q':
        drain_residue("uot;");
        retval = '"';
        break;
    }
    return retval;
}


    template<class T>
    xml_escape(BOOST_PFTO_WRAPPER(T) start) :
        super_t(Base(BOOST_MAKE_PFTO_WRAPPER(static_cast< T >(start))))
    {}

    xml_escape(const xml_escape & rhs) : 
        super_t(rhs.base_reference())
    {}


template<class Base>
char xml_escape<Base>::fill(
    const char * & bstart, 
    const char * & bend
){
    char current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = "&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = "&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = "&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = "&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = "&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}


template<class Base>
wchar_t xml_escape<Base>::fill(
    const wchar_t * & bstart, 
    const wchar_t * & bend
){
    wchar_t current_value = * this->base_reference();
    switch(current_value){
    case '<':
        bstart = L"&lt;";
        bend = bstart + 4;
        break;
    case '>':
        bstart = L"&gt;";
        bend = bstart + 4;
        break;
    case '&':
        bstart = L"&amp;";
        bend = bstart + 5;
        break;
    case '"':
        bstart = L"&quot;";
        bend = bstart + 6;
        break;
    case '\'':
        bstart = L"&apos;";
        bend = bstart + 6;
        break;
    default:
        return current_value;
    }
    return *bstart;
}


    void dereference_impl() {
        m_current_value = static_cast<Derived *>(this)->fill(m_bnext, m_bend);
        m_full = true;
    }

    reference_type dereference() const {
        if(!m_full)
            const_cast<this_t *>(this)->dereference_impl();
        return m_current_value;
    }


    bool equal(const this_t & rhs) const {
        if(m_full){
            if(! rhs.m_full)
                const_cast<this_t *>(& rhs)->dereference_impl();
        }
        else{
            if(rhs.m_full)
                const_cast<this_t *>(this)->dereference_impl();
        }
        if(m_bnext != rhs.m_bnext)
            return false;
        if(this->base_reference() != rhs.base_reference())
            return false;
        return true;
    }


   void increment(){
        if(++m_bnext < m_bend){
            m_current_value = *m_bnext;
            return;
        }
        ++(this->base_reference());
        m_bnext = NULL;
        m_bend = NULL;
        m_full = false;
    }

    escape(Base base) : 
        super_t(base),
        m_bnext(NULL),
        m_bend(NULL),
        m_full(false)
    {
    }


    reference_type dereference_impl(){
        if(! m_end){
            while(! m_predicate(* this->base_reference()))
                ++ this->base_reference();
            m_end = true;
        }
        return * this->base_reference();
    }


    reference_type dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }


    void increment(){
        ++base_reference();
    }

    template<class T>
    head_iterator(Predicate f, T start) : 
        super_t(Base(start)), 
        m_predicate(f),
        m_end(false)
    {}


    wchar_t dereference_impl() {
        if(! m_full){
            m_current_value = drain();
            m_full = true;
        }
        return m_current_value;
    }


    wchar_t dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }


    void increment(){
        dereference_impl();
        m_full = false;
        ++(this->base_reference());
    };

    template<class T>
    wchar_from_mb(BOOST_PFTO_WRAPPER(T) start) : 
        super_t(Base(BOOST_MAKE_PFTO_WRAPPER(static_cast< T >(start)))),
        m_full(false)
    {}

    wchar_from_mb(const wchar_from_mb & rhs) : 
        super_t(rhs.base_reference()),
        m_full(rhs.m_full)
    {}


template<class Base>
wchar_t wchar_from_mb<Base>::drain(){
    char buffer[9];
    char * bptr = buffer;
    char val;
    for(std::size_t i = 0; i++ < (unsigned)MB_CUR_MAX;){
        val = * this->base_reference();
        *bptr++ = val;
        int result = std::mblen(buffer, i);
        if(-1 != result)
            break;
        ++(this->base_reference());
    }
    wchar_t retval;
    int result = std::mbtowc(& retval, buffer, MB_CUR_MAX);
    if(0 >= result)
        boost::serialization::throw_exception(iterators::dataflow_exception(
            iterators::dataflow_exception::invalid_conversion
        ));
    return retval;
}

    ostream_iterator & dereference() const {
        return const_cast<ostream_iterator &>(*this);
    }

    bool equal(const this_t & rhs) const {
        return m_ostream == rhs.m_ostream;
    }

    void increment(){}

    void put_val(char_type e){
        if(NULL != m_ostream){
            m_ostream->put(e);
            if(! m_ostream->good())
                m_ostream = NULL;
        }
    }

    this_t & operator=(char_type c){
        put_val(c);
        return *this;
    }

    ostream_iterator(ostream_type & os) :
        m_ostream (& os)
    {}

    ostream_iterator() :
        m_ostream (NULL)
    {}

    ostream_iterator(const ostream_iterator & rhs) :
        m_ostream (rhs.m_ostream)
    {}

    CharType operator()(CharType t) const{
        const signed char lookup_table[] = {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
            52,53,54,55,56,57,58,59,60,61,-1,-1,-1, 0,-1,-1, // render '=' as 0
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
            15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
            -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
            41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1
        };
        // metrowerks trips this assertion - how come?
        #if ! defined(__MWERKS__)
        BOOST_STATIC_ASSERT(128 == sizeof(lookup_table));
        #endif
        signed char value = -1;
        if((unsigned)t <= 127)
            value = lookup_table[(unsigned)t];
        if(-1 == value)
            boost::serialization::throw_exception(
                dataflow_exception(dataflow_exception::invalid_base64_character)
            );
        return value;
    }

    bool operator()(unsigned char t){
        return ! std::isspace(t);
    }

    bool operator()(wchar_t t){
        return ! std::iswspace(t);
    }


    reference_type dereference_impl(){
        if(! m_full){
            while(! m_predicate(* this->base_reference()))
                ++(this->base_reference());
            m_full = true;
        }
        return * this->base_reference();
    }


    reference_type dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }

    void increment(){
        m_full = false;
        ++(this->base_reference());
    }

    filter_iterator(Base start) : 
        super_t(start), 
        m_full(false)
    {}

    filter_iterator(){}

    CharType operator()(CharType t) const{
        const char * lookup_table = 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "+/";
        BOOST_ASSERT(t < 64);
        return lookup_table[static_cast<size_t>(t)];
    }


    char dereference_impl() {
        if(! m_full){
            fill();
            m_full = true;
        }
        return m_buffer[m_bnext];
    }

    char dereference() const {
        return (const_cast<this_t *>(this))->dereference_impl();
    }

    bool equal(const mb_from_wchar<Base> & rhs) const {
        // once the value is filled, the base_reference has been incremented
        // so don't permit comparison anymore.
        return 
            0 == m_bend
            && 0 == m_bnext
            && this->base_reference() == rhs.base_reference()
        ;
    }


    void fill(){
        wchar_t value = * this->base_reference();
        #if (defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 3) \
        || ((__MINGW32_MAJOR_VERSION == 3) && (__MINGW32_MINOR_VERSION >= 8))))
        m_bend = std::wcrtomb(m_buffer, value, 0);
        #else
        m_bend = std::wctomb(m_buffer, value);
        #endif
        BOOST_ASSERT(-1 != m_bend);
        BOOST_ASSERT((std::size_t)m_bend <= sizeof(m_buffer));
        BOOST_ASSERT(m_bend > 0);
        m_bnext = 0;
    }


    void increment(){
        if(++m_bnext < m_bend)
            return;
        m_bend = 
        m_bnext = 0;
        ++(this->base_reference());
        m_full = false;
    }

    template<class T>
    mb_from_wchar(BOOST_PFTO_WRAPPER(T) start) :
        super_t(Base(BOOST_MAKE_PFTO_WRAPPER(static_cast< T >(start)))),
        m_bend(0),
        m_bnext(0),
        m_full(false)
    {}

    mb_from_wchar(const mb_from_wchar & rhs) : 
        super_t(rhs.base_reference()),
        m_bend(rhs.m_bend),
        m_bnext(rhs.m_bnext),
        m_full(rhs.m_full)
    {}


    dataflow_exception(exception_code c = other_exception) : code(c)
    {}


    virtual const char *what( ) const throw( )
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_6_bitcode:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_base64_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        case invalid_xml_escape_sequence:
            msg = "invalid xml escape_sequence";
            break;
        case comparison_not_permitted:
            msg = "cannot invoke iterator comparison now";
            break;
        case invalid_conversion:
            msg = "invalid multbyte/wide char conversion";
            break;
        default:
            BOOST_ASSERT(false);
            break;
        }
        return msg;
    }

    value_type dereference_impl() {
        if(! m_full){
            m_current_value = static_cast<Derived *>(this)->drain();
            m_full = true;
        }
        return m_current_value;
    }


    reference dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }


    void increment(){
        ++(this->base_reference());
        dereference_impl();
        m_full = false;
    };


    unescape(Base base) : 
        super_t(base),
        m_full(false)
    {}

    xml_unescape_exception()
    {}


    virtual const char *what( ) const throw( )
    {
        return "xml contained un-recognized escape code";
    }


    base64_exception(exception_code c = other_exception) : code(c)
    {}


    virtual const char *what( ) const throw( )
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_code:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        default:
            BOOST_ASSERT(false);
            break;
        }
        return msg;
    }

 
    bool equal(const this_t & rhs) const {
        // note: only  works for comparison against end of stream
        return m_istream == rhs.m_istream;
    }

    Elem dereference() const {
        return m_istream->peek();
    }


    void increment(){
        if(NULL != m_istream){
            m_istream->ignore(1);
        }
    }

    istream_iterator(istream_type & is) :
        m_istream(& is)
    {
        //increment();
    }


    istream_iterator() :
        m_istream(NULL)
    {}


    istream_iterator(const istream_iterator<Elem> & rhs) :
        m_istream(rhs.m_istream),
        m_current_value(rhs.m_current_value)
    {}

    operator bool (){
        BOOST_ASSERT(is_indeterminant != m_state);
        return is_true == m_state ? true : false;
    }

    tri_state & operator=(bool rhs) {
        m_state = rhs ? is_true : is_false;
        return *this;
    }

    tri_state(bool rhs) :
        m_state(rhs ? is_true : is_false)
    {}

    tri_state(state_enum state) :
        m_state(state)
    {}

    bool operator==(const tri_state & rhs) const {
        return m_state == rhs.m_state;
    }

    bool operator!=(const tri_state & rhs) const {
        return m_state != rhs.m_state;
    }

    tri_state equal(const Derived & rhs) const {
        if(m_eoi && rhs.m_eoi)
            return true;
        if(m_eoi || rhs.m_eoi)
            return false;
        return tri_state(tri_state::is_indeterminant);
    }

    void eoi(bool tf){
        m_eoi = tf;
    }

    bool eoi() const {
        return m_eoi;
    }

    dataflow(bool tf) :
        m_eoi(tf)
    {}

    dataflow() : // used for iterator end
        m_eoi(true)
    {}
