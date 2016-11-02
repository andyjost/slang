
  
  handle_type insert(const Entry& x)
  {
    return &*cont.insert(x).first;
  }


  void erase(handle_type h)
  {
    cont.erase(cont.iterator_to(*h));
  }


  static const Entry& entry(handle_type h){return *h;}


  static bool init(){return core::init();}

    initializer():b(init()){}

  
  flyweight():h(core::insert(key_type())){}

  flyweight(const flyweight& x):h(x.h){}

  flyweight(flyweight& x):h(x.h){}


  flyweight& operator=(const flyweight& x){h=x.h;return *this;}

  flyweight& operator=(const value_type& x){return operator=(flyweight(x));}

  
  const key_type&   get_key()const{return core::key(h);}

  const value_type& get()const{return core::value(h);}

  operator const    value_type&()const{return get();}


  void swap(flyweight& x){boost::swap(h,x.h);}


template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x.get()==y.get();
}


template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,
  const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x.get()<y.get();
}

template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator==(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y)
{
  return x.get()==y;
}


template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator==(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x==y.get();
}


template<
  typename T1,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(1),
  typename T2
>
bool operator<(
  const flyweight<T1,BOOST_FLYWEIGHT_TEMPL_ARGS(1)>& x,const T2& y)
{
  return x.get()<y;
}


template<
  typename T1,
  typename T2,BOOST_FLYWEIGHT_TYPENAME_TEMPL_ARGS(2)
