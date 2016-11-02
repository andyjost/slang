

   inline void throw_bad_alloc()
   {
      throw std::bad_alloc();
   }


   inline void throw_out_of_range(const char* str)
   {
      throw std::out_of_range(str);
   }


   inline void throw_length_error(const char* str)
   {
      throw std::length_error(str);
   }


   inline void throw_logic_error(const char* str)
   {
      throw std::logic_error(str);
   }


   inline void throw_runtime_error(const char* str)
   {
      throw std::runtime_error(str);
   }


   static type &get(MaybeScopedAlloc &a)
   {  return a;  }


   static const type &get(const MaybeScopedAlloc &a)
   {  return a;  }


   static type &get(MaybeScopedAlloc &a)
   {  return outermost_allocator_imp<outer_type>::get(a.outer_allocator());  }


   static const type &get(const MaybeScopedAlloc &a)
   {  return outermost_allocator_imp<outer_type>::get(a.outer_allocator());  }
 &
   get_outermost_allocator(Alloc &a)
{  return container_detail::outermost_allocator_imp<Alloc>::get(a);   }


template < typename OutermostAlloc
         , typename InnerAlloc
         , typename T
         , class ...Args
         >
inline void dispatch_allocator_prefix_suffix
   ( boost::true_type  use_alloc_prefix, OutermostAlloc& outermost_alloc
   , InnerAlloc& inner_alloc, T* p, BOOST_FWD_REF(Args) ...args)
{
   (void)use_alloc_prefix;
   allocator_traits<OutermostAlloc>::construct
      ( outermost_alloc, p, allocator_arg, inner_alloc, ::boost::forward<Args>(args)...);
}


template < typename OutermostAlloc
         , typename InnerAlloc
         , typename T
         , class ...Args
         >
inline void dispatch_uses_allocator
   ( boost::true_type uses_allocator, OutermostAlloc& outermost_alloc
   , InnerAlloc& inner_alloc, T* p, BOOST_FWD_REF(Args)...args)
{
   (void)uses_allocator;
   //BOOST_STATIC_ASSERT((is_constructible_with_allocator_prefix<T, InnerAlloc, Args...>::value ||
   //                     is_constructible_with_allocator_suffix<T, InnerAlloc, Args...>::value ));
   dispatch_allocator_prefix_suffix
      ( is_constructible_with_allocator_prefix<T, InnerAlloc, Args...>()
      , outermost_alloc, inner_alloc, p, ::boost::forward<Args>(args)...);
}


   scoped_allocator_adaptor_base()
      {}


   template <class OuterA2>
   scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs &...args)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      , m_inner(args...)
      {}


   scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}


   scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      , m_inner(::boost::move(other.inner_allocator()))
      {}


   template <class OuterA2>
   scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<OuterA2, InnerAllocs...>& other)
      : outer_allocator_type(other.outer_allocator())
      , m_inner(other.inner_allocator())
      {}


   scoped_allocator_adaptor_base &operator=
      (BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      m_inner = other.inner_allocator();
      return *this;
   }


   void swap(scoped_allocator_adaptor_base &r)
   {
      boost::container::swap_dispatch(this->outer_allocator(), r.outer_allocator());
      boost::container::swap_dispatch(this->m_inner, r.inner_allocator());
   }


   inner_allocator_type&       inner_allocator()
      { return m_inner; }


   scoped_allocator_adaptor_base()
      {}


   template <class OuterA2>
   scoped_allocator_adaptor_base(BOOST_FWD_REF(OuterA2) outerAlloc)
      : outer_allocator_type(::boost::forward<OuterA2>(outerAlloc))
      {}


   scoped_allocator_adaptor_base(const scoped_allocator_adaptor_base& other)
      : outer_allocator_type(other.outer_allocator())
      {}


   scoped_allocator_adaptor_base(BOOST_RV_REF(scoped_allocator_adaptor_base) other)
      : outer_allocator_type(::boost::move(other.outer_allocator()))
      {}


   template <class OuterA2>
   scoped_allocator_adaptor_base
      (const scoped_allocator_adaptor_base<
         OuterA2
         #if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
         , true
         BOOST_PP_ENUM_TRAILING(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, BOOST_CONTAINER_PP_IDENTITY, container_detail::nat)
         #endif
         >& other)
      : outer_allocator_type(other.outer_allocator())
      {}

   scoped_allocator_adaptor_base &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor_base) other)
   {
      outer_allocator_type::operator=(other.outer_allocator());
      return *this;
   }


   void swap(scoped_allocator_adaptor_base &r)
   {
      boost::container::swap_dispatch(this->outer_allocator(), r.outer_allocator());
   }


   inner_allocator_type&       inner_allocator()
      { return static_cast<inner_allocator_type&>(*this); }

   scoped_allocator_adaptor()
      {}


   ~scoped_allocator_adaptor()
      {}

   scoped_allocator_adaptor(const scoped_allocator_adaptor& other)
      : base_type(other.base())
      {}

   scoped_allocator_adaptor(BOOST_RV_REF(scoped_allocator_adaptor) other)
      : base_type(::boost::move(other.base()))
      {}

   template <class OuterA2>
   scoped_allocator_adaptor(BOOST_FWD_REF(OuterA2) outerAlloc, const InnerAllocs & ...innerAllocs)
      : base_type(::boost::forward<OuterA2>(outerAlloc), innerAllocs...)
      {}

   template <class OuterA2>
   scoped_allocator_adaptor(const scoped_allocator_adaptor<OuterA2
      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , InnerAllocs...
      #else
      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, Q)
      #endif
      > &other)
      : base_type(other.base())
      {}


   scoped_allocator_adaptor &operator=(BOOST_COPY_ASSIGN_REF(scoped_allocator_adaptor) other)
   {
      base_type::operator=(static_cast<const base_type &>(other));
      return *this;
   }

   void swap(scoped_allocator_adaptor &r)
   {
      base_type::swap(r);
   }

   outer_allocator_type      & outer_allocator()
      {  return *this; }

   const outer_allocator_type &outer_allocator() const
      {  return *this; }

   inner_allocator_type&       inner_allocator()
      {  return base_type::inner_allocator(); }

   inner_allocator_type const& inner_allocator() const
      {  return base_type::inner_allocator(); }

   size_type max_size() const
   {
      return outer_traits_type::max_size(this->outer_allocator());
   }

   template <class T>
   void destroy(T* p)
   {
      allocator_traits<typename outermost_allocator<OuterAlloc>::type>
         ::destroy(get_outermost_allocator(this->outer_allocator()), p);
   }

   pointer allocate(size_type n)
   {
      return outer_traits_type::allocate(this->outer_allocator(), n);
   }

   pointer allocate(size_type n, const_void_pointer hint)
   {
      return outer_traits_type::allocate(this->outer_allocator(), n, hint);
   }

   void deallocate(pointer p, size_type n)
   {
      outer_traits_type::deallocate(this->outer_allocator(), p, n);
   }

   scoped_allocator_adaptor select_on_container_copy_construction() const
   {
      return scoped_allocator_adaptor
         (internal_type_t()
         ,outer_traits_type::select_on_container_copy_construction(this->outer_allocator())
         ,inner_traits_type::select_on_container_copy_construction(this->inner_allocator())
         );
   }

   base_type &base()             { return *this; }


template <typename OuterA1, typename OuterA2
   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   , typename... InnerAllocs
   #else
   BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, class Q)
   #endif
   >
inline bool operator==(
   const scoped_allocator_adaptor<OuterA1
      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      ,InnerAllocs...
      #else
      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, Q)
      #endif
      >& a,
   const scoped_allocator_adaptor<OuterA2
      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      ,InnerAllocs...
      #else
      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, Q)
      #endif
   >& b)
{
   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)  
   const bool has_zero_inner = sizeof...(InnerAllocs) == 0u;
   #else
   const bool has_zero_inner =
      boost::container::container_detail::is_same
         <Q0, container_detail::nat>::value;
   #endif

    return a.outer_allocator() == b.outer_allocator()
        && (has_zero_inner || a.inner_allocator() == b.inner_allocator());
}


template <typename OuterA1, typename OuterA2
   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   , typename... InnerAllocs
   #else
   BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, class Q)
   #endif
   >
inline bool operator!=(
   const scoped_allocator_adaptor<OuterA1
      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      ,InnerAllocs...
      #else
      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, Q)
      #endif
      >& a,
   const scoped_allocator_adaptor<OuterA2
      #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      ,InnerAllocs...
      #else
      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS, Q)
      #endif
   >& b)
{
    return ! (a == b);
}


template<typename V, std::size_t C1, std::size_t C2>
inline void swap(static_vector<V, C1> & x, static_vector<V, C2> & y
      , typename container_detail::enable_if_c< C1 != C2>::type * = 0)
{
   x.swap(y);
}

   clear_on_destroy(C &c)
      :  c_(c), do_clear_(true)
   {}


   void release()
   {  do_clear_ = false; }


   ~clear_on_destroy()
   {
      if(do_clear_){
         c_.clear();
         c_.priv_clear_pool(); 
      }
   }

   node_base(const node_base_ptr_ptr &n)
      : up(n)
   {}


   node_base()
      : up()
   {}


   static node_base_ptr_ptr ptr_to_node_base_ptr(node_base_ptr &n)
   {  return node_base_ptr_ptr_traits::pointer_to(n);   }


   static void fix_up_pointers(index_iterator first, index_iterator last)
   {
      while(first != last){
         typedef typename index_type::reference node_base_ptr_ref;
         node_base_ptr_ref nbp = *first;
         nbp->up = index_traits::ptr_to_node_base_ptr(nbp);
         ++first;
      }
   }


   static index_iterator get_fix_up_end(index_type &index)
   {  return index.end() - (ExtraPointers - 1); }


   static void fix_up_pointers_from(index_type & index, index_iterator first)
   {  index_traits::fix_up_pointers(first, index_traits::get_fix_up_end(index));   }


   static void readjust_end_node(index_type &index, node_base_type &end_node)
   {
      if(!index.empty()){
         index_iterator end_node_it(index_traits::get_fix_up_end(index));
         node_base_ptr &end_node_idx_ref = *(--end_node_it);
         end_node_idx_ref = node_base_ptr_traits::pointer_to(end_node);
         end_node.up      = node_base_ptr_ptr_traits::pointer_to(end_node_idx_ref);
      }
      else{
         end_node.up = node_base_ptr_ptr();
      }
   }


   static void initialize_end_node(index_type &index, node_base_type &end_node, const size_type index_capacity_if_empty)
   {
      if(index.empty()){
         index.reserve(index_capacity_if_empty + ExtraPointers);
         index.resize(ExtraPointers);
         node_base_ptr &end_node_ref = *index.data();
         end_node_ref = node_base_ptr_traits::pointer_to(end_node);
         end_node.up = index_traits::ptr_to_node_base_ptr(end_node_ref);
      }
   }


   node_ptr allocate_one()
   {  return allocator_version_traits_t::allocate_one(this->priv_node_alloc());   }


   void deallocate_one(const node_ptr &p)
   {  allocator_version_traits_t::deallocate_one(this->priv_node_alloc(), p);   }


   void allocate_individual(typename allocator_traits_type::size_type n, multiallocation_chain &m)
   {  allocator_version_traits_t::allocate_individual(this->priv_node_alloc(), n, m);   }


   void deallocate_individual(multiallocation_chain &holder)
   {  allocator_version_traits_t::deallocate_individual(this->priv_node_alloc(), holder);   }

   stable_vector()
      : internal_data(), index()
   {
      STABLE_VECTOR_CHECK_INVARIANT;
   }

      push_back_rollback(stable_vector &sv, const node_ptr &p)
         : m_sv(sv), m_p(p)
      {}


      ~push_back_rollback()
      {
         if(m_p){
            m_sv.priv_put_in_pool(m_p);
         }
      }


      void release()
      {  m_p = node_ptr();  }


   index_iterator priv_insert_forward_non_templated(size_type pos, size_type num_new)
   {
      index_traits_type::initialize_end_node(this->index, this->internal_data.end_node, num_new);

      //Now try to fill the pool with new data
      if(this->internal_data.pool_size < num_new){
         this->priv_increase_pool(num_new - this->internal_data.pool_size);
      }

      //Now try to make room in the vector
      const node_base_ptr_ptr old_buffer = this->index.data();
      this->index.insert(this->index.begin() + pos, num_new, node_ptr());
      bool new_buffer = this->index.data() != old_buffer;

      //Fix the pointers for the newly allocated buffer
      const index_iterator index_beg = this->index.begin();
      if(new_buffer){
         index_traits_type::fix_up_pointers(index_beg, index_beg + pos);
      }
      return index_beg + pos;
   }


   bool priv_capacity_bigger_than_size() const
   {
      return this->index.capacity() > this->index.size() &&
             this->internal_data.pool_size > 0;
   }


   template <class U>
   void priv_push_back(BOOST_MOVE_CATCH_FWD(U) x)
   {
      if(this->priv_capacity_bigger_than_size()){
         //Enough memory in the pool and in the index
         const node_ptr p = this->priv_get_from_pool();
         BOOST_ASSERT(!!p);
         {
            push_back_rollback rollback(*this, p);
            //This might throw
            this->priv_build_node_from_convertible(p, ::boost::forward<U>(x));
            rollback.release();
         }
         //This can't throw as there is room for a new elements in the index
         index_iterator new_index = this->index.insert(this->index.end() - ExtraPointers, p);
         index_traits_type::fix_up_pointers_from(this->index, new_index);
      }
      else{
         this->insert(this->cend(), ::boost::forward<U>(x));
      }
   }


   iterator priv_insert(const_iterator position, const value_type &t)
   {
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(position, cvalue_iterator(t, 1), cvalue_iterator());
   }


   void priv_clear_pool()
   {
      if(!this->index.empty() && this->index.back()){
         node_base_ptr &pool_first_ref = *(this->index.end() - 2);
         node_base_ptr &pool_last_ref  = this->index.back();

         multiallocation_chain holder;
         holder.incorporate_after( holder.before_begin()
                                 , node_ptr_traits::static_cast_from(pool_first_ref)
                                 , node_ptr_traits::static_cast_from(pool_last_ref)
                                 , internal_data.pool_size);
         this->deallocate_individual(holder);
         pool_first_ref = pool_last_ref = 0;
         this->internal_data.pool_size = 0;
      }
   }


   void priv_increase_pool(size_type n)
   {
      node_base_ptr &pool_first_ref = *(this->index.end() - 2);
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      multiallocation_chain m;
      this->allocate_individual(n, m);
      holder.splice_after(holder.before_begin(), m, m.before_begin(), m.last(), n);
      this->internal_data.pool_size += n;
      std::pair<node_ptr, node_ptr> data(holder.extract_data());
      pool_first_ref = data.first;
      pool_last_ref = data.second;
   }


   void priv_put_in_pool(const node_ptr &p)
   {
      node_base_ptr &pool_first_ref = *(this->index.end()-2);
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      holder.push_front(p);
      ++this->internal_data.pool_size;
      std::pair<node_ptr, node_ptr> ret(holder.extract_data());
      pool_first_ref = ret.first;
      pool_last_ref  = ret.second;
   }


   void priv_put_in_pool(multiallocation_chain &ch)
   {
      node_base_ptr &pool_first_ref = *(this->index.end()-(ExtraPointers-1));
      node_base_ptr &pool_last_ref  = this->index.back();
      ch.incorporate_after( ch.before_begin()
                          , node_ptr_traits::static_cast_from(pool_first_ref)
                          , node_ptr_traits::static_cast_from(pool_last_ref)
                          , internal_data.pool_size);
      this->internal_data.pool_size = ch.size();
      const std::pair<node_ptr, node_ptr> ret(ch.extract_data());
      pool_first_ref = ret.first;
      pool_last_ref  = ret.second;
   }


   node_ptr priv_get_from_pool()
   {
      //Precondition: index is not empty
      BOOST_ASSERT(!this->index.empty());
      node_base_ptr &pool_first_ref = *(this->index.end() - (ExtraPointers-1));
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      node_ptr ret = holder.pop_front();
      --this->internal_data.pool_size;
      if(!internal_data.pool_size){
         pool_first_ref = pool_last_ref = node_ptr();
      }
      else{
         const std::pair<node_ptr, node_ptr> data(holder.extract_data());
         pool_first_ref = data.first;
         pool_last_ref  = data.second;
      }
      return ret;
   }


   node_ptr priv_get_end_node() const
   {
      return node_ptr_traits::pointer_to
         (static_cast<node_type&>(const_cast<node_base_type&>(this->internal_data.end_node)));
   }


   void priv_destroy_node(const node_type &n)
   {
      allocator_traits<node_allocator_type>::
         destroy(this->priv_node_alloc(), container_detail::addressof(n.value));
      static_cast<const node_base_type*>(&n)->~node_base_type();
   }


   void priv_delete_node(const node_ptr &n)
   {
      this->priv_destroy_node(*n);
      this->priv_put_in_pool(n);
   }


   template<class Iterator>
   void priv_build_node_from_it(const node_ptr &p, const index_iterator &up_index, const Iterator &it)
   {
      //This can throw
      boost::container::construct_in_place
         ( this->priv_node_alloc()
         , container_detail::addressof(p->value)
         , it);
      //This does not throw
      ::new(static_cast<node_base_type*>(container_detail::to_raw_pointer(p)))
         node_base_type(index_traits_type::ptr_to_node_base_ptr(*up_index));
   }


   template<class ValueConvertible>
   void priv_build_node_from_convertible(const node_ptr &p, BOOST_FWD_REF(ValueConvertible) value_convertible)
   {
      //This can throw
      boost::container::allocator_traits<node_allocator_type>::construct
         ( this->priv_node_alloc()
         , container_detail::addressof(p->value)
         , ::boost::forward<ValueConvertible>(value_convertible));
      //This does not throw
      ::new(static_cast<node_base_type*>(container_detail::to_raw_pointer(p))) node_base_type;
   }


   void priv_swap_members(stable_vector &x)
   {
      boost::container::swap_dispatch(this->internal_data.pool_size, x.internal_data.pool_size);
      index_traits_type::readjust_end_node(this->index, this->internal_data.end_node);
      index_traits_type::readjust_end_node(x.index, x.internal_data.end_node);
   }


   node_allocator_type &priv_node_alloc()              { return internal_data;  }

   const node_allocator_type &priv_node_alloc() const  { return internal_data;  }


