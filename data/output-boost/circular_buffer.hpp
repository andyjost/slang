
    bool full() const { return m_capacity_ctrl == size(); }

    size_type reserve() const { return m_capacity_ctrl - size(); }

    const capacity_type& capacity() const { return m_capacity_ctrl; }

    void set_capacity(const capacity_type& capacity_ctrl) {
        m_capacity_ctrl = capacity_ctrl;
        if (capacity_ctrl < size()) {
            iterator e = end();
            circular_buffer<T, Alloc>::erase(e - (size() - capacity_ctrl), e);
        }
        adjust_min_capacity();
    }

    void resize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > m_capacity_ctrl)
                m_capacity_ctrl = capacity_type(new_size, m_capacity_ctrl.min_capacity());
            insert(end(), new_size - size(), item);
        } else {
            iterator e = end();
            erase(e - (size() - new_size), e);
        }
    }

    void rset_capacity(const capacity_type& capacity_ctrl) {
        m_capacity_ctrl = capacity_ctrl;
        if (capacity_ctrl < size()) {
            iterator b = begin();
            circular_buffer<T, Alloc>::rerase(b, b + (size() - capacity_ctrl));
        }
        adjust_min_capacity();
    }

    void rresize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > m_capacity_ctrl)
                m_capacity_ctrl = capacity_type(new_size, m_capacity_ctrl.min_capacity());
            rinsert(begin(), new_size - size(), item);
        } else {
            rerase(begin(), end() - new_size);
        }
    }

    explicit circular_buffer_space_optimized(const allocator_type& alloc = allocator_type())
    : circular_buffer<T, Alloc>(0, alloc)
    , m_capacity_ctrl(0) {}

    circular_buffer_space_optimized(const circular_buffer_space_optimized<T, Alloc>& cb)
    : circular_buffer<T, Alloc>(cb.begin(), cb.end(), cb.get_allocator())
    , m_capacity_ctrl(cb.m_capacity_ctrl) {}

    circular_buffer_space_optimized<T, Alloc>& operator = (const circular_buffer_space_optimized<T, Alloc>& cb) {
        if (this == &cb)
            return *this;
        circular_buffer<T, Alloc>::assign(cb.begin(), cb.end());
        m_capacity_ctrl = cb.m_capacity_ctrl;
        return *this;
    }

    void assign(size_type n, param_value_type item) {
        circular_buffer<T, Alloc>::assign(n, item);
        m_capacity_ctrl = capacity_type(n);
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        circular_buffer<T, Alloc>::assign(first, last);
        m_capacity_ctrl = capacity_type(circular_buffer<T, Alloc>::capacity());
    }

    void swap(circular_buffer_space_optimized<T, Alloc>& cb) {
        std::swap(m_capacity_ctrl, cb.m_capacity_ctrl);
        circular_buffer<T, Alloc>::swap(cb);
    }

    void push_back(param_value_type item = value_type()) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_back(item);
    }

    void push_front(param_value_type item = value_type()) {
        check_low_capacity();
        circular_buffer<T, Alloc>::push_front(item);
    }

    void pop_back() {
        circular_buffer<T, Alloc>::pop_back();
        check_high_capacity();
    }

    void pop_front() {
        circular_buffer<T, Alloc>::pop_front();
        check_high_capacity();
    }

    iterator insert(iterator pos, param_value_type item = value_type()) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::insert(begin() + index, item);
    }

    iterator rinsert(iterator pos, param_value_type item = value_type()) {
        size_type index = pos - begin();
        check_low_capacity();
        return circular_buffer<T, Alloc>::rinsert(begin() + index, item);
    }

    iterator erase(iterator pos) {
        iterator it = circular_buffer<T, Alloc>::erase(pos);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    iterator rerase(iterator pos) {
        iterator it = circular_buffer<T, Alloc>::rerase(pos);
        size_type index = it - begin();
        check_high_capacity();
        return begin() + index;
    }

    void clear() { erase(begin(), end()); }

    void adjust_min_capacity() {
        if (m_capacity_ctrl.min_capacity() > circular_buffer<T, Alloc>::capacity())
            circular_buffer<T, Alloc>::set_capacity(m_capacity_ctrl.min_capacity());
        else
            check_high_capacity();
    }

    size_type ensure_reserve(size_type new_capacity, size_type buffer_size) const {
        if (buffer_size + new_capacity / 5 >= new_capacity)
            new_capacity *= 2; // ensure at least 20% reserve
        if (new_capacity > m_capacity_ctrl)
            return m_capacity_ctrl;
        return new_capacity;
    }

    void check_low_capacity(size_type n = 1) {
        size_type new_size = size() + n;
        size_type new_capacity = circular_buffer<T, Alloc>::capacity();
        if (new_size > new_capacity) {
            if (new_capacity == 0)
                new_capacity = 1;
            for (; new_size > new_capacity; new_capacity *= 2) {}
            circular_buffer<T, Alloc>::set_capacity(
                ensure_reserve(new_capacity, new_size));
        }
#if BOOST_CB_ENABLE_DEBUG
        this->invalidate_iterators_except(end());
#endif
    }

    void check_high_capacity() {
        size_type new_capacity = circular_buffer<T, Alloc>::capacity();
        while (new_capacity / 3 >= size()) { // (new_capacity / 3) -> avoid oscillations
            new_capacity /= 2;
            if (new_capacity <= m_capacity_ctrl.min_capacity()) {
                new_capacity = m_capacity_ctrl.min_capacity();
                break;
            }
        }
        circular_buffer<T, Alloc>::set_capacity(
            ensure_reserve(new_capacity, size()));
#if BOOST_CB_ENABLE_DEBUG
        this->invalidate_iterators_except(end());
#endif
    }

    void reduce_capacity(const true_type&) {
        circular_buffer<T, Alloc>::set_capacity((std::max)(m_capacity_ctrl.min_capacity(), size()));
    }

    static size_type init_capacity(const capacity_type& capacity_ctrl, size_type n) {
        BOOST_CB_ASSERT(capacity_ctrl.capacity() >= n); // check for capacity lower than n
        return (std::max)(capacity_ctrl.min_capacity(), n);
    }

template <class T, class Alloc>
inline bool operator == (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return lhs.size() == rhs.size() &&
        std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
inline bool operator < (const circular_buffer_space_optimized<T, Alloc>& lhs,
    const circular_buffer_space_optimized<T, Alloc>& rhs) {
    return std::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

    allocator_type get_allocator() const { return m_alloc; }

    allocator_type& get_allocator() { return m_alloc; }

    iterator begin() { return iterator(this, empty() ? 0 : m_first); }

    iterator end() { return iterator(this, 0); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    reference operator [] (size_type index) {
        BOOST_CB_ASSERT(index < size()); // check for invalid index
        return *add(m_first, index);
    }

    reference at(size_type index) {
        check_position(index);
        return (*this)[index];
    }

    reference front() {
        BOOST_CB_ASSERT(!empty()); // check for empty buffer (front element not available)
        return *m_first;
    }

    reference back() {
        BOOST_CB_ASSERT(!empty()); // check for empty buffer (back element not available)
        return *((m_last == m_buff ? m_end : m_last) - 1);
    }

    array_range array_one() {
        return array_range(m_first, (m_last <= m_first && !empty() ? m_end : m_last) - m_first);
    }

    array_range array_two() {
        return array_range(m_buff, m_last <= m_first && !empty() ? m_last - m_buff : 0);
    }

    pointer linearize() {
        if (empty())
            return 0;
        if (m_first < m_last || m_last == m_buff)
            return m_first;
        pointer src = m_first;
        pointer dest = m_buff;
        size_type moved = 0;
        size_type constructed = 0;
        BOOST_TRY {
            for (pointer first = m_first; dest < src; src = first) {
                for (size_type ii = 0; src < m_end; ++src, ++dest, ++moved, ++ii) {
                    if (moved == size()) {
                        first = dest;
                        break;
                    }
                    if (dest == first) {
                        first += ii;
                        break;
                    }
                    if (is_uninitialized(dest)) {
                        m_alloc.construct(dest, *src);
                        ++constructed;
                    } else {
                        value_type tmp = *src;
                        replace(src, *dest);
                        replace(dest, tmp);
                    }
                }
            }
        } BOOST_CATCH(...) {
            m_last += constructed;
            m_size += constructed;
            BOOST_RETHROW
        }
        BOOST_CATCH_END
        for (src = m_end - constructed; src < m_end; ++src)
            destroy_item(src);
        m_first = m_buff;
        m_last = add(m_buff, size());
#if BOOST_CB_ENABLE_DEBUG
        invalidate_iterators_except(end());
#endif
        return m_buff;
    }

    bool is_linearized() const { return m_first < m_last || m_last == m_buff; }

    void rotate(const_iterator new_begin) {
        BOOST_CB_ASSERT(new_begin.is_valid(this)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(new_begin.m_it != 0);      // check for iterator pointing to end()
        if (full()) {
            m_first = m_last = const_cast<pointer>(new_begin.m_it);
        } else {
            difference_type m = end() - new_begin;
            difference_type n = new_begin - begin();
            if (m < n) {
                for (; m > 0; --m) {
                    push_front(back());
                    pop_back();
                }
            } else {
                for (; n > 0; --n) {
                    push_back(front());
                    pop_front();
                }
            }
        }
    }

    size_type size() const { return m_size; }

    size_type max_size() const {
        return (std::min<size_type>)(m_alloc.max_size(), (std::numeric_limits<difference_type>::max)());
    }

    bool empty() const { return size() == 0; }

    bool full() const { return capacity() == size(); }

    size_type reserve() const { return capacity() - size(); }

    capacity_type capacity() const { return m_end - m_buff; }

    void set_capacity(capacity_type new_capacity) {
        if (new_capacity == capacity())
            return;
        pointer buff = allocate(new_capacity);
        iterator b = begin();
        BOOST_TRY {
            reset(buff,
                cb_details::uninitialized_copy_with_alloc(b, b + (std::min)(new_capacity, size()), buff, m_alloc),
                new_capacity);
        } BOOST_CATCH(...) {
            deallocate(buff, new_capacity);
            BOOST_RETHROW
        }
        BOOST_CATCH_END
    }

    void resize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > capacity())
                set_capacity(new_size);
            insert(end(), new_size - size(), item);
        } else {
            iterator e = end();
            erase(e - (size() - new_size), e);
        }
    }

    void rset_capacity(capacity_type new_capacity) {
        if (new_capacity == capacity())
            return;
        pointer buff = allocate(new_capacity);
        iterator e = end();
        BOOST_TRY {
            reset(buff, cb_details::uninitialized_copy_with_alloc(e - (std::min)(new_capacity, size()),
                e, buff, m_alloc), new_capacity);
        } BOOST_CATCH(...) {
            deallocate(buff, new_capacity);
            BOOST_RETHROW
        }
        BOOST_CATCH_END
    }

    void rresize(size_type new_size, param_value_type item = value_type()) {
        if (new_size > size()) {
            if (new_size > capacity())
                set_capacity(new_size);
            rinsert(begin(), new_size - size(), item);
        } else {
            rerase(begin(), end() - new_size);
        }
    }

    explicit circular_buffer(const allocator_type& alloc = allocator_type())
    : m_buff(0), m_end(0), m_first(0), m_last(0), m_size(0), m_alloc(alloc) {}

    explicit circular_buffer(capacity_type buffer_capacity, const allocator_type& alloc = allocator_type())
    : m_size(0), m_alloc(alloc) {
        initialize_buffer(buffer_capacity);
        m_first = m_last = m_buff;
    }

    circular_buffer(const circular_buffer<T, Alloc>& cb)
    :
#if BOOST_CB_ENABLE_DEBUG
    debug_iterator_registry(),
#endif
    m_size(cb.size()), m_alloc(cb.get_allocator()) {
        initialize_buffer(cb.capacity());
        m_first = m_buff;
        BOOST_TRY {
            m_last = cb_details::uninitialized_copy_with_alloc(cb.begin(), cb.end(), m_buff, m_alloc);
        } BOOST_CATCH(...) {
            deallocate(m_buff, cb.capacity());
            BOOST_RETHROW
        }
        BOOST_CATCH_END
        if (m_last == m_end)
            m_last = m_buff;
    }

    template <class InputIterator>
    circular_buffer(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
    : m_alloc(alloc) {
        initialize(first, last, is_integral<InputIterator>());
    }

    template <class InputIterator>
    circular_buffer(capacity_type buffer_capacity, InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type())
    : m_alloc(alloc) {
        initialize(buffer_capacity, first, last, is_integral<InputIterator>());
    }

    ~circular_buffer() {
        destroy();
#if BOOST_CB_ENABLE_DEBUG
        invalidate_all_iterators();
#endif
    }

    circular_buffer<T, Alloc>& operator = (const circular_buffer<T, Alloc>& cb) {
        if (this == &cb)
            return *this;
        pointer buff = allocate(cb.capacity());
        BOOST_TRY {
            reset(buff, cb_details::uninitialized_copy_with_alloc(cb.begin(), cb.end(), buff, m_alloc), cb.capacity());
        } BOOST_CATCH(...) {
            deallocate(buff, cb.capacity());
            BOOST_RETHROW
        }
        BOOST_CATCH_END
        return *this;
    }

    void assign(size_type n, param_value_type item) {
        assign_n(n, n, cb_details::assign_n<param_value_type, allocator_type>(n, item, m_alloc));
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        assign(first, last, is_integral<InputIterator>());
    }

    template <class InputIterator>
    void assign(capacity_type buffer_capacity, InputIterator first, InputIterator last) {
        assign(buffer_capacity, first, last, is_integral<InputIterator>());
    }

    void swap(circular_buffer<T, Alloc>& cb) {
        swap_allocator(cb, is_stateless<allocator_type>());
        std::swap(m_buff, cb.m_buff);
        std::swap(m_end, cb.m_end);
        std::swap(m_first, cb.m_first);
        std::swap(m_last, cb.m_last);
        std::swap(m_size, cb.m_size);
#if BOOST_CB_ENABLE_DEBUG
        invalidate_all_iterators();
        cb.invalidate_all_iterators();
#endif
    }

    void push_back(param_value_type item = value_type()) {
        if (full()) {
            if (empty())
                return;
            replace(m_last, item);
            increment(m_last);
            m_first = m_last;
        } else {
            m_alloc.construct(m_last, item);
            increment(m_last);
            ++m_size;
        }
    }

    void push_front(param_value_type item = value_type()) {
        BOOST_TRY {
            if (full()) {
                if (empty())
                    return;
                decrement(m_first);
                replace(m_first, item);
                m_last = m_first;
            } else {
                decrement(m_first);
                m_alloc.construct(m_first, item);
                ++m_size;
            }
        } BOOST_CATCH(...) {
            increment(m_first);
            BOOST_RETHROW
        }
        BOOST_CATCH_END
    }

    void pop_back() {
        BOOST_CB_ASSERT(!empty()); // check for empty buffer (back element not available)
        decrement(m_last);
        destroy_item(m_last);
        --m_size;
    }

    void pop_front() {
        BOOST_CB_ASSERT(!empty()); // check for empty buffer (front element not available)
        destroy_item(m_first);
        increment(m_first);
        --m_size;
    }

    iterator insert(iterator pos, param_value_type item = value_type()) {
        BOOST_CB_ASSERT(pos.is_valid(this)); // check for uninitialized or invalidated iterator
        iterator b = begin();
        if (full() && pos == b)
            return b;
        return insert_item(pos, item);
    }

    iterator rinsert(iterator pos, param_value_type item = value_type()) {
        BOOST_CB_ASSERT(pos.is_valid(this)); // check for uninitialized or invalidated iterator
        if (full() && pos.m_it == 0)
            return end();
        if (pos == begin()) {
            BOOST_TRY {
                decrement(m_first);
                construct_or_replace(!full(), m_first, item);
            } BOOST_CATCH(...) {
                increment(m_first);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
            pos.m_it = m_first;
        } else {
            pointer src = m_first;
            pointer dest = m_first;
            decrement(dest);
            pos.m_it = map_pointer(pos.m_it);
            bool construct = !full();
            BOOST_TRY {
                while (src != pos.m_it) {
                    construct_or_replace(construct, dest, *src);
                    increment(src);
                    increment(dest);
                    construct = false;
                }
                decrement(pos.m_it);
                replace(pos.m_it, item);
            } BOOST_CATCH(...) {
                if (!construct && !full()) {
                    decrement(m_first);
                    ++m_size;
                }
                BOOST_RETHROW
            }
            BOOST_CATCH_END
            decrement(m_first);
        }
        if (full())
            m_last = m_first;
        else
            ++m_size;
        return iterator(this, pos.m_it);
    }

    iterator erase(iterator pos) {
        BOOST_CB_ASSERT(pos.is_valid(this)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(pos.m_it != 0);      // check for iterator pointing to end()
        pointer next = pos.m_it;
        increment(next);
        for (pointer p = pos.m_it; next != m_last; p = next, increment(next))
            replace(p, *next);
        decrement(m_last);
        destroy_item(m_last);
        --m_size;
#if BOOST_CB_ENABLE_DEBUG
        return m_last == pos.m_it ? end() : iterator(this, pos.m_it);
#else
        return m_last == pos.m_it ? end() : pos;
#endif
    }

    iterator rerase(iterator pos) {
        BOOST_CB_ASSERT(pos.is_valid(this)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(pos.m_it != 0);      // check for iterator pointing to end()
        pointer prev = pos.m_it;
        pointer p = prev;
        for (decrement(prev); p != m_first; p = prev, decrement(prev))
            replace(p, *prev);
        destroy_item(m_first);
        increment(m_first);
        --m_size;
#if BOOST_CB_ENABLE_DEBUG
        return p == pos.m_it ? begin() : iterator(this, pos.m_it);
#else
        return p == pos.m_it ? begin() : pos;
#endif
    }

    void erase_begin(size_type n) {
        BOOST_CB_ASSERT(n <= size()); // check for n greater than size
#if BOOST_CB_ENABLE_DEBUG
        erase_begin(n, false_type());
#else
        erase_begin(n, is_scalar<value_type>());
#endif
    }

    void erase_end(size_type n) {
        BOOST_CB_ASSERT(n <= size()); // check for n greater than size
#if BOOST_CB_ENABLE_DEBUG
        erase_end(n, false_type());
#else
        erase_end(n, is_scalar<value_type>());
#endif
    }

    void clear() {
        destroy_content();
        m_size = 0;
    }

    void check_position(size_type index) const {
        if (index >= size())
            throw_exception(std::out_of_range("circular_buffer"));
    }

    template <class Pointer>
    void increment(Pointer& p) const {
        if (++p == m_end)
            p = m_buff;
    }

    template <class Pointer>
    void decrement(Pointer& p) const {
        if (p == m_buff)
            p = m_end;
        --p;
    }

    template <class Pointer>
    Pointer add(Pointer p, difference_type n) const {
        return p + (n < (m_end - p) ? n : n - capacity());
    }

    template <class Pointer>
    Pointer sub(Pointer p, difference_type n) const {
        return p - (n > (p - m_buff) ? n - capacity() : n);
    }

    pointer map_pointer(pointer p) const { return p == 0 ? m_last : p; }

    pointer allocate(size_type n) {
        if (n > max_size())
            throw_exception(std::length_error("circular_buffer"));
#if BOOST_CB_ENABLE_DEBUG
        pointer p = (n == 0) ? 0 : m_alloc.allocate(n, 0);
        std::memset(p, cb_details::UNINITIALIZED, sizeof(value_type) * n);
        return p;
#else
        return (n == 0) ? 0 : m_alloc.allocate(n, 0);
#endif
    }

    void deallocate(pointer p, size_type n) {
        if (p != 0)
            m_alloc.deallocate(p, n);
    }

    bool is_uninitialized(const_pointer p) const {
        return p >= m_last && (m_first < m_last || p < m_first);
    }

    void replace(pointer pos, param_value_type item) {
        *pos = item;
#if BOOST_CB_ENABLE_DEBUG
        invalidate_iterators(iterator(this, pos));
#endif
    }

    void construct_or_replace(bool construct, pointer pos, param_value_type item) {
        if (construct)
            m_alloc.construct(pos, item);
        else
            replace(pos, item);
    }

    void destroy_item(pointer p) {
        m_alloc.destroy(p);
#if BOOST_CB_ENABLE_DEBUG
        invalidate_iterators(iterator(this, p));
        std::memset(p, cb_details::UNINITIALIZED, sizeof(value_type));
#endif
    }

    void destroy_if_constructed(pointer pos) {
        if (is_uninitialized(pos))
            destroy_item(pos);
    }

    void destroy_content() {
#if BOOST_CB_ENABLE_DEBUG
        destroy_content(false_type());
#else
        destroy_content(is_scalar<value_type>());
#endif
    }

    void destroy() {
        destroy_content();
        deallocate(m_buff, capacity());
#if BOOST_CB_ENABLE_DEBUG
        m_buff = 0;
        m_first = 0;
        m_last = 0;
        m_end = 0;
#endif
    }

    void initialize_buffer(capacity_type buffer_capacity) {
        m_buff = allocate(buffer_capacity);
        m_end = m_buff + buffer_capacity;
    }

    template <class IntegralType>
    void initialize(IntegralType n, IntegralType item, const true_type&) {
        m_size = static_cast<size_type>(n);
        initialize_buffer(size(), item);
        m_first = m_last = m_buff;
    }

    template <class ForwardIterator>
    void initialize(capacity_type buffer_capacity,
        ForwardIterator first,
        ForwardIterator last,
        size_type distance) {
        initialize_buffer(buffer_capacity);
        m_first = m_buff;
        if (distance > buffer_capacity) {
            std::advance(first, distance - buffer_capacity);
            m_size = buffer_capacity;
        } else {
            m_size = distance;
        }
        BOOST_TRY {
            m_last = cb_details::uninitialized_copy_with_alloc(first, last, m_buff, m_alloc);
        } BOOST_CATCH(...) {
            deallocate(m_buff, buffer_capacity);
            BOOST_RETHROW
        }
        BOOST_CATCH_END
        if (m_last == m_end)
            m_last = m_buff;
    }

    void reset(pointer buff, pointer last, capacity_type new_capacity) {
        destroy();
        m_size = last - buff;
        m_first = m_buff = buff;
        m_end = m_buff + new_capacity;
        m_last = last == m_end ? m_buff : last;
    }

    void swap_allocator(circular_buffer<T, Alloc>&, const true_type&) {
        // Swap is not needed because allocators have no state.
    }

    template <class Functor>
    void assign_n(capacity_type new_capacity, size_type n, const Functor& fnc) {
        if (new_capacity == capacity()) {
            destroy_content();
            BOOST_TRY {
                fnc(m_buff);
            } BOOST_CATCH(...) {
                m_size = 0;
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        } else {
            pointer buff = allocate(new_capacity);
            BOOST_TRY {
                fnc(buff);
            } BOOST_CATCH(...) {
                deallocate(buff, new_capacity);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
            destroy();
            m_buff = buff;
            m_end = m_buff + new_capacity;
        }
        m_size = n;
        m_first = m_buff;
        m_last = add(m_buff, size());
    }

    iterator insert_item(const iterator& pos, param_value_type item) {
        pointer p = pos.m_it;
        if (p == 0) {
            construct_or_replace(!full(), m_last, item);
            p = m_last;
        } else {
            pointer src = m_last;
            pointer dest = m_last;
            bool construct = !full();
            BOOST_TRY {
                while (src != p) {
                    decrement(src);
                    construct_or_replace(construct, dest, *src);
                    decrement(dest);
                    construct = false;
                }
                replace(p, item);
            } BOOST_CATCH(...) {
                if (!construct && !full()) {
                    increment(m_last);
                    ++m_size;
                }
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }
        increment(m_last);
        if (full())
            m_first = m_last;
        else
            ++m_size;
        return iterator(this, p);
    }

    template <class Wrapper>
    void insert_n(const iterator& pos, size_type n, const Wrapper& wrapper) {
        size_type construct = reserve();
        if (construct > n)
            construct = n;
        if (pos.m_it == 0) {
            size_type ii = 0;
            pointer p = m_last;
            BOOST_TRY {
                for (; ii < construct; ++ii, increment(p))
                    m_alloc.construct(p, *wrapper());
                for (;ii < n; ++ii, increment(p))
                    replace(p, *wrapper());
            } BOOST_CATCH(...) {
                size_type constructed = (std::min)(ii, construct);
                m_last = add(m_last, constructed);
                m_size += constructed;
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        } else {
            pointer src = m_last;
            pointer dest = add(m_last, n - 1);
            pointer p = pos.m_it;
            size_type ii = 0;
            BOOST_TRY {
                while (src != pos.m_it) {
                    decrement(src);
                    construct_or_replace(is_uninitialized(dest), dest, *src);
                    decrement(dest);
                }
                for (; ii < n; ++ii, increment(p))
                    construct_or_replace(is_uninitialized(p), p, *wrapper());
            } BOOST_CATCH(...) {
                for (p = add(m_last, n - 1); p != dest; decrement(p))
                    destroy_if_constructed(p);
                for (n = 0, p = pos.m_it; n < ii; ++n, increment(p))
                    destroy_if_constructed(p);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }
        m_last = add(m_last, n);
        m_first = add(m_first, n - construct);
        m_size += construct;
    }

    template <class Wrapper>
    void rinsert_n(const iterator& pos, size_type n, const Wrapper& wrapper) {
        if (n == 0)
            return;
        iterator b = begin();
        size_type copy = capacity() - (pos - b);
        if (copy == 0)
            return;
        if (n > copy)
            n = copy;
        size_type construct = reserve();
        if (construct > n)
            construct = n;
        if (pos == b) {
            pointer p = sub(m_first, n);
            size_type ii = n;
            BOOST_TRY {
                for (;ii > construct; --ii, increment(p))
                    replace(p, *wrapper());
                for (; ii > 0; --ii, increment(p))
                    m_alloc.construct(p, *wrapper());
            } BOOST_CATCH(...) {
                size_type constructed = ii < construct ? construct - ii : 0;
                m_last = add(m_last, constructed);
                m_size += constructed;
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        } else {
            pointer src = m_first;
            pointer dest = sub(m_first, n);
            pointer p = map_pointer(pos.m_it);
            BOOST_TRY {
                while (src != p) {
                    construct_or_replace(is_uninitialized(dest), dest, *src);
                    increment(src);
                    increment(dest);
                }
                for (size_type ii = 0; ii < n; ++ii, increment(dest))
                    construct_or_replace(is_uninitialized(dest), dest, *wrapper());
            } BOOST_CATCH(...) {
                for (src = sub(m_first, n); src != dest; increment(src))
                    destroy_if_constructed(src);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }
        m_first = sub(m_first, n);
        m_last = sub(m_last, n - construct);
        m_size += construct;
    }

template <class T, class Alloc>
inline bool operator == (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
inline bool operator < (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
inline bool operator != (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Alloc>
inline bool operator > (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return rhs < lhs;
}

template <class T, class Alloc>
inline bool operator <= (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return !(rhs < lhs);
}

template <class T, class Alloc>
inline bool operator >= (const circular_buffer<T, Alloc>& lhs, const circular_buffer<T, Alloc>& rhs) {
    return !(lhs < rhs);
}

template <class T, class Alloc>
inline void swap(circular_buffer<T, Alloc>& lhs, circular_buffer<T, Alloc>& rhs) {
    lhs.swap(rhs);
}

    explicit iterator_wrapper(Iterator it) : m_it(it) {}

    Iterator operator () () const { return m_it++; }

    explicit item_wrapper(Value item) : m_item(item) {}

    Pointer operator () () const { return &m_item; }

    assign_n(size_type n, Value item, Alloc& alloc) : m_n(n), m_item(item), m_alloc(alloc) {}

    template <class Pointer>
    void operator () (Pointer p) const {
        uninitialized_fill_n_with_alloc(p, m_n, m_item, m_alloc);
    }

    assign_range(const Iterator& first, const Iterator& last, Alloc& alloc)
    : m_first(first), m_last(last), m_alloc(alloc) {}

    template <class Pointer>
    void operator () (Pointer p) const {
        uninitialized_copy_with_alloc(m_first, m_last, p, m_alloc);
    }

    capacity_control(Size buffer_capacity, Size min_buffer_capacity = 0)
    : m_capacity(buffer_capacity), m_min_capacity(min_buffer_capacity) {
        BOOST_CB_ASSERT(buffer_capacity >= min_buffer_capacity); // check for capacity lower than min_capacity
    }

    Size capacity() const { return m_capacity; }

    Size min_capacity() const { return m_min_capacity; }

    operator Size() const { return m_capacity; }

    iterator() : m_buff(0), m_it(0) {}


    iterator(const nonconst_self& it) : m_buff(it.m_buff), m_it(it.m_it) {}


    iterator(const Buff* cb, const pointer p) : m_buff(cb), m_it(p) {}

    iterator& operator = (const iterator& it) {
        if (this == &it)
            return *this;
#if BOOST_CB_ENABLE_DEBUG
        debug_iterator_base::operator =(it);
#endif // #if BOOST_CB_ENABLE_DEBUG
        m_buff = it.m_buff;
        m_it = it.m_it;
        return *this;
    }

    reference operator * () const {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != 0);        // check for iterator pointing to end()
        return *m_it;
    }

    pointer operator -> () const { return &(operator*()); }

    template <class Traits0>
    difference_type operator - (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return linearize_pointer(*this) - linearize_pointer(it);
    }

    iterator& operator ++ () {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != 0);        // check for iterator pointing to end()
        m_buff->increment(m_it);
        if (m_it == m_buff->m_last)
            m_it = 0;
        return *this;
    }

    iterator operator ++ (int) {
        iterator<Buff, Traits> tmp = *this;
        ++*this;
        return tmp;
    }

    iterator& operator -- () {
        BOOST_CB_ASSERT(is_valid(m_buff));        // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(m_it != m_buff->m_first); // check for iterator pointing to begin()
        if (m_it == 0)
            m_it = m_buff->m_last;
        m_buff->decrement(m_it);
        return *this;
    }

    iterator operator -- (int) {
        iterator<Buff, Traits> tmp = *this;
        --*this;
        return tmp;
    }

    iterator& operator += (difference_type n) {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        if (n > 0) {
            BOOST_CB_ASSERT(m_buff->end() - *this >= n); // check for too large n
            m_it = m_buff->add(m_it, n);
            if (m_it == m_buff->m_last)
                m_it = 0;
        } else if (n < 0) {
            *this -= -n;
        }
        return *this;
    }

    iterator operator + (difference_type n) const { return iterator<Buff, Traits>(*this) += n; }

    iterator& operator -= (difference_type n) {
        BOOST_CB_ASSERT(is_valid(m_buff)); // check for uninitialized or invalidated iterator
        if (n > 0) {
            BOOST_CB_ASSERT(*this - m_buff->begin() >= n); // check for too large n
            m_it = m_buff->sub(m_it == 0 ? m_buff->m_last : m_it, n);
        } else if (n < 0) {
            *this += -n;
        }
        return *this;
    }

    iterator operator - (difference_type n) const { return iterator<Buff, Traits>(*this) -= n; }

    reference operator [] (difference_type n) const { return *(*this + n); }

    template <class Traits0>
    bool operator == (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return m_it == it.m_it;
    }

    template <class Traits0>
    bool operator != (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return m_it != it.m_it;
    }

    template <class Traits0>
    bool operator < (const iterator<Buff, Traits0>& it) const {
        BOOST_CB_ASSERT(is_valid(m_buff));    // check for uninitialized or invalidated iterator
        BOOST_CB_ASSERT(it.is_valid(m_buff)); // check for uninitialized or invalidated iterator
        return linearize_pointer(*this) < linearize_pointer(it);
    }

    template <class Traits0>
    bool operator > (const iterator<Buff, Traits0>& it) const { return it < *this; }

    template <class Traits0>
    bool operator <= (const iterator<Buff, Traits0>& it) const { return !(it < *this); }

    template <class Traits0>
    bool operator >= (const iterator<Buff, Traits0>& it) const { return !(*this < it); }

    template <class Traits0>
    typename Traits0::pointer linearize_pointer(const iterator<Buff, Traits0>& it) const {
        return it.m_it == 0 ? m_buff->m_buff + m_buff->size() :
            (it.m_it < m_buff->m_first ? it.m_it + (m_buff->m_end - m_buff->m_first)
                : m_buff->m_buff + (it.m_it - m_buff->m_first));
    }

template <class Buff, class Traits>
inline iterator<Buff, Traits>
operator + (typename Traits::difference_type n, const iterator<Buff, Traits>& it) {
    return it + n;
}

template<class InputIterator, class ForwardIterator, class Alloc>
inline ForwardIterator uninitialized_copy_with_alloc(InputIterator first, InputIterator last, ForwardIterator dest,
    Alloc& alloc) {
    ForwardIterator next = dest;
    BOOST_TRY {
        for (; first != last; ++first, ++dest)
            alloc.construct(dest, *first);
    } BOOST_CATCH(...) {
        for (; next != dest; ++next)
            alloc.destroy(next);
        BOOST_RETHROW
    }
    BOOST_CATCH_END
    return dest;
}

template<class ForwardIterator, class Diff, class T, class Alloc>
inline void uninitialized_fill_n_with_alloc(ForwardIterator first, Diff n, const T& item, Alloc& alloc) {
    ForwardIterator next = first;
    BOOST_TRY {
        for (; n > 0; ++first, --n)
            alloc.construct(first, item);
    } BOOST_CATCH(...) {
        for (; next != first; ++next)
            alloc.destroy(next);
        BOOST_RETHROW
    }
    BOOST_CATCH_END
}
