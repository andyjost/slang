
    static char newline() { return '\n'; }

    static int good() { return '\n'; }

    static int would_block() { return WOULD_BLOCK; }

    static bool is_good(int c) { return c != EOF && c != WOULD_BLOCK; }

    static bool is_eof(int c) { return c == EOF; }

    static bool would_block(int c) { return c == WOULD_BLOCK; }

    static wchar_t newline() { return L'\n'; }

    static std::wint_t good() { return L'\n'; }

    static std::wint_t would_block() { return WWOULD_BLOCK; }

    static bool is_good(std::wint_t c) { return c != WEOF && c != WWOULD_BLOCK; }

    static bool is_eof(std::wint_t c) { return c == WEOF; }

    pipeline_segment(const Component& component) 
        : component_(component) 
        { }

    template<typename Fn>
    void for_each(Fn fn) const { fn(component_); }

    template<typename Chain>
    void push(Chain& chn) const { chn.push(component_); }

    pipeline(const Pipeline& p, const Component& component)
        : Pipeline(p), component_(component)
        { }

    template<typename Fn>
    void for_each(Fn fn) const
    {
        Pipeline::for_each(fn);
        fn(component_);
    }

    template<typename Chain>
    void push(Chain& chn) const
    { 
        Pipeline::push(chn);
        chn.push(component_);
    }

    const Pipeline& tail() const { return *this; }

    const Component& head() const { return component_; }


template<typename Pipeline, typename Filter, typename Component>
pipeline<pipeline<Pipeline, Filter>, Component>
operator|(const pipeline<Pipeline, Filter>& p, const Component& cmp)
{
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    return pipeline<pipeline<Pipeline, Filter>, Component>(p, cmp);
}

    chain_base() : pimpl_(new chain_impl) { }

    chain_base(const chain_base& rhs): pimpl_(rhs.pimpl_) { }

    void set_device_buffer_size(std::streamsize n) 
        { pimpl_->device_buffer_size_ = n; }

    void set_filter_buffer_size(std::streamsize n) 
        { pimpl_->filter_buffer_size_ = n; }

    void set_pback_size(std::streamsize n) 
        { pimpl_->pback_size_ = n; }


    const std::type_info& component_type(int n) const
    {
        if (static_cast<size_type>(n) >= size())
            boost::throw_exception(std::out_of_range("bad chain offset"));
        return (*boost::next(list().begin(), n))->component_type();
    }

    template<typename T>
    T* component(int n, boost::type<T>) const
    {
        if (static_cast<size_type>(n) >= size())
            boost::throw_exception(std::out_of_range("bad chain offset"));
        streambuf_type* link = *boost::next(list().begin(), n);
        if (BOOST_IOSTREAMS_COMPARE_TYPE_ID(link->component_type(), typeid(T)))
            return static_cast<T*>(link->component_impl());
        else
            return 0;
    }

    streambuf_type& front() { return *list().front(); }

    bool empty() const { return list().empty(); }

    size_type size() const { return list().size(); }

    bool sync() { return front().BOOST_IOSTREAMS_PUBSYNC() != -1; }

    template<typename T>
    void push_impl(const T& t, std::streamsize buffer_size = -1, 
                   std::streamsize pback_size = -1)
    {
        typedef typename iostreams::category_of<T>::type  category;
        typedef typename unwrap_ios<T>::type              component_type;
        typedef stream_buffer<
                    component_type,
                    BOOST_IOSTREAMS_CHAR_TRAITS(char_type),
                    Alloc, Mode
                >                                         streambuf_t;
        typedef typename list_type::iterator              iterator;
        BOOST_STATIC_ASSERT((is_convertible<category, Mode>::value));
        if (is_complete())
            boost::throw_exception(std::logic_error("chain complete"));
        streambuf_type* prev = !empty() ? list().back() : 0;
        buffer_size =
            buffer_size != -1 ?
                buffer_size :
                iostreams::optimal_buffer_size(t);
        pback_size =
            pback_size != -1 ?
                pback_size :
                pimpl_->pback_size_;
        std::auto_ptr<streambuf_t>
            buf(new streambuf_t(t, buffer_size, pback_size));
        list().push_back(buf.get());
        buf.release();
        if (is_device<component_type>::value) {
            pimpl_->flags_ |= f_complete | f_open;
            for ( iterator first = list().begin(),
                           last = list().end();
                  first != last;
                  ++first )
            {
                (*first)->set_needs_close();
            }
        }
        if (prev) prev->set_next(list().back());
        notify();
    }


    list_type& list() { return pimpl_->links_; }

    void register_client(client_type* client) { pimpl_->client_ = client; }

    void notify() { if (pimpl_->client_) pimpl_->client_->notify(); }


    static void close(streambuf_type* b, BOOST_IOS::openmode m)
    {
        if (m == BOOST_IOS::out && is_convertible<Mode, output>::value)
            b->BOOST_IOSTREAMS_PUBSYNC();
        b->close(m);
    }


    static void set_next(streambuf_type* b, streambuf_type* next)
    { b->set_next(next); }

        closer(BOOST_IOS::openmode m) : mode_(m) { }

        void operator() (streambuf_type* b)
        {
            close(b, mode_);
        }

        chain_impl()
            : client_(0), device_buffer_size_(default_device_buffer_size),
              filter_buffer_size_(default_filter_buffer_size),
              pback_size_(default_pback_buffer_size),
              flags_(f_auto_close)
            { }

        ~chain_impl()
            {
                try { close(); } catch (...) { }
                try { reset(); } catch (...) { }
            }

        void close()
            {
                if ((flags_ & f_open) != 0) {
                    flags_ &= ~f_open;
                    stream_buffer< basic_null_device<Ch, Mode> > null;
                    if ((flags_ & f_complete) == 0) {
                        null.open(basic_null_device<Ch, Mode>());
                        set_next(links_.back(), &null);
                    }
                    links_.front()->BOOST_IOSTREAMS_PUBSYNC();
                    try {
                        boost::iostreams::detail::execute_foreach(
                            links_.rbegin(), links_.rend(), 
                            closer(BOOST_IOS::in)
                        );
                    } catch (...) {
                        try {
                            boost::iostreams::detail::execute_foreach(
                                links_.begin(), links_.end(), 
                                closer(BOOST_IOS::out)
                            );
                        } catch (...) { }
                        throw;
                    }
                    boost::iostreams::detail::execute_foreach(
                        links_.begin(), links_.end(), 
                        closer(BOOST_IOS::out)
                    );
                }
            }

        void reset()
            {
                typedef typename list_type::iterator iterator;
                for ( iterator first = links_.begin(),
                               last = links_.end();
                      first != last;
                      ++first )
                {
                    if ( (flags_ & f_complete) == 0 ||
                         (flags_ & f_auto_close) == 0 )
                    {
                        set_auto_close(*first, false);
                    }
                    streambuf_type* buf = 0;
                    std::swap(buf, *first);
                    delete buf;
                }
                links_.clear();
                flags_ &= ~f_complete;
                flags_ &= ~f_open;
            }


    chain_client(chain_type* chn = 0) : chain_(chn ) { }

    chain_client(chain_client* client) : chain_(client->chain_) { }

    virtual ~chain_client() { }


    const std::type_info& component_type(int n) const
    { return chain_->component_type(n); }

    template<typename T>
    T* component(int n, boost::type<T> t) const
    { return chain_->component(n, t); }


    bool is_complete() const { return chain_->is_complete(); }

    bool auto_close() const { return chain_->auto_close(); }

    void set_auto_close(bool close) { chain_->set_auto_close(close); }

    bool strict_sync() { return chain_->strict_sync(); }

    void set_device_buffer_size(std::streamsize n)
        { chain_->set_device_buffer_size(n); }

    void set_filter_buffer_size(std::streamsize n)
        { chain_->set_filter_buffer_size(n); }

    void set_pback_size(std::streamsize n) { chain_->set_pback_size(n); }


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::reset()
{
    using namespace std;
    pimpl_->close();
    pimpl_->reset();
}


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::is_complete() const
{
    return (pimpl_->flags_ & f_complete) != 0;
}


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::auto_close() const
{
    return (pimpl_->flags_ & f_auto_close) != 0;
}


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::set_auto_close(bool close)
{
    pimpl_->flags_ =
        (pimpl_->flags_ & ~f_auto_close) |
        (close ? f_auto_close : 0);
}


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
bool chain_base<Self, Ch, Tr, Alloc, Mode>::strict_sync()
{
    typedef typename list_type::iterator iterator;
    bool result = true;
    for ( iterator first = list().begin(),
                   last = list().end();
          first != last;
          ++first )
    {
        bool s = (*first)->strict_sync();
        result = result && s;
    }
    return result;
}


template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
void chain_base<Self, Ch, Tr, Alloc, Mode>::pop()
{
    BOOST_ASSERT(!empty());
    if (auto_close())
        pimpl_->close();
    streambuf_type* buf = 0;
    std::swap(buf, list().back());
    buf->set_auto_close(false);
    buf->set_next(0);
    delete buf;
    list().pop_back();
    pimpl_->flags_ &= ~f_complete;
    if (auto_close() || list().empty())
        pimpl_->flags_ &= ~f_open;
}


    explicit tee_filter(param_type dev) 
        : detail::filter_adapter<Device>(dev) 
        { }


    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::read(src, s, n);
        if (result != -1) {
            std::streamsize result2 = iostreams::write(this->component(), s, result);
            (void) result2; // Suppress 'unused variable' warning.
            BOOST_ASSERT(result == result2);
        }
        return result;
    }


    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        std::streamsize result2 = iostreams::write(this->component(), s, result);
        (void) result2; // Suppress 'unused variable' warning.
        BOOST_ASSERT(result == result2);
        return result;
    }


    template<typename Next>
    void close(Next&, BOOST_IOS::openmode)
    { 
        detail::close_all(this->component());
    }


    template<typename Sink>
    bool flush(Sink& snk)
    {
        bool r1 = iostreams::flush(snk);
        bool r2 = iostreams::flush(this->component());
        return r1 && r2;
    }


