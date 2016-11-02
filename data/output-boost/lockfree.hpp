
        node(T const & val):
            v(val)
        {}

    bool is_lock_free (void) const
    {
        return tos.is_lock_free() && pool.is_lock_free();
    }

    stack(void):
        pool(node_allocator(), capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }


    explicit stack(allocator const & alloc):
        pool(alloc, capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    explicit stack(size_type n):
        pool(node_allocator(), n)
    {
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    void reserve(size_type n)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        pool.template reserve<true>(n);
    }

    void reserve_unsafe(size_type n)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        pool.template reserve<false>(n);
    }

    ~stack(void)
    {
        T dummy;
        while(unsynchronized_pop(dummy))
        {}
    }

    void initialize(void)
    {
        tos.store(tagged_node_handle(pool.null_handle(), 0));
    }


    void link_nodes_atomic(node * new_top_node, node * end_node)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_relaxed);
        for (;;) {
            tagged_node_handle new_tos (pool.get_handle(new_top_node), old_tos.get_tag());
            end_node->next = pool.get_handle(old_tos);

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }
    }


    void link_nodes_unsafe(node * new_top_node, node * end_node)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_relaxed);

        tagged_node_handle new_tos (pool.get_handle(new_top_node), old_tos.get_tag());
        end_node->next = pool.get_pointer(old_tos);

        tos.store(new_tos, memory_order_relaxed);
    }


    void initialize(void)
    {
        node * n = pool.template construct<true, false>(pool.null_handle());
        tagged_node_handle dummy_node(pool.get_handle(n), 0);
        head_.store(dummy_node, memory_order_relaxed);
        tail_.store(dummy_node, memory_order_release);
    }

    bool is_lock_free (void) const
    {
        return head_.is_lock_free() && tail_.is_lock_free() && pool.is_lock_free();
    }

    queue(void):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }


    explicit queue(allocator const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    explicit queue(size_type n):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), n + 1)
    {
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    void reserve(size_type n)
    {
        pool.template reserve<true>(n);
    }

    void reserve_unsafe(size_type n)
    {
        pool.template reserve<false>(n);
    }

    ~queue(void)
    {
        T dummy;
        while(unsynchronized_pop(dummy))
        {}

        pool.template destruct<false>(head_.load(memory_order_relaxed));
    }

    bool empty(void)
    {
        return pool.get_handle(head_.load()) == pool.get_handle(tail_.load());
    }

    bool push(T const & t)
    {
        return do_push<false>(t);
    }

    bool bounded_push(T const & t)
    {
        return do_push<true>(t);
    }

    template <bool Bounded>
    bool do_push(T const & t)
    {
        using detail::likely;

        node * n = pool.template construct<true, Bounded>(t, pool.null_handle());
        handle_type node_handle = pool.get_handle(n);

        if (n == NULL)
            return false;

        for (;;) {
            tagged_node_handle tail = tail_.load(memory_order_acquire);
            node * tail_node = pool.get_pointer(tail);
            tagged_node_handle next = tail_node->next.load(memory_order_acquire);
            node * next_ptr = pool.get_pointer(next);

            tagged_node_handle tail2 = tail_.load(memory_order_acquire);
            if (likely(tail == tail2)) {
                if (next_ptr == 0) {
                    tagged_node_handle new_tail_next(node_handle, next.get_next_tag());
                    if ( tail_node->next.compare_exchange_weak(next, new_tail_next) ) {
                        tagged_node_handle new_tail(node_handle, tail.get_next_tag());
                        tail_.compare_exchange_strong(tail, new_tail);
                        return true;
                    }
                }
                else {
                    tagged_node_handle new_tail(pool.get_handle(next_ptr), tail.get_next_tag());
                    tail_.compare_exchange_strong(tail, new_tail);
                }
            }
        }
    }

    bool unsynchronized_push(T const & t)
    {
        node * n = pool.template construct<false, false>(t, pool.null_handle());

        if (n == NULL)
            return false;

        for (;;) {
            tagged_node_handle tail = tail_.load(memory_order_relaxed);
            tagged_node_handle next = tail->next.load(memory_order_relaxed);
            node * next_ptr = next.get_ptr();

            if (next_ptr == 0) {
                tail->next.store(tagged_node_handle(n, next.get_next_tag()), memory_order_relaxed);
                tail_.store(tagged_node_handle(n, tail.get_next_tag()), memory_order_relaxed);
                return true;
            }
            else
                tail_.store(tagged_node_handle(next_ptr, tail.get_next_tag()), memory_order_relaxed);
        }
    }

    bool pop (T & ret)
    {
        return pop<T>(ret);
    }

    template <typename U>
    bool pop (U & ret)
    {
        using detail::likely;
        for (;;) {
            tagged_node_handle head = head_.load(memory_order_acquire);
            node * head_ptr = pool.get_pointer(head);

            tagged_node_handle tail = tail_.load(memory_order_acquire);
            tagged_node_handle next = head_ptr->next.load(memory_order_acquire);
            node * next_ptr = pool.get_pointer(next);

            tagged_node_handle head2 = head_.load(memory_order_acquire);
            if (likely(head == head2)) {
                if (pool.get_handle(head) == pool.get_handle(tail)) {
                    if (next_ptr == 0)
                        return false;

                    tagged_node_handle new_tail(pool.get_handle(next), tail.get_next_tag());
                    tail_.compare_exchange_strong(tail, new_tail);

                } else {
                    if (next_ptr == 0)
                        /* this check is not part of the original algorithm as published by michael and scott
                         *
                         * however we reuse the tagged_ptr part for the freelist and clear the next part during node
                         * allocation. we can observe a null-pointer here.
                         * */
                        continue;
                    detail::copy_payload(next_ptr->data, ret);

                    tagged_node_handle new_head(pool.get_handle(next), head.get_next_tag());
                    if (head_.compare_exchange_weak(head, new_head)) {
                        pool.template destruct<true>(head);
                        return true;
                    }
                }
            }
        }
    }

    bool unsynchronized_pop (T & ret)
    {
        return unsynchronized_pop<T>(ret);
    }

    template <typename U>
    bool unsynchronized_pop (U & ret)
    {
        for (;;) {
            tagged_node_handle head = head_.load(memory_order_relaxed);
            node * head_ptr = pool.get_pointer(head);
            tagged_node_handle tail = tail_.load(memory_order_relaxed);
            tagged_node_handle next = head_ptr->next.load(memory_order_relaxed);
            node * next_ptr = pool.get_pointer(next);

            if (pool.get_handle(head) == pool.get_handle(tail)) {
                if (next_ptr == 0)
                    return false;

                tagged_node_handle new_tail(pool.get_handle(next), tail.get_next_tag());
                tail_.store(new_tail);
            } else {
                if (next_ptr == 0)
                    /* this check is not part of the original algorithm as published by michael and scott
                     *
                     * however we reuse the tagged_ptr part for the freelist and clear the next part during node
                     * allocation. we can observe a null-pointer here.
                     * */
                    continue;
                detail::copy_payload(next_ptr->data, ret);
                tagged_node_handle new_head(pool.get_handle(next), head.get_next_tag());
                head_.store(new_head);
                pool.template destruct<false>(head);
                return true;
            }
        }
    }

    template <typename Functor>
    bool consume_one(Functor & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    template <typename Functor>
    size_t consume_all(Functor & f)
    {
        size_t element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }

    ringbuffer_base(void):
        write_index_(0), read_index_(0)
    {}


    static size_t next_index(size_t arg, size_t max_size)
    {
        size_t ret = arg + 1;
        while (unlikely(ret >= max_size))
            ret -= max_size;
        return ret;
    }


    static size_t read_available(size_t write_index, size_t read_index, size_t max_size)
    {
        if (write_index >= read_index)
            return write_index - read_index;

        size_t ret = write_index + max_size - read_index;
        return ret;
    }


    static size_t write_available(size_t write_index, size_t read_index, size_t max_size)
    {
        size_t ret = read_index - write_index - 1;
        if (write_index >= read_index)
            ret += max_size;
        return ret;
    }


    bool push(T const & t, T * buffer, size_t max_size)
    {
        size_t write_index = write_index_.load(memory_order_relaxed);  // only written from push thread
        size_t next = next_index(write_index, max_size);

        if (next == read_index_.load(memory_order_acquire))
            return false; /* ringbuffer is full */

        buffer[write_index] = t;

        write_index_.store(next, memory_order_release);

        return true;
    }


    size_t push(const T * input_buffer, size_t input_count, T * internal_buffer, size_t max_size)
    {
        size_t write_index = write_index_.load(memory_order_relaxed);  // only written from push thread
        const size_t read_index  = read_index_.load(memory_order_acquire);
        const size_t avail = write_available(write_index, read_index, max_size);

        if (avail == 0)
            return 0;

        input_count = (std::min)(input_count, avail);

        size_t new_write_index = write_index + input_count;

        if (write_index + input_count > max_size) {
            /* copy data in two sections */
            size_t count0 = max_size - write_index;

            std::copy(input_buffer, input_buffer + count0, internal_buffer + write_index);
            std::copy(input_buffer + count0, input_buffer + input_count, internal_buffer);
            new_write_index -= max_size;
        } else {
            std::copy(input_buffer, input_buffer + input_count, internal_buffer + write_index);

            if (new_write_index == max_size)
                new_write_index = 0;
        }

        write_index_.store(new_write_index, memory_order_release);
        return input_count;
    }


    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end, T * internal_buffer, size_t max_size)
    {
        // FIXME: avoid std::distance and std::advance

        size_t write_index = write_index_.load(memory_order_relaxed);  // only written from push thread
        const size_t read_index  = read_index_.load(memory_order_acquire);
        const size_t avail = write_available(write_index, read_index, max_size);

        if (avail == 0)
            return begin;

        size_t input_count = std::distance(begin, end);
        input_count = (std::min)(input_count, avail);

        size_t new_write_index = write_index + input_count;

        ConstIterator last = begin;
        std::advance(last, input_count);

        if (write_index + input_count > max_size) {
            /* copy data in two sections */
            size_t count0 = max_size - write_index;
            ConstIterator midpoint = begin;
            std::advance(midpoint, count0);

            std::copy(begin, midpoint, internal_buffer + write_index);
            std::copy(midpoint, last, internal_buffer);
            new_write_index -= max_size;
        } else {
            std::copy(begin, last, internal_buffer + write_index);

            if (new_write_index == max_size)
                new_write_index = 0;
        }

        write_index_.store(new_write_index, memory_order_release);
        return last;
    }


    bool pop (T & ret, T * buffer, size_t max_size)
    {
        size_t write_index = write_index_.load(memory_order_acquire);
        size_t read_index  = read_index_.load(memory_order_relaxed); // only written from pop thread
        if (empty(write_index, read_index))
            return false;

        ret = buffer[read_index];
        size_t next = next_index(read_index, max_size);
        read_index_.store(next, memory_order_release);
        return true;
    }


    size_t pop (T * output_buffer, size_t output_count, const T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);

        if (avail == 0)
            return 0;

        output_count = (std::min)(output_count, avail);

        size_t new_read_index = read_index + output_count;

        if (read_index + output_count > max_size) {
            /* copy data in two sections */
            size_t count0 = max_size - read_index;
            size_t count1 = output_count - count0;

            std::copy(internal_buffer + read_index, internal_buffer + max_size, output_buffer);
            std::copy(internal_buffer, internal_buffer + count1, output_buffer + count0);

            new_read_index -= max_size;
        } else {
            std::copy(internal_buffer + read_index, internal_buffer + read_index + output_count, output_buffer);
            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return output_count;
    }


    template <typename OutputIterator>
    size_t pop (OutputIterator it, const T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);
        if (avail == 0)
            return 0;

        size_t new_read_index = read_index + avail;

        if (read_index + avail > max_size) {
            /* copy data in two sections */
            size_t count0 = max_size - read_index;
            size_t count1 = avail - count0;

            it = std::copy(internal_buffer + read_index, internal_buffer + max_size, it);
            std::copy(internal_buffer, internal_buffer + count1, it);

            new_read_index -= max_size;
        } else {
            std::copy(internal_buffer + read_index, internal_buffer + read_index + avail, it);
            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return avail;
    }

    void reset(void)
    {
        write_index_.store(0, memory_order_relaxed);
        read_index_.store(0, memory_order_release);
    }

    bool empty(void)
    {
        return empty(write_index_.load(memory_order_relaxed), read_index_.load(memory_order_relaxed));
    }

    bool is_lock_free(void) const
    {
        return write_index_.is_lock_free() && read_index_.is_lock_free();
    }

    bool empty(size_t write_index, size_t read_index)
    {
        return write_index == read_index;
    }

    bool push(T const & t)
    {
        return ringbuffer_base<T>::push(t, array_.c_array(), max_size);
    }


    bool pop(T & ret)
    {
        return ringbuffer_base<T>::pop(ret, array_.c_array(), max_size);
    }


    size_t push(T const * t, size_t size)
    {
        return ringbuffer_base<T>::push(t, size, array_.c_array(), max_size);
    }


    template <size_t size>
    size_t push(T const (&t)[size])
    {
        return push(t, size);
    }


    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return ringbuffer_base<T>::push(begin, end, array_.c_array(), max_size);
    }


    size_t pop(T * ret, size_t size)
    {
        return ringbuffer_base<T>::pop(ret, size, array_.c_array(), max_size);
    }


    template <size_t size>
    size_t pop(T (&ret)[size])
    {
        return pop(ret, size);
    }


    template <typename OutputIterator>
    size_t pop(OutputIterator it)
    {
        return ringbuffer_base<T>::pop(it, array_.c_array(), max_size);
    }

    explicit runtime_sized_ringbuffer(size_t max_elements):
        max_elements_(max_elements + 1)
    {
        // TODO: we don't necessarily need to construct all elements
        array_ = Alloc::allocate(max_elements_);
        for (size_t i = 0; i != max_elements_; ++i)
            Alloc::construct(array_ + i, T());
    }


    template <typename U>
    runtime_sized_ringbuffer(typename Alloc::template rebind<U>::other const & alloc, size_t max_elements):
        Alloc(alloc), max_elements_(max_elements + 1)
    {
        // TODO: we don't necessarily need to construct all elements
        array_ = Alloc::allocate(max_elements_);
        for (size_t i = 0; i != max_elements_; ++i)
            Alloc::construct(array_ + i, T());
    }


    runtime_sized_ringbuffer(Alloc const & alloc, size_t max_elements):
        Alloc(alloc), max_elements_(max_elements + 1)
    {
        // TODO: we don't necessarily need to construct all elements
        array_ = Alloc::allocate(max_elements_);
        for (size_t i = 0; i != max_elements_; ++i)
            Alloc::construct(array_ + i, T());
    }


    ~runtime_sized_ringbuffer(void)
    {
        for (size_t i = 0; i != max_elements_; ++i)
            Alloc::destroy(array_ + i);
        Alloc::deallocate(array_, max_elements_);
    }


    bool push(T const & t)
    {
        return ringbuffer_base<T>::push(t, &*array_, max_elements_);
    }


    bool pop(T & ret)
    {
        return ringbuffer_base<T>::pop(ret, &*array_, max_elements_);
    }


    size_t push(T const * t, size_t size)
    {
        return ringbuffer_base<T>::push(t, size, &*array_, max_elements_);
    }


    template <size_t size>
    size_t push(T const (&t)[size])
    {
        return push(t, size);
    }


    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return ringbuffer_base<T>::push(begin, end, array_, max_elements_);
    }


    size_t pop(T * ret, size_t size)
    {
        return ringbuffer_base<T>::pop(ret, size, array_, max_elements_);
    }


    template <size_t size>
    size_t pop(T (&ret)[size])
    {
        return pop(ret, size);
    }


    template <typename OutputIterator>
    size_t pop(OutputIterator it)
    {
        return ringbuffer_base<T>::pop(it, array_, max_elements_);
    }

    spsc_queue(void)
    {
        BOOST_ASSERT(!runtime_sized);
    }


    template <typename U>
    explicit spsc_queue(typename allocator::template rebind<U>::other const & alloc)
    {
        // just for API compatibility: we don't actually need an allocator
        BOOST_STATIC_ASSERT(!runtime_sized);
    }


    explicit spsc_queue(allocator const & alloc)
    {
        // just for API compatibility: we don't actually need an allocator
        BOOST_ASSERT(!runtime_sized);
    }

    explicit spsc_queue(size_type element_count):
        base_type(element_count)
    {
        BOOST_ASSERT(runtime_sized);
    }


    template <typename U>
    spsc_queue(size_type element_count, typename allocator::template rebind<U>::other const & alloc):
        base_type(alloc, element_count)
    {
        BOOST_STATIC_ASSERT(runtime_sized);
    }


    spsc_queue(size_type element_count, allocator_arg const & alloc):
        base_type(alloc, element_count)
    {
        BOOST_ASSERT(runtime_sized);
    }

    bool push(T const & t)
    {
        return base_type::push(t);
    }

    bool pop(T & ret)
    {
        return base_type::pop(ret);
    }

    size_type push(T const * t, size_type size)
    {
        return base_type::push(t, size);
    }

    template <size_type size>
    size_type push(T const (&t)[size])
    {
        return push(t, size);
    }

    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return base_type::push(begin, end);
    }

    size_type pop(T * ret, size_type size)
    {
        return base_type::pop(ret, size);
    }

    template <size_type size>
    size_type pop(T (&ret)[size])
    {
        return pop(ret, size);
    }

    template <typename OutputIterator>
    size_type pop(OutputIterator it)
    {
        return base_type::pop(it);
    }

    template <typename Functor>
    bool consume_one(Functor & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    template <typename Functor>
    size_type consume_all(Functor & f)
    {
        size_type element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }

    template <typename Functor>
    size_type consume_all(Functor const & f)
    {
        size_type element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }


    static T* extract_ptr(volatile compressed_ptr_t const & i)
    {
        return (T*)(i & ptr_mask);
    }


    static tag_t extract_tag(volatile compressed_ptr_t const & i)
    {
        cast_unit cu;
        cu.value = i;
        return cu.tag[tag_index];
    }


    static compressed_ptr_t pack_ptr(T * ptr, int tag)
    {
        cast_unit ret;
        ret.value = compressed_ptr_t(ptr);
        ret.tag[tag_index] = tag;
        return ret.value;
    }


    explicit tagged_ptr(T * p, tag_t t = 0):
        ptr(pack_ptr(p, t))
    {}


    void set(T * p, tag_t t)
    {
        ptr = pack_ptr(p, t);
    }

    bool operator== (volatile tagged_ptr const & p) const
    {
        return (ptr == p.ptr);
    }


    bool operator!= (volatile tagged_ptr const & p) const
    {
        return !operator==(p);
    }

    T * get_ptr() const
    {
        return extract_ptr(ptr);
    }


    void set_ptr(T * p)
    {
        tag_t tag = get_tag();
        ptr = pack_ptr(p, tag);
    }

    tag_t get_tag() const
    {
        return extract_tag(ptr);
    }


    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1) & (std::numeric_limits<tag_t>::max)();
        return next;
    }


    void set_tag(tag_t t)
    {
        T * p = get_ptr();
        ptr = pack_ptr(p, t);
    }

    T & operator*() const
    {
        return *get_ptr();
    }


    T * operator->() const
    {
        return get_ptr();
    }


    operator bool(void) const
    {
        return get_ptr() != 0;
    }

    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = t;
    }

    template <typename T, typename U>
    static void copy(T & t, U & u)
    {
        u = U(t);
    }


