
    template <typename MutexType1, typename MutexType2>
    unsigned try_lock_internal(MutexType1& m1, MutexType2& m2)
    {
      boost::unique_lock<MutexType1> l1(m1, boost::try_to_lock);
      if (!l1)
      {
        return 1;
      }
      if (!m2.try_lock())
      {
        return 2;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3>
    unsigned try_lock_internal(MutexType1& m1, MutexType2& m2, MutexType3& m3)
    {
      boost::unique_lock<MutexType1> l1(m1, boost::try_to_lock);
      if (!l1)
      {
        return 1;
      }
      if (unsigned const failed_lock=try_lock_internal(m2,m3))
      {
        return failed_lock + 1;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4>
    unsigned try_lock_internal(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4)
    {
      boost::unique_lock<MutexType1> l1(m1, boost::try_to_lock);
      if (!l1)
      {
        return 1;
      }
      if (unsigned const failed_lock=try_lock_internal(m2,m3,m4))
      {
        return failed_lock + 1;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4, typename MutexType5>
    unsigned try_lock_internal(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4, MutexType5& m5)
    {
      boost::unique_lock<MutexType1> l1(m1, boost::try_to_lock);
      if (!l1)
      {
        return 1;
      }
      if (unsigned const failed_lock=try_lock_internal(m2,m3,m4,m5))
      {
        return failed_lock + 1;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2>
    unsigned lock_helper(MutexType1& m1, MutexType2& m2)
    {
      boost::unique_lock<MutexType1> l1(m1);
      if (!m2.try_lock())
      {
        return 1;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3>
    unsigned lock_helper(MutexType1& m1, MutexType2& m2, MutexType3& m3)
    {
      boost::unique_lock<MutexType1> l1(m1);
      if (unsigned const failed_lock=try_lock_internal(m2,m3))
      {
        return failed_lock;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4>
    unsigned lock_helper(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4)
    {
      boost::unique_lock<MutexType1> l1(m1);
      if (unsigned const failed_lock=try_lock_internal(m2,m3,m4))
      {
        return failed_lock;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4, typename MutexType5>
    unsigned lock_helper(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4, MutexType5& m5)
    {
      boost::unique_lock<MutexType1> l1(m1);
      if (unsigned const failed_lock=try_lock_internal(m2,m3,m4,m5))
      {
        return failed_lock;
      }
      l1.release();
      return 0;
    }


    template <typename MutexType1, typename MutexType2>
    void lock_impl(MutexType1& m1, MutexType2& m2, is_mutex_type_wrapper<true> )
    {
      unsigned const lock_count = 2;
      unsigned lock_first = 0;
      for (;;)
      {
        switch (lock_first)
        {
        case 0:
          lock_first = detail::lock_helper(m1, m2);
          if (!lock_first) return;
          break;
        case 1:
          lock_first = detail::lock_helper(m2, m1);
          if (!lock_first) return;
          lock_first = (lock_first + 1) % lock_count;
          break;
        }
      }
    }


  template <typename MutexType1, typename MutexType2>
  void lock(MutexType1& m1, MutexType2& m2)
  {
    detail::lock_impl(m1, m2, detail::is_mutex_type_wrapper<is_mutex_type<MutexType1>::value>());
  }


  template <typename MutexType1, typename MutexType2>
  void lock(const MutexType1& m1, MutexType2& m2)
  {
    detail::lock_impl(m1, m2, detail::is_mutex_type_wrapper<is_mutex_type<MutexType1>::value>());
  }


  template <typename MutexType1, typename MutexType2>
  void lock(MutexType1& m1, const MutexType2& m2)
  {
    detail::lock_impl(m1, m2, detail::is_mutex_type_wrapper<is_mutex_type<MutexType1>::value>());
  }


  template <typename MutexType1, typename MutexType2>
  void lock(const MutexType1& m1, const MutexType2& m2)
  {
    detail::lock_impl(m1, m2, detail::is_mutex_type_wrapper<is_mutex_type<MutexType1>::value>());
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3>
  void lock(MutexType1& m1, MutexType2& m2, MutexType3& m3)
  {
    unsigned const lock_count = 3;
    unsigned lock_first = 0;
    for (;;)
    {
      switch (lock_first)
      {
      case 0:
        lock_first = detail::lock_helper(m1, m2, m3);
        if (!lock_first) return;
        break;
      case 1:
        lock_first = detail::lock_helper(m2, m3, m1);
        if (!lock_first) return;
        lock_first = (lock_first + 1) % lock_count;
        break;
      case 2:
        lock_first = detail::lock_helper(m3, m1, m2);
        if (!lock_first) return;
        lock_first = (lock_first + 2) % lock_count;
        break;
      }
    }
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4>
  void lock(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4)
  {
    unsigned const lock_count = 4;
    unsigned lock_first = 0;
    for (;;)
    {
      switch (lock_first)
      {
      case 0:
        lock_first = detail::lock_helper(m1, m2, m3, m4);
        if (!lock_first) return;
        break;
      case 1:
        lock_first = detail::lock_helper(m2, m3, m4, m1);
        if (!lock_first) return;
        lock_first = (lock_first + 1) % lock_count;
        break;
      case 2:
        lock_first = detail::lock_helper(m3, m4, m1, m2);
        if (!lock_first) return;
        lock_first = (lock_first + 2) % lock_count;
        break;
      case 3:
        lock_first = detail::lock_helper(m4, m1, m2, m3);
        if (!lock_first) return;
        lock_first = (lock_first + 3) % lock_count;
        break;
      }
    }
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4, typename MutexType5>
  void lock(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4, MutexType5& m5)
  {
    unsigned const lock_count = 5;
    unsigned lock_first = 0;
    for (;;)
    {
      switch (lock_first)
      {
      case 0:
        lock_first = detail::lock_helper(m1, m2, m3, m4, m5);
        if (!lock_first) return;
        break;
      case 1:
        lock_first = detail::lock_helper(m2, m3, m4, m5, m1);
        if (!lock_first) return;
        lock_first = (lock_first + 1) % lock_count;
        break;
      case 2:
        lock_first = detail::lock_helper(m3, m4, m5, m1, m2);
        if (!lock_first) return;
        lock_first = (lock_first + 2) % lock_count;
        break;
      case 3:
        lock_first = detail::lock_helper(m4, m5, m1, m2, m3);
        if (!lock_first) return;
        lock_first = (lock_first + 3) % lock_count;
        break;
      case 4:
        lock_first = detail::lock_helper(m5, m1, m2, m3, m4);
        if (!lock_first) return;
        lock_first = (lock_first + 4) % lock_count;
        break;
      }
    }
  }


    template <typename MutexType1, typename MutexType2>
    int try_lock_impl(MutexType1& m1, MutexType2& m2, is_mutex_type_wrapper<true> )
    {
      return ((int) detail::try_lock_internal(m1, m2)) - 1;
    }
 try_lock(MutexType1& m1, MutexType2& m2)
  {
    return detail::try_lock_impl(m1, m2, detail::is_mutex_type_wrapper<is_mutex_type<MutexType1>::value>());
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3>
  int try_lock(MutexType1& m1, MutexType2& m2, MutexType3& m3)
  {
    return ((int) detail::try_lock_internal(m1, m2, m3)) - 1;
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4>
  int try_lock(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4)
  {
    return ((int) detail::try_lock_internal(m1, m2, m3, m4)) - 1;
  }


  template <typename MutexType1, typename MutexType2, typename MutexType3, typename MutexType4, typename MutexType5>
  int try_lock(MutexType1& m1, MutexType2& m2, MutexType3& m3, MutexType4& m4, MutexType5& m5)
  {
    return ((int) detail::try_lock_internal(m1, m2, m3, m4, m5)) - 1;
  }


      range_lock_guard(Iterator begin_, Iterator end_) :
        begin(begin_), end(end_)
      {
        boost::lock(begin, end);
      }


      void release()
      {
        begin = end;
      }


      ~range_lock_guard()
      {
        for (; begin != end; ++begin)
        {
          begin->unlock();
        }
      }


    template <typename Iterator>
    Iterator try_lock_impl(Iterator begin, Iterator end, is_mutex_type_wrapper<false> )

    {
      if (begin == end)
      {
        return end;
      }
      typedef typename std::iterator_traits<Iterator>::value_type lock_type;
      unique_lock<lock_type> guard(*begin, try_to_lock);

      if (!guard.owns_lock())
      {
        return begin;
      }
      Iterator const failed = boost::try_lock(++begin, end);
      if (failed == end)
      {
        guard.release();
      }

      return failed;
    }

    template <typename Iterator>
    void lock_impl(Iterator begin, Iterator end, is_mutex_type_wrapper<false> )
    {
      typedef typename std::iterator_traits<Iterator>::value_type lock_type;

      if (begin == end)
      {
        return;
      }
      bool start_with_begin = true;
      Iterator second = begin;
      ++second;
      Iterator next = second;

      for (;;)
      {
        unique_lock<lock_type> begin_lock(*begin, defer_lock);
        if (start_with_begin)
        {
          begin_lock.lock();
          Iterator const failed_lock = boost::try_lock(next, end);
          if (failed_lock == end)
          {
            begin_lock.release();
            return;
          }
          start_with_begin = false;
          next = failed_lock;
        }
        else
        {
          detail::range_lock_guard<Iterator> guard(next, end);
          if (begin_lock.try_lock())
          {
            Iterator const failed_lock = boost::try_lock(second, next);
            if (failed_lock == next)
            {
              begin_lock.release();
              guard.release();
              return;
            }
            start_with_begin = false;
            next = failed_lock;
          }
          else
          {
            start_with_begin = true;
            next = second;
          }
        }
      }
    }


    void lock_shared()
    {
      this->mtx().lock_shared();
    }

    bool try_lock_shared()
    {
      return this->mtx().try_lock_shared();
    }

    void unlock_shared()
    {
      this->mtx().unlock_shared();
    }


    bool try_lock_shared_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_lock_shared_until(abs_time);
    }

    bool try_lock_shared_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_lock_shared_for(rel_time);
    }


    void lock_upgrade()
    {
      this->mtx().lock_upgrade();
    }


    bool try_lock_upgrade()
    {
      return this->mtx().try_lock_upgrade();
    }


    void unlock_upgrade()
    {
      this->mtx().unlock_upgrade();
    }


    bool try_lock_upgrade_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_lock_upgrade_until(abs_time);
    }

    bool try_lock_upgrade_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_lock_upgrade_for(rel_time);
    }


    bool try_unlock_shared_and_lock()
    {
      return this->mtx().try_unlock_shared_and_lock();
    }


    bool try_unlock_shared_and_lock_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_unlock_shared_and_lock_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_unlock_shared_and_lock_for(rel_time);
    }


    void unlock_and_lock_shared()
    {
      this->mtx().unlock_and_lock_shared();
    }


    bool try_unlock_shared_and_lock_upgrade()
    {
      return this->mtx().try_unlock_shared_and_lock_upgrade();
    }


    bool try_unlock_shared_and_lock_upgrade_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_unlock_shared_and_lock_upgrade_until(abs_time);
    }

    bool try_unlock_shared_and_lock_upgrade_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_unlock_shared_and_lock_upgrade_for(rel_time);
    }


    void unlock_and_lock_upgrade()
    {
      this->mtx().unlock_and_lock_upgrade();
    }


    void unlock_upgrade_and_lock()
    {
      this->mtx().unlock_upgrade_and_lock();
    }


    bool try_unlock_upgrade_and_lock()
    {
      return this->mtx().try_unlock_upgrade_and_lock();
    }

    bool try_unlock_upgrade_and_lock_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_unlock_upgrade_and_lock_until(abs_time);
    }

    bool try_unlock_upgrade_and_lock_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_unlock_upgrade_and_lock_for(rel_time);
    }


    void unlock_upgrade_and_lock_shared()
    {
      this->mtx().unlock_upgrade_and_lock_shared();
    }
cv_status)


cv_status)





    externally_locked(mutex_type& mtx, const T& obj) :
      obj_(obj), mtx_(&mtx)
    {
    }

    externally_locked(mutex_type& mtx, BOOST_THREAD_RV_REF(T) obj) :
      obj_(move(obj)), mtx_(&mtx)
    {
    }

    externally_locked(mutex_type& mtx) // BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(T()))
    : obj_(), mtx_(&mtx)
    {
    }

    externally_locked(externally_locked const& rhs) //BOOST_NOEXCEPT
    : obj_(rhs.obj_), mtx_(rhs.mtx_)
    {
    }

    externally_locked(BOOST_THREAD_RV_REF(externally_locked) rhs) //BOOST_NOEXCEPT
    : obj_(move(rhs.obj_)), mtx_(rhs.mtx_)
    {
    }

    externally_locked& operator=(externally_locked const& rhs) //BOOST_NOEXCEPT
    {
      obj_=rhs.obj_;
      mtx_=rhs.mtx_;
      return *this;
    }

    externally_locked& operator=(BOOST_THREAD_RV_REF(externally_locked) rhs) // BOOST_NOEXCEPT
    {
      obj_=move(rhs.obj_);
      mtx_=rhs.mtx_;
      return *this;
    }


    void swap(externally_locked& rhs) //BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR)
    {
      swap(obj_, rhs.obj_);
      swap(mtx_, rhs.mtx_);
    }

    T& get(strict_lock<mutex_type>& lk)
    {
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return obj_;
    }


    const T& get(strict_lock<mutex_type>& lk) const
    {
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return obj_;
    }


    template <class Lock>
    T& get(nested_strict_lock<Lock>& lk)
    {
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return obj_;
    }


    template <class Lock>
    const T& get(nested_strict_lock<Lock>& lk) const
    {
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return obj_;
    }

    template <class Lock>
    T& get(Lock& lk)
    {
      BOOST_CONCEPT_ASSERT(( StrictLock<Lock> ));
      BOOST_STATIC_ASSERT( (is_strict_lock<Lock>::value)); /*< lk is a strict lock "sur parolle" >*/
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/

      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/

      return obj_;
    }


    mutex_type* mutex() const BOOST_NOEXCEPT
    {
      return mtx_;
    }


    void lock()
    {
      mtx_->lock();
    }

    void unlock()
    {
      mtx_->unlock();
    }

    bool try_lock()
    {
      return mtx_->try_lock();
    }



    externally_locked(T& obj, mutex_type& mtx) BOOST_NOEXCEPT :
      obj_(&obj), mtx_(&mtx)
    {
    }

    externally_locked(externally_locked const& rhs) BOOST_NOEXCEPT :
    obj_(rhs.obj_), mtx_(rhs.mtx_)
    {
    }

    externally_locked(BOOST_THREAD_RV_REF(externally_locked) rhs) BOOST_NOEXCEPT :
    obj_(rhs.obj_), mtx_(rhs.mtx_)
    {
    }

    externally_locked& operator=(externally_locked const& rhs) BOOST_NOEXCEPT
    {
      obj_=rhs.obj_;
      mtx_=rhs.mtx_;
      return *this;
    }

    externally_locked& operator=(BOOST_THREAD_RV_REF(externally_locked) rhs) BOOST_NOEXCEPT
    {
      obj_=rhs.obj_;
      mtx_=rhs.mtx_;
      return *this;
    }


    void swap(externally_locked& rhs) BOOST_NOEXCEPT
    {
      swap(obj_, rhs.obj_);
      swap(mtx_, rhs.mtx_);
    }

    T& get(strict_lock<mutex_type> const& lk)
    {
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }


    const T& get(strict_lock<mutex_type> const& lk) const
    {
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }


    template <class Lock>
    T& get(nested_strict_lock<Lock> const& lk)
    {
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }


    template <class Lock>
    const T& get(nested_strict_lock<Lock> const& lk) const
    {
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }

    template <class Lock>
    T& get(Lock const& lk)
    {
      BOOST_CONCEPT_ASSERT(( StrictLock<Lock> ));
      BOOST_STATIC_ASSERT( (is_strict_lock<Lock>::value)); /*< lk is a strict lock "sur parolle" >*/
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }

    template <class Lock>
    T const& get(Lock const& lk) const
    {
      BOOST_CONCEPT_ASSERT(( StrictLock<Lock> ));
      BOOST_STATIC_ASSERT( (is_strict_lock<Lock>::value)); /*< lk is a strict lock "sur parolle" >*/
      BOOST_STATIC_ASSERT( (is_same<mutex_type, typename Lock::mutex_type>::value)); /*< that locks the same type >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.owns_lock(mtx_), lock_error() ); /*< run time check throw if not locks the same >*/
      return *obj_;
    }

    mutex_type* mutex() const BOOST_NOEXCEPT
    {
      return mtx_;
    }


    void lock()
    {
      mtx_->lock();
    }

    void unlock()
    {
      mtx_->unlock();
    }

    bool try_lock()
    {
      return mtx_->try_lock();
    }


  template <typename T, typename MutexType>
  void swap(externally_locked<T, MutexType> & lhs, externally_locked<T, MutexType> & rhs) // BOOST_NOEXCEPT
  {
    lhs.swap(rhs);
  }

    explicit strict_lock(mutex_type& mtx) :
      mtx_(mtx)
    {
      mtx.lock();
    }

    ~strict_lock()
    {
      mtx_.unlock();
    }

    mutex_type* mutex() const BOOST_NOEXCEPT
    {
      return &mtx_;
    }

    bool owns_lock() const BOOST_NOEXCEPT
    {
      return true;
    }

    bool owns_lock(const mutex_type* l) const BOOST_NOEXCEPT
    {
      return l == mutex();
    }

    explicit nested_strict_lock(Lock& lk) :
      lk_(lk) /*< Store reference to lk >*/
    {
      /*< Define BOOST_THREAD_DONT_CHECK_PRECONDITIONS if you don't want to check lk ownership >*/
      BOOST_THREAD_ASSERT_PRECONDITION(  lk.mutex() != 0,
          lock_error()
      );
      if (!lk.owns_lock()) lk.lock(); /*< ensures it is locked >*/
      tmp_lk_ = move(lk); /*< Move ownership to temporary lk >*/
    }

    ~nested_strict_lock()BOOST_NOEXCEPT
    {
      lk_ = move(tmp_lk_); /*< Move ownership to nesting lock >*/
    }

    mutex_type* mutex() const BOOST_NOEXCEPT
    {
      return tmp_lk_.mutex();
    }

    bool owns_lock() const BOOST_NOEXCEPT
    {
      return true;
    }

    bool owns_lock(mutex_type const* l) const BOOST_NOEXCEPT
    {
      return l == mutex();
    }



    void notify_not_empty_if_needed(unique_lock<mutex>& lk)
    {
      if (waiting_empty_ > 0)
      {
        --waiting_empty_;
        lk.unlock();
        not_empty_.notify_one();
      }
    }


  template <typename ValueType>
  sync_queue<ValueType>::sync_queue() :
    waiting_empty_(0), data_(), closed_(false)
  {
    BOOST_ASSERT(data_.empty());
  }


  template <typename ValueType>
  sync_queue<ValueType>::~sync_queue()
  {
  }


  template <typename ValueType>
  void sync_queue<ValueType>::close()
  {
    {
      lock_guard<mutex> lk(mtx_);
      closed_ = true;
    }
    not_empty_.notify_all();
  }


  template <typename ValueType>
  bool sync_queue<ValueType>::closed() const
  {
    lock_guard<mutex> lk(mtx_);
    return closed_;
  }


  template <typename ValueType>
  bool sync_queue<ValueType>::empty() const
  {
    lock_guard<mutex> lk(mtx_);
    return empty(lk);
  }

  template <typename ValueType>
  bool sync_queue<ValueType>::full() const
  {
    return false;
  }


  template <typename ValueType>
  typename sync_queue<ValueType>::size_type sync_queue<ValueType>::size() const
  {
    lock_guard<mutex> lk(mtx_);
    return size(lk);
  }


  template <typename ValueType>
  bool sync_queue<ValueType>::try_pull(ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  boost::shared_ptr<ValueType> sync_queue<ValueType>::try_pull()
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_pull(lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_queue<ValueType>::pull(ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk);
      pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  void sync_queue<ValueType>::pull(ValueType& elem, bool & closed)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk, closed);
      if (closed) {return;}
      pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  ValueType sync_queue<ValueType>::pull()
  {
    try
    {
      value_type elem;
      pull(elem);
      return boost::move(elem);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  boost::shared_ptr<ValueType> sync_queue<ValueType>::ptr_pull()
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk);
      return ptr_pull(lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  bool sync_queue<ValueType>::try_push(const ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_queue<ValueType>::push(const ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      throw_if_closed(lk);
      push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  bool sync_queue<ValueType>::try_push(BOOST_THREAD_RV_REF(ValueType) elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_queue<ValueType>::push(BOOST_THREAD_RV_REF(ValueType) elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      throw_if_closed(lk);
      push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  sync_queue<ValueType>& operator<<(sync_queue<ValueType>& sbq, BOOST_THREAD_RV_REF(ValueType) elem)
  {
    sbq.push(boost::forward<ValueType>(elem));
    return sbq;
  }


  template <typename ValueType>
  sync_queue<ValueType>& operator<<(sync_queue<ValueType>& sbq, ValueType const&elem)
  {
    sbq.push(elem);
    return sbq;
  }


  template <typename ValueType>
  sync_queue<ValueType>& operator>>(sync_queue<ValueType>& sbq, ValueType &elem)
  {
    sbq.pull(elem);
    return sbq;
  }

    void noop()
    {
    }

    static completion_function noop()
    {
      return completion_function(&thread_detail::noop);
    }

      around_wait(completion_latch &that, boost::unique_lock<boost::mutex> &lk)
      : that_(that), lk_(lk)
      {
        that_.leavers_.cond_.wait(lk, detail::counter_is_zero(that_.leavers_));
        that_.waiters_.inc_and_notify_all();
        that_.leavers_.cond_.wait(lk, detail::counter_is_not_zero(that_.leavers_));
      }

      ~around_wait()
      {
        that_.waiters_.dec_and_notify_all();
      }


    bool count_down(unique_lock<mutex> &lk)
    {
      BOOST_ASSERT(count_ > 0);
      if (--count_ == 0)
      {
        waiters_.cond_.wait(lk, detail::counter_is_not_zero(waiters_));
        leavers_.assign_and_notify_all(waiters_);
        count_.cond_.notify_all();
        waiters_.cond_.wait(lk, detail::counter_is_zero(waiters_));
        leavers_.assign_and_notify_all(0);
        lk.unlock();
        funct_();
        return true;
      }
      return false;
    }

    ~completion_latch()
    {
    }

    void wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      around_wait aw(*this, lk);
      count_.cond_.wait(lk, detail::counter_is_zero(count_));
    }

    bool try_wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      around_wait aw(*this, lk);
      return (count_ == 0);
    }

    template <class Rep, class Period>
    cv_status wait_for(const chrono::duration<Rep, Period>& rel_time)
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      around_wait aw(*this, lk);
      return count_.cond_.wait_for(lk, rel_time, detail::counter_is_zero(count_))
              ? cv_status::no_timeout
              : cv_status::timeout;
    }

    template <class Clock, class Duration>
    cv_status wait_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      around_wait aw(*this, lk);
      return count_.cond_.wait_until(lk, abs_time, detail::counter_is_zero(count_))
          ? cv_status::no_timeout
          : cv_status::timeout;
    }

    void count_down()
    {
      unique_lock<mutex> lk(mutex_);
      count_down(lk);
    }

    void signal()
    {
      count_down();
    }

    void count_down_and_wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      if (count_down(lk))
      {
        return;
      }
      around_wait aw(*this, lk);
      count_.cond_.wait(lk, detail::counter_is_zero(count_));
    }

    void sync()
    {
      count_down_and_wait();
    }

    void reset(std::size_t count)
    {
      boost::lock_guard<boost::mutex> lk(mutex_);
      //BOOST_ASSERT(count_ == 0);
      count_ = count;
    }

    completion_function then(void(*funct)())
    {
      boost::lock_guard<boost::mutex> lk(mutex_);
      completion_function tmp(funct_);
      funct_ = completion_function(funct);
      return tmp;
    }

    void cvt_mutex_ptr(mutex_type*) {}


    BasicLock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    Lock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    TimedLock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    UniqueLock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    SharedLock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    UpgradeLock() :
      mtx(*static_cast<mutex_type*>(0))
    {}


    StrictLock() :
      l1(*static_cast<Lk*>(0)),
      mtx(*static_cast<mutex_type*>(0))
    {}
future_errc)


future_errc)



    inline
    error_code
    make_error_code(future_errc e) BOOST_NOEXCEPT
    {
        return error_code(underlying_cast<int>(e), boost::future_category());
    }


    inline
    error_condition
    make_error_condition(future_errc e) BOOST_NOEXCEPT
    {
        return error_condition(underlying_cast<int>(e), future_category());
    }

    template <class F>
    explicit strict_scoped_thread(BOOST_THREAD_FWD_REF(F) f,
        typename disable_if<is_same<typename decay<F>::type, thread>, dummy* >::type=0) :
      t_(boost::forward<F>(f)) {}

    template <class F, class A1>
    strict_scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1)) {}

    template <class F, class A1, class A2>
    strict_scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1, BOOST_THREAD_FWD_REF(A2) a2) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1), boost::forward<A2>(a2)) {}

    template <class F, class A1, class A2, class A3>
    strict_scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1, BOOST_THREAD_FWD_REF(A2) a2, BOOST_THREAD_FWD_REF(A3) a3) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3)) {}

    explicit strict_scoped_thread(BOOST_THREAD_RV_REF(thread) t) BOOST_NOEXCEPT :
    t_(boost::move(t))
    {
    }

    ~strict_scoped_thread()
    {
      CallableThread on_destructor;

      on_destructor(t_);
    }



    scoped_thread() BOOST_NOEXCEPT:
    t_()
    {
    }

    template <class F>
    explicit scoped_thread(BOOST_THREAD_FWD_REF(F) f,
        typename disable_if<is_same<typename decay<F>::type, thread>, dummy* >::type=0) :
      t_(boost::forward<F>(f)) {}

    template <class F, class A1>
    scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1)) {}

    template <class F, class A1, class A2>
    scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1, BOOST_THREAD_FWD_REF(A2) a2) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1), boost::forward<A2>(a2)) {}

    template <class F, class A1, class A2, class A3>
    scoped_thread(BOOST_THREAD_FWD_REF(F) f, BOOST_THREAD_FWD_REF(A1) a1, BOOST_THREAD_FWD_REF(A2) a2, BOOST_THREAD_FWD_REF(A3) a3) :
      t_(boost::forward<F>(f), boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3)) {}

    explicit scoped_thread(BOOST_THREAD_RV_REF(thread) t) BOOST_NOEXCEPT :
    t_(boost::move(t))
    {
    }

    scoped_thread(BOOST_RV_REF(scoped_thread) x) BOOST_NOEXCEPT :
    t_(boost::move(x.t_))
    {}

    ~scoped_thread()
    {
      CallableThread on_destructor;

      on_destructor(t_);
    }

    scoped_thread& operator=(BOOST_RV_REF(scoped_thread) x)
    {
      t_ = boost::move(x.t_);
      return *this;
    }

    void swap(scoped_thread& x) BOOST_NOEXCEPT
    {
      t_.swap(x.t_);
    }

    inline thread::id get_id() const BOOST_NOEXCEPT
    {
      return t_.get_id();
    }


    void detach()
    {
      t_.detach();
    }


    void join()
    {
      t_.join();
    }

    template <class Rep, class Period>
    bool try_join_for(const chrono::duration<Rep, Period>& rel_time)
    {
      return t_.try_join_for(rel_time);
    }


    template <class Clock, class Duration>
    bool try_join_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      return t_.try_join_until(abs_time);
    }


    thread::native_handle_type native_handle()BOOST_NOEXCEPT
    {
      return t_.native_handle();
    }


    bool joinable() const BOOST_NOEXCEPT
    {
      return t_.joinable();
    }

    void interrupt()
    {
      t_.interrupt();
    }


    bool interruption_requested() const BOOST_NOEXCEPT
    {
      return t_.interruption_requested();
    }


    static unsigned hardware_concurrency()BOOST_NOEXCEPT
    {
      return thread::hardware_concurrency();
    }

  template <class Destroyer>
  void swap(scoped_thread<Destroyer>& lhs, scoped_thread<Destroyer>& rhs)
