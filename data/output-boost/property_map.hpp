

    inline compose_property_map(const FPMap &f_p, const GPMap &g_p):
        f(f_p), g(g_p)
    {}


    inline compose_property_map() {}


    inline reference
    operator[](const key_type &v) const {
        return f[get(g, v)];
    }


template <class FPMap, class GPMap>
inline compose_property_map<FPMap, GPMap>
make_compose_property_map(const FPMap &f, const GPMap &g) {
    return compose_property_map<FPMap, GPMap>(f, g);
}


  inline shared_array_property_map(): data(), index() {}


  inline T& operator[](key_type v) const {
    return data[get(index, v)];
  }


template <class T, class IndexMap>
shared_array_property_map<T, IndexMap>
make_shared_array_property_map(size_t n, const T&, const IndexMap& index) {
  return shared_array_property_map<T, IndexMap>(n, index);
}

  template<typename Value>
  inline Value read_value(const std::string& value)
  { return boost::lexical_cast<Value>(value); }

  virtual ~dynamic_property_map() { }

  virtual ~dynamic_property_exception() throw() {}

  property_not_found(const std::string& property) : property(property) {}

  virtual ~property_not_found() throw() {}


  const char* what() const throw() {
    if(statement.empty())
      statement =
        std::string("Property not found: ") + property + ".";

    return statement.c_str();
  }

  dynamic_get_failure(const std::string& property) : property(property) {}

  virtual ~dynamic_get_failure() throw() {}


  const char* what() const throw() {
    if(statement.empty())
      statement =
        std::string(
         "dynamic property get cannot retrieve value for  property: ")
        + property + ".";

    return statement.c_str();
  }

  virtual ~dynamic_const_put_error() throw() {}


  const char* what() const throw() {
    return "Attempt to put a value into a const property map: ";
  }


  dynamic_properties() : generate_fn() { }


  ~dynamic_properties() {}


  template<typename PropertyMap>
  dynamic_properties&
  property(const std::string& name, PropertyMap property_map_)
  {
    boost::shared_ptr<dynamic_property_map> pm(
      boost::static_pointer_cast<dynamic_property_map>(
        boost::make_shared<detail::dynamic_property_map_adaptor<PropertyMap> >(property_map_)));
    property_maps.insert(property_maps_type::value_type(name, pm));

    return *this;
  }


  iterator       begin()       { return property_maps.begin(); }

  const_iterator begin() const { return property_maps.begin(); }

  iterator       end()         { return property_maps.end(); }

  const_iterator end() const   { return property_maps.end(); }


  iterator lower_bound(const std::string& name)
  { return property_maps.lower_bound(name); }


  void
  insert(const std::string& name, boost::shared_ptr<dynamic_property_map> pm)
  {
    property_maps.insert(property_maps_type::value_type(name, pm));
  }


template<typename Key, typename Value>
bool
put(const std::string& name, dynamic_properties& dp, const Key& key,
    const Value& value)
{
  for (dynamic_properties::iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key)) {
      i->second->put(key, value);
      return true;
    }
  }

  boost::shared_ptr<dynamic_property_map> new_map = dp.generate(name, key, value);
  if (new_map.get()) {
    new_map->put(key, value);
    dp.insert(name, new_map);
    return true;
  } else {
    return false;
  }
}
 