template<typename Sink>
tee_filter<Sink> tee(Sink& snk) 
{ return tee_filter<Sink>(snk); }


template<typename Sink>
tee_filter<Sink> tee(const Sink& snk) 
{ return tee_filter<Sink>(snk); }

    composite(const Filter& flt, param_type dev)
        : base(flt, dev)
        { }


template<typename Filter, typename FilterOrDevice>
composite<Filter, FilterOrDevice>
compose( const Filter& filter, const FilterOrDevice& fod
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(FilterOrDevice) )
{ return composite<Filter, FilterOrDevice>(filter, fod); }

template<typename Source, typename Sink>
std::streamsize copy_impl( Source& src, Sink& snk, 
                           std::streamsize /* buffer_size */,
                           mpl::true_, mpl::true_ )
{   
    using namespace std;
    typedef typename char_type_of<Source>::type  char_type;
    typedef std::pair<char_type*, char_type*>    pair_type;
    pair_type p1 = iostreams::input_sequence(src);
    pair_type p2 = iostreams::output_sequence(snk);
    std::streamsize total = 
        static_cast<std::streamsize>(
            (std::min)(p1.second - p1.first, p2.second - p2.first)
        );
    std::copy(p1.first, p1.first + total, p2.first);
    return total;
}

    copy_operation(Source& src, Sink& snk, std::streamsize buffer_size)
        : src_(src), snk_(snk), buffer_size_(buffer_size)
        { }

    std::streamsize operator()() 
    {
        return copy_impl( src_, snk_, buffer_size_, 
                          is_direct<Source>(), is_direct<Sink>() );
    }

template<typename Source, typename Sink>
std::streamsize
copy( const Source& src, const Sink& snk,
      std::streamsize buffer_size = default_device_buffer_size
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Source)
      BOOST_IOSTREAMS_DISABLE_IF_STREAM(Sink) )
{ 
    typedef typename char_type_of<Source>::type char_type;
    return detail::copy_impl( detail::resolve<input, char_type>(src), 
                              detail::resolve<output, char_type>(snk), 
                              buffer_size ); 
}


template<typename T>
void close_all(T& t)
{ 
    try {
        boost::iostreams::close(t, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, BOOST_IOS::out);
}


template<typename T, typename Sink>
void close_all(T& t, Sink& snk)
{ 
    try {
        boost::iostreams::close(t, snk, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, snk, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, snk, BOOST_IOS::out);
}


template<typename T>
void close(T& t) { detail::close_all(t); }

    template<typename T>
    static void close(T& t)
    {
        t.close();
    }

    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in) && t.is_complete())
            t.pop();
    }

    explicit inverse( const Filter& filter, 
                      std::streamsize buffer_size = 
                          default_filter_buffer_size) 
        : pimpl_(new impl(filter, buffer_size))
        { }


    template<typename Source>
    std::streamsize read(Source& src, char* s, std::streamsize n)
    {
        typedef detail::counted_array_sink<char_type>  array_sink;
        typedef composite<filter_ref, array_sink>      filtered_array_sink;

        BOOST_ASSERT((flags() & f_write) == 0);
        if (flags() == 0) {
            flags() = f_read;
            buf().set(0, 0);
        }

        filtered_array_sink snk(filter(), array_sink(s, n));
        int_type status;
        for ( status = traits_type::good();
              snk.second().count() < n && status == traits_type::good(); )
        {
            status = buf().fill(src);
            buf().flush(snk);
        }
        return snk.second().count() == 0 &&
               status == traits_type::eof() 
                   ? 
               -1
                   : 
               snk.second().count();
    }


    template<typename Sink>
    std::streamsize write(Sink& dest, const char* s, std::streamsize n)
    {
        typedef detail::counted_array_source<char_type>  array_source;
        typedef composite<filter_ref, array_source>      filtered_array_source;

        BOOST_ASSERT((flags() & f_read) == 0);
        if (flags() == 0) {
            flags() = f_write;
            buf().set(0, 0);
        }
        
        filtered_array_source src(filter(), array_source(s, n));
        for (bool good = true; src.second().count() < n && good; ) {
            buf().fill(src);
            good = buf().flush(dest);
        }
        return src.second().count();
    }


    template<typename Device>
    void close(Device& dev)
    {
        detail::execute_all(
            detail::flush_buffer(buf(), dev, (flags() & f_write) != 0),
            detail::call_close_all(pimpl_->filter_, dev),
            detail::clear_flags(flags())
        );
    }

    filter_ref filter() { return boost::ref(pimpl_->filter_); }

        impl(const Filter& filter, std::streamsize n) 
            : filter_(filter), buf_(n), flags_(0)
        { buf_.set(0, 0); }

template<typename Filter>
inverse<Filter> invert(const Filter& f) { return inverse<Filter>(f); }

template<typename T>
inline typename category_of<T>::type get_category(const T&) 
{ typedef typename category_of<T>::type category; return category(); }


template<typename T>
inline std::streampos
seek( T& t, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    return seek_device_impl<T>::seek(detail::unwrap(t), off, way, which); 
}

    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.rdbuf()->pubseekpos(offset_to_position(off));
        } else {
            return t.rdbuf()->pubseekoff(off, way, which);
        }
    }


template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }


template<typename T>
inline std::streamsize
read_if(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, input, output>::type tag;
    return detail::read_write_if_impl<tag>::read(t, s, n);
}


template<typename T>
bool put_if(T& t, typename char_type_of<T>::type c)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::put(t, c);
}


template<typename T>
inline std::streamsize write_if
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::write(t, s, n);
}


template<typename T>
inline std::streampos
seek_if( T& t, stream_offset off, BOOST_IOS::seekdir way, 
         BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    typedef typename dispatch<T, random_access, any_tag>::type tag;
    return seek_if_impl<tag>::seek(t, off, way, which);
}


    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    { return boost::iostreams::read(in_, src, s, n); }


    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    { return boost::iostreams::write(out_, snk, s, n); }


    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::in) {
            if (is_convertible<in_category, dual_use>::value) {
                iostreams::close(in_, snk, BOOST_IOS::in);
            } else {
                detail::close_all(in_, snk);
            }
        }
        if (which == BOOST_IOS::out) {
            if (is_convertible<out_category, dual_use>::value) {
                iostreams::close(out_, snk, BOOST_IOS::out);
            } else {
                detail::close_all(out_, snk);
            }
        }
    }

    combination(const in_type& in, const out_type& out)
        : base_type(in, out) { }

template<typename In, typename Out>
typename detail::combine_traits<In, Out>::type
combine(const In& in, const Out& out) 
{ 
    typedef typename detail::combine_traits<In, Out>::type return_type;
    return return_type(in, out); 
}


template<typename Source, typename Sink>
inline combined_device<Source, Sink>::combined_device
    (const Source& src, const Sink& snk)
    : src_(src), sink_(snk) { }


template<typename InputFilter, typename OutputFilter>
inline combined_filter<InputFilter, OutputFilter>::combined_filter
    (const InputFilter& in, const OutputFilter& out) : in_(in), out_(out)
    { }


template<typename Device>
void skip(Device& dev, stream_offset off, mpl::true_)
{ iostreams::seek(dev, off, BOOST_IOS::cur); }


template<typename Device>
void skip(Device& dev, stream_offset off)
{ 
    typedef typename mode_of<Device>::type     mode;
    typedef mpl::or_<
        is_convertible<mode, input_seekable>,
        is_convertible<mode, output_seekable>
    >                                          can_seek;
    BOOST_STATIC_ASSERT(
        (can_seek::value || is_convertible<mode, input>::value)
    );
    detail::skip(dev, off, can_seek());
}


template<typename T>
inline std::streamsize
read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::read_device_impl<T>::read(detail::unwrap(t), s, n); }


template<typename T>
bool putback(T& t, typename char_type_of<T>::type c)
{ return detail::read_device_impl<T>::putback(detail::unwrap(t), c); }

inline std::streamsize check_eof(std::streamsize n) { return n != 0 ? n : -1; }

    template<typename T>
    static bool true_eof(T& t) { return t.true_eof(); }

    template<typename T>
    static bool true_eof(T&) { return true; }


template<typename T>
inline bool true_eof(T& t)
{
    const bool linked = is_linked<T>::value;
    return true_eof_impl<linked>::true_eof(t);
}


    void close()
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    }


    template<typename Locale>
    void imbue(const Locale&) { }


    template<typename Device>
    void close(Device&)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
        BOOST_STATIC_ASSERT((!is_convertible<Mode, dual_use>::value));
    }


    template<typename Locale>
    void imbue(const Locale&) { }


template<typename T>
bool put(T& t, typename char_type_of<T>::type c)
{ return detail::write_device_impl<T>::put(detail::unwrap(t), c); }


template<typename T>
inline std::streamsize write
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::write_device_impl<T>::write(detail::unwrap(t), s, n); }


template<typename T>
std::streamsize optimal_buffer_size(const T& t)
{
    typedef detail::optimal_buffer_size_impl<T> impl;
    return impl::optimal_buffer_size(detail::unwrap(t));
}


