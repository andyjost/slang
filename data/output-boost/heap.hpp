
        static void reserve (Heap1 & lhs, std::size_t required_size)
        {}

        static void reserve (Heap1 & lhs, std::size_t required_size)
        {
            lhs.reserve(required_size);
        }


    static void merge(Heap1 & lhs, Heap2 & rhs)
    {
        if (Heap1::constant_time_size && Heap2::constant_time_size) {
            if (Heap1::has_reserve) {
                std::size_t required_size = lhs.size() + rhs.size();
                space_reserver::reserve(lhs, required_size);
            }
        }

        // FIXME: container adaptors could benefit from first appending all elements and then restoring the heap order
        // FIXME: optimize: if we have ordered iterators and we can efficiently insert keys with a below the lowest key in the heap
        //                  d-ary, b and fibonacci heaps fall into this category

        while (!rhs.empty()) {
            lhs.push(rhs.top());
            rhs.pop();
        }

        lhs.set_stability_count((std::max)(lhs.get_stability_count(),
                                           rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    static void merge(Heap & lhs, Heap & rhs)
    {
        lhs.merge(rhs);
    }


    static void merge(Heap & lhs, Heap & rhs)
    {
        heap_merger::merge(lhs, rhs);
    }

template <typename Heap1,
          typename Heap2
         >
void heap_merge(Heap1 & lhs, Heap2 & rhs)
{
    BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
    BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

    // if this assertion is triggered, the value_compare types are incompatible
    BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

    const bool same_heaps = boost::is_same<Heap1, Heap2>::value;

    typedef typename boost::mpl::if_c<same_heaps,
                                      detail::heap_merge_same<Heap1>,
                                      detail::heap_merge_emulate<Heap1, Heap2>
                                     >::type heap_merger;

    heap_merger::merge(lhs, rhs);
}

    template <typename T>
    static void run(T &, std::size_t)
    {}

            static size_type max_index(const d_ary_heap * heap)
            {
                return heap->q_.size() - 1;
            }


            static bool is_leaf(const d_ary_heap * heap, size_type index)
            {
                return !heap->not_leaf(index);
            }


    explicit d_ary_heap(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}


    d_ary_heap(d_ary_heap const & rhs):
        super_t(rhs), q_(rhs.q_)
    {}

    d_ary_heap(d_ary_heap && rhs):
        super_t(std::move(rhs)), q_(std::move(rhs.q_))
    {}


    d_ary_heap & operator=(d_ary_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        q_ = std::move(rhs.q_);
        return *this;
    }


    d_ary_heap & operator=(d_ary_heap const & rhs)
    {
        static_cast<super_t&>(*this) = static_cast<super_t const &>(rhs);
        q_ = rhs.q_;
        return *this;
    }


    bool empty(void) const
    {
        return q_.empty();
    }


    size_type size(void) const
    {
        return q_.size();
    }


    size_type max_size(void) const
    {
        return q_.max_size();
    }


    void clear(void)
    {
        q_.clear();
    }


    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }


    value_type const & top(void) const
    {
        BOOST_ASSERT(!empty());
        return super_t::get_value(q_.front());
    }


    void push(value_type const & v)
    {
        q_.push_back(super_t::make_node(v));
        reset_index(size() - 1, size() - 1);
        siftup(q_.size() - 1);
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        q_.emplace_back(super_t::make_node(std::forward<Args>(args)...));
        reset_index(size() - 1, size() - 1);
        siftup(q_.size() - 1);
    }

    void pop(void)
    {
        BOOST_ASSERT(!empty());
        std::swap(q_.front(), q_.back());
        q_.pop_back();

        if (q_.empty())
            return;

        reset_index(0, 0);
        siftdown(0);
    }


    void swap(d_ary_heap & rhs)
    {
        super_t::swap(rhs);
        q_.swap(rhs.q_);
    }


    iterator begin(void) const
    {
        return iterator(q_.begin());
    }


    iterator end(void) const
    {
        return iterator(q_.end());
    }


    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(0, this, super_t::get_internal_cmp());
    }


    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(size(), this, super_t::get_internal_cmp());
    }


    void reserve (size_type element_count)
    {
        q_.reserve(element_count);
    }


    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    void reset_index(size_type index, size_type new_index)
    {
        BOOST_HEAP_ASSERT(index < q_.size());
        index_updater::run(q_[index], new_index);
    }


    void siftdown(size_type index)
    {
        while (not_leaf(index)) {
            size_type max_child_index = top_child_index(index);
            if (!super_t::operator()(q_[max_child_index], q_[index])) {
                reset_index(index, max_child_index);
                reset_index(max_child_index, index);
                std::swap(q_[max_child_index], q_[index]);
                index = max_child_index;
            }
            else
                return;
        }
    }

    void siftup(size_type index)
    {
        while (index != 0) {
            size_type parent = parent_index(index);

            if (super_t::operator()(q_[parent], q_[index])) {
                reset_index(index, parent);
                reset_index(parent, index);
                std::swap(q_[parent], q_[index]);
                index = parent;
            }
            else
                return;
        }
    }


    bool not_leaf(size_type index) const
    {
        const size_t first_child = first_child_index(index);
        return first_child < q_.size();
    }


    size_type top_child_index(size_type index) const
    {
        // invariant: index is not a leaf, so the iterator range is not empty

        const size_t first_index = first_child_index(index);
        typedef typename container_type::const_iterator container_iterator;

        const container_iterator first_child = q_.begin() + first_index;
        const container_iterator end = q_.end();

        const size_type max_elements = std::distance(first_child, end);

        const container_iterator last_child = (max_elements > D) ? first_child + D
                                                                 : end;

        const container_iterator min_element = std::max_element(first_child, last_child, static_cast<super_t const &>(*this));

        return min_element - q_.begin();
    }


    static size_type parent_index(size_type index)
    {
        return (index - 1) / D;
    }


    static size_type first_child_index(size_type index)
    {
        return index * D + 1;
    }


    size_type last_child_index(size_type index) const
    {
        typedef typename container_type::const_iterator container_iterator;
        const size_t first_index = first_child_index(index);

        const size_type last_index = (std::min)(first_index + D - 1, size() - 1);

        return last_index;
    }


    void update(size_type index)
    {
        if (index == 0) {
            siftdown(index);
            return;
        }
        size_type parent = parent_index(index);

        if (super_t::operator()(q_[parent], q_[index]))
            siftup(index);
        else
            siftdown(index);
    }


    void erase(size_type index)
    {
        while (index != 0)
        {
            size_type parent = parent_index(index);

            reset_index(index, parent);
            reset_index(parent, index);
            std::swap(q_[parent], q_[index]);
            index = parent;
        }
        pop();
    }


    void increase(size_type index)
    {
        siftup(index);
    }


    void decrease(size_type index)
    {
        siftdown(index);
    }

    explicit d_ary_heap(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}

    d_ary_heap(d_ary_heap const & rhs):
        super_t(rhs)
    {}

    d_ary_heap(d_ary_heap && rhs):
        super_t(std::move(rhs))
    {}

    d_ary_heap & operator=(d_ary_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        return *this;
    }

    d_ary_heap & operator=(d_ary_heap const & rhs)
    {
        super_t::operator=(rhs);
        return *this;
    }

    bool empty(void) const
    {
        return super_t::empty();
    }

    size_type size(void) const
    {
        return super_t::size();
    }

    size_type max_size(void) const
    {
        return super_t::max_size();
    }

    void clear(void)
    {
        super_t::clear();
    }

    allocator_type get_allocator(void) const
    {
        return super_t::get_allocator();
    }

    value_type const & top(void) const
    {
        return super_t::top();
    }

        type(compare_argument const & arg):
            base_type(arg)
        {}

        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
        {}


        type(type & rhs):
            base_type(static_cast<base_type&>(rhs)),
            allocator_type(static_cast<allocator_type&>(rhs))
        {}


        type & operator=(type && rhs)
        {
            base_type::operator=(std::move(static_cast<base_type&>(rhs)));
            allocator_type::operator=(std::move(static_cast<allocator_type&>(rhs)));
            return *this;
        }


        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }

    explicit fibonacci_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), top_element(0)
    {}

    fibonacci_heap(fibonacci_heap const & rhs):
        super_t(rhs), top_element(0)
    {
        if (rhs.empty())
            return;

        clone_forest(rhs);
        size_holder::set_size(rhs.size());
    }

    fibonacci_heap(fibonacci_heap && rhs):
        super_t(std::move(rhs)), top_element(rhs.top_element)
    {
        roots.splice(roots.begin(), rhs.roots);
        rhs.top_element = NULL;
    }


    fibonacci_heap(fibonacci_heap & rhs):
        super_t(rhs), top_element(rhs.top_element)
    {
        roots.splice(roots.begin(), rhs.roots);
        rhs.top_element = NULL;
    }

    fibonacci_heap & operator=(fibonacci_heap && rhs)
    {
        clear();

        super_t::operator=(std::move(rhs));
        roots.splice(roots.begin(), rhs.roots);
        top_element = rhs.top_element;
        rhs.top_element = NULL;
        return *this;
    }

    fibonacci_heap & operator=(fibonacci_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.size());
        static_cast<super_t&>(*this) = rhs;

        if (rhs.empty())
            top_element = NULL;
        else
            clone_forest(rhs);
        return *this;
    }


    ~fibonacci_heap(void)
    {
        clear();
    }

    bool empty(void) const
    {
        if (constant_time_size)
            return size() == 0;
        else
            return roots.empty();
    }

    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (empty())
            return 0;
        else
            return detail::count_list_nodes<node, node_list_type>(roots);
    }

    size_type max_size(void) const
    {
        return allocator_type::max_size();
    }

    void clear(void)
    {
        typedef detail::node_disposer<node, typename node_list_type::value_type, allocator_type> disposer;
        roots.clear_and_dispose(disposer(*this));

        size_holder::set_size(0);
        top_element = NULL;
    }

    allocator_type get_allocator(void) const
    {
        return *this;
    }

    void swap(fibonacci_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(top_element, rhs.top_element);
        roots.swap(rhs.roots);
    }

    value_type const & top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(top_element->value);
    }

    handle_type push(value_type const & v)
    {
        size_holder::increment();

        node_pointer n = allocator_type::allocate(1);

        new(n) node(super_t::make_node(v));
        roots.push_front(*n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;
        return handle_type(n);
    }

    template <class... Args>
    handle_type emplace(Args&&... args)
    {
        size_holder::increment();

        node_pointer n = allocator_type::allocate(1);

        new(n) node(super_t::make_node(std::forward<Args>(args)...));
        roots.push_front(*n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;
        return handle_type(n);
    }

    void pop(void)
    {
        BOOST_ASSERT(!empty());

        node_pointer element = top_element;
        roots.erase(node_list_type::s_iterator_to(*element));

        finish_erase_or_pop(element);
    }

    void update (handle_type handle, const_reference v)
    {
        if (super_t::operator()(super_t::get_value(handle.node_->value), v))
            increase(handle, v);
        else
            decrease(handle, v);
    }

    void update_lazy(handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        update_lazy(handle);
    }

    void update (handle_type handle)
    {
        node_pointer n = handle.node_;
        node_pointer parent = n->get_parent();

        if (parent) {
            n->parent = NULL;
            roots.splice(roots.begin(), parent->children, node_list_type::s_iterator_to(*n));
        }
        add_children_to_root(n);
        consolidate();
    }

    void update_lazy (handle_type handle)
    {
        node_pointer n = handle.node_;
        node_pointer parent = n->get_parent();

        if (parent) {
            n->parent = NULL;
            roots.splice(roots.begin(), parent->children, node_list_type::s_iterator_to(*n));
        }
        add_children_to_root(n);
    }

    void increase (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        increase(handle);
    }

    void increase (handle_type handle)
    {
        node_pointer n = handle.node_;

        if (n->parent) {
            if (super_t::operator()(n->get_parent()->value, n->value)) {
                node_pointer parent = n->get_parent();
                cut(n);
                cascading_cut(parent);
            }
        }

        if (super_t::operator()(top_element->value, n->value)) {
            top_element = n;
            return;
        }
    }

    void decrease (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        decrease(handle);
    }

    void decrease (handle_type handle)
    {
        update(handle);
    }

    void erase(handle_type const & handle)
    {
        node_pointer element = handle.node_;
        node_pointer parent = element->get_parent();

        if (parent)
            parent->children.erase(node_list_type::s_iterator_to(*element));
        else
            roots.erase(node_list_type::s_iterator_to(*element));

        finish_erase_or_pop(element);
    }

    iterator begin(void) const
    {
        return iterator(roots.begin());
    }

    iterator end(void) const
    {
        return iterator(roots.end());
    }

    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(roots.begin(), roots.end(), top_element, super_t::value_comp());
    }

    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }

    void merge(fibonacci_heap & rhs)
    {
        size_holder::add(rhs.get_size());

        if (!top_element ||
            (rhs.top_element && super_t::operator()(top_element->value, rhs.top_element->value)))
            top_element = rhs.top_element;

        roots.splice(roots.end(), rhs.roots);

        rhs.set_size(0);

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node * ptr = const_cast<node *>(it.get_node());
        return handle_type(ptr);
    }

    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }

    void clone_forest(fibonacci_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(roots.empty());
        typedef typename node::template node_cloner<allocator_type> node_cloner;
        roots.clone_from(rhs.roots, node_cloner(*this, NULL), detail::nop_disposer());

        top_element = detail::find_max_child<node_list_type, node, internal_compare>(roots, super_t::get_internal_cmp());
    }


    void cut(node_pointer n)
    {
        node_pointer parent = n->get_parent();
        roots.splice(roots.begin(), parent->children, node_list_type::s_iterator_to(*n));
        n->parent = 0;
        n->mark = false;
    }


    void cascading_cut(node_pointer n)
    {
        node_pointer parent = n->get_parent();

        if (parent) {
            if (!parent->mark)
                parent->mark = true;
            else {
                cut(n);
                cascading_cut(parent);
            }
        }
    }


    void add_children_to_root(node_pointer n)
    {
        for (node_list_iterator it = n->children.begin(); it != n->children.end(); ++it) {
            node_pointer child = static_cast<node_pointer>(&*it);
            child->parent = 0;
        }

        roots.splice(roots.end(), n->children);
    }


    void consolidate(void)
    {
        if (roots.empty())
            return;

        static const size_type max_log2 = sizeof(size_type) * 8;
        boost::array<node_pointer, max_log2> aux;
        aux.assign(NULL);

        node_list_iterator it = roots.begin();
        top_element = static_cast<node_pointer>(&*it);

        do {
            node_pointer n = static_cast<node_pointer>(&*it);
            ++it;
            size_type node_rank = n->child_count();

            if (aux[node_rank] == NULL)
                aux[node_rank] = n;
            else {
                do {
                    node_pointer other = aux[node_rank];
                    if (super_t::operator()(n->value, other->value))
                        std::swap(n, other);

                    if (other->parent)
                        n->children.splice(n->children.end(), other->parent->children, node_list_type::s_iterator_to(*other));
                    else
                        n->children.splice(n->children.end(), roots, node_list_type::s_iterator_to(*other));

                    other->parent = n;

                    aux[node_rank] = NULL;
                    node_rank = n->child_count();
                } while (aux[node_rank] != NULL);
                aux[node_rank] = n;
            }

            if (super_t::operator()(top_element->value, n->value))
                top_element = n;
        }
        while (it != roots.end());
    }


    void finish_erase_or_pop(node_pointer erased_node)
    {
        add_children_to_root(erased_node);

        erased_node->~node();
        allocator_type::deallocate(erased_node, 1);

        size_holder::decrement();
        if (!empty())
            consolidate();
        else
            top_element = NULL;
    }

        type(compare_argument const & arg):
            base_type(arg)
        {}

        type(type const & rhs):
            base_type(rhs), allocator_type(rhs)
        {}


        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
        {}


        type & operator=(type && rhs)
        {
            base_type::operator=(std::move(static_cast<base_type&>(rhs)));
            allocator_type::operator=(std::move(static_cast<allocator_type&>(rhs)));
            return *this;
        }


        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<const allocator_type&>(rhs));
            return *this;
        }

    explicit pairing_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), root(NULL)
    {}

    pairing_heap(pairing_heap const & rhs):
        super_t(rhs), root(NULL)
    {
        if (rhs.empty())
            return;

        clone_tree(rhs);
        size_holder::set_size(rhs.get_size());
    }

    pairing_heap(pairing_heap && rhs):
        super_t(std::move(rhs)), root(rhs.root)
    {
        rhs.root = NULL;
    }

    pairing_heap & operator=(pairing_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        root = rhs.root;
        rhs.root = NULL;
        return *this;
    }

    pairing_heap & operator=(pairing_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        clone_tree(rhs);
        return *this;
    }


    ~pairing_heap(void)
    {
        while (!empty())
            pop();
    }

    bool empty(void) const
    {
        return root == NULL;
    }

    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (root == NULL)
            return 0;
        else
            return detail::count_nodes(root);
    }

    size_type max_size(void) const
    {
        return allocator_type::max_size();
    }

    void clear(void)
    {
        if (empty())
            return;

        root->template clear_subtree<allocator_type>(*this);
        root->~node();
        allocator_type::deallocate(root, 1);
        root = NULL;
        size_holder::set_size(0);
    }

    allocator_type get_allocator(void) const
    {
        return *this;
    }

    void swap(pairing_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(root, rhs.root);
    }

    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(root->value);
    }

    handle_type push(value_type const & v)
    {
        size_holder::increment();

        node_pointer n = allocator_type::allocate(1);

        new(n) node(super_t::make_node(v));

        merge_node(n);
        return handle_type(n);
    }

    template <class... Args>
    handle_type emplace(Args&&... args)
    {
        size_holder::increment();

        node_pointer n = allocator_type::allocate(1);

        new(n) node(super_t::make_node(std::forward<Args>(args)...));

        merge_node(n);
        return handle_type(n);
    }

    void pop(void)
    {
        BOOST_ASSERT(!empty());

        erase(handle_type(root));
    }

    void update (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        update(handle);
    }

    void update (handle_type handle)
    {
        node_pointer n = handle.node_;

        n->unlink();
        if (!n->children.empty())
            n = merge_nodes(n, merge_node_list(n->children));

        if (n != root)
            merge_node(n);
    }

    void increase (handle_type handle, const_reference v)
    {
        update(handle, v);
    }

    void increase (handle_type handle)
    {
        update(handle);
    }

    void decrease (handle_type handle, const_reference v)
    {
        update(handle, v);
    }

    void decrease (handle_type handle)
    {
        update(handle);
    }

    void erase(handle_type handle)
    {
        node_pointer n = handle.node_;
        if (n != root) {
            n->unlink();
            if (!n->children.empty())
                merge_node(merge_node_list(n->children));
        } else {
            if (!n->children.empty())
                root = merge_node_list(n->children);
            else
                root = NULL;
        }

        size_holder::decrement();
        n->~node();
        allocator_type::deallocate(n, 1);
    }

    iterator begin(void) const
    {
        return iterator(root, super_t::value_comp());
    }

    iterator end(void) const
    {
        return iterator();
    }

    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(root, super_t::value_comp());
    }

    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }

    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node * ptr = const_cast<node *>(it.get_node());
        return handle_type(ptr);
    }

    void merge(pairing_heap & rhs)
    {
        if (rhs.empty())
            return;

        merge_node(rhs.root);

        size_holder::add(rhs.get_size());
        rhs.set_size(0);
        rhs.root = NULL;

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }

    void clone_tree(pairing_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(root == NULL);
        if (rhs.empty())
            return;

        root = allocator_type::allocate(1);

        new(root) node(static_cast<node const &>(*rhs.root), static_cast<allocator_type&>(*this));
    }


    void merge_node(node_pointer other)
    {
        BOOST_HEAP_ASSERT(other);
        if (root != NULL)
            root = merge_nodes(root, other);
        else
            root = other;
    }


    node_pointer merge_node_list(node_child_list & children)
    {
        BOOST_HEAP_ASSERT(!children.empty());
        node_pointer merged = merge_first_pair(children);
        if (children.empty())
            return merged;

        node_child_list node_list;
        node_list.push_back(*merged);

        do {
            node_pointer next_merged = merge_first_pair(children);
            node_list.push_back(*next_merged);
        } while (!children.empty());

        return merge_node_list(node_list);
    }


    node_pointer merge_first_pair(node_child_list & children)
    {
        BOOST_HEAP_ASSERT(!children.empty());
        node_pointer first_child = static_cast<node_pointer>(&children.front());
        children.pop_front();
        if (children.empty())
            return first_child;

        node_pointer second_child = static_cast<node_pointer>(&children.front());
        children.pop_front();

        return merge_nodes(first_child, second_child);
    }


    node_pointer merge_nodes(node_pointer node1, node_pointer node2)
    {
        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        node2->unlink();
        node1->children.push_front(*node2);
        return node1;
    }

    parent_holder(void):
        parent_(NULL)
    {}


    void set_parent(node_pointer parent)
    {
        BOOST_HEAP_ASSERT(static_cast<node_pointer>(this) != parent);
        parent_ = parent;
    }


    node_pointer get_parent(void) const
    {
        return parent_;
    }

    void set_parent(node_pointer parent)
    {}


    node_pointer get_parent(void) const
    {
        return NULL;
    }


    skew_heap_node(value_type const & v):
        value(v)
    {
        children.assign(0);
    }

    skew_heap_node(value_type && v):
        value(v)
    {
        children.assign(0);
    }


    template <typename Alloc>
    skew_heap_node (skew_heap_node const & rhs, Alloc & allocator, skew_heap_node * parent):
        value(rhs.value)
    {
        super_t::set_parent(parent);
        node_cloner<skew_heap_node, skew_heap_node, Alloc> cloner(allocator);
        clone_child(0, rhs, cloner);
        clone_child(1, rhs, cloner);
    }


    template <typename Cloner>
    void clone_child(int index, skew_heap_node const & rhs, Cloner & cloner)
    {
        if (rhs.children[index])
            children[index] = cloner(*rhs.children[index], this);
        else
            children[index] = NULL;
    }


    template <typename Alloc>
    void clear_subtree(Alloc & alloc)
    {
        node_disposer<skew_heap_node, skew_heap_node, Alloc> disposer(alloc);
        dispose_child(children[0], disposer);
        dispose_child(children[1], disposer);
    }


    template <typename Disposer>
    void dispose_child(skew_heap_node * node, Disposer & disposer)
    {
        if (node)
            disposer(node);
    }


    std::size_t count_children(void) const
    {
        size_t ret = 1;
        if (children[0])
            ret += children[0]->count_children();
        if (children[1])
            ret += children[1]->count_children();

        return ret;
    }


    template <typename HeapBase>
    bool is_heap(typename HeapBase::value_compare const & cmp) const
    {
        for (const_child_iterator it = children.begin(); it != children.end(); ++it) {
            const skew_heap_node * child = *it;

            if (child == NULL)
                continue;

            if (store_parent_pointer)
                BOOST_HEAP_ASSERT(child->get_parent() == this);

            if (cmp(HeapBase::get_value(value), HeapBase::get_value(child->value)) ||
                !child->is_heap<HeapBase>(cmp))
                return false;
        }
        return true;
    }

        type(compare_argument const & arg):
            base_type(arg)
        {}

        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
        {}


        type(type const & rhs):
            base_type(rhs),
            allocator_type(rhs)
        {}


        type & operator=(type && rhs)
        {
            base_type::operator=(std::move(static_cast<base_type&>(rhs)));
            allocator_type::operator=(std::move(static_cast<allocator_type&>(rhs)));
            return *this;
        }


        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }

    explicit skew_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), root(NULL)
    {}

    skew_heap(skew_heap const & rhs):
        super_t(rhs), root(0)
    {
        if (rhs.empty())
            return;

        clone_tree(rhs);
        size_holder::set_size(rhs.get_size());
    }

    skew_heap & operator=(skew_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        clone_tree(rhs);
        return *this;
    }

    skew_heap(skew_heap && rhs):
        super_t(std::move(rhs)), root(rhs.root)
    {
        rhs.root = NULL;
    }

    skew_heap & operator=(skew_heap && rhs)
    {
        super_t::operator=(std::move(rhs));
        root = rhs.root;
        rhs.root = NULL;
        return *this;
    }


    ~skew_heap(void)
    {
        clear();
    }

        static handle_type push(skew_heap * self, const_reference v)
        {
            return handle_type(self->push_internal(v));
        }

        template <class... Args>
        static handle_type emplace(skew_heap * self, Args&&... args)
        {
            return handle_type(self->emplace_internal(std::forward<Args>(args)...));
        }


    node_pointer push_internal(const_reference v)
    {
        size_holder::increment();

        node_pointer n = super_t::allocate(1);
        new(n) node(super_t::make_node(v));

        merge_node(n);
        return n;
    }

    template <class... Args>
    node_pointer emplace_internal(Args&&... args)
    {
        size_holder::increment();

        node_pointer n = super_t::allocate(1);
        new(n) node(super_t::make_node(std::forward<Args>(args)...));

        merge_node(n);
        return n;
    }


    void unlink_node(node_pointer node)
    {
        node_pointer parent = node->get_parent();
        node_pointer merged_children = merge_children(node);

        if (parent) {
            if (node == parent->children[0])
                parent->children[0] = merged_children;
            else
                parent->children[1] = merged_children;
        }
        else
            root = merged_children;
    }


    void clone_tree(skew_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(root == NULL);
        if (rhs.empty())
            return;

        root = allocator_type::allocate(1);

        new(root) node(*rhs.root, static_cast<allocator_type&>(*this), NULL);
    }


    void merge_node(node_pointer other)
    {
        BOOST_HEAP_ASSERT(other);
        if (root != NULL)
            root = merge_nodes(root, other, NULL);
        else
            root = other;
    }


    node_pointer merge_nodes(node_pointer node1, node_pointer node2, node_pointer new_parent)
    {
        if (node1 == NULL) {
            if (node2)
                node2->set_parent(new_parent);
            return node2;
        }
        if (node2 == NULL) {
            node1->set_parent(new_parent);
            return node1;
        }

        node_pointer merged = merge_nodes_recursive(node1, node2, new_parent);
        return merged;
    }


    node_pointer merge_children(node_pointer node)
    {
        node_pointer parent = node->get_parent();
        node_pointer merged_children = merge_nodes(node->children[0], node->children[1], parent);

        return merged_children;
    }


    node_pointer merge_nodes_recursive(node_pointer node1, node_pointer node2, node_pointer new_parent)
    {
        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        node * parent = node1;
        node * child = node2;

        if (parent->children[1]) {
            node * merged = merge_nodes(parent->children[1], child, parent);
            parent->children[1] = merged;
            merged->set_parent(parent);
        } else {
            parent->children[1] = child;
            child->set_parent(parent);
        }


        std::swap(parent->children[0], parent->children[1]);
        parent->set_parent(new_parent);
        return parent;
    }


    void sanity_check(void)
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        if (root)
            BOOST_HEAP_ASSERT( root->template is_heap<super_t>(super_t::value_comp()) );

        if (constant_time_size) {
            size_type stored_size = size_holder::get_size();

            size_type counted_size;
            if (root == NULL)
                counted_size = 0;
            else
                counted_size = root->count_children();

            BOOST_HEAP_ASSERT(counted_size == stored_size);
        }
