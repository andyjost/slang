
   explicit splay_set_impl( const value_compare &cmp = value_compare()
                          , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   splay_set_impl( Iterator b, Iterator e
           , const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      : tree_(true, b, e, cmp, v_traits)
   {}

   splay_set_impl(BOOST_RV_REF(splay_set_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   splay_set_impl& operator=(BOOST_RV_REF(splay_set_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~splay_set_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static splay_set_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<splay_set_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &splay_set_impl::tree_);
   }

   static splay_set_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<splay_set_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &splay_set_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(splay_set_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const splay_set_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y)
#else
(const splay_set_impl<Config> &x, const splay_set_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y)
#else
(const splay_set_impl<Config> &x, const splay_set_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y)
#else
(const splay_set_impl<Config> &x, const splay_set_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_set_impl<T, Options...> &x, const splay_set_impl<T, Options...> &y)
#else
(const splay_set_impl<Config> &x, const splay_set_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(splay_set_impl<T, Options...> &x, splay_set_impl<T, Options...> &y)
#else
(splay_set_impl<Config> &x, splay_set_impl<Config> &y)
#endif
{  x.swap(y);  }


   splay_set( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   splay_set(BOOST_RV_REF(splay_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   splay_set& operator=(BOOST_RV_REF(splay_set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static splay_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splay_set &>(Base::container_from_end_iterator(end_iterator));   }


   static const splay_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splay_set &>(Base::container_from_end_iterator(end_iterator));   }


   static splay_set &container_from_iterator(iterator it)
   {  return static_cast<splay_set &>(Base::container_from_iterator(it));   }


   static const splay_set &container_from_iterator(const_iterator it)
   {  return static_cast<const splay_set &>(Base::container_from_iterator(it));   }

   explicit splay_multiset_impl( const value_compare &cmp = value_compare()
                               , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   splay_multiset_impl( Iterator b, Iterator e
                , const value_compare &cmp = value_compare()
                , const value_traits &v_traits = value_traits())
      : tree_(false, b, e, cmp, v_traits)
   {}

   splay_multiset_impl(BOOST_RV_REF(splay_multiset_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   splay_multiset_impl& operator=(BOOST_RV_REF(splay_multiset_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~splay_multiset_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static splay_multiset_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<splay_multiset_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &splay_multiset_impl::tree_);
   }

   static splay_multiset_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<splay_multiset_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &splay_multiset_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(splay_multiset_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const splay_multiset_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

   iterator insert(reference value)
   {  return tree_.insert_equal(this->end(), value);  }

   iterator insert(const_iterator hint, reference value)
   {  return tree_.insert_equal(hint, value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_.insert_equal(b, e);  }

   iterator erase(const_iterator i)
   {  return tree_.erase(i);  }

   iterator erase(const_iterator b, const_iterator e)
   {  return tree_.erase(b, e);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return tree_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  return tree_.erase_and_dispose(b, e, disposer);  }

   void clear()
   {  return tree_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return tree_.clear_and_dispose(disposer);  }

   size_type count(const_reference value)
   {  return tree_.count(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count(const KeyType& key, KeyValueCompare comp)
   {  return tree_.count(key, comp);  }

   size_type count_dont_splay(const_reference value) const
   {  return tree_.count_dont_splay(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count_dont_splay(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.count_dont_splay(key, comp);  }

   iterator lower_bound(const_reference value)
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator lower_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.lower_bound(key, comp);  }

   const_iterator lower_bound_dont_splay(const_reference value) const
   {  return tree_.lower_bound_dont_splay(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator lower_bound_dont_splay(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.lower_bound_dont_splay(key, comp);  }

   iterator upper_bound(const_reference value)
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator upper_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.upper_bound(key, comp);  }

   const_iterator upper_bound_dont_splay(const_reference value) const
   {  return tree_.upper_bound_dont_splay(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator upper_bound_dont_splay(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.upper_bound_dont_splay(key, comp);  }

   iterator find(const_reference value)
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator find(const KeyType& key, KeyValueCompare comp)
   {  return tree_.find(key, comp);  }

   const_iterator find_dont_splay(const_reference value) const
   {  return tree_.find_dont_splay(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator find_dont_splay(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.find_dont_splay(key, comp);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y)
#else
(const splay_multiset_impl<Config> &x, const splay_multiset_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y)
#else
(const splay_multiset_impl<Config> &x, const splay_multiset_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y)
#else
(const splay_multiset_impl<Config> &x, const splay_multiset_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splay_multiset_impl<T, Options...> &x, const splay_multiset_impl<T, Options...> &y)
#else
(const splay_multiset_impl<Config> &x, const splay_multiset_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(splay_multiset_impl<T, Options...> &x, splay_multiset_impl<T, Options...> &y)
#else
(splay_multiset_impl<Config> &x, splay_multiset_impl<Config> &y)
#endif
{  x.swap(y);  }


   splay_multiset( const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   splay_multiset(BOOST_RV_REF(splay_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   splay_multiset& operator=(BOOST_RV_REF(splay_multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static splay_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static const splay_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splay_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static splay_multiset &container_from_iterator(iterator it)
   {  return static_cast<splay_multiset &>(Base::container_from_iterator(it));   }


   static const splay_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const splay_multiset &>(Base::container_from_iterator(it));   }


   static node_ptr get_next(const const_node_ptr & n)
   {
      return pointer_traits<node_ptr>::pointer_to(static_cast<node&>(*n->next_));
   }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->next_ = next;  }


   static node_ptr get_prev_in_group(const const_node_ptr & n)
   {  return n->prev_in_group_;  }


   static void set_prev_in_group(const node_ptr & n, const node_ptr & prev)
   {  n->prev_in_group_ = prev;  }


   static std::size_t get_hash(const const_node_ptr & n)
   {  return n->hash_;  }


   static void set_hash(const node_ptr & n, std::size_t h)
   {  n->hash_ = h;  }


   static node_ptr get_next(const const_node_ptr & n)
   {  return NodeTraits::get_prev_in_group(n);  }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  NodeTraits::set_prev_in_group(n, next);   }


   static void init(typename base_type::node_ptr n)
   {
      base_type::init(n);
      group_algorithms::init(n);
   }


   static void init_header(typename base_type::node_ptr n)
   {
      base_type::init_header(n);
      group_algorithms::init_header(n);
   }


   static void unlink(typename base_type::node_ptr n)
   {
      base_type::unlink(n);
      group_algorithms::unlink(n);
   }

   explicit treap_set_impl( const value_compare &cmp      = value_compare()
                          , const priority_compare &pcmp  = priority_compare()
                          , const value_traits &v_traits  = value_traits())
      :  tree_(cmp, pcmp, v_traits)
   {}

   template<class Iterator>
   treap_set_impl( Iterator b, Iterator e
           , const value_compare &cmp = value_compare()
           , const priority_compare &pcmp  = priority_compare()
           , const value_traits &v_traits = value_traits())
      : tree_(true, b, e, cmp, pcmp, v_traits)
   {}

   treap_set_impl(BOOST_RV_REF(treap_set_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   treap_set_impl& operator=(BOOST_RV_REF(treap_set_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~treap_set_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   iterator top()
   { return tree_.top();  }

   const_iterator top() const
   {  return this->ctop();   }

   const_iterator ctop() const
   { return tree_.ctop();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   reverse_iterator rtop()
   {  return tree_.rtop();  }

   const_reverse_iterator rtop() const
   {  return tree_.crtop();  }

   const_reverse_iterator crtop() const
   {  return tree_.crtop();  }

   static treap_set_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<treap_set_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &treap_set_impl::tree_);
   }

   static treap_set_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<treap_set_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &treap_set_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   priority_compare priority_comp() const
   {  return tree_.priority_comp();   }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(treap_set_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const treap_set_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_set_impl<T, Options...> &x, const treap_set_impl<T, Options...> &y)
#else
(const treap_set_impl<Config> &x, const treap_set_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_set_impl<T, Options...> &x, const treap_set_impl<T, Options...> &y)
#else
(const treap_set_impl<Config> &x, const treap_set_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_set_impl<T, Options...> &x, const treap_set_impl<T, Options...> &y)
#else
(const treap_set_impl<Config> &x, const treap_set_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_set_impl<T, Options...> &x, const treap_set_impl<T, Options...> &y)
#else
(const treap_set_impl<Config> &x, const treap_set_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(treap_set_impl<T, Options...> &x, treap_set_impl<T, Options...> &y)
#else
(treap_set_impl<Config> &x, treap_set_impl<Config> &y)
#endif
{  x.swap(y);  }


   treap_set( const value_compare &cmp    = value_compare()
           , const priority_compare &pcmp = priority_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}


   treap_set(BOOST_RV_REF(treap_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   treap_set& operator=(BOOST_RV_REF(treap_set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static treap_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap_set &>(Base::container_from_end_iterator(end_iterator));   }


   static const treap_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap_set &>(Base::container_from_end_iterator(end_iterator));   }


   static treap_set &container_from_iterator(iterator it)
   {  return static_cast<treap_set &>(Base::container_from_iterator(it));   }


   static const treap_set &container_from_iterator(const_iterator it)
   {  return static_cast<const treap_set &>(Base::container_from_iterator(it));   }

   explicit treap_multiset_impl( const value_compare &cmp     = value_compare()
                               , const priority_compare &pcmp = priority_compare()
                               , const value_traits &v_traits = value_traits())
      :  tree_(cmp, pcmp, v_traits)
   {}

   template<class Iterator>
   treap_multiset_impl( Iterator b, Iterator e
                , const value_compare &cmp     = value_compare()
                , const priority_compare &pcmp = priority_compare()
                , const value_traits &v_traits = value_traits())
      : tree_(false, b, e, cmp, pcmp, v_traits)
   {}

   treap_multiset_impl(BOOST_RV_REF(treap_multiset_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   treap_multiset_impl& operator=(BOOST_RV_REF(treap_multiset_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~treap_multiset_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   iterator top()
   { return tree_.top();  }

   const_iterator top() const
   {  return this->ctop();   }

   const_iterator ctop() const
   { return tree_.ctop();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   reverse_iterator rtop()
   {  return tree_.rtop();  }

   const_reverse_iterator rtop() const
   {  return tree_.crtop();  }

   const_reverse_iterator crtop() const
   {  return tree_.crtop();  }

   static treap_multiset_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<treap_multiset_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &treap_multiset_impl::tree_);
   }

   static treap_multiset_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<treap_multiset_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &treap_multiset_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   priority_compare priority_comp() const
   {  return tree_.priority_comp();   }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(treap_multiset_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const treap_multiset_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

   iterator insert(reference value)
   {  return tree_.insert_equal(value);  }

   iterator insert(const_iterator hint, reference value)
   {  return tree_.insert_equal(hint, value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_.insert_equal(b, e);  }

   iterator insert_before(const_iterator pos, reference value)
   {  return tree_.insert_before(pos, value);  }

   void push_back(reference value)
   {  tree_.push_back(value);  }

   void push_front(reference value)
   {  tree_.push_front(value);  }

   iterator erase(const_iterator i)
   {  return tree_.erase(i);  }

   iterator erase(const_iterator b, const_iterator e)
   {  return tree_.erase(b, e);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return tree_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  return tree_.erase_and_dispose(b, e, disposer);  }

   void clear()
   {  return tree_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return tree_.clear_and_dispose(disposer);  }

   size_type count(const_reference value) const
   {  return tree_.count(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.count(key, comp);  }

   iterator lower_bound(const_reference value)
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator lower_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.lower_bound(key, comp);  }

   const_iterator lower_bound(const_reference value) const
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator lower_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.lower_bound(key, comp);  }

   iterator upper_bound(const_reference value)
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator upper_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.upper_bound(key, comp);  }

   const_iterator upper_bound(const_reference value) const
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator upper_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.upper_bound(key, comp);  }

   iterator find(const_reference value)
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator find(const KeyType& key, KeyValueCompare comp)
   {  return tree_.find(key, comp);  }

   const_iterator find(const_reference value) const
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator find(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.find(key, comp);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_multiset_impl<T, Options...> &x, const treap_multiset_impl<T, Options...> &y)
#else
(const treap_multiset_impl<Config> &x, const treap_multiset_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_multiset_impl<T, Options...> &x, const treap_multiset_impl<T, Options...> &y)
#else
(const treap_multiset_impl<Config> &x, const treap_multiset_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_multiset_impl<T, Options...> &x, const treap_multiset_impl<T, Options...> &y)
#else
(const treap_multiset_impl<Config> &x, const treap_multiset_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_multiset_impl<T, Options...> &x, const treap_multiset_impl<T, Options...> &y)
#else
(const treap_multiset_impl<Config> &x, const treap_multiset_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(treap_multiset_impl<T, Options...> &x, treap_multiset_impl<T, Options...> &y)
#else
(treap_multiset_impl<Config> &x, treap_multiset_impl<Config> &y)
#endif
{  x.swap(y);  }


   treap_multiset( const value_compare &cmp = value_compare()
                , const priority_compare &pcmp = priority_compare()
                , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}


   treap_multiset(BOOST_RV_REF(treap_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   treap_multiset& operator=(BOOST_RV_REF(treap_multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static treap_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static const treap_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static treap_multiset &container_from_iterator(iterator it)
   {  return static_cast<treap_multiset &>(Base::container_from_iterator(it));   }


   static const treap_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const treap_multiset &>(Base::container_from_iterator(it));   }

   static void init_header(const node_ptr & this_node)
   {  NodeTraits::set_next(this_node, node_ptr ());  }

   static node_ptr get_previous_node(const node_ptr & prev_init_node, const node_ptr & this_node)
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   static std::size_t count(const const_node_ptr & this_node)
   {
      std::size_t result = 0;
      const_node_ptr p = this_node;
      do{
         p = NodeTraits::get_next(p);
         ++result;
      } while (p);
      return result;
   }

   static void swap_trailing_nodes(const node_ptr & this_node, const node_ptr & other_node)
   {
      node_ptr this_nxt    = NodeTraits::get_next(this_node);
      node_ptr other_nxt   = NodeTraits::get_next(other_node);
      NodeTraits::set_next(this_node, other_nxt);
      NodeTraits::set_next(other_node, this_nxt);
   }

   static node_ptr reverse(const node_ptr & p)
   {
      if(!p) return node_ptr();
      node_ptr i = NodeTraits::get_next(p);
      node_ptr first(p);
      while(i){
         node_ptr nxti(NodeTraits::get_next(i));
         base_t::unlink_after(p);
         NodeTraits::set_next(i, first);
         first = i;
         i = nxti;
      }
      return first;
   }

      node_plus_pred_t(const value_compare &comp)
         :  detail::ebo_functor_holder<value_compare>(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}


   const value_compare &priv_comp() const
   {  return data_.node_plus_pred_.get();  }


   value_compare &priv_comp()
   {  return data_.node_plus_pred_.get();  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }


   node_ptr priv_header_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_size_.header_);  }


   const_node_ptr priv_header_ptr() const
   {  return pointer_traits<const_node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_size_.header_);  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   size_traits &priv_size_traits()
   {  return data_.node_plus_pred_.header_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }

   value_compare &prot_comp()
   {  return priv_comp(); }


   const node &prot_header_node() const
   {  return data_.node_plus_pred_.header_plus_size_.header_; }


   node &prot_header_node()
   {  return data_.node_plus_pred_.header_plus_size_.header_; }


   void prot_set_size(size_type s)
   {  this->priv_size_traits().set_size(s);  }

   explicit rbtree_impl( const value_compare &cmp = value_compare()
                       , const value_traits &v_traits = value_traits())
      :  data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
   }

   template<class Iterator>
   rbtree_impl( bool unique, Iterator b, Iterator e
              , const value_compare &cmp     = value_compare()
              , const value_traits &v_traits = value_traits())
      : data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   rbtree_impl(BOOST_RV_REF(rbtree_impl) x)
      : data_(::boost::move(x.priv_comp()), ::boost::move(x.priv_value_traits()))
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      this->swap(x);
   }

   rbtree_impl& operator=(BOOST_RV_REF(rbtree_impl) x)
   {  this->swap(x); return *this;  }

   ~rbtree_impl()
   {}

   iterator begin()
   {  return iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   const_iterator cbegin() const
   {  return const_iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   iterator end()
   {  return iterator (this->priv_header_ptr(), this);  }

   const_iterator cend() const
   {  return const_iterator (uncast(this->priv_header_ptr()), this);  }

   reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(end());  }

   reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   const_reverse_iterator crend() const
   {  return const_reverse_iterator(begin());   }

   static rbtree_impl &container_from_end_iterator(iterator end_iterator)
   {  return priv_container_from_end_iterator(end_iterator);   }

   static rbtree_impl &container_from_iterator(iterator it)
   {  return priv_container_from_iterator(it);   }

   value_compare value_comp() const
   {  return priv_comp();   }

   bool empty() const
   {  return node_algorithms::unique(this->priv_header_ptr());   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else{
         return (size_type)node_algorithms::size(this->priv_header_ptr());
      }
   }

   void swap(rbtree_impl& other)
   {
      //This can throw
      using std::swap;
      swap(priv_comp(), priv_comp());
      //These can't throw
      node_algorithms::swap_tree(this->priv_header_ptr(), node_ptr(other.priv_header_ptr()));
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   iterator insert_equal(reference value)
   {
      detail::key_nodeptr_comp<value_compare, rbtree_impl>
         key_node_comp(priv_comp(), this);
      node_ptr to_insert(get_real_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      iterator ret(node_algorithms::insert_equal_upper_bound
         (this->priv_header_ptr(), to_insert, key_node_comp), this);
      this->priv_size_traits().increment();
      return ret;
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{
   typedef rbtree_impl<Config> tree_type;
   typedef typename tree_type::const_iterator const_iterator;

   if(tree_type::constant_time_size && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();
   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(tree_type::constant_time_size){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const rbtree_impl<T, Options...> &x, const rbtree_impl<T, Options...> &y)
#else
(const rbtree_impl<Config> &x, const rbtree_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(rbtree_impl<T, Options...> &x, rbtree_impl<T, Options...> &y)
#else
(rbtree_impl<Config> &x, rbtree_impl<Config> &y)
#endif
{  x.swap(y);  }


   rbtree( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   rbtree(BOOST_RV_REF(rbtree) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   rbtree& operator=(BOOST_RV_REF(rbtree) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static rbtree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<rbtree &>(Base::container_from_end_iterator(end_iterator));   }


   static const rbtree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const rbtree &>(Base::container_from_end_iterator(end_iterator));   }


   static rbtree &container_from_it(iterator it)
   {  return static_cast<rbtree &>(Base::container_from_iterator(it));   }


   static const rbtree &container_from_it(const_iterator it)
   {  return static_cast<const rbtree &>(Base::container_from_iterator(it));   }

   static void init_header(const node_ptr &this_node)
   {  NodeTraits::set_next(this_node, this_node);  }

   static node_ptr get_previous_node(const node_ptr &prev_init_node, const node_ptr &this_node)
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   static node_ptr get_previous_node(const node_ptr & this_node)
   {  return base_t::get_previous_node(this_node, this_node); }

   static node_ptr get_previous_previous_node(const node_ptr & this_node)
   {  return get_previous_previous_node(this_node, this_node); }

   static node_ptr get_previous_previous_node(node_ptr p, const node_ptr & this_node)
   {
      node_ptr p_next = NodeTraits::get_next(p);
      node_ptr p_next_next = NodeTraits::get_next(p_next);
      while (this_node != p_next_next){
         p = p_next;
         p_next = p_next_next;
         p_next_next = NodeTraits::get_next(p_next);
      }
      return p;
   }

   static std::size_t count(const const_node_ptr & this_node)
   {
      std::size_t result = 0;
      const_node_ptr p = this_node;
      do{
         p = NodeTraits::get_next(p);
         ++result;
      } while (p != this_node);
      return result;
   }

   static void unlink(const node_ptr & this_node)
   {
      if(NodeTraits::get_next(this_node))
         base_t::unlink_after(get_previous_node(this_node));
   }

   static void link_before (const node_ptr & nxt_node, const node_ptr & this_node)
   {  base_t::link_after(get_previous_node(nxt_node), this_node);   }

   static void swap_nodes(const node_ptr & this_node, const node_ptr & other_node)
   {
      if (other_node == this_node)
         return;
      bool this_inited  = base_t::inited(this_node);
      bool other_inited = base_t::inited(other_node);
      if(this_inited){
         base_t::init_header(this_node);
      }
      if(other_inited){
         base_t::init_header(other_node);
      }

      bool empty1 = base_t::unique(this_node);
      bool empty2 = base_t::unique(other_node);
      node_ptr prev_this (get_previous_node(this_node));
      node_ptr prev_other(get_previous_node(other_node));

      node_ptr this_next (NodeTraits::get_next(this_node));
      node_ptr other_next(NodeTraits::get_next(other_node));
      NodeTraits::set_next(this_node, other_next);
      NodeTraits::set_next(other_node, this_next);
      NodeTraits::set_next(empty1 ? other_node : prev_this, other_node);
      NodeTraits::set_next(empty2 ? this_node  : prev_other, this_node);

      if(this_inited){
         base_t::init(other_node);
      }
      if(other_inited){
         base_t::init(this_node);
      }
   }

   static void reverse(const node_ptr & p)
   {
      node_ptr i = NodeTraits::get_next(p), e(p);
      for (;;) {
         node_ptr nxt(NodeTraits::get_next(i));
         if (nxt == e)
            break;
         base_t::transfer_after(e, i, nxt);
      }
   }

   static node_ptr move_backwards(const node_ptr & p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n) return node_ptr();
      node_ptr first  = NodeTraits::get_next(p);

      //count() == 1 or 2, nothing to do
      if(NodeTraits::get_next(first) == p)
         return node_ptr();

      bool end_found = false;
      node_ptr new_last = node_ptr();

      //Now find the new last node according to the shift count.
      //If we find p before finding the new last node
      //unlink p, shortcut the search now that we know the size of the list
      //and continue.
      for(std::size_t i = 1; i <= n; ++i){
         new_last = first;
         first = NodeTraits::get_next(first);
         if(first == p){
            //Shortcut the shift with the modulo of the size of the list
            n %= i;
            if(!n)
               return node_ptr();
            i = 0;
            //Unlink p and continue the new first node search
            first = NodeTraits::get_next(p);
            base_t::unlink_after(new_last);
            end_found = true;
         }
      }

      //If the p has not been found in the previous loop, find it
      //starting in the new first node and unlink it
      if(!end_found){
         base_t::unlink_after(base_t::get_previous_node(first, p));
      }

      //Now link p after the new last node
      base_t::link_after(new_last, p);
      return new_last;
   }

   static node_ptr move_forward(const node_ptr & p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n) return node_ptr();
      node_ptr first  = node_traits::get_next(p);

      //count() == 1 or 2, nothing to do
      if(node_traits::get_next(first) == p) return node_ptr();

      //Iterate until p is found to know where the current last node is.
      //If the shift count is less than the size of the list, we can also obtain
      //the position of the new last node after the shift.
      node_ptr old_last(first), next_to_it, new_last(p);
      std::size_t distance = 1;
      while(p != (next_to_it = node_traits::get_next(old_last))){
         if(++distance > n)
            new_last = node_traits::get_next(new_last);
         old_last = next_to_it;
      }
      //If the shift was bigger or equal than the size, obtain the equivalent
      //forward shifts and find the new last node.
      if(distance <= n){
         //Now find the equivalent forward shifts.
         //Shortcut the shift with the modulo of the size of the list
         std::size_t new_before_last_pos = (distance - (n % distance))% distance;
         //If the shift is a multiple of the size there is nothing to do
         if(!new_before_last_pos)   return node_ptr();

         for( new_last = p
            ; new_before_last_pos--
            ; new_last = node_traits::get_next(new_last)){
            //empty
         }
      }

      //Now unlink p and link it after the new last node
      base_t::unlink_after(old_last);
      base_t::link_after(new_last, p);
      return new_last;
   }

   explicit unordered_set_impl( const bucket_traits &b_traits
                              , const hasher & hash_func = hasher()
                              , const key_equal &equal_func = key_equal()
                              , const value_traits &v_traits = value_traits())
      :  table_(b_traits, hash_func, equal_func, v_traits)
   {}

   template<class Iterator>
   unordered_set_impl( Iterator b
                     , Iterator e
                     , const bucket_traits &b_traits
                     , const hasher & hash_func = hasher()
                     , const key_equal &equal_func = key_equal()
                     , const value_traits &v_traits = value_traits())
      :  table_(b_traits, hash_func, equal_func, v_traits)
   {  table_.insert_unique(b, e);  }

   unordered_set_impl(BOOST_RV_REF(unordered_set_impl) x)
      :  table_(::boost::move(x.table_))
   {}

   unordered_set_impl& operator=(BOOST_RV_REF(unordered_set_impl) x)
   {  table_ = ::boost::move(x.table_);  return *this;  }

   ~unordered_set_impl()
   {}

   iterator begin()
   { return table_.begin();  }

   const_iterator begin() const
   { return table_.begin();  }

   const_iterator cbegin() const
   { return table_.cbegin();  }

   iterator end()
   { return table_.end();  }

   const_iterator end() const
   { return table_.end();  }

   const_iterator cend() const
   { return table_.cend();  }

   hasher hash_function() const
   { return table_.hash_function(); }

   key_equal key_eq() const
   { return table_.key_eq(); }

   bool empty() const
   { return table_.empty(); }

   size_type size() const
   { return table_.size(); }

   void swap(unordered_set_impl& other)
   { table_.swap(other.table_); }

   template <class Cloner, class Disposer>
   void clone_from(const unordered_set_impl &src, Cloner cloner, Disposer disposer)
   {  table_.clone_from(src.table_, cloner, disposer);  }


   unordered_set  ( const bucket_traits &b_traits
                  , const hasher & hash_func = hasher()
                  , const key_equal &equal_func = key_equal()
                  , const value_traits &v_traits = value_traits())
      :  Base(b_traits, hash_func, equal_func, v_traits)
   {}


   unordered_set(BOOST_RV_REF(unordered_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   unordered_set& operator=(BOOST_RV_REF(unordered_set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }

   explicit unordered_multiset_impl ( const bucket_traits &b_traits
                                    , const hasher & hash_func = hasher()
                                    , const key_equal &equal_func = key_equal()
                                    , const value_traits &v_traits = value_traits())
      :  table_(b_traits, hash_func, equal_func, v_traits)
   {}

   template<class Iterator>
   unordered_multiset_impl ( Iterator b
                           , Iterator e
                           , const bucket_traits &b_traits
                           , const hasher & hash_func = hasher()
                           , const key_equal &equal_func = key_equal()
                           , const value_traits &v_traits = value_traits())
      :  table_(b_traits, hash_func, equal_func, v_traits)
   {  table_.insert_equal(b, e);  }

   unordered_multiset_impl(BOOST_RV_REF(unordered_multiset_impl) x)
      :  table_(::boost::move(x.table_))
   {}

   unordered_multiset_impl& operator=(BOOST_RV_REF(unordered_multiset_impl) x)
   {  table_ = ::boost::move(x.table_);  return *this;  }

   ~unordered_multiset_impl()
   {}

   iterator begin()
   { return table_.begin();  }

   const_iterator begin() const
   { return table_.begin();  }

   const_iterator cbegin() const
   { return table_.cbegin();  }

   iterator end()
   { return table_.end();  }

   const_iterator end() const
   { return table_.end();  }

   const_iterator cend() const
   { return table_.cend();  }

   hasher hash_function() const
   { return table_.hash_function(); }

   key_equal key_eq() const
   { return table_.key_eq(); }

   bool empty() const
   { return table_.empty(); }

   size_type size() const
   { return table_.size(); }

   void swap(unordered_multiset_impl& other)
   { table_.swap(other.table_); }

   template <class Cloner, class Disposer>
   void clone_from(const unordered_multiset_impl &src, Cloner cloner, Disposer disposer)
   {  table_.clone_from(src.table_, cloner, disposer);  }

   iterator insert(reference value)
   {  return table_.insert_equal(value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  table_.insert_equal(b, e);  }

   void erase(const_iterator i)
   {  table_.erase(i);  }

   void erase(const_iterator b, const_iterator e)
   {  table_.erase(b, e);  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type erase(const KeyType& key, KeyHasher hash_func, KeyValueEqual equal_func)
   {  return table_.erase(key, hash_func, equal_func);  }

   template<class Disposer>
   void erase_and_dispose(const_iterator i, Disposer disposer
                              /// @cond
                              , typename detail::enable_if_c<!detail::is_convertible<Disposer, const_iterator>::value >::type * = 0
                              /// @endcond
                              )
   {  table_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   void erase_and_dispose(const_iterator i, Disposer disposer)
   {  this->erase_and_dispose(const_iterator(i), disposer);   }

   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  table_.erase_and_dispose(b, e, disposer);  }

   template<class Disposer>
   size_type erase_and_dispose(const_reference value, Disposer disposer)
   {  return table_.erase_and_dispose(value, disposer);  }

   template<class KeyType, class KeyHasher, class KeyValueEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hash_func, KeyValueEqual equal_func, Disposer disposer)
   {  return table_.erase_and_dispose(key, hash_func, equal_func, disposer);  }

   void clear()
   {  return table_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return table_.clear_and_dispose(disposer);  }

   size_type count(const_reference value) const
   {  return table_.count(value);  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type count(const KeyType& key, KeyHasher hash_func, KeyValueEqual equal_func) const
   {  return table_.count(key, hash_func, equal_func);  }

   iterator find(const_reference value)
   {  return table_.find(value);  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   iterator find(const KeyType& key, KeyHasher hash_func, KeyValueEqual equal_func)
   {  return table_.find(key, hash_func, equal_func);  }

   const_iterator find(const_reference value) const
   {  return table_.find(value);  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   const_iterator find(const KeyType& key, KeyHasher hash_func, KeyValueEqual equal_func) const
   {  return table_.find(key, hash_func, equal_func);  }


   unordered_multiset( const bucket_traits &b_traits
                     , const hasher & hash_func = hasher()
                     , const key_equal &equal_func = key_equal()
                     , const value_traits &v_traits = value_traits())
      :  Base(b_traits, hash_func, equal_func, v_traits)
   {}


   unordered_multiset(BOOST_RV_REF(unordered_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   unordered_multiset& operator=(BOOST_RV_REF(unordered_multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


      rbtree_node_cloner(F f)
         :  base_t(f)
      {}


      node_ptr operator()(const node_ptr & p)
      {
         node_ptr n = base_t::get()(p);
         NodeTraits::set_color(n, NodeTraits::get_color(p));
         return n;
      }

      void operator()(const node_ptr & to_erase, const node_ptr & successor)
      {
         //Swap color of y and z
         color tmp(NodeTraits::get_color(successor));
         NodeTraits::set_color(successor, NodeTraits::get_color(to_erase));
         NodeTraits::set_color(to_erase, tmp);
      }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return tree_algorithms::begin_node(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return tree_algorithms::end_node(header);   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {  return tree_algorithms::swap_tree(header1, header2);  }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(tree_algorithms::get_header(node1)), header2(tree_algorithms::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {
      if(node1 == node2)   return;

      tree_algorithms::swap_nodes(node1, header1, node2, header2);
      //Swap color
      color c = NodeTraits::get_color(node1);
      NodeTraits::set_color(node1, NodeTraits::get_color(node2));
      NodeTraits::set_color(node2, c);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, tree_algorithms::get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {
      tree_algorithms::replace_node(node_to_be_replaced, header, new_node);
      NodeTraits::set_color(new_node, NodeTraits::get_color(node_to_be_replaced));
   }

   static void unlink(const node_ptr & node)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node);
      }
   }

   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header)
   {  return tree_algorithms::unlink_leftmost_without_rebalance(header);   }

   static bool unique(const const_node_ptr & node)
   {  return tree_algorithms::unique(node);  }

   static std::size_t count(const const_node_ptr & node)
   {  return tree_algorithms::count(node);   }

   static std::size_t size(const const_node_ptr & header)
   {  return tree_algorithms::size(header);   }

   static node_ptr next_node(const node_ptr & p)
   {  return tree_algorithms::next_node(p); }

   static node_ptr prev_node(const node_ptr & p)
   {  return tree_algorithms::prev_node(p); }

   static void init(const node_ptr & node)
   {  tree_algorithms::init(node);  }

   static void init_header(const node_ptr & header)
   {
      tree_algorithms::init_header(header);
      NodeTraits::set_color(header, NodeTraits::red());
   }

   static node_ptr erase(const node_ptr & header, const node_ptr & z)
   {
      typename tree_algorithms::data_for_rebalance info;
      tree_algorithms::erase(header, z, rbtree_erase_fixup(), info);
      node_ptr x = info.x;
      node_ptr x_parent = info.x_parent;

      //Rebalance rbtree
      if(NodeTraits::get_color(z) != NodeTraits::red()){
         rebalance_after_erasure(header, x, x_parent);
      }
      return z;
   }

   template <class Cloner, class Disposer>
   static void clone
      (const const_node_ptr & source_header, const node_ptr & target_header, Cloner cloner, Disposer disposer)
   {
      rbtree_node_cloner<Cloner> new_cloner(cloner);
      tree_algorithms::clone(source_header, target_header, new_cloner, disposer);
   }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {  tree_algorithms::clear_and_dispose(header, disposer); }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::lower_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::upper_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::find(header, key, comp);  }

   static void init(const node_ptr &this_node)
   {
      NodeTraits::set_next(this_node, node_ptr());
      NodeTraits::set_previous(this_node, node_ptr());
   }

   static bool inited(const const_node_ptr &this_node)
   {  return !NodeTraits::get_next(this_node); }

   static void init_header(const node_ptr &this_node)
   {
      NodeTraits::set_next(this_node, this_node);
      NodeTraits::set_previous(this_node, this_node);
   }

   static bool unique(const const_node_ptr &this_node)
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }

   static std::size_t count(const const_node_ptr &this_node)
   {
      std::size_t result = 0;
      const_node_ptr p = this_node;
      do{
         p = NodeTraits::get_next(p);
         ++result;
      }while (p != this_node);
      return result;
   }

   static node_ptr unlink(const node_ptr &this_node)
   {
      node_ptr next(NodeTraits::get_next(this_node));
      if(next){
         node_ptr prev(NodeTraits::get_previous(this_node));
         NodeTraits::set_next(prev, next);
         NodeTraits::set_previous(next, prev);
         return next;
      }
      else{
         return this_node;
      }
   }

   static void unlink(const node_ptr &b, const node_ptr &e)
   {
      if (b != e) {
         node_ptr prevb(NodeTraits::get_previous(b));
         NodeTraits::set_previous(e, prevb);
         NodeTraits::set_next(prevb, e);
      }
   }

   static void link_before(const node_ptr &nxt_node, const node_ptr &this_node)
   {
      node_ptr prev(NodeTraits::get_previous(nxt_node));
      NodeTraits::set_previous(this_node, prev);
      NodeTraits::set_next(this_node, nxt_node);
      //nxt_node might be an alias for prev->next_
      //so use it before NodeTraits::set_next(prev, ...)
      //is called and the reference changes it's value
      NodeTraits::set_previous(nxt_node, this_node);
      NodeTraits::set_next(prev, this_node);
   }

   static void link_after(const node_ptr &prev_node, const node_ptr &this_node)
   {
      node_ptr next(NodeTraits::get_next(prev_node));
      NodeTraits::set_previous(this_node, prev_node);
      NodeTraits::set_next(this_node, next);
      //prev_node might be an alias for next->next_
      //so use it before update it before NodeTraits::set_previous(next, ...)
      //is called and the reference changes it's value
      NodeTraits::set_next(prev_node, this_node);
      NodeTraits::set_previous(next, this_node);
   }

   static void swap_prev(const node_ptr &this_node, const node_ptr &other_node)
   {
      node_ptr temp(NodeTraits::get_previous(this_node));
      NodeTraits::set_previous(this_node, NodeTraits::get_previous(other_node));
      NodeTraits::set_previous(other_node, temp);
   }

   static void swap_next(const node_ptr &this_node, const node_ptr &other_node)
   {
      node_ptr temp(NodeTraits::get_next(this_node));
      NodeTraits::set_next(this_node, NodeTraits::get_next(other_node));
      NodeTraits::set_next(other_node, temp);
   }

   static void swap_nodes(const node_ptr &this_node, const node_ptr &other_node)
   {
      if (other_node == this_node)
         return;
      bool this_inited  = inited(this_node);
      bool other_inited = inited(other_node);
      if(this_inited){
         init_header(this_node);
      }
      if(other_inited){
         init_header(other_node);
      }

      node_ptr next_this(NodeTraits::get_next(this_node));
      node_ptr prev_this(NodeTraits::get_previous(this_node));
      node_ptr next_other(NodeTraits::get_next(other_node));
      node_ptr prev_other(NodeTraits::get_previous(other_node));
      //these first two swaps must happen before the other two
      swap_prev(next_this, next_other);
      swap_next(prev_this, prev_other);
      swap_next(this_node, other_node);
      swap_prev(this_node, other_node);

      if(this_inited){
         init(other_node);
      }
      if(other_inited){
         init(this_node);
      }
   }

   static void transfer(const node_ptr &p, const node_ptr &b, const node_ptr &e)
   {
      if (b != e) {
         node_ptr prev_p(NodeTraits::get_previous(p));
         node_ptr prev_b(NodeTraits::get_previous(b));
         node_ptr prev_e(NodeTraits::get_previous(e));
         NodeTraits::set_next(prev_e, p);
         NodeTraits::set_previous(p, prev_e);
         NodeTraits::set_next(prev_b, e);
         NodeTraits::set_previous(e, prev_b);
         NodeTraits::set_next(prev_p, b);
         NodeTraits::set_previous(b, prev_p);
      }
   }

   static void transfer(const node_ptr &p, const node_ptr &i)
   {
      node_ptr n(NodeTraits::get_next(i));
      if(n != p && i != p){
         node_ptr prev_p(NodeTraits::get_previous(p));
         node_ptr prev_i(NodeTraits::get_previous(i));
         NodeTraits::set_next(prev_p, i);
         NodeTraits::set_previous(i, prev_p);
         NodeTraits::set_next(i, p);
         NodeTraits::set_previous(p, i);
         NodeTraits::set_previous(n, prev_i);
         NodeTraits::set_next(prev_i, n);

      }
   }

   static void reverse(const node_ptr &p)
   {
      node_ptr f(NodeTraits::get_next(p));
      node_ptr i(NodeTraits::get_next(f)), e(p);

      while(i != e) {
         node_ptr n = i;
         i = NodeTraits::get_next(i);
         transfer(f, n, i);
         f = n;
      }
   }

   static void move_backwards(const node_ptr &p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n) return;
      node_ptr first  = NodeTraits::get_next(p);
      //size() == 0 or 1, nothing to do
      if(first == NodeTraits::get_previous(p)) return;
      unlink(p);
      //Now get the new first node
      while(n--){
         first = NodeTraits::get_next(first);
      }
      link_before(first, p);
   }

   static void move_forward(const node_ptr &p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n)   return;
      node_ptr last  = NodeTraits::get_previous(p);
      //size() == 0 or 1, nothing to do
      if(last == NodeTraits::get_next(p))   return;

      unlink(p);
      //Now get the new last node
      while(n--){
         last = NodeTraits::get_previous(last);
      }
      link_after(last, p);
   }


   template<class BucketTraits>
   bucket_plus_size(BOOST_FWD_REF(BucketTraits) b_traits)
      :  bucket_traits_(::boost::forward<BucketTraits>(b_traits))
   {}


   bucket_plus_size & operator =(const bucket_plus_size &x)
   {
      this->size_traits::operator=(x);
      bucket_traits_ = x.bucket_traits_;
      return *this;
   }


   template<class BucketTraits>
   bucket_hash_t(BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h)
      :  detail::ebo_functor_holder<hasher>(h), bucket_plus_size_(::boost::forward<BucketTraits>(b_traits))
   {}


   template<class BucketTraits>
   bucket_hash_equal_t(BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h, const equal &e)
      : detail::ebo_functor_holder<typename Config::equal>(e)//equal()
      , bucket_hash(::boost::forward<BucketTraits>(b_traits), h)
   {}


   template<class T>
   void set_cache(T)
   {}


   template<class BucketTraits>
   bucket_hash_equal_t(BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h, const equal &e)
      : detail::ebo_functor_holder<typename Config::equal>(e) //equal()
      , bucket_hash(::boost::forward<BucketTraits>(b_traits), h)
   {}


   void set_cache(const bucket_ptr & c)
   {  cached_begin_ = c;   }


   template<class BucketTraits>
   hashtable_data_t( BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h
                   , const equal &e, const value_traits &val_traits)
      :  Config::value_traits(val_traits) //value_traits
      , internal_(::boost::forward<BucketTraits>(b_traits), h, e)
   {}

      template<class BucketTraits>
      internal(BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h, const equal &e)
         :  bucket_hash_equal_(::boost::forward<BucketTraits>(b_traits), h, e)
      {}

      template<class BucketTraits>
      internal(BOOST_FWD_REF(BucketTraits) b_traits, const hasher & h, const equal &e)
         :  bucket_hash_equal_(::boost::forward<BucketTraits>(b_traits), h, e)
      {}


   static node_ptr dcast_bucket_ptr(const slist_node_ptr &p)
   {  return pointer_traits<node_ptr>::pointer_to(static_cast<node&>(*p));  }


   static slist_node_ptr get_bucket_before_begin
      (const slist_node_ptr &bucket_beg, const slist_node_ptr &bucket_end, const node_ptr &p)
   {
      //First find the last node of p's group.
      //This requires checking the first node of the next group or
      //the bucket node.
      node_ptr prev_node = p;
      node_ptr nxt(node_traits::get_next(p));
      while(!(bucket_beg <= nxt && nxt <= bucket_end) &&
             (group_traits::get_next(nxt) == prev_node)){
         prev_node = nxt;
         nxt = node_traits::get_next(nxt);
      }

      //If we've reached the bucket node just return it.
      if(bucket_beg <= nxt && nxt <= bucket_end){
         return nxt;
      }

      //Otherwise, iterate using group links until the bucket node
      node_ptr first_node_of_group  = nxt;
      node_ptr last_node_group      = group_traits::get_next(first_node_of_group);
      slist_node_ptr possible_end   = node_traits::get_next(last_node_group);

      while(!(bucket_beg <= possible_end && possible_end <= bucket_end)){
         first_node_of_group = group_functions::dcast_bucket_ptr(possible_end);
         last_node_group   = group_traits::get_next(first_node_of_group);
         possible_end      = node_traits::get_next(last_node_group);
      }
      return possible_end;
   }


   static node_ptr get_prev_to_first_in_group(const slist_node_ptr &bucket_node, const node_ptr &first_in_group)
   {
      //Just iterate using group links and obtain the node
      //before "first_in_group)"
      node_ptr prev_node = group_functions::dcast_bucket_ptr(bucket_node);
      node_ptr nxt(node_traits::get_next(prev_node));
      while(nxt != first_in_group){
         prev_node = group_traits::get_next(nxt);
         nxt = node_traits::get_next(prev_node);
      }
      return prev_node;
   }


   static node_ptr get_first_in_group_of_last_in_group(const node_ptr &last_in_group)
   {
      //Just iterate using group links and obtain the node
      //before "last_in_group"
      node_ptr possible_first = group_traits::get_next(last_in_group);
      node_ptr possible_first_prev = group_traits::get_next(possible_first);
      // The deleted node is at the end of the group, so the
      // node in the group pointing to it is at the beginning
      // of the group. Find that to change its pointer.
      while(possible_first_prev != last_in_group){
         possible_first = possible_first_prev;
         possible_first_prev = group_traits::get_next(possible_first);
      }
      return possible_first;
   }


   static void erase_from_group(const slist_node_ptr &end_ptr, const node_ptr &to_erase_ptr, detail::true_)
   {
      node_ptr nxt_ptr(node_traits::get_next(to_erase_ptr));
      node_ptr prev_in_group_ptr(group_traits::get_next(to_erase_ptr));
      bool last_in_group = (end_ptr == nxt_ptr) ||
         (group_traits::get_next(nxt_ptr) != to_erase_ptr);
      bool is_first_in_group = node_traits::get_next(prev_in_group_ptr) != to_erase_ptr;

      if(is_first_in_group && last_in_group){
         group_algorithms::init(to_erase_ptr);
      }
      else if(is_first_in_group){
         group_algorithms::unlink_after(nxt_ptr);
      }
      else if(last_in_group){
         node_ptr first_in_group =
            get_first_in_group_of_last_in_group(to_erase_ptr);
         group_algorithms::unlink_after(first_in_group);
      }
      else{
         group_algorithms::unlink_after(nxt_ptr);
      }
   }


   static node_ptr get_last_in_group(const node_ptr &first_in_group, detail::true_)
   {  return group_traits::get_next(first_in_group);  }


   static void init_group(const node_ptr &n, true_)
   {  group_algorithms::init(n); }


   static void insert_in_group(const node_ptr &first_in_group, const node_ptr &n, true_)
   {
      if(first_in_group){
         if(group_algorithms::unique(first_in_group))
            group_algorithms::link_after(first_in_group, n);
         else{
            group_algorithms::link_after(group_algorithms::node_traits::get_next(first_in_group), n);
         }
      }
      else{
         group_algorithms::init_header(n);
      }
   }


   static slist_node_ptr get_previous_and_next_in_group
      ( const slist_node_ptr &i, node_ptr &nxt_in_group
      //If first_end_ptr == last_end_ptr, then first_end_ptr is the bucket of i
      //Otherwise first_end_ptr is the first bucket and last_end_ptr the last one.
      , const slist_node_ptr &first_end_ptr, const slist_node_ptr &last_end_ptr)
   {
      slist_node_ptr prev;
      node_ptr elem(group_functions::dcast_bucket_ptr(i));

      //It's the last in group if the next_node is a bucket
      slist_node_ptr nxt(node_traits::get_next(elem));
      bool last_in_group = (first_end_ptr <= nxt && nxt <= last_end_ptr)/* ||
                            (group_traits::get_next(nxt) != elem)*/;
      //It's the first in group if group_previous's next_node is not
      //itself, as group list does not link bucket
      node_ptr prev_in_group(group_traits::get_next(elem));
      bool first_in_group = node_traits::get_next(prev_in_group) != elem;

      if(first_in_group){
         node_ptr start_pos;
         if(last_in_group){
            start_pos = elem;
            nxt_in_group = node_ptr();
         }
         else{
            start_pos = prev_in_group;
            nxt_in_group = node_traits::get_next(elem);
         }
         slist_node_ptr bucket_node;
         if(first_end_ptr != last_end_ptr){
            bucket_node = group_functions::get_bucket_before_begin
                  (first_end_ptr, last_end_ptr, start_pos);
         }
         else{
            bucket_node = first_end_ptr;
         }
         prev = group_functions::get_prev_to_first_in_group(bucket_node, elem);
      }
      else{
         if(last_in_group){
            nxt_in_group = group_functions::get_first_in_group_of_last_in_group(elem);
         }
         else{
            nxt_in_group = node_traits::get_next(elem);
         }
         prev = group_traits::get_next(elem);
      }
      return prev;
   }

   incremental_rehash_rollback
      (bucket_type &source_bucket, bucket_type &destiny_bucket, split_traits &split_traits)
      :  source_bucket_(source_bucket),  destiny_bucket_(destiny_bucket)
      ,  split_traits_(split_traits),  released_(false)
   {}


   void release()
   {  released_ = true; }


   ~incremental_rehash_rollback()
   {
      if(!released_){
         //If an exception is thrown, just put all moved nodes back in the old bucket
         //and move back the split mark.
         destiny_bucket_.splice_after(destiny_bucket_.before_begin(), source_bucket_);
         split_traits_.decrement();
      }
   }

   static void store_hash(typename NodeTraits::node_ptr p, std::size_t h, true_)
   {  return NodeTraits::set_hash(p, h); }


      downcast_node_to_value(const hashtable_impl *cont)
         :  base_t(cont)
      {}


      result_type operator()(first_argument_type arg) const
      {  return this->base_t::operator()(static_cast<intermediate_argument_type>(arg)); }


      template<class ConvertibleToF>
      node_cast_adaptor(const ConvertibleToF &c2f, const hashtable_impl *cont)
         :  base_t(base_t(c2f, cont))
      {}


      typename base_t::node_ptr operator()(const typename slist_impl::node &to_clone)
      {  return base_t::operator()(static_cast<const node &>(to_clone));   }


      void operator()(typename slist_impl::node_ptr to_clone)
      {
         base_t::operator()(pointer_traits<node_ptr>::pointer_to(static_cast<node &>(*to_clone)));
      }


   const real_value_traits &get_real_value_traits(detail::false_) const
   {  return this->data_;  }

   explicit hashtable_impl ( const bucket_traits &b_traits
                           , const hasher & hash_func = hasher()
                           , const key_equal &equal_func = key_equal()
                           , const value_traits &v_traits = value_traits())
      :  data_(b_traits, hash_func, equal_func, v_traits)
   {
      this->priv_initialize_buckets();
      this->priv_size_traits().set_size(size_type(0));
      size_type bucket_sz = this->priv_bucket_count();
      BOOST_INTRUSIVE_INVARIANT_ASSERT(bucket_sz != 0);
      //Check power of two bucket array if the option is activated
      BOOST_INTRUSIVE_INVARIANT_ASSERT
         (!power_2_buckets || (0 == (bucket_sz & (bucket_sz-1))));
      this->priv_split_traits().set_size(bucket_sz>>1);
   }

   hashtable_impl(BOOST_RV_REF(hashtable_impl) x)
      : data_( ::boost::move(x.priv_bucket_traits())
             , ::boost::move(x.priv_hasher())
             , ::boost::move(x.priv_equal())
             , ::boost::move(x.priv_value_traits())
             )
   {
      this->priv_swap_cache(cache_begin_t(), x);
      x.priv_initialize_cache();
      if(constant_time_size){
         this->priv_size_traits().set_size(size_type(0));
         this->priv_size_traits().set_size(x.priv_size_traits().get_size());
         x.priv_size_traits().set_size(size_type(0));
      }
      if(incremental){
         this->priv_split_traits().set_size(x.priv_split_traits().get_size());
         x.priv_split_traits().set_size(size_type(0));
      }
   }

   hashtable_impl& operator=(BOOST_RV_REF(hashtable_impl) x)
   {  this->swap(x); return *this;  }

   ~hashtable_impl()
   {}

   iterator begin()
   {  return iterator(this->priv_begin(), this);   }

   const_iterator begin() const
   {  return this->cbegin();  }

   const_iterator cbegin() const
   {  return const_iterator(this->priv_begin(), this);   }

   iterator end()
   {  return iterator(this->priv_invalid_local_it(), 0);   }

   const_iterator end() const
   {  return this->cend(); }

   const_iterator cend() const
   {  return const_iterator(this->priv_invalid_local_it(), 0);  }

   hasher hash_function() const
   {  return this->priv_hasher();  }

   key_equal key_eq() const
   {  return this->priv_equal();   }

   bool empty() const
   {
      if(constant_time_size){
         return !this->size();
      }
      else if(cache_begin){
         return this->begin() == this->end();
      }
      else{
         size_type bucket_cnt = this->priv_bucket_count();
         const bucket_type *b = boost::intrusive::detail::to_raw_pointer(this->priv_bucket_pointer());
         for (size_type n = 0; n < bucket_cnt; ++n, ++b){
            if(!b->empty()){
               return false;
            }
         }
         return true;
      }
   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else{
         size_type len = 0;
         size_type bucket_cnt = this->priv_bucket_count();
         const bucket_type *b = boost::intrusive::detail::to_raw_pointer(this->priv_bucket_pointer());
         for (size_type n = 0; n < bucket_cnt; ++n, ++b){
            len += b->size();
         }
         return len;
      }
   }

   void swap(hashtable_impl& other)
   {
      using std::swap;
      //These can throw
      swap(this->priv_equal(), other.priv_equal());
      swap(this->priv_hasher(), other.priv_hasher());
      //These can't throw
      swap(this->priv_bucket_traits(), other.priv_bucket_traits());
      swap(this->priv_value_traits(), other.priv_value_traits());
      this->priv_swap_cache(cache_begin_t(), other);
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
      if(incremental){
         size_type backup = this->priv_split_traits().get_size();
         this->priv_split_traits().set_size(other.priv_split_traits().get_size());
         other.priv_split_traits().set_size(backup);
      }
   }

   template <class Cloner, class Disposer>
   void clone_from(const hashtable_impl &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      if(!constant_time_size || !src.empty()){
         const size_type src_bucket_count = src.bucket_count();
         const size_type dst_bucket_count = this->bucket_count();
         //Check power of two bucket array if the option is activated
         BOOST_INTRUSIVE_INVARIANT_ASSERT
         (!power_2_buckets || (0 == (src_bucket_count & (src_bucket_count-1))));
         BOOST_INTRUSIVE_INVARIANT_ASSERT
         (!power_2_buckets || (0 == (dst_bucket_count & (dst_bucket_count-1))));

         //If src bucket count is bigger or equal, structural copy is possible
         if(!incremental && (src_bucket_count >= dst_bucket_count)){
            //First clone the first ones
            const bucket_ptr src_buckets = src.priv_bucket_pointer();
            const bucket_ptr dst_buckets = this->priv_bucket_pointer();
            size_type constructed;
            typedef node_cast_adaptor<detail::node_disposer<Disposer, hashtable_impl> > NodeDisposer;
            typedef node_cast_adaptor<detail::node_cloner<Cloner, hashtable_impl> > NodeCloner;
            NodeDisposer node_disp(disposer, this);

            detail::exception_array_disposer<bucket_type, NodeDisposer, size_type>
               rollback(dst_buckets[0], node_disp, constructed);
            for( constructed = 0
               ; constructed < dst_bucket_count
               ; ++constructed){
               dst_buckets[constructed].clone_from
                  ( src_buckets[constructed]
                  , NodeCloner(cloner, this), node_disp);
            }
            if(src_bucket_count != dst_bucket_count){
               //Now insert the remaining ones using the modulo trick
               for(//"constructed" comes from the previous loop
                  ; constructed < src_bucket_count
                  ; ++constructed){
                  bucket_type &dst_b =
                     dst_buckets[this->priv_hash_to_bucket(constructed, dst_bucket_count, dst_bucket_count)];
                  bucket_type &src_b = src_buckets[constructed];
                  for( siterator b(src_b.begin()), e(src_b.end())
                     ; b != e
                     ; ++b){
                     dst_b.push_front(*(NodeCloner(cloner, this)(*b.pointed_node())));
                  }
               }
            }
            this->priv_hasher() = src.priv_hasher();
            this->priv_equal()  = src.priv_equal();
            rollback.release();
            this->priv_size_traits().set_size(src.priv_size_traits().get_size());
            this->priv_split_traits().set_size(dst_bucket_count);
            this->priv_insertion_update_cache(0u);
            this->priv_erasure_update_cache();
         }
         else if(store_hash){
            //Unlike previous cloning algorithm, this can throw
            //if cloner, hasher or comparison functor throw
            const_iterator b(src.begin()), e(src.end());
            detail::exception_disposer<hashtable_impl, Disposer>
               rollback(*this, disposer);
            for(; b != e; ++b){
               std::size_t hash_value = this->priv_stored_or_compute_hash(*b, store_hash_t());;
               this->priv_insert_equal_with_hash(*cloner(*b), hash_value);
            }
            rollback.release();
         }
         else{
            //Unlike previous cloning algorithm, this can throw
            //if cloner, hasher or comparison functor throw
            const_iterator b(src.begin()), e(src.end());
            detail::exception_disposer<hashtable_impl, Disposer>
               rollback(*this, disposer);
            for(; b != e; ++b){
               this->insert_equal(*cloner(*b));
            }
            rollback.release();
         }
      }
   }

   iterator insert_equal(reference value)
   {
      size_type bucket_num;
      std::size_t hash_value;
      siterator prev;
      siterator it = this->priv_find
         (value, this->priv_hasher(), this->priv_equal(), bucket_num, hash_value, prev);
      return this->priv_insert_equal_find(value, bucket_num, hash_value, it);
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert_equal(*b);
   }


   hashtable ( const bucket_traits &b_traits
             , const hasher & hash_func = hasher()
             , const key_equal &equal_func = key_equal()
             , const value_traits &v_traits = value_traits())
      :  Base(b_traits, hash_func, equal_func, v_traits)
   {}


   hashtable(BOOST_RV_REF(hashtable) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   hashtable& operator=(BOOST_RV_REF(hashtable) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }

   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   node_ptr get_root_node()
   {  return pointer_traits<node_ptr>::pointer_to(data_.root_plus_size_.root_);  }


   const_node_ptr get_root_node() const
   {  return pointer_traits<const_node_ptr>::pointer_to(data_.root_plus_size_.root_);  }

      data_t(const value_traits &val_traits)
         :  value_traits(val_traits)
      {}

      data_t(const value_traits &val_traits)
         :  value_traits(val_traits)
      {}


   size_traits &priv_size_traits()
   {  return data_.root_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }

   node &prot_root_node()
   {  return data_.root_plus_size_.root_; }


   node const &prot_root_node() const
   {  return data_.root_plus_size_.root_; }


   void prot_set_size(size_type s)
   {  data_.root_plus_size_.set_size(s);  }

   explicit list_impl(const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
   }

   template<class Iterator>
   list_impl(Iterator b, Iterator e, const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
      this->insert(this->cend(), b, e);
   }

   list_impl(BOOST_RV_REF(list_impl) x)
      : data_(::boost::move(x.priv_value_traits()))
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
      this->swap(x);
   }

   list_impl& operator=(BOOST_RV_REF(list_impl) x)
   {  this->swap(x); return *this;  }

   ~list_impl()
   {}

   void push_back(reference value)
   {
      node_ptr to_insert = get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(to_insert));
      node_algorithms::link_before(this->get_root_node(), to_insert);
      this->priv_size_traits().increment();
   }

   void push_front(reference value)
   {
      node_ptr to_insert = get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(to_insert));
      node_algorithms::link_before(node_traits::get_next(this->get_root_node()), to_insert);
      this->priv_size_traits().increment();
   }

   void pop_back()
   {  return this->pop_back_and_dispose(detail::null_disposer());   }

   template<class Disposer>
   void pop_back_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_previous(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(get_real_value_traits().to_value_ptr(to_erase));
   }

   void pop_front()
   {  return this->pop_front_and_dispose(detail::null_disposer());   }

   template<class Disposer>
   void pop_front_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(get_real_value_traits().to_value_ptr(to_erase));
   }

   reference front()
   { return *get_real_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   reference back()
   { return *get_real_value_traits().to_value_ptr(node_traits::get_previous(this->get_root_node())); }

   iterator begin()
   { return iterator(node_traits::get_next(this->get_root_node()), this); }

   const_iterator cbegin() const
   { return const_iterator(node_traits::get_next(this->get_root_node()), this); }

   iterator end()
   { return iterator(this->get_root_node(), this); }

   const_iterator cend() const
   { return const_iterator(uncast(this->get_root_node()), this); }

   reverse_iterator rbegin()
   { return reverse_iterator(this->end()); }

   const_reverse_iterator crbegin() const
   { return const_reverse_iterator(end()); }

   reverse_iterator rend()
   { return reverse_iterator(begin()); }

   const_reverse_iterator crend() const
   { return const_reverse_iterator(this->begin()); }

   static list_impl &container_from_end_iterator(iterator end_iterator)
   {  return list_impl::priv_container_from_end_iterator(end_iterator);   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else
         return node_algorithms::count(this->get_root_node()) - 1;
   }

   bool empty() const
   {  return node_algorithms::unique(this->get_root_node());   }

   void swap(list_impl& other)
   {
      node_algorithms::swap_nodes(this->get_root_node(), other.get_root_node());
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   void shift_backwards(size_type n = 1)
   {  node_algorithms::move_forward(this->get_root_node(), n);  }

   void shift_forward(size_type n = 1)
   {  node_algorithms::move_backwards(this->get_root_node(), n);  }

   iterator erase(const_iterator i)
   {  return this->erase_and_dispose(i, detail::null_disposer());  }

   template <class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {
      node_ptr to_erase(i.pointed_node());
      ++i;
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(this->get_real_value_traits().to_value_ptr(to_erase));
      return i.unconst();
   }

   void clear()
   {
      if(safemode_or_autounlink){
         this->clear_and_dispose(detail::null_disposer());
      }
      else{
         node_algorithms::init_header(this->get_root_node());
         this->priv_size_traits().set_size(size_type(0));
      }
   }

   template <class Disposer>
   void clear_and_dispose(Disposer disposer)
   {
      const_iterator it(this->begin()), itend(this->end());
      while(it != itend){
         node_ptr to_erase(it.pointed_node());
         ++it;
         if(safemode_or_autounlink)
            node_algorithms::init(to_erase);
         disposer(get_real_value_traits().to_value_ptr(to_erase));
      }
      node_algorithms::init_header(this->get_root_node());
      this->priv_size_traits().set_size(0);
   }

   template <class Cloner, class Disposer>
   void clone_from(const list_impl &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      detail::exception_disposer<list_impl, Disposer>
         rollback(*this, disposer);
      const_iterator b(src.begin()), e(src.end());
      for(; b != e; ++b){
         this->push_back(*cloner(*b));
      }
      rollback.release();
   }

   iterator insert(const_iterator p, reference value)
   {
      node_ptr to_insert = this->get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(to_insert));
      node_algorithms::link_before(p.pointed_node(), to_insert);
      this->priv_size_traits().increment();
      return iterator(to_insert, this);
   }

   template<class Iterator>
   void assign(Iterator b, Iterator e)
   {
      this->clear();
      this->insert(this->cend(), b, e);
   }

   template<class Iterator, class Disposer>
   void dispose_and_assign(Disposer disposer, Iterator b, Iterator e)
   {
      this->clear_and_dispose(disposer);
      this->insert(this->cend(), b, e);
   }

   void splice(const_iterator p, list_impl& x)
   {
      if(!x.empty()){
         node_algorithms::transfer
            (p.pointed_node(), x.begin().pointed_node(), x.end().pointed_node());
         size_traits &thist = this->priv_size_traits();
         size_traits &xt = x.priv_size_traits();
         thist.increase(xt.get_size());
         xt.set_size(size_type(0));
      }
   }

   void sort()
   {  this->sort(std::less<value_type>());  }

   template<class Predicate>
   void sort(Predicate p)
   {
      if(node_traits::get_next(this->get_root_node())
         != node_traits::get_previous(this->get_root_node())){
         list_impl carry(this->priv_value_traits());
         detail::array_initializer<list_impl, 64> counter(this->priv_value_traits());
         int fill = 0;
         while(!this->empty()){
            carry.splice(carry.cbegin(), *this, this->cbegin());
            int i = 0;
            while(i < fill && !counter[i].empty()) {
               counter[i].merge(carry, p);
               carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if(i == fill)
               ++fill;
         }
         for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i-1], p);
         this->swap(counter[fill-1]);
      }
   }

   void merge(list_impl& x)
   { this->merge(x, std::less<value_type>()); }

   template<class Predicate>
   void merge(list_impl& x, Predicate p)
   {
      const_iterator e(this->cend()), ex(x.cend());
      const_iterator b(this->cbegin());
      while(!x.empty()){
         const_iterator ix(x.cbegin());
         while (b != e && !p(*ix, *b)){
            ++b;
         }
         if(b == e){
            //Now transfer the rest to the end of the container
            this->splice(e, x);
            break;
         }
         else{
            size_type n(0);
            do{
               ++ix; ++n;
            } while(ix != ex && p(*ix, *b));
            this->splice(b, x, x.begin(), ix, n);
         }
      }
   }

   void reverse()
   {  node_algorithms::reverse(this->get_root_node());   }

   void remove(const_reference value)
   {  this->remove_if(detail::equal_to_value<const_reference>(value));  }

   template<class Disposer>
   void remove_and_dispose(const_reference value, Disposer disposer)
   {  this->remove_and_dispose_if(detail::equal_to_value<const_reference>(value), disposer);  }

   template<class Pred>
   void remove_if(Pred pred)
   {  this->remove_and_dispose_if(pred, detail::null_disposer());   }

   template<class Pred, class Disposer>
   void remove_and_dispose_if(Pred pred, Disposer disposer)
   {
      const_iterator cur(this->cbegin());
      const_iterator last(this->cend());
      while(cur != last) {
         if(pred(*cur)){
            cur = this->erase_and_dispose(cur, disposer);
         }
         else{
            ++cur;
         }
      }
   }

   void unique()
   {  this->unique_and_dispose(std::equal_to<value_type>(), detail::null_disposer());  }

   template<class BinaryPredicate>
   void unique(BinaryPredicate pred)
   {  this->unique_and_dispose(pred, detail::null_disposer());  }

   template<class Disposer>
   void unique_and_dispose(Disposer disposer)
   {  this->unique_and_dispose(std::equal_to<value_type>(), disposer);  }

   template<class BinaryPredicate, class Disposer>
   void unique_and_dispose(BinaryPredicate pred, Disposer disposer)
   {
      const_iterator itend(this->cend());
      const_iterator cur(this->cbegin());

      if(cur != itend){
         const_iterator after(cur);
         ++after;
         while(after != itend){
            if(pred(*cur, *after)){
               after = this->erase_and_dispose(after, disposer);
            }
            else{
               cur = after;
               ++after;
            }
         }
      }
   }

   static iterator s_iterator_to(reference value)
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(real_value_traits::to_node_ptr(value)));
      return iterator(real_value_traits::to_node_ptr(value), 0);
   }

   iterator iterator_to(reference value)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(real_value_traits::to_node_ptr(value)));
      return iterator(real_value_traits::to_node_ptr(value), this);
   }

   static list_impl &priv_container_from_end_iterator(const const_iterator &end_iterator)
   {
      root_plus_size *r = detail::parent_from_member<root_plus_size, node>
         ( boost::intrusive::detail::to_raw_pointer(end_iterator.pointed_node()), &root_plus_size::root_);
      data_t *d = detail::parent_from_member<data_t, root_plus_size>
         ( r, &data_t::root_plus_size_);
      list_impl *s  = detail::parent_from_member<list_impl, data_t>(d, &list_impl::data_);
      return *s;
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{
   typedef list_impl<Config> list_type;
   typedef typename list_type::const_iterator const_iterator;
   const bool C = list_type::constant_time_size;
   if(C && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();

   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(C){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const list_impl<T, Options...> &x, const list_impl<T, Options...> &y)
#else
(const list_impl<Config> &x, const list_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(list_impl<T, Options...> &x, list_impl<T, Options...> &y)
#else
(list_impl<Config> &x, list_impl<Config> &y)
#endif
{  x.swap(y);  }


   list(const value_traits &v_traits = value_traits())
      :  Base(v_traits)
   {}


   list(BOOST_RV_REF(list) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   list& operator=(BOOST_RV_REF(list) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static list &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<list &>(Base::container_from_end_iterator(end_iterator));   }


   static const list &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const list &>(Base::container_from_end_iterator(end_iterator));   }

   static pointer pointer_to(reference r)
   {
      //Non-standard extension, it does not require Ptr::pointer_to. If not present
      //tries to converts &r to pointer.
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_pointer_to
            <Ptr, typename boost::intrusive::detail::unvoid<element_type &>::type>::value;
      ::boost::integral_constant<bool, value> flag;
      return pointer_traits::priv_pointer_to(flag, r);
   }

   template<class UPtr>
   static pointer static_cast_from(const UPtr &uptr)
   {
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_static_cast_from
            <Ptr, const UPtr>::value;
      ::boost::integral_constant<bool, value> flag;
      return pointer_traits::priv_static_cast_from(flag, uptr);
   }

   template<class UPtr>
   static pointer const_cast_from(const UPtr &uptr)
   {
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_const_cast_from
            <Ptr, const UPtr>::value;
      ::boost::integral_constant<bool, value> flag;
      return pointer_traits::priv_const_cast_from(flag, uptr);
   }

   template<class UPtr>
   static pointer dynamic_cast_from(const UPtr &uptr)
   {
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_dynamic_cast_from
            <Ptr, const UPtr>::value;
      ::boost::integral_constant<bool, value> flag;
      return pointer_traits::priv_dynamic_cast_from(flag, uptr);
   }

   template <class T>
   static T* to_raw_pointer(T* p)
   {  return p; }


   template <class Pointer>
   static typename pointer_traits<Pointer>::element_type*
      to_raw_pointer(const Pointer &p)
   {  return pointer_traits::to_raw_pointer(p.operator->());  }

   static pointer priv_pointer_to(boost::true_type, typename boost::intrusive::detail::unvoid<element_type>::type& r)
      { return Ptr::pointer_to(r); }

   template<class UPtr>
   static pointer priv_static_cast_from(boost::true_type, const UPtr &uptr)
   { return Ptr::static_cast_from(uptr); }

   template<class UPtr>
   static pointer priv_const_cast_from(boost::true_type, const UPtr &uptr)
   { return Ptr::const_cast_from(uptr); }

   template<class UPtr>
   static pointer priv_dynamic_cast_from(boost::true_type, const UPtr &uptr)
   { return Ptr::dynamic_cast_from(uptr); }

   static pointer pointer_to(reference r)
   { return boost::intrusive::detail::addressof(r); }

   template<class U>
   static pointer static_cast_from(U *uptr)
   {  return static_cast<pointer>(uptr);  }

   template<class U>
   static pointer const_cast_from(U *uptr)
   {  return const_cast<pointer>(uptr);  }

   template<class U>
   static pointer dynamic_cast_from(U *uptr)
   {  return dynamic_cast<pointer>(uptr);  }

   static node_ptr       to_node_ptr (value_type &value)
      {  return pointer_traits<node_ptr>::pointer_to(value);  }

   static const_node_ptr to_node_ptr (const value_type &value)
      {  return pointer_traits<const_node_ptr>::pointer_to(value);  }

   static const pointer  &      to_value_ptr(const node_ptr &n)        {  return n; }

   static const const_pointer  &to_value_ptr(const const_node_ptr &n)  {  return n; }

   node &prot_header_node(){ return tree_.prot_header_node(); }

   node const &prot_header_node() const{ return tree_.prot_header_node(); }

   void prot_set_size(size_type s){ tree_.prot_set_size(s); }

   value_compare &prot_comp(){ return tree_.prot_comp(); }

   explicit set_impl( const value_compare &cmp = value_compare()
                    , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   set_impl( Iterator b, Iterator e
           , const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      : tree_(true, b, e, cmp, v_traits)
   {}

   set_impl(BOOST_RV_REF(set_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   set_impl& operator=(BOOST_RV_REF(set_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~set_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static set_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<set_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &set_impl::tree_);
   }

   static set_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<set_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &set_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(set_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const set_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y)
#else
(const set_impl<Config> &x, const set_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y)
#else
(const set_impl<Config> &x, const set_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y)
#else
(const set_impl<Config> &x, const set_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const set_impl<T, Options...> &x, const set_impl<T, Options...> &y)
#else
(const set_impl<Config> &x, const set_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(set_impl<T, Options...> &x, set_impl<T, Options...> &y)
#else
(set_impl<Config> &x, set_impl<Config> &y)
#endif
{  x.swap(y);  }


   set( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   set(BOOST_RV_REF(set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   set& operator=(BOOST_RV_REF(set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<set &>(Base::container_from_end_iterator(end_iterator));   }


   static const set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const set &>(Base::container_from_end_iterator(end_iterator));   }


   static set &container_from_iterator(iterator it)
   {  return static_cast<set &>(Base::container_from_iterator(it));   }


   static const set &container_from_iterator(const_iterator it)
   {  return static_cast<const set &>(Base::container_from_iterator(it));   }

   node &prot_header_node(){ return tree_.prot_header_node(); }

   node const &prot_header_node() const{ return tree_.prot_header_node(); }

   void prot_set_size(size_type s){ tree_.prot_set_size(s); }

   value_compare &prot_comp(){ return tree_.prot_comp(); }

   explicit multiset_impl( const value_compare &cmp = value_compare()
                         , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   multiset_impl( Iterator b, Iterator e
                , const value_compare &cmp = value_compare()
                , const value_traits &v_traits = value_traits())
      : tree_(false, b, e, cmp, v_traits)
   {}

   multiset_impl(BOOST_RV_REF(multiset_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   multiset_impl& operator=(BOOST_RV_REF(multiset_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~multiset_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static multiset_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<multiset_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &multiset_impl::tree_);
   }

   static multiset_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<multiset_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &multiset_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(multiset_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const multiset_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

   iterator insert(reference value)
   {  return tree_.insert_equal(value);  }

   iterator insert(const_iterator hint, reference value)
   {  return tree_.insert_equal(hint, value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_.insert_equal(b, e);  }

   iterator insert_before(const_iterator pos, reference value)
   {  return tree_.insert_before(pos, value);  }

   void push_back(reference value)
   {  tree_.push_back(value);  }

   void push_front(reference value)
   {  tree_.push_front(value);  }

   iterator erase(const_iterator i)
   {  return tree_.erase(i);  }

   iterator erase(const_iterator b, iterator e)
   {  return tree_.erase(b, e);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return tree_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  return tree_.erase_and_dispose(b, e, disposer);  }

   void clear()
   {  return tree_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return tree_.clear_and_dispose(disposer);  }

   size_type count(const_reference value) const
   {  return tree_.count(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.count(key, comp);  }

   iterator lower_bound(const_reference value)
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator lower_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.lower_bound(key, comp);  }

   const_iterator lower_bound(const_reference value) const
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator lower_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.lower_bound(key, comp);  }

   iterator upper_bound(const_reference value)
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator upper_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.upper_bound(key, comp);  }

   const_iterator upper_bound(const_reference value) const
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator upper_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.upper_bound(key, comp);  }

   iterator find(const_reference value)
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator find(const KeyType& key, KeyValueCompare comp)
   {  return tree_.find(key, comp);  }

   const_iterator find(const_reference value) const
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator find(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.find(key, comp);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y)
#else
(const multiset_impl<Config> &x, const multiset_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y)
#else
(const multiset_impl<Config> &x, const multiset_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y)
#else
(const multiset_impl<Config> &x, const multiset_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const multiset_impl<T, Options...> &x, const multiset_impl<T, Options...> &y)
#else
(const multiset_impl<Config> &x, const multiset_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(multiset_impl<T, Options...> &x, multiset_impl<T, Options...> &y)
#else
(multiset_impl<Config> &x, multiset_impl<Config> &y)
#endif
{  x.swap(y);  }


   multiset( const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   multiset(BOOST_RV_REF(multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   multiset& operator=(BOOST_RV_REF(multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static const multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static multiset &container_from_iterator(iterator it)
   {  return static_cast<multiset &>(Base::container_from_iterator(it));   }


   static const multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const multiset &>(Base::container_from_iterator(it));   }

inline std::size_t calculate_h_sqrt2 (std::size_t n)
{
   std::size_t f_log2 = detail::floor_log2(n);
   return (2*f_log2) + (n >= detail::sqrt2_pow_2xplus1 (f_log2));
}

   h_alpha_sqrt2_t(void){}

   std::size_t operator()(std::size_t n) const
   {  return calculate_h_sqrt2(n);  }

   alpha_0_75_by_max_size_t(void){}

   std::size_t operator()(std::size_t max_tree_size) const
   {
      const std::size_t max_tree_size_limit = ((~std::size_t(0))/std::size_t(3));
      return max_tree_size > max_tree_size_limit ? max_tree_size/4*3 : max_tree_size*3/4;
   }

   h_alpha_t(float inv_minus_logalpha)
      :  inv_minus_logalpha_(inv_minus_logalpha)
   {}


   std::size_t operator()(std::size_t n) const
   {
      //Returns floor(log2(1/alpha(n))) ->
      // floor(log2(n)/log(1/alpha)) ->
      // floor(log2(n)/(-log2(alpha)))
      //return static_cast<std::size_t>(std::log(float(n))*inv_minus_logalpha_);
      return static_cast<std::size_t>(detail::fast_log2(float(n))*inv_minus_logalpha_);
   }

   alpha_by_max_size_t(float alpha)
      :  alpha_(alpha)
   {}


   float operator()(std::size_t max_tree_size) const
   {  return float(max_tree_size)*alpha_;   }


   alpha_holder()
   {  set_alpha(0.7f);   }


   float get_alpha() const
   {  return alpha_;  }


   void set_alpha(float alpha)
   {
      alpha_ = alpha;
      inv_minus_logalpha_ = 1/(-detail::fast_log2(alpha));
   }


   h_alpha_t get_h_alpha_t() const
   {  return h_alpha_t(inv_minus_logalpha_);  }


   multiply_by_alpha_t get_multiply_by_alpha_t() const
   {  return multiply_by_alpha_t(alpha_);  }


   float get_alpha() const
   {  return 0.70710677f;  }


   void set_alpha(float)
   {  //alpha CAN't be changed.
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0);
   }


   h_alpha_t get_h_alpha_t() const
   {  return h_alpha_t();  }


   multiply_by_alpha_t get_multiply_by_alpha_t() const
   {  return multiply_by_alpha_t();  }

      node_plus_pred_t(const value_compare &comp)
         :  detail::ebo_functor_holder<value_compare>(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
         ,  max_tree_size_(0)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
         ,  max_tree_size_(0)
      {}


   float priv_alpha() const
   {  return this->priv_alpha_traits().get_alpha();  }


   void priv_alpha(float alpha)
   {  return this->priv_alpha_traits().set_alpha(alpha);  }


   const value_compare &priv_comp() const
   {  return data_.node_plus_pred_.get();  }


   value_compare &priv_comp()
   {  return data_.node_plus_pred_.get();  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }


   node_ptr priv_header_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_alpha_.header_);  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   size_traits &priv_size_traits()
   {  return data_.node_plus_pred_.size_traits_;  }


   alpha_traits &priv_alpha_traits()
   {  return data_.node_plus_pred_.header_plus_alpha_;  }


   const alpha_traits &priv_alpha_traits() const
   {  return data_.node_plus_pred_.header_plus_alpha_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }


   h_alpha_t get_h_alpha_func() const
   {  return priv_alpha_traits().get_h_alpha_t();  }


   multiply_by_alpha_t get_alpha_by_max_size_func() const
   {  return priv_alpha_traits().get_multiply_by_alpha_t(); }

   explicit sgtree_impl( const value_compare &cmp     = value_compare()
                       , const value_traits &v_traits = value_traits())
      :  data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
   }

   template<class Iterator>
   sgtree_impl( bool unique, Iterator b, Iterator e
              , const value_compare &cmp     = value_compare()
              , const value_traits &v_traits = value_traits())
      : data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   sgtree_impl(BOOST_RV_REF(sgtree_impl) x)
      : data_(::boost::move(x.priv_comp()), ::boost::move(x.priv_value_traits()))
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      this->swap(x);
   }

   sgtree_impl& operator=(BOOST_RV_REF(sgtree_impl) x)
   {  this->swap(x); return *this;  }

   ~sgtree_impl()
   {}

   iterator begin()
   {  return iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   const_iterator cbegin() const
   {  return const_iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   iterator end()
   {  return iterator (this->priv_header_ptr(), this);  }

   const_iterator cend() const
   {  return const_iterator (uncast(this->priv_header_ptr()), this);  }

   reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(end());  }

   reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   const_reverse_iterator crend() const
   {  return const_reverse_iterator(begin());   }

   static sgtree_impl &container_from_end_iterator(iterator end_iterator)
   {  return priv_container_from_end_iterator(end_iterator);   }

   static sgtree_impl &container_from_iterator(iterator it)
   {  return priv_container_from_iterator(it);   }

   value_compare value_comp() const
   {  return priv_comp();   }

   bool empty() const
   {  return node_algorithms::unique(this->priv_header_ptr());   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else{
         return (size_type)node_algorithms::size(this->priv_header_ptr());
      }
   }

   void swap(sgtree_impl& other)
   {
      //This can throw
      using std::swap;
      swap(priv_comp(), priv_comp());
      swap(priv_alpha_traits(), priv_alpha_traits());
      swap(data_.max_tree_size_, other.data_.max_tree_size_);
      //These can't throw
      node_algorithms::swap_tree(this->priv_header_ptr(), other.priv_header_ptr());
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   iterator insert_equal(reference value)
   {
      detail::key_nodeptr_comp<value_compare, sgtree_impl>
         key_node_comp(priv_comp(), this);
      node_ptr to_insert(get_real_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      std::size_t max_tree_size = (std::size_t)data_.max_tree_size_;
      node_ptr p = node_algorithms::insert_equal_upper_bound
         (this->priv_header_ptr(), to_insert, key_node_comp
         , (size_type)this->size(), this->get_h_alpha_func(), max_tree_size);
      this->priv_size_traits().increment();
      data_.max_tree_size_ = (size_type)max_tree_size;
      return iterator(p, this);
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{
   typedef sgtree_impl<Config> tree_type;
   typedef typename tree_type::const_iterator const_iterator;

   if(tree_type::constant_time_size && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();
   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(tree_type::constant_time_size){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sgtree_impl<T, Options...> &x, const sgtree_impl<T, Options...> &y)
#else
(const sgtree_impl<Config> &x, const sgtree_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(sgtree_impl<T, Options...> &x, sgtree_impl<T, Options...> &y)
#else
(sgtree_impl<Config> &x, sgtree_impl<Config> &y)
#endif
{  x.swap(y);  }


   sgtree( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   sgtree(BOOST_RV_REF(sgtree) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   sgtree& operator=(BOOST_RV_REF(sgtree) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static sgtree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sgtree &>(Base::container_from_end_iterator(end_iterator));   }


   static const sgtree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sgtree &>(Base::container_from_end_iterator(end_iterator));   }


      avltree_node_cloner(F f)
         :  base_t(f)
      {}


      node_ptr operator()(const node_ptr &p)
      {
         node_ptr n = base_t::get()(p);
         NodeTraits::set_balance(n, NodeTraits::get_balance(p));
         return n;
      }

      void operator()(const node_ptr &to_erase, const node_ptr &successor)
      {  NodeTraits::set_balance(successor, NodeTraits::get_balance(to_erase));  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return tree_algorithms::begin_node(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return tree_algorithms::end_node(header);   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {  return tree_algorithms::swap_tree(header1, header2);  }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(tree_algorithms::get_header(node1)), header2(tree_algorithms::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {
      if(node1 == node2)   return;

      tree_algorithms::swap_nodes(node1, header1, node2, header2);
      //Swap balance
      balance c = NodeTraits::get_balance(node1);
      NodeTraits::set_balance(node1, NodeTraits::get_balance(node2));
      NodeTraits::set_balance(node2, c);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, tree_algorithms::get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {
      tree_algorithms::replace_node(node_to_be_replaced, header, new_node);
      NodeTraits::set_balance(new_node, NodeTraits::get_balance(node_to_be_replaced));
   }

   static void unlink(const node_ptr & node)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node);
      }
   }

   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header)
   {  return tree_algorithms::unlink_leftmost_without_rebalance(header);   }

   static bool unique(const const_node_ptr & node)
   {  return tree_algorithms::unique(node);  }

   static std::size_t count(const const_node_ptr & node)
   {  return tree_algorithms::count(node);   }

   static std::size_t size(const const_node_ptr & header)
   {  return tree_algorithms::size(header);   }

   static node_ptr next_node(const node_ptr & p)
   {  return tree_algorithms::next_node(p); }

   static node_ptr prev_node(const node_ptr & p)
   {  return tree_algorithms::prev_node(p); }

   static void init(const node_ptr & node)
   {  tree_algorithms::init(node);  }

   static void init_header(const node_ptr & header)
   {
      tree_algorithms::init_header(header);
      NodeTraits::set_balance(header, NodeTraits::zero());
   }

   static node_ptr erase(const node_ptr & header, const node_ptr & z)
   {
      typename tree_algorithms::data_for_rebalance info;
      tree_algorithms::erase(header, z, avltree_erase_fixup(), info);
      node_ptr x = info.x;
      node_ptr x_parent = info.x_parent;

      //Rebalance avltree
      rebalance_after_erasure(header, x, x_parent);
      return z;
   }

   template <class Cloner, class Disposer>
   static void clone
      (const const_node_ptr & source_header, const node_ptr & target_header, Cloner cloner, Disposer disposer)
   {
      avltree_node_cloner<Cloner> new_cloner(cloner);
      tree_algorithms::clone(source_header, target_header, new_cloner, disposer);
   }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {  tree_algorithms::clear_and_dispose(header, disposer); }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::lower_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::upper_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::find(header, key, comp);  }


   static node_ptr to_node_ptr(reference value)
   { return node_ptr(&value); }


   static pointer to_value_ptr(const node_ptr &n)
   {
//      This still fails in gcc < 4.4 so forget about it
//      using ::boost::static_pointer_cast;
//      return static_pointer_cast<value_type>(n));
      return pointer(&static_cast<value_type&>(*n));
   }


   node_ptr get_end_node()
   {  return node_ptr(linear ? node_ptr() : this->get_root_node());  }


   const_node_ptr get_end_node() const
   {
      return const_node_ptr
         (linear ? const_node_ptr() : this->get_root_node());  }


   node_ptr get_root_node()
   {  return pointer_traits<node_ptr>::pointer_to(data_.root_plus_size_.root_);  }


   const_node_ptr get_root_node() const
   {  return pointer_traits<const_node_ptr>::pointer_to(data_.root_plus_size_.root_);  }


   node_ptr get_last_node()
   {  return this->get_last_node(detail::bool_<cache_last>());  }


   const_node_ptr get_last_node() const
   {  return this->get_last_node(detail::bool_<cache_last>());  }


   void set_last_node(const node_ptr &n)
   {  return this->set_last_node(n, detail::bool_<cache_last>());  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   void set_default_constructed_state()
   {
      node_algorithms::init_header(this->get_root_node());
      this->priv_size_traits().set_size(size_type(0));
      if(cache_last){
         this->set_last_node(this->get_root_node());
      }
   }

      data_t(const value_traits &val_traits)
         :  value_traits(val_traits)
      {}

      data_t(const value_traits &val_traits)
         :  value_traits(val_traits)
      {}


   size_traits &priv_size_traits()
   {  return data_.root_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }

   node &prot_root_node()
   {  return data_.root_plus_size_.root_; }


   node const &prot_root_node() const
   {  return data_.root_plus_size_.root_; }


   void prot_set_size(size_type s)
   {  data_.root_plus_size_.set_size(s);  }

   slist_impl( const node_ptr & f, const node_ptr & before_l
             , size_type n, const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {
      if(n){
         this->priv_size_traits().set_size(n);
         if(cache_last){
            this->set_last_node(before_l);
         }
         node_traits::set_next(this->get_root_node(), f);
         node_traits::set_next(before_l, this->get_end_node());
      }
      else{
         this->set_default_constructed_state();
      }
   }

   explicit slist_impl(const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {  this->set_default_constructed_state(); }

   template<class Iterator>
   slist_impl(Iterator b, Iterator e, const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {
      this->set_default_constructed_state();
      this->insert_after(this->cbefore_begin(), b, e);
   }

   slist_impl(BOOST_RV_REF(slist_impl) x)
      : data_(::boost::move(x.priv_value_traits()))
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
      this->swap(x);
   }

   slist_impl& operator=(BOOST_RV_REF(slist_impl) x)
   {  this->swap(x); return *this;  }

   ~slist_impl()
   {}

   void clear()
   {
      if(safemode_or_autounlink){
         this->clear_and_dispose(detail::null_disposer());
      }
      else{
         this->set_default_constructed_state();
      }
   }

   template <class Disposer>
   void clear_and_dispose(Disposer disposer)
   {
      const_iterator it(this->begin()), itend(this->end());
      while(it != itend){
         node_ptr to_erase(it.pointed_node());
         ++it;
         if(safemode_or_autounlink)
            node_algorithms::init(to_erase);
         disposer(get_real_value_traits().to_value_ptr(to_erase));
      }
      this->set_default_constructed_state();
   }

   void push_front(reference value)
   {
      node_ptr to_insert = get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(to_insert));
      if(cache_last){
         if(this->empty()){
            this->set_last_node(to_insert);
         }
      }
      node_algorithms::link_after(this->get_root_node(), to_insert);
      this->priv_size_traits().increment();
   }

   void push_back(reference value)
   {
      BOOST_STATIC_ASSERT((cache_last));
      node_ptr n = get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(n));
      node_algorithms::link_after(this->get_last_node(), n);
      if(cache_last){
         this->set_last_node(n);
      }
      this->priv_size_traits().increment();
   }

   void pop_front()
   {  return this->pop_front_and_dispose(detail::null_disposer());   }

   template<class Disposer>
   void pop_front_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      node_algorithms::unlink_after(this->get_root_node());
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(get_real_value_traits().to_value_ptr(to_erase));
      if(cache_last){
         if(this->empty()){
            this->set_last_node(this->get_root_node());
         }
      }
   }

   reference front()
   { return *this->get_real_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   reference back()
   {
      BOOST_STATIC_ASSERT((cache_last));
      return *this->get_real_value_traits().to_value_ptr(this->get_last_node());
   }

   iterator begin()
   { return iterator (node_traits::get_next(this->get_root_node()), this); }

   const_iterator cbegin() const
   { return const_iterator(node_traits::get_next(this->get_root_node()), this); }

   iterator end()
   { return iterator(this->get_end_node(), this); }

   const_iterator cend() const
   { return this->end(); }

   iterator before_begin()
   { return iterator(this->get_root_node(), this); }

   const_iterator cbefore_begin() const
   { return this->before_begin(); }

   iterator last()
   {
      //This function shall not be used if cache_last is not true
      BOOST_INTRUSIVE_INVARIANT_ASSERT(cache_last);
      return iterator (this->get_last_node(), this);
   }

   const_iterator clast() const
   { return const_iterator(this->get_last_node(), this); }

   static slist_impl &container_from_end_iterator(iterator end_iterator)
   {  return slist_impl::priv_container_from_end_iterator(end_iterator);   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else
         return node_algorithms::count(this->get_root_node()) - 1;
   }

   bool empty() const
   { return node_algorithms::unique(this->get_root_node()); }

   void swap(slist_impl& other)
   {
      if(cache_last){
         priv_swap_cache_last(this, &other);
      }
      else{
         this->priv_swap_lists(this->get_root_node(), other.get_root_node(), detail::bool_<linear>());
      }
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   void shift_backwards(size_type n = 1)
   {  this->priv_shift_backwards(n, detail::bool_<linear>());  }

   void shift_forward(size_type n = 1)
   {  this->priv_shift_forward(n, detail::bool_<linear>()); }

   template <class Cloner, class Disposer>
   void clone_from(const slist_impl &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      detail::exception_disposer<slist_impl, Disposer>
         rollback(*this, disposer);
      const_iterator prev(this->cbefore_begin());
      const_iterator b(src.begin()), e(src.end());
      for(; b != e; ++b){
         prev = this->insert_after(prev, *cloner(*b));
      }
      rollback.release();
   }

   iterator insert_after(const_iterator prev_p, reference value)
   {
      node_ptr n = get_real_value_traits().to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::inited(n));
      node_ptr prev_n(prev_p.pointed_node());
      node_algorithms::link_after(prev_n, n);
      if(cache_last && (this->get_last_node() == prev_n)){
         this->set_last_node(n);
      }
      this->priv_size_traits().increment();
      return iterator (n, this);
   }

   iterator insert(const_iterator p, reference value)
   {  return this->insert_after(this->previous(p), value);  }

   iterator erase_after(const_iterator prev)
   {  return this->erase_after_and_dispose(prev, detail::null_disposer());  }

   iterator erase(const_iterator i)
   {  return this->erase_after(this->previous(i));  }

   template<class Disposer>
   iterator erase_after_and_dispose(const_iterator prev, Disposer disposer)
   {
      const_iterator it(prev);
      ++it;
      node_ptr to_erase(it.pointed_node());
      ++it;
      node_ptr prev_n(prev.pointed_node());
      node_algorithms::unlink_after(prev_n);
      if(cache_last && (to_erase == this->get_last_node())){
         this->set_last_node(prev_n);
      }
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(get_real_value_traits().to_value_ptr(to_erase));
      this->priv_size_traits().decrement();
      return it.unconst();
   }


   template<class Disposer>
   static iterator s_erase_after_and_dispose(const_iterator prev, Disposer disposer)
   {
      BOOST_STATIC_ASSERT(((!cache_last)&&(!constant_time_size)&&(!stateful_value_traits)));
      const_iterator it(prev);
      ++it;
      node_ptr to_erase(it.pointed_node());
      ++it;
      node_ptr prev_n(prev.pointed_node());
      node_algorithms::unlink_after(prev_n);
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(real_value_traits::to_value_ptr(to_erase));
      return it.unconst();
   }


   static iterator s_erase_after(const_iterator prev)
   {  return s_erase_after_and_dispose(prev, detail::null_disposer());  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return this->erase_after_and_dispose(this->previous(i), disposer);  }

   template<class Iterator>
   void assign(Iterator b, Iterator e)
   {
      this->clear();
      this->insert_after(this->cbefore_begin(), b, e);
   }

   template<class Iterator, class Disposer>
   void dispose_and_assign(Disposer disposer, Iterator b, Iterator e)
   {
      this->clear_and_dispose(disposer);
      this->insert_after(this->cbefore_begin(), b, e, disposer);
   }

   void splice_after(const_iterator prev, slist_impl &x, const_iterator *l = 0)
   {
      if(x.empty()){
         if(l) *l = prev;
      }
      else if(linear && this->empty()){
         this->swap(x);
         if(l) *l = this->previous(this->cend());
      }
      else{
         const_iterator last_x(x.previous(x.end()));  //<- constant time if cache_last is active
         node_ptr prev_n(prev.pointed_node());
         node_ptr last_x_n(last_x.pointed_node());
         if(cache_last){
            x.set_last_node(x.get_root_node());
            if(node_traits::get_next(prev_n) == this->get_end_node()){
               this->set_last_node(last_x_n);
            }
         }
         node_algorithms::transfer_after( prev_n, x.before_begin().pointed_node(), last_x_n);
         this->priv_size_traits().increase(x.priv_size_traits().get_size());
         x.priv_size_traits().set_size(size_type(0));
         if(l) *l = last_x;
      }
   }

   void splice(const_iterator it, slist_impl &x, const_iterator *l = 0)
   {  this->splice_after(this->previous(it), x, l);   }

   template<class Predicate>
   void sort(Predicate p)
   {
      if (node_traits::get_next(node_traits::get_next(this->get_root_node()))
         != this->get_root_node()) {

         slist_impl carry(this->priv_value_traits());
         detail::array_initializer<slist_impl, 64> counter(this->priv_value_traits());
         int fill = 0;
         const_iterator last_inserted;
         while(!this->empty()){
            last_inserted = this->cbegin();
            carry.splice_after(carry.cbefore_begin(), *this, this->cbefore_begin());
            int i = 0;
            while(i < fill && !counter[i].empty()) {
               carry.swap(counter[i]);
               carry.merge(counter[i++], p, &last_inserted);
            }
            BOOST_INTRUSIVE_INVARIANT_ASSERT(counter[i].empty());
            const_iterator last_element(carry.previous(last_inserted, carry.end()));

            if(constant_time_size){
               counter[i].splice_after( counter[i].cbefore_begin(), carry
                                    , carry.cbefore_begin(), last_element
                                    , carry.size());
            }
            else{
               counter[i].splice_after( counter[i].cbefore_begin(), carry
                                    , carry.cbefore_begin(), last_element);
            }
            if(i == fill)
               ++fill;
         }

         for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i-1], p, &last_inserted);
         --fill;
         const_iterator last_element(counter[fill].previous(last_inserted, counter[fill].end()));
         if(constant_time_size){
            this->splice_after( cbefore_begin(), counter[fill], counter[fill].cbefore_begin()
                              , last_element, counter[fill].size());
         }
         else{
            this->splice_after( cbefore_begin(), counter[fill], counter[fill].cbefore_begin()
                              , last_element);
         }
      }
   }

   void sort()
   { this->sort(std::less<value_type>()); }

   template<class Predicate>
   void merge(slist_impl& x, Predicate p, const_iterator *l = 0)
   {
      const_iterator e(this->cend()), ex(x.cend()), bb(this->cbefore_begin()),
                     bb_next;
      if(l) *l = e.unconst();
      while(!x.empty()){
         const_iterator ibx_next(x.cbefore_begin()), ibx(ibx_next++);
         while (++(bb_next = bb) != e && !p(*ibx_next, *bb_next)){
            bb = bb_next;
         }
         if(bb_next == e){
            //Now transfer the rest to the end of the container
            this->splice_after(bb, x, l);
            break;
         }
         else{
            size_type n(0);
            do{
               ibx = ibx_next; ++n;
            } while(++(ibx_next = ibx) != ex && p(*ibx_next, *bb_next));
            this->splice_after(bb, x, x.before_begin(), ibx, n);
            if(l) *l = ibx;
         }
      }
   }

   void merge(slist_impl& x)
   {  this->merge(x, std::less<value_type>());  }

   void reverse()
   {
      if(cache_last && !this->empty()){
         this->set_last_node(node_traits::get_next(this->get_root_node()));
      }
      this->priv_reverse(detail::bool_<linear>());
   }

   void remove(const_reference value)
   {  this->remove_if(detail::equal_to_value<const_reference>(value));  }

   template<class Disposer>
   void remove_and_dispose(const_reference value, Disposer disposer)
   {  this->remove_and_dispose_if(detail::equal_to_value<const_reference>(value), disposer);  }

   template<class Pred>
   void remove_if(Pred pred)
   {  this->remove_and_dispose_if(pred, detail::null_disposer());   }

   template<class Pred, class Disposer>
   void remove_and_dispose_if(Pred pred, Disposer disposer)
   {
      const_iterator bcur(this->before_begin()), cur(this->begin()), e(this->end());

      while(cur != e){
         if (pred(*cur)){
            cur = this->erase_after_and_dispose(bcur, disposer);
         }
         else{
            bcur = cur;
            ++cur;
         }
      }
      if(cache_last){
         this->set_last_node(bcur.pointed_node());
      }
   }

   void unique()
   {  this->unique_and_dispose(std::equal_to<value_type>(), detail::null_disposer());  }

   template<class BinaryPredicate>
   void unique(BinaryPredicate pred)
   {  this->unique_and_dispose(pred, detail::null_disposer());  }

   template<class Disposer>
   void unique_and_dispose(Disposer disposer)
   {  this->unique(std::equal_to<value_type>(), disposer);  }

   template<class BinaryPredicate, class Disposer>
   void unique_and_dispose(BinaryPredicate pred, Disposer disposer)
   {
      const_iterator end_n(this->cend());
      const_iterator bcur(this->cbegin());
      if(bcur != end_n){
         const_iterator cur(bcur);
         ++cur;
         while(cur != end_n) {
            if (pred(*bcur, *cur)){
               cur = this->erase_after_and_dispose(bcur, disposer);
            }
            else{
               bcur = cur;
               ++cur;
            }
         }
         if(cache_last){
            this->set_last_node(bcur.pointed_node());
         }
      }
   }

   static iterator s_iterator_to(reference value)
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      //BOOST_INTRUSIVE_INVARIANT_ASSERT (!node_algorithms::inited(value_traits::to_node_ptr(value)));
      return iterator (value_traits::to_node_ptr(value), 0);
   }

   iterator iterator_to(reference value)
   {
      //BOOST_INTRUSIVE_INVARIANT_ASSERT (!node_algorithms::inited(value_traits::to_node_ptr(value)));
      return iterator (value_traits::to_node_ptr(value), this);
   }

   iterator previous(iterator i)
   {  return this->previous(this->cbefore_begin(), i); }

   void incorporate_after(const_iterator prev_pos, const node_ptr & f, const node_ptr & before_l)
   {
      if(constant_time_size)
         this->incorporate_after(prev_pos, f, before_l, std::distance(f, before_l)+1);
      else
         this->priv_incorporate_after(prev_pos.pointed_node(), f, before_l);
   }

   void priv_splice_after(const node_ptr & prev_pos_n, slist_impl &x, const node_ptr & before_f_n, const node_ptr & before_l_n)
   {
      if (cache_last && (before_f_n != before_l_n)){
         if(prev_pos_n == this->get_last_node()){
            this->set_last_node(before_l_n);
         }
         if(&x != this && node_traits::get_next(before_l_n) == x.get_end_node()){
            x.set_last_node(before_f_n);
         }
      }
      node_algorithms::transfer_after(prev_pos_n, before_f_n, before_l_n);
   }


   void priv_incorporate_after(const node_ptr & prev_pos_n, const node_ptr & first_n, const node_ptr & before_l_n)
   {
      if(cache_last){
         if(prev_pos_n == this->get_last_node()){
            this->set_last_node(before_l_n);
         }
      }
      node_algorithms::incorporate_after(prev_pos_n, first_n, before_l_n);
   }


   void priv_reverse(detail::bool_<false>)
   {  node_algorithms::reverse(this->get_root_node());   }


   void priv_shift_backwards(size_type n, detail::bool_<false>)
   {
      node_ptr l = node_algorithms::move_forward(this->get_root_node(), (std::size_t)n);
      if(cache_last && l){
         this->set_last_node(l);
      }
   }


   void priv_shift_forward(size_type n, detail::bool_<false>)
   {
      node_ptr l = node_algorithms::move_backwards(this->get_root_node(), (std::size_t)n);
      if(cache_last && l){
         this->set_last_node(l);
      }
   }


   static void priv_swap_cache_last(slist_impl *this_impl, slist_impl *other_impl)
   {
      bool other_was_empty = false;
      if(this_impl->empty()){
         //Check if both are empty or
         if(other_impl->empty())
            return;
         //If this is empty swap pointers
         slist_impl *tmp = this_impl;
         this_impl  = other_impl;
         other_impl = tmp;
         other_was_empty = true;
      }
      else{
         other_was_empty = other_impl->empty();
      }

      //Precondition: this is not empty
      node_ptr other_old_last(other_impl->get_last_node());
      node_ptr other_bfirst(other_impl->get_root_node());
      node_ptr this_bfirst(this_impl->get_root_node());
      node_ptr this_old_last(this_impl->get_last_node());

      //Move all nodes from this to other's beginning
      node_algorithms::transfer_after(other_bfirst, this_bfirst, this_old_last);
      other_impl->set_last_node(this_old_last);

      if(other_was_empty){
         this_impl->set_last_node(this_bfirst);
      }
      else{
         //Move trailing nodes from other to this
         node_algorithms::transfer_after(this_bfirst, this_old_last, other_old_last);
         this_impl->set_last_node(other_old_last);
      }
   }

   static void priv_swap_lists(const node_ptr & this_node, const node_ptr & other_node, detail::bool_<false>)
   {  node_algorithms::swap_nodes(this_node, other_node); }


   static slist_impl &priv_container_from_end_iterator(const const_iterator &end_iterator)
   {
      //Obtaining the container from the end iterator is not possible with linear
      //singly linked lists (because "end" is represented by the null pointer)
      BOOST_STATIC_ASSERT(!linear);
      root_plus_size *r = detail::parent_from_member<root_plus_size, node>
         ( boost::intrusive::detail::to_raw_pointer(end_iterator.pointed_node()), (&root_plus_size::root_));
      data_t *d = detail::parent_from_member<data_t, root_plus_size>
         ( r, &data_t::root_plus_size_);
      slist_impl *s  = detail::parent_from_member<slist_impl, data_t>(d, &slist_impl::data_);
      return *s;
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{
   typedef slist_impl<Config> slist_type;
   typedef typename slist_type::const_iterator const_iterator;
   const bool C = slist_type::constant_time_size;
   if(C && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();

   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(C){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const slist_impl<T, Options...> &x, const slist_impl<T, Options...> &y)
#else
(const slist_impl<Config> &x, const slist_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(slist_impl<T, Options...> &x, slist_impl<T, Options...> &y)
#else
(slist_impl<Config> &x, slist_impl<Config> &y)
#endif
{  x.swap(y);  }


   explicit slist(const value_traits &v_traits = value_traits())
      :  Base(v_traits)
   {}


   slist(BOOST_RV_REF(slist) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   slist& operator=(BOOST_RV_REF(slist) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static slist &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<slist &>(Base::container_from_end_iterator(end_iterator));   }


   static const slist &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const slist &>(Base::container_from_end_iterator(end_iterator));   }

   explicit sg_set_impl( const value_compare &cmp = value_compare()
                       , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   sg_set_impl( Iterator b, Iterator e
           , const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      : tree_(true, b, e, cmp, v_traits)
   {}

   sg_set_impl(BOOST_RV_REF(sg_set_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   sg_set_impl& operator=(BOOST_RV_REF(sg_set_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~sg_set_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static sg_set_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<sg_set_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &sg_set_impl::tree_);
   }

   static sg_set_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<sg_set_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &sg_set_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(sg_set_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const sg_set_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y)
#else
(const sg_set_impl<Config> &x, const sg_set_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y)
#else
(const sg_set_impl<Config> &x, const sg_set_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y)
#else
(const sg_set_impl<Config> &x, const sg_set_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_set_impl<T, Options...> &x, const sg_set_impl<T, Options...> &y)
#else
(const sg_set_impl<Config> &x, const sg_set_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(sg_set_impl<T, Options...> &x, sg_set_impl<T, Options...> &y)
#else
(sg_set_impl<Config> &x, sg_set_impl<Config> &y)
#endif
{  x.swap(y);  }


   sg_set( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   sg_set(BOOST_RV_REF(sg_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   sg_set& operator=(BOOST_RV_REF(sg_set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static sg_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sg_set &>(Base::container_from_end_iterator(end_iterator));   }


   static const sg_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sg_set &>(Base::container_from_end_iterator(end_iterator));   }


   static sg_set &container_from_iterator(iterator it)
   {  return static_cast<sg_set &>(Base::container_from_iterator(it));   }


   static const sg_set &container_from_iterator(const_iterator it)
   {  return static_cast<const sg_set &>(Base::container_from_iterator(it));   }

   explicit sg_multiset_impl( const value_compare &cmp = value_compare()
                            , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   sg_multiset_impl( Iterator b, Iterator e
                , const value_compare &cmp = value_compare()
                , const value_traits &v_traits = value_traits())
      : tree_(false, b, e, cmp, v_traits)
   {}

   sg_multiset_impl(BOOST_RV_REF(sg_multiset_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   sg_multiset_impl& operator=(BOOST_RV_REF(sg_multiset_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~sg_multiset_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static sg_multiset_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<sg_multiset_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &sg_multiset_impl::tree_);
   }

   static sg_multiset_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<sg_multiset_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &sg_multiset_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(sg_multiset_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const sg_multiset_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

   iterator insert(reference value)
   {  return tree_.insert_equal(value);  }

   iterator insert(const_iterator hint, reference value)
   {  return tree_.insert_equal(hint, value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_.insert_equal(b, e);  }

   iterator insert_before(const_iterator pos, reference value)
   {  return tree_.insert_before(pos, value);  }

   void push_back(reference value)
   {  tree_.push_back(value);  }

   void push_front(reference value)
   {  tree_.push_front(value);  }

   iterator erase(const_iterator i)
   {  return tree_.erase(i);  }

   iterator erase(const_iterator b, const_iterator e)
   {  return tree_.erase(b, e);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return tree_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  return tree_.erase_and_dispose(b, e, disposer);  }

   void clear()
   {  return tree_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return tree_.clear_and_dispose(disposer);  }

   size_type count(const_reference value) const
   {  return tree_.count(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.count(key, comp);  }

   iterator lower_bound(const_reference value)
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator lower_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.lower_bound(key, comp);  }

   const_iterator lower_bound(const_reference value) const
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator lower_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.lower_bound(key, comp);  }

   iterator upper_bound(const_reference value)
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator upper_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.upper_bound(key, comp);  }

   const_iterator upper_bound(const_reference value) const
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator upper_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.upper_bound(key, comp);  }

   iterator find(const_reference value)
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator find(const KeyType& key, KeyValueCompare comp)
   {  return tree_.find(key, comp);  }

   const_iterator find(const_reference value) const
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator find(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.find(key, comp);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y)
#else
(const sg_multiset_impl<Config> &x, const sg_multiset_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y)
#else
(const sg_multiset_impl<Config> &x, const sg_multiset_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y)
#else
(const sg_multiset_impl<Config> &x, const sg_multiset_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const sg_multiset_impl<T, Options...> &x, const sg_multiset_impl<T, Options...> &y)
#else
(const sg_multiset_impl<Config> &x, const sg_multiset_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(sg_multiset_impl<T, Options...> &x, sg_multiset_impl<T, Options...> &y)
#else
(sg_multiset_impl<Config> &x, sg_multiset_impl<Config> &y)
#endif
{  x.swap(y);  }


   sg_multiset( const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   sg_multiset(BOOST_RV_REF(sg_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   sg_multiset& operator=(BOOST_RV_REF(sg_multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static sg_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static const sg_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const sg_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static sg_multiset &container_from_iterator(iterator it)
   {  return static_cast<sg_multiset &>(Base::container_from_iterator(it));   }


   static const sg_multiset &container_from_iterator(const_iterator it)
   {  return static_cast<const sg_multiset &>(Base::container_from_iterator(it));   }

      node_plus_pred_t(const value_compare &comp)
         :  detail::ebo_functor_holder<value_compare>(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}


   const value_compare &priv_comp() const
   {  return data_.node_plus_pred_.get();  }


   value_compare &priv_comp()
   {  return data_.node_plus_pred_.get();  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }


   node_ptr priv_header_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_size_.header_);  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   size_traits &priv_size_traits()
   {  return data_.node_plus_pred_.header_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }

   explicit avltree_impl( const value_compare &cmp = value_compare()
                        , const value_traits &v_traits = value_traits())
      :  data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
   }

   template<class Iterator>
   avltree_impl( bool unique, Iterator b, Iterator e
              , const value_compare &cmp     = value_compare()
              , const value_traits &v_traits = value_traits())
      : data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   avltree_impl(BOOST_RV_REF(avltree_impl) x)
      : data_(::boost::move(x.priv_comp()), ::boost::move(x.priv_value_traits()))
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      this->swap(x);
   }

   avltree_impl& operator=(BOOST_RV_REF(avltree_impl) x)
   {  this->swap(x); return *this;  }

   ~avltree_impl()
   {}

   iterator begin()
   {  return iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   const_iterator cbegin() const
   {  return const_iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   iterator end()
   {  return iterator (this->priv_header_ptr(), this);  }

   const_iterator cend() const
   {  return const_iterator (uncast(this->priv_header_ptr()), this);  }

   reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(end());  }

   reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   const_reverse_iterator crend() const
   {  return const_reverse_iterator(begin());   }

   static avltree_impl &container_from_end_iterator(iterator end_iterator)
   {  return priv_container_from_end_iterator(end_iterator);   }

   static avltree_impl &container_from_iterator(iterator it)
   {  return priv_container_from_iterator(it);   }

   value_compare value_comp() const
   {  return priv_comp();   }

   bool empty() const
   {  return node_algorithms::unique(this->priv_header_ptr());   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else{
         return (size_type)node_algorithms::size(this->priv_header_ptr());
      }
   }

   void swap(avltree_impl& other)
   {
      //This can throw
      using std::swap;
      swap(priv_comp(), priv_comp());
      //These can't throw
      node_algorithms::swap_tree(this->priv_header_ptr(), other.priv_header_ptr());
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   iterator insert_equal(reference value)
   {
      detail::key_nodeptr_comp<value_compare, avltree_impl>
         key_node_comp(priv_comp(), this);
      node_ptr to_insert(get_real_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      iterator ret(node_algorithms::insert_equal_upper_bound
         (this->priv_header_ptr(), to_insert, key_node_comp), this);
      this->priv_size_traits().increment();
      return ret;
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{
   typedef avltree_impl<Config> tree_type;
   typedef typename tree_type::const_iterator const_iterator;

   if(tree_type::constant_time_size && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();
   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(tree_type::constant_time_size){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avltree_impl<T, Options...> &x, const avltree_impl<T, Options...> &y)
#else
(const avltree_impl<Config> &x, const avltree_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(avltree_impl<T, Options...> &x, avltree_impl<T, Options...> &y)
#else
(avltree_impl<Config> &x, avltree_impl<Config> &y)
#endif
{  x.swap(y);  }


   avltree( const value_compare &cmp      = value_compare()
          , const value_traits &v_traits  = value_traits())
      :  Base(cmp, v_traits)
   {}


   avltree(BOOST_RV_REF(avltree) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   avltree& operator=(BOOST_RV_REF(avltree) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static avltree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avltree &>(Base::container_from_end_iterator(end_iterator));   }


   static const avltree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avltree &>(Base::container_from_end_iterator(end_iterator));   }


   static avltree &container_from_iterator(iterator it)
   {  return static_cast<avltree &>(Base::container_from_iterator(it));   }


   static const avltree &container_from_iterator(const_iterator it)
   {  return static_cast<const avltree &>(Base::container_from_iterator(it));   }

      node_plus_pred_t(const value_compare &comp)
         :  detail::ebo_functor_holder<value_compare>(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}

      data_t(const value_compare & comp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp)
      {}


   const value_compare &priv_comp() const
   {  return data_.node_plus_pred_.get();  }


   value_compare &priv_comp()
   {  return data_.node_plus_pred_.get();  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }


   node_ptr priv_header_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_size_.header_);  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   size_traits &priv_size_traits()
   {  return data_.node_plus_pred_.header_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }

   explicit splaytree_impl( const value_compare &cmp     = value_compare()
                          , const value_traits &v_traits = value_traits())
      :  data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
   }

   template<class Iterator>
   splaytree_impl ( bool unique, Iterator b, Iterator e
                  , const value_compare &cmp     = value_compare()
                  , const value_traits &v_traits = value_traits())
      : data_(cmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   splaytree_impl(BOOST_RV_REF(splaytree_impl) x)
      : data_(::boost::move(x.priv_comp()), ::boost::move(x.priv_value_traits()))
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      this->swap(x);
   }

   splaytree_impl& operator=(BOOST_RV_REF(splaytree_impl) x)
   {  this->swap(x); return *this;  }

   ~splaytree_impl()
   {}

   iterator begin()
   {  return iterator(node_algorithms::begin_node(this->priv_header_ptr()), this); }

   const_iterator cbegin() const
   {  return const_iterator(node_algorithms::begin_node(this->priv_header_ptr()), this); }

   iterator end()
   {  return iterator (this->priv_header_ptr(), this);  }

   const_iterator cend() const
   {  return const_iterator (uncast(this->priv_header_ptr()), this);  }

   reverse_iterator rbegin()
   {  return reverse_iterator(end());  }

   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(end());  }

   reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   const_reverse_iterator crend() const
   {  return const_reverse_iterator(begin());   }

   static splaytree_impl &container_from_end_iterator(iterator end_iterator)
   {  return priv_container_from_end_iterator(end_iterator);   }

   static splaytree_impl &container_from_iterator(iterator it)
   {  return priv_container_from_iterator(it);   }

   value_compare value_comp() const
   {  return priv_comp();   }

   bool empty() const
   {  return this->cbegin() == this->cend();   }

   size_type size() const
   {
      if(constant_time_size){
         return this->priv_size_traits().get_size();
      }
      else{
         return (size_type)node_algorithms::size(this->priv_header_ptr());
      }
   }

   void swap(splaytree_impl& other)
   {
      //This can throw
      using std::swap;
      swap(priv_comp(), priv_comp());
      //These can't throw
      node_algorithms::swap_tree(this->priv_header_ptr(), other.priv_header_ptr());
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   iterator insert_equal(reference value)
   {
      detail::key_nodeptr_comp<value_compare, splaytree_impl>
         key_node_comp(priv_comp(), this);
      node_ptr to_insert(get_real_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      iterator ret (node_algorithms::insert_equal_lower_bound
         (this->priv_header_ptr(), to_insert, key_node_comp), this);
      this->priv_size_traits().increment();
      return ret;
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      if(this->empty()){
         iterator iend(this->end());
         for (; b != e; ++b)
            this->insert_equal(iend, *b);
      }
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{
   typedef splaytree_impl<Config> tree_type;
   typedef typename tree_type::const_iterator const_iterator;

   if(tree_type::constant_time_size && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();
   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(tree_type::constant_time_size){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const splaytree_impl<T, Options...> &x, const splaytree_impl<T, Options...> &y)
#else
(const splaytree_impl<Config> &x, const splaytree_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(splaytree_impl<T, Options...> &x, splaytree_impl<T, Options...> &y)
#else
(splaytree_impl<Config> &x, splaytree_impl<Config> &y)
#endif
{  x.swap(y);  }


   splaytree( const value_compare &cmp = value_compare()
            , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   splaytree(BOOST_RV_REF(splaytree) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   splaytree& operator=(BOOST_RV_REF(splaytree) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static splaytree &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<splaytree &>(Base::container_from_end_iterator(end_iterator));   }


   static const splaytree &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const splaytree &>(Base::container_from_end_iterator(end_iterator));   }

   splaydown_rollback( const node_ptr *pcur_subtree, const node_ptr & header
                     , const node_ptr & leftmost           , const node_ptr & rightmost)
      : pcur_subtree_(pcur_subtree)  , header_(header)
      , leftmost_(leftmost)   , rightmost_(rightmost)
   {}


   void release()
   {  pcur_subtree_ = 0;  }


   ~splaydown_rollback()
   {
      if(pcur_subtree_){
         //Exception can only be thrown by comp, but
         //tree invariants still hold. *pcur_subtree is the current root
         //so link it to the header.
         NodeTraits::set_parent(*pcur_subtree_, header_);
         NodeTraits::set_parent(header_, *pcur_subtree_);
         //Recover leftmost/rightmost pointers
         NodeTraits::set_left (header_, leftmost_);
         NodeTraits::set_right(header_, rightmost_);
      }
   }

   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return tree_algorithms::begin_node(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return tree_algorithms::end_node(header);   }

   static bool unique(const const_node_ptr & node)
   {  return tree_algorithms::unique(node);  }


   static void unlink(const node_ptr & node)
   {  tree_algorithms::unlink(node);   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(tree_algorithms::get_header(node1)), header2(tree_algorithms::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {  tree_algorithms::swap_nodes(node1, header1, node2, header2);   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, tree_algorithms::get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {  tree_algorithms::replace_node(node_to_be_replaced, header, new_node);   }

   static node_ptr next_node(const node_ptr & p)
   {  return tree_algorithms::next_node(p); }

   static node_ptr prev_node(const node_ptr & p)
   {  return tree_algorithms::prev_node(p); }

   static void init(const node_ptr & node)
   {  tree_algorithms::init(node);  }

   static void init_header(const node_ptr & header)
   {  tree_algorithms::init_header(header);  }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {  tree_algorithms::clear_and_dispose(header, disposer); }

   static std::size_t count(const const_node_ptr & node)
   {  return tree_algorithms::count(node);   }

   static std::size_t size(const const_node_ptr & header)
   {  return tree_algorithms::size(header);   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {  return tree_algorithms::swap_tree(header1, header2);  }

   static void insert_unique_commit
      (const node_ptr & header, const node_ptr & new_value, const insert_commit_data &commit_data)
   {  tree_algorithms::insert_unique_commit(header, new_value, commit_data);  }

   bool operator()(const T &val, const T &val2) const
   {
      return priority_order(val, val2);
   }


   static pointer get_pointer(pointer n)
   {  return pointer(std::size_t(n) & ~Mask);  }


   static void set_pointer(pointer &n, pointer p)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(0 == (std::size_t(p) & Mask));
      n = pointer(std::size_t(p) | (std::size_t(n) & Mask));
   }


   static std::size_t get_bits(pointer n)
   {  return (std::size_t(n) & Mask);  }


   static void set_bits(pointer &n, std::size_t c)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(c <= Mask);
      n = pointer(std::size_t(get_pointer(n)) | c);
   }

      node_plus_pred_t(const value_compare &comp, const priority_compare &p_comp)
         :  detail::ebo_functor_holder<value_compare>(comp)
         ,  header_plus_priority_size_(p_comp)
      {}

         header_plus_priority_size(const priority_compare &p_comp)
            :  detail::ebo_functor_holder<priority_compare>(p_comp)
         {}

         header_plus_priority_size(const priority_compare &p_comp)
            :  detail::ebo_functor_holder<priority_compare>(p_comp)
         {}

      data_t(const value_compare & comp, const priority_compare &pcomp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp, pcomp)
      {}

      data_t(const value_compare & comp, const priority_compare &pcomp, const value_traits &val_traits)
         :  value_traits(val_traits), node_plus_pred_(comp, pcomp)
      {}


   const value_compare &priv_comp() const
   {  return data_.node_plus_pred_.get();  }


   value_compare &priv_comp()
   {  return data_.node_plus_pred_.get();  }


   const priority_compare &priv_pcomp() const
   {  return data_.node_plus_pred_.header_plus_priority_size_.get();  }


   priority_compare &priv_pcomp()
   {  return data_.node_plus_pred_.header_plus_priority_size_.get();  }


   const value_traits &priv_value_traits() const
   {  return data_;  }


   value_traits &priv_value_traits()
   {  return data_;  }


   node_ptr priv_header_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(data_.node_plus_pred_.header_plus_priority_size_.header_plus_size_.header_);  }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }


   size_traits &priv_size_traits()
   {  return data_.node_plus_pred_.header_plus_priority_size_.header_plus_size_;  }


   const real_value_traits &get_real_value_traits(detail::bool_<false>) const
   {  return data_;  }

   explicit treap_impl( const value_compare &cmp    = value_compare()
                      , const priority_compare &pcmp = priority_compare()
                      , const value_traits &v_traits = value_traits())
      :  data_(cmp, pcmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
   }

   template<class Iterator>
   treap_impl( bool unique, Iterator b, Iterator e
            , const value_compare &cmp     = value_compare()
            , const priority_compare &pcmp = priority_compare()
            , const value_traits &v_traits = value_traits())
      : data_(cmp, pcmp, v_traits)
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      if(unique)
         this->insert_unique(b, e);
      else
         this->insert_equal(b, e);
   }

   treap_impl(BOOST_RV_REF(treap_impl) x)
      : data_( ::boost::move(x.priv_comp())
             , ::boost::move(x.priv_pcomp())
             , ::boost::move(x.priv_value_traits()))
   {
      node_algorithms::init_header(this->priv_header_ptr());
      this->priv_size_traits().set_size(size_type(0));
      this->swap(x);
   }

   treap_impl& operator=(BOOST_RV_REF(treap_impl) x)
   {  this->swap(x); return *this;  }

   ~treap_impl()
   {}

   iterator begin()
   {  return iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   const_iterator cbegin() const
   {  return const_iterator (node_traits::get_left(this->priv_header_ptr()), this);   }

   iterator end()
   {  return iterator (this->priv_header_ptr(), this);  }

   const_iterator cend() const
   {  return const_iterator (uncast(this->priv_header_ptr()), this);  }

   iterator top()
   {  return this->empty() ? this->end() : iterator (node_traits::get_parent(this->priv_header_ptr()), this);   }

   const_iterator ctop() const
   {  return this->empty() ? this->cend() : const_iterator (node_traits::get_parent(this->priv_header_ptr()), this);   }

   reverse_iterator rbegin()
   {  return reverse_iterator(this->end());  }

   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(this->end());  }

   reverse_iterator rend()
   {  return reverse_iterator(this->begin());   }

   const_reverse_iterator crend() const
   {  return const_reverse_iterator(this->begin());   }

   reverse_iterator rtop()
   {  return reverse_iterator(this->top());  }

   const_reverse_iterator crtop() const
   {  return const_reverse_iterator(this->top());  }

   static treap_impl &container_from_end_iterator(iterator end_iterator)
   {  return priv_container_from_end_iterator(end_iterator);   }

   static treap_impl &container_from_iterator(iterator it)
   {  return priv_container_from_iterator(it);   }

   value_compare value_comp() const
   {  return this->priv_comp();   }

   priority_compare priority_comp() const
   {  return this->priv_pcomp();   }

   bool empty() const
   {  return node_algorithms::unique(this->priv_header_ptr());   }

   size_type size() const
   {
      if(constant_time_size)
         return this->priv_size_traits().get_size();
      else{
         return (size_type)node_algorithms::size(this->priv_header_ptr());
      }
   }

   void swap(treap_impl& other)
   {
      //This can throw
      using std::swap;
      swap(priv_comp(), priv_comp());
      swap(priv_pcomp(), priv_pcomp());
      //These can't throw
      node_algorithms::swap_tree(this->priv_header_ptr(), other.priv_header_ptr());
      if(constant_time_size){
         size_type backup = this->priv_size_traits().get_size();
         this->priv_size_traits().set_size(other.priv_size_traits().get_size());
         other.priv_size_traits().set_size(backup);
      }
   }

   iterator insert_equal(reference value)
   {
      detail::key_nodeptr_comp<value_compare, treap_impl>
         key_node_comp(priv_comp(), this);
      detail::key_nodeptr_comp<priority_compare, treap_impl>
         key_node_pcomp(priv_pcomp(), this);
      node_ptr to_insert(get_real_value_traits().to_node_ptr(value));
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(to_insert));
      iterator ret(node_algorithms::insert_equal_upper_bound
         (this->priv_header_ptr(), to_insert, key_node_comp, key_node_pcomp), this);
      this->priv_size_traits().increment();
      return ret;
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      iterator iend(this->end());
      for (; b != e; ++b)
         this->insert_equal(iend, *b);
   }

template<class Config>
#endif
inline bool operator<
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template<class Config>
#endif
bool operator==
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{
   typedef treap_impl<Config> tree_type;
   typedef typename tree_type::const_iterator const_iterator;

   if(tree_type::constant_time_size && x.size() != y.size()){
      return false;
   }
   const_iterator end1 = x.end();
   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(tree_type::constant_time_size){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const treap_impl<T, Options...> &x, const treap_impl<T, Options...> &y)
#else
(const treap_impl<Config> &x, const treap_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(treap_impl<T, Options...> &x, treap_impl<T, Options...> &y)
#else
(treap_impl<Config> &x, treap_impl<Config> &y)
#endif
{  x.swap(y);  }


   treap( const value_compare &cmp = value_compare()
       , const priority_compare &pcmp = priority_compare()
       , const value_traits &v_traits = value_traits())
      :  Base(cmp, pcmp, v_traits)
   {}


   treap(BOOST_RV_REF(treap) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   treap& operator=(BOOST_RV_REF(treap) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static treap &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<treap &>(Base::container_from_end_iterator(end_iterator));   }


   static const treap &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const treap &>(Base::container_from_end_iterator(end_iterator));   }


   static treap &container_from_it(iterator it)
   {  return static_cast<treap &>(Base::container_from_iterator(it));   }


   static const treap &container_from_it(const_iterator it)
   {  return static_cast<const treap &>(Base::container_from_iterator(it));   }

template<class Parent, class Member>
inline Parent *get_parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

template<class Parent, class Member>
inline const Parent *get_parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{  return ::boost::intrusive::detail::parent_from_member(member, ptr_to_member);  }

      remove_on_destroy(const node_ptr & header, const node_ptr & z)
         :  header_(header), z_(z), remove_it_(true)
      {}

      ~remove_on_destroy()
      {
         if(remove_it_){
            tree_algorithms::erase(header_, z_);
         }
      }


      void release()
      {  remove_it_ = false;  }


      ~rerotate_on_destroy()
      {
         if(remove_it_){
            rotate_up_n(header_, p_, n_);
         }
      }


      void release()
      {  remove_it_ = false;  }


   static void rotate_up_n(const node_ptr header, const node_ptr p, std::size_t n)
   {
      for( node_ptr p_parent = NodeTraits::get_parent(p)
         ; n--
         ; p_parent = NodeTraits::get_parent(p)){
         //Check if left child
         if(p == NodeTraits::get_left(p_parent)){
            tree_algorithms::rotate_right(p_parent, header);
         }
         else{ //Right child
            tree_algorithms::rotate_left(p_parent, header);
         }
      }
   }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return tree_algorithms::begin_node(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return tree_algorithms::end_node(header);   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {  return tree_algorithms::swap_tree(header1, header2);  }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(tree_algorithms::get_header(node1)), header2(tree_algorithms::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {  tree_algorithms::swap_nodes(node1, header1, node2, header2);  }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, tree_algorithms::get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {  tree_algorithms::replace_node(node_to_be_replaced, header, new_node);  }

   template<class NodePtrPriorityCompare>
   static void unlink(const node_ptr & node, NodePtrPriorityCompare pcomp)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node, pcomp);
      }
   }

   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header)
   {  return tree_algorithms::unlink_leftmost_without_rebalance(header);   }

   static bool unique(const const_node_ptr & node)
   {  return tree_algorithms::unique(node);  }

   static std::size_t count(const const_node_ptr & node)
   {  return tree_algorithms::count(node);   }

   static std::size_t size(const const_node_ptr & header)
   {  return tree_algorithms::size(header);   }

   static node_ptr next_node(const node_ptr & p)
   {  return tree_algorithms::next_node(p); }

   static node_ptr prev_node(const node_ptr & p)
   {  return tree_algorithms::prev_node(p); }

   static void init(const node_ptr & node)
   {  tree_algorithms::init(node);  }

   static void init_header(const node_ptr & header)
   {
      tree_algorithms::init_header(header);
   }

   template<class NodePtrPriorityCompare>
   static node_ptr erase(const node_ptr & header, const node_ptr & z, NodePtrPriorityCompare pcomp)
   {
      rebalance_for_erasure(header, z, pcomp);
      tree_algorithms::erase(header, z);
      return z;
   }

   template <class Cloner, class Disposer>
   static void clone
      (const const_node_ptr & source_header, const node_ptr & target_header, Cloner cloner, Disposer disposer)
   {
      tree_algorithms::clone(source_header, target_header, cloner, disposer);
   }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {  tree_algorithms::clear_and_dispose(header, disposer); }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::lower_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::upper_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::find(header, key, comp);  }

   explicit avl_set_impl( const value_compare &cmp = value_compare()
                        , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   avl_set_impl( Iterator b, Iterator e
           , const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      : tree_(true, b, e, cmp, v_traits)
   {}

   avl_set_impl(BOOST_RV_REF(avl_set_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   avl_set_impl& operator=(BOOST_RV_REF(avl_set_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~avl_set_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static avl_set_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<avl_set_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &avl_set_impl::tree_);
   }

   static avl_set_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<avl_set_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &avl_set_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(avl_set_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const avl_set_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y)
#else
(const avl_set_impl<Config> &x, const avl_set_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y)
#else
(const avl_set_impl<Config> &x, const avl_set_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y)
#else
(const avl_set_impl<Config> &x, const avl_set_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_set_impl<T, Options...> &x, const avl_set_impl<T, Options...> &y)
#else
(const avl_set_impl<Config> &x, const avl_set_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(avl_set_impl<T, Options...> &x, avl_set_impl<T, Options...> &y)
#else
(avl_set_impl<Config> &x, avl_set_impl<Config> &y)
#endif
{  x.swap(y);  }


   avl_set( const value_compare &cmp = value_compare()
         , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   avl_set(BOOST_RV_REF(avl_set) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   avl_set& operator=(BOOST_RV_REF(avl_set) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static avl_set &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avl_set &>(Base::container_from_end_iterator(end_iterator));   }


   static const avl_set &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_set &>(Base::container_from_end_iterator(end_iterator));   }


   static avl_set &container_from_iterator(iterator end_iterator)
   {  return static_cast<avl_set &>(Base::container_from_iterator(end_iterator));   }


   static const avl_set &container_from_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_set &>(Base::container_from_iterator(end_iterator));   }

   explicit avl_multiset_impl( const value_compare &cmp = value_compare()
                             , const value_traits &v_traits = value_traits())
      :  tree_(cmp, v_traits)
   {}

   template<class Iterator>
   avl_multiset_impl( Iterator b, Iterator e
                , const value_compare &cmp = value_compare()
                , const value_traits &v_traits = value_traits())
      : tree_(false, b, e, cmp, v_traits)
   {}

   avl_multiset_impl(BOOST_RV_REF(avl_multiset_impl) x)
      :  tree_(::boost::move(x.tree_))
   {}

   avl_multiset_impl& operator=(BOOST_RV_REF(avl_multiset_impl) x)
   {  tree_ = ::boost::move(x.tree_);  return *this;  }

   ~avl_multiset_impl()
   {}

   iterator begin()
   { return tree_.begin();  }

   const_iterator begin() const
   { return tree_.begin();  }

   const_iterator cbegin() const
   { return tree_.cbegin();  }

   iterator end()
   { return tree_.end();  }

   const_iterator end() const
   { return tree_.end();  }

   const_iterator cend() const
   { return tree_.cend();  }

   reverse_iterator rbegin()
   { return tree_.rbegin();  }

   const_reverse_iterator rbegin() const
   { return tree_.rbegin();  }

   const_reverse_iterator crbegin() const
   { return tree_.crbegin();  }

   reverse_iterator rend()
   { return tree_.rend();  }

   const_reverse_iterator rend() const
   { return tree_.rend();  }

   const_reverse_iterator crend() const
   { return tree_.crend();  }

   static avl_multiset_impl &container_from_end_iterator(iterator end_iterator)
   {
      return *detail::parent_from_member<avl_multiset_impl, tree_type>
         ( &tree_type::container_from_end_iterator(end_iterator)
         , &avl_multiset_impl::tree_);
   }

   static avl_multiset_impl &container_from_iterator(iterator it)
   {
      return *detail::parent_from_member<avl_multiset_impl, tree_type>
         ( &tree_type::container_from_iterator(it)
         , &avl_multiset_impl::tree_);
   }

   key_compare key_comp() const
   { return tree_.value_comp(); }

   value_compare value_comp() const
   { return tree_.value_comp(); }

   bool empty() const
   { return tree_.empty(); }

   size_type size() const
   { return tree_.size(); }

   void swap(avl_multiset_impl& other)
   { tree_.swap(other.tree_); }

   template <class Cloner, class Disposer>
   void clone_from(const avl_multiset_impl &src, Cloner cloner, Disposer disposer)
   {  tree_.clone_from(src.tree_, cloner, disposer);  }

   iterator insert(reference value)
   {  return tree_.insert_equal(value);  }

   iterator insert(const_iterator hint, reference value)
   {  return tree_.insert_equal(hint, value);  }

   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  tree_.insert_equal(b, e);  }

   iterator insert_before(const_iterator pos, reference value)
   {  return tree_.insert_before(pos, value);  }

   void push_back(reference value)
   {  tree_.push_back(value);  }

   void push_front(reference value)
   {  tree_.push_front(value);  }

   iterator erase(const_iterator i)
   {  return tree_.erase(i);  }

   iterator erase(const_iterator b, const_iterator e)
   {  return tree_.erase(b, e);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {  return tree_.erase_and_dispose(i, disposer);  }

   template<class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {  return tree_.erase_and_dispose(b, e, disposer);  }

   void clear()
   {  return tree_.clear();  }

   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  return tree_.clear_and_dispose(disposer);  }

   size_type count(const_reference value) const
   {  return tree_.count(value);  }

   template<class KeyType, class KeyValueCompare>
   size_type count(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.count(key, comp);  }

   iterator lower_bound(const_reference value)
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator lower_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.lower_bound(key, comp);  }

   const_iterator lower_bound(const_reference value) const
   {  return tree_.lower_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator lower_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.lower_bound(key, comp);  }

   iterator upper_bound(const_reference value)
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator upper_bound(const KeyType& key, KeyValueCompare comp)
   {  return tree_.upper_bound(key, comp);  }

   const_iterator upper_bound(const_reference value) const
   {  return tree_.upper_bound(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator upper_bound(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.upper_bound(key, comp);  }

   iterator find(const_reference value)
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   iterator find(const KeyType& key, KeyValueCompare comp)
   {  return tree_.find(key, comp);  }

   const_iterator find(const_reference value) const
   {  return tree_.find(value);  }

   template<class KeyType, class KeyValueCompare>
   const_iterator find(const KeyType& key, KeyValueCompare comp) const
   {  return tree_.find(key, comp);  }

template<class Config>
#endif
inline bool operator!=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y)
#else
(const avl_multiset_impl<Config> &x, const avl_multiset_impl<Config> &y)
#endif
{  return !(x == y); }

template<class Config>
#endif
inline bool operator>
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y)
#else
(const avl_multiset_impl<Config> &x, const avl_multiset_impl<Config> &y)
#endif
{  return y < x;  }

template<class Config>
#endif
inline bool operator<=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y)
#else
(const avl_multiset_impl<Config> &x, const avl_multiset_impl<Config> &y)
#endif
{  return !(y < x);  }

template<class Config>
#endif
inline bool operator>=
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(const avl_multiset_impl<T, Options...> &x, const avl_multiset_impl<T, Options...> &y)
#else
(const avl_multiset_impl<Config> &x, const avl_multiset_impl<Config> &y)
#endif
{  return !(x < y);  }

template<class Config>
#endif
inline void swap
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
(avl_multiset_impl<T, Options...> &x, avl_multiset_impl<T, Options...> &y)
#else
(avl_multiset_impl<Config> &x, avl_multiset_impl<Config> &y)
#endif
{  x.swap(y);  }


   avl_multiset( const value_compare &cmp = value_compare()
           , const value_traits &v_traits = value_traits())
      :  Base(cmp, v_traits)
   {}


   avl_multiset(BOOST_RV_REF(avl_multiset) x)
      :  Base(::boost::move(static_cast<Base&>(x)))
   {}


   avl_multiset& operator=(BOOST_RV_REF(avl_multiset) x)
   {  this->Base::operator=(::boost::move(static_cast<Base&>(x))); return *this;  }


   static avl_multiset &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static const avl_multiset &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_multiset &>(Base::container_from_end_iterator(end_iterator));   }


   static avl_multiset &container_from_iterator(iterator end_iterator)
   {  return static_cast<avl_multiset &>(Base::container_from_iterator(end_iterator));   }


   static const avl_multiset &container_from_iterator(const_iterator end_iterator)
   {  return static_cast<const avl_multiset &>(Base::container_from_iterator(end_iterator));   }


   static node_ptr to_node_ptr(reference value)
   {  return node_ptr(&(value.*PtrToMember));   }


   static const_node_ptr to_node_ptr(const_reference value)
   {  return node_ptr(&(value.*PtrToMember));   }


   static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer(detail::parent_from_member<value_type, node>
         (boost::intrusive::detail::to_raw_pointer(n), PtrToMember));
   }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return tree_algorithms::begin_node(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return tree_algorithms::end_node(header);   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {  return tree_algorithms::swap_tree(header1, header2);  }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(tree_algorithms::get_header(node1)), header2(tree_algorithms::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {  tree_algorithms::swap_nodes(node1, header1, node2, header2);  }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, tree_algorithms::get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {  tree_algorithms::replace_node(node_to_be_replaced, header, new_node);  }

   static void unlink(const node_ptr & node)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         tree_algorithms::erase(x, node);
      }
   }

   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header)
   {  return tree_algorithms::unlink_leftmost_without_rebalance(header);   }

   static bool unique(const const_node_ptr & node)
   {  return tree_algorithms::unique(node);  }

   static std::size_t count(const const_node_ptr & node)
   {  return tree_algorithms::count(node);   }

   static std::size_t size(const const_node_ptr & header)
   {  return tree_algorithms::size(header);   }

   static node_ptr next_node(const node_ptr & p)
   {  return tree_algorithms::next_node(p); }

   static node_ptr prev_node(const node_ptr & p)
   {  return tree_algorithms::prev_node(p); }

   static void init(const node_ptr & node)
   {  tree_algorithms::init(node);  }

   static void init_header(const node_ptr & header)
   {  tree_algorithms::init_header(header);  }

   template<class AlphaByMaxSize>
   static node_ptr erase(const node_ptr & header, const node_ptr & z, std::size_t tree_size, std::size_t &max_tree_size, AlphaByMaxSize alpha_by_maxsize)
   {
      //typename tree_algorithms::data_for_rebalance info;
      tree_algorithms::erase(header, z);
      --tree_size;
      if (tree_size > 0 &&
          tree_size < alpha_by_maxsize(max_tree_size)){
         tree_algorithms::rebalance(header);
         max_tree_size = tree_size;
      }
      return z;
   }

   template <class Cloner, class Disposer>
   static void clone
      (const const_node_ptr & source_header, const node_ptr & target_header, Cloner cloner, Disposer disposer)
   {
      tree_algorithms::clone(source_header, target_header, cloner, disposer);
   }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {  tree_algorithms::clear_and_dispose(header, disposer); }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::lower_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::upper_bound(header, key, comp);  }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {  return tree_algorithms::find(header, key, comp);  }


   static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->parent_ = p;  }


   static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->left_ = l;  }


   static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->right_ = r;  }



   tree_iterator()
      : members_ (node_ptr(), (const void *)0)
   {}


   explicit tree_iterator(const node_ptr & nodeptr, const Container *cont_ptr)
      : members_ (nodeptr, cont_ptr)
   {}


   tree_iterator(tree_iterator<Container, false> const& other)
      :  members_(other.pointed_node(), other.get_container())
   {}


   const node_ptr &pointed_node() const
   { return members_.nodeptr_; }


   tree_iterator &operator=(const node_ptr &nodeptr)
   {  members_.nodeptr_ = nodeptr;  return static_cast<tree_iterator&>(*this);  }

   tree_iterator& operator++()
   {
      members_.nodeptr_ = node_algorithms::next_node(members_.nodeptr_);
      return static_cast<tree_iterator&> (*this);
   }


   tree_iterator operator++(int)
   {
      tree_iterator result (*this);
      members_.nodeptr_ = node_algorithms::next_node(members_.nodeptr_);
      return result;
   }


   tree_iterator& operator--()
   {
      members_.nodeptr_ = node_algorithms::prev_node(members_.nodeptr_);
      return static_cast<tree_iterator&> (*this);
   }


   tree_iterator operator--(int)
   {
      tree_iterator result (*this);
      members_.nodeptr_ = node_algorithms::prev_node(members_.nodeptr_);
      return result;
   }


   reference operator*() const
   {  return *operator->();   }


   pointer operator->() const
   { return this->get_real_value_traits()->to_value_ptr(members_.nodeptr_); }


   const Container *get_container() const
   {  return static_cast<const Container*>(members_.get_ptr());   }


   const real_value_traits *get_real_value_traits() const
   {  return &this->get_container()->get_real_value_traits();  }


   tree_iterator end_iterator_from_it() const
   {
      return tree_iterator(node_algorithms::get_header(this->pointed_node()), this->get_container());
   }


   tree_iterator<Container, false> unconst() const
   {  return tree_iterator<Container, false>(this->pointed_node(), this->get_container());   }


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


   static const node_ptr &get_next(const const_node_ptr & n)
   {  return n->node_ptr_1;  }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->node_ptr_1 = next;  }


   static const node_ptr &get_previous(const const_node_ptr & n)
   {  return n->node_ptr_2;  }


   static void set_previous(const node_ptr & n, const node_ptr & prev)
   {  n->node_ptr_2 = prev;  }


   static const node_ptr &get_next(const const_node_ptr & n)
   {  return n->node_ptr_1;  }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->node_ptr_1 = next;  }


   static const node_ptr &get_next(const const_node_ptr & n)
   {  return n->node_ptr_1;   }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->node_ptr_1 = next;  }


   static node_ptr get_prev_in_group(const const_node_ptr & n)
   {  return n->node_ptr_2;  }


   static void set_prev_in_group(const node_ptr & n, const node_ptr & prev)
   {  n->node_ptr_2 = prev;  }


   static std::size_t get_hash(const const_node_ptr & n)
   {  return n->size_t_1;  }


   static void set_hash(const node_ptr & n, std::size_t h)
   {  n->size_t_1 = h;  }


   static const node_ptr &get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->node_ptr_1 = p;  }


   static const node_ptr &get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->node_ptr_2 = l;  }


   static const node_ptr &get_right(const const_node_ptr & n)
   {  return n->node_ptr_3;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->node_ptr_3 = r;  }


   static color get_color(const const_node_ptr & n)
   {  return n->size_t_1;  }


   static void set_color(const node_ptr & n, color c)
   {  n->size_t_1 = c;  }


   static color black()
   {  return 0u;  }


   static color red()
   {  return 1u;  }


   static const node_ptr &get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->node_ptr_1 = p;  }


   static const node_ptr &get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->node_ptr_2 = l;  }


   static const node_ptr &get_right(const const_node_ptr & n)
   {  return n->node_ptr_3;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->node_ptr_3 = r;  }


   static balance get_balance(const const_node_ptr & n)
   {  return n->size_t_1;  }


   static void set_balance(const node_ptr & n, balance b)
   {  n->size_t_1 = b;  }


   static balance negative()
   {  return 0u;  }


   static balance zero()
   {  return 1u;  }


   static balance positive()
   {  return 2u;  }


   static const node_ptr &get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->node_ptr_1 = p;  }


   static const node_ptr &get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->node_ptr_2 = l;  }


   static const node_ptr &get_right(const const_node_ptr & n)
   {  return n->node_ptr_3;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->node_ptr_3 = r;  }

   template <class T>
   static void function_not_available_for_any_hooks(typename detail::enable_if<detail::is_same<T, bool> >::type)
   {}

   static void init(const node_ptr & node)
   {  node->node_ptr_1 = 0;   };

   static bool inited(const const_node_ptr & node)
   {  return !node->node_ptr_1;  };


   static bool unique(const const_node_ptr & node)
   {  return 0 == node->node_ptr_1; }


   static void unlink(const node_ptr &)
   {
      //Auto-unlink hooks and unlink() are not available for any hooks
      any_algorithms<VoidPointer>::template function_not_available_for_any_hooks<node_ptr>();
   }


   static void swap_nodes(const node_ptr & l, const node_ptr & r)
   {
      //Any nodes have no swap_nodes capability because they don't know
      //what algorithm they must use to unlink the node from the container
      any_algorithms<VoidPointer>::template function_not_available_for_any_hooks<node_ptr>();
   }

   ~clear_on_destructor_base()
   {
      static_cast<Derived*>(this)->clear();
   }


   static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->parent_ = p;  }


   static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->left_ = l;  }


   static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->right_ = r;  }


   static balance get_balance(const const_node_ptr & n)
   {  return n->balance_;  }


   static void set_balance(const node_ptr & n, balance b)
   {  n->balance_ = b;  }


   static balance negative()
   {  return node::negative_t;  }


   static balance zero()
   {  return node::zero_t;  }


   static balance positive()
   {  return node::positive_t;  }


   static node_ptr get_parent(const const_node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  ptr_bit::set_pointer(n->parent_, p);  }


   static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->left_ = l;  }


   static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->right_ = r;  }


   static balance get_balance(const const_node_ptr & n)
   {  return (balance)ptr_bit::get_bits(n->parent_);  }


   static void set_balance(const node_ptr & n, balance b)
   {  ptr_bit::set_bits(n->parent_, (std::size_t)b);  }


   static balance negative()
   {  return node::negative_t;  }


   static balance zero()
   {  return node::zero_t;  }


   static balance positive()
   {  return node::positive_t;  }

   ebo_functor_holder_impl()
   {}

   ebo_functor_holder_impl(const T& t)
      :  t_(t)
   {}

   template<class Arg1, class Arg2>
   ebo_functor_holder_impl(const Arg1& arg1, const Arg2& arg2)
      :  t_(arg1, arg2)
   {}


   T&       get(){return t_;}

   const T& get()const{return t_;}

   ebo_functor_holder_impl()
   {}

   ebo_functor_holder_impl(const T& t)
      :  T(t)
   {}

   template<class Arg1, class Arg2>
   ebo_functor_holder_impl(const Arg1& arg1, const Arg2& arg2)
      :  T(arg1, arg2)
   {}


   T&       get(){return *this;}

   const T& get()const{return *this;}

   ebo_functor_holder(){}

   ebo_functor_holder(const T& t)
      :  super(t)
   {}


   template<class Arg1, class Arg2>
   ebo_functor_holder(const Arg1& arg1, const Arg2& arg2)
      :  super(arg1, arg2)
   {}


   ebo_functor_holder& operator=(const ebo_functor_holder& x)
   {
      this->get()=x.get();
      return *this;
   }


   static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->next_ = next;  }


   slist_iterator()
      : members_ (node_ptr(), 0)
   {}


   explicit slist_iterator(const node_ptr & node, const Container *cont_ptr)
      : members_ (node, cont_ptr)
   {}


   slist_iterator(slist_iterator<Container, false> const& other)
      :  members_(other.pointed_node(), other.get_container())
   {}


   const node_ptr &pointed_node() const
   { return members_.nodeptr_; }


   slist_iterator &operator=(const node_ptr &node)
   {  members_.nodeptr_ = node;  return static_cast<slist_iterator&>(*this);  }

   slist_iterator& operator++()
   {
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return static_cast<slist_iterator&> (*this);
   }


   slist_iterator operator++(int)
   {
      slist_iterator result (*this);
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return result;
   }


   reference operator*() const
   {  return *operator->();   }


   pointer operator->() const
   { return this->get_real_value_traits()->to_value_ptr(members_.nodeptr_); }


   const Container *get_container() const
   {
      if(store_container_ptr)
         return static_cast<const Container*>(members_.get_ptr());
      else
         return 0;
   }


   slist_iterator<Container, false> unconst() const
   {  return slist_iterator<Container, false>(this->pointed_node(), this->get_container());   }


   const real_value_traits *get_real_value_traits() const
   {
      if(store_container_ptr)
         return &this->get_container()->get_real_value_traits();
      else
         return 0;
   }


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


template <class T>
inline T* to_raw_pointer(T* p)
{  return p; }

   template <class Pointer>
   void operator()(Pointer)
   {}

   void operator()(const node_ptr & p)
   {  NodeAlgorithms::init(p);   }


   SizeType get_size() const
   {  return size_;  }


   void set_size(SizeType size)
   {  size_ = size; }


   void decrement()
   {  --size_; }


   void increment()
   {  ++size_; }


   void increase(SizeType n)
   {  size_ += n; }


   void decrease(SizeType n)
   {  size_ -= n; }


   size_type get_size() const
   {  return 0;  }


   void set_size(size_type)
   {}


   void decrement()
   {}


   void increment()
   {}


   void increase(SizeType)
   {}


   void decrease(SizeType)
   {}

   key_nodeptr_comp(KeyValueCompare kcomp, const Container *cont)
      :  base_t(kcomp), cont_(cont)
   {}


   template<class T>
   const value_type & key_forward
      (const T &node, typename enable_if_c<is_node_ptr<T>::value>::type * = 0) const
   {  return *cont_->get_real_value_traits().to_value_ptr(node);  }



   template<class KeyType, class KeyType2>
   bool operator()(const KeyType &key1, const KeyType2 &key2) const
   {  return base_t::get()(this->key_forward(key1), this->key_forward(key2));  }


   node_cloner(F f, const Container *cont)
      :  base_t(f), cont_(cont)
   {}


   node_ptr operator()(const node_ptr & p)
   {  return this->operator()(*p); }


   node_ptr operator()(const node &to_clone)
   {
      const value_type &v =
         *cont_->get_real_value_traits().to_value_ptr
            (pointer_traits<const_node_ptr>::pointer_to(to_clone));
      node_ptr n = cont_->get_real_value_traits().to_node_ptr(*base_t::get()(v));
      //Cloned node must be in default mode if the linking mode requires it
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(node_algorithms::unique(n));
      return n;
   }


   node_disposer(F f, const Container *cont)
      :  base_t(f), cont_(cont)
   {}


   void operator()(const node_ptr & p)
   {
      if(safemode_or_autounlink)
         node_algorithms::init(p);
      base_t::get()(cont_->get_real_value_traits().to_value_ptr(p));
   }

   dummy_constptr(const void *)
   {}


   const void *get_ptr() const
   {  return 0;  }


   constptr(const void *ptr)
      :  const_void_ptr_(ptr)
   {}


   const void *get_ptr() const
   {  return boost::intrusive::detail::to_raw_pointer(const_void_ptr_);  }


template<class Hook>
void destructor_impl(Hook &hook, detail::link_dispatch<safe_link>)
{  //If this assertion raises, you might have destroyed an object
   //while it was still inserted in a container that is alive.
   //If so, remove the object from the container before destroying it.
   (void)hook; BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT(!hook.is_linked());
}


   static pointer to_value_ptr(const node_ptr & n)
   {
      return pointer_traits<pointer>::pointer_to
         (static_cast<reference>(static_cast<node_holder_reference>(*n)));
   }


   static node_ptr to_node_ptr(reference value)
   {
      return pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<node_holder_reference>(value)));
   }


   static const_node_ptr to_node_ptr(const_reference value)
   {
      return pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_node_holder_reference>(value)));
   }


   static node_ptr to_node_ptr(reference value)
   {
      return pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<hook_reference>(value.*P)));
   }


   static const_node_ptr to_node_ptr(const_reference value)
   {
      return pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_hook_reference>(value.*P)));
   }


   static pointer to_value_ptr(const node_ptr & n)
   {
      return pointer_traits<pointer>::pointer_to
         (*detail::parent_from_member<T, Hook>
            (static_cast<Hook*>(boost::intrusive::detail::to_raw_pointer(n)), P));
   }


   static node_ptr to_node_ptr(reference value)
   {  return static_cast<node*>(boost::intrusive::detail::to_raw_pointer(Functor::to_hook_ptr(value)));  }


   static const_node_ptr to_node_ptr(const_reference value)
   {  return static_cast<const node*>(boost::intrusive::detail::to_raw_pointer(Functor::to_hook_ptr(value)));  }


   static pointer to_value_ptr(const node_ptr & n)
   {  return Functor::to_value_ptr(to_hook_ptr(n));  }

   static hook_ptr to_hook_ptr(const node_ptr & n)
   {  return hook_ptr(&*static_cast<hook_type*>(&*n));  }


   static const_hook_ptr to_hook_ptr(const const_node_ptr & n)
   {  return const_hook_ptr(&*static_cast<const hook_type*>(&*n));  }

inline std::size_t floor_log2 (std::size_t x)
{
   const std::size_t Bits = sizeof(std::size_t)*CHAR_BIT;
   const bool Size_t_Bits_Power_2= !(Bits & (Bits-1));
   BOOST_STATIC_ASSERT(Size_t_Bits_Power_2);

   std::size_t n = x;
   std::size_t log2 = 0;

   for(std::size_t shift = Bits >> 1; shift; shift >>= 1){
      std::size_t tmp = n >> shift;
      if (tmp)
         log2 += shift, n = tmp;
   }

   return log2;
}


inline float fast_log2 (float val)
{
   union caster_t
   {
      boost::uint32_t x;
      float val;
   } caster;

   caster.val = val;
   boost::uint32_t x = caster.x;
   const int log_2 = (int)(((x >> 23) & 255) - 128);
   x &= ~(255 << 23);
   x += 127 << 23;
   caster.x = x;
   val = caster.val;
   val = ((-1.0f/3.f) * val + 2.f) * val - (2.0f/3.f);

   return (val + log_2);
}


inline std::size_t ceil_log2 (std::size_t x)
{
   return ((x & (x-1))!= 0) + floor_log2(x);
}

inline std::size_t sqrt2_pow_2xplus1 (std::size_t x)
{
   const std::size_t value = (std::size_t)sqrt2_pow_max<std::size_t>::value;
   const std::size_t pow   = (std::size_t)sqrt2_pow_max<std::size_t>::pow;
   return (value >> (pow - x)) + 1;
}

   exception_disposer(Container &cont, Disposer &disp)
      :  cont_(&cont), disp_(disp)
   {}


   void release()
   {  cont_ = 0;  }


   ~exception_disposer()
   {
      if(cont_){
         cont_->clear_and_dispose(disp_);
      }
   }


   exception_array_disposer
      (Container &cont, Disposer &disp, SizeType &constructed)
      :  cont_(&cont), disp_(disp), constructed_(constructed)
   {}


   void release()
   {  cont_ = 0;  }


   ~exception_array_disposer()
   {
      SizeType n = constructed_;
      if(cont_){
         while(n--){
            cont_[n].clear_and_dispose(disp_);
         }
      }
   }

   template<class CommonInitializer>
   array_initializer(const CommonInitializer &init)
   {
      char *init_buf = (char*)rawbuf;
      std::size_t i = 0;
      BOOST_TRY{
         for(; i != N; ++i){
            new(init_buf)T(init);
            init_buf += sizeof(T);
         }
      }
      BOOST_CATCH(...){
         while(i--){
            init_buf -= sizeof(T);
            ((T*)init_buf)->~T();
         }
         BOOST_RETHROW;
      }
      BOOST_CATCH_END
   }


   operator T* ()
   {  return (T*)(rawbuf);  }


   operator const T*() const
   {  return (const T*)(rawbuf);  }


   ~array_initializer()
   {
      char *init_buf = (char*)rawbuf + N*sizeof(T);
      for(std::size_t i = 0; i != N; ++i){
         init_buf -= sizeof(T);
         ((T*)init_buf)->~T();
      }
   }


	reverse_iterator(){}


	explicit reverse_iterator(It r)
		: m_current(r)
   {}


	template<class OtherIt>
	reverse_iterator(const reverse_iterator<OtherIt>& r)
	   : m_current(r.base())
	{}


	It base() const
   {  return m_current;  }


	reference operator*() const
   {  It temp(m_current);   --temp; return *temp; }


	pointer operator->() const
   {  It temp(m_current);   --temp; return temp.operator->(); }


	reference operator[](difference_type off) const
	{  return this->m_current[-off];  }


	reverse_iterator& operator++()
   {  --m_current;   return *this;   }


	reverse_iterator operator++(int)
	{
		reverse_iterator temp = *this;
		--m_current;
		return temp;
	}


	reverse_iterator& operator--()
	{
	   ++m_current;
		return *this;
   }


	reverse_iterator operator--(int)
	{
	   reverse_iterator temp(*this);
	   ++m_current;
	   return temp;
	}


	reverse_iterator& operator+=(difference_type off)
	{  m_current -= off; return *this;  }


	reverse_iterator& operator-=(difference_type off)
	{  m_current += off; return *this;  }

   bucket_impl()
   {}


   bucket_impl(const bucket_impl &)
   {}


   ~bucket_impl()
   {
      //This bucket is still being used!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
   }


   bucket_impl &operator=(const bucket_impl&)
   {
      //This bucket is still in use!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
      //Slist::clear();
      return *this;
   }


   bucket_traits_impl(bucket_ptr buckets, size_type len)
      :  buckets_(buckets), buckets_len_(len)
   {}


   bucket_traits_impl(const bucket_traits_impl &x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {}



   bucket_traits_impl(BOOST_RV_REF(bucket_traits_impl) x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {  x.buckets_ = bucket_ptr();   x.buckets_len_ = 0;  }


   bucket_traits_impl& operator=(BOOST_RV_REF(bucket_traits_impl) x)
   {
      buckets_ = x.buckets_; buckets_len_ = x.buckets_len_;
      x.buckets_ = bucket_ptr();   x.buckets_len_ = 0; return *this;
   }


   const bucket_ptr &bucket_begin() const
   {  return buckets_;  }


   size_type  bucket_count() const
   {  return buckets_len_;  }


   static typename Container::node_ptr downcast_bucket(typename bucket_type::node_ptr p)
   {
      return pointer_traits<typename Container::node_ptr>::
         pointer_to(static_cast<typename Container::node&>(*p));
   }


   hashtable_iterator ()
   {}


   explicit hashtable_iterator(siterator ptr, const Container *cont)
      :  slist_it_ (ptr),   cont_ (cont ? pointer_traits<const_cont_ptr>::pointer_to(*cont) : const_cont_ptr() )
   {}


   hashtable_iterator(const hashtable_iterator<Container, false> &other)
      :  slist_it_(other.slist_it()), cont_(other.get_container())
   {}


   const siterator &slist_it() const
   { return slist_it_; }


   hashtable_iterator<Container, false> unconst() const
   {  return hashtable_iterator<Container, false>(this->slist_it(), this->get_container());   }

   hashtable_iterator& operator++()
   {  this->increment();   return *this;   }


   hashtable_iterator operator++(int)
   {
      hashtable_iterator result (*this);
      this->increment();
      return result;
   }


   reference operator*() const
   { return *this->operator ->(); }


   pointer operator->() const
   {
      return boost::intrusive::detail::to_raw_pointer(this->get_real_value_traits()->to_value_ptr
         (downcast_bucket(slist_it_.pointed_node())));
   }


   const const_cont_ptr &get_container() const
   {  return cont_;  }


   const real_value_traits *get_real_value_traits() const
   {  return &this->get_container()->get_real_value_traits();  }

   void increment()
   {
      const Container *cont =  boost::intrusive::detail::to_raw_pointer(cont_);
      bucket_type* buckets = boost::intrusive::detail::to_raw_pointer(cont->bucket_pointer());
      size_type   buckets_len    = cont->bucket_count();

      ++slist_it_;
      if(buckets[0].cend().pointed_node()    <= slist_it_.pointed_node() &&
         slist_it_.pointed_node()<= buckets[buckets_len].cend().pointed_node()      ){
         //Now get the bucket_impl from the iterator
         const bucket_type &b = static_cast<const bucket_type&>
            (bucket_type::slist_type::container_from_end_iterator(slist_it_));

         //Now just calculate the index b has in the bucket array
         size_type n_bucket = static_cast<size_type>(&b - &buckets[0]);
         do{
            if (++n_bucket == buckets_len){
               slist_it_ = (&buckets[0] + buckets_len)->end();
               break;
            }
            slist_it_ = buckets[n_bucket].begin();
         }
         while (slist_it_ == buckets[n_bucket].end());
      }
   }


template <typename T>
inline T* addressof(T& obj)
{
   return static_cast<T*>
      (static_cast<void*>
         (const_cast<char*>
            (&reinterpret_cast<const char&>(obj))
         )
      );
}

    LowPriorityConversion(const T&) { }


   static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  n->parent_ = p;  }


   static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->left_ = l;  }


   static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->right_ = r;  }


   static color get_color(const const_node_ptr & n)
   {  return n->color_;  }


   static void set_color(const node_ptr & n, color c)
   {  n->color_ = c;  }


   static color black()
   {  return node::black_t;  }


   static color red()
   {  return node::red_t;  }


   static node_ptr get_parent(const const_node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }


   static void set_parent(const node_ptr & n, const node_ptr & p)
   {  ptr_bit::set_pointer(n->parent_, p);  }


   static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }


   static void set_left(const node_ptr & n, const node_ptr & l)
   {  n->left_ = l;  }


   static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }


   static void set_right(const node_ptr & n, const node_ptr & r)
   {  n->right_ = r;  }


   static color get_color(const const_node_ptr & n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }


   static void set_color(const node_ptr & n, color c)
   {  ptr_bit::set_bits(n->parent_, c != 0);  }


   static color black()
   {  return node::black_t;  }


   static color red()
   {  return node::red_t;  }


   static node_ptr get_previous_node(node_ptr p, const node_ptr & this_node)
   {
      for( node_ptr p_next
         ; this_node != (p_next = NodeTraits::get_next(p))
         ; p = p_next){
         //Logic error: possible use of linear lists with
         //operations only permitted with lists
         BOOST_INTRUSIVE_INVARIANT_ASSERT(p);
      }
      return p;
   }


   static void init_header(const node_ptr & this_node)
   {  NodeTraits::set_next(this_node, this_node);  }


   static void init(const node_ptr & this_node)
   {  NodeTraits::set_next(this_node, node_ptr());  }


   static bool unique(const const_node_ptr & this_node)
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }


   static bool inited(const const_node_ptr & this_node)
   {  return !NodeTraits::get_next(this_node); }


   static void unlink_after(const node_ptr & prev_node)
   {
      const_node_ptr this_node(NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, NodeTraits::get_next(this_node));
   }


   static void unlink_after(const node_ptr & prev_node, const node_ptr & last_node)
   {  NodeTraits::set_next(prev_node, last_node);  }


   static void link_after(const node_ptr & prev_node, const node_ptr & this_node)
   {
      NodeTraits::set_next(this_node, NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, this_node);
   }


   static void incorporate_after(const node_ptr & bp, const node_ptr & b, const node_ptr & be)
   {
      node_ptr p(NodeTraits::get_next(bp));
      NodeTraits::set_next(bp, b);
      NodeTraits::set_next(be, p);
   }


   static void transfer_after(const node_ptr & bp, const node_ptr & bb, const node_ptr & be)
   {
      if (bp != bb && bp != be && bb != be) {
         node_ptr next_b = NodeTraits::get_next(bb);
         node_ptr next_e = NodeTraits::get_next(be);
         node_ptr next_p = NodeTraits::get_next(bp);
         NodeTraits::set_next(bb, next_e);
         NodeTraits::set_next(be, next_p);
         NodeTraits::set_next(bp, next_b);
      }
   }

   operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}


   PseudoReference* operator->() const { return &m_value; }

   operator_arrow_proxy(T &px)
      :  m_value(px)
   {}


   T* operator->() const { return &m_value; }


   node_ptr this_ptr()
   {  return pointer_traits<node_ptr>::pointer_to(static_cast<node&>(*this)); }


   const_node_ptr this_ptr() const
   {  return pointer_traits<const_node_ptr>::pointer_to(static_cast<const node&>(*this)); }


   generic_hook()
   {
      if(boost_intrusive_tags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }


   generic_hook(const generic_hook& )
   {
      if(boost_intrusive_tags::safemode_or_autounlink){
         node_algorithms::init(this->this_ptr());
      }
   }


   generic_hook& operator=(const generic_hook& )
   {  return *this;  }


   ~generic_hook()
   {
      destructor_impl
         (*this, detail::link_dispatch<boost_intrusive_tags::link_mode>());
   }


   void swap_nodes(generic_hook &other)
   {
      node_algorithms::swap_nodes
         (this->this_ptr(), other.this_ptr());
   }


   bool is_linked() const
   {
      //is_linked() can be only used in safe-mode or auto-unlink
      BOOST_STATIC_ASSERT(( boost_intrusive_tags::safemode_or_autounlink ));
      return !node_algorithms::unique(this->this_ptr());
   }


   void unlink()
   {
      BOOST_STATIC_ASSERT(( (int)boost_intrusive_tags::link_mode == (int)auto_unlink ));
      node_algorithms::unlink(this->this_ptr());
      node_algorithms::init(this->this_ptr());
   }


   static node_ptr get_previous(const const_node_ptr & n)
   {  return n->prev_;  }


   static void set_previous(const node_ptr & n, const node_ptr & prev)
   {  n->prev_ = prev;  }


   static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }


   static void set_next(const node_ptr & n, const node_ptr & next)
   {  n->next_ = next;  }


   list_iterator()
      : members_ (node_ptr(), 0)
   {}


   explicit list_iterator(const node_ptr & node, const Container *cont_ptr)
      : members_ (node, cont_ptr)
   {}


   list_iterator(list_iterator<Container, false> const& other)
      :  members_(other.pointed_node(), other.get_container())
   {}


   const node_ptr &pointed_node() const
   { return members_.nodeptr_; }


   list_iterator &operator=(const node_ptr &node)
   {  members_.nodeptr_ = node;  return static_cast<list_iterator&>(*this);  }

   list_iterator& operator++()
   {
      node_ptr p = node_traits::get_next(members_.nodeptr_);
      members_.nodeptr_ = p;
      //members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return static_cast<list_iterator&> (*this);
   }


   list_iterator operator++(int)
   {
      list_iterator result (*this);
      members_.nodeptr_ = node_traits::get_next(members_.nodeptr_);
      return result;
   }


   list_iterator& operator--()
   {
      members_.nodeptr_ = node_traits::get_previous(members_.nodeptr_);
      return static_cast<list_iterator&> (*this);
   }


   list_iterator operator--(int)
   {
      list_iterator result (*this);
      members_.nodeptr_ = node_traits::get_previous(members_.nodeptr_);
      return result;
   }


   reference operator*() const
   {  return *operator->();   }


   pointer operator->() const
   { return this->get_real_value_traits()->to_value_ptr(members_.nodeptr_); }


   const Container *get_container() const
   {
      if(store_container_ptr){
         const Container* c = static_cast<const Container*>(members_.get_ptr());
         BOOST_INTRUSIVE_INVARIANT_ASSERT(c != 0);
         return c;
      }
      else{
         return 0;
      }
   }


   const real_value_traits *get_real_value_traits() const
   {
      if(store_container_ptr)
         return &this->get_container()->get_real_value_traits();
      else
         return 0;
   }


   list_iterator<Container, false> unconst() const
   {  return list_iterator<Container, false>(this->pointed_node(), this->get_container());   }


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


      members(const node_ptr &n_ptr, const void *cont)
         :  Base(cont), nodeptr_(n_ptr)
      {}


template<class Parent, class Member>
inline std::ptrdiff_t offset_from_pointer_to_member(const Member Parent::* ptr_to_member)
{
   //The implementation of a pointer to member is compiler dependent.
   #if defined(BOOST_INTRUSIVE_MSVC_ABI_PTR_TO_MEMBER)
   //msvc compliant compilers use their the first 32 bits as offset (even in 64 bit mode)
   union caster_union
   {
      const Member Parent::* ptr_to_member;
      boost::int32_t offset;
   } caster;
   caster.ptr_to_member = ptr_to_member;
   //MSVC ABI can use up to 3 int32 to represent pointer to member data
   //with virtual base classes, in those cases there is no simple to
   //obtain the address of parent. So static assert to avoid runtime errors
   BOOST_STATIC_ASSERT( sizeof(caster) == sizeof(boost::int32_t) );
   return std::ptrdiff_t(caster.offset);
   //This works with gcc, msvc, ac++, ibmcpp
   #elif defined(__GNUC__)   || defined(__HP_aCC) || defined(BOOST_INTEL) || \
         defined(__IBMCPP__) || defined(__DECCXX)
   const Parent * const parent = 0;
   const char *const member = static_cast<const char*>(static_cast<const void*>(&(parent->*ptr_to_member)));
   return std::ptrdiff_t(member - static_cast<const char*>(static_cast<const void*>(parent)));
   #else
   //This is the traditional C-front approach: __MWERKS__, __DMC__, __SUNPRO_CC
   union caster_union
   {
      const Member Parent::* ptr_to_member;
      std::ptrdiff_t offset;
   } caster;
   caster.ptr_to_member = ptr_to_member;
   return caster.offset - 1;
   #endif
}


template<class Parent, class Member>
inline Parent *parent_from_member(Member *member, const Member Parent::* ptr_to_member)
{
   return static_cast<Parent*>
      (
         static_cast<void*>
         (
            static_cast<char*>(static_cast<void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
         )
      );
}


template<class Parent, class Member>
inline const Parent *parent_from_member(const Member *member, const Member Parent::* ptr_to_member)
{
   return static_cast<const Parent*>
      (
         static_cast<const void*>
         (
            static_cast<const char*>(static_cast<const void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
         )
      );
}

      insert_commit_data()
         :  link_left(false)
         ,  node()
      {}

      void operator()(const node_ptr&, const node_ptr&){}

      dispose_subtree_disposer(Disposer &disp, const node_ptr & subtree)
         : disposer_(&disp), subtree_(subtree)
      {}


      void release()
      {  disposer_ = 0;  }


      ~dispose_subtree_disposer()
      {
         if(disposer_){
            dispose_subtree(subtree_, *disposer_);
         }
      }


   static node_ptr uncast(const const_node_ptr & ptr)
   {  return pointer_traits<node_ptr>::const_cast_from(ptr);  }

   static node_ptr begin_node(const const_node_ptr & header)
   {  return node_traits::get_left(header);   }


   static node_ptr end_node(const const_node_ptr & header)
   {  return uncast(header);   }

   static bool unique(const const_node_ptr & node)
   { return !NodeTraits::get_parent(node); }


   static node_ptr get_header(const const_node_ptr & node)
   {
      node_ptr h = uncast(node);
      if(NodeTraits::get_parent(node)){
         h = NodeTraits::get_parent(node);
         while(!is_header(h))
            h = NodeTraits::get_parent(h);
      }
      return h;
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(get_header(node1)), header2(get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   static void swap_nodes(const node_ptr & node1, const node_ptr & header1, const node_ptr & node2, const node_ptr & header2)
   {
      if(node1 == node2)
         return;

      //node1 and node2 must not be header nodes
      //BOOST_INTRUSIVE_INVARIANT_ASSERT((header1 != node1 && header2 != node2));
      if(header1 != header2){
         //Update header1 if necessary
         if(node1 == NodeTraits::get_left(header1)){
            NodeTraits::set_left(header1, node2);
         }

         if(node1 == NodeTraits::get_right(header1)){
            NodeTraits::set_right(header1, node2);
         }

         if(node1 == NodeTraits::get_parent(header1)){
            NodeTraits::set_parent(header1, node2);
         }

         //Update header2 if necessary
         if(node2 == NodeTraits::get_left(header2)){
            NodeTraits::set_left(header2, node1);
         }

         if(node2 == NodeTraits::get_right(header2)){
            NodeTraits::set_right(header2, node1);
         }

         if(node2 == NodeTraits::get_parent(header2)){
            NodeTraits::set_parent(header2, node1);
         }
      }
      else{
         //If both nodes are from the same tree
         //Update header if necessary
         if(node1 == NodeTraits::get_left(header1)){
            NodeTraits::set_left(header1, node2);
         }
         else if(node2 == NodeTraits::get_left(header2)){
            NodeTraits::set_left(header2, node1);
         }

         if(node1 == NodeTraits::get_right(header1)){
            NodeTraits::set_right(header1, node2);
         }
         else if(node2 == NodeTraits::get_right(header2)){
            NodeTraits::set_right(header2, node1);
         }

         if(node1 == NodeTraits::get_parent(header1)){
            NodeTraits::set_parent(header1, node2);
         }
         else if(node2 == NodeTraits::get_parent(header2)){
            NodeTraits::set_parent(header2, node1);
         }

         //Adjust data in nodes to be swapped
         //so that final link swap works as expected
         if(node1 == NodeTraits::get_parent(node2)){
            NodeTraits::set_parent(node2, node2);

            if(node2 == NodeTraits::get_right(node1)){
               NodeTraits::set_right(node1, node1);
            }
            else{
               NodeTraits::set_left(node1, node1);
            }
         }
         else if(node2 == NodeTraits::get_parent(node1)){
            NodeTraits::set_parent(node1, node1);

            if(node1 == NodeTraits::get_right(node2)){
               NodeTraits::set_right(node2, node2);
            }
            else{
               NodeTraits::set_left(node2, node2);
            }
         }
      }

      //Now swap all the links
      node_ptr temp;
      //swap left link
      temp = NodeTraits::get_left(node1);
      NodeTraits::set_left(node1, NodeTraits::get_left(node2));
      NodeTraits::set_left(node2, temp);
      //swap right link
      temp = NodeTraits::get_right(node1);
      NodeTraits::set_right(node1, NodeTraits::get_right(node2));
      NodeTraits::set_right(node2, temp);
      //swap parent link
      temp = NodeTraits::get_parent(node1);
      NodeTraits::set_parent(node1, NodeTraits::get_parent(node2));
      NodeTraits::set_parent(node2, temp);

      //Now adjust adjacent nodes for newly inserted node 1
      if((temp = NodeTraits::get_left(node1))){
         NodeTraits::set_parent(temp, node1);
      }
      if((temp = NodeTraits::get_right(node1))){
         NodeTraits::set_parent(temp, node1);
      }
      if((temp = NodeTraits::get_parent(node1)) &&
         //The header has been already updated so avoid it
         temp != header2){
         if(NodeTraits::get_left(temp) == node2){
            NodeTraits::set_left(temp, node1);
         }
         if(NodeTraits::get_right(temp) == node2){
            NodeTraits::set_right(temp, node1);
         }
      }
      //Now adjust adjacent nodes for newly inserted node 2
      if((temp = NodeTraits::get_left(node2))){
         NodeTraits::set_parent(temp, node2);
      }
      if((temp = NodeTraits::get_right(node2))){
         NodeTraits::set_parent(temp, node2);
      }
      if((temp = NodeTraits::get_parent(node2)) &&
         //The header has been already updated so avoid it
         temp != header1){
         if(NodeTraits::get_left(temp) == node1){
            NodeTraits::set_left(temp, node2);
         }
         if(NodeTraits::get_right(temp) == node1){
            NodeTraits::set_right(temp, node2);
         }
      }
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, get_header(node_to_be_replaced), new_node);
   }

   static void replace_node(const node_ptr & node_to_be_replaced, const node_ptr & header, const node_ptr & new_node)
   {
      if(node_to_be_replaced == new_node)
         return;

      //Update header if necessary
      if(node_to_be_replaced == NodeTraits::get_left(header)){
         NodeTraits::set_left(header, new_node);
      }

      if(node_to_be_replaced == NodeTraits::get_right(header)){
         NodeTraits::set_right(header, new_node);
      }

      if(node_to_be_replaced == NodeTraits::get_parent(header)){
         NodeTraits::set_parent(header, new_node);
      }

      //Now set data from the original node
      node_ptr temp;
      NodeTraits::set_left(new_node, NodeTraits::get_left(node_to_be_replaced));
      NodeTraits::set_right(new_node, NodeTraits::get_right(node_to_be_replaced));
      NodeTraits::set_parent(new_node, NodeTraits::get_parent(node_to_be_replaced));

      //Now adjust adjacent nodes for newly inserted node
      if((temp = NodeTraits::get_left(new_node))){
         NodeTraits::set_parent(temp, new_node);
      }
      if((temp = NodeTraits::get_right(new_node))){
         NodeTraits::set_parent(temp, new_node);
      }
      if((temp = NodeTraits::get_parent(new_node)) &&
         //The header has been already updated so avoid it
         temp != header){
         if(NodeTraits::get_left(temp) == node_to_be_replaced){
            NodeTraits::set_left(temp, new_node);
         }
         if(NodeTraits::get_right(temp) == node_to_be_replaced){
            NodeTraits::set_right(temp, new_node);
         }
      }
   }

   static node_ptr next_node(const node_ptr & node)
   {
      node_ptr p_right(NodeTraits::get_right(node));
      if(p_right){
         return minimum(p_right);
      }
      else {
         node_ptr p(node);
         node_ptr x = NodeTraits::get_parent(p);
         while(p == NodeTraits::get_right(x)){
            p = x;
            x = NodeTraits::get_parent(x);
         }
         return NodeTraits::get_right(p) != x ? x : uncast(p);
      }
   }

   static node_ptr prev_node(const node_ptr & node)
   {
      if(is_header(node)){
         return NodeTraits::get_right(node);
         //return maximum(NodeTraits::get_parent(node));
      }
      else if(NodeTraits::get_left(node)){
         return maximum(NodeTraits::get_left(node));
      }
      else {
         node_ptr p(node);
         node_ptr x = NodeTraits::get_parent(p);
         while(p == NodeTraits::get_left(x)){
            p = x;
            x = NodeTraits::get_parent(x);
         }
         return x;
      }
   }

   static node_ptr minimum (node_ptr node)
   {
      for(node_ptr p_left = NodeTraits::get_left(node)
         ;p_left
         ;p_left = NodeTraits::get_left(node)){
         node = p_left;
      }
      return node;
   }

   static node_ptr maximum(node_ptr node)
   {
      for(node_ptr p_right = NodeTraits::get_right(node)
         ;p_right
         ;p_right = NodeTraits::get_right(node)){
         node = p_right;
      }
      return node;
   }

   static void init(const node_ptr & node)
   {
      NodeTraits::set_parent(node, node_ptr());
      NodeTraits::set_left(node, node_ptr());
      NodeTraits::set_right(node, node_ptr());
   };

   static bool inited(const const_node_ptr & node)
   {
      return !NodeTraits::get_parent(node) &&
             !NodeTraits::get_left(node)   &&
             !NodeTraits::get_right(node)  ;
   };

   static void init_header(const node_ptr & header)
   {
      NodeTraits::set_parent(header, node_ptr());
      NodeTraits::set_left(header, header);
      NodeTraits::set_right(header, header);
   }

   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer)
   {
      node_ptr source_root = NodeTraits::get_parent(header);
      if(!source_root)
         return;
      dispose_subtree(source_root, disposer);
      init_header(header);
   }

   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header)
   {
      node_ptr leftmost = NodeTraits::get_left(header);
      if (leftmost == header)
         return node_ptr();
      node_ptr leftmost_parent(NodeTraits::get_parent(leftmost));
      node_ptr leftmost_right (NodeTraits::get_right(leftmost));
      bool is_root = leftmost_parent == header;

      if (leftmost_right){
         NodeTraits::set_parent(leftmost_right, leftmost_parent);
         NodeTraits::set_left(header, tree_algorithms::minimum(leftmost_right));

         if (is_root)
            NodeTraits::set_parent(header, leftmost_right);
         else
            NodeTraits::set_left(NodeTraits::get_parent(header), leftmost_right);
      }
      else if (is_root){
         NodeTraits::set_parent(header, node_ptr());
         NodeTraits::set_left(header,  header);
         NodeTraits::set_right(header, header);
      }
      else{
         NodeTraits::set_left(leftmost_parent, node_ptr());
         NodeTraits::set_left(header, leftmost_parent);
      }
      return leftmost;
   }

   static std::size_t count(const const_node_ptr & subtree)
   {
      if(!subtree) return 0;
      std::size_t count = 0;
      node_ptr p = minimum(uncast(subtree));
      bool continue_looping = true;
      while(continue_looping){
         ++count;
         node_ptr p_right(NodeTraits::get_right(p));
         if(p_right){
            p = minimum(p_right);
         }
         else {
            for(;;){
               node_ptr q;
               if (p == subtree){
                  continue_looping = false;
                  break;
               }
               q = p;
               p = NodeTraits::get_parent(p);
               if (NodeTraits::get_left(p) == q)
                  break;
            }
         }
      }
      return count;
   }

   static std::size_t size(const const_node_ptr & header)
   {
      node_ptr beg(begin_node(header));
      node_ptr end(end_node(header));
      std::size_t i = 0;
      for(;beg != end; beg = next_node(beg)) ++i;
      return i;
   }

   static void swap_tree(const node_ptr & header1, const node_ptr & header2)
   {
      if(header1 == header2)
         return;

      node_ptr tmp;

      //Parent swap
      tmp = NodeTraits::get_parent(header1);
      NodeTraits::set_parent(header1, NodeTraits::get_parent(header2));
      NodeTraits::set_parent(header2, tmp);
      //Left swap
      tmp = NodeTraits::get_left(header1);
      NodeTraits::set_left(header1, NodeTraits::get_left(header2));
      NodeTraits::set_left(header2, tmp);
      //Right swap
      tmp = NodeTraits::get_right(header1);
      NodeTraits::set_right(header1, NodeTraits::get_right(header2));
      NodeTraits::set_right(header2, tmp);

      //Now test parent
      node_ptr h1_parent(NodeTraits::get_parent(header1));
      if(h1_parent){
         NodeTraits::set_parent(h1_parent, header1);
      }
      else{
         NodeTraits::set_left(header1, header1);
         NodeTraits::set_right(header1, header1);
      }

      node_ptr h2_parent(NodeTraits::get_parent(header2));
      if(h2_parent){
         NodeTraits::set_parent(h2_parent, header2);
      }
      else{
         NodeTraits::set_left(header2, header2);
         NodeTraits::set_right(header2, header2);
      }
   }


   static bool is_header(const const_node_ptr & p)
   {
      node_ptr p_left (NodeTraits::get_left(p));
      node_ptr p_right(NodeTraits::get_right(p));
      if(!NodeTraits::get_parent(p) || //Header condition when empty tree
         (p_left && p_right &&         //Header always has leftmost and rightmost
            (p_left == p_right ||      //Header condition when only node
               (NodeTraits::get_parent(p_left)  != p ||
                NodeTraits::get_parent(p_right) != p ))
               //When tree size > 1 headers can't be leftmost's
               //and rightmost's parent
          )){
         return true;
      }
      return false;
   }

   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp)
   {
      node_ptr end = uncast(header);
      node_ptr y = lower_bound(header, key, comp);
      return (y == end || comp(key, y)) ? end : y;
   }


   template<class F>
   static void erase(const node_ptr & header, const node_ptr & z, F z_and_successor_fixup, data_for_rebalance &info)
   {
      erase_impl(header, z, info);
      if(info.y != z){
         z_and_successor_fixup(z, info.y);
      }
   }


   static void unlink(const node_ptr & node)
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node);
      }
   }


   static void tree_to_vine(const node_ptr & header)
   {  subtree_to_vine(NodeTraits::get_parent(header)); }


   static void vine_to_tree(const node_ptr & header, std::size_t count)
   {  vine_to_subtree(NodeTraits::get_parent(header), count);  }


   static void rebalance(const node_ptr & header)
   {
      //Taken from:
      //"Tree rebalancing in optimal time and space"
      //Quentin F. Stout and Bette L. Warren
      std::size_t len = 0;
      subtree_to_vine(NodeTraits::get_parent(header), &len);
      vine_to_subtree(NodeTraits::get_parent(header), len);
   }


   static node_ptr rebalance_subtree(const node_ptr & old_root)
   {
      std::size_t len = 0;
      node_ptr new_root = subtree_to_vine(old_root, &len);
      return vine_to_subtree(new_root, len);
   }


   static node_ptr subtree_to_vine(const node_ptr & old_root, std::size_t *plen = 0)
   {
      std::size_t len;
      len = 0;
      if(!old_root)   return node_ptr();

      //To avoid irregularities in the algorithm (old_root can be a
      //left or right child or even the root of the tree) just put the
      //root as the right child of its parent. Before doing this backup
      //information to restore the original relationship after
      //the algorithm is applied.
      node_ptr super_root = NodeTraits::get_parent(old_root);
      BOOST_INTRUSIVE_INVARIANT_ASSERT(super_root);

      //Get info
      node_ptr super_root_right_backup = NodeTraits::get_right(super_root);
      bool super_root_is_header   = is_header(super_root);
      bool old_root_is_right  = is_right_child(old_root);

      node_ptr x(old_root);
      node_ptr new_root(x);
      node_ptr save;
      bool moved_to_right = false;
      for( ; x; x = save){
         save = NodeTraits::get_left(x);
         if(save){
            // Right rotation
            node_ptr save_right = NodeTraits::get_right(save);
            node_ptr x_parent   = NodeTraits::get_parent(x);
            NodeTraits::set_parent(save, x_parent);
            NodeTraits::set_right (x_parent, save);
            NodeTraits::set_parent(x, save);
            NodeTraits::set_right (save, x);
            NodeTraits::set_left(x, save_right);
            if(save_right)
               NodeTraits::set_parent(save_right, x);
            if(!moved_to_right)
               new_root = save;
         }
         else{
            moved_to_right = true;
            save = NodeTraits::get_right(x);
            ++len;
         }
      }

      if(super_root_is_header){
         NodeTraits::set_right(super_root, super_root_right_backup);
         NodeTraits::set_parent(super_root, new_root);
      }
      else if(old_root_is_right){
         NodeTraits::set_right(super_root, new_root);
      }
      else{
         NodeTraits::set_right(super_root, super_root_right_backup);
         NodeTraits::set_left(super_root, new_root);
      }
      if(plen) *plen = len;
      return new_root;
   }


   static node_ptr vine_to_subtree(const node_ptr & old_root, std::size_t count)
   {
      std::size_t leaf_nodes = count + 1 - ((std::size_t) 1 << floor_log2 (count + 1));
      std::size_t vine_nodes = count - leaf_nodes;

      node_ptr new_root = compress_subtree(old_root, leaf_nodes);
      while(vine_nodes > 1){
         vine_nodes /= 2;
         new_root = compress_subtree(new_root, vine_nodes);
      }
      return new_root;
   }


   static node_ptr compress_subtree(const node_ptr & old_root, std::size_t count)
   {
      if(!old_root)   return old_root;

      //To avoid irregularities in the algorithm (old_root can be
      //left or right child or even the root of the tree) just put the
      //root as the right child of its parent. First obtain
      //information to restore the original relationship after
      //the algorithm is applied.
      node_ptr super_root = NodeTraits::get_parent(old_root);
      BOOST_INTRUSIVE_INVARIANT_ASSERT(super_root);

      //Get info
      node_ptr super_root_right_backup = NodeTraits::get_right(super_root);
      bool super_root_is_header   = is_header(super_root);
      bool old_root_is_right  = is_right_child(old_root);

      //Put old_root as right child
      NodeTraits::set_right(super_root, old_root);

      //Start the compression algorithm
      node_ptr even_parent = super_root;
      node_ptr new_root = old_root;

      while(count--){
         node_ptr even = NodeTraits::get_right(even_parent);
         node_ptr odd = NodeTraits::get_right(even);

         if(new_root == old_root)
            new_root = odd;

         node_ptr even_right = NodeTraits::get_left(odd);
         NodeTraits::set_right(even, even_right);
         if (even_right)
            NodeTraits::set_parent(even_right, even);

         NodeTraits::set_right(even_parent, odd);
         NodeTraits::set_parent(odd, even_parent);
         NodeTraits::set_left(odd, even);
         NodeTraits::set_parent(even, odd);
         even_parent = odd;
      }

      if(super_root_is_header){
         NodeTraits::set_parent(super_root, new_root);
         NodeTraits::set_right(super_root, super_root_right_backup);
      }
      else if(old_root_is_right){
         NodeTraits::set_right(super_root, new_root);
      }
      else{
         NodeTraits::set_left(super_root, new_root);
         NodeTraits::set_right(super_root, super_root_right_backup);
      }
      return new_root;
   }

   static node_ptr get_root(const node_ptr & node)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT((!inited(node)));
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x)){
            x = NodeTraits::get_parent(x);
         }
         return x;
      }
      else{
         return node;
      }
   }


   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound_loop
      (node_ptr x, node_ptr y, const KeyType &key, KeyNodePtrCompare comp)
   {
      while(x){
         if(comp(x, key)){
            x = NodeTraits::get_right(x);
         }
         else{
            y = x;
            x = NodeTraits::get_left(x);
         }
      }
      return y;
   }


   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound_loop
      (node_ptr x, node_ptr y, const KeyType &key, KeyNodePtrCompare comp)
   {
      while(x){
         if(comp(key, x)){
            y = x;
            x = NodeTraits::get_left(x);
         }
         else{
            x = NodeTraits::get_right(x);
         }
      }
      return y;
   }



   template<class NodePtrCompare>
   static void insert_equal_check_impl
      (bool upper, const node_ptr & h, const node_ptr & new_node, NodePtrCompare comp, insert_commit_data & commit_data, std::size_t *pdepth = 0)
   {
      std::size_t depth = 0;
      node_ptr y(h);
      node_ptr x(NodeTraits::get_parent(y));
      bool link_left;

      if(upper){
         while(x){
            ++depth;
            y = x;
            x = comp(new_node, x) ?
                  NodeTraits::get_left(x) : NodeTraits::get_right(x);
         }
         link_left = (y == h) || comp(new_node, y);
      }
      else{
         while(x){
            ++depth;
            y = x;
            x = !comp(x, new_node) ?
                  NodeTraits::get_left(x) : NodeTraits::get_right(x);
         }
         link_left = (y == h) || !comp(y, new_node);
      }

      commit_data.link_left = link_left;
      commit_data.node = y;
      if(pdepth)  *pdepth = depth;
   }


   static void erase_impl(const node_ptr & header, const node_ptr & z, data_for_rebalance &info)
   {
      node_ptr y(z);
      node_ptr x;
      node_ptr x_parent = node_ptr();
      node_ptr z_left(NodeTraits::get_left(z));
      node_ptr z_right(NodeTraits::get_right(z));
      if(!z_left){
         x = z_right;    // x might be null.
      }
      else if(!z_right){ // z has exactly one non-null child. y == z.
         x = z_left;       // x is not null.
      }
      else{
         // find z's successor
         y = tree_algorithms::minimum (z_right);
         x = NodeTraits::get_right(y);     // x might be null.
      }

      if(y != z){
         // relink y in place of z.  y is z's successor
         NodeTraits::set_parent(NodeTraits::get_left(z), y);
         NodeTraits::set_left(y, NodeTraits::get_left(z));
         if(y != NodeTraits::get_right(z)){
            x_parent = NodeTraits::get_parent(y);
            if(x)
               NodeTraits::set_parent(x, x_parent);
            NodeTraits::set_left(x_parent, x);   // y must be a child of left_
            NodeTraits::set_right(y, NodeTraits::get_right(z));
            NodeTraits::set_parent(NodeTraits::get_right(z), y);
         }
         else
            x_parent = y;
         tree_algorithms::replace_own (z, y, header);
         NodeTraits::set_parent(y, NodeTraits::get_parent(z));
      }
      else {   // y == z --> z has only one child, or none
         x_parent = NodeTraits::get_parent(z);
         if(x)
            NodeTraits::set_parent(x, x_parent);
         tree_algorithms::replace_own (z, x, header);
         if(NodeTraits::get_left(header) == z){
            NodeTraits::set_left(header, !NodeTraits::get_right(z) ?        // z->get_left() must be null also
               NodeTraits::get_parent(z) :  // makes leftmost == header if z == root
               tree_algorithms::minimum (x));
         }
         if(NodeTraits::get_right(header) == z){
            NodeTraits::set_right(header, !NodeTraits::get_left(z) ?        // z->get_right() must be null also
                              NodeTraits::get_parent(z) :  // makes rightmost == header if z == root
                              tree_algorithms::maximum(x));
         }
      }

      info.x = x;
      info.x_parent = x_parent;
      info.y = y;
   }