template<typename T>
bool flush(T& t)
{ return detail::flush_device_impl<T>::flush(detail::unwrap(t)); }


template<typename T, typename Sink>
bool flush(T& t, Sink& snk)
{ return detail::flush_filter_impl<T>::flush(detail::unwrap(t), snk); }


inline std::streamoff stream_offset_to_streamoff(stream_offset off)
{ return static_cast<stream_offset>(off); }


inline std::streampos offset_to_position(stream_offset off) { return off; }

template<typename PosType> 
inline stream_offset position_to_offset(PosType pos)
{ return std::streamoff(pos); }

    code_conversion_error() 
        : BOOST_IOSTREAMS_FAILURE("code conversion error")
        { }

    template<typename Ch>
    static Ch* copy(Ch* tgt, const Ch* src, std::streamsize n)
    { return BOOST_IOSTREAMS_CHAR_TRAITS(Ch)::copy(tgt, src, n); }

    template<typename Src, typename Tgt>
    static Tgt* copy(Tgt* tgt, const Src*, std::streamsize) { return tgt; }


template<typename Src, typename Tgt>
Tgt* strncpy_if_same(Tgt* tgt, const Src* src, std::streamsize n)
{
    typedef strncpy_if_same_impl<is_same<Src, Tgt>::value> impl;
    return impl::copy(tgt, src, n);
}


    code_converter_impl() : cvt_(), flags_(0) { }


    ~code_converter_impl()
    { 
        try { 
            if (flags_ & f_open) close(); 
        } catch (...) { /* */ } 
    }


    template <class T>
    void open(const T& dev, int buffer_size)
    {
        if (flags_ & f_open)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("already open"));
        if (buffer_size == -1)
            buffer_size = default_filter_buffer_size;
        int max_length = cvt_.get().max_length();
        buffer_size = (std::max)(buffer_size, 2 * max_length);
        if (can_read::value) {
            buf_.first().resize(buffer_size);
            buf_.first().set(0, 0);
        }
        if (can_write::value && !is_double::value) {
            buf_.second().resize(buffer_size);
            buf_.second().set(0, 0);
        }
        dev_.reset(concept_adapter<device_type>(dev));
        flags_ = f_open;
    }


    void close()
    {
        detail::execute_all(
            detail::call_member_close(*this, BOOST_IOS::in),
            detail::call_member_close(*this, BOOST_IOS::out)
        );
    }


    bool is_open() const { return (flags_ & f_open) != 0;}


    device_type& dev() { return **dev_; }

    code_converter_base() : pimpl_(new impl_type) { }


    void const* address() const { return &dummy_.data[0]; }

    void      * address()       { return &dummy_.data[0]; }

    optional() : initialized_(false) { }

    optional(const T& t) : initialized_(false) { reset(t); }

    ~optional() { reset(); }

    T& operator*() 
    { 
        BOOST_ASSERT(initialized_);
        return *static_cast<T*>(address()); 
    }

    const T& operator*() const
    { 
        BOOST_ASSERT(initialized_);
        return *static_cast<const T*>(address()); 
    }

    T* operator->() 
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<T*>(address()); 
    }

    const T* operator->() const
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<const T*>(address()); 
    }

    T* get() 
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<T*>(address()); 
    }

    const T* get() const
    { 
        BOOST_ASSERT(initialized_);
        return static_cast<const T*>(address()); 
    }

    void reset() 
    {
        if (initialized_) { 
        #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)) || \
            BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
            /**/
            T* t = static_cast<T*>(address());
            t->~T();
        #else
            static_cast<T*>(address())->T::~T();
        #endif
            initialized_ = false;
        }
    }

    void reset(const T& t) 
    {
        reset();
        new (address()) T(t); 
        initialized_ = true;
    }

    void* address() { return &storage_; }

    const void* address() const { return &storage_; }


template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type
resolve( const T& t 
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)

         // I suspect that the compilers which require this workaround may
         // be correct, but I'm not sure why :(
         #if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) ||\
             BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205)) || \
             BOOST_WORKAROUND(BOOST_IOSTREAMS_GCC, BOOST_TESTED_AT(400)) ||\
             BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(1110))
             /**/
         , typename disable_if< is_iterator_range<T> >::type* = 0
         #endif
         )
{
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(t);
}

    template<typename T>
    inline T wrap(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)) 
    { return t; }


    template<typename T>
    inline typename wrapped_type<T>::type
    wrap(T& t BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)) { return boost::ref(t); }

    template<typename T>
    static typename unwrapped_type<T>::type& unwrap(const T& t) 
    { return t.get(); }

    template<typename T>
    static typename unwrapped_type<T>::type& unwrap(const T& t) 
    { return const_cast<T&>(t); }


template<typename T>
typename unwrapped_type<T>::type& 
unwrap(const T& t) 
{ return unwrap_impl<is_reference_wrapper<T>::value>::unwrap(t); }

    single_object_holder() { }

    single_object_holder(param_type t) : first_(t) { }

    reference first() { return first_; }

    const_reference first() const { return first_; }

    reference second() { return first_; }

    const_reference second() const { return first_; }

    void swap(single_object_holder& o)
    { std::swap(first_, o.first_); }

    double_object_holder() { }

    double_object_holder(param_type t1, param_type t2)
        : first_(t1), second_(t2) { }

    reference first() { return first_; }

    const_reference first() const { return first_; }

    reference second() { return second_; }

    const_reference second() const { return second_; }

    void swap(double_object_holder& d)
    { 
        std::swap(first_, d.first_); 
        std::swap(second_, d.second_); 
    }

    double_object() : base_type() {}

    double_object(param_type t1, param_type t2)
        : base_type(t1, t2) { }

    bool is_double() const { return IsDouble::value; }

    template<typename Op>
    static Result execute(Op op) { return op(); }

    template<typename Op>
    static int execute(Op op) { op(); return 0; }
 
execute_all(Op op) 
{ 
    return execute_traits<Op>::execute(op);
}


template<class InIt, class Op>
Op execute_foreach(InIt first, InIt last, Op op)
{
    if (first == last)
        return op;
    try {
        op(*first);
    } catch (...) {
        try {
            ++first;
            boost::iostreams::detail::execute_foreach(first, last, op);
        } catch (...) { }
        throw;
    }
    ++first;
    return boost::iostreams::detail::execute_foreach(first, last, op);
}

inline std::string absolute_path(const std::string& path)
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/' || path[0] == '\\') ||
           path.size() > 1 && std::isalpha(path[0]) && path[1] == ':' ?
               path :
               current_directory() + '\\' + path;
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    return path.size() && (path[0] == '/') ?
        path :
        current_directory() + '/' + path;
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

    counted_array_source(const Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }

    std::streamsize read(Ch* s, std::streamsize n)
    {
        std::streamsize result = (std::min)(n, end_ - ptr_);
        BOOST_IOSTREAMS_CHAR_TRAITS(char_type)::copy
            (s, buf_ + ptr_, result);
        ptr_ += result;
        return result;
    }

    std::streamsize count() const { return ptr_; }

    counted_array_sink(Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }

        std::streamsize write(const Ch* s, std::streamsize n)
    {
        std::streamsize result = (std::min)(n, end_ - ptr_);
        BOOST_IOSTREAMS_CHAR_TRAITS(char_type)::copy
            (buf_ + ptr_, s, result);
        ptr_ += result;
        return result;
    }

    std::streamsize count() const { return ptr_; }


inline BOOST_IOSTREAMS_FAILURE system_failure(const char* msg)
{
    std::string result;
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD err;
    LPVOID lpMsgBuf;
    if ( (err = ::GetLastError()) != NO_ERROR &&
         ::FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER |
                           FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           err,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                           (LPSTR) &lpMsgBuf,
                           0,
                           NULL ) != 0 )
    {
        result.reserve(std::strlen(msg) + 2 + std::strlen((LPSTR)lpMsgBuf));
        result.append(msg);
        result.append(": ");
        result.append((LPSTR) lpMsgBuf);
        ::LocalFree(lpMsgBuf);
    } else {
        result += msg;
    }
#else
    const char* system_msg = errno ? strerror(errno) : "";
    result.reserve(std::strlen(msg) + 2 + std::strlen(system_msg));
    result.append(msg);
    result.append(": ");
    result.append(system_msg);
#endif
    return BOOST_IOSTREAMS_FAILURE(result);
}


inline void throw_system_failure(const char* msg)
{ boost::throw_exception(system_failure(msg)); }


template<class Facet>
inline std::locale add_facet(const std::locale &l, Facet * f)
{
    return
        #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) || \
            defined(BOOST_IOSTREMS_STLPORT_WITH_OLD_DINKUMWARE) \
            /**/
            std::locale(std::_Addfac(l, f));
        #else
            // standard compatible
            std::locale(l, f);
        #endif
}


inline BOOST_IOSTREAMS_FAILURE cant_read() 
{ return BOOST_IOSTREAMS_FAILURE("no read access"); }


inline BOOST_IOSTREAMS_FAILURE cant_write() 
{ return BOOST_IOSTREAMS_FAILURE("no write access"); }


inline BOOST_IOSTREAMS_FAILURE cant_seek() 
{ return BOOST_IOSTREAMS_FAILURE("no random access"); }


inline BOOST_IOSTREAMS_FAILURE bad_read() 
{ return BOOST_IOSTREAMS_FAILURE("bad read"); }


inline BOOST_IOSTREAMS_FAILURE bad_putback() 
{ return BOOST_IOSTREAMS_FAILURE("putback buffer full"); }


inline BOOST_IOSTREAMS_FAILURE bad_write() 
{ return BOOST_IOSTREAMS_FAILURE("bad write"); }


