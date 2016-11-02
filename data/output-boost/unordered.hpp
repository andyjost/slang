
        unordered_map(unordered_map&& other)
            : table_(other.table_, boost::unordered::detail::move_tag())
        {
        }

        unordered_map& operator=(unordered_map const& x)
        {
            table_.assign(x.table_);
            return *this;
        }

        unordered_map& operator=(unordered_map&& x)
        {
            table_.move_assign(x.table_);
            return *this;
        }

        void quick_erase(const_iterator it) { erase(it); }

        void erase_return_void(const_iterator it) { erase(it); }


        size_type bucket(const key_type& k) const
        {
            return table_.hash_to_bucket(table_.hash(k));
        }


        local_iterator end(size_type)
        {
            return local_iterator();
        }


        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }

        unordered_multimap(unordered_multimap&& other)
            : table_(other.table_, boost::unordered::detail::move_tag())
        {
        }

        unordered_multimap& operator=(unordered_multimap const& x)
        {
            table_.assign(x.table_);
            return *this;
        }

        unordered_multimap& operator=(unordered_multimap&& x)
        {
            table_.move_assign(x.table_);
            return *this;
        }

        void quick_erase(const_iterator it) { erase(it); }

        void erase_return_void(const_iterator it) { erase(it); }


        size_type bucket(const key_type& k) const
        {
            return table_.hash_to_bucket(table_.hash(k));
        }


        local_iterator end(size_type)
        {
            return local_iterator();
        }


        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }


    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            size_type n, const hasher &hf, const key_equal &eql,
            const allocator_type &a)
      : table_(n, hf, eql, a)
    {
    }


    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(allocator_type const& a)
      : table_(boost::unordered::detail::default_bucket_count,
            hasher(), key_equal(), a)
    {
    }


    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            unordered_map const& other, allocator_type const& a)
      : table_(other.table_, a)
    {
    }

    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(InputIt f, InputIt l)
      : table_(boost::unordered::detail::initial_size(f, l),
        hasher(), key_equal(), allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql)
      : table_(boost::unordered::detail::initial_size(f, l, n),
            hf, eql, allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql,
            const allocator_type &a)
      : table_(boost::unordered::detail::initial_size(f, l, n), hf, eql, a)
    {
        table_.insert_range(f, l);
    }

    
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::~unordered_map() {}


    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            unordered_map const& other)
      : table_(other.table_)
    {
    }


    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            unordered_map&& other, allocator_type const& a)
      : table_(other.table_, a, boost::unordered::detail::move_tag())
    {
    }

        unordered_set(unordered_set&& other)
            : table_(other.table_, boost::unordered::detail::move_tag())
        {
        }

        unordered_set& operator=(unordered_set const& x)
        {
            table_.assign(x.table_);
            return *this;
        }

        unordered_set& operator=(unordered_set&& x)
        {
            table_.move_assign(x.table_);
            return *this;
        }

        void quick_erase(const_iterator it) { erase(it); }

        void erase_return_void(const_iterator it) { erase(it); }


        size_type bucket(const key_type& k) const
        {
            return table_.hash_to_bucket(table_.hash(k));
        }


        local_iterator begin(size_type n)
        {
            return local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        local_iterator end(size_type)
        {
            return local_iterator();
        }


        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }

        unordered_multiset(unordered_multiset&& other)
            : table_(other.table_, boost::unordered::detail::move_tag())
        {
        }

        unordered_multiset& operator=(unordered_multiset const& x)
        {
            table_.assign(x.table_);
            return *this;
        }

        unordered_multiset& operator=(unordered_multiset&& x)
        {
            table_.move_assign(x.table_);
            return *this;
        }

        void quick_erase(const_iterator it) { erase(it); }

        void erase_return_void(const_iterator it) { erase(it); }


        size_type bucket(const key_type& k) const
        {
            return table_.hash_to_bucket(table_.hash(k));
        }


        local_iterator begin(size_type n)
        {
            return local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        local_iterator end(size_type)
        {
            return local_iterator();
        }


        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.begin(n), n, table_.bucket_count_);
        }


        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }


    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::unordered_set(
            size_type n, const hasher &hf, const key_equal &eql,
            const allocator_type &a)
      : table_(n, hf, eql, a)
    {
    }


    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::unordered_set(allocator_type const& a)
      : table_(boost::unordered::detail::default_bucket_count,
            hasher(), key_equal(), a)
    {
    }


    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::unordered_set(
            unordered_set const& other, allocator_type const& a)
      : table_(other.table_, a)
    {
    }

    template <class InputIt>
    unordered_set<T,H,P,A>::unordered_set(InputIt f, InputIt l)
      : table_(boost::unordered::detail::initial_size(f, l),
        hasher(), key_equal(), allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class InputIt>
    unordered_set<T,H,P,A>::unordered_set(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql)
      : table_(boost::unordered::detail::initial_size(f, l, n),
            hf, eql, allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class InputIt>
    unordered_set<T,H,P,A>::unordered_set(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql,
            const allocator_type &a)
      : table_(boost::unordered::detail::initial_size(f, l, n), hf, eql, a)
    {
        table_.insert_range(f, l);
    }

    
    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::~unordered_set() {}


    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::unordered_set(
            unordered_set const& other)
      : table_(other.table_)
    {
    }


    template <class T, class H, class P, class A>
    unordered_set<T,H,P,A>::unordered_set(
            unordered_set&& other, allocator_type const& a)
      : table_(other.table_, a, boost::unordered::detail::move_tag())
    {
    }


        unique_node() :
            next_(),
            hash_(0)
        {}


        void init(node_pointer)
        {
        }


        ptr_node() :
            bucket_base(),
            hash_(0)
        {}


        void init(node_pointer)
        {
        }


        table_impl(std::size_t n,
                hasher const& hf,
                key_equal const& eq,
                node_allocator const& a)
          : table(n, hf, eq, a)
        {}


        table_impl(table_impl const& x)
          : table(x, node_allocator_traits::
                select_on_container_copy_construction(x.node_alloc()))
        {
            this->init(x);
        }


        table_impl(table_impl const& x,
                node_allocator const& a)
          : table(x, a)
        {
            this->init(x);
        }


        template <class Key, class Pred>
        iterator find_node_impl(
                std::size_t key_hash,
                Key const& k,
                Pred const& eq) const
        {
            std::size_t bucket_index = this->hash_to_bucket(key_hash);
            iterator n = this->begin(bucket_index);

            for (;;)
            {
                if (!n.node_) return n;

                std::size_t node_hash = n.node_->hash_;
                if (key_hash == node_hash)
                {
                    if (eq(k, this->get_key(*n)))
                        return n;
                }
                else
                {
                    if (this->hash_to_bucket(node_hash) != bucket_index)
                        return iterator();
                }

                ++n;
            }
        }


        std::size_t count(key_type const& k) const
        {
            return this->find_node(k).node_ ? 1 : 0;
        }


        value_type& at(key_type const& k) const
        {
            if (this->size_) {
                iterator it = this->find_node(k);
                if (it.node_) return *it;
            }

            boost::throw_exception(
                std::out_of_range("Unable to find key in unordered_map."));
        }


    template <class T>
    inline void destroy(T* x) {
        x->~T();
    }


    template <typename Alloc>
    inline Alloc call_select_on_container_copy_construction(const Alloc& rhs,
        typename boost::enable_if_c<
            boost::unordered::detail::
            has_select_on_container_copy_construction<Alloc>::value, void*
        >::type = 0)
    {
        return rhs.select_on_container_copy_construction();
    }


    template <typename SizeType, typename Alloc>
    inline SizeType call_max_size(const Alloc& a,
        typename boost::enable_if_c<
            boost::unordered::detail::has_max_size<Alloc>::value, void*
        >::type = 0)
    {
        return a.max_size();
    }


        static pointer allocate(Alloc& a, size_type n)
            { return a.allocate(n); }


        static void deallocate(Alloc& a, pointer p, size_type n)
            { a.deallocate(p, n); }


    template <typename Alloc, typename T, typename... Args>
    inline void call_construct(Alloc& alloc, T* address,
        BOOST_FWD_REF(Args)... args)
    {
        boost::unordered::detail::allocator_traits<Alloc>::construct(alloc,
            address, boost::forward<Args>(args)...);
    }


    template <typename Alloc, typename T>
    inline void destroy_value_impl(Alloc& alloc, T* x) {
        boost::unordered::detail::allocator_traits<Alloc>::destroy(alloc, x);
    }
              \
    template<typename Alloc, typename T>                                    \
    void construct_from_tuple(Alloc& alloc, T* ptr, namespace_ tuple<>)     \
    {                                                                       \
        boost::unordered::detail::call_construct(alloc, ptr);               \
    }                                                                       \
                                                                            \
    BOOST_PP_REPEAT_FROM_TO(1, n,                                           \
        BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL, namespace_)

#   define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL(z, n, namespace_)      \
    template<typename Alloc, typename T,                                    \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                           \
    void construct_from_tuple(Alloc& alloc, T* ptr,                         \
            namespace_ tuple<BOOST_PP_ENUM_PARAMS_Z(z, n, A)> const& x)     \
    {                                                                       \
        boost::unordered::detail::call_construct(alloc, ptr,                \
            BOOST_PP_ENUM_##z(n, BOOST_UNORDERED_GET_TUPLE_ARG, namespace_) \
        );                                                                  \
    }

#   define BOOST_UNORDERED_GET_TUPLE_ARG(z, n, namespace_)                  \
    namespace_ get<n>(x)

#elif !defined(__SUNPRO_CC)

#   define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(n, namespace_)              \
    template<typename Alloc, typename T>                                    \
    void construct_from_tuple(Alloc&, T* ptr, namespace_ tuple<>)           \
    {                                                                       \
        new ((void*) ptr) T();                                              \
    }                                                                       \
                                                                            \
    BOOST_PP_REPEAT_FROM_TO(1, n,                                           \
        BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL, namespace_)

#   define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL(z, n, namespace_)      \
    template<typename Alloc, typename T,                                    \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                           \
    void construct_from_tuple(Alloc&, T* ptr,                               \
            namespace_ tuple<BOOST_PP_ENUM_PARAMS_Z(z, n, A)> const& x)     \
    {                                                                       \
        new ((void*) ptr) T(                                                \
            BOOST_PP_ENUM_##z(n, BOOST_UNORDERED_GET_TUPLE_ARG, namespace_) \
        );                                                                  \
    }

#   define BOOST_UNORDERED_GET_TUPLE_ARG(z, n, namespace_)                  \
    namespace_ get<n>(x)

#else

    template <int N> struct length {};

#   define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(n, namespace_)              \
    template<typename Alloc, typename T>                                    \
    void construct_from_tuple_impl(                                         \
            boost::unordered::detail::length<0>, Alloc&, T* ptr,            \
            namespace_ tuple<>)                                             \
    {                                                                       \
        new ((void*) ptr) T();                                              \
    }                                                                       \
                                                                            \
    BOOST_PP_REPEAT_FROM_TO(1, n,                                           \
        BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL, namespace_)

#   define BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE_IMPL(z, n, namespace_)      \
    template<typename Alloc, typename T,                                    \
        BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>                           \
    void construct_from_tuple_impl(                                         \
            boost::unordered::detail::length<n>, Alloc&, T* ptr,            \
            namespace_ tuple<BOOST_PP_ENUM_PARAMS_Z(z, n, A)> const& x)     \
    {                                                                       \
        new ((void*) ptr) T(                                                \
            BOOST_PP_ENUM_##z(n, BOOST_UNORDERED_GET_TUPLE_ARG, namespace_) \
        );                                                                  \
    }

#   define BOOST_UNORDERED_GET_TUPLE_ARG(z, n, namespace_)                  \
    namespace_ get<n>(x)

#endif

BOOST_UNORDERED_CONSTRUCT_FROM_TUPLE(10, boost::)


    template <typename Alloc, typename T, typename... Args>
    inline void construct_value_impl(Alloc& alloc, T* address,
        BOOST_FWD_REF(Args)... args)
    {
        boost::unordered::detail::call_construct(alloc,
            address, boost::forward<Args>(args)...);
    }


        array_constructor(Allocator& a)
            : alloc_(a), ptr_(), constructed_(), length_(0)
        {
            constructed_ = pointer();
            ptr_ = pointer();
        }


        ~array_constructor() {
            if (ptr_) {
                for(pointer p = ptr_; p != constructed_; ++p)
                    traits::destroy(alloc_, boost::addressof(*p));

                traits::deallocate(alloc_, ptr_, length_);
            }
        }


        template <typename V>
        void construct(V const& v, std::size_t l)
        {
            BOOST_ASSERT(!ptr_);
            length_ = l;
            ptr_ = traits::allocate(alloc_, length_);
            pointer end = ptr_ + static_cast<std::ptrdiff_t>(length_);
            for(constructed_ = ptr_; constructed_ != end; ++constructed_)
                traits::construct(alloc_, boost::addressof(*constructed_), v);
        }


        pointer get() const
        {
            return ptr_;
        }


        pointer release()
        {
            pointer p(ptr_);
            ptr_ = pointer();
            return p;
        }


        l_iterator() : ptr_() {}


        value_type& operator*() const {
            return ptr_->value();
        }


        value_type* operator->() const {
            return ptr_->value_ptr();
        }


        l_iterator& operator++() {
            ptr_ = static_cast<node_pointer>(ptr_->next_);
            if (ptr_ && Policy::to_bucket(bucket_count_, ptr_->hash_)
                    != bucket_)
                ptr_ = node_pointer();
            return *this;
        }


        l_iterator operator++(int) {
            l_iterator tmp(*this);
            ++(*this);
            return tmp;
        }


        bool operator==(l_iterator x) const {
            return ptr_ == x.ptr_;
        }


        bool operator!=(l_iterator x) const {
            return ptr_ != x.ptr_;
        }


        cl_iterator() : ptr_() {}


        cl_iterator(boost::unordered::iterator_detail::l_iterator<
                Node, Policy> const& x) :
            ptr_(x.ptr_), bucket_(x.bucket_), bucket_count_(x.bucket_count_)
        {}


        value_type const& operator*() const {
            return ptr_->value();
        }


        value_type const* operator->() const {
            return ptr_->value_ptr();
        }


        cl_iterator& operator++() {
            ptr_ = static_cast<node_pointer>(ptr_->next_);
            if (ptr_ && Policy::to_bucket(bucket_count_, ptr_->hash_)
                    != bucket_)
                ptr_ = node_pointer();
            return *this;
        }


        cl_iterator operator++(int) {
            cl_iterator tmp(*this);
            ++(*this);
            return tmp;
        }


        iterator() : node_() {}


        explicit iterator(typename Node::link_pointer x) :
            node_(static_cast<node_pointer>(x)) {}


        value_type& operator*() const {
            return node_->value();
        }


        value_type* operator->() const {
            return &node_->value();
        }


        iterator& operator++() {
            node_ = static_cast<node_pointer>(node_->next_);
            return *this;
        }


        iterator operator++(int) {
            iterator tmp(node_);
            node_ = static_cast<node_pointer>(node_->next_);
            return tmp;
        }


        bool operator==(iterator const& x) const {
            return node_ == x.node_;
        }


        bool operator!=(iterator const& x) const {
            return node_ != x.node_;
        }


        c_iterator() : node_() {}


        explicit c_iterator(typename Node::link_pointer x) :
            node_(static_cast<node_pointer>(x)) {}


        c_iterator(iterator const& x) : node_(x.node_) {}


        value_type const& operator*() const {
            return node_->value();
        }


        value_type const* operator->() const {
            return &node_->value();
        }


        c_iterator& operator++() {
            node_ = static_cast<node_pointer>(node_->next_);
            return *this;
        }


        c_iterator operator++(int) {
            c_iterator tmp(node_);
            node_ = static_cast<node_pointer>(node_->next_);
            return tmp;
        }


        node_constructor(node_allocator& n) :
            alloc_(n),
            node_(),
            node_constructed_(false),
            value_constructed_(false)
        {
        }


        template <BOOST_UNORDERED_EMPLACE_TEMPLATE>
        void construct_with_value(BOOST_UNORDERED_EMPLACE_ARGS)
        {
            construct();
            boost::unordered::detail::construct_value_impl(
                alloc_, node_->value_ptr(), BOOST_UNORDERED_EMPLACE_FORWARD);
            value_constructed_ = true;
        }


        template <typename A0>
        void construct_with_value2(BOOST_FWD_REF(A0) a0)
        {
            construct();
            boost::unordered::detail::construct_value_impl(
                alloc_, node_->value_ptr(),
                BOOST_UNORDERED_EMPLACE_ARGS1(boost::forward<A0>(a0)));
            value_constructed_ = true;
        }


        value_type const& value() const {
            BOOST_ASSERT(node_ && node_constructed_ && value_constructed_);
            return node_->value();
        }

        node_pointer release()
        {
            BOOST_ASSERT(node_ && node_constructed_);
            node_pointer p = node_;
            node_ = node_pointer();
            return p;
        }


    template <typename Alloc>
    node_constructor<Alloc>::~node_constructor()
    {
        if (node_) {
            if (value_constructed_) {
                boost::unordered::detail::destroy_value_impl(alloc_,
                    node_->value_ptr());
            }

            if (node_constructed_) {
                node_allocator_traits::destroy(alloc_,
                    boost::addressof(*node_));
            }

            node_allocator_traits::deallocate(alloc_, node_, 1);
        }
    }


    template <typename Alloc>
    void node_constructor<Alloc>::construct()
    {
        if(!node_) {
            node_constructed_ = false;
            value_constructed_ = false;

            node_ = node_allocator_traits::allocate(alloc_, 1);

            node_allocator_traits::construct(alloc_,
                boost::addressof(*node_), node());
            node_->init(node_);
            node_constructed_ = true;
        }
        else {
            BOOST_ASSERT(node_constructed_);

            if (value_constructed_)
            {
                boost::unordered::detail::destroy_value_impl(alloc_,
                    node_->value_ptr());
                value_constructed_ = false;
            }
        }
    }


        template <typename Table>
        explicit node_holder(Table& b) :
            base(b.node_alloc()),
            nodes_()
        {
            if (b.size_) {
                typename Table::link_pointer prev = b.get_previous_start();
                nodes_ = static_cast<node_pointer>(prev->next_);
                prev->next_ = link_pointer();
                b.size_ = 0;
            }
        }


        void node_for_assignment()
        {
            if (!this->node_ && nodes_) {
                this->node_ = nodes_;
                nodes_ = static_cast<node_pointer>(nodes_->next_);
                this->node_->init(this->node_);
                this->node_->next_ = link_pointer();

                this->node_constructed_ = true;
                this->value_constructed_ = true;
            }
        }


        template <typename T>
        inline void assign_impl(T const& v) {
            if (this->node_ && this->value_constructed_) {
                this->node_->value() = v;
            }
            else {
                this->construct_with_value2(v);
            }
        }


        template <typename T>
        inline void move_assign_impl(T& v) {
            if (this->node_ && this->value_constructed_) {
                this->node_->value() = boost::move(v);
            }
            else {
                this->construct_with_value2(boost::move(v));
            }
        }


        node_pointer copy_of(value_type const& v)
        {
            node_for_assignment();
            assign_impl(v);
            return base::release();
        }


        node_pointer move_copy_of(value_type& v)
        {
            node_for_assignment();
            move_assign_impl(v);
            return base::release();
        }


        iterator begin() const
        {
            return iterator(nodes_);
        }


    template <typename Alloc>
    node_holder<Alloc>::~node_holder()
    {
        while (nodes_) {
            node_pointer p = nodes_;
            nodes_ = static_cast<node_pointer>(p->next_);

            boost::unordered::detail::destroy_value_impl(this->alloc_,
                p->value_ptr());
            node_allocator_traits::destroy(this->alloc_, boost::addressof(*p));
            node_allocator_traits::deallocate(this->alloc_, p, 1);
        }
    }


        bucket() : next_() {}


        link_pointer first_from_start()
        {
            return next_;
        }


        ptr_bucket() : next_(0) {}


        link_pointer first_from_start()
        {
            return this;
        }

        template <typename Hash, typename T>
        static inline SizeT apply_hash(Hash const& hf, T const& x) {
            return hf(x);
        }


        static inline SizeT to_bucket(SizeT bucket_count, SizeT hash) {
            return hash % bucket_count;
        }


        static inline SizeT new_bucket_count(SizeT min) {
            return boost::unordered::detail::next_prime(min);
        }


        static inline SizeT prev_bucket_count(SizeT max) {
            return boost::unordered::detail::prev_prime(max);
        }

        template <typename Hash, typename T>
        static inline SizeT apply_hash(Hash const& hf, T const& x) {
            SizeT key = hf(x);
            key = (~key) + (key << 21); // key = (key << 21) - key - 1;
            key = key ^ (key >> 24);
            key = (key + (key << 3)) + (key << 8); // key * 265
            key = key ^ (key >> 14);
            key = (key + (key << 2)) + (key << 4); // key * 21
            key = key ^ (key >> 28);
            key = key + (key << 31);
            return key;
        }


        static inline SizeT to_bucket(SizeT bucket_count, SizeT hash) {
            return hash & (bucket_count - 1);
        }


        static inline SizeT new_bucket_count(SizeT min) {
            if (min <= 4) return 4;
            --min;
            min |= min >> 1;
            min |= min >> 2;
            min |= min >> 4;
            min |= min >> 8;
            min |= min >> 16;
            min |= min >> 32;
            return min + 1;
        }


        static inline SizeT prev_bucket_count(SizeT max) {
            max |= max >> 1;
            max |= max >> 2;
            max |= max >> 4;
            max |= max >> 8;
            max |= max >> 16;
            max |= max >> 32;
            return (max >> 1) + 1;
        }


        functions(H const& hf, P const& eq)
            : current_(false)
        {
            construct(current_, hf, eq);
        }


        functions(functions const& bf)
            : current_(false)
        {
            construct(current_, bf.current());
        }


        ~functions() {
            this->destroy(current_);
        }


        H const& hash_function() const {
            return current().first();
        }


        P const& key_eq() const {
            return current().second();
        }


        set_hash_functions(functions_type& f, H const& h, P const& p)
          : functions_(f),
            tmp_functions_(!f.current_)
        {
            f.construct(tmp_functions_, h, p);
        }


        set_hash_functions(functions_type& f, functions_type const& other)
          : functions_(f),
            tmp_functions_(!f.current_)
        {
            f.construct(tmp_functions_, other.current());
        }


        ~set_hash_functions()
        {
            functions_.destroy(tmp_functions_);
        }


        void commit()
        {
            functions_.current_ = tmp_functions_;
            tmp_functions_ = !tmp_functions_;
        }


        set_hash_functions(functions_type& f, H const& h, P const& p) :
            functions_(f),
            hash_(h),
            pred_(p) {}


        set_hash_functions(functions_type& f, functions_type const& other) :
            functions_(f),
            hash_(other.hash_function()),
            pred_(other.key_eq()) {}


        void commit()
        {
            functions_.current().first() = boost::move(hash_);
            functions_.current().second() = boost::move(pred_);
        }


        grouped_node() :
            next_(),
            group_prev_(),
            hash_(0)
        {}


        void init(node_pointer self)
        {
            group_prev_ = self;
        }


        grouped_ptr_node() :
            bucket_base(),
            group_prev_(0),
            hash_(0)
        {}


        void init(node_pointer self)
        {
            group_prev_ = self;
        }


        grouped_table_impl(std::size_t n,
                hasher const& hf,
                key_equal const& eq,
                node_allocator const& a)
          : table(n, hf, eq, a)
        {}


        grouped_table_impl(grouped_table_impl const& x)
          : table(x, node_allocator_traits::
                select_on_container_copy_construction(x.node_alloc()))
        {
            this->init(x);
        }


        grouped_table_impl(grouped_table_impl const& x,
                node_allocator const& a)
          : table(x, a)
        {
            this->init(x);
        }


        template <class Key, class Pred>
        iterator find_node_impl(
                std::size_t key_hash,
                Key const& k,
                Pred const& eq) const
        {
            std::size_t bucket_index = this->hash_to_bucket(key_hash);
            iterator n = this->begin(bucket_index);

            for (;;)
            {
                if (!n.node_) return n;

                std::size_t node_hash = n.node_->hash_;
                if (key_hash == node_hash)
                {
                    if (eq(k, this->get_key(*n)))
                        return n;
                }
                else
                {
                    if (this->hash_to_bucket(node_hash) != bucket_index)
                        return iterator();
                }

                n = iterator(n.node_->group_prev_->next_);
            }
        }


        std::size_t count(key_type const& k) const
        {
            iterator n = this->find_node(k);
            if (!n.node_) return 0;

            std::size_t x = 0;
            node_pointer it = n.node_;
            do {
                it = it->group_prev_;
                ++x;
            } while(it != n.node_);

            return x;
        }


    inline std::size_t double_to_size(double f)
    {
        return f >= static_cast<double>(
            (std::numeric_limits<std::size_t>::max)()) ?
            (std::numeric_limits<std::size_t>::max)() :
            static_cast<std::size_t>(f);
    }


        void* address() {
            return this;
        }


        value_type& value() {
            return *(ValueType*) this;
        }


        value_type* value_ptr() {
            return (ValueType*) this;
        }


        explicit copy_nodes(NodeAlloc& a) : constructor(a) {}


        explicit move_nodes(NodeAlloc& a) : constructor(a) {}


        explicit assign_nodes(Buckets& b) : holder(b) {}


        typename Buckets::node_pointer create(
                typename Buckets::value_type const& v)
        {
            return holder.copy_of(v);
        }


        explicit move_assign_nodes(Buckets& b) : holder(b) {}


        typename Buckets::node_pointer create(
                typename Buckets::value_type& v)
        {
            return holder.move_copy_of(v);
        }

    template <typename Types>
    inline void table<Types>::reserve_for_insert(std::size_t size)
    {
        if (!buckets_) {
            create_buckets((std::max)(bucket_count_,
                min_buckets_for_size(size)));
        }
        // According to the standard this should be 'size >= max_load_',
        // but I think this is better, defect report filed.
        else if(size > max_load_) {
            std::size_t num_buckets
                = min_buckets_for_size((std::max)(size,
                    size_ + (size_ >> 1)));

            if (num_buckets != bucket_count_)
                static_cast<table_impl*>(this)->rehash_impl(num_buckets);
        }
    }

    inline std::size_t next_prime(std::size_t num) {
        std::size_t const* const prime_list_begin = prime_list::value;
        std::size_t const* const prime_list_end = prime_list_begin +
            prime_list::length;
        std::size_t const* bound =
            std::lower_bound(prime_list_begin, prime_list_end, num);
        if(bound == prime_list_end)
            bound--;
        return *bound;
    }

    inline std::size_t prev_prime(std::size_t num) {
        std::size_t const* const prime_list_begin = prime_list::value;
        std::size_t const* const prime_list_end = prime_list_begin +
            prime_list::length;
        std::size_t const* bound =
            std::upper_bound(prime_list_begin,prime_list_end, num);
        if(bound != prime_list_begin)
            bound--;
        return *bound;
    }

        insert_size(I i, I j)
    {
        return std::distance(i, j);
    }


    template <class I>
    inline std::size_t initial_size(I i, I j,
        std::size_t num_buckets =
            boost::unordered::detail::default_bucket_count)
    {
        // TODO: Why +1?
        return (std::max)(
            boost::unordered::detail::insert_size(i, j) + 1,
            num_buckets);
    }

        compressed_base(T const& x) : T(x) {}

        compressed_base(T& x, move_tag) : T(boost::move(x)) {}


        T& get() { return *this; }

        T const& get() const { return *this; }

        uncompressed_base(T const& x) : value_(x) {}

        uncompressed_base(T& x, move_tag) : value_(boost::move(x)) {}


        T& get() { return value_; }

        T const& get() const { return value_; }

        
        first_type& first() {
            return static_cast<base1*>(this)->get();
        }


        first_type const& first() const {
            return static_cast<base1 const*>(this)->get();
        }


        second_type& second() {
            return static_cast<base2*>(this)->get();
        }


        second_type const& second() const {
            return static_cast<base2 const*>(this)->get();
        }


        template <typename First, typename Second>
        compressed(First const& x1, Second const& x2)
            : base1(x1), base2(x2) {}


        compressed(compressed const& x)
            : base1(x.first()), base2(x.second()) {}


        compressed(compressed& x, move_tag m)
            : base1(x.first(), m), base2(x.second(), m) {}


        void assign(compressed const& x)
        {
            first() = x.first();
            second() = x.second();
        }


        void move_assign(compressed& x)
        {
            first() = boost::move(x.first());
            second() = boost::move(x.second());
        }

        
        void swap(compressed& x)
        {
            boost::swap(first(), x.first());
            boost::swap(second(), x.second());
        }

        no_key() {}

        template <class T> no_key(T const&) {}


        static key_type const& extract(key_type const& v)
        {
            return v;
        }


        static no_key extract()
        {
            return no_key();
        }

        template <class... Args>
        static no_key extract(Args const&...)
        {
            return no_key();
        }
