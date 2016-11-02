
    static const char* registration_file() { return __FILE__; }


        enqueued_record(enqueued_record const& that) : m_timestamp(that.m_timestamp), m_record(that.m_record)
        {
        }

        enqueued_record(BOOST_RV_REF(enqueued_record) that) :
            m_timestamp(that.m_timestamp),
            m_record(boost::move(that.m_record))
        {
        }

        enqueued_record& operator= (BOOST_COPY_ASSIGN_REF(enqueued_record) that)
        {
            m_timestamp = that.m_timestamp;
            m_record = that.m_record;
            return *this;
        }

    posix_time::time_duration get_ordering_window() const
    {
        return posix_time::milliseconds(m_ordering_window);
    }

    static posix_time::time_duration get_default_ordering_window()
    {
        // The main idea behind this parameter is that the ordering window should be large enough
        // to allow the frontend to order records from different threads on an attribute
        // that contains system time. Thus this value should be:
        // * No less than the minimum time resolution quant that Boost.DateTime provides on the current OS.
        //   For instance, on Windows it defaults to around 15-16 ms.
        // * No less than thread switching quant on the current OS. For now 30 ms is large enough window size to
        //   switch threads on any known OS. It can be tuned for other platforms as needed.
        return posix_time::milliseconds(30);
    }

    template< typename ArgsT >
    explicit bounded_ordering_queue(ArgsT const& args) :
        m_ordering_window(args[keywords::ordering_window || &bounded_ordering_queue::get_default_ordering_window].total_milliseconds()),
        m_queue(args[keywords::order]),
        m_interruption_requested(false)
    {
    }

    void enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);
        std::size_t size = m_queue.size();
        for (; size >= MaxQueueSizeV; size = m_queue.size())
        {
            if (!overflow_strategy::on_overflow(rec, lock))
                return;
        }

        m_queue.push(enqueued_record(rec));
        if (size == 0)
            m_cond.notify_one();
    }

    bool try_enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex, try_to_lock);
        if (lock.owns_lock())
        {
            const std::size_t size = m_queue.size();

            // Do not invoke the bounding strategy in case of overflow as it may block
            if (size < MaxQueueSizeV)
            {
                m_queue.push(enqueued_record(rec));
                if (size == 0)
                    m_cond.notify_one();
                return true;
            }
        }

        return false;
    }

    bool try_dequeue_ready(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
            enqueued_record const& elem = m_queue.top();
            if (static_cast< uint64_t >((now - elem.m_timestamp).milliseconds()) >= m_ordering_window)
            {
                // We got a new element
                rec = elem.m_record;
                m_queue.pop();
                if (size == MaxQueueSizeV)
                    overflow_strategy::on_queue_space_available();
                return true;
            }
        }

        return false;
    }

    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            enqueued_record const& elem = m_queue.top();
            rec = elem.m_record;
            m_queue.pop();
            if (size == MaxQueueSizeV)
                overflow_strategy::on_queue_space_available();
            return true;
        }

        return false;
    }

    bool dequeue_ready(record_view& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);

        while (!m_interruption_requested)
        {
            const std::size_t size = m_queue.size();
            if (size > 0)
            {
                const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
                enqueued_record const& elem = m_queue.top();
                const uint64_t difference = (now - elem.m_timestamp).milliseconds();
                if (difference >= m_ordering_window)
                {
                    rec = elem.m_record;
                    m_queue.pop();
                    if (size == MaxQueueSizeV)
                        overflow_strategy::on_queue_space_available();
                    return true;
                }
                else
                {
                    // Wait until the element becomes ready to be processed
                    m_cond.timed_wait(lock, posix_time::milliseconds(m_ordering_window - difference));
                }
            }
            else
            {
                m_cond.wait(lock);
            }
        }
        m_interruption_requested = false;

        return false;
    }

    void interrupt_dequeue()
    {
        lock_guard< mutex_type > lock(m_mutex);
        m_interruption_requested = true;
        overflow_strategy::interrupt();
        m_cond.notify_one();
    }

    explicit rotation_at_time_interval(posix_time::time_duration const& interval) :
        m_Interval(interval)
    {
        BOOST_ASSERT(!interval.is_special());
        BOOST_ASSERT(interval.total_seconds() > 0);
    }

    template< typename PathT >
    void set_file_name_pattern(PathT const& pattern)
    {
        set_file_name_pattern_internal(filesystem::path(pattern));
    }

    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            filesystem::path(args[keywords::file_name | filesystem::path()]),
            args[keywords::open_mode | (std::ios_base::trunc | std::ios_base::out)],
            args[keywords::rotation_size | (std::numeric_limits< uintmax_t >::max)()],
            args[keywords::time_based_rotation | time_based_rotation_predicate()],
            args[keywords::auto_flush | false]);
    }

    bounded_fifo_queue() : m_interruption_requested(false)
    {
    }

    template< typename ArgsT >
    explicit bounded_fifo_queue(ArgsT const&) : m_interruption_requested(false)
    {
    }

    void enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);
        std::size_t size = m_queue.size();
        for (; size >= MaxQueueSizeV; size = m_queue.size())
        {
            if (!overflow_strategy::on_overflow(rec, lock))
                return;
        }

        m_queue.push(rec);
        if (size == 0)
            m_cond.notify_one();
    }

    bool try_enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex, try_to_lock);
        if (lock.owns_lock())
        {
            const std::size_t size = m_queue.size();

            // Do not invoke the bounding strategy in case of overflow as it may block
            if (size < MaxQueueSizeV)
            {
                m_queue.push(rec);
                if (size == 0)
                    m_cond.notify_one();
                return true;
            }
        }

        return false;
    }

    bool try_dequeue_ready(record_view& rec)
    {
        return try_dequeue(rec);
    }

    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            rec.swap(m_queue.front());
            m_queue.pop();
            if (size == MaxQueueSizeV)
                overflow_strategy::on_queue_space_available();
            return true;
        }

        return false;
    }

    bool dequeue_ready(record_view& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);

        while (!m_interruption_requested)
        {
            const std::size_t size = m_queue.size();
            if (size > 0)
            {
                rec.swap(m_queue.front());
                m_queue.pop();
                if (size == MaxQueueSizeV)
                    overflow_strategy::on_queue_space_available();
                return true;
            }
            else
            {
                m_cond.wait(lock);
            }
        }
        m_interruption_requested = false;

        return false;
    }

    void interrupt_dequeue()
    {
        lock_guard< mutex_type > lock(m_mutex);
        m_interruption_requested = true;
        overflow_strategy::interrupt();
        m_cond.notify_one();
    }


        enqueued_record(enqueued_record const& that) : m_timestamp(that.m_timestamp), m_record(that.m_record)
        {
        }

        enqueued_record(BOOST_RV_REF(enqueued_record) that) :
            m_timestamp(that.m_timestamp),
            m_record(boost::move(that.m_record))
        {
        }

        enqueued_record& operator= (BOOST_COPY_ASSIGN_REF(enqueued_record) that)
        {
            m_timestamp = that.m_timestamp;
            m_record = that.m_record;
            return *this;
        }

    posix_time::time_duration get_ordering_window() const
    {
        return posix_time::milliseconds(m_ordering_window);
    }

    static posix_time::time_duration get_default_ordering_window()
    {
        // The main idea behind this parameter is that the ordering window should be large enough
        // to allow the frontend to order records from different threads on an attribute
        // that contains system time. Thus this value should be:
        // * No less than the minimum time resolution quant that Boost.DateTime provides on the current OS.
        //   For instance, on Windows it defaults to around 15-16 ms.
        // * No less than thread switching quant on the current OS. For now 30 ms is large enough window size to
        //   switch threads on any known OS. It can be tuned for other platforms as needed.
        return posix_time::milliseconds(30);
    }

    template< typename ArgsT >
    explicit unbounded_ordering_queue(ArgsT const& args) :
        m_ordering_window(args[keywords::ordering_window || &unbounded_ordering_queue::get_default_ordering_window].total_milliseconds()),
        m_queue(args[keywords::order]),
        m_interruption_requested(false)
    {
    }

    void enqueue(record_view const& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        enqueue_unlocked(rec);
    }

    bool try_enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex, try_to_lock);
        if (lock.owns_lock())
        {
            enqueue_unlocked(rec);
            return true;
        }
        else
            return false;
    }

    bool try_dequeue_ready(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        if (!m_queue.empty())
        {
            const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
            enqueued_record const& elem = m_queue.top();
            if (static_cast< uint64_t >((now - elem.m_timestamp).milliseconds()) >= m_ordering_window)
            {
                // We got a new element
                rec = elem.m_record;
                m_queue.pop();
                return true;
            }
        }

        return false;
    }

    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        if (!m_queue.empty())
        {
            enqueued_record const& elem = m_queue.top();
            rec = elem.m_record;
            m_queue.pop();
            return true;
        }

        return false;
    }

    bool dequeue_ready(record_view& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);
        while (!m_interruption_requested)
        {
            if (!m_queue.empty())
            {
                const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
                enqueued_record const& elem = m_queue.top();
                const uint64_t difference = (now - elem.m_timestamp).milliseconds();
                if (difference >= m_ordering_window)
                {
                    // We got a new element
                    rec = elem.m_record;
                    m_queue.pop();
                    return true;
                }
                else
                {
                    // Wait until the element becomes ready to be processed
                    m_cond.timed_wait(lock, posix_time::milliseconds(m_ordering_window - difference));
                }
            }
            else
            {
                // Wait for an element to come
                m_cond.wait(lock);
            }
        }
        m_interruption_requested = false;

        return false;
    }

    void interrupt_dequeue()
    {
        lock_guard< mutex_type > lock(m_mutex);
        m_interruption_requested = true;
        m_cond.notify_one();
    }

    void enqueue_unlocked(record_view const& rec)
    {
        const bool was_empty = m_queue.empty();
        m_queue.push(enqueued_record(rec));
        if (was_empty)
            m_cond.notify_one();
    }

        explicit direct_severity_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }

        explicit custom_severity_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }

    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            args[keywords::facility | syslog::user],
#if !defined(BOOST_LOG_NO_ASIO)
            args[keywords::use_impl | syslog::udp_socket_based],
#else
            args[keywords::use_impl | syslog::native],