#endif
    }

    explicit priority_queue(value_compare const & cmp = value_compare()):
        super_t(cmp)
    {}

    priority_queue (priority_queue const & rhs):
        super_t(rhs), q_(rhs.q_)
    {}

    priority_queue(priority_queue && rhs):
        super_t(std::move(rhs)), q_(std::move(rhs.q_))
    {}

    priority_queue & operator=(priority_queue && rhs)
    {
        super_t::operator=(std::move(rhs));
        q_ = std::move(rhs.q_);
        return *this;
    }

    priority_queue & operator=(priority_queue const & rhs)
    {
        static_cast<super_t&>(*this) = static_cast<super_t const &>(rhs);
        q_ = rhs.q_;
        return *this;
    }

    bool empty(void) const
    {
        return q_.empty();
    }

    size_type size(void) const
    {
        return q_.size();
    }

    size_type max_size(void) const
    {
        return q_.max_size();
    }

    void clear(void)
    {
        q_.clear();
    }

    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }

    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());
        return super_t::get_value(q_.front());
    }

    void push(value_type const & v)
    {
        q_.push_back(super_t::make_node(v));
        std::push_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
    }

    template <class... Args>
    void emplace(Args&&... args)
    {
        q_.emplace_back(super_t::make_node(std::forward<Args>(args)...));
        std::push_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
    }

    void pop(void)
    {
        BOOST_ASSERT(!empty());
        std::pop_heap(q_.begin(), q_.end(), static_cast<super_t const &>(*this));
        q_.pop_back();
    }

    void swap(priority_queue & rhs)
    {
        super_t::swap(rhs);
        q_.swap(rhs.q_);
    }

    iterator begin(void) const
    {
        return iterator(q_.begin());
    }

    iterator end(void) const
    {
        return iterator(q_.end());
    }

    void reserve(size_type element_count)
    {
        q_.reserve(element_count);
    }

    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }

        type(compare_argument const & arg):
            base_type(arg)
        {}

        type(type const & rhs):
            base_type(rhs), allocator_type(rhs)
        {}


        type(type && rhs):
            base_type(std::move(static_cast<base_type&>(rhs))),
            allocator_type(std::move(static_cast<allocator_type&>(rhs)))
        {}


        type & operator=(type && rhs)
        {
            base_type::operator=(std::move(static_cast<base_type&>(rhs)));
            allocator_type::operator=(std::move(static_cast<allocator_type&>(rhs)));
            return *this;
        }


        type & operator=(type const & rhs)
        {
            base_type::operator=(static_cast<base_type const &>(rhs));
            allocator_type::operator=(static_cast<allocator_type const &>(rhs));
            return *this;
        }

    explicit binomial_heap(value_compare const & cmp = value_compare()):
        super_t(cmp), top_element(0)
    {}

    binomial_heap(binomial_heap const & rhs):
        super_t(rhs), top_element(0)
    {
        if (rhs.empty())
            return;

        clone_forest(rhs);
        size_holder::set_size(rhs.get_size());
    }

    binomial_heap & operator=(binomial_heap const & rhs)
    {
        clear();
        size_holder::set_size(rhs.get_size());
        static_cast<super_t&>(*this) = rhs;

        if (rhs.empty())
            top_element = NULL;
        else
            clone_forest(rhs);
        return *this;
    }

    binomial_heap(binomial_heap && rhs):
        super_t(std::move(rhs)), top_element(rhs.top_element)
    {
        trees.splice(trees.begin(), rhs.trees);
        rhs.top_element = NULL;
    }

    binomial_heap & operator=(binomial_heap && rhs)
    {
        clear();
        super_t::operator=(std::move(rhs));
        trees.splice(trees.begin(), rhs.trees);
        top_element = rhs.top_element;
        rhs.top_element = NULL;
        return *this;
    }


    ~binomial_heap(void)
    {
        clear();
    }

    bool empty(void) const
    {
        return top_element == NULL;
    }

    size_type size(void) const
    {
        if (constant_time_size)
            return size_holder::get_size();

        if (empty())
            return 0;
        else
            return detail::count_list_nodes<node_type, node_list_type>(trees);
    }

    size_type max_size(void) const
    {
        return allocator_type::max_size();
    }

    void clear(void)
    {
        typedef detail::node_disposer<node_type, typename node_list_type::value_type, allocator_type> disposer;
        trees.clear_and_dispose(disposer(*this));

        size_holder::set_size(0);
        top_element = NULL;
    }

    allocator_type get_allocator(void) const
    {
        return *this;
    }

    void swap(binomial_heap & rhs)
    {
        super_t::swap(rhs);
        std::swap(top_element, rhs.top_element);
        trees.swap(rhs.trees);
    }

    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());

        return super_t::get_value(top_element->value);
    }

    handle_type push(value_type const & v)
    {
        node_pointer n = allocator_type::allocate(1);
        new(n) node_type(super_t::make_node(v));

        insert_node(trees.begin(), n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;

        size_holder::increment();
        sanity_check();
        return handle_type(n);
    }

    template <class... Args>
    handle_type emplace(Args&&... args)
    {
        node_pointer n = allocator_type::allocate(1);
        new(n) node_type(super_t::make_node(std::forward<Args>(args)...));

        insert_node(trees.begin(), n);

        if (!top_element || super_t::operator()(top_element->value, n->value))
            top_element = n;

        size_holder::increment();
        sanity_check();
        return handle_type(n);
    }

    void pop(void)
    {
        BOOST_ASSERT(!empty());

        node_pointer element = top_element;

        trees.erase(node_list_type::s_iterator_to(*element));
        size_holder::decrement();

        if (element->child_count()) {
            size_type sz = (1 << element->child_count()) - 1;
            binomial_heap children(value_comp(), element->children, sz);
            if (trees.empty())
                swap(children);
            else
                merge_and_clear_nodes(children);
        }

        if (trees.empty())
            top_element = NULL;
        else
            update_top_element();

        element->~node_type();
        allocator_type::deallocate(element, 1);
        sanity_check();
    }

    void update (handle_type handle, const_reference v)
    {
        if (super_t::operator()(super_t::get_value(handle.node_->value), v))
            increase(handle, v);
        else
            decrease(handle, v);
    }

    void update (handle_type handle)
    {
        node_pointer this_node = handle.node_;

        if (this_node->parent) {
            if (super_t::operator()(super_t::get_value(this_node->parent->value), super_t::get_value(this_node->value)))
                increase(handle);
            else
                decrease(handle);
        }
        else
            decrease(handle);
    }

    void increase (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        increase(handle);
    }

    void increase (handle_type handle)
    {
        node_pointer n = handle.node_;
        siftup(n, *this);

        update_top_element();
        sanity_check();
    }

    void decrease (handle_type handle, const_reference v)
    {
        handle.node_->value = super_t::make_node(v);
        decrease(handle);
    }

    void decrease (handle_type handle)
    {
        node_pointer n = handle.node_;

        siftdown(n);

        if (n == top_element)
            update_top_element();
    }

    void merge(binomial_heap & rhs)
    {
        if (rhs.empty())
            return;

        if (empty()) {
            swap(rhs);
            return;
        }

        size_type new_size = size_holder::get_size() + rhs.get_size();
        merge_and_clear_nodes(rhs);

        size_holder::set_size(new_size);
        rhs.set_size(0);
        rhs.top_element = NULL;

        super_t::set_stability_count((std::max)(super_t::get_stability_count(),
                                     rhs.get_stability_count()));
        rhs.set_stability_count(0);
    }

    iterator begin(void) const
    {
        return iterator(trees.begin());
    }

    iterator end(void) const
    {
        return iterator(trees.end());
    }

    ordered_iterator ordered_begin(void) const
    {
        return ordered_iterator(trees.begin(), trees.end(), top_element, super_t::value_comp());
    }

    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(NULL, super_t::value_comp());
    }

    void erase(handle_type handle)
    {
        node_pointer n = handle.node_;
        siftup(n, force_inf());
        top_element = n;
        pop();
    }

    static handle_type s_handle_from_iterator(iterator const & it)
    {
        node_type * ptr = const_cast<node_type *>(it.get_node());
        return handle_type(ptr);
    }

    value_compare const & value_comp(void) const
    {
        return super_t::value_comp();
    }

    template <typename HeapType>
    bool operator<(HeapType const & rhs) const
    {
        return detail::heap_compare(*this, rhs);
    }

    template <typename HeapType>
    bool operator>(HeapType const & rhs) const
    {
        return detail::heap_compare(rhs, *this);
    }

    template <typename HeapType>
    bool operator>=(HeapType const & rhs) const
    {
        return !operator<(rhs);
    }

    template <typename HeapType>
    bool operator<=(HeapType const & rhs) const
    {
        return !operator>(rhs);
    }

    template <typename HeapType>
    bool operator==(HeapType const & rhs) const
    {
        return detail::heap_equality(*this, rhs);
    }

    template <typename HeapType>
    bool operator!=(HeapType const & rhs) const
    {
        return !(*this == rhs);
    }

    void merge_and_clear_nodes(binomial_heap & rhs)
    {
        BOOST_HEAP_ASSERT (!empty());
        BOOST_HEAP_ASSERT (!rhs.empty());

        node_list_iterator this_iterator = trees.begin();
        node_pointer carry_node = NULL;

        while (!rhs.trees.empty()) {
            node_pointer rhs_node = static_cast<node_pointer>(&rhs.trees.front());
            size_type rhs_degree = rhs_node->child_count();

            if (super_t::operator()(top_element->value, rhs_node->value))
                top_element = rhs_node;

        try_again:
            node_pointer this_node = static_cast<node_pointer>(&*this_iterator);
            size_type this_degree = this_node->child_count();
            sorted_by_degree();
            rhs.sorted_by_degree();

            if (this_degree == rhs_degree) {
                if (carry_node) {
                    if (carry_node->child_count() < this_degree) {
                        trees.insert(this_iterator, *carry_node);
                        carry_node = NULL;
                    } else {
                        rhs.trees.pop_front();
                        carry_node = merge_trees(carry_node, rhs_node);
                    }
                    ++this_iterator;
                } else {
                    this_iterator = trees.erase(this_iterator);
                    rhs.trees.pop_front();
                    carry_node = merge_trees(this_node, rhs_node);
                }

                if (this_iterator == trees.end())
                    break;
                else
                    continue;
            }

            if (this_degree < rhs_degree) {
                if (carry_node) {
                    if (carry_node->child_count() < this_degree) {
                        trees.insert(this_iterator, *carry_node);
                        carry_node = NULL;
                        ++this_iterator;
                    } else if (carry_node->child_count() == rhs_degree) {
                        rhs.trees.pop_front();
                        carry_node = merge_trees(carry_node, rhs_node);
                        continue;
                    } else {
                        this_iterator = trees.erase(this_iterator);
                        carry_node = merge_trees(this_node, carry_node);
                    }
                    goto try_again;
                } else {
                    ++this_iterator;
                    if (this_iterator == trees.end())
                        break;
                    goto try_again;
                }

                if (this_iterator == trees.end())
                    break;
                else
                    continue;
            }

            if (this_degree > rhs_degree) {
                rhs.trees.pop_front();
                if (carry_node) {
                    if (carry_node->child_count() < rhs_degree) {
                        trees.insert(this_iterator, *carry_node);
                        trees.insert(this_iterator, *rhs_node);
                        carry_node = NULL;
                    } else
                        carry_node = merge_trees(rhs_node, carry_node);
                } else
                    trees.insert(this_iterator, *rhs_node);
            }
        }

        if (!rhs.trees.empty()) {
            if (carry_node) {
                node_list_iterator rhs_it = rhs.trees.begin();
                while (static_cast<node_pointer>(&*rhs_it)->child_count() < carry_node->child_count())
                    ++rhs_it;
                rhs.insert_node(rhs_it, carry_node);
                rhs.increment();
                sorted_by_degree();
                rhs.sorted_by_degree();
                if (trees.empty()) {
                    trees.splice(trees.end(), rhs.trees, rhs.trees.begin(), rhs.trees.end());
                    update_top_element();
                } else
                    merge_and_clear_nodes(rhs);
            } else
                trees.splice(trees.end(), rhs.trees, rhs.trees.begin(), rhs.trees.end());
            return;
        }

        if (carry_node)
            insert_node(this_iterator, carry_node);
    }


    void clone_forest(binomial_heap const & rhs)
    {
        BOOST_HEAP_ASSERT(trees.empty());
        typedef typename node_type::template node_cloner<allocator_type> node_cloner;
        trees.clone_from(rhs.trees, node_cloner(*this, NULL), detail::nop_disposer());

        update_top_element();
    }

        template <typename X>
        bool operator()(X const &, X const &) const
        {
            return false;
        }


    template <typename Compare>
    void siftup(node_pointer n, Compare const & cmp)
    {
        while (n->parent) {
            node_pointer parent = n->parent;
            node_pointer grand_parent = parent->parent;
            if (cmp(n->value, parent->value))
                return;

            n->remove_from_parent();

            n->swap_children(parent);
            n->update_children();
            parent->update_children();

            if (grand_parent) {
                parent->remove_from_parent();
                grand_parent->add_child(n);
            } else {
                node_list_iterator it = trees.erase(node_list_type::s_iterator_to(*parent));
                trees.insert(it, *n);
            }
            n->add_child(parent);
            BOOST_HEAP_ASSERT(parent->child_count() == n->child_count());
        }
    }


    void siftdown(node_pointer n)
    {
        while (n->child_count()) {
            node_pointer max_child = detail::find_max_child<node_list_type, node_type, internal_compare>(n->children, super_t::get_internal_cmp());

            if (super_t::operator()(max_child->value, n->value))
                return;

            max_child->remove_from_parent();

            n->swap_children(max_child);
            n->update_children();
            max_child->update_children();

            node_pointer parent = n->parent;
            if (parent) {
                n->remove_from_parent();
                max_child->add_child(n);
                parent->add_child(max_child);
            } else {
                node_list_iterator position = trees.erase(node_list_type::s_iterator_to(*n));
                max_child->add_child(n);
                trees.insert(position, *max_child);
            }
        }
    }


    void insert_node(node_list_iterator it, node_pointer n)
    {
        if (it != trees.end())
            BOOST_HEAP_ASSERT(static_cast<node_pointer>(&*it)->child_count() >= n->child_count());

        while(true) {
            BOOST_HEAP_ASSERT(!n->is_linked());
            if (it == trees.end())
                break;

            node_pointer this_node = static_cast<node_pointer>(&*it);
            size_type this_degree = this_node->child_count();
            size_type n_degree = n->child_count();
            if (this_degree == n_degree) {
                BOOST_HEAP_ASSERT(it->is_linked());
                it = trees.erase(it);

                n = merge_trees(n, this_node);
            } else
                break;
        }
        trees.insert(it, *n);
    }

    explicit binomial_heap(value_compare const & cmp, node_list_type & child_list, size_type size):
        super_t(cmp)
    {
        size_holder::set_size(size);
        if (size)
            top_element = static_cast<node_pointer>(&*child_list.begin()); // not correct, but we will reset it later
        else
            top_element = NULL;

        for (node_list_iterator it = child_list.begin(); it != child_list.end(); ++it) {
            node_pointer n = static_cast<node_pointer>(&*it);
            n->parent = NULL;
        }

        trees.splice(trees.end(), child_list, child_list.begin(), child_list.end());

        trees.sort(detail::cmp_by_degree<node_type>());
    }


    node_pointer merge_trees (node_pointer node1, node_pointer node2)
    {
        BOOST_HEAP_ASSERT(node1->child_count() == node2->child_count());

        if (super_t::operator()(node1->value, node2->value))
            std::swap(node1, node2);

        if (node2->parent)
            node2->remove_from_parent();

        node1->add_child(node2);
        return node1;
    }


    void update_top_element(void)
    {
        top_element = detail::find_max_child<node_list_type, node_type, internal_compare>(trees, super_t::get_internal_cmp());
    }


    void sorted_by_degree(void) const
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        int degree = -1;

        for (node_list_const_iterator it = trees.begin(); it != trees.end(); ++it) {
            const_node_pointer n = static_cast<const_node_pointer>(&*it);
            BOOST_HEAP_ASSERT(int(n->child_count()) > degree);
            degree = n->child_count();

            BOOST_HEAP_ASSERT((detail::is_heap<node_type, super_t>(n, *this)));

            size_type child_nodes = detail::count_nodes<node_type>(n);
            BOOST_HEAP_ASSERT(child_nodes == size_type(1 << static_cast<const_node_pointer>(&*it)->child_count()));
        }
