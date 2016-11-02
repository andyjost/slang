
   basic_managed_external_buffer()
   {}

   basic_managed_external_buffer(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      this->swap(moved);
   }

   basic_managed_external_buffer &operator=(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      basic_managed_external_buffer tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


   void grow(size_type extra_bytes)
   {  base_t::grow(extra_bytes);   }

   void swap(basic_managed_external_buffer &other)
   {  base_t::swap(other); }

      static mapped_region
         create_posix_mapped_region(void *address, std::size_t size)
      {
         mapped_region region;
         region.m_base = address;
         region.m_size = size;
         return region;
      }

static mapped_region
anonymous_shared_memory(std::size_t size, void *address = 0)
#if (!defined(BOOST_INTERPROCESS_WINDOWS))
{
   int flags;
   int fd = -1;

   #if defined(MAP_ANONYMOUS) //Use MAP_ANONYMOUS
   flags = MAP_ANONYMOUS | MAP_SHARED;
   #elif !defined(MAP_ANONYMOUS) && defined(MAP_ANON) //use MAP_ANON
   flags = MAP_ANON | MAP_SHARED;
   #else // Use "/dev/zero"
   fd = open("/dev/zero", O_RDWR);
   flags = MAP_SHARED;
   if(fd == -1){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   #endif


   address = mmap( address
                  , size
                  , PROT_READ|PROT_WRITE
                  , flags
                  , fd
                  , 0);

   if(address == MAP_FAILED){
      if(fd != -1)
         close(fd);
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   if(fd != -1)
      close(fd);

   return ipcdetail::raw_mapped_region_creator::create_posix_mapped_region(address, size);
}


   basic_managed_windows_shared_memory *get_this_pointer()
   {  return this;   }

   basic_managed_windows_shared_memory()
   {}

   basic_managed_windows_shared_memory
      (BOOST_RV_REF(basic_managed_windows_shared_memory) moved)
   {  this->swap(moved);   }

   basic_managed_windows_shared_memory &operator=(BOOST_RV_REF(basic_managed_windows_shared_memory) moved)
   {
      basic_managed_windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   ~basic_managed_windows_shared_memory()
   {}

   void swap(basic_managed_windows_shared_memory &other)
   {
      base_t::swap(other);
      m_wshm.swap(other.m_wshm);
   }


   basic_managed_shared_memory *get_this_pointer()
   {  return this;   }

   permissions(os_permissions_type type)
      : m_perm(type)
   {}

   permissions()
   {  set_default(); }

   void set_default()
   {
      /// @cond
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = 0;
      #else
      m_perm = 0644;
      #endif
      /// @endcond
   }

   void set_unrestricted()
   {
      /// @cond
      #if defined (BOOST_INTERPROCESS_WINDOWS)
      m_perm = &ipcdetail::unrestricted_permissions_holder<0>::unrestricted;
      #else
      m_perm = 0666;
      #endif
      /// @endcond
   }

   void set_permissions(os_permissions_type perm)
   {  m_perm = perm; }

   os_permissions_type get_permissions() const
   {  return m_perm; }

   xsi_key()
      : m_key(IPC_PRIVATE)
   {}

   key_t get_key() const
   {  return m_key;  }


   basic_managed_mapped_file *get_this_pointer()
   {  return this;   }

   file_mapping(BOOST_RV_REF(file_mapping) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   file_mapping &operator=(BOOST_RV_REF(file_mapping) moved)
   {
      file_mapping tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline file_mapping::~file_mapping()
{  this->priv_close(); }


inline const char *file_mapping::get_name() const
{  return m_filename.c_str(); }


inline void file_mapping::swap(file_mapping &other)
{
   std::swap(m_handle, other.m_handle);
   std::swap(m_mode, other.m_mode);
   m_filename.swap(other.m_filename);
}


inline bool file_mapping::remove(const char *filename)
{  return ipcdetail::delete_file(filename);  }


inline void file_mapping::priv_close()
{
   if(m_handle != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_handle);
      m_handle = ipcdetail::invalid_file();
   }
}

   remove_file_on_destroy(const char *name)
      :  m_name(name)
   {}


   ~remove_file_on_destroy()
   {  ipcdetail::delete_file(m_name);  }

   segment_manager_base(size_type sz, size_type reserved_bytes)
      :  MemoryAlgorithm(sz, reserved_bytes)
   {
      BOOST_ASSERT((sizeof(segment_manager_base<MemoryAlgorithm>) == sizeof(MemoryAlgorithm)));
   }

   size_type get_size() const
   {  return MemoryAlgorithm::get_size();  }

   size_type get_free_memory() const
   {  return MemoryAlgorithm::get_free_memory();  }

   static size_type get_min_size (size_type size)
   {  return MemoryAlgorithm::get_min_size(size);  }

   void * allocate (size_type nbytes, std::nothrow_t)
   {  return MemoryAlgorithm::allocate(nbytes);   }

   void allocate_many(size_type elem_bytes, size_type n_elements, multiallocation_chain &chain)
   {
      size_type prev_size = chain.size();
      MemoryAlgorithm::allocate_many(elem_bytes, n_elements, chain);
      if(!elem_bytes || chain.size() == prev_size){
         throw bad_alloc();
      }
   }

   void allocate_many(const size_type *element_lengths, size_type n_elements, size_type sizeof_element, multiallocation_chain &chain)
   {
      size_type prev_size = chain.size();
      MemoryAlgorithm::allocate_many(element_lengths, n_elements, sizeof_element, chain);
      if(!sizeof_element || chain.size() == prev_size){
         throw bad_alloc();
      }
   }

   void deallocate_many(multiallocation_chain &chain)
   {  MemoryAlgorithm::deallocate_many(chain); }

   void * allocate(size_type nbytes)
   {
      void * ret = MemoryAlgorithm::allocate(nbytes);
      if(!ret)
         throw bad_alloc();
      return ret;
   }

   void * allocate_aligned (size_type nbytes, size_type alignment, std::nothrow_t)
   {  return MemoryAlgorithm::allocate_aligned(nbytes, alignment);   }

   void * allocate_aligned(size_type nbytes, size_type alignment)
   {
      void * ret = MemoryAlgorithm::allocate_aligned(nbytes, alignment);
      if(!ret)
         throw bad_alloc();
      return ret;
   }

   explicit segment_manager(size_type segment_size)
      :  Base(segment_size, priv_get_reserved_bytes())
      ,  m_header(static_cast<Base*>(get_this_pointer()))
   {
      (void) anonymous_instance;   (void) unique_instance;
      BOOST_ASSERT(static_cast<const void*>(this) == static_cast<const void*>(static_cast<Base*>(this)));
   }

      explicit offset_ptr_internal(OffsetType off)
         : m_offset(off)
      {}


   template<int Dummy>
   #ifndef BOOST_INTERPROCESS_OFFSET_PTR_INLINE_TO_PTR
      BOOST_INTERPROCESS_NEVER_INLINE
   #elif defined(NDEBUG)
      inline
   #endif
   void * offset_ptr_to_raw_pointer(const volatile void *this_ptr, std::size_t offset)
   {
      typedef pointer_size_t_caster<void*> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_PTR
         if(offset == 1){
            return 0;
         }
         else{
            const caster_t caster((void*)this_ptr);
            return caster_t(caster.size() + offset).pointer();
         }
      #else
         const caster_t caster((void*)this_ptr);
         return caster_t((caster.size() + offset) & -std::size_t(offset != 1)).pointer();
      #endif
   }


   template<int Dummy>
   #ifndef BOOST_INTERPROCESS_OFFSET_PTR_INLINE_TO_OFF
      BOOST_INTERPROCESS_NEVER_INLINE
   #elif defined(NDEBUG)
      inline
   #endif
   std::size_t offset_ptr_to_offset(const volatile void *ptr, const volatile void *this_ptr)
   {
      typedef pointer_size_t_caster<void*> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF
         //offset == 1 && ptr != 0 is not legal for this pointer
         if(!ptr){
            return 1;
         }
         else{
            const caster_t this_caster((void*)this_ptr);
            const caster_t ptr_caster((void*)ptr);
            std::size_t offset = ptr_caster.size() - this_caster.size();
            BOOST_ASSERT(offset != 1);
            return offset;
         }
      #else
         const caster_t this_caster((void*)this_ptr);
         const caster_t ptr_caster((void*)ptr);
         //std::size_t other = -std::size_t(ptr != 0);
         //std::size_t offset = (ptr_caster.size() - this_caster.size()) & other;
         //return offset + !other;
         //
         std::size_t offset = (ptr_caster.size() - this_caster.size() - 1) & -std::size_t(ptr != 0);
         return ++offset;
      #endif
   }


   template<int Dummy>
   #ifndef BOOST_INTERPROCESS_OFFSET_PTR_INLINE_TO_OFF_FROM_OTHER
      BOOST_INTERPROCESS_NEVER_INLINE
   #elif defined(NDEBUG)
      inline
   #endif
   std::size_t offset_ptr_to_offset_from_other
      (const volatile void *this_ptr, const volatile void *other_ptr, std::size_t other_offset)
   {
      typedef pointer_size_t_caster<void*> caster_t;
      #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF_FROM_OTHER
      if(other_offset == 1){
         return 1;
      }
      else{
         const caster_t this_caster((void*)this_ptr);
         const caster_t other_caster((void*)other_ptr);
         std::size_t offset = other_caster.size() - this_caster.size() + other_offset;
         BOOST_ASSERT(offset != 1);
         return offset;
      }
      #else
      const caster_t this_caster((void*)this_ptr);
      const caster_t other_caster((void*)other_ptr);
      return ((other_caster.size() - this_caster.size()) & -std::size_t(other_offset != 1)) + other_offset;
      #endif
   }

   void unspecified_bool_type_func() const {}

   offset_ptr()
      : internal(1)
   {}

   offset_ptr(pointer ptr)
      : internal(static_cast<OffsetType>(ipcdetail::offset_ptr_to_offset<0>(ptr, this)))
   {}

   offset_ptr(const offset_ptr& ptr)
      : internal(static_cast<OffsetType>
         (ipcdetail::offset_ptr_to_offset_from_other<0>(this, &ptr, ptr.internal.m_offset)))
   {}

   pointer get() const
   {  return (pointer)ipcdetail::offset_ptr_to_raw_pointer<0>(this, this->internal.m_offset);   }


   offset_type get_offset() const
   {  return this->internal.m_offset;  }

   pointer operator->() const
   {  return this->get(); }

   reference operator* () const
   {
      pointer p = this->get();
      reference r = *p;
      return r;
   }

   reference operator[](difference_type idx) const
   {  return this->get()[idx];  }

   offset_ptr& operator= (pointer from)
   {
      this->internal.m_offset =
         static_cast<OffsetType>(ipcdetail::offset_ptr_to_offset<0>(from, this));
      return *this;
   }

   offset_ptr& operator= (const offset_ptr & ptr)
   {
      this->internal.m_offset =
         static_cast<OffsetType>(ipcdetail::offset_ptr_to_offset_from_other<0>(this, &ptr, ptr.internal.m_offset));
      return *this;
   }

   static offset_ptr pointer_to(reference r)
   { return offset_ptr(&r); }

   void inc_offset(DifferenceType bytes)
   {  internal.m_offset += bytes;   }


   void dec_offset(DifferenceType bytes)
   {  internal.m_offset -= bytes;   }

template <class T, class P, class O, std::size_t A>
inline T * to_raw_pointer(boost::interprocess::offset_ptr<T, P, O, A> const & p)
{  return ipcdetail::to_raw_pointer(p);   }


   static pointer get_pointer(const pointer &n)
   {
      caster_t caster(n.get());
      return pointer(caster_t(caster.size() & ~Mask).pointer());
   }


   static void set_pointer(pointer &n, const pointer &p)
   {
      caster_t n_caster(n.get());
      caster_t p_caster(p.get());
      BOOST_ASSERT(0 == (p_caster.size() & Mask));
      n = caster_t(p_caster.size() | (n_caster.size() & Mask)).pointer();
   }


   static std::size_t get_bits(const pointer &n)
   {  return (caster_t(n.get()).size() & Mask) >> 1u;  }


   static void set_bits(pointer &n, std::size_t b)
   {
      BOOST_ASSERT(b < (std::size_t(1) << NumBits));
      caster_t n_caster(n.get());
      n = caster_t((n_caster.size() & ~Mask) | (b << 1u)).pointer();
   }

   shared_memory_object(create_only_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   shared_memory_object(BOOST_RV_REF(shared_memory_object) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   shared_memory_object &operator=(BOOST_RV_REF(shared_memory_object) moved)
   {
      shared_memory_object tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline shared_memory_object::~shared_memory_object()
{  this->priv_close(); }



inline const char *shared_memory_object::get_name() const
{  return m_filename.c_str(); }


inline void shared_memory_object::swap(shared_memory_object &other)
{
   std::swap(m_handle,  other.m_handle);
   std::swap(m_mode,    other.m_mode);
   m_filename.swap(other.m_filename);
}


inline bool shared_memory_object::remove(const char *filename)
{
   try{
      //Make sure a temporary path is created for shared memory
      std::string shmfile;
      ipcdetail::tmp_filename(filename, shmfile);
      return ipcdetail::delete_file(shmfile.c_str());
   }
   catch(...){
      return false;
   }
}


inline void shared_memory_object::priv_close()
{
   if(m_handle != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_handle);
      m_handle = ipcdetail::invalid_file();
   }
}

   remove_shared_memory_on_destroy(const char *name)
      :  m_name(name)
   {}


   ~remove_shared_memory_on_destroy()
   {  shared_memory_object::remove(m_name);  }

   xsi_shared_memory(open_only_t, int shmid)
      : m_shmid (shmid)
   {}

   xsi_shared_memory(BOOST_RV_REF(xsi_shared_memory) moved)
      : m_shmid(-1)
   {  this->swap(moved);   }

   xsi_shared_memory &operator=(BOOST_RV_REF(xsi_shared_memory) moved)
   {
      xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline xsi_shared_memory::~xsi_shared_memory()
{}


inline int xsi_shared_memory::get_shmid() const
{  return m_shmid; }


inline void xsi_shared_memory::swap(xsi_shared_memory &other)
{
   std::swap(m_shmid, other.m_shmid);
}


inline bool xsi_shared_memory::remove(int shmid)
{  return -1 != ::shmctl(shmid, IPC_RMID, 0); }


   basic_managed_xsi_shared_memory *get_this_pointer()
   {  return this;   }

   ~basic_managed_xsi_shared_memory()
   {}

   basic_managed_xsi_shared_memory()
   {}

   basic_managed_xsi_shared_memory(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved)
   {
      basic_managed_xsi_shared_memory tmp;
      this->swap(moved);
      tmp.swap(moved);
   }

   basic_managed_xsi_shared_memory &operator=(BOOST_RV_REF(basic_managed_xsi_shared_memory) moved)
   {
      basic_managed_xsi_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   void swap(basic_managed_xsi_shared_memory &other)
   {
      base_t::swap(other);
      base2_t::swap(other);
   }

   static bool remove(int shmid)
   {  return device_type::remove(shmid); }


   int get_shmid() const
   {  return base2_t::get_device().get_shmid(); }

   interprocess_exception(const char *err/*error_code_t ec = other_error*/)
      :  m_err(other_error)
   {
//      try   {  m_str = "boost::interprocess_exception::library_error"; }
      try   {  m_str = err; }
      catch (...) {}
   }


   virtual ~interprocess_exception() throw(){}


   virtual const char * what() const throw()
   {  return m_str.c_str();  }


   native_error_t get_native_error()const { return m_err.get_native_error(); }

   error_code_t   get_error_code()  const { return m_err.get_error_code(); }

   lock_exception()
      :  interprocess_exception(lock_error)
   {}


   virtual const char* what() const throw()
   {  return "boost::interprocess::lock_exception";  }

   bad_alloc() : interprocess_exception("::boost::interprocess::bad_alloc"){}

   virtual const char* what() const throw()
      {  return "boost::interprocess::bad_alloc";  }

   windows_shared_memory(create_only_t, const char *name, mode_t mode, std::size_t size, const permissions& perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, size, perm);  }

   windows_shared_memory(BOOST_RV_REF(windows_shared_memory) moved)
      : m_handle(0)
   {  this->swap(moved);   }

   windows_shared_memory &operator=(BOOST_RV_REF(windows_shared_memory) moved)
   {
      windows_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline windows_shared_memory::~windows_shared_memory()
{  this->priv_close(); }


inline const char *windows_shared_memory::get_name() const
{  return m_name.c_str(); }


inline void windows_shared_memory::swap(windows_shared_memory &other)
{
   std::swap(m_handle,  other.m_handle);
   std::swap(m_mode,    other.m_mode);
   m_name.swap(other.m_name);
}


inline void windows_shared_memory::priv_close()
{
   if(m_handle){
      winapi::close_handle(m_handle);
      m_handle = 0;
   }
}

   mapped_region(BOOST_RV_REF(mapped_region) other)
   #if defined (BOOST_INTERPROCESS_WINDOWS)
   :  m_base(0), m_size(0)
   ,  m_page_offset(0)
   ,  m_mode(read_only)
   ,  m_file_or_mapping_hnd(ipcdetail::invalid_file())
   #else
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only), m_is_xsi(false)
   #endif
   {  this->swap(other);   }

   mapped_region &operator=(BOOST_RV_REF(mapped_region) other)
   {
      mapped_region tmp(boost::move(other));
      this->swap(tmp);
      return *this;
   }


inline void swap(mapped_region &x, mapped_region &y)
{  x.swap(y);  }


inline mapped_region::~mapped_region()
{  this->priv_close(); }


inline void*    mapped_region::get_address()  const
{  return m_base; }


inline void*    mapped_region::priv_map_address()  const
{  return static_cast<char*>(m_base) - m_page_offset; }


inline mapped_region::mapped_region()
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only), m_is_xsi(false)
{}


inline bool mapped_region::advise(advice_types advice)
{
   int unix_advice = 0;
   //Modes; 0: none, 2: posix, 1: madvise
   const unsigned int mode_none = 0;
   const unsigned int mode_padv = 1;
   const unsigned int mode_madv = 2;
   unsigned int mode = mode_none;
   //Choose advice either from POSIX (preferred) or native Unix
   switch(advice){
      case advice_normal:
         #if defined(POSIX_MADV_NORMAL)
         unix_advice = POSIX_MADV_NORMAL;
         mode = mode_padv;
         #elif defined(MADV_NORMAL)
         unix_advice = MADV_NORMAL;
         mode = mode_madv;
         #endif
      break;
      case advice_sequential:
         #if defined(POSIX_MADV_SEQUENTIAL)
         unix_advice = POSIX_MADV_SEQUENTIAL;
         mode = mode_padv;
         #elif defined(MADV_SEQUENTIAL)
         unix_advice = MADV_SEQUENTIAL;
         mode = mode_madv;
         #endif
      break;
      case advice_random:
         #if defined(POSIX_MADV_RANDOM)
         unix_advice = POSIX_MADV_RANDOM;
         mode = mode_padv;
         #elif defined(MADV_RANDOM)
         unix_advice = MADV_RANDOM;
         mode = mode_madv;
         #endif
      break;
      case advice_willneed:
         #if defined(POSIX_MADV_WILLNEED)
         unix_advice = POSIX_MADV_WILLNEED;
         mode = mode_padv;
         #elif defined(MADV_WILLNEED)
         unix_advice = MADV_WILLNEED;
         mode = mode_madv;
         #endif
      break;
      case advice_dontneed:
         #if defined(POSIX_MADV_DONTNEED)
         unix_advice = POSIX_MADV_DONTNEED;
         mode = mode_padv;
         #elif defined(MADV_DONTNEED) && defined(BOOST_INTERPROCESS_MADV_DONTNEED_HAS_NONDESTRUCTIVE_SEMANTICS)
         unix_advice = MADV_DONTNEED;
         mode = mode_madv;
         #endif
      break;
      default:
      return false;
   }
   switch(mode){
      #if defined(POSIX_MADV_NORMAL)
         case mode_padv:
         return 0 == posix_madvise(this->priv_map_address(), this->priv_map_size(), unix_advice);
      #endif
      #if defined(MADV_NORMAL)
         case mode_madv:
         return 0 == madvise(
            #if defined(BOOST_INTERPROCESS_MADVISE_USES_CADDR_T)
            (caddr_t)
            #endif
            this->priv_map_address(), this->priv_map_size(), unix_advice);
      #endif
      default:
      return false;

   }
}


inline void mapped_region::priv_close()
{
   if(m_base != 0){
      #ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
      if(m_is_xsi){
         int ret = ::shmdt(m_base);
         BOOST_ASSERT(ret == 0);
         (void)ret;
         return;
      }
      #endif //#ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
      munmap(this->priv_map_address(), this->priv_map_size());
      m_base = 0;
   }
}


inline void mapped_region::dont_close_on_destruction()
{  m_base = 0;   }


inline void mapped_region::swap(mapped_region &other)
{
   ipcdetail::do_swap(this->m_base, other.m_base);
   ipcdetail::do_swap(this->m_size, other.m_size);
   ipcdetail::do_swap(this->m_page_offset, other.m_page_offset);
   ipcdetail::do_swap(this->m_mode,  other.m_mode);
   #if (defined BOOST_INTERPROCESS_WINDOWS)
   ipcdetail::do_swap(this->m_file_or_mapping_hnd, other.m_file_or_mapping_hnd);
   #else
   ipcdetail::do_swap(this->m_is_xsi, other.m_is_xsi);
   #endif
}

   bool operator()(void *, std::size_t , bool) const
      {   return true;   }


   std::size_t get_min_size() const
   {  return 0;  }

inline int system_error_code() // artifact of POSIX and WINDOWS error reporting
{
   #if (defined BOOST_INTERPROCESS_WINDOWS)
   return winapi::get_last_error();
   #else
   return errno; // GCC 3.1 won't accept ::errno
   #endif
}

inline void fill_system_message( int system_error, std::string &str)
{  str = std::strerror(system_error);  }


inline error_code_t lookup_error(native_error_t err)
{
   const ec_xlate *cur  = &ec_table[0],
                  *end  = cur + sizeof(ec_table)/sizeof(ec_xlate);
   for  (;cur != end; ++cur ){
      if ( err == cur->sys_ec ) return cur->ec;
   }
   return system_error; // general system error code
}

   error_info(error_code_t ec = other_error )
      :  m_nat(0), m_ec(ec)
   {}


   error_info(native_error_t sys_err_code)
      :  m_nat(sys_err_code), m_ec(lookup_error(sys_err_code))
   {}


   error_info & operator =(error_code_t ec)
   {
      m_nat = 0;
      m_ec = ec;
      return *this;
   }


   error_info & operator =(native_error_t sys_err_code)
   {
      m_nat = sys_err_code;
      m_ec = lookup_error(sys_err_code);
      return *this;
   }


   native_error_t get_native_error()const
   {  return m_nat;  }


   error_code_t   get_error_code()const
   {  return m_ec;  }

   basic_managed_heap_memory(){}

   ~basic_managed_heap_memory()
   {  this->priv_close();  }

   basic_managed_heap_memory(BOOST_RV_REF(basic_managed_heap_memory) moved)
   {  this->swap(moved);   }

   basic_managed_heap_memory &operator=(BOOST_RV_REF(basic_managed_heap_memory) moved)
   {
      basic_managed_heap_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   bool grow(size_type extra_bytes)
   {
      //If memory is reallocated, data will
      //be automatically copied
      BOOST_TRY{
        m_heapmem.resize(m_heapmem.size()+extra_bytes);
      }
      BOOST_CATCH(...){
         return false;
      }
      BOOST_CATCH_END

      //Grow always works
      base_t::close_impl();
      base_t::open_impl(&m_heapmem[0], m_heapmem.size());
      base_t::grow(extra_bytes);
      return true;
   }

   void swap(basic_managed_heap_memory &other)
   {
      base_t::swap(other);
      m_heapmem.swap(other.m_heapmem);
   }

   void priv_close()
   {
      base_t::destroy_impl();
      std::vector<char>().swap(m_heapmem);
   }

   mem_algo_deallocator(void *ptr, MemoryAlgorithm &algo)
      :  m_ptr(ptr), m_algo(algo)
   {}


   void release()
   {  m_ptr = 0;  }


   ~mem_algo_deallocator()
   {  if(m_ptr) m_algo.deallocate(m_ptr);  }


   block_header(size_type val_bytes
               ,size_type val_alignment
               ,unsigned char al_type
               ,std::size_t szof_char
               ,std::size_t num_char
               )
      :  m_value_bytes(val_bytes)
      ,  m_num_char((unsigned short)num_char)
      ,  m_value_alignment((unsigned char)val_alignment)
      ,  m_alloc_type_sizeof_char( (al_type << 5u) | ((unsigned char)szof_char & 0x1F) )
   {};


   template<class T>
   block_header &operator= (const T& )
   {  return *this;  }


   size_type total_size() const
   {
      if(alloc_type() != anonymous_type){
         return name_offset() + (m_num_char+1)*sizeof_char();
      }
      else{
         return this->value_offset() + m_value_bytes;
      }
   }


   size_type value_bytes() const
   {  return m_value_bytes;   }


   template<class Header>
   size_type total_size_with_header() const
   {
      return get_rounded_size
               ( size_type(sizeof(Header))
			   , size_type(::boost::alignment_of<block_header<size_type> >::value))
           + total_size();
   }


   unsigned char alloc_type() const
   {  return (m_alloc_type_sizeof_char >> 5u)&(unsigned char)0x7;  }


   unsigned char sizeof_char() const
   {  return m_alloc_type_sizeof_char & (unsigned char)0x1F;  }


   template<class CharType>
   CharType *name() const
   {
      return const_cast<CharType*>(reinterpret_cast<const CharType*>
         (reinterpret_cast<const char*>(this) + name_offset()));
   }


   unsigned short name_length() const
   {  return m_num_char;   }


   size_type name_offset() const
   {
      return this->value_offset() + get_rounded_size(size_type(m_value_bytes), size_type(sizeof_char()));
   }


   void *value() const
   {
      return const_cast<char*>((reinterpret_cast<const char*>(this) + this->value_offset()));
   }


   size_type value_offset() const
   {
      return get_rounded_size(size_type(sizeof(block_header<size_type>)), size_type(m_value_alignment));
   }


   template<class CharType>
   bool less_comp(const block_header<size_type> &b) const
   {
      return m_num_char < b.m_num_char ||
             (m_num_char < b.m_num_char &&
               std::char_traits<CharType>::compare
                  (name<CharType>(), b.name<CharType>(), m_num_char) < 0);
   }


   template<class CharType>
   bool equal_comp(const block_header<size_type> &b) const
   {
      return m_num_char == b.m_num_char &&
             std::char_traits<CharType>::compare
               (name<CharType>(), b.name<CharType>(), m_num_char) == 0;
   }


   template<class T>
   static block_header<size_type> *block_header_from_value(T *value)
   {  return block_header_from_value(value, sizeof(T), ::boost::alignment_of<T>::value);  }


   template<class Header>
   static block_header<size_type> *from_first_header(Header *header)
   {
      block_header<size_type> * hdr =
         reinterpret_cast<block_header<size_type>*>(reinterpret_cast<char*>(header) +
		 get_rounded_size(size_type(sizeof(Header)), size_type(::boost::alignment_of<block_header<size_type> >::value)));
      //Some sanity checks
      return hdr;
   }


   template<class Header>
   static Header *to_first_header(block_header<size_type> *bheader)
   {
      Header * hdr =
         reinterpret_cast<Header*>(reinterpret_cast<char*>(bheader) -
		 get_rounded_size(size_type(sizeof(Header)), size_type(::boost::alignment_of<block_header<size_type> >::value)));
      //Some sanity checks
      return hdr;
   }


inline void array_construct(void *mem, std::size_t num, in_place_interface &table)
{
   //Try constructors
   std::size_t constructed = 0;
   BOOST_TRY{
      table.construct_n(mem, num, constructed);
   }
   //If there is an exception call destructors and erase index node
   BOOST_CATCH(...){
      std::size_t destroyed = 0;
      table.destroy_n(mem, constructed, destroyed);
      BOOST_RETHROW
   }
   BOOST_CATCH_END
}


   intrusive_compare_key(const CharT *str, std::size_t len)
      :  mp_str(str), m_len(len)
   {}

   instance_t(){}


   intrusive_value_type_impl(){}


   block_header<size_type> *get_block_header() const
   {
      return const_cast<block_header<size_type>*>
         (reinterpret_cast<const block_header<size_type> *>(reinterpret_cast<const char*>(this) +
            get_rounded_size(size_type(sizeof(*this)), size_type(BlockHdrAlignment))));
   }


   bool operator <(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template less_comp<CharType>(*other.get_block_header());  }


   bool operator ==(const intrusive_value_type_impl<Hook, CharType, SizeType> & other) const
   {  return (this->get_block_header())->template equal_comp<CharType>(*other.get_block_header());  }


   static intrusive_value_type_impl *get_intrusive_value_type(block_header<size_type> *hdr)
   {
      return reinterpret_cast<intrusive_value_type_impl *>(reinterpret_cast<char*>(hdr) -
         get_rounded_size(size_type(sizeof(intrusive_value_type_impl)), size_type(BlockHdrAlignment)));
   }


   CharType *name() const
   {  return get_block_header()->template name<CharType>(); }


   unsigned short name_length() const
   {  return get_block_header()->name_length(); }


   void *value() const
   {  return get_block_header()->value(); }

   char_ptr_holder(const CharType *name)
      : m_name(name)
   {}


   char_ptr_holder(const anonymous_instance_t *)
      : m_name(static_cast<CharType*>(0))
   {}


   char_ptr_holder(const unique_instance_t *)
      : m_name(reinterpret_cast<CharType*>(-1))
   {}


   operator const CharType *()
   {  return m_name;  }

   index_key (const char_type *nm, size_type length)
      : mp_str(nm), m_len(length)
   {}

   bool operator < (const index_key & right) const
   {
      return (m_len < right.m_len) ||
               (m_len == right.m_len &&
               std::char_traits<char_type>::compare
                  (to_raw_pointer(mp_str)
              ,to_raw_pointer(right.mp_str), m_len) < 0);
   }

   bool operator == (const index_key & right) const
   {
      return   m_len == right.m_len &&
               std::char_traits<char_type>::compare
                  (to_raw_pointer(mp_str),
                   to_raw_pointer(right.mp_str), m_len) == 0;
   }


   void name(const CharT *nm)
   {  mp_str = nm; }


   void name_length(size_type len)
   {  m_len = len; }


   const CharT *name() const
   {  return to_raw_pointer(mp_str); }

   index_data(void *ptr) : m_ptr(ptr){}


   void *value() const
   {  return static_cast<void*>(to_raw_pointer(m_ptr));  }

   segment_manager_iterator_value_adaptor(const typename Iterator::value_type &val)
      :  m_val(&val)
   {}


   const char_type *name() const
   {  return m_val->name(); }


   unsigned short name_length() const
   {  return m_val->name_length(); }


   const void *value() const
   {  return m_val->value(); }

   segment_manager_iterator_value_adaptor(const typename Iterator::value_type &val)
      :  m_val(&val)
   {}


   const char_type *name() const
   {  return m_val->first.name(); }


   size_type name_length() const
   {  return m_val->first.name_length(); }


   const void *value() const
   {
      return reinterpret_cast<block_header<size_type>*>
         (to_raw_pointer(m_val->second.m_ptr))->value();
   }


   result_type operator()(const typename Iterator::value_type &arg) const
   {  return result_type(arg); }

   dummy()
   {
      (void)anonymous_instance;
      (void)unique_instance;
   }

   template<class ManagedMemory>
   static bool grow(const char *filename, size_type extra_bytes)
   {
      typedef typename ManagedMemory::device_type device_type;
      //Increase file size
      try{
         offset_t old_size;
         {
            device_type f(open_or_create, filename, read_write);
            if(!f.get_size(old_size))
               return false;
            f.truncate(old_size + extra_bytes);
         }
         ManagedMemory managed_memory(open_only, filename);
         //Grow always works
         managed_memory.self_t::grow(extra_bytes);
      }
      catch(...){
         return false;
      }
      return true;
   }


   template<class ManagedMemory>
   static bool shrink_to_fit(const char *filename)
   {
      typedef typename ManagedMemory::device_type device_type;
      size_type new_size;
      try{
         ManagedMemory managed_memory(open_only, filename);
         managed_memory.get_size();
         managed_memory.self_t::shrink_to_fit();
         new_size = managed_memory.get_size();
      }
      catch(...){
         return false;
      }

      //Decrease file size
      {
         device_type f(open_or_create, filename, read_write);
         f.truncate(new_size);
      }
      return true;
   }

   basic_managed_memory_impl()
      : mp_header(0){}

   ~basic_managed_memory_impl()
   {  this->close_impl(); }

   bool  create_impl   (void *addr, size_type size)
   {
      if(mp_header)  return false;

      //Check if there is enough space
      if(size < segment_manager::get_min_size())
         return false;

      //This function should not throw. The index construction can
      //throw if constructor allocates memory. So we must catch it.
      BOOST_TRY{
         //Let's construct the allocator in memory
         mp_header       = new(addr) segment_manager(size);
      }
      BOOST_CATCH(...){
         return false;
      }
      BOOST_CATCH_END
      return true;
   }

   bool  open_impl     (void *addr, size_type)
   {
      if(mp_header)  return false;
      mp_header = static_cast<segment_manager*>(addr);
      return true;
   }

   bool close_impl()
   {
      bool ret = mp_header != 0;
      mp_header = 0;
      return ret;
   }

   bool destroy_impl()
   {
      if(mp_header == 0)
         return false;
      mp_header->~segment_manager();
      this->close_impl();
         return true;
   }

   void grow(size_type extra_bytes)
   {  mp_header->grow(extra_bytes); }


   void shrink_to_fit()
   {  mp_header->shrink_to_fit(); }

   segment_manager *get_segment_manager() const
   {   return mp_header; }

   void *   get_address   () const
   {   return reinterpret_cast<char*>(mp_header) - Offset; }

   size_type   get_size   () const
   {   return mp_header->get_size() + Offset;  }

   size_type get_free_memory() const
   {  return mp_header->get_free_memory();  }

   bool all_memory_deallocated()
   {   return mp_header->all_memory_deallocated(); }

   bool check_sanity()
   {   return mp_header->check_sanity(); }

   void zero_free_memory()
   {   mp_header->zero_free_memory(); }

   handle_t get_handle_from_address   (const void *ptr) const
   {
      return (handle_t)(reinterpret_cast<const char*>(ptr) -
             reinterpret_cast<const char*>(this->get_address()));
   }

   bool belongs_to_segment (const void *ptr) const
   {
      return ptr >= this->get_address() &&
             ptr <  (reinterpret_cast<const char*>(this->get_address()) + this->get_size());
   }

   void *    get_address_from_handle (handle_t offset) const
   {  return reinterpret_cast<char*>(this->get_address()) + offset; }

   void* allocate             (size_type nbytes)
   {   return mp_header->allocate(nbytes);   }

   void * allocate_aligned (size_type nbytes, size_type alignment, std::nothrow_t nothrow)
   {   return mp_header->allocate_aligned(nbytes, alignment, nothrow);  }


   create_open_func(BasicManagedMemoryImpl * const frontend, create_enum_t type)
      : m_frontend(frontend), m_type(type){}


   bool operator()(void *addr, std::size_t size, bool created) const
   {
      if( ((m_type == DoOpen)   &&  created) ||
          ((m_type == DoCreate) && !created) ||
          //Check for overflow
          size_type(-1) < size ){
         return false;
      }
      else if(created){
         return m_frontend->create_impl(addr, static_cast<size_type>(size));
      }
      else{
         return m_frontend->open_impl  (addr, static_cast<size_type>(size));
      }
   }


   std::size_t get_min_size() const
   {
      const size_type sz = m_frontend->get_segment_manager()->get_min_size();
      if(sz > std::size_t(-1)){
         //The minimum size is not representable by std::size_t
         BOOST_ASSERT(false);
         return std::size_t(-1);
      }
      else{
         return static_cast<std::size_t>(sz);
      }
   }

   DeviceAbstraction &get_device()
   {  static DeviceAbstraction dev; return dev; }


   const DeviceAbstraction &get_device() const
   {  static DeviceAbstraction dev; return dev; }

   DeviceAbstraction &get_device()
   {  return dev; }


   const DeviceAbstraction &get_device() const
   {  return dev; }


   managed_open_or_create_impl()
   {}


   managed_open_or_create_impl(BOOST_RV_REF(managed_open_or_create_impl) moved)
   {  this->swap(moved);   }


   managed_open_or_create_impl &operator=(BOOST_RV_REF(managed_open_or_create_impl) moved)
   {
      managed_open_or_create_impl tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


   ~managed_open_or_create_impl()
   {}


   std::size_t get_user_size()  const
   {  return m_mapped_region.get_size() - ManagedOpenOrCreateUserOffset; }


   void *get_user_address()  const
   {  return static_cast<char*>(m_mapped_region.get_address()) + ManagedOpenOrCreateUserOffset;  }


   std::size_t get_real_size()  const
   {  return m_mapped_region.get_size(); }


   void *get_real_address()  const
   {  return m_mapped_region.get_address();  }


   void swap(managed_open_or_create_impl &other)
   {
      this->m_mapped_region.swap(other.m_mapped_region);
   }


   bool flush()
   {  return m_mapped_region.flush();  }


   const mapped_region &get_mapped_region() const
   {  return m_mapped_region;  }



   DeviceAbstraction &get_device()
   {  return this->DevHolder::get_device(); }


   const DeviceAbstraction &get_device() const
   {  return this->DevHolder::get_device(); }

   template<bool dummy>
   static void truncate_device(DeviceAbstraction &, offset_t, false_)
   {}



   template<bool dummy>
   static bool check_offset_t_size(std::size_t , false_)
   { return true; }

   template<bool dummy>
   static void create_device(DeviceAbstraction &dev, const device_id_t & id, std::size_t size, const permissions &perm, false_ file_like)
   {
      (void)file_like;
      DeviceAbstraction tmp(create_only, id, read_write, size, perm);
      tmp.swap(dev);
   }


   template <class ConstructFunc> inline
   void priv_open_or_create
      (create_enum_t type,
       const device_id_t & id,
       std::size_t size,
       mode_t mode, const void *addr,
       const permissions &perm,
       ConstructFunc construct_func)
   {
      typedef bool_<FileBased> file_like_t;
      (void)mode;
      error_info err;
      bool created = false;
      bool ronly   = false;
      bool cow     = false;
      DeviceAbstraction dev;

      if(type != DoOpen){
         //Check if the requested size is enough to build the managed metadata
         const std::size_t func_min_size = construct_func.get_min_size();
         if( (std::size_t(-1) - ManagedOpenOrCreateUserOffset) < func_min_size ||
             size < (func_min_size + ManagedOpenOrCreateUserOffset) ){
            throw interprocess_exception(error_info(size_error));
         }
      }
      //Check size can be represented by offset_t (used by truncate)
      if(type != DoOpen && !check_offset_t_size<FileBased>(size, file_like_t())){
         throw interprocess_exception(error_info(size_error));
      }
      if(type == DoOpen && mode == read_write){
         DeviceAbstraction tmp(open_only, id, read_write);
         tmp.swap(dev);
         created = false;
      }
      else if(type == DoOpen && mode == read_only){
         DeviceAbstraction tmp(open_only, id, read_only);
         tmp.swap(dev);
         created = false;
         ronly   = true;
      }
      else if(type == DoOpen && mode == copy_on_write){
         DeviceAbstraction tmp(open_only, id, read_only);
         tmp.swap(dev);
         created = false;
         cow     = true;
      }
      else if(type == DoCreate){
         create_device<FileBased>(dev, id, size, perm, file_like_t());
         created = true;
      }
      else if(type == DoOpenOrCreate){
         //This loop is very ugly, but brute force is sometimes better
         //than diplomacy. If someone knows how to open or create a
         //file and know if we have really created it or just open it
         //drop me a e-mail!
         bool completed = false;
         while(!completed){
            try{
               create_device<FileBased>(dev, id, size, perm, file_like_t());
               created     = true;
               completed   = true;
            }
            catch(interprocess_exception &ex){
               if(ex.get_error_code() != already_exists_error){
                  throw;
               }
               else{
                  try{
                     DeviceAbstraction tmp(open_only, id, read_write);
                     dev.swap(tmp);
                     created     = false;
                     completed   = true;
                  }
                  catch(interprocess_exception &e){
                     if(e.get_error_code() != not_found_error){
                        throw;
                     }
                  }
                  catch(...){
                     throw;
                  }
               }
            }
            catch(...){
               throw;
            }
            thread_yield();
         }
      }

      if(created){
         try{
            //If this throws, we are lost
            truncate_device<FileBased>(dev, size, file_like_t());

            //If the following throws, we will truncate the file to 1
            mapped_region        region(dev, read_write, 0, 0, addr);
            boost::uint32_t *patomic_word = 0;  //avoid gcc warning
            patomic_word = static_cast<boost::uint32_t*>(region.get_address());
            boost::uint32_t previous = atomic_cas32(patomic_word, InitializingSegment, UninitializedSegment);

            if(previous == UninitializedSegment){
               try{
                  construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                                , size - ManagedOpenOrCreateUserOffset, true);
                  //All ok, just move resources to the external mapped region
                  m_mapped_region.swap(region);
               }
               catch(...){
                  atomic_write32(patomic_word, CorruptedSegment);
                  throw;
               }
               atomic_write32(patomic_word, InitializedSegment);
            }
            else if(previous == InitializingSegment || previous == InitializedSegment){
               throw interprocess_exception(error_info(already_exists_error));
            }
            else{
               throw interprocess_exception(error_info(corrupted_error));
            }
         }
         catch(...){
            try{
               truncate_device<FileBased>(dev, 1u, file_like_t());
            }
            catch(...){
            }
            throw;
         }
      }
      else{
         if(FileBased){
            offset_t filesize = 0;
            while(filesize == 0){
               if(!get_file_size(file_handle_from_mapping_handle(dev.get_mapping_handle()), filesize)){
                  throw interprocess_exception(error_info(system_error_code()));
               }
               thread_yield();
            }
            if(filesize == 1){
               throw interprocess_exception(error_info(corrupted_error));
            }
         }

         mapped_region  region(dev, ronly ? read_only : (cow ? copy_on_write : read_write), 0, 0, addr);

         boost::uint32_t *patomic_word = static_cast<boost::uint32_t*>(region.get_address());
         boost::uint32_t value = atomic_read32(patomic_word);

         while(value == InitializingSegment || value == UninitializedSegment){
            thread_yield();
            value = atomic_read32(patomic_word);
         }

         if(value != InitializedSegment)
            throw interprocess_exception(error_info(corrupted_error));

         construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                        , region.get_size() - ManagedOpenOrCreateUserOffset
                        , false);
         //All ok, just move resources to the external mapped region
         m_mapped_region.swap(region);
      }
      if(StoreDevice){
         this->DevHolder::get_device() = boost::move(dev);
      }
   }

   void dont_close_on_destruction()
   {  interprocess_tester::dont_close_on_destruction(m_mapped_region);  }

   template<class T>
   static void dont_close_on_destruction(T &t)
   {  t.dont_close_on_destruction(); }


inline bool lock_locking_file(int fd)
{
   int ret = 0;
   while(ret != 0 && errno != EINTR){
      struct flock lock;
      lock.l_type = F_WRLCK;
      lock.l_whence = SEEK_SET;
      lock.l_start = 0;
      lock.l_len = 1;
      ret = fcntl (fd, F_SETLKW, &lock);
   }
   return 0 == ret;
}


inline bool try_lock_locking_file(int fd)
{
   struct flock lock;
   lock.l_type = F_WRLCK;
   lock.l_whence = SEEK_SET;
   lock.l_start = 0;
   lock.l_len = 1;
   return 0 == fcntl (fd, F_SETLK, &lock);
}


inline int open_or_create_and_lock_file(const char *name)
{
   permissions p;
   p.set_unrestricted();
   while(1){
      int fd = create_or_open_file(name, read_write, p);
      if(fd < 0){
         return fd;
      }
      if(!try_lock_locking_file(fd)){
         close(fd);
         return -1;
      }
      struct stat s;
      if(0 == stat(name, &s)){
         return fd;
      }
      else{
         close(fd);
      }
   }
}


inline int try_open_and_lock_file(const char *name)
{
   int fd = open_existing_file(name, read_write);
   if(fd < 0){
      return fd;
   }
   if(!try_lock_locking_file(fd)){
      close(fd);
      return -1;
   }
   return fd;
}


inline void close_lock_file(int fd)
{  close(fd); }


inline bool is_valid_fd(int fd)
{
   struct stat s;
   return EBADF != fstat(fd, &s);
}


inline bool is_normal_file(int fd)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return false;
   return 0 != (s.st_mode & S_IFREG);
}


inline std::size_t get_size(int fd)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return 0u;
   return (std::size_t)s.st_size;
}


inline bool fill_file_serial_id(int fd, locking_file_serial_id &id)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return false;
   id.fd = fd;
   id.st_dev = s.st_dev;
   id.st_ino = s.st_ino;
   id.modules_attached_to_gmem_count = 1; //Initialize attached count
   return true;
}


inline bool compare_file_serial(int fd, const locking_file_serial_id &id)
{
   struct stat info;
   if(0 != fstat(fd, &info))
      return false;

   return   id.st_dev == info.st_dev  &&
            id.st_ino == info.st_ino;
}


template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }


template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }


   xsi_shared_memory_device(create_only_t, const char *name, mode_t mode, std::size_t size)
   {  this->priv_open_or_create_name_only(ipcdetail::DoCreate, name, mode, size);  }


   xsi_shared_memory_device(BOOST_RV_REF(xsi_shared_memory_device) moved)
   {  this->swap(moved);   }


   xsi_shared_memory_device &operator=(BOOST_RV_REF(xsi_shared_memory_device) moved)
   {
      xsi_shared_memory_device tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline xsi_shared_memory_device::~xsi_shared_memory_device()
{}


inline const char *xsi_shared_memory_device::get_name() const
{  return m_name.c_str(); }


inline void xsi_shared_memory_device::swap(xsi_shared_memory_device &other)
{
   m_shm.swap(other.m_shm);
   std::swap(m_mode,  other.m_mode);
   m_name.swap(other.m_name);
}


inline bool xsi_shared_memory_device::priv_remove_dead_memory
   (xsi_shared_memory_device::info_t *info, const char *path)
{
   bool removed = false;
   for(std::size_t i = 0; i != info_constants_t<0>::NumID; ++i){
      if(info->names[i].buf[0]){
         try{
            xsi_shared_memory temp( open_only, path, i+info_constants_t<0>::FirstID, 0600);
         }
         catch(interprocess_exception &e){
               if(e.get_error_code() == not_found_error){
                  std::memset(info->names[i].buf, 0, info_constants_t<0>::MaxName);
                  removed = true;
               }
         }
      }
   }
   return removed;
}


inline bool xsi_shared_memory_device::remove(const char *shmname)
{
   try{
      //Obtain index and index lockss
      mapped_region region;
      xsi_named_mutex mut;
      std::string xsi_shm_emulation_file_path;
      priv_obtain_index(region, mut, xsi_shm_emulation_file_path);
      scoped_lock<xsi_named_mutex> lock(mut);
      info_t *info = static_cast<info_t *>(region.get_address());

      //Now check and remove
      bool removed = false;

      for(std::size_t i = 0; i != info_constants_t<0>::NumID; ++i){
         if(0 == std::strcmp(info->names[i].buf, name)){
            xsi_shared_memory temp( open_only, xsi_shm_emulation_file_path.c_str()
                                  , i+info_constants_t<0>::FirstID);
            if(!xsi_shared_memory::remove(temp.get_shmid()) && (system_error_code() != invalid_argument)){
               return false;
            }
            std::memset(info->names[i].buf, 0, info_constants_t<0>::MaxName);
            removed = true;
            break;
         }
      }
      return removed;
   }
   catch(...){
      return false;
   }
}


inline bool xsi_shared_memory_device::remove(int shmid)
{  return xsi_shared_memory::remove(shmid);  }

   file_wrapper(create_only_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   file_wrapper(BOOST_RV_REF(file_wrapper) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   file_wrapper &operator=(BOOST_RV_REF(file_wrapper) moved)
   {
      file_wrapper tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }


inline file_wrapper::~file_wrapper()
{  this->priv_close(); }


inline const char *file_wrapper::get_name() const
{  return m_filename.c_str(); }


inline void file_wrapper::swap(file_wrapper &other)
{
   std::swap(m_handle,  other.m_handle);
   std::swap(m_mode,    other.m_mode);
   m_filename.swap(other.m_filename);
}


inline bool file_wrapper::remove(const char *filename)
{  return delete_file(filename); }


inline void file_wrapper::priv_close()
{
   if(m_handle != invalid_file()){
      close_file(m_handle);
      m_handle = invalid_file();
   }
}

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

      group_services(frontend_t *const frontend)
         :  mp_frontend(frontend), m_group(0), m_min_segment_size(0){}


      create_open_func(self_t * const    frontend,
                       type_t type, size_type segment_number)
         : mp_frontend(frontend), m_type(type), m_segment_number(segment_number){}


      bool operator()(void *addr, size_type size, bool created) const
      {
         if(((m_type == DoOpen)   &&  created) ||
            ((m_type == DoCreate) && !created))
            return false;
         segment_group_id group = mp_frontend->m_group_services.get_group();
         bool mapped       = false;
         bool impl_done    = false;

         //Associate this newly created segment as the
         //segment id = 0 of this group
         void_pointer::insert_mapping
            ( group
            , static_cast<char*>(addr) - managed_impl::ManagedOpenOrCreateUserOffset
            , size + managed_impl::ManagedOpenOrCreateUserOffset);
         //Check if this is the master segment
         if(!m_segment_number){
            //Create or open the Interprocess machinery
            if((impl_done = created ?
               mp_frontend->create_impl(addr, size) : mp_frontend->open_impl(addr, size))){
               return true;
            }
         }
         else{
            return true;
         }

         //This is the cleanup part
         //---------------
         if(impl_done){
            mp_frontend->close_impl();
         }
         if(mapped){
            bool ret = void_pointer::erase_last_mapping(group);
            BOOST_ASSERT(ret);(void)ret;
         }
         return false;
      }


      std::size_t get_min_size() const
      {
         const size_type sz = mp_frontend->get_segment_manager()->get_min_size();
         if(sz > std::size_t(-1)){
            //The minimum size is not representable by std::size_t
            BOOST_ASSERT(false);
            return std::size_t(-1);
         }
         else{
            return static_cast<std::size_t>(sz);
         }
      }


      close_func(self_t * const frontend)
         : mp_frontend(frontend){}


      void operator()(const mapped_region &region, bool last) const
      {
         if(last) mp_frontend->destroy_impl();
         else     mp_frontend->close_impl();
      }


   basic_managed_multi_shared_memory *get_this_pointer()
      {  return this;   }


   basic_managed_multi_shared_memory(create_only_t,
                                     const char *name,
                                     size_type size,
                                     const permissions &perm = permissions())
      :  m_group_services(get_this_pointer())
   {
      priv_open_or_create(create_open_func::DoCreate,name, size, perm);
   }


   ~basic_managed_multi_shared_memory()
      {  this->priv_close(); }

   bool  priv_open_or_create(typename create_open_func::type_t type,
                             const char *name,
                             size_type size,
                             const permissions &perm)
   {
      if(!m_shmem_list.empty())
         return false;
      typename void_pointer::segment_group_id group = 0;
      BOOST_TRY{
         m_root_name = name;
         //Insert multi segment services and get a group identifier
         group = void_pointer::new_segment_group(&m_group_services);
         size = void_pointer::round_size(size);
         m_group_services.set_group(group);
         m_group_services.set_min_segment_size(size);

         if(group){
            if(this->priv_new_segment(type, size, 0, perm)){
               return true;
            }
         }
      }
      BOOST_CATCH(const std::bad_alloc&){
      }
      BOOST_CATCH_END
      if(group){
         void_pointer::delete_group(group);
      }
      return false;
   }


   bool  priv_new_segment(typename create_open_func::type_t type,
                          size_type size,
                          const void *addr,
                          const permissions &perm)
   {
      BOOST_TRY{
         //Get the number of groups of this multi_segment group
         size_type segment_id  = m_shmem_list.size();
         //Format the name of the shared memory: append segment number.
         boost::interprocess::basic_ovectorstream<boost::interprocess::string> formatter;
         //Pre-reserve string size
         size_type str_size = m_root_name.length()+10;
         if(formatter.vector().size() < str_size){
            //This can throw.
            formatter.reserve(str_size);
         }
         //Format segment's name
         formatter << m_root_name
                   << static_cast<unsigned int>(segment_id) << std::ends;
         //This functor will be executed when constructing
         create_open_func func(this, type, segment_id);
         const char *name = formatter.vector().c_str();
         //This can throw.
         managed_impl mshm;

         switch(type){
            case create_open_func::DoCreate:
            {
               managed_impl shm(create_only, name, size, read_write, addr, func, perm);
               mshm = boost::move(shm);
            }
            break;

            case create_open_func::DoOpen:
            {
               managed_impl shm(open_only, name,read_write, addr, func);
               mshm = boost::move(shm);
            }
            break;

            case create_open_func::DoOpenOrCreate:
            {
               managed_impl shm(open_or_create, name, size, read_write, addr, func, perm);
               mshm = boost::move(shm);
            }
            break;

            default:
               return false;
            break;
         }

         //This can throw.
         m_shmem_list.push_back(boost::move(mshm));
         return true;
      }
      BOOST_CATCH(const std::bad_alloc&){
      }
      BOOST_CATCH_END
      return false;
   }

   void priv_close()
   {
      if(!m_shmem_list.empty()){
         bool ret;
         //Obtain group identifier
         segment_group_id group = m_group_services.get_group();
         //Erase main segment and its resources
         //typename shmem_list_t::iterator  itbeg = m_shmem_list.begin(),
         //                        itend = m_shmem_list.end(),
         //                        it    = itbeg;
         //(*itbeg)->close_with_func(close_func(this));
         //Delete group. All mappings are erased too.
         ret = void_pointer::delete_group(group);
         (void)ret;
         BOOST_ASSERT(ret);
         m_shmem_list.clear();
      }
   }


   basic_managed_global_memory *get_this_pointer()
   {  return this;   }

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


   Ctor0Arg(){}


   self_t& operator++()       {  return *this;  }

   self_t  operator++(int)    {  return *this;  }


   void construct(void *mem)
   {  new((void*)mem)T;  }


   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed)
   {
      T* memory = static_cast<T*>(mem);
      for(constructed = 0; constructed < num; ++constructed)
         new((void*)memory++)T;
   }

   named_proxy(SegmentManager *mngr, const char_type *name, bool find, bool dothrow)
      :  mp_name(name), mp_mngr(mngr), m_num(1)
      ,  m_find(find),  m_dothrow(dothrow)
   {}

   T *operator()() const
   {
      Ctor0Arg<T> ctor_obj;
      return mp_mngr->template
         generic_construct<T>(mp_name, m_num, m_find, m_dothrow, ctor_obj);
   }

   const named_proxy &operator[](std::size_t num) const
      {  m_num *= num; return *this;  }


inline unsigned long get_last_error()
{  return GetLastError();  }


inline void set_last_error(unsigned long err)
{  return SetLastError(err);  }


inline unsigned long format_message
   (unsigned long dwFlags, const void *lpSource,
    unsigned long dwMessageId, unsigned long dwLanguageId,
    char *lpBuffer, unsigned long nSize, std::va_list *Arguments)
{
   return FormatMessageA
      (dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
}

inline void * local_free(void *hmem)
{  return LocalFree(hmem); }


inline unsigned long make_lang_id(unsigned long p, unsigned long s)
{  return ((((unsigned short)(s)) << 10) | (unsigned short)(p));   }


inline void sched_yield()
{
   if(!SwitchToThread()){
      Sleep(1);
   }
}


inline void sleep(unsigned long ms)
{  Sleep(ms);  }


inline unsigned long get_current_thread_id()
{  return GetCurrentThreadId();  }


inline bool get_process_times
   ( void *hProcess, interprocess_filetime* lpCreationTime
   , interprocess_filetime *lpExitTime, interprocess_filetime *lpKernelTime
   , interprocess_filetime *lpUserTime )
{  return 0 != GetProcessTimes(hProcess, lpCreationTime, lpExitTime, lpKernelTime, lpUserTime); }


inline unsigned long get_current_process_id()
{  return GetCurrentProcessId();  }


inline unsigned int close_handle(void* handle)
{  return CloseHandle(handle);   }


inline void * find_first_file(const char *lpFileName, win32_find_data_t *lpFindFileData)
{  return FindFirstFileA(lpFileName, lpFindFileData);   }


inline bool find_next_file(void *hFindFile, win32_find_data_t *lpFindFileData)
{  return FindNextFileA(hFindFile, lpFindFileData) != 0;   }


inline bool find_close(void *handle)
{  return FindClose(handle) != 0;   }


inline bool duplicate_current_process_handle
   (void *hSourceHandle, void **lpTargetHandle)
{
   return 0 != DuplicateHandle
      ( GetCurrentProcess(),  hSourceHandle,    GetCurrentProcess()
      , lpTargetHandle,       0,                0
      , duplicate_same_access);
}


inline unsigned long get_file_type(void *hFile)
{
   return GetFileType(hFile);
}

inline void *open_or_create_mutex(const char *name, bool initial_owner, interprocess_security_attributes *attr)
{  return CreateMutexA(attr, (int)initial_owner, name);  }


inline unsigned long wait_for_single_object(void *handle, unsigned long time)
{  return WaitForSingleObject(handle, time); }


inline int release_mutex(void *handle)
{  return ReleaseMutex(handle);  }


inline int unmap_view_of_file(void *address)
{  return UnmapViewOfFile(address); }


inline void *open_or_create_semaphore(const char *name, long initial_count, long maximum_count, interprocess_security_attributes *attr)
{  return CreateSemaphoreA(attr, initial_count, maximum_count, name);  }


inline void *open_semaphore(const char *name)
{  return OpenSemaphoreA(semaphore_all_access, 0, name);  }


inline int release_semaphore(void *handle, long release_count, long *prev_count)
{  return ReleaseSemaphore(handle, release_count, prev_count); }

   interprocess_all_access_security()
      : initialized(false)
   {
      if(!InitializeSecurityDescriptor(&sd, security_descriptor_revision))
         return;
      if(!SetSecurityDescriptorDacl(&sd, true, 0, false))
         return;
      sa.lpSecurityDescriptor = &sd;
      sa.nLength = sizeof(interprocess_security_attributes);
      sa.bInheritHandle = false;
      initialized = false;
   }


   interprocess_security_attributes *get_attributes()
   {  return &sa; }


inline void * create_file_mapping (void * handle, unsigned long access, unsigned __int64 file_offset, const char * name, interprocess_security_attributes *psec)
{
   const unsigned long high_size(file_offset >> 32), low_size((boost::uint32_t)file_offset);
   return CreateFileMappingA (handle, psec, access, high_size, low_size, name);
}


inline void * open_file_mapping (unsigned long access, const char *name)
{  return OpenFileMappingA (access, 0, name);   }


inline void *map_view_of_file_ex(void *handle, unsigned long file_access, unsigned __int64 offset, std::size_t numbytes, void *base_addr)
{
   const unsigned long offset_low  = (unsigned long)(offset & ((unsigned __int64)0xFFFFFFFF));
   const unsigned long offset_high = offset >> 32;
   return MapViewOfFileEx(handle, file_access, offset_high, offset_low, numbytes, base_addr);
}


inline void *create_file(const char *name, unsigned long access, unsigned long creation_flags, unsigned long attributes, interprocess_security_attributes *psec)
{
   for (unsigned int attempt(0); attempt < error_sharing_violation_tries; ++attempt){
      void * const handle = CreateFileA(name, access,
                                        file_share_read | file_share_write | file_share_delete,
                                        psec, creation_flags, attributes, 0);
      bool const invalid(invalid_handle_value == handle);
      if (!invalid){
         return handle;
      }
      if (error_sharing_violation != get_last_error()){
         return handle;
      }
      sleep(error_sharing_violation_sleep_ms);
   }
   return invalid_handle_value;
}


inline void get_system_info(system_info *info)
{  GetSystemInfo(info); }


inline bool flush_view_of_file(void *base_addr, std::size_t numbytes)
{  return 0 != FlushViewOfFile(base_addr, numbytes); }


inline bool virtual_unlock(void *base_addr, std::size_t numbytes)
{  return 0 != VirtualUnlock(base_addr, numbytes); }


inline bool virtual_protect(void *base_addr, std::size_t numbytes, unsigned long flNewProtect, unsigned long &lpflOldProtect)
{  return 0 != VirtualProtect(base_addr, numbytes, flNewProtect, &lpflOldProtect); }


inline bool flush_file_buffers(void *handle)
{  return 0 != FlushFileBuffers(handle); }


inline bool get_file_size(void *handle, __int64 &size)
{  return 0 != GetFileSizeEx(handle, &size);  }


inline bool create_directory(const char *name)
{
   interprocess_all_access_security sec;
   return 0 != CreateDirectoryA(name, sec.get_attributes());
}


inline bool remove_directory(const char *lpPathName)
{  return 0 != RemoveDirectoryA(lpPathName);   }


inline unsigned long get_temp_path(unsigned long length, char *buffer)
{  return GetTempPathA(length, buffer);   }


inline int set_end_of_file(void *handle)
{  return 0 != SetEndOfFile(handle);   }


inline bool set_file_pointer_ex(void *handle, __int64 distance, __int64 *new_file_pointer, unsigned long move_method)
{  return 0 != SetFilePointerEx(handle, distance, new_file_pointer, move_method);   }


inline bool lock_file_ex(void *hnd, unsigned long flags, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped *overlapped)
{  return 0 != LockFileEx(hnd, flags, reserved, size_low, size_high, overlapped); }


inline bool unlock_file_ex(void *hnd, unsigned long reserved, unsigned long size_low, unsigned long size_high, interprocess_overlapped *overlapped)
{  return 0 != UnlockFileEx(hnd, reserved, size_low, size_high, overlapped);  }


inline bool write_file(void *hnd, const void *buffer, unsigned long bytes_to_write, unsigned long *bytes_written, interprocess_overlapped* overlapped)
{  return 0 != WriteFile(hnd, buffer, bytes_to_write, bytes_written, overlapped);  }


inline bool read_file(void *hnd, void *buffer, unsigned long bytes_to_read, unsigned long *bytes_read, interprocess_overlapped* overlapped)
{  return 0 != ReadFile(hnd, buffer, bytes_to_read, bytes_read, overlapped);  }


inline bool get_file_information_by_handle(void *hnd, interprocess_by_handle_file_information *info)
{  return 0 != GetFileInformationByHandle(hnd, info);  }


inline long interlocked_increment(long volatile *addr)
{  return BOOST_INTERLOCKED_INCREMENT(addr);  }


inline long interlocked_decrement(long volatile *addr)
{  return BOOST_INTERLOCKED_DECREMENT(addr);  }


inline long interlocked_compare_exchange(long volatile *addr, long val1, long val2)
{  return BOOST_INTERLOCKED_COMPARE_EXCHANGE(addr, val1, val2);  }


inline long interlocked_exchange_add(long volatile* addend, long value)
{  return BOOST_INTERLOCKED_EXCHANGE_ADD(const_cast<long*>(addend), value);  }


inline long interlocked_exchange(long volatile* addend, long value)
{  return BOOST_INTERLOCKED_EXCHANGE(const_cast<long*>(addend), value);  }

inline void *load_library(const char *name)
{  return LoadLibraryA(name); }


inline bool free_library(void *module)
{  return 0 != FreeLibrary(module); }


inline void *get_proc_address(void *module, const char *name)
{  return GetProcAddress(module, name); }


inline void *get_current_process()
{  return GetCurrentProcess();  }


inline void *get_module_handle(const char *name)
{  return GetModuleHandleA(name); }


inline long reg_open_key_ex(void *hKey, const char *lpSubKey, unsigned long ulOptions, unsigned long samDesired, void **phkResult)
{  return RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult); }


inline long reg_query_value_ex(void *hKey, const char *lpValueName, unsigned long*lpReserved, unsigned long*lpType, unsigned char *lpData, unsigned long*lpcbData)
{  return RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData); }


inline long reg_close_key(void *hKey)
{  return RegCloseKey(hKey); }


inline bool query_performance_counter(__int64 *lpPerformanceCount)
{
   return 0 != QueryPerformanceCounter(lpPerformanceCount);
}


inline void initialize_object_attributes
( object_attributes_t *pobject_attr, unicode_string_t *name
 , unsigned long attr, void *rootdir, void *security_descr)

{
   pobject_attr->Length = sizeof(object_attributes_t);
   pobject_attr->RootDirectory = rootdir;
   pobject_attr->Attributes = attr;
   pobject_attr->ObjectName = name;
   pobject_attr->SecurityDescriptor = security_descr;
   pobject_attr->SecurityQualityOfService = 0;
}


inline void rtl_init_empty_unicode_string(unicode_string_t *ucStr, wchar_t *buf, unsigned short bufSize)
{
   ucStr->Buffer = buf;
   ucStr->Length = 0;
   ucStr->MaximumLength = bufSize;
}


   static void *get_module_from_id(unsigned int id)
   {
      BOOST_ASSERT(id < (unsigned int)NumModule);
      return get_module_handle(ModuleNames[id]);
   }


   static void *get_module(const unsigned int id)
   {
      BOOST_ASSERT(id < (unsigned int)NumModule);
      while(ModuleStates[id] < 2){
         if(interlocked_compare_exchange(&ModuleStates[id], 1, 0) == 0){
            ModuleAddresses[id] = get_module_from_id(id);
            interlocked_increment(&ModuleStates[id]);
            break;
         }
         else{
            sched_yield();
         }
      }
      return ModuleAddresses[id];
   }


   static void *get_address_from_dll(const unsigned int id)
   {
      BOOST_ASSERT(id < (unsigned int)NumFunction);
      return get_proc_address(get_module(FunctionModules[id]), FunctionNames[id]);
   }

   static void *get(const unsigned int id)
   {
      BOOST_ASSERT(id < (unsigned int)NumFunction);
      while(FunctionStates[id] < 2){
         if(interlocked_compare_exchange(&FunctionStates[id], 1, 0) == 0){
            FunctionAddresses[id] = get_address_from_dll(id);
            interlocked_increment(&FunctionStates[id]);
            break;
         }
         else{
            sched_yield();
         }
      }
      return FunctionAddresses[id];
   }

   library_unloader(void *module) : lib_(module){}

   ~library_unloader(){ free_library(lib_);  }



inline bool get_system_time_of_day_information(system_timeofday_information &info)
{
   NtQuerySystemInformation_t pNtQuerySystemInformation = (NtQuerySystemInformation_t)
         dll_func::get(dll_func::NtQuerySystemInformation);
   unsigned long res;
   long status = pNtQuerySystemInformation(system_time_of_day_information, &info, sizeof(info), &res);
   if(status){
      return false;
   }
   return true;
}


inline bool get_boot_time(unsigned char (&bootstamp) [BootstampLength])
{
   system_timeofday_information info;
   bool ret = get_system_time_of_day_information(info);
   if(!ret){
      return false;
   }
   std::memcpy(&bootstamp[0], &info.Reserved1, sizeof(bootstamp));
   return true;
}


inline bool get_boot_and_system_time(unsigned char (&bootsystemstamp) [BootAndSystemstampLength])
{
   system_timeofday_information info;
   bool ret = get_system_time_of_day_information(info);
   if(!ret){
      return false;
   }
   std::memcpy(&bootsystemstamp[0], &info.Reserved1, sizeof(bootsystemstamp));
   return true;
}


inline bool get_boot_time_str(char *bootstamp_str, std::size_t &s) //will write BootstampLength chars
{
   if(s < (BootstampLength*2))
      return false;
   system_timeofday_information info;
   bool ret = get_system_time_of_day_information(info);
   if(!ret){
      return false;
   }
   const char Characters [] =
      { '0', '1', '2', '3', '4', '5', '6', '7'
      , '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
   std::size_t char_counter = 0;
   for(std::size_t i = 0; i != static_cast<std::size_t>(BootstampLength); ++i){
      bootstamp_str[char_counter++] = Characters[(info.Reserved1[i]&0xF0)>>4];
      bootstamp_str[char_counter++] = Characters[(info.Reserved1[i]&0x0F)];
   }
   s = BootstampLength*2;
   return true;
}

inline void buffer_to_wide_str(const void *buf, std::size_t length, wchar_t *str)
{
   const wchar_t Characters [] =
      { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7'
      , L'8', L'9', L'A', L'B', L'C', L'D', L'E', L'F' };
   std::size_t char_counter = 0;
   const char *chbuf = static_cast<const char *>(buf);
   for(std::size_t i = 0; i != length; ++i){
      str[char_counter++] = Characters[(chbuf[i]&0xF0)>>4];
      str[char_counter++] = Characters[(chbuf[i]&0x0F)];
   }
}


inline bool get_boot_and_system_time_wstr(wchar_t *bootsystemstamp, std::size_t &s)  //will write BootAndSystemstampLength chars
{
   if(s < (BootAndSystemstampLength*2))
      return false;
   system_timeofday_information info;
   bool ret = get_system_time_of_day_information(info);
   if(!ret){
      return false;
   }

   buffer_to_wide_str(&info.Reserved1[0], BootAndSystemstampLength, bootsystemstamp);
   s = BootAndSystemstampLength*2;
   return true;
}

   explicit handle_closer(void *handle) : handle_(handle){}

   ~handle_closer()
   {  close_handle(handle_);  }

   explicit eventlog_handle_closer(void *handle) : handle_(handle){}

   ~eventlog_handle_closer()
   {  CloseEventLog(handle_);  }

   nt_query_mem_deleter(std::size_t object_name_information_size)
      : m_size(object_name_information_size + rename_offset + rename_suffix)
      , m_buf(new char [m_size])
   {}


   ~nt_query_mem_deleter()
   {
      delete[]m_buf;
   }


   void realloc(std::size_t num_bytes)
   {
      num_bytes += rename_suffix + rename_offset;
      char *buf = m_buf;
      m_buf = new char[num_bytes];
      delete[]buf;
      m_size = num_bytes;
   }


   ntquery_mem_t *query_mem() const
   {  return static_cast<ntquery_mem_t *>(static_cast<void*>(m_buf));  }
  

   unsigned long object_name_information_size() const
   {  return static_cast<unsigned long>(m_size - rename_offset - SystemTimeOfDayInfoLength*2);  }


   std::size_t file_rename_information_size() const
   {  return static_cast<unsigned long>(m_size);  }

   c_heap_deleter(std::size_t size)
      : m_buf(::malloc(size))
   {}


   ~c_heap_deleter()
   {
      if(m_buf) ::free(m_buf);
   }


   void realloc(std::size_t num_bytes)
   {
      void *buf = ::realloc(m_buf, num_bytes);
      if(!buf){
         free(m_buf);
         m_buf = 0;
      }
   }


   void *get() const
   {  return m_buf;  }


inline bool unlink_file(const char *filename)
{
   //Don't try to optimize doing a DeleteFile first
   //as there are interactions with permissions and
   //in-use files.
   //
   //if(!delete_file(filename)){
   //   (...)
   //

   //This functions tries to emulate UNIX unlink semantics in windows.
   //
   //- Open the file and mark the handle as delete-on-close
   //- Rename the file to an arbitrary name based on a random number
   //- Close the handle. If there are no file users, it will be deleted.
   //  Otherwise it will be used by already connected handles but the
   //  file name can't be used to open this file again
   try{
      NtSetInformationFile_t pNtSetInformationFile =
         (NtSetInformationFile_t)dll_func::get(dll_func::NtSetInformationFile);

      NtQueryObject_t pNtQueryObject = (NtQueryObject_t)dll_func::get(dll_func::NtQueryObject);

      //First step: Obtain a handle to the file using Win32 rules. This resolves relative paths
      void *fh = create_file(filename, generic_read | delete_access, open_existing, 0, 0);
      if(fh == invalid_handle_value){
         return false;
      }

      handle_closer h_closer(fh);
      {
         //Obtain name length
         unsigned long size;
         const std::size_t initial_string_mem = 512u;

         nt_query_mem_deleter nt_query_mem(sizeof(ntquery_mem_t)+initial_string_mem);
         //Obtain file name with guessed length
         if(pNtQueryObject(fh, object_name_information, nt_query_mem.query_mem(), nt_query_mem.object_name_information_size(), &size)){
            //Obtain file name with exact length buffer
            nt_query_mem.realloc(size);
            if(pNtQueryObject(fh, object_name_information, nt_query_mem.query_mem(), nt_query_mem.object_name_information_size(), &size)){
               return false;
            }
         }
         ntquery_mem_t *pmem = nt_query_mem.query_mem();
         file_rename_information_t *pfri = &pmem->ren.info;
         const std::size_t RenMaxNumChars =
            (((char*)(pmem) + nt_query_mem.file_rename_information_size()) - (char*)&pmem->ren.info.FileName[0])/sizeof(wchar_t);

         //Copy filename to the rename member
         std::memmove(pmem->ren.info.FileName, pmem->name.Name.Buffer, pmem->name.Name.Length);
         std::size_t filename_string_length = pmem->name.Name.Length/sizeof(wchar_t);

         //Search '\\' character to replace from it
         for(std::size_t i = filename_string_length; i != 0; --filename_string_length){
            if(pmem->ren.info.FileName[--i] == L'\\')
               break;
         }

         //Add random number
         std::size_t s = RenMaxNumChars - filename_string_length;
         if(!get_boot_and_system_time_wstr(&pfri->FileName[filename_string_length], s)){
            return false;
         }
         filename_string_length += s;

         //Sometimes the precission of the timestamp is not enough and we need to add another random number.
         //The process id (to exclude concurrent processes) and an atomic count (to exclude concurrent threads).
         //should be enough
         const unsigned long pid = get_current_process_id();
         buffer_to_wide_str(&pid, sizeof(pid), &pfri->FileName[filename_string_length]);
         filename_string_length += sizeof(pid)*2;

         static volatile boost::uint32_t u32_count = 0;
         interlocked_decrement(reinterpret_cast<volatile long*>(&u32_count));
         buffer_to_wide_str(const_cast<const boost::uint32_t *>(&u32_count), sizeof(boost::uint32_t), &pfri->FileName[filename_string_length]);
         filename_string_length += sizeof(boost::uint32_t)*2;

         //Fill rename information (FileNameLength is in bytes)
         pfri->FileNameLength = static_cast<unsigned long>(sizeof(wchar_t)*(filename_string_length));
         pfri->Replace = 1;
         pfri->RootDir = 0;

         //Cange the name of the in-use file...
         io_status_block_t io;
         if(0 != pNtSetInformationFile(fh, &io, pfri, nt_query_mem.file_rename_information_size(), file_rename_information)){
            return false;
         }
      }
      //...and mark it as delete-on-close
      {
         //Don't use pNtSetInformationFile with file_disposition_information as it can return STATUS_CANNOT_DELETE
         //if the file is still mapped. Reopen it with NtOpenFile and file_delete_on_close
         NtOpenFile_t pNtOpenFile = (NtOpenFile_t)dll_func::get(dll_func::NtOpenFile);
         NtClose_t pNtClose = (NtClose_t)dll_func::get(dll_func::NtClose);
         const wchar_t empty_str [] = L"";
         unicode_string_t ustring = { sizeof(empty_str) - sizeof (wchar_t)   //length in bytes without null
                                    , sizeof(empty_str)   //total size in bytes of memory allocated for Buffer.
                                    , const_cast<wchar_t*>(empty_str)
                                    };
         object_attributes_t object_attr;
	      initialize_object_attributes(&object_attr, &ustring, 0, fh, 0);
         void* fh2 = 0;
         io_status_block_t io;
         pNtOpenFile( &fh2, delete_flag, &object_attr, &io
                    , file_share_read | file_share_write | file_share_delete, file_delete_on_close);
         pNtClose(fh2);
         //Even if NtOpenFile fails, the file was renamed and the original no longer exists, so return a success status
         return true;
      }
   }
   catch(...){
      return false;
   }
   return true;
}

   reg_closer(void *key) : key_(key){}

   ~reg_closer(){ reg_close_key(key_);  }


inline void get_shared_documents_folder(std::string &s)
{
   s.clear();
   void *key;
   if (reg_open_key_ex( hkey_local_machine
                     , "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"
                     , 0
                     , key_query_value
                     , &key) == 0){
      reg_closer key_closer(key);

      //Obtain the value
      unsigned long size;
      unsigned long type;
      const char *const reg_value = "Common AppData";
      //long err = (*pRegQueryValue)( key, reg_value, 0, &type, 0, &size);
      long err = reg_query_value_ex( key, reg_value, 0, &type, 0, &size);
      if(!err){
         //Size includes terminating NULL
         s.resize(size);
         //err = (*pRegQueryValue)( key, reg_value, 0, &type, (unsigned char*)(&s[0]), &size);
         err = reg_query_value_ex( key, reg_value, 0, &type, (unsigned char*)(&s[0]), &size);
         if(!err)
            s.erase(s.end()-1);
         (void)err;
      }
   }
}


inline void get_registry_value(const char *folder, const char *value_key, std::vector<unsigned char> &s)
{
   s.clear();
   void *key;
   if (reg_open_key_ex( hkey_local_machine
                     , folder
                     , 0
                     , key_query_value
                     , &key) == 0){
      reg_closer key_closer(key);

      //Obtain the value
      unsigned long size;
      unsigned long type;
      const char *const reg_value = value_key;
      //long err = (*pRegQueryValue)( key, reg_value, 0, &type, 0, &size);
      long err = reg_query_value_ex( key, reg_value, 0, &type, 0, &size);
      if(!err){
         //Size includes terminating NULL
         s.resize(size);
         //err = (*pRegQueryValue)( key, reg_value, 0, &type, (unsigned char*)(&s[0]), &size);
         err = reg_query_value_ex( key, reg_value, 0, &type, (unsigned char*)(&s[0]), &size);
         if(!err)
            s.erase(s.end()-1);
         (void)err;
      }
   }
}

   co_uninitializer(bool b_uninitialize)
      : m_b_uninitialize(b_uninitialize)
   {}


   ~co_uninitializer()
   {
      if(m_b_uninitialize){
         CoUninitialize();
      }
   }

   com_releaser(Object *&object) : object_(object) {}

   ~com_releaser()  {  object_->Release();    object_ = 0;  }


inline bool get_wmi_class_attribute( std::wstring& strValue, const wchar_t *wmi_class, const wchar_t *wmi_class_var)
{
   //See example http://msdn.microsoft.com/en-us/library/aa390423%28v=VS.85%29.aspx
   //
   //See BOOST_INTERPROCESS_WINDOWS_COINIT_MODEL definition if you need to change the
   //default value of this macro in your application
   long co_init_ret = CoInitializeEx(0, BOOST_INTERPROCESS_WINDOWS_COINIT_MODEL);
   if(co_init_ret != S_OK_BIPC && co_init_ret != S_FALSE_BIPC && co_init_ret != RPC_E_CHANGED_MODE_BIPC)
      return false;
   co_uninitializer co_initialize_end(co_init_ret != RPC_E_CHANGED_MODE_BIPC);
   (void)co_initialize_end;

   bool bRet = false;
   long sec_init_ret = CoInitializeSecurity
      ( 0   //pVoid
      ,-1   //cAuthSvc
      , 0   //asAuthSvc
      , 0   //pReserved1
      , RPC_C_AUTHN_LEVEL_PKT_BIPC //dwAuthnLevel
      , RPC_C_IMP_LEVEL_IMPERSONATE_BIPC //dwImpLevel
      , 0   //pAuthList
      , EOAC_NONE_BIPC //dwCapabilities
      , 0   //pReserved3
      );
   if( 0 == sec_init_ret || RPC_E_TOO_LATE_BIPC == sec_init_ret)
   {
      IWbemLocator_BIPC * pIWbemLocator = 0;
      const wchar_t * bstrNamespace = L"root\\cimv2";

      if( 0 != CoCreateInstance(
            CLSID_WbemAdministrativeLocator,
            0,
            CLSCTX_INPROC_SERVER_BIPC | CLSCTX_LOCAL_SERVER_BIPC,
            IID_IUnknown, (void **)&pIWbemLocator)){
         return false;
      }

      com_releaser<IWbemLocator_BIPC> IWbemLocator_releaser(pIWbemLocator);

      IWbemServices_BIPC *pWbemServices = 0;

      if( 0 != pIWbemLocator->ConnectServer(
            bstrNamespace,  // Namespace
            0,          // Userid
            0,           // PW
            0,           // Locale
            0,              // flags
            0,           // Authority
            0,           // Context
            &pWbemServices
            )
         ){
         return false;
      }

      if( S_OK_BIPC != CoSetProxyBlanket(
            pWbemServices,
            RPC_C_AUTHN_DEFAULT_BIPC,
            RPC_C_AUTHZ_DEFAULT_BIPC,
            0,
            RPC_C_AUTHN_LEVEL_PKT_BIPC,
            RPC_C_IMP_LEVEL_IMPERSONATE_BIPC,
            0,
            EOAC_NONE_BIPC
            )
         ){
         return false;
      }

      com_releaser<IWbemServices_BIPC> IWbemServices_releaser(pWbemServices);

      strValue.clear();
      strValue += L"Select ";
      strValue += wmi_class_var;
      strValue += L" from ";
      strValue += wmi_class;

      IEnumWbemClassObject_BIPC * pEnumObject  = 0;

      if ( 0 != pWbemServices->ExecQuery(
            L"WQL",
            strValue.c_str(),
            //WBEM_FLAG_RETURN_IMMEDIATELY_BIPC,
            WBEM_FLAG_RETURN_WHEN_COMPLETE_BIPC | WBEM_FLAG_FORWARD_ONLY_BIPC,
            0,
            &pEnumObject
            )
         ){
         return false;
      }

      com_releaser<IEnumWbemClassObject_BIPC> IEnumWbemClassObject_releaser(pEnumObject);

      //WBEM_FLAG_FORWARD_ONLY_BIPC incompatible with Reset
      //if ( 0 != pEnumObject->Reset() ){
         //return false;
      //}

      wchar_variant vwchar;
      unsigned long uCount = 1, uReturned;
      IWbemClassObject_BIPC * pClassObject = 0;
      while( 0 == pEnumObject->Next( WBEM_INFINITE_BIPC, uCount, &pClassObject, &uReturned ) )
      {
         com_releaser<IWbemClassObject_BIPC> IWbemClassObject_releaser(pClassObject);
         if ( 0 == pClassObject->Get( L"LastBootUpTime", 0, &vwchar, 0, 0 ) ){
            bRet = true;
            strValue = vwchar.value.pbstrVal;
            VariantClear(&vwchar );
            break;
         }
      }
   }
   return bRet;
}

inline bool find_record_in_buffer( const void* pBuffer, unsigned long dwBytesRead, const char *provider_name
                                 , unsigned int id_to_find, interprocess_eventlogrecord *&pevent_log_record)
{
   const unsigned char * pRecord = static_cast<const unsigned char*>(pBuffer);
   const unsigned char * pEndOfRecords = pRecord + dwBytesRead;

   while (pRecord < pEndOfRecords){
      interprocess_eventlogrecord *pTypedRecord = (interprocess_eventlogrecord*)pRecord;
      // Check provider, written at the end of the fixed-part of the record
      if (0 == std::strcmp(provider_name, (char*)(pRecord + sizeof(interprocess_eventlogrecord))))
      {
         // Check event id
         if(id_to_find == (pTypedRecord->EventID & 0xFFFF)){
            pevent_log_record = pTypedRecord;
            return true;
         }
      }

      pRecord += pTypedRecord->Length;
   }
   pevent_log_record = 0;
   return false;
}

inline bool get_last_bootup_time(std::string &stamp)
{
   const char *source_name = "System";
   const char *provider_name = "EventLog";
   const unsigned short event_id = 6005u;

   unsigned long status = 0;
   unsigned long dwBytesToRead = 0;
   unsigned long dwBytesRead = 0;
   unsigned long dwMinimumBytesToRead = 0;

   // The source name (provider) must exist as a subkey of Application.
   void *hEventLog = OpenEventLogA(0, source_name);
   if (hEventLog){
      eventlog_handle_closer hnd_closer(hEventLog); (void)hnd_closer;
      // Allocate an initial block of memory used to read event records. The number 
      // of records read into the buffer will vary depending on the size of each event.
      // The size of each event will vary based on the size of the user-defined
      // data included with each event, the number and length of insertion 
      // strings, and other data appended to the end of the event record.
      dwBytesToRead = max_record_buffer_size;
      c_heap_deleter heap_deleter(dwBytesToRead);

      // Read blocks of records until you reach the end of the log or an 
      // error occurs. The records are read from newest to oldest. If the buffer
      // is not big enough to hold a complete event record, reallocate the buffer.
      if (heap_deleter.get() != 0){
         while (0 == status){
            if (!ReadEventLogA(hEventLog, 
                  eventlog_sequential_read | eventlog_backwards_read,
                  0, 
                  heap_deleter.get(),
                  dwBytesToRead,
                  &dwBytesRead,
                  &dwMinimumBytesToRead)) {
               status = get_last_error();
               if (error_insufficient_buffer == status) {
                  status = 0;
                  dwBytesToRead = dwMinimumBytesToRead;
                  heap_deleter.realloc(dwMinimumBytesToRead);
                  if (!heap_deleter.get()){
                     return false;
                  }
               }
               else{  //Not found or EOF
                  return false;
               }
            }
            else
            {
               interprocess_eventlogrecord *pTypedRecord;
               // Print the contents of each record in the buffer.
               if(find_record_in_buffer(heap_deleter.get(), dwBytesRead, provider_name, event_id, pTypedRecord)){
                  char stamp_str[sizeof(unsigned long)*3+1];
                  std::sprintf(&stamp_str[0], "%u", ((unsigned int)pTypedRecord->TimeGenerated));
                  stamp = stamp_str;
                  break;
               }
            }
         }
      }
   }
   return true;
}


inline bool is_directory(const char *path)
{
	unsigned long attrib = GetFileAttributesA(path);

	return (attrib != invalid_file_attributes &&
	        (attrib & file_attribute_directory));
}


inline bool get_file_mapping_size(void *file_mapping_hnd, __int64 &size)
{
   NtQuerySection_t pNtQuerySection =
      (NtQuerySection_t)dll_func::get(dll_func::NtQuerySection);
   //Obtain file name
   interprocess_section_basic_information info;
   unsigned long ntstatus =
      pNtQuerySection(file_mapping_hnd, section_basic_information, &info, sizeof(info), 0);
   if(ntstatus){
      return false;
   }
   size = info.section_size;
   return true;
}


inline bool get_semaphore_info(void *handle, long &count, long &limit)
{
   winapi::interprocess_semaphore_basic_information info;
   winapi::NtQuerySemaphore_t pNtQuerySemaphore =
         (winapi::NtQuerySemaphore_t)dll_func::get(winapi::dll_func::NtQuerySemaphore);
   unsigned int ret_len;
   long status = pNtQuerySemaphore(handle, winapi::semaphore_basic_information, &info, sizeof(info), &ret_len);
   if(status){
      return false;
   }
   count = info.count;
   limit = info.limit;
   return true;
}


inline void get_pid_creation_time_str(std::string &s)
{
   std::stringstream stream;
   stream << get_current_process_id() << '_';
   stream.precision(6);
   stream << std::fixed << get_current_process_creation_time();
   s = stream.str();
}


inline const char *get_map_base_name()
{  return "bip.gmem.map.";  }


inline void get_map_name(std::string &map_name)
{
   get_pid_creation_time_str(map_name);
   map_name.insert(0, get_map_base_name());
}


inline std::size_t get_map_size()
{  return 65536;  }

   static void initialize_singleton_logic
      (void *&ptr, volatile boost::uint32_t &this_module_singleton_initialized, singleton_constructor_t constructor, bool phoenix)
   {
      //If current module is not initialized enter to lock free logic
      if(atomic_read32(&this_module_singleton_initialized) != Initialized){
         //Now a single thread of the module will succeed in this CAS.
         //trying to pass from Uninitialized to Initializing
         ::boost::uint32_t previous_module_singleton_initialized = atomic_cas32
            (&this_module_singleton_initialized, Initializing, Uninitialized);
         //If the thread succeeded the CAS (winner) it will compete with other
         //winner threads from other modules to create the global map
         if(previous_module_singleton_initialized == Destroyed){
            //Trying to resurrect a dead Phoenix singleton. Just try to
            //mark it as uninitialized and start again
            if(phoenix){
               atomic_cas32(&this_module_singleton_initialized, Uninitialized, Destroyed);
               previous_module_singleton_initialized = atomic_cas32
                  (&this_module_singleton_initialized, Initializing, Uninitialized);
            }
            //Trying to resurrect a non-Phoenix dead singleton is an error
            else{
               throw interprocess_exception("Boost.Interprocess: Dead reference on non-Phoenix singleton of type");
            }
         }
         if(previous_module_singleton_initialized == Uninitialized){
            try{
               //Now initialize the global map, this function must solve concurrency
               //issues between threads of several modules
               initialize_global_map_handle();
               //Now try to create the singleton in global map.
               //This function solves concurrency issues
               //between threads of several modules
               void *tmp = constructor(get_map());
               //Increment the module reference count that reflects how many
               //singletons this module holds, so that we can safely destroy
               //module global map object when no singleton is left
               atomic_inc32(&this_module_singleton_count);
               //Insert a barrier before assigning the pointer to
               //make sure this assignment comes after the initialization
               atomic_write32(&this_module_singleton_initialized, Initializing);
               //Assign the singleton address to the module-local pointer
               ptr = tmp;
               //Memory barrier inserted, all previous operations should complete
               //before this one. Now marked as initialized
               atomic_write32(&this_module_singleton_initialized, Initialized);
            }
            catch(...){
               //Mark singleton failed to initialize
               atomic_write32(&this_module_singleton_initialized, Broken);
               throw;
            }
         }
         //If previous state was initializing, this means that another winner thread is
         //trying to initialize the singleton. Just wait until completes its work.
         else if(previous_module_singleton_initialized == Initializing){
            while(1){
               previous_module_singleton_initialized = atomic_read32(&this_module_singleton_initialized);
               if(previous_module_singleton_initialized >= Initialized){
                  //Already initialized, or exception thrown by initializer thread
                  break;
               }
               else if(previous_module_singleton_initialized == Initializing){
                  thread_yield();
               }
               else{
                  //This can't be happening!
                  BOOST_ASSERT(0);
               }
            }
         }
         else if(previous_module_singleton_initialized == Initialized){
            //Nothing to do here, the singleton is ready
         }
         //If previous state was greater than initialized, then memory is broken
         //trying to initialize the singleton.
         else{//(previous_module_singleton_initialized > Initialized)
            throw interprocess_exception("boost::interprocess::intermodule_singleton initialization failed");
         }
      }
      BOOST_ASSERT(ptr != 0);
   }


   static void finalize_singleton_logic(void *&ptr, volatile boost::uint32_t &this_module_singleton_initialized, singleton_destructor_t destructor)
   {
      //Protect destruction against lazy singletons not initialized in this execution
      if(ptr){
         //Note: this destructor might provoke a Phoenix singleton
         //resurrection. This means that this_module_singleton_count
         //might change after this call.
         destructor(ptr, get_map());
         ptr = 0;

         //Memory barrier to make sure pointer is nulled.
         //Mark this singleton as destroyed.
         atomic_write32(&this_module_singleton_initialized, Destroyed);

         //If this is the last singleton of this module
         //apply map destruction.
         //Note: singletons are destroyed when the module is unloaded
         //so no threads should be executing or holding references
         //to this module
         if(1 == atomic_dec32(&this_module_singleton_count)){
            destroy_global_map_handle();
         }
      }
   }

   static ThreadSafeGlobalMap &get_map()
   {
      return *static_cast<ThreadSafeGlobalMap *>(static_cast<void *>(&mem_holder.map_mem[0]));
   }


   static void initialize_global_map_handle()
   {
      //Obtain unique map name and size
      while(1){
         //Try to pass map state to initializing
         ::boost::uint32_t tmp = atomic_cas32(&this_module_map_initialized, Initializing, Uninitialized);
         if(tmp == Initialized || tmp == Broken){
            break;
         }
         else if(tmp == Destroyed){
            tmp = atomic_cas32(&this_module_map_initialized, Uninitialized, Destroyed);
            continue;
         }
         //If some other thread is doing the work wait
         else if(tmp == Initializing){
            thread_yield();
         }
         else{ //(tmp == Uninitialized)
            //If not initialized try it again?
            try{
               //Remove old global map from the system
               intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::remove_old_gmem();
               //in-place construction of the global map class
               intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::construct_map(static_cast<void*>(&get_map()));
               //Use global map's internal lock to initialize the lock file
               //that will mark this gmem as "in use".
               typename intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::
                  lock_file_logic f(get_map());
               //If function failed (maybe a competing process has erased the shared
               //memory between creation and file locking), retry with a new instance.
               if(f.retry()){
                  get_map().~ThreadSafeGlobalMap();
                  atomic_write32(&this_module_map_initialized, Destroyed);
               }
               else{
                  //Locking succeeded, so this global map module-instance is ready
                  atomic_write32(&this_module_map_initialized, Initialized);
                  break;
               }
            }
            catch(...){
               //
               throw;
            }
         }
      }
   }


   static void destroy_global_map_handle()
   {
      if(!atomic_read32(&this_module_singleton_count)){
         //This module is being unloaded, so destroy
         //the global map object of this module
         //and unlink the global map if it's the last
         typename intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::
            unlink_map_logic f(get_map());
         (get_map()).~ThreadSafeGlobalMap();
         atomic_write32(&this_module_map_initialized, Destroyed);
         //Do some cleanup for other processes old gmem instances
         intermodule_singleton_helpers::thread_safe_global_map_dependant<ThreadSafeGlobalMap>::remove_old_gmem();
      }
   }

   ref_count_ptr(void *p, boost::uint32_t count)
      : ptr(p), singleton_ref_count(count)
   {}


   static C& get()   //Let's make inlining easy
   {
      if(!this_module_singleton_ptr){
         if(lifetime.dummy_function()){  //This forces lifetime instantiation, for reference counted destruction
            atentry_work();
         }
      }
      return *static_cast<C*>(this_module_singleton_ptr);
   }


   static void atentry_work()
   {
      intermodule_singleton_common<ThreadSafeGlobalMap>::initialize_singleton_logic
         (this_module_singleton_ptr, this_module_singleton_initialized, singleton_constructor, Phoenix);
   }


   static void atexit_work()
   {
      intermodule_singleton_common<ThreadSafeGlobalMap>::finalize_singleton_logic
         (this_module_singleton_ptr, this_module_singleton_initialized, singleton_destructor);
   }

      bool dummy_function()
      {  return m_dummy == 0; }


      ~lifetime_type_lazy()
      {
         if(!Phoenix){
            atexit_work();
         }
      }

      lifetime_type_static()
      {  atentry_work();  }

      init_atomic_func(ThreadSafeGlobalMap &m)
         : m_map(m)
      {}


      void operator()()
      {
         ref_count_ptr *rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
            <ThreadSafeGlobalMap>::find(m_map, typeid(C).name());
         if(!rcount){
            C *p = new C;
            try{
               ref_count_ptr val(p, 0u);
               rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::insert(m_map, typeid(C).name(), val);
            }
            catch(...){
               intermodule_singleton_helpers::thread_safe_global_map_dependant
                           <ThreadSafeGlobalMap>::erase(m_map, typeid(C).name());
               delete p;
               throw;
            }
         }
         if(Phoenix){
            std::atexit(&atexit_work);
         }
         atomic_inc32(&rcount->singleton_ref_count);
         ret_ptr = rcount->ptr;
      }

      void *data() const
         { return ret_ptr;  }

      fini_atomic_func(ThreadSafeGlobalMap &m)
         : m_map(m)
      {}


      void operator()()
      {
         ref_count_ptr *rcount = intermodule_singleton_helpers::thread_safe_global_map_dependant
            <ThreadSafeGlobalMap>::find(m_map, typeid(C).name());
            //The object must exist
         BOOST_ASSERT(rcount);
         BOOST_ASSERT(rcount->singleton_ref_count > 0);
         //Check if last reference
         if(atomic_dec32(&rcount->singleton_ref_count) == 1){
            //If last, destroy the object
            BOOST_ASSERT(rcount->ptr != 0);
            C *pc = static_cast<C*>(rcount->ptr);
            //Now destroy map entry
            bool destroyed = intermodule_singleton_helpers::thread_safe_global_map_dependant
                        <ThreadSafeGlobalMap>::erase(m_map, typeid(C).name());
            (void)destroyed;  BOOST_ASSERT(destroyed == true);
            delete pc;
         }
      }

      void *data() const
         { return ret_ptr;  }

   static void *singleton_constructor(ThreadSafeGlobalMap &map)
   {
      init_atomic_func f(map);
      intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::atomic_func(map, f);
      return f.data();
   }

   static void singleton_destructor(void *p, ThreadSafeGlobalMap &map)
   {  (void)p;
      fini_atomic_func f(map);
      intermodule_singleton_helpers::thread_safe_global_map_dependant
                  <ThreadSafeGlobalMap>::atomic_func(map, f);
   }

inline boost::uint32_t atomic_add32
   (volatile boost::uint32_t *mem, boost::uint32_t val)
{
   // int r = *pw;
   // *mem += val;
   // return r;
   int r;

   asm volatile
   (
      "lock\n\t"
      "xadd %1, %0":
      "+m"( *mem ), "=r"( r ): // outputs (%0, %1)
      "1"( val ): // inputs (%2 == %1)
      "memory", "cc" // clobbers
   );

   return r;
}

inline boost::uint32_t atomic_dec32(volatile boost::uint32_t *mem)
{  return atomic_add32(mem, (boost::uint32_t)-1);  }


inline bool atomic_add_unless32
   (volatile boost::uint32_t *mem, boost::uint32_t value, boost::uint32_t unless_this)
{
   boost::uint32_t old, c(atomic_read32(mem));
   while(c != unless_this && (old = atomic_cas32(mem, c + value, c)) != c){
      c = old;
   }
   return c != unless_this;
}


   intersegment_base()
   {
      this->set_mode(is_pointee_outside);
      this->set_null();
   }


   void *relative_calculate_begin_addr() const
   {
      const std::size_t mask = ~(align - 1);
      std::size_t beg = this->members.relative.beg;
      return reinterpret_cast<void*>((((std::size_t)this) & mask) - (beg << align_bits));
   }


   void relative_set_begin_from_base(void *addr)
   {
      BOOST_ASSERT(addr < static_cast<void*>(this));
      std::size_t off = reinterpret_cast<char*>(this) - reinterpret_cast<char*>(addr);
      members.relative.beg = off >> align_bits;
   }

   std::size_t relative_size() const
   {
      std::size_t pow  = members.relative.pow;
      std::size_t size = (std::size_t(1u) << pow);
      BOOST_ASSERT(pow >= frc_size_bits);
      size |= members.relative.frc << (pow - frc_size_bits);
      return size;
   }


   static std::size_t calculate_size(std::size_t orig_size, std::size_t &pow, std::size_t &frc)
   {
      if(orig_size < align)
         orig_size = align;
      orig_size = ipcdetail::get_rounded_size_po2(orig_size, align);
      pow = ipcdetail::floor_log2(orig_size);
      std::size_t low_size = (std::size_t(1) << pow);
      std::size_t diff = orig_size - low_size;
      BOOST_ASSERT(pow >= frc_size_bits);
      std::size_t rounded = ipcdetail::get_rounded_size_po2
                              (diff, (std::size_t)(1u << (pow - frc_size_bits)));
      if(rounded == low_size){
         ++pow;
         frc = 0;
         rounded  = 0;
      }
      else{
         frc = rounded >> (pow - frc_size_bits);
      }
      BOOST_ASSERT(((frc << (pow - frc_size_bits)) & (align-1))==0);
      return low_size + rounded;
   }


   std::size_t get_mode()const
   {  return members.direct.ctrl;   }


   void set_mode(std::size_t mode)
   {
      BOOST_ASSERT(mode < is_max_mode);
      members.direct.ctrl = mode;
   }

   bool is_null() const
   {
      return   (this->get_mode() < is_relative) &&
               !members.direct.dummy &&
               !members.direct.addr;
   }

   void set_null()
   {
      if(this->get_mode() >= is_relative){
         this->set_mode(is_pointee_outside);
      }
      members.direct.dummy = 0;
      members.direct.addr  = 0;
   }


   static std::size_t round_size(std::size_t orig_size)
   {
      std::size_t pow, frc;
      return calculate_size(orig_size, pow, frc);
   }


   void set_from_pointer(const volatile void *ptr)
   {  this->set_from_pointer(const_cast<const void *>(ptr));  }

   void *to_raw_pointer() const
   {
      if(is_null()){
         return 0;
      }
      switch(this->get_mode()){
         case is_relative:
            return const_cast<char*>(reinterpret_cast<const char*>(this)) + members.relative.off;
         break;
         case is_segmented:
            {
            segment_info_t segment_info;
            std::size_t offset;
            void *this_base;
            get_segment_info_and_offset(this, segment_info, offset, this_base);
            char *base  = static_cast<char*>(segment_info.group->address_of(this->members.segmented.segment));
            return base + this->members.segmented.off;
            }
         break;
         case is_in_stack:
         case is_pointee_outside:
            return members.direct.addr;
         break;
         default:
         return 0;
         break;
      }
   }

   std::ptrdiff_t diff(const self_t &other) const
   {  return static_cast<char*>(this->to_raw_pointer()) - static_cast<char*>(other.to_raw_pointer());   }

   bool equal(const self_t &y) const
   {  return this->to_raw_pointer() == y.to_raw_pointer();  }

   bool less(const self_t &y) const
   {  return this->to_raw_pointer() < y.to_raw_pointer(); }


   void swap(self_t &other)
   {
      void *ptr_this  = this->to_raw_pointer();
      void *ptr_other = other.to_raw_pointer();
      other.set_from_pointer(ptr_this);
      this->set_from_pointer(ptr_other);
   }

   void set_from_pointer(const void *ptr)
   {
      if(!ptr){
         this->set_null();
         return;
      }

      std::size_t mode = this->get_mode();
      if(mode == is_in_stack){
         members.direct.addr = const_cast<void*>(ptr);
         return;
      }
      if(mode == is_relative){
         char *beg_addr = static_cast<char*>(this->relative_calculate_begin_addr());
         std::size_t seg_size = this->relative_size();
         if(ptr >= beg_addr && ptr < (beg_addr + seg_size)){
            members.relative.off = static_cast<const char*>(ptr) - reinterpret_cast<const char*>(this);
            return;
         }
      }
      std::size_t ptr_offset;
      std::size_t this_offset;
      segment_info_t ptr_info;
      segment_info_t this_info;
      void *ptr_base;
      void *this_base;
      get_segment_info_and_offset(this, this_info, this_offset, this_base);

      if(!this_info.group){
         this->set_mode(is_in_stack);
         this->members.direct.addr = const_cast<void*>(ptr);
      }
      else{
         get_segment_info_and_offset(ptr, ptr_info, ptr_offset, ptr_base);

         if(ptr_info.group != this_info.group){
            this->set_mode(is_pointee_outside);
            this->members.direct.addr =  const_cast<void*>(ptr);
         }
         else if(ptr_info.id == this_info.id){
            this->set_mode(is_relative);
            members.relative.off = (static_cast<const char*>(ptr) - reinterpret_cast<const char*>(this));
            this->relative_set_begin_from_base(this_base);
            std::size_t pow, frc;
            std::size_t s = calculate_size(this_info.size, pow, frc);
            (void)s;
            BOOST_ASSERT(this_info.size == s);
            this->members.relative.pow = pow;
            this->members.relative.frc = frc;
         }
         else{
            this->set_mode(is_segmented);
            this->members.segmented.segment = ptr_info.id;
            this->members.segmented.off     = ptr_offset;
         }
      }
   }

   void set_from_other(const self_t &other)
   {
      this->set_from_pointer(other.to_raw_pointer());
   }

   void inc_offset(std::ptrdiff_t bytes)
   {
      this->set_from_pointer(static_cast<char*>(this->to_raw_pointer()) + bytes);
   }

   void dec_offset(std::ptrdiff_t bytes)
   {
      this->set_from_pointer(static_cast<char*>(this->to_raw_pointer()) - bytes);
   }


   flat_map_intersegment()
      :  intersegment_base()
   {}


   ~flat_map_intersegment()
   {}

      segment_group_t(multi_segment_services &ms_services)
         :  m_ms_services(ms_services)
      {}


      void push_back(void *addr, std::size_t size)
      {
         segment_data d = { addr, size };
         m_segments.push_back(d);
      }


      void pop_back()
      {
         BOOST_ASSERT(!m_segments.empty());
         m_segments.erase(--m_segments.end());
      }



      void *address_of(std::size_t segment_id)
      {
         BOOST_ASSERT(segment_id < (std::size_t)m_segments.size());
         return m_segments[segment_id].addr;
      }


      void clear_segments()
      {  m_segments.clear();  }


      std::size_t get_size() const
      {  return m_segments.size();  }


      multi_segment_services &get_multi_segment_services() const
      {  return m_ms_services;   }

      segment_info_t()
         :  size(0), id(0), group(0)
      {}


      ~mappings_t()
      {
         //Check that all mappings have been erased
         BOOST_ASSERT(m_ptr_to_segment_info.empty());
      }

   static void get_segment_info_and_offset(const void *ptr, segment_info_t &segment, std::size_t &offset, void *&base)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------
      base = 0;
      if(s_map.m_ptr_to_segment_info.empty()){
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char*>(0);
         return;
      }
      //Find the first base address greater than ptr
      typename ptr_to_segment_info_t::iterator it
         = s_map.m_ptr_to_segment_info.upper_bound(ptr);
      if(it == s_map.m_ptr_to_segment_info.begin()){
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char *>(0);
      }
      //Go to the previous one
      --it;
      char *      segment_base = const_cast<char*>(reinterpret_cast<const char*>(it->first));
      std::size_t segment_size = it->second.size;

      if(segment_base <= reinterpret_cast<const char*>(ptr) &&
         (segment_base + segment_size) >= reinterpret_cast<const char*>(ptr)){
         segment = it->second;
         offset  = reinterpret_cast<const char*>(ptr) - segment_base;
         base = segment_base;
      }
      else{
         segment = segment_info_t();
         offset  = reinterpret_cast<const char*>(ptr) - static_cast<const char*>(0);
      }
   }

   static void insert_mapping(segment_group_id group_id, void *ptr, std::size_t size)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------

      typedef typename ptr_to_segment_info_t::value_type value_type;
      typedef typename ptr_to_segment_info_t::iterator   iterator;
      typedef std::pair<iterator, bool>                  it_b_t;

      segment_info_t info;
      info.group = group_id;
      info.size  = size;
      info.id    = group_id->get_size();

      it_b_t ret = s_map.m_ptr_to_segment_info.insert(value_type(ptr, info));
      BOOST_ASSERT(ret.second);

      value_eraser<ptr_to_segment_info_t> v_eraser(s_map.m_ptr_to_segment_info, ret.first);
      group_id->push_back(ptr, size);
      v_eraser.release();
   }


   static bool erase_last_mapping(segment_group_id group_id)
   {
      //------------------------------------------------------------------
      boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
      //------------------------------------------------------------------
      if(!group_id->get_size()){
         return false;
      }
      else{
         void *addr = group_id->address_of(group_id->get_size()-1);
         group_id->pop_back();
         std::size_t erased = s_map.m_ptr_to_segment_info.erase(addr);
         (void)erased;
         BOOST_ASSERT(erased);
         return true;
      }
   }


   static segment_group_id new_segment_group(multi_segment_services *services)
   {
      {  //------------------------------------------------------------------
         boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
         //------------------------------------------------------------------
         typedef typename segment_groups_t::iterator iterator;
         std::pair<iterator, bool> ret =
            s_groups.insert(segment_group_t(*services));
         BOOST_ASSERT(ret.second);
         return &*ret.first;
      }
   }


   static bool delete_group(segment_group_id id)
   {
      {  //------------------------------------------------------------------
         boost::interprocess::scoped_lock<typename mappings_t::mutex_type> lock(s_map);
         //------------------------------------------------------------------
         bool success = 1u == s_groups.erase(segment_group_t(*id));
         if(success){
            typedef typename ptr_to_segment_info_t::iterator ptr_to_segment_info_it;
            ptr_to_segment_info_it it(s_map.m_ptr_to_segment_info.begin());
            while(it != s_map.m_ptr_to_segment_info.end()){
               if(it->second.group == id){
                  it = s_map.m_ptr_to_segment_info.erase(it);
               }
               else{
                  ++it;
               }
            }
         }
         return success;
      }
   }


   void unspecified_bool_type_func() const {}

   intersegment_ptr(pointer ptr = 0)
   {  base_t::set_from_pointer(ptr);   }

   template <class U>
   intersegment_ptr(U *ptr){  base_t::set_from_pointer(pointer(ptr)); }

   intersegment_ptr(const intersegment_ptr& ptr)
   {  base_t::set_from_other(ptr);   }

   template<class T2>
   intersegment_ptr(const intersegment_ptr<T2> &ptr)
   {  pointer p(ptr.get());   (void)p; base_t::set_from_other(ptr); }

   pointer get()const
   {  return static_cast<pointer>(base_t::to_raw_pointer());   }

   pointer operator->() const
   {  return self_t::get(); }

   reference operator* () const
   {  return *(self_t::get());   }

   reference operator[](std::ptrdiff_t idx) const
   {  return self_t::get()[idx];  }

   intersegment_ptr& operator= (pointer from)
   {  base_t::set_from_pointer(from); return *this;  }

   intersegment_ptr& operator= (const intersegment_ptr &ptr)
   {  base_t::set_from_other(ptr);  return *this;  }

   template <class T2>
   intersegment_ptr& operator= (const intersegment_ptr<T2> & ptr)
   {
      pointer p(ptr.get());   (void)p;
      base_t::set_from_other(ptr); return *this;
   }

   intersegment_ptr operator+ (std::ptrdiff_t idx) const
   {
      intersegment_ptr result (*this);
      result.inc_offset(idx*sizeof(T));
      return result;
   }

   intersegment_ptr operator- (std::ptrdiff_t idx) const
   {
      intersegment_ptr result (*this);
      result.dec_offset(idx*sizeof(T));
      return result;
   }

   intersegment_ptr &operator+= (std::ptrdiff_t offset)
   {  base_t::inc_offset(offset*sizeof(T));  return *this;  }

   intersegment_ptr &operator-= (std::ptrdiff_t offset)
   {  base_t::dec_offset(offset*sizeof(T));  return *this;  }

   intersegment_ptr& operator++ (void)
   {  base_t::inc_offset(sizeof(T));   return *this;  }

   intersegment_ptr operator++ (int)
   {  intersegment_ptr temp(*this); ++*this; return temp; }

   intersegment_ptr& operator-- (void)
   {  base_t::dec_offset(sizeof(T));   return *this;  }

   intersegment_ptr operator-- (int)
   {  intersegment_ptr temp(*this); --*this; return temp; }

   operator unspecified_bool_type() const
   {  return base_t::is_null()? 0 : &self_t::unspecified_bool_type_func;   }

   bool operator! () const
   {  return base_t::is_null();   }

   void swap(intersegment_ptr &other)
   {  base_t::swap(other);   }

   template <class T2>
   std::ptrdiff_t _diff(const intersegment_ptr<T2> &other) const
   {  return base_t::diff(other);   }

   template <class T2>
   bool _equal(const intersegment_ptr<T2>&other) const
   {  return base_t::equal(other);   }

   template <class T2>
   bool _less(const intersegment_ptr<T2> &other) const
   {  return base_t::less(other);   }

template <class T1, class T2> inline
bool operator ==(const intersegment_ptr<T1> &left,
                 const intersegment_ptr<T2> &right)
{
   //Make sure both pointers can be compared
   bool e = typename intersegment_ptr<T1>::pointer(0) ==
            typename intersegment_ptr<T2>::pointer(0);
   (void)e;
   return left._equal(right);
}

template <class T1, class T2> inline
bool operator <(const intersegment_ptr<T1> &left,
                const intersegment_ptr<T2> &right)
{
   //Make sure both pointers can be compared
   bool e = typename intersegment_ptr<T1>::pointer(0) <
            typename intersegment_ptr<T2>::pointer(0);
   (void)e;
   return left._less(right);
}


template<class T1, class T2> inline
bool operator!= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 ==pt2);  }

