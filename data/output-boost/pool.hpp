
    pool_allocator()
    { /*! Results in default construction of the underlying singleton_pool IFF an
       instance of this allocator is constructed during global initialization (
         required to ensure construction of singleton_pool IFF an
         instance of this allocator is constructed during global
         initialization. See ticket #2359 for a complete explanation at
         http://svn.boost.org/trac/boost/ticket/2359) .
       */
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
                     NextSize, MaxSize>::is_from(0);
    }

    template <typename U>
    pool_allocator(const pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> &)
    { /*! Results in the default construction of the underlying singleton_pool, this
         is required to ensure construction of singleton_pool IFF an
         instance of this allocator is constructed during global
         initialization. See ticket #2359 for a complete explanation
         at http://svn.boost.org/trac/boost/ticket/2359 .
       */
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
                     NextSize, MaxSize>::is_from(0);
    }


    static pointer address(reference r)
    { return &r; }

    static const_pointer address(const_reference s)
    { return &s; }

    static size_type max_size()
    { return (std::numeric_limits<size_type>::max)(); }

    static void construct(const pointer ptr, const value_type & t)
    { new (ptr) T(t); }

    static void destroy(const pointer ptr)
    {
      ptr->~T();
      (void) ptr; // avoid unused variable warning.
    }


    bool operator==(const pool_allocator &) const
    { return true; }

    bool operator!=(const pool_allocator &) const
    { return false; }


    static pointer allocate(const size_type n)
    {
#ifdef BOOST_POOL_INSTRUMENT
       debug_info<true>::allocated += n * sizeof(T);
       std::cout << "Allocating " << n << " * " << sizeof(T) << " bytes...\n"
          "Total allocated is now " << debug_info<true>::allocated << std::endl;
#endif
      const pointer ret = static_cast<pointer>(
          singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
              NextSize, MaxSize>::ordered_malloc(n) );
      if ((ret == 0) && n)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }

    static void deallocate(const pointer ptr, const size_type n)
    {  //! Deallocate n bytes from ptr
       //! \param ptr location to deallocate from.
       //! \param n number of bytes to deallocate.
#ifdef BOOST_POOL_INSTRUMENT
       debug_info<true>::allocated -= n * sizeof(T);
       std::cout << "Deallocating " << n << " * " << sizeof(T) << " bytes...\n"
          "Total allocated is now " << debug_info<true>::allocated << std::endl;
#endif
#ifdef BOOST_NO_PROPER_STL_DEALLOCATE
      if (ptr == 0 || n == 0)
        return;
#endif
      singleton_pool<pool_allocator_tag, sizeof(T), UserAllocator, Mutex,
          NextSize, MaxSize>::ordered_free(ptr, n);
    }

    fast_pool_allocator()
    {
      //! Ensures construction of the underlying singleton_pool IFF an
      //! instance of this allocator is constructed during global
      //! initialization. See ticket #2359 for a complete explanation
      //! at http://svn.boost.org/trac/boost/ticket/2359 .
      singleton_pool<fast_pool_allocator_tag, sizeof(T),
                     UserAllocator, Mutex, NextSize, MaxSize>::is_from(0);
    }

    template <typename U>
    fast_pool_allocator(
        const fast_pool_allocator<U, UserAllocator, Mutex, NextSize, MaxSize> &)
    {
      //! Ensures construction of the underlying singleton_pool IFF an
      //! instance of this allocator is constructed during global
      //! initialization. See ticket #2359 for a complete explanation
      //! at http://svn.boost.org/trac/boost/ticket/2359 .
      singleton_pool<fast_pool_allocator_tag, sizeof(T),
                     UserAllocator, Mutex, NextSize, MaxSize>::is_from(0);
    }


    static pointer address(reference r)
    {
      return &r;
    }

    static const_pointer address(const_reference s)
    { return &s; }

    static size_type max_size()
    { return (std::numeric_limits<size_type>::max)(); }

    void construct(const pointer ptr, const value_type & t)
    { new (ptr) T(t); }

    void destroy(const pointer ptr)
    { //! Destroy ptr using destructor.
      ptr->~T();
      (void) ptr; // Avoid unused variable warning.
    }


    bool operator==(const fast_pool_allocator &) const
    { return true; }

    bool operator!=(const fast_pool_allocator &) const
    { return false; }


    static pointer allocate(const size_type n)
    {
      const pointer ret = (n == 1) ?
          static_cast<pointer>(
              (singleton_pool<fast_pool_allocator_tag, sizeof(T),
                  UserAllocator, Mutex, NextSize, MaxSize>::malloc)() ) :
          static_cast<pointer>(
              singleton_pool<fast_pool_allocator_tag, sizeof(T),
                  UserAllocator, Mutex, NextSize, MaxSize>::ordered_malloc(n) );
      if (ret == 0)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }

    static pointer allocate()
    { //! Allocate memory.
      const pointer ret = static_cast<pointer>(
          (singleton_pool<fast_pool_allocator_tag, sizeof(T),
              UserAllocator, Mutex, NextSize, MaxSize>::malloc)() );
      if (ret == 0)
        boost::throw_exception(std::bad_alloc());
      return ret;
    }

    static void deallocate(const pointer ptr, const size_type n)
    { //! Deallocate memory.

#ifdef BOOST_NO_PROPER_STL_DEALLOCATE
      if (ptr == 0 || n == 0)
        return;
#endif
      if (n == 1)
        (singleton_pool<fast_pool_allocator_tag, sizeof(T),
            UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr);
      else
        (singleton_pool<fast_pool_allocator_tag, sizeof(T),
            UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr, n);
    }

    static void deallocate(const pointer ptr)
    { //! deallocate/free
      (singleton_pool<fast_pool_allocator_tag, sizeof(T),
          UserAllocator, Mutex, NextSize, MaxSize>::free)(ptr);
    }


    char * ptr_next_size() const
    {
      return (ptr + sz - sizeof(size_type));
    }

    char * ptr_next_ptr() const
    {
      return (ptr_next_size() -
          math::static_lcm<sizeof(size_type), sizeof(void *)>::value);
    }

    PODptr(char * const nptr, const size_type nsize)
    :ptr(nptr), sz(nsize)
    {
      //! A PODptr may be created to point to a memory block by passing
      //! the address and size of that memory block into the constructor.
      //! A PODptr constructed in this way is valid.
    }

    PODptr()
    :  ptr(0), sz(0)
    { //! default constructor for PODptr will result in an invalid object.
    }


    bool valid() const
    { //! A PODptr object is either valid or invalid.
      //! An invalid PODptr is analogous to a null pointer.
      //! \returns true if PODptr is valid, false if invalid.
      return (begin() != 0);
    }

    void invalidate()
    { //! Make object invalid.
      begin() = 0;
    }

    char * & begin()
    { //! Each PODptr keeps the address and size of its memory block.
      //! \returns The address of its memory block.
      return ptr;
  }

    char * begin() const
    { //! Each PODptr keeps the address and size of its memory block.
      //! \return The address of its memory block.
      return ptr;
    }

    char * end() const
    { //! \returns begin() plus element_size (a 'past the end' value).
      return ptr_next_ptr();
    }

    size_type total_size() const
    { //! Each PODptr keeps the address and size of its memory block.
      //! The address may be read or written by the member functions begin.
      //! The size of the memory block may only be read,
      //! \returns size of the memory block.
      return sz;
    }

    size_type element_size() const
    { //! \returns size of element pointer area.
      return static_cast<size_type>(sz - sizeof(size_type) -
          math::static_lcm<sizeof(size_type), sizeof(void *)>::value);
    }


    size_type & next_size() const
    { //!
      //! \returns next_size.
      return *(static_cast<size_type *>(static_cast<void*>((ptr_next_size()))));
    }

    char * & next_ptr() const
    {  //! \returns pointer to next pointer area.
      return *(static_cast<char **>(static_cast<void*>(ptr_next_ptr())));
    }


    PODptr next() const
    { //! \returns next PODptr.
      return PODptr<size_type>(next_ptr(), next_size());
    }

    void next(const PODptr & arg) const
    { //! Sets next PODptr.
      next_ptr() = arg.begin();
      next_size() = arg.total_size();
    }

    static bool is_from(void * const chunk, char * const i,
        const size_type sizeof_i)
    { //! \param chunk chunk to check if is from this pool.
      //! \param i memory chunk at i with element sizeof_i.
      //! \param sizeof_i element size (size of the chunk area of that block, not the total size of that block).
      //! \returns true if chunk was allocated or may be returned.
      //! as the result of a future allocation.
      //!
      //! Returns false if chunk was allocated from some other pool,
      //! or may be returned as the result of a future allocation from some other pool.
      //! Otherwise, the return value is meaningless.
      //!
      //! Note that this function may not be used to reliably test random pointer values.

      // We use std::less_equal and std::less to test 'chunk'
      //  against the array bounds because standard operators
      //  may return unspecified results.
      // This is to ensure portability.  The operators < <= > >= are only
      //  defined for pointers to objects that are 1) in the same array, or
      //  2) subobjects of the same object [5.9/2].
      // The functor objects guarantee a total order for any pointer [20.3.3/8]
      std::less_equal<void *> lt_eq;
      std::less<void *> lt;
      return (lt_eq(i, chunk) && lt(chunk, i + sizeof_i));
    }


    size_type alloc_size() const
    { //!  Calculated size of the memory chunks that will be allocated by this Pool.
      //! \returns allocated size.
      // For alignment reasons, this used to be defined to be lcm(requested_size, sizeof(void *), sizeof(size_type)),
      // but is now more parsimonious: just rounding up to the minimum required alignment of our housekeeping data
      // when required.  This works provided all alignments are powers of two.
      size_type s = (std::max)(requested_size, min_alloc_size);
      size_type rem = s % min_align;
      if(rem)
         s += min_align - rem;
      BOOST_ASSERT(s >= min_alloc_size);
      BOOST_ASSERT(s % min_align == 0);
      return s;
    }


    static void * & nextof(void * const ptr)
    { //! \returns Pointer dereferenced.
      //! (Provided and used for the sake of code readability :)
      return *(static_cast<void **>(ptr));
    }

    explicit pool(const size_type nrequested_size,
        const size_type nnext_size = 32,
        const size_type nmax_size = 0)
    :
        list(0, 0), requested_size(nrequested_size), next_size(nnext_size), start_size(nnext_size),max_size(nmax_size)
    { //!   Constructs a new empty Pool that can be used to allocate chunks of size RequestedSize.
      //! \param nrequested_size  Requested chunk size
      //! \param  nnext_size parameter is of type size_type,
      //!   is the number of chunks to request from the system
      //!   the first time that object needs to allocate system memory.
      //!   The default is 32. This parameter may not be 0.
      //! \param nmax_size is the maximum number of chunks to allocate in one block.
    }


    ~pool()
    { //!   Destructs the Pool, freeing its list of memory blocks.
      purge_memory();
    }


    size_type get_next_size() const
    { //! Number of chunks to request from the system the next time that object needs to allocate system memory. This value should never be 0.
      //! \returns next_size;
      return next_size;
    }

    void set_next_size(const size_type nnext_size)
    { //! Set number of chunks to request from the system the next time that object needs to allocate system memory. This value should never be set to 0.
      //! \returns nnext_size.
      next_size = start_size = nnext_size;
    }

    size_type get_max_size() const
    { //! \returns max_size.
      return max_size;
    }

    void set_max_size(const size_type nmax_size)
    { //! Set max_size.
      max_size = nmax_size;
    }

    size_type get_requested_size() const
    { //!   \returns the requested size passed into the constructor.
      //! (This value will not change during the lifetime of a Pool object).
      return requested_size;
    }


