

  sequenced_index<SuperMeta,TagList>& operator=(
    const sequenced_index<SuperMeta,TagList>& x)
  {
    this->final()=x.final();
    return *this;
  }


  template <class InputIterator>
  void assign(InputIterator first,InputIterator last)
  {
    assign_iter(first,last,mpl::not_<is_integral<InputIterator> >());
  }

    
  allocator_type get_allocator()const
  {
    return this->final().get_allocator();
  }


  iterator               begin()
    {return make_iterator(node_type::from_impl(header()->next()));}

  const_iterator         begin()const
    {return make_iterator(node_type::from_impl(header()->next()));}

  iterator               end(){return make_iterator(header());}

  const_iterator         end()const{return make_iterator(header());}

  reverse_iterator       rbegin(){return make_reverse_iterator(end());}

  reverse_iterator       rend(){return make_reverse_iterator(begin());}

  const_iterator         cbegin()const{return begin();}

  const_iterator         cend()const{return end();}

  const_reverse_iterator crbegin()const{return rbegin();}

  const_reverse_iterator crend()const{return rend();}


  iterator iterator_to(const value_type& x)
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  bool      empty()const{return this->final_empty_();}

  size_type size()const{return this->final_size_();}

  size_type max_size()const{return this->final_max_size_();}


  void resize(size_type n,value_param_type x=value_type())
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    if(n>size())insert(end(),n-size(),x);
    else if(n<size()){
      iterator it;
      if(n<=size()/2){
        it=begin();
        std::advance(it,n);
      }
      else{
        it=end();
        for(size_type m=size()-n;m--;--it){}
      }
      erase(it,end());
    }   
  }


  const_reference front()const{return *begin();}

  const_reference back()const{return *--end();}


  static void unlink(node_type* x)
  {
    node_impl_type::unlink(x->impl());
  }


  static void relink(node_type* position,node_type* x)
  {
    node_impl_type::relink(position->impl(),x->impl());
  }

  void rearranger(node_type* position,node_type *x)
  {
    if(!position)position=header();
    node_type::increment(position);
    if(position!=x)relink(position,x);
  }


  template <class InputIterator>
  void assign_iter(InputIterator first,InputIterator last,mpl::true_)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    clear();
    for(;first!=last;++first)push_back(*first);
  }


  template<typename InputIterator>
  void insert_iter(
    iterator position,InputIterator first,InputIterator last,mpl::true_)
  {
    BOOST_MULTI_INDEX_SEQ_INDEX_CHECK_INVARIANT;
    for(;first!=last;++first)insert(position,*first);
  }


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x==y);
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return y<x;
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x<y);
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y)
{
  return !(x>y);
}


template<typename SuperMeta,typename TagList>
void swap(
  sequenced_index<SuperMeta,TagList>& x,
  sequenced_index<SuperMeta,TagList>& y)
{
  x.swap(y);
}


template<typename SuperMeta,typename TagList>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::sequenced_index<SuperMeta,TagList>*&,
  boost::foreach::tag)
{
  return 0;
}


  ordered_index<KeyFromValue,Compare,SuperMeta,TagList,Category>& operator=(
    const ordered_index<KeyFromValue,Compare,SuperMeta,TagList,Category>& x)
  {
    this->final()=x.final();
    return *this;
  }


  allocator_type get_allocator()const
  {
    return this->final().get_allocator();
  }


  iterator               begin(){return make_iterator(leftmost());}

  const_iterator         begin()const{return make_iterator(leftmost());}

  iterator               end(){return make_iterator(header());}

  const_iterator         end()const{return make_iterator(header());}

  reverse_iterator       rbegin(){return make_reverse_iterator(end());}

  reverse_iterator       rend(){return make_reverse_iterator(begin());}

  const_iterator         cbegin()const{return begin();}

  const_iterator         cend()const{return end();}

  const_reverse_iterator crbegin()const{return rbegin();}

  const_reverse_iterator crend()const{return rend();}

 
  iterator iterator_to(const value_type& x)
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  bool      empty()const{return this->final_empty_();}

  size_type size()const{return this->final_size_();}

  size_type max_size()const{return this->final_max_size_();}


  bool link_point(key_param_type k,link_info& inf,ordered_unique_tag)
  {
    node_type* y=header();
    node_type* x=root();
    bool c=true;
    while(x){
      y=x;
      c=comp_(k,key(x->value()));
      x=node_type::from_impl(c?x->left():x->right());
    }
    node_type* yy=y;
    if(c){
      if(yy==leftmost()){
        inf.side=to_left;
        inf.pos=y->impl();
        return true;
      }
      else node_type::decrement(yy);
    }

    if(comp_(key(yy->value()),k)){
      inf.side=c?to_left:to_right;
      inf.pos=y->impl();
      return true;
    }
    else{
      inf.pos=yy->impl();
      return false;
    }
  }


  bool lower_link_point(key_param_type k,link_info& inf,ordered_non_unique_tag)
  {
    node_type* y=header();
    node_type* x=root();
    bool c=false;
    while (x){
     y=x;
     c=comp_(key(x->value()),k);
     x=node_type::from_impl(c?x->right():x->left());
    }
    inf.side=c?to_right:to_left;
    inf.pos=y->impl();
    return true;
  }


  bool hinted_link_point(
    key_param_type k,node_type* position,link_info& inf,ordered_unique_tag)
  {
    if(position->impl()==header()->left()){ 
      if(size()>0&&comp_(k,key(position->value()))){
        inf.side=to_left;
        inf.pos=position->impl();
        return true;
      }
      else return link_point(k,inf,ordered_unique_tag());
    } 
    else if(position==header()){ 
      if(comp_(key(rightmost()->value()),k)){
        inf.side=to_right;
        inf.pos=rightmost()->impl();
        return true;
      }
      else return link_point(k,inf,ordered_unique_tag());
    } 
    else{
      node_type* before=position;
      node_type::decrement(before);
      if(comp_(key(before->value()),k)&&comp_(k,key(position->value()))){
        if(before->right()==node_impl_pointer(0)){
          inf.side=to_right;
          inf.pos=before->impl();
          return true;
        }
        else{
          inf.side=to_left;
          inf.pos=position->impl();
          return true;
        }
      } 
      else return link_point(k,inf,ordered_unique_tag());
    }
  }


  void delete_all_nodes(node_type* x)
  {
    if(!x)return;

    delete_all_nodes(node_type::from_impl(x->left()));
    delete_all_nodes(node_type::from_impl(x->right()));
    this->final_delete_node_(static_cast<final_node_type*>(x));
  }


  bool in_place(value_param_type v,node_type* x,ordered_unique_tag)
  {
    node_type* y;
    if(x!=leftmost()){
      y=x;
      node_type::decrement(y);
      if(!comp_(key(y->value()),key(v)))return false;
    }

    y=x;
    node_type::increment(y);
    return y==header()||comp_(key(v),key(y->value()));
  }


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator==(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator<(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator!=(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return !(x==y);
}


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator>(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return y<x;
}


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator>=(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return !(x<y);
}


template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2
>
bool operator<=(
  const ordered_index<KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1>& x,
  const ordered_index<KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2>& y)
{
  return !(x>y);
}


template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category
>
void swap(
  ordered_index<KeyFromValue,Compare,SuperMeta,TagList,Category>& x,
  ordered_index<KeyFromValue,Compare,SuperMeta,TagList,Category>& y)
{
  x.swap(y);
}


template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category
>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category>*&,
  boost::foreach::tag)
{
  return 0;
}


  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& operator=(
    const hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x)
  {
    this->final()=x.final();
    return *this;
  }


  allocator_type get_allocator()const
  {
    return this->final().get_allocator();
  }


  bool      empty()const{return this->final_empty_();}

  size_type size()const{return this->final_size_();}

  size_type max_size()const{return this->final_max_size_();}


  iterator begin()
  {
    return make_iterator(
      node_type::from_impl(buckets.at(first_bucket)->next()));
  }


  const_iterator begin()const
  {
    return make_iterator(
      node_type::from_impl(buckets.at(first_bucket)->next()));
  }


  iterator       end(){return make_iterator(header());}

  const_iterator end()const{return make_iterator(header());}


  const_iterator cbegin()const{return begin();}

  const_iterator cend()const{return end();}


  iterator iterator_to(const value_type& x)
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  static void link(node_impl_pointer x,node_impl_pointer pos)
  {
    node_impl_type::link(x,pos);
  };


  static void unlink(node_type* x)
  {
    node_impl_type::unlink(x->impl());
  };


  static node_impl_pointer prev(node_type* x)
  {
    return node_impl_type::prev(x->impl());
  }


  static node_impl_pointer prev_from(node_type* x,node_impl_pointer y)
  {
    return node_impl_type::prev_from(x->impl(),y);
  }


  static void unlink_next(node_impl_pointer x)
  {
    node_impl_type::unlink_next(x);
  }


  void calculate_max_load()
  {
    float fml=static_cast<float>(mlf*bucket_count());
    max_load=(std::numeric_limits<size_type>::max)();
    if(max_load>fml)max_load=static_cast<size_type>(fml);
  }


  void reserve(size_type n)
  {
    if(n>max_load){
      size_type bc =(std::numeric_limits<size_type>::max)();
      float     fbc=static_cast<float>(1+static_cast<double>(n)/mlf);
      if(bc>fbc)bc =static_cast<size_type>(fbc);
      unchecked_rehash(bc);
    }
  }


  void unchecked_rehash(size_type n)
  {
    bucket_array_type buckets1(get_allocator(),header()->impl(),n);
    auto_space<std::size_t,allocator_type> hashes(get_allocator(),size());

    std::size_t i=0;
    node_impl_pointer x=buckets.begin();
    node_impl_pointer x_end=buckets.end();
    for(;x!=x_end;++x){
      node_impl_pointer y=x->next();
      while(y!=x){
        hashes.data()[i++]=hash_(key(node_type::from_impl(y)->value()));
        y=y->next();
      }
    }

    i=0;
    x=buckets.begin();
    for(;x!=x_end;++x){
      node_impl_pointer y=x->next();
      while(y!=x){
        node_impl_pointer z=y->next();
        std::size_t       buc1=buckets1.position(hashes.data()[i++]);
        node_impl_pointer x1=buckets1.at(buc1);
        link(y,x1);
        y=z;
      }
    }

    buckets.swap(buckets1);
    calculate_max_load();
    first_bucket=buckets.first_nonempty(0);
  }


  bool in_place(
    node_impl_pointer x,key_param_type k,std::size_t buc,
    hashed_unique_tag)const
  {
    std::less_equal<node_impl_pointer> leq;
    node_impl_pointer                  bbegin=buckets.begin();
    node_impl_pointer                  bend=buckets.end();
    node_impl_pointer                  pbuc=x->next();

    while(!leq(bbegin,pbuc)||!leq(pbuc,bend))pbuc=pbuc->next();
    if(buc!=static_cast<std::size_t>(pbuc-bbegin))return false;

    node_impl_pointer y=x;
    while(y->next()!=x){
      y=y->next();
      if(y==pbuc)continue;
      if(eq_(k,key(node_type::from_impl(y)->value())))return false;
    }
    return true;
  }


template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
void swap(
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& x,
  hashed_index<KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>& y)
{
  x.swap(y);
}


template<
  typename KeyFromValue,typename Hash,typename Pred,
  typename SuperMeta,typename TagList,typename Category
>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::hashed_index<
    KeyFromValue,Hash,Pred,SuperMeta,TagList,Category>*&,
  boost::foreach::tag)
{
  return 0;
}


  random_access_index<SuperMeta,TagList>& operator=(
    const random_access_index<SuperMeta,TagList>& x)
  {
    this->final()=x.final();
    return *this;
  }


  template <class InputIterator>
  void assign(InputIterator first,InputIterator last)
  {
    assign_iter(first,last,mpl::not_<is_integral<InputIterator> >());
  }

    
  allocator_type get_allocator()const
  {
    return this->final().get_allocator();
  }


  iterator               begin()
    {return make_iterator(node_type::from_impl(*ptrs.begin()));}

  const_iterator         begin()const
    {return make_iterator(node_type::from_impl(*ptrs.begin()));}

  iterator               end(){return make_iterator(header());}

  const_iterator         end()const{return make_iterator(header());}

  reverse_iterator       rbegin(){return make_reverse_iterator(end());}

  reverse_iterator       rend(){return make_reverse_iterator(begin());}

  const_iterator         cbegin()const{return begin();}

  const_iterator         cend()const{return end();}

  const_reverse_iterator crbegin()const{return rbegin();}

  const_reverse_iterator crend()const{return rend();}


  iterator iterator_to(const value_type& x)
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  const_iterator iterator_to(const value_type& x)const
  {
    return make_iterator(node_from_value<node_type>(&x));
  }


  bool      empty()const{return this->final_empty_();}

  size_type size()const{return this->final_size_();}

  size_type max_size()const{return this->final_max_size_();}

  size_type capacity()const{return ptrs.capacity();}

  void      reserve(size_type n){ptrs.reserve(n);}


  void resize(size_type n,value_param_type x=value_type())
  {
    BOOST_MULTI_INDEX_RND_INDEX_CHECK_INVARIANT;
    if(n>size())insert(end(),n-size(),x);
    else if(n<size())erase(begin()+n,end());
  }


  const_reference operator[](size_type n)const
  {
    BOOST_MULTI_INDEX_SAFE_MODE_ASSERT(n<size(),safe_mode::out_of_bounds);
    return node_type::from_impl(*ptrs.at(n))->value();
  }


  const_reference at(size_type n)const
  {
    if(n>=size())throw_exception(std::out_of_range("random access index"));
    return node_type::from_impl(*ptrs.at(n))->value();
  }


  const_reference front()const{return operator[](0);}

  const_reference back()const{return operator[](size()-1);}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x==y);
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return y<x;
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x<y);
}