template<class T1, class T2> inline
bool operator<= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 > pt2);  }

template<class T1, class T2> inline
bool operator> (const intersegment_ptr<T1> &pt1,
                       const intersegment_ptr<T2> &pt2)
{  return (pt2 < pt1);  }

template<class T1, class T2> inline
bool operator>= (const intersegment_ptr<T1> &pt1,
                 const intersegment_ptr<T2> &pt2)
{  return !(pt1 < pt2);  }

   template<class OtherPair>
   const typename Pair::first_type& operator()(const OtherPair& x) const
   {  return x.first;   }


   const typename Pair::first_type& operator()(const typename Pair::first_type& x) const
   {  return x;   }

   const T& operator()(const T& x) const
   { return x; }


inline multi_segment_services::~multi_segment_services()
{}


static void create_tmp_subdir_and_get_pid_based_filepath
   (const char *subdir_name, const char *file_prefix, OS_process_id_t pid, std::string &s, bool creation_time = false)
{
   //Let's create a lock file for each process gmem that will mark if
   //the process is alive or not
   create_tmp_and_clean_old(s);
   s += "/";
   s += subdir_name;
   if(!open_or_create_directory(s.c_str())){
      throw interprocess_exception(error_info(system_error_code()));
   }
   s += "/";
   s += file_prefix;
   if(creation_time){
      std::string sstamp;
      get_pid_creation_time_str(sstamp);
      s += sstamp;
   }
   else{
      pid_str_t pid_str;
      get_pid_str(pid_str, pid);
      s += pid_str;
   }
}