#endif
    }


    void sanity_check(void)
    {
#ifdef BOOST_HEAP_SANITYCHECKS
        sorted_by_degree();

        if (!empty()) {
            node_pointer found_top = detail::find_max_child<node_list_type, node_type, internal_compare>(trees, super_t::get_internal_cmp());
            BOOST_HEAP_ASSERT(top_element == found_top);
        }

        if (constant_time_size) {
            size_t counted = detail::count_list_nodes<node_type, node_list_type>(trees);
            size_t stored = size_holder::get_size();
            BOOST_HEAP_ASSERT(counted == stored);
        }
#endif
    }


    size_holder(void):
        size_(0)
    {}

    size_holder(size_holder && rhs):
        size_(rhs.size_)
    {
        rhs.size_ = 0;
    }


    size_holder(size_holder const & rhs):
        size_(rhs.size_)
    {}


    size_holder & operator=(size_holder && rhs)
    {
        size_ = rhs.size_;
        rhs.size_ = 0;
        return *this;
    }


    size_holder & operator=(size_holder const & rhs)
    {
        size_ = rhs.size_;
        return *this;
    }


    SizeType get_size() const
    {  return size_;  }


    void set_size(SizeType size)
    {  size_ = size; }


    void decrement()
    {  --size_; }


    void increment()
    {  ++size_; }


    void add(SizeType value)
    {  size_ += value; }


    void sub(SizeType value)
    {  size_ -= value; }


    void swap(size_holder & rhs)
    {  std::swap(size_, rhs.size_); }


    size_holder(void)
    {}

    size_holder(size_holder && rhs)
    {}


    size_holder(size_holder const & rhs)
    {}


    size_holder & operator=(size_holder && rhs)
    {
        return *this;
    }


    size_holder & operator=(size_holder const & rhs)
    {
        return *this;
    }


    size_type get_size() const
    {  return 0;  }


    void set_size(size_type)
    {}


    void decrement()
    {}


    void increment()
    {}


    void add(SizeType value)
    {}


    void sub(SizeType value)
    {}


    void swap(size_holder & rhs)
    {}


    heap_base (Cmp const & cmp = Cmp()):