template<typename Value, typename Key>
Value
get(const std::string& name, const dynamic_properties& dp, const Key& key)
{
  for (dynamic_properties::const_iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key))
      return any_cast<Value>(i->second->get(key));
  }

  BOOST_THROW_EXCEPTION(dynamic_get_failure(name));
}

      lvalue_pmap_iter() { }

      lvalue_pmap_iter(Iterator const&     it,
                       LvaluePropertyMap m)
        : super_t(it),
          m_map(m) {}

      readable_pmap_iter() { }

      readable_pmap_iter(Iterator const&     it,
                         ReadablePropertyMap m)
        : super_t(it),
          m_map(m) {}


  template <class PropertyMap, class Iterator>
  typename property_map_iterator_generator<PropertyMap, Iterator>::type
  make_property_map_iterator(PropertyMap pmap, Iterator iter)
  {
    typedef typename property_map_iterator_generator<PropertyMap, 
      Iterator>::type Iter;
    return Iter(iter, pmap);
  }

        
        vector_property_map(const IndexMap& index = IndexMap())
        : store(new std::vector<T>()), index(index)
        {}


        vector_property_map(unsigned initial_size, 
                            const IndexMap& index = IndexMap())
        : store(new std::vector<T>(initial_size)), index(index)
        {}

    
    template<typename T, typename IndexMap>
    vector_property_map<T, IndexMap>
    make_vector_property_map(IndexMap index)
    {
        return vector_property_map<T, IndexMap>(index);
    }

  template <class T, class V>
  inline void put(T* pa, std::ptrdiff_t k, const V& val) { pa[k] = val;  }


  template <class T>
  inline const T& get(const T* pa, std::ptrdiff_t k) { return pa[k]; }

    void constraints() {
      function_requires< ConvertibleConcept<Category, ReadableTag> >();

      val = get(pmap, k);
    }

  template <typename K, typename V>
  const typename readable_property_map_archetype<K,V>::reference&
  get(const readable_property_map_archetype<K,V>&, 
      const typename readable_property_map_archetype<K,V>::key_type&)
  {
    typedef typename readable_property_map_archetype<K,V>::reference R;
    return static_object<R>::get();
  }

    void constraints() {
      function_requires< ConvertibleConcept<Category, WritableTag> >();
      put(pmap, k, val);
    }

  template <typename K, typename V>
  void put(const writable_property_map_archetype<K,V>&, 
           const typename writable_property_map_archetype<K,V>::key_type&, 
           const typename writable_property_map_archetype<K,V>::value_type&) { }

    void constraints() {
      function_requires< ReadablePropertyMapConcept<PMap, Key> >();
      function_requires< WritablePropertyMapConcept<PMap, Key> >();
      function_requires< ConvertibleConcept<Category, ReadWriteTag> >();
    }


    void constraints() {
      function_requires< ReadablePropertyMapConcept<PMap, Key> >();
      function_requires< ConvertibleConcept<Category, LvalueTag> >();

      typedef typename property_traits<PMap>::value_type value_type;
      BOOST_MPL_ASSERT((boost::mpl::or_<
                          boost::is_same<const value_type&, reference>,
                          boost::is_same<value_type&, reference> >));

      reference ref = pmap[k];
      ignore_unused_variable_warning(ref);
    }

    const value_type& operator[](const key_type&) const {
      return static_object<value_type>::get();
    }

    void constraints() { 
      boost::function_requires< ReadWritePropertyMapConcept<PMap, Key> >();
      boost::function_requires<ConvertibleConcept<Category, LvalueTag> >();
      
      typedef typename property_traits<PMap>::value_type value_type;
      BOOST_MPL_ASSERT((boost::is_same<value_type&, reference>));

      reference ref = pmap[k];
      ignore_unused_variable_warning(ref);
    }

    value_type& operator[](const key_type&) const { 
      return static_object<value_type>::get();
    }


  template <class PropertyMap, class Reference, class K>
  inline Reference
  get(const put_get_helper<Reference, PropertyMap>& pa, const K& k)
  {
    Reference v = static_cast<const PropertyMap&>(pa)[k];
    return v;
  }

  template <class PropertyMap, class Reference, class K, class V>
  inline void
  put(const put_get_helper<Reference, PropertyMap>& pa, K k, const V& v)
  {
    static_cast<const PropertyMap&>(pa)[k] = v;
  }

    ref_property_map(ValueType& v) : value(&v) {}

    ValueType& operator[](key_type const&) const { return *value; }


    inline value_type operator[](const key_type& v) const { return v; }

      template <class T>
      dummy_pmap_reference& operator=(const T&) { return *this; }

      operator int() { return 0; }

    inline dummy_property_map() : c(0) { }

    inline dummy_property_map(value_type cc) : c(cc) { }

    inline dummy_property_map(const dummy_property_map& x)
      : c(x.c) { }

    template <class Vertex>
    inline reference operator[](Vertex) const { return reference(); }

    explicit property_map_function(const PropMap& pm): pm(pm) {}

    result_type operator()(const param_type& k) const {return get(pm, k);}


  template <typename PropMap>
  property_map_function<PropMap>
  make_property_map_function(const PropMap& pm) {
    return property_map_function<PropMap>(pm);
  }


    local_property_map() { }


    local_property_map(const ProcessGroup& process_group, 
                       const GlobalMap& global, const StorageMap& storage)
      : process_group_(process_group), global_(global), storage(storage) { }


    reference operator[](const key_type& key) 
    { 
      owner_local_pair p = get(global_, key);
      BOOST_ASSERT(p.first == process_id(process_group_));
      return storage[p.second]; 
    }


    GlobalMap& global() const { return global_; }

    StorageMap& base() const { return storage; }


    ProcessGroup&       process_group()       { return process_group_; }

    const ProcessGroup& process_group() const { return process_group_; }


  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline
  typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::reference
  get(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm, 
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>::key_type
        const & key)

  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    return get(pm.base(), p.second);
  }


  template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
  inline void
  put(const local_property_map<ProcessGroup, GlobalMap, StorageMap>& pm, 
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::key_type const & key,
      typename local_property_map<ProcessGroup, GlobalMap, StorageMap>
                 ::value_type const& v)
  {
    typename property_traits<GlobalMap>::value_type p = get(pm.global(), key);
    BOOST_ASSERT(p.first == process_id(pm.process_group()));
    put(pm.base(), p.second, v);
  }


  template<typename ProcessGroup>
  global_index_map(ProcessGroup pg, value_type num_local_indices, 
                   IndexMap index_map, GlobalMap global)
    : index_map(index_map), global(global)
  {
    typedef typename ProcessGroup::process_id_type process_id_type;
    starting_index.reset(new std::vector<value_type>(num_processes(pg) + 1));
    send(pg, 0, 0, num_local_indices);
    synchronize(pg);
    
    // Populate starting_index in all processes
    if (process_id(pg) == 0) {
      (*starting_index)[0] = 0;
      for (process_id_type src = 0; src < num_processes(pg); ++src) {
        value_type n;
        receive(pg, src, 0, n);
        (*starting_index)[src + 1] = (*starting_index)[src] + n;
      }
      for (process_id_type dest = 1; dest < num_processes(pg); ++dest)
        send(pg, dest, 1, &starting_index->front(), num_processes(pg));
      synchronize(pg);
    } else {
      synchronize(pg);
      receive(pg, 0, 1, &starting_index->front(), num_processes(pg));
    }
  }