inline BOOST_IOSTREAMS_FAILURE write_area_exhausted() 
{ return BOOST_IOSTREAMS_FAILURE("write area exhausted"); }


inline BOOST_IOSTREAMS_FAILURE bad_seek() 
{ return BOOST_IOSTREAMS_FAILURE("bad seek"); }

    device_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }

    void operator()() const { boost::iostreams::close(t_, which_); }

    filter_close_operation(T& t, Sink& snk, BOOST_IOS::openmode which)
        : t_(t), snk_(snk), which_(which)
        { }

    void operator()() const { boost::iostreams::close(t_, snk_, which_); }


template<typename T>
device_close_operation<T> 
call_close(T& t, BOOST_IOS::openmode which) 
{ return device_close_operation<T>(t, which); }

    device_close_all_operation(T& t) : t_(t) { }

    void operator()() const { detail::close_all(t_); }

    filter_close_all_operation(T& t, Sink& snk) : t_(t), snk_(snk) { }

    void operator()() const { detail::close_all(t_, snk_); }


template<typename T>
device_close_all_operation<T> call_close_all(T& t) 
{ return device_close_all_operation<T>(t); }


template<typename T, typename Sink>
filter_close_all_operation<T, Sink> 
call_close_all(T& t, Sink& snk) 
{ return filter_close_all_operation<T, Sink>(t, snk); }

    member_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }

    void operator()() const { t_.close(which_); }


template<typename T>
member_close_operation<T> call_member_close(T& t, BOOST_IOS::openmode which) 
{ return member_close_operation<T>(t, which); }

    reset_operation(T& t) : t_(t) { }

    void operator()() const { t_.reset(); }


template<typename T>
reset_operation<T> call_reset(T& t) { return reset_operation<T>(t); }

    clear_flags_operation(T& t) : t_(t) { }

    void operator()() const { t_ = 0; }


template<typename T>
clear_flags_operation<T> clear_flags(T& t) 
{ return clear_flags_operation<T>(t); }

    flush_buffer_operation(Buffer& buf, Device& dev, bool flush)
        : buf_(buf), dev_(dev), flush_(flush)
        { }

    void operator()() const
    {
        if (flush_) 
            buf_.flush(dev_);
    }


template<typename Buffer, typename Device>
flush_buffer_operation<Buffer, Device> 
flush_buffer(Buffer& buf, Device& dev, bool flush)
{ return flush_buffer_operation<Buffer, Device>(buf, dev, flush); }

template<typename SourceTr, typename TargetTr>
typename TargetTr::int_type 
translate_int_type(typename SourceTr::int_type c) 
{ 
    typedef translate_int_type_impl<is_same<SourceTr, TargetTr>::value> impl;
    return impl::template inner<SourceTr, TargetTr>::translate(c);
}

        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c) { return c; }

        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c)
            { 
                return SourceTr::eq_int_type(SourceTr::eof()) ?
                           TargetTr::eof() :
                           TargetTr::to_int_type(SourceTr::to_char_type(c));
            }

inline std::string current_directory()
{
#ifdef BOOST_IOSTREAMS_WINDOWS
    DWORD               length;
    basic_buffer<char>  buf(MAX_PATH);
    while (true) {
        length = ::GetCurrentDirectoryA(buf.size(), buf.data());
        if (!length)
            throw_system_failure("failed determining current directory");
        if (length < static_cast<DWORD>(buf.size()))
            break;
        buf.resize(buf.size() * 2);
    }
    return std::string(buf.data(), length);
#else // #ifdef BOOST_IOSTREAMS_WINDOWS
    basic_buffer<char> buf(pathconf(".", _PC_PATH_MAX));
    if (!getcwd(buf.data(), static_cast<size_t>(buf.size())))
        throw_system_failure("failed determining current directory");
    return std::string(buf.data());
#endif // #ifdef BOOST_IOSTREAMS_WINDOWS
}

    const codecvt_type& get() const { return codecvt_; }

    void imbue(const std::locale&) { }

    codecvt_holder() { reset_codecvt(); }

    const codecvt_type& get() const { return *codecvt_; }

    void imbue(const std::locale& loc) 
    { 
        loc_ = loc;
        reset_codecvt();
    }

    void reset_codecvt()
    {
        using namespace std;
        #ifndef BOOST_HAS_MACRO_USE_FACET
            codecvt_ = & use_facet< codecvt_type >(loc_);
        #else
            codecvt_ = & _USE(loc_, codecvt_type);
        #endif
    }


template<typename T> 
struct is_dereferenceable 
    BOOST_TT_AUX_BOOL_C_BASE(is_dereferenceable_::impl<T>::value)
{ 
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(is_dereferenceable_::impl<T>::value)
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_dereferenceable,(T))
};

    path() : narrow_(), wide_(), is_wide_(false) { }

    path(const char* p) : narrow_(p), wide_(), is_wide_(false) { }

    template<typename Path>
    explicit path(const Path& p, typename Path::external_string_type* = 0)
    {
        init(p.external_file_string());
    }

    template<typename Path>
    explicit path(const Path& p, typename Path::codecvt_type* = 0)
    {
        init(p.native());
    }

    path(const path& p) 
        : narrow_(p.narrow_), wide_(p.wide_), is_wide_(p.is_wide_) 
        { }

    path& operator=(const path& p)
    {
        narrow_ = p.narrow_;
        wide_ = p.wide_;
        is_wide_ = p.is_wide_;
        return *this;
    }

    path& operator=(const char* p)
    {
        narrow_.assign(p);
        wide_.clear();
        is_wide_ = false;
        return *this;
    }

    template<typename Path>
    typename sfinae<typename Path::codecvt_type, path&>::type
        operator=(const Path& p)
    {
        init(p.native());
        return *this;
    }


    bool is_wide() const { return is_wide_; }

    const char* c_str() const { return narrow_.c_str(); }

    const wchar_t* c_wstr() const { return wide_.c_str(); }


    void init(std::string const& file_path)
    {
        narrow_ = file_path;
        wide_.clear();
        is_wide_ = false;
    }


inline bool operator==(const path& lhs, const path& rhs)
{
    return lhs.is_wide() ?
        rhs.is_wide() && std::wcscmp(lhs.c_wstr(), rhs.c_wstr()) == 0 :
        !rhs.is_wide() && std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
 
        prot_() { }

        template<typename V> prot_(V v) : U(v) { }
 
        pub_() { }

        template<typename V> pub_(V v) : U(v) { }
 
    access_control() { }

    template<typename U> explicit access_control(U u) : Base(u) { }

    codecvt_helper(std::size_t refs = 0) 
    #if !defined(BOOST_IOSTREAMS_NO_CODECVT_CTOR_FROM_SIZE_T)
        : std::codecvt<Intern, Extern, State>(refs)
    #else
        : std::codecvt<Intern, Extern, State>()
    #endif
        { }


    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!open_)
            open(src, BOOST_IOS::in);
        std::streamsize amt =
            end_ != -1 ?
                (std::min) (n, static_cast<std::streamsize>(end_ - pos_)) :
                n;
        std::streamsize result = 
            iostreams::read(this->component(), src, s, amt);
        if (result != -1)
            pos_ += result;
        return result;
    }


    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!open_)
            open(snk, BOOST_IOS::out);
        if (end_ != -1 && pos_ + n >= end_) {
            if(pos_ < end_)
                pos_ += iostreams::write(this->component(),
                    snk, s, end_ - pos_);
            boost::throw_exception(bad_write());
        }
        std::streamsize result = 
            iostreams::write(this->component(), snk, s, n);
        pos_ += result;
        return result;
    }


    template<typename Device>
    std::streampos seek(Device& dev, stream_offset off, BOOST_IOS::seekdir way)
    {
        stream_offset next;
        if (way == BOOST_IOS::beg) {
            next = beg_ + off;
        } else if (way == BOOST_IOS::cur) {
            next = pos_ + off;
        } else if (end_ != -1) {
            next = end_ + off;
        } else {
            // Restriction is half-open; seek relative to the actual end.
            pos_ = this->component().seek(dev, off, BOOST_IOS::end);
            if (pos_ < beg_)
                boost::throw_exception(bad_seek());
            return offset_to_position(pos_ - beg_);
        }
        if (next < beg_ || (end_ != -1 && next >= end_))
            boost::throw_exception(bad_seek());
        pos_ = this->component().seek(dev, next, BOOST_IOS::cur);
        return offset_to_position(pos_ - beg_);
    }


    template<typename Device>
    void close(Device& dev) 
    { 
        open_ = false;
        detail::close_all(this->component(), dev); 
    }

    template<typename Device>
    void open(Device& dev, BOOST_IOS::openmode which)
    {
        typedef typename is_convertible<mode, dual_use>::type is_dual_use;
        open_ = true;
        which = is_dual_use() ? which : (BOOST_IOS::in | BOOST_IOS::out);
        iostreams::skip(this->component(), dev, beg_, which);
    }

    restriction(param_type t, stream_offset off, stream_offset len = -1)
        : base_type(t, off, len)
        { }

    explicit non_blocking_adapter(Device& dev) : device_(dev) { }

    std::streamsize read(char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = iostreams::read(device_, s, n);
            if (amt == -1)
                break;
            result += amt;
        }
        return result != 0 ? result : -1;
    }

    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = 
                iostreams::write(device_, s + result, n - result);
            result += amt;
        }
        return result;    
    }

    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out )
    { return iostreams::seek(device_, off, way, which); }

    template<typename U>
    direct_adapter(const U& u) 
        : base_type(forward(u, is_direct<U>()))
        { }


    Direct& operator*() { return d_; }

    Direct* operator->() { return &d_; }