#ifndef BOOST_MSVC
        Cmp(cmp)
#else
        cmp_(cmp)
#endif
    {}

    heap_base(heap_base && rhs):
#ifndef BOOST_MSVC
        Cmp(std::move(static_cast<Cmp&>(rhs))),
#else
        cmp_(std::move(rhs.cmp_)),
#endif
        size_holder_type(std::move(static_cast<size_holder_type&>(rhs)))
    {}


    heap_base(heap_base const & rhs):
#ifndef BOOST_MSVC
        Cmp(static_cast<Cmp const &>(rhs)),
#else
        cmp_(rhs.value_comp()),
#endif
        size_holder_type(static_cast<size_holder_type const &>(rhs))
    {}


    heap_base & operator=(heap_base && rhs)
    {
        value_comp_ref().operator=(std::move(rhs.value_comp_ref()));
        size_holder_type::operator=(std::move(static_cast<size_holder_type&>(rhs)));
        return *this;
    }


    heap_base & operator=(heap_base const & rhs)
    {
        value_comp_ref().operator=(rhs.value_comp());
        size_holder_type::operator=(static_cast<size_holder_type const &>(rhs));
        return *this;
    }


    bool operator()(internal_type const & lhs, internal_type const & rhs) const
    {
        return value_comp().operator()(lhs, rhs);
    }


    internal_type make_node(T const & val)
    {
        return val;
    }

    T && make_node(T && val)
    {
        return std::forward<T>(val);
    }

    template <class... Args>
    internal_type make_node(Args && ... val)
    {
        return internal_type(std::forward<Args>(val)...);
    }


    static T & get_value(internal_type & val)
    {
        return val;
    }


    static T const & get_value(internal_type const & val)
    {
        return val;
    }


    Cmp const & value_comp(void) const
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }


    Cmp const & get_internal_cmp(void) const
    {
        return value_comp();
    }


    void swap(heap_base & rhs)
    {
        std::swap(value_comp_ref(), rhs.value_comp_ref());
        size_holder<constant_time_size, size_t>::swap(rhs);
    }


    stability_counter_type get_stability_count(void) const
    {
        return 0;
    }


    void set_stability_count(stability_counter_type)
    {}

    Cmp & value_comp_ref(void)
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

        template <class ...Args>
        internal_type(stability_counter_type cnt, Args && ... args):
            first(std::forward<Args>(args)...), second(cnt)
        {}


        internal_type(stability_counter_type const & cnt, T const & value):
            first(value), second(cnt)
        {}


    heap_base (Cmp const & cmp = Cmp()):