BOOST_NOEXCEPT {
  return lhs.swap(rhs);
}

    template <typename Clock, typename Duration>
    bool try_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_lock_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_lock_for(duration_cast<Clock::duration>(rel_time));
    }

            virtual ~tss_cleanup_function()
            {}

            void operator()(void* data)
            {
                delete static_cast<T*>(data);
            }

            
            explicit run_custom_cleanup_function(void (*cleanup_function_)(T*)):
                cleanup_function(cleanup_function_)
            {}

            
            void operator()(void* data)
            {
                cleanup_function(static_cast<T*>(data));
            }

        
        thread_specific_ptr():
            cleanup(detail::heap_new<delete_data>(),detail::do_heap_delete<delete_data>())
        {}

        explicit thread_specific_ptr(void (*func_)(T*))
        {
            if(func_)
            {
                cleanup.reset(detail::heap_new<run_custom_cleanup_function>(func_),detail::do_heap_delete<run_custom_cleanup_function>());
            }
        }

        ~thread_specific_ptr()
        {
            detail::set_tss_data(this,boost::shared_ptr<detail::tss_cleanup_function>(),0,true);
        }


        T* get() const
        {
            return static_cast<T*>(detail::get_tss_data(this));
        }

        T* operator->() const
        {
            return get();
        }

        T& operator*() const
        {
            return *get();
        }

        T* release()
        {
            T* const temp=get();
            detail::set_tss_data(this,boost::shared_ptr<detail::tss_cleanup_function>(),0,false);
            return temp;
        }

        void reset(T* new_value=0)
        {
            T* const current_value=get();
            if(current_value!=new_value)
            {
                detail::set_tss_data(this,cleanup,new_value,true);
            }
        }



    unique_lock()BOOST_NOEXCEPT :
    m(0),is_locked(false)
    {}


    explicit unique_lock(Mutex& m_) :
      m(&m_), is_locked(false)
    {
      lock();
    }

    unique_lock(Mutex& m_, adopt_lock_t) :
      m(&m_), is_locked(true)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

    unique_lock(Mutex& m_, defer_lock_t)BOOST_NOEXCEPT:
    m(&m_),is_locked(false)
    {}

    unique_lock(Mutex& m_, try_to_lock_t) :
      m(&m_), is_locked(false)
    {
      try_lock();
    }

    template<typename TimeDuration>
    unique_lock(Mutex& m_,TimeDuration const& target_time):
    m(&m_),is_locked(false)
    {
      timed_lock(target_time);
    }

    unique_lock(Mutex& m_,system_time const& target_time):
    m(&m_),is_locked(false)
    {
      timed_lock(target_time);
    }

    template <class Clock, class Duration>
    unique_lock(Mutex& mtx, const chrono::time_point<Clock, Duration>& t)
    : m(&mtx), is_locked(mtx.try_lock_until(t))
    {
    }

    template <class Rep, class Period>
    unique_lock(Mutex& mtx, const chrono::duration<Rep, Period>& d)
    : m(&mtx), is_locked(mtx.try_lock_for(d))
    {
    }


    unique_lock(BOOST_THREAD_RV_REF(unique_lock) other) BOOST_NOEXCEPT:
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }

    unique_lock& operator=(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other) //BOOST_NOEXCEPT
    {
      unique_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }

    unique_lock& operator=(BOOST_THREAD_RV_REF(unique_lock) other) //BOOST_NOEXCEPT
    {
      unique_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }

    unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul, try_to_lock_t)
    : m(0),is_locked(false)
    {
      if (BOOST_THREAD_RV(ul).owns_lock())
      {
        if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock())
        {
          m = BOOST_THREAD_RV(ul).release();
          is_locked = true;
        }
      }
      else
      {
        m = BOOST_THREAD_RV(ul).release();
      }
    }

    template <class Clock, class Duration>
    unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul,
        const chrono::time_point<Clock, Duration>& abs_time)
    : m(0),is_locked(false)
    {
      if (BOOST_THREAD_RV(ul).owns_lock())
      {
        if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock_until(abs_time))
        {
          m = BOOST_THREAD_RV(ul).release();
          is_locked = true;
        }
      }
      else
      {
        m = BOOST_THREAD_RV(ul).release();
      }
    }


    template <class Rep, class Period>
    unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<mutex_type> BOOST_THREAD_RV_REF_END ul,
        const chrono::duration<Rep, Period>& rel_time)
    : m(0),is_locked(false)
    {
      if (BOOST_THREAD_RV(ul).owns_lock())
      {
        if (BOOST_THREAD_RV(ul).mutex()->try_unlock_upgrade_and_lock_for(rel_time))
        {
          m = BOOST_THREAD_RV(ul).release();
          is_locked = true;
        }
      }
      else
      {
        m = BOOST_THREAD_RV(ul).release();
      }
    }


    void swap(unique_lock& other)BOOST_NOEXCEPT
    {
      std::swap(m,other.m);
      std::swap(is_locked,other.is_locked);
    }


    ~unique_lock()
    {
      if (owns_lock())
      {
        m->unlock();
      }
    }

    void lock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if (owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      m->lock();
      is_locked = true;
    }

    bool try_lock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if (owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked = m->try_lock();
      return is_locked;
    }

    template<typename TimeDuration>
    bool timed_lock(TimeDuration const& relative_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked=m->timed_lock(relative_time);
      return is_locked;
    }


    bool timed_lock(::boost::system_time const& absolute_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked=m->timed_lock(absolute_time);
      return is_locked;
    }

    bool timed_lock(::boost::xtime const& absolute_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked=m->timed_lock(absolute_time);
      return is_locked;
    }


    template <class Rep, class Period>
    bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked=m->try_lock_for(rel_time);
      return is_locked;
    }

    template <class Clock, class Duration>
    bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost unique_lock owns already the mutex"));
      }
      is_locked=m->try_lock_until(abs_time);
      return is_locked;
    }


    void unlock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock has no mutex"));
      }
      if (!owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost unique_lock doesn't own the mutex"));
      }
      m->unlock();
      is_locked = false;
    }

    operator bool_type() const BOOST_NOEXCEPT
    {
      return is_locked?&unique_lock::lock:0;
    }

    bool operator!() const BOOST_NOEXCEPT
    {
      return !owns_lock();
    }

    bool owns_lock() const BOOST_NOEXCEPT
    {
      return is_locked;
    }


    Mutex* mutex() const BOOST_NOEXCEPT
    {
      return m;
    }


    Mutex* release()BOOST_NOEXCEPT
    {
      Mutex* const res=m;
      m=0;
      is_locked=false;
      return res;
    }


  template<typename Mutex>
  void swap(unique_lock<Mutex>& lhs, unique_lock<Mutex>& rhs)
  BOOST_NOEXCEPT
  {
    lhs.swap(rhs);
  }




    shared_lock() BOOST_NOEXCEPT:
    m(0),is_locked(false)
    {}


    explicit shared_lock(Mutex& m_):
    m(&m_),is_locked(false)
    {
      lock();
    }

    shared_lock(Mutex& m_,adopt_lock_t):
    m(&m_),is_locked(true)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

    shared_lock(Mutex& m_,defer_lock_t) BOOST_NOEXCEPT:
    m(&m_),is_locked(false)
    {}

    shared_lock(Mutex& m_,try_to_lock_t):
    m(&m_),is_locked(false)
    {
      try_lock();
    }

    shared_lock(Mutex& m_,system_time const& target_time):
    m(&m_),is_locked(false)
    {
      timed_lock(target_time);
    }

    template <class Clock, class Duration>
    shared_lock(Mutex& mtx, const chrono::time_point<Clock, Duration>& t)
    : m(&mtx), is_locked(mtx.try_lock_shared_until(t))
    {
    }

    template <class Rep, class Period>
    shared_lock(Mutex& mtx, const chrono::duration<Rep, Period>& d)
    : m(&mtx), is_locked(mtx.try_lock_shared_for(d))
    {
    }


    shared_lock(BOOST_THREAD_RV_REF_BEG shared_lock<Mutex> BOOST_THREAD_RV_REF_END other) BOOST_NOEXCEPT:
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }
 shared_lock(BOOST_THREAD_RV_REF_BEG unique_lock<Mutex> BOOST_THREAD_RV_REF_END other):
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      if(is_locked)
      {
        m->unlock_and_lock_shared();
      }
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }
 shared_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other):
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      if(is_locked)
      {
        m->unlock_upgrade_and_lock_shared();
      }
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }

    shared_lock& operator=(BOOST_THREAD_RV_REF_BEG shared_lock<Mutex> BOOST_THREAD_RV_REF_END other) //BOOST_NOEXCEPT
    {
      shared_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }

    shared_lock& operator=(BOOST_THREAD_RV_REF_BEG unique_lock<Mutex> BOOST_THREAD_RV_REF_END other)
    {
      shared_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }


    shared_lock& operator=(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other)
    {
      shared_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }


    void swap(shared_lock& other) BOOST_NOEXCEPT
    {
      std::swap(m,other.m);
      std::swap(is_locked,other.is_locked);
    }


    Mutex* mutex() const BOOST_NOEXCEPT
    {
      return m;
    }


    Mutex* release() BOOST_NOEXCEPT
    {
      Mutex* const res=m;
      m=0;
      is_locked=false;
      return res;
    }


    ~shared_lock()
    {
      if(owns_lock())
      {
        m->unlock_shared();
      }
    }

    void lock()
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      m->lock_shared();
      is_locked=true;
    }

    bool try_lock()
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->try_lock_shared();
      return is_locked;
    }

    bool timed_lock(boost::system_time const& target_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->timed_lock_shared(target_time);
      return is_locked;
    }

    template<typename Duration>
    bool timed_lock(Duration const& target_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->timed_lock_shared(target_time);
      return is_locked;
    }

    template <class Rep, class Period>
    bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->try_lock_shared_for(rel_time);
      return is_locked;
    }

    template <class Clock, class Duration>
    bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->try_lock_shared_until(abs_time);
      return is_locked;
    }

    void unlock()
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(!owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock doesn't own the mutex"));
      }
      m->unlock_shared();
      is_locked=false;
    }

    operator bool_type() const BOOST_NOEXCEPT
    {
      return is_locked?&shared_lock::lock:0;
    }

    bool operator!() const BOOST_NOEXCEPT
    {
      return !owns_lock();
    }

    bool owns_lock() const BOOST_NOEXCEPT
    {
      return is_locked;
    }


  template<typename Mutex>
  void swap(shared_lock<Mutex>& lhs,shared_lock<Mutex>& rhs) BOOST_NOEXCEPT
  {
    lhs.swap(rhs);
  }




    upgrade_lock()BOOST_NOEXCEPT:
    m(0),is_locked(false)
    {}


    explicit upgrade_lock(Mutex& m_) :
      m(&m_), is_locked(false)
    {
      lock();
    }

    upgrade_lock(Mutex& m_, adopt_lock_t) :
      m(&m_), is_locked(true)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

    upgrade_lock(Mutex& m_, defer_lock_t)BOOST_NOEXCEPT:
    m(&m_),is_locked(false)
    {}

    upgrade_lock(Mutex& m_, try_to_lock_t) :
      m(&m_), is_locked(false)
    {
      try_lock();
    }

    template <class Clock, class Duration>
    upgrade_lock(Mutex& mtx, const chrono::time_point<Clock, Duration>& t)
    : m(&mtx), is_locked(mtx.try_lock_upgrade_until(t))
    {
    }

    template <class Rep, class Period>
    upgrade_lock(Mutex& mtx, const chrono::duration<Rep, Period>& d)
    : m(&mtx), is_locked(mtx.try_lock_upgrade_for(d))
    {
    }


    upgrade_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other) BOOST_NOEXCEPT:
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }
 upgrade_lock(BOOST_THREAD_RV_REF_BEG unique_lock<Mutex> BOOST_THREAD_RV_REF_END other):
    m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
    {
      if(is_locked)
      {
        m->unlock_and_lock_upgrade();
      }
      BOOST_THREAD_RV(other).is_locked=false;
      BOOST_THREAD_RV(other).m=0;
    }

    upgrade_lock& operator=(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other) //BOOST_NOEXCEPT
    {
      upgrade_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }

    upgrade_lock& operator=(BOOST_THREAD_RV_REF_BEG unique_lock<Mutex> BOOST_THREAD_RV_REF_END other)
    {
      upgrade_lock temp(::boost::move(other));
      swap(temp);
      return *this;
    }

    void swap(upgrade_lock& other)BOOST_NOEXCEPT
    {
      std::swap(m,other.m);
      std::swap(is_locked,other.is_locked);
    }

    Mutex* mutex() const BOOST_NOEXCEPT
    {
      return m;
    }


    Mutex* release()BOOST_NOEXCEPT
    {
      Mutex* const res=m;
      m=0;
      is_locked=false;
      return res;
    }

    ~upgrade_lock()
    {
      if (owns_lock())
      {
        m->unlock_upgrade();
      }
    }

    void lock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if (owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::resource_deadlock_would_occur, "boost upgrade_lock owns already the mutex"));
      }
      m->lock_upgrade();
      is_locked = true;
    }

    bool try_lock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if (owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::resource_deadlock_would_occur, "boost upgrade_lock owns already the mutex"));
      }
      is_locked = m->try_lock_upgrade();
      return is_locked;
    }

    void unlock()
    {
      if (m == 0)
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if (!owns_lock())
      {
        boost::throw_exception(
            boost::lock_error(system::errc::operation_not_permitted, "boost upgrade_lock doesn't own the mutex"));
      }
      m->unlock_upgrade();
      is_locked = false;
    }

    template <class Rep, class Period>
    bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->try_lock_upgrade_for(rel_time);
      return is_locked;
    }

    template <class Clock, class Duration>
    bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      if(m==0)
      {
        boost::throw_exception(boost::lock_error(system::errc::operation_not_permitted, "boost shared_lock has no mutex"));
      }
      if(owns_lock())
      {
        boost::throw_exception(boost::lock_error(system::errc::resource_deadlock_would_occur, "boost shared_lock owns already the mutex"));
      }
      is_locked=m->try_lock_upgrade_until(abs_time);
      return is_locked;
    }

    operator bool_type() const BOOST_NOEXCEPT
    {
      return is_locked?&upgrade_lock::lock:0;
    }

    bool operator!() const BOOST_NOEXCEPT
    {
      return !owns_lock();
    }

    bool owns_lock() const BOOST_NOEXCEPT
    {
      return is_locked;
    }


  template<typename Mutex>
  void swap(upgrade_lock<Mutex>& lhs, upgrade_lock<Mutex>& rhs)
  BOOST_NOEXCEPT
  {
    lhs.swap(rhs);
  }


  template<typename Mutex>
  unique_lock<Mutex>::unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_lock<Mutex> BOOST_THREAD_RV_REF_END other):
  m(BOOST_THREAD_RV(other).m),is_locked(BOOST_THREAD_RV(other).is_locked)
  {
    if(is_locked)
    {
      m->unlock_upgrade_and_lock();
    }
    BOOST_THREAD_RV(other).release();
  }




    explicit upgrade_to_unique_lock(upgrade_lock<Mutex>& m_) :
      source(&m_), exclusive(::boost::move(*source))
    {
    }

    ~upgrade_to_unique_lock()
    {
      if (source)
      {
        *source = BOOST_THREAD_MAKE_RV_REF(upgrade_lock<Mutex> (::boost::move(exclusive)));
      }
    }


    upgrade_to_unique_lock(BOOST_THREAD_RV_REF_BEG upgrade_to_unique_lock<Mutex> BOOST_THREAD_RV_REF_END other) BOOST_NOEXCEPT:
    source(BOOST_THREAD_RV(other).source),exclusive(::boost::move(BOOST_THREAD_RV(other).exclusive))
    {
      BOOST_THREAD_RV(other).source=0;
    }

    upgrade_to_unique_lock& operator=(BOOST_THREAD_RV_REF_BEG upgrade_to_unique_lock<Mutex> BOOST_THREAD_RV_REF_END other) //BOOST_NOEXCEPT
    {
      upgrade_to_unique_lock temp(other);
      swap(temp);
      return *this;
    }


    void swap(upgrade_to_unique_lock& other)BOOST_NOEXCEPT
    {
      std::swap(source,other.source);
      exclusive.swap(other.exclusive);
    }

    operator bool_type() const BOOST_NOEXCEPT
    {
      return exclusive.owns_lock()?&upgrade_to_unique_lock::swap:0;
    }

    bool operator!() const BOOST_NOEXCEPT
    {
      return !owns_lock();
    }


    bool owns_lock() const BOOST_NOEXCEPT
    {
      return exclusive.owns_lock();
    }




    try_lock_wrapper()
    {}


    explicit try_lock_wrapper(Mutex& m):
    base(m,try_to_lock)
    {}


    try_lock_wrapper(Mutex& m_,adopt_lock_t):
    base(m_,adopt_lock)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m_));
#endif
    }

    try_lock_wrapper(Mutex& m_,defer_lock_t):
    base(m_,defer_lock)
    {}

    try_lock_wrapper(Mutex& m_,try_to_lock_t):
    base(m_,try_to_lock)
    {}

    try_lock_wrapper(BOOST_THREAD_RV_REF(try_lock_wrapper) other):
    base(BOOST_THREAD_RV_REF(base)(*other))
    {}

    try_lock_wrapper& operator=(BOOST_THREAD_RV_REF_BEG try_lock_wrapper<Mutex> BOOST_THREAD_RV_REF_END other)
    {
      try_lock_wrapper temp(other);
      swap(temp);
      return *this;
    }

    void swap(try_lock_wrapper& other)
    {
      base::swap(other);
    }

    void lock()
    {
      base::lock();
    }

    bool try_lock()
    {
      return base::try_lock();
    }

    void unlock()
    {
      base::unlock();
    }

    bool owns_lock() const
    {
      return base::owns_lock();
    }

    Mutex* mutex() const
    {
      return base::mutex();
    }

    Mutex* release()
    {
      return base::release();
    }

    operator bool_type() const
    {
      return base::operator bool_type();
    }

    bool operator!() const
    {
      return !this->owns_lock();
    }


  template<typename Mutex>
  void swap(try_lock_wrapper<Mutex>& lhs,try_lock_wrapper<Mutex>& rhs)
  {
    lhs.swap(rhs);
  }


        explicit reverse_lock(Lock& m_)
        : m(m_), mtx(0)
        {
            if (m.owns_lock())
            {
              m.unlock();
            }
            mtx=m.release();
        }

        ~reverse_lock()
        {
          if (mtx) {
            mtx->lock();
            m = BOOST_THREAD_MAKE_RV_REF(Lock(*mtx, adopt_lock));
          }
        }


    operator system_time() const
    {
        return boost::posix_time::from_time_t(0)+
            boost::posix_time::seconds(static_cast<long>(sec))+
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
            boost::posix_time::nanoseconds(nsec);
#else
        boost::posix_time::microseconds((nsec+500)/1000);
#endif
    }


inline xtime get_xtime(boost::system_time const& abs_time)
{
    xtime res;
    boost::posix_time::time_duration const time_since_epoch=abs_time-boost::posix_time::from_time_t(0);

    res.sec=static_cast<xtime::xtime_sec_t>(time_since_epoch.total_seconds());
    res.nsec=static_cast<xtime::xtime_nsec_t>(time_since_epoch.fractional_seconds()*(1000000000/time_since_epoch.ticks_per_second()));
    return res;
}


inline int xtime_get(struct xtime* xtp, int clock_type)
{
    if (clock_type == TIME_UTC_)
    {
        *xtp=get_xtime(get_system_time());
        return clock_type;
    }
    return 0;
}



inline int xtime_cmp(const xtime& xt1, const xtime& xt2)
{
    if (xt1.sec == xt2.sec)
        return (int)(xt1.nsec - xt2.nsec);
    else
        return (xt1.sec > xt2.sec) ? 1 : -1;
}




    stream_guard(externally_locked_stream<Stream, RecursiveMutex>& mtx) :
      mtx_(&mtx)
    {
      mtx.lock();
    }


    stream_guard(externally_locked_stream<Stream, RecursiveMutex>& mtx, adopt_lock_t) :
      mtx_(&mtx)
    {
    }


    stream_guard(BOOST_THREAD_RV_REF(stream_guard) rhs) BOOST_NOEXCEPT
    : mtx_(rhs.mtx_)
    {
      rhs.mtx_= 0;
    }


    ~stream_guard()
    {
      if (mtx_ != 0) mtx_->unlock();
    }


    bool owns_lock(const mutex_type * l) const BOOST_NOEXCEPT
    {
      return l == mtx_->mutex();
    }

    Stream& get() const
    {
      BOOST_THREAD_ASSERT_PRECONDITION(  mtx_, lock_error() );
      return mtx_->get(*this);
    }

    Stream& bypass() const
    {
      return get();
    }

    externally_locked_stream(Stream& stream, RecursiveMutex& mtx) BOOST_NOEXCEPT :
      base_type(stream, mtx)
    {
    }


    stream_guard<Stream, RecursiveMutex> hold() BOOST_NOEXCEPT
    {
      return stream_guard<Stream, RecursiveMutex> (*this);
    }

    Stream& bypass() const
    {
      stream_guard<Stream, RecursiveMutex> lk(*this);
      return get(lk);
    }


  template <typename Stream, typename RecursiveMutex, typename T>
  inline const stream_guard<Stream, RecursiveMutex>& operator<<(const stream_guard<Stream, RecursiveMutex>& lck, T arg)
  {
    lck.get() << arg;
    return lck;
  }


  template <typename Stream, typename RecursiveMutex>
  inline const stream_guard<Stream, RecursiveMutex>& operator<<(const stream_guard<Stream, RecursiveMutex>& lck, Stream& (*arg)(Stream&))
  {
    lck.get() << arg;
    return lck;
  }


  template <typename Stream, typename RecursiveMutex, typename T>
  inline const stream_guard<Stream, RecursiveMutex>& operator>>(const stream_guard<Stream, RecursiveMutex>& lck, T& arg)
  {
    lck.get() >> arg;
    return lck;
  }


  template <typename Stream, typename RecursiveMutex, typename T>
  inline stream_guard<Stream, RecursiveMutex> operator<<(externally_locked_stream<Stream, RecursiveMutex>& mtx, T arg)
  {
    stream_guard<Stream, RecursiveMutex> lk(mtx);
    mtx.get(lk) << arg;
    return boost::move(lk);
  }


  template <typename Stream, typename RecursiveMutex>
  inline stream_guard<Stream, RecursiveMutex> operator<<(externally_locked_stream<Stream, RecursiveMutex>& mtx, Stream& (*arg)(Stream&))
  {
    stream_guard<Stream, RecursiveMutex> lk(mtx);
    mtx.get(lk) << arg;
    return boost::move(lk);
  }


  template <typename Stream, typename RecursiveMutex, typename T>
  inline stream_guard<Stream, RecursiveMutex> operator>>(externally_locked_stream<Stream, RecursiveMutex>& mtx, T& arg)
  {
    stream_guard<Stream, RecursiveMutex> lk(mtx);
    mtx.get(lk) >> arg;
    return boost::move(lk);
  }

    void operator()(thread& t)
    {
      t.detach();
    }

    void operator()(thread& t)
    {
      if (t.joinable())
      {
        t.join();
      }
    }

    void operator()(thread& t)
    {
      t.interrupt();
      if (t.joinable())
      {
        t.join();
      }
    }


  template <typename Lockable>
  unique_lock<Lockable> make_unique_lock(Lockable& mtx)
  {
    return unique_lock<Lockable> (mtx);
  }


  template <typename Lockable>
  unique_lock<Lockable> make_unique_lock(Lockable& mtx, adopt_lock_t)
  {
    return unique_lock<Lockable> (mtx, adopt_lock);
  }


  template <typename Lockable>
  unique_lock<Lockable> make_unique_lock(Lockable& mtx, defer_lock_t)
  {
    return unique_lock<Lockable> (mtx, defer_lock);
  }


  template <typename Lockable>
  unique_lock<Lockable> make_unique_lock(Lockable& mtx, try_to_lock_t)
  {
    return unique_lock<Lockable> (mtx, try_to_lock);
  }



    const_strict_lock_ptr(T const& val, Lockable & mtx) :
      lk_(mtx), value_(val)
    {
    }

    const_strict_lock_ptr(T const& val, Lockable & mtx, adopt_lock_t tag) BOOST_NOEXCEPT :
      lk_(mtx, tag), value_(val)
    {
    }

    const_strict_lock_ptr(BOOST_THREAD_RV_REF(const_strict_lock_ptr) other) BOOST_NOEXCEPT
    : lk_(boost::move(BOOST_THREAD_RV(other).lk_)),value_(BOOST_THREAD_RV(other).value_)
    {
    }


    ~const_strict_lock_ptr()
    {
    }

    const T* operator->() const
    {
      return &value_;
    }

    const T& operator*() const
    {
      return value_;
    }



    strict_lock_ptr(T & val, Lockable & mtx) :
    base_type(val, mtx)
    {
    }

    strict_lock_ptr(T & val, Lockable & mtx, adopt_lock_t tag) :
    base_type(val, mtx, tag)
    {
    }

    strict_lock_ptr(BOOST_THREAD_RV_REF(strict_lock_ptr) other)
    : base_type(boost::move(static_cast<base_type&>(other)))
    {
    }


    ~strict_lock_ptr()
    {
    }

    T* operator->()
    {
      return const_cast<T*>(&this->value_);
    }

    T& operator*()
    {
      return const_cast<T&>(this->value_);
    }



    const_unique_lock_ptr(T const& val, Lockable & mtx)
    : base_type(mtx), value_(val)
    {
    }

    const_unique_lock_ptr(T const& val, Lockable & mtx, adopt_lock_t) BOOST_NOEXCEPT
    : base_type(mtx, adopt_lock), value_(val)
    {
    }

    const_unique_lock_ptr(T const& val, Lockable & mtx, defer_lock_t) BOOST_NOEXCEPT
    : base_type(mtx, defer_lock), value_(val)
    {
    }

    const_unique_lock_ptr(T const& val, Lockable & mtx, try_to_lock_t) BOOST_NOEXCEPT
    : base_type(mtx, try_to_lock), value_(val)
    {
    }

    const_unique_lock_ptr(BOOST_THREAD_RV_REF(const_unique_lock_ptr) other) BOOST_NOEXCEPT
    : base_type(boost::move(static_cast<base_type&>(other))), value_(BOOST_THREAD_RV(other).value_)
    {
    }

    ~const_unique_lock_ptr()
    {
    }

    const T* operator->() const
    {
      BOOST_ASSERT (this->owns_lock());
      return &value_;
    }

    const T& operator*() const
    {
      BOOST_ASSERT (this->owns_lock());
      return value_;
    }



    unique_lock_ptr(T & val, Lockable & mtx)
    : base_type(val, mtx)
    {
    }

    unique_lock_ptr(T & value, Lockable & mtx, adopt_lock_t) BOOST_NOEXCEPT
    : base_type(value, mtx, adopt_lock)
    {
    }

    unique_lock_ptr(T & value, Lockable & mtx, defer_lock_t) BOOST_NOEXCEPT
    : base_type(value, mtx, defer_lock)
    {
    }

    unique_lock_ptr(T & value, Lockable & mtx, try_to_lock_t) BOOST_NOEXCEPT
    : base_type(value, mtx, try_to_lock)
    {
    }

    unique_lock_ptr(BOOST_THREAD_RV_REF(unique_lock_ptr) other) BOOST_NOEXCEPT
    : base_type(boost::move(static_cast<base_type&>(other)))
    {
    }


    ~unique_lock_ptr()
    {
    }

    T* operator->()
    {
      BOOST_ASSERT (this->owns_lock());
      return const_cast<T*>(&this->value_);
    }

    T& operator*()
    {
      BOOST_ASSERT (this->owns_lock());
      return const_cast<T&>(this->value_);
    }

    synchronized_value()
    //BOOST_NOEXCEPT_IF(is_nothrow_default_constructible<T>::value)
    : value_()
    {
    }

    synchronized_value(T const& other)
    //BOOST_NOEXCEPT_IF(is_nothrow_copy_constructible<T>::value)
    : value_(other)
    {
    }

    synchronized_value(BOOST_THREAD_RV_REF(T) other)
    //BOOST_NOEXCEPT_IF(is_nothrow_move_constructible<T>::value)
    : value_(boost::move(other))
    {
    }

    synchronized_value(synchronized_value const& rhs)
    {
      strict_lock<mutex_type> lk(rhs.mtx_);
      value_ = rhs.value_;
    }

    synchronized_value(BOOST_THREAD_RV_REF(synchronized_value) other)
    {
      strict_lock<mutex_type> lk(other.mtx_);
      value_= boost::move(other.value_);
    }


    synchronized_value& operator=(synchronized_value const& rhs)
    {
      if(&rhs != this)
      {
        // auto _ = make_unique_locks(mtx_, rhs.mtx_);
        unique_lock<mutex_type> lk1(mtx_, defer_lock);
        unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
        lock(lk1,lk2);

        value_ = rhs.value_;
      }
      return *this;
    }

    synchronized_value& operator=(value_type const& val)
    {
      {
        strict_lock<mutex_type> lk(mtx_);
        value_ = val;
      }
      return *this;
    }

    T get() const
    {
      strict_lock<mutex_type> lk(mtx_);
      return value_;
    }

    T const& value() const
    {
      return value_;
    }

    mutex_type const& mutex() const
    {
      return mtx_;
    }

    void swap(synchronized_value & rhs)
    {
      if (this == &rhs) {
        return;
      }
      // auto _ = make_unique_locks(mtx_, rhs.mtx_);
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);
      boost::swap(value_, rhs.value_);
    }

    void swap(value_type & rhs)
    {
      strict_lock<mutex_type> lk(mtx_);
      boost::swap(value_, rhs);
    }

    strict_lock_ptr<T,Lockable> operator->()
    {
      return BOOST_THREAD_MAKE_RV_REF((strict_lock_ptr<T,Lockable>(value_, mtx_)));
    }

    const_strict_lock_ptr<T,Lockable> operator->() const
    {
      return BOOST_THREAD_MAKE_RV_REF((const_strict_lock_ptr<T,Lockable>(value_, mtx_)));
    }

    strict_lock_ptr<T,Lockable> synchronize()
    {
      return BOOST_THREAD_MAKE_RV_REF((strict_lock_ptr<T,Lockable>(value_, mtx_)));
    }

    const_strict_lock_ptr<T,Lockable> synchronize() const
    {
      return BOOST_THREAD_MAKE_RV_REF((const_strict_lock_ptr<T,Lockable>(value_, mtx_)));
    }


    unique_lock_ptr<T,Lockable> unique_synchronize()
    {
      return BOOST_THREAD_MAKE_RV_REF((unique_lock_ptr<T,Lockable>(value_, mtx_)));
    }

    const_unique_lock_ptr<T,Lockable> unique_synchronize() const
    {
      return BOOST_THREAD_MAKE_RV_REF((const_unique_lock_ptr<T,Lockable>(value_, mtx_)));
    }

    unique_lock_ptr<T,Lockable> unique_synchronize(defer_lock_t tag)
    {
      return BOOST_THREAD_MAKE_RV_REF((unique_lock_ptr<T,Lockable>(value_, mtx_, tag)));
    }

    const_unique_lock_ptr<T,Lockable> unique_synchronize(defer_lock_t tag) const
    {
      return BOOST_THREAD_MAKE_RV_REF((const_unique_lock_ptr<T,Lockable>(value_, mtx_, tag)));
    }

    unique_lock_ptr<T,Lockable> defer_synchronize() BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((unique_lock_ptr<T,Lockable>(value_, mtx_, defer_lock)));
    }

    const_unique_lock_ptr<T,Lockable> defer_synchronize() const BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((const_unique_lock_ptr<T,Lockable>(value_, mtx_, defer_lock)));
    }

    unique_lock_ptr<T,Lockable> try_to_synchronize() BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((unique_lock_ptr<T,Lockable>(value_, mtx_, try_to_lock)));
    }

    const_unique_lock_ptr<T,Lockable> try_to_synchronize() const BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((const_unique_lock_ptr<T,Lockable>(value_, mtx_, try_to_lock)));
    }

    unique_lock_ptr<T,Lockable> adopt_synchronize() BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((unique_lock_ptr<T,Lockable>(value_, mtx_, adopt_lock)));
    }

    const_unique_lock_ptr<T,Lockable> adopt_synchronize() const BOOST_NOEXCEPT
    {
      return BOOST_THREAD_MAKE_RV_REF((const_unique_lock_ptr<T,Lockable>(value_, mtx_, adopt_lock)));
    }


      explicit deref_value(synchronized_value& outer):
      lk_(outer.mtx_),value_(outer.value_)
      {}




      deref_value(BOOST_THREAD_RV_REF(deref_value) other):
      lk_(boost::move(BOOST_THREAD_RV(other).lk_)),value_(BOOST_THREAD_RV(other).value_)
      {}

      operator T&()
      {
        return value_;
      }


      deref_value& operator=(T const& newVal)
      {
        value_=newVal;
        return *this;
      }


      explicit const_deref_value(synchronized_value const& outer):
      lk_(outer.mtx_), value_(outer.value_)
      {}




      const_deref_value(BOOST_THREAD_RV_REF(const_deref_value) other):
      lk_(boost::move(BOOST_THREAD_RV(other).lk_)), value_(BOOST_THREAD_RV(other).value_)
      {}


      operator const T&()
      {
        return value_;
      }

    deref_value operator*()
    {
      return BOOST_THREAD_MAKE_RV_REF(deref_value(*this));
    }


    const_deref_value operator*() const
    {
      return BOOST_THREAD_MAKE_RV_REF(const_deref_value(*this));
    }

    template <typename OStream>
    void save(OStream& os) const
    {
      strict_lock<mutex_type> lk(mtx_);
      os << value_;
    }

    template <typename IStream>
    void load(IStream& is) const
    {
      strict_lock<mutex_type> lk(mtx_);
      is >> value_;
    }

    bool operator==(synchronized_value const& rhs)  const
    {
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);

      return value_ == rhs.value_;
    }

    bool operator<(synchronized_value const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);

      return value_ < rhs.value_;
    }

    bool operator>(synchronized_value const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);

      return value_ > rhs.value_;
    }

    bool operator<=(synchronized_value const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);

      return value_ <= rhs.value_;
    }

    bool operator>=(synchronized_value const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_, defer_lock);
      unique_lock<mutex_type> lk2(rhs.mtx_, defer_lock);
      lock(lk1,lk2);

      return value_ >= rhs.value_;
    }

    bool operator==(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ == rhs;
    }

    bool operator!=(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ != rhs;
    }

    bool operator<(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ < rhs;
    }

    bool operator<=(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ <= rhs;
    }

    bool operator>(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ > rhs;
    }

    bool operator>=(value_type const& rhs) const
    {
      unique_lock<mutex_type> lk1(mtx_);

      return value_ >= rhs;
    }

  template <typename T, typename L>
  inline void swap(synchronized_value<T,L> & lhs, synchronized_value<T,L> & rhs)
  {
    lhs.swap(rhs);
  }

  template <typename T, typename L>
  inline void swap(synchronized_value<T,L> & lhs, T & rhs)
  {
    lhs.swap(rhs);
  }

  template <typename T, typename L>
  inline void swap(T & lhs, synchronized_value<T,L> & rhs)
  {
    rhs.swap(lhs);
  }

  template <typename T, typename L>
  bool operator!=(synchronized_value<T,L> const&lhs, synchronized_value<T,L> const& rhs)
  {
    return ! (lhs==rhs);
  }


  template <typename T, typename L>
  bool operator==(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs==lhs;
  }

  template <typename T, typename L>
  bool operator!=(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs!=lhs;
  }

  template <typename T, typename L>
  bool operator<(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs>=lhs;
  }

  template <typename T, typename L>
  bool operator<=(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs>lhs;
  }

  template <typename T, typename L>
  bool operator>(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs<=lhs;
  }

  template <typename T, typename L>
  bool operator>=(T const& lhs, synchronized_value<T,L> const&rhs)
  {
    return rhs<lhs;
  }

  template <typename OStream, typename T, typename L>
  inline OStream& operator<<(OStream& os, synchronized_value<T,L> const& rhs)
  {
    rhs.save(os);
    return os;
  }

  template <typename IStream, typename T, typename L>
  inline IStream& operator>>(IStream& is, synchronized_value<T,L> const& rhs)
  {
    rhs.load(is);
    return is;
  }


    null_mutex() {}

    void lock()
    {
    }

    bool try_lock()
    {
      return true;
    }

    void unlock()
    {
    }

    template <typename Clock, typename Duration>
    bool try_lock_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_lock_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    void lock_shared()
    {
    }

    bool try_lock_shared()
    {
      return true;
    }

    void unlock_shared()
    {
    }

    template <typename Clock, typename Duration>
    bool try_lock_shared_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_lock_shared_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    void lock_upgrade()
    {
    }

    bool try_lock_upgrade()
    {
      return true;
    }

    void unlock_upgrade()
    {
    }

    template <typename Clock, typename Duration>
    bool try_lock_upgrade_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_lock_upgrade_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    bool try_unlock_shared_and_lock()
    {
      return true;
    }

    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    void unlock_and_lock_shared()
    {
    }

    bool try_unlock_shared_and_lock_upgrade()
    {
      return true;
    }

    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_upgrade_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_upgrade_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    void unlock_and_lock_upgrade()
    {
    }

    void unlock_upgrade_and_lock()
    {
    }

    bool try_unlock_upgrade_and_lock()
    {
      return true;
    }

    template <typename Clock, typename Duration>
    bool try_unlock_upgrade_and_lock_until(chrono::time_point<Clock, Duration> const &)
    {
      return true;
    }

    template <typename Rep, typename Period>
    bool try_unlock_upgrade_and_lock_for(chrono::duration<Rep, Period> const &)
    {
      return true;
    }

    void unlock_upgrade_and_lock_shared()
    {
    }
launch)


launch)


future_status)


future_status)



      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }


      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }

        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}

        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}

        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}

        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}

        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}

            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}

                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}


            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }

            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }

            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }

            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }

            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}

            virtual ~future_object_base()
            {}


            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }

            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }

            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }


            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }


            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }

            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }

            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }


            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }



            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }

            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }


            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }

            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }

            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }

            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }

            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }

            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }

            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }

            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }

            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }


            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }


            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }

            virtual void execute(boost::unique_lock<boost::mutex>&) {}


            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }


            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }


            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }


            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }


            static void cleanup(storage_type& storage)
            {
                storage=0;
            }


            static void init(storage_type& storage)
            {
                storage=true;
            }


            static void cleanup(storage_type& storage)
            {
                storage=false;
            }


            future_object():
                result(0)
            {}


            ~future_object()
            {}


            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }


            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }


            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }



            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }


            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }

            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


            future_object():
                result(0)
            {}


            ~future_object()
            {
            }


            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }


            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }



            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }


            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


            future_object()
            {}


            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }


            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }


            void get()
            {
                this->wait();
            }

            void get_sh()
            {
                wait();
            }

            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }

          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }


          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }


          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }

          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }


          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }


          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }

          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }


          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }


          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }

          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }


          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }

          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }


          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }

          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }


          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }


                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}


                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }


                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }

            future_waiter():
                future_count(0)
            {}


            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }


            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }


            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }


    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }


    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }


    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }


    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }


    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }


    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }


    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }


    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }


    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }


    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }


        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }



        basic_future(): future_() {}

        ~basic_future() {}


        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }

        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }

        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }

        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }


        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }


        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }


        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }


        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }


        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }



        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }


        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }

        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }

        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }


unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}


        ~BOOST_THREAD_FUTURE() {}
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        BOOST_THREAD_FUTURE& operator=(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT
        {
            this->base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }


        shared_future<R> share()
        {
          return shared_future<R>(::boost::move(*this));
        }


        void swap(BOOST_THREAD_FUTURE& other)
        {
            static_cast<base_type*>(this)->swap(other);
        }

        void set_async()
        {
          this->future_->set_async();
        }

        void set_deferred()
        {
          this->future_->set_deferred();
        }

        move_dest_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }
#ifdef BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
            future_ptr fut_=this->future_;
            this->future_.reset();
            return fut_->get();

#else
            return this->future_->get();
#endif
        }

        shared_future(future_ptr a_future):
          base_type(a_future)
        {}




        shared_future(shared_future const& other):
        base_type(other)
        {}
 shared_future()
        {}


        ~shared_future()
        {}


        shared_future& operator=(shared_future const& other)
        {
            shared_future(other).swap(*this);
            return *this;
        }

        shared_future(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
            BOOST_THREAD_RV(other).future_.reset();
        }

        shared_future(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }


        shared_future& operator=(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }

        shared_future& operator=(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            //shared_future(boost::move(other)).swap(*this);
            //this->future_.swap(BOOST_THREAD_RV(other).future_);
            //BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }


        void swap(shared_future& other) BOOST_NOEXCEPT
        {
            static_cast<base_type*>(this)->swap(other);
        }

        typename detail::future_object<R>::shared_future_get_result_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }

            return this->future_->get_sh();
        }

      template <typename R>
      inline basic_future<R>::basic_future(const shared_future<R>& other) BOOST_NOEXCEPT
      : future_(other.future_)
      {
      }


        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
          if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }



        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R>()),
#endif
            future_obtained(false)
        {}


        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }

        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }


        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        BOOST_THREAD_FUTURE& operator=(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT
        {
            this->base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }

        shared_future<R> share()
        {
          return shared_future<R>(::boost::move(*this));
        }

        void swap(BOOST_THREAD_FUTURE& other)
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_async()
        {
          this->future_->set_async();
        }
        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_deferred()
        {
          this->future_->set_deferred();
        }

        // retrieving the value
        move_dest_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }
#ifdef BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
            future_ptr fut_=this->future_;
            this->future_.reset();
            return fut_->get();

#else
            return this->future_->get();
#endif
        }


#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

//        template<typename F>
//        auto then(F&& func) -> BOOST_THREAD_FUTURE<decltype(func(*this))>;

//#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(RF(*func)(BOOST_THREAD_FUTURE&));
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(launch policy, RF(*func)(BOOST_THREAD_FUTURE&));
//#endif
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(BOOST_THREAD_FWD_REF(F) func);
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(launch policy, BOOST_THREAD_FWD_REF(F) func);
#endif
    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) BOOST_THREAD_FUTURE<T> BOOST_THREAD_DCL_MOVABLE_END

    template <typename R>
    class shared_future : public detail::basic_future<R>
    {

        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class detail::future_waiter;
        friend class promise<R>;

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task;// todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        shared_future(future_ptr a_future):
          base_type(a_future)
        {}

    public:
        BOOST_THREAD_MOVABLE(shared_future)

        shared_future(shared_future const& other):
        base_type(other)
        {}

        typedef future_state::state state;

        BOOST_CONSTEXPR shared_future()
        {}

        ~shared_future()
        {}

        shared_future& operator=(shared_future const& other)
        {
            shared_future(other).swap(*this);
            return *this;
        }
        shared_future(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        shared_future(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        shared_future& operator=(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }
        shared_future& operator=(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            //shared_future(boost::move(other)).swap(*this);
            //this->future_.swap(BOOST_THREAD_RV(other).future_);
            //BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }

        void swap(shared_future& other) BOOST_NOEXCEPT
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // retrieving the value
        typename detail::future_object<R>::shared_future_get_result_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }

            return this->future_->get_sh();
        }

    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) shared_future<T> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
      /// Copy construction from a shared_future
      template <typename R>
      inline basic_future<R>::basic_future(const shared_future<R>& other) BOOST_NOEXCEPT
      : future_(other.future_)
      {
      }
    }

    template <typename R>
    class promise
    {
        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
          if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R>(future_);
        }


        void set_value(typename detail::future_traits<R>::source_reference_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

        void set_value(typename detail::future_traits<R>::rvalue_source_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            future_->mark_finished_with_result_internal(boost::forward<R>(r), lock);
#else
            future_->mark_finished_with_result_internal(static_cast<typename detail::future_traits<R>::rvalue_source_type>(r), lock);
#endif
        }


        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        void set_value_at_thread_exit(const R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }


        void set_value_at_thread_exit(BOOST_THREAD_RV_REF(R) r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(boost::move(r));
        }

        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }


        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }


        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R&>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }



        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R&>()),
#endif
            future_obtained(false)
        {}


        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }

        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }


        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        BOOST_THREAD_FUTURE& operator=(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT
        {
            this->base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }

        shared_future<R> share()
        {
          return shared_future<R>(::boost::move(*this));
        }

        void swap(BOOST_THREAD_FUTURE& other)
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_async()
        {
          this->future_->set_async();
        }
        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_deferred()
        {
          this->future_->set_deferred();
        }

        // retrieving the value
        move_dest_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }
#ifdef BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
            future_ptr fut_=this->future_;
            this->future_.reset();
            return fut_->get();

#else
            return this->future_->get();
#endif
        }


#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

//        template<typename F>
//        auto then(F&& func) -> BOOST_THREAD_FUTURE<decltype(func(*this))>;

//#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(RF(*func)(BOOST_THREAD_FUTURE&));
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(launch policy, RF(*func)(BOOST_THREAD_FUTURE&));
//#endif
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(BOOST_THREAD_FWD_REF(F) func);
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(launch policy, BOOST_THREAD_FWD_REF(F) func);
#endif
    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) BOOST_THREAD_FUTURE<T> BOOST_THREAD_DCL_MOVABLE_END

    template <typename R>
    class shared_future : public detail::basic_future<R>
    {

        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class detail::future_waiter;
        friend class promise<R>;

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task;// todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        shared_future(future_ptr a_future):
          base_type(a_future)
        {}

    public:
        BOOST_THREAD_MOVABLE(shared_future)

        shared_future(shared_future const& other):
        base_type(other)
        {}

        typedef future_state::state state;

        BOOST_CONSTEXPR shared_future()
        {}

        ~shared_future()
        {}

        shared_future& operator=(shared_future const& other)
        {
            shared_future(other).swap(*this);
            return *this;
        }
        shared_future(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        shared_future(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        shared_future& operator=(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }
        shared_future& operator=(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            //shared_future(boost::move(other)).swap(*this);
            //this->future_.swap(BOOST_THREAD_RV(other).future_);
            //BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }

        void swap(shared_future& other) BOOST_NOEXCEPT
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // retrieving the value
        typename detail::future_object<R>::shared_future_get_result_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }

            return this->future_->get_sh();
        }

    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) shared_future<T> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
      /// Copy construction from a shared_future
      template <typename R>
      inline basic_future<R>::basic_future(const shared_future<R>& other) BOOST_NOEXCEPT
      : future_(other.future_)
      {
      }
    }

    template <typename R>
    class promise
    {
        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
          if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R>(future_);
        }

        void set_value(typename detail::future_traits<R>::source_reference_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

//         void set_value(R && r);
        void set_value(typename detail::future_traits<R>::rvalue_source_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            future_->mark_finished_with_result_internal(boost::forward<R>(r), lock);
#else
            future_->mark_finished_with_result_internal(static_cast<typename detail::future_traits<R>::rvalue_source_type>(r), lock);
#endif
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit(const R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }

        void set_value_at_thread_exit(BOOST_THREAD_RV_REF(R) r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(boost::move(r));
        }
        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };

    template <typename R>
    class promise<R&>
    {
        typedef boost::shared_ptr<detail::future_object<R&> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R&>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R&> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R&>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R&>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R&> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R&>(future_);
        }


        void set_value(R& r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }


        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        void set_value_at_thread_exit(R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }


        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }


        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }


        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<void>));
            }
#endif
        }



        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<void>),
#endif
            future_obtained(false)
        {}


        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
          // we need to release the future as shared_ptr doesn't implements move semantics
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }


        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }


        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        BOOST_THREAD_FUTURE& operator=(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT
        {
            this->base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }

        shared_future<R> share()
        {
          return shared_future<R>(::boost::move(*this));
        }

        void swap(BOOST_THREAD_FUTURE& other)
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_async()
        {
          this->future_->set_async();
        }
        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_deferred()
        {
          this->future_->set_deferred();
        }

        // retrieving the value
        move_dest_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }
#ifdef BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
            future_ptr fut_=this->future_;
            this->future_.reset();
            return fut_->get();

#else
            return this->future_->get();
#endif
        }


#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

//        template<typename F>
//        auto then(F&& func) -> BOOST_THREAD_FUTURE<decltype(func(*this))>;

//#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(RF(*func)(BOOST_THREAD_FUTURE&));
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(launch policy, RF(*func)(BOOST_THREAD_FUTURE&));
//#endif
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(BOOST_THREAD_FWD_REF(F) func);
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(launch policy, BOOST_THREAD_FWD_REF(F) func);
#endif
    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) BOOST_THREAD_FUTURE<T> BOOST_THREAD_DCL_MOVABLE_END

    template <typename R>
    class shared_future : public detail::basic_future<R>
    {

        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class detail::future_waiter;
        friend class promise<R>;

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task;// todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        shared_future(future_ptr a_future):
          base_type(a_future)
        {}

    public:
        BOOST_THREAD_MOVABLE(shared_future)

        shared_future(shared_future const& other):
        base_type(other)
        {}

        typedef future_state::state state;

        BOOST_CONSTEXPR shared_future()
        {}

        ~shared_future()
        {}

        shared_future& operator=(shared_future const& other)
        {
            shared_future(other).swap(*this);
            return *this;
        }
        shared_future(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        shared_future(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        shared_future& operator=(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }
        shared_future& operator=(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            //shared_future(boost::move(other)).swap(*this);
            //this->future_.swap(BOOST_THREAD_RV(other).future_);
            //BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }

        void swap(shared_future& other) BOOST_NOEXCEPT
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // retrieving the value
        typename detail::future_object<R>::shared_future_get_result_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }

            return this->future_->get_sh();
        }

    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) shared_future<T> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
      /// Copy construction from a shared_future
      template <typename R>
      inline basic_future<R>::basic_future(const shared_future<R>& other) BOOST_NOEXCEPT
      : future_(other.future_)
      {
      }
    }

    template <typename R>
    class promise
    {
        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
          if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R>(future_);
        }

        void set_value(typename detail::future_traits<R>::source_reference_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

//         void set_value(R && r);
        void set_value(typename detail::future_traits<R>::rvalue_source_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            future_->mark_finished_with_result_internal(boost::forward<R>(r), lock);
#else
            future_->mark_finished_with_result_internal(static_cast<typename detail::future_traits<R>::rvalue_source_type>(r), lock);
#endif
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit(const R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }

        void set_value_at_thread_exit(BOOST_THREAD_RV_REF(R) r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(boost::move(r));
        }
        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };

    template <typename R>
    class promise<R&>
    {
        typedef boost::shared_ptr<detail::future_object<R&> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R&>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R&> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R&>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R&>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R&> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R&>(future_);
        }

        void set_value(R& r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit(R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }

        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };
    template <>
    class promise<void>
    {
        typedef boost::shared_ptr<detail::future_object<void> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<void>));
            }
#endif
        }
    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<void> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<void>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<void>),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
          // we need to release the future as shared_ptr doesn't implements move semantics
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }

        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<void> get_future()
        {
            lazy_init();

            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if(future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<void>(future_);
        }


        void set_value()
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(lock);
        }


        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p,lock);
        }

        void set_value_at_thread_exit()
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit();
        }


        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }


        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }


            task_base():
                started(false)
            {}


            void reset()
            {
              started=false;
            }

            void run()
#endif
            {
                {
                    boost::lock_guard<boost::mutex> lk(this->mutex);
                    if(started)
                    {
                        boost::throw_exception(task_already_started());
                    }
                    started=true;
                }
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                do_run(boost::forward<ArgTypes>(args)...);
#else
                do_run();
#endif
            }

            void apply()
#endif
            {
                {
                    boost::lock_guard<boost::mutex> lk(this->mutex);
                    if(started)
                    {
                        boost::throw_exception(task_already_started());
                    }
                    started=true;
                }
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                do_apply(boost::forward<ArgTypes>(args)...);
#else
                do_apply();
#endif
            }


            void owner_destroyed()
            {
                boost::unique_lock<boost::mutex> lk(this->mutex);
                if(!started)
                {
                    started=true;
                    this->mark_exceptional_finish_internal(boost::copy_exception(boost::broken_promise()), lk);
                }
            }

            task_object(F const& f_):
                f(f_)
            {}

            task_object(BOOST_THREAD_RV_REF(F) f_):
              f(boost::move(f_))
            {}

            void do_apply()
            {
                try
                {
                    this->set_value_at_thread_exit(f());
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

            void do_run()
            {
                try
                {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                  R res((f()));
                  this->mark_finished_with_result(boost::move(res));
#else
                  this->mark_finished_with_result(f());
#endif
                  }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }

            task_object(F const& f_):
                f(f_)
            {}

            task_object(BOOST_THREAD_RV_REF(F) f_):
                f(boost::move(f_))
            {}

            void do_apply()
            {
                try
                {
                    this->set_value_at_thread_exit(f());
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

            void do_run()
            {
                try
                {
                  R& res((f()));
                  this->mark_finished_with_result(res);
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }

                task_object(R (*f_)()):
                    f(f_)
                {}

                void do_apply()
                {
                    try
                    {
                        R r((f()));
                        this->set_value_at_thread_exit(boost::move(r));
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->set_interrupted_at_thread_exit();
                    }
#endif
                    catch(...)
                    {
                        this->set_exception_at_thread_exit(current_exception());
                    }
                }

                void do_run()
                {
                    try
                    {
                        R res((f()));
                        this->mark_finished_with_result(boost::move(res));
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->mark_interrupted_finish();
                    }
#endif
                    catch(...)
                    {
                        this->mark_exceptional_finish();
                    }
                }

                task_object(R& (*f_)()):
                    f(f_)
                {}

                void do_apply()
                {
                    try
                    {
                      this->set_value_at_thread_exit(f());
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->set_interrupted_at_thread_exit();
                    }
#endif
                    catch(...)
                    {
                        this->set_exception_at_thread_exit(current_exception());
                    }
                }

                void do_run()
                {
                    try
                    {
                        this->mark_finished_with_result(f());
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->mark_interrupted_finish();
                    }
#endif
                    catch(...)
                    {
                        this->mark_exceptional_finish();
                    }
                }

            task_object(F const& f_):
                f(f_)
            {}

            task_object(BOOST_THREAD_RV_REF(F) f_):
                f(boost::move(f_))
            {}

            void do_apply()
            {
                try
                {
                    f();
#endif
                  this->set_value_at_thread_exit();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

            void do_run()
            {
                try
                {
                    f();
#endif
                    this->mark_finished_with_result();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }

            task_object(void (*f_)()):
                f(f_)
            {}

            void do_apply()
            {
                try
                {
                    f();
#endif
                    this->set_value_at_thread_exit();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

            void do_run()
            {
                try
                {
                  f();
#endif
                  this->mark_finished_with_result();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }




        packaged_task():
            future_obtained(false)
        {}

        explicit packaged_task(R(*f)())
        {
              typedef R(*FR)();
            typedef detail::task_object<FR,R> task_object_type;
            task= task_ptr(new task_object_type(f));
            future_obtained=false;
        }

        template <class F>
        explicit packaged_task(F const& f
            , typename disable_if<is_same<typename decay<F>::type, packaged_task>, dummy* >::type=0
            )
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
  #else
            typedef detail::task_object<F,R()> task_object_type;
  #endif
#else
            typedef detail::task_object<F,R> task_object_type;
#endif
            task = task_ptr(new task_object_type(f));
            future_obtained=false;
        }

        template <class F>
        explicit packaged_task(BOOST_THREAD_RV_REF(F) f)
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
            task = task_ptr(new task_object_type(boost::forward<F>(f)));
#else
            typedef detail::task_object<F,R()> task_object_type;
            task = task_ptr(new task_object_type(boost::move<F>(f))); // TODO forward
#endif
#else
            typedef detail::task_object<F,R> task_object_type;
            task = task_ptr(new task_object_type(boost::forward<F>(f)));
#endif
            future_obtained=false;

        }


        ~packaged_task()
        {
            if(task)
            {
                task->owner_destroyed();
            }
        }

        packaged_task(BOOST_THREAD_RV_REF(packaged_task) other) BOOST_NOEXCEPT :
            future_obtained(BOOST_THREAD_RV(other).future_obtained)
        {
            task.swap(BOOST_THREAD_RV(other).task);
            BOOST_THREAD_RV(other).future_obtained=false;
        }

        packaged_task& operator=(BOOST_THREAD_RV_REF(packaged_task) other) BOOST_NOEXCEPT
        {

            // todo use forward
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            packaged_task temp(boost::move(other));
#else
            packaged_task temp(static_cast<BOOST_THREAD_RV_REF(packaged_task)>(other));
#endif
            swap(temp);
            return *this;
        }


        void reset()
        {
            if (!valid())
                throw future_error(system::make_error_code(future_errc::no_state));
            task->reset();
            future_obtained=false;
        }


        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            task.swap(other.task);
            std::swap(future_obtained,other.future_obtained);
        }

        bool valid() const BOOST_NOEXCEPT
        {
          return task.get()!=0;
        }
unique_future
#endif

namespace boost
{

  //enum class launch
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(launch)
  {
      none = 0,
      async = 1,
      deferred = 2,
      any = async | deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(launch)

  //enum class future_status
  BOOST_SCOPED_ENUM_DECLARE_BEGIN(future_status)
  {
      ready,
      timeout,
      deferred
  }
  BOOST_SCOPED_ENUM_DECLARE_END(future_status)

  class BOOST_SYMBOL_VISIBLE future_error
      : public std::logic_error
  {
      system::error_code ec_;
  public:
      future_error(system::error_code ec)
      : logic_error(ec.message()),
        ec_(ec)
      {
      }

      const system::error_code& code() const BOOST_NOEXCEPT
      {
        return ec_;
      }
  };

    class BOOST_SYMBOL_VISIBLE future_uninitialized:
        public future_error
    {
    public:
        future_uninitialized() :
          future_error(system::make_error_code(future_errc::no_state))
        {}
    };
    class BOOST_SYMBOL_VISIBLE broken_promise:
        public future_error
    {
    public:
        broken_promise():
          future_error(system::make_error_code(future_errc::broken_promise))
        {}
    };
    class BOOST_SYMBOL_VISIBLE future_already_retrieved:
        public future_error
    {
    public:
        future_already_retrieved():
          future_error(system::make_error_code(future_errc::future_already_retrieved))
        {}
    };
    class BOOST_SYMBOL_VISIBLE promise_already_satisfied:
        public future_error
    {
    public:
        promise_already_satisfied():
          future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

    class BOOST_SYMBOL_VISIBLE task_already_started:
        public future_error
    {
    public:
        task_already_started():
        future_error(system::make_error_code(future_errc::promise_already_satisfied))
        {}
    };

        class BOOST_SYMBOL_VISIBLE task_moved:
            public future_error
        {
        public:
            task_moved():
              future_error(system::make_error_code(future_errc::no_state))
            {}
        };

            class promise_moved:
                public future_error
            {
            public:
                  promise_moved():
                  future_error(system::make_error_code(future_errc::no_state))
                {}
            };

    namespace future_state
    {
        enum state { uninitialized, waiting, ready, moved, deferred };
    }

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
      template<typename F, typename Rp, typename Fp>
      struct future_deferred_continuation;
      template<typename F, typename Rp, typename Fp>
      struct future_async_continuation;
#endif

        struct relocker
        {
            boost::unique_lock<boost::mutex>& lock_;
            bool  unlocked_;

            relocker(boost::unique_lock<boost::mutex>& lk):
                lock_(lk)
            {
                lock_.unlock();
                unlocked_=true;
            }
            ~relocker()
            {
              if (unlocked_) {
                lock_.lock();
              }
            }
            void lock() {
              if (unlocked_) {
                lock_.lock();
                unlocked_=false;
              }
            }
        private:
            relocker& operator=(relocker const&);
        };

        struct future_object_base : enable_shared_from_this<future_object_base>
        {

            boost::exception_ptr exception;
            bool done;
            bool is_deferred_;
            launch policy_;
            bool is_constructed;
            boost::mutex mutex;
            boost::condition_variable waiters;
            typedef std::list<boost::condition_variable_any*> waiter_list;
            waiter_list external_waiters;
            boost::function<void()> callback;
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            bool thread_was_interrupted;
//#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            typedef shared_ptr<future_object_base> continuation_ptr_type;
#else
            typedef shared_ptr<void> continuation_ptr_type;
#endif
            continuation_ptr_type continuation_ptr;


//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            virtual void launch_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
//#endif
            future_object_base():
                done(false),
                is_deferred_(false),
                policy_(launch::none),
                is_constructed(false)

            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              , thread_was_interrupted(false)
//#endif
            // This declaration should be only included conditinally, but are included to maintain the same layout.
//#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
               , continuation_ptr()
//#endif
            {}
            virtual ~future_object_base()
            {}

            void set_deferred()
            {
              is_deferred_ = true;
              set_launch_policy(launch::deferred);
            }
            void set_async()
            {
              is_deferred_ = false;
              set_launch_policy(launch::async);
            }
            void set_launch_policy(launch policy)
            {
              policy_ = policy;
            }

            waiter_list::iterator register_external_waiter(boost::condition_variable_any& cv)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                do_callback(lock);
                return external_waiters.insert(external_waiters.end(),&cv);
            }

            void remove_external_waiter(waiter_list::iterator it)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                external_waiters.erase(it);
            }

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void do_continuation(boost::unique_lock<boost::mutex>& lock)
            {
                if (continuation_ptr) {
                  continuation_ptr->launch_continuation(lock);
                  if (! lock.owns_lock())
                    lock.lock();
                  continuation_ptr.reset();
                }
            }
#else
            void do_continuation(boost::unique_lock<boost::mutex>&)
            {
            }
#endif
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
            void set_continuation_ptr(continuation_ptr_type continuation, boost::unique_lock<boost::mutex>& lock)
            {
              continuation_ptr= continuation;
              if (done) {
                do_continuation(lock);
              }
            }
#endif
            void mark_finished_internal(boost::unique_lock<boost::mutex>& lock)
            {
                done=true;
                waiters.notify_all();
                for(waiter_list::const_iterator it=external_waiters.begin(),
                        end=external_waiters.end();it!=end;++it)
                {
                    (*it)->notify_all();
                }
                do_continuation(lock);
            }
            void make_ready()
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              mark_finished_internal(lock);
            }

            void do_callback(boost::unique_lock<boost::mutex>& lock)
            {
                if(callback && !done)
                {
                    boost::function<void()> local_callback=callback;
                    relocker relock(lock);
                    local_callback();
                }
            }


            void wait_internal(boost::unique_lock<boost::mutex> &lock, bool rethrow=true)
            {
              do_callback(lock);
              //if (!done) // fixme why this doesn't work?
              {
                if (is_deferred_)
                {
                  is_deferred_=false;
                  execute(lock);
                  //lock.unlock();
                }
                else
                {
                  while(!done)
                  {
                      waiters.wait(lock);
                  }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                  if(rethrow && thread_was_interrupted)
                  {
                      throw boost::thread_interrupted();
                  }
#endif
                  if(rethrow && exception)
                  {
                      boost::rethrow_exception(exception);
                  }
                }
              }
            }
            void wait(bool rethrow=true)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                wait_internal(lock, rethrow);
            }

#if defined BOOST_THREAD_USES_DATETIME
            bool timed_wait_until(boost::system_time const& target_time)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                if (is_deferred_)
                    return false;

                do_callback(lock);
                while(!done)
                {
                    bool const success=waiters.timed_wait(lock,target_time);
                    if(!success && !done)
                    {
                        return false;
                    }
                }
                return true;
            }
#endif
#ifdef BOOST_THREAD_USES_CHRONO

            template <class Clock, class Duration>
            future_status
            wait_until(const chrono::time_point<Clock, Duration>& abs_time)
            {
              boost::unique_lock<boost::mutex> lock(mutex);
              if (is_deferred_)
                  return future_status::deferred;
              do_callback(lock);
              while(!done)
              {
                  cv_status const st=waiters.wait_until(lock,abs_time);
                  if(st==cv_status::timeout && !done)
                  {
                    return future_status::timeout;
                  }
              }
              return future_status::ready;
            }
#endif
            void mark_exceptional_finish_internal(boost::exception_ptr const& e, boost::unique_lock<boost::mutex>& lock)
            {
                exception=e;
                mark_finished_internal(lock);
            }
            void mark_exceptional_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_exceptional_finish_internal(boost::current_exception(), lock);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            void mark_interrupted_finish()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                thread_was_interrupted=true;
                mark_finished_internal(lock);
            }
            void set_interrupted_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(mutex);
              thread_was_interrupted=true;
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
#endif
            void set_exception_at_thread_exit(exception_ptr e)
            {
              unique_lock<boost::mutex> lk(mutex);
              if (has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              exception=e;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            bool has_value()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_value(unique_lock<boost::mutex>& )
            {
                return done && !(exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                );
            }
            bool has_exception()
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool has_exception(unique_lock<boost::mutex>&)
            {
                return done && (exception
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    || thread_was_interrupted
#endif
                    );
            }
            bool is_deferred()  const BOOST_NOEXCEPT {
                return is_deferred_;
            }

            launch launch_policy() const BOOST_NOEXCEPT
            {
                return policy_;
            }

            template<typename F,typename U>
            void set_wait_callback(F f,U* u)
            {
                boost::lock_guard<boost::mutex> lock(mutex);
                callback=boost::bind(f,boost::ref(*u));
            }
            virtual void execute(boost::unique_lock<boost::mutex>&) {}

        private:
            future_object_base(future_object_base const&);
            future_object_base& operator=(future_object_base const&);
        };

        template<typename T>
        struct future_traits
        {
          typedef boost::scoped_ptr<T> storage_type;
          struct dummy;
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
          typedef T const& source_reference_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,dummy&,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          //typedef typename boost::mpl::if_<boost::is_fundamental<T>,T,BOOST_THREAD_RV_REF(T)>::type move_dest_type;
          typedef T move_dest_type;
#elif defined BOOST_THREAD_USES_MOVE
          typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,T&>::type source_reference_type;
          //typedef typename boost::mpl::if_c<boost::is_fundamental<T>::value,T,BOOST_THREAD_RV_REF(T)>::type rvalue_source_type;
          //typedef typename boost::mpl::if_c<boost::enable_move_utility_emulation<T>::value,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
          typedef BOOST_THREAD_RV_REF(T) rvalue_source_type;
          typedef T move_dest_type;
#else
          typedef T& source_reference_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T const&>::type rvalue_source_type;
          typedef typename boost::mpl::if_<boost::thread_detail::is_convertible<T&,BOOST_THREAD_RV_REF(T) >,BOOST_THREAD_RV_REF(T),T>::type move_dest_type;
#endif


            typedef const T& shared_future_get_result_type;

            static void init(storage_type& storage,source_reference_type t)
            {
                storage.reset(new T(t));
            }

            static void init(storage_type& storage,rvalue_source_type t)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
              storage.reset(new T(boost::forward<T>(t)));
#else
              storage.reset(new T(static_cast<rvalue_source_type>(t)));
#endif
            }

            static void cleanup(storage_type& storage)
            {
                storage.reset();
            }
        };

        template<typename T>
        struct future_traits<T&>
        {
            typedef T* storage_type;
            typedef T& source_reference_type;
            //struct rvalue_source_type
            //{};
            typedef T& move_dest_type;
            typedef T& shared_future_get_result_type;

            static void init(storage_type& storage,T& t)
            {
                storage=&t;
            }

            static void cleanup(storage_type& storage)
            {
                storage=0;
            }
        };

        template<>
        struct future_traits<void>
        {
            typedef bool storage_type;
            typedef void move_dest_type;
            typedef void shared_future_get_result_type;

            static void init(storage_type& storage)
            {
                storage=true;
            }

            static void cleanup(storage_type& storage)
            {
                storage=false;
            }

        };

        // Used to create stand-alone futures
        template<typename T>
        struct future_object:
            detail::future_object_base
        {
            typedef typename future_traits<T>::storage_type storage_type;
            typedef typename future_traits<T>::source_reference_type source_reference_type;
            typedef typename future_traits<T>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T>::move_dest_type move_dest_type;
            typedef typename future_traits<T>::shared_future_get_result_type shared_future_get_result_type;

            storage_type result;

            future_object():
                result(0)
            {}

            ~future_object()
            {}

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                future_traits<T>::init(result,result_);
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
            {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                future_traits<T>::init(result,boost::forward<T>(result_));
#else
                future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
#endif
                this->mark_finished_internal(lock);
            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                this->mark_finished_with_result_internal(result_, lock);
            }

            void mark_finished_with_result(rvalue_source_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);

#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                mark_finished_with_result_internal(boost::forward<T>(result_), lock);
#else
                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
#endif
            }


            virtual move_dest_type get()
            {
                wait();
                return boost::move(*result);
            }

            shared_future_get_result_type get_sh()
            {
                wait();
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }


            //void set_value_at_thread_exit(const T & result_)
            void set_value_at_thread_exit(source_reference_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
              //future_traits<T>::init(result,result_);
              result.reset(new T(result_));

              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
            //void set_value_at_thread_exit(BOOST_THREAD_RV_REF(T) result_)
            void set_value_at_thread_exit(rvalue_source_type result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              result.reset(new T(boost::move(result_)));
              //future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<typename T>
        struct future_object<T&>:
            detail::future_object_base
        {
            typedef typename future_traits<T&>::storage_type storage_type;
            typedef typename future_traits<T&>::source_reference_type source_reference_type;
            //typedef typename future_traits<T&>::rvalue_source_type rvalue_source_type;
            typedef typename future_traits<T&>::move_dest_type move_dest_type;
            typedef typename future_traits<T&>::shared_future_get_result_type shared_future_get_result_type;

            T* result;

            future_object():
                result(0)
            {}

            ~future_object()
            {
            }

            void mark_finished_with_result_internal(source_reference_type result_, boost::unique_lock<boost::mutex>& lock)
            {
                //future_traits<T>::init(result,result_);
                result= &result_;
                mark_finished_internal(lock);
            }

//            void mark_finished_with_result_internal(rvalue_source_type result_, boost::unique_lock<boost::mutex>& lock)
//            {
//                future_traits<T&>::init(result,static_cast<rvalue_source_type>(result_));
//                mark_finished_internal(lock);
//            }

            void mark_finished_with_result(source_reference_type result_)
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(result_, lock);
            }

//            void mark_finished_with_result(rvalue_source_type result_)
//            {
//                boost::unique_lock<boost::mutex> lock(mutex);
//                mark_finished_with_result_internal(static_cast<rvalue_source_type>(result_), lock);
//            }


            T& get()
            {
                wait();
                //return static_cast<T&>(*result);
                return *result;
            }

            T& get_sh()
            {
                wait();
                //return static_cast<shared_future_get_result_type>(*result);
                return *result;
            }

            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }

            void set_value_at_thread_exit(T& result_)
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
                  throw_exception(promise_already_satisfied());
              //future_traits<T>::init(result,result_);
              result= &result_;
              this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
//            void set_value_at_thread_exit(rvalue_source_type result_)
//            {
//              unique_lock<boost::mutex> lk(this->mutex);
//              if (this->has_value())
//                  throw_exception(promise_already_satisfied());
//              future_traits<T>::init(result,static_cast<rvalue_source_type>(result_));
//              this->is_constructed = true;
//              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
//            }


        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        template<>
        struct future_object<void>:
            detail::future_object_base
        {
          typedef void shared_future_get_result_type;

            future_object()
            {}

            void mark_finished_with_result_internal(boost::unique_lock<boost::mutex>& lock)
            {
                mark_finished_internal(lock);
            }

            void mark_finished_with_result()
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                mark_finished_with_result_internal(lock);
            }

            void get()
            {
                this->wait();
            }
            void get_sh()
            {
                wait();
            }
            // todo move this to detail::future_object_base
            future_state::state get_state()
            {
                boost::lock_guard<boost::mutex> guard(mutex);
                if(!done)
                {
                    return future_state::waiting;
                }
                else
                {
                    return future_state::ready;
                }
            }
            void set_value_at_thread_exit()
            {
              unique_lock<boost::mutex> lk(this->mutex);
              if (this->has_value(lk))
              {
                  throw_exception(promise_already_satisfied());
              }
             this->is_constructed = true;
              get_current_thread_data()->make_ready_at_thread_exit(shared_from_this());
            }
        private:
            future_object(future_object const&);
            future_object& operator=(future_object const&);
        };

        /////////////////////////
        /// future_async_object
        /////////////////////////
        template<typename Rp, typename Fp>
        struct future_async_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              //return boost::move<Rp>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Fp>
        struct future_async_object<void, Fp>: public future_object<void>
        {
          typedef future_object<void> base_type;
          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              f();
              that->mark_finished_with_result();
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        template<typename Rp, typename Fp>
        struct future_async_object<Rp&, Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          typedef typename base_type::move_dest_type move_dest_type;

          boost::thread thr_;

        public:
          explicit future_async_object(BOOST_THREAD_FWD_REF(Fp) f) :
            thr_(&future_async_object::run, this, boost::forward<Fp>(f))
          {
            this->set_async();
          }

          ~future_async_object()
          {
            if (thr_.joinable()) thr_.join();
          }

          move_dest_type get()
          {
              if (thr_.joinable()) thr_.join();
              // fixme Is the lock needed during the whole scope?
              //this->wait();
              boost::unique_lock<boost::mutex> lock(this->mutex);
              this->wait_internal(lock);

              //return static_cast<move_dest_type>(*(this->result));
              return boost::move(*(this->result));
          }
          static void run(future_async_object* that, BOOST_THREAD_FWD_REF(Fp) f)
          {
            try
            {
              that->mark_finished_with_result(f());
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            catch(thread_interrupted& )
            {
              that->mark_interrupted_finish();
            }
#endif
            catch(...)
            {
              that->mark_exceptional_finish();
            }
          }
        };

        //////////////////////////
        /// future_deferred_object
        //////////////////////////
        template<typename Rp, typename Fp>
        struct future_deferred_object: future_object<Rp>
        {
          typedef future_object<Rp> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };
        template<typename Rp, typename Fp>
        struct future_deferred_object<Rp&,Fp>: future_object<Rp&>
        {
          typedef future_object<Rp&> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              this->mark_finished_with_result_internal(func_(), lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

        template<typename Fp>
        struct future_deferred_object<void,Fp>: future_object<void>
        {
          typedef future_object<void> base_type;
          Fp func_;

        public:
          explicit future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
          : func_(boost::forward<Fp>(f))
          {
            this->set_deferred();
          }

          virtual void execute(boost::unique_lock<boost::mutex>& lck) {
            try
            {
              func_();
              this->mark_finished_with_result_internal(lck);
            }
            catch (...)
            {
              this->mark_exceptional_finish_internal(current_exception(), lck);
            }
          }
        };

//        template<typename T, typename Allocator>
//        struct future_object_alloc: public future_object<T>
//        {
//          typedef future_object<T> base;
//          Allocator alloc_;
//
//        public:
//          explicit future_object_alloc(const Allocator& a)
//              : alloc_(a) {}
//
//        };
        class future_waiter
        {
            struct registered_waiter;
            typedef std::vector<int>::size_type count_type;

            struct registered_waiter
            {
                boost::shared_ptr<detail::future_object_base> future_;
                detail::future_object_base::waiter_list::iterator wait_iterator;
                count_type index;

                registered_waiter(boost::shared_ptr<detail::future_object_base> const& a_future,
                                  detail::future_object_base::waiter_list::iterator wait_iterator_,
                                  count_type index_):
                    future_(a_future),wait_iterator(wait_iterator_),index(index_)
                {}
            };

            struct all_futures_lock
            {
#ifdef _MANAGED
                   typedef std::ptrdiff_t count_type_portable;
#else
                   typedef count_type count_type_portable;
#endif
                   count_type_portable count;
                   boost::scoped_array<boost::unique_lock<boost::mutex> > locks;

                all_futures_lock(std::vector<registered_waiter>& futures):
                    count(futures.size()),locks(new boost::unique_lock<boost::mutex>[count])
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
#if defined __DECCXX || defined __SUNPRO_CC || defined __hpux
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex).move();
#else
                        locks[i]=boost::unique_lock<boost::mutex>(futures[i].future_->mutex); // TODO shouldn't be moved explicitly
#endif
                    }
                }

                void lock()
                {
                    boost::lock(locks.get(),locks.get()+count);
                }

                void unlock()
                {
                    for(count_type_portable i=0;i<count;++i)
                    {
                        locks[i].unlock();
                    }
                }
            };

            boost::condition_variable_any cv;
            std::vector<registered_waiter> futures;
            count_type future_count;

        public:
            future_waiter():
                future_count(0)
            {}

            template<typename F>
            void add(F& f)
            {
                if(f.future_)
                {
                    futures.push_back(registered_waiter(f.future_,f.future_->register_external_waiter(cv),future_count));
                }
                ++future_count;
            }

            count_type wait()
            {
                all_futures_lock lk(futures);
                for(;;)
                {
                    for(count_type i=0;i<futures.size();++i)
                    {
                        if(futures[i].future_->done)
                        {
                            return futures[i].index;
                        }
                    }
                    cv.wait(lk);
                }
            }

            ~future_waiter()
            {
                for(count_type i=0;i<futures.size();++i)
                {
                    futures[i].future_->remove_external_waiter(futures[i].wait_iterator);
                }
            }

        };

    }

    template <typename R>
    class BOOST_THREAD_FUTURE;

    template <typename R>
    class shared_future;

    template<typename T>
    struct is_future_type
    {
        BOOST_STATIC_CONSTANT(bool, value=false);
    };

    template<typename T>
    struct is_future_type<BOOST_THREAD_FUTURE<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename T>
    struct is_future_type<shared_future<T> >
    {
        BOOST_STATIC_CONSTANT(bool, value=true);
    };

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,void>::type wait_for_all(Iterator begin,Iterator end)
    {
        for(Iterator current=begin;current!=end;++current)
        {
            current->wait();
        }
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,void>::type wait_for_all(F1& f1,F2& f2)
    {
        f1.wait();
        f2.wait();
    }

    template<typename F1,typename F2,typename F3>
    void wait_for_all(F1& f1,F2& f2,F3& f3)
    {
        f1.wait();
        f2.wait();
        f3.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    void wait_for_all(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        f1.wait();
        f2.wait();
        f3.wait();
        f4.wait();
        f5.wait();
    }

    template<typename Iterator>
    typename boost::disable_if<is_future_type<Iterator>,Iterator>::type wait_for_any(Iterator begin,Iterator end)
    {
        if(begin==end)
            return end;

        detail::future_waiter waiter;
        for(Iterator current=begin;current!=end;++current)
        {
            waiter.add(*current);
        }
        return boost::next(begin,waiter.wait());
    }

    template<typename F1,typename F2>
    typename boost::enable_if<is_future_type<F1>,unsigned>::type wait_for_any(F1& f1,F2& f2)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        return waiter.wait();
    }

    template<typename F1,typename F2,typename F3,typename F4,typename F5>
    unsigned wait_for_any(F1& f1,F2& f2,F3& f3,F4& f4,F5& f5)
    {
        detail::future_waiter waiter;
        waiter.add(f1);
        waiter.add(f2);
        waiter.add(f3);
        waiter.add(f4);
        waiter.add(f5);
        return waiter.wait();
    }

    template <typename R>
    class promise;

    template <typename R>
    class packaged_task;

    namespace detail
    {
      /// Common implementation for all the futures independently of the return type
      class base_future
      {
        //BOOST_THREAD_MOVABLE(base_future)

      };
      /// Common implementation for future and shared_future.
      template <typename R>
      class basic_future : public base_future
      {
      protected:

        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;

        basic_future(future_ptr a_future):
          future_(a_future)
        {
        }
        // Copy construction from a shared_future
        explicit basic_future(const shared_future<R>&) BOOST_NOEXCEPT;

      public:
        typedef future_state::state state;

        BOOST_THREAD_MOVABLE(basic_future)
        basic_future(): future_() {}
        ~basic_future() {}

        basic_future(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT:
        future_(BOOST_THREAD_RV(other).future_)
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        basic_future& operator=(BOOST_THREAD_RV_REF(basic_future) other) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(other).future_;
            BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }
        void swap(basic_future& that) BOOST_NOEXCEPT
        {
          future_.swap(that.future_);
        }
        // functions to check state, and wait for ready
        state get_state() const BOOST_NOEXCEPT
        {
            if(!future_)
            {
                return future_state::uninitialized;
            }
            return future_->get_state();
        }

        bool is_ready() const BOOST_NOEXCEPT
        {
            return get_state()==future_state::ready;
        }

        bool has_exception() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_exception();
        }

        bool has_value() const BOOST_NOEXCEPT
        {
            return future_ && future_->has_value();
        }

        launch launch_policy() const BOOST_NOEXCEPT
        {
            if ( future_ ) return future_->launch_policy();
            else return launch(launch::none);
        }

        bool valid() const BOOST_NOEXCEPT
        {
            return future_ != 0;
        }


        void wait() const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            future_->wait(false);
        }

#if defined BOOST_THREAD_USES_DATETIME
        template<typename Duration>
        bool timed_wait(Duration const& rel_time) const
        {
            return timed_wait_until(boost::get_system_time()+rel_time);
        }

        bool timed_wait_until(boost::system_time const& abs_time) const
        {
            if(!future_)
            {
                boost::throw_exception(future_uninitialized());
            }
            return future_->timed_wait_until(abs_time);
        }
#endif
#ifdef BOOST_THREAD_USES_CHRONO
        template <class Rep, class Period>
        future_status
        wait_for(const chrono::duration<Rep, Period>& rel_time) const
        {
          return wait_until(chrono::steady_clock::now() + rel_time);

        }
        template <class Clock, class Duration>
        future_status
        wait_until(const chrono::time_point<Clock, Duration>& abs_time) const
        {
          if(!future_)
          {
              boost::throw_exception(future_uninitialized());
          }
          return future_->wait_until(abs_time);
        }
#endif

      };

    } // detail
    BOOST_THREAD_DCL_MOVABLE_BEG(R) detail::basic_future<R> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if (!defined _MSC_VER || _MSC_VER >= 1400) // _MSC_VER == 1400 on MSVC 2005
        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);
#endif // #if (!defined _MSC_VER || _MSC_VER >= 1400)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        BOOST_THREAD_FUTURE<Rp>
        make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

    }

    template <typename R>
    class BOOST_THREAD_FUTURE : public detail::basic_future<R>
    {
    private:
        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class shared_future<R>;
        friend class promise<R>;
#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <typename, typename, typename>
        friend struct detail::future_async_continuation;
        template <typename, typename, typename>
        friend struct detail::future_deferred_continuation;
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task; // todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        friend class detail::future_waiter;

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f);

        template <class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f);

#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_async_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);

        template <class F, class Rp, class Fp>
        friend BOOST_THREAD_FUTURE<Rp>
        detail::make_future_deferred_continuation(boost::unique_lock<boost::mutex> &lock, F& f, BOOST_THREAD_FWD_REF(Fp) c);
#endif

        typedef typename detail::future_traits<R>::move_dest_type move_dest_type;

        BOOST_THREAD_FUTURE(future_ptr a_future):
          base_type(a_future)
        {
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(BOOST_THREAD_FUTURE)
        typedef future_state::state state;

        BOOST_CONSTEXPR BOOST_THREAD_FUTURE() {}

        ~BOOST_THREAD_FUTURE() {}

        BOOST_THREAD_FUTURE(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT:
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        BOOST_THREAD_FUTURE& operator=(BOOST_THREAD_RV_REF(BOOST_THREAD_FUTURE) other) BOOST_NOEXCEPT
        {
            this->base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }

        shared_future<R> share()
        {
          return shared_future<R>(::boost::move(*this));
        }

        void swap(BOOST_THREAD_FUTURE& other)
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_async()
        {
          this->future_->set_async();
        }
        // todo this functioˆn must be private and friendship provided to the internal users.
        void set_deferred()
        {
          this->future_->set_deferred();
        }

        // retrieving the value
        move_dest_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }
#ifdef BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
            future_ptr fut_=this->future_;
            this->future_.reset();
            return fut_->get();

#else
            return this->future_->get();
#endif
        }


#if defined BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

//        template<typename F>
//        auto then(F&& func) -> BOOST_THREAD_FUTURE<decltype(func(*this))>;

//#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(RF(*func)(BOOST_THREAD_FUTURE&));
//        template<typename RF>
//        inline BOOST_THREAD_FUTURE<RF> then(launch policy, RF(*func)(BOOST_THREAD_FUTURE&));
//#endif
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(BOOST_THREAD_FWD_REF(F) func);
        template<typename F>
        inline BOOST_THREAD_FUTURE<typename boost::result_of<F(BOOST_THREAD_FUTURE&)>::type>
        then(launch policy, BOOST_THREAD_FWD_REF(F) func);
#endif
    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) BOOST_THREAD_FUTURE<T> BOOST_THREAD_DCL_MOVABLE_END

    template <typename R>
    class shared_future : public detail::basic_future<R>
    {

        typedef detail::basic_future<R> base_type;
        typedef typename base_type::future_ptr future_ptr;

        friend class detail::future_waiter;
        friend class promise<R>;

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template <class> friend class packaged_task;// todo check if this works in windows
#else
        friend class packaged_task<R>;
#endif
        shared_future(future_ptr a_future):
          base_type(a_future)
        {}

    public:
        BOOST_THREAD_MOVABLE(shared_future)

        shared_future(shared_future const& other):
        base_type(other)
        {}

        typedef future_state::state state;

        BOOST_CONSTEXPR shared_future()
        {}

        ~shared_future()
        {}

        shared_future& operator=(shared_future const& other)
        {
            shared_future(other).swap(*this);
            return *this;
        }
        shared_future(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
            BOOST_THREAD_RV(other).future_.reset();
        }
        shared_future(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT :
        base_type(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))))
        {
        }

        shared_future& operator=(BOOST_THREAD_RV_REF(shared_future) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            return *this;
        }
        shared_future& operator=(BOOST_THREAD_RV_REF( BOOST_THREAD_FUTURE<R> ) other) BOOST_NOEXCEPT
        {
            base_type::operator=(boost::move(static_cast<base_type&>(BOOST_THREAD_RV(other))));
            //shared_future(boost::move(other)).swap(*this);
            //this->future_.swap(BOOST_THREAD_RV(other).future_);
            //BOOST_THREAD_RV(other).future_.reset();
            return *this;
        }

        void swap(shared_future& other) BOOST_NOEXCEPT
        {
            static_cast<base_type*>(this)->swap(other);
        }

        // retrieving the value
        typename detail::future_object<R>::shared_future_get_result_type get()
        {
            if(!this->future_)
            {
                boost::throw_exception(future_uninitialized());
            }

            return this->future_->get_sh();
        }

    };

    BOOST_THREAD_DCL_MOVABLE_BEG(T) shared_future<T> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
      /// Copy construction from a shared_future
      template <typename R>
      inline basic_future<R>::basic_future(const shared_future<R>& other) BOOST_NOEXCEPT
      : future_(other.future_)
      {
      }
    }

    template <typename R>
    class promise
    {
        typedef boost::shared_ptr<detail::future_object<R> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
          if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R>(future_);
        }

        void set_value(typename detail::future_traits<R>::source_reference_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

//         void set_value(R && r);
        void set_value(typename detail::future_traits<R>::rvalue_source_type r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            future_->mark_finished_with_result_internal(boost::forward<R>(r), lock);
#else
            future_->mark_finished_with_result_internal(static_cast<typename detail::future_traits<R>::rvalue_source_type>(r), lock);
#endif
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit(const R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }

        void set_value_at_thread_exit(BOOST_THREAD_RV_REF(R) r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(boost::move(r));
        }
        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };

    template <typename R>
    class promise<R&>
    {
        typedef boost::shared_ptr<detail::future_object<R&> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
#include <boost/detail/atomic_undef_macros.hpp>
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<R&>));
            }