#endif
            args[keywords::ip_version | v4],
            args[keywords::ident | std::string()]);
    }

    inline event_id make_event_id(unsigned int id)
    {
        event_id iden = { id };
        return iden;
    }

    inline event_category make_event_category(unsigned short cat)
    {
        event_category category = { cat };
        return category;
    }

    unlocked_sink() :
        base_type(false),
        m_pBackend(boost::make_shared< sink_backend_type >())
    {
    }

    unbounded_fifo_queue() : m_interruption_requested(false)
    {
    }

    template< typename ArgsT >
    explicit unbounded_fifo_queue(ArgsT const&) : m_interruption_requested(false)
    {
    }

    void enqueue(record_view const& rec)
    {
        m_queue.push(rec);
        m_event.set_signalled();
    }

    bool try_enqueue(record_view const& rec)
    {
        // Assume the call never blocks
        enqueue(rec);
        return true;
    }

    bool try_dequeue_ready(record_view& rec)
    {
        return m_queue.try_pop(rec);
    }

    bool try_dequeue(record_view& rec)
    {
        return m_queue.try_pop(rec);
    }

    bool dequeue_ready(record_view& rec)
    {
        // Try the fast way first
        if (m_queue.try_pop(rec))
            return true;

        // Ok, we probably have to wait for new records
        while (true)
        {
            m_event.wait();
            if (m_interruption_requested)
            {
                m_interruption_requested = false;
                return false;
            }
            if (m_queue.try_pop(rec))
                return true;
        }
    }

    void interrupt_dequeue()
    {
        m_interruption_requested = true;
        m_event.set_signalled();
    }

    template< typename LockT >
    static bool on_overflow(record_view const&, LockT&)
    {
        return false;
    }

    static void on_queue_space_available()
    {
    }

    static void interrupt()
    {
    }

        explicit file_name_composer_adapter(formatter_type const& formatter, std::locale const& loc = std::locale()) :
            m_Formatter(formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(loc);
        }

        file_name_composer_adapter(file_name_composer_adapter const& that) :
            m_Formatter(that.m_Formatter),
            m_FormattingStream(m_FileName)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(that.m_FormattingStream.getloc());
        }

        file_name_composer_adapter& operator= (file_name_composer_adapter const& that)
        {
            m_Formatter = that.m_Formatter;
            return *this;
        }

        result_type operator() (record_view const& rec) const
        {
            boost::log::aux::cleanup_guard< stream_type > cleanup1(m_FormattingStream);
            boost::log::aux::cleanup_guard< result_type::string_type > cleanup2(m_FileName);

            m_Formatter(rec, m_FormattingStream);
            m_FormattingStream.flush();

            return result_type(m_FileName);
        }

    template< typename FormatterT >
    inline file_name_composer_adapter< FormatterT > as_file_name_composer(
        FormatterT const& fmt, std::locale const& loc = std::locale())
    {
        return file_name_composer_adapter< FormatterT >(fmt, loc);
    }

    template< typename ComposerT >
    void set_file_name_composer(ComposerT const& composer)
    {
        set_file_name_composer_internal(composer);
    }

        scoped_thread_id(frontend_mutex_type& mut, condition_variable_any& cond, thread::id& tid, bool volatile& sr)
            : m_Mutex(mut), m_Cond(cond), m_ThreadID(tid), m_StopRequested(sr)
        {
            lock_guard< frontend_mutex_type > lock(m_Mutex);
            if (m_ThreadID != thread::id())
                BOOST_LOG_THROW_DESCR(unexpected_call, "Asynchronous sink frontend already runs a record feeding thread");
            m_ThreadID = this_thread::get_id();
        }

        ~scoped_thread_id()
        {
            try
            {
                lock_guard< frontend_mutex_type > lock(m_Mutex);
                m_StopRequested = false;
                m_ThreadID = thread::id();
                m_Cond.notify_all();
            }
            catch (...)
            {
            }
        }

        explicit scoped_flag(frontend_mutex_type& mut, condition_variable_any& cond, volatile bool& f) :
            m_Mutex(mut), m_Cond(cond), m_Flag(f)
        {
        }

        ~scoped_flag()
        {
            try
            {
                lock_guard< frontend_mutex_type > lock(m_Mutex);
                m_Flag = false;
                m_Cond.notify_all();
            }
            catch (...)
            {
            }
        }

    asynchronous_sink(bool start_thread = true) :
        base_type(true),
        m_pBackend(boost::make_shared< sink_backend_type >()),
        m_StopRequested(false),
        m_FlushRequested(false)
    {
        if (start_thread)
            start_feeding_thread();
    }


        explicit direct_mapping_visitor(mapped_type& extracted) :
            m_Extracted(extracted)
        {
        }

        template< typename T >
        void operator() (T const& val) const
        {
            m_Extracted = mapped_type(val);
        }

    explicit basic_direct_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }

    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        aux::direct_mapping_visitor< mapped_type > vis(res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }

        reference_proxy(mapping_type& mapping, attribute_value_type const& key) : m_Mapping(mapping), m_Key(key) {}

        reference_proxy const& operator= (mapped_type const& val) const
        {
            m_Mapping[m_Key] = val;
            return *this;
        }


        visitor(mapping_type const& mapping, mapped_type& extracted) :
            m_Mapping(mapping),
            m_Extracted(extracted)
        {
        }

        template< typename T >
        void operator() (T const& val) const
        {
            typename mapping_type::const_iterator it = m_Mapping.find(val);
            if (it != m_Mapping.end())
                m_Extracted = it->second;
        }

    explicit basic_custom_mapping(attribute_name const& name, mapped_type const& default_value) :
        m_Name(name),
        m_DefaultValue(default_value)
    {
    }

    mapped_type operator() (record_view const& rec) const
    {
        mapped_type res = m_DefaultValue;
        visitor vis(m_Mapping, res);
        m_Invoker(m_Name, rec.attribute_values(), vis);
        return res;
    }

    reference_proxy operator[] (attribute_value_type const& key)
#else
    implementation_defined operator[] (attribute_value_type const& key)