template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y)
{
  return !(x>y);
}


template<typename SuperMeta,typename TagList>
void swap(
  random_access_index<SuperMeta,TagList>& x,
  random_access_index<SuperMeta,TagList>& y)
{
  x.swap(y);
}


template<typename SuperMeta,typename TagList>
inline boost::mpl::true_* boost_foreach_is_noncopyable(
  boost::multi_index::detail::random_access_index<SuperMeta,TagList>*&,
  boost::foreach::tag)
{
  return 0;
}

  template<typename T,typename Q>
  bool operator()(const T& x,const Q& y)const{return x==y;}

  template<typename T,typename Q>
  bool operator()(const T& x,const Q& y)const{return x<y;}

  static bool compare(
    const KeyCons1&,const Value1&,
    const KeyCons2&,const Value2&,
    const EqualCons&)
  {
    return true;
  }

  static bool compare(
    const KeyCons1& c0,const Value1& v0,
    const KeyCons2& c1,const Value2& v1,
    const EqualCons& eq)
  {
    if(!eq.get_head()(c0.get_head()(v0),c1.get_head()(v1)))return false;
    return equal_ckey_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons1::tail_type,Value1,
      BOOST_DEDUCED_TYPENAME KeyCons2::tail_type,Value2,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(c0.get_tail(),v0,c1.get_tail(),v1,eq.get_tail());
  }

  static bool compare(
    const KeyCons&,const Value&,const ValCons&,const EqualCons&)
  {
    return true;
  }


  static bool compare(
    const ValCons&,const KeyCons&,const Value&,const EqualCons&)
  {
    return true;
  }

  static bool compare(
    const KeyCons& c,const Value& v,const ValCons& vc,
    const EqualCons& eq)
  {
    if(!eq.get_head()(c.get_head()(v),vc.get_head()))return false;
    return equal_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(c.get_tail(),v,vc.get_tail(),eq.get_tail());
  }


  static bool compare(
    const ValCons& vc,const KeyCons& c,const Value& v,
    const EqualCons& eq)
  {
    if(!eq.get_head()(vc.get_head(),c.get_head()(v)))return false;
    return equal_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME EqualCons::tail_type
    >::compare(vc.get_tail(),c.get_tail(),v,eq.get_tail());
  }

  static bool compare(
    const KeyCons1&,const Value1&,
    const KeyCons2&,const Value2&,
    const CompareCons&)
  {
    return false;
  }

  static bool compare(
    const KeyCons1& c0,const Value1& v0,
    const KeyCons2& c1,const Value2& v1,
    const CompareCons& comp)
  {
    if(comp.get_head()(c0.get_head()(v0),c1.get_head()(v1)))return true;
    if(comp.get_head()(c1.get_head()(v1),c0.get_head()(v0)))return false;
    return compare_ckey_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons1::tail_type,Value1,
      BOOST_DEDUCED_TYPENAME KeyCons2::tail_type,Value2,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(c0.get_tail(),v0,c1.get_tail(),v1,comp.get_tail());
  }

  static bool compare(
    const KeyCons&,const Value&,const ValCons&,const CompareCons&)
  {
    return false;
  }


  static bool compare(
    const ValCons&,const KeyCons&,const Value&,const CompareCons&)
  {
    return false;
  }

  static bool compare(
    const KeyCons& c,const Value& v,const ValCons& vc,
    const CompareCons& comp)
  {
    if(comp.get_head()(c.get_head()(v),vc.get_head()))return true;
    if(comp.get_head()(vc.get_head(),c.get_head()(v)))return false;
    return compare_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(c.get_tail(),v,vc.get_tail(),comp.get_tail());
  }


  static bool compare(
    const ValCons& vc,const KeyCons& c,const Value& v,
    const CompareCons& comp)
  {
    if(comp.get_head()(vc.get_head(),c.get_head()(v)))return true;
    if(comp.get_head()(c.get_head()(v),vc.get_head()))return false;
    return compare_ckey_cval<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME CompareCons::tail_type
    >::compare(vc.get_tail(),c.get_tail(),v,comp.get_tail());
  }

  static std::size_t hash(
    const KeyCons&,const Value&,const HashCons&,std::size_t carry)
  {
    return carry;
  }

  static std::size_t hash(
    const KeyCons& c,const Value& v,const HashCons& h,std::size_t carry=0)
  {
    /* same hashing formula as boost::hash_combine */

    carry^=h.get_head()(c.get_head()(v))+0x9e3779b9+(carry<<6)+(carry>>2);
    return hash_ckey<
      BOOST_DEDUCED_TYPENAME KeyCons::tail_type,Value,
      BOOST_DEDUCED_TYPENAME HashCons::tail_type
    >::hash(c.get_tail(),v,h.get_tail(),carry);
  }

  static std::size_t hash(const ValCons&,const HashCons&,std::size_t carry)
  {
    return carry;
  }

  static std::size_t hash(
    const ValCons& vc,const HashCons& h,std::size_t carry=0)
  {
    carry^=h.get_head()(vc.get_head())+0x9e3779b9+(carry<<6)+(carry>>2);
    return hash_cval<
      BOOST_DEDUCED_TYPENAME ValCons::tail_type,
      BOOST_DEDUCED_TYPENAME HashCons::tail_type
    >::hash(vc.get_tail(),h.get_tail(),carry);
  }


  composite_key_result(
    const composite_key_type& composite_key_,const value_type& value_):
    composite_key(composite_key_),value(value_)
  {}


  composite_key(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,KeyFromValue)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}


  composite_key(const key_extractor_tuple& x):super(x){}


  const key_extractor_tuple& key_extractors()const{return *this;}

  key_extractor_tuple&       key_extractors(){return *this;}


template<typename CompositeKey1,typename CompositeKey2>
inline bool operator==(
  const composite_key_result<CompositeKey1>& x,
  const composite_key_result<CompositeKey2>& y)
{
  typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
  typedef typename CompositeKey1::value_type          value_type1;
  typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
  typedef typename CompositeKey2::value_type          value_type2;

  BOOST_STATIC_ASSERT(
    tuples::length<key_extractor_tuple1>::value==
    tuples::length<key_extractor_tuple2>::value);

  return detail::equal_ckey_ckey<
    key_extractor_tuple1,value_type1,
    key_extractor_tuple2,value_type2,
    detail::generic_operator_equal_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y.composite_key.key_extractors(),y.value,
    detail::generic_operator_equal_tuple());
}


template<typename CompositeKey1,typename CompositeKey2>
inline bool operator<(
  const composite_key_result<CompositeKey1>& x,
  const composite_key_result<CompositeKey2>& y)
{
  typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
  typedef typename CompositeKey1::value_type          value_type1;
  typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
  typedef typename CompositeKey2::value_type          value_type2;

  return detail::compare_ckey_ckey<
   key_extractor_tuple1,value_type1,
   key_extractor_tuple2,value_type2,
   detail::generic_operator_less_tuple
  >::compare(
    x.composite_key.key_extractors(),x.value,
    y.composite_key.key_extractors(),y.value,
    detail::generic_operator_less_tuple());
}
                  template<t1,t2> inline bool operator!=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x==y);                                                            \
}                                                                            \
                                                                             template<t1,t2> inline bool operator>(const a1& x,const a2& y)               \
{                                                                            \
  return y<x;                                                                \
}                                                                            \
                                                                             template<t1,t2> inline bool operator>=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x<y);                                                             \
}                                                                            \
                                                                             template<t1,t2> inline bool operator<=(const a1& x,const a2& y)              \
{                                                                            \
  return !(y<x);                                                             \
}

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey1,
  typename CompositeKey2,
  composite_key_result<CompositeKey1>,
  composite_key_result<CompositeKey2>
)
                                                                            \
                                                                             template<t1,t2> inline bool operator>(const a1& x,const a2& y)               \
{                                                                            \
  return y<x;                                                                \
}                                                                            \
                                                                             template<t1,t2> inline bool operator>=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x<y);                                                             \
}                                                                            \
                                                                             template<t1,t2> inline bool operator<=(const a1& x,const a2& y)              \
{                                                                            \
  return !(y<x);                                                             \
}

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey1,
  typename CompositeKey2,
  composite_key_result<CompositeKey1>,
  composite_key_result<CompositeKey2>
)
                                                                            \
                                                                             template<t1,t2> inline bool operator>=(const a1& x,const a2& y)              \
{                                                                            \
  return !(x<y);                                                             \
}                                                                            \
                                                                             template<t1,t2> inline bool operator<=(const a1& x,const a2& y)              \
{                                                                            \
  return !(y<x);                                                             \
}

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey1,
  typename CompositeKey2,
  composite_key_result<CompositeKey1>,
  composite_key_result<CompositeKey2>
)
                                                                            \
                                                                             template<t1,t2> inline bool operator<=(const a1& x,const a2& y)              \
{                                                                            \
  return !(y<x);                                                             \
}