template<typename Device>
typename wrap_direct_traits<Device>::type
inline wrap_direct(Device dev) 
{ 
    typedef typename wrap_direct_traits<Device>::type type;
    return type(dev); 
}


template<typename Device>
inline Device& unwrap_direct(Device& d) { return d; }
  

template<typename Device>
inline Device& unwrap_direct(direct_adapter<Device>& d) { return *d; }


template<typename Direct>
direct_adapter_base<Direct>::direct_adapter_base(const Direct& d) : d_(d)
{
    init_input(is_convertible<category, input>());
    init_output(is_convertible<category, output>());
}


template<typename Direct>
void direct_adapter<Direct>::close() 
{ 
    BOOST_STATIC_ASSERT((!is_convertible<category, two_sequence>::value));
    detail::close_all(d_);
}

    explicit mode_adapter(const component_type& t) : t_(t) { }


    template<typename Device>
    void close(Device& dev)
    { detail::close_all(t_, dev); }


    template<typename Locale>
    void imbue(const Locale& loc)
    { iostreams::imbue(t_, loc); }

    explicit filter_adapter(param_type t) : t_(t) { }

    T& component() { return t_; }


    template<typename Device>
    void close(Device& dev) 
    { 
        detail::close_all(t_, dev); 
    }


    template<typename Device>
    void flush(Device& dev) 
    { 
        return iostreams::flush(t_, dev); 
    }


    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }


    std::streamsize optimal_buffer_size() const 
    { return iostreams::optimal_buffer_size(t_); }


template<typename Mode, typename Range>
range_adapter<Mode, Range>::range_adapter(const Range& rng)
    : first_(rng.begin()), cur_(rng.begin()), last_(rng.end()) { }


template<typename Mode, typename Range>
range_adapter<Mode, Range>::range_adapter(iterator first, iterator last)
    : first_(first), cur_(first), last_(last) { }

    explicit output_iterator_adapter(OutIt out) : out_(out) { }

    std::streamsize write(const char_type* s, std::streamsize n) 
    { 
        std::copy(s, s + n, out_); 
        return n; 
    }


    explicit concept_adapter(const reference_wrapper<T>& ref) : t_(ref.get())
    { BOOST_STATIC_ASSERT(is_std_io<T>::value); }

    explicit concept_adapter(const T& t) : t_(t)
    { BOOST_STATIC_ASSERT(!is_std_io<T>::value); }


    T& operator*() { return t_; }

    T* operator->() { return &t_; }


    std::streamsize read(char_type* s, std::streamsize n)
    { return this->read(s, n, (basic_null_source<char_type>*) 0); }


    std::streamsize write(const char_type* s, std::streamsize n)
    { return this->write(s, n, (basic_null_sink<char_type>*) 0); }


    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which )
    { 
        return this->seek( off, way, which, 
                           (basic_null_device<char_type, seekable>*) 0); 
    }


    void close(BOOST_IOS::openmode which)
    { this->close(which, (basic_null_device<char_type, seekable>*) 0); }


    template<typename Device>
    bool flush( Device* dev )
    {
        bool result = any_impl::flush(t_, dev);
        if (dev && dev->BOOST_IOSTREAMS_PUBSYNC() == -1)
            result = false;
        return result;
    }


    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }


    std::streamsize optimal_buffer_size() const
    { return iostreams::optimal_buffer_size(t_); }

    explicit device_adapter(param_type t) : t_(t) { }

    T& component() { return t_; }


    void close() 
    {
        detail::close_all(t_);
    }


    bool flush() 
    { 
        return iostreams::flush(t_); 
    }


    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }


    std::streamsize optimal_buffer_size() const 
    { return iostreams::optimal_buffer_size(t_); }


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::open
    (const T& t, std::streamsize buffer_size, std::streamsize pback_size)
{
    using namespace std;

    // Normalize buffer sizes.
    buffer_size =
        (buffer_size != -1) ?
        buffer_size :
        iostreams::optimal_buffer_size(t);
    pback_size =
        (pback_size != -1) ?
        pback_size :
        default_pback_buffer_size;

    // Construct input buffer.
    if (can_read()) {
        pback_size_ = (std::max)(std::streamsize(2), pback_size); // STLPort needs 2.
        std::streamsize size =
            pback_size_ +
            ( buffer_size ? buffer_size: 1 );
        in().resize(size);
        if (!shared_buffer())
            init_get_area();
    }

    // Construct output buffer.
    if (can_write() && !shared_buffer()) {
        if (buffer_size != 0)
            out().resize(buffer_size);
        init_put_area();
    }

    storage_.reset(wrapper(t));
    flags_ |= f_open;
    if (can_write() && buffer_size > 1)
        flags_ |= f_output_buffered;
    this->set_true_eof(false);
    this->set_needs_close();
}


template<typename T, typename Tr, typename Alloc, typename Mode>
inline bool indirect_streambuf<T, Tr, Alloc, Mode>::is_open() const
{ return (flags_ & f_open) != 0; }


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::close()
{
    using namespace std;
    base_type* self = this;
    detail::execute_all(
        detail::call_member_close(*self, BOOST_IOS::in),
        detail::call_member_close(*self, BOOST_IOS::out),
        detail::call_reset(storage_),
        detail::clear_flags(flags_)
    );
}


template<typename T, typename Tr, typename Alloc, typename Mode>
bool indirect_streambuf<T, Tr, Alloc, Mode>::auto_close() const
{ return (flags_ & f_auto_close) != 0; }


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::set_auto_close(bool close)
{ flags_ = (flags_ & ~f_auto_close) | (close ? f_auto_close : 0); }

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::imbue(const std::locale& loc)
{
    if (is_open()) {
        obj().imbue(loc);
        if (next_)
            next_->pubimbue(loc);
    }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::underflow()
{
    using namespace std;
    if (!gptr()) init_get_area();
    buffer_type& buf = in();
    if (gptr() < egptr()) return traits_type::to_int_type(*gptr());

    // Fill putback buffer.
    std::streamsize keep = 
        (std::min)( static_cast<std::streamsize>(gptr() - eback()),
                    pback_size_ );
    if (keep)
        traits_type::move( buf.data() + (pback_size_ - keep),
                           gptr() - keep, keep );

    // Set pointers to reasonable values in case read throws.
    setg( buf.data() + pback_size_ - keep,
          buf.data() + pback_size_,
          buf.data() + pback_size_ );

    // Read from source.
    std::streamsize chars =
        obj().read(buf.data() + pback_size_, buf.size() - pback_size_, next_);
    if (chars == -1) {
        this->set_true_eof(true);
        chars = 0;
    }
    setg(eback(), gptr(), buf.data() + pback_size_ + chars);
    return chars != 0 ?
        traits_type::to_int_type(*gptr()) :
        traits_type::eof();
}


template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::pbackfail(int_type c)
{
    if (gptr() != eback()) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    } else {
        boost::throw_exception(bad_putback());
    }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::overflow(int_type c)
{
    if ( (output_buffered() && pptr() == 0) ||
         (shared_buffer() && gptr() != 0) )
    {
        init_put_area();
    }
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (output_buffered()) {
            if (pptr() == epptr()) {
                sync_impl();
                if (pptr() == epptr())
                    return traits_type::eof();
            }
            *pptr() = traits_type::to_char_type(c);
            pbump(1);
        } else {
            char_type d = traits_type::to_char_type(c);
            if (obj().write(&d, 1, next_) != 1)
                return traits_type::eof();
        }
    }
    return traits_type::not_eof(c);
}