template <typename T, typename U>
void copy_payload(T & t, U & u)
{
    typedef typename boost::mpl::if_<typename boost::is_convertible<T, U>::type,
                                     copy_convertible,
                                     copy_constructible_and_copyable
                                    >::type copy_type;
    copy_type::copy(t, u);
}


    explicit tagged_index(index_t i, tag_t t = 0):
        index(i), tag(t)
    {}

    index_t get_index() const
    {
        return index;
    }


    void set_index(index_t i)
    {
        index = i;
    }

    tag_t get_tag() const
    {
        return tag;
    }


    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1) & (std::numeric_limits<tag_t>::max)();
        return next;
    }


    void set_tag(tag_t t)
    {
        tag = t;
    }


    bool operator==(tagged_index const & rhs) const
    {
        return (index == rhs.index) && (tag == rhs.tag);
    }


    bool operator!=(tagged_index const & rhs) const
    {
        return !operator==(rhs);
    }

    template <typename Allocator>
    compiletime_sized_freelist_storage(Allocator const & /* alloc */, std::size_t /* count */)
    {}


    T * nodes(void) const
    {
        return reinterpret_cast<T*>(const_cast<char*>(data.data()));
    }


    std::size_t node_count(void) const
    {
        return size;
    }

inline bool likely(bool expr)
{
#ifdef __GNUC__
    return __builtin_expect(expr, true);
#else
    return expr;
#endif
    }

inline bool unlikely(bool expr)
{
#ifdef __GNUC__
    return __builtin_expect(expr, false);
#else
    return expr;
#endif
}
