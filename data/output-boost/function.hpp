

  template<typename Signature>
  inline void swap(function<Signature>& f1, function<Signature>& f2)
  {
    f1.swap(f2);
  }

        unusable() {}

        template<typename T> unusable(const T&) {}

        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer, 
               functor_manager_operation_type op)
        {
          switch (op) {
          case clone_functor_tag: 
            out_buffer.obj_ref = in_buffer.obj_ref;
            return;

          case move_functor_tag:
            out_buffer.obj_ref = in_buffer.obj_ref;
            in_buffer.obj_ref.obj_ptr = 0;
            return;

          case destroy_functor_tag:
            out_buffer.obj_ref.obj_ptr = 0;
            return;

          case check_functor_type_tag:
            {
              const detail::sp_typeinfo& check_type 
                = *out_buffer.type.type;

              // Check whether we have the same type. We can add
              // cv-qualifiers, but we can't take them away.
              if (BOOST_FUNCTION_COMPARE_TYPE_ID(check_type, BOOST_SP_TYPEID(F))
                  && (!in_buffer.obj_ref.is_const_qualified 
                      || out_buffer.type.const_qualified)
                  && (!in_buffer.obj_ref.is_volatile_qualified
                      || out_buffer.type.volatile_qualified))
                out_buffer.obj_ptr = in_buffer.obj_ref.obj_ptr;
              else
                out_buffer.obj_ptr = 0;
            }
            return;

          case get_functor_type_tag:
            out_buffer.type.type = &BOOST_SP_TYPEID(F);
            out_buffer.type.const_qualified = in_buffer.obj_ref.is_const_qualified;
            out_buffer.type.volatile_qualified = in_buffer.obj_ref.is_volatile_qualified;
            return;
          }
        }

        functor_wrapper( F f, A a ):
          F(f),
          A(a)
        {
        }

        
        functor_wrapper(const functor_wrapper& f) :
          F(static_cast<const F&>(f)),
          A(static_cast<const A&>(f))
        {
        }

        static inline void
        manage_ptr(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op)
        {
          if (op == clone_functor_tag)
            out_buffer.func_ptr = in_buffer.func_ptr;
          else if (op == move_functor_tag) {
            out_buffer.func_ptr = in_buffer.func_ptr;
            in_buffer.func_ptr = 0;
          } else if (op == destroy_functor_tag)
            out_buffer.func_ptr = 0;
          else if (op == check_functor_type_tag) {
            const detail::sp_typeinfo& check_type 
              = *out_buffer.type.type;
            if (BOOST_FUNCTION_COMPARE_TYPE_ID(check_type, BOOST_SP_TYPEID(Functor)))
              out_buffer.obj_ptr = &in_buffer.func_ptr;
            else
              out_buffer.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.type.type = &BOOST_SP_TYPEID(Functor);
            out_buffer.type.const_qualified = false;
            out_buffer.type.volatile_qualified = false;
          }
        }

        static inline void
        manage_small(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op)
        {
          if (op == clone_functor_tag || op == move_functor_tag) {
            const functor_type* in_functor = 
              reinterpret_cast<const functor_type*>(&in_buffer.data);
            new (reinterpret_cast<void*>(&out_buffer.data)) functor_type(*in_functor);

            if (op == move_functor_tag) {
              functor_type* f = reinterpret_cast<functor_type*>(&in_buffer.data);
              (void)f; // suppress warning about the value of f not being used (MSVC)
              f->~Functor();
            }
          } else if (op == destroy_functor_tag) {
            // Some compilers (Borland, vc6, ...) are unhappy with ~functor_type.
             functor_type* f = reinterpret_cast<functor_type*>(&out_buffer.data);
             (void)f; // suppress warning about the value of f not being used (MSVC)
             f->~Functor();
          } else if (op == check_functor_type_tag) {
            const detail::sp_typeinfo& check_type 
              = *out_buffer.type.type;
            if (BOOST_FUNCTION_COMPARE_TYPE_ID(check_type, BOOST_SP_TYPEID(Functor)))
              out_buffer.obj_ptr = &in_buffer.data;
            else
              out_buffer.obj_ptr = 0;
          } else /* op == get_functor_type_tag */ {
            out_buffer.type.type = &BOOST_SP_TYPEID(Functor);
            out_buffer.type.const_qualified = false;
            out_buffer.type.volatile_qualified = false;            
          }
        }

        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op, function_ptr_tag)
        {
          functor_manager_common<Functor>::manage_ptr(in_buffer,out_buffer,op);
        }

        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op, function_obj_tag)
        {
          manager(in_buffer, out_buffer, op,
                  mpl::bool_<(function_allows_small_object_optimization<functor_type>::value)>());
        }

        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op, member_ptr_tag)
        {
          manager(in_buffer, out_buffer, op, mpl::true_());
        }

        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer, 
               functor_manager_operation_type op)
        {
          typedef typename get_function_tag<functor_type>::type tag_type;
          switch (op) {
          case get_functor_type_tag:
            out_buffer.type.type = &BOOST_SP_TYPEID(functor_type);
            out_buffer.type.const_qualified = false;
            out_buffer.type.volatile_qualified = false;
            return;

          default:
            manager(in_buffer, out_buffer, op, tag_type());
            return;
          }
        }

        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op, function_ptr_tag)
        {
          functor_manager_common<Functor>::manage_ptr(in_buffer,out_buffer,op);
        }

        static inline void
        manager(const function_buffer& in_buffer, function_buffer& out_buffer, 
                functor_manager_operation_type op, function_obj_tag)
        {
          manager(in_buffer, out_buffer, op,
                  mpl::bool_<(function_allows_small_object_optimization<functor_type>::value)>());
        }

        static inline void
        manage(const function_buffer& in_buffer, function_buffer& out_buffer, 
               functor_manager_operation_type op)
        {
          typedef typename get_function_tag<functor_type>::type tag_type;
          switch (op) {
          case get_functor_type_tag:
            out_buffer.type.type = &BOOST_SP_TYPEID(functor_type);
            out_buffer.type.const_qualified = false;
            out_buffer.type.volatile_qualified = false;
            return;

          default:
            manager(in_buffer, out_buffer, op, tag_type());
            return;
          }
        }

  function_base() : vtable(0) { }

  bool empty() const { return !vtable; }

  const detail::sp_typeinfo& target_type() const
  {
    if (!vtable) return BOOST_SP_TYPEID(void);

    detail::function::function_buffer type;
    get_vtable()->manager(functor, type, detail::function::get_functor_type_tag);
    return *type.type.type;
  }


  template<typename Functor>
    Functor* target()
    {
      if (!vtable) return 0;

      detail::function::function_buffer type_result;
      type_result.type.type = &BOOST_SP_TYPEID(Functor);
      type_result.type.const_qualified = is_const<Functor>::value;
      type_result.type.volatile_qualified = is_volatile<Functor>::value;
      get_vtable()->manager(functor, type_result, 
                      detail::function::check_functor_type_tag);
      return static_cast<Functor*>(type_result.obj_ptr);
    }


  template<typename Functor>
