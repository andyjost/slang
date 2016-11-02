
  template<class Archive>
  inline void serialize(Archive&, no_property&, const unsigned int) { }

    template <class ParentPA, class Vertex>
    Vertex operator()(ParentPA p, Vertex v) { 
      return detail::find_representative_with_path_halving(p, v);
    }

    template <class ParentPA, class Vertex>
    Vertex operator()(ParentPA p, Vertex v){
      return detail::find_representative_with_full_compression(p, v);
    }

    
    inline disjoint_sets() {}

    inline disjoint_sets(RankPA r, ParentPA p) 
      : rank(r), parent(p) {}


    inline disjoint_sets(const self& c) 
      : rank(c.rank), parent(c.parent) {}

    template <class Element>
    inline void make_set(Element x)
    {
      put(parent, x, x);
      typedef typename property_traits<RankPA>::value_type R;
      put(rank, x, R());
    }

    template <class Element>
    inline void link(Element x, Element y)
    {
      detail::link_sets(parent, rank, x, y, rep);
    }

    template <class Element>
    inline void union_set(Element x, Element y)
    {
      link(find_set(x), find_set(y));
    }

    template <class Element>
    inline Element find_set(Element x)
    {
      return rep(parent, x);
    }


    template <class ElementIterator>
    inline std::size_t count_sets(ElementIterator first, ElementIterator last)
    {
      std::size_t count = 0;  
      for ( ; first != last; ++first)
      if (get(parent, *first) == *first)
        ++count;
      return count;
    }


    template <class ElementIterator>
    inline void normalize_sets(ElementIterator first, ElementIterator last)
    {
      for (; first != last; ++first) 
        detail::normalize_node(parent, *first);
    }
    
    
    template <class ElementIterator>
    inline void compress_sets(ElementIterator first, ElementIterator last)
    {
      for (; first != last; ++first) 
        detail::find_representative_with_full_compression(parent, *first);
    }


    disjoint_sets_with_storage(size_type n = 0,
                               ID id_ = ID(),
                               InverseID inv = InverseID())
      : id(id_), id_to_vertex(inv), rank(n, 0), parent(n)
    {
      for (Index i = 0; i < n; ++i)
        parent[i] = i;
    }

    template <class Element>
    inline void 
    make_set(Element x) {
      parent[x] = x;
      rank[x]   = 0;
    }

    template <class Element>
    inline void 
    link(Element x, Element y)
    {
      extend_sets(x,y);
      detail::link_sets(&parent[0], &rank[0], 
                        get(id,x), get(id,y), rep);
    }

    template <class Element>
    inline void 
    union_set(Element x, Element y) {
      Element rx = find_set(x);
      Element ry = find_set(y);
      link(rx, ry);
    }

    template <class Element>
    inline Element find_set(Element x) {
      return id_to_vertex[rep(&parent[0], get(id,x))];
    }


    template <class ElementIterator>
    inline std::size_t count_sets(ElementIterator first, ElementIterator last)
    {
      std::size_t count = 0;  
      for ( ; first != last; ++first)
      if (parent[*first] == *first)
        ++count;
      return count;
    }


    template <class ElementIterator>
    inline void normalize_sets(ElementIterator first, ElementIterator last)
    {
      for (; first != last; ++first) 
        detail::normalize_node(&parent[0], *first);
    }
    
    
    template <class ElementIterator>
    inline void compress_sets(ElementIterator first, ElementIterator last)
    {
      for (; first != last; ++first) 
        detail::find_representative_with_full_compression(&parent[0],
                                                          *first);
    }
    

    const ParentContainer& parents() { return parent; }


    template <class Element>
    inline void 
    extend_sets(Element x, Element y)
    {
      Index needed = get(id,x) > get(id,y) ? get(id,x) + 1 : get(id,y) + 1;
      if (needed > parent.size()) {
        rank.insert(rank.end(), needed - rank.size(), 0);
        for (Index k = parent.size(); k < needed; ++k)
        parent.push_back(k);
      } 
    }
 
  dummyT() { }

  dummyT(int x) : m_x(x) { }

  int foo() const { return m_x; }
 
  bool operator==(const dummyT& d) const { return m_x == d.m_x; }

    property(const T& v = T()) : m_value(v) { }

    property(const T& v, const Base& b) : m_value(v), m_base(b) { }


  template <class PropertyList, class Tag>
  inline typename lookup_one_property<PropertyList, Tag>::type&
  get_property_value(PropertyList& p, Tag tag) {
    return lookup_one_property<PropertyList, Tag>::lookup(p, tag);
  }


  template <class PropertyList, class Tag>
  inline const typename lookup_one_property<PropertyList, Tag>::type&
  get_property_value(const PropertyList& p, Tag tag) {
    return lookup_one_property<PropertyList, Tag>::lookup(p, tag);
  }

      lookup_one_property_f(Tag tag): tag(tag) {}


      typename lookup_one_property_f_result<PList, Tag, const lookup_one_property_f(PList&)>::type
      operator()(PList& pl) const {
        return lookup_one_property<PList, Tag>::lookup(pl, tag);
      }

    template <typename Prop>
    typename Prop::next_type& operator()(Prop& p) const {return p.m_base;}

    template <typename Prop>
    const typename Prop::next_type& operator()(const Prop& p) const {return p.m_base;}


  template <class TreeNode, class Compare, class ExternalData>
  inline TreeNode up_heap(TreeNode x, const Compare& comp, ExternalData& edata) {
    while (x.has_parent() && comp(x, x.parent()))
      x.swap(x.parent(), edata);
    return x;
  }


  template <class TreeNode, class Compare, class ExternalData>
  inline TreeNode down_heap(TreeNode x, const Compare& comp, ExternalData& edata) {
    while (x.children().size() > 0) {
      typename TreeNode::children_type::iterator 
        child_iter = std::min_element(x.children().begin(),
                                      x.children().end(), 
                                      comp);
      if (comp(*child_iter, x))
        x.swap(*child_iter, edata);
      else
        break;
    }
    return x;
  }


  template <class TreeNode, class Compare, class ExternalData>
  inline void update_heap(TreeNode x, const Compare& comp, ExternalData& edata) {
    x = down_heap(x, comp, edata);
    (void)up_heap(x, comp, edata);
  }

    inline indirect_cmp(const ReadablePropertyMap& df, const Compare& c = Compare())
      : d(df), cmp(c) { }


    template <class A, class B>
    inline bool 
    operator()(const A& u, const B& v) const {
      const T& du = get(d, u);
      const T& dv = get(d, v);
      return cmp(du, dv);
    }


  template <typename Compare, typename ReadablePropertyMap>
  indirect_cmp<ReadablePropertyMap, Compare>
  make_indirect_cmp(const Compare& cmp, ReadablePropertyMap pmap) {
    indirect_cmp<ReadablePropertyMap, Compare> p(pmap, cmp);
    return p;
  }

    inline indirect_pmap(const ReadablePropertyMap& df)
      : d(df) { }


    inline T operator()(const K& u) const {
      return get(d, u);
    }


  template <typename ReadablePropertyMap>
  indirect_pmap<ReadablePropertyMap>
  make_indirect_pmap(ReadablePropertyMap pmap) {
    indirect_pmap<ReadablePropertyMap> f(pmap);
    return f;
  }

  queue() : c() {}

  explicit queue(const _Sequence& __c) : c(__c) {}


  bool empty() const { return c.empty(); }

  size_type size() const { return c.size(); }

  reference front() { return c.front(); }

  const_reference front() const { return c.front(); }

  reference top() { return c.front(); }

  const_reference top() const { return c.front(); }

  reference back() { return c.back(); }

  const_reference back() const { return c.back(); }

  void push(const value_type& __x) { c.push_back(__x); }

  void pop() { c.pop_front(); }


  void swap(queue& other)
  {
    using std::swap;
    swap(c, other.c);
  }