#include <boost/detail/atomic_redef_macros.hpp>
#endif
        }

    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)
#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<R&> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<R&>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<R&>()),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }
        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<R&> get_future()
        {
            lazy_init();
            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if (future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<R&>(future_);
        }

        void set_value(R& r)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(r, lock);
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p, lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit(R& r)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit(r);
        }

        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };
    template <>
    class promise<void>
    {
        typedef boost::shared_ptr<detail::future_object<void> > future_ptr;

        future_ptr future_;
        bool future_obtained;

        void lazy_init()
        {
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            if(!atomic_load(&future_))
            {
                future_ptr blank;
                atomic_compare_exchange(&future_,&blank,future_ptr(new detail::future_object<void>));
            }
#endif
        }
    public:
        BOOST_THREAD_MOVABLE_ONLY(promise)

#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
        template <class Allocator>
        promise(boost::allocator_arg_t, Allocator a)
        {
          typedef typename Allocator::template rebind<detail::future_object<void> >::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          future_ = future_ptr(::new(a2.allocate(1)) detail::future_object<void>(), D(a2, 1) );
          future_obtained = false;
        }
#endif
        promise():
#if defined BOOST_THREAD_PROVIDES_PROMISE_LAZY
            future_(),
#else
            future_(new detail::future_object<void>),
#endif
            future_obtained(false)
        {}

        ~promise()
        {
            if(future_)
            {
                boost::unique_lock<boost::mutex> lock(future_->mutex);

                if(!future_->done && !future_->is_constructed)
                {
                    future_->mark_exceptional_finish_internal(boost::copy_exception(broken_promise()), lock);
                }
            }
        }

        // Assignment
        promise(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT :
            future_(BOOST_THREAD_RV(rhs).future_),future_obtained(BOOST_THREAD_RV(rhs).future_obtained)
        {
          // we need to release the future as shared_ptr doesn't implements move semantics
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
        }

        promise & operator=(BOOST_THREAD_RV_REF(promise) rhs) BOOST_NOEXCEPT
        {
            future_=BOOST_THREAD_RV(rhs).future_;
            future_obtained=BOOST_THREAD_RV(rhs).future_obtained;
            BOOST_THREAD_RV(rhs).future_.reset();
            BOOST_THREAD_RV(rhs).future_obtained=false;
            return *this;
        }

        void swap(promise& other)
        {
            future_.swap(other.future_);
            std::swap(future_obtained,other.future_obtained);
        }

        // Result retrieval
        BOOST_THREAD_FUTURE<void> get_future()
        {
            lazy_init();

            if (future_.get()==0)
            {
                boost::throw_exception(promise_moved());
            }
            if(future_obtained)
            {
                boost::throw_exception(future_already_retrieved());
            }
            future_obtained=true;
            return BOOST_THREAD_FUTURE<void>(future_);
        }

        void set_value()
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_finished_with_result_internal(lock);
        }

        void set_exception(boost::exception_ptr p)
        {
            lazy_init();
            boost::unique_lock<boost::mutex> lock(future_->mutex);
            if(future_->done)
            {
                boost::throw_exception(promise_already_satisfied());
            }
            future_->mark_exceptional_finish_internal(p,lock);
        }

        // setting the result with deferred notification
        void set_value_at_thread_exit()
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_value_at_thread_exit();
        }

        void set_exception_at_thread_exit(exception_ptr e)
        {
          if (future_.get()==0)
          {
              boost::throw_exception(promise_moved());
          }
          future_->set_exception_at_thread_exit(e);
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            lazy_init();
            future_->set_wait_callback(f,this);
        }

    };

#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
    namespace container
    {
      template <class R, class Alloc>
      struct uses_allocator<promise<R> , Alloc> : true_type
      {
      };
    }
#endif

    BOOST_THREAD_DCL_MOVABLE_BEG(T) promise<T> BOOST_THREAD_DCL_MOVABLE_END

    namespace detail
    {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
      template<typename R>
      struct task_base;
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
      template<typename R, typename ...ArgTypes>
      struct task_base<R(ArgTypes...)>:
#else
      template<typename R>
      struct task_base<R()>:
#endif
#else
      template<typename R>
      struct task_base:
#endif
            detail::future_object<R>
        {
            bool started;

            task_base():
                started(false)
            {}

            void reset()
            {
              started=false;
            }
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            virtual void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)=0;
            void run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
#else
            virtual void do_run()=0;
            void run()
#endif
            {
                {
                    boost::lock_guard<boost::mutex> lk(this->mutex);
                    if(started)
                    {
                        boost::throw_exception(task_already_started());
                    }
                    started=true;
                }
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                do_run(boost::forward<ArgTypes>(args)...);
#else
                do_run();
#endif
            }

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            virtual void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)=0;
            void apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
#else
            virtual void do_apply()=0;
            void apply()
#endif
            {
                {
                    boost::lock_guard<boost::mutex> lk(this->mutex);
                    if(started)
                    {
                        boost::throw_exception(task_already_started());
                    }
                    started=true;
                }
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                do_apply(boost::forward<ArgTypes>(args)...);
#else
                do_apply();
#endif
            }

            void owner_destroyed()
            {
                boost::unique_lock<boost::mutex> lk(this->mutex);
                if(!started)
                {
                    started=true;
                    this->mark_exceptional_finish_internal(boost::copy_exception(boost::broken_promise()), lk);
                }
            }

        };

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
        template<typename F, typename R>
        struct task_object;
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename F, typename R, typename ...ArgTypes>
        struct task_object<F, R(ArgTypes...)>:
          task_base<R(ArgTypes...)>
#else
        template<typename F, typename R>
        struct task_object<F, R()>:
          task_base<R()>
#endif
#else
        template<typename F, typename R>
        struct task_object:
            task_base<R>
#endif
        {
        private:
          task_object(task_object&);
        public:
            F f;
            task_object(F const& f_):
                f(f_)
            {}
            task_object(BOOST_THREAD_RV_REF(F) f_):
              f(boost::move(f_))
            {}

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    this->set_value_at_thread_exit(f(boost::forward<ArgTypes>(args)...));
                }
#else
            void do_apply()
            {
                try
                {
                    this->set_value_at_thread_exit(f());
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    this->mark_finished_with_result(f(boost::forward<ArgTypes>(args)...));
                }
#else
            void do_run()
            {
                try
                {
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
                  R res((f()));
                  this->mark_finished_with_result(boost::move(res));
#else
                  this->mark_finished_with_result(f());
#endif
                  }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }
        };

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename F, typename R, typename ...ArgTypes>
        struct task_object<F, R&(ArgTypes...)>:
          task_base<R&(ArgTypes...)>
#else
        template<typename F, typename R>
        struct task_object<F, R&()>:
          task_base<R&()>
#endif
#else
        template<typename F, typename R>
        struct task_object<F,R&>:
            task_base<R&>
#endif
        {
        private:
          task_object(task_object&);
        public:
            F f;
            task_object(F const& f_):
                f(f_)
            {}
            task_object(BOOST_THREAD_RV_REF(F) f_):
                f(boost::move(f_))
            {}

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    this->set_value_at_thread_exit(f(boost::forward<ArgTypes>(args)...));
                }
#else
            void do_apply()
            {
                try
                {
                    this->set_value_at_thread_exit(f());
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    this->mark_finished_with_result(f(boost::forward<ArgTypes>(args)...));
                }
#else
            void do_run()
            {
                try
                {
                  R& res((f()));
                  this->mark_finished_with_result(res);
                }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }
        };

#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename R, typename ...ArgTypes>
        struct task_object<R (*)(ArgTypes...), R(ArgTypes...)>:
          task_base<R(ArgTypes...)>
#else
        template<typename R>
        struct task_object<R (*)(), R()>:
          task_base<R()>
#endif
#else
        template<typename R>
        struct task_object<R (*)(), R> :
           task_base<R>
#endif
            {
            private:
              task_object(task_object&);
            public:
                R (*f)();
                task_object(R (*f_)()):
                    f(f_)
                {}


#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
                {
                    try
                    {
                        this->set_value_at_thread_exit(f(boost::forward<ArgTypes>(args)...));
                    }
#else
                void do_apply()
                {
                    try
                    {
                        R r((f()));
                        this->set_value_at_thread_exit(boost::move(r));
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->set_interrupted_at_thread_exit();
                    }
#endif
                    catch(...)
                    {
                        this->set_exception_at_thread_exit(current_exception());
                    }
                }


#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
                {
                    try
                    {
                        this->mark_finished_with_result(f(boost::forward<ArgTypes>(args)...));
                    }
#else
                void do_run()
                {
                    try
                    {
                        R res((f()));
                        this->mark_finished_with_result(boost::move(res));
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->mark_interrupted_finish();
                    }
#endif
                    catch(...)
                    {
                        this->mark_exceptional_finish();
                    }
                }
            };
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename R, typename ...ArgTypes>
        struct task_object<R& (*)(ArgTypes...), R&(ArgTypes...)>:
          task_base<R&(ArgTypes...)>
#else
        template<typename R>
        struct task_object<R& (*)(), R&()>:
          task_base<R&()>
#endif
#else
        template<typename R>
        struct task_object<R& (*)(), R&> :
           task_base<R&>
#endif
            {
            private:
              task_object(task_object&);
            public:
                R& (*f)();
                task_object(R& (*f_)()):
                    f(f_)
                {}


#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
                {
                    try
                    {
                        this->set_value_at_thread_exit(f(boost::forward<ArgTypes>(args)...));
                    }
#else
                void do_apply()
                {
                    try
                    {
                      this->set_value_at_thread_exit(f());
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->set_interrupted_at_thread_exit();
                    }
#endif
                    catch(...)
                    {
                        this->set_exception_at_thread_exit(current_exception());
                    }
                }


#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
                void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
                {
                    try
                    {
                        this->mark_finished_with_result(f(boost::forward<ArgTypes>(args)...));
                    }
#else
                void do_run()
                {
                    try
                    {
                        this->mark_finished_with_result(f());
                    }
#endif
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                    catch(thread_interrupted& )
                    {
                        this->mark_interrupted_finish();
                    }
#endif
                    catch(...)
                    {
                        this->mark_exceptional_finish();
                    }
                }
            };
#endif
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename F, typename ...ArgTypes>
        struct task_object<F, void(ArgTypes...)>:
          task_base<void(ArgTypes...)>
#else
        template<typename F>
        struct task_object<F, void()>:
          task_base<void()>
#endif
#else
        template<typename F>
        struct task_object<F,void>:
          task_base<void>
#endif
        {
        private:
          task_object(task_object&);
        public:
            F f;
            task_object(F const& f_):
                f(f_)
            {}
            task_object(BOOST_THREAD_RV_REF(F) f_):
                f(boost::move(f_))
            {}

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
              try
              {
                f(boost::forward<ArgTypes>(args)...);
#else
            void do_apply()
            {
                try
                {
                    f();
#endif
                  this->set_value_at_thread_exit();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    f(boost::forward<ArgTypes>(args)...);
#else
            void do_run()
            {
                try
                {
                    f();
#endif
                    this->mark_finished_with_result();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }
        };

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        template<typename ...ArgTypes>
        struct task_object<void (*)(ArgTypes...), void(ArgTypes...)>:
        task_base<void(ArgTypes...)>
#else
        template<>
        struct task_object<void (*)(), void()>:
        task_base<void()>
#endif
#else
        template<>
        struct task_object<void (*)(),void>:
          task_base<void>
#endif
        {
        private:
          task_object(task_object&);
        public:
            void (*f)();
            task_object(void (*f_)()):
                f(f_)
            {}

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_apply(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    f(boost::forward<ArgTypes>(args)...);
#else
            void do_apply()
            {
                try
                {
                    f();
#endif
                    this->set_value_at_thread_exit();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->set_interrupted_at_thread_exit();
                }
#endif
                catch(...)
                {
                    this->set_exception_at_thread_exit(current_exception());
                }
            }

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            void do_run(BOOST_THREAD_RV_REF(ArgTypes) ... args)
            {
                try
                {
                    f(boost::forward<ArgTypes>(args)...);
#else
            void do_run()
            {
                try
                {
                  f();
#endif
                  this->mark_finished_with_result();
                }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                catch(thread_interrupted& )
                {
                    this->mark_interrupted_finish();
                }
#endif
                catch(...)
                {
                    this->mark_exceptional_finish();
                }
            }
        };

    }


#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
    template<typename R, typename ...ArgTypes>
    class packaged_task<R(ArgTypes...)>
    {
      typedef boost::shared_ptr<detail::task_base<R(ArgTypes...)> > task_ptr;
      boost::shared_ptr<detail::task_base<R(ArgTypes...)> > task;
  #else
    template<typename R>
    class packaged_task<R()>
    {
      typedef boost::shared_ptr<detail::task_base<R()> > task_ptr;
      boost::shared_ptr<detail::task_base<R()> > task;
  #endif
#else
    template<typename R>
    class packaged_task
    {
      typedef boost::shared_ptr<detail::task_base<R> > task_ptr;
      boost::shared_ptr<detail::task_base<R> > task;
#endif
        bool future_obtained;
        struct dummy;

    public:
        typedef R result_type;
        BOOST_THREAD_MOVABLE_ONLY(packaged_task)

        packaged_task():
            future_obtained(false)
        {}

        // construction and destruction
#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
        explicit packaged_task(R(*f)(), BOOST_THREAD_FWD_REF(ArgTypes)... args)
        {
            typedef R(*FR)(BOOST_THREAD_FWD_REF(ArgTypes)...);
            typedef detail::task_object<FR,R(ArgTypes...)> task_object_type;
            task= task_ptr(new task_object_type(f, boost::forward<ArgTypes>(args)...));
            future_obtained=false;
        }
  #else
        explicit packaged_task(R(*f)())
        {
            typedef R(*FR)();
            typedef detail::task_object<FR,R()> task_object_type;
            task= task_ptr(new task_object_type(f));
            future_obtained=false;
        }
  #endif
#else
        explicit packaged_task(R(*f)())
        {
              typedef R(*FR)();
            typedef detail::task_object<FR,R> task_object_type;
            task= task_ptr(new task_object_type(f));
            future_obtained=false;
        }
#endif
#endif
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        template <class F>
        explicit packaged_task(BOOST_THREAD_FWD_REF(F) f
            , typename disable_if<is_same<typename decay<F>::type, packaged_task>, dummy* >::type=0
            )
        {
          typedef typename remove_cv<typename remove_reference<F>::type>::type FR;
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            typedef detail::task_object<FR,R(ArgTypes...)> task_object_type;
  #else
            typedef detail::task_object<FR,R()> task_object_type;
  #endif
#else
            typedef detail::task_object<FR,R> task_object_type;
#endif
            task = task_ptr(new task_object_type(boost::forward<F>(f)));
            future_obtained = false;

        }

#else
        template <class F>
        explicit packaged_task(F const& f
            , typename disable_if<is_same<typename decay<F>::type, packaged_task>, dummy* >::type=0
            )
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
  #else
            typedef detail::task_object<F,R()> task_object_type;
  #endif
#else
            typedef detail::task_object<F,R> task_object_type;
#endif
            task = task_ptr(new task_object_type(f));
            future_obtained=false;
        }
        template <class F>
        explicit packaged_task(BOOST_THREAD_RV_REF(F) f)
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
            typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
            task = task_ptr(new task_object_type(boost::forward<F>(f)));
#else
            typedef detail::task_object<F,R()> task_object_type;
            task = task_ptr(new task_object_type(boost::move<F>(f))); // TODO forward
#endif
#else
            typedef detail::task_object<F,R> task_object_type;
            task = task_ptr(new task_object_type(boost::forward<F>(f)));
#endif
            future_obtained=false;

        }
#endif

#if defined BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
#if defined(BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR)
        template <class Allocator>
        packaged_task(boost::allocator_arg_t, Allocator a, R(*f)())
        {
          typedef R(*FR)();
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          typedef detail::task_object<FR,R(ArgTypes...)> task_object_type;
  #else
          typedef detail::task_object<FR,R()> task_object_type;
  #endif
#else
          typedef detail::task_object<FR,R> task_object_type;
#endif
          typedef typename Allocator::template rebind<task_object_type>::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          task = task_ptr(::new(a2.allocate(1)) task_object_type(f), D(a2, 1) );
          future_obtained = false;
        }
#endif // BOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR

#if ! defined BOOST_NO_CXX11_RVALUE_REFERENCES
        template <class F, class Allocator>
        packaged_task(boost::allocator_arg_t, Allocator a, BOOST_THREAD_FWD_REF(F) f)
        {
          typedef typename remove_cv<typename remove_reference<F>::type>::type FR;
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          typedef detail::task_object<FR,R(ArgTypes...)> task_object_type;
  #else
          typedef detail::task_object<FR,R()> task_object_type;
  #endif
#else
          typedef detail::task_object<FR,R> task_object_type;
#endif
          typedef typename Allocator::template rebind<task_object_type>::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          task = task_ptr(::new(a2.allocate(1)) task_object_type(boost::forward<F>(f)), D(a2, 1) );
          future_obtained = false;
        }
#else // ! defined BOOST_NO_CXX11_RVALUE_REFERENCES
        template <class F, class Allocator>
        packaged_task(boost::allocator_arg_t, Allocator a, const F& f)
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
  #else
          typedef detail::task_object<F,R()> task_object_type;
  #endif
#else
          typedef detail::task_object<F,R> task_object_type;
#endif
          typedef typename Allocator::template rebind<task_object_type>::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

          task = task_ptr(::new(a2.allocate(1)) task_object_type(f), D(a2, 1) );
          future_obtained = false;
        }
        template <class F, class Allocator>
        packaged_task(boost::allocator_arg_t, Allocator a, BOOST_THREAD_RV_REF(F) f)
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
  #if defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          typedef detail::task_object<F,R(ArgTypes...)> task_object_type;
  #else
          typedef detail::task_object<F,R()> task_object_type;
  #endif
#else
          typedef detail::task_object<F,R> task_object_type;
#endif
          typedef typename Allocator::template rebind<task_object_type>::other A2;
          A2 a2(a);
          typedef thread_detail::allocator_destructor<A2> D;

#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          task = task_ptr(::new(a2.allocate(1)) task_object_type(boost::forward<F>(f)), D(a2, 1) );
#else
          task = task_ptr(::new(a2.allocate(1)) task_object_type(boost::move(f)), D(a2, 1) );  // TODO forward
#endif
          future_obtained = false;
        }

#endif //BOOST_NO_CXX11_RVALUE_REFERENCES
#endif // BOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS

        ~packaged_task()
        {
            if(task)
            {
                task->owner_destroyed();
            }
        }

        // assignment
        packaged_task(BOOST_THREAD_RV_REF(packaged_task) other) BOOST_NOEXCEPT :
            future_obtained(BOOST_THREAD_RV(other).future_obtained)
        {
            task.swap(BOOST_THREAD_RV(other).task);
            BOOST_THREAD_RV(other).future_obtained=false;
        }
        packaged_task& operator=(BOOST_THREAD_RV_REF(packaged_task) other) BOOST_NOEXCEPT
        {

            // todo use forward
#if ! defined  BOOST_NO_CXX11_RVALUE_REFERENCES
            packaged_task temp(boost::move(other));
#else
            packaged_task temp(static_cast<BOOST_THREAD_RV_REF(packaged_task)>(other));
#endif
            swap(temp);
            return *this;
        }

        void reset()
        {
            if (!valid())
                throw future_error(system::make_error_code(future_errc::no_state));
            task->reset();
            future_obtained=false;
        }

        void swap(packaged_task& other) BOOST_NOEXCEPT
        {
            task.swap(other.task);
            std::swap(future_obtained,other.future_obtained);
        }
        bool valid() const BOOST_NOEXCEPT
        {
          return task.get()!=0;
        }

        // result retrieval
        BOOST_THREAD_FUTURE<R> get_future()
        {

            if(!task)
            {
                boost::throw_exception(task_moved());
            }
            else if(!future_obtained)
            {
                future_obtained=true;
                return BOOST_THREAD_FUTURE<R>(task);
            }
            else
            {
                boost::throw_exception(future_already_retrieved());
            }
            //return BOOST_THREAD_FUTURE<R>();

        }

        void operator()()
        {
            if(!task)
            {
                boost::throw_exception(task_moved());
            }
            task->run();
        }

        void make_ready_at_thread_exit()
        {
          if(!task)
          {
              boost::throw_exception(task_moved());
          }
          if (task->has_value())
                boost::throw_exception(promise_already_satisfied());
          task->apply();
        }

        template<typename F>
        void set_wait_callback(F f)
        {
            task->set_wait_callback(f,this);
        }

    template <class Rp, class Fp>
    BOOST_THREAD_FUTURE<Rp>
    make_future_deferred_object(BOOST_THREAD_FWD_REF(Fp) f)
    {
      shared_ptr<future_deferred_object<Rp, Fp> >
          h(new future_deferred_object<Rp, Fp>(boost::forward<Fp>(f)));
      return BOOST_THREAD_FUTURE<Rp>(h);
    }

    template <class Rp, class Fp>
    BOOST_THREAD_FUTURE<Rp>
    make_future_async_object(BOOST_THREAD_FWD_REF(Fp) f)
    {
      shared_ptr<future_async_object<Rp, Fp> >
          h(new future_async_object<Rp, Fp>(boost::forward<Fp>(f)));
      return BOOST_THREAD_FUTURE<Rp>(h);
    }

        template <class R>
        BOOST_THREAD_FUTURE<R>
        async(launch policy, R(*f)())
        {
          typedef packaged_task<R> packaged_task_type;
#endif
          if (int(policy) & int(launch::async))
            {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          return BOOST_THREAD_MAKE_RV_REF(boost::detail::make_future_async_object<Rp>(
              BF(
                  thread_detail::decay_copy(boost::forward<F>(f))
                  , thread_detail::decay_copy(boost::forward<ArgTypes>(args))...
              )
          ));
#else
              packaged_task_type pt( f );

              BOOST_THREAD_FUTURE<R> ret = BOOST_THREAD_MAKE_RV_REF(pt.get_future());
              ret.set_async();
              boost::thread( boost::move(pt) ).detach();
              return ::boost::move(ret);
#endif
            }
            else if (int(policy) & int(launch::deferred))
            {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          return BOOST_THREAD_MAKE_RV_REF(boost::detail::make_future_deferred_object<Rp>(
              BF(
                  thread_detail::decay_copy(boost::forward<F>(f))
                  , thread_detail::decay_copy(boost::forward<ArgTypes>(args))...
              )
          ));
#else
          std::terminate();
          BOOST_THREAD_FUTURE<R> ret;
          return ::boost::move(ret);

#endif
            } else {
              std::terminate();
              BOOST_THREAD_FUTURE<R> ret;
              return ::boost::move(ret);
            }
        }

        template <class F>
        BOOST_THREAD_FUTURE<typename boost::result_of<typename decay<F>::type()>::type>
        async(launch policy, BOOST_THREAD_FWD_REF(F)  f)
        {
          typedef typename boost::result_of<typename decay<F>::type()>::type R;
          typedef packaged_task<R> packaged_task_type;

#endif

        if (int(policy) & int(launch::async))
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          return BOOST_THREAD_MAKE_RV_REF(boost::detail::make_future_async_object<Rp>(
              BF(
                  thread_detail::decay_copy(boost::forward<F>(f))
                  , thread_detail::decay_copy(boost::forward<ArgTypes>(args))...
              )
          ));
#else
          packaged_task_type pt( boost::forward<F>(f) );

          BOOST_THREAD_FUTURE<R> ret = pt.get_future();
          ret.set_async();
//#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
//          boost::thread( boost::move(pt), boost::forward<ArgTypes>(args)... ).detach(); // todo forward
//#else
          boost::thread( boost::move(pt) ).detach();
//#endif
          return ::boost::move(ret);
#endif
        }
        else if (int(policy) & int(launch::deferred))
        {
#if defined BOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(BOOST_THREAD_PROVIDES_VARIADIC_THREAD)
          return BOOST_THREAD_MAKE_RV_REF(boost::detail::make_future_deferred_object<Rp>(
              BF(
                  thread_detail::decay_copy(boost::forward<F>(f))
                  , thread_detail::decay_copy(boost::forward<ArgTypes>(args))...
              )
          ));
#else
              std::terminate();
              BOOST_THREAD_FUTURE<R> ret;
              return ::boost::move(ret);
//          return boost::detail::make_future_deferred_object<Rp>(
//              BF(
//                  thread_detail::decay_copy(boost::forward<F>(f))
//              )
//          );
#endif

        } else {
          std::terminate();
          BOOST_THREAD_FUTURE<R> ret;
          return ::boost::move(ret);
        }
    }

            template <class R>
            BOOST_THREAD_FUTURE<R>
            async(R(*f)())
            {
              return BOOST_THREAD_MAKE_RV_REF(async(launch(launch::any), f));
            }

    template <class F>
    BOOST_THREAD_FUTURE<typename boost::result_of<F()>::type>
    async(BOOST_THREAD_RV_REF(F) f)
    {
        return BOOST_THREAD_MAKE_RV_REF(async(launch(launch::any), boost::forward<F>(f)));
    }

  template <typename T>
  BOOST_THREAD_FUTURE<typename decay<T>::type> make_future(BOOST_THREAD_FWD_REF(T) value)
  {
    typedef typename decay<T>::type future_type;
    promise<future_type> p;
    p.set_value(boost::forward<T>(value));
    return BOOST_THREAD_MAKE_RV_REF(p.get_future());
  }

  template <typename T>
  BOOST_THREAD_FUTURE<typename decay<T>::type> make_ready_future(BOOST_THREAD_FWD_REF(T) value)
  {
    typedef typename decay<T>::type future_type;
    promise<future_type> p;
    p.set_value(boost::forward<T>(value));
    return BOOST_THREAD_MAKE_RV_REF(p.get_future());
  }

  template <typename T>
  BOOST_THREAD_FUTURE<T> make_exceptional_future(exception_ptr ex)
  {
    promise<T> p;
    p.set_exception(ex);
    return BOOST_THREAD_MAKE_RV_REF(p.get_future());
  }

  template <typename T>
  shared_future<typename decay<T>::type> make_shared_future(BOOST_THREAD_FWD_REF(T) value)
  {
    typedef typename decay<T>::type future_type;
    promise<future_type> p;
    p.set_value(boost::forward<T>(value));
    return BOOST_THREAD_MAKE_RV_REF(p.get_future().share());
  }



  inline shared_future<void> make_shared_future()
  {
    promise<void> p;
    return BOOST_THREAD_MAKE_RV_REF(p.get_future().share());

  }

  template <typename T>
  shared_future<typename decay<T>::type> make_ready_shared_future(BOOST_THREAD_FWD_REF(T) value)
  {
    typedef typename decay<T>::type future_type;
    promise<future_type> p;
    p.set_value(boost::forward<T>(value));
    return p.get_future().share();
  }



  inline shared_future<void> make_ready_shared_future()
  {
    promise<void> p;
    return BOOST_THREAD_MAKE_RV_REF(p.get_future().share());

  }

  template <typename T>
  shared_future<T> make_exceptional_shared_future(exception_ptr ex)
  {
    promise<T> p;
    p.set_exception(ex);
    return p.get_future().share();
  }

    mutex_type& lockable() const
    {
      return lockable_;
    }


    basic_lockable_adapter()
    {}


    void lock()
    {
      lockable().lock();
    }

    void unlock()
    {
      lockable().unlock();
    }


    bool try_lock()
    {
      return this->lockable().try_lock();
    }


    template <typename Clock, typename Duration>
    bool try_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_lock_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_lock_for(rel_time);
    }


    void lock_shared()
    {
      this->lockable().lock_shared();
    }

    bool try_lock_shared()
    {
      return this->lockable().try_lock_shared();
    }

    void unlock_shared()
    {
      this->lockable().unlock_shared();
    }


    template <typename Clock, typename Duration>
    bool try_lock_shared_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_lock_shared_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_lock_shared_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_lock_shared_for(rel_time);
    }


    void lock_upgrade()
    {
      this->lockable().lock_upgrade();
    }


    bool try_lock_upgrade()
    {
      return this->lockable().try_lock_upgrade();
    }


    void unlock_upgrade()
    {
      this->lockable().unlock_upgrade();
    }


    template <typename Clock, typename Duration>
    bool try_lock_upgrade_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_lock_upgrade_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_lock_upgrade_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_lock_upgrade_for(rel_time);
    }


    bool try_unlock_shared_and_lock()
    {
      return this->lockable().try_unlock_shared_and_lock();
    }


    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_unlock_shared_and_lock_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_unlock_shared_and_lock_for(rel_time);
    }


    void unlock_and_lock_shared()
    {
      this->lockable().unlock_and_lock_shared();
    }


    bool try_unlock_shared_and_lock_upgrade()
    {
      return this->lockable().try_unlock_shared_and_lock_upgrade();
    }


    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_upgrade_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_unlock_shared_and_lock_upgrade_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_upgrade_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_unlock_shared_and_lock_upgrade_for(rel_time);
    }


    void unlock_and_lock_upgrade()
    {
      this->lockable().unlock_and_lock_upgrade();
    }


    void unlock_upgrade_and_lock()
    {
      this->lockable().unlock_upgrade_and_lock();
    }


    bool try_unlock_upgrade_and_lock()
    {
      return this->lockable().try_unlock_upgrade_and_lock();
    }

    template <typename Clock, typename Duration>
    bool try_unlock_upgrade_and_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return this->lockable().try_unlock_upgrade_and_lock_until(abs_time);
    }

    template <typename Rep, typename Period>
    bool try_unlock_upgrade_and_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return this->lockable().try_unlock_upgrade_and_lock_for(rel_time);
    }


    void unlock_upgrade_and_lock_shared()
    {
      this->lockable().unlock_upgrade_and_lock_shared();
    }

        explicit shared_lock_guard(SharedMutex& m_):
            m(m_)
        {
            m.lock_shared();
        }

        shared_lock_guard(SharedMutex& m_,adopt_lock_t):
            m(m_)
        {}

        ~shared_lock_guard()
        {
            m.unlock_shared();
        }


    BasicLockable() : l(*static_cast<Mutex*>(0)) {}


    Lockable() : l(*static_cast<Mutex*>(0)) {}


    TimedLockable() : l(*static_cast<Mutex*>(0)) {}


    SharedLockable() : l(*static_cast<Mutex*>(0)) {}


    UpgradeLockable() : l(*static_cast<Mutex*>(0)) {}


    explicit lock_guard(Mutex& m_) :
      m(m_)
    {
      m.lock();
    }


    lock_guard(Mutex& m_, adopt_lock_t) :
      m(m_)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

    ~lock_guard()
    {
      m.unlock();
    }

    bool count_down(unique_lock<mutex> &lk)
    /// pre_condition (count_.value_ > 0)
    {
      BOOST_ASSERT(count_.value_ > 0);
      if (--count_.value_ == 0)
      {
        count_.cond_.notify_all();
        lk.unlock();
        return true;
      }
      return false;
    }


    ~latch()
    {

    }

    void wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      count_.cond_.wait(lk, detail::counter_is_zero(count_));
    }

    bool try_wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      return (count_ == 0);
    }

    template <class Rep, class Period>
    cv_status wait_for(const chrono::duration<Rep, Period>& rel_time)
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      return count_.cond_.wait_for(lk, rel_time, detail::counter_is_zero(count_))
              ? cv_status::no_timeout
              : cv_status::timeout;
    }

    template <class Clock, class Duration>
    cv_status wait_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      return count_.cond_.wait_until(lk, abs_time, detail::counter_is_zero(count_))
          ? cv_status::no_timeout
          : cv_status::timeout;
    }

    void count_down()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      count_down(lk);
    }

    void signal()
    {
      count_down();
    }

    void count_down_and_wait()
    {
      boost::unique_lock<boost::mutex> lk(mutex_);
      if (count_down(lk))
      {
        return;
      }
      count_.cond_.wait(lk, detail::counter_is_zero(count_));
    }

    void sync()
    {
      count_down_and_wait();
    }

    void reset(std::size_t count)
    {
      boost::lock_guard<boost::mutex> lk(mutex_);
      //BOOST_ASSERT(count_ == 0);
      count_ = count;
    }