template <typename T,typename Allocator>
bool operator==(const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}


template <typename T,typename Allocator>
bool operator< (const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}


template <typename T,typename Allocator>
bool operator!=(const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return !(x==y);
}


template <typename T,typename Allocator>
bool operator> (const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return y<x;
}


template <typename T,typename Allocator>
bool operator>=(const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return !(x<y);
}


template <typename T,typename Allocator>
bool operator<=(const stable_vector<T,Allocator>& x,const stable_vector<T,Allocator>& y)
{
   return !(x>y);
}


template <typename T, typename Allocator>
void swap(stable_vector<T,Allocator>& x,stable_vector<T,Allocator>& y)
{
   x.swap(y);
}

inline std::size_t deque_buf_size(std::size_t size)
   {  return size < 512 ? std::size_t(512 / size) : std::size_t(1);  }


   static size_type s_buffer_size() { return deque_buf_size(sizeof(T)); }


   val_alloc_ptr priv_allocate_node()
      {  return this->alloc().allocate(s_buffer_size());  }


   void priv_deallocate_node(val_alloc_ptr p)
      {  this->alloc().deallocate(p, s_buffer_size());  }


   ptr_alloc_ptr priv_allocate_map(size_type n)
      { return this->ptr_alloc().allocate(n); }


   void priv_deallocate_map(ptr_alloc_ptr p, size_type n)
      { this->ptr_alloc().deallocate(p, n); }

      static size_type s_buffer_size() { return deque_base<T, Allocator>::s_buffer_size(); }

      const_iterator(val_alloc_ptr x, index_pointer y)
         : m_cur(x), m_first(*y),
           m_last(*y + s_buffer_size()), m_node(y) {}


      const_iterator() : m_cur(0), m_first(0), m_last(0), m_node(0) {}


      const_iterator(const const_iterator& x)
         : m_cur(x.m_cur),   m_first(x.m_first),
           m_last(x.m_last), m_node(x.m_node) {}


      reference operator*() const
         { return *this->m_cur; }


      pointer operator->() const
         { return this->m_cur; }


      difference_type operator-(const self_t& x) const
      {
         if(!this->m_cur && !x.m_cur){
            return 0;
         }
         return difference_type(this->s_buffer_size()) * (this->m_node - x.m_node - 1) +
            (this->m_cur - this->m_first) + (x.m_last - x.m_cur);
      }


      self_t& operator++()
      {
         ++this->m_cur;
         if (this->m_cur == this->m_last) {
            this->priv_set_node(this->m_node + 1);
            this->m_cur = this->m_first;
         }
         return *this;
      }


      self_t operator++(int) 
      {
         self_t tmp = *this;
         ++*this;
         return tmp;
      }


      self_t& operator--()
      {
         if (this->m_cur == this->m_first) {
            this->priv_set_node(this->m_node - 1);
            this->m_cur = this->m_last;
         }
         --this->m_cur;
         return *this;
      }


      self_t operator--(int)
      {
         self_t tmp = *this;
         --*this;
         return tmp;
      }


      self_t& operator+=(difference_type n)
      {
         difference_type offset = n + (this->m_cur - this->m_first);
         if (offset >= 0 && offset < difference_type(this->s_buffer_size()))
            this->m_cur += n;
         else {
            difference_type node_offset =
            offset > 0 ? offset / difference_type(this->s_buffer_size())
                        : -difference_type((-offset - 1) / this->s_buffer_size()) - 1;
            this->priv_set_node(this->m_node + node_offset);
            this->m_cur = this->m_first +
            (offset - node_offset * difference_type(this->s_buffer_size()));
         }
         return *this;
      }


      self_t operator+(difference_type n) const
         {  self_t tmp = *this; return tmp += n;  }


      self_t& operator-=(difference_type n)
         { return *this += -n; }

      
      self_t operator-(difference_type n) const
         {  self_t tmp = *this; return tmp -= n;  }


      reference operator[](difference_type n) const
         { return *(*this + n); }


      bool operator==(const self_t& x) const
         { return this->m_cur == x.m_cur; }


      bool operator!=(const self_t& x) const
         { return !(*this == x); }


      bool operator<(const self_t& x) const
      {
         return (this->m_node == x.m_node) ?
            (this->m_cur < x.m_cur) : (this->m_node < x.m_node);
      }


      bool operator>(const self_t& x) const 
         { return x < *this; }


      bool operator<=(const self_t& x) const
         { return !(x < *this); }


      bool operator>=(const self_t& x) const
         { return !(*this < x); }


      void priv_set_node(index_pointer new_node)
      {
         this->m_node = new_node;
         this->m_first = *new_node;
         this->m_last = this->m_first + this->s_buffer_size();
      }

      explicit iterator(const const_iterator& x) : const_iterator(x){}

      iterator() : const_iterator(){}

      iterator(const iterator& x) : const_iterator(x){}

      reference operator*() const { return *this->m_cur; }

      pointer operator->() const { return this->m_cur; }


      reference operator[](difference_type n) const { return *(*this + n); }

      iterator& operator++() 
         { this->const_iterator::operator++(); return *this;  }


      iterator operator++(int)
         { iterator tmp = *this; ++*this; return tmp; }

     
      iterator& operator--()
         {  this->const_iterator::operator--(); return *this;  }


      iterator operator--(int)
         {  iterator tmp = *this; --*this; return tmp; }

      iterator& operator+=(difference_type off)
         {  this->const_iterator::operator+=(off); return *this;  }


      iterator operator+(difference_type off) const
         {  return iterator(this->const_iterator::operator+(off));  }


      iterator& operator-=(difference_type off)
         {  this->const_iterator::operator-=(off); return *this;   }


      iterator operator-(difference_type off) const
         {  return iterator(this->const_iterator::operator-(off));  }


      difference_type operator-(const const_iterator& right) const
         {  return static_cast<const const_iterator&>(*this) - right;   }


   deque_base(size_type num_elements, const allocator_type& a)
      :  members_(a)
   { this->priv_initialize_map(num_elements); }


   explicit deque_base(const allocator_type& a)
      :  members_(a)
   {}


   deque_base()
      :  members_()
   {}


   explicit deque_base(BOOST_RV_REF(deque_base) x)
      :  members_( boost::move(x.ptr_alloc())
                 , boost::move(x.alloc()) )
   {}


   ~deque_base()
   {
      if (this->members_.m_map) {
         this->priv_destroy_nodes(this->members_.m_start.m_node, this->members_.m_finish.m_node + 1);
         this->priv_deallocate_map(this->members_.m_map, this->members_.m_map_size);
      }
   }


   void swap_members(deque_base &x)
   {
      std::swap(this->members_.m_start, x.members_.m_start);
      std::swap(this->members_.m_finish, x.members_.m_finish);
      std::swap(this->members_.m_map, x.members_.m_map);
      std::swap(this->members_.m_map_size, x.members_.m_map_size);
   }


   void priv_initialize_map(size_type num_elements)
   {
//      if(num_elements){
         size_type num_nodes = num_elements / s_buffer_size() + 1;

         this->members_.m_map_size = container_detail::max_value((size_type) InitialMapSize, num_nodes + 2);
         this->members_.m_map = this->priv_allocate_map(this->members_.m_map_size);

         ptr_alloc_ptr nstart = this->members_.m_map + (this->members_.m_map_size - num_nodes) / 2;
         ptr_alloc_ptr nfinish = nstart + num_nodes;
            
         BOOST_TRY {
            this->priv_create_nodes(nstart, nfinish);
         }
         BOOST_CATCH(...){
            this->priv_deallocate_map(this->members_.m_map, this->members_.m_map_size);
            this->members_.m_map = 0;
            this->members_.m_map_size = 0;
            BOOST_RETHROW
         }
         BOOST_CATCH_END

         this->members_.m_start.priv_set_node(nstart);
         this->members_.m_finish.priv_set_node(nfinish - 1);
         this->members_.m_start.m_cur = this->members_.m_start.m_first;
         this->members_.m_finish.m_cur = this->members_.m_finish.m_first +
                        num_elements % s_buffer_size();
//      }
   }


   void priv_create_nodes(ptr_alloc_ptr nstart, ptr_alloc_ptr nfinish)
   {
      ptr_alloc_ptr cur;
      BOOST_TRY {
         for (cur = nstart; cur < nfinish; ++cur)
            *cur = this->priv_allocate_node();
      }
      BOOST_CATCH(...){
         this->priv_destroy_nodes(nstart, cur);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }


   void priv_destroy_nodes(ptr_alloc_ptr nstart, ptr_alloc_ptr nfinish)
   {
      for (ptr_alloc_ptr n = nstart; n < nfinish; ++n)
         this->priv_deallocate_node(*n);
   }


   void priv_clear_map()
   {
      if (this->members_.m_map) {
         this->priv_destroy_nodes(this->members_.m_start.m_node, this->members_.m_finish.m_node + 1);
         this->priv_deallocate_map(this->members_.m_map, this->members_.m_map_size);
         this->members_.m_map = 0;
         this->members_.m_map_size = 0;
         this->members_.m_start = iterator();
         this->members_.m_finish = this->members_.m_start;
      }
   }

      members_holder()
         :  map_allocator_type(), allocator_type()
         ,  m_map(0), m_map_size(0)
         ,  m_start(), m_finish(m_start)
      {}


      explicit members_holder(const allocator_type &a)
         :  map_allocator_type(a), allocator_type(a)
         ,  m_map(0), m_map_size(0)
         ,  m_start(), m_finish(m_start)
      {}


      template<class ValAllocConvertible, class PtrAllocConvertible>
      members_holder(BOOST_FWD_REF(PtrAllocConvertible) pa, BOOST_FWD_REF(ValAllocConvertible) va)
         : map_allocator_type(boost::forward<PtrAllocConvertible>(pa))
         , allocator_type    (boost::forward<ValAllocConvertible>(va))
         , m_map(0), m_map_size(0)
         , m_start(), m_finish(m_start)
      {}

      members_holder()
         :  map_allocator_type(), allocator_type()
         ,  m_map(0), m_map_size(0)
         ,  m_start(), m_finish(m_start)
      {}


      explicit members_holder(const allocator_type &a)
         :  map_allocator_type(a), allocator_type(a)
         ,  m_map(0), m_map_size(0)
         ,  m_start(), m_finish(m_start)
      {}


      template<class ValAllocConvertible, class PtrAllocConvertible>
      members_holder(BOOST_FWD_REF(PtrAllocConvertible) pa, BOOST_FWD_REF(ValAllocConvertible) va)
         : map_allocator_type(boost::forward<PtrAllocConvertible>(pa))
         , allocator_type    (boost::forward<ValAllocConvertible>(va))
         , m_map(0), m_map_size(0)
         , m_start(), m_finish(m_start)
      {}


   ptr_alloc_t &ptr_alloc()
   {  return members_;  }


   allocator_type &alloc()
   {  return members_;  }

  
   const allocator_type &alloc() const
   {  return members_;  }

   static size_type s_buffer_size()
      { return Base::s_buffer_size(); }

   deque()
      : Base()
   {}

template <class T, class Allocator>
inline bool operator==(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
{
   return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
}


template <class T, class Allocator>
inline bool operator<(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
{
   return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}


template <class T, class Allocator>
inline bool operator!=(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
   {  return !(x == y);   }


template <class T, class Allocator>
inline bool operator>(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
   {  return y < x; }


template <class T, class Allocator>
inline bool operator>=(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
   {  return !(x < y); }


template <class T, class Allocator>
inline bool operator<=(const deque<T, Allocator>& x, const deque<T, Allocator>& y)
   {  return !(y < x); }


template <class T, class Allocator>
inline void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
{  x.swap(y);  }


   basic_string_base()
      : members_()
   {  init(); }


   basic_string_base(const allocator_type& a)
      : members_(a)
   {  init(); }


   basic_string_base(const allocator_type& a, size_type n)
      : members_(a)
   { 
      this->init();
      this->allocate_initial_block(n);
   }


   basic_string_base(BOOST_RV_REF(basic_string_base) b)
      :  members_(boost::move(b.alloc()))
   { 
      this->init();
      this->swap_data(b);
   }


   ~basic_string_base()
   { 
      if(!this->is_short()){
         this->deallocate_block();
         this->is_short(true);
      }
   }


      long_t()
      {}


      long_t(const long_t &other)
      {
         this->is_short = other.is_short;
         length   = other.length;
         storage  = other.storage;
         start    = other.start;
      }


      long_t &operator =(const long_t &other)
      {
         this->is_short = other.is_short;
         length   = other.length;
         storage  = other.storage;
         start    = other.start;
         return *this;
      }


      const short_t &short_repr() const
      {  return s;  }


      const long_t &long_repr() const
      {  return *static_cast<const long_t*>(static_cast<const void*>(&r));  }


      short_t &short_repr()
      {  return s;  }


      long_t &long_repr()
      {  return *static_cast<long_t*>(static_cast<void*>(&r));  }

      members_holder()
         : Allocator()
      {}


      template<class AllocatorConvertible>
      explicit members_holder(BOOST_FWD_REF(AllocatorConvertible) a)
         :  Allocator(boost::forward<AllocatorConvertible>(a))
      {}

      members_holder()
         : Allocator()
      {}


      template<class AllocatorConvertible>
      explicit members_holder(BOOST_FWD_REF(AllocatorConvertible) a)
         :  Allocator(boost::forward<AllocatorConvertible>(a))
      {}


   const Allocator &alloc() const
   {  return members_;  }


   Allocator &alloc()
   {  return members_;  }

   bool is_short() const
   {  return static_cast<bool>(this->members_.m_repr.s.h.is_short != 0);  }


   void is_short(bool yes)
   {
      const bool was_short = this->is_short();
      if(yes && !was_short){
         allocator_traits_type::destroy
            ( this->alloc()
            , static_cast<long_t*>(static_cast<void*>(&this->members_.m_repr.r))
            );
         this->members_.m_repr.s.h.is_short = true;
      }
      else if(!yes && was_short){
         allocator_traits_type::construct
            ( this->alloc()
            , static_cast<long_t*>(static_cast<void*>(&this->members_.m_repr.r))
            );
         this->members_.m_repr.s.h.is_short = false;
      }
   }

   void init()
   {
      this->members_.m_repr.s.h.is_short = 1;
      this->members_.m_repr.s.h.length   = 0;
   }

      bool operator()(const typename Tr::char_type& x,
                      const typename Tr::char_type& y) const
         { return Tr::eq(x, y); }


      Not_within_traits(Pointer f, Pointer l)
         : m_first(f), m_last(l) {}


      bool operator()(const typename Tr::char_type& x) const
      {
         return std::find_if(m_first, m_last,
                        std::bind1st(Eq_traits<Tr>(), x)) == m_last;
      }


   basic_string(reserve_t, size_type n,
                const allocator_type& a = allocator_type())
      //Select allocator as in copy constructor as reserve_t-based constructors
      //are two step copies optimized for capacity
      : base_t( allocator_traits_type::select_on_container_copy_construction(a)
              , n + 1)
   { this->priv_terminate_string(); }

   basic_string()
      : base_t()
   { this->priv_terminate_string(); }


template <class CharT, class Traits, class Allocator> inline 
   basic_string<CharT,Traits,Allocator>
   operator+(const basic_string<CharT,Traits,Allocator>& x
            ,const basic_string<CharT,Traits,Allocator>& y)
{
   typedef basic_string<CharT,Traits,Allocator> str_t;
   typedef typename str_t::reserve_t reserve_t;
   reserve_t reserve;
   str_t result(reserve, x.size() + y.size(), x.get_stored_allocator());
   result.append(x);
   result.append(y);
   return result;
}


template <class CharT, class Traits, class Allocator> inline
   basic_string<CharT, Traits, Allocator> operator+
      (const CharT* s, basic_string<CharT, Traits, Allocator> y)
{
   y.insert(y.begin(), s, s + Traits::length(s));
   return y;
}


template <class CharT, class Traits, class Allocator> inline 
   basic_string<CharT,Traits,Allocator> operator+
      (basic_string<CharT,Traits,Allocator> x, const CharT* s)
{
   x += s;
   return x;
}


template <class CharT, class Traits, class Allocator> inline
   basic_string<CharT,Traits,Allocator> operator+
      (CharT c, basic_string<CharT,Traits,Allocator> y)
{
   y.insert(y.begin(), c);
   return y;
}


template <class CharT, class Traits, class Allocator> inline 
   basic_string<CharT,Traits,Allocator> operator+
      (basic_string<CharT,Traits,Allocator> x, const CharT c)
{
   x += c;
   return x;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator==(const basic_string<CharT,Traits,Allocator>& x,
           const basic_string<CharT,Traits,Allocator>& y)
{
   return x.size() == y.size() &&
          Traits::compare(x.data(), y.data(), x.size()) == 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator==(const CharT* s, const basic_string<CharT,Traits,Allocator>& y)
{
   typename basic_string<CharT,Traits,Allocator>::size_type n = Traits::length(s);
   return n == y.size() && Traits::compare(s, y.data(), n) == 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator==(const basic_string<CharT,Traits,Allocator>& x, const CharT* s)
{
   typename basic_string<CharT,Traits,Allocator>::size_type n = Traits::length(s);
   return x.size() == n && Traits::compare(x.data(), s, n) == 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator!=(const basic_string<CharT,Traits,Allocator>& x,
           const basic_string<CharT,Traits,Allocator>& y)
   {  return !(x == y);  }


template <class CharT, class Traits, class Allocator>
inline bool
operator!=(const CharT* s, const basic_string<CharT,Traits,Allocator>& y)
   {  return !(s == y); }


template <class CharT, class Traits, class Allocator>
inline bool
operator!=(const basic_string<CharT,Traits,Allocator>& x, const CharT* s)
   {  return !(x == s);   }


template <class CharT, class Traits, class Allocator>
inline bool
operator<(const basic_string<CharT,Traits,Allocator>& x, const basic_string<CharT,Traits,Allocator>& y)
{
   return x.compare(y) < 0;
//   return basic_string<CharT,Traits,Allocator>
//      ::s_compare(x.begin(), x.end(), y.begin(), y.end()) < 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator<(const CharT* s, const basic_string<CharT,Traits,Allocator>& y)
{
   return y.compare(s) > 0;
//   basic_string<CharT,Traits,Allocator>::size_type n = Traits::length(s);
//   return basic_string<CharT,Traits,Allocator>
//          ::s_compare(s, s + n, y.begin(), y.end()) < 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator<(const basic_string<CharT,Traits,Allocator>& x,
          const CharT* s)
{
   return x.compare(s) < 0;
//   basic_string<CharT,Traits,Allocator>::size_type n = Traits::length(s);
//   return basic_string<CharT,Traits,Allocator>
//      ::s_compare(x.begin(), x.end(), s, s + n) < 0;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator>(const basic_string<CharT,Traits,Allocator>& x,
          const basic_string<CharT,Traits,Allocator>& y) {
   return y < x;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator>(const CharT* s, const basic_string<CharT,Traits,Allocator>& y) {
   return y < s;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator>(const basic_string<CharT,Traits,Allocator>& x, const CharT* s)
{
   return s < x;
}


template <class CharT, class Traits, class Allocator>
inline bool
operator<=(const basic_string<CharT,Traits,Allocator>& x,
           const basic_string<CharT,Traits,Allocator>& y)
{
  return !(y < x);
}


template <class CharT, class Traits, class Allocator>
inline bool
operator<=(const CharT* s, const basic_string<CharT,Traits,Allocator>& y)
   {  return !(y < s);  }


template <class CharT, class Traits, class Allocator>
inline bool
operator<=(const basic_string<CharT,Traits,Allocator>& x, const CharT* s)
   {  return !(s < x);  }


template <class CharT, class Traits, class Allocator>
inline bool
operator>=(const basic_string<CharT,Traits,Allocator>& x,
           const basic_string<CharT,Traits,Allocator>& y)
   {  return !(x < y);  }


template <class CharT, class Traits, class Allocator>
inline bool
operator>=(const CharT* s, const basic_string<CharT,Traits,Allocator>& y)
   {  return !(s < y);  }


template <class CharT, class Traits, class Allocator>
inline bool
operator>=(const basic_string<CharT,Traits,Allocator>& x, const CharT* s)
   {  return !(x < s);  }

template <class CharT, class Traits, class Allocator>
inline void swap(basic_string<CharT,Traits,Allocator>& x, basic_string<CharT,Traits,Allocator>& y)
{  x.swap(y);  }

   list_const_iterator()
      : m_it()
   {}


   explicit list_const_iterator(const IIterator &it) 
      : m_it(it)
   {}

   const_reference operator*() const
   { return this->m_it->m_data;  }


   const_pointer   operator->() const
   { return ::boost::intrusive::pointer_traits<const_pointer>::pointer_to(this->m_it->m_data); }

   list_const_iterator& operator++()      
   { ++this->m_it;  return *this; }


   list_const_iterator operator++(int)     
   { IIterator tmp = this->m_it; ++*this; return list_const_iterator(tmp);  }


   list_const_iterator& operator--()
   { --this->m_it; return *this;   }


   list_const_iterator operator--(int)
   {  IIterator tmp = this->m_it; --*this; return list_const_iterator(tmp); }


   const IIterator &get() const
   {  return this->m_it;   }

   list_iterator()
      : const_iterator()
   {}


   explicit list_iterator(const IIterator &it)
      :  const_iterator(it)
   {}

   reference operator*()  const
   {  return  this->m_it->m_data;  }


   pointer   operator->() const
   { return ::boost::intrusive::pointer_traits<pointer>::pointer_to(this->m_it->m_data); }

   list_iterator& operator++() 
   { ++this->m_it; return *this;  }


   list_iterator operator++(int)
   { IIterator tmp = this->m_it; ++*this; return list_iterator(tmp); }


   list_iterator& operator--()
   { --this->m_it; return *this;   }


   list_iterator operator--(int)
   {  IIterator tmp = this->m_it; --*this; return list_iterator(tmp); }


   const IIterator &get() const
   {  return this->m_it;   }

      equal_to_value(const value_type &t)
         :  t_(t)
      {}


      bool operator()(const value_type &t)const
      {  return t_ == t;   }

      ValueCompareToNodeCompare(Pred pred)
         :  Pred(pred)
      {}


      bool operator()(const Node &a, const Node &b) const
      {  return static_cast<const Pred&>(*this)(a.m_data, b.m_data);  }


      bool operator()(const Node &a) const
      {  return static_cast<const Pred&>(*this)(a.m_data);  }

   list()
      : AllocHolder()
   {}

      insertion_functor(Icont &icont, typename Icont::const_iterator pos)
         :  icont_(icont), pos_(pos)
      {}


      void operator()(Node &n)
      {
         this->icont_.insert(pos_, n);
      }

      bool operator()(const value_type &a, const value_type &b) const
         {  return a < b;  }

      bool operator()(const value_type &a, const value_type &b) const
         {  return a == b;  }


template <class T, class Allocator>
inline bool operator==(const list<T,Allocator>& x, const list<T,Allocator>& y)
{
   if(x.size() != y.size()){
      return false;
   }
   typedef typename list<T,Allocator>::const_iterator const_iterator;
   const_iterator end1 = x.end();

   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   while (i1 != end1 && *i1 == *i2) {
      ++i1;
      ++i2;
   }
   return i1 == end1;
}


template <class T, class Allocator>
inline bool operator<(const list<T,Allocator>& x,
                      const list<T,Allocator>& y)
{
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}


template <class T, class Allocator>
inline bool operator!=(const list<T,Allocator>& x, const list<T,Allocator>& y)
{
  return !(x == y);
}


template <class T, class Allocator>
inline bool operator>(const list<T,Allocator>& x, const list<T,Allocator>& y)
{
  return y < x;
}


template <class T, class Allocator>
inline bool operator<=(const list<T,Allocator>& x, const list<T,Allocator>& y)
{
  return !(y < x);
}


template <class T, class Allocator>
inline bool operator>=(const list<T,Allocator>& x, const list<T,Allocator>& y)
{
  return !(x < y);
}


template <class T, class Allocator>
inline void swap(list<T, Allocator>& x, list<T, Allocator>& y)
{
  x.swap(y);
}

   set()
      : m_tree()
   {}

   explicit set(const Compare& comp,
                const allocator_type& a = allocator_type())
      : m_tree(comp, a)
   {}

   template <class InputIterator>
   set(InputIterator first, InputIterator last, const Compare& comp = Compare(),
         const allocator_type& a = allocator_type())
      : m_tree(true, first, last, comp, a)
   {}

   set(const set& x)
      : m_tree(x.m_tree)
   {}

   set(BOOST_RV_REF(set) x)
      : m_tree(boost::move(x.m_tree))
   {}

   set(const set& x, const allocator_type &a)
      : m_tree(x.m_tree, a)
   {}

   set& operator=(BOOST_COPY_ASSIGN_REF(set) x)
   {  m_tree = x.m_tree;   return *this;  }

   allocator_type get_allocator() const
   { return m_tree.get_allocator(); }

   const stored_allocator_type &get_stored_allocator() const
   { return m_tree.get_stored_allocator(); }

   iterator begin()
   { return m_tree.begin(); }

   iterator end()
   { return m_tree.end(); }

   reverse_iterator rbegin()
   { return m_tree.rbegin(); }

   reverse_iterator rend()
   { return m_tree.rend(); }

   const_iterator cbegin() const
   { return m_tree.cbegin(); }

   const_iterator cend() const
   { return m_tree.cend(); }

   const_reverse_iterator crbegin() const
   { return m_tree.crbegin(); }

   const_reverse_iterator crend() const
   { return m_tree.crend(); }

   bool empty() const
   { return m_tree.empty(); }

   size_type size() const
   { return m_tree.size(); }

   size_type max_size() const
   { return m_tree.max_size(); }


template <class Key, class Compare, class Allocator>
inline bool operator==(const set<Key,Compare,Allocator>& x,
                       const set<Key,Compare,Allocator>& y)
{  return x.m_tree == y.m_tree;  }


template <class Key, class Compare, class Allocator>
inline bool operator<(const set<Key,Compare,Allocator>& x,
                      const set<Key,Compare,Allocator>& y)
{  return x.m_tree < y.m_tree;   }


template <class Key, class Compare, class Allocator>
inline bool operator!=(const set<Key,Compare,Allocator>& x,
                       const set<Key,Compare,Allocator>& y)
{  return !(x == y);   }


template <class Key, class Compare, class Allocator>
inline bool operator>(const set<Key,Compare,Allocator>& x,
                      const set<Key,Compare,Allocator>& y)
{  return y < x; }


template <class Key, class Compare, class Allocator>
inline bool operator<=(const set<Key,Compare,Allocator>& x,
                       const set<Key,Compare,Allocator>& y)
{  return !(y < x); }


template <class Key, class Compare, class Allocator>
inline bool operator>=(const set<Key,Compare,Allocator>& x,
                       const set<Key,Compare,Allocator>& y)
{  return !(x < y);  }


template <class Key, class Compare, class Allocator>
inline void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y)
{  x.swap(y);  }

   multiset()
      : m_tree()
   {}

   explicit multiset(const Compare& comp,
                     const allocator_type& a = allocator_type())
      : m_tree(comp, a)
   {}

   template <class InputIterator>
   multiset(InputIterator first, InputIterator last,
            const Compare& comp = Compare(),
            const allocator_type& a = allocator_type())
      : m_tree(false, first, last, comp, a)
   {}

   multiset(const multiset& x)
      : m_tree(x.m_tree)
   {}

   multiset(BOOST_RV_REF(multiset) x)
      : m_tree(boost::move(x.m_tree))
   {}

   multiset(const multiset& x, const allocator_type &a)
      : m_tree(x.m_tree, a)
   {}

   multiset& operator=(BOOST_COPY_ASSIGN_REF(multiset) x)
   {  m_tree = x.m_tree;   return *this;  }

   allocator_type get_allocator() const
   { return m_tree.get_allocator(); }

   stored_allocator_type &get_stored_allocator()
   { return m_tree.get_stored_allocator(); }

   iterator begin()
   { return m_tree.begin(); }

   iterator end()
   { return m_tree.end(); }

   reverse_iterator rbegin()
   { return m_tree.rbegin(); }

   reverse_iterator rend()
   { return m_tree.rend(); }

   const_iterator cbegin() const
   { return m_tree.cbegin(); }

   const_iterator cend() const
   { return m_tree.cend(); }

   const_reverse_iterator crbegin() const
   { return m_tree.crbegin(); }

   const_reverse_iterator crend() const
   { return m_tree.crend(); }

   bool empty() const
   { return m_tree.empty(); }

   size_type size() const
   { return m_tree.size(); }

   size_type max_size() const
   { return m_tree.max_size(); }

   template <class KeyType>
   iterator priv_insert(BOOST_FWD_REF(KeyType) x)
   {  return m_tree.insert_equal(::boost::forward<KeyType>(x));  }


template <class Key, class Compare, class Allocator>
inline bool operator==(const multiset<Key,Compare,Allocator>& x,
                       const multiset<Key,Compare,Allocator>& y)
{  return x.m_tree == y.m_tree;  }


template <class Key, class Compare, class Allocator>
inline bool operator<(const multiset<Key,Compare,Allocator>& x,
                      const multiset<Key,Compare,Allocator>& y)
{  return x.m_tree < y.m_tree;   }


template <class Key, class Compare, class Allocator>
inline bool operator!=(const multiset<Key,Compare,Allocator>& x,
                       const multiset<Key,Compare,Allocator>& y)
{  return !(x == y);  }


template <class Key, class Compare, class Allocator>
inline bool operator>(const multiset<Key,Compare,Allocator>& x,
                      const multiset<Key,Compare,Allocator>& y)
{  return y < x;  }


template <class Key, class Compare, class Allocator>
inline bool operator<=(const multiset<Key,Compare,Allocator>& x,
                       const multiset<Key,Compare,Allocator>& y)
{  return !(y < x);  }


template <class Key, class Compare, class Allocator>
inline bool operator>=(const multiset<Key,Compare,Allocator>& x,
                       const multiset<Key,Compare,Allocator>& y)
{  return !(x < y);  }


template <class Key, class Compare, class Allocator>
inline void swap(multiset<Key,Compare,Allocator>& x, multiset<Key,Compare,Allocator>& y)
{  x.swap(y);  }


template<class D, class S>
static D &force(const S &s)
{  return *const_cast<D*>((reinterpret_cast<const D*>(&s))); }


template<class D, class S>
static D force_copy(S s)
{
   D *vp = reinterpret_cast<D *>(&s);
   return D(*vp);
}

   flat_map()
      : m_flat_tree() {}

   explicit flat_map(const Compare& comp, const allocator_type& a = allocator_type())
      : m_flat_tree(comp, container_detail::force<impl_allocator_type>(a)) {}

   template <class InputIterator>
   flat_map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
         const allocator_type& a = allocator_type())
      : m_flat_tree(true, first, last, comp, container_detail::force<impl_allocator_type>(a))
   {}

   flat_map(const flat_map& x)
      : m_flat_tree(x.m_flat_tree) {}

   flat_map(BOOST_RV_REF(flat_map) x)
      : m_flat_tree(boost::move(x.m_flat_tree))
   {}

   flat_map(const flat_map& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, a)
   {}

   flat_map& operator=(BOOST_COPY_ASSIGN_REF(flat_map) x)
   {  m_flat_tree = x.m_flat_tree;   return *this;  }

   mapped_type &priv_subscript(const key_type& k)
   {
      iterator i = lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first)){
         container_detail::value_init<mapped_type> m;
         i = insert(i, impl_value_type(k, ::boost::move(m.m_t)));
      }
      return (*i).second;
   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const flat_map<Key,T,Compare,Allocator>& x,
                       const flat_map<Key,T,Compare,Allocator>& y)
   {  return x.m_flat_tree == y.m_flat_tree;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<(const flat_map<Key,T,Compare,Allocator>& x,
                      const flat_map<Key,T,Compare,Allocator>& y)
   {  return x.m_flat_tree < y.m_flat_tree;   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator!=(const flat_map<Key,T,Compare,Allocator>& x,
                       const flat_map<Key,T,Compare,Allocator>& y)
   {  return !(x == y); }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>(const flat_map<Key,T,Compare,Allocator>& x,
                      const flat_map<Key,T,Compare,Allocator>& y)
   {  return y < x;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<=(const flat_map<Key,T,Compare,Allocator>& x,
                       const flat_map<Key,T,Compare,Allocator>& y)
   {  return !(y < x);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>=(const flat_map<Key,T,Compare,Allocator>& x,
                       const flat_map<Key,T,Compare,Allocator>& y)
   {  return !(x < y);  }


template <class Key, class T, class Compare, class Allocator>
inline void swap(flat_map<Key,T,Compare,Allocator>& x,
                 flat_map<Key,T,Compare,Allocator>& y)
   {  x.swap(y);  }

   flat_multimap()
      : m_flat_tree() {}

   explicit flat_multimap(const Compare& comp,
                          const allocator_type& a = allocator_type())
      : m_flat_tree(comp, container_detail::force<impl_allocator_type>(a)) { }

   template <class InputIterator>
   flat_multimap(InputIterator first, InputIterator last,
            const Compare& comp        = Compare(),
            const allocator_type& a = allocator_type())
      : m_flat_tree(false, first, last, comp, container_detail::force<impl_allocator_type>(a))
   {}

   flat_multimap(const flat_multimap& x)
      : m_flat_tree(x.m_flat_tree) { }

   flat_multimap(BOOST_RV_REF(flat_multimap) x)
      : m_flat_tree(boost::move(x.m_flat_tree))
   {}

   flat_multimap(const flat_multimap& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, a)
   {}

   flat_multimap& operator=(BOOST_COPY_ASSIGN_REF(flat_multimap) x)
      {  m_flat_tree = x.m_flat_tree;   return *this;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const flat_multimap<Key,T,Compare,Allocator>& x,
                       const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return x.m_flat_tree == y.m_flat_tree;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<(const flat_multimap<Key,T,Compare,Allocator>& x,
                      const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return x.m_flat_tree < y.m_flat_tree;   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator!=(const flat_multimap<Key,T,Compare,Allocator>& x,
                       const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return !(x == y);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>(const flat_multimap<Key,T,Compare,Allocator>& x,
                      const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return y < x;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<=(const flat_multimap<Key,T,Compare,Allocator>& x,
                       const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return !(y < x);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>=(const flat_multimap<Key,T,Compare,Allocator>& x,
                       const flat_multimap<Key,T,Compare,Allocator>& y)
   {  return !(x < y);  }


template <class Key, class T, class Compare, class Allocator>
inline void swap(flat_multimap<Key,T,Compare,Allocator>& x, flat_multimap<Key,T,Compare,Allocator>& y)
   {  x.swap(y);  }

   map()
      : m_tree()
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   explicit map(const Compare& comp,
                const allocator_type& a = allocator_type())
      : m_tree(comp, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   template <class InputIterator>
   map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
         const allocator_type& a = allocator_type())
      : m_tree(true, first, last, comp, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   map(const map& x)
      : m_tree(x.m_tree)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   map(BOOST_RV_REF(map) x)
      : m_tree(boost::move(x.m_tree))
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   map(const map& x, const allocator_type &a)
      : m_tree(x.m_tree, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   map& operator=(BOOST_COPY_ASSIGN_REF(map) x)
   {  m_tree = x.m_tree;   return *this;  }

   mapped_type& priv_subscript(const key_type &k)
   {
      //we can optimize this
      iterator i = lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first)){
         container_detail::value_init<mapped_type> m;
         movable_value_type val(k, boost::move(m.m_t));
         i = insert(i, boost::move(val));
      }
      return (*i).second;
   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const map<Key,T,Compare,Allocator>& x,
                       const map<Key,T,Compare,Allocator>& y)
   {  return x.m_tree == y.m_tree;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<(const map<Key,T,Compare,Allocator>& x,
                      const map<Key,T,Compare,Allocator>& y)
   {  return x.m_tree < y.m_tree;   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator!=(const map<Key,T,Compare,Allocator>& x,
                       const map<Key,T,Compare,Allocator>& y)
   {  return !(x == y); }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>(const map<Key,T,Compare,Allocator>& x,
                      const map<Key,T,Compare,Allocator>& y)
   {  return y < x;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<=(const map<Key,T,Compare,Allocator>& x,
                       const map<Key,T,Compare,Allocator>& y)
   {  return !(y < x);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>=(const map<Key,T,Compare,Allocator>& x,
                       const map<Key,T,Compare,Allocator>& y)
   {  return !(x < y);  }


template <class Key, class T, class Compare, class Allocator>
inline void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
   {  x.swap(y);  }

   multimap()
      : m_tree()
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   explicit multimap(const Compare& comp, const allocator_type& a = allocator_type())
      : m_tree(comp, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   template <class InputIterator>
   multimap(InputIterator first, InputIterator last,
            const Compare& comp = Compare(),
            const allocator_type& a = allocator_type())
      : m_tree(false, first, last, comp, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   multimap(const multimap& x)
      : m_tree(x.m_tree)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   multimap(BOOST_RV_REF(multimap) x)
      : m_tree(boost::move(x.m_tree))
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   multimap(const multimap& x, const allocator_type &a)
      : m_tree(x.m_tree, a)
   {
      //Allocator type must be std::pair<CONST Key, T>
      BOOST_STATIC_ASSERT((container_detail::is_same<std::pair<const Key, T>, typename Allocator::value_type>::value));
   }

   multimap& operator=(BOOST_COPY_ASSIGN_REF(multimap) x)
   {  m_tree = x.m_tree;   return *this;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const multimap<Key,T,Compare,Allocator>& x,
                       const multimap<Key,T,Compare,Allocator>& y)
{  return x.m_tree == y.m_tree;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<(const multimap<Key,T,Compare,Allocator>& x,
                      const multimap<Key,T,Compare,Allocator>& y)
{  return x.m_tree < y.m_tree;   }


template <class Key, class T, class Compare, class Allocator>
inline bool operator!=(const multimap<Key,T,Compare,Allocator>& x,
                       const multimap<Key,T,Compare,Allocator>& y)
{  return !(x == y);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>(const multimap<Key,T,Compare,Allocator>& x,
                      const multimap<Key,T,Compare,Allocator>& y)
{  return y < x;  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator<=(const multimap<Key,T,Compare,Allocator>& x,
                       const multimap<Key,T,Compare,Allocator>& y)
{  return !(y < x);  }


template <class Key, class T, class Compare, class Allocator>
inline bool operator>=(const multimap<Key,T,Compare,Allocator>& x,
                       const multimap<Key,T,Compare,Allocator>& y)
{  return !(x < y);  }


template <class Key, class T, class Compare, class Allocator>
inline void swap(multimap<Key,T,Compare,Allocator>& x, multimap<Key,T,Compare,Allocator>& y)
{  x.swap(y);  }


template <class T, class Allocator>
inline bool
operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
   //Check first size and each element if needed
   return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}


template <class T, class Allocator>
inline bool
operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
   //Check first size and each element if needed
  return x.size() != y.size() || !std::equal(x.begin(), x.end(), y.begin());
}


template <class T, class Allocator>
inline bool
operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
{
   return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

   slist_const_iterator()
      : m_it()
   {}


   explicit slist_const_iterator(const IIterator &it) 
      : m_it(it)
   {}

   const_reference operator*() const
   { return this->m_it->m_data;  }


   const_pointer   operator->() const
   { return ::boost::intrusive::pointer_traits<const_pointer>::pointer_to(this->m_it->m_data); }

   slist_const_iterator& operator++()      
   { ++this->m_it;  return *this; }


   slist_const_iterator operator++(int)     
   { IIterator tmp = this->m_it; ++*this; return slist_const_iterator(tmp);  }


   const IIterator &get() const
   {  return this->m_it;   }

   slist_iterator()
      : const_iterator()
   {}


   explicit slist_iterator(const IIterator &it)
      :  const_iterator(it)
   {}

   reference operator*()  const
   {  return  this->m_it->m_data;  }


   pointer   operator->() const
   { return ::boost::intrusive::pointer_traits<pointer>::pointer_to(this->m_it->m_data); }

   slist_iterator& operator++() 
   { ++this->m_it; return *this;  }


   slist_iterator operator++(int)
   { IIterator tmp = this->m_it; ++*this; return slist_iterator(tmp); }


   const IIterator &get() const
   {  return this->m_it;   }

      equal_to_value(const value_type &t)
         :  t_(t)
      {}


      bool operator()(const value_type &t)const
      {  return t_ == t;   }

      ValueCompareToNodeCompare(Pred pred)
         :  Pred(pred)
      {}


      bool operator()(const Node &a, const Node &b) const
      {  return static_cast<const Pred&>(*this)(a.m_data, b.m_data);  }


      bool operator()(const Node &a) const
      {  return static_cast<const Pred&>(*this)(a.m_data);  }

   slist()
      :  AllocHolder()
   {}

      insertion_functor(Icont &icont, typename Icont::const_iterator prev)
         :  icont_(icont), prev_(prev), ret_(prev.unconst())
      {}


      void operator()(Node &n)
      {
         ret_ = this->icont_.insert_after(prev_, n);
      }


      iiterator inserted_first() const
      {  return ret_;   }

      bool operator()(const value_type &a, const value_type &b) const
         {  return a < b;  }

      bool operator()(const value_type &a, const value_type &b) const
         {  return a == b;  }

      explicit value_equal_to_this(const value_type &ref)
         : m_ref(ref){}


      bool operator()(const value_type &val) const
         {  return m_ref == val;  }


template <class T, class Allocator>
inline bool
operator==(const slist<T,Allocator>& x, const slist<T,Allocator>& y)
{
   if(x.size() != y.size()){
      return false;
   }
   typedef typename slist<T,Allocator>::const_iterator const_iterator;
   const_iterator end1 = x.end();

   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   while (i1 != end1 && *i1 == *i2){
      ++i1;
      ++i2;
   }
   return i1 == end1;
}


template <class T, class Allocator>
inline bool
operator<(const slist<T,Allocator>& sL1, const slist<T,Allocator>& sL2)
{
   return std::lexicographical_compare
      (sL1.begin(), sL1.end(), sL2.begin(), sL2.end());
}


template <class T, class Allocator>
inline bool
operator!=(const slist<T,Allocator>& sL1, const slist<T,Allocator>& sL2)
   {  return !(sL1 == sL2);   }


template <class T, class Allocator>
inline bool
operator>(const slist<T,Allocator>& sL1, const slist<T,Allocator>& sL2)
   {  return sL2 < sL1; }


template <class T, class Allocator>
inline bool
operator<=(const slist<T,Allocator>& sL1, const slist<T,Allocator>& sL2)
   {  return !(sL2 < sL1); }


template <class T, class Allocator>
inline bool
operator>=(const slist<T,Allocator>& sL1, const slist<T,Allocator>& sL2)
   {  return !(sL1 < sL2); }


template <class T, class Allocator>
inline void swap(slist<T,Allocator>& x, slist<T,Allocator>& y)
   {  x.swap(y);  }


   insert_iterator(Container& x,
                   typename Container::iterator i,
                   bool is_previous = false)
      : container(&x), iter(is_previous ? i : x.previous(i)){ }


   insert_iterator<Container>&
      operator=(const typename Container::value_type& value)
   {
      iter = container->insert_after(iter, value);
      return *this;
   }

   insert_iterator<Container>& operator*(){ return *this; }

   insert_iterator<Container>& operator++(){ return *this; }

   explicit flat_set()
      : m_flat_tree()
   {}

   explicit flat_set(const Compare& comp,
                     const allocator_type& a = allocator_type())
      : m_flat_tree(comp, a)
   {}

   template <class InputIterator>
   flat_set(InputIterator first, InputIterator last,
            const Compare& comp = Compare(),
            const allocator_type& a = allocator_type())
      : m_flat_tree(true, first, last, comp, a)
   {}

   flat_set(const flat_set& x)
      : m_flat_tree(x.m_flat_tree)
   {}

   flat_set(BOOST_RV_REF(flat_set) mx)
      : m_flat_tree(boost::move(mx.m_flat_tree))
   {}

   flat_set(const flat_set& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, a)
   {}

   flat_set& operator=(BOOST_COPY_ASSIGN_REF(flat_set) x)
      {  m_flat_tree = x.m_flat_tree;   return *this;  }


template <class Key, class Compare, class Allocator>
inline bool operator==(const flat_set<Key,Compare,Allocator>& x,
                       const flat_set<Key,Compare,Allocator>& y)
   {  return x.m_flat_tree == y.m_flat_tree;  }


template <class Key, class Compare, class Allocator>
inline bool operator<(const flat_set<Key,Compare,Allocator>& x,
                      const flat_set<Key,Compare,Allocator>& y)
   {  return x.m_flat_tree < y.m_flat_tree;   }


template <class Key, class Compare, class Allocator>
inline bool operator!=(const flat_set<Key,Compare,Allocator>& x,
                       const flat_set<Key,Compare,Allocator>& y)
   {  return !(x == y);   }


template <class Key, class Compare, class Allocator>
inline bool operator>(const flat_set<Key,Compare,Allocator>& x,
                      const flat_set<Key,Compare,Allocator>& y)
   {  return y < x; }


template <class Key, class Compare, class Allocator>
inline bool operator<=(const flat_set<Key,Compare,Allocator>& x,
                       const flat_set<Key,Compare,Allocator>& y)
   {  return !(y < x); }


template <class Key, class Compare, class Allocator>
inline bool operator>=(const flat_set<Key,Compare,Allocator>& x,
                       const flat_set<Key,Compare,Allocator>& y)
   {  return !(x < y);  }


template <class Key, class Compare, class Allocator>
inline void swap(flat_set<Key,Compare,Allocator>& x, flat_set<Key,Compare,Allocator>& y)
   {  x.swap(y);  }

   explicit flat_multiset()
      : m_flat_tree()
   {}


   explicit flat_multiset(const Compare& comp,
                          const allocator_type& a = allocator_type())
      : m_flat_tree(comp, a) {}


   template <class InputIterator>
   flat_multiset(InputIterator first, InputIterator last,
                 const Compare& comp        = Compare(),
                 const allocator_type& a = allocator_type())
      : m_flat_tree(false, first, last, comp, a)
   {}

   flat_multiset(const flat_multiset& x)
      : m_flat_tree(x.m_flat_tree)
   {}

   flat_multiset(BOOST_RV_REF(flat_multiset) mx)
      : m_flat_tree(boost::move(mx.m_flat_tree))
   {}

   flat_multiset(const flat_multiset& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, a)
   {}

   flat_multiset& operator=(BOOST_COPY_ASSIGN_REF(flat_multiset) x)
      {  m_flat_tree = x.m_flat_tree;   return *this;  }

   template <class KeyType>
   iterator priv_insert(BOOST_FWD_REF(KeyType) x)
   {  return m_flat_tree.insert_equal(::boost::forward<KeyType>(x));  }


template <class Key, class Compare, class Allocator>
inline bool operator==(const flat_multiset<Key,Compare,Allocator>& x,
                       const flat_multiset<Key,Compare,Allocator>& y)
   {  return x.m_flat_tree == y.m_flat_tree;  }


template <class Key, class Compare, class Allocator>
inline bool operator<(const flat_multiset<Key,Compare,Allocator>& x,
                      const flat_multiset<Key,Compare,Allocator>& y)
   {  return x.m_flat_tree < y.m_flat_tree;   }


template <class Key, class Compare, class Allocator>
inline bool operator!=(const flat_multiset<Key,Compare,Allocator>& x,
                       const flat_multiset<Key,Compare,Allocator>& y)
   {  return !(x == y);  }


template <class Key, class Compare, class Allocator>
inline bool operator>(const flat_multiset<Key,Compare,Allocator>& x,
                      const flat_multiset<Key,Compare,Allocator>& y)
   {  return y < x;  }


template <class Key, class Compare, class Allocator>
inline bool operator<=(const flat_multiset<Key,Compare,Allocator>& x,
                       const flat_multiset<Key,Compare,Allocator>& y)
   {  return !(y < x);  }


template <class Key, class Compare, class Allocator>
inline bool operator>=(const flat_multiset<Key,Compare,Allocator>& x,
                       const flat_multiset<Key,Compare,Allocator>& y)
{  return !(x < y);  }


template <class Key, class Compare, class Allocator>
inline void swap(flat_multiset<Key,Compare,Allocator>& x, flat_multiset<Key,Compare,Allocator>& y)
   {  x.swap(y);  }

   dummy()
   {
      (void)ordered_range;
      (void)ordered_unique_range;
   }

   static pointer allocate(Alloc &a, size_type n)
   {  return a.allocate(n);  }

   static void deallocate(Alloc &a, pointer p, size_type n)
   {  a.deallocate(p, n);  }

   template<class T>
   static void destroy(Alloc &a, T*p)
   {
      typedef T* destroy_pointer;
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_destroy
            <Alloc, const destroy_pointer>::value;
      ::boost::integral_constant<bool, value> flag;
      allocator_traits::priv_destroy(flag, a, p);
   }

   static size_type max_size(const Alloc &a)
   {
      const bool value = boost::container::container_detail::
         has_member_function_callable_with_max_size
            <const Alloc>::value;
      ::boost::integral_constant<bool, value> flag;
      return allocator_traits::priv_max_size(flag, a);
   }

   explicit constant_iterator(const T &ref, Difference range_size)
      :  m_ptr(&ref), m_num(range_size){}

   constant_iterator()
      :  m_ptr(0), m_num(0){}


   constant_iterator& operator++()
   { increment();   return *this;   }

  
   constant_iterator operator++(int)
   {
      constant_iterator result (*this);
      increment();
      return result;
   }


   constant_iterator& operator--()
   { decrement();   return *this;   }

  
   constant_iterator operator--(int)
   {
      constant_iterator result (*this);
      decrement();
      return result;
   }

   constant_iterator& operator+=(Difference off)
   {  this->advance(off); return *this;   }


   constant_iterator operator+(Difference off) const
   {
      constant_iterator other(*this);
      other.advance(off);
      return other;
   }


   constant_iterator& operator-=(Difference off)
   {  this->advance(-off); return *this;   }


   constant_iterator operator-(Difference off) const
   {  return *this + (-off);  }


   const T& operator*() const
   { return dereference(); }


   const T& operator[] (Difference ) const
   { return dereference(); }


   const T* operator->() const
   { return &(dereference()); }


   void increment()
   { --m_num; }


   void decrement()
   { ++m_num; }


   bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }


   bool less(const this_type &other) const
   {  return other.m_num < m_num;   }


   const T & dereference() const
   { return *m_ptr; }


   void advance(Difference n)
   {  m_num -= n; }


   Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }

   explicit default_construct_iterator(Difference range_size)
      :  m_num(range_size){}

   default_construct_iterator()
      :  m_num(0){}


   default_construct_iterator& operator++()
   { increment();   return *this;   }

  
   default_construct_iterator operator++(int)
   {
      default_construct_iterator result (*this);
      increment();
      return result;
   }


   default_construct_iterator& operator--()
   { decrement();   return *this;   }

  
   default_construct_iterator operator--(int)
   {
      default_construct_iterator result (*this);
      decrement();
      return result;
   }

   default_construct_iterator& operator+=(Difference off)
   {  this->advance(off); return *this;   }


   default_construct_iterator operator+(Difference off) const
   {
      default_construct_iterator other(*this);
      other.advance(off);
      return other;
   }


   default_construct_iterator& operator-=(Difference off)
   {  this->advance(-off); return *this;   }


   default_construct_iterator operator-(Difference off) const
   {  return *this + (-off);  }


   void increment()
   { --m_num; }


   void decrement()
   { ++m_num; }


   bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }


   bool less(const this_type &other) const
   {  return other.m_num < m_num;   }


   const T & dereference() const
   {
      static T dummy;
      return dummy;
   }


   void advance(Difference n)
   {  m_num -= n; }


   Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }

   explicit repeat_iterator(T &ref, Difference range_size)
      :  m_ptr(&ref), m_num(range_size){}

   repeat_iterator()
      :  m_ptr(0), m_num(0){}


   this_type& operator++()
   { increment();   return *this;   }

  
   this_type operator++(int)
   {
      this_type result (*this);
      increment();
      return result;
   }


   this_type& operator--()
   { increment();   return *this;   }

  
   this_type operator--(int)
   {
      this_type result (*this);
      increment();
      return result;
   }

   this_type& operator+=(Difference off)
   {  this->advance(off); return *this;   }


   this_type operator+(Difference off) const
   {
      this_type other(*this);
      other.advance(off);
      return other;
   }


   this_type& operator-=(Difference off)
   {  this->advance(-off); return *this;   }


   this_type operator-(Difference off) const
   {  return *this + (-off);  }


   T& operator*() const
   { return dereference(); }


   T& operator[] (Difference ) const
   { return dereference(); }


   T *operator->() const
   { return &(dereference()); }


   void increment()
   { --m_num; }


   void decrement()
   { ++m_num; }


   bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }


   bool less(const this_type &other) const
   {  return other.m_num < m_num;   }


   T & dereference() const
   { return *m_ptr; }


   void advance(Difference n)
   {  m_num -= n; }


   Difference distance_to(const this_type &other)const
   {  return m_num - other.m_num;   }

   explicit emplace_iterator(EmplaceFunctor&e)
      :  m_num(1), m_pe(&e){}


   emplace_iterator()
      :  m_num(0), m_pe(0){}


   this_type& operator++()
   { increment();   return *this;   }

  
   this_type operator++(int)
   {
      this_type result (*this);
      increment();
      return result;
   }


   this_type& operator--()
   { decrement();   return *this;   }

  
   this_type operator--(int)
   {
      this_type result (*this);
      decrement();
      return result;
   }

   this_type& operator+=(difference_type off)
   {  this->advance(off); return *this;   }


   this_type operator+(difference_type off) const
   {
      this_type other(*this);
      other.advance(off);
      return other;
   }


   this_type& operator-=(difference_type off)
   {  this->advance(-off); return *this;   }


   this_type operator-(difference_type off) const
   {  return *this + (-off);  }


   template<class A>
   void construct_in_place(A &a, T* ptr)
   {  (*m_pe)(a, ptr);  }


   void increment()
   { --m_num; }


   void decrement()
   { ++m_num; }


   bool equal(const this_type &other) const
   {  return m_num == other.m_num;   }


   bool less(const this_type &other) const
   {  return other.m_num < m_num;   }


   const T & dereference() const
   {
      static T dummy;
      return dummy;
   }


   void advance(difference_type n)
   {  m_num -= n; }


   difference_type distance_to(const this_type &other)const
   {  return difference_type(m_num - other.m_num);   }

   private_node_pool_impl(segment_manager_base_type *segment_mngr_base, size_type node_size, size_type nodes_per_block)
   :  m_nodes_per_block(nodes_per_block)
   ,  m_real_node_size(lcm(node_size, size_type(alignment_of<node_t>::value)))
      //General purpose allocator
   ,  mp_segment_mngr_base(segment_mngr_base)
   ,  m_blocklist()
   ,  m_freelist()
      //Debug node count
   ,  m_allocated(0)
   {}

   ~private_node_pool_impl()
   {  this->purge_blocks();  }


   size_type get_real_num_node() const
   {  return m_nodes_per_block; }

   segment_manager_base_type* get_segment_manager_base()const
   {  return container_detail::to_raw_pointer(mp_segment_mngr_base);  }


   void *allocate_node()
   {  return this->priv_alloc_node();  }

   void deallocate_node(void *ptr)
   {  this->priv_dealloc_node(ptr); }

   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      //Preallocate all needed blocks to fulfill the request
      size_type cur_nodes = m_freelist.size();
      if(cur_nodes < n){
         this->priv_alloc_block(((n - cur_nodes) - 1)/m_nodes_per_block + 1);
      }

      //We just iterate the needed nodes to get the last we'll erase
      typedef typename free_nodes_t::iterator free_iterator;
      free_iterator before_last_new_it = m_freelist.before_begin();
      for(size_type j = 0; j != n; ++j){
         ++before_last_new_it;
      }

      //Cache the first node of the allocated range before erasing
      free_iterator first_node(m_freelist.begin());
      free_iterator last_node (before_last_new_it);

      //Erase the range. Since we already have the distance, this is O(1)
      m_freelist.erase_after( m_freelist.before_begin()
                            , ++free_iterator(before_last_new_it)
                            , n);

      //Now take the last erased node and just splice it in the end
      //of the intrusive list that will be traversed by the multialloc iterator.
      chain.incorporate_after(chain.before_begin(), &*first_node, &*last_node, n);
      m_allocated += n;
   }


   void deallocate_nodes(multiallocation_chain &chain)
   {
      typedef typename multiallocation_chain::iterator iterator;
      iterator it(chain.begin()), itend(chain.end());
      while(it != itend){
         void *pElem = &*it;
         ++it;
         this->priv_dealloc_node(pElem);
      }
   }

   void deallocate_free_blocks()
   {
      typedef typename free_nodes_t::iterator nodelist_iterator;
      typename blockslist_t::iterator bit(m_blocklist.before_begin()),
                                      it(m_blocklist.begin()),
                                      itend(m_blocklist.end());
      free_nodes_t backup_list;
      nodelist_iterator backup_list_last = backup_list.before_begin();

      //Execute the algorithm and get an iterator to the last value
      size_type blocksize = get_rounded_size
         (m_real_node_size*m_nodes_per_block, (size_type) alignment_of<node_t>::value);

      while(it != itend){
         //Collect all the nodes from the block pointed by it
         //and push them in the list
         free_nodes_t free_nodes;
         nodelist_iterator last_it = free_nodes.before_begin();
         const void *addr = get_block_from_hook(&*it, blocksize);

         m_freelist.remove_and_dispose_if
            (is_between(addr, blocksize), push_in_list(free_nodes, last_it));

         //If the number of nodes is equal to m_nodes_per_block
         //this means that the block can be deallocated
         if(free_nodes.size() == m_nodes_per_block){
            //Unlink the nodes
            free_nodes.clear();
            it = m_blocklist.erase_after(bit);
            mp_segment_mngr_base->deallocate((void*)addr);
         }
         //Otherwise, insert them in the backup list, since the
         //next "remove_if" does not need to check them again.
         else{
            //Assign the iterator to the last value if necessary
            if(backup_list.empty() && !m_freelist.empty()){
               backup_list_last = last_it;
            }
            //Transfer nodes. This is constant time.
            backup_list.splice_after
               ( backup_list.before_begin()
               , free_nodes
               , free_nodes.before_begin()
               , last_it
               , free_nodes.size());
            bit = it;
            ++it;
         }
      }
      //We should have removed all the nodes from the free list
      BOOST_ASSERT(m_freelist.empty());

      //Now pass all the node to the free list again
      m_freelist.splice_after
         ( m_freelist.before_begin()
         , backup_list
         , backup_list.before_begin()
         , backup_list_last
         , backup_list.size());
   }


   size_type num_free_nodes()
   {  return m_freelist.size();  }

   void purge_blocks()
   {
      //check for memory leaks
      BOOST_ASSERT(m_allocated==0);
      size_type blocksize = get_rounded_size
         (m_real_node_size*m_nodes_per_block, (size_type)alignment_of<node_t>::value);

      //We iterate though the NodeBlock list to free the memory
      while(!m_blocklist.empty()){
         void *addr = get_block_from_hook(&m_blocklist.front(), blocksize);
         m_blocklist.pop_front();
         mp_segment_mngr_base->deallocate((void*)addr);
      }
      //Just clear free node list
      m_freelist.clear();
   }


   void swap(private_node_pool_impl &other)
   {
      BOOST_ASSERT(m_nodes_per_block == other.m_nodes_per_block);
      BOOST_ASSERT(m_real_node_size == other.m_real_node_size);
      std::swap(mp_segment_mngr_base, other.mp_segment_mngr_base);
      m_blocklist.swap(other.m_blocklist);
      m_freelist.swap(other.m_freelist);
      std::swap(m_allocated, other.m_allocated);
   }

      push_in_list(free_nodes_t &l, typename free_nodes_t::iterator &it)
         :  slist_(l), last_it_(it)
      {}

     
      void operator()(typename free_nodes_t::pointer p) const
      {
         slist_.push_front(*p);
         if(slist_.size() == 1){ //Cache last element
            ++last_it_ = slist_.begin();
         }
      }

      is_between(const void *addr, std::size_t size)
         :  beg_(static_cast<const char *>(addr)), end_(beg_+size)
      {}

     
      bool operator()(typename free_nodes_t::const_reference v) const
      {
         return (beg_ <= reinterpret_cast<const char *>(&v) &&
                 end_ >  reinterpret_cast<const char *>(&v));
      }

   node_t *priv_alloc_node()
   {
      //If there are no free nodes we allocate a new block
      if (m_freelist.empty())
         this->priv_alloc_block(1);
      //We take the first free node
      node_t *n = (node_t*)&m_freelist.front();
      m_freelist.pop_front();
      ++m_allocated;
      return n;
   }

   void priv_dealloc_node(void *pElem)
   {
      //We put the node at the beginning of the free node list
      node_t * to_deallocate = static_cast<node_t*>(pElem);
      m_freelist.push_front(*to_deallocate);
      BOOST_ASSERT(m_allocated>0);
      --m_allocated;
   }

   void priv_alloc_block(size_type num_blocks)
   {
      BOOST_ASSERT(num_blocks > 0);
      size_type blocksize =
         get_rounded_size(m_real_node_size*m_nodes_per_block, (size_type)alignment_of<node_t>::value);

      BOOST_TRY{
         for(size_type i = 0; i != num_blocks; ++i){
            //We allocate a new NodeBlock and put it as first
            //element in the free Node list
            char *pNode = reinterpret_cast<char*>
               (mp_segment_mngr_base->allocate(blocksize + sizeof(node_t)));
            char *pBlock = pNode;
            m_blocklist.push_front(get_block_hook(pBlock, blocksize));

            //We initialize all Nodes in Node Block to insert
            //them in the free Node list
            for(size_type j = 0; j < m_nodes_per_block; ++j, pNode += m_real_node_size){
               m_freelist.push_front(*new (pNode) node_t);
            }
         }
      }
      BOOST_CATCH(...){
         //to-do: if possible, an efficient way to deallocate allocated blocks
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   void deallocate_free_chunks()
   {  this->deallocate_free_blocks(); }

   void purge_chunks()
   {  this->purge_blocks(); }

   static node_t & get_block_hook (void *block, size_type blocksize)
   { 
      return *reinterpret_cast<node_t*>(reinterpret_cast<char*>(block) + blocksize); 
   }

   void *get_block_from_hook (node_t *hook, size_type blocksize)
   { 
      return (reinterpret_cast<char*>(hook) - blocksize);
   }

   static pointer allocate_one(Allocator &a)
   {  return a.allocate(1);   }


   static void deallocate_one(Allocator &a, const pointer &p)
   {  a.deallocate(p, 1);   }


   static void deallocate_individual(Allocator &a, multiallocation_chain &holder)
   {
      while(!holder.empty()){
         a.deallocate(holder.pop_front(), 1);
      }
   }

      allocate_individual_rollback(Allocator &a, multiallocation_chain &chain)
         : mr_a(a), mp_chain(&chain)
      {}


      ~allocate_individual_rollback()
      {
         if(mp_chain)
            allocator_version_traits::deallocate_individual(mr_a, *mp_chain);
      }


      void release()
      {
         mp_chain = 0;
      }


   static void allocate_individual(Allocator &a, size_type n, multiallocation_chain &m)
   {
      allocate_individual_rollback rollback(a, m);
      while(n--){
         m.push_front(a.allocate(1));
      }
      rollback.release();
   }


   node_compare(const ValueCompare &pred)
      :  ValueCompare(pred)
   {}


   ValueCompare &value_comp()
   {  return static_cast<ValueCompare &>(*this);  }


   ValueCompare &value_comp() const
   {  return static_cast<const ValueCompare &>(*this);  }


   bool operator()(const Node &a, const Node &b) const
   {  return ValueCompare::operator()(a.get_data(), b.get_data());  }

      members_holder()
         : NodeAlloc(), m_icont()
      {}


      template<class ConvertibleToAlloc>
      explicit members_holder(BOOST_FWD_REF(ConvertibleToAlloc) c2alloc)
         :  NodeAlloc(boost::forward<ConvertibleToAlloc>(c2alloc))
         , m_icont()
      {}


      explicit members_holder(const Pred &c)
         : NodeAlloc()
         , m_icont(typename ICont::value_compare(c))
      {}


   ICont &non_const_icont() const
   {  return const_cast<ICont&>(this->members_.m_icont);   }


   ICont &icont()
   {  return this->members_.m_icont;   }


   const ICont &icont() const
   {  return this->members_.m_icont;   }


   NodeAlloc &node_alloc()
   {  return static_cast<NodeAlloc &>(this->members_);   }

   LowPriorityConversion(const U&) { }

   hdr_offset_holder_t(size_type offset = 0)
      : hdr_offset(offset)
   {}

   static bool less(SizeType, SizeType, const void *, const void *)
   {  return true;   }

   static bool less(SizeType ls, SizeType rs, const void *, const void *)
   {  return ls < rs;   }

   static bool less(SizeType, SizeType, const void *la, const void *ra)
   {  return &la < &ra;   }

   static bool less(SizeType ls, SizeType rs, const void *la, const void *ra)
   {  return (ls < rs) || ((ls == rs) && (la < ra));  }


   template<class Container>
   static void reinsert_was_used(Container &container, typename Container::reference v, bool)
   {
      typedef typename Container::const_iterator const_block_iterator;
      const const_block_iterator this_block
         (Container::s_iterator_to(const_cast<typename Container::const_reference>(v)));
      const_block_iterator next_block(this_block);
      if(++next_block != container.cend()){
         if(this_block->free_nodes.size() > next_block->free_nodes.size()){
            container.erase(this_block);
            container.insert(v);
         }
      }
   }


   template<class Container>
   static void insert_was_empty(Container &container, typename Container::value_type &v, bool)
   {
      container.insert(v);
   }


   template<class Container>
   static void erase_first(Container &container)
   {
      container.erase(container.cbegin());
   }


   template<class Container>
   static void erase_last(Container &container)
   {
      container.erase(--container.cend());
   }


   template<class Container>
   static void reinsert_was_used(Container &container, typename Container::value_type &v, bool is_full)
   {
      if(is_full){
         container.erase(Container::s_iterator_to(v));
         container.push_back(v);
      }
   }


   template<class Container>
   static void insert_was_empty(Container &container, typename Container::value_type &v, bool is_full)
   {
      if(is_full){
         container.push_back(v);
      }
      else{
         container.push_front(v);
      }
   }


   template<class Container>
   static void erase_first(Container &container)
   {
      container.pop_front();
   }


   template<class Container>
   static void erase_last(Container &container)
   {
      container.pop_back();
   }


template<class size_type>
inline size_type calculate_alignment
   ( size_type overhead_percent, size_type real_node_size
   , size_type hdr_size, size_type hdr_offset_size, size_type payload_per_allocation)
{
   //to-do: handle real_node_size != node_size
   const size_type divisor  = overhead_percent*real_node_size;
   const size_type dividend = hdr_offset_size*100;
   size_type elements_per_subblock = (dividend - 1)/divisor + 1;
   size_type candidate_power_of_2 =
      upper_power_of_2(elements_per_subblock*real_node_size + hdr_offset_size);
   bool overhead_satisfied = false;
   //Now calculate the wors-case overhead for a subblock
   const size_type max_subblock_overhead  = hdr_size + payload_per_allocation;
   while(!overhead_satisfied){
      elements_per_subblock = (candidate_power_of_2 - max_subblock_overhead)/real_node_size;
      const size_type overhead_size = candidate_power_of_2 - elements_per_subblock*real_node_size;
      if(overhead_size*100/candidate_power_of_2 < overhead_percent){
         overhead_satisfied = true;
      }
      else{
         candidate_power_of_2 <<= 1;
      }
   }
   return candidate_power_of_2;
}


template<class size_type>
inline void calculate_num_subblocks
   (size_type alignment, size_type real_node_size, size_type elements_per_block
   , size_type &num_subblocks, size_type &real_num_node, size_type overhead_percent
   , size_type hdr_size, size_type hdr_offset_size, size_type payload_per_allocation)
{
   const size_type hdr_subblock_elements = (alignment - hdr_size - payload_per_allocation)/real_node_size;
   size_type elements_per_subblock = (alignment - hdr_offset_size)/real_node_size;
   size_type possible_num_subblock = (elements_per_block - 1)/elements_per_subblock + 1;
   while(((possible_num_subblock-1)*elements_per_subblock + hdr_subblock_elements) < elements_per_block){
      ++possible_num_subblock;
   }
   elements_per_subblock = (alignment - hdr_offset_size)/real_node_size;
   bool overhead_satisfied = false;
   while(!overhead_satisfied){
      const size_type total_data = (elements_per_subblock*(possible_num_subblock-1) + hdr_subblock_elements)*real_node_size;
      const size_type total_size = alignment*possible_num_subblock;
      if((total_size - total_data)*100/total_size < overhead_percent){
         overhead_satisfied = true;
      }
      else{
         ++possible_num_subblock;
      }
   }
   num_subblocks = possible_num_subblock;
   real_num_node = (possible_num_subblock-1)*elements_per_subblock + hdr_subblock_elements;
}

   private_adaptive_node_pool_impl
      ( segment_manager_base_type *segment_mngr_base
      , size_type node_size
      , size_type nodes_per_block
      , size_type max_free_blocks
      , unsigned char overhead_percent
      )
   :  m_max_free_blocks(max_free_blocks)
   ,  m_real_node_size(lcm(node_size, size_type(alignment_of<void_pointer>::value)))
      //Round the size to a power of two value.
      //This is the total memory size (including payload) that we want to
      //allocate from the general-purpose allocator
   ,  m_real_block_alignment
         (AlignOnly ?
            upper_power_of_2(HdrSize + m_real_node_size*nodes_per_block) :
            calculate_alignment( (size_type)overhead_percent, m_real_node_size
                               , HdrSize, HdrOffsetSize, PayloadPerAllocation))
      //This is the real number of nodes per block
   ,  m_num_subblocks(0)
   ,  m_real_num_node(AlignOnly ? (m_real_block_alignment - PayloadPerAllocation - HdrSize)/m_real_node_size : 0)
      //General purpose allocator
   ,  mp_segment_mngr_base(segment_mngr_base)
   ,  m_block_container()
   ,  m_totally_free_blocks(0)
   {
      if(!AlignOnly){
         calculate_num_subblocks
            ( m_real_block_alignment
            , m_real_node_size
            , nodes_per_block
            , m_num_subblocks
            , m_real_num_node
            , (size_type)overhead_percent
            , HdrSize
            , HdrOffsetSize
            , PayloadPerAllocation);
      }
   }

   ~private_adaptive_node_pool_impl()
   {  this->priv_clear();  }


   size_type get_real_num_node() const
   {  return m_real_num_node; }

   segment_manager_base_type* get_segment_manager_base()const
   {  return container_detail::to_raw_pointer(mp_segment_mngr_base);  }

   void *allocate_node()
   {
      this->priv_invariants();
      //If there are no free nodes we allocate a new block
      if(!m_block_container.empty()){
         //We take the first free node the multiset can't be empty
         free_nodes_t &free_nodes = m_block_container.begin()->free_nodes;
         BOOST_ASSERT(!free_nodes.empty());
         const size_type free_nodes_count = free_nodes.size();
         void *first_node = container_detail::to_raw_pointer(free_nodes.pop_front());
         if(free_nodes.empty()){
            block_container_traits_t::erase_first(m_block_container);
         }
         m_totally_free_blocks -= static_cast<size_type>(free_nodes_count == m_real_num_node);
         this->priv_invariants();
         return first_node;
      }
      else{
         multiallocation_chain chain;
         this->priv_append_from_new_blocks(1, chain, IsAlignOnly());
         return container_detail::to_raw_pointer(chain.pop_front());
      }
   }

   void deallocate_node(void *pElem)
   {
      this->priv_invariants();
      block_info_t &block_info = *this->priv_block_from_node(pElem);
      BOOST_ASSERT(block_info.free_nodes.size() < m_real_num_node);

      //We put the node at the beginning of the free node list
      block_info.free_nodes.push_back(void_pointer(pElem));

      //The loop reinserts all blocks except the last one
      this->priv_reinsert_block(block_info, block_info.free_nodes.size() == 1);
      this->priv_deallocate_free_blocks(m_max_free_blocks);
      this->priv_invariants();
   }

   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      size_type i = 0;
      BOOST_TRY{
         this->priv_invariants();
         while(i != n){
            //If there are no free nodes we allocate all needed blocks
            if (m_block_container.empty()){
               this->priv_append_from_new_blocks(n - i, chain, IsAlignOnly());
               BOOST_ASSERT(m_block_container.empty() || (++m_block_container.cbegin() == m_block_container.cend()));
               BOOST_ASSERT(chain.size() == n);
               break;
            }
            free_nodes_t &free_nodes = m_block_container.begin()->free_nodes;
            const size_type free_nodes_count_before = free_nodes.size();
            m_totally_free_blocks -= static_cast<size_type>(free_nodes_count_before == m_real_num_node);
            const size_type num_left  = n-i;
            const size_type num_elems = (num_left < free_nodes_count_before) ? num_left : free_nodes_count_before;
            typedef typename free_nodes_t::iterator free_nodes_iterator;

            if(num_left < free_nodes_count_before){
               const free_nodes_iterator it_bbeg(free_nodes.before_begin());
               free_nodes_iterator it_bend(it_bbeg);
               for(size_type j = 0; j != num_elems; ++j){
                  ++it_bend;
               }
               free_nodes_iterator it_end = it_bend; ++it_end;
               free_nodes_iterator it_beg = it_bbeg; ++it_beg;
               free_nodes.erase_after(it_bbeg, it_end, num_elems);
               chain.incorporate_after(chain.last(), &*it_beg, &*it_bend, num_elems);
               //chain.splice_after(chain.last(), free_nodes, it_bbeg, it_bend, num_elems);
               BOOST_ASSERT(!free_nodes.empty());
            }
            else{
               const free_nodes_iterator it_beg(free_nodes.begin()), it_bend(free_nodes.last());
               free_nodes.clear();
               chain.incorporate_after(chain.last(), &*it_beg, &*it_bend, num_elems);
               block_container_traits_t::erase_first(m_block_container);
            }
            i += num_elems;
         }
      }
      BOOST_CATCH(...){
         this->deallocate_nodes(chain);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
      this->priv_invariants();
   }

   void deallocate_nodes(multiallocation_chain &nodes)
   {
      this->priv_invariants();
      //To take advantage of node locality, wait until two
      //nodes belong to different blocks. Only then reinsert
      //the block of the first node in the block tree.
      //Cache of the previous block
      block_info_t *prev_block_info = 0;

      //If block was empty before this call, it's not already
      //inserted in the block tree.
      bool prev_block_was_empty     = false;
      typedef typename free_nodes_t::iterator free_nodes_iterator;
      {
         const free_nodes_iterator itbb(nodes.before_begin()), ite(nodes.end());
         free_nodes_iterator itf(nodes.begin()), itbf(itbb);
         size_type splice_node_count = size_type(-1);
         while(itf != ite){
            void *pElem = container_detail::to_raw_pointer(&*itf);
            block_info_t &block_info = *this->priv_block_from_node(pElem);
            BOOST_ASSERT(block_info.free_nodes.size() < m_real_num_node);
            ++splice_node_count;

            //If block change is detected calculate the cached block position in the tree
            if(&block_info != prev_block_info){
               if(prev_block_info){ //Make sure we skip the initial "dummy" cache
                  free_nodes_iterator it(itbb); ++it;
                  nodes.erase_after(itbb, itf, splice_node_count);
                  prev_block_info->free_nodes.incorporate_after(prev_block_info->free_nodes.last(), &*it, &*itbf, splice_node_count);
                  this->priv_reinsert_block(*prev_block_info, prev_block_was_empty);
                  splice_node_count = 0;
               }
               //Update cache with new data
               prev_block_was_empty = block_info.free_nodes.empty();
               prev_block_info = &block_info;
            }
            itbf = itf;
            ++itf;
         }
      }
      if(prev_block_info){
         //The loop reinserts all blocks except the last one
         const free_nodes_iterator itfirst(nodes.begin()), itlast(nodes.last());
         const size_type splice_node_count = nodes.size();
         nodes.clear();
         prev_block_info->free_nodes.incorporate_after(prev_block_info->free_nodes.last(), &*itfirst, &*itlast, splice_node_count);
         this->priv_reinsert_block(*prev_block_info, prev_block_was_empty);
         this->priv_invariants();
         this->priv_deallocate_free_blocks(m_max_free_blocks);
      }
   }


   void deallocate_free_blocks()
   {  this->priv_deallocate_free_blocks(0);  }


   size_type num_free_nodes()
   {
      typedef typename block_container_t::const_iterator citerator;
      size_type count = 0;
      citerator it (m_block_container.begin()), itend(m_block_container.end());
      for(; it != itend; ++it){
         count += it->free_nodes.size();
      }
      return count;
   }


   void swap(private_adaptive_node_pool_impl &other)
   {
      BOOST_ASSERT(m_max_free_blocks == other.m_max_free_blocks);
      BOOST_ASSERT(m_real_node_size == other.m_real_node_size);
      BOOST_ASSERT(m_real_block_alignment == other.m_real_block_alignment);
      BOOST_ASSERT(m_real_num_node == other.m_real_num_node);
      std::swap(mp_segment_mngr_base, other.mp_segment_mngr_base);
      std::swap(m_totally_free_blocks, other.m_totally_free_blocks);
      m_block_container.swap(other.m_block_container);
   }

   void deallocate_free_chunks()
   {  this->priv_deallocate_free_blocks(0);   }


   void priv_deallocate_free_blocks(size_type max_free_blocks)
   {  //Trampoline function to ease inlining
      if(m_totally_free_blocks > max_free_blocks){
         this->priv_deallocate_free_blocks_impl(max_free_blocks);
      }
   }


   void priv_deallocate_free_blocks_impl(size_type max_free_blocks)
   {
      this->priv_invariants();
      //Now check if we've reached the free nodes limit
      //and check if we have free blocks. If so, deallocate as much
      //as we can to stay below the limit
      multiallocation_chain chain;
      {
         const const_block_iterator itend = m_block_container.cend();
         const_block_iterator it = itend;
         --it;
         size_type totally_free_blocks = m_totally_free_blocks;

         for( ; totally_free_blocks > max_free_blocks; --totally_free_blocks){
            BOOST_ASSERT(it->free_nodes.size() == m_real_num_node);
            void *addr = priv_first_subblock_from_block(const_cast<block_info_t*>(&*it));
            --it;
            block_container_traits_t::erase_last(m_block_container);
            chain.push_front(void_pointer(addr));
         }
         BOOST_ASSERT((m_totally_free_blocks - max_free_blocks) == chain.size());
         m_totally_free_blocks = max_free_blocks;
      }
      this->mp_segment_mngr_base->deallocate_many(chain);
   }


   void priv_reinsert_block(block_info_t &prev_block_info, const bool prev_block_was_empty)
   {
      //Cache the free nodes from the block
      const size_type this_block_free_nodes = prev_block_info.free_nodes.size();
      const bool is_full = this_block_free_nodes == m_real_num_node;

      //Update free block count
      m_totally_free_blocks += static_cast<size_type>(is_full);
      if(prev_block_was_empty){
         block_container_traits_t::insert_was_empty(m_block_container, prev_block_info, is_full);
      }
      else{
         block_container_traits_t::reinsert_was_used(m_block_container, prev_block_info, is_full);
      }
   }

      block_destroyer(const this_type *impl, multiallocation_chain &chain)
         :  mp_impl(impl), m_chain(chain)
      {}


      void operator()(typename block_container_t::pointer to_deallocate)
      {  return this->do_destroy(to_deallocate, IsAlignOnly()); }

      void do_destroy(typename block_container_t::pointer to_deallocate, AlignOnlyTrue)
      {
         BOOST_ASSERT(to_deallocate->free_nodes.size() == mp_impl->m_real_num_node);
         m_chain.push_back(to_deallocate);
      }

   void priv_invariants()
   #ifdef BOOST_CONTAINER_ADAPTIVE_NODE_POOL_CHECK_INVARIANTS
   #undef BOOST_CONTAINER_ADAPTIVE_NODE_POOL_CHECK_INVARIANTS
   {
      const const_block_iterator itend(m_block_container.end());

      {  //We iterate through the block tree to free the memory
         const_block_iterator it(m_block_container.begin());
   
         if(it != itend){
            for(++it; it != itend; ++it){
               const_block_iterator prev(it);
               --prev;
               BOOST_ASSERT(*prev < *it);
               (void)prev;   (void)it;
            }
         }
      }
      {  //Check that the total free nodes are correct
         const_block_iterator it(m_block_container.cbegin());
         size_type total_free_nodes = 0;
         for(; it != itend; ++it){
            total_free_nodes += it->free_nodes.size();
         }
         BOOST_ASSERT(total_free_nodes >= m_totally_free_blocks*m_real_num_node);
      }
      {  //Check that the total totally free blocks are correct
         BOOST_ASSERT(m_block_container.size() >= m_totally_free_blocks);
         const_block_iterator it = m_block_container.cend();
         size_type total_free_blocks = m_totally_free_blocks;
         while(total_free_blocks--){
            BOOST_ASSERT((--it)->free_nodes.size() == m_real_num_node);
         }
      }

      if(!AlignOnly){
         //Check that header offsets are correct
         const_block_iterator it = m_block_container.begin();
         for(; it != itend; ++it){
            hdr_offset_holder *hdr_off_holder = this->priv_first_subblock_from_block(const_cast<block_info_t *>(&*it));
            for(size_type i = 0, max = m_num_subblocks; i < max; ++i){
               const size_type offset = reinterpret_cast<char*>(const_cast<block_info_t *>(&*it)) - reinterpret_cast<char*>(hdr_off_holder);
               BOOST_ASSERT(hdr_off_holder->hdr_offset == offset);
               BOOST_ASSERT(0 == ((size_type)hdr_off_holder & (m_real_block_alignment - 1)));
               BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (m_real_block_alignment - 1)));
               hdr_off_holder = reinterpret_cast<hdr_offset_holder *>(reinterpret_cast<char*>(hdr_off_holder) + m_real_block_alignment);
            }
         }
      }
   }
   #else
   {}

   void priv_clear()
   {
      #ifndef NDEBUG
      block_iterator it    = m_block_container.begin();
      block_iterator itend = m_block_container.end();
      size_type n_free_nodes = 0;
      for(; it != itend; ++it){
         //Check for memory leak
         BOOST_ASSERT(it->free_nodes.size() == m_real_num_node);
         ++n_free_nodes;
      }
      BOOST_ASSERT(n_free_nodes == m_totally_free_blocks);
      #endif
      //Check for memory leaks
      this->priv_invariants();
      multiallocation_chain chain;
      m_block_container.clear_and_dispose(block_destroyer(this, chain));
      this->mp_segment_mngr_base->deallocate_many(chain);
      m_totally_free_blocks = 0;
   }


   block_info_t *priv_block_from_node(void *node, AlignOnlyFalse) const
   {
      hdr_offset_holder *hdr_off_holder =
         reinterpret_cast<hdr_offset_holder*>((std::size_t)node & size_type(~(m_real_block_alignment - 1)));
      BOOST_ASSERT(0 == ((std::size_t)hdr_off_holder & (m_real_block_alignment - 1)));
      BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (m_real_block_alignment - 1)));
      block_info_t *block = reinterpret_cast<block_info_t *>
         (reinterpret_cast<char*>(hdr_off_holder) + hdr_off_holder->hdr_offset);
      BOOST_ASSERT(block->hdr_offset == 0);
      return block;
   }


   block_info_t *priv_block_from_node(void *node) const
   {  return this->priv_block_from_node(node, IsAlignOnly());   }


   hdr_offset_holder *priv_first_subblock_from_block(block_info_t *block) const
   {  return this->priv_first_subblock_from_block(block, IsAlignOnly());   }


   hdr_offset_holder *priv_first_subblock_from_block(block_info_t *block, AlignOnlyFalse) const
   {
      hdr_offset_holder *const hdr_off_holder = reinterpret_cast<hdr_offset_holder*>
            (reinterpret_cast<char*>(block) - (m_num_subblocks-1)*m_real_block_alignment);
      BOOST_ASSERT(hdr_off_holder->hdr_offset == size_type(reinterpret_cast<char*>(block) - reinterpret_cast<char*>(hdr_off_holder)));
      BOOST_ASSERT(0 == ((std::size_t)hdr_off_holder & (m_real_block_alignment - 1)));
      BOOST_ASSERT(0 == (hdr_off_holder->hdr_offset & (m_real_block_alignment - 1)));
      return hdr_off_holder;
   }


   void priv_dispatch_block_chain_or_free
      ( multiallocation_chain &chain, block_info_t &c_info, size_type num_node
      , char *mem_address, size_type total_elements, bool insert_block_if_free)
   {
      BOOST_ASSERT(chain.size() <= total_elements);
      //First add all possible nodes to the chain
      const size_type left = total_elements - chain.size();
      const size_type max_chain = (num_node < left) ? num_node : left;
      mem_address = static_cast<char *>(container_detail::to_raw_pointer
         (chain.incorporate_after(chain.last(), void_pointer(mem_address), m_real_node_size, max_chain)));
      //Now store remaining nodes in the free list
      if(const size_type max_free = num_node - max_chain){
         free_nodes_t & free_nodes = c_info.free_nodes;
         free_nodes.incorporate_after(free_nodes.last(), void_pointer(mem_address), m_real_node_size, max_free);
         if(insert_block_if_free){
            m_block_container.push_front(c_info);
         }
      }
   }

   void priv_append_from_new_blocks(size_type min_elements, multiallocation_chain &chain, AlignOnlyTrue)
   {
      BOOST_ASSERT(m_block_container.empty());
      BOOST_ASSERT(min_elements > 0);
      const size_type n = (min_elements - 1)/m_real_num_node + 1;
      const size_type real_block_size = m_real_block_alignment - PayloadPerAllocation;
      const size_type total_elements = chain.size() + min_elements;
      for(size_type i = 0; i != n; ++i){
         //We allocate a new NodeBlock and put it the last
         //element of the tree
         char *mem_address = static_cast<char*>
            (mp_segment_mngr_base->allocate_aligned(real_block_size, m_real_block_alignment));
         if(!mem_address){
            //In case of error, free memory deallocating all nodes (the new ones allocated
            //in this function plus previously stored nodes in chain).
            this->deallocate_nodes(chain);
            throw_bad_alloc();
         }
         block_info_t &c_info = *new(mem_address)block_info_t();
         mem_address += HdrSize;
         if(i != (n-1)){
            chain.incorporate_after(chain.last(), void_pointer(mem_address), m_real_node_size, m_real_num_node);
         }
         else{
            this->priv_dispatch_block_chain_or_free(chain, c_info, m_real_num_node, mem_address, total_elements, true);
         }
      }
   }
    
   flat_tree_value_compare()
      : Compare()
   {}


   flat_tree_value_compare(const Compare &pred)
      : Compare(pred)
   {}


   bool operator()(const Value& lhs, const Value& rhs) const
   {
      KeyOfValue key_extract;
      return Compare::operator()(key_extract(lhs), key_extract(rhs));
   }


   const Compare &get_comp() const
      {  return *this;  }

  
   Compare &get_comp()
      {  return *this;  }

   flat_tree()
      : m_data()
   { }


   explicit flat_tree(const Compare& comp)
      : m_data(comp)
   { }


   flat_tree(const Compare& comp, const allocator_type& a)
      : m_data(comp, a)
   { }


   flat_tree(const flat_tree& x)
      :  m_data(x.m_data)
   { }


   flat_tree(BOOST_RV_REF(flat_tree) x)
      :  m_data(boost::move(x.m_data))
   { }


   flat_tree(const flat_tree& x, const allocator_type &a)
      :  m_data(x.m_data, a)
   { }


   template <class InputIterator>
   flat_tree( bool unique_insertion
            , InputIterator first, InputIterator last
            , const Compare& comp     = Compare()
            , const allocator_type& a = allocator_type())
      : m_data(comp, a)
   {
      if(unique_insertion){
         this->insert_unique(first, last);
      }
      else{
         this->insert_equal(first, last);
      }
   }


   ~flat_tree()
   { }


   flat_tree&  operator=(BOOST_COPY_ASSIGN_REF(flat_tree) x)
   {  m_data = x.m_data;   return *this;  }

   Compare key_comp() const
   { return this->m_data.get_comp(); }


   allocator_type get_allocator() const
   { return this->m_data.m_vect.get_allocator(); }


   const stored_allocator_type &get_stored_allocator() const
   {  return this->m_data.m_vect.get_stored_allocator(); }


   stored_allocator_type &get_stored_allocator()
   {  return this->m_data.m_vect.get_stored_allocator(); }


   iterator begin()
   { return this->m_data.m_vect.begin(); }


   const_iterator begin() const
   { return this->cbegin(); }


   const_iterator cbegin() const
   { return this->m_data.m_vect.begin(); }


   iterator end()
   { return this->m_data.m_vect.end(); }


   const_iterator end() const
   { return this->cend(); }


   const_iterator cend() const
   { return this->m_data.m_vect.end(); }


   reverse_iterator rbegin()
   { return reverse_iterator(this->end()); }


   const_reverse_iterator rbegin() const
   {  return this->crbegin();  }


   const_reverse_iterator crbegin() const
   {  return const_reverse_iterator(this->cend());  }


   reverse_iterator rend()
   { return reverse_iterator(this->begin()); }


   const_reverse_iterator rend() const
   { return this->crend(); }


   const_reverse_iterator crend() const
   { return const_reverse_iterator(this->cbegin()); }


   bool empty() const
   { return this->m_data.m_vect.empty(); }


   size_type size() const
   { return this->m_data.m_vect.size(); }


   size_type max_size() const
   { return this->m_data.m_vect.max_size(); }


   void swap(flat_tree& other)
   {  this->m_data.swap(other.m_data);  }

   void priv_insert_equal_prepare
      (const_iterator pos, const value_type& val, insert_commit_data &data)
   {
      // N1780
      //   To insert val at pos:
      //   if pos == end || val <= *pos
      //      if pos == begin || val >= *(pos-1)
      //         insert val before pos
      //      else
      //         insert val before upper_bound(val)
      //   else
      //      insert val before lower_bound(val)
      const value_compare &value_comp = this->m_data;

      if(pos == this->cend() || !value_comp(*pos, val)){
         if (pos == this->cbegin() || !value_comp(val, pos[-1])){
            data.position = pos;
         }
         else{
            data.position =
               this->priv_upper_bound(this->cbegin(), pos, KeyOfValue()(val));
         }
      }
      else{
         data.position =
            this->priv_lower_bound(pos, this->cend(), KeyOfValue()(val));
      }
   }


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator==(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
           const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
{
  return x.size() == y.size() &&
         std::equal(x.begin(), x.end(), y.begin());
}


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator<(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
          const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
{
  return std::lexicographical_compare(x.begin(), x.end(),
                                      y.begin(), y.end());
}


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator!=(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
           const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
   {  return !(x == y); }


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator>(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
          const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
   {  return y < x;  }


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator<=(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
           const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
   {  return !(y < x);  }


template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline bool
operator>=(const flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
           const flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
   {  return !(x < y);  }



template <class Key, class Value, class KeyOfValue,
          class Compare, class A>
inline void
swap(flat_tree<Key,Value,KeyOfValue,Compare,A>& x,
     flat_tree<Key,Value,KeyOfValue,Compare,A>& y)
   {  x.swap(y);  }

   tuple() { }

   template<typename... VValues>
   tuple(const tuple<VValues...>& other)
      : m_head(other.head()), inherited(other.tail())
   {}


   template<typename... VValues>
   tuple& operator=(const tuple<VValues...>& other)
   {
      m_head = other.head();
      tail() = other.tail();
      return this;
   }



template<typename... Values>
tuple<Values&&...> tie_forward(Values&&... values)
{ return tuple<Values&&...>(values...); }

   static type get(tuple<Head, Values...>& t)              { return Next::get(t.tail()); }

   static type       get(tuple<Head, Values...>& t)      { return t.head(); }


template<int I, typename... Values>
typename get_impl<I, tuple<Values...> >::type get(tuple<Values...>& t)
{  return get_impl<I, tuple<Values...> >::get(t);  }


template<int I, typename... Values>
typename get_impl<I, tuple<Values...> >::const_type get(const tuple<Values...>& t)
{  return get_impl<I, tuple<Values...> >::get(t);  }

template <typename Integer>
inline Integer gcd(Integer A, Integer B)
{
   do
   {
      const Integer tmp(B);
      B = A % B;
      A = tmp;
   } while (B != 0);

   return A;
}

template <typename Integer>
inline Integer lcm(const Integer & A, const Integer & B)
{
   Integer ret = A;
   ret /= gcd(A, B);
   ret *= B;
   return ret;
}


template <typename Integer>
inline Integer log2_ceil(const Integer & A)
{
   Integer i = 0;
   Integer power_of_2 = 1;

   while(power_of_2 < A){
      power_of_2 <<= 1;
      ++i;
   }
   return i;
}


template <typename Integer>
inline Integer upper_power_of_2(const Integer & A)
{
   Integer power_of_2 = 1;

   while(power_of_2 < A){
      power_of_2 <<= 1;
   }
   return power_of_2;
}

inline std::size_t floor_log2 (std::size_t x)
{
   const std::size_t Bits = sizeof(std::size_t)*CHAR_BIT;
   const bool Size_t_Bits_Power_2= !(Bits & (Bits-1));
   BOOST_STATIC_ASSERT(((Size_t_Bits_Power_2)== true));

   std::size_t n = x;
   std::size_t log2 = 0;
  
   for(std::size_t shift = Bits >> 1; shift; shift >>= 1){
      std::size_t tmp = n >> shift;
      if (tmp)
         log2 += shift, n = tmp;
   }

   return log2;
}

   value_init()
      : m_t()
   {}


   operator T &() { return m_t; }

   void priv_deallocate(allocator_v1)
   {  m_alloc.deallocate(m_ptr, 1); }


   scoped_deallocator(pointer p, A& a)
      : m_ptr(p), m_alloc(a)
   {}


   ~scoped_deallocator()
   {  if (m_ptr)priv_deallocate(alloc_version());  }


   scoped_deallocator(BOOST_RV_REF(scoped_deallocator) o)
      :  m_ptr(o.m_ptr), m_alloc(o.m_alloc)
   {  o.release();  }


   pointer get() const
   {  return m_ptr;  }


   void release()
   {  m_ptr = 0; }


   null_scoped_deallocator(pointer, Allocator&, size_type)
   {}


   void release()
   {}


   pointer get() const
   {  return pointer();  }


   scoped_array_deallocator(pointer p, Allocator& a, size_type length)
      : m_ptr(p), m_alloc(a), m_length(length) {}


   ~scoped_array_deallocator()
   {  if (m_ptr) m_alloc.deallocate(m_ptr, m_length);  }


   void release()
   {  m_ptr = 0; }


   null_scoped_array_deallocator(pointer, Allocator&, size_type)
   {}


   void release()
   {}


   scoped_destroy_deallocator(pointer p, Allocator& a)
      : m_ptr(p), m_alloc(a) {}


   ~scoped_destroy_deallocator()
   {
      if(m_ptr){
         AllocTraits::destroy(m_alloc, container_detail::to_raw_pointer(m_ptr));
         priv_deallocate(m_ptr, alloc_version());
      }
   }


   void release()
   {  m_ptr = 0; }


   void priv_deallocate(const pointer &p, allocator_v1)
   {  AllocTraits::deallocate(m_alloc, p, 1); }


   scoped_destructor_n(pointer p, Allocator& a, size_type n)
      : m_p(p), m_a(a), m_n(n)
   {}


   void release()
   {  m_p = 0; }


   void increment_size(size_type inc)
   {  m_n += inc;   }


   void increment_size_backwards(size_type inc)
   {  m_n += inc;   m_p -= inc;  }


   void shrink_forward(size_type inc)
   {  m_n -= inc;   m_p += inc;  }

  
   ~scoped_destructor_n()
   {
      if(!m_p) return;
      value_type *raw_ptr = container_detail::to_raw_pointer(m_p);
      while(m_n--){
         AllocTraits::destroy(m_a, raw_ptr);
      }
   }


   null_scoped_destructor_n(pointer, Allocator&, size_type)
   {}


   void increment_size(size_type)
   {}


   void increment_size_backwards(size_type)
   {}


   void release()
   {}

   scoped_destructor(A &a, value_type *pv)
      : pv_(pv), a_(a)
   {}


   ~scoped_destructor()
   {
      if(pv_){
         AllocTraits::destroy(a_, pv_);
      }
   }


   void release()
   {  pv_ = 0; }

   value_destructor(A &a, value_type &rv)
      : rv_(rv), a_(a)
   {}


   ~value_destructor()
   {
      AllocTraits::destroy(a_, &rv_);
   }

   void priv_deallocate(const pointer &p, allocator_v1)
   {  AllocTraits::deallocate(a_,p, 1); }

   allocator_destroyer(Allocator &a)
      : a_(a)
   {}


   void operator()(const pointer &p)
   {
      AllocTraits::destroy(a_, container_detail::to_raw_pointer(p));
      this->priv_deallocate(p, alloc_version());
   }

   allocator_destroyer_and_chain_builder(A &a, multiallocation_chain &c)
      :  a_(a), c_(c)
   {}


   void operator()(const typename A::pointer &p)
   {
      allocator_traits<A>::destroy(a_, container_detail::to_raw_pointer(p));
      c_.push_back(p);
   }

   allocator_multialloc_chain_node_deallocator(A &a)
      :  a_(a), c_()
   {}


   chain_builder get_chain_builder()
   {  return chain_builder(a_, c_);  }


   ~allocator_multialloc_chain_node_deallocator()
   {
      a_.deallocate_individual(c_);
   }

   pair()
      : first(), second()
   {}

   pair(const pair& x)
      : first(x.first), second(x.second)
   {}

   pair(BOOST_RV_REF(pair) p)
      : first(::boost::move(p.first)), second(::boost::move(p.second))
   {}


   template <class D, class S>
   pair(const pair<D, S> &p)
      : first(p.first), second(p.second)
   {}

   pair(const T1 &t1, const T2 &t2)
      : first(t1)
      , second(t2)
   {}


   template<class U, class V>
   pair(BOOST_FWD_REF(U) u, BOOST_FWD_REF(V) v)
      : first(::boost::forward<U>(u))
      , second(::boost::forward<V>(v))
   {}

   pair& operator=(BOOST_COPY_ASSIGN_REF(pair) p)
   {
      first  = p.first;
      second = p.second;
      return *this;
   }


template <class T1, class T2>
inline bool operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(x.first == y.first && x.second == y.second);  }


template <class T1, class T2>
inline bool operator< (const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(x.first < y.first ||
                         (!(y.first < x.first) && x.second < y.second)); }


template <class T1, class T2>
inline bool operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(x == y));  }


template <class T1, class T2>
inline bool operator> (const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return y < x;  }


template <class T1, class T2>
inline bool operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(x < y)); }


template <class T1, class T2>
inline bool operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{  return static_cast<bool>(!(y < x)); }


template <class T1, class T2>
inline pair<T1, T2> make_pair(T1 x, T2 y)
{  return pair<T1, T2>(x, y); }


template <class T1, class T2>
inline void swap(pair<T1, T2>& x, pair<T1, T2>& y)
{
   swap(x.first, y.first);
   swap(x.second, y.second);
}

   operator bool() const { return bool_::value; }

   template<class OtherPair>
   const typename Pair::first_type& operator()(const OtherPair& x) const
   {  return x.first;   }


   const typename Pair::first_type& operator()(const typename Pair::first_type& x) const
   {  return x;   }

   const T& operator()(const T& x) const
   { return x; }


   static node & to_node(const VoidPointer &p)
   {  return *static_cast<node*>(static_cast<void*>(container_detail::to_raw_pointer(p)));  }


   static VoidPointer from_node(node &n)
   {  return node_ptr_traits::pointer_to(n);  }


   static node_ptr to_node_ptr(const VoidPointer &p)
   {  return node_ptr_traits::static_cast_from(p);   }


   basic_multiallocation_chain()
      :  slist_impl_()
   {}


   basic_multiallocation_chain(BOOST_RV_REF(basic_multiallocation_chain) other)
      :  slist_impl_(::boost::move(other.slist_impl_))
   {}


   basic_multiallocation_chain& operator=(BOOST_RV_REF(basic_multiallocation_chain) other)
   {
      slist_impl_ = ::boost::move(other.slist_impl_);
      return *this;
   }


   bool empty() const
   {  return slist_impl_.empty(); }


   size_type size() const
   {  return slist_impl_.size();  }


   iterator before_begin()
   {  return slist_impl_.before_begin(); }


   iterator begin()
   {  return slist_impl_.begin(); }


   iterator end()
   {  return slist_impl_.end(); }


   iterator last()
   {  return slist_impl_.last(); }


   void clear()
   {  slist_impl_.clear(); }


   iterator insert_after(iterator it, void_pointer m)
   {  return slist_impl_.insert_after(it, to_node(m));   }


   void push_front(const void_pointer &m)
   {  return slist_impl_.push_front(to_node(m));  }


   void push_back(const void_pointer &m)
   {  return slist_impl_.push_back(to_node(m));   }


   void_pointer pop_front()
   {
      node & n = slist_impl_.front();
      void_pointer ret = from_node(n);
      slist_impl_.pop_front();
      return ret;
   }


   void splice_after(iterator after_this, basic_multiallocation_chain &x, iterator before_b, iterator before_e, size_type n)
   {  slist_impl_.splice_after(after_this, x.slist_impl_, before_b, before_e, n);   }


   void splice_after(iterator after_this, basic_multiallocation_chain &x)
   {  slist_impl_.splice_after(after_this, x.slist_impl_);   }


   void erase_after(iterator before_b, iterator e, size_type n)
   {  slist_impl_.erase_after(before_b, e, n);   }


   void_pointer incorporate_after(iterator after_this, const void_pointer &b, size_type unit_bytes, size_type num_units)
   {
      typedef typename boost::intrusive::pointer_traits<char_ptr> char_pointer_traits;
      char_ptr elem = char_pointer_traits::static_cast_from(b);
      if(num_units){
         char_ptr prev_elem = elem;
         elem += unit_bytes;
         for(size_type i = 0; i != num_units-1; ++i, elem += unit_bytes){
            ::new (container_detail::to_raw_pointer(prev_elem)) void_pointer(elem);
            prev_elem = elem;
         }
         slist_impl_.incorporate_after(after_this, to_node_ptr(b), to_node_ptr(prev_elem), num_units);
      }
      return elem;
   }


   void swap(basic_multiallocation_chain &x)
   {  slist_impl_.swap(x.slist_impl_);   }


   static iterator iterator_to(const void_pointer &p)
   {  return slist_impl_t::s_iterator_to(to_node(p));   }

   template<class U>
   result_type operator()(U &ptr) const
   {  return *static_cast<T*>(static_cast<void*>(&ptr));  }


   static pointer cast(const void_pointer &p)
   {  return pointer_traits::static_cast_from(p);  }


   transform_multiallocation_chain()
      : MultiallocationChain()
   {}


   transform_multiallocation_chain(BOOST_RV_REF(transform_multiallocation_chain) other)
      : MultiallocationChain(::boost::move(static_cast<MultiallocationChain&>(other)))
   {}


   transform_multiallocation_chain(BOOST_RV_REF(MultiallocationChain) other)
      : MultiallocationChain(::boost::move(static_cast<MultiallocationChain&>(other)))
   {}


   transform_multiallocation_chain& operator=(BOOST_RV_REF(transform_multiallocation_chain) other)
   {
      return static_cast<MultiallocationChain&>
         (this->MultiallocationChain::operator=(::boost::move(static_cast<MultiallocationChain&>(other))));
   }

   pointer pop_front()
   {  return cast(this->MultiallocationChain::pop_front());  }

   iterator insert_after(iterator it, pointer m)
   {  return iterator(this->MultiallocationChain::insert_after(it.base(), m)); }


   static iterator iterator_to(const pointer &p)
   {  return iterator(MultiallocationChain::iterator_to(p));  }

template
   <typename A,
    typename I, // I models InputIterator
    typename F> // F models ForwardIterator
inline typename container_detail::disable_if_memcpy_copy_constructible<I, F, F>::type
   uninitialized_move_alloc(A &a, I f, I l, F r)
{
   F back = r;
   BOOST_TRY{
      while (f != l) {
         allocator_traits<A>::construct(a, container_detail::to_raw_pointer(&*r), boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
	   for (; back != r; ++back){
         allocator_traits<A>::destroy(a, container_detail::to_raw_pointer(&*back));
      }
	   BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}


   tree_value_compare(const key_compare &kcomp)
      :  key_compare(kcomp)
   {}


   const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }


   key_compare &key_comp()
   {  return static_cast<key_compare &>(*this);  }


   T &get_data()
   {
      T* ptr = reinterpret_cast<T*>(&this->m_data);
      return *ptr;
   }


   const T &get_data() const
   {
      const T* ptr = reinterpret_cast<const T*>(&this->m_data);
      return *ptr;
   }


   template<class A, class B>
   void do_assign(const std::pair<const A, B> &p)
   {
      const_cast<A&>(m_data.first) = p.first;
      m_data.second  = p.second;
   }


   template<class V>
   void do_assign(const V &v)
   {  m_data = v; }


   template<class A, class B>
   void do_move_assign(std::pair<const A, B> &p)
   {
      const_cast<A&>(m_data.first) = ::boost::move(p.first);
      m_data.second = ::boost::move(p.second);
   }


   template<class V>
   void do_move_assign(V &v)
   {  m_data = ::boost::move(v); }

      RecyclingCloner(AllocHolder &holder, Icont &irbtree)
         :  m_holder(holder), m_icont(irbtree)
      {}


      NodePtr operator()(const Node &other) const
      {
         if(NodePtr p = m_icont.unlink_leftmost_without_rebalance()){
            //First recycle a node (this can't throw)
            BOOST_TRY{
               //This can throw
               p->do_assign(other.m_data);
               return p;
            }
            BOOST_CATCH(...){
               //If there is an exception destroy the whole source
               m_holder.destroy_node(p);
               while((p = m_icont.unlink_leftmost_without_rebalance())){
                  m_holder.destroy_node(p);
               }
               BOOST_RETHROW
            }
            BOOST_CATCH_END
         }
         else{
            return m_holder.create_node(other.m_data);
         }
      }

      RecyclingMoveCloner(AllocHolder &holder, Icont &irbtree)
         :  m_holder(holder), m_icont(irbtree)
      {}


      NodePtr operator()(const Node &other) const
      {
         if(NodePtr p = m_icont.unlink_leftmost_without_rebalance()){
            //First recycle a node (this can't throw)
            BOOST_TRY{
               //This can throw
               p->do_move_assign(const_cast<Node &>(other).m_data);
               return p;
            }
            BOOST_CATCH(...){
               //If there is an exception destroy the whole source
               m_holder.destroy_node(p);
               while((p = m_icont.unlink_leftmost_without_rebalance())){
                  m_holder.destroy_node(p);
               }
               BOOST_RETHROW
            }
            BOOST_CATCH_END
         }
         else{
            return m_holder.create_node(other.m_data);
         }
      }

      key_node_compare(const KeyValueCompare &comp)
         :  KeyValueCompare(comp)
      {}

      explicit const_iterator(iiterator it)  : m_it(it){}

      void prot_incr() { ++m_it; }

      void prot_decr() { --m_it; }

      iiterator get()
      {  return this->m_it;   }

      const_iterator()
         :  m_it()
      {}

      const_reference operator*()  const
      { return  m_it->get_data();  }


      const_pointer   operator->() const
      { return  const_pointer(&m_it->get_data()); }

      const_iterator& operator++()      
      { prot_incr();  return *this; }


      const_iterator operator++(int)     
      { iiterator tmp = m_it; ++*this; return const_iterator(tmp);  }


      const_iterator& operator--()
      {   prot_decr(); return *this;   }


      const_iterator operator--(int)
      {  iiterator tmp = m_it; --*this; return const_iterator(tmp); }

      bool operator==   (const const_iterator& r)  const
      {  return m_it == r.m_it;  }


      bool operator!=   (const const_iterator& r)  const
      {  return m_it != r.m_it;  }

      explicit iterator(iiterator it)
         :  const_iterator(it)
      {}

  
      iiterator get()
      {  return this->m_it;   }

      iterator(){}

      reference operator*()  const
         {  return this->m_it->get_data();  }

      pointer   operator->() const
         {  return boost::intrusive::pointer_traits<pointer>::pointer_to(this->m_it->get_data());  }

      iterator& operator++() 
         { this->prot_incr(); return *this;  }


      iterator operator++(int)
         { iiterator tmp = this->m_it; ++*this; return iterator(tmp); }

     
      iterator& operator--()
         {  this->prot_decr(); return *this;  }


      iterator operator--(int)
         {  iterator tmp = *this; --*this; return tmp; }


   rbtree()
      : AllocHolder(key_compare())
   {}


   rbtree(const key_compare& comp, const allocator_type& a = allocator_type())
      : AllocHolder(a, comp)
   {}


   rbtree(const rbtree& x)
      :  AllocHolder(x, x.key_comp())
   {
      this->icont().clone_from
         (x.icont(), typename AllocHolder::cloner(*this), Destroyer(this->node_alloc()));
   }


   rbtree(BOOST_RV_REF(rbtree) x)
      :  AllocHolder(::boost::move(static_cast<AllocHolder&>(x)), x.key_comp())
   {}


   rbtree(const rbtree& x, const allocator_type &a)
      :  AllocHolder(a, x.key_comp())
   {
      this->icont().clone_from
         (x.icont(), typename AllocHolder::cloner(*this), Destroyer(this->node_alloc()));
   }


   ~rbtree()
   {}


   rbtree& operator=(BOOST_COPY_ASSIGN_REF(rbtree) x)
   {
      if (&x != this){
         NodeAlloc &this_alloc     = this->get_stored_allocator();
         const NodeAlloc &x_alloc  = x.get_stored_allocator();
         container_detail::bool_<allocator_traits<NodeAlloc>::
            propagate_on_container_copy_assignment::value> flag;
         if(flag && this_alloc != x_alloc){
            this->clear();
         }
         this->AllocHolder::copy_assign_alloc(x);
         //Transfer all the nodes to a temporary tree
         //If anything goes wrong, all the nodes will be destroyed
         //automatically
         Icont other_tree(::boost::move(this->icont()));

         //Now recreate the source tree reusing nodes stored by other_tree
         this->icont().clone_from
            (x.icont()
            , RecyclingCloner(*this, other_tree)
            , Destroyer(this->node_alloc()));

         //If there are remaining nodes, destroy them
         NodePtr p;
         while((p = other_tree.unlink_leftmost_without_rebalance())){
            AllocHolder::destroy_node(p);
         }
      }
      return *this;
   }

   value_compare value_comp() const
   {  return this->icont().value_comp().value_comp(); }


   key_compare key_comp() const
   {  return this->icont().value_comp().value_comp().key_comp(); }


   allocator_type get_allocator() const
   {  return allocator_type(this->node_alloc()); }


   const stored_allocator_type &get_stored_allocator() const
   {  return this->node_alloc(); }


   stored_allocator_type &get_stored_allocator()
   {  return this->node_alloc(); }


   iterator begin()
   { return iterator(this->icont().begin()); }


   const_iterator begin() const
   {  return this->cbegin();  }


   iterator end()
   {  return iterator(this->icont().end());  }


   const_iterator end() const
   {  return this->cend();  }


   reverse_iterator rbegin()
   {  return reverse_iterator(end());  }


   reverse_iterator rend()
   {  return reverse_iterator(begin());   }

   const_iterator cbegin() const
   { return const_iterator(this->non_const_icont().begin()); }

   const_iterator cend() const
   { return const_iterator(this->non_const_icont().end()); }

   const_reverse_iterator crbegin() const
   { return const_reverse_iterator(cend()); }

   const_reverse_iterator crend() const
   { return const_reverse_iterator(cbegin()); }


   bool empty() const
   {  return !this->size();  }


   size_type size() const
   {  return this->icont().size();   }


   size_type max_size() const
   {  return AllocHolder::max_size();  }


   void swap(ThisType& x)
   {  AllocHolder::swap(x);   }

      insert_equal_end_hint_functor(Icont &icont)
         :  icont_(icont), cend_(this->icont_.cend())
      {}


      void operator()(Node &n)
      {  this->icont_.insert_equal(cend_, n); }

      push_back_functor(Icont &icont)
         :  icont_(icont)
      {}


      void operator()(Node &n)
      {  this->icont_.push_back(n); }


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator==(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
           const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y)
{
  return x.size() == y.size() &&
         std::equal(x.begin(), x.end(), y.begin());
}


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator<(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
          const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y)
{
  return std::lexicographical_compare(x.begin(), x.end(),
                                      y.begin(), y.end());
}


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator!=(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
           const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y) {
  return !(x == y);
}


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator>(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
          const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y) {
  return y < x;
}


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator<=(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
           const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y) {
  return !(y < x);
}


template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline bool
operator>=(const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
           const rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y) {
  return !(x < y);
}



template <class Key, class Value, class KeyOfValue,
          class KeyCompare, class A>
inline void
swap(rbtree<Key,Value,KeyOfValue,KeyCompare,A>& x,
     rbtree<Key,Value,KeyOfValue,KeyCompare,A>& y)
{
  x.swap(y);
}

   void dummy(){}


template<class A, class T, class InpIt>
inline void construct_in_place(A &a, T* dest, InpIt source)
{     boost::container::allocator_traits<A>::construct(a, dest, *source);  }

   operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}


   PseudoReference* operator->() const { return &m_value; }

   operator_arrow_proxy(T &px)
      :  m_value(px)
   {}


   T* operator->() const { return const_cast<T*>(&m_value); }


template <class Iterator, class UnaryFunc>
transform_iterator<Iterator, UnaryFunc>
make_transform_iterator(Iterator it, UnaryFunc fun)
{
   return transform_iterator<Iterator, UnaryFunc>(it, fun);
}


   move_insert_range_proxy(A& a, FwdIt first)
      :  a_(a), first_(first)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_move_alloc_n_source
         (this->a_, this->first_, n, p);
   }


   void copy_n_and_update(Iterator p, size_type n)
   {
      this->first_ = ::boost::container::move_n_source(this->first_, n, p);
   }


   insert_range_proxy(A& a, FwdIt first)
      :  a_(a), first_(first)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n)
   {
      this->first_ = ::boost::container::uninitialized_copy_alloc_n_source(this->a_, this->first_, n, p);
   }


   void copy_n_and_update(Iterator p, size_type n)
   {
      this->first_ = ::boost::container::copy_n_source(this->first_, n, p);
   }


   insert_n_copies_proxy(A& a, const value_type &v)
      :  a_(a), v_(v)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n) const
   {  boost::container::uninitialized_fill_alloc_n(this->a_, v_, n, p);  }


   void copy_n_and_update(Iterator p, size_type n) const
   {  std::fill_n(p, n, v_);  }



   explicit insert_default_constructed_n_proxy(A &a)
      :  a_(a)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n) const
   {  boost::container::uninitialized_default_alloc_n(this->a_, n, p);  }


   void copy_n_and_update(Iterator, size_type) const
   {
      BOOST_ASSERT(false);
   }


   insert_copy_proxy(A& a, const value_type &v)
      :  a_(a), v_(v)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( this->a_
                              , container_detail::to_raw_pointer(&*p)
                              , v_
                              );
   }


   void copy_n_and_update(Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p =v_;
   }


   insert_move_proxy(A& a, value_type &v)
      :  a_(a), v_(v)
   {}


   void uninitialized_copy_n_and_update(Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      alloc_traits::construct( this->a_
                              , container_detail::to_raw_pointer(&*p)
                              , ::boost::move(v_)
                              );
   }


   void copy_n_and_update(Iterator p, size_type n) const
   {
      BOOST_ASSERT(n == 1);  (void)n;
      *p = ::boost::move(v_);
   }


template<class It, class A>
insert_move_proxy<A, It> get_insert_value_proxy(A& a, BOOST_RV_REF(typename std::iterator_traits<It>::value_type) v)
{
   return insert_move_proxy<A, It>(a, v);
}