template <class _Tp, class _Sequence>
bool 
operator==(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __x.c == __y.c;
}


template <class _Tp, class _Sequence>
bool
operator<(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __x.c < __y.c;
}


template <class _Tp, class _Sequence>
bool
operator!=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__x == __y);
}


template <class _Tp, class _Sequence>
bool 
operator>(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return __y < __x;
}


template <class _Tp, class _Sequence>
bool 
operator<=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__y < __x);
}


template <class _Tp, class _Sequence>
bool 
operator>=(const queue<_Tp, _Sequence>& __x, const queue<_Tp, _Sequence>& __y)
{
  return !(__x < __y);
}


template <class _Tp, class _Sequence>
inline void
swap(queue<_Tp, _Sequence>& __x, queue<_Tp, _Sequence>& __y)
{ __x.swap(__y); }


    template <typename T>
    int lowest_bit(T x) {

        assert(x >= 1); // PRE

        // clear all bits on except the rightmost one,
        // then calculate the logarithm base 2
        //
        return boost::integer_log2<T>( x - ( x & (x-1) ) );

    }


    inline bool
    isws (char c, char const * const wstr)
    {
        using namespace std;
        return (strchr(wstr,c) != NULL);
    }

template <typename Container>
void
stringtok (Container &l, std::string const &s, char const * const ws = " \t\n")
{
  typedef std::string::size_type size_type;
    const size_type  S = s.size();
          size_type  i = 0;

    while (i < S) {
        // eat leading whitespace
        while ((i < S) && (isws(s[i],ws)))  ++i;
        if (i == S)  return;  // nothing left but WS

        // find end of word
        size_type  j = i+1;
        while ((j < S) && (!isws(s[j],ws)))  ++j;

        // add word
        l.push_back(s.substr(i,j-i));

        // set up for next loop
        i = j+1;
    }
}

    
    bucket_sorter(size_type _length, bucket_type _max_bucket, 
                  const Bucket& _bucket = Bucket(), 
                  const ValueIndexMap& _id = ValueIndexMap()) 
      : head(_max_bucket, invalid_value()),
        next(_length, invalid_value()), 
        prev(_length, invalid_value()),
        id_to_value(_length),
        bucket(_bucket), id(_id) { }

    
    void remove(const value_type& x) {
      const size_type i = get(id, x);
      const size_type& next_node = next[i];
      const size_type& prev_node = prev[i];
    
      //check if i is the end of the bucket list 
      if ( next_node != invalid_value() )
        prev[next_node] = prev_node; 
      //check if i is the begin of the bucket list
      if ( prev_node != invalid_value() )
        next[prev_node] = next_node;
      else //need update head of current bucket list
        head[ bucket[x] ] = next_node;
    }


    void push(const value_type& x) {
      id_to_value[get(id, x)] = x;
      (*this)[bucket[x]].push(x);
    }

    
    void update(const value_type& x) {
      remove(x);
      (*this)[bucket[x]].push(x);
    }

    static size_type invalid_value() {
      return (std::numeric_limits<size_type>::max)();
    }

      stack(bucket_type _bucket_id, Iter h, Iter n, Iter p, IndexValueMap v,
            const ValueIndexMap& _id)
      : bucket_id(_bucket_id), head(h), next(n), prev(p), value(v), id(_id) {}

      
      void push(const value_type& x) {
        const size_type new_head = get(id, x);
        const size_type current = head[bucket_id];
        if ( current != invalid_value() )
          prev[current] = new_head;
        prev[new_head] = invalid_value();
        next[new_head] = current;
        head[bucket_id] = new_head;
      }

      void pop() {
        size_type current = head[bucket_id];
        size_type next_node = next[current];
        head[bucket_id] = next_node;
        if ( next_node != invalid_value() )
          prev[next_node] = invalid_value();
      }

      value_type& top() { return value[ head[bucket_id] ]; }

      const value_type& top() const { return value[ head[bucket_id] ]; }

      bool empty() const { return head[bucket_id] == invalid_value(); }

    
    stack operator[](const bucket_type& i) {
      assert(i < head.size());
      return stack(i, head.begin(), next.begin(), prev.begin(),
                   id_to_value.begin(), id);
    }

  inline void require_stable(stable_tag) { }


  template <class T, class Alloc>
  vector_tag container_category(const std::vector<T,Alloc>&)
    { return vector_tag(); }


  template <class T, class Alloc>
  unstable_tag iterator_stability(const std::vector<T,Alloc>&)
    { return unstable_tag(); }

  template <class Sequence, class T>
  void erase_dispatch(Sequence& c, const T& x, 
                      sequence_tag)
  {
    c.erase(std::remove(c.begin(), c.end(), x), c.end());
  }


  template <class AssociativeContainer, class T>
  void erase_dispatch(AssociativeContainer& c, const T& x, 
                      associative_container_tag)
  {
    c.erase(x);
  }

  template <class Container, class T>
  void erase(Container& c, const T& x)
  {
    erase_dispatch(c, x, container_category(c));
  }

  template <class Sequence, class Predicate, class IteratorStability>
  void erase_if_dispatch(Sequence& c, Predicate p,
                         sequence_tag, IteratorStability)
  {
#if 0
    c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#else
    if (! c.empty())
      c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
#endif
  }

  template <class AssociativeContainer, class Predicate>
  void erase_if_dispatch(AssociativeContainer& c, Predicate p,
                         associative_container_tag, stable_tag)
  {
    typename AssociativeContainer::iterator i, next;
    for (i = next = c.begin(); next != c.end(); i = next) {
      ++next;
      if (p(*i))
        c.erase(i);
    }
  }

  template <class AssociativeContainer, class Predicate>
  void erase_if_dispatch(AssociativeContainer& c, Predicate p,
                         associative_container_tag, unstable_tag)
  {
    // This method is really slow, so hopefully we won't have any
    // associative containers with unstable iterators!
    // Is there a better way to do this?
    typename AssociativeContainer::iterator i;
    typename AssociativeContainer::size_type n = c.size();
    while (n--)
      for (i = c.begin(); i != c.end(); ++i)
        if (p(*i)) {
          c.erase(i);
          break;
        }
  }

  template <class Container, class Predicate>
  void erase_if(Container& c, Predicate p)
  {
    erase_if_dispatch(c, p, container_category(c), iterator_stability(c));
  }


  template <typename T>
  int integer_log2_impl(T x, int n) {

      int result = 0;

      while (x != 1) {

          const T t = static_cast<T>(x >> n);
          if (t) {
              result += n;
              x = t;
          }
          n /= 2;

      }

      return result;
  }

 template <typename T>
 int integer_log2(T x) {

     assert(x > 0);

     const int n = detail::max_pow2_less<
                     detail::width<T> :: value, 4
                   > :: value;

     return detail::integer_log2_impl(x, n);

 }