#if defined(BOOST_MSVC) && BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    const Functor* target( Functor * = 0 ) const
#else
    const Functor* target() const
#endif
    {
      if (!vtable) return 0;

      detail::function::function_buffer type_result;
      type_result.type.type = &BOOST_SP_TYPEID(Functor);
      type_result.type.const_qualified = true;
      type_result.type.volatile_qualified = is_volatile<Functor>::value;
      get_vtable()->manager(functor, type_result, 
                      detail::function::check_functor_type_tag);
      // GCC 2.95.3 gets the CV qualifiers wrong here, so we
      // can't do the static_cast that we should do.
      return static_cast<const Functor*>(type_result.obj_ptr);
    }


  template<typename F>
    bool contains(const F& f) const
    {
#if defined(BOOST_MSVC) && BOOST_WORKAROUND(BOOST_MSVC, < 1300)
      if (const F* fp = this->target( (F*)0 ))
#else
      if (const F* fp = this->template target<F>())
#endif
      {
        return function_equal(*fp, f);
      } else {
        return false;
      }
    }

  detail::function::vtable_base* get_vtable() const {
    return reinterpret_cast<detail::function::vtable_base*>(
             reinterpret_cast<std::size_t>(vtable) & ~static_cast<std::size_t>(0x01));
  }


  bool has_trivial_copy_and_destroy() const {
    return reinterpret_cast<std::size_t>(vtable) & 0x01;
  }

  bad_function_call() : std::runtime_error("call to empty boost::function") {}

inline bool operator==(const function_base& f,
                       detail::function::useless_clear_type*)
{
  return f.empty();
}


inline bool operator!=(const function_base& f,
                       detail::function::useless_clear_type*)
{
  return !f.empty();
}


inline bool operator==(detail::function::useless_clear_type*,
                       const function_base& f)
{
  return f.empty();
}


inline bool operator!=(detail::function::useless_clear_type*,
                       const function_base& f)
{
  return !f.empty();
}