template<typename Function>
inline void call_once(Function func,once_flag& flag)
//inline void call_once(void (*func)(),once_flag& flag)
    {
        call_once(flag,func);
    }

        thread_exception()
          : base_type(0,system::system_category())
        {}


        thread_exception(int sys_error_code)
          : base_type(sys_error_code, system::system_category())
        {}


        thread_exception( int ev, const char * what_arg )
        : base_type(system::error_code(ev, system::system_category()), what_arg)
        {
        }


        ~thread_exception() throw()
        {}



        int native_error() const
        {
            return code().value();
        }

          condition_error()
          : base_type(system::error_code(0, system::system_category()), "Condition error")
          {}

          condition_error( int ev )
          : base_type(system::error_code(ev, system::system_category()), "Condition error")
          {
          }

          condition_error( int ev, const char * what_arg )
          : base_type(system::error_code(ev, system::system_category()), what_arg)
          {
          }

        lock_error()
        : base_type(0, "boost::lock_error")
        {}


        lock_error( int ev )
        : base_type(ev, "boost::lock_error")
        {
        }

        lock_error( int ev, const char * what_arg )
        : base_type(ev, what_arg)
        {
        }


        ~lock_error() throw()
        {}

          thread_resource_error()
          : base_type(system::errc::resource_unavailable_try_again, "boost::thread_resource_error")
          {}


          thread_resource_error( int ev )
          : base_type(ev, "boost::thread_resource_error")
          {
          }

          thread_resource_error( int ev, const char * what_arg )
          : base_type(ev, what_arg)
          {
          }



        ~thread_resource_error() throw()
        {}

          unsupported_thread_option()
          : base_type(system::errc::invalid_argument, "boost::unsupported_thread_option")
          {}


          unsupported_thread_option( int ev )
          : base_type(ev, "boost::unsupported_thread_option")
          {
          }

          unsupported_thread_option( int ev, const char * what_arg )
          : base_type(ev, what_arg)
          {
          }

        invalid_thread_argument()
        : base_type(system::errc::invalid_argument, "boost::invalid_thread_argument")
        {}


        invalid_thread_argument( int ev )
        : base_type(ev, "boost::invalid_thread_argument")
        {
        }

        invalid_thread_argument( int ev, const char * what_arg )
        : base_type(ev, what_arg)
        {
        }

          thread_permission_error()
          : base_type(system::errc::permission_denied, "boost::thread_permission_error")
          {}


          thread_permission_error( int ev )
          : base_type(ev, "boost::thread_permission_error")
          {
          }

          thread_permission_error( int ev, const char * what_arg )
          : base_type(ev, what_arg)
          {
          }


    size_type inc(size_type idx) const BOOST_NOEXCEPT
    {
      return (idx + 1) % capacity_;
    }



    void notify_not_empty_if_needed(unique_lock<mutex>& lk)
    {
      if (waiting_empty_ > 0)
      {
        --waiting_empty_;
        lk.unlock();
        not_empty_.notify_one();
      }
    }

    void notify_not_full_if_needed(unique_lock<mutex>& lk)
    {
      if (waiting_full_ > 0)
      {
        --waiting_full_;
        lk.unlock();
        not_full_.notify_one();
      }
    }



    void set_in(size_type in, unique_lock<mutex>& lk)
    {
      in_ = in;
      notify_not_empty_if_needed(lk);
    }


    void push_at(const value_type& elem, size_type in_p_1, unique_lock<mutex>& lk)
    {
      data_[in_] = elem;
      set_in(in_p_1, lk);
    }


  template <typename ValueType>
  sync_bounded_queue<ValueType>::sync_bounded_queue(typename sync_bounded_queue<ValueType>::size_type max_elems) :
    waiting_full_(0), waiting_empty_(0), data_(new value_type[max_elems + 1]), in_(0), out_(0), capacity_(max_elems + 1),
        closed_(false)
  {
    BOOST_ASSERT_MSG(max_elems >= 1, "number of elements must be > 1");
  }


  template <typename ValueType>
  sync_bounded_queue<ValueType>::~sync_bounded_queue()
  {
    delete[] data_;
  }


  template <typename ValueType>
  void sync_bounded_queue<ValueType>::close()
  {
    {
      lock_guard<mutex> lk(mtx_);
      closed_ = true;
    }
    not_empty_.notify_all();
    not_full_.notify_all();
  }


  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::closed() const
  {
    lock_guard<mutex> lk(mtx_);
    return closed_;
  }


  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::empty() const
  {
    lock_guard<mutex> lk(mtx_);
    return empty(lk);
  }

  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::full() const
  {
    lock_guard<mutex> lk(mtx_);
    return full(lk);
  }


  template <typename ValueType>
  typename sync_bounded_queue<ValueType>::size_type sync_bounded_queue<ValueType>::capacity() const
  {
    lock_guard<mutex> lk(mtx_);
    return capacity(lk);
  }


  template <typename ValueType>
  typename sync_bounded_queue<ValueType>::size_type sync_bounded_queue<ValueType>::size() const
  {
    lock_guard<mutex> lk(mtx_);
    return size(lk);
  }


  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::try_pull(ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  boost::shared_ptr<ValueType> sync_bounded_queue<ValueType>::try_pull()
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_pull(lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_bounded_queue<ValueType>::pull(ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk);
      pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  void sync_bounded_queue<ValueType>::pull(ValueType& elem, bool & closed)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk, closed);
      if (closed) {return;}
      pull(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  ValueType sync_bounded_queue<ValueType>::pull()
  {
    try
    {
      value_type elem;
      pull(elem);
      return boost::move(elem);
    }
    catch (...)
    {
      close();
      throw;
    }
  }

  template <typename ValueType>
  boost::shared_ptr<ValueType> sync_bounded_queue<ValueType>::ptr_pull()
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      wait_until_not_empty(lk);
      return ptr_pull(lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::try_push(const ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_bounded_queue<ValueType>::push(const ValueType& elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      push_at(elem, wait_until_not_full(lk), lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  bool sync_bounded_queue<ValueType>::try_push(BOOST_THREAD_RV_REF(ValueType) elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      return try_push(elem, lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  void sync_bounded_queue<ValueType>::push(BOOST_THREAD_RV_REF(ValueType) elem)
  {
    try
    {
      unique_lock<mutex> lk(mtx_);
      push_at(elem, wait_until_not_full(lk), lk);
    }
    catch (...)
    {
      close();
      throw;
    }
  }


  template <typename ValueType>
  sync_bounded_queue<ValueType>& operator<<(sync_bounded_queue<ValueType>& sbq, BOOST_THREAD_RV_REF(ValueType) elem)
  {
    sbq.push(boost::forward<ValueType>(elem));
    return sbq;
  }


  template <typename ValueType>
  sync_bounded_queue<ValueType>& operator<<(sync_bounded_queue<ValueType>& sbq, ValueType const&elem)
  {
    sbq.push(elem);
    return sbq;
  }


  template <typename ValueType>
  sync_bounded_queue<ValueType>& operator>>(sync_bounded_queue<ValueType>& sbq, ValueType &elem)
  {
    sbq.pull(elem);
    return sbq;
  }


    testable_mutex() : id_(thread::id()) {}


    void lock()
    {
      mtx_.lock();
      id_ = this_thread::get_id();
    }


    void unlock()
    {
      BOOST_ASSERT(is_locked_by_this_thread());
      id_ = thread::id();
      mtx_.unlock();
    }


    bool try_lock()
    {
      if (mtx_.try_lock())
      {
        id_ = this_thread::get_id();
        return true;
      }
      else
      {
        return false;
      }
    }

    template <class Rep, class Period>
    bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
    {
      if (mtx_.try_lock_for(rel_time))
      {
        id_ = this_thread::get_id();
        return true;
      }
      else
      {
        return false;
      }
    }

    template <class Clock, class Duration>
    bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
    {
      if (mtx_.try_lock_until(abs_time))
      {
        id_ = this_thread::get_id();
        return true;
      }
      else
      {
        return false;
      }
    }


    bool is_locked_by_this_thread() const
    {
      return this_thread::get_id() == id_;
    }

    bool is_locked() const
    {
      return ! (thread::id() == id_);
    }


    thread::id get_id() const
    {
      return id_;
    }

  template <typename Lockable>
  bool is_locked_by_this_thread(testable_mutex<Lockable> const& mtx)
  {
    return mtx.is_locked_by_this_thread();
  }

  template <typename Lockable>
  bool is_locked_by_this_thread(Lockable const&)
  {
    return true;
  }

    
    inline system_time get_system_time()
    {
#if defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
        return boost::date_time::microsec_clock<system_time>::universal_time();
#else // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
        return boost::date_time::second_clock<system_time>::universal_time();
#endif // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    }

        inline system_time get_system_time_sentinel()
        {
            return system_time(boost::posix_time::pos_infin);
        }


        inline unsigned long get_milliseconds_until(system_time const& target_time)
        {
            if(target_time.is_pos_infinity())
            {
                return ~(unsigned long)0;
            }
            system_time const now=get_system_time();
            if(target_time<=now)
            {
                return 0;
            }
            return static_cast<unsigned long>((target_time-now).total_milliseconds()+1);
        }


        barrier(unsigned int count)
            : m_threshold(count), m_count(count), m_generation(0)
        {
            if (count == 0)
                boost::throw_exception(thread_exception(system::errc::invalid_argument, "barrier constructor: count cannot be zero."));
        }


        bool wait()
        {
            boost::unique_lock<boost::mutex> lock(m_mutex);
            unsigned int gen = m_generation;

            if (--m_count == 0)
            {
                m_generation++;
                m_count = m_threshold;
                m_cond.notify_all();
                return true;
            }

            while (gen == m_generation)
                m_cond.wait(lock);
            return false;
        }


    explicit thread_guard(thread& t) :
    t_(t)
    {
    }

    ~thread_guard()
    {
      CallableThread on_destructor;

      on_destructor(t_);
    }

    template <typename Clock, typename Duration>
    bool try_lock_shared_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_lock_shared_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_lock_shared_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_lock_shared_for(duration_cast<Clock::duration>(rel_time));
    }

    template <typename Clock, typename Duration>
    bool try_lock_upgrade_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_lock_upgrade_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_lock_upgrade_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_lock_upgrade_for(duration_cast<Clock::duration>(rel_time));
    }

    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_unlock_shared_and_lock_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_unlock_shared_and_lock_for(duration_cast<Clock::duration>(rel_time));
    }

    template <typename Clock, typename Duration>
    bool try_unlock_shared_and_lock_upgrade_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_unlock_shared_and_lock_upgrade_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_unlock_shared_and_lock_upgrade_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_unlock_shared_and_lock_upgrade_for(duration_cast<Clock::duration>(rel_time));
    }

    template <typename Clock, typename Duration>
    bool try_unlock_upgrade_and_lock_until(chrono::time_point<Clock, Duration> const & abs_time)
    {
      return try_unlock_upgrade_and_lock_until(time_point_cast<Clock::time_point>(abs_time));
    }

    template <typename Rep, typename Period>
    bool try_unlock_upgrade_and_lock_for(chrono::duration<Rep, Period> const & rel_time)
    {
      return try_unlock_upgrade_and_lock_for(duration_cast<Clock::duration>(rel_time));
    }

    mutex_type& mtx() const
    {
      return mtx_;
    }


    poly_basic_lockable_adapter()
    {}


    void lock()
    {
      mtx().lock();
    }

    void unlock()
    {
      mtx().unlock();
    }


    bool try_lock()
    {
      return this->mtx().try_lock();
    }


    bool try_lock_until(chrono::system_clock::time_point const & abs_time)
    {
      return this->mtx().try_lock_until(abs_time);
    }

    bool try_lock_for(chrono::nanoseconds const & rel_time)
    {
      return this->mtx().try_lock_for(rel_time);
    }


            thread_data(BOOST_THREAD_RV_REF(F) f_):
              f(f_)
            {}

            thread_data(F f_):
                f(f_)
            {}


            void run()
            {
                f();
            }

            thread_data(boost::reference_wrapper<F> f_):
                f(f_)
            {}

            void run()
            {
                f();
            }

            thread_data(const boost::reference_wrapper<F> f_):
                f(f_)
            {}

            void run()
            {
                f();
            }



        void start_thread()
        {
          if (!start_thread_noexcept())
          {
            boost::throw_exception(thread_resource_error());
          }
        }

        void start_thread(const attributes& attr)
        {
          if (!start_thread_noexcept(attr))
          {
            boost::throw_exception(thread_resource_error());
          }
        }

        template<typename F>
        static inline detail::thread_data_ptr make_thread_info(F f
            , typename disable_if_c<
                //boost::thread_detail::is_convertible<F&,BOOST_THREAD_RV_REF(F)>::value ||
                is_same<typename decay<F>::type, thread>::value,
                dummy* >::type=0
                )
        {
            return detail::thread_data_ptr(detail::heap_new<detail::thread_data<F> >(f));
        }

        ~thread()
        {

    #if defined BOOST_THREAD_PROVIDES_THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE
          if (joinable()) {
            std::terminate();
          }
    #else
            detach();
    #endif
        }

        template <class F>
        explicit thread(F f
        , typename disable_if_c<
            boost::thread_detail::is_convertible<F&,BOOST_THREAD_RV_REF(F)>::value
            //|| is_same<typename decay<F>::type, thread>::value
           , dummy* >::type=0
        ):
            thread_info(make_thread_info(f))
        {
            start_thread();
        }

        template <class F>
        thread(attributes const& attrs, F f
        , typename disable_if<boost::thread_detail::is_convertible<F&,BOOST_THREAD_RV_REF(F) >, dummy* >::type=0
        ):
            thread_info(make_thread_info(f))
        {
            start_thread(attrs);
        }

        template <class F>
        explicit thread(BOOST_THREAD_RV_REF(F) f
        , typename disable_if<is_same<typename decay<F>::type, thread>, dummy* >::type=0
        ):
#ifdef BOOST_THREAD_USES_MOVE
        thread_info(make_thread_info(boost::move<F>(f))) // todo : Add forward
#else
        thread_info(make_thread_info(f)) // todo : Add forward
#endif
        {
            start_thread();
        }


        template <class F>
        thread(attributes const& attrs, BOOST_THREAD_RV_REF(F) f):
#ifdef BOOST_THREAD_USES_MOVE
            thread_info(make_thread_info(boost::move<F>(f))) // todo : Add forward
#else
            thread_info(make_thread_info(f)) // todo : Add forward
#endif
        {
            start_thread(attrs);
        }

        thread(BOOST_THREAD_RV_REF(thread) x)
        {
            thread_info=BOOST_THREAD_RV(x).thread_info;
            BOOST_THREAD_RV(x).thread_info.reset();
        }


        thread& operator=(BOOST_THREAD_RV_REF(thread) other) BOOST_NOEXCEPT
        {

#if defined BOOST_THREAD_PROVIDES_THREAD_MOVE_ASSIGN_CALLS_TERMINATE_IF_JOINABLE
            if (joinable()) std::terminate();
#endif
            thread_info=BOOST_THREAD_RV(other).thread_info;
            BOOST_THREAD_RV(other).thread_info.reset();
            return *this;
        }

        template <class F,class A1,class A2>
        thread(F f,A1 a1,A2 a2):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3>
        thread(F f,A1 a1,A2 a2,A3 a3):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4,class A5>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4,a5)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4,class A5,class A6>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4,a5,a6)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4,class A5,class A6,class A7>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4,a5,a6,a7)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4,a5,a6,a7,a8)))
        {
            start_thread();
        }


        template <class F,class A1,class A2,class A3,class A4,class A5,class A6,class A7,class A8,class A9>
        thread(F f,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9):
            thread_info(make_thread_info(boost::bind(boost::type<void>(),f,a1,a2,a3,a4,a5,a6,a7,a8,a9)))
        {
            start_thread();
        }

        void swap(thread& x) BOOST_NOEXCEPT
        {
            thread_info.swap(x.thread_info);
        }

        template <class Rep, class Period>
        bool try_join_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_join_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_join_until(const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          bool joined= false;
          do {
            typename Clock::duration   d = ceil<nanoseconds>(t-Clock::now());
            if (d <= Clock::duration::zero()) return false; // in case the Clock::time_point t is already reached
            joined = try_join_until(s_now + d);
          } while (! joined);
          return true;
        }

        template <class Duration>
        bool try_join_until(const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
          return try_join_until(nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
        }

        bool timed_join(const system_time& abs_time)
        {
          struct timespec const ts=detail::to_timespec(abs_time);
          return do_try_join_until(ts);
        }

        bool try_join_until(const chrono::time_point<chrono::system_clock, chrono::nanoseconds>& tp)
        {
          using namespace chrono;
          nanoseconds d = tp.time_since_epoch();
          timespec ts = boost::detail::to_timespec(d);
          return do_try_join_until(ts);
        }

        template<typename TimeDuration>
        inline bool timed_join(TimeDuration const& rel_time)
        {
            return timed_join(get_system_time()+rel_time);
        }

        static inline void yield() BOOST_NOEXCEPT
        {
            this_thread::yield();
        }


        static inline void sleep(const system_time& xt)
        {
            this_thread::sleep(xt);
        }


    inline void swap(thread& lhs,thread& rhs) BOOST_NOEXCEPT
    {
        return lhs.swap(rhs);
    }

        inline BOOST_SYMBOL_VISIBLE void sleep(xtime const& abs_time)
        {
            sleep(system_time(abs_time));
        }


        id(data thread_data_):
            thread_data(thread_data_)
        {}

        id() BOOST_NOEXCEPT:
#if defined BOOST_THREAD_PROVIDES_BASIC_THREAD_ID
        thread_data(0)
#else
        thread_data()
#endif
        {}


        id(const id& other) BOOST_NOEXCEPT :
            thread_data(other.thread_data)
        {}


        bool operator==(const id& y) const BOOST_NOEXCEPT
        {
            return thread_data==y.thread_data;
        }


        bool operator!=(const id& y) const BOOST_NOEXCEPT
        {
            return thread_data!=y.thread_data;
        }


        bool operator<(const id& y) const BOOST_NOEXCEPT
        {
            return thread_data<y.thread_data;
        }


        bool operator>(const id& y) const BOOST_NOEXCEPT
        {
            return y.thread_data<thread_data;
        }


        bool operator<=(const id& y) const BOOST_NOEXCEPT
        {
            return !(y.thread_data<thread_data);
        }


        bool operator>=(const id& y) const BOOST_NOEXCEPT
        {
            return !(thread_data<y.thread_data);
        }

    void thread::join() {
        if (this_thread::get_id() == get_id())
          boost::throw_exception(thread_resource_error(system::errc::resource_deadlock_would_occur, "boost thread: trying joining itself"));

        BOOST_THREAD_VERIFY_PRECONDITION( join_noexcept(),
            thread_resource_error(system::errc::invalid_argument, "boost thread: thread not joinable")
        );
    }

    inline bool thread::operator==(const thread& other) const
    {
        return get_id()==other.get_id();
    }


    inline bool thread::operator!=(const thread& other) const
    {
        return get_id()!=other.get_id();
    }

            virtual ~thread_exit_function_base()
            {}


            thread_exit_function(F f_):
                f(f_)
            {}


            void operator()()
            {
                f();
            }

        template<typename F>
        void at_thread_exit(F f)
        {
            detail::thread_exit_function_base* const thread_exit_func=detail::heap_new<detail::thread_exit_function<F> >(f);
            detail::add_thread_exit_function(thread_exit_func);
        }


    template <typename T>
    inline dummy_stream_t const& operator<<(dummy_stream_t const& os, T)
    {
      return os;
    }


    inline dummy_stream_t const& operator<<(dummy_stream_t const& os, dummy_stream_t const&)
    {
      return os;
    }


    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(), BOOST_THREAD_RV_REF(A0) a0)
    {
        return (boost::forward<A0>(a0).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1), BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1), A0 a0, A1 a1)
    {
        return (a0.*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2),
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2), A0 a0, A1 a1, A2 a2)
    {
        return (a0.*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3),
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3), A0 a0, A1 a1, A2 a2, A3 a3)
    {
        return (a0.*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() const, BOOST_THREAD_RV_REF(A0) a0)
    {
        return (boost::forward<A0>(a0).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const, BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const, A0 a0, A1 a1)
    {
        return (a0.*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2)
            );
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const, A0 a0, A1 a1, A2 a2)
    {
        return (a0.*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        return (a0.*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() volatile, BOOST_THREAD_RV_REF(A0) a0)
    {
        return (boost::forward<A0>(a0).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) volatile, BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) volatile, A0 a0, A1 a1)
    {
        return (a0.*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) volatile, A0 a0, A1 a1, A2 a2 )
    {
        return (a0.*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) volatile, A0 a0, A1 a1, A2 a2, A3 a3)
    {
        return (a0.*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() const volatile, BOOST_THREAD_RV_REF(A0) a0)
    {
        return (boost::forward<A0>(a0).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const volatile, BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const volatile, A0 a0, A1 a1)
    {
        return (a0.*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const volatile,
        A0 a0, A1 a1, A2 a2
        )
    {
        return (a0.*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3
        )
    {
        return (boost::forward<A0>(a0).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const volatile,
        A0 a0, A1 a1, A2 a2, A3 a3
        )
    {
        return (a0.*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(), BOOST_THREAD_RV_REF(A0) a0)
    {
      return ((*boost::forward<A0>(a0)).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1), BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1), A0 a0, A1 a1)
    {
      return ((*a0).*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, BOOST_THREAD_RV_REF(A2)),
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2), A0 a0, A1 a1, A2 a2)
    {
      return ((*a0).*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, BOOST_THREAD_RV_REF(A2), BOOST_THREAD_RV_REF(A3)),
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3)
          );
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3), A0 a0, A1 a1, A2 a2, A3 a3)
    {
      return ((*a0).*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() const, BOOST_THREAD_RV_REF(A0) a0)
    {
      return ((*boost::forward<A0>(a0)).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const, BOOST_THREAD_RV_REF(A0) a0, A1 a1)
    {
      return ((*boost::forward<A0>(a0)).*f)(a1);
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const, A0 a0, A1 a1)
    {
      return ((*a0).*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const, A0 a0, A1 a1, A2 a2)
    {
      return ((*a0).*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const,
        A0 a0, A1 a1, A2 a2, A3 a3)
    {
      return ((*a0).*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() volatile, BOOST_THREAD_RV_REF(A0) a0)
    {
      return ((*boost::forward<A0>(a0)).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) volatile, A0 a0, A1 a1)
    {
      return ((*a0).*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) volatile, A0 a0, A1 a1, A2 a2)
    {
      return ((*a0).*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) volatile, A0 a0, A1 a1, A2 a2, A3 a3)
    {
      return ((*a0).*f)(a1, a2, a3);
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() const volatile, BOOST_THREAD_RV_REF(A0) a0)
    {
      return ((*boost::forward<A0>(a0)).*f)();
    }

    template <class Ret, class A, class A0>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)() const volatile, A0 a0)
    {
      return ((*a0).*f)();
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1));
    }

    template <class Ret, class A, class A0, class A1>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1) const volatile, A0 a0, A1 a1)
    {
      return ((*a0).*f)(a1);
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A, class A0, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2) const volatile,
        A0 a0, A1 a1, A2 a2)
    {
      return ((*a0).*f)(a1, a2);
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const volatile,
        BOOST_THREAD_RV_REF(A0) a0, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return ((*boost::forward<A0>(a0)).*f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class A, class A0, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_base_of<A, typename remove_reference<A0>::type>::value,
        Ret
    >::type
    invoke(Ret (A::*f)(A1, A2, A3) const volatile,
        A0 a0, A1 a1, A2 a2, A3 a3)
    {
      return ((*a0).*f)(a1, a2, a3);
    }


    template <class Ret, class Fp>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f)
    {
      return boost::forward<Fp>(f)();
    }

    template <class Ret, class Fp, class A1>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, BOOST_THREAD_RV_REF(A1) a1)
    {
      return boost::forward<Fp>(f)(boost::forward<A1>(a1));
    }

    template <class Ret, class Fp, class A1>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, A1 a1)
    {
      return boost::forward<Fp>(f)(a1);
    }

    template <class Ret, class Fp, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return boost::forward<Fp>(f)(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class Fp, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, A1 a1, A2 a2)
    {
      return boost::forward<Fp>(f)(a1, a2);
    }

    template <class Ret, class Fp, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return boost::forward<Fp>(f)(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class Fp, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(BOOST_THREAD_RV_REF(Fp) f, A1 a1, A2 a2, A3 a3)
    {
      return boost::forward<Fp>(f)(a1, a2, a3);
    }

    template <class Ret, class Fp>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f)
    {
      return f();
    }

    template <class Ret, class Fp, class A1>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, BOOST_THREAD_RV_REF(A1) a1)
    {
      return f(boost::forward<A1>(a1));
    }

    template <class Ret, class Fp, class A1>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, A1 a1)
    {
      return f(a1);
    }

    template <class Ret, class Fp, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return f(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class Fp, class A1, class A2>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, A1 a1, A2 a2)
    {
      return f(a1, a2);
    }

    template <class Ret, class Fp, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return f(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }

    template <class Ret, class Fp, class A1, class A2, class A3>
    inline
    typename enable_if_c
    <
        ! is_member_function_pointer<Fp>::value,
        Ret
    >::type
    invoke(Fp const &f, A1 a1, A2 a2, A3 a3)
    {
      return f(a1, a2, a3);
    }


    template <class Ret>
    inline Ret
    invoke(Ret(*f)())
    {
      return f();
    }

    template <class Ret, class A1>
    inline Ret
    invoke(Ret(*f)(A1), BOOST_THREAD_RV_REF(A1) a1)
    {
      return f(boost::forward<A1>(a1));
    }

    template <class Ret, class A1, class A2>
    inline Ret
    invoke(Ret(*f)(A1, A2),
        BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2)
    {
      return f(boost::forward<A1>(a1), boost::forward<A2>(a2));
    }

    template <class Ret, class A1, class A2, class A3>
    inline Ret
    invoke(Ret(*f)(A1, A2, A3),
        BOOST_THREAD_RV_REF(A1) a1, BOOST_THREAD_RV_REF(A2) a2, BOOST_THREAD_RV_REF(A3) a3)
    {
      return f(boost::forward<A1>(a1), boost::forward<A2>(a2), boost::forward<A3>(a3));
    }


      counter(std::size_t value)
      : value_(value)
      {

      }

      counter& operator=(counter const& rhs)
      {
        value_ = rhs.value_;
        return *this;
      }

      counter_is_not_zero(const counter& count) : count_(count) {}

      bool operator()() const { return count_ != 0; }

      counter_is_zero(const counter& count) : count_(count) {}

      bool operator()() const { return count_ == 0; }

            explicit thread_move_t(T& t_):
                t(t_)
            {}


            T& operator*() const
            {
                return t;
            }


            T* operator->() const
            {
                return &t;
            }

    template<typename T>
    typename enable_if<boost::is_convertible<T&,boost::detail::thread_move_t<T> >, boost::detail::thread_move_t<T> >::type move(T& t)
    {
        return boost::detail::thread_move_t<T>(t);
    }


    template<typename T>
    boost::detail::thread_move_t<T> move(boost::detail::thread_move_t<T> t)
    {
        return t;
    }

  template <typename T>
  BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type)
  make_rv_ref(T v)  BOOST_NOEXCEPT
  {
    return (BOOST_THREAD_RV_REF(typename ::boost::remove_cv<typename ::boost::remove_reference<T>::type>::type))(v);
  }

  template <class T>
  typename decay<T>::type
  decay_copy(BOOST_THREAD_FWD_REF(T) t)
  {
      return boost::forward<T>(t);
  }



template <class T>
inline singleton<T>::singleton()
{
    /* no-op */
}


template <class T>
inline singleton<T>::~singleton()
{
    /* no-op */
}


template <class T>
/*static*/ T &singleton<T>::instance()
{
    // function-local static to force this to work correctly at static
    // initialization time.
    static singleton<T> s_oT;
    return(s_oT);
}

      allocator_destructor(_Alloc& a, size_type s)BOOST_NOEXCEPT
      : alloc_(a), s_(s)
      {}

      void operator()(pointer p)BOOST_NOEXCEPT
      {
        alloc_traits::destroy(alloc_, p);
        alloc_traits::deallocate(alloc_, p, s_);
      }




    template <class U>
    BOOST_SYMBOL_VISIBLE
    void operator() (U* ptr,
                     typename enable_if<thread_detail::same_or_less_cv_qualified<U*, T*> >::type* = 0) const BOOST_NOEXCEPT
    {
      BOOST_STATIC_ASSERT_MSG(sizeof(T) > 0, "default_delete can not delete incomplete type");
      delete [] ptr;
    }

template<class Return_Type, class Argument_Type>
inline Return_Type &force_cast(Argument_Type &rSrc)
{
    return(*reinterpret_cast<Return_Type *>(&rSrc));
}

template<class Return_Type, class Argument_Type>
inline const Return_Type &force_cast(const Argument_Type &rSrc)
{
    return(*reinterpret_cast<const Return_Type *>(&rSrc));
}

        thread_group() {}

        ~thread_group()
        {
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
                delete *it;
            }
        }


        bool is_this_thread_in()
        {
            thread::id id = this_thread::get_id();
            boost::shared_lock<shared_mutex> guard(m);
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->get_id() == id)
                return true;
            }
            return false;
        }


        bool is_thread_in(thread* thrd)
        {
          if(thrd)
          {
            thread::id id = thrd->get_id();
            boost::shared_lock<shared_mutex> guard(m);
            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->get_id() == id)
                return true;
            }
            return false;
          }
          else
          {
            return false;
          }
        }


        template<typename F>
        thread* create_thread(F threadfunc)
        {
            boost::lock_guard<shared_mutex> guard(m);
            std::auto_ptr<thread> new_thread(new thread(threadfunc));
            threads.push_back(new_thread.get());
            return new_thread.release();
        }


        void add_thread(thread* thrd)
        {
            if(thrd)
            {
                BOOST_THREAD_ASSERT_PRECONDITION( ! is_thread_in(thrd) ,
                    thread_resource_error(system::errc::resource_deadlock_would_occur, "boost::thread_group: trying to add a duplicated thread")
                );

                boost::lock_guard<shared_mutex> guard(m);
                threads.push_back(thrd);
            }
        }


        void remove_thread(thread* thrd)
        {
            boost::lock_guard<shared_mutex> guard(m);
            std::list<thread*>::iterator const it=std::find(threads.begin(),threads.end(),thrd);
            if(it!=threads.end())
            {
                threads.erase(it);
            }
        }


        void join_all()
        {
            BOOST_THREAD_ASSERT_PRECONDITION( ! is_this_thread_in() ,
                thread_resource_error(system::errc::resource_deadlock_would_occur, "boost::thread_group: trying joining itself")
            );
            boost::shared_lock<shared_mutex> guard(m);

            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
              if ((*it)->joinable())
                (*it)->join();
            }
        }

        void interrupt_all()
        {
            boost::shared_lock<shared_mutex> guard(m);

            for(std::list<thread*>::iterator it=threads.begin(),end=threads.end();
                it!=end;
                ++it)
            {
                (*it)->interrupt();
            }
        }


        size_t size() const
        {
            boost::shared_lock<shared_mutex> guard(m);
            return threads.size();
        }


        bool do_wait_for(
            unique_lock<mutex>& lock,
            struct timespec const &timeout)
        {
          return do_wait_until(lock, boost::detail::timespec_plus(timeout, boost::detail::timespec_now()));
        }

        condition_variable()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            int const res=pthread_mutex_init(&internal_mutex,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost::condition_variable::condition_variable() constructor failed in pthread_mutex_init"));
            }