#ifndef BOOST_MSVC
        Cmp(cmp),
#else
        cmp_(cmp),
#endif
        counter_(0)
    {}

    heap_base(heap_base && rhs):
#ifndef BOOST_MSVC
        Cmp(std::move(static_cast<Cmp&>(rhs))),
#else
        cmp_(std::move(rhs.cmp_)),
#endif
        size_holder_type(std::move(static_cast<size_holder_type&>(rhs))), counter_(rhs.counter_)
    {
        rhs.counter_ = 0;
    }


    heap_base(heap_base const & rhs):
#ifndef BOOST_MSVC
        Cmp(static_cast<Cmp const&>(rhs)),
#else
        cmp_(rhs.value_comp()),
#endif
        size_holder_type(static_cast<size_holder_type const &>(rhs)), counter_(rhs.counter_)
    {}


    heap_base & operator=(heap_base && rhs)
    {
        value_comp_ref().operator=(std::move(rhs.value_comp_ref()));
        size_holder_type::operator=(std::move(static_cast<size_holder_type&>(rhs)));

        counter_ = rhs.counter_;
        rhs.counter_ = 0;
        return *this;
    }


    heap_base & operator=(heap_base const & rhs)
    {
        value_comp_ref().operator=(rhs.value_comp());
        size_holder_type::operator=(static_cast<size_holder_type const &>(rhs));

        counter_ = rhs.counter_;
        return *this;
    }


    bool operator()(internal_type const & lhs, internal_type const & rhs) const
    {
        return get_internal_cmp()(lhs, rhs);
    }


    bool operator()(T const & lhs, T const & rhs) const
    {
        return value_comp()(lhs, rhs);
    }


    internal_type make_node(T const & val)
    {
        stability_counter_type count = ++counter_;
        if (counter_ == (std::numeric_limits<stability_counter_type>::max)())
            BOOST_THROW_EXCEPTION(std::runtime_error("boost::heap counter overflow"));
        return internal_type(count, val);
    }

    template <class... Args>
    internal_type make_node(Args&&... args)
    {
        stability_counter_type count = ++counter_;
        if (counter_ == (std::numeric_limits<stability_counter_type>::max)())
            BOOST_THROW_EXCEPTION(std::runtime_error("boost::heap counter overflow"));
        return internal_type (count, std::forward<Args>(args)...);
    }


    static T & get_value(internal_type & val)
    {
        return val.first;
    }


    static T const & get_value(internal_type const & val)
    {
        return val.first;
    }


    Cmp const & value_comp(void) const
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

        internal_compare(Cmp const & cmp = Cmp()):
            Cmp(cmp)
        {}


        bool operator()(internal_type const & lhs, internal_type const & rhs) const
        {
            if (Cmp::operator()(lhs.first, rhs.first))
                return true;

            if (Cmp::operator()(rhs.first, lhs.first))
                return false;

            return lhs.second > rhs.second;
        }


    internal_compare get_internal_cmp(void) const
    {
        return internal_compare(value_comp());
    }


    void swap(heap_base & rhs)
    {
#ifndef BOOST_MSVC
        std::swap(static_cast<Cmp&>(*this), static_cast<Cmp&>(rhs));
#else
        std::swap(cmp_, rhs.cmp_);
#endif
        std::swap(counter_, rhs.counter_);
        size_holder<constant_time_size, size_t>::swap(rhs);
    }


    stability_counter_type get_stability_count(void) const
    {
        return counter_;
    }


    void set_stability_count(stability_counter_type new_count)
    {
        counter_ = new_count;
    }

    Cmp & value_comp_ref(void)
    {
#ifndef BOOST_MSVC
        return *this;
#else
        return cmp_;
#endif
    }

    explicit node_handle(node_pointer n = 0):
        node_(n)
    {}


    reference operator*() const
    {
        return extractor::get_value(node_->value);
    }


    bool operator==(node_handle const & rhs) const
    {
        return node_ == rhs.node_;
    }


    bool operator!=(node_handle const & rhs) const
    {
        return node_ != rhs.node_;
    }

    value_type const & operator()(internal_type const & data) const
    {
        return extractor::get_value(data);
    }

    stable_heap_iterator(void):
        super_t(0)
    {}


    explicit stable_heap_iterator(ContainerIterator const & it):
        super_t(it)
    {}


    T const & dereference() const
    {
        return Extractor::get_value(*super_t::base());
    }


        compare_by_heap_value (const ContainerType * container, ValueCompare const & cmp):
            ValueCompare(cmp), container(container)
        {}


        bool operator()(size_t lhs, size_t rhs)
        {
            BOOST_ASSERT(lhs <= Dispatcher::max_index(container));
            BOOST_ASSERT(rhs <= Dispatcher::max_index(container));
            return ValueCompare::operator()(Dispatcher::get_internal_value(container, lhs),
                                            Dispatcher::get_internal_value(container, rhs));
        }

    ordered_adaptor_iterator(void):
        container(NULL), current_index((std::numeric_limits<size_t>::max)()),
        unvisited_nodes(compare_by_heap_value(NULL, ValueCompare()))
    {}


    ordered_adaptor_iterator(const ContainerType * container, ValueCompare const & cmp):
        container(container), current_index(container->size()),
        unvisited_nodes(compare_by_heap_value(container, ValueCompare()))
    {}

    bool equal (ordered_adaptor_iterator const & rhs) const
    {
        if (current_index != rhs.current_index)
            return false;

        if (container != rhs.container) // less likely than first check
            return false;

        return true;
    }


    void increment(void)
    {
        if (unvisited_nodes.empty())
            current_index = Dispatcher::max_index(container) + 1;
        else {
            current_index = unvisited_nodes.top();
            unvisited_nodes.pop();
            discover_nodes(current_index);
        }
    }


    ValueType const & dereference() const
    {
        BOOST_ASSERT(current_index <= Dispatcher::max_index(container));
        return Dispatcher::get_value(Dispatcher::get_internal_value(container, current_index));
    }


    void discover_nodes(size_t index)
    {
        if (Dispatcher::is_leaf(container, index))
            return;

        std::pair<size_t, size_t> child_range = Dispatcher::get_child_nodes(container, index);

        for (size_t i = child_range.first; i <= child_range.second; ++i)
            unvisited_nodes.push(i);
    }


    stability_counter_type get_stability_count(void) const
    {
        return q_.get_stability_count();
    }


    void set_stability_count(stability_counter_type new_count)
    {
        q_.set_stability_count(new_count);
    }

        template <typename It>
        static void run(It & it, size_type new_index)
        {
            q_type::get_value(it)->second = new_index;
        }

        value_type & operator*() const
        {
            return iterator->first;
        }


        handle_type (void)
        {}


        handle_type(handle_type const & rhs):
            iterator(rhs.iterator)
        {}


        bool operator==(handle_type const & rhs) const
        {
            return iterator == rhs.iterator;
        }


        bool operator!=(handle_type const & rhs) const
        {
            return iterator != rhs.iterator;
        }

        indirect_cmp(value_compare const & cmp = value_compare()):
            value_compare(cmp)
        {}


        bool operator()(const_list_iterator const & lhs, const_list_iterator const & rhs) const
        {
            return value_compare::operator()(lhs->first, rhs->first);
        }

    priority_queue_mutable_wrapper(value_compare const & cmp = value_compare()):
        q_(cmp)
    {}


    priority_queue_mutable_wrapper(priority_queue_mutable_wrapper const & rhs):
        q_(rhs.q_), objects(rhs.objects)
    {
        for (typename object_list::iterator it = objects.begin(); it != objects.end(); ++it)
            q_.push(it);
    }


    priority_queue_mutable_wrapper & operator=(priority_queue_mutable_wrapper const & rhs)
    {
        q_ = rhs.q_;
        objects = rhs.objects;
        q_.clear();
        for (typename object_list::iterator it = objects.begin(); it != objects.end(); ++it)
            q_.push(it);
        return *this;
    }

    priority_queue_mutable_wrapper (priority_queue_mutable_wrapper && rhs):
        q_(std::move(rhs.q_))
    {
        /// FIXME: msvc seems to invalidate iterators when moving std::list
        std::swap(objects, rhs.objects);
    }


    priority_queue_mutable_wrapper & operator=(priority_queue_mutable_wrapper && rhs)
    {
        q_ = std::move(rhs.q_);
        objects.clear();
        std::swap(objects, rhs.objects);
        return *this;
    }


        iterator_base(void):
            super_t(0)
        {}


        template <typename T>
        explicit iterator_base(T const & it):
            super_t(it)
        {}


        value_type const & dereference() const
        {
            return super_t::base()->first;
        }


        iterator_type get_list_iterator() const
        {
            return super_t::base_reference();
        }

        ordered_iterator(void):
            adaptor_type(0), unvisited_nodes(indirect_cmp()), q_(NULL)
        {}


        ordered_iterator(const priority_queue_mutable_wrapper * q, indirect_cmp const & cmp):
            adaptor_type(0), unvisited_nodes(cmp), q_(q)
        {}


        bool operator!=(ordered_iterator const & rhs) const
        {
            return adaptor_type::base() != rhs.base();
        }


        bool operator==(ordered_iterator const & rhs) const
        {
            return !operator!=(rhs);
        }

        void increment(void)
        {
            if (unvisited_nodes.empty())
                adaptor_type::base_reference() = q_->objects.end();
            else {
                iterator next = unvisited_nodes.top();
                unvisited_nodes.pop();
                discover_nodes(next);
                adaptor_type::base_reference() = next;
            }
        }


        value_type const & dereference() const
        {
            return adaptor_type::base()->first;
        }


        void discover_nodes(iterator current)
        {
            size_type current_index = current->second;
            const q_type * q = &(q_->q_);

            if (ordered_iterator_dispatcher::is_leaf(q, current_index))
                return;

            std::pair<size_type, size_type> child_range = ordered_iterator_dispatcher::get_child_nodes(q, current_index);

            for (size_type i = child_range.first; i <= child_range.second; ++i) {
                typename q_type::internal_type const & internal_value_at_index = ordered_iterator_dispatcher::get_internal_value(q, i);
                typename q_type::value_type const & value_at_index = q_->q_.get_value(internal_value_at_index);

                unvisited_nodes.push(value_at_index);
            }
        }


    bool empty(void) const
    {
        return q_.empty();
    }


    size_type size(void) const
    {
        return q_.size();
    }


    size_type max_size(void) const
    {
        return objects.max_size();
    }


    void clear(void)
    {
        q_.clear();
        objects.clear();
    }


    allocator_type get_allocator(void) const
    {
        return q_.get_allocator();
    }


    void swap(priority_queue_mutable_wrapper & rhs)
    {
        objects.swap(rhs.objects);
        q_.swap(rhs.q_);
    }


    const_reference top(void) const
    {
        BOOST_ASSERT(!empty());
        return q_.top()->first;
    }


    handle_type push(value_type const & v)
    {
        objects.push_front(std::make_pair(v, 0));
        list_iterator ret = objects.begin();
        q_.push(ret);
        return handle_type(ret);
    }

    template <class... Args>
    handle_type emplace(Args&&... args)
    {
        objects.push_front(std::make_pair(std::forward<Args>(args)..., 0));
        list_iterator ret = objects.begin();
        q_.push(ret);
        return handle_type(ret);
    }


    void pop(void)
    {
        BOOST_ASSERT(!empty());
        list_iterator q_top = q_.top();
        q_.pop();
        objects.erase(q_top);
    }

    void merge(priority_queue_mutable_wrapper const & rhs)
    {
        q_.reserve(q_.size() + rhs.q_.size());

        for (typename object_list::const_iterator it = rhs.objects.begin(); it != rhs.objects.end(); ++it)
            push(it->first);
    }

    void update(handle_type handle, const_reference v)
    {
        list_iterator it = handle.iterator;
        value_type const & current_value = it->first;
        value_compare const & cmp = q_.value_comp();
        if (cmp(v, current_value))
            decrease(handle, v);
        else
            increase(handle, v);
    }

    void update(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.update(index);
    }

    void increase(handle_type handle, const_reference v)
    {
        BOOST_ASSERT(!value_compare()(v, handle.iterator->first));
        handle.iterator->first = v;
        increase(handle);
    }

    void increase(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.increase(index);
    }

    void decrease(handle_type handle, const_reference v)
    {
        BOOST_ASSERT(!value_compare()(handle.iterator->first, v));
        handle.iterator->first = v;
        decrease(handle);
    }

    void decrease(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.decrease(index);
    }

    void erase(handle_type handle)
    {
        list_iterator it = handle.iterator;
        size_type index = it->second;
        q_.erase(index);
        objects.erase(it);
    }


    const_iterator begin(void) const
    {
        return const_iterator(objects.begin());
    }


    const_iterator end(void) const
    {
        return const_iterator(objects.end());
    }


    iterator begin(void)
    {
        return iterator(objects.begin());
    }


    iterator end(void)
    {
        return iterator(objects.end());
    }


    ordered_iterator ordered_begin(void) const
    {
        if (!empty())
            return ordered_iterator(q_.top(), this, indirect_cmp(q_.value_comp()));
        else
            return ordered_end();
    }


    ordered_iterator ordered_end(void) const
    {
        return ordered_iterator(objects.end(), this, indirect_cmp(q_.value_comp()));
    }


    static handle_type s_handle_from_iterator(iterator const & it)
    {
        return handle_type(it.get_list_iterator());
    }


    value_compare const & value_comp(void) const
    {
        return q_.value_comp();
    }


    void reserve (size_type element_count)
    {
        q_.reserve(element_count);
    }