static bool check_if_filename_complies_with_pid
   (const char *filename, const char *prefix, OS_process_id_t pid, std::string &file_suffix, bool creation_time = false)
{
   //Check if filename complies with lock file name pattern
   std::string fname(filename);
   std::string fprefix(prefix);
   if(fname.size() <= fprefix.size()){
      return false;
   }
   fname.resize(fprefix.size());
   if(fname != fprefix){
      return false;
   }

   //If not our lock file, delete it if we can lock it
   fname = filename;
   fname.erase(0, fprefix.size());
   pid_str_t pid_str;
   get_pid_str(pid_str, pid);
   file_suffix = pid_str;
   if(creation_time){
      std::size_t p = fname.find('_');
      if (p == std::string::npos){
         return false;
      }
      std::string save_suffix(fname);
      fname.erase(p);
      fname.swap(file_suffix);
      bool ret = (file_suffix == fname);
      file_suffix.swap(save_suffix);
      return ret;
   }
   else{
      fname.swap(file_suffix);
      return (file_suffix == fname);
   }
}


   static const char *get_lock_file_subdir_name()
   {  return "gmem";  }


   static const char *get_lock_file_base_name()
   {  return "lck";  }


   static void create_and_get_singleton_lock_file_path(std::string &s)
   {
      create_tmp_subdir_and_get_pid_based_filepath
         (get_lock_file_subdir_name(), get_lock_file_base_name(), get_current_process_id(), s, true);
   }

      gmem_erase_func(const char *shm_name, const char *singleton_lock_file_path, managed_global_memory & shm)
         :shm_name_(shm_name), singleton_lock_file_path_(singleton_lock_file_path), shm_(shm)
      {}


      void operator()()
      {
         locking_file_serial_id *pserial_id = shm_.find<locking_file_serial_id>("lock_file_fd").first;
         if(pserial_id){
            pserial_id->fd = GMemMarkToBeRemoved;
         }
         delete_file(singleton_lock_file_path_);
         shared_memory_object::remove(shm_name_);
      }

   static void apply_gmem_erase_logic(const char *filepath, const char *filename)
   {
      int fd = GMemMarkToBeRemoved;
      try{
         std::string str;
         //If the filename is current process lock file, then avoid it
         if(check_if_filename_complies_with_pid
            (filename, get_lock_file_base_name(), get_current_process_id(), str, true)){
            return;
         }
         //Open and lock the other process' lock file
         fd = try_open_and_lock_file(filepath);
         if(fd < 0){
            return;
         }
         //If done, then the process is dead so take global shared memory name
         //(the name is based on the lock file name) and try to apply erasure logic
         str.insert(0, get_map_base_name());
         try{
            managed_global_memory shm(open_only, str.c_str());
            gmem_erase_func func(str.c_str(), filepath, shm);
            shm.try_atomic_func(func);
         }
         catch(interprocess_exception &e){
            //If shared memory is not found erase the lock file
            if(e.get_error_code() == not_found_error){
               delete_file(filepath);
            }
         }
      }
      catch(...){

      }
      if(fd >= 0){
         close_lock_file(fd);
      }
   }


   static bool remove_old_gmem()
   {
      std::string refcstrRootDirectory;
      tmp_folder(refcstrRootDirectory);
      refcstrRootDirectory += "/";
      refcstrRootDirectory += get_lock_file_subdir_name();
      return for_each_file_in_dir(refcstrRootDirectory.c_str(), apply_gmem_erase_logic);
   }

      lock_file_logic(managed_global_memory &shm)
         : mshm(shm)
      {  shm.atomic_func(*this); }


      void operator()(void)
      {
         retry_with_new_map = false;

         //First find the file locking descriptor id
         locking_file_serial_id *pserial_id =
            mshm.find<locking_file_serial_id>("lock_file_fd").first;

         int fd;
         //If not found schedule a creation
         if(!pserial_id){
            fd = GMemNotPresent;
         }
         //Else get it
         else{
            fd = pserial_id->fd;
         }
         //If we need to create a new one, do it
         if(fd == GMemNotPresent){
            std::string lck_str;
            //Create a unique current pid based lock file path
            create_and_get_singleton_lock_file_path(lck_str);
            //Open or create and lock file
            int fd_lockfile = open_or_create_and_lock_file(lck_str.c_str());
            //If failed, write a bad file descriptor to notify other modules that
            //something was wrong and unlink shared memory. Mark the function object
            //to tell caller to retry with another shared memory
            if(fd_lockfile < 0){
               this->register_lock_file(GMemMarkToBeRemoved);
               std::string s;
               get_map_name(s);
               shared_memory_object::remove(s.c_str());
               retry_with_new_map = true;
            }
            //If successful, register the file descriptor
            else{
               this->register_lock_file(fd_lockfile);
            }
         }
         //If the fd was invalid (maybe a previous try failed) notify caller that
         //should retry creation logic, since this shm might have been already
         //unlinked since the shm was removed
         else if (fd == GMemMarkToBeRemoved){
            retry_with_new_map = true;
         }
         //If the stored fd is not valid (a open fd, a normal file with the
         //expected size, or does not have the same file id number,
         //then it's an old shm from an old process with the same pid.
         //If that's the case, mark it as invalid
         else if(!is_valid_fd(fd) ||
               !is_normal_file(fd) ||
               0 != get_size(fd) ||
               !compare_file_serial(fd, *pserial_id)){
            pserial_id->fd = GMemMarkToBeRemoved;
            std::string s;
            get_map_name(s);
            shared_memory_object::remove(s.c_str());
            retry_with_new_map = true;
         }
         else{
            //If the lock file is ok, increment reference count of
            //attached modules to shared memory
            atomic_inc32(&pserial_id->modules_attached_to_gmem_count);
         }
      }


      bool retry() const { return retry_with_new_map; }

      locking_file_serial_id * register_lock_file(int fd)
      {
         locking_file_serial_id *pinfo = mshm.construct<locking_file_serial_id>("lock_file_fd")();
         fill_file_serial_id(fd, *pinfo);
         return pinfo;
      }


   static void construct_map(void *addr)
   {
      std::string s;
      intermodule_singleton_helpers::get_map_name(s);
      const char *MapName = s.c_str();
      const std::size_t MapSize = intermodule_singleton_helpers::get_map_size();;
      ::new (addr)managed_global_memory(open_or_create, MapName, MapSize);
   }

      unlink_map_logic(managed_global_memory &mshm)
         : mshm_(mshm)
      {  mshm.atomic_func(*this);  }


      void operator()()
      {
         locking_file_serial_id *pserial_id =
            mshm_.find<locking_file_serial_id>
               ("lock_file_fd").first;
         BOOST_ASSERT(0 != pserial_id);
         if(1 == atomic_dec32(&pserial_id->modules_attached_to_gmem_count)){
            int fd = pserial_id->fd;
            if(fd > 0){
               pserial_id->fd = GMemMarkToBeRemoved;
               std::string s;
               create_and_get_singleton_lock_file_path(s);
               delete_file(s.c_str());
               close_lock_file(fd);
               intermodule_singleton_helpers::get_map_name(s);
               shared_memory_object::remove(s.c_str());
            }
         }
      }


   static ref_count_ptr *find(managed_global_memory &map, const char *name)
   {
      return map.find<ref_count_ptr>(name).first;
   }


   static ref_count_ptr *insert(managed_global_memory &map, const char *name, const ref_count_ptr &ref)
   {
      return map.construct<ref_count_ptr>(name)(ref);
   }


   static bool erase(managed_global_memory &map, const char *name)
   {
      return map.destroy<ref_count_ptr>(name);
   }


   template<class F>
   static void atomic_func(managed_global_memory &map, F &f)
   {
      map.atomic_func(f);
   }