template <class ParentPA, class Vertex>
Vertex
find_representative_with_path_halving(ParentPA p, Vertex v)
{ 
  Vertex parent = get(p, v);
  Vertex grandparent = get(p, parent);
  while (parent != grandparent) {
    put(p, v, grandparent);
    v =  grandparent;
    parent = get(p, v);
    grandparent = get(p, parent); 
  }
  return parent;
}


template <class ParentPA, class Vertex>
Vertex
find_representative_with_full_compression(ParentPA parent, Vertex v)
{
  Vertex old = v;
  Vertex ancestor = get(parent, v);
  while (ancestor != v) {
    v = ancestor;
    ancestor = get(parent, v);
  }
  v = get(parent, old);
  while (ancestor != v) {
    put(parent, old, ancestor);
    old = v;
    v = get(parent, old);
  }
  return ancestor;
}

template <class ParentPA, class RankPA, class Vertex, 
          class ComponentRepresentative>
inline void
link_sets(ParentPA p, RankPA rank, Vertex i, Vertex j,
          ComponentRepresentative comp_rep)
{
  i = comp_rep(p, i);
  j = comp_rep(p, j);
  if (i == j) return;
  if (get(rank, i) > get(rank, j)) 
    put(p, j, i);
  else {
    put(p, i, j);
    if (get(rank, i) == get(rank, j)) 
      put(rank, j, get(rank, j) + 1);
  }
}