#endif
    {
        return reference_proxy(m_Mapping, key);
    }


        thread_context() : result(true) {}

    block_on_overflow() {}

    template< typename LockT >
    bool on_overflow(record_view const&, LockT& lock)
    {
        thread_context context;
        m_thread_contexts.push_back(context);
        do
        {
            context.cond.wait(lock);
        }
        while (context.is_linked());

        return context.result;
    }

    void on_queue_space_available()
    {
        if (!m_thread_contexts.empty())
        {
            m_thread_contexts.front().cond.notify_one();
            m_thread_contexts.pop_front();
        }
    }

    void interrupt()
    {
        while (!m_thread_contexts.empty())
        {
            thread_context& context = m_thread_contexts.front();
            context.result = false;
            context.cond.notify_one();
            m_thread_contexts.pop_front();
        }
    }

        explicit direct_event_type_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }

        explicit custom_event_type_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }

        explicit direct_event_id_mapping(attribute_name const& name) :
            base_type(name, make_event_id(0))
        {
        }

        explicit custom_event_id_mapping(attribute_name const& name) :
            base_type(name, make_event_id(0))
        {
        }

        explicit direct_event_category_mapping(attribute_name const& name) :
            base_type(name, make_event_category(0))
        {
        }

        explicit custom_event_category_mapping(attribute_name const& name) :
            base_type(name, make_event_category(0))
        {
        }

    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            args[keywords::target | string_type()],
            args[keywords::log_name || &basic_simple_event_log_backend::get_default_log_name],
            args[keywords::log_source || &basic_simple_event_log_backend::get_default_source_name],
            args[keywords::registration | event_log::on_demand]);
    }

    template< typename T >
    explicit basic_event_log_backend(std::basic_string< T > const& message_file_name)
    {
        construct(keywords::message_file = message_file_name);
    }

    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            filesystem::path(args[keywords::message_file]),
            args[keywords::target | string_type()],
            args[keywords::log_name || &basic_event_log_backend::get_default_log_name],
            args[keywords::log_source || &basic_event_log_backend::get_default_source_name],
            args[keywords::registration | event_log::on_demand]);
    }

    synchronous_sink() :
        base_type(false),
        m_pBackend(boost::make_shared< sink_backend_type >())
    {
    }

    explicit cleanup_guard(T& obj) : m_Obj(obj) {}

    ~cleanup_guard() { m_Obj.clear(); }

    operator integer_type() const { return value; }

    tagged_integer& operator++ () { ++value; return *this; }

    tagged_integer operator++ (int) { tagged_integer temp = *this; ++value; return temp; }

    tagged_integer& operator-- () { --value; return *this; }

    tagged_integer operator-- (int) { tagged_integer temp = *this; --value; return temp; }
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
    BOOST_LOG_TAGGED_INTEGER_OP(*=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
    BOOST_LOG_TAGGED_INTEGER_OP(*=)
    BOOST_LOG_TAGGED_INTEGER_OP(/=)
\
    tagged_integer& operator op (tagged_integer const& that) { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
    BOOST_LOG_TAGGED_INTEGER_OP(*=)
    BOOST_LOG_TAGGED_INTEGER_OP(/=)
    BOOST_LOG_TAGGED_INTEGER_OP(%=)

    tagged_integer& operator~ () { ~value; return *this; }

    template< typename T >
    tagged_integer& operator<<= (T const& that) { value <<= that; return *this; }

    template< typename T >
    tagged_integer& operator>>= (T const& that) { value >>= that; return *this; }
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
BOOST_LOG_TAGGED_INTEGER_OP(>)
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
BOOST_LOG_TAGGED_INTEGER_OP(>)
BOOST_LOG_TAGGED_INTEGER_OP(<=)
\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
BOOST_LOG_TAGGED_INTEGER_OP(>)
BOOST_LOG_TAGGED_INTEGER_OP(<=)
BOOST_LOG_TAGGED_INTEGER_OP(>=)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
BOOST_LOG_TAGGED_INTEGER_OP(*)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
BOOST_LOG_TAGGED_INTEGER_OP(*)
BOOST_LOG_TAGGED_INTEGER_OP(/)
\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
BOOST_LOG_TAGGED_INTEGER_OP(*)
BOOST_LOG_TAGGED_INTEGER_OP(/)
BOOST_LOG_TAGGED_INTEGER_OP(%)
\
    template< typename IntT, typename TagT, typename T >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, T const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(<<)
\
    template< typename IntT, typename TagT, typename T >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, T const& right)\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(<<)
BOOST_LOG_TAGGED_INTEGER_OP(>>)


    decomposed_time() : year(0), month(1), day(1), hours(0), minutes(0), seconds(0), subseconds(0), negative(false)
    {
    }


    unsigned int week_day() const
    {
        unsigned int a = (14u - month) / 12u;
        unsigned int y = year - a;
        unsigned int m = month + 12u * a - 2u;
        return (day + y + (y / 4u) - (y / 100u) + (y / 400u) + (31u * m) / 12u) % 7u;
    }


    unsigned int year_day() const
    {
        bool is_leap_year = (!(year % 4u)) && ((year % 100u) || (!(year % 400u)));
        static const unsigned int first_day_offset[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
        return first_day_offset[month - 1] + day + (month > 2 && is_leap_year);
    }


inline std::tm to_tm(decomposed_time const& t)
{
    std::tm res = {};
    res.tm_year = static_cast< int >(t.year) - 1900;
    res.tm_mon = t.month - 1;
    res.tm_mday = t.day;
    res.tm_hour = t.hours;
    res.tm_min = t.minutes;
    res.tm_sec = t.seconds;
    res.tm_wday = t.week_day();
    res.tm_yday = t.year_day();
    res.tm_isdst = -1;

    return res;
}


        context(date_time_formatter const& self_, stream_type& strm_, value_type const& value_) :
            self(self_),
            strm(strm_),
            str(*strm_.rdbuf()->storage()),
            value(value_),
            literal_index(0),
            literal_pos(0)
        {
        }

    explicit decomposed_time_formatter_builder(formatter_type& fmt) : m_formatter(fmt)
    {
    }


    void on_literal(iterator_range< const char_type* > const& lit)
    {
        m_formatter.add_literal(lit);
    }


    void on_short_year()
    {
        m_formatter.add_formatter(&formatter_type::format_short_year);
    }


    void on_full_year()
    {
        m_formatter.add_formatter(&formatter_type::format_full_year);
    }


    void on_numeric_month()
    {
        m_formatter.add_formatter(&formatter_type::format_numeric_month);
    }


    void on_short_month()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'b' >);
    }


    void on_full_month()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'B' >);
    }


    void on_month_day(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_month_day< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_month_day< ' ' >);
    }


    void on_numeric_week_day()
    {
        m_formatter.add_formatter(&formatter_type::format_week_day);
    }


    void on_short_week_day()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'a' >);
    }


    void on_full_week_day()
    {
        m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_through_locale< 'A' >);
    }


    void on_hours(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours< ' ' >);
    }


    void on_hours_12(bool leading_zero)
    {
        if (leading_zero)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours_12< '0' >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_hours_12< ' ' >);
    }


    void on_minutes()
    {
        m_formatter.add_formatter(&formatter_type::format_minutes);
    }


    void on_seconds()
    {
        m_formatter.add_formatter(&formatter_type::format_seconds);
    }


    void on_fractional_seconds()
    {
        m_formatter.add_formatter(&formatter_type::format_fractional_seconds);
    }


    void on_am_pm(bool upper_case)
    {
        if (upper_case)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_am_pm< true >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_am_pm< false >);
    }


    void on_duration_sign(bool display_positive)
    {
        if (display_positive)
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_sign< true >);
        else
            m_formatter.add_formatter(&formatter_type::BOOST_NESTED_TEMPLATE format_sign< false >);
    }


    void on_iso_time_zone()
    {
    }


    void on_extended_iso_time_zone()
    {
    }


    format_element() : arg_number(0), literal_start_pos(0), literal_len(0)
    {
    }


    static format_element literal(unsigned int start_pos, unsigned int len)
    {
        format_element el;
        el.arg_number = -1;
        el.literal_start_pos = start_pos;
        el.literal_len = len;
        return el;
    }


    static format_element positional_argument(unsigned int arg_n)
    {
        format_element el;
        el.arg_number = arg_n;
        return el;
    }


        impl_base(invoke_type inv, clone_type cl, destroy_type dstr) : invoke(inv), clone(cl), destroy(dstr)
        {
        }

        explicit impl(FunT const& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }

        explicit impl(FunT&& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }


        static void destroy_impl(impl_base* self)
        {
            delete static_cast< impl* >(self);
        }

        static impl_base* clone_impl(const impl_base* self)
        {
            return new impl(static_cast< const impl* >(self)->m_Function);
        }

        static result_type invoke_impl(impl_base* self, ArgsT... args)
        {
            return static_cast< impl* >(self)->m_Function(args...);
        }


        impl_base(invoke_type inv, clone_type cl, destroy_type dstr) : invoke(inv), clone(cl), destroy(dstr)
        {
        }

        explicit impl(FunT const& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }

        explicit impl(FunT&& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }


        static void destroy_impl(impl_base* self)
        {
            delete static_cast< impl* >(self);
        }

        static impl_base* clone_impl(const impl_base* self)
        {
            return new impl(static_cast< const impl* >(self)->m_Function);
        }

        static result_type invoke_impl(impl_base* self, ArgsT... args)
        {
            static_cast< impl* >(self)->m_Function(args...);
        }


template< typename SignatureT >
inline void swap(light_function< SignatureT >& left, light_function< SignatureT >& right)
{
    left.swap(right);
}

template< typename CharT >
inline filter acquire_filter(const CharT* filter)
{
    return boost::log::parse_filter(filter);
}

