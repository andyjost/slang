

  template <typename OPtr>
  const_sub_array (const const_sub_array<T,NumDims,OPtr>& rhs) :
    base_(rhs.base_), extents_(rhs.extents_), strides_(rhs.strides_),
    index_base_(rhs.index_base_) {
  }

  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
                              idx,base_,shape(),strides(),index_bases());
  }

  
  template <typename IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<const element&>(),
                                      indices,origin(),
                                      shape(),strides(),index_bases());
  }


  template <typename OPtr>
  bool operator<(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return std::lexicographical_compare(begin(),end(),rhs.begin(),rhs.end());
  }


  template <typename OPtr>
  bool operator==(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    if(std::equal(shape(),shape()+num_dimensions(),rhs.shape()))
      return std::equal(begin(),end(),rhs.begin());
    else return false;
  }


  template <typename OPtr>
  bool operator!=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this == rhs);
  }


  template <typename OPtr>
  bool operator>(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return rhs < *this;
  }


  template <typename OPtr>
  bool operator<=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this > rhs);
  }


  template <typename OPtr>
  bool operator>=(const const_sub_array<T,NumDims,OPtr>& rhs) const {
    return !(*this < rhs);
  }


  const_iterator begin() const {
    return const_iterator(*index_bases(),origin(),
                          shape(),strides(),index_bases());
  }


  const_iterator end() const {
    return const_iterator(*index_bases()+(index)*shape(),origin(),
                          shape(),strides(),index_bases());
  }


  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }


  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }


  TPtr origin() const { return base_; }

  size_type size() const { return extents_[0]; }

  size_type max_size() const { return num_elements(); }

  bool empty() const { return size() == 0; }

  size_type num_dimensions() const { return NumDims; }

  const size_type*  shape() const { return extents_; }

  const index* strides() const { return strides_; }

  const index* index_bases() const { return index_base_; }


  size_type num_elements() const { 
    return std::accumulate(shape(),shape() + num_dimensions(),
                           size_type(1), std::multiplies<size_type>());
  }


  const_sub_array (TPtr base,
                 const size_type* extents,
                 const index* strides,
                 const index* index_base) :
    base_(base), extents_(extents), strides_(strides),
    index_base_(index_base) {
  }

  template <typename ConstMultiArray>
  sub_array& operator=(const ConstMultiArray& other) {
    function_requires< boost::multi_array_concepts::ConstMultiArrayConcept< 
        ConstMultiArray, NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),begin());
    return *this;
  }



  sub_array& operator=(const sub_array& other) {
    if (&other != this) {
      // make sure the dimensions agree
      BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
      BOOST_ASSERT(std::equal(other.shape(),
                              other.shape()+this->num_dimensions(),
                              this->shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),begin());
    }
    return *this;
  }


  T* origin() { return this->base_; }

  const T* origin() const { return this->base_; }


  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
                              idx,this->base_,this->shape(),this->strides(),
                              this->index_bases());
  }


  template <class IndexList>
  element& operator()(const IndexList& indices) {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<element&>(),
                                      indices,origin(),
                                      this->shape(),this->strides(),
                                      this->index_bases());
  }


  iterator begin() {
    return iterator(*this->index_bases(),origin(),
                    this->shape(),this->strides(),this->index_bases());
  }


  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),this->index_bases());
  }

  reverse_iterator rbegin() {
    reverse_iterator ri(end());
    return ri;
  }


  reverse_iterator rend() {
    reverse_iterator ri(begin());
    return ri;
  }


  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::operator()(indices);
  }


  const_reference operator[](index idx) const {
    return super_type::operator[](idx);
  }


  const_iterator begin() const {
    return super_type::begin();
  }

  
  const_iterator end() const {
    return super_type::end();
  }


  const_reverse_iterator rbegin() const {
    return super_type::rbegin();
  }


  const_reverse_iterator rend() const {
    return super_type::rend();
  }


  sub_array (T* base,
            const size_type* extents,
            const index* strides,
            const index* index_base) :
    super_type(base,extents,strides,index_base) {
  }


  extent_gen() { }


  extent_gen<NumRanges+1>
  operator[](const range& a_range)
  {
    return extent_gen<NumRanges+1>(*this,a_range);    
  }


  extent_gen<NumRanges+1>
  operator[](index idx)
  {
    return extent_gen<NumRanges+1>(*this,range(0,idx));    
  }
    

  static extent_gen<0> extents() {
    return extent_gen<0>();
  }

  template <typename Reference, typename TPtr>
  Reference access(boost::type<Reference>,index idx,TPtr base,
                   const size_type* extents,
                   const index* strides,
                   const index* index_bases) const {

    BOOST_ASSERT(idx - index_bases[0] >= 0);
    BOOST_ASSERT(size_type(idx - index_bases[0]) < extents[0]);
    // return a sub_array<T,NDims-1> proxy object
    TPtr newbase = base + idx * strides[0];
    return Reference(newbase,extents+1,strides+1,index_bases+1);

  }


  value_accessor_n() { }

  ~value_accessor_n() { }

  template <typename Reference, typename TPtr>
  Reference access(boost::type<Reference>,index idx,TPtr base,
                   const size_type* extents,
                   const index* strides,
                   const index* index_bases) const {

    ignore_unused_variable_warning(index_bases);
    ignore_unused_variable_warning(extents);
    BOOST_ASSERT(idx - index_bases[0] >= 0);
    BOOST_ASSERT(size_type(idx - index_bases[0]) < extents[0]);
    return *(base + idx * strides[0]);
  }


  value_accessor_one() { }

  ~value_accessor_one() { }


  multi_array_impl_base() { }

  ~multi_array_impl_base() { }

  template <typename Reference, typename IndexList, typename TPtr>
  Reference access_element(boost::type<Reference>,
                           const IndexList& indices,
                           TPtr base,
                           const size_type* extents,
                           const index* strides,
                           const index* index_bases) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    ignore_unused_variable_warning(index_bases);
    ignore_unused_variable_warning(extents);