inline void get_tmp_base_dir(std::string &tmp_name)
{
   #if defined (BOOST_INTERPROCESS_WINDOWS)
      winapi::get_shared_documents_folder(tmp_name);
      if(tmp_name.empty() || !winapi::is_directory(tmp_name.c_str())){
         tmp_name = get_temporary_path();
      }
   #else
      tmp_name = get_temporary_path();
   #endif
   if(tmp_name.empty()){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   //Remove final null.
   tmp_name += "/boost_interprocess";
}


inline void tmp_folder(std::string &tmp_name)
{
   get_tmp_base_dir(tmp_name);
   #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
      tmp_name += "/";
      get_bootstamp(tmp_name, true);
   #endif
}


inline void tmp_filename(const char *filename, std::string &tmp_name)
{
   tmp_folder(tmp_name);
   tmp_name += "/";
   tmp_name += filename;
}


inline void create_tmp_and_clean_old(std::string &tmp_name)
{
   //First get the temp directory
   std::string root_tmp_name;
   get_tmp_base_dir(root_tmp_name);

   //If fails, check that it's because already exists
   if(!create_directory(root_tmp_name.c_str())){
      error_info info(system_error_code());
      if(info.get_error_code() != already_exists_error){
         throw interprocess_exception(info);
      }
   }

   #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
      tmp_folder(tmp_name);

      //If fails, check that it's because already exists
      if(!create_directory(tmp_name.c_str())){
         error_info info(system_error_code());
         if(info.get_error_code() != already_exists_error){
            throw interprocess_exception(info);
         }
      }
      //Now erase all old directories created in the previous boot sessions
      std::string subdir = tmp_name;
      subdir.erase(0, root_tmp_name.size()+1);
      delete_subdirectories(root_tmp_name, subdir.c_str());
   #else
      tmp_name = root_tmp_name;
   #endif
}


inline void create_tmp_and_clean_old_and_get_filename(const char *filename, std::string &tmp_name)
{
   create_tmp_and_clean_old(tmp_name);
   tmp_name += "/";
   tmp_name += filename;
}


inline void add_leading_slash(const char *name, std::string &new_name)
{
   if(name[0] != '/'){
      new_name = '/';
   }
   new_name += name;
}

   static void take_ownership(T &t)
   {  t.take_ownership(); }


inline void remove_if_can_lock_file(const char *file_path)
{
   file_handle_t fhnd = open_existing_file(file_path, read_write);

   if(fhnd != invalid_file()){
      bool acquired;
      if(try_acquire_file_lock(fhnd, acquired) && acquired){
         delete_file(file_path);
      }
      close_file(fhnd);
   }
}


inline const char *robust_lock_subdir_path()
{  return "robust"; }


inline const char *robust_lock_prefix()
{  return "lck"; }


inline void robust_lock_path(std::string &s)
{
   tmp_folder(s);
   s += "/";
   s += robust_lock_subdir_path();
}


inline void create_and_get_robust_lock_file_path(std::string &s, OS_process_id_t pid)
{
   intermodule_singleton_helpers::create_tmp_subdir_and_get_pid_based_filepath
      (robust_lock_subdir_path(), robust_lock_prefix(), pid, s);
}

   robust_mutex_lock_file()
   {
      permissions p;
      p.set_unrestricted();
      //Remove old lock files of other processes
      remove_old_robust_lock_files();
      //Create path and obtain lock file path for this process
      create_and_get_robust_lock_file_path(fname, get_current_process_id());

      //Now try to open or create the lock file
      fd = create_or_open_file(fname.c_str(), read_write, p);
      //If we can't open or create it, then something unrecoverable has happened
      if(fd == invalid_file()){
         throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: could not open or create file");
      }

      //Now we must take in care a race condition with another process
      //calling "remove_old_robust_lock_files()". No other threads from this
      //process will be creating the lock file because intermodule_singleton
      //guarantees this. So let's loop acquiring the lock and checking if we
      //can't exclusively create the file (if the file is erased by another process
      //then this exclusive open would fail). If the file can't be exclusively created
      //then we have correctly open/create and lock the file. If the file can
      //be exclusively created, then close previous locked file and try again.
      while(1){
         bool acquired;
         if(!try_acquire_file_lock(fd, acquired) || !acquired ){
            throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: try_acquire_file_lock");
         }
         //Creating exclusively must fail with already_exists_error
         //to make sure we've locked the file and no one has
         //deleted it between creation and locking
         file_handle_t fd2 = create_new_file(fname.c_str(), read_write, p);
         if(fd2 != invalid_file()){
            close_file(fd);
            fd = fd2;
            continue;
         }
         //If exclusive creation fails with expected error go ahead
         else if(error_info(system_error_code()).get_error_code() == already_exists_error){ //must already exist
            //Leak descriptor to mantain the file locked until the process dies
            break;
         }
         //If exclusive creation fails with unexpected error throw an unrecoverable error
         else{
            close_file(fd);
            throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: create_file filed with unexpected error");
         }
      }
   }


   ~robust_mutex_lock_file()
   {
      //The destructor is guaranteed by intermodule_singleton to be
      //executed serialized between all threads from current process,
      //so we just need to close and unlink the file.
      close_file(fd);
      //If some other process deletes the file before us after
      //closing it there should not be any problem.
      delete_file(fname.c_str());
   }

      void operator()(const char *filepath, const char *filename)
      {
         std::string pid_str;
         //If the lock file is not our own lock file, then try to do the cleanup
         if(!intermodule_singleton_helpers::check_if_filename_complies_with_pid
            (filename, robust_lock_prefix(), get_current_process_id(), pid_str)){
            remove_if_can_lock_file(filepath);
         }
      }


   bool remove_old_robust_lock_files()
   {
      std::string refcstrRootDirectory;
      robust_lock_path(refcstrRootDirectory);
      return for_each_file_in_dir(refcstrRootDirectory.c_str(), other_process_lock_remover());
   }


template<class Mutex>
inline robust_spin_mutex<Mutex>::robust_spin_mutex()
   : mtx(), owner(get_invalid_process_id()), state(correct_state)
{}


template<class Mutex>
inline void robust_spin_mutex<Mutex>::lock()
{
   //If the mutex is broken (recovery didn't call consistent()),
   //then throw an exception
   if(atomic_read32(&this->state) == broken_state){
      throw interprocess_exception(lock_error, "Broken id");
   }

   //This function provokes intermodule_singleton instantiation
   if(!this->lock_own_unique_file()){
      throw interprocess_exception(lock_error, "Broken id");
   }

   //Now the logic. Try to lock, if successful mark the owner
   //if it fails, start recovery logic
   unsigned int spin_count = 0;
   while(1){
      if (mtx.try_lock()){
         atomic_write32(&this->owner, get_current_process_id());
         break;
      }
      else{
         //Do the dead owner checking each spin_threshold lock tries
         ipcdetail::thread_yield();
         ++spin_count;
         if(spin_count > spin_threshold){
            //Check if owner dead and take ownership if possible
            if(!this->robust_check()){
               spin_count = 0;
            }
            else{
               break;
            }
         }
      }
   }
}


template<class Mutex>
inline bool robust_spin_mutex<Mutex>::try_lock()
{
   //Same as lock() but without spinning
   if(atomic_read32(&this->state) == broken_state){
      throw interprocess_exception(lock_error, "Broken id");
   }

   if(!this->lock_own_unique_file()){
      throw interprocess_exception(lock_error, "Broken id");
   }

   if (mtx.try_lock()){
      atomic_write32(&this->owner, get_current_process_id());
      return true;
   }
   else{
      if(!this->robust_check()){
         return false;
      }
      else{
         return true;
      }
   }
}


template<class Mutex>
inline bool robust_spin_mutex<Mutex>::robust_check()
{
   //If the old owner was dead, and we've acquired ownership, mark
   //the mutex as 'fixing'. This means that a "consistent()" is needed
   //to avoid marking the mutex as "broken" when the mutex is unlocked.
   if(!this->check_if_owner_dead_and_take_ownership_atomically()){
      return false;
   }
   atomic_write32(&this->state, fixing_state);
   return true;
}


template<class Mutex>
inline bool robust_spin_mutex<Mutex>::check_if_owner_dead_and_take_ownership_atomically()
{
   boost::uint32_t cur_owner = get_current_process_id();
   boost::uint32_t old_owner = atomic_read32(&this->owner), old_owner2;
   //The cas loop guarantees that only one thread from this or another process
   //will succeed taking ownership
   do{
      //Check if owner is dead
      if(!this->is_owner_dead(old_owner)){
         return false;
      }
      //If it's dead, try to mark this process as the owner in the owner field
      old_owner2 = old_owner;
      old_owner = atomic_cas32(&this->owner, cur_owner, old_owner);
   }while(old_owner2 != old_owner);
   //If success, we fix mutex internals to assure our ownership
   mutex_traits_t::take_ownership(mtx);
   return true;
}


template<class Mutex>
inline void robust_spin_mutex<Mutex>::consistent()
{
   //This function supposes the previous state was "fixing"
   //and the current process holds the mutex
   if(atomic_read32(&this->state) != fixing_state &&
      atomic_read32(&this->owner) != (boost::uint32_t)get_current_process_id()){
      throw interprocess_exception(lock_error, "Broken id");
   }
   //If that's the case, just update mutex state
   atomic_write32(&this->state, correct_state);
}


template<class Mutex>
inline bool robust_spin_mutex<Mutex>::previous_owner_dead()
{
   //Notifies if a owner recovery has been performed in the last lock()
   return atomic_read32(&this->state) == fixing_state;
};


template<class Mutex>
inline void robust_spin_mutex<Mutex>::unlock()
{
   //If in "fixing" state, unlock and mark the mutex as unrecoverable
   //so next locks will fail and all threads will be notified that the
   //data protected by the mutex was not recoverable.
   if(atomic_read32(&this->state) == fixing_state){
      atomic_write32(&this->state, broken_state);
   }
   //Write an invalid owner to minimize pid reuse possibility
   atomic_write32(&this->owner, get_invalid_process_id());
   mtx.unlock();
}


template<class Mutex>
inline bool robust_spin_mutex<Mutex>::lock_own_unique_file()
{
   //This function forces instantiation of the singleton
   robust_emulation_helpers::robust_mutex_lock_file* dummy =
      &ipcdetail::intermodule_singleton
         <robust_emulation_helpers::robust_mutex_lock_file>::get();
   return dummy != 0;
}


template <class T>
inline T* to_raw_pointer(T* p)
{  return p; }

template <class T>
inline void do_swap(T& x, T& y)
{
   using std::swap;
   swap(x, y);
}

template<class SizeType>
inline SizeType get_rounded_size(SizeType orig_size, SizeType round_to)
{
   return ((orig_size-1)/round_to+1)*round_to;
}

template<class SizeType>
inline SizeType get_truncated_size(SizeType orig_size, SizeType multiple)
{
   return orig_size/multiple*multiple;
}

template<class SizeType>
inline SizeType get_rounded_size_po2(SizeType orig_size, SizeType round_to)
{
   return ((orig_size-1)&(~(round_to-1))) + round_to;
}

template<class SizeType>
inline SizeType get_truncated_size_po2(SizeType orig_size, SizeType multiple)
{
   return (orig_size & (~(multiple-1)));
}


template <typename T> T*
addressof(T& v)
{
  return reinterpret_cast<T*>(
       &const_cast<char&>(reinterpret_cast<const volatile char &>(v)));
}


template<class SizeType>
inline bool multiplication_overflows(SizeType a, SizeType b)
{
   const SizeType sqrt_size_max = sqrt_size_type_max<SizeType>::value;
   return   //Fast runtime check 
         (  (a | b) > sqrt_size_max &&
            //Slow division check 
            b && a > SizeType(-1)/b
         );
}


template<std::size_t SztSizeOfType, class SizeType>
inline bool size_overflows(SizeType count)
{
   //Compile time-check
   BOOST_STATIC_ASSERT(SztSizeOfType <= SizeType(-1));
   //Runtime check
   return multiplication_overflows(SizeType(SztSizeOfType), count);
}

   explicit pointer_size_t_caster(std::size_t sz)
      : m_ptr(reinterpret_cast<RawPointer>(sz))
   {}


   explicit pointer_size_t_caster(RawPointer p)
      : m_ptr(p)
   {}


   std::size_t size() const
   {   return reinterpret_cast<std::size_t>(m_ptr);   }


   RawPointer pointer() const
   {   return m_ptr;   }



template<class SizeType>
inline bool sum_overflows(SizeType a, SizeType b)
{  return SizeType(-1) - a < b;  }

   value_eraser(Cont & cont, typename Cont::iterator it)
      : m_cont(cont), m_index_it(it), m_erase(true){}

   ~value_eraser()
   {  if(m_erase) m_cont.erase(m_index_it);  }


   void release() {  m_erase = false;  }

   windows_semaphore_based_map()
   {
      map_type *m = new map_type;
      boost::uint32_t initial_count = 0;
      boost::uint32_t max_count = 0;

      //Windows user address space sizes:
      //32 bit windows: [32 bit processes] 2GB or 3GB (31/32 bits)
      //64 bit windows: [32 bit processes] 2GB or 4GB (31/32 bits)
      //                [64 bit processes] 2GB or 8TB (31/43 bits)
      //
      //Windows semaphores use 'long' parameters (32 bits in LLP64 data model) and
      //those values can't be negative, so we have 31 bits to store something
      //in max_count and initial count parameters.
      //Also, max count must be bigger than 0 and bigger or equal than initial count.
      if(sizeof(void*) == sizeof(boost::uint32_t)){
         //This means that for 32 bit processes, a semaphore count (31 usable bits) is
         //enough to store 4 byte aligned memory (4GB -> 32 bits - 2 bits = 30 bits).
         //The max count will hold the pointer value and current semaphore count
         //will be zero.
         //
         //Relying in UB with a cast through union, but all known windows compilers
         //accept this (C11 also accepts this).
         union caster_union
         {
            void *addr;
            boost::uint32_t addr_uint32;
         } caster;
         caster.addr = m;
         //memory is at least 4 byte aligned in windows
         BOOST_ASSERT((caster.addr_uint32 & boost::uint32_t(3)) == 0);
         max_count = caster.addr_uint32 >> 2;
      }
      else if(sizeof(void*) == sizeof(boost::uint64_t)){
         //Relying in UB with a cast through union, but all known windows compilers
         //accept this (C11 accepts this).
         union caster_union
         {
            void *addr;
            boost::uint64_t addr_uint64;
         } caster;
         caster.addr = m;
         //We'll encode the address using 30 bits in each 32 bit high and low parts.
         //High part will be the sem max count, low part will be the sem initial count.
         //(restrictions: max count > 0, initial count >= 0 and max count >= initial count):
         //
         // - Low part will be shifted two times (4 byte alignment) so that top
         //   two bits are cleared (the top one for sign, the next one to
         //   assure low part value is always less than the high part value.
         // - The top bit of the high part will be cleared and the next bit will be 1
         //   (so high part is always bigger than low part due to the quasi-top bit).
         //
         //   This means that the addresses we can store must be 4 byte aligned
         //   and less than 1 ExbiBytes ( 2^60 bytes, ~1 ExaByte). User-level address space in Windows 64
         //   is much less than this (8TB, 2^43 bytes): "1 EByte (or it was 640K?) ought to be enough for anybody" ;-).
         caster.addr = m;
         BOOST_ASSERT((caster.addr_uint64 & boost::uint64_t(3)) == 0);
         max_count = boost::uint32_t(caster.addr_uint64 >> 32);
         initial_count = boost::uint32_t(caster.addr_uint64);
         initial_count = initial_count/4;
         //Make sure top two bits are zero
         BOOST_ASSERT((max_count & boost::uint32_t(0xC0000000)) == 0);
         //Set quasi-top bit
         max_count |= boost::uint32_t(0x40000000);
      }
      bool created = false;
      const permissions & perm = permissions();
      std::string pid_creation_time, name;
      get_pid_creation_time_str(pid_creation_time);
      name = "bipc_gmap_sem_lock_";
      name += pid_creation_time;
      bool success = m_mtx_lock.open_or_create(name.c_str(), perm);
      name = "bipc_gmap_sem_count_";
      name += pid_creation_time;
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      {
         success = success && m_sem_count.open_or_create
            ( name.c_str(), static_cast<long>(0), winapi_semaphore_wrapper::MaxCount, perm, created);
         name = "bipc_gmap_sem_map_";
         name += pid_creation_time;
         success = success && m_sem_map.open_or_create
            (name.c_str(), initial_count, max_count, perm, created);
         if(!success){
            //winapi_xxx wrappers do the cleanup...
            throw int(0);
         }
         if(!created){
            delete m;
         }
         else{
            BOOST_ASSERT(&get_map_unlocked() == m);
         }
         m_sem_count.post();
      }
   }


   map_type &get_map_unlocked()
   {
      if(sizeof(void*) == sizeof(boost::uint32_t)){
         union caster_union
         {
            void *addr;
            boost::uint32_t addr_uint32;
         } caster;
         caster.addr = 0;
         caster.addr_uint32 = m_sem_map.limit();
         caster.addr_uint32 = caster.addr_uint32 << 2;
         return *static_cast<map_type*>(caster.addr);
      }
      else{
         union caster_union
         {
            void *addr;
            boost::uint64_t addr_uint64;
         } caster;
         boost::uint32_t max_count(m_sem_map.limit()), initial_count(m_sem_map.value());
         //Clear quasi-top bit
         max_count &= boost::uint32_t(0xBFFFFFFF);
         caster.addr_uint64 = max_count;
         caster.addr_uint64 =  caster.addr_uint64 << 32;
         caster.addr_uint64 |= boost::uint64_t(initial_count) << 2;
         return *static_cast<map_type*>(caster.addr);
      }
   }


   ref_count_ptr *find(const char *name)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      map_type::iterator it = map.find(std::string(name));
      if(it != map.end()){
         return &it->second;
      }
      else{
         return 0;
      }
   }


   ref_count_ptr * insert(const char *name, const ref_count_ptr &ref)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      map_type::iterator it = map.insert(map_type::value_type(std::string(name), ref)).first;
      return &it->second;
   }


   bool erase(const char *name)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      return map.erase(std::string(name)) != 0;
   }


   template<class F>
   void atomic_func(F &f)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      f();
   }


   ~windows_semaphore_based_map()
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      m_sem_count.wait();
      if(0 == m_sem_count.value()){
         delete &this->get_map_unlocked();
      }
      //First close sems to protect this with the external mutex
      m_sem_map.close();
      m_sem_count.close();
      //Once scoped_lock unlocks the mutex, the destructor will close the handle...
   }

   static void apply_gmem_erase_logic(const char *, const char *){}


   static bool remove_old_gmem()
   { return true; }

      lock_file_logic(windows_semaphore_based_map &)
         : retry_with_new_map(false)
      {}


      void operator()(void){}

      bool retry() const { return retry_with_new_map; }


   static void construct_map(void *addr)
   {
      ::new (addr)windows_semaphore_based_map;
   }

      unlink_map_logic(windows_semaphore_based_map &)
      {}

      void operator()(){}


   static ref_count_ptr *find(windows_semaphore_based_map &map, const char *name)
   {
      return map.find(name);
   }


   static ref_count_ptr * insert(windows_semaphore_based_map &map, const char *name, const ref_count_ptr &ref)
   {
      return map.insert(name, ref);
   }


   static bool erase(windows_semaphore_based_map &map, const char *name)
   {
      return map.erase(name);
   }


   template<class F>
   static void atomic_func(windows_semaphore_based_map &map, F &f)
   {
      map.atomic_func(f);
   }

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

   OS_systemwide_thread_id_t()
      :  pid(), tid()
   {}


   OS_systemwide_thread_id_t(const OS_systemwide_thread_id_t &x)
      :  pid(x.pid), tid(x.tid)
   {}


   OS_systemwide_thread_id_t(const volatile OS_systemwide_thread_id_t &x)
      :  pid(x.pid), tid(x.tid)
   {}


   OS_systemwide_thread_id_t & operator=(const OS_systemwide_thread_id_t &x)
   {  pid = x.pid;   tid = x.tid;   return *this;   }


   OS_systemwide_thread_id_t & operator=(const volatile OS_systemwide_thread_id_t &x)
   {  pid = x.pid;   tid = x.tid;   return *this;  }


   void operator=(const OS_systemwide_thread_id_t &x) volatile
   {  pid = x.pid;   tid = x.tid;   }


inline void systemwide_thread_id_copy
   (const volatile OS_systemwide_thread_id_t &from, volatile OS_systemwide_thread_id_t &to)
{
   to.pid = from.pid;
   to.tid = from.tid;
}

inline OS_process_id_t get_current_process_id()
{  return ::getpid();  }


inline OS_process_id_t get_invalid_process_id()
{  return pid_t(0);  }

inline OS_thread_id_t get_current_thread_id()
{  return ::pthread_self();  }


inline OS_thread_id_t get_invalid_thread_id()
{
   static pthread_t invalid_id;
   return invalid_id;
}


inline bool equal_thread_id(OS_thread_id_t id1, OS_thread_id_t id2)
{  return 0 != pthread_equal(id1, id2);  }


inline void thread_yield()
{  ::sched_yield();  }


inline void thread_sleep(unsigned int ms)
{
   const struct timespec rqt = { ms/1000u, (ms%1000u)*1000000u  };
   ::nanosleep(&rqt, 0);
}

inline OS_systemwide_thread_id_t get_current_systemwide_thread_id()
{
   return OS_systemwide_thread_id_t(::getpid(), ::pthread_self());
}


inline bool equal_systemwide_thread_id(const OS_systemwide_thread_id_t &id1, const OS_systemwide_thread_id_t &id2)
{
   return (0 != pthread_equal(id1.tid, id2.tid)) && (id1.pid == id2.pid);
}


inline OS_systemwide_thread_id_t get_invalid_systemwide_thread_id()
{
   return OS_systemwide_thread_id_t(get_invalid_process_id(), get_invalid_thread_id());
}


inline long double get_current_process_creation_time()
{ return 0.0L; }


inline void get_pid_str(pid_str_t &pid_str, OS_process_id_t pid)
{
   bufferstream bstream(pid_str, sizeof(pid_str));
   bstream << pid << std::ends;
}


inline void get_pid_str(pid_str_t &pid_str)
{  get_pid_str(pid_str, get_current_process_id());  }

   in_place_interface(std::size_t alignm, std::size_t sz, const char *tname)
   :  alignment(alignm), size(sz), type_name(tname)
   {}

   virtual ~in_place_interface(){}

   placement_destroy()
	   :  in_place_interface(::boost::alignment_of<T>::value, sizeof(T), typeid(T).name())
   {}


   virtual void destroy_n(void *mem, std::size_t num, std::size_t &destroyed)
   {
      T* memory = static_cast<T*>(mem);
      for(destroyed = 0; destroyed < num; ++destroyed)
         (memory++)->~T();
   }


   virtual void construct_n(void *, std::size_t, std::size_t &) {}

   void destroy(void *mem)
   {  static_cast<T*>(mem)->~T();   }


inline mapping_handle_t mapping_handle_from_file_handle(file_handle_t hnd)
{
   mapping_handle_t ret;
   ret.handle = hnd;
   ret.is_xsi = false;
   return ret;
}


inline file_handle_t file_handle_from_mapping_handle(mapping_handle_t hnd)
{  return hnd.handle; }


inline bool create_directory(const char *path)
{  return ::mkdir(path, 0777) == 0 && ::chmod(path, 0777) == 0; }


inline const char *get_temporary_path()
{
   const char *names[] = {"/tmp", "TMPDIR", "TMP", "TEMP" };
   const int names_size = sizeof(names)/sizeof(names[0]);
   struct stat data;
   for(int i = 0; i != names_size; ++i){
      if(::stat(names[i], &data) == 0){
         return names[i];
      }
   }
   return "/tmp";
}


inline file_handle_t create_new_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   (void)temporary;
   int ret = ::open(name, ((int)mode) | O_EXCL | O_CREAT, perm.get_permissions());
   if(ret >= 0){
      ::fchmod(ret, perm.get_permissions());
   }
   return ret;
}


inline file_handle_t create_or_open_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   (void)temporary;
   int ret = -1;
   //We need a loop to change permissions correctly using fchmod, since
   //with "O_CREAT only" ::open we don't know if we've created or opened the file.
   while(1){
      ret = ::open(name, ((int)mode) | O_EXCL | O_CREAT, perm.get_permissions());
      if(ret >= 0){
         ::fchmod(ret, perm.get_permissions());
         break;
      }
      else if(errno == EEXIST){
         if((ret = ::open(name, (int)mode)) >= 0 || errno != ENOENT){
            break;
         }
      }
   }
   return ret;
}


inline file_handle_t open_existing_file
   (const char *name, mode_t mode, bool temporary = false)
{
   (void)temporary;
   return ::open(name, (int)mode);
}


inline bool delete_file(const char *name)
{  return ::unlink(name) == 0;   }


inline bool truncate_file (file_handle_t hnd, std::size_t size)
{
   typedef boost::make_unsigned<off_t>::type uoff_t;
   if(uoff_t((std::numeric_limits<off_t>::max)()) < size){
      errno = EINVAL;
      return false;
   }
   return 0 == ::ftruncate(hnd, off_t(size));
}


inline bool get_file_size(file_handle_t hnd, offset_t &size)
{
   struct stat data;
   bool ret = 0 == ::fstat(hnd, &data);
   if(ret){
      size = data.st_size;
   }
   return ret;
}


inline bool set_file_pointer(file_handle_t hnd, offset_t off, file_pos_t pos)
{  return ((off_t)(-1)) != ::lseek(hnd, off, (int)pos); }


inline bool get_file_pointer(file_handle_t hnd, offset_t &off)
{
   off = ::lseek(hnd, 0, SEEK_CUR);
   return off != ((off_t)-1);
}


inline bool write_file(file_handle_t hnd, const void *data, std::size_t numdata)
{  return (ssize_t(numdata)) == ::write(hnd, data, numdata);  }


inline file_handle_t invalid_file()
{  return -1;  }


inline bool close_file(file_handle_t hnd)
{  return ::close(hnd) == 0;   }


inline bool acquire_file_lock(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}


inline bool try_acquire_file_lock(file_handle_t hnd, bool &acquired)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno == EAGAIN || errno == EACCES) ?
               acquired = false, true : false;
   }
   return (acquired = true);
}


inline bool release_file_lock(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_UNLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLK, &lock);
}


inline bool acquire_file_lock_sharable(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}


inline bool try_acquire_file_lock_sharable(file_handle_t hnd, bool &acquired)
{
   struct flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno == EAGAIN || errno == EACCES) ?
               acquired = false, true : false;
   }
   return (acquired = true);
}


inline bool release_file_lock_sharable(file_handle_t hnd)
{  return release_file_lock(hnd);   }


inline bool delete_subdirectories_recursive
   (const std::string &refcstrRootDirectory, const char *dont_delete_this)
{
   DIR *d = opendir(refcstrRootDirectory.c_str());
   if(!d) {
      return false;
   }

   struct dir_close
   {
      DIR *d_;
      dir_close(DIR *d) : d_(d) {}
      ~dir_close() { ::closedir(d_); }
   } dc(d); (void)dc;

   struct ::dirent *de;
   struct ::stat st;
   std::string fn;

   while((de=::readdir(d))) {
      if( de->d_name[0] == '.' && ( de->d_name[1] == '\0'
            || (de->d_name[1] == '.' && de->d_name[2] == '\0' )) ){
         continue;
      }
      if(dont_delete_this && std::strcmp(dont_delete_this, de->d_name) == 0){
         continue;
      }
      fn = refcstrRootDirectory;
      fn += '/';
      fn += de->d_name;

      if(std::remove(fn.c_str())) {
         if(::stat(fn.c_str(), & st)) {
            return false;
         }
         if(S_ISDIR(st.st_mode)) {
            if(!delete_subdirectories_recursive(fn, 0) ){
               return false;
            }
         } else {
            return false;
         }
      }
   }
   return std::remove(refcstrRootDirectory.c_str()) ? false : true;
}

      dir_close(DIR *d) : d_(d) {}

      ~dir_close() { ::closedir(d_); }

      dir_close(DIR *d) : d_(d) {}

      ~dir_close() { ::closedir(d_); }


template<class Function>
inline bool for_each_file_in_dir(const char *dir, Function f)
{
   std::string refcstrRootDirectory(dir);

   DIR *d = opendir(refcstrRootDirectory.c_str());
   if(!d) {
      return false;
   }

   struct dir_close
   {
      DIR *d_;
      dir_close(DIR *d) : d_(d) {}
      ~dir_close() { ::closedir(d_); }
   } dc(d); (void)dc;

   struct ::dirent *de;
   struct ::stat st;
   std::string fn;

   while((de=::readdir(d))) {
      if( de->d_name[0] == '.' && ( de->d_name[1] == '\0'
            || (de->d_name[1] == '.' && de->d_name[2] == '\0' )) ){
         continue;
      }
      fn = refcstrRootDirectory;
      fn += '/';
      fn += de->d_name;

      if(::stat(fn.c_str(), & st)) {
         return false;
      }
      //If it's a file, apply erase logic
      if(!S_ISDIR(st.st_mode)) {
         f(fn.c_str(), de->d_name);
      }
   }
   return true;
}

      dir_close(DIR *d) : d_(d) {}

      ~dir_close() { ::closedir(d_); }

      dir_close(DIR *d) : d_(d) {}

      ~dir_close() { ::closedir(d_); }

inline bool delete_subdirectories(const std::string &refcstrRootDirectory, const char *dont_delete_this)
{
   return delete_subdirectories_recursive(refcstrRootDirectory, dont_delete_this );
}


inline bool open_or_create_directory(const char *dir_name)
{
   //If fails, check that it's because it already exists
   if(!create_directory(dir_name)){
      error_info info(system_error_code());
      if(info.get_error_code() != already_exists_error){
         return false;
      }
   }
   return true;
}

   void * data(){ return this+1; }

   bool operator()(const msg_hdr_ptr_t &msg1,
                   const msg_hdr_ptr_t &msg2) const
      {  return msg1->priority < msg2->priority;  }

   mq_hdr_t(size_type max_num_msg, size_type max_msg_size)
      : m_max_num_msg(max_num_msg),
         m_max_msg_size(max_msg_size),
         m_cur_num_msg(0)
         #if defined(BOOST_INTERPROCESS_MSG_QUEUE_CIRCULAR_INDEX)
         ,m_cur_first_msg(0u)
         #endif
      {  this->initialize_memory();  }

   bool is_full() const
      {  return m_cur_num_msg == m_max_num_msg;  }

   bool is_empty() const
      {  return !m_cur_num_msg;  }

   void free_top_msg()
      {  --m_cur_num_msg;  }

   msg_header &top_msg()
      {  return *mp_index[m_cur_num_msg-1];   }

   msg_header &bottom_msg()
      {  return *mp_index[0];   }


   iterator inserted_ptr_begin() const
   {  return &mp_index[0]; }


   iterator inserted_ptr_end() const
   {  return &mp_index[m_cur_num_msg]; }


   iterator lower_bound(const msg_hdr_ptr_t & value, priority_functor<VoidPointer> func)
   {  return std::lower_bound(this->inserted_ptr_begin(), this->inserted_ptr_end(), value, func);  }


   msg_header & insert_at(iterator pos)
   {
      const msg_hdr_ptr_t backup = *inserted_ptr_end();
      std::copy_backward(pos, inserted_ptr_end(), inserted_ptr_end()+1);
      *pos = backup;
      ++m_cur_num_msg;
      return **pos;
   }

   msg_header & queue_free_msg(unsigned int priority)
   {
      //Get priority queue's range
      iterator it  (inserted_ptr_begin()), it_end(inserted_ptr_end());
      //Optimize for non-priority usage
      if(m_cur_num_msg && priority > this->bottom_msg().priority){
         //Check for higher priority than all stored messages
         if(priority > this->top_msg().priority){
            it = it_end;
         }
         else{
            //Since we don't now which free message we will pick
            //build a dummy header for searches
            msg_header dummy_hdr;
            dummy_hdr.priority = priority;

            //Get free msg
            msg_hdr_ptr_t dummy_ptr(&dummy_hdr);

            //Check where the free message should be placed
            it = this->lower_bound(dummy_ptr, static_cast<priority_functor<VoidPointer>&>(*this));
         }
         
      }
      //Insert the free message in the correct position
      return this->insert_at(it);
   }

   static size_type get_mem_size
      (size_type max_msg_size, size_type max_num_msg)
   {
      const size_type
		 msg_hdr_align  = ::boost::alignment_of<msg_header>::value,
		 index_align    = ::boost::alignment_of<msg_hdr_ptr_t>::value,
         r_hdr_size     = ipcdetail::ct_rounded_size<sizeof(mq_hdr_t), index_align>::value,
         r_index_size   = ipcdetail::get_rounded_size(max_num_msg*sizeof(msg_hdr_ptr_t), msg_hdr_align),
         r_max_msg_size = ipcdetail::get_rounded_size(max_msg_size, msg_hdr_align) + sizeof(msg_header);
      return r_hdr_size + r_index_size + (max_num_msg*r_max_msg_size) +
         open_create_impl_t::ManagedOpenOrCreateUserOffset;
   }

   void initialize_memory()
   {
      const size_type
		  msg_hdr_align  = ::boost::alignment_of<msg_header>::value,
		  index_align    = ::boost::alignment_of<msg_hdr_ptr_t>::value,
         r_hdr_size     = ipcdetail::ct_rounded_size<sizeof(mq_hdr_t), index_align>::value,
         r_index_size   = ipcdetail::get_rounded_size(m_max_num_msg*sizeof(msg_hdr_ptr_t), msg_hdr_align),
         r_max_msg_size = ipcdetail::get_rounded_size(m_max_msg_size, msg_hdr_align) + sizeof(msg_header);

      //Pointer to the index
      msg_hdr_ptr_t *index =  reinterpret_cast<msg_hdr_ptr_t*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size);

      //Pointer to the first message header
      msg_header *msg_hdr   =  reinterpret_cast<msg_header*>
                                 (reinterpret_cast<char*>(this)+r_hdr_size+r_index_size);

      //Initialize the pointer to the index
      mp_index             = index;

      //Initialize the index so each slot points to a preallocated message
      for(size_type i = 0; i < m_max_num_msg; ++i){
         index[i] = msg_hdr;
         msg_hdr  = reinterpret_cast<msg_header*>
                        (reinterpret_cast<char*>(msg_hdr)+r_max_msg_size);
      }
   }


   msg_queue_initialization_func_t(size_type maxmsg = 0,
                         size_type maxmsgsize = 0)
      : m_maxmsg (maxmsg), m_maxmsgsize(maxmsgsize) {}


   bool operator()(void *address, size_type, bool created)
   {
      char      *mptr;

      if(created){
         mptr     = reinterpret_cast<char*>(address);
         //Construct the message queue header at the beginning
         BOOST_TRY{
            new (mptr) mq_hdr_t<VoidPointer>(m_maxmsg, m_maxmsgsize);
         }
         BOOST_CATCH(...){
            return false;
         }
         BOOST_CATCH_END
      }
      return true;
   }


   std::size_t get_min_size() const
   {
      return mq_hdr_t<VoidPointer>::get_mem_size(m_maxmsgsize, m_maxmsg)
      - message_queue_t<VoidPointer>::open_create_impl_t::ManagedOpenOrCreateUserOffset;
   }