template <typename Heap1, typename Heap2>
bool value_equality(Heap1 const & lhs, Heap2 const & rhs,
                    typename Heap1::value_type lval, typename Heap2::value_type rval)
{
    typename Heap1::value_compare const & cmp = lhs.value_comp();
    bool ret = !(cmp(lval, rval)) && !(cmp(rval, lval));

    // if this assertion is triggered, the value_compare objects of lhs and rhs return different values
    BOOST_ASSERT((ret == (!(rhs.value_comp()(lval, rval)) && !(rhs.value_comp()(rval, lval)))));

    return ret;
}


template <typename Heap1, typename Heap2>
bool value_compare(Heap1 const & lhs, Heap2 const & rhs,
                    typename Heap1::value_type lval, typename Heap2::value_type rval)
{
    typename Heap1::value_compare const & cmp = lhs.value_comp();
    bool ret = cmp(lval, rval);

    // if this assertion is triggered, the value_compare objects of lhs and rhs return different values
    BOOST_ASSERT((ret == rhs.value_comp()(lval, rval)));
    return ret;
}

    template <typename Heap1, typename Heap2>
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

        // if this assertion is triggered, the value_compare types are incompatible
        BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

        if (Heap1::constant_time_size && Heap2::constant_time_size)
            if (lhs.size() != rhs.size())
                return false;

        if (lhs.empty() && rhs.empty())
            return true;

        Heap1 lhs_copy(lhs);
        Heap2 rhs_copy(rhs);

        while (true) {
            if (!value_equality(lhs_copy, rhs_copy, lhs_copy.top(), rhs_copy.top()))
                return false;

            lhs_copy.pop();
            rhs_copy.pop();

            if (lhs_copy.empty() && rhs_copy.empty())
                return true;

            if (lhs_copy.empty())
                return false;

            if (rhs_copy.empty())
                return false;
        }
    }

    template <typename Heap1, typename Heap2>
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap1>));
        BOOST_CONCEPT_ASSERT((boost::heap::PriorityQueue<Heap2>));

        // if this assertion is triggered, the value_compare types are incompatible
        BOOST_STATIC_ASSERT((boost::is_same<typename Heap1::value_compare, typename Heap2::value_compare>::value));

        if (Heap1::constant_time_size && Heap2::constant_time_size)
            if (lhs.size() != rhs.size())
                return false;

        if (lhs.empty() && rhs.empty())
            return true;

        typename Heap1::ordered_iterator it1 = lhs.ordered_begin();
        typename Heap1::ordered_iterator it1_end = lhs.ordered_end();
        typename Heap1::ordered_iterator it2 = rhs.ordered_begin();
        typename Heap1::ordered_iterator it2_end = rhs.ordered_end();
        while (true) {
            if (!value_equality(lhs, rhs, *it1, *it2))
                return false;

            ++it1;
            ++it2;

            if (it1 == it1_end && it2 == it2_end)
                return true;

            if (it1 == it1_end || it2 == it2_end)
                return false;
        }
    }