#endif
            int const res2=pthread_cond_init(&cond,NULL);
            if(res2)
            {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                BOOST_VERIFY(!pthread_mutex_destroy(&internal_mutex));
#endif
                boost::throw_exception(thread_resource_error(res2, "boost::condition_variable::condition_variable() constructor failed in pthread_cond_init"));
            }
        }

        ~condition_variable()
        {
            int ret;
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            do {
              ret = pthread_mutex_destroy(&internal_mutex);
            } while (ret == EINTR);
            BOOST_ASSERT(!ret);
#endif
            do {
              ret = pthread_cond_destroy(&cond);
            } while (ret == EINTR);
            BOOST_ASSERT(!ret);
        }

        inline bool timed_wait(
            unique_lock<mutex>& m,
            boost::system_time const& wait_until)
        {
#if defined BOOST_THREAD_WAIT_BUG
            struct timespec const timeout=detail::to_timespec(wait_until + BOOST_THREAD_WAIT_BUG);
            return do_wait_until(m, timeout);
#else
            struct timespec const timeout=detail::to_timespec(wait_until);
            return do_wait_until(m, timeout);
#endif
        }


        template <class Duration>
        cv_status
        wait_until(
                unique_lock<mutex>& lock,
                const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
          wait_until(lock,
                        nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
          return system_clock::now() < t ? cv_status::no_timeout :
                                             cv_status::timeout;
        }



        template <class Rep, class Period>
        cv_status
        wait_for(
                unique_lock<mutex>& lock,
                const chrono::duration<Rep, Period>& d)
        {
          using namespace chrono;
          system_clock::time_point s_now = system_clock::now();
          steady_clock::time_point c_now = steady_clock::now();
          wait_until(lock, s_now + ceil<nanoseconds>(d));
          return steady_clock::now() - c_now < d ? cv_status::no_timeout :
                                                   cv_status::timeout;

        }

        native_handle_type native_handle()
        {
            return &cond;
        }

        thread_attributes() BOOST_NOEXCEPT {
            int res = pthread_attr_init(&val_);
            BOOST_VERIFY(!res && "pthread_attr_init failed");
        }

        ~thread_attributes() {
          int res = pthread_attr_destroy(&val_);
          BOOST_VERIFY(!res && "pthread_attr_destroy failed");
        }

        void set_stack_size(std::size_t size) BOOST_NOEXCEPT {
          if (size==0) return;
          std::size_t page_size = getpagesize();
#ifdef PTHREAD_STACK_MIN
          if (size<PTHREAD_STACK_MIN) size=PTHREAD_STACK_MIN;
#endif
          size = ((size+page_size-1)/page_size)*page_size;
          int res = pthread_attr_setstacksize(&val_, size);
          BOOST_VERIFY(!res && "pthread_attr_setstacksize failed");
        }


        std::size_t get_stack_size() const BOOST_NOEXCEPT {
            std::size_t size;
            int res = pthread_attr_getstacksize(&val_, &size);
            BOOST_VERIFY(!res && "pthread_attr_getstacksize failed");
            return size;
        }

        native_handle_type* native_handle() BOOST_NOEXCEPT {
          return &val_;
        }

        const native_handle_type* native_handle() const BOOST_NOEXCEPT {
          return &val_;
        }


            tss_data_node(boost::shared_ptr<boost::detail::tss_cleanup_function> func_,
                          void* value_):
                func(func_),value(value_)
            {}

            thread_data_base():
                thread_handle(0),
                done(false),join_started(false),joined(false),
                thread_exit_callbacks(0),
                cond_mutex(0),
                current_cond(0),
                notify(),
                async_states_()
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                , interrupt_enabled(true)
                , interrupt_requested(false)
//#endif
            {}

            virtual void notify_all_at_thread_exit(condition_variable* cv, mutex* m)
            {
              notify.push_back(std::pair<condition_variable*, mutex*>(cv, m));
            }


            void make_ready_at_thread_exit(shared_ptr<future_object_base> as)
            {
              async_states_.push_back(as);
            }


            void check_for_interruption()
            {
#ifndef BOOST_NO_EXCEPTIONS
                if(thread_info->interrupt_requested)
                {
                    thread_info->interrupt_requested=false;
                    throw thread_interrupted(); // BOOST_NO_EXCEPTIONS protected
                }
#endif
            }

            explicit interruption_checker(pthread_mutex_t* cond_mutex,pthread_cond_t* cond):
                thread_info(detail::get_current_thread_data()),m(cond_mutex),
                set(thread_info && thread_info->interrupt_enabled)
            {
                if(set)
                {
                    lock_guard<mutex> guard(thread_info->data_mutex);
                    check_for_interruption();
                    thread_info->cond_mutex=cond_mutex;
                    thread_info->current_cond=cond;
                    BOOST_VERIFY(!pthread_mutex_lock(m));
                }
                else
                {
                    BOOST_VERIFY(!pthread_mutex_lock(m));
                }
            }

            ~interruption_checker()
            {
                if(set)
                {
                    BOOST_VERIFY(!pthread_mutex_unlock(m));
                    lock_guard<mutex> guard(thread_info->data_mutex);
                    thread_info->cond_mutex=NULL;
                    thread_info->current_cond=NULL;
                }
                else
                {
                    BOOST_VERIFY(!pthread_mutex_unlock(m));
                }
            }

        inline void sleep(system_time const& abs_time)
        {
          return boost::this_thread::hiden::sleep_until(boost::detail::to_timespec(abs_time));
        }


        template<typename TimeDuration>
        inline BOOST_SYMBOL_VISIBLE void sleep(TimeDuration const& rel_time)
        {
            this_thread::sleep(get_system_time()+rel_time);
        }


            lock_on_exit():
                m(0)
            {}


            void activate(MutexType& m_)
            {
                m_.unlock();
                m=&m_;
            }

            ~lock_on_exit()
            {
                if(m)
                {
                    m->lock();
                }
           }


    inline void condition_variable::notify_one() BOOST_NOEXCEPT
    {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
        boost::pthread::pthread_mutex_scoped_lock internal_lock(&internal_mutex);
#endif
        BOOST_VERIFY(!pthread_cond_signal(&cond));
    }


    inline void condition_variable::notify_all() BOOST_NOEXCEPT
    {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
        boost::pthread::pthread_mutex_scoped_lock internal_lock(&internal_mutex);
#endif
        BOOST_VERIFY(!pthread_cond_broadcast(&cond));
    }

        condition_variable_any()
        {
            int const res=pthread_mutex_init(&internal_mutex,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost::condition_variable_any::condition_variable_any() failed in pthread_mutex_init"));
            }
            int const res2=pthread_cond_init(&cond,NULL);
            if(res2)
            {
                BOOST_VERIFY(!pthread_mutex_destroy(&internal_mutex));
                boost::throw_exception(thread_resource_error(res, "boost::condition_variable_any::condition_variable_any() failed in pthread_cond_init"));
            }
        }

        ~condition_variable_any()
        {
            BOOST_VERIFY(!pthread_mutex_destroy(&internal_mutex));
            BOOST_VERIFY(!pthread_cond_destroy(&cond));
        }


        template<typename lock_type>
        void wait(lock_type& m)
        {
            int res=0;
            {
                thread_cv_detail::lock_on_exit<lock_type> guard;
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                detail::interruption_checker check_for_interruption(&internal_mutex,&cond);
#else
            boost::pthread::pthread_mutex_scoped_lock check_for_interruption(&internal_mutex);
#endif
                guard.activate(m);
                res=pthread_cond_wait(&cond,&internal_mutex);
            }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            this_thread::interruption_point();
#endif
            if(res)
            {
                boost::throw_exception(condition_error(res, "boost::condition_variable_any::wait() failed in pthread_cond_wait"));
            }
        }


        template<typename lock_type,typename predicate_type>
        void wait(lock_type& m,predicate_type pred)
        {
            while(!pred()) wait(m);
        }

        template<typename lock_type>
        bool timed_wait(lock_type& m,boost::system_time const& wait_until)
        {
            struct timespec const timeout=detail::to_timespec(wait_until);
            return do_wait_until(m, timeout);
        }

        template<typename lock_type>
        bool timed_wait(lock_type& m,xtime const& wait_until)
        {
            return timed_wait(m,system_time(wait_until));
        }


        template<typename lock_type,typename duration_type>
        bool timed_wait(lock_type& m,duration_type const& wait_duration)
        {
            return timed_wait(m,get_system_time()+wait_duration);
        }


        template<typename lock_type,typename predicate_type>
        bool timed_wait(lock_type& m,boost::system_time const& wait_until,predicate_type pred)
        {
            while (!pred())
            {
                if(!timed_wait(m, wait_until))
                    return pred();
            }
            return true;
        }


        template<typename lock_type,typename predicate_type>
        bool timed_wait(lock_type& m,xtime const& wait_until,predicate_type pred)
        {
            return timed_wait(m,system_time(wait_until),pred);
        }


        template<typename lock_type,typename duration_type,typename predicate_type>
        bool timed_wait(lock_type& m,duration_type const& wait_duration,predicate_type pred)
        {
            return timed_wait(m,get_system_time()+wait_duration,pred);
        }

        template <class lock_type,class Duration>
        cv_status
        wait_until(
                lock_type& lock,
                const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
          wait_until(lock,
                        nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
          return system_clock::now() < t ? cv_status::no_timeout :
                                             cv_status::timeout;
        }


        template <class lock_type, class Clock, class Duration>
        cv_status
        wait_until(
                lock_type& lock,
                const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          typename Clock::time_point  c_now = Clock::now();
          wait_until(lock, s_now + ceil<nanoseconds>(t - c_now));
          return Clock::now() < t ? cv_status::no_timeout : cv_status::timeout;
        }


        template <class lock_type, class Clock, class Duration, class Predicate>
        bool
        wait_until(
                lock_type& lock,
                const chrono::time_point<Clock, Duration>& t,
                Predicate pred)
        {
            while (!pred())
            {
                if (wait_until(lock, t) == cv_status::timeout)
                    return pred();
            }
            return true;
        }



        template <class lock_type, class Rep, class Period>
        cv_status
        wait_for(
                lock_type& lock,
                const chrono::duration<Rep, Period>& d)
        {
          using namespace chrono;
          system_clock::time_point s_now = system_clock::now();
          steady_clock::time_point c_now = steady_clock::now();
          wait_until(lock, s_now + ceil<nanoseconds>(d));
          return steady_clock::now() - c_now < d ? cv_status::no_timeout :
                                                   cv_status::timeout;

        }



        template <class lock_type, class Rep, class Period, class Predicate>
        bool
        wait_for(
                lock_type& lock,
                const chrono::duration<Rep, Period>& d,
                Predicate pred)
        {
          return wait_until(lock, chrono::steady_clock::now() + d, boost::move(pred));

//          while (!pred())
//          {
//              if (wait_for(lock, d) == cv_status::timeout)
//                  return pred();
//          }
//          return true;
        }


        template <class lock_type>
        cv_status wait_until(
            lock_type& lk,
            chrono::time_point<chrono::system_clock, chrono::nanoseconds> tp)
        {
            using namespace chrono;
            nanoseconds d = tp.time_since_epoch();
            timespec ts = boost::detail::to_timespec(d);
            if (do_wait_until(lk, ts)) return cv_status::no_timeout;
            else return cv_status::timeout;
        }


        void notify_one() BOOST_NOEXCEPT
        {
            boost::pthread::pthread_mutex_scoped_lock internal_lock(&internal_mutex);
            BOOST_VERIFY(!pthread_cond_signal(&cond));
        }


        void notify_all() BOOST_NOEXCEPT
        {
            boost::pthread::pthread_mutex_scoped_lock internal_lock(&internal_mutex);
            BOOST_VERIFY(!pthread_cond_broadcast(&cond));
        }


        template <class lock_type>
        inline bool do_wait_until(
          lock_type& m,
          struct timespec const &timeout)
        {
          int res=0;
          {
              thread_cv_detail::lock_on_exit<lock_type> guard;
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
              detail::interruption_checker check_for_interruption(&internal_mutex,&cond);
#else
            boost::pthread::pthread_mutex_scoped_lock check_for_interruption(&internal_mutex);
#endif
              guard.activate(m);
              res=pthread_cond_timedwait(&cond,&internal_mutex,&timeout);
          }
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          this_thread::interruption_point();
#endif
          if(res==ETIMEDOUT)
          {
              return false;
          }
          if(res)
          {
              boost::throw_exception(condition_error(res, "boost::condition_variable_any::do_wait_until() failed in pthread_cond_timedwait"));
          }
          return true;
        }

        recursive_mutex()
        {
#ifdef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
            pthread_mutexattr_t attr;

            int const init_attr_res=pthread_mutexattr_init(&attr);
            if(init_attr_res)
            {
                boost::throw_exception(thread_resource_error(init_attr_res, "boost:: recursive_mutex constructor failed in pthread_mutexattr_init"));
            }
            int const set_attr_res=pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
            if(set_attr_res)
            {
                BOOST_VERIFY(!pthread_mutexattr_destroy(&attr));
                boost::throw_exception(thread_resource_error(set_attr_res, "boost:: recursive_mutex constructor failed in pthread_mutexattr_settype"));
            }

            int const res=pthread_mutex_init(&m,&attr);
            if(res)
            {
                BOOST_VERIFY(!pthread_mutexattr_destroy(&attr));
                boost::throw_exception(thread_resource_error(res, "boost:: recursive_mutex constructor failed in pthread_mutex_init"));
            }
            BOOST_VERIFY(!pthread_mutexattr_destroy(&attr));
#else
            int const res=pthread_mutex_init(&m,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost:: recursive_mutex constructor failed in pthread_mutex_init"));
            }
            int const res2=pthread_cond_init(&cond,NULL);
            if(res2)
            {
                BOOST_VERIFY(!pthread_mutex_destroy(&m));
                boost::throw_exception(thread_resource_error(res2, "boost:: recursive_mutex constructor failed in pthread_cond_init"));
            }
            is_locked=false;
            count=0;
#endif
        }

        ~recursive_mutex()
        {
            BOOST_VERIFY(!pthread_mutex_destroy(&m));
#ifndef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
            BOOST_VERIFY(!pthread_cond_destroy(&cond));
#endif
        }

        void lock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked && pthread_equal(owner,pthread_self()))
            {
                ++count;
                return;
            }

            while(is_locked)
            {
                BOOST_VERIFY(!pthread_cond_wait(&cond,&m));
            }
            is_locked=true;
            ++count;
            owner=pthread_self();
        }


        void unlock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(!--count)
            {
                is_locked=false;
            }
            BOOST_VERIFY(!pthread_cond_signal(&cond));
        }


        bool try_lock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked && !pthread_equal(owner,pthread_self()))
            {
                return false;
            }
            is_locked=true;
            ++count;
            owner=pthread_self();
            return true;
        }

        recursive_timed_mutex()
        {
#ifdef BOOST_USE_PTHREAD_RECURSIVE_TIMEDLOCK
            pthread_mutexattr_t attr;

            int const init_attr_res=pthread_mutexattr_init(&attr);
            if(init_attr_res)
            {
                boost::throw_exception(thread_resource_error(init_attr_res, "boost:: recursive_timed_mutex constructor failed in pthread_mutexattr_init"));
            }
            int const set_attr_res=pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
            if(set_attr_res)
            {
                boost::throw_exception(thread_resource_error(set_attr_res, "boost:: recursive_timed_mutex constructor failed in pthread_mutexattr_settype"));
            }

            int const res=pthread_mutex_init(&m,&attr);
            if(res)
            {
                BOOST_VERIFY(!pthread_mutexattr_destroy(&attr));
                boost::throw_exception(thread_resource_error(res, "boost:: recursive_timed_mutex constructor failed in pthread_mutex_init"));
            }
            BOOST_VERIFY(!pthread_mutexattr_destroy(&attr));
#else
            int const res=pthread_mutex_init(&m,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost:: recursive_timed_mutex constructor failed in pthread_mutex_init"));
            }
            int const res2=pthread_cond_init(&cond,NULL);
            if(res2)
            {
                BOOST_VERIFY(!pthread_mutex_destroy(&m));
                boost::throw_exception(thread_resource_error(res2, "boost:: recursive_timed_mutex constructor failed in pthread_cond_init"));
            }
            is_locked=false;
            count=0;
#endif
        }

        ~recursive_timed_mutex()
        {
            BOOST_VERIFY(!pthread_mutex_destroy(&m));
#ifndef BOOST_USE_PTHREAD_RECURSIVE_TIMEDLOCK
            BOOST_VERIFY(!pthread_cond_destroy(&cond));
#endif
        }

        template<typename TimeDuration>
        bool timed_lock(TimeDuration const & relative_time)
        {
            return timed_lock(get_system_time()+relative_time);
        }

        void lock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked && pthread_equal(owner,pthread_self()))
            {
                ++count;
                return;
            }

            while(is_locked)
            {
                BOOST_VERIFY(!pthread_cond_wait(&cond,&m));
            }
            is_locked=true;
            ++count;
            owner=pthread_self();
        }


        void unlock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(!--count)
            {
                is_locked=false;
            }
            BOOST_VERIFY(!pthread_cond_signal(&cond));
        }


        bool try_lock() BOOST_NOEXCEPT
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked && !pthread_equal(owner,pthread_self()))
            {
                return false;
            }
            is_locked=true;
            ++count;
            owner=pthread_self();
            return true;
        }

        bool do_try_lock_until(struct timespec const &timeout)
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked && pthread_equal(owner,pthread_self()))
            {
                ++count;
                return true;
            }
            while(is_locked)
            {
                int const cond_res=pthread_cond_timedwait(&cond,&m,&timeout);
                if(cond_res==ETIMEDOUT)
                {
                    return false;
                }
                BOOST_ASSERT(!cond_res);
            }
            is_locked=true;
            ++count;
            owner=pthread_self();
            return true;
        }

        bool timed_lock(system_time const & abs_time)
        {
            struct timespec const ts=detail::to_timespec(abs_time);
            return do_try_lock_until(ts);
        }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          typename Clock::time_point  c_now = Clock::now();
          return try_lock_until(s_now + ceil<nanoseconds>(t - c_now));
        }

        template <class Duration>
        bool try_lock_until(const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
          return try_lock_until(nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
        }

        bool try_lock_until(const chrono::time_point<chrono::system_clock, chrono::nanoseconds>& tp)
        {
          //using namespace chrono;
          chrono::nanoseconds d = tp.time_since_epoch();
          timespec ts = boost::detail::to_timespec(d);
          return do_try_lock_until(ts);
        }

        native_handle_type native_handle()
        {
            return &m;
        }

        template<typename T>
        inline T* heap_new()
        {
            return new T();
        }

        template<typename T,typename A1>
        inline T* heap_new_impl(A1 a1)
        {
            return new T(a1);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new_impl(A1 a1,A2 a2)
        {
            return new T(a1,a2);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new_impl(A1 a1,A2 a2,A3 a3)
        {
            return new T(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new_impl(A1 a1,A2 a2,A3 a3,A4 a4)
        {
            return new T(a1,a2,a3,a4);
        }


        template<typename T,typename A1>
        inline T* heap_new(A1 const& a1)
        {
            return heap_new_impl<T,A1 const&>(a1);
        }

        template<typename T,typename A1>
        inline T* heap_new(A1& a1)
        {
            return heap_new_impl<T,A1&>(a1);
        }


        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1 const& a1,A2 const& a2)
        {
            return heap_new_impl<T,A1 const&,A2 const&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1& a1,A2 const& a2)
        {
            return heap_new_impl<T,A1&,A2 const&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1 const& a1,A2& a2)
        {
            return heap_new_impl<T,A1 const&,A2&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1& a1,A2& a2)
        {
            return heap_new_impl<T,A1&,A2&>(a1,a2);
        }


        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&>(a1,a2,a3);
        }


        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2& a2,A3& a3)
        {
            return heap_new_impl<T,A1&,A2&,A3&>(a1,a2,a3);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&,A4&>(a1,a2,a3,a4);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T>
        inline void heap_delete(T* data)
        {
            delete data;
        }

            void operator()(T* data) const
            {
                detail::heap_delete(data);
            }

            explicit pthread_mutex_scoped_lock(pthread_mutex_t* m_):
                m(m_),locked(true)
            {
                BOOST_VERIFY(!pthread_mutex_lock(m));
            }

            void unlock()
            {
                BOOST_VERIFY(!pthread_mutex_unlock(m));
                locked=false;
            }

            
            ~pthread_mutex_scoped_lock()
            {
                if(locked)
                {
                    unlock();
                }
            }

            explicit pthread_mutex_scoped_unlock(pthread_mutex_t* m_):
                m(m_)
            {
                BOOST_VERIFY(!pthread_mutex_unlock(m));
            }

            ~pthread_mutex_scoped_unlock()
            {
                BOOST_VERIFY(!pthread_mutex_lock(m));
            }

    inline atomic_type& get_atomic_storage(once_flag& flag) BOOST_NOEXCEPT
    {
      return reinterpret_cast< atomic_type& >(flag.storage);
    }

  template<typename Function>
  inline void call_once(once_flag& flag, Function f)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        f();
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }


  template<typename Function, typename T1>
  inline void call_once(once_flag& flag, Function f, T1 p1)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(f, p1) BOOST_THREAD_INVOKE_RET_VOID_CALL;
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }


  template<typename Function, typename T1, typename T2>
  inline void call_once(once_flag& flag, Function f, T1 p1, T2 p2)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(f, p1, p2) BOOST_THREAD_INVOKE_RET_VOID_CALL;
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }


  template<typename Function, typename T1, typename T2, typename T3>
  inline void call_once(once_flag& flag, Function f, T1 p1, T2 p2, T3 p3)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(f, p1, p2, p3) BOOST_THREAD_INVOKE_RET_VOID_CALL;
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }


  template<typename Function>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        f();
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }


  template<typename Function, typename T1>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(
            thread_detail::decay_copy(boost::forward<Function>(f)),
            thread_detail::decay_copy(boost::forward<T1>(p1))
        ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }

  template<typename Function, typename T1, typename T2>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(
            thread_detail::decay_copy(boost::forward<Function>(f)),
            thread_detail::decay_copy(boost::forward<T1>(p1)),
            thread_detail::decay_copy(boost::forward<T1>(p2))
        ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }

  template<typename Function, typename T1, typename T2, typename T3>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2, BOOST_THREAD_RV_REF(T3) p3)
  {
    if (thread_detail::enter_once_region(flag))
    {
      BOOST_TRY
      {
        BOOST_THREAD_INVOKE_RET_VOID(
            thread_detail::decay_copy(boost::forward<Function>(f)),
            thread_detail::decay_copy(boost::forward<T1>(p1)),
            thread_detail::decay_copy(boost::forward<T1>(p2)),
            thread_detail::decay_copy(boost::forward<T1>(p3))
        ) BOOST_THREAD_INVOKE_RET_VOID_CALL;

      }
      BOOST_CATCH (...)
      {
        thread_detail::rollback_once_region(flag);
        BOOST_RETHROW
      }
      BOOST_CATCH_END
      thread_detail::commit_once_region(flag);
    }
  }

            state_data () :
              shared_count(0),
              exclusive(false),
              upgrade(false),
              exclusive_waiting_blocked(false)
            {}


            void assert_free() const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT( ! upgrade );
                BOOST_ASSERT( shared_count==0 );
            }


            void assert_locked() const
            {
                BOOST_ASSERT( exclusive );
                BOOST_ASSERT( shared_count==0 );
                BOOST_ASSERT( ! upgrade );
            }


            void assert_lock_shared () const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT( shared_count>0 );
                //BOOST_ASSERT( (! upgrade) || (shared_count>1));
                // if upgraded there are at least 2 threads sharing the mutex,
                // except when unlock_upgrade_and_lock has decreased the number of readers but has not taken yet exclusive ownership.
            }


            void assert_lock_upgraded () const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT(  upgrade );
                BOOST_ASSERT(  shared_count>0 );
            }


            void assert_lock_not_upgraded () const
            {
                BOOST_ASSERT(  ! upgrade );
            }


            bool can_lock () const
            {
                return ! (shared_count || exclusive);
            }


            void exclusive_blocked (bool blocked)
            {
                exclusive_waiting_blocked = blocked;
            }


            void lock ()
            {
                exclusive = true;
            }


            void unlock ()
            {
                exclusive = false;
                exclusive_waiting_blocked = false;
            }


            bool can_lock_shared () const
            {
                return ! (exclusive || exclusive_waiting_blocked);
            }


            bool more_shared () const
            {
                return shared_count > 0 ;
            }

            unsigned get_shared_count () const
            {
                return shared_count ;
            }

            unsigned  lock_shared ()
            {
                return ++shared_count;
            }



            void unlock_shared ()
            {
                --shared_count;
            }


            bool unlock_shared_downgrades()
            {
                  if (upgrade) {
                      upgrade=false;
                      exclusive=true;
                      return true;
                  } else {
                      exclusive_waiting_blocked=false;
                      return false;
                  }
            }


            void lock_upgrade ()
            {
                ++shared_count;
                upgrade=true;
            }

            bool can_lock_upgrade () const
            {
                return ! (exclusive || exclusive_waiting_blocked || upgrade);
            }


            void unlock_upgrade ()
            {
                upgrade=false;
                --shared_count;
            }


        void release_waiters()
        {
            exclusive_cond.notify_one();
            shared_cond.notify_all();
        }


        shared_mutex()
        {
        }


        ~shared_mutex()
        {
        }


        void lock_shared()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            while(!state.can_lock_shared())
            {
                shared_cond.wait(lk);
            }
            state.lock_shared();
        }


        bool try_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);

            if(!state.can_lock_shared())
            {
                return false;
            }
            state.lock_shared();
            return true;
        }

        bool timed_lock_shared(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(!state.can_lock_shared())
            {
                if(!shared_cond.timed_wait(lk,timeout))
                {
                    return false;
                }
            }
            state.lock_shared();
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock_shared(TimeDuration const & relative_time)
        {
            return timed_lock_shared(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_shared_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_shared_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_shared_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);

          while(!state.can_lock_shared())
          //while(state.exclusive || state.exclusive_waiting_blocked)
          {
              if(cv_status::timeout==shared_cond.wait_until(lk,abs_time))
              {
                  return false;
              }
          }
          state.lock_shared();
          return true;
        }

        void unlock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_shared();
            state.unlock_shared();
            if (! state.more_shared())
            {
                if (state.upgrade)
                {
                    // As there is a thread doing a unlock_upgrade_and_lock that is waiting for ! state.more_shared()
                    // avoid other threads to lock, lock_upgrade or lock_shared, so only this thread is notified.
                    state.upgrade=false;
                    state.exclusive=true;
                    lk.unlock();
                    upgrade_cond.notify_one();
                }
                else
                {
                    state.exclusive_waiting_blocked=false;
                    lk.unlock();
                }
                release_waiters();
            }
        }


        void lock()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while (state.shared_count || state.exclusive)
            {
                state.exclusive_waiting_blocked=true;
                exclusive_cond.wait(lk);
            }
            state.exclusive=true;
        }

        bool timed_lock(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(state.shared_count || state.exclusive)
            {
                state.exclusive_waiting_blocked=true;
                if(!exclusive_cond.timed_wait(lk,timeout))
                {
                    if(state.shared_count || state.exclusive)
                    {
                        state.exclusive_waiting_blocked=false;
                        release_waiters();
                        return false;
                    }
                    break;
                }
            }
            state.exclusive=true;
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock(TimeDuration const & relative_time)
        {
            return timed_lock(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);

          while(state.shared_count || state.exclusive)
          {
              state.exclusive_waiting_blocked=true;
              if(cv_status::timeout == exclusive_cond.wait_until(lk,abs_time))
              {
                  if(state.shared_count || state.exclusive)
                  {
                      state.exclusive_waiting_blocked=false;
                      release_waiters();
                      return false;
                  }
                  break;
              }
          }
          state.exclusive=true;
          return true;
        }


        bool try_lock()
        {
            boost::unique_lock<boost::mutex> lk(state_change);

            if(state.shared_count || state.exclusive)
            {
                return false;
            }
            else
            {
                state.exclusive=true;
                return true;
            }

        }


        void unlock()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.exclusive=false;
            state.exclusive_waiting_blocked=false;
            state.assert_free();
            release_waiters();
        }


        void lock_upgrade()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            while(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
            {
                shared_cond.wait(lk);
            }
            state.lock_shared();
            state.upgrade=true;
        }

        bool timed_lock_upgrade(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            while(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
            {
                if(!shared_cond.timed_wait(lk,timeout))
                {
                    if(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
                    {
                        return false;
                    }
                    break;
                }
            }
            state.lock_shared();
            state.upgrade=true;
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock_upgrade(TimeDuration const & relative_time)
        {
            return timed_lock_upgrade(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_upgrade_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_upgrade_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_upgrade_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);
          while(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
          {
              if(cv_status::timeout == shared_cond.wait_until(lk,abs_time))
              {
                  if(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
                  {
                      return false;
                  }
                  break;
              }
          }
          state.lock_shared();
          state.upgrade=true;
          return true;
        }

        bool try_lock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            if(state.exclusive || state.exclusive_waiting_blocked || state.upgrade)
            {
                return false;
            }
            else
            {
                state.lock_shared();
                state.upgrade=true;
                state.assert_lock_upgraded();
                return true;
            }
        }


        void unlock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            //state.upgrade=false;
            state.unlock_upgrade();
            if(! state.more_shared() )
            {
                state.exclusive_waiting_blocked=false;
                release_waiters();
            } else {
                shared_cond.notify_all();
            }
        }

        void unlock_upgrade_and_lock()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_upgraded();
            state.unlock_shared();
            while (state.more_shared())
            {
                upgrade_cond.wait(lk);
            }
            state.upgrade=false;
            state.exclusive=true;
            state.assert_locked();
        }


        void unlock_and_lock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.exclusive=false;
            state.upgrade=true;
            state.lock_shared();
            state.exclusive_waiting_blocked=false;
            state.assert_lock_upgraded();
            release_waiters();
        }


        bool try_unlock_upgrade_and_lock()
        {
          boost::unique_lock<boost::mutex> lk(state_change);
          state.assert_lock_upgraded();
          if(    !state.exclusive
              && !state.exclusive_waiting_blocked
              && state.upgrade
              && state.shared_count==1)
          {
            state.shared_count=0;
            state.exclusive=true;
            state.upgrade=false;
            state.assert_locked();
            return true;
          }
          return false;
        }

        template <class Rep, class Period>
        bool
        try_unlock_upgrade_and_lock_for(
                                const chrono::duration<Rep, Period>& rel_time)
        {
          return try_unlock_upgrade_and_lock_until(
                                 chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool
        try_unlock_upgrade_and_lock_until(
                          const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);
          state.assert_lock_upgraded();
          if (state.shared_count != 1)
          {
              for (;;)
              {
                cv_status status = shared_cond.wait_until(lk,abs_time);
                if (state.shared_count == 1)
                  break;
                if(status == cv_status::timeout)
                  return false;
              }
          }
          state.upgrade=false;
          state.exclusive=true;
          state.exclusive_waiting_blocked=false;
          state.shared_count=0;
          return true;
        }

        void unlock_and_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.exclusive=false;
            state.lock_shared();
            state.exclusive_waiting_blocked=false;
            release_waiters();
        }

        void unlock_upgrade_and_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_upgraded();
            state.upgrade=false;
            state.exclusive_waiting_blocked=false;
            release_waiters();
        }





        mutex()
        {
            int const res=pthread_mutex_init(&m,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost:: mutex constructor failed in pthread_mutex_init"));
            }
        }

        ~mutex()
        {
          BOOST_VERIFY(!posix::pthread_mutex_destroy(&m));
        }


        void lock()
        {
            int res = posix::pthread_mutex_lock(&m);
            if (res)
            {
                boost::throw_exception(lock_error(res,"boost: mutex lock failed in pthread_mutex_lock"));
            }
        }


        void unlock()
        {
            int res = posix::pthread_mutex_unlock(&m);
            if (res)
            {
                boost::throw_exception(lock_error(res,"boost: mutex unlock failed in pthread_mutex_unlock"));
            }
        }


        bool try_lock()
        {
            int res;
            do
            {
                res = pthread_mutex_trylock(&m);
            } while (res == EINTR);
            if (res==EBUSY)
            {
                return false;
            }

            return !res;
        }

        native_handle_type native_handle()
        {
            return &m;
        }

        timed_mutex()
        {
            int const res=pthread_mutex_init(&m,NULL);
            if(res)
            {
                boost::throw_exception(thread_resource_error(res, "boost:: timed_mutex constructor failed in pthread_mutex_init"));
            }
#ifndef BOOST_PTHREAD_HAS_TIMEDLOCK
            int const res2=pthread_cond_init(&cond,NULL);
            if(res2)
            {
                BOOST_VERIFY(!posix::pthread_mutex_destroy(&m));
                //BOOST_VERIFY(!pthread_mutex_destroy(&m));
                boost::throw_exception(thread_resource_error(res2, "boost:: timed_mutex constructor failed in pthread_cond_init"));
            }
            is_locked=false;
#endif
        }

        ~timed_mutex()
        {
            BOOST_VERIFY(!posix::pthread_mutex_destroy(&m));
#ifndef BOOST_PTHREAD_HAS_TIMEDLOCK
            BOOST_VERIFY(!pthread_cond_destroy(&cond));
#endif
        }

        template<typename TimeDuration>
        bool timed_lock(TimeDuration const & relative_time)
        {
            return timed_lock(get_system_time()+relative_time);
        }

        bool timed_lock(boost::xtime const & absolute_time)
        {
            return timed_lock(system_time(absolute_time));
        }

        void lock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            while(is_locked)
            {
                BOOST_VERIFY(!pthread_cond_wait(&cond,&m));
            }
            is_locked=true;
        }


        void unlock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            is_locked=false;
            BOOST_VERIFY(!pthread_cond_signal(&cond));
        }


        bool try_lock()
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            if(is_locked)
            {
                return false;
            }
            is_locked=true;
            return true;
        }

        bool do_try_lock_until(struct timespec const &timeout)
        {
            boost::pthread::pthread_mutex_scoped_lock const local_lock(&m);
            while(is_locked)
            {
                int const cond_res=pthread_cond_timedwait(&cond,&m,&timeout);
                if(cond_res==ETIMEDOUT)
                {
                    return false;
                }
                BOOST_ASSERT(!cond_res);
            }
            is_locked=true;
            return true;
        }

        bool timed_lock(system_time const & abs_time)
        {
            struct timespec const ts=boost::detail::to_timespec(abs_time);
            return do_try_lock_until(ts);
        }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          typename Clock::time_point  c_now = Clock::now();
          return try_lock_until(s_now + ceil<nanoseconds>(t - c_now));
        }

        template <class Duration>
        bool try_lock_until(const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
          return try_lock_until(nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
        }

        bool try_lock_until(const chrono::time_point<chrono::system_clock, chrono::nanoseconds>& tp)
        {
          //using namespace chrono;
          chrono::nanoseconds d = tp.time_since_epoch();
          timespec ts = boost::detail::to_timespec(d);
          return do_try_lock_until(ts);
        }

        native_handle_type native_handle()
        {
            return &m;
        }

  template<typename Function>
  inline void call_once(once_flag& flag, Function f)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    f();
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }


  template<typename Function, typename T1>
  inline void call_once(once_flag& flag, Function f, T1 p1)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(f,p1) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }

  template<typename Function, typename T1, typename T2>
  inline void call_once(once_flag& flag, Function f, T1 p1, T2 p2)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(f,p1, p2) BOOST_THREAD_INVOKE_RET_VOID_CALL;
        }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }


  template<typename Function, typename T1, typename T2, typename T3>
  inline void call_once(once_flag& flag, Function f, T1 p1, T2 p2, T3 p3)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(f,p1, p2, p3) BOOST_THREAD_INVOKE_RET_VOID_CALL;
        }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }


  template<typename Function>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    f();
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }


  template<typename Function, typename T1>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(
                        thread_detail::decay_copy(boost::forward<Function>(f)),
                        thread_detail::decay_copy(boost::forward<T1>(p1))
                    ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }

  template<typename Function, typename T1, typename T2>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(
                        thread_detail::decay_copy(boost::forward<Function>(f)),
                        thread_detail::decay_copy(boost::forward<T1>(p1)),
                        thread_detail::decay_copy(boost::forward<T1>(p2))
                    ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }


  template<typename Function, typename T1, typename T2, typename T3>
  inline void call_once(once_flag& flag, BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2, BOOST_THREAD_RV_REF(T3) p3)
  {
    static thread_detail::uintmax_atomic_t const uninitialized_flag=BOOST_ONCE_INITIAL_FLAG_VALUE;
    static thread_detail::uintmax_atomic_t const being_initialized=uninitialized_flag+1;
    thread_detail::uintmax_atomic_t const epoch=flag.epoch;
    thread_detail::uintmax_atomic_t& this_thread_epoch=thread_detail::get_once_per_thread_epoch();

    if(epoch<this_thread_epoch)
    {
        pthread::pthread_mutex_scoped_lock lk(&thread_detail::once_epoch_mutex);

        while(flag.epoch<=being_initialized)
        {
            if(flag.epoch==uninitialized_flag)
            {
                flag.epoch=being_initialized;
                BOOST_TRY
                {
                    pthread::pthread_mutex_scoped_unlock relocker(&thread_detail::once_epoch_mutex);
                    BOOST_THREAD_INVOKE_RET_VOID(
                        thread_detail::decay_copy(boost::forward<Function>(f)),
                        thread_detail::decay_copy(boost::forward<T1>(p1)),
                        thread_detail::decay_copy(boost::forward<T1>(p2)),
                        thread_detail::decay_copy(boost::forward<T1>(p3))
                    ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH (...)
                {
                    flag.epoch=uninitialized_flag;
                    BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                flag.epoch=--thread_detail::once_global_epoch;
                BOOST_VERIFY(!pthread_cond_broadcast(&thread_detail::once_epoch_cv));
            }
            else
            {
                while(flag.epoch==being_initialized)
                {
                    BOOST_VERIFY(!pthread_cond_wait(&thread_detail::once_epoch_cv,&thread_detail::once_epoch_mutex));
                }
            }
        }
        this_thread_epoch=thread_detail::once_global_epoch;
    }
  }

    inline struct timespec to_timespec(boost::system_time const& abs_time)
    {
      struct timespec timeout = { 0,0};
      boost::posix_time::time_duration const time_since_epoch=abs_time-boost::posix_time::from_time_t(0);

      timeout.tv_sec=time_since_epoch.total_seconds();
      timeout.tv_nsec=(long)(time_since_epoch.fractional_seconds()*(1000000000l/time_since_epoch.ticks_per_second()));
      return timeout;
    }

    inline timespec to_timespec(chrono::nanoseconds const& ns)
    {
      struct timespec ts;
      ts.tv_sec = static_cast<long>(chrono::duration_cast<chrono::seconds>(ns).count());
      ts.tv_nsec = static_cast<long>((ns - chrono::duration_cast<chrono::seconds>(ns)).count());
      return ts;
    }

            state_data () :
              shared_count(0),
              exclusive(false),
              upgrade(false),
              exclusive_waiting_blocked(false)
            {}


            void assert_free() const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT( ! upgrade );
                BOOST_ASSERT( shared_count==0 );
            }


            void assert_locked() const
            {
                BOOST_ASSERT( exclusive );
                BOOST_ASSERT( shared_count==0 );
                BOOST_ASSERT( ! upgrade );
            }


            void assert_lock_shared () const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT( shared_count>0 );
                //BOOST_ASSERT( (! upgrade) || (shared_count>1));
                // if upgraded there are at least 2 threads sharing the mutex,
                // except when unlock_upgrade_and_lock has decreased the number of readers but has not taken yet exclusive ownership.
            }


            void assert_lock_upgraded () const
            {
                BOOST_ASSERT( ! exclusive );
                BOOST_ASSERT(  upgrade );
                BOOST_ASSERT(  shared_count>0 );
            }


            void assert_lock_not_upgraded () const
            {
                BOOST_ASSERT(  ! upgrade );
            }


            bool can_lock () const
            {
                return ! (shared_count || exclusive);
            }


            void exclusive_blocked (bool blocked)
            {
                exclusive_waiting_blocked = blocked;
            }


            void lock ()
            {
                exclusive = true;
            }


            void unlock ()
            {
                exclusive = false;
                exclusive_waiting_blocked = false;
            }


            bool can_lock_shared () const
            {
                return ! (exclusive || exclusive_waiting_blocked);
            }


            bool is_last_shared () const
            {
                return !shared_count ;
            }

            unsigned get_shared_count () const
            {
                return shared_count ;
            }

            unsigned  lock_shared ()
            {
                return ++shared_count;
            }



            void unlock_shared ()
            {
                --shared_count;
            }


            bool unlock_shared_downgrades()
            {
                  if (upgrade) {
                      upgrade=false;
                      exclusive=true;
                      return true;
                  } else {
                      exclusive_waiting_blocked=false;
                      return false;
                  }
            }


            void lock_upgrade ()
            {
                lock_shared ();
                upgrade=true;
            }

            bool can_lock_upgrade () const
            {
                return ! (exclusive || exclusive_waiting_blocked || upgrade);
            }


            void unlock_upgrade ()
            {
                upgrade=false;
                unlock_shared();
            }


        void release_waiters()
        {
            exclusive_cond.notify_one();
            shared_cond.notify_all();
        }


        shared_mutex()
        {
        }


        ~shared_mutex()
        {
        }


        void lock_shared()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(!state.can_lock_shared())
            {
                shared_cond.wait(lk);
            }
            state.lock_shared();
        }


        bool try_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            if(!state.can_lock_shared())
            {
                return false;
            }
            else
            {
                state.lock_shared();
                return true;
            }
        }

        bool timed_lock_shared(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(!state.can_lock_shared())
            {
                if(!shared_cond.timed_wait(lk,timeout))
                {
                    return false;
                }
            }
            state.lock_shared();
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock_shared(TimeDuration const & relative_time)
        {
            return timed_lock_shared(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_shared_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_shared_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_shared_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);

          while(!state.can_lock_shared())
          {
              if(cv_status::timeout==shared_cond.wait_until(lk,abs_time))
              {
                  return false;
              }
          }
          state.lock_shared();
          return true;
        }

        void unlock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_shared();
            state.unlock_shared();
            if (state.get_shared_count () == 0)
            {
              if (state.unlock_shared_downgrades())
              {
                lk.unlock();
                upgrade_cond.notify_one();
              } else {
                lk.unlock();
              }
              release_waiters();
            }
        }


        void lock()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(!state.can_lock())
            {
                state.exclusive_blocked(true);
                exclusive_cond.wait(lk);
            }
            state.lock();
        }

        bool timed_lock(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);

            while(!state.can_lock())
            {
                state.exclusive_blocked(true);
                if(!exclusive_cond.timed_wait(lk,timeout))
                {
                    if(!state.can_lock())
                    {
                        state.exclusive_blocked(false);
                        release_waiters();
                        return false;
                    }
                    break;
                }
            }
            state.exclusive=true;
            //state.lock();
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock(TimeDuration const & relative_time)
        {
            return timed_lock(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);

          while(!state.can_lock())
          {
              state.exclusive_blocked(true);
              if(cv_status::timeout == exclusive_cond.wait_until(lk,abs_time))
              {
                  if(!state.can_lock())
                  {
                      state.exclusive_blocked(false);
                      release_waiters();
                      return false;
                  }
                  break;
              }
          }
          state.exclusive=true;
          //state.lock();
          return true;
        }


        bool try_lock()
        {
            boost::unique_lock<boost::mutex> lk(state_change);

            if(!state.can_lock())
            {
                return false;
            }
            else
            {
                state.lock();
                return true;
            }

        }


        void unlock()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.unlock();
            state.assert_free();
            release_waiters();
        }


        void lock_upgrade()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            while(!state.can_lock_upgrade())
            {
                shared_cond.wait(lk);
            }
            state.lock_upgrade();
        }

        bool timed_lock_upgrade(system_time const& timeout)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            while(!state.can_lock_upgrade())
            {
                if(!shared_cond.timed_wait(lk,timeout))
                {
                    if(!state.can_lock_upgrade())
                    {
                        return false;
                    }
                    break;
                }
            }
            state.lock_upgrade();
            return true;
        }


        template<typename TimeDuration>
        bool timed_lock_upgrade(TimeDuration const & relative_time)
        {
            return timed_lock_upgrade(get_system_time()+relative_time);
        }

        template <class Rep, class Period>
        bool try_lock_upgrade_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_upgrade_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_upgrade_until(const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);
          while(!state.can_lock_upgrade())
          {
              if(cv_status::timeout == shared_cond.wait_until(lk,abs_time))
              {
                  if(!state.can_lock_upgrade())
                  {
                      return false;
                  }
                  break;
              }
          }
          state.lock_upgrade();
          return true;
        }

        bool try_lock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            if(!state.can_lock_upgrade())
            {
                return false;
            }
            else
            {
                state.lock_upgrade();
                state.assert_lock_upgraded();
                return true;
            }
        }


        void unlock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_upgraded();
            state.unlock_upgrade();
            state.assert_lock_not_upgraded ();
            if(state.get_shared_count () == 0)
            {
                state.exclusive_blocked(false);
                lk.unlock();
                release_waiters();
            } else {
                lk.unlock();
                shared_cond.notify_all();
            }
        }

        void unlock_upgrade_and_lock()
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
            boost::this_thread::disable_interruption do_not_disturb;