BOOST_MULTI_INDEX_CK_COMPLETE_COMP_OPS(
  typename CompositeKey1,
  typename CompositeKey2,
  composite_key_result<CompositeKey1>,
  composite_key_result<CompositeKey2>
)


  composite_key_equal_to(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Pred)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}


  composite_key_equal_to(const key_eq_tuple& x):super(x){}


  const key_eq_tuple& key_eqs()const{return *this;}

  key_eq_tuple&       key_eqs(){return *this;}


  template<typename CompositeKey1,typename CompositeKey2>
  bool operator()(
    const composite_key_result<CompositeKey1> & x,
    const composite_key_result<CompositeKey2> & y)const
  {
    typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
    typedef typename CompositeKey1::value_type          value_type1;
    typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
    typedef typename CompositeKey2::value_type          value_type2;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple1>::value<=
      tuples::length<key_eq_tuple>::value&&
      tuples::length<key_extractor_tuple1>::value==
      tuples::length<key_extractor_tuple2>::value);

    return detail::equal_ckey_ckey<
      key_extractor_tuple1,value_type1,
      key_extractor_tuple2,value_type2,
      key_eq_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      y.composite_key.key_extractors(),y.value,
      key_eqs());
  }


  composite_key_compare(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Compare)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}


  composite_key_compare(const key_comp_tuple& x):super(x){}


  const key_comp_tuple& key_comps()const{return *this;}

  key_comp_tuple&       key_comps(){return *this;}


  template<typename CompositeKey1,typename CompositeKey2>
  bool operator()(
    const composite_key_result<CompositeKey1> & x,
    const composite_key_result<CompositeKey2> & y)const
  {
    typedef typename CompositeKey1::key_extractor_tuple key_extractor_tuple1;
    typedef typename CompositeKey1::value_type          value_type1;
    typedef typename CompositeKey2::key_extractor_tuple key_extractor_tuple2;
    typedef typename CompositeKey2::value_type          value_type2;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple1>::value<=
      tuples::length<key_comp_tuple>::value||
      tuples::length<key_extractor_tuple2>::value<=
      tuples::length<key_comp_tuple>::value);

    return detail::compare_ckey_ckey<
      key_extractor_tuple1,value_type1,
      key_extractor_tuple2,value_type2,
      key_comp_tuple
    >::compare(
      x.composite_key.key_extractors(),x.value,
      y.composite_key.key_extractors(),y.value,
      key_comps());
  }

  template<typename CompositeKey,typename Value>
  bool operator()(
    const composite_key_result<CompositeKey>& x,
    const Value& y)const
  {
    return operator()(x,boost::make_tuple(boost::cref(y)));
  }

  template<typename Value,typename CompositeKey>
  bool operator()(
    const Value& x,
    const composite_key_result<CompositeKey>& y)const
  {
    return operator()(boost::make_tuple(boost::cref(x)),y);
  }


  composite_key_hash(
    BOOST_MULTI_INDEX_CK_ENUM(BOOST_MULTI_INDEX_CK_CTOR_ARG,Hash)):
    super(BOOST_MULTI_INDEX_CK_ENUM_PARAMS(k))
  {}


  composite_key_hash(const key_hasher_tuple& x):super(x){}


  const key_hasher_tuple& key_hash_functions()const{return *this;}

  key_hasher_tuple&       key_hash_functions(){return *this;}


  template<typename CompositeKey>
  std::size_t operator()(const composite_key_result<CompositeKey> & x)const
  {
    typedef typename CompositeKey::key_extractor_tuple key_extractor_tuple;
    typedef typename CompositeKey::value_type          value_type;

    BOOST_STATIC_ASSERT(
      tuples::length<key_extractor_tuple>::value==
      tuples::length<key_hasher_tuple>::value);

    return detail::hash_ckey<
      key_extractor_tuple,value_type,
      key_hasher_tuple
    >::hash(x.composite_key.key_extractors(),x.value,key_hash_functions());
  }

  entry(void* node_,std::size_t pos_=0):node(node_),pos(pos_){}

    bool operator()(
      const entry& x,const entry& y)const
    {
      return std::less<void*>()(x.node,y.node);
    }

    bool operator()(
      const entry& x,const entry& y)const
    {
      return x.pile_top<y.pile_top;
    }

  algorithm_base(const Allocator& al,std::size_t size):
    spc(al,size),size_(size),n_(0),sorted(false)
  {
  }


  void add(void* node)
  {
    entries()[n_]=entry(node,n_);
    ++n_;
  }


  void begin_algorithm()const
  {
    if(!sorted){
      std::sort(entries(),entries()+size_,entry::less_by_node());
      sorted=true;
    }
    num_piles=0;
  }


  void add_node_to_algorithm(void* node)const
  {
    entry* ent=
      std::lower_bound(
        entries(),entries()+size_,
        entry(node),entry::less_by_node()); /* localize entry */
    ent->ordered=false;
    std::size_t n=ent->pos;                 /* get its position */

    entry dummy(0);
    dummy.pile_top=n;

    entry* pile_ent=                        /* find the first available pile */
      std::lower_bound(                     /* to stack the entry            */
        entries(),entries()+num_piles,
        dummy,entry::less_by_pile_top());

    pile_ent->pile_top=n;                   /* stack the entry */
    pile_ent->pile_top_entry=ent;        

    /* if not the first pile, link entry to top of the preceding pile */
    if(pile_ent>&entries()[0]){ 
      ent->previous=(pile_ent-1)->pile_top_entry;
    }

    if(pile_ent==&entries()[num_piles]){    /* new pile? */
      ++num_piles;
    }
  }


  void finish_algorithm()const
  {
    if(num_piles>0){
      /* Mark those elements which are in their correct position, i.e. those
       * belonging to the longest increasing subsequence. These are those
       * elements linked from the top of the last pile.
       */

      entry* ent=entries()[num_piles-1].pile_top_entry;
      for(std::size_t n=num_piles;n--;){
        ent->ordered=true;
        ent=ent->previous;
      }
    }
  }


  bool is_ordered(void * node)const
  {
    return std::lower_bound(
      entries(),entries()+size_,
      entry(node),entry::less_by_node())->ordered;
  }

  entry* entries()const{return &*spc.data();}

  algorithm(const Allocator& al,std::size_t size):super(al,size){}


  void add(Node* node)
  {
    super::add(node);
  }


  template<typename IndexIterator>
  void execute(IndexIterator first,IndexIterator last)const
  {
    super::begin_algorithm();

    for(IndexIterator it=first;it!=last;++it){
      add_node_to_algorithm(get_node(it));
    }

    super::finish_algorithm();
  }


  bool is_ordered(Node* node)const
  {
    return super::is_ordered(node);
  }

  void add_node_to_algorithm(Node* node)const
  {
    super::add_node_to_algorithm(node);
  }


  template<typename IndexIterator>
  static Node* get_node(IndexIterator it)
  {
    return static_cast<Node*>(it.get_node());
  }


template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_find(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  Node* y0=y;

  while (top){
    if(!comp(key(top->value()),x)){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }
    
  return (y==y0||comp(x,key(y->value())))?y0:y;
}


template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_lower_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  while(top){
    if(!comp(key(top->value()),x)){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }

  return y;
}


template<
  typename Node,typename KeyFromValue,
  typename CompatibleKey,typename CompatibleCompare
>
inline Node* ordered_index_upper_bound(
  Node* top,Node* y,const KeyFromValue& key,const CompatibleKey& x,
  const CompatibleCompare& comp)
{
  while(top){
    if(comp(x,key(top->value()))){
      y=top;
      top=Node::from_impl(top->left());
    }
    else top=Node::from_impl(top->right());
  }

  return y;
}

  header_holder():member(final().allocate_node()){}

  ~header_holder(){final().deallocate_node(&*member);}

  Final& final(){return *static_cast<Final*>(this);}

  scope_guard_impl_base():dismissed_(false){}

  void dismiss()const{dismissed_=true;}

  void touch()const{}

  ~scope_guard_impl_base(){}


  scope_guard_impl_base(const scope_guard_impl_base& other):
    dismissed_(other.dismissed_)
  {
    other.dismiss();
  }


  template<typename J>
  static void safe_execute(J& j){
    BOOST_TRY{
      if(!j.dismissed_)j.execute();
    }
    BOOST_CATCH(...){}
    BOOST_CATCH_END
  }

    template< class T1 >
    null_guard( const T1& )
    { }


    template< class T1, class T2 >
    null_guard( const T1&, const T2& )
    { }


    template< class T1, class T2, class T3 >
    null_guard( const T1&, const T2&, const T3& )
    { }


    template< class T1, class T2, class T3, class T4 >
    null_guard( const T1&, const T2&, const T3&, const T4& )
    { }


    template< class T1, class T2, class T3, class T4, class T5 >
    null_guard( const T1&, const T2&, const T3&, const T4&, const T5& )
    { }

  scope_guard_impl0(F fun):fun_(fun){}

  ~scope_guard_impl0(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){fun_();}


template<typename F> 
inline scope_guard_impl0<F> make_guard(F fun)
{
  return scope_guard_impl0<F>(fun);
}


template<bool cond, typename F> 
inline typename null_guard_return<cond,scope_guard_impl0<F> >::type  
make_guard_if_c(F fun)
{
  return typename null_guard_return<cond,scope_guard_impl0<F> >::type(fun);
}


template<typename C, typename F> 
inline typename null_guard_return<C::value,scope_guard_impl0<F> >::type  
make_guard_if(F fun)
{
  return make_guard_if<C::value>(fun);
}

  scope_guard_impl1(F fun,P1 p1):fun_(fun),p1_(p1){}

  ~scope_guard_impl1(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){fun_(p1_);}


template<typename F,typename P1> 
inline scope_guard_impl1<F,P1> make_guard(F fun,P1 p1)
{
  return scope_guard_impl1<F,P1>(fun,p1);
}


template<bool cond, typename F,typename P1> 
inline typename null_guard_return<cond,scope_guard_impl1<F,P1> >::type 
make_guard_if_c(F fun,P1 p1)
{
  return typename null_guard_return<cond,scope_guard_impl1<F,P1> >::type(fun,p1);
}


template<typename C, typename F,typename P1> 
inline typename null_guard_return<C::value,scope_guard_impl1<F,P1> >::type 
make_guard_if(F fun,P1 p1)
{
  return make_guard_if_c<C::value>(fun,p1);
}

  scope_guard_impl2(F fun,P1 p1,P2 p2):fun_(fun),p1_(p1),p2_(p2){}

  ~scope_guard_impl2(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){fun_(p1_,p2_);}


template<typename F,typename P1,typename P2>
inline scope_guard_impl2<F,P1,P2> make_guard(F fun,P1 p1,P2 p2)
{
  return scope_guard_impl2<F,P1,P2>(fun,p1,p2);
}


template<bool cond, typename F,typename P1,typename P2>
inline typename null_guard_return<cond,scope_guard_impl2<F,P1,P2> >::type
make_guard_if_c(F fun,P1 p1,P2 p2)
{
  return typename null_guard_return<cond,scope_guard_impl2<F,P1,P2> >::type(fun,p1,p2);
}


template<typename C, typename F,typename P1,typename P2>
inline typename null_guard_return<C::value,scope_guard_impl2<F,P1,P2> >::type
make_guard_if(F fun,P1 p1,P2 p2)
{
  return make_guard_if_c<C::value>(fun,p1,p2);
}

  scope_guard_impl3(F fun,P1 p1,P2 p2,P3 p3):fun_(fun),p1_(p1),p2_(p2),p3_(p3){}

  ~scope_guard_impl3(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){fun_(p1_,p2_,p3_);}


template<typename F,typename P1,typename P2,typename P3>
inline scope_guard_impl3<F,P1,P2,P3> make_guard(F fun,P1 p1,P2 p2,P3 p3)
{
  return scope_guard_impl3<F,P1,P2,P3>(fun,p1,p2,p3);
}


template<bool cond,typename F,typename P1,typename P2,typename P3>
inline typename null_guard_return<cond,scope_guard_impl3<F,P1,P2,P3> >::type 
make_guard_if_c(F fun,P1 p1,P2 p2,P3 p3)
{
  return typename null_guard_return<cond,scope_guard_impl3<F,P1,P2,P3> >::type(fun,p1,p2,p3);
}


template<typename C,typename F,typename P1,typename P2,typename P3>
inline typename null_guard_return< C::value,scope_guard_impl3<F,P1,P2,P3> >::type 
make_guard_if(F fun,P1 p1,P2 p2,P3 p3)
{
  return make_guard_if_c<C::value>(fun,p1,p2,p3);
}

  scope_guard_impl4(F fun,P1 p1,P2 p2,P3 p3,P4 p4):
    fun_(fun),p1_(p1),p2_(p2),p3_(p3),p4_(p4){}

  ~scope_guard_impl4(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){fun_(p1_,p2_,p3_,p4_);}


template<typename F,typename P1,typename P2,typename P3,typename P4>
inline scope_guard_impl4<F,P1,P2,P3,P4> make_guard(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return scope_guard_impl4<F,P1,P2,P3,P4>(fun,p1,p2,p3,p4);
}


template<bool cond, typename F,typename P1,typename P2,typename P3,typename P4>
inline typename null_guard_return<cond,scope_guard_impl4<F,P1,P2,P3,P4> >::type 
make_guard_if_c(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return typename null_guard_return<cond,scope_guard_impl4<F,P1,P2,P3,P4> >::type(fun,p1,p2,p3,p4);
}


template<typename C, typename F,typename P1,typename P2,typename P3,typename P4>
inline typename null_guard_return<C::value,scope_guard_impl4<F,P1,P2,P3,P4> >::type 
make_guard_if(
  F fun,P1 p1,P2 p2,P3 p3,P4 p4)
{
  return make_guard_if_c<C::value>(fun,p1,p2,p3,p4);
}

  obj_scope_guard_impl0(Obj& obj,MemFun mem_fun):obj_(obj),mem_fun_(mem_fun){}

  ~obj_scope_guard_impl0(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){(obj_.*mem_fun_)();}


template<class Obj,typename MemFun>
inline obj_scope_guard_impl0<Obj,MemFun> make_obj_guard(Obj& obj,MemFun mem_fun)
{
  return obj_scope_guard_impl0<Obj,MemFun>(obj,mem_fun);
}


template<bool cond, class Obj,typename MemFun>
inline typename null_guard_return<cond,obj_scope_guard_impl0<Obj,MemFun> >::type 
make_obj_guard_if_c(Obj& obj,MemFun mem_fun)
{
  return typename null_guard_return<cond,obj_scope_guard_impl0<Obj,MemFun> >::type(obj,mem_fun);
}


template<typename C, class Obj,typename MemFun>
inline typename null_guard_return<C::value,obj_scope_guard_impl0<Obj,MemFun> >::type 
make_obj_guard_if(Obj& obj,MemFun mem_fun)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun);
}

  obj_scope_guard_impl1(Obj& obj,MemFun mem_fun,P1 p1):
    obj_(obj),mem_fun_(mem_fun),p1_(p1){}

  ~obj_scope_guard_impl1(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){(obj_.*mem_fun_)(p1_);}