template<class VoidPointer>
inline message_queue_t<VoidPointer>::~message_queue_t()
{}


template<class VoidPointer>
inline bool message_queue_t<VoidPointer>::remove(const char *name)
{  return shared_memory_object::remove(name);  }

   const_iterator begin() const
   {  return const_iterator(0);  }

   iterator begin()
   {  return iterator(0);  }

   const_iterator end() const
   {  return const_iterator(0);  }

   iterator end()
   {  return iterator(0);  }

   null_index(segment_manager_base *){}

        std::size_t operator()(const key_type &val) const
        {
            typedef typename key_type::char_type    char_type;
            const char_type *beg = ipcdetail::to_raw_pointer(val.mp_str),
                            *end = beg + val.m_len;
            return boost::hash_range(beg, end);
        }

   unordered_map_index(segment_manager_base *segment_mngr)
      : base_type(0,
                  typename index_aux::hasher(),
                  typename index_aux::key_equal(),
                  segment_mngr){}

   void reserve(typename segment_manager_base::size_type n)
   {  base_type::rehash(n);  }

   void shrink_to_fit()
   {  base_type::rehash(base_type::size()); }

   flat_map_index(segment_manager_base *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  typename index_aux::allocator_type(segment_mngr))
   {}

   void reserve(typename segment_manager_base::size_type n)
   {  base_type::reserve(n);  }

   void shrink_to_fit()
   {  base_type::shrink_to_fit();   }

   map_index(segment_manager_base *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  segment_mngr){}

   void reserve(typename segment_manager_base::size_type)
      {  /*Does nothing, map has not reserve or rehash*/  }

   void shrink_to_fit()
   {  base_type::get_stored_allocator().deallocate_free_blocks(); }

      bool operator()(const intrusive_compare_key_type &i, const value_type &b) const
      {
         return (i.m_len == b.name_length()) &&
                  (std::char_traits<char_type>::compare
                     (i.mp_str, b.name(), i.m_len) == 0);
      }

        std::size_t operator()(const value_type &val) const
        {
            const char_type *beg = ipcdetail::to_raw_pointer(val.name()),
                            *end = beg + val.name_length();
            return boost::hash_range(beg, end);
        }

      allocator_holder(segment_manager_base *mngr)
         :  alloc(mngr)
      {}


   static bucket_ptr create_buckets(allocator_type &alloc, size_type num)
   {
      num = index_type::suggested_upper_bucket_count(num);
      bucket_ptr buckets = alloc.allocate(num);
      bucket_ptr buckets_init = buckets;
      for(size_type i = 0; i < num; ++i){
         new(to_raw_pointer(buckets_init++))bucket_type();
      }
      return buckets;
   }


   static size_type shrink_buckets
      ( bucket_ptr buckets, size_type old_size
      , allocator_type &alloc, size_type new_size)
   {
      if(old_size <= new_size )
         return old_size;
      size_type received_size;
      if(!alloc.allocation_command
         (boost::interprocess::try_shrink_in_place | boost::interprocess::nothrow_allocation, old_size, new_size, received_size, buckets).first){
         return old_size;
      }

      for( bucket_type *p = ipcdetail::to_raw_pointer(buckets) + received_size
         , *pend = ipcdetail::to_raw_pointer(buckets) + old_size
         ; p != pend
         ; ++p){
         p->~bucket_type();
      }

      bucket_ptr shunk_p = alloc.allocation_command
         (boost::interprocess::shrink_in_place | boost::interprocess::nothrow_allocation, received_size, received_size, received_size, buckets).first;
      BOOST_ASSERT(buckets == shunk_p); (void)shunk_p;

      bucket_ptr buckets_init = buckets + received_size;
      for(size_type i = 0; i < (old_size - received_size); ++i){
         to_raw_pointer(buckets_init++)->~bucket_type();
      }
      return received_size;
   }


   static bucket_ptr expand_or_create_buckets
      ( bucket_ptr old_buckets, const size_type old_num
      , allocator_type &alloc,  const size_type new_num)
   {
      size_type received_size;
      std::pair<bucket_ptr, bool> ret =
         alloc.allocation_command
            (boost::interprocess::expand_fwd | boost::interprocess::allocate_new, new_num, new_num, received_size, old_buckets);
      if(ret.first == old_buckets){
         bucket_ptr buckets_init = old_buckets + old_num;
         for(size_type i = 0; i < (new_num - old_num); ++i){
            new(to_raw_pointer(buckets_init++))bucket_type();
         }
      }
      else{
         bucket_ptr buckets_init = ret.first;
         for(size_type i = 0; i < new_num; ++i){
            new(to_raw_pointer(buckets_init++))bucket_type();
         }
      }

      return ret.first;
   }


   static void destroy_buckets
      (allocator_type &alloc, bucket_ptr buckets, size_type num)
   {
      bucket_ptr buckets_destroy = buckets;
      for(size_type i = 0; i < num; ++i){
         to_raw_pointer(buckets_destroy++)->~bucket_type();
      }
      alloc.deallocate(buckets, num);
   }


   iunordered_set_index<MapConfig>* get_this_pointer()
   {  return this;   }

   iunordered_set_index(segment_manager_base *mngr)
      :  allocator_holder(mngr)
      ,  index_type(bucket_traits(&get_this_pointer()->init_bucket, 1))
   {}


   ~iunordered_set_index()
   {
      index_type::clear();
      if(index_type::bucket_pointer() != bucket_ptr(&this->init_bucket)){
         destroy_buckets(this->alloc, index_type::bucket_pointer(), index_type::bucket_count());
      }
   }

   void reserve(size_type new_n)
   {
      //Let's maintain a 1.0f load factor
      size_type old_n  = this->bucket_count();
      if(new_n <= old_n)
         return;
      bucket_ptr old_p = this->bucket_pointer();
      new_n = index_type::suggested_upper_bucket_count(new_n);
      bucket_ptr new_p;
      //This can throw
      try{
         if(old_p != bucket_ptr(&this->init_bucket))
            new_p = expand_or_create_buckets(old_p, old_n, this->alloc, new_n);
         else
            new_p = create_buckets(this->alloc, new_n);
      }
      catch(...){
         return;
      }
      //Rehashing does not throw, since neither the hash nor the
      //comparison function can throw
      this->rehash(bucket_traits(new_p, new_n));
      if(new_p != old_p && old_p != bucket_ptr(&this->init_bucket)){
         destroy_buckets(this->alloc, old_p, old_n);
      }
   }

   void shrink_to_fit()
   {
      size_type cur_size   = this->size();
      size_type cur_count  = this->bucket_count();
      bucket_ptr old_p = this->bucket_pointer();

      if(!this->size() && old_p != bucket_ptr(&this->init_bucket)){
         this->rehash(bucket_traits(bucket_ptr(&this->init_bucket), 1));
         destroy_buckets(this->alloc, old_p, cur_count);
      }
      else{
         size_type sug_count = 0; //gcc warning
         sug_count = index_type::suggested_upper_bucket_count(cur_size);

         if(sug_count >= cur_count)
            return;

         try{
            shrink_buckets(old_p, cur_count, this->alloc, sug_count);
         }
         catch(...){
            return;
         }

         //Rehashing does not throw, since neither the hash nor the
         //comparison function can throw
         this->rehash(bucket_traits(old_p, sug_count));
      }
   }


   iterator find(const intrusive_compare_key_type &key)
   {  return index_type::find(key, hash_function(), equal_function());  }


   const_iterator find(const intrusive_compare_key_type &key) const
   {  return index_type::find(key, hash_function(), equal_function());  }

      bool operator()(const intrusive_compare_key_type &i, const value_type &b) const
      {
         std::size_t blen = b.name_length();
         return (i.m_len < blen) ||
                  (i.m_len == blen &&
                  std::char_traits<char_type>::compare
                     (i.mp_str, b.name(), i.m_len) < 0);
      }


      bool operator()(const value_type &b, const intrusive_compare_key_type &i) const
      {
         std::size_t blen = b.name_length();
         return (blen < i.m_len) ||
                  (blen == i.m_len &&
                  std::char_traits<char_type>::compare
                     (b.name(), i.mp_str, i.m_len) < 0);
      }

   iset_index(typename MapConfig::segment_manager_base *)
      : index_type(/*typename index_aux::value_compare()*/)
   {}

   void reserve(typename MapConfig::segment_manager_base::size_type)
   {  /*Does nothing, map has not reserve or rehash*/  }

   void shrink_to_fit()
   {  /*Does nothing, this intrusive index does not allocate memory;*/   }


   iterator find(const intrusive_compare_key_type &key)
   {  return index_type::find(key, intrusive_key_value_less());  }


   const_iterator find(const intrusive_compare_key_type &key) const
   {  return index_type::find(key, intrusive_key_value_less());  }

   ~scoped_ptr()
   {
      if(m_ptr){
         Deleter &del = static_cast<Deleter&>(*this);
         del(m_ptr);
      }
   }

   void reset(const pointer &p = 0) // never throws
   {  BOOST_ASSERT(p == 0 || p != m_ptr); this_type(p).swap(*this);  }

   pointer release()
   {  pointer tmp(m_ptr);  m_ptr = 0;  return tmp; }

   reference operator*() const
   {  BOOST_ASSERT(m_ptr != 0);  return *m_ptr; }

   pointer &operator->()
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   pointer & get()
   {  return m_ptr;  }

   operator unspecified_bool_type() const
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   bool operator! () const // never throws
   {  return m_ptr == 0;   }

   void swap(scoped_ptr & b) // never throws
   {  ipcdetail::do_swap<Deleter>(*this, b); ipcdetail::do_swap(m_ptr, b.m_ptr); }

template<class T, class D> inline
void swap(scoped_ptr<T, D> & a, scoped_ptr<T, D> & b)
{  a.swap(b); }

template<class T, class D> inline
typename scoped_ptr<T, D>::pointer to_raw_pointer(scoped_ptr<T, D> const & p)
{  return p.get();   }

   deleter(segment_manager_pointer pmngr)
      :  mp_mngr(pmngr)
   {}


   void operator()(const pointer &p)
   {  mp_mngr->destroy_ptr(ipcdetail::to_raw_pointer(p));   }


template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator==(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a.get() == b.get(); }


template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator!=(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a.get() != b.get(); }


template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator<(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a._internal_less(b);   }


template<class T, class VoidAllocator, class Deleter> inline
void swap(shared_ptr<T, VoidAllocator, Deleter> & a, shared_ptr<T, VoidAllocator, Deleter> & b)
{  a.swap(b);  }


template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> static_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::static_cast_tag());   }


template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> const_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::const_cast_tag()); }


template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> dynamic_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::dynamic_cast_tag());  }

template<class T, class VoidAllocator, class Deleter> inline
T * to_raw_pointer(shared_ptr<T, VoidAllocator, Deleter> const & p)
{  return p.get();   }

   make_managed_shared_ptr(T *constructed_object, ManagedMemory &managed_memory, std::nothrow_t)
{
   try{
      return typename managed_shared_ptr<T, ManagedMemory>::type
      ( constructed_object
      , managed_memory.template get_allocator<void>()
      , managed_memory.template get_deleter<T>()
      );
   }
   catch(...){
      return typename managed_shared_ptr<T, ManagedMemory>::type();
   }
}

   enable_shared_from_this()
   {}


   enable_shared_from_this(enable_shared_from_this const &)
   {}


   enable_shared_from_this & operator=(enable_shared_from_this const &)
   {  return *this;  }


   ~enable_shared_from_this()
   {}

   weak_ptr()
   : m_pn() // never throws
   {}

   template<class Y>
   weak_ptr(weak_ptr<Y, A, D> const & r)
      : m_pn(r.m_pn) // never throws
   {
      //Construct a temporary shared_ptr so that nobody
      //can destroy the value while constructing this
      const shared_ptr<T, A, D> &ref = r.lock();
      m_pn.set_pointer(ref.get());
   }

   template<class Y>
   weak_ptr & operator=(weak_ptr<Y, A, D> const & r) // never throws
   {
      //Construct a temporary shared_ptr so that nobody
      //can destroy the value while constructing this
      const shared_ptr<T, A, D> &ref = r.lock();
      m_pn = r.m_pn;
      m_pn.set_pointer(ref.get());
      return *this;
   }


template<class T, class A, class D, class U, class A2, class D2> inline
bool operator<(weak_ptr<T, A, D> const & a, weak_ptr<U, A2, D2> const & b)
{  return a._internal_less(b);   }


template<class T, class A, class D> inline
void swap(weak_ptr<T, A, D> & a, weak_ptr<T, A, D> & b)
{  a.swap(b);  }

template<class T, class ManagedMemory>
inline typename managed_weak_ptr<T, ManagedMemory>::type
   make_managed_weak_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_weak_ptr<T, ManagedMemory>::type
   ( constructed_object
   , managed_memory.template get_allocator<void>()
   , managed_memory.template get_deleter<T>()
   );
}

   intrusive_ptr(): m_ptr(0)
   {}

   intrusive_ptr(intrusive_ptr const & rhs)
      :  m_ptr(rhs.m_ptr)
   {
      if(m_ptr != 0) intrusive_ptr_add_ref(ipcdetail::to_raw_pointer(m_ptr));
   }

   template<class U> intrusive_ptr
      (intrusive_ptr<U, VP> const & rhs)
      :  m_ptr(rhs.get())
   {
      if(m_ptr != 0) intrusive_ptr_add_ref(ipcdetail::to_raw_pointer(m_ptr));
   }

   ~intrusive_ptr()
   {
      if(m_ptr != 0) intrusive_ptr_release(ipcdetail::to_raw_pointer(m_ptr));
   }

   intrusive_ptr & operator=(intrusive_ptr const & rhs)
   {
      this_type(rhs).swap(*this);
      return *this;
   }

   template<class U> intrusive_ptr & operator=
      (intrusive_ptr<U, VP> const & rhs)
   {
      this_type(rhs).swap(*this);
      return *this;
   }

   pointer &get()
   {  return m_ptr;  }

   T & operator*() const
   {  return *m_ptr; }

   const pointer &operator->() const
   {  return m_ptr;  }

   operator unspecified_bool_type () const
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   bool operator! () const
   {  return m_ptr == 0;   }

   void swap(intrusive_ptr & rhs)
   {  ipcdetail::do_swap(m_ptr, rhs.m_ptr);  }

template<class T, class U, class VP> inline
bool operator==(intrusive_ptr<T, VP> const & a,
                intrusive_ptr<U, VP> const & b)
{  return a.get() == b.get(); }

template<class T, class U, class VP> inline
bool operator!=(intrusive_ptr<T, VP> const & a,
                intrusive_ptr<U, VP> const & b)
{  return a.get() != b.get(); }

template<class T, class VP> inline
bool operator==(intrusive_ptr<T, VP> const & a,
                       const typename intrusive_ptr<T, VP>::pointer &b)
{  return a.get() == b; }

template<class T, class VP> inline
bool operator!=(intrusive_ptr<T, VP> const & a,
                const typename intrusive_ptr<T, VP>::pointer &b)
{  return a.get() != b; }

template<class T, class VP> inline
bool operator==(const typename intrusive_ptr<T, VP>::pointer &a,
                intrusive_ptr<T, VP> const & b)
{  return a == b.get(); }

template<class T, class VP> inline
bool operator!=(const typename intrusive_ptr<T, VP>::pointer &a,
                       intrusive_ptr<T, VP> const & b)
{  return a != b.get(); }

template<class T, class VP> inline
bool operator<(intrusive_ptr<T, VP> const & a,
               intrusive_ptr<T, VP> const & b)
{
   return std::less<typename intrusive_ptr<T, VP>::pointer>()
      (a.get(), b.get());
}

template<class T, class VP> inline
void swap(intrusive_ptr<T, VP> & lhs,
          intrusive_ptr<T, VP> & rhs)
{  lhs.swap(rhs); }

   unique_ptr()
      :  ptr_(pointer(0))
   {}

   unique_ptr(BOOST_RV_REF(unique_ptr) u)
      : ptr_(u.release(), boost::forward<D>(u.get_deleter()))
   {}

   ~unique_ptr()
   {  reset(); }

   unique_ptr& operator=(BOOST_RV_REF(unique_ptr) u)
   {
      reset(u.release());
      ptr_.second() = boost::move(u.get_deleter());
      return *this;
   }

   unique_ptr& operator=(nullptr_t)
   {
      reset();
      return *this;
   }

template <class T, class D> inline
void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y)
{  x.swap(y);  }


template <class T1, class D1, class T2, class D2> inline
bool operator==(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() == y.get(); }


template <class T1, class D1, class T2, class D2> inline
bool operator!=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() != y.get(); }


template <class T1, class D1, class T2, class D2> inline
bool operator <(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() < y.get();  }


template <class T1, class D1, class T2, class D2> inline
bool operator<=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() <= y.get(); }


template <class T1, class D1, class T2, class D2> inline
bool operator >(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() > y.get();  }


template <class T1, class D1, class T2, class D2> inline
bool operator>=(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y)
{  return x.get() >= y.get(); }

template<class T, class ManagedMemory>
inline typename managed_unique_ptr<T, ManagedMemory>::type
   make_managed_unique_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_unique_ptr<T, ManagedMemory>::type
      (constructed_object, managed_memory.template get_deleter<T>());
}

   void priv_deallocate(const typename Allocator::pointer &p, allocator_v1)
   {  m_alloc.deallocate(p, 1); }


   scoped_ptr_dealloc_functor(Allocator& a)
      : m_alloc(a) {}


   void operator()(pointer ptr)
   {  if (ptr) priv_deallocate(ptr, alloc_version());  }


   virtual char const * what() const throw()
   {  return "boost::interprocess::bad_weak_ptr"; }


   shared_count()
      :  m_px(0), m_pi(0) // nothrow
   {}


   template <class Ptr>
   shared_count(const shared_count &other_shared_count, const Ptr &p)
      :  m_px(p), m_pi(other_shared_count.m_pi)
   {}


   template <class Ptr>
   shared_count(const Ptr &p, const VoidAllocator &a, Deleter d)
      :  m_px(p), m_pi(0)
   {
      BOOST_TRY{
         if(p){
            counted_impl_allocator alloc(a);
            m_pi = alloc.allocate(1);
            //Anti-exception deallocator
            scoped_ptr<counted_impl,
                     scoped_ptr_dealloc_functor<counted_impl_allocator> >
                        deallocator(m_pi, alloc);
            //It's more correct to use VoidAllocator::construct but
            //this needs copy constructor and we don't like it
            new(ipcdetail::to_raw_pointer(m_pi))counted_impl(p, a, d);
            deallocator.release();
         }
      }
      BOOST_CATCH (...){
         d(p); // delete p
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }


   ~shared_count() // nothrow
   {
      if(m_pi)
         m_pi->release();
   }


   shared_count(shared_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   { if( m_pi != 0 ) m_pi->add_ref_copy(); }

   template<class Y>
   explicit shared_count(shared_count<Y, VoidAllocator, Deleter> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if( m_pi != 0 ) m_pi->add_ref_copy();  }

   template<class Y>
   explicit shared_count(weak_count<Y, VoidAllocator, Deleter> const & r)
      // throws bad_weak_ptr when r.use_count() == 0
      : m_px(r.m_px), m_pi( r.m_pi )
   {
      if( m_pi == 0 || !m_pi->add_ref_lock() ){
         throw( boost::interprocess::bad_weak_ptr() );
      }
   }


   const pointer &to_raw_pointer() const
   {  return m_px;   }


   shared_count & operator= (shared_count const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release();
         m_pi = tmp;
      }
      return *this;
   }


   template<class Y>
   shared_count & operator= (shared_count<Y, VoidAllocator, Deleter> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release();
         m_pi = tmp;
      }
      return *this;
   }


   void swap(shared_count & r) // nothrow
   {  ipcdetail::do_swap(m_px, r.m_px);   ipcdetail::do_swap(m_pi, r.m_pi);   }


   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count(): 0;  }


   bool unique() const // nothrow
   {  return use_count() == 1;   }


   const_deleter_pointer get_deleter() const
   {  return m_pi ? m_pi->get_deleter() : 0; }


   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_equal (shared_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return this->m_pi == other.m_pi;   }


   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_less  (shared_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return std::less<counted_base_ptr>()(this->m_pi, other.m_pi);  }


template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator==(shared_count<T, VoidAllocator, Deleter> const & a, shared_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_equal(b);  }


template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator<(shared_count<T, VoidAllocator, Deleter> const & a, shared_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_less(b);   }


   weak_count(): m_px(0), m_pi(0) // nothrow
   {}


   template <class Y>
   explicit weak_count(shared_count<Y, VoidAllocator, Deleter> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }


   weak_count(weak_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }


   template<class Y>
   weak_count(weak_count<Y, VoidAllocator, Deleter> const & r)
      : m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }


   ~weak_count() // nothrow
   {  if(m_pi != 0) m_pi->weak_release(); }


   template<class Y>
   weak_count & operator= (shared_count<Y, VoidAllocator, Deleter> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0)   tmp->weak_add_ref();
      if(m_pi != 0)  m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }


   weak_count & operator= (weak_count const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }


   void set_pointer(const pointer &ptr)
   {  m_px = ptr; }


   template<class Y>
   weak_count & operator= (weak_count<Y, VoidAllocator, Deleter> const& r) // nothrow
   {
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }


   void swap(weak_count & r) // nothrow
   {  ipcdetail::do_swap(m_px, r.m_px);  ipcdetail::do_swap(m_pi, r.m_pi);   }


   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count() : 0;   }


   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_equal (weak_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return this->m_pi == other.m_pi;   }


   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_less (weak_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return std::less<counted_base_ptr>()(this->m_pi, other.m_pi);  }


template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator==(weak_count<T, VoidAllocator, Deleter> const & a, weak_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_equal(b);  }


template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator<(weak_count<T, VoidAllocator, Deleter> const & a, weak_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_less(b);   }


    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {}


    ~sp_counted_base() // nothrow
    {}


    void add_ref_copy()
    {
        ipcdetail::atomic_inc32( &use_count_ );
    }


    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            boost::uint32_t tmp = static_cast< boost::uint32_t const volatile& >( use_count_ );
            if( tmp == 0 ) return false;
            if( ipcdetail::atomic_cas32( &use_count_, tmp + 1, tmp ) == tmp )
               return true;
        }
    }


   bool ref_release() // nothrow
   { return 1 == ipcdetail::atomic_dec32( &use_count_ );  }


   void weak_add_ref() // nothrow
   { ipcdetail::atomic_inc32( &weak_count_ ); }


   bool weak_release() // nothrow
   { return 1 == ipcdetail::atomic_dec32( &weak_count_ ); }


   long use_count() const // nothrow
   { return (long)static_cast<boost::uint32_t const volatile &>( use_count_ ); }

   explicit basic_bufferbuf(std::ios_base::openmode mode
                            = std::ios_base::in | std::ios_base::out)
      :  base_t(), m_mode(mode), m_buffer(0), m_length(0)
      {}


   virtual ~basic_bufferbuf(){}

   basic_ibufferstream(std::ios_base::openmode mode = std::ios_base::in)
      :  basic_ios_t(), base_t(0), m_buf(mode | std::ios_base::in)
      {  basic_ios_t::init(&m_buf); }


   ~basic_ibufferstream(){};

   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&m_buf); }

   basic_obufferstream(std::ios_base::openmode mode = std::ios_base::out)
      :  basic_ios_t(), base_t(0), m_buf(mode | std::ios_base::out)
      {  basic_ios_t::init(&m_buf); }


   ~basic_obufferstream(){}

   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&m_buf); }

   basic_bufferstream(std::ios_base::openmode mode
                      = std::ios_base::in | std::ios_base::out)
      :  basic_ios_t(), base_t(0), m_buf(mode)
      {  basic_ios_t::init(&m_buf); }


   ~basic_bufferstream(){}

   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&m_buf); }


   virtual ~basic_vectorbuf(){}

   void swap_vector(vector_type &vect)
   {
      if (this->m_mode & std::ios_base::out){
         //Update high water if necessary
         //And resize vector to remove extra size
         if (mp_high_water < base_t::pptr()){
            //Restore the vector's size if necessary
            mp_high_water = base_t::pptr();
         }
         //This does not reallocate
         m_vect.resize(mp_high_water - (m_vect.size() ? &m_vect[0] : 0));
      }
      //Now swap vector
      m_vect.swap(vect);
      this->initialize_pointers();
   }

   const vector_type &vector() const
   {
      if (this->m_mode & std::ios_base::out){
         if (mp_high_water < base_t::pptr()){
            //Restore the vector's size if necessary
            mp_high_water = base_t::pptr();
         }
         //This shouldn't reallocate
         typedef typename vector_type::size_type size_type;
         char_type *old_ptr = base_t::pbase();
         size_type high_pos = size_type(mp_high_water-old_ptr);
         if(m_vect.size() > high_pos){
            m_vect.resize(high_pos);
            //But we must update end write pointer because vector size is now shorter
            int old_pos = base_t::pptr() - base_t::pbase();
            const_cast<basic_vectorbuf*>(this)->base_t::setp(old_ptr, old_ptr + high_pos);
            const_cast<basic_vectorbuf*>(this)->base_t::pbump(old_pos);
         }
      }
      return m_vect;
   }

   void reserve(typename vector_type::size_type size)
   {
      if (this->m_mode & std::ios_base::out && size > m_vect.size()){
         typename vector_type::difference_type write_pos = base_t::pptr() - base_t::pbase();
         typename vector_type::difference_type read_pos  = base_t::gptr() - base_t::eback();
         //Now update pointer data
         m_vect.reserve(size);
         this->initialize_pointers();
         base_t::pbump((int)write_pos);
         if(this->m_mode & std::ios_base::in){
            base_t::gbump((int)read_pos);
         }
      }
   }

   void clear()
   {  m_vect.clear();   this->initialize_pointers();   }

   void initialize_pointers()
   {
      // The initial read position is the beginning of the vector.
      if(!(m_mode & std::ios_base::out)){
         if(m_vect.empty()){
            this->setg(0, 0, 0);
         }
         else{
            this->setg(&m_vect[0], &m_vect[0], &m_vect[0] + m_vect.size());
         }
      }

      // The initial write position is the beginning of the vector.
      if(m_mode & std::ios_base::out){
         //First get real size
         int real_size = (int)m_vect.size();
         //Then maximize size for high watermarking
         m_vect.resize(m_vect.capacity());
         BOOST_ASSERT(m_vect.size() == m_vect.capacity());
         //Set high watermarking with the expanded size
         mp_high_water = m_vect.size() ? (&m_vect[0] + real_size) : 0;
         //Now set formatting pointers
         if(m_vect.empty()){
            this->setp(0, 0);
            if(m_mode & std::ios_base::in)
               this->setg(0, 0, 0);
         }
         else{
            char_type *p = &m_vect[0];
            this->setp(p, p + m_vect.size());
            if(m_mode & std::ios_base::in)
               this->setg(p, p, p + real_size);
         }
         if (m_mode & (std::ios_base::app | std::ios_base::ate)){
            base_t::pbump((int)real_size);
         }
      }
   }

   virtual int_type underflow()
   {
      if (base_t::gptr() == 0)
         return CharTraits::eof();
      if(m_mode & std::ios_base::out){
         if (mp_high_water < base_t::pptr())
            mp_high_water = base_t::pptr();
         if (base_t::egptr() < mp_high_water)
            base_t::setg(base_t::eback(), base_t::gptr(), mp_high_water);
      }
      if (base_t::gptr() < base_t::egptr())
         return CharTraits::to_int_type(*base_t::gptr());
      return CharTraits::eof();
   }


   virtual int_type pbackfail(int_type c = CharTraits::eof())
   {
      if(this->gptr() != this->eback()) {
         if(!CharTraits::eq_int_type(c, CharTraits::eof())) {
            if(CharTraits::eq(CharTraits::to_char_type(c), this->gptr()[-1])) {
               this->gbump(-1);
               return c;
            }
            else if(m_mode & std::ios_base::out) {
               this->gbump(-1);
               *this->gptr() = c;
               return c;
            }
            else
               return CharTraits::eof();
         }
         else {
            this->gbump(-1);
            return CharTraits::not_eof(c);
         }
      }
      else
         return CharTraits::eof();
   }


   virtual int_type overflow(int_type c = CharTraits::eof())
   {
      if(m_mode & std::ios_base::out) {
         if(!CharTraits::eq_int_type(c, CharTraits::eof())) {
               typedef typename vector_type::difference_type dif_t;
               //The new output position is the previous one plus one
               //because 'overflow' requires putting 'c' on the buffer
               dif_t new_outpos = base_t::pptr() - base_t::pbase() + 1;
               //Adjust high water if necessary
               dif_t hipos = mp_high_water - base_t::pbase();
               if (hipos < new_outpos)
                  hipos = new_outpos;
               //Insert the new data
               m_vect.push_back(CharTraits::to_char_type(c));
               m_vect.resize(m_vect.capacity());
               BOOST_ASSERT(m_vect.size() == m_vect.capacity());
               char_type* p = const_cast<char_type*>(&m_vect[0]);
               //A reallocation might have happened, update pointers
               base_t::setp(p, p + (dif_t)m_vect.size());
               mp_high_water = p + hipos;
               if (m_mode & std::ios_base::in)
                  base_t::setg(p, p + (base_t::gptr() - base_t::eback()), mp_high_water);
               //Update write position to the old position + 1
               base_t::pbump((int)new_outpos);
               return c;
         }
         else  // c is EOF, so we don't have to do anything
            return CharTraits::not_eof(c);
      }
      else     // Overflow always fails if it's read-only.
         return CharTraits::eof();
   }


   virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir,
                              std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
   {
      //Get seek mode
      bool in(0 != (mode & std::ios_base::in)), out(0 != (mode & std::ios_base::out));
      //Test for logic errors
      if(!in & !out)
         return pos_type(off_type(-1));
      else if((in && out) && (dir == std::ios_base::cur))
         return pos_type(off_type(-1));
      else if((in  && (!(m_mode & std::ios_base::in) || this->gptr() == 0)) ||
               (out && (!(m_mode & std::ios_base::out) || this->pptr() == 0)))
         return pos_type(off_type(-1));

      off_type newoff;
      //Just calculate the end of the stream. If the stream is read-only
      //the limit is the size of the vector. Otherwise, the high water mark
      //will mark the real size.
      off_type limit;
      if(m_mode & std::ios_base::out){
         //Update high water marking because pptr() is going to change and it might
         //have been updated since last overflow()
         if(mp_high_water < base_t::pptr())
            mp_high_water = base_t::pptr();
         //Update read limits in case high water mark was changed
         if(m_mode & std::ios_base::in){
            if (base_t::egptr() < mp_high_water)
               base_t::setg(base_t::eback(), base_t::gptr(), mp_high_water);
         }
         limit = static_cast<off_type>(mp_high_water - base_t::pbase());
      }
      else{
         limit = static_cast<off_type>(m_vect.size());
      }

      switch(dir) {
         case std::ios_base::beg:
            newoff = 0;
         break;
         case std::ios_base::end:
            newoff = limit;
         break;
         case std::ios_base::cur:
            newoff = in ? static_cast<std::streamoff>(this->gptr() - this->eback())
                        : static_cast<std::streamoff>(this->pptr() - this->pbase());
         break;
         default:
            return pos_type(off_type(-1));
      }

      newoff += off;

      if (newoff < 0 || newoff > limit)
         return pos_type(-1);
      if (m_mode & std::ios_base::app && mode & std::ios_base::out && newoff != limit)
         return pos_type(-1);
      //This can reassign pointers
      //if(m_vect.size() != m_vect.capacity())
         //this->initialize_pointers();
      if (in)
         base_t::setg(base_t::eback(), base_t::eback() + newoff, base_t::egptr());
      if (out){
         base_t::setp(base_t::pbase(), base_t::epptr());
         base_t::pbump(newoff);
      }
      return pos_type(newoff);
   }


   virtual pos_type seekpos(pos_type pos, std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
   {  return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);  }


   vectorbuf_t &       m_buf()      {  return *this;  }

   const vectorbuf_t & m_buf() const{  return *this;  }

   basic_ivectorstream(std::ios_base::openmode mode = std::ios_base::in)
      :  vectorbuf_t(mode | std::ios_base::in), base_t(&m_buf())
   {}


   ~basic_ivectorstream(){};

   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&m_buf()); }

   void swap_vector(vector_type &vect)
   {  m_buf().swap_vector(vect);   }

   const vector_type &vector() const
   {  return m_buf().vector();   }

   void reserve(typename vector_type::size_type size)
   {  m_buf().reserve(size);   }

   void clear()
   {  m_buf().clear();   }


   vectorbuf_t &       m_buf()      {  return *this;  }

   const vectorbuf_t & m_buf()const {  return *this;  }

   basic_ovectorstream(std::ios_base::openmode mode = std::ios_base::out)
      :  vectorbuf_t(mode | std::ios_base::out), base_t(&m_buf())
   {}


   ~basic_ovectorstream(){}

   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&m_buf()); }

   void swap_vector(vector_type &vect)
   {  m_buf().swap_vector(vect);   }

   const vector_type &vector() const
   {  return m_buf().vector();   }

   void reserve(typename vector_type::size_type size)
   {  m_buf().reserve(size);   }

   basic_vectorstream(std::ios_base::openmode mode
                      = std::ios_base::in | std::ios_base::out)
      :  basic_ios_t(), base_t(0), m_buf(mode)
   {  basic_ios_t::init(&m_buf); }


   ~basic_vectorstream(){}

   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&m_buf); }

   void swap_vector(vector_type &vect)
   {  m_buf.swap_vector(vect);   }

   const vector_type &vector() const
   {  return m_buf.vector();   }

   void reserve(typename vector_type::size_type size)
   {  m_buf.reserve(size);   }

   void clear()
   {  m_buf.clear();   }

      block_ctrl()
      {  this->m_size = 0; this->m_allocated = 0, this->m_prev_allocated = 0;  }

      bool operator()(size_type size, const block_ctrl &block) const
      {  return size < block.m_size;  }

   void allocate_many(size_type elem_bytes, size_type num_elements, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      algo_impl_t::allocate_many(this, elem_bytes, num_elements, chain);
   }

   void priv_mark_new_allocated_block(block_ctrl *ptr)
   {  return priv_mark_as_allocated_block(ptr); }


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
inline typename rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::block_ctrl *
       rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>
   ::priv_first_block()
{
   size_type block1_off = priv_first_block_offset_from_this(this, m_header.m_extra_hdr_bytes);
   return reinterpret_cast<block_ctrl *>(reinterpret_cast<char*>(this) + block1_off);
}


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
inline typename rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::block_ctrl *
       rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>
   ::priv_end_block()
{
   size_type block1_off  = priv_first_block_offset_from_this(this, m_header.m_extra_hdr_bytes);
   const size_type original_first_block_size = m_header.m_size/Alignment*Alignment - block1_off/Alignment*Alignment - EndCtrlBlockBytes;
   block_ctrl *end_block = reinterpret_cast<block_ctrl*>
      (reinterpret_cast<char*>(this) + block1_off + original_first_block_size);
   return end_block;
}


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
inline rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::~rbtree_best_fit()
{
   //There is a memory leak!
//   BOOST_ASSERT(m_header.m_allocated == 0);
//   BOOST_ASSERT(m_header.m_root.m_next->m_next == block_ctrl_ptr(&m_header.m_root));
}


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
void rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::shrink_to_fit()
{
   //Get the address of the first block
   block_ctrl *first_block = priv_first_block();
   algo_impl_t::assert_alignment(first_block);

   //block_ctrl *old_end_block = priv_end_block(first_block);
   block_ctrl *old_end_block = priv_end_block();
   algo_impl_t::assert_alignment(old_end_block);
   size_type old_end_block_size = old_end_block->m_size;

   void *unique_buffer = 0;
   block_ctrl *last_block;
   //Check if no memory is allocated between the first and last block
   if(priv_next_block(first_block) == old_end_block){
      //If so check if we can allocate memory
      size_type ignore;
      unique_buffer = priv_allocate(boost::interprocess::allocate_new, 0, 0, ignore).first;
      //If not, return, we can't shrink
      if(!unique_buffer)
         return;
      //If we can, mark the position just after the new allocation as the new end
      algo_impl_t::assert_alignment(unique_buffer);
      block_ctrl *unique_block = priv_get_block(unique_buffer);
      BOOST_ASSERT(priv_is_allocated_block(unique_block));
      algo_impl_t::assert_alignment(unique_block);
      last_block = priv_next_block(unique_block);
      BOOST_ASSERT(!priv_is_allocated_block(last_block));
      algo_impl_t::assert_alignment(last_block);
   }
   else{
      //If memory is allocated, check if the last block is allocated
      if(priv_is_prev_allocated(old_end_block))
         return;
      //If not, mark last block after the free block
      last_block = priv_prev_block(old_end_block);
   }

   size_type last_block_size = last_block->m_size;

   //Erase block from the free tree, since we will erase it
   m_header.m_imultiset.erase(Imultiset::s_iterator_to(*last_block));

   size_type shrunk_border_offset = (size_type)(reinterpret_cast<char*>(last_block) -
                                       reinterpret_cast<char*>(this)) + EndCtrlBlockBytes;

   block_ctrl *new_end_block = last_block;
   algo_impl_t::assert_alignment(new_end_block);

   //Write new end block attributes
   #ifdef BOOST_INTERPROCESS_RBTREE_BEST_FIT_ABI_V1_HPP
   new_end_block->m_size = first_block->m_prev_size =
      (reinterpret_cast<char*>(first_block) - reinterpret_cast<char*>(new_end_block))/Alignment;
   #else
   new_end_block->m_size = first_block->m_prev_size =
      (reinterpret_cast<char*>(new_end_block) - reinterpret_cast<char*>(first_block))/Alignment;
   #endif

   new_end_block->m_allocated = 1;
   (void)last_block_size;
   (void)old_end_block_size;
   BOOST_ASSERT(new_end_block->m_size == (old_end_block_size - last_block_size));

   //Update managed buffer's size
   m_header.m_size = shrunk_border_offset;
   BOOST_ASSERT(priv_end_block() == new_end_block);
   if(unique_buffer)
      priv_deallocate(unique_buffer);
}


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
inline bool rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::
    all_memory_deallocated()
{
   //-----------------------
   boost::interprocess::scoped_lock<mutex_type> guard(m_header);
   //-----------------------
   size_type block1_off  =
      priv_first_block_offset_from_this(this, m_header.m_extra_hdr_bytes);

   return m_header.m_allocated == 0 &&
      m_header.m_imultiset.begin() != m_header.m_imultiset.end() &&
       (++m_header.m_imultiset.begin()) == m_header.m_imultiset.end()
       && m_header.m_imultiset.begin()->m_size ==
         (m_header.m_size - block1_off - EndCtrlBlockBytes)/Alignment;
}