>
bool operator<(
  const T1& x,const flyweight<T2,BOOST_FLYWEIGHT_TEMPL_ARGS(2)>& y)
{
  return x<y.get();
}

  
  handle_type insert(const entry_type& x)
  {
    return cont.insert(x).first;
  }


  void erase(handle_type h)
  {
    cont.erase(h);
  }


  static const entry_type& entry(handle_type h){return *h;}

  explicit refcounted_value(const Value& x_):
    x(x_),ref(0),del_ref(0)
  {}

  
  refcounted_value(const refcounted_value& r):
    x(r.x),ref(0),del_ref(0)
  {}


  refcounted_value& operator=(const refcounted_value& r)
  {
    x=r.x;
    return *this;
  }

  
  operator const Value&()const{return x;}

  operator const Key&()const{return x;}


  long count()const{return ref;}

  long add_ref()const{return ++ref;}

  bool release()const{return (--ref==0);}


  void add_deleter()const{++del_ref;}

  bool release_deleter()const{return (--del_ref==0);}

  explicit refcounted_handle(const Handle& h_):h(h_)
  {
    if(TrackingHelper::entry(*this).add_ref()==1){
      TrackingHelper::entry(*this).add_deleter();
    }
  }

  
  refcounted_handle(const refcounted_handle& x):h(x.h)
  {
    TrackingHelper::entry(*this).add_ref();
  }


  refcounted_handle& operator=(refcounted_handle x)
  {
    swap(*this,x);
    return *this;
  }


  ~refcounted_handle()
  {
    if(TrackingHelper::entry(*this).release()){
      TrackingHelper::erase(*this,check_erase);
    }
  }


  operator const Handle&()const{return h;}

  static bool check_erase(const refcounted_handle& x)
  {
    return TrackingHelper::entry(x).release_deleter();
  }


    rep_type(const value_type& x):value_ptr(&x){}


    rep_type(const rep_type& x):value_ptr(x.value_ptr)
    {
      if(!x.value_ptr)new(key_ptr())key_type(*x.key_ptr());
    }


    ~rep_type()
    {
      if(!value_ptr)       key_ptr()->~key_type();
      else if(value_cted())value_ptr->~value_type();
    }


    operator const key_type&()const
    {
      if(value_ptr)return key_from_value(*value_ptr);
      else         return *key_ptr();
    }


    operator const value_type&()const
    {
      /* This is always called after construct_value() or copy_value(),
       * so we access spc directly rather than through value_ptr to
       * save us an indirection.
       */

      return *static_cast<value_type*>(spc_ptr());
    }


    void* spc_ptr()const{return static_cast<void*>(&spc);}

    bool  value_cted()const{return value_ptr==spc_ptr();}


    key_type* key_ptr()const
    {
      return static_cast<key_type*>(static_cast<void*>(&spc));
    }


    static const key_type& key_from_value(const value_type& x)
    {
      KeyFromValue k;
      return k(x);
    }


    void construct_value()const
    {
      if(!value_cted()){
        /* value_ptr must be ==0, oherwise copy_value would have been called */

        key_type k(*key_ptr());
        key_ptr()->~key_type();
        value_ptr= /* guarantees key won't be re-dted at ~rep_type if the */
          static_cast<value_type*>(spc_ptr())+1; /* next statement throws */
        value_ptr=new(spc_ptr())value_type(k);
      }
    }


    void copy_value()const
    {
      if(!value_cted())value_ptr=new(spc_ptr())value_type(*value_ptr);
    }


  static void construct_value(const rep_type& r)
  {
    r.construct_value();
  }


  static void copy_value(const rep_type& r)
  {
    r.copy_value();
  }


    rep_type(const value_type& x):key(no_key_from_value_failure()){}


    rep_type(const rep_type& x):key(x.key),value_ptr(0){}


    ~rep_type()
    {
      if(value_ptr)value_ptr->~value_type();
    }


    operator const key_type&()const{return key;}


    operator const value_type&()const
    {
      /* This is always called after construct_value(),so we access spc
       * directly rather than through value_ptr to save us an indirection.
       */

      return *static_cast<value_type*>(spc_ptr());
    }


    void* spc_ptr()const{return static_cast<void*>(&spc);}


    void construct_value()const
    {
      if(!value_ptr)value_ptr=new(spc_ptr())value_type(key);
    }


  static void construct_value(const rep_type& r)
  {
    r.construct_value();
  }


  static void copy_value(const rep_type&){}

  static C& get()
  {
    static C c;
    return c;
  }


    operator const value_type&()const{return x;}


  static void construct_value(const rep_type&){}

  static void copy_value(const rep_type&){}

  static const entry_type& entry(const handle_type& h)
  {
    return core::entry(h);
  }


  template<typename Checker>
  static void erase(const handle_type& h,Checker check)
  {
    typedef typename core::lock_type lock_type;
    lock_type lock(core::mutex());
    if(check(h))core::factory().erase(h);
  }


  static bool init()
  {
    if(static_initializer)return true;
    else{
      holder_arg& a=holder_type::get();
      static_factory_ptr=&a.factory;
      static_mutex_ptr=&a.mutex;
      static_initializer=(static_factory_ptr!=0);
      return static_initializer;
    }
  }


  static handle_type insert(const value_type& x){return insert_value(x);}

  static handle_type insert(value_type& x){return insert_value(x);}


  static const entry_type& entry(const base_handle_type& h)
  {
    return factory().entry(h);
  }


  static const value_type& value(const handle_type& h)
  {
    return static_cast<const rep_type&>(entry(h));
  }


  static const key_type& key(const handle_type& h)
  {
    return static_cast<const rep_type&>(entry(h));
  }


  static factory_type& factory()
  {
    return *static_factory_ptr;
  }


  static mutex_type& mutex()
  {
    return *static_mutex_ptr;
  }


  static handle_type insert_rep(const rep_type& x)
  {
    init();
    entry_type       e(x);
    lock_type        lock(mutex());
    base_handle_type h(factory().insert(e));
    BOOST_TRY{
      ValuePolicy::construct_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }


  static handle_type insert_value(const value_type& x)
  {
    init();
    entry_type       e((rep_type(x)));
    lock_type        lock(mutex());
    base_handle_type h(factory().insert(e));
    BOOST_TRY{
      ValuePolicy::copy_value(
        static_cast<const rep_type&>(entry(h)));
    }
    BOOST_CATCH(...){
      factory().erase(h);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    return static_cast<handle_type>(h);
  }