template <class ParentPA, class Vertex>
inline void
normalize_node(ParentPA p, Vertex i)
{
  if (i > get(p,i) || get(p, get(p,i)) != get(p,i))   
    put(p,i, get(p, get(p,i)));
  else {
    put(p, get(p,i), i);
    put(p, i, i);
  } 
}


  inline int_iterator() : _i(0) { }

  inline int_iterator(IntT i) : _i(i) { }

  inline int_iterator(const self& x) : _i(x._i) { }

  inline self& operator=(const self& x) { _i = x._i; return *this; }

  inline IntT operator*() { return _i; }

  inline IntT operator[](IntT n) { return _i + n; }

  inline self& operator++() { ++_i; return *this; }

  inline self operator++(int) { self t = *this; ++_i; return t; }

  inline self& operator+=(IntT n) { _i += n; return *this; }

  inline self operator+(IntT n) { self t = *this; t += n; return t; }

  inline self& operator--() { --_i; return *this; }

  inline self operator--(int) { self t = *this; --_i; return t; }

  inline self& operator-=(IntT n) { _i -= n; return *this; }

  inline IntT operator-(const self& x) const { return _i - x._i; }

  inline bool operator==(const self& x) const { return _i == x._i; }

  inline bool operator!=(const self& x) const { return _i != x._i; }

  inline bool operator<(const self& x) const { return _i < x._i; }

  inline bool operator<=(const self& x) const { return _i <= x._i; }

  inline bool operator>(const self& x) const { return _i > x._i; }

  inline bool operator>=(const self& x) const { return _i >= x._i; }


template <class IntT>
inline int_iterator<IntT>
operator+(IntT n, int_iterator<IntT> t) { t += n; return t; }