template<class MutexFamily, class VoidPointer, std::size_t MemAlignment>
bool rbtree_best_fit<MutexFamily, VoidPointer, MemAlignment>::
    check_sanity()
{
   //-----------------------
   boost::interprocess::scoped_lock<mutex_type> guard(m_header);
   //-----------------------
   imultiset_iterator ib(m_header.m_imultiset.begin()), ie(m_header.m_imultiset.end());

   size_type free_memory = 0;

   //Iterate through all blocks obtaining their size
   for(; ib != ie; ++ib){
      free_memory += (size_type)ib->m_size*Alignment;
      algo_impl_t::assert_alignment(&*ib);
      if(!algo_impl_t::check_alignment(&*ib))
         return false;
   }

   //Check allocated bytes are less than size
   if(m_header.m_allocated > m_header.m_size){
      return false;
   }

   size_type block1_off  =
      priv_first_block_offset_from_this(this, m_header.m_extra_hdr_bytes);

   //Check free bytes are less than size
   if(free_memory > (m_header.m_size - block1_off)){
      return false;
   }
   return true;
}

   simple_seq_fit(size_type segment_size, size_type extra_hdr_bytes)
      : base_t(segment_size, extra_hdr_bytes){}


   basic_multiallocation_chain()
      :  base_t()
   {}


   basic_multiallocation_chain(BOOST_RV_REF(basic_multiallocation_chain) other)
      :  base_t(::boost::move(static_cast<base_t&>(other)))
   {}


   basic_multiallocation_chain& operator=(BOOST_RV_REF(basic_multiallocation_chain) other)
   {
      this->base_t::operator=(::boost::move(static_cast<base_t&>(other)));
      return *this;
   }


   void *pop_front()
   {
      return boost::interprocess::ipcdetail::to_raw_pointer(this->base_t::pop_front());
   }


   static void assert_alignment(const void *ptr)
   {  assert_alignment((std::size_t)ptr); }


   static void assert_alignment(size_type uint_ptr)
   {
      (void)uint_ptr;
      BOOST_ASSERT(uint_ptr % Alignment == 0);
   }


   static bool check_alignment(const void *ptr)
   {  return (((std::size_t)ptr) % Alignment == 0);   }


   static size_type ceil_units(size_type size)
   {  return get_rounded_size(size, Alignment)/Alignment; }


   static size_type floor_units(size_type size)
   {  return size/Alignment;  }


   static size_type multiple_of_units(size_type size)
   {  return get_rounded_size(size, Alignment);  }


   static void allocate_many
      (MemoryAlgorithm *memory_algo, size_type elem_bytes, size_type n_elements, multiallocation_chain &chain)
   {
      return this_type::priv_allocate_many(memory_algo, &elem_bytes, n_elements, 0, chain);
   }


   static void deallocate_many(MemoryAlgorithm *memory_algo, multiallocation_chain &chain)
   {
      return this_type::priv_deallocate_many(memory_algo, chain);
   }


   static bool calculate_lcm_and_needs_backwards_lcmed
      (size_type backwards_multiple, size_type received_size, size_type size_to_achieve,
      size_type &lcm_out, size_type &needs_backwards_lcmed_out)
   {
      // Now calculate lcm_val
      size_type max = backwards_multiple;
      size_type min = Alignment;
      size_type needs_backwards;
      size_type needs_backwards_lcmed;
      size_type lcm_val;
      size_type current_forward;
      //Swap if necessary
      if(max < min){
         size_type tmp = min;
         min = max;
         max = tmp;
      }
      //Check if it's power of two
      if((backwards_multiple & (backwards_multiple-1)) == 0){
         if(0 != (size_to_achieve & ((backwards_multiple-1)))){
            return false;
         }

         lcm_val = max;
         //If we want to use minbytes data to get a buffer between maxbytes
         //and minbytes if maxbytes can't be achieved, calculate the
         //biggest of all possibilities
         current_forward = get_truncated_size_po2(received_size, backwards_multiple);
         needs_backwards = size_to_achieve - current_forward;
         BOOST_ASSERT((needs_backwards % backwards_multiple) == 0);
         needs_backwards_lcmed = get_rounded_size_po2(needs_backwards, lcm_val);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of alignment
      else if((backwards_multiple & (Alignment - 1u)) == 0){
         lcm_val = backwards_multiple;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         //No need to round needs_backwards because backwards_multiple == lcm_val
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         BOOST_ASSERT((needs_backwards_lcmed & (Alignment - 1u)) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of the half of the alignmment
      else if((backwards_multiple & ((Alignment/2u) - 1u)) == 0){
         lcm_val = backwards_multiple*2u;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         if(0 != (needs_backwards_lcmed & (Alignment-1)))
         //while(0 != (needs_backwards_lcmed & (Alignment-1)))
            needs_backwards_lcmed += backwards_multiple;
         BOOST_ASSERT((needs_backwards_lcmed % lcm_val) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      //Check if it's multiple of the quarter of the alignmment
      else if((backwards_multiple & ((Alignment/4u) - 1u)) == 0){
         size_type remainder;
         lcm_val = backwards_multiple*4u;
         current_forward = get_truncated_size(received_size, backwards_multiple);
         needs_backwards_lcmed = needs_backwards = size_to_achieve - current_forward;
         //while(0 != (needs_backwards_lcmed & (Alignment-1)))
            //needs_backwards_lcmed += backwards_multiple;
         if(0 != (remainder = ((needs_backwards_lcmed & (Alignment-1))>>(Alignment/8u)))){
            if(backwards_multiple & Alignment/2u){
               needs_backwards_lcmed += (remainder)*backwards_multiple;
            }
            else{
               needs_backwards_lcmed += (4-remainder)*backwards_multiple;
            }
         }
         BOOST_ASSERT((needs_backwards_lcmed % lcm_val) == 0);
         lcm_out = lcm_val;
         needs_backwards_lcmed_out = needs_backwards_lcmed;
         return true;
      }
      else{
         lcm_val = lcm(max, min);
      }
      //If we want to use minbytes data to get a buffer between maxbytes
      //and minbytes if maxbytes can't be achieved, calculate the
      //biggest of all possibilities
      current_forward = get_truncated_size(received_size, backwards_multiple);
      needs_backwards = size_to_achieve - current_forward;
      BOOST_ASSERT((needs_backwards % backwards_multiple) == 0);
      needs_backwards_lcmed = get_rounded_size(needs_backwards, lcm_val);
      lcm_out = lcm_val;
      needs_backwards_lcmed_out = needs_backwards_lcmed;
      return true;
   }


   static void allocate_many
      ( MemoryAlgorithm *memory_algo
      , const size_type *elem_sizes
      , size_type n_elements
      , size_type sizeof_element
      , multiallocation_chain &chain)
   {
      this_type::priv_allocate_many(memory_algo, elem_sizes, n_elements, sizeof_element, chain);
   }


   static void* allocate_aligned
      (MemoryAlgorithm *memory_algo, size_type nbytes, size_type alignment)
   {

      //Ensure power of 2
      if ((alignment & (alignment - size_type(1u))) != 0){
         //Alignment is not power of two
         BOOST_ASSERT((alignment & (alignment - size_type(1u))) == 0);
         return 0;
      }

      size_type real_size;
      if(alignment <= Alignment){
         return memory_algo->priv_allocate
            (boost::interprocess::allocate_new, nbytes, nbytes, real_size).first;
      }

      if(nbytes > UsableByPreviousChunk)
         nbytes -= UsableByPreviousChunk;

      //We can find a aligned portion if we allocate a block that has alignment
      //nbytes + alignment bytes or more.
      size_type minimum_allocation = max_value
         (nbytes + alignment, size_type(MinBlockUnits*Alignment));
      //Since we will split that block, we must request a bit more memory
      //if the alignment is near the beginning of the buffer, because otherwise,
      //there is no space for a new block before the alignment.
      //
      //            ____ Aligned here
      //           |
      //  -----------------------------------------------------
      // | MBU |
      //  -----------------------------------------------------
      size_type request =
         minimum_allocation + (2*MinBlockUnits*Alignment - AllocatedCtrlBytes
         //prevsize - UsableByPreviousChunk
         );

      //Now allocate the buffer
      void *buffer = memory_algo->priv_allocate
         (boost::interprocess::allocate_new, request, request, real_size).first;
      if(!buffer){
         return 0;
      }
      else if ((((std::size_t)(buffer)) % alignment) == 0){
         //If we are lucky and the buffer is aligned, just split it and
         //return the high part
         block_ctrl *first  = memory_algo->priv_get_block(buffer);
         size_type old_size = first->m_size;
         const size_type first_min_units =
            max_value(ceil_units(nbytes) + AllocatedCtrlUnits, size_type(MinBlockUnits));
         //We can create a new block in the end of the segment
         if(old_size >= (first_min_units + MinBlockUnits)){
            block_ctrl *second =  reinterpret_cast<block_ctrl *>
               (reinterpret_cast<char*>(first) + Alignment*first_min_units);
            first->m_size  = first_min_units;
            second->m_size = old_size - first->m_size;
            BOOST_ASSERT(second->m_size >= MinBlockUnits);
            memory_algo->priv_mark_new_allocated_block(first);
            //memory_algo->priv_tail_size(first, first->m_size);
            memory_algo->priv_mark_new_allocated_block(second);
            memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(second));
         }
         return buffer;
      }

      //Buffer not aligned, find the aligned part.
      //
      //                    ____ Aligned here
      //                   |
      //  -----------------------------------------------------
      // | MBU +more | ACB |
      //  -----------------------------------------------------
      char *pos = reinterpret_cast<char*>
         (reinterpret_cast<std::size_t>(static_cast<char*>(buffer) +
            //This is the minimum size of (2)
            (MinBlockUnits*Alignment - AllocatedCtrlBytes) +
            //This is the next MBU for the aligned memory
            AllocatedCtrlBytes +
            //This is the alignment trick
            alignment - 1) & -alignment);

      //Now obtain the address of the blocks
      block_ctrl *first  = memory_algo->priv_get_block(buffer);
      block_ctrl *second = memory_algo->priv_get_block(pos);
      BOOST_ASSERT(pos <= (reinterpret_cast<char*>(first) + first->m_size*Alignment));
      BOOST_ASSERT(first->m_size >= 2*MinBlockUnits);
      BOOST_ASSERT((pos + MinBlockUnits*Alignment - AllocatedCtrlBytes + nbytes*Alignment/Alignment) <=
             (reinterpret_cast<char*>(first) + first->m_size*Alignment));
      //Set the new size of the first block
      size_type old_size = first->m_size;
      first->m_size  = (size_type)(reinterpret_cast<char*>(second) - reinterpret_cast<char*>(first))/Alignment;
      memory_algo->priv_mark_new_allocated_block(first);

      //Now check if we can create a new buffer in the end
      //
      //              __"second" block
      //             |      __Aligned here
      //             |     |      __"third" block
      //  -----------|-----|-----|------------------------------
      // | MBU +more | ACB | (3) | BCU |
      //  -----------------------------------------------------
      //This size will be the minimum size to be able to create a
      //new block in the end.
      const size_type second_min_units = max_value(size_type(MinBlockUnits),
                        ceil_units(nbytes) + AllocatedCtrlUnits );

      //Check if we can create a new block (of size MinBlockUnits) in the end of the segment
      if((old_size - first->m_size) >= (second_min_units + MinBlockUnits)){
         //Now obtain the address of the end block
         block_ctrl *third = new (reinterpret_cast<char*>(second) + Alignment*second_min_units)block_ctrl;
         second->m_size = second_min_units;
         third->m_size  = old_size - first->m_size - second->m_size;
         BOOST_ASSERT(third->m_size >= MinBlockUnits);
         memory_algo->priv_mark_new_allocated_block(second);
         memory_algo->priv_mark_new_allocated_block(third);
         memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(third));
      }
      else{
         second->m_size = old_size - first->m_size;
         BOOST_ASSERT(second->m_size >= MinBlockUnits);
         memory_algo->priv_mark_new_allocated_block(second);
      }

      memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(first));
      return memory_algo->priv_get_user_buffer(second);
   }


   static bool try_shrink
      (MemoryAlgorithm *memory_algo, void *ptr
      ,const size_type max_size,   const size_type preferred_size
      ,size_type &received_size)
   {
      (void)memory_algo;
      //Obtain the real block
      block_ctrl *block = memory_algo->priv_get_block(ptr);
      size_type old_block_units = (size_type)block->m_size;

      //The block must be marked as allocated
      BOOST_ASSERT(memory_algo->priv_is_allocated_block(block));

      //Check if alignment and block size are right
      assert_alignment(ptr);

      //Put this to a safe value
      received_size = (old_block_units - AllocatedCtrlUnits)*Alignment + UsableByPreviousChunk;

      //Now translate it to Alignment units
      const size_type max_user_units       = floor_units(max_size - UsableByPreviousChunk);
      const size_type preferred_user_units = ceil_units(preferred_size - UsableByPreviousChunk);

      //Check if rounded max and preferred are possible correct
      if(max_user_units < preferred_user_units)
         return false;

      //Check if the block is smaller than the requested minimum
      size_type old_user_units = old_block_units - AllocatedCtrlUnits;

      if(old_user_units < preferred_user_units)
         return false;

      //If the block is smaller than the requested minimum
      if(old_user_units == preferred_user_units)
         return true;

      size_type shrunk_user_units =
         ((BlockCtrlUnits - AllocatedCtrlUnits) >= preferred_user_units)
         ? (BlockCtrlUnits - AllocatedCtrlUnits)
         : preferred_user_units;

      //Some parameter checks
      if(max_user_units < shrunk_user_units)
         return false;

      //We must be able to create at least a new empty block
      if((old_user_units - shrunk_user_units) < BlockCtrlUnits ){
         return false;
      }

      //Update new size
      received_size = shrunk_user_units*Alignment + UsableByPreviousChunk;
      return true;
   }


   static bool shrink
      (MemoryAlgorithm *memory_algo, void *ptr
      ,const size_type max_size,   const size_type preferred_size
      ,size_type &received_size)
   {
      //Obtain the real block
      block_ctrl *block = memory_algo->priv_get_block(ptr);
      size_type old_block_units = (size_type)block->m_size;

      if(!try_shrink
         (memory_algo, ptr, max_size, preferred_size, received_size)){
         return false;
      }

      //Check if the old size was just the shrunk size (no splitting)
      if((old_block_units - AllocatedCtrlUnits) == ceil_units(preferred_size - UsableByPreviousChunk))
         return true;

      //Now we can just rewrite the size of the old buffer
      block->m_size = (received_size-UsableByPreviousChunk)/Alignment + AllocatedCtrlUnits;
      BOOST_ASSERT(block->m_size >= BlockCtrlUnits);

      //We create the new block
      block_ctrl *new_block = reinterpret_cast<block_ctrl*>
                  (reinterpret_cast<char*>(block) + block->m_size*Alignment);
      //Write control data to simulate this new block was previously allocated
      //and deallocate it
      new_block->m_size = old_block_units - block->m_size;
      BOOST_ASSERT(new_block->m_size >= BlockCtrlUnits);
      memory_algo->priv_mark_new_allocated_block(block);
      memory_algo->priv_mark_new_allocated_block(new_block);
      memory_algo->priv_deallocate(memory_algo->priv_get_user_buffer(new_block));
      return true;
   }

   static void priv_allocate_many
      ( MemoryAlgorithm *memory_algo
      , const size_type *elem_sizes
      , size_type n_elements
      , size_type sizeof_element
      , multiallocation_chain &chain)
   {
      //Note: sizeof_element == 0 indicates that we want to
      //allocate n_elements of the same size "*elem_sizes"

      //Calculate the total size of all requests
      size_type total_request_units = 0;
      size_type elem_units = 0;
      const size_type ptr_size_units = memory_algo->priv_get_total_units(sizeof(void_pointer));
      if(!sizeof_element){
         elem_units = memory_algo->priv_get_total_units(*elem_sizes);
         elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
         total_request_units = n_elements*elem_units;
      }
      else{
         for(size_type i = 0; i < n_elements; ++i){
            if(multiplication_overflows(elem_sizes[i], sizeof_element)){
               total_request_units = 0;
               break;
            }
            elem_units = memory_algo->priv_get_total_units(elem_sizes[i]*sizeof_element);
            elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
            if(sum_overflows(total_request_units, elem_units)){
               total_request_units = 0;
               break;
            }
            total_request_units += elem_units;
         }
      }

      if(total_request_units && !multiplication_overflows(total_request_units, Alignment)){
         size_type low_idx = 0;
         while(low_idx < n_elements){
            size_type total_bytes = total_request_units*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;
            size_type min_allocation = (!sizeof_element)
               ?  elem_units
               :  memory_algo->priv_get_total_units(elem_sizes[low_idx]*sizeof_element);
            min_allocation = min_allocation*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;

            size_type received_size;
            std::pair<void *, bool> ret = memory_algo->priv_allocate
               (boost::interprocess::allocate_new, min_allocation, total_bytes, received_size, 0);
            if(!ret.first){
               break;
            }

            block_ctrl *block = memory_algo->priv_get_block(ret.first);
            size_type received_units = (size_type)block->m_size;
            char *block_address = reinterpret_cast<char*>(block);

            size_type total_used_units = 0;
            while(total_used_units < received_units){
               if(sizeof_element){
                  elem_units = memory_algo->priv_get_total_units(elem_sizes[low_idx]*sizeof_element);
                  elem_units = ptr_size_units > elem_units ? ptr_size_units : elem_units;
               }
               if(total_used_units + elem_units > received_units)
                  break;
               total_request_units -= elem_units;
               //This is the position where the new block must be created
               block_ctrl *new_block = reinterpret_cast<block_ctrl *>(block_address);
               assert_alignment(new_block);

               //The last block should take all the remaining space
               if((low_idx + 1) == n_elements ||
                  (total_used_units + elem_units +
                  ((!sizeof_element)
                     ? elem_units
               : std::max(memory_algo->priv_get_total_units(elem_sizes[low_idx+1]*sizeof_element), ptr_size_units))
                  ) > received_units){
                  //By default, the new block will use the rest of the buffer
                  new_block->m_size = received_units - total_used_units;
                  memory_algo->priv_mark_new_allocated_block(new_block);

                  //If the remaining units are bigger than needed and we can
                  //split it obtaining a new free memory block do it.
                  if((received_units - total_used_units) >= (elem_units + MemoryAlgorithm::BlockCtrlUnits)){
                     size_type shrunk_received;
                     size_type shrunk_request = elem_units*Alignment - AllocatedCtrlBytes + UsableByPreviousChunk;
                     bool shrink_ok = shrink
                           (memory_algo
                           ,memory_algo->priv_get_user_buffer(new_block)
                           ,shrunk_request
                           ,shrunk_request
                           ,shrunk_received);
                     (void)shrink_ok;
                     //Shrink must always succeed with passed parameters
                     BOOST_ASSERT(shrink_ok);
                     //Some sanity checks
                     BOOST_ASSERT(shrunk_request == shrunk_received);
                     BOOST_ASSERT(elem_units == ((shrunk_request-UsableByPreviousChunk)/Alignment + AllocatedCtrlUnits));
                     //"new_block->m_size" must have been reduced to elem_units by "shrink"
                     BOOST_ASSERT(new_block->m_size == elem_units);
                     //Now update the total received units with the reduction
                     received_units = elem_units + total_used_units;
                  }
               }
               else{
                  new_block->m_size = elem_units;
                  memory_algo->priv_mark_new_allocated_block(new_block);
               }

               block_address += new_block->m_size*Alignment;
               total_used_units += (size_type)new_block->m_size;
               //Check we have enough room to overwrite the intrusive pointer
               BOOST_ASSERT((new_block->m_size*Alignment - AllocatedCtrlUnits) >= sizeof(void_pointer));
               void_pointer p = new(memory_algo->priv_get_user_buffer(new_block))void_pointer(0);
               chain.push_back(p);
               ++low_idx;
            }
            //Sanity check
            BOOST_ASSERT(total_used_units == received_units);
         }

         if(low_idx != n_elements){
            priv_deallocate_many(memory_algo, chain);
         }
      }
   }


   static void priv_deallocate_many(MemoryAlgorithm *memory_algo, multiallocation_chain &chain)
   {
      while(!chain.empty()){
         memory_algo->priv_deallocate(to_raw_pointer(chain.pop_front()));
      }
   }

   
      size_type get_user_bytes() const
      {  return this->m_size*Alignment - BlockCtrlBytes; }


      size_type get_total_bytes() const
      {  return this->m_size*Alignment; }


      static block_ctrl *get_block_from_addr(void *addr)
      {
         return reinterpret_cast<block_ctrl*>
            (reinterpret_cast<char*>(addr) - BlockCtrlBytes);
      }


      void *get_addr() const
      {
         return reinterpret_cast<block_ctrl*>
            (reinterpret_cast<const char*>(this) + BlockCtrlBytes);
      }


template<class MutexFamily, class VoidPointer>
inline simple_seq_fit_impl<MutexFamily, VoidPointer>::~simple_seq_fit_impl()
{
   //There is a memory leak!
//   BOOST_ASSERT(m_header.m_allocated == 0);
//   BOOST_ASSERT(m_header.m_root.m_next->m_next == block_ctrl_ptr(&m_header.m_root));
}


template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    all_memory_deallocated()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   return m_header.m_allocated == 0 &&
          ipcdetail::to_raw_pointer(m_header.m_root.m_next->m_next) == &m_header.m_root;
}


template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::clear_free_memory()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   //Iterate through all free portions
   do{
      //Just clear user the memory part reserved for the user      
      std::memset( reinterpret_cast<char*>(block) + BlockCtrlBytes
                 , 0
                 , block->m_size*Alignment - BlockCtrlBytes);
      block = ipcdetail::to_raw_pointer(block->m_next);
   }
   while(block != &m_header.m_root);
}


template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    check_sanity()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   size_type free_memory = 0;

   //Iterate through all blocks obtaining their size
   do{
      //Free blocks's next must be always valid
      block_ctrl *next = ipcdetail::to_raw_pointer(block->m_next);
      if(!next){
         return false;
      }
      free_memory += block->m_size*Alignment;
      block = next;
   }
   while(block != &m_header.m_root);

   //Check allocated bytes are less than size
   if(m_header.m_allocated > m_header.m_size){
      return false;
   }

   //Check free bytes are less than size
   if(free_memory > m_header.m_size){
      return false;
   }
   return true;
}


      size_type get_user_bytes() const
      {  return this->m_size*Alignment - BlockCtrlBytes; }


      size_type get_total_bytes() const
      {  return this->m_size*Alignment; }

   void allocate_many(size_type elem_bytes, size_type num_elements, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
      //-----------------------
      algo_impl_t::allocate_many(this, elem_bytes, num_elements, chain);
   }


template<class MutexFamily, class VoidPointer>
inline simple_seq_fit_impl<MutexFamily, VoidPointer>::~simple_seq_fit_impl()
{
   //There is a memory leak!
//   BOOST_ASSERT(m_header.m_allocated == 0);
//   BOOST_ASSERT(m_header.m_root.m_next->m_next == block_ctrl_ptr(&m_header.m_root));
}


template<class MutexFamily, class VoidPointer>
void simple_seq_fit_impl<MutexFamily, VoidPointer>::shrink_to_fit()
{
   //Get the root and the first memory block
   block_ctrl *prev                 = &m_header.m_root;
   block_ctrl *last                 = &m_header.m_root;
   block_ctrl *block                = ipcdetail::to_raw_pointer(last->m_next);
   block_ctrl *root                 = &m_header.m_root;

   //No free block?
   if(block == root) return;

   //Iterate through the free block list
   while(block != root){
      prev  = last;
      last  = block;
      block = ipcdetail::to_raw_pointer(block->m_next);
   }

   char *last_free_end_address   = reinterpret_cast<char*>(last) + last->m_size*Alignment;
   if(last_free_end_address != (reinterpret_cast<char*>(this) + priv_block_end_offset())){
      //there is an allocated block in the end of this block
      //so no shrinking is possible
      return;
   }

   //Check if have only 1 big free block
   void *unique_block = 0;
   if(!m_header.m_allocated){
      BOOST_ASSERT(prev == root);
      size_type ignore;
      unique_block = priv_allocate(boost::interprocess::allocate_new, 0, 0, ignore).first;
      if(!unique_block)
         return;
      last = ipcdetail::to_raw_pointer(m_header.m_root.m_next);
      BOOST_ASSERT(last_free_end_address == (reinterpret_cast<char*>(last) + last->m_size*Alignment));
   }
   size_type last_units = last->m_size;

   size_type received_size;
   void *addr = priv_check_and_allocate(last_units, prev, last, received_size);
   (void)addr;
   BOOST_ASSERT(addr);
   BOOST_ASSERT(received_size == last_units*Alignment - AllocatedCtrlBytes);

   //Shrink it
   m_header.m_size /= Alignment;
   m_header.m_size -= last->m_size;
   m_header.m_size *= Alignment;
   m_header.m_allocated -= last->m_size*Alignment;

   if(unique_block)
      priv_deallocate(unique_block);
}


template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::
   priv_mark_new_allocated_block(block_ctrl *new_block)
{
   new_block->m_next = 0;
}


template<class MutexFamily, class VoidPointer>
inline
typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *
   simple_seq_fit_impl<MutexFamily, VoidPointer>::priv_get_block(const void *ptr)
{
   return const_cast<block_ctrl*>(reinterpret_cast<const block_ctrl*>
      (reinterpret_cast<const char*>(ptr) - AllocatedCtrlBytes));
}


template<class MutexFamily, class VoidPointer>
inline
void *simple_seq_fit_impl<MutexFamily, VoidPointer>::
      priv_get_user_buffer(const typename simple_seq_fit_impl<MutexFamily, VoidPointer>::block_ctrl *block)
{
   return const_cast<char*>(reinterpret_cast<const char*>(block) + AllocatedCtrlBytes);
}


template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    all_memory_deallocated()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   return m_header.m_allocated == 0 &&
          ipcdetail::to_raw_pointer(m_header.m_root.m_next->m_next) == &m_header.m_root;
}


template<class MutexFamily, class VoidPointer>
inline void simple_seq_fit_impl<MutexFamily, VoidPointer>::zero_free_memory()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   //Iterate through all free portions
   do{
      //Just clear user the memory part reserved for the user
      std::memset( priv_get_user_buffer(block)
                 , 0
             , block->get_user_bytes());
      block = ipcdetail::to_raw_pointer(block->m_next);
   }
   while(block != &m_header.m_root);
}


template<class MutexFamily, class VoidPointer>
inline bool simple_seq_fit_impl<MutexFamily, VoidPointer>::
    check_sanity()
{
   //-----------------------
   boost::interprocess::scoped_lock<interprocess_mutex> guard(m_header);
   //-----------------------
   block_ctrl *block = ipcdetail::to_raw_pointer(m_header.m_root.m_next);

   size_type free_memory = 0;

   //Iterate through all blocks obtaining their size
   while(block != &m_header.m_root){
      algo_impl_t::assert_alignment(block);
      if(!algo_impl_t::check_alignment(block))
         return false;
      //Free blocks's next must be always valid
      block_ctrl *next = ipcdetail::to_raw_pointer(block->m_next);
      if(!next){
         return false;
      }
      free_memory += block->m_size*Alignment;
      block = next;
   }

   //Check allocated bytes are less than size
   if(m_header.m_allocated > m_header.m_size){
      return false;
   }

   //Check free bytes are less than size
   if(free_memory > m_header.m_size){
      return false;
   }
   return true;
}

   multi_simple_seq_fit           (size_type size, size_type extra_hdr_bytes)
      : base_t(size, extra_hdr_bytes){}

   void* allocate             (size_type nbytes)
      {  return base_t::multi_allocate(nbytes);   }

   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }


inline named_condition::~named_condition()
{}


inline void named_condition::notify_one()
{  m_cond.notify_one();  }


inline void named_condition::notify_all()
{  m_cond.notify_all();  }


template <typename L>
inline void named_condition::wait(L& lock)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock);
}


template <typename L, typename Pr>
inline void named_condition::wait(L& lock, Pr pred)
{
   ipcdetail::internal_mutex_lock<L> internal_lock(lock);
   m_cond.wait(internal_lock, pred);
}


inline bool named_condition::remove(const char *name)
{
   return condition_type::remove(name);
}

      void take_ownership(){ m_mutex.take_ownership(); }

   internal_mutex_type &internal_mutex()
   {  return m_mutex;   }


   const internal_mutex_type &internal_mutex() const
   {  return m_mutex;   }


inline interprocess_mutex::interprocess_mutex(){}


inline interprocess_mutex::~interprocess_mutex(){}


inline void interprocess_mutex::lock()
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = boost::posix_time::microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!m_mutex.timed_lock(wait_time))
      {
         throw interprocess_exception(timeout_when_locking_error
                                     , "Interprocess mutex timeout when locking. Possible deadlock: "
                                       "owner died without unlocking?");
      }
   #else
      m_mutex.lock();
   #endif
}


inline bool interprocess_mutex::try_lock()
{ return m_mutex.try_lock(); }


inline void interprocess_mutex::unlock()
{ m_mutex.unlock(); }


   interprocess_upgradable_mutex *mutex() const
   {  return static_cast<interprocess_upgradable_mutex*>(m_shmem.get_user_address()); }


inline named_upgradable_mutex::~named_upgradable_mutex()
{}


inline void named_upgradable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void named_upgradable_mutex::lock()
{  this->mutex()->lock();  }


inline void named_upgradable_mutex::unlock()
{  this->mutex()->unlock();  }


inline bool named_upgradable_mutex::try_lock()
{  return this->mutex()->try_lock();  }


inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }


inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }


inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }


inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }


inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }


inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }


inline void named_upgradable_mutex::unlock_and_lock_upgradable()
{  this->mutex()->unlock_and_lock_upgradable();  }


inline void named_upgradable_mutex::unlock_and_lock_sharable()
{  this->mutex()->unlock_and_lock_sharable();  }


inline void named_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{  this->mutex()->unlock_upgradable_and_lock_sharable();  }


inline void named_upgradable_mutex::unlock_upgradable_and_lock()
{  this->mutex()->unlock_upgradable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_upgradable_and_lock()
{  return this->mutex()->try_unlock_upgradable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_sharable_and_lock()
{  return this->mutex()->try_unlock_sharable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{  return this->mutex()->try_unlock_sharable_and_lock_upgradable();  }


inline bool named_upgradable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

   
      condvar_type &get_condvar() {  return m_cond;  }

      mutex_type   &get_mutex()   {  return m_mut; }

   interprocess_condition_any(){}

   ~interprocess_condition_any(){}

   void notify_one()
   {  m_cond.notify_one();  }

   void notify_all()
   {  m_cond.notify_all();  }

   template <typename L>
   void wait(L& lock)
   {  m_cond.wait(lock);  }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_cond.wait(lock, pred);  }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time);  }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred);  }


   interprocess_sharable_mutex *mutex() const
   {  return static_cast<interprocess_sharable_mutex*>(m_shmem.get_user_address()); }


inline named_sharable_mutex::~named_sharable_mutex()
{}


inline void named_sharable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void named_sharable_mutex::lock()
{  this->mutex()->lock();  }


inline void named_sharable_mutex::unlock()
{  this->mutex()->unlock();  }


inline bool named_sharable_mutex::try_lock()
{  return this->mutex()->try_lock();  }


inline void named_sharable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }


inline void named_sharable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }


inline bool named_sharable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }


inline bool named_sharable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }


inline named_recursive_mutex::~named_recursive_mutex()
{}


inline void named_recursive_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut);  }


inline void named_recursive_mutex::lock()
{  m_mut.lock();  }


inline void named_recursive_mutex::unlock()
{  m_mut.unlock();  }


inline bool named_recursive_mutex::try_lock()
{  return m_mut.try_lock();  }


inline bool named_recursive_mutex::remove(const char *name)
{  return impl_t::remove(name); }

   file_lock(BOOST_RV_REF(file_lock) moved)
      :  m_file_hnd(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   file_lock &operator=(BOOST_RV_REF(file_lock) moved)
   {
      file_lock tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   void swap(file_lock &other)
   {
      file_handle_t tmp = m_file_hnd;
      m_file_hnd = other.m_file_hnd;
      other.m_file_hnd = tmp;
   }


   bool timed_acquire_file_lock
      (file_handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
   {
      //Obtain current count and target time
      boost::posix_time::ptime now = microsec_clock::universal_time();
      using namespace boost::detail;

      if(now >= abs_time) return false;

      do{
         if(!ipcdetail::try_acquire_file_lock(hnd, acquired))
            return false;

         if(acquired)
            return true;
         else{
            now = microsec_clock::universal_time();

            if(now >= abs_time){
               acquired = false;
               return true;
            }
            // relinquish current time slice
            ipcdetail::thread_yield();
         }
      }while (true);
   }


   bool timed_acquire_file_lock_sharable
      (file_handle_t hnd, bool &acquired, const boost::posix_time::ptime &abs_time)
   {
      //Obtain current count and target time
      boost::posix_time::ptime now = microsec_clock::universal_time();
      using namespace boost::detail;

      if(now >= abs_time) return false;

      do{
         if(!ipcdetail::try_acquire_file_lock_sharable(hnd, acquired))
            return false;

         if(acquired)
            return true;
         else{
            now = microsec_clock::universal_time();

            if(now >= abs_time){
               acquired = false;
               return true;
            }
            // relinquish current time slice
            ipcdetail::thread_yield();
         }
      }while (true);
   }


inline file_lock::file_lock(const char *name)
{
   m_file_hnd = ipcdetail::open_existing_file(name, read_write);

   if(m_file_hnd == ipcdetail::invalid_file()){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}


inline file_lock::~file_lock()
{
   if(m_file_hnd != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_file_hnd);
      m_file_hnd = ipcdetail::invalid_file();
   }
}


inline void file_lock::lock()
{
   if(!ipcdetail::acquire_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}


inline bool file_lock::try_lock()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}


inline void file_lock::unlock()
{
   if(!ipcdetail::release_file_lock(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}


inline void file_lock::lock_sharable()
{
   if(!ipcdetail::acquire_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}


inline bool file_lock::try_lock_sharable()
{
   bool result;
   if(!ipcdetail::try_acquire_file_lock_sharable(m_file_hnd, result)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
   return result;
}


inline void file_lock::unlock_sharable()
{
   if(!ipcdetail::release_file_lock_sharable(m_file_hnd)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

   interprocess_condition()
   {}

   ~interprocess_condition()
   {}

   void notify_one()
   {  m_condition.notify_one();  }

   void notify_all()
   {  m_condition.notify_all();  }

   template <typename L>
   void wait(L& lock)
   {  
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock);
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock, pred);
   }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time);
   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time, pred);
   }

      exclusive_rollback(control_word_t         &ctrl
                        ,interprocess_condition &first_gate)
         :  mp_ctrl(&ctrl), m_first_gate(first_gate)
      {}


      void release()
      {  mp_ctrl = 0;   }


      ~exclusive_rollback()
      {
         if(mp_ctrl){
            mp_ctrl->exclusive_in = 0;
            m_first_gate.notify_all();
         }
      }

      upgradable_to_exclusive_rollback(control_word_t         &ctrl)
         :  mp_ctrl(&ctrl)
      {}


      void release()
      {  mp_ctrl = 0;   }


      ~upgradable_to_exclusive_rollback()
      {
         if(mp_ctrl){
            //Recover upgradable lock
            mp_ctrl->upgradable_in = 1;
            ++mp_ctrl->num_upr_shar;
            //Execute the second half of exclusive locking
            mp_ctrl->exclusive_in = 0;
         }
      }


inline interprocess_upgradable_mutex::interprocess_upgradable_mutex()
{
   this->m_ctrl.exclusive_in  = 0;
   this->m_ctrl.upgradable_in = 0;
   this->m_ctrl.num_upr_shar   = 0;
}


inline interprocess_upgradable_mutex::~interprocess_upgradable_mutex()
{}


inline void interprocess_upgradable_mutex::lock()
{
   scoped_lock_t lck(m_mut);

   //The exclusive lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   while (this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in){
      this->m_first_gate.wait(lck);
   }

   //Mark that exclusive lock has been acquired
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   exclusive_rollback rollback(this->m_ctrl, this->m_first_gate);

   //Now wait until all readers are gone
   while (this->m_ctrl.num_upr_shar){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}


inline bool interprocess_upgradable_mutex::try_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive, upgradable
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_upr_shar){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   return true;
}


inline void interprocess_upgradable_mutex::unlock()
{
   scoped_lock_t lck(m_mut);
   this->m_ctrl.exclusive_in = 0;
   this->m_first_gate.notify_all();
}


inline void interprocess_upgradable_mutex::lock_upgradable()
{
   scoped_lock_t lck(m_mut);

   //The upgradable lock must block in the first gate
   //if an exclusive or upgradable lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in || this->m_ctrl.upgradable_in
         || this->m_ctrl.num_upr_shar == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 1;
   ++this->m_ctrl.num_upr_shar;
}


inline bool interprocess_upgradable_mutex::try_lock_upgradable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The upgradable lock must fail
   //if an exclusive or upgradable lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in
      || this->m_ctrl.num_upr_shar == constants::max_readers){
      return false;
   }

   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 1;
   ++this->m_ctrl.num_upr_shar;
   return true;
}


inline void interprocess_upgradable_mutex::unlock_upgradable()
{
   scoped_lock_t lck(m_mut);
   //Mark that upgradable lock has been acquired
   //And add upgradable to the sharable count
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   this->m_first_gate.notify_all();
}


inline void interprocess_upgradable_mutex::lock_sharable()
{
   scoped_lock_t lck(m_mut);

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in
        || this->m_ctrl.num_upr_shar == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Increment sharable count
   ++this->m_ctrl.num_upr_shar;
}


inline bool interprocess_upgradable_mutex::try_lock_sharable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The sharable lock must fail
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_upr_shar == constants::max_readers){
      return false;
   }

   //Increment sharable count
   ++this->m_ctrl.num_upr_shar;
   return true;
}


inline void interprocess_upgradable_mutex::unlock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Decrement sharable count
   --this->m_ctrl.num_upr_shar;
   if (this->m_ctrl.num_upr_shar == 0){
      this->m_second_gate.notify_one();
   }
   //Check if there are blocked sharables because of
   //there were too many sharables
   else if(this->m_ctrl.num_upr_shar == (constants::max_readers-1)){
      this->m_first_gate.notify_all();
   }
}