template< typename SinkT, typename ArgsT >
inline void setup_filter(SinkT&, ArgsT const&, mpl::true_)
{
}

    virtual ~date_format_parser_callback() {}

    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }

    virtual void on_short_year()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('y'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_full_year()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('Y'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_numeric_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('m'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_short_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('b'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_full_month()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('B'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_month_day(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('d') : static_cast< char_type >('e')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_numeric_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('w'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_short_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('a'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_full_week_day()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('A'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_iso_date()
    {
        on_full_year();
        on_numeric_month();
        on_month_day(true);
    }

    virtual void on_extended_iso_date()
    {
        const char_type delimiter[2] = { static_cast< char_type >('-'), static_cast< char_type >('\0') };
        on_full_year();
        on_literal(boost::as_literal(delimiter));
        on_numeric_month();
        on_literal(boost::as_literal(delimiter));
        on_month_day(true);
    }

    virtual ~time_format_parser_callback() {}

    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }

    virtual void on_hours(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('O') : static_cast< char_type >('k')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_hours_12(bool leading_zero)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (leading_zero ? static_cast< char_type >('I') : static_cast< char_type >('l')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_minutes()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('M'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_seconds()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('S'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_fractional_seconds()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('f'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_am_pm(bool upper_case)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (upper_case ? static_cast< char_type >('p') : static_cast< char_type >('P')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_duration_sign(bool display_positive)
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), (display_positive ? static_cast< char_type >('+') : static_cast< char_type >('-')), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_iso_time_zone()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('q'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_extended_iso_time_zone()
    {
        const char_type placeholder[3] = { static_cast< char_type >('%'), static_cast< char_type >('Q'), static_cast< char_type >('\0') };
        on_placeholder(boost::as_literal(placeholder));
    }

    virtual void on_iso_time()
    {
        on_hours(true);
        on_minutes();
        on_seconds();
    }

    virtual void on_extended_iso_time()
    {
        const char_type delimiter[2] = { static_cast< char_type >(':'), static_cast< char_type >('\0') };
        on_hours(true);
        on_literal(boost::as_literal(delimiter));
        on_minutes();
        on_literal(boost::as_literal(delimiter));
        on_seconds();
    }

    virtual void on_default_time()
    {
        on_extended_iso_time();

        const char_type delimiter[2] = { static_cast< char_type >('.'), static_cast< char_type >('\0') };
        on_literal(boost::as_literal(delimiter));
        on_fractional_seconds();
    }

    virtual ~date_time_format_parser_callback() {}

    virtual void on_placeholder(iterator_range< const char_type* > const& ph)
    {
        // By default interpret all unrecognized placeholders as literals
        on_literal(ph);
    }


    template< typename ContextT >
    typename result< const this_type(T const&, ContextT&) >::type operator() (T const& term, ContextT& ctx) const
    {
        return term(ctx);
    }

    attribute_predicate(attribute_name const& name, argument_type const& pred_arg) : m_arg(pred_arg), m_name(name)
    {
    }

    template< typename ArgumentT >
    result_type operator() (ArgumentT const& arg) const
    {
        typedef binder2nd< predicate_type, argument_type const& > visitor_type;

        bool res = false;
        m_visitor_invoker(m_name, arg, boost::log::save_result(visitor_type(predicate_type(), m_arg), res));
        return res;
    }

    explicit duration(int64_t ticks = 0) : m_ticks(ticks) {}

    explicit timestamp(uint64_t ticks = 0) : m_ticks(ticks) {}


    duration operator- (timestamp that) const
    {
        return duration(m_ticks - that.m_ticks);
    }

    explicit exclusive_lock_guard(MutexT& m) : m_Mutex(m)
    {
        m.lock();
    }

    ~exclusive_lock_guard()
    {
        m_Mutex.unlock();
    }

    explicit shared_lock_guard(MutexT& m) : m_Mutex(m)
    {
        m.lock_shared();
    }

    ~shared_lock_guard()
    {
        m_Mutex.unlock_shared();
    }

    multiple_unique_lock2(MutexT1& m1, MutexT2& m2) :
        m_p1(&m1),
        m_p2(&m2)
    {
        // Yes, it's not conforming, but it works
        // and it doesn't require to #include <functional>
        if (static_cast< void* >(m_p1) < static_cast< void* >(m_p2))
        {
            m_p1->lock();
            m_p2->lock();
        }
        else
        {
            m_p2->lock();
            m_p1->lock();
        }
    }

    ~multiple_unique_lock2()
    {
        m_p2->unlock();
        m_p1->unlock();
    }


        impl_base(invoke_type inv, clone_type cl, destroy_type dstr) : invoke(inv), clone(cl), destroy(dstr)
        {
        }

        explicit impl(FunT const& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }

        explicit impl(FunT&& fun) :
            impl_base(&this_type::invoke_impl, &this_type::clone_impl, &this_type::destroy_impl),
            m_Function(fun)
        {
        }


        static void destroy_impl(impl_base* self)
        {
            delete static_cast< impl* >(self);
        }

        static impl_base* clone_impl(const impl_base* self)
        {
            return new impl(static_cast< const impl* >(self)->m_Function);
        }

        static result_type invoke_impl(impl_base* self BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), ArgT, arg))
        {
            return static_cast< impl* >(self)->m_Function(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), arg));
        }

    attribute_output_terminal(LeftT const& left, attribute_name const& name) : m_left(left), m_name(name)
    {
    }

    attribute_output_terminal(attribute_output_terminal const& that) :
        m_left(that.m_left), m_name(that.m_name), m_visitor_invoker(that.m_visitor_invoker), m_impl(that.m_impl)
    {
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< impl_type&, result_type >(m_impl, strm));
        return strm;
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< impl_type const&, result_type >(m_impl, strm));
        return strm;
    }

        locking_ptr(shared_ptr< element_type > const& p, locking_ptr_counter_base& l)
            : m_pElement(p), m_pLock(&l)
        {
            if (m_pLock->m_RefCounter == 0)
                m_pLock->lock();
            ++m_pLock->m_RefCounter;
        }

        locking_ptr(locking_ptr const& that) : m_pElement(that.m_pElement), m_pLock(that.m_pLock)
        {
            if (m_pLock)
                ++m_pLock->m_RefCounter;
        }

        ~locking_ptr()
        {
            if (m_pLock && --m_pLock->m_RefCounter == 0)
                m_pLock->unlock();
        }

        locking_ptr& operator= (locking_ptr that)
        {
            this->swap(that);
            return *this;
        }

        element_type* operator-> () const { return m_pElement.get(); }

        element_type& operator* () const { return *m_pElement; }

        element_type* get() const { return m_pElement.get(); }

    template< typename T >
    inline T* get_pointer(locking_ptr< T > const& p)
    {
        return p.get();
    }

    template< typename T >
    inline void swap(locking_ptr< T >& left, locking_ptr< T >& right)
    {
        left.swap(right);
    }


    virtual ~threadsafe_queue_impl() {}


        node() {}

        explicit node(T const& val) { new (storage.address()) T(val); }

        T& value() { return *static_cast< T* >(storage.address()); }

        void destroy() { static_cast< T* >(storage.address())->~T(); }

        severity_level() : attribute(new impl())
        {
        }

        severity_level(severity_level const& that) : attribute(static_cast< attribute const& >(that))
        {
        }

        severity_level(BOOST_RV_REF(severity_level) that) : attribute(boost::move(static_cast< attribute& >(that)))
        {
        }

        severity_level& operator= (BOOST_COPY_ASSIGN_REF(severity_level) that)
        {
            attribute::operator= (that);
            return *this;
        }

        void set_value(value_type level)
        {
            reinterpret_cast< value_type& >(get_severity_level()) = level;
        }

    basic_severity_logger() :
        base_type(),
        m_DefaultSeverity(static_cast< severity_level >(0))
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::severity(), m_SeverityAttr);
    }

    basic_severity_logger(basic_severity_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_DefaultSeverity(that.m_DefaultSeverity),
        m_SeverityAttr(that.m_SeverityAttr)
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::severity()] = m_SeverityAttr;
    }

    basic_severity_logger(BOOST_RV_REF(basic_severity_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_DefaultSeverity(boost::move(that.m_DefaultSeverity)),
        m_SeverityAttr(boost::move(that.m_SeverityAttr))
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::severity()] = m_SeverityAttr;
    }

    template< typename ArgsT >
    explicit basic_severity_logger(ArgsT const& args) :
        base_type(args),
        m_DefaultSeverity(args[keywords::severity | severity_level()])
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::severity(), m_SeverityAttr);
    }

    severity_level default_severity() const { return m_DefaultSeverity; }

    severity_attribute const& get_severity_attribute() const { return m_SeverityAttr; }

    template< typename ArgsT >
    record open_record_unlocked(ArgsT const& args)
    {
        m_SeverityAttr.set_value(args[keywords::severity | m_DefaultSeverity]);
        return base_type::open_record_unlocked(args);
    }

    void swap_unlocked(basic_severity_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
        severity_level t = m_DefaultSeverity;
        m_DefaultSeverity = that.m_DefaultSeverity;
        that.m_DefaultSeverity = t;
        m_SeverityAttr.swap(that.m_SeverityAttr);
    }

    static logger_type& get()
    {
        return base_type::get()->m_Logger;
    }

    static void init_instance()
    {
        shared_ptr< logger_holder< logger_type > >& instance = base_type::get_instance();
        shared_ptr< logger_holder_base > holder = global_storage::get_or_init(
            typeid(boost::log::aux::visible_type< TagT >),
            &logger_singleton::construct_logger);
        instance = boost::dynamic_pointer_cast< logger_holder< logger_type > >(holder);
        if (!instance)
        {
            // In pure C++ this should never happen, since there cannot be two
            // different tag types that have equal type_infos. In real life it can
            // happen if the same-named tag is defined differently in two or more
            // dlls. This check is intended to detect such ODR violations. However, there
            // is no protection against different definitions of the logger type itself.
            throw_odr_violation(typeid(TagT), typeid(logger_type), *holder);
        }
    }

    basic_exception_handler_logger() : base_type()
    {
    }

    basic_exception_handler_logger(basic_exception_handler_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_ExceptionHandler(that.m_ExceptionHandler)
    {
    }

    basic_exception_handler_logger(BOOST_RV_REF(basic_exception_handler_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_ExceptionHandler(boost::move(that.m_ExceptionHandler))
    {
    }

    template< typename ArgsT >
    explicit basic_exception_handler_logger(ArgsT const& args) :
        base_type(args)
    {
    }

    template< typename HandlerT >
    void set_exception_handler(HandlerT const& handler)
    {
#ifndef BOOST_LOG_NO_THREADS
        boost::log::aux::exclusive_lock_guard< threading_model > lock(this->get_threading_model());
#endif
        m_ExceptionHandler = handler;
    }

    template< typename ArgsT >
    record open_record_unlocked(ArgsT const& args)
    {
        try
        {
            return base_type::open_record_unlocked(args);
        }
#ifndef BOOST_LOG_NO_THREADS
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            handle_exception();
            return record();
        }
    }

    void push_record_unlocked(BOOST_RV_REF(record) rec)
    {
        try
        {
            base_type::push_record_unlocked(boost::move(rec));
        }
#ifndef BOOST_LOG_NO_THREADS
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            handle_exception();
        }
    }

    void swap_unlocked(basic_exception_handler_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
        m_ExceptionHandler.swap(that.m_ExceptionHandler);
    }

    void handle_exception()
    {
#ifndef BOOST_LOG_NO_THREADS
        // Here's the trick with the lock type. Since the lock
        // is only needed when an exception is caught, we indicate
        // no locking requirements in the push_record_lock type.
        // However, if other features don't require locking either,
        // we shall acquire a read lock here, when an exception is caught.
        // If other features do require locking, the thread model is
        // already locked by now, and we don't do locking at all.
        typedef typename mpl::if_<
            is_same< no_lock< threading_model >, typename final_type::push_record_lock >,
            boost::log::aux::shared_lock_guard< threading_model >,
            no_lock< threading_model >
        >::type lock_type;
        lock_type lock(base_type::get_threading_model());
#endif // !defined(BOOST_LOG_NO_THREADS)

        if (m_ExceptionHandler.empty())
            throw;
        m_ExceptionHandler();
    }

    void lock_shared() const {}

    bool try_lock_shared() const { return true; }

    template< typename TimeT >
    bool timed_lock_shared(TimeT const&) const { return true; }

    void unlock_shared() const {}

    void lock() const {}

    bool try_lock() const { return true; }

    template< typename TimeT >
    bool timed_lock(TimeT const&) const { return true; }

    void unlock() const {}

    void lock_upgrade() const {}

    bool try_lock_upgrade() const { return true; }

    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const&) const { return true; }

    void unlock_upgrade() const {}

    void unlock_upgrade_and_lock() const {}

    void unlock_and_lock_upgrade() const {}

    void unlock_and_lock_shared() const {}

    void unlock_upgrade_and_lock_shared() const {}


    void swap(single_thread_model&) {}

    multi_thread_model() {}

    multi_thread_model(multi_thread_model const&) {}

    multi_thread_model& operator= (multi_thread_model const&) { return *this; }


    void lock_shared() const { m_Mutex.lock_shared(); }

    bool try_lock_shared() const { return m_Mutex.try_lock_shared(); }

    template< typename TimeT >
    bool timed_lock_shared(TimeT const& t) const { return m_Mutex.timed_lock_shared(t); }

    void unlock_shared() const { m_Mutex.unlock_shared(); }

    void lock() const { m_Mutex.lock(); }

    bool try_lock() const { return m_Mutex.try_lock(); }

    template< typename TimeT >
    bool timed_lock(TimeT const& t) const { return m_Mutex.timed_lock(t); }

    void unlock() const { m_Mutex.unlock(); }

    void lock_upgrade() const { m_Mutex.lock_upgrade(); }

    bool try_lock_upgrade() const { return m_Mutex.try_lock_upgrade(); }

    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const& t) const { return m_Mutex.timed_lock_upgrade(t); }

    void unlock_upgrade() const { m_Mutex.unlock_upgrade(); }

    void unlock_upgrade_and_lock() const { m_Mutex.unlock_upgrade_and_lock(); }

    void unlock_and_lock_upgrade() const { m_Mutex.unlock_and_lock_upgrade(); }

    void unlock_and_lock_shared() const { m_Mutex.unlock_and_lock_shared(); }

    void unlock_upgrade_and_lock_shared() const { m_Mutex.unlock_upgrade_and_lock_shared(); }


    void swap(multi_thread_model&) {}

        explicit stream_compound(record& rec) : next(NULL), stream(rec) {}

    explicit record_pump(logger_type& lg, record& rec) :
        m_pLogger(boost::addressof(lg)),
        m_pStreamCompound(stream_provider_type::allocate_compound(rec)),
        m_ExceptionCount(unhandled_exception_count())
    {
    }
 make_record_pump(LoggerT& lg, record& rec)
{
    return record_pump< LoggerT >(lg, rec);
}

    basic_logger() :
        threading_model(),
        m_pCore(core::get())
    {
    }

    basic_logger(basic_logger const& that) :
        threading_model(static_cast< threading_model const& >(that)),
        m_pCore(core::get()),
        m_Attributes(that.m_Attributes)
    {
    }

    basic_logger(BOOST_RV_REF(basic_logger) that) :
        threading_model(boost::move(static_cast< threading_model& >(that)))
    {
        m_pCore.swap(that.m_pCore);
        m_Attributes.swap(that.m_Attributes);
    }

    template< typename ArgsT >
    explicit basic_logger(ArgsT const&) :
        threading_model(),
        m_pCore(core::get())
    {
    }

template< typename CharT, typename FinalT, typename ThreadingModelT >
inline void swap(
    basic_logger< CharT, FinalT, ThreadingModelT >& left,
    basic_logger< CharT, FinalT, ThreadingModelT >& right)
{
    static_cast< FinalT& >(left).swap(static_cast< FinalT& >(right));
}

    basic_composite_logger() {}

    basic_composite_logger(basic_composite_logger const& that) :
        base_type
        ((
            boost::log::aux::shared_lock_guard< const threading_model >(that.get_threading_model()),
            static_cast< base_type const& >(that)
        ))
    {
    }

    basic_composite_logger(BOOST_RV_REF(logger_base) that) :
        base_type(boost::move(static_cast< base_type& >(that)))
    {
    }

    template< typename ArgsT >
    explicit basic_composite_logger(ArgsT const& args) : base_type(args)
    {
    }

        result_type operator() () const { return result_type(); }

    basic_channel_logger() : base_type(), m_ChannelAttr(channel_type())
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::channel(), m_ChannelAttr);
    }

    basic_channel_logger(basic_channel_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_ChannelAttr(that.m_ChannelAttr)
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::channel()] = m_ChannelAttr;
    }

    basic_channel_logger(BOOST_RV_REF(basic_channel_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_ChannelAttr(boost::move(that.m_ChannelAttr))
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::channel()] = m_ChannelAttr;
    }

    template< typename ArgsT >
    explicit basic_channel_logger(ArgsT const& args) :
        base_type(args),
        m_ChannelAttr(args[keywords::channel || make_default_channel_name()])
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::channel(), m_ChannelAttr);
    }

    channel_type channel() const
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< const threading_model > lock(this->get_threading_model());)
        return m_ChannelAttr.get();
    }

    void channel(channel_type const& ch)
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< threading_model > lock(this->get_threading_model());)
        m_ChannelAttr.set(ch);
    }

    static attribute_name get_name() { return descriptor_type::get_name(); }

    static or_none_result_type or_none()
    {
        typedef typename or_none_result_type::terminal_type result_terminal;
        typename or_none_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_none_result_type(act);
    }

    static or_throw_result_type or_throw()
    {
        typedef typename or_throw_result_type::terminal_type result_terminal;
        typename or_throw_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_throw_result_type(act);
    }


    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }

    explicit attribute_terminal(attribute_name const& name) : m_name(name)
    {
    }

    attribute_name get_name() const
    {
        return m_name;
    }

    fallback_policy const& get_fallback_policy() const
    {
        return m_value_extractor.get_fallback_policy();
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type
    operator() (ContextT const& ctx)
    {
        return m_value_extractor(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type
    operator() (ContextT const& ctx) const
    {
        return m_value_extractor(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    explicit attribute_actor(base_type const& act) : base_type(act)
    {
    }

    attribute_name get_name() const
    {
        return this->proto_expr_.child0.get_name();
    }

    fallback_policy const& get_fallback_policy() const
    {
        return this->proto_expr_.child0.get_fallback_policy();
    }

    or_none_result_type or_none() const
    {
        typedef typename or_none_result_type::terminal_type result_terminal;
        typename or_none_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_none_result_type(act);
    }

    or_throw_result_type or_throw() const
    {
        typedef typename or_throw_result_type::terminal_type result_terminal;
        typename or_throw_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_throw_result_type(act);
    }

    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        return m_visitor_invoker(m_name, arg, nop()).code() == visitation_result::ok;
    }

    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    result_type operator() (attribute_value_set const& attrs) const
    {
        return attrs.find(m_name) != attrs.end();
    }
 make_csv_decor()
{
    return aux::csv_decorator_gen< CharT >();
}
 make_c_decor()
{
    return aux::c_decorator_gen< CharT >();
}

    c_ascii_pattern_replacer() : base_type(traits_type::get_patterns(), traits_type::get_replacements())
    {
    }

    result_type operator() (string_type& str, typename string_type::size_type start_pos = 0) const
    {
        base_type::operator() (str, start_pos);

        typedef typename string_type::iterator string_iterator;
        for (string_iterator it = str.begin() + start_pos, end = str.end(); it != end; ++it)
        {
            char_type c = *it;
            if (c < 0x20 || c > 0x7e)
            {
                char_type buf[(std::numeric_limits< char_type >::digits + 3) / 4 + 3];
                std::size_t n = traits_type::print_escaped(buf, c);
                std::size_t pos = it - str.begin();
                str.replace(pos, 1, buf, n);
                it = str.begin() + n - 1;
                end = str.end();
            }
        }
    }
 make_c_ascii_decor()
{
    return aux::c_ascii_decorator_gen< CharT >();
}

    template< typename FormatT >
    format_named_scope_terminal(attribute_name const& name, fallback_policy const& fallback, FormatT const& element_format, string_type const& delimiter, value_type::size_type depth, scope_iteration_direction direction) :
        m_name(name), m_formatter(aux::parse_named_scope_format(element_format), delimiter, depth, direction), m_visitor_invoker(fallback)
    {
    }

    format_named_scope_terminal(format_named_scope_terminal const& that) :
        m_name(that.m_name), m_formatter(that.m_formatter), m_visitor_invoker(that.m_visitor_invoker)
    {
    }

    attribute_name get_name() const
    {
        return m_name;
    }

    fallback_policy const& get_fallback_policy() const
    {
        return m_visitor_invoker.get_fallback_policy();
    }

    explicit format_named_scope_actor(base_type const& act) : base_type(act)
    {
    }

    attribute_name get_name() const
    {
        return this->proto_expr_.child0.get_name();
    }

    fallback_policy const& get_fallback_policy() const
    {
        return this->proto_expr_.child0.get_fallback_policy();
    }

    formatter_function_type const& get_formatter_function() const
    {
        return this->proto_expr_.child0.get_formatter_function();
    }

    template< typename RangeT >
    explicit pattern_replacer(RangeT const& decorations)
    {
        typedef typename range_const_iterator< RangeT >::type iterator;
        for (iterator it = begin(decorations), end_ = end(decorations); it != end_; ++it)
        {
            string_lengths lens;
            {
                typedef typename aux::string_const_iterator< typename range_value< RangeT >::type::first_type >::type first_iterator;
                first_iterator b = string_begin(it->first), e = string_end(it->first);
                lens.from_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            {
                typedef typename aux::string_const_iterator< typename range_value< RangeT >::type::second_type >::type second_iterator;
                second_iterator b = string_begin(it->second), e = string_end(it->second);
                lens.to_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            m_string_lengths.push_back(lens);
        }
    }

    template< typename FromRangeT, typename ToRangeT >
    pattern_replacer(FromRangeT const& from, ToRangeT const& to)
    {
        typedef typename range_const_iterator< FromRangeT >::type iterator1;
        typedef typename range_const_iterator< ToRangeT >::type iterator2;
        iterator1 it1 = begin(from), end1 = end(from);
        iterator2 it2 = begin(to), end2 = end(to);
        for (; it1 != end1 && it2 != end2; ++it1, ++it2)
        {
            string_lengths lens;
            {
                typedef typename aux::string_const_iterator< typename range_value< FromRangeT >::type >::type from_iterator;
                from_iterator b = string_begin(*it1), e = string_end(*it1);
                lens.from_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            {
                typedef typename aux::string_const_iterator< typename range_value< ToRangeT >::type >::type to_iterator;
                to_iterator b = string_begin(*it2), e = string_end(*it2);
                lens.to_len = static_cast< unsigned int >(std::distance(b, e));
                m_decoration_chars.append(b, e);
            }
            m_string_lengths.push_back(lens);
        }

        // Both sequences should be of the same size
        BOOST_ASSERT(it1 == end1);
        BOOST_ASSERT(it2 == end2);
    }

    pattern_replacer(pattern_replacer const& that) : m_decoration_chars(that.m_decoration_chars), m_string_lengths(that.m_string_lengths)
    {
    }

    result_type operator() (string_type& str, typename string_type::size_type start_pos = 0) const
    {
        typedef typename string_type::size_type size_type;

        const char_type* from_chars = m_decoration_chars.c_str();
        for (typename string_lengths_list::const_iterator it = m_string_lengths.begin(), end = m_string_lengths.end(); it != end; ++it)
        {
            const unsigned int from_len = it->from_len, to_len = it->to_len;
            const char_type* const to_chars = from_chars + from_len;
            for (size_type pos = str.find(from_chars, start_pos, from_len); pos != string_type::npos; pos = str.find(from_chars, pos, from_len))
            {
                str.replace(pos, from_len, to_chars, to_len);
                pos += to_len;
            }
            from_chars = to_chars + to_len;
        }
    }

    static char_type* string_begin(char_type* p)
    {
        return p;
    }

    static const char_type* string_begin(const char_type* p)
    {
        return p;
    }

    char_decorator_output_terminal(LeftT const& left, subactor_type const& sub, impl_type const& impl) :
        m_left(left), m_subactor(sub), m_impl(impl)
    {
    }

    char_decorator_output_terminal(char_decorator_output_terminal const& that) :
        m_left(that.m_left), m_subactor(that.m_subactor), m_impl(that.m_impl)
    {
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        // Flush the stream and keep the current write position in the target string
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        strm.flush();
        typename string_type::size_type const start_pos = strm.rdbuf()->storage()->size();

        // Invoke the adopted formatter
        typedef typename result< this_type(ContextT const&) >::type result_type;
        phoenix::eval(m_subactor, ctx);

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage(), start_pos);

        return strm;
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        // Flush the stream and keep the current write position in the target string
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        strm.flush();
        typename string_type::size_type const start_pos = strm.rdbuf()->storage()->size();

        // Invoke the adopted formatter
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        phoenix::eval(m_subactor, ctx);

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage(), start_pos);

        return strm;
    }

    char_decorator_terminal(subactor_type const& sub, impl_type const& impl) : m_subactor(sub), m_impl(impl)
    {
    }

    char_decorator_terminal(char_decorator_terminal const& that) : m_subactor(that.m_subactor), m_impl(that.m_impl)
    {
    }

    subactor_type const& get_subactor() const
    {
        return m_subactor;
    }

    impl_type const& get_impl() const
    {
        return m_impl;
    }

    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);

        // Invoke the adopted formatter
        typedef phoenix::vector3<
            subactor_type*,
            typename fusion::result_of::at_c<
                typename remove_cv<
                    typename remove_reference<
                        typename phoenix::result_of::env< ContextT const& >::type
                    >::type
                >::type::args_type,
                0
            >::type,
            stream_type&
        > env_type;
        env_type env = { boost::addressof(m_subactor), fusion::at_c< 0 >(phoenix::env(ctx).args()), strm };
        phoenix::eval(m_subactor, phoenix::make_context(env, phoenix::actions(ctx)));

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage());

        return boost::move(str);
    }

    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        string_type str;
        stream_type strm(str);

        // Invoke the adopted formatter
        typedef phoenix::vector3<
            const subactor_type*,
            typename fusion::result_of::at_c<
                typename remove_cv<
                    typename remove_reference<
                        typename phoenix::result_of::env< ContextT const& >::type
                    >::type
                >::type::args_type,
                0
            >::type,
            stream_type&
        > env_type;
        env_type env = { boost::addressof(m_subactor), fusion::at_c< 0 >(phoenix::env(ctx).args()), strm };
        phoenix::eval(m_subactor, phoenix::make_context(env, phoenix::actions(ctx)));

        // Flush the buffered characters and apply decorations
        strm.flush();
        m_impl(*strm.rdbuf()->storage());

        return boost::move(str);
    }

    explicit char_decorator_actor(base_type const& act) : base_type(act)
    {
    }

    terminal_type const& get_terminal() const
    {
        return this->proto_expr_.child0;
    }

    explicit char_decorator_gen1(RangeT const& decorations) : m_decorations(decorations)
    {
    }


    template< typename SubactorT >
    BOOST_LOG_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef pattern_replacer< char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(m_decorations)) }};
        return result_type(act);
    }

    char_decorator_gen2(FromRangeT const& from, ToRangeT const& to) : m_from(from), m_to(to)
    {
    }


    template< typename SubactorT >
    BOOST_LOG_FORCEINLINE char_decorator_actor< SubactorT, pattern_replacer< from_char_type > > operator[] (SubactorT const& subactor) const
    {
        typedef pattern_replacer< from_char_type > replacer_type;
        typedef char_decorator_actor< SubactorT, replacer_type > result_type;
        typedef typename result_type::terminal_type terminal_type;
        typename result_type::base_type act = {{ terminal_type(subactor, replacer_type(m_from, m_to)) }};
        return result_type(act);
    }

    explicit format_terminal(const char_type* format) : m_format(format) {}

    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        return m_format.make_pump(fusion::at_c< 1 >(phoenix::env(ctx).args()));
    }
 make_xml_decor()
{
    return aux::xml_decorator_gen< CharT >();
}

    wrapped_formatter_output_terminal(LeftT const& left, function_type const& fun) : m_left(left), m_fun(fun)
    {
    }

    wrapped_formatter_output_terminal(wrapped_formatter_output_terminal const& that) : m_left(that.m_left), m_fun(that.m_fun)
    {
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        return strm;
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        return strm;
    }

    explicit wrapped_formatter_terminal(function_type const& fun) : m_fun(fun)
    {
    }

    wrapped_formatter_terminal(wrapped_formatter_terminal const& that) : m_fun(that.m_fun)
    {
    }

    function_type const& get_function() const
    {
        return m_fun;
    }

    template< typename ContextT >
    result_type operator() (ContextT const& ctx)
    {
        string_type str;
        stream_type strm(str);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        strm.flush();
        return boost::move(str);
    }

    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        string_type str;
        stream_type strm(str);
        m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()), strm);
        strm.flush();
        return boost::move(str);
    }

    explicit wrapped_formatter_actor(base_type const& act) : base_type(act)
    {
    }

    function_type const& get_function() const
    {
        return this->proto_expr_.child0.get_function();
    }