template<class Obj,typename MemFun,typename P1>
inline obj_scope_guard_impl1<Obj,MemFun,P1> make_obj_guard(
  Obj& obj,MemFun mem_fun,P1 p1)
{
  return obj_scope_guard_impl1<Obj,MemFun,P1>(obj,mem_fun,p1);
}


template<bool cond, class Obj,typename MemFun,typename P1>
inline typename null_guard_return<cond,obj_scope_guard_impl1<Obj,MemFun,P1> >::type 
make_obj_guard_if_c(  Obj& obj,MemFun mem_fun,P1 p1)
{
  return typename null_guard_return<cond,obj_scope_guard_impl1<Obj,MemFun,P1> >::type(obj,mem_fun,p1);
}


template<typename C, class Obj,typename MemFun,typename P1>
inline typename null_guard_return<C::value,obj_scope_guard_impl1<Obj,MemFun,P1> >::type 
make_obj_guard_if( Obj& obj,MemFun mem_fun,P1 p1)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1);
}

  obj_scope_guard_impl2(Obj& obj,MemFun mem_fun,P1 p1,P2 p2):
    obj_(obj),mem_fun_(mem_fun),p1_(p1),p2_(p2)
  {}

  ~obj_scope_guard_impl2(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){(obj_.*mem_fun_)(p1_,p2_);}


template<class Obj,typename MemFun,typename P1,typename P2>
inline obj_scope_guard_impl2<Obj,MemFun,P1,P2>
make_obj_guard(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return obj_scope_guard_impl2<Obj,MemFun,P1,P2>(obj,mem_fun,p1,p2);
}


template<bool cond, class Obj,typename MemFun,typename P1,typename P2>
inline typename null_guard_return<cond,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type
make_obj_guard_if_c(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return typename null_guard_return<cond,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type(obj,mem_fun,p1,p2);
}


template<typename C, class Obj,typename MemFun,typename P1,typename P2>
inline typename null_guard_return<C::value,obj_scope_guard_impl2<Obj,MemFun,P1,P2> >::type
make_obj_guard_if(Obj& obj,MemFun mem_fun,P1 p1,P2 p2)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1,p2);
}

  obj_scope_guard_impl3(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3):
    obj_(obj),mem_fun_(mem_fun),p1_(p1),p2_(p2),p3_(p3)
  {}

  ~obj_scope_guard_impl3(){scope_guard_impl_base::safe_execute(*this);}

  void execute(){(obj_.*mem_fun_)(p1_,p2_,p3_);}


template<class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3>
make_obj_guard(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3>(obj,mem_fun,p1,p2,p3);
}


template<bool cond, class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline typename null_guard_return<cond,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type
make_obj_guard_if_c(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return typename null_guard_return<cond,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type(obj,mem_fun,p1,p2,p3);
}


template<typename C, class Obj,typename MemFun,typename P1,typename P2,typename P3>
inline typename null_guard_return<C::value,obj_scope_guard_impl3<Obj,MemFun,P1,P2,P3> >::type
make_obj_guard_if(Obj& obj,MemFun mem_fun,P1 p1,P2 p2,P3 p3)
{
  return make_obj_guard_if_c<C::value>(obj,mem_fun,p1,p2,p3);
}


template <typename SequencedIndex,typename Predicate>
void sequenced_index_remove(SequencedIndex& x,Predicate pred)
{
  typedef typename SequencedIndex::iterator iterator;
  iterator first=x.begin(),last=x.end();
  while(first!=last){
    if(pred(*first))x.erase(first++);
    else ++first;
  }
}


template <typename SequencedIndex,class BinaryPredicate>
void sequenced_index_unique(SequencedIndex& x,BinaryPredicate binary_pred)
{
  typedef typename SequencedIndex::iterator iterator;
  iterator first=x.begin();
  iterator last=x.end();
  if(first!=last){
    for(iterator middle=first;++middle!=last;middle=first){
      if(binary_pred(*middle,*first))x.erase(middle);
      else first=middle;
    }
  }
}


template <typename SequencedIndex,typename Compare>
void sequenced_index_merge(SequencedIndex& x,SequencedIndex& y,Compare comp)
{
  typedef typename SequencedIndex::iterator iterator;
  if(&x!=&y){
    iterator first0=x.begin(),last0=x.end();
    iterator first1=y.begin(),last1=y.end();
    while(first0!=last0&&first1!=last1){
      if(comp(*first1,*first0))x.splice(first0,y,first1++);
      else ++first0;
    }
    x.splice(last0,y,first1,last1);
  }
}


template<typename Node,typename Compare>
void sequenced_index_collate(
  BOOST_DEDUCED_TYPENAME Node::impl_type* x,
  BOOST_DEDUCED_TYPENAME Node::impl_type* y,
  Compare comp
  BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Node))
{
  typedef typename Node::impl_type    impl_type;
  typedef typename Node::impl_pointer impl_pointer;

  impl_pointer first0=x->next();
  impl_pointer last0=x;
  impl_pointer first1=y->next();
  impl_pointer last1=y;
  while(first0!=last0&&first1!=last1){
    if(comp(
        Node::from_impl(first1)->value(),Node::from_impl(first0)->value())){
      impl_pointer tmp=first1->next();
      impl_type::relink(first0,first1);
      first1=tmp;
    }
    else first0=first0->next();
  }
  impl_type::relink(last0,first1,last1);
}