template <typename UserAllocator>
bool pool<UserAllocator>::release_memory()
{ //! pool must be ordered. Frees every memory block that doesn't have any allocated chunks.
  //! \returns true if at least one memory block was freed.

  // ret is the return value: it will be set to true when we actually call
  //  UserAllocator::free(..)
  bool ret = false;

  // This is a current & previous iterator pair over the memory block list
  details::PODptr<size_type> ptr = list;
  details::PODptr<size_type> prev;

  // This is a current & previous iterator pair over the free memory chunk list
  //  Note that "prev_free" in this case does NOT point to the previous memory
  //  chunk in the free list, but rather the last free memory chunk before the
  //  current block.
  void * free_p = this->first;
  void * prev_free_p = 0;

  const size_type partition_size = alloc_size();

  // Search through all the all the allocated memory blocks
  while (ptr.valid())
  {
    // At this point:
    //  ptr points to a valid memory block
    //  free_p points to either:
    //    0 if there are no more free chunks
    //    the first free chunk in this or some next memory block
    //  prev_free_p points to either:
    //    the last free chunk in some previous memory block
    //    0 if there is no such free chunk
    //  prev is either:
    //    the PODptr whose next() is ptr
    //    !valid() if there is no such PODptr

    // If there are no more free memory chunks, then every remaining
    //  block is allocated out to its fullest capacity, and we can't
    //  release any more memory
    if (free_p == 0)
      break;

    // We have to check all the chunks.  If they are *all* free (i.e., present
    //  in the free list), then we can free the block.
    bool all_chunks_free = true;

    // Iterate 'i' through all chunks in the memory block
    // if free starts in the memory block, be careful to keep it there
    void * saved_free = free_p;
    for (char * i = ptr.begin(); i != ptr.end(); i += partition_size)
    {
      // If this chunk is not free
      if (i != free_p)
      {
        // We won't be able to free this block
        all_chunks_free = false;

        // free_p might have travelled outside ptr
        free_p = saved_free;
        // Abort searching the chunks; we won't be able to free this
        //  block because a chunk is not free.
        break;
      }

      // We do not increment prev_free_p because we are in the same block
      free_p = nextof(free_p);
    }

    // post: if the memory block has any chunks, free_p points to one of them
    // otherwise, our assertions above are still valid

    const details::PODptr<size_type> next = ptr.next();

    if (!all_chunks_free)
    {
      if (is_from(free_p, ptr.begin(), ptr.element_size()))
      {
        std::less<void *> lt;
        void * const end = ptr.end();
        do
        {
          prev_free_p = free_p;
          free_p = nextof(free_p);
        } while (free_p && lt(free_p, end));
      }
      // This invariant is now restored:
      //     free_p points to the first free chunk in some next memory block, or
      //       0 if there is no such chunk.
      //     prev_free_p points to the last free chunk in this memory block.

      // We are just about to advance ptr.  Maintain the invariant:
      // prev is the PODptr whose next() is ptr, or !valid()
      // if there is no such PODptr
      prev = ptr;
    }
    else
    {
      // All chunks from this block are free

      // Remove block from list
      if (prev.valid())
        prev.next(next);
      else
        list = next;

      // Remove all entries in the free list from this block
      if (prev_free_p != 0)
        nextof(prev_free_p) = free_p;
      else
        this->first = free_p;

      // And release memory
      (UserAllocator::free)(ptr.begin());
      ret = true;
    }

    // Increment ptr
    ptr = next;
  }

  next_size = start_size;
  return ret;
}