#endif
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_upgraded();
            // assert state.get_shared_count() >=1
            while(
                //! state.exclusive_waiting_blocked  // Fixme: is this needed?
                //&&
                state.get_shared_count()!=1)
            {
                upgrade_cond.wait(lk);
            }
            state.unlock_upgrade();
            state.lock();
            state.assert_locked();
        }


        void unlock_and_lock_upgrade()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.unlock();
            state.lock_upgrade();
            state.assert_lock_upgraded();
            release_waiters();
        }


        bool try_unlock_upgrade_and_lock()
        {
          boost::unique_lock<boost::mutex> lk(state_change);
          state.assert_lock_upgraded();
          if( //!state.exclusive // this should be removed once the assertion work
                 ! state.exclusive_waiting_blocked // Fixme: why this is needed?
              //&& state.upgrade // this should be removed once the assertion work
              && state.get_shared_count()==1)
          {
            state.unlock_upgrade();
            state.lock();
            state.assert_locked();
            return true;
          }
          return false;
        }

        template <class Rep, class Period>
        bool
        try_unlock_upgrade_and_lock_for(
                                const chrono::duration<Rep, Period>& rel_time)
        {
          return try_unlock_upgrade_and_lock_until(
                                 chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool
        try_unlock_upgrade_and_lock_until(
                          const chrono::time_point<Clock, Duration>& abs_time)
        {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
          boost::this_thread::disable_interruption do_not_disturb;
#endif
          boost::unique_lock<boost::mutex> lk(state_change);
          state.assert_lock_upgraded();
          if (//state.exclusive // this should be removed once the assertion work
                 state.exclusive_waiting_blocked  // Fixme: is this needed?
              //|| ! state.upgrade // this should be removed once the assertion work
              || state.get_shared_count() != 1)
          {
              for (;;)
              {
                //cv_status status = shared_cond.wait_until(lk,abs_time);
                cv_status status = upgrade_cond.wait_until(lk,abs_time);
                if (//!state.exclusive // this should be removed once the assertion work
                       ! state.exclusive_waiting_blocked  // Fixme: is this needed?
                    //&& ! state.upgrade // this should be removed once the assertion work
                    &&   state.get_shared_count() == 1)
                  break;
                if(status == cv_status::timeout)
                  return false;
              }
          }
          state.unlock_upgrade();
          state.lock();
          return true;
        }

        void unlock_and_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_locked();
            state.unlock();
            state.lock_shared();
            release_waiters();
        }

        void unlock_upgrade_and_lock_shared()
        {
            boost::unique_lock<boost::mutex> lk(state_change);
            state.assert_lock_upgraded();
            //state.unlock_upgrade();
            //state.lock_shared(); // less efficient
            state.upgrade=false;
            state.exclusive_waiting_blocked=false; // Is this absolutely needed?
            release_waiters();
        }


            void initialize()
            {
                recursion_count=0;
                locking_thread_id=0;
                mutex.initialize();
            }


            void destroy()
            {
                mutex.destroy();
            }


            bool try_lock() BOOST_NOEXCEPT
            {
                long const current_thread_id=win32::GetCurrentThreadId();
                return try_recursive_lock(current_thread_id) || try_basic_lock(current_thread_id);
            }


            void lock()
            {
                long const current_thread_id=win32::GetCurrentThreadId();
                if(!try_recursive_lock(current_thread_id))
                {
                    mutex.lock();
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,current_thread_id);
                    recursion_count=1;
                }
            }

            bool timed_lock(::boost::system_time const& target)
            {
                long const current_thread_id=win32::GetCurrentThreadId();
                return try_recursive_lock(current_thread_id) || try_timed_lock(current_thread_id,target);
            }

            template<typename Duration>
            bool timed_lock(Duration const& timeout)
            {
                return timed_lock(get_system_time()+timeout);
            }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
                long const current_thread_id=win32::GetCurrentThreadId();
                return try_recursive_lock(current_thread_id) || try_timed_lock_for(current_thread_id,rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& t)
        {
                long const current_thread_id=win32::GetCurrentThreadId();
                return try_recursive_lock(current_thread_id) || try_timed_lock_until(current_thread_id,t);
        }

            void unlock()
            {
                if(!--recursion_count)
                {
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,0);
                    mutex.unlock();
                }
            }

            bool try_recursive_lock(long current_thread_id) BOOST_NOEXCEPT
            {
                if(::boost::detail::interlocked_read_acquire(&locking_thread_id)==current_thread_id)
                {
                    ++recursion_count;
                    return true;
                }
                return false;
            }


            bool try_basic_lock(long current_thread_id) BOOST_NOEXCEPT
            {
                if(mutex.try_lock())
                {
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,current_thread_id);
                    recursion_count=1;
                    return true;
                }
                return false;
            }

            bool try_timed_lock(long current_thread_id,::boost::system_time const& target)
            {
                if(mutex.timed_lock(target))
                {
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,current_thread_id);
                    recursion_count=1;
                    return true;
                }
                return false;
            }

            template <typename TP>
            bool try_timed_lock_until(long current_thread_id,TP const& target)
            {
                if(mutex.try_lock_until(target))
                {
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,current_thread_id);
                    recursion_count=1;
                    return true;
                }
                return false;
            }

            template <typename D>
            bool try_timed_lock_for(long current_thread_id,D const& target)
            {
                if(mutex.try_lock_for(target))
                {
                    BOOST_INTERLOCKED_EXCHANGE(&locking_thread_id,current_thread_id);
                    recursion_count=1;
                    return true;
                }
                return false;
            }

      thread_attributes() BOOST_NOEXCEPT {
        val_.stack_size = 0;
        //val_.lpThreadAttributes=0;
      }

      ~thread_attributes() {
      }

      void set_stack_size(std::size_t size) BOOST_NOEXCEPT {
        val_.stack_size = size;
      }


      std::size_t get_stack_size() const BOOST_NOEXCEPT {
          return val_.stack_size;
      }

      native_handle_type* native_handle() {return &val_;}

      const native_handle_type* native_handle() const {return &val_;}


            tss_data_node(boost::shared_ptr<boost::detail::tss_cleanup_function> func_,
                          void* value_):
                func(func_),value(value_)
            {}


            thread_data_base():
                count(0),thread_handle(detail::win32::invalid_handle_value),
                thread_exit_callbacks(0),tss_data(),
                id(0),
                notify(),
                async_states_()
//#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
                , interruption_handle(create_anonymous_event(detail::win32::manual_reset_event,detail::win32::event_initially_reset))
                , interruption_enabled(true)