template<typename Node,typename Compare>
void sequenced_index_sort(Node* header,Compare comp)
{
  /* Musser's mergesort, see http://www.cs.rpi.edu/~musser/gp/List/lists1.html.
   * The implementation is a little convoluted: in the original code
   * counter elements and carry are std::lists: here we do not want
   * to use multi_index instead, so we do things at a lower level, managing
   * directly the internal node representation.
   * Incidentally, the implementations I've seen of this algorithm (SGI,
   * Dinkumware, STLPort) are not exception-safe: this is. Moreover, we do not
   * use any dynamic storage.
   */

  if(header->next()==header->impl()||
     header->next()->next()==header->impl())return;

  typedef typename Node::impl_type      impl_type;
  typedef typename Node::impl_pointer   impl_pointer;

  typedef typename aligned_storage<
    sizeof(impl_type),
    alignment_of<impl_type>::value
  >::type                               carry_spc_type;
  carry_spc_type                        carry_spc;
  impl_type&                            carry=
    *static_cast<impl_type*>(static_cast<void*>(&carry_spc));
  typedef typename aligned_storage<
    sizeof(
      impl_type
        [sequenced_index_sort_max_fill]),
    alignment_of<
      impl_type
        [sequenced_index_sort_max_fill]
    >::value
  >::type                               counter_spc_type;
  counter_spc_type                      counter_spc;
  impl_type*                            counter=
    static_cast<impl_type*>(static_cast<void*>(&counter_spc));
  std::size_t                           fill=0;

  carry.prior()=carry.next()=static_cast<impl_pointer>(&carry);
  counter[0].prior()=counter[0].next()=static_cast<impl_pointer>(&counter[0]);

  BOOST_TRY{
    while(header->next()!=header->impl()){
      impl_type::relink(carry.next(),header->next());
      std::size_t i=0;
      while(i<fill&&counter[i].next()!=static_cast<impl_pointer>(&counter[i])){
        sequenced_index_collate<Node>(&carry,&counter[i++],comp);
      }
      impl_type::swap(
        static_cast<impl_pointer>(&carry),
        static_cast<impl_pointer>(&counter[i]));
      if(i==fill){
        ++fill;
        counter[fill].prior()=counter[fill].next()=
          static_cast<impl_pointer>(&counter[fill]);
      }
    }

    for(std::size_t i=1;i<fill;++i){
      sequenced_index_collate<Node>(&counter[i],&counter[i-1],comp);
    }
    impl_type::swap(
      header->impl(),static_cast<impl_pointer>(&counter[fill-1]));
  }
  BOOST_CATCH(...)
  {
    impl_type::relink(
      header->impl(),carry.next(),static_cast<impl_pointer>(&carry));
    for(std::size_t i=0;i<=fill;++i){
      impl_type::relink(
        header->impl(),counter[i].next(),
        static_cast<impl_pointer>(&counter[i]));
    }
    BOOST_RETHROW;
  }
  BOOST_CATCH_END
}

  inline static std::size_t next_prime(std::size_t n)
  {
    static const std::size_t prime_list[]={
      53ul, 97ul, 193ul, 389ul, 769ul,
      1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
      49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
      1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
      50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
      1610612741ul, 3221225473ul,

#if ((((ULONG_MAX>>16)>>16)>>16)>>15)==0 /* unsigned long less than 64 bits */
      4294967291ul
#else
      /* obtained with aid from
       *   http://javaboutique.internet.com/prime_numb/
       *   http://www.rsok.com/~jrm/next_ten_primes.html
       * and verified with
       *   http://www.alpertron.com.ar/ECM.HTM
       */

      6442450939ul, 12884901893ul, 25769803751ul, 51539607551ul,
      103079215111ul, 206158430209ul, 412316860441ul, 824633720831ul,
      1649267441651ul, 3298534883309ul, 6597069766657ul, 13194139533299ul,
      26388279066623ul, 52776558133303ul, 105553116266489ul, 211106232532969ul,
      422212465066001ul, 844424930131963ul, 1688849860263953ul,
      3377699720527861ul, 6755399441055731ul, 13510798882111483ul,
      27021597764222939ul, 54043195528445957ul, 108086391056891903ul,
      216172782113783843ul, 432345564227567621ul, 864691128455135207ul,
      1729382256910270481ul, 3458764513820540933ul, 6917529027641081903ul,
      13835058055282163729ul, 18446744073709551557ul
#endif

    };
    static const std::size_t prime_list_size=
      sizeof(prime_list)/sizeof(prime_list[0]);

    std::size_t const *bound=
      std::lower_bound(prime_list,prime_list+prime_list_size,n);
    if(bound==prime_list+prime_list_size)bound--;
    return *bound;
  }


  bucket_array(const Allocator& al,pointer end_,std::size_t size):
    size_(bucket_array_base::next_prime(size)),
    spc(al,size_+1)
  {
    clear();
    end()->next()=end_;
    end_->next()=end();
  }


  std::size_t size()const
  {
    return size_;
  }


  std::size_t position(std::size_t hash)const
  {
    return hash%size_;
  }


  pointer begin()const{return buckets();}

  pointer end()const{return buckets()+size_;}

  pointer at(std::size_t n)const{return buckets()+n;}


  std::size_t first_nonempty(std::size_t n)const
  {
    for(;;++n){
      pointer x=at(n);
      if(x->next()!=x)return n;
    }
  }


  void clear()
  {
    for(pointer x=begin(),y=end();x!=y;++x)x->next()=x;
  }


  void swap(bucket_array& x)
  {
    std::swap(size_,x.size_);
    spc.swap(x.spc);
  }


  pointer buckets()const
  {
    return spc.data();
  }


  template<class Archive>
  void serialize(Archive&,const unsigned int)
  {
  }


template<typename Allocator>
void swap(bucket_array<Allocator>& x,bucket_array<Allocator>& y)
{
  x.swap(y);
}


template<class Archive,typename Allocator>
inline void load_construct_data(
  Archive&,boost::multi_index::detail::bucket_array<Allocator>*,
  const unsigned int)
{
  throw_exception(
    archive::archive_exception(archive::archive_exception::other_exception));
}


  duplicates_iterator(Node* node_,Node* end_,Predicate pred_):
    node(node_),begin_chunk(0),end(end_),pred(pred_)
  {
    advance();
  }


  duplicates_iterator(Node* end_,Predicate pred_):
    node(end_),begin_chunk(end_),end(end_),pred(pred_)
  {
  }


  reference operator*()const
  {
    return node->value();
  }


  pointer operator->()const
  {
    return &node->value();
  }


  duplicates_iterator& operator++()
  {
    Node::increment(node);
    sync();
    return *this;
  }


  duplicates_iterator operator++(int)
  {
    duplicates_iterator tmp(*this);
    ++(*this);
    return tmp;
  }


  Node* get_node()const{return node;}

  void sync()
  {
    if(node!=end&&pred(begin_chunk->value(),node->value()))advance();
  }


  void advance()
  {
    for(Node* node2=node;node!=end;node=node2){
      Node::increment(node2);
      if(node2!=end&&!pred(node->value(),node2->value()))break;
    }
    begin_chunk=node;
  }


template<typename Node,typename Predicate>
bool operator==(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return x.get_node()==y.get_node();
}


template<typename Node,typename Predicate>
bool operator!=(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return !(x==y);
}

  bidir_node_iterator(){}

  explicit bidir_node_iterator(Node* node_):node(node_){}


  const typename Node::value_type& operator*()const
  {
    return node->value();
  }


  bidir_node_iterator& operator++()
  {
    Node::increment(node);
    return *this;
  }


  bidir_node_iterator& operator--()
  {
    Node::decrement(node);
    return *this;
  }


  template<class Archive>
  void save(Archive& ar,const unsigned int)const
  {
    node_base_type* bnode=node;
    ar<<serialization::make_nvp("pointer",bnode);
  }


  template<class Archive>
  void load(Archive& ar,const unsigned int)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
  }


  Node* get_node()const{return node;}


template<typename Node>
bool operator==(
  const bidir_node_iterator<Node>& x,
  const bidir_node_iterator<Node>& y)
{
  return x.get_node()==y.get_node();
}


  modify_key_adaptor(Fun f_,KeyFromValue kfv_):f(f_),kfv(kfv_){}


  void operator()(Value& x)
  {
    f(kfv(x));
  }

  index_loader(const Allocator& al,std::size_t size):
    spc(al,size),size_(size),n(0),sorted(false)
  {
  }


  template<class Archive>
  void add(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
    entries()[n++]=node;
  }


  template<class Archive>
  void add_track(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
  }


  template<typename Rearranger,class Archive>
  void load(Rearranger r,Archive& ar,const unsigned int)const
  {
    FinalNode* prev=unchecked_load_node(ar);
    if(!prev)return;

    if(!sorted){
      std::sort(entries(),entries()+size_);
      sorted=true;
    }

    check_node(prev);

    for(;;){
      for(;;){
        FinalNode* node=load_node(ar);
        if(!node)break;

        if(node==prev)prev=0;
        r(prev,node);

        prev=node;
      }
      prev=load_node(ar);
      if(!prev)break;
    }
  }

  Node** entries()const{return &*spc.data();}


  template<class Archive>
  FinalNode* unchecked_load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    return static_cast<FinalNode*>(node);
  }


  template<class Archive>
  FinalNode* load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    check_node(node);
    return static_cast<FinalNode*>(node);
  }


  void check_node(Node* node)const
  {
    if(node!=0&&!std::binary_search(entries(),entries()+size_,node)){
      throw_exception(
        archive::archive_exception(
          archive::archive_exception::other_exception));
    }
  }


template<typename Node,typename Allocator,typename Compare>
void random_access_index_inplace_merge(
  const Allocator& al,
  random_access_index_ptr_array<Allocator>& ptrs,
  BOOST_DEDUCED_TYPENAME Node::impl_ptr_pointer first1,Compare comp
  BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Node))
{
  typedef typename Node::value_type       value_type;
  typedef typename Node::impl_pointer     impl_pointer;
  typedef typename Node::impl_ptr_pointer impl_ptr_pointer;

  auto_space<impl_pointer,Allocator> spc(al,ptrs.size());

  impl_ptr_pointer first0=ptrs.begin(),
                   last0=first1,
                   last1=ptrs.end(),
                   out=spc.data();
  while(first0!=last0&&first1!=last1){
    if(comp(
        const_cast<const value_type&>(Node::from_impl(*first1)->value()),
        const_cast<const value_type&>(Node::from_impl(*first0)->value()))){
      *out++=*first1++;
    }
    else{
      *out++=*first0++;
    }
  }
  std::copy(&*first0,&*last0,&*out);
  std::copy(&*first1,&*last1,&*out);

  first1=ptrs.begin();
  out=spc.data();
  while(first1!=last1){
    *first1=*out++;
    (*first1)->up()=first1;
    ++first1;
  }
}

  random_access_index_sort_compare(Compare comp_=Compare()):comp(comp_){}


  bool operator()(
    typename Node::impl_pointer x,typename Node::impl_pointer y)const
  {
    typedef typename Node::value_type value_type;

    return comp(
      const_cast<const value_type&>(Node::from_impl(x)->value()),
      const_cast<const value_type&>(Node::from_impl(y)->value()));
  }