template<typename Key, typename Value>
inline void local_put(dummy_property_map, const Key&, const Value&) {}


  explicit caching_property_map(const PropertyMap& property_map)
    : property_map(property_map) {}


  PropertyMap&        base()       { return property_map; }

  const PropertyMap&  base() const { return property_map; }


  template<typename Reduce>
  void set_reduce(const Reduce& reduce)
  { property_map.set_reduce(reduce); }


  void reset() { property_map.reset(); }


template<typename PropertyMap, typename Key>
inline typename caching_property_map<PropertyMap>::value_type
get(const caching_property_map<PropertyMap>& pm, const Key& key)
{ return get(pm.base(), key); }


template<typename PropertyMap, typename Key, typename Value>
inline void
local_put(const caching_property_map<PropertyMap>& pm, const Key& key,
          const Value& value)
{ local_put(pm.base(), key, value); }


template<typename PropertyMap, typename Key, typename Value>
inline void
cache(const caching_property_map<PropertyMap>& pm, const Key& key,
      const Value& value)
{ cache(pm.base(), key, value); }


template<typename PropertyMap, typename Key, typename Value>
inline void
put(const caching_property_map<PropertyMap>& pm, const Key& key,
    const Value& value)
{ local_put(pm.base(), key, value); }


template<typename PropertyMap>
inline caching_property_map<PropertyMap>
make_caching_property_map(const PropertyMap& pm)
{ return caching_property_map<PropertyMap>(pm); }

    template<typename PropertyMap, typename Key, typename Value>
    static inline void
    do_put(PropertyMap, const Key&, const Value&)
    { BOOST_ASSERT(false); }

    template<typename PropertyMap, typename Key, typename Value>
    static inline void
    do_put(PropertyMap pm, const Key& key, const Value& value)
    { 
      using boost::put;

      put(pm, key, value); 
    }


  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put_impl(PropertyMap pm, const Key& key, const Value& value,
                 writable_property_map_tag)
  {
    using boost::put;

    put(pm, key, value);
  }


  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put_impl(PropertyMap, const Key&, const Value&, ...)
  { BOOST_ASSERT(false); }


  template<typename PropertyMap, typename Key, typename Value>
  inline void
  maybe_put(PropertyMap pm, const Key& key, const Value& value)
  {
    maybe_put_impl(pm, key, value,
                   typename property_traits<PropertyMap>::category());
  }

    const result_type& operator()(const value_type& x) const {
      return x.first;
    }

  distributed_property_map() {}

  distributed_property_map(const ProcessGroup& pg, const GlobalMap& global,
                           const StorageMap& pm)
    : data(new data_t(pg, global, pm, basic_reduce<value_type>(), false))
  {
    typedef handle_message<basic_reduce<value_type> > Handler;

    data->ghost_cells.reset(new ghost_cells_type());
    Handler handler(data);
    data->process_group.replace_handler(handler, true);
    data->process_group.template get_receiver<Handler>()
      ->setup_triggers(data->process_group);
  }

  int get_consistency_model() const { return data->model; }


  reference operator[](const key_type& key) const
  {
    owner_local_pair p = get(data->global, key);
    
    if (p.first == process_id(data->process_group)) {
      return data->storage[p.second];
    } else {
      return cell(key);
    }
  }


  process_group_type process_group() const
  {
    return data->process_group.base();
  }


  StorageMap&       base()       { return data->storage; }

  const StorageMap& base() const { return data->storage; }

  void 
  request_put(process_id_type p, const key_type& k, const value_type& v) const
  { 
    send(data->process_group, p, property_map_put, 
         boost::parallel::detail::make_untracked_pair(k, v)); 
  }


  const GlobalMap& global() const { return data->global; }

  GlobalMap&       global()       { return data->global; }

    data_t(const ProcessGroup& pg, const GlobalMap& global, 
           const StorageMap& pm, const function1<value_type, key_type>& dv,
           bool has_default_resolver)
      : process_group(pg), global(global), storage(pm), 
        ghost_cells(), max_ghost_cells(1000000), get_default_value(dv), 
        has_default_resolver(has_default_resolver), model(cm_forward) { }

    explicit handle_message(const shared_ptr<data_t>& data,
                            const Reduce& reduce = Reduce())
      : data_ptr(data), reduce(reduce) { }

    explicit on_synchronize(const shared_ptr<data_t>& data) : data_ptr(data) { }

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
request(const PBGL_DISTRIB_PMAP& pm,
        typename PBGL_DISTRIB_PMAP::key_type const& key)
{
  if (get(pm.data->global, key).first != process_id(pm.data->process_group))
    pm.cell(key, false);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline
typename PBGL_DISTRIB_PMAP::value_type
get(const PBGL_DISTRIB_PMAP& pm,
    typename PBGL_DISTRIB_PMAP::key_type const& key)
{
  using boost::get;

  typename property_traits<GlobalMap>::value_type p = 
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group)) {
    return get(pm.data->storage, p.second);
  } else {
    return pm.cell(key);
  }
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
put(const PBGL_DISTRIB_PMAP& pm,
    typename PBGL_DISTRIB_PMAP::key_type const & key,
    typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  using boost::put;

  typename property_traits<GlobalMap>::value_type p = 
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group)) {
    put(pm.data->storage, p.second, value);
  } else {
    if (pm.data->model & cm_forward) 
      pm.request_put(p.first, key, value);

    pm.cell(key, false) = value;
  }
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
local_put(const PBGL_DISTRIB_PMAP& pm,
          typename PBGL_DISTRIB_PMAP::key_type const & key,
          typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  using boost::put;

  typename property_traits<GlobalMap>::value_type p = 
    get(pm.data->global, key);

  if (p.first == process_id(pm.data->process_group))
    put(pm.data->storage, p.second, value);
  else pm.cell(key, false) = value;
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline void
cache(const PBGL_DISTRIB_PMAP& pm,
      typename PBGL_DISTRIB_PMAP::key_type const & key,
      typename PBGL_DISTRIB_PMAP::value_type const & value)
{
  typename ProcessGroup::process_id_type id = get(pm.data->global, key).first;

  if (id != process_id(pm.data->process_group)) pm.cell(key, false) = value;
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
void
synchronize(PBGL_DISTRIB_PMAP& pm)
{
  pm.do_synchronize();
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap>
inline distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
make_distributed_property_map(const ProcessGroup& pg, GlobalMap global, 
                              StorageMap storage)
{
  typedef distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
    result_type;
  return result_type(pg, global, storage);
}

template<typename ProcessGroup, typename GlobalMap, typename StorageMap, 
         typename Reduce>
inline distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
make_distributed_property_map(const ProcessGroup& pg, GlobalMap global, 
                              StorageMap storage, Reduce reduce)
{
  typedef distributed_property_map<ProcessGroup, GlobalMap, StorageMap>
    result_type;
  return result_type(pg, global, storage, reduce);
}