inline void interprocess_upgradable_mutex::unlock_and_lock_upgradable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as exclusive
   this->m_ctrl.exclusive_in     = 0;
   //Mark it as upgradable
   this->m_ctrl.upgradable_in    = 1;
   //The sharable count should be 0 so increment it
   this->m_ctrl.num_upr_shar   = 1;
   //Notify readers that they can enter
   m_first_gate.notify_all();
}


inline void interprocess_upgradable_mutex::unlock_and_lock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as exclusive
   this->m_ctrl.exclusive_in   = 0;
   //The sharable count should be 0 so increment it
   this->m_ctrl.num_upr_shar   = 1;
   //Notify readers that they can enter
   m_first_gate.notify_all();
}


inline void interprocess_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Unmark it as upgradable (we don't have to decrement count)
   this->m_ctrl.upgradable_in    = 0;
   //Notify readers/upgradable that they can enter
   m_first_gate.notify_all();
}


inline void interprocess_upgradable_mutex::unlock_upgradable_and_lock()
{
   scoped_lock_t lck(m_mut);
   //Simulate unlock_upgradable() without
   //notifying sharables.
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   //Execute the second half of exclusive locking
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   upgradable_to_exclusive_rollback rollback(m_ctrl);

   while (this->m_ctrl.num_upr_shar){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}


inline bool interprocess_upgradable_mutex::try_unlock_upgradable_and_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);
   //Check if there are no readers
   if(!lck.owns()
      || this->m_ctrl.num_upr_shar != 1){
      return false;
   }
   //Now unlock upgradable and mark exclusive
   this->m_ctrl.upgradable_in = 0;
   --this->m_ctrl.num_upr_shar;
   this->m_ctrl.exclusive_in = 1;
   return true;
}


inline bool interprocess_upgradable_mutex::try_unlock_sharable_and_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive, upgradable
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in
      || this->m_ctrl.num_upr_shar != 1){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   this->m_ctrl.num_upr_shar = 0;
   return true;
}


inline bool interprocess_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The upgradable lock must fail
   //if an exclusive or upgradable lock has been acquired
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.upgradable_in){
      return false;
   }

   //Mark that upgradable lock has been acquired
   this->m_ctrl.upgradable_in = 1;
   return true;
}

   null_mutex(){}

   ~null_mutex(){}

   void lock(){}

   bool try_lock()
   {  return true;   }

   bool timed_lock(const boost::posix_time::ptime &)
   {  return true;   }

   void unlock(){}

   void lock_sharable(){}

   bool try_lock_sharable()
   {  return true;   }

   bool timed_lock_sharable(const boost::posix_time::ptime &)
   {  return true;   }

   void unlock_sharable(){}

   void lock_upgradable(){}

   bool try_lock_upgradable()
   {  return true;   }

   bool timed_lock_upgradable(const boost::posix_time::ptime &)
   {  return true;   }

   void unlock_upgradable(){}

   void unlock_and_lock_upgradable(){}

   void unlock_and_lock_sharable(){}

   void unlock_upgradable_and_lock_sharable(){}

   void unlock_upgradable_and_lock(){}

   bool try_unlock_upgradable_and_lock()
   {  return true;   }

   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &)
   {  return true;   }

   bool try_unlock_sharable_and_lock()
   {  return true;   }

   bool try_unlock_sharable_and_lock_upgradable()
   {  return true;   }

      exclusive_rollback(control_word_t         &ctrl
                        ,interprocess_condition &first_gate)
         :  mp_ctrl(&ctrl), m_first_gate(first_gate)
      {}


      void release()
      {  mp_ctrl = 0;   }


      ~exclusive_rollback()
      {
         if(mp_ctrl){
            mp_ctrl->exclusive_in = 0;
            m_first_gate.notify_all();
         }
      }


inline interprocess_sharable_mutex::interprocess_sharable_mutex()
{
   this->m_ctrl.exclusive_in  = 0;
   this->m_ctrl.num_shared   = 0;
}


inline interprocess_sharable_mutex::~interprocess_sharable_mutex()
{}


inline void interprocess_sharable_mutex::lock()
{
   scoped_lock_t lck(m_mut);

   //The exclusive lock must block in the first gate
   //if an exclusive lock has been acquired
   while (this->m_ctrl.exclusive_in){
      this->m_first_gate.wait(lck);
   }

   //Mark that exclusive lock has been acquired
   this->m_ctrl.exclusive_in = 1;

   //Prepare rollback
   exclusive_rollback rollback(this->m_ctrl, this->m_first_gate);

   //Now wait until all readers are gone
   while (this->m_ctrl.num_shared){
      this->m_second_gate.wait(lck);
   }
   rollback.release();
}


inline bool interprocess_sharable_mutex::try_lock()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //If we can't lock or any has there is any exclusive
   //or sharable mark return false;
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_shared){
      return false;
   }
   this->m_ctrl.exclusive_in = 1;
   return true;
}


inline void interprocess_sharable_mutex::unlock()
{
   scoped_lock_t lck(m_mut);
   this->m_ctrl.exclusive_in = 0;
   this->m_first_gate.notify_all();
}


inline void interprocess_sharable_mutex::lock_sharable()
{
   scoped_lock_t lck(m_mut);

   //The sharable lock must block in the first gate
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   while(this->m_ctrl.exclusive_in
        || this->m_ctrl.num_shared == constants::max_readers){
      this->m_first_gate.wait(lck);
   }

   //Increment sharable count
   ++this->m_ctrl.num_shared;
}


inline bool interprocess_sharable_mutex::try_lock_sharable()
{
   scoped_lock_t lck(m_mut, try_to_lock);

   //The sharable lock must fail
   //if an exclusive lock has been acquired
   //or there are too many sharable locks
   if(!lck.owns()
      || this->m_ctrl.exclusive_in
      || this->m_ctrl.num_shared == constants::max_readers){
      return false;
   }

   //Increment sharable count
   ++this->m_ctrl.num_shared;
   return true;
}


inline void interprocess_sharable_mutex::unlock_sharable()
{
   scoped_lock_t lck(m_mut);
   //Decrement sharable count
   --this->m_ctrl.num_shared;
   if (this->m_ctrl.num_shared == 0){
      this->m_second_gate.notify_one();
   }
   //Check if there are blocked sharables because of
   //there were too many sharables
   else if(this->m_ctrl.num_shared == (constants::max_readers-1)){
      this->m_first_gate.notify_all();
   }
}


inline interprocess_semaphore::interprocess_semaphore(unsigned int initialCount)
   : m_sem(initialCount)
{}


inline interprocess_semaphore::~interprocess_semaphore(){}


inline void interprocess_semaphore::wait()
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = boost::posix_time::microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!m_sem.timed_wait(wait_time))
      {
         throw interprocess_exception(timeout_when_waiting_error, "Interprocess semaphore timeout when waiting. Possible deadlock: owner died without posting?");
      }
   #else
      m_sem.wait();
   #endif
}

inline bool interprocess_semaphore::try_wait()
{ return m_sem.try_wait(); }


inline void interprocess_semaphore::post()
{ m_sem.post(); }

   internal_mutex_type &internal_mutex()
   {  return m_mut; }


inline void named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut); }


inline named_mutex::~named_mutex()
{}


inline void named_mutex::lock()
{  m_mut.lock();  }


inline void named_mutex::unlock()
{  m_mut.unlock();  }


inline bool named_mutex::try_lock()
{  return m_mut.try_lock();  }


inline bool named_mutex::remove(const char *name)
{  return internal_mutex_type::remove(name);   }

   ~named_condition_any()
   {}

   void notify_one()
   {  m_cond.notify_one();  }

   void notify_all()
   {  m_cond.notify_all();  }

   template <typename L>
   void wait(L& lock)
   {  return m_cond.wait(lock); }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  return m_cond.wait(lock, pred); }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time); }

   static bool remove(const char *name)
   {  return condition_any_type::remove(name);  }

   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }

   scoped_lock()
      : mp_mutex(0), m_locked(false)
   {}

   explicit scoped_lock(mutex_type& m)
      : mp_mutex(&m), m_locked(false)
   {  mp_mutex->lock();   m_locked = true;  }

   scoped_lock(BOOST_RV_REF(scoped_lock) scop)
      : mp_mutex(0), m_locked(scop.owns())
   {  mp_mutex = scop.release(); }

   ~scoped_lock()
   {
      try{  if(m_locked && mp_mutex)   mp_mutex->unlock();  }
      catch(...){}
   }

   scoped_lock &operator=(BOOST_RV_REF(scoped_lock) scop)
   {
      if(this->owns())
         this->unlock();
      m_locked = scop.owns();
      mp_mutex = scop.release();
      return *this;
   }

   void lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      mp_mutex->lock();
      m_locked = true;
   }

   bool try_lock()
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->try_lock();
      return m_locked;
   }

   bool timed_lock(const boost::posix_time::ptime& abs_time)
   {
      if(!mp_mutex || m_locked)
         throw lock_exception();
      m_locked = mp_mutex->timed_lock(abs_time);
      return m_locked;
   }

   void unlock()
   {
      if(!mp_mutex || !m_locked)
         throw lock_exception();
      mp_mutex->unlock();
      m_locked = false;
   }

   bool owns() const
   {  return m_locked && mp_mutex;  }


inline named_semaphore::~named_semaphore()
{}


inline void named_semaphore::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_sem);  }


inline void named_semaphore::wait()
{  m_sem.wait();  }


inline void named_semaphore::post()
{  m_sem.post();  }


inline bool named_semaphore::try_wait()
{  return m_sem.try_wait();  }


inline bool named_semaphore::remove(const char *name)
{  return impl_t::remove(name);   }

      void take_ownership(){ mutex.take_ownership(); }


inline interprocess_recursive_mutex::interprocess_recursive_mutex(){}


inline interprocess_recursive_mutex::~interprocess_recursive_mutex(){}


inline void interprocess_recursive_mutex::lock()
{
   #ifdef BOOST_INTERPROCESS_ENABLE_TIMEOUT_WHEN_LOCKING
      boost::posix_time::ptime wait_time
         = boost::posix_time::microsec_clock::universal_time()
         + boost::posix_time::milliseconds(BOOST_INTERPROCESS_TIMEOUT_WHEN_LOCKING_DURATION_MS);
      if (!mutex.timed_lock(wait_time)){
         throw interprocess_exception(timeout_when_locking_error, "Interprocess mutex timeout when locking. Possible deadlock: owner died without unlocking?");
      }
   #else
      mutex.lock();
   #endif
}


inline bool interprocess_recursive_mutex::try_lock()
{ return mutex.try_lock(); }


inline void interprocess_recursive_mutex::unlock()
{ mutex.unlock(); }


template<class ConditionAnyMembers>
void condition_any_algorithm<ConditionAnyMembers>::signal(ConditionAnyMembers &data, bool broadcast)
{
   scoped_lock<mutex_type> internal_lock(data.get_mutex());
   if(broadcast){
      data.get_condvar().notify_all();
   }
   else{
      data.get_condvar().notify_one();
   }
}

template <class Lock>
void condition_any_algorithm<ConditionAnyMembers>::do_wait
   (ConditionAnyMembers &data, Lock& lock)
{
   //lock internal before unlocking external to avoid race with a notifier
   scoped_lock<mutex_type> internal_lock(data.get_mutex());
   {
      lock_inverter<Lock> inverted_lock(lock);
      scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);
      {  //unlock internal first to avoid deadlock with near simultaneous waits
         scoped_lock<mutex_type>     internal_unlock;
         internal_lock.swap(internal_unlock);
         data.get_condvar().wait(internal_unlock);
      }
   }
}


   condition_any_wrapper(){}


   ~condition_any_wrapper(){}


   ConditionAnyMembers & get_members()
   {  return m_data; }


   const ConditionAnyMembers & get_members() const
   {  return m_data; }


   void notify_one()
   {  algo_type::signal(m_data, false);  }


   void notify_all()
   {  algo_type::signal(m_data, true);  }


   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }


   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }


   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      if (!lock)
         throw lock_exception();
      return algo_type::wait(m_data, lock, true, abs_time);
   }


template<class ConditionMembers>
inline void condition_algorithm_8a<ConditionMembers>::signal(ConditionMembers &data, bool broadcast)
{
   integer_type nsignals_to_issue;

   {
      scoped_lock<mutex_type> locker(data.get_mtx_unblock_lock());

      if ( 0 != data.get_nwaiters_to_unblock() ) {        // the gate is closed!!!
         if ( 0 == data.get_nwaiters_blocked() ) {        // NO-OP
            //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
            return;
         }
         if (broadcast) {
            data.get_nwaiters_to_unblock() += nsignals_to_issue = data.get_nwaiters_blocked();
            data.get_nwaiters_blocked() = 0;
         }
         else {
            nsignals_to_issue = 1;
            data.get_nwaiters_to_unblock()++;
            data.get_nwaiters_blocked()--;
         }
      }
      else if ( data.get_nwaiters_blocked() > data.get_nwaiters_gone() ) { // HARMLESS RACE CONDITION!
         data.get_sem_block_lock().wait();                      // close the gate
         if ( 0 != data.get_nwaiters_gone() ) {
            data.get_nwaiters_blocked() -= data.get_nwaiters_gone();
            data.get_nwaiters_gone() = 0;
         }
         if (broadcast) {
            nsignals_to_issue = data.get_nwaiters_to_unblock() = data.get_nwaiters_blocked();
            data.get_nwaiters_blocked() = 0;
         }
         else {
            nsignals_to_issue = data.get_nwaiters_to_unblock() = 1;
            data.get_nwaiters_blocked()--;
         }
      }
      else { // NO-OP
         //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
         return;
      }
      //locker's destructor triggers data.get_mtx_unblock_lock().unlock()
   }
   data.get_sem_block_queue().post(nsignals_to_issue);
}


   condition_8a_wrapper(){}


   ~condition_8a_wrapper(){}


   ConditionMembers & get_members()
   {  return m_data; }


   const ConditionMembers & get_members() const
   {  return m_data; }


   void notify_one()
   {  algo_type::signal(m_data, false);  }


   void notify_all()
   {  algo_type::signal(m_data, true);  }


   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }


   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }


   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      if (!lock)
         throw lock_exception();
      return algo_type::wait(m_data, lock, true, abs_time);
   }

   

   internal_mutex_lock(Lock &l)
      : l_(l)
   {}


   mutex_type* mutex() const
   {  return l_ ? &l_.mutex()->internal_mutex() : 0;  }


   void lock()    { l_.lock(); }


   void unlock()  { l_.unlock(); }


   operator unspecified_bool_type() const
   {  return l_ ? &internal_mutex_lock::lock : 0;  }

   lock_inverter(Lock &l)
      :  l_(l)
   {}

   void lock()    {   l_.unlock();   }

   void unlock()  {   l_.lock();     }


inline spin_recursive_mutex::spin_recursive_mutex()
   : m_nLockCount(0), m_nOwner(ipcdetail::get_invalid_systemwide_thread_id()){}


inline spin_recursive_mutex::~spin_recursive_mutex(){}


inline void spin_recursive_mutex::lock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   if(ipcdetail::equal_systemwide_thread_id(thr_id , old_id)){
      if((unsigned int)(m_nLockCount+1) == 0){
         //Overflow, throw an exception
         throw interprocess_exception("boost::interprocess::spin_recursive_mutex recursive lock overflow");
      }
      ++m_nLockCount;
   }
   else{
      m_mutex.lock();
      ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
      m_nLockCount = 1;
   }
}


inline bool spin_recursive_mutex::try_lock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   if(ipcdetail::equal_systemwide_thread_id(thr_id , old_id)) {  // we own it
      if((unsigned int)(m_nLockCount+1) == 0){
         //Overflow, throw an exception
         throw interprocess_exception("boost::interprocess::spin_recursive_mutex recursive lock overflow");
      }
      ++m_nLockCount;
      return true;
   }
   if(m_mutex.try_lock()){
      ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
      m_nLockCount = 1;
      return true;
   }
   return false;
}


inline void spin_recursive_mutex::unlock()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   handle_t old_id;
   ipcdetail::systemwide_thread_id_copy(m_nOwner, old_id);
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   (void)old_id;
   (void)thr_id;
   BOOST_ASSERT(ipcdetail::equal_systemwide_thread_id(thr_id, old_id));
   --m_nLockCount;
   if(!m_nLockCount){
      const handle_t new_id(ipcdetail::get_invalid_systemwide_thread_id());
      ipcdetail::systemwide_thread_id_copy(new_id, m_nOwner);
      m_mutex.unlock();
   }
}


inline void spin_recursive_mutex::take_ownership()
{
   typedef ipcdetail::OS_systemwide_thread_id_t handle_t;
   this->m_nLockCount = 1;
   const handle_t thr_id(ipcdetail::get_current_systemwide_thread_id());
   ipcdetail::systemwide_thread_id_copy(thr_id, m_nOwner);
}



inline spin_semaphore::~spin_semaphore()
{}


inline spin_semaphore::spin_semaphore(unsigned int initialCount)
{  ipcdetail::atomic_write32(&this->m_count, boost::uint32_t(initialCount));  }


inline void spin_semaphore::post()
{
   ipcdetail::atomic_inc32(&m_count);
}


inline void spin_semaphore::wait()
{
   while(!ipcdetail::atomic_add_unless32(&m_count, boost::uint32_t(-1), boost::uint32_t(0))){
      while(ipcdetail::atomic_read32(&m_count) == 0){
         ipcdetail::thread_yield();
      }
   }
}


inline bool spin_semaphore::try_wait()
{
   return ipcdetail::atomic_add_unless32(&m_count, boost::uint32_t(-1), boost::uint32_t(0));
}


   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      if (!lock)
         throw lock_exception();
      return this->do_timed_wait(abs_time, *lock.mutex());
   }


   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      do_wait(*lock.mutex());
   }


   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         do_wait(*lock.mutex());
   }


inline spin_condition::spin_condition()
{
   //Note that this class is initialized to zero.
   //So zeroed memory can be interpreted as an initialized
   //condition variable
   m_command      = SLEEP;
   m_num_waiters  = 0;
}


inline spin_condition::~spin_condition()
{
   //Trivial destructor
}


inline void spin_condition::notify_one()
{
   this->notify(NOTIFY_ONE);
}


inline void spin_condition::notify_all()
{
   this->notify(NOTIFY_ALL);
}


template<class InterprocessMutex>
inline void spin_condition::do_wait(InterprocessMutex &mut)
{
   this->do_timed_wait(false, boost::posix_time::ptime(), mut);
}

   void take_ownership(){};


inline spin_mutex::spin_mutex()
   : m_s(0)
{
   //Note that this class is initialized to zero.
   //So zeroed memory can be interpreted as an
   //initialized mutex
}


inline spin_mutex::~spin_mutex()
{
   //Trivial destructor
}


inline void spin_mutex::lock(void)
{
   do{
      boost::uint32_t prev_s = ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 1, 0);

      if (m_s == 1 && prev_s == 0){
            break;
      }
      // relinquish current timeslice
      ipcdetail::thread_yield();
   }while (true);
}


inline bool spin_mutex::try_lock(void)
{
   boost::uint32_t prev_s = ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 1, 0);
   return m_s == 1 && prev_s == 0;
}


inline void spin_mutex::unlock(void)
{  ipcdetail::atomic_cas32(const_cast<boost::uint32_t*>(&m_s), 0, 1);   }


inline windows_named_sync_interface::~windows_named_sync_interface()
{}


inline windows_named_sync::windows_named_sync()
   : m_file_hnd(winapi::invalid_handle_value)
{}


inline void windows_named_sync::close(windows_named_sync_interface &sync_interface)
{
   const std::size_t buflen = sync_interface.get_data_size();
   const std::size_t sizeof_file_info = sizeof(sync_id::internal_type) + buflen;
   winapi::interprocess_overlapped overlapped;
   if(winapi::lock_file_ex
      (m_file_hnd, winapi::lockfile_exclusive_lock, 0, sizeof_file_info, 0, &overlapped)){
      if(winapi::set_file_pointer_ex(m_file_hnd, sizeof(sync_id::internal_type), 0, winapi::file_begin)){
         const void *buf = sync_interface.buffer_with_final_data_to_file();

         unsigned long written_or_read = 0;
         if(winapi::write_file(m_file_hnd, buf, buflen, &written_or_read, 0)){
            //...
         }
      }
   }
   sync_interface.close();
   if(m_file_hnd != winapi::invalid_handle_value){
      winapi::close_handle(m_file_hnd);
      m_file_hnd = winapi::invalid_handle_value;
   }
}


inline bool windows_named_sync::remove(const char *name)
{
   try{
      //Make sure a temporary path is created for shared memory
      std::string semfile;
      ipcdetail::tmp_filename(name, semfile);
      return winapi::unlink_file(semfile.c_str());
   }
   catch(...){
      return false;
   }
}

   windows_recursive_mutex() : windows_mutex() {}


inline windows_semaphore::windows_semaphore(unsigned int initialCount)
   : id_(this)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Force smeaphore creation with the initial count
   bool open_or_created;
   handles.obtain_semaphore(this->id_, initialCount, &open_or_created);
   //The semaphore must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}


inline windows_semaphore::~windows_semaphore()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}


inline void windows_semaphore::wait(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   sem.wait();
}


inline bool windows_semaphore::try_wait(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   return sem.try_wait();
}


inline void windows_semaphore::post(long release_count)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   winapi_semaphore_functions sem(handles.obtain_semaphore(this->id_, 0));
   sem.post(release_count);
}

   windows_condition()
      : m_condition_data()
   {}


   ~windows_condition()
   {}


   void notify_one()
   {  m_condition_data.notify_one();   }


   void notify_all()
   {  m_condition_data.notify_all();   }


   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }


   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }


   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }


      condition_data()
         : m_nwaiters_blocked(0)
         , m_nwaiters_gone(0)
         , m_nwaiters_to_unblock(0)
         , m_sem_block_queue(0)
         , m_sem_block_lock(1)
         , m_mtx_unblock_lock()
      {}


      integer_type    &get_nwaiters_blocked()
      {  return m_nwaiters_blocked;  }


      integer_type    &get_nwaiters_gone()
      {  return m_nwaiters_gone;  }


      integer_type    &get_nwaiters_to_unblock()
      {  return m_nwaiters_to_unblock;  }


      semaphore_type  &get_sem_block_queue()
      {  return m_sem_block_queue;  }


      semaphore_type  &get_sem_block_lock()
      {  return m_sem_block_lock;  }


      mutex_type      &get_mtx_unblock_lock()
      {  return m_mtx_unblock_lock;  }


inline bool bytes_to_str(const void *mem, const std::size_t mem_length, char *out_str, std::size_t &out_length)
{
   const std::size_t need_mem = mem_length*2+1;
   if(out_length < need_mem){
      out_length = need_mem;
      return false;
   }

   const char Characters [] =
      { '0', '1', '2', '3', '4', '5', '6', '7'
      , '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

   std::size_t char_counter = 0;
   const char *buf = (const char *)mem;
   for(std::size_t i = 0; i != mem_length; ++i){
      out_str[char_counter++] = Characters[(buf[i]&0xF0)>>4];
      out_str[char_counter++] = Characters[(buf[i]&0x0F)];
   }
   out_str[char_counter] = 0;
   return true;
}

   sync_id(const void *map_addr)
      : map_addr_(map_addr)
   {  winapi::query_performance_counter(&rand_);  }


   explicit sync_id(internal_type val, const void *map_addr)
      : map_addr_(map_addr)
   {  rand_ = val;  }


   const internal_type &internal_pod() const
   {  return rand_;  }


   internal_type &internal_pod()
   {  return rand_;  }


   const void *map_address() const
   {  return map_addr_;  }

      bool operator()(sync_id const * const l, sync_id const * const r) const
      {  return l->map_address() <  r->map_address(); }



   void fill_name(NameBuf &name, const sync_id &id)
   {
      const char *n = "Global\\boost.ipc";
      std::size_t i = 0;
      do{
         name[i] = n[i];
         ++i;
      } while(n[i]);
      std::size_t len = sizeof(NameBuf) - LengthOfGlobal;
      bytes_to_str(&id.internal_pod(), sizeof(id.internal_pod()), &name[LengthOfGlobal], len);
   }


   void throw_if_error(void *hnd_val)
   {
      if(!hnd_val){
         error_info err(winapi::get_last_error());
         throw interprocess_exception(err);
      }
   }


   void* open_or_create_semaphore(const sync_id &id, unsigned int initial_count)
   {
      NameBuf name;
      fill_name(name, id);
      permissions unrestricted_security;
      unrestricted_security.set_unrestricted();
      winapi_semaphore_wrapper sem_wrapper;
      bool created;
      sem_wrapper.open_or_create
         (name, (long)initial_count, winapi_semaphore_wrapper::MaxCount, unrestricted_security, created);
      throw_if_error(sem_wrapper.handle());
      return sem_wrapper.release();
   }


   void* open_or_create_mutex(const sync_id &id)
   {
      NameBuf name;
      fill_name(name, id);
      permissions unrestricted_security;
      unrestricted_security.set_unrestricted();
      winapi_mutex_wrapper mtx_wrapper;
      mtx_wrapper.open_or_create(name, unrestricted_security);
      throw_if_error(mtx_wrapper.handle());
      return mtx_wrapper.release();
   }

   void *obtain_mutex(const sync_id &id, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         map_[&it->first] = it;
         hnd_val = open_or_create_mutex(id);
         if(popen_created) *popen_created = true;
      }
      else if(popen_created){
         *popen_created = false;
      }
      return hnd_val;
   }


   void *obtain_semaphore(const sync_id &id, unsigned int initial_count, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         map_[&it->first] = it;
         hnd_val = open_or_create_semaphore(id, initial_count);
         if(popen_created) *popen_created = true;
      }
      else if(popen_created){
         *popen_created = false;
      }
      return hnd_val;
   }


   void destroy_handle(const sync_id &id)
   {
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.find(id);
      umap_type::iterator itend = umap_.end();

      if(it != itend){
         winapi::close_handle(it->second);
         const map_type::key_type &k = &it->first;
         map_.erase(k);
         umap_.erase(it);
      }
   }


   void destroy_syncs_in_range(const void *addr, std::size_t size)
   {
      const sync_id low_id(addr);
      const sync_id hig_id(static_cast<const char*>(addr)+size);
      scoped_lock<spin_mutex> lock(mtx_);
      map_type::iterator itlow(map_.lower_bound(&low_id)),
                         ithig(map_.lower_bound(&hig_id));
      while(itlow != ithig){
         void * const hnd = umap_[*itlow->first];
         winapi::close_handle(hnd);
         umap_.erase(*itlow->first);
         itlow = map_.erase(itlow);
      }
   }

   void take_ownership(){};


inline windows_mutex::windows_mutex()
   : id_(this)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //Create mutex with the initial count
   bool open_or_created;
   (void)handles.obtain_mutex(this->id_, &open_or_created);
   //The mutex must be created, never opened
   BOOST_ASSERT(open_or_created);
   BOOST_ASSERT(open_or_created && winapi::get_last_error() != winapi::error_already_exists);
   (void)open_or_created;
}


inline windows_mutex::~windows_mutex()
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   handles.destroy_handle(this->id_);
}


inline void windows_mutex::lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   mut.lock();
}


inline bool windows_mutex::try_lock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.try_lock();
}


inline void windows_mutex::unlock(void)
{
   sync_handles &handles =
      windows_intermodule_singleton<sync_handles>::get();
   //This can throw
   winapi_mutex_functions mut(handles.obtain_mutex(this->id_));
   return mut.unlock();
}

      named_mut_callbacks(winapi_mutex_wrapper &mtx_wrapper)
         : m_mtx_wrapper(mtx_wrapper)
      {}


      virtual std::size_t get_data_size() const
      {  return 0u;   }


      virtual const void *buffer_with_init_data_to_file()
      {  return 0; }


      virtual const void *buffer_with_final_data_to_file()
      {  return 0; }


      virtual void *buffer_to_store_init_data_from_file()
      {  return 0; }


      virtual bool open(create_enum_t, const char *id_name)
      {
         std::string aux_str  = "Global\\bipc.mut.";
         aux_str += id_name;
         //
         permissions mut_perm;
         mut_perm.set_unrestricted();
         return m_mtx_wrapper.open_or_create(aux_str.c_str(), mut_perm);
      }


      virtual void close()
      {
         m_mtx_wrapper.close();
      }


      virtual ~named_mut_callbacks()
      {}


inline windows_named_mutex::~windows_named_mutex()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.close(callbacks);
}


inline void windows_named_mutex::dont_close_on_destruction()
{}


inline void windows_named_mutex::unlock()
{
   m_mtx_wrapper.unlock();
}


inline void windows_named_mutex::lock()
{
   m_mtx_wrapper.lock();
}


inline bool windows_named_mutex::try_lock()
{
   return m_mtx_wrapper.try_lock();
}


inline bool windows_named_mutex::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

   winapi_mutex_functions(void *mtx_hnd)
      : m_mtx_hnd(mtx_hnd)
   {}


   void unlock()
   {
      winapi::release_mutex(m_mtx_hnd);
   }


   void lock()
   {
      if(winapi::wait_for_single_object(m_mtx_hnd, winapi::infinite_time) != winapi::wait_object_0){
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }


   bool try_lock()
   {
      unsigned long ret = winapi::wait_for_single_object(m_mtx_hnd, 0);
      if(ret == winapi::wait_object_0){
         return true;
      }
      else if(ret == winapi::wait_timeout){
         return false;
      }
      else{
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }


   bool timed_lock(const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->lock();
         return true;
      }

      unsigned long ret = winapi::wait_for_single_object
         (m_mtx_hnd, (abs_time - microsec_clock::universal_time()).total_milliseconds());
      if(ret == winapi::wait_object_0){
         return true;
      }
      else if(ret == winapi::wait_timeout){
         return false;
      }
      else{
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }

   winapi_mutex_wrapper(void *mtx_hnd = winapi::invalid_handle_value)
      : winapi_mutex_functions(mtx_hnd)
   {}


   ~winapi_mutex_wrapper()
   {  this->close(); }


   void *release()
   {
      void *hnd = m_mtx_hnd;
      m_mtx_hnd = winapi::invalid_handle_value;
      return hnd;
   }


   void *handle() const
   {  return m_mtx_hnd; }


   bool open_or_create(const char *name, const permissions &perm)
   {
      if(m_mtx_hnd == winapi::invalid_handle_value){
         m_mtx_hnd = winapi::open_or_create_mutex
            ( name
            , false
            , (winapi::interprocess_security_attributes*)perm.get_permissions()
            );
         return m_mtx_hnd != winapi::invalid_handle_value;
      }
      else{
         return false;
      }
   }
  

   void close()
   {
      if(m_mtx_hnd != winapi::invalid_handle_value){
         winapi::close_handle(m_mtx_hnd);
         m_mtx_hnd = winapi::invalid_handle_value;
      }
   }


   void swap(winapi_mutex_wrapper &other)
   {  void *tmp = m_mtx_hnd; m_mtx_hnd = other.m_mtx_hnd; other.m_mtx_hnd = tmp;   }


   ~windows_named_condition_any()
   {
      named_cond_callbacks callbacks(m_condition_data.get_members());
      m_named_sync.close(callbacks);
   }


   void notify_one()
   {  m_condition_data.notify_one();   }


   void notify_all()
   {  m_condition_data.notify_all();   }


   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_condition_data.timed_wait(lock, abs_time);   }


   template <typename L>
   void wait(L& lock)
   {  m_condition_data.wait(lock);   }


   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_condition_data.wait(lock, pred);   }


   static bool remove(const char *name)
   {  return windows_named_sync::remove(name);  }


   void windows_named_condition_any::dont_close_on_destruction()
   {}


      integer_type    &get_nwaiters_blocked()
      {  return m_nwaiters_blocked;  }


      integer_type    &get_nwaiters_gone()
      {  return m_nwaiters_gone;  }


      integer_type    &get_nwaiters_to_unblock()
      {  return m_nwaiters_to_unblock;  }


      semaphore_type  &get_sem_block_queue()
      {  return m_sem_block_queue;  }


      semaphore_type  &get_sem_block_lock()
      {  return m_sem_block_lock;  }


      mutex_type      &get_mtx_unblock_lock()
      {  return m_mtx_unblock_lock;  }

      named_cond_callbacks(condition_data &cond_data)
         : m_condition_data(cond_data)
      {}


      virtual std::size_t get_data_size() const
      {  return sizeof(sem_counts);   }


      virtual const void *buffer_with_final_data_to_file()
      {
         sem_counts[0] = m_condition_data.m_sem_block_queue.value();
         sem_counts[1] = m_condition_data.m_sem_block_lock.value();
         return &sem_counts;
      }


      virtual const void *buffer_with_init_data_to_file()
      {
         sem_counts[0] = 0;
         sem_counts[1] = 1;
         return &sem_counts;
      }


      virtual void *buffer_to_store_init_data_from_file()
      {  return &sem_counts; }


      virtual bool open(create_enum_t, const char *id_name)
      {
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;

         //Now open semaphores and mutex.
         //Use local variables + swap to guarantee consistent
         //initialization and cleanup in case any opening fails
         permissions perm;
         perm.set_unrestricted();
         std::string aux_str  = "Global\\bipc.cond.";
         aux_str += id_name;
         std::size_t pos = aux_str.size();

         //sem_block_queue
         aux_str += "_bq";
         winapi_semaphore_wrapper sem_block_queue;
         bool created;
         if(!sem_block_queue.open_or_create
            (aux_str.c_str(), sem_counts[0], winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //sem_block_lock
         aux_str += "_bl";
         winapi_semaphore_wrapper sem_block_lock;
         if(!sem_block_lock.open_or_create
            (aux_str.c_str(), sem_counts[1], winapi_semaphore_wrapper::MaxCount, perm, created))
            return false;
         aux_str.erase(pos);

         //mtx_unblock_lock
         aux_str += "_ul";
         winapi_mutex_wrapper mtx_unblock_lock;
         if(!mtx_unblock_lock.open_or_create(aux_str.c_str(), perm))
            return false;

         //All ok, commit data
         m_condition_data.m_sem_block_queue.swap(sem_block_queue);
         m_condition_data.m_sem_block_lock.swap(sem_block_lock);
         m_condition_data.m_mtx_unblock_lock.swap(mtx_unblock_lock);
         return true;
      }


      virtual void close()
      {
         m_condition_data.m_sem_block_queue.close();
         m_condition_data.m_sem_block_lock.close();
         m_condition_data.m_mtx_unblock_lock.close();
         m_condition_data.m_nwaiters_blocked = 0;
         m_condition_data.m_nwaiters_gone = 0;
         m_condition_data.m_nwaiters_to_unblock = 0;
      }


      virtual ~named_cond_callbacks()
      {}

      named_sem_callbacks(winapi_semaphore_wrapper &sem_wrapper, sem_count_t sem_cnt)
         : m_sem_wrapper(sem_wrapper), m_sem_count(sem_cnt)
      {}


      virtual std::size_t get_data_size() const
      {  return sizeof(sem_count_t);   }


      virtual const void *buffer_with_final_data_to_file()
      {  return &m_sem_count; }


      virtual const void *buffer_with_init_data_to_file()
      {  return &m_sem_count; }


      virtual void *buffer_to_store_init_data_from_file()
      {  return &m_sem_count; }


      virtual bool open(create_enum_t, const char *id_name)
      {
         std::string aux_str  = "Global\\bipc.sem.";
         aux_str += id_name;
         //
         permissions sem_perm;
         sem_perm.set_unrestricted();
         bool created;
         return m_sem_wrapper.open_or_create
            ( aux_str.c_str(), static_cast<long>(m_sem_count)
            , winapi_semaphore_wrapper::MaxCount, sem_perm, created);
      }


      virtual void close()
      {
         m_sem_wrapper.close();
      }


      virtual ~named_sem_callbacks()
      {}


inline windows_named_semaphore::~windows_named_semaphore()
{
   named_sem_callbacks callbacks(m_sem_wrapper, m_sem_wrapper.value());
   m_named_sync.close(callbacks);
}


inline void windows_named_semaphore::dont_close_on_destruction()
{}


inline void windows_named_semaphore::post()
{
   m_sem_wrapper.post();
}


inline void windows_named_semaphore::wait()
{
   m_sem_wrapper.wait();
}


inline bool windows_named_semaphore::try_wait()
{
   return m_sem_wrapper.try_wait();
}


inline bool windows_named_semaphore::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

   winapi_semaphore_functions(void *hnd)
      : m_sem_hnd(hnd)
   {}


   void post(long count = 1)
   {
      long prev_count;
      winapi::release_semaphore(m_sem_hnd, count, &prev_count);
   }


   void wait()
   {
      if(winapi::wait_for_single_object(m_sem_hnd, winapi::infinite_time) != winapi::wait_object_0){
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }


   bool try_wait()
   {
      unsigned long ret = winapi::wait_for_single_object(m_sem_hnd, 0);
      if(ret == winapi::wait_object_0){
         return true;
      }
      else if(ret == winapi::wait_timeout){
         return false;
      }
      else{
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }


   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->wait();
         return true;
      }

      unsigned long ret = winapi::wait_for_single_object
         (m_sem_hnd, (abs_time - microsec_clock::universal_time()).total_milliseconds());
      if(ret == winapi::wait_object_0){
         return true;
      }
      else if(ret == winapi::wait_timeout){
         return false;
      }
      else{
         error_info err = system_error_code();
         throw interprocess_exception(err);
      }
   }


   long value() const
   {
      long l_count, l_limit;
      if(!winapi::get_semaphore_info(m_sem_hnd, l_count, l_limit))
         return 0;
      return l_count;
   }


   long limit() const
   {
      long l_count, l_limit;
      if(!winapi::get_semaphore_info(m_sem_hnd, l_count, l_limit))
         return 0;
      return l_limit;
   }


   winapi_semaphore_wrapper(void *hnd = winapi::invalid_handle_value)
      : winapi_semaphore_functions(hnd)
   {}


   ~winapi_semaphore_wrapper()
   {  this->close(); }


   void *release()
   {
      void *hnd = m_sem_hnd;
      m_sem_hnd = winapi::invalid_handle_value;
      return hnd;
   }


   void *handle() const
   {  return m_sem_hnd; }


   bool open_or_create( const char *name
                      , long sem_count
                      , long max_count
                      , const permissions &perm
                      , bool &created)
   {
      if(m_sem_hnd == winapi::invalid_handle_value){
         m_sem_hnd = winapi::open_or_create_semaphore
            ( name
            , sem_count
            , max_count
            , (winapi::interprocess_security_attributes*)perm.get_permissions()
            );
         created = winapi::get_last_error() != winapi::error_already_exists;
         return m_sem_hnd != winapi::invalid_handle_value;
      }
      else{
         return false;
      }
   }


   bool open_semaphore(const char *name)
   {
      if(m_sem_hnd == winapi::invalid_handle_value){
         m_sem_hnd = winapi::open_semaphore(name);
         return m_sem_hnd != winapi::invalid_handle_value;
      }
      else{
         return false;
      }
   }


   void close()
   {
      if(m_sem_hnd != winapi::invalid_handle_value){
         winapi::close_handle(m_sem_hnd);
         m_sem_hnd = winapi::invalid_handle_value;
      }
   }


   void swap(winapi_semaphore_wrapper &other)
   {  void *tmp = m_sem_hnd; m_sem_hnd = other.m_sem_hnd; other.m_sem_hnd = tmp;   }


inline posix_recursive_mutex::posix_recursive_mutex()
{
   mutexattr_wrapper mut_attr(true);
   mutex_initializer mut(m_mut, mut_attr);
   mut.release();
}


inline posix_recursive_mutex::~posix_recursive_mutex()
{
   int res = pthread_mutex_destroy(&m_mut);
   BOOST_ASSERT(res == 0);(void)res;
}


inline void posix_recursive_mutex::lock()
{
   if (pthread_mutex_lock(&m_mut) != 0)
      throw lock_exception();
}


inline bool posix_recursive_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}


inline void posix_recursive_mutex::unlock()
{
   int res = 0;
   res = pthread_mutex_unlock(&m_mut);
   BOOST_ASSERT(res == 0); (void)res;
}

   posix_semaphore(unsigned int initialCount)
   {  semaphore_init(&m_sem, initialCount);  }


   ~posix_semaphore()
   {  semaphore_destroy(&m_sem);  }


   void post()
   {  semaphore_post(&m_sem); }


   void wait()
   {  semaphore_wait(&m_sem); }


   bool try_wait()
   {  return semaphore_try_wait(&m_sem); }


   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(&m_sem, abs_time); }