template< typename FunT >
BOOST_LOG_FORCEINLINE wrapped_formatter_actor< FunT, typename aux::default_char_type< FunT >::type > wrap_formatter(FunT const& fun)
{
    typedef wrapped_formatter_actor< FunT, typename aux::default_char_type< FunT >::type > actor_type;
    typedef typename actor_type::terminal_type terminal_type;
    typename actor_type::base_type act = {{ terminal_type(fun) }};
    return actor_type(act);
}

    if_output_terminal(LeftT const& left, CondT const& cond, ThenT const& then_) : m_left(left), m_cond(cond), m_then(then_)
    {
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        return strm;
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        return strm;
    }

    if_else_output_terminal(LeftT const& left, CondT const& cond, ThenT const& then_, ElseT const& else_) : m_left(left), m_cond(cond), m_then(then_), m_else(else_)
    {
    }

    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        else
            phoenix::eval(m_else, ctx);
        return strm;
    }

    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        if (phoenix::eval(m_cond, ctx))
            phoenix::eval(m_then, ctx);
        else
            phoenix::eval(m_else, ctx);
        return strm;
    }


    if_then_else_gen(CondT const& cond, ThenT const& then_, ElseT const& else_) : m_cond(cond), m_then(then_), m_else(else_)
    {
    }


        else_gen(CondT const& cond, ThenT const& then_) : m_cond(cond), m_then(then_)
        {
        }


        else_gen(CondT const& cond, ThenT const& then_) : m_cond(cond), m_then(then_)
        {
        }


    if_then_gen(CondT const& cond, ThenT const& then_) : else_(cond, then_) {}

    explicit if_gen(CondT const& cond) : m_cond(cond)
    {
    }

    format_date_time_terminal(attribute_name const& name, fallback_policy const& fallback, string_type const& format) :
        m_name(name), m_formatter(formatter_generator::parse(format)), m_visitor_invoker(fallback)
    {
    }

    format_date_time_terminal(format_date_time_terminal const& that) :
        m_name(that.m_name), m_formatter(that.m_formatter), m_visitor_invoker(that.m_visitor_invoker)
    {
    }

    attribute_name get_name() const
    {
        return m_name;
    }

    fallback_policy const& get_fallback_policy() const
    {
        return m_visitor_invoker.get_fallback_policy();
    }

    explicit format_date_time_actor(base_type const& act) : base_type(act)
    {
    }

    attribute_name get_name() const
    {
        return this->proto_expr_.child0.get_name();
    }

    fallback_policy const& get_fallback_policy() const
    {
        return this->proto_expr_.child0.get_fallback_policy();
    }

    formatter_function_type const& get_formatter_function() const
    {
        return this->proto_expr_.child0.get_formatter_function();
    }

    template< typename StringT, typename ParserT >
    static bool matches(
        StringT const& str,
        ParserT const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        spirit::classic::parse_info< const_iterator > info =
            spirit::classic::parse(str.begin(), str.end(), expr);
        return info.full;
    }

