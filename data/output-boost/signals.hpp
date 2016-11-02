

        bool operator==(const bound_object& other) const
          { return obj == other.obj && data == other.data; }

        bool operator<(const bound_object& other) const
          { return obj < other.obj; }

        bool operator!=(const bound_object& other) const
        { return !(*this==other); }

        bool operator>(const bound_object& other) const
        { return !(*this < other); }


        connection_slot_pair() {}

        bool operator==(const connection_slot_pair&) const { return false; }

        bool operator<(const connection_slot_pair&) const { return false;}


        inline bool operator()(const argument_type& c) const
        {
          return !c.first.connected();
        }


        inline bool operator()(const argument_type& c) const
        {
          return c.first.connected() && !c.first.blocked() ;
        }

        auto_disconnect_bound_object(const bound_object& b) :
          binding(b), auto_disconnect(true)
        {
        }


        ~auto_disconnect_bound_object()
        {
          if (auto_disconnect)
            binding.disconnect(binding.obj, binding.data);
        }


        void release() { auto_disconnect = false; }

    template<typename F>
    slot(const F& f) : slot_function(BOOST_SIGNALS_NAMESPACE::get_invocable_slot(f, BOOST_SIGNALS_NAMESPACE::tag_type(f)))
    {
      this->data.reset(new data_t);

      // Visit each of the bound objects and store them for later use
      // An exception thrown here will allow the basic_connection to be
      // destroyed when this goes out of scope, and no other connections
      // have been made.
      BOOST_SIGNALS_NAMESPACE::detail::bound_objects_visitor 
        do_bind(this->data->bound_objects);
      visit_each(do_bind, 
                 BOOST_SIGNALS_NAMESPACE::get_inspectable_slot
                   (f, BOOST_SIGNALS_NAMESPACE::tag_type(f)));
      create_connection();
    }

    const SlotFunction& get_slot_function() const { return slot_function; }


    void release() const { data->watch_bound_objects.set_controlling(false); }

      bound_objects_visitor(std::vector<const trackable*>& v) :
        bound_objects(v)
      {
      }


      template<typename T>
      void operator()(const T& t) const
      {
        decode(t, 0);
      }

      template<typename T>
      void decode(const reference_wrapper<T>& t, int) const
      {
        add_if_trackable(t.get_pointer());
      }


      template<typename T>
      void decode(const T& t, long) const
      {
        typedef truth<(is_pointer<T>::value)> is_a_pointer;
        maybe_get_pointer(t, is_a_pointer());
      }

      template<typename T>
      void maybe_get_pointer(const T& t, truth<true>) const
      {
        add_if_trackable(t);
      }


      template<typename T>
      void maybe_get_pointer(const T& t, truth<false>) const
      {
        // Take the address of this object, because the object itself may be
        // trackable
        add_if_trackable(boost::addressof(t));
      }

      inline void add_if_trackable(const trackable* b) const
      {
        if (b) {
          bound_objects.push_back(b);
        }
      }


      inline void add_if_trackable(const void*) const { }


      template<typename R>
      inline void add_if_trackable(R (*)()) const { }


      template<typename R, typename T1>
      inline void add_if_trackable(R (*)(T1)) const { }


      template<typename R, typename T1, typename T2>
      inline void add_if_trackable(R (*)(T1, T2)) const { }


      template<typename R, typename T1, typename T2, typename T3>
      inline void add_if_trackable(R (*)(T1, T2, T3)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4>
      inline void add_if_trackable(R (*)(T1, T2, T3, T4)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5>
      inline void add_if_trackable(R (*)(T1, T2, T3, T4, T5)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6>
      inline void add_if_trackable(R (*)(T1, T2, T3, T4, T5, T6)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7>
      inline void add_if_trackable(R (*)(T1, T2, T3, T4, T5, T6, T7)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8>
      inline void 
      add_if_trackable(R (*)(T1, T2, T3, T4, T5, T6, T7, T8)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8, typename T9>
      inline void
      add_if_trackable(R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)) const { }


      template<typename R, typename T1, typename T2, typename T3, typename T4,
               typename T5, typename T6, typename T7, typename T8, typename T9,
               typename T10>
      inline void
      add_if_trackable(R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)) const { }

        unusable() {}


  stored_group(storage_kind p_kind = sk_empty) : kind(p_kind), group() { }


  template<typename T>
  stored_group(const T& p_group) : kind(sk_group), group(new T(p_group)) { }


  bool is_front() const { return kind == sk_front; }

  bool is_back() const { return kind == sk_back; }

  bool empty() const { return kind == sk_empty; }


  void* get() const { return group.get(); }


  group_bridge_compare(const Compare& c) : comp(c) 
  { }


  bool operator()(const stored_group& k1, const stored_group& k2) const
  {
    if (k1.is_front()) return !k2.is_front();
    if (k1.is_back()) return false;
    if (k2.is_front()) return false;
    if (k2.is_back()) return true;

    // Neither is empty, so compare their values to order them
    return comp(*static_cast<Key*>(k1.get()), *static_cast<Key*>(k2.get()));
  }

        slot_call_iterator(Iterator iter_in, Iterator end_in, Function func,
                           optional<result_type> &c)
          : iter(iter_in), end(end_in), f(func), cache(&c)
        {
          iter = std::find_if(iter, end, is_callable());
        }