template<typename T, typename Tr, typename Alloc, typename Mode>
int indirect_streambuf<T, Tr, Alloc, Mode>::sync()
{
    try { // sync() is no-throw.
        sync_impl();
        obj().flush(next_);
        return 0;
    } catch (...) { return -1; }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
bool indirect_streambuf<T, Tr, Alloc, Mode>::strict_sync()
{
    try { // sync() is no-throw.
        sync_impl();
        return obj().flush(next_);
    } catch (...) { return false; }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekoff
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return seek_impl(off, way, which); }


template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekpos
    (pos_type sp, BOOST_IOS::openmode which)
{ 
    return seek_impl(position_to_offset(sp), BOOST_IOS::beg, which); 
}


template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seek_impl
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{
    if ( gptr() != 0 && way == BOOST_IOS::cur && which == BOOST_IOS::in && 
         eback() - gptr() <= off && off <= egptr() - gptr() ) 
    {   // Small seek optimization
        gbump(off);
        return obj().seek(0, BOOST_IOS::cur, BOOST_IOS::in, next_) -
               static_cast<off_type>(egptr() - gptr());
    }
    if (pptr() != 0) 
        this->BOOST_IOSTREAMS_PUBSYNC(); // sync() confuses VisualAge 6.
    if (way == BOOST_IOS::cur && gptr())
        off -= static_cast<off_type>(egptr() - gptr());
    setg(0, 0, 0);
    setp(0, 0);
    return obj().seek(off, way, which, next_);
}


template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::set_next
    (streambuf_type* next)
{ next_ = next; }


template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::close_impl
    (BOOST_IOS::openmode which)
{
    if (which == BOOST_IOS::in && is_convertible<Mode, input>::value) {
        setg(0, 0, 0);
    }
    if (which == BOOST_IOS::out && is_convertible<Mode, output>::value) {
        sync();
        setp(0, 0);
    }
    if ( !is_convertible<category, dual_use>::value ||
         is_convertible<Mode, input>::value == (which == BOOST_IOS::in) )
    {
        obj().close(which, next_);
    }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::sync_impl()
{
    std::streamsize avail, amt;
    if ((avail = static_cast<std::streamsize>(pptr() - pbase())) > 0) {
        if ((amt = obj().write(pbase(), avail, next())) == avail)
            setp(out().begin(), out().end());
        else {
            const char_type* ptr = pptr();
            setp(out().begin() + amt, out().end());
            pbump(ptr - pptr());
        }
    }
}


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_get_area()
{
    if (shared_buffer() && pptr() != 0) {
        sync_impl();
        setp(0, 0);
    }
    setg(in().begin(), in().begin(), in().begin());
}


template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_put_area()
{
    using namespace std;
    if (shared_buffer() && gptr() != 0)
        setg(0, 0, 0);
    if (output_buffered())
        setp(out().begin(), out().end());
    else
        setp(0, 0);
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::open
    (const T& t, std::streamsize, std::streamsize)
{
    storage_.reset(t);
    init_input(category());
    init_output(category());
    setg(0, 0, 0);
    setp(0, 0);
    this->set_needs_close();
}


template<typename T, typename Tr>
bool direct_streambuf<T, Tr>::is_open() const 
{ return ibeg_ != 0 || obeg_ != 0; }


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close() 
{ 
    base_type* self = this;
    detail::execute_all( detail::call_member_close(*self, BOOST_IOS::in),
                         detail::call_member_close(*self, BOOST_IOS::out),
                         detail::call_reset(storage_) );
}


template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::underflow()
{
    if (!ibeg_) 
        boost::throw_exception(cant_read());
    if (!gptr()) 
        init_get_area();
    return gptr() != iend_ ? 
        traits_type::to_int_type(*gptr()) : 
        traits_type::eof();
}


template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::pbackfail(int_type c)
{
    using namespace std;
    if (!ibeg_) 
        boost::throw_exception(cant_read());
    if (gptr() != 0 && gptr() != ibeg_) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    }
    boost::throw_exception(bad_putback());
}


template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::overflow(int_type c)
{
    using namespace std;
    if (!obeg_)
        boost::throw_exception(BOOST_IOSTREAMS_FAILURE("no write access"));
    if (!pptr()) init_put_area();
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (pptr() == oend_)
            boost::throw_exception(
                BOOST_IOSTREAMS_FAILURE("write area exhausted")
            );
        *pptr() = traits_type::to_char_type(c);
        pbump(1);
        return c;
    }
    return traits_type::not_eof(c);
}


template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekoff
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return seek_impl(off, way, which); }


template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekpos
    (pos_type sp, BOOST_IOS::openmode which)
{ 
    return seek_impl(position_to_offset(sp), BOOST_IOS::beg, which);
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close_impl(BOOST_IOS::openmode which)
{
    if (which == BOOST_IOS::in && ibeg_ != 0) {
        setg(0, 0, 0);
        ibeg_ = iend_ = 0;
    }
    if (which == BOOST_IOS::out && obeg_ != 0) {
        sync();
        setp(0, 0);
        obeg_ = oend_ = 0;
    }
    boost::iostreams::close(*storage_, which);
}


template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::pos_type direct_streambuf<T, Tr>::seek_impl
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{
    using namespace std;
    BOOST_IOS::openmode both = BOOST_IOS::in | BOOST_IOS::out;
    if (two_head() && (which & both) == both)
        boost::throw_exception(bad_seek());
    stream_offset result = -1;
    bool one = one_head();
    if (one && (pptr() != 0 || gptr()== 0))
        init_get_area(); // Switch to input mode, for code reuse.
    if (one || ((which & BOOST_IOS::in) != 0 && ibeg_ != 0)) {
        if (!gptr()) setg(ibeg_, ibeg_, iend_);
        ptrdiff_t next = 0;
        switch (way) {
        case BOOST_IOS::beg: next = off; break;
        case BOOST_IOS::cur: next = (gptr() - ibeg_) + off; break;
        case BOOST_IOS::end: next = (iend_ - ibeg_) + off; break;
        default: BOOST_ASSERT(0);
        }
        if (next < 0 || next > (iend_ - ibeg_))
            boost::throw_exception(bad_seek());
        setg(ibeg_, ibeg_ + next, iend_);
        result = next;
    }
    if (!one && (which & BOOST_IOS::out) != 0 && obeg_ != 0) {
        if (!pptr()) setp(obeg_, oend_);
        ptrdiff_t next = 0;
        switch (way) {
        case BOOST_IOS::beg: next = off; break;
        case BOOST_IOS::cur: next = (pptr() - obeg_) + off; break;
        case BOOST_IOS::end: next = (oend_ - obeg_) + off; break;
        default: BOOST_ASSERT(0);
        }
        if (next < 0 || next > (oend_ - obeg_))
            boost::throw_exception(bad_seek());
        pbump(static_cast<int>(next - (pptr() - obeg_)));
        result = next;
    }
    return offset_to_position(result);
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_input(input)
{
    std::pair<char_type*, char_type*> p = input_sequence(*storage_);
    ibeg_ = p.first;
    iend_ = p.second;
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_output(output)
{
    std::pair<char_type*, char_type*> p = output_sequence(*storage_);
    obeg_ = p.first;
    oend_ = p.second;
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_get_area()
{
    setg(ibeg_, ibeg_, iend_);
    if (one_head() && pptr()) {
        gbump(static_cast<int>(pptr() - obeg_));
        setp(0, 0);
    }
}


template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_put_area()
{
    setp(obeg_, oend_);
    if (one_head() && gptr()) {
        pbump(static_cast<int>(gptr() - ibeg_));
        setg(0, 0, 0);
    }
}


template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::one_head() const
{ return ibeg_ && obeg_ && ibeg_ == obeg_; }


template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::two_head() const
{ return ibeg_ && obeg_ && ibeg_ != obeg_; }

    chainbuf() { client_type::set_chain(&chain_); }

    int_type underflow() 
        { sentry t(this); return translate(delegate().underflow()); }

    int_type pbackfail(int_type c)
        { sentry t(this); return translate(delegate().pbackfail(c)); }

    std::streamsize xsgetn(char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsgetn(s, n); }

    int_type overflow(int_type c)
        { sentry t(this); return translate(delegate().overflow(c)); }

    std::streamsize xsputn(const char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsputn(s, n); }

    int sync() { sentry t(this); return delegate().sync(); }

    pos_type seekoff( off_type off, BOOST_IOS::seekdir way,
                      BOOST_IOS::openmode which =
                          BOOST_IOS::in | BOOST_IOS::out )
        { sentry t(this); return delegate().seekoff(off, way, which); }

    pos_type seekpos( pos_type sp,
                      BOOST_IOS::openmode which =
                          BOOST_IOS::in | BOOST_IOS::out )
        { sentry t(this); return delegate().seekpos(sp, which); }

    static typename chain_traits::int_type 
    translate(typename std_traits::int_type c)
        { return translate_int_type<std_traits, chain_traits>(c); }


    delegate_type& delegate() 
        { return static_cast<delegate_type&>(chain_.front()); }

    void get_pointers()
        {
            this->setg(delegate().eback(), delegate().gptr(), delegate().egptr());
            this->setp(delegate().pbase(), delegate().epptr());
            this->pbump((int) (delegate().pptr() - delegate().pbase()));
        }

    void set_pointers()
        {
            delegate().setg(this->eback(), this->gptr(), this->egptr());
            delegate().setp(this->pbase(), this->epptr());
            delegate().pbump((int) (this->pptr() - this->pbase()));
        }

        sentry(chainbuf<Chain, Mode, Access>* buf) : buf_(buf)
            { buf_->set_pointers(); }

        ~sentry() { buf_->get_pointers(); }

    linked_streambuf() : flags_(0) { }

    void set_true_eof(bool eof) 
    { 
        flags_ = (flags_ & ~f_true_eof) | (eof ? f_true_eof : 0); 
    }

    bool true_eof() const { return (flags_ & f_true_eof) != 0; }

    void close(BOOST_IOS::openmode which)
    {
        if ( which == BOOST_IOS::in && 
            (flags_ & f_input_closed) == 0 )
        {
            flags_ |= f_input_closed;
            close_impl(which);
        }
        if ( which == BOOST_IOS::out && 
            (flags_ & f_output_closed) == 0 )
        {
            flags_ |= f_output_closed;
            close_impl(which);
        }
    }

    void set_needs_close()
    {
        flags_ &= ~(f_input_closed | f_output_closed);
    }

    virtual void set_next(linked_streambuf<Ch, Tr>* /* next */) { }


template<typename T>
void close(T& t) { detail::close_all(t); }


template<typename T>
inline std::streamsize
read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::read_device_impl<T>::inner<unwrapped>::read(detail::unwrap(t), s, n);
}


template<typename T>
bool putback(T& t, typename char_type_of<T>::type c)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::read_device_impl<T>::inner<unwrapped>::putback(detail::unwrap(t), c);
}

inline std::streamsize check_eof(std::streamsize n) { return n != 0 ? n : -1; }

    template<typename T>
    static bool true_eof(T& t) { return t.true_eof(); }

    template<typename T>
    static bool true_eof(T& t) { return true; }


template<typename T>
inline bool true_eof(T& t)
{
    const bool linked = is_linked<T>::value;
    return true_eof_impl<linked>::true_eof(t);
}


template<typename T>
bool put(T& t, typename char_type_of<T>::type c)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::write_device_impl<T>::inner<unwrapped>::put(detail::unwrap(t), c);
}


template<typename T>
inline std::streamsize write
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{
    typedef typename detail::unwrapped_type<T>::type unwrapped;
    return detail::write_device_impl<T>::inner<unwrapped>::write(detail::unwrap(t), s, n);
}

    mapped_file_params_base()
        : flags(static_cast<mapped_file_base::mapmode>(0)), 
          mode(), offset(0), length(static_cast<std::size_t>(-1)), 
          new_file_size(0), hint(0)
        { }

    basic_mapped_file_params() { }

    explicit basic_mapped_file_params(const Path& p) : path(p) { }

    template<typename PathT>
    explicit basic_mapped_file_params(const PathT& p) : path(p) { }

    basic_mapped_file_params(const basic_mapped_file_params& other)
        : base_type(other), path(other.path)
        { }

    template<typename PathT>
    basic_mapped_file_params(const basic_mapped_file_params<PathT>& other)
        : base_type(other), path(other.path)
        { }


template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (char_type* begin, char_type* end) 
    : begin_(begin), end_(end) 
    { }


template<typename Mode, typename Ch>
array_adapter<Mode, Ch>::array_adapter
    (const char_type* begin, const char_type* end) 
    : begin_(const_cast<char_type*>(begin)),  // Treated as read-only.
      end_(const_cast<char_type*>(end))       // Treated as read-only.
{ BOOST_STATIC_ASSERT((!is_convertible<Mode, output>::value)); }

    back_insert_device(Container& cnt) : container(&cnt) { }

    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        container->insert(container->end(), s, s + n); 
        return n;
    }