template<typename Node,typename Allocator,class Compare>
void random_access_index_sort(
  const Allocator& al,
  random_access_index_ptr_array<Allocator>& ptrs,
  Compare comp
  BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Node))
{
  /* The implementation is extremely simple: an auxiliary
   * array of pointers is sorted using stdlib facilities and
   * then used to rearrange the index. This is suboptimal
   * in space and time, but has some advantages over other
   * possible approaches:
   *   - Use std::stable_sort() directly on ptrs using some
   *     special iterator in charge of maintaining pointers
   *     and up() pointers in sync: we cannot guarantee
   *     preservation of the container invariants in the face of
   *     exceptions, if, for instance, std::stable_sort throws
   *     when ptrs transitorily contains duplicate elements.
   *   - Rewrite the internal algorithms of std::stable_sort
   *     adapted for this case: besides being a fair amount of
   *     work, making a stable sort compatible with Boost.MultiIndex
   *     invariants (basically, no duplicates or missing elements
   *     even if an exception is thrown) is complicated, error-prone
   *     and possibly won't perform much better than the
   *     solution adopted.
   */

  if(ptrs.size()<=1)return;

  typedef typename Node::value_type         value_type;
  typedef typename Node::impl_pointer       impl_pointer;
  typedef typename Node::impl_ptr_pointer   impl_ptr_pointer;
  typedef random_access_index_sort_compare<
    Node,Compare>                           ptr_compare;
  
  impl_ptr_pointer   first=ptrs.begin();
  impl_ptr_pointer   last=ptrs.end();
  auto_space<
    impl_pointer,
    Allocator>       spc(al,ptrs.size());
  impl_ptr_pointer   buf=spc.data();

  std::copy(&*first,&*last,&*buf);
  std::stable_sort(&*buf,&*buf+ptrs.size(),ptr_compare(comp));

  while(first!=last){
    *first=*buf++;
    (*first)->up()=first;
    ++first;
  }
}


  ordered_index_color& color(){return color_;}

  ordered_index_color  color()const{return color_;}

  pointer&             parent(){return parent_;}

  pointer&             left(){return left_;}

  pointer&             right(){return right_;}

    color_ref(uintptr_type* r_):r(r_){}

    
    operator ordered_index_color()const
    {
      return ordered_index_color(*r&uintptr_type(1));
    }

    
    color_ref& operator=(ordered_index_color c)
    {
      *r&=~uintptr_type(1);
      *r|=uintptr_type(c);
      return *this;
    }

    
    color_ref& operator=(const color_ref& x)
    {
      return operator=(x.operator ordered_index_color());
    }

    parent_ref(uintptr_type* r_):r(r_){}

    
    operator pointer()const
    {
      return (pointer)(void*)(*r&~uintptr_type(1));
    }

    
    parent_ref& operator=(pointer p)
    {
      *r=((uintptr_type)(void*)p)|(*r&uintptr_type(1));
      return *this;
    }

    
    parent_ref& operator=(const parent_ref& x)
    {
      return operator=(x.operator pointer());
    }


    pointer operator->()const
    {
      return operator pointer();
    }

  
  color_ref           color(){return color_ref(&parentcolor_);}

  ordered_index_color color()const
  {
    return ordered_index_color(parentcolor_&std::size_t(1ul));
  }


  parent_ref parent(){return parent_ref(&parentcolor_);}

  pointer    parent()const
  {
    return (pointer)(void*)(parentcolor_&~uintptr_type(1));
  }


  pointer& left(){return left_;}

  pointer  left()const{return left_;}

  pointer& right(){return right_;}

  pointer  right()const{return right_;}


  static void increment(pointer& x)
  {
    if(x->right()!=pointer(0)){
      x=x->right();
      while(x->left()!=pointer(0))x=x->left();
    }
    else{
      pointer y=x->parent();
      while(x==y->right()){
        x=y;
        y=y->parent();
      }
      if(x->right()!=y)x=y;
    }
  }


  static void decrement(pointer& x)
  {
    if(x->color()==red&&x->parent()->parent()==x){
      x=x->right();
    }
    else if(x->left()!=pointer(0)){
      pointer y=x->left();
      while(y->right()!=pointer(0))y=y->right();
      x=y;
    }else{
      pointer y=x->parent();
      while(x==y->left()){
        x=y;
        y=y->parent();
      }
      x=y;
    }
  }


  static void rotate_left(pointer x,parent_ref root)
  {
    pointer y=x->right();
    x->right()=y->left();
    if(y->left()!=pointer(0))y->left()->parent()=x;
    y->parent()=x->parent();
    
    if(x==root)                    root=y;
    else if(x==x->parent()->left())x->parent()->left()=y;
    else                           x->parent()->right()=y;
    y->left()=x;
    x->parent()=y;
  }


  static pointer minimum(pointer x)
  {
    while(x->left()!=pointer(0))x=x->left();
    return x;
  }


  static pointer maximum(pointer x)
  {
    while(x->right()!=pointer(0))x=x->right();
    return x;
  }


  static void rotate_right(pointer x,parent_ref root)
  {
    pointer y=x->left();
    x->left()=y->right();
    if(y->right()!=pointer(0))y->right()->parent()=x;
    y->parent()=x->parent();

    if(x==root)                     root=y;
    else if(x==x->parent()->right())x->parent()->right()=y;
    else                            x->parent()->left()=y;
    y->right()=x;
    x->parent()=y;
  }


  static void rebalance(pointer x,parent_ref root)
  {
    x->color()=red;
    while(x!=root&&x->parent()->color()==red){
      if(x->parent()==x->parent()->parent()->left()){
        pointer y=x->parent()->parent()->right();
        if(y!=pointer(0)&&y->color()==red){
          x->parent()->color()=black;
          y->color()=black;
          x->parent()->parent()->color()=red;
          x=x->parent()->parent();
        }
        else{
          if(x==x->parent()->right()){
            x=x->parent();
            rotate_left(x,root);
          }
          x->parent()->color()=black;
          x->parent()->parent()->color()=red;
          rotate_right(x->parent()->parent(),root);
        }
      }
      else{
        pointer y=x->parent()->parent()->left();
        if(y!=pointer(0)&&y->color()==red){
          x->parent()->color()=black;
          y->color()=black;
          x->parent()->parent()->color()=red;
          x=x->parent()->parent();
        }
        else{
          if(x==x->parent()->left()){
            x=x->parent();
            rotate_right(x,root);
          }
          x->parent()->color()=black;
          x->parent()->parent()->color()=red;
          rotate_left(x->parent()->parent(),root);
        }
      }
    }
    root->color()=black;
  }


  static void link(
    pointer x,ordered_index_side side,pointer position,pointer header)
  {
    if(side==to_left){
      position->left()=x;  /* also makes leftmost=x when parent==header */
      if(position==header){
        header->parent()=x;
        header->right()=x;
      }
      else if(position==header->left()){
        header->left()=x;  /* maintain leftmost pointing to min node */
      }
    }
    else{
      position->right()=x;
      if(position==header->right()){
        header->right()=x; /* maintain rightmost pointing to max node */
      }
    }
    x->parent()=position;
    x->left()=pointer(0);
    x->right()=pointer(0);
    ordered_index_node_impl::rebalance(x,header->parent());
  }


  static pointer rebalance_for_erase(
    pointer z,parent_ref root,pointer& leftmost,pointer& rightmost)
  {
    pointer y=z;
    pointer x=pointer(0);
    pointer x_parent=pointer(0);
    if(y->left()==pointer(0)){    /* z has at most one non-null child. y==z. */
      x=y->right();               /* x might be null */
    }
    else{
      if(y->right()==pointer(0)){ /* z has exactly one non-null child. y==z. */
        x=y->left();              /* x is not null */
      }
      else{                       /* z has two non-null children.  Set y to */
        y=y->right();             /* z's successor. x might be null.        */
        while(y->left()!=pointer(0))y=y->left();
        x=y->right();
      }
    }
    if(y!=z){
      z->left()->parent()=y;   /* relink y in place of z. y is z's successor */
      y->left()=z->left();
      if(y!=z->right()){
        x_parent=y->parent();
        if(x!=pointer(0))x->parent()=y->parent();
        y->parent()->left()=x; /* y must be a child of left */
        y->right()=z->right();
        z->right()->parent()=y;
      }
      else{
        x_parent=y;
      }

      if(root==z)                    root=y;
      else if(z->parent()->left()==z)z->parent()->left()=y;
      else                           z->parent()->right()=y;
      y->parent()=z->parent();
      ordered_index_color c=y->color();
      y->color()=z->color();
      z->color()=c;
      y=z;                    /* y now points to node to be actually deleted */
    }
    else{                     /* y==z */
      x_parent=y->parent();
      if(x!=pointer(0))x->parent()=y->parent();   
      if(root==z){
        root=x;
      }
      else{
        if(z->parent()->left()==z)z->parent()->left()=x;
        else                      z->parent()->right()=x;
      }
      if(leftmost==z){
        if(z->right()==pointer(0)){ /* z->left() must be null also */
          leftmost=z->parent();
        }
        else{              
          leftmost=minimum(x);      /* makes leftmost==header if z==root */
        }
      }
      if(rightmost==z){
        if(z->left()==pointer(0)){  /* z->right() must be null also */
          rightmost=z->parent();
        }
        else{                   /* x==z->left() */
          rightmost=maximum(x); /* makes rightmost==header if z==root */
        }
      }
    }
    if(y->color()!=red){
      while(x!=root&&(x==pointer(0)|| x->color()==black)){
        if(x==x_parent->left()){
          pointer w=x_parent->right();
          if(w->color()==red){
            w->color()=black;
            x_parent->color()=red;
            rotate_left(x_parent,root);
            w=x_parent->right();
          }
          if((w->left()==pointer(0)||w->left()->color()==black) &&
             (w->right()==pointer(0)||w->right()->color()==black)){
            w->color()=red;
            x=x_parent;
            x_parent=x_parent->parent();
          } 
          else{
            if(w->right()==pointer(0 )
                || w->right()->color()==black){
              if(w->left()!=pointer(0)) w->left()->color()=black;
              w->color()=red;
              rotate_right(w,root);
              w=x_parent->right();
            }
            w->color()=x_parent->color();
            x_parent->color()=black;
            if(w->right()!=pointer(0))w->right()->color()=black;
            rotate_left(x_parent,root);
            break;
          }
        } 
        else{                   /* same as above,with right <-> left */
          pointer w=x_parent->left();
          if(w->color()==red){
            w->color()=black;
            x_parent->color()=red;
            rotate_right(x_parent,root);
            w=x_parent->left();
          }
          if((w->right()==pointer(0)||w->right()->color()==black) &&
             (w->left()==pointer(0)||w->left()->color()==black)){
            w->color()=red;
            x=x_parent;
            x_parent=x_parent->parent();
          }
          else{
            if(w->left()==pointer(0)||w->left()->color()==black){
              if(w->right()!=pointer(0))w->right()->color()=black;
              w->color()=red;
              rotate_left(w,root);
              w=x_parent->left();
            }
            w->color()=x_parent->color();
            x_parent->color()=black;
            if(w->left()!=pointer(0))w->left()->color()=black;
            rotate_right(x_parent,root);
            break;
          }
        }
      }
      if(x!=pointer(0))x->color()=black;
    }
    return y;
  }


  static void restore(pointer x,pointer position,pointer header)
  {
    if(position->left()==pointer(0)||position->left()==header){
      link(x,to_left,position,header);
    }
    else{
      decrement(position);
      link(x,to_right,position,header);
    }
  }


  impl_color_ref      color(){return trampoline::color();}

  ordered_index_color color()const{return trampoline::color();}

  impl_parent_ref     parent(){return trampoline::parent();}

  impl_pointer        parent()const{return trampoline::parent();}

  impl_pointer&       left(){return trampoline::left();}

  impl_pointer        left()const{return trampoline::left();}

  impl_pointer&       right(){return trampoline::right();}

  impl_pointer        right()const{return trampoline::right();}


  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }


  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }


  static ordered_index_node* from_impl(impl_pointer x)
  {
    return static_cast<ordered_index_node*>(
      static_cast<trampoline*>(&*x));
  }


  static const ordered_index_node* from_impl(const_impl_pointer x)
  {
    return static_cast<const ordered_index_node*>(
      static_cast<const trampoline*>(&*x));
  }


  static void increment(ordered_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }


  static void decrement(ordered_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }


  pointer& next(){return next_;}


  static void increment(pointer& x,pointer bbegin,pointer bend)
  {
    std::less_equal<pointer> leq;

    x=x->next();
    if(leq(bbegin,x)&&leq(x,bend)){ /* bucket node */
      do{
        ++x;
      }while(x->next()==x);
      x=x->next();
    }
  }


  static void link(pointer x,pointer pos)
  {
    x->next()=pos->next();
    pos->next()=x;
  };


  static void unlink(pointer x)
  {
    pointer y=x->next();
    while(y->next()!=x){y=y->next();}
    y->next()=x->next();
  }


  static pointer prev(pointer x)
  {
    pointer y=x->next();
    while(y->next()!=x){y=y->next();}
    return y;
  }


  static void unlink_next(pointer x)
  {
    x->next()=x->next()->next();
  }


  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }


  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }


  static hashed_index_node* from_impl(impl_pointer x)
  {
    return static_cast<hashed_index_node*>(
      static_cast<trampoline*>(&*x));
  }


  static const hashed_index_node* from_impl(const_impl_pointer x)
  {
    return static_cast<const hashed_index_node*>(
      static_cast<const trampoline*>(&*x));
  }


  static void increment(
    hashed_index_node*& x,impl_pointer bbegin,impl_pointer bend)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi,bbegin,bend);
    x=from_impl(xi);
  }

  hashed_index_iterator(){}

  hashed_index_iterator(Node* node_,BucketArray* buckets_):
    node(node_),buckets(buckets_)
  {}


  const typename Node::value_type& operator*()const
  {
    return node->value();
  }


  hashed_index_iterator& operator++()
  {
    Node::increment(node,buckets->begin(),buckets->end());
    return *this;
  }


  template<class Archive>
  void save(Archive& ar,const unsigned int)const
  {
    node_base_type* bnode=node;
    ar<<serialization::make_nvp("pointer",bnode);
    ar<<serialization::make_nvp("pointer",buckets);
  }


  template<class Archive>
  void load(Archive& ar,const unsigned int)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
    ar>>serialization::make_nvp("pointer",buckets);
  }


  Node* get_node()const{return node;}