template <typename Heap1,
          typename Heap2
         >
bool heap_equality(Heap1 const & lhs, Heap2 const & rhs)
{
    const bool use_ordered_iterators = Heap1::has_ordered_iterators && Heap2::has_ordered_iterators;

    typedef typename boost::mpl::if_c<use_ordered_iterators,
                                      heap_equivalence_iteration,
                                      heap_equivalence_copy
                                     >::type equivalence_check;

    equivalence_check eq_check;
    return eq_check(lhs, rhs);
}

    template <typename Heap1,
              typename Heap2
             >
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        typename Heap1::size_type left_size = lhs.size();
        typename Heap2::size_type right_size = rhs.size();
        if (left_size < right_size)
            return true;

        if (left_size > right_size)
            return false;

        typename Heap1::ordered_iterator it1 = lhs.ordered_begin();
        typename Heap1::ordered_iterator it1_end = lhs.ordered_end();
        typename Heap1::ordered_iterator it2 = rhs.ordered_begin();
        typename Heap1::ordered_iterator it2_end = rhs.ordered_end();
        while (true) {
            if (value_compare(lhs, rhs, *it1, *it2))
                return true;

            if (value_compare(lhs, rhs, *it2, *it1))
                return false;

            ++it1;
            ++it2;

            if (it1 == it1_end && it2 == it2_end)
                return true;

            if (it1 == it1_end || it2 == it2_end)
                return false;
        }
    }

    template <typename Heap1,
              typename Heap2
             >
    bool operator()(Heap1 const & lhs, Heap2 const & rhs)
    {
        typename Heap1::size_type left_size = lhs.size();
        typename Heap2::size_type right_size = rhs.size();
        if (left_size < right_size)
            return true;

        if (left_size > right_size)
            return false;

        Heap1 lhs_copy(lhs);
        Heap2 rhs_copy(rhs);

        while (true) {
            if (value_compare(lhs_copy, rhs_copy, lhs_copy.top(), rhs_copy.top()))
                return true;

            if (value_compare(lhs_copy, rhs_copy, rhs_copy.top(), lhs_copy.top()))
                return false;

            lhs_copy.pop();
            rhs_copy.pop();

            if (lhs_copy.empty() && rhs_copy.empty())
                return false;
        }
    }