#if !defined(NDEBUG) && !defined(BOOST_DISABLE_ASSERTS)
    for (size_type i = 0; i != NumDims; ++i) {
      BOOST_ASSERT(indices[i] - index_bases[i] >= 0);
      BOOST_ASSERT(size_type(indices[i] - index_bases[i]) < extents[i]);
    }
#endif

    index offset = 0;
    {
      typename IndexList::const_iterator i = indices.begin();
      size_type n = 0; 
      while (n != NumDims) {
        offset += (*i) * strides[n];
        ++n;
        ++i;
      }
    }
    return base[offset];
  }


  template <typename StrideList, typename ExtentList>
  void compute_strides(StrideList& stride_list, ExtentList& extent_list,
                       const general_storage_order<NumDims>& storage)
  {
    // invariant: stride = the stride for dimension n
    index stride = 1;
    for (size_type n = 0; n != NumDims; ++n) {
      index stride_sign = +1;
      
      if (!storage.ascending(storage.ordering(n)))
        stride_sign = -1;
      
      // The stride for this dimension is the product of the
      // lengths of the ranks minor to it.
      stride_list[storage.ordering(n)] = stride * stride_sign;
      
      stride *= extent_list[storage.ordering(n)];
    } 
  }

  template <typename StrideList, typename ExtentList, typename BaseList>
  index
  calculate_origin_offset(const StrideList& stride_list,
                          const ExtentList& extent_list,
                          const general_storage_order<NumDims>& storage,
                          const BaseList& index_base_list)
  {
    return
      calculate_descending_dimension_offset(stride_list,extent_list,
                                            storage) +
      calculate_indexing_offset(stride_list,index_base_list);
  }

  template <typename StrideList, typename ExtentList>
  index
  calculate_descending_dimension_offset(const StrideList& stride_list,
                                const ExtentList& extent_list,
                                const general_storage_order<NumDims>& storage)
  {
    index offset = 0;
    if (!storage.all_dims_ascending()) 
      for (size_type n = 0; n != NumDims; ++n)
        if (!storage.ascending(n))
          offset -= (extent_list[n] - 1) * stride_list[n];

    return offset;
  }


  template <typename StrideList, typename BaseList>
  index
  calculate_indexing_offset(const StrideList& stride_list,
                          const BaseList& index_base_list)
  {
    index offset = 0;
    for (size_type n = 0; n != NumDims; ++n)
        offset -= stride_list[n] * index_base_list[n];
    return offset;
  }

  template <typename ArrayRef, int NDims, typename TPtr>
  ArrayRef
  generate_array_view(boost::type<ArrayRef>,
                      const boost::detail::multi_array::
                      index_gen<NumDims,NDims>& indices,
                      const size_type* extents,
                      const index* strides,
                      const index* index_bases,
                      TPtr base) const {

    boost::array<index,NDims> new_strides;
    boost::array<index,NDims> new_extents;

    index offset = 0;
    size_type dim = 0;
    for (size_type n = 0; n != NumDims; ++n) {

      // Use array specs and input specs to produce real specs.
      const index default_start = index_bases[n];
      const index default_finish = default_start+extents[n];
      const index_range& current_range = indices.ranges_[n];
      index start = current_range.get_start(default_start);
      index finish = current_range.get_finish(default_finish);
      index stride = current_range.stride();
      BOOST_ASSERT(stride != 0);

      // An index range indicates a half-open strided interval 
      // [start,finish) (with stride) which faces upward when stride 
      // is positive and downward when stride is negative, 

      // RG: The following code for calculating length suffers from 
      // some representation issues: if finish-start cannot be represented as
      // by type index, then overflow may result.

      index len;
      if ((finish - start) / stride < 0) {
        // [start,finish) is empty according to the direction imposed by 
        // the stride.
        len = 0;
      } else {
        // integral trick for ceiling((finish-start) / stride) 
        // taking into account signs.
        index shrinkage = stride > 0 ? 1 : -1;
        len = (finish - start + (stride - shrinkage)) / stride;
      }

      // start marks the closed side of the range, so it must lie
      // exactly in the set of legal indices
      // with a special case for empty arrays
      BOOST_ASSERT(index_bases[n] <= start &&
                   ((start <= index_bases[n]+index(extents[n])) ||
                     (start == index_bases[n] && extents[n] == 0)));

#ifndef BOOST_DISABLE_ASSERTS
      // finish marks the open side of the range, so it can go one past
      // the "far side" of the range (the top if stride is positive, the bottom
      // if stride is negative).
      index bound_adjustment = stride < 0 ? 1 : 0;
      BOOST_ASSERT(((index_bases[n] - bound_adjustment) <= finish) &&
        (finish <= (index_bases[n] + index(extents[n]) - bound_adjustment)));
#endif // BOOST_DISABLE_ASSERTS


      // the array data pointer is modified to account for non-zero
      // bases during slicing (see [Garcia] for the math involved)
      offset += start * strides[n];

      if (!current_range.is_degenerate()) {

        // The stride for each dimension is included into the
        // strides for the array_view (see [Garcia] for the math involved).
        new_strides[dim] = stride * strides[n];
        
        // calculate new extents
        new_extents[dim] = len;
        ++dim;
      }
    }
    BOOST_ASSERT(dim == NDims);

    return
      ArrayRef(base+offset,
               new_extents,
               new_strides);
  }


  index_gen() { }


  index_gen<NumRanges+1,NumDims+1>
  operator[](const range& r) const
  {
    index_gen<NumRanges+1,NumDims+1> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = r;
    return tmp;
  }


  index_gen<NumRanges+1,NumDims>
  operator[](index idx) const
  {
    index_gen<NumRanges+1,NumDims> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = range(idx);
    return tmp;
  }
    

  static index_gen<0,0> indices() {
    return index_gen<0,0>();
  }

  operator_arrow_proxy(T const& px) : value_(px) {}

  T* operator->() const { return &value_; }

  operator T*() const { return &value_; }

  template <typename SourceIterator, typename DestIterator>
  static void copy_array (SourceIterator first, SourceIterator last,
                   DestIterator result) {
    while (first != last) {
      copy_array(*first++,*result++);
    }
  }

  template <typename Array1, typename Array2>
  static void copy_array (const Array1& source, Array2 dest) {
    copy_array(source.begin(),source.end(),dest.begin());
  }


  static void copy_array (const Element& source, Element& dest) {
    dest = source;
  }