template<typename Node,typename BucketArray>
bool operator==(
  const hashed_index_iterator<Node,BucketArray>& x,
  const hashed_index_iterator<Node,BucketArray>& y)
{
  return x.get_node()==y.get_node();
}

  serialization_version():
    value(boost::serialization::version<serialization_version>::value){}


  serialization_version& operator=(unsigned int x){value=x;return *this;};


  operator unsigned int()const{return value;}


  ptr_pointer& up(){return up_;}


  static void increment(pointer& x)
  {
    x=*(x->up()+1);
  }


  static void decrement(pointer& x)
  {
    x=*(x->up()-1);
  }


  static void advance(pointer& x,std::ptrdiff_t n)
  {
    x=*(x->up()+n);
  }


  static std::ptrdiff_t distance(pointer x,pointer y)
  {
    return y->up()-x->up();
  }


  static void relocate(ptr_pointer pos,ptr_pointer x)
  {
    pointer n=*x;
    if(x<pos){
      extract(x,pos);
      *(pos-1)=n;
      n->up()=pos-1;
    }
    else{
      while(x!=pos){
        *x=*(x-1);
        (*x)->up()=x;
        --x;
      }
      *pos=n;
      n->up()=pos;
    }
  };


  static void extract(ptr_pointer x,ptr_pointer pend)
  {
    --pend;
    while(x!=pend){
      *x=*(x+1);
      (*x)->up()=x;
      ++x;
    }
  }


  static void transfer(
    ptr_pointer pbegin0,ptr_pointer pend0,ptr_pointer pbegin1)
  {
    while(pbegin0!=pend0){
      *pbegin1=*pbegin0++;
      (*pbegin1)->up()=pbegin1;
      ++pbegin1;
    }
  }


  static void reverse(ptr_pointer pbegin,ptr_pointer pend)
  {
    std::ptrdiff_t d=(pend-pbegin)/2;
    for(std::ptrdiff_t i=0;i<d;++i){
      std::swap(*pbegin,*--pend);
      (*pbegin)->up()=pbegin;
      (*pend)->up()=pend;
      ++pbegin;
    }
  }


  impl_ptr_pointer& up(){return trampoline::up();}

  impl_ptr_pointer  up()const{return trampoline::up();}


  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }


  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }


  static random_access_index_node* from_impl(impl_pointer x)
  {
    return static_cast<random_access_index_node*>(
      static_cast<trampoline*>(&*x));
  }


  static const random_access_index_node* from_impl(const_impl_pointer x)
  {
    return static_cast<const random_access_index_node*>(
      static_cast<const trampoline*>(&*x));
  }


  static void increment(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }


  static void decrement(random_access_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }


  static void advance(random_access_index_node*& x,std::ptrdiff_t n)
  {
    impl_pointer xi=x->impl();
    trampoline::advance(xi,n);
    x=from_impl(xi);
  }


  static std::ptrdiff_t distance(
    random_access_index_node* x,random_access_index_node* y)
  {
    return trampoline::distance(x->impl(),y->impl());
  }

  template<class Archive>
  archive_constructed(Archive& ar,const unsigned int version)
  {
    serialization::load_construct_data_adl(ar,&get(),version);
    BOOST_TRY{
      ar>>get();
    }
    BOOST_CATCH(...){
      (&get())->~T();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }


  template<class Archive>
  archive_constructed(const char* name,Archive& ar,const unsigned int version)
  {
    serialization::load_construct_data_adl(ar,&get(),version);
    BOOST_TRY{
      ar>>serialization::make_nvp(name,get());
    }
    BOOST_CATCH(...){
      (&get())->~T();
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
  }


  ~archive_constructed()
  {
    (&get())->~T();
  }


  T& get(){return *static_cast<T*>(static_cast<void*>(&space));}

  template<class Class>
    static typename Class::reference dereference(const Class& x)
  {
    return x.dereference();
  }


  template<class Class>
  static bool equal(const Class& x,const Class& y)
  {
    return x.equal(y);
  }


  template<class Class>
  static void increment(Class& x)
  {
    x.increment();
  }


  template<class Class>
  static void decrement(Class& x)
  {
    x.decrement();
  }


  template<class Class>
  static void advance(Class& x,typename Class::difference_type n)
  {
    x.advance(n);
  }


  template<class Class>
  static typename Class::difference_type distance_to(
    const Class& x,const Class& y)
  {
    return x.distance_to(y);
  }


  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }


  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }

  Derived& final(){return *static_cast<Derived*>(this);}

  const Derived& final()const{return *static_cast<const Derived*>(this);}


template<class Derived,class Base>
bool operator==(
  const forward_iter_adaptor_base<Derived,Base>& x,
  const forward_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}


  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }


  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }


  Derived& operator--()
  {
    iter_adaptor_access::decrement(final());
    return final();
  }

  Derived& final(){return *static_cast<Derived*>(this);}

  const Derived& final()const{return *static_cast<const Derived*>(this);}


template<class Derived,class Base>
bool operator==(
  const bidirectional_iter_adaptor_base<Derived,Base>& x,
  const bidirectional_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}


  reference operator*()const
  {
    return iter_adaptor_access::dereference(final());
  }


  Derived& operator++()
  {
    iter_adaptor_access::increment(final());
    return final();
  }


  Derived& operator--()
  {
    iter_adaptor_access::decrement(final());
    return final();
  }


  Derived& operator+=(difference_type n)
  {
    iter_adaptor_access::advance(final(),n);
    return final();
  }


  Derived& operator-=(difference_type n)
  {
    iter_adaptor_access::advance(final(),-n);
    return final();
  }

  Derived& final(){return *static_cast<Derived*>(this);}

  const Derived& final()const{return *static_cast<const Derived*>(this);}


template<class Derived,class Base>
bool operator==(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::equal(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y));
}


template<class Derived,class Base>
bool operator<(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::distance_to(
    static_cast<const Derived&>(x),static_cast<const Derived&>(y))>0;
}


template<class Derived,class Base>
typename random_access_iter_adaptor_base<Derived,Base>::difference_type
operator-(
  const random_access_iter_adaptor_base<Derived,Base>& x,
  const random_access_iter_adaptor_base<Derived,Base>& y)
{
  return iter_adaptor_access::distance_to(
    static_cast<const Derived&>(y),static_cast<const Derived&>(x));
}

  iter_adaptor(){}

  explicit iter_adaptor(const Base& b_):b(b_){}


  const Base& base_reference()const{return b;}

  Base&       base_reference(){return b;}

  unbounded_helper(){}

  unbounded_helper(const unbounded_helper&){}


inline detail::unbounded_helper unbounded(detail::unbounded_helper)
{
  return detail::unbounded_helper();
}

  static const Index& index(const MultiIndexContainer& x){return x;}

  static Index&       index(MultiIndexContainer& x){return x;}


  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }


  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }


  pointer& prior(){return prior_;}

  pointer& next(){return next_;}


  static void increment(pointer& x){x=x->next();}

  static void decrement(pointer& x){x=x->prior();}


  static void link(pointer x,pointer header)
  {
    x->prior()=header->prior();
    x->next()=header;
    x->prior()->next()=x->next()->prior()=x;
  };


  static void unlink(pointer x)
  {
    x->prior()->next()=x->next();
    x->next()->prior()=x->prior();
  }


  static void relink(pointer position,pointer x)
  {
    unlink(x);
    x->prior()=position->prior();
    x->next()=position;
    x->prior()->next()=x->next()->prior()=x;
  }


  static void reverse(pointer header)
  {
    pointer x=header;
    do{
      pointer y=x->next();
      std::swap(x->prior(),x->next());
      x=y;
    }while(x!=header);
  }


  static void swap(pointer x,pointer y)
  {
    /* This swap function does not exchange the header nodes,
     * but rather their pointers. This is *not* used for implementing
     * sequenced_index::swap.
     */

    if(x->next()!=x){
      if(y->next()!=y){
        std::swap(x->next(),y->next());
        std::swap(x->prior(),y->prior());
        x->next()->prior()=x->prior()->next()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
      else{
        y->next()=x->next();
        y->prior()=x->prior();
        x->next()=x->prior()=x;
        y->next()->prior()=y->prior()->next()=y;
      }
    }
    else if(y->next()!=y){
      x->next()=y->next();
      x->prior()=y->prior();
      y->next()=y->prior()=y;
      x->next()->prior()=x->prior()->next()=x;
    }
  }


  impl_pointer& prior(){return trampoline::prior();}

  impl_pointer  prior()const{return trampoline::prior();}

  impl_pointer& next(){return trampoline::next();}

  impl_pointer  next()const{return trampoline::next();}


  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }


  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }


  static sequenced_index_node* from_impl(impl_pointer x)
  {
    return static_cast<sequenced_index_node*>(
      static_cast<trampoline*>(&*x));
  }


  static const sequenced_index_node* from_impl(const_impl_pointer x)
  {
    return static_cast<const sequenced_index_node*>(
      static_cast<const trampoline*>(&*x));
  }


  static void increment(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }


  static void decrement(sequenced_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }

  index_saver(const Allocator& al,std::size_t size):alg(al,size){}


  template<class Archive>
  void add(Node* node,Archive& ar,const unsigned int)
  {
    ar<<serialization::make_nvp("position",*node);
    alg.add(node);
  }


  template<class Archive>
  void add_track(Node* node,Archive& ar,const unsigned int)
  {
    ar<<serialization::make_nvp("position",*node);
  }


  template<typename IndexIterator,class Archive>
  void save(
    IndexIterator first,IndexIterator last,Archive& ar,
    const unsigned int)const
  {
    /* calculate ordered positions */

    alg.execute(first,last);

    /* Given a consecutive subsequence of displaced elements
     * x1,...,xn, the following information is serialized:
     *
     *   p0,p1,...,pn,0
     *
     * where pi is a pointer to xi and p0 is a pointer to the element
     * preceding x1. Crealy, from this information is possible to
     * restore the original order on loading time. If x1 is the first
     * element in the sequence, the following is serialized instead:
     *
     *   p1,p1,...,pn,0
     *
     * For each subsequence of n elements, n+2 pointers are serialized.
     * An optimization policy is applied: consider for instance the
     * sequence
     *
     *   a,B,c,D
     * 
     * where B and D are displaced, but c is in its correct position.
     * Applying the schema described above we would serialize 6 pointers:
     *
     *  p(a),p(B),0
     *  p(c),p(D),0
     * 
     * but this can be reduced to 5 pointers by treating c as a displaced
     * element:
     *
     *  p(a),p(B),p(c),p(D),0
     */

    std::size_t last_saved=3; /* distance to last pointer saved */
    for(IndexIterator it=first,prev=first;it!=last;prev=it++,++last_saved){
      if(!alg.is_ordered(get_node(it))){
        if(last_saved>1)save_node(get_node(prev),ar);
        save_node(get_node(it),ar);
        last_saved=0;
      }
      else if(last_saved==2)save_node(null_node(),ar);
    }
    if(last_saved<=2)save_node(null_node(),ar);

    /* marks the end of the serialization info for [first,last) */

    save_node(null_node(),ar);
  }

  template<typename IndexIterator>
  static Node* get_node(IndexIterator it)
  {
    return it.get_node();
  }


  static Node* null_node(){return 0;}


  template<typename Archive>
  static void save_node(Node* node,Archive& ar)
  {
    ar<<serialization::make_nvp("pointer",node);
  }

  value_comparison(
    const KeyFromValue& key_=KeyFromValue(),const Compare& comp_=Compare()):
    key(key_),comp(comp_)
  {
  }


  bool operator()(
    typename call_traits<Value>::param_type x,
    typename call_traits<Value>::param_type y)const
  {
    return comp(key(x),key(y));
  }


  value_type& value()
  {
    return *static_cast<value_type*>(
      static_cast<void*>(&this->space));
  }


  const value_type& value()const
  {
    return *static_cast<const value_type*>(
      static_cast<const void*>(&this->space));
  }


  static index_node_base* from_value(const value_type* p)
  {
    return static_cast<index_node_base *>(
      reinterpret_cast<pod_value_holder<Value>*>( /* std 9.2.17 */
        const_cast<value_type*>(p))); 
  }


  template<class Archive>
  void serialize(Archive&,const unsigned int)
  {
  }