template <typename UserAllocator>
bool pool<UserAllocator>::purge_memory()
{ //! pool must be ordered.
  //! Frees every memory block.
  //!
  //! This function invalidates any pointers previously returned
  //! by allocation functions of t.
  //! \returns true if at least one memory block was freed.

  details::PODptr<size_type> iter = list;

  if (!iter.valid())
    return false;

  do
  {
    // hold "next" pointer
    const details::PODptr<size_type> next = iter.next();

    // delete the storage
    (UserAllocator::free)(iter.begin());

    // increment iter
    iter = next;
  } while (iter.valid());

  list.invalidate();
  this->first = 0;
  next_size = start_size;

  return true;
}


template <typename UserAllocator>
void * pool<UserAllocator>::malloc_need_resize()
{ //! No memory in any of our storages; make a new storage,
  //!  Allocates chunk in newly malloc aftert resize.
  //! \returns pointer to chunk.
  size_type partition_size = alloc_size();
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(next_size > 4)
     {
        next_size >>= 1;
        partition_size = alloc_size();
        POD_size = static_cast<size_type>(next_size * partition_size +
            math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
        ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
        return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  initialize it,
  store().add_block(node.begin(), node.element_size(), partition_size);

  //  insert it into the list,
  node.next(list);
  list = node;

  //  and return a chunk from it.
  return (store().malloc)();
}


template <typename UserAllocator>
void * pool<UserAllocator>::ordered_malloc_need_resize()
{ //! No memory in any of our storages; make a new storage,
  //! \returns pointer to new chunk.
  size_type partition_size = alloc_size();
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(next_size > 4)
     {
       next_size >>= 1;
       partition_size = alloc_size();
       POD_size = static_cast<size_type>(next_size * partition_size +
                    math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
       ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
       return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  initialize it,
  //  (we can use "add_block" here because we know that
  //  the free list is empty, so we don't have to use
  //  the slower ordered version)
  store().add_ordered_block(node.begin(), node.element_size(), partition_size);

  //  insert it into the list,
  //   handle border case
  if (!list.valid() || std::greater<void *>()(list.begin(), node.begin()))
  {
    node.next(list);
    list = node;
  }
  else
  {
    details::PODptr<size_type> prev = list;

    while (true)
    {
      // if we're about to hit the end or
      //  if we've found where "node" goes
      if (prev.next_ptr() == 0
          || std::greater<void *>()(prev.next_ptr(), node.begin()))
        break;

      prev = prev.next();
    }

    node.next(prev.next());
    prev.next(node);
  }
  //  and return a chunk from it.
  return (store().malloc)();
}


template <typename UserAllocator>
void * pool<UserAllocator>::ordered_malloc(const size_type n)
{ //! Gets address of a chunk n, allocating new memory if not already available.
  //! \returns Address of chunk n if allocated ok.
  //! \returns 0 if not enough memory for n chunks.

  const size_type partition_size = alloc_size();
  const size_type total_req_size = n * requested_size;
  const size_type num_chunks = total_req_size / partition_size +
      ((total_req_size % partition_size) ? true : false);

  void * ret = store().malloc_n(num_chunks, partition_size);

#ifdef BOOST_POOL_INSTRUMENT
  std::cout << "Allocating " << n << " chunks from pool of size " << partition_size << std::endl;
#endif
  if ((ret != 0) || (n == 0))
    return ret;

#ifdef BOOST_POOL_INSTRUMENT
  std::cout << "Cache miss, allocating another chunk...\n";
#endif

  // Not enough memory in our storages; make a new storage,
  BOOST_USING_STD_MAX();
  next_size = max BOOST_PREVENT_MACRO_SUBSTITUTION(next_size, num_chunks);
  size_type POD_size = static_cast<size_type>(next_size * partition_size +
      math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
  char * ptr = (UserAllocator::malloc)(POD_size);
  if (ptr == 0)
  {
     if(num_chunks < next_size)
     {
        // Try again with just enough memory to do the job, or at least whatever we
        // allocated last time:
        next_size >>= 1;
        next_size = max BOOST_PREVENT_MACRO_SUBSTITUTION(next_size, num_chunks);
        POD_size = static_cast<size_type>(next_size * partition_size +
            math::static_lcm<sizeof(size_type), sizeof(void *)>::value + sizeof(size_type));
        ptr = (UserAllocator::malloc)(POD_size);
     }
     if(ptr == 0)
       return 0;
  }
  const details::PODptr<size_type> node(ptr, POD_size);

  // Split up block so we can use what wasn't requested.
  if (next_size > num_chunks)
    store().add_ordered_block(node.begin() + num_chunks * partition_size,
        node.element_size() - num_chunks * partition_size, partition_size);

  BOOST_USING_STD_MIN();
  if(!max_size)
    next_size <<= 1;
  else if( next_size*partition_size/requested_size < max_size)
    next_size = min BOOST_PREVENT_MACRO_SUBSTITUTION(next_size << 1, max_size*requested_size/ partition_size);

  //  insert it into the list,
  //   handle border case.
  if (!list.valid() || std::greater<void *>()(list.begin(), node.begin()))
  {
    node.next(list);
    list = node;
  }
  else
  {
    details::PODptr<size_type> prev = list;

    while (true)
    {
      // if we're about to hit the end, or if we've found where "node" goes.
      if (prev.next_ptr() == 0
          || std::greater<void *>()(prev.next_ptr(), node.begin()))
        break;

      prev = prev.next();
    }

    node.next(prev.next());
    prev.next(node);
  }

  //  and return it.
  return node.begin();
}


template <typename UserAllocator>
details::PODptr<typename pool<UserAllocator>::size_type>
pool<UserAllocator>::find_POD(void * const chunk) const
{ //! find which PODptr storage memory that this chunk is from.
  //! \returns the PODptr that holds this chunk.
  // Iterate down list to find which storage this chunk is from.
  details::PODptr<size_type> iter = list;
  while (iter.valid())
  {
    if (is_from(chunk, iter.begin(), iter.element_size()))
      return iter;
    iter = iter.next();
  }

  return iter;
}

      pool_type() : pool<UserAllocator>(RequestedSize, NextSize, MaxSize) {}


   static pool_type& get_pool()
   {
      static bool f = false;
      if(!f)
      {
         // This code *must* be called before main() starts, 
         // and when only one thread is executing.
         f = true;
         new (&storage) pool_type;
      }

      // The following line does nothing else than force the instantiation
      //  of singleton<T>::create_object, whose constructor is
      //  called before main() begins.
      create_object.do_nothing();

      return *static_cast<pool_type*>(static_cast<void*>(&storage));
   }

      object_creator()
      {  // This constructor does nothing more than ensure that instance()
         //  is called before main() begins, thus creating the static
         //  T object before multithreading race issues can come up.
         singleton_pool<Tag, RequestedSize, UserAllocator, Mutex, NextSize, MaxSize>::get_pool();
      }

      inline void do_nothing() const
      {
      }


template <typename T, typename UserAllocator>
object_pool<T, UserAllocator>::~object_pool()
{
#ifndef BOOST_POOL_VALGRIND
  // handle trivial case of invalid list.
  if (!this->list.valid())
    return;

  details::PODptr<size_type> iter = this->list;
  details::PODptr<size_type> next = iter;

  // Start 'freed_iter' at beginning of free list
  void * freed_iter = this->first;

  const size_type partition_size = this->alloc_size();

  do
  {
    // increment next
    next = next.next();

    // delete all contained objects that aren't freed.

    // Iterate 'i' through all chunks in the memory block.
    for (char * i = iter.begin(); i != iter.end(); i += partition_size)
    {
      // If this chunk is free,
      if (i == freed_iter)
      {
        // Increment freed_iter to point to next in free list.
        freed_iter = nextof(freed_iter);

        // Continue searching chunks in the memory block.
        continue;
      }

      // This chunk is not free (allocated), so call its destructor,
      static_cast<T *>(static_cast<void *>(i))->~T();
      // and continue searching chunks in the memory block.
    }

    // free storage.
    (UserAllocator::free)(iter.begin());

    // increment iter.
    iter = next;
  } while (iter.valid());

  // Make the block list empty so that the inherited destructor doesn't try to
  // free it again.
  this->list.invalidate();
#else
   // destruct all used elements:
   for(std::set<void*>::iterator pos = this->used_list.begin(); pos != this->used_list.end(); ++pos)
   {
      static_cast<T*>(*pos)->~T();
   }
   // base class will actually free the memory...
#endif
}

    static void * & nextof(void * const ptr)
    { //! The return value is just *ptr cast to the appropriate type. ptr must not be 0. (For the sake of code readability :)
    //! As an example, let us assume that we want to truncate the free list after the first chunk.
    //! That is, we want to set *first to 0; this will result in a free list with only one entry.
    //! The normal way to do this is to first cast first to a pointer to a pointer to void,
    //! and then dereference and assign (*static_cast<void **>(first) = 0;).
    //! This can be done more easily through the use of this convenience function (nextof(first) = 0;).
    //! \returns dereferenced pointer.
      return *(static_cast<void **>(ptr));
    }

    simple_segregated_storage()
    :first(0)
    { //! Construct empty storage area.
      //! \post empty()
    }

    void add_block(void * const block,
        const size_type nsz, const size_type npartition_sz)
    { //! Add block
      //! Segregate this block and merge its free list into the
      //!  free list referred to by "first".
      //! \pre Same as segregate.
      //!  \post !empty()
      BOOST_POOL_VALIDATE_INTERNALS
      first = segregate(block, nsz, npartition_sz, first);
      BOOST_POOL_VALIDATE_INTERNALS
    }

    void add_ordered_block(void * const block,
        const size_type nsz, const size_type npartition_sz)
    { //! add block (ordered into list)
      //! This (slower) version of add_block segregates the
      //!  block and merges its free list into our free list
      //!  in the proper order.
       BOOST_POOL_VALIDATE_INTERNALS
      // Find where "block" would go in the free list
      void * const loc = find_prev(block);

      // Place either at beginning or in middle/end
      if (loc == 0)
        add_block(block, nsz, npartition_sz);
      else
        nextof(loc) = segregate(block, nsz, npartition_sz, nextof(loc));
      BOOST_POOL_VALIDATE_INTERNALS
    }


    bool empty() const
    { //! \returns true only if simple_segregated_storage is empty.
      return (first == 0);
    }

    void free_n(void * const chunks, const size_type n,
        const size_type partition_size)
    { 
       BOOST_POOL_VALIDATE_INTERNALS
      if(n != 0)
        add_block(chunks, n * partition_size, partition_size);
       BOOST_POOL_VALIDATE_INTERNALS
    }

    void ordered_free_n(void * const chunks, const size_type n,
        const size_type partition_size)
    { //! Free n chunks from order list.
      //! \pre chunks was previously allocated from *this with the same
      //!   values for n and partition_size.

      //! \pre n should not be zero (n == 0 has no effect).
       BOOST_POOL_VALIDATE_INTERNALS
      if(n != 0)
        add_ordered_block(chunks, n * partition_size, partition_size);
       BOOST_POOL_VALIDATE_INTERNALS
    }

template <typename SizeType>
void * simple_segregated_storage<SizeType>::find_prev(void * const ptr)
{ 
  // Handle border case.
  if (first == 0 || std::greater<void *>()(first, ptr))
    return 0;

  void * iter = first;
  while (true)
  {
    // if we're about to hit the end, or if we've found where "ptr" goes.
    if (nextof(iter) == 0 || std::greater<void *>()(nextof(iter), ptr))
      return iter;

    iter = nextof(iter);
  }
}

template <typename SizeType>
void * simple_segregated_storage<SizeType>::segregate(
    void * const block,
    const size_type sz,
    const size_type partition_sz,
    void * const end)
{
  // Get pointer to last valid chunk, preventing overflow on size calculations
  //  The division followed by the multiplication just makes sure that
  //    old == block + partition_sz * i, for some integer i, even if the
  //    block size (sz) is not a multiple of the partition size.
  char * old = static_cast<char *>(block)
      + ((sz - partition_sz) / partition_sz) * partition_sz;

  // Set it to point to the end
  nextof(old) = end;

  // Handle border case where sz == partition_sz (i.e., we're handling an array
  //  of 1 element)
  if (old == block)
    return block;

  // Iterate backwards, building a singly-linked list of pointers
  for (char * iter = old - partition_sz; iter != block;
      old = iter, iter -= partition_sz)
    nextof(iter) = old;

  // Point the first pointer, too
  nextof(block) = old;

  return block;
}

template <typename SizeType>
void * simple_segregated_storage<SizeType>::try_malloc_n(
    void * & start, size_type n, const size_type partition_size)
{
  void * iter = nextof(start);
  while (--n != 0)
  {
    void * next = nextof(iter);
    if (next != static_cast<char *>(iter) + partition_size)
    {
      // next == 0 (end-of-list) or non-contiguous chunk found
      start = iter;
      return 0;
    }
    iter = next;
  }
  return iter;
}

template <typename SizeType>
void * simple_segregated_storage<SizeType>::malloc_n(const size_type n,
    const size_type partition_size)
{
   BOOST_POOL_VALIDATE_INTERNALS
  if(n == 0)
    return 0;
  void * start = &first;
  void * iter;
  do
  {
    if (nextof(start) == 0)
      return 0;
    iter = try_malloc_n(start, n, partition_size);
  } while (iter == 0);
  void * const ret = nextof(start);
  nextof(start) = nextof(iter);
  BOOST_POOL_VALIDATE_INTERNALS
  return ret;
}

    explicit guard(Mutex & nmtx)
    :mtx(nmtx)
    { //! Locks the mutex of the guard class.
			mtx.lock();
		}


    ~guard()
    { //! destructor unlocks the mutex of the guard class.
			mtx.unlock();
		}

    null_mutex() { }


    static void lock() { }

    static void unlock() { }