template <typename Heap1,
          typename Heap2
         >
bool heap_compare(Heap1 const & lhs, Heap2 const & rhs)
{
    const bool use_ordered_iterators = Heap1::has_ordered_iterators && Heap2::has_ordered_iterators;

    typedef typename boost::mpl::if_c<use_ordered_iterators,
                                      heap_compare_iteration,
                                      heap_compare_copy
                                     >::type compare_check;

    compare_check check_object;
    return check_object(lhs, rhs);
}

    template <typename T>
    void operator()(T * n)
    {
        BOOST_HEAP_ASSERT(false);
    }


template <typename Node, typename HeapBase>
bool is_heap(const Node * n, typename HeapBase::value_compare const & cmp)
{
    for (typename Node::const_child_iterator it = n->children.begin(); it != n->children.end(); ++it) {
        Node const & this_node = static_cast<Node const &>(*it);
        const Node * child = static_cast<const Node*>(&this_node);

        if (cmp(HeapBase::get_value(n->value), HeapBase::get_value(child->value)) ||
            !is_heap<Node, HeapBase>(child, cmp))
            return false;
    }
    return true;
}


template <typename Node, typename List>
std::size_t count_list_nodes(List const & node_list)
{
    std::size_t ret = 0;

    for (typename List::const_iterator it = node_list.begin(); it != node_list.end(); ++it) {
        const Node * child = static_cast<const Node*>(&*it);
        ret += count_nodes<Node>(child);
    }
    return ret;
}

    node_cloner(Alloc & allocator):
        allocator(allocator)
    {}


    Node * operator() (NodeBase const & node)
    {
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator);
        return ret;
    }


    Node * operator() (NodeBase const & node, Node * parent)
    {
        Node * ret = allocator.allocate(1);
        new (ret) Node(static_cast<Node const &>(node), allocator, parent);
        return ret;
    }


    node_disposer(Alloc & alloc):
        alloc_(alloc)
    {}


    void operator()(NodeBase * base)
    {
        node_pointer n = static_cast<node_pointer>(base);
        n->clear_subtree(alloc_);
        alloc_.deallocate(n, 1);
    }


    heap_node(ValueType const & v):
        value(v)
    {}

    template <class... Args>
    heap_node(Args&&... args):
        value(std::forward<Args>(args)...)
    {}

    heap_node(heap_node const & rhs):
        value(rhs.value)
    {
        /* we don't copy the child list, but clone it later */
    }


    template <typename Alloc>
    heap_node (heap_node const & rhs, Alloc & allocator):
        value(rhs.value)
    {
        children.clone_from(rhs.children, node_cloner<heap_node, node_base, Alloc>(allocator), nop_disposer());
    }


    size_type child_count(void) const
    {
        BOOST_STATIC_ASSERT(constant_time_child_size);
        return children.size();
    }


    void add_child(heap_node * n)
    {
        children.push_back(*n);
    }


    template <typename Alloc>
    void clear_subtree(Alloc & alloc)
    {
        children.clear_and_dispose(node_disposer<heap_node, node_base, Alloc>(alloc));
    }


    void swap_children(heap_node * rhs)
    {
        children.swap(rhs->children);
    }


    parent_pointing_heap_node(value_type const & v):
        super_t(v), parent(NULL)
    {}

    template <class... Args>
    parent_pointing_heap_node(Args&&... args):
        super_t(std::forward<Args>(args)...), parent(NULL)
    {}

        node_cloner(Alloc & allocator, parent_pointing_heap_node * parent):
            allocator(allocator), parent_(parent)
        {}


        parent_pointing_heap_node * operator() (typename super_t::node_base const & node)
        {
            parent_pointing_heap_node * ret = allocator.allocate(1);
            new (ret) parent_pointing_heap_node(static_cast<parent_pointing_heap_node const &>(node), allocator, parent_);
            return ret;
        }


    template <typename Alloc>
    parent_pointing_heap_node (parent_pointing_heap_node const & rhs, Alloc & allocator, parent_pointing_heap_node * parent):
        super_t(static_cast<super_t const &>(rhs)), parent(parent)
    {
        super_t::children.clone_from(rhs.children, node_cloner<Alloc>(allocator, this), nop_disposer());
    }


    void update_children(void)
    {
        typedef heap_node_list::iterator node_list_iterator;
        for (node_list_iterator it = super_t::children.begin(); it != super_t::children.end(); ++it) {
            parent_pointing_heap_node * child = static_cast<parent_pointing_heap_node*>(&*it);
            child->parent = this;
        }
    }


    void remove_from_parent(void)
    {
        BOOST_HEAP_ASSERT(parent);
        parent->children.erase(heap_node_list::s_iterator_to(*this));
        parent = NULL;
    }


    void add_child(parent_pointing_heap_node * n)
    {
        BOOST_HEAP_ASSERT(n->parent == NULL);
        n->parent = this;
        super_t::add_child(n);
    }


    parent_pointing_heap_node * get_parent(void)
    {
        return parent;
    }


    const parent_pointing_heap_node * get_parent(void) const
    {
        return parent;
    }


    marked_heap_node(value_type const & v):
        super_t(v), mark(false)
    {}

    template <class... Args>
    marked_heap_node(Args&&... args):
        super_t(std::forward<Args>(args)...), mark(false)
    {}


    marked_heap_node * get_parent(void)
    {
        return static_cast<marked_heap_node*>(super_t::parent);
    }


    const marked_heap_node * get_parent(void) const
    {
        return static_cast<marked_heap_node*>(super_t::parent);
    }

    template <typename NodeBase>
    bool operator()(NodeBase const & left,
                    NodeBase const & right)
    {
        return static_cast<const Node*>(&left)->child_count() < static_cast<const Node*>(&right)->child_count();
    }


template <typename List, typename Node, typename Cmp>
Node * find_max_child(List const & list, Cmp const & cmp)
{
    BOOST_HEAP_ASSERT(!list.empty());

    const Node * ret = static_cast<const Node *> (&list.front());
    for (typename List::const_iterator it = list.begin(); it != list.end(); ++it) {
        const Node * current = static_cast<const Node *> (&*it);

        if (cmp(ret->value, current->value))
            ret = current;
    }

    return const_cast<Node*>(ret);
}

    type& operator()(type& x) const
    { return x; }


    const type& operator()(const type& x) const
    { return x; }

    template <typename U>
    type& operator()(U& x) const
    { return static_cast<type&>(x); }


    template <typename U>
    const type& operator()(const U& x) const
    { return static_cast<const type&>(x); }

    template <typename Iterator>
    Node * operator()(Iterator const & it)
    {
        return static_cast<Node *>(*it);
    }

    template <typename Iterator>
    const Node * operator()(Iterator const & it)
    {
        return static_cast<const Node *>(&*it);
    }

    unordered_tree_iterator_storage(ValueCompare const & cmp)
    {}


    void push(HandleType h)
    {
        data_.push_back(h);
    }


    HandleType const & top(void)
    {
        return data_.back();
    }


    void pop(void)
    {
        data_.pop_back();
    }


    bool empty(void) const
    {
        return data_.empty();
    }

        compare_values_by_handle(ValueCompare const & cmp):
            ValueCompare(cmp)
        {}


        bool operator()(HandleType const & lhs, HandleType const & rhs) const
        {
            ValueType const & lhs_value = ValueExtractor::operator()(lhs->value);
            ValueType const & rhs_value = ValueExtractor::operator()(rhs->value);
            return ValueCompare::operator()(lhs_value, rhs_value);
        }


    ordered_tree_iterator_storage(ValueCompare const & cmp):
        data_(compare_values_by_handle(cmp))
    {}


    void push(HandleType h)
    {
        data_.push(h);
    }


    void pop(void)
    {
        data_.pop();
    }


    HandleType const & top(void)
    {
        return data_.top();
    }


    bool empty(void) const
    {
        return data_.empty();
    }

    typename NodeList::const_iterator operator()(const Node * node)
    {
        return NodeList::s_iterator_to(*node);
    }


    Node * operator()(typename NodeList::const_iterator it)
    {
        return const_cast<Node*>(static_cast<const Node*>(&*it));
    }

    recursive_tree_iterator(void):
        adaptor_type(0)
    {}


    explicit recursive_tree_iterator(NodeIterator const & it):
        adaptor_type(it)
    {}


    void increment(void)
    {
        NodeIterator next = adaptor_type::base_reference();

        const Node * n = get_node(next);
        if (n->children.empty()) {
            const Node * parent = get_node(next)->get_parent();

            ++next;

            while (true) {
                if (parent == NULL || next != parent->children.end())
                    break;

                next = IteratorCoverter::operator()(parent);
                parent = get_node(next)->get_parent();
                ++next;
            }
        } else
            next = n->children.begin();

        adaptor_type::base_reference() = next;
        return;
    }


    ValueType const & dereference() const
    {
        return ValueExtractor::operator()(get_node(adaptor_type::base_reference())->value);
    }


    static const Node * get_node(NodeIterator const & it)
    {
        return static_cast<const Node *>(&*it);
    }


    const Node * get_node() const
    {
        return get_node(adaptor_type::base_reference());
    }

    IntType operator()(IntType value)
    {
        IntType l = 0;
        while( (value >> l) > 1 )
            ++l;
        return l;
    }

    unsigned int operator()(unsigned int value)
    {
        return sizeof(unsigned int)*8 - __builtin_clz(value - 1);
    }

    unsigned long operator()(unsigned long value)
    {
        return sizeof(unsigned long)*8 - __builtin_clzl(value - 1);
    }



template <typename IntType>
IntType log2(IntType value)
{
    detail::log2<IntType> fn;
    return fn(value);
}