inline timespec ptime_to_timespec (const boost::posix_time::ptime &tm)
{
   const boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
   boost::posix_time::time_duration duration (tm - epoch);
   timespec ts;
   ts.tv_sec  = duration.total_seconds();
   ts.tv_nsec = duration.total_nanoseconds() % 1000000000;
   return ts;
}

   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      this->do_wait(*lock.mutex());
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         this->do_wait(*lock.mutex());
   }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      if (!lock)
            throw lock_exception();
      return this->do_timed_wait(abs_time, *lock.mutex());
   }


inline posix_condition::posix_condition()
{
   int res;
   pthread_condattr_t cond_attr;
   res = pthread_condattr_init(&cond_attr);
   if(res != 0){
      throw interprocess_exception("pthread_condattr_init failed");
   }
   res = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
   if(res != 0){
      pthread_condattr_destroy(&cond_attr);
      throw interprocess_exception(res);
   }
   res = pthread_cond_init(&m_condition, &cond_attr);
   pthread_condattr_destroy(&cond_attr);
   if(res != 0){
      throw interprocess_exception(res);
   }
}


inline posix_condition::~posix_condition()
{
    int res = 0;
    res = pthread_cond_destroy(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}


inline void posix_condition::notify_one()
{
    int res = 0;
    res = pthread_cond_signal(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}


inline void posix_condition::notify_all()
{
    int res = 0;
    res = pthread_cond_broadcast(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}


inline posix_mutex::posix_mutex()
{
   mutexattr_wrapper mut_attr;
   mutex_initializer mut(m_mut, mut_attr);
   mut.release();
}


inline posix_mutex::~posix_mutex()
{
   int res = pthread_mutex_destroy(&m_mut);
   BOOST_ASSERT(res  == 0);(void)res;
}


inline void posix_mutex::lock()
{
   if (pthread_mutex_lock(&m_mut) != 0)
      throw lock_exception();
}


inline bool posix_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}


inline void posix_mutex::unlock()
{
   int res = 0;
   res = pthread_mutex_unlock(&m_mut);
   (void)res;
   BOOST_ASSERT(res == 0);
}


inline void posix_named_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_sem);  }


inline posix_named_mutex::~posix_named_mutex()
{}


inline void posix_named_mutex::lock()
{  m_sem.wait();  }


inline void posix_named_mutex::unlock()
{  m_sem.post();  }


inline bool posix_named_mutex::try_lock()
{  return m_sem.try_wait();  }


inline bool posix_named_mutex::remove(const char *name)
{  return posix_named_semaphore::remove(name);   }


inline bool semaphore_open
   (sem_t *&handle, create_enum_t type, const char *origname,
    unsigned int count = 0, const permissions &perm = permissions())
{
   std::string name;
   #ifndef BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
   add_leading_slash(origname, name);
   #else
   create_tmp_and_clean_old_and_get_filename(origname, name);
   #endif

   //Create new mapping
   int oflag = 0;
   switch(type){
      case DoOpen:
      {
         //No addition
         handle = ::sem_open(name.c_str(), oflag);
      }
      break;
      case DoOpenOrCreate:
      case DoCreate:
      {
         while(1){
            oflag = (O_CREAT | O_EXCL);
            handle = ::sem_open(name.c_str(), oflag, perm.get_permissions(), count);
            if(handle != BOOST_INTERPROCESS_POSIX_SEM_FAILED){
               //We can't change semaphore permissions!
               //::fchmod(handle, perm.get_permissions());
               break;
            }
            else if(errno == EEXIST && type == DoOpenOrCreate){
               oflag = 0;
               if( (handle = ::sem_open(name.c_str(), oflag)) != BOOST_INTERPROCESS_POSIX_SEM_FAILED
                   || (errno != ENOENT) ){
                  break;
               }
            }
            else{
               break;
            }
         }
      }
      break;
      default:
      {
         error_info err(other_error);
         throw interprocess_exception(err);
      }
   }

   //Check for error
   if(handle == BOOST_INTERPROCESS_POSIX_SEM_FAILED){
      throw interprocess_exception(error_info(errno));
   }

   return true;
}


inline void semaphore_close(sem_t *handle)
{
   int ret = sem_close(handle);
   if(ret != 0){
      BOOST_ASSERT(0);
   }
}


inline bool semaphore_unlink(const char *semname)
{
   try{
      std::string sem_str;
      #ifndef BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
      add_leading_slash(semname, sem_str);
      #else
      tmp_filename(semname, sem_str);
      #endif
      return 0 == sem_unlink(sem_str.c_str());
   }
   catch(...){
      return false;
   }
}


inline void semaphore_init(sem_t *handle, unsigned int initialCount)
{
   int ret = sem_init(handle, 1, initialCount);
   //According to SUSV3 version 2003 edition, the return value of a successful
   //sem_init call is not defined, but -1 is returned on failure.
   //In the future, a successful call might be required to return 0.
   if(ret == -1){
      throw interprocess_exception(system_error_code());
   }
}


inline void semaphore_destroy(sem_t *handle)
{
   int ret = sem_destroy(handle);
   if(ret != 0){
      BOOST_ASSERT(0);
   }
}


inline void semaphore_post(sem_t *handle)
{
   int ret = sem_post(handle);
   if(ret != 0){
      throw interprocess_exception(system_error_code());
   }
}


inline void semaphore_wait(sem_t *handle)
{
   int ret = sem_wait(handle);
   if(ret != 0){
      throw interprocess_exception(system_error_code());
   }
}


inline bool semaphore_try_wait(sem_t *handle)
{
   int res = sem_trywait(handle);
   if(res == 0)
      return true;
   if(system_error_code() == EAGAIN){
      return false;
   }
   throw interprocess_exception(system_error_code());
   return false;
}


inline bool semaphore_timed_wait(sem_t *handle, const boost::posix_time::ptime &abs_time)
{
   if(abs_time == boost::posix_time::pos_infin){
      semaphore_wait(handle);
      return true;
   }
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   timespec tspec = ptime_to_timespec(abs_time);
   for (;;){
      int res = sem_timedwait(handle, &tspec);
      if(res == 0)
         return true;
      if (res > 0){
         //buggy glibc, copy the returned error code to errno
         errno = res;
      }
      if(system_error_code() == ETIMEDOUT){
         return false;
      }
      throw interprocess_exception(system_error_code());
   }
   return false;
   #else //#ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   boost::posix_time::ptime now;
   do{
      if(semaphore_try_wait(handle))
         return true;
      thread_yield();
   }while((now = microsec_clock::universal_time()) < abs_time);
   return false;
   #endif   //#ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
}


   ~posix_named_semaphore()
   {
      if(mp_sem != BOOST_INTERPROCESS_POSIX_SEM_FAILED)
         semaphore_close(mp_sem);
   }


   void post()
   {  semaphore_post(mp_sem); }


   void wait()
   {  semaphore_wait(mp_sem); }


   bool try_wait()
   {  return semaphore_try_wait(mp_sem); }


   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(mp_sem, abs_time); }


   static bool remove(const char *name)
   {  return semaphore_unlink(name);   }

   void dont_close_on_destruction()
   {  mp_sem = BOOST_INTERPROCESS_POSIX_SEM_FAILED; }


inline bool advanced_sem_open_or_create(::key_t key, int initval, int &semid, int perm)
{
   semid = -1;
   int id, semval;
   union semun {
      int         val;
      ::semid_ds *buf;
      ushort     *array;
   } semctl_arg;

   if (key == IPC_PRIVATE)
      return false; //not intended for private semaphores

   else if (key == (::key_t) -1)
      return false; //probably an ftok() error by caller

   again:
   if ((id = ::semget(key, 3, (perm & 0x01FF) | IPC_CREAT)) < 0)
      return false;   //permission problem or tables full

   // When the semaphore is created, we know that the value of all
   // 3 members is 0.
   // Get a lock on the semaphore by waiting for [2] to equal 0,
   // then increment it.
   //
   // There is a race condition here.  There is a possibility that
   // between the semget() above and the ::semop() below, another
   // process can call our sem_close() function which can remove
   // the semaphore if that process is the last one using it.
   // Therefore, we handle the error condition of an invalid
   // semaphore ID specially below, and if it does happen, we just
   // go back and create it again.
   struct sembuf op_lock[2] = {
      {2, 0, 0},        // wait for [2] (lock) to equal 0
      {2, 1, SEM_UNDO}  // then increment [2] to 1 - this locks it
                        // UNDO to release the lock if processes exits
                        // before explicitly unlocking
   };

   if (::semop(id, &op_lock[0], 2) < 0) {
      if (errno == EINVAL)
         goto again;
   }

   // Get the value of the process counter.  If it equals 0,
   // then no one has initialized the semaphore yet.
   if ((semval = ::semctl(id, 1, GETVAL, 0)) < 0)
      return false;

   if (semval == 0) {
      // We could initialize by doing a SETALL, but that
      // would clear the adjust value that we set when we
      // locked the semaphore above.  Instead, we'll do 2
      // system calls to initialize [0] and [1].
      semctl_arg.val = initval;
      if (::semctl(id, 0, SETVAL, semctl_arg) < 0)
         return false;

      semctl_arg.val = 1;
      if (::semctl(id, 1, SETVAL, semctl_arg) < 0)
         return false;
   }

   // Decrement the process counter and then release the lock.
   struct sembuf op_unlock[1] = {
      2, -1, 0/*SEM_UNDO*/ // decrement [2] (lock) back to 0
   };

   if (::semop(id, &op_unlock[0], 1) < 0)
      return false;

   semid = id;
   return true;
}


inline bool advanced_sem_rm(int id)
{
   if (::semctl(id, 0, IPC_RMID, 0) < 0)
      return false;
   return true;
}


inline bool advanced_sem_op(int id, int value, bool undo = true)
{
   ::sembuf op_op[1] = {
      0, 99, 0 // decrement or increment [0] with undo on exit
               // the 99 is set to the actual amount to add
               // or subtract (positive or negative)
   };
   if(undo){
      op_op[0].sem_flg = SEM_UNDO;
   }
   if ((op_op[0].sem_op = value) == 0)
      return false;

   if (::semop(id, &op_op[0], 1) < 0)
      return false;
   return true;
}

   xsi_named_mutex(BOOST_RV_REF(xsi_named_mutex) moved)
   {  this->swap(moved);   }


inline xsi_named_mutex::xsi_named_mutex()
   :  m_semid(-1), m_key(-1), m_id(0), m_perm(0), m_path()
{}


inline xsi_named_mutex::~xsi_named_mutex()
{  this->priv_close(); }


inline const char *xsi_named_mutex::get_path() const
{  return m_path.c_str(); }


inline void xsi_named_mutex::swap(xsi_named_mutex &other)
{
   std::swap(m_key,   other.m_key);
   std::swap(m_id,    other.m_id);
   std::swap(m_semid, other.m_semid);
   std::swap(m_perm,  other.m_perm);
   m_path.swap(other.m_path);
}


inline int xsi_named_mutex::get_permissions() const
{  return m_perm; }


inline void xsi_named_mutex::priv_close()
{
}


inline void xsi_named_mutex::lock()
{
   if(!xsi::simple_sem_op(m_semid, -1)){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}


inline void xsi_named_mutex::unlock()
{
   bool success = xsi::simple_sem_op(m_semid, 1);
   (void)success;
   BOOST_ASSERT(success);
}


inline bool xsi_named_mutex::remove()
{
   if(m_semid != -1){
      int ret = ::semctl(m_semid, IPC_RMID, 0);
      if(-1 == ret)
         return false;
      //Now put it in default-constructed state
      m_semid  = -1;
      m_key    = -1;
      m_id     = 0;
      m_perm   = 0;
      m_path.clear();
   }
   return false;
}


inline bool simple_sem_open_or_create(::key_t key, int initval, int &semid, int perm)
{
   int id, semval;
   semid = -1;

   if (key == IPC_PRIVATE)
      return false; //not intended for private semaphores

   else if (key == (::key_t) -1)
      return false; //probably an ftok() error by caller

   again:
   if ((id = ::semget(key, 1, (perm & 0x01FF) | IPC_CREAT)) < 0)
      return false;   //permission problem or tables full

   semid = id;
   return true;
}


inline bool simple_sem_rm(int id)
{
   if (::semctl(id, 0, IPC_RMID, 0) < 0)
      return false;
   return true;
}


inline bool simple_sem_op(int id, int value, bool undo = true)
{
   ::sembuf op_op[1] = {
      0, 99, 0 // decrement or increment [0] with undo on exit
               // the 99 is set to the actual amount to add
               // or subtract (positive or negative)
   };
   if(undo){
      op_op[0].sem_flg = SEM_UNDO;
   }
   if ((op_op[0].sem_op = value) == 0)
      return false;

   if (::semop(id, &op_op[0], 1) < 0)
      return false;
   return true;
}


   internal_condition &internal_cond()
   {  return *static_cast<internal_condition*>(m_shmem.get_user_address()); }


inline shm_named_condition::~shm_named_condition()
{}


inline void shm_named_condition::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void shm_named_condition::notify_one()
{  this->internal_cond().notify_one(); }


inline void shm_named_condition::notify_all()
{  this->internal_cond().notify_all(); }


template <typename L>
inline void shm_named_condition::wait(L& lock)
{  this->internal_cond().wait(lock); }


template <typename L, typename Pr>
inline void shm_named_condition::wait(L& lock, Pr pred)
{  this->internal_cond().wait(lock, pred); }


inline bool shm_named_condition::remove(const char *name)
{  return shared_memory_object::remove(name); }


   interprocess_upgradable_mutex *mutex() const
   {  return static_cast<interprocess_upgradable_mutex*>(m_shmem.get_user_address()); }


inline named_upgradable_mutex::~named_upgradable_mutex()
{}


inline void named_upgradable_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void named_upgradable_mutex::lock()
{  this->mutex()->lock();  }


inline void named_upgradable_mutex::unlock()
{  this->mutex()->unlock();  }


inline bool named_upgradable_mutex::try_lock()
{  return this->mutex()->try_lock();  }


inline void named_upgradable_mutex::lock_upgradable()
{  this->mutex()->lock_upgradable();  }


inline void named_upgradable_mutex::unlock_upgradable()
{  this->mutex()->unlock_upgradable();  }


inline bool named_upgradable_mutex::try_lock_upgradable()
{  return this->mutex()->try_lock_upgradable();  }


inline void named_upgradable_mutex::lock_sharable()
{  this->mutex()->lock_sharable();  }


inline void named_upgradable_mutex::unlock_sharable()
{  this->mutex()->unlock_sharable();  }


inline bool named_upgradable_mutex::try_lock_sharable()
{  return this->mutex()->try_lock_sharable();  }


inline void named_upgradable_mutex::unlock_and_lock_upgradable()
{  this->mutex()->unlock_and_lock_upgradable();  }


inline void named_upgradable_mutex::unlock_and_lock_sharable()
{  this->mutex()->unlock_and_lock_sharable();  }


inline void named_upgradable_mutex::unlock_upgradable_and_lock_sharable()
{  this->mutex()->unlock_upgradable_and_lock_sharable();  }


inline void named_upgradable_mutex::unlock_upgradable_and_lock()
{  this->mutex()->unlock_upgradable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_upgradable_and_lock()
{  return this->mutex()->try_unlock_upgradable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_sharable_and_lock()
{  return this->mutex()->try_unlock_sharable_and_lock();  }


inline bool named_upgradable_mutex::try_unlock_sharable_and_lock_upgradable()
{  return this->mutex()->try_unlock_sharable_and_lock_upgradable();  }


inline bool named_upgradable_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }


   interprocess_recursive_mutex *mutex() const
   {  return static_cast<interprocess_recursive_mutex*>(m_shmem.get_user_address()); }


inline shm_named_recursive_mutex::~shm_named_recursive_mutex()
{}


inline void shm_named_recursive_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void shm_named_recursive_mutex::lock()
{  this->mutex()->lock();  }


inline void shm_named_recursive_mutex::unlock()
{  this->mutex()->unlock();  }


inline bool shm_named_recursive_mutex::try_lock()
{  return this->mutex()->try_lock();  }


inline bool shm_named_recursive_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

   named_creation_functor(create_enum_t type, Arg arg = Arg())
      :  m_creation_type(type), m_arg(arg){}


   template<class ArgType>
   void construct(void *address, typename enable_if_c<is_same<ArgType, no_arg_t>::value>::type * = 0) const
   {  new(address)T; }


   bool operator()(void *address, std::size_t, bool created) const
   {
      switch(m_creation_type){
         case DoOpen:
            return true;
         break;
         case DoCreate:
         case DoOpenOrCreate:
            if(created){
               construct<Arg>(address);
            }
            return true;
         break;

         default:
            return false;
         break;
      }
   }


   std::size_t get_min_size() const
   {  return sizeof(T);  }

   interprocess_mutex &internal_mutex()
   {  return *static_cast<interprocess_mutex*>(m_shmem.get_user_address()); }


inline void shm_named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline shm_named_mutex::~shm_named_mutex()
{}


inline void shm_named_mutex::lock()
{  this->internal_mutex().lock();  }


inline void shm_named_mutex::unlock()
{  this->internal_mutex().unlock();  }


inline bool shm_named_mutex::try_lock()
{  return this->internal_mutex().try_lock();  }


inline bool shm_named_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

   ~shm_named_condition_any()
   {}

   void notify_one()
   {  m_cond.notify_one(); }

   void notify_all()
   {  m_cond.notify_all(); }

   template <typename L>
   void wait(L& lock)
   {  m_cond.wait(lock); }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_cond.wait(lock, pred); }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time); }

   static bool remove(const char *name)
   {  return shared_memory_object::remove(name); }

  
      condvar_type&  get_condvar() {  return m_cond;  }

      mutex_type&    get_mutex()   {  return m_mtx; }

   void dont_close_on_destruction()
   {  interprocess_tester::dont_close_on_destruction(m_shmem);  }


   interprocess_semaphore *semaphore() const
   {  return static_cast<interprocess_semaphore*>(m_shmem.get_user_address()); }


inline shm_named_semaphore::~shm_named_semaphore()
{}


inline void shm_named_semaphore::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }


inline void shm_named_semaphore::post()
{  semaphore()->post();   }


inline void shm_named_semaphore::wait()
{  semaphore()->wait();   }


inline bool shm_named_semaphore::try_wait()
{  return semaphore()->try_wait();   }


inline bool shm_named_semaphore::remove(const char *name)
{  return shared_memory_object::remove(name); }


      static type *get(void *p)
      {  return static_cast<type*>(p);  }

   private_node_allocator_base(segment_manager *segment_mngr)
      : m_node_pool(segment_mngr)
   {}

   private_node_allocator_base(const private_node_allocator_base &other)
      : m_node_pool(other.get_segment_manager())
   {}

   template<class T2>
   private_node_allocator_base
      (const private_node_allocator_base
         <Version, T2, SegmentManager, NodesPerBlock> &other)
      : m_node_pool(other.get_segment_manager())
   {}

   ~private_node_allocator_base()
   {}

   segment_manager* get_segment_manager()const
   {  return m_node_pool.get_segment_manager(); }

   node_pool_t* get_node_pool() const
   {  return const_cast<node_pool_t*>(&m_node_pool); }

template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator==(const private_node_allocator_base<V, T, S, NPC> &alloc1,
                const private_node_allocator_base<V, T, S, NPC> &alloc2)
{  return &alloc1 == &alloc2; }

template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator!=(const private_node_allocator_base<V, T, S, NPC> &alloc1,
                const private_node_allocator_base<V, T, S, NPC> &alloc2)
{  return &alloc1 != &alloc2; }


   private_node_allocator_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   private_node_allocator_v1
      (const private_node_allocator_v1<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}


   private_node_allocator(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   private_node_allocator
      (const private_node_allocator<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}


   cached_node_allocator_v1(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}


   template<class T2>
   cached_node_allocator_v1
      (const cached_node_allocator_v1
         <T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}


   cached_node_allocator(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}


   template<class T2>
   cached_node_allocator
      (const cached_node_allocator<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}


      static type *get(void *p)
      {  return static_cast<type*>(p);  }

   private_adaptive_pool_base(segment_manager *segment_mngr)
      : m_node_pool(segment_mngr)
   {}

   private_adaptive_pool_base(const private_adaptive_pool_base &other)
      : m_node_pool(other.get_segment_manager())
   {}

   template<class T2>
   private_adaptive_pool_base
      (const private_adaptive_pool_base
         <Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : m_node_pool(other.get_segment_manager())
   {}

   ~private_adaptive_pool_base()
   {}

   segment_manager* get_segment_manager()const
   {  return m_node_pool.get_segment_manager(); }

   node_pool_t* get_node_pool() const
   {  return const_cast<node_pool_t*>(&m_node_pool); }

template<unsigned int V, class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator==(const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc2)
{  return &alloc1 == &alloc2; }

template<unsigned int V, class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator!=(const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc2)
{  return &alloc1 != &alloc2; }


   private_adaptive_pool_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   private_adaptive_pool_v1
      (const private_adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


   private_adaptive_pool(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   private_adaptive_pool
      (const private_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


   cached_adaptive_pool_v1(SegmentManager *segment_mngr,
                           size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}


   template<class T2>
   cached_adaptive_pool_v1
      (const cached_adaptive_pool_v1
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


   cached_adaptive_pool(SegmentManager *segment_mngr,
                         std::size_t max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}


   template<class T2>
   cached_adaptive_pool
      (const cached_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


      static type *get(void *p)
      {  return static_cast<type*>(p);  }

   adaptive_pool_base(segment_manager *segment_mngr)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(segment_mngr)) { }

   adaptive_pool_base(const adaptive_pool_base &other)
      : mp_node_pool(other.get_node_pool())
   {
      node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->inc_ref_count();
   }

   adaptive_pool_base& operator=(const adaptive_pool_base &other)
   {
      adaptive_pool_base c(other);
      swap(*this, c);
      return *this;
   }

   template<class T2>
   adaptive_pool_base
      (const adaptive_pool_base<Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(other.get_segment_manager())) { }

   ~adaptive_pool_base()
   {  ipcdetail::destroy_node_pool_if_last_link(node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool)));   }

   void* get_node_pool() const
   {  return ipcdetail::to_raw_pointer(mp_node_pool);   }

   segment_manager* get_segment_manager()const
   {  return node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->get_segment_manager();  }

template<unsigned int V, class T, class S, std::size_t NPC, std::size_t F, unsigned char OP> inline
bool operator==(const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc1,
                const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

template<unsigned int V, class T, class S, std::size_t NPC, std::size_t F, unsigned char OP> inline
bool operator!=(const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc1,
                const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }


   adaptive_pool_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   adaptive_pool_v1
      (const adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


   adaptive_pool(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   adaptive_pool
      (const adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}


      static type *get(void *p)
      {  return static_cast<type*>(p);  }

   node_allocator_base(segment_manager *segment_mngr)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(segment_mngr)) { }

   node_allocator_base(const node_allocator_base &other)
      : mp_node_pool(other.get_node_pool())
   {
      node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->inc_ref_count();
   }

   template<class T2>
   node_allocator_base
      (const node_allocator_base<Version, T2, SegmentManager, NodesPerBlock> &other)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(other.get_segment_manager())) { }

   node_allocator_base& operator=(const node_allocator_base &other)
   {
      node_allocator_base c(other);
      swap(*this, c);
      return *this;
   }

   ~node_allocator_base()
   {  ipcdetail::destroy_node_pool_if_last_link(node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool)));   }

   void* get_node_pool() const
   {  return ipcdetail::to_raw_pointer(mp_node_pool);   }

   segment_manager* get_segment_manager()const
   {  return node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->get_segment_manager();  }

template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator==(const node_allocator_base<V, T, S, NPC> &alloc1,
                const node_allocator_base<V, T, S, NPC> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator!=(const node_allocator_base<V, T, S, NPC> &alloc1,
                const node_allocator_base<V, T, S, NPC> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }


   node_allocator_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   node_allocator_v1
      (const node_allocator_v1<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}


   node_allocator(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}


   template<class T2>
   node_allocator
      (const node_allocator<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}

   segment_manager* get_segment_manager()const
   {  return ipcdetail::to_raw_pointer(mp_mngr);   }

   allocator(segment_manager *segment_mngr)
      : mp_mngr(segment_mngr) { }

   allocator(const allocator &other)
      : mp_mngr(other.get_segment_manager()){ }

   template<class T2>
   allocator(const allocator<T2, SegmentManager> &other)
      : mp_mngr(other.get_segment_manager()){}

   pointer allocate(size_type count, cvoid_ptr hint = 0)
   {
      (void)hint;
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      return pointer(static_cast<value_type*>(mp_mngr->allocate(count*sizeof(T))));
   }

   void deallocate(const pointer &ptr, size_type)
   {  mp_mngr->deallocate((void*)ipcdetail::to_raw_pointer(ptr));  }

   size_type max_size() const
   {  return mp_mngr->get_size()/sizeof(T);   }

   size_type size(const pointer &p) const
   {
      return (size_type)mp_mngr->size(ipcdetail::to_raw_pointer(p))/sizeof(T);
   }

template<class T, class SegmentManager> inline
bool operator==(const allocator<T , SegmentManager>  &alloc1,
                const allocator<T, SegmentManager>  &alloc2)
   {  return alloc1.get_segment_manager() == alloc2.get_segment_manager(); }

template<class T, class SegmentManager> inline
bool operator!=(const allocator<T, SegmentManager>  &alloc1,
                const allocator<T, SegmentManager>  &alloc2)
   {  return alloc1.get_segment_manager() != alloc2.get_segment_manager(); }

   private_node_pool(segment_manager *segment_mngr)
      :  base_t(segment_mngr, NodeSize, NodesPerBlock)
   {}

   segment_manager* get_segment_manager() const
   {  return static_cast<segment_manager*>(base_t::get_segment_manager_base()); }

   shared_node_pool(SegmentManager *segment_mgnr)
      : base_t(segment_mgnr)
   {}

   void operator()()
   {
      //Find or create the node_pool_t
      mp_node_pool =    mp_segment_manager->template find_or_construct
                        <NodePool>(boost::interprocess::unique_instance)(mp_segment_manager);
      //If valid, increment link count
      if(mp_node_pool != 0)
         mp_node_pool->inc_ref_count();
   }

   get_or_create_node_pool_func(typename NodePool::segment_manager *mngr)
      : mp_segment_manager(mngr){}


template<class NodePool>
inline NodePool *get_or_create_node_pool(typename NodePool::segment_manager *mgnr)
{
   ipcdetail::get_or_create_node_pool_func<NodePool> func(mgnr);
   mgnr->atomic_func(func);
   return func.mp_node_pool;
}

   void operator()()
   {
      //If not the last link return
      if(mp_node_pool->dec_ref_count() != 0) return;

      //Last link, let's destroy the segment_manager
      mp_node_pool->get_segment_manager()->template destroy<NodePool>(boost::interprocess::unique_instance);
   }

   destroy_if_last_link_func(NodePool *pool)
      : mp_node_pool(pool)
   {}

template<class NodePool>
inline void destroy_node_pool_if_last_link(NodePool *pool)
{
   //Get segment manager
   typename NodePool::segment_manager *mngr = pool->get_segment_manager();
   //Execute destruction functor atomically
   destroy_if_last_link_func<NodePool>func(pool);
   mngr->atomic_func(func);
}


   cache_impl(segment_manager *segment_mngr, size_type max_cached_nodes)
      : mp_node_pool(get_or_create_node_pool<NodePool>(segment_mngr))
      , m_max_cached_nodes(max_cached_nodes)
   {}


   cache_impl(const cache_impl &other)
      : mp_node_pool(other.get_node_pool())
      , m_max_cached_nodes(other.get_max_cached_nodes())
   {
      mp_node_pool->inc_ref_count();
   }


   ~cache_impl()
   {
      this->deallocate_all_cached_nodes();
      ipcdetail::destroy_node_pool_if_last_link(ipcdetail::to_raw_pointer(mp_node_pool));
   }


   NodePool *get_node_pool() const
   {  return ipcdetail::to_raw_pointer(mp_node_pool); }


   segment_manager *get_segment_manager() const
   {  return mp_node_pool->get_segment_manager(); }


   size_type get_max_cached_nodes() const
   {  return m_max_cached_nodes; }


   void *cached_allocation()
   {
      //If don't have any cached node, we have to get a new list of free nodes from the pool
      if(m_cached_nodes.empty()){
         mp_node_pool->allocate_nodes(m_max_cached_nodes/2, m_cached_nodes);
      }
      void *ret = ipcdetail::to_raw_pointer(m_cached_nodes.pop_front());
      return ret;
   }


   void cached_allocation(size_type n, multiallocation_chain &chain)
   {
      size_type count = n, allocated(0);
      BOOST_TRY{
         //If don't have any cached node, we have to get a new list of free nodes from the pool
         while(!m_cached_nodes.empty() && count--){
            void *ret = ipcdetail::to_raw_pointer(m_cached_nodes.pop_front());
            chain.push_back(ret);
            ++allocated;
         }

         if(allocated != n){
            mp_node_pool->allocate_nodes(n - allocated, chain);
         }
      }
      BOOST_CATCH(...){
         this->cached_deallocation(chain);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }


   void cached_deallocation(void *ptr)
   {
      //Check if cache is full
      if(m_cached_nodes.size() >= m_max_cached_nodes){
         //This only occurs if this allocator deallocate memory allocated
         //with other equal allocator. Since the cache is full, and more
         //deallocations are probably coming, we'll make some room in cache
         //in a single, efficient multi node deallocation.
         this->priv_deallocate_n_nodes(m_cached_nodes.size() - m_max_cached_nodes/2);
      }
      m_cached_nodes.push_front(ptr);
   }


   void cached_deallocation(multiallocation_chain &chain)
   {
      m_cached_nodes.splice_after(m_cached_nodes.before_begin(), chain);

      //Check if cache is full
      if(m_cached_nodes.size() >= m_max_cached_nodes){
         //This only occurs if this allocator deallocate memory allocated
         //with other equal allocator. Since the cache is full, and more
         //deallocations are probably coming, we'll make some room in cache
         //in a single, efficient multi node deallocation.
         this->priv_deallocate_n_nodes(m_cached_nodes.size() - m_max_cached_nodes/2);
      }
   }

   void set_max_cached_nodes(size_type newmax)
   {
      m_max_cached_nodes = newmax;
      this->priv_deallocate_remaining_nodes();
   }

   void deallocate_all_cached_nodes()
   {
      if(m_cached_nodes.empty()) return;
      mp_node_pool->deallocate_nodes(m_cached_nodes);
   }

   void priv_deallocate_remaining_nodes()
   {
      if(m_cached_nodes.size() > m_max_cached_nodes){
         priv_deallocate_n_nodes(m_cached_nodes.size()-m_max_cached_nodes);
      }
   }

   void priv_deallocate_n_nodes(size_type n)
   {
      //This only occurs if this allocator deallocate memory allocated
      //with other equal allocator. Since the cache is full, and more
      //deallocations are probably coming, we'll make some room in cache
      //in a single, efficient multi node deallocation.
      size_type count(n);
      typename multiallocation_chain::iterator it(m_cached_nodes.before_begin());
      while(count--){
         ++it;
      }
      multiallocation_chain chain;
      chain.splice_after(chain.before_begin(), m_cached_nodes, m_cached_nodes.before_begin(), it, n);
      //Deallocate all new linked list at once
      mp_node_pool->deallocate_nodes(chain);
   }

   void swap(cache_impl &other)
   {
      ipcdetail::do_swap(mp_node_pool, other.mp_node_pool);
      m_cached_nodes.swap(other.m_cached_nodes);
      ipcdetail::do_swap(m_max_cached_nodes, other.m_max_cached_nodes);
   }

   const Derived *derived() const
   {  return static_cast<const Derived*>(this); }

   Derived *derived()
   {  return static_cast<Derived*>(this); }

   size_type size(const pointer &p) const
   {
      return (size_type)this->derived()->get_segment_manager()->size(ipcdetail::to_raw_pointer(p))/sizeof(T);
   }

   const Derived *derived() const
   {  return static_cast<const Derived*>(this); }

   Derived *derived()
   {  return static_cast<Derived*>(this); }

      static type *get(void *p)
      {  return static_cast<type*>(p); }

   pointer allocate(size_type count, cvoid_pointer hint = 0)
   {
      (void)hint;
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      else if(Version == 1 && count == 1){
         return pointer(static_cast<value_type*>
         (pool->allocate_node()));
      }
      else{
         return pointer(static_cast<value_type*>
            (pool->get_segment_manager()->allocate(count*sizeof(T))));
      }
   }

   void deallocate(const pointer &ptr, size_type count)
   {
      (void)count;
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      if(Version == 1 && count == 1)
         pool->deallocate_node(ipcdetail::to_raw_pointer(ptr));
      else
         pool->get_segment_manager()->deallocate((void*)ipcdetail::to_raw_pointer(ptr));
   }

   pointer allocate_one()
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      return pointer(static_cast<value_type*>(pool->allocate_node()));
   }

   void allocate_individual(size_type num_elements, multiallocation_chain &chain)
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      pool->allocate_nodes(num_elements, chain);
   }

   void deallocate_one(const pointer &p)
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      pool->deallocate_node(ipcdetail::to_raw_pointer(p));
   }

   void deallocate_individual(multiallocation_chain &chain)
   {
      node_pool<0>::get(this->derived()->get_node_pool())->deallocate_nodes
         (chain);
   }

   void deallocate_free_blocks()
   {  node_pool<0>::get(this->derived()->get_node_pool())->deallocate_free_blocks();  }

   void deallocate_free_chunks()
   {  node_pool<0>::get(this->derived()->get_node_pool())->deallocate_free_blocks();  }


   cached_allocator_impl(segment_manager *segment_mngr, size_type max_cached_nodes)
      : m_cache(segment_mngr, max_cached_nodes)
   {}


   cached_allocator_impl(const cached_allocator_impl &other)
      : m_cache(other.m_cache)
   {}

   template<class T2, class NodePool2>
   cached_allocator_impl
      (const cached_allocator_impl
         <T2, NodePool2, Version> &other)
      : m_cache(other.get_segment_manager(), other.get_max_cached_nodes())
   {}

   node_pool_t* get_node_pool() const
   {  return m_cache.get_node_pool();   }

   segment_manager* get_segment_manager()const
   {  return m_cache.get_segment_manager();   }

   void set_max_cached_nodes(size_type newmax)
   {  m_cache.set_max_cached_nodes(newmax);   }

   size_type get_max_cached_nodes() const
   {  return m_cache.get_max_cached_nodes();   }

   pointer allocate(size_type count, cvoid_pointer hint = 0)
   {
      (void)hint;
      void * ret;
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      else if(Version == 1 && count == 1){
         ret = m_cache.cached_allocation();
      }
      else{
         ret = this->get_segment_manager()->allocate(count*sizeof(T));
      }
      return pointer(static_cast<T*>(ret));
   }

   void deallocate(const pointer &ptr, size_type count)
   {
      (void)count;
      if(Version == 1 && count == 1){
         m_cache.cached_deallocation(ipcdetail::to_raw_pointer(ptr));
      }
      else{
         this->get_segment_manager()->deallocate((void*)ipcdetail::to_raw_pointer(ptr));
      }
   }

   pointer allocate_one()
   {  return pointer(static_cast<value_type*>(this->m_cache.cached_allocation()));   }

   void allocate_individual(size_type num_elements, multiallocation_chain &chain)
   {  this->m_cache.cached_allocation(num_elements, chain);   }

   void deallocate_one(const pointer &p)
   {  this->m_cache.cached_deallocation(ipcdetail::to_raw_pointer(p)); }

   void deallocate_individual(multiallocation_chain &chain)
   {  m_cache.cached_deallocation(chain);  }

   void deallocate_free_blocks()
   {  m_cache.get_node_pool()->deallocate_free_blocks();   }


   void deallocate_cache()
   {  m_cache.deallocate_all_cached_nodes(); }

   void deallocate_free_chunks()
   {  m_cache.get_node_pool()->deallocate_free_blocks();   }

template<class T, class N, unsigned int V> inline
bool operator==(const cached_allocator_impl<T, N, V> &alloc1,
                const cached_allocator_impl<T, N, V> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

template<class T, class N, unsigned int V> inline
bool operator!=(const cached_allocator_impl<T, N, V> &alloc1,
                const cached_allocator_impl<T, N, V> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }

   shared_pool_impl(segment_manager *segment_mngr)
      : private_node_allocator_t(segment_mngr)
   {}

   ~shared_pool_impl()
   {}

   void *allocate_node()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      return private_node_allocator_t::allocate_node();
   }

   void deallocate_node(void *ptr)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_node(ptr);
   }

   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::allocate_nodes(n, chain);
   }

   void deallocate_nodes(multiallocation_chain &nodes, size_type num)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_nodes(nodes, num);
   }

   void deallocate_nodes(multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_nodes(chain);
   }

   void deallocate_free_blocks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_free_blocks();
   }

   void purge_blocks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::purge_blocks();
   }

   size_type inc_ref_count()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      return ++m_header.m_usecount;
   }

   size_type dec_ref_count()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      BOOST_ASSERT(m_header.m_usecount > 0);
      return --m_header.m_usecount;
   }

   void deallocate_free_chunks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_free_blocks();
   }

   void purge_chunks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::purge_blocks();
   }


      header_t()
      :  m_usecount(0) {}


      header_t()
      :  m_usecount(0) {}

   private_adaptive_node_pool(segment_manager *segment_mngr)
      :  base_t(segment_mngr, NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent)
   {}

   segment_manager* get_segment_manager() const
   {  return static_cast<segment_manager*>(base_t::get_segment_manager_base()); }

   shared_adaptive_node_pool(SegmentManager *segment_mgnr)
      : base_t(segment_mgnr)
   {}