//#endif
            {}

            void interrupt()
            {
                BOOST_VERIFY(detail::win32::SetEvent(interruption_handle)!=0);
            }


            void notify_all_at_thread_exit(condition_variable* cv, mutex* m)
            {
              notify.push_back(std::pair<condition_variable*, mutex*>(cv, m));
            }


            void make_ready_at_thread_exit(shared_ptr<future_object_base> as)
            {
              async_states_.push_back(as);
            }


            timeout(uintmax_t milliseconds_):
                start(win32::GetTickCount64()),
                milliseconds(milliseconds_),
                relative(true),
                abs_time(boost::get_system_time())
            {}


            timeout(boost::system_time const& abs_time_):
                start(win32::GetTickCount64()),
                milliseconds(0),
                relative(false),
                abs_time(abs_time_)
            {}


                remaining_time(uintmax_t remaining):
                    more(remaining>max_non_infinite_wait),
                    milliseconds(more?max_non_infinite_wait:(unsigned long)remaining)
                {}


            remaining_time remaining_milliseconds() const
            {
                if(is_sentinel())
                {
                    return remaining_time(win32::infinite);
                }
                else if(relative)
                {
                    win32::ticks_type const now=win32::GetTickCount64();
                    win32::ticks_type const elapsed=now-start;
                    return remaining_time((elapsed<milliseconds)?(milliseconds-elapsed):0);
                }
                else
                {
                    system_time const now=get_system_time();
                    if(abs_time<=now)
                    {
                        return remaining_time(0);
                    }
                    return remaining_time((abs_time-now).total_milliseconds()+1);
                }
            }


            bool is_sentinel() const
            {
                return milliseconds==~uintmax_t(0);
            }



            static timeout sentinel()
            {
                return timeout(sentinel_type());
            }


            explicit timeout(sentinel_type):
                start(0),milliseconds(~uintmax_t(0)),relative(true)
            {}


        inline uintmax_t pin_to_zero(intmax_t value)
        {
            return (value<0)?0u:(uintmax_t)value;
        }

        inline BOOST_SYMBOL_VISIBLE void interruptible_wait(system_time const& abs_time)
        {
            interruptible_wait(detail::win32::invalid_handle_value,abs_time);
        }

        template<typename TimeDuration>
        inline BOOST_SYMBOL_VISIBLE void sleep(TimeDuration const& rel_time)
        {
            interruptible_wait(detail::pin_to_zero(rel_time.total_milliseconds()));
        }

        inline BOOST_SYMBOL_VISIBLE void sleep(system_time const& abs_time)
        {
            interruptible_wait(abs_time);
        }

        inline void BOOST_SYMBOL_VISIBLE sleep_for(const chrono::nanoseconds& ns)
        {
          interruptible_wait(chrono::duration_cast<chrono::milliseconds>(ns).count());
        }

            explicit basic_cv_list_entry(detail::win32::handle_manager const& wake_sem_):
                semaphore(detail::win32::create_anonymous_semaphore(0,LONG_MAX)),
                wake_sem(wake_sem_.duplicate()),
                waiters(1),notified(false),references(0)
            {}


            static bool no_waiters(boost::intrusive_ptr<basic_cv_list_entry> const& entry)
            {
                return !detail::interlocked_read_acquire(&entry->waiters);
            }


            void add_waiter()
            {
                BOOST_INTERLOCKED_INCREMENT(&waiters);
            }


            void remove_waiter()
            {
                BOOST_INTERLOCKED_DECREMENT(&waiters);
            }


            void release(unsigned count_to_release)
            {
                notified=true;
                detail::win32::ReleaseSemaphore(semaphore,count_to_release,0);
            }


            void release_waiters()
            {
                release(detail::interlocked_read_acquire(&waiters));
            }


            bool is_notified() const
            {
                return notified;
            }


            bool wait(timeout abs_time)
            {
                return this_thread::interruptible_wait(semaphore,abs_time);
            }


            bool woken()
            {
                unsigned long const woken_result=detail::win32::WaitForSingleObject(wake_sem,0);
                BOOST_ASSERT((woken_result==detail::win32::timeout) || (woken_result==0));
                return woken_result==0;
            }


        inline void intrusive_ptr_add_ref(basic_cv_list_entry * p)
        {
            BOOST_INTERLOCKED_INCREMENT(&p->references);
        }


        inline void intrusive_ptr_release(basic_cv_list_entry * p)
        {
            if(!BOOST_INTERLOCKED_DECREMENT(&p->references))
            {
                delete p;
            }
        }


            void wake_waiters(long count_to_wake)
            {
                detail::interlocked_write_release(&total_count,total_count-count_to_wake);
                detail::win32::ReleaseSemaphore(wake_sem,count_to_wake,0);
            }


                relocker(lock_type& lock_):
                    lock(lock_),unlocked(false)
                {}

                void unlock()
                {
                    lock.unlock();
                    unlocked=true;
                }

                ~relocker()
                {
                    if(unlocked)
                    {
                        lock.lock();
                    }

                }



            entry_ptr get_wait_entry()
            {
                boost::lock_guard<boost::mutex> internal_lock(internal_mutex);

                if(!wake_sem)
                {
                    wake_sem=detail::win32::create_anonymous_semaphore(0,LONG_MAX);
                    BOOST_ASSERT(wake_sem);
                }

                detail::interlocked_write_release(&total_count,total_count+1);
                if(generations.empty() || generations.back()->is_notified())
                {
                    entry_ptr new_entry(new list_entry(wake_sem));
                    generations.push_back(new_entry);
                    return new_entry;
                }
                else
                {
                    generations.back()->add_waiter();
                    return generations.back();
                }
            }

                entry_manager(entry_ptr const& entry_):
                    entry(entry_)
                {}


                ~entry_manager()
                {
                  //if(! entry->is_notified()) // several regression #7657
                  {
                    entry->remove_waiter();
                  }
                }


                list_entry* operator->()
                {
                    return entry.get();
                }

            template<typename lock_type>
            bool do_wait(lock_type& lock,timeout abs_time)
            {
                relocker<lock_type> locker(lock);

                entry_manager entry(get_wait_entry());

                locker.unlock();

                bool woken=false;
                while(!woken)
                {
                    if(!entry->wait(abs_time))
                    {
                        return false;
                    }

                    woken=entry->woken();
                }
                return woken;
            }


            template<typename lock_type,typename predicate_type>
            bool do_wait(lock_type& m,timeout const& abs_time,predicate_type pred)
            {
                while (!pred())
                {
                    if(!do_wait(m, abs_time))
                        return pred();
                }
                return true;
            }

            basic_condition_variable():
                total_count(0),active_generation_count(0),wake_sem(0)
            {}


            ~basic_condition_variable()
            {}


            void notify_one() BOOST_NOEXCEPT
            {
                if(detail::interlocked_read_acquire(&total_count))
                {
                    boost::lock_guard<boost::mutex> internal_lock(internal_mutex);
                    if(!total_count)
                    {
                        return;
                    }
                    wake_waiters(1);

                    for(generation_list::iterator it=generations.begin(),
                            end=generations.end();
                        it!=end;++it)
                    {
                        (*it)->release(1);
                    }
                    generations.erase(std::remove_if(generations.begin(),generations.end(),&basic_cv_list_entry::no_waiters),generations.end());
                }
            }


            void notify_all() BOOST_NOEXCEPT
            {
                if(detail::interlocked_read_acquire(&total_count))
                {
                    boost::lock_guard<boost::mutex> internal_lock(internal_mutex);
                    if(!total_count)
                    {
                        return;
                    }
                    wake_waiters(total_count);
                    for(generation_list::iterator it=generations.begin(),
                            end=generations.end();
                        it!=end;++it)
                    {
                        (*it)->release_waiters();
                    }
                    generations.clear();
                    wake_sem=detail::win32::handle(0);
                }
            }

        condition_variable()
        {}


        void wait(unique_lock<mutex>& m)
        {
            do_wait(m,detail::timeout::sentinel());
        }


        template<typename predicate_type>
        void wait(unique_lock<mutex>& m,predicate_type pred)
        {
            while(!pred()) wait(m);
        }

        bool timed_wait(unique_lock<mutex>& m,boost::system_time const& abs_time)
        {
            return do_wait(m,abs_time);
        }


        bool timed_wait(unique_lock<mutex>& m,boost::xtime const& abs_time)
        {
            return do_wait(m,system_time(abs_time));
        }

        template<typename duration_type>
        bool timed_wait(unique_lock<mutex>& m,duration_type const& wait_duration)
        {
            return do_wait(m,wait_duration.total_milliseconds());
        }


        template<typename predicate_type>
        bool timed_wait(unique_lock<mutex>& m,boost::system_time const& abs_time,predicate_type pred)
        {
            return do_wait(m,abs_time,pred);
        }

        template<typename predicate_type>
        bool timed_wait(unique_lock<mutex>& m,boost::xtime const& abs_time,predicate_type pred)
        {
            return do_wait(m,system_time(abs_time),pred);
        }

        template<typename duration_type,typename predicate_type>
        bool timed_wait(unique_lock<mutex>& m,duration_type const& wait_duration,predicate_type pred)
        {
            return do_wait(m,wait_duration.total_milliseconds(),pred);
        }


        template <class Clock, class Duration>
        cv_status
        wait_until(
                unique_lock<mutex>& lock,
                const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          do_wait(lock, ceil<milliseconds>(t-Clock::now()).count());
          return Clock::now() < t ? cv_status::no_timeout :
                                             cv_status::timeout;
        }


        template <class Rep, class Period>
        cv_status
        wait_for(
                unique_lock<mutex>& lock,
                const chrono::duration<Rep, Period>& d)
        {
          using namespace chrono;
          steady_clock::time_point c_now = steady_clock::now();
          do_wait(lock, ceil<milliseconds>(d).count());
          return steady_clock::now() - c_now < d ? cv_status::no_timeout :
                                                   cv_status::timeout;
        }


        template <class Clock, class Duration, class Predicate>
        bool
        wait_until(
                unique_lock<mutex>& lock,
                const chrono::time_point<Clock, Duration>& t,
                Predicate pred)
        {
            while (!pred())
            {
                if (wait_until(lock, t) == cv_status::timeout)
                    return pred();
            }
            return true;
        }

        template <class Rep, class Period, class Predicate>
        bool
        wait_for(
                unique_lock<mutex>& lock,
                const chrono::duration<Rep, Period>& d,
                Predicate pred)
        {
            return wait_until(lock, chrono::steady_clock::now() + d, boost::move(pred));
        }

        condition_variable_any()
        {}


        template<typename lock_type>
        void wait(lock_type& m)
        {
            do_wait(m,detail::timeout::sentinel());
        }


        template<typename lock_type,typename predicate_type>
        void wait(lock_type& m,predicate_type pred)
        {
            while(!pred()) wait(m);
        }

        template<typename lock_type>
        bool timed_wait(lock_type& m,boost::system_time const& abs_time)
        {
            return do_wait(m,abs_time);
        }


        template<typename lock_type>
        bool timed_wait(lock_type& m,boost::xtime const& abs_time)
        {
            return do_wait(m,system_time(abs_time));
        }


        template<typename lock_type,typename duration_type>
        bool timed_wait(lock_type& m,duration_type const& wait_duration)
        {
            return do_wait(m,wait_duration.total_milliseconds());
        }


        template<typename lock_type,typename predicate_type>
        bool timed_wait(lock_type& m,boost::system_time const& abs_time,predicate_type pred)
        {
            return do_wait(m,abs_time,pred);
        }


        template<typename lock_type,typename predicate_type>
        bool timed_wait(lock_type& m,boost::xtime const& abs_time,predicate_type pred)
        {
            return do_wait(m,system_time(abs_time),pred);
        }


        template<typename lock_type,typename duration_type,typename predicate_type>
        bool timed_wait(lock_type& m,duration_type const& wait_duration,predicate_type pred)
        {
            return do_wait(m,wait_duration.total_milliseconds(),pred);
        }


        template <class lock_type, class Clock, class Duration>
        cv_status
        wait_until(
                lock_type& lock,
                const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          do_wait(lock, ceil<milliseconds>(t-Clock::now()).count());
          return Clock::now() < t ? cv_status::no_timeout :
                                             cv_status::timeout;
        }


        template <class lock_type,  class Rep, class Period>
        cv_status
        wait_for(
                lock_type& lock,
                const chrono::duration<Rep, Period>& d)
        {
          using namespace chrono;
          steady_clock::time_point c_now = steady_clock::now();
          do_wait(lock, ceil<milliseconds>(d).count());
          return steady_clock::now() - c_now < d ? cv_status::no_timeout :
                                                   cv_status::timeout;
        }


        template <class lock_type, class Clock, class Duration, class Predicate>
        bool
        wait_until(
                lock_type& lock,
                const chrono::time_point<Clock, Duration>& t,
                Predicate pred)
        {
            while (!pred())
            {
                if (wait_until(lock, t) == cv_status::timeout)
                    return pred();
            }
            return true;
        }


        template <class lock_type, class Rep, class Period, class Predicate>
        bool
        wait_for(
                lock_type& lock,
                const chrono::duration<Rep, Period>& d,
                Predicate pred)
        {
            return wait_until(lock, chrono::steady_clock::now() + d, boost::move(pred));
        }

        recursive_mutex()
        {
            ::boost::detail::basic_recursive_mutex::initialize();
        }

        ~recursive_mutex()
        {
            ::boost::detail::basic_recursive_mutex::destroy();
        }

        recursive_timed_mutex()
        {
            ::boost::detail::basic_recursive_timed_mutex::initialize();
        }

        ~recursive_timed_mutex()
        {
            ::boost::detail::basic_recursive_timed_mutex::destroy();
        }

        inline void* allocate_raw_heap_memory(unsigned size)
        {
            void* const heap_memory=detail::win32::HeapAlloc(detail::win32::GetProcessHeap(),0,size);
            if(!heap_memory)
            {
                boost::throw_exception(std::bad_alloc());
            }
            return heap_memory;
        }


        inline void free_raw_heap_memory(void* heap_memory)
        {
            BOOST_VERIFY(detail::win32::HeapFree(detail::win32::GetProcessHeap(),0,heap_memory)!=0);
        }


        template<typename T>
        inline T* heap_new()
        {
            void* const heap_memory=allocate_raw_heap_memory(sizeof(T));
            BOOST_TRY
            {
                T* const data=new (heap_memory) T();
                return data;
            }
            BOOST_CATCH(...)
            {
                free_raw_heap_memory(heap_memory);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }

        template<typename T,typename A1>
        inline T* heap_new_impl(A1 a1)
        {
            void* const heap_memory=allocate_raw_heap_memory(sizeof(T));
            BOOST_TRY
            {
                T* const data=new (heap_memory) T(a1);
                return data;
            }
            BOOST_CATCH(...)
            {
                free_raw_heap_memory(heap_memory);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }


        template<typename T,typename A1,typename A2>
        inline T* heap_new_impl(A1 a1,A2 a2)
        {
            void* const heap_memory=allocate_raw_heap_memory(sizeof(T));
            BOOST_TRY
            {
                T* const data=new (heap_memory) T(a1,a2);
                return data;
            }
            BOOST_CATCH(...)
            {
                free_raw_heap_memory(heap_memory);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }


        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new_impl(A1 a1,A2 a2,A3 a3)
        {
            void* const heap_memory=allocate_raw_heap_memory(sizeof(T));
            BOOST_TRY
            {
                T* const data=new (heap_memory) T(a1,a2,a3);
                return data;
            }
            BOOST_CATCH(...)
            {
                free_raw_heap_memory(heap_memory);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new_impl(A1 a1,A2 a2,A3 a3,A4 a4)
        {
            void* const heap_memory=allocate_raw_heap_memory(sizeof(T));
            BOOST_TRY
            {
                T* const data=new (heap_memory) T(a1,a2,a3,a4);
                return data;
            }
            BOOST_CATCH(...)
            {
                free_raw_heap_memory(heap_memory);
                BOOST_RETHROW
            }
            BOOST_CATCH_END
        }



        template<typename T,typename A1>
        inline T* heap_new(A1 const& a1)
        {
            return heap_new_impl<T,A1 const&>(a1);
        }

        template<typename T,typename A1>
        inline T* heap_new(A1& a1)
        {
            return heap_new_impl<T,A1&>(a1);
        }


        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1 const& a1,A2 const& a2)
        {
            return heap_new_impl<T,A1 const&,A2 const&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1& a1,A2 const& a2)
        {
            return heap_new_impl<T,A1&,A2 const&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1 const& a1,A2& a2)
        {
            return heap_new_impl<T,A1 const&,A2&>(a1,a2);
        }

        template<typename T,typename A1,typename A2>
        inline T* heap_new(A1& a1,A2& a2)
        {
            return heap_new_impl<T,A1&,A2&>(a1,a2);
        }


        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&>(a1,a2,a3);
        }


        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&>(a1,a2,a3);
        }

        template<typename T,typename A1,typename A2,typename A3>
        inline T* heap_new(A1& a1,A2& a2,A3& a3)
        {
            return heap_new_impl<T,A1&,A2&,A3&>(a1,a2,a3);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&,A4 const&>(a1,a2,a3,a4);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3& a3,A4 const& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3&,A4 const&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3 const&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3 const& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3 const&,A4&>(a1,a2,a3,a4);
        }


        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2 const& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2 const&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2 const& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2 const&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1 const& a1,A2& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1 const&,A2&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T,typename A1,typename A2,typename A3,typename A4>
        inline T* heap_new(A1& a1,A2& a2,A3& a3,A4& a4)
        {
            return heap_new_impl<T,A1&,A2&,A3&,A4&>(a1,a2,a3,a4);
        }

        template<typename T>
        inline void heap_delete(T* data)
        {
            data->~T();
            free_raw_heap_memory(data);
        }

            void operator()(T* data) const
            {
                detail::heap_delete(data);
            }


            void initialize()
            {
                active_count=0;
                event=0;
            }


            void destroy()
            {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4312)
#endif
                void* const old_event=BOOST_INTERLOCKED_EXCHANGE_POINTER(&event,0);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
                if(old_event)
                {
                    win32::CloseHandle(old_event);
                }
            }



            bool try_lock() BOOST_NOEXCEPT
            {
                return !win32::interlocked_bit_test_and_set(&active_count,lock_flag_bit);
            }


            void lock()
            {
                if(try_lock())
                {
                    return;
                }
                long old_count=active_count;
                mark_waiting_and_try_lock(old_count);

                if(old_count&lock_flag_value)
                {
                    bool lock_acquired=false;
                    void* const sem=get_event();

                    do
                    {
                        unsigned const retval(win32::WaitForSingleObject(sem, ::boost::detail::win32::infinite));
                        BOOST_VERIFY(0 == retval || ::boost::detail::win32::wait_abandoned == retval);
//                        BOOST_VERIFY(win32::WaitForSingleObject(
//                                         sem,::boost::detail::win32::infinite)==0);
                        clear_waiting_and_try_lock(old_count);
                        lock_acquired=!(old_count&lock_flag_value);
                    }
                    while(!lock_acquired);
                }
            }

            void mark_waiting_and_try_lock(long& old_count)
            {
                for(;;)
                {
                    bool const was_locked=(old_count&lock_flag_value) ? true : false;
                    long const new_count=was_locked?(old_count+1):(old_count|lock_flag_value);
                    long const current=BOOST_INTERLOCKED_COMPARE_EXCHANGE(&active_count,new_count,old_count);
                    if(current==old_count)
                    {
                        if(was_locked)
                            old_count=new_count;
                        break;
                    }
                    old_count=current;
                }
            }


            void clear_waiting_and_try_lock(long& old_count)
            {
                old_count&=~lock_flag_value;
                old_count|=event_set_flag_value;
                for(;;)
                {
                    long const new_count=((old_count&lock_flag_value)?old_count:((old_count-1)|lock_flag_value))&~event_set_flag_value;
                    long const current=BOOST_INTERLOCKED_COMPARE_EXCHANGE(&active_count,new_count,old_count);
                    if(current==old_count)
                    {
                        break;
                    }
                    old_count=current;
                }
            }

            bool timed_lock(::boost::system_time const& wait_until)
            {
                if(try_lock())
                {
                    return true;
                }
                long old_count=active_count;
                mark_waiting_and_try_lock(old_count);

                if(old_count&lock_flag_value)
                {
                    bool lock_acquired=false;
                    void* const sem=get_event();

                    do
                    {
                        if(win32::WaitForSingleObject(sem,::boost::detail::get_milliseconds_until(wait_until))!=0)
                        {
                            BOOST_INTERLOCKED_DECREMENT(&active_count);
                            return false;
                        }
                        clear_waiting_and_try_lock(old_count);
                        lock_acquired=!(old_count&lock_flag_value);
                    }
                    while(!lock_acquired);
                }
                return true;
            }


            template<typename Duration>
            bool timed_lock(Duration const& timeout)
            {
                return timed_lock(get_system_time()+timeout);
            }


            bool timed_lock(boost::xtime const& timeout)
            {
                return timed_lock(system_time(timeout));
            }

            template <class Rep, class Period>
            bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
            {
              return try_lock_until(chrono::steady_clock::now() + rel_time);
            }

            template <class Clock, class Duration>
            bool try_lock_until(const chrono::time_point<Clock, Duration>& t)
            {
              using namespace chrono;
              system_clock::time_point     s_now = system_clock::now();
              typename Clock::time_point  c_now = Clock::now();
              return try_lock_until(s_now + ceil<system_clock::duration>(t - c_now));
            }

            template <class Duration>
            bool try_lock_until(const chrono::time_point<chrono::system_clock, Duration>& t)
            {
              using namespace chrono;
              typedef time_point<chrono::system_clock, chrono::system_clock::duration> sys_tmpt;
              return try_lock_until(sys_tmpt(chrono::ceil<chrono::system_clock::duration>(t.time_since_epoch())));
            }

            bool try_lock_until(const chrono::time_point<chrono::system_clock, chrono::system_clock::duration>& tp)
            {
              if(try_lock())
              {
                  return true;
              }
              long old_count=active_count;
              mark_waiting_and_try_lock(old_count);

              if(old_count&lock_flag_value)
              {
                  bool lock_acquired=false;
                  void* const sem=get_event();

                  do
                  {
                      chrono::milliseconds rel_time= chrono::ceil<chrono::milliseconds>(tp-chrono::system_clock::now());

                      if(win32::WaitForSingleObject(sem,static_cast<unsigned long>(rel_time.count()))!=0)
                      {
                          BOOST_INTERLOCKED_DECREMENT(&active_count);
                          return false;
                      }
                      clear_waiting_and_try_lock(old_count);
                      lock_acquired=!(old_count&lock_flag_value);
                  }
                  while(!lock_acquired);
              }
              return true;
            }


            void unlock()
            {
                long const offset=lock_flag_value;
                long const old_count=BOOST_INTERLOCKED_EXCHANGE_ADD(&active_count,lock_flag_value);
                if(!(old_count&event_set_flag_value) && (old_count>offset))
                {
                    if(!win32::interlocked_bit_test_and_set(&active_count,event_set_flag_bit))
                    {
                        win32::SetEvent(get_event());
                    }
                }
            }

            void* get_event()
            {
                void* current_event=::boost::detail::interlocked_read_acquire(&event);

                if(!current_event)
                {
                    void* const new_event=win32::create_anonymous_event(win32::auto_reset_event,win32::event_initially_reset);
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif
                    void* const old_event=BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(&event,new_event,0);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
                    if(old_event!=0)
                    {
                        win32::CloseHandle(new_event);
                        return old_event;
                    }
                    else
                    {
                        return new_event;
                    }
                }
                return current_event;
            }

        inline long interlocked_read_acquire(long volatile* x) BOOST_NOEXCEPT
        {
            return BOOST_INTERLOCKED_COMPARE_EXCHANGE(x,0,0);
        }

        inline void* interlocked_read_acquire(void* volatile* x) BOOST_NOEXCEPT
        {
            return BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(x,0,0);
        }

        inline void interlocked_write_release(long volatile* x,long value) BOOST_NOEXCEPT
        {
            BOOST_INTERLOCKED_EXCHANGE(x,value);
        }

        inline void interlocked_write_release(void* volatile* x,void* value) BOOST_NOEXCEPT
        {
            BOOST_INTERLOCKED_EXCHANGE_POINTER(x,value);
        }



        template<typename T>
        T interlocked_compare_exchange(T* target,T new_value,T comparand)
        {
            BOOST_STATIC_ASSERT(sizeof(T)==sizeof(long));
            long const res=BOOST_INTERLOCKED_COMPARE_EXCHANGE(reinterpret_cast<long*>(target),
                                                              *reinterpret_cast<long*>(&new_value),
                                                              *reinterpret_cast<long*>(&comparand));
            return *reinterpret_cast<T const*>(&res);
        }


        void release_waiters(state_data old_state)
        {
            if(old_state.exclusive_waiting)
            {
                BOOST_VERIFY(detail::win32::ReleaseSemaphore(semaphores[exclusive_sem],1,0)!=0);
            }

            if(old_state.shared_waiting || old_state.exclusive_waiting)
            {
                BOOST_VERIFY(detail::win32::ReleaseSemaphore(semaphores[unlock_sem],old_state.shared_waiting + (old_state.exclusive_waiting?1:0),0)!=0);
            }
        }

        shared_mutex()
        {
            semaphores[unlock_sem]=detail::win32::create_anonymous_semaphore(0,LONG_MAX);
            semaphores[exclusive_sem]=detail::win32::create_anonymous_semaphore_nothrow(0,LONG_MAX);
            if (!semaphores[exclusive_sem])
            {
              detail::win32::release_semaphore(semaphores[unlock_sem],LONG_MAX);
              boost::throw_exception(thread_resource_error());
            }
            upgrade_sem=detail::win32::create_anonymous_semaphore_nothrow(0,LONG_MAX);
            if (!upgrade_sem)
            {
              detail::win32::release_semaphore(semaphores[unlock_sem],LONG_MAX);
              detail::win32::release_semaphore(semaphores[exclusive_sem],LONG_MAX);
              boost::throw_exception(thread_resource_error());
            }
            state_data state_={0,0,0,0,0,0};
            state=state_;
        }


        ~shared_mutex()
        {
            detail::win32::CloseHandle(upgrade_sem);
            detail::win32::CloseHandle(semaphores[unlock_sem]);
            detail::win32::CloseHandle(semaphores[exclusive_sem]);
        }


        bool try_lock_shared()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                if(!new_state.exclusive && !new_state.exclusive_waiting_blocked)
                {
                    ++new_state.shared_count;
                    if(!new_state.shared_count)
                    {
                        return false;
                    }
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            return !(old_state.exclusive| old_state.exclusive_waiting_blocked);
        }


        void lock_shared()
        {
#if defined BOOST_THREAD_USES_DATETIME
            BOOST_VERIFY(timed_lock_shared(::boost::detail::get_system_time_sentinel()));
#else
            BOOST_VERIFY(try_lock_shared_until(chrono::steady_clock::now()));
#endif
        }

        template<typename TimeDuration>
        bool timed_lock_shared(TimeDuration const & relative_time)
        {
            return timed_lock_shared(get_system_time()+relative_time);
        }

        bool timed_lock_shared(boost::system_time const& wait_until)
        {
            for(;;)
            {
                state_data old_state=state;
                for(;;)
                {
                    state_data new_state=old_state;
                    if(new_state.exclusive || new_state.exclusive_waiting_blocked)
                    {
                        ++new_state.shared_waiting;
                        if(!new_state.shared_waiting)
                        {
                            boost::throw_exception(boost::lock_error());
                        }
                    }
                    else
                    {
                        ++new_state.shared_count;
                        if(!new_state.shared_count)
                        {
                            boost::throw_exception(boost::lock_error());
                        }
                    }

                    state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                    if(current_state==old_state)
                    {
                        break;
                    }
                    old_state=current_state;
                }

                if(!(old_state.exclusive| old_state.exclusive_waiting_blocked))
                {
                    return true;
                }

                unsigned long const res=detail::win32::WaitForSingleObject(semaphores[unlock_sem],::boost::detail::get_milliseconds_until(wait_until));
                if(res==detail::win32::timeout)
                {
                    for(;;)
                    {
                        state_data new_state=old_state;
                        if(new_state.exclusive || new_state.exclusive_waiting_blocked)
                        {
                            if(new_state.shared_waiting)
                            {
                                --new_state.shared_waiting;
                            }
                        }
                        else
                        {
                            ++new_state.shared_count;
                            if(!new_state.shared_count)
                            {
                                return false;
                            }
                        }

                        state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                        if(current_state==old_state)
                        {
                            break;
                        }
                        old_state=current_state;
                    }

                    if(!(old_state.exclusive| old_state.exclusive_waiting_blocked))
                    {
                        return true;
                    }
                    return false;
                }

                BOOST_ASSERT(res==0);
            }
        }

        template <class Rep, class Period>
        bool try_lock_shared_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_shared_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_shared_until(const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          typename Clock::time_point  c_now = Clock::now();
          return try_lock_shared_until(s_now + ceil<system_clock::duration>(t - c_now));
        }

        template <class Duration>
        bool try_lock_shared_until(const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<chrono::system_clock, chrono::system_clock::duration> sys_tmpt;
          return try_lock_shared_until(sys_tmpt(chrono::ceil<chrono::system_clock::duration>(t.time_since_epoch())));
        }

        bool try_lock_shared_until(const chrono::time_point<chrono::system_clock, chrono::system_clock::duration>& tp)
        {
          for(;;)
          {
            state_data old_state=state;
            for(;;)
            {
              state_data new_state=old_state;
              if(new_state.exclusive || new_state.exclusive_waiting_blocked)
              {
                  ++new_state.shared_waiting;
                  if(!new_state.shared_waiting)
                  {
                      boost::throw_exception(boost::lock_error());
                  }
              }
              else
              {
                  ++new_state.shared_count;
                  if(!new_state.shared_count)
                  {
                      boost::throw_exception(boost::lock_error());
                  }
              }

              state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
              if(current_state==old_state)
              {
                  break;
              }
              old_state=current_state;
            }

            if(!(old_state.exclusive| old_state.exclusive_waiting_blocked))
            {
              return true;
            }

            chrono::system_clock::time_point n = chrono::system_clock::now();
            unsigned long res;
            if (tp>n) {
              chrono::milliseconds rel_time= chrono::ceil<chrono::milliseconds>(tp-n);
              res=detail::win32::WaitForSingleObject(semaphores[unlock_sem],
                static_cast<unsigned long>(rel_time.count()));
            } else {
              res=detail::win32::timeout;
            }
            if(res==detail::win32::timeout)
            {
              for(;;)
              {
                state_data new_state=old_state;
                if(new_state.exclusive || new_state.exclusive_waiting_blocked)
                {
                  if(new_state.shared_waiting)
                  {
                      --new_state.shared_waiting;
                  }
                }
                else
                {
                  ++new_state.shared_count;
                  if(!new_state.shared_count)
                  {
                      return false;
                  }
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
              }

              if(!(old_state.exclusive| old_state.exclusive_waiting_blocked))
              {
                return true;
              }
              return false;
            }

            BOOST_ASSERT(res==0);
          }
        }


        void unlock_shared()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                bool const last_reader=!--new_state.shared_count;

                if(last_reader)
                {
                    if(new_state.upgrade)
                    {
                        new_state.upgrade=false;
                        new_state.exclusive=true;
                    }
                    else
                    {
                        if(new_state.exclusive_waiting)
                        {
                            --new_state.exclusive_waiting;
                            new_state.exclusive_waiting_blocked=false;
                        }
                        new_state.shared_waiting=0;
                    }
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    if(last_reader)
                    {
                        if(old_state.upgrade)
                        {
                            BOOST_VERIFY(detail::win32::ReleaseSemaphore(upgrade_sem,1,0)!=0);
                        }
                        else
                        {
                            release_waiters(old_state);
                        }
                    }
                    break;
                }
                old_state=current_state;
            }
        }


        void lock()
        {
#if defined BOOST_THREAD_USES_DATETIME
            BOOST_VERIFY(timed_lock(::boost::detail::get_system_time_sentinel()));
#else
            BOOST_VERIFY(try_lock_until(chrono::steady_clock::now()));
#endif
        }

        template<typename TimeDuration>
        bool timed_lock(TimeDuration const & relative_time)
        {
            return timed_lock(get_system_time()+relative_time);
        }


        bool try_lock()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                if(new_state.shared_count || new_state.exclusive)
                {
                    return false;
                }
                else
                {
                    new_state.exclusive=true;
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            return true;
        }

        bool timed_lock(boost::system_time const& wait_until)
        {
            for(;;)
            {
                state_data old_state=state;

                for(;;)
                {
                    state_data new_state=old_state;
                    if(new_state.shared_count || new_state.exclusive)
                    {
                        ++new_state.exclusive_waiting;
                        if(!new_state.exclusive_waiting)
                        {
                            boost::throw_exception(boost::lock_error());
                        }

                        new_state.exclusive_waiting_blocked=true;
                    }
                    else
                    {
                        new_state.exclusive=true;
                    }

                    state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                    if(current_state==old_state)
                    {
                        break;
                    }
                    old_state=current_state;
                }

                if(!old_state.shared_count && !old_state.exclusive)
                {
                    return true;
                }
                #ifndef UNDER_CE
                const bool wait_all = true;
                #else
                const bool wait_all = false;
                #endif
                unsigned long const wait_res=detail::win32::WaitForMultipleObjects(2,semaphores,wait_all,::boost::detail::get_milliseconds_until(wait_until));
                if(wait_res==detail::win32::timeout)
                {
                    for(;;)
                    {
                        bool must_notify = false;
                        state_data new_state=old_state;
                        if(new_state.shared_count || new_state.exclusive)
                        {
                            if(new_state.exclusive_waiting)
                            {
                                if(!--new_state.exclusive_waiting)
                                {
                                    new_state.exclusive_waiting_blocked=false;
                                    must_notify = true;
                                }
                            }
                        }
                        else
                        {
                            new_state.exclusive=true;
                        }

                        state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                        if (must_notify)
                        {
                          BOOST_VERIFY(detail::win32::ReleaseSemaphore(semaphores[unlock_sem],1,0)!=0);
                        }

                        if(current_state==old_state)
                        {
                            break;
                        }
                        old_state=current_state;
                    }
                    if(!old_state.shared_count && !old_state.exclusive)
                    {
                        return true;
                    }
                    return false;
                }
                BOOST_ASSERT(wait_res<2);
            }
        }

        template <class Rep, class Period>
        bool try_lock_for(const chrono::duration<Rep, Period>& rel_time)
        {
          return try_lock_until(chrono::steady_clock::now() + rel_time);
        }

        template <class Clock, class Duration>
        bool try_lock_until(const chrono::time_point<Clock, Duration>& t)
        {
          using namespace chrono;
          system_clock::time_point     s_now = system_clock::now();
          typename Clock::time_point  c_now = Clock::now();
          return try_lock_until(s_now + ceil<system_clock::duration>(t - c_now));
        }

        template <class Duration>
        bool try_lock_until(const chrono::time_point<chrono::system_clock, Duration>& t)
        {
          using namespace chrono;
          typedef time_point<chrono::system_clock, chrono::system_clock::duration> sys_tmpt;
          return try_lock_until(sys_tmpt(chrono::ceil<chrono::system_clock::duration>(t.time_since_epoch())));
        }

        bool try_lock_until(const chrono::time_point<chrono::system_clock, chrono::system_clock::duration>& tp)
        {
          for(;;)
          {
            state_data old_state=state;

            for(;;)
            {
              state_data new_state=old_state;
              if(new_state.shared_count || new_state.exclusive)
              {
                ++new_state.exclusive_waiting;
                if(!new_state.exclusive_waiting)
                {
                    boost::throw_exception(boost::lock_error());
                }

                new_state.exclusive_waiting_blocked=true;
              }
              else
              {
                new_state.exclusive=true;
              }

              state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
              if(current_state==old_state)
              {
                break;
              }
              old_state=current_state;
            }

            if(!old_state.shared_count && !old_state.exclusive)
            {
                return true;
            }
            #ifndef UNDER_CE
            const bool wait_all = true;
            #else
            const bool wait_all = false;
            #endif

            chrono::system_clock::time_point n = chrono::system_clock::now();
            unsigned long wait_res;
            if (tp>n) {
              chrono::milliseconds rel_time= chrono::ceil<chrono::milliseconds>(tp-chrono::system_clock::now());
              wait_res=detail::win32::WaitForMultipleObjects(2,semaphores,wait_all,
                  static_cast<unsigned long>(rel_time.count()));
            } else {
              wait_res=detail::win32::timeout;
            }
            if(wait_res==detail::win32::timeout)
            {
              for(;;)
              {
                bool must_notify = false;
                state_data new_state=old_state;
                if(new_state.shared_count || new_state.exclusive)
                {
                  if(new_state.exclusive_waiting)
                  {
                    if(!--new_state.exclusive_waiting)
                    {
                      new_state.exclusive_waiting_blocked=false;
                      must_notify = true;
                    }
                  }
                }
                else
                {
                  new_state.exclusive=true;
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if (must_notify)
                {
                  BOOST_VERIFY(detail::win32::ReleaseSemaphore(semaphores[unlock_sem],1,0)!=0);
                }
                if(current_state==old_state)
                {
                  break;
                }
                old_state=current_state;
              }
              if(!old_state.shared_count && !old_state.exclusive)
              {
                return true;
              }
              return false;
            }
            BOOST_ASSERT(wait_res<2);
          }
        }


        void unlock()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                new_state.exclusive=false;
                if(new_state.exclusive_waiting)
                {
                    --new_state.exclusive_waiting;
                    new_state.exclusive_waiting_blocked=false;
                }
                new_state.shared_waiting=0;

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            release_waiters(old_state);
        }


        void lock_upgrade()
        {
            for(;;)
            {
                state_data old_state=state;
                for(;;)
                {
                    state_data new_state=old_state;
                    if(new_state.exclusive || new_state.exclusive_waiting_blocked || new_state.upgrade)
                    {
                        ++new_state.shared_waiting;
                        if(!new_state.shared_waiting)
                        {
                            boost::throw_exception(boost::lock_error());
                        }
                    }
                    else
                    {
                        ++new_state.shared_count;
                        if(!new_state.shared_count)
                        {
                            boost::throw_exception(boost::lock_error());
                        }
                        new_state.upgrade=true;
                    }

                    state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                    if(current_state==old_state)
                    {
                        break;
                    }
                    old_state=current_state;
                }

                if(!(old_state.exclusive|| old_state.exclusive_waiting_blocked|| old_state.upgrade))
                {
                    return;
                }

                BOOST_VERIFY(!detail::win32::WaitForSingleObject(semaphores[unlock_sem],detail::win32::infinite));
            }
        }


        bool try_lock_upgrade()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                if(new_state.exclusive || new_state.exclusive_waiting_blocked || new_state.upgrade)
                {
                    return false;
                }
                else
                {
                    ++new_state.shared_count;
                    if(!new_state.shared_count)
                    {
                        return false;
                    }
                    new_state.upgrade=true;
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            return true;
        }


        void unlock_upgrade()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                new_state.upgrade=false;
                bool const last_reader=!--new_state.shared_count;

                if(last_reader)
                {
                    if(new_state.exclusive_waiting)
                    {
                        --new_state.exclusive_waiting;
                        new_state.exclusive_waiting_blocked=false;
                    }
                    new_state.shared_waiting=0;
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    if(last_reader)
                    {
                        release_waiters(old_state);
                    }
                    // #7720
                    //else {
                    //    release_waiters(old_state);
                    //}
                    break;
                }
                old_state=current_state;
            }
        }


        void unlock_upgrade_and_lock()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                bool const last_reader=!--new_state.shared_count;

                if(last_reader)
                {
                    new_state.upgrade=false;
                    new_state.exclusive=true;
                }

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    if(!last_reader)
                    {
                        BOOST_VERIFY(!detail::win32::WaitForSingleObject(upgrade_sem,detail::win32::infinite));
                    }
                    break;
                }
                old_state=current_state;
            }
        }


        void unlock_and_lock_upgrade()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                new_state.exclusive=false;
                new_state.upgrade=true;
                ++new_state.shared_count;
                if(new_state.exclusive_waiting)
                {
                    --new_state.exclusive_waiting;
                    new_state.exclusive_waiting_blocked=false;
                }
                new_state.shared_waiting=0;

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            release_waiters(old_state);
        }


        void unlock_and_lock_shared()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                new_state.exclusive=false;
                ++new_state.shared_count;
                if(new_state.exclusive_waiting)
                {
                    --new_state.exclusive_waiting;
                    new_state.exclusive_waiting_blocked=false;
                }
                new_state.shared_waiting=0;

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            release_waiters(old_state);
        }

        void unlock_upgrade_and_lock_shared()
        {
            state_data old_state=state;
            for(;;)
            {
                state_data new_state=old_state;
                new_state.upgrade=false;
                if(new_state.exclusive_waiting)
                {
                    --new_state.exclusive_waiting;
                    new_state.exclusive_waiting_blocked=false;
                }
                new_state.shared_waiting=0;

                state_data const current_state=interlocked_compare_exchange(&state,new_state,old_state);
                if(current_state==old_state)
                {
                    break;
                }
                old_state=current_state;
            }
            release_waiters(old_state);
        }

        mutex()
        {
            initialize();
        }

        ~mutex()
        {
            destroy();
        }

        timed_mutex()
        {
            initialize();
        }


        ~timed_mutex()
        {
            destroy();
        }


        template <class I>
        void int_to_string(I p, once_char_type* buf)
        {
            for(unsigned i=0; i < sizeof(I)*2; ++i,++buf)
            {
#ifdef BOOST_NO_ANSI_APIS
                once_char_type const a=L'A';
#else
                once_char_type const a='A';
#endif
                *buf = a + static_cast<once_char_type>((p >> (i*4)) & 0x0f);
            }
            *buf = 0;
        }


        inline void name_once_mutex(once_char_type* mutex_name,void* flag_address)
        {
#ifdef BOOST_NO_ANSI_APIS
            static const once_char_type fixed_mutex_name[]=L"Local\\{C15730E2-145C-4c5e-B005-3BC753F42475}-once-flag";
#else
            static const once_char_type fixed_mutex_name[]="Local\\{C15730E2-145C-4c5e-B005-3BC753F42475}-once-flag";
#endif
            BOOST_STATIC_ASSERT(sizeof(fixed_mutex_name) ==
                                (sizeof(once_char_type)*(once_mutex_name_fixed_length+1)));

            std::memcpy(mutex_name,fixed_mutex_name,sizeof(fixed_mutex_name));
            detail::int_to_string(reinterpret_cast<std::ptrdiff_t>(flag_address),
                                  mutex_name + once_mutex_name_fixed_length);
            detail::int_to_string(win32::GetCurrentProcessId(),
                                  mutex_name + once_mutex_name_fixed_length + sizeof(void*)*2);
        }


        inline void* open_once_event(once_char_type* mutex_name,void* flag_address)
        {
            if(!*mutex_name)
            {
                name_once_mutex(mutex_name,flag_address);
            }

#ifdef BOOST_NO_ANSI_APIS
            return ::boost::detail::win32::OpenEventW(
#else
            return ::boost::detail::win32::OpenEventA(
#endif
                ::boost::detail::win32::synchronize |
                ::boost::detail::win32::event_modify_state,
                false,
                mutex_name);
        }


        inline void* create_once_event(once_char_type* mutex_name,void* flag_address)
        {
            if(!*mutex_name)
            {
                name_once_mutex(mutex_name,flag_address);
            }
#ifdef BOOST_NO_ANSI_APIS
            return ::boost::detail::win32::CreateEventW(
#else
            return ::boost::detail::win32::CreateEventA(
#endif
                0,::boost::detail::win32::manual_reset_event,
                ::boost::detail::win32::event_initially_reset,
                mutex_name);
        }

          once_context() :
            function_complete_flag_value(0xc15730e2),
            running_value(0x7f0725e3),
            counted(false)
          {
            mutex_name[0]=0;
          }


        inline bool enter_once_region(once_flag& flag, once_context& ctx) BOOST_NOEXCEPT
        {
          long status=BOOST_INTERLOCKED_COMPARE_EXCHANGE(&flag.status,ctx.running_value,0);
          if(!status)
          {
            if(!ctx.event_handle)
            {
                ctx.event_handle=detail::open_once_event(ctx.mutex_name,&flag);
            }
            if(ctx.event_handle)
            {
                ::boost::detail::win32::ResetEvent(ctx.event_handle);
            }
            return true;
          }
          return false;
        }

        inline void commit_once_region(once_flag& flag, once_context& ctx) BOOST_NOEXCEPT
        {
          if(!ctx.counted)
          {
              BOOST_INTERLOCKED_INCREMENT(&flag.count);
              ctx.counted=true;
          }
          BOOST_INTERLOCKED_EXCHANGE(&flag.status,ctx.function_complete_flag_value);
          if(!ctx.event_handle &&
             (::boost::detail::interlocked_read_acquire(&flag.count)>1))
          {
              ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
          }
          if(ctx.event_handle)
          {
              ::boost::detail::win32::SetEvent(ctx.event_handle);
          }
        }

        inline void rollback_once_region(once_flag& flag, once_context& ctx) BOOST_NOEXCEPT
        {
          BOOST_INTERLOCKED_EXCHANGE(&flag.status,0);
          if(!ctx.event_handle)
          {
              ctx.event_handle=detail::open_once_event(ctx.mutex_name,&flag);
          }
          if(ctx.event_handle)
          {
              ::boost::detail::win32::SetEvent(ctx.event_handle);
          }
        }

    template<typename Function>
    void call_once(once_flag& flag,Function f)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                    f();
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

    template<typename Function, typename T1>
    void call_once(once_flag& flag,Function f, T1 p1)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(f,p1) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

    template<typename Function, typename T1, typename T2>
    void call_once(once_flag& flag,Function f, T1 p1, T2 p2)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(f,p1,p2) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

    template<typename Function, typename T1, typename T2, typename T3>
    void call_once(once_flag& flag,Function f, T1 p1, T2 p2, T3 p3)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(f,p1,p2,p3) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

        inline void call_once(once_flag& flag, void (*f)())
        {
            // Try for a quick win: if the procedure has already been called
            // just skip through:
            detail::once_context ctx;
            while(::boost::detail::interlocked_read_acquire(&flag.status)
                  !=ctx.function_complete_flag_value)
            {
                if(detail::enter_once_region(flag, ctx))
                {
                    BOOST_TRY
                    {
                      f();
                    }
                    BOOST_CATCH(...)
                    {
                        detail::rollback_once_region(flag, ctx);
                        BOOST_RETHROW
                    }
                    BOOST_CATCH_END
                    detail::commit_once_region(flag, ctx);
                    break;
                }
                if(!ctx.counted)
                {
                    BOOST_INTERLOCKED_INCREMENT(&flag.count);
                    ctx.counted=true;
                    long status=::boost::detail::interlocked_read_acquire(&flag.status);
                    if(status==ctx.function_complete_flag_value)
                    {
                        break;
                    }
                    if(!ctx.event_handle)
                    {
                        ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                        continue;
                    }
                }
                BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                                 ctx.event_handle,::boost::detail::win32::infinite));
            }
        }

        template<typename T1>
        void call_once(once_flag& flag,void (*f)(BOOST_THREAD_RV_REF(T1)), BOOST_THREAD_RV_REF(T1) p1)
        {
            // Try for a quick win: if the procedure has already been called
            // just skip through:
            detail::once_context ctx;
            while(::boost::detail::interlocked_read_acquire(&flag.status)
                  !=ctx.function_complete_flag_value)
            {
                if(detail::enter_once_region(flag, ctx))
                {
                    BOOST_TRY
                    {
                       f(
                           thread_detail::decay_copy(boost::forward<T1>(p1))
                       );
                    }
                    BOOST_CATCH(...)
                    {
                        detail::rollback_once_region(flag, ctx);
                        BOOST_RETHROW
                    }
                    BOOST_CATCH_END
                    detail::commit_once_region(flag, ctx);
                    break;
                }
                if(!ctx.counted)
                {
                    BOOST_INTERLOCKED_INCREMENT(&flag.count);
                    ctx.counted=true;
                    long status=::boost::detail::interlocked_read_acquire(&flag.status);
                    if(status==ctx.function_complete_flag_value)
                    {
                        break;
                    }
                    if(!ctx.event_handle)
                    {
                        ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                        continue;
                    }
                }
                BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                                 ctx.event_handle,::boost::detail::win32::infinite));
            }
        }

        template<typename Function, typename T1, typename T2>
        void call_once(once_flag& flag,void (*f)(BOOST_THREAD_RV_REF(T1),BOOST_THREAD_RV_REF(T2)), BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2)
        {
            // Try for a quick win: if the procedure has already been called
            // just skip through:
            detail::once_context ctx;
            while(::boost::detail::interlocked_read_acquire(&flag.status)
                  !=ctx.function_complete_flag_value)
            {
                if(detail::enter_once_region(flag, ctx))
                {
                    BOOST_TRY
                    {
                      f(
                          thread_detail::decay_copy(boost::forward<T1>(p1)),
                          thread_detail::decay_copy(boost::forward<T2>(p2))
                      );
                    }
                    BOOST_CATCH(...)
                    {
                        detail::rollback_once_region(flag, ctx);
                        BOOST_RETHROW
                    }
                    BOOST_CATCH_END
                    detail::commit_once_region(flag, ctx);
                    break;
                }
                if(!ctx.counted)
                {
                    BOOST_INTERLOCKED_INCREMENT(&flag.count);
                    ctx.counted=true;
                    long status=::boost::detail::interlocked_read_acquire(&flag.status);
                    if(status==ctx.function_complete_flag_value)
                    {
                        break;
                    }
                    if(!ctx.event_handle)
                    {
                        ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                        continue;
                    }
                }
                BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                                 ctx.event_handle,::boost::detail::win32::infinite));
            }
        }

        template<typename Function, typename T1, typename T2, typename T3>
        void call_once(once_flag& flag,void (*f)(BOOST_THREAD_RV_REF(T1),BOOST_THREAD_RV_REF(T2)), BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2, BOOST_THREAD_RV_REF(T3) p3)
        {
            // Try for a quick win: if the procedure has already been called
            // just skip through:
            detail::once_context ctx;
            while(::boost::detail::interlocked_read_acquire(&flag.status)
                  !=ctx.function_complete_flag_value)
            {
                if(detail::enter_once_region(flag, ctx))
                {
                    BOOST_TRY
                    {
                      f(
                          thread_detail::decay_copy(boost::forward<T1>(p1)),
                          thread_detail::decay_copy(boost::forward<T2>(p2)),
                          thread_detail::decay_copy(boost::forward<T3>(p3))
                      );
                    }
                    BOOST_CATCH(...)
                    {
                        detail::rollback_once_region(flag, ctx);
                        BOOST_RETHROW
                    }
                    BOOST_CATCH_END
                    detail::commit_once_region(flag, ctx);
                    break;
                }
                if(!ctx.counted)
                {
                    BOOST_INTERLOCKED_INCREMENT(&flag.count);
                    ctx.counted=true;
                    long status=::boost::detail::interlocked_read_acquire(&flag.status);
                    if(status==ctx.function_complete_flag_value)
                    {
                        break;
                    }
                    if(!ctx.event_handle)
                    {
                        ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                        continue;
                    }
                }
                BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                                 ctx.event_handle,::boost::detail::win32::infinite));
            }
        }

    template<typename Function>
    void call_once(once_flag& flag,BOOST_THREAD_RV_REF(Function) f)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                    f();
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }


    template<typename Function, typename T1>
    void call_once(once_flag& flag,BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(
                      thread_detail::decay_copy(boost::forward<Function>(f)),
                      thread_detail::decay_copy(boost::forward<T1>(p1))
                  ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

    template<typename Function, typename T1, typename T2>
    void call_once(once_flag& flag,BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(
                      thread_detail::decay_copy(boost::forward<Function>(f)),
                      thread_detail::decay_copy(boost::forward<T1>(p1)),
                      thread_detail::decay_copy(boost::forward<T2>(p2))
                  ) BOOST_THREAD_INVOKE_RET_VOID_CALL;
                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }

    template<typename Function, typename T1, typename T2, typename T3>
    void call_once(once_flag& flag,BOOST_THREAD_RV_REF(Function) f, BOOST_THREAD_RV_REF(T1) p1, BOOST_THREAD_RV_REF(T2) p2, BOOST_THREAD_RV_REF(T3) p3)
    {
        // Try for a quick win: if the procedure has already been called
        // just skip through:
        detail::once_context ctx;
        while(::boost::detail::interlocked_read_acquire(&flag.status)
              !=ctx.function_complete_flag_value)
        {
            if(detail::enter_once_region(flag, ctx))
            {
                BOOST_TRY
                {
                  BOOST_THREAD_INVOKE_RET_VOID(
                      thread_detail::decay_copy(boost::forward<Function>(f)),
                      thread_detail::decay_copy(boost::forward<T1>(p1)),
                      thread_detail::decay_copy(boost::forward<T2>(p2)),
                      thread_detail::decay_copy(boost::forward<T3>(p3))
                  ) BOOST_THREAD_INVOKE_RET_VOID_CALL;

                }
                BOOST_CATCH(...)
                {
                    detail::rollback_once_region(flag, ctx);
                    BOOST_RETHROW
                }
                BOOST_CATCH_END
                detail::commit_once_region(flag, ctx);
                break;
            }
            if(!ctx.counted)
            {
                BOOST_INTERLOCKED_INCREMENT(&flag.count);
                ctx.counted=true;
                long status=::boost::detail::interlocked_read_acquire(&flag.status);
                if(status==ctx.function_complete_flag_value)
                {
                    break;
                }
                if(!ctx.event_handle)
                {
                    ctx.event_handle=detail::create_once_event(ctx.mutex_name,&flag);
                    continue;
                }
            }
            BOOST_VERIFY(!::boost::detail::win32::WaitForSingleObject(
                             ctx.event_handle,::boost::detail::win32::infinite));
        }
    }


            inline handle create_anonymous_event(event_type type,initial_event_state state)
            {
#if !defined(BOOST_NO_ANSI_APIS)
                handle const res=win32::CreateEventA(0,type,state,0);
#else
                handle const res=win32::CreateEventW(0,type,state,0);
#endif
                if(!res)
                {
                    boost::throw_exception(thread_resource_error());
                }
                return res;
            }


            inline handle create_anonymous_semaphore(long initial_count,long max_count)
            {
#if !defined(BOOST_NO_ANSI_APIS)
                handle const res=CreateSemaphoreA(0,initial_count,max_count,0);
#else
                handle const res=CreateSemaphoreW(0,initial_count,max_count,0);
#endif
                if(!res)
                {
                    boost::throw_exception(thread_resource_error());
                }
                return res;
            }

            inline handle create_anonymous_semaphore_nothrow(long initial_count,long max_count)
            {
#if !defined(BOOST_NO_ANSI_APIS)
                handle const res=CreateSemaphoreA(0,initial_count,max_count,0);
#else
                handle const res=CreateSemaphoreW(0,initial_count,max_count,0);
#endif
                return res;
            }


            inline handle duplicate_handle(handle source)
            {
                handle const current_process=GetCurrentProcess();
                long const same_access_flag=2;
                handle new_handle=0;
                bool const success=DuplicateHandle(current_process,source,current_process,&new_handle,0,false,same_access_flag)!=0;
                if(!success)
                {
                    boost::throw_exception(thread_resource_error());
                }
                return new_handle;
            }


            inline void release_semaphore(handle semaphore,long count)
            {
                BOOST_VERIFY(ReleaseSemaphore(semaphore,count,0)!=0);
            }


                void cleanup()
                {
                    if(handle_to_manage && handle_to_manage!=invalid_handle_value)
                    {
                        BOOST_VERIFY(CloseHandle(handle_to_manage));
                    }
                }

                handle_manager():
                    handle_to_manage(0)
                {}

            inline bool interlocked_bit_test_and_set(long* x,long bit)
            {
                long const value=1<<bit;
                long old=*x;
                do
                {
                    long const current=BOOST_INTERLOCKED_COMPARE_EXCHANGE(x,old|value,old);
                    if(current==old)
                    {
                        break;
                    }
                    old=current;
                }
                while(true);
                return (old&value)!=0;
            }


            inline bool interlocked_bit_test_and_reset(long* x,long bit)
            {
                long const value=1<<bit;
                long old=*x;
                do
                {
                    long const current=BOOST_INTERLOCKED_COMPARE_EXCHANGE(x,old&~value,old);
                    if(current==old)
                    {
                        break;
                    }
                    old=current;
                }
                while(true);
                return (old&value)!=0;
            }


    template <class Clock, class Duration>
    void sleep_until(const chrono::time_point<Clock, Duration>& t)
    {
      using namespace chrono;
      mutex mut;
      condition_variable cv;
      unique_lock<mutex> lk(mut);
      while (Clock::now() < t)
        cv.wait_until(lk, t);
    }

    template <class Rep, class Period>
    void sleep_for(const chrono::duration<Rep, Period>& d)
    {
      using namespace chrono;
      if (d > duration<Rep, Period>::zero())
      {
        steady_clock::time_point c_timeout = steady_clock::now() + ceil<nanoseconds>(d);
        sleep_until(c_timeout);
      }
    }

      template <class Rep, class Period>
      bool try_lock_for(const boost::chrono::duration<Rep, Period>& rel_time)
      {
        return try_lock_until(boost::chrono::steady_clock::now() + rel_time);
      }

      template <class Rep, class Period>
      bool
      try_lock_shared_for(const boost::chrono::duration<Rep, Period>& rel_time)
      {
        return try_lock_shared_until(boost::chrono::steady_clock::now() +
            rel_time);
      }

      template<typename TimeDuration>
      bool timed_lock(TimeDuration const & relative_time)
      {
          return timed_lock(get_system_time()+relative_time);
      }

      template<typename TimeDuration>
      bool timed_lock_shared(TimeDuration const & relative_time)
      {
        return timed_lock_shared(get_system_time()+relative_time);
      }


    template <class Clock, class Duration>
    bool
    shared_mutex::try_lock_until(
        const boost::chrono::time_point<Clock, Duration>& abs_time)
    {
      boost::unique_lock<mutex_t> lk(mut_);
      if (state_ & write_entered_)
      {
        while (true)
        {
          boost::cv_status status = gate1_.wait_until(lk, abs_time);
          if ((state_ & write_entered_) == 0)
            break;
          if (status == boost::cv_status::timeout)
            return false;
        }
      }
      state_ |= write_entered_;
      if (state_ & n_readers_)
      {
        while (true)
        {
          boost::cv_status status = gate2_.wait_until(lk, abs_time);
          if ((state_ & n_readers_) == 0)
            break;
          if (status == boost::cv_status::timeout)
          {
            state_ &= ~write_entered_;
            return false;
          }
        }
      }
      return true;
    }


    template <class Clock, class Duration>
    bool
    shared_mutex::try_lock_shared_until(
        const boost::chrono::time_point<Clock, Duration>& abs_time)
    {
      boost::unique_lock<mutex_t> lk(mut_);
      if ((state_ & write_entered_) || (state_ & n_readers_) == n_readers_)
      {
        while (true)
        {
          boost::cv_status status = gate1_.wait_until(lk, abs_time);
          if ((state_ & write_entered_) == 0 &&
              (state_ & n_readers_) < n_readers_)
            break;
          if (status == boost::cv_status::timeout)
            return false;
        }
      }
      count_t num_readers = (state_ & n_readers_) + 1;
      state_ &= ~n_readers_;
      state_ |= num_readers;
      return true;
    }