inline current_scope_info current_scope()
{
    return current_scope_info(attributes::named_scope::get_scopes());
}


template< typename DateT, typename ValueT >
inline void decompose_date(DateT const& d, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    typedef typename DateT::ymd_type ymd_type;
    ymd_type ymd = d.year_month_day();
    v.year = ymd.year;
    v.month = ymd.month;
    v.day = ymd.day;
}


template< typename TimeDurationT, typename ValueT >
inline void decompose_time_of_day(TimeDurationT const& tod, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    v.hours = tod.hours();
    v.minutes = tod.minutes();
    v.seconds = tod.seconds();

    typedef typename TimeDurationT::traits_type traits_type;
    enum
    {
        adjustment_ratio = (traits_type::ticks_per_second > boost::log::aux::decomposed_time::subseconds_per_second ?
            traits_type::ticks_per_second / boost::log::aux::decomposed_time::subseconds_per_second :
            boost::log::aux::decomposed_time::subseconds_per_second / traits_type::ticks_per_second)
    };
    uint64_t frac = tod.fractional_seconds();
    v.subseconds = static_cast< uint32_t >(traits_type::ticks_per_second > boost::log::aux::decomposed_time::subseconds_per_second ? frac / adjustment_ratio : frac * adjustment_ratio);
}


template< typename TimeDurationT, typename ValueT >
inline void decompose_time_duration(TimeDurationT const& dur, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    if (dur.is_negative())
    {
        v.negative = true;
        (decompose_time_of_day)(-dur, v);
    }
    else
        (decompose_time_of_day)(dur, v);
}


template< typename DateDurationT, typename ValueT >
inline void decompose_date_duration(DateDurationT const& dur, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    if (dur.is_negative())
    {
        v.negative = true;
        v.day = (-dur).days();
    }
    else
        v.day = dur.days();
}