template<typename Node,typename Value>
Node* node_from_value(
  const Value* p
  BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Node))
{
  typedef typename Node::allocator_type allocator_type;
  return static_cast<Node*>(
    index_node_base<Value,allocator_type>::from_value(p));
}


template<class Archive,typename Value,typename Allocator>
inline void load_construct_data(
  Archive&,boost::multi_index::detail::index_node_base<Value,Allocator>*,
  const unsigned int)
{
  throw_exception(
    archive::archive_exception(archive::archive_exception::other_exception));
}


  random_access_index_ptr_array(
    const Allocator& al,value_type end_,std::size_t size):
    size_(size),
    capacity_(size),
    spc(al,capacity_+1)
  {
    *end()=end_;
    end_->up()=end();
  }


  std::size_t size()const{return size_;}

  std::size_t capacity()const{return capacity_;}


  void room_for_one()
  {
    if(size_==capacity_){
      reserve(capacity_<=10?15:capacity_+capacity_/2);
    }
  }


  void reserve(std::size_t c)
  {
    if(c>capacity_){
      auto_space<value_type,Allocator> spc1(spc.get_allocator(),c+1);
      node_impl_type::transfer(begin(),end()+1,spc1.data());
      spc.swap(spc1);
      capacity_=c;
    }
  }


  pointer begin()const{return ptrs();}

  pointer end()const{return ptrs()+size_;}

  pointer at(std::size_t n)const{return ptrs()+n;}


  void push_back(value_type x)
  {
    *(end()+1)=*end();
    (*(end()+1))->up()=end()+1;
    *end()=x;
    (*end())->up()=end();
    ++size_;
  }


  void erase(value_type x)
  {
    node_impl_type::extract(x->up(),end()+1);
    --size_;
  }


  void clear()
  {
    *begin()=*end();
    (*begin())->up()=begin();
    size_=0;
  }


  void swap(random_access_index_ptr_array& x)
  {
    std::swap(size_,x.size_);
    std::swap(capacity_,x.capacity_);
    spc.swap(x.spc);
  }


  pointer ptrs()const
  {
    return spc.data();
  }


template<typename Allocator>
void swap(
  random_access_index_ptr_array<Allocator>& x,
  random_access_index_ptr_array<Allocator>& y)
{
  x.swap(y);
}


  random_access_index_loader_base(const Allocator& al_,ptr_array& ptrs_):
    al(al_),
    ptrs(ptrs_),
    header(*ptrs.end()),
    prev_spc(al,0),
    preprocessed(false)
  {}


  ~random_access_index_loader_base()
  {
    if(preprocessed)
    {
      node_impl_pointer n=header;
      next(n)=n;

      for(std::size_t i=ptrs.size();i--;){
        n=prev(n);
        std::size_t d=position(n);
        if(d!=i){
          node_impl_pointer m=prev(next_at(i));
          std::swap(m->up(),n->up());
          next_at(d)=next_at(i);
          std::swap(prev_at(d),prev_at(i));
        }
        next(n)=n;
      }
    }
  }


  void rearrange(node_impl_pointer position,node_impl_pointer x)
  {
    preprocess(); /* only incur this penalty if rearrange() is ever called */
    if(position==node_impl_pointer(0))position=header;
    next(prev(x))=next(x);
    prev(next(x))=prev(x);
    prev(x)=position;
    next(x)=next(position);
    next(prev(x))=prev(next(x))=x;
  }

  void preprocess()
  {
    if(!preprocessed){
      /* get space for the auxiliary prev array */
      auto_space<node_impl_pointer,Allocator> tmp(al,ptrs.size()+1);
      prev_spc.swap(tmp);

      /* prev_spc elements point to the prev nodes */
      std::rotate_copy(
        &*ptrs.begin(),&*ptrs.end(),&*ptrs.end()+1,&*prev_spc.data());

      /* ptrs elements point to the next nodes */
      std::rotate(&*ptrs.begin(),&*ptrs.begin()+1,&*ptrs.end()+1);

      preprocessed=true;
    }
  }


  std::size_t position(node_impl_pointer x)const
  {
    return (std::size_t)(x->up()-ptrs.begin());
  }


  node_impl_pointer& next_at(std::size_t n)const
  {
    return *ptrs.at(n);
  }


  node_impl_pointer& prev_at(std::size_t n)const
  {
    return *(prev_spc.data()+n);
  }


  node_impl_pointer& next(node_impl_pointer x)const
  {
    return *(x->up());
  }


  node_impl_pointer& prev(node_impl_pointer x)const
  {
    return prev_at(position(x));
  }

  random_access_index_loader(const Allocator& al_,ptr_array& ptrs_):
    super(al_,ptrs_)
  {}


  void rearrange(Node* position,Node *x)
  {
    super::rearrange(position?position->impl():node_impl_pointer(0),x->impl());
  }


template<typename T>
void adl_swap(T& x,T& y)
{

#if !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  using std::swap;
  swap(x,y);
#else
  std::swap(x,y);
#endif

}

  explicit index_base(const ctor_args_list&,const Allocator&){}


  void copy_(
    const index_base<Value,IndexSpecifierList,Allocator>&,const copy_map_type&)
  {}


  node_type* insert_(value_param_type v,node_type* x)
  {
    boost::detail::allocator::construct(&x->value(),v);
    return x;
  }


  void erase_(node_type* x)
  {
    boost::detail::allocator::destroy(&x->value());
  }


  void delete_node_(node_type* x)
  {
    boost::detail::allocator::destroy(&x->value());
  }


  void clear_(){}


  void swap_(index_base<Value,IndexSpecifierList,Allocator>&){}


  bool replace_(value_param_type v,node_type* x)
  {
    x->value()=v;
    return true;
  }


  bool modify_(node_type*){return true;}


  bool modify_rollback_(node_type*){return true;}


  template<typename Archive>
  void save_(Archive&,const unsigned int,const index_saver_type&)const{}


  template<typename Archive>
  void load_(Archive&,const unsigned int,const index_loader_type&){}


  final_type&       final(){return *static_cast<final_type*>(this);}


  final_node_type* final_header()const{return final().header();}


  bool        final_empty_()const{return final().empty_();}

  std::size_t final_size_()const{return final().size_();}

  std::size_t final_max_size_()const{return final().max_size_();}

  copy_map_entry(Node* f,Node* s):first(f),second(s){}


  bool operator<(const copy_map_entry<Node>& x)const
  {
    return std::less<Node*>()(first,x.first);
  }


  copy_map(
    const Allocator& al,std::size_t size,Node* header_org,Node* header_cpy):
    al_(al),size_(size),spc(al_,size_),n(0),
    header_org_(header_org),header_cpy_(header_cpy),released(false)
  {}


  ~copy_map()
  {
    if(!released){
      for(std::size_t i=0;i<n;++i){
        boost::detail::allocator::destroy(&(spc.data()+i)->second->value());
        deallocate((spc.data()+i)->second);
      }
    }
  }


  const_iterator begin()const{return &*spc.data();}

  const_iterator end()const{return &*(spc.data()+n);}


  void clone(Node* node)
  {
    (spc.data()+n)->first=node;
    (spc.data()+n)->second=&*al_.allocate(1);
    BOOST_TRY{
      boost::detail::allocator::construct(
        &(spc.data()+n)->second->value(),node->value());
    }
    BOOST_CATCH(...){
      deallocate((spc.data()+n)->second);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    ++n;

    if(n==size_)std::sort(&*spc.data(),&*spc.data()+size_);
  }


  Node* find(Node* node)const
  {
    if(node==header_org_)return header_cpy_;
    return std::lower_bound(
      begin(),end(),copy_map_entry<Node>(node,0))->second;
  }


  void release()
  {
    released=true;
  }


  void deallocate(Node* node)
  {
    al_.deallocate(static_cast<allocator_pointer>(node),1);
  }

  rnd_node_iterator(){}

  explicit rnd_node_iterator(Node* node_):node(node_){}


  const typename Node::value_type& operator*()const
  {
    return node->value();
  }


  rnd_node_iterator& operator++()
  {
    Node::increment(node);
    return *this;
  }


  rnd_node_iterator& operator--()
  {
    Node::decrement(node);
    return *this;
  }


  rnd_node_iterator& operator+=(std::ptrdiff_t n)
  {
    Node::advance(node,n);
    return *this;
  }


  rnd_node_iterator& operator-=(std::ptrdiff_t n)
  {
    Node::advance(node,-n);
    return *this;
  }


  template<class Archive>
  void save(Archive& ar,const unsigned int)const
  {
    node_base_type* bnode=node;
    ar<<serialization::make_nvp("pointer",bnode);
  }


  template<class Archive>
  void load(Archive& ar,const unsigned int)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
  }


  Node* get_node()const{return node;}


template<typename Node>
bool operator==(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return x.get_node()==y.get_node();
}


template<typename Node>
bool operator<(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(x.get_node(),y.get_node())>0;
}


template<typename Node>
std::ptrdiff_t operator-(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(y.get_node(),x.get_node());
}