template<typename Container>
back_insert_device<Container> back_inserter(Container& cnt)
{ return back_insert_device<Container>(cnt); }

    std::streamsize read(Ch*, std::streamsize) { return 0; }

    std::streamsize write(const Ch*, std::streamsize n) { return n; }

    std::streampos seek( stream_offset, BOOST_IOS::seekdir,
                         BOOST_IOS::openmode = 
                             BOOST_IOS::in | BOOST_IOS::out ) 
    { return -1; }

    void close() { }

    void imbue(const std::locale& loc) { pimpl_->file_.pubimbue(loc);  }

        impl(const std::string& path, BOOST_IOS::openmode mode)
            { file_.open(path.c_str(), mode); }

        ~impl() { if (file_.is_open()) file_.close(); }

    basic_file_source( const std::string& path,
                       BOOST_IOS::openmode mode = 
                           BOOST_IOS::in )
        : basic_file<Ch>(path, mode & ~BOOST_IOS::out, BOOST_IOS::in)
        { }

    void open( const std::string& path,
               BOOST_IOS::openmode mode = BOOST_IOS::in )
    {
        basic_file<Ch>::open(path, mode & ~BOOST_IOS::out, BOOST_IOS::in);
    }

    basic_file_sink( const std::string& path,
                     BOOST_IOS::openmode mode = BOOST_IOS::out )
        : basic_file<Ch>(path, mode & ~BOOST_IOS::in, BOOST_IOS::out)
        { }

    void open( const std::string& path,
               BOOST_IOS::openmode mode = BOOST_IOS::out )
    {
        basic_file<Ch>::open(path, mode & ~BOOST_IOS::in, BOOST_IOS::out);
    }


template<typename Ch>
inline bool basic_file<Ch>::putback(char_type c)
{ 
    return !!pimpl_->file_.sputbackc(c); 
}


template<typename Ch>
bool basic_file<Ch>::is_open() const { return pimpl_->file_.is_open(); }


template<typename Ch>
void basic_file<Ch>::close() { pimpl_->file_.close(); }


template<typename Ch>
bool basic_file<Ch>::flush()
{ return pimpl_->file_.BOOST_IOSTREAMS_PUBSYNC() == 0; }

    zlib_params( int level           = zlib::default_compression,
                 int method          = zlib::deflated,
                 int window_bits     = zlib::default_window_bits, 
                 int mem_level       = zlib::default_mem_level, 
                 int strategy        = zlib::default_strategy,
                 bool noheader       = zlib::default_noheader,
                 bool calculate_crc  = zlib::default_crc )
        : level(level), method(method), window_bits(window_bits),
          mem_level(mem_level), strategy(strategy),  
          noheader(noheader), calculate_crc(calculate_crc)
        { }


template<typename Alloc, typename Base>
void* zlib_allocator<Alloc, Base>::allocate
    (void* self, zlib::uint items, zlib::uint size)
{ 
    size_type len = items * size;
    char* ptr = 
        static_cast<allocator_type*>(self)->allocate
            (len + sizeof(size_type)
            #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
                , (char*)0
            #endif
            );
    *reinterpret_cast<size_type*>(ptr) = len;
    return ptr + sizeof(size_type);
}