template< typename TimeT, typename ValueT >
inline void decompose_time(TimeT const& t, boost::log::aux::decomposed_time_wrapper< ValueT >& v)
{
    (decompose_date)(t.date(), v);
    (decompose_time_of_day)(t.time_of_day(), v);
}

    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_time_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }

    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }

    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_time_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }

    static formatter_function_type parse(string_type const& format)
    {
        formatter fmt;
        boost::log::aux::decomposed_time_formatter_builder< formatter, char_type > builder(fmt);
        boost::log::aux::parse_date_format(format, builder);
        return formatter_function_type(boost::move(fmt));
    }

    template< typename StringT, typename T >
    static bool matches(
        StringT const& str,
        xpressive::basic_regex< T > const& expr,
        xpressive::regex_constants::match_flag_type flags = xpressive::regex_constants::match_default)
    {
        return xpressive::regex_match(str, expr, flags);
    }

    template< typename StringT, typename CharT, typename TraitsT >
    static bool matches(
        StringT const& str,
        basic_regex< CharT, TraitsT > const& expr,
        match_flag_type flags = match_default)
    {
        return boost::regex_match(str.begin(), str.end(), expr, flags);
    }

    template< typename StringT, typename ParserT >
    static bool matches(
        StringT const& str,
        ParserT const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        const_iterator it = str.begin(), end = str.end();
        return (spirit::qi::parse(it, end, expr) && it == end);
    }

        explicit public_data(BOOST_RV_REF(attribute_value_set) values) :
            m_ref_counter(1),
            m_attribute_values(values)
        {
        }

        ~public_data() {}

    explicit record_view(public_data* impl) : m_impl(impl, false) {}

    record() : m_impl(NULL) {}

    current_process_name() : base_type(boost::log::aux::get_process_name()) {}

        iter() : m_pNode(NULL) {}

        explicit iter(aux::named_scope_list_node* pNode) : m_pNode(pNode) {}

        iter(iter< false > const& that) : m_pNode(that.m_pNode) {}

        template< bool f >
        iter& operator= (iter< f > const& that)
        {
            m_pNode = that.m_pNode;
            return *this;
        }

        template< bool f >
        bool operator== (iter< f > const& that) const { return (m_pNode == that.m_pNode); }

        template< bool f >
        bool operator!= (iter< f > const& that) const { return (m_pNode != that.m_pNode); }

        iter& operator++ ()
        {
            m_pNode = m_pNode->_m_pNext;
            return *this;
        }

        iter& operator-- ()
        {
            m_pNode = m_pNode->_m_pPrev;
            return *this;
        }

        iter operator++ (int)
        {
            iter tmp(*this);
            m_pNode = m_pNode->_m_pNext;
            return tmp;
        }

        iter operator-- (int)
        {
            iter tmp(*this);
            m_pNode = m_pNode->_m_pPrev;
            return tmp;
        }

        pointer operator-> () const { return static_cast< pointer >(m_pNode); }

        reference operator* () const { return *static_cast< pointer >(m_pNode); }

    named_scope_list() : m_Size(0), m_fNeedToDeallocate(false) {}

    named_scope_list& operator= (named_scope_list const& that)
    {
        if (this != &that)
        {
            named_scope_list tmp(that);
            swap(tmp);
        }
        return *this;
    }

    const_iterator begin() const { return const_iterator(m_RootNode._m_pNext); }

    const_iterator end() const { return const_iterator(const_cast< aux::named_scope_list_node* >(&m_RootNode)); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    size_type size() const { return m_Size; }

    bool empty() const { return (m_Size == 0); }

    const_reference back() const { return *rbegin(); }

    const_reference front() const { return *begin(); }

    current_process_id() : base_type(boost::log::aux::this_process::get_id()) {}

    explicit cast_source(attribute::impl* p) : m_pImpl(p)
    {
    }

    template< typename T >
    T* as() const { return dynamic_cast< T* >(m_pImpl); }

    basic_clock() : attribute(new impl())
    {
    }


    value_ref_initializer(RefT& ref) : m_ref(ref)
    {
    }


    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        m_ref = RefT(arg);
    }

    static time_type get_clock()
    {
        return clock_source::universal_time();
    }

    static time_type get_clock()
    {
        return clock_source::local_time();
    }

    explicit counter(value_type initial = (value_type)0, long step = 1) :
#ifndef BOOST_LOG_NO_THREADS
        attribute()
    {
        if (step == 1)
            this->set_impl(new impl_inc(initial));
        else if (step == -1)
            this->set_impl(new impl_dec(initial));
        else
            this->set_impl(new impl_generic(initial, step));
    }

    impl_generic(value_type initial, long step) : m_Initial(initial), m_Step(step), m_Counter(-1)
    {
    }


    attribute_value get_value()
    {
        register unsigned long next_counter = static_cast< unsigned long >(++m_Counter);
        register value_type next = static_cast< value_type >(m_Initial + (next_counter * m_Step));
        return make_attribute_value(next);
    }

    explicit impl_inc(value_type initial) : m_Counter(initial - 1)
    {
    }


    attribute_value get_value()
    {
        return make_attribute_value(static_cast< value_type >(++m_Counter));
    }

    explicit impl_dec(value_type initial) : m_Counter(initial + 1)
    {
    }


    attribute_value get_value()
    {
        return make_attribute_value(static_cast< value_type >(--m_Counter));
    }

    explicit mutable_constant(value_type const& value) : attribute(new impl(value))
    {
    }

    explicit mutable_constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value)))
    {
    }

    void set(value_type const& value)
    {
        get_impl()->set(value);
    }

    value_type get() const
    {
        return get_impl()->get();
    }

    impl* get_impl() const
    {
        return static_cast< impl* >(attribute::get_impl());
    }

    current_thread_id() : attribute(new impl())
    {
    }

    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    static void on_invalid_type(type_info_wrapper const& t)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(invalid_type, "Attribute value has incompatible type", (t));
    }

    static void on_missing_value()
    {
        BOOST_LOG_THROW_DESCR(missing_value, "Attribute value not found");
    }

    fallback_to_default() : m_default()
    {
    }

    template< typename FunT >
    bool apply_default(FunT& fun) const
    {
        fun(m_default);
        return true;
    }

    template< typename FunT >
    bool apply_default(FunT const& fun) const
    {
        fun(m_default);
        return true;
    }

    static void on_invalid_type(type_info_wrapper const&)
    {
    }

    static void on_missing_value()
    {
    }

    scoped_logger_attribute(logger_type& l, attribute_name const& name, attribute const& attr) :
        m_pLogger(boost::addressof(l))
    {
        std::pair<
            attribute_set::iterator,
            bool
        > res = l.add_attribute(name, attr);
        if (res.second)
            m_itAttribute = res.first;
        else
            m_pLogger = 0; // if there already is a same-named attribute, don't register anything
    }

    scoped_logger_attribute(BOOST_RV_REF(scoped_logger_attribute) that) :
        m_pLogger(that.m_pLogger),
        m_itAttribute(that.m_itAttribute)
    {
        that.m_pLogger = 0;
    }

    ~scoped_logger_attribute()
    {
        if (m_pLogger)
            m_pLogger->remove_attribute(m_itAttribute);
    }

    explicit constant(value_type const& value) : attribute(new impl(value)) {}

    explicit constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value))) {}

    value_type const& get() const
    {
        return static_cast< impl* >(this->get_impl())->get();
    }

    explicit attribute_value_impl(value_type const& v) : m_value(v) {}

    explicit attribute_value_impl(BOOST_RV_REF(value_type) v) : m_value(v) {}

    virtual bool dispatch(type_dispatcher& dispatcher)
    {
        type_dispatcher::callback< value_type > callback = dispatcher.get_callback< value_type >();
        if (callback)
        {
            callback(m_value);
            return true;
        }
        else
            return false;
    }

    type_info_wrapper get_type() const { return type_info_wrapper(typeid(value_type)); }

    value_type const& get() const { return m_value; }


template< typename T >
inline attribute_value make_attribute_value(T&& v)
{
    typedef typename remove_cv< typename remove_reference< T >::type >::type value_type;
    return attribute_value(new attribute_value_impl< value_type >(boost::forward< T >(v)));
}

        explicit impl_template(T const& fun) : m_Functor(fun) {}


        attribute_value get_value()
        {
            return attributes::make_attribute_value(m_Functor());
        }

    template< typename T >
    explicit function(T const& fun) : attribute(new impl_template< T >(fun))
    {
    }

    intrusive_ref_counter() : m_RefCounter(0)
    {
    }

    intrusive_ref_counter(intrusive_ref_counter const&) : m_RefCounter(0)
    {
    }

    virtual ~intrusive_ref_counter() {}

    intrusive_ref_counter& operator= (intrusive_ref_counter const&) { return *this; }

    unsigned long use_count() const
    {
        return static_cast< unsigned long >(static_cast< long >(m_RefCounter));
    }

inline void intrusive_ptr_add_ref(const intrusive_ref_counter* p)
{
    ++p->m_RefCounter;
}

inline void intrusive_ptr_release(const intrusive_ref_counter* p)
{
    if (--p->m_RefCounter == 0)
        delete p;
}

        explicit sentry(basic_formatting_ostream& strm) : base_type(strm.stream())
        {
        }

    basic_formatting_ostream() : m_stream(&m_streambuf)
    {
        init_stream();
    }

    explicit basic_formatting_ostream(string_type& str) :
        m_streambuf(str),
        m_stream(&m_streambuf)
    {
        init_stream();
    }

    ~basic_formatting_ostream()
    {
        if (m_streambuf.storage())
            flush();
    }

    void attach(string_type& str)
    {
        m_streambuf.attach(str);
        m_stream.clear(ostream_type::goodbit);
    }

    void detach()
    {
        m_streambuf.detach();
        m_stream.clear(ostream_type::badbit);
    }

    string_type const& str() const
    {
        string_type* storage = m_streambuf.storage();
        BOOST_ASSERT(storage != NULL);

        m_streambuf.pubsync();

        return *storage;
    }

    ostream_type& stream() { return m_stream; }



template< typename CharT, typename TraitsT, typename AllocatorT, typename T >
inline basic_formatting_ostream< CharT, TraitsT, AllocatorT >&
operator<< (basic_formatting_ostream< CharT, TraitsT, AllocatorT >& strm, T const& value)
{
    strm.stream() << value;
    return strm;
}

    explicit eh_cons(handler_type const& handler) : base_type(handler)
    {
    }

    void operator()() const
    {
        try
        {
            base_type::operator()();
        }
        catch (ExceptionT& e)
        {
            this->m_Handler(e);
        }
    }

    explicit exception_handler(handler_type const& handler) : base_type(handler)
    {
    }

    void operator()() const
    {
        base_type::operator()();
    }

    explicit nothrow_exception_handler(handler_type const& handler) : base_type(handler)
    {
    }

    void operator()() const
    {
        try
        {
            base_type::operator()();
        }
        catch (...)
        {
            this->m_Handler();
        }
    }