template <typename Array1, typename Array2>
void copy_array (Array1& source, Array2& dest) {
  BOOST_ASSERT(std::equal(source.shape(),source.shape()+source.num_dimensions(),
                          dest.shape()));
  // Dispatch to the proper function
  typedef typename Array1::element element_type;
  copy_dispatch<element_type>::
    copy_array(source.begin(),source.end(),dest.begin());
}


template <class InputIter, class Size, class OutputIter>
OutputIter copy_n(InputIter first, Size count,
                  OutputIter result) {
  for ( ; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}


    template <typename Array, typename IdxGen, typename Call_Type>
    static void call(Array& a, const IdxGen& idgen, Call_Type c) {
      typedef typename Array::index_range index_range;
      typedef typename Array::index index;
      idgen_helper<N-1>::call(a,idgen[c],c);
    }


    template <typename Array, typename IdxGen, typename Call_Type>
    static void call(Array& a, const IdxGen& idgen, Call_Type) {
      typedef typename Array::index_range index_range;
      typedef typename Array::index index;
      a[ idgen ];
    }

    void constraints() {
    //    function_requires< CopyConstructibleConcept<Array> >();
    function_requires< boost_concepts::ForwardTraversalConcept<iterator> >();
    function_requires< boost_concepts::ReadableIteratorConcept<iterator> >();
    function_requires< boost_concepts::ForwardTraversalConcept<const_iterator> >();
    function_requires< boost_concepts::ReadableIteratorConcept<const_iterator> >();

      // RG - a( CollectionArchetype) when available...
      a[ id ];
      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = Array::dimensionality;
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      cit = a.begin();
      cit = a.end();
      crit = a.rbegin();
      crit = a.rend();
      eltp = a.origin();
    }

    void constraints() {
      //    function_requires< CopyConstructibleConcept<Array> >();

      function_requires< boost_concepts::ForwardTraversalConcept<iterator> >();
      function_requires< boost_concepts::ReadableIteratorConcept<iterator> >();
      function_requires< boost_concepts::WritableIteratorConcept<iterator> >();
      function_requires< boost_concepts::ForwardTraversalConcept<const_iterator> >();
      function_requires< boost_concepts::ReadableIteratorConcept<const_iterator> >();
      function_requires< boost::OutputIterator<iterator,value_type> >();
      
      // RG - a( CollectionArchetype) when available...
      value_type vt = a[ id ];

      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      it = a.begin();
      it = a.end();
      rit = a.rbegin();
      rit = a.rend();
      eltp = a.origin();
      const_constraints(a);
    }


    void const_constraints(const Array& a) {

      //      value_type vt = a[ id ];

      // Test slicing, keeping only the first dimension, losing the rest
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],id);

      // Test slicing, keeping all dimensions.
      detail::idgen_helper<NumDims-1>::call(a,idgen[range],range);

      st = a.size();
      st = a.num_dimensions();
      st = a.num_elements();
      stp = a.shape();
      idp = a.strides();
      idp = a.index_bases();
      cit = a.begin();
      cit = a.end();
      crit = a.rbegin();
      crit = a.rend();
      eltp = a.origin();
    }


  template <typename OPtr>
  const_multi_array_view(const 
                         const_multi_array_view<T,NumDims,OPtr>& other) :
    base_(other.base_), origin_offset_(other.origin_offset_),
    num_elements_(other.num_elements_), extent_list_(other.extent_list_),
    stride_list_(other.stride_list_), index_base_list_(other.index_base_list_)
  { }

  template <typename ConstMultiArray>
  multi_array_view& operator=(const ConstMultiArray& other) {
    function_requires< 
      boost::multi_array_concepts::
      ConstMultiArrayConcept<ConstMultiArray,NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),begin());
    return *this;
  }



  multi_array_view& operator=(const multi_array_view& other) {
    if (&other != this) {
      // make sure the dimensions agree
      BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
      BOOST_ASSERT(std::equal(other.shape(),
                              other.shape()+this->num_dimensions(),
                              this->shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),begin());
    }
    return *this;
  }


  element* origin() { return this->base_+this->origin_offset_; }


  template <class IndexList>
  element& operator()(const IndexList& indices) {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<element&>(),
                                      indices,origin(),
                                      this->shape(),this->strides(),
                                      this->index_bases());
  }



  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
                              idx,origin(),
                              this->shape(),this->strides(),
                              this->index_bases());
  }

  
  
  iterator begin() {
    return iterator(*this->index_bases(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }


  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }


  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }


  reverse_iterator rend() {
    return reverse_iterator(begin());
  }


  const element* origin() const { return super_type::origin(); }


  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::operator()(indices);
  }


  const_reference operator[](index idx) const {
    return super_type::operator[](idx);
  }

  
  const_iterator begin() const {
    return super_type::begin();
  }


  const_iterator end() const {
    return super_type::end();
  }


  const_reverse_iterator rbegin() const {
    return super_type::rbegin();
  }


  const_reverse_iterator rend() const {
    return super_type::rend();
  }

  template <typename ExtentList, typename Index>
  explicit multi_array_view(T* base,
                            const ExtentList& extents,
                            const boost::array<Index,NumDims>& strides) :
    super_type(base,extents,strides) { }

    template <typename OrderingIter, typename AscendingIter>
    general_storage_order(OrderingIter ordering,
                          AscendingIter ascending) {
      boost::detail::multi_array::copy_n(ordering,NumDims,ordering_.begin());
      boost::detail::multi_array::copy_n(ascending,NumDims,ascending_.begin());
    }

    general_storage_order(const c_storage_order&) {
      for (size_type i=0; i != NumDims; ++i) {
        ordering_[i] = NumDims - 1 - i;
      }
      ascending_.assign(true);
    }


    general_storage_order(const fortran_storage_order&) {
      for (size_type i=0; i != NumDims; ++i) {
        ordering_[i] = i;
      }
      ascending_.assign(true);
    }


    size_type ordering(size_type dim) const { return ordering_[dim]; }

    bool ascending(size_type dim) const { return ascending_[dim]; }


    bool all_dims_ascending() const {
      return std::accumulate(ascending_.begin(),ascending_.end(),true,
                      std::logical_and<bool>());
    }


    bool operator==(general_storage_order const& rhs) const {
      return (ordering_ == rhs.ordering_) &&
        (ascending_ == rhs.ascending_);
    }

    template <std::size_t NumDims>
    operator general_storage_order<NumDims>() const {
      boost::array<size_type,NumDims> ordering;
      boost::array<bool,NumDims> ascending;

      for (size_type i=0; i != NumDims; ++i) {
        ordering[i] = NumDims - 1 - i;
        ascending[i] = true;
      }
      return general_storage_order<NumDims>(ordering.begin(),
                                            ascending.begin());
    }

    template <std::size_t NumDims>
    operator general_storage_order<NumDims>() const {
      boost::array<size_type,NumDims> ordering;
      boost::array<bool,NumDims> ascending;

      for (size_type i=0; i != NumDims; ++i) {
        ordering[i] = i;
        ascending[i] = true;
      }
      return general_storage_order<NumDims>(ordering.begin(),
                                            ascending.begin());
    }

  template <typename OPtr>
  const_multi_array_ref(const const_multi_array_ref<T,NumDims,OPtr>& other)
    : base_(other.base_), storage_(other.storage_),
      extent_list_(other.extent_list_),
      stride_list_(other.stride_list_),
      index_base_list_(other.index_base_list_),
      origin_offset_(other.origin_offset_),
      directional_offset_(other.directional_offset_),
      num_elements_(other.num_elements_)  {  }


  template <typename ExtentList>
  explicit const_multi_array_ref(TPtr base, const ExtentList& extents) :
    base_(base), storage_(c_storage_order()) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();

    index_base_list_.assign(0);
    init_multi_array_ref(extents.begin());
  }

  
  template <class InputIterator>
  void assign(InputIterator begin, InputIterator end) {
    boost::function_requires<InputIteratorConcept<InputIterator> >();

    InputIterator in_iter = begin;
    T* out_iter = base_;
    std::size_t copy_count=0;
    while (in_iter != end && copy_count < num_elements_) {
      *out_iter++ = *in_iter++;
      copy_count++;      
    }
  }

  void set_base_ptr(TPtr new_base) { base_ = new_base; }


  void init_from_extent_gen(const
                        detail::multi_array::
                        extent_gen<NumDims>& ranges) { 
    
    typedef boost::array<index,NumDims> extent_list;

    // get the index_base values
    std::transform(ranges.ranges_.begin(),ranges.ranges_.end(),
              index_base_list_.begin(),
              boost::mem_fun_ref(&extent_range::start));

    // calculate the extents
    extent_list extents;
    std::transform(ranges.ranges_.begin(),ranges.ranges_.end(),
              extents.begin(),
              boost::mem_fun_ref(&extent_range::size));

    init_multi_array_ref(extents.begin());
  }

  template <class InputIterator>
  void init_multi_array_ref(InputIterator extents_iter) {
    boost::function_requires<InputIteratorConcept<InputIterator> >();

    boost::detail::multi_array::
      copy_n(extents_iter,num_dimensions(),extent_list_.begin());

    // Calculate the array size
    num_elements_ = std::accumulate(extent_list_.begin(),extent_list_.end(),
                            size_type(1),std::multiplies<size_type>());

    this->compute_strides(stride_list_,extent_list_,storage_);

    origin_offset_ =
      this->calculate_origin_offset(stride_list_,extent_list_,
                              storage_,index_base_list_);
    directional_offset_ =
      this->calculate_descending_dimension_offset(stride_list_,extent_list_,
                                            storage_);
  }


  template <class ExtentList>
  explicit multi_array_ref(T* base, const ExtentList& extents) :
    super_type(base,extents) {
    boost::function_requires<
      CollectionConcept<ExtentList> >();
  }

  template <typename ConstMultiArray>
  multi_array_ref& operator=(const ConstMultiArray& other) {
    function_requires< 
      multi_array_concepts::
      ConstMultiArrayConcept<ConstMultiArray,NumDims> >();

    // make sure the dimensions agree
    BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
    BOOST_ASSERT(std::equal(other.shape(),other.shape()+this->num_dimensions(),
                            this->shape()));
    // iterator-based copy
    std::copy(other.begin(),other.end(),this->begin());
    return *this;
  }


  multi_array_ref& operator=(const multi_array_ref& other) {
    if (&other != this) {
      // make sure the dimensions agree
      
      BOOST_ASSERT(other.num_dimensions() == this->num_dimensions());
      BOOST_ASSERT(std::equal(other.shape(),
                              other.shape()+this->num_dimensions(),
                              this->shape()));
      // iterator-based copy
      std::copy(other.begin(),other.end(),this->begin());
    }
    return *this;
  }


  element* origin() { return super_type::base_+super_type::origin_offset_; }


  element* data() { return super_type::base_; }


  template <class IndexList>
  element& operator()(const IndexList& indices) {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::access_element(boost::type<element&>(),
                                      indices,origin(),
                                      this->shape(),this->strides(),
                                      this->index_bases());
  }



  reference operator[](index idx) {
    return super_type::access(boost::type<reference>(),
                              idx,origin(),
                              this->shape(),this->strides(),
                              this->index_bases());
  }

  
  
  iterator begin() {
    return iterator(*this->index_bases(),origin(),this->shape(),
                    this->strides(),this->index_bases());
  }


  iterator end() {
    return iterator(*this->index_bases()+(index)*this->shape(),origin(),
                    this->shape(),this->strides(),
                    this->index_bases());
  }

  reverse_iterator rbegin() {
    reverse_iterator ri(end());
    return ri;
  }


  reverse_iterator rend() {
    reverse_iterator ri(begin());
    return ri;
  }


  const element* origin() const { return super_type::origin(); }

  const element* data() const { return super_type::data(); }


  template <class IndexList>
  const element& operator()(const IndexList& indices) const {
    boost::function_requires<
      CollectionConcept<IndexList> >();
    return super_type::operator()(indices);
  }


  const_reference operator[](index idx) const {
    return super_type::access(boost::type<const_reference>(),
                              idx,origin(),
                              this->shape(),this->strides(),
                              this->index_bases());
  }

  
  const_iterator begin() const {
    return super_type::begin();
  }


  const_iterator end() const {
    return super_type::end();
  }


  const_reverse_iterator rbegin() const {
    return super_type::rbegin();
  }


  const_reverse_iterator rend() const {
    return super_type::rend();
  }

  explicit multi_array_ref(T* base,
                           const storage_order_type& so,
                           const index* index_bases,
                           const size_type* extents) :
    super_type(base,so,index_bases,extents) { }


  extent_range(index start, index finish) :
    super_type(start,finish) { }


  extent_range(index finish) :
    super_type(0,finish) { }


  extent_range() : super_type(0,0) { }


  index start() const { return super_type::first; }


  index finish() const { return super_type::second; }


  size_type size() const { return super_type::second - super_type::first; }

    static index from_start()
      { return (std::numeric_limits<index>::min)(); }


    static index to_end()
      { return (std::numeric_limits<index>::max)(); }


    index_range()
    {
      start_ = from_start();
      finish_ = to_end();
      stride_ = 1;
      degenerate_ = false;
    }


    explicit index_range(index pos)
    {
      start_ = pos;
      finish_ = pos+1;
      stride_ = 1;
      degenerate_ = true;
    }


    explicit index_range(index start, index finish, index stride=1)
      : start_(start), finish_(finish), stride_(stride),
        degenerate_(false)
    { }

    index_range& start(index s) {
      start_ = s;
      degenerate_ = false;
      return *this;
    }


    index_range& finish(index f) {
      finish_ = f;
      degenerate_ = false;
      return *this;
    }


    index_range& stride(index s) { stride_ = s; return *this; }


    index start() const
    { 
      return start_; 
    }


    index get_start(index low_index_range = index_range::from_start()) const
    { 
      if (start_ == from_start())
        return low_index_range;
      return start_; 
    }


    index finish() const
    {
      return finish_;
    }


    index get_finish(index high_index_range = index_range::to_end()) const
    {
      if (finish_ == to_end())
        return high_index_range;
      return finish_;
    }


    index stride() const { return stride_; }


    void set_index_range(index start, index finish, index stride=1)
    {
      start_ = start;
      finish_ = finish;
      stride_ = stride;
    }


    static index_range all() 
    { return index_range(from_start(), to_end(), 1); }


    bool is_degenerate() const { return degenerate_; }


    index_range operator-(index shift) const
    { 
      return index_range(start_ - shift, finish_ - shift, stride_); 
    }


    index_range operator+(index shift) const
    { 
      return index_range(start_ + shift, finish_ + shift, stride_); 
    }


    index operator[](unsigned i) const
    {
      return start_ + i * stride_;
    }


    index operator()(unsigned i) const
    {
      return start_ + i * stride_;
    }

  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<=(Index s, const index_range<Index,SizeType>& r)
  {
    return index_range<Index,SizeType>(s, r.finish(), r.stride());
  }

  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<(Index s, const index_range<Index,SizeType>& r)
  {
    return index_range<Index,SizeType>(s + 1, r.finish(), r.stride());
  }

  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<(const index_range<Index,SizeType>& r, Index f)
  {
    return index_range<Index,SizeType>(r.start(), f, r.stride());
  }

  template <typename Index, typename SizeType>
  inline index_range<Index,SizeType>
  operator<=(const index_range<Index,SizeType>& r, Index f)
  {
    return index_range<Index,SizeType>(r.start(), f + 1, r.stride());
  }