template<typename Alloc, typename Base>
void zlib_allocator<Alloc, Base>::deallocate(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}

    explicit basic_counter(int first_line = 0, int first_char = 0)
        : lines_(first_line), chars_(first_char)
        { }

    int lines() const { return lines_; }

    int characters() const { return chars_; }

    std::streamsize optimal_buffer_size() const { return 0; }


    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::read(src, s, n);
        if (result == -1)
            return -1;
        lines_ += std::count(s, s + result, char_traits<Ch>::newline());
        chars_ += result;
        return result;
    }


    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        std::streamsize result = iostreams::write(snk, s, n);
        lines_ += std::count(s, s + result, char_traits<Ch>::newline());
        chars_ += result;
        return result;
    }

    gzip_params( int level              = gzip::default_compression,
                 int method             = gzip::deflated,
                 int window_bits        = gzip::default_window_bits,
                 int mem_level          = gzip::default_mem_level,
                 int strategy           = gzip::default_strategy,
                 std::string file_name  = "",
                 std::string comment    = "",
                 std::time_t mtime      = 0 )
        : zlib_params(level, method, window_bits, mem_level, strategy),
          file_name(file_name), comment(comment), mtime(mtime)
        { }

    explicit gzip_error(int error)
        : BOOST_IOSTREAMS_FAILURE("gzip error"),
          error_(error), zlib_error_code_(zlib::okay) { }

    int error() const { return error_; }

    int zlib_error_code() const { return zlib_error_code_; }

    bool is_posix() const
    {
        return !is_mixed() && (flags_ & newline::posix) != 0;
    }

    bool is_dos() const
    {
        return !is_mixed() && (flags_ & newline::dos) != 0;
    }

    bool is_mac() const
    {
        return !is_mixed() && (flags_ & newline::mac) != 0;
    }

    bool is_mixed_posix() const { return (flags_ & newline::posix) != 0; }

    bool is_mixed_dos() const { return (flags_ & newline::dos) != 0; }

    bool is_mixed_mac() const { return (flags_ & newline::mac) != 0; }

    bool is_mixed() const
    {
        int platform =
            (flags_ & newline::posix) != 0 ?
                newline::posix :
                (flags_ & newline::dos) != 0 ?
                    newline::dos :
                    (flags_ & newline::mac) != 0 ?
                        newline::mac :
                        0;
        return (flags_ & ~platform & newline::platform_mask) != 0;
    }

    bool has_final_newline() const
    {
        return (flags_ & newline::final_newline) != 0;
    }

    newline_base(int flags) : flags_(flags) { }

    newline_error(int flags)
        : BOOST_IOSTREAMS_FAILURE("bad line endings"),
          detail::newline_base(flags)
        { }


    explicit newline_filter(int target) : flags_(target)
    {
        if ( target != iostreams::newline::posix &&
             target != iostreams::newline::dos &&
             target != iostreams::newline::mac )
        {
            boost::throw_exception(std::logic_error("bad flags"));
        }
    }


    template<typename Source>
    int get(Source& src)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        BOOST_ASSERT((flags_ & f_write) == 0);
        flags_ |= f_read;

        if (flags_ & (f_has_LF | f_has_EOF)) {
            if (flags_ & f_has_LF)
                return newline();
            else
                return EOF;
        }

        int c =
            (flags_ & f_has_CR) == 0 ?
                iostreams::get(src) :
                CR;

        if (c == WOULD_BLOCK )
            return WOULD_BLOCK;

        if (c == CR) {
            flags_ |= f_has_CR;

            int d;
            if ((d = iostreams::get(src)) == WOULD_BLOCK)
                return WOULD_BLOCK;

            if (d == LF) {
                flags_ &= ~f_has_CR;
                return newline();
            }

            if (d == EOF) {
                flags_ |= f_has_EOF;
            } else {
                iostreams::putback(src, d);
            }

            flags_ &= ~f_has_CR;
            return newline();
        }

        if (c == LF)
            return newline();

        return c;
    }


    template<typename Sink>
    bool put(Sink& dest, char c)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        BOOST_ASSERT((flags_ & f_read) == 0);
        flags_ |= f_write;

        if ((flags_ & f_has_LF) != 0)
            return c == LF ?
                newline(dest) :
                newline(dest) && this->put(dest, c);

        if (c == LF)
           return newline(dest);

        if ((flags_ & f_has_CR) != 0)
            return newline(dest) ?
                this->put(dest, c) :
                false;

        if (c == CR) {
            flags_ |= f_has_CR;
            return true;
        }

        return iostreams::put(dest, c);
    }


    template<typename Sink>
    void close(Sink& dest, BOOST_IOS::openmode)
    {
        typedef typename iostreams::category_of<Sink>::type category;
        if ((flags_ & f_write) != 0 && (flags_ & f_has_CR) != 0)
            newline_if_sink(dest);
        flags_ &= ~f_has_LF; // Restore original flags.
    }

    int newline()
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        switch (flags_ & iostreams::newline::platform_mask) {
        case iostreams::newline::posix:
            return LF;
        case iostreams::newline::mac:
            return CR;
        case iostreams::newline::dos:
            if (flags_ & f_has_LF) {
                flags_ &= ~f_has_LF;
                return LF;
            } else {
                flags_ |= f_has_LF;
                return CR;
            }
        }
        return BOOST_IOSTREAMS_ASSERT_UNREACHABLE(0);
    }

    template<typename Sink>
    bool newline(Sink& dest)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        bool success = false;
        switch (flags_ & iostreams::newline::platform_mask) {
        case iostreams::newline::posix:
            success = boost::iostreams::put(dest, LF);
            break;
        case iostreams::newline::mac:
            success = boost::iostreams::put(dest, CR);
            break;
        case iostreams::newline::dos:
            if ((flags_ & f_has_LF) != 0) {
                if ((success = boost::iostreams::put(dest, LF)))
                    flags_ &= ~f_has_LF;
            } else if (boost::iostreams::put(dest, CR)) {
                if (!(success = boost::iostreams::put(dest, LF)))
                    flags_ |= f_has_LF;
            }
            break;
        }
        if (success)
            flags_ &= ~f_has_CR;
        return success;
    }

    template<typename Device>
    void newline_if_sink(Device& dest) 
    { 
        typedef typename iostreams::category_of<Device>::type category;
        newline_if_sink(dest, is_convertible<category, output>()); 
    }

    explicit newline_checker(int target = newline::mixed)
        : detail::newline_base(0), target_(target), open_(false)
        { }

    template<typename Source>
    int get(Source& src)
    {
        using newline::CR;
        using newline::LF;

        if (!open_) {
            open_ = true;
            source() = 0;
        }

        int c;
        if ((c = iostreams::get(src)) == WOULD_BLOCK)
            return WOULD_BLOCK;

        // Update source flags.
        if (c != EOF)
            source() &= ~f_line_complete;
        if ((source() & f_has_CR) != 0) {
            if (c == LF) {
                source() |= newline::dos;
                source() |= f_line_complete;
            } else {
                source() |= newline::mac;
                if (c == EOF)
                    source() |= f_line_complete;
            }
        } else if (c == LF) {
            source() |= newline::posix;
            source() |= f_line_complete;
        }
        source() = (source() & ~f_has_CR) | (c == CR ? f_has_CR : 0);

        // Check for errors.
        if ( c == EOF &&
            (target_ & newline::final_newline) != 0 &&
            (source() & f_line_complete) == 0 )
        {
            fail();
        }
        if ( (target_ & newline::platform_mask) != 0 &&
             (source() & ~target_ & newline::platform_mask) != 0 )
        {
            fail();
        }

        return c;
    }


    template<typename Sink>
    bool put(Sink& dest, int c)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        if (!open_) {
            open_ = true;
            source() = 0;
        }

        if (!iostreams::put(dest, c))
            return false;

         // Update source flags.
        source() &= ~f_line_complete;
        if ((source() & f_has_CR) != 0) {
            if (c == LF) {
                source() |= newline::dos;
                source() |= f_line_complete;
            } else {
                source() |= newline::mac;
            }
        } else if (c == LF) {
            source() |= newline::posix;
            source() |= f_line_complete;
        }
        source() = (source() & ~f_has_CR) | (c == CR ? f_has_CR : 0);

        // Check for errors.
        if ( (target_ & newline::platform_mask) != 0 &&
             (source() & ~target_ & newline::platform_mask) != 0 )
        {
            fail();
        }

        return true;
    }


    template<typename Sink>
    void close(Sink&, BOOST_IOS::openmode)
    {
        using iostreams::newline::final_newline;

        // Update final_newline flag.
        if ( (source() & f_has_CR) != 0 ||
             (source() & f_line_complete) != 0 )
        {
            source() |= final_newline;
        }

        // Clear non-sticky flags.
        source() &= ~(f_has_CR | f_line_complete);

        // Check for errors.
        if ( (target_ & final_newline) != 0 &&
             (source() & final_newline) == 0 )
        {
            fail();
        }
    }

    void fail() { boost::throw_exception(newline_error(source())); }

    int& source() { return flags_; }

    int source() const { return flags_; }

    std::streamsize rand(int inc) 
    { 
        return (std::rand() * inc + 1) / RAND_MAX; 
    }

    explicit non_blocking_source( const std::string& data, 
                                  std::streamsize inc = default_increment ) 
        : data_(data), inc_(inc), pos_(0)
        { }

    std::streamsize read(char* s, std::streamsize n)
    {
        if (pos_ == static_cast<std::streamsize>(data_.size()))
            return -1;
        std::streamsize avail = 
            (std::min) (n, static_cast<std::streamsize>(data_.size() - pos_));
        std::streamsize amt = (std::min) (rand(inc_), avail);
        if (amt)
            std::memcpy(s, data_.c_str() + pos_, amt);
        pos_ += amt;
        return amt;
    }


    bool putback(char c)
    {
        if (pos_ > 0) {
            data_[--pos_] = c;
            return true;
        }
        return false;
    }

    non_blocking_sink( std::string& dest,
                       std::streamsize inc = default_increment ) 
        : dest_(dest), inc_(inc) 
        { }

    std::streamsize write(const char* s, std::streamsize n)
    {
        std::streamsize amt = (std::min) (rand(inc_), n);
        dest_.insert(dest_.end(), s, s + amt);
        return amt;
    }


template<typename Filter>
bool test_input_filter( Filter filter, 
                        const std::string& input, 
                        const std::string& output, 
                        mpl::true_ )
{
    for ( int inc = default_increment; 
          inc < default_increment * 40; 
          inc += default_increment )
    {
        non_blocking_source  src(input, inc);
        std::string          dest;
        iostreams::copy(compose(filter, src), iostreams::back_inserter(dest));
        if (dest != output)
            return false;
    }
    return true;
}


template<typename Filter, typename Source1, typename Source2>
bool test_input_filter( Filter filter, 
                        const Source1& input, 
                        const Source2& output )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_input_filter( filter, input, output,    
                              is_string<Source1>() );
}


template<typename Filter>
bool test_output_filter( Filter filter, 
                         const std::string& input, 
                         const std::string& output, 
                         mpl::true_ )
{
    for ( int inc = default_increment; 
          inc < default_increment * 40; 
          inc += default_increment )
    {
        array_source  src(input.data(), input.data() + input.size());
        std::string   dest;
        iostreams::copy(src, compose(filter, non_blocking_sink(dest, inc)));
        if (dest != output )
            return false;
    }
    return true;
}


template<typename Filter, typename Source1, typename Source2>
bool test_output_filter( Filter filter, 
                         const Source1& input, 
                         const Source2& output )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_output_filter( filter, input, output,    
                               is_string<Source1>() );
}


template<typename OutputFilter, typename InputFilter>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const std::string& data, 
                       mpl::true_ )
{
    for ( int inc = default_increment; 
          inc <= default_increment * 40; 
          inc += default_increment )
    {
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(src, compose(out, non_blocking_sink(temp, inc)));
            iostreams::copy( 
                compose(in, non_blocking_source(temp, inc)),
                iostreams::back_inserter(dest)
            );
            if (dest != data)
                return false;
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(src, compose(out, non_blocking_sink(temp, inc)));
            // truncate the file, this should not loop, it may throw
            // std::ios_base::failure, which we swallow.
            try {
                temp.resize(temp.size() / 2);
                iostreams::copy( 
                    compose(in, non_blocking_source(temp, inc)),
                    iostreams::back_inserter(dest)
                );
            } catch(std::ios_base::failure&) {}
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(compose(out, src), non_blocking_sink(temp, inc));
            iostreams::copy( 
                non_blocking_source(temp, inc),
                compose(in, iostreams::back_inserter(dest))
            );
            if (dest != data)
                return false;
        }
        {
            array_source  src(data.data(), data.data() + data.size());
            std::string   temp;
            std::string   dest;
            iostreams::copy(compose(out, src), non_blocking_sink(temp, inc));
            // truncate the file, this should not loop, it may throw
            // std::ios_base::failure, which we swallow.
            try {
                temp.resize(temp.size() / 2);
                iostreams::copy( 
                    non_blocking_source(temp, inc),
                    compose(in, iostreams::back_inserter(dest))
                );
            } catch(std::ios_base::failure&) {}
        }
    }
    return true;
}


template<typename OutputFilter, typename InputFilter, typename Source>
bool test_filter_pair( OutputFilter out, 
                       InputFilter in, 
                       const Source& data )
{
    // Use tag dispatch to compensate for bad overload resolution.
    return test_filter_pair(out, in, data, is_string<Source>());
}

    bzip2_params( int block_size   = bzip2::default_block_size,
                  int work_factor  = bzip2::default_work_factor )
        : block_size(block_size), work_factor(work_factor)
        { }

    bzip2_params(bool small)
        : small(small), work_factor(0)
        { }


template<typename Alloc, typename Base>
void* bzip2_allocator<Alloc, Base>::allocate(void* self, int items, int size)
{ 
    size_type len = items * size;
    char* ptr = 
        static_cast<allocator_type*>(self)->allocate
            (len + sizeof(size_type)
            #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
                , (char*)0
            #endif
            );
    *reinterpret_cast<size_type*>(ptr) = len;
    return ptr + sizeof(size_type);
}


template<typename Alloc, typename Base>
void bzip2_allocator<Alloc, Base>::deallocate(void* self, void* address)
{ 
    char* ptr = reinterpret_cast<char*>(address) - sizeof(size_type);
    size_type len = *reinterpret_cast<size_type*>(ptr) + sizeof(size_type);
    static_cast<allocator_type*>(self)->deallocate(ptr, len); 
}