inline nop make_exception_suppressor()
{
    return nop();
}


        l2_visitor(FunT const& fun, LeftT const& left, bool& result) :
            m_fun(fun), m_left(left), m_result(result)
        {
        }


        template< typename RightT >
        result_type operator() (RightT const& right) const
        {
            m_result = m_fun(m_left, right);
        }


        l1_visitor(attribute_value_ordering const& owner, record_view const& right, bool& result) :
            m_owner(owner), m_right(right), m_result(result)
        {
        }


        template< typename LeftT >
        result_type operator() (LeftT const& left) const
        {
            boost::log::visit< value_type >(m_owner.m_name, m_right, l2_visitor< LeftT >(static_cast< FunT const& >(m_owner), left, m_result));
        }

    explicit attribute_value_ordering(attribute_name const& name, FunT const& fun = FunT()) :
        FunT(fun),
        m_name(name)
    {
    }

    result_type operator() (record_view const& left, record_view const& right) const
    {
        bool result = false;
        if (!boost::log::visit< value_type >(m_name, left, l1_visitor(*this, right, result)))
        {
            return !boost::log::visit< value_type >(m_name, right, nop());
        }
        return result;
    }

inline bool operator!= (type_info_wrapper const& left, type_info_wrapper const& right)
{
    return !left.operator==(right);
}

inline bool operator<= (type_info_wrapper const& left, type_info_wrapper const& right)
{
    return (left.operator==(right) || left.operator<(right));
}

inline bool operator> (type_info_wrapper const& left, type_info_wrapper const& right)
{
    return !(left.operator==(right) || left.operator<(right));
}

inline bool operator>= (type_info_wrapper const& left, type_info_wrapper const& right)
{
    return !left.operator<(right);
}

inline void swap(type_info_wrapper& left, type_info_wrapper& right)
{
    left.swap(right);
}

    explicit once_block_sentry(once_block_flag& f) : m_Flag(f)
    {
    }


    ~once_block_sentry()
    {
        if (m_Flag.status != once_block_flag::initialized)
            rollback();
    }


    bool executed() const
    {
        return (m_Flag.status == once_block_flag::initialized || enter_once_block());
    }


    vistation_invoker(VisitableT& visitable, result_type const& def_val) : m_visitable(visitable), m_def_val(def_val)
    {
    }


    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        return m_visitable.apply_visitor_or_default(binder1st< FunT, ArgT const& >(FunT(), arg), m_def_val);
    }

template< typename T, typename TagT >
inline void swap(value_ref< T, TagT >& left, value_ref< T, TagT >& right)
{
    left.swap(right);
}


    binder1st(FunT const& fun, typename aux::make_arg_type< FirstArgT >::type arg) : FunT(fun), m_arg(arg) {}


    result_type operator() () const
    {
        return FunT::operator()(m_arg);
    }


    template< typename T0 >
    result_type operator() (T0 const& arg0) const
    {
        return FunT::operator()(m_arg, arg0);
    }


    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(m_arg, arg0, arg1);
    }


    binder1st(FunT& fun, typename aux::make_arg_type< FirstArgT >::type arg) : m_fun(fun), m_arg(arg) {}


    result_type operator() () const
    {
        return m_fun(m_arg);
    }
 bind1st(FunT fun, FirstArgT const& arg)
{
    return binder1st< FunT, FirstArgT >(fun, arg);
}


    binder2nd(FunT const& fun, typename aux::make_arg_type< SecondArgT >::type arg) : FunT(fun), m_arg(arg) {}


    template< typename T >
    result_type operator() (T const& arg) const
    {
        return FunT::operator()(arg, m_arg);
    }


    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(arg0, m_arg, arg1);
    }


    binder2nd(FunT& fun, typename aux::make_arg_type< SecondArgT >::type arg) : m_fun(fun), m_arg(arg) {}


    template< typename T >
    result_type operator() (T const& arg) const
    {
        return m_fun(arg, m_arg);
    }
 bind2nd(FunT fun, SecondArgT const& arg)
{
    return binder2nd< FunT, SecondArgT >(fun, arg);
}


    binder3rd(FunT const& fun, typename aux::make_arg_type< ThirdArgT >::type arg) : FunT(fun), m_arg(arg) {}


    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(arg0, arg1, m_arg);
    }


    binder3rd(FunT& fun, typename aux::make_arg_type< ThirdArgT >::type arg) : m_fun(fun), m_arg(arg) {}


    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return m_fun(arg0, arg1, m_arg);
    }
 bind3rd(FunT fun, ThirdArgT const& arg)
{
    return binder3rd< FunT, ThirdArgT >(fun, arg);
}


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left == right);
    }


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left != right);
    }


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left < right);
    }


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left > right);
    }


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left <= right);
    }


    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        return op(left, right, typename mpl::and_< is_integral< T >, is_integral< U > >::type());
    }

    template< typename T, typename U >
    static bool op(T const& left, U const& right, mpl::false_ const&)
    {
        return (left >= right);
    }

    template< typename StringT, typename ExpressionT >
    bool operator() (StringT const& str, ExpressionT const& expr) const
    {
        typedef typename match_traits< ExpressionT >::tag_type tag_type;
        typedef aux::matches_fun_impl< tag_type > impl;
        return impl::matches(str, expr);
    }

    template< typename StringT, typename ExpressionT, typename ArgT >
    bool operator() (StringT const& str, ExpressionT const& expr, ArgT const& arg) const
    {
        typedef typename match_traits< ExpressionT >::tag_type tag_type;
        typedef aux::matches_fun_impl< tag_type > impl;
        return impl::matches(str, expr, arg);
    }


    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log(val);
    }

    virtual filter on_exists_test(attribute_name const& name)
    {
        return filter(expressions::has_attr< value_type >(name));
    }

    virtual filter on_equality_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) == parse_argument(arg));
    }

    virtual filter on_inequality_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) != parse_argument(arg));
    }

    virtual filter on_less_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) < parse_argument(arg));
    }

    virtual filter on_greater_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) > parse_argument(arg));
    }

    virtual filter on_less_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) <= parse_argument(arg));
    }

    virtual filter on_greater_or_equal_relation(attribute_name const& name, string_type const& arg)
    {
        return filter(expressions::attr< value_type >(name) >= parse_argument(arg));
    }

    virtual filter on_custom_relation(attribute_name const& name, string_type const& rel, string_type const& arg)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(parse_error, "The custom attribute value relation \"" + boost::log::aux::to_narrow(arg) + "\" is not supported", (name));
        BOOST_LOG_UNREACHABLE();
    }

    virtual value_type parse_argument(string_type const& arg)
    {
        return boost::lexical_cast< value_type >(arg);
    }

    formatter_type create_formatter(attribute_name const& name, args_map const& args)
    {
        return formatter_type(expressions::stream << expressions::attr< value_type >(name));
    }

        ref(section_type& section, std::string const& section_name) :
            m_section(section),
            m_path(section_name)
        {
        }


        ref& operator[] (std::string const& param_name)
        {
            m_path /= param_name;
            return *this;
        }


        ref& operator= (string_type const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }


        template< bool V >
        ref& operator= (ref< V > const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            optional< string_type > val = value.get();
            if (!!val)
            {
                m_section.m_ptree->put(m_path, val);
            }
            else if (optional< property_tree_type& > node = m_section.m_ptree->get_child_optional(m_path))
            {
                node.put_value(string_type());
            }

            return *this;
        }


        template< typename T >
        ref& operator= (T const& value)
        {
            BOOST_ASSERT(m_section.m_ptree != NULL);
            m_section.m_ptree->put(m_path, value);
            return *this;
        }

    basic_settings_section() : m_ptree(NULL)
    {
    }

    basic_settings_section(basic_settings_section const& that) : m_ptree(that.m_ptree)
    {
    }


template< typename CharT >
inline void swap(basic_settings_section< CharT >& left, basic_settings_section< CharT >& right)
{
    left.swap(right);
}

    basic_settings() : section(new property_tree_type())
    {
    }

    basic_settings(basic_settings const& that) :
        section(that.m_ptree ? new property_tree_type(*that.m_ptree) : static_cast< property_tree_type* >(NULL))
    {
    }

    basic_settings(BOOST_RV_REF(this_type) that)
    {
        this->swap(that);
    }

    explicit basic_settings(property_tree_type const& tree) : section(new property_tree_type(tree))
    {
    }

    ~basic_settings()
    {
        delete this->m_ptree;
    }

    basic_settings& operator= (BOOST_COPY_ASSIGN_REF(basic_settings) that)
    {
        if (this != &that)
        {
            basic_settings tmp = that;
            this->swap(tmp);
        }
        return *this;
    }

    result_type operator() (first_argument_type const& left, second_argument_type const& right) const
    {
        return (left.first < right.first);
    }

    template< typename VisitorT >
    explicit type_sequence_dispatcher(VisitorT& visitor) :
        type_dispatcher(&type_sequence_dispatcher< supported_types >::get_callback),
        m_pVisitor((void*)boost::addressof(visitor)),
        m_DispatchingMap(get_dispatching_map< VisitorT >())
    {
    }

    static callback_base get_callback(type_dispatcher* p, std::type_info const& type)
    {
        type_sequence_dispatcher* const self = static_cast< type_sequence_dispatcher* >(p);
        type_info_wrapper wrapper(type);
        typename dispatching_map::value_type const* begin = &*self->m_DispatchingMap.begin();
        typename dispatching_map::value_type const* end = begin + dispatching_map::static_size;
        typename dispatching_map::value_type const* it =
            std::lower_bound(
                begin,
                end,
                std::make_pair(wrapper, (void*)0),
                dispatching_map_order()
            );

        if (it != end && it->first == wrapper)
            return callback_base(self->m_pVisitor, it->second);
        else
            return callback_base();
    }

    template< typename VisitorT >
    explicit single_type_dispatcher(VisitorT& visitor) :
        type_dispatcher(&single_type_dispatcher< T >::get_callback),
        m_Callback(
            (void*)boost::addressof(visitor),
            &callback_base::trampoline< VisitorT, T >
        )
    {
    }

    static callback_base get_callback(type_dispatcher* p, std::type_info const& type)
    {
        if (type == typeid(visible_type< T >))
        {
            single_type_dispatcher* const self = static_cast< single_type_dispatcher* >(p);
            return self->m_Callback;
        }
        else
            return callback_base();
    }

    template< typename ReceiverT >
    explicit static_type_dispatcher(ReceiverT& receiver) :
        base_type(receiver)
    {
    }
